#ifndef PRODUCTIONSOCKETWRAPPER_H
#define PRODUCTIONSOCKETWRAPPER_H

#include "ISocketWrapper.h"

#if defined(_WIN32) && !defined(__CYGWIN__)
  #include <iphlpapi.h>   // if_nametoindex
  // winsock uses SOCKET (an unsigned handle) and different argument types than
  // POSIX. This interface models fds as int, which is safe for the fd values
  // Windows hands out in practice; the casts below bridge the signatures.

// Ensures WSAStartup() has been called once before any socket call and
// WSACleanup() runs at process exit. Winsock requires this initialization;
// POSIX needs no equivalent. Constructing a ProductionSocketWrapper (which
// happens before any socket is created) triggers it via the static below.
class WinsockInitializer {
public:
    WinsockInitializer() { WSADATA wsa; ::WSAStartup(MAKEWORD(2, 2), &wsa); }
    ~WinsockInitializer() { ::WSACleanup(); }
};
#else
  #include <net/if.h>
  #include <unistd.h>
#endif

// Production implementation of ISocketWrapper that calls the real system functions.
class ProductionSocketWrapper : public ISocketWrapper {
public:
#if defined(_WIN32) && !defined(__CYGWIN__)
    ProductionSocketWrapper() {
        // Function-local static: WSAStartup runs exactly once, thread-safely,
        // the first time any ProductionSocketWrapper is constructed.
        static WinsockInitializer winsock_init;
    }
#endif
#if defined(_WIN32) && !defined(__CYGWIN__)
    int socket(int domain, int type, int protocol) override {
        return static_cast<int>(::socket(domain, type, protocol));
    }
    int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) override {
        return ::bind(static_cast<SOCKET>(sockfd), addr, addrlen);
    }
    int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen) override {
        return ::setsockopt(static_cast<SOCKET>(sockfd), level, optname,
                            reinterpret_cast<const char*>(optval), optlen);
    }
    int poll(struct pollfd *fds, nfds_t nfds, int timeout) override {
        return ::WSAPoll(fds, nfds, timeout);
    }
    ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen) override {
        return ::recvfrom(static_cast<SOCKET>(sockfd), reinterpret_cast<char*>(buf),
                          static_cast<int>(len), flags, src_addr, addrlen);
    }
    ssize_t sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen) override {
        return ::sendto(static_cast<SOCKET>(sockfd), reinterpret_cast<const char*>(buf),
                        static_cast<int>(len), flags, dest_addr, addrlen);
    }
    int close(int fd) override { return ::closesocket(static_cast<SOCKET>(fd)); }
    int getsockname(int sockfd, struct sockaddr* addr, socklen_t* addrlen) override {
        return ::getsockname(static_cast<SOCKET>(sockfd), addr, addrlen);
    }
    unsigned int if_nametoindex(const char* ifname) override { return ::if_nametoindex(ifname); }
#else
    int socket(int domain, int type, int protocol) override { return ::socket(domain, type, protocol); }
    int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) override { return ::bind(sockfd, addr, addrlen); }
    int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen) override { return ::setsockopt(sockfd, level, optname, optval, optlen); }
    int poll(struct pollfd *fds, nfds_t nfds, int timeout) override { return ::poll(fds, nfds, timeout); }
    ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen) override { return ::recvfrom(sockfd, buf, len, flags, src_addr, addrlen); }
    ssize_t sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen) override { return ::sendto(sockfd, buf, len, flags, dest_addr, addrlen); }
    int close(int fd) override { return ::close(fd); }
    int getsockname(int sockfd, struct sockaddr* addr, socklen_t* addrlen) override { return ::getsockname(sockfd, addr, addrlen); }
    unsigned int if_nametoindex(const char* ifname) override { return ::if_nametoindex(ifname); }
#endif
};

#endif // PRODUCTIONSOCKETWRAPPER_H
