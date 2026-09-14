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
 *  Diese Datei enthaelt die Implementierung diverser Funktionen
 *  im BAP Projekt, welche nicht genau einer Schicht (BAL, BPL, BCL)
 *  zugeordnet werden koennen. Siehe auch bap_util.c.
 *
 *  Enthaelt das Verteilen der zyklischen Task-Aufrufe.
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
 * 2017-03-17	1.9.0.1		FST			[SSWCCB-1545] SSW-Lokatierungs-Pragmas eingefuegt
 * 2014-11-28	1.8.0		WWU/FST		CR variable PDU-Groesse: Formataenderung der Variablen 16Bit->32Bit
 * 2014-03-24	1.7.1		WWU			Defines fuer BAP_BPL_TaskProcessDispatcher() korrigiert.
 * 2004-04-10   1.3         CRI         Processing Ueberwachungstask im FSG hinzugefuegt
 * 2004-06-07   1.1         JOK         Compilerschalter fuer SG-Typen zur Optimierung
 *                                      des ROM-Bedarfs eingefuegt
 * 2004-06-07   1.1         JOK         Reihenfolge in BAP_Task() von BAP_BCL_TaskSend();BAP_BCL_TaskRxNotify();
 *                                      auf BAP_BCL_TaskRxNotify();BAP_BCL_TaskSend(); geaendert.
 *                                      Damit kann eine Anfrage noch im gleichen Task direkt beantwortet werden.
 ******************************************************************/


/* Systemincludes mit <...> */

/* Bibliotheken von externen Herstellen mit <...> */

/* Eigene Header-Dateien "..." */
#include "bap_bpl.h"
#include "bap_bcl.h"
#include "bap_debug.h"

/* Externe globale Variablen-Definitionen */

/* Interne Makro-Definitionen */

/* Interne Typ-Definitionen */

/* Interne Const Deklarationen */

/* Interne statische Variablen */

/* Vorwaerts-Deklarationen von statischen Funktionen */

/* Definition (Implementierung) von statischen Funktionen */

/* Definition (Implementierung) von globalen Funktionen */

/* Diese Funktion ist in bap.h dokumentiert */
#   define BAP_START_SEC_CODE_CYCLIC
#   include <BAP_MemMap.h>
BAP_IMPL_FAR void
BAP_Task(void)
{
    /* Initialisiere Zeitueberwachung fuer Indications (wird beim Polling und Notify modifiziert) */
#ifdef BAP_TASKTIME_LIMIT
    BAP_u32TaskTimeCounter = (uint32_t)0;
#endif /* #ifdef BAP_TASKTIME_LIMIT */   
      
    /* Aufrufe an BAL => BAL hat keinen Task */
    
    /* Aufrufe an BPL */
#ifdef BAP_ASG    
    BAP_BPL_TaskRetryMonitoring();
    BAP_BPL_TaskHeartbeatMonitoring();
#endif /* #ifdef BAP_ASG */

#if defined(BAP_FSG) && defined(BAP_USES_METHODS)
    BAP_BPL_TaskProcessDispatcher();
#endif /* #if defined(BAP_FSG) && defined(BAP_USES_METHODS) */

#ifdef BAP_FSG
    BAP_BPL_TaskHeartbeatDispatcher();
#endif /* #ifdef BAP_FSG */


    /* Aufrufe an BCL */
    BAP_BCL_ReadRingbuffer();       /* Abfrage des Empfangsringbuffer */
    BAP_BCL_TaskRxNotify();         /* Notifizierung empfangener Nachrichten an BPL */
    BAP_BCL_TaskSend();             /* Versenden von Nachrichten ueber Low-Level-Treiber */
    
    /* Aufruf an das Debug-Interface */
    BAP_DBG_Task();
    
    return;
}
#define BAP_STOP_SEC_CODE_CYCLIC
#include <BAP_MemMap.h>
