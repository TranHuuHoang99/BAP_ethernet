/******************************************************************
 *
 *     Copyright (c) 2003-2023 Volkswagen AG, D-38436 Wolfsburg
 *
 ******************************************************************
 *
 * Projekt:    BAP
 * Komponente: Konfiguration
 *
 *
 ******************************************************************
 *
 * Beschreibung
 *
 * Generierte Konfigurationsdatei fuer den BAP Protokoll-Stack.
 * Diese Datei darf nicht manuell veraendert werden.
 *
 ******************************************************************
 * Generiert am:    18.08.2026
 *           um:    15:41:00
 * Quelldatei:      C:\workspace\sample_project\POC_8255\backup\FSG\BAP_SW1.10_ClimateZone_P30DF79_V5.90_FSG.xml
 * Zieldatei:       C:\workspace\sample_project\POC_8255\backup\FSG\BAP_SW1.10_ClimateZone_P30DF79_V5.90_FSG.c
 *
 * BAPgen Version:  1.12.2
 * BAPgen Stand:    10.10.2023
 ******************************************************************/

/* Systemincludes mit <...> */

/*lint -e651 -e64 -e740 -e826 -e754 -e708 -e545 -e961 */

/* Eigene Header-Dateien "..." */
#include "bap_types.h"
#include "bap_privatetypes.h"
#include "bap_balconfig.h"
#include "bap_bplconfig.h"
#include "bap_bclconfig.h"
#include "bap_config.h"
#include "bap.h"

/* Bibliotheken von externen Herstellen mit <...> */
#include "can_fsg.h"
#ifdef BAP_USES_CAN
#include "can_inc.h"
#endif

/* Makro-Definitionen */
#ifndef BAP_ROM_CONST
#define BAP_ROM_CONST
#endif

#ifndef BAP_RAM_DATA_FAR
#define BAP_RAM_DATA_FAR
#endif

#ifndef BAP_ROM_DATA_FAR
#define BAP_ROM_DATA_FAR
#endif
#if BAP_VERSION != 11220
#error Datei ist nicht kompatibel mit der Version des BAP-Stacks. Bitte diese Datei noch einmal mit dem mitgeliefertem BAPgen aus der XML-Datei generieren.
#endif

#ifdef BAP_USES_EXCLUSIVE_ADDRESS 
#if (BAP_VERSION_MINOR < 7u) && (BAP_VERSION_MAJOR == 1u) 
#error Erweiterte Adressierungsart ist nicht in dieser BAP-Version unterstuetzt. Bitte verwenden Sie BAP Version ab 1.7.0.
#endif /* BAP_VERSION_MINOR */
#endif /* BAP_USES_EXCLUSIVE_ADDRESS */

#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
/* BAP LsgRamRow Tabelle ******************************************************/
BAP_RAM_DATA_FAR BapLsgRamRow_ot BAP_LsgRamTable[]=
{
    /* eLsgStatus, u16HeartbeatTimer, eHeartbeatStatus, u8LastSentFctIndex, BAP_BAPConfigTable[BAP_FCTID_BAPCONFIG_SIZE], BAP_aru8FunctionList[BAP_FCTID_FCTLIST_SIZE], fState */
    {BapLayerLsgStat_NoInit, 0u, BapBplStat_Stopped, 0u, {0u, 0u, 0u, 0u, 0u, 0u}, {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u}, {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u} },
    {BapLayerLsgStat_NoInit, 0u, BapBplStat_Stopped, 0u, {0u, 0u, 0u, 0u, 0u, 0u}, {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u}, {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u} }
};

/* CAN-TX und LsgID Zuordnungstabelle *********************************************************/
BAP_ROM_DATA_FAR BapCanMsg2LsgMapping_ot BAP_ROM_CONST BAP_CanTxMsgToLsgMappingTable[]=
{
	/* CanTxMessage, 		 LsgId */
	{(BapCanMsgId_t) BAP_KlimaMaster_FSG_01, 	(lsgId_t) 66}
};

/* CAN-RX und LsgID Zuordnungstabelle *********************************************************/
BAP_ROM_DATA_FAR BapCanMsg2LsgMapping_ot BAP_ROM_CONST BAP_CanRxMsgToLsgMappingTable[]=
{
	/* CanRxMessage, 		 LsgId */
	{(BapCanMsgId_t) BAP_KlimaMaster_ASG_04, 	(lsgId_t) 66},
	{(BapCanMsgId_t) BAP_KlimaMaster_ASG_03, 	(lsgId_t) 66},
	{(BapCanMsgId_t) BAP_KlimaMaster_ASG_02, 	(lsgId_t) 66},
	{(BapCanMsgId_t) BAP_KlimaMaster_ASG_01, 	(lsgId_t) 66},
};

#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
#define BAP_START_SEC_CONST_UNSPECIFIED
#include <BAP_MemMap.h>
/* CAN-TX und PDU_Size Zuordnungstabelle *********************************************************/
BAP_ROM_DATA_FAR BapMsgPduSize_ot BAP_ROM_CONST BAP_CanTxMsgPduSizeTable[]=
{
	/* CanTxMessage, 						PDU_Size */
	{(BapCanMsgId_t) BAP_Klima1_FSG_01, 	(uint16_t) 8},
	{(BapCanMsgId_t) BAP_KlimaMaster_FSG_01, 	(uint16_t) 8}
};

/* CAN-RX und PDU_Size Zuordnungstabelle *********************************************************/
BAP_ROM_DATA_FAR BapMsgPduSize_ot BAP_ROM_CONST BAP_CanRxMsgPduSizeTable[]=
{
	/* CanRxMessage, 						PDU_Size */
	{(BapCanMsgId_t) BAP_KlimaMaster_ASG_04, 	(uint16_t) 8},
	{(BapCanMsgId_t) BAP_KlimaMaster_ASG_03, 	(uint16_t) 8},
	{(BapCanMsgId_t) BAP_KlimaMaster_ASG_02, 	(uint16_t) 8},
	{(BapCanMsgId_t) BAP_KlimaMaster_ASG_01, 	(uint16_t) 8},
	{(BapCanMsgId_t) BAP_Klima1_ASG_04, 	(uint16_t) 8},
	{(BapCanMsgId_t) BAP_Klima1_ASG_03, 	(uint16_t) 8},
	{(BapCanMsgId_t) BAP_Klima1_ASG_02, 	(uint16_t) 8},
	{(BapCanMsgId_t) BAP_Klima1_ASG_01, 	(uint16_t) 8}
};
#define BAP_STOP_SEC_CONST_UNSPECIFIED
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/*------- BAL ------*/

/*Hier befinden sich die Caches der Funktionen mit cacheAvailable="true"*/
/*------- BPL ------*/

/* BPL RAM Tabelle ************************************************************/
/* fuer alle Funktionen mit maxRetryTimer>0                                   */
BAP_RAM_DATA_FAR
BapBplRamRow_ot BAP_BplRamTable[]={
    /* bOngoingStatusAll, u16RetryOrProcessingTimer, fRetryOrProcessingFlags */
    {(uint8_t) 0, (uint16_t) 0, {0u,0u,0u}}
};

/* BPL HeartbeatTimer *********************************************************/
/* pro LSG ein HeartbeatTimer                                                 */
BAP_RAM_DATA_FAR
uint16_t BAP_BplHeartbeatTimerTable[]={
    (uint16_t) 0,
    (uint16_t) 0
};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>



/*------- BCL ------*/

/*------- RX-Buffer -------*/
/* Buffer for Function  lsg.id=1 fct.id=16*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer0[6];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer0 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 6, (paru8Buffer_t)&aru8BclRxBuffer0}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=17*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer1[6];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer1 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 6, (paru8Buffer_t)&aru8BclRxBuffer1}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=18*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer2[4];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer2 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 4, (paru8Buffer_t)&aru8BclRxBuffer2}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=19*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer3[4];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer3 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 4, (paru8Buffer_t)&aru8BclRxBuffer3}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=20*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer4[5];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer4 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 5, (paru8Buffer_t)&aru8BclRxBuffer4}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=21*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer5[5];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer5 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 5, (paru8Buffer_t)&aru8BclRxBuffer5}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=22*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer6[7];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer6 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 7, (paru8Buffer_t)&aru8BclRxBuffer6}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=23*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer7[7];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer7 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 7, (paru8Buffer_t)&aru8BclRxBuffer7}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=24*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer8[4];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer8 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 4, (paru8Buffer_t)&aru8BclRxBuffer8}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=25*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer9[4];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer9 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 4, (paru8Buffer_t)&aru8BclRxBuffer9}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=26*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer10[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer10 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclRxBuffer10}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=27*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer11[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer11 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclRxBuffer11}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=30*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer12[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer12 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclRxBuffer12}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=31*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer13[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer13 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclRxBuffer13}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=32*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer14[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer14 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclRxBuffer14}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=33*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer15[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer15 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclRxBuffer15}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=34*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer16[5];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer16 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 5, (paru8Buffer_t)&aru8BclRxBuffer16}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=35*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer17[5];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer17 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 5, (paru8Buffer_t)&aru8BclRxBuffer17}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=36*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer18[112];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer18 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 112, (paru8Buffer_t)&aru8BclRxBuffer18}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=37*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer19[1];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer19 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 1, (paru8Buffer_t)&aru8BclRxBuffer19}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=39*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer20[4];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer20 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 4, (paru8Buffer_t)&aru8BclRxBuffer20}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=40*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer21[4];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer21 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 4, (paru8Buffer_t)&aru8BclRxBuffer21}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=41*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer22[5];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer22 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 5, (paru8Buffer_t)&aru8BclRxBuffer22}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=43*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer23[9];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer23 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 9, (paru8Buffer_t)&aru8BclRxBuffer23}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=44*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer24[9];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer24 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 9, (paru8Buffer_t)&aru8BclRxBuffer24}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=45*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer25[4];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer25 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 4, (paru8Buffer_t)&aru8BclRxBuffer25}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=46*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer26[6];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer26 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 6, (paru8Buffer_t)&aru8BclRxBuffer26}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=47*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer27[6];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer27 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 6, (paru8Buffer_t)&aru8BclRxBuffer27}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=48*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer28[8];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer28 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 8, (paru8Buffer_t)&aru8BclRxBuffer28}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=49*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer29[8];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer29 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 8, (paru8Buffer_t)&aru8BclRxBuffer29}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=50*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer30[6];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer30 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 6, (paru8Buffer_t)&aru8BclRxBuffer30}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=51*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer31[6];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer31 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 6, (paru8Buffer_t)&aru8BclRxBuffer31}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=16*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer32[2];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer32 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 2, (paru8Buffer_t)&aru8BclRxBuffer32}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=17*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer33[2];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer33 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 2, (paru8Buffer_t)&aru8BclRxBuffer33}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=18*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer34[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer34 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclRxBuffer34}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=19*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer35[2];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer35 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 2, (paru8Buffer_t)&aru8BclRxBuffer35}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=20*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer36[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer36 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclRxBuffer36}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=21*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer37[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer37 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclRxBuffer37}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=22*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer38[9];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer38 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 9, (paru8Buffer_t)&aru8BclRxBuffer38}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=23*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer39[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer39 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclRxBuffer39}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=24*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer40[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer40 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclRxBuffer40}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=25*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer41[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer41 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclRxBuffer41}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=26*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer42[4];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer42 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 4, (paru8Buffer_t)&aru8BclRxBuffer42}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=27*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer43[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer43 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclRxBuffer43}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=28*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer44[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer44 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclRxBuffer44}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=29*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer45[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer45 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclRxBuffer45}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=30*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer46[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer46 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclRxBuffer46}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=31*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer47[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer47 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclRxBuffer47}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=32*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer48[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer48 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclRxBuffer48}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=33*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer49[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer49 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclRxBuffer49}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=34*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer50[6];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer50 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 6, (paru8Buffer_t)&aru8BclRxBuffer50}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=35*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer51[6];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer51 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 6, (paru8Buffer_t)&aru8BclRxBuffer51}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=37*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer52[6];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer52 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 6, (paru8Buffer_t)&aru8BclRxBuffer52}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=38*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer53[18];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer53 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 18, (paru8Buffer_t)&aru8BclRxBuffer53}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=39*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer54[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer54 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclRxBuffer54}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=40*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer55[273];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer55 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 273, (paru8Buffer_t)&aru8BclRxBuffer55}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=41*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer56[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer56 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclRxBuffer56}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=42*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer57[44];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer57 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 44, (paru8Buffer_t)&aru8BclRxBuffer57}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=43*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer58[6];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer58 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 6, (paru8Buffer_t)&aru8BclRxBuffer58}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=44*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer59[6];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer59 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 6, (paru8Buffer_t)&aru8BclRxBuffer59}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=45*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer60[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer60 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclRxBuffer60}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=46*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer61[4];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer61 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 4, (paru8Buffer_t)&aru8BclRxBuffer61}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=48*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclRxBuffer62[6];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclRxRamRow_ot BCL_RxBuffer62 = {
				{
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fRxInProgressFlag */
#endif
				(uint8_t)0, /* fRxCompleteFlag */
				(uint8_t)0, /* fRxErrorFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 6, (paru8Buffer_t)&aru8BclRxBuffer62}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/*------- TX-Buffer -------*/
/* Buffer for Function  lsg.id=1 fct.id=1*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer0[214];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer0 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 214, (paru8Buffer_t)&aru8BclTxBuffer0}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=2*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer1[6];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer1 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 6, (paru8Buffer_t)&aru8BclTxBuffer1}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=3*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer2[8];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer2 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 8, (paru8Buffer_t)&aru8BclTxBuffer2}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=4*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer3[1];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer3 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 1, (paru8Buffer_t)&aru8BclTxBuffer3}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=13*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer4[1];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer4 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 1, (paru8Buffer_t)&aru8BclTxBuffer4}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=14*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer5[11];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer5 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 11, (paru8Buffer_t)&aru8BclTxBuffer5}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=15*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer6[1];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer6 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 1, (paru8Buffer_t)&aru8BclTxBuffer6}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=16*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer7[6];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer7 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 6, (paru8Buffer_t)&aru8BclTxBuffer7}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=17*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer8[6];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer8 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 6, (paru8Buffer_t)&aru8BclTxBuffer8}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=18*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer9[4];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer9 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 4, (paru8Buffer_t)&aru8BclTxBuffer9}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=19*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer10[4];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer10 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 4, (paru8Buffer_t)&aru8BclTxBuffer10}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=20*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer11[5];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer11 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 5, (paru8Buffer_t)&aru8BclTxBuffer11}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=21*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer12[5];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer12 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 5, (paru8Buffer_t)&aru8BclTxBuffer12}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=22*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer13[7];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer13 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 7, (paru8Buffer_t)&aru8BclTxBuffer13}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=23*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer14[7];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer14 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 7, (paru8Buffer_t)&aru8BclTxBuffer14}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=24*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer15[4];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer15 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 4, (paru8Buffer_t)&aru8BclTxBuffer15}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=25*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer16[4];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer16 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 4, (paru8Buffer_t)&aru8BclTxBuffer16}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=26*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer17[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer17 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclTxBuffer17}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=27*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer18[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer18 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclTxBuffer18}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=28*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer19[2];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer19 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 2, (paru8Buffer_t)&aru8BclTxBuffer19}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=29*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer20[2];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer20 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 2, (paru8Buffer_t)&aru8BclTxBuffer20}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=30*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer21[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer21 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclTxBuffer21}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=31*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer22[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer22 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclTxBuffer22}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=32*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer23[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer23 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclTxBuffer23}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=33*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer24[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer24 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclTxBuffer24}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=34*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer25[5];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer25 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 5, (paru8Buffer_t)&aru8BclTxBuffer25}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=35*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer26[5];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer26 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 5, (paru8Buffer_t)&aru8BclTxBuffer26}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=36*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer27[113];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer27 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 113, (paru8Buffer_t)&aru8BclTxBuffer27}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=37*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer28[1];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer28 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 1, (paru8Buffer_t)&aru8BclTxBuffer28}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=38*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer29[2];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer29 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 2, (paru8Buffer_t)&aru8BclTxBuffer29}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=39*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer30[4];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer30 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 4, (paru8Buffer_t)&aru8BclTxBuffer30}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=40*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer31[4];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer31 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 4, (paru8Buffer_t)&aru8BclTxBuffer31}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=41*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer32[5];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer32 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 5, (paru8Buffer_t)&aru8BclTxBuffer32}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=42*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer33[11];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer33 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 11, (paru8Buffer_t)&aru8BclTxBuffer33}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=43*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer34[9];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer34 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 9, (paru8Buffer_t)&aru8BclTxBuffer34}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=44*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer35[9];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer35 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 9, (paru8Buffer_t)&aru8BclTxBuffer35}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=45*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer36[25];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer36 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 25, (paru8Buffer_t)&aru8BclTxBuffer36}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=46*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer37[6];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer37 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 6, (paru8Buffer_t)&aru8BclTxBuffer37}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=47*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer38[6];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer38 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 6, (paru8Buffer_t)&aru8BclTxBuffer38}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=48*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer39[8];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer39 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 8, (paru8Buffer_t)&aru8BclTxBuffer39}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=49*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer40[8];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer40 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 8, (paru8Buffer_t)&aru8BclTxBuffer40}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=50*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer41[6];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer41 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 6, (paru8Buffer_t)&aru8BclTxBuffer41}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=1 fct.id=51*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer42[6];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer42 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 6, (paru8Buffer_t)&aru8BclTxBuffer42}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=1*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer43[170];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer43 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 170, (paru8Buffer_t)&aru8BclTxBuffer43}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=2*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer44[6];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer44 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 6, (paru8Buffer_t)&aru8BclTxBuffer44}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=3*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer45[8];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer45 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 8, (paru8Buffer_t)&aru8BclTxBuffer45}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=4*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer46[1];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer46 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 1, (paru8Buffer_t)&aru8BclTxBuffer46}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=13*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer47[1];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer47 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 1, (paru8Buffer_t)&aru8BclTxBuffer47}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=14*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer48[8];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer48 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 8, (paru8Buffer_t)&aru8BclTxBuffer48}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=15*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer49[1];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer49 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 1, (paru8Buffer_t)&aru8BclTxBuffer49}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=16*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer50[2];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer50 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 2, (paru8Buffer_t)&aru8BclTxBuffer50}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=17*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer51[2];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer51 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 2, (paru8Buffer_t)&aru8BclTxBuffer51}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=18*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer52[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer52 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclTxBuffer52}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=19*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer53[2];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer53 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 2, (paru8Buffer_t)&aru8BclTxBuffer53}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=20*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer54[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer54 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclTxBuffer54}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=21*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer55[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer55 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclTxBuffer55}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=22*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer56[9];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer56 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 9, (paru8Buffer_t)&aru8BclTxBuffer56}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=23*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer57[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer57 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclTxBuffer57}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=24*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer58[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer58 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclTxBuffer58}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=25*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer59[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer59 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclTxBuffer59}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=26*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer60[4];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer60 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 4, (paru8Buffer_t)&aru8BclTxBuffer60}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=27*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer61[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer61 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclTxBuffer61}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=28*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer62[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer62 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclTxBuffer62}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=29*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer63[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer63 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclTxBuffer63}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=30*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer64[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer64 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclTxBuffer64}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=31*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer65[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer65 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclTxBuffer65}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=32*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer66[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer66 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclTxBuffer66}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=33*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer67[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer67 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclTxBuffer67}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=34*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer68[6];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer68 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 6, (paru8Buffer_t)&aru8BclTxBuffer68}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=35*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer69[6];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer69 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 6, (paru8Buffer_t)&aru8BclTxBuffer69}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=36*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer70[6];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer70 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 6, (paru8Buffer_t)&aru8BclTxBuffer70}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=37*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer71[6];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer71 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 6, (paru8Buffer_t)&aru8BclTxBuffer71}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=38*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer72[18];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer72 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 18, (paru8Buffer_t)&aru8BclTxBuffer72}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=39*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer73[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer73 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclTxBuffer73}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=40*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer74[276];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer74 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 276, (paru8Buffer_t)&aru8BclTxBuffer74}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=41*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer75[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer75 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclTxBuffer75}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=42*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer76[45];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer76 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 45, (paru8Buffer_t)&aru8BclTxBuffer76}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=43*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer77[6];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer77 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 6, (paru8Buffer_t)&aru8BclTxBuffer77}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=44*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer78[6];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer78 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 6, (paru8Buffer_t)&aru8BclTxBuffer78}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=45*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer79[3];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer79 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 3, (paru8Buffer_t)&aru8BclTxBuffer79}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=46*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer80[4];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer80 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 4, (paru8Buffer_t)&aru8BclTxBuffer80}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=47*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer81[6];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer81 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 6, (paru8Buffer_t)&aru8BclTxBuffer81}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Buffer for Function  lsg.id=66 fct.id=48*/
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer82[6];
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR BapBclTxRamRow_ot BCL_TxBuffer82 = {
				{
#ifdef BAP_USES_ACKNOWLEDGE
				(uint8_t)0, /* fTxRequestNeedsAckFlag */
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				(uint8_t)0, /* fTxErrorNeedsAckFlag */
#endif
				(uint8_t)0, /* fTxRequestFlag */
#ifdef BAP_USES_SEGMENTATION
				(uint8_t)0, /* fTxInProgressFlag */
#endif
#ifdef BAP_FSG
				(uint8_t)0, /* fTxErrorFlag */
				(uint8_t)0, /* fTxInitializedFlag */
#endif
				(uint8_t)0 /* fTxSendBufferFlag */
				}, BapErr_OK, (BapOpCodes_et) 0, {(uint32_t) 6, (paru8Buffer_t)&aru8BclTxBuffer82}};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>


#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
/* BAP BCL Inhibit Timer Tabelle **********************************************/
/* pro TxCanId ein Eintrag                                                    */
BAP_RAM_DATA_FAR
BapInhibitRamRow_ot BAP_InhibitRamTable[]=
{
    /* u16InhibitTimer, u8HeuristikLsgIndex, u8HeuristikFctIndex, oHeuristikFlags */
    /* BAP_Klima1_FSG_01 */ {0u,0u,0u,{0u,0u}},
    /* BAP_KlimaMaster_FSG_01 */ {0u,0u,0u,{0u,0u}}
};

#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>


#define BAP_START_SEC_CONST_UNSPECIFIED
#include <BAP_MemMap.h>
/* BAP BCL Inhibit ROM Tabelle ***********************************************/
BAP_ROM_DATA_FAR BapInhibitRomRow_ot BAP_ROM_CONST BAP_InhibitRomTable []=
{
    /* u16ConfiguredInhibitTime, canMsgId, u16MapCanIdToLsgTableIndex, u8MapCanIdToLsgSize, u16MapCanIdByLsgTableIndex, u8MapCanIdByLsgSize, u8InterfaceNumber */
    {8u, (BapCanMsgId_t) BAP_Klima1_FSG_01, 0u, 1u, 0u, 43u, 20u},
    {5u, (BapCanMsgId_t) BAP_KlimaMaster_FSG_01, 1u, 1u, 43u, 40u, 20u}
};

#define BAP_STOP_SEC_CONST_UNSPECIFIED
#include <BAP_MemMap.h>

#define BAP_START_SEC_CONST_UNSPECIFIED
#include <BAP_MemMap.h>
/* BAP BCL InterTelegram Timer Abbildungstabelle ******************************/
BAP_ROM_DATA_FAR BapInterTelegramTimerMapRow_ot BAP_ROM_CONST BAP_InterTelegramTimerMappingTable[]=
{
    /* lsgId, fctId */
    {(lsgId_t)1,(fctId_t)22},
    {(lsgId_t)1,(fctId_t)22},
    {(lsgId_t)1,(fctId_t)22},
    {(lsgId_t)1,(fctId_t)22},
    {(lsgId_t)1,(fctId_t)23},
    {(lsgId_t)1,(fctId_t)23},
    {(lsgId_t)1,(fctId_t)23},
    {(lsgId_t)1,(fctId_t)23},
    {(lsgId_t)1,(fctId_t)36},
    {(lsgId_t)1,(fctId_t)36},
    {(lsgId_t)1,(fctId_t)36},
    {(lsgId_t)1,(fctId_t)36},
    {(lsgId_t)1,(fctId_t)43},
    {(lsgId_t)1,(fctId_t)43},
    {(lsgId_t)1,(fctId_t)43},
    {(lsgId_t)1,(fctId_t)43},
    {(lsgId_t)1,(fctId_t)44},
    {(lsgId_t)1,(fctId_t)44},
    {(lsgId_t)1,(fctId_t)44},
    {(lsgId_t)1,(fctId_t)44},
    {(lsgId_t)1,(fctId_t)45},
    {(lsgId_t)1,(fctId_t)45},
    {(lsgId_t)1,(fctId_t)45},
    {(lsgId_t)1,(fctId_t)45},
    {(lsgId_t)1,(fctId_t)48},
    {(lsgId_t)1,(fctId_t)48},
    {(lsgId_t)1,(fctId_t)48},
    {(lsgId_t)1,(fctId_t)48},
    {(lsgId_t)1,(fctId_t)49},
    {(lsgId_t)1,(fctId_t)49},
    {(lsgId_t)1,(fctId_t)49},
    {(lsgId_t)1,(fctId_t)49},
    {(lsgId_t)66,(fctId_t)22},
    {(lsgId_t)66,(fctId_t)22},
    {(lsgId_t)66,(fctId_t)22},
    {(lsgId_t)66,(fctId_t)22},
    {(lsgId_t)66,(fctId_t)38},
    {(lsgId_t)66,(fctId_t)38},
    {(lsgId_t)66,(fctId_t)38},
    {(lsgId_t)66,(fctId_t)38},
    {(lsgId_t)66,(fctId_t)40},
    {(lsgId_t)66,(fctId_t)42},
    {(lsgId_t)66,(fctId_t)42},
    {(lsgId_t)66,(fctId_t)42},
    {(lsgId_t)66,(fctId_t)42}
};

#define BAP_STOP_SEC_CONST_UNSPECIFIED
#include <BAP_MemMap.h>


#define BAP_START_SEC_VAR_INIT_16
#include <BAP_MemMap.h>
/* BAP BCL InterTelegram Timer Tabelle ****************************************/
BAP_RAM_DATA_FAR
uint16_t BAP_u16InterTelegramTimerTable[]=
{
    /* {(lsgId_t)1,(fctId_t)22} */ 0u,
    /* {(lsgId_t)1,(fctId_t)22} */ 0u,
    /* {(lsgId_t)1,(fctId_t)22} */ 0u,
    /* {(lsgId_t)1,(fctId_t)22} */ 0u,
    /* {(lsgId_t)1,(fctId_t)23} */ 0u,
    /* {(lsgId_t)1,(fctId_t)23} */ 0u,
    /* {(lsgId_t)1,(fctId_t)23} */ 0u,
    /* {(lsgId_t)1,(fctId_t)23} */ 0u,
    /* {(lsgId_t)1,(fctId_t)36} */ 0u,
    /* {(lsgId_t)1,(fctId_t)36} */ 0u,
    /* {(lsgId_t)1,(fctId_t)36} */ 0u,
    /* {(lsgId_t)1,(fctId_t)36} */ 0u,
    /* {(lsgId_t)1,(fctId_t)43} */ 0u,
    /* {(lsgId_t)1,(fctId_t)43} */ 0u,
    /* {(lsgId_t)1,(fctId_t)43} */ 0u,
    /* {(lsgId_t)1,(fctId_t)43} */ 0u,
    /* {(lsgId_t)1,(fctId_t)44} */ 0u,
    /* {(lsgId_t)1,(fctId_t)44} */ 0u,
    /* {(lsgId_t)1,(fctId_t)44} */ 0u,
    /* {(lsgId_t)1,(fctId_t)44} */ 0u,
    /* {(lsgId_t)1,(fctId_t)45} */ 0u,
    /* {(lsgId_t)1,(fctId_t)45} */ 0u,
    /* {(lsgId_t)1,(fctId_t)45} */ 0u,
    /* {(lsgId_t)1,(fctId_t)45} */ 0u,
    /* {(lsgId_t)1,(fctId_t)48} */ 0u,
    /* {(lsgId_t)1,(fctId_t)48} */ 0u,
    /* {(lsgId_t)1,(fctId_t)48} */ 0u,
    /* {(lsgId_t)1,(fctId_t)48} */ 0u,
    /* {(lsgId_t)1,(fctId_t)49} */ 0u,
    /* {(lsgId_t)1,(fctId_t)49} */ 0u,
    /* {(lsgId_t)1,(fctId_t)49} */ 0u,
    /* {(lsgId_t)1,(fctId_t)49} */ 0u,
    /* {(lsgId_t)66,(fctId_t)22} */ 0u,
    /* {(lsgId_t)66,(fctId_t)22} */ 0u,
    /* {(lsgId_t)66,(fctId_t)22} */ 0u,
    /* {(lsgId_t)66,(fctId_t)22} */ 0u,
    /* {(lsgId_t)66,(fctId_t)38} */ 0u,
    /* {(lsgId_t)66,(fctId_t)38} */ 0u,
    /* {(lsgId_t)66,(fctId_t)38} */ 0u,
    /* {(lsgId_t)66,(fctId_t)38} */ 0u,
    /* {(lsgId_t)66,(fctId_t)40} */ 0u,
    /* {(lsgId_t)66,(fctId_t)42} */ 0u,
    /* {(lsgId_t)66,(fctId_t)42} */ 0u,
    /* {(lsgId_t)66,(fctId_t)42} */ 0u,
    /* {(lsgId_t)66,(fctId_t)42} */ 0u
};

#define BAP_STOP_SEC_VAR_INIT_16
#include <BAP_MemMap.h>

#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
/* BAP BCL CanTxSegmentation Tabelle ******************************************/
BAP_RAM_DATA_FAR
BapCanTxSegmentationRamRow_ot BAP_u16CanTxSegmentationTable[]=
{
    /* flags, u16BclTxBufferByteOffset, eSelectedSegmentationChannel */
    /* LsgId=1, FctId=1 */ {{0u}, 0u, BapSegType_ChannelOne},
    /* LsgId=1, FctId=3 */ {{0u}, 0u, BapSegType_ChannelOne},
    /* LsgId=1, FctId=14 */ {{0u}, 0u, BapSegType_ChannelOne},
    /* LsgId=1, FctId=22 */ {{0u}, 0u, BapSegType_ChannelOne},
    /* LsgId=1, FctId=23 */ {{0u}, 0u, BapSegType_ChannelOne},
    /* LsgId=1, FctId=36 */ {{0u}, 0u, BapSegType_ChannelOne},
    /* LsgId=1, FctId=42 */ {{0u}, 0u, BapSegType_ChannelOne},
    /* LsgId=1, FctId=43 */ {{0u}, 0u, BapSegType_ChannelOne},
    /* LsgId=1, FctId=44 */ {{0u}, 0u, BapSegType_ChannelOne},
    /* LsgId=1, FctId=45 */ {{0u}, 0u, BapSegType_ChannelOne},
    /* LsgId=1, FctId=48 */ {{0u}, 0u, BapSegType_ChannelOne},
    /* LsgId=1, FctId=49 */ {{0u}, 0u, BapSegType_ChannelOne},
    /* LsgId=66, FctId=1 */ {{0u}, 0u, BapSegType_ChannelOne},
    /* LsgId=66, FctId=3 */ {{0u}, 0u, BapSegType_ChannelOne},
    /* LsgId=66, FctId=14 */ {{0u}, 0u, BapSegType_ChannelOne},
    /* LsgId=66, FctId=22 */ {{0u}, 0u, BapSegType_ChannelOne},
    /* LsgId=66, FctId=38 */ {{0u}, 0u, BapSegType_ChannelOne},
    /* LsgId=66, FctId=40 */ {{0u}, 0u, BapSegType_ChannelOne},
    /* LsgId=66, FctId=42 */ {{0u}, 0u, BapSegType_ChannelOne}
};

#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
/* BAP BCL CanRxSegmentation Tabelle ******************************************/
BAP_RAM_DATA_FAR
BapCanRxSegmentationRamRow_ot BAP_u16CanRxSegmentationTable[]=
{
    /* flags, u16BclRxBufferByteOffset */
    /* LsgId=1, FctId=22 */ {{0u}, 0u},
    /* LsgId=1, FctId=22 */ {{0u}, 0u},
    /* LsgId=1, FctId=22 */ {{0u}, 0u},
    /* LsgId=1, FctId=22 */ {{0u}, 0u},
    /* LsgId=1, FctId=23 */ {{0u}, 0u},
    /* LsgId=1, FctId=23 */ {{0u}, 0u},
    /* LsgId=1, FctId=23 */ {{0u}, 0u},
    /* LsgId=1, FctId=23 */ {{0u}, 0u},
    /* LsgId=1, FctId=36 */ {{0u}, 0u},
    /* LsgId=1, FctId=36 */ {{0u}, 0u},
    /* LsgId=1, FctId=36 */ {{0u}, 0u},
    /* LsgId=1, FctId=36 */ {{0u}, 0u},
    /* LsgId=1, FctId=43 */ {{0u}, 0u},
    /* LsgId=1, FctId=43 */ {{0u}, 0u},
    /* LsgId=1, FctId=43 */ {{0u}, 0u},
    /* LsgId=1, FctId=43 */ {{0u}, 0u},
    /* LsgId=1, FctId=44 */ {{0u}, 0u},
    /* LsgId=1, FctId=44 */ {{0u}, 0u},
    /* LsgId=1, FctId=44 */ {{0u}, 0u},
    /* LsgId=1, FctId=44 */ {{0u}, 0u},
    /* LsgId=1, FctId=45 */ {{0u}, 0u},
    /* LsgId=1, FctId=45 */ {{0u}, 0u},
    /* LsgId=1, FctId=45 */ {{0u}, 0u},
    /* LsgId=1, FctId=45 */ {{0u}, 0u},
    /* LsgId=1, FctId=48 */ {{0u}, 0u},
    /* LsgId=1, FctId=48 */ {{0u}, 0u},
    /* LsgId=1, FctId=48 */ {{0u}, 0u},
    /* LsgId=1, FctId=48 */ {{0u}, 0u},
    /* LsgId=1, FctId=49 */ {{0u}, 0u},
    /* LsgId=1, FctId=49 */ {{0u}, 0u},
    /* LsgId=1, FctId=49 */ {{0u}, 0u},
    /* LsgId=1, FctId=49 */ {{0u}, 0u},
    /* LsgId=66, FctId=22 */ {{0u}, 0u},
    /* LsgId=66, FctId=22 */ {{0u}, 0u},
    /* LsgId=66, FctId=22 */ {{0u}, 0u},
    /* LsgId=66, FctId=22 */ {{0u}, 0u},
    /* LsgId=66, FctId=38 */ {{0u}, 0u},
    /* LsgId=66, FctId=38 */ {{0u}, 0u},
    /* LsgId=66, FctId=38 */ {{0u}, 0u},
    /* LsgId=66, FctId=38 */ {{0u}, 0u},
    /* LsgId=66, FctId=40 */ {{0u}, 0u},
    /* LsgId=66, FctId=42 */ {{0u}, 0u},
    /* LsgId=66, FctId=42 */ {{0u}, 0u},
    /* LsgId=66, FctId=42 */ {{0u}, 0u},
    /* LsgId=66, FctId=42 */ {{0u}, 0u}
};

#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* BCL CAN Tabellen fuer dynamische Kanalvergabe bei Segmentierung ************/

#ifdef BAP_USES_SEGMENTATION


#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BAP_RAM_DATA_FAR
BapCanTxDynSegChannels_ot BAP_CanTxSegmentationChannels[]=
{
    /* arpoTxDynSegChannels[4] */
    {{NULL, NULL, NULL, NULL}},
    {{NULL, NULL, NULL, NULL}}
};

#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

#define BAP_START_SEC_CONST_UNSPECIFIED
#include <BAP_MemMap.h>

BAP_ROM_DATA_FAR const BapCanMsgId_t BAP_ROM_CONST BAP_CanTxMsgIdToSegChannelMappingTable[]=
{
   (BapCanMsgId_t) BAP_Klima1_FSG_01,
   (BapCanMsgId_t) BAP_KlimaMaster_FSG_01
};

#define BAP_STOP_SEC_CONST_UNSPECIFIED
#include <BAP_MemMap.h>

#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

BAP_RAM_DATA_FAR
BapCanRxDynSegChannels_ot  BAP_CanRxSegmentationChannels[]=
{
    /* arpoTxDynSegChannels[4] */
    {{NULL, NULL, NULL, NULL}},
    {{NULL, NULL, NULL, NULL}},
    {{NULL, NULL, NULL, NULL}},
    {{NULL, NULL, NULL, NULL}},
    {{NULL, NULL, NULL, NULL}},
    {{NULL, NULL, NULL, NULL}},
    {{NULL, NULL, NULL, NULL}},
    {{NULL, NULL, NULL, NULL}}
};

#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

#define BAP_START_SEC_CONST_UNSPECIFIED
#include <BAP_MemMap.h>

BAP_ROM_DATA_FAR const BapCanMsgId_t BAP_ROM_CONST BAP_CanRxMsgIdToSegChannelMappingTable[]=
{
    (BapCanMsgId_t) BAP_KlimaMaster_ASG_04,
    (BapCanMsgId_t) BAP_KlimaMaster_ASG_03,
    (BapCanMsgId_t) BAP_KlimaMaster_ASG_02,
    (BapCanMsgId_t) BAP_KlimaMaster_ASG_01,
    (BapCanMsgId_t) BAP_Klima1_ASG_04,
    (BapCanMsgId_t) BAP_Klima1_ASG_03,
    (BapCanMsgId_t) BAP_Klima1_ASG_02,
    (BapCanMsgId_t) BAP_Klima1_ASG_01
};

#define BAP_STOP_SEC_CONST_UNSPECIFIED
#include <BAP_MemMap.h>

#endif

#define BAP_START_SEC_CONST_UNSPECIFIED
#include <BAP_MemMap.h>

/* CAN Tx ROM Tabelle *********************************************************/
BAP_ROM_DATA_FAR BapCanTxRomRow_ot BAP_ROM_CONST BAP_CanTxRomTable[]={
    /*                               u8InterfaceNumber, eSegmentationType, *pCanTxRamRow, *pBclTxRamRow, u8InhibitTimerIndex, canMsgId, poTxDynSegChannels, *poFctRomRow , u8SendCnt*/
/* LSG#id="1", Function#id="1" */ {20u, BapSegType_ChannelOneTwoThreeFour, &BAP_u16CanTxSegmentationTable[0], &BCL_TxBuffer0, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, &BAP_CanTxSegmentationChannels[0], &BAP_FctRomTables[0], 1},
/* LSG#id="1", Function#id="2" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer1, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, NULL, &BAP_FctRomTables[1], 1},
/* LSG#id="1", Function#id="3" */ {20u, BapSegType_ChannelOneTwoThreeFour, &BAP_u16CanTxSegmentationTable[1], &BCL_TxBuffer2, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, &BAP_CanTxSegmentationChannels[0], &BAP_FctRomTables[2], 1},
/* LSG#id="1", Function#id="4" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer3, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, NULL, &BAP_FctRomTables[3], 1},
/* LSG#id="1", Function#id="13" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer4, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, NULL, &BAP_FctRomTables[4], 1},
/* LSG#id="1", Function#id="14" */ {20u, BapSegType_ChannelOneTwoThreeFour, &BAP_u16CanTxSegmentationTable[2], &BCL_TxBuffer5, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, &BAP_CanTxSegmentationChannels[0], &BAP_FctRomTables[5], 1},
/* LSG#id="1", Function#id="15" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer6, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, NULL, &BAP_FctRomTables[6], 1},
/* LSG#id="1", Function#id="16" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer7, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, NULL, &BAP_FctRomTables[7], 1},
/* LSG#id="1", Function#id="17" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer8, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, NULL, &BAP_FctRomTables[8], 1},
/* LSG#id="1", Function#id="18" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer9, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, NULL, &BAP_FctRomTables[9], 1},
/* LSG#id="1", Function#id="19" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer10, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, NULL, &BAP_FctRomTables[10], 1},
/* LSG#id="1", Function#id="20" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer11, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, NULL, &BAP_FctRomTables[11], 1},
/* LSG#id="1", Function#id="21" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer12, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, NULL, &BAP_FctRomTables[12], 1},
/* LSG#id="1", Function#id="22" */ {20u, BapSegType_ChannelOneTwoThreeFour, &BAP_u16CanTxSegmentationTable[3], &BCL_TxBuffer13, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, &BAP_CanTxSegmentationChannels[0], &BAP_FctRomTables[13], 1},
/* LSG#id="1", Function#id="23" */ {20u, BapSegType_ChannelOneTwoThreeFour, &BAP_u16CanTxSegmentationTable[4], &BCL_TxBuffer14, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, &BAP_CanTxSegmentationChannels[0], &BAP_FctRomTables[14], 1},
/* LSG#id="1", Function#id="24" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer15, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, NULL, &BAP_FctRomTables[15], 1},
/* LSG#id="1", Function#id="25" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer16, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, NULL, &BAP_FctRomTables[16], 1},
/* LSG#id="1", Function#id="26" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer17, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, NULL, &BAP_FctRomTables[17], 1},
/* LSG#id="1", Function#id="27" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer18, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, NULL, &BAP_FctRomTables[18], 1},
/* LSG#id="1", Function#id="28" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer19, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, NULL, &BAP_FctRomTables[19], 1},
/* LSG#id="1", Function#id="29" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer20, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, NULL, &BAP_FctRomTables[20], 1},
/* LSG#id="1", Function#id="30" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer21, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, NULL, &BAP_FctRomTables[21], 1},
/* LSG#id="1", Function#id="31" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer22, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, NULL, &BAP_FctRomTables[22], 1},
/* LSG#id="1", Function#id="32" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer23, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, NULL, &BAP_FctRomTables[23], 1},
/* LSG#id="1", Function#id="33" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer24, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, NULL, &BAP_FctRomTables[24], 1},
/* LSG#id="1", Function#id="34" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer25, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, NULL, &BAP_FctRomTables[25], 1},
/* LSG#id="1", Function#id="35" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer26, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, NULL, &BAP_FctRomTables[26], 1},
/* LSG#id="1", Function#id="36" */ {20u, BapSegType_ChannelOneTwoThreeFour, &BAP_u16CanTxSegmentationTable[5], &BCL_TxBuffer27, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, &BAP_CanTxSegmentationChannels[0], &BAP_FctRomTables[27], 1},
/* LSG#id="1", Function#id="37" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer28, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, NULL, &BAP_FctRomTables[28], 1},
/* LSG#id="1", Function#id="38" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer29, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, NULL, &BAP_FctRomTables[29], 1},
/* LSG#id="1", Function#id="39" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer30, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, NULL, &BAP_FctRomTables[30], 1},
/* LSG#id="1", Function#id="40" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer31, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, NULL, &BAP_FctRomTables[31], 1},
/* LSG#id="1", Function#id="41" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer32, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, NULL, &BAP_FctRomTables[32], 1},
/* LSG#id="1", Function#id="42" */ {20u, BapSegType_ChannelOneTwoThreeFour, &BAP_u16CanTxSegmentationTable[6], &BCL_TxBuffer33, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, &BAP_CanTxSegmentationChannels[0], &BAP_FctRomTables[33], 1},
/* LSG#id="1", Function#id="43" */ {20u, BapSegType_ChannelOneTwoThreeFour, &BAP_u16CanTxSegmentationTable[7], &BCL_TxBuffer34, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, &BAP_CanTxSegmentationChannels[0], &BAP_FctRomTables[34], 1},
/* LSG#id="1", Function#id="44" */ {20u, BapSegType_ChannelOneTwoThreeFour, &BAP_u16CanTxSegmentationTable[8], &BCL_TxBuffer35, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, &BAP_CanTxSegmentationChannels[0], &BAP_FctRomTables[35], 1},
/* LSG#id="1", Function#id="45" */ {20u, BapSegType_ChannelOneTwoThreeFour, &BAP_u16CanTxSegmentationTable[9], &BCL_TxBuffer36, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, &BAP_CanTxSegmentationChannels[0], &BAP_FctRomTables[36], 1},
/* LSG#id="1", Function#id="46" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer37, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, NULL, &BAP_FctRomTables[37], 1},
/* LSG#id="1", Function#id="47" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer38, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, NULL, &BAP_FctRomTables[38], 1},
/* LSG#id="1", Function#id="48" */ {20u, BapSegType_ChannelOneTwoThreeFour, &BAP_u16CanTxSegmentationTable[10], &BCL_TxBuffer39, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, &BAP_CanTxSegmentationChannels[0], &BAP_FctRomTables[39], 1},
/* LSG#id="1", Function#id="49" */ {20u, BapSegType_ChannelOneTwoThreeFour, &BAP_u16CanTxSegmentationTable[11], &BCL_TxBuffer40, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, &BAP_CanTxSegmentationChannels[0], &BAP_FctRomTables[40], 1},
/* LSG#id="1", Function#id="50" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer41, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, NULL, &BAP_FctRomTables[41], 1},
/* LSG#id="1", Function#id="51" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer42, 0u, (BapCanMsgId_t) BAP_Klima1_FSG_01, NULL, &BAP_FctRomTables[42], 1},
/* LSG#id="66", Function#id="1" */ {20u, BapSegType_ChannelOneTwoThreeFour, &BAP_u16CanTxSegmentationTable[12], &BCL_TxBuffer43, 1u, (BapCanMsgId_t) BAP_KlimaMaster_FSG_01, &BAP_CanTxSegmentationChannels[1], &BAP_FctRomTables[43], 1},
/* LSG#id="66", Function#id="2" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer44, 1u, (BapCanMsgId_t) BAP_KlimaMaster_FSG_01, NULL, &BAP_FctRomTables[44], 1},
/* LSG#id="66", Function#id="3" */ {20u, BapSegType_ChannelOneTwoThreeFour, &BAP_u16CanTxSegmentationTable[13], &BCL_TxBuffer45, 1u, (BapCanMsgId_t) BAP_KlimaMaster_FSG_01, &BAP_CanTxSegmentationChannels[1], &BAP_FctRomTables[45], 1},
/* LSG#id="66", Function#id="4" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer46, 1u, (BapCanMsgId_t) BAP_KlimaMaster_FSG_01, NULL, &BAP_FctRomTables[46], 1},
/* LSG#id="66", Function#id="13" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer47, 1u, (BapCanMsgId_t) BAP_KlimaMaster_FSG_01, NULL, &BAP_FctRomTables[47], 1},
/* LSG#id="66", Function#id="14" */ {20u, BapSegType_ChannelOneTwoThreeFour, &BAP_u16CanTxSegmentationTable[14], &BCL_TxBuffer48, 1u, (BapCanMsgId_t) BAP_KlimaMaster_FSG_01, &BAP_CanTxSegmentationChannels[1], &BAP_FctRomTables[48], 1},
/* LSG#id="66", Function#id="15" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer49, 1u, (BapCanMsgId_t) BAP_KlimaMaster_FSG_01, NULL, &BAP_FctRomTables[49], 1},
/* LSG#id="66", Function#id="16" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer50, 1u, (BapCanMsgId_t) BAP_KlimaMaster_FSG_01, NULL, &BAP_FctRomTables[50], 1},
/* LSG#id="66", Function#id="17" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer51, 1u, (BapCanMsgId_t) BAP_KlimaMaster_FSG_01, NULL, &BAP_FctRomTables[51], 1},
/* LSG#id="66", Function#id="18" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer52, 1u, (BapCanMsgId_t) BAP_KlimaMaster_FSG_01, NULL, &BAP_FctRomTables[52], 1},
/* LSG#id="66", Function#id="19" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer53, 1u, (BapCanMsgId_t) BAP_KlimaMaster_FSG_01, NULL, &BAP_FctRomTables[53], 1},
/* LSG#id="66", Function#id="20" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer54, 1u, (BapCanMsgId_t) BAP_KlimaMaster_FSG_01, NULL, &BAP_FctRomTables[54], 1},
/* LSG#id="66", Function#id="21" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer55, 1u, (BapCanMsgId_t) BAP_KlimaMaster_FSG_01, NULL, &BAP_FctRomTables[55], 1},
/* LSG#id="66", Function#id="22" */ {20u, BapSegType_ChannelOneTwoThreeFour, &BAP_u16CanTxSegmentationTable[15], &BCL_TxBuffer56, 1u, (BapCanMsgId_t) BAP_KlimaMaster_FSG_01, &BAP_CanTxSegmentationChannels[1], &BAP_FctRomTables[56], 1},
/* LSG#id="66", Function#id="23" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer57, 1u, (BapCanMsgId_t) BAP_KlimaMaster_FSG_01, NULL, &BAP_FctRomTables[57], 1},
/* LSG#id="66", Function#id="24" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer58, 1u, (BapCanMsgId_t) BAP_KlimaMaster_FSG_01, NULL, &BAP_FctRomTables[58], 1},
/* LSG#id="66", Function#id="25" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer59, 1u, (BapCanMsgId_t) BAP_KlimaMaster_FSG_01, NULL, &BAP_FctRomTables[59], 1},
/* LSG#id="66", Function#id="26" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer60, 1u, (BapCanMsgId_t) BAP_KlimaMaster_FSG_01, NULL, &BAP_FctRomTables[60], 1},
/* LSG#id="66", Function#id="27" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer61, 1u, (BapCanMsgId_t) BAP_KlimaMaster_FSG_01, NULL, &BAP_FctRomTables[61], 1},
/* LSG#id="66", Function#id="28" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer62, 1u, (BapCanMsgId_t) BAP_KlimaMaster_FSG_01, NULL, &BAP_FctRomTables[62], 1},
/* LSG#id="66", Function#id="29" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer63, 1u, (BapCanMsgId_t) BAP_KlimaMaster_FSG_01, NULL, &BAP_FctRomTables[63], 1},
/* LSG#id="66", Function#id="30" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer64, 1u, (BapCanMsgId_t) BAP_KlimaMaster_FSG_01, NULL, &BAP_FctRomTables[64], 1},
/* LSG#id="66", Function#id="31" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer65, 1u, (BapCanMsgId_t) BAP_KlimaMaster_FSG_01, NULL, &BAP_FctRomTables[65], 1},
/* LSG#id="66", Function#id="32" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer66, 1u, (BapCanMsgId_t) BAP_KlimaMaster_FSG_01, NULL, &BAP_FctRomTables[66], 1},
/* LSG#id="66", Function#id="33" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer67, 1u, (BapCanMsgId_t) BAP_KlimaMaster_FSG_01, NULL, &BAP_FctRomTables[67], 1},
/* LSG#id="66", Function#id="34" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer68, 1u, (BapCanMsgId_t) BAP_KlimaMaster_FSG_01, NULL, &BAP_FctRomTables[68], 1},
/* LSG#id="66", Function#id="35" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer69, 1u, (BapCanMsgId_t) BAP_KlimaMaster_FSG_01, NULL, &BAP_FctRomTables[69], 1},
/* LSG#id="66", Function#id="36" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer70, 1u, (BapCanMsgId_t) BAP_KlimaMaster_FSG_01, NULL, &BAP_FctRomTables[70], 1},
/* LSG#id="66", Function#id="37" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer71, 1u, (BapCanMsgId_t) BAP_KlimaMaster_FSG_01, NULL, &BAP_FctRomTables[71], 1},
/* LSG#id="66", Function#id="38" */ {20u, BapSegType_ChannelOneTwoThreeFour, &BAP_u16CanTxSegmentationTable[16], &BCL_TxBuffer72, 1u, (BapCanMsgId_t) BAP_KlimaMaster_FSG_01, &BAP_CanTxSegmentationChannels[1], &BAP_FctRomTables[72], 1},
/* LSG#id="66", Function#id="39" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer73, 1u, (BapCanMsgId_t) BAP_KlimaMaster_FSG_01, NULL, &BAP_FctRomTables[73], 1},
/* LSG#id="66", Function#id="40" */ {20u, BapSegType_ChannelOneTwoThreeFour, &BAP_u16CanTxSegmentationTable[17], &BCL_TxBuffer74, 1u, (BapCanMsgId_t) BAP_KlimaMaster_FSG_01, &BAP_CanTxSegmentationChannels[1], &BAP_FctRomTables[74], 1},
/* LSG#id="66", Function#id="41" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer75, 1u, (BapCanMsgId_t) BAP_KlimaMaster_FSG_01, NULL, &BAP_FctRomTables[75], 1},
/* LSG#id="66", Function#id="42" */ {20u, BapSegType_ChannelOneTwoThreeFour, &BAP_u16CanTxSegmentationTable[18], &BCL_TxBuffer76, 1u, (BapCanMsgId_t) BAP_KlimaMaster_FSG_01, &BAP_CanTxSegmentationChannels[1], &BAP_FctRomTables[76], 1},
/* LSG#id="66", Function#id="43" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer77, 1u, (BapCanMsgId_t) BAP_KlimaMaster_FSG_01, NULL, &BAP_FctRomTables[77], 1},
/* LSG#id="66", Function#id="44" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer78, 1u, (BapCanMsgId_t) BAP_KlimaMaster_FSG_01, NULL, &BAP_FctRomTables[78], 1},
/* LSG#id="66", Function#id="45" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer79, 1u, (BapCanMsgId_t) BAP_KlimaMaster_FSG_01, NULL, &BAP_FctRomTables[79], 1},
/* LSG#id="66", Function#id="46" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer80, 1u, (BapCanMsgId_t) BAP_KlimaMaster_FSG_01, NULL, &BAP_FctRomTables[80], 1},
/* LSG#id="66", Function#id="47" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer81, 1u, (BapCanMsgId_t) BAP_KlimaMaster_FSG_01, NULL, &BAP_FctRomTables[81], 1},
/* LSG#id="66", Function#id="48" */ {20u, BapSegType_Unsegmented, NULL, &BCL_TxBuffer82, 1u, (BapCanMsgId_t) BAP_KlimaMaster_FSG_01, NULL, &BAP_FctRomTables[82], 1}
};

/* CAN Rx ROM Tabelle *********************************************************/
BAP_ROM_DATA_FAR BapCanRxRomRow_ot BAP_ROM_CONST BAP_CanRxRomTable[]={
    /*  lsgId, fctId, u32Size, u8InterfaceNumber, eSegmentationType, u16IntertelegramTime, *pCanRxRamRow, *pBclRxRamRow, *pu16InterTelegramTimer, canMsgId, poRxDynSegChannels */
    {(lsgId_t)1, (fctId_t)1, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_01, NULL},
    {(lsgId_t)1, (fctId_t)1, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_02, NULL},
    {(lsgId_t)1, (fctId_t)1, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_03, NULL},
    {(lsgId_t)1, (fctId_t)1, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_04, NULL},
    {(lsgId_t)1, (fctId_t)2, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_01, NULL},
    {(lsgId_t)1, (fctId_t)2, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_02, NULL},
    {(lsgId_t)1, (fctId_t)2, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_03, NULL},
    {(lsgId_t)1, (fctId_t)2, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_04, NULL},
    {(lsgId_t)1, (fctId_t)3, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_01, NULL},
    {(lsgId_t)1, (fctId_t)3, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_02, NULL},
    {(lsgId_t)1, (fctId_t)3, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_03, NULL},
    {(lsgId_t)1, (fctId_t)3, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_04, NULL},
    {(lsgId_t)1, (fctId_t)4, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_01, NULL},
    {(lsgId_t)1, (fctId_t)4, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_02, NULL},
    {(lsgId_t)1, (fctId_t)4, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_03, NULL},
    {(lsgId_t)1, (fctId_t)4, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_04, NULL},
    {(lsgId_t)1, (fctId_t)13, 1u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_01, NULL},
    {(lsgId_t)1, (fctId_t)13, 1u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_02, NULL},
    {(lsgId_t)1, (fctId_t)13, 1u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_03, NULL},
    {(lsgId_t)1, (fctId_t)13, 1u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_04, NULL},
    {(lsgId_t)1, (fctId_t)14, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_01, NULL},
    {(lsgId_t)1, (fctId_t)14, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_02, NULL},
    {(lsgId_t)1, (fctId_t)14, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_03, NULL},
    {(lsgId_t)1, (fctId_t)14, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_04, NULL},
    {(lsgId_t)1, (fctId_t)15, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_01, NULL},
    {(lsgId_t)1, (fctId_t)15, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_02, NULL},
    {(lsgId_t)1, (fctId_t)15, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_03, NULL},
    {(lsgId_t)1, (fctId_t)15, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_04, NULL},
    {(lsgId_t)1, (fctId_t)16, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer0,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_01, NULL},
    {(lsgId_t)1, (fctId_t)16, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer0,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_02, NULL},
    {(lsgId_t)1, (fctId_t)16, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer0,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_03, NULL},
    {(lsgId_t)1, (fctId_t)16, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer0,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_04, NULL},
    {(lsgId_t)1, (fctId_t)17, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer1,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_01, NULL},
    {(lsgId_t)1, (fctId_t)17, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer1,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_02, NULL},
    {(lsgId_t)1, (fctId_t)17, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer1,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_03, NULL},
    {(lsgId_t)1, (fctId_t)17, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer1,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_04, NULL},
    {(lsgId_t)1, (fctId_t)18, 4u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer2,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_01, NULL},
    {(lsgId_t)1, (fctId_t)18, 4u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer2,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_02, NULL},
    {(lsgId_t)1, (fctId_t)18, 4u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer2,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_03, NULL},
    {(lsgId_t)1, (fctId_t)18, 4u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer2,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_04, NULL},
    {(lsgId_t)1, (fctId_t)19, 4u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer3,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_01, NULL},
    {(lsgId_t)1, (fctId_t)19, 4u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer3,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_02, NULL},
    {(lsgId_t)1, (fctId_t)19, 4u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer3,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_03, NULL},
    {(lsgId_t)1, (fctId_t)19, 4u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer3,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_04, NULL},
    {(lsgId_t)1, (fctId_t)20, 5u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer4,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_01, NULL},
    {(lsgId_t)1, (fctId_t)20, 5u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer4,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_02, NULL},
    {(lsgId_t)1, (fctId_t)20, 5u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer4,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_03, NULL},
    {(lsgId_t)1, (fctId_t)20, 5u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer4,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_04, NULL},
    {(lsgId_t)1, (fctId_t)21, 5u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer5,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_01, NULL},
    {(lsgId_t)1, (fctId_t)21, 5u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer5,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_02, NULL},
    {(lsgId_t)1, (fctId_t)21, 5u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer5,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_03, NULL},
    {(lsgId_t)1, (fctId_t)21, 5u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer5,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_04, NULL},
    {(lsgId_t)1, (fctId_t)22, 7u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[0], &BCL_RxBuffer6,  &BAP_u16InterTelegramTimerTable[0], (BapCanMsgId_t) BAP_Klima1_ASG_01, &BAP_CanRxSegmentationChannels[7]},
    {(lsgId_t)1, (fctId_t)22, 7u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[1], &BCL_RxBuffer6,  &BAP_u16InterTelegramTimerTable[1], (BapCanMsgId_t) BAP_Klima1_ASG_02, &BAP_CanRxSegmentationChannels[6]},
    {(lsgId_t)1, (fctId_t)22, 7u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[2], &BCL_RxBuffer6,  &BAP_u16InterTelegramTimerTable[2], (BapCanMsgId_t) BAP_Klima1_ASG_03, &BAP_CanRxSegmentationChannels[5]},
    {(lsgId_t)1, (fctId_t)22, 7u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[3], &BCL_RxBuffer6,  &BAP_u16InterTelegramTimerTable[3], (BapCanMsgId_t) BAP_Klima1_ASG_04, &BAP_CanRxSegmentationChannels[4]},
    {(lsgId_t)1, (fctId_t)23, 7u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[4], &BCL_RxBuffer7,  &BAP_u16InterTelegramTimerTable[4], (BapCanMsgId_t) BAP_Klima1_ASG_01, &BAP_CanRxSegmentationChannels[7]},
    {(lsgId_t)1, (fctId_t)23, 7u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[5], &BCL_RxBuffer7,  &BAP_u16InterTelegramTimerTable[5], (BapCanMsgId_t) BAP_Klima1_ASG_02, &BAP_CanRxSegmentationChannels[6]},
    {(lsgId_t)1, (fctId_t)23, 7u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[6], &BCL_RxBuffer7,  &BAP_u16InterTelegramTimerTable[6], (BapCanMsgId_t) BAP_Klima1_ASG_03, &BAP_CanRxSegmentationChannels[5]},
    {(lsgId_t)1, (fctId_t)23, 7u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[7], &BCL_RxBuffer7,  &BAP_u16InterTelegramTimerTable[7], (BapCanMsgId_t) BAP_Klima1_ASG_04, &BAP_CanRxSegmentationChannels[4]},
    {(lsgId_t)1, (fctId_t)24, 4u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer8,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_01, NULL},
    {(lsgId_t)1, (fctId_t)24, 4u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer8,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_02, NULL},
    {(lsgId_t)1, (fctId_t)24, 4u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer8,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_03, NULL},
    {(lsgId_t)1, (fctId_t)24, 4u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer8,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_04, NULL},
    {(lsgId_t)1, (fctId_t)25, 4u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer9,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_01, NULL},
    {(lsgId_t)1, (fctId_t)25, 4u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer9,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_02, NULL},
    {(lsgId_t)1, (fctId_t)25, 4u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer9,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_03, NULL},
    {(lsgId_t)1, (fctId_t)25, 4u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer9,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_04, NULL},
    {(lsgId_t)1, (fctId_t)26, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer10,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_01, NULL},
    {(lsgId_t)1, (fctId_t)26, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer10,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_02, NULL},
    {(lsgId_t)1, (fctId_t)26, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer10,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_03, NULL},
    {(lsgId_t)1, (fctId_t)26, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer10,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_04, NULL},
    {(lsgId_t)1, (fctId_t)27, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer11,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_01, NULL},
    {(lsgId_t)1, (fctId_t)27, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer11,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_02, NULL},
    {(lsgId_t)1, (fctId_t)27, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer11,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_03, NULL},
    {(lsgId_t)1, (fctId_t)27, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer11,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_04, NULL},
    {(lsgId_t)1, (fctId_t)28, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_01, NULL},
    {(lsgId_t)1, (fctId_t)28, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_02, NULL},
    {(lsgId_t)1, (fctId_t)28, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_03, NULL},
    {(lsgId_t)1, (fctId_t)28, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_04, NULL},
    {(lsgId_t)1, (fctId_t)29, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_01, NULL},
    {(lsgId_t)1, (fctId_t)29, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_02, NULL},
    {(lsgId_t)1, (fctId_t)29, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_03, NULL},
    {(lsgId_t)1, (fctId_t)29, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_04, NULL},
    {(lsgId_t)1, (fctId_t)30, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer12,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_01, NULL},
    {(lsgId_t)1, (fctId_t)30, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer12,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_02, NULL},
    {(lsgId_t)1, (fctId_t)30, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer12,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_03, NULL},
    {(lsgId_t)1, (fctId_t)30, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer12,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_04, NULL},
    {(lsgId_t)1, (fctId_t)31, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer13,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_01, NULL},
    {(lsgId_t)1, (fctId_t)31, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer13,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_02, NULL},
    {(lsgId_t)1, (fctId_t)31, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer13,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_03, NULL},
    {(lsgId_t)1, (fctId_t)31, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer13,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_04, NULL},
    {(lsgId_t)1, (fctId_t)32, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer14,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_01, NULL},
    {(lsgId_t)1, (fctId_t)32, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer14,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_02, NULL},
    {(lsgId_t)1, (fctId_t)32, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer14,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_03, NULL},
    {(lsgId_t)1, (fctId_t)32, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer14,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_04, NULL},
    {(lsgId_t)1, (fctId_t)33, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer15,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_01, NULL},
    {(lsgId_t)1, (fctId_t)33, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer15,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_02, NULL},
    {(lsgId_t)1, (fctId_t)33, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer15,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_03, NULL},
    {(lsgId_t)1, (fctId_t)33, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer15,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_04, NULL},
    {(lsgId_t)1, (fctId_t)34, 5u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer16,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_01, NULL},
    {(lsgId_t)1, (fctId_t)34, 5u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer16,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_02, NULL},
    {(lsgId_t)1, (fctId_t)34, 5u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer16,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_03, NULL},
    {(lsgId_t)1, (fctId_t)34, 5u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer16,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_04, NULL},
    {(lsgId_t)1, (fctId_t)35, 5u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer17,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_01, NULL},
    {(lsgId_t)1, (fctId_t)35, 5u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer17,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_02, NULL},
    {(lsgId_t)1, (fctId_t)35, 5u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer17,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_03, NULL},
    {(lsgId_t)1, (fctId_t)35, 5u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer17,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_04, NULL},
    {(lsgId_t)1, (fctId_t)36, 112u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[8], &BCL_RxBuffer18,  &BAP_u16InterTelegramTimerTable[8], (BapCanMsgId_t) BAP_Klima1_ASG_01, &BAP_CanRxSegmentationChannels[7]},
    {(lsgId_t)1, (fctId_t)36, 112u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[9], &BCL_RxBuffer18,  &BAP_u16InterTelegramTimerTable[9], (BapCanMsgId_t) BAP_Klima1_ASG_02, &BAP_CanRxSegmentationChannels[6]},
    {(lsgId_t)1, (fctId_t)36, 112u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[10], &BCL_RxBuffer18,  &BAP_u16InterTelegramTimerTable[10], (BapCanMsgId_t) BAP_Klima1_ASG_03, &BAP_CanRxSegmentationChannels[5]},
    {(lsgId_t)1, (fctId_t)36, 112u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[11], &BCL_RxBuffer18,  &BAP_u16InterTelegramTimerTable[11], (BapCanMsgId_t) BAP_Klima1_ASG_04, &BAP_CanRxSegmentationChannels[4]},
    {(lsgId_t)1, (fctId_t)37, 1u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer19,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_01, NULL},
    {(lsgId_t)1, (fctId_t)37, 1u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer19,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_02, NULL},
    {(lsgId_t)1, (fctId_t)37, 1u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer19,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_03, NULL},
    {(lsgId_t)1, (fctId_t)37, 1u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer19,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_04, NULL},
    {(lsgId_t)1, (fctId_t)38, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_01, NULL},
    {(lsgId_t)1, (fctId_t)38, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_02, NULL},
    {(lsgId_t)1, (fctId_t)38, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_03, NULL},
    {(lsgId_t)1, (fctId_t)38, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_04, NULL},
    {(lsgId_t)1, (fctId_t)39, 4u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer20,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_01, NULL},
    {(lsgId_t)1, (fctId_t)39, 4u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer20,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_02, NULL},
    {(lsgId_t)1, (fctId_t)39, 4u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer20,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_03, NULL},
    {(lsgId_t)1, (fctId_t)39, 4u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer20,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_04, NULL},
    {(lsgId_t)1, (fctId_t)40, 4u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer21,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_01, NULL},
    {(lsgId_t)1, (fctId_t)40, 4u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer21,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_02, NULL},
    {(lsgId_t)1, (fctId_t)40, 4u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer21,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_03, NULL},
    {(lsgId_t)1, (fctId_t)40, 4u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer21,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_04, NULL},
    {(lsgId_t)1, (fctId_t)41, 5u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer22,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_01, NULL},
    {(lsgId_t)1, (fctId_t)41, 5u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer22,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_02, NULL},
    {(lsgId_t)1, (fctId_t)41, 5u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer22,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_03, NULL},
    {(lsgId_t)1, (fctId_t)41, 5u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer22,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_04, NULL},
    {(lsgId_t)1, (fctId_t)42, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_01, NULL},
    {(lsgId_t)1, (fctId_t)42, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_02, NULL},
    {(lsgId_t)1, (fctId_t)42, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_03, NULL},
    {(lsgId_t)1, (fctId_t)42, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_04, NULL},
    {(lsgId_t)1, (fctId_t)43, 9u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[12], &BCL_RxBuffer23,  &BAP_u16InterTelegramTimerTable[12], (BapCanMsgId_t) BAP_Klima1_ASG_01, &BAP_CanRxSegmentationChannels[7]},
    {(lsgId_t)1, (fctId_t)43, 9u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[13], &BCL_RxBuffer23,  &BAP_u16InterTelegramTimerTable[13], (BapCanMsgId_t) BAP_Klima1_ASG_02, &BAP_CanRxSegmentationChannels[6]},
    {(lsgId_t)1, (fctId_t)43, 9u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[14], &BCL_RxBuffer23,  &BAP_u16InterTelegramTimerTable[14], (BapCanMsgId_t) BAP_Klima1_ASG_03, &BAP_CanRxSegmentationChannels[5]},
    {(lsgId_t)1, (fctId_t)43, 9u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[15], &BCL_RxBuffer23,  &BAP_u16InterTelegramTimerTable[15], (BapCanMsgId_t) BAP_Klima1_ASG_04, &BAP_CanRxSegmentationChannels[4]},
    {(lsgId_t)1, (fctId_t)44, 9u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[16], &BCL_RxBuffer24,  &BAP_u16InterTelegramTimerTable[16], (BapCanMsgId_t) BAP_Klima1_ASG_01, &BAP_CanRxSegmentationChannels[7]},
    {(lsgId_t)1, (fctId_t)44, 9u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[17], &BCL_RxBuffer24,  &BAP_u16InterTelegramTimerTable[17], (BapCanMsgId_t) BAP_Klima1_ASG_02, &BAP_CanRxSegmentationChannels[6]},
    {(lsgId_t)1, (fctId_t)44, 9u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[18], &BCL_RxBuffer24,  &BAP_u16InterTelegramTimerTable[18], (BapCanMsgId_t) BAP_Klima1_ASG_03, &BAP_CanRxSegmentationChannels[5]},
    {(lsgId_t)1, (fctId_t)44, 9u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[19], &BCL_RxBuffer24,  &BAP_u16InterTelegramTimerTable[19], (BapCanMsgId_t) BAP_Klima1_ASG_04, &BAP_CanRxSegmentationChannels[4]},
    {(lsgId_t)1, (fctId_t)45, 4u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[20], &BCL_RxBuffer25,  &BAP_u16InterTelegramTimerTable[20], (BapCanMsgId_t) BAP_Klima1_ASG_01, &BAP_CanRxSegmentationChannels[7]},
    {(lsgId_t)1, (fctId_t)45, 4u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[21], &BCL_RxBuffer25,  &BAP_u16InterTelegramTimerTable[21], (BapCanMsgId_t) BAP_Klima1_ASG_02, &BAP_CanRxSegmentationChannels[6]},
    {(lsgId_t)1, (fctId_t)45, 4u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[22], &BCL_RxBuffer25,  &BAP_u16InterTelegramTimerTable[22], (BapCanMsgId_t) BAP_Klima1_ASG_03, &BAP_CanRxSegmentationChannels[5]},
    {(lsgId_t)1, (fctId_t)45, 4u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[23], &BCL_RxBuffer25,  &BAP_u16InterTelegramTimerTable[23], (BapCanMsgId_t) BAP_Klima1_ASG_04, &BAP_CanRxSegmentationChannels[4]},
    {(lsgId_t)1, (fctId_t)46, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer26,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_01, NULL},
    {(lsgId_t)1, (fctId_t)46, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer26,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_02, NULL},
    {(lsgId_t)1, (fctId_t)46, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer26,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_03, NULL},
    {(lsgId_t)1, (fctId_t)46, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer26,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_04, NULL},
    {(lsgId_t)1, (fctId_t)47, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer27,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_01, NULL},
    {(lsgId_t)1, (fctId_t)47, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer27,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_02, NULL},
    {(lsgId_t)1, (fctId_t)47, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer27,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_03, NULL},
    {(lsgId_t)1, (fctId_t)47, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer27,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_04, NULL},
    {(lsgId_t)1, (fctId_t)48, 8u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[24], &BCL_RxBuffer28,  &BAP_u16InterTelegramTimerTable[24], (BapCanMsgId_t) BAP_Klima1_ASG_01, &BAP_CanRxSegmentationChannels[7]},
    {(lsgId_t)1, (fctId_t)48, 8u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[25], &BCL_RxBuffer28,  &BAP_u16InterTelegramTimerTable[25], (BapCanMsgId_t) BAP_Klima1_ASG_02, &BAP_CanRxSegmentationChannels[6]},
    {(lsgId_t)1, (fctId_t)48, 8u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[26], &BCL_RxBuffer28,  &BAP_u16InterTelegramTimerTable[26], (BapCanMsgId_t) BAP_Klima1_ASG_03, &BAP_CanRxSegmentationChannels[5]},
    {(lsgId_t)1, (fctId_t)48, 8u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[27], &BCL_RxBuffer28,  &BAP_u16InterTelegramTimerTable[27], (BapCanMsgId_t) BAP_Klima1_ASG_04, &BAP_CanRxSegmentationChannels[4]},
    {(lsgId_t)1, (fctId_t)49, 8u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[28], &BCL_RxBuffer29,  &BAP_u16InterTelegramTimerTable[28], (BapCanMsgId_t) BAP_Klima1_ASG_01, &BAP_CanRxSegmentationChannels[7]},
    {(lsgId_t)1, (fctId_t)49, 8u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[29], &BCL_RxBuffer29,  &BAP_u16InterTelegramTimerTable[29], (BapCanMsgId_t) BAP_Klima1_ASG_02, &BAP_CanRxSegmentationChannels[6]},
    {(lsgId_t)1, (fctId_t)49, 8u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[30], &BCL_RxBuffer29,  &BAP_u16InterTelegramTimerTable[30], (BapCanMsgId_t) BAP_Klima1_ASG_03, &BAP_CanRxSegmentationChannels[5]},
    {(lsgId_t)1, (fctId_t)49, 8u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[31], &BCL_RxBuffer29,  &BAP_u16InterTelegramTimerTable[31], (BapCanMsgId_t) BAP_Klima1_ASG_04, &BAP_CanRxSegmentationChannels[4]},
    {(lsgId_t)1, (fctId_t)50, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer30,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_01, NULL},
    {(lsgId_t)1, (fctId_t)50, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer30,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_02, NULL},
    {(lsgId_t)1, (fctId_t)50, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer30,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_03, NULL},
    {(lsgId_t)1, (fctId_t)50, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer30,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_04, NULL},
    {(lsgId_t)1, (fctId_t)51, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer31,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_01, NULL},
    {(lsgId_t)1, (fctId_t)51, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer31,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_02, NULL},
    {(lsgId_t)1, (fctId_t)51, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer31,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_03, NULL},
    {(lsgId_t)1, (fctId_t)51, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer31,  NULL, (BapCanMsgId_t) BAP_Klima1_ASG_04, NULL},
    {(lsgId_t)66, (fctId_t)1, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_01, NULL},
    {(lsgId_t)66, (fctId_t)1, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_02, NULL},
    {(lsgId_t)66, (fctId_t)1, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_03, NULL},
    {(lsgId_t)66, (fctId_t)1, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_04, NULL},
    {(lsgId_t)66, (fctId_t)2, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_01, NULL},
    {(lsgId_t)66, (fctId_t)2, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_02, NULL},
    {(lsgId_t)66, (fctId_t)2, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_03, NULL},
    {(lsgId_t)66, (fctId_t)2, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_04, NULL},
    {(lsgId_t)66, (fctId_t)3, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_01, NULL},
    {(lsgId_t)66, (fctId_t)3, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_02, NULL},
    {(lsgId_t)66, (fctId_t)3, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_03, NULL},
    {(lsgId_t)66, (fctId_t)3, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_04, NULL},
    {(lsgId_t)66, (fctId_t)4, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_01, NULL},
    {(lsgId_t)66, (fctId_t)4, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_02, NULL},
    {(lsgId_t)66, (fctId_t)4, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_03, NULL},
    {(lsgId_t)66, (fctId_t)4, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_04, NULL},
    {(lsgId_t)66, (fctId_t)13, 1u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_01, NULL},
    {(lsgId_t)66, (fctId_t)13, 1u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_02, NULL},
    {(lsgId_t)66, (fctId_t)13, 1u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_03, NULL},
    {(lsgId_t)66, (fctId_t)13, 1u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_04, NULL},
    {(lsgId_t)66, (fctId_t)14, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_01, NULL},
    {(lsgId_t)66, (fctId_t)14, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_02, NULL},
    {(lsgId_t)66, (fctId_t)14, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_03, NULL},
    {(lsgId_t)66, (fctId_t)14, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_04, NULL},
    {(lsgId_t)66, (fctId_t)15, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_01, NULL},
    {(lsgId_t)66, (fctId_t)15, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_02, NULL},
    {(lsgId_t)66, (fctId_t)15, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_03, NULL},
    {(lsgId_t)66, (fctId_t)15, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_04, NULL},
    {(lsgId_t)66, (fctId_t)16, 2u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer32,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_01, NULL},
    {(lsgId_t)66, (fctId_t)16, 2u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer32,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_02, NULL},
    {(lsgId_t)66, (fctId_t)16, 2u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer32,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_03, NULL},
    {(lsgId_t)66, (fctId_t)16, 2u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer32,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_04, NULL},
    {(lsgId_t)66, (fctId_t)17, 2u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer33,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_01, NULL},
    {(lsgId_t)66, (fctId_t)17, 2u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer33,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_02, NULL},
    {(lsgId_t)66, (fctId_t)17, 2u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer33,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_03, NULL},
    {(lsgId_t)66, (fctId_t)17, 2u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer33,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_04, NULL},
    {(lsgId_t)66, (fctId_t)18, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer34,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_01, NULL},
    {(lsgId_t)66, (fctId_t)18, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer34,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_02, NULL},
    {(lsgId_t)66, (fctId_t)18, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer34,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_03, NULL},
    {(lsgId_t)66, (fctId_t)18, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer34,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_04, NULL},
    {(lsgId_t)66, (fctId_t)19, 2u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer35,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_01, NULL},
    {(lsgId_t)66, (fctId_t)19, 2u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer35,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_02, NULL},
    {(lsgId_t)66, (fctId_t)19, 2u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer35,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_03, NULL},
    {(lsgId_t)66, (fctId_t)19, 2u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer35,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_04, NULL},
    {(lsgId_t)66, (fctId_t)20, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer36,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_01, NULL},
    {(lsgId_t)66, (fctId_t)20, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer36,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_02, NULL},
    {(lsgId_t)66, (fctId_t)20, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer36,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_03, NULL},
    {(lsgId_t)66, (fctId_t)20, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer36,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_04, NULL},
    {(lsgId_t)66, (fctId_t)21, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer37,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_01, NULL},
    {(lsgId_t)66, (fctId_t)21, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer37,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_02, NULL},
    {(lsgId_t)66, (fctId_t)21, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer37,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_03, NULL},
    {(lsgId_t)66, (fctId_t)21, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer37,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_04, NULL},
    {(lsgId_t)66, (fctId_t)22, 9u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[32], &BCL_RxBuffer38,  &BAP_u16InterTelegramTimerTable[32], (BapCanMsgId_t) BAP_KlimaMaster_ASG_01, &BAP_CanRxSegmentationChannels[3]},
    {(lsgId_t)66, (fctId_t)22, 9u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[33], &BCL_RxBuffer38,  &BAP_u16InterTelegramTimerTable[33], (BapCanMsgId_t) BAP_KlimaMaster_ASG_02, &BAP_CanRxSegmentationChannels[2]},
    {(lsgId_t)66, (fctId_t)22, 9u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[34], &BCL_RxBuffer38,  &BAP_u16InterTelegramTimerTable[34], (BapCanMsgId_t) BAP_KlimaMaster_ASG_03, &BAP_CanRxSegmentationChannels[1]},
    {(lsgId_t)66, (fctId_t)22, 9u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[35], &BCL_RxBuffer38,  &BAP_u16InterTelegramTimerTable[35], (BapCanMsgId_t) BAP_KlimaMaster_ASG_04, &BAP_CanRxSegmentationChannels[0]},
    {(lsgId_t)66, (fctId_t)23, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer39,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_01, NULL},
    {(lsgId_t)66, (fctId_t)23, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer39,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_02, NULL},
    {(lsgId_t)66, (fctId_t)23, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer39,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_03, NULL},
    {(lsgId_t)66, (fctId_t)23, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer39,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_04, NULL},
    {(lsgId_t)66, (fctId_t)24, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer40,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_01, NULL},
    {(lsgId_t)66, (fctId_t)24, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer40,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_02, NULL},
    {(lsgId_t)66, (fctId_t)24, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer40,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_03, NULL},
    {(lsgId_t)66, (fctId_t)24, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer40,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_04, NULL},
    {(lsgId_t)66, (fctId_t)25, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer41,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_01, NULL},
    {(lsgId_t)66, (fctId_t)25, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer41,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_02, NULL},
    {(lsgId_t)66, (fctId_t)25, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer41,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_03, NULL},
    {(lsgId_t)66, (fctId_t)25, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer41,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_04, NULL},
    {(lsgId_t)66, (fctId_t)26, 4u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer42,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_01, NULL},
    {(lsgId_t)66, (fctId_t)26, 4u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer42,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_02, NULL},
    {(lsgId_t)66, (fctId_t)26, 4u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer42,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_03, NULL},
    {(lsgId_t)66, (fctId_t)26, 4u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer42,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_04, NULL},
    {(lsgId_t)66, (fctId_t)27, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer43,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_01, NULL},
    {(lsgId_t)66, (fctId_t)27, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer43,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_02, NULL},
    {(lsgId_t)66, (fctId_t)27, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer43,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_03, NULL},
    {(lsgId_t)66, (fctId_t)27, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer43,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_04, NULL},
    {(lsgId_t)66, (fctId_t)28, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer44,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_01, NULL},
    {(lsgId_t)66, (fctId_t)28, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer44,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_02, NULL},
    {(lsgId_t)66, (fctId_t)28, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer44,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_03, NULL},
    {(lsgId_t)66, (fctId_t)28, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer44,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_04, NULL},
    {(lsgId_t)66, (fctId_t)29, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer45,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_01, NULL},
    {(lsgId_t)66, (fctId_t)29, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer45,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_02, NULL},
    {(lsgId_t)66, (fctId_t)29, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer45,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_03, NULL},
    {(lsgId_t)66, (fctId_t)29, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer45,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_04, NULL},
    {(lsgId_t)66, (fctId_t)30, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer46,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_01, NULL},
    {(lsgId_t)66, (fctId_t)30, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer46,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_02, NULL},
    {(lsgId_t)66, (fctId_t)30, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer46,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_03, NULL},
    {(lsgId_t)66, (fctId_t)30, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer46,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_04, NULL},
    {(lsgId_t)66, (fctId_t)31, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer47,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_01, NULL},
    {(lsgId_t)66, (fctId_t)31, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer47,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_02, NULL},
    {(lsgId_t)66, (fctId_t)31, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer47,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_03, NULL},
    {(lsgId_t)66, (fctId_t)31, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer47,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_04, NULL},
    {(lsgId_t)66, (fctId_t)32, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer48,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_01, NULL},
    {(lsgId_t)66, (fctId_t)32, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer48,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_02, NULL},
    {(lsgId_t)66, (fctId_t)32, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer48,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_03, NULL},
    {(lsgId_t)66, (fctId_t)32, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer48,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_04, NULL},
    {(lsgId_t)66, (fctId_t)33, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer49,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_01, NULL},
    {(lsgId_t)66, (fctId_t)33, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer49,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_02, NULL},
    {(lsgId_t)66, (fctId_t)33, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer49,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_03, NULL},
    {(lsgId_t)66, (fctId_t)33, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer49,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_04, NULL},
    {(lsgId_t)66, (fctId_t)34, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer50,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_01, NULL},
    {(lsgId_t)66, (fctId_t)34, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer50,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_02, NULL},
    {(lsgId_t)66, (fctId_t)34, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer50,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_03, NULL},
    {(lsgId_t)66, (fctId_t)34, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer50,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_04, NULL},
    {(lsgId_t)66, (fctId_t)35, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer51,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_01, NULL},
    {(lsgId_t)66, (fctId_t)35, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer51,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_02, NULL},
    {(lsgId_t)66, (fctId_t)35, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer51,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_03, NULL},
    {(lsgId_t)66, (fctId_t)35, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer51,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_04, NULL},
    {(lsgId_t)66, (fctId_t)36, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_01, NULL},
    {(lsgId_t)66, (fctId_t)36, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_02, NULL},
    {(lsgId_t)66, (fctId_t)36, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_03, NULL},
    {(lsgId_t)66, (fctId_t)36, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_04, NULL},
    {(lsgId_t)66, (fctId_t)37, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer52,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_01, NULL},
    {(lsgId_t)66, (fctId_t)37, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer52,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_02, NULL},
    {(lsgId_t)66, (fctId_t)37, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer52,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_03, NULL},
    {(lsgId_t)66, (fctId_t)37, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer52,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_04, NULL},
    {(lsgId_t)66, (fctId_t)38, 18u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[36], &BCL_RxBuffer53,  &BAP_u16InterTelegramTimerTable[36], (BapCanMsgId_t) BAP_KlimaMaster_ASG_01, &BAP_CanRxSegmentationChannels[3]},
    {(lsgId_t)66, (fctId_t)38, 18u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[37], &BCL_RxBuffer53,  &BAP_u16InterTelegramTimerTable[37], (BapCanMsgId_t) BAP_KlimaMaster_ASG_02, &BAP_CanRxSegmentationChannels[2]},
    {(lsgId_t)66, (fctId_t)38, 18u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[38], &BCL_RxBuffer53,  &BAP_u16InterTelegramTimerTable[38], (BapCanMsgId_t) BAP_KlimaMaster_ASG_03, &BAP_CanRxSegmentationChannels[1]},
    {(lsgId_t)66, (fctId_t)38, 18u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[39], &BCL_RxBuffer53,  &BAP_u16InterTelegramTimerTable[39], (BapCanMsgId_t) BAP_KlimaMaster_ASG_04, &BAP_CanRxSegmentationChannels[0]},
    {(lsgId_t)66, (fctId_t)39, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer54,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_01, NULL},
    {(lsgId_t)66, (fctId_t)39, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer54,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_02, NULL},
    {(lsgId_t)66, (fctId_t)39, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer54,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_03, NULL},
    {(lsgId_t)66, (fctId_t)39, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer54,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_04, NULL},
    {(lsgId_t)66, (fctId_t)40, 273u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[40], &BCL_RxBuffer55,  &BAP_u16InterTelegramTimerTable[40], (BapCanMsgId_t) BAP_KlimaMaster_ASG_02, &BAP_CanRxSegmentationChannels[2]},
    {(lsgId_t)66, (fctId_t)41, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer56,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_01, NULL},
    {(lsgId_t)66, (fctId_t)41, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer56,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_02, NULL},
    {(lsgId_t)66, (fctId_t)41, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer56,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_03, NULL},
    {(lsgId_t)66, (fctId_t)41, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer56,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_04, NULL},
    {(lsgId_t)66, (fctId_t)42, 44u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[41], &BCL_RxBuffer57,  &BAP_u16InterTelegramTimerTable[41], (BapCanMsgId_t) BAP_KlimaMaster_ASG_01, &BAP_CanRxSegmentationChannels[3]},
    {(lsgId_t)66, (fctId_t)42, 44u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[42], &BCL_RxBuffer57,  &BAP_u16InterTelegramTimerTable[42], (BapCanMsgId_t) BAP_KlimaMaster_ASG_02, &BAP_CanRxSegmentationChannels[2]},
    {(lsgId_t)66, (fctId_t)42, 44u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[43], &BCL_RxBuffer57,  &BAP_u16InterTelegramTimerTable[43], (BapCanMsgId_t) BAP_KlimaMaster_ASG_03, &BAP_CanRxSegmentationChannels[1]},
    {(lsgId_t)66, (fctId_t)42, 44u, 20u, BapSegType_ChannelOneTwoThreeFour, 50u, &BAP_u16CanRxSegmentationTable[44], &BCL_RxBuffer57,  &BAP_u16InterTelegramTimerTable[44], (BapCanMsgId_t) BAP_KlimaMaster_ASG_04, &BAP_CanRxSegmentationChannels[0]},
    {(lsgId_t)66, (fctId_t)43, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer58,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_01, NULL},
    {(lsgId_t)66, (fctId_t)43, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer58,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_02, NULL},
    {(lsgId_t)66, (fctId_t)43, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer58,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_03, NULL},
    {(lsgId_t)66, (fctId_t)43, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer58,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_04, NULL},
    {(lsgId_t)66, (fctId_t)44, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer59,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_01, NULL},
    {(lsgId_t)66, (fctId_t)44, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer59,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_02, NULL},
    {(lsgId_t)66, (fctId_t)44, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer59,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_03, NULL},
    {(lsgId_t)66, (fctId_t)44, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer59,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_04, NULL},
    {(lsgId_t)66, (fctId_t)45, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer60,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_01, NULL},
    {(lsgId_t)66, (fctId_t)45, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer60,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_02, NULL},
    {(lsgId_t)66, (fctId_t)45, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer60,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_03, NULL},
    {(lsgId_t)66, (fctId_t)45, 3u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer60,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_04, NULL},
    {(lsgId_t)66, (fctId_t)46, 4u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer61,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_01, NULL},
    {(lsgId_t)66, (fctId_t)46, 4u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer61,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_02, NULL},
    {(lsgId_t)66, (fctId_t)46, 4u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer61,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_03, NULL},
    {(lsgId_t)66, (fctId_t)46, 4u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer61,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_04, NULL},
    {(lsgId_t)66, (fctId_t)47, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_01, NULL},
    {(lsgId_t)66, (fctId_t)47, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_02, NULL},
    {(lsgId_t)66, (fctId_t)47, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_03, NULL},
    {(lsgId_t)66, (fctId_t)47, 0u, 20u, BapSegType_Unsegmented, 0u, NULL, (BapBclRxRamRow_pot) NULL,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_04, NULL},
    {(lsgId_t)66, (fctId_t)48, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer62,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_01, NULL},
    {(lsgId_t)66, (fctId_t)48, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer62,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_02, NULL},
    {(lsgId_t)66, (fctId_t)48, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer62,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_03, NULL},
    {(lsgId_t)66, (fctId_t)48, 6u, 20u, BapSegType_Unsegmented, 0u, NULL, &BCL_RxBuffer62,  NULL, (BapCanMsgId_t) BAP_KlimaMaster_ASG_04, NULL}
};

#define BAP_STOP_SEC_CONST_UNSPECIFIED
#include <BAP_MemMap.h>

#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
/* CAN Rx Ringbuffer */
BAP_RAM_DATA_FAR
uint8_t BAP_CanRxRingBuffer[BAP_CAN_RX_RING_BUFFER_SIZE] = {0};

BAP_RAM_DATA_FAR
bool_t BAP_u8CanRxRingBufferMessageLost = 0u;


#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
#define BAP_START_SEC_CONST_UNSPECIFIED
#include <BAP_MemMap.h>
/* BCL Bus Indirection Tx Tabelle *********************************************/
BAP_ROM_DATA_FAR BapBusIndirectionTxRomRow_ot BAP_ROM_CONST BAP_BusIndTxTable[]={
    /*                                 eInterfaceType, BusTxRomRow, poBclTxRamRow, u32BufferSize, bDataTypeSupportsVarLength */
    /* LSG#id="1", Function#id="1" */{ BapIft_Can,  &BAP_CanTxRomTable[0],  &BCL_TxBuffer0, 214u, BAP_TRUE },
    /* LSG#id="1", Function#id="2" */{ BapIft_Can,  &BAP_CanTxRomTable[1],  &BCL_TxBuffer1, 6u, BAP_FALSE },
    /* LSG#id="1", Function#id="3" */{ BapIft_Can,  &BAP_CanTxRomTable[2],  &BCL_TxBuffer2, 8u, BAP_TRUE },
    /* LSG#id="1", Function#id="4" */{ BapIft_Can,  &BAP_CanTxRomTable[3],  &BCL_TxBuffer3, 1u, BAP_FALSE },
    /* LSG#id="1", Function#id="13" */{ BapIft_Can,  &BAP_CanTxRomTable[4],  &BCL_TxBuffer4, 1u, BAP_FALSE },
    /* LSG#id="1", Function#id="14" */{ BapIft_Can,  &BAP_CanTxRomTable[5],  &BCL_TxBuffer5, 11u, BAP_TRUE },
    /* LSG#id="1", Function#id="15" */{ BapIft_Can,  &BAP_CanTxRomTable[6],  &BCL_TxBuffer6, 1u, BAP_FALSE },
    /* LSG#id="1", Function#id="16" */{ BapIft_Can,  &BAP_CanTxRomTable[7],  &BCL_TxBuffer7, 6u, BAP_FALSE },
    /* LSG#id="1", Function#id="17" */{ BapIft_Can,  &BAP_CanTxRomTable[8],  &BCL_TxBuffer8, 6u, BAP_FALSE },
    /* LSG#id="1", Function#id="18" */{ BapIft_Can,  &BAP_CanTxRomTable[9],  &BCL_TxBuffer9, 4u, BAP_FALSE },
    /* LSG#id="1", Function#id="19" */{ BapIft_Can,  &BAP_CanTxRomTable[10],  &BCL_TxBuffer10, 4u, BAP_FALSE },
    /* LSG#id="1", Function#id="20" */{ BapIft_Can,  &BAP_CanTxRomTable[11],  &BCL_TxBuffer11, 5u, BAP_FALSE },
    /* LSG#id="1", Function#id="21" */{ BapIft_Can,  &BAP_CanTxRomTable[12],  &BCL_TxBuffer12, 5u, BAP_FALSE },
    /* LSG#id="1", Function#id="22" */{ BapIft_Can,  &BAP_CanTxRomTable[13],  &BCL_TxBuffer13, 7u, BAP_TRUE },
    /* LSG#id="1", Function#id="23" */{ BapIft_Can,  &BAP_CanTxRomTable[14],  &BCL_TxBuffer14, 7u, BAP_TRUE },
    /* LSG#id="1", Function#id="24" */{ BapIft_Can,  &BAP_CanTxRomTable[15],  &BCL_TxBuffer15, 4u, BAP_FALSE },
    /* LSG#id="1", Function#id="25" */{ BapIft_Can,  &BAP_CanTxRomTable[16],  &BCL_TxBuffer16, 4u, BAP_FALSE },
    /* LSG#id="1", Function#id="26" */{ BapIft_Can,  &BAP_CanTxRomTable[17],  &BCL_TxBuffer17, 3u, BAP_FALSE },
    /* LSG#id="1", Function#id="27" */{ BapIft_Can,  &BAP_CanTxRomTable[18],  &BCL_TxBuffer18, 3u, BAP_FALSE },
    /* LSG#id="1", Function#id="28" */{ BapIft_Can,  &BAP_CanTxRomTable[19],  &BCL_TxBuffer19, 2u, BAP_FALSE },
    /* LSG#id="1", Function#id="29" */{ BapIft_Can,  &BAP_CanTxRomTable[20],  &BCL_TxBuffer20, 2u, BAP_FALSE },
    /* LSG#id="1", Function#id="30" */{ BapIft_Can,  &BAP_CanTxRomTable[21],  &BCL_TxBuffer21, 3u, BAP_FALSE },
    /* LSG#id="1", Function#id="31" */{ BapIft_Can,  &BAP_CanTxRomTable[22],  &BCL_TxBuffer22, 3u, BAP_FALSE },
    /* LSG#id="1", Function#id="32" */{ BapIft_Can,  &BAP_CanTxRomTable[23],  &BCL_TxBuffer23, 3u, BAP_FALSE },
    /* LSG#id="1", Function#id="33" */{ BapIft_Can,  &BAP_CanTxRomTable[24],  &BCL_TxBuffer24, 3u, BAP_FALSE },
    /* LSG#id="1", Function#id="34" */{ BapIft_Can,  &BAP_CanTxRomTable[25],  &BCL_TxBuffer25, 5u, BAP_FALSE },
    /* LSG#id="1", Function#id="35" */{ BapIft_Can,  &BAP_CanTxRomTable[26],  &BCL_TxBuffer26, 5u, BAP_FALSE },
    /* LSG#id="1", Function#id="36" */{ BapIft_Can,  &BAP_CanTxRomTable[27],  &BCL_TxBuffer27, 113u, BAP_TRUE },
    /* LSG#id="1", Function#id="37" */{ BapIft_Can,  &BAP_CanTxRomTable[28],  &BCL_TxBuffer28, 1u, BAP_FALSE },
    /* LSG#id="1", Function#id="38" */{ BapIft_Can,  &BAP_CanTxRomTable[29],  &BCL_TxBuffer29, 2u, BAP_FALSE },
    /* LSG#id="1", Function#id="39" */{ BapIft_Can,  &BAP_CanTxRomTable[30],  &BCL_TxBuffer30, 4u, BAP_FALSE },
    /* LSG#id="1", Function#id="40" */{ BapIft_Can,  &BAP_CanTxRomTable[31],  &BCL_TxBuffer31, 4u, BAP_FALSE },
    /* LSG#id="1", Function#id="41" */{ BapIft_Can,  &BAP_CanTxRomTable[32],  &BCL_TxBuffer32, 5u, BAP_FALSE },
    /* LSG#id="1", Function#id="42" */{ BapIft_Can,  &BAP_CanTxRomTable[33],  &BCL_TxBuffer33, 11u, BAP_TRUE },
    /* LSG#id="1", Function#id="43" */{ BapIft_Can,  &BAP_CanTxRomTable[34],  &BCL_TxBuffer34, 9u, BAP_TRUE },
    /* LSG#id="1", Function#id="44" */{ BapIft_Can,  &BAP_CanTxRomTable[35],  &BCL_TxBuffer35, 9u, BAP_TRUE },
    /* LSG#id="1", Function#id="45" */{ BapIft_Can,  &BAP_CanTxRomTable[36],  &BCL_TxBuffer36, 25u, BAP_TRUE },
    /* LSG#id="1", Function#id="46" */{ BapIft_Can,  &BAP_CanTxRomTable[37],  &BCL_TxBuffer37, 6u, BAP_FALSE },
    /* LSG#id="1", Function#id="47" */{ BapIft_Can,  &BAP_CanTxRomTable[38],  &BCL_TxBuffer38, 6u, BAP_FALSE },
    /* LSG#id="1", Function#id="48" */{ BapIft_Can,  &BAP_CanTxRomTable[39],  &BCL_TxBuffer39, 8u, BAP_TRUE },
    /* LSG#id="1", Function#id="49" */{ BapIft_Can,  &BAP_CanTxRomTable[40],  &BCL_TxBuffer40, 8u, BAP_TRUE },
    /* LSG#id="1", Function#id="50" */{ BapIft_Can,  &BAP_CanTxRomTable[41],  &BCL_TxBuffer41, 6u, BAP_FALSE },
    /* LSG#id="1", Function#id="51" */{ BapIft_Can,  &BAP_CanTxRomTable[42],  &BCL_TxBuffer42, 6u, BAP_FALSE },
    /* LSG#id="66", Function#id="1" */{ BapIft_Can,  &BAP_CanTxRomTable[43],  &BCL_TxBuffer43, 170u, BAP_TRUE },
    /* LSG#id="66", Function#id="2" */{ BapIft_Can,  &BAP_CanTxRomTable[44],  &BCL_TxBuffer44, 6u, BAP_FALSE },
    /* LSG#id="66", Function#id="3" */{ BapIft_Can,  &BAP_CanTxRomTable[45],  &BCL_TxBuffer45, 8u, BAP_TRUE },
    /* LSG#id="66", Function#id="4" */{ BapIft_Can,  &BAP_CanTxRomTable[46],  &BCL_TxBuffer46, 1u, BAP_FALSE },
    /* LSG#id="66", Function#id="13" */{ BapIft_Can,  &BAP_CanTxRomTable[47],  &BCL_TxBuffer47, 1u, BAP_FALSE },
    /* LSG#id="66", Function#id="14" */{ BapIft_Can,  &BAP_CanTxRomTable[48],  &BCL_TxBuffer48, 8u, BAP_TRUE },
    /* LSG#id="66", Function#id="15" */{ BapIft_Can,  &BAP_CanTxRomTable[49],  &BCL_TxBuffer49, 1u, BAP_FALSE },
    /* LSG#id="66", Function#id="16" */{ BapIft_Can,  &BAP_CanTxRomTable[50],  &BCL_TxBuffer50, 2u, BAP_FALSE },
    /* LSG#id="66", Function#id="17" */{ BapIft_Can,  &BAP_CanTxRomTable[51],  &BCL_TxBuffer51, 2u, BAP_FALSE },
    /* LSG#id="66", Function#id="18" */{ BapIft_Can,  &BAP_CanTxRomTable[52],  &BCL_TxBuffer52, 3u, BAP_FALSE },
    /* LSG#id="66", Function#id="19" */{ BapIft_Can,  &BAP_CanTxRomTable[53],  &BCL_TxBuffer53, 2u, BAP_FALSE },
    /* LSG#id="66", Function#id="20" */{ BapIft_Can,  &BAP_CanTxRomTable[54],  &BCL_TxBuffer54, 3u, BAP_FALSE },
    /* LSG#id="66", Function#id="21" */{ BapIft_Can,  &BAP_CanTxRomTable[55],  &BCL_TxBuffer55, 3u, BAP_FALSE },
    /* LSG#id="66", Function#id="22" */{ BapIft_Can,  &BAP_CanTxRomTable[56],  &BCL_TxBuffer56, 9u, BAP_TRUE },
    /* LSG#id="66", Function#id="23" */{ BapIft_Can,  &BAP_CanTxRomTable[57],  &BCL_TxBuffer57, 3u, BAP_FALSE },
    /* LSG#id="66", Function#id="24" */{ BapIft_Can,  &BAP_CanTxRomTable[58],  &BCL_TxBuffer58, 3u, BAP_FALSE },
    /* LSG#id="66", Function#id="25" */{ BapIft_Can,  &BAP_CanTxRomTable[59],  &BCL_TxBuffer59, 3u, BAP_FALSE },
    /* LSG#id="66", Function#id="26" */{ BapIft_Can,  &BAP_CanTxRomTable[60],  &BCL_TxBuffer60, 4u, BAP_FALSE },
    /* LSG#id="66", Function#id="27" */{ BapIft_Can,  &BAP_CanTxRomTable[61],  &BCL_TxBuffer61, 3u, BAP_FALSE },
    /* LSG#id="66", Function#id="28" */{ BapIft_Can,  &BAP_CanTxRomTable[62],  &BCL_TxBuffer62, 3u, BAP_FALSE },
    /* LSG#id="66", Function#id="29" */{ BapIft_Can,  &BAP_CanTxRomTable[63],  &BCL_TxBuffer63, 3u, BAP_FALSE },
    /* LSG#id="66", Function#id="30" */{ BapIft_Can,  &BAP_CanTxRomTable[64],  &BCL_TxBuffer64, 3u, BAP_FALSE },
    /* LSG#id="66", Function#id="31" */{ BapIft_Can,  &BAP_CanTxRomTable[65],  &BCL_TxBuffer65, 3u, BAP_FALSE },
    /* LSG#id="66", Function#id="32" */{ BapIft_Can,  &BAP_CanTxRomTable[66],  &BCL_TxBuffer66, 3u, BAP_FALSE },
    /* LSG#id="66", Function#id="33" */{ BapIft_Can,  &BAP_CanTxRomTable[67],  &BCL_TxBuffer67, 3u, BAP_FALSE },
    /* LSG#id="66", Function#id="34" */{ BapIft_Can,  &BAP_CanTxRomTable[68],  &BCL_TxBuffer68, 6u, BAP_FALSE },
    /* LSG#id="66", Function#id="35" */{ BapIft_Can,  &BAP_CanTxRomTable[69],  &BCL_TxBuffer69, 6u, BAP_FALSE },
    /* LSG#id="66", Function#id="36" */{ BapIft_Can,  &BAP_CanTxRomTable[70],  &BCL_TxBuffer70, 6u, BAP_FALSE },
    /* LSG#id="66", Function#id="37" */{ BapIft_Can,  &BAP_CanTxRomTable[71],  &BCL_TxBuffer71, 6u, BAP_FALSE },
    /* LSG#id="66", Function#id="38" */{ BapIft_Can,  &BAP_CanTxRomTable[72],  &BCL_TxBuffer72, 18u, BAP_TRUE },
    /* LSG#id="66", Function#id="39" */{ BapIft_Can,  &BAP_CanTxRomTable[73],  &BCL_TxBuffer73, 3u, BAP_FALSE },
    /* LSG#id="66", Function#id="40" */{ BapIft_Can,  &BAP_CanTxRomTable[74],  &BCL_TxBuffer74, 276u, BAP_TRUE },
    /* LSG#id="66", Function#id="41" */{ BapIft_Can,  &BAP_CanTxRomTable[75],  &BCL_TxBuffer75, 3u, BAP_FALSE },
    /* LSG#id="66", Function#id="42" */{ BapIft_Can,  &BAP_CanTxRomTable[76],  &BCL_TxBuffer76, 45u, BAP_TRUE },
    /* LSG#id="66", Function#id="43" */{ BapIft_Can,  &BAP_CanTxRomTable[77],  &BCL_TxBuffer77, 6u, BAP_FALSE },
    /* LSG#id="66", Function#id="44" */{ BapIft_Can,  &BAP_CanTxRomTable[78],  &BCL_TxBuffer78, 6u, BAP_FALSE },
    /* LSG#id="66", Function#id="45" */{ BapIft_Can,  &BAP_CanTxRomTable[79],  &BCL_TxBuffer79, 3u, BAP_FALSE },
    /* LSG#id="66", Function#id="46" */{ BapIft_Can,  &BAP_CanTxRomTable[80],  &BCL_TxBuffer80, 4u, BAP_FALSE },
    /* LSG#id="66", Function#id="47" */{ BapIft_Can,  &BAP_CanTxRomTable[81],  &BCL_TxBuffer81, 6u, BAP_FALSE },
    /* LSG#id="66", Function#id="48" */{ BapIft_Can,  &BAP_CanTxRomTable[82],  &BCL_TxBuffer82, 6u, BAP_FALSE }
};

/* BCL Bus Indirection Rx Tabelle *********************************************/
BAP_ROM_DATA_FAR BapBusIndirectionRxRomRow_ot BAP_ROM_CONST BAP_BusIndRxTable[]=
{
    /*                                 eInterfaceType, BusRxRomRow, poBclRxRamRow */
    /* LSG#id="1", Function#id="1" */{ BapIft_Can,  &BAP_CanRxRomTable[0], NULL},
    /* LSG#id="1", Function#id="1" */{ BapIft_Can,  &BAP_CanRxRomTable[1], NULL},
    /* LSG#id="1", Function#id="1" */{ BapIft_Can,  &BAP_CanRxRomTable[2], NULL},
    /* LSG#id="1", Function#id="1" */{ BapIft_Can,  &BAP_CanRxRomTable[3], NULL},
    /* LSG#id="1", Function#id="2" */{ BapIft_Can,  &BAP_CanRxRomTable[4], NULL},
    /* LSG#id="1", Function#id="2" */{ BapIft_Can,  &BAP_CanRxRomTable[5], NULL},
    /* LSG#id="1", Function#id="2" */{ BapIft_Can,  &BAP_CanRxRomTable[6], NULL},
    /* LSG#id="1", Function#id="2" */{ BapIft_Can,  &BAP_CanRxRomTable[7], NULL},
    /* LSG#id="1", Function#id="3" */{ BapIft_Can,  &BAP_CanRxRomTable[8], NULL},
    /* LSG#id="1", Function#id="3" */{ BapIft_Can,  &BAP_CanRxRomTable[9], NULL},
    /* LSG#id="1", Function#id="3" */{ BapIft_Can,  &BAP_CanRxRomTable[10], NULL},
    /* LSG#id="1", Function#id="3" */{ BapIft_Can,  &BAP_CanRxRomTable[11], NULL},
    /* LSG#id="1", Function#id="4" */{ BapIft_Can,  &BAP_CanRxRomTable[12], NULL},
    /* LSG#id="1", Function#id="4" */{ BapIft_Can,  &BAP_CanRxRomTable[13], NULL},
    /* LSG#id="1", Function#id="4" */{ BapIft_Can,  &BAP_CanRxRomTable[14], NULL},
    /* LSG#id="1", Function#id="4" */{ BapIft_Can,  &BAP_CanRxRomTable[15], NULL},
    /* LSG#id="1", Function#id="13" */{ BapIft_Can,  &BAP_CanRxRomTable[16], NULL},
    /* LSG#id="1", Function#id="13" */{ BapIft_Can,  &BAP_CanRxRomTable[17], NULL},
    /* LSG#id="1", Function#id="13" */{ BapIft_Can,  &BAP_CanRxRomTable[18], NULL},
    /* LSG#id="1", Function#id="13" */{ BapIft_Can,  &BAP_CanRxRomTable[19], NULL},
    /* LSG#id="1", Function#id="14" */{ BapIft_Can,  &BAP_CanRxRomTable[20], NULL},
    /* LSG#id="1", Function#id="14" */{ BapIft_Can,  &BAP_CanRxRomTable[21], NULL},
    /* LSG#id="1", Function#id="14" */{ BapIft_Can,  &BAP_CanRxRomTable[22], NULL},
    /* LSG#id="1", Function#id="14" */{ BapIft_Can,  &BAP_CanRxRomTable[23], NULL},
    /* LSG#id="1", Function#id="15" */{ BapIft_Can,  &BAP_CanRxRomTable[24], NULL},
    /* LSG#id="1", Function#id="15" */{ BapIft_Can,  &BAP_CanRxRomTable[25], NULL},
    /* LSG#id="1", Function#id="15" */{ BapIft_Can,  &BAP_CanRxRomTable[26], NULL},
    /* LSG#id="1", Function#id="15" */{ BapIft_Can,  &BAP_CanRxRomTable[27], NULL},
    /* LSG#id="1", Function#id="16" */{ BapIft_Can,  &BAP_CanRxRomTable[28],  &BCL_RxBuffer0},
    /* LSG#id="1", Function#id="16" */{ BapIft_Can,  &BAP_CanRxRomTable[29],  &BCL_RxBuffer0},
    /* LSG#id="1", Function#id="16" */{ BapIft_Can,  &BAP_CanRxRomTable[30],  &BCL_RxBuffer0},
    /* LSG#id="1", Function#id="16" */{ BapIft_Can,  &BAP_CanRxRomTable[31],  &BCL_RxBuffer0},
    /* LSG#id="1", Function#id="17" */{ BapIft_Can,  &BAP_CanRxRomTable[32],  &BCL_RxBuffer1},
    /* LSG#id="1", Function#id="17" */{ BapIft_Can,  &BAP_CanRxRomTable[33],  &BCL_RxBuffer1},
    /* LSG#id="1", Function#id="17" */{ BapIft_Can,  &BAP_CanRxRomTable[34],  &BCL_RxBuffer1},
    /* LSG#id="1", Function#id="17" */{ BapIft_Can,  &BAP_CanRxRomTable[35],  &BCL_RxBuffer1},
    /* LSG#id="1", Function#id="18" */{ BapIft_Can,  &BAP_CanRxRomTable[36],  &BCL_RxBuffer2},
    /* LSG#id="1", Function#id="18" */{ BapIft_Can,  &BAP_CanRxRomTable[37],  &BCL_RxBuffer2},
    /* LSG#id="1", Function#id="18" */{ BapIft_Can,  &BAP_CanRxRomTable[38],  &BCL_RxBuffer2},
    /* LSG#id="1", Function#id="18" */{ BapIft_Can,  &BAP_CanRxRomTable[39],  &BCL_RxBuffer2},
    /* LSG#id="1", Function#id="19" */{ BapIft_Can,  &BAP_CanRxRomTable[40],  &BCL_RxBuffer3},
    /* LSG#id="1", Function#id="19" */{ BapIft_Can,  &BAP_CanRxRomTable[41],  &BCL_RxBuffer3},
    /* LSG#id="1", Function#id="19" */{ BapIft_Can,  &BAP_CanRxRomTable[42],  &BCL_RxBuffer3},
    /* LSG#id="1", Function#id="19" */{ BapIft_Can,  &BAP_CanRxRomTable[43],  &BCL_RxBuffer3},
    /* LSG#id="1", Function#id="20" */{ BapIft_Can,  &BAP_CanRxRomTable[44],  &BCL_RxBuffer4},
    /* LSG#id="1", Function#id="20" */{ BapIft_Can,  &BAP_CanRxRomTable[45],  &BCL_RxBuffer4},
    /* LSG#id="1", Function#id="20" */{ BapIft_Can,  &BAP_CanRxRomTable[46],  &BCL_RxBuffer4},
    /* LSG#id="1", Function#id="20" */{ BapIft_Can,  &BAP_CanRxRomTable[47],  &BCL_RxBuffer4},
    /* LSG#id="1", Function#id="21" */{ BapIft_Can,  &BAP_CanRxRomTable[48],  &BCL_RxBuffer5},
    /* LSG#id="1", Function#id="21" */{ BapIft_Can,  &BAP_CanRxRomTable[49],  &BCL_RxBuffer5},
    /* LSG#id="1", Function#id="21" */{ BapIft_Can,  &BAP_CanRxRomTable[50],  &BCL_RxBuffer5},
    /* LSG#id="1", Function#id="21" */{ BapIft_Can,  &BAP_CanRxRomTable[51],  &BCL_RxBuffer5},
    /* LSG#id="1", Function#id="22" */{ BapIft_Can,  &BAP_CanRxRomTable[52],  &BCL_RxBuffer6},
    /* LSG#id="1", Function#id="22" */{ BapIft_Can,  &BAP_CanRxRomTable[53],  &BCL_RxBuffer6},
    /* LSG#id="1", Function#id="22" */{ BapIft_Can,  &BAP_CanRxRomTable[54],  &BCL_RxBuffer6},
    /* LSG#id="1", Function#id="22" */{ BapIft_Can,  &BAP_CanRxRomTable[55],  &BCL_RxBuffer6},
    /* LSG#id="1", Function#id="23" */{ BapIft_Can,  &BAP_CanRxRomTable[56],  &BCL_RxBuffer7},
    /* LSG#id="1", Function#id="23" */{ BapIft_Can,  &BAP_CanRxRomTable[57],  &BCL_RxBuffer7},
    /* LSG#id="1", Function#id="23" */{ BapIft_Can,  &BAP_CanRxRomTable[58],  &BCL_RxBuffer7},
    /* LSG#id="1", Function#id="23" */{ BapIft_Can,  &BAP_CanRxRomTable[59],  &BCL_RxBuffer7},
    /* LSG#id="1", Function#id="24" */{ BapIft_Can,  &BAP_CanRxRomTable[60],  &BCL_RxBuffer8},
    /* LSG#id="1", Function#id="24" */{ BapIft_Can,  &BAP_CanRxRomTable[61],  &BCL_RxBuffer8},
    /* LSG#id="1", Function#id="24" */{ BapIft_Can,  &BAP_CanRxRomTable[62],  &BCL_RxBuffer8},
    /* LSG#id="1", Function#id="24" */{ BapIft_Can,  &BAP_CanRxRomTable[63],  &BCL_RxBuffer8},
    /* LSG#id="1", Function#id="25" */{ BapIft_Can,  &BAP_CanRxRomTable[64],  &BCL_RxBuffer9},
    /* LSG#id="1", Function#id="25" */{ BapIft_Can,  &BAP_CanRxRomTable[65],  &BCL_RxBuffer9},
    /* LSG#id="1", Function#id="25" */{ BapIft_Can,  &BAP_CanRxRomTable[66],  &BCL_RxBuffer9},
    /* LSG#id="1", Function#id="25" */{ BapIft_Can,  &BAP_CanRxRomTable[67],  &BCL_RxBuffer9},
    /* LSG#id="1", Function#id="26" */{ BapIft_Can,  &BAP_CanRxRomTable[68],  &BCL_RxBuffer10},
    /* LSG#id="1", Function#id="26" */{ BapIft_Can,  &BAP_CanRxRomTable[69],  &BCL_RxBuffer10},
    /* LSG#id="1", Function#id="26" */{ BapIft_Can,  &BAP_CanRxRomTable[70],  &BCL_RxBuffer10},
    /* LSG#id="1", Function#id="26" */{ BapIft_Can,  &BAP_CanRxRomTable[71],  &BCL_RxBuffer10},
    /* LSG#id="1", Function#id="27" */{ BapIft_Can,  &BAP_CanRxRomTable[72],  &BCL_RxBuffer11},
    /* LSG#id="1", Function#id="27" */{ BapIft_Can,  &BAP_CanRxRomTable[73],  &BCL_RxBuffer11},
    /* LSG#id="1", Function#id="27" */{ BapIft_Can,  &BAP_CanRxRomTable[74],  &BCL_RxBuffer11},
    /* LSG#id="1", Function#id="27" */{ BapIft_Can,  &BAP_CanRxRomTable[75],  &BCL_RxBuffer11},
    /* LSG#id="1", Function#id="28" */{ BapIft_Can,  &BAP_CanRxRomTable[76], NULL},
    /* LSG#id="1", Function#id="28" */{ BapIft_Can,  &BAP_CanRxRomTable[77], NULL},
    /* LSG#id="1", Function#id="28" */{ BapIft_Can,  &BAP_CanRxRomTable[78], NULL},
    /* LSG#id="1", Function#id="28" */{ BapIft_Can,  &BAP_CanRxRomTable[79], NULL},
    /* LSG#id="1", Function#id="29" */{ BapIft_Can,  &BAP_CanRxRomTable[80], NULL},
    /* LSG#id="1", Function#id="29" */{ BapIft_Can,  &BAP_CanRxRomTable[81], NULL},
    /* LSG#id="1", Function#id="29" */{ BapIft_Can,  &BAP_CanRxRomTable[82], NULL},
    /* LSG#id="1", Function#id="29" */{ BapIft_Can,  &BAP_CanRxRomTable[83], NULL},
    /* LSG#id="1", Function#id="30" */{ BapIft_Can,  &BAP_CanRxRomTable[84],  &BCL_RxBuffer12},
    /* LSG#id="1", Function#id="30" */{ BapIft_Can,  &BAP_CanRxRomTable[85],  &BCL_RxBuffer12},
    /* LSG#id="1", Function#id="30" */{ BapIft_Can,  &BAP_CanRxRomTable[86],  &BCL_RxBuffer12},
    /* LSG#id="1", Function#id="30" */{ BapIft_Can,  &BAP_CanRxRomTable[87],  &BCL_RxBuffer12},
    /* LSG#id="1", Function#id="31" */{ BapIft_Can,  &BAP_CanRxRomTable[88],  &BCL_RxBuffer13},
    /* LSG#id="1", Function#id="31" */{ BapIft_Can,  &BAP_CanRxRomTable[89],  &BCL_RxBuffer13},
    /* LSG#id="1", Function#id="31" */{ BapIft_Can,  &BAP_CanRxRomTable[90],  &BCL_RxBuffer13},
    /* LSG#id="1", Function#id="31" */{ BapIft_Can,  &BAP_CanRxRomTable[91],  &BCL_RxBuffer13},
    /* LSG#id="1", Function#id="32" */{ BapIft_Can,  &BAP_CanRxRomTable[92],  &BCL_RxBuffer14},
    /* LSG#id="1", Function#id="32" */{ BapIft_Can,  &BAP_CanRxRomTable[93],  &BCL_RxBuffer14},
    /* LSG#id="1", Function#id="32" */{ BapIft_Can,  &BAP_CanRxRomTable[94],  &BCL_RxBuffer14},
    /* LSG#id="1", Function#id="32" */{ BapIft_Can,  &BAP_CanRxRomTable[95],  &BCL_RxBuffer14},
    /* LSG#id="1", Function#id="33" */{ BapIft_Can,  &BAP_CanRxRomTable[96],  &BCL_RxBuffer15},
    /* LSG#id="1", Function#id="33" */{ BapIft_Can,  &BAP_CanRxRomTable[97],  &BCL_RxBuffer15},
    /* LSG#id="1", Function#id="33" */{ BapIft_Can,  &BAP_CanRxRomTable[98],  &BCL_RxBuffer15},
    /* LSG#id="1", Function#id="33" */{ BapIft_Can,  &BAP_CanRxRomTable[99],  &BCL_RxBuffer15},
    /* LSG#id="1", Function#id="34" */{ BapIft_Can,  &BAP_CanRxRomTable[100],  &BCL_RxBuffer16},
    /* LSG#id="1", Function#id="34" */{ BapIft_Can,  &BAP_CanRxRomTable[101],  &BCL_RxBuffer16},
    /* LSG#id="1", Function#id="34" */{ BapIft_Can,  &BAP_CanRxRomTable[102],  &BCL_RxBuffer16},
    /* LSG#id="1", Function#id="34" */{ BapIft_Can,  &BAP_CanRxRomTable[103],  &BCL_RxBuffer16},
    /* LSG#id="1", Function#id="35" */{ BapIft_Can,  &BAP_CanRxRomTable[104],  &BCL_RxBuffer17},
    /* LSG#id="1", Function#id="35" */{ BapIft_Can,  &BAP_CanRxRomTable[105],  &BCL_RxBuffer17},
    /* LSG#id="1", Function#id="35" */{ BapIft_Can,  &BAP_CanRxRomTable[106],  &BCL_RxBuffer17},
    /* LSG#id="1", Function#id="35" */{ BapIft_Can,  &BAP_CanRxRomTable[107],  &BCL_RxBuffer17},
    /* LSG#id="1", Function#id="36" */{ BapIft_Can,  &BAP_CanRxRomTable[108],  &BCL_RxBuffer18},
    /* LSG#id="1", Function#id="36" */{ BapIft_Can,  &BAP_CanRxRomTable[109],  &BCL_RxBuffer18},
    /* LSG#id="1", Function#id="36" */{ BapIft_Can,  &BAP_CanRxRomTable[110],  &BCL_RxBuffer18},
    /* LSG#id="1", Function#id="36" */{ BapIft_Can,  &BAP_CanRxRomTable[111],  &BCL_RxBuffer18},
    /* LSG#id="1", Function#id="37" */{ BapIft_Can,  &BAP_CanRxRomTable[112],  &BCL_RxBuffer19},
    /* LSG#id="1", Function#id="37" */{ BapIft_Can,  &BAP_CanRxRomTable[113],  &BCL_RxBuffer19},
    /* LSG#id="1", Function#id="37" */{ BapIft_Can,  &BAP_CanRxRomTable[114],  &BCL_RxBuffer19},
    /* LSG#id="1", Function#id="37" */{ BapIft_Can,  &BAP_CanRxRomTable[115],  &BCL_RxBuffer19},
    /* LSG#id="1", Function#id="38" */{ BapIft_Can,  &BAP_CanRxRomTable[116], NULL},
    /* LSG#id="1", Function#id="38" */{ BapIft_Can,  &BAP_CanRxRomTable[117], NULL},
    /* LSG#id="1", Function#id="38" */{ BapIft_Can,  &BAP_CanRxRomTable[118], NULL},
    /* LSG#id="1", Function#id="38" */{ BapIft_Can,  &BAP_CanRxRomTable[119], NULL},
    /* LSG#id="1", Function#id="39" */{ BapIft_Can,  &BAP_CanRxRomTable[120],  &BCL_RxBuffer20},
    /* LSG#id="1", Function#id="39" */{ BapIft_Can,  &BAP_CanRxRomTable[121],  &BCL_RxBuffer20},
    /* LSG#id="1", Function#id="39" */{ BapIft_Can,  &BAP_CanRxRomTable[122],  &BCL_RxBuffer20},
    /* LSG#id="1", Function#id="39" */{ BapIft_Can,  &BAP_CanRxRomTable[123],  &BCL_RxBuffer20},
    /* LSG#id="1", Function#id="40" */{ BapIft_Can,  &BAP_CanRxRomTable[124],  &BCL_RxBuffer21},
    /* LSG#id="1", Function#id="40" */{ BapIft_Can,  &BAP_CanRxRomTable[125],  &BCL_RxBuffer21},
    /* LSG#id="1", Function#id="40" */{ BapIft_Can,  &BAP_CanRxRomTable[126],  &BCL_RxBuffer21},
    /* LSG#id="1", Function#id="40" */{ BapIft_Can,  &BAP_CanRxRomTable[127],  &BCL_RxBuffer21},
    /* LSG#id="1", Function#id="41" */{ BapIft_Can,  &BAP_CanRxRomTable[128],  &BCL_RxBuffer22},
    /* LSG#id="1", Function#id="41" */{ BapIft_Can,  &BAP_CanRxRomTable[129],  &BCL_RxBuffer22},
    /* LSG#id="1", Function#id="41" */{ BapIft_Can,  &BAP_CanRxRomTable[130],  &BCL_RxBuffer22},
    /* LSG#id="1", Function#id="41" */{ BapIft_Can,  &BAP_CanRxRomTable[131],  &BCL_RxBuffer22},
    /* LSG#id="1", Function#id="42" */{ BapIft_Can,  &BAP_CanRxRomTable[132], NULL},
    /* LSG#id="1", Function#id="42" */{ BapIft_Can,  &BAP_CanRxRomTable[133], NULL},
    /* LSG#id="1", Function#id="42" */{ BapIft_Can,  &BAP_CanRxRomTable[134], NULL},
    /* LSG#id="1", Function#id="42" */{ BapIft_Can,  &BAP_CanRxRomTable[135], NULL},
    /* LSG#id="1", Function#id="43" */{ BapIft_Can,  &BAP_CanRxRomTable[136],  &BCL_RxBuffer23},
    /* LSG#id="1", Function#id="43" */{ BapIft_Can,  &BAP_CanRxRomTable[137],  &BCL_RxBuffer23},
    /* LSG#id="1", Function#id="43" */{ BapIft_Can,  &BAP_CanRxRomTable[138],  &BCL_RxBuffer23},
    /* LSG#id="1", Function#id="43" */{ BapIft_Can,  &BAP_CanRxRomTable[139],  &BCL_RxBuffer23},
    /* LSG#id="1", Function#id="44" */{ BapIft_Can,  &BAP_CanRxRomTable[140],  &BCL_RxBuffer24},
    /* LSG#id="1", Function#id="44" */{ BapIft_Can,  &BAP_CanRxRomTable[141],  &BCL_RxBuffer24},
    /* LSG#id="1", Function#id="44" */{ BapIft_Can,  &BAP_CanRxRomTable[142],  &BCL_RxBuffer24},
    /* LSG#id="1", Function#id="44" */{ BapIft_Can,  &BAP_CanRxRomTable[143],  &BCL_RxBuffer24},
    /* LSG#id="1", Function#id="45" */{ BapIft_Can,  &BAP_CanRxRomTable[144],  &BCL_RxBuffer25},
    /* LSG#id="1", Function#id="45" */{ BapIft_Can,  &BAP_CanRxRomTable[145],  &BCL_RxBuffer25},
    /* LSG#id="1", Function#id="45" */{ BapIft_Can,  &BAP_CanRxRomTable[146],  &BCL_RxBuffer25},
    /* LSG#id="1", Function#id="45" */{ BapIft_Can,  &BAP_CanRxRomTable[147],  &BCL_RxBuffer25},
    /* LSG#id="1", Function#id="46" */{ BapIft_Can,  &BAP_CanRxRomTable[148],  &BCL_RxBuffer26},
    /* LSG#id="1", Function#id="46" */{ BapIft_Can,  &BAP_CanRxRomTable[149],  &BCL_RxBuffer26},
    /* LSG#id="1", Function#id="46" */{ BapIft_Can,  &BAP_CanRxRomTable[150],  &BCL_RxBuffer26},
    /* LSG#id="1", Function#id="46" */{ BapIft_Can,  &BAP_CanRxRomTable[151],  &BCL_RxBuffer26},
    /* LSG#id="1", Function#id="47" */{ BapIft_Can,  &BAP_CanRxRomTable[152],  &BCL_RxBuffer27},
    /* LSG#id="1", Function#id="47" */{ BapIft_Can,  &BAP_CanRxRomTable[153],  &BCL_RxBuffer27},
    /* LSG#id="1", Function#id="47" */{ BapIft_Can,  &BAP_CanRxRomTable[154],  &BCL_RxBuffer27},
    /* LSG#id="1", Function#id="47" */{ BapIft_Can,  &BAP_CanRxRomTable[155],  &BCL_RxBuffer27},
    /* LSG#id="1", Function#id="48" */{ BapIft_Can,  &BAP_CanRxRomTable[156],  &BCL_RxBuffer28},
    /* LSG#id="1", Function#id="48" */{ BapIft_Can,  &BAP_CanRxRomTable[157],  &BCL_RxBuffer28},
    /* LSG#id="1", Function#id="48" */{ BapIft_Can,  &BAP_CanRxRomTable[158],  &BCL_RxBuffer28},
    /* LSG#id="1", Function#id="48" */{ BapIft_Can,  &BAP_CanRxRomTable[159],  &BCL_RxBuffer28},
    /* LSG#id="1", Function#id="49" */{ BapIft_Can,  &BAP_CanRxRomTable[160],  &BCL_RxBuffer29},
    /* LSG#id="1", Function#id="49" */{ BapIft_Can,  &BAP_CanRxRomTable[161],  &BCL_RxBuffer29},
    /* LSG#id="1", Function#id="49" */{ BapIft_Can,  &BAP_CanRxRomTable[162],  &BCL_RxBuffer29},
    /* LSG#id="1", Function#id="49" */{ BapIft_Can,  &BAP_CanRxRomTable[163],  &BCL_RxBuffer29},
    /* LSG#id="1", Function#id="50" */{ BapIft_Can,  &BAP_CanRxRomTable[164],  &BCL_RxBuffer30},
    /* LSG#id="1", Function#id="50" */{ BapIft_Can,  &BAP_CanRxRomTable[165],  &BCL_RxBuffer30},
    /* LSG#id="1", Function#id="50" */{ BapIft_Can,  &BAP_CanRxRomTable[166],  &BCL_RxBuffer30},
    /* LSG#id="1", Function#id="50" */{ BapIft_Can,  &BAP_CanRxRomTable[167],  &BCL_RxBuffer30},
    /* LSG#id="1", Function#id="51" */{ BapIft_Can,  &BAP_CanRxRomTable[168],  &BCL_RxBuffer31},
    /* LSG#id="1", Function#id="51" */{ BapIft_Can,  &BAP_CanRxRomTable[169],  &BCL_RxBuffer31},
    /* LSG#id="1", Function#id="51" */{ BapIft_Can,  &BAP_CanRxRomTable[170],  &BCL_RxBuffer31},
    /* LSG#id="1", Function#id="51" */{ BapIft_Can,  &BAP_CanRxRomTable[171],  &BCL_RxBuffer31},
    /* LSG#id="66", Function#id="1" */{ BapIft_Can,  &BAP_CanRxRomTable[172], NULL},
    /* LSG#id="66", Function#id="1" */{ BapIft_Can,  &BAP_CanRxRomTable[173], NULL},
    /* LSG#id="66", Function#id="1" */{ BapIft_Can,  &BAP_CanRxRomTable[174], NULL},
    /* LSG#id="66", Function#id="1" */{ BapIft_Can,  &BAP_CanRxRomTable[175], NULL},
    /* LSG#id="66", Function#id="2" */{ BapIft_Can,  &BAP_CanRxRomTable[176], NULL},
    /* LSG#id="66", Function#id="2" */{ BapIft_Can,  &BAP_CanRxRomTable[177], NULL},
    /* LSG#id="66", Function#id="2" */{ BapIft_Can,  &BAP_CanRxRomTable[178], NULL},
    /* LSG#id="66", Function#id="2" */{ BapIft_Can,  &BAP_CanRxRomTable[179], NULL},
    /* LSG#id="66", Function#id="3" */{ BapIft_Can,  &BAP_CanRxRomTable[180], NULL},
    /* LSG#id="66", Function#id="3" */{ BapIft_Can,  &BAP_CanRxRomTable[181], NULL},
    /* LSG#id="66", Function#id="3" */{ BapIft_Can,  &BAP_CanRxRomTable[182], NULL},
    /* LSG#id="66", Function#id="3" */{ BapIft_Can,  &BAP_CanRxRomTable[183], NULL},
    /* LSG#id="66", Function#id="4" */{ BapIft_Can,  &BAP_CanRxRomTable[184], NULL},
    /* LSG#id="66", Function#id="4" */{ BapIft_Can,  &BAP_CanRxRomTable[185], NULL},
    /* LSG#id="66", Function#id="4" */{ BapIft_Can,  &BAP_CanRxRomTable[186], NULL},
    /* LSG#id="66", Function#id="4" */{ BapIft_Can,  &BAP_CanRxRomTable[187], NULL},
    /* LSG#id="66", Function#id="13" */{ BapIft_Can,  &BAP_CanRxRomTable[188], NULL},
    /* LSG#id="66", Function#id="13" */{ BapIft_Can,  &BAP_CanRxRomTable[189], NULL},
    /* LSG#id="66", Function#id="13" */{ BapIft_Can,  &BAP_CanRxRomTable[190], NULL},
    /* LSG#id="66", Function#id="13" */{ BapIft_Can,  &BAP_CanRxRomTable[191], NULL},
    /* LSG#id="66", Function#id="14" */{ BapIft_Can,  &BAP_CanRxRomTable[192], NULL},
    /* LSG#id="66", Function#id="14" */{ BapIft_Can,  &BAP_CanRxRomTable[193], NULL},
    /* LSG#id="66", Function#id="14" */{ BapIft_Can,  &BAP_CanRxRomTable[194], NULL},
    /* LSG#id="66", Function#id="14" */{ BapIft_Can,  &BAP_CanRxRomTable[195], NULL},
    /* LSG#id="66", Function#id="15" */{ BapIft_Can,  &BAP_CanRxRomTable[196], NULL},
    /* LSG#id="66", Function#id="15" */{ BapIft_Can,  &BAP_CanRxRomTable[197], NULL},
    /* LSG#id="66", Function#id="15" */{ BapIft_Can,  &BAP_CanRxRomTable[198], NULL},
    /* LSG#id="66", Function#id="15" */{ BapIft_Can,  &BAP_CanRxRomTable[199], NULL},
    /* LSG#id="66", Function#id="16" */{ BapIft_Can,  &BAP_CanRxRomTable[200],  &BCL_RxBuffer32},
    /* LSG#id="66", Function#id="16" */{ BapIft_Can,  &BAP_CanRxRomTable[201],  &BCL_RxBuffer32},
    /* LSG#id="66", Function#id="16" */{ BapIft_Can,  &BAP_CanRxRomTable[202],  &BCL_RxBuffer32},
    /* LSG#id="66", Function#id="16" */{ BapIft_Can,  &BAP_CanRxRomTable[203],  &BCL_RxBuffer32},
    /* LSG#id="66", Function#id="17" */{ BapIft_Can,  &BAP_CanRxRomTable[204],  &BCL_RxBuffer33},
    /* LSG#id="66", Function#id="17" */{ BapIft_Can,  &BAP_CanRxRomTable[205],  &BCL_RxBuffer33},
    /* LSG#id="66", Function#id="17" */{ BapIft_Can,  &BAP_CanRxRomTable[206],  &BCL_RxBuffer33},
    /* LSG#id="66", Function#id="17" */{ BapIft_Can,  &BAP_CanRxRomTable[207],  &BCL_RxBuffer33},
    /* LSG#id="66", Function#id="18" */{ BapIft_Can,  &BAP_CanRxRomTable[208],  &BCL_RxBuffer34},
    /* LSG#id="66", Function#id="18" */{ BapIft_Can,  &BAP_CanRxRomTable[209],  &BCL_RxBuffer34},
    /* LSG#id="66", Function#id="18" */{ BapIft_Can,  &BAP_CanRxRomTable[210],  &BCL_RxBuffer34},
    /* LSG#id="66", Function#id="18" */{ BapIft_Can,  &BAP_CanRxRomTable[211],  &BCL_RxBuffer34},
    /* LSG#id="66", Function#id="19" */{ BapIft_Can,  &BAP_CanRxRomTable[212],  &BCL_RxBuffer35},
    /* LSG#id="66", Function#id="19" */{ BapIft_Can,  &BAP_CanRxRomTable[213],  &BCL_RxBuffer35},
    /* LSG#id="66", Function#id="19" */{ BapIft_Can,  &BAP_CanRxRomTable[214],  &BCL_RxBuffer35},
    /* LSG#id="66", Function#id="19" */{ BapIft_Can,  &BAP_CanRxRomTable[215],  &BCL_RxBuffer35},
    /* LSG#id="66", Function#id="20" */{ BapIft_Can,  &BAP_CanRxRomTable[216],  &BCL_RxBuffer36},
    /* LSG#id="66", Function#id="20" */{ BapIft_Can,  &BAP_CanRxRomTable[217],  &BCL_RxBuffer36},
    /* LSG#id="66", Function#id="20" */{ BapIft_Can,  &BAP_CanRxRomTable[218],  &BCL_RxBuffer36},
    /* LSG#id="66", Function#id="20" */{ BapIft_Can,  &BAP_CanRxRomTable[219],  &BCL_RxBuffer36},
    /* LSG#id="66", Function#id="21" */{ BapIft_Can,  &BAP_CanRxRomTable[220],  &BCL_RxBuffer37},
    /* LSG#id="66", Function#id="21" */{ BapIft_Can,  &BAP_CanRxRomTable[221],  &BCL_RxBuffer37},
    /* LSG#id="66", Function#id="21" */{ BapIft_Can,  &BAP_CanRxRomTable[222],  &BCL_RxBuffer37},
    /* LSG#id="66", Function#id="21" */{ BapIft_Can,  &BAP_CanRxRomTable[223],  &BCL_RxBuffer37},
    /* LSG#id="66", Function#id="22" */{ BapIft_Can,  &BAP_CanRxRomTable[224],  &BCL_RxBuffer38},
    /* LSG#id="66", Function#id="22" */{ BapIft_Can,  &BAP_CanRxRomTable[225],  &BCL_RxBuffer38},
    /* LSG#id="66", Function#id="22" */{ BapIft_Can,  &BAP_CanRxRomTable[226],  &BCL_RxBuffer38},
    /* LSG#id="66", Function#id="22" */{ BapIft_Can,  &BAP_CanRxRomTable[227],  &BCL_RxBuffer38},
    /* LSG#id="66", Function#id="23" */{ BapIft_Can,  &BAP_CanRxRomTable[228],  &BCL_RxBuffer39},
    /* LSG#id="66", Function#id="23" */{ BapIft_Can,  &BAP_CanRxRomTable[229],  &BCL_RxBuffer39},
    /* LSG#id="66", Function#id="23" */{ BapIft_Can,  &BAP_CanRxRomTable[230],  &BCL_RxBuffer39},
    /* LSG#id="66", Function#id="23" */{ BapIft_Can,  &BAP_CanRxRomTable[231],  &BCL_RxBuffer39},
    /* LSG#id="66", Function#id="24" */{ BapIft_Can,  &BAP_CanRxRomTable[232],  &BCL_RxBuffer40},
    /* LSG#id="66", Function#id="24" */{ BapIft_Can,  &BAP_CanRxRomTable[233],  &BCL_RxBuffer40},
    /* LSG#id="66", Function#id="24" */{ BapIft_Can,  &BAP_CanRxRomTable[234],  &BCL_RxBuffer40},
    /* LSG#id="66", Function#id="24" */{ BapIft_Can,  &BAP_CanRxRomTable[235],  &BCL_RxBuffer40},
    /* LSG#id="66", Function#id="25" */{ BapIft_Can,  &BAP_CanRxRomTable[236],  &BCL_RxBuffer41},
    /* LSG#id="66", Function#id="25" */{ BapIft_Can,  &BAP_CanRxRomTable[237],  &BCL_RxBuffer41},
    /* LSG#id="66", Function#id="25" */{ BapIft_Can,  &BAP_CanRxRomTable[238],  &BCL_RxBuffer41},
    /* LSG#id="66", Function#id="25" */{ BapIft_Can,  &BAP_CanRxRomTable[239],  &BCL_RxBuffer41},
    /* LSG#id="66", Function#id="26" */{ BapIft_Can,  &BAP_CanRxRomTable[240],  &BCL_RxBuffer42},
    /* LSG#id="66", Function#id="26" */{ BapIft_Can,  &BAP_CanRxRomTable[241],  &BCL_RxBuffer42},
    /* LSG#id="66", Function#id="26" */{ BapIft_Can,  &BAP_CanRxRomTable[242],  &BCL_RxBuffer42},
    /* LSG#id="66", Function#id="26" */{ BapIft_Can,  &BAP_CanRxRomTable[243],  &BCL_RxBuffer42},
    /* LSG#id="66", Function#id="27" */{ BapIft_Can,  &BAP_CanRxRomTable[244],  &BCL_RxBuffer43},
    /* LSG#id="66", Function#id="27" */{ BapIft_Can,  &BAP_CanRxRomTable[245],  &BCL_RxBuffer43},
    /* LSG#id="66", Function#id="27" */{ BapIft_Can,  &BAP_CanRxRomTable[246],  &BCL_RxBuffer43},
    /* LSG#id="66", Function#id="27" */{ BapIft_Can,  &BAP_CanRxRomTable[247],  &BCL_RxBuffer43},
    /* LSG#id="66", Function#id="28" */{ BapIft_Can,  &BAP_CanRxRomTable[248],  &BCL_RxBuffer44},
    /* LSG#id="66", Function#id="28" */{ BapIft_Can,  &BAP_CanRxRomTable[249],  &BCL_RxBuffer44},
    /* LSG#id="66", Function#id="28" */{ BapIft_Can,  &BAP_CanRxRomTable[250],  &BCL_RxBuffer44},
    /* LSG#id="66", Function#id="28" */{ BapIft_Can,  &BAP_CanRxRomTable[251],  &BCL_RxBuffer44},
    /* LSG#id="66", Function#id="29" */{ BapIft_Can,  &BAP_CanRxRomTable[252],  &BCL_RxBuffer45},
    /* LSG#id="66", Function#id="29" */{ BapIft_Can,  &BAP_CanRxRomTable[253],  &BCL_RxBuffer45},
    /* LSG#id="66", Function#id="29" */{ BapIft_Can,  &BAP_CanRxRomTable[254],  &BCL_RxBuffer45},
    /* LSG#id="66", Function#id="29" */{ BapIft_Can,  &BAP_CanRxRomTable[255],  &BCL_RxBuffer45},
    /* LSG#id="66", Function#id="30" */{ BapIft_Can,  &BAP_CanRxRomTable[256],  &BCL_RxBuffer46},
    /* LSG#id="66", Function#id="30" */{ BapIft_Can,  &BAP_CanRxRomTable[257],  &BCL_RxBuffer46},
    /* LSG#id="66", Function#id="30" */{ BapIft_Can,  &BAP_CanRxRomTable[258],  &BCL_RxBuffer46},
    /* LSG#id="66", Function#id="30" */{ BapIft_Can,  &BAP_CanRxRomTable[259],  &BCL_RxBuffer46},
    /* LSG#id="66", Function#id="31" */{ BapIft_Can,  &BAP_CanRxRomTable[260],  &BCL_RxBuffer47},
    /* LSG#id="66", Function#id="31" */{ BapIft_Can,  &BAP_CanRxRomTable[261],  &BCL_RxBuffer47},
    /* LSG#id="66", Function#id="31" */{ BapIft_Can,  &BAP_CanRxRomTable[262],  &BCL_RxBuffer47},
    /* LSG#id="66", Function#id="31" */{ BapIft_Can,  &BAP_CanRxRomTable[263],  &BCL_RxBuffer47},
    /* LSG#id="66", Function#id="32" */{ BapIft_Can,  &BAP_CanRxRomTable[264],  &BCL_RxBuffer48},
    /* LSG#id="66", Function#id="32" */{ BapIft_Can,  &BAP_CanRxRomTable[265],  &BCL_RxBuffer48},
    /* LSG#id="66", Function#id="32" */{ BapIft_Can,  &BAP_CanRxRomTable[266],  &BCL_RxBuffer48},
    /* LSG#id="66", Function#id="32" */{ BapIft_Can,  &BAP_CanRxRomTable[267],  &BCL_RxBuffer48},
    /* LSG#id="66", Function#id="33" */{ BapIft_Can,  &BAP_CanRxRomTable[268],  &BCL_RxBuffer49},
    /* LSG#id="66", Function#id="33" */{ BapIft_Can,  &BAP_CanRxRomTable[269],  &BCL_RxBuffer49},
    /* LSG#id="66", Function#id="33" */{ BapIft_Can,  &BAP_CanRxRomTable[270],  &BCL_RxBuffer49},
    /* LSG#id="66", Function#id="33" */{ BapIft_Can,  &BAP_CanRxRomTable[271],  &BCL_RxBuffer49},
    /* LSG#id="66", Function#id="34" */{ BapIft_Can,  &BAP_CanRxRomTable[272],  &BCL_RxBuffer50},
    /* LSG#id="66", Function#id="34" */{ BapIft_Can,  &BAP_CanRxRomTable[273],  &BCL_RxBuffer50},
    /* LSG#id="66", Function#id="34" */{ BapIft_Can,  &BAP_CanRxRomTable[274],  &BCL_RxBuffer50},
    /* LSG#id="66", Function#id="34" */{ BapIft_Can,  &BAP_CanRxRomTable[275],  &BCL_RxBuffer50},
    /* LSG#id="66", Function#id="35" */{ BapIft_Can,  &BAP_CanRxRomTable[276],  &BCL_RxBuffer51},
    /* LSG#id="66", Function#id="35" */{ BapIft_Can,  &BAP_CanRxRomTable[277],  &BCL_RxBuffer51},
    /* LSG#id="66", Function#id="35" */{ BapIft_Can,  &BAP_CanRxRomTable[278],  &BCL_RxBuffer51},
    /* LSG#id="66", Function#id="35" */{ BapIft_Can,  &BAP_CanRxRomTable[279],  &BCL_RxBuffer51},
    /* LSG#id="66", Function#id="36" */{ BapIft_Can,  &BAP_CanRxRomTable[280], NULL},
    /* LSG#id="66", Function#id="36" */{ BapIft_Can,  &BAP_CanRxRomTable[281], NULL},
    /* LSG#id="66", Function#id="36" */{ BapIft_Can,  &BAP_CanRxRomTable[282], NULL},
    /* LSG#id="66", Function#id="36" */{ BapIft_Can,  &BAP_CanRxRomTable[283], NULL},
    /* LSG#id="66", Function#id="37" */{ BapIft_Can,  &BAP_CanRxRomTable[284],  &BCL_RxBuffer52},
    /* LSG#id="66", Function#id="37" */{ BapIft_Can,  &BAP_CanRxRomTable[285],  &BCL_RxBuffer52},
    /* LSG#id="66", Function#id="37" */{ BapIft_Can,  &BAP_CanRxRomTable[286],  &BCL_RxBuffer52},
    /* LSG#id="66", Function#id="37" */{ BapIft_Can,  &BAP_CanRxRomTable[287],  &BCL_RxBuffer52},
    /* LSG#id="66", Function#id="38" */{ BapIft_Can,  &BAP_CanRxRomTable[288],  &BCL_RxBuffer53},
    /* LSG#id="66", Function#id="38" */{ BapIft_Can,  &BAP_CanRxRomTable[289],  &BCL_RxBuffer53},
    /* LSG#id="66", Function#id="38" */{ BapIft_Can,  &BAP_CanRxRomTable[290],  &BCL_RxBuffer53},
    /* LSG#id="66", Function#id="38" */{ BapIft_Can,  &BAP_CanRxRomTable[291],  &BCL_RxBuffer53},
    /* LSG#id="66", Function#id="39" */{ BapIft_Can,  &BAP_CanRxRomTable[292],  &BCL_RxBuffer54},
    /* LSG#id="66", Function#id="39" */{ BapIft_Can,  &BAP_CanRxRomTable[293],  &BCL_RxBuffer54},
    /* LSG#id="66", Function#id="39" */{ BapIft_Can,  &BAP_CanRxRomTable[294],  &BCL_RxBuffer54},
    /* LSG#id="66", Function#id="39" */{ BapIft_Can,  &BAP_CanRxRomTable[295],  &BCL_RxBuffer54},
    /* LSG#id="66", Function#id="40" */{ BapIft_Can,  &BAP_CanRxRomTable[296],  &BCL_RxBuffer55},
    /* LSG#id="66", Function#id="41" */{ BapIft_Can,  &BAP_CanRxRomTable[297],  &BCL_RxBuffer56},
    /* LSG#id="66", Function#id="41" */{ BapIft_Can,  &BAP_CanRxRomTable[298],  &BCL_RxBuffer56},
    /* LSG#id="66", Function#id="41" */{ BapIft_Can,  &BAP_CanRxRomTable[299],  &BCL_RxBuffer56},
    /* LSG#id="66", Function#id="41" */{ BapIft_Can,  &BAP_CanRxRomTable[300],  &BCL_RxBuffer56},
    /* LSG#id="66", Function#id="42" */{ BapIft_Can,  &BAP_CanRxRomTable[301],  &BCL_RxBuffer57},
    /* LSG#id="66", Function#id="42" */{ BapIft_Can,  &BAP_CanRxRomTable[302],  &BCL_RxBuffer57},
    /* LSG#id="66", Function#id="42" */{ BapIft_Can,  &BAP_CanRxRomTable[303],  &BCL_RxBuffer57},
    /* LSG#id="66", Function#id="42" */{ BapIft_Can,  &BAP_CanRxRomTable[304],  &BCL_RxBuffer57},
    /* LSG#id="66", Function#id="43" */{ BapIft_Can,  &BAP_CanRxRomTable[305],  &BCL_RxBuffer58},
    /* LSG#id="66", Function#id="43" */{ BapIft_Can,  &BAP_CanRxRomTable[306],  &BCL_RxBuffer58},
    /* LSG#id="66", Function#id="43" */{ BapIft_Can,  &BAP_CanRxRomTable[307],  &BCL_RxBuffer58},
    /* LSG#id="66", Function#id="43" */{ BapIft_Can,  &BAP_CanRxRomTable[308],  &BCL_RxBuffer58},
    /* LSG#id="66", Function#id="44" */{ BapIft_Can,  &BAP_CanRxRomTable[309],  &BCL_RxBuffer59},
    /* LSG#id="66", Function#id="44" */{ BapIft_Can,  &BAP_CanRxRomTable[310],  &BCL_RxBuffer59},
    /* LSG#id="66", Function#id="44" */{ BapIft_Can,  &BAP_CanRxRomTable[311],  &BCL_RxBuffer59},
    /* LSG#id="66", Function#id="44" */{ BapIft_Can,  &BAP_CanRxRomTable[312],  &BCL_RxBuffer59},
    /* LSG#id="66", Function#id="45" */{ BapIft_Can,  &BAP_CanRxRomTable[313],  &BCL_RxBuffer60},
    /* LSG#id="66", Function#id="45" */{ BapIft_Can,  &BAP_CanRxRomTable[314],  &BCL_RxBuffer60},
    /* LSG#id="66", Function#id="45" */{ BapIft_Can,  &BAP_CanRxRomTable[315],  &BCL_RxBuffer60},
    /* LSG#id="66", Function#id="45" */{ BapIft_Can,  &BAP_CanRxRomTable[316],  &BCL_RxBuffer60},
    /* LSG#id="66", Function#id="46" */{ BapIft_Can,  &BAP_CanRxRomTable[317],  &BCL_RxBuffer61},
    /* LSG#id="66", Function#id="46" */{ BapIft_Can,  &BAP_CanRxRomTable[318],  &BCL_RxBuffer61},
    /* LSG#id="66", Function#id="46" */{ BapIft_Can,  &BAP_CanRxRomTable[319],  &BCL_RxBuffer61},
    /* LSG#id="66", Function#id="46" */{ BapIft_Can,  &BAP_CanRxRomTable[320],  &BCL_RxBuffer61},
    /* LSG#id="66", Function#id="47" */{ BapIft_Can,  &BAP_CanRxRomTable[321], NULL},
    /* LSG#id="66", Function#id="47" */{ BapIft_Can,  &BAP_CanRxRomTable[322], NULL},
    /* LSG#id="66", Function#id="47" */{ BapIft_Can,  &BAP_CanRxRomTable[323], NULL},
    /* LSG#id="66", Function#id="47" */{ BapIft_Can,  &BAP_CanRxRomTable[324], NULL},
    /* LSG#id="66", Function#id="48" */{ BapIft_Can,  &BAP_CanRxRomTable[325],  &BCL_RxBuffer62},
    /* LSG#id="66", Function#id="48" */{ BapIft_Can,  &BAP_CanRxRomTable[326],  &BCL_RxBuffer62},
    /* LSG#id="66", Function#id="48" */{ BapIft_Can,  &BAP_CanRxRomTable[327],  &BCL_RxBuffer62},
    /* LSG#id="66", Function#id="48" */{ BapIft_Can,  &BAP_CanRxRomTable[328],  &BCL_RxBuffer62}
};

/* MapCanIdToLsgRomRow Tabelle ********************************************************/

BAP_ROM_DATA_FAR BapMapCanIdToLsg_ot BAP_ROM_CONST BAP_MapCanIdToLsgRomRowTable[]=
{
    /* canId=BAP_Klima1_FSG_01 LsgId=1 */ {&BAP_LsgRomTables[0]},
    /* canId=BAP_KlimaMaster_FSG_01 LsgId=66 */ {&BAP_LsgRomTables[1]}
};


/* Globale BAP ROM Tabelle ****************************************************/
/* Enthaelt die ROM Konfiguration fuer alle Schichten je Funktions-ID         **/
BAP_ROM_DATA_FAR BapFctRomRow_ot BAP_ROM_CONST BAP_FctRomTables[]={
    /* lsgId, fctId, eFunctionClass, u8OpCodeSendMask, u8OpCodeReceiveMask, eRxDataType, u32RxSize, eTxDataType, u32TxSize, *poBalRamRow, bHeartbeatOn, nMaxRetryCounter, nMaxRetryTimer, *poBplRamRow, u8TxTableSize, u16BusTxTableIndex, u8RxTableSize, u16BusRxTableIndex*/
    {(lsgId_t)1, (fctId_t)1, BapFctCls_Cache, 0x90u, 0x2u, BapDt_Void,0u, BapDt_ByteSequence,214u, NULL, 0u, 0u, 0u, NULL, 1u, 0u, 4u, 0u },
    {(lsgId_t)1, (fctId_t)2, BapFctCls_Property, 0x91u, 0x2u, BapDt_Void,0u, BapDt_FixedByteSequence,6u, NULL, 1u, 0u, 0u, NULL, 1u, 1u, 4u, 4u },
    {(lsgId_t)1, (fctId_t)3, BapFctCls_Property, 0x90u, 0x2u, BapDt_Void,0u, BapDt_ByteSequence,8u, NULL, 1u, 0u, 0u, NULL, 1u, 2u, 4u, 8u },
    {(lsgId_t)1, (fctId_t)4, BapFctCls_Property, 0x90u, 0x2u, BapDt_Void,0u, BapDt_Int8,1u, NULL, 1u, 0u, 0u, NULL, 1u, 3u, 4u, 12u },
    {(lsgId_t)1, (fctId_t)13, BapFctCls_Property, 0x90u, 0x6u, BapDt_Int8,1u, BapDt_Int8,1u, NULL, 1u, 0u, 0u, NULL, 1u, 4u, 4u, 16u },
    {(lsgId_t)1, (fctId_t)14, BapFctCls_Property, 0x90u, 0x2u, BapDt_Void,0u, BapDt_ByteSequence,11u, NULL, 1u, 0u, 0u, NULL, 1u, 5u, 4u, 20u },
    {(lsgId_t)1, (fctId_t)15, BapFctCls_Property, 0x90u, 0x2u, BapDt_Void,0u, BapDt_Int8,1u, NULL, 1u, 0u, 0u, NULL, 1u, 6u, 4u, 24u },
    {(lsgId_t)1, (fctId_t)16, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,6u, BapDt_FixedByteSequence,6u, NULL, 1u, 0u, 0u, NULL, 1u, 7u, 4u, 28u },
    {(lsgId_t)1, (fctId_t)17, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,6u, BapDt_FixedByteSequence,6u, NULL, 1u, 0u, 0u, NULL, 1u, 8u, 4u, 32u },
    {(lsgId_t)1, (fctId_t)18, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,4u, BapDt_FixedByteSequence,4u, NULL, 1u, 0u, 0u, NULL, 1u, 9u, 4u, 36u },
    {(lsgId_t)1, (fctId_t)19, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,4u, BapDt_FixedByteSequence,4u, NULL, 1u, 0u, 0u, NULL, 1u, 10u, 4u, 40u },
    {(lsgId_t)1, (fctId_t)20, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,5u, BapDt_FixedByteSequence,5u, NULL, 1u, 0u, 0u, NULL, 1u, 11u, 4u, 44u },
    {(lsgId_t)1, (fctId_t)21, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,5u, BapDt_FixedByteSequence,5u, NULL, 1u, 0u, 0u, NULL, 1u, 12u, 4u, 48u },
    {(lsgId_t)1, (fctId_t)22, BapFctCls_Property, 0x90u, 0x6u, BapDt_ByteSequence,7u, BapDt_ByteSequence,7u, NULL, 1u, 0u, 0u, NULL, 1u, 13u, 4u, 52u },
    {(lsgId_t)1, (fctId_t)23, BapFctCls_Property, 0x90u, 0x6u, BapDt_ByteSequence,7u, BapDt_ByteSequence,7u, NULL, 1u, 0u, 0u, NULL, 1u, 14u, 4u, 56u },
    {(lsgId_t)1, (fctId_t)24, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,4u, BapDt_FixedByteSequence,4u, NULL, 1u, 0u, 0u, NULL, 1u, 15u, 4u, 60u },
    {(lsgId_t)1, (fctId_t)25, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,4u, BapDt_FixedByteSequence,4u, NULL, 1u, 0u, 0u, NULL, 1u, 16u, 4u, 64u },
    {(lsgId_t)1, (fctId_t)26, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,3u, BapDt_FixedByteSequence,3u, NULL, 1u, 0u, 0u, NULL, 1u, 17u, 4u, 68u },
    {(lsgId_t)1, (fctId_t)27, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,3u, BapDt_FixedByteSequence,3u, NULL, 1u, 0u, 0u, NULL, 1u, 18u, 4u, 72u },
    {(lsgId_t)1, (fctId_t)28, BapFctCls_Property, 0x90u, 0x2u, BapDt_Void,0u, BapDt_FixedByteSequence,2u, NULL, 1u, 0u, 0u, NULL, 1u, 19u, 4u, 76u },
    {(lsgId_t)1, (fctId_t)29, BapFctCls_Property, 0x90u, 0x2u, BapDt_Void,0u, BapDt_FixedByteSequence,2u, NULL, 1u, 0u, 0u, NULL, 1u, 20u, 4u, 80u },
    {(lsgId_t)1, (fctId_t)30, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,3u, BapDt_FixedByteSequence,3u, NULL, 1u, 0u, 0u, NULL, 1u, 21u, 4u, 84u },
    {(lsgId_t)1, (fctId_t)31, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,3u, BapDt_FixedByteSequence,3u, NULL, 1u, 0u, 0u, NULL, 1u, 22u, 4u, 88u },
    {(lsgId_t)1, (fctId_t)32, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,3u, BapDt_FixedByteSequence,3u, NULL, 1u, 0u, 0u, NULL, 1u, 23u, 4u, 92u },
    {(lsgId_t)1, (fctId_t)33, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,3u, BapDt_FixedByteSequence,3u, NULL, 1u, 0u, 0u, NULL, 1u, 24u, 4u, 96u },
    {(lsgId_t)1, (fctId_t)34, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,5u, BapDt_FixedByteSequence,5u, NULL, 1u, 0u, 0u, NULL, 1u, 25u, 4u, 100u },
    {(lsgId_t)1, (fctId_t)35, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,5u, BapDt_FixedByteSequence,5u, NULL, 1u, 0u, 0u, NULL, 1u, 26u, 4u, 104u },
    {(lsgId_t)1, (fctId_t)36, BapFctCls_Array, 0x98u, 0x6u, BapDt_ByteSequence,112u, BapDt_ByteSequence,113u, NULL, 0u, 0u, 0u, NULL, 1u, 27u, 4u, 108u },
    {(lsgId_t)1, (fctId_t)37, BapFctCls_Method, 0x98u, 0xcu, BapDt_FixedByteSequence,1u, BapDt_Int8,1u, NULL, 0u, 0u, 30u, &BAP_BplRamTable[0], 1u, 28u, 4u, 112u },
    {(lsgId_t)1, (fctId_t)38, BapFctCls_Property, 0x90u, 0x2u, BapDt_Void,0u, BapDt_FixedByteSequence,2u, NULL, 1u, 0u, 0u, NULL, 1u, 29u, 4u, 116u },
    {(lsgId_t)1, (fctId_t)39, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,4u, BapDt_FixedByteSequence,4u, NULL, 1u, 0u, 0u, NULL, 1u, 30u, 4u, 120u },
    {(lsgId_t)1, (fctId_t)40, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,4u, BapDt_FixedByteSequence,4u, NULL, 1u, 0u, 0u, NULL, 1u, 31u, 4u, 124u },
    {(lsgId_t)1, (fctId_t)41, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,5u, BapDt_FixedByteSequence,5u, NULL, 1u, 0u, 0u, NULL, 1u, 32u, 4u, 128u },
    {(lsgId_t)1, (fctId_t)42, BapFctCls_Property, 0x90u, 0x2u, BapDt_Void,0u, BapDt_ByteSequence,11u, NULL, 1u, 0u, 0u, NULL, 1u, 33u, 4u, 132u },
    {(lsgId_t)1, (fctId_t)43, BapFctCls_Property, 0x90u, 0x6u, BapDt_ByteSequence,9u, BapDt_ByteSequence,9u, NULL, 1u, 0u, 0u, NULL, 1u, 34u, 4u, 136u },
    {(lsgId_t)1, (fctId_t)44, BapFctCls_Property, 0x90u, 0x6u, BapDt_ByteSequence,9u, BapDt_ByteSequence,9u, NULL, 1u, 0u, 0u, NULL, 1u, 35u, 4u, 140u },
    {(lsgId_t)1, (fctId_t)45, BapFctCls_Array, 0x98u, 0x2u, BapDt_ByteSequence,4u, BapDt_ByteSequence,25u, NULL, 0u, 0u, 0u, NULL, 1u, 36u, 4u, 144u },
    {(lsgId_t)1, (fctId_t)46, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,6u, BapDt_FixedByteSequence,6u, NULL, 1u, 0u, 0u, NULL, 1u, 37u, 4u, 148u },
    {(lsgId_t)1, (fctId_t)47, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,6u, BapDt_FixedByteSequence,6u, NULL, 1u, 0u, 0u, NULL, 1u, 38u, 4u, 152u },
    {(lsgId_t)1, (fctId_t)48, BapFctCls_Property, 0x90u, 0x6u, BapDt_ByteSequence,8u, BapDt_ByteSequence,8u, NULL, 1u, 0u, 0u, NULL, 1u, 39u, 4u, 156u },
    {(lsgId_t)1, (fctId_t)49, BapFctCls_Property, 0x90u, 0x6u, BapDt_ByteSequence,8u, BapDt_ByteSequence,8u, NULL, 1u, 0u, 0u, NULL, 1u, 40u, 4u, 160u },
    {(lsgId_t)1, (fctId_t)50, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,6u, BapDt_FixedByteSequence,6u, NULL, 1u, 0u, 0u, NULL, 1u, 41u, 4u, 164u },
    {(lsgId_t)1, (fctId_t)51, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,6u, BapDt_FixedByteSequence,6u, NULL, 1u, 0u, 0u, NULL, 1u, 42u, 4u, 168u },
    {(lsgId_t)66, (fctId_t)1, BapFctCls_Cache, 0x90u, 0x2u, BapDt_Void,0u, BapDt_ByteSequence,170u, NULL, 0u, 0u, 0u, NULL, 1u, 43u, 4u, 172u },
    {(lsgId_t)66, (fctId_t)2, BapFctCls_Property, 0x91u, 0x2u, BapDt_Void,0u, BapDt_FixedByteSequence,6u, NULL, 1u, 0u, 0u, NULL, 1u, 44u, 4u, 176u },
    {(lsgId_t)66, (fctId_t)3, BapFctCls_Property, 0x90u, 0x2u, BapDt_Void,0u, BapDt_ByteSequence,8u, NULL, 1u, 0u, 0u, NULL, 1u, 45u, 4u, 180u },
    {(lsgId_t)66, (fctId_t)4, BapFctCls_Property, 0x90u, 0x2u, BapDt_Void,0u, BapDt_Int8,1u, NULL, 1u, 0u, 0u, NULL, 1u, 46u, 4u, 184u },
    {(lsgId_t)66, (fctId_t)13, BapFctCls_Property, 0x90u, 0x6u, BapDt_Int8,1u, BapDt_Int8,1u, NULL, 1u, 0u, 0u, NULL, 1u, 47u, 4u, 188u },
    {(lsgId_t)66, (fctId_t)14, BapFctCls_Property, 0x90u, 0x2u, BapDt_Void,0u, BapDt_ByteSequence,8u, NULL, 1u, 0u, 0u, NULL, 1u, 48u, 4u, 192u },
    {(lsgId_t)66, (fctId_t)15, BapFctCls_Property, 0x90u, 0x2u, BapDt_Void,0u, BapDt_Int8,1u, NULL, 1u, 0u, 0u, NULL, 1u, 49u, 4u, 196u },
    {(lsgId_t)66, (fctId_t)16, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,2u, BapDt_FixedByteSequence,2u, NULL, 1u, 0u, 0u, NULL, 1u, 50u, 4u, 200u },
    {(lsgId_t)66, (fctId_t)17, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,2u, BapDt_FixedByteSequence,2u, NULL, 1u, 0u, 0u, NULL, 1u, 51u, 4u, 204u },
    {(lsgId_t)66, (fctId_t)18, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,3u, BapDt_FixedByteSequence,3u, NULL, 1u, 0u, 0u, NULL, 1u, 52u, 4u, 208u },
    {(lsgId_t)66, (fctId_t)19, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,2u, BapDt_FixedByteSequence,2u, NULL, 1u, 0u, 0u, NULL, 1u, 53u, 4u, 212u },
    {(lsgId_t)66, (fctId_t)20, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,3u, BapDt_FixedByteSequence,3u, NULL, 1u, 0u, 0u, NULL, 1u, 54u, 4u, 216u },
    {(lsgId_t)66, (fctId_t)21, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,3u, BapDt_FixedByteSequence,3u, NULL, 1u, 0u, 0u, NULL, 1u, 55u, 4u, 220u },
    {(lsgId_t)66, (fctId_t)22, BapFctCls_Property, 0x90u, 0x7u, BapDt_ByteSequence,9u, BapDt_ByteSequence,9u, NULL, 1u, 0u, 0u, NULL, 1u, 56u, 4u, 224u },
    {(lsgId_t)66, (fctId_t)23, BapFctCls_Property, 0xb0u, 0x46u, BapDt_FixedByteSequence,3u, BapDt_FixedByteSequence,3u, NULL, 1u, 0u, 0u, NULL, 1u, 57u, 4u, 228u },
    {(lsgId_t)66, (fctId_t)24, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,3u, BapDt_FixedByteSequence,3u, NULL, 1u, 0u, 0u, NULL, 1u, 58u, 4u, 232u },
    {(lsgId_t)66, (fctId_t)25, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,3u, BapDt_FixedByteSequence,3u, NULL, 1u, 0u, 0u, NULL, 1u, 59u, 4u, 236u },
    {(lsgId_t)66, (fctId_t)26, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,4u, BapDt_FixedByteSequence,4u, NULL, 1u, 0u, 0u, NULL, 1u, 60u, 4u, 240u },
    {(lsgId_t)66, (fctId_t)27, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,3u, BapDt_FixedByteSequence,3u, NULL, 1u, 0u, 0u, NULL, 1u, 61u, 4u, 244u },
    {(lsgId_t)66, (fctId_t)28, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,3u, BapDt_FixedByteSequence,3u, NULL, 1u, 0u, 0u, NULL, 1u, 62u, 4u, 248u },
    {(lsgId_t)66, (fctId_t)29, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,3u, BapDt_FixedByteSequence,3u, NULL, 1u, 0u, 0u, NULL, 1u, 63u, 4u, 252u },
    {(lsgId_t)66, (fctId_t)30, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,3u, BapDt_FixedByteSequence,3u, NULL, 1u, 0u, 0u, NULL, 1u, 64u, 4u, 256u },
    {(lsgId_t)66, (fctId_t)31, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,3u, BapDt_FixedByteSequence,3u, NULL, 1u, 0u, 0u, NULL, 1u, 65u, 4u, 260u },
    {(lsgId_t)66, (fctId_t)32, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,3u, BapDt_FixedByteSequence,3u, NULL, 1u, 0u, 0u, NULL, 1u, 66u, 4u, 264u },
    {(lsgId_t)66, (fctId_t)33, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,3u, BapDt_FixedByteSequence,3u, NULL, 1u, 0u, 0u, NULL, 1u, 67u, 4u, 268u },
    {(lsgId_t)66, (fctId_t)34, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,6u, BapDt_FixedByteSequence,6u, NULL, 1u, 0u, 0u, NULL, 1u, 68u, 4u, 272u },
    {(lsgId_t)66, (fctId_t)35, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,6u, BapDt_FixedByteSequence,6u, NULL, 1u, 0u, 0u, NULL, 1u, 69u, 4u, 276u },
    {(lsgId_t)66, (fctId_t)36, BapFctCls_Property, 0x90u, 0x2u, BapDt_Void,0u, BapDt_FixedByteSequence,6u, NULL, 1u, 0u, 0u, NULL, 1u, 70u, 4u, 280u },
    {(lsgId_t)66, (fctId_t)37, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,6u, BapDt_FixedByteSequence,6u, NULL, 1u, 0u, 0u, NULL, 1u, 71u, 4u, 284u },
    {(lsgId_t)66, (fctId_t)38, BapFctCls_Property, 0x90u, 0x6u, BapDt_ByteSequence,18u, BapDt_ByteSequence,18u, NULL, 1u, 0u, 0u, NULL, 1u, 72u, 4u, 288u },
    {(lsgId_t)66, (fctId_t)39, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,3u, BapDt_FixedByteSequence,3u, NULL, 1u, 0u, 0u, NULL, 1u, 73u, 4u, 292u },
    {(lsgId_t)66, (fctId_t)40, BapFctCls_Array, 0x98u, 0x6u, BapDt_ByteSequence,273u, BapDt_ByteSequence,276u, NULL, 0u, 0u, 0u, NULL, 1u, 74u, 1u, 296u },
    {(lsgId_t)66, (fctId_t)41, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,3u, BapDt_FixedByteSequence,3u, NULL, 1u, 0u, 0u, NULL, 1u, 75u, 4u, 297u },
    {(lsgId_t)66, (fctId_t)42, BapFctCls_Array, 0x98u, 0x6u, BapDt_ByteSequence,44u, BapDt_ByteSequence,45u, NULL, 0u, 0u, 0u, NULL, 1u, 76u, 4u, 301u },
    {(lsgId_t)66, (fctId_t)43, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,6u, BapDt_FixedByteSequence,6u, NULL, 1u, 0u, 0u, NULL, 1u, 77u, 4u, 305u },
    {(lsgId_t)66, (fctId_t)44, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,6u, BapDt_FixedByteSequence,6u, NULL, 1u, 0u, 0u, NULL, 1u, 78u, 4u, 309u },
    {(lsgId_t)66, (fctId_t)45, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,3u, BapDt_FixedByteSequence,3u, NULL, 1u, 0u, 0u, NULL, 1u, 79u, 4u, 313u },
    {(lsgId_t)66, (fctId_t)46, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,4u, BapDt_FixedByteSequence,4u, NULL, 1u, 0u, 0u, NULL, 1u, 80u, 4u, 317u },
    {(lsgId_t)66, (fctId_t)47, BapFctCls_Property, 0x90u, 0x2u, BapDt_Void,0u, BapDt_FixedByteSequence,6u, NULL, 1u, 0u, 0u, NULL, 1u, 81u, 4u, 321u },
    {(lsgId_t)66, (fctId_t)48, BapFctCls_Property, 0x90u, 0x6u, BapDt_FixedByteSequence,6u, BapDt_FixedByteSequence,6u, NULL, 1u, 0u, 0u, NULL, 1u, 82u, 4u, 325u }
};

#define BAP_STOP_SEC_CONST_UNSPECIFIED
#include <BAP_MemMap.h>
#define BAP_START_SEC_CONST_8
#include <BAP_MemMap.h>
/*  BAP Konfigurations-Tabelle ************************************************/
BAP_ROM_DATA_FAR const uint8_t BAP_ROM_CONST BAP_BAPConfigTable[][BAP_FCTID_BAPCONFIG_SIZE]={
    /*             PV-Major, PV-Minor, SG-Major, SG-Minor, DF-Major, DF-Minor */
    /* LsgId=1 */ {3u, 0u, 1u, 0u, 7u, 9u },
    /* LsgId=66 */ {3u, 1u, 66u, 0u, 3u, 11u }
};

#define BAP_STOP_SEC_CONST_8
#include <BAP_MemMap.h>
#define BAP_START_SEC_CONST_UNSPECIFIED
#include <BAP_MemMap.h>

/* Globale BAP ROM Tabelle ****************************************************/
BAP_ROM_DATA_FAR BapLsgRomRow_ot BAP_ROM_CONST BAP_LsgRomTables[]={
    /* LSG1 */
    {
        (lsgId_t)1,/*lsgId*/
        1u,/* u8BAPConfigTableSize */
        0u, /* u8BAPConfigTableIndex */
        {  /* FunctionList */0x38u,0x7u,0xffu,0xffu,0xffu,0xffu,0xf0u,0x0u},
        &BAP_BplHeartbeatTimerTable [0], /* pu16HeartbeatTimer */
        10u,/* u8TaskTimeMs */
        10u,/*u8Heartbeat*/
        43u, /* u8FctRomTableSize */
        0u, /* u16FctRomIndex */
        172u, /* u16CanRxRomTableSize */
        0u, /* u16CanRxRomTableIndex */
        BAP_FALSE, /* bUseDLC8 */
#if defined(BAP_ASG) && defined(BAP_FSG)
        BapSG_FSG, /*eSGType;*/
#endif /*#if defined(BAP_ASG) && defined(BAP_FSG)*/
        &BAP_LsgRamTable [0], /* *poLsgRamRow */
        43u, /* u16CanTxRomTableSize */
        0u, /* u16CanTxRomTableIndex */
        BAP_FALSE /* alte Adressierungsart */
    },

    /* LSG66 */
    {
        (lsgId_t)66,/*lsgId*/
        1u,/* u8BAPConfigTableSize */
        1u, /* u8BAPConfigTableIndex */
        {  /* FunctionList */0x38u,0x7u,0xffu,0xffu,0xffu,0xffu,0x80u,0x0u},
        &BAP_BplHeartbeatTimerTable [1], /* pu16HeartbeatTimer */
        10u,/* u8TaskTimeMs */
        10u,/*u8Heartbeat*/
        40u, /* u8FctRomTableSize */
        43u, /* u16FctRomIndex */
        157u, /* u16CanRxRomTableSize */
        172u, /* u16CanRxRomTableIndex */
        BAP_FALSE, /* bUseDLC8 */
#if defined(BAP_ASG) && defined(BAP_FSG)
        BapSG_FSG, /*eSGType;*/
#endif /*#if defined(BAP_ASG) && defined(BAP_FSG)*/
        &BAP_LsgRamTable [1], /* *poLsgRamRow */
        40u, /* u16CanTxRomTableSize */
        43u, /* u16CanTxRomTableIndex */
        BAP_TRUE /* neue Adressierungsart */
    }
};


#define BAP_STOP_SEC_CONST_UNSPECIFIED
#include <BAP_MemMap.h>
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
/* BAP Tabelle mit Zeiger auf das aktuelle Lsg (wegen Multiconfig) ************/
BAP_RAM_DATA_FAR BapLsgRomRow_pot BAP_pLsgRomTable[]={
    &BAP_LsgRomTables[0],
    &BAP_LsgRomTables[1]
};
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

