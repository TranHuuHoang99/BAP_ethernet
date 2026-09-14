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
 * Generiert am:    10.08.2026
 *           um:    09:46:34
 * Quelldatei:      C:\workspace\docs\8255_antona_1000\BAP\BAP_v1.12.2_Distribution_2023-10-10\Distribution\POC_8255\input\BAP_SW1.12_ICC_MQBevo_V2_187.xml
 * Zieldatei:       C:\workspace\docs\8255_antona_1000\BAP\BAP_v1.12.2_Distribution_2023-10-10\Distribution\POC_8255\output\palb_cfg_project.h
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

#define BAP_ACC_ASG_01_MSGID                    1
#define BAP_AWV_ASG_01_MSGID                    2
#define BAP_Audio_FSG_03_MSGID                  3
#define BAP_Aussenlicht_ASG_01_MSGID            4
#define BAP_BC_ASG_01_MSGID                     5
#define BAP_BCmE_ASG_02_MSGID                   6
#define BAP_BSMOIS2_ASG_01_MSGID                7
#define BAP_BSMOIS3_ASG_01_MSGID                8
#define BAP_BSMOIS_ASG_01_MSGID                 9
#define BAP_BatteryControl_ASG_01_MSGID         10
#define BAP_Brake_ASG_01_MSGID                  11
#define BAP_California_ASG_01_MSGID             12
#define BAP_Car2X_ASG_03_MSGID                  13
#define BAP_Charisma_ASG_01_MSGID               14
#define BAP_DisplayConfig_ASG_01_MSGID          15
#define BAP_Doorlocking_ASG_01_MSGID            16
#define BAP_ENI2_ASG_01_MSGID                   17
#define BAP_ENI2_ASG_02_MSGID                   18
#define BAP_ENI_ASG_01_MSGID                    19
#define BAP_ENI_ASG_02_MSGID                    20
#define BAP_EfficiencyAssist_ASG_01_MSGID       21
#define BAP_Einheiten_ASG_01_MSGID              22
#define BAP_EngFunctions_ASG_01_MSGID           23
#define BAP_FAS_Profiles_ASG_01_MSGID           24
#define BAP_HUD_ASG_01_MSGID                    25
#define BAP_Homelink_ASG_01_MSGID               26
#define BAP_Hybrid_ASG_01_MSGID                 27
#define BAP_IAA_PSO2_ASG_01_MSGID               28
#define BAP_InfoSettings_FSG_01_MSGID           29
#define BAP_InfoSettings_FSG_02_MSGID           30
#define BAP_Innenlicht_ASG_01_MSGID             31
#define BAP_Klima1_ASG_01_MSGID                 32
#define BAP_Klima2_ASG_01_MSGID                 33
#define BAP_KlimaMaster_ASG_01_MSGID            34
#define BAP_LDW_ASG_01_MSGID                    35
#define BAP_MFL_FSG_01_MSGID                    36
#define BAP_MKE_ASG_01_MSGID                    37
#define BAP_Mirror_ASG_01_MSGID                 38
#define BAP_MobDevKey_ASG_01_MSGID              39
#define BAP_Navigation_FSG_03_MSGID             40
#define BAP_OPS_ASG_01_MSGID                    41
#define BAP_OPS_ASG_08_MSGID                    42
#define BAP_OnlineFunction_FSG_01_MSGID         43
#define BAP_PaCo_ASG_01_MSGID                   44
#define BAP_ParkHeater_ASG_01_MSGID             45
#define BAP_PlugAndCharge_ASG_02_MSGID          46
#define BAP_RDK_ASG_01_MSGID                    47
#define BAP_RVC_ASG_01_MSGID                    48
#define BAP_RangeData_ASG_01_MSGID              49
#define BAP_RollingAbility_ASG_01_MSGID         50
#define BAP_RushhourPilot_ASG_01_MSGID          51
#define BAP_SDS_FSG_02_MSGID                    52
#define BAP_SIA_ASG_01_MSGID                    53
#define BAP_SLCView_ASG_01_MSGID                54
#define BAP_SWA_ASG_01_MSGID                    55
#define BAP_SeatPneumatic_ASG_01_MSGID          56
#define BAP_Sitz1_ASG_01_MSGID                  57
#define BAP_Sitz2_ASG_01_MSGID                  58
#define BAP_Statistics_ASG_01_MSGID             59
#define BAP_Sunroof_ASG_01_MSGID                60
#define BAP_TPA_ASG_02_MSGID                    61
#define BAP_Telefon_FSG_03_MSGID                62
#define BAP_TrailerAssist_ASG_01_MSGID          63
#define BAP_Uhrzeit_ASG_01_MSGID                64
#define BAP_VZA_ASG_01_MSGID                    65
#define BAP_Wiper_ASG_01_MSGID                  66
#define BAP_eCall_ASG_01_MSGID                  67

/*Rx MSG IDs*/

#define BAP_SLCView_FSG_01_MSGID                68
#define BAP_PlugAndCharge_FSG_02_MSGID          69
#define BAP_MobDevKey_FSG_01_MSGID              70
#define BAP_IAA_PSO2_FSG_01_MSGID               71
#define BAP_Car2X_FSG_03_MSGID                  72
#define BAP_PaCo_FSG_01_MSGID                   73
#define BAP_LDW_FSG_01_MSGID                    74
#define BAP_Sitz2_FSG_01_MSGID                  75
#define BAP_Sitz1_FSG_01_MSGID                  76
#define BAP_AWV_FSG_01_MSGID                    77
#define BAP_ACC_FSG_01_MSGID                    78
#define BAP_SDS_ASG_02_MSGID                    79
#define BAP_Telefon_ASG_07_MSGID                80
#define BAP_Telefon_ASG_08_MSGID                81
#define BAP_Audio_ASG_07_MSGID                  82
#define BAP_Navigation_ASG_07_MSGID             83
#define BAP_Navigation_ASG_08_MSGID             84
#define BAP_RollingAbility_FSG_01_MSGID         85
#define BAP_Klima1_FSG_01_MSGID                 86
#define BAP_Klima2_FSG_01_MSGID                 87
#define BAP_HUD_FSG_01_MSGID                    88
#define BAP_RDK_FSG_01_MSGID                    89
#define BAP_Innenlicht_FSG_01_MSGID             90
#define BAP_Aussenlicht_FSG_01_MSGID            91
#define BAP_OPS_FSG_01_MSGID                    92
#define BAP_OPS_FSG_02_MSGID                    93
#define BAP_Wiper_FSG_01_MSGID                  94
#define BAP_Mirror_FSG_01_MSGID                 95
#define BAP_BC_FSG_01_MSGID                     96
#define BAP_BC_FSG_02_MSGID                     97
#define BAP_Uhrzeit_FSG_01_MSGID                98
#define BAP_SIA_FSG_01_MSGID                    99
#define BAP_Einheiten_FSG_01_MSGID              100
#define BAP_Charisma_FSG_01_MSGID               101
#define BAP_Hybrid_FSG_01_MSGID                 102
#define BAP_VZA_FSG_01_MSGID                    103
#define BAP_MKE_FSG_01_MSGID                    104
#define BAP_BatteryControl_FSG_01_MSGID         105
#define BAP_BCmE_FSG_01_MSGID                   106
#define BAP_OnlineFunction_ASG_01_MSGID         107
#define BAP_OnlineFunction_ASG_02_MSGID         108
#define BAP_MFL_ASG_01_MSGID                    109
#define BAP_ENI_FSG_02_MSGID                    110
#define BAP_ENI_FSG_01_MSGID                    111
#define BAP_RangeData_FSG_01_MSGID              112
#define BAP_EfficiencyAssist_FSG_01_MSGID       113
#define BAP_SeatPneumatic_FSG_01_MSGID          114
#define BAP_KlimaMaster_FSG_01_MSGID            115
#define BAP_FAS_Profiles_FSG_01_MSGID           116
#define BAP_TPA_FSG_01_MSGID                    117
#define BAP_EngFunctions_FSG_01_MSGID           118
#define BAP_ParkHeater_FSG_01_MSGID             119
#define BAP_Homelink_FSG_01_MSGID               120
#define BAP_TrailerAssist_FSG_01_MSGID          121
#define BAP_Statistics_FSG_01_MSGID             122
#define BAP_Brake_FSG_01_MSGID                  123
#define BAP_RVC_FSG_01_MSGID                    124
#define BAP_Doorlocking_FSG_01_MSGID            125
#define BAP_SWA_FSG_01_MSGID                    126
#define BAP_InfoSettings_ASG_03_MSGID           127
#define BAP_InfoSettings_ASG_02_MSGID           128
#define BAP_InfoSettings_ASG_01_MSGID           129
#define BAP_ENI2_FSG_02_MSGID                   130
#define BAP_ENI2_FSG_01_MSGID                   131
#define BAP_eCall_FSG_01_MSGID                  132
#define BAP_DisplayConfig_FSG_01_MSGID          133
#define BAP_SDS_ASG_03_MSGID                    134
#define BAP_Audio_ASG_08_MSGID                  135
#define BAP_OPS_FSG_03_MSGID                    136
#define BAP_Sunroof_FSG_01_MSGID                137
#define BAP_RushhourPilot_FSG_01_MSGID          138
#define BAP_BSMOIS3_FSG_01_MSGID                139
#define BAP_BSMOIS2_FSG_01_MSGID                140
#define BAP_BSMOIS_FSG_01_MSGID                 141
#define BAP_California_FSG_01_MSGID             142


#endif /* PALB_CFG_PROJECT_H */
