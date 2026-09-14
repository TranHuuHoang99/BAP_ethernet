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
 * Generiert am:    10.08.2026
 *           um:    09:46:34
 * Quelldatei:      C:\workspace\docs\8255_antona_1000\BAP\BAP_v1.12.2_Distribution_2023-10-10\Distribution\POC_8255\input\BAP_SW1.12_ICC_MQBevo_V2_187.xml
 * Zieldatei:       C:\workspace\docs\8255_antona_1000\BAP\BAP_v1.12.2_Distribution_2023-10-10\Distribution\POC_8255\output\palb_cfg.c
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
	{BAP_ACC_ASG_01,            BAP_ACC_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_AWV_ASG_01,            BAP_AWV_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Audio_FSG_03,            BAP_Audio_FSG_03_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Aussenlicht_ASG_01,            BAP_Aussenlicht_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_BC_ASG_01,            BAP_BC_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_BCmE_ASG_02,            BAP_BCmE_ASG_02_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_BSMOIS2_ASG_01,            BAP_BSMOIS2_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_BSMOIS3_ASG_01,            BAP_BSMOIS3_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_BSMOIS_ASG_01,            BAP_BSMOIS_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_BatteryControl_ASG_01,            BAP_BatteryControl_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Brake_ASG_01,            BAP_Brake_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_California_ASG_01,            BAP_California_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Car2X_ASG_03,            BAP_Car2X_ASG_03_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Charisma_ASG_01,            BAP_Charisma_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_DisplayConfig_ASG_01,            BAP_DisplayConfig_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Doorlocking_ASG_01,            BAP_Doorlocking_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_ENI2_ASG_01,            BAP_ENI2_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_ENI2_ASG_02,            BAP_ENI2_ASG_02_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_ENI_ASG_01,            BAP_ENI_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_ENI_ASG_02,            BAP_ENI_ASG_02_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_EfficiencyAssist_ASG_01,            BAP_EfficiencyAssist_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Einheiten_ASG_01,            BAP_Einheiten_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_EngFunctions_ASG_01,            BAP_EngFunctions_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_FAS_Profiles_ASG_01,            BAP_FAS_Profiles_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_HUD_ASG_01,            BAP_HUD_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Homelink_ASG_01,            BAP_Homelink_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Hybrid_ASG_01,            BAP_Hybrid_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_IAA_PSO2_ASG_01,            BAP_IAA_PSO2_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_InfoSettings_FSG_01,            BAP_InfoSettings_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_InfoSettings_FSG_02,            BAP_InfoSettings_FSG_02_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Innenlicht_ASG_01,            BAP_Innenlicht_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Klima1_ASG_01,            BAP_Klima1_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Klima2_ASG_01,            BAP_Klima2_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_KlimaMaster_ASG_01,            BAP_KlimaMaster_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_LDW_ASG_01,            BAP_LDW_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_MFL_FSG_01,            BAP_MFL_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_MKE_ASG_01,            BAP_MKE_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Mirror_ASG_01,            BAP_Mirror_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_MobDevKey_ASG_01,            BAP_MobDevKey_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Navigation_FSG_03,            BAP_Navigation_FSG_03_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_OPS_ASG_01,            BAP_OPS_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_OPS_ASG_08,            BAP_OPS_ASG_08_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_OnlineFunction_FSG_01,            BAP_OnlineFunction_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_PaCo_ASG_01,            BAP_PaCo_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_ParkHeater_ASG_01,            BAP_ParkHeater_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_PlugAndCharge_ASG_02,            BAP_PlugAndCharge_ASG_02_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_RDK_ASG_01,            BAP_RDK_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_RVC_ASG_01,            BAP_RVC_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_RangeData_ASG_01,            BAP_RangeData_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_RollingAbility_ASG_01,            BAP_RollingAbility_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_RushhourPilot_ASG_01,            BAP_RushhourPilot_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_SDS_FSG_02,            BAP_SDS_FSG_02_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_SIA_ASG_01,            BAP_SIA_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_SLCView_ASG_01,            BAP_SLCView_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_SWA_ASG_01,            BAP_SWA_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_SeatPneumatic_ASG_01,            BAP_SeatPneumatic_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Sitz1_ASG_01,            BAP_Sitz1_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Sitz2_ASG_01,            BAP_Sitz2_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Statistics_ASG_01,            BAP_Statistics_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Sunroof_ASG_01,            BAP_Sunroof_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_TPA_ASG_02,            BAP_TPA_ASG_02_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Telefon_FSG_03,            BAP_Telefon_FSG_03_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_TrailerAssist_ASG_01,            BAP_TrailerAssist_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Uhrzeit_ASG_01,            BAP_Uhrzeit_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_VZA_ASG_01,            BAP_VZA_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Wiper_ASG_01,            BAP_Wiper_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_eCall_ASG_01,            BAP_eCall_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_SLCView_FSG_01,            BAP_SLCView_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_PlugAndCharge_FSG_02,            BAP_PlugAndCharge_FSG_02_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_MobDevKey_FSG_01,            BAP_MobDevKey_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_IAA_PSO2_FSG_01,            BAP_IAA_PSO2_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Car2X_FSG_03,            BAP_Car2X_FSG_03_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_PaCo_FSG_01,            BAP_PaCo_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_LDW_FSG_01,            BAP_LDW_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Sitz2_FSG_01,            BAP_Sitz2_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Sitz1_FSG_01,            BAP_Sitz1_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_AWV_FSG_01,            BAP_AWV_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_ACC_FSG_01,            BAP_ACC_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_SDS_ASG_02,            BAP_SDS_ASG_02_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Telefon_ASG_07,            BAP_Telefon_ASG_07_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Telefon_ASG_08,            BAP_Telefon_ASG_08_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Audio_ASG_07,            BAP_Audio_ASG_07_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Navigation_ASG_07,            BAP_Navigation_ASG_07_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Navigation_ASG_08,            BAP_Navigation_ASG_08_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_RollingAbility_FSG_01,            BAP_RollingAbility_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Klima1_FSG_01,            BAP_Klima1_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Klima2_FSG_01,            BAP_Klima2_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_HUD_FSG_01,            BAP_HUD_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_RDK_FSG_01,            BAP_RDK_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Innenlicht_FSG_01,            BAP_Innenlicht_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Aussenlicht_FSG_01,            BAP_Aussenlicht_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_OPS_FSG_01,            BAP_OPS_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_OPS_FSG_02,            BAP_OPS_FSG_02_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Wiper_FSG_01,            BAP_Wiper_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Mirror_FSG_01,            BAP_Mirror_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_BC_FSG_01,            BAP_BC_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_BC_FSG_02,            BAP_BC_FSG_02_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Uhrzeit_FSG_01,            BAP_Uhrzeit_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_SIA_FSG_01,            BAP_SIA_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Einheiten_FSG_01,            BAP_Einheiten_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Charisma_FSG_01,            BAP_Charisma_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Hybrid_FSG_01,            BAP_Hybrid_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_VZA_FSG_01,            BAP_VZA_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_MKE_FSG_01,            BAP_MKE_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_BatteryControl_FSG_01,            BAP_BatteryControl_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_BCmE_FSG_01,            BAP_BCmE_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_OnlineFunction_ASG_01,            BAP_OnlineFunction_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_OnlineFunction_ASG_02,            BAP_OnlineFunction_ASG_02_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_MFL_ASG_01,            BAP_MFL_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_ENI_FSG_02,            BAP_ENI_FSG_02_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_ENI_FSG_01,            BAP_ENI_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_RangeData_FSG_01,            BAP_RangeData_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_EfficiencyAssist_FSG_01,            BAP_EfficiencyAssist_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_SeatPneumatic_FSG_01,            BAP_SeatPneumatic_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_KlimaMaster_FSG_01,            BAP_KlimaMaster_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_FAS_Profiles_FSG_01,            BAP_FAS_Profiles_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_TPA_FSG_01,            BAP_TPA_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_EngFunctions_FSG_01,            BAP_EngFunctions_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_ParkHeater_FSG_01,            BAP_ParkHeater_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Homelink_FSG_01,            BAP_Homelink_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_TrailerAssist_FSG_01,            BAP_TrailerAssist_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Statistics_FSG_01,            BAP_Statistics_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Brake_FSG_01,            BAP_Brake_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_RVC_FSG_01,            BAP_RVC_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Doorlocking_FSG_01,            BAP_Doorlocking_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_SWA_FSG_01,            BAP_SWA_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_InfoSettings_ASG_03,            BAP_InfoSettings_ASG_03_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_InfoSettings_ASG_02,            BAP_InfoSettings_ASG_02_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_InfoSettings_ASG_01,            BAP_InfoSettings_ASG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_ENI2_FSG_02,            BAP_ENI2_FSG_02_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_ENI2_FSG_01,            BAP_ENI2_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_eCall_FSG_01,            BAP_eCall_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_DisplayConfig_FSG_01,            BAP_DisplayConfig_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_SDS_ASG_03,            BAP_SDS_ASG_03_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Audio_ASG_08,            BAP_Audio_ASG_08_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_OPS_FSG_03,            BAP_OPS_FSG_03_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_Sunroof_FSG_01,            BAP_Sunroof_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_RushhourPilot_FSG_01,            BAP_RushhourPilot_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_BSMOIS3_FSG_01,            BAP_BSMOIS3_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_BSMOIS2_FSG_01,            BAP_BSMOIS2_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_BSMOIS_FSG_01,            BAP_BSMOIS_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20},
	{BAP_California_FSG_01,            BAP_California_FSG_01_MSGID,            (BapCanInterfaceChannel_t) 20}
};


/* Internal makro definitions */

/* Internal type definitions */

/* Internal const deklarations */

/* Internal static variables */

/* static function declarations */

/* Definition (Implementation) of static functions */

/* Definition (Implementation) of global functions */



