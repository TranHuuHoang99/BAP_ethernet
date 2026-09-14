#ifndef __ASG_MANAGER__
#define __ASG_MANAGER__

#include <iostream>
#include <stdio.h>
#include <string>
#include <memory>
#include <stdlib.h>
#include <thread>
#include <vector>

extern "C" {

#include "bap.h"
#include "bap_defines.h"
#include "bap_util.h"
#include "bap_canubs.h"
#include "palb.h"

} // extern "C"

#include "EthernetHandler.hpp"
#include "GTHandler.hpp"
#include "asg_mapping.hpp"

/* define all lsg machine need to connect with */
const std::vector<lsgId_t> lsgId_vec = {
    lsgId_t::BapLsg_ClimateMaster,
    lsgId_t::BapLsg_ClimateZone
};

class ASGManager {
private:
    struct ASGManagerToken {
        explicit ASGManagerToken(void) = default;
    };

    void _waitBAPTasks(int32_t time_delay);

    /* HVAC transfer data to Linux */
    /* CLIMATE ZONE 1 */
    void _rx_Fsg_control_acknowledge_fctId_13(const lsgId_t lsgId,
                                              const fctId_t fctId,
                                              const BapAcknowledge_t ackCode);
    void _rx_Fsg_control_error_fctId_13(const lsgId_t lsgId,
                                        const fctId_t fctId,
                                        const BapError_t err);
    void _rx_Fsg_control_fctId_13(const lsgId_t lsgId,
                                  const fctId_t fctId,
                                  const BapIndication_t cmd,
                                  const uint8_t data);

    void _rx_ZL_Temperature_acknowledge_fctId_16(const lsgId_t lsgId,
                                                 const fctId_t fctId,
                                                 const BapAcknowledge_t ackCode);
    void _rx_ZL_Temperature_error_fctId_16(const lsgId_t lsgId,
                                           const fctId_t fctId,
                                           const BapError_t err);
    void _rx_ZL_Temperature_fctId_16(const lsgId_t lsgId,
                                     const fctId_t fctId,
                                     const BapIndication_t cmd,
                                     const volatile uint8_t* data,
                                     const uint32_t len);

    void _rx_ZR_Temperature_acknowledge_fctId_17(const lsgId_t lsgId,
                                                 const fctId_t fctId,
                                                 const BapAcknowledge_t ackCode);
    void _rx_ZR_Temperature_error_fctId_17(const lsgId_t lsgId,
                                           const fctId_t fctId,
                                           const BapError_t err);
    void _rx_ZR_Temperature_fctId_17(const lsgId_t lsgId,
                                     const fctId_t fctId,
                                     const BapIndication_t cmd,
                                     const volatile uint8_t* data,
                                     const uint32_t len);

    void _rx_ZL_AirVolume_acknowledge_fctId_18(const lsgId_t lsgId,
                                               const fctId_t fctId,
                                               const BapAcknowledge_t ackCode);
    void _rx_ZL_AirVolume_error_fctId_18(const lsgId_t lsgId,
                                         const fctId_t fctId,
                                         const BapError_t err);
    void _rx_ZL_AirVolume_fctId_18(const lsgId_t lsgId,
                                   const fctId_t fctId,
                                   const BapIndication_t cmd,
                                   const volatile uint8_t* data,
                                   const uint32_t len);

    void _rx_ZR_AirVolume_acknowledge_fctId_19(const lsgId_t lsgId,
                                               const fctId_t fctId,
                                               const BapAcknowledge_t ackCode);
    void _rx_ZR_AirVolume_error_fctId_19(const lsgId_t lsgId,
                                         const fctId_t fctId,
                                         const BapError_t err);
    void _rx_ZR_AirVolume_fctId_19(const lsgId_t lsgId,
                                   const fctId_t fctId,
                                   const BapIndication_t cmd,
                                   const volatile uint8_t* data,
                                   const uint32_t len);

    /* CLIMATE MASTER ZONE */
    void _rx_ClimateMaster_AC_acknowledge_fctId_16(const lsgId_t lsgId,
                                                   const fctId_t fctId,
                                                   const BapAcknowledge_t ackCode);
    void _rx_ClimateMaster_AC_error_fctId_16(const lsgId_t lsgId,
                                             const fctId_t fctId,
                                             const BapError_t err);
    void _rx_ClimateMaster_AC_fctId_16(const lsgId_t lsgId,
                                     const fctId_t fctId,
                                     const BapIndication_t cmd,
                                     const volatile uint8_t* data,
                                     const uint32_t len);

    void _registerTxFunction(void);
    void _registerRxFunction(void);
    void _generateDataBase(void);
    int32_t _initLsg(void);
    int32_t _startLsg(void);
    int32_t _stopLsg(void);

public:
    ASGManager(ASGManager::ASGManagerToken) {}
    ASGManager(const ASGManager&) = delete;
    ASGManager& operator=(const ASGManager&) = delete;
    ~ASGManager(void);
    static std::shared_ptr<ASGManager> instance(void);

    /* definition for BAP function not use for invoking */
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
    bool_t transmitTxData(ptr_t apData, const uint16_t au16MsgLength);
    /* ------------------------------------------------ */

    int32_t init(void);
    void start(void);
    int32_t stop(void);

    void txByteSequence(const lsgId_t lsgId,
                        const fctId_t fctId,
                        const enum BapRequest_t cmd,
                        const uint8_t apValue[],
                        const uint32_t au32Length);

    void txSingleVal(const lsgId_t lsgId,
                     const fctId_t fctId,
                     const enum BapRequest_t cmd,
                     const std::optional<std::any> any_data);

private:
    uint8_t m_buffer[BAP_MAX_PDU_SIZE + BAP_SOAD_HEADER_SIZE];
    std::shared_ptr<EthernetHandler> m_ethernetHandler;
    std::shared_ptr<GTHandler> m_gtHandler;
    std::shared_ptr<ClimateLoadBalancer> m_climateLoadBalancer;
};

#endif // __ASG_MANAGER__
