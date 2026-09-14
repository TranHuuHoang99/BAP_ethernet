/******************************************************************
 *
 *     Copyright (c) 2006-2023 Audi AG, D-85045 Ingolstadt
 *
 ******************************************************************
 *
 * Project:    BAP
 * Component:  AALB
 * BAP Version: 1.12.2
 *
 ******************************************************************
 *
 * Summary
 *
 *  This file contains type definitions of the configuration of the
 *  AALB adaption layer between PDU Router and BAP (Bedien- und
 *  Anzeigeprotokoll).
 *
 *  This types are used in AALB and in aalb_cfg.c
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
 * 2021-06-09   1.11.3      JEO         [SSWPPB-209] Add ASR interface to enable/disable sending of debug informations.
 * 2020-08-13   1.11.2      KUL         [SSWPPB-73] Element added to struct CanMsgIdPduIdTab_t for mapping with UL PDU IDs
 * 2020-03-31   1.11.1      ODD         [SSWPPB-93] Changed #define MAX_UINT_16 Definition because the old implementation
 *                                      ((uint16_t) (-1)) produce Polyspace Warning and is poor coding style
 * 2014-10-06   1.8.0       FST         [SSWCCB-2104] Changed MAX_BAP_MSG_LEN from 8 Byte to 1514 Byte for Ethernet
 * 2011-05-27               NQU         BAP_E_PENDING definiert
 * 2007-11-14   1.03        MIP         Aalb_Cbk.h changes - include structure
 * 2007-03-15   1.0         MIP         Changes after Audi review
 *                                      new function: BAP_GetVersionInfo()
 * 2006-12-11   1.0         ALA         Initial Version
 ******************************************************************/

#ifndef AALB_AALB_TYPES_H
#define AALB_AALB_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/* System includes <...> */

/* Vendor libraries <...> */
#include <BAP_Cbk.h>
#include <bap_canubs.h>

/* own header files "..." */

/* macro definitions */
#ifndef BAP_MAX_UINT_16
#define BAP_MAX_UINT_16     ((uint16_t) 65535u) /* equals 0xFFFFu */
#endif

#ifndef MAX_BAP_MSG_LEN
#define MAX_BAP_MSG_LEN ((uint16_t) 1444u) /* BAP Message (CAN), max. length = 8; (Ethernet), max. length = 1444 */
#endif

#define BAP_E_PENDING 2u

/* type definitions */

/**
 * Mapping Channel to PduId (TX)
 */
typedef struct
{
    /**
     * This value identifies the CAN or Flexray channel to be used. In VW/Audi
     * projects this value normally is 1.
     */
    BapCanInterfaceChannel_t canChannel;

    /**
     * PDU Router ID where the CanMsgId shall be transmitted (ID which is parameter of BAP_TriggerTransmit).
     */
    PduIdType pduId;

#ifndef BAP_USES_PDUR
    /**
     * ComIf PDU ID used for <BusIf>_TxConfirmation callback.
     */
    PduIdType pduIdComIf;
#endif

} CanMsgIdPduIdTab_t;


/**
 * Mapping PduId to Channel (RX)
 */
typedef struct
{
    /**
     * PDU Router ID to be mapped to a CanMsgId.
     */
    PduIdType pduId;

    /**
     * This value identifies the CAN channel to be used. In VW/Audi
     * projects this value normally is 1.
     */
    BapCanInterfaceChannel_t canChannel;
} PduId2CanMsgIdTab_t;


/**
 * Mapping BAP PduId to PduR PduId
 */
typedef struct
{
    PduIdType bap_pdu_id;
    PduIdType pdur_pdu_id;
} BapPduId2PdurPduIdTab_t;

/* const deklarations */

/* External global variable definitions */

extern bool_t BAP_SendDebugInfo_Active;

/* function declarations */


#ifdef __cplusplus
}
#endif

#endif      /* #ifndef AALB_AALB_TYPES_H */
