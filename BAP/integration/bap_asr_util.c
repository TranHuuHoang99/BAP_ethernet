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
 * This module implements NM state change indication callback. 
 * This function is an interface for integrator to implement any 
 * LSG specific logic. [SSWPPB-27]
 *
 ******************************************************************
 *
 * Versionsgeschichte (ohne SCM)
 *
 * Datum        Version     Author      Beschreibung
 * ----------------------------------------------------------------
 * 2023-10-10	1.12.2		DRH			[EEARCH-35935] Release preparation, adapt Copyright date and version number.
 * 2023-06-06   1.12.1      DRH         [EEARCH-32697] Fix missing BAP-Start for NM_STATE_PREPARE_BUS_SLEEP
 * 2022-10-21	1.12.1		DRH			[SSWPPB-296] Release preparation, adapt Copyright date and version number.
 * 2022-06-17	1.12.0		DRH			[SSWPPB-269] Release preparation, adapt Copyright date and version number.
 * 2021-12-07	1.11.3		JEO			[SSWPPB-244] Release preparation, adapt Copyright date and version number.
 * 2019-07-04   1.11.0      KUL         [SSWPPB-27] BAP-Wrapper - generische Schnittstelle zum NM
 *
 ******************************************************************/
#include "Nm.h"
#include "bap_util.h"

void BAP_Nm_StateChangeIndication ( const NetworkHandleType nmNetworkHandle,
                                          const Nm_StateType nmPreviousState,
                                          const Nm_StateType nmCurrentState)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* BapNmFlags array index are mapped to LSG ids manually. There is one 
     flag per LSG.
     The indexes are mapped one-to-one with the sequence of LSG ids from
     the BAP Config XML. In this example, there are 18 LSGs configured.
     Mapping BapNmFlags array index -> LSG ids shown in comments below.
  */
  switch (nmCurrentState)
  {
    case NM_STATE_REPEAT_MESSAGE:
      /* Transition: BS -> RM */
      if (((NM_STATE_BUS_SLEEP == nmPreviousState) || NM_STATE_PREPARE_BUS_SLEEP == nmPreviousState)) && (0u==nmNetworkHandle))
      {
        /* Let the Appl decide on LSG start/shutdown */
        BapNmFlags[0]=1u;        /* Flag for LSG id 1   */
        BapNmFlags[1]=1u;        /* Flag for LSG id 3   */
        BapNmFlags[2]=1u;        /* Flag for LSG id 9   */
        BapNmFlags[3]=1u;        /* Flag for LSG id 10  */
        BapNmFlags[4]=1u;        /* Flag for LSG id 13  */
        BapNmFlags[5]=1u;        /* Flag for LSG id 17  */
        BapNmFlags[6]=1u;        /* Flag for LSG id 19  */
        BapNmFlags[7]=1u;        /* Flag for LSG id 25  */
        BapNmFlags[8]=1u;        /* Flag for LSG id 27  */
        BapNmFlags[9]=1u;        /* Flag for LSG id 29  */
        BapNmFlags[10]=1u;       /* Flag for LSG id 33  */
        BapNmFlags[11]=1u;       /* Flag for LSG id 35  */
        BapNmFlags[12]=1u;       /* Flag for LSG id 41  */
        BapNmFlags[13]=1u;       /* Flag for LSG id 45  */
        BapNmFlags[14]=1u;       /* Flag for LSG id 111 */
        BapNmFlags[15]=1u;       /* Flag for LSG id 112 */
        BapNmFlags[16]=1u;       /* Flag for LSG id 113 */
        BapNmFlags[17]=1u;       /* Flag for LSG id 200 */
      }
      break;
    case NM_STATE_BUS_SLEEP:
      /* Transition: PBS -> BS */
      if ((NM_STATE_PREPARE_BUS_SLEEP == nmPreviousState) && (0u==nmNetworkHandle))
      { 
        /* Force shutdown LSGs, ignore application's request for BAP_Start(lsg_id) */
        BapNmFlags[0]=0u;
        BapNmFlags[1]=0u;
        BapNmFlags[2]=0u;
        BapNmFlags[3]=0u;
        BapNmFlags[4]=0u;
        BapNmFlags[5]=0u;
        BapNmFlags[6]=0u;
        BapNmFlags[7]=0u;
        BapNmFlags[8]=0u;
        BapNmFlags[9]=0u;
        BapNmFlags[10]=0u;
        BapNmFlags[11]=0u;
        BapNmFlags[12]=0u;
        BapNmFlags[13]=0u;
        BapNmFlags[14]=0u;
        BapNmFlags[15]=0u;
        BapNmFlags[16]=0u;
        BapNmFlags[17]=0u;
      }
      break;
    default:
      /* Do nothing */
      break;
  }
}
