/******************************************************************
 *
 *     Copyright (c) 2006-2023 Audi AG, D-85045 Ingolstadt
 *
 ******************************************************************
 *
 * Project:    BAP
 * Component:  AALB
 * BAP Version: 1.12.2
 *
 ******************************************************************
 *
 * Summary
 *
 *  Header file. Declaration of Aalb interface functions
 *
 ******************************************************************
 *
 * Revision History (w/o SCM)
 *
 * Date        Version     Author       Description
 * ----------------------------------------------------------------
 * 2023-10-10	1.12.2		DRH			[EEARCH-35935] Release preparation, adapt Copyright date and version number.
 * 2022-10-21	1.12.1		DRH			[SSWPPB-296] Release preparation, adapt Copyright date and version number.
 * 2022-06-17	1.12.0		DRH			[SSWPPB-269] Release preparation, adapt Copyright date and version number.
 * 2021-12-07	1.11.3		JEO			[SSWPPB-244] Release preparation, adapt Copyright date and version number.
 * 2021-03-12	1.11.3		JEO			[SSWPPB-142] Fix MISRA violations.
 * 2019-01-28	1.10.99		FFS			[SSWCCB-2647]: Return type changed to void for functions BAP_RxIndication and BAP_TxConfirmation
 * 2017-02-28	1.9.0 		FST			[SSWCCB-1545]: SSW-Lokatierungs-Pragmas eingefuegt
 * 2013-12-04	1.7.0		WWU			[SSWCCB-1521]: Ersetze AALB_VERSION_INFO_API durch BAP_VERSION_INFO_API.
 * 2013-04-15   1.7.0       FRISA       [SSWCCB-1024]: Inkludierung von Can_Cfg/Fr_Cfg je nach Umgebung
 * 2012-03-01	1.6.3		NQU			BAP_MASQUERADE_ASR_API Macro notwendig fuer die ASIL Umgebung
 * 2011-06-03	1.6			WWU			Anpassung fuer Uebergabe-/Rueckgabeparameter von fct BAP_RxIndication,
 * 										BAP_TxConfirmation,BAP_TriggerTransmit
 * 2007-11-14   1.03        MIP         Aalb_Cbk.h changes - include structure
 * 										eingefuehrt
 ******************************************************************/

#ifndef BAP_CBK_H
#define BAP_CBK_H
#ifndef BAP_MASQUERADE_ASR_API	/* ASIL Umgebung Schalter */
#include "ComStack_Types.h"
#include "Platform_Types.h"

#ifndef BAP_TYPES_H
#ifdef BAP_USES_CAN
#include "Can_Cfg.h"
#endif /* BAP_USES_CAN */
#ifdef BAP_USES_FR
#include "Fr_Cfg.h"
#endif /* BAP_USES_FR */
#endif /* #ifndef BAP_TYPES_H */

#else /* BAP_MASQUERADE_ASR_API */
#include "BAP_ComStack_Types.h"
#include "BAP_Platform_Types.h"

#ifndef BAP_TYPES_H
#ifdef BAP_USES_CAN
#include "BAP_Can_Cfg.h"
#endif /* BAP_USES_CAN */
#ifdef BAP_USES_FR
#include "BAP_Fr_Cfg.h"
#endif /* BAP_USES_FR */
#endif /* #ifndef BAP_TYPES_H */

#endif /* #ifndef BAP_MASQUERADE_ASR_API */



/**
 * Version Information capability has to be dis/enabled with
 * pre-compiler switch BAP_VERSION_INFO_API.
 */
#define BAP_VERSION_INFO_API

#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>

extern void BAP_RxIndication(PduIdType AalbRxPduId, const PduInfoType * PduInfoPtr);

extern void BAP_TxConfirmation (PduIdType AalbTxPduId);

extern Std_ReturnType BAP_TriggerTransmit (PduIdType AalbTxPduId, const PduInfoType * PduInfoPtr);

#ifdef BAP_VERSION_INFO_API
extern void BAP_GetVersionInfo(Std_VersionInfoType *aVersionInfo);
#endif /*#ifdef BAP_VERSION_INFO_API*/

#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>

#endif /* BAP_CBK_H */
