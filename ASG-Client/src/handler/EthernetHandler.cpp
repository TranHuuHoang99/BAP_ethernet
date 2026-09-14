#include "EthernetHandler.hpp"
#include <iomanip>

EthernetHandler::EthernetHandler(const std::string server_ip,
                                 const uint16_t port,
                                 const uint16_t dpu_sz,
                                 const uint16_t header_sz)
                                : m_client_fd(-1),
                                  m_server_len(0),
                                  m_ret_initSocket(-1),
                                  m_serverIp(server_ip),
                                  m_port(port),
                                  m_isSocket_start(false),
                                  m_bap_dpu_sz(dpu_sz),
                                  m_bap_header_sz(header_sz)
{
    std::cout << "[ETHERNET_HANDLER] Start ethernet handler !!!\n";
    m_ret_initSocket = _initUdpSocket();

    try {
        m_buffer.resize(m_bap_dpu_sz + m_bap_header_sz);
    } catch (std::length_error& err) {
        m_ret_initSocket = -1;
        std::cerr << "[ETHERNET_HANDLER] failed to init event buffer, err: " << err.what() << '\n';
    } catch (std::bad_alloc& err) {
        m_ret_initSocket = -1;
        std::cerr << "[ETHERNET_HANDLER] failed to init event buffer, err: " << err.what() << '\n';
    }
}

EthernetHandler::~EthernetHandler(void)
{
    std::cout << "[ETHERNET_HANDLER] Destroy ethernet handler !!!\n";
    m_isSocket_start = false;
#if defined(__CYGWIN__) || defined(WIN32)
    closesocket(m_client_fd);
#else
    close(m_client_fd);
#endif // defined(__CYGWIN__) || defined(WIN32)
    m_ethernet_listener.join();
}

void EthernetHandler::startEthernetHandler(std::function<void(const uint8_t*)> callback)
{
    std::cout << "[ETHERNET_HANDLER] Start !!!\n";
    if (m_ethernet_listener.joinable()) {
        std::cout << "[ETHERNET_HANDLER] current thread is still running !!!\n";
        m_ethernet_listener.join();
    }
    m_ethernet_listener = std::thread(&EthernetHandler::_handleUdpTraffic, this, callback);
}

int32_t EthernetHandler::_initUdpSocket(void)
{
    std::cout << "[ETHERNET_HANDLER][INIT] init socket !!!\n";
    m_server_len = sizeof(m_server_addr);
#if defined(__CYGWIN__) || defined(WIN32)
    WSADATA wsaData;
    const int32_t ret_WSA = WSAStartup(0x202, &wsaData);
    if (ret_WSA != 0) {
        std::cerr << "[ETHERNET_HANDLER][ERROR] Failed to create socket file descriptor, err :"
                  <<  ret_WSA << '\n';
        return -1;
    }
#endif // defined(__CYGWIN__) || defined(WIN32)

    // Init ethernet connection
    // configure destination server address
    memset(&m_server_addr, 0, m_server_len);
    m_server_addr.sin_family = AF_INET;
    m_server_addr.sin_port = htons(m_port);
    m_server_addr.sin_addr.s_addr = inet_addr(m_serverIp.c_str());

    m_client_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (m_client_fd < 0) {
        std::cerr << "[ETHERNET_HANDLER][ERROR] Failed to create socket file descriptor, err :"
                  << m_client_fd << '\n';
        return -1;
    }
    std::cout << "[ETHERNET_HANDLER] Success to create socket file descriptor\n";

    // connect to server
    const int32_t ret_connect = connect(m_client_fd,
                                        (struct sockaddr*)&m_server_addr,
                                        m_server_len);
    if (ret_connect < 0) {
        std::cerr << "[ETHERNET_HANDLER][ERROR] Failed to connect to server, error : "
                  << ret_connect << '\n';
        return -1;
    }
    std::cout << "[ETHERNET_HANDLER] Success to connect to server\n";

    return 0;
}

void EthernetHandler::_handleUdpTraffic(std::function<void(const uint8_t*)> callback)
{
    if (m_ret_initSocket < 0) {
        std::cerr << "[ETHERNET_HANDLER] init socket failed can not start socket !\n";
        m_isSocket_start = false;
        return;
    }

    std::cout << "[ETHERNET_HANDLER] start socket !!!\n";
    m_isSocket_start = true;
    while (m_isSocket_start) {
        const int32_t rec_code = recv(m_client_fd,
#if defined(__CYGWIN__) || defined(WIN32)
                                      (char*)&m_buffer[0], // win32sock use char
#else
                                      m_buffer, // linux use uint8_t
#endif // #if defined(__CYGWIN__) || defined(WIN32)
                                      sizeof(m_buffer),
                                      0);
        if (rec_code < 0) {
            std::cerr << "[ETHERNET_HANDLER][ERROR] Failed to receive message from server!!!\n";
            continue;
        }

#if defined(__ASG_DEBUG_MODE__)
        std::cout << "[ETHERNET_HANDLER] Success to receive message from server\n";
        const int32_t msg_len = m_buffer[7];
        std::cout << "[ETHERNET_HANDLER][RECEIVE] : ";
        for (int32_t i = 0; i < (msg_len + m_bap_header_sz); i++) {
            std::cout << std::hex << std::setw(2) << std::setfill('0')
                      << (int32_t)(m_buffer[i]) << " ";
        }
        std::cout << '\n';
#endif // defined(__ASG_DEBUG_MODE__)

        callback(reinterpret_cast<const uint8_t*>(&m_buffer[0]));
    }
}

int32_t EthernetHandler::deliverEthernetPackage(const char* apData, const uint16_t au16MsgLength)
{
    std::cout << "[ETHERNET_HANDLER] Delivery ethernet packages\n";
    const int32_t ret = sendto(m_client_fd,
                               apData,
                               au16MsgLength,
                               0,
                               (struct sockaddr*)&m_server_addr,
                               m_server_len);
    return ret;
}
