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
 *  Diese Datei enthaelt alle zugelassenen Typdefinitionen im BAP
 *  Projekt, die in mehr als einer Schicht verwendet werden aber
 *  ausserhalb des BAP Projektes nicht sichtbar sein sollen.
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
 * 2007-08-27   1.5         RVE         Konstanten fuer OpCodes StatusAck und Ack definiert.
 * 2006-04-12   1.4         ALA         Unterstuetzung fuer HB-Trigger
 * 2006-04-12   1.4         ALA         Unterstuetzung fuer BAP_ROM_DATA_FAR
 * 2004-09-03   1.2         JOK         Konstante fuer Funktionsklasse Methode definiert
 * 2004-09-03   1.2         JOK         Konstanten fuer OpCodes von Methode definiert
 *
 ******************************************************************/

#ifndef BAP_PRIVATETYPES_H
#define BAP_PRIVATETYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/* Systemincludes mit <...> */

/* Bibliotheken von externen Herstellen mit <...> */

/* Eigene Header-Dateien "..." */
#include "bap_types.h"

/* Makro-Definitionen */

/* Typ-Definitionen */

/**
 *  Beschreibt die Funktionsklasse einer BAP-Funktion (FctId, eines Datums).
 *  Die Enum-Werte sind fest vergeben, um einen einfachen Zugriff auf die
 *  Abbildungsmatrix fuer die Abbildung f(Req/Inc, FctKlasse) => OpCode zu erreichen.
 */
typedef enum BapFunctionClass_t
{
    /**
     *  Die Funktionsklasse Property beschreibt ein einfaches Datenelement, moeglicherweise mit Cache
     */
    BapFctCls_Property = 0,

    /**
     *  Die Funktionsklasse Cache bietet die Moeglichkeit, alle Elemente des
     *  Caches auf einen Schlag zu synchronisieren.
     */
    BapFctCls_Cache = 1

#ifdef BAP_USES_ARRAYS
    ,
    /**
     *  Die Funktionsklasse Array kuemmert sich um die Uebertragung mehrerer Elemente
     */
    BapFctCls_Array = 2
#endif /* #ifdef BAP_USES_ARRAYS */

#ifdef BAP_USES_METHODS
    ,
    /**
     *  Die Funktionsklasse Method erlaubt es, Aktionen mit einer laengeren Zeitdauer aufzurufen
     *  und ueber ein Processing zu ueberwachen.
     */ 
    BapFctCls_Method = 3
#endif  /* BAP_USES_METHODS */
} BapFunctionClass_et;

/** Konstanten fuer die Anzahl von Funktionsklassen */
#ifdef BAP_USES_METHODS
#define BAP_NUMBER_OF_FUNCTIONCLASSES 4
#else
#ifdef BAP_USES_ARRAYS
#define BAP_NUMBER_OF_FUNCTIONCLASSES 3
#else
#define BAP_NUMBER_OF_FUNCTIONCLASSES 2
#endif
#endif

/**
 *  Enthaelt alle Opcodes, die ueber das Uebertragungsmedium uebertragen werden koennen.
 *  Die bei den Elementen in Anfuehrungszeichen angegebenen Opcode-Namen stammen aus dem
 *  Lastenheft von den Volkswagen und Audi AG
 */
typedef enum BapOpCodes_t
{
    /**
     * Opcode "Reset/Set" gueltig fuer BapFctCls_Property
     *
     * @remarks
     * Zeigt entweder ein Reset vom FSG an, oder dient zum Setzen 
     * eines Wertes im FSG vom ASG aus.
     */
    BapOp_PropReset_Set = 0,

    /**
     * Opcode "Get" gueltig fuer BapFctCls_Property
     *
     * @remarks
     * Fordert einen "Status" von der Gegenstelle (FSG) an.
     */
    BapOp_PropGet = 1,

    /**
     * Opcode "SetGet" gueltig fuer BapFctCls_Property
     *
     * @remarks
     * Setzt einen Wert in der Gegenstelle (FSG) und erwartet
     * eine Bestaetigung des Vorgangs mit einem "Status".
     */
    BapOp_PropSetGet = 2,

    /**
     * Opcode "HeartbeatStatus" gueltig fuer BapFctCls_Property
     *
     * @remarks
     * Wird vom FSG zum Versenden von Heartbeat Nachrichten verwendet
     */
    BapOp_PropHeartbeatStatus = 3,

    /**
     * Opcode "Status" gueltig fuer BapFctCls_Property
     *
     * @remarks
     * Informiert ASG ueber Zustandsaenderungen
     */
    BapOp_PropStatus = 4,

    /**
     * Opcode "StatusAck" gueltig fuer BapFctCls_Property
     *
     * @remarks
     * Wird vom FSG zum Anfordern einer "Ack" Antwort auf die "Status" Meldung verwendet
     */
    BapOp_PropStatusAck = 5,

    /**
     * Opcode "Ack" gueltig fuer BapFctCls_Property
     *
     * @remarks
     * Wird vom ASG zum beantworten einer "StatusAck" Anfrage verwendet
     */
    BapOp_PropAck = 6,

    /**
     * Opcode "Error" gueltig fuer BapFctCls_Property
     *
     * @remarks
     * Signalisiert einen Fehler ueber den Bus. Fehlercodes gemaess LAH.
     */
    BapOp_PropError = 7,


    /**
     * Opcode "SetArray" gueltig fuer BapFctCls_Array
     */
    BapOp_ArrSet = 0,

    /**
     * Opcode "GetArray" gueltig fuer BapFctCls_Array
     */
    BapOp_ArrGet = 1,

    /**
     * Opcode "SetGetArray" gueltig fuer BapFctCls_Array
     */
    BapOp_ArrSetGet = 2,

    /**
     * Opcode "ChangedArray" gueltig fuer BapFctCls_Array
     */
    BapOp_ArrChanged = 3,

    /**
     * Opcode "StatusArray" gueltig fuer BapFctCls_Array
     */
    BapOp_ArrStatus = 4,

    /**
     * Opcode "Error" gueltig fuer BapFctCls_Array
     */
    BapOp_ArrError = 7,


    /**
     * Opcode "SetAll" gueltig fuer BapFctCls_Cache
     *
     * @remarks
     * Wird in der aktuellen BAP-Version nicht unterstuetzt
     */
    BapOp_CacheSetAll = 0,

    /**
     * Opcode "GetAll" gueltig fuer BapFctCls_Cache
     *
     * @remarks
     * Fordert alle Werte vom FSG an. Das FSG uebertraegt die 
     * Werte mittels einzelbotschaften an das ASG.
     */
    BapOp_CacheGetAll = 1,

    /**
     * Opcode "SetGetAll" gueltig fuer BapFctCls_Cache
     *
     * @remarks
     * Wird in der aktuellen BAP-Version nicht unterstuetzt
     */
    BapOp_CacheSetGetAll = 2,

    /**
     * Opcode "StatusAll" gueltig fuer BapFctCls_Cache
     *
     * @remarks
     * Gedacht fuer komprimierte Antwort aller Stati aus dem Cache
     * auf ein "GetAll".
     * Wird in der aktuellen BAP-Version nicht unterstuetzt
     */
    BapOp_CacheStatusAll = 4,

    /**
     * Opcode "Error" gueltig fuer BapFctCls_Cache
     *
     * @remarks
     * Wird in der aktuellen BAP-Version nicht unterstuetzt
     */
    BapOp_CacheError = 7,

#ifdef BAP_USES_METHODS
    /**
     * Opcode "Start" gueltig fuer BapFctCls_Method
     *
     * @remarks
     * Ruft eine Methode (Funktion) im FSG auf, ohne ein Rueckgabeergebnis
     * zu erwarten.
     */
    BapOp_MethStart = 0,

    /**
     * Opcode "Abort" gueltig fuer BapFctCls_Method
     *
     * @remarks
     * Bricht eine laufende Berechnung im FSG ab.
     */
    BapOp_MethAbort = 1,

    /**
     * Opcode "StartResult" gueltig fuer BapFctCls_Method
     *
     * @remarks
     * Ruft eine Methode (Funktion) im FSG auf (startet Berechnung)
     * und erwartet ein Rueckgabeergebnis.
     */
    BapOp_MethStartResult = 2,

    /**
     * Opcode "Processing" gueltig fuer BapFctCls_Method
     *
     * @remarks
     * Anzeige vom FSG, dass eine Berechnung im FSG laueft
     */
    BapOp_MethProcessing = 3,

    /**
     * Opcode "Result" gueltig fuer BapFctCls_Method
     *
     * @remarks
     * FSG liefert das Ergebnis der Berechnung.
     */
    BapOp_MethResult = 4,

    /**
     * Opcode "Error" gueltig fuer BapFctCls_Method
     *
     * @remarks
     * Signalisiert einen Fehler ueber den Bus. Fehlercodes gemaess LAH.
     */
    BapOp_MethError = 7,
#endif /* #ifdef BAP_USES_METHODS */

    /**
     * Interner Opcode zur Meldung des Empfangs einer Botschaft
     * vom BCL and den BPL. Wird zum Retriggern des Heartbeat-Timers
     * im ASG genutzt.
     */
    BapOp_MessageReceived = 0x1c,

#ifdef BAP_USES_SEGMENTATION
    /**
     * Interner Opcode zur Meldung des erfolgreichen Versendens 
     * eines Datenelements (ggfs. nur eines Segments) vom BCL an den BPL
     */
    BapOp_MessageSent = 0x1d,

    /**
     * Interner Opcode zur Meldung des Empfangs einer Startbotschaft 
     * vom BCL an den BPL
     */
    BapOp_StartMessage = 0x1e,
#endif /* #ifdef BAP_USES_SEGMENTATION */

    /**
     * Interner Opcode zur Kennzeichnung eines ungueltigen OpCodes,
     * wird bei der Gueltigkeitspruefung der Opcodes verwendet.     
     */
    BapOp_Invalid = 0x1f
} BapOpCodes_et;

/** Konstante fuer die Anzahl von OpCodes relevant fuer Indications */
#define BAP_NUMBER_OF_OPCODES_FOR_INDICATIONS 7

/** Konstante fuer die Anzahl von OpCodes relevant fuer Acknowledges */
#define BAP_NUMBER_OF_OPCODES_FOR_ACKNOWLEDGES 8

/* Const Deklarationen */

/* Externe globale Variablen */

/* Deklarationen von Funktionen */


#ifdef __cplusplus
}
#endif

#endif      /* #ifndef BAP_PRIVATETYPES_H */

