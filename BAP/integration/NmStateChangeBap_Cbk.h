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
 *  Callback header file with NM state change notification function
 *  declaration
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
 * 2019-07-04   1.11.0      KUL         [SSWPPB-27] Creation of first version
 *
 ******************************************************************/


/* double include prevention */
#ifndef _NMSTATECHANGE_BAP_CBK_H
# define _NMSTATECHANGE_BAP_CBK_H


/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 *  Nm_StateChangeNotification()
 *********************************************************************************************************************/
/*! \brief       Callback to be called by Nm module when an Nm state change has occured.
 *  \param[in]   nmNetworkHandle       Identification of the NM-channel
 *  \param[in]   nmPreviousState       Previous (old) state of the NM-channel 
 *  \param[in]   nmCurrentState        Current (new) state of the NM-channel 
 *********************************************************************************************************************/
extern void BAP_Nm_StateChangeIndication ( const NetworkHandleType nmNetworkHandle,
                                                 const Nm_StateType nmPreviousState,
                                                 const Nm_StateType nmCurrentState);
                                       

#endif /* _NMSTATECHANGE_BAP_CBK_H */


/**********************************************************************************************************************
 *  END OF FILE: NmStateChangeBap_Cbk.h
 *********************************************************************************************************************/
