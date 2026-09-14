#ifndef ISOCKETWRAPPER_H
#define ISOCKETWRAPPER_H

// ---------------------------------------------------------------------------
// Platform socket headers / types.
// Windows (winsock) and POSIX expose the same conceptual API through different
// headers and type names. The interface below is written in POSIX terms; the
// Windows branch supplies the POSIX typedefs winsock is missing.
// ---------------------------------------------------------------------------
#if defined(_WIN32) || defined(__CYGWIN__)
  #ifndef _WIN32_WINNT
    #define _WIN32_WINNT 0x0601   // Windows 7: required for WSAPoll / inet_pton
  #endif
  #ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
  #endif
  #include <winsock2.h>
  #include <ws2tcpip.h>
  #include <basetsd.h>
  #include <cstddef>
  #if defined(_WIN32) && !defined(__CYGWIN__)
    // Winsock does not define these POSIX typedefs used by this interface.
    typedef ULONG nfds_t;             // WSAPoll takes a ULONG fd count
    #ifndef _SSIZE_T_DEFINED
      #define _SSIZE_T_DEFINED
      typedef SSIZE_T ssize_t;
    #endif
  #endif
#else
  #include <sys/socket.h>
  #include <poll.h>
  #include <cstddef>
  #include <sys/types.h>
#endif

// Abstract interface for socket system calls to enable dependency injection and mocking.
class ISocketWrapper {
public:
    virtual ~ISocketWrapper() = default;
    virtual int socket(int domain, int type, int protocol) = 0;
    virtual int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen) = 0;
    virtual int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) = 0;
    virtual ssize_t sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen) = 0;
    // Use standard nfds_t from <poll.h> (POSIX) / typedef'd above (Windows)
    virtual int poll(struct pollfd *fds, nfds_t nfds, int timeout) = 0;
    virtual ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen) = 0;
    virtual int close(int fd) = 0;
    virtual int getsockname(int sockfd, struct sockaddr *addr, socklen_t *addrlen) = 0;
    virtual unsigned int if_nametoindex(const char* ifname) = 0;
};

#endif // ISOCKETWRAPPER_H
