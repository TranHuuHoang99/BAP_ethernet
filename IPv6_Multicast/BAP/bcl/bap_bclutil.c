/******************************************************************
 *
 *     Copyright (c) 2004-2023 Volkswagen AG, D-38436 Wolfsburg
 *
 ******************************************************************
 *
 * Projekt:    BAP
 * Komponente: BCL
 * BAP Version: 1.12.2
 *
 ******************************************************************
 *
 * Beschreibung
 *
 *  Diese Datei enthaelt Hilfsfunktionen fuer die BCL Schicht im BAP
 *  Projekt. Die Hilfsfunktionen umfassen auch den Zugriff auf
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
 * 2021-03-08   1.11.3      DRH         [SSWPPB-142] Replaced magic numbers by constants
 * 2020-09-30   1.11.2      KUL         [SSWPPB-70] Use of BAP_USES_ETH to support POSIX based ECUs with Ethernet
 * 2019-03-21   1.10.99     KUL         [SSWPPB-4] Removal of string.h inclusion
 * 2018-07-19	1.10.3      FFS         [SSWCCB-2522] Misra-2012 fix (release was postponed)
 * 2017-04-01	1.9.0.2	    FST         [SSWCCB-1545] SSW-Lokatierungs-Pragmas eingefuegt
 * 2015-03-17	1.8.0.3	    FST         [SSWCCB-2188][SSWCCB-2189][SSWCCB-2190] BAP_GetRxPduSize und BAP_GetTxPduSize nach bap_util umgezogen
 * 2014-12-11	1.8.0.1	    WWU         [SSWCCB-2104] Funktionen BAP_BCL_GetTxPduSize, BAP_BCL_GetRxPduSize hinzugefuegt.
 * 2014-11-28	1.8.0.0	    FST         [SSWCCB-2105] Formataenderung der Variablen 16Bit->32Bit
 * 2014-07-16	1.8.0       WWU         Makro BAP_USES_PDU fuer PDU-Router erweitert.
 * 2013-02-06	1.7.0       WWU         Funktionsname umbenannt, wegen Misra : Identifier exceeds 31 characters
 * 2012-10-15	1.6.5.1     WWU         Korrektur der Misra-98 Abweichungen
 * 2007-10-12   1.5         SHU         Beim Ruecksetzen des BCL Tx Puffer Bereichs auch NeedsAck zuruecksetzen.
 * 2006-11-20   1.4.1       ALA         Optimierung Laufzeit von Reset-Nachrichten
 * 2006-04-12   1.4         ALA         Unterstuetzung fuer BAP_ROM_DATA_FAR.
 * 2006-03-28   1.3.2       ALA         Stoppen der Intertelegramzeitueberwachung bei Reset
 * 2005-04-29   1.3         ALA         Funktion BAP_BCL_GetFctRomRow() entfernt, Anpassung an neue
 *                                      Datenstrukturen, Verbesserte Compilerunterstuetzung.
 * 2004-11-17   1.2         JOK         Interruptsperre bei BAP_BCL_InterTelegramTimerTask() eingebaut
 * 2004-11-17   1.2         JOK         Funktion BAP_BCL_SetInitRamValues() in zwei Funktionen
 *                                      BAP_BCL_InitRxRamValues() und BAP_BCL_InitTxRamValues() aufgeteilt
 * 2004-06-07   1.1         JOK         Compilerschalter fuer SG-Typen zur Optimierung
 *                                      des ROM-Bedarfs eingefuegt
 * 2004-06-07   1.1         JOK         Include stdlib.h eingefuegt
 * 2004-06-07   1.1         JOK         Funktion BAP_BCL_SetInitRamValues() eingefuegt
 * 2004-06-07   1.1         JOK         Funktion BAP_BCL_InitLsgRamAreas() mittels Hilfsfunktion
 *                                      BAP_BCL_SetInitRamValues() optimiert
 * 2004-06-07   1.1         JOK         Funktion BAP_BCL_GetLsgStatus() entfernt
 ******************************************************************/


/* Systemincludes mit <...> */

/* Bibliotheken von externen Herstellen mit <...> */

/* Eigene Header-Dateien "..." */
#include "bap_util.h"
#include "bap_bcl.h"
#include "bap_bclconfig.h"
#include "bap_config.h"
#include "bap_bclutil.h"
#include "bap_bclbus.h"
#include "bap_debug.h"

/* Externe globale Variablen-Definitionen */

/* diese Variable ist in bap_bclutil.h dokumentiert */

#ifdef BAP_USES_SEGMENTATION
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
bool_t BAP_bInterTelegramTimerRunning;
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#endif /* BAP_USES_SEGMENTATION */

/* Interne Makro-Definitionen */

/* Interne Typ-Definitionen */

/* Interne Const Deklarationen */

/* Interne statische Variablen */

/* Vorwaerts-Deklarationen von statischen Funktionen */

#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
static BAP_IMPL_FAR void
BAP_BCL_InitRxRamValues(BapCanRxRomRow_pot apoCanRomRow);

static BAP_IMPL_FAR void
BAP_BCL_InitTxRamValues(BapCanTxRomRow_pot apoCanRomRow);

#ifdef BAP_USES_SEGMENTATION
BAP_STATIC BAP_IMPL_FAR void
BAP_BCL_HdlInterTelegramTimer(uint16_t au16InterTelegramIndex);
#endif /* #ifdef BAP_USES_SEGMENTATION */

/* Definition (Implementierung) von statischen Funktionen */


/**
 *  Initialisiert alle RAM-Bereiche der BCL TX-Puffer.
 *
 *  @param apoCanRomRow  der zu initialisierende Eintrag in der BCL-TX-Tabelle.
 */
static BAP_IMPL_FAR void
BAP_BCL_InitTxRamValues(BapCanTxRomRow_pot apoCanRomRow)
{
    BapBclTxRamRow_pot poBclTxRamRow;
    /*lint -esym(613,apoCanRomRow) */
    BAP_ASSERT(NULL != apoCanRomRow);

    poBclTxRamRow = apoCanRomRow->poBclTxRamRow;

    /* Ruecksetzen des BCL Tx Puffer Bereichs */
    if(poBclTxRamRow != NULL)
    {
#ifdef BAP_USES_ACKNOWLEDGE
        poBclTxRamRow->flags.fTxRequestNeedsAckFlag = (uint8_t)0;
#endif /* #ifdef BAP_USES_ACKNOWLEDGE */
        poBclTxRamRow->flags.fTxRequestFlag = (uint8_t)0;
#ifdef BAP_USES_SEGMENTATION
        poBclTxRamRow->flags.fTxInProgressFlag = (uint8_t)0;
#endif /* #ifdef BAP_USES_SEGMENTATION */
#ifdef BAP_FSG
        /* Keine Fallunterscheidung fuer das Kombigeraet noetig, da im ASG TxError unbenutzt */
        poBclTxRamRow->flags.fTxErrorFlag = (uint8_t)0;
#endif /* BAP_FSG */
    }

#ifdef BAP_USES_SEGMENTATION
    /* Ruecksetzen des CAN Tx RAM Bereichs (nur bei Segmentierung vorhanden) */
    if (apoCanRomRow->poCanTxRamRow != NULL)
    {
        apoCanRomRow->poCanTxRamRow->flags.fSequenceNumber = (uint8_t)0;
        apoCanRomRow->poCanTxRamRow->u32BclTxBufferByteOffset = (uint32_t)0;
    }
#endif /* #ifdef BAP_USES_SEGMENTATION */

    BAP_InhibitRamTable[apoCanRomRow->u8InhibitIndex].u16InhibitTimer = (uint8_t)0;

    /*lint +esym(613,apoCanRomRow) */
    return;
}


/**
 *  Initialisiert alle RAM-Bereiche der BCL RX-Puffer.
 *
 *  @param apoCanRomRow  der zu initialisierende Eintrag in der BCL-RX-Tabelle.
 *
 */
static BAP_IMPL_FAR void
BAP_BCL_InitRxRamValues(BapCanRxRomRow_pot apoCanRomRow)
{
    BapBclRxRamRow_pot poBclRxRamRow;
#ifdef BAP_USES_SEGMENTATION
    uint16_t u16MaxDataSize;
#endif /* #ifdef BAP_USES_SEGMENTATION */
    /*lint -esym(613,apoCanRomRow) */
    BAP_ASSERT(NULL != apoCanRomRow);

    poBclRxRamRow = apoCanRomRow->poBclRxRamRow;

    /* Ruecksetzen des BCL Tx Puffer Bereichs */
    if(poBclRxRamRow != NULL)
    {
#ifdef BAP_USES_SEGMENTATION
        poBclRxRamRow->flags.fRxInProgressFlag = BAP_FALSE;
#endif /* #ifdef BAP_USES_SEGMENTATION */
        poBclRxRamRow->flags.fRxCompleteFlag = BAP_FALSE;
        poBclRxRamRow->flags.fRxErrorFlag = BAP_FALSE;

        poBclRxRamRow->oBufferWithLength.u32Length = apoCanRomRow->u32Size;
        /* nur bei FixedByteSequence ist das Loeschen des Puffers erforderlich.
           FixedByteSequence ist immer unsegmentiert.
           Bei ByteSequence wird darauf verzichtet, um die Verarbeitungszeit
           einer Reset-Nachricht gering zu halten.
         */
#ifdef BAP_USES_SEGMENTATION
        u16MaxDataSize = BAP_GetRxPduSize(apoCanRomRow->canMsgId) - BAP_HEADER_BYTES_NONSEG;
        if ( (BapSegType_Unsegmented == apoCanRomRow->eSegmentationType) &&
             (apoCanRomRow->u32Size > u16MaxDataSize)
            )
#endif /* #ifdef BAP_USES_SEGMENTATION */
        {
        	/*lint -e9087*/ /* MISRA_2012_REQ_11.3 : 1st argument of MEMSET of type uint8* is
        		     	 	 *implicitly cast to void*. uint8_t will be filled by 0, which will not cause any problem.*/
            MEMSET(poBclRxRamRow->oBufferWithLength.paru8Buffer, 0
                , poBclRxRamRow->oBufferWithLength.u32Length);
            /*lint +e9087*/
        }
    }

#ifdef BAP_USES_SEGMENTATION
    /* Ruecksetzen des CAN Rx RAM Bereichs (nur bei Segmentierung vorhanden) */
    if (apoCanRomRow->poCanRxRamRow != NULL)
    {
        apoCanRomRow->poCanRxRamRow->flags.fSequenceNumber = (uint8_t)0;
        apoCanRomRow->poCanRxRamRow->u32BclRxBufferByteOffset = (uint32_t)0;
        *apoCanRomRow->pu16InterTelegramTimer = (uint8_t)0;
    }
#endif /* #ifdef BAP_USES_SEGMENTATION */

    /*lint +esym(613,apoCanRomRow) */
    return;
}


#ifdef BAP_USES_SEGMENTATION
/**
 *  Dekrementiert einen InterTelegramTimer um '1' je Funktionsaufruf
 *
 *  @param au16InterTelegramIndex 1 basierter Index des InterTelegramTimers in der RAM-Tabelle
 */
BAP_STATIC BAP_IMPL_FAR void
BAP_BCL_HdlInterTelegramTimer(uint16_t au16InterTelegramIndex)
{
    DBGVAR uint16_t *pu16InterTelegramTimer;

    au16InterTelegramIndex--;

    pu16InterTelegramTimer = &BAP_u16InterTelegramTimerTable[au16InterTelegramIndex];

    if( (uint16_t) 0u < *pu16InterTelegramTimer)
    {
    	--(*pu16InterTelegramTimer);
        if( (uint16_t) 0u == *pu16InterTelegramTimer)
        {
            DBGVAR fctId_t fctId = BAP_InterTelegramTimerMappingTable[au16InterTelegramIndex].fctId;
            DBGVAR lsgId_t lsgId = BAP_InterTelegramTimerMappingTable[au16InterTelegramIndex].lsgId;

            BAP_DBG_IntertelegramTmoutErr(lsgId);

            /* Melde Fehler an Applikation */
            BAP_BCL_ErrorIndication(lsgId, fctId, BapErr_TimeoutSegmentation);
        }
        BAP_bInterTelegramTimerRunning = BAP_TRUE;
    }
}
#endif  /* #ifdef BAP_USES_SEGMENTATION */


/* Definition (Implementierung) von globalen Funktionen */


/*  Diese Funktion ist in bap_bclutil.h dokumentiert */
BAP_IMPL_FAR void
BAP_BCL_InhibitTimerTask(void)
{
    DBGVAR uint16_t u16InhibitIndex;
    DBGVAR uint16_t *pu16InhibitTimer;

    /* Dekrementiere alle InhibitTimer um je '1' pro Funktionsaufruf */
    for(u16InhibitIndex = (uint16_t)0; u16InhibitIndex < BAP_INHIBIT_ROWS; u16InhibitIndex++)
    {
        pu16InhibitTimer = &BAP_InhibitRamTable[u16InhibitIndex].u16InhibitTimer;
        if( (uint16_t) 0u < *pu16InhibitTimer)
        {
            (*pu16InhibitTimer)--;
        }
    }
    return;
}


#ifdef BAP_USES_SEGMENTATION
/*  Diese Funktion ist in bap_bclutil.h dokumentiert */
BAP_IMPL_FAR void
BAP_BCL_InterTelegramTimerTask(void)
{
    DBGVAR uint16_t u16InterTelegramIndex;

    /* Dekrementiere alle InterTelegramTimer um je '1' pro Funktionsaufruf */
    if (BAP_FALSE != BAP_bInterTelegramTimerRunning)
    {
        BAP_bInterTelegramTimerRunning = BAP_FALSE;

        /*lint -e681 Meldung "Schleife wird nicht durchlaufen" moeglich, wenn nichts Segmentiertes empfangen wird */
        for(u16InterTelegramIndex = BAP_INTER_TELEGRAM_TIMER_ROWS;
            u16InterTelegramIndex > (uint16_t) 0u;
            u16InterTelegramIndex--)
        {
            BAP_BCL_HdlInterTelegramTimer(u16InterTelegramIndex);
        }
        /*lint +e681 */
    }
    return;
}
#endif /* BAP_USES_SEGMENTATION */


/*  Diese Funktion ist in bap_bclutil.h dokumentiert */
BAP_IMPL_FAR void
BAP_BCL_InitLsgRamAreas(BapLsgRomRow_pot apoLsgRomRow)
{
#if defined(BAP_USES_CAN) || defined(BAP_USES_FR) || defined(BAP_USES_PDUR) || defined(BAP_USES_ETH)
    BapCanTxRomRow_pot poCanTxRomRow;
    BapCanRxRomRow_pot poCanRxRomRow;
    DBGVAR uint16_t i;
    DBGVAR uint16_t currentIdx;
    DBGVAR lsgId_t lsgId;

    /*lint -esym(613,apoLsgRomRow) */
    BAP_ASSERT(NULL != apoLsgRomRow);

    lsgId = apoLsgRomRow->lsgId;

    /* Initialisierung der CAN Tx RAM Bereiche */
    for (i=(uint8_t)0; i<BAP_CAN_TX_ROM_TABLE_ROWS; i++)
    {
        poCanTxRomRow = &BAP_CanTxRomTable[i];
        if(poCanTxRomRow->poFctRomRow->lsgId == lsgId)
        {
            BAP_BCL_InitTxRamValues(poCanTxRomRow);
        }
    }

    /* Initialisierung der CAN Rx RAM Bereiche */

    /* Bug in PC-Lint 8.0 laesst sonst naechste Zeile auflisten, da apoLsgRomRow abgeschaltet */
    /*lint -e613 */
    currentIdx = apoLsgRomRow->u16CanRxRomTableIndex;
    if(BAP_MAX_UINT16 != currentIdx)
    {
		for (i=(uint8_t)0; i<apoLsgRomRow->u16CanRxRomTableSize; i++)
		{
			poCanRxRomRow = &BAP_CanRxRomTable[currentIdx+i];
			BAP_BCL_InitRxRamValues(poCanRxRomRow);
		}
    }
    /*lint +e613 */
#endif /* BAP_USES_CAN || BAP_USES_FR ||BAP_USES_PDUR || defined(BAP_USES_ETH) */
    return;
}

#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>
/* CallBack-Funktionen */
