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
 *  Diese Datei enthaelt die Anpassung der BCL CANUBS Implementierung
 *  an den CAN-Treiber von Vector Software.
 *
 *  Laut Auskunft von Herrn Maurice Muecke (Volkswagen) vom 2004-10-11
 *  sind die Funktionen CanGetRxDataPtr und CanGetTxDataPtr nicht
 *  teil der offiziellen Vector CAN Treiber Schnittstelle.
 *
 *  Es kann nicht garantiert werden, dass dies mit allen Treibern funktioniert.
 *
 *  Die Verwendung wird gestattet, erfordert aber eventuell
 *  Anpassungen bei anderen Versionen des Treibers.
 *
 *  Ebenso ist die direkte Verwendung der CanConfirmationMask und
 *  CanConfirmationFlags._c nicht Teil der offiziellen Schnittstelle.
 *
 *  @todo
 *  In der Version des CAN Treibers fuer HCS 12 sind diese
 *  Funktionen vorhanden. Falls diese fuer andere CPU Typen nicht
 *  vorhanden sind (Erkennung: Compilierfehler), dann muessen
 *  entsprechende Anpassungen in dieser Datei vorgenommen werden.
 *
 *  Die Makros CAN_CONFIRMATION_FLAG und CAN_CONFIRMATION_MASK
 *  kapseln den Zugriff auf die Confirmation-Flags. Es wird
 *  davon ausgegangen, dass der CAN Treiber nach dem Versenden
 *  das entsprechende Bit setzt.
 *
 *  CanGetRxDataPtr liefert zu einem CanMsgHandle einen Zeiger
 *  auf den Can-Puffer der empfangenen Nachricht.
 *
 *  CanGetTxDataPtr liefert zu einem CanMsgHandle einen Zeiger
 *  auf den Can-Puffer der zu sendenden Nachricht.
 *
 *  @todo
 *  Diese Implementierung unterstuetzt nicht die Verwendung von
 *  Can-Interface-Channels. Daher muss in der Xml-Konfiguration immmer 1
 *  als Can-Interface-Channel eingetragen sein, da diese Implementierung
 *  diesen Wert als Konstante beim Empfang verwendet.
 *  Ansonsten werden im BCL alle empfangenen Daten verworfen.
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
 * 2017-03-07	1.9.0 		FST			[SSWCCB-1545] SSW-Lokatierungs-Pragmas eingefuegt
 * 2014-10-06	1.8.0		FST			[SSWCCB-2104] Umstellung u8Length auf uint16_t u16MsgLength für Nachrichtengroesse > 8 Byte
 * 2007_08_29   1.5         SHU         Setzen des ConfirmationFlag das zum Xten Mal hintereinander nicht gesetzt ist.
 * 2007_08_01   1.5         SHU         Define Integrationsbeispiel
 * 2005-04-21   1.3         ALA         Aufsplittung nach Prozessortyp
 * 2004-09-09   1.2         ALA         Initiale Version
 ******************************************************************/

/* Systemincludes mit <...> */
#include <stdlib.h>
#include <string.h>

/* Bibliotheken von externen Herstellen mit <...> */
#include "can_inc.h"

/* Eigene Header-Dateien "..." */
#include "bap_canubs.h"
#include "bap_bclconfig.h"

#ifdef BAP_RUNTIME_TEST
#include "sw_timer.h"
#endif /*BAP_RUNTIME_TEST */

#ifndef BAP_USES_CAN
#error Die mit BAPgen konfigurierte Datenfestlegung enthaelt kein CAN.
#endif

#ifndef BAP_INTEGRATIONSBEISPIEL
#error Dies ist nur ein Beispiel. Bitte passen Sie die Datei ihren Anforderungen an.
#endif

/* Externe globale Variablen-Definitionen */

/**
 * Aufgrund von Problemen bzgl. Bitfeldern mit dem Metrowerks Compiler
 * wird ueber dieses Makro direkt auf das CAN-Tx-Confirmation-Bitfeld
 * des CAN Treibers zugegriffen um festzustellen, ob das Versenden einer
 * CAN Botschaft moeglich ist bzw. erfolgreich war.
 */
#define CAN_CONFIRMATION_FLAG(CanTxHandle) \
        CanConfirmationFlags._c[CanConfirmationOffset[(CanTxHandle)]]

/**
 * Aufgrund von Problemen bzgl. Bitfeldern mit dem Metrowerks Compiler
 * wird ueber dieses Makro direkt das CAN-Tx-Confirmation-Bitfeld
 * des CAN Treibers maskiert um festzustellen, ob das Versenden einer
 * CAN Botschaft moeglich ist bzw. erfolgreich war.
 */
#define CAN_CONFIRMATION_MASK(CanTxHandle) \
        CanConfirmationMask[(CanTxHandle)]


/* Interne Typ-Definitionen */

/* Interne Const Deklarationen */

/* Interne statische Variablen */

/* Vorwaerts-Deklarationen von statischen Funktionen */

/* Definition (Implementierung) von statischen Funktionen */

/* Definition (Implementierung) von globalen Funktionen */


/*  Diese Funktion ist in bap_canubs.h dokumentiert */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_FAR bool_t
BAP_CANUBS_TxData(BapCanInterfaceChannel_t aCanInterfaceChannel
    , BapCanMsgId_t aCanMsgId
    , const ptr_t apData
    , uint16_t au16MsgLength)
{
    DBGVAR bool_t bResult;
    volatile uint8_t* pu8ConfFlag;
    DBGVAR uint8_t u8ConfMask;
    DBGVAR uint8_t u8InterruptStatus;
    DBGVAR ptr_t pCanMsgObject;

#ifdef BAP_RUNTIME_TEST
    BAP_RUNTIME_TEST_TRANSMIT_START();
#endif /* BAP_RUNTIME_TEST */

    disableint(&u8InterruptStatus);

    /* Hole Zeiger auf CAN Message Object */
    pCanMsgObject = CanGetTxDataPtr(aCanMsgId);

    /*lint -e668*//* apData ist niemals NULL */
    MEMCPY(pCanMsgObject, apData, au16MsgLength);
    /*lint +e668*/

    pu8ConfFlag = &(CAN_CONFIRMATION_FLAG(aCanMsgId));
    u8ConfMask = CAN_CONFIRMATION_MASK(aCanMsgId);

    /* Tx Confirmation Flag loeschen, damit weitere Sendevorgaenge blockiert werden */
    *pu8ConfFlag &= ~u8ConfMask;

#ifdef C_ENABLE_VARIABLE_DLC
    if (kCanTxOk != CanTransmitVarDLC(aCanMsgId, au16MsgLength) )
#else
    if (kCanTxOk != CanTransmit(aCanMsgId))
#endif
    {
        /* Tx Confirmation Flag wieder setzen, sonst wird das Senden fuer immer blockiert */
        *pu8ConfFlag |= u8ConfMask;

        restoreint(u8InterruptStatus);
        bResult = BAP_FALSE;
    }
    else
    {
        /* das Tx Confirmation Flag wird vom Treiber gesetzt, wenn der CAN-Controller
           per Interrupt das erfolgreiche Versenden meldet. */

        restoreint(u8InterruptStatus);
        bResult = BAP_TRUE;

        /* Fehlercodes 'kCanTxFailed' und 'kCanTxPartOffline'
           des CAN-Treibers werden nicht weiter ausgewertet.

           Im Fehlerfall wird beim naechsten Aufruf versucht die Botschaft erneut zu senden */
    }

#ifdef BAP_RUNTIME_TEST
    BAP_RUNTIME_TEST_TRANSMIT_STOP();
#endif /* BAP_RUNTIME_TEST */

    return bResult;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


/*  Diese Funktion ist in bap_canubs.h dokumentiert */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_FAR bool_t
BAP_CANUBS_IsReadyForTx(BapCanInterfaceChannel_t aCanInterfaceChannel
    , BapCanMsgId_t aCanMsgId)
{
    DBGVAR bool_t bResult;
    static uint8_t CF_TimeoutTable[BAP_CAN_TX_SEGMENTATION_CHANNELS] = {0}; /*Tabelle zum ermitteln, wie oft ein ConfirmationFlag hintereinander ungesetzt blieb.*/
    uint16_t i;

    /* Beim Lesezugriff auf Confirmationflags ist die Interruptsperre nicht erforderlich */
    bResult = (CAN_CONFIRMATION_FLAG(aCanMsgId) & CAN_CONFIRMATION_MASK(aCanMsgId)) ? BAP_TRUE : BAP_FALSE;

    /* Wenn ConfirmationFlag zum Xten mal in Folge nicht gesetzt ist => automatisch setzen!*/
    for(i=0;i<BAP_CAN_TX_SEGMENTATION_CHANNELS;i++)
    {
        if(aCanMsgId == BAP_InhibitRomTable[i].canMsgId)
        {
            if(!bResult)
            {
                if(CF_TimeoutTable[i] < BAP_MAX_CONFIRMATION_FLAG_TIMEOUT)
                {
                    CF_TimeoutTable[i]++;
                }
                else
                {
                    /* Hier wird ConfirmationFlag gesetzt!*/
                    (CanConfirmationFlags._c[CanConfirmationOffset[(aCanMsgId)]] |= (CanConfirmationMask[(aCanMsgId)]));
                    CF_TimeoutTable[i] = 0;
                    /*break;*/
                }
            }
            else
            {
               CF_TimeoutTable[i] = 0;
            }
        }
    }

    return bResult;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


/*  Diese Funktion ist in bap_canubs.h dokumentiert */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_FAR void
BAP_CANUBS_InitReadyForTx(BapCanInterfaceChannel_t aCanInterfaceChannel
    , BapCanMsgId_t aCanMsgId)
{
    volatile uint8_t* pu8ConfFlag;
    DBGVAR uint8_t u8InterruptStatus;

    disableint(&u8InterruptStatus);
    pu8ConfFlag = &CAN_CONFIRMATION_FLAG(aCanMsgId);
    *pu8ConfFlag |= CAN_CONFIRMATION_MASK(aCanMsgId);
    restoreint(u8InterruptStatus);
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


/*  Callback-Funktionen */

/* HCS12 Version benutzt die BAP_BCL_CanRxPreCopy Funktion und variablen DLC */

/**
 *  Wird im CAN ReceiveInterrupt aufgerufen, bevor die Daten in
 *  den Empfangspuffer kopiert wurden.
 *
 *  @param aRxCanMsgHandle => Handle-Nummer der Empfangsbotschaft
 *
 *  @returns kCanNoCopyData
 *
 *  @remarks: Diese Funktion muss verwendet werden, wenn variabler
 *  DLC unterstuetzt werden soll.
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
uint8_t
BAP_BCL_CanRxPreCopy(CanReceiveHandle aRxCanMsgHandle)
{
#ifdef BAP_RUNTIME_TEST
    BAP_RUNTIME_TEST_IRQ_START();
#endif /* BAP_RUNTIME_TEST */
    BAP_CANUBS_RxData((BapCanInterfaceChannel_t) 1u, (const BapCanMsgId_t) aRxCanMsgHandle, &CanRxActualData(0), CanRxActualDLC);
#ifdef BAP_RUNTIME_TEST
    BAP_RUNTIME_TEST_IRQ_STOP();
#endif /* BAP_RUNTIME_TEST */

    return kCanNoCopyData;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>
