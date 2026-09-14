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
 *  Diese Datei enthaelt Hilfsfunktionen fuer die BPL Schicht
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
 * 2006-04-12   1.4         ALA         Unterstuetzung fuer BAP_ROM_DATA_FAR.
 * 2006-04-12   1.4         ALA         Unterstuetzung fuer HB-Trigger
 * 2005-10-24   1.3.1.2     ALA         #include "bap_config" ergaenzt.
 * 2004-11-17   1.2         JOK         struct BapBplRomRow_t* mit const versehen
 * 2004-06-07   1.1         JOK         Laufzeitoptimierung in BAP_BPL_SetNextFctIndex()
 *                                      durch ersetzen der aLsgId durch den Zeiger apoLsgRomRow
 *                                      in die LSG-Tabelle
 ******************************************************************/

#ifndef BAP_BPLUTIL_H
#define BAP_BPLUTIL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Systemincludes mit <...> */

/* Bibliotheken von externen Herstellen mit <...> */

/* Eigene Header-Dateien "..." */
#include "bap_config.h"

/* Makro-Definitionen */

/** Konstante fuer die Heartbeat-Frequenz in ms */
#define BAP_HEARTBEAT_FREQUENCY_MS ((uint16_t) 100)

/* Typ-Definitionen */

/* Const Deklarationen */

/* Externe globale Variablen */

/* Deklarationen von Funktionen */

#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>

#ifdef BAP_FSG
/**
 *  Schaltet lastSentFctIndex auf die naechste Funktion,
 *  bei der bHeartbeatOn gesetzt ist und die in der aktuellen Fct.list enthalten ist..
 *  Setzt im LSG den Index des zuletzt zu sendenden Heartbeat auf den folgenden.
 *
 *  @param apoLsgRomRow bezeichnet das logische Steuergeraet.
 *
 *  @returns FctId im LSG vorhanden.
 *
 *  @remarks Wenn keine FunctionId mit Heartbeat konfiguriert ist und der
 *      Heartbeat-Mechanismus ueber die Heartbeat-Zeit eingeschaltet ist
 *      fuehrt dies zu einer Endlosschleife. Es liegt dann jedoch ein
 *      Konfigurationsfehler vor.
 *
 *      Dieser Fehler kann nicht mittels BAPgen abgefangen werden, da
 *      die Funktionsliste dynamisch geaendert werden kann.
 */
BAP_IMPL_FAR void
BAP_BPL_SetNextFctIndex(BapLsgRomRow_pot apoLsgRomRow);
#endif /* #ifdef BAP_FSG */


#if defined(BAP_USES_METHODS) || defined(BAP_ASG)
/**
 *  Alle retries des LSGs werden gestoppt.
 *
 *  @param apoLsgRomRow bezeichnet das logische Steuergeraet.
 *
 */
BAP_IMPL_FAR void
BAP_BPL_StopRetries (BapLsgRomRow_pot apoLsgRomRow);
#else
#define BAP_BPL_StopRetries(dummy) ((void)0)
#endif  /* #if defined(BAP_USES_METHODS) || defined(BAP_ASG) */

/**
 *  Retriggert den Heartbeat-Dispatcher (im FSG) oder die Heartbeat-Ueberwachung (im ASG)
 *
 *  @param apoLsgRomRow - Zeiger auf die Zeile des logischen Steuergeraetes das retriggert werden soll.
 */
BAP_IMPL_FAR void
BAP_BPL_RetriggerHeartbeat(BapLsgRomRow_pot apoLsgRomRow);

/**
 *  Initialisiert den Heartbeat-Timer mit dem im ROM konfigurierten Wert 
 *
 *  @param apoLsgRomRow - Zeiger auf die Zeile des logischen Steuergeraetes das initialisiert werden soll.
 *
 *  @param au8HeartbeatTime - Heartbeat-Faktor, beim FSG muss dieser Wert immer 1 sein.
 *  
 */
BAP_IMPL_FAR void
BAP_BPL_InitializeHeartbeat(BapLsgRomRow_pot apoLsgRomRow, uint8_t au8HeartbeatTime);

#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>

#ifdef __cplusplus
}
#endif

#endif      /* #ifndef BAP_BPLUTIL_H */

