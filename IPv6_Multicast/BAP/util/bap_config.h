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
 *  Diese Datei enthaelt die Datentypen und Schnittstellen auf
 *  die konfigurierten Daten des Bedien- und Anzeigeprotokolls
 *  welche alle Schichten betreffen.
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
 * 2018-11-27   1.10.3      ODD         [SSWCCB-2490] Integration von BAP 1.9.0.4 in Mainbranch
 * 2017-06-27   1.9.0.3     FST         [SSWCCB-1545] SSW-Lokatierungs-Pragmas eingefuegt
 * 2016-10-10   1.8.1       FST         [SSWCCB-2410] Softwareschalter DLL_COMPILATION zur Unterscheidung
 *                                      der Erzeugung von Steuergeraete-Code und der BAP-Dll eingefuegt
 * 2014-12-12   1.8.0.1     WWU         [SSWCCB-2104] BapMsgPduSize_t, BapMsgPduSize_ot hinzugefuegt.
 * 2014-11-28   1.8.0.0     WWU/FST     [SSWCCB-2104] CR variable PDU-Groesse: Formataenderung der Variablen 16Bit->32Bit
 * 2014-03-21   1.7.1       WWU         Typ BapBalRamRowU8_t, BapBalRamRowU16_t, BapBalRamRowU32_t und BapBalRamRowBufferWithLength_t
 *                                      sind entfernt. Siehe Umsetzung fuer Union-Ersetzung durch Struct in bap_balutil.h.
 * 2014-03-19   1.7.1       WWU         [CCB-664] und [CCB-1731]: Ersetze aru8Buffer[MAX_BYTE_SEQUENCE_LENGTH] durch
 *                                      (*paru8Buffer)[] in Struktur BapBufferWithLength_t.
 * 2014-03-10   1.7.1       WWU         Union BapHeartbeatInfo_t wird entfernt.
 *                                      2 Element "eHeartbeatStatus" und "u8LastSentFctIndex" jetzt direkt in BapLsgRamRow_t definiert.
 * 2014-01-08   1.7.1       WWU         Die Arraylaenge ist jetzt bei extern Definition bekannt.
 *                                      Die Arraylaenge wird bei BAPgen in bap_defines.h generiert.
 * 2013-10-22   1.7.0       WWU         Anpassung wegen MISRA-2004: (ersetze Pointer durch Index)
 *                                      Element *poBusTxTable und *poBusRxTable in Struktur BapFctRomRow_ot
 *                                      werden durch u16BusTxTableIndex, u16BusRxTableIndex ersetzt.
 * 2013-10-14   1.7.0       WWU         Anpassung wegen Misra-2004: (ersetze Pointer durch Index)
 *                                      Element paru8BAPConfigTable in Struktur BapLsgRomRow_ot durch u8BAPConfigTableIndex ersetzt
 * 2013-04-17   1.7.0       FRISA       Erweiterung des Structs BapFctRomRow_t fuer Zwischenspeicherung der Konfigurationsliste
 * 2013-03-05   1.7.0       WWU         Misra-2004 fix
 * 2007-08-28   1.5         ALI         u8BAPConfigTableSize nun auch fuer FSG lesbar wegen MultiConfig
 * 2007-08-28   1.5         ALI         BapLayerLsgStat_WaitForConfig zu BapLayerLsgStat_WaitForOrInvalidConfig, da FSG
 *                                      den Zustand fuer eine InvalidConfig benoetigt.
 * 2007-08-16   1.5         ALI         Durch ein Alignment-Problem wurde BapBalRamRowUx_t eingefuehrt
 *                                      und struct BapBalRamRow_t zu union BapBalRamRow_t geaendert.
 * 2006-04-12   1.4         ALA         Unterstuetzung fuer BAP_ROM_DATA_FAR.
 * 2005-03-14   1.4         ALA         Unterstuetzung bis zu 255 kompatiblen BAPConfig Versionen
 * 2004-11-17   1.2         JOK         Anpassung der Strukturen an die optimierten Konfigurationstabellen
 * 2004-09-17   1.1.1       ALA         Defines von internen FctIds nach bap_types.h verschoben, da diese
 *                                      auch in der Applikation benoetigt werden.
 * 2004-06-07   1.1         JOK         Compilerschalter fuer SG-Typen zur Optimierung
 *                                      des ROM-Bedarfs eingefuegt
 * 2004-06-07   1.1         JOK         Datentyp BapDt_FixedByteSequence eingefuegt
 * 2004-06-07   1.1         JOK         Enumeration BapSGType_t entfernt
 * 2004-06-07   1.1         JOK         Variable u8TaskTimeMs zur Berechnung der Anzahl-Tasks
 *                                      anhand der Absolutzeit eingefuegt
 * 2004-06-07   1.1         JOK         Variable fuer die Heartbeat-Zeit von 16 auf 8 Bit geaendert.
 *                                      Die Zeit ist nun statt in Anzahltasks in 100ms angegeben.
 *                                      In kleinen SGs kann damit auf den Datentyp 16 Bit verzichtet werden.
 ******************************************************************/

#ifndef BAP_CONFIG_H
#define BAP_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Systemincludes mit <...> */

/* Bibliotheken von externen Herstellern mit <...> */

/* Eigene Header-Dateien "..." */
#include "bap_types.h"
#include "bap_privatetypes.h"

/* Makro-Definitionen */

/** Konstante fuer die maximale Laenge einer ByteSequenz */
#define BAP_MAX_BYTE_SEQUENCE_LENGTH	((uint32_t) 4094) /* [FST] Ist anzupassen anhand Maximallaenge aus Funktionskatalog */

/** Konstante fuer die Laenge von BAPCONFIG */
#define BAP_FCTID_BAPCONFIG_SIZE	((uint16_t)6)

/** Konstante fuer die Position von BAPVersion Major */
#define BAP_BAPCONFIG_POS_PV_MAJOR ((uint8_t)0)

/** Konstante fuer die Position von BAPVersion Minor */
#define BAP_BAPCONFIG_POS_PV_MINOR ((uint8_t)1)

/** Konstante fuer die Position von SG-Klasse Major */
#define BAP_BAPCONFIG_POS_SG_MAJOR ((uint8_t)2)

/** Konstante fuer die Position von SG-Klasse Minor */
#define BAP_BAPCONFIG_POS_SG_MINOR ((uint8_t)3)

/** Konstante fuer die Position von Datenfestlegung Major */
#define BAP_BAPCONFIG_POS_DF_MAJOR ((uint8_t)4)

/** Konstante fuer die Position von Datenfestlegung Minor */
#define BAP_BAPCONFIG_POS_DF_MINOR ((uint8_t)5)

/** Konstante fuer die reservierte LsgID */
#define BAP_RESERVED_LSG_ID 0

/** Konstante fuer die groesst moegliche LsgID */
#define BAP_MAX_LSG_ID 63

/** Konstante fuer die groesst moegliche FctID */
#define BAP_MAX_FCT_ID 63

/* 2014-12-12 WWU: definiere Headerlaenge fuer alt/neu Format*/
#define BAP_FIRST_HEADER_BYTE ((uint8_t) 0)
#define BAP_SECOND_HEADER_BYTE ((uint8_t) 1)
#define BAP_HEADER_BYTES_NONSEG ((uint8_t) 2)
#define BAP_HEADER_BYTES_SEG_OLD ((uint8_t) 4)	  /* Alt Format fuer segmentierte Botschaft, 4 Bytes */
#define BAP_HEADER_BYTES_SEG_NEW ((uint8_t) 8)    /* Neu Format fuer segmentierte Botschaft, 8 Bytes */
#define BAP_HEADER_BYTES_SEG_DATA ((uint8_t) 1)    /* Nachfolgende segmentierte Datenbotschaften, 1 Byte */
#define BAP_PDU_HEADER_BYTES_SEG_DATA ((uint16_t) 2)    /* Headergroesse nachfolgender segmentierter Datenbotschaften in PDU, 2 Bytes */

/** Konstante fuer die maximale PDU Groesse die im alten Format uebertragen werden kann */
#define BAP_MAX_PDU_SIZE_OLD_FORMAT ((uint16_t) 8u)

/** Konstante fuer die minimale Groesse einer segmentierten Startbotschaft */
#define BAP_MIN_SEG_STARTMSG_SIZE ((uint16_t) 4u)

/** Konstante fuer die erweiterte Nachrichtenlaenge einer segmentierten Botschaft */
#define BAP_EXTENDED_MSG_SIZE ((uint16_t)4095u)

/** Konstante fuer die Groesse des Headers einer Botschaft im alten Format */
#define BAP_OLD_SEG_STARTMSG_HEADER_SIZE ((uint8_t)2)

/** Konstante fuer die Groesse des Headers einer Botschaft mit erweiterter Nachrichtenlaenge */
#define BAP_EXTENDED_SEG_STARTMSG_HEADER_SIZE ((uint8_t)6)

/**
 * Startposition des Opcode in Headerbyte2 der segmentierten Startmessage oder
 * Headerbyte0 der nicht segmentierten Startmessage
 */
#define BAP_OPCODE_POS ((uint8_t) 4)

/**
 * Startposition der LsgID in Headerbyte2 verschoben nach Headerbyte3 der segmentierten Startmessage
 * oder in Headerbyte0 verschoben nach Headerbyte1 der nicht segmentierten Startmessage
 */
#define BAP_LSGID_POS_IN_FIRSTBYTE ((uint8_t) 2)

/**
 * Startposition des LsgID in Headerbyte3 der segmentierten Startmessage
 * oder in Headerbyte1 der nicht segmentierten Startmessage
 */
#define BAP_LSGID_POS_IN_SECONDBYTE ((uint8_t) 6)


/* Typ-Definitionen */

#define BAP_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* definiert und dokumentiert in bap_balconfig.h */
struct BapBalRamRow_t;

/* definiert und dokumentiert in bap_bplconfig.h */
struct BapBplRamRow_t;

/* definiert und dokumentiert in bap_bclconfig.h */
struct BapCanRxRomRow_t;

/* definiert und dokumentiert in bap_bclconfig.h */
struct BapCanTxRomRow_t;

/* definiert und dokumentiert in bap_bclconfig.h */
struct BapBusIndirectionRxRomRow_t;

/* definiert und dokumentiert in bap_bclconfig.h */
struct BapBusIndirectionTxRomRow_t;

#define BAP_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/**
 *  Zeiger auf BapBalRamRow_ot
 */
typedef DBGVAR struct BapBalRamRow_t * BapBalRamRow_pot;

/**
 *  Definiert einen Zeiger auf BapBplRamRow_ot im RAM
 */
typedef DBGVAR struct BapBplRamRow_t * BapBplRamRow_pot;

/**
 *  Definiert einen Zeiger auf BapCanTxRomRow_ot im ROM
 */
typedef BAP_ROM_DATA_FAR const struct BapCanTxRomRow_t * BapCanTxRomRow_pot;

/**
 * Definiert einen Zeiger auf BapCanRxRomRow_ot im ROM
 */
typedef BAP_ROM_DATA_FAR const struct BapCanRxRomRow_t * BapCanRxRomRow_pot;

/**
 *  Definiert einen Zeiger auf BapBusIndirectionRxRomRow_ot im ROM
 */
typedef BAP_ROM_DATA_FAR const struct BapBusIndirectionRxRomRow_t * BapBusIndirectionRxRomRow_pot;

/**
 *  Definiert einen Zeiger auf BapBusIndirectionTxRomRow_ot im ROM
 */
typedef BAP_ROM_DATA_FAR const struct BapBusIndirectionTxRomRow_t * BapBusIndirectionTxRomRow_pot;

/**
 * Enthaelt eine Bitmaske welche Arten von OpCodes beim Senden erlaubt sind.
 * Die Bedeutung der einzelnen Bits sind die Zweierpotenz der
 * Werte der Enumeration BapOpCodes_t.
 */
typedef uint8_t BapOpCodeSendMask_t;

/**
 * Enthaelt eine Bitmaske welche Arten von OpCodes beim Empfangen erlaubt sind.
 * Die Bedeutung der einzelnen Bits sind die Zweierpotenz der
 * Werte der Enumeration BapOpCodes_t.
 */
typedef uint8_t BapOpCodeReceiveMask_t;


/**
 * Zustand einer Schicht des BAP-Stacks pro LSG
 */
typedef enum BapLayerLsgStatus_t
{
    /**
     * Initial-Zustand eines LSG nach dem Hochfahren
     */
    BapLayerLsgStat_NoInit = 0,

    /**
     * Zustand des LSG nach BAP_Init() oder BAP_Shutdown()
     */
    BapLayerLsgStat_Initialized = 1,

    /**
     * Unterschiedliche Bedeutung, je nachdem ob ASG oder FSG.
     *
     * Zustand des ASG nach BAP_Start() und noch nicht erfolgter Versionpruefung.
     * Diesen Zustand gibt es nur im ASG, da hier die Versionspruefung stattfindet.
     * Das FSG wechselt nach BAP_Start() sofort in BapLayerLsgStat_Running.
     *
     * Zustand des FSG nach BAP_Init() oder BAP_Shutdown(), fals die Applikation eine
     * nicht vorhandene BAPConfig angibt. Hier ist kein BAP_Start() moeglich. Der
     * Zustand kann nur ueber eine gueltige BAPConfig oder ein BAP_Shutdown() verlassen
     * werden.
     */
    BapLayerLsgStat_WaitForOrInvalidConfig = 2,

     /**
     * Zustand des LSG im laufenden Betrieb
     */
    BapLayerLsgStat_Running = 3


} BapLayerLsgStatus_et;


#if defined(BAP_ASG) && defined(BAP_FSG)
/**
 * Gibt fuer die BAP-Konfiguration ASG+FSG den Steuergeraetetyp des jeweiligen LSG an.
 */
typedef enum BapSGType_t
{
    /**
     * Bei dem Steuergeraet handelt es sich um ein Anzeigesteuergeraet
     */
    BapSG_ASG = 0,

    /**
     * Bei dem Steuergeraet handelt es sich um ein Funktions- oder Bediensteuergeraet
     */
    BapSG_FSG
} BapSGType_et;
#endif /* #if defined(BAP_ASG) && defined(BAP_FSG) */


/**
 * Enthaelt ein Bytearray mit u32Length Bytes
 */
typedef struct BapBufferWithLength_t
{
    /**
     * Die Anzahl an gueltigen Bytes in aru8Buffer.
     * Muss kleiner sein als der vom Konfigurationstool
     * reservierte Speicher, der kleiner oder gleich
     * BAP_MAX_BYTE_SEQUENCE_LENGTH ist.
     */
    uint32_t u32Length;

    /**
     * Enthaelt die Bytes der Byte-Sequenz. Gueltig sind
     * allerdings nur u32Length Bytes. Auf nachfolgende Bytes
     * darf nicht lesend zugegriffen werden.
     * Schreibender Zugriff ist nur unter Pruefung der konfigurierten
     * reservierten Laenge erlaubt.
     */
    paru8Buffer_t  paru8Buffer;
} BapBufferWithLength_ot;

/** Zeiger auf das Bytearray BapBufferWithLength_t */
typedef DBGVAR struct BapBufferWithLength_t * BapBufferWithLength_pot;


#ifdef BAP_ASG
/**
 * Zustand einer FunktionsID (Datenzeile) im BAL Cache
 */
typedef enum BapBalDataStatus_t
{
    /**
     * Die Daten im Cache sind ungueltig
     */
    BapBalDataStat_Invalid,
    /**
     * Die Daten im Cache sind gueltig
     */
    BapBalDataStat_Valid,
    /**
     * Die Daten sind gueltig, es findet aber derzeit ein GetAll statt
     * Es ist aber moeglich durch HB & Status in den Valid Zustand
     * waehrend GetAll zu kommen
     */
    BapBalDataStat_GetAll
} BapBalDataStatus_et;
#endif /* #ifdef BAP_ASG */


/**
 *  Zustaende der Heartbeatueberwachung bei ASG
 */
typedef enum BapBplStatus_t
{
    /**
     *  Bedeutung bei ASG:
     *  Frisch initialisiert, gestartet und noch
     *  kein Heartbeat-Takt empfangen
     *
     *  Bedeutung bei FSG:
     *  Frisch initialisiert.
     */
    BapBplStat_Stopped,

    /**
     *  Verbindung zu dem LSG ist OK
     */
    BapBplStat_OK,

    /**
     *  Es gab eine Zeitueberschreitung beim
     *  Empfangen von Nachrichten des LSG
     */
    BapBplStat_Timeout
} BapBplStatus_et;


/**
 *  Beschreibt die unterstuetzten Datentypen vom BAL
 */
typedef enum BapDataType_t
{
    /**
     *  Datenelement ohne Wert. Mit diesem Datenelement ist nur der
     *  Aufruf von BAP_RequestVoid erlaubt.
     *
     *  Wird u.a. verwendet, wenn bei Properties nur ein BapReq_DataGet
     *  erlaubt ist, aber z.B. kein DataReq_DataSetGet benoetigt wird.
     *
     *  @remarks Der Zahlenwert wird im Code auch als Datengroesse verwendet
     */
    BapDt_Void=0,

    /**
     *  Datenelement ist ein ganzzahliger Wert mit 8 Bit Genauigkeit
     *  ohne Vorzeichen
     *
     *  @remarks Der Zahlenwert wird im Code auch als Datengroesse verwendet
     */
    BapDt_Int8=1,

#ifdef BAP_USES_DATATYPE_16
    /**
     *  Datenelement ist ein ganzzahliger Wert mit 16 Bit Genauigkeit
     *  ohne Vorzeichen
     *
     *  @remarks Der Zahlenwert wird im Code auch als Datengroesse verwendet
     */
    BapDt_Int16=2,
#endif

#ifdef BAP_USES_DATATYPE_32
    /**
     *  Datenelement ist ein ganzzahliger Wert mit 32 Bit Genauigkeit
     *  ohne Vorzeichen
     *
     *  @remarks Der Zahlenwert wird im Code auch als Datengroesse verwendet
     */
    BapDt_Int32=4,
#endif

#ifdef BAP_USES_SEGMENTATION
    /**
     *  Datenelement ist eine untypisierte Byte-Sequenz mit Laengenangabe.
     *  Die maximale Laenge ist kleiner oder gleich BAP_MAX_BYTE_SEQUENCE_LENGTH.
     *  Es duerfen kuerzere Laengen versendet werden wie konfiguriert.
     */
    BapDt_ByteSequence=5,
#endif

    /**
     *  Datenelement ist eine untypisierte Byte-Sequenz mit Laengenangabe.
     *  Die maximale Laenge ist kleiner oder gleich BAP_MAX_BYTE_SEQUENCE_LENGTH.
     *  Im Gegensatz zu BapDt_ByteSequence muss immer exakt die konfigurierte
     *  Laenge versendet werden. Kuerzere Laengen sind nicht erlaubt.
     *  Wird fuer unsegmentierte Uebertragung von Bytesequenzen verwendet.
     */
    BapDt_FixedByteSequence=6,


    /**
     *  Datenelement ist kein Wert. Datenrichtung ist nicht konfiguriert.
     */
    BapDt_None=7
} BapDataType_et;


/**
 *  Enthaelt die ROM Konfiguration fuer alle Schichten je Funktions-ID
 */
#ifdef DLL_COMPILATION
typedef DBGVAR struct BapFctRomRow_t
#else
typedef DBGVAR BAP_ROM_DATA_FAR const struct BapFctRomRow_t
#endif /* DLL_COMPILATION */
{
    /**
     * Die LsgID auf die sich diese ROM Zeile bezieht.
     */
    lsgId_t lsgId;

    /**
     * Die FunctionID auf die sich diese ROM Zeile bezieht.
     */
    fctId_t fctId;

    /**
     * Die Funktionsklasse zu der die FunctionID gehoert.
     */
    BapFunctionClass_et eFunctionClass;

    /**
     * Maske der erlaubten OpCodes beim Senden.
     */
    BapOpCodeSendMask_t u8OpCodeSendMask;

    /**
     * Maske, der erlaubten OpCodes beim Empfangen.
     */
    BapOpCodeReceiveMask_t u8OpCodeReceiveMask;

    /**
     * Datentyp in Empfangsrichtung, der in dieser FunctionID verarbeitet wird.
     */
    BapDataType_et eRxDataType;

    /**
     * Groesse des Datentyps in Bytes in Empfangsrichtung. Fuer die Datentypen
     * BapDt_Int8 immer 1, BapDt_Int16 immer 2, BapDt_Int32 immer 4,
     * und BapDt_FixedByteSequence oder BapDt_ByteSequence
     * kleiner gleich BAP_MAX_BYTE_SEQUENCE_LENGTH
     */
    uint32_t u32RxSize;

    /**
     * Datentyp in Senderichtung, der in dieser FunctionID verarbeitet wird.
     */
    BapDataType_et eTxDataType;

    /**
     * Groesse des Datentyps in Bytes in Senderichtung. Fuer die Datentypen
     * BapDt_Int8 immer 1, BapDt_Int16 immer 2, BapDt_Int32 immer 4,
     * und BapDt_FixedByteSequence oder BapDt_ByteSequence
     * kleiner gleich BAP_MAX_BYTE_SEQUENCE_LENGTH
     */
    uint32_t u32TxSize;

    /**
     * Zeigt auf den RAM Bereich fuer diese FunctionID.
     * NULL zeigt an, dass fuer diese FunctionID kein Cache vorhanden ist.
     */
    BapBalRamRow_pot poBalRamRow;

    /** True und eDirection = BapDir_Source:
     *  Datenelement nimmt am zyklischen HB Senden teil
     */
    bool_t bHeartbeatOn;

    /** Maximale Anzahl an Wiederholungen fuer dieses LSG */
    uint8_t nMaxRetryCounter;

    /** Taskzaehler fuer Zeitueberwachung, rueckwaerts zaehlend */
    uint16_t nMaxRetryOrProcessingTime;

    /** zeigt auf eine Zeile im RAM */
    BapBplRamRow_pot poBplRamRow;

    /** Enthaelt die Anzahl der Zeilen in der BAP_BusIndTxTable fuer diese FctId */
    uint8_t u8TxTableSize;

    /**
     * Index von Tx Eintrag in BAP_BusIndTxTable fuer diese FctId.
     * Index 65535 bedeutet keine Eintrag in BusTxTable.
     */
    uint16_t u16BusTxTableIndex;

    /** Enthaelt die Anzahl der Zeilen in der BAP_BusIndRxTable fuer diese FctId */
    uint8_t u8RxTableSize;

    /**
	 * Index von Rx Eintrag in BAP_BusIndRxTable fuer diese FctId.
	 * Index 65535 bedeutet keine Eintrag in BusRxTable.
	 */
	uint16_t u16BusRxTableIndex;
} BapFctRomRow_ot;

/**
 *  Zeiger auf ein BapFctRomRow_t im ROM
 */
typedef DBGVAR BAP_ROM_DATA_FAR const struct BapFctRomRow_t * BapFctRomRow_pot;


/**
 * Enthaelt Flags, welche angeben, ob etwas zu Senden ist oder
 * etwas empfangen wurde
 */
typedef struct BapLsgState_t
{
    /**
     * Gibt an, dass dieses logische Steuergeraet bei der Auswertung der Tx-Flags
     * beruecksichtigt werden muss.
     * @deprecated - wird in BAP 1.4 nicht mehr genutzt. Fuer CAN werden stattdessen die BapHeuristikFlags_t genutzt.
     */
    bitfield_t fTxFlag:1;

    /**
     * Wird als Zwischenspeicher bei der CAN Heuristik benoetigt.
     */
    bitfield_t fTxCanRequestFound:1;

    /**
     * Gibt an, dass dieses logische Steuergeraet bei der Auswertung der Rx-Flags
     * beruecksichtigt werden muss.
     */
    bitfield_t fRxFlag:1;

    /**
     * Gesamtgueltigkeit des Caches
     */
    bitfield_t fCacheValid:1;

    /**
     * Beschreibt, ob in diesem Lsg gerade eine Retry-Ueberwachung oder ein
     * Processing Timer laeuft.
     */
    bitfield_t fRetryProcessingActive:1;

    /** Reserviert fuer zukuenftige Erweiterungen */
    bitfield_t fUnused1:1;

    /** Reserviert fuer zukuenftige Erweiterungen */
    bitfield_t fUnused2:1;

    /** Reserviert fuer zukuenftige Erweiterungen */
    bitfield_t fUnused3:1;
} BapLsgState_ot;

/**
 *  Zeiger auf ein BapLsgState_ot
 */
typedef DBGVAR struct BapLsgState_t * BapLsgState_pot;

/**
 * Stati aller Schichten, welche das LSG betreffen
 */
typedef DBGVAR struct BapLsgRamRow_t
{
    /**
     *  Enthaelt den Status fuer das logische Steuergeraet
     */
    BapLayerLsgStatus_et eLsgStatus;

    /**
     *  Rueckwaerts zaehlender Heartbeat-Timer.
     *  Bei FSG: Timer zum Versenden von Heartbeat-Nachrichten
     *  Bei ASG: Ueberwachungstimer beim Empfang von HB-Nachrichten
     */
    uint16_t u16HeartbeatTimer;

    /**
     *  Enthaelt den Zustand der Heartbeat-Ueberwachung.
     *  @remarks
     *  Nur bei ASG relevant.
     */
    BapBplStatus_et eHeartbeatStatus;

    /**
     *  Enthaelt den Index in der BAP_BplRomTable der Function, die zuletzt versendet wurde.
     *  Wird nach einem Durchlauf auf 0 gesetzt, da diese FctId reserviert ist,
     *  braucht sie auch nicht versendet zu werden.
     *
     *  @remarks
     *  Nur bei FSG relevant.
     */
    uint8_t u8LastSentFctIndex;

	/**
     * Enthaelt die momentan aktive Konfigurationliste des FSG
     */
    uint8_t BapBAPConfig_t[BAP_FCTID_BAPCONFIG_SIZE];
	
    /**
     * Enthaelt die momentan aktive Funktionsliste des ASG bzw. FSG
     */
    uint8_t BAP_aru8FunctionList[BAP_FCTID_FCTLIST_SIZE];

    /**
     * Enthaelt Flags, welche angeben, ob etwas zu Senden ist oder
     * etwas empfangen wurde
     */
    BapLsgState_ot fState;
} BapLsgRamRow_ot;

/*
 * Struct fuer das Mapping der CAN-Message-Ids zu LsgIds
 */
typedef struct BapCanMsg2LsgMapping_t
{
	BapCanMsgId_t CanMessageId;
	lsgId_t LsgId;
} BapCanMsg2LsgMapping_ot;

/*
 * Struct fuer das Mapping der CAN-Message-Ids zu LsgIds
 */
#ifdef DLL_COMPILATION
typedef struct BapMsgPduSize_t
#else
typedef const struct BapMsgPduSize_t
#endif /* #ifdef DLL_COMPILATION */
{
	BapCanMsgId_t CanMessageId;
	uint16_t pduSize;
} BapMsgPduSize_ot;

/**
 *  Zeiger auf eine RAM Zeile auf struct BapLsgRamRow_t
 */
typedef DBGVAR struct BapLsgRamRow_t * BapLsgRamRow_pot;

/**
 *  Konstanter Zeiger auf eine RAM Zeile auf struct BapLsgRamRow_t
 */
typedef DBGVAR const struct BapLsgRamRow_t * BapLsgRamRow_cpot;



/**
 * Liste der Elemente der Funktions-Id 2, BAP_CONFIG
 * @remarks
 * Bedeutung der Indizes:
 * 0 BAP Version Major          - BAP_BAPCONFIG_POS_PV_MAJOR
 * 1 BAP Version Minor          - BAP_BAPCONFIG_POS_PV_MINOR
 * 2 Steuergeraete Klasse Major - BAP_BAPCONFIG_POS_SG_MAJOR
 * 3 Steuergeraete Klasse Minor - BAP_BAPCONFIG_POS_SG_MINOR
 * 4 Datenfestlegung Major      - BAP_BAPCONFIG_POS_DF_MAJOR
 * 5 Datenfestlegung Minor      - BAP_BAPCONFIG_POS_DF_MINOR
 */
typedef uint8_t BapBAPConfig_t[BAP_FCTID_BAPCONFIG_SIZE];

/**
 * Zeiger auf ROM Tabelle BapBAPConfig_t
 */
#ifdef DLL_COMPILATION
typedef BapBAPConfig_t * BapBAPConfig_pt;
#else
typedef BAP_ROM_DATA_FAR const BapBAPConfig_t * BapBAPConfig_pt;
#endif /* DLL_COMPILATION */
/**
 *  Gibt Zugriff auf ROM Tabellen und die LSG RAM Tabellen
 *  der einzelnen Schichten ueber die LSG ID.
 */
#ifdef DLL_COMPILATION
typedef DBGVAR struct BapLsgRomRow_t
#else
typedef DBGVAR const struct BapLsgRomRow_t
#endif /* DLL_COMPILATION */
{
    /**
     * Beschreibt, fuer welches LSG diese Zeile gilt
     */
    lsgId_t lsgId;


    /**
     * Anzahl der Elemente in poBAPConfigTable fuer dieses LSG
     *
     */
    uint8_t u8BAPConfigTableSize;

    /**
     * Index der BAPConfig fuer aktulle LSG in BAPConfigTable
     * ASG: nur Anfangsindex, weil ASG mehrer BAPConfig unterstuetzen koennen
     * FSG: nur eine Eintrag
     */
    uint8_t u8BAPConfigTableIndex;

    /**
     * Liste der unterstuetzten Function Identifier
     * FSG: zur Verfuegung gestellte FctIds
     * ASG: Defaultmaessig unterstuetze  FctIds (falls noch kein FctList/FctId 3 empfangen wurde)
     */
#ifdef DLL_COMPILATION
    uint8_t BAP_aru8FunctionList[BAP_FCTID_FCTLIST_SIZE];
#else
    const uint8_t BAP_aru8FunctionList[BAP_FCTID_FCTLIST_SIZE];
#endif /* DLL_COMPILATION */
    /**
     * Zeiger auf den Wert des HeartBeat-Timers in Anzahl Task-Aufrufe.
     * Die Heartbeat-Zeit des FSG wird mit 100ms multipliziert und durch die
     * BAP_Task-Zeit (jeweils des FSGs/ASGs) in ms dividiert.
     * Beim ASG wird zusaetzlich der HB-Faktor multipliziert.
     */
    uint16_t *pu16HeartbeatTimer;

    /**
     * Zykluszeit in Millisekunden mit der ein Task-Aufruf stattfindet.
     */
    uint8_t u8TaskTimeMs;

    /**
     * Heartbeat-Zeit oder Faktor je nach SG-Typ
     * FSG: Zeit in 100ms Schritten mit der Heartbeats ausgesendet werden
     * ASG: Faktor mit dem die empfangene HB-Zeit des FSG multipliziert
     *      werden soll fuer die HB-Ueberwachung.
     */
    uint8_t u8Heartbeat;

    /**
     * Anzahl der Elemente in poFctRomTable fuer dieses LSG
     */
    uint8_t u8FctRomTableSize;

    /**
     *  Index auf die erste Funktion im ROM fuer dieses LSG
     */
    uint16_t u16FctRomIndex;

    /**
     * Anzahl der Elemente in poCanRxRomTable fuer dieses LSG,
     * 0 falls dieses Steuergeraet nicht den BCL CAN nutzt.
     */
    uint16_t u16CanRxRomTableSize;


    /** Index auf BCL CanRx Tabelle im ROM
     *  fuer dieses LSG bzw. 65535 falls kein BCL CAN verwendet
     *  wird.
     */
    uint16_t u16CanRxRomTableIndex;

    /** Falls diese Spalte BAP_TRUE ist, dann wird beim Senden
     *  immer die Laenge 8 an BAP_CANUBS_TxData uebergeben.
     *
     *  Falls die Spalte BAP_FALSE ist, dann wird beim Senden
     *  immer die aktuelle Laenge an BAP_CANUBS_TxData uebergeben.
     *
     *  @remarks:
     *  Dadurch ist es moeglich, je Lsg festzulegen, ob es kompatibel zu BAP 1.1
     *  mit fester DLC-Laenge = 8 oder kompatibel zu BAP 1.2 mit variablem DLC sein soll.
     */
    bool_t bUseDLC8;

#if defined(BAP_ASG) && defined(BAP_FSG)
    /**
     * Gibt an, ob es sich bei dem Steuergeraet um ein ASG oder ein FSG handelt.
     * Diese Spalte wird nur verwendet, wenn ASG+FSG zusammen in einem Steuergeraet vorhanden sind.
     */
    BapSGType_et eSGType;
#endif /* #if defined(BAP_ASG) && defined(BAP_FSG) */

    /**
     * Zeiger auf die Zeile im RAM, die die Zustaende dieses LSG enthalten
     */
    BapLsgRamRow_pot poLsgRamRow;

   /**
     * Anzahl der Elemente in poCanTxRomTable fuer dieses LSG,
     * 0 falls dieses Steuergeraet nicht den BCL CAN nutzt.
     */
    uint16_t u16CanTxRomTableSize;

    /** Index auf BCL CanTx Tabelle im ROM
     *  fuer dieses LSG bzw. 65535 falls kein BCL CAN verwendet
     *  wird.
     */
    uint16_t u16CanTxRomTableIndex;

    bool_t bNewLsgId;

} BapLsgRomRow_ot;

/**
 *  Definiert einen Zeiger auf BapLsgRomRow_ot im ROM
 */
typedef DBGVAR BAP_ROM_DATA_FAR const struct BapLsgRomRow_t * BapLsgRomRow_pot;

/**
 *  Gemeinsame Parameterliste fuer interne Funktionen.
 *
 *  @remarks:
 *  Dient der Optimierung des Stackframes und Reduzierung von Suchvorgaengen.
 */
typedef DBGVAR struct BapInternalParameters_t
{
    /** Enthaelt die LSG-ID oder 0 */
    lsgId_t lsgId;

    /** Enthaelt die FCT-ID oder 0 */
    fctId_t fctId;

    /** Zeigt auf das aktuelle LSG oder NULL, falls kein LSG zugeordnet werden kann */
    BapLsgRomRow_pot poLsgRomRow;

    /** Zeigt auf die aktuelle FCT oder NULL, falls die gesuchte FCT nicht existiert */
    BapFctRomRow_pot poFctRomRow;

    /** Zeigt auf die aktuellen Daten */
    DBGVAR ptr_t pData;

    /** Enthaelt die Laenge der aktuellen Daten */
    uint32_t u32Length;

    /** Enthaelt den aktuellen OpCode */
    BapOpCodes_et eOpCode;
} BapInternalParameters_ot;

/**
 *  Definiert einen nicht konstanten Stack-Zeiger auf BapInternalParameters_ot;
 */
typedef DBGVAR struct BapInternalParameters_t * BapInternalParameters_pot;

/**
 *  Definiert einen Stack-Zeiger auf ein konstantes BapInternalParameters_ot;
 */
typedef DBGVAR const struct BapInternalParameters_t * BapInternalParameters_cpot;


/* Const Deklarationen */

/**
 *  Einsprungstabelle auf alle moeglichen Konfigurationen im Steuergeraet.
 *
 *  Im ASG kann zu einer LsgId mehrere Konfigurationen hinterlegt sein.
 *  Im FSG muss es zu jeder LsgId genau eine Konfiguration geben.
 */
#ifdef DLL_COMPILATION
#   define BAP_START_SEC_VAR_NO_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>
extern BapLsgRomRow_ot* BAP_LsgRomTables;
#   define BAP_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>
#else
#   define BAP_START_SEC_CONST_UNSPECIFIED
#   include <BAP_MemMap.h>
extern BAP_ROM_DATA_FAR BapLsgRomRow_ot BAP_ROM_CONST BAP_LsgRomTables[BAP_LSG_ROM_TABLE_ROWS];
#   define BAP_STOP_SEC_CONST_UNSPECIFIED
#   include <BAP_MemMap.h>
#endif /* DLL_COMPILATION */
/* Externe globale Variablen */

/**
 *  Einsprungtabelle auf die aktuell ausgewaehlte Konfiguration.
 *
 *  Dazu muss die LsgId in der Tabelle gesucht werden,
 *  Index und LsgId sind nicht synchron, da die Daten
 *  gepackt vorgehalten werden.
 *
 *  @remarks:
 *  Diese Tabelle liegt im RAM, die Zeiger koennen geaendert werden,
 *  nicht jedoch die Werte, auf die der Zeiger zeigt.
 *
 *  Diese Tabelle darf/sollte keine NULL-Zeiger enthalten.
 *
 *  Diese Tabelle muss vor dem Aufruf von BAP_Init initialisiert
 *  worden sein, i.d.R. macht dies der Startup-Code der C-Bibliothek.
 *
 *  Ansonsten siehe Beispiel initialization.c im Integrationsordner.
 */
#ifdef DLL_COMPILATION
#   define BAP_START_SEC_VAR_NO_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>
extern BapLsgRomRow_pot* BAP_pLsgRomTable;
extern BapFctRomRow_ot* BAP_FctRomTables;
extern BapBAPConfig_t* BAP_BAPConfigTable;
#   define BAP_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>
#else
#   define BAP_START_SEC_VAR_NO_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>
extern BapLsgRomRow_pot BAP_pLsgRomTable[BAP_P_LSG_ROM_TABLE_ROWS];
#   define BAP_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>
#   define BAP_START_SEC_CONST_UNSPECIFIED
#   include <BAP_MemMap.h>
extern BAP_ROM_DATA_FAR BapFctRomRow_ot BAP_ROM_CONST BAP_FctRomTables[BAP_FCT_ROM_TABLE_ROWS];
extern BAP_ROM_DATA_FAR const BapBAPConfig_t BAP_ROM_CONST BAP_BAPConfigTable[BAP_BAPCONFIG_TABLE_ROWS];
#   define BAP_STOP_SEC_CONST_UNSPECIFIED
#   include <BAP_MemMap.h>
#endif /* DLL_COMPILATION */

#define BAP_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <BAP_MemMap.h>

/* Deklarationen von Funktionen */

#ifdef __cplusplus
}
#endif

#endif      /* #ifndef BAP_CONFIG_H */

