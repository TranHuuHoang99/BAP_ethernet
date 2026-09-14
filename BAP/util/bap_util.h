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
 *  Diese Datei enthaelt Hilfsfunktionen fuer alle Schichten im
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
 * 2021-12-07	1.11.3		JEO			[SSWPPB-244] Release preparation, adapt Copyright date and version number
 * 2021-03-08   1.11.3      DRH         [SSWPPB-142] Replaced magic numbers by constants
 * 2017-07-31   1.10.0      FHA         [SSWCCB-2474] DLC-Mapping für CAN-FD
 * 2017-03-02	1.9.0       FST         [SSWCCB-1545] SSW-Lokatierungs-Pragmas eingefuegt
 * 2015-03-10	1.8.0.3     FST         [SSWCCB-2188][SSWCCB-2189][SSWCCB-2190] BAP_GetRxPduSize und BAP_GetTxPduSize eingefuegt, waren bisher in bap_bclutil
 * 2013-01-30	1.7         WWU         MISRA-2004 fix
 * 2007-09-13   1.5         ALI         Einige Macros nach bap_user_stdtypes.h verschoben
 * 2006-04-12   1.4         ALA         Unterstuetzung von symbolischen IDs in der Konfiguration.
 * 2006-04-12   1.4         ALA         Unterstuetzung fuer BAP_ROM_DATA_FAR.
 * 2005-07-07   1.3.1       ALA         #include "bap_config.h" hinzugefuegt (wg. BapInternalParameters_t)
 * 2004-11-17   1.2         JOK         #include "bap_types.h" eingefuegt
 * 2004-11-17   1.2         JOK         struct BapLsgRomRow_t* mit const versehen
 ******************************************************************/

#ifndef BAP_UTIL_H
#define BAP_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Systemincludes mit <...> */

/* Bibliotheken von externen Herstellen mit <...> */

/* Eigene Header-Dateien "..." */
#include "bap_types.h"
#include "bap_config.h"

/* Makro-Definitionen */

#ifdef BAP_USES_NAMED_IDS
#define BAP_BINARY_ID    (uint8_t)
#else
#define BAP_BINARY_ID
#endif

/** Konstanten fuer Bitmasken */
#define BAP_BIT7 ((uint8_t) 0x80)
#define BAP_BIT6 ((uint8_t) 0x40)
#define BAP_BIT5 ((uint8_t) 0x20)
#define BAP_BIT4 ((uint8_t) 0x10)
#define BAP_BIT3 ((uint8_t) 0x0F)
#define BAP_BIT2 ((uint8_t) 0x04)
#define BAP_BIT1 ((uint8_t) 0x02)
#define BAP_BIT0 ((uint8_t) 0x01)
#define BAP_BITMASK_00000111 ((uint8_t) 0x07)
#define BAP_BITMASK_00001110 ((uint8_t) 0x0E)
#define BAP_BITMASK_00001111 ((uint8_t) 0x0F)
#define BAP_BITMASK_00010001 ((uint8_t) 0x11)
#define BAP_BITMASK_00011111 ((uint8_t) 0x1F)
#define BAP_BITMASK_00111100 ((uint8_t) 0x3C)
#define BAP_BITMASK_00111111 ((uint8_t) 0x3F)
#define BAP_BITMASK_00110000 ((uint8_t) 0x30)
#define BAP_BITMASK_10000000 ((uint8_t) 0x40)
#define BAP_BITMASK_10001000 ((uint8_t) 0x44)
#define BAP_BITMASK_10011001 ((uint8_t) 0x55)
#define BAP_BITMASK_01110000 ((uint8_t) 0x70)
#define BAP_BITMASK_11000000 ((uint8_t) 0xC0)
#define BAP_BITMASK_11011111 ((uint8_t) 0xDF)
#define BAP_BITMASK_11100000 ((uint8_t) 0xE0)
#define BAP_BITMASK_11110000 ((uint8_t) 0xF0)
#define BAP_BITMASK_11110001 ((uint8_t) 0xF1)
#define BAP_BITMASK_11110111 ((uint8_t) 0xF7)
#define BAP_BITMASK_11111101 ((uint8_t) 0xFD)
#define BAP_BITMASK_11111111 ((uint8_t) 0xFF)


/** Konstante fuer die Anzahl der Bits in einem Byte */
#define BAP_BYTE ((uint8_t) 8)


/* Typ-Definitionen */

/* Const Deklarationen */

/* Externe globale Variablen */
/* @WWU:
 * MISRA-2004 fix: Bap_oPars wird als interne Objekt in ganzen BAP Verwendet
 * Definiere Bap_oPars als globale Variable */

#   define BAP_START_SEC_VAR_NO_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>
extern BapInternalParameters_ot Bap_oPars;
extern BapInternalParameters_ot Bap_oPars_fctlist;
#ifdef BAP_USES_ASR_WRAPPER
extern Boolean BapNmFlags[];
#endif
#   define BAP_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#   include <BAP_MemMap.h>

/* Deklarationen von Funktionen */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
/**
 *  Diese Funktion gibt den Eintrag in der FCT-ROM-Tabelle des adressierten
 *  LSG und der adressierten FCT zurueck.
 *
 *  @param aLsgId bezeichnet das logische Steuergeraet
 *  @param aFctId bezeichnet die Funktion
 *
 *  @returns
 *      Falls diese Funktion existiert einen Zeiger auf den Eintrag in der Tabelle
 *      und sonst NULL.
 */
BapFctRomRow_pot BAP_IMPL_FAR
BAP_GetFctRomRow(DBGVAR lsgId_t aLsgId, DBGVAR fctId_t aFctId);

/**
 *  Diese Funktion gibt den Eintrag in der LSG-ROM-Tabelle des adressierten
 *  LSG zurueck.
 *
 *  @param aLsgId bezeichnet das logische Steuergeraet.
 *
 *  @returns 
 *      Falls der Eintrag existiert ein Zeiger auf den Eintrag in der LSG-ROM-Tabelle 
 *      und sonst NULL.
 *
 */
BapLsgRomRow_pot BAP_IMPL_FAR 
BAP_GetLsgRomRow(DBGVAR lsgId_t aLsgId);  
/*lint -sem(BAP_GetLsgRomRow ,r_null) Funktion kann NULL-Zeiger zurueckliefern */

/**
 *  Diese Funktion gibt den Eintrag in der FCT-ROM-Tabelle des adressierten
 *  LSG und der adressierten FCT zurueck
 *
 *  @param apoLsgRomRow bezeichnet das logische Steuergeraet (darf NULL sein)
 *  @param aFctId bezeichnet die Funktion
 *
 *  @returns
 *      Falls diese Funktion existiert einen Zeiger auf den Eintrag in der Tabelle
 *      und sonst NULL.
 *
 *  @remarks
 *      liefert NULL falls apoLsgRomRow NULL ist.
 */
BapFctRomRow_pot BAP_IMPL_FAR 
BAP_GetLsgFctRomRow(BapLsgRomRow_pot apoLsgRomRow, DBGVAR fctId_t aFctId);
/*lint -sem(BAP_GetLsgFctRomRow ,r_null) Funktion kann NULL-Zeiger zurueckliefern */

#ifndef BAP_ROM_DATA_FAR_EMPTY
/**
 *  Diese Funktion ersetzt die Bibliotheksfunktion memcpy, um BAP_ROM_DATA_FAR Konstanten ins RAM zu kopieren.
 *
 *  @param dest Pointer auf den Zielspeicher
 *  @param source Pointer auf den Quellspeicher
 *  @param length Laenge der Daten die kopiert werden sollen
 */
BAP_IMPL_FAR void 
BAP_RomToRamMemCpy(DBGVAR void * dest, DBGVAR BAP_ROM_DATA_FAR const void * source, DBGVAR const size_t length);
#endif /* #ifndef BAP_ROM_DATA_FAR_EMPTY */


/**
 *  Fuehrt ein MEMSET(apoPars, 0, sizeof(*apoPars)) durch.
 *
 *  @param apoPars - Zeiger auf die zu initialisierende Struktur
 */
BAP_IMPL_FAR void 
BAP_InitInternalParameters(BapInternalParameters_pot apoPars);

/**
 * Gibt die konfigurierte PDU-Groesse an die eingegebene Rx-Msg zurueck
 *
 * @param msg_id
 */
BAP_IMPL_FAR uint16_t
BAP_GetRxPduSize(BapCanMsgId_t msg_id);

/**
 * Gibt die konfigurierte PDU-Groesse an die eingegebene Tx-Msg zurueck
 *
 * @param msg_id
 */
BAP_IMPL_FAR uint16_t
BAP_GetTxPduSize(BapCanMsgId_t msg_id);

#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>

#ifdef __cplusplus
}
#endif

#endif      /* #ifndef BAP_UTIL_H */

