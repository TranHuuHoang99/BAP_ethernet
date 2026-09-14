#ifndef __FSG_MANAGER__
#define __FSG_MANAGER__

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

extern "C" {

#include "bap.h"
#include "bap_defines.h"
#include "bap_util.h"
#include "bap_canubs.h"
#include "palb.h"

} // extern "C"

const std::vector<lsgId_t> lsgId_vec = {
    lsgId_t::BapLsg_ClimateMaster,
    lsgId_t::BapLsg_ClimateZone
};

class FSGManager {
private:
    struct FSGManagerToken {
        explicit FSGManagerToken(void) = default;
    };

    void _ethernetEventListener(void);
    void _waitBAPTasks(int32_t time_delay);
    int32_t _initAllSendBuffers(const lsgId_t aLsgId);

    int32_t _initLsg(void);
    int32_t _startLsg(void);
    int32_t _stopLsg(void);

public:
    FSGManager(FSGManager::FSGManagerToken) {}
    FSGManager(const FSGManager&) = delete;
    FSGManager& operator=(const FSGManager&) = delete;
    ~FSGManager(void);
    static std::shared_ptr<FSGManager> instance(void);

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

private:
    int32_t m_server_fd = -1;
    struct sockaddr_in m_client_addr;
    socklen_t m_client_len = 0;
    uint8_t m_buffer[BAP_MAX_PDU_SIZE + BAP_SOAD_HEADER_SIZE];
    std::thread m_fsg_listener;
    bool m_startEventListener = false;
    uint8_t m_leftZoneTemp = 0u;
    uint8_t m_rightZoneTemp = 0u;
    bool m_client_connected = false;
};

#endif // __FSG_MANAGER__
