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
 * Generiert am:    14.09.2026
 *           um:    15:22:06
 * Quelldatei:      C:\workspace\sample_project\BAP_ethernet\IPv6_Multicast\FSG\FsgLarge\fsg.xml
 * Zieldatei:       C:\workspace\sample_project\BAP_ethernet\IPv6_Multicast\FSG\FsgLarge\palb_cfg_project.h
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

#define BAP_Klima1_FSG_01_MSGID	0x38000100u
#define BAP_Klima2_FSG_01_MSGID	0x38000200u
#define BAP_KlimaMaster_FSG_01_MSGID	0x38004200u
#define BAP_RDK_FSG_01_MSGID	0x38000700u

/*Rx MSG IDs*/

#define BAP_KlimaMaster_ASG_01_MSGID	0x30004200u
#define BAP_Klima2_ASG_01_MSGID	0x30000200u
#define BAP_Klima1_ASG_01_MSGID	0x30000100u
#define BAP_RDK_ASG_01_MSGID	0x30000700u


#endif /* PALB_CFG_PROJECT_H */
