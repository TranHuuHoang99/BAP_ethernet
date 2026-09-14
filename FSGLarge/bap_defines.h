 /******************************************************************
 *
 *     Copyright (c) 2003-2023 Volkswagen AG, D-38436 Wolfsburg
 *
 ******************************************************************
 *
 * Projekt:    BAP (P0674)
 * Komponente: Konfiguration
 *
 ******************************************************************
 *
 * Beschreibung
 *
 *  Diese Datei enthaelt alle #defines zur Anpassung der BAP-SSW
 *  an den jeweiligen Steuergeraetetyp. Mit Hilfe von Makro-Schaltern
 *  werden einzelne Funktionalitaeten an- bzw. ausgeschaltet. Damit
 *  wird die SW optimal an die zur Verfuegung stehenden Ressourcen
 *  angepasst.
 *
 ******************************************************************
 * Generiert am:    18.08.2026
 *           um:    18:06:58
 * Quelldatei:      C:\workspace\sample_project\POC_8255\FSGLarge\BAP_SW1.10_ClimateZone_P30DF79_V5.90_FSG.xml
 * Zieldatei:       C:\workspace\sample_project\POC_8255\FSGLarge\bap_defines.h
 *
 * BAPgen Version:  1.12.2
 * BAPgen Stand:    10.10.2023
 ******************************************************************/

#ifndef BAP_DEFINES_H
#define BAP_DEFINES_H

#ifdef __cplusplus
extern "C" {
#endif

/* Makro-Definitionen */

/**
 * Makro bei der Verwendung des erweiterten Adressierungsbereiches
 */
#define BAP_USES_EXCLUSIVE_ADDRESS 

/**
 * Makro bei der Verwendung der Ethernet-Kommunikation
 */
#define BAP_USES_ETH

/**
 * Type Definition des Steuergeraetes
 */
#define BAP_SGTYPE_IS_LARGE_FSG

/**
 * XML-Versionsinfo MAJOR. Ergibt mit der BAP_XML_VERSION_MINOR zusammen die Version.
 */
#define BAP_XML_VERSION_MAJOR 1

/**
 * XML-Versionsinfo MINOR. Ergibt mit der BAP_XML_VERSION_MAJOR zusammen die Version
 */
#define BAP_XML_VERSION_MINOR 0

/**
 * Name der XML-Datei aus der die Konfiguration stammt.
 */
#define BAP_SSW_XML (BAP_SW1.10_ClimateZone_P30DF79_V5.90_FSG.xml)

/**
 * Anzahl der Zeilen in der BAP_CanTxRomTable
 */
#define BAP_CAN_TX_ROM_TABLE_ROWS ((uint16_t)83)

/**
 * Anzahl der Zeilen in der BAP_CanRxRomTable
 */
#define BAP_CAN_RX_ROM_TABLE_ROWS ((uint16_t)329)

/**
 * Maximale PDU-Groesse der verarbeiteten Config-XML.
 * Wird automatisch auf 8 gesetzt, sofern kein Eintrag vorhanden oder kleiner 8.
 */
#define BAP_MAX_PDU_SIZE ((uint16_t)8)

/**
 * Anzahl der Zeilen in der BAP_InhibitRamTable
 */
#define BAP_INHIBIT_ROWS ((uint16_t)2)

/**
 * Haelt die Anzahl an Zyklen, die nach eine segmentierte Botschaft zusaetzlich warten muss.
 * Siehe Tag <InhibitAdditional> in Config-XML.
 */
#define BAP_INHIBITADDITIONAL_TIMER ((uint8_t)1)

/**
 * Anzahl der Zeilen in BAP_CanTxSegmentationChannels
 */
#define BAP_CAN_TX_SEGMENTATION_CHANNELS ((uint16_t)2)

/**
 * Anzahl der Zeilen in BAP_CanRxSegmentationChannels
 */
#define BAP_CAN_RX_SEGMENTATION_CHANNELS ((uint16_t)8)

/**
 * Enthaelt die Anzahl der Bytes von BAP_CanRxRingBuffer.
 */
#define BAP_CAN_RX_RING_BUFFER_SIZE ((uint32_t)942)

/**
 * Anzahl der Zeilen in der BAP_u16InterTelegramTimerTable
 */
#define BAP_INTER_TELEGRAM_TIMER_ROWS ((uint16_t)45)

/**
 *  Haelt die Anzahl an Zeilen, die die Tabelle BAP_LsgRomTables enthaelt.
 */
#define BAP_LSG_ROM_TABLE_ROWS ((uint8_t)2)

/**
 *  Haelt die Anzahl an Zeilen, die die Tabelle BAP_pLsgRomTable enthaelt.
 */
#define BAP_P_LSG_ROM_TABLE_ROWS ((uint8_t)2)

/**
 * Enthaelt die Anzahl der Elemente von BAP_FctRomTable.
 */
#define BAP_FCT_ROM_TABLE_ROWS ((uint16_t)83)

/**
 * Enthaelt die Anzahl der Elemente von BAP_BAPConfigTable.
 */
#define BAP_BAPCONFIG_TABLE_ROWS ((uint8_t)2)

/**
 * Haelt die Anzahl an Zeilen, die die Tabelle BAP_MapCanIdToLsgRomRowTable enthaelt.
 */
#define BAP_MAP_CANID_TO_LSGROMROW_TABLE_ROWS ((uint16_t)2)

/**
 * Haelt die Anzahl an Zeilen, die die Tabelle BAP_CanRxMsgToLsgMappingTable enthaelt.
 */
#define BAP_CAN2LSGID_TABLE_ROWS ((uint8_t)4)

/**
 * Enthaelt die hoechste in der Konfiguration verwendete LsgId.
 */
#define BAP_IDX_HIGHEST_LSG ((uint8_t)66)

/**
 *  Diese Auflistung enthaelt alle Fehlercodes von BAP.
 *  Diese werden als Rueckgabewert bei Funktionsaufrufen zurueckgegeben
 */
 typedef enum BapError_t
 {
     /**
     * Der Funktionsaufruf war erfolgreich.
     */
     BapErr_OK = 0x00,

     /* BCL Fehlermeldungen */
     /**
     * Sequenzbotschaft ohne vorangegangene Startbotschaft empfangen
     * @remarks
     * Dieser Fehlercode tritt ab BAP 1.4 nur dann auf, wenn nach dem Ausloesen
     * des Fehlers BapErr_TimeoutSegmentation noch Sequenzbotschaften folgen.
     *
     * In Vorgaengerversionen trat der Fehler immer auf, wenn eine Sequenzbotschaft
     * ohne Startbotschaft empfangen wurde.
     *
     * Grund fuer die Aenderung: Die dynamische Kanalvergabe erlaubt es, dass eine
     * CAN-Id/Segmentierungskanal nun mehrere LSGs adressieren kann, welche auf 
     * unterschiedlichen physikalischen Steuergeraeten realisiert sein koennen.
     *
     * Ein Aussenden einer segmentierten Botschaft haette zur Folge gehabt, dass
     * im jeweils gerade nicht adressierten Steuergeraet sehr viele Fehlermeldungen 
     * ausgeloest worden waeren.
     */
     BapErr_IllegalSequence = 0x12,

     /**
     * Nicht erwartete Sequenznummer empfangen.
     */
     BapErr_SequenceNumber = 0x13,

     /**
     * Folgebotschaft nicht rechtzeitig empfangen.
     * Die Intertelegrammzeit wurde verletzt.
     */
     BapErr_TimeoutSegmentation = 0x14,

     /**
     * Datenelement passt nicht in BCL Rx Puffer
     */
     BapErr_OversizeSegmentation  = 0x15,

     /**
     * Beim Datenempfang wurden weniger Datenbytes empfangen, als erforderlich gewesen waeren.
     *
     * @example
     * Im ASG ist Funktion 17 als Int16 definiert.
     * Im FSG ist Funktion 17 als Int8 definiert.
     * Es erfolgt eine Datenuebertragung mit eingeschaltetem variablen DLC ueber CAN.
     * Das ASG erhaelt also 3 Bytes (2 Byte Header + 1 Byte Nutzdaten).
     * Da 1 Byte Nutzdaten nicht ausreichen, um einen 16 Bit Wert zu fuellen wird die
     * Nachricht verworfen und dieser Fehler gemeldet.
     */
     BapErr_BadDataLength = 0x16,

     /**
     * Pufferueberlauf beim Empfang von Daten.
     * Bei korrekter Konfiguration der Ringpuffergroesse darf dieser Fehler nicht auftreten.
     */
     BapErr_ReceivedDataLost = 0x17,
     
     /* BPL Fehlermeldungen */
     /**
     * ASG Zeitueberwachungen Heartbeat - Cache wurde ungueltig gesetzt
     */
     BapErr_TimeoutHeartbeat = 0x21,

     /**
     * Alle Retrys waren erfolglos.
     */
     BapErr_RetryNotSuccessful = 0x22,

     /**
      * Die Processing Nachricht vom FSG kam nicht rechtzeitig im ASG an
      * Wird von der gleichen Funktionalitaet im BPL ausgeloest wie BapErr_RetryNotSuccessful
      */
     BapErr_ProcessingTimeout = 0x38,

     /**
     * Der Vorgang wurde nicht ausgefuehrt, weil zuviele interne Vorgaenge anstehen.
     * Genauere Beschreibung bei den Rueckgabewerten der einzelnen Funktionen.
     */
     BapErr_Busy = 0x23,

     /**
     * Die max. zu erwartende Antwortzeit wurde ueberschritten, ohne dass der Request
     * abgesendet werden konnte.
     *
     * @remarks Dieser Fehler kann auch bei unsegmentierten Nachrichten auftreten.
     * @remarks Der Fehler tritt nur im ASG auf.
     */
     BapErr_RequestTimeout = 0x24,


     /* BAL Fehlermeldungen */
     /**
     * Die Protokollversion des FSG passt nicht mit der des ASG zusammen.
     */
     BapErr_IncompatibleProtocolVersion = 0x32,

     /**
     * Die Datenfestlegung des FSG passt nicht mit der des ASG zusammen.
     */
     BapErr_IncompatibleDataSpecification = 0x33,

     /**
     * Die Daten im Cache sind ungueltig.
     * @remarks: 
     * Tritt nur im ASG als synchroner Fehler auf.
     */
     BapErr_CacheInvalid = 0x34,

     /**
     * Die Daten im Cache sind ungueltig.
     * @remarks: 
     * Tritt nur im ASG als asynchroner Fehler auf.
     */
     BapErr_GetAllMessageCorrupted = 0x39,

     /**
     * Mindestens ein Sendepuffer wurde nicht initialisiert.
     * @remarks:
     * Tritt nur im FSG als synchroner Fehler auf.
     */
     BapErr_SendBufferNotInitialized = 0x3A,

     /**
     * Diese Operation ist in diesem Zustand nicht erlaubt.
     * @remarks
     * Dieser Fehler tritt haeufig auf, wenn BAP_Init oder BAP_Start nicht aufgerufen wurden
     * oder danach BAP_Shutdown aufgerufen wurde.
     * Im ASG schlagen alle Request-Aufrufe fehl, solange keine BAP_Config empfangen wurde.
     */
     BapErr_InvalidState = 0x35,

     /**
     * Fuer den geforderten Cache Zugriff der angegebene FunktionId gibt es kein Cache.
     */
     BapErr_CacheNotAvailable = 0x36,

     /**
     * Einer der uebergebenen Parameter ist ungueltig.
     * (Null-Zeiger, ungueltige FctId oder LsgId, Requesttyp fuer diese Funktionsklasse nicht
     * erlaubt, Datentyp der Funktion und FunktionID stimmen nicht ueberein)
     */
     BapErr_InvalidArg = 0x37,

     /*
     * If a call to BAP_SendDebugInfo() is done and the global active flag is disabling the send of debug info
     * it will return BapErr_SendDebugDisable.
     */
     BapErr_SendDebugDisable = 0x51
,
    AppErr_OutOfRange = 0x41,
    AppErr_MaxDataLengthExceeded = 0x43,
    AppErr_UnitMismatch = 0x44,
    AppErr_ParameterMismatch = 0x45,
    AppErr_InvalidArgument = 0x46,
    AppErr_MethodAborted = 0x50,
    AppErr_IncompleteTransferOfParameterlistATN = 0xA0
}BapError_et;

#ifdef BAP_NOT_USES_NAMED_IDS
/** Der Datentyp fuer die Kennung eines Logischen Steuer-Geraetes */
typedef uint8_t lsgId_t;
/** Der Datentyp fuer die Kennung einer Funktion eines Logischen Steuer-Geraetes */
typedef uint8_t fctId_t;

#else
/**
 * Symbolische Namen fuer LSGs und Funktionen werden verwendet.
 */
#define BAP_USES_NAMED_IDS

/**
 * Benamte Bezeichner fuer logische Steuergeraete
 */
typedef enum BapLsg_t
{
  BapLsg_Reserved = 0x00,
  BapLsg_ClimateZone = 0x01,
  BapLsg_ClimateMaster = 0x42
}lsgId_t;

/**
 * Benamte Bezeichner fuer die Funktionen der verschiedenen logischen Steuergeraete
 */
typedef enum BapFct_t
{
  BapFct_Reserved = 0x00,
  /* Steuergeraet ClimateZone */
  BapFct_ClimateZone_GetAll = 0x01,
  BapFct_ClimateZone_BAP_Config = 0x02,
  BapFct_ClimateZone_FunctionList = 0x03,
  BapFct_ClimateZone_HeartBeat = 0x04,
  BapFct_ClimateZone_FSG_Control = 0x0d,
  BapFct_ClimateZone_FSG_Setup = 0x0e,
  BapFct_ClimateZone_FSG_OperationState = 0x0f,
  BapFct_ClimateZone_ZL_Temperature = 0x10,
  BapFct_ClimateZone_ZR_Temperature = 0x11,
  BapFct_ClimateZone_ZL_AirVolume = 0x12,
  BapFct_ClimateZone_ZR_AirVolume = 0x13,
  BapFct_ClimateZone_ZL_AirDistribution = 0x14,
  BapFct_ClimateZone_ZR_AirDistribution = 0x15,
  BapFct_ClimateZone_ZL_SeatClimate = 0x16,
  BapFct_ClimateZone_ZR_SeatClimate = 0x17,
  BapFct_ClimateZone_ZL_FootwellTemperature = 0x18,
  BapFct_ClimateZone_ZR_FootwellTemperature = 0x19,
  BapFct_ClimateZone_ZL_ClimateStyle = 0x1a,
  BapFct_ClimateZone_ZR_ClimateStyle = 0x1b,
  BapFct_ClimateZone_ZL_ClimateState = 0x1c,
  BapFct_ClimateZone_ZR_ClimateState = 0x1d,
  BapFct_ClimateZone_ZL_IndividualClimatisation = 0x1e,
  BapFct_ClimateZone_ZR_IndividualClimatisation = 0x1f,
  BapFct_ClimateZone_ZL_Ionisator = 0x20,
  BapFct_ClimateZone_ZR_Ionisator = 0x21,
  BapFct_ClimateZone_ZL_BodyCloseMeasures = 0x22,
  BapFct_ClimateZone_ZR_BodyCloseMeasures = 0x23,
  BapFct_ClimateZone_NozzlePositioning = 0x24,
  BapFct_ClimateZone_NozzleControl = 0x25,
  BapFct_ClimateZone_NozzleStatus = 0x26,
  BapFct_ClimateZone_ZL_AUTO = 0x27,
  BapFct_ClimateZone_ZR_AUTO = 0x28,
  BapFct_ClimateZone_FootHeater = 0x29,
  BapFct_ClimateZone_FSG_Setup2 = 0x2a,
  BapFct_ClimateZone_ZL_IntelligentAUTO = 0x2b,
  BapFct_ClimateZone_ZR_IntelligentAUTO = 0x2c,
  BapFct_ClimateZone_AirDistributionPresetList = 0x2d,
  BapFct_ClimateZone_ZL_AdaptSeatClimateCtrl = 0x2e,
  BapFct_ClimateZone_ZR_AdaptSeatClimateCtrl = 0x2f,
  BapFct_ClimateZone_ZL_AutomaticSeatClimate = 0x30,
  BapFct_ClimateZone_ZR_AutomaticSeatClimate = 0x31,
  BapFct_ClimateZone_ZL_SeatClimate_Extension = 0x32,
  BapFct_ClimateZone_ZR_SeatClimate_Extension = 0x33,
  /* Steuergeraet ClimateMaster */
  BapFct_ClimateMaster_GetAll = 0x01,
  BapFct_ClimateMaster_BAP_Config = 0x02,
  BapFct_ClimateMaster_FunctionList = 0x03,
  BapFct_ClimateMaster_HeartBeat = 0x04,
  BapFct_ClimateMaster_FSG_Control = 0x0d,
  BapFct_ClimateMaster_FSG_Setup = 0x0e,
  BapFct_ClimateMaster_FSG_OperationState = 0x0f,
  BapFct_ClimateMaster_AC = 0x10,
  BapFct_ClimateMaster_AirCirculation = 0x11,
  BapFct_ClimateMaster_AutomaticAirCirculation = 0x12,
  BapFct_ClimateMaster_Solar = 0x13,
  BapFct_ClimateMaster_IndirectVentilation = 0x14,
  BapFct_ClimateMaster_Synchronisation = 0x15,
  BapFct_ClimateMaster_PopupContent = 0x16,
  BapFct_ClimateMaster_DP_Presentation = 0x17,
  BapFct_ClimateMaster_FrontWindowHeater = 0x18,
  BapFct_ClimateMaster_RearWindowHeater = 0x19,
  BapFct_ClimateMaster_SteeringwheelHeater = 0x1a,
  BapFct_ClimateMaster_AuxHeater = 0x1b,
  BapFct_ClimateMaster_RearAuxHeater = 0x1c,
  BapFct_ClimateMaster_ResidualHeat = 0x1d,
  BapFct_ClimateMaster_Defrost = 0x1e,
  BapFct_ClimateMaster_RearControlLock = 0x1f,
  BapFct_ClimateMaster_RearPriorisation = 0x20,
  BapFct_ClimateMaster_BlowerCompensation = 0x21,
  BapFct_ClimateMaster_AirQuality = 0x22,
  BapFct_ClimateMaster_FreshAirConfiguration = 0x23,
  BapFct_ClimateMaster_FreshAirState = 0x24,
  BapFct_ClimateMaster_PureAir = 0x25,
  BapFct_ClimateMaster_AirQuality_2 = 0x26,
  BapFct_ClimateMaster_BehaviorMode = 0x27,
  BapFct_ClimateMaster_PSO_ImExport = 0x28,
  BapFct_ClimateMaster_ECOModeControl = 0x29,
  BapFct_ClimateMaster_VoiceControl = 0x2a,
  BapFct_ClimateMaster_Learning = 0x2b,
  BapFct_ClimateMaster_WinterFunction = 0x2c,
  BapFct_ClimateMaster_FANOnlyMode = 0x2d,
  BapFct_ClimateMaster_SeatClimateSynchronisation = 0x2e,
  BapFct_ClimateMaster_FSG_Setup2 = 0x2f,
  BapFct_ClimateMaster_CabinScene = 0x30
}fctId_t;

#endif
#ifdef __cplusplus
}
#endif

#endif      /* #ifndef BAP_DEFINES_H */
