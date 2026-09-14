#include "MulticastSocket.h"
#include "pdu_parser.h"
#include "ProductionSocketWrapper.h"
#include "logging.h"
#include "sys_endian.h"

// Platform networking headers.
// On Windows the winsock2/ws2tcpip headers are already pulled in through
// ISocketWrapper.h / ProductionSocketWrapper.h; only the C runtime helpers
// are needed here. On POSIX we include the BSD-socket header set directly.
#if defined(_WIN32) && !defined(__CYGWIN__)
  #include <cstring>   // memcpy
#else
  #include <arpa/inet.h>
  #include <errno.h>
  #include <fcntl.h>
  #include <net/if.h>
  #include <netinet/in.h>
  #include <netinet/ip.h>
  #include <netinet/ip6.h>
  #include <string.h>
  #include <poll.h>
  #include <sys/socket.h>
  #include <sys/types.h>
  #include <unistd.h>
#endif

#include <algorithm>
#include <chrono>
#include <condition_variable>
#include <limits>
#include <mutex>
#include <atomic>

// ---------------------------------------------------------------------------
// Platform error-reporting shim.
// POSIX socket calls report failures via errno; winsock reports via
// WSAGetLastError() and uses WSAEINTR instead of EINTR. net_last_error() and
// NET_EINTR let the loops below share one code path.
// ---------------------------------------------------------------------------
#if defined(_WIN32) && !defined(__CYGWIN__)
static inline int net_last_error() { return ::WSAGetLastError(); }
#define NET_EINTR WSAEINTR
#else
static inline int net_last_error() { return errno; }
#define NET_EINTR EINTR
#endif

// The MQB multi-interface path relies on Linux-only socket features
// (SO_BINDTODEVICE, SO_PRIORITY, ip_mreqn) that winsock does not provide, so it
// is Linux-only. The default single-interface path below is cross-platform.
#if defined(MQB_NETWORK_CONFIG_ENABLED) && defined(_WIN32) && !defined(__CYGWIN__)
#error "MQB_NETWORK_CONFIG_ENABLED (multi-interface VLAN path) is Linux-only and cannot be built on Windows. Build without this macro for the portable single-interface path."
#endif

// Compile-time feedback: print which code path is active for this TU
#ifdef MQB_NETWORK_CONFIG_ENABLED
#include <cinttypes>
#include <sstream>
#pragma message("MulticastSocket.cpp: MQB_NETWORK_CONFIG_ENABLED defined -> using MQB multi-iface code path")
#else
#pragma message("MulticastSocket.cpp: MQB_NETWORK_CONFIG_ENABLED NOT defined -> using LEGACY single-iface code path")
#endif

namespace {
constexpr size_t kMaxDatagramSize = 64 * 1024; // UDP max (approx)
#ifdef MQB_NETWORK_CONFIG_ENABLED
constexpr int kDupWindowMs = 50; // duplicate-suppression window in milliseconds
#endif
}

namespace multicast_socket_internal {
std::atomic<size_t>& SerializeLimitStorage() {
    static std::atomic<size_t> limit{std::numeric_limits<size_t>::max()};
    return limit;
}
}

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

#ifdef MQB_NETWORK_CONFIG_ENABLED
/**
 * @brief Split a comma-separated interface list into individual names.
 */
std::vector<std::string> MulticastSocket::splitInterfaces(const std::string& s) {
    std::vector<std::string> result;
    std::istringstream ss(s);
    std::string token;
    while (std::getline(ss, token, ',')) {
        if (!token.empty()) {
            result.push_back(token);
        }
    }
    return result;
}

/**
 * @brief FNV-1a 64-bit hash used for receive duplicate suppression.
 */
uint64_t MulticastSocket::fnv1a64(const uint8_t* data, size_t len) {
    uint64_t hash = 14695981039346656037ULL;
    for (size_t i = 0; i < len; ++i) {
        hash ^= static_cast<uint64_t>(data[i]);
        hash *= 1099511628211ULL;
    }
    return hash;
}
#endif

/**
 * @brief Constructs a multicast socket using default ProductionSocketWrapper.
 *
 * This function constructs a MulticastSocket object with the specified parameters,
 * using the default ProductionSocketWrapper for socket operations.
 * 
 * @param group_addr The multicast group address (IPv4 or IPv6).
 * @param local_port The local port for sending.
 * @param remote_port The remote port for receiving.
 * @param vlan_pro VLAN priority for outgoing packets.
 */
MulticastSocket::MulticastSocket(const std::string& group_addr, uint16_t local_port, uint16_t remote_port, uint32_t vlan_pro)
    : MulticastSocket(group_addr, local_port, remote_port, std::make_shared<ProductionSocketWrapper>(), vlan_pro) {}

/**
 * @brief Constructs a multicast socket with specified parameters.
 *
 * This constructor initializes the multicast socket with the given group address,
 * local port, remote port, socket wrapper, and VLAN priority.
 *
 * @param group_addr The multicast group address (IPv4 or IPv6).
 * @param local_port The local port for sending.
 * @param remote_port The remote port for receiving.
 * @param socket_wrapper The socket wrapper for socket operations.
 * @param vlan_pro VLAN priority for outgoing packets.
 */
MulticastSocket::MulticastSocket(const std::string& group_addr, uint16_t local_port, uint16_t remote_port, std::shared_ptr<ISocketWrapper> socket_wrapper, uint32_t vlan_pro)
    : recieve_sockfd_(-1), send_sockfd_(-1), group_addr_(group_addr), local_port_(local_port), remote_port_(remote_port), vlan_pro_(vlan_pro), socket_wrapper_(socket_wrapper) {
    // Detect address family
    struct in_addr v4;
    struct in6_addr v6;
    if (inet_pton(AF_INET, group_addr.c_str(), &v4) == 1) {
        family_ = AF_INET;
        sockaddr_in* sin = reinterpret_cast<sockaddr_in*>(&group_sockaddr_);
        sin->sin_family = AF_INET;
        sin->sin_port = htons(remote_port_);
        sin->sin_addr = v4;
        group_socklen_ = sizeof(sockaddr_in);
    } else if (inet_pton(AF_INET6, group_addr.c_str(), &v6) == 1) {
        family_ = AF_INET6;
        sockaddr_in6* sin6 = reinterpret_cast<sockaddr_in6*>(&group_sockaddr_);
        sin6->sin6_family = AF_INET6;
        sin6->sin6_port = htons(remote_port_);
        sin6->sin6_addr = v6;
        group_socklen_ = sizeof(sockaddr_in6);
    } else {
        family_ = AF_INET; // fallback
        group_socklen_ = 0;
    }
    vlan_pro_ = vlan_pro;
}

/**
 * @brief Destroy the `MulticastSocket` object.
 *
 * @details
 * Cleans up resources by stopping the socket if it is running.
 */
MulticastSocket::~MulticastSocket() { stop(); }

/**
 * @brief Start the multicast socket for sending and receiving.
 *
 * This function sets up the multicast socket and launches background threads
 * for non-blocking I/O operations.
 * 
 * @return true if the socket started successfully, false otherwise.
 */
bool MulticastSocket::start() {
    if (running_.load()) return true;
    if (!setupSocket()) return false;
    running_.store(true);

    // Launch background threads for non-blocking I/O
    recv_thread_ = std::thread(&MulticastSocket::recvLoop, this);
    send_thread_ = std::thread(&MulticastSocket::sendLoop, this);
    LOGI("MulticastSocket start group=%s localPort=%u remotePort=%u family=%d", group_addr_.c_str(), local_port_, remote_port_, family_);
    return true;
}

/**
 * @brief Stop the multicast socket and clean up resources.
 * This function stops the multicast socket, joins background threads,
 * and releases associated resources.
 */
void MulticastSocket::stop() {
    bool wasRunning;
    {
        // Hold queue_mutex_ while flipping running_ so that sendLoop's predicate
        // check (which runs under queue_mutex_ inside wait(lk, pred)) is properly
        // synchronized with this update. This closes the lost-wakeup race where
        // sendLoop could miss the notify_all if it was between the predicate
        // check and the actual wait.
        std::lock_guard<std::mutex> lk(queue_mutex_);
        wasRunning = running_.exchange(false);
    }
    if (!wasRunning) {
        closeSocket();
        return;
    }

    // Wake sender in case it is blocked on queue_cv_
    queue_cv_.notify_all();

    // Threads are always started when running_ was true, so joinable() must be true here.
    recv_thread_.join();
    send_thread_.join();

    closeSocket();
    LOGI("MulticastSocket stopped group=%s", group_addr_.c_str());
}

/**
 * @brief Set the callback function for received PDUs.
 *
 * This function sets the callback that will be invoked when PDUs are received.
 * 
 * @param cb The callback function to handle received PDUs.
 */
void MulticastSocket::setReceiveCallback(RecvCallback cb) { recv_callback_ = std::move(cb); }

/**
 * @brief Send a batch of PDUs via the multicast socket.
 *
 * This function enqueues a batch of PDUs to be sent by the multicast socket.
 * 
 * @param pdus The vector of PDUs to send.
 */
void MulticastSocket::sendPDUs(const std::vector<PDU>& pdus) {
    std::lock_guard<std::mutex> lk(queue_mutex_);
    send_queue_.push(pdus);
    queue_cv_.notify_one();
    LOGD("enqueue batch size=%zu", pdus.size());
}

/**
 * @brief Serialize a vector of PDUs into a byte array for transmission.
 *
 * This function serializes the given PDUs into a contiguous byte array,
 * ensuring that the total size does not exceed the configured limit.
 * 
 * @param pdus The vector of PDUs to serialize.
 * @return A vector of bytes representing the serialized PDUs.
 */
std::vector<uint8_t> MulticastSocket::serializePDUs(const std::vector<PDU>& pdus) {
    if (pdus.empty()) return {};

    size_t total = 0;
    const size_t limit = multicast_socket_internal::SerializeLimitStorage().load(std::memory_order_relaxed);
    for (const auto& p : pdus) {
        if (total >= limit) {
            return {};
        }
        const size_t remaining = limit - total;
        if (remaining <= PDU_HEADER_SIZE) {
            return {};
        }
        const size_t maxPayload = remaining - PDU_HEADER_SIZE;
        if (p.payload.size() > maxPayload) {
            return {};
        }
        total += PDU_HEADER_SIZE + p.payload.size();
    }

    std::vector<uint8_t> bytes;
    bytes.reserve(total);
    for (const auto& p : pdus) {
        uint32_t id_be = host_to_be32(p.message_id);
        uint32_t len_be = host_to_be32(p.length);
        const auto* idp = reinterpret_cast<const uint8_t*>(&id_be);
        const auto* lenp = reinterpret_cast<const uint8_t*>(&len_be);
        bytes.insert(bytes.end(), idp, idp + sizeof(id_be));
        bytes.insert(bytes.end(), lenp, lenp + sizeof(len_be));
        bytes.insert(bytes.end(), p.payload.begin(), p.payload.end());
    }

    return bytes;
}

/**
 * @brief Receive loop running in a background thread to handle incoming PDUs.
 *
 * This function continuously listens for incoming datagrams on the multicast socket,
 * parses them into PDUs, and invokes the registered callback with the received PDUs.
 */
#ifdef MQB_NETWORK_CONFIG_ENABLED
void MulticastSocket::recvLoop() {
    std::vector<uint8_t> buffer(kMaxDatagramSize);

    // Multi-interface path: poll all recv fds simultaneously.
    if (!recv_fds_.empty()) {
        std::vector<struct pollfd> pfds;
        pfds.reserve(recv_fds_.size());
        for (const auto& p : recv_fds_) {
            struct pollfd pfd{};
            pfd.fd = p.first;
            pfd.events = POLLIN;
            pfds.push_back(pfd);
        }

        while (running_.load()) {
            // Reset revents before each poll call.
            for (auto& pfd : pfds) { pfd.revents = 0; }

            int rv = socket_wrapper_->poll(pfds.data(), static_cast<nfds_t>(pfds.size()), 500);
            if (rv <= 0) continue;

            for (auto& pfd : pfds) {
                if ((pfd.revents & (POLLERR | POLLHUP | POLLNVAL)) != 0) continue;
                if ((pfd.revents & POLLIN) == 0) continue;

                sockaddr_storage src{};
                socklen_t srclen = sizeof(src);
                ssize_t n = socket_wrapper_->recvfrom(pfd.fd, buffer.data(), buffer.size(), 0,
                                                       (sockaddr*)&src, &srclen);
                if (n <= 0) {
                    if (n < 0 && errno != EINTR) {
                        std::this_thread::sleep_for(std::chrono::milliseconds(5));
                    }
                    continue;
                }

                // Duplicate suppression: compute hash and check 50 ms window.
                uint64_t h = fnv1a64(buffer.data(), static_cast<size_t>(n));
                auto now = std::chrono::steady_clock::now();
                bool is_dup = false;
                {
                    std::lock_guard<std::mutex> lk(hash_mutex_);
                    // Evict entries older than kDupWindowMs.
                    while (!recent_hashes_.empty()) {
                        auto age = std::chrono::duration_cast<std::chrono::milliseconds>(
                            now - recent_hashes_.front().second).count();
                        if (age >= kDupWindowMs) {
                            recent_hashes_.pop_front();
                        } else {
                            break;
                        }
                    }
                    // Check for duplicate.
                    for (const auto& entry : recent_hashes_) {
                        if (entry.first == h) { is_dup = true; break; }
                    }
                    if (!is_dup) {
                        recent_hashes_.push_back({h, now});
                    }
                }
                if (is_dup) {
                    LOGD("recvLoop dup suppressed hash=0x%" PRIx64, h);
                    continue;
                }

                auto pdus = PDUParser::parse(buffer.data(), static_cast<size_t>(n));
                LOGD("recv (multi-iface fd=%d) bytes=%zd parsed=%zu", pfd.fd, n, pdus.size());
                if (!pdus.empty() && recv_callback_) {
                    recv_callback_(pdus);
                }
            }
        }
        return; // multi-interface path done
    }

    // Legacy single-fd path (IPv4 or no interface specified).
    struct pollfd pfd{};
    pfd.fd = recieve_sockfd_;
    pfd.events = POLLIN;

    while (running_.load()) {
        pfd.revents = 0;
        int rv = socket_wrapper_->poll(&pfd, 1, 500);
        if (rv <= 0) continue;
        if ((pfd.revents & (POLLERR | POLLHUP | POLLNVAL)) != 0) break;
        if (pfd.revents & POLLIN) {
            sockaddr_storage src{};
            socklen_t srclen = sizeof(src);
            ssize_t n = socket_wrapper_->recvfrom(recieve_sockfd_, buffer.data(), buffer.size(), 0,
                                                   (sockaddr*)&src, &srclen);
            if (n < 0) {
                if (errno == EINTR) continue;
                std::this_thread::sleep_for(std::chrono::milliseconds(5));
                continue;
            }
            if (n == 0) continue;

            auto pdus = PDUParser::parse(buffer.data(), static_cast<size_t>(n));
            LOGD("recv datagram bytes=%zd parsed=%zu", n, pdus.size());
            if (!pdus.empty() && recv_callback_) {
                recv_callback_(pdus);
            }
        }
    }
}
#else
void MulticastSocket::recvLoop() {
    std::vector<uint8_t> buffer(kMaxDatagramSize);

    struct pollfd pfd;
    pfd.fd = recieve_sockfd_;
    pfd.events = POLLIN;
    pfd.revents = 0;

    while (running_.load()) {
    int rv = 0;
    rv = socket_wrapper_->poll(&pfd, 1, 500); // 500ms timeout to check running_
        if (rv <= 0) {
            // timeout
            continue;
        }
        if ((pfd.revents & (POLLERR | POLLHUP | POLLNVAL)) != 0) {
            // socket error or hangup; exit loop
            break;
        }
        if (pfd.revents & POLLIN) {
            sockaddr_storage src{};
            socklen_t srclen = sizeof(src);
            ssize_t n = 0;
            n = socket_wrapper_->recvfrom(recieve_sockfd_, buffer.data(), buffer.size(), 0, (sockaddr*)&src, &srclen);
            if (n < 0) {
                if (net_last_error() == NET_EINTR) continue;
                std::this_thread::sleep_for(std::chrono::milliseconds(5));
                continue;
            }
            if (n == 0) continue;

            auto pdus = PDUParser::parse(buffer.data(), static_cast<size_t>(n));
            LOGD("recv datagram bytes=%zd parsed=%zu", n, pdus.size());
            if (!pdus.empty() && recv_callback_) {
                recv_callback_(pdus);
            }
        }
    }
}
#endif

/**
 * @brief Send loop running in a background thread to handle outgoing PDUs.
 *
 * This function continuously checks for batches of PDUs to send, serializes them,
 * and transmits them via the multicast socket.
 */
// LCOV_EXCL_START
#ifdef MQB_NETWORK_CONFIG_ENABLED
void MulticastSocket::sendLoop() {
    for (;;) {
        std::vector<PDU> batch;
        {
            std::unique_lock<std::mutex> lk(queue_mutex_);
            queue_cv_.wait(lk, [&] { return !running_.load() || !send_queue_.empty(); });
            if (send_queue_.empty()) break;
            batch = std::move(send_queue_.front());
            send_queue_.pop();
        }// LCOV_EXCL_BR_LINE
        if (batch.empty()) {
            continue;
        }
        auto bytes = serializePDUs(batch);
        if (bytes.empty()) {
            LOGW("serializePDUs returned empty for non-empty batch size=%zu", batch.size());
            continue;
        }

        // Multi-interface path: send on every interface.
        if (!send_fds_.empty()) {
            for (const auto& sfd : send_fds_) {
                ssize_t sent = socket_wrapper_->sendto(sfd.first, bytes.data(), bytes.size(), 0,
                                                        (sockaddr*)&group_sockaddr_, group_socklen_);
                if (sent < 0) {
                    int e = errno;
                    LOGE("sendto (multi-iface fd=%d ifidx=%u) failed frames=%zu err=%d (%s)",
                         sfd.first, sfd.second, batch.size(), e, strerror(e));
                } else {
                    LOGD("send (multi-iface fd=%d ifidx=%u) frames=%zu totalBytes=%zu actuallySent=%zd",
                         sfd.first, sfd.second, batch.size(), bytes.size(), sent);
                }
            }
            continue;
        }

        // Legacy single-fd path.
        ssize_t sent = socket_wrapper_->sendto(send_sockfd_, bytes.data(), bytes.size(), 0,
                                                (sockaddr*)&group_sockaddr_, group_socklen_);
        if (sent < 0) {
            int e = errno;
            LOGE("sendto failed frames=%zu totalBytes=%zu err=%d (%s)", batch.size(), bytes.size(), e, strerror(e));
        } else {
            LOGD("send batch frames=%zu totalBytes=%zu actuallySent=%zd", batch.size(), bytes.size(), sent);
            size_t dumpLen = std::min<size_t>(64, bytes.size());
            char line[3*65] = {0};
            for (size_t i = 0; i < dumpLen; i++) {
                std::snprintf(line + i*3, 4, "%02X ", bytes[i]);
            }
            LOGD("send bytes head group=%s data=%s%s", group_addr_.c_str(), line, (dumpLen < bytes.size()) ? "..." : "");
        }
    }
}
#else
void MulticastSocket::sendLoop() {
    for (;;) {
        std::vector<PDU> batch;
        {
            std::unique_lock<std::mutex> lk(queue_mutex_);
            queue_cv_.wait(lk, [&] { return !running_.load() || !send_queue_.empty(); });
            bool empty = send_queue_.empty();
            if (empty) {
                break;
            }
            batch = std::move(send_queue_.front());
            send_queue_.pop();
        }// LCOV_EXCL_BR_LINE
        if (batch.empty()) {
            continue;
        }
        auto bytes = serializePDUs(batch);
        if (bytes.empty()) {
            LOGW("serializePDUs returned empty for non-empty batch size=%zu", batch.size());
            continue;
        }
        ssize_t sent = socket_wrapper_->sendto(send_sockfd_, bytes.data(), bytes.size(), 0, (sockaddr*)&group_sockaddr_, group_socklen_);
        if (sent < 0) {
            int e = net_last_error();
            (void)e;
            LOGE("sendto failed frames=%zu totalBytes=%zu err=%d", batch.size(), bytes.size(), e);
        } else {
            LOGD("send batch frames=%zu totalBytes=%zu actuallySent=%zd", batch.size(), bytes.size(), sent);
            // Optional concise hex dump (cap at first 64 bytes)
            size_t dumpLen = std::min<size_t>(64, bytes.size());
            char line[3*65] = {0};
            for (size_t i=0;i<dumpLen;i++) {
                std::snprintf(line + i*3, 4, "%02X ", bytes[i]);
            }
            LOGD("send bytes head group=%s data=%s%s", group_addr_.c_str(), line, (dumpLen < bytes.size()) ? "..." : "");
        }
    }
}
#endif
// LCOV_EXCL_START
/**
 * @brief Setup the multicast socket for sending and receiving.
 *
 * This function creates and configures the multicast socket, including joining
 * the multicast group and setting socket options.
 *
 * @return true if setup was successful, false otherwise.
 */
#ifdef MQB_NETWORK_CONFIG_ENABLED
bool MulticastSocket::setupSocket() {
    int32_t reuse_addr = 1;
    int reuse = 1;

    // -----------------------------------------------------------------------
    // Multi-interface IPv6 path
    // -----------------------------------------------------------------------
    if (family_ == AF_INET6 && !local_addrs_.empty()) {
        constexpr int kIfaceRetryIntervalMs = 500;  // wait between retries when interfaces are not ready
        constexpr int kIfaceMaxTotalWaitMs = 10000; // total retry timeout (10 seconds)
        int waitedMs = 0;

        LOGI("setupSocket: multi-iface path group=%s ifaceCount=%zu", group_addr_.c_str(), local_addrs_.size());

        while (true) {
            for (const auto& iface : local_addrs_) {
                // --- Receive fd ---
                int rfd = socket_wrapper_->socket(AF_INET6, SOCK_DGRAM, 0);
                if (rfd < 0) {
                    LOGW("setupSocket: socket() failed for recv iface=%s errno=%d", iface.c_str(), errno);
                    continue;
                }
                if (socket_wrapper_->setsockopt(rfd, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof(reuse_addr)) < 0) {
                    LOGW("setupSocket: SO_REUSEADDR failed iface=%s errno=%d", iface.c_str(), errno);
                    socket_wrapper_->close(rfd);
                    continue;
                }
                // SO_REUSEPORT intentionally NOT set on recv fds: we want each fd
                // to receive its own copy of the multicast datagram independently.

                sockaddr_in6 addr6{};
                addr6.sin6_family = AF_INET6;
                addr6.sin6_port = htons(remote_port_);
                addr6.sin6_addr = in6addr_any;
                if (socket_wrapper_->bind(rfd, (sockaddr*)&addr6, sizeof(addr6)) < 0) {
                    LOGW("setupSocket: bind() failed for recv iface=%s errno=%d", iface.c_str(), errno);
                    socket_wrapper_->close(rfd);
                    continue;
                }

                unsigned int ifindex = socket_wrapper_->if_nametoindex(iface.c_str());
                if (ifindex == 0) {
                    LOGW("setupSocket: if_nametoindex failed iface=%s", iface.c_str());
                    socket_wrapper_->close(rfd);
                    continue;
                }

                struct ipv6_mreq mreq6{};
                inet_pton(AF_INET6, group_addr_.c_str(), &mreq6.ipv6mr_multiaddr);
                mreq6.ipv6mr_interface = ifindex;
                if (socket_wrapper_->setsockopt(rfd, IPPROTO_IPV6, IPV6_JOIN_GROUP, &mreq6, sizeof(mreq6)) < 0) {
                    LOGW("setupSocket: IPV6_JOIN_GROUP failed iface=%s errno=%d", iface.c_str(), errno);
                    socket_wrapper_->close(rfd);
                    continue;
                }

                int hops = 1;
                socket_wrapper_->setsockopt(rfd, IPPROTO_IPV6, IPV6_MULTICAST_HOPS, &hops, sizeof(hops));
                unsigned int loop = 1;
                socket_wrapper_->setsockopt(rfd, IPPROTO_IPV6, IPV6_MULTICAST_LOOP, &loop, sizeof(loop));
                socket_wrapper_->setsockopt(rfd, IPPROTO_IPV6, IPV6_MULTICAST_IF, &ifindex, sizeof(ifindex));

                recv_fds_.push_back({rfd, ifindex});
                LOGD("setupSocket: recv fd=%d ifindex=%u iface=%s", rfd, ifindex, iface.c_str());

                // --- Send fd ---
                int sfd = socket_wrapper_->socket(AF_INET6, SOCK_DGRAM, 0);
                if (sfd < 0) {
                    LOGW("setupSocket: socket() failed for send iface=%s errno=%d", iface.c_str(), errno);
                    // recv fd already registered; continue with recv-only for this iface.
                    send_fds_.push_back({-1, ifindex});
                    continue;
                }
                socket_wrapper_->setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof(reuse_addr));
                socket_wrapper_->setsockopt(sfd, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse));
                socket_wrapper_->setsockopt(sfd, SOL_SOCKET, SO_PRIORITY, &vlan_pro_, sizeof(vlan_pro_));
                // SO_BINDTODEVICE ensures the kernel routes outgoing packets through this
                // specific VLAN sub-interface regardless of the multicast routing table.
                // Without it, all send fds fall back to the routing table default (vnetap0.3).
                if (socket_wrapper_->setsockopt(sfd, SOL_SOCKET, SO_BINDTODEVICE,
                                                 iface.c_str(), static_cast<socklen_t>(iface.size() + 1)) < 0) {
                    LOGW("setupSocket: SO_BINDTODEVICE failed for send iface=%s errno=%d", iface.c_str(), errno);
                    socket_wrapper_->close(sfd);
                    send_fds_.push_back({-1, ifindex});
                    continue;
                }

                sockaddr_in6 saddr6{};
                saddr6.sin6_family = AF_INET6;
                saddr6.sin6_port = htons(local_port_);
                saddr6.sin6_addr = in6addr_any;
                if (socket_wrapper_->bind(sfd, (sockaddr*)&saddr6, sizeof(saddr6)) < 0) {
                    LOGW("setupSocket: bind() failed for send iface=%s errno=%d", iface.c_str(), errno);
                    socket_wrapper_->close(sfd);
                    send_fds_.push_back({-1, ifindex});
                    continue;
                }

                int send_hops = 255;
                socket_wrapper_->setsockopt(sfd, IPPROTO_IPV6, IPV6_MULTICAST_HOPS, &send_hops, sizeof(send_hops));
                unsigned int loopDisable = 0;
                socket_wrapper_->setsockopt(sfd, IPPROTO_IPV6, IPV6_MULTICAST_LOOP, &loopDisable, sizeof(loopDisable));
                // Pre-bind outgoing interface so sendLoop only needs sendto().
                socket_wrapper_->setsockopt(sfd, IPPROTO_IPV6, IPV6_MULTICAST_IF, &ifindex, sizeof(ifindex));

                send_fds_.push_back({sfd, ifindex});
                LOGD("setupSocket: send fd=%d ifindex=%u iface=%s", sfd, ifindex, iface.c_str());
            }

            // At least one usable recv fd is required.
            bool any_recv = false;
            for (const auto& p : recv_fds_) { if (p.first >= 0) { any_recv = true; break; } }
            if (any_recv) {
                LOGI("setupSocket (multi-iface) success group=%s recvFds=%zu sendFds=%zu waitedMs=%d",
                     group_addr_.c_str(), recv_fds_.size(), send_fds_.size(), waitedMs);
                return true;
            }

            // All interfaces failed — decide whether to retry.
            if (waitedMs >= kIfaceMaxTotalWaitMs) {
                LOGE("setupSocket: all interfaces failed after %dms retry timeout for group=%s",
                     waitedMs, group_addr_.c_str());
                closeSocket();
                return false;
            }

            LOGW("setupSocket: all interfaces failed for group=%s, retrying in %dms (waited %dms/%dms)",
                 group_addr_.c_str(), kIfaceRetryIntervalMs, waitedMs, kIfaceMaxTotalWaitMs);
            closeSocket();
            std::this_thread::sleep_for(std::chrono::milliseconds(kIfaceRetryIntervalMs));
            waitedMs += kIfaceRetryIntervalMs;
        }
    }

    // -----------------------------------------------------------------------
    // Legacy path (IPv4 or no interface specified)
    // -----------------------------------------------------------------------

    // Receive socket (multicast membership) bound to remote_port_
    recieve_sockfd_ = socket_wrapper_->socket(family_, SOCK_DGRAM, 0);
    if (recieve_sockfd_ < 0) return false;

    if (socket_wrapper_->setsockopt(recieve_sockfd_, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof(reuse_addr)) < 0) {
        int e = errno;
        LOGD("setsockopt SO_REUSEADDR failed on recieve_sockfd_ err=%d (%s)", e, strerror(e));
        socket_wrapper_->close(recieve_sockfd_);
        return false;
    }
    LOGD("SO_REUSEADDR enabled on recieve_sockfd_");

    socket_wrapper_->setsockopt(recieve_sockfd_, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse));

    if (family_ == AF_INET) {
        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_port = htons(remote_port_);
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        if (socket_wrapper_->bind(recieve_sockfd_, (sockaddr*)&addr, sizeof(addr)) < 0) {
            closeSocket();
            return false;
        }

        ip_mreqn mreq{};
        inet_pton(AF_INET, group_addr_.c_str(), &mreq.imr_multiaddr);
        mreq.imr_address.s_addr = htonl(INADDR_ANY);
        mreq.imr_ifindex = 0;
        if (socket_wrapper_->setsockopt(recieve_sockfd_, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) {
            ip_mreq mreq2{};
            memcpy(&mreq2.imr_multiaddr, &mreq.imr_multiaddr, sizeof(in_addr));
            mreq2.imr_interface.s_addr = htonl(INADDR_ANY);
            if (socket_wrapper_->setsockopt(recieve_sockfd_, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq2, sizeof(mreq2)) < 0) {
                closeSocket();
                return false;
            }
        }

        int ttl = 1;
        socket_wrapper_->setsockopt(recieve_sockfd_, IPPROTO_IP, IP_MULTICAST_TTL, &ttl, sizeof(ttl));
        unsigned char loop = 1;
        socket_wrapper_->setsockopt(recieve_sockfd_, IPPROTO_IP, IP_MULTICAST_LOOP, &loop, sizeof(loop));
    } else { // AF_INET6, no interface list
        sockaddr_in6 addr6{};
        addr6.sin6_family = AF_INET6;
        addr6.sin6_port = htons(remote_port_);
        addr6.sin6_addr = in6addr_any;
        if (socket_wrapper_->bind(recieve_sockfd_, (sockaddr*)&addr6, sizeof(addr6)) < 0) {
            closeSocket();
            return false;
        }

        struct ipv6_mreq mreq6{};
        inet_pton(AF_INET6, group_addr_.c_str(), &mreq6.ipv6mr_multiaddr);
        unsigned int ifindex6 = 0;
        if (!local_addrs_.empty()) {
            ifindex6 = socket_wrapper_->if_nametoindex(local_addrs_[0].c_str());
        }
        mreq6.ipv6mr_interface = ifindex6;
        if (socket_wrapper_->setsockopt(recieve_sockfd_, IPPROTO_IPV6, IPV6_JOIN_GROUP, &mreq6, sizeof(mreq6)) < 0) {
            closeSocket();
            return false;
        }

        int hops = 1;
        socket_wrapper_->setsockopt(recieve_sockfd_, IPPROTO_IPV6, IPV6_MULTICAST_HOPS, &hops, sizeof(hops));
        unsigned int loop = 1;
        socket_wrapper_->setsockopt(recieve_sockfd_, IPPROTO_IPV6, IPV6_MULTICAST_LOOP, &loop, sizeof(loop));
        if (ifindex6 != 0) {
            socket_wrapper_->setsockopt(recieve_sockfd_, IPPROTO_IPV6, IPV6_MULTICAST_IF, &ifindex6, sizeof(ifindex6));
        }
    }

    // Create separate send socket bound to local_port_
    send_sockfd_ = socket_wrapper_->socket(family_, SOCK_DGRAM, 0);
    if (send_sockfd_ >= 0) {
        if (socket_wrapper_->setsockopt(send_sockfd_, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof(reuse_addr)) < 0) {
            int e = errno;
            LOGD("setsockopt SO_REUSEADDR failed on send_sockfd_ err=%d (%s)", e, strerror(e));
            socket_wrapper_->close(send_sockfd_);
            return false;
        }
        LOGD("SO_REUSEADDR enabled on send_sockfd_");
        socket_wrapper_->setsockopt(send_sockfd_, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse));
        if (family_ == AF_INET) {
            int send_ttl = 255;
            if (socket_wrapper_->setsockopt(send_sockfd_, IPPROTO_IP, IP_MULTICAST_TTL, &send_ttl, sizeof(send_ttl)) < 0) {
                LOGD("Failed to set send socket IP_MULTICAST_TTL to 255");
            } else {
                LOGD("Send socket IPv4 multicast TTL set to 255");
            }
            unsigned char loopDisable = 0;
            socket_wrapper_->setsockopt(send_sockfd_, IPPROTO_IP, IP_MULTICAST_LOOP, &loopDisable, sizeof(loopDisable));
            socket_wrapper_->setsockopt(send_sockfd_, SOL_SOCKET, SO_PRIORITY, &vlan_pro_, sizeof(vlan_pro_));
            sockaddr_in saddr{};
            saddr.sin_family = AF_INET;
            saddr.sin_port = htons(local_port_);
            saddr.sin_addr.s_addr = htonl(INADDR_ANY);
            if (socket_wrapper_->bind(send_sockfd_, (sockaddr*)&saddr, sizeof(saddr)) < 0) {
                socket_wrapper_->close(send_sockfd_);
                send_sockfd_ = -1;
            }
        } else { // IPv6
            int send_hops = 255;
            if (socket_wrapper_->setsockopt(send_sockfd_, IPPROTO_IPV6, IPV6_MULTICAST_HOPS, &send_hops, sizeof(send_hops)) < 0) {
                LOGD("Failed to set send socket IPV6_MULTICAST_HOPS to 255");
            } else {
                LOGD("Send socket IPv6 multicast hop limit set to 255");
            }
            unsigned int loopDisable = 0;
            socket_wrapper_->setsockopt(send_sockfd_, IPPROTO_IPV6, IP_MULTICAST_LOOP, &loopDisable, sizeof(loopDisable));
            socket_wrapper_->setsockopt(send_sockfd_, SOL_SOCKET, SO_PRIORITY, &vlan_pro_, sizeof(vlan_pro_));
            sockaddr_in6 saddr6{};
            saddr6.sin6_family = AF_INET6;
            saddr6.sin6_port = htons(local_port_);
            unsigned int ifindex6 = 0;
            if (!local_addrs_.empty()) {
                ifindex6 = socket_wrapper_->if_nametoindex(local_addrs_[0].c_str());
            }
            if (socket_wrapper_->bind(send_sockfd_, (sockaddr*)&saddr6, sizeof(saddr6)) < 0) {
                LOGD("Failed to bind IPv6 send socket port=%u", local_port_);
                socket_wrapper_->close(send_sockfd_);
                send_sockfd_ = -1;
            } else if (ifindex6 != 0) {
                LOGD("Setting IPv6 multicast interface index to %u", ifindex6);
                socket_wrapper_->setsockopt(send_sockfd_, IPPROTO_IPV6, IPV6_MULTICAST_IF, &ifindex6, sizeof(ifindex6));
            }
        }
    }
    LOGD("setupSocket success group=%s recvFd=%d sendFd=%d vlanPro=%u", group_addr_.c_str(), recieve_sockfd_, send_sockfd_, vlan_pro_);
    return true;
}
#else
bool MulticastSocket::setupSocket() {
    constexpr int kSocketRetryIntervalMs = 500;  // wait between retries
    constexpr int kSocketMaxTotalWaitMs = 10000; // total retry timeout (10 seconds)
    int waitedMs = 0;

    while (true) {
        // Receive socket (multicast membership) bound to remote_port_
        recieve_sockfd_ = socket_wrapper_->socket(family_, SOCK_DGRAM, 0);
        if (recieve_sockfd_ < 0) {
            if (waitedMs >= kSocketMaxTotalWaitMs) {
                LOGE("setupSocket: socket creation failed after %dms retry timeout", waitedMs);
                return false;
            }
            LOGW("setupSocket: socket creation failed, retrying in %dms (waited %dms/%dms)",
                 kSocketRetryIntervalMs, waitedMs, kSocketMaxTotalWaitMs);
            std::this_thread::sleep_for(std::chrono::milliseconds(kSocketRetryIntervalMs));
            waitedMs += kSocketRetryIntervalMs;
            continue;
        }

        // -------- SET  SO_REUSEADDR --------
        int32_t reuse_addr = 1;
        if (socket_wrapper_->setsockopt(recieve_sockfd_, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof(reuse_addr)) < 0) {
            int e = net_last_error();
            (void)e;
            LOGD("setsockopt SO_REUSEADDR failed on recieve_sockfd_ err=%d", e);
            socket_wrapper_->close(recieve_sockfd_);
            if (waitedMs >= kSocketMaxTotalWaitMs) {
                LOGE("setupSocket: SO_REUSEADDR failed after %dms retry timeout", waitedMs);
                return false;
            }
            LOGW("setupSocket: SO_REUSEADDR failed, retrying in %dms (waited %dms/%dms)",
                 kSocketRetryIntervalMs, waitedMs, kSocketMaxTotalWaitMs);
            std::this_thread::sleep_for(std::chrono::milliseconds(kSocketRetryIntervalMs));
            waitedMs += kSocketRetryIntervalMs;
            continue;
        }
        LOGD("SO_REUSEADDR enabled on recieve_sockfd_");

        // SO_REUSEPORT is a Linux/BSD extension; winsock has no equivalent.
        int reuse = 1;
        (void)reuse;
#ifdef SO_REUSEPORT
        socket_wrapper_->setsockopt(recieve_sockfd_, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse));
#endif

        if (family_ == AF_INET) {
            sockaddr_in addr{};
            addr.sin_family = AF_INET;
            addr.sin_port = htons(remote_port_);
            addr.sin_addr.s_addr = htonl(INADDR_ANY);
            if (socket_wrapper_->bind(recieve_sockfd_, (sockaddr*)&addr, sizeof(addr)) < 0) {
                closeSocket();
                if (waitedMs >= kSocketMaxTotalWaitMs) {
                    LOGE("setupSocket: bind failed after %dms retry timeout", waitedMs);
                    return false;
                }
                LOGW("setupSocket: bind failed, retrying in %dms (waited %dms/%dms)",
                     kSocketRetryIntervalMs, waitedMs, kSocketMaxTotalWaitMs);
                std::this_thread::sleep_for(std::chrono::milliseconds(kSocketRetryIntervalMs));
                waitedMs += kSocketRetryIntervalMs;
                continue;
            }

            // Join multicast group.
            // ip_mreqn (with imr_ifindex) is a Linux extension and is absent from
            // winsock; use the portable ip_mreq there. On Linux we still try
            // ip_mreqn first and fall back to ip_mreq.
            bool joined = false;
#if !defined(_WIN32) || defined(__CYGWIN__)
            {
                ip_mreqn mreq{};
                inet_pton(AF_INET, group_addr_.c_str(), &mreq.imr_multiaddr);
                mreq.imr_address.s_addr = htonl(INADDR_ANY);
                mreq.imr_ifindex = 0; // kernel chooses
                joined = socket_wrapper_->setsockopt(recieve_sockfd_, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) >= 0;
            }
#endif
            if (!joined) {
                // Portable path (winsock, or systems without ip_mreqn).
                ip_mreq mreq2{};
                inet_pton(AF_INET, group_addr_.c_str(), &mreq2.imr_multiaddr);
                mreq2.imr_interface.s_addr = htonl(INADDR_ANY);
                if (socket_wrapper_->setsockopt(recieve_sockfd_, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq2, sizeof(mreq2)) < 0) {
                    closeSocket();
                    if (waitedMs >= kSocketMaxTotalWaitMs) {
                        LOGE("setupSocket: IP_ADD_MEMBERSHIP failed after %dms retry timeout", waitedMs);
                        return false;
                    }
                    LOGW("setupSocket: IP_ADD_MEMBERSHIP failed, retrying in %dms (waited %dms/%dms)",
                         kSocketRetryIntervalMs, waitedMs, kSocketMaxTotalWaitMs);
                    std::this_thread::sleep_for(std::chrono::milliseconds(kSocketRetryIntervalMs));
                    waitedMs += kSocketRetryIntervalMs;
                    continue;
                }
            }

            // Set TTL low by default
            int ttl = 1;
            socket_wrapper_->setsockopt(recieve_sockfd_, IPPROTO_IP, IP_MULTICAST_TTL, &ttl, sizeof(ttl));

            // Enable loopback so local sends can be received by this host
            unsigned char loop = 1;
            socket_wrapper_->setsockopt(recieve_sockfd_, IPPROTO_IP, IP_MULTICAST_LOOP, &loop, sizeof(loop));
        } else { // AF_INET6 (only other valid family)
            sockaddr_in6 addr6{};
            addr6.sin6_family = AF_INET6;
            addr6.sin6_port = htons(remote_port_);
            addr6.sin6_addr = in6addr_any;
            if (socket_wrapper_->bind(recieve_sockfd_, (sockaddr*)&addr6, sizeof(addr6)) < 0) {
                closeSocket();
                if (waitedMs >= kSocketMaxTotalWaitMs) {
                    LOGE("setupSocket: IPv6 bind failed after %dms retry timeout", waitedMs);
                    return false;
                }
                LOGW("setupSocket: IPv6 bind failed, retrying in %dms (waited %dms/%dms)",
                     kSocketRetryIntervalMs, waitedMs, kSocketMaxTotalWaitMs);
                std::this_thread::sleep_for(std::chrono::milliseconds(kSocketRetryIntervalMs));
                waitedMs += kSocketRetryIntervalMs;
                continue;
            }

            // Join IPv6 multicast group; optionally on a specific interface
            struct ipv6_mreq mreq6{};
            inet_pton(AF_INET6, group_addr_.c_str(), &mreq6.ipv6mr_multiaddr);
            unsigned int ifindex6 = 0;
            if (!local_addr_.empty()) {
                // If local_addr_ looks like an interface name, try if_nametoindex
                ifindex6 = socket_wrapper_->if_nametoindex(local_addr_.c_str());
                if (ifindex6 == 0) {
                    closeSocket();
                    if (waitedMs >= kSocketMaxTotalWaitMs) {
                        LOGE("setupSocket: if_nametoindex failed after %dms retry timeout for interface=%s",
                             waitedMs, local_addr_.c_str());
                        return false;
                    }
                    LOGW("setupSocket: if_nametoindex failed for interface=%s, retrying in %dms (waited %dms/%dms)",
                         local_addr_.c_str(), kSocketRetryIntervalMs, waitedMs, kSocketMaxTotalWaitMs);
                    std::this_thread::sleep_for(std::chrono::milliseconds(kSocketRetryIntervalMs));
                    waitedMs += kSocketRetryIntervalMs;
                    continue;
                }
            }
            mreq6.ipv6mr_interface = ifindex6; // 0 = kernel chooses
            if (socket_wrapper_->setsockopt(recieve_sockfd_, IPPROTO_IPV6, IPV6_JOIN_GROUP, &mreq6, sizeof(mreq6)) < 0) {
                closeSocket();
                if (waitedMs >= kSocketMaxTotalWaitMs) {
                    LOGE("setupSocket: IPV6_JOIN_GROUP failed after %dms retry timeout", waitedMs);
                    return false;
                }
                LOGW("setupSocket: IPV6_JOIN_GROUP failed, retrying in %dms (waited %dms/%dms)",
                     kSocketRetryIntervalMs, waitedMs, kSocketMaxTotalWaitMs);
                std::this_thread::sleep_for(std::chrono::milliseconds(kSocketRetryIntervalMs));
                waitedMs += kSocketRetryIntervalMs;
                continue;
            }

            // Set TTL low by default
            int hops = 1;
            socket_wrapper_->setsockopt(recieve_sockfd_, IPPROTO_IPV6, IPV6_MULTICAST_HOPS, &hops, sizeof(hops));

            // Enable loopback so local sends can be received by this host
            unsigned int loop = 1;
            socket_wrapper_->setsockopt(recieve_sockfd_, IPPROTO_IPV6, IP_MULTICAST_LOOP, &loop, sizeof(loop));

            // Set outgoing interface for multicast if specified
            if (ifindex6 != 0) {
                socket_wrapper_->setsockopt(recieve_sockfd_, IPPROTO_IPV6, IPV6_MULTICAST_IF, &ifindex6, sizeof(ifindex6));
            }
        }

        // Create separate send socket bound to local_port_ (optional: could reuse if ports equal)
        send_sockfd_ = socket_wrapper_->socket(family_, SOCK_DGRAM, 0);
        if (send_sockfd_ >= 0) {
            if (socket_wrapper_->setsockopt(send_sockfd_, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof(reuse_addr)) < 0) {
                int e = net_last_error();
                (void)e;
                LOGD("setsockopt SO_REUSEADDR failed on send_sockfd_ err=%d", e);
                socket_wrapper_->close(send_sockfd_);
                if (waitedMs >= kSocketMaxTotalWaitMs) {
                    LOGE("setupSocket: send socket SO_REUSEADDR failed after %dms retry timeout", waitedMs);
                    return false;
                }
                LOGW("setupSocket: send socket SO_REUSEADDR failed, retrying in %dms (waited %dms/%dms)",
                     kSocketRetryIntervalMs, waitedMs, kSocketMaxTotalWaitMs);
                std::this_thread::sleep_for(std::chrono::milliseconds(kSocketRetryIntervalMs));
                waitedMs += kSocketRetryIntervalMs;
                continue;
            }
            LOGD("SO_REUSEADDR enabled on send_sockfd_");
#ifdef SO_REUSEPORT
            socket_wrapper_->setsockopt(send_sockfd_, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse));
#endif
            if (family_ == AF_INET) {
                int send_ttl = 255;
                if (socket_wrapper_->setsockopt(send_sockfd_, IPPROTO_IP, IP_MULTICAST_TTL, &send_ttl, sizeof(send_ttl)) < 0) {
                    LOGD("Failed to set send socket IP_MULTICAST_TTL to 255");
                } else {
                    LOGD("Send  socket IPv4 multicast TTL set to 255");
                }

                unsigned char loopDisable = 0;
                socket_wrapper_->setsockopt(send_sockfd_, IPPROTO_IP, IP_MULTICAST_LOOP, &loopDisable, sizeof(loopDisable));
                // SO_PRIORITY (Linux VLAN egress priority) has no winsock equivalent.
#ifdef SO_PRIORITY
                socket_wrapper_->setsockopt(send_sockfd_, SOL_SOCKET, SO_PRIORITY, &vlan_pro_, sizeof(vlan_pro_));
#endif
                sockaddr_in saddr{};
                saddr.sin_family = AF_INET;
                saddr.sin_port = htons(local_port_);
                saddr.sin_addr.s_addr = htonl(INADDR_ANY);
                if (socket_wrapper_->bind(send_sockfd_, (sockaddr*)&saddr, sizeof(saddr)) < 0) {
                    // If binding fails, we still can try sending without explicit bind.
                    // Close and mark invalid to fall back.
                    socket_wrapper_->close(send_sockfd_);
                    send_sockfd_ = -1;
                }
            } else { // IPv6
                int send_hops = 255;
                if (socket_wrapper_->setsockopt(send_sockfd_, IPPROTO_IPV6, IPV6_MULTICAST_HOPS, &send_hops, sizeof(send_hops)) < 0) {
                    LOGD("Failed to set send socket IPV6_MULTICAST_HOPS to 255");
                } else {
                    LOGD("Send socket IPv6 multicast hop limit set to 255");
                }
                unsigned int loopDisable = 0;
                socket_wrapper_->setsockopt(send_sockfd_, IPPROTO_IPV6, IP_MULTICAST_LOOP, &loopDisable, sizeof(loopDisable));
                // SO_PRIORITY (Linux VLAN egress priority) has no winsock equivalent.
#ifdef SO_PRIORITY
                socket_wrapper_->setsockopt(send_sockfd_, SOL_SOCKET, SO_PRIORITY, &vlan_pro_, sizeof(vlan_pro_));
#endif
                sockaddr_in6 saddr6{};
                saddr6.sin6_family = AF_INET6;
                saddr6.sin6_port = htons(local_port_);
                unsigned int ifindex6 = 0;
                ifindex6 = socket_wrapper_->if_nametoindex(local_addr_.c_str());

                if (socket_wrapper_->bind(send_sockfd_, (sockaddr*)&saddr6, sizeof(saddr6)) < 0) {
                    LOGD("Failed to bind IPv6 send socket to %s:%u", local_addr_.c_str(), local_port_);
                    socket_wrapper_->close(send_sockfd_);
                    send_sockfd_ = -1;
                } else if (ifindex6 != 0) {
                    LOGD("Setting IPv6 multicast interface index to %u", ifindex6);

                    socket_wrapper_->setsockopt(send_sockfd_, IPPROTO_IPV6, IPV6_MULTICAST_IF, &ifindex6, sizeof(ifindex6));
                }
            }
        }
        LOGD("setupSocket success group=%s recvFd=%d sendFd=%d vlanPro=%u waitedMs=%d",
             group_addr_.c_str(), recieve_sockfd_, send_sockfd_, vlan_pro_, waitedMs);
        return true;
    }
}
#endif

/**
 * @brief Close and clean up all sockets.
 *
 * In multi-interface mode each recv fd leaves the multicast group using the
 * ifindex it was joined with, preventing kernel multicast table leaks.
 */
#ifdef MQB_NETWORK_CONFIG_ENABLED
void MulticastSocket::closeSocket() {
    // Multi-interface path
    for (const auto& p : recv_fds_) {
        int fd = p.first;
        unsigned int ifindex = p.second;
        if (fd < 0) continue;
        struct ipv6_mreq mreq6{};
        inet_pton(AF_INET6, group_addr_.c_str(), &mreq6.ipv6mr_multiaddr);
        mreq6.ipv6mr_interface = ifindex;
        socket_wrapper_->setsockopt(fd, IPPROTO_IPV6, IPV6_LEAVE_GROUP, &mreq6, sizeof(mreq6));
        socket_wrapper_->close(fd);
    }
    recv_fds_.clear();

    for (const auto& p : send_fds_) {
        if (p.first >= 0) socket_wrapper_->close(p.first);
    }
    send_fds_.clear();

    // Legacy path
    if (recieve_sockfd_ >= 0) {
        if (family_ == AF_INET) {
            ip_mreqn mreq{};
            inet_pton(AF_INET, group_addr_.c_str(), &mreq.imr_multiaddr);
            mreq.imr_address.s_addr = htonl(INADDR_ANY);
            mreq.imr_ifindex = 0;
            socket_wrapper_->setsockopt(recieve_sockfd_, IPPROTO_IP, IP_DROP_MEMBERSHIP, &mreq, sizeof(mreq));
            ip_mreq mreq2{};
            memcpy(&mreq2.imr_multiaddr, &mreq.imr_multiaddr, sizeof(in_addr));
            mreq2.imr_interface.s_addr = htonl(INADDR_ANY);
            socket_wrapper_->setsockopt(recieve_sockfd_, IPPROTO_IP, IP_DROP_MEMBERSHIP, &mreq2, sizeof(mreq2));
        } else {
            struct ipv6_mreq mreq6{};
            inet_pton(AF_INET6, group_addr_.c_str(), &mreq6.ipv6mr_multiaddr);
            mreq6.ipv6mr_interface = 0;
            socket_wrapper_->setsockopt(recieve_sockfd_, IPPROTO_IPV6, IPV6_LEAVE_GROUP, &mreq6, sizeof(mreq6));
        }
        socket_wrapper_->close(recieve_sockfd_);
        recieve_sockfd_ = -1;
    }
    if (send_sockfd_ >= 0) {
        socket_wrapper_->close(send_sockfd_);
        send_sockfd_ = -1;
    }
}
#else
void MulticastSocket::closeSocket() {
    if (recieve_sockfd_ >= 0) {
    if (family_ == AF_INET) {
            // Try to drop membership.
            // ip_mreqn (imr_ifindex) is Linux-only; use ip_mreq on winsock.
#if !defined(_WIN32) || defined(__CYGWIN__)
            ip_mreqn mreq{};
            inet_pton(AF_INET, group_addr_.c_str(), &mreq.imr_multiaddr);
            mreq.imr_address.s_addr = htonl(INADDR_ANY);
            mreq.imr_ifindex = 0;
            socket_wrapper_->setsockopt(recieve_sockfd_, IPPROTO_IP, IP_DROP_MEMBERSHIP, &mreq, sizeof(mreq));
#endif
            // Best-effort fallback (portable ip_mreq).
            ip_mreq mreq2{};
            inet_pton(AF_INET, group_addr_.c_str(), &mreq2.imr_multiaddr);
            mreq2.imr_interface.s_addr = htonl(INADDR_ANY);
            socket_wrapper_->setsockopt(recieve_sockfd_, IPPROTO_IP, IP_DROP_MEMBERSHIP, &mreq2, sizeof(mreq2));
    } else { // AF_INET6
            struct ipv6_mreq mreq6{};
            inet_pton(AF_INET6, group_addr_.c_str(), &mreq6.ipv6mr_multiaddr);
            mreq6.ipv6mr_interface = 0;
            socket_wrapper_->setsockopt(recieve_sockfd_, IPPROTO_IPV6, IPV6_LEAVE_GROUP, &mreq6, sizeof(mreq6));
        }
        socket_wrapper_->close(recieve_sockfd_);
        recieve_sockfd_ = -1;
    }
    if (send_sockfd_ >= 0) {
        socket_wrapper_->close(send_sockfd_);
        send_sockfd_ = -1;
    }
}
#endif

/**
 * @brief Set the local bind address for the multicast socket.
 *
 * This function sets the local address (interface name or IP address)
 * to be used for binding the multicast socket.
 *
 * @param addr The local address (interface name or IP address).
 */
#ifdef MQB_NETWORK_CONFIG_ENABLED
void MulticastSocket::setLocalAddress(const std::string& addr) {
    LOGI("MulticastSocket setLocalAddress %s", addr.c_str());
    local_addrs_ = splitInterfaces(addr);
}
#else
void MulticastSocket::setLocalAddress(const std::string& addr) {
    LOGI("MulticastSocket setLocalAddress %s", addr.c_str());
    local_addr_ = addr;
}
#endif
