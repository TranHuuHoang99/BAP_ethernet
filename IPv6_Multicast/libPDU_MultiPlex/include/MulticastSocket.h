#ifndef __MULTICASTSOCKET_H_
#define __MULTICASTSOCKET_H_

#include <cstdint>
#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>
#include <memory>

#ifdef MQB_NETWORK_CONFIG_ENABLED
#include <chrono>
#include <deque>
#include <utility>
#endif

#include "pdu.h"
// ISocketWrapper.h pulls in the correct platform socket headers
// (winsock2/ws2tcpip on Windows, sys/socket.h + poll.h + netinet/in.h on POSIX)
// and the socklen_t / nfds_t / pollfd definitions used below.
#include "ISocketWrapper.h"

class MulticastSocket {
public:
    using RecvCallback = std::function<void(const std::vector<PDU>&)>;

    // New ctor: specify distinct local bind port and remote destination port
    MulticastSocket(const std::string& group_addr, uint16_t local_port, uint16_t remote_port, uint32_t vlan_pro=0);

    // Constructor for dependency injection with explicit remote port
    MulticastSocket(const std::string& group_addr, uint16_t local_port, uint16_t remote_port, std::shared_ptr<ISocketWrapper> socket_wrapper, uint32_t vlan_pro=0);
    
    ~MulticastSocket();

    // Start background threads for receiving and sending.
    bool start();
    // Stop background threads and close the socket.
    void stop();

    // Register a callback to receive parsed PDUs.
    void setReceiveCallback(RecvCallback cb);

    // Optional: set local interface or IP address used for multicast.
    void setLocalAddress(const std::string& addr);

    // Enqueue PDUs to be serialized and sent as a single datagram.
    void sendPDUs(const std::vector<PDU>& pdus);

    // Serialize a vector of PDUs back into a single datagram.
    static std::vector<uint8_t> serializePDUs(const std::vector<PDU>& pdus);

    // Friend accessor for unit tests; avoids exposing internal seams publicly.
    friend struct MulticastSocketTestAccessor;

    #ifdef UNIT_TEST
    bool isforUnitTest = false;
    void setUnitTest(bool isunitTest) { isforUnitTest = isunitTest; }
    #endif

private:
    // Background loops
    void recvLoop();
    void sendLoop();

    // Socket helpers
    bool setupSocket();
    void closeSocket();
#ifdef MQB_NETWORK_CONFIG_ENABLED
    // Split a comma-separated interface list into individual names.
    static std::vector<std::string> splitInterfaces(const std::string& s);
    // FNV-1a 64-bit hash for duplicate-suppression in recvLoop.
    static uint64_t fnv1a64(const uint8_t* data, size_t len);
#endif

private:
#ifdef MQB_NETWORK_CONFIG_ENABLED
    // Per-interface fd pairs: first = fd, second = ifindex (needed for LEAVE_GROUP / IF binding).
    std::vector<std::pair<int, unsigned int>> recv_fds_; // one entry per interface for receiving
    std::vector<std::pair<int, unsigned int>> send_fds_; // one entry per interface for sending
#endif
    // Legacy single-fd fallback (used when local_addrs_ is empty / IPv4).
    int recieve_sockfd_ = -1;
    int send_sockfd_    = -1;

    std::string group_addr_;
    uint16_t local_port_ = 0;   // local bind port for outbound traffic
    uint16_t remote_port_ = 0;  // multicast group destination port
    uint32_t vlan_pro_ = 0;
#ifdef MQB_NETWORK_CONFIG_ENABLED
    std::vector<std::string> local_addrs_; // parsed interface list
#else
    std::string local_addr_;
#endif
    int family_ = AF_INET; // AF_INET or AF_INET6

#ifdef MQB_NETWORK_CONFIG_ENABLED
    // Short-window duplicate suppression for multi-interface receive.
    // Stores (hash, arrival_time) of recently received datagrams.
    std::deque<std::pair<uint64_t, std::chrono::steady_clock::time_point>> recent_hashes_;
    std::mutex hash_mutex_;
#endif
    struct sockaddr_storage group_sockaddr_{};
    socklen_t group_socklen_ = 0;

    std::thread recv_thread_;
    std::thread send_thread_;

    std::queue<std::vector<PDU>> send_queue_;
    RecvCallback recv_callback_;

    // Internals
    std::atomic<bool> running_{false};
    std::mutex queue_mutex_;
    std::condition_variable queue_cv_;
    
    // Dependency injection for socket operations
    std::shared_ptr<ISocketWrapper> socket_wrapper_;
};

#endif // __MULTICASTSOCKET_H_
