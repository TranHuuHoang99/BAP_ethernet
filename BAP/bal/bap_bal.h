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
 *  Diese Datei enthaelt die Schnittstelle zur BAL Schicht im BAP
 *  Projekt. Diese Schnittstelle darf nicht ausserhalb der BAP
 *  Komponente verwendet werden, da sie in zukuenftigen Versionen
 *  Aenderungen unterliegen darf.
 *
 *  Stattdessen ist die freigegebene Schnittstelle bap.h zu ver-
 *  wenden.
 *
 *  Diese Header-Datei enthaelt nicht die Funktionen BAP_Request* und
 *  BAP_Indication*, da diese in bap.h deklariert sind und in der
 *  Implementierungsdatei definiert sind.
 *  Die BAP_Indication* muessen allerings in der Applikation
 *  implementiert werden, welche den BAP Stack nutzt.
 *
 *  Ausserdem enthaelt sie nicht die CallBack-Funktionen des BPL,
 *  BAP_BPL_Received und BAP_BPL_ErrorIndication (bap_bpl.h), 
 *  welche vom BAL implementiert werden.
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
 *
 ******************************************************************/

#ifndef BAP_BAL_H
#define BAP_BAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Systemincludes mit <...> */

/* Bibliotheken von externen Herstellen mit <...> */

/* Eigene Header-Dateien "..." */
#include "bap.h"

/* Makro-Definitionen */

/** Konstante fuer die Anzahl der Bytes, die 8 Bit ergeben */
#define BAP_BIT8_BYTES 1u

/** Konstante fuer die Anzahl der Bytes, die 16 Bit ergeben */
#define BAP_BIT16_BYTES 2u

/** Konstante fuer die Anzahl der Bytes, die 32 Bit ergeben */
#define BAP_BIT32_BYTES 4u

/** Konstante fuer OpCode 4 (Status) und Lsg-ID 0 (Bit5-Bit2)
        Byte0         Byte1
      OpCode   LSG-ID    FCT-ID
    0  100   0000 | 00  000000 */
#define BAP_OPCODE_STATUS_LSGID_ZERO 0x40

/** Konstante fuer Lsg-ID 0 (Bit1-Bit0) und Fct-ID 0 (Bit5-Bit0) */
#define BAP_LSGID_ZERO_FCTID_ZERO 0


/* Vordefinierte FunctionIds */

/* Typ-Definitionen */

/* Const Deklarationen */

/* Externe globale Variablen */

/* Deklarationen von Funktionen */

/* 
 *  Alle Funktionen von bap_bal.c sind in bap.h deklariert.
 *  Ausnahme bilden die CallBack-Funktionen des BPL, welche
 *  in bap_bpl.h deklariert sind.
 */

#ifdef __cplusplus
}
#endif

#endif      /* #ifndef BAP_BAL_BAL_H */

