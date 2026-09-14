#include "ASGManager.hpp"
#include "asg_type.hpp"
#include <iomanip>

#if defined(__CYGWIN__) || defined(WIN32)
    #include <windows.h>
#else
    #include <unistd.h>
#endif

using namespace std::placeholders;

#define TIMEOUT_AFTER_START_LSG 1000 // 1 second
#define BAP_USES_NOT_OWN_UINT32
// constexpr std::string SERVER_IP = "10.169.225.102";
constexpr std::string SERVER_IP = "127.0.0.1";
constexpr uint16_t PORT = 2007;

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
    std::cout << "[CLIENT][CALLBACK][TX] BAP_Transmit_TxData\n";
    const bool_t ret = ASGManager::instance()->transmitTxData(apData, au16MsgLength);
    return ret;
}

} // extern "C"

ASGManager::~ASGManager(void)
{
    std::wcout << "[CLIENT] ASGManager has been stopped\n";
    stop();
}

std::shared_ptr<ASGManager> ASGManager::instance(void)
{
    static std::shared_ptr<ASGManager> _instance = std::make_shared<ASGManager>(ASGManagerToken{});
    return _instance;
}

void ASGManager::acknowledge(const lsgId_t aLsgId,
                             const fctId_t aFctId,
                             const BapAcknowledge_et aeAcknowledge)
{
    std::cout << "[CLIENT][INDICATION][ACKNOWLEDGE] Receive message\n";
    if (m_climateLoadBalancer == nullptr) {
        std::cout << "[CLIENT] climate load balancer is nullptr\n";
        return;
    }
    if (m_climateLoadBalancer->rx == nullptr) {
        std::cout << "[CLIENT] balancer receive is nullptr\n";
        return;
    }
    m_climateLoadBalancer->rx->executeCb<void>(aLsgId, aFctId, aeAcknowledge);
}

void ASGManager::indicationVoid(const lsgId_t aLsgId,
                                const fctId_t aFctId,
                                const enum BapIndication_t aeIndication)
{
    std::cout << "[CLIENT][INDICATION][VOID] Receive message\n";
    if (m_climateLoadBalancer == nullptr) {
        std::cout << "[CLIENT] climate load balancer is nullptr\n";
        return;
    }
    if (m_climateLoadBalancer->rx == nullptr) {
        std::cout << "[CLIENT] balancer receive is nullptr\n";
        return;
    }
    m_climateLoadBalancer->rx->executeCb<void>(aLsgId, aFctId, aeIndication);
}

void ASGManager::indicationInt8(const lsgId_t aLsgId,
                                const fctId_t aFctId,
                                const enum BapIndication_t aeIndication,
                                const uint8_t au8Value)
{
    std::cout << "[CLIENT][INDICATION][INT8_T] Receive message\n";
    if (m_climateLoadBalancer == nullptr) {
        std::cout << "[CLIENT] climate load balancer is nullptr\n";
        return;
    }
    if (m_climateLoadBalancer->rx == nullptr) {
        std::cout << "[CLIENT] balancer receive is nullptr\n";
        return;
    }
    m_climateLoadBalancer->rx->executeCb<void>(aLsgId, aFctId, aeIndication, au8Value);
}

void ASGManager::indicationInt16(const lsgId_t aLsgId,
                                 fctId_t aFctId,
                                 enum BapIndication_t aeIndication,
                                 uint16_t au16Value)
{
    std::cout << "[CLIENT][INDICATION][INT16_T] Receive message\n";
    if (m_climateLoadBalancer == nullptr) {
        std::cout << "[CLIENT] climate load balancer is nullptr\n";
        return;
    }
    if (m_climateLoadBalancer->rx == nullptr) {
        std::cout << "[CLIENT] balancer receive is nullptr\n";
        return;
    }
    m_climateLoadBalancer->rx->executeCb<void>(aLsgId, aFctId, aeIndication, au16Value);
}

void ASGManager::indicationInt32(const lsgId_t aLsgId,
                                 fctId_t aFctId,
                                 enum BapIndication_t aeIndication,
                                 uint32_t au32Value)
{
    std::cout << "[CLIENT][INDICATION][INT32_T] Receive message\n";
    if (m_climateLoadBalancer == nullptr) {
        std::cout << "[CLIENT] climate load balancer is nullptr\n";
        return;
    }
    if (m_climateLoadBalancer->rx == nullptr) {
        std::cout << "[CLIENT] balancer receive is nullptr\n";
        return;
    }
    m_climateLoadBalancer->rx->executeCb<void>(aLsgId, aFctId, aeIndication, au32Value);
}

void ASGManager::indicationByteSequence(const lsgId_t aLsgId,
                                        const fctId_t aFctId,
                                        const enum BapIndication_t aeIndication,
                                        const volatile uint8_t apValue[],
                                        const uint32_t au32Length)
{
    std::cout << "[CLIENT][INDICATION][BYTE_SEQUENCE] Receive message\n";
    if (m_climateLoadBalancer == nullptr) {
        std::cout << "[CLIENT] climate load balancer is nullptr\n";
        return;
    }
    if (m_climateLoadBalancer->rx == nullptr) {
        std::cout << "[CLIENT] balancer receive is nullptr\n";
        return;
    }
    m_climateLoadBalancer->rx->executeCb<void>(aLsgId, aFctId, aeIndication, apValue, au32Length);
}

void ASGManager::indicationError(const lsgId_t aLsgId,
                                 const fctId_t aFctId,
                                 const enum BapError_t aeErrorCode)
{
    std::cout << "[CLIENT][INDICATION][ERROR] Receive message\n";
    if (m_climateLoadBalancer == nullptr) {
        std::cout << "[CLIENT] climate load balancer is nullptr\n";
        return;
    }
    if (m_climateLoadBalancer->rx == nullptr) {
        std::cout << "[CLIENT] balancer receive is nullptr\n";
        return;
    }
    m_climateLoadBalancer->rx->executeCb<void>(aLsgId, aFctId, aeErrorCode);
}

enum BapError_t ASGManager::sendDebugInfo(DBGVAR const uint8_t pDebugInfo[8])
{
    return BapError_t::BapErr_OK;
}

int32_t ASGManager::init(void)
{
    // Init BAP storage
    try {
        m_climateLoadBalancer = std::make_shared<ClimateLoadBalancer>();
    } catch (std::bad_alloc& err) {
        std::cerr << "[CLIENT] Failed to allocate climateStorage, err : " << err.what() << '\n';
    }
    // Init gRPC to BAP Router
    // Init General transfer
    // Init Ethernet bridge
    try {
        m_ethernetHandler = std::make_shared<EthernetHandler>(SERVER_IP,
                                                              PORT,
                                                              BAP_MAX_PDU_SIZE,
                                                              BAP_SOAD_HEADER_SIZE);
    } catch (std::bad_alloc& err) {
        std::cerr << "[CLIENT] Failed to allocate ethernet Handler, err : " << err.what() << '\n';
    } 

    const int32_t ret_init_lsg = _initLsg();
    if (ret_init_lsg != 0) return -1;

    std::cout << "[CLIENT] Success to create BAP logical block\n";
    return 0;
}

void ASGManager::start(void)
{
    std::cout << "[CLIENT][START] Start ASG client !!!\n";
    // start general transfer handler

    // start ethernet handler
    if (m_ethernetHandler == nullptr) {
        std::cerr << "[CLIENT] ethernet handler is nullptr\n";
        return;
    }
    m_ethernetHandler->startEthernetHandler(BAP_RxIndication);

    // register transmit/receive methods via BAP
    _registerRxFunction();
    _registerTxFunction();
    _generateDataBase();

    const int32_t ret_start_lsg = _startLsg();
    if (ret_start_lsg != 0) return;

    std::vector<uint8_t> data = {10, 11, 12, 13, 14, 15};
    uint32_t len = 6u;
    txByteSequence(lsgId_t::BapLsg_ClimateZone,
                   fctId_t::BapFct_ClimateZone_ZL_Temperature,
                   BapRequest_t::BapReq_DataSetGet,
                   &*data.begin(),
                   len);

    data.clear();
    data = (std::vector<uint8_t>){15u, 14u};
    txByteSequence(lsgId_t::BapLsg_ClimateMaster,
                   fctId_t::BapFct_ClimateMaster_AC,
                   BapRequest_t::BapReq_DataSetGet,
                   &*data.begin(),
                   2u);

    while (true) {
        BAP_Task();
#if defined(__CYGWIN__) || defined(WIN32)
        Sleep(1);
#else
        usleep(1);
#endif // defined(__CYGWIN__) || defined(WIN32)
    }

    return;
}

int32_t ASGManager::stop(void)
{
    std::cout << "[CLIENT][STOP] stop ASG client !!!\n";
    return 0;
}

void ASGManager::_waitBAPTasks(int32_t time_delay)
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

bool_t ASGManager::transmitTxData(ptr_t apData, const uint16_t au16MsgLength)
{
    if (m_ethernetHandler == nullptr) {
        std::cerr << "[CLIENT] ethernet handler is nullptr\n";
        return BAP_FALSE;
    }
    const int32_t ret_send = m_ethernetHandler->deliverEthernetPackage((const char*)apData,
                                                                       au16MsgLength);
    if (ret_send < 0) {
        std::cerr << "[CLIENT] Failed to send data !!!\n";
        return BAP_FALSE;
    }
    return BAP_TRUE;
}

/* HVAC transfer data to Linux */
void ASGManager::_rx_Fsg_control_fctId_13(const lsgId_t lsgId,
                                          const fctId_t fctId,
                                          const BapIndication_t cmd,
                                          const uint8_t data)
{
    (void)lsgId;
    (void)fctId;
    (void)cmd;
    // write logic forwarding to android
}

void ASGManager::_rx_Fsg_control_acknowledge_fctId_13(const lsgId_t lsgId,
                                                      const fctId_t fctId,
                                                      const BapAcknowledge_t ackCode)
{
    std::cout << "[CLIENT] acknowledge function with lsg/fctid/ackCode : "
              << static_cast<int32_t>(lsgId) << '/'
              << static_cast<int32_t>(fctId) << '/'
              << static_cast<int32_t>(ackCode) << '\n';
}

void ASGManager::_rx_Fsg_control_error_fctId_13(const lsgId_t lsgId,
                                                const fctId_t fctId,
                                                const BapError_t err)
{
    std::cout << "[CLIENT] error function with lsg/fctid/err : "
              << static_cast<int32_t>(lsgId) << '/'
              << static_cast<int32_t>(fctId) << '/'
              << static_cast<int32_t>(err) << '\n';
}

void ASGManager::_rx_ZL_Temperature_acknowledge_fctId_16(const lsgId_t lsgId,
                                                         const fctId_t fctId,
                                                         const BapAcknowledge_t ackCode)
{
    std::cout << "[CLIENT] acknowledge function with lsg/fctid/ackCode : "
              << static_cast<int32_t>(lsgId) << '/'
              << static_cast<int32_t>(fctId) << '/'
              << static_cast<int32_t>(ackCode) << '\n';
}

void ASGManager::_rx_ZL_Temperature_error_fctId_16(const lsgId_t lsgId,
                                                   const fctId_t fctId,
                                                   const BapError_t err)
{
    std::cout << "[CLIENT] error function with lsg/fctid/err : "
              << static_cast<int32_t>(lsgId) << '/'
              << static_cast<int32_t>(fctId) << '/'
              << static_cast<int32_t>(err) << '\n';
}

void ASGManager::_rx_ZL_Temperature_fctId_16(const lsgId_t lsgId,
                                             const fctId_t fctId,
                                             const BapIndication_t cmd,
                                             const volatile uint8_t* data,
                                             const uint32_t len)
{
    (void)lsgId;
    (void)fctId;
    (void)cmd;
    std::cout << "[CLIENT] Receive indication for ZL temperature\n";
    std::cout << "[CLIENT][RECV] : ";
    for (uint32_t i = 0u; i < len; i++) {
        std::cout << std::hex << std::setw(2) << std::setfill('0')
                  << static_cast<int32_t>(data[i]) << ' ';
        std::cout << std::dec;
    }
    std::cout << '\n';
}

void ASGManager::_rx_ZR_Temperature_acknowledge_fctId_17(const lsgId_t lsgId,
                                                         const fctId_t fctId,
                                                         const BapAcknowledge_t ackCode)
{
    std::cout << "[CLIENT] acknowledge function with lsg/fctid/ackCode : "
              << static_cast<int32_t>(lsgId) << '/'
              << static_cast<int32_t>(fctId) << '/'
              << static_cast<int32_t>(ackCode) << '\n';
}

void ASGManager::_rx_ZR_Temperature_error_fctId_17(const lsgId_t lsgId,
                                                   const fctId_t fctId,
                                                   const BapError_t err)
{
    std::cout << "[CLIENT] error function with lsg/fctid/err : "
              << static_cast<int32_t>(lsgId) << '/'
              << static_cast<int32_t>(fctId) << '/'
              << static_cast<int32_t>(err) << '\n';
}

void ASGManager::_rx_ZR_Temperature_fctId_17(const lsgId_t lsgId,
                                             const fctId_t fctId,
                                             const BapIndication_t cmd,
                                             const volatile uint8_t* data,
                                             const uint32_t len)
{
    (void)lsgId;
    (void)fctId;
    (void)cmd;
    std::cout << "[CLIENT] Receive indication for ZR temperature\n";
    std::cout << "[CLIENT][RECV] : ";
    for (uint32_t i = 0u; i < len; i++) {
        std::cout << std::hex << std::setw(2) << std::setfill('0')
                  << static_cast<int32_t>(data[i]) << ' ';
        std::cout << std::dec;
    }
    std::cout << '\n';
}

void ASGManager::_rx_ZL_AirVolume_acknowledge_fctId_18(const lsgId_t lsgId,
                                                       const fctId_t fctId,
                                                       const BapAcknowledge_t ackCode)
{
    std::cout << "[CLIENT] acknowledge function with lsg/fctid/ackCode : "
              << static_cast<int32_t>(lsgId) << '/'
              << static_cast<int32_t>(fctId) << '/'
              << static_cast<int32_t>(ackCode) << '\n';
}

void ASGManager::_rx_ZL_AirVolume_error_fctId_18(const lsgId_t lsgId,
                                                 const fctId_t fctId,
                                                 const BapError_t err)
{
    std::cout << "[CLIENT] error function with lsg/fctid/err : "
              << static_cast<int32_t>(lsgId) << '/'
              << static_cast<int32_t>(fctId) << '/'
              << static_cast<int32_t>(err) << '\n';
}

void ASGManager::_rx_ZL_AirVolume_fctId_18(const lsgId_t lsgId,
                                             const fctId_t fctId,
                                             const BapIndication_t cmd,
                                             const volatile uint8_t* data,
                                             const uint32_t len)
{
    (void)lsgId;
    (void)fctId;
    (void)cmd;
    std::cout << "[CLIENT] Receive indication for ZL AirVolume\n";
    std::cout << "[CLIENT][RECV] : ";
    for (uint32_t i = 0u; i < len; i++) {
        std::cout << std::hex << std::setw(2) << std::setfill('0')
                  << static_cast<int32_t>(data[i]) << ' ';
        std::cout << std::dec;
    }
    std::cout << '\n';
}

void ASGManager::_rx_ZR_AirVolume_acknowledge_fctId_19(const lsgId_t lsgId,
                                                       const fctId_t fctId,
                                                       const BapAcknowledge_t ackCode)
{
    std::cout << "[CLIENT] acknowledge function with lsg/fctid/ackCode : "
              << static_cast<int32_t>(lsgId) << '/'
              << static_cast<int32_t>(fctId) << '/'
              << static_cast<int32_t>(ackCode) << '\n';
}

void ASGManager::_rx_ZR_AirVolume_error_fctId_19(const lsgId_t lsgId,
                                                 const fctId_t fctId,
                                                 const BapError_t err)
{
    std::cout << "[CLIENT] error function with lsg/fctid/err : "
              << static_cast<int32_t>(lsgId) << '/'
              << static_cast<int32_t>(fctId) << '/'
              << static_cast<int32_t>(err) << '\n';
}

void ASGManager::_rx_ZR_AirVolume_fctId_19(const lsgId_t lsgId,
                                             const fctId_t fctId,
                                             const BapIndication_t cmd,
                                             const volatile uint8_t* data,
                                             const uint32_t len)
{
    (void)lsgId;
    (void)fctId;
    (void)cmd;
    std::cout << "[CLIENT] Receive indication for ZR AirVolume\n";
    std::cout << "[CLIENT][RECV] : ";
    for (uint32_t i = 0u; i < len; i++) {
        std::cout << std::hex << std::setw(2) << std::setfill('0')
                  << static_cast<int32_t>(data[i]) << ' ';
        std::cout << std::dec;
    }
    std::cout << '\n';
}

void ASGManager::_rx_ClimateMaster_AC_acknowledge_fctId_16(const lsgId_t lsgId,
                                                           const fctId_t fctId,
                                                           const BapAcknowledge_t ackCode)
{
    std::cout << "[CLIENT] acknowledge function with lsg/fctid/ackCode : "
              << static_cast<int32_t>(lsgId) << '/'
              << static_cast<int32_t>(fctId) << '/'
              << static_cast<int32_t>(ackCode) << '\n';
}

void ASGManager::_rx_ClimateMaster_AC_error_fctId_16(const lsgId_t lsgId,
                                                     const fctId_t fctId,
                                                     const BapError_t err)
{
    std::cout << "[CLIENT] error function with lsg/fctid/err : "
              << static_cast<int32_t>(lsgId) << '/'
              << static_cast<int32_t>(fctId) << '/'
              << static_cast<int32_t>(err) << '\n';
}

void ASGManager::_rx_ClimateMaster_AC_fctId_16(const lsgId_t lsgId,
                                               const fctId_t fctId,
                                               const BapIndication_t cmd,
                                               const volatile uint8_t* data,
                                               const uint32_t len)
{
    (void)lsgId;
    (void)fctId;
    (void)cmd;
    std::cout << "[CLIENT] Receive indication for climate master AC\n";
    std::cout << "[CLIENT][RECV] : ";
    for (uint32_t i = 0u; i < len; i++) {
        std::cout << std::hex << std::setw(2) << std::setfill('0')
                  << static_cast<int32_t>(data[i]) << ' ';
        std::cout << std::dec;
    }
    std::cout << '\n';
}

void ASGManager::_registerTxFunction(void)
{
    if (m_climateLoadBalancer == nullptr) {
        std::cerr << "[CLIENT] climate zone rec mapping is nullptr\n";
        return;
    }

    const std::shared_ptr<ClimateZoneBridge> transmitter = m_climateLoadBalancer->tx;
    if (transmitter == nullptr) {
        std::cout << "[CLIENT] balancer transmitter is nullptr\n";
        return;
    }

    transmitter->registerCb<cbTxInt8>
    (
        lsgId_t::BapLsg_ClimateZone,
        fctId_t::BapFct_ClimateZone_FSG_Control,
        std::bind(&BAP_RequestInt8, _1, _2, _3, _4)
    );
    transmitter->registerCb<cbTxByteSequence>
    (
        lsgId_t::BapLsg_ClimateZone,
        fctId_t::BapFct_ClimateZone_ZL_Temperature,
        std::bind(&BAP_RequestByteSequence, _1, _2, _3, _4, _5)
    );
    transmitter->registerCb<cbTxByteSequence>
    (
        lsgId_t::BapLsg_ClimateZone,
        fctId_t::BapFct_ClimateZone_ZR_Temperature,
        std::bind(&BAP_RequestByteSequence, _1, _2, _3, _4, _5)
    );
    transmitter->registerCb<cbTxByteSequence>
    (
        lsgId_t::BapLsg_ClimateZone,
        fctId_t::BapFct_ClimateZone_ZL_AirVolume,
        std::bind(&BAP_RequestByteSequence, _1, _2, _3, _4, _5)
    );
    transmitter->registerCb<cbTxByteSequence>
    (
        lsgId_t::BapLsg_ClimateZone,
        fctId_t::BapFct_ClimateZone_ZR_AirVolume,
        std::bind(&BAP_RequestByteSequence, _1, _2, _3, _4, _5)
    );
    transmitter->registerCb<cbTxByteSequence>
    (
        lsgId_t::BapLsg_ClimateMaster,
        fctId_t::BapFct_ClimateMaster_AC,
        std::bind(&BAP_RequestByteSequence, _1, _2, _3, _4, _5)
    );
}

void ASGManager::_registerRxFunction(void)
{
    if (m_climateLoadBalancer == nullptr) {
        std::cerr << "[CLIENT] climate zone rec mapping is nullptr\n";
        return;
    }

    const std::shared_ptr<ClimateZoneBridge> receiver = m_climateLoadBalancer->rx;
    if (receiver == nullptr) {
        std::cout << "[CLIENT] balancer receive is nullptr\n";
        return;
    }

    /* ------------------- FSG CONTROL ----------------------------*/
    receiver->registerCb<cbRxVoidInt8>(
        lsgId_t::BapLsg_ClimateZone,
        fctId_t::BapFct_ClimateZone_FSG_Control,
        std::bind(&ASGManager::_rx_Fsg_control_fctId_13, this, _1, _2, _3, _4)
    );
    receiver->registerCb<cbRxVoidAcknowledge>(
        lsgId_t::BapLsg_ClimateZone,
        fctId_t::BapFct_ClimateZone_FSG_Control,
        std::bind(&ASGManager::_rx_Fsg_control_acknowledge_fctId_13, this, _1, _2, _3)
    );
    receiver->registerCb<cbRxVoidError>(
        lsgId_t::BapLsg_ClimateZone,
        fctId_t::BapFct_ClimateZone_FSG_Control,
        std::bind(&ASGManager::_rx_Fsg_control_error_fctId_13, this, _1, _2, _3)
    );
    /* ------------------------------------------------------------*/

    /* ------------------- ZL Temperature -------------------------*/
    receiver->registerCb<cbRxVoidByteSq>(
        lsgId_t::BapLsg_ClimateZone,
        fctId_t::BapFct_ClimateZone_ZL_Temperature,
        std::bind(&ASGManager::_rx_ZL_Temperature_fctId_16, this, _1, _2, _3, _4, _5)
    );
    receiver->registerCb<cbRxVoidAcknowledge>(
        lsgId_t::BapLsg_ClimateZone,
        fctId_t::BapFct_ClimateZone_ZL_Temperature,
        std::bind(&ASGManager::_rx_ZL_Temperature_acknowledge_fctId_16, this, _1, _2, _3)
    );
    receiver->registerCb<cbRxVoidError>(
        lsgId_t::BapLsg_ClimateZone,
        fctId_t::BapFct_ClimateZone_ZL_Temperature,
        std::bind(&ASGManager::_rx_ZL_Temperature_error_fctId_16, this, _1, _2, _3)
    );
    /* ------------------------------------------------------------*/

    /* ------------------- ZR Temperature -------------------------*/
    receiver->registerCb<cbRxVoidByteSq>(
        lsgId_t::BapLsg_ClimateZone,
        fctId_t::BapFct_ClimateZone_ZR_Temperature,
        std::bind(&ASGManager::_rx_ZR_Temperature_fctId_17, this, _1, _2, _3, _4, _5)
    );
    receiver->registerCb<cbRxVoidAcknowledge>(
        lsgId_t::BapLsg_ClimateZone,
        fctId_t::BapFct_ClimateZone_ZR_Temperature,
        std::bind(&ASGManager::_rx_ZR_Temperature_acknowledge_fctId_17, this, _1, _2, _3)
    );
    receiver->registerCb<cbRxVoidError>(
        lsgId_t::BapLsg_ClimateZone,
        fctId_t::BapFct_ClimateZone_ZR_Temperature,
        std::bind(&ASGManager::_rx_ZR_Temperature_error_fctId_17, this, _1, _2, _3)
    );
    /* ------------------------------------------------------------*/

    /* ------------------- ZL AirVolume ---------------------------*/
    receiver->registerCb<cbRxVoidByteSq>(
        lsgId_t::BapLsg_ClimateZone,
        fctId_t::BapFct_ClimateZone_ZL_AirVolume,
        std::bind(&ASGManager::_rx_ZL_AirVolume_fctId_18, this, _1, _2, _3, _4, _5)
    );
    receiver->registerCb<cbRxVoidAcknowledge>(
        lsgId_t::BapLsg_ClimateZone,
        fctId_t::BapFct_ClimateZone_ZL_AirVolume,
        std::bind(&ASGManager::_rx_ZL_AirVolume_acknowledge_fctId_18, this, _1, _2, _3)
    );
    receiver->registerCb<cbRxVoidError>(
        lsgId_t::BapLsg_ClimateZone,
        fctId_t::BapFct_ClimateZone_ZL_AirVolume,
        std::bind(&ASGManager::_rx_ZL_AirVolume_error_fctId_18, this, _1, _2, _3)
    );
    /* ------------------------------------------------------------*/

    /* ------------------- ZR AirVolume ---------------------------*/
    receiver->registerCb<cbRxVoidByteSq>(
        lsgId_t::BapLsg_ClimateZone,
        fctId_t::BapFct_ClimateZone_ZR_AirVolume,
        std::bind(&ASGManager::_rx_ZR_AirVolume_fctId_19, this, _1, _2, _3, _4, _5)
    );
    receiver->registerCb<cbRxVoidAcknowledge>(
        lsgId_t::BapLsg_ClimateZone,
        fctId_t::BapFct_ClimateZone_ZR_AirVolume,
        std::bind(&ASGManager::_rx_ZR_AirVolume_acknowledge_fctId_19, this, _1, _2, _3)
    );
    receiver->registerCb<cbRxVoidError>(
        lsgId_t::BapLsg_ClimateZone,
        fctId_t::BapFct_ClimateZone_ZR_AirVolume,
        std::bind(&ASGManager::_rx_ZR_AirVolume_error_fctId_19, this, _1, _2, _3)
    );
    /* ------------------------------------------------------------*/

    /* ------------------- Climate master AC ----------------------*/
    receiver->registerCb<cbRxVoidByteSq>(
        lsgId_t::BapLsg_ClimateMaster,
        fctId_t::BapFct_ClimateMaster_AC,
        std::bind(&ASGManager::_rx_ClimateMaster_AC_fctId_16, this, _1, _2, _3, _4, _5)
    );
    receiver->registerCb<cbRxVoidAcknowledge>(
        lsgId_t::BapLsg_ClimateMaster,
        fctId_t::BapFct_ClimateMaster_AC,
        std::bind(&ASGManager::_rx_ClimateMaster_AC_acknowledge_fctId_16, this, _1, _2, _3)
    );
    receiver->registerCb<cbRxVoidError>(
        lsgId_t::BapLsg_ClimateMaster,
        fctId_t::BapFct_ClimateMaster_AC,
        std::bind(&ASGManager::_rx_ClimateMaster_AC_error_fctId_16, this, _1, _2, _3)
    );
    /* ------------------------------------------------------------*/
}

void ASGManager::_generateDataBase(void)
{
    if (m_climateLoadBalancer == nullptr) {
        std::cerr << "[CLIENT] climate zone rec mapping is nullptr\n";
        return;
    }
}

void ASGManager::txByteSequence(const lsgId_t lsgId,
                                const fctId_t fctId,
                                const enum BapRequest_t cmd,
                                const uint8_t apValue[],
                                const uint32_t au32Length)
{
    if (m_climateLoadBalancer == nullptr) {
        std::cerr << "[CLIENT] climate zone rec mapping is nullptr\n";
        return;
    }
    std::cout << "[CLIENT] txByteSequence: lsgId="
              << static_cast<int32_t>(lsgId)
              << " fctId="
              << static_cast<int32_t>(fctId)
              << " cmd="
              << static_cast<int32_t>(cmd)
              << " au32Length="
              << static_cast<int32_t>(au32Length)
              << '\n';
    BapError_t err = m_climateLoadBalancer->tx->executeCb<BapError_t>(lsgId,
                                                                      fctId,
                                                                      cmd,
                                                                      apValue,
                                                                      au32Length);
    _waitBAPTasks(100);
    if (err == BapError_t::BapErr_OK) {
        std::cout << "[CLIENT] Success to transmit byte sequence API\n";
    } else {
        std::cerr << "[CLIENT] Failed to transmit byte sequence API, err : "
                  << static_cast<int32_t>(err) << '\n';
    }
}

void ASGManager::txSingleVal(const lsgId_t lsgId,
                             const fctId_t fctId,
                             const enum BapRequest_t cmd,
                             const std::optional<std::any> any_data)
{
    if (m_climateLoadBalancer == nullptr) {
        std::cerr << "[CLIENT] climate zone rec mapping is nullptr\n";
        return;
    }
    BapError_t err = m_climateLoadBalancer->tx->executeCb<BapError_t>(lsgId,
                                                                      fctId,
                                                                      cmd,
                                                                      any_data);
    if (err == BapError_t::BapErr_OK) {
        std::cout << "[CLIENT] Success to transmit single value API\n";
    } else {
        std::cerr << "[CLIENT] Failed to transmit single value API\n";
    }
}

int32_t ASGManager::_initLsg(void)
{
    std::cout << "[CLIENT] Start init all lsg needed\n";
    for (const lsgId_t lsg : lsgId_vec) {
        if (BAP_Init(lsg) == BapError_t::BapErr_OK) {
            std::cout << "[CLIENT] Success to init for lsgId : "
                      << static_cast<int32_t>(lsg) << '\n';
        } else {
            std::cerr << "[CLIENT] Failed to init for lsgId : "
                      << static_cast<int32_t>(lsg) << '\n';
            return -1;
        }
    }
    std::cout << "[CLIENT] Success init all LSG required\n";
    return 0;
}

int32_t ASGManager::_startLsg(void)
{
    std::cout << "[CLIENT] Start all lsg needed\n";
    for (const lsgId_t lsg : lsgId_vec) {
        // start BAP cycle
        if (BAP_Start(lsg) != BapError_t::BapErr_OK) {
            std::cerr << "[CLIENT] Failed to start lsgId : "
                      << static_cast<int32_t>(lsg) << '\n';
            return -1;
            
        }
        std::cout << "[CLIENT] Success to start lsgId : "
                  << static_cast<int32_t>(lsg) << '\n';

        // timeout after start
        int32_t timeout = 0;
        while (BAP_GetLsgState(lsg) != BAP_TRUE && timeout < TIMEOUT_AFTER_START_LSG) {
            BAP_Task();
#if defined(__CYGWIN__) || defined(WIN32)
            Sleep(1);
#else
            sleep(1);
#endif // defined(__CYGWIN__) || defined(WIN32)
        }

        // re-check lsg state
        if (BAP_GetLsgState(lsg) != BAP_TRUE) {
            std::cerr << "[CLIENT] Timeout waiting for lsgId : "
                      << static_cast<int32_t>(lsg) << ", handshake\n";
            return -1;
        }
        std::cout << "[CLIENT] LsgId : "
                  << static_cast<int32_t>(lsg) << ", state OK\n";
        _waitBAPTasks(200);
    }
    std::cout << "[CLIENT] All Lsg is running !!!\n";
    
    return 0;
}

int32_t ASGManager::_stopLsg(void)
{
    return 0;
}
