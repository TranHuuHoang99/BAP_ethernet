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
 * This file contains definitions and variable declarations
 * of the of the PALB layer between POSIX OS and BAP (Bedien- und Anzeigeprotokoll).
 *
 *
 ******************************************************************
 *
 * Revision History (w/o SCM)
 *
 * Date        Version     Author       Description
 * ----------------------------------------------------------------
 * 2023-10-10	1.12.2		DRH			[EEARCH-35935] Release preparation, adapt Copyright date and version number.
 * 2022-11-15   1.12.1      DRH         [SSWPPB-297] Renamed macros and global variables module specific
 * 2022-10-21	1.12.1		DRH			[SSWPPB-296] Release preparation, adapt Copyright date and version number.
 * 2022-06-17	1.12.0		DRH			[SSWPPB-269] Release preparation, adapt Copyright date and version number.
 * 2021-12-07	1.11.3		JEO			[SSWPPB-244] Release preparation, adapt Copyright date and version number.
 * 2020-10-08   1.11.2      KUL         [SSWPPB70] - Initial version
 ******************************************************************
 */

#ifndef PALB_PALB_H
#define PALB_PALB_H

/* System includes <...> */

/* Vendor libraries <...> */
/* own header files "..." */
#include "bap.h"

#if BAP_VERSION != 11220
#error Datei ist nicht kompatibel mit der Version des BAP-Stacks. Bitte diese Datei noch einmal mit dem mitgeliefertem BAPgen aus der XML-Datei generieren.
#endif

/* Macro-Definitions */

#define BAP_SOAD_HEADER_SIZE 8u
#define BAP_SOAD_MSGID_SIZE 4u
#define BAP_SOAD_MSGLEN_SIZE 4u
#define BAP_START_OF_USER_DATA 8u
#define BAP_START_OF_MSG_LEN 4u
#define BAP_SOAD_MSGLEN_DLC_BYTE 7u

#define BAP_BYTE0 0u
#define BAP_BYTE1 1u
#define BAP_BYTE2 2u
#define BAP_BYTE3 3u
#define BAP_BYTE4 4u

/* Type-Definitions */

/* Const Declarations */

/* Extern global Variables */

/* Function Declarations */
/* documentation can be found in the implementation section */
void BAP_RxIndication(ptr_t apData);

/**
 *  This function is to be implemented by application / user of BAP layer.
 *
 *  @param aCanInterfaceChannel
 *      Channel number of Ethernet Channel according to configuration xml.
 *
 *  @param aPduId
 *      BAP PDU ID according to configuration xml.
 *
 *  @param apData
 *      Buffer in SoAd format i.e. 8 byte SoAd format header + BAP data
 *
 *  @param au16MsgLength
 *      Length of the buffer to be transmitted on socket
 *
 *  @returns BAP_TRUE if transmission on socket is successful,
 *      BAP_FALSE if unsuccessful.
 *
 *  @remarks
 *
 *
 */
bool_t BAP_Transmit_TxData(BapCanInterfaceChannel_t aCanInterfaceChannel
        , BapCanMsgId_t aPduId
        , ptr_t apData
        , uint16_t au16MsgLength);

#endif /* PALB_PALB_H */
