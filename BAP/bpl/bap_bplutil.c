/******************************************************************
 *
 *     Copyright (c) 2004-2023 Volkswagen AG, D-38436 Wolfsburg
 *
 ******************************************************************
 *
 * Projekt:    BAP
 * Komponente: BPL
 * BAP Version: 1.12.2
 *
 ******************************************************************
 *
 * Beschreibung
 *
 *  Diese Datei enthaelt Hilfsfunktionen fuer die Schicht im BPL
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
 * 2017-03-03	1.9.0       FST         [SSWCCB-1545] SSW-Lokatierungs-Pragmas eingefuegt
 * 2013-03-05	1.7.0       WWU         Misra-2004 Fix
 * 2012-10-15	1.6.5.1     WWU         Korrektur der Misra-98 Abweichungen
 * 2006-04-12   1.4         ALA         Fix fuer Cosmic HCS12 Problem mit FAR-Pointern
 * 2006-04-12   1.4         ALA         Unterstuetzung fuer HB-Trigger.
 * 2006-04-12   1.4         ALA         Unterstuetzung fuer BAP_ROM_DATA_FAR.
 * 2005-04-13   1.3         ALA         Optimierung der Datenstrukturen
 * 2005-03-30   1.3         CRI         Bei der Bestimmung des naechsten HBs in SetNextFctIndex
 *                                      wird zukuenftig die aktuelle Funkctionlist einbezogen
 * 2004-11-17   1.2         JOK         Diverse Zeiger als const deklariert
 * 2004-06-07   1.1         JOK         Laufzeitoptimierung in BAP_BPL_SetNextFctIndex() 
 *                                      durch ersetzen der aLsgId durch den Zeiger apoLsgRomRow
 *                                      in die LSG-Tabelle
 ******************************************************************/


/* Systemincludes mit <...> */

/* Bibliotheken von externen Herstellen mit <...> */

/* Eigene Header-Dateien "..." */
#include "bap_balconfig.h"      
#include "bap_bplconfig.h"
#include "bap_bplutil.h"
#include "bap_util.h"
#include "bap_debug.h"

/* Externe globale Variablen-Definitionen */

/* Interne Makro-Definitionen */

/* Interne Typ-Definitionen */

/* Interne Const Deklarationen */

/* Interne statische Variablen */

/* Vorwaerts-Deklarationen von statischen Funktionen */

/* Definition (Implementierung) von statischen Funktionen */

/* Definition (Implementierung) von globalen Funktionen */

#ifdef BAP_FSG
/* Diese Funktion ist in bap_bplutil.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_BPL_SetNextFctIndex(BapLsgRomRow_pot apoLsgRomRow)
{
    DBGVAR uint8_t i;
    DBGVAR bool_t isNxtFctFound = BAP_FALSE;

    /*lint -esym(613,apoLsgRomRow)*/
    BAP_ASSERT(NULL != apoLsgRomRow);

    i = apoLsgRomRow->poLsgRamRow->u8LastSentFctIndex;
    for (;isNxtFctFound == BAP_FALSE;)
    {
        i++;
        /* bis zum Ende, und fange vom Anfang an */
        if(i == apoLsgRomRow->u8FctRomTableSize)
        {
            i=(uint8_t)0;
            BAP_DBG_HeartbeatLoopEvent(apoLsgRomRow->lsgId);
        }

        if( /* Wenn Heartbeat angechaltet ist, */
        	(BAP_TRUE == BAP_FctRomTables[apoLsgRomRow->u16FctRomIndex + i].bHeartbeatOn)
        	/* UND die Funktion in FctList angeschaltet ist.*/
            && ((uint8_t)0 != (apoLsgRomRow->poLsgRamRow->BAP_aru8FunctionList[BAP_BINARY_ID(BAP_FctRomTables[apoLsgRomRow->u16FctRomIndex + i].fctId) / BAP_BYTE] & (BAP_BIT7 >> (BAP_BINARY_ID(BAP_FctRomTables[apoLsgRomRow->u16FctRomIndex + i].fctId) % BAP_BYTE)) ) )
            ) 
        {
        	/* DANN Setze naechste Send-Funktion */
            apoLsgRomRow->poLsgRamRow->u8LastSentFctIndex=i;
            isNxtFctFound = BAP_TRUE;
        }
    }
    return;
    /*lint +esym(613,apoLsgRomRow)*/
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* #ifdef BAP_FSG */


#if defined(BAP_USES_METHODS) || defined(BAP_ASG)
/* Diese Funktion ist in bap_bplutil.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void 
BAP_BPL_StopRetries (BapLsgRomRow_pot apoLsgRomRow)
{
    DBGVAR uint8_t i;
    BapBplRamRow_pot poBplRamRow;

    /*lint -esym(613,apoLsgRomRow)*/
    BAP_ASSERT(NULL != apoLsgRomRow);

    /* Schleife ueber die gesamte Retry-Tabelle und alle Retries ausschalten */
    for(i=apoLsgRomRow->u8FctRomTableSize;i>(uint8_t)0;i--)
    {
        poBplRamRow = BAP_FctRomTables[apoLsgRomRow->u16FctRomIndex + (uint16_t)(i - (uint16_t)1)].poBplRamRow;
        if(poBplRamRow != NULL)
        {
            poBplRamRow->fRetryOrProcessingFlags.u6RetryCounter = (uint8_t)0;
            poBplRamRow->fRetryOrProcessingFlags.bRetryOrProcessingActive = BAP_FALSE;
            poBplRamRow->u16RetryOrProcessingTimer  = (uint16_t)0;
            BAP_DBG_RetryStoppedEvent(apoLsgRomRow->lsgId);
        }
    }

    /*lint +esym(613,apoLsgRomRow)*/
    return;
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* #if defined(BAP_USES_METHODS) || defined(BAP_ASG) */


/* Diese Funktion ist in bap_bplutil.h dokumentiert */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_BPL_RetriggerHeartbeat(BapLsgRomRow_pot apoLsgRomRow)
{
    if (NULL != apoLsgRomRow)
    {
        apoLsgRomRow->poLsgRamRow->u16HeartbeatTimer = *(apoLsgRomRow->pu16HeartbeatTimer);
    }
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


/* Diese Funktion ist in bap_bplutil.h dokumentiert */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_BPL_InitializeHeartbeat(BapLsgRomRow_pot apoLsgRomRow, uint8_t au8HeartbeatTime) 
{
    uint16_t u16HeartbeatMs;
    uint8_t  u8TaskTimeMs;
    uint16_t u16HeartbeatTasks;

    if (NULL != apoLsgRomRow) 
    {      
        u16HeartbeatMs = (uint16_t)( (uint16_t)apoLsgRomRow->u8Heartbeat * BAP_HEARTBEAT_FREQUENCY_MS);
        u8TaskTimeMs =  apoLsgRomRow->u8TaskTimeMs; 
        u16HeartbeatTasks = (uint16_t) ((uint16_t) au8HeartbeatTime * (u16HeartbeatMs / (uint16_t) u8TaskTimeMs));
        *(apoLsgRomRow->pu16HeartbeatTimer) = u16HeartbeatTasks;  
        apoLsgRomRow->poLsgRamRow->u16HeartbeatTimer = *(apoLsgRomRow->pu16HeartbeatTimer);
    }
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>
