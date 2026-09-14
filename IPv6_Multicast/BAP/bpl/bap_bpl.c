/******************************************************************
 *
 *     Copyright (c) 2004-2023 Volkswagen AG, D-38436 Wolfsburg
 *
 ******************************************************************
 *
 * Projekt:    BAP
 * Komponente: BPL
 * BAP Version: 1.12.2
 *
 ******************************************************************
 *
 * Beschreibung
 *
 *  Diese Datei enthaelt die Implementierung der BPL Schicht im BAP
 *  Projekt.
 *
 *  Diese C-Datei enthaelt nicht die Funktionen BAP_BPL_DataReceived
 *  und BAP_BPL_ErrorIndication, da diese von der BAL Schicht
 *  implementiert wird.
 *
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
 * 2021-03-12	1.11.3		JEO			[SSWPPB-142] Fix MISRA violations.
 * 2021-03-01	1.11.3		JEO			[SSWPPB-142] Improve jutification of Pc-Lint deac or MISRA rules violation.
 * 2020-02-24	1.11.3		JEO			[SSWPPB-142] Removed "To do" comment.
 * 2019-06		1.11.1		KUL			[SSWCCB-1302] bOngoingStatusAll flag introduced for each LSG instead of a single global
 * 2019-06		1.10.99		FFS			[SSWCCB-1302] Introduction of bOngoingStatusAll to manage the influence of heartbeats on the retryTimer of Fct1. Read section 5.6 in the protocol specification.
 * 2019-05-23	1.10.99		FFS			[SSWPPB-20]   Taking into account BapErr_BadDataLength to trigger the retry mechanism.
 * 2018-07-19	1.10.3		FFS			[SSWCCB-2522] Misra-2012 fix (release was postponed)
 * 2017-03-03	1.9.0 		FST			[SSWCCB-1545] SSW-Lokatierungs-Pragmas eingefuegt
 * 2014-11-28	1.8.0		FST			[SSWCCB-2105] Formataenderung der Variablen 16Bit->32Bit
 * 2014-03-24	1.7.1		WWU			Anpassung fuer MISAR-2004 Fix: Funktion-Like Makros fuer BAP_BPL_Start sind entfernt.
 * 2013-02-06	1.7.0		WWU			Funktionsname Umbenannt, wegen Misra : Identifier exceeds 31 characters
 * 2013-01-30	1.7			WWU			MISRA-2004 fix
 * 2012-10-15	1.6.5.1		WWU			Korrektur der Misra-98 Abweichungen
 * 2012-09-18	1.6.5		WWU			Codepflegen wegen zyklomatischer Komplexitaet. BAP_BPL_Send() in ASG und FSG geteilt.
 * 										neue Funktionen: BAP_BPL_Send_ASG() und BAP_BPL_Send_FSG()
 * 2011-03-24   1.6         ALI         Der Start der Heartbeat Ueberwachung darf nur erfolgen, wenn der Zustand BapLayerLsgStat_Running ist
 * 2007-09-07   1.5         RVE         Retry wird auch beim Erhalt eines StatusAck abgestelt.
 * 2007-08-21   1.5         ALI         Parameteruebergabe in BAP_BPL_AbortSend geaendert
 * 2006-06-02   1.4         ALA         Unterstuetzung von Bap_Acknowledge
 * 2006-04-12   1.4         ALA         Unterstuetzung fuer BAP_ROM_DATA_FAR.
 * 2006-04-12   1.4         ALA         Optimierung der Task-Laufzeit (HB-Monitoring)
 * 2006-04-12   1.4         ALA         Unterstuetzung fuer neue HB-Trigger.
 * 2006-03-14   1.4         ALA         Bugfix: BCL Fehler wurden im FSG unterdrueckt, wenn Processing-Timer aktiv war
 * 2005-10-24   1.3.1.2     ALA         const vor void Rueckgabetyp entfernt.
 * 2005-07-20   1.3.1       ALA         Bugfix: Kein erneutes Aussenden von Get, SetGet, StartResult, wenn Busy,
 *                                      doppeltes Abort entfernt.
 * 2005-04-13   1.3         CRI         StopRetries werden nun auch fuer FSG durchgefuehrt bei Init
 * 2005-04-13   1.3         ALA         Optimierung der Datenstrukturen. HB-TO Meldung nun auf Funktion 4.
 * 2005-04-10   1.3         CRI         Hinzufuegen von 2 Fkt. zur Zeitueberwachung im FSG
 * 2005-04-10   1.3         CRI         Erweitern von UpdateRetryOnOpcode, Send, SendError um Methoden
 * 2005-04-05   1.3         ALA         BapErr_Busy, falls Retry-Timeout auftritt ohne dass der Request bereits versendet wurde.
 * 2005-03-14   1.2.1       CRI         BCL_Start wird wieder aufgerufen
 * 2004-11-22   1.2         JOK         BapOp_MethAbortResultNoBusy wieder raus, da Processing und Ueberwachung von
 *                                      Anwendung gemacht wird.
 * 2004-11-17   1.2         JOK         Interruptsperre in BAP_BPL_TaskRetryMonitoringFct() eingebaut
 * 2004-11-17   1.2         JOK         Funktion BAP_BPL_RetryAnswered() ausgegliedert
 * 2004-11-17   1.2         JOK         Globale Variable gu16HeartbeatTimerValue in LsgRam-Bereich uebernommen
 * 2004-11-04   1.2         ALA         BAP_BPL_SendError Funktion hinzugefuegt.
 * 2004-09-08   1.2         JOK         BapOp_MethAbortResult wird intern mit BapOp_MethAbortResultNoBusy verarbeitet
 *                                      damit ein AbortResult nach StartResult moeglich ist.
 * 2004-09-08   1.2         JOK         FktKlasse-Methode Aufrufe werden mittels Retry ueberwacht. Keine spezielle
 *                                      Ueberpruefung ob Start/Abort gerade laeuft.
 * 2004-09-03   1.2         JOK         Interne OpCodes werden nicht mehr an den BAL weitergegeben und
 *                                      fuehren damit nicht mehr zu einer Fehlermeldung in der Diagnose-Botschaft
 * 2004-09-03   1.2         JOK         Verarbeitung der HB-Meldung im ASG als Funktion extrahiert und
 *                                      nun auch vom BAL nutzbar
 * 2004-06-07   1.1         JOK         Compilerschalter fuer SG-Typen zur Optimierung
 *                                      des ROM-Bedarfs eingefuegt
 * 2004-06-07   1.1         JOK         Konfigurierte HB-Zeit ist in 100ms angegeben. Der BPL
 *                                      rechnet diese Zeit in Anzahl Task-Aufrufe fuer die
 *                                      interne Timerbehandlung um.
 * 2004-06-07   1.1         JOK         Beachtung des Sonderfalls von HB-Zeit 0 im FSG bedeutet
 *                                      kein HB-Mechanismus im FSG
 * 2004-06-07   1.1         JOK         Beachtung des Sonderfalls von HB-Faktor 0 im ASG bedeutet
 *                                      keine HB-Ueberwachung des FSG im ASG.
 * 2004-06-07   1.1         JOK         Globale Variable gu16HeartbeatTimerValue eingefuegt
 * 2004-06-07   1.1         JOK         Funktion BAP_BPL_TaskRetryMonitoringLsg() in
 *                                      BAP_BPL_TaskRetryMonitoringFct() umbenannt
 * 2004-06-07   1.1         JOK         Enumeration BapDir_Sink/Source entfernt
 * 2004-06-07   1.1         JOK         Funktion BAP_BPL_Shutdown() entfernt (siehe bap_bpl.h)
 ******************************************************************/

/* Systemincludes mit <...> */

/* Bibliotheken von externen Herstellen mit <...> */

/* Eigene Header-Dateien "..." */
#include "bap_bpl.h"
#include "bap_bplconfig.h"
#include "bap_bplutil.h"
#include "bap_util.h"
#include "bap_bcl.h"    /* darunterliegende Schicht */
#include "bap_debug.h"
#include "bap_balutil.h"
#include "bap_balconfig.h"

/* Externe globale Variablen-Definitionen */

#ifdef BAP_FSG
/* Funktionszeiger mit Namen BAP_BPL_BufferSet,
   der auf BAP_BCL_BufferSet zeigt */
/*lint -e546 */ /* LINT is overly correct here - that's the only way to be MISRA rule 16.9 compliant, see MISRA bulletin board www.misra.org.uk/forum/viewtopic.php?f=76&t=1208 */
#   define BAP_START_SEC_CONST_UNSPECIFIED
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void (* const BAP_BPL_BufferSet)
    (BapInternalParameters_cpot apoPars) = &BAP_BCL_BufferSet;
#   define BAP_STOP_SEC_CONST_UNSPECIFIED
#   include <BAP_MemMap.h>
#endif /* #ifdef BAP_FSG */
 /*lint +e546 */

/* Heartbeats have a different impact on the retry timer of Fct1 depending on whether FSG uses segmentation or not. See SSWCCB1302. */
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>

/* Interne Makro-Definitionen */

/* Interne Typ-Definitionen */

/* Interne Const Deklarationen */

/* Interne statische Variablen */

/* Vorwaerts-Deklarationen von statischen Funktionen */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>

#ifdef BAP_ASG
BAP_STATIC BAP_IMPL_FAR void
BAP_BPL_DoRetry(BapBplRamRow_pot apoBplRamRow, BapInternalParameters_cpot apoPars);
#endif /* #ifdef BAP_ASG */

#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>
#define BAP_START_SEC_CODE_CYCLIC
#include <BAP_MemMap.h>

#ifdef BAP_ASG
static BAP_IMPL_FAR void
BAP_BPL_TaskRetryMonitoringFct(BapInternalParameters_cpot apoPars);
#endif /* #ifdef BAP_ASG */

#define BAP_STOP_SEC_CODE_CYCLIC
#include <BAP_MemMap.h>
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>

#ifdef BAP_ASG
BAP_STATIC BAP_IMPL_FAR void
BAP_BPL_UpdGetAllRetryOnOpCode(BapInternalParameters_cpot apoPars);
#endif /* #ifdef BAP_ASG */

#ifdef BAP_ASG
static BAP_IMPL_FAR void
BAP_BPL_UpdateRetryOnOpCode(BapFctRomRow_pot apoFctRomRow
    , DBGVAR BapOpCodes_et aeOpCode);
#endif /* #ifdef BAP_ASG */

#ifdef BAP_FSG
#ifdef BAP_USES_METHODS
static BAP_IMPL_FAR void
BAP_BPL_UpdProcessDispatching(BapFctRomRow_pot apoFctRomRow
    , DBGVAR BapOpCodes_et aeOpCode);
#endif /* #ifdef BAP_USES_METHODS */
#endif /* #ifdef BAP_FSG */

#ifdef BAP_ASG
static BAP_IMPL_FAR void
BAP_BPL_RetryAnswered(DBGVAR lsgId_t aLsgId
    , BapBplRamRow_pot apoBplRamRow);
#endif /* #ifdef BAP_ASG */

#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>

/* Definition (Implementierung) von statischen Funktionen */

#ifdef BAP_ASG
/**
 *  Fuehrt ein Retry durch (Retry-Timer ist abgelaufen) wenn noch ein Retry
 *  durchzufuehren ist oder meldet ein BapErr_RetryNotSuccessful oder BapErr_RequestTimeout
 *  an die Applikation.
 *
 *  @param apoPars -\>poLsgRomRow Zeiger auf die Rom-Zeile des Lsg, wo das Retry-Monitoring durchgefuehrt werden soll.<br>
 *                 -\>lsgId bezeichnet das logische Steuergeraet.<br>
 *                 -\>poFctRomRow Zeiger auf die Rom-Zeile der Funktion, wo das Retry-Monitoring durchgefuehrt werden soll.<br>
 *                 -\>fctId bezeichnet die Funktion des angegebenen logischen Steuergeraetes.<br>
 *                 -\>pData muss mit NULL vorbesetzt worden sein <br>
 *                 -\>u16Length muss mit 0 vorbesetzt worden sein <br>
 *                 -\>eOpCode muss mit BapOp_Invalid vorbesetzt worden sein
 *
 *  @param apoBplRamRow muss apoPars->poFctRomRow->poBplRamRow entsprechen.
 *
 *  @remarks
 *  Die Parameter duerfen nicht NULL sein.
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_STATIC BAP_IMPL_FAR void
BAP_BPL_DoRetry(BapBplRamRow_pot apoBplRamRow, BapInternalParameters_cpot apoPars)
{
    /*lint -esym(613, apoBplRamRow) */
    BAP_ASSERT(NULL != apoBplRamRow);
    /*lint -esym(613, apoPars) */
    BAP_ASSERT(NULL != apoPars);
	
	/* If a Retry is asked for Fct1, it means that in all case the desired transmission from FSG is not happening. */
	if((fctId_t)BAP_FCTID_GETALL==(fctId_t)apoPars->fctId)
	{
		apoBplRamRow->bOngoingStatusAll=BAP_FALSE;
	}

    if((bitfield_t)0 != apoBplRamRow->fRetryOrProcessingFlags.u6RetryCounter) /* Ist Counter noch nicht abgelaufen?*/
    {
        /* Timer fuer naechsten Retry wieder auf ROMWert hochsetzen */
        apoBplRamRow->u16RetryOrProcessingTimer = apoPars->poFctRomRow->nMaxRetryOrProcessingTime;

        /* Retry-Anzahl dekrementieren */
        apoBplRamRow->fRetryOrProcessingFlags.u6RetryCounter
            = (apoBplRamRow->fRetryOrProcessingFlags.u6RetryCounter - 1u); /* -- geht nicht wegen CVI Compiler */

        /* Retry durchfuehren */
        BAP_BCL_Resend(apoPars);

        BAP_DBG_RetryProvokedEvent(apoPars->lsgId);
    }
    else
    {
        /*Jetzt sind alle Retry's verstrichen*/
        /*Dieses Send ist schief gegangen - also nicht mehr versuchen */
        apoBplRamRow->u16RetryOrProcessingTimer=(uint16_t)0;

        apoBplRamRow->fRetryOrProcessingFlags.bRetryOrProcessingActive = BAP_FALSE;   /* Retry ausschalten */

        if ((bitfield_t) 1u == apoBplRamRow->fRetryOrProcessingFlags.bRequestSent)
        {
            /* Falls Request versendet wurde */

            /* uebergeordnete Schicht informieren! */
            BAP_BPL_ErrorIndication(apoPars->lsgId
                , apoPars->fctId
                , BapErr_RetryNotSuccessful
            );

            BAP_DBG_RetryTimeoutError(apoPars->lsgId);
        }
        else
        {
            /* Falls Request nicht gesendet werden konnte */

            /* uebergeordnete Schicht informieren! */
            BAP_BPL_ErrorIndication(apoPars->lsgId
                , apoPars->fctId
                , BapErr_RequestTimeout
            );

            BAP_DBG_RequestTimeoutError(apoPars->lsgId);
        }

        /* Sendevorgang abbrechen */
        BAP_BCL_AbortSend(apoPars);
    }
    /*lint +esym(613, apoBplRamRow) */
    /*lint +esym(613, apoPars) */
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif  /* #ifdef BAP_ASG */


#ifdef BAP_ASG
/**
 *  Fuehrt das RetryMonitoring fuer eine FctId durch (wg. max. Schachtelungstiefe in eigene Funktion ausgeglieder)
 *
 *  @param apoPars -\>poLsgRomRow Zeiger auf die Rom-Zeile des Lsg, wo das Retry-Monitoring durchgefuehrt werden soll.<br>
 *                 -\>lsgId bezeichnet das logische Steuergeraet.<br>
 *                 -\>poFctRomRow Zeiger auf die Rom-Zeile der Funktion, wo das Retry-Monitoring durchgefuehrt werden soll.<br>
 *                 -\>fctId bezeichnet die Funktion des angegebenen logischen Steuergeraetes.<br>
 *                 -\>pData muss mit NULL vorbesetzt worden sein <br>
 *                 -\>u16Length muss mit 0 vorbesetzt worden sein <br>
 *                 -\>eOpCode muss mit BapOp_Invalid vorbesetzt worden sein
 *
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
static BAP_IMPL_FAR void
BAP_BPL_TaskRetryMonitoringFct(BapInternalParameters_cpot apoPars)
{
    BapBplRamRow_pot poBplRamRow;
    /* interne Hilfsfunktion */

    /*lint -esym(613, apoPars)*/
    BAP_ASSERT( apoPars != NULL );
    BAP_ASSERT( apoPars->pData == NULL );
    BAP_ASSERT( apoPars->eOpCode == BapOp_Invalid );
    BAP_ASSERT( apoPars->poLsgRomRow != NULL );
    BAP_ASSERT( apoPars->poFctRomRow != NULL );
    BAP_ASSERT( apoPars->poFctRomRow->fctId == apoPars->fctId );
    BAP_ASSERT( apoPars->poLsgRomRow->lsgId == apoPars->lsgId );

    poBplRamRow = apoPars->poFctRomRow->poBplRamRow;

    /* RamTabelle existiert (=> Retry ist moeglich) und der Retry ist aktiv, d.h. noch keine Antwort gekommen. */
    if( (NULL !=poBplRamRow) &&  ((bitfield_t) 1u == poBplRamRow->fRetryOrProcessingFlags.bRetryOrProcessingActive) )
    {
        /* Ist Timer abgelaufen? */
        switch (poBplRamRow->u16RetryOrProcessingTimer)
        {
            case 0:
                /* 0 bedeutet, dass der Retry-Timer gestoppt wurde (StartMsg empfangen),
                 * dann warte auf Antwort oder Intertelegrammzeit- oder Segmentierungsfehler
                 * (= an dieser Stelle nichts zu tun).
                 */
                break;
            case 1:
                /* 1 bedeutet, dass der Retry-Timer abgelaufen ist */
                BAP_BPL_DoRetry(poBplRamRow, apoPars);
                break;
            default:
                --poBplRamRow->u16RetryOrProcessingTimer;
                break;
        }
        /* Retry-Ueberwachung des Lsgs eingeschaltet lassen */
        apoPars->poLsgRomRow->poLsgRamRow->fState.fRetryProcessingActive = BAP_TRUE;
    }

    /*lint +esym(613, apoPars)*/
    return;
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* #ifdef BAP_ASG */



#ifdef BAP_ASG
/**
 *  Schaltet den Retry-Timer aus und aktualisiert die Diagnose-Bits.
 *
 *  @param aLsgId bezeichnet das logische Steuergeraet
 *
 *  @param *apoBplRamRow zeigt auf die Retry-Informationen.
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
static BAP_IMPL_FAR void
BAP_BPL_RetryAnswered(DBGVAR lsgId_t aLsgId
    , BapBplRamRow_pot apoBplRamRow)
{
    /* interne Hilfsfunktion */
    /*lint -esym(613,apoBplRamRow) */
    BAP_ASSERT(NULL != apoBplRamRow);

    if ((bitfield_t) 1u == apoBplRamRow->fRetryOrProcessingFlags.bRetryOrProcessingActive)
    {
        BAP_DBG_RetryAnsweredEvent(aLsgId);
        apoBplRamRow->u16RetryOrProcessingTimer = (uint16_t)0;
        apoBplRamRow->fRetryOrProcessingFlags.u6RetryCounter = (uint8_t)0;
        apoBplRamRow->fRetryOrProcessingFlags.bRetryOrProcessingActive = BAP_FALSE;
    }
    return;
    /*lint +esym(613,apoBplRamRow) */
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* #ifdef BAP_ASG */


#ifdef BAP_ASG
/**
 *  Retriggert den Retry-Timer von GetAll bei Beantwortung durch einzelne HB-Status-Nachrichten
 *
 *  @param apoPars
 *      -\>poFctRomRow Funktion, auf den sich der OpCode bezieht (falls HB-Status-Nachricht)
 *      -\> eOpCode Der OpCode, der ausgewertet werden soll.
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_STATIC BAP_IMPL_FAR void
BAP_BPL_UpdGetAllRetryOnOpCode(BapInternalParameters_cpot apoPars)
{
    /*lint -esym(613,apoPars) */
    BAP_ASSERT(NULL != apoPars);

    /* war es ein Heartbeat-Status? */
    if ( (BapOp_PropHeartbeatStatus == apoPars->eOpCode) && (BapFctCls_Property == apoPars->poFctRomRow->eFunctionClass))
    {
        BapBplRamRow_pot poBplRamRowGetAll;
        /*lint -e9034*/ /*MISRA_2012_REQ_10.3 : Warning deactivated. Refers to bap_types.h, definition of BAP_FCTID_GETALL
         * no risk arise because  BAP_FCTID_GETALL is never below 0 and then fit in enum */
        BapFctRomRow_pot poFctRomRowGetAll = BAP_GetLsgFctRomRow(apoPars->poLsgRomRow, BAP_FCTID_GETALL);
        /*lint +e9034*/
        /* Retriggern von GetAll, falls bei GetAll gerade die Retry-Ueberwachung laueft */

        if (NULL != poFctRomRowGetAll)  /* Falls GetAll-FctId vorhanden */
        {
            poBplRamRowGetAll = poFctRomRowGetAll->poBplRamRow;
        }
        else
        {
            poBplRamRowGetAll = NULL;
        }

        if ( (NULL != poBplRamRowGetAll)   /* Falls Retry-Ueberwachung bei GetAll konfiguriert */
            && ( (bitfield_t) 1u == poBplRamRowGetAll->fRetryOrProcessingFlags.bRetryOrProcessingActive ) /* und gerade aktiv */
		    && (BAP_FALSE == poBplRamRowGetAll->bOngoingStatusAll)) /* If there is an ongoing status all on the LSG, don't update timer */
        {
            /*lint -esym(613,poFctRomRowGetAll) *//* Zweig wird nie erreicht wenn poFctRomRowGetAll == NULL */
            poBplRamRowGetAll->u16RetryOrProcessingTimer = poFctRomRowGetAll->nMaxRetryOrProcessingTime;
            /*line +esym(613,poFctRomRowGetAll) */
        }
    }
    /*lint +esym(613,apoPars) */
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif  /* #ifdef BAP_ASG */

#ifdef BAP_ASG
/**
 *  Verarbeitet einen OpCode und aktualisiert die Retry-Timer abhaengig vom OpCode.
 *
 *  @param *apoFctRomRow Funktion, auf den sich der OpCode bezieht.
 *
 *  @param aeOpCode Der OpCode, der ausgewertet werden soll.
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
static BAP_IMPL_FAR void
BAP_BPL_UpdateRetryOnOpCode(BapFctRomRow_pot apoFctRomRow
    , DBGVAR BapOpCodes_et aeOpCode)
{
    BapBplRamRow_pot poBplRamRow;

    /* interne Hilfsfunktion */
    /*lint -esym(613,apoFctRomRow) */
    BAP_ASSERT(NULL != apoFctRomRow);

    poBplRamRow = apoFctRomRow->poBplRamRow;

    /* Teste, ob Ram fuer Retry konfiguriert */
    if(NULL != poBplRamRow)
    {
        switch(aeOpCode)
        {
        case BapOp_PropStatus:
        /*case BapOp_ArrStatus:*/   /* gleicher numerischer Wert */
        /*case BapOp_MethResult:*/   /* gleicher numerischer Wert */
        case BapOp_PropStatusAck:
            /* Stoppen des Retry-timer LAH 1.0 Seite 51*/
            BAP_BPL_RetryAnswered(apoFctRomRow->lsgId, poBplRamRow);
			/* If it is the status of Fct1, the transmission of StatusAll is over. */
			if((fctId_t)BAP_FCTID_GETALL==(fctId_t)apoFctRomRow->fctId)
			{
				poBplRamRow->bOngoingStatusAll=BAP_FALSE;
			}
            break;
#ifdef BAP_USES_SEGMENTATION
        case BapOp_StartMessage:
            /* Beim Erhalt einer segmentierten Nachricht wird die Retry-Zeitueberwachung
               angehalten, da schon ein Teil der Antwort da ist. Der vollstaendige Empfang
               wird ueber den BCL sichergestellt */
            poBplRamRow->u16RetryOrProcessingTimer = (uint16_t)0;
            /* Nicht den Counter zuruecksetzen, Retry bleibt aktiv, aber gestoppt (Timer=0) */
            /* Retry muss ja nach Intertelegrammzeitfehler wieder eingeschaltet werden. */
			/* If it is the startMsg of Fct1, the transmission of StatusAll has just started. */
			if((fctId_t)BAP_FCTID_GETALL==(fctId_t)apoFctRomRow->fctId)
			{
				poBplRamRow->bOngoingStatusAll=BAP_TRUE;
			}
            BAP_DBG_RetryStoppedEvent(apoFctRomRow->lsgId);
            break;
#endif /* #ifdef BAP_USES_SEGMENTATION */
        case BapOp_MessageSent:
            if((bitfield_t) 1u == poBplRamRow->fRetryOrProcessingFlags.bRetryOrProcessingActive)
            {
                /* Request wurde versendet */
                poBplRamRow->fRetryOrProcessingFlags.bRequestSent = BAP_TRUE;
                /*Retriggern des Retry-Timer Seite 52*/
                poBplRamRow->u16RetryOrProcessingTimer = apoFctRomRow->nMaxRetryOrProcessingTime;
                BAP_DBG_RetryRetriggeredEvent(apoFctRomRow->lsgId);
            }
            break;
        case BapOp_PropHeartbeatStatus:
        /* case BapOp_ArrChanged: (gleicher numerischer Wert)*/
        /* case BapOp_MethProcessing: (gleicher numerischer Wert)  */
        /*   --> eigentlich nicht gewollt, aber keine Probleme zu erwarten */

#ifdef BAP_USES_METHODS
            if (BapFctCls_Method == apoFctRomRow->eFunctionClass)
            {
                /* Reset des Counters bei Erhalt eines Processing, damit kein Resend von StartResult */
                poBplRamRow->fRetryOrProcessingFlags.u6RetryCounter = (uint8_t)0;
            }
#endif /* #ifdef BAP_USES_METHODS */

            /*Retriggern des Retry-Timer Seite 52*/
            if( (bitfield_t) 1u == poBplRamRow->fRetryOrProcessingFlags.bRetryOrProcessingActive)
            {
                /* Retriggern Retry-Timer der aktuellen Fct-Id */
                poBplRamRow->u16RetryOrProcessingTimer = apoFctRomRow->nMaxRetryOrProcessingTime;

                BAP_DBG_RetryRetriggeredEvent(apoFctRomRow->lsgId);
            }
            break;
        default:
            /* No Statements */
            break;
        }
    }

    return;
    /* interne Hilfsfunktion */
    /*lint +esym(613,apoFctRomRow) */
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* #ifdef BAP_ASG */


/* Definition (Implementierung) von globalen Funktionen */

#ifdef BAP_FSG
/* Diese Funktion ist in bap_bpl.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_BPL_ResendStatus(BapInternalParameters_cpot apoPars)
{
    BapOpCodes_et eOpCode;

    /*lint -esym(613,apoPars)*/
    BAP_ASSERT(NULL != apoPars);

    /* Der OpCode wird temporaer fuer die Dauer des Funktionsaufrufs geaendert
     * und ansschliessend wieder auf den urspruenglichen Wert zurueckgesetzt.
     * Spart Code, Stackspeicher und Laufzeit
     */
    eOpCode = apoPars->eOpCode;

    /* const_cast<>, temporaeres Aendern des OpCodes */
    /*lint -e960*//* MISRA2004: attempt to cast away const/volatile from a pointer or reference. --> ist aber noetig*/
    /*lint -e9005*/	/* MISRA_2012_REQ_11.8 : cast of a const. This was already checked and accepted for MISRA 2004. Hence, the warning is deactivated.*/
    /*lint -e9087*/	/* MISRA_2012_REQ_11.3 : apoPars of type BapInternalParameters_cpot cast to (void*) then cast to BapInternalParameters_pot.
         	 	 	 * (No memory alignment problem and manually checked)*/
    ((BapInternalParameters_pot)( void*)apoPars)->eOpCode =
            BapOp_PropStatus;  /*lint !e613 */ /* Zeiger kann nicht durch const_cast<> zu NULL werden */
    /*lint +e9087*/
    /*lint +e9005*/
    /*lint +e960*/
    /*lint +esym(960, apoPars)*/

    /* Heartbeat muss immer retriggert werden, da FSG */
    BAP_BPL_RetriggerHeartbeat(apoPars->poLsgRomRow);

    BAP_BCL_ResendWithOpCode(apoPars);

    /* const_cast<>, Wiederherstellen des OpCodes */
    /*lint -e960*/	/* MISRA2004: attempt to cast away const/volatile from a pointer or reference. --> ist aber noetig*/
    /*lint -e9005*/	/* MISRA_2012_REQ_11.8 : cast of a const. This was already checked and accepted for MISRA 2004. Hence, the warning is deactivated.*/
    /*lint -e9087*/	/* MISRA_2012_REQ_11.3 : apoPars of type BapInternalParameters_cpot cast to (void*) then cast to BapInternalParameters_pot.
     	 	 	 	 * (No memory alignment problem and manually checked)*/
    ((BapInternalParameters_pot)( void*)apoPars)->eOpCode =
    		eOpCode; /*lint !e613*/ /* Zeiger kann nicht durch const_cast<> zu NULL werden */
    /*lint +e9087*/
    /*lint +e9005*/
    /*lint +e960*/

    return;
    /*lint +esym(613,apoPars)*/
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* #ifdef BAP_FSG */

#ifdef BAP_ASG
/**
 * ASG Teil in BAP_BPL_Send
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BapError_et BAP_BPL_Send_ASG(BapInternalParameters_cpot apoPars)
{
	BapError_et retErr = BapErr_OK;
    BapBplRamRow_pot poBplRamRow = NULL;

    /* apoPars->poFctRomRow ist nicht NULL. In BAP_BPL_Send geprueft! */
#ifdef BAP_USES_METHODS
    if (NULL != apoPars->poFctRomRow)
    {
        poBplRamRow = apoPars->poFctRomRow->poBplRamRow;
    }
#endif /* #ifdef BAP_USES_METHODS */

    if (NULL != poBplRamRow)
    {
		/* Nur im ASG, pruefen, ob gerade ein Retry laeuft */
		if ((bitfield_t) 1u == poBplRamRow->fRetryOrProcessingFlags.bRetryOrProcessingActive )
		{
#ifdef BAP_USES_METHODS
			/* Nur ein Abort darf waehrend einer laufenden Ueberwachung unterbrechen */
			/* Die vorherige Ueberwachung kann von einem StartResult oder Abort sein */
			if ( (BapFctCls_Method == apoPars->poFctRomRow->eFunctionClass)
				&& (BapOp_MethAbort == apoPars->eOpCode) )
			{
				/* Reset des Timers */
				poBplRamRow->fRetryOrProcessingFlags.u6RetryCounter = apoPars->poFctRomRow->nMaxRetryCounter;
				poBplRamRow->fRetryOrProcessingFlags.bRequestSent = BAP_FALSE;
				poBplRamRow->u16RetryOrProcessingTimer = apoPars->poFctRomRow->nMaxRetryOrProcessingTime;

				BAP_DBG_RetryMntStartedEvent(apoPars->lsgId);
			}
			else
#endif /* BAP_USES_METHODS */
			{
				BAP_DBG_RetryBusyError(apoPars->lsgId);
				/* Der Request darf im Fehlerfall nicht gesendet werden */
				retErr = BapErr_Busy;
			}
		}
		else
		{
			/* Pruefen, ob ein Retry ueberwacht werden muss */
			/* Bedingungen: MaxRetryTimer>0 und richtiger Request und ASG */
			/* Ein Abort ohne dass ein Retry laeuft, darf keinen Timer starten! */
			if( /* (apoPars->poFctRomRow->nMaxRetryOrProcessingTime > 0u)*/
				((BapOp_PropSetGet == apoPars->eOpCode) || (BapOp_PropGet == apoPars->eOpCode))
				/* || (BapOp_ArrSetGet == apoPars->eOpCode) || (BapOp_ArrGet == apoPars->eOpCode)
				   || (BapOp_CacheSetGetAll == apoPars->eOpCode) || (BapOp_CacheGetAll == apoPars->eOpCode)
				   || (BapOp_MethStartResult == apoPars->eOpCode) - OpCodes sind alle gleich, daher kann Pruefung entfallen */
#ifdef BAP_USES_METHODS
				&& (!((BapFctCls_Method == apoPars->poFctRomRow->eFunctionClass) && (BapOp_MethAbort == apoPars->eOpCode)))
#endif /* BAP_USES_METHODS */
				)
			{
				apoPars->poLsgRomRow->poLsgRamRow->fState.fRetryProcessingActive = BAP_TRUE;
				poBplRamRow->fRetryOrProcessingFlags.bRetryOrProcessingActive = BAP_TRUE;
				poBplRamRow->fRetryOrProcessingFlags.u6RetryCounter = apoPars->poFctRomRow->nMaxRetryCounter;
				poBplRamRow->fRetryOrProcessingFlags.bRequestSent = BAP_FALSE;
				poBplRamRow->u16RetryOrProcessingTimer = apoPars->poFctRomRow->nMaxRetryOrProcessingTime;

				BAP_DBG_RetryMntStartedEvent(apoPars->lsgId);
			}
		}
    }


    if(BapErr_OK == retErr)
    {
    	BAP_BCL_Send(apoPars);
    }

return retErr;
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* #ifdef BAP_ASG */

#ifdef BAP_FSG
/**
 * FSG Teil in BAP_BPL_Send
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BapError_et BAP_BPL_Send_FSG(BapInternalParameters_cpot apoPars)
{
#if defined(BAP_USES_METHODS)
    DBGVAR bool_t bIgnoreSending = BAP_FALSE;
    BapBplRamRow_pot poBplRamRow;
#endif /* #if defined(BAP_USES_METHODS) */

	/* Nur im FSG beim Senden den HB retriggern, bei ASG beim Empfang retriggern */
	BAP_BPL_RetriggerHeartbeat(apoPars->poLsgRomRow);

#if defined(BAP_USES_METHODS)
    poBplRamRow = apoPars->poFctRomRow->poBplRamRow;
    if (NULL != poBplRamRow)
    {
		/* Das Senden eines Results deaktiviert Retry */
		/* Das Senden einer Processing resettet ihn wenn aktiv, wenn inaktiv wird Processing ignoriert */
		switch(apoPars->eOpCode)
		{
			case BapOp_MethProcessing:
				/* Ueberwachung aktiv --> kein Result versendet, Processing an BCL leiten */
				if ((bitfield_t) 1u == poBplRamRow->fRetryOrProcessingFlags.bRetryOrProcessingActive)
				{
					poBplRamRow->u16RetryOrProcessingTimer = apoPars->poFctRomRow->nMaxRetryOrProcessingTime;
				}
				else /* Keine Ueberwachung mehr, Processing wird ignoriert und nicht an BCL geleitet */
				{
					bIgnoreSending = BAP_TRUE;
				}
				break;
			case BapOp_MethResult:
				/* Nach Result Ueberwachung deaktivieren */
				poBplRamRow->fRetryOrProcessingFlags.bRetryOrProcessingActive = BAP_FALSE;
				break;
			default:
				/* nichts zu tun */
				break;
		 }
	}
    if(BAP_FALSE == bIgnoreSending)
#endif /* #if defined(BAP_USES_METHODS) */

    {
    	BAP_BCL_Send(apoPars);
    }

return BapErr_OK;
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* #ifdef BAP_FSG */

/* Diese Funktion ist in bap_bpl.h dokumentiert */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_IMPL_FAR DBGVAR BapError_et
BAP_BPL_Send(BapInternalParameters_cpot apoPars)
{
	BapError_et retErr = BapErr_OK;

    /*lint -esym(613,apoPars)*/
    BAP_ASSERT(NULL != apoPars);

    if( (NULL == apoPars->poLsgRomRow) || (NULL == apoPars->poFctRomRow) )
	{
    	retErr = BapErr_InvalidArg;
	}else{
#ifdef BAP_ASG
#if defined(BAP_ASG) && defined(BAP_FSG)
		/* Darf nur im ASG passieren, sonst Problem in FSG Processing */
		if (BapSG_ASG == apoPars->poLsgRomRow->eSGType)
#endif /* defined(BAP_ASG) && defined(BAP_FSG)  */
		{
			retErr = BAP_BPL_Send_ASG(apoPars);
		}
#endif /* #ifdef BAP_ASG */

#ifdef BAP_FSG
#if defined(BAP_ASG) && defined(BAP_FSG)
		/* Darf nur im FSG passieren */
		if (BapSG_FSG == apoPars->poLsgRomRow->eSGType)
#endif /* defined(BAP_ASG) && defined(BAP_FSG)  */
		{
			retErr = BAP_BPL_Send_FSG(apoPars);
		}
#endif /* #ifdef BAP_FSG */
	}

    return retErr;
    /*lint +esym(613,apoPars)*/
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


#if defined (BAP_ASG) || defined(WIRD_NIE_GEBRAUCHT)
/*  Diese Funktion ist in bap_bpl.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_BPL_AbortSend(DBGVAR BapLsgRomRow_pot apoLsgRomRow
    ,DBGVAR fctId_t aFctId)
{
    BapBplRamRow_pot poBplRamRow = NULL;

    /*lint -esym(613,apoLsgRomRow)*/
    BAP_ASSERT(NULL != apoLsgRomRow);

    BAP_InitInternalParameters(&Bap_oPars);
    Bap_oPars.lsgId = apoLsgRomRow->lsgId;
    Bap_oPars.fctId = aFctId;
    Bap_oPars.eOpCode = BapOp_Invalid;
    Bap_oPars.pData = NULL;
    Bap_oPars.u32Length = (uint32_t)0;
    Bap_oPars.poLsgRomRow = apoLsgRomRow;
    Bap_oPars.poFctRomRow = BAP_GetLsgFctRomRow(apoLsgRomRow, aFctId);

    if (NULL != Bap_oPars.poFctRomRow)
    {
        poBplRamRow = Bap_oPars.poFctRomRow->poBplRamRow;
        if (NULL != poBplRamRow)
        {
            /* Loeschen des Sendeauftrags (durch Retry ausgeloest) */
            BAP_BCL_AbortSend(&Bap_oPars);
            /* loeschen der Retryueberwachung */
            poBplRamRow->fRetryOrProcessingFlags.bRetryOrProcessingActive = BAP_FALSE;
        }
    }
    return;
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* #if defined (BAP_ASG) || defined(WIRD_NIE_GEBRAUCHT)  */

#ifdef BAP_FSG
/* Diese Funktion ist in bap_bpl.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR DBGVAR BapError_et
BAP_BPL_SendError(BapInternalParameters_cpot apoPars)
{
    DBGVAR BapError_et  ret;
    BapBplRamRow_pot poBplRamRow;

     /*lint -esym(613,apoPars)*/
    BAP_ASSERT(NULL != apoPars);

    if (NULL != apoPars->poFctRomRow)
    {
        /* retriggert HeartbeatTimer */
        BAP_BCL_SendError(apoPars);

        BAP_BPL_RetriggerHeartbeat(apoPars->poLsgRomRow);

        /* Ein Error einer Methode beendet die Ueberwachung */
        poBplRamRow = apoPars->poFctRomRow->poBplRamRow;
        if (NULL != poBplRamRow)
        {
            poBplRamRow->fRetryOrProcessingFlags.bRetryOrProcessingActive = BAP_FALSE;
        }

        ret = BapErr_OK;
    }
    else
    {
        ret = BapErr_InvalidArg;
    }

    return ret;
    /*lint +esym(613,apoPars)*/
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* #ifdef BAP_FSG */


/* Diese Funktion ist in bap_bpl.h dokumentiert */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_BPL_Init(BapLsgRomRow_pot apoLsgRomRow)
{
    /*lint -esym(613,apoLsgRomRow)*/
    BAP_ASSERT(NULL != apoLsgRomRow);

    /* Zuerst die darunterliegende Schicht anhalten */
    BAP_BCL_Init(apoLsgRomRow);

	/* Stoppen der Heartbeats */
	apoLsgRomRow->poLsgRamRow->eHeartbeatStatus = BapBplStat_Stopped; /* Passt sowohl bei ASG und FSG */
	apoLsgRomRow->poLsgRamRow->u16HeartbeatTimer = (uint16_t)0;

	/* Stoppen der Retries im ASG bzw. Processing_CNF Senden im FSG */
	BAP_BPL_StopRetries(apoLsgRomRow);
	BAP_DBG_SetHeartbeatState(apoLsgRomRow->lsgId, BAP_FALSE); /*lint !e835, !e845*/

	return;
    /*lint +esym(613,apoLsgRomRow)*/
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_BPL_Shutdown(BapLsgRomRow_pot apoLsgRomRow)
{
	BAP_BPL_Init(apoLsgRomRow);
	return;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


/* Diese Funktion ist in bap_bpl.h dokumentiert */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_IMPL_FAR DBGVAR BapError_et
BAP_BPL_Start(BapLsgRomRow_pot apoLsgRomRow)
{
    DBGVAR BapError_et eResult = BapErr_OK;
#ifdef BAP_FSG

    /*lint -esym(613,apoLsgRomRow)*/
    BAP_ASSERT(NULL != apoLsgRomRow);

    /* Zuerst die darunterliegende Schicht starten */
    eResult = BAP_BCL_Start(apoLsgRomRow);
    if (BapErr_OK == eResult)
    {
#if defined(BAP_ASG) && defined(BAP_FSG)
        /* Nur FSG startet HB */
        if (BapSG_FSG == apoLsgRomRow->eSGType)
#endif /* defined(BAP_ASG) && defined(BAP_FSG)  */
        {
            if((uint8_t)0 != apoLsgRomRow->u8Heartbeat)
            {
                /*Starten des HBs*/
                BAP_BPL_InitializeHeartbeat(apoLsgRomRow, (uint8_t) 1);
                BAP_DBG_SetHeartbeatState(apoLsgRomRow->lsgId, BAP_TRUE);
                BAP_BPL_SetNextFctIndex(apoLsgRomRow); /* Fehler darf nicht vorkommen wenn BAPGen verwendet wird */
            }
        }
    }
#endif /* #ifdef BAP_FSG */
    return eResult;
    /*lint +esym(613,apoLsgRomRow)*/
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


#ifdef BAP_ASG
/* Diese Funktion ist in bap_bpl.h dokumentiert
 *
 * Diese Funktion hat 6 ControlNestingLayers (max.4)*/
#   define BAP_START_SEC_CODE_CYCLIC
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_BPL_TaskHeartbeatMonitoring(void)
{
    DBGVAR uint8_t u8LsgIndex = (uint8_t) 0;
    BapLsgRomRow_pot poLsgRomRow = NULL;
    BapLsgRamRow_pot poLsgRamRow = NULL;

    while((u8LsgIndex < BAP_P_LSG_ROM_TABLE_ROWS) )
    {
    	poLsgRomRow=BAP_pLsgRomTable[u8LsgIndex];
        poLsgRamRow = poLsgRomRow->poLsgRamRow;

        if((NULL != poLsgRamRow) && (poLsgRamRow->eLsgStatus == BapLayerLsgStat_Running)) /* In WaitForConfig gibt es kein HB Monitoring */
        {
#if defined(BAP_ASG) && defined(BAP_FSG)
        	if (BapSG_ASG == poLsgRomRow->eSGType)
        	{
#endif /* defined(BAP_ASG) && defined(BAP_FSG)  */
        		if(BapBplStat_OK == poLsgRamRow->eHeartbeatStatus) /* Timer gestartet ?*/
        		{
        			if(poLsgRamRow->u16HeartbeatTimer > (uint16_t)1u) /* noch nicht abgelaufen */
        			{
        				poLsgRamRow->u16HeartbeatTimer--;
        			}
        			else /* HBTimer abgelaufen */
        			{
        				/* jetzt wird der HeartbeatTimer angehalten */
        				poLsgRamRow->eHeartbeatStatus = BapBplStat_Stopped;

        				/* Meldung an uebergeordnete Schicht HeartbeatTimer abgelaufen */
        				/*lint -e9034*/ /*MISRA_2012_REQ_10.3 : Warning deactivated. Refers to bap_types.h, definition of BAP_FCTID_HEARTBEAT
                            * no risk arise because fctid number is never below 0 then fit in enum.*/
        				BAP_BPL_ErrorIndication(poLsgRomRow->lsgId , BAP_FCTID_HEARTBEAT , BapErr_TimeoutHeartbeat);
        				/*lint -e9034*/
        				BAP_DBG_HeartbeatTimeoutError(poLsgRomRow->lsgId);
        			}
        		}
#if defined(BAP_ASG) && defined(BAP_FSG)
        	}
#endif /* defined(BAP_ASG) && defined(BAP_FSG)  */
        }
        ++u8LsgIndex;
    }
    return;
}
#   define BAP_STOP_SEC_CODE_CYCLIC
#   include <BAP_MemMap.h>
#endif /* #ifdef BAP_ASG */


#ifdef BAP_FSG
/* Diese Funktion ist in bap_bpl.h dokumentiert */
#   define BAP_START_SEC_CODE_CYCLIC
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_BPL_TaskHeartbeatDispatcher(void)
{
    DBGVAR uint8_t u8LsgIndex = (uint8_t)0;
    BapLsgRamRow_pot poLsgRamRow = NULL;

    BAP_InitInternalParameters(&Bap_oPars);

    Bap_oPars.eOpCode = BapOp_PropHeartbeatStatus;

    while((u8LsgIndex < BAP_P_LSG_ROM_TABLE_ROWS) )
    {
        Bap_oPars.poLsgRomRow=BAP_pLsgRomTable[u8LsgIndex];

        if((Bap_oPars.poLsgRomRow->u8Heartbeat > (uint8_t)0)
#if defined(BAP_ASG) && defined(BAP_FSG)
            && (BapSG_FSG == Bap_oPars.poLsgRomRow->eSGType)
#endif /* defined(BAP_ASG) && defined(BAP_FSG)  */
            && (Bap_oPars.poLsgRomRow->poLsgRamRow->eLsgStatus == BapLayerLsgStat_Running))
        {
            Bap_oPars.lsgId = Bap_oPars.poLsgRomRow->lsgId;
            poLsgRamRow = Bap_oPars.poLsgRomRow->poLsgRamRow;

            /* Interruptsperre ist hier nicht erforderlich, da beim FSG kein Retriggern im Rx-IRQ */

            if(poLsgRamRow->u16HeartbeatTimer > (uint16_t) 1u) /* noch nicht abgelaufen */
            {
                poLsgRamRow->u16HeartbeatTimer--;
            }
            else /* HBTimer abgelaufen */
            {
                /* Naechstes Element im Heartbeat-Umlauf versenden */
                Bap_oPars.poFctRomRow = &BAP_FctRomTables[Bap_oPars.poLsgRomRow->u16FctRomIndex + poLsgRamRow->u8LastSentFctIndex];
                Bap_oPars.fctId = Bap_oPars.poFctRomRow->fctId;


                /* retriggere HeartbeatTimer */
                BAP_BPL_RetriggerHeartbeat(Bap_oPars.poLsgRomRow);

                BAP_BCL_ResendWithOpCode(&Bap_oPars);

                BAP_DBG_HeartbeatProcessedEvent(Bap_oPars.lsgId);

                BAP_BPL_SetNextFctIndex(Bap_oPars.poLsgRomRow); /*fuer naechste fct vorbereiten*/
            }
        }
        ++u8LsgIndex;
    }
    return;
}
#   define BAP_STOP_SEC_CODE_CYCLIC
#   include <BAP_MemMap.h>
#endif /* #ifdef BAP_FSG */


#ifdef BAP_ASG
/* Diese Funktion ist in bap_bpl.h dokumentiert */
#   define BAP_START_SEC_CODE_CYCLIC
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_BPL_TaskRetryMonitoring(void)
{
    BapLsgRamRow_pot poLsgRamRow;

    DBGVAR uint8_t u8LsgIndex;
    DBGVAR uint8_t u8RomRowIndex;

    BAP_InitInternalParameters(&Bap_oPars);
    Bap_oPars.eOpCode = BapOp_Invalid;
    Bap_oPars.pData = NULL;
    Bap_oPars.u32Length = (uint32_t)0;

    for(u8LsgIndex = (uint8_t)0; u8LsgIndex < BAP_P_LSG_ROM_TABLE_ROWS; ++u8LsgIndex)
    {
        Bap_oPars.poLsgRomRow = BAP_pLsgRomTable[u8LsgIndex];
        Bap_oPars.lsgId = Bap_oPars.poLsgRomRow->lsgId;
        poLsgRamRow = Bap_oPars.poLsgRomRow->poLsgRamRow;

        if(
#if defined(BAP_ASG) && defined(BAP_FSG)
            (BapSG_ASG == Bap_oPars.poLsgRomRow->eSGType) &&
#endif /* defined(BAP_ASG) && defined(BAP_FSG)  */
            ((poLsgRamRow->eLsgStatus == BapLayerLsgStat_Running) ||
                (poLsgRamRow->eLsgStatus == BapLayerLsgStat_WaitForOrInvalidConfig))
            && ((bitfield_t) 1u == poLsgRamRow->fState.fRetryProcessingActive)
          )
        {
            /* Ueberwachung fuer das Lsg abschalten. Wird bei Bedarf wieder durch BAP_BPL_TaskRetryMonitoringFct() eingeschaltet */
            poLsgRamRow->fState.fRetryProcessingActive = BAP_FALSE;

            for(u8RomRowIndex = Bap_oPars.poLsgRomRow->u8FctRomTableSize; u8RomRowIndex > (uint8_t)0; --u8RomRowIndex)
            {
                Bap_oPars.poFctRomRow =  &BAP_FctRomTables[Bap_oPars.poLsgRomRow->u16FctRomIndex + (uint16_t)(u8RomRowIndex - (uint16_t)1)];
                Bap_oPars.fctId = Bap_oPars.poFctRomRow->fctId;

                BAP_BPL_TaskRetryMonitoringFct(&Bap_oPars);
            }
        }
    }
    return;
}
#   define BAP_STOP_SEC_CODE_CYCLIC
#   include <BAP_MemMap.h>
#endif /* #ifdef BAP_ASG */


#ifdef BAP_ASG
/* Diese Funktion ist in bap_bpl.h dokumentiert */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_BPL_ProcessHBMsg(BapLsgRomRow_pot apoLsgRomRow, DBGVAR uint8_t au8HearbeatTime)
{
    BapLsgRamRow_pot poLsgRamRow;

    /* Hilfsfunktion, wird nur beim Empfang der HB-Nachricht vom BPL selbst oder
     * beim Empfang der Statusall-Nachricht aufgerufen, d.h. alle Aufrufenden sind bekannt.
     */
    /*lint -esym(613,apoLsgRomRow) */
    BAP_ASSERT(NULL != apoLsgRomRow);

    poLsgRamRow = apoLsgRomRow->poLsgRamRow;

    if( /* HB-Zeit vom FSG == 0 bedeutet kein HB-Mechanismus */
        (au8HearbeatTime > (uint8_t)0)
        /* HB-Faktor im ASG == 0 bedeutet keine HB-Ueberwachung */
        && (apoLsgRomRow->u8Heartbeat > (uint8_t)0)
        && (BapLayerLsgStat_Running == poLsgRamRow->eLsgStatus))
    {
        /*  Heartbeat eingetroffen, dann Ueberwachung starten */
        poLsgRamRow->eHeartbeatStatus = BapBplStat_OK;
        BAP_DBG_SetHeartbeatState(apoLsgRomRow->lsgId, BAP_TRUE);
        BAP_BPL_InitializeHeartbeat(apoLsgRomRow, au8HearbeatTime);
    }
    return;
    /*lint +esym(613,apoLsgRomRow) */
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif /* #ifdef BAP_ASG */


/* CallBack-Funktionen */

/*  Wird vom BCL als Callback aufgerufen. Dokumentiert in bap_bcl.h */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_BCL_ErrorIndication(DBGVAR lsgId_t aLsgId
    , DBGVAR fctId_t aFctId
    , DBGVAR BapError_et aeErrorCode)
{
#ifdef BAP_ASG
    BapLsgRomRow_pot poLsgRomRow;
    BapFctRomRow_pot poFctRomRow;
    BapBplRamRow_pot  poBplRamRow;

    poLsgRomRow = BAP_GetLsgRomRow(aLsgId);
    poFctRomRow = BAP_GetLsgFctRomRow(poLsgRomRow, aFctId);
    poBplRamRow = (poFctRomRow != NULL) ? poFctRomRow->poBplRamRow : NULL;

    /*lint -esym(613, poLsgRomRow) falls BplRamRow dann existiert auch LsgRomRow! */
    if ((NULL != poBplRamRow)
        && ((bitfield_t) 1u == poBplRamRow->fRetryOrProcessingFlags.bRetryOrProcessingActive)
#if defined(BAP_ASG) && defined(BAP_FSG)
        && (BapSG_ASG == poLsgRomRow->eSGType)
#endif /* defined(BAP_ASG) && defined(BAP_FSG)  */
       )
    {
        switch(aeErrorCode)
        {
            /* BCL Fehlermeldungen */
            case BapErr_IllegalSequence:
            case BapErr_SequenceNumber:
            case BapErr_TimeoutSegmentation:
            case BapErr_OversizeSegmentation:
            case BapErr_BadDataLength:
                /* Wiedereinschalten des Retry-Mechanismus nach einem
                 * Intertelegrammzeitfehler und allen moeglichen Segmentierungsfehlern.
                 *
                 * Retry oder Retry-Timeout beim naechsten RetryDispatcher-Lauf ausloesen
                 * durch Setzen des Timers auf "abgelaufen"=1.
                 */
                poBplRamRow->u16RetryOrProcessingTimer = (uint16_t)1;

                BAP_DBG_RetryMntStartedEvent(aLsgId);

                /* Im Retry-Fall erfolgt keine Meldung an BAL */

                break;
            default:
                /* Stoppen des Retry-timer LAH 1.0 Seite 51*/
                BAP_BPL_RetryAnswered(aLsgId, poBplRamRow);

                /* Meldung an BAL */
                BAP_BPL_ErrorIndication(aLsgId, aFctId, aeErrorCode);
                break;
        }
    }
    else
#endif /* #ifdef BAP_ASG */
    {
        /* Meldung an BAL */
        BAP_BPL_ErrorIndication(aLsgId, aFctId, aeErrorCode);
    }

    /*lint +esym(613, poLsgRomRow) */

    return;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


/*  Wird vom BCL als Callback aufgerufen. Dokumentiert in bap_bcl.h
 *
 * Diese Funktion hat 9 OutgoingCalls (max.7), 6 ControlNestingLayers (max.4)
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_BCL_DataReceived(BapInternalParameters_cpot apoPars)
{
/*
 * wenn ASG und aFctId ==4 (HB) und aeOpCode = BapOp_PropHeartbeatStatus => Ueberwachung starten
 * wenn ASG und aFctId ==2 (BAP_Config versionsNr) und aeOpCode = BapOp_PropReset  => HB aus
 */

    /* Diese Funktion wird nur vom BCL aufgerufen, apData wird nicht NULL sein */
    /*lint -esym(613,apoPars) */
    BAP_ASSERT(NULL != apoPars);

#ifdef BAP_ASG
    if ( (apoPars->eOpCode == BapOp_MessageReceived) )
    {
        if( (NULL != apoPars->poLsgRomRow)
            && (BapBplStat_Stopped != apoPars->poLsgRomRow->poLsgRamRow->eHeartbeatStatus)
#if defined(BAP_ASG) && defined(BAP_FSG)
            && (BapSG_ASG == apoPars->poLsgRomRow->eSGType)
#endif /* defined(BAP_ASG) && defined(BAP_FSG)  */
           )
        {
            /* retriggere Heartbeat auch bei Nachrichten einer kompatiblen Erweiterung der Funktionsliste */
            BAP_BPL_RetriggerHeartbeat(apoPars->poLsgRomRow);

            /* retriggere GetAll auch bei Nachrichten einer kompatiblen Erweiterung der Funktionsliste */
            BAP_BPL_UpdGetAllRetryOnOpCode(apoPars);
        }
    }
    else
#endif /* #ifdef BAP_ASG */

    if(NULL != apoPars->poFctRomRow)
    {
#ifdef BAP_ASG
#if defined(BAP_ASG) && defined(BAP_FSG)
        if (BapSG_ASG == apoPars->poLsgRomRow->eSGType)
#endif /* defined(BAP_ASG) && defined(BAP_FSG)  */
        {
            if( ((fctId_t)BAP_FCTID_HEARTBEAT == (fctId_t)apoPars->fctId)
                /* HMS, ALA: Status nicht gemaess LAH, aber damit Get HB vom BAL auch den HB einschaltet */
                && ((BapOp_PropHeartbeatStatus == apoPars->eOpCode) ||  (BapOp_PropStatus == apoPars->eOpCode)))
            {
                BAP_BPL_ProcessHBMsg(apoPars->poLsgRomRow, *apoPars->pData);
            }
            else if( ((fctId_t)BAP_FCTID_BAPCONFIG == (fctId_t)apoPars->fctId) && (BapOp_PropReset_Set == apoPars->eOpCode) )
            {
                /*  Heartbeat-Ueberwachung stoppen */
                apoPars->poLsgRomRow->poLsgRamRow->eHeartbeatStatus = BapBplStat_Stopped;
                BAP_DBG_SetHeartbeatState(apoPars->lsgId, BAP_FALSE);

                /*  Nach FSG Reset auch die laufenden Retries anhalten ohne Timeout-Meldung */
                BAP_BPL_StopRetries(apoPars->poLsgRomRow);
            }
            else
            {
                /* keine reservierte Funktion die fuer den BPL Bedeutung hat */
            }

            BAP_BPL_UpdateRetryOnOpCode(apoPars->poFctRomRow, apoPars->eOpCode);
            BAP_BPL_UpdGetAllRetryOnOpCode(apoPars);
        }
#endif /* #ifdef BAP_ASG */

#if defined(BAP_FSG) && defined(BAP_USES_METHODS)
#if defined(BAP_ASG)
        if (BapSG_FSG == apoPars->poLsgRomRow->eSGType)
#endif /* defined(BAP_ASG) && defined(BAP_FSG)  */
        {
            BAP_BPL_UpdProcessDispatching(apoPars->poFctRomRow, apoPars->eOpCode);
        }
#endif /* #if defined(BAP_FSG) && defined(BAP_USES_METHODS) */

        /* nur externe OpCodes verarbeiten und an BAL weitergeben */
        if(apoPars->eOpCode < BapOp_CacheError)
        {
            BAP_BPL_DataReceived(apoPars);
        }
        else
        {
            /* interne OpCodes werden nur vom BPL verarbeitet */
        }
    }
    else
    {
        /*Nachricht war nicht fuer mich!*/

        /* Bit ist zwar dem BCL zugeordnet, aber der kann es selbst nicht
           auf allen Bussystemen auswerten ohne zusaetzlichen Speicherbedarf */
        BAP_DBG_RxDataPurgedEvent();
    }
    /*lint +esym(613,apoPars) */
    return;
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>


#if defined(BAP_FSG) && defined(BAP_USES_METHODS)
/* Diese Funktion ist in bap_bpl.h dokumentiert
 *
 * Diese Funktion hat 6 ControlNestingLayers (max.4)*/
#   define BAP_START_SEC_CODE_CYCLIC
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_BPL_TaskProcessDispatcher(void)
{
    BapBplRamRow_pot poBplRamRow;

    DBGVAR uint8_t u8LsgIndex;
    DBGVAR uint8_t u8RomTableSize;
    DBGVAR uint8_t u8RomRowIndex;

    BAP_InitInternalParameters(&Bap_oPars);
    Bap_oPars.eOpCode = BapOp_MethProcessing;

    /* Ueber LSGs iterieren */
    for(u8LsgIndex = (uint8_t)0; u8LsgIndex < BAP_P_LSG_ROM_TABLE_ROWS; ++u8LsgIndex)
    {
        Bap_oPars.poLsgRomRow = BAP_pLsgRomTable[u8LsgIndex];
        Bap_oPars.lsgId = Bap_oPars.poLsgRomRow->lsgId;
        u8RomTableSize = Bap_oPars.poLsgRomRow->u8FctRomTableSize;
        if(   (Bap_oPars.poLsgRomRow->poLsgRamRow->eLsgStatus == BapLayerLsgStat_Running)
            && ( Bap_oPars.poLsgRomRow->poLsgRamRow->fState.fRetryProcessingActive == (bitfield_t) 1u)
#if defined(BAP_ASG) && defined(BAP_FSG)
            &&(BapSG_FSG == Bap_oPars.poLsgRomRow->eSGType)
#endif /* defined(BAP_ASG) && defined(BAP_FSG)  */
            )
        {
            /* Dispatcher fuer dieses Lsg ausschalten, wird bei Bedarf spaeter wieder eingeschaltet */
            Bap_oPars.poLsgRomRow->poLsgRamRow->fState.fRetryProcessingActive = BAP_FALSE;
            /* Ueber Fcts des LSG iterieren */
            for(u8RomRowIndex = (uint8_t)0; u8RomRowIndex < u8RomTableSize; ++u8RomRowIndex)
            {
                Bap_oPars.poFctRomRow = &BAP_FctRomTables[Bap_oPars.poLsgRomRow->u16FctRomIndex + u8RomRowIndex];
                Bap_oPars.fctId = Bap_oPars.poFctRomRow->fctId;

                poBplRamRow = Bap_oPars.poFctRomRow->poBplRamRow;
                /* Ist ein Retry konfiguriert ?, kann nur Methode sein! */
                /* RamTabelle existiert und der Retry ist aktiv, d.h. noch keine Antwort gekommen. */
                if( (NULL != poBplRamRow) && ( poBplRamRow->fRetryOrProcessingFlags.bRetryOrProcessingActive == (bitfield_t) 1u) )
                {
                    /* Ist Timer abgelaufen? */
                    switch (poBplRamRow->u16RetryOrProcessingTimer)
                    {
                        case 0:
                            /* 0 bedeutet, dass der Retry-Timer gestoppt wurde (StartMsg empfangen),
                             * dann warte auf Antwort oder Intertelegrammzeit- oder Segmentierungsfehler
                             * (= an dieser Stelle nichts zu tun).
                             */
                            break;
                        case 1:
                            /* 1 bedeutet, dass der Retry-Timer abgelaufen ist */

                            /* Timer fuer naechsten Retry wieder auf ROMWert hochsetzen */
                            poBplRamRow->u16RetryOrProcessingTimer = Bap_oPars.poFctRomRow->nMaxRetryOrProcessingTime;

                            /* setzte konfigurierte Laenge, sonst wird die Nachricht bei der Typpruefung verworfen */
                            Bap_oPars.u32Length = Bap_oPars.poFctRomRow->u32RxSize;

                            /* Senden einer Aufforderung eine Processing Nachricht zu verschicken in FSG Applikation */
                            BAP_BPL_DataReceived(&Bap_oPars);

                            break;
                        default:
                            --poBplRamRow->u16RetryOrProcessingTimer;
                            break;
                    }
                    /* Dispatcher fuer dieses Lsg wieder einschalten */
                    Bap_oPars.poLsgRomRow->poLsgRamRow->fState.fRetryProcessingActive = BAP_TRUE;
                }
            }
        }
    }
    return;
}
#   define BAP_STOP_SEC_CODE_CYCLIC
#   include <BAP_MemMap.h>
#endif /* #if defined(BAP_FSG) && defined(BAP_USES_METHODS) */

#if defined(BAP_FSG) && defined(BAP_USES_METHODS)
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
static BAP_IMPL_FAR void
BAP_BPL_UpdProcessDispatching(BapFctRomRow_pot apoFctRomRow
    , DBGVAR BapOpCodes_et aeOpCode)
{
    BapBplRamRow_pot poBplRamRow;

    /* interne Hilfsfunktion */
    /*lint -esym(613,apoFctRomRow) */
    BAP_ASSERT(NULL != apoFctRomRow);

    poBplRamRow = apoFctRomRow->poBplRamRow;

    if(NULL != poBplRamRow)
    {
        switch(aeOpCode)
        {
        case BapOp_MethAbort:
            /* Retry stoppen */
            poBplRamRow->fRetryOrProcessingFlags.bRetryOrProcessingActive = BAP_FALSE;
            break;
        case BapOp_MethStartResult:
            /* Im ASG werden beim Absenden Timer aktiviert, hier im FSG beim Empfang */
            /* Pruefen, ob ein Retry ueberwacht werden muss */
            /* Bedingungen: MaxRetryTimer>0 und richtiger Request und ASG */
            if(apoFctRomRow->nMaxRetryOrProcessingTime > (uint16_t) 0u)
            {
                /*lint -esym(613,poLsgRomRow) Wenn es eine FctRomRow gibt, gibt es auch immer eine poLsgRomRow*/
                BapLsgRomRow_pot poLsgRomRow = BAP_GetLsgRomRow(apoFctRomRow->lsgId);
                poLsgRomRow->poLsgRamRow->fState.fRetryProcessingActive = BAP_TRUE; /*lint !e613 During Specific Walk poLsgRomRow might be NULL */
                /*lint +esym(613,poLsgRomRow) */
                poBplRamRow->u16RetryOrProcessingTimer = apoFctRomRow->nMaxRetryOrProcessingTime;
                poBplRamRow->fRetryOrProcessingFlags.u6RetryCounter = apoFctRomRow->nMaxRetryCounter;
                poBplRamRow->fRetryOrProcessingFlags.bRetryOrProcessingActive = BAP_TRUE;

                BAP_DBG_RetryMntStartedEvent(apoFctRomRow->lsgId);
            }
            break;
            /* Nachricht wurde komplett versendet, entweder MethProcessing oder MethResult */
            /* kein Retrigger; Aber merken, dass versendet */
        default:
            /* No Statements */
            break;
        }
    }
    else
    {
        /* keine RamRow --> Kein retry */
    }
    return;
    /* interne Hilfsfunktion */
    /*lint +esym(613,apoFctRomRow) */
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif  /* #if defined(BAP_FSG) && defined(BAP_USES_METHODS) */

#ifdef BAP_USES_ACKNOWLEDGE
/**
 *  Diese Funktion wird vom BCL aufgerufen, wenn eine Nachricht erfolgreich verschickt wurde.
 *  Sie wird nur nach einem BAP_BCL_Send aufgerufen, nicht jedoch nach einem BAP_BCL_Resend oder
 *  BAP_BCL_ResendWithOpcode.
 *
 *  @param apoFctRomRow zeigt auf die Funktion
 *  @param aeOpCode enthaelt den gesendeten OpCode
 */
#   define BAP_START_SEC_CODE_FAST
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_BCL_Acknowledge(BapFctRomRow_pot apoFctRomRow, BapOpCodes_et aeOpCode)
{
    BAP_BPL_Acknowledge(apoFctRomRow, aeOpCode);
}
#   define BAP_STOP_SEC_CODE_FAST
#   include <BAP_MemMap.h>
#endif  /* #ifdef BAP_USES_ACKNOWLEDGE */
