#ifndef __ASG_TYPE__
#define __ASG_TYPE__

#include "bap_defines.h"
#include "bap_types.h"

typedef BapError_t cbTxVoid(lsgId_t, fctId_t, BapRequest_t);
typedef BapError_t cbTxInt8(lsgId_t, fctId_t, BapRequest_t, bap_uint8_t);
typedef BapError_t cbTxInt16(lsgId_t, fctId_t, BapRequest_t, bap_uint16_t);
typedef BapError_t cbTxInt32(lsgId_t, fctId_t, BapRequest_t, bap_uint32_t);
typedef BapError_t cbTxByteSequence(lsgId_t, fctId_t, BapRequest_t, const uint8_t*, bap_uint32_t);

typedef void cbRxVoidAcknowledge(lsgId_t, fctId_t, BapAcknowledge_t);
typedef void cbRxVoidError(lsgId_t, fctId_t, BapError_t);
typedef void cbRxVoid(lsgId_t, fctId_t, BapIndication_t);
typedef void cbRxVoidInt8(lsgId_t, fctId_t, BapIndication_t, bap_uint8_t);
typedef void cbRxVoidInt16(lsgId_t, fctId_t, BapIndication_t, bap_uint16_t);
typedef void cbRxVoidInt32(lsgId_t, fctId_t, BapIndication_t, bap_uint32_t);
typedef void cbRxVoidByteSq(lsgId_t, fctId_t, BapIndication_t, const volatile uint8_t*, uint32_t);

#endif // __ASG_TYPE__
