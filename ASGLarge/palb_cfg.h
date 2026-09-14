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
 *  of the configuration of the PALB layer between 
 *  POSIX OS and BAP (Bedien- und Anzeigeprotokoll).
 *
 ******************************************************************
 *
 * Revision History (w/o SCM)
 *
 * Date        Version     Author       Description
 * ----------------------------------------------------------------
 * 2020-10-09   1.11.2     KUL          [SSWPPB-70] Initial version.
 ******************************************************************
 *
 * Generiert am:    18.08.2026
 *           um:    14:49:14
 * Quelldatei:      C:\workspace\sample_project\POC_8255\backup\ASG\BAP_SW1.12_ICC_MQBevo_V2_187_asg.xml
 * Zieldatei:       C:\workspace\sample_project\POC_8255\backup\ASG\palb_cfg.h
 *
 * BAPgen Version:  1.12.2
 * BAPgen Stand:    10.10.2023
 ******************************************************************/

#ifndef PALB_PALB_CFG_H
#define PALB_PALB_CFG_H

#ifdef __cplusplus
extern "C" {
#endif

/* System includes <...> */

/* Vendor libraries <...> */
/* own header files "..." */
#include "bap.h"
#include "palb_types.h"
/*
 * Project specific header-file include. This file needs to be manually adapted to project configuration
 */
#include "palb_cfg_project.h"

#include "can_asg.h"

#if BAP_VERSION != 11220
#error Datei ist nicht kompatibel mit der Version des BAP-Stacks. Bitte diese Datei noch einmal mit dem mitgeliefertem BAPgen aus der XML-Datei generieren.
#endif


/**
 * Defines the number of PALB relevant TX PDUs in configuration xml.
 */
#define PALB_TX_PDU_COUNT   ((uint16_t)2)

/**
 * Defines the number of rows in table palb_EthPduIdConfigTab. 
 * Equals (number of PALB TX PDUs + number of PALB RX PDUs)
 */
#define PALB_PDU_CONFIG_TAB_SIZE   ((uint16_t)4)

/* type definitions */

/* const declarations */

/* External global variable definitions */
 /* Table of all ETH PDU Configurations */
extern EthPduIdConfigTab_t palb_EthPduIdConfigTab[PALB_PDU_CONFIG_TAB_SIZE];

/* function declarations */

#ifdef __cplusplus
}
#endif

#endif      /* #ifndef PALB_PALB_CFG_H */

