#include "bap.h"
#include <string.h>
#if defined (CYGWIN_GCC)
#define _UINT32_T_DECLARED
#include <stdio.h>
#include "bap_defines.h"
#define printf printf
#else
#include "stdafx.h"
#endif

#include "FsgIpv6.hpp"

void BAP_Acknowledge(lsgId_t aLsgId, fctId_t aFctId, BapAcknowledge_et aeAcknowledge)
{
    FsgIpv6::instance()->acknowledge(aLsgId, aFctId, aeAcknowledge);
}

void BAP_IndicationVoid(lsgId_t aLsgId, fctId_t aFctId, enum BapIndication_t aeIndication)
{
    FsgIpv6::instance()->indicationVoid(aLsgId, aFctId, aeIndication);
}

void BAP_IndicationInt8(lsgId_t aLsgId,
                        fctId_t aFctId,
                        enum BapIndication_t aeIndication,
                        uint8_t au8Value)
{
	FsgIpv6::instance()->indicationInt8(aLsgId, aFctId, aeIndication, au8Value);
}

void BAP_IndicationInt16(lsgId_t aLsgId,
                         fctId_t aFctId,
                         enum BapIndication_t aeIndication,
                         uint16_t au16Value)
{
	FsgIpv6::instance()->indicationInt16(aLsgId, aFctId, aeIndication, au16Value);
}

void BAP_IndicationInt32(lsgId_t aLsgId,
                         fctId_t aFctId,
                         enum BapIndication_t aeIndication,
                         uint32_t au32Value)
{
	FsgIpv6::instance()->indicationInt32(aLsgId, aFctId, aeIndication, au32Value);
}

void BAP_IndicationByteSequence(lsgId_t aLsgId,
                                fctId_t aFctId,
                                enum BapIndication_t aeIndication,
                                const volatile uint8_t apValue[],
                                uint32_t au32Length)
{
	FsgIpv6::instance()->indicationByteSequence(aLsgId,
                                                   aFctId,
                                                   aeIndication,
                                                   apValue,
                                                   au32Length);
}

void BAP_IndicationError(lsgId_t aLsgId,
                         fctId_t aFctId,
                         enum BapError_t aeErrorCode)
{
	FsgIpv6::instance()->indicationError(aLsgId, aFctId, aeErrorCode);
}

enum BapError_t BAP_SendDebugInfo(DBGVAR const uint8_t pDebugInfo[8])
{
	
    const BapError_t ret_code = FsgIpv6::instance()->sendDebugInfo(pDebugInfo);
    return ret_code;
}
