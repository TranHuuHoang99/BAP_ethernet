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
 *  Diese Datei enthaelt die Deklaration (Schnittstelle) der
 *  busspezifischen Funktionen fuer die BCL Schicht im BAP Projekt.
 *
 *  Je nach Compiler-Schalter werden die Bussysteme eingebunden
 *  oder leere Funktionen dafuer erzeugt.
 *
 *  Aktuell werden folgende Bussysteme unterstuetzt:
 *      - CAN
 *
 ******************************************************************
 *
 * Versionsgeschichte (ohne SCM)
 *
 * Datum        Version     Autor       Beschreibung
 * ----------------------------------------------------------------
 * 2023-10-10	1.12.2		DRH			[EEARCH-35935] Release preparation, adapt Copyright date and version number.
 * 2022-10-21	1.12.1		DRH			[SSWPPB-296] Release preparation, adapt Copyright date and version number.
 * 2022-06-17	1.12.0		DRH			[SSWPPB-269] Release preparation, adapt Copyright date and version number.
 * 2021-12-07	1.11.3		JEO			[SSWPPB-244] Release preparation, adapt Copyright date and version number.
 * 2020-09-30   1.11.2      KUL         [SSWPPB-70] Use of BAP_USES_ETH to support POSIX based ECUs with Ethernet
 * 2017-07-24   1.10.0      FHA         [SSWCCB-2391] Schnelle Suche TX-PDU
 * 2017-02-28   1.9.0       FST         [SSWCCB-1545] SSW-Lokatierungs-Pragmas eingefuegt
 * 2015-02-09   1.8.0.2     FST         Verringerung der zyklomatischen Komplexitaet, Aufspaltung zweier Funktionen
 * 2014-07-16   1.8.0       WWU         [SSWCCB-1862] Makro BAP_USES_PDU fuer PDU-Router erweitert.
 * 2013-02-06   1.7.0       WWU         Funktionsname Umbenannt, wegen Misra : Identifier exceeds 31 characters
 * 2010-08-17   1.5.1       RPI         Include der bap_debug.h anstatt BAP_DUMMY_VOID_FUNCTION ein zweites 
 *                                      mal zu definieren.
 * 2006-11-20   1.4.1       ALA         Zur Laufzeitoptimierung der Funktion BAP_BCL_InitCanDrvTxConfirmationFlags
 *                                      den Parameter aLsgId hinzugefuegt.
 * 2005-04-29   1.3         ALA         Funktion BAP_BCL_CanReceiveTask hinzugefuegt, LIN und IPC Bus
 *                                      werden seit BAP 1.0 nicht mehr unterstuetzt. Deklarationen entfernt.
 * 2004-11-17   1.2         JOK         Funktionen BAP_BCL_Can/Lin/IPCRxNotifyTask() entfernt
 * 2004-11-17   1.2         JOK         Funktionen BAP_BCL_SendOnCan/Lin/IPC() entfernt
 * 2004-06-07   1.1         JOK         Spezielle Funktion BAP_BCL_LowLevelCanTxTask() entfernt
 * 2004-06-07   1.1         JOK         Spezielle Funktion BAP_BCL_LowLevelLinTxTask() entfernt
 * 2004-06-07   1.1         JOK         Spezielle Funktion BAP_BCL_ProcessNotSegmentedCanRxMsg() entfernt
 * 2004-06-07   1.1         JOK         Spezielle Funktion BAP_BCL_ProcessNotSegmentedLinRxMsg() entfernt
 * 2004-06-07   1.1         JOK         Spezielle Funktion BAP_BCL_ProcessSegmentedCanRxMsg() entfernt
 * 2004-06-07   1.1         JOK         Spezielle Funktion BAP_BCL_ProcessSegmentedLinRxMsg() entfernt
 ******************************************************************/

#ifndef BAP_BCLBUS_H
#define BAP_BCLBUS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Systemincludes mit <...> */

/* Bibliotheken von externen Herstellen mit <...> */

/* Eigene Header-Dateien "..." */
#include "bap_debug.h"
#include "bap_bclconfig.h"

/* Makro-Definitionen */

/** Konstante fuer eine nicht vorhandene Funktion */
#define BAP_DUMMY_FUNCTION      (BapErr_NotImplemented)

/* Typ-Definitionen */

/* Const Deklarationen */

/* Externe globale Variablen */

/* Deklarationen von Funktionen */

#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>

#if defined(BAP_USES_CAN) || defined(BAP_USES_FR) || defined(BAP_USES_PDUR) || defined(BAP_USES_ETH)
/**
 *  Uebertragungsmediumspezifische Task-Funktion, die alle
 *  zu versendenden Datenelemente ueber CAN uebertraegt.
 *
 *  Die Auswahl der zu sendenden Daten wird ueber eine Heuristik
 *  gemacht, um ein faires Verhalten zwischen den einzelnen
 *  Datenelementen zu erreichen. Die Datenelemente konkurrieren
 *  um den Zugriff auf den CAN-Bus und werden noch ueber die
 *  Inhibit-Zeit zurueckgehalten.
 */
BAP_IMPL_FAR void
BAP_BCL_CanSendTask(void);

/**
 * Auslagerung einer Pruefung aus CanSendTask: wurde ein Tx-Request gefunden?
 */
BAP_IMPL_FAR bool_t
BAP_BCL_CanSendTaskTxReq(
#ifdef BAP_USES_SEGMENTATION
		BapLsgRomRow_pot poLsgRomRow
#endif /* BAP_USES_SEGMENTATION */
#ifdef BAP_TASKTIME_LIMIT
		, BapLsgState_pot pfLsgState
#endif /* BAP_TASKTIME_LIMIT */
#ifndef BAP_USES_SEGMENTATION
#ifndef BAP_TASKTIME_LIMIT
		void
#endif  /* BAP_TASKTIME_LIMIT */
#endif  /* BAP_USES_SEGMENTATION */
);

/**
 *  Uebertragungsmediumspezifische Task-Funktion, die alle
 *  empfangenenen Datenelemente von CAN aus dem Ringpuffer
 *  an den BCL uebergibt.
 */
BAP_IMPL_FAR void
BAP_BCL_CanReceiveTask(void);

/**
 *  Initialisiert die Tx Confirmation Flags des CAN Treibers
 *  fuer die von BAP verwendeten CAN-Ids.
 *
 *  @param apoLsgRomRow Das Steuergeraet, dessen Confirmationflags initialisiert werden
 *
 *  @remarks
 *  Die uebergebene LsgId verringert die Suchzeit fuer CAN-Ids, die von diesem Steuergeraet nicht verwendet werden.
 *  Es werden nur bei den CAN-Ids, welche nicht von gestarteten Lsgs verwendet werden, die Confirmation-Flags initialisiert.
 *
 */
BAP_IMPL_FAR void
BAP_BCL_InitCanDrvTxCfmFlags(BapLsgRomRow_pot apoLsgRomRow);

/**
 *  Diese Funktion dient zum Schreiben von Datenelementen in dem Sende-Ringbuffer. Jedes Datenelement darf nur einmal enthalten sein.
 *  Mehrfaches Eintragen eines Datenelements ist aufgrund einer Ueberpruefung ausgeschlossen.
 *
 *  @param poBusTxRomRow Ist der Pointer von dem Datenelement welches in den Ringbuffer geschrieben werden soll.
 *
 */
BAP_IMPL_FAR void
BAP_BCL_CanTxBufferWrite(BapCanTxRomRow_pot apoBusTxRomRow);

/**
 *  Diese Funktion dient zum Lesen von Datenelementen aus dem Sende-Ringbuffer. Nach dem Lesen wird der Speiecherbereich
 *  des Datenelements wieder freigebenen.
 *
 *  @param u8InhibitIndex Ist der Index der zulesenden Sende-PDU.
 *
 *  @returns Ein Pointer vom Typ BapCanTxRomRow_pot von dem Datenelement welches versendet werden soll. Es wird ein Nullpointer zurückgegeben
 *  falls kein Datenelement vorliegt.
 *
 */
BapCanTxRomRow_pot
BAP_BCL_CanTxBufferRead(uint8_t u8InhibitIndex);

/**
 *  Diese Funktion dient zum Loeschen von Datenelementen aus dem Sende-Ringbuffer anhand der LSG-ID. Da Lueken innerhalb
 *  des Buffers nicht vorgesehen sind werden die Nachricht bei vorhandensein eines Datenelementen der angeforderten LSG-ID neu sortiert.
 *
 *  @param apoLsgRomRow Ist der Pointer vom logischen Steuergeraet, dessen Sendebereich initailisiert werden soll.
 *
 */
BAP_IMPL_FAR void
BAP_BCL_CanTxBufferInit(BapLsgRomRow_pot apoLsgRomRow);
#else   /*defined(BAP_USES_CAN) || defined(BAP_USES_FR) || defined(BAP_USES_PDUR) || defined(BAP_USES_ETH)*/
#define BAP_BCL_CanSendTask() BAP_DUMMY_VOID_FUNCTION
#define BAP_BCL_CanReceiveTask() BAP_DUMMY_VOID_FUNCTION
#define BAP_BCL_InitCanDrvTxConfirmationFlags(apoLsgRomRow) BAP_DUMMY_VOID_FUNCTION
#define BAP_BCL_CanTxBufferWrite(apoBusTxRomRow) BAP_DUMMY_VOID_FUNCTION
#define BAP_BCL_CanTxBufferRead(u8InhibitIndex) BAP_DUMMY_VOID_FUNCTION
#define BAP_BCL_CanTxBufferInit(apoLsgRomRow) BAP_DUMMY_VOID_FUNCTION
#endif  /*defined(BAP_USES_CAN) || defined(BAP_USES_FR) || defined(BAP_USES_PDUR) || defined(BAP_USES_ETH)*/

#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>

#ifdef __cplusplus
}
#endif

#endif      /* #ifndef BAP_BCLBUS_H */

