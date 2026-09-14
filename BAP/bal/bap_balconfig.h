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
 *  Diese Datei enthaelt die Datentypen und Schnittstellen auf
 *  die konfigurierten Daten des Bedien- und Anzeigeprotokolls
 *  welche den BAL (Protokollschicht 6) betreffen.
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
 * 2007-08-16   1.5         ALI         struct BapBalRamRow_t mit union wird zu union BapBalRamRow_t mit
 *                                      mehreren structs als Inhalt - Alignment-Problem gewesen
 * 2006-04-12   1.4         ALA         Unterstuetzung fuer BAP_ROM_DATA_FAR.
 * 2004-03-30   1.3         CRI         FSG besitzt ebenfalls einen Fct.list Buffer
 * 2004-11-17   1.2         JOK         Gesonderter Datenpuffer fuer aktuelle FctList im ASG
 * 2004-09-08   1.2         JOK         Erweiterung von BapBalRomRow_t um eRx/TxDataType und u16Rx/TxSize
 *                                      fuer asymetrische Konfiguration
 * 2004-06-07   1.1         JOK         Einfuehrung der BapDt_FixedByteSequence fuer nicht-segmentierte
 *                                      ByteSequenzen
 ******************************************************************/

#ifndef BAP_BALCONFIG_H
#define BAP_BALCONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Systemincludes mit <...> */

/* Bibliotheken von externen Herstellen mit <...> */

/* Eigene Header-Dateien "..." */
#include "bap_config.h"
#include "bap_privatetypes.h"

/* Makro-Definitionen */

/* Typ-Definitionen */

#ifdef BAP_ASG
/**
 * Enthaelt Status und Wert je Funktion. xValue existiert nur
 * wenn in BapBalRomRow_t das Flag bCacheAvailable wahr ist
 * und eFunctionClass ein Property ist.
 */
typedef struct BapBalRamRow_t
{
	BapBalDataStatus_et eDataStatus;

	uint8_t  u8Value;

#ifdef BAP_USES_DATATYPE_16
    /**
     * Gueltig, falls Datentyp = BapDt_Int16.
     */
	uint16_t u16Value;
#endif

#ifdef BAP_USES_DATATYPE_32
    /**
     * Gueltig, falls Datentyp = BapDt_Int32.
     */
	uint32_t u32Value;
#endif

/**
     * Gueltig, falls Datentyp = BapDt_ByteSequence
     * oder Datentyp = BapDt_FixedByteSequence.
     * u16Length enthaelt die Anzahl an gueltigen Bytes
     * in aru8Buffer.
     */
   BapBufferWithLength_ot oBufferWithLength;
} BapBalRamRow_ot;
/* Zeiger auf BapBalRamRow_ot ist in bap_config.h definiert */
#endif /* #ifdef BAP_ASG */


/* Const Deklarationen */

/* Deklarationen von Funktionen */

#ifdef __cplusplus
}
#endif

#endif      /* #ifndef BAP_BALCONFIG_H */

