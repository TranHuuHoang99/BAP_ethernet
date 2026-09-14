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
 *  Diese Datei enthaelt die Schnittstelle zur BCL Schicht im BAP
 *  Projekt. Diese Schnittstelle darf nicht ausserhalb der BAP
 *  Komponente verwendet werden, da sie in zukuenftigen Versionen
 *  Aenderungen unterliegen darf.
 *
 *  Stattdessen ist die freigegebene Schnittstelle BAP.h zu ver-
 *  wenden.
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
 * 2017-07-24   1.10.0      FHA         [SSWCCB-2391] Schnelle Suche TX-PDU
 * 2017-02-28   1.9.0       FST         [SSWCCB-1545] SSW-Lokatierungs-Pragmas eingefuegt
 * 2014-11-28   1.8.0       WWU/FST     [SSWCCB-2105] Formataenderung der Variablen 16Bit->32Bit
 * 2014-03-27   1.7.1       WWU         MISRA-2004 Fix. Macro Definition korrigiert.
 *                                      Funktion-Like Makros fuer BAP_BCL_Start wurde entfernt.
 * 2012-10-15   1.6.5.1     WWU         Korrektur der Misra-98 Abweichungen: stddef und String nicht mehr inkludieren
 * 2006-04-12   1.4         ALA         Unterstuetzung fuer BAP_ROM_DATA_FAR.
 * 2005-07-07   1.3.1       ALA         #include "bap_config.h" hinzugefuegt (wg. BapInternalParameters_t)
 * 2005-04-29   1.3         ALA         Parameteruebergabe optimiert, Taskzeitbegrenzung hinzugefuegt.
 *                                      Codegroesse fuer SmallFSG optimiert, Anpassungen an div. Compiler
 * 2005-03-14   1.2.1       CRI         BCL_Start hinzugefuegt
 * 2004-11-04   1.2         ALA         BAP_BCL_SendError Funktion hinzugefuegt.
 * 2004-06-07   1.1         JOK         Compilerschalter fuer SG-Typen zur Optimierung
 *                                      des ROM-Bedarfs eingefuegt
 * 2004-06-07   1.1         JOK         Include bap_privatetypes.h aufgenommen
 * 2004-06-07   1.1         JOK         BAP_BCL_Start() als Konstante definiert
 * 2004-06-07   1.1         JOK         BAP_BCL_Shutdown() als Funktionspointer auf 
 *                                      BAP_BCL_Init() definiert
 * 2004-06-07   1.1         JOK         Makros fuer memcpy() und memset() mit entsprechenden
 *                                      Casts entsprechend MISRA-C Pruefung definiert
 ******************************************************************/

#ifndef BAP_BCL_H
#define BAP_BCL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Systemincludes mit <...> */

/* Bibliotheken von externen Herstellen mit <...> */

/* Eigene Header-Dateien "..." */
#include "bap_types.h"
#include "bap_privatetypes.h"
#include "bap_config.h"

/* Makro-Definitionen */

/**
 * Konstante fuer die Anzahl an Bytes fuer die Laengeninformation des GetAll Buffer
 * mit variabler Laenge in StatusAll Nachricht */
#define BAP_NUM_VAR_LENGTH_BYTES 2u

/* Typ-Definitionen */

/* Const Deklarationen */

/* Externe globale Variablen */

/**
 *  Berechnet aus der Anzahl der Bytes, welche innerhalb eines BAP_Tasks
 *  an die Applikation gemeldet werden sowie der Anzahl der Meldungen,
 *  die Auftritt, einen Zeitwert.
 *
 *  Dieser Zeitwert wird fuer die Entscheidung genutzt, ob innerhalb dieses
 *  BAP_Task-Aufrufs noch weitere Indications an die Applikation gemeldet
 *  werden oder ob bis zum naechsten BAP_Task-Aufruf gewartet wird.
 *
 *  @see BAP_MAX_TASK_TIME
 *  @see BAP_IND_RX_TIME
 *  @see BAP_BUS_TX_TIME
 */
#ifdef BAP_TASKTIME_LIMIT
extern uint32_t BAP_u32TaskTimeCounter;
#endif /* #ifdef BAP_TASKTIME_LIMIT */

/* Deklarationen von Funktionen */

#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>

/**
 *  Wird vom BCL als Callback aufgerufen, um interne (z.B. bei Timeouts bei
 *  Intertelegrammzeit von segmentierten Nachrichten) oder auch externe.
 *  Error-Nachrichten (Error_IND) zu melden.
 *
 *  @param aLsgId bezeichnet das logische Steuergeraet.
 *
 *  @param aFctId bezeichnet die Funktion des angegebenen logischen Steuergeraetes.
 *
 *  @param aeErrorCode enthaelt den Fehlercode, der an BAL signalisiert wird.
 */
extern BAP_IMPL_FAR void 
BAP_BCL_ErrorIndication(DBGVAR lsgId_t aLsgId
    , DBGVAR fctId_t aFctId
    , DBGVAR BapError_et aeErrorCode);


/**
 *  Wird vom BCL als Callback aufgerufen, wenn Daten empfangen wurden.
 *
 *  Die uebergeordnete Schicht muss diese Funktion implementieren.
 *
 *  Die Verbindung des CallBacks erfolgt automatisch ueber
 *  den Namen der Funktion und dem Linker.
 *
 *  @param apoPars - Parameterliste, verwendet werden alle Elemente:<br>
 *                 -\>lsgId bezeichnet das logische Steuergeraet.<br>
 *                 -\>poLsgRomRow zeigt auf das logische Steuergeraet<br>
 *                 -\>fctId bezeichnet die Funktion des angegebenen logischen Steuergeraetes.<br>
 *                 -\>poFctRomRow zeigt auf die Funktion<br>
 *                 -\>eOpCode bezeichnet den OpCode, welcher die Operation der Daten beschreibt.<br>
 *                 -\>pData muss untypisiert auf eine Bytefolge zeigen, deren Laenge in au16Length 
 *  uebergeben wird, und die zu sendenden Daten enthaelt<br>
 *                 -\>u16Length muss die Laenge der zu sendenden Daten enthalten
 *
 */
extern BAP_IMPL_FAR void 
BAP_BCL_DataReceived(BapInternalParameters_cpot apoPars);


#if defined (BAP_ASG) || defined(WIRD_NIE_GEBRAUCHT) 
/* Diese Funktion wird im FSG nie gebraucht und kann nicht ueber die BAP-API
 * von der Anwendung aufgerufen werden. Daher wird diese Funktion 
 * aus dem Code herausgenommen und um ROM zu sparen.
 */
/**
 *  Loescht die Sendeanfrage des BPL.
 *  Der BCL Tx Puffer bleibt erhalten.
 *
 *  @param apoPars - Parameterliste, verwendet werden:<br>
 *                 -\>lsgId<br>
 *                 -\>fctId<br>
 *                 -\>poLsgRomRow<br>
 *                 -\>poFctRomRow<br>
 *                 OpCode, Daten und Laenge werden nicht genutzt.
 */
BAP_IMPL_FAR void 
BAP_BCL_AbortSend(BapInternalParameters_cpot apoPars);
#endif /* #if defined (BAP_ASG) || defined(WIRD_NIE_GEBRAUCHT)  */


#ifdef BAP_FSG
/**
 *  Legt die zu sendenden Daten in die Sendepuffer.
 *  Ein Senden auf dem Uebertragungsmedium wird nicht getriggert.
 *
 *  @param apoPars - Parameterliste, verwendet werden alle Elemente:<br>
 *                 -\>lsgId bezeichnet das logische Steuergeraet.<br>
 *                 -\>poLsgRomRow zeigt auf das logische Steuergeraet<br>
 *                 -\>fctId bezeichnet die Funktion des angegebenen logischen Steuergeraetes.<br>
 *                 -\>poFctRomRow zeigt auf die Funktion<br>
 *                 -\>eOpCode bezeichnet den OpCode, welcher die Operation der Daten beschreibt.<br>
 *                 -\>pData muss untypisiert auf eine Bytefolge zeigen, deren Laenge in au16Length
 *  uebergeben wird, und die zu sendenden Daten enthaelt<br>
 *                 -\>u16Length muss die Laenge der zu sendenden Daten enthalten
 */
BAP_IMPL_FAR void
BAP_BCL_BufferSet(BapInternalParameters_cpot apoPars);
#endif /* #ifdef BAP_FSG */


/**
 * Legt die zu sendenden Daten in die Ausgangspuffer und triggert das Versenden der Daten.
 *
 * @param apoPars enthaelt die zu sendenden Daten<br>
 *                -\>lsgId - muss die LSG-ID enthalten<br>
 *                -\>fctId - muss die FCT-ID enthalten<br>
 *                -\>poLsgRomRow - muss auf das aktuelle LSG zeigen<br>
 *                -\>poFctRomRow - muss auf die aktuelle FCT zeigen<br>
 *                -\>pData - muss auf die aktuellen Daten zeigen (NULL nur erlaubt, wenn u16Length=0)<br>
 *                -\>u16Length - muss die Laenge der aktuellen Daten enthalten<br>
 *                -\>eOpCode - muss den aktuellen OpCode enthalten
 */
BAP_IMPL_FAR void
BAP_BCL_Send(BapInternalParameters_cpot apoPars);



#ifdef BAP_FSG
/**
 *  Sendet den angegebenen Fehlerwert mit dem OpCode Error.
 *
 *  @param apoPars - Parameterliste, verwendet werden folgende Elemente:<br>
 *                -\>lsgId bezeichnet das logische Steuergeraet.<br>
 *                -\>poLsgRomRow zeigt auf das logische Steuergeraet<br>
 *                -\>fctId bezeichnet die Funktion des angegebenen logischen Steuergeraetes.<br>
 *                -\>poFctRomRow zeigt auf die Funktion<br>
 *                -\>eOpCode nicht genutzt<br>
 *                -\>pData das erste Byte wird als Fehlerwert gewertet, welcher zu versenden ist<br>
 *                -\>u16Length nicht genutzt
 */
BAP_IMPL_FAR void
BAP_BCL_SendError(BapInternalParameters_cpot apoPars);
#endif /* #ifdef BAP_FSG */


#ifdef BAP_ASG
/**
 *  Versendet die Daten im Sendepuffer nocheinmal exakt wie zuvor. Diese Funktion 
 *  wird im ASG bei einem Retry verwendet.
 *
 *  @param apoPars - Parameterliste, verwendet werden folgende Elemente:<br>
 *                -\>lsgId bezeichnet das logische Steuergeraet.<br>
 *                -\>poLsgRomRow zeigt auf das logische Steuergeraet<br>
 *                -\>fctId bezeichnet die Funktion des angegebenen logischen Steuergeraetes.<br>
 *                -\>poFctRomRow zeigt auf die Funktion
 *  
 *  @remarks: OpCode, Daten und Laenge werden von dieser Funktion nicht verarbeitet.
 */
BAP_IMPL_FAR void 
BAP_BCL_Resend(BapInternalParameters_cpot apoPars);
#endif /* #ifdef BAP_ASG */


#ifdef BAP_FSG
/**
 *  Versendet die Nutzdaten erneut, jedoch mit geaendertem OpCode.
 *  Diese Funktion wird u.a. beim Versenden der Heartbeat-Nachricht,
 *  bei der Beantwortung von Get-Anfragen und der Beantwortung von GetAll-Anfragen
 *  verwendet.
 *
 *  @param apoPars - Parameterliste, verwendet werden folgende Elemente:<br>
 *                -\>lsgId bezeichnet das logische Steuergeraet.<br>
 *                -\>poLsgRomRow zeigt auf das logische Steuergeraet<br>
 *                -\>fctId bezeichnet die Funktion des angegebenen logischen Steuergeraetes.<br>
 *                -\>poFctRomRow zeigt auf die Funktion<br>
 *                -\>eOpCode enthaelt den neuen OpCode. Dieser darf nicht BapOp_Error sein.
 *
 *  @remarks
 *  Daten und Laenge werden von dieser Funktion nicht verarbeitet.
 *  Es werden die Daten des letzten Aufrufs von BAP_BCL_Send verwendet.
 */
BAP_IMPL_FAR void 
BAP_BCL_ResendWithOpCode(BapInternalParameters_cpot apoPars);
#endif /* #ifdef BAP_FSG */


/**
 *  Diese Funktion wird von BAP_BPL_Init aufgerufen.
 *  Es werden die RAM Bereiche die zur BCL Schicht
 *  gehoeren initialisiert, sowie die Tx Confirmation
 *  Flags des Vector CAN Treibers die fuer den BAP
 *  Betrieb benoetigt werden.
 *  
 *  @param apoLsgRomRow bezeichnet das logische Steuergeraet.
 */
BAP_IMPL_FAR void
BAP_BCL_Init(BapLsgRomRow_pot apoLsgRomRow);


/**
 *  Diese Funktion wird von BAP_BPL_Start aufgerufen.
 *  Der LSG Status der BCL Schicht wird in den Zustand
 *  'Running' ueberfuehrt.
 *
 *  @param apoLsgRomRow bezeichnet das logische Steuergeraet.
 */
BAP_IMPL_FAR BapError_et
BAP_BCL_Start(BapLsgRomRow_pot apoLsgRomRow);


/**
 *  Diese Funktion wird von BAP_BPL_Shutdown aufgerufen.
 *
 *  @param apoLsgRomRow bezeichnet das logische Steuergeraet.
 *
 *  @returns Es werden keine Pruefungen ueber die des BAL hinaus gemacht. Daher
 *      wird immer BapErr_OK zurueckgegeben.
 */
BAP_IMPL_FAR void
BAP_BCL_Shutdown(BapLsgRomRow_pot apoLsgRomRow);

#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#   define BAP_START_SEC_CODE_CYCLIC
#   include <BAP_MemMap.h>

/**
 *  Diese Funktion wird vom BAP_Task aufgerufen.
 * 
 *  Es werden alle anstehenden Sendeanforderungen geprueft und
 *  wenn moeglich versendet. Die Pruefung kann fehlschlagen, 
 *  falls die Inhibit-Zeit noch nicht abgelaufen ist oder
 *  der CAN-Bus gerade belegt ist.
 */
BAP_IMPL_FAR void 
BAP_BCL_TaskSend(void);


/**
 *  Diese Funktion wird vom BAP_Task aufgerufen.
 *
 *  Hier wird der Ringpuffer ausgelesen
 *  in den der CAN Interrupt seine Daten abgelegt hat.
 *  Damit wird eine Entkoppelung des Empfangs und der
 *  Weiterverarbeitung erreicht, was die Interruptsperrzeit 
 *  reduziert.
 *
 */
BAP_IMPL_FAR void 
BAP_BCL_ReadRingbuffer(void);


#ifdef BAP_USES_SEGMENTATION
/**
 *  Diese Funktion wird vom BAP_Task aufgerufen.
 *
 *  Es werden alle komplett empfangenen Botschaften (alle Segmente)
 *  ueber die Funktion BAP_BCL_DataReceived nach oben gemeldet.
 */
BAP_IMPL_FAR void 
BAP_BCL_TaskRxNotify(void);
#else
/**
 *  Bei unsegmentierten Nachrichten erfolgt die Meldung ohne die Rx-Puffer direkt nach oben.
 *  Daher braucht dieser Task nicht aufgerufen zu werden.
 */
#define BAP_BCL_TaskRxNotify() ((void)0)
#endif /* #ifdef BAP_USES_SEGMENTATION */

#   define BAP_STOP_SEC_CODE_CYCLIC
#   include <BAP_MemMap.h>
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>

#ifdef BAP_USES_ACKNOWLEDGE
/**
 *  Diese Funktion wird vom BCL aufgerufen, wenn eine Nachricht erfolgreich verschickt wurde.
 *  Sie wird nur nach einem BAP_BCL_Send aufgerufen, nicht jedoch nach einem BAP_BCL_Resend oder
 *  BAP_BCL_ResendWithOpcode.
 *
 *  @param apoFctRomRow zeigt auf die Funktion 
 *  @param aeOpCode enthaelt den gesendeten OpCode
 */
BAP_IMPL_FAR void
BAP_BCL_Acknowledge(BapFctRomRow_pot apoFctRomRow, BapOpCodes_et aeOpCode);
#endif  /* #ifdef BAP_USES_ACKNOWLEDGE */

#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>

#ifdef __cplusplus
}
#endif

#endif      /* #ifndef BAP_BCL_H */

