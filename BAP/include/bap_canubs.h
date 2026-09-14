/******************************************************************
 *
 *     Copyright (c) 2004-2023 Volkswagen AG, D-38436 Wolfsburg
 *
 ******************************************************************
 *
 * Projekt:    BAP
 * BAP Version: 1.12.2
 *
 ******************************************************************
 *
 * Beschreibung
 *
 *  Diese Datei enthaelt die oeffentliche Schnittstelle von BAP,
 *  dem Bedien- und Anzeigeprotokoll, die nur fuer CANUBS geeignet sind.
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
 * 2017-02-28	1.9.0 		FST			[SSWCCB-1545] SSW-Lokatierungs-Pragmas eingefuegt
 * 2016-10-20	1.8.1		FST			[SSWCCB-2410] Softwareschalter DLL_COMPILATION zur Unterscheidung
 * 										der Erzeugung von Steuergeraete-Code und der BAP-Dll eingefuegt
 * 2014-10-06	1.8.0		FST			[SSWCCB-2104] Umstellung u8Length auf uint16_t u16MsgLength für Nachrichtengroesse > 8 Byte
 * 2004-10-15   1.2         SOU         Verschiebung die CANUBS-Funktionen aus bap.h nach bap_canubs.h
 * 2004-10-15   1.2         SOU         Datei erstellt
 ******************************************************************/

#ifndef BAP_CANUBS_H
#define BAP_CANUBS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Systemincludes mit <...> */

/* Bibliotheken von externen Herstellen mit <...> */

/* Eigene Header-Dateien "..." */
#include "bap.h"

/* Makro-Definitionen */

/* Typ-Definitionen */

/* Const Deklarationen */

/* Externe globale Variablen */

/* Deklarationen von Funktionen */

#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>

/**
 *  Diese Funktion muss von der Busanbindung implementiert werden.
 *  Sie wird vom BAP Stack immer dann aufgerufen, wenn Daten ueber
 *  CANUBS zu versenden sind.
 * 
 *  @param aCanInterfaceChannel bezeichnet die Nummer des physikalischen
 *  CAN-Interfaces.
 *
 *  @param aPduId bezeichnet einen Can-Identifier oder ein Can-Message-Handle,
 *  auf dem kommuniziert wird (z.B. CAN Id)
 *
 *  @param apData enthaelt einen Zeiger auf die zu sendenden Daten.
 *
 *  @param au16MsgLength enthaelt die Laenge der zu sendenden Daten.
 *
 *  @returns 
 *  BAP_TRUE falls das Versenden moeglich ist, d.h. die Daten nicht erneut 
 *  an die Busanbindung gesendet werden brauchen.
 *  BAP_FALSE falls die Daten nicht versendet werden konnten. In diesem
 *  Falle wird diese Funktion erneut aufgerufen.
 *
 *  @remarks: Wenn die CAN-Uebertragung ueber den CAN-Treiber
 *  von Vector Software erfolgen soll, dann genuegt es, die mitgelieferte
 *  Datei "bap_bclcan_vector.c" hinzuzulinken.
 */
extern BAP_FAR bool_t BAP_CANUBS_TxData(BapCanInterfaceChannel_t aCanInterfaceChannel
    , BapCanMsgId_t aPduId
    , const ptr_t apData
#ifdef DLL_COMPILATION
    , uint32_t au32MsgLength);
#else
    , uint16_t au16MsgLength);
#endif /* #ifdef DLL_COMPILATION */

/**
 *  Diese Funktion muss von der Busanbindung implementiert werden.
 *  Sie wird vom BAP Stack immer vor dem Versenden von Daten 
 *  mittels BAP_CANUBS_TxData aufgerufen. 
 *
 *  Die Busanbindung muss entweder BAP_TRUE zurueckgeben, wenn
 *  das Versenden von Daten erlaubt ist und BAP_FALSE, wenn
 *  momentan das Versenden von Daten nicht erlaubt ist.
 *  
 *  @param aCanInterfaceChannel bezeichnet die Nummer des physikalischen
 *  CAN-Interfaces.
 *
 *  @param aPduId bezeichnet einen Can-Identifier oder ein Can-Message-Handle,
 *  auf dem kommuniziert wird (z.B. CAN Id)
 *
 *  @returns 
 *  BAP_TRUE, falls der Aufruf von BAP_CANUBS_TxData erlaubt ist,
 *  BAP_FALSE, falls nicht.
 *
 *  @remarks:
 *  Falls diese Funktion BAP_TRUE zurueckliefert werden die Daten zum
 *  Senden aufbereitet und mittels BAP_CANUBS_TxData versendet.
 *
 *  Dieses vorzeitiges Pruefen, ob gesendet werden kann, fuehrt zu einer
 *  Optimierung der Laufzeit, da die Aufbereitung der Daten nur erfolgt,
 *  wenn sie notwendig ist.
 *
 *  Diese Funktion muss bei BusOff BAP_FALSE zurueckliefern.
 */
extern BAP_FAR bool_t BAP_CANUBS_IsReadyForTx(BapCanInterfaceChannel_t aCanInterfaceChannel
    , BapCanMsgId_t aPduId);


/**
 *  Diese Funktion muss von der Busanbindung implementiert werden.
 *  Sie wird vom BAP Stack beim Initialisieren des Stacks aufgerufen.
 *
 *  @param aCanInterfaceChannel bezeichnet die Nummer des physikalischen
 *  CAN-Interfaces.
 *
 *  @param aPduId bezeichnet einen Can-Identifier oder ein Can-Message-Handle,
 *  auf dem kommuniziert wird (z.B. CAN Id)
 *
 *  @remarks:
 *  Unmittelbar nach dem Initialisieren muss BAP_CANUBS_IsReadyForTx
 *  immer BAP_TRUE zuruecklieferen.
 */
extern BAP_FAR void BAP_CANUBS_InitReadyForTx(BapCanInterfaceChannel_t aCanInterfaceChannel
    , BapCanMsgId_t aPduId);



/**
 *  Diese Funktion muss von der Busanbindung aufgerufen werden, wenn Daten
 *  ueber CANUBS empfangen wurden. Diese werden dann durch den BAP Stack
 *  analysiert und uber BAP_Indiciations an die Applikation gemeldet.
 *
 *  @param aCanInterfaceChannel bezeichnet die Nummer des physikalischen
 *  CAN-Interfaces.
 *
 *  @param aCanMsgId bezeichnet einen Can-Identifier oder ein Can-Message-Handle,
 *  auf dem kommuniziert wird (z.B. CAN Id)
 *
 *  @param apData enthaelt einen Zeiger auf die empfangenen Daten.
 *  Falls apData==NULL, wird die Nachricht verworfen.
 *  Falls es sich um eine Fuellbotschaft handelt, wird die Nachricht verworfen.
 *
 *  @param au16MsgLength enthaelt die Laenge der empfangenden Daten.
 *  Es muss 2<=au16MsgLength<=PDU_SIZE sein, sonst wird die Nachricht verworfen.
 */
BAP_IMPL_FAR void BAP_CANUBS_RxData(DBGVAR BapCanInterfaceChannel_t aCanInterfaceChannel
    , DBGVAR BapCanMsgId_t aCanMsgId
    , DBGVAR const uint8_t apData[]
    , DBGVAR uint16_t au16MsgLength);

#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>

#ifdef __cplusplus
}
#endif

#endif      /* #ifndef BAP_CANUBS_H */

