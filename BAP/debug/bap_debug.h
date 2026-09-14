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
 *  Diese Datei enthaelt die Schnittstelle zum Debug/Diagnose-
 *  Support des BAP-Stacks.
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
 * 2021-11-23   1.11.3      DRH         [SSWPPB-216] Improve DLL generation.
 * 2021-03-08   1.11.3      DRH         [SSWPPB-142] Replaced magic numbers by constants
 * 2017-03-06	1.9.0       FST         [SSWCCB-1545] SSW-Lokatierungs-Pragmas eingefuegt
 * 2016-10-25	1.8.1       FST         [SSWCCB-2410] Softwareschalter DLL_COMPILATION zur Unterscheidung
 *                                      der Erzeugung von Steuergeraete-Code und der BAP-Dll eingefuegt
 * 2016-10-15	1.8.1       FST         [SSWCCB-2392] Debugmode erweitern für neue LSG-IDs,
 *                                      fuer LSG-ID > hat sich die Struktur der BAP-Boschaften geandert.
 *                                      Umlagern von Makros als echte Funktionen in die bap_debug.c
 * 2014-03-25	1.7.1       WWU         Misra-2004 fix: Function-like Macros.
 * 2013-04-17	1.7.0       FST         Get+Set-Funktionen fuer Bap_gDebugLsgId erstellt fuer debug-Zugriff 
 * 2013-02-06	1.7.0       WWU         Funktionsname Umbenannt, wegen Misra : Identifier exceeds 31 characters
 * 2012-02-02   1.6.3       NQU         Lint Warnung wegen Enum->Int Cast behoben
 * 2007-09-12   1.5         ALI         Aenderung BAP_DBG_SetBalState (InvalidConfig)
 * 2007-08-22   1.5         SHU         Aenderung der BAP-Debug-Botschaften mit Byte0+1 als BAP-Header
 * 2006-04-12   1.4         ALA         Unterstuetzung fuer BAP_ROM_DATA_FAR.
 * 2005-04-20   1.3         ALA         Funktion BAP_DBG_SetBplState entfernt, da gemeinsamer Zustand fuer alle Schichten.
 * 2005-04-06   1.3         ALA         BAP_DBG_RequestTimeoutError() und BAP_DBG_DataLostError() hinzugefuegt
 * 2004-11-17   1.2         JOK         BAP_DBG_GetAllMessageCorruptedError() hinzugefuegt
 * 2004-06-07   1.1         JOK         Compilerschalter fuer SG-Typen zur Optimierung
 *                                      des ROM-Bedarfs eingefuegt
 * 2004-06-07   1.1         JOK         Funktion BAP_DBG_SetBclState() entfernt
 ******************************************************************/

#ifndef BAP_DEBUG_H
#define BAP_DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Systemincludes mit <...> */

/* Bibliotheken von externen Herstellen mit <...> */

/* Eigene Header-Dateien "..." */
#include "bap.h"
#include "bap_config.h"
#ifdef DLL_COMPILATION
#include "bap_debug_iav.h"
#endif /* DLL_COMPILATION */
/* Makro-Definitionen */

/** Konstante fuer eine leere Funktion */
#define BAP_DUMMY_VOID_FUNCTION ((void)0)

/** Konstante fuer die Groesse der Debug Info Tabelle */
#define BAP_DBG_INFO_TABLE_SIZE 8

/* Vordefinierte FunctionIds */

/* Typ-Definitionen */

/* Const Deklarationen */

/* Externe globale Variablen */
#   define BAP_START_SEC_VAR_NO_INIT_8
#   include <BAP_MemMap.h>
#ifdef DLL_COMPILATION
extern DBGVAR uint8_t* BAP_DBG_DebugInfoTable;
extern uint8_t Bap_gDebugLsgId;
extern uint8_t BAP_SendDebugInfo_Active;
#else
extern DBGVAR uint8_t BAP_DBG_DebugInfoTable[8];
#endif /* DLL_COMPILATION */
#   define BAP_STOP_SEC_VAR_NO_INIT_8
#   include <BAP_MemMap.h>

/* Deklarationen von Funktionen */

#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>

/**
 *  Setze dauerhaft den neuen Lsg-Zustand des BAL im Diagnose-Speicher
 *
 *  @param aLsgId - bezeichnet das logische Steuergeraet
 *
 *  @param aeState - der neue Zustand
 *
 *  @remarks Der Zustand wird im Diagnose-Speicher im Datenbyte 1,
 *      Maske 0xC0 gehalten.
 */
#if defined (BAP_DBG_PER_LSG) || defined (BAP_DBG_ON_OFF)
BAP_IMPL_FAR void BAP_DBG_SetBalState(lsgId_t aLsgId, BapLayerLsgStatus_et aeState);
#else
#define BAP_DBG_SetBalState(dummy1, dummy2) BAP_DUMMY_VOID_FUNCTION
#endif


/**
 *  Setze dauerhaft den neuen Cache-Zustand des LSGs im Diagnose-Speicher
 *
 *  @param aLsgId - bezeichnet das logische Steuergeraet
 *
 *  @param abValid - BAP_TRUE steht fuer der Cache ist gueltig.
 *
 *  @remarks Der Zustand wird im Diagnose-Speicher im Datenbyte 1,
 *      Maske 0x20 gehalten.
 */
#if defined (BAP_DBG_PER_LSG) || defined (BAP_DBG_ON_OFF)
BAP_IMPL_FAR void BAP_DBG_SetCacheValidState(lsgId_t aLsgId, bool_t abValid);
#else
#define BAP_DBG_SetCacheValidState(dummy1, dummy2) BAP_DUMMY_VOID_FUNCTION
#endif


/**
 *  Zeigt an, dass an die Applikation ein BapErr_GetAllMessageCorrupted gemeldet wurde
 *  und speichert das Ereignis im Diagnose-Speicher bis zum naechsten Auslesen.
 *
 *  @remarks Der Zustand wird im Diagnose-Speicher im Datenbyte 1,
 *      Maske 0x01 gehalten.
 */
#ifdef BAP_DBG_PER_LSG
BAP_IMPL_FAR void BAP_DBG_GetAllMsgCorruptedErr(lsgId_t aLsgId);
#elif defined (BAP_DBG_ON_OFF)
#define BAP_DBG_GetAllMsgCorruptedErr(dummy) \
    (BAP_DBG_DebugInfoTable[2] |= (uint8_t)0x01u)
#else
#define BAP_DBG_GetAllMsgCorruptedErr(dummy)  BAP_DUMMY_VOID_FUNCTION
#endif


/**
 *  Zeigt an, dass an die Applikation ein BapErr_InvalidState gemeldet wurde
 *  und speichert das Ereignis im Diagnose-Speicher bis zum naechsten Auslesen.
 *
 *  @remarks Der Zustand wird im Diagnose-Speicher im Datenbyte 2,
 *      Maske 0x80 gehalten.
 */
#ifdef BAP_DBG_PER_LSG
BAP_IMPL_FAR void BAP_DBG_InvalidStateError(lsgId_t aLsgId);
#elif defined (BAP_DBG_ON_OFF)
#define BAP_DBG_InvalidStateError(dummy) \
    (BAP_DBG_DebugInfoTable[3] |= (uint8_t)0x80u)
#else
#define BAP_DBG_InvalidStateError(dummy) BAP_DUMMY_VOID_FUNCTION
#endif

/**
 *  Zeigt an, dass an die Applikation ein BapErr_CacheInvalid gemeldet wurde
 *  und speichert das Ereignis im Diagnose-Speicher bis zum naechsten Auslesen.
 *
 *  @remarks Der Zustand wird im Diagnose-Speicher im Datenbyte 2,
 *      Maske 0x40 gehalten.
 */
#ifdef BAP_DBG_PER_LSG
BAP_IMPL_FAR void BAP_DBG_CacheInvalidError(lsgId_t aLsgId);
#elif defined (BAP_DBG_ON_OFF)
#define BAP_DBG_CacheInvalidError(dummy) \
    (BAP_DBG_DebugInfoTable[3] |= (uint8_t)0x40u)
#else
#define BAP_DBG_CacheInvalidError(dummy) BAP_DUMMY_VOID_FUNCTION
#endif


/**
 *  Zeigt an, dass an die Applikation ein BapErr_CacheNotAvailable gemeldet wurde
 *  und speichert das Ereignis im Diagnose-Speicher bis zum naechsten Auslesen.
 *
 *  @remarks Der Zustand wird im Diagnose-Speicher im Datenbyte 2,
 *      Maske 0x20 gehalten.
 */
#ifdef BAP_DBG_PER_LSG
BAP_IMPL_FAR void BAP_DBG_CacheNotAvailableError(lsgId_t aLsgId);
#elif defined (BAP_DBG_ON_OFF)
#define BAP_DBG_CacheNotAvailableError(dummy) \
    (BAP_DBG_DebugInfoTable[3] |= (uint8_t)0x20u)
#else
#define BAP_DBG_CacheNotAvailableError(dummy) BAP_DUMMY_VOID_FUNCTION
#endif


/**
 *  Zeigt an, dass an die Applikation ein BapErr_InvalidArgument gemeldet wurde
 *  und speichert das Ereignis im Diagnose-Speicher bis zum naechsten Auslesen.
 *
 *  @remarks Der Zustand wird im Diagnose-Speicher im Datenbyte 2,
 *      Maske 0x10 gehalten.
 */
#ifdef BAP_DBG_PER_LSG
BAP_IMPL_FAR void BAP_DBG_InvalidArgError(lsgId_t aLsgId);
#elif defined (BAP_DBG_ON_OFF)
#define BAP_DBG_InvalidArgError(dummy) \
    (BAP_DBG_DebugInfoTable[3] |= (uint8_t)0x10u)
#else
#define BAP_DBG_InvalidArgError(dummy) BAP_DUMMY_VOID_FUNCTION
#endif


/**
 *  Zeigt an, dass bei der Ueberpruefung der BAP-Config-Nachricht keine
 *  Uebereinstimmung der BAP-Protokoll-Version gefunden wurde und speichert
 *  das Ereignis im Diagnose-Speicher bis zum naechsten Auslesen.
 *
 *  @remarks Der Zustand wird im Diagnose-Speicher im Datenbyte 2,
 *      Maske 0x08 gehalten.
 */
#ifdef BAP_DBG_PER_LSG
BAP_IMPL_FAR void BAP_DBG_ProtocolVersionError(lsgId_t aLsgId);
#elif defined (BAP_DBG_ON_OFF)
#define BAP_DBG_ProtocolVersionError(dummy) \
    (BAP_DBG_DebugInfoTable[3] |= (uint8_t)0x08u)
#else
#define BAP_DBG_ProtocolVersionError(dummy) BAP_DUMMY_VOID_FUNCTION
#endif


/**
 *  Zeigt an, dass bei der Ueberpruefung der BAP-Config-Nachricht keine
 *  Uebereinstimmung der Datenfestlegung gefunden wurde (LSG-Def oder FctMask)
 *  und speichert das Ereignis im Diagnose-Speicher bis zum naechsten Auslesen.
 *
 *  @remarks Der Zustand wird im Diagnose-Speicher im Datenbyte 2,
 *      Maske 0x04 gehalten.
 */
#ifdef BAP_DBG_PER_LSG
BAP_IMPL_FAR void BAP_DBG_DataDefinitionError(lsgId_t aLsgId);
#elif defined (BAP_DBG_ON_OFF)
#define BAP_DBG_DataDefinitionError(dummy) \
    (BAP_DBG_DebugInfoTable[3] |= (uint8_t)0x04u)
#else
#define BAP_DBG_DataDefinitionError(dummy) BAP_DUMMY_VOID_FUNCTION
#endif


#ifdef BAP_FSG
/**
 *  Zeigt an, dass entweder eine GetAll-Nachricht versendet wurde oder dass
 *  gerade eine GetAll-Anfrage beantwortet wird und speichert das Ereignis
 *  im Diagnose-Speicher bis zum naechsten Auslesen.
 *
 *  @remarks Der Zustand wird im Diagnose-Speicher im Datenbyte 2,
 *      Maske 0x02 gehalten.
 */
#ifdef BAP_DBG_PER_LSG
BAP_IMPL_FAR void BAP_DBG_GetAllEvent(lsgId_t aLsgId);
#elif defined (BAP_DBG_ON_OFF)
#define BAP_DBG_GetAllEvent(dummy) \
    (BAP_DBG_DebugInfoTable[3] |= (uint8_t)0x02u)
#else
#define BAP_DBG_GetAllEvent(dummy) BAP_DUMMY_VOID_FUNCTION
#endif
#endif /* BAP_FSG */


/**
 *  Zeigt an, dass eine Nachricht an die Anwendung gemeldet wurde.
 *  Das Ereignis wird beim Auslesen des Diagnose-Speichers geloescht.
 *
 *  @remarks Der Zustand wird im Diagnose-Speicher im Datenbyte 3,
 *      Maske 0x01 gehalten.
 */
#if defined(BAP_DBG_PER_LSG) || defined(BAP_DBG_ON_OFF)
BAP_IMPL_FAR void BAP_DBG_IncomingMessageEvent(lsgId_t aLsgId, fctId_t aFctId, BapOpCodes_et aeOpCode);
#else
#define BAP_DBG_IncomingMessageEvent(dummy1,dummy2,dummy3) BAP_DUMMY_VOID_FUNCTION
#endif


/**
 *  Setzt dauerhaft den Zustand des Heartbeat-Mechanismus (FSG) bzw. der
 *  Heartbeat-Ueberwachung. Ein Heartbeat-Timeout-Error setzt das Bit
 *  automatisch zurueck.
 *
 *  @remarks Der Zustand wird im Diagnose-Speicher im Datenbyte 3,
 *      Maske 0x20 gehalten.
 */
#if defined (BAP_DBG_PER_LSG) || defined (BAP_DBG_ON_OFF)
BAP_IMPL_FAR void BAP_DBG_SetHeartbeatState(lsgId_t aLsgId, bool_t bHeartbeatOn);
#else
#define BAP_DBG_SetHeartbeatState(dummy1, dummy2) BAP_DUMMY_VOID_FUNCTION
#endif


#ifdef BAP_ASG
/**
 *  Zeigt an, dass ein BapErr_RequestTimeout an die Applikation gemeldet wurde und
 *  speichert den Fehler im Diagnose-Speicher bis zum naechsten Auslesen.
 *
 *  @see BapErr_RequestTimeout
 *
 *  @remarks Der Zustand wird im Diagnose-Speicher im Datenbyte 3,
 *      Maske 0x04 gehalten.
 */
#ifdef BAP_DBG_PER_LSG
BAP_IMPL_FAR void BAP_DBG_RequestTimeoutError(lsgId_t aLsgId);
#elif defined(BAP_DBG_ON_OFF)
#define BAP_DBG_RequestTimeoutError(dummy) \
    (BAP_DBG_DebugInfoTable[4] |= (uint8_t)0x04u)
#else
#define BAP_DBG_RequestTimeoutError(dummy) BAP_DUMMY_VOID_FUNCTION
#endif
#endif /* BAP_ASG */


/**
 *  Zeigt an, dass ein BapErr_RetryTimeout an die Applikation gemeldet wurde und
 *  speichert den Fehler im Diagnose-Speicher bis zum naechsten Auslesen.
 *
 *  @see BapErr_RetryTimeout
 *
 *  @remarks Der Zustand wird im Diagnose-Speicher im Datenbyte 3,
 *      Maske 0x02 gehalten.
 */
#ifdef BAP_DBG_PER_LSG
BAP_IMPL_FAR void BAP_DBG_RetryTimeoutError(lsgId_t aLsgId);
#elif defined (BAP_DBG_ON_OFF)
#define BAP_DBG_RetryTimeoutError(dummy) \
    (BAP_DBG_DebugInfoTable[4] |= (uint8_t)0x02u)
#else
#define BAP_DBG_RetryTimeoutError(dummy) BAP_DUMMY_VOID_FUNCTION
#endif


#ifdef BAP_FSG
/**
 *  Speichert das Ereignis eines Heartbeat-Umlaufs (also alle Nachrichten
 *  wurden ueber den HB-Mechanismus mindestens einmal ausgesendet) im
 *  Diagnose-Speicher bis zum naechsten Auslesen.
 *
 *  @remarks Der Zustand wird im Diagnose-Speicher im Datenbyte 3,
 *      Maske 0x01 gehalten.
 */
#ifdef BAP_DBG_PER_LSG
BAP_IMPL_FAR void BAP_DBG_HeartbeatLoopEvent(lsgId_t aLsgId);
#elif defined (BAP_DBG_ON_OFF)
#define BAP_DBG_HeartbeatLoopEvent(dummy) \
    (BAP_DBG_DebugInfoTable[4] |= (uint8_t)0x01u)
#else
#define BAP_DBG_HeartbeatLoopEvent(dummy) BAP_DUMMY_VOID_FUNCTION
#endif
#endif /* BAP_FSG */


/**
 *  Speichert das Ereignis dass ein HB gesendet wurde (FSG) bzw empfangen wurde (ASG)
 *  im Diagnose-Speicher bis zum naechsten Auslesen.
 *
 *  @remarks Der Zustand wird im Diagnose-Speicher im Datenbyte 4,
 *      Maske 0x80 gehalten.
 */
#ifdef BAP_DBG_PER_LSG
BAP_IMPL_FAR void BAP_DBG_HeartbeatProcessedEvent(lsgId_t aLsgId);
#elif defined (BAP_DBG_ON_OFF)
#define BAP_DBG_HeartbeatProcessedEvent(dummy) \
    (BAP_DBG_DebugInfoTable[5] |= (uint8_t)0x80u)
#else
#define BAP_DBG_HeartbeatProcessedEvent(dummy) BAP_DUMMY_VOID_FUNCTION
#endif


/**
 *  Speichert das Ereignis dass ein HB-Timeout-Fehler aufgetreten ist im
 *  Diagnose-Speicher bis zum naechsten Auslesen.
 *
 *  @see BapErr_HeartbeatTimeout
 *
 *  @remarks Der Zustand wird im Diagnose-Speicher im Datenbyte 4,
 *      Maske 0x40 gehalten.
 */
#ifdef BAP_DBG_PER_LSG
BAP_IMPL_FAR void BAP_DBG_HeartbeatTimeoutError(lsgId_t aLsgId);
#elif defined (BAP_DBG_ON_OFF)
#define BAP_DBG_HeartbeatTimeoutError(dummy) \
    (BAP_DBG_DebugInfoTable[5] |= (uint8_t)0x40u)
#else
#define BAP_DBG_HeartbeatTimeoutError(dummy) BAP_DUMMY_VOID_FUNCTION
#endif

/**
 *  Speichert das Ereignis, dass fuer eine Funktion eine Retry-Ueberwachung
 *  gestartet wurde bis zum naechsten Auslesen des Diagnose-Speichers.
 *
 *  @remarks Der Zustand wird im Diagnose-Speicher im Datenbyte 4,
 *      Maske 0x20 gehalten.
 */
#ifdef BAP_DBG_PER_LSG
BAP_IMPL_FAR void BAP_DBG_RetryMntStartedEvent(lsgId_t aLsgId);
#elif defined (BAP_DBG_ON_OFF)
#define BAP_DBG_RetryMntStartedEvent(dummy) \
    (BAP_DBG_DebugInfoTable[5] |= (uint8_t)0x20u)
#else
#define BAP_DBG_RetryMntStartedEvent(dummy) BAP_DUMMY_VOID_FUNCTION
#endif


/**
 *  Speichert das Ereignis, dass fuer eine Funktion der Request wiederholt wurde
 *  bis zum naechsten Auslesen des Diagnose-Speichers.
 *
 *  @remarks Der Zustand wird im Diagnose-Speicher im Datenbyte 4,
 *      Maske 0x10 gehalten.
 */
#ifdef BAP_DBG_PER_LSG
BAP_IMPL_FAR void BAP_DBG_RetryProvokedEvent(lsgId_t aLsgId);
#elif defined (BAP_DBG_ON_OFF)
#define BAP_DBG_RetryProvokedEvent(dummy) \
    (BAP_DBG_DebugInfoTable[5] |= (uint8_t)0x10u)
#else
#define BAP_DBG_RetryProvokedEvent(dummy) BAP_DUMMY_VOID_FUNCTION
#endif


/**
 *  Speichert das Ereignis, dass fuer eine aktive Retry-Ueberwachung eine
 *  Antwort erhalten wurde, welche diese Ueberwachung ausgeschaltet hat.
 *  Das Auslesen des Diagnose-Speichers loescht das Ereignis.
 *
 *  @remarks Der Zustand wird im Diagnose-Speicher im Datenbyte 4,
 *      Maske 0x08 gehalten.
 */
#ifdef BAP_DBG_PER_LSG
BAP_IMPL_FAR void BAP_DBG_RetryAnsweredEvent(lsgId_t aLsgId);
#elif defined (BAP_DBG_ON_OFF)
#define BAP_DBG_RetryAnsweredEvent(dummy) \
    (BAP_DBG_DebugInfoTable[5] |= (uint8_t)0x08u)
#else
#define BAP_DBG_RetryAnsweredEvent(dummy) BAP_DUMMY_VOID_FUNCTION
#endif


/**
 *  Speichert das Ereignis, dass fuer eine aktive Retry-Ueberwachung der
 *  Timer retriggert wurde. Dies tritt auf wenn der Request erfolgreich
 *  versendet wurde. Das Auslesen des Diagnose-Speichers loescht das Ereignis.
 *
 *  @remarks Der Zustand wird im Diagnose-Speicher im Datenbyte 4,
 *      Maske 0x04 gehalten.
 */
#ifdef BAP_DBG_PER_LSG
BAP_IMPL_FAR void BAP_DBG_RetryRetriggeredEvent(lsgId_t aLsgId);
#elif defined (BAP_DBG_ON_OFF)
#define BAP_DBG_RetryRetriggeredEvent(dummy) \
    (BAP_DBG_DebugInfoTable[5] |= (uint8_t)0x04u)
#else
#define BAP_DBG_RetryRetriggeredEvent(dummy) BAP_DUMMY_VOID_FUNCTION
#endif


/**
 *  Speichert das Ereignis, das der Retry-Timer gestoppt wurde
 *  (Startbotschaft einer segmentierten Nachricht erhalten) im Diagnose-Speicher
 *  bis zum naechsten Auslesen.
 *
 *  @remarks Der Zustand wird im Diagnose-Speicher im Datenbyte 4,
 *      Maske 0x02 gehalten.
 */
#ifdef BAP_DBG_PER_LSG
BAP_IMPL_FAR void BAP_DBG_RetryStoppedEvent(lsgId_t aLsgId);
#elif defined (BAP_DBG_ON_OFF)
#define BAP_DBG_RetryStoppedEvent(dummy) \
    (BAP_DBG_DebugInfoTable[5] |= (uint8_t)0x02u)
#else
#define BAP_DBG_RetryStoppedEvent(dummy) BAP_DUMMY_VOID_FUNCTION
#endif


/**
 *  Zeigt an, dass ein BapErr_Busy an die Applikation gemeldet wurde und
 *  speichert den Fehler im Diagnose-Speicher bis zum naechsten Auslesen.
 *
 *  @see BapErr_Busy
 *
 *  @remarks Der Zustand wird im Diagnose-Speicher im Datenbyte 4,
 *      Maske 0x01 gehalten.
 */
#ifdef BAP_DBG_PER_LSG
BAP_IMPL_FAR void BAP_DBG_RetryBusyError(lsgId_t aLsgId);
#elif defined (BAP_DBG_ON_OFF)
#define BAP_DBG_RetryBusyError(dummy) \
    (BAP_DBG_DebugInfoTable[5] |= (uint8_t)0x01u)
#else
#define BAP_DBG_RetryBusyError(dummy) BAP_DUMMY_VOID_FUNCTION
#endif



/**
 *  Zeigt an, dass die Task-Zeit wegen hoher Anzahl an Sende- und Emfpangs-
 *  vorgaengen auf ein vordefiniertes Mass begrenzt wurde
 *  speichert den Fehler im Diagnose-Speicher bis zum naechsten Auslesen.
 *
 *  @see BapErr_BadDataLength
 *
 *  @remarks Der Zustand wird im Diagnose-Speicher im Datenbyte 5,
 *      Maste 0x10 gehalten.
 */
#ifdef BAP_DBG_PER_LSG
BAP_IMPL_FAR void BAP_DBG_TaskTimeLimitEvent(void);
#elif defined(BAP_DBG_ON_OFF)
#define BAP_DBG_TaskTimeLimitEvent() \
    (BAP_DBG_DebugInfoTable[6] |= (uint8_t)0x10u)
#else
#define BAP_DBG_TaskTimeLimitEvent() BAP_DUMMY_VOID_FUNCTION
#endif


/**
 *  Zeigt an, dass ein BapErr_BadDataLength an die Applikation gemeldet wurde und
 *  speichert den Fehler im Diagnose-Speicher bis zum naechsten Auslesen.
 *
 *  @see BapErr_BadDataLength
 *
 *  @remarks Der Zustand wird im Diagnose-Speicher im Datenbyte 5,
 *      Maste 0x08 gehalten.
 */
#ifdef BAP_DBG_PER_LSG
BAP_IMPL_FAR void BAP_DBG_BadDataLengthError(lsgId_t aLsgId);
#elif defined(BAP_DBG_ON_OFF)
#define BAP_DBG_BadDataLengthError(dummy) \
    (BAP_DBG_DebugInfoTable[6] |= (uint8_t)0x08u)
#else
#define BAP_DBG_BadDataLengthError(dummy) BAP_DUMMY_VOID_FUNCTION
#endif


/**
 *  Zeigt an, dass ein BapErr_DataLost an die Applikation gemeldet wurde und
 *  speichert den Fehler im Diagnose-Speicher bis zum naechsten Auslesen.
 *
 *  @see BapErr_DataLost
 *
 *  @remarks Der Zustand wird im Diagnose-Speicher im Datenbyte 5,
 *      Maste 0x04 gehalten.
 */
#ifdef BAP_DBG_PER_LSG
BAP_IMPL_FAR void BAP_DBG_DataLostError(void);
#elif defined(BAP_DBG_ON_OFF)
#define BAP_DBG_DataLostError() \
    (BAP_DBG_DebugInfoTable[6] |= (uint8_t)0x04u)
#else
#define BAP_DBG_DataLostError() BAP_DUMMY_VOID_FUNCTION
#endif


/**
 *  Speichere das Ereignis, dass begonnen wurde, eine segmentierte Nachricht
 *  zu versenden im Diagnose-Speicher bis zum naechsten Auslesen.
 *
 *  @remarks Der Zustand wird im Diagnose-Speicher im Datenbyte 5,
 *      Maske 0x02 gehalten.
 */
#ifdef BAP_DBG_PER_LSG
BAP_IMPL_FAR void BAP_DBG_TxStartMsgEvent(lsgId_t aLsgId);
#elif defined (BAP_DBG_ON_OFF)
#define BAP_DBG_TxStartMsgEvent(dummy) \
    (BAP_DBG_DebugInfoTable[6] |= (uint8_t)0x02u)
#else
#define BAP_DBG_TxStartMsgEvent(dummy) BAP_DUMMY_VOID_FUNCTION
#endif


/**
 *  Speichere das Ereignis, dass eine Startnachricht einer segmentierten
 *  Nachricht empfangen wurde im Diagnose-Speicher bis zum naechsten Auslesen
 *
 *  @remarks Der Zustand wird im Diagnose-Speicher im Datenbyte 5,
 *      Maske 0x01 gehalten.
 */
#ifdef BAP_DBG_PER_LSG
BAP_IMPL_FAR void BAP_DBG_RxStartMsgEvent(lsgId_t aLsgId);
#elif defined (BAP_DBG_ON_OFF)
#define BAP_DBG_RxStartMsgEvent(dummy) \
    (BAP_DBG_DebugInfoTable[6] |= (uint8_t)0x01u)
#else
#define BAP_DBG_RxStartMsgEvent(dummy) BAP_DUMMY_VOID_FUNCTION
#endif


/**
 *  Speichere das Ereignis, dass eine segmentierte Nachricht komplett
 *  versendet wurde im Diagnose-Speicher bis zum naechsten Auslesen.
 *
 *  @remarks Der Zustand wird im Diagnose-Speicher im Datenbyte 6,
 *      Maske 0x80 gehalten.
 */
#ifdef BAP_DBG_PER_LSG
BAP_IMPL_FAR void BAP_DBG_TxSegMsgCompleteEvent(lsgId_t aLsgId);
#elif defined (BAP_DBG_ON_OFF)
#define BAP_DBG_TxSegMsgCompleteEvent(dummy) \
    (BAP_DBG_DebugInfoTable[7] |= (uint8_t)0x80u)
#else
#define BAP_DBG_TxSegMsgCompleteEvent(dummy) BAP_DUMMY_VOID_FUNCTION
#endif


/**
 *  Speichere das Ereignis, dass eine segmentierte Nachricht vollstaendig
 *  empfangen wurde im Diagnose-Speicher bis zum naechsten Auslesen.
 *
 *  @remarks Der Zustand wird im Diagnose-Speicher im Datenbyte 6,
 *      Maske 0x40 gehalten.
 */
#ifdef BAP_DBG_PER_LSG
BAP_IMPL_FAR void BAP_DBG_RxSegMsgCompleteEvent(lsgId_t aLsgId);
#elif defined (BAP_DBG_ON_OFF)
#define BAP_DBG_RxSegMsgCompleteEvent(dummy) \
    (BAP_DBG_DebugInfoTable[7] |= (uint8_t)0x40u)
#else
#define BAP_DBG_RxSegMsgCompleteEvent(dummy) BAP_DUMMY_VOID_FUNCTION
#endif


/**
 *  Zeigt an, dass an den BPL ein Intertelegrammzeitfehler bei der
 *  Ueberwachung des Empfangs einer segmentierten Nachricht aufgetreten ist
 *  gemeldet wurde und speichert das Ereignis im Diagnose-Speicher bis
 *  zum naechsten Auslesen.
 *
 *  @see BapErr_TimeoutSegmentation
 *
 *  @remarks Der Zustand wird im Diagnose-Speicher im Datenbyte 6,
 *      Maske 0x20 gehalten.
 */
#ifdef BAP_DBG_PER_LSG
BAP_IMPL_FAR void BAP_DBG_IntertelegramTmoutErr(lsgId_t aLsgId);
#elif defined (BAP_DBG_ON_OFF)
#define BAP_DBG_IntertelegramTmoutErr(dummy) \
    (BAP_DBG_DebugInfoTable[7] |= (uint8_t)0x20u)
#else
#define BAP_DBG_IntertelegramTmoutErr(dummy) BAP_DUMMY_VOID_FUNCTION
#endif


/**
 *  Zeigt an, dass eine segmentierte Nachricht empfangen wurde, die
 *  laenger als der dafuer vorgesehene Empfangspuffer ist.
 *  Die Nachricht wurde verworfen und der Fehler an die Applikation
 *  gemeldet.
 *  Dieses Ereignis bleibt im Diagnose-Speicher bis zum naechsten Auslesen
 *  gespeichert.
 *
 *  @see BapErr_OversizeSegmentation
 *
 *  @remarks Der Zustand wird im Diagnose-Speicher im Datenbyte 6,
 *      Maske 0x10 gehalten.
 */
#ifdef BAP_DBG_PER_LSG
BAP_IMPL_FAR void BAP_DBG_MsgOversizeError(lsgId_t aLsgId);
#elif defined (BAP_DBG_ON_OFF)
#define BAP_DBG_MsgOversizeError(dummy) \
    (BAP_DBG_DebugInfoTable[7] |= (uint8_t)0x10u)
#else
#define BAP_DBG_MsgOversizeError(dummy) BAP_DUMMY_VOID_FUNCTION
#endif


/**
 *  Zeigt an, dass ein Sequenzfehler an die Applikation gemeldet wurde
 *  und speichert das Ereignis im Diagnose-Speicher bis zum naechsten Auslesen.
 *
 *  @see BapErr_SequenceNumber, BapErr_IllegalSequence
 *
 *  @remarks Der Zustand wird im Diagnose-Speicher im Datenbyte 6,
 *      Maske 0x08 gehalten.
 */
#ifdef BAP_DBG_PER_LSG
BAP_IMPL_FAR void BAP_DBG_SequenceError(lsgId_t aLsgId);
#elif defined (BAP_DBG_ON_OFF)
#define BAP_DBG_SequenceError(dummy) \
    (BAP_DBG_DebugInfoTable[7] |= (uint8_t)0x08u)
#else
#define BAP_DBG_SequenceError(dummy) BAP_DUMMY_VOID_FUNCTION
#endif


/**
 *  Zeigt an, dass Daten empfangen wurde, welche verworfen wurden.
 *  Dies wurde nicht an die Applikation gemeldet.
 *  Ursache koennen sein:
 *  Empfang einer Nachricht mit unbekannter LsgId oder FctId.
 *  Empfang einer segmentierten Nachricht auf einem ungueltigen Kanal.
 *  @since BAP1.3: Empfang einer Fct.Id die nicht in der aktiven Fct.list enthalten ist
 *
 *  @remarks Der Zustand wird im Diagnose-Speicher im Datenbyte 6,
 *      Maske 0x04 gehalten.
 */
#ifdef BAP_DBG_PER_LSG
BAP_IMPL_FAR void BAP_DBG_RxDataPurgedEvent(void);
#elif defined (BAP_DBG_ON_OFF)
#define BAP_DBG_RxDataPurgedEvent() \
    (BAP_DBG_DebugInfoTable[7] |= (uint8_t)0x04u)
#else
#define BAP_DBG_RxDataPurgedEvent() BAP_DUMMY_VOID_FUNCTION
#endif


/**
 *  Zeigt an, dass der darunterliegende Treiber den erfolgreichen
 *  Versand einer BAP-Nachricht bestaetigt hat.
 *  Das Auslesen des Diagnose-Speichers loescht dieses Ereignis.
 *
 *  @remarks Der Zustand wird im Diagnose-Speicher im Datenbyte 6,
 *      Maske 0x02 gehalten.
 */
#ifdef BAP_DBG_PER_LSG
BAP_IMPL_FAR void BAP_DBG_TxEvent(void);
#elif defined (BAP_DBG_ON_OFF)
#define BAP_DBG_TxEvent() \
    (BAP_DBG_DebugInfoTable[7] |= (uint8_t)0x02u)
#else
#define BAP_DBG_TxEvent() BAP_DUMMY_VOID_FUNCTION
#endif


/**
 *  Zeigt an, dass der BAP-Stack Nachrichten vom unterliegenden
 *  Treiber empfangen hat.
 *  Das Auslesen des Diagnose-Speichers loescht dieses Ereignis
 *
 *  @remarks Der Zustand wird im Diagnose-Speicher im Datenbyte 6,
 *      Maske 0x01 gehalten.
 */
#ifdef BAP_DBG_PER_LSG
BAP_IMPL_FAR void BAP_DBG_RxEvent(void);
#elif defined (BAP_DBG_ON_OFF)
#define BAP_DBG_RxEvent() \
    (BAP_DBG_DebugInfoTable[7] |= (uint8_t)0x01u)
#else
#define BAP_DBG_RxEvent() BAP_DUMMY_VOID_FUNCTION
#endif

#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#   define BAP_START_SEC_CODE_CYCLIC
#   include <BAP_MemMap.h>

#if defined(BAP_DBG_PER_LSG) || defined(BAP_DBG_ON_OFF)
/**
 *  Diese Funktion versendet bei Bedarf die Diagnose-Nachricht
 *  ueber die Callback-Funktion BAP_SendDebugInfo.
 */
BAP_IMPL_FAR void BAP_DBG_Task(void);
#else
#define BAP_DBG_Task() BAP_DUMMY_VOID_FUNCTION
#endif

#   define BAP_STOP_SEC_CODE_CYCLIC
#   include <BAP_MemMap.h>
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>

/**
 * Diese Funktion bietet externen Zugriff auf die Variable Bap_gDebugLsgId
 * (notwendig fuer CUnit-Tests).
 */
BAP_IMPL_FAR lsgId_t
BAP_DBG_GetDebugLsgId(void);


/**
 * Diese Funktion bietet externen Aenderungsmoeglichkeiten fuer die Variable Bap_gDebugLsgId
 * (notwendig fuer CUnit-Tests).
 */
BAP_IMPL_FAR void
BAP_DBG_SetDebugLsgId(lsgId_t LsgId);

#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>

#   ifdef __cplusplus
}
#   endif

#endif      /* #ifndef BAP_DEBUG_DEBUG_H */
