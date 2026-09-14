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
 *  Diese Datei enthaelt die CAN Anbindung der BCL Schicht im BAP
 *  Projekt.
 *
 ******************************************************************
 *
 * Versionsgeschichte (ohne SCM)
 *
 * Datum        Version     Autor       Beschreibung
 * ----------------------------------------------------------------
 * 2023-10-10	1.12.2		DRH			[EEARCH-35935] Release preparation, adapt Copyright date and version number.
 * 2023-03-14   1.12.1      DRH         [EEARCH-27488] Add conditional external linkage for static global variables on DLL compilation.
 * 2022-11-15   1.12.1      DRH         [SSWPPB-297] Renamed macros and global variables module specific
 * 2022-10-21	1.12.1		DRH			[SSWPPB-296] Release preparation, adapt Copyright date and version number.
 * 2022-07-26   1.12.0      DRH         [SSWPPB-292] Improve Rx-Ringbuffer padding calculation and BclTxRamRow initialization
 * 2022-06-17	1.12.0		DRH			[SSWPPB-269] Release preparation, adapt Copyright date and version number.
 * 2022-02-15   1.11.3      DRH         [SSWPPB-246] Implementierung der dynamischen Rx-Ringbuffer Verwaltung
 * 2021-12-10	1.11.3		JEO			[SSWPPB-244] Release preparation, fix MISRA violations.
 * 2021-12-07	1.11.3		JEO			[SSWPPB-244] Release preparation, adapt Copyright date and version number.
 * 2021-11-23   1.11.3      DRH         [SSWPPB-216] Improve DLL generation.
 * 2021-03-08   1.11.3      DRH         [SSWPPB-142] Replaced magic numbers by constants
 * 2021-03-01	1.11.3		JEO			[SSWPPB-142] Improve jutification of Pc-Lint deac or MISRA rules violation + fix MISRA Rule 13.4 violation in "BAP_BCL_CanReceiveData" function
 * 2020-10-26   1.11.2      NAG         [SSWPPB-56] Check Group Basic Software Requirements (KGAS)
 * 2020-09-30   1.11.2      KUL         [SSWPPB-70] Use of BAP_USES_ETH to support POSIX based ECUs with Ethernet
 * 2020-07-01   1.11.2      NAG         [SSWPPB-117] Segmented start message with extended data length format dropped
 * 2020-03-31   1.11.1      ODD         [SSWPPB-93] add typecast to global variable initialisation oBclTxRamRow to reomve compiler error when 
 *                                      compiling under Autosar when using strict compiler settings which not allow implicit typecast
 * 2019-03-21   1.10.99     KUL         [SSWPPB-4] Removal of string.h inclusion
 * 2018-07-19   1.10.3      FFS         [SSWCCB-2522] Misra-2012 fix
 * 2018-01-08   1.10.0      FHA         [SSWCCB-2554] Unerwuenschte TimeoutSegmentation bei großen Datenpaketen
 * 2017-11-09   1.10.0      FHA         [SSWCCB-2555] Rollback der Padding-Funktion
 * 2017-07-24   1.10.0      FHA         [SSWCCB-2391] Schnelle Suche TX-PDU
 * 2017-03-22   1.9.0.1     FST         [SSWCCB-1545] SSW-Lokatierungs-Pragmas eingefuegt
 * 2016-10-13   1.8.1       FST         [SSWCCB-2410] Softwareschalter DLL_COMPILATION zur Unterscheidung
 *                                      der Erzeugung von Steuergeraete-Code und der BAP-Dll eingefuegt
 * 2015-03-17   1.8.0.3     FST         [SSWCCB-2188][SSWCCB-2189][SSWCCB-2190] BAP_BCL_GetRxPduSize zu BAP_GetRxPduSize und
 *                                      BAP_BCL_GetTxPduSize zu BAP_GetTxPduSize umbenannt wegen Umzug von bap_bclutil zu bap_util
 * 2015-02-09   1.8.0.2     FST         Verringerung der zyklomatischen Komplexitaet, Aufspaltung zweier Funktionen, Misra-Korrekturen
 * 2015-02-09   1.8.0.2     WWU         [SSWCCB-2151] Polyspacemeldung gefixed.
 * 2014-01-23   1.8.0.2     WWU         [SSWCCB-2105] variable PDU-Groesse: Padding fuer segmentierte Nachricht.
 * 2014-01-16   1.8.0.1     WWU         [SSWCCB-2105] variable PDU-Groesse und neues Format fuer segmentierte Nachricht.
 * 2014-11-28   1.8.0.0     WWU/FST     [SSWCCB-2105] variable PDU-Groesse: Formataenderung der Variablen 16Bit->32Bit
 * 2014-10-06   1.8.0       FST         Umstellung u8Length auf uint16_t u16MsgLength fuer Nachrichtengroesse > 8 Byte
 * 2014-07-16   1.8.0       WWU         Makro BAP_USES_PDU fuer PDU-Router erweitert.
 * 2014-07-01   1.7.2       WWU         CR Verlaengerte Inhibitzeit nach eine segmentierte Nachricht.
 * 2014-03-21   1.7.1       WWU         CCB-664 und CCB-1731: Alignment problem.
 * 2013-02-06   1.7.0       WWU         Funktionsname umbenannt, wegen Misra : Identifier exceeds 31 characters
 * 2013-01-16   1.7         GRO         Bei BAP-Nachrichten mit LsgId-Erweiterung wird die LsgId auf Null gesetzt.
 * 2012-10-15   1.6.5.1     WWU         Korrektur der Misra-98 Abweichungen
 * 2012-09-18   1.6.5       WWU         Code Complexity Reduzieren: Die Kombi-Ueberpruefung in der Funktion BAP_CAN_RxSegmentedStart
 *                                      entfernt.
 * 2011-08-25   1.6.2       WWU         Unterstuetzung fuer FSG mit unsegmentierter Functionlist
 * 2010-12-16   1.5.1       ALI         Bugfix BAP_BCL_CanProcessData Zuweisung des poCanRxRomRow verschoben 
 * 2010-08-12   1.5.1       HEW         Bugfix bei mehreren DF
 * 2007-11-07   1.5         RVE         Heuristik ueberarbeitet und optimiert
 * 2007-10-01   1.5         ALI         BAP_BCL_InitCanDrvTxConfirmationFlags optimiert
 * 2007-08-24   1.5         ALI         Heuristik beim Senden geaendert: Pro CanId ein Zeiger beim
 *                                      Abarbeiten der TX-Nachrichten, statt einem Zeiger fuer alle
 * 2007-09-24   1.4.1.1     RVE         Aenderung an der Initialisierung der ConfirmationFlags gemaess den Anforderungen von VW
 * 2006-11-20   1.4.1       ALA         Optimierung Laufzeit BAP_BCL_InitCanDrvTxConfirmationFlags
 *                                      Optimierung Verarbeitungszeit von Reset-Nachrichten
 * 2006-06-02   1.4         ALA         Unterstuetzung von Bap_Acknowledge
 * 2006-06-01   1.4         ALA         Optimierung Speicherplatzbedarf
 * 2006-06-01   1.4         ALA         Aufsplittung BAP_BCL_CanReceiveData in zwei Funktionen
 * 2006-04-12   1.4         ALA         Unterstuetzung fuer BAP_ROM_DATA_FAR.
 * 2006-04-12   1.4         ALA         Optimierungen fuer Task-Laufzeit.
 * 2006-04-12   1.4         ALA         Unterstuetzung fuer neue HB-Trigger.
 * 2006-04-12   1.4         ALA         Unterstuetzung fuer kompatible Erweiterung.
 * 2005-07-18   1.3.1       ALA         Bugfix: Bei ungueltiger BAPConfig werden keine Remotefehler mehr
 *                                      angenommen.
 * 2005-04-29   1.3         ALA         Verbesserte Parameteruebergabe, Reduzierung Stackbedarf, Optimierungen,
 *                                      Unterstuetzung von fixem und variablem DLC, einstellbar je LSG
 * 2005-04-21   1.3         ALA         Unterstuetzung von Fuellbotschaften, Robustheit gegenueber falschem DLC,
 *                                      Bugfix: Empfang von Fehlern nun moeglich fuer ByteSequence der Laenge 0.
 * 2005-04-15   1.3         ALA         Reduzierung der CPU-Last bei Busruhe
 * 2005-04-13   1.3         ALA         Reduzierung der CPU-Last bei Multi Konfigurationen im ASG
 * 2005-04-05   1.3         ALA         Verbesserte Heuristik, Ringpuffer zur Reduzierung der Interruptsperrzeiten,
 *                                      dynamische Kanalvergabe bei Segmentierung
 * 2005-03-14   1.2.1       CRI         Compilerwarning fuer gcc mit Konstruktion umgangen
 * 2004-11-08   1.2         ALA         Eigene Puffer fuer Errorcodes. Durch Opcodepuffer den
 *                                      Puffer fuer den BAP-Header eingespart => unveraenderter RAM-Bedarf.
 * 2004-10-26   1.2         ALA         Unterstuetzung von GetAll/StatusAll a Block und mit
 *                                      Einzelantworten auf BCL CAN Ebene.
 *                                      Komplette Verarbeitung von empfangenen Nachrichten refakturiert
 * 2004-09-09   1.2         ALA         Message-Objekte werden nun ueber CanGetTxDataPtr bzw.
 *                                      CanGetRxDataPtr ermittelt und fehlen in Konfiguration.
 *                                      UBS Unterstuetzung
 * 2004-09-17   1.1.1       ALA         Code zum Inkrementieren von 4 Bit Sequenzzaehler
 *                                      an CVI 6.0 Compiler angepasst
 * 2004-06-07   1.1         JOK         Compilerschalter fuer SG-Typen zur Optimierung
 *                                      des ROM-Bedarfs eingefuegt
 * 2004-06-07   1.1         JOK         Include stdlib.h eingefuegt
 * 2004-06-07   1.1         JOK         Makro fuer memcpy() mit entsprechenden
 *                                      Casts entsprechend MISRA-C Pruefung definiert
 * 2004-06-07   1.1         JOK         Komplett neuer Ablauf und Funktionen zum Senden
 *                                      einer Nachricht implementiert
 * 2004-06-07   1.1         JOK         Diverse kleinere Optimierungen beim Empfangen
 *                                      einer Nachricht implementiert
 * 2004-06-07   1.1         JOK         Nur noch BapSegType_None (unsegmentiert) und
 *                                      BapSegType_One (segmentiert) unterstuetzt
 * 2004-03-15   1.0         KNE         Initiale Version
 ******************************************************************/


/* Systemincludes mit <...> */

/* Bibliotheken von externen Herstellen mit <...> */

/* Eigene Header-Dateien "..." */
#include "bap_canubs.h"
#include "bap_types.h"
#include "bap_bcl.h"
#include "bap_bclutil.h"
#include "bap_bclbus.h"
#include "bap_debug.h"
#include "bap_util.h"
#include "bap_bclconfig.h"

#ifdef DLL_COMPILATION
#include "bap_bclcan.h"
#endif

#ifdef BAP_RUNTIME_TEST
#include "sw_timer.h"
#endif /* BAP_RUNTIME_TEST */

#if defined(BAP_USES_CAN) || defined(BAP_USES_FR) || defined(BAP_USES_PDUR) || defined(BAP_USES_ETH)
#else
#error Bitte Bussystem definieren (CAN Oder FlexRay Oder PDU-Router).
#endif

/* Externe globale Variablen-Definitionen */
/*MISRA-2004, lokale Variable in BAP_BCL_CanCopyTransmitSeg ist jetzt als globale Variable */
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#ifdef DLL_COMPILATION
extern uint8_t Bap_aru8CanMsgObject[BAP_MAX_PDU_SIZE];
#else
/* MISRA 2012. Rule 8.4 */
BAP_STATIC DBGVAR uint8_t Bap_aru8CanMsgObject[BAP_MAX_PDU_SIZE];
#endif /* #ifdef DLL_COMPILATION */
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>

/*MISRA-2004: als global definieren, verwendet von Interruptlocking funktionen disableint/restoreint*/
#define BAP_START_SEC_VAR_INIT_8
#include <BAP_MemMap.h>
#ifdef DLL_COMPILATION
extern uint8_t Bap_u8IRQState;
#else
/* MISRA 2012. Rule 8.4 */
extern uint8_t Bap_u8IRQState;
    
uint8_t Bap_u8IRQState = (uint8_t)0;
#endif /* #ifdef DLL_COMPILATION */
#define BAP_STOP_SEC_VAR_INIT_8
#include <BAP_MemMap.h>

#if defined(BAP_ASG) && defined(BAP_USES_SEGMENTATION)
/* Variable fuer BAP 1.6.2 update
 * BAP_FALSE: CAN Interface der Funktion FctList von ASG und FSG ist nicht symmetrisch.
 *              d.h. ASG(Segmentierte) <--> FSG (Unsegmentierte)
 *              Speziele Behandlung noetig.
 * BAP_TRUE: normaler Fall, keine speziele Behandlung.
 *
 * Fuer FSG in Kombi ist dieser Variable immer BAP_TRUE
 */
#   define BAP_START_SEC_VAR_INIT_8
#   include <BAP_MemMap.h>
#   ifdef DLL_COMPILATION
extern bool_t Bap_bIsFctListSym;
#   else
/* MISRA 2012. Rule 8.4 */
extern DBGVAR bool_t Bap_bIsFctListSym;    

DBGVAR bool_t Bap_bIsFctListSym = BAP_TRUE;
#   endif /* #ifdef DLL_COMPILATION */
#   define BAP_STOP_SEC_VAR_INIT_8
#   include <BAP_MemMap.h>
#endif /* defined(BAP_ASG) && defined(BAP_USES_SEGMENTATION) */

/* Interne Makro-Definitionen */
/* Interne Typ-Definitionen */

#ifdef BAP_FSG
/* Nachfolgende Struktur ist ein Datenpuffer, der zum Versenden des Fehlerwertes genutzt wird */
#   define BAP_START_SEC_VAR_INIT_8
#   include <BAP_MemMap.h>
/* MISRA 2012. Rule 8.4 */
extern BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer_Err[1];

BAP_RAM_DATA_FAR uint8_t aru8BclTxBuffer_Err[1] = {(uint8_t) 0};
#   define BAP_STOP_SEC_VAR_INIT_8
#   include <BAP_MemMap.h>
/*lint -e545 */
/* "Warning: unsuspecious use of &" wird hier deactiviert.
 * Grund:   Then a and &a, as pointers, both represent the same bit pattern,
 *          but whereas a is a pointer to int, &a is a pointer to array 10 of int.
 *          Of the two only &a may be assigned to p without complaint. I
 *          If you are using the & operator in this way, we recommend that you disable this message.
 */
#   define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>
#   ifdef DLL_COMPILATION
extern BapBclTxRamRow_ot oBclTxRamRow;
#   else
/* MISRA 2012. Rule 8.4 */
extern BAP_RAM_DATA_FAR BapBclTxRamRow_ot oBclTxRamRow; 
/*lint -e9087*/ /* MISRA_2012_REQ_11.3 Intentional cast */
BAP_RAM_DATA_FAR BapBclTxRamRow_ot oBclTxRamRow = {
		{
#ifdef BAP_USES_ACKNOWLEDGE
				/* fTxRequestNeedsAckFlag */
				(uint8_t)0,
#endif
#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
				/* fTxErrorNeedsAckFlag */
				(uint8_t)0,
#endif
				/* fTxRequestFlag */
				(uint8_t)0,
#ifdef BAP_USES_SEGMENTATION
				/* fTxInProgressFlag */
				(uint8_t)0,
#endif
#ifdef BAP_FSG
				/* fTxErrorFlag */
				(uint8_t)0,
				/* fTxInitializedFlag */
				(uint8_t)0,
#endif
				/* fTxSendBufferFlag */
				(uint8_t)0
		}, BapErr_OK,  BapOp_PropReset_Set , {(uint16_t) 1, (paru8Buffer_t)&aru8BclTxBuffer_Err}};


/*lint +e9087*/
#   endif /* #ifdef DLL_COMPILATION */
#   define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>
/*lint +e545 */
#endif /* #ifdef BAP_FSG */

#ifndef DLL_COMPILATION
/**
 *  Parameterliste, die innerhalb der Verarbeitung von Daten aus dem Ringpuffer an Subroutinen
 *  uebergeben wird. Spart Stackspeicher und reduziert die Kopiervorgaenge.
 */
typedef struct BapRxParameters_t
{
    /**
     * Bap_oPars enthaelt folgende Parameter, welche im Fall von unsegmentieren Nachrichten
     * direkt weiter nach oben durchgereicht werden (ohne umzukopieren)
     * Bap_oPars.lsgId - Die LsgId, falls es sich um eine unsegmentierte Nachricht oder eine Startbotschaft handelt
     * Bap_oPars.poLsgRomRow - dto
     * Bap_oPars.fctId - Die FunctionId, falls es sich um eine unsegmentierte Nachricht oder eine Startbotschaft handelt
     * Bap_oPars.poFctRomRow - dto
     *
     * Die folgenden Parameter werden im folgenden im Aufrufstack modifiziert:
     * Bap_oPars.pData     - Zeigt auf die Nutzdaten, wird gesetzt vor dem Aufruf der Indication
     * Bap_oPars.eOpCode   - Der OpCode, falls es sich um eine unsegmentierte Nachricht oder eine
     *                   Startbotschaft handelt. Dieser wird nach oben gemeldet. Zum Melden des Empfangs
     *                   einer Startbotschaft an den BPL wird dessen Wert geaendert
     * Bap_oPars.u16Length - Laenge der Nutzdaten, diese Laenge hat nichts mit u16MsgLength zu tun.
     */
    BapInternalParameters_ot oPars;

    /** Enthaelt die empfangenen Daten */
    uint8_t aru8RxData[BAP_MAX_PDU_SIZE];

    /** Laenge der empfangenen Nachricht, bei CAN 0..8 Bytes, CAN-FD 0..64 Bytes, Ethernet 0..1514 Bytes */
    uint16_t u16MsgLength;

    /** Die CanId oder das CanMsgHandle des Vector-CAN-Treibers */
    BapCanMsgId_t canId;

#   ifdef BAP_USES_SEGMENTATION
    /** Nur bei Startbotschaft: Die Laenge der segmentierten Nachricht */
    /** Wird nur bei segmentierten Nachrichten benutzt */
    uint32_t u32SegmentationLength;
#   endif /* #ifdef BAP_USES_SEGMENTATION */

    /** Der Segmentierungstyp, d.h. bei Segmentierung der Kanal, sonst Unsegmented */
    BapSegmentationType_et eSegmentationType;

    /** Maske fuer den Segmentierungstyp, d.h. bei Segmentierung der Kanal, sonst alle Kanaele */
    BapSegmentationType_et eSegmentationTypeMask;

    /** Beschreibt das CAN Interface, von dem die Nachricht empfangen wurde */
    BapCanInterfaceChannel_t canInterfaceChannel;

    /** Zeiger auf die zu pruefende Zeile der Datenfestlegung */
    BapCanRxRomRow_pot poCanRxRomRow;
} BapRxParameters_ot;
#endif /* #ifdef DLL_COMPILATION */

/* MISRA-2004 fix: Bap_oRxPars als globale Variable definieren */
#define BAP_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
#ifdef DLL_COMPILATION
extern BapRxParameters_ot Bap_oRxPars;
#else
/* MISRA 2012. Rule 8.4 */
extern DBGVAR BapRxParameters_ot Bap_oRxPars;

DBGVAR BapRxParameters_ot Bap_oRxPars;
#endif /* #ifdef DLL_COMPILATION */
#define BAP_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/**
 *  Zeiger zeigt auf ein Element des Typs @see BapRxParameters_t, welches auf dem Stack angelegt wurde.
 */
typedef DBGVAR struct BapRxParameters_t * BapRxParameters_pot;

#ifdef BAP_USES_SEGMENTATION
/**
 *  Zeiger zeigt auf ein Element des Typs @see BapRxParameters_t, welches auf dem Stack angelegt wurde,
 *  und innerhalb der Funktion nicht veraendert wird.
 */
typedef DBGVAR const struct BapRxParameters_t * BapRxParameters_cpot;
#endif /* #ifdef BAP_USES_SEGMENTATION */


#ifndef DLL_COMPILATION
/**
 *  Parameterliste, die innerhalb der Sendefunktionen haeufig uebergeben wird.
 *  Reduziert Kopiervorgaenge.
 */
typedef struct BapTxParameters_t
{
    /** der zum LSG/FCT gehoerige Zeiger auf den Eintrag in der CanTxRom-Tabelle. */
    BapCanTxRomRow_pot poCanTxRomRow;

#   ifdef BAP_USES_SEGMENTATION
    /** entspricht poCanTxRomRow->poCanTxRamRow
     *  @remarks Optimierung der Dereferenzierungen
     */
    BapCanTxSegmentationRamRow_pot poCanTxRamRow;
#   endif  /* #ifdef BAP_USES_SEGMENTATION */

    /** der zum LSG/FCT gehoerige Zeiger auf den Eintrag des RAM-Bereiches */
    BapBclTxRamRow_pot poBclTxRamRow;
} BapTxParameters_ot;
#endif /* #ifdef DLL_COMPILATION */

/* MISRA-2004 fix: Bap_oTxPars als globale Variable definieren */
#define BAP_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
#ifdef DLL_COMPILATION
extern BapTxParameters_ot Bap_oTxPars;
#else
/* MISRA 2012. Rule 8.4 */
extern DBGVAR BapTxParameters_ot Bap_oTxPars;
    
DBGVAR BapTxParameters_ot Bap_oTxPars;
#endif /* #ifdef DLL_COMPILATION */
#define BAP_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/**
 *  Zeiger zeigt auf ein Element des Typs @see BapTxParameters_t, welches auf dem Stack angelegt wurde.
 */
typedef DBGVAR struct BapTxParameters_t * BapTxParameters_pot;

/**
 *  Zeiger zeigt auf ein Element des Typs @see BapTxParameters_t, welches auf dem Stack angelegt wurde.
 */
typedef DBGVAR const struct BapTxParameters_t * BapTxParameters_cpot;

/**
 *  Funktionszeigertyp fuer Behandlung empfangener Daten
 */
typedef BAP_IMPL_FAR void (*RxHandler_ft)(const BapRxParameters_pot BapRxParameter);

/* Interne Const Deklarationen */

/* Interne statische Variablen */
#define BAP_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
#ifdef DLL_COMPILATION
 extern BapCanRxBufferMeta_pot BAP_CanRxRingBufferFirstBlock;
 extern BapCanRxBufferMeta_pot BAP_CanRxRingBufferFifoHead;
 extern BapCanRxBufferMeta_pot BAP_CanRxRingBufferFifoTail;
#else
 static DBGVAR BapCanRxBufferMeta_pot BAP_CanRxRingBufferFirstBlock = NULL;
 static DBGVAR BapCanRxBufferMeta_pot BAP_CanRxRingBufferFifoHead = NULL;
 static DBGVAR BapCanRxBufferMeta_pot BAP_CanRxRingBufferFifoTail = NULL;
#endif
#define BAP_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <BAP_MemMap.h>


#ifdef BAP_USES_SEGMENTATION


/**
 * Konvertierung von Segmentierungstyp BapSegType_ChannelOne, BapSegType_ChannelTwo, BapSegType_ChannelThree, BapSegType_ChannelFour
 * in die Zahlenwerte 0x80, 0x90, 0xA0, 0xB0, wie sie im BAP Header kodiert sind.
 */
#   define BAP_START_SEC_CONST_8
#   include <BAP_MemMap.h>
static const uint8_t Bap_garu8HeaderBySegType[9] =
{
        (uint8_t)0, (uint8_t)0x80, (uint8_t)0x90, (uint8_t)0, (uint8_t)0xA0, (uint8_t)0, (uint8_t)0, (uint8_t)0, (uint8_t)0xB0
};
#   define BAP_STOP_SEC_CONST_8
#   include <BAP_MemMap.h>
#endif /* #ifdef BAP_USES_SEGMENTATION */

#ifdef BAP_USES_SEGMENTATION
/**
 * Konvertierung von Segmentierungstyp BapSegType_ChannelOne, BapSegType_ChannelTwo, BapSegType_ChannelThree, BapSegType_ChannelFour
 * in die Zahlenwerte 0, 1, 2, 3.
 */
#   define BAP_START_SEC_CONST_8
#   include <BAP_MemMap.h>
static const uint8_t Bap_garu8ChannelBySegType[9] =
{
        (uint8_t)0, (uint8_t)0, (uint8_t)1, (uint8_t)0, (uint8_t)2, (uint8_t)0, (uint8_t)0, (uint8_t)0, (uint8_t)3
};
#   define BAP_STOP_SEC_CONST_8
#   include <BAP_MemMap.h>
#endif /* #ifdef BAP_USES_SEGMENTATION */

/* Variablen fuer [SSWCCB-2391] Schnelle Suche TX-PDU */
#   define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>
#ifdef DLL_COMPILATION
extern BapMapCanIdByLsg_ot* Bap_poCanTxRingBuffer; /* Tx-Sende-Ringbuffer */
#else
/* MISRA 2012. Rule 8.4 */
extern BAP_RAM_DATA_FAR BapMapCanIdByLsg_ot Bap_poCanTxRingBuffer[BAP_CAN_TX_ROM_TABLE_ROWS];    

BAP_RAM_DATA_FAR BapMapCanIdByLsg_ot Bap_poCanTxRingBuffer[BAP_CAN_TX_ROM_TABLE_ROWS] = {{NULL}};
#endif /* #ifdef DLL_COMPILATION */
#   define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>
/*lint +e545 */

/* [FHA] 2017-07-25 Variablen BAP_BCL_CanTxBufferWrite und BAP_BCL_CanTxBufferRead herausgezogen, im Zusammenhang mit [SSWCCB-1545] aufgrund moeglicher Nebenlaeufigkeits-Probleme */
#ifndef DLL_COMPILATION
#   define BAP_START_SEC_VAR_INIT_8
#   include <BAP_MemMap.h>
static DBGVAR uint8_t Bap_u8CanTxBufferLength[BAP_CAN_TX_SEGMENTATION_CHANNELS] = {(uint8_t)0}; /* Zum Sichern der im Ringbuffer enthaltenen Elemente */
static DBGVAR uint8_t Bap_u8TxRomRowBufferReadPos[BAP_CAN_TX_SEGMENTATION_CHANNELS] = {(uint8_t)0}; /* Zum Sichern der Ringbuffer-Leseposition */
static DBGVAR uint8_t Bap_u8TxRomRowBufferWritePos[BAP_CAN_TX_SEGMENTATION_CHANNELS] = {(uint8_t)0}; /* Zum Sichern der Ringbuffer-Schreibposition */
#define BAP_STOP_SEC_VAR_INIT_8
#include <BAP_MemMap.h>
#else
#define BAP_START_SEC_VAR_INIT_8
#include <BAP_MemMap.h>
extern uint8_t* Bap_u8CanTxBufferLength; /* Zum Sichern der im Ringbuffer enthaltenen Elemente */
extern uint8_t* Bap_u8TxRomRowBufferReadPos; /* Zum Sichern der Ringbuffer-Leseposition */
extern uint8_t* Bap_u8TxRomRowBufferWritePos; /* Zum Sichern der Ringbuffer-Schreibposition */
#   define BAP_STOP_SEC_VAR_INIT_8
#   include <BAP_MemMap.h>
#endif /* #ifdef DLL_COMPILATION */

/* Vorwaerts-Deklarationen von statischen Funktionen */

#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>

#ifdef BAP_USES_SEGMENTATION
BAP_STATIC BAP_IMPL_FAR void
BAP_BCL_CanCopyTransmitSeg(BapTxParameters_cpot apoTxPars
        , DBGVAR uint8_t au8Header0
        , DBGVAR uint16_t au16Len
        , DBGVAR uint32_t au32Offset);
#else /* BAP_USES_SEGMENTATION */
static BAP_IMPL_FAR void
BAP_BCL_CanCopyTransmitNonSeg(BapTxParameters_cpot apoTxPars
        , DBGVAR uint16_t au16Len);
#endif /* BAP_USES_SEGMENTATION */

static BAP_IMPL_FAR bool_t
BAP_BCL_CanCheckRxData(DBGVAR BapCanMsgId_t aCanMsgId,
#ifdef BAP_USES_SEGMENTATION
        DBGVAR const uint8_t apData[],
#endif /* BAP_USES_SEGMENTATION */
        DBGVAR uint16_t au16MsgLength);

#ifdef BAP_USES_SEGMENTATION
BAP_STATIC BAP_IMPL_FAR bool_t
BAP_BCL_CanSendStartMsg(BapTxParameters_cpot apoTxPars);
#endif /* BAP_USES_SEGMENTATION */

#ifdef BAP_USES_SEGMENTATION
static BAP_IMPL_FAR void
BAP_BCL_CanSendSequenceMsg(BapTxParameters_cpot apoTxPars);
#endif /* BAP_USES_SEGMENTATION */

#ifdef BAP_USES_SEGMENTATION
static BAP_IMPL_FAR bool_t
BAP_BCL_CheckSegStart(const BapRxParameters_pot apoRxPars, uint16_t u16PduSize, BapOpCodes_et eOpCode
#ifdef BAP_ASG
        , const BapInternalParameters_pot poPars
#endif /* BAP_ASG */
);
#endif /* BAP_USES_SEGMENTATION */

static BAP_IMPL_FAR bool_t
BAP_BCL_LowerLevelCanTxTask(BapTxParameters_cpot apoTxPars);

static BAP_IMPL_FAR bool_t
BAP_BCL_LowLevelCanTxTask(BapTxParameters_pot apoTxPars);

static BAP_IMPL_FAR void
BAP_CAN_AnalyzeHeaderBytes(const BapRxParameters_pot apoRxPars);

static BAP_IMPL_FAR void
BAP_CAN_RxNothing(const BapRxParameters_pot apoRxPars);

static BAP_IMPL_FAR void
BAP_CAN_RxUnsegmented(const BapRxParameters_pot apoRxPars);

#ifdef BAP_USES_SEGMENTATION
static BAP_IMPL_FAR void
BAP_CAN_RxSegCompleteCheck(const BapRxParameters_cpot apoRxPars);
#endif /* BAP_USES_SEGMENTATION */

#ifdef BAP_USES_SEGMENTATION
BAP_STATIC BAP_IMPL_FAR void
BAP_CAN_RxSegmentedStart(const BapRxParameters_pot apoRxPars);
#endif /* BAP_USES_SEGMENTATION */

#ifdef BAP_USES_SEGMENTATION
BAP_STATIC BAP_IMPL_FAR void
BAP_CAN_RxSegmentedSequence(const BapRxParameters_cpot apoRxPars);
#endif /* BAP_USES_SEGMENTATION */

#ifdef BAP_USES_SEGMENTATION
static BAP_IMPL_FAR bool_t
BAP_BCL_CanReceiveSequence(const BapRxParameters_pot apoRxPars);
#endif /* BAP_USES_SEGMENTATION */

#ifdef BAP_USES_SEGMENTATION
static BapCanRxDynSegChannels_pot  BAP_IMPL_FAR
BAP_BCL_GetRxDynSegChannel(BapCanMsgId_t aCanId);
#endif /* BAP_USES_SEGMENTATION */

BAP_STATIC BAP_IMPL_FAR bool_t
BAP_BCL_CanProcessData(BapRxParameters_pot apoRxPars, RxHandler_ft apfnRxHandler);

BAP_STATIC BAP_IMPL_FAR void
BAP_BCL_CanReceiveData(BapCanRxBuffer_cpot apoCanRxBuffer);

#if defined(BAP_ASG) && defined(BAP_USES_SEGMENTATION)
static BAP_IMPL_FAR bool_t
BAP_BCL_CheckCanIfSymmetry(BapRxParameters_pot apoRxPars);
#endif

#ifdef BAP_USES_ACKNOWLEDGE
static BAP_IMPL_FAR void
BAP_BCL_IfReqAcknowledge(BapTxParameters_cpot apoTxPars);
#else
#define BAP_BCL_IfReqAcknowledge(dummy) (void)(0)
#endif  /* #else #ifdef BAP_USES_ACKNOWLEDGE */

#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>

/* Definition (Implementierung) von statischen Funktionen */

#ifdef BAP_USES_ACKNOWLEDGE
/**
 *  Ruft BAP_BCL_Acknowledge auf, falls dies erforderlich ist
 *
 *  @param apoTxPars - Zeiger auf die Uebergabeparameterliste
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
static BAP_IMPL_FAR void
BAP_BCL_IfReqAcknowledge(BapTxParameters_cpot apoTxPars)
{
    /*lint -esym(613,apoTxPars)*/
    BAP_ASSERT(NULL != apoTxPars);

    if (BAP_FALSE != apoTxPars->poBclTxRamRow->flags.fTxRequestNeedsAckFlag)
    {
        apoTxPars->poBclTxRamRow->flags.fTxRequestNeedsAckFlag = BAP_FALSE;
        /* Acknowledge an BPL melden */
        BAP_BCL_Acknowledge(apoTxPars->poCanTxRomRow->poFctRomRow, apoTxPars->poBclTxRamRow->eOpCode);
    }
    return;
    /*lint +esym(613,apoTxPars)*/
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif  /* #ifdef BAP_USES_ACKNOWLEDGE */


#ifdef BAP_USES_SEGMENTATION
/**
 *  Kopiert die zu sendenden Daten in einen Puffer und ruft dann die
 *  Transmit-Funktion der UBS-Schnittstelle auf. Diese Funktion hat zwei
 *  Auspraegungen, eine mit Header-Daten im Falle von Segmentierung
 *  und eine ohne Header-Daten falls keine Segmentierung per Compiler-Schalter
 *  aktiviert wurde.
 *
 *  @param apoTxPars - Zeiger auf die Uebergabeparameterliste
 *
 *  @param  au8Header0 das nullte Byte des Headers bei einer segmentierten Nachricht
 *
 *  @param  au8Header1 das erste Byte des Headers bei einer segmentierten Nachricht
 *
 *  @param  au8Len die Laenge der zu uebertragenden Daten
 *
 *  @param  au32Offset der Offset im BCL-Sendepuffer, ab dem die Daten aus dem
 *          BCL-Puffer in den CAN-Puffer kopiert werden.
 *
 *  Diese Funktion hat 12 OutgoingCalls (max.7), 63 Statements (max.50)
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_STATIC BAP_IMPL_FAR void
BAP_BCL_CanCopyTransmitSeg(BapTxParameters_cpot apoTxPars
        , DBGVAR uint8_t au8Header0
        , DBGVAR uint16_t au16Len
        , DBGVAR uint32_t au32Offset)
{
    DBGVAR uint16_t u16UserDataLen; /* die Nutzdatalaenger einer Botschaft, PDU_Size - Headerlaenge */
    DBGVAR uint8_t u8CopyOffset;
    DBGVAR uint16_t u16PduSize;  /* die gesamte PDU_Size einer Botschaft, einzel definiert in xml. */
    DBGVAR uint32_t u32LengthNewFormat; /* die gesamte Laenger der Nachricht */

    BAP_InitInternalParameters(&Bap_oPars);
    /*lint -esym(613,apoTxPars)*/
    BAP_ASSERT(NULL != apoTxPars);

    Bap_oPars.poFctRomRow = apoTxPars->poCanTxRomRow->poFctRomRow;
    Bap_oPars.fctId = Bap_oPars.poFctRomRow->fctId;
    Bap_oPars.lsgId = Bap_oPars.poFctRomRow->lsgId;
    Bap_oPars.poLsgRomRow = BAP_GetLsgRomRow(Bap_oPars.lsgId);
#ifdef BAP_ASG
    Bap_oPars.eOpCode = BapOp_MessageSent;
#endif /* #ifdef BAP_ASG */
    Bap_oPars.pData = NULL;
    Bap_oPars.u32Length = (uint16_t)0;


    u16PduSize = BAP_GetTxPduSize(apoTxPars->poCanTxRomRow->canMsgId);
    /* Initialisiere mit 00 falls DBGVAR genutzt wird */
#ifndef BAP_AUTO_DBGVAR
    MEMSET(Bap_aru8CanMsgObject, 0, u16PduSize);  /*  2014-11-17 WWU BAP 1.8.0: Ersetze 8 durch Konfigurierbare PDU Groesse   */
#endif /* BAP_AUTO_DBGVAR */

    /* -- Aufbereitung des BAP-Headers -- */

    /* Kopiere Header1 falls segmentierte Botschaft */
    if(BAP_BIT7 == (au8Header0 & BAP_BIT7))
    {
        /* Kopiere Header2 falls Startbotschaft */
        if( (uint8_t)0 == (au8Header0 & BAP_BIT6))
        {
            u32LengthNewFormat =  apoTxPars->poBclTxRamRow->oBufferWithLength.u32Length;
            if ( u16PduSize > BAP_MAX_PDU_SIZE_OLD_FORMAT)
            {
                /* 2014-11-25 WWU: BAP 1.8.0 */
                /* Startbotschaft mit neuem Format */
                /* | Byte-0  | Byte-1   | Byte-2...5     | */
                /* |10XX 1111| 1111 1111| 4-Bytes Laenge |  */
                Bap_aru8CanMsgObject[0] = au8Header0 | ((uint8_t)0x0F);  /* Setze untere 4-Bits als 1 in neuem Format */
                Bap_aru8CanMsgObject[1] = (uint8_t) 0xFF;
                /* Berechnung der 4-Bytes Seg.Laenge */
                Bap_aru8CanMsgObject[2] = (uint8_t)(u32LengthNewFormat >> 24);
                Bap_aru8CanMsgObject[3] = (uint8_t)(u32LengthNewFormat >> 16);
                Bap_aru8CanMsgObject[4] = (uint8_t)(u32LengthNewFormat >> 8);
                Bap_aru8CanMsgObject[5] = (uint8_t) u32LengthNewFormat;
                u8CopyOffset = BAP_HEADER_BYTES_SEG_NEW;  /* Startbotschaft hat 8 Bytes Header in neuem Format. */
            }else{
                /* Startbotschaft mit altem Format */
                /* | Byte-0   | Byte-1   | Byte-2...7     | */
                /* |10XX 12Bit| Laenge   | Data           |  */
                Bap_aru8CanMsgObject[0] = au8Header0 + (uint8_t)((uint16_t)(u32LengthNewFormat) >> 8);
                Bap_aru8CanMsgObject[1] = (uint8_t)u32LengthNewFormat;
                u8CopyOffset = BAP_HEADER_BYTES_SEG_OLD;  /* Startbotschaft hat 4 Bytes BAP Header in altem Format. */
            }
        }
        else
        {
            /* Sequenzbotschaft */
            Bap_aru8CanMsgObject[0] = au8Header0;
            u8CopyOffset = BAP_HEADER_BYTES_SEG_DATA;  /* Sequenzbotschaft hat 1 Byte BAP Header */
        }
    }
    else
    {
        u8CopyOffset = BAP_HEADER_BYTES_NONSEG;      /* Unsegmentierte Nachricht hat 2 Bytes BAP Header */
    }

    /* Falls unsegmentierte Nachricht oder Startbotschaft, dann BAP Standard-Header hinzufuegen */
    if (u8CopyOffset > BAP_HEADER_BYTES_SEG_DATA)
    {
        /* Kopiere LSG-ID, FCT-ID und OpCode in Sende-Puffer. */
        /* 2013-01-16 BAP-1.7, SSWCCB-809, GRO
         * Setze LsgId = 0 falls neue LsgId verwendet wird.   */
        const uint8_t u8LsgId = ( Bap_oPars.poLsgRomRow->bNewLsgId !=(uint8_t)0 ) ? (uint8_t)0 : BAP_BINARY_ID(Bap_oPars.lsgId);

        Bap_aru8CanMsgObject[u8CopyOffset-(uint8_t)2] = (uint8_t) ((uint8_t)(((uint8_t)apoTxPars->poBclTxRamRow->eOpCode)<<BAP_OPCODE_POS) | (uint8_t)(u8LsgId>>BAP_LSGID_POS_IN_FIRSTBYTE));
        Bap_aru8CanMsgObject[u8CopyOffset-(uint8_t)1] = (uint8_t) ((uint8_t)(u8LsgId<<BAP_LSGID_POS_IN_SECONDBYTE) | BAP_BINARY_ID(Bap_oPars.fctId));
    }
    else
    {
        /* Bei Sequenzbotschaften ist kein zusaetzlicher Header erforderlich, da diese Informationen
           bereits aus der Startbotschaft bekannt sind. */
    }

    /* -- Aufbereitung der Nutzdaten -- */

    /* Kopiere Nutzdaten in den Puffer */
    /*lint -e9087*/ /* MISRA_2012_REQ_11.3 : 1st and 2nd arguments of MEMCPY are of types (uint8_t*).
                     * They are implicitly cast to (void*). The memory is packed because it is uint8_t so there should be no problem to copy.*/
    MEMCPY(&Bap_aru8CanMsgObject[u8CopyOffset], &(*apoTxPars->poBclTxRamRow->oBufferWithLength.paru8Buffer)[au32Offset], au16Len);
    /*lint +e9087*/
    if (BAP_FALSE != Bap_oPars.poLsgRomRow->bUseDLC8)
    {
        /* Verwende feste DLC Laenge 8 */
        u16UserDataLen = (uint16_t)8;
    }
    else
    {
        /* Den Header auch zur Nutzdatenlaenge hinzuzaehlen */
        u16UserDataLen = au16Len + u8CopyOffset;
    }

    /* 2014-11-17 WWU BAP 1.8.0: Konfigurierbare PDU Groesse
     */
    if (u16UserDataLen > u16PduSize)
    {
        /* Schneide ggfs. Daten ab. */
        u16UserDataLen = u16PduSize;
    }
    else
    {
        /* nimm die uebergebene Laenge */
    }

    /* Initiiere Versenden der Nachricht */
    /* MISRA_2012_REQ_14.3 : The controlling expression is not invariant,
     * but always true except if no valid interface channel is found */
    if (BAP_FALSE != BAP_CANUBS_TxData(apoTxPars->poCanTxRomRow->canInterfaceChannel
            , apoTxPars->poCanTxRomRow->canMsgId
            , Bap_aru8CanMsgObject
            , u16UserDataLen))
    {
        /* Nur falls segmentierte Nachricht */
        if ((uint8_t) BAP_HEADER_BYTES_NONSEG != u8CopyOffset)
        {
            /* Setze Tx-InProgress Flag */
            apoTxPars->poBclTxRamRow->flags.fTxInProgressFlag = BAP_TRUE;
        }
        /* Restart Inhibit Timer */
        BAP_InhibitRamTable[apoTxPars->poCanTxRomRow->u8InhibitIndex].u16InhibitTimer
        = BAP_InhibitRomTable[apoTxPars->poCanTxRomRow->u8InhibitIndex].u16ConfiguredInhibitTime;

        /* Loesche Tx-Request Flag */
        apoTxPars->poBclTxRamRow->flags.fTxRequestFlag = BAP_FALSE;

        /* Etwas wurde erfolgreich versendet */
        BAP_DBG_TxEvent();

#ifdef BAP_ASG
        /* Keine explizite Fallunterscheidung fuer das Kombigeraet, da weiter oben verworfen */
        /* Eine Nachricht wurde vom CAN-Treiber erfolgreich verschickt an BPL melden, wird zum retriggern der Retry-Timer benoetigt */
        BAP_BCL_DataReceived(&Bap_oPars);
#endif /* #ifdef BAP_ASG */

        /* Verschiebe Offset falls segmentierte Botschaft */
        if(BAP_BIT7 == (au8Header0 & BAP_BIT7))
        {
            apoTxPars->poCanTxRamRow->u32BclTxBufferByteOffset = (uint32_t)(apoTxPars->poCanTxRamRow->u32BclTxBufferByteOffset + (uint32_t)au16Len);
            if(BAP_BIT6 == (au8Header0 & BAP_BIT6))
            {
                /* Bei Sequenzbotschaften die Nummer nach dem Versenden erhoehen. 4 Bit Zaehler. */
                apoTxPars->poCanTxRamRow->flags.fSequenceNumber
                = (uint8_t) (((uint8_t) apoTxPars->poCanTxRamRow->flags.fSequenceNumber + (uint8_t)1) & BAP_BITMASK_00001111);
            }
            else
            {
                /* Melde DebugEvent falls Startbotschaft */
                BAP_DBG_TxStartMsgEvent(Bap_oPars.lsgId);
            }
            /* Senden beenden wenn alle Segmente erfolgreich versandt wurden */
            if(apoTxPars->poCanTxRamRow->u32BclTxBufferByteOffset
                    >= apoTxPars->poBclTxRamRow->oBufferWithLength.u32Length)
            {
                BAP_DBG_TxSegMsgCompleteEvent(Bap_oPars.lsgId);

                apoTxPars->poBclTxRamRow->flags.fTxInProgressFlag = BAP_FALSE;
                /* 2014-06-25 WWU: CR verlaengerte Inhibitzeit nach segmentierter Botschaft
                 * Nach dem Senden einer segmentierten Botschaft soll die Inhibitzeit einmalig
                 * um eine konstante Anzahl von Taskzyklen verlaengert werden. */
                BAP_InhibitRamTable[apoTxPars->poCanTxRomRow->u8InhibitIndex].u16InhibitTimer += BAP_INHIBITADDITIONAL_TIMER;

                BAP_BCL_IfReqAcknowledge(apoTxPars);
            }
        }
        else
        {
            BAP_BCL_IfReqAcknowledge(apoTxPars);
        }
    }
    else
    {
        /* Daten konnten nicht versendet werden.
           Beim naechsten Aufruf wird versucht die Botschaft erneut zu senden */
    }
    return;
    /*lint +esym(613,apoTxPars)*/
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#else /* #ifdef BAP_USES_SEGMENTATION */


/**
 *  Kopiert die zu sendenden Daten in einen Puffer und ruft dann die
 *  Transmit-Funktion der UBS-Schnittstelle auf. Diese Funktion hat zwei
 *  Auspraegungen, eine mit Header-Daten im Falle von Segmentierung
 *  und eine ohne Header-Daten falls keine Segmentierung per Compiler-Schalter
 *  aktiviert wurde.
 *
 *  @param apoTxPars - Zeiger auf die Uebergabeparameterliste
 *
 *  @param  au8Len die Laenge der zu uebertragenden Daten
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
static BAP_IMPL_FAR void
BAP_BCL_CanCopyTransmitNonSeg(BapTxParameters_cpot apoTxPars
        , DBGVAR uint16_t au16Len)
{
    /*lint -esym(613,apoTxPars)*/
    BapFctRomRow_pot poFctRomRow = apoTxPars->poCanTxRomRow->poFctRomRow;
    DBGVAR fctId_t fctId = poFctRomRow->fctId;
    DBGVAR lsgId_t lsgId = poFctRomRow->lsgId;
    DBGVAR uint16_t u16UserDataLen;
    DBGVAR uint16_t u16MaxDataSize; /* max. erlaubte Datalaenge in eine Botschaft */
    BapLsgRomRow_pot poLsgRomRow = BAP_GetLsgRomRow(lsgId);

    /* Begrenze die Laenge auf die von aru8Buffer, damit der Stack nicht ueberschrieben wird.
     */
    /* 2014-11-17 WWU BAP 1.8.0: Konfigurierbare PDU Groesse  */
    u16MaxDataSize = BAP_GetTxPduSize(apoTxPars->poCanTxRomRow->canMsgId) - BAP_HEADER_BYTES_NONSEG;
    if (au16Len > u16MaxDataSize)
    {
        /* Schneide ggfs. Daten ab. */
        au16Len = u16MaxDataSize;
    }
    else
    {
        /* nimm die uebergebene Laenge */
    }

    /* Initialisiere mit 00 falls DBGVAR genutzt wird */
#ifndef BAP_AUTO_DBGVAR
    MEMSET(aru8Buffer, 0, BAP_GetTxPduSize(apoTxPars->poCanTxRomRow->canMsgId));
#endif /* BAP_AUTO_DBGVAR */

    /* Kopiere LSG-ID, FCT-ID und OpCode in Sende-Puffer */
    /* 2013-01-16 BAP-1.7, SSWCCB-809, GRO
     * Setze LsgId = 0 falls neue LsgId verwendet wird.
     */

    /*lint -e9033*/ /*MISRA_2012_REQ_10.8 : (uint8_t)0 and BAP_BINARY_ID(lsgId) cast to lsgId_t. lsgId_t is either uint8_t or enum so it can fit an uint8_t.*/
    /*lint -e9034*/ /*MISRA_2012_REQ_10.3 : Cast will not cause any loss of information if lsgId_t is uint8_t or enum.*/
    lsgId = (lsgId_t)(( poLsgRomRow->bNewLsgId != (uint8_t)0 ) ? (uint8_t)0 : BAP_BINARY_ID(lsgId));
    /*lint +e9034*/
    /*lint +e9033*/

    if(BAP_FALSE != poLsgRomRow->bNewLsgId){
        /*lint -e9034*/ /* MISRA_2012_REQ_10.3 : PC-Lint 9.00L throws a warning due to Tool bug. Hence, this warning has been deactivated.
                         * Documented with a mail from the Lint team in the SSWCCB-2522_BAP-Entwicklung auf MISRA2012 umstellen folder */
        lsgId = (lsgId_t)0;
        /*lint +e9034*/
    }

    Bap_aru8CanMsgObject[0] = (uint8_t) ((uint8_t)(((uint8_t)apoTxPars->poBclTxRamRow->eOpCode)<<BAP_OPCODE_POS) | (uint8_t)((const uint8_t)lsgId>>BAP_LSGID_POS_IN_FIRSTBYTE));
    Bap_aru8CanMsgObject[1] = (uint8_t) ( (uint8_t)((const uint8_t)lsgId<<BAP_LSGID_POS_IN_SECONDBYTE) | ((const uint8_t)fctId) );

    /* Fuelle Datenelement in den temporaeren UBS Puffer */
    /*lint -e9087*/ /* MISRA_2012_REQ_11.3 : 1st and 2nd arguments of MEMCPY are of types (uint8_t*).
                     * They are implicitly cast to (void*). The memory is packed because it is uint8_t so there should be no problem to copy.*/
    MEMCPY(&Bap_aru8CanMsgObject[BAP_HEADER_BYTES_NONSEG], apoTxPars->poBclTxRamRow->oBufferWithLength.paru8Buffer, au16Len);
    /*lint +e9087*/

    BAP_ASSERT(poLsgRomRow != NULL);

    /* [FST] 2014-10-20 Kompatibilitaet zu BAP 1.1 nicht mehr gefordert */
    if (BAP_FALSE != poLsgRomRow->bUseDLC8) /*lint !e613  nur wenn es das Steuergeraet gibt, wird diese Funktion aufgerufen */
    {
        /* Verwende feste DLC Laenge 8 (Unterstuetzung BAP 1.1) */
        u16UserDataLen = (uint16_t)8;
    }
    else
    {
        /* Den Header auch zur Nutzdatenlaenge hinzuzaehlen */
        u16UserDataLen = (uint16_t) (au16Len + (uint16_t) BAP_HEADER_BYTES_NONSEG);
    }

    /* Initiiere das Versenden der CAN Message */
    if(BAP_FALSE != BAP_CANUBS_TxData(apoTxPars->poCanTxRomRow->canInterfaceChannel
            , apoTxPars->poCanTxRomRow->canMsgId
            , Bap_aru8CanMsgObject
            , u16UserDataLen))
    {
        /* Restart Inhibit Timer */
        BAP_InhibitRamTable[apoTxPars->poCanTxRomRow->u8InhibitIndex].u16InhibitTimer
        = BAP_InhibitRomTable[apoTxPars->poCanTxRomRow->u8InhibitIndex].u16ConfiguredInhibitTime;
        /* Loesche Tx-Request Flag */
        apoTxPars->poBclTxRamRow->flags.fTxRequestFlag = BAP_FALSE;

        BAP_BCL_IfReqAcknowledge(apoTxPars);

        /* Etwas wurde erfolgreich versendet */
        BAP_DBG_TxEvent();
    }
    else
    {
        /* Daten konnten nicht versendet werden.
           Beim naechsten Aufruf wird versucht die Botschaft erneut zu senden */
    }
    return;
    /*lint +esym(613,apoTxPars)*/
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* #ifdef BAP_USES_SEGMENTATION /#else  */

#ifdef BAP_USES_SEGMENTATION
/**
 *  Initialisiert das Senden einer segmentierten Botschaft und beginnt mit der
 *  Uebertragung durch das Senden der Startbotschaft.
 *
 *  @param apoTxPars - Zeiger auf die Uebergabeparameterliste
 *
 *  @retval BAP_TRUE - Ein Kanal wurde reserviert und der Versuch unternommen,
 *  die Daten an den CAN-Treiber zu uebergeben.
 *
 *  @retval BAP_FALSE - Kein freier Segmentierungskanal vorhanden
 *
 *  Diese Funktion hat 7 ControlNestingLayers (max.4)
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_STATIC BAP_IMPL_FAR bool_t
BAP_BCL_CanSendStartMsg(BapTxParameters_cpot apoTxPars)
{
    /*lint -esym(613,apoTxPars)*/
    DBGVAR uint32_t u32Length = apoTxPars->poBclTxRamRow->oBufferWithLength.u32Length;

    DBGVAR bool_t bSegmentationChannelIsFree = BAP_FALSE;

    /* Merkt sich, welche Funktion den aktuellen Segmentierungskanal verwendet */
    BapCanTxRomRow_pot * ppoSelectedCanTxRomRow = NULL;
    /*lint -esym(613,ppoSelectedCanTxRomRow)*/ /* Im folgenden Code ist sichergestellt dass nicht NULL */

    DBGVAR uint8_t u8SegmentationChannel;
    DBGVAR bool_t bRetVal = BAP_TRUE;

    /* insgesamt 2 mal soll die do-while-Schleife durchlaufen werden */
    DBGVAR uint8_t u8LoopCounter;

    for(u8LoopCounter=(uint8_t)0; u8LoopCounter<(uint8_t)2; u8LoopCounter++)
    {
        for (u8SegmentationChannel=(uint8_t)0; (BAP_FALSE == bSegmentationChannelIsFree) && (u8SegmentationChannel<BAP_NUM_SEG_CHANNELS); u8SegmentationChannel++)
        {
            /*lint -e9033*/ /* MISRA_2012_REQ_10.8 : logical operation is performed on two uint8_t operands which is cast to an uint8_t.
                             *No risk arise because: u8SegmentationChannel is less than 4, so the operation "1u<<u8SegmentationChannel"
                             * will not overflow an uint8_t.*/
            /*lint -e9034*/ /* MISRA_2012_REQ_10.5 : cast from uint8_t to BapSegmentationType_et, which is defined as an enum,
             	 	 	 	 * so no risk arise because no loss of information as uint8_t can fit in an enum.*/
            apoTxPars->poCanTxRamRow->eSelectedSegmentationChannel = (BapSegmentationType_et) ((uint8_t)(1u << u8SegmentationChannel));
            /*lint +e9033*/
            /*lint +e9034*/
			ppoSelectedCanTxRomRow = &apoTxPars->poCanTxRomRow->poTxDynSegChannels->arpoTxDynSegChannels[u8SegmentationChannel];

			/* 1. aeusserer Schleifendurchlauf */
			if ((uint8_t)0==u8LoopCounter)
			{
				/* Pruefe, ob ein reservierter Segmentierungskanal zur Verfuegung steht, */
				/* Falls der Kanal durch die aktuelle Funktion belegt wurde, dann kann er wieder verwendet werden */
				bSegmentationChannelIsFree = (*ppoSelectedCanTxRomRow == apoTxPars->poCanTxRomRow)?  BAP_TRUE : BAP_FALSE;
			}
			else
			{
				/*  2. aeusserer Schleifendurchlauf */
				/*  Pruefe, ob ein freier Segmentierungskanal zur Verfuegung steht */
				if ( *ppoSelectedCanTxRomRow == NULL )
				{
					/*  Falls ja, dann muss der Kanal auch frei sein */
					bSegmentationChannelIsFree = BAP_TRUE;
				}
				else
				{
					/* Ueberpruefe, ob alte Uebertragung bereits zu Ende, dann kann der Kanal auch wieder verwendet werden */
					if(  ( (bitfield_t) 1u == (*ppoSelectedCanTxRomRow)->poBclTxRamRow->flags.fTxRequestFlag)
							|| ((bitfield_t) 1u == (*ppoSelectedCanTxRomRow)->poBclTxRamRow->flags.fTxInProgressFlag)
#ifdef BAP_FSG
							/* Keine explizite Fallunterscheidung fuer das Kombigeraet, da im ASG TxError inaktiv */
							|| ((bitfield_t) 1u == (*ppoSelectedCanTxRomRow)->poBclTxRamRow->flags.fTxErrorFlag)
#endif /* #ifdef BAP_FSG */
					)
					{
						bSegmentationChannelIsFree = BAP_FALSE;
					}
					else
					{
						bSegmentationChannelIsFree = BAP_TRUE;
					}
				}
			}
        }
    }



    /* Versende Daten nur dann, wenn ein freier Segmentierungskanal gefunden wurde */
    if (BAP_FALSE == bSegmentationChannelIsFree)
    {
        apoTxPars->poCanTxRamRow->eSelectedSegmentationChannel = BapSegType_Unsegmented;
        bRetVal = BAP_FALSE;
    }
    else
    {
        DBGVAR uint8_t u8HeaderByte0;
        DBGVAR uint16_t u16CopyLength;
        DBGVAR uint16_t u16MaxDataSize;  /* max. Datalaenge in eine Botschaft */

        /* Senden darf gestartet werden */

        /* Initialisiere Sequenzzaehler und Offsetzaehler */
        apoTxPars->poCanTxRamRow->flags.fSequenceNumber = (uint8_t)0;
        apoTxPars->poCanTxRamRow->u32BclTxBufferByteOffset = (uint32_t)0;

        /* Belege den Segmentierungskanal durch die aktuelle Funktion */
        *ppoSelectedCanTxRomRow = apoTxPars->poCanTxRomRow;

        /* Baue Header auf */
        /* berechne das obere Nibble des Headers der StartMessage 1->80, 2->90, 4->A0, 8->B0 */
        u8HeaderByte0 = Bap_garu8HeaderBySegType[apoTxPars->poCanTxRamRow->eSelectedSegmentationChannel];

        u16MaxDataSize = BAP_GetTxPduSize(apoTxPars->poCanTxRomRow->canMsgId);  /* hole konfigurierte PDU-Groesse */

        /* 2012-12-11 WWU: Dyn. PDU-Groesse */
        if(u16MaxDataSize > (uint16_t)BAP_HEADER_BYTES_SEG_NEW)
        {
            u16MaxDataSize -= BAP_HEADER_BYTES_SEG_NEW; /* Neues Format hat 8 Bytes Header  */
        }
        else
        {
            u16MaxDataSize -= (uint16_t)BAP_HEADER_BYTES_SEG_OLD; /* Default PDU-Groesse ist 8, altes Format hat 4 Bytes Header, deswegen 4  */
        }


        u16CopyLength = (u32Length < u16MaxDataSize ) ? (uint16_t) u32Length : u16MaxDataSize;
        /* Kopiere die Daten in den CAN Puffer und versende sie */
        /* Header Byte fuer Startbotschaft wird spaeter berechnet */
        BAP_BCL_CanCopyTransmitSeg(apoTxPars
                , u8HeaderByte0 /* enthalt nur SegmentionChannel */
                , u16CopyLength
                , (uint32_t) 0u);
    }

    return bRetVal;
    /*lint +esym(613,ppoSelectedCanTxRomRow)*/
    /*lint +esym(613,apoTxPars)*/
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_USES_SEGMENTATION */


#ifdef BAP_USES_SEGMENTATION
/**
 *  Prueft, ob schon alle Segmente der segmentierten Botschaft versandt wurden
 *  und setzt im Falle der vollstaendigen Botschaft die entsprechenden Flags.
 *  Stehen noch Teile der Botschaft aus, werden diese als Sequenzbotschaft
 *  verschickt.
 *
 *  @param apoTxPars - Zeiger auf die Uebergabeparameterliste
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
static BAP_IMPL_FAR void
BAP_BCL_CanSendSequenceMsg(BapTxParameters_cpot apoTxPars)
{
    DBGVAR uint32_t u32SequenceMessageMemcpyLength;
    DBGVAR uint16_t u16MaxDataSize;

    /*lint -esym(613,apoTxPars)*/
    BAP_ASSERT(NULL != apoTxPars);

    /* Fuelle Folgedaten des Datenelements in das CAN Message
       Object fuer die Sequenzebotschaft und verwalte CanTxRam
       Daten */
    u32SequenceMessageMemcpyLength
    = (uint32_t)(apoTxPars->poBclTxRamRow->oBufferWithLength.u32Length
            - apoTxPars->poCanTxRamRow->u32BclTxBufferByteOffset);

    u16MaxDataSize = BAP_GetTxPduSize(apoTxPars->poCanTxRomRow->canMsgId) - (uint16_t)1; /* PDU-Size - 1 Byte Sqz-Header */

    if(u32SequenceMessageMemcpyLength >= (uint32_t) (u16MaxDataSize))
    {
        u32SequenceMessageMemcpyLength = (uint32_t) u16MaxDataSize;
    }

    /* Kopiere die Daten in den CAN Puffer und versende sie */
    /* Daten haben bei Sequenzbotschaft noch 1Byte Header */
    BAP_BCL_CanCopyTransmitSeg(apoTxPars
            , (uint8_t)((uint8_t) 0x40 /* Kennung fuer Sequenzbotschaft */
                    /* berechne das obere Nibble des Headers der StartMessage 1->00, 2->10, 4->20, 8->30 */
                    + Bap_garu8HeaderBySegType[apoTxPars->poCanTxRamRow->eSelectedSegmentationChannel]
                                           + (uint8_t)(apoTxPars->poCanTxRamRow->flags.fSequenceNumber))
                                           , (uint16_t)u32SequenceMessageMemcpyLength
                                           , apoTxPars->poCanTxRamRow->u32BclTxBufferByteOffset);

    return;
    /*lint +esym(613,apoTxPars)*/
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_USES_SEGMENTATION */


/**
 *  Diese Funktion setzt Senden einzelner BCL Sendepuffer auf die UBS-Schnittstelle um.
 *
 *  Die Funktion wird vom BAP_BCL_LowLevlCanTxTask aufgerufen.
 *
 *  @param apoTxPars - Zeiger auf die Uebergabeparameterliste
 *
 *  @retval BAP_TRUE - Ein Eintragen in den CAN-Treiber wurde versucht
 *
 *  @retval BAP_FALSE - Der CAN-Treiber ist noch belegt (ConfirmationFlag) oder
 *  kein Segmentierungskanal frei.
 *
 *  @remarks:
 *  Fuer normale Uebertragung entspricht der Parameter poBclTxRamRow poCanTxRomRow->poBclTxRamRow.
 *  Werden jedoch Fehlerwerte gesendet, dann zeigt dieser Zeiger auf einen temporaeren Puffer.
 *
 *	Diese Funktion hat 6 ControlNestingLayers (max.4)
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
static BAP_IMPL_FAR bool_t
BAP_BCL_LowerLevelCanTxTask(BapTxParameters_cpot apoTxPars)
{
    DBGVAR bool_t bRetVal = BAP_FALSE;
#ifdef BAP_USES_SEGMENTATION
    DBGVAR uint16_t u16CopyLength = (uint16_t) 0u;
#endif /* #ifdef BAP_USES_SEGMENTATION */

    /*lint -esym(613,apoTxPars)*/
    // We do not pass pointer anymore, thanks to "NULL!=", the expression is now resolved to a boolean type
    BAP_ASSERT(NULL != apoTxPars);

    /* Abbrechen wenn CAN Tx Handle bereits in Verwendung */
    /* MISRA_2012_REQ_14.3 : The controlling expression is not invariant,
     * "BAP_CANUBS_IsReadyForTx" will return false if the call to this function is prohibited. */
    if(BAP_FALSE != BAP_CANUBS_IsReadyForTx(apoTxPars->poCanTxRomRow->canInterfaceChannel, apoTxPars->poCanTxRomRow->canMsgId))
    {
        bRetVal = BAP_TRUE;
#ifdef BAP_TASKTIME_LIMIT
        BAP_u32TaskTimeCounter += BAP_BUS_TX_TIME;
#endif /* #ifdef BAP_TASKTIME_LIMIT */

#ifndef BAP_USES_SEGMENTATION
        /* Neuen Sendeauftrag verarbeiten */
        if((bitfield_t) 1u == apoTxPars->poBclTxRamRow->flags.fTxRequestFlag)
        {
            BAP_BCL_CanCopyTransmitNonSeg(apoTxPars, (uint16_t) apoTxPars->poBclTxRamRow->oBufferWithLength.u32Length);
        }
#else  /* #ifndef BAP_USES_SEGMENTATION */
        /* Warte auf das Ende des Sendevorgangs */
        if((bitfield_t) 1u == apoTxPars->poBclTxRamRow->flags.fTxInProgressFlag)
        {
            BAP_BCL_CanSendSequenceMsg(apoTxPars);
        }

        /* Neuen Sendeauftrag verarbeiten */
        if((  (bitfield_t) 1u == apoTxPars->poBclTxRamRow->flags.fTxRequestFlag)
                && (  (bitfield_t) 0u == apoTxPars->poBclTxRamRow->flags.fTxInProgressFlag)
        )
        {
            if(BapSegType_Unsegmented != apoTxPars->poCanTxRomRow->eSegmentationType)
            {
                bRetVal = BAP_BCL_CanSendStartMsg(apoTxPars);
            }
            else
            {
                u16CopyLength = (uint16_t)apoTxPars->poBclTxRamRow->oBufferWithLength.u32Length;
                if(u16CopyLength > (BAP_GetTxPduSize(apoTxPars->poCanTxRomRow->canMsgId) - BAP_HEADER_BYTES_SEG_DATA) )
                {
                    u16CopyLength = BAP_GetTxPduSize(apoTxPars->poCanTxRomRow->canMsgId) - BAP_HEADER_BYTES_SEG_DATA;
                }

                BAP_BCL_CanCopyTransmitSeg(apoTxPars, (uint8_t) 0u, u16CopyLength, (uint32_t) 0u);
            }
        }
#endif /* #else .. #ifndef BAP_USES_SEGMENTATION */
    }
    else
    {
        bRetVal = BAP_FALSE;
    }
    return bRetVal;
    /*lint +esym(613,apoTxPars)*/
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


/**
 *  Diese Funktion setzt Senden einzelner BCL Sendepuffer auf die UBS-Schnittstelle um.
 *
 *  Die Funktion wird vom BAP_BCL_TaskSend aufgerufen.
 *
 *  @param apoTxPars - Zeiger auf die Uebergabeparameterliste
 *
 *  @returns BAP_TRUE wenn ein Tx-Request gefunden wurde, BAP_FALSE falls nicht
 *
 *  @remarks:
 *  Diese Funktion macht die Unterscheidung, ob nun Datenwerte oder Fehlerwerte gesendet werden sollen.
 *
 *  Diese Funktion aendert apoTxPars->poBclTxRamRow, falls ein Fehler versendet wird, und stellt nach Versand den urspuenglichen Wert wieder her.
 *
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
static BAP_IMPL_FAR bool_t
BAP_BCL_LowLevelCanTxTask(BapTxParameters_pot apoTxPars)
/*lint -esym(818,apoTxPars) */ /* Im ASG koennte apoTxPars const sein, im FSG jedoch nicht */
{
    DBGVAR bool_t bCanTxRequestFound = BAP_FALSE;

    /*  2017-03-15 Verbesserte Sende- und Empfangsperformance abspeichern des SendCnt auf der Function f�r jeweiligen TX-Channel*/
    DBGVAR uint8_t sendCountFct = apoTxPars->poCanTxRomRow->u8SendCnt ;
    DBGVAR bool_t bAbortLowerLevelCanTxTask = BAP_FALSE ;
    /* 2017-07-2017 FHA [SSWCCB-2391] Zum Zwischenspeichern des pBclTxRamRowTmp pointers bei einem Error-Request*/
    #ifdef BAP_FSG
    BapBclTxRamRow_pot pBclTxRamRowTmp;
    #endif

    /*lint -esym(613,apoTxPars) */
    BAP_ASSERT(NULL != apoTxPars);

#ifdef BAP_FSG
    /* Keine explizite Fallunterscheidung fuer das Kombigeraet, da im ASG TxError inaktiv */
    if ((BAP_FALSE != apoTxPars->poBclTxRamRow->flags.fTxErrorFlag))
    {
        /* Fehlerwert als Datenwert im eigenen RAM Puffer versenden */
        oBclTxRamRow.eErrorCode = apoTxPars->poBclTxRamRow->eErrorCode;
        (*oBclTxRamRow.oBufferWithLength.paru8Buffer)[0] = (uint8_t) oBclTxRamRow.eErrorCode;
        oBclTxRamRow.eOpCode = BapOp_PropError;
        oBclTxRamRow.oBufferWithLength.u32Length = (uint8_t)1;
        oBclTxRamRow.flags.fTxRequestFlag = BAP_TRUE;
#   ifdef BAP_USES_ACKNOWLEDGE
        oBclTxRamRow.flags.fTxRequestNeedsAckFlag = apoTxPars->poBclTxRamRow->flags.fTxErrorNeedsAckFlag;
#   endif  /* #ifdef BAP_USES_ACKNOWLEDGE */
#   ifdef BAP_USES_SEGMENTATION
        oBclTxRamRow.flags.fTxInProgressFlag = BAP_FALSE;
#   endif /* BAP_USES_SEGMENTATION */

        /* Bevor der poBclTxRamRow pointer ueberschrieben wird muss dieser, zum späteren Wiederherstellen, zwischengespeichert werden. */
        pBclTxRamRowTmp = apoTxPars->poBclTxRamRow;
        /* Folgendes Cast erzeugt Lint-Meldung, ist aber OK */
        apoTxPars->poBclTxRamRow = &oBclTxRamRow;
        /* Fehler senden */
        /* [SSWCCB-2151] Polyspace Meldung */
        bCanTxRequestFound = BAP_BCL_LowerLevelCanTxTask(apoTxPars);

        /* erfolgreich */
        if (BAP_FALSE == (bool_t)oBclTxRamRow.flags.fTxRequestFlag)
        {
            /* dann TxError-Request loeschen */
            apoTxPars->poCanTxRomRow->poBclTxRamRow->flags.fTxErrorFlag = BAP_FALSE;
#   ifdef BAP_USES_ACKNOWLEDGE
            apoTxPars->poCanTxRomRow->poBclTxRamRow->flags.fTxErrorNeedsAckFlag = BAP_FALSE;
#   endif  /* #ifdef BAP_USES_ACKNOWLEDGE */
            /* Wiederherstellen des urspruenglichen pointers damit ein zuvor angeforderter data request erfolgen kann. */
            apoTxPars->poBclTxRamRow = pBclTxRamRowTmp;
            pBclTxRamRowTmp->flags.fTxErrorFlag = BAP_FALSE;
#   ifdef BAP_USES_ACKNOWLEDGE
            pBclTxRamRowTmp->flags.fTxErrorNeedsAckFlag = BAP_FALSE;
#   endif  /* #ifdef BAP_USES_ACKNOWLEDGE */
            bCanTxRequestFound = BAP_TRUE;
        }
        else
        {
            /* Senden ist fehlgeschlagen. Wiederherstellen des urspruenglichen pointers zum erneuten Versenden */
            apoTxPars->poBclTxRamRow = pBclTxRamRowTmp;
        }
    }
    else
#endif /* BAP_FSG */
        if(   ( (bitfield_t) 1u ==  (apoTxPars->poBclTxRamRow->flags.fTxRequestFlag) )
#ifdef BAP_USES_SEGMENTATION
                || ((bitfield_t) 1u == (apoTxPars->poBclTxRamRow->flags.fTxInProgressFlag) )
#endif /* BAP_USES_SEGMENTATION */
        )
        {
            /* Daten senden */
            bCanTxRequestFound = BAP_BCL_LowerLevelCanTxTask(apoTxPars);


            /*  2017-03-22 nur bei segmentierten Nachrichten mehrfaches senden innerhalb BAP_TASK Zyklus ueber eine PDU */
#ifdef BAP_USES_SEGMENTATION
            /* SendCnt Schleife muss nicht ausgefuehrt werden wenn kein TX Request gefunden werden konnte */
            bAbortLowerLevelCanTxTask = ((bCanTxRequestFound == BAP_TRUE)  ? BAP_FALSE : BAP_TRUE);
            /* 2017-03-15 ODD  SWCCB2400 verbesserte Sende- und Empfangsperformance */
            while ( (0u < (--sendCountFct)) && (BAP_FALSE == bAbortLowerLevelCanTxTask))
            {
                if( (bitfield_t) 1u == (apoTxPars->poBclTxRamRow->flags.fTxInProgressFlag) ) /*TX Request  */
                {
                	/* MISRA_2012_REQ_14.3 : The controlling expression is not invariant,
                	 * it will be false if the CAN driver is busy, or if no segmentation canal is free */
                    bAbortLowerLevelCanTxTask = ((BAP_BCL_LowerLevelCanTxTask(apoTxPars) == BAP_TRUE) ? BAP_FALSE : BAP_TRUE);                    
                }else
                {
                    /* nichts mehr zu versenden */
                    bAbortLowerLevelCanTxTask =  BAP_TRUE ; 
                }
            }
#endif  /* BAP_USES_SEGMENTATION */
        }
        else
        {
            /* es gab nichts zu versenden */
        }
    /*lint -e438*/ /* MISRA_2012_REQ_2.2 : Last value of SendCountFct is never utilised because there is a pre decrement that update this value.
                    * Last value of bAbortLowerLevelCanTxTask is never utilised because it is followed by a condition statement.
                    * It is better to let the code like that instead of not initializing the values because functionally they do not create problems.*/
    return bCanTxRequestFound;
    /*lint +e438*/
    /*lint +esym(613,apoTxPars) */
}
/*lint +esym(818,apoTxPars) */
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


/**
 * Diese Funktion analysiert die Standard BAP-Header-Bytes und
 * speichert das Ergebnis in apoRxPars als lsgId, fctId und OpCode
 *
 * @param apoRxPars: Eingabe: pData, Ausgabe: lsgId, fctId, eOpCode
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
static BAP_IMPL_FAR void
BAP_CAN_AnalyzeHeaderBytes(const BapRxParameters_pot apoRxPars)
{
    /*lint -esym(613,apoRxPars)*/
    uint8_t u8TempByte1;
    uint8_t u8TempByte2;
    //In Referenz_bap_defines_Emb.h lsgId_t and fctId_t are defined as uint8_t or enum <255
    /* LsgId extrahieren */
    u8TempByte1 = (apoRxPars->aru8RxData[BAP_FIRST_HEADER_BYTE] & BAP_BITMASK_00001111) << BAP_LSGID_POS_IN_FIRSTBYTE;
    u8TempByte2 = (uint8_t)apoRxPars->aru8RxData[BAP_SECOND_HEADER_BYTE] >> BAP_LSGID_POS_IN_SECONDBYTE;
    /*lint -e9034*/ /* MISRA_2012_REQ_10.5 : uint8_t is cast to lsgId_t, fctId_t or BapOpCodes_et. These cast are
                     * required and no risk arise because it do not cause side effects since they are defined as enum and can fit uint8_t.*/
    /*lint -e9033*/ /* MISRA_2012_REQ_10.8 : logical operation is performed on two uint8_t operands which is cast to an enum.
                     * Bitwise & and bitwise | can be used between two uint8_t without loss of data.
                     * No risk arise because uint8 fit these enum. */
    apoRxPars->oPars.lsgId = (lsgId_t) (u8TempByte1 | u8TempByte2);
    /* FctId extrahieren */
    apoRxPars->oPars.fctId = (fctId_t) (apoRxPars->aru8RxData[BAP_SECOND_HEADER_BYTE] & BAP_BITMASK_00111111);
    /* OpCode extrahieren */
    apoRxPars->oPars.eOpCode = (BapOpCodes_et)((apoRxPars->aru8RxData[BAP_FIRST_HEADER_BYTE] & BAP_BITMASK_01110000) >> BAP_OPCODE_POS);
    /*lint +e9034*/
    /*lint +e9033*/
#ifdef BAP_USES_EXCLUSIVE_ADDRESS
    /* Bei neuer Adressierungsmethode LsgId aus CanMsgId ableiten */
    if( ((uint8_t)0 == u8TempByte1) && ((uint8_t)0 == u8TempByte2) ) /* falls lsgid == 0 und Erweiterung aktiv: */
    {
        uint8_t i;
        uint8_t numMsgId = BAP_CAN2LSGID_TABLE_ROWS;
        /* MISRA_2012_REQ_14.3 : The controlling expression is not invariant,
         * "i< numMsgId" can be false if no corresponding id if found between "BAP_CanRxMsgToLsgMappingTable[i].CanMessageId"  &  "apoRxPars->canId" */
        for ( i = (uint8_t) 0; i < numMsgId; i++)
        {
            if (BAP_CanRxMsgToLsgMappingTable[i].CanMessageId == apoRxPars->canId)
            {
                apoRxPars->oPars.lsgId = BAP_CanRxMsgToLsgMappingTable[i].LsgId;
                break;
            }
        }
    }

    return;
    /*lint +esym(613,apoRxPars)*/
#endif /*BAP_USES_EXCLUSIVE_ADDRESS*/
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


/**
 * Diese Funktion verwirft die empfangenen Daten. Sie wird aufgerufen,
 * falls segmentierte Daten empfangen werden, aber keine Segmentierung
 * unterstuetzt wird.
 *
 * @param apoRxPars: Parameter wird nicht genutzt.
 *
 * @remarks: Schnittstelle entspricht RxHandler_t
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
static BAP_IMPL_FAR void
BAP_CAN_RxNothing(const BapRxParameters_pot apoRxPars)
{
    /* Nutzloser Code, damit die Prueftools Ruhe geben */
    (void) apoRxPars;
    return;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


/**
 * Diese Funktion verarbeitet unsegmentierte, empfangene Daten.
 *
 * @param apoRxPars: Enthaelt alle Eingangsparameter. Siehe Beschreibung des Datentyps.
 *
 * @remarks: Schnittstelle entspricht RxHandler_t
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
static BAP_IMPL_FAR void
BAP_CAN_RxUnsegmented(const BapRxParameters_pot apoRxPars)
{
    BapCanRxRomRow_pot  poCanRxRomRow;
    BapInternalParameters_pot poPars;
    DBGVAR uint16_t u16Length;
    bool_t bLengthCheck;

    /*lint -esym(613,apoRxPars) */
    BAP_ASSERT(NULL != apoRxPars);

    poCanRxRomRow = apoRxPars->poCanRxRomRow;

#ifdef BAP_RUNTIME_TEST
    BAP_RUNTIME_TEST_INDINT8_START();
#endif /* BAP_RUNTIME_TEST */

    poPars = &apoRxPars->oPars;
    /* hier gibt es ein MISRA-2004 Rule 1.2, aber ist ok, wegen verlorende const/volatile bei cast*/
    poPars->pData =  &(apoRxPars->aru8RxData[BAP_HEADER_BYTES_NONSEG]); /*lint !e960*/
    u16Length = apoRxPars->u16MsgLength - (uint16_t)BAP_HEADER_BYTES_NONSEG;

#ifdef BAP_ASG
    /* Keine explizite Fallunterscheidung fuer das Kombigeraet, da im FSG kein PropError in Rx Richtung */
    /* Speichere Fehler in speziellem Puffer */
    if ( (BapOp_PropError == poPars->eOpCode)
#   if defined(BAP_ASG) && defined(BAP_FSG)
            && (BapSG_ASG == poPars->poLsgRomRow->eSGType)
#   endif /* #if defined(BAP_ASG) && defined(BAP_FSG) */
    )
    {
        bLengthCheck = (u16Length>=(uint16_t)1)? BAP_TRUE :  BAP_FALSE;
        if ( (BAP_TRUE == bLengthCheck)
#   ifdef BAP_ASG
                /* Im WaitForConfig-Zustand keine Remote-Fehler annehmen */
                && (BapLayerLsgStat_Running == poPars->poLsgRomRow->poLsgRamRow->eLsgStatus)
#   endif /* #ifdef BAP_ASG */
        )
        {
            /*lint -e9034*/ /* MISRA_2012_REQ_10.3 : PC-Lint 9.00L throws a warning due to Tool bug. Hence, this warning has been deactivated.
                             * Documented with a mail from the Lint team in the SSWCCB-2522_BAP-Entwicklung auf MISRA2012 umstellen folder
                             * No risk arise because the uint8 fit in enum.  */
            BAP_BCL_ErrorIndication(poPars->lsgId, poPars->fctId, (BapError_et) *poPars->pData);
            /*lint +e9034*/
#   ifdef BAP_TASKTIME_LIMIT
            BAP_u32TaskTimeCounter = BAP_u32TaskTimeCounter + BAP_IND_RX_TIME + (uint16_t)sizeof(BapError_et);
#   endif /* #ifdef BAP_TASKTIME_LIMIT */
        }
    }
    else
#endif /* #ifdef BAP_ASG */
    {
        DBGVAR uint16_t u16CopyLength;
        DBGVAR uint16_t u16RxPDUSize = BAP_GetRxPduSize(poCanRxRomRow->canMsgId);
        poPars->u32Length = poCanRxRomRow->u32Size;

        /* berechnung der Nutzdatenlaenge */
        u16CopyLength = (u16RxPDUSize-(uint16_t)BAP_HEADER_BYTES_NONSEG);  /* Initialisiere als Max-PDUSize-Header */
        if(poPars->u32Length < u16CopyLength)   /* Korregiere, falls Datenlaener kleiner als PDU_Size */
        {
            u16CopyLength = (uint16_t) poPars->u32Length;
        }

        bLengthCheck  /* Datenlose Requests durchlassen (BapOp_PropGet, BapOp_ArrGet, BapOp_CacheGetAll, BapOp_MethAbort */
        = ((u16CopyLength<=u16Length) || (BapOp_PropGet == poPars->eOpCode))? BAP_TRUE :  BAP_FALSE;

        if (BAP_FALSE != bLengthCheck)
        {
            /* Falls FixedByteSequence groesser als die Datenmenge im CAN-Puffer, dann
               kopiere Daten um, damit die Laenge mit 0 Bytes aufgefuellt ist */
            if ((poPars->u32Length> ((uint32_t)u16RxPDUSize-(uint32_t)BAP_HEADER_BYTES_NONSEG))
                    && ( (BapDt_FixedByteSequence == poPars->poFctRomRow->eRxDataType)
#if defined(BAP_ASG) && defined(BAP_USES_SEGMENTATION)
                            || (Bap_bIsFctListSym == BAP_FALSE) /* Sonderfall in BAP v.1.6.2 */
#endif /* defined(BAP_ASG) && defined(BAP_USES_SEGMENTATION)*/
                    )    )
            {
                poPars->pData = *(poCanRxRomRow->poBclRxRamRow->oBufferWithLength.paru8Buffer);
                /*lint -e9087*/ /* MISRA_2012_REQ_11.3 : 1st and 2nd arguments of MEMCPY are of types (const char*) and (uint8_t*).
                                 * They are implicitly cast to (void*). As long as the char is 8 bits long, there will be no problem.*/
                /*lint -e9005*/ /* MISRA_2012_REQ_11.8 : cast of the 1st argument of MEMCPY which is a const pointer to an (unsigned char),
                                 * not a pointer to a (const unsigned char). Hence the values in the array can be modified.*/
                /* hier gibt es ein MISRA-2004 Rule 1.2, aber ist ok, wegen verlorende const/volatile bei cast*/
                MEMCPY(poPars->pData, &apoRxPars->aru8RxData[BAP_HEADER_BYTES_NONSEG], u16CopyLength); /*lint !e960*/
                /*lint +e9005*/
                /*lint +e9087*/
            }

            BAP_BCL_DataReceived(poPars);
#ifdef BAP_TASKTIME_LIMIT
            BAP_u32TaskTimeCounter = BAP_u32TaskTimeCounter + (uint32_t) BAP_IND_RX_TIME + poPars->u32Length;
#endif /* #ifdef BAP_TASKTIME_LIMIT */
        }
    }

    if (BAP_FALSE == bLengthCheck)
    {
        BAP_BCL_ErrorIndication(poPars->lsgId, poPars->fctId, BapErr_BadDataLength);
        BAP_DBG_BadDataLengthError( poPars->lsgId );
    }

#ifdef BAP_TASKTIME_LIMIT
    poPars->poLsgRomRow->poLsgRamRow->fState.fRxFlag = BAP_TRUE;
#endif /* #ifdef BAP_TASKTIME_LIMIT */

#ifdef BAP_RUNTIME_TEST
    BAP_RUNTIME_TEST_INDINT8_STOP();
#endif /* BAP_RUNTIME_TEST */

    return;
    /*lint +esym(613,apoRxPars) */
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


#ifdef BAP_USES_SEGMENTATION
/**
 * Diese Funktion prueft, ob nach dem Empfang einer segmentierten Nachricht
 * diese vollstaendig empfangen wurde und setzt entsprechende Notifizierungsflags.
 *
 * @param apoRxPars: Enthaelt alle Eingangsparameter. Siehe Beschreibung des Datentyps.
 *
 * @remarks: Schnittstelle entspricht RxHandler_t
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
static BAP_IMPL_FAR void
BAP_CAN_RxSegCompleteCheck(const BapRxParameters_cpot apoRxPars)
{
    /*lint -esym(613,apoRxPars) */
    const BapCanRxRomRow_pot poCanRxRomRow = apoRxPars->poCanRxRomRow;
    BapBclRxRamRow_pot poBclRxRamRow = poCanRxRomRow->poBclRxRamRow;
    DBGVAR lsgId_t lsgId = poCanRxRomRow->lsgId;
    BapLsgRomRow_pot poLsgRomRow = BAP_GetLsgRomRow(lsgId);
    uint16_t u16IntertelegramTime;
    DBGVAR uint8_t u8SegChannel;
    BapCanRxDynSegChannels_pot  poCanRxDynSegChannel;

    if (NULL == (poCanRxRomRow->poCanRxRamRow))
    {
        /* tritt nur dann auf, wenn Sequenzbotschaften einer nicht konfigurierten Fct-Id */
        /* empfangen wurden. Wird aber zum Retriggern benoetigt */
    }
    else if ( (poCanRxRomRow->poCanRxRamRow->u32BclRxBufferByteOffset >= poBclRxRamRow->oBufferWithLength.u32Length)
            && ( (bitfield_t) 1u == poBclRxRamRow->flags.fRxInProgressFlag)
    )
    {
        poBclRxRamRow->flags.fRxInProgressFlag = BAP_FALSE;
        poBclRxRamRow->flags.fRxCompleteFlag = BAP_TRUE;

#   ifdef BAP_TASKTIME_LIMIT
        if (NULL != poLsgRomRow)
        {
            poLsgRomRow->poLsgRamRow->fState.fRxFlag = BAP_TRUE;
        }
#   endif /* #ifdef BAP_TASKTIME_LIMIT */

        /* InterTelegramTimer auf 0 setzen */
        *(poCanRxRomRow->pu16InterTelegramTimer) = (uint16_t)0;

        /* eSegmentationType enthaelt folgende Werte: 1, 2, 4, 8 */
        u8SegChannel = Bap_garu8ChannelBySegType[apoRxPars->eSegmentationType];

        /* Suche nach dem Can-Handle, ob es einen Eintrag fuer den gewaehlten Segmentierungskanal gibt */
        poCanRxDynSegChannel = BAP_BCL_GetRxDynSegChannel(apoRxPars->canId);

        /* gib den Empfangskanal wieder frei */
        if (NULL != poCanRxDynSegChannel)
        {
            poCanRxDynSegChannel->arpoRxDynSegChannels[u8SegChannel] = NULL;
        }

        BAP_DBG_RxSegMsgCompleteEvent(lsgId);
    }
#   ifdef BAP_ASG
    /* Keine explizite Fallunterscheidung fuer das Kombigeraet, da im FSG RxError inaktiv */
    else if ( ((bitfield_t) 1u == poBclRxRamRow->flags.fRxErrorFlag)
            && ( (bitfield_t) 0u == poBclRxRamRow->flags.fRxInProgressFlag) )
    {

#       ifdef BAP_TASKTIME_LIMIT
        if (NULL != poLsgRomRow)
        {
            poLsgRomRow->poLsgRamRow->fState.fRxFlag = BAP_TRUE;
        }
#       endif /* #ifdef BAP_TASKTIME_LIMIT */

        /* InterTelegramTimer auf 0 setzen */
        *(poCanRxRomRow->pu16InterTelegramTimer) = (uint16_t)0;

        BAP_DBG_RxSegMsgCompleteEvent(lsgId);
    }
#   endif /* #ifdef BAP_ASG */
    else if ((bitfield_t) 1u == poBclRxRamRow->flags.fRxInProgressFlag)
    {
        /* InterTelegramTimer neu starten (retriggern) */
        u16IntertelegramTime = poCanRxRomRow->u16IntertelegramTime;
        *(poCanRxRomRow->pu16InterTelegramTimer) = u16IntertelegramTime;
        BAP_bInterTelegramTimerRunning = BAP_TRUE;
    }
    else
    {
        /* Misra Rule 60 */
    }
    return;
    /*lint -esym(613,apoRxPars) */
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_USES_SEGMENTATION */

#ifdef BAP_USES_SEGMENTATION
/* Pruefe, ob Laenge i.O. */
/* 4094 Laenge in altem Format nicht erlaubt */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
static BAP_IMPL_FAR bool_t
BAP_BCL_CheckSegStart(const BapRxParameters_pot apoRxPars, uint16_t u16PduSize, BapOpCodes_et eOpCode
#   ifdef BAP_ASG
        , const BapInternalParameters_pot poPars
#   endif /* BAP_ASG */
)
{
    /*lint -esym(818,poPars) */
    /*lint -esym(818,apoRxPars) */
    bool_t bRetVal = BAP_FALSE;

    /* If segmented Length is greater (old format max length) AND PDU_Size is 8 (which means old format) */
    if( (apoRxPars->u32SegmentationLength > BAP_MAX_BYTE_SEQUENCE_LENGTH )
            && (u16PduSize == BAP_MAX_PDU_SIZE_OLD_FORMAT))
    {
        bRetVal = BAP_TRUE;
    }
    else if (
            ( (apoRxPars->u32SegmentationLength > apoRxPars->poCanRxRomRow->u32Size)

                    /* Bei Errors muss die Laenge 1 betragen */
                    && ((apoRxPars->u32SegmentationLength != (uint16_t)1) || (BapOp_PropError != eOpCode))

                    /* Beim ASG darf bei kompatibler Erweiterung die Laenge der StatusAll Nachricht */
                    /* groesser sein wie konfiguriert */
#   ifdef BAP_ASG
                    &&  (BAP_FCTID_GETALL !=(fctId_t)poPars->fctId)
                    /*
        #if defined(BAP_ASG) && defined(BAP_FSG)
               || (poPars->poLsgRomRow->eSGType != BapSG_ASG)
        #endif
                     */
#   endif  /* #ifdef BAP_ASG */
            )
    )
    {
        bRetVal = BAP_TRUE;
    }
    else
    {
        /* Nicht zu tun, Ergebnis bleibt BAP_FALSE, wie vorbelegt */
    }

    return bRetVal;
}
/*lint +esym(818,apoRxPars) */
/*lint +esym(818,poPars) */
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_USES_SEGMENTATION */

#ifdef BAP_USES_SEGMENTATION
/**
 * Diese Funktion verarbeitet eine Startbotschaft einer empfangenen, segmentierten Nachricht.
 * Alte, laufende Uebertragungen werden ohne Fehlermeldung abgebrochen.
 *
 * @param apoRxPars: Enthaelt alle Eingangsparameter. Siehe Beschreibung des Datentyps.
 *
 * @remarks: Schnittstelle entspricht RxHandler_t
 *
 * Diese Funktion hat 53 Statements (max.50)
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_STATIC BAP_IMPL_FAR void
BAP_CAN_RxSegmentedStart(const BapRxParameters_pot apoRxPars)
{
    /*lint -esym(613,apoRxPars) */
    BapCanRxRomRow_pot  const poCanRxRomRow = apoRxPars->poCanRxRomRow;
    BapBclRxRamRow_pot poBclRxRamRow = poCanRxRomRow->poBclRxRamRow;
    BapInternalParameters_pot poPars;
    DBGVAR BapOpCodes_et eOpCode;
    DBGVAR uint8_t  u8HeaderSize; /* Laenge der Header Bytes */
    DBGVAR uint16_t u16PduSize;  /* PDU-Groesse von einer Botschaft  */
    DBGVAR uint16_t u16MaxDataSize; /* max. Datalaenge in einer Botschaft */
    DBGVAR uint16_t u16CpyDataSize; /* zu kopierende Datalaenge in einer Botschaft */
    DBGVAR bool_t bIllegalFormat;
    poPars = &apoRxPars->oPars;

    /* OpCode, welcher empfangen wurde, retten */
    eOpCode = poPars->eOpCode;
    poPars->eOpCode = BapOp_StartMessage;

    u16PduSize = BAP_GetRxPduSize(apoRxPars->poCanRxRomRow->canMsgId);
    bIllegalFormat = BAP_BCL_CheckSegStart(apoRxPars, u16PduSize, eOpCode
#   ifdef BAP_ASG
            , poPars
#   endif /* BAP_ASG */
    );

    if (BAP_TRUE == bIllegalFormat)
    {
        /* Falls segmentiertes Format nicht in Ordnung */
        if ( BAP_FALSE == (bool_t)poBclRxRamRow->flags.fRxErrorFlag )   /* Remote-Fehler haben Prioritaet vor internem */
        {
            poBclRxRamRow->flags.fRxErrorFlag = BAP_TRUE;
            poBclRxRamRow->eErrorCode = BapErr_OversizeSegmentation;
        }

        BAP_DBG_MsgOversizeError(poPars->lsgId);
    }
    else
    {
        /* Alte Segmentierung abbrechen */
        poBclRxRamRow->flags.fRxInProgressFlag = BAP_FALSE;

#   ifdef BAP_ASG
        /* Speichere Fehler in speziellem Puffer */
        if ( (BapOp_PropError == eOpCode)
                /* Keine explizite Fallunterscheidung fuer das Kombigeraet, da im FSG Rx ErrorOpcode verboten */
                /*
        #if defined(BAP_ASG) && defined(BAP_FSG)
                      && (BapSG_ASG == poPars->poLsgRomRow->eSGType)
        #endif
                 */
        )
        {
            /* Im WaitForConfig-Zustand keine Remote-Fehler annehmen */
            if (BapLayerLsgStat_Running == poPars->poLsgRomRow->poLsgRamRow->eLsgStatus)
            {
                poBclRxRamRow->flags.fRxErrorFlag = BAP_TRUE;

                if ( (apoRxPars->u16MsgLength<(uint16_t)5u) || (apoRxPars->u32SegmentationLength!=(uint16_t)1) )
                {
                    BAP_DBG_BadDataLengthError( poPars->lsgId );
                    poBclRxRamRow->eErrorCode = BapErr_BadDataLength;
                }
                else
                {
                    /*lint -e9034*/ /* MISRA_2012_REQ_10.3 : PC-Lint 9.00L throws a warning due to Tool bug. Hence, this warning has been deactivated.
                                     * Documented with a mail from the Lint team in the SSWCCB-2522_BAP-Entwicklung auf MISRA2012 umstellen folder
                                     * no risk arise because the uint8_t fit in enum */
                    poBclRxRamRow->eErrorCode = (BapError_et) apoRxPars->aru8RxData[2];
                    /*lint +e9034*/
                }
            }
        }
        else
#   endif /* #ifdef BAP_ASG */
        {
            BapCanRxSegmentationRamRow_pot poCanRxRamRow = poCanRxRomRow->poCanRxRamRow;
            /* Berechne aus der Bitkodierung des Segmentationstyps den Segmentierungskanal:
               Konvertiere 1->0, 2->1, 4->2, 8->3, entspricht lg2 */
            DBGVAR uint8_t u8SegChannel = Bap_garu8ChannelBySegType[apoRxPars->eSegmentationType];

            poCanRxRamRow->flags.fSequenceNumber = (uint8_t)0;
            poBclRxRamRow->eOpCode = eOpCode;

#   ifdef BAP_ASG
            /* Spezialbehandlung wegen StatusAll bei kompatibler Erweiterung */

            /* MISRA_2012_REQ_14.3 : "(u16PduSize == (uint8_t) 8u)" is not invariant,
                     * the PDU size can be different from 8 */
            if ( (apoRxPars->u32SegmentationLength > poCanRxRomRow->u32Size)
                    || ( (apoRxPars->u32SegmentationLength > BAP_MAX_BYTE_SEQUENCE_LENGTH )  && (u16PduSize == BAP_MAX_PDU_SIZE_OLD_FORMAT) )
            )
            {
                apoRxPars->u32SegmentationLength = poCanRxRomRow->u32Size;
                /* dennoch den Fehler anzeigen */
                BAP_DBG_MsgOversizeError(poPars->lsgId);
            }
#   endif /* #ifdef BAP_ASG */

            poBclRxRamRow->oBufferWithLength.u32Length = apoRxPars->u32SegmentationLength;

            /* Berechnung der Datalaenge */

            if(u16PduSize > BAP_MAX_PDU_SIZE_OLD_FORMAT)
            {
                u8HeaderSize = BAP_HEADER_BYTES_SEG_NEW;  /* 8 Byte Header in neuem Format */
                u16MaxDataSize = u16PduSize - u8HeaderSize;
            }else{
                u8HeaderSize = BAP_HEADER_BYTES_SEG_OLD;  /* Default PDU_Size ist 8, 4 Byte Header in altem Format. */
                u16MaxDataSize = (uint16_t)8u - u8HeaderSize;  /* Default PDU_Size ist 8 */
            }

            /* Offset als zu kopierende Laenge verwenden, muesste sonst nach memcpy gesetzt werden */
            poCanRxRamRow->u32BclRxBufferByteOffset
            =  (apoRxPars->u32SegmentationLength < u16MaxDataSize) ? apoRxPars->u32SegmentationLength : u16MaxDataSize;

            u16CpyDataSize= apoRxPars->u16MsgLength - (uint16_t)u8HeaderSize;
            if (poCanRxRamRow->u32BclRxBufferByteOffset <= u16CpyDataSize ) /* 4 Bytes Segmentierungs-Header */
            {
                /* Kopiere die Daten Byte 4 .. max. zu Byte 8 aus dem CAN-Treiber in den BCL-Puffer */
                /* hier gibt es ein MISRA-2004 Rule 1.2, aber ist ok, wegen verlorende const/volatile bei cast*/
                /*lint -e960*/
                /*lint -e9087*/ /* MISRA_2012_REQ_11.3 : 1st and 2nd arguments of MEMCPY are of types (uint8_t*).
                                 * They are implicitly cast to (void*). The memory is packed because it is uint8_t so there should be no problem to copy.*/
                MEMCPY( poBclRxRamRow->oBufferWithLength.paru8Buffer
                        , &apoRxPars->aru8RxData[2]   /* weist noch auf Byte 2 des Puffers wg. Optimierung. Dies ist so gewollt. */
                        , poCanRxRamRow->u32BclRxBufferByteOffset);
                /*lint +e9087*/
                /*lint +e960*/

                /* Merke den aktiven Segmentierungskanal fuer schnelles Einsortieren der Sequenzbotschaften */
                poCanRxRomRow->poRxDynSegChannels->arpoRxDynSegChannels[u8SegChannel] = poCanRxRomRow;

                poBclRxRamRow->flags.fRxInProgressFlag = BAP_TRUE;
            }
            else
            {
#   ifdef BAP_ASG
                /* Keine explizite Fallunterscheidung fuer das Kombigeraet, da im FSG RxError inaktiv */
                if ( BAP_FALSE == (bool_t)poBclRxRamRow->flags.fRxErrorFlag )   /* Remote-Fehler haben Prioritaet vor internem */
#   endif /* BAP_ASG */
                {
                    BAP_DBG_BadDataLengthError( poPars->lsgId );
                    poBclRxRamRow->eErrorCode = BapErr_BadDataLength;
                    poBclRxRamRow->flags.fRxErrorFlag = BAP_TRUE;
                }
            }
        }
        BAP_DBG_RxStartMsgEvent(poPars->lsgId);
        /* BPL ueber den Empfang einer Startbotschaft informieren zwecks Retry-Mechanismus */
        BAP_BCL_DataReceived(poPars);
    }
    return;
    /*lint +esym(613,apoRxPars) */
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_USES_SEGMENTATION */


#ifdef BAP_USES_SEGMENTATION
/**
 * Diese Funktion verarbeitet eine Sequenzbotschaft einer empfangenen, segmentierten Nachricht.
 * Hierbei werden Intertelegrammtimer, Sequenzfehler usw. ueberprueft.
 *
 * @param apoRxPars: Enthaelt alle Eingangsparameter. Siehe Beschreibung des Datentyps.
 *
 * @remarks: Schnittstelle entspricht RxHandler_t
 *
 * Diese Funktion hat 6 ControlNestingLayers (max.4)
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_STATIC BAP_IMPL_FAR void
BAP_CAN_RxSegmentedSequence(const BapRxParameters_cpot apoRxPars)
{
    /*lint -esym(613,apoRxPars) */
    BapCanRxRomRow_pot  const poCanRxRomRow = apoRxPars->poCanRxRomRow;
    BapBclRxRamRow_pot poBclRxRamRow = poCanRxRomRow->poBclRxRamRow;
    BapCanRxSegmentationRamRow_pot poCanRxRamRow = poCanRxRomRow->poCanRxRamRow;

    if( (apoRxPars->canId == poCanRxRomRow->canMsgId)
            &&  (poCanRxRomRow->canInterfaceChannel == apoRxPars->canInterfaceChannel) )
    {
        DBGVAR uint32_t * const pu32BclRxBufferByteOffset = &poCanRxRamRow->u32BclRxBufferByteOffset;

        /* Sequenzbotschaft ohne Startbotschaft? */
        /* IntertelegrammTimer abgelaufen? */
        if ( (BAP_FALSE == (bool_t)poBclRxRamRow->flags.fRxInProgressFlag)
                || ((uint16_t)0u == *(poCanRxRomRow->pu16InterTelegramTimer)) )
        {
            poBclRxRamRow->flags.fRxInProgressFlag = BAP_FALSE;

            /* In BAP 1.4 wird kein BapErr_IllegalSequence mehr an die Applikation gemeldet,
               sondern die Nachricht stillschweigend ignoriert */
        }
        /* Sequenznummerfehler aufgetreten? */
        else if( (uint8_t) ((apoRxPars->aru8RxData[BAP_FIRST_HEADER_BYTE]) & BAP_BITMASK_00001111)
                != (uint8_t) (poCanRxRamRow->flags.fSequenceNumber))
        {
#   ifdef BAP_ASG
            /* Keine explizite Fallunterscheidung fuer das Kombigeraet, da im FSG RxError inaktiv */
            if ( BAP_FALSE == (bool_t)poBclRxRamRow->flags.fRxErrorFlag )   /* Remote-Fehler haben Prioritaet vor internem */
#   endif /* BAP_ASG */
            {
                poBclRxRamRow->flags.fRxErrorFlag = BAP_TRUE;
                poBclRxRamRow->eErrorCode = BapErr_SequenceNumber;
            }

            BAP_DBG_SequenceError(poCanRxRomRow->lsgId);

            /* InterTelegramTimer auf 0 setzen */
            *(poCanRxRomRow->pu16InterTelegramTimer) = (uint16_t)0;

            poBclRxRamRow->flags.fRxInProgressFlag = BAP_FALSE;
        }
        else
        {
            /* Extrahiere Folgedaten des Datenelements aus dem CAN
               Message Object fuer die Sequenzebotschaft und verwalte
               CanRxRam Daten */
            DBGVAR uint32_t u32SequenceMessageMemcpyLength = (uint32_t)(poBclRxRamRow->oBufferWithLength.u32Length
                    - *pu32BclRxBufferByteOffset);
            DBGVAR uint16_t u16MaxDataSize;  /* max. Datalaenge in einer Botschaft. */

            u16MaxDataSize = BAP_GetRxPduSize(apoRxPars->poCanRxRomRow->canMsgId) - (uint16_t)1; /* 1 Byte Sequenz-Header */
            if( u32SequenceMessageMemcpyLength > (uint32_t)u16MaxDataSize)
            {
                u32SequenceMessageMemcpyLength = (uint32_t)u16MaxDataSize;
            }


            if ( u32SequenceMessageMemcpyLength <= ((uint32_t)apoRxPars->u16MsgLength - (uint32_t) 1 )/* 1 Byte Header fuer Sequenzbotschaft */) 
            {
                /* hier gibt es ein MISRA-2004 Rule 1.2, aber ist ok, wegen verlorende const/volatile bei cast*/
                /*lint -e960*/
                /*lint -e9087*/ /* MISRA_2012_REQ_11.3 : 1st and 2nd arguments of MEMCPY are of types (uint8_t*).
                                 * They are implicitly cast to (void*). The memory is packed because it is uint8_t so there should be no problem to copy.*/
                MEMCPY( &(*poBclRxRamRow->oBufferWithLength.paru8Buffer)[*pu32BclRxBufferByteOffset]
                       , &apoRxPars->aru8RxData[1]
                       , u32SequenceMessageMemcpyLength);
                /*lint +e9087*/
                /*lint +e960*/

                *pu32BclRxBufferByteOffset = (uint32_t)(*pu32BclRxBufferByteOffset + u32SequenceMessageMemcpyLength);
            }
            else
            {
#   ifdef BAP_ASG
                /* Keine explizite Fallunterscheidung fuer das Kombigeraet, da im FSG RxError inaktiv */
                if ( BAP_FALSE == (bool_t)poBclRxRamRow->flags.fRxErrorFlag )   /* Remote-Fehler haben Prioritaet vor internem */
#   endif /* BAP_ASG */
                {
                    BAP_DBG_BadDataLengthError( apoRxPars->oPars.lsgId );
                    poBclRxRamRow->eErrorCode = BapErr_BadDataLength;
                    poBclRxRamRow->flags.fRxErrorFlag = BAP_TRUE;
                }

                /* InterTelegramTimer auf 0 setzen */
                *(poCanRxRomRow->pu16InterTelegramTimer) = (uint16_t)0;

                poBclRxRamRow->flags.fRxInProgressFlag = BAP_FALSE;
            }

            /* Sequenznummer hochzaehlen (4 Bits) */
            poCanRxRamRow->flags.fSequenceNumber = (poCanRxRamRow->flags.fSequenceNumber + 1u) & BAP_BITMASK_00001111;
        }
    }
    return;
    /*lint +esym(613,apoRxPars) */
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_USES_SEGMENTATION */


#ifdef BAP_USES_SEGMENTATION
/**
 *  Hole die zur CanId gehoerenden dynamischen Segmentierungskanaele
 *
 *  @param aCanId can id zu der die Segmentierungskanaele gesucht werden sollen
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
static BapCanRxDynSegChannels_pot  BAP_IMPL_FAR
BAP_BCL_GetRxDynSegChannel(BapCanMsgId_t aCanId)
{
    DBGVAR uint16_t u16CanHandleCounter;
    BapCanRxDynSegChannels_pot  poCanRxDynSegChannel = NULL;

    /* Suche nach dem Can-Handle, ob es einen Eintrag fuer den gewaehlten Segmentierungskanal gibt */
    for ( u16CanHandleCounter = (uint16_t)0; (u16CanHandleCounter<BAP_CAN_RX_SEGMENTATION_CHANNELS) && (NULL == poCanRxDynSegChannel); u16CanHandleCounter++)
    {
        /* Falls CAN-Id gefunden, pruefe ob Segmentierungskanal vergeben */
        if ( BAP_CanRxMsgIdToSegChannelMappingTable[u16CanHandleCounter] == aCanId )
        {
            poCanRxDynSegChannel = &BAP_CanRxSegmentationChannels[u16CanHandleCounter];
        }
    }
    return poCanRxDynSegChannel;
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* BAP_USES_SEGMENTATION */

#ifdef BAP_USES_SEGMENTATION
/**
 *  Diese Funktion verarbeitet eine Sequenzbotschaft optimiert.
 *
 *  @param apoRxPars - modifiziert folgende Elemente
 *  apoRxPars->poLsgRomRow zeigt nach dem Funktionsaufruf auf das Lsg, welchem die Nachricht zugeordnet wurde.
 *  apoRxPars->poCanRxRomRow zeigt nach dem Funktionsaufruf auf die Funktion, welcher die Nachricht zugeordnet wurde.
 *
 *  @returns
 *  BAP_TRUE, falls die Nachricht verarbeitet wurde
 *  BAP_FALSE, falls die Nachricht verworfen wurde
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
static BAP_IMPL_FAR bool_t
BAP_BCL_CanReceiveSequence(const BapRxParameters_pot apoRxPars)
{
    /*lint -esym(613,apoRxPars) */ /* wird nur durch BAP_BCL_CanReceiveData aufgerufen, wo benutzte Pars gesetzt werden */
    /* Optimierung fuer Sequenzbotschaften */
    DBGVAR bool_t bDataProcessed = BAP_FALSE;

    /* eSegmentationType enthaelt folgende Werte: 1, 2, 4, 8 */
    DBGVAR uint8_t u8SegChannel = Bap_garu8ChannelBySegType[apoRxPars->eSegmentationType];

    /* Suche nach dem Can-Handle, ob es einen Eintrag fuer den gewaehlten Segmentierungskanal gibt */
    BapCanRxDynSegChannels_pot  poCanRxDynSegChannel = BAP_BCL_GetRxDynSegChannel(apoRxPars->canId);

    /* Falls CAN-Id gefunden, pruefe ob Segmentierungskanal vergeben */
    if (NULL != poCanRxDynSegChannel)
    {
        apoRxPars->oPars.poLsgRomRow = NULL;
        apoRxPars->poCanRxRomRow = poCanRxDynSegChannel->arpoRxDynSegChannels[u8SegChannel];
        if (apoRxPars->poCanRxRomRow != NULL)
        {
            apoRxPars->oPars.poLsgRomRow = BAP_GetLsgRomRow(apoRxPars->poCanRxRomRow->lsgId);
        }

        if ( (NULL != apoRxPars->oPars.poLsgRomRow)
                && ( (apoRxPars->oPars.poLsgRomRow->poLsgRamRow->eLsgStatus == BapLayerLsgStat_Running)
#   ifdef BAP_ASG  /* Im Kombigeraet gibt es WaitForConfig nicht fuer FSGs */
                        || (apoRxPars->oPars.poLsgRomRow->poLsgRamRow->eLsgStatus == BapLayerLsgStat_WaitForOrInvalidConfig)
                        /* keine Spezialbehandlung fuer kompatible erweiterte Funktionsliste noetig, da in diesem
           Fall BAP_CAN_RxSegmentedSequence die Eingabe ignoriert (Vergleich der Segmentierungskanaele) */
#   endif /* #ifdef BAP_ASG */
                )
        )
        {
            BAP_CAN_RxSegmentedSequence(apoRxPars);
            bDataProcessed = BAP_TRUE;
        }
    }
    /*lint +esym(613,apoRxPars) */
    return bDataProcessed;
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* #ifdef BAP_USES_SEGMENTATION */


/**
 *  Diese Funktion verarbeitet Startbotschaften und unsegmentierte Nachrichten.
 *
 *  @param apoRxPars enthaelt die Empfangsdaten, welche weiterverarbeitet werden.
 *  @param apfnRxHandler enthaelt die Verarbeitungsfunktion, welche aufgerufen werden soll.
 *
 *  @return Gibt zurueck, ob die Daten verarbeitet wurden
 *
 *  @remarks: Ist eine Hilfsfunktion fuer BAP_BCL_CanReceiveData. Enthaelt die Sonderbehandlung
 *  fuer die Verarbeitung von Startbotschaften nicht vorhandener Funktionen bei kompatibler
 *  Erweiterung.
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_STATIC BAP_IMPL_FAR bool_t
BAP_BCL_CanProcessData(BapRxParameters_pot apoRxPars, RxHandler_ft apfnRxHandler)
{
    DBGVAR bool_t bDataProcessed = BAP_FALSE;

    /*lint -esym(613, apoRxPars) */
    /*lint -esym(613, apfnRxHandler) */
    BAP_ASSERT(apoRxPars != NULL );
    BAP_ASSERT(apfnRxHandler != NULL );

    if ( NULL != apoRxPars->oPars.poFctRomRow )
    {
        BapBusIndirectionRxRomRow_pot poBusIndRx = NULL;
        DBGVAR uint8_t u8RxTableSize = apoRxPars->oPars.poFctRomRow->u8RxTableSize;
        DBGVAR uint8_t u8RxTableIdx;

        /* Suche unter den moeglichen CAN Rx Eintraegen nach dem Eintrag, bei dem canId usw. uebereinstimmen.
           Da i.d.R. nur 1-2 Rx konfiguriert werden, lohnt es sich nicht, die Schleife vorzeitig abzubrechen
         */
        for (u8RxTableIdx=(uint8_t)0; u8RxTableIdx<u8RxTableSize; u8RxTableIdx++)
        {
            poBusIndRx = &BAP_BusIndRxTable[apoRxPars->oPars.poFctRomRow->u16BusRxTableIndex + (uint16_t)u8RxTableIdx];
            if( (BapIft_Can == poBusIndRx->eInterfaceType)     /* Bus Interfacetyp muss gleich sein*/
                    && (apoRxPars->canId == poBusIndRx->poCanRx->canMsgId) /* CAN Message ID gleich */
                    && (apoRxPars->canInterfaceChannel == poBusIndRx->poCanRx->canInterfaceChannel)  /* Message Channel gleich */
            )
            {
                /* Segmentierungsart muss gleich
                 * ODER (BAP v.1.6.2) Sonderfall: Fuer Fctlist,
                 * ASG darf unsegmentierte Nachricht bearbeiten, selbst wenn Rx-Seite in ASG segmentierte ist.
                 * ASG(Segmentierte) -- FSG (Unsegmentierte)
                 */
                if (   (((uint8_t)poBusIndRx->poCanRx->eSegmentationType & (uint8_t)apoRxPars->eSegmentationTypeMask)
                        == (uint8_t)apoRxPars->eSegmentationType)
#if defined(BAP_ASG) && defined(BAP_USES_SEGMENTATION)  /* BAP v.1.6.2 */
                        ||(BAP_FALSE == Bap_bIsFctListSym)
#endif /* defined(BAP_ASG) && defined(BAP_USES_SEGMENTATION)*/
                )
                {
                    /* gefunden - jetzt kann die Zuweisung zur RxRomRow erfolgen */
                    apoRxPars->poCanRxRomRow = poBusIndRx->poCanRx;
                    /* Rufe abhaengig von der Nachricht den entsprechenden RxHandler auf */
                    apfnRxHandler(apoRxPars);
                    bDataProcessed = BAP_TRUE;
                }
            }
        }
    }
#if defined(BAP_ASG) && defined(BAP_USES_SEGMENTATION)
    else if ( (BapSegType_Unsegmented != apoRxPars->eSegmentationType )
#   if defined(BAP_ASG) && defined(BAP_USES_SEGMENTATION) && defined(BAP_FSG)
            && (BapSG_ASG == apoRxPars->oPars.poLsgRomRow->eSGType)
#   endif /* #if defined(BAP_ASG) && defined(BAP_USES_SEGMENTATION) && defined(BAP_FSG) */
    )
    {
        /* Spezialbehandlung fuer Funktionen bei kompatibler Erweiterung (Superset) */
        /* In diesem Fall wird bei Segmentierungsstart der dynamische Empfangskanal auf Fct-Id 2 */
        /* (BAPConfig) gesetzt, welcher immer unsegmentiert ist. Dies ist noetig, damit beim Empfang */
        /* der Sequenzbotschaften diese einem logischen Steuergeraet zugeordnet werden koennen. */
        /* Dies ist noetig, damit diese Sequenzbotschaften den Heartbeat-Timer retriggern koennen. */

        /* Berechne aus der Bitkodierung des Segmentationstyps den Segmentierungskanal:
           Konvertiere 1->0, 2->1, 4->2, 8->3, entspricht lg2 */
        DBGVAR uint8_t u8SegChannel = Bap_garu8ChannelBySegType[apoRxPars->eSegmentationType];

        BapCanRxDynSegChannels_pot poRxDynSegChannels;

        poRxDynSegChannels = BAP_BCL_GetRxDynSegChannel(apoRxPars->canId);

        if (NULL != poRxDynSegChannels)
        {
            BapBusIndirectionRxRomRow_pot poBusRxTable;
            /*lint -e9034*/ /*MISRA_2012_REQ_10.3 : Warning deactivated. Refers to bap_types.h, definition of BAP_FCTID_BAPCONFIG*/
            apoRxPars->oPars.poFctRomRow = BAP_GetLsgFctRomRow(apoRxPars->oPars.poLsgRomRow, BAP_FCTID_BAPCONFIG);
            /*lint +e9034*/
            poBusRxTable = &BAP_BusIndRxTable[apoRxPars->oPars.poFctRomRow->u16BusRxTableIndex];
            poRxDynSegChannels->arpoRxDynSegChannels[u8SegChannel] = poBusRxTable->poCanRx;
        }
    }
#endif /* #if defined(BAP_ASG) && defined(BAP_USES_SEGMENTATION) */
    else
    {
        /* ignoriere empfangene Daten */
    }

    return bDataProcessed;
    /*lint +esym(613, apoRxPars) */
    /*lint +esym(613, apfnRxHandler) */
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


/**
 *  Diese Funktion verarbeitet eine empfangene CAN-Nachricht.
 *
 *  Falls es sich um eine unsegmentierte Nachricht handelt, dann wird diese direkt an die Applikation gemeldet.
 *
 *  Bei segmentierten Nachrichten wird die Nachricht zunaechst in den Puffer eingetragen und falls die
 *  Nachricht vollstaendig empfangen wurde, wird diese direkt an die Applikation gemeldet.
 *
 *  Es erfolgt keine Interrupt-Entkopplung innerhalb dieser Funktion.
 *
 *  Diese Funktion hat 12 OutgoingCalls (max.7), 6 ControlNestingLayers (max.4), 58 Statements (max.50)
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_STATIC BAP_IMPL_FAR void
BAP_BCL_CanReceiveData(BapCanRxBuffer_cpot apoCanRxBuffer)
{
    /*lint -e546 */ /* LINT is overly correct here - that's the only way to be MISRA rule 16.9 compliant, see MISRA bulletin board www.misra.org.uk/forum/viewtopic.php?f=76&t=1208 */
    DBGVAR RxHandler_ft pfnRxHandler = &BAP_CAN_RxNothing;
    /*lint +e546 */
    DBGVAR bool_t bDataProcessed = BAP_FALSE;


#ifdef BAP_USES_SEGMENTATION
    DBGVAR uint16_t u16PDUSize;
    DBGVAR uint16_t u16TempVal;
#endif

    /*lint -esym(613,apoCanRxBuffer) */
    BAP_ASSERT(NULL != apoCanRxBuffer);
    /*lint -e9087*/ /* MISRA_2012_REQ_11.3 : 1st argument of MEMSET of type BapRxParameters_ot is
                     *implicitly cast to void*. MEMSET was manually tested with this argument and behaved properly.*/
    MEMSET(&Bap_oRxPars, 0, sizeof(Bap_oRxPars));
    /*lint +e9087*/
    /* memset belegt folgende Felder mit Werten:
       Bap_oRxPars.fctId = 0;
       Bap_oRxPars.lsgId = 0;
       Bap_oRxPars.u32SegmentationLength = 0;
       Bap_oRxPars.poCanRxRomRow = NULL;
       Bap_oRxPars.eSegmentationType = BapSegType_Unsegmented;
       Bap_oRxPars.poLsgRomRow = NULL;
       Bap_oRxPars.poFctRomRow = NULL;
       Bap_oRxPars.eSegmentationTypeMask = BapSegType_Unsegmented;
     */

#ifdef BAP_USES_SEGMENTATION
    Bap_oRxPars.eSegmentationTypeMask = BapSegType_ChannelOneTwoThreeFour;
#endif
    Bap_oRxPars.u16MsgLength = apoCanRxBuffer->u16MsgLength;
    /*lint -e960*/ /* MISRA2004: attempt to cast away const/volatile from a pointer or reference. --> ist aber noetig*/
    /*lint +e9087*/
    /*lint -e9087*/ /* MISRA_2012_REQ_11.3 : 1st and 2nd arguments of MEMCPY are of types (uint8_t*).
                     * They are implicitly cast to (void*). The memory is packed because it is uint8_t so there should be no problem to copy.*/
    /*lint -e9005*/ /* MISRA_2012_REQ_11.8 : From the behavior of PC-Lint 9.00L, it seems it throws a warning because apoCanRxBuffer->aru8Data is a uint8_t* passed
                     * to a const void*. This is used as a source array so it will not be modified.*/
    MEMCPY(Bap_oRxPars.aru8RxData, apoCanRxBuffer->aru8Data, apoCanRxBuffer->u16MsgLength );
    /*lint +e9087 +e9005*/
    /*lint +e960*/
    Bap_oRxPars.canId = apoCanRxBuffer->canMsgId;
    Bap_oRxPars.canInterfaceChannel = apoCanRxBuffer->canInterfaceChannel;

    /* Analysiere Telegramm, ob segmentiert oder unsegmentiert */
    if ( (uint8_t)0 == (Bap_oRxPars.aru8RxData[BAP_FIRST_HEADER_BYTE] & BAP_BIT7)) /* if Header nicht 0x80, d.h. Data ist NonSeg*/
    {
        /*lint -e546 */ /* LINT is overly correct here - that's the only way to be MISRA rule 16.9 compliant, see MISRA bulletin board www.misra.org.uk/forum/viewtopic.php?f=76&t=1208 */
        pfnRxHandler = &BAP_CAN_RxUnsegmented;
        /*lint +e546 */

        /* Analysiere BAP Header (lsgId, fctId) */
        BAP_CAN_AnalyzeHeaderBytes(&Bap_oRxPars);
    }
#ifdef BAP_USES_SEGMENTATION
    else
    {
         /* Ermittle Segmentierungskanal. Bilde Zweierpotenz, dies entspricht dem Segmentierungstyp */
        /*lint -e9033*/ /* MISRA_2012_REQ_10.3 cast of a composite expression is seen as suspicious. The max possible is only 24,
                         *  wich fits in a uint8_t so no risk of overflow arise there.*/
        /*lint -e9034*/ /* MISRA_2012_REQ_10.5 cast of uint8_t to BapSegmentationType_et.
         	 	 	 	 * No risk arise here as uint8_t can be assigned to a valid enum */
        /* MISRA-C 2012 C99 Rule 13.4: The result of an assignment operator should not be used -> fixed 2021_03_01 */
    	Bap_oRxPars.eSegmentationType
    	       = (BapSegmentationType_et) (uint8_t)( (uint8_t)1 << ((Bap_oRxPars.aru8RxData[0] & BAP_BITMASK_00110000) >> (uint8_t)4));
        Bap_oRxPars.eSegmentationTypeMask = (Bap_oRxPars.eSegmentationType);
        /*lint +e9033 +e9034*/

        if ((uint8_t)0 == (Bap_oRxPars.aru8RxData[BAP_FIRST_HEADER_BYTE] & BAP_BIT6))
        {
            if (apoCanRxBuffer->u16MsgLength<BAP_MIN_SEG_STARTMSG_SIZE)
            {
                /* Segmentierte Startbotschaften, auch die Fuellbotschaften, muessen mindestens 4 Bytes haben */
                /*lint -e9034*/ /* MISRA_2012_REQ_10.3 : PC-Lint 9.00L throws a warning due to Tool bug. Hence, this warning has been deactivated.
                                 * Documented with a mail from the Lint team in the SSWCCB-2522_BAP-Entwicklung auf MISRA2012 umstellen folder
                                 * Nor risk arise because fctid and lsgid is never below 0 and fit in enum.*/
                BAP_BCL_ErrorIndication((lsgId_t)0, (fctId_t)0, BapErr_BadDataLength);
                /*lint +e9034*/
                /*lint -e9034*/ /* MISRA_2012_REQ_10.3 : PC-Lint 9.00L throws a warning due to Tool bug. Hence, this warning has been deactivated.
                                 * Documented with a mail from the Lint team in the SSWCCB-2522_BAP-Entwicklung auf MISRA2012 umstellen folder
                                 * No risk arise because fctid and lsgid is never below 0 and fit in enum.*/
                BAP_DBG_BadDataLengthError( (lsgId_t)0 );
                /*lint +e9034*/
            }
            else
            {
                u16PDUSize = BAP_GetRxPduSize(Bap_oRxPars.canId);
                /* Analysiere BAP Header (lsgId, fctId) */
                u16TempVal = (uint16_t) (Bap_oRxPars.aru8RxData[BAP_FIRST_HEADER_BYTE] & (uint16_t)BAP_BITMASK_00001111) << (uint16_t)8; /* 4bit Laenge-Info von Byte0*/
                /* Extrahiere Informationen aus Segmentierungsheader (BCL Rx Pufferlaenge und Segmentierungskanal) */
                Bap_oRxPars.u32SegmentationLength =  u16TempVal;
                Bap_oRxPars.u32SegmentationLength += Bap_oRxPars.aru8RxData[1];
                /* 2014-11-25 WWU: BAP 1.8.0 */
                /* Falls 12-Bits Laenge gleich 4095 ist, dann ist neuem Format */

                /* MISRA2004: attempt to cast away const/volatile from a pointer or reference. --> ist aber noetig*/
                if((Bap_oRxPars.u32SegmentationLength == BAP_EXTENDED_MSG_SIZE) && ( BAP_MAX_PDU_SIZE_OLD_FORMAT < u16PDUSize )){
                    /* Fall-1: PDU_Size ist angegeben >8, Laenge in Header ist 4095, --> Korrekt neues Format */
                    /* Extrahiere Informationen aus Segmentierungsheader (BCL Rx Pufferlaenge und Segmentierungskanal) */
                    Bap_oRxPars.u32SegmentationLength = (uint32_t)((uint32_t)(Bap_oRxPars.aru8RxData[2]) << 24);
                    Bap_oRxPars.u32SegmentationLength += (uint32_t)((uint32_t)(Bap_oRxPars.aru8RxData[3]) << 16);
                    Bap_oRxPars.u32SegmentationLength += (uint32_t)((uint32_t)(Bap_oRxPars.aru8RxData[4]) << 8);
                    Bap_oRxPars.u32SegmentationLength += (uint32_t)(Bap_oRxPars.aru8RxData[5]);

                    /* Optimierung: Bap Header in neuem Format beginnt ab Byte 6 */
                    /*lint -e960*/
                    /*lint -e9087*/ /* MISRA_2012_REQ_11.3 : 1st argument of MEMSET of type uint8_t* is
                                     * implicitly cast to void*. Won't cause any problem as this array will be updated by the following MEMCPY.*/
                    MEMSET(Bap_oRxPars.aru8RxData, 0, sizeof(Bap_oRxPars.aru8RxData));
                    /*lint +e9087*/
                    /*lint +e9087*/
                    /*lint -e9087*/ /* MISRA_2012_REQ_11.3 : 1st and 2nd arguments of MEMCPY are of types (uint8_t*).
                                     * They are implicitly cast to (void*). The memory is packed because it is uint8_t so there should be no problem to copy.*/
                    /*lint -e9005*/ /* MISRA_2012_REQ_11.8 : apoCanRxBuffer->aru8Data[6] is a const uint8_t*, assigned to const void*. This is used as a source array so it will not be modified.*/
                    MEMCPY(Bap_oRxPars.aru8RxData, &apoCanRxBuffer->aru8Data[BAP_EXTENDED_SEG_STARTMSG_HEADER_SIZE], (size_t) apoCanRxBuffer->u16MsgLength - (size_t) BAP_EXTENDED_SEG_STARTMSG_HEADER_SIZE );
                    /*lint +e9087 +e9005*/
                    /*lint +e960 */
                    /*lint -e546 */ /* LINT is overly correct here - that's the only way to be MISRA rule 16.9 compliant, see MISRA bulletin board www.misra.org.uk/forum/viewtopic.php?f=76&t=1208 */
                    pfnRxHandler = &BAP_CAN_RxSegmentedStart;
                    /*lint +e546 */
                    BAP_CAN_AnalyzeHeaderBytes(&Bap_oRxPars);
                }else if((Bap_oRxPars.u32SegmentationLength < BAP_EXTENDED_MSG_SIZE && ( BAP_MAX_PDU_SIZE_OLD_FORMAT == u16PDUSize ))){
                    /* Fall-2: PDU_Size ist NICHT angegeben (default=8), Laenge in Header ist < 4095, --> Korrekt altes Format */
                    /* Optimierung: Bap Header in altem Format beginnt ab Byte 2 */
                    /*lint -e960*/
                    /*lint -e9087*/ /* MISRA_2012_REQ_11.3 : 1st argument of MEMSET of type uint8_t* is
                                     * implicitly cast to void*. Won't cause any problem as this array will be updated by the following MEMCPY.*/
                    MEMSET(Bap_oRxPars.aru8RxData, 0, sizeof(Bap_oRxPars.aru8RxData));
                    /*lint +e9087*/
                    /*lint -e9087*/ /* MISRA_2012_REQ_11.3 : 1st and 2nd arguments of MEMCPY are of types (uint8_t*).
                                     * They are implicitly cast to (void*). The memory is packed because it is uint8_t so there should be no problem to copy.*/
                    /*lint -e9005*/ /* MISRA_2012_REQ_11.8 : apoCanRxBuffer->aru8Data[2] is a const uint8_t*, assigned to const void*. This is used as a source array so it will not be modified.*/
                    MEMCPY(Bap_oRxPars.aru8RxData, &apoCanRxBuffer->aru8Data[BAP_OLD_SEG_STARTMSG_HEADER_SIZE], (size_t) apoCanRxBuffer->u16MsgLength - (size_t) BAP_OLD_SEG_STARTMSG_HEADER_SIZE );
                    /*lint +e9087 +e9005*/
                    /*lint +e960 */
                    /*lint -e546 */ /* LINT is overly correct here - that's the only way to be MISRA rule 16.9 compliant, see MISRA bulletin board www.misra.org.uk/forum/viewtopic.php?f=76&t=1208 */
                    pfnRxHandler = &BAP_CAN_RxSegmentedStart;
                    /*lint +e546 */

                    BAP_CAN_AnalyzeHeaderBytes(&Bap_oRxPars);
                }else{
                    /* Ansonsten wird die Nachricht verworfen. */
                }
            }
        }
        else
        {
            /* Optimierung fuer Sequenzbotschaften */
            bDataProcessed = BAP_BCL_CanReceiveSequence(&Bap_oRxPars);

#   ifdef BAP_ASG
            /* Melde dem BPL dass Daten empfangen wurden (zum Retriggern der Heartbeat-Ueberwachung) */
            Bap_oRxPars.oPars.eOpCode = BapOp_MessageReceived;
            BAP_BCL_DataReceived(&Bap_oRxPars.oPars);
#   endif /* #ifdef BAP_ASG */

            /* Auch wenn die Daten hier nicht verarbeitet werden bewirkt nachfolgender Code nichts
             * da in diesem Fall keine uebereinstimmende LsgId gefunden wird.
             */
        }
    }
#endif /* BAP_USES_SEGMENTATION */

    /* Fuer Sequenzbotschaften werden beide Zeiger = NULL */
    Bap_oRxPars.oPars.poLsgRomRow = BAP_GetLsgRomRow(Bap_oRxPars.oPars.lsgId);
    Bap_oRxPars.oPars.poFctRomRow = BAP_GetLsgFctRomRow(Bap_oRxPars.oPars.poLsgRomRow, Bap_oRxPars.oPars.fctId);

    if ( (NULL != Bap_oRxPars.oPars.poLsgRomRow)
            && ( (Bap_oRxPars.oPars.poLsgRomRow->poLsgRamRow->eLsgStatus == BapLayerLsgStat_Running)
#ifdef BAP_ASG  /* Im Kombigeraet gibt es WaitForConfig nicht fuer FSGs */
                    || (Bap_oRxPars.oPars.poLsgRomRow->poLsgRamRow->eLsgStatus == BapLayerLsgStat_WaitForOrInvalidConfig)
#endif /* #ifdef BAP_ASG */
            )
    )
    {
#if defined(BAP_ASG) && defined(BAP_USES_SEGMENTATION)
        /* BAP v1.6.2: Speziele Behandlung fuer Funktionlist mit unsymmetrischer Interface
         * ASG: Segmentierte Interfache  ----  FSG: unsegmentierte Interface
         */
        Bap_bIsFctListSym = BAP_TRUE;
        if( (BAP_FCTID_FCTLIST == (fctId_t)Bap_oRxPars.oPars.fctId )
#   ifdef BAP_FSG /* Kombi */
                && (BapSG_ASG == Bap_oRxPars.oPars.poLsgRomRow->eSGType)
#   endif /* BAP_FSG */
        )
        {
            Bap_bIsFctListSym = BAP_BCL_CheckCanIfSymmetry(&Bap_oRxPars);
        }
#endif /* defined(BAP_ASG) && defined(BAP_USES_SEGMENTATION) */

        bDataProcessed = BAP_BCL_CanProcessData(&Bap_oRxPars, pfnRxHandler);

#ifdef BAP_ASG
        /* Melde dem BPL dass Daten empfangen wurden (zum Retriggern der Heartbeat-Ueberwachung) */
        Bap_oRxPars.oPars.eOpCode = BapOp_MessageReceived;
        BAP_BCL_DataReceived(&Bap_oRxPars.oPars);
#endif /* BAP_ASG */
    }

    if (BAP_FALSE == bDataProcessed)
    {
        BAP_DBG_RxDataPurgedEvent();
    }
#ifdef BAP_USES_SEGMENTATION
    else
        if (Bap_oRxPars.eSegmentationType != BapSegType_Unsegmented)
        {
            BAP_CAN_RxSegCompleteCheck(&Bap_oRxPars);
        }
        else
        {
            /* Unsegmentierte Daten wurden verarbeitet, keine weitere Arbeiten noetig.
           Else-Zweig wird fuer Einhaltung der Misra Regel 60 benoetigt */
        }
#endif /* BAP_USES_SEGMENTATION */

    return;
    /*lint +esym(613,apoCanRxBuffer) */
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


/*  Diese Funktion ist in bap_bclbus.h dokumentiert */
#define BAP_START_SEC_CODE_CYCLIC
#include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_BCL_CanSendTask(void)
{
    /* Einstiegspunkt muss static sein, sonst wird er verworfen, beim naechsten Aufruf */
#ifndef DLL_COMPILATION
#endif /* #ifdef DLL_COMPILATION */
    DBGVAR bool_t bCanTxSentNow; /* Flag zum Kennzeichnen ob Nachricht verschickt werden konnte */
    DBGVAR uint8_t u8CanIndex; /* Zum inkrementieren der Sende-PDU */
    DBGVAR uint8_t u8CanIdBufferLength; /* Zum Zwischenspeichern der Bufferlaenge */
    DBGVAR uint8_t u8CanTxMsgIdx;
#ifdef BAP_TASKTIME_LIMIT
    BapLsgRomRow_pot poLsgRomRow = NULL;
    BapLsgState_pot pfLsgState = NULL;
#endif /* #ifdef BAP_TASKTIME_LIMIT */

    /* Nachfolgende Behandlungen sind sortiert nach Tx-CAN-Ids */
    for (u8CanIndex = (uint8_t)0;
            u8CanIndex < BAP_CAN_TX_SEGMENTATION_CHANNELS;
            u8CanIndex++ )
    {
        u8CanIdBufferLength = Bap_u8CanTxBufferLength[u8CanIndex];
        bCanTxSentNow = BAP_FALSE;

        /* Der Sende-Buffer einer Tx-Sende-PDU wird solange abgearbeitet bis eine Nachricht erfolgreich versandt wurde oder das Ende des Buffers erreicht ist. */
        for(u8CanTxMsgIdx = (uint8_t)0; (BAP_FALSE == bCanTxSentNow) && (u8CanIdBufferLength > u8CanTxMsgIdx); u8CanTxMsgIdx++)
        {
            Bap_oTxPars.poCanTxRomRow = BAP_BCL_CanTxBufferRead(u8CanIndex);

            /* Wenn ein NULL-Pointer Eintrag vorliegt sind keine Daten ueber diese PDU zu verschicken */
            if (NULL != Bap_oTxPars.poCanTxRomRow)
            {
#ifdef BAP_TASKTIME_LIMIT
                poLsgRomRow = BAP_GetLsgRomRow(Bap_oTxPars.poCanTxRomRow->poFctRomRow->lsgId);

                if (NULL != poLsgRomRow)
                {
                    pfLsgState = &poLsgRomRow->poLsgRamRow->fState;
                }
#endif /* #ifdef BAP_TASKTIME_LIMIT */

                Bap_oTxPars.poBclTxRamRow = Bap_oTxPars.poCanTxRomRow->poBclTxRamRow;
#ifdef BAP_USES_SEGMENTATION
                Bap_oTxPars.poCanTxRamRow = Bap_oTxPars.poCanTxRomRow->poCanTxRamRow;
#endif  /* #ifdef BAP_USES_SEGMENTATION */

                bCanTxSentNow = BAP_BCL_CanSendTaskTxReq(
#ifdef BAP_USES_SEGMENTATION
                        poLsgRomRow
#endif /* BAP_USES_SEGMENTATION */
#ifdef BAP_TASKTIME_LIMIT
                        , pfLsgState
#endif /* BAP_TASKTIME_LIMIT */
                );
                /* Ueberpruefung der Sende-Flags ob die aktuelle Nachricht erneut verschickt werden muss. Grund hierfür kann sein das der Bus voll ist
                 *  oder nach einer Error-Message eine Request-Message folgt oder eine segementierte Nachricht noch nicht abgeschlossen ist. */
                if  (((bitfield_t) 1u == Bap_oTxPars.poBclTxRamRow->flags.fTxRequestFlag)
#ifdef BAP_USES_SEGMENTATION
                        || ((bitfield_t) 1u == Bap_oTxPars.poBclTxRamRow->flags.fTxInProgressFlag)
#endif  /* #ifdef BAP_USES_SEGMENTATION */
#ifdef BAP_FSG
                        || ((bitfield_t) 1u == Bap_oTxPars.poBclTxRamRow->flags.fTxErrorFlag)
#endif /* #ifdef BAP_FSG */
                )   {
                    /* Falls ein erneuter Sendevorgang erfoderlich ist, muss die Nachricht wieder in den Sende-Buffer eingetragen werden. */
                    BAP_BCL_CanTxBufferWrite(Bap_oTxPars.poCanTxRomRow);
                }
            }
        }
    }
    return;
}
#define BAP_STOP_SEC_CODE_CYCLIC
#include <BAP_MemMap.h>


/*  Diese Funktion ist in bap_bclbus.h dokumentiert */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_IMPL_FAR bool_t
BAP_BCL_CanSendTaskTxReq(
#ifdef BAP_USES_SEGMENTATION
        BapLsgRomRow_pot poLsgRomRow
#endif /* BAP_USES_SEGMENTATION */
#ifdef BAP_TASKTIME_LIMIT
        , BapLsgState_pot pfLsgState
#endif /* BAP_TASKTIME_LIMIT */
)
{
    DBGVAR bool_t bCanTxSentNow = BAP_FALSE;
#ifdef BAP_USES_SEGMENTATION
    if (Bap_oTxPars.poCanTxRomRow->poFctRomRow == BAP_GetLsgFctRomRow(poLsgRomRow, Bap_oTxPars.poCanTxRomRow->poFctRomRow->fctId))
#endif  /* #ifdef BAP_USES_SEGMENTATION */
    {
#ifdef BAP_TASKTIME_LIMIT
        /* Ubernehme Ergebnis in Zwischenpuffer, da durch die Heuristik bedingt ein Lsg zweimal drankommen kann */
        pfLsgState->fTxFlag = BAP_TRUE; /*lint !e613*/ /* pfLsgState wird immer initialisiert wenn bLsgTxFlag != BAP_FALSE */
#endif /* #ifdef BAP_TASKTIME_LIMIT */

        if (( (uint16_t)0u == BAP_InhibitRamTable[Bap_oTxPars.poCanTxRomRow->u8InhibitIndex].u16InhibitTimer))
        {
            bCanTxSentNow = BAP_BCL_LowLevelCanTxTask(&Bap_oTxPars);
        }
    }
    return bCanTxSentNow;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


/*  Diese Funktion ist in bap_bclbus.h dokumentiert */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_BCL_InitCanDrvTxCfmFlags(BapLsgRomRow_pot apoLsgRomRow)
{
    DBGVAR uint16_t u16InhibitIndex;
    DBGVAR uint8_t u8LsgIndex;
    DBGVAR uint8_t u8LsgTableSize;
    DBGVAR uint16_t pu16MapCanIdToLsgTableIndex;
    DBGVAR BapLsgRomRow_pot poLsgRomRow;

    /* Gibt an, ob es ein Steuergeraet mit dieser CAN-Id gibt, welches schon gestartet ist.
       Wird auch als Abbruchbedingung von Schleifen verwendet */
    DBGVAR bool_t bLsgStarted;

    /* Gibt an, ob die betroffene CAN-Id auch vom aktuellen Steuergeraet verwendet wird */
    DBGVAR bool_t bCurrentLsgOwns;

    /*lint -esym(613,apoLsgRomRow)*/
    BAP_ASSERT(apoLsgRomRow != NULL);

    /* [ALA 2006-11-17] Optimierung Verarbeitungszeit von Reset-Nachrichten */
    /* Verwendung der BAP_InhibitRomTable um CAN Msg Ids zu finden */
    for(u16InhibitIndex = (uint16_t)0; u16InhibitIndex < BAP_INHIBIT_ROWS; u16InhibitIndex++)
    {
        bLsgStarted = BAP_FALSE;
        bCurrentLsgOwns = BAP_FALSE;
        u8LsgTableSize = BAP_InhibitRomTable[u16InhibitIndex].u8MapCanIdToLsgSize;
        pu16MapCanIdToLsgTableIndex = BAP_InhibitRomTable[u16InhibitIndex].u16MapCanIdToLsgTableIndex;

        /* Nur falls kein Steuergeraet gestartet ist, welches diese CAN-Id verwendet, darf das Tx-Flag initialisiert werden */
        for(u8LsgIndex = (uint8_t)0; (u8LsgIndex < u8LsgTableSize) && ( BAP_FALSE == bLsgStarted); u8LsgIndex++)
        {
            poLsgRomRow = BAP_MapCanIdToLsgRomRowTable[pu16MapCanIdToLsgTableIndex+u8LsgIndex].poLsgRomRow;
            if ((poLsgRomRow->poLsgRamRow->eLsgStatus > BapLayerLsgStat_Initialized) && (poLsgRomRow->lsgId != apoLsgRomRow->lsgId))
            {
                bLsgStarted = BAP_TRUE;
            }
            if (poLsgRomRow->lsgId == apoLsgRomRow->lsgId)
            {
                bCurrentLsgOwns = BAP_TRUE;
            }
        }

        if (BAP_FALSE == bCurrentLsgOwns)
        {
            /* CAN-Id soll nicht initialisiert werden, falls sie vom aktuellen Steuergeraet ueberhaupt nicht verwendet wird */
            bLsgStarted = BAP_TRUE;
        }

        /* Nehme den passenden Interface-Channel und MsgId */
        if (BAP_FALSE == bLsgStarted)
        {
            BAP_CANUBS_InitReadyForTx(BAP_InhibitRomTable[u16InhibitIndex].canInterfaceChannel
                    , BAP_InhibitRomTable[u16InhibitIndex].canMsgId);
        }
    }
    return;
    /*lint +esym(613,apoLsgRomRow)*/
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>

/*
 * Diese Funktion dient zur Initialisierung des ersten Blocks im Empfangs-Ringbuffer
 * und muss einmalig vor dessen erster Verwendung aufgerufen werden.
 *
 * @param
 *
 * @returns
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
static BAP_IMPL_FAR
void BAP_RxRingBufferInit() {
    /*lint -e923*/ /*[MISRA 2012 Rule 11.6, required] cast from pointer to unsigned int */
    /*lint -e9078*/ /*[MISRA 2012 Rule 11.4, advisory] conversion between a pointer and integer type
                     * Address of BAP_CanRxRingBuffer must be cast to integral value to calculate number of padding bytes.*/
	/* Padding calculation for memory alignment may require platform dependent adjustments */
	uintptr_t padding = ((~(uintptr_t)BAP_CanRxRingBuffer) + (uintptr_t)1) & (sizeof(uint8_t*) - (uintptr_t)1);
	/*lint +e9078*/
	/*lint +e923*/
	/*lint -e9087*/ /*[MISRA 2012 Rule 11.3, required] cast performed between a pointer to object type and a pointer to a different object type */
	/*lint -e9016*/ /*[MISRA 2012 Rule 18.4, advisory] pointer arithmetic other than array indexing used
	 	 	 	 	 * Aligned BAP_CanRxRingBuffer start address must be calculated arithmetically */
	BAP_CanRxRingBufferFirstBlock = (BapCanRxBufferMeta_pot) (BAP_CanRxRingBuffer + padding);
	/*lint +e9016*/
	/*lint +e9087*/
	BAP_CanRxRingBufferFirstBlock->u32BlockSize = (uint32_t)(BAP_CAN_RX_RING_BUFFER_SIZE - sizeof(BapCanRxBufferMeta_ot));
	BAP_CanRxRingBufferFirstBlock->isFree = BAP_TRUE;
	BAP_CanRxRingBufferFirstBlock->next = NULL;
	BAP_CanRxRingBufferFirstBlock->nextFifo = NULL;
	BAP_CanRxRingBufferFifoHead = BAP_CanRxRingBufferFirstBlock;
	BAP_CanRxRingBufferFifoTail = BAP_CanRxRingBufferFirstBlock;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>

/*
 * Diese Funktion dient zur Aufteilung eines freien Ringbuffer Speicher-Blocks in einen belegten Speicher-Block in
 * angegebener Groesse und einen freien Rest-Block.
 *
 * @param fittingBlock Speicher-Block, der aufgeteilt werden soll
 * @param size Erforderliche Nutzdatengroesse
 *
 * @returns
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
static BAP_IMPL_FAR void
BAP_RxRingBufferSplit(BapCanRxBufferMeta_pot fittingBlock, size_t size) {
	uint8_t* restBlock_unaligned = ((uint8_t*)fittingBlock) + size + sizeof(BapCanRxBufferMeta_ot);
    /*lint -e923*/ /*[MISRA 2012 Rule 11.6, required] cast from pointer to unsigned int */
    /*lint -e9078*/ /*[MISRA 2012 Rule 11.4, advisory] conversion between a pointer and integer type
                     * Address of restBlock_unaligned must be cast to integral value to calculate number of padding bytes.*/
	/* Padding calculation for memory alignment may require platform dependent adjustments */
	uintptr_t padding = ((~(uintptr_t)restBlock_unaligned) + (uintptr_t)1) & (sizeof(uint8_t*) - (uintptr_t)1);
	/*lint +e9078*/
	/*lint +e923*/
	restBlock_unaligned += padding;
	/*lint -e9087*/ /*[MISRA 2012 Rule 11.3, required] cast performed between a pointer to object type and a pointer to a different object type */
	/*lint -e9016*/ /*[MISRA 2012 Rule 18.4, advisory] pointer arithmetic other than array indexing used
	 	 	 	 	 * Aligned BAP_CanRxRingBuffer start address must be calculated arithmetically */
	BapCanRxBufferMeta_pot restBlock = (BapCanRxBufferMeta_pot) restBlock_unaligned;
	/*lint +e9016*/
	/*lint +e9087*/
	restBlock->u32BlockSize = (uint32_t)((fittingBlock->u32BlockSize) - size - sizeof(BapCanRxBufferMeta_ot) - padding);
	restBlock->isFree = BAP_TRUE;
	restBlock->next = fittingBlock->next;
	fittingBlock->u32BlockSize = (uint32_t)(size + padding);
	fittingBlock->isFree = BAP_FALSE;
	fittingBlock->next = restBlock;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>

/*
 * Diese Funktion dient zur dynamischen Allokierung eines zusammenhaengenden Speicherbereichs im Empfangs-Ringbuffer.
 * Der erste passende, freie Block wird verwendet und wenn moeglich in einen verwendeten und einen freien Rest-Block aufgeteilt.
 *
 * @param requestedBytes Erforderliche Nutzdatengroesse
 *
 * @returns Pointer vom Typ uint8_t auf den allokierten Speicherbereich oder NULL, falls keine Allokierung moeglich war
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
static BAP_IMPL_FAR uint8_t*
BAP_RxRingBufferAlloc(size_t requestedBytes) {
	if(BAP_CanRxRingBufferFirstBlock == NULL || BAP_CanRxRingBufferFirstBlock->u32BlockSize == (uint32_t)0){
		BAP_RxRingBufferInit();
	}
	BapCanRxBufferMeta_pot block = BAP_CanRxRingBufferFirstBlock;
	while ((((block->u32BlockSize) < requestedBytes) || ((block->isFree) == BAP_FALSE)) && (block->next != NULL)) {
		block = block->next;
	}
	if((block->isFree) == BAP_FALSE){
		return NULL;
	}
	if ((block->u32BlockSize) > (requestedBytes + sizeof(BapCanRxBufferMeta_ot))) {
		BAP_RxRingBufferSplit(block, requestedBytes);
	} else if ((block->u32BlockSize) >= requestedBytes) {
		block->isFree = BAP_FALSE;
	} else {
		return NULL;
	}
	BAP_CanRxRingBufferFifoHead->nextFifo = block;
	BAP_CanRxRingBufferFifoHead = block;
	return (uint8_t*) ++block;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>

/*
 * Diese Funktion dient zur Vereinigung aneinander angrenzender, freier Speicherbereiche im Empfangs-Ringbuffer.
 *
 * @param
 *
 * @returns
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
static BAP_IMPL_FAR void
BAP_RxRingBufferMerge() {
	BapCanRxBufferMeta_pot curr = BAP_CanRxRingBufferFirstBlock;
	while (curr && (curr->next) != NULL) {
		if ((curr->isFree == BAP_TRUE) && (curr->next->isFree == BAP_TRUE)) {
			curr->u32BlockSize += (uint32_t)((curr->next->u32BlockSize) + sizeof(BapCanRxBufferMeta_ot));
			curr->next = curr->next->next;
		}else{
			curr = curr->next;
		}
	}
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>

/*
 * Diese Funktion kapselt die Bedingung zur Abfrage, ob der Empfangs-Ringbuffer leer ist.
 *
 * @param
 *
 * @returns True wenn Rx-Ringbuffer leer ist
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
static BAP_IMPL_FAR bool_t
BAP_RxRingbufferEmpty(){
	if((BAP_CanRxRingBufferFirstBlock == NULL) ||
			((BAP_CanRxRingBufferFifoHead == BAP_CanRxRingBufferFifoTail) && (BAP_CanRxRingBufferFifoTail->isFree == BAP_TRUE))){
		return BAP_TRUE;
	}else{
		return BAP_FALSE;
	}
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>

/*
 * Diese Funktion dient zur Deallokierung des aeltesten Speicherbereichs im Empfangs-Ringbuffer.
 * Der Blockstatus wird in den Meta-Daten auf "frei" gesetzt. Die globalen Variablen zur Verwaltung des
 * FIFO Zugriffs werden aktualisiert und BAP_RxRingBufferMerge wird aufgerufen.
 *
 * @param
 *
 * @returns
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
static BAP_IMPL_FAR void
BAP_RxRingBufferFree() {
	BapCanRxBufferMeta_pot curr = BAP_CanRxRingBufferFifoTail;
	curr->isFree = BAP_TRUE;
	if(BAP_RxRingbufferEmpty() == BAP_TRUE){
		BAP_CanRxRingBufferFifoHead = BAP_CanRxRingBufferFirstBlock;
		BAP_CanRxRingBufferFifoTail = BAP_CanRxRingBufferFirstBlock;
	} else if (curr->nextFifo != NULL) {
		BAP_CanRxRingBufferFifoTail = curr->nextFifo;
		curr->nextFifo = NULL;
	} else {
		/* [MISRA 2012 Rule 15.7, required] */
	}
	BAP_RxRingBufferMerge();
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>

/*
 * Diese Funktion gibt die als naechstes zu Verarbeitende Nachricht aus dem Empfangs-Ringbuffer zurueck.
 *
 * @param
 *
 * @returns BapCanRxBuffer_t Pointer auf die naechste (Fifo) zu verarbeitende Nachricht
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
static BAP_IMPL_FAR BapCanRxBuffer_pot
BAP_RxRingBufferCurrentMessage() {
	/*lint -e740*/ /*[MISRA 2012 Rule 1.3, required] Unusual pointer cast (incompatible indirect types) */
	/*lint -e9087*/ /*[MISRA 2012 Rule 11.3, required] cast performed between a pointer to object type and a pointer to a different object type */
	 	 	 	    /* Oldest alloated meta data pointer has to be incremented to point to the user data */
	return (BapCanRxBuffer_pot)(BAP_CanRxRingBufferFifoTail + 1);
	/*lint +e9087*/
	/*lint +e740*/
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>

/* Diese Funktion ist in bap_bclbus.h dokumentiert */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_BCL_CanReceiveTask(void)
{
    DBGVAR bool_t bFlagBufferOverflow;
    DBGVAR bool_t bRingBufferEmpty;
    Bap_u8IRQState = (uint8_t) 0;

#ifdef BAP_RUNTIME_TEST
			BAP_RUNTIME_TEST_PROCESS_RECEIVED_START();
#endif /* BAP_RUNTIME_TEST */

	do {
		disableint(&Bap_u8IRQState);
		bRingBufferEmpty = BAP_RxRingbufferEmpty();
		bFlagBufferOverflow = BAP_u8CanRxRingBufferMessageLost;
		restoreint(Bap_u8IRQState);

		if (bFlagBufferOverflow != BAP_FALSE) {
			/*lint -e9034*/ /*MISRA_2012_REQ_10.3 : Allow cast from integer to enum because it is ensured that enum value 0 always exists */
			BAP_BCL_ErrorIndication((lsgId_t)0, (fctId_t)0, BapErr_ReceivedDataLost);
			/*lint +e9034*/
			BAP_DBG_DataLostError();
		}
		if (bRingBufferEmpty == BAP_FALSE) {
			BapCanRxBuffer_pot poCanRxBuffer = BAP_RxRingBufferCurrentMessage();
			BAP_BCL_CanReceiveData(poCanRxBuffer);

			disableint(&Bap_u8IRQState);
			BAP_RxRingBufferFree();
			bRingBufferEmpty = BAP_RxRingbufferEmpty();
			BAP_u8CanRxRingBufferMessageLost = BAP_FALSE;
			restoreint(Bap_u8IRQState);
		}
	} while (bRingBufferEmpty == BAP_FALSE);

#ifdef BAP_RUNTIME_TEST
			BAP_RUNTIME_TEST_PROCESS_RECEIVED_STOP();
#endif /* BAP_RUNTIME_TEST */

    return;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


#if defined(BAP_ASG) && defined(BAP_USES_SEGMENTATION)
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
static BAP_IMPL_FAR bool_t
BAP_BCL_CheckCanIfSymmetry(BapRxParameters_pot apoRxPars)
/*lint -esym(818,apoRxPars) */  /* LINT Meldung wegen pointer to const */
{
    DBGVAR bool_t result = BAP_FALSE;
    BapBusIndirectionRxRomRow_pot poBusIndRx = NULL;
    DBGVAR uint8_t u8RxTableSize;
    DBGVAR uint8_t u8RxTableIdx;

    /*lint -esym(613,apoRxPars) */
    BAP_ASSERT(apoRxPars != NULL);

    u8RxTableSize = apoRxPars->oPars.poFctRomRow->u8RxTableSize;

    /* Suche unter den moeglichen CAN Rx Eintraegen nach dem Eintrag, bei dem canId usw. uebereinstimmen.
       Da i.d.R. nur 1-2 Rx konfiguriert werden, lohnt es sich nicht, die Schleife vorzeitig abzubrechen
     */
    for (u8RxTableIdx=(uint8_t)0; u8RxTableIdx<u8RxTableSize; u8RxTableIdx++)
    {
        poBusIndRx = &BAP_BusIndRxTable[apoRxPars->oPars.poFctRomRow->u16BusRxTableIndex + (uint16_t)u8RxTableIdx];
        if ( (BapIft_Can == poBusIndRx->eInterfaceType)
                && (apoRxPars->canId == poBusIndRx->poCanRx->canMsgId)
                && (apoRxPars->canInterfaceChannel == poBusIndRx->poCanRx->canInterfaceChannel)
        ) /* Interface gefunden ? */
        {
            if( ((uint8_t)poBusIndRx->poCanRx->eSegmentationType & (uint8_t)apoRxPars->eSegmentationTypeMask)
                    == (uint8_t)apoRxPars->eSegmentationType)  /* Sind 2 Interface symmetrisch? */
            {
                result = BAP_TRUE;
            }
        }
    }

    return result;
    /*lint +esym(613,apoRxPars) */
}
/*lint +esym(818,apoRxPars) */
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* defined(BAP_ASG) && defined(BAP_USES_SEGMENTATION) */

/* CallBack-Funktionen */

/* Ueberpruef, ob der Rx-Botschaft gueltig zum Verarbeitung oder soll verworfen werden.
 * Alt Format
 *      10XX 1111 | 1111 1111 --> Fuellbotschaft, wird verworfen.
 * Neu Format
 *  Fall-1: PDU_SIZE angegeben, aber alte Laenge != 4095  --> wird verworfen
 *  Fall-2: PDU_SIZE angegeben, alte Laenge == 4095, aber neue Laenge ==0  --> wird verworfen
 *
 * Return:
 *      true: Rx-Botschaft ist gueltig
 *      false: Verwerfen
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
static BAP_IMPL_FAR bool_t
BAP_BCL_CanCheckRxData(DBGVAR BapCanMsgId_t aCanMsgId,
#ifdef BAP_USES_SEGMENTATION
        DBGVAR const uint8_t apData[],
#endif /* BAP_USES_SEGMENTATION */
        DBGVAR uint16_t au16MsgLength)
{
    DBGVAR bool_t bResult = BAP_TRUE;
    DBGVAR uint16_t u16RxPDUSize = BAP_GetRxPduSize(aCanMsgId);
    if ( (au16MsgLength < (uint16_t)BAP_HEADER_BYTES_NONSEG) || (au16MsgLength > u16RxPDUSize) )
    {
        /* ignoriere Nachrichten, welche keinen BAP-Header haben
           1 Byte Header gibt es zwar bei Folgebotschaften segmentierter Nachrichten,
           diese muessen aber mindestens ein Datenbyte beinhalten.
           Unsegmentierte Nachrichten haben einen 2 Byte Header.
           Segmentierte Nachrichten haben einen 4 Byte Header.
           CAN Botschaften koennen nicht mehr als 8 Bytes haben.
           CAN-FD Botschaften koennen nicht mehr als 64 Bytes haben.
           Ethernet Botschaften koennen nicht mehr als 1514 Bytes haben.
           Falls diese Laenge uebergeben wird, handelt es sich um einen Integrationsfehler.
         */
        bResult = BAP_FALSE;
    }
#ifdef BAP_USES_SEGMENTATION
    else if( BAP_BIT7 == (apData[BAP_FIRST_HEADER_BYTE] & BAP_BITMASK_11000000))
    {
        /* RxData ist Startbotschaft */
        if (u16RxPDUSize > BAP_MAX_PDU_SIZE_OLD_FORMAT)
        {
            /* Fuellbotschaft in Neues Format: */
            /* Fall-2: PDU_SIZE angegeben, alte Laenge == 4095, aber neue Laenge ==0 */
            if ( (BAP_BITMASK_00001111 == (apData[BAP_FIRST_HEADER_BYTE] & BAP_BITMASK_00001111)) && (BAP_BITMASK_11111111 == apData[BAP_SECOND_HEADER_BYTE]) )
            {
                /* ignoriere Fuellbotschaft, ohne dass eine Diagnosemeldung auftritt */
                bResult = BAP_TRUE;
            }
            else
            {
                /* Fall-1: PDU_SIZE angegeben, aber alte Laenge != 4095  --> verwerfen! */
                bResult = BAP_FALSE;
            }
        }
        else
        {  /* Altes Format */
            if ( (BAP_BITMASK_00001111 == (apData[BAP_FIRST_HEADER_BYTE] & BAP_BITMASK_00001111)) && (BAP_BITMASK_11111111 == apData[BAP_SECOND_HEADER_BYTE]) )
            {
                /* 10XX 1111 | 1111 1111| ist in altem Format ein Fuellbotschaft. */
                /* ignoriere Fuellbotschaft, ohne dass eine Diagnosemeldung auftritt */
                bResult = BAP_FALSE;
            }
        }
    }
    else
    {
        /* Sequencebotschaft oder unsegmentierte Botschaft */
        bResult = BAP_TRUE;
    }
#endif /* #ifdef BAP_USES_SEGMENTATION */

    return bResult;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


/*  Diese Funktion ist in bap_canubs.h dokumentiert */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_CANUBS_RxData(DBGVAR BapCanInterfaceChannel_t aCanInterfaceChannel
        , DBGVAR BapCanMsgId_t aCanMsgId
        , DBGVAR const uint8_t apData[]
                                      , DBGVAR uint16_t au16MsgLength)
{
    Bap_u8IRQState = (uint8_t) 0;
    if(NULL != apData)
    {
        if ( BAP_BCL_CanCheckRxData(aCanMsgId,
#ifdef BAP_USES_SEGMENTATION
                apData,
#endif /* BAP_USES_SEGMENTATION */
                au16MsgLength) == BAP_TRUE )
        {
            BAP_DBG_RxEvent();

#ifdef BAP_RUNTIME_TEST
            BAP_RUNTIME_TEST_RECEIVE_START();
#endif /* BAP_RUNTIME_TEST */

			disableint(&Bap_u8IRQState);

			/*lint -e9087*/ /*[MISRA 2012 Rule 11.3, required] cast performed between a pointer to object type and a pointer to a different object type */
			 	 	 	    /* Allocated buffer memory has to be reinterpreted as BapCanRxBuffer object */
			BapCanRxBuffer_pot poCanRxBuffer = (BapCanRxBuffer_pot) BAP_RxRingBufferAlloc(sizeof(BapCanRxBuffer_ot) + au16MsgLength);
			/*lint +e9087*/
			if (poCanRxBuffer == NULL) {
				BAP_u8CanRxRingBufferMessageLost = BAP_TRUE;
				BAP_DBG_RxDataPurgedEvent();
			} else {
				poCanRxBuffer->canInterfaceChannel = aCanInterfaceChannel;
				poCanRxBuffer->canMsgId = aCanMsgId;
				poCanRxBuffer->u16MsgLength = au16MsgLength;
				/*lint -e9087*/ /*[MISRA 2012 Rule 11.3, required] cast performed between a pointer to object type and a pointer to a different object type */
 	 	 	    				/* Buffer memory after meta data has to be reinterpreted as payload address */
				poCanRxBuffer->aru8Data = (uint8_t*) (poCanRxBuffer + 1);
				/*lint +e9087*/
			    /*lint -e9087*/ /* MISRA_2012_REQ_11.3 : 1st and 2nd arguments of MEMCPY are of types (uint8_t*).
			                     * They are implicitly cast to (void*). The memory is packed because it is uint8_t so there should be no problem to copy.*/
				MEMCPY(poCanRxBuffer->aru8Data, apData, au16MsgLength);
				/*lint +e9087*/
			}

            restoreint(Bap_u8IRQState);

#ifdef BAP_RUNTIME_TEST
            BAP_RUNTIME_TEST_RECEIVE_STOP();
#endif /* BAP_RUNTIME_TEST */

        }
    }
    return;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


/*  Diese Funktion ist in bap_bclbus.h dokumentiert */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_BCL_CanTxBufferWrite(BapCanTxRomRow_pot apoBusTxRomRow)
{
    DBGVAR uint16_t u16MapCanIdByLsgTableIdx; /* Hilfsvariable fuer Algorithmus (MISRA-2004)*/

    u16MapCanIdByLsgTableIdx = BAP_InhibitRomTable[apoBusTxRomRow->u8InhibitIndex].u16MapCanIdByLsgTableIndex +
            Bap_u8TxRomRowBufferWritePos[apoBusTxRomRow->u8InhibitIndex];

    /* Wenn kein doppelter Eintrag gefunden wurde und die Schreibposition ein Leerstelle ist, wird der Pointer in den Buffer übernommen */
    if((NULL == Bap_poCanTxRingBuffer[u16MapCanIdByLsgTableIdx].poCanTxRomRow) &&
            (BAP_FALSE == apoBusTxRomRow->poBclTxRamRow->flags.fTxSendBufferFlag))
    {
        apoBusTxRomRow->poBclTxRamRow->flags.fTxSendBufferFlag = BAP_TRUE;
        Bap_poCanTxRingBuffer[u16MapCanIdByLsgTableIdx].poCanTxRomRow = apoBusTxRomRow;
        Bap_u8TxRomRowBufferWritePos[apoBusTxRomRow->u8InhibitIndex] = (Bap_u8TxRomRowBufferWritePos[apoBusTxRomRow->u8InhibitIndex] + (uint8_t)1)
                                % BAP_InhibitRomTable[apoBusTxRomRow->u8InhibitIndex].u8MapCanIdByLsgSize;
        ++Bap_u8CanTxBufferLength[apoBusTxRomRow->u8InhibitIndex];
    }
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


/*  Diese Funktion ist in bap_bclbus.h dokumentiert */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_IMPL_FAR BapCanTxRomRow_pot
BAP_BCL_CanTxBufferRead(uint8_t u8InhibitIndex)
{
    DBGVAR uint16_t u16MapCanIdByLsgTableIdx; /* Hilfsvariable fuer Algorithmus (MISRA-2004)*/
    BapCanTxRomRow_pot poBusTxRomRow = NULL; /* Zwischenspeicher zur Rueckgabe */

    /* Uberprüfung auf Längenangabe in u8MapCanIdByLsgSize dient zur Vermeidung einer exception durch Modulo-Operator */
    if (0u < BAP_InhibitRomTable[u8InhibitIndex].u8MapCanIdByLsgSize)
    {
        u16MapCanIdByLsgTableIdx = BAP_InhibitRomTable[u8InhibitIndex].u16MapCanIdByLsgTableIndex +
                Bap_u8TxRomRowBufferReadPos[u8InhibitIndex];

        if (NULL != Bap_poCanTxRingBuffer[u16MapCanIdByLsgTableIdx].poCanTxRomRow)
        {
            /* Wenn Daten im Buffer enthalten sind dann Pointereintrag uebernehmen und ... */
            poBusTxRomRow = Bap_poCanTxRingBuffer[u16MapCanIdByLsgTableIdx].poCanTxRomRow;

            /* ...Speicherbereich freigeben, Lesezeiger Inkrementieren und Bufferlaenge dekrementieren  */
            Bap_poCanTxRingBuffer[u16MapCanIdByLsgTableIdx].poCanTxRomRow->poBclTxRamRow->flags.fTxSendBufferFlag = BAP_FALSE;
            Bap_poCanTxRingBuffer[u16MapCanIdByLsgTableIdx].poCanTxRomRow = NULL;
            Bap_u8TxRomRowBufferReadPos[u8InhibitIndex] = (Bap_u8TxRomRowBufferReadPos[u8InhibitIndex] + (uint8_t)1)
                                    % BAP_InhibitRomTable[u8InhibitIndex].u8MapCanIdByLsgSize;
            --Bap_u8CanTxBufferLength[u8InhibitIndex];
        }
    }
    return poBusTxRomRow;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


/*  Diese Funktion ist in bap_bclbus.h dokumentiert */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_IMPL_FAR void BAP_BCL_CanTxBufferInit(BapLsgRomRow_pot apoLsgRomRow)
{
    DBGVAR uint8_t u8InhibitIdx; /* Index zum Hochzaehlen der PDU-ID*/
    DBGVAR uint8_t u8BufferIdx; /* Index zum Hochzaehlen der Sendebuffer-Eintraege */
    DBGVAR uint8_t u8CanIdBufferLength; /* Zum Zwischenspeichern der Bufferlaenge */
    DBGVAR BapCanTxRomRow_pot poCanTxRomRow; /* Pointer zum Zwischenspeichern */

    /* for-Schleife zum Suchen und Loeschen von LSG Einträgen innerhalb der einzelnen CAN Buffer Sendebereiche */
    for (u8InhibitIdx = (uint8_t)0; u8InhibitIdx < BAP_CAN_TX_SEGMENTATION_CHANNELS; u8InhibitIdx++)
    {
        u8CanIdBufferLength = Bap_u8CanTxBufferLength[u8InhibitIdx];

        for(u8BufferIdx = (uint8_t)0; (u8CanIdBufferLength > u8BufferIdx); u8BufferIdx++)
        {
            poCanTxRomRow = BAP_BCL_CanTxBufferRead(u8InhibitIdx);

            if ((NULL != poCanTxRomRow) && (poCanTxRomRow->poFctRomRow->lsgId != apoLsgRomRow->lsgId))
            {
                BAP_BCL_CanTxBufferWrite(poCanTxRomRow);
            }
        }
    }
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>
