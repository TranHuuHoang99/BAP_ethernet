/******************************************************************
 *
 *     Copyright (c) 2004-2023 Volkswagen AG, D-38436 Wolfsburg
 *
 ******************************************************************
 *
 * Projekt:    BAP
 * Komponente: BAL
 * BAP Version: 1.12.2
 *
 ******************************************************************
 *
 * Beschreibung
 *
 *  Diese Datei enthaelt Hilfsfunktionen fuer die BAL Schicht im
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
 * 2021-03-12	1.11.3		JEO			[SSWPPB-142] Fix MISRA violations.
 * 2021-03-08   1.11.3      DRH         [SSWPPB-142] Replaced magic numbers by constants
 * 2021-03-01	1.11.3		JEO			[SSWPPB-142] Improve jutification of Pc-Lint deac or MISRA rules violation + fix MISRA_2012_10.4 violation in "BAP_BAL_CheckDataReceived()"
 * 2020-03-31   1.11.1      ODD         [SSWPPB-93] removed Dead Code in Function BAP_BAL_CheckDatatype()
 * 2019-07-19   1.11.0      KUL         [SSWPPB-14] Versionsprüfung der DF-Minor im FSG
 * 2019-03-27   1.10.99     ODD         [SSWCCB-800]  Anpassung Auswertung FctList in Abhaengigkeit ob FctList im Zuge der StatusAll oder Heartbeat/GetData empfangen wurde 
 * 2019-03-21   1.10.99     KUL         [SSWPPB-4] Removal of string.h inclusion
 * 2019-01-18   1.10.99     FFS         [SSWCCB-2657] Improvement of BAP_GetLsgRomRow, Extern declaration and use of Bap_reAssignLsgRomRowFctTable for Multiconfig
 * 2018-07-19   1.10.3      FFS         [SSWCCB-2522] Misra-2012 fix (release was postponed)
 * 2017-05-05   1.9.0.3     FST         [SSWCCB-2425] Pruefung auf Nullzeiger vor Aufruf von BAP_BPL_AbortSend eingefuegt
 * 2017-03-17   1.9.0.1     FST         [SSWCCB-1545] SSW-Lokatierungs-Pragmas eingefuegt
 * 2016-10-12   1.8.1       FST         [SSWCCB-2410] Softwareschalter DLL_COMPILATION zur Unterscheidung
 *                                      der Erzeugung von Steuergeraete-Code und der BAP-Dll eingefuegt
 * 2014-11-28   1.8.0.0     WWU/FST     [SSWCCB-2105] Formataenderung der Variablen 16Bit->32Bit
 * 2014-03-24   1.7.1       WWU         MISRA-2004 Fix: Array Dimensionen fuer BAP_OpCode2AcknowledgeMatrix,
 *                                      BAP_OpCode2IndicationMatrix und BAP_Request2OpCodeMatrix hinzugefuegt.
 * 2014-03-21   1.7.1       WWU         Codeanpassungen wegen CCB664, CCB 1731: Alignment problem.
 *                                      Type BapBalRamRow_t ist jetzt struct, statt union.
 * 2013-03-05   1.7.0       WWU         Misra-2004 Fix
 * 2012-10-15   1.6.5.1     WWU         Korrektur der Misra-98 Abweichungen
 * 2012-09-18   1.6.5       WWU         Cyclomatic Complexity reduziert in Funktion: BAP_BAL_CheckBapConfig, BAP_BAL_AsgDataReceived,
 *                                      BAP_BAL_CheckRequest, BAP_BAL_CheckDataType
 * 2012-06-14   1.6.4       WWU         Die Aenderung von 2011-05-26:Superset in der Funktionlist als Fehler behandeln
 *                                      wird zurueckgesetzt, wegen Kompabilitaetsproblem. FSG darf hinter mehr Funktionen als ASG haben.
 * 2012-06-14   1.6.4       WWU         keine Ueberpruefung der PV_MINOR, SG_MINOR und DF_MINOR im ASG
 * 2011-08-25   1.6.2       WWU         Anpassung von Bearbeitung einer StatusAll Nachricht mit unsegmentierter Funktionlist
 * 2011-06-07   1.6         WWU         Pruefung von DF_MINOR auch Combi
 * 2011-05-26   1.6         WWU         Pruefung von DF_MINOR (nur ASG)
 * 2011-05-26   1.6         WWU         Cast Problem: Kein Byte Zugriff  bei ARM wegen ungrader Speicheradresse.
 *                                      Loesung: Zugriff und Cast trennen.
 * 2011-05-26   1.6         WWU         Superset in der Funktionlist als Fehler behandeln
 * 2007-09-18   1.5         RVE         Die Tabellen fuer BAP_OpCode2AcknowledgeMatrix um StatusAck und Ack erweitert.
 * 2007-08-28   1.5         ALI         Ueberpruefung ASG-PVMinor >= FSG-PVMinor statt ==
 * 2007-08-28   1.5         ALI         CheckBapConfig() nun auch fuer FSG moeglich wegen MultiConfig
 * 2007-08-27   1.5         RVE         Tabellen fuer die Abbildung von OpCodes <-> Requests/Indications erweitert und
 *                                      angepasst auf die neuen OpCodes StatusAck und Ack.
 *                                      In BAP_BAL_AsgDataReceived Anpassungen fuer Cache-Aktualisierung bei StatusAck.
 * 2007-08-21   1.5         ALI         Parameteruebergabe in BAP_BPL_AbortSend und BAP_BAL_UpdateLsgCacheStatus geaendert
 * 2007-08-16   1.5         ALI         Zugriff auf BapBalRamRow_t geaendert, da der Datentyp geaendert wurde
 * 2006-06-02   1.4         ALA         Unterstuetzung von Bap_Acknowledge
 * 2006-04-12   1.4         ALA         Unterstuetzung fuer kompatible Erweiterung.
 * 2006-04-12   1.4         ALA         Unterstuetzung fuer neue Versionspruefung.
 * 2006-04-12   1.4         ALA         Fehler behoben: InitSendBuffer kann nun fuer jedes Property aufgerufen werden
 *                                      unabhaengig von der dynamischen FctList
 * 2006-03-24   1.4         ALA         Unterstuetzung fuer BAP_ROM_DATA_FAR.
 * 2006-03-24   1.4         ALA         Nur in bap_balutil.c verwendete Funktionen statisch definiert
 * 2005-11-14   1.3.1.3     ALA         C++ Kommentar entfernt
 * 2005-10-24   1.3.1.2     ALA         Kommentarzeichen hinter #endif ergaenzt, Lint-Meldung im FSG entfernt.
 * 2005-08-02   1.3.1.1     ALA         Bugfix: BAP_CacheGetRequestIntXYZ fuer Properties mit Tx-Datentyp void
 *                                      lieferte zuvor InvalidArg.
 * 2005-05-03   1.3         CRI         Entfernung von BAP_BAL_SetLsgRomRow, da jetzt direkt
 * 2005-05-02   1.3         CRI         Bugfix: Status des Einzelcaches zwischenspeichern
 *                                      vor Aufruf von UpdateCache
 * 2005-04-29   1.3         CRI         InitpLsgRomRow() entfernt
 * 2005-04-29   1.3         CRI         Gesamt Cache Status in globales Flag lsgState.tCacheValid
 * 2005-04-25   1.3         CRI         BUGFIX: Wenn ASG im WaitForConfig Zustand ist,
 *                                      muss der Erhalt einer BAPCONFIG eine IndBS ausloesen
 * 2005-04-18   1.3         CRI         Gesamt Cache Status in globale LSG Variable
 * 2005-04-18   1.3         CRI         Ext. Fct.list Anpassung in CheckIfFctValid
 * 2005-04-13   1.3         ALA         Optimierung der Datenstrukturen
 * 2005-04-12   1.3         CRI         ASG&FSG zusammen
 * 2005-04-11   1.3         CRI         FixedByteSequence muss exakt Laenge 6 haben (CheckDatatype)
 * 2005-04-11   1.3         CRI         BapInd_Processing_CNF fuer das FSG hinzugekommen
 * 2005-04-11   1.3         CRI         Eine StatusAll Indication deaktiviert Zeitueberwachung fuer GetAll
 * 2005-04-10   1.3         CRI         Im FSG darf kein Request auf Fct-Id 0-7 gemacht werden
 * 2005-04-08   1.3         CRI         Hinzufuegen von BAP_BPL_AbortSend (Aufruf von BCL und loeeschen Retry)
 * 2005-04-08   1.3         CRI         Man kann jetzt bereits mit einem Fct.list Subset im ASG starten
 * 2005-04-04   1.3         CRI         Erweiterung von CheckDatatype um Funktionstyp VOID fuer asym. Prop.
 * 2005-04-04   1.3         CRI         Fuer das FSG werden beim Fct.list Zugriff statt der ROM Table
 *                                      die RAM-Table benutzt
 * 2005-04-01   1.3         CRI         Hinzufuegen der CheckIfFunctionValid Funktion
 * 2005-03-31   1.3         ALA         Interruptsperre entfernt
 * 2005-03-20   1.3         CRI         InitFSGBuffers, CheckDataReceived, CheckRequest, InvalidateCache
 *                                      an dynamische Fct.list angepasst
 *                                      (Benutzung des RAM Eintrags bzw. sperren nicht unterstuetzter Fcts)
 * 2005-03-24   1.2.1       CRI         In CheckBapConfigAsg: Bei Wechseln der Konfiguration durch einen
 *                                      Reset muessen die BPL/BCL Schicht neu initialisiert werden
 * 2005-03-18   1.3         CRI         Rueckgabewert bei BAP_BAL_UpdateCache entsprechend einer Wertaenderung
 * 2004-03-14   1.2.1       CRI         Bugfix: Illegaler Arrayzugriff auf Fct-Id 255 entfernt (2mal)
 * 2004-11-17   1.2         JOK         Auswertung der StatusAll-Block Nachricht eingebaut
 * 2004-10-21   1.2         JOK         Hilfsfunktionen aus bap_bal in bap_balutil verschoben
 * 2004-09-03   1.2         JOK         Inhalt von BAP_OpCode2IndicationMatrix
 *                                      an Funktionsklasse Methode angepasst
 * 2004-09-03   1.2         JOK         Inhalt von BAP_Request2OpCodeMatrix
 *                                      an Funktionsklasse Methode angepasst
 * 2004-08-25   1.2         JOK         Cache-Gueltigkeit abhaengig von FunctionList des FSG
 * 2004-06-07   1.1         JOK         Compilerschalter fuer SG-Typen zur Optimierung
 *                                      des ROM-Bedarfs eingefuegt
 * 2004-06-07   1.1         JOK         Laufzeitoptimierungen in Funktionen durch ersetzen der aLsgId
 *                                      durch den Zeiger apoLsgRomRow in die LSG-Tabelle
 * 2004-06-07   1.1         JOK         Includes bap_bal.h entfernt
 * 2004-06-07   1.1         JOK         BAP_OpCode2IndicationMatrix je nach SG-Type definiert, um
 *                                      Opcode-Doppeldeutigkeit aufzuloesen.
 * 2004-06-07   1.1         JOK         FctId 4 (Heartbeat) wird nicht mehr fuer Cache-Gueltigkeit
 *                                      ausgewertet.
 ******************************************************************/


/* Systemincludes mit <...> */

/* Bibliotheken von externen Herstellen mit <...> */

/* Eigene Header-Dateien "..." */
#include "bap_types.h"
#include "bap_balconfig.h"
#include "bap_balutil.h"
#include "bap_debug.h"
#include "bap_util.h"
#include "bap_bpl.h"
#include "bap_bal.h"
#include "bap_config.h"

#ifdef BAP_USES_ASR_WRAPPER
/* Include required only in Autosar as defines from bap_defines.h will be 
   defined in rte_bap_types.h */
#include "Rte_BAP.h"
#endif /* #ifdef BAP_USES_ASR_WRAPPER */


/* Externe globale Variablen-Definitionen */
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>

/* Table zur Zwischenspeicherung der Funktionslist*/
#ifdef DLL_COMPILATION
extern uint8_t aru8LocalFunctionList[BAP_FCTID_FCTLIST_SIZE];
#else
static DBGVAR uint8_t aru8LocalFunctionList[BAP_FCTID_FCTLIST_SIZE];
#endif /* #ifdef DLL_COMPILATION */

#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>



/* Multiconfig in der Funktion BAP_GetLsgRomRow(DBGVAR lsgId_t aLsgId) */
#ifdef DLL_COMPILATION
extern bool_t Bap_reAssignLsgRomRowFctTable  ;
#else
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
extern bool_t Bap_reAssignLsgRomRowFctTable  ;
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#endif // DLL_COMPILATION




/* Fuer die 3 verschiedenen Konfigurationen (ASG, FSG, ASG & FSG)
   werden im folgenden die entsprechenden Matrizen fuer die
   Gueltigkeitpruefungen OPC-->IND und REQ-->OPC angelegt */

/* ---------------------------------------------------------------------------------------------- */
#if defined(BAP_ASG) && (!defined(BAP_FSG))
/**
 * Tabelle zur Abbildung eines Paars (Funktionsklasse,Request) auf OpCode
 * Diese Tabelle ist im ASG bzw. FSG unterschiedlich
 */
#   define BAP_START_SEC_CONST_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>
const BapOpCodes_et BAP_ROM_CONST BAP_Request2OpCodeMatrix[][BAP_NUMBER_OF_REQUESTS] =
{
    /* Funktionsklasse Property */
    {
        BapOp_PropSetGet,       BapOp_PropReset_Set,    BapOp_PropGet,        BapOp_Invalid,
        BapOp_Invalid,          BapOp_Invalid,          BapOp_Invalid,        BapOp_Invalid,
        BapOp_Invalid,          BapOp_Invalid,          BapOp_Invalid,        BapOp_PropAck
    },
    /* Funktionsklasse Cache */
    {
        BapOp_CacheSetGetAll,   BapOp_CacheSetAll,      BapOp_CacheGetAll,    BapOp_Invalid,
        BapOp_Invalid,          BapOp_Invalid,          BapOp_Invalid,        BapOp_Invalid,
        BapOp_Invalid,          BapOp_Invalid,          BapOp_Invalid,        BapOp_Invalid
    }
#if defined(BAP_USES_ARRAYS) || defined(BAP_USES_METHODS)
    ,
    /* Funktionsklasse Array */
    {
        BapOp_ArrSetGet,        BapOp_ArrSet,           BapOp_ArrGet,         BapOp_Invalid,
        BapOp_Invalid,          BapOp_Invalid,          BapOp_Invalid,        BapOp_Invalid,
        BapOp_Invalid,          BapOp_Invalid,          BapOp_Invalid,        BapOp_Invalid
    }
#endif /* #if defined(BAP_USES_ARRAYS) || defined(BAP_USES_METHODS) */
#ifdef BAP_USES_METHODS
    ,
    /* Funktionsklasse Methode */
    {
        BapOp_Invalid,          BapOp_Invalid,          BapOp_Invalid,        BapOp_Invalid,
        BapOp_Invalid,          BapOp_MethStart,        BapOp_MethStartResult,BapOp_MethAbort,
        BapOp_Invalid,          BapOp_Invalid,          BapOp_Invalid,        BapOp_Invalid
    }
#endif /* BAP_USES_METHODS */
};
#   define BAP_STOP_SEC_CONST_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>

/**
 * Tabelle zur Abbildung eines Paars (Funktionsklasse,OpCode) auf Indication
 */
#   define BAP_START_SEC_CONST_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>
const BapIndication_et BAP_ROM_CONST BAP_OpCode2IndicationMatrix[][BAP_NUMBER_OF_OPCODES_FOR_INDICATIONS] =
{
    /* Funktionsklasse Property */
    {
        BapInd_Reset,       BapInd_Invalid,     BapInd_Invalid,  BapInd_Invalid,
        BapInd_Data,        BapInd_DataAck,     BapInd_Invalid
    },
    /* Funktionsklasse Cache */
    {
        BapInd_Invalid,     BapInd_Invalid,     BapInd_Invalid,  BapInd_Invalid,
        BapInd_Data,        BapInd_Invalid,     BapInd_Invalid
    }
#if defined(BAP_USES_ARRAYS) || defined(BAP_USES_METHODS)
    ,
    /* Funktionsklasse Array */
    {
        BapInd_Invalid,     BapInd_Invalid,     BapInd_Invalid,  BapInd_Changed,
        BapInd_Data,        BapInd_Invalid,     BapInd_Invalid
    }
#endif /* #if defined(BAP_USES_ARRAYS) || defined(BAP_USES_METHODS) */
#ifdef BAP_USES_METHODS
    ,
    /* Funktionsklasse Methode */
    {
        BapInd_Invalid,     BapInd_Invalid,     BapInd_Invalid,  BapInd_Processing,
        BapInd_Result,      BapInd_Invalid,     BapInd_Invalid
    }
#endif /* BAP_USES_METHODS */
};
#   define BAP_STOP_SEC_CONST_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>

#ifdef BAP_USES_ACKNOWLEDGE
/**
 * Tabelle zur Abbildung eines Paars (Funktionsklasse,OpCode) auf Acknowledge
 */
#   define BAP_START_SEC_CONST_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>
/* MISRA 2012 warning removal */
extern const BapAcknowledge_et BAP_ROM_CONST BAP_OpCode2AcknowledgeMatrix[][BAP_NUMBER_OF_OPCODES_FOR_ACKNOWLEDGES];
const BapAcknowledge_et BAP_ROM_CONST BAP_OpCode2AcknowledgeMatrix[][BAP_NUMBER_OF_OPCODES_FOR_ACKNOWLEDGES] =
{
    /* Funktionsklasse Property */
    {
        BapAck_Property_DataSet,    BapAck_Property_DataGet,    BapAck_Property_DataSetGet, BapAck_Nothing,
        BapAck_Nothing,             BapAck_Nothing,             BapAck_Property_Ack,        BapAck_Nothing
    },
    /* Funktionsklasse Cache */
    {
        BapAck_Nothing,     BapAck_Cache_DataGet,               BapAck_Nothing,             BapAck_Nothing,
        BapAck_Nothing,     BapAck_Nothing,                     BapAck_Nothing,             BapAck_Nothing
    }
#if defined(BAP_USES_ARRAYS) || defined(BAP_USES_METHODS)
    ,
    /* Funktionsklasse Array */
    {
        BapAck_Array_DataSet,       BapAck_Array_DataGet,       BapAck_Array_DataSetGet,    BapAck_Nothing,
        BapAck_Nothing,             BapAck_Nothing,             BapAck_Nothing,             BapAck_Nothing
    }
#endif /* #if defined(BAP_USES_ARRAYS) || defined(BAP_USES_METHODS) */
#ifdef BAP_USES_METHODS
    ,
    /* Funktionsklasse Methode */
    {
        BapAck_Method_Start,        BapAck_Method_Abort,        BapAck_Method_StartResult,  BapAck_Nothing,
        BapAck_Nothing,             BapAck_Nothing,             BapAck_Nothing,             BapAck_Nothing
    }
#endif /* BAP_USES_METHODS */
};
#       define BAP_STOP_SEC_CONST_INIT_UNSPECIFIED
#       include <BAP_MemMap.h>
#endif /* #ifdef BAP_USES_ACKNOWLEDGE */


/* ---------------------------------------------------------------------------------------------- */
#elif defined(BAP_FSG) && (!defined(BAP_ASG))
/**
 * Tabelle zur Abbildung eines Paars (Funktionsklasse,Request) auf OpCode
 * Diese Tabelle ist im ASG bzw. FSG unterschiedlich
 */
#   define BAP_START_SEC_CONST_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>
const BapOpCodes_et BAP_ROM_CONST BAP_Request2OpCodeMatrix[][BAP_NUMBER_OF_REQUESTS] =
{
    /* Funktionsklasse Property */
    {
        BapOp_Invalid,          BapOp_Invalid,          BapOp_Invalid,        BapOp_PropStatus,
        BapOp_Invalid,          BapOp_Invalid,          BapOp_Invalid,        BapOp_Invalid,
        BapOp_Invalid,          BapOp_Invalid,          BapOp_PropStatusAck,  BapOp_Invalid
    },
    /* Funktionsklasse Cache */
    {
        BapOp_Invalid,          BapOp_Invalid,          BapOp_Invalid,        BapOp_CacheStatusAll,
        BapOp_Invalid,          BapOp_Invalid,          BapOp_Invalid,        BapOp_Invalid,
        BapOp_Invalid,          BapOp_Invalid,          BapOp_Invalid,        BapOp_Invalid
    }
#if defined(BAP_USES_ARRAYS) || defined(BAP_USES_METHODS)
    ,
    /* Funktionsklasse Array */
    {
        BapOp_Invalid,          BapOp_Invalid,          BapOp_Invalid,        BapOp_ArrStatus,
        BapOp_ArrChanged,       BapOp_Invalid,          BapOp_Invalid,        BapOp_Invalid,
        BapOp_Invalid,          BapOp_Invalid,          BapOp_Invalid,        BapOp_Invalid
    }
#endif /* #if defined(BAP_USES_ARRAYS) || defined(BAP_USES_METHODS) */
#ifdef BAP_USES_METHODS
    ,
    /* Funktionsklasse Methode */
    {
        BapOp_Invalid,          BapOp_Invalid,          BapOp_Invalid,        BapOp_Invalid,
        BapOp_Invalid,          BapOp_Invalid,          BapOp_Invalid,        BapOp_Invalid,
        BapOp_MethProcessing,   BapOp_MethResult,       BapOp_Invalid,        BapOp_Invalid
    }
#endif /* BAP_USES_METHODS */
};
#   define BAP_STOP_SEC_CONST_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>

/**
 * Tabelle zur Abbildung eines Paars (Funktionsklasse,OpCode) auf Indication
 */
#   define BAP_START_SEC_CONST_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>
const BapIndication_et BAP_ROM_CONST BAP_OpCode2IndicationMatrix[][BAP_NUMBER_OF_OPCODES_FOR_INDICATIONS] =
{
    /* Funktionsklasse Property */
    {
        BapInd_DataSet,     BapInd_DataGet,     BapInd_DataSetGet,  BapInd_Invalid,
        BapInd_Invalid,     BapInd_Invalid,     BapInd_Ack
    },
    /* Funktionsklasse Cache */
    {
        BapInd_DataSet,     BapInd_DataGet,     BapInd_DataSetGet,  BapInd_Invalid,
        BapInd_Invalid,     BapInd_Invalid,     BapInd_Invalid
    }
#if defined(BAP_USES_ARRAYS) || defined(BAP_USES_METHODS)
    ,
    /* Funktionsklasse Array */
    {
        BapInd_DataSet,     BapInd_DataGet,     BapInd_DataSetGet,  BapInd_Invalid,
        BapInd_Invalid,     BapInd_Invalid,     BapInd_Invalid
    }
#endif /* #if defined(BAP_USES_ARRAYS) || defined(BAP_USES_METHODS) */
#ifdef BAP_USES_METHODS
    ,
    /* Funktionsklasse Methode */
    {
        BapInd_Start,       BapInd_Abort,       BapInd_StartResult, BapInd_Processing_CNF,
        BapInd_Invalid,     BapInd_Invalid,     BapInd_Invalid
    }
#endif /* BAP_USES_METHODS */
};
#   define BAP_STOP_SEC_CONST_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>


#ifdef BAP_USES_ACKNOWLEDGE
/**
 * Tabelle zur Abbildung eines Paars (Funktionsklasse,OpCode) auf Acknowledge
 */
#       define BAP_START_SEC_CONST_INIT_UNSPECIFIED
#       include <BAP_MemMap.h>
/* MISRA 2012 warning removal */
static const BapAcknowledge_et BAP_ROM_CONST BAP_OpCode2AcknowledgeMatrix[][BAP_NUMBER_OF_OPCODES_FOR_ACKNOWLEDGES] =
{
    /* Funktionsklasse Property */
    {
        BapAck_Nothing,             BapAck_Nothing,             BapAck_Nothing,             BapAck_Nothing,
        BapAck_Property_Data,       BapAck_Property_DataAck,    BapAck_Nothing,             BapAck_Property_Error
    },
    /* Funktionsklasse Cache */
    {
        BapAck_Nothing,             BapAck_Nothing,             BapAck_Nothing,             BapAck_Nothing,
        BapAck_Nothing,             BapAck_Nothing,             BapAck_Nothing,             BapAck_Nothing
    }
#if defined(BAP_USES_ARRAYS) || defined(BAP_USES_METHODS)
    ,
    /* Funktionsklasse Array */
    {
        BapAck_Nothing,             BapAck_Nothing,             BapAck_Nothing,             BapAck_Array_Changed,
        BapAck_Array_Data,          BapAck_Nothing,             BapAck_Nothing,             BapAck_Array_Error
    }
#endif /* #if defined(BAP_USES_ARRAYS) || defined(BAP_USES_METHODS) */
#ifdef BAP_USES_METHODS
    ,
    /* Funktionsklasse Methode */
    {
        BapAck_Nothing,             BapAck_Nothing,             BapAck_Nothing,             BapAck_Method_Processing,
        BapAck_Method_Result,       BapAck_Nothing,             BapAck_Nothing,             BapAck_Method_Error
    }
#endif /* BAP_USES_METHODS */
};
#       define BAP_STOP_SEC_CONST_INIT_UNSPECIFIED
#       include <BAP_MemMap.h>
#endif /* #ifdef BAP_USES_ACKNOWLEDGE */

/* ---------------------------------------------------------------------------------------------- */
#elif defined(BAP_ASG) && defined(BAP_FSG)
/**
 * Tabelle zur Abbildung eines Paars (Funktionsklasse,Request) auf OpCode
 * Dabei muss unterschieden werden ob ein ASG oder FSG den Aufruf macht
 * Erster Index: 0==ASG;1==FSG
 */
#   define BAP_START_SEC_CONST_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>
#ifdef BAP_USES_METHODS
const BapOpCodes_et BAP_ROM_CONST BAP_Request2OpCodeMatrix[BAP_NUMBER_OF_LSGTYPES][BAP_NUMBER_OF_FUNCTIONCLASSES][BAP_NUMBER_OF_REQUESTS] =
#else
#ifdef BAP_USES_ARRAYS
const BapOpCodes_et BAP_ROM_CONST BAP_Request2OpCodeMatrix[BAP_NUMBER_OF_LSGTYPES][BAP_NUMBER_OF_FUNCTIONCLASSES][BAP_NUMBER_OF_REQUESTS] =
#else
const BapOpCodes_et BAP_ROM_CONST BAP_Request2OpCodeMatrix[BAP_NUMBER_OF_LSGTYPES][BAP_NUMBER_OF_FUNCTIONCLASSES][BAP_NUMBER_OF_REQUESTS] =
#endif /* BAP_USES_ARRAYS */
#endif /* BAP_USES_METHODS */
{
    { /* ASG Teil */
        /* Funktionsklasse Property */
        {
            BapOp_PropSetGet,       BapOp_PropReset_Set,    BapOp_PropGet,        BapOp_Invalid,
            BapOp_Invalid,          BapOp_Invalid,          BapOp_Invalid,        BapOp_Invalid,
            BapOp_Invalid,          BapOp_Invalid,          BapOp_Invalid,        BapOp_PropAck
        },
        /* Funktionsklasse Cache */
        {
            BapOp_CacheSetGetAll,   BapOp_CacheSetAll,      BapOp_CacheGetAll,    BapOp_Invalid,
            BapOp_Invalid,          BapOp_Invalid,          BapOp_Invalid,        BapOp_Invalid,
            BapOp_Invalid,          BapOp_Invalid,          BapOp_Invalid,        BapOp_Invalid
        }
#if defined(BAP_USES_ARRAYS) || defined(BAP_USES_METHODS)
        ,
        /* Funktionsklasse Array */
        {
            BapOp_ArrSetGet,        BapOp_ArrSet,           BapOp_ArrGet,         BapOp_Invalid,
            BapOp_Invalid,          BapOp_Invalid,          BapOp_Invalid,        BapOp_Invalid,
            BapOp_Invalid,          BapOp_Invalid,          BapOp_Invalid,        BapOp_Invalid
        }
#endif /* #if defined(BAP_USES_ARRAYS) || defined(BAP_USES_METHODS) */
#ifdef BAP_USES_METHODS
        ,
        /* Funktionsklasse Methode */
        {
            BapOp_Invalid,          BapOp_Invalid,          BapOp_Invalid,        BapOp_Invalid,
            BapOp_Invalid,          BapOp_MethStart,        BapOp_MethStartResult,BapOp_MethAbort,
            BapOp_Invalid,          BapOp_Invalid,          BapOp_Invalid,        BapOp_Invalid
        }
#endif /* BAP_USES_METHODS */
    },
    { /* FSG Teil */
        /* Funktionsklasse Property */
        {
            BapOp_Invalid,          BapOp_Invalid,          BapOp_Invalid,        BapOp_PropStatus,
            BapOp_Invalid,          BapOp_Invalid,          BapOp_Invalid,        BapOp_Invalid,
            BapOp_Invalid,          BapOp_Invalid,          BapOp_PropStatusAck,  BapOp_Invalid
        },
        /* Funktionsklasse Cache */
        {
            BapOp_Invalid,          BapOp_Invalid,          BapOp_Invalid,        BapOp_CacheStatusAll,
            BapOp_Invalid,          BapOp_Invalid,          BapOp_Invalid,        BapOp_Invalid,
            BapOp_Invalid,          BapOp_Invalid,          BapOp_Invalid,        BapOp_Invalid
        }
#if defined(BAP_USES_ARRAYS) || defined(BAP_USES_METHODS)
        ,
        /* Funktionsklasse Array */
        {
            BapOp_Invalid,          BapOp_Invalid,          BapOp_Invalid,        BapOp_ArrStatus,
            BapOp_ArrChanged,       BapOp_Invalid,          BapOp_Invalid,        BapOp_Invalid,
            BapOp_Invalid,          BapOp_Invalid,          BapOp_Invalid,        BapOp_Invalid
        }
#endif /* #if defined(BAP_USES_ARRAYS) || defined(BAP_USES_METHODS) */
#ifdef BAP_USES_METHODS
        ,
        /* Funktionsklasse Methode */
        {
            BapOp_Invalid,          BapOp_Invalid,          BapOp_Invalid,        BapOp_Invalid,
            BapOp_Invalid,          BapOp_Invalid,          BapOp_Invalid,        BapOp_Invalid,
            BapOp_MethProcessing,   BapOp_MethResult,       BapOp_Invalid,        BapOp_Invalid
        }
#endif /* BAP_USES_METHODS */
    }
};
#   define BAP_STOP_SEC_CONST_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>

/**
 * Tabelle zur Abbildung eines Paars (Funktionsklasse,OpCode) auf Indication
 * Unterschiedlich fuer ASG & FSG
 * Erster Index: 0==ASG;1==FSG
 */
#   define BAP_START_SEC_CONST_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>
#ifdef BAP_USES_METHODS
const BapIndication_et BAP_ROM_CONST BAP_OpCode2IndicationMatrix[BAP_NUMBER_OF_LSGTYPES][BAP_NUMBER_OF_FUNCTIONCLASSES][BAP_NUMBER_OF_OPCODES_FOR_INDICATIONS] =
#else
#ifdef BAP_USES_ARRAYS
const BapIndication_et BAP_ROM_CONST BAP_OpCode2IndicationMatrix[BAP_NUMBER_OF_LSGTYPES][BAP_NUMBER_OF_FUNCTIONCLASSES][BAP_NUMBER_OF_OPCODES_FOR_INDICATIONS] =
#else
const BapIndication_et BAP_ROM_CONST BAP_OpCode2IndicationMatrix[BAP_NUMBER_OF_LSGTYPES][BAP_NUMBER_OF_FUNCTIONCLASSES][BAP_NUMBER_OF_OPCODES_FOR_INDICATIONS] =
#endif /* BAP_USES_ARRAYS */
#endif /* BAP_USES_METHODS */
{
    { /* ASG Teil */
        /* Funktionsklasse Property */
        {
            BapInd_Reset,       BapInd_Invalid,     BapInd_Invalid,  BapInd_Invalid,
            BapInd_Data,        BapInd_DataAck,     BapInd_Invalid
        },
        /* Funktionsklasse Cache */
        {
            BapInd_Invalid,     BapInd_Invalid,     BapInd_Invalid,  BapInd_Invalid,
            BapInd_Data,        BapInd_Invalid,     BapInd_Invalid
        }
#if defined(BAP_USES_ARRAYS) || defined(BAP_USES_METHODS)
        ,
        /* Funktionsklasse Array */
        {
            BapInd_Invalid,     BapInd_Invalid,     BapInd_Invalid,  BapInd_Changed,
            BapInd_Data,        BapInd_Invalid,     BapInd_Invalid
        }
#endif /* #if defined(BAP_USES_ARRAYS) || defined(BAP_USES_METHODS) */
#ifdef BAP_USES_METHODS
        ,
        /* Funktionsklasse Methode */
        {
            BapInd_Invalid,     BapInd_Invalid,     BapInd_Invalid,  BapInd_Processing,
            BapInd_Result,      BapInd_Invalid,     BapInd_Invalid
        }
#endif /* BAP_USES_METHODS */
    },
    { /* FSG Teil */
        /* Funktionsklasse Property */
        {
            BapInd_DataSet,     BapInd_DataGet,     BapInd_DataSetGet,  BapInd_Invalid,
            BapInd_Invalid,     BapInd_Invalid,     BapInd_Ack
        },
        /* Funktionsklasse Cache */
        {
            BapInd_DataSet,     BapInd_DataGet,     BapInd_DataSetGet,  BapInd_Invalid,
            BapInd_Invalid,     BapInd_Invalid,     BapInd_Invalid
        }
#if defined(BAP_USES_ARRAYS) || defined(BAP_USES_METHODS)
        ,
        /* Funktionsklasse Array */
        {
            BapInd_DataSet,     BapInd_DataGet,     BapInd_DataSetGet,  BapInd_Invalid,
            BapInd_Invalid,     BapInd_Invalid,     BapInd_Invalid
        }
#endif /* #if defined(BAP_USES_ARRAYS) || defined(BAP_USES_METHODS) */
#ifdef BAP_USES_METHODS
        ,
        /* Funktionsklasse Methode */
        {
            BapInd_Start,       BapInd_Abort,       BapInd_StartResult, BapInd_Processing_CNF,
            BapInd_Invalid,     BapInd_Invalid,     BapInd_Invalid
        }
#endif /* BAP_USES_METHODS */
    }
};
#   define BAP_STOP_SEC_CONST_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>

#ifdef BAP_USES_ACKNOWLEDGE
/**
 * Tabelle zur Abbildung eines Paars (Funktionsklasse,OpCode) auf Acknowledge
 * Unterschiedlich fuer ASG & FSG
 * Erster Index: 0==ASG;1==FSG
 */
#       define BAP_START_SEC_CONST_INIT_UNSPECIFIED
#       include <BAP_MemMap.h>
#ifdef BAP_USES_METHODS
/* MISRA 2012 warning removal */
extern const BapAcknowledge_et BAP_ROM_CONST BAP_OpCode2AcknowledgeMatrix[BAP_NUMBER_OF_LSGTYPES][BAP_NUMBER_OF_FUNCTIONCLASSES][BAP_NUMBER_OF_OPCODES_FOR_ACKNOWLEDGES];
const BapAcknowledge_et BAP_ROM_CONST BAP_OpCode2AcknowledgeMatrix[BAP_NUMBER_OF_LSGTYPES][BAP_NUMBER_OF_FUNCTIONCLASSES][BAP_NUMBER_OF_OPCODES_FOR_ACKNOWLEDGES] =
#else
#ifdef BAP_USES_ARRAYS
/* MISRA 2012 warning removal */
extern const BapAcknowledge_et BAP_ROM_CONST BAP_OpCode2AcknowledgeMatrix[BAP_NUMBER_OF_LSGTYPES][BAP_NUMBER_OF_FUNCTIONCLASSES][BAP_NUMBER_OF_OPCODES_FOR_ACKNOWLEDGES];
const BapAcknowledge_et BAP_ROM_CONST BAP_OpCode2AcknowledgeMatrix[BAP_NUMBER_OF_LSGTYPES][BAP_NUMBER_OF_FUNCTIONCLASSES][BAP_NUMBER_OF_OPCODES_FOR_ACKNOWLEDGES] =
#else
#endif /* BAP_USES_ARRAYS */
/* MISRA 2012 warning removal */
extern const BapAcknowledge_et BAP_ROM_CONST BAP_OpCode2AcknowledgeMatrix[BAP_NUMBER_OF_LSGTYPES][BAP_NUMBER_OF_FUNCTIONCLASSES][BAP_NUMBER_OF_OPCODES_FOR_ACKNOWLEDGES];
const BapAcknowledge_et BAP_ROM_CONST BAP_OpCode2AcknowledgeMatrix[BAP_NUMBER_OF_LSGTYPES][BAP_NUMBER_OF_FUNCTIONCLASSES][BAP_NUMBER_OF_OPCODES_FOR_ACKNOWLEDGES] =
#endif /* BAP_USES_METHODS */
{
    { /* ASG Teil */
        /* Funktionsklasse Property */
        {
            BapAck_Property_DataSet,    BapAck_Property_DataGet,    BapAck_Property_DataSetGet, BapAck_Nothing,
            BapAck_Nothing,             BapAck_Nothing,             BapAck_Property_Ack,        BapAck_Nothing
        },
        /* Funktionsklasse Cache */
        {
            BapAck_Nothing,     BapAck_Cache_DataGet,               BapAck_Nothing,             BapAck_Nothing,
            BapAck_Nothing,     BapAck_Nothing,                     BapAck_Nothing,             BapAck_Nothing
        }
#if defined(BAP_USES_ARRAYS) || defined(BAP_USES_METHODS)
        ,
        /* Funktionsklasse Array */
        {
            BapAck_Array_DataSet,       BapAck_Array_DataGet,       BapAck_Array_DataSetGet,    BapAck_Nothing,
            BapAck_Nothing,             BapAck_Nothing,             BapAck_Nothing,             BapAck_Nothing
        }
#endif /* #if defined(BAP_USES_ARRAYS) || defined(BAP_USES_METHODS) */
#ifdef BAP_USES_METHODS
        ,
        /* Funktionsklasse Methode */
        {
            BapAck_Method_Start,        BapAck_Method_Abort,        BapAck_Method_StartResult,  BapAck_Nothing,
            BapAck_Nothing,             BapAck_Nothing,             BapAck_Nothing,             BapAck_Nothing
        }
#endif /* BAP_USES_METHODS */
    }
    ,
    { /* FSG Teil */
        /* Funktionsklasse Property */
        {
            BapAck_Nothing,             BapAck_Nothing,             BapAck_Nothing,             BapAck_Nothing,
            BapAck_Property_Data,       BapAck_Property_DataAck,    BapAck_Nothing,             BapAck_Property_Error
        },
        /* Funktionsklasse Cache */
        {
            BapAck_Nothing,             BapAck_Nothing,             BapAck_Nothing,             BapAck_Nothing,
            BapAck_Nothing,             BapAck_Nothing,             BapAck_Nothing,             BapAck_Nothing
        }
#if defined(BAP_USES_ARRAYS) || defined(BAP_USES_METHODS)
        ,
        /* Funktionsklasse Array */
        {
            BapAck_Nothing,             BapAck_Nothing,             BapAck_Nothing,             BapAck_Array_Changed,
            BapAck_Array_Data,          BapAck_Nothing,             BapAck_Nothing,             BapAck_Array_Error
        }
#endif /* #if defined(BAP_USES_ARRAYS) || defined(BAP_USES_METHODS) */
#ifdef BAP_USES_METHODS
        ,
        /* Funktionsklasse Methode */
        {
            BapAck_Nothing,             BapAck_Nothing,             BapAck_Nothing,             BapAck_Method_Processing,
            BapAck_Method_Result,       BapAck_Nothing,             BapAck_Nothing,             BapAck_Method_Error
        }
#endif /* BAP_USES_METHODS */
    }
};
#       define BAP_STOP_SEC_CONST_INIT_UNSPECIFIED
#       include <BAP_MemMap.h>
#endif /* #ifdef BAP_USES_ACKNOWLEDGE */

#endif  /* #elif defined(BAP_ASG) && defined(BAP_FSG) */





/* ---------------------------------------------------------------------------------------------- */

/* Interne Makro-Definitionen */

/* Interne Typ-Definitionen */

/* Interne Const Deklarationen */

/* Interne statische Variablen */


/* Vorwaerts-Deklarationen von statischen Funktionen */

#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>

static BAP_IMPL_FAR DBGVAR bool_t
BAP_BAL_CheckDatatype(DBGVAR BapDataType_et aeDataType
    , DBGVAR uint32_t au32BSSize
    , DBGVAR uint32_t au32DataSize
    , DBGVAR bool_t aIsSend
    , DBGVAR BapBalCheckDataType_et eScalarType
    );

static BAP_IMPL_FAR DBGVAR uint8_t
BAP_BAL_CompareBapConfig(BapLsgRomRow_pot poLsgRomRow,
        const volatile uint8_t* apData);

static BAP_IMPL_FAR DBGVAR bool_t
BAP_BAL_CheckIsScalar(BapBalCheckDataType_et eScalarType);

static BAP_IMPL_FAR DBGVAR BapError_et
BAP_BAL_CheckRequestParam(BapInternalParameters_pot apoPars
        , DBGVAR BapRequest_et aeRequest
        ,BapBalCheckDataType_et eCheckDataType);

#ifdef BAP_ASG
BAP_STATIC BAP_IMPL_FAR DBGVAR BapError_et
BAP_BAL_CheckFunctionListAsg(DBGVAR const volatile uint8_t* apData
    , BapLsgRomRow_pot apoLsgRomRow ,  bool_t statusAllActive );
#endif /* #ifdef BAP_ASG */


#ifdef BAP_ASG
BAP_STATIC BAP_IMPL_FAR void
BAP_BAL_ProcessStatusAll(DBGVAR uint32_t au32Length
    , DBGVAR const volatile uint8_t* apData
    , BapLsgRomRow_pot apoLsgRomRow);
#endif /* #ifdef BAP_ASG */


#ifdef BAP_ASG
BAP_STATIC BAP_IMPL_FAR DBGVAR bool_t
BAP_BAL_UpdateCache(BapFctRomRow_pot apoFctRomRow
    , DBGVAR const volatile uint8_t* apData
    , DBGVAR const uint32_t au32Length);
#endif /* #ifdef BAP_ASG */


#ifdef BAP_ASG
BAP_STATIC BAP_IMPL_FAR void
BAP_BAL_UpdateLsgCacheStatus(DBGVAR BapLsgRomRow_pot apoLsgRomRow);
#endif /* #ifdef BAP_ASG */

#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>

/* Definition (Implementierung) von statischen Funktionen */

/**
 *  Diese Funktion prueft ob der eingegebene Datatype ein skalierbarer Typ ist.
 *  Skalierbare Typen sind BapChkDt_ScalarIn und BapChkDt_ScalarOut.
 *
 *  @param eScalarType gibt an, ob es sich bei dem Pruefling um einen skalaren Datentyp handelt
 *
 *  @retval BAP_TRUE
 *      der Datentyp ist skalierbar (BapChkDt_ScalarIn oder BapChkDt_ScalarOut)
 *  @retval BAP_FALSE
 *      die Datentyp ist nicht skalierbar (BapChkDt_VariableIn, BapChkDt_VariableOut, BapChkDt_Void)
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
static BAP_IMPL_FAR DBGVAR bool_t BAP_BAL_CheckIsScalar(BapBalCheckDataType_et eScalarType)
{
    bool_t bIsScalar;
#ifdef BAP_FSG
    if (BapChkDt_ScalarInit == eScalarType)
    {
        eScalarType = BapChkDt_ScalarIn;
    }
    else if (BapChkDt_VariableInit == eScalarType)
    {
        eScalarType = BapChkDt_VariableIn;
    }
    else { /* andere Init Typen existieren nicht */ }
#endif /* #ifdef BAP_FSG */

    if((BapChkDt_ScalarIn != eScalarType) && (BapChkDt_ScalarOut != eScalarType))
    {
        bIsScalar = BAP_FALSE;
    }
    else /* BapChkDt_VariableIn, BapChkDt_VariableOut und BapChkDt_VoidIn sind kein skalierbarer typ */
    {
        bIsScalar = BAP_TRUE;
    }
    return bIsScalar;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>

/**
 *  2012-05-16 WWU: Reduktion der zykronmatischen Komplexitaet
 *  Diese Funktion prueft ob die Eingabeparameter von BAP_BAL_CheckRequest gueltig sind.
 *
 *  @param apoPars, Zeiger der BapInternalParameter
 *
 *  @param aeRequest gibt die zu pruefener RequestTyp an
 *
 *  @param eCheckDataType gibt die zu pruefener DataTyp an
 *
 *  @retval BapErr_OK
 *      alle Parameter sind gueltig
 *  @retval BapErr_InvalidArg
 *      Die Eingabeparameter sind ungueltig oder nicht zulaessig.
 *  @retval BapErr_InvalidState
 *      Das betroffene LSG ist in falschem Zustand.
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
static
BAP_IMPL_FAR DBGVAR BapError_et
BAP_BAL_CheckRequestParam(BapInternalParameters_pot apoPars
        , DBGVAR BapRequest_et aeRequest
        , BapBalCheckDataType_et eCheckDataType)
{
    DBGVAR BapError_et eResult = BapErr_OK;
    BapLayerLsgStatus_et eLsgStatus = BapLayerLsgStat_Running;

    /* Pruefen ob die Funktion existiert oder gueltig ist */
    if( NULL == apoPars->poFctRomRow )
    {
        eResult = BapErr_InvalidArg;
    }
    else
    {
        /* Ueberpruefe Zustandsmaschine:
         * Im FSG darf Scalar-/VariableInit in Initialized Zustand verwendet werden.
         * Ansonsten muss das betroffene LSG in Running.
         */
#ifdef BAP_FSG
        if ( (BapChkDt_ScalarInit == eCheckDataType) || (BapChkDt_VariableInit == eCheckDataType))
        {
            eLsgStatus = BapLayerLsgStat_Initialized;
        }
#endif /* #ifdef BAP_FSG */
        if(eLsgStatus != apoPars->poLsgRomRow->poLsgRamRow->eLsgStatus)
        {
            eResult =  BapErr_InvalidState;
        }
        else if( ( BAP_FALSE == BAP_BAL_CheckIfFunctionIsValid(apoPars->poFctRomRow->fctId, apoPars->poLsgRomRow->poLsgRamRow->BAP_aru8FunctionList) )
                && (BapLayerLsgStat_Initialized != apoPars->poLsgRomRow->poLsgRamRow->eLsgStatus) )
        {
            eResult = BapErr_InvalidArg;
        }
        else
        {
            /* do nothing */
        }

        /* Im FSG ist es verboten einen Request auf Fct.ID 0-7 zu schicken, im ASG ist es OK */
        /* Nur erlaubt im Nicht initialisierten Zustand */
        /* Nur im Initzustand duerfen BAP interne Fct-Ids gesetzt werden */
#if defined(BAP_FSG) /* nur im FSG */
#if defined(BAP_ASG) && defined(BAP_FSG) /* oder im KombiFSG */
        if (BapSG_FSG == apoPars->poLsgRomRow->eSGType)
#endif
        {
            if( ((uint8_t)BAP_SMALLEST_ALLOWED_FCTID_IN_FSG > BAP_BINARY_ID(apoPars->fctId))
                && (BapLayerLsgStat_Initialized != apoPars->poLsgRomRow->poLsgRamRow->eLsgStatus))
            {
                eResult = BapErr_InvalidArg;
            }
        }
#endif /* defined(BAP_ASG) && defined(BAP_FSG) */
    }


    if(BapErr_OK == eResult)
    {
        /* Pruefen OpCode Gueltigkeit */
        if (BapReq_Invalid == aeRequest)
        {
            /* Requesttyp: InitSendBuffer/CacheGetRequest. Fuer InitSendBuffer richtigen OpCode eintragen.
               Bei CacheGetRequest wird der OpCode nicht benoetigt */
            apoPars->eOpCode = BapOp_PropHeartbeatStatus;
        }
        else
        {
#if defined(BAP_ASG) && defined(BAP_FSG)
            apoPars->eOpCode = BAP_Request2OpCodeMatrix[apoPars->poLsgRomRow->eSGType][apoPars->poFctRomRow->eFunctionClass][aeRequest];
#else
            apoPars->eOpCode = BAP_Request2OpCodeMatrix[apoPars->poFctRomRow->eFunctionClass][aeRequest];
#endif
            /* Pruefen ob der OpCode erlaubt ist */
            /*lint -e701*/ /* Info 701: Shift left of signed quantity (int). But BAP_BIT0 is cast into uint8_t at definition and here.
             * 					So false warning */
            if ((uint8_t)0 == (apoPars->poFctRomRow->u8OpCodeSendMask & ((uint8_t)((uint8_t)BAP_BIT0<<(uint8_t)apoPars->eOpCode)))  )
            /*lint +e701*/
            {
                eResult = BapErr_InvalidArg;
            }
        }
    }

    return eResult;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>

/**
 *  Diese Funktion prueft ob zu einem konfigurierten Datentyp die angegebenen
 *  Werte passen und gibt BAP_FALSE im Fehlerfall zurueck.
 *
 *  @param aeDataType bezeichnet den konfigurierten Datentyp
 *
 *  @param au16BSSize gibt bei dem nicht skalaren Datentypen ByteSequenz die Groesse an
 *      Wird bei skalaren Typen ignoriert.
 *
 *  @param au16DataSize gibt die zur pruefende Datengroesse an
 *
 *  @param aIsSend True wenn Pruefung fuer Request, False bei Empfang
 *      Dadurch kann gewaehrleistet werden, dass Processing als IndVoid an App gemeldet wird
 *
 *  @param eScalarType gibt an, ob es sich bei dem Pruefling um einen skalaren Datentyp handelt
 *
 *  @retval BAP_TRUE
 *      der Datentyp passt zu den Werten
 *  @retval BAP_FALSE
 *      die Pruefung ist fehlgeschlagen
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
static BAP_IMPL_FAR DBGVAR bool_t
BAP_BAL_CheckDatatype(DBGVAR BapDataType_et aeDataType
    , DBGVAR uint32_t au32BSSize
    , DBGVAR uint32_t au32DataSize
    , DBGVAR bool_t aIsSend
    , DBGVAR BapBalCheckDataType_et eScalarType)
{
    bool_t bResult = BAP_TRUE;
    bool_t bIsScalar = BAP_BAL_CheckIsScalar(eScalarType);

    switch(aeDataType)
    {
        /* pruefen des Void Datentyps: Ist ein Skalartyp mit Laenge=0 */
        case BapDt_Void:
        /* pruefen von skalaren Datentypen: muss exakt passen oder void sein */
        case BapDt_Int8:
#ifdef BAP_USES_DATATYPE_16
        case BapDt_Int16:
#endif /* BAP_USES_DATATYPE_16 */
#ifdef BAP_USES_DATATYPE_32
        case BapDt_Int32:
#endif /* BAP_USES_DATATYPE_32 */
            if( (((uint16_t)aeDataType != au32DataSize) || (BAP_FALSE == bIsScalar))
                    && (BapChkDt_VoidIn != eScalarType)
              )
            {
                bResult = BAP_FALSE;
            }
            break;
        /* pruefen von FixedBytesequenzen: Laenge muss exakt passen oder void, was immer als skalar angesehen wird */
        /* aIsSend Bedingung: Nur in Senderichtung muss alles passen */
        /* In Empfangsrichtung ist Processing mit anderer Kennung moeglich */
        case BapDt_FixedByteSequence:
            if( (BAP_TRUE == bIsScalar)
                || ((au32BSSize != au32DataSize) && (BAP_TRUE == aIsSend))
              )
            {
                bResult = BAP_FALSE;
            }
            break;
#ifdef BAP_USES_SEGMENTATION
        /* pruefen von Bytesequenzen: Laenge muss in Puffer passen oder void, was immer als skalar angesehen wird */
        case BapDt_ByteSequence:
            if( (BAP_TRUE == bIsScalar)
                || (au32BSSize < au32DataSize)
              )
            {
                bResult = BAP_FALSE;
            }
            break;
#endif /* BAP_USES_SEGMENTATION */
        default:
        /* unbekannten Datentyp verbieten */
            bResult = BAP_FALSE;
            break;
    }
    return bResult;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


#ifdef BAP_ASG
/**
 *  Diese Funktion prueft im ASG die FunctionList Botschaft. Es wird geprueft, ob
 *  die Liste des FSG gleich oder ein Subset vom ASG ist (alle FctIds vom FSG muessen
 *  auch im ASG konfiguriert sein).
 *
 *  Aktionen:
 *      - Bei einer fehlerhaften FunctionList und wenn es sich um eine StatusALL Nachricht handelt wird eine ErrorIndication mit dem
 *        Fehlerwert BapErr_IncompatibleDataSpecification gemeldet.
 *
 *  @param apData beinhaltet die FunctionList Botschaft selbst
 *
 *  @param apoLsgRomRow beinhaltet ein Zeiger auf das zugehoerige LSG
 *
 *  @retval BapErr_OK Funktionsliste ist zulaessig
 *  @retval BapErr_ReceivedDataLost falls ein kompatibles Superset definiert wurde (ist zulaessig)
 *  @retval BapErr_IncompatibleDataSpecification falls ein inkompatibles Superset definiert wurde.
 *
 *  @remark Der Zeiger apoLsgRomRow muss vor Aufruf dieser Funktion auf NULL
 *          geprueft sein. Ein Aufruf mit NULL-Zeiger ist verboten!
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_STATIC BAP_IMPL_FAR DBGVAR BapError_et BAP_BAL_CheckFunctionListAsg(
        DBGVAR const volatile uint8_t apData[], BapLsgRomRow_pot apoLsgRomRow,
        bool_t statusAllActive)
{
    DBGVAR fctId_t u8CurrentFctId;
    DBGVAR BapError_et eFctListOk = BapErr_OK;
    /*lint -e9034*//* MISRA_2012_REQ_10.3 : PC-Lint 9.00L throws a warning due to Tool bug. Hence, this warning has been deactivated.
     * Documented with a mail from the Lint team in the SSWCCB-2522_BAP-Entwicklung auf MISRA2012 umstellen folder */
    /* MISRA_2012_REQ_10.5 : 0 fit in enum, so no risk arise.  */
    DBGVAR fctId_t u8HighestASGFctId = (fctId_t) 0;
    /*lint +e9034*/
    uint8_t u8CurrentFctBit = (uint8_t) 0;
    uint8_t u8FctRomRowIdx;

    /* In diese Tabelle werden die vom ASG unterstuetzten Funktionen eingetragen */

    volatile const uint8_t * pSourceData;
    DBGVAR uint8_t *pDestData = &aru8LocalFunctionList[BAP_FCTLIST_LASTINDEX];

    /*lint -esym(613,apoLsgRomRow)*/
    BAP_ASSERT(NULL != apoLsgRomRow);
    /*lint -esym(613,apData)*/
    BAP_ASSERT(NULL != apData);

    /* Im ASG kann ein Subset der verfuegbaren Funktionsliste im ROM hinterlegt sein */
    /* Das FSG kann ebenso ein Subset der im ASG verfuegbaren Funktionen als neue Funktionsliste uebertragen */
    /* Ebenso darf das FSG ein Superset der im ASG verfuegbaren Funktionen senden, falls alle zusaetzlichen */
    /* Funktionen hoehere FctIds haben wie die hoechste FctId im ASG. In diesem Falle wird die Schnittmenge */
    /* beider Funktionslisten als neue Funktionsliste gewaehlt */

    pSourceData = &apData[BAP_FCTLIST_LASTINDEX];
    /*lint -e9087*//* MISRA_2012_REQ_11.3 : 1st argument of MEMSET of type uint8_t* is
     * implicitly cast to void*. Won't cause any problem as this array will be updated in the following for loop.*/
    MEMSET(aru8LocalFunctionList, 0, BAP_FCTID_FCTLIST_SIZE);
    /*lint +e9087*/

    /* ermittle die vom ASG unterstuetzte Funktionsliste */
    for (u8FctRomRowIdx = (uint8_t) 0;
            u8FctRomRowIdx < apoLsgRomRow->u8FctRomTableSize; u8FctRomRowIdx++)
    {
        uint8_t u8FctId =
        BAP_BINARY_ID (BAP_FctRomTables[apoLsgRomRow->u16FctRomIndex
                + u8FctRomRowIdx].fctId);

        aru8LocalFunctionList[u8FctId / BAP_BYTE] |= (BAP_BIT7 >> (u8FctId % BAP_BYTE));
    }

    /* Prufe zunaechst die Zulaessigkeit der neuen FunctionList und entferne */
    /* die FctIds aus dem Empfangspuffer, welche ein Superset definieren     */

    /*lint -e9027*//* MISRA_2012_REQ_10.1 : the -- operator should not be used with an enum type. Here, the enum is used like a integer which is initialised
     * at 63 and is decremented until BAP_FCTID_FCTLIST. u8CurrentFctId is referred several times in the code
     * and the code structure has to be modified considerably in order to remove this warning. Hence, the warning was not removed */
    /*lint -e9034*//* MISRA_2012_REQ_10.3 : PC-Lint 9.00L throws a warning due to Tool bug. Hence, this warning has been deactivated.
     * Documented with a mail from the Lint team in the SSWCCB-2522_BAP-Entwicklung auf MISRA2012 umstellen folder */
    /* MISRA_2012_REQ_10.5 : BAP_FCTID_FCTLIST fit in enum and is already cast at declaration, so no risk arise.  */
    /* MISRA_2012_REQ_10.5 : (64-1) fit in enum, so no risk arise.  */
    for (u8CurrentFctId = (fctId_t) BAP_MAX_FCT_ID;
            (fctId_t) u8CurrentFctId >= (fctId_t) BAP_FCTID_FCTLIST;
            (u8CurrentFctId)--)/* beginne mit 63 und hoer nach der FctList auf */
    /*lint +e9034*/
    /*lint +e9027*/
    {
        if ((uint8_t) 0 == u8CurrentFctBit)
        {
            u8CurrentFctBit++; /* hat danach den Wert 0x01 */

            /* const_cast<> ist erforderlich. */
            /* Ungefaehrlich in BAP 1.4, da danach niemand mehr auf den Empfangspuffer zugreift. */
            /* MISRA_2012_REQ_10.5 : No risk arise, because 8 fit in enum  */
            pSourceData = &apData[(fctId_t) u8CurrentFctId / (fctId_t) BAP_BYTE];
            pDestData = &aru8LocalFunctionList[(fctId_t) u8CurrentFctId
                    / (fctId_t) BAP_BYTE];
        }

        /* existiert diese Funktion im ASG? */
        if ((uint8_t) 0 == (u8CurrentFctBit & (*pDestData)))
        {

            /* Bit gesetzt in neuer Fct.list, dann muss es auch im ASG unterstuetzt werden, falls die neue
             * Funktion nicht hinter der hoechsten unterstuetzten Funktion des ASG liegt
             */
            if ((uint8_t) 0 != (u8CurrentFctBit & (*pSourceData)))
            {
                /* WWU 25-04-2012: [AP-6] Rueckrollen wegen Kompabilitaetsproblem
                 * WWU 26-05-2011: Nach [A-6]: Superset in der Funktionslist als Fehler behandeln
                 */
            	/* MISRA_2012_REQ_10.5 : 0 fit in enum, so no risk arise.  */
                if ((fctId_t) 0 != (fctId_t) u8HighestASGFctId)
                {
                    eFctListOk = BapErr_IncompatibleDataSpecification;
                }
                else
                {
                    eFctListOk = BapErr_ReceivedDataLost;
                }
            }
        }
        else
        {
            /* Merke die hoechste FctId des ASG um inkompatible Erweiterungen zu erkennen */
        	/* MISRA_2012_REQ_10.5 : 0 fit in enum, so no risk arise.  */
            if ((fctId_t) 0 == (fctId_t) u8HighestASGFctId)
            {
                u8HighestASGFctId = u8CurrentFctId;
            }

            /* Falls in neuer Funktionliste das Bit nicht gesetzt ist, Bit im ASG ausmaskieren */
            if ((uint8_t) 0 == (u8CurrentFctBit & (*pSourceData)))
            {
                *pDestData ^= u8CurrentFctBit;
                if (BapErr_OK == eFctListOk)
                {
                    eFctListOk = BapErr_ReceivedDataLost;
                }
            }
        }
        u8CurrentFctBit = u8CurrentFctBit + u8CurrentFctBit; /* schiebe Bit nach Links */
    }

    /*
     * SSWCCB[800] Feature: Nur wenn die FctList uber GetALL Botschaft kommt ist die Fehlermeldung
     * BapErr_IncompatibleDataSpecification relevant. Wenn die Botschaft im Zuge einer Heartbeat Botschaft kommt, dann
     * kann die GetALL Botschaft empfangen werden ohne das es zu Problemen beim Decodieren kommmt.
     * Unterscheidung kommt ueber Parameter "statusAllActive"
     */
    if ((BapErr_IncompatibleDataSpecification == eFctListOk)
            && (BAP_FALSE != statusAllActive))
    {
        /* Fehlerhafte Datenfestlegung an die Applikation melden */
        /*lint -e9034*//*MISRA_2012_REQ_10.3 : Warning deactivated. Refers to bap_types.h, definition of BAP_FCTID_FCTLIST*/
    	/* MISRA_2012_REQ_10.5 : No risk arise, because BAP_FCTID_FCTLIST is already cast at declaration and fit in enum. */
        BAP_IndicationError(apoLsgRomRow->lsgId, BAP_FCTID_FCTLIST,
                BapErr_IncompatibleDataSpecification);
        /*lint +e9034*/
        BAP_DBG_DataDefinitionError(apoLsgRomRow->lsgId);
    }

    /*
     * SSWCCB[800] Nur wenn die FctList gueltig ist dann uebernahme der FctList.
     */

    if (BapErr_IncompatibleDataSpecification != eFctListOk)
    {
        /* FunctionList uebernehmen */
        /*lint -e9087*//* MISRA_2012_REQ_11.3 : 1st and 2nd arguments of MEMCPY are of types (uint8_t*).
         * They are implicitly cast to (void*). The memory is packed because it is uint8_t so there should be no problem to copy.*/
        MEMCPY(apoLsgRomRow->poLsgRamRow->BAP_aru8FunctionList,
                aru8LocalFunctionList, BAP_FCTID_FCTLIST_SIZE); /*lint !e668*//* (void*)apData!=NULL */
        /*lint +e9087*/
    }

    return eFctListOk;
    /*lint +esym(613,apData)*/
    /*lint +esym(613,apoLsgRomRow)*/
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* #ifdef BAP_ASG */


#ifdef BAP_ASG
/**
 *  Diese Funktion verarbeitet eine StatusAll-Block Nachricht. Entsprechend der
 *  FunctionList werden die einzelnen Daten ueber die Konfigurierte Daten-Groesse
 *  aus dem Block herausgeschnitten und falls ein Cache fuer die FctId vorhanden
 *  ist abgelegt. Bis eine FunctionList vom FSG da ist, wird mit der vom ASG
 *  gearbeitet.
 *  Als Sonderfall wird die FctId Heartbeat behandelt. Die Daten werden hier
 *  an den BPL geschickt, um dort die Heartbeat-Ueberwachung zu starten.
 *  Ist die GetAll Nachricht fehlerhaft (z.B. falsche Laenge) wird der Gesamtcache
 *  ungueltig und die Fehlermeldung BapErr_GetAllMessageCorrupted gemeldet.
 *
 *  @param au32Length gibt die Laenge der Daten an.
 *
 *  @param apData beinhaltet die FunctionList Botschaft selbst
 *
 *  @param apoLsgRomRow beinhaltet ein Zeiger auf das zugehoerige LSG
 *
 *  @remark Der Zeiger apoLsgRomRow muss vor Aufruf dieser Funktion auf NULL
 *          geprueft sein. Ein Aufruf mit NULL-Zeiger ist verboten!
 *
 *  Diese Funktion hat 9 OutgoingCalls (max.7), 7 ControlNestingLayers (max.4)
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_STATIC BAP_IMPL_FAR void
BAP_BAL_ProcessStatusAll(DBGVAR uint32_t au32Length
    , DBGVAR const volatile uint8_t apData[]
    , BapLsgRomRow_pot apoLsgRomRow
)
{
    DBGVAR uint8_t u8TableSize;
    DBGVAR uint8_t u8FctIndex;
    BapFctRomRow_pot poFctRomRow;
    DBGVAR uint32_t u32GetAllOffset;
    DBGVAR BapError_et eError = BapErr_OK;
    DBGVAR BapError_et eCompatibleExtension = BapErr_OK;

    /*lint -esym(613,apoLsgRomRow)*/
    /*lint -esym(831,apoLsgRomRow)*/
    BAP_ASSERT(NULL != apoLsgRomRow);
    /*lint -esym(613,apData)*/
    BAP_ASSERT(NULL != apData);

    u8TableSize = apoLsgRomRow->u8FctRomTableSize;

    u32GetAllOffset =(uint32_t) 0;
    /* Schleife solange alle Fct-Caches gueltig sind und nicht Ende der Tabelle erreicht */
    for(u8FctIndex=(uint8_t)0; (u8FctIndex<u8TableSize) && (BapErr_OK == eError); ++u8FctIndex)
    {
        poFctRomRow = &BAP_FctRomTables[apoLsgRomRow->u16FctRomIndex + u8FctIndex];
        /* Ist die FunctionId im GetAll enthalten? */
        if(   ( BAP_TRUE == BAP_BAL_CheckIfFunctionIsValid(poFctRomRow->fctId, apoLsgRomRow->poLsgRamRow->BAP_aru8FunctionList) )
                && (BapFctCls_Property == poFctRomRow->eFunctionClass) ) /* Es werden nur Properties uebertragen */
        {
            uint32_t u32Size = poFctRomRow->u32RxSize;

            /* Ermittle Laenge des Eintrages */
            if(BapDt_ByteSequence == poFctRomRow->eRxDataType)
            {
                if(au32Length < (uint32_t) (u32GetAllOffset + BAP_HEADER_BYTES_NONSEG))
                {
                    /* Is ByteSequence, aber nicht genuegend Daten */
                    eError = BapErr_GetAllMessageCorrupted;
                }/* BAP 1.6.2: Pruefung ob Laenge Information in Functionlist erhaelt oder nicht*/
                else if( ((uint16_t)0 == (apData[u32GetAllOffset] & (uint16_t)BAP_BIT5)) /* Ist der 5. Bit gesetzt? Nein-> FctList mit Laenge Info */
                        || ((uint8_t)BAP_FCTID_FCTLIST != BAP_BINARY_ID(poFctRomRow->fctId))
                    )
                {
                    /* Normaler Fall */
                    /* bei ByteSequences wird die Laenge in den ersten 2 Bytes [Lo,Hi] uebertragen */
                    u32Size = (uint32_t)(((uint32_t)apData[u32GetAllOffset+ BAP_SECOND_HEADER_BYTE]) << BAP_BYTE);
                    u32Size += (uint32_t) apData[u32GetAllOffset];

                    /* Offset auf Daten nach Laenge setzen */
                    u32GetAllOffset += BAP_HEADER_BYTES_NONSEG;
                    if (u32Size > poFctRomRow->u32RxSize) /* Message ist groesser als Rx seite */
                    {
                        /* Fehler, Schleife abbrechen */
                        eError = BapErr_GetAllMessageCorrupted;
                    }
                }else{
                    /* Spezieller Fall fuer ab BAP 1.6.2: Funktionslist ohne Laenge-Info */
                    /* Wird auch akzeptiert. Nix zu tun. */
                }
            }


            if((u32GetAllOffset + u32Size) > au32Length) /* Sind nicht ausreichend gueltige Daten vorhanden */
            {
                /* Fehler, Schleife abbrechen */
                eError = BapErr_GetAllMessageCorrupted;
            }

            if(BapErr_OK == eError)
            {
                /* Sonderfall bei der Behandlung von HEARTBEAT, da hier der BPL informiert werden muss */
            	/* MISRA_2012_REQ_10.5 : 4 fit in enum and BAP_FCTID_HEARTBEAT is already cast at declaration, so no risk arise.  */
                if((fctId_t)poFctRomRow->fctId == BAP_FCTID_HEARTBEAT)
                {
                    BAP_BPL_ProcessHBMsg(apoLsgRomRow, apData[u32GetAllOffset]);
                }

                /* Uebernehme die FunctionList, falls sie gueltig ist */
                /* MISRA_2012_REQ_10.5 : 3 fit in enum and BAP_FCTID_FCTLIST is already cast at declaration, so no risk arise.  */
                if( ((fctId_t)poFctRomRow->fctId == BAP_FCTID_FCTLIST)) {
                    eCompatibleExtension = BAP_BAL_CheckFunctionListAsg(&apData[u32GetAllOffset], apoLsgRomRow , BAP_TRUE );
                    /*lint -esym(960,33) Seiteneffekt ist nur gewuenscht, wenn es eine FunctionList ist */
                    if (BapErr_IncompatibleDataSpecification == eCompatibleExtension )
                    /*lint +esym(960,33) */
                    {
                        eError = BapErr_GetAllMessageCorrupted;
                    }
                }

                /* nur wenn im ASG ein Cache fuer diese FctId vorhanden ist und der */
                /* Cache nicht valid ist, ein Update durchfuehren. Verwerfen des Datums wenn Valid */
                /* wenn kein Cache vorhanden, werden die Daten ueberlesen */

                /* *(BapBalDataStatus_et*)poFctRomRow->poBalRamRow enthaelt den eDataStatus*/
                if((NULL != poFctRomRow->poBalRamRow)
                        && (BapBalDataStat_Valid != poFctRomRow->poBalRamRow->eDataStatus) )
                {
                    /* Information ueber eine Werteaenderung ist unwichtig hier */
                    (void) BAP_BAL_UpdateCache(poFctRomRow, &apData[u32GetAllOffset], u32Size);
                }

                /* Offset auf naechsten Wert im GetAll-Block setzen */
                u32GetAllOffset =u32GetAllOffset + u32Size;
            }
        } /* Naechste Funktion */
    }

    /* Gesamt Cache Check */
    if( (BapErr_OK != eError)
        ||((u32GetAllOffset < au32Length) && (BapErr_ReceivedDataLost != eCompatibleExtension) )
      )
    {
        /* Korrupte GETALL-Nachricht an die Applikation melden */
        /*lint -e9034*/ /*MISRA_2012_REQ_10.3 : Warning deactivated. Refers to bap_types.h, definition of BAP_FCTID_GETALL */
    	/* MISRA_2012_REQ_10.5 : No risk arise, because BAP_FCTID_GETALL is already cast at declaration and fit in enum. */
        BAP_IndicationError(apoLsgRomRow->lsgId, BAP_FCTID_GETALL, BapErr_GetAllMessageCorrupted);
        /*lint +e9034*/
        BAP_DBG_GetAllMsgCorruptedErr(apoLsgRomRow->lsgId);
        /* Nach einem korrupten STATUSALL muss der teilweise ueberschriebene Cache ungueltig werden */
        BAP_BAL_InvalidateCache(&*apoLsgRomRow);    /* &* behebt Lint-Analyse-Problem */
    }
    else
    {
        /* Gesamt-Cache-Gueltigkeit neu berechnen */
        BAP_BAL_UpdateLsgCacheStatus(apoLsgRomRow);
    }
    return;
    /*lint +esym(613,apData)*/
    /*lint +esym(613,apoLsgRomRow)*/
    /*lint +esym(831,apoLsgRomRow)*/
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* #ifdef BAP_ASG */


#ifdef BAP_ASG
/**
 *  Diese Funktion aktualisiert den Cache-Speicher mit den neuen Werten fuer
 *  ein einzelnen Cache-Eintrag. Der Zustand des Gesamt LSG Caches muss anschliessend
 *  ueber die Funktion BAP_BAL_UpdateLsgCacheStatus neu berechnet werden.
 *  Die Anpassung von Little/Big-Endian muss bereits geschehen sein.
 *  Ein vorhandener Cache fuer die FunctionID muss vor dem Aufruf bereits
 *  sichergestellt sein.
 *
 *  @param apoFctRomRow gibt die BapFctRomRow der betreffenden FctId an.
 *
 *  @param apData beinhaltet ein Byte-Array auf die zu verarbeiteten Daten.
 *
 *  @param au16Length gibt die Laenge der Daten an.
 *
 *  @returns
 *      BAP_FALSE wenn sich der uebergebende Wert vom urspruenglichen unterscheidet,
 *      BAP_TRUE  wenn identisch
 *
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_STATIC BAP_IMPL_FAR DBGVAR bool_t
BAP_BAL_UpdateCache(BapFctRomRow_pot apoFctRomRow
    , DBGVAR const volatile uint8_t apData[]
    , DBGVAR const uint32_t au32Length)
{
    /*lint -esym(613,apoFctRomRow)*/
    DBGVAR BapBalRamRow_pot pBalRamRow = apoFctRomRow->poBalRamRow;
    DBGVAR bool_t bValueHasChanged = BAP_FALSE;
    DBGVAR bool_t bUpdateCache = BAP_TRUE;
    DBGVAR int temp;
    BAP_ASSERT(NULL != apData);


    switch(apoFctRomRow->eRxDataType)
    {
        case BapDt_Int8:
            if (pBalRamRow->u8Value !=  apData[0])
            {
                pBalRamRow->u8Value = apData[0] ;
                bValueHasChanged = BAP_TRUE;
            }
            if(BapBalDataStat_Valid != pBalRamRow->eDataStatus)
            {
                pBalRamRow->eDataStatus = BapBalDataStat_Valid;
            }
            break;
        case BapDt_Int16:
            if (pBalRamRow->u16Value != BAP_BAL_DataStreamToInt16(apData) )
            {
                pBalRamRow->u16Value = BAP_BAL_DataStreamToInt16(apData) ;
                bValueHasChanged = BAP_TRUE;
            }
            if(BapBalDataStat_Valid != pBalRamRow->eDataStatus)
            {
                pBalRamRow->eDataStatus = BapBalDataStat_Valid;
            }
            break;
        case BapDt_Int32:
            if (pBalRamRow->u32Value != BAP_BAL_DataStreamToInt32(apData) )
            {
                pBalRamRow->u32Value = BAP_BAL_DataStreamToInt32(apData) ;
                bValueHasChanged = BAP_TRUE;
            }
            if(BapBalDataStat_Valid != pBalRamRow->eDataStatus)
            {
                pBalRamRow->eDataStatus = BapBalDataStat_Valid;
            }
            break;
        case BapDt_FixedByteSequence:
        case BapDt_ByteSequence:
            if (pBalRamRow->oBufferWithLength.u32Length == au32Length)
            {
				/*lint -e668*//* (void*)apData != NULL */
				/*lint -esym(960,33) MEMCMP hat keinen Seiteneffekt */
				/*lint -e960*/ /* MISRA2004: attempt to cast away const/volatile from a pointer or reference. See below*/
				/*lint -e9087*/ /* MISRA_2012_REQ_11.3 : 1st and 2nd arguments of MEMCPY are of types (uint8_t*).
								 * They are implicitly cast to (void*). The memory is packed because it is uint8_t so there should be no problem to copy.*/
				/*lint -e9005*/ /* MISRA_2012_REQ_11.8 : apData is a const uint8_t*, assigned to const void*.
								 * This is used as a source array so it will not be modified.*/
				temp = MEMCMP(pBalRamRow->oBufferWithLength.paru8Buffer, apData, au32Length);
				/*lint +e9005*/
				/*lint +e9087*/
				if(0 == temp )
				{
					bUpdateCache = BAP_FALSE;
				}
            }
            if (BAP_TRUE == bUpdateCache)
			{
				/*lint -e9087*/ /* MISRA_2012_REQ_11.3 : 1st and 2nd arguments of MEMCPY are of types (uint8_t*).
								 * They are implicitly cast to (void*). The memory is packed because it is uint8_t so there should be no problem to copy.*/
				/*lint -e9005*/ /* MISRA_2012_REQ_11.8 : apData is a const uint8_t*, assigned to const void*.
								 * This is used as a source array so it will not be modified.*/
				MEMCPY(pBalRamRow->oBufferWithLength.paru8Buffer, apData, au32Length);
				/*lint +e9005*/
				/*lint +e9087*/
				pBalRamRow->oBufferWithLength.u32Length = au32Length;
				bValueHasChanged = BAP_TRUE;
			}
            /*lint +e960*/
            /*lint +esym(960,33) */
            /*lint +e668*/
            if(BapBalDataStat_Valid != pBalRamRow->eDataStatus)
            {
                pBalRamRow->eDataStatus = BapBalDataStat_Valid;
            }
            break;
        default:
            /* MISRA 2012 warning removal Nothing to be done */
            break;
    }

    return bValueHasChanged;
    /*lint +esym(613,apoFctRomRow)*/
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* #ifdef BAP_ASG */


#ifdef BAP_ASG
/**
 *  Diese Funktion aktualisiert den Gesamt-Cache-Status des adressierten LSG,
 *  in dem alle Einzel-Caches auf valid geprueft werden und falls alle valid sind
 *  auch der Gesamt-Cache-Status valid wird. Wird ein Cache einer FunktionID
 *  als invalid gefunden, so wird der Gesamt-Cache-Status invalid.
 *  Fuer die Ueberpruefung der Cache-Gueltigkeit werden nur FctIds in Betracht
 *  gezogen, die in der derzeitigen FunctionList enthalten sind.
 *
 *  @param apoLsgRomRow bezeichnet die RomRow das logische Steuergeraet.
 *
 *  @remarks
 *      Falls das LSG nicht gefunden wird, wird der Update-Aufruf ignoriert.
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_STATIC BAP_IMPL_FAR void
BAP_BAL_UpdateLsgCacheStatus(DBGVAR BapLsgRomRow_pot apoLsgRomRow)
{
    DBGVAR uint8_t u8TableSize;
    DBGVAR uint8_t u8FctIndex;
    DBGVAR bool_t bLsgCacheStatus = BAP_TRUE;

    /* Eintrag des LSGs holen */
    if(NULL != apoLsgRomRow)
    {
        /* FunctionList holen */
        /* FunctionList-Eintrag immer gueltig: entweder durch ASG FctList initial, oder durch uebertragene FSG FctList */
        /*lint -e9087*/ /* MISRA_2012_REQ_11.3 : 1st and 2nd arguments of MEMCPY are of types (uint8_t*).
                         * They are implicitly cast to (void*). The memory is packed because it is uint8_t so there should be no problem to copy.*/
        MEMCPY(aru8LocalFunctionList,apoLsgRomRow->poLsgRamRow->BAP_aru8FunctionList,BAP_FCTID_FCTLIST_SIZE);
        /*lint +e9087*/
        u8TableSize = apoLsgRomRow->u8FctRomTableSize;
        u8FctIndex = (uint8_t)0;
        /* Schleife solange alle Fct-Caches gueltig sind und nicht Ende der Tabelle erreicht */
        while((u8FctIndex < u8TableSize) && (BAP_TRUE == bLsgCacheStatus))
        {
            BapFctRomRow_pot poFctRomRow = &BAP_FctRomTables[apoLsgRomRow->u16FctRomIndex + u8FctIndex];
            /* Ist der Cache fuer eine Funktion ungueltig, dann ist der ganze Cache ungueltig */
            /* MISRA_2012_REQ_14.3 : "(BAP_BINARY_ID(poFctRomRow->fctId) < (uint8_t)64)" is not invariant
             * but always true except in case of configuration issue or running issue. */
            if((NULL != poFctRomRow->poBalRamRow)
                && (BAP_BINARY_ID(poFctRomRow->fctId) > (uint8_t)BAP_FCTID_GETALL)     /* GETALL ausschliessen */
                && (BAP_BINARY_ID(poFctRomRow->fctId) <= (uint8_t)BAP_MAX_FCT_ID)    /*lint !e650 enums haben mindestens 8 bit *//* keine internen FctIds (CacheStatus) */
                /* Bit in der FctList holen, welches angibt ob die FctId vom FSG relevant ist */
                && ((uint8_t)0 != (aru8LocalFunctionList[BAP_BINARY_ID(poFctRomRow->fctId) / BAP_BYTE] & (BAP_BIT7 >> (BAP_BINARY_ID(poFctRomRow->fctId) % BAP_BYTE))) )
                && (BapBalDataStat_Invalid == poFctRomRow->poBalRamRow->eDataStatus)) /*(BapBalDataStatus_et*)poFctRomRow->poBalRamRow gibt eDataStatus zurueck*/
            {
                bLsgCacheStatus = BAP_FALSE;
            }
            else
            {
                ++u8FctIndex;
            }
        }
        /* Hat sich die Gueltigkeit des Caches veraendert? (! ist erforderlich, damit es fuer 1 != -1 auch funktioniert) */
        if ( bLsgCacheStatus != ((bool_t)apoLsgRomRow->poLsgRamRow->fState.fCacheValid))
        {
            /* nur Aenderungen melden */
            apoLsgRomRow->poLsgRamRow->fState.fCacheValid = bLsgCacheStatus;
            if (BAP_FALSE != bLsgCacheStatus)
            {
                /*lint -e9034*/ /*MISRA_2012_REQ_10.3 : Warning deactivated. Refers to bap_types.h, definition of BAP_FCTID_GETALL*/
            	/* MISRA_2012_REQ_10.5 : No risk arise, because BAP_FCTID_GETALL is already cast at declaration and fit in enum. */
                BAP_IndicationVoid(apoLsgRomRow->lsgId, BAP_FCTID_GETALL, BapInd_Data);
                /*lint +e9034*/
                /* Setzen der Gesamtcachegueltigkeit */
                apoLsgRomRow->poLsgRamRow->fState.fCacheValid = BAP_TRUE;
                /* Beenden des Retry fuer GetAll */
                /*lint -e9034*/ /*MISRA_2012_REQ_10.3 : Warning deactivated. Refers to bap_types.h, definition of BAP_FCTID_GETALL*/
                /* MISRA_2012_REQ_10.5 : No risk arise, because BAP_FCTID_GETALL is already cast at declaration and fit in enum. */
                if(NULL  != BAP_GetLsgFctRomRow(apoLsgRomRow, BAP_FCTID_GETALL) )
                /*lint +e9034*/
                {
                   /*Beenden des Retry fuer GetAll, nur wenn GetAll definiert ist */
                /*lint -e9034*/ /*MISRA_2012_REQ_10.3 : Warning deactivated. Refers to bap_types.h, definition of BAP_FCTID_GETALL*/
                	/* MISRA_2012_REQ_10.5 : No risk arise, because BAP_FCTID_GETALL is already cast at declaration and fit in enum. */
                BAP_BPL_AbortSend(apoLsgRomRow, BAP_FCTID_GETALL);
                /*lint +e9034*/
                }
                BAP_DBG_SetCacheValidState(apoLsgRomRow->lsgId, BAP_TRUE);
            }
            else
            {
                /* Loeschen der Gesamtcachegueltigkeit */
                apoLsgRomRow->poLsgRamRow->fState.fCacheValid = BAP_FALSE;
                BAP_DBG_SetCacheValidState(apoLsgRomRow->lsgId, BAP_FALSE);
            }
        }
        else
        {
            /* keine Meldung erforderlich */
        }
    }
    return;
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* #ifdef BAP_ASG */

/* Definition (Implementierung) von globalen Funktionen */

/*
 *  Diese Funktion wird in bap_balutil.h dokumentiert.
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_IMPL_FAR DBGVAR BapError_et
BAP_BAL_CheckRequest(BapInternalParameters_pot apoPars
    , DBGVAR BapRequest_et aeRequest
    , BapBalCheckDataType_et eCheckDataType
    )
{
    bool_t bDataTypeCheck;
    BapError_et eResult;

    /*lint -esym(613,apoPars)*/
    BAP_ASSERT(NULL != apoPars);

    apoPars->poLsgRomRow = BAP_GetLsgRomRow(apoPars->lsgId);
    apoPars->poFctRomRow = BAP_GetLsgFctRomRow(apoPars->poLsgRomRow, apoPars->fctId);

    eResult = BAP_BAL_CheckRequestParam(apoPars,aeRequest, eCheckDataType);
    if(BapErr_OK != eResult)
    {
        BAP_DBG_InvalidArgError(apoPars->lsgId);
    }
    else
    {
        /* Pruefen ob der Datentyp erlaubt ist */
        switch(eCheckDataType)
        {
            case BapChkDt_VoidIn:
#ifdef BAP_ASG /* auch Kombigeraet */
                /* bei Get und Abort Datentyp void verwenden statt dem konfigurierten. */
                if((BapReq_DataGet == aeRequest) || (BapReq_Abort == aeRequest))
                {
                    /* BAP_BAL_CheckDatatype(BapDt_Void, BAP_VOID_SIZE, BAP_VOID_SIZE, BAP_TRUE, BapChkDt_VoidIn); immer TRUE!*/
                    bDataTypeCheck = BAP_TRUE;
                }else
#endif /* #ifdef BAP_ASG */
                {
                    bDataTypeCheck = BAP_BAL_CheckDatatype(
                        apoPars->poFctRomRow->eTxDataType
                        , BAP_VOID_SIZE
                        , BAP_VOID_SIZE
                        , BAP_TRUE  /* Ist Senderichtung */
                        , BapChkDt_ScalarIn );
                }
                break;
#ifdef BAP_FSG
            case BapChkDt_ScalarInit:
            case BapChkDt_VariableInit:
#endif /* #ifdef BAP_FSG */
            case BapChkDt_ScalarIn:
            case BapChkDt_VariableIn:
                bDataTypeCheck = BAP_BAL_CheckDatatype(apoPars->poFctRomRow->eTxDataType
                    , apoPars->poFctRomRow->u32TxSize /* au32BSSize */
                    , apoPars->u32Length              /* au32DataSize */
                    , BAP_TRUE /* Ist Senderichtung */
                    , eCheckDataType /* VariableIn | Skalar */
                );
            break;

#ifdef BAP_ASG
            case BapChkDt_ScalarOut:
                bDataTypeCheck = BAP_BAL_CheckDatatype(apoPars->poFctRomRow->eRxDataType
                    , apoPars->poFctRomRow->u32RxSize /* au16BSSize */
                    , apoPars->u32Length              /* au16DataSize */
                    , BAP_TRUE /* Ist Senderichtung */
                    , eCheckDataType /* VariableIn | Skalar */
                );
            break;

            /** Pruefung fuer BYTESEQUENCE bei BAP_CacheGetRequestByteSequence */
            case BapChkDt_VariableOut:
            default:
                bDataTypeCheck = BAP_BAL_CheckDatatype(apoPars->poFctRomRow->eRxDataType
                    , apoPars->poFctRomRow->u32RxSize /* au16BSSize */
                    , apoPars->poFctRomRow->u32RxSize /* au16DataSize */
                    , BAP_TRUE /* Ist Senderichtung */
                    , BapChkDt_VariableOut
                );
                break;
#else
            default:
                bDataTypeCheck = BAP_FALSE;
                break;
#endif /* #ifdef BAP_ASG */
        }

        if (BAP_FALSE == bDataTypeCheck)
        {
            BAP_DBG_InvalidArgError(apoPars->lsgId);
            eResult = BapErr_InvalidArg;
        }
        else
        {
            eResult = BapErr_OK;
        }

        /*lint +esym(613,apoPars)*/
    }
    return eResult;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


/*
 *  Diese Funktion wird in bap_balutil.h dokumentiert.
 *
 *  Diese Funktion hat 8 ControlNestingLayers (max.4)
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_IMPL_FAR DBGVAR BapError_et
BAP_BAL_CheckDataReceived(BapInternalParameters_cpot apoPars)
{
    DBGVAR BapError_et eResult = BapErr_OK;

    /*lint -esym(613,apoPars)*/
    BAP_ASSERT(NULL != apoPars);
    /* MISRA_2012_REQ_10.4 : add cast of BAP_MAX_FCT_ID into fctId to be compliant. 2021_03_01 */
    BAP_ASSERT(apoPars->fctId <= (fctId_t)BAP_MAX_FCT_ID);


    /* Pruefen ob die Funktion existiert */
    /* SSWPPB[93] Nullpointer checks for missing initalization FctFromRow or LsgRomRow */
    if(  (NULL == apoPars) || (NULL == apoPars->poFctRomRow) || (NULL == apoPars->poLsgRomRow)  )
    {
        eResult = BapErr_InvalidArg;
    }

    /* Pruefen ob der OpCode erlaubt ist */
    /*lint -e701*/ /* Info 701: Shift left of signed quantity (int). But BAP_BIT0 is cast into uint8_t at definition and here.
                 	* So false warning */
    else if ((uint8_t)0 == (apoPars->poFctRomRow->u8OpCodeReceiveMask & ((uint8_t)((uint8_t)BAP_BIT0<<(uint8_t)apoPars->eOpCode))) )
    /*lint -e701*/
    {
        eResult = BapErr_InvalidArg;
    }
    /* Pruefen ob der Datentyp erlaubt ist */
    else if(BAP_FALSE == BAP_BAL_CheckDatatype(apoPars->poFctRomRow->eRxDataType
            , apoPars->poFctRomRow->u32RxSize
            , apoPars->u32Length
            , BAP_FALSE /* Ist nicht Senderichtung */
            , (
#ifdef BAP_USES_SEGMENTATION
                ((apoPars->poFctRomRow->eRxDataType == BapDt_ByteSequence) || (apoPars->poFctRomRow->eRxDataType == BapDt_FixedByteSequence)) ? BapChkDt_VariableOut :
#else
                (apoPars->poFctRomRow->eRxDataType == BapDt_FixedByteSequence) ? BapChkDt_VariableOut :
#endif /* #ifdef BAP_USES_SEGMENTATION */
               BapChkDt_ScalarOut) )
    )
    {
        eResult = BapErr_InvalidArg;
    }

    /* Pruefen ob nicht in Fct.list */
    else if ( (BAP_FALSE == BAP_BAL_CheckIfFunctionIsValid(apoPars->poFctRomRow->fctId, apoPars->poLsgRomRow->poLsgRamRow->BAP_aru8FunctionList))
            && (BapLayerLsgStat_Initialized != apoPars->poLsgRomRow->poLsgRamRow->eLsgStatus))
    {
        /* Fct. ist nicht in aktueller Fct.list und wird demzufolge purged */
        BAP_DBG_RxDataPurgedEvent();
        eResult = BapErr_InvalidArg;
    }

    /* Normalerweise darf im Nicht Running Zustand nichts nach oben gemeldet werden, aber */
    /* Die BAP_FCTID_BAPCONFIG muss auch im WAIT_FOR_CONFIG Status an Applikation gemeldet werden! */
    /* MISRA_2012_REQ_10.5 : No risk arise, because BAP_FCTID_BAPCONFIG is already cast at declaration and fit in enum. */
    else if(    (BapLayerLsgStat_Running != apoPars->poLsgRomRow->poLsgRamRow->eLsgStatus)
#ifdef BAP_ASG
        && (!( ((fctId_t)BAP_FCTID_BAPCONFIG == (fctId_t)apoPars->fctId) && (BapLayerLsgStat_WaitForOrInvalidConfig == apoPars->poLsgRomRow->poLsgRamRow->eLsgStatus) ))
#endif /* #ifdef BAP_ASG */
        )
    {
        /* hier keine BAP_DBG Meldung, da der BAP-Stack noch nicht gestartet wurde */
        eResult = BapErr_InvalidState;
    }
    else
    {
        /* diese Teil ist von BAP_BAP  */

        /* Folgende Pruefung bringt das ASG vom WaitForConfig in den Running Zustand */
        /* Dabei wird ueberprueft ob die uebermittelte BAPCONFIG gueltig ist */
    	/* MISRA_2012_REQ_10.5 : No risk arise, because BAP_FCTID_BAPCONFIG is already cast at declaration and fit in enum. */
#ifdef BAP_ASG /* Behandlung muss in ASG durchgefuehrt werden */
        if (
#if defined(BAP_ASG) && defined(BAP_FSG) /* Im Kombigeraet muss die Abfrage ob es ein ASG ist, drin sein */
            (BapSG_ASG == apoPars->poLsgRomRow->eSGType) &&
#endif /* defined(BAP_ASG) && defined(BAP_FSG) */
                ((fctId_t)BAP_FCTID_BAPCONFIG == (fctId_t)apoPars->fctId)&&
                ((BapOp_PropReset_Set == apoPars->eOpCode)
                        || (BapOp_PropStatus == apoPars->eOpCode)
                        || (BapOp_PropHeartbeatStatus == apoPars->eOpCode))
            )
        {
            /* ungueltige BAPConfig nicht an Appl melden */
            if (BAP_FALSE != BAP_BAL_CheckBapConfig(apoPars, apoPars->pData))
            {
                eResult = BapErr_IncompatibleProtocolVersion;
            }
        }
#endif /* #ifdef BAP_ASG */
    }
    return eResult;
    /*lint +esym(613,apoPars)*/
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


#ifdef BAP_ASG
/*
 *  Diese Funktion wird in bap_balutil.h dokumentiert.
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_BAL_InvalidateCache(BapLsgRomRow_pot apoLsgRomRow)
{
    DBGVAR uint8_t u8FctIndex;
    DBGVAR uint8_t u8TableSize;

    /*lint -esym(613, apoLsgRomRow) */
    /*lint -esym(831, apoLsgRomRow) */
    BAP_ASSERT(NULL != apoLsgRomRow);

    u8TableSize = apoLsgRomRow->u8FctRomTableSize;
    for(u8FctIndex=(uint8_t)0; u8FctIndex<u8TableSize; ++u8FctIndex)
    {
        BapFctRomRow_pot poFctRomRow = &BAP_FctRomTables[apoLsgRomRow->u16FctRomIndex + u8FctIndex];
        if(NULL != poFctRomRow->poBalRamRow)
        {
            /*keine Typpruefung (u8,u16,u32, buffer) zum Eintragen noetig, auf Grund des union */
            poFctRomRow->poBalRamRow->eDataStatus = BapBalDataStat_Invalid;
        }
    }
    /* FctList-Puffer mit ASG FctList vorbelegen */
    /*lint -e9087*/ /* MISRA_2012_REQ_11.3 : 1st and 2nd arguments of MEMCPY are of types (uint8_t*).
                     * They are implicitly cast to (void*). The memory is packed because it is uint8_t so there should be no problem to copy.*/
    FAR_MEMCPY(apoLsgRomRow->poLsgRamRow->BAP_aru8FunctionList, apoLsgRomRow->BAP_aru8FunctionList, BAP_FCTID_FCTLIST_SIZE);
    /*lint +e9087*/
    BAP_BAL_UpdateLsgCacheStatus(apoLsgRomRow);
    /*lint +esym(831, apoLsgRomRow) */
    /*lint +esym(613, apoLsgRomRow) */

    return;
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* #ifdef BAP_ASG */


#ifdef BAP_ASG
/*
 *  Diese Funktion wird in bap_balutil.h dokumentiert.
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR DBGVAR BapBalDataStatus_et
BAP_BAL_GetLsgCacheStatus(BapLsgRomRow_pot apoLsgRomRow)
{
    DBGVAR BapBalDataStatus_et eReturnStatus = BapBalDataStat_Invalid;

    if(NULL != apoLsgRomRow)
    {
        /*lint -e9034*/ /* MISRA_2012_REQ_10.3 : PC-Lint 9.00L throws a warning due to Tool bug. Hence, this warning has been deactivated.
                         * Documented with a mail from the Lint team in the SSWCCB-2522_BAP-Entwicklung auf MISRA2012 umstellen folder */
        eReturnStatus = (BapBalDataStatus_et) (
            ( (bitfield_t)1u == apoLsgRomRow->poLsgRamRow->fState.fCacheValid) ?
            BapBalDataStat_Valid : BapBalDataStat_Invalid);
        /*lint +e9034*/
    }
    else
    {
        /* darf nie vorkommen! */
    }
    return eReturnStatus;
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* #ifdef BAP_ASG */

/*Diese Funktion hat 6 ControlNestingLayers (max.4)*/
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
static BAP_IMPL_FAR DBGVAR uint8_t
BAP_BAL_CompareBapConfig(BapLsgRomRow_pot poLsgRomRow,
        const volatile uint8_t apData[])
{
    DBGVAR uint8_t u8ListId;
    DBGVAR uint8_t u8ValidConfig = (uint8_t)0;
    DBGVAR uint8_t u8BAPConfigIndex;
    /* BAPConfig vom FSG bzw. der Applikation pruefen */
    for(u8ListId=(uint8_t)0; (u8ListId<poLsgRomRow->u8BAPConfigTableSize) && (BAP_BITMASK_10011001 != u8ValidConfig); u8ListId++)
    {
        /* Intialisiere das aktuelle Ergebnis mit keine Uebereinstimmung gefunden, nicht jedoch das Gesamtergebnis */
        u8ValidConfig &= BAP_BITMASK_11110000;

        u8BAPConfigIndex = poLsgRomRow->u8BAPConfigTableIndex+u8ListId;

        if(BAP_BAPConfigTable[u8BAPConfigIndex][BAP_BAPCONFIG_POS_PV_MAJOR] == apData[BAP_BAPCONFIG_POS_PV_MAJOR])
        {
            /* 2012-06-14 WWU: Minor-Nummer wird in ASG (CombiASG) nicht geprueft. */
#if defined(BAP_FSG)
            if ( /* nur FSG */ /* SSWPPB-14 Added DF Minor check here */
                 /*lint -e9007*/ /* MISRA_2012_REQ_13.5 : Warning deactivated. Logically, right hand side of && has lower priority.
                  *  Therefore side-effects doesn't matter*/
                 ((BAP_BAPConfigTable[u8BAPConfigIndex][BAP_BAPCONFIG_POS_PV_MINOR] == apData[BAP_BAPCONFIG_POS_PV_MINOR]) && \
                  (BAP_BAPConfigTable[u8BAPConfigIndex][BAP_BAPCONFIG_POS_DF_MINOR] >= apData[BAP_BAPCONFIG_POS_DF_MINOR]))
                 /*lint +e9007*/
#if defined(BAP_ASG)
                 /* Combi: MINOR wird im CombiASG nicht geprueft */
                 || (poLsgRomRow->eSGType == BapSG_ASG)
#endif /* #ifdef BAP_ASG */
                )
#endif /*#ifdef BAP_FSG*/
            {
                    u8ValidConfig |= BAP_BITMASK_10001000;

                if(BAP_BAPConfigTable[u8BAPConfigIndex][BAP_BAPCONFIG_POS_SG_MAJOR] == apData[BAP_BAPCONFIG_POS_SG_MAJOR])
                {
                    if (BAP_BAPConfigTable[u8BAPConfigIndex][BAP_BAPCONFIG_POS_DF_MAJOR] == apData[BAP_BAPCONFIG_POS_DF_MAJOR])
                    {
                        u8ValidConfig |= BAP_BITMASK_00010001;
                    }/* DF_MAJOR */
                } /* SG_MAJOR */
            } /* PV_MINOR */
        }/* PV_MAJOR */ /* DF_MINOR */
    } /* For */
    return u8ValidConfig;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>

/*
 *  Diese Funktion wird in bap_balutil.h dokumentiert.
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_IMPL_FAR DBGVAR bool_t
BAP_BAL_CheckBapConfig(BapInternalParameters_cpot apoPars
    , DBGVAR const volatile uint8_t apData[]
)
{
    /*
     * Bit6 = PV, Bit4 = SG/DF  (Gesamtergebnis aller Konfigurationszeilen)
     * Bit2 = PV, Bit0 = SG/DF  (Einzelergebnis der aktuellen Konfigurationszeile)
     */
    DBGVAR uint8_t u8ValidConfig = (uint8_t)0;
    DBGVAR uint8_t u8LsgTableId;
    DBGVAR uint8_t u8RefLsgTableId =(uint8_t) 0;
    DBGVAR lsgId_t oldLsgId;
    DBGVAR BapError_et bapErr;

    BapLsgRomRow_pot poLsgRomRow=NULL;

    /*lint -esym(613,apData)*/
    /*lint -esym(613,apoPars)*/ /* wurde bereits vorher benutzt */
    BAP_ASSERT(NULL != apData);

    /* Eine passende Konfiguration suchen */
    oldLsgId = BAP_LsgRomTables[u8RefLsgTableId].lsgId; /* mit erste lsgId initializieren. */
    for(u8LsgTableId=(uint8_t)0; (u8LsgTableId<BAP_LSG_ROM_TABLE_ROWS) && (BAP_BITMASK_10011001 != u8ValidConfig); u8LsgTableId++)
    {
        poLsgRomRow = &BAP_LsgRomTables[u8LsgTableId];
        if(oldLsgId != poLsgRomRow->lsgId)
        {
            u8RefLsgTableId++;
            oldLsgId = poLsgRomRow->lsgId;
        }
        if(poLsgRomRow->lsgId == apoPars->lsgId)
        {
            u8ValidConfig = BAP_BAL_CompareBapConfig(poLsgRomRow,  apData);
        }
    }

    if ((uint8_t) 0x55 == u8ValidConfig )
    {
        /* Eine gueltige BAPConfig gefunden */
        BAP_pLsgRomTable[u8RefLsgTableId] = poLsgRomRow;
        Bap_reAssignLsgRomRowFctTable = BAP_TRUE ;  /* neu erstellung der Index Tabelle aufgrund Änderung des aktuellen Steuergerätes notwendig. siehe Funktion BAP_GetLsgRomRow */
    }
    else
    {
        /* falls keine gueltige Konfig gefunden mit der "alten" weiterarbeiten */
        poLsgRomRow = apoPars->poLsgRomRow;
#ifdef BAP_FSG
#ifdef BAP_ASG
        if(poLsgRomRow->eSGType==BapSG_FSG)
#endif /* #ifdef BAP_ASG */
        {
            /* Zustand auf InvalidConfig setzen */
            poLsgRomRow->poLsgRamRow->eLsgStatus = BapLayerLsgStat_WaitForOrInvalidConfig;
            BAP_DBG_SetBalState(apoPars->lsgId, BapLayerLsgStat_WaitForOrInvalidConfig);
        }
#endif /* #ifdef BAP_FSG */
    }

#ifdef BAP_ASG
#ifdef BAP_FSG
    if(poLsgRomRow->eSGType==BapSG_ASG)
#endif /* #ifdef BAP_FSG */
    {
        /* Beim Empfang eines Reset den Cache ungueltig machen */
        if(BapOp_PropReset_Set == apoPars->eOpCode)
        {
            /* Nachdem das ASG gestartet wurde und ein Reset kommt erst mal den Zustand
               WaitForConfig einnehmen, bis die Version geprueft wurde
               (erfolgt noch in dieser Funktion, erforderlich fuer ungueltige Version) */
            /*lint -esym(771,poLsgRomRow)  da die Lsg-Tabelle immer mindestens eine Zeile hat, ist der Zeiger initialisiert */
            /*lint -esym(794,poLsgRomRow)*/
            poLsgRomRow->poLsgRamRow->eLsgStatus = BapLayerLsgStat_WaitForOrInvalidConfig;
            BAP_DBG_SetBalState(apoPars->lsgId, BapLayerLsgStat_WaitForOrInvalidConfig);
            BAP_BAL_InvalidateCache(poLsgRomRow);
            /* Es muessen die darunterliegenden Schichten neu initialisiert werden */
            /* z.B. Heartbeat, Sendeauftraege muessen an die neue Config angepasst werden */
            /* Es ist nicht moeglich die BAL Ebene neu zu starten, da sonst auch BAPConfig */
            /* Anfragen durchgefuehrt werden wuerden */
            BAP_BPL_Init(poLsgRomRow);
            (void)BAP_BPL_Start(poLsgRomRow);
        }
    }
#endif /* #ifdef BAP_ASG */

    if((uint8_t)0x55 == u8ValidConfig)
    {
#if defined(BAP_ASG) && defined(BAP_FSG)
        /*Combi*/
        if(poLsgRomRow->eSGType==BapSG_ASG)
        {
            /* Wenn alles ok => Zsutand auf running setzen */
            poLsgRomRow->poLsgRamRow->eLsgStatus = BapLayerLsgStat_Running;
            /*lint +esym(794,poLsgRomRow)*/
            /*lint +esym(771,poLsgRomRow)*/
            BAP_DBG_SetBalState(apoPars->lsgId, BapLayerLsgStat_Running);
        }
        else
        {
            /* Wenn alles ok => Zsutand auf BapLayerLsgStat_Initialized setzen */
            poLsgRomRow->poLsgRamRow->eLsgStatus = BapLayerLsgStat_Initialized;
            /*lint +esym(794,poLsgRomRow)*/
            /*lint +esym(771,poLsgRomRow)*/
            BAP_DBG_SetBalState(apoPars->lsgId, BapLayerLsgStat_Initialized);
        }
#elif defined(BAP_ASG)
        /*ASG*/
         /* Wenn alles ok => Zsutand auf running setzen */
        poLsgRomRow->poLsgRamRow->eLsgStatus = BapLayerLsgStat_Running;
        /*lint +esym(794,poLsgRomRow)*/
        /*lint +esym(771,poLsgRomRow)*/
        BAP_DBG_SetBalState(apoPars->lsgId, BapLayerLsgStat_Running);
#elif defined(BAP_FSG)
        /* FSG */
        /* Wenn alles ok => Zsutand auf BapLayerLsgStat_Initialized setzen */
        poLsgRomRow->poLsgRamRow->eLsgStatus = BapLayerLsgStat_Initialized;
        /*lint +esym(794,poLsgRomRow)*/
        /*lint +esym(771,poLsgRomRow)*/
        BAP_DBG_SetBalState(apoPars->lsgId, BapLayerLsgStat_Initialized);
#endif /* Combi / ASG / FSG */
        bapErr = BapErr_OK;
    }
    else
    {
        if( (uint8_t)0 == (u8ValidConfig & BAP_BITMASK_10000000))
        {
            /* Fehlerhafte Protokollversion an die Applikation melden */
            BAP_DBG_ProtocolVersionError(apoPars->lsgId);
            bapErr = BapErr_IncompatibleProtocolVersion;
        }
        else
        {
            /* Es ist durchaus moeglich, dass es eine passende DF und SG gibt, aber nicht in Kombination mit einer gueltigen PV */

            /* Fehlerhafte Datenfestlegung oder SG-Klasse an die Applikation melden */
            BAP_DBG_DataDefinitionError(apoPars->lsgId);
            bapErr = BapErr_IncompatibleDataSpecification;
        }
        /*lint -e9034*/ /*MISRA_2012_REQ_10.3 : Warning deactivated. Refers to bap_types.h, definition of BAP_FCTID_BAPCONFIG*/
        /* MISRA_2012_REQ_10.5 : No risk arise, because BAP_FCTID_BAPCONFIG is already cast at definition and fit in enum. */
        BAP_IndicationError(apoPars->lsgId, BAP_FCTID_BAPCONFIG, bapErr);
        /*lint +e9034*/
    }

    return ((BapErr_OK != bapErr)? BAP_TRUE : BAP_FALSE);

    /*lint +esym(613,apoPars)*/
    /*lint +esym(613,apData)*/
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


#ifdef BAP_FSG
/*
 *  Diese Funktion wird in bap_balutil.h dokumentiert.
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR DBGVAR BapError_et
BAP_BAL_InitFSGBuffers(BapLsgRomRow_pot apoLsgRomRow)
{
    /* Zum Zwischenspeichern des Funktionsergebnisses */
    DBGVAR BapError_et eResult;

#ifdef BAP_ROM_DATA_FAR_EMPTY
    DBGVAR ptr_t pBapConfig;
    DBGVAR ptr_t pFctList;
#else
    DBGVAR uint8_t pBapConfig[BAP_FCTID_BAPCONFIG_SIZE];
    DBGVAR uint8_t pFctList[BAP_FCTID_FCTLIST_SIZE];
#endif /* #ifdef BAP_ROM_DATA_FAR_EMPTY */

    /*lint -esym(613,apoLsgRomRow) */
    BAP_ASSERT(NULL != apoLsgRomRow);

#ifdef BAP_ROM_DATA_FAR_EMPTY
    pBapConfig =  BAP_BAPConfigTable[apoLsgRomRow->u8BAPConfigTableIndex];
    pFctList =  apoLsgRomRow->poLsgRamRow->BAP_aru8FunctionList;
#else
    FAR_MEMCPY(pBapConfig, BAP_BAPConfigTable[apoLsgRomRow->u8BAPConfigTableIndex], BAP_FCTID_BAPCONFIG_SIZE);
    FAR_MEMCPY(pFctList, apoLsgRomRow->poLsgRamRow->BAP_aru8FunctionList, BAP_FCTID_FCTLIST_SIZE);
#endif /* #ifdef BAP_ROM_DATA_FAR_EMPTY */

    /* Das FSG muss die internen FctIds im Sendepuffer setzen */
    /*lint -e9034*/ /*MISRA_2012_REQ_10.3 : Warning deactivated. Refers to bap_types.h, definition of BAP_FCTID_BAPCONFIG*/
    /* MISRA_2012_REQ_10.5 : No risk arise, because BAP_FCTID_BAPCONFIG is already cast at definition and fit in enum. */
    eResult = BAP_InitSendBufferByteSequence(apoLsgRomRow->lsgId
        , BAP_FCTID_BAPCONFIG
        , pBapConfig
        , BAP_FCTID_BAPCONFIG_SIZE);
    /*lint +e9034*/

    if(BapErr_OK == eResult)
    {
        /* Spezialfall ohne FctList pruefen */
        /*lint -e9034*/ /*MISRA_2012_REQ_10.3 : Warning deactivated. Refers to bap_types.h, definition of BAP_FCTID_FCTLIST*/
    	/* MISRA_2012_REQ_10.5 : No risk arise, because BAP_FCTID_FCTLIST is already cast at definition and fit in enum. */
        if(NULL != BAP_GetLsgFctRomRow(apoLsgRomRow, BAP_FCTID_FCTLIST))
        /*lint +e9034*/
        {
            /*lint -e9034*/ /*MISRA_2012_REQ_10.3 : Warning deactivated. Refers to bap_types.h, definition of BAP_FCTID_FCTLIST*/
        	/* MISRA_2012_REQ_10.5 : No risk arise, because BAP_FCTID_FCTLIST is already cast at definition and fit in enum. */
            eResult = BAP_InitSendBufferByteSequence(apoLsgRomRow->lsgId
                , BAP_FCTID_FCTLIST
                , pFctList
                , BAP_FCTID_FCTLIST_SIZE);
            /*lint +e9034*/
        }
    }
    if(BapErr_OK == eResult)
    {
        /* Spezialfall ohne Heartbeat pruefen */
        /*lint -e9034*/ /*MISRA_2012_REQ_10.3 : Warning deactivated. Refers to bap_types.h, definition of BAP_FCTID_HEARTBEAT*/
    	/* MISRA_2012_REQ_10.5 : No risk arise, because BAP_FCTID_HEARTBEAT is already cast at definition and fit in enum. */
        if(NULL != BAP_GetLsgFctRomRow(apoLsgRomRow, BAP_FCTID_HEARTBEAT))
        /*lint +e9034*/
        {
            /*lint -e9034*/ /*MISRA_2012_REQ_10.3 : Warning deactivated. Refers to bap_types.h, definition of BAP_FCTID_HEARTBEAT*/
        	/* MISRA_2012_REQ_10.5 : No risk arise, because BAP_FCTID_HEARTBEAT is already cast at definition and fit in enum. */
            eResult = BAP_InitSendBufferInt8(apoLsgRomRow->lsgId
                , BAP_FCTID_HEARTBEAT
                , apoLsgRomRow->u8Heartbeat);
            /*lint +e9034*/
        }
    }
    if(BapErr_OK != eResult)
    {
        /* Falls irgendwas in den unteren Schichten fehlschlaegt immer InvalidArg */
        BAP_DBG_InvalidArgError(apoLsgRomRow->lsgId);
        eResult = BapErr_InvalidArg;
    }
    return eResult;
    /*lint +esym(613,apoLsgRomRow) */
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* #ifdef BAP_FSG */


#ifdef BAP_USES_DATATYPE_16
/*
 *  Diese Funktion wird in bap_balutil.h dokumentiert.
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_BAL_Int16toDataStream(DBGVAR uint16_t au16Value, DBGVAR uint8_t apPtr[])
{
    /*lint -esym(613,apPtr)*/
    BAP_ASSERT(NULL != apPtr);

    apPtr[0] = (uint8_t) au16Value; /* & 0xff ist implizit durch den Cast) */
    apPtr[1] = (uint8_t) (au16Value >> BAP_BYTE);
    return;
    /*lint +esym(613,apPtr)*/
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_USES_DATATYPE_16 */


#ifdef BAP_USES_DATATYPE_16
/*
 *  Diese Funktion wird in bap_balutil.h dokumentiert.
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR DBGVAR uint16_t
BAP_BAL_DataStreamToInt16(DBGVAR const volatile uint8_t apPtr[])
{
    DBGVAR uint16_t u16Return;
    uint16_t u16ShortLow;
    uint16_t u16ShortHigh;

    if (NULL == apPtr)
    {
        u16Return = (uint16_t)0u;
    }
    else
    {
        u16ShortLow = (uint16_t)apPtr[0];
        u16ShortHigh = (uint16_t)((uint16_t)apPtr[1] << BAP_BYTE);
        u16Return = u16ShortLow + u16ShortHigh;
    }
    return u16Return;
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_USES_DATATYPE_16 */


#ifdef BAP_USES_DATATYPE_32
/*
 *  Diese Funktion wird in bap_balutil.h dokumentiert.
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_BAL_Int32toDataStream(DBGVAR uint32_t au32Value, DBGVAR uint8_t apPtr[])
{
    /*lint -esym(613,apPtr)*/
    BAP_ASSERT(NULL != apPtr);

    apPtr[0] = (uint8_t)(au32Value);       /* & 0xff ist implizit durch den Cast */
    apPtr[1] = (uint8_t)(au32Value >> 8);  /* & 0xff ist implizit durch den Cast */
    apPtr[2] = (uint8_t)(au32Value >> 16); /* & 0xff ist implizit durch den Cast */
    apPtr[3] = (uint8_t)(au32Value >> 24);
    return;

    /*lint +esym(613,apPtr)*/
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_USES_DATATYPE_32 */


#ifdef BAP_USES_DATATYPE_32
/*
 *  Diese Funktion wird in bap_balutil.h dokumentiert.
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR DBGVAR uint32_t
BAP_BAL_DataStreamToInt32(DBGVAR const volatile uint8_t apPtr[])
{
    DBGVAR uint32_t u32Return;
    uint32_t u32Byte1;
    uint32_t u32Byte2;
    uint32_t u32Byte3;
    uint32_t u32Byte4;

    if (NULL == apPtr)
    {
        u32Return = 0u;
    }
    else
    {
        u32Byte1 = (uint32_t)apPtr[0];
        u32Byte2 = (uint32_t)apPtr[1] << 8;
        u32Byte3 = (uint32_t)apPtr[2] << 16;
        u32Byte4 = (uint32_t)apPtr[3] << 24;
        u32Return = u32Byte1 + u32Byte2 + u32Byte3 + u32Byte4;
    }
    return u32Return;
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_USES_DATATYPE_32 */

/*
 * Diese Funktion wird in bap_balutil.h dokumentiert.
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_IMPL_FAR DBGVAR bool_t
BAP_BAL_CheckIfFunctionIsValid(fctId_t fctId, const uint8_t aru8FctList[])
{
    DBGVAR bool_t bIsValid;

    /* MISRA_2012_REQ_14.3 : "( BAP_BINARY_ID(fctId) < (uint8_t)64)" is not invariant
     * but always true except in case of configuration issue or running issue. */
    if ( ((uint8_t) 1 < BAP_BINARY_ID(fctId))    /* GetAll braucht nicht in Fct.list zu sein (wg. Kompatibilitaet zu BAP1.2) */
        && ( BAP_BINARY_ID(fctId) <= (uint8_t)BAP_MAX_FCT_ID) /*lint !e650 enums haben mindestens 8 bit *//* keine internen FctIds (CacheStatus) */
        && ((uint8_t)0 == (aru8FctList[BAP_BINARY_ID(fctId) / BAP_BYTE] & (BAP_BIT7 >> (BAP_BINARY_ID(fctId) % BAP_BYTE))) )
    )
    {
        /* Fct.Id ist nicht in Fct.list enthalten */
        bIsValid = BAP_FALSE;
    }
    else
    {
        bIsValid = BAP_TRUE;
    }

    return bIsValid;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


#ifdef BAP_ASG
/*
 * Diese Funktion wird in bap_balutil.h dokumentiert.
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR BapError_et
BAP_BAL_RequestVoidGet(BapInternalParameters_cpot apoPars)
{
    DBGVAR BapError_et eResult = BapErr_OK;
    DBGVAR uint8_t u8FctIndex;
    DBGVAR uint8_t u8TableSize;

    /* Hier muss zwischen der Einzel Cache Gueltigkeit der Properties */
    /* und der Gesamtgueltigkeit des Cache bei BAP_FCTID_GETALL unterschieden werden */
    /* MISRA_2012_REQ_10.5 : No risk arise, because BAP_FCTID_GETALL is already cast at definition and fit in enum. */
    /*lint -esym(613,apoPars)*/ /* Ist bereits vom Aufrufer abgeprueft */
    if ((fctId_t)BAP_FCTID_GETALL == (fctId_t)apoPars->fctId)
    {
        if(BapBalDataStat_Valid == BAP_BAL_GetLsgCacheStatus(apoPars->poLsgRomRow))
        {
            /* Bei gueltigem GesamtCache gleich eine STATUSALL Meldung erzeugen und keine Botschaft ueber Bus senden */
            /*lint -e9034*/ /*MISRA_2012_REQ_10.3 : Warning deactivated. Refers to bap_types.h, definition of BAP_FCTID_GETALL*/
        	 /* MISRA_2012_REQ_10.5 : No risk arise, because BAP_FCTID_GETALL is already cast at definition and fit in enum. */
            BAP_IndicationVoid(apoPars->lsgId, BAP_FCTID_GETALL, BapInd_Data);
            /*lint +e9034*/
        }
        else /* Cache Zustand von BAP_FCTID_GETALL ist ungueltig */
        {
            /* Alle Valid Cache Eintraege gehen in den GetAll Zustand ueber und Aussenden auf Bus an FSG */
            u8TableSize = apoPars->poLsgRomRow->u8FctRomTableSize;
            for(u8FctIndex=(uint8_t)0; u8FctIndex<u8TableSize; ++u8FctIndex)
            {
                BapBalRamRow_pot poBalRamRow = BAP_FctRomTables[apoPars->poLsgRomRow->u16FctRomIndex + u8FctIndex].poBalRamRow;

                /* keine Typpruefung (u8,u16,u32,buffer) bei poBalRamRow noetig, auf Grund des union*/
                if ( (NULL != poBalRamRow) && (BapBalDataStat_Valid == poBalRamRow->eDataStatus) )
                {
                    /*keine Typpruefung (u8,u16,u32, buffer) zum Eintragen noetig, auf Grund des union */
                    poBalRamRow->eDataStatus = BapBalDataStat_GetAll;
                }
            }
            eResult = BAP_BPL_Send(apoPars);
        }
    }
    /* Existiert ueberhaupt ein Cache fuer diese Funktion? && */
    /* Automatisches Beantworten von DataGet wenn der Einzelcache Zustand nicht Invalid ist */
    else
    if ( (NULL != apoPars->poFctRomRow->poBalRamRow)
         && (BapBalDataStat_Invalid != apoPars->poFctRomRow->poBalRamRow->eDataStatus) ) /* *(BapBalDataStatus_et*)apoPars->poFctRomRow->poBalRamRow liefert eDataStatus zurueck*/
    {
        /* gueltiger Cache vorhanden => direkt Indication aufrufen */
        switch(apoPars->poFctRomRow->eRxDataType)
        {
            case BapDt_Int8:
                BAP_IndicationInt8(apoPars->lsgId, apoPars->fctId, BapInd_Data, apoPars->poFctRomRow->poBalRamRow->u8Value);
                break;
            case BapDt_Int16:
                BAP_IndicationInt16(apoPars->lsgId, apoPars->fctId, BapInd_Data, apoPars->poFctRomRow->poBalRamRow->u16Value);
                break;
            case BapDt_Int32:
                BAP_IndicationInt32(apoPars->lsgId, apoPars->fctId, BapInd_Data, apoPars->poFctRomRow->poBalRamRow->u32Value);
                break;
            case BapDt_FixedByteSequence:
            case BapDt_ByteSequence:
                BAP_IndicationByteSequence(apoPars->lsgId, apoPars->fctId, BapInd_Data
                    , *(apoPars->poFctRomRow->poBalRamRow->oBufferWithLength.paru8Buffer)
                    , apoPars->poFctRomRow->poBalRamRow->oBufferWithLength.u32Length);
                break;
            default:
                /* No Statements */
                break;
        }
    }
    /* Wenn Get nicht aus dem Cache beantwortet werden kann, dann an FSG schicken */
    else
    {
#ifdef BAP_USES_ARRAYS
        /* Array/Get ist als BAP_RequestVoid nicht erlaubt! */
        if(BapFctCls_Array == apoPars->poFctRomRow->eFunctionClass)
        {
            BAP_DBG_InvalidArgError(apoPars->lsgId);
            eResult = BapErr_InvalidArg;
        }
        else
#endif /* #ifdef BAP_USES_ARRAYS */
        {
            eResult = BAP_BPL_Send(apoPars);
        }
    }
    /*lint +esym(613,apoPars)*/
    return eResult;
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* #ifdef BAP_ASG */


#ifdef BAP_FSG
/*
 * Diese Funktion wird in bap_balutil.h dokumentiert.
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR BapDataType_et
BAP_BAL_FsgDataReceived(BapInternalParameters_cpot apoPars, DBGVAR const BapIndication_et aeIndication)
{
    DBGVAR bool_t giveNoIndication = BAP_FALSE;
    DBGVAR BapDataType_et eDataType = BapDt_None;

    /*lint -esym(613,apoPars)*/ /* Ist bereits vom Aufrufer abgeprueft */
    /* Spezialbehandlungen fuer FSG durchfuehren */
    if ( (BapInd_DataGet == aeIndication)
        && ( (BapFctCls_Property == apoPars->poFctRomRow->eFunctionClass) || (BapFctCls_Cache == apoPars->poFctRomRow->eFunctionClass) )
       )
    {
        /* Properties & Cache werden direkt vom Stack beantwortet, Arrays werden als Indication gemeldet */
    	 /* MISRA_2012_REQ_10.5 : No risk arise, because BAP_FCTID_GETALL is already cast at definition and fit in enum. */
        giveNoIndication = BAP_TRUE;
        if ((fctId_t)apoPars->fctId == (fctId_t)BAP_FCTID_GETALL)
        {
            BAP_DBG_GetAllEvent(apoPars->lsgId);
            /* Sonderbehandlung fuer GetAll im BAL-FSG nicht mehr erforderlich, da BCL dies nun tut. */
        }

        /* DataGet wird direkt beantwortet ohne Indication */
        /* fuer Property und Cache */
        BAP_BPL_ResendStatus(apoPars);
    }

    /* Indications nur wenn das FSG gestartet wurde */
    if( (BAP_FALSE == giveNoIndication) && (BapInd_Invalid != aeIndication)
        && (BapLayerLsgStat_Running == apoPars->poLsgRomRow->poLsgRamRow->eLsgStatus))
    { /* Sonderbehandlung fuer Void-Indications */
#ifdef BAP_USES_METHODS
        /* Abort oder Processing im FSG immer Void */
        if ( (BapInd_Abort == aeIndication) || (BapInd_Processing_CNF == aeIndication) )
        {
            eDataType = BapDt_Void;
        }
        else
#endif /* #ifdef BAP_USES_METHODS */
        {
            eDataType = apoPars->poFctRomRow->eRxDataType;
        }
    }
    /*lint +esym(613,apoPars)*/
    return eDataType;
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_FSG */


#ifdef BAP_ASG
/*
 * Diese Funktion wird in bap_balutil.h dokumentiert.
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR BapDataType_et
BAP_BAL_AsgDataReceived(DBGVAR volatile_ptr_t apConvertedData
    , BapInternalParameters_cpot apoPars
    , DBGVAR BapIndication_et * const apeIndication)
{
    DBGVAR bool_t giveIndication = BAP_TRUE;
    DBGVAR BapDataType_et eDataType = BapDt_None;

    /*lint -esym(613,apoPars)*/ /* Ist bereits vom Aufrufer abgeprueft */
    /*lint -esym(613,apeIndication)*/ /* Sicher, dass bereits vom Aufrufer gesetzt */
    /* Spezialbehandlungen fuer ASG durchfuehren */
    if ( (BapInd_Data == *apeIndication) || (BapOp_PropHeartbeatStatus==apoPars->eOpCode) )
    {
        switch((uint16_t) apoPars->fctId)
        {
            case BAP_FCTID_FCTLIST:
                /* Sonderbehandlung fuer FunctionList im ASG */
                if(BapErr_IncompatibleDataSpecification == BAP_BAL_CheckFunctionListAsg(apConvertedData, apoPars->poLsgRomRow , BAP_FALSE ) )
                {
                    /* ungueltige FctList nicht an Appl melden */
                    giveIndication = BAP_FALSE;
                }
                else
                {
                    BAP_BAL_UpdateLsgCacheStatus(BAP_GetLsgRomRow(apoPars->lsgId));
                }
                break;
            case BAP_FCTID_GETALL:
                /* Sonderbehandlung fuer GETALL-Block-Antwort im ASG */
                BAP_BAL_ProcessStatusAll(apoPars->u32Length, apConvertedData, apoPars->poLsgRomRow);
                /* StatusAll unterdruecken, da dies von UpdateLsgCacheStatus gemeldet wird */
                if(BapInd_Data == *apeIndication){
                    giveIndication = BAP_FALSE;
                }
                break;
            default:
                /* nichts tun */
                break;
        }
    }

    /* Indications nur wenn das ASG komplett gestartet wurde oder im Falle einer BAPConfig-Nachricht */
    if( BapLayerLsgStat_Running == apoPars->poLsgRomRow->poLsgRamRow->eLsgStatus)
    {
        if(NULL != apoPars->poFctRomRow->poBalRamRow)
        {
            if(BapOp_PropHeartbeatStatus == apoPars->eOpCode)
            {
                /* Alter Status muss zwischengespeichert werden, da UpdateCache dies ueberschreibt */
                /* keine Typpruefung (u8,u16,u32,buffer) bei poBalRamRow noetig, auf Grund des union*/
                DBGVAR BapBalDataStatus_et eOldState = apoPars->poFctRomRow->poBalRamRow->eDataStatus;
                DBGVAR bool_t bValueHasChanged = BAP_BAL_UpdateCache(apoPars->poFctRomRow, apConvertedData, apoPars->u32Length);
                /* Sonderbehandlung fuer Status und Heartbeats im ASG */
                BAP_DBG_HeartbeatProcessedEvent(apoPars->lsgId);

                if ((BapBalDataStat_Valid == eOldState) && (BAP_TRUE == bValueHasChanged) )
                {
                    /* Im Falle einer Wertaenderung eines Heartbeat auch Indication */
                    *apeIndication = BapInd_Data; /* Heartbeat erzeugt auch Indication! */
                }
                BAP_BAL_UpdateLsgCacheStatus(BAP_GetLsgRomRow(apoPars->lsgId));
            }else if((BapOp_PropStatus == apoPars->eOpCode) || (BapOp_PropStatusAck == apoPars->eOpCode))
            {
                (void)BAP_BAL_UpdateCache(apoPars->poFctRomRow, apConvertedData, apoPars->u32Length);
                BAP_BAL_UpdateLsgCacheStatus(BAP_GetLsgRomRow(apoPars->lsgId));
            }
            else{ /* nothing to do */   }
        }
    }else{
        /* Nur Indication fuer BAPConfig ist bei nicht laufenem ASG erlaubt */
        if(BAP_FCTID_BAPCONFIG != (fctId_t)apoPars->fctId){
            giveIndication = BAP_FALSE;
        }
    }

    if((BAP_TRUE == giveIndication)  && (BapInd_Invalid != *apeIndication))
    {
        eDataType = apoPars->poFctRomRow->eRxDataType;
    }

    /*lint +esym(613,apeIndication)*/
    /*lint +esym(613,apoPars)*/
    return eDataType;
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_ASG */


#ifdef BAP_USES_ACKNOWLEDGE
/*  Diese Funktion ist in bap_balutil.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR BapAcknowledge_et
BAP_BAL_GetAcknowledge(BapFctRomRow_pot apoFctRomRow, BapOpCodes_et aeOpCode)
{
    BapAcknowledge_et eAck;
#if defined(BAP_ASG) && defined(BAP_FSG)
    BapLsgRomRow_pot poLsgRomRow;
#endif /* #if defined(BAP_ASG) && defined(BAP_FSG) */

    /*lint -esym(613, apoFctRomRow) */
    BAP_ASSERT(NULL != apoFctRomRow);

#if defined(BAP_ASG) && defined(BAP_FSG)
    poLsgRomRow = BAP_GetLsgRomRow(apoFctRomRow->lsgId);
    eAck = BAP_OpCode2AcknowledgeMatrix[poLsgRomRow->eSGType][apoFctRomRow->eFunctionClass][aeOpCode];  /*lint !e613 Falls fct existiert, dann gibt es auch lsg */
#else
    eAck = BAP_OpCode2AcknowledgeMatrix[apoFctRomRow->eFunctionClass][aeOpCode];
#endif  /* #else defined(BAP_ASG) && defined(BAP_FSG) */

    return eAck;
    /*lint +esym(613, apoFctRomRow) */

}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif  /* #ifdef BAP_USES_ACKNOWLEDGE */

/* CallBack-Funktionen */
