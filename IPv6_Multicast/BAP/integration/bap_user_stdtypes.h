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
 *  Diese Datei enthaelt alle zugelassenen Standard-Typdefinitionen
 *  im BAP Projekt. Diese Typen bzw. erweiterte Typen (z.B. structs)
 *  duerfen vom Zulieferer veraendert werden, um eine Anpassung an
 *  Compiler und Prozessor zu ermoeglichen.
 *
 *  Diese Datei darf und soll vom Zulieferer modifiziert werden,
 *  insbesondere wenn die Namen der Standardtypen bereits in anderen
 *  Header-Dateien im Projekt definiert worden sind.
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
 * 2019-08-12   1.11.0      ODD         Change Typedef for DataType RTE_TYPE_uint32_t 
 * 2019-03-21   1.10.99     KUL         [SSWPPB-4] Included string.h only in this file. Library
 *                                      functions can be replaced with supplier specific implementation.
 * 2013-01-30   1.7.0       WWU         Misra-2004 Abweichungen korregiert.
 * 2012-10-15   1.6.5.1     WWU         Korrektur der Misra-98 Abweichungen: stddef nicht mehr inkludieren
 * 2011-06-21   1.6.1.2     NQU         UInt-Typen Ueberprueft nach mehrfach Definition bei Verwendung von AUTOSAR
 * 2007-09-13   1.5         ALI         BAP_ASSERT anders definiert
 * 2007-09-13   1.5         ALI         Einige Macros aus anderen Headern hierher verschoben
 * 2006_08_01   1.5         SHU         Define Integrationsbeispiel
 * 2006-03-28   1.4         MWI         Erstellen der Datei, in der
 *                                      die vom Zulieferer anpassbaren
 *                                      Typen gelagert sind
 *
 ******************************************************************/

#ifndef BAP_USER_STDTYPES_H
#define BAP_USER_STDTYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/* Systemincludes mit <...> */
#ifdef BAP_USES_ASSERT
#include <assert.h>
#endif /* BAP_USES_ASSERT */

/* Include von stdint.h benoetigt fuer plattformspezischen Typ uintptr_t.
 * Kann durch manuelle Typdefinition von uintptr_t ersetzt werden. */
#include <stdint.h>

#include <string.h>

/* Bibliotheken von externen Herstellen mit <...> */

/* Eigene Header-Dateien "..." */

/* Makro-Definitionen */
#ifndef NULL
/** Konstante fuer einen Null-Zeiger */
#define NULL        ((void*)0)
#endif

/** Konstante fuer ein boolean TRUE */
#define BAP_TRUE    ((bool_t)1)

/** Konstante fuer ein boolean FALSE */
#define BAP_FALSE   ((bool_t)0)

#ifndef BAP_INT8_MIN
/** Konstante fuer den kleinsten Wert eines 8-Bit Wertes */
#define BAP_INT8_MIN    (CHAR_MIN)
#endif /* BAP_INT8_MIN */

#ifndef BAP_INT8_MAX
/** Konstante fuer den groessten Wert eines 8-Bit Wertes */
#define BAP_INT8_MAX    (CHAR_MAX)
#endif /* BAP_INT8_MAX */

#ifndef BAP_INT16_MIN
/** Konstante fuer den kleinsten Wert eines 16-Bit Wertes */
#define BAP_INT16_MIN   (INT_MIN)
#endif /* BAP_INT16_MIN */

#ifndef BAP_INT16_MAX
/** Konstante fuer den groessten Wert eines 16-Bit Wertes */
#define BAP_INT16_MAX   (INT_MAX)
#endif /* BAP_INT16_MAX */

#ifndef BAP_INT32_MIN
/** Konstante fuer den kleinsten Wert eines 32-Bit Wertes */
#define BAP_INT32_MIN   (LONG_MIN)
#endif /* BAP_INT32_MIN */

#ifndef BAP_INT32_MAX
/** Konstante fuer den groessten Wert eines 32-Bit Wertes */
#define BAP_INT32_MAX   (LONG_MAX)
#endif /* BAP_INT32_MAX */

#ifndef BAP_MAX_CONFIRMATION_FLAG_TIMEOUT
/**
 *  Diese Konstante dient dazu, falls faelschlicherweise ein Confirmation-Flag
 *  geloescht wird, das Flag nach diesen maximalen Sendeaufrufen wieder zu setzen.
 */
#define BAP_MAX_CONFIRMATION_FLAG_TIMEOUT     ((uint8_t)50)
#endif /* BAP_MAX_CONFIRMATION_FLAG_TIMEOUT */

#ifndef BAP_MAX_TASK_TIME
/**
 *  Diese Konstante dient dazu, die max. Anzahl an Indication-Aufrufen je BAP_Task zu begrenzen.
 *  @see BAP_IND_RX_TIME
 *  @see BAP_BUS_TX_TIME
 *  @see BAP_u16TaskTimeCounter
 */
#define BAP_MAX_TASK_TIME     ((uint16_t)500)
#endif /* BAP_MAX_TASK_TIME */

#ifndef BAP_IND_RX_TIME
 /**
 *  Diese Konstante wird bei jeder Indication auf BAP_u16TaskTimeCounter addiert.
 *  @remarks:
 *  Zusaetzlich wird die Laenge der Daten addiert.
 *  @see BAP_MAX_TASK_TIME
 *  @see BAP_BUS_TX_TIME
 *  @see BAP_u16TaskTimeCounter
 */
#define BAP_IND_RX_TIME     ((uint16_t)80)
#endif /* BAP_IND_RX_TIME */

#ifndef BAP_BUS_TX_TIME
/**
 *  Diese Konstante wird bei jedem Versenden einer Nachricht auf BAP_u16TaskTimeCounter addiert.
 *  @see BAP_IND_RX_TIME
 *  @see BAP_MAX_TASK_TIME
 *  @see BAP_u16TaskTimeCounter
 */
#define BAP_BUS_TX_TIME     ((uint16_t)40)
#endif /* BAP_BUS_TX_TIME */


/**
 *  BAP_ROM_CONST kann im Makefile als -DBAP_ROM_CONST=const angegeben werden, um
 *  Compiler zu unterstuetzen, welche ein const hinter dem Datentyp benoetigen, damit
 *  diese die Variablen ins ROM legen.
 */
#if !defined(BAP_ROM_CONST)
#define BAP_ROM_CONST
#endif

/**
 *  BAP_ROM_DATA_FAR kann beim Compilieren als "#define BAP_ROM_DATA_FAR __far " oder "@far" angegeben werden
 *  dann koennen alle Variablen in den groesseren Adressbereich verschoben werden
 *  @remarks Falls diese Option nicht verwendet wird, sollte dieses Makro nicht von ausserhalb definiert werden.
 */
#if !defined(BAP_ROM_DATA_FAR)
#define BAP_ROM_DATA_FAR
#define BAP_ROM_DATA_FAR_EMPTY
#endif

/**
 *  Hiermit kann die komplette Implementierung des BAP-Stack in den FAR-Bereich gelegt werden.
 *  @remarks
 *  Dies vergroessert den ROM Bedarf fuer den Code.
 *  Beim Cosmic-Compiler fuer HCS 12 kann alternativ auch +modf angegeben werden.
 */
#if !defined(BAP_IMPL_FAR)
#define BAP_IMPL_FAR
#endif

/**
 *  Hiermit kann fuer alle RAM-Werte, welche vom BAP-Stack genutzt werden, ein FAR Zeiger verwendet werden.
 *  Dadurch wird es moeglich, die Daten in die Paged-Area zu legen.
 *
 *  @remarks
 *  Fuer den Tasking Compiler fuer ST 10 muss hier shuge angegeben werden, wenn mehr als 16kBytes
 *  RAM erforderlich sind.
 *  Dies vergroessert den ROM Bedarf fuer den Code
 */
#if !defined(BAP_RAM_DATA_FAR)
#define BAP_RAM_DATA_FAR
#endif

/**
 *  Hiermit koennen alle Callbacks, welche von der Applikation implementiert werden muessen, in den FAR-Bereich gelegt werden.
 *  @remarks
 *  Dies vergroessert den ROM Bedarf fuer den Code geringfuegig.
 *  Beim Cosmic-Compiler fuer HCS 12 kann alternativ auch +modf angegeben werden.
 */
#ifndef BAP_FAR
#ifdef COMPILER_COSMIC
#define BAP_FAR @far
#else
#define BAP_FAR
#endif  /* #ifdef COMPILER_COSMIC */
#endif /* #ifndef BAP_FAR */

/**
 *  Falls das Macro BAP_USES_ASSERT definiert ist, wird BAP_ASSERT(cond) auf das C assert(cond) umgeleitet (sinnvoll fuer den
 *  DEBUG Modus). Ansonsten wird nichts gemacht.
 */
#ifndef BAP_ASSERT
#ifndef BAP_USES_ASSERT
#define BAP_ASSERT(cond)    ((void)0)
#else
#define BAP_ASSERT(cond) assert(cond)
#endif
#endif

//To handle the testing of static fonctions from CUnitTest
#ifndef BAP_STATIC_UNSET
#define BAP_STATIC static
#else
#define BAP_STATIC
#endif

#if !defined(DBGVAR)
/**
 *  Wird definiert, um bei der automatischen Definition von DBGVAR zusaetzlichen
 *  Debug-Code zu entfernen.
 */
#define BAP_AUTO_DBGVAR
/**
 *  DBGVAR kann im Makefile als -DDBGVAR=volatile angegeben werden, um Anzeigeproblemen
 *  von Variablen beim Debuggen wegen Registeroptimierung zu umgehen.
 */
#define DBGVAR
/**
 *  Je nachdem, ob DBGVAR definiert ist, ist ein cast nach (DBGVAR ptr_t) erforderlich.
 *  Wenn der Typ bereits ein ptr_t ist, darf nach MISRA Rule 44 kein cast erfolgen.
 */
#define CAST_TO_PTR(arg) (arg)
#else
#define CAST_TO_PTR(arg) (DBGVAR ptr_t)(arg)
#endif

/**
 *  Ruft memset auf mit den fuer die Misra C Regeln relevanten Casts
 *  @param dest     - Zieladresse
 *  @param c        - Zeichen zum Fuellen
 *  @param length    - Anzahl der zu setzenden Bytes
 */
#define MEMSET(dest, c, length)    ((void) memset((void*)(dest), (int)(c), (size_t)(length)))

/**
 *  Ruft memcpy auf mit den fuer die Misra C Regeln relevanten Casts
 *  @param dest     - Zieladresse
 *  @param source   - Quelladresse
 *  @param length   - Anzahl der zu kopierenden Bytes
 */
#define MEMCPY(dest, source, length)    ((void) memcpy((void*)(dest), (const void*)(source), (size_t)(length)))

/**
 *  Diese Funktion ersetzt die Bibliotheksfunktion memcpy, um BAP_ROM_DATA_FAR Konstanten ins RAM zu kopieren.
 *  @param dest     - Zieladresse
 *  @param source   - Quelladresse
 *  @param length   - Anzahl der zu kopierenden Bytes
 */
#ifdef BAP_ROM_DATA_FAR_EMPTY
#define FAR_MEMCPY(dest, source, length)    ((void) memcpy((void*)(dest), (const void*)(source), (size_t)(length)))
#else
#define FAR_MEMCPY(dest, source, length)    BAP_RomToRamMemCpy(dest, source, (size_t)(length))
#endif /* #ifdef BAP_ROM_DATA_FAR_EMPTY */

/**
 *  Ruft memcmp auf mit den fuer die Misra C Regeln relevanten Casts
 *  @param dest     - Zieladresse
 *  @param source   - Quelladresse
 *  @param length   - Anzahl der zu vergleichenden Bytes
 */
#define MEMCMP(dest, source, length)    (memcmp((void*)(dest), (const void*)(source), (size_t)(length)))


/* Typ-Definitionen */

/**
 *  Dieser Typ enthaelt einen Zeiger auf ein Bytearray, welches
 *  untypisiert ist.
 */
typedef const unsigned char* ptr_t;

/**
 *  Dieser Typ enthaelt einen Zeiger auf ein Bytearray, welches
 *  untypisiert ist. Dieses ByteArray kann auch im Interrupt veraendert werden.
 */
typedef const volatile unsigned char* volatile_ptr_t;


/**
 *  Dieser Typ wird fuer Bitfelder mit maximal 8 Bits verwendet.
 *  Nur int ist portabel und nach ANSI Standard erlaubt, verbraucht
 *  aber eventuell mehr Speicher als notwendig.
 *
 *  @remark: es muss immer ein unsigned Typ verwendet werden.
 *  Falls der Compiler es erlaubt und Einsparungen an RAM/ROM moeglich
 *  sind, kann dies auch auf unsigned char umdefiniert werden.
 */
typedef unsigned int bitfield_t;

/**
 *  Dieser Typ speichert einen ganzzahligen Wert in 8 Bit ohne Vorzeichen.
 */
#if defined(BAP_USES_ASR_WRAPPER)
	#if (!defined(Rte_TypeDef_uint8_t)) && (!defined(RTE_TYPE_uint8_t))
	#define Rte_TypeDef_uint8_t
	#define RTE_TYPE_uint8_t
	#define uint8_t bap_uint8_t
	typedef unsigned char uint8_t;
	#endif /* #if !defined(Rte_TypeDef_uint8_t) && !defined(RTE_TYPE_uint8_t) */
#else
	#define uint8_t bap_uint8_t
	typedef unsigned char uint8_t;
#endif /* #if defined(BAP_USES_ASR_WRAPPER) */

/**
 *  Dieser Typ speichert einen ganzzahligen Wert in 16 Bit ohne Vorzeichen.
 */
#if defined(BAP_USES_ASR_WRAPPER)
	#if (!defined(Rte_TypeDef_uint16_t)) && (!defined(RTE_TYPE_uint16_t))
	#define Rte_TypeDef_uint16_t
	#define RTE_TYPE_uint16_t
	#define uint16_t bap_uint16_t
	typedef unsigned short uint16_t;
	#endif /* #if !defined(Rte_TypeDef_uint16_t) && !defined(RTE_TYPE_uint16_t) */
#else
	#define uint16_t bap_uint16_t
	typedef unsigned short uint16_t;
#endif /* #if defined(BAP_USES_ASR_WRAPPER) */

/**
 *  Dieser Typ speichert einen ganzzahligen Wert in 32 Bit ohne Vorzeichen.
 */
#if defined(BAP_USES_ASR_WRAPPER)
	#if (!defined(Rte_TypeDef_uint32_t)) && (!defined(RTE_TYPE_uint32_t))
	#define Rte_TypeDef_uint32_t
	#define RTE_TYPE_uint32_t
	#define uint32_t bap_uint32_t
	typedef unsigned int uint32_t;
	#endif /* #if !defined(Rte_TypeDef_uint32_t) && !defined(RTE_TYPE_uint32_t) */
#else
	#define uint32_t bap_uint32_t
	typedef unsigned int uint32_t;
#endif /* #if defined(BAP_USES_ASR_WRAPPER) */

/**
 *  Dieser Typ enthaelt einen Wert vom Typ boolean.
 */
typedef uint8_t bool_t;



#ifdef __cplusplus
}
#endif /*__cplusplus */

#endif      /* #ifndef BAP_USER_STDTYPES_H */

