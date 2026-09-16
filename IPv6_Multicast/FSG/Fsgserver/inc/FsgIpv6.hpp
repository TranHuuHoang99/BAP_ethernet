#ifndef __FSG_IPV6_HPP__
#define __FSG_IPV6_HPP__

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
#include <queue>

extern "C" {

#include "bap.h"
#include "bap_util.h"
#include "bap_canubs.h"
#include "palb.h"
#include "bap_defines.h"

} // extern "C"

#include "PDUManager.h"
#include "common/FsgDataBase.hpp"
#include "HttpRequestHandler.hpp"

const std::vector<lsgId_t> lsgId_vec = {
    lsgId_t::BapLsg_ClimateZone,
    lsgId_t::BapLsg_ClimateMaster,
    lsgId_t::BapLsg_ClimateZone2,
    lsgId_t::BapLsg_RDK
};

class FsgIpv6 {
private:
    struct FsgIpv6Token {
        explicit FsgIpv6Token(void) = default;
    };

    void _waitBAPTasks(int32_t time_delay);
    void _heartBeat(void);
    int32_t _initAllSendBuffers(const lsgId_t aLsgId);

    int32_t _initLsg(void);
    int32_t _startLsg(void);
    int32_t _stopLsg(void);
    void _onPduReceived(const PDU& pdu);
    void _tickBap(void);
    void _sendInitialValue(void);
    void _genDataBase(void);
    int32_t _genDataFollowLsgId(const lsgId_t lsgId);
    void _startHttpHandler(void);

public:
    FsgIpv6(FsgIpv6::FsgIpv6Token) {}
    FsgIpv6(const FsgIpv6&) = delete;
    FsgIpv6& operator=(const FsgIpv6&) = delete;
    ~FsgIpv6(void);
    static std::shared_ptr<FsgIpv6> instance(void);

    void acknowledge(const lsgId_t aLsgId,
                     const fctId_t aFctId,
                     const BapAcknowledge_et aeAcknowledge);
    void indicationVoid(const lsgId_t aLsgId,
                        const fctId_t aFctId,
                        const enum BapIndication_t aeIndication);
    void indicationInt8(const lsgId_t aLsgId,
                        const fctId_t aFctId,
                        const enum BapIndication_t aeIndication,
                        const uint8_t au8Value);
    void indicationInt16(const lsgId_t aLsgId,
                         const fctId_t aFctId,
                         const enum BapIndication_t aeIndication,
                         const uint16_t au16Value);
    void indicationInt32(const lsgId_t aLsgId,
                         const fctId_t aFctId,
                         const enum BapIndication_t aeIndication,
                         const uint32_t au32Value);
    void indicationByteSequence(const lsgId_t aLsgId,
                                const fctId_t aFctId,
                                const enum BapIndication_t aeIndication,
                                const volatile uint8_t apValue[],
                                const uint32_t au32Length);
    void indicationError(const lsgId_t aLsgId,
                         const fctId_t aFctId,
                         const enum BapError_t aeErrorCode);
    enum BapError_t sendDebugInfo(DBGVAR const uint8_t pDebugInfo[8]);

    int32_t init(void);
    void start(void);
    int32_t stop(void);
    bool_t transmitTxData(ptr_t apData, const uint16_t au16MsgLength);

    template<typename T>
    const DataType<T> loadData(const lsgId_t lsgId, const fctId_t fctId)
    {
        if (m_dataBase == nullptr) {
            std::cout << "database ptr is nullptr\n";
            return DataType<T>{T{}, 0}; 
        }

        const auto q = m_dataBase->query<T>(lsgId, fctId);
        return q;
    }

    template<typename T>
    int32_t storeData(const lsgId_t lsgId, const fctId_t fctId, const DataType<T> newData)
    {
        if (m_dataBase == nullptr) {
            std::cout << "database ptr is nullptr\n";
            return -1;
        }
        return m_dataBase->write<T>(lsgId, fctId, newData);
    }

    /*
        BAP API
    */
    void write_hvac_power_status(const uint8_t value);
    void write_ac_compressor_status(const std::vector<uint8_t> payload);
    void write_ac_compressor_eco_max(const std::vector<uint8_t> payload);
    void write_hvac_temp_zl(const std::vector<uint8_t> payload);
    void write_hvac_temp_zr(const std::vector<uint8_t> payload);
    void write_hvac_fan_speed_zl(const std::vector<uint8_t> payload);
    void write_hvac_fan_speed_zr(const std::vector<uint8_t> payload);
    void write_rvc(const bool value);
    void write_seat_climate_zl(const std::vector<uint8_t> payload);
    void write_seat_climate_zr(const std::vector<uint8_t> payload);
    void write_air_circ_manual(const std::vector<uint8_t> payload);
    void write_air_dist_zl(const std::vector<uint8_t> payload);
    void write_air_dist_zr(const std::vector<uint8_t> payload);

private:
    std::unique_ptr<PDUManager> m_pduManager;
    std::unique_ptr<DataBase> m_dataBase;
    std::shared_ptr<HttpRequestHandler> m_httpRequestHandler;
    std::mutex m_txMtx;
    std::mutex m_rxMtx;
    std::recursive_mutex m_bapMtx;
    std::recursive_mutex m_bapRecvMtx;
    std::queue<std::vector<uint8_t>> m_rxQueue;
    std::atomic_bool m_bapRunning = false;
    std::thread m_heartBeatThread;

};

#endif // __FSG_IPV6_HPP__
