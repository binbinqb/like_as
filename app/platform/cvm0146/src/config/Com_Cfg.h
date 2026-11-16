/**
 * SSAS - Simple Smart Automotive Software
 * Copyright (C) 2021 Parai Wang <parai@foxmail.com>
 *
 * @generated
 * 本文件由 tools/generator 自动生成，请勿手工修改。
 * 改动请改配置源，然后重新生成；一致性由 tools/a4_gen_check.py 校验。
 */
#ifndef COM_CFG_H
#define COM_CFG_H
/* ================================ [ INCLUDES  ] ============================================== */
/* ================================ [ MACROS    ] ============================================== */
#ifndef COM_CONST
#define COM_CONST
#endif

#ifndef COM_MAIN_FUNCTION_PERIOD
#define COM_MAIN_FUNCTION_PERIOD 10u
#endif
#define COM_CONVERT_MS_TO_MAIN_CYCLES(x) \
  ((x + COM_MAIN_FUNCTION_PERIOD - 1u) / COM_MAIN_FUNCTION_PERIOD)

#define COM_USE_CAN
#define COM_USE_SIGNAL_CONFIG
#define COM_USE_SIGNAL_UPDATE_BIT

#define COM_RX_FOR_CAN1(id, PduInfoPtr) \
  if (0x94F02B54 == id) { \
    Com_RxIndication(COM_CAN1_CRASH_NOTIFICATION_RX, PduInfoPtr); \
  }  else if (0x98FEF500 == id) { \
    Com_RxIndication(COM_CAN1_AMB_AMBIENT_CONDITIONS_RX, PduInfoPtr); \
  }  else if (0x98FF0534 == id) { \
    Com_RxIndication(COM_CAN1_PEPS1_RX, PduInfoPtr); \
  }  else if (0x98FF7534 == id) { \
    Com_RxIndication(COM_CAN1_PEPS2_RX, PduInfoPtr); \
  }  else if (0x90FFB634 == id) { \
    Com_RxIndication(COM_CAN1_PEPS_ESCLM_RX, PduInfoPtr); \
  }  else if (0x98EEFF00 == id) { \
    Com_RxIndication(COM_CAN1_ACL_RX, PduInfoPtr); \
  }  else if (0x8CFD9200 == id) { \
    Com_RxIndication(COM_CAN1_EOI_RX, PduInfoPtr); \
  }  else if (0x98F00503 == id) { \
    Com_RxIndication(COM_CAN1_ETC2_RX, PduInfoPtr); \
  }  else if (0x90FFB04D == id) { \
    Com_RxIndication(COM_CAN1_ESCL1_RX, PduInfoPtr); \
  }  else if (0x90FFB24D == id) { \
    Com_RxIndication(COM_CAN1_ESCLM_PEPS_RX, PduInfoPtr); \
  }  else if (0x98FF904D == id) { \
    Com_RxIndication(COM_CAN1_ESCL_NM_RX, PduInfoPtr); \
  }  else if (0x98FF0CEC == id) { \
    Com_RxIndication(COM_CAN1_DW_STATE_RX, PduInfoPtr); \
  }  else if (0x98FF0917 == id) { \
    Com_RxIndication(COM_CAN1_IC_MSG_RX, PduInfoPtr); \
  }  else if (0x8CF00400 == id) { \
    Com_RxIndication(COM_CAN1_EEC1_ELECTRONIC_ENGINE_CONTROLLER_1_RX, PduInfoPtr); \
  }  else if (0x98FEF121 == id) { \
    Com_RxIndication(COM_CAN1_CCVS_RX, PduInfoPtr); \
  }  else if (0x98FF12EF == id) { \
    Com_RxIndication(COM_CAN1_VCU_4_RX, PduInfoPtr); \
  }  else if (0x8CFE6CEE == id) { \
    Com_RxIndication(COM_CAN1_TCO1_RX, PduInfoPtr); \
  }  else if (0x98FEF433 == id) { \
    Com_RxIndication(COM_CAN1_TIRE_CONDITION_RX, PduInfoPtr); \
  }  else if (0x98FECA33 == id) { \
    Com_RxIndication(COM_CAN1_DM1_TPMS_RX, PduInfoPtr); \
  }  else if (0x98F0010B == id) { \
    Com_RxIndication(COM_CAN1_EBC1_ELECTRONIC_BRAKE_CONTROLLER_1_RX, PduInfoPtr); \
  }  else if (0x98FDC40B == id) { \
    Com_RxIndication(COM_CAN1_EBC5_ELECTRONIC_BRAKE_CONTROLLER_5_RX, PduInfoPtr); \
  }  else if (0x98FD0700 == id) { \
    Com_RxIndication(COM_CAN1_DLCC1_DIRECT_LAMP_CONTROL_COMMAND_1_RX, PduInfoPtr); \
  }  else if (0x98FEF100 == id) { \
    Com_RxIndication(COM_CAN1_CCVS1_CRUISE_CONTROL_VEHICLE_SPEED_1_RX, PduInfoPtr); \
  }  else if (0x98FE4F0B == id) { \
    Com_RxIndication(COM_CAN1_VDC1_VEHICLE_DYNAMIC_STABILITY_CONTROL_1_RX, PduInfoPtr); \
  }  else if (0x98F0000F == id) { \
    Com_RxIndication(COM_CAN1_ERC1_RX, PduInfoPtr); \
  }  else if (0x98F00000 == id) { \
    Com_RxIndication(COM_CAN1_ERC3_RX, PduInfoPtr); \
  }  else if (0x9CFEC321 == id) { \
    Com_RxIndication(COM_CAN1_ETC5_RX, PduInfoPtr); \
  }  else if (0x98FFBA19 == id) { \
    Com_RxIndication(COM_CAN1_EEC3_RX, PduInfoPtr); \
  }  else if (0x98FFBC19 == id) { \
    Com_RxIndication(COM_CAN1_ECC2_RX, PduInfoPtr); \
  }  else if (0x98FF4C56 == id) { \
    Com_RxIndication(COM_CAN1_ID1_RX, PduInfoPtr); \
  }  else if (0x98FF4D56 == id) { \
    Com_RxIndication(COM_CAN1_ID2_RX, PduInfoPtr); \
  }  else if (0x98FF4E56 == id) { \
    Com_RxIndication(COM_CAN1_ID3_RX, PduInfoPtr); \
  }  else if (0x9CECFF21 == id) { \
    Com_RxIndication(COM_CAN1_TP_CM_RX, PduInfoPtr); \
  }  else if (0x9CEBFF21 == id) { \
    Com_RxIndication(COM_CAN1_TP_DT_RX, PduInfoPtr); \
  }

#define COM_RX_FOR_CANTEST(id, PduInfoPtr) \
  if (0x201 == id) { \
    Com_RxIndication(COM_CANTEST_RX_TEST, PduInfoPtr); \
  }

#ifndef COM_ECUC_PDUID_OFFSET
#define COM_ECUC_PDUID_OFFSET 0
#endif

/* NOTE: manually modify to fix it to the right HTH */
#define COM_ECUC_CAN1_PDUID_MIN COM_ECUC_PDUID_OFFSET
#define COM_ECUC_CAN1_PDUID_MAX COM_ECUC_PDUID_OFFSET + 40
#define COM_TX_FOR_CAN1(TxPduId, dlPdu, PduInfoPtr, ret) \
  if ((COM_CAN1_BCM_LCSF_TX+COM_ECUC_PDUID_OFFSET) == TxPduId) { \
    dlPdu.id = 0x98FE4021; \
    ret = Can_Write(0, &dlPdu); \
  }  else if ((COM_CAN1_BCM_CTRL_TX+COM_ECUC_PDUID_OFFSET) == TxPduId) { \
    dlPdu.id = 0x98FF0C21; \
    ret = Can_Write(0, &dlPdu); \
  }  else if ((COM_CAN1_BCM_OEL_TX+COM_ECUC_PDUID_OFFSET) == TxPduId) { \
    dlPdu.id = 0x8CFDCC21; \
    ret = Can_Write(0, &dlPdu); \
  }  else if ((COM_CAN1_BCM_OWW_TX+COM_ECUC_PDUID_OFFSET) == TxPduId) { \
    dlPdu.id = 0x98FDCD21; \
    ret = Can_Write(0, &dlPdu); \
  }  else if ((COM_CAN1_BCM_DOOR_CTRL_TX+COM_ECUC_PDUID_OFFSET) == TxPduId) { \
    dlPdu.id = 0x98FE4E21; \
    ret = Can_Write(0, &dlPdu); \
  }  else if ((COM_CAN1_BCM_DM1_TX+COM_ECUC_PDUID_OFFSET) == TxPduId) { \
    dlPdu.id = 0x98FECA21; \
    ret = Can_Write(0, &dlPdu); \
  }

/* NOTE: manually modify to fix it to the right HTH */
#define COM_ECUC_CANTEST_PDUID_MIN COM_ECUC_CAN1_PDUID_MAX
#define COM_ECUC_CANTEST_PDUID_MAX COM_ECUC_CAN1_PDUID_MAX + 2
#define COM_TX_FOR_CANTEST(TxPduId, dlPdu, PduInfoPtr, ret) \
  if ((COM_CANTEST_TX_TEST+COM_ECUC_PDUID_OFFSET) == TxPduId) { \
    dlPdu.id = 0x200; \
    ret = Can_Write(1, &dlPdu); \
  }

/* messages for network CAN1 */
#define COM_CAN1_BCM_LCSF_TX 0
#define COM_CAN1_BCM_CTRL_TX 1
#define COM_CAN1_BCM_OEL_TX 2
#define COM_CAN1_BCM_OWW_TX 3
#define COM_CAN1_BCM_DOOR_CTRL_TX 4
#define COM_CAN1_BCM_DM1_TX 5
#define COM_CAN1_CRASH_NOTIFICATION_RX 6
#define COM_CAN1_AMB_AMBIENT_CONDITIONS_RX 7
#define COM_CAN1_PEPS1_RX 8
#define COM_CAN1_PEPS2_RX 9
#define COM_CAN1_PEPS_ESCLM_RX 10
#define COM_CAN1_ACL_RX 11
#define COM_CAN1_EOI_RX 12
#define COM_CAN1_ETC2_RX 13
#define COM_CAN1_ESCL1_RX 14
#define COM_CAN1_ESCLM_PEPS_RX 15
#define COM_CAN1_ESCL_NM_RX 16
#define COM_CAN1_DW_STATE_RX 17
#define COM_CAN1_IC_MSG_RX 18
#define COM_CAN1_EEC1_ELECTRONIC_ENGINE_CONTROLLER_1_RX 19
#define COM_CAN1_CCVS_RX 20
#define COM_CAN1_VCU_4_RX 21
#define COM_CAN1_TCO1_RX 22
#define COM_CAN1_TIRE_CONDITION_RX 23
#define COM_CAN1_DM1_TPMS_RX 24
#define COM_CAN1_EBC1_ELECTRONIC_BRAKE_CONTROLLER_1_RX 25
#define COM_CAN1_EBC5_ELECTRONIC_BRAKE_CONTROLLER_5_RX 26
#define COM_CAN1_DLCC1_DIRECT_LAMP_CONTROL_COMMAND_1_RX 27
#define COM_CAN1_CCVS1_CRUISE_CONTROL_VEHICLE_SPEED_1_RX 28
#define COM_CAN1_VDC1_VEHICLE_DYNAMIC_STABILITY_CONTROL_1_RX 29
#define COM_CAN1_ERC1_RX 30
#define COM_CAN1_ERC3_RX 31
#define COM_CAN1_ETC5_RX 32
#define COM_CAN1_EEC3_RX 33
#define COM_CAN1_ECC2_RX 34
#define COM_CAN1_ID1_RX 35
#define COM_CAN1_ID2_RX 36
#define COM_CAN1_ID3_RX 37
#define COM_CAN1_TP_CM_RX 38
#define COM_CAN1_TP_DT_RX 39

/* messages for network CANTEST */
#define COM_CANTEST_TX_TEST 40
#define COM_CANTEST_RX_TEST 41

/* signals for network CAN1 */
/* signals for network CAN1 message BCM_LCSF_TX: id=0x98fe4021 dlc=8, dir=TX */
#define COM_SID_BCM_LowBeamSts 0 /* little 2@4 */
#define COM_SID_BCM_HighBeamSts 1 /* little 2@6 */
#define COM_SID_BCM_FrontFogSts 2 /* little 2@8 */
#define COM_SID_BCM_TurnRLightSts 3 /* little 2@12 */
#define COM_SID_BCM_TurnLLightSts 4 /* little 2@14 */
#define COM_SID_BCM_DRLSts 5 /* little 2@24 */
#define COM_SID_BCM_PositionLightSts 6 /* little 2@30 */
#define COM_SID_BCM_RearFogSts 7 /* little 2@32 */
#define COM_SID_BackUpLightSt 8 /* little 2@44 */
#define COM_SID_BrakelightST 9 /* little 2@46 */
#define COM_SID_InteriorLampSt 10 /* little 2@48 */

/* signals for network CAN1 message BCM_Ctrl_TX: id=0x98ff0c21 dlc=8, dir=TX */
#define COM_SID_BCM_PassWindowLcokSw 11 /* little 2@0 */
#define COM_SID_CentralLockSw 12 /* little 2@2 */
#define COM_SID_MRightFrontWinSw 13 /* little 2@4 */
#define COM_SID_MLeftFrontWinSw 14 /* little 2@6 */
#define COM_SID_RightFrontWinSw 15 /* little 2@10 */
#define COM_SID_MRightRearWinSw 16 /* little 2@12 */
#define COM_SID_MLeftRearWinSw 17 /* little 2@14 */
#define COM_SID_RightRearWinSw 18 /* little 2@16 */
#define COM_SID_LeftRearWinSw 19 /* little 2@18 */
#define COM_SID_BCM_Ctrl_TX_MechKeySt 20 /* little 2@20 */
#define COM_SID_LeftFrontWinSt 21 /* little 2@22 */
#define COM_SID_RightFrontWinSt 22 /* little 2@24 */
#define COM_SID_LeftRearWinSt 23 /* little 2@26 */
#define COM_SID_RightRearWinSt 24 /* little 2@28 */
#define COM_SID_DoorLockMotorState 25 /* little 2@30 */
#define COM_SID_RemoteDoorState 26 /* little 2@32 */
#define COM_SID_LeftFrontWinErrorSt 27 /* little 2@48 */
#define COM_SID_RightFrontWinErrorSt 28 /* little 2@50 */
#define COM_SID_LeftRearWinErrorSt 29 /* little 2@52 */
#define COM_SID_RightRearWinErrorSt 30 /* little 2@54 */

/* signals for network CAN1 message BCM_OEL_TX: id=0x8cfdcc21 dlc=8, dir=TX */
#define COM_SID_HazardSw 31 /* little 2@12 */
#define COM_SID_HazardSt 32 /* little 2@40 */

/* signals for network CAN1 message BCM_OWW_TX: id=0x98fdcd21 dlc=8, dir=TX */
#define COM_SID_WiperSt 33 /* little 2@8 */

/* signals for network CAN1 message BCM_DoorCtrl_TX: id=0x98fe4e21 dlc=8, dir=TX */
#define COM_SID_SKC_u8PEPSICUIndCnt_WF 34 /* little 2@0 */
#define COM_SID_PRM_u8PEPSICUIndCnt_WF 35 /* little 2@2 */
#define COM_SID_ATP_u8DrvLockRotor_WF 36 /* little 2@4 */
#define COM_SID_ESCL_u8AuthReqCnt_WF 37 /* little 2@6 */
#define COM_SID_BCM_OpenStatusofDdoor 38 /* little 2@8 */
#define COM_SID_BCM_OpenStatusofPdoor 39 /* little 2@10 */
#define COM_SID_BCM_OpenStatusofLeftReardoor 40 /* little 2@12 */
#define COM_SID_BCM_OpenStatusofRightReardoor 41 /* little 2@14 */
#define COM_SID_BASE_u8AuthResultCnt_WF 42 /* little 3@16 */
#define COM_SID_BSW_TPMS_FrameCnt_WF 43 /* little 4@19 */
#define COM_SID_PAM_u8SleepFlag_WF 44 /* little 1@23 */
#define COM_SID_ATP_u8PasLockRotor_WF 45 /* little 2@24 */
#define COM_SID_FEE_APPWriteIdleFlag_WF 46 /* little 2@28 */
#define COM_SID_FEE_BOOTWriteIdleFlag_WF 47 /* little 2@30 */
#define COM_SID_WIN_u8DrvWinCmdCAN_WF 48 /* little 4@32 */
#define COM_SID_WIN_u8PasWinCmdCAN_WF 49 /* little 4@36 */
#define COM_SID_TUL_u8HonkingStyle_WF 50 /* little 4@40 */
#define COM_SID_DLC_u8LockSource_WF 51 /* little 4@44 */
#define COM_SID_HornRelaySt 52 /* little 2@48 */
#define COM_SID_BrakeLightWarning 53 /* little 2@50 */
#define COM_SID_LF_SendCounter_WF 54 /* little 4@56 */
#define COM_SID_LF_Commond_WF 55 /* little 4@60 */

/* signals for network CAN1 message BCM_DM1_TX: id=0x98feca21 dlc=8, dir=TX */
#define COM_SID_DM1_MalfunctionIndicatorLampStatus 56 /* little 2@2 */
#define COM_SID_DM1_RedStopLampState 57 /* little 2@4 */
#define COM_SID_BCM_LeastByteofSPN 58 /* little 8@16 */
#define COM_SID_BCM_SecondByteofSPN 59 /* little 8@24 */
#define COM_SID_BCM_FMI 60 /* little 5@32 */
#define COM_SID_BCM_3MostBitofSPN 61 /* little 3@37 */
#define COM_SID_BCM_OC 62 /* little 7@40 */
#define COM_SID_BCM_CM 63 /* little 1@47 */

/* signals for network CAN1 message Crash_Notification_RX: id=0x94f02b54 dlc=8, dir=RX */
#define COM_SID_SRS_Crash_Type 64 /* little 5@0 */

/* signals for network CAN1 message AMB_Ambient_Conditions_RX: id=0x98fef500 dlc=8, dir=RX */
#define COM_SID_AMB_BarometricPress 65 /* little 8@0 */
#define COM_SID_LFE1_AmbientAirTemp 66 /* little 16@24 */
#define COM_SID_LFE1_EngAirIntakeTemp 67 /* little 8@40 */

/* signals for network CAN1 message PEPS1_RX: id=0x98ff0534 dlc=8, dir=RX */
#define COM_SID_PEPsKeyInState 68 /* little 2@2 */
#define COM_SID_PEPS_PkeLockCmd 69 /* little 4@8 */
#define COM_SID_PEPS_PowerMode 70 /* little 3@21 */
#define COM_SID_PEPS_ESCLInhabitSt 71 /* little 2@24 */
#define COM_SID_PEPS_EmergencyST 72 /* little 2@28 */
#define COM_SID_PEPS_KeyAuthenticationSt_PEPS 73 /* little 2@30 */
#define COM_SID_ESCL_failure 74 /* little 1@32 */
#define COM_SID_PEPS_failure 75 /* little 1@33 */
#define COM_SID_Key_Not_Found 76 /* little 1@34 */
#define COM_SID_Key_Battery_Low 77 /* little 1@35 */
#define COM_SID_PEPS_PEPSICUInd 78 /* little 4@36 */
#define COM_SID_PEPsKeyInFeedback 79 /* little 2@40 */
#define COM_SID_ACC_FB 80 /* little 1@42 */
#define COM_SID_IGN1_FB 81 /* little 1@43 */
#define COM_SID_PEPsKeyOutFeedback 82 /* little 2@46 */
#define COM_SID_Alive_counter 83 /* little 8@48 */
#define COM_SID_PEPS1_RX_CRC 84 /* little 8@56 */

/* signals for network CAN1 message PEPS2_RX: id=0x98ff7534 dlc=8, dir=RX */
#define COM_SID_Key1_Inside_St 85 /* little 1@0 */
#define COM_SID_Key2_Inside_St 86 /* little 1@1 */
#define COM_SID_Key3_Inside_St 87 /* little 1@2 */
#define COM_SID_Key4_Inside_St 88 /* little 1@3 */
#define COM_SID_Key1_Inhibit_St 89 /* little 1@4 */
#define COM_SID_Key2_Inhibit_St 90 /* little 1@5 */
#define COM_SID_Key3_Inhibit_St 91 /* little 1@6 */
#define COM_SID_Key4_Inhibit_St 92 /* little 1@7 */
#define COM_SID_RKE_u8UnlockCounter_WF 93 /* little 4@8 */
#define COM_SID_RKE_u8SearchCounter_WF 94 /* little 4@12 */
#define COM_SID_KE_u8LockCounter_WF 95 /* little 4@16 */
#define COM_SID_PKE_Count_WF 96 /* little 4@20 */
#define COM_SID_WKUPFALG_WF 97 /* little 30@24 */
#define COM_SID_DLC_u8DrvPESts_WF 98 /* little 1@54 */
#define COM_SID_SSB_u8SWSts_WF 99 /* little 1@55 */
#define COM_SID_PKE_AuthResult_WF 100 /* little 2@56 */
#define COM_SID_FEE_DTCWriteIdleFlag_WF 101 /* little 2@58 */
#define COM_SID_PMM_u8PwrStsLoad_WF 102 /* little 2@60 */
#define COM_SID_SWK_u8NmSleepSt_WF 103 /* little 1@62 */
#define COM_SID_DLC_u8PasPESts_WF 104 /* little 1@63 */

/* signals for network CAN1 message PEPS_ESCLM_RX: id=0x90ffb634 dlc=5, dir=RX */
#define COM_SID_PEPS_SUB_ID 105 /* little 2@0 */
#define COM_SID_PEPS_AuthResp 106 /* little 32@8 */

/* signals for network CAN1 message ACL_RX: id=0x98eeff00 dlc=8, dir=RX */
#define COM_SID_ManufacturerCode 107 /* little 11@21 */

/* signals for network CAN1 message EOI_RX: id=0x8cfd9200 dlc=8, dir=RX */
#define COM_SID_EngOperatingState 108 /* little 4@0 */

/* signals for network CAN1 message ETC2_RX: id=0x98f00503 dlc=8, dir=RX */
#define COM_SID_TransCurrentGear 109 /* little 8@24 */

/* signals for network CAN1 message ESCL1_RX: id=0x90ffb04d dlc=8, dir=RX */
#define COM_SID_ESCL_St 110 /* little 2@0 */
#define COM_SID_ESCL_WarnSafety 111 /* little 2@2 */
#define COM_SID_ESCL_PromptRotateSteerWheel 112 /* little 2@4 */
#define COM_SID_AliveCounter 113 /* little 8@48 */
#define COM_SID_ESCL1_RX_CRC 114 /* little 8@56 */

/* signals for network CAN1 message ESCLM_PEPS_RX: id=0x90ffb24d dlc=8, dir=RX */
#define COM_SID_ESCL_SUB_ID 115 /* little 2@0 */
#define COM_SID_ESCL_AuthChallenge 116 /* little 32@8 */
#define COM_SID_ESCL_AuthResult 117 /* little 2@40 */

/* signals for network CAN1 message ESCL_NM_RX: id=0x98ff904d dlc=8, dir=RX */
#define COM_SID_Destination_Address 118 /* little 8@0 */

/* signals for network CAN1 message DW_State_RX: id=0x98ff0cec dlc=8, dir=RX */
#define COM_SID_SecAlarm 119 /* little 2@0 */
#define COM_SID_ESCL_u8SleepFlag_NM_WF 120 /* little 1@2 */
#define COM_SID_WIN_u8SleepFlag_NM_WF 121 /* little 1@3 */
#define COM_SID_ACC_u8SleepFlag_NM_WF 122 /* little 1@4 */
#define COM_SID_RMH_u8SleepFlag_NM_WF 123 /* little 1@5 */
#define COM_SID_DLC_u8SleepFlag_NM_WF 124 /* little 1@6 */
#define COM_SID_SAC_u8SleepFlag_NM_WF 125 /* little 1@7 */
#define COM_SID_HORN_u8SleepFlag_NM_WF 126 /* little 1@8 */
#define COM_SID_TUL_u8SleepFlag_NM_WF 127 /* little 1@9 */
#define COM_SID_FMHL_u8SleepFlag_NM_WF 128 /* little 1@10 */
#define COM_SID_AHL_u8SleepFlag_NM_WF 129 /* little 1@11 */
#define COM_SID_POL_u8SleepFlag_NM_WF 130 /* little 1@12 */
#define COM_SID_LBL_u8SleepFlag_NM_WF 131 /* little 1@13 */
#define COM_SID_HBL_u8SleepFlag_NM_WF 132 /* little 1@14 */
#define COM_SID_FFL_u8SleepFlag_NM_WF 133 /* little 1@15 */
#define COM_SID_DW_State_RX_MechKeySt 134 /* little 2@20 */
#define COM_SID_RFL_u8SleepFlag_NM_WF 135 /* little 1@24 */
#define COM_SID_DRL_u8SleepFlag_NM_WF 136 /* little 1@25 */
#define COM_SID_BRL_u8SleepFlag_NM_WF 137 /* little 1@26 */
#define COM_SID_SLED_u8SleepFlag_WF 138 /* little 1@27 */
#define COM_SID_DML_u8LampSleepFlag_NM_WF 139 /* little 1@28 */
#define COM_SID_LOL_u8SleepFlag_NM_WF 140 /* little 1@29 */
#define COM_SID_WDIL_u8SleepFlag_NM_WF 141 /* little 1@30 */
#define COM_SID_SKC_u8SleepFlag_WF 142 /* little 1@31 */
#define COM_SID_DLC_u8UnlockSource_WF 143 /* little 4@32 */
#define COM_SID_ON_SW_WF 144 /* little 1@36 */
#define COM_SID_ST_SW_WF 145 /* little 1@37 */
#define COM_SID_ACC_SW_WF 146 /* little 1@38 */
#define COM_SID_Lighting_Sensor_WF 147 /* little 1@39 */
#define COM_SID_VehicleVoltage 148 /* little 2@46 */
#define COM_SID_Mirror_Heat_SW_WF 149 /* little 1@48 */
#define COM_SID_LOGO_SW_WF 150 /* little 1@49 */
#define COM_SID_Window_Inhibite_SW_WF 151 /* little 1@50 */
#define COM_SID_Key_IN_WF 152 /* little 1@51 */
#define COM_SID_Reserve1_SW_WF 153 /* little 1@52 */
#define COM_SID_Reserve5_SW_WF 154 /* little 1@53 */
#define COM_SID_FL_TL_LED_Fb_WF 155 /* little 1@54 */
#define COM_SID_FR_TL_LED_Fb_WF 156 /* little 1@55 */
#define COM_SID_Reserve2_SW_WF 157 /* little 1@56 */
#define COM_SID_Reserve3_SW_WF 158 /* little 1@57 */
#define COM_SID_Reserve4_SW_WF 159 /* little 1@58 */
#define COM_SID_DIL_Brake_WF 160 /* little 1@59 */
#define COM_SID_SSB_SW1_WF 161 /* little 1@60 */
#define COM_SID_DIH_SSB_SW2_WF 162 /* little 1@61 */
#define COM_SID_RDoor_SW_WF 163 /* little 1@62 */
#define COM_SID_LDoor_SW_WF 164 /* little 1@63 */

/* signals for network CAN1 message IC_MSG_RX: id=0x98ff0917 dlc=8, dir=RX */
#define COM_SID_DoorOpenSw 165 /* little 2@12 */

/* signals for network CAN1 message EEC1_Electronic_Engine_Controller_1_RX: id=0x8cf00400 dlc=8, dir=RX */
#define COM_SID_EEC1_EngTorqueMode 166 /* little 4@0 */
#define COM_SID_EEC1_ActlEngPrcntTrqueHighResolution 167 /* little 4@4 */
#define COM_SID_EEC1_DriversDemandPercentTorque 168 /* little 8@8 */
#define COM_SID_EEC1_ActualEngPercentTorque 169 /* little 8@16 */
#define COM_SID_EEC1_EngSpeed 170 /* little 16@24 */
#define COM_SID_EEC1_ECU_SA 171 /* little 8@40 */
#define COM_SID_EEC1_EngDemandPercentTorque 172 /* little 8@56 */

/* signals for network CAN1 message CCVS_RX: id=0x98fef121 dlc=8, dir=RX */
#define COM_SID_ParkingBrakeSwitch 173 /* little 2@2 */

/* signals for network CAN1 message VCU_4_RX: id=0x98ff12ef dlc=8, dir=RX */
#define COM_SID_VBUS_VCU4_N_VehicleSpeed 174 /* little 16@0 */
#define COM_SID_VBUS_VCU4_St_Gears 175 /* little 2@32 */
#define COM_SID_VBUS_VCU4_St_Ready 176 /* little 1@34 */
#define COM_SID_VBUS_VCU4_St_BrakeSta 177 /* little 1@58 */

/* signals for network CAN1 message TCO1_RX: id=0x8cfe6cee dlc=8, dir=RX */
#define COM_SID_TachographVehicleSpeed 178 /* little 16@48 */

/* signals for network CAN1 message TireCondition_RX: id=0x98fef433 dlc=8, dir=RX */
#define COM_SID_TireLocation 179 /* little 8@0 */
#define COM_SID_TirePressure 180 /* little 8@8 */
#define COM_SID_TireTemperature 181 /* little 16@16 */
#define COM_SID_WheelSensorStatus 182 /* little 2@32 */
#define COM_SID_TireStatus 183 /* little 2@34 */
#define COM_SID_Tire_Sensor_Electrical_Fault 184 /* little 2@36 */
#define COM_SID_Tire_Air_Leakage_Rate 185 /* little 16@40 */
#define COM_SID_TirePressureThresholdDetection 186 /* little 3@61 */

/* signals for network CAN1 message DM1_TPMS_RX: id=0x98feca33 dlc=8, dir=RX */
#define COM_SID_DM1_TPMS_ProtectLampStatus 187 /* little 2@0 */
#define COM_SID_DM1_TPMS_AmberWarningLampStatus 188 /* little 2@2 */
#define COM_SID_DM1_TPMS_RedStopLampState 189 /* little 2@4 */
#define COM_SID_LeastByteofSPN 190 /* little 8@16 */
#define COM_SID_SecondByteofSPN 191 /* little 8@24 */
#define COM_SID_FMI 192 /* little 5@32 */
#define COM_SID__3MostBitofSPN 193 /* little 3@37 */
#define COM_SID_OC 194 /* little 7@40 */
#define COM_SID_CM 195 /* little 1@47 */

/* signals for network CAN1 message EBC1_Electronic_Brake_Controller_1_RX: id=0x98f0010b dlc=8, dir=RX */
#define COM_SID_EBC1_ASREngCtrlActive 196 /* little 2@0 */
#define COM_SID_EBC1_ASRBrakeCtrlActive 197 /* little 2@2 */
#define COM_SID_EBC1_AntiLockBrakingActive 198 /* little 2@4 */
#define COM_SID_EBC1_EBSBrakeSwitch 199 /* little 2@6 */
#define COM_SID_EBC1_Brake_Pedal_Position 200 /* little 8@8 */
#define COM_SID_EBC1_ABS_OffRoad_switch 201 /* little 2@16 */
#define COM_SID_EBC1_ASR_OffRoad_switch 202 /* little 2@18 */
#define COM_SID_EBC1_ASR_HillHolder_switch 203 /* little 2@20 */
#define COM_SID_EBC1_Traction_ControlOverride_switch 204 /* little 2@22 */
#define COM_SID_ABS_Fully_Operational 205 /* little 2@40 */
#define COM_SID_EBC1_EBSRedWarningSignal 206 /* little 2@42 */
#define COM_SID_EBC1_ABS_EBSAmberWarningSignal 207 /* little 2@44 */
#define COM_SID_EBC1_ATC_ASRInformationSignal 208 /* little 2@46 */

/* signals for network CAN1 message EBC5_Electronic_Brake_Controller_5_RX: id=0x98fdc40b dlc=8, dir=RX */
#define COM_SID_Foundation_Brake_Use 209 /* little 2@8 */
#define COM_SID_XBR_System_State 210 /* little 2@10 */
#define COM_SID_XBR_Active_Control_Mode 211 /* little 4@12 */
#define COM_SID_XBR_Acceleration_Limit 212 /* little 8@16 */
#define COM_SID_Parking_Brake_Actuator_Fully_Activated 213 /* little 2@24 */
#define COM_SID_Emergency_Braking_Active 214 /* little 2@26 */

/* signals for network CAN1 message DLCC1_Direct_Lamp_Control_Command_1_RX: id=0x98fd0700 dlc=8, dir=RX */
#define COM_SID_DLCC1_EngAmberWarningLampCmd 215 /* little 2@2 */
#define COM_SID_DLCC1_EngRedStopLampCmd 216 /* little 2@4 */
#define COM_SID_DLCC1_OBDMalfunctionLampCmd 217 /* little 2@6 */
#define COM_SID_DLCC1_EngBrakeActiveLampCmd 218 /* little 2@8 */
#define COM_SID_DLCC1_EngOilPressLowLampCmd 219 /* little 2@12 */
#define COM_SID_DLCC1_EngCoolantTempHighLampCmd 220 /* little 2@14 */
#define COM_SID_DLCC1_EngCoolantLevelLowLampCmd 221 /* little 2@16 */

/* signals for network CAN1 message CCVS1_Cruise_Control_Vehicle_Speed_1_RX: id=0x98fef100 dlc=8, dir=RX */
#define COM_SID_CCVS1_TwoSpeedAxleSwitch 222 /* little 2@0 */
#define COM_SID_CCVS1_ParkingBrakeSwitch 223 /* little 2@2 */
#define COM_SID_CCVS1_WheelBasedVehicleSpeed 224 /* little 16@8 */
#define COM_SID_CCVS1_CruiseCtrlActive 225 /* little 2@24 */
#define COM_SID_CCVS1_CruiseCtrlEnableSwitch 226 /* little 2@26 */
#define COM_SID_CCVS1_BrakeSwitch 227 /* little 2@28 */
#define COM_SID_CCVS1_ClutchSwitch 228 /* little 2@30 */
#define COM_SID_CCVS1_CruiseCtrlSetSwitch 229 /* little 2@32 */
#define COM_SID_CCVS1_CruiseCtrlCoastSwitch 230 /* little 2@34 */
#define COM_SID_CCVS1_CruiseCtrlResumeSwitch 231 /* little 2@36 */
#define COM_SID_CCVS1_CruiseCtrlAccelerateSwitch 232 /* little 2@38 */
#define COM_SID_CCVS1_CruiseCtrlSetSpeed 233 /* little 8@40 */
#define COM_SID_CCVS1_PTOGovernorState 234 /* little 5@48 */
#define COM_SID_CCVS1_CruiseCtrlStates 235 /* little 3@53 */

/* signals for network CAN1 message VDC1_Vehicle_Dynamic_Stability_Control_1_RX: id=0x98fe4f0b dlc=8, dir=RX */
#define COM_SID_VDC1_VDCInformationSignal 236 /* little 2@0 */
#define COM_SID_VDC1_VDCFullyOperational 237 /* little 2@2 */
#define COM_SID_VDC1_VDC_brake_light_request 238 /* little 2@4 */
#define COM_SID_VDC1_ROPEngCtrlActive 239 /* little 2@8 */
#define COM_SID_VDC1_ROPBrakeCtrlActive 240 /* little 2@10 */
#define COM_SID_VDC1_YCEngCtrlActive 241 /* little 2@12 */
#define COM_SID_VDC1_YCBrakeCtrlActive 242 /* little 2@14 */

/* signals for network CAN1 message ERC1_RX: id=0x98f0000f dlc=8, dir=RX */
#define COM_SID_ERC1_RX_ERC1_ActualRetarderPercentTorque 243 /* little 8@8 */

/* signals for network CAN1 message ERC3_RX: id=0x98f00000 dlc=8, dir=RX */
#define COM_SID_ERC3_RX_ERC1_ActualRetarderPercentTorque 244 /* little 8@8 */

/* signals for network CAN1 message ETC5_RX: id=0x9cfec321 dlc=8, dir=RX */
#define COM_SID_TransReverseDirectionSw 245 /* little 2@8 */
#define COM_SID_TransNeutralSwitch 246 /* little 2@10 */

/* signals for network CAN1 message EEC3_RX: id=0x98ffba19 dlc=8, dir=RX */
#define COM_SID_ECC_Work_Switch 247 /* little 1@0 */
#define COM_SID_ECC_COMP_ReqSwitch 248 /* little 1@1 */
#define COM_SID_ECC_WPTC_ReqSwitch 249 /* little 1@2 */
#define COM_SID_REC_Switch 250 /* little 1@3 */
#define COM_SID_Fan_Gear_Switch 251 /* little 4@4 */
#define COM_SID_HVAC_MODE_Switch 252 /* little 3@8 */
#define COM_SID_HVAC_SET_Temp_Switch 253 /* little 5@11 */
#define COM_SID_One_click_defrosting 254 /* little 1@47 */

/* signals for network CAN1 message ECC2_RX: id=0x98ffbc19 dlc=8, dir=RX */
#define COM_SID_ECC_Work_Status 255 /* little 1@0 */
#define COM_SID_ECC_COMP_ReqStatus 256 /* little 1@1 */
#define COM_SID_REC_Status 257 /* little 1@3 */
#define COM_SID_Fan_Gear 258 /* little 4@4 */
#define COM_SID_HVAC_MODE_Status 259 /* little 3@8 */
#define COM_SID_HVAC_SET_Temp 260 /* little 5@11 */
#define COM_SID_EVAP_Temp 261 /* little 8@24 */
#define COM_SID_MID_PRESS_Status 262 /* little 1@42 */
#define COM_SID_H_L_PRESS_Sta 263 /* little 2@43 */
#define COM_SID_One_click_defrosting_Status 264 /* little 1@47 */

/* signals for network CAN1 message ID1_RX: id=0x98ff4c56 dlc=8, dir=RX */
#define COM_SID_N_Shift_WF 265 /* little 1@0 */
#define COM_SID_AI_Clutch_WF 266 /* little 1@1 */
#define COM_SID_StartupSts_Fb_WF 267 /* little 1@2 */
#define COM_SID_High_low_Voltage_SW_WF 268 /* little 1@3 */
#define COM_SID_AC_DOH_WF 269 /* little 1@4 */
#define COM_SID_D1_Diag_WF 270 /* little 1@5 */
#define COM_SID_D2_Diag_WF 271 /* little 1@6 */
#define COM_SID_D3_Diag_WF 272 /* little 1@7 */
#define COM_SID_D4_Diag_WF 273 /* little 1@8 */
#define COM_SID_D5_Diag_WF 274 /* little 1@9 */
#define COM_SID_D6_Diag_WF 275 /* little 1@10 */
#define COM_SID_D7_Diag_WF 276 /* little 1@11 */
#define COM_SID_D8_Diag_WF 277 /* little 1@12 */
#define COM_SID_D9_Diag_WF 278 /* little 1@13 */
#define COM_SID_D10_Diag_WF 279 /* little 1@14 */
#define COM_SID_D11_Diag_WF 280 /* little 1@15 */
#define COM_SID_D12_Diag_WF 281 /* little 1@16 */
#define COM_SID_D13_Diag_WF 282 /* little 1@17 */
#define COM_SID_D14_Diag_WF 283 /* little 1@18 */
#define COM_SID_D15_Diag_WF 284 /* little 1@19 */
#define COM_SID_D16_Diag_WF 285 /* little 1@20 */
#define COM_SID_D17_Diag_WF 286 /* little 1@21 */
#define COM_SID_D18_Diag_WF 287 /* little 1@22 */
#define COM_SID_D19_Diag_WF 288 /* little 1@23 */
#define COM_SID_D20_Diag_WF 289 /* little 1@24 */
#define COM_SID_D21_Diag_WF 290 /* little 1@25 */
#define COM_SID_D22_Diag_WF 291 /* little 1@26 */
#define COM_SID_D23_Diag_WF 292 /* little 1@27 */
#define COM_SID_D24_Diag_WF 293 /* little 1@28 */
#define COM_SID_D25_Diag_WF 294 /* little 1@29 */
#define COM_SID_D26_Diag_WF 295 /* little 1@30 */
#define COM_SID_D27_Diag_WF 296 /* little 1@31 */
#define COM_SID_D28_Diag_WF 297 /* little 1@32 */
#define COM_SID_D29_Diag_WF 298 /* little 1@33 */
#define COM_SID_D30_Diag_WF 299 /* little 1@34 */
#define COM_SID_D31_Diag_WF 300 /* little 1@35 */
#define COM_SID_D32_Diag_WF 301 /* little 1@36 */
#define COM_SID_D33_Diag_WF 302 /* little 1@37 */
#define COM_SID_D34_Diag_WF 303 /* little 1@38 */
#define COM_SID_D35_Diag_WF 304 /* little 1@39 */
#define COM_SID_D36_Diag_WF 305 /* little 1@40 */
#define COM_SID_D38_Diag_WF 306 /* little 1@41 */
#define COM_SID_D39_Diag_WF 307 /* little 1@42 */
#define COM_SID_D40_Diag_WF 308 /* little 1@43 */
#define COM_SID_D41_Diag_WF 309 /* little 1@44 */
#define COM_SID_Wiper_H_RlyCoil_Ctrl_WF 310 /* little 1@45 */
#define COM_SID_Blower_RlyCoil_Ctrl_WF 311 /* little 1@46 */
#define COM_SID_IG_Fb_WF 312 /* little 1@47 */
#define COM_SID_IG_RlyCoil_Ctrl_WF 313 /* little 1@48 */
#define COM_SID_ACC_Fb_WF 314 /* little 1@49 */
#define COM_SID_ACC_RlyCoil_Ctrl_WF 315 /* little 1@50 */
#define COM_SID_Horn_RlyCoil_Ctrl_WF 316 /* little 1@51 */
#define COM_SID_Wiper_Power_RlyCoil_Ctrl_WF 317 /* little 1@52 */
#define COM_SID_Startup_SIG_WF 318 /* little 1@53 */
#define COM_SID_F_LOGO_Lamp_WF 319 /* little 1@54 */
#define COM_SID_Washer_Motor_WF 320 /* little 1@55 */
#define COM_SID_HSD1_Reserve_WF 321 /* little 1@56 */
#define COM_SID_Battery_Saver_WF 322 /* little 1@57 */
#define COM_SID_Dome_Lamp_WF 323 /* little 1@58 */
#define COM_SID_LSD1_Reserve_WF 324 /* little 1@59 */
#define COM_SID_LSD2_Reserve_WF 325 /* little 1@60 */
#define COM_SID_Window_Indication_Lamp_WF 326 /* little 1@61 */
#define COM_SID_IDM_COMP_ReqStatus 327 /* little 1@62 */
#define COM_SID_F_FOG_RlyCoil_Ctrl_WF 328 /* little 1@63 */

/* signals for network CAN1 message ID2_RX: id=0x98ff4d56 dlc=8, dir=RX */
#define COM_SID_POS_RlyCoil_Ctrl_WF 329 /* little 1@0 */
#define COM_SID_LB_RlyCoil_Ctrl_WF 330 /* little 1@1 */
#define COM_SID_HB_RlyCoil_Ctrl_WF 331 /* little 1@2 */
#define COM_SID_FL_Wind_Up_RlyCoil_Ctrl_WF 332 /* little 1@3 */
#define COM_SID_FL_Wind_Down_RlyCoil_Ctrl_WF 333 /* little 1@4 */
#define COM_SID_FR_Wind_Up_RlyCoil_Ctrl_WF 334 /* little 1@5 */
#define COM_SID_FR_Wind_Down_RlyCoil_Ctrl_WF 335 /* little 1@6 */
#define COM_SID_RL_Wind_Up_RlyCoil_Ctrl_WF 336 /* little 1@7 */
#define COM_SID_RL_Wind_Down_RlyCoil_Ctrl_WF 337 /* little 1@8 */
#define COM_SID_RR_Wind_Up_RlyCoil_Ctrl_WF 338 /* little 1@9 */
#define COM_SID_RR_Wind_Down_RlyCoil_Ctrl_WF 339 /* little 1@10 */
#define COM_SID_Center_Unlock_RlyCoil_Ctrl_WF 340 /* little 1@11 */
#define COM_SID_Center_Lock_RlyCoil_Ctrl_WF 341 /* little 1@12 */
#define COM_SID_Mirror_Heat_RlyCoil_Ctrl_WF 342 /* little 1@13 */
#define COM_SID_Horn_SW_WF 343 /* little 1@14 */
#define COM_SID_FL_Wind_Gnd_Ctrl_WF 344 /* little 1@15 */
#define COM_SID_FR_Wind_Gnd_Ctrl_WF 345 /* little 1@16 */
#define COM_SID_RL_Wind_Gnd_Ctrl_WF 346 /* little 1@17 */
#define COM_SID_RR_Wind_Gnd_Ctrl_WF 347 /* little 1@18 */
#define COM_SID_LSD_SSB_LED3_WF 348 /* little 1@19 */
#define COM_SID_LSD_SSB_LED2_WF 349 /* little 1@20 */
#define COM_SID_LSD_SSB_LED1_WF 350 /* little 1@21 */
#define COM_SID_Condensing_Fan_Low_Ctrl_WF 351 /* little 1@22 */
#define COM_SID_Condensing_Fan_High_Ctrl_WF 352 /* little 1@23 */
#define COM_SID_Int_Ext_Motor_Inc_WF 353 /* little 1@24 */
#define COM_SID_Int_Ext_Motor_Dec_WF 354 /* little 1@25 */
#define COM_SID_Cold_Heat_Motor_Inc_WF 355 /* little 1@26 */
#define COM_SID_Cold_Heat_Motor_Dec_WF 356 /* little 1@27 */
#define COM_SID_Mode_Motor_Inc_WF 357 /* little 1@28 */
#define COM_SID_Mode_MotoR_Dec_WF 358 /* little 1@29 */
#define COM_SID_IDM_LPOWER 359 /* little 2@30 */
#define COM_SID_FL_Gnd_Ctrl_WF 360 /* little 12@32 */
#define COM_SID_FR_Gnd_Ctrl_WF 361 /* little 12@44 */

/* signals for network CAN1 message ID3_RX: id=0x98ff4e56 dlc=8, dir=RX */
#define COM_SID_RL_Wind_Samp_WF 362 /* little 12@0 */
#define COM_SID_RR_Wind_Samp_WF 363 /* little 12@12 */
#define COM_SID_Blower_Analog_Out_WF 364 /* little 12@24 */
#define COM_SID_Cold_Heat_Motor_Fb_WF 365 /* little 12@36 */
#define COM_SID_Mode_MotoR_WF 366 /* little 12@48 */

/* signals for network CAN1 message TP_CM_RX: id=0x9cecff21 dlc=8, dir=RX */
#define COM_SID_ControlByte 367 /* little 8@0 */
#define COM_SID_TotalNumberOfBbytes 368 /* little 16@8 */
#define COM_SID_TotalNumberOfPackets 369 /* little 8@24 */
#define COM_SID_ParameterGroupNumber 370 /* little 24@40 */

/* signals for network CAN1 message TP_DT_RX: id=0x9cebff21 dlc=8, dir=RX */
#define COM_SID_SequenceNumber 371 /* little 8@0 */


/* signals for network CANTEST */
/* signals for network CANTEST message CANTEST_TX_TEST: id=0x200 dlc=8, dir=TX */
#define COM_SID_TX_COUNTER 372 /* little 8@0 */
#define COM_SID_TX_FLAG 373 /* little 1@9 */
#define COM_SID_TX_LEVEL 374 /* little 12@16 */

/* signals for network CANTEST message CANTEST_RX_TEST: id=0x201 dlc=8, dir=RX */
#define COM_SID_RX_COUNTER 375 /* little 8@0 */
#define COM_SID_RX_TEMP 376 /* big 16@23 */


/* NOTE: manually modify to create more groups */
#define COM_GROUP_ID_CAN1 0
#define Com_IPduBCM_LCSF_TX_GroupRefMask (1<<COM_GROUP_ID_CAN1)
#define Com_IPduBCM_Ctrl_TX_GroupRefMask (1<<COM_GROUP_ID_CAN1)
#define Com_IPduBCM_OEL_TX_GroupRefMask (1<<COM_GROUP_ID_CAN1)
#define Com_IPduBCM_OWW_TX_GroupRefMask (1<<COM_GROUP_ID_CAN1)
#define Com_IPduBCM_DoorCtrl_TX_GroupRefMask (1<<COM_GROUP_ID_CAN1)
#define Com_IPduBCM_DM1_TX_GroupRefMask (1<<COM_GROUP_ID_CAN1)
#define Com_IPduCrash_Notification_RX_GroupRefMask (1<<COM_GROUP_ID_CAN1)
#define Com_IPduAMB_Ambient_Conditions_RX_GroupRefMask (1<<COM_GROUP_ID_CAN1)
#define Com_IPduPEPS1_RX_GroupRefMask (1<<COM_GROUP_ID_CAN1)
#define Com_IPduPEPS2_RX_GroupRefMask (1<<COM_GROUP_ID_CAN1)
#define Com_IPduPEPS_ESCLM_RX_GroupRefMask (1<<COM_GROUP_ID_CAN1)
#define Com_IPduACL_RX_GroupRefMask (1<<COM_GROUP_ID_CAN1)
#define Com_IPduEOI_RX_GroupRefMask (1<<COM_GROUP_ID_CAN1)
#define Com_IPduETC2_RX_GroupRefMask (1<<COM_GROUP_ID_CAN1)
#define Com_IPduESCL1_RX_GroupRefMask (1<<COM_GROUP_ID_CAN1)
#define Com_IPduESCLM_PEPS_RX_GroupRefMask (1<<COM_GROUP_ID_CAN1)
#define Com_IPduESCL_NM_RX_GroupRefMask (1<<COM_GROUP_ID_CAN1)
#define Com_IPduDW_State_RX_GroupRefMask (1<<COM_GROUP_ID_CAN1)
#define Com_IPduIC_MSG_RX_GroupRefMask (1<<COM_GROUP_ID_CAN1)
#define Com_IPduEEC1_Electronic_Engine_Controller_1_RX_GroupRefMask (1<<COM_GROUP_ID_CAN1)
#define Com_IPduCCVS_RX_GroupRefMask (1<<COM_GROUP_ID_CAN1)
#define Com_IPduVCU_4_RX_GroupRefMask (1<<COM_GROUP_ID_CAN1)
#define Com_IPduTCO1_RX_GroupRefMask (1<<COM_GROUP_ID_CAN1)
#define Com_IPduTireCondition_RX_GroupRefMask (1<<COM_GROUP_ID_CAN1)
#define Com_IPduDM1_TPMS_RX_GroupRefMask (1<<COM_GROUP_ID_CAN1)
#define Com_IPduEBC1_Electronic_Brake_Controller_1_RX_GroupRefMask (1<<COM_GROUP_ID_CAN1)
#define Com_IPduEBC5_Electronic_Brake_Controller_5_RX_GroupRefMask (1<<COM_GROUP_ID_CAN1)
#define Com_IPduDLCC1_Direct_Lamp_Control_Command_1_RX_GroupRefMask (1<<COM_GROUP_ID_CAN1)
#define Com_IPduCCVS1_Cruise_Control_Vehicle_Speed_1_RX_GroupRefMask (1<<COM_GROUP_ID_CAN1)
#define Com_IPduVDC1_Vehicle_Dynamic_Stability_Control_1_RX_GroupRefMask (1<<COM_GROUP_ID_CAN1)
#define Com_IPduERC1_RX_GroupRefMask (1<<COM_GROUP_ID_CAN1)
#define Com_IPduERC3_RX_GroupRefMask (1<<COM_GROUP_ID_CAN1)
#define Com_IPduETC5_RX_GroupRefMask (1<<COM_GROUP_ID_CAN1)
#define Com_IPduEEC3_RX_GroupRefMask (1<<COM_GROUP_ID_CAN1)
#define Com_IPduECC2_RX_GroupRefMask (1<<COM_GROUP_ID_CAN1)
#define Com_IPduID1_RX_GroupRefMask (1<<COM_GROUP_ID_CAN1)
#define Com_IPduID2_RX_GroupRefMask (1<<COM_GROUP_ID_CAN1)
#define Com_IPduID3_RX_GroupRefMask (1<<COM_GROUP_ID_CAN1)
#define Com_IPduTP_CM_RX_GroupRefMask (1<<COM_GROUP_ID_CAN1)
#define Com_IPduTP_DT_RX_GroupRefMask (1<<COM_GROUP_ID_CAN1)
#define COM_GROUP_ID_CANTEST 1
#define Com_IPduCANTEST_TX_TEST_GroupRefMask (1<<COM_GROUP_ID_CANTEST)
#define Com_IPduCANTEST_RX_TEST_GroupRefMask (1<<COM_GROUP_ID_CANTEST)

#define COM_GROUP_ID_MAX 2

#define COM_USE_MAIN_FAST

// #define COM_USE_PB_CONFIG

/* ================================ [ TYPES     ] ============================================== */
/* ================================ [ DECLARES  ] ============================================== */
/* ================================ [ DATAS     ] ============================================== */
/* ================================ [ LOCALS    ] ============================================== */
/* ================================ [ FUNCTIONS ] ============================================== */
#endif /* COM_CFG_H */
