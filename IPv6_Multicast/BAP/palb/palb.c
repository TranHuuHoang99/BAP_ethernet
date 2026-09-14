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
 *  This file contains the layer PALB (POSIX Adaption Layer BAP).
 *  It is located as an intermediate layer between OS and BAP (Bedien und Anzeigeprotokoll) and
 *  applicable for the ECUs that use automotive Ethernet interface for network communication.
 *
 ******************************************************************
 *
 * Revision History (w/o SCM)
 *
 * Date        Version     Author       Description
 * -----------------------------------------------------------------
 * 2023-10-10	1.12.2		DRH			[EEARCH-35935] Release preparation, adapt Copyright date and version number.
 * 2022-11-15   1.12.1      DRH         [SSWPPB-297] Renamed macros and global variables module specific
 * 2022-10-21	1.12.1		DRH			[SSWPPB-296] Release preparation, adapt Copyright date and version number.
 * 2022-06-17	1.12.0		DRH			[SSWPPB-269] Release preparation, adapt Copyright date and version number.
 * 2021-12-07	1.11.3		JEO			[SSWPPB-244] Release preparation, adapt Copyright date and version number.
 * 2020-10-09  	1.11.2      KUL         [SSWPPB-70] Creation of PALB layer.
 *******************************************************************
 */

/* System includes <...> */

/* Vendor libraries <...> */
#include "bap_canubs.h"
#include "palb.h"
#include "palb_cfg.h"

/* Internal macro definitions */

/* Internal type definitions */

/* Internal const declarations */

/* Internal static variables */

/* Transmit buffers */
static uint8_t palb_EthTxBuffers[PALB_TX_PDU_COUNT][BAP_MAX_PDU_SIZE
		+ BAP_SOAD_HEADER_SIZE];

/* static function forward declarations */
/* documentation can be found in the implementation section */
static uint32_t palb_GetMsgId(const BapCanMsgId_t aPduId);

/* documentation can be found in the implementation section */
static BapCanMsgId_t palb_GetPduId(const uint32_t aMsgId);

/* documentation can be found in the implementation section */
static uint8_t palb_GetRxChnlNumByPdu(uint16_t aPduId);

/* documentation can be found in the implementation section */
static BapCanMsgId_t palb_GetPduIdfromSoAdHdr(const ptr_t SoAdBuf);

/* documentation can be found in the implementation section */
static uint32_t palb_GetMsgLenfromSoAdHdr(const ptr_t SoAdBuf);

/* documentation can be found in the implementation section */
static void palb_AddSoAdHdr(uint16_t u16Index, const BapCanMsgId_t aPduId,
		const ptr_t apData, uint16_t au16Length);

/* documentation can be found in the implementation section */
static uint8_t palb_GetTxHandleByPdu(uint8_t aPduId);

/**
 *  BAP_CANUBS_IsReadyForTx() has to be implemented by bus connection
 *  and is called by BAP stack (BAP_CANUBS_TxData) any time there is
 *  data to be transmitted.
 *
 *  The bus interface replies either with BAP_TRUE in case of sending
 *  of data is allowed or BAP_FALSE if sending of data is not allowed
 *  at the moment.
 *
 *  @param aCanInterfaceChannel identifies the number of the physical
 *  CAN interface.
 *
 *  @param aPduId is a PDU identifier or a CAN message handle
 *  which is used for communication (e.g. CAN Id)
 *
 *  @returns
 *  BAP_TRUE in case of calling BAP_CANUBS_TxData is permitted or
 *  BAP_FALSE if it is prohibited.
 *
 *  @remarks
 *  Always returns BAP_TRUE because for Ethernet because no transmit
 *  confirmation call back available to facilitate DLC mechanism. Might
 *  require merging with existing implementation of this function in case
 *  of multiple bus types supported.
 *
 *  In case of BAP_TRUE data will be prepared for transmission and will
 *  be send out with BAP_CANUBS_TxData.
 *
 *  This pre-check is used for optimization of run-time because data will be
 *  processed only if required
 *
 *  This function shall return BAP_FALSE in case of BusOff.
 */
bool_t BAP_CANUBS_IsReadyForTx(BapCanInterfaceChannel_t aCanInterfaceChannel,
		BapCanMsgId_t aPduId) {
	return BAP_TRUE;
}

/**
 *  BAP_CANUBS_InitReadyForTx needs to be implemented by bus connection.
 *  It is called by BAP Stack during initialization of the stack.
 *
 *  @param aCanInterfaceChannel identifies the number of the physical
 *  CAN interface.
 *
 *  @param aPduId is a PDU identifier or a CAN message handle
 *  which is used for communication (e.g. CAN Id)
 *
 *  @remarks Empty for POSIX Ethernet. Might require merging with existing implementation
 *   of this function in case of multiple bus types supported.
 */
void BAP_CANUBS_InitReadyForTx(BapCanInterfaceChannel_t aCanInterfaceChannel,
		BapCanMsgId_t aPduId) {

}

/**
 *  BAP_CANUBS_TxData() has to be implemented by the bus connection and
 *  is called by the BAP Stack data shall be transmitted irrespective of bus type.
 *
 *  @param aCanInterfaceChannel identifies physical bus interfaces.
 *  aCanInterfaceCannel is [0, 9] --> TxHandle will be transmitted via CAN BUS
 *  aCanInterfaceCannel is [10, 19] --> TxHandle will be transmitted via FlexRay BUS
 *  aCanInterfaceCannel is [20, 29] --> TxHandle will be transmitted via Ethernet BUS
 *
 *  @param aPduId is the PDU identifier or a CAN message handle
 *  which is used for communication (e.g. CAN Id)
 *
 *  @param apData points to the data to be transmitted.
 *
 *  @param au16MsgLength contains the length of the data to be transmitted.
 *
 *  @returns
 *  BAP_TRUE in case of success, no re-transmit to bus interface necessary.
 *  BAP_FALSE in case of an error. There will be a retry.
 *
 *  @remarks Might require merging with existing implementation of this function
 *  in case of multiple bus types supported. Following shall be considered as an
 *  example implementation.
 *
 */
bool_t BAP_CANUBS_TxData(BapCanInterfaceChannel_t aCanInterfaceChannel,
		BapCanMsgId_t aPduId, const ptr_t apData, uint16_t au16MsgLength) {
	bool_t retval = BAP_FALSE;
	bool_t iFChnValid = BAP_FALSE; /* Validity of Interface Channel */

	uint8_t u8Index = palb_GetTxHandleByPdu((BapCanMsgId_t) aPduId);

	if ((BAP_MAX_UINT_8 != u8Index) && (NULL != apData)) {
		if (au16MsgLength > MAX_BAP_MSG_LEN) {
			/* must not be reached by BAP */
			au16MsgLength = MAX_BAP_MSG_LEN;
		}

		if (((BapCanInterfaceChannel_t) 20 <= aCanInterfaceChannel)
				&& ((BapCanInterfaceChannel_t) 30 > aCanInterfaceChannel)) {
			/* Add SoAd header bytes to transmit buffer */
			palb_AddSoAdHdr(u8Index, aPduId, apData, au16MsgLength);

			au16MsgLength = au16MsgLength + BAP_SOAD_HEADER_SIZE;

			/* Valid interface channel found. */
			iFChnValid = BAP_TRUE;
		} else {
			/* NO Valid interface channel found ! */
			iFChnValid = BAP_FALSE;
		}

		/* Call BAP_Transmit_TxData only if the Interface Channel is Valid */
		if (BAP_TRUE == iFChnValid) {
			/* Integration Specific - Implement your own send/sendto inside this function */
			retval = BAP_Transmit_TxData(aCanInterfaceChannel, aPduId,
					palb_EthTxBuffers[u8Index], au16MsgLength);
		}
	}

	return retval;
}

/**
 *  BAP_RxIndication shall be called immediately after recv/recvfrom receives
 *  data on a socket. This function derives Message Length and PDU ID from received PDU data
 *  Also copies user data bytes to BAP stack input buffer by calling BAP_CANUBS_RxData().
 *
 *  @param apData ID of a PDU which was received via FlexRay Interface
 *
 *  @returns
 *	Nothing
 *
 *  @remarks
 *
 */
void BAP_RxIndication(ptr_t apData) {
	uint8_t UsrData[BAP_MAX_PDU_SIZE];
	uint32_t MsgLen;
	BapCanMsgId_t PduId;
	BapCanInterfaceChannel_t ChnlNum;

	/* Derive message length from received buffer on socket */
	MsgLen = palb_GetMsgLenfromSoAdHdr(apData + BAP_START_OF_MSG_LEN);

	/* Derive BAP PDU ID from the message id field of received buffer */
	PduId = palb_GetPduIdfromSoAdHdr(apData);

	/* Find channel number corresponding to the PDU ID as per configuration */
	ChnlNum = palb_GetRxChnlNumByPdu(PduId);

	/* Feed the relevant data to BAP stack */
	BAP_CANUBS_RxData(ChnlNum, PduId, &apData[BAP_START_OF_USER_DATA], (uint16_t) MsgLen);
}

/* Definition (Implementation) of static functions */

/**
 *  The function palb_GetPduIdfromSoAdHdr() provides the PDU ID corresponding
 *  to the four byte SoAd Message ID received as part of SoAd format header.
 *
 *  @param SoAdBuf - Pointer to buffer
 *
 *  @return retval - PDU ID corresponding to the Message ID.
 *
 */
static BapCanMsgId_t palb_GetPduIdfromSoAdHdr(const ptr_t SoAdBuf) {
	uint8_t SoAdMsgId[BAP_SOAD_MSGID_SIZE] = { 0x00, 0x00, 0x00, 0x00 };
	uint8_t retval = BAP_MAX_UINT_8;
	uint32_t MsgId;

	if (NULL != SoAdBuf) {
		/* Copy first four bytes from header */
		MEMCPY(SoAdMsgId, SoAdBuf, sizeof(SoAdMsgId));

		/* Convert four bytes to a uint32_t */
		MsgId = ((uint32_t) SoAdMsgId[BAP_BYTE0] << 24u)
				+ ((uint32_t) SoAdMsgId[BAP_BYTE1] << 16u)
				+ ((uint32_t) SoAdMsgId[BAP_BYTE2] << 8u)
				+ (uint32_t) SoAdMsgId[BAP_BYTE3];

		/* Find corresponding PDU ID */
		retval = palb_GetPduId(MsgId);
	}

	return retval;
}

/* Definition (Implementation) of static functions */

/**
 *  The function palb_GetMsgLenfromSoAdHdr() provides the message length in uint32_t
 *  by converting 4 byte message length received as part of SoAd format header.
 *
 *  @param SoAdBuf - Pointer to buffer
 *
 *  @return MsgLen - Denotes the number of BAP user data bytes that follows the message length field.
 *
 */
static uint32_t palb_GetMsgLenfromSoAdHdr(const ptr_t SoAdBuf) {
	uint8_t SoAdMsgLen[BAP_SOAD_MSGLEN_SIZE] = { 0x00, 0x00, 0x00, 0x00 };
	uint32_t MsgLen = BAP_MAX_UINT_32;

	if (NULL != SoAdBuf) {
		/* Copy message length bytes from header */
		MEMCPY(SoAdMsgLen, SoAdBuf, sizeof(SoAdMsgLen));

		/* Convert 4 bytes to a uint32_t */
		MsgLen = ((uint32_t) SoAdMsgLen[BAP_BYTE0] << 24u)
				+ ((uint32_t) SoAdMsgLen[BAP_BYTE1] << 16u)
				+ ((uint32_t) SoAdMsgLen[BAP_BYTE2] << 8u)
				+ (uint32_t) SoAdMsgLen[BAP_BYTE3];
	}

	return MsgLen;
}

/* Definition (Implementation) of static functions */

/**
 *  The function palb_AddSoAdHdr() adds the 8 byte SoAd format header and BAP
 *  user data to a global transmit buffer.
 *
 *  @param u16Index - Pointer to buffer
 *
 *  @param aPduId - PDU ID according to configuration xml
 *
 *  @param apData - BAP user data
 *
 *  @param au16Length - Length of user data
 *
 *  @return Nothing.
 *
 */
static void palb_AddSoAdHdr(uint16_t u16Index, const BapCanMsgId_t aPduId,
		const ptr_t apData, uint16_t au16Length) {
	uint8_t SoAdMsgId[BAP_SOAD_MSGID_SIZE];
	uint8_t SoAdMsgLen[BAP_SOAD_MSGLEN_SIZE];
	uint32_t MsgId, MsgLen;

	/* Find Message ID corresponding to PDU ID*/
	MsgId = palb_GetMsgId(aPduId);

	MsgLen = (uint32_t) au16Length;

	/* Convert message id to 4 byte array */
	SoAdMsgId[BAP_BYTE0] = (uint8_t) (MsgId >> 24u);
	SoAdMsgId[BAP_BYTE1] = (uint8_t) (MsgId >> 16u);
	SoAdMsgId[BAP_BYTE2] = (uint8_t) (MsgId >> 8u);
	SoAdMsgId[BAP_BYTE3] = (uint8_t) (MsgId);

	/* Convert message length to 4 byte array */
	SoAdMsgLen[BAP_BYTE0] = (uint8_t) (MsgLen >> 24u);
	SoAdMsgLen[BAP_BYTE1] = (uint8_t) (MsgLen >> 16u);
	SoAdMsgLen[BAP_BYTE2] = (uint8_t) (MsgLen >> 8u);
	SoAdMsgLen[BAP_BYTE3] = (uint8_t) (MsgLen);

	/* Add SoAd header to global transmit buffer */
	MEMCPY(palb_EthTxBuffers[u16Index], SoAdMsgId, sizeof(SoAdMsgId));
	MEMCPY(&(palb_EthTxBuffers[u16Index][BAP_BYTE4]), SoAdMsgLen,
			sizeof(SoAdMsgLen));

	if (NULL != apData) {
		/* BAP User Data buffer copied to global buffer */
		MEMCPY(&(palb_EthTxBuffers[u16Index][BAP_START_OF_USER_DATA]), apData,
				au16Length);
	}
}

/**
 *  The function palb_GetMsgId() provides the message id mapped to
 *  corresponding PDU ID from the configured table palb_EthPduId2MsgIdTab.
 *
 *  @param  MsgId - PDU ID according to configuration xml
 *
 *  @return Nothing.
 *
 */
static uint32_t palb_GetMsgId(const BapCanMsgId_t aPduId) {
	uint32_t aMsgId = BAP_MAX_UINT_32;
	uint8_t index;

	/* search entry in palb_EthPduId2MsgIdTab */
	for (index = 0; index < PALB_PDU_CONFIG_TAB_SIZE; index++) {
		if (aPduId == palb_EthPduIdConfigTab[index].pduId) {
			aMsgId = palb_EthPduIdConfigTab[index].msgId;
		}
	}

	return aMsgId;
}

/**
 *  The function palb_GetPduId() provides the pdu id mapped to
 *  corresponding message id from the configured table palb_EthPduId2MsgIdTab.
 *
 *  @param  aMsgId - Message id according to manual configuration
 *
 *  @return PduId - Corresponding PduId mapped.
 *
 */
static BapCanMsgId_t palb_GetPduId(const uint32_t aMsgId) {
	BapCanMsgId_t PduId = BAP_MAX_UINT_8;
	uint8_t index;

	/* search entry in palb_EthPduId2MsgIdTab */
	for (index = 0; index < PALB_PDU_CONFIG_TAB_SIZE; index++) {
		if (aMsgId == palb_EthPduIdConfigTab[index].msgId) {
			PduId = palb_EthPduIdConfigTab[index].pduId;
		}
	}

	return PduId;
}

/**
 *  The function palb_GetTxHandleByPdu() provides the index of the array of
 *  transmit buffers for corresponding PDU ID.
 *
 *  @param  aPduId - Pdu id to be transmitted, according to configuration
 *
 *  @return retval - Index of the array of transmit buffers
 *
 */
static uint8_t palb_GetTxHandleByPdu(uint8_t aPduId) {
	uint8_t u8Index;
	uint8_t retval = BAP_MAX_UINT_8;
	/* search entry in palb_EthPduId2MsgIdTab */
	for (u8Index = (uint8_t) 0; u8Index < PALB_PDU_CONFIG_TAB_SIZE; u8Index++) {
		if (palb_EthPduIdConfigTab[u8Index].pduId == aPduId) {
			retval = u8Index;
		}
	}

	return retval;
}

/**
 *  The function palb_GetRxChnlNumByPdu() provides the interface channel number
 *  specified in BAP configuration for the currently received PDU ID.
 *
 *  @param  aPduId - Pdu id received
 *
 *  @return retval - Interface channel number
 *
 */
static uint8_t palb_GetRxChnlNumByPdu(uint16_t aPduId) {
	uint8_t u8Index;
	uint8_t retval = BAP_MAX_UINT_8;

	/* search entry in palb_EthPduId2MsgIdTab */
	for (u8Index = (uint8_t) 0; u8Index < PALB_PDU_CONFIG_TAB_SIZE; u8Index++) {
		if (palb_EthPduIdConfigTab[u8Index].pduId == aPduId) {
			retval = palb_EthPduIdConfigTab[u8Index].interfaceChnlNum;
		}
	}

	return retval;
}
