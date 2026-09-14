/******************************************************************
 *
 *     Copyright (c) 2004-2023 Volkswagen AG, D-38436 Wolfsburg
 *
 ******************************************************************
 *
 * Projekt:    BAP
 * Komponente: Debug
 * BAP Version: 1.12.2
 *
 ******************************************************************
 *
 * Beschreibung
 *
 *  Diese Datei enthaelt die Implementierung der Debug/Diagnose-
 *  Komponente im BAP-Projekt.
 *
 *  Diese C-Datei enthaelt nicht die Funktionen, welche die
 *  Anbindung an die Kommunikationschicht vornehmen.
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
 * 2022-07-26   1.12.0      DRH         [SSWPPB-292] LsgId check made conditionally in BAP_DBG_SetDebugLsgId
 * 2022-06-17	1.12.0		DRH			[SSWPPB-269] Release preparation, adapt Copyright date and version number.
 * 2022-04-21	1.12.0		JEO			[SSWPPB-273] Fix BAL debug message construction for LSG-ID>63.
 * 2021-12-10	1.11.3		JEO			[SSWPPB-244] Release preparation, fix MISRA violations.
 * 2021-12-07	1.11.3		JEO			[SSWPPB-244] Release preparation, adapt Copyright date and version number.
 * 2021-06-09   1.11.3      JEO         [SSWPPB-209] Add ASR interface to enable/disable sending of debug informations.
 * 2021-03-08   1.11.3      DRH         [SSWPPB-142] Replaced magic numbers by constants
 * 2021-03-01	1.11.3		JEO			[SSWPPB-142] Improve jutification of Pc-Lint deac or MISRA rules violation.
 * 2018-07-31   1.10.2      PPE         [SSWCCB-2620] Bugfix DebugMacro
 * 2018-07-19	1.10.3      FFS         [SSWCCB-2522] Misra-2012 fix (release was postponed)
 * 2017-03-06	1.9.0       FST         [SSWCCB-1545] SSW-Lokatierungs-Pragmas eingefuegt
 * 2016-10-25	1.8.1       FST         [SSWCCB-2410] Softwareschalter DLL_COMPILATION zur Unterscheidung
 *                                      der Erzeugung von Steuergeraete-Code und der BAP-Dll eingefuegt
 * 2016-10-24	1.8.1       FST         [SSWCCB-2392] Debugmode erweitern für neue LSG-IDs,
 *                                      fuer LSG-ID > hat sich die Struktur der BAP-Boschaften geandert
 * 2014-03-25	1.7.1       WWU         Misra-2004 fix: Function-like Macros.
 * 2013-04-17	1.7.0       FST         Get+Set-Funktionen fuer Bap_gDebugLsgId erstellt fuer debug-Zugriff
 * 2013-02-06	1.7.0       WWU         Funktionsname Umbenannt, wegen Misra : Identifier exceeds 31 characters,
 *                                      bugfix in BAP_ProcessDebugControl
 * 2012-10-15	1.6.5.1     WWU         Korrektur der Misra-98 Abweichungen
 * 2012-02-02   1.6.3       NQU         Lint Warnung wegen Enum->Int Cast behoben
 * 2007-09-03   1.5         ALI         BAP_DBG_SetBalState um Zustand InvalidConfig erweitert
 * 2007-08-22   1.5         SHU         Aenderung der BAP-Debug-Botschaften mit Byte0+1 als BAP-Header
 * 2006-04-12   1.4         ALA         Unterstuetzung fuer BAP_ROM_DATA_FAR.
 * 2005-04-20   1.3         ALA         Funktion BAP_DBG_SetBplState entfernt, da gemeinsamer Zustand fuer alle Schichten.
 * 2005-04-06   1.3         ALA         Funktion BAP_DBG_RequestTimeoutError() und BAP_DBG_DataLostError() eingebaut
 * 2004-11-17   1.2         JOK         Funktion BAP_DBG_GetAllMessageCorruptedError() eingebaut
 * 2004-06-07   1.1         JOK         Compilerschalter fuer SG-Typen zur Optimierung
 *                                      des ROM-Bedarfs eingefuegt
 * 2004-06-07   1.1         JOK         Funktion BAP_DBG_SetBclState() entfernt
 ******************************************************************/


/* Systemincludes mit <...> */

/* Bibliotheken von externen Herstellen mit <...> */

/* Eigene Header-Dateien "..." */
#include "bap_debug.h"
#include "bap_util.h"
#include "bap_balconfig.h"
#include "bap_bplconfig.h"
#include "bap_bclconfig.h"

/* Externe globale Variablen-Definitionen */

/* Interne Makro-Definitionen */

/* Interne Typ-Definitionen */

/* Interne Const Deklarationen */

/* Interne statische Variablen */

#if defined(BAP_DBG_PER_LSG) || defined(BAP_DBG_ON_OFF)
/**
 *  Speichert, fuer welche Lsg gerade Debug-Betrieb aktiv ist.
 */
#	ifndef DLL_COMPILATION
#       define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#       include <BAP_MemMap.h>
/*lint -e9034*/ /* MISRA_2012_REQ_10.3 : PC-Lint 9.00L throws a warning due to Tool bug. Hence, this warning has been deactivated.
     	 	 	 * Documented with a mail from the Lint team in the SSWCCB-2522_BAP-Entwicklung auf MISRA2012 umstellen folder
     	 	 	 * no risk arise because 0 fit in enum */
static DBGVAR lsgId_t Bap_gDebugLsgId = (lsgId_t)0;
/*lint +e9034*/
#       define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#       include <BAP_MemMap.h>
#	endif /* DLL_COMPILATION */
#	ifndef DLL_COMPILATION
#       define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#       include <BAP_MemMap.h>
/*lint -e9075*/ /* MISRA_2012_REQ_8.4 : PC-Lint 9.00L throws a warning as it takes BAP_SendDebugInfo_Active for a symbol. It is not
 	 	 	 	 * a symbol but a variable. Hence the warning is not justified. */
DBGVAR bool_t BAP_SendDebugInfo_Active = BAP_TRUE;
/*lint +e9075*/
#       define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#       include <BAP_MemMap.h>
#	endif /* DLL_COMPILATION */
#endif /* defined(BAP_DBG_PER_LSG) || defined(BAP_DBG_ON_OFF) */

#if defined(BAP_DBG_PER_LSG) || defined(BAP_DBG_ON_OFF)
/**
 *  Speichert die aktuelle Debug-Information.
 */
#	ifndef DLL_COMPILATION
#       define BAP_START_SEC_VAR_NO_INIT_8
#       include <BAP_MemMap.h>
DBGVAR uint8_t BAP_DBG_DebugInfoTable[BAP_DBG_INFO_TABLE_SIZE];
#       define BAP_STOP_SEC_VAR_NO_INIT_8
#       include <BAP_MemMap.h>
#	endif /* DLL_COMPILATION */
#endif /* defined(BAP_DBG_PER_LSG) || defined(BAP_DBG_ON_OFF) */

/* Vorwaerts-Deklarationen von statischen Funktionen */

/* Definition von statischen Funktionen */

/* Definition von global sichtbaren Funktionen */

/**************************************************/
/*         Debug-Flags der BAL-Schicht            */
/**************************************************/

#if defined (BAP_DBG_PER_LSG) || defined (BAP_DBG_ON_OFF)
/* Diese Funktion ist in bap_debug.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_DBG_SetBalState(lsgId_t aLsgId
    , BapLayerLsgStatus_et aeState)
{
#   ifdef BAP_DBG_PER_LSG
    if (aLsgId == Bap_gDebugLsgId)
    {
#   endif /*BAP_DBG_PER_LSG*/
        if ((lsgId_t)Bap_gDebugLsgId <= (lsgId_t)BAP_MAX_LSG_ID) /* MISRA_2012_REQ_10.5 : no risk arise because 64 fit in enum. could be a 64u */
        {
            /* Byte 1, Bit 2^6 und 2^7 */
            BAP_DBG_DebugInfoTable[2] &= BAP_BITMASK_00111111;  /* loeschen, weil kein Ereignis */
            BAP_DBG_DebugInfoTable[2] |= (uint8_t)(((uint8_t)aeState) << (uint8_t)6);
        }
        else
        {
            /* Byte 1, Bit 2^2 und 2^3 */ /*[FST] 2016-08-22 [SSWCCB-2392]*/
            BAP_DBG_DebugInfoTable[2] &= BAP_BITMASK_11110001;  /* loeschen, weil kein Ereignis */
            BAP_DBG_DebugInfoTable[2] |= (uint8_t)(((uint8_t)aeState) << (uint8_t)2);
        }
#   ifdef BAP_DBG_PER_LSG
    }
#   elif defined (BAP_DBG_ON_OFF)
    /* aLsgId hat keine Funktion im FSG */
    (void)aLsgId;
#   endif /*BAP_DBG_PER_LSG || BAP_DBG_ON_OFF*/
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_DBG_PER_LSG || BAP_DBG_ON_OFF */

#if defined (BAP_DBG_PER_LSG) || defined (BAP_DBG_ON_OFF)
/* Diese Funktion ist in bap_debug.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_DBG_SetCacheValidState(lsgId_t aLsgId
    , bool_t abValid)
{
#   ifdef BAP_DBG_PER_LSG
    if (aLsgId == Bap_gDebugLsgId)
    {
#   endif /*BAP_DBG_PER_LSG*/
        if ((lsgId_t)Bap_gDebugLsgId <= (lsgId_t)BAP_MAX_LSG_ID) /* MISRA_2012_REQ_10.5 : no risk arise because 64 fit in enum. could be a 64u */
        {
            /* Byte 1, Bit 2^5 */
            BAP_DBG_DebugInfoTable[2] &= BAP_BITMASK_11011111;  /* loeschen, weil kein Ereignis */
            BAP_DBG_DebugInfoTable[2] |= (abValid & (uint8_t)1) << (uint8_t)5;
        }
        else
        {
            /* Byte 1, Bit 2^1 */ /*[FST] 2016-08-22 [SSWCCB-2392]*/
            BAP_DBG_DebugInfoTable[2] &= BAP_BITMASK_11111101;  /* loeschen, weil kein Ereignis */
            BAP_DBG_DebugInfoTable[2] |= (abValid & (uint8_t)1) << (uint8_t)1;
        }
#   ifdef BAP_DBG_PER_LSG
    }
#   elif defined (BAP_DBG_ON_OFF)
    /* aLsgId hat keine Funktion im FSG */
    (void)aLsgId;
#   endif /*BAP_DBG_PER_LSG || BAP_DBG_ON_OFF*/
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /*BAP_DBG_PER_LSG || BAP_DBG_ON_OFF*/

#ifdef BAP_DBG_PER_LSG
/* Diese Funktion ist in bap_debug.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_DBG_GetAllMsgCorruptedErr(lsgId_t aLsgId)
{
    if (aLsgId == Bap_gDebugLsgId)
    {
        /* Byte 1, Bit 2^0 */
        BAP_DBG_DebugInfoTable[2] |= BAP_BIT0;
    }
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_DBG_PER_LSG */

#ifdef BAP_DBG_PER_LSG
/* Diese Funktion ist in bap_debug.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_DBG_InvalidStateError(lsgId_t aLsgId)
{
    if (Bap_gDebugLsgId == aLsgId)
    {
        /* Byte 2, Bit 2^7 */
        BAP_DBG_DebugInfoTable[3] |= BAP_BIT7;
    }
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_DBG_PER_LSG */

#ifdef BAP_DBG_PER_LSG
/* Diese Funktion ist in bap_debug.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_DBG_CacheInvalidError(lsgId_t aLsgId)
{
    if (aLsgId == Bap_gDebugLsgId)
    {
        /* Byte 2, Bit 2^6 */
        BAP_DBG_DebugInfoTable[3] |= BAP_BIT6;
    }
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_DBG_PER_LSG */

#ifdef BAP_DBG_PER_LSG
/* Diese Funktion ist in bap_debug.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_DBG_CacheNotAvailableError(lsgId_t aLsgId)
{
    if (aLsgId == Bap_gDebugLsgId)
    {
        /* Byte 2, Bit 2^5 */
        BAP_DBG_DebugInfoTable[3] |= BAP_BIT5;
    }
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_DBG_PER_LSG */

#ifdef BAP_DBG_PER_LSG
/* Diese Funktion ist in bap_debug.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_DBG_InvalidArgError(lsgId_t aLsgId)
{
    if (aLsgId == Bap_gDebugLsgId)
    {
        /* Byte 2, Bit 2^4 */
        BAP_DBG_DebugInfoTable[3] |= BAP_BIT4;
    }
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_DBG_PER_LSG */

#ifdef BAP_DBG_PER_LSG
/* Diese Funktion ist in bap_debug.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_DBG_ProtocolVersionError(lsgId_t aLsgId)
{
    if (aLsgId == Bap_gDebugLsgId)
    {
        /* Byte 2, Bit 2^3 */
        BAP_DBG_DebugInfoTable[3] |= BAP_BIT3;
    }
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_DBG_PER_LSG */

#ifdef BAP_DBG_PER_LSG
/* Diese Funktion ist in bap_debug.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_DBG_DataDefinitionError(lsgId_t aLsgId)
{
    if (aLsgId == Bap_gDebugLsgId)
    {
        /* Byte 2, Bit 2^2 */
        BAP_DBG_DebugInfoTable[3] |= BAP_BIT2;
    }
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_DBG_PER_LSG */

#ifdef BAP_FSG
#   ifdef BAP_DBG_PER_LSG
/* Diese Funktion ist in bap_debug.h dokumentiert */
#       define BAP_START_SEC_CODE_FAST
#       include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_DBG_GetAllEvent(lsgId_t aLsgId)
{
    if (aLsgId == Bap_gDebugLsgId)
    {
        /* Byte 2, Bit 2^1 */
        BAP_DBG_DebugInfoTable[3] |= BAP_BIT1;
    }
}
#       define BAP_STOP_SEC_CODE_FAST
#       include <BAP_MemMap.h>
#   endif /* BAP_DBG_PER_LSG */
#endif /* BAP_FSG */

#if defined(BAP_DBG_PER_LSG)
/* Diese Funktion ist in bap_debug.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_DBG_IncomingMessageEvent(lsgId_t aLsgId,
                             fctId_t aFctId,
                             BapOpCodes_et aeOpCode)
{
    if (aLsgId == Bap_gDebugLsgId)
    {
        /*Loeschen des BAP-Headers*/
        BAP_DBG_DebugInfoTable[0] = (uint8_t)0;
        BAP_DBG_DebugInfoTable[1] = (uint8_t)0;

        /* Byte 3, Bit 2^0 */
        BAP_DBG_DebugInfoTable[3] |= BAP_BIT0;

        /* BAP-Header fuer unsegmentierte Botschaft
                     Byte0         Byte1
                OpCode   LSG-ID    FCT-ID
               0  000   XXXX | XX  000000 | */
        /* Neuer BAP-Header fuer Debug-Botschaft
         * 	Byte0 = LSG-ID; Byte1 = Fct-ID; OpCode = Bit 4-6 von Byte2
         */

        /*OpCode*/
        if((lsgId_t)Bap_gDebugLsgId <= (lsgId_t)BAP_MAX_LSG_ID) /* MISRA_2012_REQ_10.5 : no risk arise because 64 fit in enum. could be a 64u */
        {
            BAP_DBG_DebugInfoTable[0] |= ((uint8_t)aeOpCode & BAP_BITMASK_00000111) << (uint8_t)4;
        }
        else
        {
            BAP_DBG_DebugInfoTable[2] |= ((uint8_t)aeOpCode & BAP_BITMASK_00000111) << (uint8_t)4; /*[FST] 2016-08-23 [SSWCCB-2392]*/
        }
        /*LSG-ID*/
        if((lsgId_t)Bap_gDebugLsgId <= (lsgId_t)BAP_MAX_LSG_ID) /* MISRA_2012_REQ_10.5 : no risk arise because 64 fit in enum. could be a 64u */
        {
            BAP_DBG_DebugInfoTable[0] |= (uint8_t)(((uint8_t)aLsgId & BAP_BITMASK_00111100) >> (uint8_t)2);
            BAP_DBG_DebugInfoTable[1] = (uint8_t)(((uint8_t)aLsgId & BAP_BITMASK_00111100) << (uint8_t)6);
        }
        else
        {   
            BAP_DBG_DebugInfoTable[0] |= (uint8_t)aLsgId;									/*[FST] 2016-08-23 [SSWCCB-2392]*/
        }
        /*FCT-ID*/
        if((lsgId_t)Bap_gDebugLsgId <= (lsgId_t)BAP_MAX_LSG_ID) /* MISRA_2012_REQ_10.5 : no risk arise because 64 fit in enum. could be a 64u */
        {
            BAP_DBG_DebugInfoTable[1] |= ((uint8_t)aFctId & BAP_BITMASK_00111111);
        }
        else
        {
            BAP_DBG_DebugInfoTable[1] |= (uint8_t)aFctId;									/*[FST] 2016-08-23 [SSWCCB-2392]*/
        }
    }
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#elif defined(BAP_DBG_ON_OFF)
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_DBG_IncomingMessageEvent(lsgId_t aLsgId,
                             fctId_t aFctId,
                             BapOpCodes_et aeOpCode)
{
    if((lsgId_t)Bap_gDebugLsgId <= (lsgId_t)BAP_MAX_LSG_ID)
    {
        BAP_DBG_DebugInfoTable[0] |= ((uint8_t)(aeOpCode) & BAP_BITMASK_00000111) << (uint8_t)4;
        BAP_DBG_DebugInfoTable[1] |= ((uint8_t)(aFctId) & BAP_BITMASK_00111111);
    }
    else
    {
        BAP_DBG_DebugInfoTable[2] |= ((uint8_t)(aeOpCode) & BAP_BITMASK_00000111) << (uint8_t)4; /*[FST] 2016-08-23 [SSWCCB-2392]*/
        BAP_DBG_DebugInfoTable[1] |= (uint8_t)aFctId;
    }
    BAP_DBG_DebugInfoTable[3] |= (uint8_t)0x01u;
    (void)aLsgId;
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* #if defined(BAP_DBG_PER_LSG) || defined(BAP_DBG_ON_OFF) */

/**************************************************/
/*         Debug-Flags der BPL-Schicht            */
/**************************************************/

#if defined (BAP_DBG_PER_LSG) || defined (BAP_DBG_ON_OFF)
/* Diese Funktion ist in bap_debug.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_DBG_SetHeartbeatState(lsgId_t aLsgId
    , bool_t bHeartbeatOn)
{
#   ifdef BAP_DBG_PER_LSG
    if (aLsgId == Bap_gDebugLsgId)
    {
#   endif /*BAP_DBG_PER_LSG*/
        if((lsgId_t)Bap_gDebugLsgId <= (lsgId_t)BAP_MAX_LSG_ID) /* MISRA_2012_REQ_10.5 : no risk arise because 64 fit in enum. could be a 64u */
        {
            /* Byte 3, Bit 2^5 */
            BAP_DBG_DebugInfoTable[4] &= BAP_BITMASK_11011111;  /* loeschen, weil kein Ereignis */
            BAP_DBG_DebugInfoTable[4] |= (bHeartbeatOn & BAP_BIT0) << (uint8_t)5;
        }
        else
        {
            /* Byte 3, Bit 2^3 */ /*[FST] 2016-08-22 [SSWCCB-2392]*/
            BAP_DBG_DebugInfoTable[4] &= BAP_BITMASK_11110111;  /* loeschen, weil kein Ereignis */
            BAP_DBG_DebugInfoTable[4] |= (bHeartbeatOn & BAP_BIT0) << (uint8_t)3;
        }
#   ifdef BAP_DBG_PER_LSG
    }
#   elif defined (BAP_DBG_ON_OFF)
    /* aLsgId hat keine Funktion im FSG */
    (void)aLsgId;
#   endif /*BAP_DBG_PER_LSG || BAP_DBG_ON_OFF*/
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /*BAP_DBG_PER_LSG || BAP_DBG_ON_OFF*/

/* Test*/

#ifdef BAP_ASG
#ifdef BAP_DBG_PER_LSG
/* Diese Funktion ist in bap_debug.h dokumentiert */
#       define BAP_START_SEC_CODE_FAST
#       include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_DBG_RequestTimeoutError(lsgId_t aLsgId)
{
    if (aLsgId == Bap_gDebugLsgId)
    {
        /* Byte 3, Bit 2^2 */
        BAP_DBG_DebugInfoTable[4] |= BAP_BIT2;
    }
}
#       define BAP_STOP_SEC_CODE_FAST
#       include <BAP_MemMap.h>
#endif /* BAP_DBG_PER_LSG */
#endif /* BAP_ASG */

#ifdef BAP_DBG_PER_LSG
/* Diese Funktion ist in bap_debug.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_DBG_RetryTimeoutError(lsgId_t aLsgId)
{
    if (aLsgId == Bap_gDebugLsgId)
    {
        /* Byte 3, Bit 2^1 */
        BAP_DBG_DebugInfoTable[4] |= BAP_BIT1;
    }
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_DBG_PER_LSG */

#ifdef BAP_FSG
#ifdef BAP_DBG_PER_LSG
/* Diese Funktion ist in bap_debug.h dokumentiert */
#       define BAP_START_SEC_CODE_FAST
#       include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_DBG_HeartbeatLoopEvent(lsgId_t aLsgId)
{
    if (aLsgId == Bap_gDebugLsgId)
    {
        /* Byte 3, Bit 2^0 */
        BAP_DBG_DebugInfoTable[4] |= BAP_BIT0;
    }
}
#       define BAP_STOP_SEC_CODE_FAST
#       include <BAP_MemMap.h>
#endif /* BAP_DBG_PER_LSG */
#endif /* BAP_FSG */

#ifdef BAP_DBG_PER_LSG
/* Diese Funktion ist in bap_debug.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_DBG_HeartbeatProcessedEvent(lsgId_t aLsgId)
{
    if (aLsgId == Bap_gDebugLsgId)
    {
        /* Byte 4, Bit 2^7 */
        BAP_DBG_DebugInfoTable[5] |= BAP_BIT7;
    }
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_DBG_PER_LSG */

#ifdef BAP_DBG_PER_LSG
/* Diese Funktion ist in bap_debug.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_DBG_HeartbeatTimeoutError(lsgId_t aLsgId)
{
    if (aLsgId == Bap_gDebugLsgId)
    {
        /* Byte 4, Bit 2^6 */
        BAP_DBG_DebugInfoTable[5] |= BAP_BIT6;
    }
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_DBG_PER_LSG */

#ifdef BAP_DBG_PER_LSG
/* Diese Funktion ist in bap_debug.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_DBG_RetryMntStartedEvent(lsgId_t aLsgId)
{
    if (aLsgId == Bap_gDebugLsgId)
    {
        /* Byte 4, Bit 2^5 */
        BAP_DBG_DebugInfoTable[5] |= BAP_BIT5;
    }
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_DBG_PER_LSG */

#ifdef BAP_DBG_PER_LSG
/* Diese Funktion ist in bap_debug.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_DBG_RetryProvokedEvent(lsgId_t aLsgId)
{
    if (aLsgId == Bap_gDebugLsgId)
    {
        /* Byte 4, Bit 2^4 */
        BAP_DBG_DebugInfoTable[5] |= BAP_BIT4;
    }
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_DBG_PER_LSG */

#ifdef BAP_DBG_PER_LSG
/* Diese Funktion ist in bap_debug.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_DBG_RetryAnsweredEvent(lsgId_t aLsgId)
{
    if (aLsgId == Bap_gDebugLsgId)
    {
        /* Byte 4, Bit 2^3 */
        BAP_DBG_DebugInfoTable[5] |= BAP_BIT3;
    }
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_DBG_PER_LSG */

#ifdef BAP_DBG_PER_LSG
/* Diese Funktion ist in bap_debug.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_DBG_RetryRetriggeredEvent(lsgId_t aLsgId)
{
    if (aLsgId == Bap_gDebugLsgId)
    {
        /* Byte 4, Bit 2^2 */
        BAP_DBG_DebugInfoTable[5] |= BAP_BIT2;
    }
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_DBG_PER_LSG */

#ifdef BAP_DBG_PER_LSG
/* Diese Funktion ist in bap_debug.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_DBG_RetryStoppedEvent(lsgId_t aLsgId)
{
    if (aLsgId == Bap_gDebugLsgId)
    {
        /* Byte 4, Bit 2^1 */
        BAP_DBG_DebugInfoTable[5] |= BAP_BIT1;
    }
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_DBG_PER_LSG */

#ifdef BAP_DBG_PER_LSG
/* Diese Funktion ist in bap_debug.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_DBG_RetryBusyError(lsgId_t aLsgId)
{
    if (aLsgId == Bap_gDebugLsgId)
    {
        /* Byte 4, Bit 2^0 */
        BAP_DBG_DebugInfoTable[5] |= BAP_BIT0;
    }
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_DBG_PER_LSG */


/**************************************************/
/*         Debug-Flags der BPL-Schicht            */
/**************************************************/

#ifdef BAP_DBG_PER_LSG
/* Diese Funktion ist in bap_debug.h dokumentiert
 *
 * Diese Funktion hat 6 ControlNestingLayers (max.4)*/
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_DBG_TaskTimeLimitEvent(void)
{
    if ((lsgId_t)0  != (lsgId_t)Bap_gDebugLsgId) /* MISRA_2012_REQ_10.5 : no risk arise because 0 fit in enum. could be a 0u */
    {
        /* Byte 5, Bit 2^4 */
        BAP_DBG_DebugInfoTable[6] |= BAP_BIT4;
    }
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_DBG_PER_LSG */

#ifdef BAP_DBG_PER_LSG
/* Diese Funktion ist in bap_debug.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_DBG_BadDataLengthError(lsgId_t aLsgId)
{
    if (aLsgId == Bap_gDebugLsgId)
    {
        /* Byte 5, Bit 2^3 */
        BAP_DBG_DebugInfoTable[6] |= BAP_BIT3;
    }
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_DBG_PER_LSG */

#ifdef BAP_DBG_PER_LSG
/* Diese Funktion ist in bap_debug.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_DBG_DataLostError(void)
{
    if ((lsgId_t)0  != (lsgId_t)Bap_gDebugLsgId) /* MISRA_2012_REQ_10.5 : no risk arise because 0 fit in enum. could be a 0u */
    {
        /* Byte 5, Bit 2^2 */
        BAP_DBG_DebugInfoTable[6] |= BAP_BIT2;
    }
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_DBG_PER_LSG */

#ifdef BAP_DBG_PER_LSG
/* Diese Funktion ist in bap_debug.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_DBG_TxStartMsgEvent(lsgId_t aLsgId)
{
    if (aLsgId == Bap_gDebugLsgId)
    {
        /* Byte 5, Bit 2^1 */
        BAP_DBG_DebugInfoTable[6] |= BAP_BIT1;
    }
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_DBG_PER_LSG */

#ifdef BAP_DBG_PER_LSG
/* Diese Funktion ist in bap_debug.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_DBG_RxStartMsgEvent(lsgId_t aLsgId)
{
    if (aLsgId == Bap_gDebugLsgId)
    {
        /* Byte 5, Bit 2^0 */
        BAP_DBG_DebugInfoTable[6] |= BAP_BIT0;
    }
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_DBG_PER_LSG */

#ifdef BAP_DBG_PER_LSG
/* Diese Funktion ist in bap_debug.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_DBG_TxSegMsgCompleteEvent(lsgId_t aLsgId)
{
    if (aLsgId == Bap_gDebugLsgId)
    {
        /* Byte 6, Bit 2^7 */
        BAP_DBG_DebugInfoTable[7] |= BAP_BIT7;
    }
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_DBG_PER_LSG */

#ifdef BAP_DBG_PER_LSG
/* Diese Funktion ist in bap_debug.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_DBG_RxSegMsgCompleteEvent(lsgId_t aLsgId)
{
    if (aLsgId == Bap_gDebugLsgId)
    {
        /* Byte 6, Bit 2^6 */
        BAP_DBG_DebugInfoTable[7] |= BAP_BIT6;
    }
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_DBG_PER_LSG */

#ifdef BAP_DBG_PER_LSG
/* Diese Funktion ist in bap_debug.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_DBG_IntertelegramTmoutErr(lsgId_t aLsgId)
{
    if (aLsgId == Bap_gDebugLsgId)
    {
        /* Byte 6, Bit 2^5 */
        BAP_DBG_DebugInfoTable[7] |= BAP_BIT5;
    }
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_DBG_PER_LSG */

#ifdef BAP_DBG_PER_LSG
/* Diese Funktion ist in bap_debug.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_DBG_MsgOversizeError(lsgId_t aLsgId)
{
    if (aLsgId == Bap_gDebugLsgId)
    {
        /* Byte 6, Bit 2^4 */
        BAP_DBG_DebugInfoTable[7] |= BAP_BIT4;
    }
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_DBG_PER_LSG */

#ifdef BAP_DBG_PER_LSG
/* Diese Funktion ist in bap_debug.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_DBG_SequenceError(lsgId_t aLsgId)
{
    if (aLsgId == Bap_gDebugLsgId)
    {
        /* Byte 6, Bit 2^3 */
        BAP_DBG_DebugInfoTable[7] |= BAP_BIT3;
    }
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_DBG_PER_LSG */

#ifdef BAP_DBG_PER_LSG
/* Diese Funktion ist in bap_debug.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_DBG_RxDataPurgedEvent(void)
{
    if ((lsgId_t)0  != (lsgId_t)Bap_gDebugLsgId) /* MISRA_2012_REQ_10.5 : no risk arise because 0 fit in enum. could be a 0u */
    {
        /* Byte 6, Bit 2^2 */
        BAP_DBG_DebugInfoTable[7] |= BAP_BIT2;
    }
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_DBG_PER_LSG */

#ifdef BAP_DBG_PER_LSG
/* Diese Funktion ist in bap_debug.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_DBG_TxEvent(void)
{
    if ((lsgId_t)0  != (lsgId_t)Bap_gDebugLsgId) /* MISRA_2012_REQ_10.5 : no risk arise because 0 fit in enum. could be a 0u */
    {
        /* Byte 6, Bit 2^1 */
        BAP_DBG_DebugInfoTable[7] |= BAP_BIT1;
    }
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_DBG_PER_LSG */

#ifdef BAP_DBG_PER_LSG
/* Diese Funktion ist in bap_debug.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_DBG_RxEvent(void)
{
    if ((lsgId_t)0 != (lsgId_t)Bap_gDebugLsgId) /* MISRA_2012_REQ_10.5 : no risk arise because 0 fit in enum. could be a 0u */
    {
        /* Byte 6, Bit 2^0 */
        BAP_DBG_DebugInfoTable[7] |= BAP_BIT0;
    }
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_DBG_PER_LSG */


#if defined(BAP_DBG_PER_LSG) || defined(BAP_DBG_ON_OFF)
/* Diese Funktion ist in bap_debug.h dokumentiert */
#   define BAP_START_SEC_CODE_CYCLIC
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_DBG_Task(void)
{
	/* BAP_SendDebugInfo_Active is to deactivate this task for IPC testcase 128. In all other cases it would remain active
       BAP_SendDebugInfo_Active == 1 means BAP_DBG_Task is active
       BAP_SendDebugInfo_Active == 0 means BAP_DBG_Task is not active (This is set from IPC test case 128) */
	if(BAP_TRUE == (bool_t)BAP_SendDebugInfo_Active)
	{
		if ((lsgId_t)Bap_gDebugLsgId > (lsgId_t)BAP_MAX_LSG_ID) /* MISRA_2012_REQ_10.5 : no risk arise because 63 fit in enum. could be a 63u */
		{
			/* Ist ein Ereignis oder Fehler aufgetreten? */
			if ((uint8_t)0u  != ((BAP_DBG_DebugInfoTable[2] & BAP_BITMASK_00001111) |
					(BAP_DBG_DebugInfoTable[3]) |
					(BAP_DBG_DebugInfoTable[4] & BAP_BITMASK_00001111) |
					(BAP_DBG_DebugInfoTable[5]) |
					(BAP_DBG_DebugInfoTable[6] & BAP_BITMASK_00001111) |
					(BAP_DBG_DebugInfoTable[7])))
			{
				/* Versende Botschaft */
				DBGVAR BapError_et bapErr = BAP_SendDebugInfo(BAP_DBG_DebugInfoTable);

				/* Nach erfolgreichem Versenden */
				/* MISRA_2012_REQ_14.3 : The controlling expression is not invariant,
				 * "bapErr" will be different from "BapErr_OK" if the infos could not be send (for busy CAN for instance) */
				if (BapErr_OK == bapErr)
				{
					/* Loeschen von Fct-Id und OpCode im BAP-Header */
					BAP_DBG_DebugInfoTable[1] = (uint8_t)0u;
					BAP_DBG_DebugInfoTable[2] &= BAP_BITMASK_00001110;
					/* Loesche Ereignisbits */
					BAP_DBG_DebugInfoTable[4] &= BAP_BIT3;
					BAP_DBG_DebugInfoTable[3] = (uint8_t)0u;
					BAP_DBG_DebugInfoTable[5] = (uint8_t)0u;
					BAP_DBG_DebugInfoTable[6] &= BAP_BITMASK_11000000;
					BAP_DBG_DebugInfoTable[7] = (uint8_t)0u;
				}
			}
		}
		/* MISRA_2012_REQ_14.3 : "((lsgId_t)Bap_gDebugLsgId < (lsgId_t)64)" is not invariant,
		 * it will be false in case of configuration issue, but indeed in normal running way it should not be false. */
		/* MISRA_2012_REQ_10.5 : no risk arise because 0 and 64 fit in enum. could be a 0u and a 64u*/
		else if (((lsgId_t)Bap_gDebugLsgId > (lsgId_t)0) && ((lsgId_t)Bap_gDebugLsgId <= (lsgId_t)BAP_MAX_LSG_ID))
		{
			/* Ist ein Ereignis oder Fehler aufgetreten? */
			if ((uint8_t)0u != ((BAP_DBG_DebugInfoTable[2] & BAP_BITMASK_00011111) |
					(BAP_DBG_DebugInfoTable[3]) |
					(BAP_DBG_DebugInfoTable[4] & BAP_BITMASK_11011111) |
					(BAP_DBG_DebugInfoTable[5]) |
					(BAP_DBG_DebugInfoTable[6] & BAP_BITMASK_00111111) |
					(BAP_DBG_DebugInfoTable[7])))
			{
				/* Versende Botschaft */
				DBGVAR BapError_et bapErr = BAP_SendDebugInfo(BAP_DBG_DebugInfoTable);

				/* Nach erfolgreichem Versenden */
				/* MISRA_2012_REQ_14.3 : The controlling expression is not invariant,
				 * "bapErr" will be different from "BapErr_OK" if the infos could not be send (for busy CAN for instance) */
				if (BapErr_OK == bapErr)
				{
					/* Loeschen von Fct-Id und OpCode im BAP-Header */
					BAP_DBG_DebugInfoTable[0] &= BAP_BITMASK_00001111;
					BAP_DBG_DebugInfoTable[1] &= BAP_BITMASK_11000000;
					/* Loesche Ereignisbits */
					BAP_DBG_DebugInfoTable[2] &= BAP_BITMASK_11100000;
					BAP_DBG_DebugInfoTable[3] = (uint8_t)0u;
					BAP_DBG_DebugInfoTable[4] &= BAP_BIT5;
					BAP_DBG_DebugInfoTable[5] = (uint8_t)0u;
					BAP_DBG_DebugInfoTable[6] &= BAP_BITMASK_11000000;
					BAP_DBG_DebugInfoTable[7] = (uint8_t)0u;
				}
			}
		}
		else
		{
			/* nichts zu tun, soll nicht erreicht werden */
		}
	}
}
#   define BAP_STOP_SEC_CODE_CYCLIC
#   include <BAP_MemMap.h>
#endif /* defined(BAP_DBG_PER_LSG) || defined(BAP_DBG_ON_OFF) */

#if defined(BAP_DBG_PER_LSG) || defined(BAP_DBG_ON_OFF)
/**
 * Diese Funktion bietet externen Zugriff auf die Variable Bap_gDebugLsgId
 * (notwendig fuer CUnit-Tests).
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_IMPL_FAR lsgId_t
BAP_DBG_GetDebugLsgId(void)
{
    return Bap_gDebugLsgId;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>
#endif

#if defined(BAP_DBG_PER_LSG) || defined(BAP_DBG_ON_OFF)
/**
 * Diese Funktion bietet externen Aenderungsmoeglichkeiten fuer die Variable Bap_gDebugLsgId
 * (notwendig fuer CUnit-Tests).
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_DBG_SetDebugLsgId(lsgId_t LsgId)
{
    Bap_gDebugLsgId = LsgId;

    /* Clear BAP_DBG_DebugInfoTable */
    if ((lsgId_t) Bap_gDebugLsgId > (lsgId_t) BAP_MAX_LSG_ID)
    {
    	/* Loeschen von Fct-Id und OpCode im BAP-Header */
    	BAP_DBG_DebugInfoTable[1] = (uint8_t) 0u;
    	BAP_DBG_DebugInfoTable[2] &= BAP_BITMASK_00001110;
    	/* Loesche Ereignisbits */
    	BAP_DBG_DebugInfoTable[4] &= BAP_BIT3;
    	BAP_DBG_DebugInfoTable[3] = (uint8_t) 0u;
    	BAP_DBG_DebugInfoTable[5] = (uint8_t) 0u;
    	BAP_DBG_DebugInfoTable[6] &= BAP_BITMASK_11000000;
    	BAP_DBG_DebugInfoTable[7] = (uint8_t) 0u;
    }
    /*lint -e685*/ /* [MISRA 2012 Rule 14.3, required] : PC-Lint rise a warning as relational operator ">=" is here always evaluates to true.
     * That's true only in ASR variant because lsgId_t is defined as Uint8_t but in embedded variant it is an enumeration which then justify the check.
     * No risk arrise because we need this check to always be true. */
    else if (
#ifdef BAP_USES_ASR_WRAPPER
    		((lsgId_t) Bap_gDebugLsgId >= (lsgId_t) 0) &&
#endif
			((lsgId_t) Bap_gDebugLsgId <= (lsgId_t) BAP_MAX_LSG_ID))
    {
    	/*lint +e685*/
    	/* Loeschen von Fct-Id und OpCode im BAP-Header */
    	BAP_DBG_DebugInfoTable[0] &= BAP_BITMASK_00001111;
    	BAP_DBG_DebugInfoTable[1] &= BAP_BITMASK_11000000;
    	/* Loesche Ereignisbits */
    	BAP_DBG_DebugInfoTable[2] &= BAP_BITMASK_11100000;
    	BAP_DBG_DebugInfoTable[3] = (uint8_t) 0u;
    	BAP_DBG_DebugInfoTable[4] &= BAP_BIT5;
    	BAP_DBG_DebugInfoTable[5] = (uint8_t) 0u;
    	BAP_DBG_DebugInfoTable[6] &= BAP_BITMASK_11000000;
    	BAP_DBG_DebugInfoTable[7] = (uint8_t) 0u;
    }
    else
    {
    	/* Empty else for misra, should not be reachable */
    }
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>
#endif

#if defined(BAP_DBG_PER_LSG) || defined(BAP_DBG_ON_OFF)
/* Diese Funktion ist in bap_debug.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_ProcessDebugControl(const uint8_t aru8DebugCtrl[2])
{

	BapLsgRomRow_pot poLsgRomRow;
    if (NULL != aru8DebugCtrl)
    {
    	/*lint -e9034*/ /* MISRA_2012_REQ_10.5 : aru8DebugCtrl of data type uint8_t is cast to enum BapLsg_t,
    	 * but no risk arise because in aru8DebugCtrl, first byte contains the LSG-Id and second byte a activation flag 0 or 1.
    	 * So a value which is never below 0 and fit in enum BapLsg_t. */
    	poLsgRomRow = BAP_GetLsgRomRow((lsgId_t) aru8DebugCtrl[0]);
    	/*lint +e9034*/
        if (NULL != poLsgRomRow)
        {
        	/*lint -e9034*/ /* MISRA_2012_REQ_10.5 : see above deactivation  */
            Bap_gDebugLsgId = (lsgId_t) aru8DebugCtrl[0];
            /*lint +e9034*/
            if ( (uint8_t)0 == aru8DebugCtrl[1])
            {
            	/*lint -e9034*/ /* MISRA_2012_REQ_10.5 : 0 fit in enum, so no risk arise.  */
            	Bap_gDebugLsgId = (lsgId_t)0;
            	/*lint +e9034*/
            }
            else
            {
                /*[FST] 2016-09-20 [SSWCCB-2392] neue Pruefung zur Bestimmung ob altes Debug-Format (LSG-ID > 63), oder Neues*/
                if((lsgId_t)Bap_gDebugLsgId <= (lsgId_t)BAP_MAX_LSG_ID)  /* MISRA_2012_REQ_10.5 : no risk arise because 64 fit in enum. could be a 64u*/
                {
                    /* BAP-Header fuer unsegmentierte Botschaft
                                 Byte0         Byte1
                            OpCode   LSG-ID    FCT-ID
                           0  000   XXXX | XX  000000 | */
                    BAP_DBG_DebugInfoTable[0] = (uint8_t)(((uint8_t)Bap_gDebugLsgId & (uint8_t)0x3Cu) >> (uint8_t)2);
                    BAP_DBG_DebugInfoTable[1] = (uint8_t)(((uint8_t)Bap_gDebugLsgId & (uint8_t)0x03u) << (uint8_t)6);
                }
                else /*[FST] 2016-09-20 [SSWCCB-2392] LSG-ID nur noch im ersten kompletten Byte*/
                {
                    BAP_DBG_DebugInfoTable[0] = (uint8_t)(Bap_gDebugLsgId);
                    BAP_DBG_DebugInfoTable[1] = (uint8_t)0u;
                }

                BAP_DBG_DebugInfoTable[2] = (uint8_t)0u;
                BAP_DBG_DebugInfoTable[3] = (uint8_t)0u;
                BAP_DBG_DebugInfoTable[4] = (uint8_t)0u;
                BAP_DBG_DebugInfoTable[5] = (uint8_t)0u;
                BAP_DBG_DebugInfoTable[6] = (uint8_t)0u;
                BAP_DBG_DebugInfoTable[7] = (uint8_t)0u;

                /* Die richtigen Anfangszustaende setzen */
                BAP_DBG_SetBalState(Bap_gDebugLsgId, poLsgRomRow->poLsgRamRow->eLsgStatus);

#   ifdef BAP_ASG
#       if defined(BAP_ASG) && defined(BAP_FSG)
                if (BapSG_ASG == poLsgRomRow->eSGType)
#       endif /* defined(BAP_ASG) && defined(BAP_FSG) */
                {
                    BAP_DBG_SetCacheValidState(Bap_gDebugLsgId
                        , (bool_t)poLsgRomRow->poLsgRamRow->fState.fCacheValid);
                }
#   endif /* #ifdef BAP_ASG */
                BAP_DBG_SetHeartbeatState(Bap_gDebugLsgId
                    , ((poLsgRomRow->poLsgRamRow->eHeartbeatStatus == BapBplStat_OK) ? BAP_TRUE : BAP_FALSE) );

                /* Nach dem Einschalten gleich die Botschaft versenden */
                (void) BAP_SendDebugInfo(BAP_DBG_DebugInfoTable);
            }
        }
    }
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* defined(BAP_DBG_PER_LSG) || defined(BAP_DBG_ON_OFF) */

