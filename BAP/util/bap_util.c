/******************************************************************
 *
 *     Copyright (c) 2004-2023 Volkswagen AG, D-38436 Wolfsburg
 *
 ******************************************************************
 *
 * Projekt:    BAP
 * Komponente: Util
 * BAP Version: 1.12.2
 *
 ******************************************************************
 *
 * Beschreibung
 *
 *  Diese Datei enthaelt Hilfsfunktionen fuer alle Schichten im
 *  BAP Projekt. Die Hilfsfunktionen umfassen auch den Zugriff auf 
 *  die Konfigurationstabellen.
 *
 ******************************************************************
 *
 * Versionsgeschichte (ohne SCM)
 *
 * Datum        Version     Autor       Beschreibung
 * ----------------------------------------------------------------
 * 2023-10-10	1.12.2		DRH			[EEARCH-35935] Release preparation, adapt Copyright date and version number.
 * 2022-11-15   1.12.1      DRH         [SSWPPB-297] Renamed macros and global variables module specific
 * 2022-10-21	1.12.1		DRH			[SSWPPB-296] Release preparation, adapt Copyright date and version number.
 * 2022-06-17	1.12.0		DRH			[SSWPPB-269] Release preparation, adapt Copyright date and version number.
 * 2021-12-07	1.11.3		JEO			[SSWPPB-244] Release preparation, adapt Copyright date and version number.
 * 2021-11-23   1.11.3      DRH         [SSWPPB-216] Remove unnecessary include of MemMap.h. Improve DLL generation.
 * 2021-03-01	1.11.3		JEO			[SSWPPB-142] Improve justification of Pc-Lint deac or MISRA rules violation.
 * 2019-01-18	1.10.99		FFS			[SSWCCB-2657] Improvement of BAP_GetLsgRomRow, adding the use of a table of LSG
 * 2018-07-19	1.10.3		FFS			[SSWCCB-2522] Misra-2012 fix
 * 2017-07-31   1.10.0      FHA         [SSWCCB-2474] DLC-Mapping für CAN-FD
 * 2017-02-16	1.9.0 		FST			[SSWCCB-1545] SSW-Lokatierungs-Pragmas eingefuegt
 * 2015-03-10	1.8.0.3		FST			[SSWCCB-2188][SSWCCB-2189][SSWCCB-2190] BAP_GetRxPduSize und BAP_GetTxPduSize eingefuegt, waren bisher in bap_bclutil
 * 2013-01-30	1.7			WWU			MISRA-2004 fix
 * 2006-04-12   1.4         ALA         Unterstuetzung fuer BAP_ROM_DATA_FAR.
 * 2006-04-12   1.4         ALA         Neue Funktion BAP_RomToRamMemCpy
 ******************************************************************/


/* Systemincludes mit <...> */
#include <string.h>

/* Bibliotheken von externen Herstellen mit <...> */

/* Eigene Header-Dateien "..." */
#include "bap_util.h" 
#include "bap_balconfig.h"
#include "bap_bclconfig.h"
#include "bap_debug.h"

/* Externe globale Variablen-Definitionen */
/* @WWU:
 * MISRA-2004 fix: Bap_oPars wird als interne Objekt in ganzen BAP Verwendet
 * Definiere Bap_oPars als globale Variable */
#define BAP_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
BapInternalParameters_ot Bap_oPars;
BapInternalParameters_ot Bap_oPars_fctlist; /* SSWCCB-1028: Hier muss man eine zusaetzliche Bap_oPars_fctlist definieren. */
#define BAP_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <BAP_MemMap.h>


#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
extern bool_t Bap_reAssignLsgRomRowFctTable ;
bool_t Bap_reAssignLsgRomRowFctTable ;
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>

	
/* Interne Makro-Definitionen */

/* Interne Typ-Definitionen */

/* Interne Const Deklarationen */

/* Interne statische Variablen */

#define BAP_START_SEC_VAR_NO_INIT_UNSPECIFIED /* PRQA S 1534 # Macro required for AUTOSAR Memory Mapping */
#include <BAP_MemMap.h> /* PRQA S 5087 # Include required for AUTOSAR Memory Mapping */
BAP_STATIC BapLsgRomRow_pot lsgRomRowIdxTable[BAP_IDX_HIGHEST_LSG] = { NULL };
#define BAP_STOP_SEC_VAR_NO_INIT_UNSPECIFIED /* PRQA S 1534 # Macro required for AUTOSAR Memory Mapping */
#include <BAP_MemMap.h> /* PRQA S 5087 # Include required for AUTOSAR Memory Mapping */

/* Vorwaerts-Deklarationen von statischen Funktionen */

/* Definition (Implementierung) von statischen Funktionen */

/* Definition (Implementierung) von globalen Funktionen */


/*
 *  Diese Funktion wird in bap_util.h dokumentiert.
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>

BapLsgRomRow_pot BAP_IMPL_FAR
BAP_GetLsgRomRow(DBGVAR lsgId_t aLsgId)
{
    BapLsgRomRow_pot poReturnLsg = NULL;

#ifdef DLL_COMPILATION
	// when used in CANoe, the DLL is only loaded once
	// node data is independent, but the BAP functions are shared (so this function and its static variables are shared between LSGs)
	// as such, the static array above would need to be initialized at every call
	// to make sure we are using the data from the correct LSG
	// issues arise when you have an ASG and FSG with the same ID in the same simulation (common case)
	// e.g. ASG 114 and FSG 114 - the data from the ASG might be used for the FSG, as they share the same position in lsgRomRowIdxTable
	Bap_reAssignLsgRomRowFctTable = BAP_TRUE;
#endif

    if( BAP_FALSE != Bap_reAssignLsgRomRowFctTable ) {
    	uint8_t u8LsgIndex = BAP_P_LSG_ROM_TABLE_ROWS;
    	while( (uint8_t)0 < u8LsgIndex ) {
          u8LsgIndex--;
          /* MISRA_2012_REQ_10.5 : no risk arise because 1 fit in enum. could be a 1u */
          if( NULL != BAP_pLsgRomTable[u8LsgIndex] ){
             lsgRomRowIdxTable[((lsgId_t)BAP_pLsgRomTable[ u8LsgIndex]->lsgId) - ((lsgId_t)1) ] = BAP_pLsgRomTable[u8LsgIndex];
          }
       }
       Bap_reAssignLsgRomRowFctTable = BAP_FALSE;
    }else{
		/* left empty only for misra */
	}

    /* MISRA_2012_REQ_14.3 : "((lsgId_t)BAP_IDX_HIGHEST_LSG>=(lsgId_t)aLsgId)" is not invariant,
     * can be false if a wrong aLsdId is given to the function for instance. */
	 /* MISRA_2012_REQ_10.5 : no risk arise because 0 and BAP_IDX_HIGHEST_LSG fit in enum. */
	if(((lsgId_t)0<(lsgId_t)aLsgId) && ((lsgId_t)BAP_IDX_HIGHEST_LSG>=(lsgId_t)aLsgId))
	{
		poReturnLsg = lsgRomRowIdxTable[ (lsgId_t)aLsgId - ((lsgId_t)1) ];
		/* MISRA_2012_REQ_10.5 : no risk arise because 1 fit in enum. could be a 1u */
	}
    if (NULL == poReturnLsg)
    {
		BAP_DBG_InvalidArgError(aLsgId);
    }else{
		/* left empty only for misra */
	}
    return poReturnLsg;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


/*
 *  Diese Funktion wird in bap_util.h dokumentiert.
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BapFctRomRow_pot BAP_IMPL_FAR
BAP_GetLsgFctRomRow(BapLsgRomRow_pot apoLsgRomRow, DBGVAR fctId_t aFctId)
{
    BapFctRomRow_pot poReturnFct = NULL;

    if (apoLsgRomRow != NULL)
    {
        DBGVAR uint8_t u8FctIndexLowest = (uint8_t) 0;
        DBGVAR uint8_t u8FctIndexMiddle;
        DBGVAR uint8_t u8FctIndexHighest= apoLsgRomRow->u8FctRomTableSize;

        /* binaerer Suchalgorithmus O(lg N) */

        while((u8FctIndexHighest>u8FctIndexLowest))
        {
            u8FctIndexMiddle = (uint8_t) ((uint8_t)(u8FctIndexHighest + u8FctIndexLowest) / (uint8_t)2u);

            if (BAP_FctRomTables[apoLsgRomRow->u16FctRomIndex + u8FctIndexMiddle].fctId == aFctId)
            {
                /* passende Zeile wurde gefunden */
                poReturnFct = &BAP_FctRomTables[apoLsgRomRow->u16FctRomIndex + u8FctIndexMiddle];
                u8FctIndexHighest = (uint8_t)0;  /* Schleife abbrechen */
            }
            else
            {
                if (BAP_FctRomTables[apoLsgRomRow->u16FctRomIndex + u8FctIndexMiddle].fctId < aFctId)
                {
                    u8FctIndexLowest =  u8FctIndexMiddle + (uint8_t)1u;
                }
                else
                {
                    u8FctIndexHighest = u8FctIndexMiddle;
                }
            }
        }
        /* falls keine Zeile gefunden wurde, bleibt poReturnFct = NULL */
    }
    return poReturnFct;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


#ifndef BAP_ROM_DATA_FAR_EMPTY
/*
 *  Diese Funktion wird in bap_util.h dokumentiert.
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void 
BAP_RomToRamMemCpy(DBGVAR void * dest, DBGVAR BAP_ROM_DATA_FAR const void * source, DBGVAR const size_t length)
{
    size_t index;

    /*lint -e613*/
    BAP_ASSERT( NULL != dest );
    BAP_ASSERT( NULL != source );

    for(index = 0; index<length; index++)
    {   /* Kopiere von source nach dest */
        ((uint8_t *) dest)[index] = ((BAP_ROM_DATA_FAR const uint8_t *)source)[index];
    }
    /*lint +e613*/
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* #ifndef BAP_ROM_DATA_FAR_EMPTY */


/*
 *  Diese Funktion wird in bap_util.h dokumentiert.
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BapFctRomRow_pot BAP_IMPL_FAR
BAP_GetFctRomRow(DBGVAR lsgId_t aLsgId, DBGVAR fctId_t aFctId)
{
    return BAP_GetLsgFctRomRow(BAP_GetLsgRomRow(aLsgId), (aFctId));
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>

/*
 *  Diese Funktion wird in bap_util.h dokumentiert.
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_IMPL_FAR void 
BAP_InitInternalParameters(BapInternalParameters_pot apoPars)
{
    /*lint -e668*/ /* Alle aufrufenden Funktionen wurden ueberprueft, ob sie fuer apoPars NULL uebergeben */ 
	/*lint -e9087*/ /* MISRA_2012_REQ_11.3 : 1st argument of MEMSET of type BapRxParameters_ot is
	     	 	 	*implicitly cast to void*. MEMSET was manually tested with this argument and behaved properly.*/
    MEMSET(apoPars, 0, sizeof(*apoPars));
    /*lint +e9087*/
    /*lint +e668*/
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>

/*  Diese Funktion ist in bap_util.h dokumentiert */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_IMPL_FAR uint16_t
BAP_GetRxPduSize(BapCanMsgId_t msg_id)
{
    DBGVAR uint16_t u16CanHandleCounter;
    DBGVAR uint16_t pduSize = (uint16_t)0u;

    /* Suche nach dem Can-Handle, ob es einen Eintrag fuer den gewaehlten Segmentierungskanal gibt */
    for ( u16CanHandleCounter = (uint16_t)0; (u16CanHandleCounter<BAP_CAN_RX_SEGMENTATION_CHANNELS) && ((uint16_t)0u == pduSize); u16CanHandleCounter++)
    {
        /* Falls CAN-Id gefunden, pruefe ob Segmentierungskanal vergeben */
        if ( BAP_CanRxMsgPduSizeTable[u16CanHandleCounter].CanMessageId == msg_id )
        {
            pduSize = BAP_CanRxMsgPduSizeTable[u16CanHandleCounter].pduSize;
        }
    }
    return pduSize;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>

/*  Diese Funktion ist in bap_util.h dokumentiert */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_IMPL_FAR uint16_t
BAP_GetTxPduSize(BapCanMsgId_t msg_id)
{
    DBGVAR uint16_t u16CanHandleCounter;
    DBGVAR uint16_t pduSize = 0u;

    /* Suche nach dem Can-Handle, ob es einen Eintrag fuer den gewaehlten Segmentierungskanal gibt */
    for ( u16CanHandleCounter = (uint16_t)0; (u16CanHandleCounter<BAP_CAN_TX_SEGMENTATION_CHANNELS) && ((uint16_t)0u == pduSize); u16CanHandleCounter++)
    {
        /* Falls CAN-Id gefunden, pruefe ob Segmentierungskanal vergeben */
        if ( BAP_CanTxMsgPduSizeTable[u16CanHandleCounter].CanMessageId == msg_id )
        {
            pduSize = BAP_CanTxMsgPduSizeTable[u16CanHandleCounter].pduSize;
        }
    }
    return pduSize;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>

/* CallBack-Funktionen */

