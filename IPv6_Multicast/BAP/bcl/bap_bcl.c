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
 *  Diese Datei enthaelt die Implementierung der BCL Schicht im BAP
 *  Projekt.
 *
 *  Diese C-Datei enthaelt nicht die Funktionen BAP_BCL_Received
 *  und BAP_BCL_ErrorIndication, da diese von der BPL Schicht
 *  implementiert werden.
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
 * 2022-07-26   1.12.0      DRH         [SSWPPB-292] Removed const keyword for parameters for function BAP_BCL_GeneralSend
 * 2022-06-17	1.12.0		DRH			[SSWPPB-269] Release preparation, adapt Copyright date and version number.
 * 2021-12-07	1.11.3		JEO			[SSWPPB-244] Release preparation, adapt Copyright date and version number.
 * 2021-03-08   1.11.3      DRH         [SSWPPB-142] Replaced magic numbers by constants
 * 2021-03-01	1.11.3		JEO			[SSWPPB-142] Improve jutification of Pc-Lint deac or MISRA rules violation.
 * 2020-03-31   1.11.1      ODD         [SSWPPB-93] added const keyword for parameters for function BAP_BCL_GeneralSend 
 * 2020-01-13   1.11.1      ODD         [SSWPPB-43] Heartbeat unterbricht Status Bugfix
 * 2019-03-21   1.10.99     KUL         [SSWPPB-4] Removal of string.h inclusion
 * 2018-07-19   1.10.3      FFS         [SSWCCB-2522] Misra-2012 fix (release was postponed)
 * 2017-07-24   1.10.0      FHA         [SSWCCB-2391] Schnelle Suche TX-PDU
 * 2017-02-24   1.9.0       FST         [SSWCCB-1545] SSW-Lokatierungs-Pragmas eingefuegt
 * 2016-10-13   1.8.1       FST         [SSWCCB-2410] Softwareschalter DLL_COMPILATION zur Unterscheidung
 *                                      der Erzeugung von Steuergeraete-Code und der BAP-Dll eingefuegt
 * 2014-11-28   1.8.0.0     WWU/FST     [SSWCCB-2105] Formataenderung der Variablen 16Bit->32Bit
 * 2014-03-24   1.7.1       WWU         MISRA-2004 fix: Funktion-Like Makros fuer BAP_BCL_Start wurde entfernt.
 * 2014-03-21   1.7.1       WWU         CCB-664 und CCB-1731: Alignment problem.
 * 2013-01-30   1.7.0       WWU         MISRA-2004 fix
 * 2012-10-15   1.6.5.1     WWU         Korrektur der Misra-98 Abweichungen
 * 2011-05-02   1.6         HWA         Bugfix Endlosschleife durch Compiler (LB BAP1.6 A-10) 
 * 2006-06-07   1.4         ALA         Falls ein Status verzoegert gesendet wird bleibt der Opcode erhalten, falls
 *                                      das Senden eines Heartbeats angetriggert wird.
 * 2006-04-12   1.4         ALA         Unterstuetzung fuer neue HB-Trigger.
 * 2006-04-12   1.4         ALA         Unterstuetzung fuer BAP_ROM_DATA_FAR.
 * 2005-04-29   1.3         ALA         Entfernung von Dummy-Code. Doppelte Abfrage (nun in bclcan) des Lsg-Zustands entfernt.
 * 2005-04-15   1.3         ALA         Reduzierung der CPU-Last bei Busruhe
 * 2005-04-13   1.3         CRI         ASG&FSG zusammen
 * 2005-04-08   1.3         ALA         Anpassung an neue Datenstrukturen, Optimierung Parameteruebergabe
 * 2005-03-14   1.2.1       CRI         BCL_Start hinzugefuegt
 * 2005-03-14   1.2.1       CRI         Errors & Nachrichten wenn nicht mehr an BPL
 *                                      uebergeben, wenn Zustand nicht running ist
 * 2004-11-17   1.2         ALA         Behandlung fuer Antwort auf GetAll als Einzelnachrichten oder
 *                                      Block hinzugefuegt.
 * 2004-11-04   1.2         ALA         BAP_BCL_SendError Funktion hinzugefuegt.
 * 2004-09-17   1.1.1       ALA         Out-Of-Bounds-Check in BAP_BCL_GeneralSend hinzugefuegt
 * 2004-06-07   1.1         JOK         Compilerschalter fuer SG-Typen zur Optimierung
 *                                      des ROM-Bedarfs eingefuegt
 * 2004-06-07   1.1         JOK         Die verschiedenen Send-Funktionen (BufferSet, Send, Abort,
 *                                      Resend, ResendWithOpcode) zu einer allgemeinen Funktion
 *                                      BAP_BCL_GeneralSend() zusammengefasst.
 * 2004-06-07   1.1         JOK         BAP_BCL_Start() und BAP_BCL_Shutdown() entfernt (siehe bap_bcl.h)
 ******************************************************************/


/* Systemincludes mit <...> */

/* Bibliotheken von externen Herstellen mit <...> */

/* Eigene Header-Dateien "..." */
#include "bap_types.h"
#include "bap_config.h"
#include "bap_privatetypes.h"
#include "bap_bcl.h"
#include "bap_bclutil.h"
#include "bap_bclbus.h"
#include "bap_util.h"
#include "bap_debug.h"
#include "bap_balconfig.h"

#ifdef BAP_RUNTIME_TEST
#include "sw_timer.h"
#endif /* BAP_RUNTIME_TEST */

/* Externe globale Variablen-Definitionen */

/* Diese Variable ist in bap_bcl.h dokumentiert */
#ifdef BAP_TASKTIME_LIMIT
#   ifndef DLL_COMPILATION
#       define BAP_START_SEC_VAR_NO_INIT_32
#       include <BAP_MemMap.h>
uint32_t BAP_u32TaskTimeCounter;
#       define BAP_STOP_SEC_VAR_NO_INIT_32
#       include <BAP_MemMap.h>
#   endif /* #ifdef DLL_COMPILATION */
#endif /* #ifdef BAP_TASKTIME_LIMIT */

/* Interne Makro-Definitionen */

/* Interne Typ-Definitionen */
typedef enum BapSendType_t
{
    /** Kennung fuer einen Sendeauftrag durch BAP_BCL_Send() */
    BapSendType_Send,
#if defined (BAP_ASG) || defined(WIRD_NIE_GEBRAUCHT)
    /** Kennung fuer einen Sendeauftrag durch BAP_BCL_AbortSend() */
    BapSendType_Abort,
#endif /* #if defined (BAP_ASG) || defined(WIRD_NIE_GEBRAUCHT) */
#ifdef BAP_ASG
    /** Kennung fuer einen Sendeauftrag durch BAP_BCL_Resend() */
    BapSendType_Resend,
#endif /* #ifdef BAP_ASG */
#ifdef BAP_FSG
    /** Kennung fuer einen Sendeauftrag durch BAP_BCL_BufferSet() */
    BapSendType_BufferSet,
    /** Kennung fuer einen Sendeauftrag durch BAP_BCL_SendError() */
    BapSendType_SendError,
    /** Kennung fuer einen Sendeauftrag durch BAP_BCL_ResendWithOpcode() */
    BapSendType_ResendWithOpcode,
#endif /* #ifdef BAP_FSG */
    /*lint -esym(749, BapSendType_t::BapSendType_Unused) */
    /** Diese Kennung wird nicht verwendet. Dient als Abschluss fuer das Komma abhaengig vom Steuergeratetyp */
    BapSendType_Unused
} BapSendType_et;

/* Interne Const Deklarationen */

/* Interne statische Variablen */


/* Vorwaerts-Deklarationen von statischen Funktionen */

#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>

static BAP_IMPL_FAR void
BAP_BCL_GeneralSend(const BapInternalParameters_cpot apoPars
    , DBGVAR BapSendType_et aeSendType);

#ifdef BAP_USES_SEGMENTATION
static BAP_IMPL_FAR void
BAP_BCL_SingleRxNotify(BapInternalParameters_pot apoPars);
#endif /* #ifdef BAP_USES_SEGMENTATION */

#ifdef BAP_FSG
BAP_STATIC BAP_IMPL_FAR void
BAP_BCL_SendStatusAll(BapInternalParameters_cpot apoPars);
#endif /* #ifdef BAP_FSG */

#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>

/* Definition (Implementierung) von statischen Funktionen */

/**
 *  Allgemeine Funktion zum Senden von Nachrichten. Je nach Parameterwert von aeSendType
 *  werden die entsprechenden spezialisierten Funktionen ausgefuehrt.
 *
 *  @param apoPars  Struktur mit den benoetigten Parametern:<br>
 *                  -\>poLsgRomRow - Zeigt auf das den Sendeauftrag betreffende LSG oder NULL, falls kein LSG zugeordnet werden kann<br>
 *                  -\>poFctRomRow - Zeigt auf die den Sendeauftrag betreffende FCT oder NULL, falls die gesuchte FCT nicht existiert<br>
 *                  -\>pData       - Zeigt auf die  zu sendenden Daten<br>
 *                  -\>u32Length   - Enthaelt die Laenge der zu sendenden Daten<br>
 *                  -\>eOpCode     - Enthaelt den zu sendenden OpCode
 *
 *  @param aeSendType  Typ der speziellen Sendeanforderung
 *
 *  Diese Funktion hat 54 Statements (max.50)
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
static BAP_IMPL_FAR void
BAP_BCL_GeneralSend(const BapInternalParameters_cpot apoPars
        , DBGVAR BapSendType_et aeSendType)
{
    /*lint -esym(613,apoPars) */
    DBGVAR uint8_t u8TxTableIdx;
    BapFctRomRow_pot poFctRomRow = apoPars->poFctRomRow;
    DBGVAR bool_t bFlag = BAP_TRUE;
    DBGVAR uint32_t u32Length = apoPars->u32Length;

#ifdef BAP_TASKTIME_LIMIT
    apoPars->poLsgRomRow->poLsgRamRow->fState.fTxFlag = BAP_TRUE;
#endif /* #ifdef BAP_TASKTIME_LIMIT */

    for (u8TxTableIdx=(uint8_t)0; (NULL != poFctRomRow) && (u8TxTableIdx < poFctRomRow->u8TxTableSize); u8TxTableIdx++)
    {
        BapBusIndirectionTxRomRow_pot  const poBusTxRomRow
        = &(BAP_BusIndTxTable[poFctRomRow->u16BusTxTableIndex + (uint16_t)u8TxTableIdx]);
        BapBclTxRamRow_pot  const poBclTxRamRow
        = poBusTxRomRow->poBclTxRamRow;

        if(BapIft_None != poBusTxRomRow->eInterfaceType)
        {
            switch(aeSendType)
            {
            /* Im folgenden keine Fallunterscheidungen fuer das Kombigeraet noetig */
            /* da Types nur in bestimmten SGs auftreten koennen, @see BapSendType_t */
#if defined(BAP_ASG) || defined(WIRD_NIE_GEBRAUCHT)
            case BapSendType_Abort:
#ifdef BAP_USES_SEGMENTATION
                poBusTxRomRow->poBclTxRamRow->flags.fTxInProgressFlag = (uint8_t)0;
#endif /* #ifdef BAP_USES_SEGMENTATION */
                poBusTxRomRow->poBclTxRamRow->flags.fTxRequestFlag = BAP_FALSE;

#ifdef BAP_USES_ACKNOWLEDGE
                poBclTxRamRow->flags.fTxRequestNeedsAckFlag = BAP_FALSE;
#endif /* #ifdef BAP_USES_ACKNOWLEDGE */

                break;
#endif /* #if defined(BAP_ASG) || defined(WIRD_NIE_GEBRAUCHT) */
#ifdef BAP_FSG
            case BapSendType_BufferSet:
#endif /* #ifdef BAP_FSG */
            case BapSendType_Send:
                /* Opcode in Buffer schreiben */
                poBclTxRamRow->eOpCode = apoPars->eOpCode;

                /* Wert ist unzulaessig ? */
                if (u32Length > poBusTxRomRow->u32BufferSize)
                {
                    /* Was zuviel ist abschneiden */
                    u32Length = poBusTxRomRow->u32BufferSize;
                }

                /* Setze Datengroesse des Sendepuffers und kopiere die Daten */
                poBclTxRamRow->oBufferWithLength.u32Length = u32Length;
                /*lint -e9087*/ /* MISRA_2012_REQ_11.3 : 1st and 2nd arguments of MEMCPY are of types (uint8_t*)
                                 * and (const unsigned char*). They are implicitly cast to (void*). The memory is
                                 * packed because it is uint8_t and unsigned char so there should be no problem to copy.*/
                MEMCPY(poBclTxRamRow->oBufferWithLength.paru8Buffer, apoPars->pData, u32Length);
                /*lint +e9087*/

#ifdef BAP_FSG
#if defined(BAP_ASG) && defined(BAP_FSG)
                if (BapSG_FSG == apoPars->poLsgRomRow->eSGType)
#endif /* defined(BAP_ASG) && defined(BAP_FSG) */
                {
                    poBclTxRamRow->flags.fTxInitializedFlag = BAP_TRUE;
                    /* Setze Tx Flags bei Send und loesche Sie bei BufferSet */
                    bFlag = (const bool_t) ((BapSendType_BufferSet != aeSendType) ? BAP_TRUE : BAP_FALSE);
                }
#endif /* #ifdef BAP_FSG */
#ifdef BAP_USES_SEGMENTATION
                poBusTxRomRow->poBclTxRamRow->flags.fTxInProgressFlag = (uint8_t)0;
#endif /* #ifdef BAP_USES_SEGMENTATION */
                poBusTxRomRow->poBclTxRamRow->flags.fTxRequestFlag = bFlag;

#ifdef BAP_USES_ACKNOWLEDGE
                poBclTxRamRow->flags.fTxRequestNeedsAckFlag = bFlag;
#endif /* #ifdef BAP_USES_ACKNOWLEDGE */
                break;
#ifdef BAP_FSG
            case BapSendType_SendError:
                /* Fehlerwert in Spezialpuffer speichern */
                /*lint -e9034*/ /* MISRA_2012_REQ_10.3 : PC-Lint 9.00L throws a warning due to Tool bug. Hence, this warning has been deactivated.
                                 * Documented with a mail from the Lint team in the SSWCCB-2522_BAP-Entwicklung auf MISRA2012 umstellen folder */
            	/* MISRA_2012_REQ_10.5 : no risk arise because *apoPars->pData contains an error code between 0x00 and 0xFF which fit in enum */
                poBclTxRamRow->eErrorCode = (BapError_et) *apoPars->pData;
                /*lint +e9034*/
                /* TX Flag setzen, damit Fehler ausgesendet wird */
                poBclTxRamRow->flags.fTxErrorFlag = BAP_TRUE;

#if defined(BAP_FSG) && defined(BAP_USES_ACKNOWLEDGE)
                poBclTxRamRow->flags.fTxErrorNeedsAckFlag = BAP_TRUE;
#endif /* #if defined(BAP_FSG) && defined(BAP_USES_ACKNOWLEDGE) */

                /* Durch das Loeschen des Progress-Flags wird zuerst der Fehler gesendet (Prioritaet).
                       Falls zuvor eine Wertuebertragung lief, wird diese nach dem Aussenden des Fehlers neu begonnen.
                       Somit geht der Werte-Request nicht verloren, aber der Fehler wird zuerst gemeldet.

                       Ein Aussenden des Fehlers bei eingeschalteter Segmentierung zwischendurch haette sonst die Wirkung,
                       dass die Start-Botschaft (des Fehlers) dazwischen im ASG zu Sequenzfehlern fuehren wuerde,
                       da keine weiteren Segmente mehr erwartet wuerden.
                 */
#if defined(BAP_FSG) && defined(BAP_USES_SEGMENTATION)
                if (BAP_FALSE != poBclTxRamRow->flags.fTxInProgressFlag)
                {
                    poBclTxRamRow->flags.fTxRequestFlag = BAP_TRUE;
                    poBclTxRamRow->flags.fTxInProgressFlag = BAP_FALSE;
                }
#endif /* #if defined(BAP_FSG) && defined(BAP_USES_SEGMENTATION) */

                break;
            case BapSendType_ResendWithOpcode:
#if defined(BAP_FSG) && defined(BAP_USES_ACKNOWLEDGE)
                /* Fuehre kein ResendWithOpcode durch, falls gewoehnliches Senden noch nicht erfolgt */
                /*
                 * Ticket SSWPPB 43 Bugfix Heartbeat unterbricht Status.
                 * Neue Bedingungsabfrage, wenn Heartbeat und bereits eine uebertragung derselben FctId laueft , Heartbeat verwerfen
                 */
                if ( (BAP_FALSE == (bool_t) (poBclTxRamRow->flags.fTxRequestNeedsAckFlag))
#ifdef BAP_USES_SEGMENTATION
                        && ( (BapOp_PropHeartbeatStatus != apoPars->eOpCode) || (BAP_FALSE == (bool_t) poBclTxRamRow->flags.fTxInProgressFlag) )
#endif

                    )
#endif /* #if defined(BAP_FSG) && defined(BAP_USES_ACKNOWLEDGE) */
                {
#if defined(BAP_FSG) && defined(BAP_USES_ACKNOWLEDGE)
                    poBclTxRamRow->flags.fTxRequestNeedsAckFlag = BAP_FALSE;
#endif /* #if defined(BAP_FSG) && defined(BAP_USES_ACKNOWLEDGE) */

                    /*  Aendere den OpCode ab */
                    poBclTxRamRow->eOpCode = apoPars->eOpCode;

#ifdef BAP_USES_SEGMENTATION
                    poBusTxRomRow->poBclTxRamRow->flags.fTxInProgressFlag = (uint8_t)0;
#endif /* #ifdef BAP_USES_SEGMENTATION */
                    poBusTxRomRow->poBclTxRamRow->flags.fTxRequestFlag = BAP_TRUE;
                }
                break;
#endif /* #ifdef BAP_FSG */
#ifdef BAP_ASG
            case BapSendType_Resend:
#ifdef BAP_USES_SEGMENTATION
                poBusTxRomRow->poBclTxRamRow->flags.fTxInProgressFlag = (uint8_t)0;
#endif /* #ifdef BAP_USES_SEGMENTATION */
                poBusTxRomRow->poBclTxRamRow->flags.fTxRequestFlag = BAP_TRUE;

                /* Falls noch ein Acknowledge aussteht, nichts dran aendern */
                break;
#endif /* #ifdef BAP_ASG */
            default:
                /* No Statements */
                break;
            }
            if  (((bitfield_t) 1u == poBusTxRomRow->poBclTxRamRow->flags.fTxRequestFlag)
#ifdef BAP_USES_SEGMENTATION
                    || ((bitfield_t) 1u == poBusTxRomRow->poBclTxRamRow->flags.fTxInProgressFlag)
#endif  /* #ifdef BAP_USES_SEGMENTATION */
#ifdef BAP_FSG
                    || ((bitfield_t) 1u == poBusTxRomRow->poBclTxRamRow->flags.fTxErrorFlag)
#endif /* #ifdef BAP_FSG */
            )   {
                /* Falls Sende-Flag gesetzt wurde muss die Komponente in den Sende-Buffer eintragen werden. */
                BAP_BCL_CanTxBufferWrite(poBusTxRomRow->poCanTx);
            }
        }
    }   /* for (u8TxTableIdx... */
    return;
    /*lint +esym(613,apoPars) */
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


#ifdef BAP_USES_SEGMENTATION
/**
 *  Diese Funktion prueft, ob ein Datenelement oder ein Fehlerwert empfangen wurde
 *  und ruft ggfs. die entsprechende Callback-Funktion auf.
 *
 *  @see BAP_BCL_ErrorIndication, BAP_BCL_DataReceived
 *
 *  @param apoPars  benoetigt die Parameter lsgId und fctId sowie die Zeiger auf die entsprechenden ROM-Zeilen.
 *
 *  @remarks: Diese Funktion veraendert apoPars->eOpCode, apoPars->pData und apoPars->u32Length
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
static BAP_IMPL_FAR void
BAP_BCL_SingleRxNotify(BapInternalParameters_pot apoPars)
{
    /*lint -esym(613,apoPars) */
    DBGVAR uint8_t u8BusRomRowIdx;
    DBGVAR uint8_t u8BusTableSize = apoPars->poFctRomRow->u8RxTableSize;
    DBGVAR uint16_t u16BusRxTableIdx = apoPars->poFctRomRow->u16BusRxTableIndex;

#ifdef BAP_RUNTIME_TEST
    BAP_RUNTIME_TEST_INDBS_START();
    BAP_RUNTIME_TEST_INDALL_START();
#endif /* BAP_RUNTIME_TEST */

    /* Durchsuche alle Empfangsmoeglichkeiten fuer die jeweilige FunctionId */
    for(u8BusRomRowIdx = (uint8_t)0; u8BusRomRowIdx < u8BusTableSize; u8BusRomRowIdx++)
    {
        BapBclRxRamRow_pot  const poBclRxRamRow = BAP_BusIndRxTable[u16BusRxTableIdx + (uint16_t)u8BusRomRowIdx].poBclRxRamRow;

        /* wenn kein Rx-Puffer vorhanden, dann wurde der Empfang direkt gemeldet, z.B. in BAP_CAN_RxUnsegmented */
        if (NULL != poBclRxRamRow)
        {
            /* Wurde ein Fehler empfangen? */
            if(BAP_FALSE != poBclRxRamRow->flags.fRxErrorFlag)
            {
#ifdef BAP_TASKTIME_LIMIT
                BAP_u32TaskTimeCounter = BAP_u32TaskTimeCounter + BAP_IND_RX_TIME + (uint16_t)sizeof(BapError_et);
                apoPars->poLsgRomRow->poLsgRamRow->fState.fRxFlag = BAP_TRUE;
#endif /* #ifdef BAP_TASKTIME_LIMIT */

                /* BPL benachrichten */
                BAP_BCL_ErrorIndication(apoPars->lsgId
                    , apoPars->fctId
                    , poBclRxRamRow->eErrorCode);

                /* Loesche RxError Flag */
                poBclRxRamRow->flags.fRxErrorFlag = BAP_FALSE;
            }

            /* Wurde das Datenelement vollstaendig empfangen? */
            if(BAP_FALSE != poBclRxRamRow->flags.fRxCompleteFlag)
            {
                apoPars->eOpCode = poBclRxRamRow->eOpCode;
                apoPars->pData = *(poBclRxRamRow->oBufferWithLength.paru8Buffer);
                apoPars->u32Length = poBclRxRamRow->oBufferWithLength.u32Length;

#ifdef BAP_TASKTIME_LIMIT
                BAP_u32TaskTimeCounter = (uint32_t)(BAP_u32TaskTimeCounter + BAP_IND_RX_TIME + apoPars->u32Length);
                apoPars->poLsgRomRow->poLsgRamRow->fState.fRxFlag = BAP_TRUE;
#endif /* #ifdef BAP_TASKTIME_LIMIT */

                /* BPL benachrichtigen */
                BAP_BCL_DataReceived(apoPars);

                /* Loesche RxComplete Flag */
                poBclRxRamRow->flags.fRxCompleteFlag = BAP_FALSE;
            }
        }
    }

#ifdef BAP_RUNTIME_TEST
    BAP_RUNTIME_TEST_INDBS_STOP();
    BAP_RUNTIME_TEST_INDALL_STOP();
#endif /*BAP_RUNTIME_TEST */

    return;
    /*lint +esym(613,apoPars) */
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* #ifdef BAP_USES_SEGMENTATION */

#ifdef BAP_FSG
/**
 *  Diese Funktion behandelt eine GetAll Anfrage und sendet entwender einzelne Heartbeat-Statusnachrichten
 *  oder einen StatusAll-Block als Antwort auf die GetAll Anfrage.
 *
 *  @param apoPars Struktur mit den benoetigten Parametern:<br>
 *                 -\>poLsgRomRow - Zeigt auf das den Sendeauftrag betreffende LSG oder NULL, falls kein LSG zugeordnet werden kann <br>
 *                 -\>poFctRomRow - Zeigt auf die den Sendeauftrag betreffende FCT oder NULL, falls die gesuchte FCT nicht existiert
 *
 *  @remarks
 *  Wenn ein Sendepuffer existiert, wird ein StatusAll-Block als Antwort gesendet.
 *  Sonst wird mit einzelnen Heartbeat Status Nachrichten geantwortet.
 *
 *  Diese Funktion hat 6 ControlNestingLayers (max.4)
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_STATIC BAP_IMPL_FAR void
BAP_BCL_SendStatusAll(BapInternalParameters_cpot apoPars)
{
    DBGVAR uint8_t u8FctIdMask = BAP_FCTID_BAPCONFIG_BITMAP;  /* FctId 0 (reserviert) und 1 (Cache) brauchen nicht ausgewertet zu werden */

    uint8_t u8Counter;
    DBGVAR uint8_t u8FctListSeg;
#ifdef BAP_USES_STATUS_ALL
    BapBufferWithLength_pot poGetAllBufferWithLength = NULL;
#endif /* BAP_USES_STATUS_ALL */

    /*lint -esym(613, apoPars) */
    BAP_ASSERT(NULL != apoPars);

    BAP_InitInternalParameters(&Bap_oPars);
    Bap_oPars.eOpCode = BapOp_PropHeartbeatStatus;

#ifdef BAP_USES_STATUS_ALL
    if (BAP_MAX_UINT16 != apoPars->poFctRomRow->u16BusTxTableIndex)
    {
        poGetAllBufferWithLength = &((BAP_BusIndTxTable[apoPars->poFctRomRow->u16BusTxTableIndex].poBclTxRamRow)->oBufferWithLength);

        /* Versenden des StatusAll-Blocks beim naechsten BAP_Task Aufruf, OpCode and Flags werden hiermit initialisiert. */
        BAP_BCL_GeneralSend(apoPars, BapSendType_Send);
    }
    else
    {
        /* Nutze Einzelbeantwortung */
    }
#endif /* BAP_USES_STATUS_ALL */

    Bap_oPars.lsgId = apoPars->lsgId;
    Bap_oPars.poLsgRomRow = apoPars->poLsgRomRow;
    u8FctListSeg = apoPars->poLsgRomRow->poLsgRamRow->BAP_aru8FunctionList[0];

    /* Suche alle Properties, in denen ein Bit in der FunctionList gesetzt ist */
    /* MISRA_2012_REQ_10.5 : no risk arise because BAP_FCTID_BAPCONFIG fit in uint8_t */
    for (u8Counter = (uint8_t)BAP_FCTID_BAPCONFIG; u8Counter <= (uint8_t)BAP_MAX_FCT_ID; u8Counter++) /*lint !e650 enums haben mindestens 8 bit */
    {
        /*lint -e9034*/ /* MISRA_2012_REQ_10.3 : PC-Lint 9.00L throws a warning due to Tool bug. Hence, this warning has been deactivated.
                                 * Documented with a mail from the Lint team in the SSWCCB-2522_BAP-Entwicklung auf MISRA2012 umstellen folder */
        Bap_oPars.fctId = (fctId_t)u8Counter; /* MISRA_2012_REQ_10.5 : no risk arise because u8Counter is uint8_t and fit in enum.*/
        /*lint +e9034*/
        /* Wechsel zum naechstes Byte (falls FctId % 8 == 0)? */
        if ( (uint8_t)0 == (BAP_BINARY_ID(Bap_oPars.fctId) & BAP_BITMASK_00000111))
        {
            u8FctIdMask = BAP_BIT7;

            /* Hole dieses Element aus dem Array mit Index (FctId / 8) */
            u8FctListSeg = Bap_oPars.poLsgRomRow->poLsgRamRow->BAP_aru8FunctionList[BAP_BINARY_ID(Bap_oPars.fctId)>>3];
        }

        /* Ist Bit gesetzt? */
        if((uint8_t)0 != (u8FctListSeg & u8FctIdMask))
        {
            Bap_oPars.poFctRomRow = BAP_GetLsgFctRomRow(Bap_oPars.poLsgRomRow, Bap_oPars.fctId);

            if ( BapFctCls_Property != Bap_oPars.poFctRomRow->eFunctionClass )
            {
                /* Nur Properties werden bei StatusAll versendet */
            }
            else
#ifdef BAP_USES_STATUS_ALL
            if (NULL != poGetAllBufferWithLength)
            {
                /* ja, dann fuege diese Nachricht zum Sendepuffer hinzu, falls einer konfiguiert ist */

                /* Hole Nachricht, die hinzugefuegt werden muss */
                BapBufferWithLength_pot poCurrentBufferWithLength = &((BAP_BusIndTxTable[Bap_oPars.poFctRomRow->u16BusTxTableIndex].poBclTxRamRow)->oBufferWithLength);
                Bap_oPars.pData =  *(poCurrentBufferWithLength->paru8Buffer);

                /* Laenge voranstellen, falls erforderlich */
                if (BAP_FALSE != BAP_BusIndTxTable[Bap_oPars.poFctRomRow->u16BusTxTableIndex].bDataTypeSupportsVarLength)
                {
                    Bap_oPars.u32Length = poCurrentBufferWithLength->u32Length;

                    /* Untere 8 Bit der Laenge setzen */
                    (*poGetAllBufferWithLength->paru8Buffer)[poGetAllBufferWithLength->u32Length] = (uint8_t) (Bap_oPars.u32Length);

                    /* Obere 8 Bit der Laenge setzen */
                   ( *poGetAllBufferWithLength->paru8Buffer)[poGetAllBufferWithLength->u32Length+(uint16_t)1u] = (uint8_t) (Bap_oPars.u32Length >> 8);

                    poGetAllBufferWithLength->u32Length += (uint16_t)BAP_NUM_VAR_LENGTH_BYTES;

                    /* Daten kopieren */
                    /*lint -e9087*/ /* MISRA_2012_REQ_11.3 : 1st and 2nd arguments of MEMCPY are of types (uint8_t*)
                                     * and (const unsigned char*). They are implicitly cast to (void*). The memory is
                                     * packed because it is uint8_t and unsigned char so there should be no problem to copy.*/
                    MEMCPY( &(*poGetAllBufferWithLength->paru8Buffer)[poGetAllBufferWithLength->u32Length]
                        , Bap_oPars.pData
                        , Bap_oPars.u32Length );
                    /*lint +e9087*/

                    /* Laenge der aktuellen Nachricht zur Gesamtnachricht hinzufuegen */
                    poGetAllBufferWithLength->u32Length = poGetAllBufferWithLength->u32Length + Bap_oPars.u32Length;
                }
                else
                { /* bei fixer Laenge steht diese im ROM */
                    Bap_oPars.u32Length = BAP_BusIndTxTable[Bap_oPars.poFctRomRow->u16BusTxTableIndex].u32BufferSize;

                    /* Daten kopieren */
                    /*lint -e9087*/ /* MISRA_2012_REQ_11.3 : 1st and 2nd arguments of MEMCPY are of types (uint8_t*)
                                     * and (const unsigned char*). They are implicitly cast to (void*). The memory is
                                     * packed because it is uint8_t and unsigned char so there should be no problem to copy.*/
                    MEMCPY( &(*poGetAllBufferWithLength->paru8Buffer)[poGetAllBufferWithLength->u32Length]
                        , Bap_oPars.pData
                        , Bap_oPars.u32Length );
                    /*lint +e9087*/

                    /* Laenge der aktuellen Nachricht zur Gesamtnachricht hinzufuegen */
                    poGetAllBufferWithLength->u32Length = poGetAllBufferWithLength->u32Length + Bap_oPars.u32Length;
                }
            }
            else /* falls kein Sendepuffer fuer GetAll, dann nutze Einzelbeantwortung */
#endif /* BAP_USES_STATUS_ALL */
            {
                /* ja, dann ResendWithOpCode, Aufruf von GeneralSend vermeidet Rekursion */
                BAP_BCL_GeneralSend(&Bap_oPars, BapSendType_ResendWithOpcode);
            }
        }
        else
        {
            /* Diese Funktion nicht versenden */
        }
        /* Schiebe Masken-Bit um eine Stelle nach rechts */
        u8FctIdMask /= (uint8_t) 2u;
    }

    /*lint +esym(613, apoPars) */
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* #ifdef BAP_FSG */


/* Definition (Implementierung) von globalen Funktionen */

#if defined (BAP_ASG) || defined(WIRD_NIE_GEBRAUCHT)
/*  Diese Funktion ist in bap_bcl.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_BCL_AbortSend(BapInternalParameters_cpot apoPars)
{
    /*lint -esym(613,apoPars) */
    BAP_BCL_GeneralSend(apoPars, BapSendType_Abort);
    return;
    /*lint +esym(613,apoPars) */
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* #if defined (BAP_ASG) || defined(WIRD_NIE_GEBRAUCHT)  */


#ifdef BAP_FSG
/*  Diese Funktion ist in bap_bcl.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_BCL_SendError(BapInternalParameters_cpot apoPars)
{
    /*lint -esym(613,apoPars) */
    BAP_BCL_GeneralSend(apoPars, BapSendType_SendError);
    return;
    /*lint +esym(613,apoPars) */
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* #ifdef BAP_FSG */


/*  Diese Funktion ist in bap_bcl.h dokumentiert */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_BCL_Send(BapInternalParameters_cpot apoPars)
{
    /*lint -esym(613,apoPars) */
    BAP_BCL_GeneralSend(apoPars, BapSendType_Send);
    return;
    /*lint +esym(613,apoPars) */
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


#ifdef BAP_ASG
/*  Diese Funktion ist in bap_bcl.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_BCL_Resend(BapInternalParameters_cpot apoPars)
{
    /*lint -esym(613,apoPars) */
    BAP_BCL_GeneralSend(apoPars, BapSendType_Resend);
    return;
    /*lint +esym(613,apoPars) */
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* #ifdef BAP_ASG */


#ifdef BAP_FSG
/*  Diese Funktion ist in bap_bcl.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_BCL_ResendWithOpCode(BapInternalParameters_cpot apoPars)
{
    /*lint -esym(613,apoPars) */
	/* MISRA_2012_REQ_10.5 : no risk arise because BAP_FCTID_GETALL is already cast at definition and fit in enum. */
    if ((fctId_t)BAP_FCTID_GETALL == (fctId_t)apoPars->fctId)
    {
        /* Sonderbehandlung fuer Funktionsklasse Cache */
        BAP_BCL_SendStatusAll(apoPars);
    }
    else
    {
        BAP_BCL_GeneralSend(apoPars, BapSendType_ResendWithOpcode);
    }
    return;
    /*lint +esym(613,apoPars) */
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* #ifdef BAP_FSG */


#ifdef BAP_FSG
/*  Diese Funktion ist in bap_bcl.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_BCL_BufferSet(BapInternalParameters_cpot apoPars)
{
    /*lint -esym(613,apoPars) */
    BAP_BCL_GeneralSend(apoPars, BapSendType_BufferSet);
    return;
    /*lint +esym(613,apoPars) */
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* #ifdef BAP_FSG */


/*  Diese Funktion ist in bap_bcl.h dokumentiert */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_BCL_Init(BapLsgRomRow_pot apoLsgRomRow)
{
    /*lint -esym(613,apoLsgRomRow)*/
    BAP_ASSERT(NULL != apoLsgRomRow);

    /* Initialisierung aller dem LSG gehoerenden BCL RAM Bereiche */
    BAP_BCL_InitLsgRamAreas(apoLsgRomRow);
    /* Initialisierung des Vector CAN Treibers fuer den BAP Tx Pfad */
    BAP_BCL_InitCanDrvTxCfmFlags(apoLsgRomRow);
    /* Initialisierung des Tx-Send-Buffers */
    BAP_BCL_CanTxBufferInit(apoLsgRomRow);

    return;
    /*lint +esym(613,apoLsgRomRow)*/
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>

#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_IMPL_FAR DBGVAR void
BAP_BCL_Shutdown(BapLsgRomRow_pot apoLsgRomRow)
{
    BAP_BCL_Init(apoLsgRomRow);
    return;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


/*  Diese Funktion ist in bap_bcl.h dokumentiert */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_IMPL_FAR BapError_et
BAP_BCL_Start(BapLsgRomRow_pot apoLsgRomRow)
{
    DBGVAR BapError_et eResult = BapErr_OK;
#ifdef BAP_FSG
    DBGVAR uint8_t u8FctRomRowIdx;
    DBGVAR uint8_t u8BusTxIdx;

    /*lint -esym(613,apoLsgRomRow)*/
    BAP_ASSERT(NULL != apoLsgRomRow);

#if defined(BAP_ASG) && defined(BAP_FSG)
    if (BapSG_FSG == apoLsgRomRow->eSGType)
#endif /* defined(BAP_ASG) && defined(BAP_FSG) */
    {
        /* Teste, ob alle Sendepuffer initialisiert sind */
        for (u8FctRomRowIdx=(uint8_t)0; (u8FctRomRowIdx<apoLsgRomRow->u8FctRomTableSize) && (BapErr_OK == eResult); u8FctRomRowIdx++)
        {
            BapFctRomRow_pot poFctRomRow = &BAP_FctRomTables[apoLsgRomRow->u16FctRomIndex + u8FctRomRowIdx];

            for(u8BusTxIdx=(uint8_t)0; u8BusTxIdx<poFctRomRow->u8TxTableSize; u8BusTxIdx++)
            {
                BapBusIndirectionTxRomRow_pot  const poBusTxRow = &(BAP_BusIndTxTable[poFctRomRow->u16BusTxTableIndex + (uint16_t)u8BusTxIdx]);
                if (/* Nur falls Werte versendet werden koennen ist eine Initialisierung erforderlich */
                        ( poBusTxRow->u32BufferSize > (uint32_t)0)
                        /* Nur Properties muessen vorbelegt werden */
                        && (BapFctCls_Property == poFctRomRow->eFunctionClass)
                        /* Wert nicht initialisiert? */
                        && (BAP_FALSE == (bool_t)poBusTxRow->poBclTxRamRow->flags.fTxInitializedFlag )
                        /* Funktion muss in Funktionsliste sein */
                        && ((uint8_t)0 != (apoLsgRomRow->poLsgRamRow->BAP_aru8FunctionList[BAP_BINARY_ID(poFctRomRow->fctId) / BAP_BYTE] & (BAP_BIT7 >> (BAP_BINARY_ID(poFctRomRow->fctId) % BAP_BYTE))))
                )
                {
                    eResult = BapErr_SendBufferNotInitialized;
                }
            }
        }
    }
#endif /* #ifdef BAP_FSG */

    return eResult;
    /*lint +esym(613,apoLsgRomRow)*/

}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


/*  Diese Funktion ist in bap_bcl.h dokumentiert */
#define BAP_START_SEC_CODE_CYCLIC
#include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_BCL_TaskSend(void)
{
    /* Verwalte die Inhibit Timer */
    BAP_BCL_InhibitTimerTask();

    /* Aufruf CAN Sende Task */
#ifdef BAP_RUNTIME_TEST
    BAP_RUNTIME_TEST_CANSENDTASK_START();
#endif /* BAP_RUNTIME_TEST */ 

    BAP_BCL_CanSendTask();

#ifdef BAP_RUNTIME_TEST
    BAP_RUNTIME_TEST_CANSENDTASK_STOP();
#endif /* BAP_RUNTIME_TEST */ 

    return;
}
#define BAP_STOP_SEC_CODE_CYCLIC
#include <BAP_MemMap.h>


/*  Diese Funktion ist in bap_bcl.h dokumentiert */
#define BAP_START_SEC_CODE_CYCLIC
#include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_BCL_ReadRingbuffer(void)
{
    /* Hole die Daten aus den Ringpuffern ab */
    BAP_BCL_CanReceiveTask();

    return;
}
#define BAP_STOP_SEC_CODE_CYCLIC
#include <BAP_MemMap.h>


#ifdef BAP_USES_SEGMENTATION
/*  Diese Funktion ist in bap_bcl.h dokumentiert */
#   define BAP_START_SEC_CODE_CYCLIC
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_BCL_TaskRxNotify(void)
{
    DBGVAR uint8_t u8LsgRomRowIdx;

    BAP_InitInternalParameters(&Bap_oPars);

    Bap_oPars.eOpCode = BapOp_Invalid;
    Bap_oPars.pData = NULL;
    Bap_oPars.u32Length = (uint32_t)0;

    /* Verwalte die InterTelegram Timer */
    BAP_BCL_InterTelegramTimerTask();

    /* Fuer alle Lsgs: Durchsuche, ob in deren BCL Puffern vollstaendig
     * empfangene Datenelemente oder Fehlerwerte enthalten sind
     */
    for ( u8LsgRomRowIdx = (uint8_t)0; u8LsgRomRowIdx < BAP_P_LSG_ROM_TABLE_ROWS; u8LsgRomRowIdx++)
    {
        DBGVAR uint8_t u8FctRomRowIdx;
        DBGVAR uint8_t u8FctRomTableSize;

        Bap_oPars.poLsgRomRow = BAP_pLsgRomTable[u8LsgRomRowIdx];
        Bap_oPars.lsgId = Bap_oPars.poLsgRomRow->lsgId;
        u8FctRomTableSize = Bap_oPars.poLsgRomRow->u8FctRomTableSize;


#ifdef BAP_TASKTIME_LIMIT
        if ( ( ((bitfield_t) 1u) == Bap_oPars.poLsgRomRow->poLsgRamRow->fState.fRxFlag)
            && (BAP_u32TaskTimeCounter< (uint32_t)BAP_MAX_TASK_TIME)
           )
#endif /* #ifdef BAP_TASKTIME_LIMIT */
        {
#ifdef BAP_TASKTIME_LIMIT
            Bap_oPars.poLsgRomRow->poLsgRamRow->fState.fRxFlag = BAP_FALSE;
#endif /* #ifdef BAP_TASKTIME_LIMIT */

            for (u8FctRomRowIdx = (uint8_t)0;
#ifdef BAP_TASKTIME_LIMIT
                 (BAP_u32TaskTimeCounter< (uint32_t)BAP_MAX_TASK_TIME) &&
#endif /* #ifdef BAP_TASKTIME_LIMIT */
                 (u8FctRomRowIdx < u8FctRomTableSize);
                 u8FctRomRowIdx++)
            {
                Bap_oPars.poFctRomRow = &BAP_FctRomTables[Bap_oPars.poLsgRomRow->u16FctRomIndex + u8FctRomRowIdx];
                Bap_oPars.fctId = Bap_oPars.poFctRomRow->fctId;

                BAP_BCL_SingleRxNotify(&Bap_oPars);
            }
        }
    }
#ifdef BAP_TASKTIME_LIMIT
    if (BAP_u32TaskTimeCounter>= (uint32_t)BAP_MAX_TASK_TIME)
    {
        BAP_DBG_TaskTimeLimitEvent();
    }
#endif /* #ifdef BAP_TASKTIME_LIMIT */
    return;
}
#   define BAP_STOP_SEC_CODE_CYCLIC
#   include <BAP_MemMap.h>
#endif /* #ifdef BAP_USES_SEGMENTATION */
