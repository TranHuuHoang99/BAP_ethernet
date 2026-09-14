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
 *  Diese Datei enthaelt die Datentypen und Schnittstellen auf
 *  die konfigurierten Daten des Bedien- und Anzeigeprotokolls
 *  welche den BCL (Protokollschicht 2-4) betreffen.
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
 * 2022-02-15   1.11.3      DRH         [SSWPPB-246] Anpassung der Datenstrukturen für dyn. Rx-Ringbuffer Verwaltung
 * 2021-12-07	1.11.3		JEO			[SSWPPB-244] Release preparation, adapt Copyright date and version number.
 * 2021-03-08   1.11.3      DRH         [SSWPPB-142] Replaced magic numbers by constants
 * 2018-12-04   1.10.3      ODD         [SSWCCB-2490] Integration BAP Version 1.9.0.4 in Mainbranch 	
 * 2017-07-24   1.10.0      FHA         [SSWCCB-2391] Schnelle Suche TX-PDU
 * 2017-05-12   1.9.0.3     FST         [SSWCCB-1545] SSW-Lokatierungs-Pragmas eingefuegt
 * 2016-10-20   1.8.1       FST         [SSWCCB-2410] Softwareschalter DLL_COMPILATION zur Unterscheidung
 *                                      der Erzeugung von Steuergeraete-Code und der BAP-Dll eingefuegt
 * 2015-01-14   1.8.0.1     WWU         [SSWCCB-2104] Laenge der aru8Data in BapCanRxBuffer_t nun BAP_MAX_PDU_SIZE, statt 8.
 * 2014-11-28   1.8.0.0     WWU/FST     [SSWCCB-2105] Formataenderung der Variablen 16Bit->32Bit
 * 2014-01-08   1.7.1       WWU         Die Arraylaenge ist jetzt bei extern Definition bekannt.
 *                                      Die Arraylaenge wird bei BAPgen in bap_defines.h generiert.
 * 2013-10-22   1.7         WWU         Definiere BAP_BusIndTxTable, BAP_BusIndRxTable als globale Variable fuer MISRA-2004 Fix
 * 2007-11-07   1.5         RVE         Datentyp BapInhibitRomRow_t angepasst fuer Erweiterung, welche
 *                                      Heuristikoptimierung ermoeglicht.
 * 2006-04-12   1.4         ALA         Unterstuetzung fuer BAP_ROM_DATA_FAR.
 * 2005-04-29   1.3         ALA         Optimierung Datenstrukturen fuer Unterstuetzung von dynamischer
 *                                      Kanalvergabe bei Segmentierung. Ueberfluessige volatiles entfernt
 *                                      wegen besserer Interruptverwaltung. Verbesserte Compilerunterstuetzung.
 * 2004-11-17   1.2         JOK         Umbau der Tabellenstrukturen fuer einen optimierten Zugriff
 * 2004-11-17   1.2         JOK         Enums BapSegmentationChannel_t und BapSegmentationType_t
 *                                      zusammengefuehrt
 * 2004-06-07   1.1         JOK         Compilerschalter fuer SG-Typen zur Optimierung
 *                                      des ROM-Bedarfs eingefuegt
 * 2004-06-07   1.1         JOK         Nur noch BapSegType_None (unsegmentiert) und
 *                                      BapSegType_One (segmentiert) unterstuetzt
 * 2004-06-07   1.1         JOK         In BapCanTxRomRow_t den Eintrag u16TxCanId entfernt
 * 2004-06-07   1.1         JOK         In BapCanRxRomRow_t den Eintrag u16RxCanId entfernt
 ******************************************************************/

#ifndef BAP_BCLCONFIG_H
#define BAP_BCLCONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Systemincludes mit <...> */

/* Bibliotheken von externen Herstellen mit <...> */

/* Eigene Header-Dateien "..." */
#include "bap_config.h"


/* Makro-Definitionen */

/** Konstante fuer die Anzahl von Segmentierungskanaelen */
#define BAP_NUM_SEG_CHANNELS ((uint8_t) 4)

/* Typ-Definitionen */

/* Enumerationen */

/**
 * 'enum' fuer die Spezifikation des BCL Uebertragungsmediums.
 * Der Interface Typ muss in der BCL Konfigurationsdatei fuer
 * jedes zu uebertragende Datenelement angegeben werden.
 */
typedef enum BapInterfaceType_t
{
    /** Interface Typ fuer CAN */
    BapIft_Can,
    /** Interface Typ fuer LIN */
    BapIft_Lin,
    /** Interface Typ fuer IPC */
    BapIft_Ipc,
    /** Kennung fuer keinen Interface Typ. d.h. die FunctionId
     *  ist nur intern gueltig und kann nicht versendet werden */
    BapIft_None
} BapInterfaceType_et;

/**
 * 'enum' fuer die Angabe des auf BCL Ebene zu verwendenden
 * Segmentierungsalgorithmus.
 * Bei Segmentierungstyp 1 erfolgt die Uebertragung auf einem
 * statisch konfigurierten Uebertragungskanal (es kannn es je
 * CAN ID vier Uebertragungskanaele geben (2Bit)).
 *
 * Die Wertzuordnung der 'enum' Mitglieder ist so gewaehlt,
 * dass die Werte auf ein 2Bit-Feld passen.
 * Wird kein Uebertragungskanal verwendet, so muss '..._Unsegmented'
 * eingetragen werden!
 * Der Uebertragungskanal muss in der BCL Konfigurationsdatei
 * angegeben werden.
 *
 * @remarks:
 * In der derzeitigen Implementierung wird bei Segmentierung
 * direkt der Wert in den Header eingesetzt, daher sind die Bits
 * schon entsprechend ausgerichtet und die Markierung fuer segmentierte
 * Nachricht schon gesetzt.
 */
typedef enum BapSegmentationType_t
{
#ifdef BAP_USES_SEGMENTATION

    /* -------- Enumwerte, bei denen nur ein Segmentierungskanal gewaehlt werden kann ------------ */

    /** Uebertragungskanal 0 fuer eine segmentierte Nachricht */
    BapSegType_ChannelOne = 0x01,

    /** Uebertragungskanal 1 fuer eine segmentierte Nachricht */
    BapSegType_ChannelTwo = 0x02,

    /** Uebertragungskanal 2 fuer eine segmentierte Nachricht */
    BapSegType_ChannelThree = 0x04,

    /** Uebertragungskanal 3 fuer eine segmentierte Nachricht */
    BapSegType_ChannelFour = 0x08,

	/** Uebertragungskanal 0, 1, 2 oder 3 fuer eine segmentierte Nachricht */
    BapSegType_ChannelOneTwoThreeFour = 0x0f, /* BapSegType_ChannelOne | BapSegType_ChannelTwo | BapSegType_ChannelThree | BapSegType_ChannelFour */
#endif  /* BAP_USES_SEGMENTATION */
    /** Kennung fuer eine nicht-segmentierte Nachricht ohne Kanalnummer */
    BapSegType_Unsegmented = 0x00
} BapSegmentationType_et;


/* Strukturen */

/**
 * BCL ROM Zeile fuer die Zuordnung Intertelegramm Timer
 * zu LSG-ID und FCT-ID.
 */
#ifdef DLL_COMPILATION
typedef struct BapInterTelegramTimerMapRow_t
#else
typedef const struct BapInterTelegramTimerMapRow_t
#endif /* #ifdef DLL_COMPILATION */
{
    /** Kennung des logischen Steuergeraets */
    lsgId_t lsgId;
    /** Kennung der Function */
    fctId_t fctId;
} BapInterTelegramTimerMapRow_ot;

/**
 *  Definiert einen Zeiger auf BapInterTelegramTimerMapRow_ot im ROM
 */
typedef BAP_ROM_DATA_FAR BapInterTelegramTimerMapRow_ot * BapInterTelegramTimerMapRow_pt;

/* werden spaeter definiert */

/* Vorwaertsdeklaration noetig wegen gegenseitiger Abhaengigkeit der Strukturen */
struct BapCanTxDynSegChannels_t;
typedef struct BapCanTxDynSegChannels_t * BapCanTxDynSegChannels_pot;

/* Vorwaertsdeklaration noetig wegen gegenseitiger Abhaengigkeit der Strukturen */
struct BapCanRxDynSegChannels_t;

/** Zeiger auf die RAM-Tabelle BapCanRxDynSegChannels_t */
typedef DBGVAR struct BapCanRxDynSegChannels_t * BapCanRxDynSegChannels_pot;

/* Vorwaertsdeklaration noetig wegen gegenseitiger Abhaengigkeit der Strukturen */
struct BapCanTxSegmentationRamRow_t;

/** Zeiger auf die RAM-Statuszeile BapCanRxSegmentationRamRow_t*/
typedef DBGVAR struct BapCanRxSegmentationRamRow_t * BapCanRxSegmentationRamRow_pot;

/** Zeiger auf die RAM-Statuszeile BapCanTxSegmentationRamRow_t*/
typedef struct BapCanTxSegmentationRamRow_t * BapCanTxSegmentationRamRow_pot;

/* Vorwaertsdeklaration noetig wegen gegenseitiger Abhaengigkeit der Strukturen */
struct BapBclRxRamRow_t;

/** Zeiger auf BapBclRxRamRow_t */
typedef DBGVAR struct BapBclRxRamRow_t * BapBclRxRamRow_pot;

/* Vorwaertsdeklaration noetig wegen gegenseitiger Abhaengigkeit der Strukturen */
struct BapBclTxRamRow_t;

/** Zeiger auf BapBclTxRamRow_t */
typedef DBGVAR struct BapBclTxRamRow_t * BapBclTxRamRow_pot;


/**
 * BCL ROM Parameterzeile fuer ein Datenelement, dass auf CAN
 * gesendet werden soll.
 */
#ifdef DLL_COMPILATION
typedef struct BapCanTxRomRow_t
#else
typedef const struct BapCanTxRomRow_t
#endif /* #ifdef DLL_COMPILATION */
{
    /** Nummer des physikalischen Interface, falls mehrere
     *  CAN-Interfaces auf der Hardware verfuegbar sind.
     *
     *  @remarks
     *  Wird in der aktuellen Anpassung an den Vector-Treiber fuer HCS12
     *  ignoriert.
     *  In der Anpassung an den Treiber fuer die CANcardX wird sie jedoch
     *  verwendet.
     */
    BapCanInterfaceChannel_t canInterfaceChannel;

    /** Segmentierungstyp */
    BapSegmentationType_et eSegmentationType;

#ifdef BAP_USES_SEGMENTATION
    /** Zeiger auf den speziellen RAM-Bereich fuer CAN */
    BapCanTxSegmentationRamRow_pot poCanTxRamRow;
#endif /* #ifdef BAP_USES_SEGMENTATION */

    /** Zeiger auf den allgemeinen RAM-Bereich zum Senden */
    BapBclTxRamRow_pot poBclTxRamRow;

    /** Index auf die Timer-Tabelle fuer die aktuelle Inhibit-Zeit sowie
        die konfigurierte Inhibit-Zeit beim Versenden */
    uint8_t u8InhibitIndex;

    /** CAN-Message-Handle des CAN-Treibers */
    BapCanMsgId_t canMsgId;

#ifdef BAP_USES_SEGMENTATION
    BapCanTxDynSegChannels_pot poTxDynSegChannels;
#endif /* #ifdef BAP_USES_SEGMENTATION */

    /** Zeiger auf die zugehoerige FctRomRow */
    BapFctRomRow_pot poFctRomRow;
	
    /** Anzahl der PDU die innerhalb eines BAP_TASK Zyklus fuer 
        eine Sende-PDU maximal gesendet werden duerfen */
    uint8_t u8SendCnt;
} BapCanTxRomRow_ot;


/**
 * BCL ROM Parameterzeile fuer ein Datenelement, dass auf CAN
 * empfangen werden soll.
 */
#ifdef DLL_COMPILATION
typedef struct BapCanRxRomRow_t
#else
typedef const struct BapCanRxRomRow_t
#endif /* #ifdef DLL_COMPILATION */
{
    lsgId_t lsgId;
    fctId_t fctId;
    uint32_t u32Size;

    /** Nummer des physikalischen Interface, falls mehrere
     *  CAN-Interfaces auf der Hardware verfuegbar sind.
     */
    BapCanInterfaceChannel_t canInterfaceChannel;

    /** Segmentierungstyp */
    BapSegmentationType_et eSegmentationType;

#ifdef BAP_USES_SEGMENTATION
    /** Konfigurierte Intertelegramm-Zeit beim Empfangen */
    uint16_t u16IntertelegramTime;
#endif /* #ifdef BAP_USES_SEGMENTATION */
#ifdef BAP_USES_SEGMENTATION
    /** Zeiger auf den speziellen RAM-Bereich fuer CAN */
    BapCanRxSegmentationRamRow_pot poCanRxRamRow;
#endif /* #ifdef BAP_USES_SEGMENTATION */
    /** Zeiger auf den allgemeinen RAM-Bereich beim Empfangen */
    BapBclRxRamRow_pot poBclRxRamRow;
#ifdef BAP_USES_SEGMENTATION
    /** Timer fuer die aktuelle Intertelegramm-Zeit */
    uint16_t * pu16InterTelegramTimer;
#endif /* #ifdef BAP_USES_SEGMENTATION */
    /** CAN-Message-Handle des CAN-Treibers */
    BapCanMsgId_t canMsgId;

#ifdef BAP_USES_SEGMENTATION
    BapCanRxDynSegChannels_pot poRxDynSegChannels;
#endif /* #ifdef BAP_USES_SEGMENTATION */
} BapCanRxRomRow_ot;


/**
 * Ein Bitfeld mit den fuer Rx/Tx auf Can/Lin relevanten Flags
 *
 * @remarks LIN wird in der aktuellen Version nicht unterstuetzt
 */
typedef struct BapCanLinFlags_t
{
    /** Sequenznummer bei segmentierter Uebertragung */
    bitfield_t fSequenceNumber :4;
} BapCanLinFlags_ot;


#ifdef BAP_USES_SEGMENTATION
/**
 * BCL RAM Statuszeile fuer ein Datenelement, dass auf CAN
 * gesendet werden soll. Wird fuer segmentierte Botschaften benoetigt
 */
typedef struct BapCanTxSegmentationRamRow_t
{
    /** Flags fuer das Versenden von Botschaften auf CAN und LIN */
    BapCanLinFlags_ot flags;

    /** Offset im Sendepuffer, der auf den als naechstes zu versendenden
     *  Teil der Botschaft zeigt */
    uint32_t u32BclTxBufferByteOffset;

    /**
     * Haelt den ausgewaehlten Segmentierungskanal fest
     */
    BapSegmentationType_et eSelectedSegmentationChannel;
} BapCanTxSegmentationRamRow_ot;
#endif /* #ifdef BAP_USES_SEGMENTATION */


#ifdef BAP_USES_SEGMENTATION
/**
 * RAM Tabelle, welche die Belegung der Sende-Segmentierungskanaele einer CanMsgId speichert.
 */
typedef struct BapCanTxDynSegChannels_t
{
    /**
     * Speichert, welche BapCanTxRomRow gerade den Segmentierungskanal verwendet oder NULL,
     * falls der Segmentierungskanal gerade frei ist.
     */
    BapCanTxRomRow_pot arpoTxDynSegChannels[BAP_NUM_SEG_CHANNELS];
} BapCanTxDynSegChannels_ot;
#endif /* #ifdef BAP_USES_SEGMENTATION */


#ifdef BAP_USES_SEGMENTATION
/**
 * BCL RAM Statuszeile fuer ein Datenelement, dass auf CAN
 * empfangen werden soll. Wird fuer segmentierte Botschaften benoetigt
 */
typedef struct BapCanRxSegmentationRamRow_t
{
    /** Flags fuer das Empfangen von Botschaften auf CAN und LIN */
    BapCanLinFlags_ot flags;

    /** Offset im Empfangspuffer, wo als naechstes empfangene Daten
     *  hinkopiert werden */
    uint32_t u32BclRxBufferByteOffset;
} BapCanRxSegmentationRamRow_ot;
#endif /* #ifdef BAP_USES_SEGMENTATION */


#ifdef BAP_USES_SEGMENTATION
/**
 * RAM Tabelle, welche die Belegung der Empfangs-Segmentierungskanaele einer CanMsgId speichert.
 */
typedef struct BapCanRxDynSegChannels_t
{
    /**
     * Speichert, welche BapCanRxRomRow gerade den Segmentierungskanal verwendet oder NULL,
     * falls der Segmentierungskanal gerade frei ist.
     */
    BapCanRxRomRow_pot arpoRxDynSegChannels[BAP_NUM_SEG_CHANNELS];
} BapCanRxDynSegChannels_ot;
#endif /* #ifdef BAP_USES_SEGMENTATION */

/**
 * RAM Zelle, speichert eine im CAN-Rx-Interrupt empfangene CAN Botschaft zwischen
 * bis zum naechsten Aufruf von BAP_Task.
 */
typedef struct BapCanRxBuffer_t
{
    /** Enthaelt den Can Interface Channel, auf welchem die Daten empfangen wurden */
    BapCanInterfaceChannel_t canInterfaceChannel;

    /** Enthaelt die Can Message Id, auf welcher die Daten empfangen wurden */
    BapCanMsgId_t canMsgId;

    /** Enthaelt die Laenge der empfangenen Daten */
    uint16_t u16MsgLength;

    /** Enthaelt die empfangenen Daten */
    uint8_t* aru8Data;
} BapCanRxBuffer_ot;

/** Zeiger auf die RAM-Zelle BapCanRxBuffer_ot */
typedef BapCanRxBuffer_ot * BapCanRxBuffer_pot;

/** Konstanter Zeiger auf die RAM-Zelle BapCanRxBuffer_ot */
typedef const BapCanRxBuffer_ot * BapCanRxBuffer_cpot;

/**
 * Meta-Daten Block zur Verwaltung dynamisch allokierter Speicherbereiche
 * im CAN-Rx-Ringbuffer fuer empfangene CAN Botschaften.
 */
typedef struct BapCanRxBufferMeta_t {

	/** Enthaelt die Nutzdatengroesse eines Speicherbereichs */
	uint32_t u32BlockSize;

	/** Zeigt an, ob ein Speicherbereich noch verwendet wird oder zur Wiederverwendung freigegeben ist */
	DBGVAR bool_t isFree;

	/** Enthaelt die Adresse des oertlich naechsten allokierten Speicherbereichs */
	struct BapCanRxBufferMeta_t *next;

	/** Enthaelt die Adresse des zeitlich naechsten allokierten Speicherbereichs */
	struct BapCanRxBufferMeta_t *nextFifo;
} BapCanRxBufferMeta_ot;

/** Zeiger auf die Meta-Daten BapCanRxBufferMeta_ot */
typedef DBGVAR BapCanRxBufferMeta_ot *BapCanRxBufferMeta_pot;

/** Konstanter Zeiger auf die Meta-Daten BapCanRxBufferMeta_t */
typedef BAP_ROM_DATA_FAR struct BapCanRxBufferMeta_t *const BapCanRxBufferMeta_cpot;

/**
 *  Abstraktion des Bustypes fuer Senderichtung.
 */
#ifdef DLL_COMPILATION
typedef struct BapBusIndirectionTxRomRow_t
#else
typedef const struct BapBusIndirectionTxRomRow_t
#endif /* #ifdef DLL_COMPILATION */
{
    /**
     * Bestimmt, welcher Eintrag in der Union verwendet
     * werden muss und legt gleichzeitig den Typ fest
     */
    BapInterfaceType_et eInterfaceType;

    /** Zeiger auf die busspezifische ROM-Konfiguration zum Senden */
    BapCanTxRomRow_pot poCanTx;

    /** Zeiger auf die RAM-Bereiche zum Senden */
    BapBclTxRamRow_pot poBclTxRamRow;

    /** Enthaelt die konfigurierte Groesse des Puffers in poBclTxRamRow */
    uint32_t u32BufferSize;

#ifdef BAP_USES_STATUS_ALL
    /** Gibt an, ob bei StatusAll die Laenge vorangestellt werden soll oder nicht */
    bool_t bDataTypeSupportsVarLength;
#endif /*  BAP_USES_STATUS_ALL */
} BapBusIndirectionTxRomRow_ot;


/**
 *  Abstraktion des Bustypes fuer Empfangsrichtung.
 */
#ifdef DLL_COMPILATION
typedef struct BapBusIndirectionRxRomRow_t
#else
typedef const struct BapBusIndirectionRxRomRow_t
#endif /* #ifdef DLL_COMPILATION */
{
    /**
     * Bestimmt, welcher Eintrag in der Union verwendet
     * werden muss und legt gleichzeitig den Typ fest
     */
    BapInterfaceType_et eInterfaceType;

    /** Zeiger auf die busspezifische ROM-Konfiguration zum Empfangen */
    BapCanRxRomRow_pot poCanRx;

    /** Zeiger auf die RAM-Bereiche zum Empfangen */
    BapBclRxRamRow_pot poBclRxRamRow;
} BapBusIndirectionRxRomRow_ot;


/**
 *  Bitfeld, das die Flags fuer den Bcl enthaelt
 */
typedef struct BapBclTxRamRowFlags_t
{
#ifdef BAP_USES_ACKNOWLEDGE
    /** Flag zeigt an, dass nach dem Senden eines Requests ein Acknowledge an die Applikation gemeldet werden soll */
    bitfield_t fTxRequestNeedsAckFlag    :1;
#endif  /* #ifdef BAP_USES_ACKNOWLEDGE */

#if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG)
    /** Flag zeigt an, dass nach dem Senden eines Errors ein Acknowledge an die Applikation gemeldet werden soll */
    bitfield_t fTxErrorNeedsAckFlag      :1;
#endif  /* #if defined(BAP_USES_ACKNOWLEDGE) && defined(BAP_FSG) */

    /** Flag zeigt an, ob das Datenelement gesendet werden soll */
    bitfield_t fTxRequestFlag    :1;

#ifdef BAP_USES_SEGMENTATION
    /** Flag zeigt an, dass das Datenelement gerade gesendet wird */
    bitfield_t fTxInProgressFlag :1;
#endif /* #ifdef BAP_USES_SEGMENTATION */

#ifdef BAP_FSG
    /** Flag zeigt an, dass ein Fehler als Nachricht versendet werden soll */
    bitfield_t fTxErrorFlag      :1;

    /** Flag zeigt an, dass der Sendepuffer initialisiert wurde */
    bitfield_t fTxInitializedFlag:1;
#endif /* #ifdef BAP_FSG */
    /** Flag zeigt an, ob sich das Datenelement im Sendebuffer befindet */
    bitfield_t fTxSendBufferFlag:1;
} BapBclTxRamRowFlags_ot;


/**
 *  Bitfeld, das die Flags fuer den Bcl enthaelt
 */
typedef struct BapBclRxRamRowFlags_t
{
#ifdef BAP_USES_SEGMENTATION
    /** Flag zeigt an, dass das Datenelement gerade empfangen wird */
    bitfield_t fRxInProgressFlag :1;
#endif /* #ifdef BAP_USES_SEGMENTATION */

    /** Flag zeigt an, dass das Datenelement komplett empfangen wurde */
    bitfield_t fRxCompleteFlag   :1;

    /** Flag zeigt an, dass eine Fehlernachricht empfangen wurde, oder dass ein interner Fehler
      * aufgetreten ist, welcher asynchron gemeldet wird.
      */
    bitfield_t fRxErrorFlag      :1;
} BapBclRxRamRowFlags_ot;


/**
 *  Enthaelt Informationen ueber den aktuellen Zustand in Sende- und
 *  Empfangsrichtung des BCL und die zugehoerigen Sende- und
 *  Empfangspuffer.
 */
typedef struct BapBclTxRamRow_t
{
    /** Zustandsflags in Sende- und Empfangsrichtung */
    BapBclTxRamRowFlags_ot flags;

    /** Sende- und Empfangspuffer fuer Fehlerwerte */
    BapError_et eErrorCode;

    /** Sende- und Empfangspuffer fuer den zum Datenwert gehoerenden Opcode.
        Zum Fehlerwert braucht kein Opcode gespeichert werden, da dieser fix ist */
    BapOpCodes_et eOpCode;

    /** Sende- und Empfangspuffer fuer Datenwerte */
    BapBufferWithLength_ot oBufferWithLength;
} BapBclTxRamRow_ot;


/**
 *  Enthaelt Informationen ueber den aktuellen Zustand in Sende- und
 *  Empfangsrichtung des BCL und die zugehoerigen Sende- und
 *  Empfangspuffer.
 */
typedef struct BapBclRxRamRow_t
{
    /** Zustandsflags in Sende- und Empfangsrichtung */
    BapBclRxRamRowFlags_ot flags;

    /** Sende- und Empfangspuffer fuer Fehlerwerte */
    BapError_et eErrorCode;

    /** Sende- und Empfangspuffer fuer den zum Datenwert gehoerenden Opcode.
        Zum Fehlerwert braucht kein Opcode gespeichert werden, da dieser fix ist */
    BapOpCodes_et eOpCode;

    /** Sende- und Empfangspuffer fuer Datenwerte */
    BapBufferWithLength_ot oBufferWithLength;
} BapBclRxRamRow_ot;


/**
 * Definiert Flags, welche fuer das Senden auf CAN mit heuristischem Verfahren genutzt werden
 */
typedef struct BapHeuristikFlags_t
{
    /**
     * Falls dieses Bit gesetzt ist, dann soll auf dieser CAN-Id etwas gesendet werden.
     */
    bitfield_t fTxRequest:1;

    /**
     * Zaehler fuer die Prioritaetsvergabe von segmentierten Nachrichten bei heuristischem Senden.
     * Begrenzt die Anzahl unsegmentierter Nachrichten zwischen zwei Sequenzbotschaften
     * @remark Wird in BAP 1.4 nicht verwendet
     */
    bitfield_t u4SegmentationPriority:4;
} BapHeuristikFlags_ot;

/**
 * Enthaelt Inhibit-Timer und Heuristikinformationen fuer eine
 * CAN-Id, welche zum Senden genutzt wird.
 */
typedef struct BapInhibitRamRow_t
{
    /**
     * Zaehler fuer den aktuellen Inhibit-Timer dieser CAN-Id.
     */
    uint16_t u16InhibitTimer;
    /**
     * Offset auf das logische Steuergeraet, auf dem zuletzt
     * eine Nachricht auf dieser Can-Id gesendet wurde
     *
     * @see BAP_InhibitRomTable
     * @see BAP_MapCanIdToLsgRomRowTable
     *
     * @remark Dieser Offset + BAP_InhibitRomTable.aroMapCanIdToLsgTable zeigt
     * auf eine Zeile in BAP_MapCanIdToLsgTable.
     */
    uint8_t u8HeuristikLsgIndex;
    /**
     * Offset auf die Funktion innerhalb des logischen Steuergeraets,
     * auf dem zuletzt eine Nachricht auf dieser Can-Id gesendet wurde
     * @remark enthaelt den Index auf die Funktion des Lsgs dieser Can-Id,
     * @see BAP_MapCanIdByLsgTable
     */
    uint8_t u8HeuristikFctIndex;
    /**
     * Enthaelt Informationen darueber, ob etwas zu senden ist und mit
     * welcher Strategie.
     */
    BapHeuristikFlags_ot oHeuristikFlags;
} BapInhibitRamRow_ot;

/**
 * Enthaelt eine Liste von CanTxRomRows, sortiert nach Lsg-Konfiguration
 * und Can-Id.
 */
#ifdef DLL_COMPILATION
typedef struct BapMapCanIdByLsg_t
#else
typedef struct BapMapCanIdByLsg_t
#endif /* #ifdef DLL_COMPILATION */
{
    /** Enthaelt eine CanTxRomRow welche einer gegebenen CanId zugeordnet ist.
     *
     *  @remark Die Beziehung zur CanId besteht ueber BapMapCanIdToLsg_t und
     *  BapInhibitRomRow_t
     */
    BapCanTxRomRow_pot poCanTxRomRow;
} BapMapCanIdByLsg_ot;

/** Konstanter Zeiger auf die Zuordnungsliste BapMapCanIdByLsg_t */
typedef BAP_ROM_DATA_FAR  const struct BapMapCanIdByLsg_t *  BapMapCanIdByLsg_cpot;

/**
 * Bildet die Beziehung zwischen einer Sende-CAN-Id und einer Lsg-Konfiguration,
 * welche diese CAN-Id nutzt, ab.
 */
#ifdef DLL_COMPILATION
typedef struct BapMapCanIdToLsg_t
#else
typedef const struct BapMapCanIdToLsg_t
#endif /* #ifdef DLL_COMPILATION */
{
    /**
     * Enthaelt einen Zeiger auf ein konfiguriertes logisches Steuergeraet.
     * Diese Konfiguration braucht im ASG jedoch nicht die gerade aktive zu sein.
     */
    BapLsgRomRow_pot poLsgRomRow;

} BapMapCanIdToLsg_ot;

/** Konstanter Zeiger auf die reverse Zuordnungsliste BapMapCanIdToLsg_t */
typedef BAP_ROM_DATA_FAR const struct BapMapCanIdToLsg_t * BapMapCanIdToLsg_cpot;

/**
 * Enthaelt Informationen ueber die Sende-CAN-Id, der konfigurierten Inhibit-Zeit,
 * und verweist auf eine Liste von logischen Steuergeraeten, die diese CAN-Id
 * verwenden.
 */
#ifdef DLL_COMPILATION
typedef struct BapInhibitRomRow_t
#else
typedef const struct BapInhibitRomRow_t
#endif /* #ifdef DLL_COMPILATION */
{
    /** Enthaelt die konfigurierte Inhibit-Zeit der gegebenen Can-Id canMsgId */
    uint16_t u16ConfiguredInhibitTime;

    /** Bestimmt die Can-Id, fuer die diese Zeile gueltig ist */
    BapCanMsgId_t canMsgId;

    /** Index fuer Zugriff auf einer Element in Tabelle mit logischen Steuergeraeten, welche diese Can-Id nutzen */
    uint16_t u16MapCanIdToLsgTableIndex;

    /** Anzahl der Steuergeraete, die diese Can-Id nutzen */
    uint8_t u8MapCanIdToLsgSize;

    /** Index fuer Zugriff auf eine Tabelle mit Funktionen von logischen Steuergeraeten, welche diese Can-Id nutzen */
    uint16_t u16MapCanIdByLsgTableIndex;

    /** Anzahl der Funktionen, die diese Can-Id nutzen */
    uint8_t u8MapCanIdByLsgSize;

    /** Nummer des physikalischen Interface, falls mehrere
     *  CAN-Interfaces auf der Hardware verfuegbar sind.
     *
     *  @remarks
     *  Wird in der aktuellen Anpassung an den Vector-Treiber fuer HCS12
     *  ignoriert.
     *  In der Anpassung an den Treiber fuer die CANcardX wird sie jedoch
     *  verwendet.
     */
    BapCanInterfaceChannel_t canInterfaceChannel;

} BapInhibitRomRow_ot;

/** Konstanter Zeiger auf die InhibitRomRow */
#ifndef DLL_COMPILATION
typedef BAP_ROM_DATA_FAR const struct BapInhibitRomRow_t * BapInhibitRomRow_cpot;
#endif /* #ifndef DLL_COMPILATION */

/* Const Deklarationen */

/* Externe globale Variablen */

/**
 * Tabelle mit der gesamten CAN-Konfiguration fuer alle
 * zu versendenden Datenelementen.
 */
#ifdef DLL_COMPILATION
#   define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>
extern BapCanTxRomRow_ot* BAP_CanTxRomTable;
#   define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>
#else
#   define BAP_START_SEC_CONST_UNSPECIFIED
#   include <BAP_MemMap.h>
extern BAP_ROM_DATA_FAR BapCanTxRomRow_ot BAP_CanTxRomTable[BAP_CAN_TX_ROM_TABLE_ROWS];
#   define BAP_STOP_SEC_CONST_UNSPECIFIED
#   include <BAP_MemMap.h>
#endif /* #ifdef DLL_COMPILATION */
/**
 * Tabelle mit der gesamten CAN-Konfiguration fuer alle
 * zu empfangenden Datenelementen.
 */
#ifdef DLL_COMPILATION
#   define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>
extern BapCanRxRomRow_ot* BAP_CanRxRomTable;
#   define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>
#else
#   define BAP_START_SEC_CONST_UNSPECIFIED
#   include <BAP_MemMap.h>
extern BAP_ROM_DATA_FAR BapCanRxRomRow_ot BAP_CanRxRomTable[BAP_CAN_RX_ROM_TABLE_ROWS];
#   define BAP_STOP_SEC_CONST_UNSPECIFIED
#   include <BAP_MemMap.h>
#endif /* #ifdef DLL_COMPILATION */
/**
 * Tabelle mit allen aktuellen Inhibit-Timern fuer alle
 * konfigurierten CAN-Ids.
 */
#ifdef DLL_COMPILATION
extern BapInhibitRamRow_ot* BAP_InhibitRamTable;
#else
extern BapInhibitRamRow_ot BAP_InhibitRamTable[BAP_INHIBIT_ROWS];
#endif /* #ifdef DLL_COMPILATION */

#ifdef BAP_USES_EXCLUSIVE_ADDRESS
/* Tabelle mit eindeutigen Zuweisungen von CAN-MessageId und LsgId */
#   ifdef DLL_COMPILATION
extern BapCanMsg2LsgMapping_ot* BAP_CanRxMsgToLsgMappingTable;
#   else
extern BapCanMsg2LsgMapping_ot BAP_CanRxMsgToLsgMappingTable[BAP_CAN2LSGID_TABLE_ROWS];
#   endif /* #ifdef DLL_COMPILATION */
#endif

#ifdef BAP_USES_SEGMENTATION
/**
 * Tabelle enthaelt eine Liste aller Tx Segmentierungskanaele, welche zur Zeit
 * verwendet werden.
 */
#   ifdef DLL_COMPILATION
extern BapCanTxDynSegChannels_ot* BAP_CanTxSegmentationChannels;
#   else /* else #ifdef DLL_COMPILATION */
#   define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>	
extern BapCanTxDynSegChannels_ot BAP_CanTxSegmentationChannels[BAP_CAN_TX_SEGMENTATION_CHANNELS];
#   define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>
#   endif /* #ifdef DLL_COMPILATION */
/**
 * Tabelle enthaelt alle CanMsgIds, bei welchen segmentiertes Senden moeglich ist.
 * Der Index dieser Tabelle entspricht dem Index der Tabelle BAP_CanTxSegmentationChannels.
 *
 * BAP_u16CanTxSegmentationChannels enthaelt die Anzahl der Zeilen dieser Tabelle.
 */
#   define BAP_START_SEC_CONST_UNSPECIFIED
#   include <BAP_MemMap.h>
#   ifdef DLL_COMPILATION
extern BAP_ROM_DATA_FAR BapCanMsgId_t* BAP_ROM_CONST BAP_CanTxMsgIdToSegChannelMappingTable;
#   else
extern BAP_ROM_DATA_FAR const BapCanMsgId_t BAP_ROM_CONST BAP_CanTxMsgIdToSegChannelMappingTable[BAP_CAN_TX_SEGMENTATION_CHANNELS];
#   endif /* #ifdef DLL_COMPILATION */
#   define BAP_STOP_SEC_CONST_UNSPECIFIED
#   include <BAP_MemMap.h>
/**
 * Tabelle enthaelt eine Liste aller Rx Segmentierungskanaele, welche zur Zeit
 * verwendet werden.
 */
#   define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>
#   ifdef DLL_COMPILATION
extern BapCanRxDynSegChannels_ot* BAP_CanRxSegmentationChannels;
#   else
extern BapCanRxDynSegChannels_ot BAP_CanRxSegmentationChannels[BAP_CAN_RX_SEGMENTATION_CHANNELS];
#   endif /* #ifdef DLL_COMPILATION */
#   define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>
/**
 * Tabelle enthaelt alle CanMsgIds, bei welchen Segmentierter Empfang moeglich ist.
 * Der Index dieser Tabelle entspricht dem Index der Tabelle BAP_CanRxSegmentationChannels.
 *
 * BAP_u16CanRxSegmentationChannels enthaelt die Anzahl der Zeilen dieser Tabelle.
 */
#   ifdef DLL_COMPILATION
#       define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#       include <BAP_MemMap.h>
extern BapCanMsgId_t* BAP_CanRxMsgIdToSegChannelMappingTable;
#       define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#       include <BAP_MemMap.h>
#   else
#       define BAP_START_SEC_CONST_UNSPECIFIED
#       include <BAP_MemMap.h>
extern BAP_ROM_DATA_FAR const BapCanMsgId_t BAP_ROM_CONST BAP_CanRxMsgIdToSegChannelMappingTable[BAP_CAN_RX_SEGMENTATION_CHANNELS];
#       define BAP_STOP_SEC_CONST_UNSPECIFIED
#       include <BAP_MemMap.h>
#   endif /* #ifdef DLL_COMPILATION */
#endif /* #ifdef BAP_USES_SEGMENTATION */

#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
/**
 * Enthaelt alle CAN-Nachrichten, welche zwischen den letzten beiden BAP_Task-Aufrufen empfangen wurden.
 */
#ifdef DLL_COMPILATION
extern BapCanRxBuffer_ot* BAP_CanRxRingBuffer;
#else
extern uint8_t BAP_CanRxRingBuffer[];
#endif /* #ifdef DLL_COMPILATION */
/**
 * Enthaelt den Index, wohin die naechste empfange Nachricht hingeschrieben werden soll.
 * Dieser Wert kann nur dann gleich BAP_u8CanRxRingBufferReadOffset werden, wenn durch
 * Verarbeitung der Nachrichten der Ringpuffer geleert wurde.
 *
 * @see BAP_CanRxRingBuffer
 */
extern volatile uint8_t BAP_u8CanRxRingBufferWriteOffset;

/**
 * Enthaelt den Index der naechsten zu verarbeitenden Nachricht.
 * Der RingPuffer ist leer, falls BAP_u8CanRxRingBufferReadOffset == BAP_u8CanRxRingBufferWriteOffset.
 *
 * @see BAP_CanRxRingBuffer
 */
extern uint8_t BAP_u8CanRxRingBufferReadOffset;

/**
 * Enthaelt die Nachricht von BAP_CANUBS_RxData an BAP_BCL_CanReceiveTask,
 * dass mindestens eine empfangene CAN Nachricht aus Platzmangel nicht im
 * BAP_CanRxRingBuffer gespeichert werden konnte und damit verloren ist.
 *
 * @see BAP_CanRxRingBuffer
 */
extern bool_t BAP_u8CanRxRingBufferMessageLost;

#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
/**
 * Tabelle mit den konfigurierten Inhibit-Zeiten fuer
 * alle CAN-Ids.
 */
#ifdef DLL_COMPILATION
#   define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>
extern BAP_ROM_DATA_FAR BapInhibitRomRow_ot* BAP_ROM_CONST BAP_InhibitRomTable;
#   define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>
#else
#   define BAP_START_SEC_CONST_UNSPECIFIED
#   include <BAP_MemMap.h>
extern BAP_ROM_DATA_FAR BapInhibitRomRow_ot BAP_ROM_CONST BAP_InhibitRomTable[BAP_INHIBIT_ROWS];
#   define BAP_STOP_SEC_CONST_UNSPECIFIED
#   include <BAP_MemMap.h>
#endif /* #ifdef DLL_COMPILATION */

/**
 * Tabelle mit allen aktuellen Intertelegramm-Timern
 * fuer alle segmentierten Kanaele.
 */
#define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
#ifdef DLL_COMPILATION
extern uint16_t* BAP_u16InterTelegramTimerTable;
#else
extern uint16_t BAP_u16InterTelegramTimerTable[BAP_INTER_TELEGRAM_TIMER_ROWS];
#endif /* #ifdef DLL_COMPILATION */
#define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <BAP_MemMap.h>
/**
 * Abbildungstabelle, um vom Index des Intertelegramm-Timers auf die
 * LsgId und FctId zu kommen.
 */
#ifdef DLL_COMPILATION
#   define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>
extern BapInterTelegramTimerMapRow_ot* BAP_InterTelegramTimerMappingTable;
#   define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>
#else
#   define BAP_START_SEC_CONST_UNSPECIFIED
#   include <BAP_MemMap.h>
extern BAP_ROM_DATA_FAR BapInterTelegramTimerMapRow_ot BAP_ROM_CONST BAP_InterTelegramTimerMappingTable[BAP_INTER_TELEGRAM_TIMER_ROWS];
#   define BAP_STOP_SEC_CONST_UNSPECIFIED
#   include <BAP_MemMap.h>
#endif /* #ifdef DLL_COMPILATION */

/**
 * Tabelle mit allen Bustypen in Senderrichtung.
 */
#ifdef DLL_COMPILATION
#   define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>
extern BapBusIndirectionTxRomRow_ot* BAP_BusIndTxTable;
#   define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>
#else
#   define BAP_START_SEC_CONST_UNSPECIFIED
#   include <BAP_MemMap.h>
extern BAP_ROM_DATA_FAR BapBusIndirectionTxRomRow_ot BAP_ROM_CONST BAP_BusIndTxTable[BAP_CAN_TX_ROM_TABLE_ROWS];
#   define BAP_STOP_SEC_CONST_UNSPECIFIED
#   include <BAP_MemMap.h>
#endif /* #ifdef DLL_COMPILATION */
/**
 * Tabelle mit allen Bustypen in Empfangenrichtung.
 */
#ifdef DLL_COMPILATION
#   define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>
extern BapBusIndirectionRxRomRow_ot* BAP_BusIndRxTable;
#   define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>
#else
#   define BAP_START_SEC_CONST_UNSPECIFIED
#   include <BAP_MemMap.h>
extern BAP_ROM_DATA_FAR BapBusIndirectionRxRomRow_ot BAP_ROM_CONST BAP_BusIndRxTable[BAP_CAN_RX_ROM_TABLE_ROWS];
#   define BAP_STOP_SEC_CONST_UNSPECIFIED
#   include <BAP_MemMap.h>
#endif /* #ifdef DLL_COMPILATION */
/**
 * Abbildungstabelle ueber die Beziehung zwischen einer Sende-CAN-Id und einer Lsg-Konfiguration,
 * welche diese CAN-Id nutzt.
 */
#ifdef DLL_COMPILATION
#   define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>
extern BapMapCanIdToLsg_ot* BAP_MapCanIdToLsgRomRowTable;
#   define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>
#else
#   define BAP_START_SEC_CONST_UNSPECIFIED
#   include <BAP_MemMap.h>
extern BAP_ROM_DATA_FAR BapMapCanIdToLsg_ot BAP_ROM_CONST BAP_MapCanIdToLsgRomRowTable[BAP_MAP_CANID_TO_LSGROMROW_TABLE_ROWS];
#   define BAP_STOP_SEC_CONST_UNSPECIFIED
#   include <BAP_MemMap.h>
#endif /* #ifdef DLL_COMPILATION */
/* poLsgRomRow, aroMapCanIdByLsgTable, u8MapCanIdByLsgSize */

/**
 * Abbildungstabelle ueber die Beziehung zwischen einer Sende-CAN-Id und PDU-Groesse
 */
#ifdef DLL_COMPILATION
#   define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>
extern  BapMsgPduSize_ot* BAP_CanTxMsgPduSizeTable;
#   define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>
#else
#   define BAP_START_SEC_CONST_UNSPECIFIED
#   include <BAP_MemMap.h>
extern BAP_ROM_DATA_FAR BapMsgPduSize_ot BAP_ROM_CONST BAP_CanTxMsgPduSizeTable[BAP_CAN_TX_SEGMENTATION_CHANNELS];
#   define BAP_STOP_SEC_CONST_UNSPECIFIED
#   include <BAP_MemMap.h>
#endif /* #ifdef DLL_COMPILATION */
/**
 * Abbildungstabelle ueber die Beziehung zwischen einer Emfpange-CAN-Id und PDU-Groesse
 */
#ifdef DLL_COMPILATION
#   define BAP_START_SEC_VAR_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>
extern BapMsgPduSize_ot* BAP_CanRxMsgPduSizeTable;
#   define BAP_STOP_SEC_VAR_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>
#else
#   define BAP_START_SEC_CONST_UNSPECIFIED
#   include <BAP_MemMap.h>
extern BAP_ROM_DATA_FAR BapMsgPduSize_ot BAP_ROM_CONST BAP_CanRxMsgPduSizeTable[BAP_CAN_RX_SEGMENTATION_CHANNELS];
#   define BAP_STOP_SEC_CONST_UNSPECIFIED
#   include <BAP_MemMap.h>
#endif /* #ifdef DLL_COMPILATION */
/* Deklarationen von Funktionen */

#ifdef __cplusplus
}
#endif

#endif      /* #ifndef BAP_BCLCONFIG_H */

