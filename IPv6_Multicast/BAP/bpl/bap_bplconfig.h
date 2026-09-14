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
 *  Diese Datei enthaelt die Datentypen und Schnittstellen auf
 *  die konfigurierten Daten des Bedien- und Anzeigeprotokolls
 *  welche den BPL (Protokollschicht 5) betreffen.
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
 * 2020-03-24   1.11.1      KUL         [SSWCCB-1302] bOngoingStatusAll flag added to struct BapBplRamRow_t
 * 2006-04-12   1.4         ALA         Unterstuetzung fuer HB-Trigger.
 * 2006-04-12   1.4         ALA         Unterstuetzung fuer BAP_ROM_DATA_FAR.
 * 2005-03-31   1.3         ALA         uint16_t u16Retrytimer volatile entfernt 
 *                                      nach Verbesserung des IRQ Handlings
 * 2004-11-17   1.2         JOK         uint16_t u16Retrytimer mit volatile versehen
 * 2004-06-07   1.1         JOK         Enumeration BapDirection_t entfernt
 ******************************************************************/

#ifndef BAP_BPLCONFIG_H
#define BAP_BPLCONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Systemincludes mit <...> */

/* Bibliotheken von externen Herstellen mit <...> */

/* Eigene Header-Dateien "..." */
#include "bap_config.h"

/* Makro-Definitionen */

/* Typ-Definitionen */


/**
 *  Dieses Bitfeld enthaelt die Anzahl der noch durchzufuehrenden Retrys
 *  und in einem Bit, ob ueberhaupt eine Retry-Ueberwachung laeuft.
 */
typedef struct BapBplRetryOrProcessingFlags_t
{
    /** enthaelt die Anzahl noch moeglicher Retries (Abwaertszaehler) */
    bitfield_t u6RetryCounter:6;

    /** 0, falls die Retry-Ueberwachung abgeschaltet wurde (ASG), 1, falls die Retry-Ueberwachung eingeschaltet ist (ASG)
     *  0, falls ProcessingRequired-Timer gestoppt sind (FSG) 1, falls die ProcessingRequired-Timer laufen (FSG)
     */
    bitfield_t bRetryOrProcessingActive:1;

    /** 1, falls mindestens eine Nachricht wirklich gesendet wurde und eine Retry-Ueberwachung laeuft 
     *  Kommt bei der dynamischen Kanalvergabe zum Tragen. Laueft der Timer ab und dieses Bit ist nicht 
     *  gesetzt gibt es einen RequestTimeout Fehler --> Es war nicht moeglich zu senden da Kanaele belegt. 
     */  
    bitfield_t bRequestSent:1;
} BapBplRetryOrProcessingFlags_ot;


/**
 *  Diese Struktur enthaelt Zustaende fuer ein BPL-Datenelement
 */
typedef struct BapBplRamRow_t
{
	/** Flag to detect ongoing StatusAll transmission on the LSG */
	uint8_t bOngoingStatusAll;

    /** Aktueller Wert des Retry- oder Processing-Timers bei einer laufenden Ueberwachung */
    uint16_t u16RetryOrProcessingTimer;

    /** Flags fuer die Retry-Ueberwachung @see BapBplRetryOrProcessingFlags_t */
    BapBplRetryOrProcessingFlags_ot fRetryOrProcessingFlags;
} BapBplRamRow_ot;
/* BapBplRamRow_pot ist in bap_config.h definiert */

/* Const Deklarationen */

/* Externe globale Variablen */

/* Deklarationen von Funktionen */

#ifdef __cplusplus
}
#endif

#endif      /* #ifndef BAP_BPLCONFIG_H */
