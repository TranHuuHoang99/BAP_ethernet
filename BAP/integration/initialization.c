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
 *  Diese Datei enthaelt Code welcher das Initialisiern der RAM-
 *  Elemente des BAP Stacks vornimmt falls dies nicht von der
 *  C-Library im Startup-Code vorgenommen wird.
 *
 *  @remarks
 *  Es wird nicht fuer Vollstaendigkeit und/oder Korrektheit
 *  dieses Codes garantiert.
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
 * 2019-01-18	1.10.3		FFS			[SSWCCB-2657] Extern declaration and initialization of Bap_reAssignLsgRomRowFctTable
 * 2017-03-07	1.9.0 		FST			[SSWCCB-1545] SSW-Lokatierungs-Pragmas eingefuegt
 * 2016-08-29	1.8.1		FST			[SSWCCB-2410] Softwareschalter DLL_COMPILATION zur Unterscheidung
 * 										der Erzeugung von Steuergeraete-Code und der BAP-Dll eingefuegt
 * 2006_08_01   1.5         SHU         Define Integrationsbeispiel
 * 2006-06-06   1.4         ALA         Initiale Version
 ******************************************************************/

#ifndef DLL_COMPILATION
#	error Verwendung auf eigene Gefahr
#	ifndef BAP_INTEGRATIONSBEISPIEL
#		error Dies ist nur ein Beispiel. Bitte passen Sie die Datei ihren Anforderungen an.
#	endif /* BAP_INTEGRATIONSBEISPIEL */
#endif /* not defined DLL_COMPILATION */
/* Systemincludes mit <...> */
#include <string.h>

/* Bibliotheken von externen Herstellen mit <...> */

/* Eigene Header-Dateien "..." */
#include "bap_types.h"
#include "bap_privatetypes.h"
#include "bap_balconfig.h"
#include "bap_bplconfig.h"
#include "bap_bclconfig.h"
#include "bap_config.h"
#include "bap.h"

/* Externe globale Variablen-Definitionen */
/*MISRA-2004,  Multiconfig in der Funktion BAP_GetLsgRomRow(DBGVAR lsgId_t aLsgId) */
#define BAP_START_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>
extern bool_t Bap_reAssignLsgRomRowFctTable ;
#define BAP_STOP_SEC_VAR_NO_INIT_8
#include <BAP_MemMap.h>




/* Interne Typ-Definitionen */

/* Interne Const Deklarationen */

/* Interne statische Variablen */

/* Vorwaerts-Deklarationen von statischen Funktionen */

/* Definition (Implementierung) von statischen Funktionen */

/* Definition (Implementierung) von globalen Funktionen */

/**
 * Diese Funktion muss vor dem Aufruf von BAP_Init aufgerufen werden,
 * falls der C-Startup-Code nicht das Initialiseren des RAMS
 * mit den Default-Werten aus der generierten C-Datei uebernimmt.
 *
 * @remarks
 * Diese Funktion ist ungetestet.
 * Verwendung dieser Funktion auf eigene Gefahr!
 */
#define BAP_START_SEC_CODE_FAST
#include <BAP_MemMap.h>
void BAP_IMPL_FAR 
Initialize_BAP_RAM(void)
{  
    uint16_t u16LsgCounter;      /* Zaehler fuer Zeilen in der ROM-Tabelle */
    uint16_t u16pLsgCounter = 0; /* Zaehler fuer Zeilen in der RAM-Tabelle */
    lsgId_t lsgId = 0;           /* dieses Lsg gibt es nicht */

    /* Initialisiere Zustaende der logischen Steuergeraete */
    for(u16LsgCounter = 0; u16LsgCounter < BAP_LSG_ROM_TABLE_ROWS; u16LsgCounter++)
    {
        (void) memset( BAP_LsgRomTables[u16LsgCounter].poLsgRamRow 
            , 0
            , sizeof(*BAP_LsgRomTables[u16LsgCounter].poLsgRamRow) );
    }

    /* Initialisiere Intertelegramzeitueberwachung */
    (void) memset (BAP_u16InterTelegramTimerTable
        , 0
        , sizeof(BAP_u16InterTelegramTimerTable[0]) * BAP_INTER_TELEGRAM_TIMER_ROWS );
   
    /* Initialisiere Segmentierungskanaele */
    (void) memset (BAP_CanTxSegmentationChannels
        , 0
        , sizeof(BAP_CanTxSegmentationChannels[0]) * BAP_CAN_TX_SEGMENTATION_CHANNELS );
    (void) memset (BAP_CanRxSegmentationChannels
        , 0
        , sizeof(BAP_CanRxSegmentationChannels[0]) * BAP_CAN_RX_SEGMENTATION_CHANNELS );

    /* Initialisiere Ringpuffer */
    BAP_u8CanRxRingBufferReadOffset = 0;
    BAP_u8CanRxRingBufferWriteOffset = 0;
    
    /* Initialisiere Inhibit-Timer */
    (void) memset (BAP_InhibitRamTable
        , 0
        , sizeof(BAP_InhibitRamTable[0]) * BAP_INHIBIT_ROWS);
    
    /* Initialisiere Tabelle mit Zeigern auf die ausgewaehlte Lsg-Konfiguration */
    for(u16LsgCounter = 0; u16LsgCounter < BAP_LSG_ROM_TABLE_ROWS; u16LsgCounter++)
    {
        /* Waehle immer die erste inkompatible Konfiguration eines Lsgs als Default aus */
        if (lsgId != BAP_LsgRomTables[u16LsgCounter].lsgId)
        {
            lsgId = BAP_LsgRomTables[u16LsgCounter].lsgId;
            BAP_pLsgRomTable[u16pLsgCounter] = &BAP_LsgRomTables[u16LsgCounter];
            u16pLsgCounter++;
        }
    }
	Bap_reAssignLsgRomRowFctTable = BAP_TRUE ;  /* neu erstellung der Index Tabelle notwendig. siehe Funktion BAP_GetLsgRomRow */
}
#define BAP_STOP_SEC_CODE_FAST
#include <BAP_MemMap.h>

/*  Callback-Funktionen */

