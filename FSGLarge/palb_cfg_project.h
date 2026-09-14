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
*  This generated file contains definitions and variable declarations
*  of the configuration of the PALB adaption layer between
*  SoAd Message IDs and BAP PDU IDs.
*
******************************************************************
*
* Revision History (w/o SCM)
*
* Date        Version     Author       Description
* ----------------------------------------------------------------
* 2020-09-28   1.11.2       KUL        [SSWPPB-70] Initial version PALB 
******************************************************************
 *
 * Generiert am:    18.08.2026
 *           um:    15:41:00
 * Quelldatei:      C:\workspace\sample_project\POC_8255\backup\FSG\BAP_SW1.10_ClimateZone_P30DF79_V5.90_FSG.xml
 * Zieldatei:       C:\workspace\sample_project\POC_8255\backup\FSG\palb_cfg_project.h
 *
 * BAPgen Version:  1.12.2
 * BAPgen Stand:    10.10.2023
 ******************************************************************/


/******* Do not edit - Start !!!. Tool generated *********/
#ifndef PALB_CFG_PROJECT_H
#define PALB_CFG_PROJECT_H

/******* Do not edit - End !!!. Tool generated ***********/
/*
   ATTENTION !! -> Integrator must edit this file. Please enter appropriate 
   32 bit Message ID for each Ethernet PDU.
*/

/* Macro definitions */

/*Tx MSG IDs*/

#define BAP_Klima1_FSG_01_MSGID	100
#define BAP_KlimaMaster_FSG_01_MSGID	101

/*Rx MSG IDs*/

#define BAP_KlimaMaster_ASG_04_MSGID	107
#define BAP_KlimaMaster_ASG_03_MSGID	106
#define BAP_KlimaMaster_ASG_02_MSGID	105
#define BAP_Klima1_ASG_04_MSGID	104
#define BAP_Klima1_ASG_03_MSGID	103
#define BAP_Klima1_ASG_02_MSGID	102

#define BAP_KlimaMaster_ASG_01_MSGID	1
#define BAP_Klima1_ASG_01_MSGID	0


#endif /* PALB_CFG_PROJECT_H */
