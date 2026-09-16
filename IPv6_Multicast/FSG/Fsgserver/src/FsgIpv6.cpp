#include "FsgIpv6.hpp"
#include <iomanip>
#include <vector>
#include <cstring>
#include "palb_cfg_project.h"
#include "BapParser.hpp"

#define LSG_START_RETRY_INTERVAL_MS 1000
#define TIMEOUT_AFTER_START_LSG 3000 

static const std::string MULTICAST_GROUP = "ff14::1:fe";
static const uint16_t    MULTICAST_PORT  = 42514u;
static const std::string VLAN_IP         = "vEthernet (br0.3)";
static const uint16_t    SRC_PORT        = 42993u;

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
    const bool_t ret = FsgIpv6::instance()->transmitTxData(apData, au16MsgLength);
    return ret;
}

} // extern "C"

FsgIpv6::~FsgIpv6(void)
{
    std::wcout << "[SERVER] FsgIpv6 has been stopped\n";
    stop();
}

std::shared_ptr<FsgIpv6> FsgIpv6::instance(void)
{
    static std::shared_ptr<FsgIpv6> _instance = std::make_shared<FsgIpv6>(FsgIpv6Token{});
    return _instance;
}

void FsgIpv6::acknowledge(const lsgId_t aLsgId,
                          const fctId_t aFctId,
                          const BapAcknowledge_et aeAcknowledge)
{

}

void FsgIpv6::indicationVoid(const lsgId_t aLsgId,
                             const fctId_t aFctId,
                             const enum BapIndication_t aeIndication)
{

}

void FsgIpv6::indicationInt8(const lsgId_t aLsgId,
                             const fctId_t aFctId,
                             const enum BapIndication_t aeIndication,
                             const uint8_t au8Value)
{

}

void FsgIpv6::indicationInt16(const lsgId_t aLsgId,
                              fctId_t aFctId,
                              enum BapIndication_t aeIndication,
                              uint16_t au16Value)
{

}

void FsgIpv6::indicationInt32(const lsgId_t aLsgId,
                              fctId_t aFctId,
                              enum BapIndication_t aeIndication,
                              uint32_t au32Value)
{

}

void FsgIpv6::indicationByteSequence(const lsgId_t aLsgId,
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
}

void FsgIpv6::indicationError(const lsgId_t aLsgId,
                                 const fctId_t aFctId,
                                 const enum BapError_t aeErrorCode)
{

}

enum BapError_t FsgIpv6::sendDebugInfo(DBGVAR const uint8_t pDebugInfo[8])
{
    return BapError_t::BapErr_OK;
}

void FsgIpv6::_onPduReceived(const PDU& pdu)
{
    std::vector<uint8_t> buf(BAP_SOAD_HEADER_SIZE + pdu.payload.size());
    buf[0] = (pdu.message_id >> 24) & 0xFFu;
    buf[1] = (pdu.message_id >> 16) & 0xFFu;
    buf[2] = (pdu.message_id >>  8) & 0xFFu;
    buf[3] =  pdu.message_id        & 0xFFu;
    buf[4] = (pdu.length     >> 24) & 0xFFu;
    buf[5] = (pdu.length     >> 16) & 0xFFu;
    buf[6] = (pdu.length     >>  8) & 0xFFu;
    buf[7] =  pdu.length            & 0xFFu;
    std::copy(pdu.payload.begin(), pdu.payload.end(), buf.begin() + BAP_SOAD_HEADER_SIZE);

    std::lock_guard<std::mutex> lk(m_rxMtx);
    m_rxQueue.push(std::move(buf));
}

void FsgIpv6::_tickBap(void)
{
    std::lock_guard<std::recursive_mutex> lk(m_bapMtx);
    BAP_Task();
}

int32_t FsgIpv6::init(void)
{
    std::cout << "[SERVER][INIT] Init FSG Server!!!\n";

    try {
        m_pduManager = std::make_unique<PDUManager>(MULTICAST_GROUP,
                                                    SRC_PORT,
                                                    MULTICAST_PORT,
                                                    0u,
                                                    VLAN_IP);
        for (const uint16_t msg_id : {BAP_Klima1_FSG_01_MSGID,
                                      BAP_Klima2_FSG_01_MSGID,
                                      BAP_KlimaMaster_FSG_01_MSGID,
                                      BAP_RDK_FSG_01_MSGID})
        {
            m_pduManager->registerNotifier(msg_id, [this](const PDU& pdu) {
                _onPduReceived(pdu);
            });
        }

        m_httpRequestHandler = std::make_shared<HttpRequestHandler>();
        m_dataBase = std::make_unique<DataBase>();
    } catch (const std::bad_alloc& err) {
        std::cerr << "failed to allocate pdu manager\n";
        return -1;
    }

    // Init BAP
    const int32_t ret_init_lsg = _initLsg();
    if (ret_init_lsg != 0) {
        std::cerr << "Failed to init BAP\n";
        return -1;
    }
    return 0;
}

void FsgIpv6::start(void)
{
    std::cout << "[SERVER][START] Start FSG server !!!\n";

    // start BAP cycle
    const int32_t ret_start_lsg = _startLsg();
    if (ret_start_lsg != 0) return;

    int32_t retry = 0;
    while (!m_pduManager->isMulticastRunning()) {
        if (m_pduManager->startMulticast()) {
            std::cout << "Multicast started successfully\n";
            break;
        }
        retry++;
        std::cerr << "Failed to start multicast (attempt " << retry
                  << "), retrying in " << LSG_START_RETRY_INTERVAL_MS << "ms...\n";
#if defined(__CYGWIN__) || defined(WIN32)
        Sleep(1000);
#else
        usleep(LSG_START_RETRY_INTERVAL_MS * 1000);
#endif // defined(__CYGWIN__) || defined(WIN32)
    }

    _genDataBase();
    _sendInitialValue();

    m_bapRunning.store(true);
    _heartBeat();
    _startHttpHandler();
    while (m_bapRunning.load()) {
        _waitBAPTasks(1);
    }

    return;
}

int32_t FsgIpv6::stop(void)
{
    std::cout << "[SERVER][STOP] stop FSG server !!!\n";
    m_bapRunning.store(false);
    if (m_httpRequestHandler != nullptr) m_httpRequestHandler->stop();
    if (m_heartBeatThread.joinable()) {
        m_heartBeatThread.join();
    }
    return 0;
}

void FsgIpv6::_waitBAPTasks(int32_t time_delay)
{
    while (time_delay--) {
        std::queue<std::vector<uint8_t>> localQueue;
        {
            std::lock_guard<std::mutex> lk(m_rxMtx);
            std::swap(localQueue, m_rxQueue);
        }
        while (!localQueue.empty()) {
            BAP_RxIndication(localQueue.front().data());
            localQueue.pop();
        }
        _tickBap();
#if defined(__CYGWIN__) || defined(WIN32)
        Sleep(1000);
#else
        usleep(1);
#endif // defined(__CYGWIN__) || defined(WIN32)
    }
}

void FsgIpv6::_heartBeat(void)
{
    m_heartBeatThread = std::thread([&](void) -> void {
        while (m_bapRunning.load()) {
            for (const lsgId_t lsgId : lsgId_vec) {
                BAP_RequestInt8(lsgId, (fctId_t)4, BapRequest_t::BapReq_Data, 0x0A);
            }
#if defined(__CYGWIN__) || defined(WIN32)
            Sleep(1000);
#else
            usleep(1);
#endif // defined(__CYGWIN__) || defined(WIN32)
        }
    });
}

bool_t FsgIpv6::transmitTxData(ptr_t apData, const uint16_t au16MsgLength)
{
    if (!m_pduManager) {
        std::cerr << "PDUManager is nullptr\n";
        return BAP_FALSE;
    }
    if (au16MsgLength < BAP_SOAD_HEADER_SIZE) {
        std::cerr << "TX buffer too short: " << au16MsgLength << '\n';
        return BAP_FALSE;
    }
    // Parse SoAD header: [4B msg_id big-endian][4B length big-endian] + payload
    const uint32_t msg_id = (static_cast<uint32_t>(apData[0]) << 24) |
                            (static_cast<uint32_t>(apData[1]) << 16) |
                            (static_cast<uint32_t>(apData[2]) <<  8) |
                            static_cast<uint32_t>(apData[3]);
    const uint32_t payload_len = static_cast<uint32_t>(au16MsgLength) - BAP_SOAD_HEADER_SIZE;
    std::vector<uint8_t> payload(apData + BAP_SOAD_HEADER_SIZE, apData + au16MsgLength);
    m_pduManager->insertPDU({msg_id, payload_len, std::move(payload)});
    m_pduManager->sendPDU();
    return BAP_TRUE;
}

int32_t FsgIpv6::_initAllSendBuffers(const lsgId_t aLsgId)
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

int32_t FsgIpv6::_initLsg(void)
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

int32_t FsgIpv6::_startLsg(void)
{
    std::cout << "[SERVER] start all lsg needed\n";
    // start BAP cycle
    for (const lsgId_t lsg : lsgId_vec) {
        if (BAP_Start(lsg) != BapError_t::BapErr_OK) {
            std::cerr << "[SERVER] Failed to start lsgId : "
                      << static_cast<int32_t>(lsg) << '\n';
            return -1;
        }
        std::cout << "[SERVER] Success to start lsgId : " << static_cast<int32_t>(lsg) << '\n';
        int32_t timeout = 0;
        while (BAP_GetLsgState(lsg) != BAP_TRUE && timeout < TIMEOUT_AFTER_START_LSG) {
            _waitBAPTasks(1);
            timeout++;
        }

        if (BAP_GetLsgState(lsg) != BAP_TRUE) {
            std::cerr << "[SERVER] lsgId : "
                      << static_cast<int32_t>(lsg) << ", is not running !!!\n";
            return -1;
        }
        std::cout << "[SERVER] lsgId : " << static_cast<int32_t>(lsg) << ", is running !!!\n";
        _waitBAPTasks(1);
    }
    return 0;
}

int32_t FsgIpv6::_stopLsg(void)
{
    return 0;
}

void FsgIpv6::_sendInitialValue(void)
{
    std::cout << "[SERVER] sending initial value to ASG\n";
    const std::shared_ptr<BapParser> parser = BapParser::instance();
    if (parser == nullptr) {
        std::cerr << "[SERVER] parser is nullptr\n";
        return;
    }
    parser->load_initial_vals();
}

void FsgIpv6::_genDataBase(void)
{
    if (m_dataBase == nullptr) {
        LOG_ERR << "climate zone rec mapping is nullptr";
        return;
    }
    LOG_DEBUG << "init data base for all lsgid";
    for (const lsgId_t lsg : lsgId_vec) {
        if (_genDataFollowLsgId(lsg) != 0) {
            LOG_ERR << "failed to init data base for lsgId : " << static_cast<int32_t>(lsg);
        } else {
            LOG_DEBUG << "success to init data base for lsgId : " << static_cast<int32_t>(lsg);
        }
    }
    LOG_DEBUG << "init data base for all lsgid success";
}

int32_t FsgIpv6::_genDataFollowLsgId(const lsgId_t lsgId)
{
    if (m_dataBase == nullptr) {
        LOG_ERR << "climate zone rec mapping is nullptr";
        return -1;
    }

    const BapLsgRomRow_pot lsgRomRow = BAP_GetLsgRomRow(lsgId);
    if (lsgRomRow == NULL) {
        LOG_DEBUG << "lsg not found";
        return 0;
    }
    const int32_t fct_numb = lsgRomRow->u8FctRomTableSize;
    const int32_t fct_index = lsgRomRow->u16FctRomIndex;
    LOG_DEBUG << "number_func="
                  << fct_numb
                  << ", start_index="
                  << fct_index
                  << ", lsgId="
                  << static_cast<int32_t>(lsgId);

    int32_t firstErr = 0;
    for (int32_t i = 0; i < fct_numb; i++) {
        const BapFctRomRow_ot& fct = BAP_FctRomTables[fct_index + i];
        int32_t err = 0;
        if (fct.eFunctionClass == BapFctCls_Method ||
            fct.eFunctionClass == BapFctCls_Cache ||
            fct.fctId == (fctId_t)2 ||
            fct.fctId == (fctId_t)3 ||
            fct.fctId == (fctId_t)4)
        {
            LOG_DEBUG << "Skip function : " << static_cast<int32_t>(fct.fctId);
            continue;
        }

        if (fct.eTxDataType == BapDataType_t::BapDt_Void) {
            LOG_DEBUG << "skip function : "
                      << static_cast<int32_t>(fct.fctId) << " type void";
            continue;
        }

        switch (fct.eTxDataType) {
            case BapDataType_t::BapDt_Int8:
            {
                err = m_dataBase->insert<uint8_t>(lsgId, fct.fctId, {0u, fct.u32TxSize});
                break;
            }
            case BapDataType_t::BapDt_Int16:
            {
                err = m_dataBase->insert<uint16_t>(lsgId, fct.fctId, {0u, fct.u32TxSize});
                break;
            }
            case BapDataType_t::BapDt_Int32:
            {
                err = m_dataBase->insert<uint32_t>(lsgId, fct.fctId, {0u, fct.u32TxSize});
                break;
            }
            case BapDataType_t::BapDt_FixedByteSequence: // FALL-THROUGH
            case BapDataType_t::BapDt_ByteSequence:
            {
                std::vector<uint8_t> zeroBuf(fct.u32TxSize, 0u);
                err = m_dataBase->insert<std::vector<uint8_t>>(lsgId,
                                                               fct.fctId,
                                                               {zeroBuf, fct.u32TxSize});
                break;
            }
            default:
            {
                /* unknown data type – skip but warn */
                LOG_ERR << "insert data base : unknown eTxDataType="
                          << (int32_t)fct.eTxDataType
                          << " for fctId=" << (int32_t)fct.fctId;
                break;
            }
        }

        if (firstErr == 0) {
            firstErr = err;
        }
        LOG_ERR << "insert data base : lsgId : "
                    << (int32_t)fct.lsgId
                    << " fctId="
                    << (int32_t)fct.fctId
                    << " type=" << (int32_t)fct.eTxDataType
                    << " size=" << (int32_t)fct.u32TxSize;
    }

    if (firstErr != 0) {
        LOG_DEBUG << "Failed to init send TX buffer";
    }
    return firstErr;
}

void FsgIpv6::_startHttpHandler(void)
{
    if (m_httpRequestHandler == nullptr) {
        std::cerr << "[SERVER] m_httpRequestHandler is nullptr\n";
        return;
    }
    m_httpRequestHandler->start();
}

void FsgIpv6::write_hvac_power_status(const uint8_t value)
{
    const BapError_t ret = BAP_RequestInt8(lsgId_t::BapLsg_ClimateZone,
                                           fctId_t::BapFct_ClimateZone_FSG_Control,
                                           BapRequest_t::BapReq_Data,
                                           value);
    if (ret != BapError_t::BapErr_OK) {
        std::cerr << "[WRITE] failed to request bap hvac power\n";
    }
}

void FsgIpv6::write_ac_compressor_status(const std::vector<uint8_t> payload)
{
    const BapError_t ret = BAP_RequestByteSequence(lsgId_t::BapLsg_ClimateMaster,
                                                   fctId_t::BapFct_ClimateMaster_AC,
                                                   BapRequest_t::BapReq_Data,
                                                   payload.data(),
                                                   payload.size());
}

void FsgIpv6::write_ac_compressor_eco_max(const std::vector<uint8_t> payload)
{
    const BapError_t ret = BAP_RequestByteSequence(lsgId_t::BapLsg_ClimateMaster,
                                                   fctId_t::BapFct_ClimateMaster_AC,
                                                   BapRequest_t::BapReq_Data,
                                                   payload.data(),
                                                   payload.size());
}

void FsgIpv6::write_hvac_temp_zl(const std::vector<uint8_t> payload)
{
    const BapError_t ret = BAP_RequestByteSequence(lsgId_t::BapLsg_ClimateZone,
                                                   fctId_t::BapFct_ClimateZone_ZL_Temperature,
                                                   BapRequest_t::BapReq_Data,
                                                   payload.data(),
                                                   payload.size());
}

void FsgIpv6::write_hvac_temp_zr(const std::vector<uint8_t> payload)
{
    const BapError_t ret = BAP_RequestByteSequence(lsgId_t::BapLsg_ClimateZone,
                                                   fctId_t::BapFct_ClimateZone_ZR_Temperature,
                                                   BapRequest_t::BapReq_Data,
                                                   payload.data(),
                                                   payload.size());
}

void FsgIpv6::write_hvac_fan_speed_zl(const std::vector<uint8_t> payload)
{
    const BapError_t ret = BAP_RequestByteSequence(lsgId_t::BapLsg_ClimateZone,
                                                   fctId_t::BapFct_ClimateZone_ZL_AirVolume,
                                                   BapRequest_t::BapReq_Data,
                                                   payload.data(),
                                                   payload.size());
}

void FsgIpv6::write_hvac_fan_speed_zr(const std::vector<uint8_t> payload)
{
    const BapError_t ret = BAP_RequestByteSequence(lsgId_t::BapLsg_ClimateZone,
                                                   fctId_t::BapFct_ClimateZone_ZR_AirVolume,
                                                   BapRequest_t::BapReq_Data,
                                                   payload.data(),
                                                   payload.size());
}

void FsgIpv6::write_rvc(const bool value)
{

}

void FsgIpv6::write_seat_climate_zl(const std::vector<uint8_t> payload)
{
    const BapError_t ret = BAP_RequestByteSequence(lsgId_t::BapLsg_ClimateZone,
                                                   fctId_t::BapFct_ClimateZone_ZL_SeatClimate,
                                                   BapRequest_t::BapReq_Data,
                                                   payload.data(),
                                                   payload.size());
    if (ret != BapError_t::BapErr_OK) {
        std::cerr << "[WRITE] failed to send seat climate zl\n";
    }
}

void FsgIpv6::write_seat_climate_zr(const std::vector<uint8_t> payload)
{
    const BapError_t ret = BAP_RequestByteSequence(lsgId_t::BapLsg_ClimateZone,
                                                   fctId_t::BapFct_ClimateZone_ZR_SeatClimate,
                                                   BapRequest_t::BapReq_Data,
                                                   payload.data(),
                                                   payload.size());
}

void FsgIpv6::write_air_circ_manual(const std::vector<uint8_t> payload)
{
    const BapError_t ret = BAP_RequestByteSequence(lsgId_t::BapLsg_ClimateMaster,
                                                   fctId_t::BapFct_ClimateMaster_AirCirculation,
                                                   BapRequest_t::BapReq_Data,
                                                   payload.data(),
                                                   payload.size());
}

void FsgIpv6::write_air_dist_zl(const std::vector<uint8_t> payload)
{
    const BapError_t ret = BAP_RequestByteSequence(lsgId_t::BapLsg_ClimateZone,
                                                   fctId_t::BapFct_ClimateZone_ZL_AirDistribution,
                                                   BapRequest_t::BapReq_Data,
                                                   payload.data(),
                                                   payload.size());
}

void FsgIpv6::write_air_dist_zr(const std::vector<uint8_t> payload)
{
    const BapError_t ret = BAP_RequestByteSequence(lsgId_t::BapLsg_ClimateZone,
                                                   fctId_t::BapFct_ClimateZone_ZR_AirDistribution,
                                                   BapRequest_t::BapReq_Data,
                                                   payload.data(),
                                                   payload.size());
}
