#ifndef __ETHERNET_HANDLER__
#define __ETHERNET_HANDLER__

#if defined(__CYGWIN__) || defined(WIN32)
	#include <winsock2.h>
    #include <ws2tcpip.h>
#else
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <net/if.h>
	#include <unistd.h>
	#include <netdb.h>
	#include <errno.h>
    #include <arpa/inet.h>
    #include <unistd.h>
#endif

#include <iostream>
#include <stdio.h>
#include <string>
#include <memory>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <functional>

class EthernetHandler {
public:
    EthernetHandler(const std::string server_ip,
                    const uint16_t port,
                    const uint16_t dpu_sz,
                    const uint16_t header_sz);
    ~EthernetHandler(void);

    void startEthernetHandler(std::function<void(const uint8_t*)> callback);
#if defined(__CYGWIN__) || defined(WIN32)
    int32_t deliverEthernetPackage(const char* apData, const uint16_t au16MsgLength);
#else
    int32_t deliverEthernetPackage(const unsigned char* apData, const uint16_t au16MsgLength);
#endif // #if defined(__CYGWIN__) || defined(WIN32)
private:
    int32_t m_client_fd;
    int32_t m_ret_initSocket;
    struct sockaddr_in m_server_addr;
    socklen_t m_server_len;
    std::string m_serverIp;
    uint16_t m_port;
    bool m_isSocket_start;
    uint32_t m_bap_header_sz;
    uint32_t m_bap_dpu_sz;
    std::thread m_ethernet_listener;
#if defined(__CYGWIN__) || defined(WIN32)
    std::vector<char> m_buffer;
#else
    std::vector<uint8_t> m_buffer;
#endif // #if defined(__CYGWIN__) || defined(WIN32)

    int32_t _initUdpSocket(void);
    void _handleUdpTraffic(std::function<void(const uint8_t*)> callback);
};

#endif // __ETHERNET_HANDLER__
