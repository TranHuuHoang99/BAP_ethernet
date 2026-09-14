/******************************************************************
 *
 *     Copyright (c) 2006-2023 Audi AG, D-85045 Ingolstadt
 *
 ******************************************************************
 *
 * Projekt:    BAP
 * Komponente: PALB
 * BAP Version: 1.12.2
 *
 ******************************************************************
 *
 * Summary
 *
 *  This file contains type definitions of the configuration of the
 *  PALB adaption layer between PDU Router and BAP (Bedien- und
 *  Anzeigeprotokoll).
 *
 *  These types are used in PALB and in palb_cfg.c
 *
 ******************************************************************
 *
 * Revision History (w/o SCM)
 *
 * Date         Version     Author      Description
 * ----------------------------------------------------------------
 * 2023-10-10	1.12.2		DRH			[EEARCH-35935] Release preparation, adapt Copyright date and version number.
 * 2022-11-15   1.12.1      DRH         [SSWPPB-297] Renamed macros and global variables module specific
 * 2022-10-21	1.12.1		DRH			[SSWPPB-296] Release preparation, adapt Copyright date and version number.
 * 2022-06-17	1.12.0		DRH			[SSWPPB-269] Release preparation, adapt Copyright date and version number.
 * 2021-12-07	1.11.3		JEO			[SSWPPB-244] Release preparation, adapt Copyright date and version number.
 * 2020-08-13   1.11.2      KUL         [SSWPPB70] Initial version
 ******************************************************************/
#ifndef PALB_PALB_TYPES_H
#define PALB_PALB_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/* System includes <...> */

/* Vendor libraries <...> */
#include "bap_types.h"

/* own header files "..." */

/* macro definitions */
#ifndef BAP_MAX_UINT_16
#define BAP_MAX_UINT_16     (0xFFFFu)
#endif

#ifndef BAP_MAX_UINT_32
#define BAP_MAX_UINT_32     (0xFFFFFFFFu)
#endif

#ifndef BAP_MAX_UINT_8
#define BAP_MAX_UINT_8      (0xFFu)
#endif

#ifndef MAX_BAP_MSG_LEN
#define MAX_BAP_MSG_LEN ((uint16_t) 1444u) /* BAP Message (Ethernet), max. length = 1444 */
#endif

/* type definitions */

/**
 * Mapping Channel to PduId (TX)
 */
typedef struct
{
	/**
	 * BAP Internal PDU ID.
	 */
	BapCanMsgId_t pduId;
    /**
     * Part of SoAd Header - Message ID
     */
    uint32_t msgId;
    /**
     * Ethernet Channel Number
     */
    uint8_t interfaceChnlNum;

} EthPduIdConfigTab_t;

/* const declarations */

/* External global variable definitions */

/* function declarations */

#endif /* PALB_PALB_TYPES_H */
