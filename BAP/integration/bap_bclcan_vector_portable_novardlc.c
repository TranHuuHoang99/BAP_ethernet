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
 *  WARNUNG
 *  Diese Variante unterstuetzt nicht den Empfang von variablem DLC,
 *  ist aber unabhaengig von der Version des Vector CAN-Treibers.
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
 * 2007_08_31   1.5         SHU         Setzen des ConfirmationFlag das zum Xten Mal hintereinander nicht gesetzt ist.
 * 2006_08_01   1.5         SHU         Define Integrationsbeispiel
 * 2005-04-21   1.3         ALA         Aufsplittung nach Prozessortyp,
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

#ifndef BAP_USES_CAN
#error Die mit BAPgen konfigurierte Datenfestlegung enthaelt kein CAN.
#endif

#ifndef BAP_INTEGRATIONSBEISPIEL
#error Dies ist nur ein Beispiel. Bitte passen Sie die Datei ihren Anforderungen an.
#endif

#if defined(C_ENABLE_DLC_CHECK) || defined(BAP_ASG)
#error Diese Version unterstuetzt keinen variablen DLC.
/* Bitte abklaeren, ob variabler DLC unterstuetzt werden muss!
 * Falls ja, bitte zu den anderen in diesem Verzeichnis liegenden Versionen ausweichen.
 * ASGs muessen immer variablen DLC unterstuetzen.
 * Falls nein (sehr unwahrscheinlich), dann kann diese Zeile entfernt werden.
 */
#endif /* #if defined(C_ENABLE_DLC_CHECK) || defined(BAP_ASG) */


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

/**
 *  Wird im CAN ReceiveInterrupt aufgerufen nachdem die Daten
 *  aus dem Empfangspuffer des ECU CAN Moduls in das zugehoerige
 *  CAN Datenobjekt des CAN Treibers kopiert wurde.
 *
 *  Die Funktion kopiert bei passender Konfiguration (Handle ist
 *  fuer den CAN Rx eingetragen) die Daten in den BCL Rx Puffer.
 *  Segmentierte sowie unsegmentierte Datenstroeme werden in
 *  dieser Funktion mit Hilfe von entsprechenden Subfunktion
 *  verarbeitet.
 *
 *  @param aRxCanMsgHandle => Handle-Nummer der Empfangsbotschaft
 *
 *  @remarks: Dies ist die portable Version, sie unterstuetzt aber
 *  kein variables DLC.
 *
 *  Wenn variabler DLC erforderlich ist, muss stattdessen die
 *  CanPreCopy-Funktion BAP_BCL_CanRxPreCopyHCS12 verwendet werden.
 *
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
void
BAP_BCL_CanRxIndicationFunction(DBGVAR BapCanMsgId_t aRxCanMsgHandle)
{
    BAP_CANUBS_RxData((BapCanInterfaceChannel_t) 1u, aRxCanMsgHandle, (ptr_t) CanGetRxDataPtr(aRxCanMsgHandle), (uint8_t) 8);
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>
