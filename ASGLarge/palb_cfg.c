/******************************************************************
 *
 *     Copyright (c) 2006-2023 Audi AG, D-85045 Ingolstadt
 *
 ******************************************************************
 *
 * Project:    BAP 
 * Component:  PALB Configuration 
 *
 ******************************************************************
 *
 * Summary
 *
 *  This file contains the configuration of the interfacing layer
 *  PALB (POSIX Adaption Layer BAP) which is located between the
 *  POSIX OS and the BAP (Bedien- und Anzeigeprotokoll).
 *
 ******************************************************************
 *
 * Revision History (w/o SCM)
 *
 * Date        Version     Author       Description
 * ----------------------------------------------------------------
 * 2020-10-09   1.11.2      KUL         [SSWPPB-70] Initial version
 ******************************************************************
 *
 * Generiert am:    18.08.2026
 *           um:    14:49:14
 * Quelldatei:      C:\workspace\sample_project\POC_8255\backup\ASG\BAP_SW1.12_ICC_MQBevo_V2_187_asg.xml
 * Zieldatei:       C:\workspace\sample_project\POC_8255\backup\ASG\palb_cfg.c
 *
 * BAPgen Version:  1.12.2
 * BAPgen Stand:    10.10.2023
 ******************************************************************/


/* System includes <...> */

/* Vendor libraries <...> */
/* own header files "..." */
#include "palb_cfg.h"
#include "bap.h"

#if BAP_VERSION != 11220
#error Datei ist nicht kompatibel mit der Version des BAP-Stacks. Bitte diese Datei noch einmal mit dem mitgeliefertem BAPgen aus der XML-Datei generieren.
#endif


EthPduIdConfigTab_t
palb_EthPduIdConfigTab[PALB_PDU_CONFIG_TAB_SIZE] =
{
    /* PDU ID */                 /* MSG ID */               /* Interface Channel Number */
	{BAP_Klima1_ASG_01,            BAP_Klima1_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_KlimaMaster_ASG_01,            BAP_KlimaMaster_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Klima1_FSG_01,            BAP_Klima1_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_KlimaMaster_FSG_01,            BAP_KlimaMaster_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20}
};


/* Internal makro definitions */

/* Internal type definitions */

/* Internal const deklarations */

/* Internal static variables */

/* static function declarations */

/* Definition (Implementation) of static functions */

/* Definition (Implementation) of global functions */



