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
 *  This file contains the interfacing layer AALB (AUTOSAR Adaption
 *  Layer BAP). It is located on top of the AUTOSAR PDU-Router and
 *  below the BAP (Bedien und Anzeigeprotokoll).
 *
 ******************************************************************
 *
 * Revision History (w/o SCM)
 *
 * Date        Version     Author       Description
 * ----------------------------------------------------------------
 * 2023-10-10	1.12.2		DRH			[EEARCH-35935] Release preparation, adapt Copyright date and version number.
 * 2022-11-15   1.12.1      DRH         [SSWPPB-297] Renamed macros and global variables module specific
 * 2022-10-21	1.12.1		DRH			[SSWPPB-296] Release preparation, adapt Copyright date and version number.
 * 2022-06-17	1.12.0		DRH			[SSWPPB-269] Release preparation, adapt Copyright date and version number.
 * 2021-12-07	1.11.3		JEO			[SSWPPB-244] Release preparation, adapt Copyright date and version number.
 * 2021-06-09   1.11.3      JEO         [SSWPPB-209] Add ASR interface to enable/disable sending of debug informations.
 * 2021-03-12	1.11.3		JEO			[SSWPPB-142] Fix MISRA violations.
 * 2020-08-13   1.11.2      KUL         [SSWPPB-73] Added function to return Upper Layer (CDD ComIf) PDU ids when Interface option is used instead of PDUR with ASR4
 * 2020-03-31   1.11.1      ODD         [SSWPPB-93] Removed compiler Error in Autosar when they using strict compiler settings which not allow implicit typecast
 * 2020-03-11   1.11.1      ODD         [SSWPPB-60] Optimise CAN-FD-Mapping on Ethernet
 * 2020-02-12   1.11.1      KUL         [SSWPPB-76] BAP_SendDebugInfo function moved to aalb.c.
 * 2020-02-12   1.11.1      KUL         [SSWPPB-55] Reordering header inclusion. Removed BAP_Cbh.h inclusion, already included in aalb_Types.h.
 * 2019-03-21   1.10.99     KUL         [SSWPPB-4] Removal of string.h inclusion and associated replace library calls
 * 2019-01-28   1.10.99     FFS         [SSWCCB-2647] Return type changed to void for functions BAP_RxIndication and BAP_TxConfirmation
 * 2018-12-05   1.10.3      ODD          typecast correction from DataType (uint8) -> (uint8_t)
 * 2018-07-19   1.10.3      FFS         [SSWCCB-2522] Misra-2012 fix (release postponed)
 * 2017-10-25   1.10.1      ODD         [SSWCCB-2528] Bugfix: Ethernetschnittstelle im AALB nicht untersützt
 * 2017-10-25   1.10.0      FHA         [SSWCCB-2514] BugFix: Debug-Interface in ASR ist nicht verfuegbar
 * 2017-07-31   1.10.0      FHA         [SSWCCB-2474] DLC-Mapping für CAN-FD
 * 2017-02-06   1.9         FST         [SSWCCB-1545] SSW-Lokatierungs-Pragmas eingefuegt
 * 2016-11-22   1.8.1       FST         [SSWCCB-2379] #ifdef BAP_USES_ASR3 fuer BAP_GetVersionInfo hinzugefuegt, wegen Unterschied zu ASR4
 * 2015-03-17   1.8.0.3     FST         [SSWCCB-2188][SSWCCB-2189][SSWCCB-2190] Fuer CAN, CAN-FD und FR wieder 1 Byte DLC verwendet
 * 2015-02-27   1.8.0.3     FST         [SSWCCB-2187] Voraussetzung für BAP_TriggerTransmit durch logisches Oder um PDU-Router ergaenzt,
 *                                      wie bereits laut Kommentar vorgesehen
 * 2015-01-16   1.8.0.1     WWU         [SSWCCB-2105] DLC ist 2 Byte (uint16_t) statt 1 Byte.
 *                                      Laenge des aalb_CanTxBuffers geaendert: [BAP_MAX_PDU_SIZE + 2], statt 9
 * 2014-10-06   1.8.0       FST         [SSWCCB-2104] Umstellung u8Length auf uint16_t u16MsgLength fuer Nachrichtengroesse > 8 Byte
 * 2014-07-16   1.8.0       WWU         [SSWCCB-1862] Anbindung mit PDU-Router erweitert.
 * 2013-12-04   1.7.0       WWU         [SSWCCB-1521]: Ersetze AALB_VERSION_INFO_API durch BAP_VERSION_INFO_API.
 * 2013-01-30   1.7.0       WWU         MISRA-2004 fix
 * 2013-01-22   1.6.7       GRO         BAP_CANUBS_IsReadyForTx Retry-Limit implemented.
 * 2012-11-12   1.6.6       WWU         Bugfix in FlexRay(#elif BAP_USES_FR) to (#elif defined(BAP_USES_FR))
 * 2012-09-20   1.6.5       WWU         Code Refaktoring in Funktion BAP_CANUBS_TxData. Neue Funktion fuer FlexRay und CAN
 *                                      Transmit BAP_Transmit_TxData ist hinzugefuegt.
 * 2012-03-01   1.6.3       NQU         BAP_MASQUERADE_ASR_API Macro notwendig fuer die ASIL Umgebung eingefuehrt
 * 2011-10-10   1.6.2       NQU         Anpassung von BAP_RxIndication und BAP_CANUBS_TxData fuer FlexRay
 * 2011-09-08   1.6.2       NQU         Bugfix in FlexRay
 * 2011-06-03   1.6         WWU         Anpassung fuer Uebergabe-/Rueckgabeparameter von fct BAP_RxIndication,
 *                                      BAP_TxConfirmation,BAP_TriggerTransmit
 * 2007-11-14   1.03.00     MIP         Aalb_Cbk.h changes - include structure
 * 2007-11-04   1.02        MIP         Aalb_Cbk.h changes
 * 2007-10-13   1.02        MIP         BugFix in BAP_GetVersionInfo()
 * 2007-05-25   1.01        MIP         Changes after Audi review
 *                                      new function: BAP_GetVersionInfo()
 * 2006-12-11   1.0         ALA         Initial Version
 ******************************************************************/

/* System includes <...> */

/* Vendor libraries <...> */
#include <bap_canubs.h>
#include "bap_debug.h"
#include "bap_util.h"
#ifdef BAP_USES_PDUR
#include "PduR_BAP.h"       /* [WWU] todo: PduR_BAP.h soll von AUTOSAR zur Verfuegung gestellt werden.  */
#else
#ifdef BAP_USES_FR
#include "FrIf.h"               /* Include FrIf APIs */
#endif /* BAP_USES_FR */
#ifdef BAP_USES_CAN
#include "CanIf.h"              /* Include CanIf APIs */
#endif /* BAP_USES_CAN */
#endif /* #ifdef BAP_USES_PDUROUTER */
#include "aalb_Types.h"
#include "aalb_cfg.h"

/* own header files "..." */
#ifndef BAP_MASQUERADE_ASR_API  /* ASIL Umgebung Schalter */
#include "ComStack_Types.h"
#else /* BAP_MASQUERADE_ASR_API */
#include "BAP_ComStack_Types.h"
#ifdef BAP_USES_PDUR
#include "BAP_PduR_BAP.h"       /* [WWU] todo: BAP_PduR_BAP.h soll von AUTOSAR zur Verfuegung gestellt werden.  */
#else
#ifdef BAP_USES_FR
#include "BAP_FrIf.h"               /* Include FrIf APIs */
#endif /* BAP_USES_FR */
#ifdef BAP_USES_CAN
#include "BAP_CanIf.h"              /* Include CanIf APIs */
#endif /* BAP_USES_CAN */
#endif /*BAP_USES_PDUR*/
#define CanIf_Transmit  BAP_CanIf_Transmit
#define FrIf_Transmit   BAP_FrIf_Transmit
#endif /* #ifndef BAP_MASQUERADE_ASR_API */


#if (defined(AALB_BAP_DIAGNOSTICS_PDU_SEND_ID) && (!defined(AALB_BAP_DIAGNOSTICS_PDU_ID))) || ((!defined(AALB_BAP_DIAGNOSTICS_PDU_SEND_ID)) && defined(AALB_BAP_DIAGNOSTICS_PDU_ID))
#error To support the BAP Debug and Diagnostic messages on FlexRay you must define both macros AALB_BAP_DIAGNOSTICS_PDU_SEND_ID and AALB_BAP_DIAGNOSTICS_PDU_ID
#endif


#define BAP_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
static PduInfoType pduInfo;
#define BAP_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Internal macro definitions */

/* Internal type definitions */

/* enum typ definition fuer CAN-FD Mapping */
#if defined(BAP_CAN_FD_PADDING_ENABLE)
typedef enum BapCanFdDataLength_t
{
    /** CAN-FD-Datenlaengen 9-12 Byte */
    Bap_Can_Fd_12_Byte = 12,
    /** CAN-FD-Datenlaengen 13-16 Byte */
    Bap_Can_Fd_16_Byte = 16,
    /** CAN-FD-Datenlaengen 17-20 Byte */
    Bap_Can_Fd_20_Byte = 20,
    /** CAN-FD-Datenlaengen 21-24 Byte */
    Bap_Can_Fd_24_Byte = 24,
    /** CAN-FD-Datenlaengen 25-32 Byte */
    Bap_Can_Fd_32_Byte = 32,
    /** CAN-FD-Datenlaengen 33-48 Byte */
    Bap_Can_Fd_48_Byte = 48,
    /** CAN-FD-Datenlaengen 49-64 Byte */
    Bap_Can_Fd_64_Byte = 64
};
#endif 
/* Internal const declarations */

/* Internal static variables */
#define BAP_START_SEC_VAR_INIT_8
#include <BAP_MemMap.h>
static uint8_t Bap_CanMsg_TimeoutTable[AALB_CAN_MSG_ID_2_PDU_ID_TAB_SIZE] = {(uint8_t)0}; /*Tabelle zum ermitteln, wie oft eine CAN-Message hintereinander nicht gesendet wurde.*/
#define BAP_STOP_SEC_VAR_INIT_8
#include <BAP_MemMap.h>

/* static function forward declarations */
/* documentation can be found in the implementation section */
static bool_t BAP_Transmit_TxData(BapCanInterfaceChannel_t aCanInterfaceChannel
        , BapCanMsgId_t aPduId
        , uint16_t u16Index
        , uint16_t au16MsgLength);

/* documentation can be found in the implementation section */
static uint16_t aalb_GetTxHandleByPdu(PduIdType aPduId);

#if( !defined(BAP_USES_PDUR) && defined(BAP_USES_ASR4) )
/* documentation can be found in the implementation section */
static uint16_t aalb_GetComIfTxHandleByPdu(PduIdType aPduId);
#endif

/* documentation can be found in the implementation section */
static uint16_t aalb_GetRxHandle(PduIdType aPduId);

/* documentation can be found in the implementation section */
void aalb_ResetCanTxBuffers(BapCanMsgId_t aPduId, uint16_t u16Index);

#ifdef BAP_USES_PDUR
/* documentation can be found in the implementation section */
static PduIdType aalb_GetPdurTxPduByBapTxPdu(PduIdType aBapPduId);
#endif /* BAP_USES_PDUR */



#if defined(BAP_CAN_FD_PADDING_ENABLE)
/* documentation can be found in the implementation section */
uint16_t BAP_GetCanFdDataLength(uint16_t au16MsgLength);
#endif

/* Definition (Implementation) of static functions */


/**
 *  The function aalb_GetTxHandleByPdu() provides the index of the table
 *  aalb_CanMsgId2PduIdTab of corresponding PDU ID.
 *
 *  @param aPduId
 *  @return Index of the table.
 *          BAP_MAX_UINT_16 == -1 == 0xffff, in case of no entry found.
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
static uint16_t aalb_GetTxHandleByPdu(PduIdType aPduId)
{
    uint16_t u16Index;
    uint16_t retval = BAP_MAX_UINT_16;
    /* search entry in aalb_CanMsgId2PduIdTab */
    for(u16Index = (uint16_t)0; u16Index < AALB_CAN_MSG_ID_2_PDU_ID_TAB_SIZE; u16Index++)
    {
        if (aalb_CanMsgId2PduIdTab[u16Index].pduId == aPduId)
        {
            retval = u16Index;
        }
    }
    return retval;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>

#if( !defined(BAP_USES_PDUR) && defined(BAP_USES_ASR4) )

#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
/**
 *  The function aalb_GetComIfTxHandleByPdu() provides the index of the table
 *  aalb_CanMsgId2PduIdTab of corresponding ComIf PDU ID.
 *
 *  @param aPduId
 *  @return Index of the table.
 *          BAP_MAX_UINT_16 == -1 == 0xffff, in case of no entry found.
 */
static uint16_t aalb_GetComIfTxHandleByPdu(PduIdType aPduId)
{
    uint16_t u16Index;
    uint16_t retval = BAP_MAX_UINT_16;
    /* search entry in aalb_CanMsgId2PduIdTab */
    for(u16Index = (uint16_t)0; u16Index < AALB_CAN_MSG_ID_2_PDU_ID_TAB_SIZE; u16Index++)
    {
        if (aalb_CanMsgId2PduIdTab[u16Index].pduIdComIf == aPduId)
        {
            retval = u16Index;
        }
    }
    return retval;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>

#endif

/**
 *  The function aalb_GetRxHandle() provides the index of the table aalb_PduId2CanMsgIdTab
 *  of a corresponding PDU ID.
 *
 *  @param aPduId
 *  @return Index of the table.
 *          BAP_MAX_UINT_16 == -1 == 0xffff, in case of no entry found.
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
static uint16_t aalb_GetRxHandle(PduIdType aPduId)
{
    uint16_t u16Index;
    uint16_t retval = BAP_MAX_UINT_16;
    /* search entry in aalb_PduId2CanMsgIdTab */
    for(u16Index = (uint16_t)0; u16Index < AALB_PDU_ID_2_CAN_MSG_ID_TAB_SIZE; u16Index++)
    {
        if (aalb_PduId2CanMsgIdTab[u16Index].pduId == aPduId)
        {
            retval = u16Index;
        }
    }
    return retval;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>

#ifdef BAP_USES_PDUR
/**
 *  The function aalb_GetPdurTxPduByBapTxPdu() provides the PduR PDU ID
 *  of a corresponding BAP PDU ID.
 *
 *  @param aBapPduId
 *  @return PduR PDU ID
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
static PduIdType aalb_GetPdurTxPduByBapTxPdu(PduIdType aBapPduId)
{
    uint16_t u16Index;
    /*lint -e9034*//* Size of type PduIdType depends on number of configured PDUs */
    PduIdType retval = BAP_MAX_UINT_16;
    /*lint +e9034*/
    // search entry in aalb_BapPduId2PdurPduIdTab
    for(u16Index = (uint16_t)0; u16Index < AALB_BAP_PDU_ID_2_PDUR_PDU_ID_TAB_SIZE; u16Index++)
    {
        if (aalb_BapPduId2PdurPduIdTab[u16Index].bap_pdu_id == aBapPduId)
        {
            retval = aalb_BapPduId2PdurPduIdTab[u16Index].pdur_pdu_id;
        }
    }
    return retval;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>
#endif /* BAP_USES_PDUR */

#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
static bool_t BAP_Transmit_TxData(BapCanInterfaceChannel_t aCanInterfaceChannel
        , BapCanMsgId_t aPduId
        , uint16_t u16Index
        , uint16_t au16MsgLength)
{
    Std_ReturnType transmitResult;
    bool_t retval = BAP_FALSE;

#ifdef BAP_USES_PDUR
    {
        PduIdType aPdurPduId;
        pduInfo.SduLength = au16MsgLength; /* BAP Message Payload Length + additional Padding if CAN-FD is used  */

        /* Fall-CAN */
        if ( aCanInterfaceChannel < (BapCanInterfaceChannel_t)10)
        {
            pduInfo.SduDataPtr = &aalb_CanTxBuffers[u16Index][1];
        }
        /* Fall-FR */
        else if ( (aCanInterfaceChannel >= (uint8_t)10) && (aCanInterfaceChannel < (uint8_t)20) )
        {
            pduInfo.SduDataPtr = &aalb_CanTxBuffers[u16Index][0];
            pduInfo.SduLength += (PduLengthType)1;    /* BAP Message Length plus 1 byte for DLC */
        }
        /* Fall-Ethernet */
        else if ( (aCanInterfaceChannel >= (uint8_t)20) && (aCanInterfaceChannel < (uint8_t)30) )
        {
            pduInfo.SduDataPtr = &aalb_CanTxBuffers[u16Index][2];   /* without 2 Byte Header Payload Start at Index 2 for Ethernet */
        }
        else
        {
        	// For Misra compliancy
        }

        aPdurPduId = aalb_GetPdurTxPduByBapTxPdu((PduIdType) aPduId);
        transmitResult = (Std_ReturnType)PduR_BAPTransmit(aPdurPduId, &pduInfo);

#elif defined(BAP_USES_CAN)
        if ( aCanInterfaceChannel < (BapCanInterfaceChannel_t)10)
        {
            pduInfo.SduDataPtr = &aalb_CanTxBuffers[u16Index][1];
            pduInfo.SduLength = au16MsgLength;    /* BAP Message Length */

            transmitResult = CanIf_Transmit( (PduIdType) aPduId, &pduInfo);

#elif defined(BAP_USES_FR)
            if ( (aCanInterfaceChannel >= 10) && (aCanInterfaceChannel < 20) )
            {
                pduInfo.SduDataPtr = &aalb_CanTxBuffers[u16Index][0];
                pduInfo.SduLength = au16MsgLength+1;    /* BAP Message Length plus 1 byte for  DLC */

                transmitResult = FrIf_Transmit(aPduId, &pduInfo);
#else
                {
#endif /* BAP_USES_CAN */

                    if ((E_OK == transmitResult) || (BAP_E_PENDING == transmitResult))
                    {
                        retval = BAP_TRUE;
                    }
                    else
                    {
                        /*transmission failed, reset dlc in buffer so that Tx is not locked*/
                        aalb_ResetCanTxBuffers(aPduId, u16Index);
                    }
                }

    return retval;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


/* Definition (Implementation) of global functions */

/**
 * Sends diagnostic messages from BAP to FlexRay or CAN.
 * See BAP-API documentation
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BapError_et BAP_SendDebugInfo(const uint8_t pDebugInfo[8])
{
	BapError_et retval = BapErr_OK;
	/* BAP_SendDebugInfo_Active == 0 means BAP_DBG_Task is active
	   BAP_SendDebugInfo_Active == 1 means BAP_DBG_Task is not active */
	if(BAP_TRUE == (bool_t)BAP_SendDebugInfo_Active)
	{
		/** @todo Implement your specific debug interface here if necessary, e.g. send the debug info over an own PDU Id */
#ifdef AALB_BAP_DIAGNOSTICS_PDU_SEND_ID
		PduInfoType pduInfo;
		Std_ReturnType transmitResult;

#ifdef BAP_USES_PDUR
		PduIdType aPdurPduId;
		pduInfo.SduDataPtr = BAP_DBG_DebugInfoTable;
		pduInfo.SduLength = (uint8_t) 8;
        aPdurPduId = aalb_GetPdurTxPduByBapTxPdu(AALB_BAP_DIAGNOSTICS_PDU_SEND_ID);
        transmitResult = PduR_BAPTransmit(aPdurPduId, &pduInfo);
		if (transmitResult == E_OK) {
			retval = BapErr_OK;
		} else {
			return BapErr_Busy;
		}
#elif defined(BAP_USES_CAN)
		pduInfo.SduDataPtr = BAP_DBG_DebugInfoTable;
		pduInfo.SduLength = (uint8_t) 8;
		transmitResult = CanIf_Transmit(AALB_BAP_DIAGNOSTICS_PDU_SEND_ID, &pduInfo);
		if (transmitResult == E_OK) {
			retval = BapErr_OK;
		} else {
			return BapErr_Busy;
		}
#elif defined(BAP_USES_FR)
		pduInfo.SduDataPtr = BAP_DBG_DebugInfoTable;
		pduInfo.SduLength = (uint8_t) 8;
		transmitResult = FrIf_Transmit(AALB_BAP_DIAGNOSTICS_PDU_SEND_ID, &pduInfo);
		if (transmitResult == E_OK) {
			retval = BapErr_OK;
		} else {
			return BapErr_Busy;
		}
#else
		transmitResult = BapErr_Busy;
#endif

#endif /* #ifdef AALB_BAP_DIAGNOSTICS_PDU_SEND_ID */

	}
	else
	{
		retval = BapErr_SendDebugDisable;
	}

	return retval;
}

#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>

/**
 *  BAP_CANUBS_TxData() has to be implemented by the bus connection and
 *  is called by the BAP Stack data shall be transmitted via CANBUS or FlexRay BUS.
 *
 *  @param aCanInterfaceChannel identifies physical CAN interfaces.
 *  aCanInterfaceCannel is [0, 9] --> TxHandle will be transmitted via CAN BUS
 *  aCanInterfaceCannel is [10, 19] --> TxHandle will be transmitted via FlexRay BUS
 *  aCanInterfaceCannel is [20, 29] --> TxHandle will be transmitted via Ethernet BUS
 *
 *  @param aPduId is the PDU identifier or a CAN message handle
 *  which is used for communication (e.g. CAN Id)
 *
 *  @param apData points to the data to be transmitted.
 *
 *  @param au16MsgLength contains the length of the data to be transmitted.
 *
 *  @returns
 *  BAP_TRUE in case of success, no re-transmit to bus interface necessary.
 *  BAP_FALSE in case of an error. There will be a retry.
 *
 *  @remarks If transmission shall be done with Vector Software mechanism
 *  delivered file "bap_bclcan_vector.c" has to be linked.
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_FAR bool_t BAP_CANUBS_TxData(BapCanInterfaceChannel_t aCanInterfaceChannel
        , BapCanMsgId_t aPduId
        , const ptr_t apData
        , uint16_t au16MsgLength)
{
    bool_t retval = BAP_FALSE;
    bool_t iFChnValid = BAP_FALSE;    /* Validity of Interface Channel */ 
    uint16_t u16Index = aalb_GetTxHandleByPdu((PduIdType)aPduId);
    uint16_t u16CanFdLengtWithPadding = 0; 

    /* entry found? */
    if ( (BAP_MAX_UINT_16 != u16Index) && (NULL != apData) )
    {
        if (au16MsgLength > MAX_BAP_MSG_LEN)
        {
            /* must not be reached by BAP */
            au16MsgLength = MAX_BAP_MSG_LEN;
        }
#if defined(BAP_USES_CAN)
        /* Pruefung ob es sich um eine CAN-FD Nachricht handelt  */
        if (((BapCanInterfaceChannel_t)10 > aCanInterfaceChannel) && ((uint16_t)8 < au16MsgLength))
        {
            /* Abrufen der Nachrichtenlange nach CAN-FD Format. */
#if defined(BAP_CAN_FD_PADDING_ENABLE)
            u16CanFdLengtWithPadding = BAP_GetCanFdDataLength(au16MsgLength);
#else
            u16CanFdLengtWithPadding = au16MsgLength;
#endif
            /* Initialisieren des Buffer-Bereichs auf null, da die urspruengliche Nachrichtenlaenge kuerzer sein kann */
            /* Beruecksichtigt werden muss der 1 Byte Header der aber bei CAN und CAN-FD nicht mit uebertragen wird */
            /*lint -e9087*/ /* MISRA_2012_REQ_11.3 : 1st argument of MEMSET is implicitly cast to void*.
             	 	 	 	 * MEMSET was manually tested with this argument and behaved properly.*/
            MEMSET(&aalb_CanTxBuffers[u16Index][(uint8_t)1], 0, (u16CanFdLengtWithPadding));
            /*lint +e9087*/
            
            /* Valid interface channel found. */ 
            iFChnValid = BAP_TRUE;
        }
#endif /* BAP_USES_CAN */

        /* DLC = 1Byte */
        if( aCanInterfaceChannel < (BapCanInterfaceChannel_t)20 ) /* for CAN, FR and CANFD  equal 10 .. 19*/
        {
            aalb_CanTxBuffers[u16Index][0] = (uint8_t)(au16MsgLength);

            /*lint -e9087*/ /* MISRA_2012_REQ_11.3 : 1st and 2nd arguments of MEMCPY are of types (uint8_t*).
                             * They are implicitly cast to (void*). The memory is packed because it is uint8_t so there should be no problem to copy.*/
            MEMCPY( &aalb_CanTxBuffers[u16Index][1], apData, au16MsgLength);
            /*lint +e9087*/
            
            /* Valid interface channel found. */ 
            iFChnValid = BAP_TRUE;
        }

        /* DLC = 2Bytes Header wird bei Ethernet nicht uebertragen, wird aber benötigt fuer Funktion BAP_CANUBS_IsReadyForTx   */
        else if ( aCanInterfaceChannel < (BapCanInterfaceChannel_t)30 ) /* for Ethernet means aCanInterfaceChannel 20 .. 29    */
        {
            aalb_CanTxBuffers[u16Index][0] = (uint8_t)(au16MsgLength>>8);
            aalb_CanTxBuffers[u16Index][1] = (uint8_t) au16MsgLength;
            /*lint -e9087*/ /* MISRA_2012_REQ_11.3 : 1st and 2nd arguments of MEMCPY are of types (uint8_t*).
                             * They are implicitly cast to (void*). The memory is packed because it is uint8_t so there should be no problem to copy.*/
            MEMCPY( &aalb_CanTxBuffers[u16Index][2], apData, au16MsgLength);
            /*lint +e9087*/
            
            /* Valid interface channel found. */ 
            iFChnValid = BAP_TRUE;
        }
        else 
        {
            /* fuer zukuenftige Erweiterungen */
            /* NO Valid interface channel found ! */ 
            iFChnValid = BAP_FALSE;           
       
        }
        
        /* Wird fuer CAN-FD benoetigt, damit die Nachricht inklusive der padding-bytes uebertragen wird */ 
        /* Ticket SSWCCB-60 nur wenn Padding Enabled ist, macht if Abfrage Sinn  */
#if defined(BAP_CAN_FD_PADDING_ENABLE)        
        if ( u16CanFdLengtWithPadding > au16MsgLength )
        {
            au16MsgLength = u16CanFdLengtWithPadding ;
        }
#endif        
        
        /* Call BAP_Transmit_TxData only if the Interface Channel is Valid */
        if(iFChnValid == BAP_TRUE)
        {
            retval = BAP_Transmit_TxData(aCanInterfaceChannel, aPduId, u16Index, au16MsgLength );
        }    
        
    }
    return retval;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


/**
 *  BAP_CANUBS_IsReadyForTx() has to be implemented by bus connection
 *  and is called by BAP stack (BAP_CANUBS_TxData) any time there is
 *  data to be transmitted.
 *
 *  The bus interface replies either with BAP_TRUE in case of sending
 *  of data is allowed or BAP_FALSE if sending of data is not allowed
 *  at the moment.
 *
 *  @param aCanInterfaceChannel identifies the number of the physical
 *  CAN interface.
 *
 *  @param aPduId is a PDU identifier or a CAN message handle
 *  which is used for communication (e.g. CAN Id)
 *
 *  @returns
 *  BAP_TRUE in case of calling BAP_CANUBS_TxData is permitted or
 *  BAP_FALSE if it is prohibited.
 *
 *  @remarks
 *  In case of BAP_TRUE data will be prepared for transmission and will
 *  be send out with BAP_CANUBS_TxData.
 *
 *  This pre-check is used for optimization of run-time because data will be
 *  processed only if required
 *
 *  This function shall return BAP_FALSE in case of BusOff.
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_FAR bool_t BAP_CANUBS_IsReadyForTx(BapCanInterfaceChannel_t aCanInterfaceChannel
        , BapCanMsgId_t aPduId)
{
    bool_t retval = BAP_FALSE;  /* Default, in case of aalb_cfg.c is not adapted */
    uint16_t u16Index = aalb_GetTxHandleByPdu((PduIdType)aPduId);

    uint16_t u16DLCSize=(uint16_t)0;

    if ( (BapCanInterfaceChannel_t)20 > aCanInterfaceChannel )  /* for CAN, CAN-FD, FR Number Attribut 0 .. 19 */
    {
        u16DLCSize = (aalb_CanTxBuffers[u16Index][0]);
    }
    else if ( (BapCanInterfaceChannel_t)30 > aCanInterfaceChannel ) /* for Ethernet Number Attribut 20 .. 29 */
    {
        u16DLCSize = ((uint16_t)(aalb_CanTxBuffers[u16Index][0]) ) << 8u;
        u16DLCSize += (uint16_t)(aalb_CanTxBuffers[u16Index][1]);
    }
    else /* The Interface Channel is invalid. Set Entry not found */
    {
        /* Reset the entry to invalid */
        u16Index = BAP_MAX_UINT_16;
    }
    /* entry found? */
    if (BAP_MAX_UINT_16 != u16Index)
    {
        /* check if DLC = 0, means transmission buffer is available */
        if ( (uint16_t)0 == u16DLCSize)
        {
            retval = BAP_TRUE;
            Bap_CanMsg_TimeoutTable[u16Index] = (uint8_t) 0;
        }
        else
        {
            if (Bap_CanMsg_TimeoutTable[u16Index] < BAP_MAX_CONFIRMATION_FLAG_TIMEOUT)
            {
                Bap_CanMsg_TimeoutTable[u16Index]++;
            }
            else /* CAN-Message Timeout occurs, Clears the Transmit and reset buffer */
            {
                /* Puffer auf Null setzen und damit Nachricht loeschen */
                aalb_ResetCanTxBuffers(aPduId, u16Index);
                Bap_CanMsg_TimeoutTable[u16Index] = (uint8_t) 0;
            }
        }
    }
    return retval;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


/**
 *  BAP_CANUBS_InitReadyForTx needs to be implemented by bus connection.
 *  It is called by BAP Stack during initialization of the stack.
 *
 *  @param aCanInterfaceChannel identifies the number of the physical
 *  CAN interface.
 *
 *  @param aPduId is a PDU identifier or a CAN message handle
 *  which is used for communication (e.g. CAN Id)
 *
 *  @remarks
 *  Immediately after initialization this function must return BAP_TRUE.
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_FAR void BAP_CANUBS_InitReadyForTx(BapCanInterfaceChannel_t aCanInterfaceChannel
        , BapCanMsgId_t aPduId)
{
    uint16_t u16Index = aalb_GetTxHandleByPdu((PduIdType)aPduId);
    /* entry found? */
    if (BAP_MAX_UINT_16 != u16Index)
    {
        /* initialize DLC with 0, means tx buffer is available. See BAP_CANUBS_IsReadyForTx. */
        aalb_ResetCanTxBuffers(aPduId, u16Index);
    }
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


/**
 * Version Information capability has to be dis/enabled with
 * pre-compiler switch BAP_VERSION_INFO_API.
 *
 * @todo check your vendor information and define pre-compiler switch
 */

#ifdef BAP_VERSION_INFO_API
/**
 *  BAP_GetVersionInfo is an optional function which has to be enabled by
 *  pre-compiler switch BAP_VERSION_INFO_API and provides version information
 *  about the module like ModuleID, VendorID and Vendor specific version numbers
 *  acording to BSW00407. For version-encoding BCD is used, meaning each digit
 *  needs to be between 0 and 9.
 *
 *  @param aVersionInfo is a structure which holds version information. see Std_Types.h
 *
 *  @remarks update your VendorID, ModuleID and Vendor specific version numbers
 *  e.g. in aalb_cfg.h
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
void BAP_GetVersionInfo(Std_VersionInfoType *aVersionInfo)
{
    aVersionInfo->vendorID = BAP_VENDOR_ID;
    aVersionInfo->moduleID = BAP_MODULE_ID;
#   ifdef BAP_USES_ASR3
    /*lint -e40*/ /* MISRA_2012_REQ_1.3: instanceID is seen as undeclared.
     	 	 	   * However, ASR3 defines the element uint8_t instanceID for
     	 	 	   * the structure Std_VersionInfoType, so no problem here.*/
    aVersionInfo->instanceID = (uint8_t) 0x00u;
    /*lint +e40*/
#   endif /* BAP_USES_ASR3 */
    aVersionInfo->sw_major_version = (uint8_t) BAP_VERSION_MAJOR;
    aVersionInfo->sw_minor_version = (uint8_t) BAP_VERSION_MINOR;
    aVersionInfo->sw_patch_version = (uint8_t) BAP_VERSION_PATCH;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>
#endif /* BAP_VERSION_INFO_API */

/* CallBack functions */


/**
 *  BAP_RxIndication is called by PDU Router if an according
 *  PDU is received through FlexRay Interface. Received PDU data
 *  is found in receive buffer of the FlexRay Interface and will
 *  be copied to BAP stack input buffer by calling BAP_CANUBS_RxData().
 *
 *  @param AalbRxPduId ID of a PDU which was received via FlexRay Interface
 *
 *  @param AalbRxSduPtr is a message handle
 *
 *  @returns
 *	Nothing
 *
 *  @remarks
 *  Immediately after initialization this function must return BAP_TRUE.
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
void BAP_RxIndication(PduIdType AalbRxPduId, const PduInfoType * PduInfoPtr)
{
    uint16_t u16Index = aalb_GetRxHandle(AalbRxPduId);

    /* entry found? */
    if ( (BAP_MAX_UINT_16 != u16Index) && (NULL != PduInfoPtr))
    {
        BapCanInterfaceChannel_t canInterfaceChannel = aalb_PduId2CanMsgIdTab[u16Index].canChannel;

#ifdef BAP_USES_CAN
        if ( canInterfaceChannel < (BapCanInterfaceChannel_t)10)
        {
            BAP_CANUBS_RxData(canInterfaceChannel
                    , (uint8_t) AalbRxPduId
                    , PduInfoPtr->SduDataPtr
                    , PduInfoPtr->SduLength);
        }
#endif /* BAP_USES_CAN */

#ifdef BAP_USES_FR
        if ( (canInterfaceChannel >= 10) && (canInterfaceChannel < 20) )
        {
            BAP_CANUBS_RxData(canInterfaceChannel
                    , AalbRxPduId
                    , PduInfoPtr->SduDataPtr + 1
                    , PduInfoPtr->SduDataPtr[0]);
        }
#endif /* BAP_USES_FR */

/* Fuer Ethernet,  */
#ifdef BAP_USES_ETH
        if ( (canInterfaceChannel >= 20) && (canInterfaceChannel < 30) )
        {
            BAP_CANUBS_RxData(canInterfaceChannel
                    , AalbRxPduId
                    , PduInfoPtr->SduDataPtr 
                    , PduInfoPtr->SduLength);
        }
#endif /* BAP_USES_ETH */
    }

    /*  FHA: BugFix [SSWCCB-2514] ASG-DB-1 und FSG-DB-1:  If the RX Diagnostics Id is defined */
#ifdef AALB_BAP_DIAGNOSTICS_PDU_ID
    else if(AALB_BAP_DIAGNOSTICS_PDU_ID == AalbRxPduId)
    {
        BAP_ProcessDebugControl(PduInfoPtr->SduDataPtr);
    }
    else
    {
        /* No Statement */
    }    
#endif /* AALB_BAP_DIAGNOSTICS_PDU_ID */
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


/**
 *  This function is called by the PDU router if the data was sent
 *
 *  @param AalbTxPduId Id of the PDU where the data was sent
 *
 *  @returns
 *      Nothing
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
void BAP_TxConfirmation(PduIdType AalbTxPduId)
{
#if( !defined(BAP_USES_PDUR) && defined(BAP_USES_ASR4) )
    /* For CAN IF / FR IF + AUTOSAR4 Configurations */
    uint16_t u16Index = aalb_GetComIfTxHandleByPdu(AalbTxPduId);
#else
    uint16_t u16Index = aalb_GetTxHandleByPdu(AalbTxPduId);
#endif
    /* entry found? */
    if (BAP_MAX_UINT_16 != u16Index)
    {
        /* set DLC to 0, means buffer is available again */
        aalb_ResetCanTxBuffers((BapCanMsgId_t) AalbTxPduId, u16Index);
    }
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


#if( defined(BAP_USES_FR) || defined(BAP_USES_PDUR) ) /* [FST] 2015-02-27 Define for PDUR was missing, though mentioned in comment */
/**
 *  This function is called by PDU router on these conditions
 *  - A previous request was called by Aalb (see BAP_CANUBS_TxData)
 *  - FlexRay interface is ready to copy data into send buffer
 *
 *  @param AalbTxPduId Id of the PDU to which the send buffer is assigned
 *  @param PduInfoPtr Pointer to the send buffer
 *  @returns
 *  	E_OK: SDU has been copied and Sdulength indicates the number of copied bytes.
 *  	E_NOT_OK: No SDU has been copied. PduInfoPtr must not be used since it may contain a NULL pointer or point to invalid data
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
Std_ReturnType BAP_TriggerTransmit(
        PduIdType AalbTxPduId,
        const PduInfoType * PduInfoPtr)
{
    uint16_t u16Index;
    uint16_t u16DLCSize;

    u16Index = aalb_GetTxHandleByPdu(AalbTxPduId);

    /* entry found? */
    if ((BAP_MAX_UINT_16 != u16Index) && PduInfoPtr)
    {
        if( BAP_GetTxPduSize((BapCanMsgId_t)AalbTxPduId) <= 255u) /* for CAN, CAN-FD, FR */
        {
            u16DLCSize = (uint16_t)aalb_CanTxBuffers[u16Index][0] + (uint16_t)1;
        }
        else /* [FST] 2015-03-10 only available for Ethernet at this time */
        {
            u16DLCSize = ((uint16_t)(aalb_CanTxBuffers[u16Index][0]) ) << 8u;
            u16DLCSize += (uint16_t)aalb_CanTxBuffers[u16Index][1];
            u16DLCSize += (uint8_t)2;
        }

        /* copy data into target buffer */
        /*lint -e9087*//* Cast to void-pointer required for generic memcopy */
        MEMCPY(PduInfoPtr->SduDataPtr
                , &aalb_CanTxBuffers[u16Index][0]
                                               , u16DLCSize);    /* +1 oder 2 Byte: data length plus length-byte */
        /*lint +e9087*/
        return E_OK;
    }
    else
    {
        return E_NOT_OK;
    }
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>
#endif /* ( defined(BAP_USES_FR) || defined(BAP_USES_PDUR) ) */

/**
 * This function is called for reset the first (or first two in case of Ethernet) Bytes of
 * aalb_CanTxBuffers[u16Index]
 *
 * @param aPduId Id of the PDU to which the send buffer is assigned
 * @param u16Index Index of the handle
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
void aalb_ResetCanTxBuffers(BapCanMsgId_t aPduId, uint16_t u16Index)
{
    aalb_CanTxBuffers[u16Index][0] = 0x00u;
    aalb_CanTxBuffers[u16Index][1] = 0x00u;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>

/**
* Gibt anhand der Nachrichtenlänge die CAN-FD Data-Length zurueck.
*
* @param au16MsgLength ist die Laenge in Byte der zu versendenden Nachricht.
*
* @returns CAN-FD Data-Length. Bei Nachrichtenlaengen groeßer 64 Byte wird der maximale CAN-FD Data-Length zuruekgegeben.
*/
#if defined(BAP_CAN_FD_PADDING_ENABLE)
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_IMPL_FAR uint16_t BAP_GetCanFdDataLength(uint16_t au16MsgLength)
{
    /* Anpassen der Nachrichtenlaengen nur bei groesser acht Byte. */
    if ((uint16_t)8 < au16MsgLength)
    {
        if ((uint16_t)Bap_Can_Fd_12_Byte >= au16MsgLength)
        {
            au16MsgLength = (uint16_t)Bap_Can_Fd_12_Byte;
        }
        else if ((uint16_t)Bap_Can_Fd_16_Byte >= au16MsgLength)
        {
            au16MsgLength = (uint16_t)Bap_Can_Fd_16_Byte;
        }
        else if ((uint16_t)Bap_Can_Fd_20_Byte >= au16MsgLength)
        {
            au16MsgLength = (uint16_t)Bap_Can_Fd_20_Byte;
        }
        else if ((uint16_t)Bap_Can_Fd_24_Byte >= au16MsgLength)
        {
            au16MsgLength = (uint16_t)Bap_Can_Fd_24_Byte;
        }
        else if ((uint16_t)Bap_Can_Fd_32_Byte >= au16MsgLength)
        {
            au16MsgLength = (uint16_t)Bap_Can_Fd_32_Byte;
        }
        else if ((uint16_t)Bap_Can_Fd_48_Byte >= au16MsgLength)
        {
            au16MsgLength = (uint16_t)Bap_Can_Fd_48_Byte;
        }
        else
        {
            au16MsgLength = (uint16_t)Bap_Can_Fd_64_Byte;
        }
    }
    return au16MsgLength;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>
#endif /* defined(BAP_CAN_FD_PADDING_ENABLE) */



