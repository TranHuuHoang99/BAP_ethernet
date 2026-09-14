#include "FSGManager.hpp"
#include <iomanip>
#include <vector>
#include <cstring>

#define BAP_USES_NOT_OWN_UINT32
#define PORT 2007

char client_ip[INET_ADDRSTRLEN];

extern "C"
{
void disableint(uint8_t *apu8SaveValue)
{

}

void restoreint(uint8_t au8RestoreValue)
{

}

bool_t BAP_Transmit_TxData(BapCanInterfaceChannel_t aCanInterfaceChannel,
						   BapCanMsgId_t aPduId,
						   ptr_t apData,
						   uint16_t au16MsgLength)
{
    const bool_t ret = FSGManager::instance()->transmitTxData(apData, au16MsgLength);
    return ret;
}

} // extern "C"

FSGManager::~FSGManager(void)
{
    std::wcout << "[SERVER] FSGManager has been stopped\n";
    stop();
}

std::shared_ptr<FSGManager> FSGManager::instance(void)
{
    static std::shared_ptr<FSGManager> _instance = std::make_shared<FSGManager>(FSGManagerToken{});
    return _instance;
}

void FSGManager::acknowledge(const lsgId_t aLsgId,
                             const fctId_t aFctId,
                             const BapAcknowledge_et aeAcknowledge)
{

}

void FSGManager::indicationVoid(const lsgId_t aLsgId,
                                const fctId_t aFctId,
                                const enum BapIndication_t aeIndication)
{

}

void FSGManager::indicationInt8(const lsgId_t aLsgId,
                                const fctId_t aFctId,
                                const enum BapIndication_t aeIndication,
                                const uint8_t au8Value)
{

}

void FSGManager::indicationInt16(const lsgId_t aLsgId,
                                 fctId_t aFctId,
                                 enum BapIndication_t aeIndication,
                                 uint16_t au16Value)
{

}

void FSGManager::indicationInt32(const lsgId_t aLsgId,
                                 fctId_t aFctId,
                                 enum BapIndication_t aeIndication,
                                 uint32_t au32Value)
{

}

void FSGManager::indicationByteSequence(const lsgId_t aLsgId,
                                        const fctId_t aFctId,
                                        const enum BapIndication_t aeIndication,
                                        const volatile uint8_t apValue[],
                                        const uint32_t au32Length)
{
    std::cout << "[SERVER] aLsgId : " << static_cast<int32_t>(aLsgId) << ", "
              << "aFctId: " << static_cast<int32_t>(aFctId) << ", "
              << "aeIndication: " << static_cast<int32_t>(aeIndication) << '\n';
    std::cout << "[SERVER][data] : ";
    for (int32_t i = 0; i < (int32_t)au32Length; i++) {
        std::cout << std::hex << std::setw(2) << std::setfill('0')
                    << (int32_t)(apValue[i]) << " ";
    }
    std::cout << '\n';

    if (aLsgId == lsgId_t::BapLsg_ClimateZone &&
        aFctId == fctId_t::BapFct_ClimateZone_ZL_Temperature)
    {
        if (aeIndication == BapIndication_t::BapInd_DataSetGet) {
            std::vector<uint8_t> response(
                const_cast<const uint8_t*>(apValue),
                const_cast<const uint8_t*>(apValue) + au32Length
            );
            BAP_RequestByteSequence(aLsgId, aFctId,
                                    BapRequest_t::BapReq_Data,
                                    response.data(),
                                    6);
        } else if (aeIndication == BapIndication_t::BapInd_DataGet) {
            std::vector<uint8_t> response(6, 0xFFu);
            BAP_RequestByteSequence(aLsgId, aFctId,
                                    BapRequest_t::BapReq_Data,
                                    response.data(),
                                    6);
        }
    }

    if (aLsgId == lsgId_t::BapLsg_ClimateMaster &&
        aFctId == fctId_t::BapFct_ClimateMaster_AC)
    {
        if (aeIndication == BapIndication_t::BapInd_DataSetGet) {
            std::vector<uint8_t> response(
                const_cast<const uint8_t*>(apValue),
                const_cast<const uint8_t*>(apValue) + au32Length
            );
            BAP_RequestByteSequence(aLsgId, aFctId,
                                    BapRequest_t::BapReq_Data,
                                    response.data(),
                                    2u);
        } else if (aeIndication == BapIndication_t::BapInd_DataGet) {
            std::vector<uint8_t> response(6, 0xFFu);
            BAP_RequestByteSequence(aLsgId, aFctId,
                                    BapRequest_t::BapReq_Data,
                                    response.data(),
                                    2u);
        }
    }
}

void FSGManager::indicationError(const lsgId_t aLsgId,
                                 const fctId_t aFctId,
                                 const enum BapError_t aeErrorCode)
{

}

enum BapError_t FSGManager::sendDebugInfo(DBGVAR const uint8_t pDebugInfo[8])
{
    return BapError_t::BapErr_OK;
}

int32_t FSGManager::init(void)
{
    std::cout << "[SERVER] show default value\n";
    std::cout << "=========================================================================\n";
    std::cout << "initial left zone's temperature : " << (int32_t)m_leftZoneTemp << '\n';
    std::cout << "initial right zone's temperature : " << (int32_t)m_rightZoneTemp << '\n';
    std::cout << "=========================================================================\n";
    std::cout << "[SERVER][INIT] Init FSG Server!!!\n";
    std::cout << "[SERVER][INIT] Init FSG Server!!!\n";
    m_client_len = sizeof(m_client_addr);
#if defined(__CYGWIN__) || defined(WIN32)
    WSADATA wsaData;
    const int32_t ret_WSA = WSAStartup(0x202, &wsaData);
    if (ret_WSA != 0) {
        std::cerr << "[SERVER][ERROR] Failed to create socket file descriptor, err :"
                  <<  ret_WSA << '\n';
        return -1;
    }
#endif // defined(__CYGWIN__) || defined(WIN32)

    // Init ethernet connection
    // configure destination server address
    memset(&m_client_addr, 0, m_client_len);
    m_client_addr.sin_family = AF_INET;
    m_client_addr.sin_addr.s_addr = INADDR_ANY;
    m_client_addr.sin_port = htons(PORT);

    m_server_fd = socket(AF_INET, SOCK_DGRAM, 0);
#if defined(__CYGWIN__) || defined(WIN32)
    if (m_server_fd == INVALID_SOCKET)
#else
    if (m_server_fd < 0)
#endif // defined(__CYGWIN__) || defined(WIN32)
    {
        std::cerr << "[SERVER][ERROR] Failed to create socket file descriptor, err :"
                  << m_server_fd << '\n';
        return -1;
    }
    std::cout << "[SERVER] Success to create socket file descriptor\n";

    // connect to server
    const int32_t ret_connect = bind(m_server_fd,
                                     (struct sockaddr*)&m_client_addr,
                                     m_client_len);
    if (ret_connect < 0) {
        std::cerr << "[SERVER][ERROR] Failed to connect to client, error : " << ret_connect << '\n';
        return -1;
    }
    std::cout << "[SERVER] Success to connect to client\n";

    // Init BAP
    const int32_t ret_init_lsg = _initLsg();
    if (ret_init_lsg != 0) return -1;

    return 0;
}

void FSGManager::start(void)
{
    std::cout << "[SERVER][START] Start FSG server !!!\n";
    m_startEventListener = true;

    // start event listener
    m_fsg_listener = std::thread(&FSGManager::_ethernetEventListener, this);

    // start BAP cycle
    const int32_t ret_start_lsg = _startLsg();
    if (ret_start_lsg != 0) return;

    while (m_startEventListener) {
        BAP_Task();
#if defined(__CYGWIN__) || defined(WIN32)
        Sleep(1);
#else
        usleep(1);
#endif // defined(__CYGWIN__) || defined(WIN32)
    }

    return;
}

int32_t FSGManager::stop(void)
{
    std::cout << "[SERVER][STOP] stop FSG server !!!\n";
    if (m_fsg_listener.joinable()) {
        m_fsg_listener.join();
    }
#if defined(__CYGWIN__) || defined(WIN32)
    if (m_server_fd != (int32_t)INVALID_SOCKET) {
        closesocket(m_server_fd);
        m_server_fd = (int32_t)INVALID_SOCKET;
    }
#else
    if (m_server_fd >= 0) {
        close(m_server_fd);
        m_server_fd = -1;
    }
#endif // defined(__CYGWIN__) || defined(WIN32)
    return 0;
}

void FSGManager::_ethernetEventListener(void)
{
    while (m_startEventListener) {
        socklen_t client_len = sizeof(m_client_addr);
        const int32_t rec_code = recvfrom(m_server_fd,
                                          (char*)m_buffer, // win32sock force to use char not uint8_t
                                          sizeof(m_buffer),
                                          0,
                                          (struct sockaddr*)&m_client_addr,
                                          &client_len);
        if (rec_code < 0) {
            std::cerr << "[SERVER][ERROR] Failed to receive message from client!!!\n";
            continue;
        }

        m_client_len = client_len;
        m_client_connected = true;

        inet_ntop(AF_INET, &m_client_addr.sin_addr, client_ip, sizeof(client_ip));
        std::cout << "[SERVER] Server receive msg from client IP : "
                  << client_ip << ", on port : "
                  << ntohs(m_client_addr.sin_port) << '\n';

        const int32_t msg_len = m_buffer[7];
        std::cout << "[SERVER][RECEIVE] : ";
        for (int32_t i = 0; i < (msg_len + BAP_SOAD_HEADER_SIZE); i++) {
            std::cout << std::hex << std::setw(2) << std::setfill('0')
                      << (int32_t)(m_buffer[i]) << " ";
        }
        std::cout << '\n';

        BAP_RxIndication(m_buffer);
    }
}

void FSGManager::_waitBAPTasks(int32_t time_delay)
{
    while (time_delay--) {
        BAP_Task();
#if defined(__CYGWIN__) || defined(WIN32)
        Sleep(1);
#else
        usleep(1);
#endif // defined(__CYGWIN__) || defined(WIN32)
    }
}

bool_t FSGManager::transmitTxData(ptr_t apData, const uint16_t au16MsgLength)
{
    if (!m_client_connected) {
        return BAP_FALSE;
    }

    const int32_t ret_send = sendto(m_server_fd,
                                    (const char*)apData,
                                    au16MsgLength,
                                    0,
                                    (struct sockaddr*)&m_client_addr,
                                    m_client_len);
    if (ret_send < 0) {
        std::cerr << "[SERVER] Failed to send data !!!\n";
        return BAP_FALSE;
    }

#if defined(__FSG_DEBUG_MODE__)
    std::cout << "[SERVER] Success to send data\n";
    std::cout << "[SERVER][SEND] : ";
    for (int32_t i = 0; i < (int32_t)au16MsgLength; i++) {
        std::cout << std::hex << std::setw(2) << std::setfill('0')
                    << (int32_t)(apData[i]) << " ";
    }
    std::cout << '\n';
#endif // defined(__FSG_DEBUG_MODE__)

    return BAP_TRUE;
}

int32_t FSGManager::_initAllSendBuffers(const lsgId_t aLsgId)
{
    BapLsgRomRow_pot lsgRomRow = BAP_GetLsgRomRow(aLsgId);
    if (lsgRomRow == NULL) {
        std::cout << "[SERVER] lsg not found";
        return -1;
    }

    const int32_t fct_numb = lsgRomRow->u8FctRomTableSize;
    // in FSG xml some function we did not define but leave it default so
    // the index will return the order of the first function we define our own in FSG xml file
    const int32_t fct_index = lsgRomRow->u16FctRomIndex;
    std::cout << "[SERVER] number of function : " << fct_numb << '\n';
    std::cout << "[SERVER] index of start function : " << fct_index << '\n';

    BapError_t firstErr = BapError_t::BapErr_OK;
    for (int32_t i = 0; i < fct_numb; i++) {
        const BapFctRomRow_ot& fct = BAP_FctRomTables[fct_index + i];
        BapError_t err = BapError_t::BapErr_OK;

        if (fct.eFunctionClass == BapFctCls_Method
            || fct.eFunctionClass == BapFctCls_Cache
            || fct.fctId == (fctId_t)2    // BAP_Config
            || fct.fctId == (fctId_t)3    // FunctionList
            || fct.fctId == (fctId_t)4    // HeartBeat
            )
        {
            std::cout << "[SERVER][INIT] skip function : " << static_cast<int32_t>(fct.fctId)
                       << '\n';
            continue;
        }

        if (fct.eTxDataType == BapDataType_t::BapDt_Void) {
            std::cout << "[SERVER][INIT] skip function : "
                      << static_cast<int32_t>(fct.fctId) << " type void\n";
            continue;
        }

        switch (fct.eTxDataType) {
            case BapDataType_t::BapDt_Int8:
            {
                err = BAP_InitSendBufferInt8(aLsgId,
                                             fct.fctId,
                                             (uint8_t)0u);
                break;
            }
            case BapDataType_t::BapDt_Int16:
            {
                err = BAP_InitSendBufferInt16(aLsgId,
                                              fct.fctId,
                                              (uint16_t)0u);
                break;
            }
            case BapDataType_t::BapDt_Int32:
            {
                err = BAP_InitSendBufferInt32(aLsgId,
                                              fct.fctId,
                                              (uint32_t)0u);
                break;
            }
            case BapDataType_t::BapDt_FixedByteSequence: // FALL-THROUGH
            case BapDataType_t::BapDt_ByteSequence:
            {
                std::vector<uint8_t> zeroBuf(fct.u32TxSize, 0u);
                err = BAP_InitSendBufferByteSequence(aLsgId,
                                                     fct.fctId,
                                                     zeroBuf.data(),
                                                     fct.u32TxSize);
                break;
            }
            default:
            {
                /* unknown data type – skip but warn */
                std::cerr << "[SERVER][INIT] initAllSendBuffers: unknown eTxDataType="
                          << (int32_t)fct.eTxDataType
                          << " for fctId=" << (int32_t)fct.fctId << '\n';
                break;
            }
        }

        if (firstErr == BapError_t::BapErr_OK) {
            firstErr = err;
        }
        std::cerr << "[SERVER][INIT] initAllSendBuffers: lsgId : "
                  << (int32_t)fct.lsgId
                  << " fctId="
                  << (int32_t)fct.fctId
                  << " type=" << (int32_t)fct.eTxDataType
                  << " size=" << (int32_t)fct.u32TxSize
                  << " code: 0x" << std::hex << std::setw(2) << std::setfill('0')
                  << (int32_t)err << std::dec << '\n';
    }

    if (firstErr != BapError_t::BapErr_OK) {
        std::cout << "[SERVER] Failed to init send TX buffer\n";
        return -1;
    }

    return 0;
}

int32_t FSGManager::_initLsg(void)
{
    // Init BAP
    std::cout << "[SERVER] Init all lsg needed\n";
    for (const lsgId_t lsg : lsgId_vec) {
        // init LSG cyclic
        if (BAP_Init(lsg) != BapError_t::BapErr_OK) {
            std::cerr << "[SERVER] Failed to init lsgId : "
                      << static_cast<int32_t>(lsg) << '\n';
            return -1;
        }
        std::cout << "[SERVER] Success to init lsgId : "
                  << static_cast<int32_t>(lsg) << '\n';

        // init sending buffer
        if (_initAllSendBuffers(lsg) != 0) {
            std::cout << "[SERVER] failed to init sending buffers\n";
            return -1;
        }
        std::cout << "[SERVER] Success to init sending buffers\n";
    }
    std::cout << "[SERVER] all buffers needed of each lsgId already generated\n";
    return 0;
}

int32_t FSGManager::_startLsg(void)
{
    std::cout << "[SERVER] start all lsg needed\n";
    // start BAP cycle
    for (const lsgId_t lsg : lsgId_vec) {
        if (BAP_Start(lsg) != BapError_t::BapErr_OK) {
            std::cerr << "[SERVER] Failed to start lsgId : "
                      << static_cast<int32_t>(lsg) << '\n';
            return -1;
        }
        std::cout << "[SERVER] Success to start lsgId : "
                  << static_cast<int32_t>(lsg) << '\n';

        _waitBAPTasks(100);
        if (BAP_GetLsgState(lsg) != BAP_TRUE) {
            std::cerr << "[SERVER] lsgId : "
                      << static_cast<int32_t>(lsg) << ", is not running !!!\n";
            return -1;
        }
        std::cout << "[SERVER] lsgId : "
                  << static_cast<int32_t>(lsg) << ", is running !!!\n";
    }
    return 0;
}

int32_t FSGManager::_stopLsg(void)
{
    return 0;
}
