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
 *  Diese Datei enthaelt die Implementierung der BAL Schicht im BAP
 *  Projekt.
 *
 *  Diese C-Datei enthaelt nicht die Funktionen BAP_Indication*,
 *  da diese von der Applikation, die BAP nutzt, implementiert
 *  werden muessen.
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
 * 2021-12-10	1.11.3		JEO			[SSWPPB-244] Release preparation, fix MISRA violations.
 * 2021-12-07	1.11.3		JEO			[SSWPPB-244] Release preparation, adapt Copyright date and version number.
 * 2021-03-12	1.11.3		JEO			[SSWPPB-142] Fix MISRA violations.
 * 2021-03-08   1.11.3      DRH         [SSWPPB-142] Replaced magic numbers by constants
 * 2021-03-01	1.11.3		JEO			[SSWPPB-142] Improve jutification of Pc-Lint deac or MISRA rules violation. + fix MISRA 12.3 in "BAP_InitSendBufferByteSequence" function.
 * 2020-10-26   1.11.2      NAG         [SSWPPB-56] Check Group Basic Software Requirements (KGAS)
 * 2020-05-13   1.11.1      ODD         [SSWPPB-112] Set Indication on inital heartbeat status. Behaviour change implemented.
 * 2020-03-31   1.11.1      ODD         [SSWPPB-93] Removed polyspace warning, added Nullpointer checks on different places
 * 2020-03-23   1.11.1      NAG         [SSWPPB-53] Shutdown without Init shall not restore ROM settings for 
 *                                      BAP_Config & FctList (Warmstart problem)
 * 2019-03-21   1.10.99     KUL         [SSWPPB-4] Removal of string.h inclusion
 * 2019-01-18   1.10.99     FFS         [SSWCCB-2657] Extern declaration and initialization of Bap_reAssignLsgRomRowFctTable
 * 2018-07-19   1.10.3      FFS         [SSWCCB-2522] Misra-2012 fix (release was postponed)
 * 2017-03-17   1.9.0.1     FST         [SSWCCB-1545] SSW-Lokatierungs-Pragmas eingefuegt
 * 2016-10-12   1.8.1       FST         [SSWCCB-2410] Softwareschalter DLL_COMPILATION zur Unterscheidung
 *                                      der Erzeugung von Steuergeraete-Code und der BAP-Dll eingefuegt
 * 2014-11-28   1.8.0.0     WWU/ FST    [SSWCCB-2105] Formataenderung der Variablen 16Bit->32Bit
 * 2014-03-21   1.7.1       WWU         CCB-664 und CCB-1731: Alignment problem.
 * 2013-03-25   1.7.0       WWU         LSG Erweiterung und MISRA-2004 fix
 * 2013-03-25   1.6.8                   FRISA  Loesung von SSWCCB-1028: Im MultiConfig bei Wechsel der BAPConfig,
 *                                      wird die passende Fctlist auch aktualisiert.
 *                                      Loesung von SSWCCB-1262: Kopie der BAPconfig in das RAM
 *                                      Kopie der Konfigurationsliste in das RAM
 * 2013-01-30   1.6.8       WWU         MISRA-2004 fix
 * 2012-10-15   1.6.5.1     WWU         Korrektur der Misra-98 Abweichungen
 * 2012-09-18   1.6.5       WWU         Cyclomatic Complexity von Function BAP_BPL_DataReceived und BAP_InitSendBufferByteSequence reduziert.
 * 2011-03-03   1.6         WWU         Der Zustand ("running", "not running") des LSGs abgefragt werden.
 * 2008-08-26   1.5.0.1     RVE         Fuer VersionsInfo richtige InterfaceNumber verwenden statt hardcoded '0' 
 * 2007-08-28   1.5         RVE         Aenderung in BAP_BPL_DataReceived um BapConfig im ASG auch ueber Heartbeat-Botschaft zu akzeptieren.
 * 2007-08-28   1.5         ALI         FSG MultiConfig: Auswahl ueber InitSendBufferByteSequence()
 * 2007-08-27   1.5         RVE         Unterstuetzung fuer Requests der OpCodes StatusAck und Ack eingebaut.
 * 2007-08-22   1.5         SHU         Beim 1.Start eines LSGs wird Versionsinfo ueber 1.TX-CAN-ID auf den CAN-Bus ausgegeben.
 * 2007-08-16   1.5         ALI         Zugriff auf BapBalRamRow_t geaendert, da der Datentyp geaendert wurde
 * 2006-06-16   1.4.0.1     ALA         Bugfix: Im ASG loeste die interne Anfrage BapReq_DataGet BAPConfig ein BAP_Acknowledge aus
 * 2006-06-02   1.4         ALA         Unterstuetzung von Bap_Acknowledge
 * 2006-06-01   1.4         ALA         Optimierung Speicherplatzbedarf: Zusammenfassung Init/Shutdown
 * 2006-04-12   1.4         ALA         Unterstuetzung fuer BAP_ROM_DATA_FAR.
 * 2005-11-15   1.3.1.3     ALA         Bugfix: BAP_RequestVoid mit BapReq_Processing lieferte immer BapErr_InvalidArg
 * 2005-10-24   1.3.1.2     ALA         pu8SendData nach Bap_aru8SendData umbenannt. Ueberfluessiges const innerhalb eines Cast entfernt.
 * 2005-04-29   1.3         CRI         InitPLsgBuffer durch GetLsgRomRow ersetzt
 * 2005-04-18   1.3         CRI         Asymmetrische DT: RequestVoid Unterstuetzung
 * 2005-04-13   1.3         ALA         Optimierung der Datenstrukturen, Optimierung Parameterliste BAP_BAL_CheckRequest
 * 2005-04-12   1.3         CRI         ASG&FSG zusammen
 * 2005-04-11   1.3         CRI         Processing_CNF loest IndicationVoid aus (nur FSG)
 * 2005-04-11   1.3         CRI         CacheGetBS prueft auf NULL Pointer
 * 2005-04-10   1.3         CRI         Beim Setzen einer neuen Fct.list (initsendbuffer) muessen
 *                                      Fct. 2+3 dabei sein
 * 2005-04-08   1.3         CRI         Error Indications werden anhand der Fct.list ueberprueft
 * 2005-04-08   1.3         CRI         Testen auf NULL Pointer Uebergabe bei Requests
 * 2005-04-06   1.3         CRI         FSG kann bereits mit Subset der Fct.list starten und spaeter
 *                                      zu einem Superset umkonfigurieren
 * 2005-04-04   1.3         CRI         In BAP_BPL_DataReceived klare Trennung zwischen ifdefs fuer FSG/ASG
 * 2005-04-04   1.3         CRI         Zustandsmaschine fuer Einzelcachegueltigkeit und HB Indications
 * 2005-04-01   1.3         CRI         Einzelcachegueltigkeit und Gesamtcachegueltigkeit (StatusAll)
 * 2005-03-30   1.3         CRI         Init,Shutdown und InitSendBufferByteSequence sind
 *                                      an dynamische Fct.lists angepasst
 * 2005-03-18   1.3         CRI         Wertaenderung im Cache durch HB loest Indication aus
 * 2005-03-17   1.3         CRI         RequestByteSequence auch mit Arrays & Opcode Get/Changed moeglich,
 *                                      dafuer nicht mehr in RequestVoid erlaubt
 * 2005-03-17   1.3         CRI         Get/Changed bei Array loest keine IndicationVoid
 *                                      mehr aus sondern IndicationByteSequence
 * 2005-03-17   1.2.1       CRI         Bugfix: Bei asymmetrischen Properties (eigentlich erst ab BAP1.3 erlaubt) wird bei
 *                                      einem Get im Zusammenhang mit dem Cache statt Typ des Empfangs der Typ des Sendens benutzt.
 * 2004-11-17   1.2         JOK         Ungueltige FctList und BAPConfig wird nicht mehr an Appl gemeldet
 *                                      sondern nur noch der entsprechende Fehler.
 * 2004-11-04   1.2         ALA         CacheSetRequest nach InitSendBuffer umbenannt.
 *                                      BAP_RequestError Funktion und Aufrufe BAP_IndicationError hinzugefuegt.
 * 2004-10-21   1.2         JOK         Hilfsfunktionen aus bap_bal in bap_balutil verschoben
 * 2004-10-21   1.2         JOK         Asymetrische Konfiguration der Datentypen/DatenSize in RX/TX moeglich
 * 2004-10-21   1.2         JOK         Unterstuetzung von Methoden
 * 2004-10-21   1.2         JOK         Verzicht auf FctId FunctionList moeglich
 * 2004-10-21   1.2         JOK         Verzicht auf FctId Heartbeat moeglich
 * 2004-10-21   1.2         JOK         GetAll-Block Verarbeitung im ASG
 * 2004-10-21   1.2         JOK         FunctionList nicht mehr relevant fuer Versionspruefung
 * 2004-09-23   1.2         JOK         FunctionList vom FSG kann ein Subset vom ASG sein
 * 2004-09-23   1.2         JOK         Cache-Gueltigkeit abhaengig von FunctionList des FSG
 * 2004-09-23   1.2         JOK         Kompatible Erweiterung der FunctionList nicht mehr erlaubt
 * 2004-09-17   1.1.1       ALA         Anpassung type const * const nach const type * const wegen
 *                                      Problemen mit CVI-Compiler
 * 2004-06-07   1.1         JOK         Compilerschalter fuer SG-Typen zur Optimierung
 *                                      des ROM-Bedarfs eingefuegt
 * 2004-06-07   1.1         JOK         BAP_BAL_CheckCacheSetRequest() entfernt und Funktionalitaet
 *                                      in BAP_BAL_CheckRequest() mit aufgenommen
 * 2004-06-07   1.1         JOK         Laufzeitoptimierungen in Funktionen durch ersetzen der aLsgId
 *                                      durch den Zeiger apoLsgRomRow in die LSG-Tabelle
 * 2004-06-07   1.1         JOK         Einfuehrung der BapDt_FixedByteSequence fuer nicht-segmentierte
 *                                      ByteSequenzen
 ******************************************************************/


/* Systemincludes mit <...> */

/* Bibliotheken von externen Herstellen mit <...> */

/* Eigene Header-Dateien "..." */
#include "bap_util.h"           /* Allgemeine Hilfsfunktionen fuer BAP */
#include "bap_bal.h"            /* BAP interne BAL Schnittstelle */
#include "bap_balconfig.h"      /* Struktur der Konfigtabellen */
#include "bap_balutil.h"        /* Hilfsfunktionen fuer die BAL Schicht */
#include "bap_bpl.h"            /* darunterliegende Schicht */
#include "bap_debug.h"          /* Diagnoseschnittstelle */
#include "bap_canubs.h"
#include "bap_bclconfig.h"

#ifdef BAP_USES_ASR_WRAPPER
/* Include required only in Autosar as defines from bap_defines.h will be 
   defined in rte_bap_types.h */
#include "Rte_BAP.h"
#endif /* #ifdef BAP_USES_ASR_WRAPPER */

/* Externe globale Variablen-Definitionen */

/**
 * Beim 1.Start eines LSGs(ASG und FSG) wird die Versionsinfo ueber die erste
 * TX-CAN-ID mit LSG-ID = 0, FctID = 0 und OpCode Status auf den CAN-Bus ausgegeben.
 * Die erfolgte Ausgabe wird mittels eines Flags gespeichert. Das Flag wird bei jedem
 * BAP_Shutdown wieder zurueckgesetzt, so dass ein weiterer BAP_Start zur erneuten
 * Ausgabe der Versionsinfo fuehrt.
 * */
#ifdef DLL_COMPILATION
extern bool_t BAP_bVersionInfo;
#else
#   define BAP_START_SEC_VAR_INIT_8
#   include <BAP_MemMap.h>
/* MISRA 2012 8.4 removal */
extern bool_t BAP_bVersionInfo;

bool_t BAP_bVersionInfo = BAP_FALSE;
#   define BAP_STOP_SEC_VAR_INIT_8
#   include <BAP_MemMap.h>
#endif /* #ifdef DLL_COMPILATION */

/**
 * MISRA-2004 fix: Rule 1.2 near auto address
 * Ersetze uint8-, uint16-, uint32- Pointer durch array.
 */
#ifdef DLL_COMPILATION
extern uint8_t Bap_aru8SendData[BAP_BIT8_BYTES];
extern uint8_t Bap_aru16SendData[BAP_BIT16_BYTES];
extern uint8_t Bap_aru32SendData[BAP_BIT32_BYTES];
#else
#   define BAP_START_SEC_VAR_NO_INIT_8
#   include <BAP_MemMap.h>
/* MISRA 2012 8.4 removal */
extern DBGVAR uint8_t Bap_aru8SendData[BAP_BIT8_BYTES];
extern DBGVAR uint8_t Bap_aru16SendData[BAP_BIT16_BYTES];
extern DBGVAR uint8_t Bap_aru32SendData[BAP_BIT32_BYTES];

DBGVAR uint8_t Bap_aru8SendData[BAP_BIT8_BYTES];
DBGVAR uint8_t Bap_aru16SendData[BAP_BIT16_BYTES];
DBGVAR uint8_t Bap_aru32SendData[BAP_BIT32_BYTES];
#   define BAP_STOP_SEC_VAR_NO_INIT_8
#   include <BAP_MemMap.h>
#endif /* #ifdef DLL_COMPILATION */

/**
 * MISRA-2004 fix: Rule 1.2 near auto address
 * Ersetze ptr durch globale Variable
 * Siehe Funktion BAP_RequestError
 */
#ifdef DLL_COMPILATION
extern uint8_t Bap_u8ErrorCode;
#else
#   define BAP_START_SEC_VAR_NO_INIT_8
#   include <BAP_MemMap.h>
/* MISRA 2012 8.4 removal */
extern DBGVAR uint8_t Bap_u8ErrorCode;

DBGVAR uint8_t Bap_u8ErrorCode;
#   define BAP_STOP_SEC_VAR_NO_INIT_8
#   include <BAP_MemMap.h>
#endif /* #ifdef DLL_COMPILATION */

/* Temporaerer Speicher fuer Zugriff mittels Pointer auf BAP_XML_VERSION_MAJOR und BAP_XML_VERSION_MINOR */
#ifdef DLL_COMPILATION
extern uint8_t Bap_aru8VersionInfo[BAP_BIT32_BYTES];
#else
#   define BAP_START_SEC_VAR_NO_INIT_8
#   include <BAP_MemMap.h>
/* MISRA 2012 8.4 removal */
extern DBGVAR uint8_t Bap_aru8VersionInfo[BAP_BIT32_BYTES];

DBGVAR uint8_t Bap_aru8VersionInfo[BAP_BIT32_BYTES];
#   define BAP_STOP_SEC_VAR_NO_INIT_8
#   include <BAP_MemMap.h>
#endif /* #ifdef DLL_COMPILATION */

/**
 * MISRA-2004 fix: Rule 1.2 near auto address
 * Definiere als globale Variable, vorher lokale Variable in Fct BAP_BPL_DataReceived
 */
#ifdef DLL_COMPILATION
extern BapIndication_et Bap_eIndication;
#else
#   define BAP_START_SEC_VAR_NO_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>
/* MISRA 2012 8.4 */
extern DBGVAR BapIndication_et Bap_eIndication;

DBGVAR BapIndication_et Bap_eIndication;
#   define BAP_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>
#endif /* #ifdef DLL_COMPILATION */


/* Multiconfig Index-Table neu generieren für BapGetLsgRomRow */
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
extern bool_t Bap_reAssignLsgRomRowFctTable  ;
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>



/* Interne Makro-Definitionen */

/* Interne Typ-Definitionen */


/* Interne Const Deklarationen */

/* Interne statische Variablen */

/* Vorwaerts-Deklarationen von statischen Funktionen */

BAP_STATIC BAP_IMPL_FAR BapError_et
BAP_BAL_Init(bool_t abIsShutdown, lsgId_t aLsgId);

/* Definition (Implementierung) von statischen Funktionen */

/**
 *  Diese Funktion initialisiert die darunterliegenden Schichten.
 *
 *  @param abIsShutdown - Entscheidet darueber, welche Zustaende erlaubt sind.
 *
 *  @param aLsgId - gibt an, welches Lsg initialisiert werden soll.
 *
 *  @remarks: Wird sowohl von BAP_Init als auch BAP_Shutdown verwendet.
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_STATIC BAP_IMPL_FAR BapError_et
BAP_BAL_Init(bool_t abIsShutdown, lsgId_t aLsgId)
{
    /* Zum Zwischenspeichern des Funktionsergebnisses */
    DBGVAR BapError_et eResult;

    BapLsgRomRow_pot poLsgRomRow;

    /* Index Table in BAP_GetLsgRomRow neu erzeugen */
    Bap_reAssignLsgRomRowFctTable = BAP_TRUE;
    
    /* Bedingung muss sein: in pLsgRomRowTable keine NULL Eintraege */
    poLsgRomRow = BAP_GetLsgRomRow(aLsgId);

    if (NULL == poLsgRomRow)
    {
        BAP_DBG_InvalidArgError(aLsgId);
        eResult = BapErr_InvalidArg;
    }
    else
    /* Ueberpruefe Zustandsmaschine */
    if (abIsShutdown != ((BapLayerLsgStat_NoInit != poLsgRomRow->poLsgRamRow->eLsgStatus)? BAP_TRUE : BAP_FALSE))
    {
        BAP_DBG_InvalidStateError(aLsgId);
        eResult = BapErr_InvalidState;
    }
    else
    {
        /* Die darunterliegende Schicht initialisieren */
        BAP_BPL_Init(poLsgRomRow);
        eResult = BapErr_OK;
    }

    if(eResult == BapErr_OK)
    {
        /*NULLpointer wird ueber eResult oben abgefangen */
        /*lint -esym(613, poLsgRomRow) */
        poLsgRomRow->poLsgRamRow->eLsgStatus = BapLayerLsgStat_Initialized;

#ifdef BAP_FSG
#if defined(BAP_ASG) && defined(BAP_FSG)
        if (BapSG_FSG == poLsgRomRow->eSGType)
#endif /* defined(BAP_ASG) && defined(BAP_FSG) */
        {
#ifdef BAP_USES_ASR_WRAPPER            
            /*SSWPPB53: In AUTOSAR with RTE, 
            During warmstart, RAM settings for BAP_Config, Functionlist and heartbeat 
            shall be retained when NM layer calls the BAP_Shutdown routine*/
            if (abIsShutdown == BAP_FALSE)
#endif /* BAP_USES_ASR_WRAPPER */       
			{
				/* Das FSG kopiert die default ROM Fct.list in den RAM Buffer */
				/*lint -e9087*/ /* MISRA_2012_REQ_11.3 : 1st and 2nd arguments of MEMCPY are of types (uint8_t*).
								 * They are implicitly cast to (void*). The memory is packed because it is uint8_t so there should be no problem to copy.*/
				FAR_MEMCPY  (poLsgRomRow->poLsgRamRow->BAP_aru8FunctionList
					 , poLsgRomRow->BAP_aru8FunctionList
					 , BAP_FCTID_FCTLIST_SIZE);
				/*lint +e9087*/
					 
				/* Das FSG kopiert die default ROM Cfg.list in den RAM Buffer */
				/*lint -e9087*/ /* MISRA_2012_REQ_11.3 : 1st and 2nd arguments of MEMCPY are of types (uint8_t*).
								 * They are implicitly cast to (void*). The memory is packed because it is uint8_t so there should be no problem to copy.*/
				FAR_MEMCPY  (poLsgRomRow->poLsgRamRow->BapBAPConfig_t
					 , BAP_BAPConfigTable[poLsgRomRow->u8BAPConfigTableIndex]
					 , BAP_FCTID_BAPCONFIG_SIZE);
				/*lint +e9087*/
					 
				/* Das FSG muss die internen FctIds im Sendepuffer setzen */
				eResult = BAP_BAL_InitFSGBuffers(poLsgRomRow);
			}
		}
#endif /* #ifdef BAP_FSG */
#ifdef BAP_ASG
#if defined(BAP_ASG) && defined(BAP_FSG)
        else
#endif /* defined(BAP_ASG) && defined(BAP_FSG) */
        {
            /* Das ASG muss den Cache initialisieren */
            /* Fct.list aus ROM wird in das RAM uebernommen */
            BAP_BAL_InvalidateCache(poLsgRomRow);
        }
#endif /* #ifdef BAP_ASG */

        BAP_DBG_SetBalState(aLsgId, BapLayerLsgStat_Initialized);
        /*lint +esym(613, poLsgRomRow) */
    }
    return eResult;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


/* Definition (Implementierung) von globalen Funktionen */

/*
 *  Diese Funktion ist in bap.h dokumentiert
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_IMPL_FAR BapError_et
BAP_RequestVoid(const lsgId_t aLsgId
    , const fctId_t aFctId
    , const BapRequest_et aeRequest)
{
    DBGVAR BapError_et eResult = BapErr_InvalidArg;

    BAP_InitInternalParameters(&Bap_oPars);
    Bap_oPars.lsgId = aLsgId;
    Bap_oPars.fctId = aFctId;

    eResult = BAP_BAL_CheckRequest(&Bap_oPars, aeRequest, BapChkDt_VoidIn);

    if ( (BapErr_OK == eResult) && ((Bap_oPars.poLsgRomRow->bNewLsgId)!= BAP_TRUE) && ( ( (uint8_t)aLsgId == (uint8_t)BAP_RESERVED_LSG_ID ) || ( (uint8_t)aLsgId > (uint8_t)BAP_MAX_LSG_ID ) ) )
    {
        eResult = BapErr_InvalidArg;
    }

    /* Fuer das Kombigeraet muessen hier keine SG Unterscheidungen gemacht werden, da
       eOpCode bereits in CheckRequest mit dem SG Type bestimmt wird. Passt der Request
       nicht zum SG Type so gibt es BapOpInvalid und keine Aktion ausgefuehrt
       Die #ifdefs bleiben drin fuer die Einzelvarianten*/
    if((BapErr_OK == eResult) && (BapOp_Invalid != Bap_oPars.eOpCode))
    {
        /* Aktionen je nach RequestType ausfuehren */
        switch(aeRequest)
        {
#ifdef BAP_FSG
            case BapReq_Data:       /* speziell fuer VOID Datentyp */
            case BapReq_DataAck:    /* speziell fuer VOID Datentyp */
                eResult = BAP_BPL_Send(&Bap_oPars);
                break;
#ifdef BAP_USES_METHODS
            case BapReq_Processing: /* speziell fuer VOID Datentyp */
            case BapReq_Result:     /* speziell fuer VOID Datentyp */
                eResult = BAP_BPL_Send(&Bap_oPars);
                break;
#endif /* #ifdef BAP_USES_METHODS */
#endif /* #ifdef BAP_FSG */
#ifdef BAP_ASG
            case BapReq_Abort:
            case BapReq_Start:      /* speziell fuer VOID Datentyp */
            case BapReq_StartResult:/* speziell fuer VOID Datentyp */
            case BapReq_DataSetGet: /* speziell fuer VOID Datentyp */
            case BapReq_DataSet:    /* speziell fuer VOID Datentyp */
            case BapReq_Ack:        /* speziell fuer VOID Datentyp */
                eResult = BAP_BPL_Send(&Bap_oPars);
                break;
            case BapReq_DataGet:
                eResult = BAP_BAL_RequestVoidGet(&Bap_oPars);
                break;
#endif /* #ifdef BAP_ASG */
            /* alle anderen RequestTypes sind nicht erlaubt bei Void */
            /* BapReq_Invalid, BapReq_Changed */
            default:
                BAP_DBG_InvalidArgError(Bap_oPars.lsgId);
                eResult = BapErr_InvalidArg;
                break;
        }
    }
    return eResult;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


#ifdef BAP_USES_DATATYPE_8
/*
 *  Diese Funktion ist in bap.h dokumentiert
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR BapError_et
BAP_RequestInt8(const lsgId_t aLsgId
    , const fctId_t aFctId
    , const BapRequest_et aeRequest
    , const uint8_t au8Data)
{
    DBGVAR BapError_et eResult;

    Bap_aru8SendData[0] = au8Data;

    BAP_InitInternalParameters(&Bap_oPars);
    Bap_oPars.lsgId = aLsgId;
    Bap_oPars.fctId = aFctId;
    Bap_oPars.u32Length = BAP_INT8_SIZE;
    Bap_oPars.pData = Bap_aru8SendData;

    eResult = BAP_BAL_CheckRequest(&Bap_oPars, aeRequest, BapChkDt_ScalarIn);

    /* Fuer das Kombigeraet muessen hier keine SG Unterscheidungen gemacht werden, da
       eOpCode bereits in CheckRequest mit dem SG Type bestimmt wird. Passt der Request
       nicht zum SG Type so gibt es BapOpInvalid und keine Aktion ausgefuehrt
       Die #ifdefs bleiben drin fuer die Einzelvarianten*/
    if((BapErr_OK == eResult) && (BapOp_Invalid != Bap_oPars.eOpCode))
    {
        /* Aktionen je nach RequestType ausfuehren */
        switch(aeRequest)
        {
#ifdef BAP_ASG
            case BapReq_DataSetGet:
            case BapReq_DataSet:
            case BapReq_Ack:
            case BapReq_Start:
            case BapReq_StartResult:
#endif /* BAP_ASG */
#ifdef BAP_FSG
            case BapReq_Data:
            case BapReq_DataAck:
#ifdef BAP_USES_METHODS
            case BapReq_Result:
            case BapReq_Processing:
#endif /* BAP_USES_METHODS */
#endif /* BAP_FSG */
                eResult = BAP_BPL_Send(&Bap_oPars);
                break;
            /* alle anderen RequestTypes sind nicht erlaubt bei Int8 */
            /* BapReq_DataGet, BapReq_Abort, BapReq_Changed, BapReq_Processing, BapReq_Invalid */
            default:
                BAP_DBG_InvalidArgError(Bap_oPars.lsgId);
                eResult = BapErr_InvalidArg;
                break;
        }
    }
    return eResult;
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_USES_DATATYPE_8 */


#ifdef BAP_USES_DATATYPE_16
/*
 *  Diese Funktion ist in bap.h dokumentiert
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR BapError_et
BAP_RequestInt16(const lsgId_t aLsgId
    , const fctId_t aFctId
    , const BapRequest_et aeRequest
    , const uint16_t au16Data)
{
    DBGVAR BapError_et eResult;

    /* Wert vor dem Senden ins Little-Endian-Format konvertieren */
    BAP_BAL_Int16toDataStream(au16Data, Bap_aru16SendData);

    BAP_InitInternalParameters(&Bap_oPars);
    Bap_oPars.lsgId = aLsgId;
    Bap_oPars.fctId = aFctId;
    Bap_oPars.u32Length = BAP_INT16_SIZE;
    Bap_oPars.pData = Bap_aru16SendData;

    eResult = BAP_BAL_CheckRequest(&Bap_oPars, aeRequest, BapChkDt_ScalarIn);

    if ( (BapErr_OK == eResult) && ((Bap_oPars.poLsgRomRow->bNewLsgId)!= BAP_TRUE) && ( ( (uint8_t)aLsgId == (uint8_t)BAP_RESERVED_LSG_ID ) || ( (uint8_t)aLsgId > (uint8_t)BAP_MAX_LSG_ID ) ) )
    {
        eResult = BapErr_InvalidArg;
    }

    /* Fuer das Kombigeraet muessen hier keine SG Unterscheidungen gemacht werden, da
       eOpCode bereits in CheckRequest mit dem SG Type bestimmt wird. Passt der Request
       nicht zum SG Type so gibt es BapOpInvalid und keine Aktion ausgefuehrt
       Die #ifdefs bleiben drin fuer die Einzelvarianten*/
    if((BapErr_OK == eResult) && (BapOp_Invalid != Bap_oPars.eOpCode))
    {
        /* Aktionen je nach RequestType ausfuehren */
        switch(aeRequest)
        {
#ifdef BAP_ASG
            case BapReq_DataSetGet:
            case BapReq_DataSet:
            case BapReq_Ack:
            case BapReq_Start:
            case BapReq_StartResult:
#endif /* BAP_ASG */
#ifdef BAP_FSG
            case BapReq_Data:
            case BapReq_DataAck:
#ifdef BAP_USES_METHODS
            case BapReq_Result:
            case BapReq_Processing:
#endif /* BAP_USES_METHODS */
#endif /* BAP_FSG */
                eResult = BAP_BPL_Send(&Bap_oPars);
                break;
            /* alle anderen RequestTypes sind nicht erlaubt bei Int16 */
            /* BapReq_DataGet, BapReq_Abort, BapReq_Changed, BapReq_Processing, BapReq_Invalid */
            default:
                BAP_DBG_InvalidArgError(Bap_oPars.lsgId);
                eResult = BapErr_InvalidArg;
                break;
        }
    }
    return eResult;
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_USES_DATATYPE_16 */


#ifdef BAP_USES_DATATYPE_32
/*
 *  Diese Funktion ist in bap.h dokumentiert
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR BapError_et
BAP_RequestInt32(const lsgId_t aLsgId
    , const fctId_t aFctId
    , const BapRequest_et aeRequest
    , const uint32_t au32Data)
{
    DBGVAR BapError_et eResult;

    /* Wert vor dem Senden ins Little-Endian-Format konvertieren */
    BAP_BAL_Int32toDataStream(au32Data, Bap_aru32SendData);

    BAP_InitInternalParameters(&Bap_oPars);
    Bap_oPars.lsgId = aLsgId;
    Bap_oPars.fctId = aFctId;
    Bap_oPars.u32Length = BAP_INT32_SIZE;
    Bap_oPars.pData = Bap_aru32SendData;

    eResult = BAP_BAL_CheckRequest(&Bap_oPars, aeRequest, BapChkDt_ScalarIn);

    if ( (BapErr_OK == eResult) && ((Bap_oPars.poLsgRomRow->bNewLsgId)!= BAP_TRUE) && ( ( (uint8_t)aLsgId == (uint8_t)BAP_RESERVED_LSG_ID ) || ( (uint8_t)aLsgId > (uint8_t)BAP_MAX_LSG_ID ) ) )
    {
        eResult = BapErr_InvalidArg;
    }

    /* Fuer das Kombigeraet muessen hier keine SG Unterscheidungen gemacht werden, da
       eOpCode bereits in CheckRequest mit dem SG Type bestimmt wird. Passt der Request
       nicht zum SG Type so gibt es BapOpInvalid und keine Aktion ausgefuehrt
       Die #ifdefs bleiben drin fuer die Einzelvarianten*/
    if((BapErr_OK == eResult) && (BapOp_Invalid != Bap_oPars.eOpCode))
    {
        /* Aktionen je nach RequestType ausfuehren */
        switch(aeRequest)
        {
#ifdef BAP_ASG
            case BapReq_DataSetGet:
            case BapReq_DataSet:
            case BapReq_Ack:
            case BapReq_Start:
            case BapReq_StartResult:
#endif /* BAP_ASG */
#ifdef BAP_FSG
            case BapReq_Data:
            case BapReq_DataAck:
#ifdef BAP_USES_METHODS
            case BapReq_Result:
            case BapReq_Processing:
#endif /* BAP_USES_METHODS */
#endif /* BAP_FSG */
                eResult = BAP_BPL_Send(&Bap_oPars);
                break;
            /* alle anderen RequestTypes sind nicht erlaubt bei Int32 */
            /* BapReq_DataGet, BapReq_Abort, BapReq_Changed, BapReq_Processing, BapReq_Invalid */
            default:
                BAP_DBG_InvalidArgError(Bap_oPars.lsgId);
                eResult = BapErr_InvalidArg;
                break;
        }
    }
    return eResult;
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_USES_DATATYPE_32 */


#ifdef BAP_USES_DATATYPE_BS
/*
 *  Diese Funktion ist in bap.h dokumentiert
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR BapError_et
BAP_RequestByteSequence(const lsgId_t aLsgId
    , const fctId_t aFctId
    , const BapRequest_et aeRequest
    , const uint8_t apData[]
    , const uint32_t au32Length)
{
    DBGVAR BapError_et eResult = BapErr_OK;
    BAP_InitInternalParameters(&Bap_oPars);

    if ( (NULL == apData) && (au32Length > (uint32_t)0) )
    {
        eResult = BapErr_InvalidArg;
    }
    if (BapErr_OK == eResult)
    {
        Bap_oPars.lsgId = aLsgId;
        Bap_oPars.fctId = aFctId;
        Bap_oPars.pData = apData;
        Bap_oPars.u32Length = au32Length;

        eResult = BAP_BAL_CheckRequest(&Bap_oPars, aeRequest, BapChkDt_VariableIn);
    }
    if ( (BapErr_OK == eResult) && ((Bap_oPars.poLsgRomRow->bNewLsgId)!= BAP_TRUE) && ( ( (uint8_t)aLsgId == (uint8_t)BAP_RESERVED_LSG_ID ) || ( (uint8_t)aLsgId > (uint8_t)BAP_MAX_LSG_ID ) ) )
    {
        eResult = BapErr_InvalidArg;
    }

    /* Fuer das Kombigeraet muessen hier keine SG Unterscheidungen gemacht werden, da
       eOpCode bereits in CheckRequest mit dem SG Type bestimmt wird. Passt der Request
       nicht zum SG Type so gibt es BapOpInvalid und keine Aktion ausgefuehrt
       Die #ifdefs bleiben drin fuer die Einzelvarianten*/
    /*lint -esym(644,Bap_oPars)*/
    if((BapErr_OK == eResult) && (BapOp_Invalid != Bap_oPars.eOpCode))
    /*lint +esym(644,Bap_oPars)*/
    {
        /* Aktionen je nach RequestType ausfuehren */
        switch(aeRequest)
        {
#ifdef BAP_ASG
            case BapReq_DataSetGet:
            case BapReq_DataSet:
            case BapReq_Ack:
            case BapReq_Start:
            case BapReq_StartResult:
#endif /* BAP_ASG */
#ifdef BAP_FSG
            case BapReq_Data:
            case BapReq_DataAck:
#ifdef BAP_USES_METHODS
            case BapReq_Result:
            case BapReq_Processing:
#endif /* BAP_USES_METHODS */
#endif /* BAP_FSG */
                eResult = BAP_BPL_Send(&Bap_oPars);
                break;
#ifdef BAP_ASG
            case BapReq_DataGet: /* Ist nur fuer Arrays im ASG erlaubt */
#endif /* BAP_ASG */
#ifdef BAP_USES_ARRAYS
#ifdef BAP_FSG
            case BapReq_Changed: /* Ist nur fuer Arrays im FSG erlaubt */
#endif /* BAP_FSG */
                if(BapFctCls_Array == Bap_oPars.poFctRomRow->eFunctionClass)
                {
                    eResult = BAP_BPL_Send(&Bap_oPars);
                }
                else
                {
                    BAP_DBG_InvalidArgError(Bap_oPars.lsgId);
                    eResult = BapErr_InvalidArg;
                }
                break;
#endif /* #ifdef BAP_USES_ARRAYS */
            /* alle anderen RequestTypes sind nicht erlaubt bei ByteSequence: */
            /* BapReq_Abort, BapReq_Processing, BapReq_Invalid */
            /* BapReq_DataGet und BapReq_Changed sind nur bei Arrays erlaubt */
            default:
                BAP_DBG_InvalidArgError(Bap_oPars.lsgId);
                eResult = BapErr_InvalidArg;
                break;
        }
    }
    return eResult;
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_USES_DATATYPE_BS */

#ifdef BAP_FSG
/*
 *  Diese Funktion ist in bap.h dokumentiert
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR BapError_et
BAP_RequestError(const lsgId_t aLsgId
    , const fctId_t aFctId
    , const BapError_et aeErrorCode)
{
    DBGVAR BapError_et eResult = BapErr_OK;

    Bap_u8ErrorCode = (uint8_t) aeErrorCode;

    Bap_oPars.lsgId = aLsgId;
    Bap_oPars.fctId = aFctId;
    Bap_oPars.poLsgRomRow = BAP_GetLsgRomRow(Bap_oPars.lsgId);
    Bap_oPars.poFctRomRow = BAP_GetLsgFctRomRow(Bap_oPars.poLsgRomRow, Bap_oPars.fctId);

    /* SSWPPB[93] solution for critical polyspace finding */
    if ((NULL != Bap_oPars.poLsgRomRow)) /* prevent segmentation fault when access Bap_oPars.poLsgRomRow->bNewLsgId variable */
    {
    	/* MISRA_2012_REQ_14.3 : "((uint8_t) aLsgId >= (uint8_t) 64))" is not invariant,
    	 * but it should never be True except in case of issue. */
        if (((Bap_oPars.poLsgRomRow->bNewLsgId) != BAP_TRUE)
                && (((uint8_t) aLsgId == (uint8_t) BAP_RESERVED_LSG_ID) || ((uint8_t) aLsgId > (uint8_t) BAP_MAX_LSG_ID)))
        {
            eResult = BapErr_InvalidArg;
        }
    }

    /* Pruefen ob die Funktion existiert und der ErrorCode erlaubt ist (kein interner Fehlerwert) */
    /* MISRA_2012_REQ_14.3 : "(BAP_BINARY_ID(Bap_oPars.fctId) >(uint8_t) BAP_MAX_FCT_ID) " is not invariant,
        	 * but it should never be True except in case of issue. */
    if( (NULL == Bap_oPars.poFctRomRow) 
#if defined(BAP_ASG) && defined(BAP_FSG)
        /*lint !e613 wenn poLsgRomRow = NULL dann ist auch poFctRomRow = NULL */
        || (BapSG_FSG != Bap_oPars.poLsgRomRow->eSGType) /* Error darf nur fuer FSG aufgerufen werden */
#endif /* defined(BAP_ASG) && defined(BAP_FSG)  */
        || (BAP_BINARY_ID(Bap_oPars.fctId) >(uint8_t) BAP_MAX_FCT_ID) /*lint !e650 enums haben mindestens 8 bit */ /*lint !e685 bei BAP_USES_NAMED_IDS */
        || (((uint8_t)BAP_MAX_ERROR_CODE >= (uint8_t)aeErrorCode) && (BapErr_OK != aeErrorCode)))
    {
        BAP_DBG_InvalidArgError(Bap_oPars.lsgId);
        eResult = BapErr_InvalidArg;
    }
    /* Ueberpruefe Zustandsmaschine */
    /* SSWPPB[93] solution for critical polyspace finding */
    else if( (NULL != Bap_oPars.poLsgRomRow) ) 
    {
        if(BapLayerLsgStat_Running != Bap_oPars.poLsgRomRow->poLsgRamRow->eLsgStatus)
        {
            BAP_DBG_InvalidStateError(Bap_oPars.lsgId);
            eResult = BapErr_InvalidState;
        }else{
            Bap_oPars.eOpCode = BapOp_PropError;
            Bap_oPars.pData = &Bap_u8ErrorCode;
            Bap_oPars.u32Length = 1u;
            eResult = BAP_BPL_SendError(&Bap_oPars);
        }
    }
    else {
    	/* Do Nothing (for lint) */
    }

    return eResult;
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* #ifdef BAP_FSG */


#if defined(BAP_ASG)  && defined (BAP_USES_DATATYPE_8)
/*
 *  Diese Funktion ist in bap.h dokumentiert
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR BapError_et
BAP_CacheGetRequestInt8(const lsgId_t aLsgId
    , const fctId_t aFctId
    , uint8_t * const apu8OutData)
{
    DBGVAR BapError_et eResult;

    BAP_InitInternalParameters(&Bap_oPars);

    /* Pointer muss existieren */
    if (NULL == apu8OutData)
    {
        eResult = BapErr_InvalidArg;
    }
    else
    {
        Bap_oPars.lsgId = aLsgId;
        Bap_oPars.fctId = aFctId;
        Bap_oPars.u32Length = BAP_INT8_SIZE;

        eResult = BAP_BAL_CheckRequest(&Bap_oPars, BapReq_Invalid, BapChkDt_ScalarOut);

        if ( (BapErr_OK == eResult) && ((Bap_oPars.poLsgRomRow->bNewLsgId)!= BAP_TRUE) && ( ( (uint8_t)aLsgId == (uint8_t)BAP_RESERVED_LSG_ID ) || ( (uint8_t)aLsgId > (uint8_t)BAP_MAX_LSG_ID ) ) )
        {
            eResult = BapErr_InvalidArg;
        }
    }
    /*lint -esym(644,Bap_oPars)*/ /* Wurde durch BAP_BAL_CheckRequest gesetzt */
    /*lint -esym(613,Bap_oPars)*/
    BAP_ASSERT(NULL != &Bap_oPars);
#if defined(BAP_ASG) && defined(BAP_FSG)
    /* CacheGet darf nur fuer ASG aufgerufen werden! */
    /* Erste bedingung stellt sicher das LSG&FCT auch existieren (CheckRequest)! */
    if ((BapErr_OK == eResult) && (BapSG_ASG != Bap_oPars.poLsgRomRow->eSGType))
    {
        eResult = BapErr_InvalidArg;
    }
#endif /* defined(BAP_ASG) && defined(BAP_FSG)  */

    if(BapErr_OK == eResult)
    {
        /* Cache muss vorhanden sein */
        if(NULL == Bap_oPars.poFctRomRow->poBalRamRow)
        {
            BAP_DBG_CacheNotAvailableError(Bap_oPars.lsgId);
            eResult = BapErr_CacheNotAvailable;
        }
        else
        {
            /* Einzelcache muss gueltig sein */
            /* *(BapBalDataStatus_et*)Bap_oPars.poFctRomRow->poBalRamRow enthaelt den eDataStatus*/
            if(   (BapBalDataStat_Valid ==    Bap_oPars.poFctRomRow->poBalRamRow->eDataStatus)
                ||(BapBalDataStat_GetAll ==   Bap_oPars.poFctRomRow->poBalRamRow->eDataStatus) )
            {
                /*lint -esym(613,apu8OutData)*/ /* Wird schon am Anfang geprueft */
                *apu8OutData = Bap_oPars.poFctRomRow->poBalRamRow->u8Value;
                /*lint +esym(613,apu8OutData)*/
            }
            else
            {
                BAP_DBG_CacheInvalidError(Bap_oPars.lsgId);
                eResult = BapErr_CacheInvalid;
            }
            /*lint +esym(644,Bap_oPars)*/
        }
    }
    /*lint +esym(613,apu8OutData)*/
    /*lint +esym(644,Bap_oPars)*/
    return eResult;
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* ASG && BAP_USES_DATATYPE_8 */


#if defined(BAP_ASG)  && defined (BAP_USES_DATATYPE_16)
/*
 *  Diese Funktion ist in bap.h dokumentiert
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR BapError_et
BAP_CacheGetRequestInt16(const lsgId_t aLsgId
    , const fctId_t aFctId
    , uint16_t * const apu16OutData)
{
    DBGVAR BapError_et eResult;

    BAP_InitInternalParameters(&Bap_oPars);

    /* Pointer muss existieren */
    if (NULL == apu16OutData)
    {
        eResult = BapErr_InvalidArg;
    }
    else
    {
        Bap_oPars.lsgId = aLsgId;
        Bap_oPars.fctId = aFctId;
        Bap_oPars.u32Length = BAP_INT16_SIZE;

        eResult = BAP_BAL_CheckRequest(&Bap_oPars, BapReq_Invalid, BapChkDt_ScalarOut);
        if ( (BapErr_OK == eResult) && ((Bap_oPars.poLsgRomRow->bNewLsgId)!= BAP_TRUE) && ( ( (uint8_t)aLsgId == (uint8_t)BAP_RESERVED_LSG_ID ) || ( (uint8_t)aLsgId > (uint8_t)BAP_MAX_LSG_ID ) ) )
        {
            eResult = BapErr_InvalidArg;
        }
    }
    /*lint -esym(644,Bap_oPars)*/ /* wird durch BAP_BAL_CheckRequest initialisiert*/
#if defined(BAP_ASG) && defined(BAP_FSG)
    /* CacheGet darf nur fuer ASG aufgerufen werden! */
    /* Erste bedingung stellt sicher das LSG&FCT auch existieren (CheckRequest)! */
    if ( (BapErr_OK == eResult) && (BapSG_ASG != Bap_oPars.poLsgRomRow->eSGType) )  /*lint !e644 (in BAP_BAL_CheckRequest) */
    {
        eResult = BapErr_InvalidArg;
    }
#endif /* defined(BAP_ASG) && defined(BAP_FSG)  */

    if(BapErr_OK == eResult)
    {
        /* Cache muss vorhanden sein */
        if(NULL == Bap_oPars.poFctRomRow->poBalRamRow)  /*lint !e644 (in BAP_BAL_CheckRequest) */
        {
            BAP_DBG_CacheNotAvailableError(Bap_oPars.lsgId);
            eResult = BapErr_CacheNotAvailable;
        }
        else
        {
            /* Einzelcache muss gueltig sein */
            /* *(BapBalDataStatus_et*)Bap_oPars.poFctRomRow->poBalRamRow enthaelt den eDataStatus*/
            if(   (BapBalDataStat_Valid == Bap_oPars.poFctRomRow->poBalRamRow->eDataStatus)
                ||(BapBalDataStat_GetAll == Bap_oPars.poFctRomRow->poBalRamRow->eDataStatus) )
            {
                /*lint -esym(613,apu16OutData)*/ /* Wird durch Abfrage zu Beginn abgefangen */
                *apu16OutData = Bap_oPars.poFctRomRow->poBalRamRow->u16Value;
                /*lint +esym(613,apu16OutData)*/
            }
            else
            {
                BAP_DBG_CacheInvalidError(Bap_oPars.lsgId);
                eResult = BapErr_CacheInvalid;
            }
        }
    }
    /*lint +esym(644,Bap_oPars)*/
    return eResult;
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* ASG && BAP_USES_DATATYPE_16 */


#if defined(BAP_ASG)  && defined (BAP_USES_DATATYPE_32)
/*
 *  Diese Funktion ist in bap.h dokumentiert
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR BapError_et
BAP_CacheGetRequestInt32(const lsgId_t aLsgId
    , const fctId_t aFctId
    , uint32_t * const apu32OutData)
{
    DBGVAR BapError_et eResult;

    BAP_InitInternalParameters(&Bap_oPars);

    /* Pointer muss existieren */
    if (NULL == apu32OutData)
    {
        eResult = BapErr_InvalidArg;
    }
    else
    {
        Bap_oPars.lsgId = aLsgId;
        Bap_oPars.fctId = aFctId;
        Bap_oPars.u32Length = BAP_INT32_SIZE;

        eResult = BAP_BAL_CheckRequest(&Bap_oPars, BapReq_Invalid, BapChkDt_ScalarOut);
        if ( (BapErr_OK == eResult) && ((Bap_oPars.poLsgRomRow->bNewLsgId)!= BAP_TRUE) && ( ( (uint8_t)aLsgId == (uint8_t)BAP_RESERVED_LSG_ID ) || ( (uint8_t)aLsgId > (uint8_t)BAP_MAX_LSG_ID ) ) )
        {
            eResult = BapErr_InvalidArg;
        }
    }
    /*lint -esym(644,Bap_oPars)*/ /* wird durch BAP_BAL_CheckRequest initialisiert*/
#if defined(BAP_ASG) && defined(BAP_FSG)
    /* CacheGet darf nur fuer ASG aufgerufen werden! */
    /* Erste bedingung stellt sicher das LSG&FCT auch existieren (CheckRequest)! */
    if ( (BapErr_OK == eResult) && (BapSG_ASG != Bap_oPars.poLsgRomRow->eSGType) )  /*lint !e644 (in BAP_BAL_CheckRequest) */
    {
        eResult = BapErr_InvalidArg;
    }
#endif /* defined(BAP_ASG) && defined(BAP_FSG)  */

    if(BapErr_OK == eResult)
    {
        /* Cache muss vorhanden sein */
        if(NULL == Bap_oPars.poFctRomRow->poBalRamRow)  /*lint !e644 (in BAP_BAL_CheckRequest) */
        {
            BAP_DBG_CacheNotAvailableError(Bap_oPars.lsgId);
            eResult = BapErr_CacheNotAvailable;
        }
        else
        {
            /* Einzelcache muss gueltig sein */
            /* *(BapBalDataStatus_et*)Bap_oPars.poFctRomRow->poBalRamRow enthaelt den eDataStatus*/
            if(   (BapBalDataStat_Valid == Bap_oPars.poFctRomRow->poBalRamRow->eDataStatus)
                ||(BapBalDataStat_GetAll == Bap_oPars.poFctRomRow->poBalRamRow->eDataStatus) )
            {
                /*lint -esym(613,apu32OutData)*/ /* Wird durch Abfrage zu Beginn abgefangen */
                *apu32OutData = Bap_oPars.poFctRomRow->poBalRamRow->u32Value;
                /*lint +esym(613,apu32OutData)*/
            }
            else
            {
                BAP_DBG_CacheInvalidError(Bap_oPars.lsgId);
                eResult = BapErr_CacheInvalid;
            }
        }
    }
    /*lint +esym(644,Bap_oPars)*/
    return eResult;
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* ASG && BAP_USES_DATATYPE_32 */


#if defined(BAP_ASG)  && defined (BAP_USES_DATATYPE_BS)
/*
 *  Diese Funktion ist in bap.h dokumentiert
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR BapError_et
BAP_CacheGetRequestByteSequence(const lsgId_t aLsgId
    , const fctId_t aFctId
    , ptr_t * const appOutData
    , uint32_t * const apu32OutLength)
{
    DBGVAR BapError_et eResult = BapErr_OK;
    BapBufferWithLength_pot pBufWLen;

    BAP_InitInternalParameters(&Bap_oPars);

    /* Pointer muessen existieren */
    if ( (NULL == appOutData) || (NULL == apu32OutLength) )
    {
        eResult = BapErr_InvalidArg;
    }

    if (BapErr_OK == eResult)
    {
        Bap_oPars.lsgId = aLsgId;
        Bap_oPars.fctId = aFctId;
        Bap_oPars.u32Length = BAP_VOID_SIZE;    /* Bei CacheGet ist es egal welcher Parameter */

        eResult = BAP_BAL_CheckRequest(&Bap_oPars, BapReq_Invalid, BapChkDt_VariableOut);
        if ( (BapErr_OK == eResult) && ((Bap_oPars.poLsgRomRow->bNewLsgId)!= BAP_TRUE) && ( ( (uint8_t)aLsgId == (uint8_t)BAP_RESERVED_LSG_ID ) || ( (uint8_t)aLsgId > (uint8_t)BAP_MAX_LSG_ID ) ) )
        {
            eResult = BapErr_InvalidArg;
        }
    }
    /*lint -esym(644,Bap_oPars)*/ /* wird durch BAP_BAL_CheckRequest initialisiert*/
#if defined(BAP_ASG) && defined(BAP_FSG)
    /* CacheGet darf nur fuer ASG aufgerufen werden! */
    /* Erste bedingung stellt sicher das LSG&FCT auch existieren (CheckRequest)! */
    if ( (BapErr_OK == eResult) && (BapSG_ASG != Bap_oPars.poLsgRomRow->eSGType) )  /*lint !e644 (in BAP_BAL_CheckRequest) */
    {
        eResult = BapErr_InvalidArg;
    }
#endif /* defined(BAP_ASG) && defined(BAP_FSG)  */

    if(eResult == BapErr_OK)
    {
        /* Cache muss vorhanden sein */
        if(NULL == Bap_oPars.poFctRomRow->poBalRamRow)  /*lint !e644 (in BAP_BAL_CheckRequest) */
        {
            BAP_DBG_CacheNotAvailableError(Bap_oPars.lsgId);
            eResult = BapErr_CacheNotAvailable;
        }
        else
        {
            /* Einzelcache muss gueltig sein */
            /* *(BapBalDataStatus_et*)Bap_oPars.poFctRomRow->poBalRamRow enthaelt den eDataStatus*/
            if(   (BapBalDataStat_Valid == Bap_oPars.poFctRomRow->poBalRamRow->eDataStatus)
                ||(BapBalDataStat_GetAll == Bap_oPars.poFctRomRow->poBalRamRow->eDataStatus) )
            {
                pBufWLen = &Bap_oPars.poFctRomRow->poBalRamRow->oBufferWithLength;
                /*lint -esym(613,appOutData)*/ /* Wird durch Abfrage zu Beginn abgefangen */
                *appOutData =   *(pBufWLen->paru8Buffer);
                /*lint +esym(613,appOutData)*/
                /*lint -esym(613,apu32OutLength)*/
                *apu32OutLength = pBufWLen->u32Length;
                /*lint +esym(613,apu32OutLength)*/
            }
            else
            {
                BAP_DBG_CacheInvalidError(Bap_oPars.lsgId);
                eResult = BapErr_CacheInvalid;
            }
        }
    }
    /*lint +esym(644,Bap_oPars)*/
    return eResult;
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* ASG && BAP_USES_DATATYPE_BS */


#if defined(BAP_FSG)  && defined (BAP_USES_DATATYPE_8)
/*
 *  Diese Funktion ist in bap.h dokumentiert
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR BapError_et
BAP_InitSendBufferInt8(const lsgId_t aLsgId
    , const fctId_t aFctId
    , const uint8_t au8Data)
{
    DBGVAR BapError_et eResult;

    Bap_aru8SendData[0] = au8Data;

    BAP_InitInternalParameters(&Bap_oPars);
    Bap_oPars.lsgId = aLsgId;
    Bap_oPars.fctId = aFctId;
    Bap_oPars.u32Length = BAP_INT8_SIZE;
    Bap_oPars.pData = Bap_aru8SendData;

    eResult = BAP_BAL_CheckRequest(&Bap_oPars, BapReq_Invalid, BapChkDt_ScalarInit);

    if(eResult == BapErr_OK)
    {
#if defined(BAP_ASG) && defined(BAP_FSG)
        /* InitSendBuffer darf nur fuer FSG aufgerufen werden! */
        if (BapSG_FSG != Bap_oPars.poLsgRomRow->eSGType)
        {
            eResult = BapErr_InvalidArg;
        }
        else
#endif /* defined(BAP_ASG) && defined(BAP_FSG)  */
        {
            /* Schreibt den Wert runter in den BCL - der OpCode ist hier nur ein Dummy-Wert */
            BAP_BPL_BufferSet(&Bap_oPars);
        }
    }
    return eResult;
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* #if defined(BAP_FSG)  && defined (BAP_USES_DATATYPE_8) */


#if defined(BAP_FSG)  && defined (BAP_USES_DATATYPE_16)
/*
 *  Diese Funktion ist in bap.h dokumentiert
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR BapError_et
BAP_InitSendBufferInt16(const lsgId_t aLsgId
    , const fctId_t aFctId
    , const uint16_t au16Data)
{
    DBGVAR BapError_et eResult;

    BAP_BAL_Int16toDataStream(au16Data, Bap_aru16SendData);

    BAP_InitInternalParameters(&Bap_oPars);
    Bap_oPars.lsgId = aLsgId;
    Bap_oPars.fctId = aFctId;
    Bap_oPars.u32Length = BAP_INT16_SIZE;
    Bap_oPars.pData =  Bap_aru16SendData ;

    eResult = BAP_BAL_CheckRequest(&Bap_oPars, BapReq_Invalid, BapChkDt_ScalarInit);

    if(eResult == BapErr_OK)
    {
#if defined(BAP_ASG) && defined(BAP_FSG)
        /* InitSendBuffer darf nur fuer FSG aufgerufen werden! */
        if (BapSG_FSG != Bap_oPars.poLsgRomRow->eSGType)
        {
            eResult = BapErr_InvalidArg;
        }
        else
#endif /* defined(BAP_ASG) && defined(BAP_FSG)  */
        {
            /* Schreibt den Wert runter in den BCL - der OpCode ist hier nur ein Dummy-Wert ist */
            BAP_BPL_BufferSet(&Bap_oPars);
        }
    }
    return eResult;
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* #if defined(BAP_FSG)  && defined (BAP_USES_DATATYPE_16) */


#if defined(BAP_FSG) && defined (BAP_USES_DATATYPE_32)
/*
 *  Diese Funktion ist in bap.h dokumentiert
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR BapError_et
BAP_InitSendBufferInt32(const lsgId_t aLsgId
    , const fctId_t aFctId
    , const uint32_t au32Data)
{
    DBGVAR BapError_et eResult;

    BAP_BAL_Int32toDataStream(au32Data, Bap_aru32SendData);

    BAP_InitInternalParameters(&Bap_oPars);
    Bap_oPars.lsgId = aLsgId;
    Bap_oPars.fctId = aFctId;
    Bap_oPars.u32Length = BAP_INT32_SIZE;
    Bap_oPars.pData =  Bap_aru32SendData ;

    eResult = BAP_BAL_CheckRequest(&Bap_oPars, BapReq_Invalid, BapChkDt_ScalarInit);

    if(eResult == BapErr_OK)
    {
#if defined(BAP_ASG) && defined(BAP_FSG)
        /* InitSendBuffer darf nur fuer FSG aufgerufen werden! */
        if (BapSG_FSG != Bap_oPars.poLsgRomRow->eSGType)
        {
            eResult = BapErr_InvalidArg;
        }
        else
#endif /* defined(BAP_ASG) && defined(BAP_FSG)  */
        {
            /* Schreibt den Wert runter in den BCL - der OpCode ist hier nur ein Dummy-Wert */
            BAP_BPL_BufferSet(&Bap_oPars);
        }
    }
    return eResult;
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* #if defined(BAP_FSG)  && defined (BAP_USES_DATATYPE_32) */


#if defined(BAP_FSG)  && defined (BAP_USES_DATATYPE_BS)
/*
 *  Diese Funktion ist in bap.h dokumentiert
 *
 *  Diese Funktion hat 7 ControlNestingLayers (max.4)
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR BapError_et
BAP_InitSendBufferByteSequence(const lsgId_t aLsgId
    , const fctId_t aFctId
    , const uint8_t apData[]
    , const uint32_t au32Length)
{
    DBGVAR BapError_et eResult = BapErr_OK;
    BapLsgRomRow_pot poLsgRomRow;

    BAP_InitInternalParameters(&Bap_oPars);
    BAP_InitInternalParameters(&Bap_oPars_fctlist);

    //BAP_ASSERT(NULL != apData);

    Bap_oPars.lsgId = aLsgId;
    Bap_oPars.fctId = aFctId;
    Bap_oPars.u32Length = au32Length;
    Bap_oPars.pData = apData;
    poLsgRomRow = BAP_GetLsgRomRow(Bap_oPars.lsgId);

    /*lint -esym(613,apData) siehe nachfolgende Pruefung */
    /*lint -esym(644,poLsgRomRow)*/ /* Ist durch BAP_BAL_CheckRequest spaeter sichergestellt */
    if ( ((NULL == apData) && ((uint16_t)0 < au32Length))
            ||(NULL == poLsgRomRow) /* Pruefen ob die LsgRomRow existiert */
#if defined(BAP_ASG) && defined(BAP_FSG)
            ||( BapSG_FSG != poLsgRomRow->eSGType )  /*lint !e644 (in BAP_BAL_CheckRequest) */
#endif
    )
    {
        eResult = BapErr_InvalidArg;
    }else
    {
        /* falls das FSG im Status InvalidConfig ist, Status auf Initialized setzen, sonst geht BAP_BAL_CheckRequest schief */
    	/* MISRA_2012_REQ_10.5 : no risk arise because BAP_FCTID_BAPCONFIG fit in enum.*/
        if ( ((fctId_t)BAP_FCTID_BAPCONFIG == (fctId_t)Bap_oPars.fctId)
                && (poLsgRomRow->poLsgRamRow->eLsgStatus == BapLayerLsgStat_WaitForOrInvalidConfig)
            )
        {
                poLsgRomRow->poLsgRamRow->eLsgStatus = BapLayerLsgStat_Initialized;
                BAP_DBG_SetBalState(aLsgId, BapLayerLsgStat_Initialized);
        }

        /* Durch BAP_BAL_CheckRequest sichergestellt */
        eResult = BAP_BAL_CheckRequest(&Bap_oPars, BapReq_Invalid, BapChkDt_VariableInit);
    }

    if (eResult == BapErr_OK)
    {
        /*lint -esym(644,Bap_oPars)*/ // Bap_oPars is initialized line from 1276 to 1285, so no risk arise
    	/* MISRA_2012_REQ_10.5 : no risk arise  with the cast because BAP_FCTID_FCTLIST fit in enum.*/
        if (BAP_FCTID_FCTLIST == ((fctId_t)Bap_oPars.fctId))
        {
            uint8_t u8CurrentFctId;

            /* Neue Fct.list muss auf alle Faelle Fct.ID 2+3 beinhalten */
            /* SSWPPB[93] added missing Nullpointer check, added invalid Length check for fctList */
            if ( (NULL == apData) || (BAP_FCTID_FCTLIST_SIZE != au32Length) || (apData[0] & BAP_FCTID_BAPCONFIG_FCTLIST_BITMAP) != BAP_FCTID_BAPCONFIG_FCTLIST_BITMAP )
            {
                eResult = BapErr_IncompatibleDataSpecification;
            }else{
                /* Eine neue Fct.list darf ein Superset der initalen im ROM gespeicherten sein */
                /* Man kann dann bereits mit einem Subset anfangen! Allerdings muessen fuer das Superset */
                /* entsprechende XML Eintraege vorgenommen worden sein, welche RomRows generiert haben */
                for(u8CurrentFctId = BAP_BINARY_ID(BAP_FCTID_FCTLIST); u8CurrentFctId <= (uint8_t)BAP_MAX_FCT_ID; u8CurrentFctId++)
                {
                    /* SSWPPB[93] Nullpointer check is implemented in first if condition   */
                    /* Bit gesetzt in neuer Fct.list, aber existiert auch eine RomRow dafuer? */
                	/* MISRA_2012_REQ_12.1 : Add paranthesis to be compliant. "((uint8_t)0x80 >> (u8CurrentFctId % (uint8_t)8))))"*/
                    if ( ((uint8_t)0 != (apData[u8CurrentFctId / BAP_BYTE] & (BAP_BIT7 >> (u8CurrentFctId % BAP_BYTE)))) )
                    {
                        /*lint -esym( 960, 33 ) Funktion hat keinen Seiteneffekt */
                        /*lint -e9034*/
                        /*lint -e9034*/ /* MISRA_2012_REQ_10.3 : PC-Lint 9.00L throws a warning due to Tool bug. Hence, this warning has been deactivated.
                                         * Documented with a mail from the Lint team in the SSWCCB-2522_BAP-Entwicklung auf MISRA2012 umstellen folder */
                    					/* MISRA_2012_REQ_10.5 : no risk arise  with the cast because
                    					 * u8CurrentFctId contains a function id and fit in enum.*/
                        if (NULL == BAP_GetLsgFctRomRow(Bap_oPars.poLsgRomRow, ((const fctId_t)u8CurrentFctId)))
                        /*lint +e9034*/
                        /*lint +esym( 960, 33 ) */
                        {
                            eResult = BapErr_IncompatibleDataSpecification;
                        }
                    }
                }
            }

            /* FunctionList uebernehmen */
            /* SSWPPB[93] Nullpointer check is included within Variable eResult */
            if(eResult == BapErr_OK)
            {
                /*lint -e668*/
                /* MISRA_2004 : (void*)apData != NULL */
                /*lint -e9087*/ /* MISRA_2012_REQ_11.3 : 1st and 2nd arguments of MEMCPY are of types (uint8_t*).
                                 * They are implicitly cast to (void*). The memory is packed because it is uint8_t so there should be no problem to copy.*/
                MEMCPY(Bap_oPars.poLsgRomRow->poLsgRamRow->BAP_aru8FunctionList, apData
                       , BAP_FCTID_FCTLIST_SIZE);
                /*lint +e668 +e9087*/
            }
        }else if( (fctId_t)BAP_FCTID_BAPCONFIG == (fctId_t)Bap_oPars.fctId)
        	/* MISRA_2012_REQ_10.5 : no risk arise  with the cast because BAP_FCTID_BAPCONFIG fit in enum.*/
        {
            /* Ueberpruefe bekommene Config und setze sie als aktiv, falls eine passende gefunden */
        	/*lint -e9007*/ /* MISRA_2012_REQ_13.5 : Note 9007 deactivated, no side effects - manually verified */
            if( (NULL == apData) || (BAP_FCTID_BAPCONFIG_SIZE != au32Length) || (BAP_FALSE != BAP_BAL_CheckBapConfig(&Bap_oPars, Bap_oPars.pData)) )
            /*lint +e9007*/
            {
                /* keine passende Config gefunden */
                eResult = BapErr_InvalidArg;
            }else{
                /* Das FSG kopiert die default ROM Cfg.list in den RAM Buffer */
                /*lint -e668*/
                /* MISRA_2004 : (void*)apData != NULL */
                /*lint -e9087*/ /* MISRA_2012_REQ_11.3 : 1st and 2nd arguments of MEMCPY are of types (uint8_t*).
                                 * They are implicitly cast to (void*). The memory is packed because it is uint8_t so there should be no problem to copy.*/
                MEMCPY(Bap_oPars.poLsgRomRow->poLsgRamRow->BapBAPConfig_t, apData, BAP_FCTID_BAPCONFIG_SIZE);
                /*lint +e668 +e9087*/

                /* SSWCCB-1028: RAM-Wert fuer FctList aktualisieren. */
                Bap_oPars_fctlist.lsgId = aLsgId;
                Bap_oPars_fctlist.poLsgRomRow = BAP_GetLsgRomRow(aLsgId);
                /*lint -e9034*/ /*MISRA_2012_REQ_10.3 : Warning deactivated. Refers to bap_types.h, definition of BAP_FCTID_FCTLIST*/
                /* MISRA_2012_REQ_10.5 : no risk arise because BAP_FCTID_FCTLIST fit in enum and is already cast at declaration.*/
                Bap_oPars_fctlist.fctId = BAP_FCTID_FCTLIST;
                /*lint +e9034 */
                Bap_oPars_fctlist.u32Length = BAP_FCTID_FCTLIST_SIZE;
                /*lint -e9034*/ /*MISRA_2012_REQ_10.3 : Warning deactivated. Refers to bap_types.h, definition of BAP_FCTID_FCTLIST*/
                /* MISRA_2012_REQ_10.5 : no risk arise because BAP_FCTID_FCTLIST fit in enum and is already cast at declaration.*/
                Bap_oPars_fctlist.poFctRomRow = BAP_GetLsgFctRomRow(poLsgRomRow,BAP_FCTID_FCTLIST);
                /*lint +e9034 */
                /*lint -e9087*/ /* MISRA_2012_REQ_11.3 : 1st and 2nd arguments of MEMCPY are of types (uint8_t*).
                                 * They are implicitly cast to (void*). The memory is packed because it is uint8_t so there should be no problem to copy.*/
                MEMCPY(Bap_oPars_fctlist.poLsgRomRow->poLsgRamRow->BAP_aru8FunctionList
                    , BAP_GetLsgRomRow(aLsgId)->BAP_aru8FunctionList
                    , BAP_FCTID_FCTLIST_SIZE);
                /*lint +e9087 */
                Bap_oPars_fctlist.pData = Bap_oPars_fctlist.poLsgRomRow->poLsgRamRow->BAP_aru8FunctionList;
                BAP_BPL_BufferSet(&Bap_oPars_fctlist);   /* Schreibt neue Bufferwert fuer FctList */
            }
        }else{
            /* for lint */
        }
    }

    /* Wenn alles geklappt hat den Puffer setzen */
    /* Schreibt den Wert runter in den BCL - der OpCode ist hier nur ein Dummy-Wert */
    if(eResult == BapErr_OK)
    {
        BAP_BPL_BufferSet(&Bap_oPars);
    }
    return eResult;
    /*lint +esym(644,Bap_oPars)*/
    /*lint +esym(644,poLsgRomRow)*/
    /*lint +esym(613,apData) */
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* #if defined(BAP_FSG)  && defined (BAP_USES_DATATYPE_BS) */



/*
 *  Diese Funktion ist in bap.h dokumentiert
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_IMPL_FAR BapError_et
BAP_Init(lsgId_t aLsgId)
{
    /* Zum Zwischenspeichern des Funktionsergebnisses */
    DBGVAR BapError_et eResult;

    /*  Wenn Compiler meldet: Bedingung immer falsch,
        dann darf das Makro im Makefile definiert werden */
#ifndef BAP_DISABLE_TYPE_CHECKING

    /* Teste, ob die Compilereinstellungen und die
       Konfiguration aufeinander passen, d.h. die
       Standardtypen die richtige Groesse haben.
       Diese Zeilen werden typischerweise, falls
       die Typen stimmen, vom Compiler wegoptimiert */
    if( (sizeof(uint8_t)  != BAP_BIT8_BYTES) || (sizeof(uint16_t) != BAP_BIT16_BYTES) || (sizeof(uint32_t) != BAP_BIT32_BYTES) )   /*lint !e912 !e506 !e774 !e845*/
    /* MISRA_2012_REQ_14.3 : The controlling expression shall not be invariant.
     * MISRA_2012_REQ_2.1 : A project should not contain unreachable code. See the following explanation.
     * deac. 912:  Implicit binary conversion from Type to Type. No risk because the value is only used for this check.
     * deac. 506: Constant value Boolean. Indeed, the goal is to check the configuration.
	 * No risk of keeping constant value since it should never be different. except in case of configuration issue.
	 * deac. 774:  Boolean within 'String' always evaluates to [True/False]. See deac. 506.
	 * deac. 845: The [left/right] argument to operator 'Name' is certain to be 0.
	 * Indeed, that's the goal. except in case of configuration issue. So no risk arise here.
     */
    /* muss immer FALSE sein, code is reacheable only in case configuration issue */
    {
        eResult = BapErr_InvalidArg;    /* DBG wird mit || (eResult != BapErr_OK) gesetzt */
    }
    else
#endif /* #ifndef BAP_DISABLE_TYPE_CHECKING */
    {
        eResult = BAP_BAL_Init(BAP_FALSE, aLsgId);
    }
    return eResult;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


/*
 *  Diese Funktion ist in bap.h dokumentiert
 *
 *  Diese Funktion hat 11 OutgoingCalls (max.7), 7 ControlNestingLayers (max.4), 58 Statements (max.50)
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_IMPL_FAR BapError_et
BAP_Start(lsgId_t aLsgId)
{
    DBGVAR BapError_et eResult;
    DBGVAR BapLayerLsgStatus_et eNewLayerStatus = BapLayerLsgStat_Initialized;
#ifdef BAP_ROM_DATA_FAR_EMPTY
    /* Werte koennen direkt aus dem ROM kopiert werden */
#else
    /* Temporaerer Speicher, da Werte aus dem ROM nicht direkt versendet werden koennen */
    DBGVAR uint8_t aru8NearRamForBAPConfig[BAP_FCTID_BAPCONFIG_SIZE];
#endif

    BAP_InitInternalParameters(&Bap_oPars);
    Bap_oPars.lsgId = aLsgId;
    Bap_oPars.poLsgRomRow = BAP_GetLsgRomRow(Bap_oPars.lsgId);

    if(NULL == Bap_oPars.poLsgRomRow)
    {
        BAP_DBG_InvalidArgError(Bap_oPars.lsgId);
        eResult = BapErr_InvalidArg;
    }
    else
    {
        /* Ueberpruefe Zustandsmaschine */
        if (BapLayerLsgStat_Initialized != Bap_oPars.poLsgRomRow->poLsgRamRow->eLsgStatus)
        {
            BAP_DBG_InvalidStateError(Bap_oPars.lsgId);
            eResult = BapErr_InvalidState;
        }
        else
        {
#ifdef BAP_FSG  /* Fuer reine ASG Variante nicht noetig, da immer BapErr_OK */
            /* Die darunterliegende Schicht initialisieren */
            eResult = BAP_BPL_Start(Bap_oPars.poLsgRomRow);
            if(eResult == BapErr_OK)
#endif
            {
                /*lint -e9034*/ /*MISRA_2012_REQ_10.3 : Warning deactivated. Refers to bap_types.h, definition of BAP_FCTID_BAPCONFIG*/
                Bap_oPars.fctId = BAP_FCTID_BAPCONFIG;
                /*lint +e9034 */
                Bap_oPars.poFctRomRow = BAP_GetLsgFctRomRow(Bap_oPars.poLsgRomRow, Bap_oPars.fctId);

#ifdef BAP_ASG
#if defined(BAP_ASG) && defined(BAP_FSG)
                if (BapSG_ASG == Bap_oPars.poLsgRomRow->eSGType)
#endif /* defined(BAP_ASG) && defined(BAP_FSG) */
                {
                    /* Beim Start des ASG die BAPConfig vom FSG abfragen */
                    Bap_oPars.eOpCode = BapOp_PropGet;
                    /* Loeschen der Gesamtcachegueltigkeit */
                    Bap_oPars.poLsgRomRow->poLsgRamRow->fState.fCacheValid = BAP_FALSE;
                    BAP_DBG_SetCacheValidState(aLsgId, BAP_FALSE);
                    eNewLayerStatus = BapLayerLsgStat_WaitForOrInvalidConfig;
                }
#endif /* #ifdef BAP_ASG */

#ifdef BAP_FSG
#if defined(BAP_ASG) && defined(BAP_FSG)
                else
#endif /* defined(BAP_ASG) && defined(BAP_FSG) */
                {
                    /* Beim Start des FSG dem ASG die BAPConfig mit Reset schicken */
                    Bap_oPars.eOpCode = BapOp_PropReset_Set;
#ifdef BAP_ROM_DATA_FAR_EMPTY
                    /* Nimm den Wert direkt aus dem RAM */
                    Bap_oPars.pData = Bap_oPars.poLsgRomRow->poLsgRamRow->BapBAPConfig_t;
#else
                    /* Kopiere den Wert vorher aus dem BAP_ROM_DATA_FAR ROM ins RAM */
                    Bap_oPars.pData = Bap_oPars.poLsgRomRow->poLsgRamRow->BapBAPConfig_t;
                    FAR_MEMCPY(aru8NearRamForBAPConfig, Bap_oPars.poLsgRomRow->poLsgRamRow->BapBAPConfig_t, BAP_FCTID_BAPCONFIG_SIZE);
#endif /* BAP_ROM_DATA_FAR_EMPTY */
                    Bap_oPars.u32Length = BAP_FCTID_BAPCONFIG_SIZE;
                    eNewLayerStatus = BapLayerLsgStat_Running;
                }
#endif /* #ifdef BAP_FSG */
                /* Sende den erforderlichen Request aus */
                eResult = BAP_BPL_Send(&Bap_oPars);

                if(eResult != BapErr_OK)
                {
                    BAP_BPL_Shutdown(Bap_oPars.poLsgRomRow);
                    /* Falls irgendwas in den unteren Schichten fehlschlaegt immer InvalidArg */
                    BAP_DBG_InvalidArgError(Bap_oPars.lsgId);
                    eResult = BapErr_InvalidArg;
                }
                else
                {
                    (Bap_oPars.poLsgRomRow->poLsgRamRow->eLsgStatus) = eNewLayerStatus;
                    BAP_DBG_SetBalState(Bap_oPars.lsgId, eNewLayerStatus);

                    /* Beim 1.Start eines LSGs(ASG und FSG) wird die Versionsinfo ueber die erste
                    TX-CAN-ID mit LSG-ID = 0, FctID = 0 und OpCode Status auf den CAN-Bus ausgegeben.
                    Die erfolgte Ausgabe wird mittels eines Flags gespeichert. Das Flag wird bei jedem
                    BAP_Shutdown wieder zurueckgesetzt, so dass ein weiterer BAP_Start zur erneuten
                    Ausgabe der Versionsinfo fuehrt.*/
                    if(BAP_bVersionInfo == BAP_FALSE)
                    {
                        /* apData fuer unsegmentierte Botschaft:
                                     Byte0         Byte1       Byte2        Byte3
                                OpCode   LSG-ID    FCT-ID    VersionMajor VersionMinor
                               0  100   0000 | 00  000000 |              | */
                        Bap_aru8VersionInfo[0] = (uint8_t)BAP_OPCODE_STATUS_LSGID_ZERO;  /* Byte0*/
                        Bap_aru8VersionInfo[1] = (uint8_t)BAP_LSGID_ZERO_FCTID_ZERO;   /* Byte1*/
#ifdef DLL_COMPILATION
                        Bap_aru8VersionInfo[2] = gXMLVersionMajor;   // Byte2
                        Bap_aru8VersionInfo[3] = gXMLVersionMinor;   // Byte3
#else
                        Bap_aru8VersionInfo[2] = (uint8_t)BAP_XML_VERSION_MAJOR;   /* Byte2*/
                        Bap_aru8VersionInfo[3] = (uint8_t)BAP_XML_VERSION_MINOR;   /* Byte3*/
#endif /* #ifdef DLL_COMPILATION */
                        /* MISRA_2012_REQ_14.3 : The controlling expression is not invariant,
                         * but always true except if no valid interface channel is found */
                        if(BAP_FALSE != BAP_CANUBS_TxData(BAP_InhibitRomTable[0].canInterfaceChannel, BAP_InhibitRomTable[0].canMsgId, Bap_aru8VersionInfo, (uint8_t)BAP_BIT32_BYTES))
                        {
                            BAP_bVersionInfo = BAP_TRUE;
                        }
                    }
                }
            }
        }
    }
    return eResult;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


/*
 *  Diese Funktion ist in bap.h dokumentiert
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_IMPL_FAR BapError_et
BAP_Shutdown(lsgId_t aLsgId)
{
    DBGVAR BapError_et eResult;
    eResult = BAP_BAL_Init(BAP_TRUE, aLsgId);

    if(eResult == BapErr_OK)
    {
        BAP_bVersionInfo = BAP_FALSE;
    }
    return eResult;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


/*
 *  Diese Funktion ist in bap.h dokumentiert
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_IMPL_FAR bool_t
BAP_GetLsgState(lsgId_t aLsgId)
{
    DBGVAR BapLsgRomRow_pot poLsgRomRow = BAP_GetLsgRomRow(aLsgId);
    DBGVAR bool_t bRetVal = BAP_FALSE;
    if(NULL == poLsgRomRow)
    {
        BAP_DBG_InvalidArgError(aLsgId);
        bRetVal = BAP_FALSE;
    }
    else
    {
        if(BapLayerLsgStat_Running == poLsgRomRow->poLsgRamRow->eLsgStatus )
        {
            bRetVal = BAP_TRUE;
        }
        else
        {
            bRetVal = BAP_FALSE;
        }
    }
    return bRetVal;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>

/* CallBack-Funktionen */

/*
 *  Wird vom BPL als Callback aufgerufen. Dokumentiert in bap_bpl.h
 *
 *  Diese Funktion hat 12 OutgoingCalls (max.7)
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_BPL_DataReceived(BapInternalParameters_cpot apoPars)
{
    /*lint -esym(613,apoPars)*/
    DBGVAR volatile_ptr_t pConvertedData = apoPars->pData;
    DBGVAR BapDataType_et eDataType = BapDt_None;
#if defined (BAP_ASG)
    DBGVAR BapLayerLsgStatus_et eOldLayerStatus = BapLayerLsgStat_NoInit;

    if (( NULL != apoPars->poLsgRomRow)
            && (NULL != apoPars->poLsgRomRow->poLsgRamRow))
    {
        eOldLayerStatus = apoPars->poLsgRomRow->poLsgRamRow->eLsgStatus;
    }
#endif

    if(BapErr_OK != BAP_BAL_CheckDataReceived(apoPars))
    {
        BAP_DBG_InvalidArgError(apoPars->lsgId);
    }
    else
    {
        /* Hole Indication Typ */
        /*
         * Ticket SSWPPB-112.
         * Trigger BapConfig Indication when LSG state switch from BapLayerLsgStat_WaitForOrInvalidConfig to BapLayerLsgStat_Running
         * within receiving the BapConfig through HeartBeath messages
         */
#if defined(BAP_ASG) && defined(BAP_FSG)
        if ((NULL != apoPars->poLsgRomRow)
                && (BapSG_ASG == apoPars->poLsgRomRow->eSGType)
                && (BapLayerLsgStat_WaitForOrInvalidConfig == eOldLayerStatus)
                && (BapLayerLsgStat_Running == apoPars->poLsgRomRow->poLsgRamRow->eLsgStatus)
                && (BapOp_PropHeartbeatStatus == apoPars->eOpCode )
                && ((uint8_t)BAP_FCTID_BAPCONFIG == (uint8_t)apoPars->fctId )
        )
        {
            Bap_eIndication = BapInd_Data;
        }
        else
        {
            Bap_eIndication = BAP_OpCode2IndicationMatrix[apoPars->poLsgRomRow->eSGType][apoPars->poFctRomRow->eFunctionClass][apoPars->eOpCode];
        }
#else
        /*
         * Ticket SSWPPB-112.
         * Trigger BapConfig Indication when LSG state switch from BapLayerLsgStat_WaitForOrInvalidConfig to BapLayerLsgStat_Running
         * within receiving the BapConfig through HeartBeath messages
         */
#if defined (BAP_ASG)
        if ((NULL != apoPars->poLsgRomRow)
                && (BapLayerLsgStat_WaitForOrInvalidConfig == eOldLayerStatus)
                && (BapLayerLsgStat_Running == apoPars->poLsgRomRow->poLsgRamRow->eLsgStatus)
                && (BapOp_PropHeartbeatStatus == apoPars->eOpCode )
                && ((uint8_t)BAP_FCTID_BAPCONFIG == (uint8_t)apoPars->fctId )
        )
        {
            Bap_eIndication = BapInd_Data;
        }
        else
        {
            Bap_eIndication =
                    BAP_OpCode2IndicationMatrix[apoPars->poFctRomRow->eFunctionClass][apoPars->eOpCode];
        }
#else /* implementation for configurations with only FSG in their configurations */
        Bap_eIndication =
                BAP_OpCode2IndicationMatrix[apoPars->poFctRomRow->eFunctionClass][apoPars->eOpCode];
#endif /* defined (BAP_ASG) */

#endif /* defined(BAP_ASG) && defined(BAP_FSG) */

        /* DataType je nach LSG-Typ und Indication aufbereiten */
#if defined(BAP_ASG) && defined(BAP_FSG) /* Im Kombigeraet muss die Abfrage ob es ein ASG ist, drin sein */
        if (BapSG_ASG == apoPars->poLsgRomRow->eSGType)
#endif /* defined(BAP_ASG) && defined(BAP_FSG) */

#ifdef BAP_ASG /* Behandlung muss in ASG durchgefuehrt werden */
        {
            eDataType = BAP_BAL_AsgDataReceived(pConvertedData, apoPars, &Bap_eIndication);
        }
#endif /* BAP_ASG */

#if defined(BAP_ASG) && defined(BAP_FSG) /* Im Kombigeraet muss die Abfrage ob es ein FSG ist, drin sein */
        else
#endif /* defined(BAP_ASG) && defined(BAP_FSG) */

#ifdef BAP_FSG
        {
            eDataType = BAP_BAL_FsgDataReceived(apoPars, Bap_eIndication);
        }
#endif /* BAP_FSG */

        /* Ist bei der Auswertung von FSG bzw. ASG ein Spezialfall aufgetreten der nicht nach oben */
        /* gemeldet werden darf ist der eDataType auf BapDt_None gesetzt und keine Indication wird ausgeloest*/

        /* In Abhaengigkeit der Datentypen die entsprechende Indication aufrufen */
        /* gilt auch fuer Array mit Changed! */
        switch (eDataType) {
        case BapDt_Int8:
            /*lint -esym(613,pConvertedData)*//* Von unterliegenden Schichten initialisiert */
            BAP_IndicationInt8(apoPars->lsgId
                    , apoPars->fctId
                    , Bap_eIndication
                    , (uint8_t)(*pConvertedData));
            BAP_DBG_IncomingMessageEvent(apoPars->lsgId, apoPars->fctId, apoPars->eOpCode);
            /*lint +esym(613,pConvertedData)*/
            break;
#ifdef BAP_USES_DATATYPE_16
        case BapDt_Int16:
            BAP_IndicationInt16(apoPars->lsgId
                    , apoPars->fctId
                    , Bap_eIndication
                    , BAP_BAL_DataStreamToInt16(pConvertedData));
            BAP_DBG_IncomingMessageEvent(apoPars->lsgId, apoPars->fctId, apoPars->eOpCode);
            break;
#endif  /* BAP_USES_DATATYPE_16 */
#ifdef BAP_USES_DATATYPE_32
        case BapDt_Int32:
            BAP_IndicationInt32(apoPars->lsgId
                    , apoPars->fctId, Bap_eIndication
                    , BAP_BAL_DataStreamToInt32(pConvertedData));
            BAP_DBG_IncomingMessageEvent(apoPars->lsgId, apoPars->fctId, apoPars->eOpCode);
            break;
#endif  /* BAP_USES_DATATYPE_32 */
        case BapDt_FixedByteSequence:
#ifdef BAP_USES_SEGMENTATION
        case BapDt_ByteSequence:
#endif /* BAP_USES_SEGMENTATION */
            BAP_IndicationByteSequence(apoPars->lsgId, apoPars->fctId, Bap_eIndication, pConvertedData, apoPars->u32Length);
            BAP_DBG_IncomingMessageEvent(apoPars->lsgId, apoPars->fctId, apoPars->eOpCode);
            break;
        case BapDt_Void:
            BAP_IndicationVoid(apoPars->lsgId, apoPars->fctId, Bap_eIndication);
            BAP_DBG_IncomingMessageEvent(apoPars->lsgId
                    , apoPars->fctId
                    , apoPars->eOpCode);
            break;
        case BapDt_None: /* nichts zu tun! */
        default:
            /* No Statements */
            break;
        }
    }
    /*lint +esym(613,apoPars)*/
    return;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>

/*
 *  Wird vom BPL als Callback aufgerufen. Dokumentiert in bap_bpl.h
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_BPL_ErrorIndication(DBGVAR lsgId_t aLsgId
    , DBGVAR fctId_t aFctId
    , DBGVAR BapError_et aeErrorCode)
{
#ifdef BAP_ASG
    DBGVAR bool_t giveNoIndication = BAP_FALSE;

    BapLsgRomRow_pot poLsgRomRow;
    BapLsgRamRow_cpot poLsgRamRow;

    poLsgRomRow = BAP_GetLsgRomRow(aLsgId);
    if ((NULL != poLsgRomRow)
#if defined(BAP_ASG) && defined(BAP_FSG)
        && (BapSG_ASG == poLsgRomRow->eSGType)
#endif /* defined(BAP_ASG) && defined(BAP_FSG) */
       )
    {
        /* Falls lsg=0 oder fct=0 Indication nach oben melden == allgemeiner Fehler */
        if ( ((lsgId_t)0 != (lsgId_t)aLsgId) && ((fctId_t)0 != (fctId_t)aFctId) )
        {
            poLsgRamRow = poLsgRomRow->poLsgRamRow;
            if (NULL != poLsgRamRow )
            {
                /*lint -esym( 960, 33 ) Funktion hat keinen Seiteneffekt */
                if( ( BAP_FALSE == BAP_BAL_CheckIfFunctionIsValid(aFctId, poLsgRamRow->BAP_aru8FunctionList))
                        && (BapLayerLsgStat_Initialized != poLsgRamRow->eLsgStatus) )
                /*lint +esym( 960, 33 ) */
                {
                    /* Fct. ist nicht in aktueller Fct.list und wird demzufolge purged */
                    BAP_DBG_RxDataPurgedEvent();
                    /* Wenn nicht in Fct.list keine Indication melden */
                    giveNoIndication = BAP_TRUE;
                }
            }
        }
        /* Sonderbehandlung fuer Retry-Ueberwachung bei GetAll */
        if((BAP_FCTID_GETALL == (fctId_t)aFctId)    && (BapErr_RetryNotSuccessful == aeErrorCode))
        {
            /*lint -esym( 960, 33 ) Funktion hat keinen Seiteneffekt */
            if(BapBalDataStat_Valid == BAP_BAL_GetLsgCacheStatus(poLsgRomRow))
                /*lint +esym( 960, 33 ) */
            {
                /* StatusAll wurde schon gemeldet, also Error ignorieren */
                giveNoIndication = BAP_TRUE;
            }
        }
        /* Sonderbehandlung fuer Heartbeat-Ueberwachung */
        if(BapErr_TimeoutHeartbeat == aeErrorCode)
        {
            /* LSG lebt nicht mehr => Cache auf invalid setzten */
            BAP_BAL_InvalidateCache(poLsgRomRow);
        }
    }

    if(BAP_FALSE == giveNoIndication)
#endif /* BAP_ASG */
    {
        BAP_IndicationError(aLsgId, aFctId, aeErrorCode);
    }

    return;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>

#ifdef BAP_USES_ACKNOWLEDGE
/**
 *  Diese Funktion wird vom BPL aufgerufen, wenn eine Nachricht erfolgreich verschickt wurde.
 *
 *  @param apoFctRomRow zeigt auf die Funktion
 *  @param aeOpCode enthaelt den gesendeten OpCode
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_BPL_Acknowledge(BapFctRomRow_pot apoFctRomRow, BapOpCodes_et aeOpCode)
{
    BapAcknowledge_et eAcknowledge;

    /*lint -esym(613, apoFctRomRow) */
    BAP_ASSERT(NULL != apoFctRomRow);

    eAcknowledge = BAP_BAL_GetAcknowledge(apoFctRomRow, aeOpCode);

    if (BapAck_Nothing != eAcknowledge)
    {
#ifdef BAP_ASG
        /* Die Abfrage stoert im Kombigeraet bei FSGs nicht */
        BapLsgRomRow_pot poLsgRomRow = BAP_GetLsgRomRow(apoFctRomRow->lsgId);
        if ( (NULL != poLsgRomRow)
                && (BapLayerLsgStat_Running == poLsgRomRow->poLsgRamRow->eLsgStatus))
#endif /* #ifdef BAP_ASG */
        {
            BAP_Acknowledge(apoFctRomRow->lsgId, apoFctRomRow->fctId, eAcknowledge);
        }
    }
    /*lint +esym(613, apoFctRomRow) */
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif  /* #ifdef BAP_USES_ACKNOWLEDGE */
