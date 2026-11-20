/**
 * SSAS - Simple Smart Automotive Software
 * Copyright (C) 2021 Parai Wang <parai@foxmail.com>
 *
 * @generated
 * 本文件由 tools/generator 自动生成，请勿手工修改。
 * 改动请改配置源，然后重新生成；一致性由 tools/a4_gen_check.py 校验。
 */
/* ================================ [ INCLUDES  ] ============================================== */
#include "Com_Cfg.h"
#include "Com.h"
#include "Com_Priv.h"
#ifdef USE_PDUR
#include "PduR_Cfg.h"
#endif
/* ================================ [ MACROS    ] ============================================== */
/* ================================ [ TYPES     ] ============================================== */
/* ================================ [ DECLARES  ] ============================================== */
/* ================================ [ DATAS     ] ============================================== */
static const uint8_t BCM_LowBeamSts_InitialValue = 0;
static const uint8_t BCM_HighBeamSts_InitialValue = 0;
static const uint8_t BCM_FrontFogSts_InitialValue = 0;
static const uint8_t BCM_TurnRLightSts_InitialValue = 0;
static const uint8_t BCM_TurnLLightSts_InitialValue = 0;
static const uint8_t BCM_DRLSts_InitialValue = 0;
static const uint8_t BCM_PositionLightSts_InitialValue = 0;
static const uint8_t BCM_RearFogSts_InitialValue = 0;
static const uint8_t BackUpLightSt_InitialValue = 0;
static const uint8_t BrakelightST_InitialValue = 0;
static const uint8_t InteriorLampSt_InitialValue = 0;
static const uint8_t BCM_PassWindowLcokSw_InitialValue = 0;
static const uint8_t CentralLockSw_InitialValue = 0;
static const uint8_t MRightFrontWinSw_InitialValue = 0;
static const uint8_t MLeftFrontWinSw_InitialValue = 0;
static const uint8_t RightFrontWinSw_InitialValue = 0;
static const uint8_t MRightRearWinSw_InitialValue = 0;
static const uint8_t MLeftRearWinSw_InitialValue = 0;
static const uint8_t RightRearWinSw_InitialValue = 0;
static const uint8_t LeftRearWinSw_InitialValue = 0;
static const uint8_t BCM_Ctrl_TX_MechKeySt_InitialValue = 0;
static const uint8_t LeftFrontWinSt_InitialValue = 0;
static const uint8_t RightFrontWinSt_InitialValue = 0;
static const uint8_t LeftRearWinSt_InitialValue = 0;
static const uint8_t RightRearWinSt_InitialValue = 0;
static const uint8_t DoorLockMotorState_InitialValue = 0;
static const uint8_t RemoteDoorState_InitialValue = 0;
static const uint8_t LeftFrontWinErrorSt_InitialValue = 0;
static const uint8_t RightFrontWinErrorSt_InitialValue = 0;
static const uint8_t LeftRearWinErrorSt_InitialValue = 0;
static const uint8_t RightRearWinErrorSt_InitialValue = 0;
static const uint8_t HazardSw_InitialValue = 0;
static const uint8_t HazardSt_InitialValue = 0;
static const uint8_t WiperSt_InitialValue = 0;
static const uint8_t SKC_u8PEPSICUIndCnt_WF_InitialValue = 0;
static const uint8_t PRM_u8PEPSICUIndCnt_WF_InitialValue = 0;
static const uint8_t ATP_u8DrvLockRotor_WF_InitialValue = 0;
static const uint8_t ESCL_u8AuthReqCnt_WF_InitialValue = 0;
static const uint8_t BCM_OpenStatusofDdoor_InitialValue = 0;
static const uint8_t BCM_OpenStatusofPdoor_InitialValue = 0;
static const uint8_t BCM_OpenStatusofLeftReardoor_InitialValue = 0;
static const uint8_t BCM_OpenStatusofRightReardoor_InitialValue = 0;
static const uint8_t BASE_u8AuthResultCnt_WF_InitialValue = 0;
static const uint8_t BSW_TPMS_FrameCnt_WF_InitialValue = 0;
static const uint8_t PAM_u8SleepFlag_WF_InitialValue = 0;
static const uint8_t ATP_u8PasLockRotor_WF_InitialValue = 0;
static const uint8_t FEE_APPWriteIdleFlag_WF_InitialValue = 0;
static const uint8_t FEE_BOOTWriteIdleFlag_WF_InitialValue = 0;
static const uint8_t WIN_u8DrvWinCmdCAN_WF_InitialValue = 0;
static const uint8_t WIN_u8PasWinCmdCAN_WF_InitialValue = 0;
static const uint8_t TUL_u8HonkingStyle_WF_InitialValue = 0;
static const uint8_t DLC_u8LockSource_WF_InitialValue = 0;
static const uint8_t HornRelaySt_InitialValue = 0;
static const uint8_t BrakeLightWarning_InitialValue = 0;
static const uint8_t LF_SendCounter_WF_InitialValue = 0;
static const uint8_t LF_Commond_WF_InitialValue = 0;
static const uint8_t DM1_MalfunctionIndicatorLampStatus_InitialValue = 0;
static const uint8_t DM1_RedStopLampState_InitialValue = 0;
static const uint8_t BCM_LeastByteofSPN_InitialValue = 0;
static const uint8_t BCM_SecondByteofSPN_InitialValue = 0;
static const uint8_t BCM_FMI_InitialValue = 0;
static const uint8_t BCM_3MostBitofSPN_InitialValue = 0;
static const uint8_t BCM_OC_InitialValue = 0;
static const uint8_t BCM_CM_InitialValue = 0;
static const uint8_t SRS_Crash_Type_InitialValue = 0;
static const uint8_t AMB_BarometricPress_InitialValue = 0;
static const uint16_t LFE1_AmbientAirTemp_InitialValue = 0;
static const uint8_t LFE1_EngAirIntakeTemp_InitialValue = 0;
static const uint8_t PEPsKeyInState_InitialValue = 0;
static const uint8_t PEPS_PkeLockCmd_InitialValue = 0;
static const uint8_t PEPS_PowerMode_InitialValue = 0;
static const uint8_t PEPS_ESCLInhabitSt_InitialValue = 0;
static const uint8_t PEPS_EmergencyST_InitialValue = 0;
static const uint8_t PEPS_KeyAuthenticationSt_PEPS_InitialValue = 0;
static const uint8_t ESCL_failure_InitialValue = 0;
static const uint8_t PEPS_failure_InitialValue = 0;
static const uint8_t Key_Not_Found_InitialValue = 0;
static const uint8_t Key_Battery_Low_InitialValue = 0;
static const uint8_t PEPS_PEPSICUInd_InitialValue = 0;
static const uint8_t PEPsKeyInFeedback_InitialValue = 0;
static const uint8_t ACC_FB_InitialValue = 0;
static const uint8_t IGN1_FB_InitialValue = 0;
static const uint8_t PEPsKeyOutFeedback_InitialValue = 0;
static const uint8_t Alive_counter_InitialValue = 0;
static const uint8_t PEPS1_RX_CRC_InitialValue = 0;
static const uint8_t Key1_Inside_St_InitialValue = 0;
static const uint8_t Key2_Inside_St_InitialValue = 0;
static const uint8_t Key3_Inside_St_InitialValue = 0;
static const uint8_t Key4_Inside_St_InitialValue = 0;
static const uint8_t Key1_Inhibit_St_InitialValue = 0;
static const uint8_t Key2_Inhibit_St_InitialValue = 0;
static const uint8_t Key3_Inhibit_St_InitialValue = 0;
static const uint8_t Key4_Inhibit_St_InitialValue = 0;
static const uint8_t RKE_u8UnlockCounter_WF_InitialValue = 0;
static const uint8_t RKE_u8SearchCounter_WF_InitialValue = 0;
static const uint8_t KE_u8LockCounter_WF_InitialValue = 0;
static const uint8_t PKE_Count_WF_InitialValue = 0;
static const uint32_t WKUPFALG_WF_InitialValue = 0;
static const uint8_t DLC_u8DrvPESts_WF_InitialValue = 0;
static const uint8_t SSB_u8SWSts_WF_InitialValue = 0;
static const uint8_t PKE_AuthResult_WF_InitialValue = 0;
static const uint8_t FEE_DTCWriteIdleFlag_WF_InitialValue = 0;
static const uint8_t PMM_u8PwrStsLoad_WF_InitialValue = 0;
static const uint8_t SWK_u8NmSleepSt_WF_InitialValue = 0;
static const uint8_t DLC_u8PasPESts_WF_InitialValue = 0;
static const uint8_t PEPS_SUB_ID_InitialValue = 0;
static const uint32_t PEPS_AuthResp_InitialValue = 0;
static const uint16_t ManufacturerCode_InitialValue = 0;
static const uint8_t EngOperatingState_InitialValue = 0;
static const uint8_t TransCurrentGear_InitialValue = 0;
static const uint8_t ESCL_St_InitialValue = 0;
static const uint8_t ESCL_WarnSafety_InitialValue = 0;
static const uint8_t ESCL_PromptRotateSteerWheel_InitialValue = 0;
static const uint8_t AliveCounter_InitialValue = 0;
static const uint8_t ESCL1_RX_CRC_InitialValue = 0;
static const uint8_t ESCL_SUB_ID_InitialValue = 0;
static const uint32_t ESCL_AuthChallenge_InitialValue = 0;
static const uint8_t ESCL_AuthResult_InitialValue = 0;
static const uint8_t Destination_Address_InitialValue = 0;
static const uint8_t SecAlarm_InitialValue = 0;
static const uint8_t ESCL_u8SleepFlag_NM_WF_InitialValue = 0;
static const uint8_t WIN_u8SleepFlag_NM_WF_InitialValue = 0;
static const uint8_t ACC_u8SleepFlag_NM_WF_InitialValue = 0;
static const uint8_t RMH_u8SleepFlag_NM_WF_InitialValue = 0;
static const uint8_t DLC_u8SleepFlag_NM_WF_InitialValue = 0;
static const uint8_t SAC_u8SleepFlag_NM_WF_InitialValue = 0;
static const uint8_t HORN_u8SleepFlag_NM_WF_InitialValue = 0;
static const uint8_t TUL_u8SleepFlag_NM_WF_InitialValue = 0;
static const uint8_t FMHL_u8SleepFlag_NM_WF_InitialValue = 0;
static const uint8_t AHL_u8SleepFlag_NM_WF_InitialValue = 0;
static const uint8_t POL_u8SleepFlag_NM_WF_InitialValue = 0;
static const uint8_t LBL_u8SleepFlag_NM_WF_InitialValue = 0;
static const uint8_t HBL_u8SleepFlag_NM_WF_InitialValue = 0;
static const uint8_t FFL_u8SleepFlag_NM_WF_InitialValue = 0;
static const uint8_t DW_State_RX_MechKeySt_InitialValue = 0;
static const uint8_t RFL_u8SleepFlag_NM_WF_InitialValue = 0;
static const uint8_t DRL_u8SleepFlag_NM_WF_InitialValue = 0;
static const uint8_t BRL_u8SleepFlag_NM_WF_InitialValue = 0;
static const uint8_t SLED_u8SleepFlag_WF_InitialValue = 0;
static const uint8_t DML_u8LampSleepFlag_NM_WF_InitialValue = 0;
static const uint8_t LOL_u8SleepFlag_NM_WF_InitialValue = 0;
static const uint8_t WDIL_u8SleepFlag_NM_WF_InitialValue = 0;
static const uint8_t SKC_u8SleepFlag_WF_InitialValue = 0;
static const uint8_t DLC_u8UnlockSource_WF_InitialValue = 0;
static const uint8_t ON_SW_WF_InitialValue = 0;
static const uint8_t ST_SW_WF_InitialValue = 0;
static const uint8_t ACC_SW_WF_InitialValue = 0;
static const uint8_t Lighting_Sensor_WF_InitialValue = 0;
static const uint8_t VehicleVoltage_InitialValue = 0;
static const uint8_t Mirror_Heat_SW_WF_InitialValue = 0;
static const uint8_t LOGO_SW_WF_InitialValue = 0;
static const uint8_t Window_Inhibite_SW_WF_InitialValue = 0;
static const uint8_t Key_IN_WF_InitialValue = 0;
static const uint8_t Reserve1_SW_WF_InitialValue = 0;
static const uint8_t Reserve5_SW_WF_InitialValue = 0;
static const uint8_t FL_TL_LED_Fb_WF_InitialValue = 0;
static const uint8_t FR_TL_LED_Fb_WF_InitialValue = 0;
static const uint8_t Reserve2_SW_WF_InitialValue = 0;
static const uint8_t Reserve3_SW_WF_InitialValue = 0;
static const uint8_t Reserve4_SW_WF_InitialValue = 0;
static const uint8_t DIL_Brake_WF_InitialValue = 0;
static const uint8_t SSB_SW1_WF_InitialValue = 0;
static const uint8_t DIH_SSB_SW2_WF_InitialValue = 0;
static const uint8_t RDoor_SW_WF_InitialValue = 0;
static const uint8_t LDoor_SW_WF_InitialValue = 0;
static const uint8_t DoorOpenSw_InitialValue = 0;
static const uint8_t EEC1_EngTorqueMode_InitialValue = 0;
static const uint8_t EEC1_ActlEngPrcntTrqueHighResolution_InitialValue = 0;
static const uint8_t EEC1_DriversDemandPercentTorque_InitialValue = 0;
static const uint8_t EEC1_ActualEngPercentTorque_InitialValue = 0;
static const uint16_t EEC1_EngSpeed_InitialValue = 0;
static const uint8_t EEC1_ECU_SA_InitialValue = 0;
static const uint8_t EEC1_EngDemandPercentTorque_InitialValue = 0;
static const uint8_t ParkingBrakeSwitch_InitialValue = 0;
static const uint16_t VBUS_VCU4_N_VehicleSpeed_InitialValue = 0;
static const uint8_t VBUS_VCU4_St_Gears_InitialValue = 0;
static const uint8_t VBUS_VCU4_St_Ready_InitialValue = 0;
static const uint8_t VBUS_VCU4_St_BrakeSta_InitialValue = 0;
static const uint16_t TachographVehicleSpeed_InitialValue = 0;
static const uint8_t TireLocation_InitialValue = 0;
static const uint8_t TirePressure_InitialValue = 0;
static const uint16_t TireTemperature_InitialValue = 0;
static const uint8_t WheelSensorStatus_InitialValue = 0;
static const uint8_t TireStatus_InitialValue = 0;
static const uint8_t Tire_Sensor_Electrical_Fault_InitialValue = 0;
static const uint16_t Tire_Air_Leakage_Rate_InitialValue = 0;
static const uint8_t TirePressureThresholdDetection_InitialValue = 0;
static const uint8_t DM1_TPMS_ProtectLampStatus_InitialValue = 0;
static const uint8_t DM1_TPMS_AmberWarningLampStatus_InitialValue = 0;
static const uint8_t DM1_TPMS_RedStopLampState_InitialValue = 0;
static const uint8_t LeastByteofSPN_InitialValue = 0;
static const uint8_t SecondByteofSPN_InitialValue = 0;
static const uint8_t FMI_InitialValue = 0;
static const uint8_t _3MostBitofSPN_InitialValue = 0;
static const uint8_t OC_InitialValue = 0;
static const uint8_t CM_InitialValue = 0;
static const uint8_t EBC1_ASREngCtrlActive_InitialValue = 0;
static const uint8_t EBC1_ASRBrakeCtrlActive_InitialValue = 0;
static const uint8_t EBC1_AntiLockBrakingActive_InitialValue = 0;
static const uint8_t EBC1_EBSBrakeSwitch_InitialValue = 0;
static const uint8_t EBC1_Brake_Pedal_Position_InitialValue = 0;
static const uint8_t EBC1_ABS_OffRoad_switch_InitialValue = 0;
static const uint8_t EBC1_ASR_OffRoad_switch_InitialValue = 0;
static const uint8_t EBC1_ASR_HillHolder_switch_InitialValue = 0;
static const uint8_t EBC1_Traction_ControlOverride_switch_InitialValue = 0;
static const uint8_t ABS_Fully_Operational_InitialValue = 0;
static const uint8_t EBC1_EBSRedWarningSignal_InitialValue = 0;
static const uint8_t EBC1_ABS_EBSAmberWarningSignal_InitialValue = 0;
static const uint8_t EBC1_ATC_ASRInformationSignal_InitialValue = 0;
static const uint8_t Foundation_Brake_Use_InitialValue = 0;
static const uint8_t XBR_System_State_InitialValue = 0;
static const uint8_t XBR_Active_Control_Mode_InitialValue = 0;
static const uint8_t XBR_Acceleration_Limit_InitialValue = 0;
static const uint8_t Parking_Brake_Actuator_Fully_Activated_InitialValue = 0;
static const uint8_t Emergency_Braking_Active_InitialValue = 0;
static const uint8_t DLCC1_EngAmberWarningLampCmd_InitialValue = 0;
static const uint8_t DLCC1_EngRedStopLampCmd_InitialValue = 0;
static const uint8_t DLCC1_OBDMalfunctionLampCmd_InitialValue = 0;
static const uint8_t DLCC1_EngBrakeActiveLampCmd_InitialValue = 0;
static const uint8_t DLCC1_EngOilPressLowLampCmd_InitialValue = 0;
static const uint8_t DLCC1_EngCoolantTempHighLampCmd_InitialValue = 0;
static const uint8_t DLCC1_EngCoolantLevelLowLampCmd_InitialValue = 0;
static const uint8_t CCVS1_TwoSpeedAxleSwitch_InitialValue = 0;
static const uint8_t CCVS1_ParkingBrakeSwitch_InitialValue = 0;
static const uint16_t CCVS1_WheelBasedVehicleSpeed_InitialValue = 0;
static const uint8_t CCVS1_CruiseCtrlActive_InitialValue = 0;
static const uint8_t CCVS1_CruiseCtrlEnableSwitch_InitialValue = 0;
static const uint8_t CCVS1_BrakeSwitch_InitialValue = 0;
static const uint8_t CCVS1_ClutchSwitch_InitialValue = 0;
static const uint8_t CCVS1_CruiseCtrlSetSwitch_InitialValue = 0;
static const uint8_t CCVS1_CruiseCtrlCoastSwitch_InitialValue = 0;
static const uint8_t CCVS1_CruiseCtrlResumeSwitch_InitialValue = 0;
static const uint8_t CCVS1_CruiseCtrlAccelerateSwitch_InitialValue = 0;
static const uint8_t CCVS1_CruiseCtrlSetSpeed_InitialValue = 0;
static const uint8_t CCVS1_PTOGovernorState_InitialValue = 0;
static const uint8_t CCVS1_CruiseCtrlStates_InitialValue = 0;
static const uint8_t VDC1_VDCInformationSignal_InitialValue = 0;
static const uint8_t VDC1_VDCFullyOperational_InitialValue = 0;
static const uint8_t VDC1_VDC_brake_light_request_InitialValue = 0;
static const uint8_t VDC1_ROPEngCtrlActive_InitialValue = 0;
static const uint8_t VDC1_ROPBrakeCtrlActive_InitialValue = 0;
static const uint8_t VDC1_YCEngCtrlActive_InitialValue = 0;
static const uint8_t VDC1_YCBrakeCtrlActive_InitialValue = 0;
static const uint8_t ERC1_RX_ERC1_ActualRetarderPercentTorque_InitialValue = 0;
static const uint8_t ERC3_RX_ERC1_ActualRetarderPercentTorque_InitialValue = 0;
static const uint8_t TransReverseDirectionSw_InitialValue = 0;
static const uint8_t TransNeutralSwitch_InitialValue = 0;
static const uint8_t ECC_Work_Switch_InitialValue = 0;
static const uint8_t ECC_COMP_ReqSwitch_InitialValue = 0;
static const uint8_t ECC_WPTC_ReqSwitch_InitialValue = 0;
static const uint8_t REC_Switch_InitialValue = 0;
static const uint8_t Fan_Gear_Switch_InitialValue = 0;
static const uint8_t HVAC_MODE_Switch_InitialValue = 0;
static const uint8_t HVAC_SET_Temp_Switch_InitialValue = 0;
static const uint8_t One_click_defrosting_InitialValue = 0;
static const uint8_t ECC_Work_Status_InitialValue = 0;
static const uint8_t ECC_COMP_ReqStatus_InitialValue = 0;
static const uint8_t REC_Status_InitialValue = 0;
static const uint8_t Fan_Gear_InitialValue = 0;
static const uint8_t HVAC_MODE_Status_InitialValue = 0;
static const uint8_t HVAC_SET_Temp_InitialValue = 0;
static const uint8_t EVAP_Temp_InitialValue = 0;
static const uint8_t MID_PRESS_Status_InitialValue = 0;
static const uint8_t H_L_PRESS_Sta_InitialValue = 0;
static const uint8_t One_click_defrosting_Status_InitialValue = 0;
static const uint8_t N_Shift_WF_InitialValue = 0;
static const uint8_t AI_Clutch_WF_InitialValue = 0;
static const uint8_t StartupSts_Fb_WF_InitialValue = 0;
static const uint8_t High_low_Voltage_SW_WF_InitialValue = 0;
static const uint8_t AC_DOH_WF_InitialValue = 0;
static const uint8_t D1_Diag_WF_InitialValue = 0;
static const uint8_t D2_Diag_WF_InitialValue = 0;
static const uint8_t D3_Diag_WF_InitialValue = 0;
static const uint8_t D4_Diag_WF_InitialValue = 0;
static const uint8_t D5_Diag_WF_InitialValue = 0;
static const uint8_t D6_Diag_WF_InitialValue = 0;
static const uint8_t D7_Diag_WF_InitialValue = 0;
static const uint8_t D8_Diag_WF_InitialValue = 0;
static const uint8_t D9_Diag_WF_InitialValue = 0;
static const uint8_t D10_Diag_WF_InitialValue = 0;
static const uint8_t D11_Diag_WF_InitialValue = 0;
static const uint8_t D12_Diag_WF_InitialValue = 0;
static const uint8_t D13_Diag_WF_InitialValue = 0;
static const uint8_t D14_Diag_WF_InitialValue = 0;
static const uint8_t D15_Diag_WF_InitialValue = 0;
static const uint8_t D16_Diag_WF_InitialValue = 0;
static const uint8_t D17_Diag_WF_InitialValue = 0;
static const uint8_t D18_Diag_WF_InitialValue = 0;
static const uint8_t D19_Diag_WF_InitialValue = 0;
static const uint8_t D20_Diag_WF_InitialValue = 0;
static const uint8_t D21_Diag_WF_InitialValue = 0;
static const uint8_t D22_Diag_WF_InitialValue = 0;
static const uint8_t D23_Diag_WF_InitialValue = 0;
static const uint8_t D24_Diag_WF_InitialValue = 0;
static const uint8_t D25_Diag_WF_InitialValue = 0;
static const uint8_t D26_Diag_WF_InitialValue = 0;
static const uint8_t D27_Diag_WF_InitialValue = 0;
static const uint8_t D28_Diag_WF_InitialValue = 0;
static const uint8_t D29_Diag_WF_InitialValue = 0;
static const uint8_t D30_Diag_WF_InitialValue = 0;
static const uint8_t D31_Diag_WF_InitialValue = 0;
static const uint8_t D32_Diag_WF_InitialValue = 0;
static const uint8_t D33_Diag_WF_InitialValue = 0;
static const uint8_t D34_Diag_WF_InitialValue = 0;
static const uint8_t D35_Diag_WF_InitialValue = 0;
static const uint8_t D36_Diag_WF_InitialValue = 0;
static const uint8_t D38_Diag_WF_InitialValue = 0;
static const uint8_t D39_Diag_WF_InitialValue = 0;
static const uint8_t D40_Diag_WF_InitialValue = 0;
static const uint8_t D41_Diag_WF_InitialValue = 0;
static const uint8_t Wiper_H_RlyCoil_Ctrl_WF_InitialValue = 0;
static const uint8_t Blower_RlyCoil_Ctrl_WF_InitialValue = 0;
static const uint8_t IG_Fb_WF_InitialValue = 0;
static const uint8_t IG_RlyCoil_Ctrl_WF_InitialValue = 0;
static const uint8_t ACC_Fb_WF_InitialValue = 0;
static const uint8_t ACC_RlyCoil_Ctrl_WF_InitialValue = 0;
static const uint8_t Horn_RlyCoil_Ctrl_WF_InitialValue = 0;
static const uint8_t Wiper_Power_RlyCoil_Ctrl_WF_InitialValue = 0;
static const uint8_t Startup_SIG_WF_InitialValue = 0;
static const uint8_t F_LOGO_Lamp_WF_InitialValue = 0;
static const uint8_t Washer_Motor_WF_InitialValue = 0;
static const uint8_t HSD1_Reserve_WF_InitialValue = 0;
static const uint8_t Battery_Saver_WF_InitialValue = 0;
static const uint8_t Dome_Lamp_WF_InitialValue = 0;
static const uint8_t LSD1_Reserve_WF_InitialValue = 0;
static const uint8_t LSD2_Reserve_WF_InitialValue = 0;
static const uint8_t Window_Indication_Lamp_WF_InitialValue = 0;
static const uint8_t IDM_COMP_ReqStatus_InitialValue = 0;
static const uint8_t F_FOG_RlyCoil_Ctrl_WF_InitialValue = 0;
static const uint8_t POS_RlyCoil_Ctrl_WF_InitialValue = 0;
static const uint8_t LB_RlyCoil_Ctrl_WF_InitialValue = 0;
static const uint8_t HB_RlyCoil_Ctrl_WF_InitialValue = 0;
static const uint8_t FL_Wind_Up_RlyCoil_Ctrl_WF_InitialValue = 0;
static const uint8_t FL_Wind_Down_RlyCoil_Ctrl_WF_InitialValue = 0;
static const uint8_t FR_Wind_Up_RlyCoil_Ctrl_WF_InitialValue = 0;
static const uint8_t FR_Wind_Down_RlyCoil_Ctrl_WF_InitialValue = 0;
static const uint8_t RL_Wind_Up_RlyCoil_Ctrl_WF_InitialValue = 0;
static const uint8_t RL_Wind_Down_RlyCoil_Ctrl_WF_InitialValue = 0;
static const uint8_t RR_Wind_Up_RlyCoil_Ctrl_WF_InitialValue = 0;
static const uint8_t RR_Wind_Down_RlyCoil_Ctrl_WF_InitialValue = 0;
static const uint8_t Center_Unlock_RlyCoil_Ctrl_WF_InitialValue = 0;
static const uint8_t Center_Lock_RlyCoil_Ctrl_WF_InitialValue = 0;
static const uint8_t Mirror_Heat_RlyCoil_Ctrl_WF_InitialValue = 0;
static const uint8_t Horn_SW_WF_InitialValue = 0;
static const uint8_t FL_Wind_Gnd_Ctrl_WF_InitialValue = 0;
static const uint8_t FR_Wind_Gnd_Ctrl_WF_InitialValue = 0;
static const uint8_t RL_Wind_Gnd_Ctrl_WF_InitialValue = 0;
static const uint8_t RR_Wind_Gnd_Ctrl_WF_InitialValue = 0;
static const uint8_t LSD_SSB_LED3_WF_InitialValue = 0;
static const uint8_t LSD_SSB_LED2_WF_InitialValue = 0;
static const uint8_t LSD_SSB_LED1_WF_InitialValue = 0;
static const uint8_t Condensing_Fan_Low_Ctrl_WF_InitialValue = 0;
static const uint8_t Condensing_Fan_High_Ctrl_WF_InitialValue = 0;
static const uint8_t Int_Ext_Motor_Inc_WF_InitialValue = 0;
static const uint8_t Int_Ext_Motor_Dec_WF_InitialValue = 0;
static const uint8_t Cold_Heat_Motor_Inc_WF_InitialValue = 0;
static const uint8_t Cold_Heat_Motor_Dec_WF_InitialValue = 0;
static const uint8_t Mode_Motor_Inc_WF_InitialValue = 0;
static const uint8_t Mode_MotoR_Dec_WF_InitialValue = 0;
static const uint8_t IDM_LPOWER_InitialValue = 0;
static const uint16_t FL_Gnd_Ctrl_WF_InitialValue = 0;
static const uint16_t FR_Gnd_Ctrl_WF_InitialValue = 0;
static const uint16_t RL_Wind_Samp_WF_InitialValue = 0;
static const uint16_t RR_Wind_Samp_WF_InitialValue = 0;
static const uint16_t Blower_Analog_Out_WF_InitialValue = 0;
static const uint16_t Cold_Heat_Motor_Fb_WF_InitialValue = 0;
static const uint16_t Mode_MotoR_WF_InitialValue = 0;
static const uint8_t ControlByte_InitialValue = 0;
static const uint16_t TotalNumberOfBbytes_InitialValue = 0;
static const uint8_t TotalNumberOfPackets_InitialValue = 0;
static const uint32_t ParameterGroupNumber_InitialValue = 0;
static const uint8_t SequenceNumber_InitialValue = 0;
static const uint8_t TX_COUNTER_InitialValue = 0;
static const uint8_t TX_FLAG_InitialValue = 1;
static const uint16_t TX_LEVEL_InitialValue = 2748;
static const uint8_t LedRunMode_InitialValue = 3;
static const uint8_t LedOut_InitialValue = 0;
static const uint8_t LedBlinkPhase_InitialValue = 0;
static const uint8_t LedFaultTimeout_InitialValue = 0;
static const uint8_t LedFaultCmd_InitialValue = 0;
static const uint8_t RX_COUNTER_InitialValue = 0;
static const uint8_t RX_COUNTER_TimeoutSubstitutionValue = 238;
static const uint16_t RX_TEMP_InitialValue = 0;

static uint8_t Com_PduData_BCM_LCSF_TX[8];
static uint8_t Com_PduData_BCM_Ctrl_TX[8];
static uint8_t Com_PduData_BCM_OEL_TX[8];
static uint8_t Com_PduData_BCM_OWW_TX[8];
static uint8_t Com_PduData_BCM_DoorCtrl_TX[8];
static uint8_t Com_PduData_BCM_DM1_TX[8];
static uint8_t Com_PduData_Crash_Notification_RX[8];
static uint8_t Com_PduData_AMB_Ambient_Conditions_RX[8];
static uint8_t Com_PduData_PEPS1_RX[8];
static uint8_t Com_PduData_PEPS2_RX[8];
static uint8_t Com_PduData_PEPS_ESCLM_RX[5];
static uint8_t Com_PduData_ACL_RX[8];
static uint8_t Com_PduData_EOI_RX[8];
static uint8_t Com_PduData_ETC2_RX[8];
static uint8_t Com_PduData_ESCL1_RX[8];
static uint8_t Com_PduData_ESCLM_PEPS_RX[8];
static uint8_t Com_PduData_ESCL_NM_RX[8];
static uint8_t Com_PduData_DW_State_RX[8];
static uint8_t Com_PduData_IC_MSG_RX[8];
static uint8_t Com_PduData_EEC1_Electronic_Engine_Controller_1_RX[8];
static uint8_t Com_PduData_CCVS_RX[8];
static uint8_t Com_PduData_VCU_4_RX[8];
static uint8_t Com_PduData_TCO1_RX[8];
static uint8_t Com_PduData_TireCondition_RX[8];
static uint8_t Com_PduData_DM1_TPMS_RX[8];
static uint8_t Com_PduData_EBC1_Electronic_Brake_Controller_1_RX[8];
static uint8_t Com_PduData_EBC5_Electronic_Brake_Controller_5_RX[8];
static uint8_t Com_PduData_DLCC1_Direct_Lamp_Control_Command_1_RX[8];
static uint8_t Com_PduData_CCVS1_Cruise_Control_Vehicle_Speed_1_RX[8];
static uint8_t Com_PduData_VDC1_Vehicle_Dynamic_Stability_Control_1_RX[8];
static uint8_t Com_PduData_ERC1_RX[8];
static uint8_t Com_PduData_ERC3_RX[8];
static uint8_t Com_PduData_ETC5_RX[8];
static uint8_t Com_PduData_EEC3_RX[8];
static uint8_t Com_PduData_ECC2_RX[8];
static uint8_t Com_PduData_ID1_RX[8];
static uint8_t Com_PduData_ID2_RX[8];
static uint8_t Com_PduData_ID3_RX[8];
static uint8_t Com_PduData_TP_CM_RX[8];
static uint8_t Com_PduData_TP_DT_RX[8];
static uint8_t Com_PduData_CANTEST_TX_TEST[8];
static uint8_t Com_PduData_CANTEST_RX_TEST[8];

static Com_IPduTxContextType Com_IPduTxContext_BCM_LCSF_TX;
static Com_IPduTxContextType Com_IPduTxContext_BCM_Ctrl_TX;
static Com_IPduTxContextType Com_IPduTxContext_BCM_OEL_TX;
static Com_IPduTxContextType Com_IPduTxContext_BCM_OWW_TX;
static Com_IPduTxContextType Com_IPduTxContext_BCM_DoorCtrl_TX;
static Com_IPduTxContextType Com_IPduTxContext_BCM_DM1_TX;
static Com_IPduRxContextType Com_IPduRxContext_Crash_Notification_RX;
static Com_IPduRxContextType Com_IPduRxContext_AMB_Ambient_Conditions_RX;
static Com_IPduRxContextType Com_IPduRxContext_PEPS1_RX;
static Com_IPduRxContextType Com_IPduRxContext_PEPS2_RX;
static Com_IPduRxContextType Com_IPduRxContext_PEPS_ESCLM_RX;
static Com_IPduRxContextType Com_IPduRxContext_ACL_RX;
static Com_IPduRxContextType Com_IPduRxContext_EOI_RX;
static Com_IPduRxContextType Com_IPduRxContext_ETC2_RX;
static Com_IPduRxContextType Com_IPduRxContext_ESCL1_RX;
static Com_IPduRxContextType Com_IPduRxContext_ESCLM_PEPS_RX;
static Com_IPduRxContextType Com_IPduRxContext_ESCL_NM_RX;
static Com_IPduRxContextType Com_IPduRxContext_DW_State_RX;
static Com_IPduRxContextType Com_IPduRxContext_IC_MSG_RX;
static Com_IPduRxContextType Com_IPduRxContext_EEC1_Electronic_Engine_Controller_1_RX;
static Com_IPduRxContextType Com_IPduRxContext_CCVS_RX;
static Com_IPduRxContextType Com_IPduRxContext_VCU_4_RX;
static Com_IPduRxContextType Com_IPduRxContext_TCO1_RX;
static Com_IPduRxContextType Com_IPduRxContext_TireCondition_RX;
static Com_IPduRxContextType Com_IPduRxContext_DM1_TPMS_RX;
static Com_IPduRxContextType Com_IPduRxContext_EBC1_Electronic_Brake_Controller_1_RX;
static Com_IPduRxContextType Com_IPduRxContext_EBC5_Electronic_Brake_Controller_5_RX;
static Com_IPduRxContextType Com_IPduRxContext_DLCC1_Direct_Lamp_Control_Command_1_RX;
static Com_IPduRxContextType Com_IPduRxContext_CCVS1_Cruise_Control_Vehicle_Speed_1_RX;
static Com_IPduRxContextType Com_IPduRxContext_VDC1_Vehicle_Dynamic_Stability_Control_1_RX;
static Com_IPduRxContextType Com_IPduRxContext_ERC1_RX;
static Com_IPduRxContextType Com_IPduRxContext_ERC3_RX;
static Com_IPduRxContextType Com_IPduRxContext_ETC5_RX;
static Com_IPduRxContextType Com_IPduRxContext_EEC3_RX;
static Com_IPduRxContextType Com_IPduRxContext_ECC2_RX;
static Com_IPduRxContextType Com_IPduRxContext_ID1_RX;
static Com_IPduRxContextType Com_IPduRxContext_ID2_RX;
static Com_IPduRxContextType Com_IPduRxContext_ID3_RX;
static Com_IPduRxContextType Com_IPduRxContext_TP_CM_RX;
static Com_IPduRxContextType Com_IPduRxContext_TP_DT_RX;
static Com_IPduTxContextType Com_IPduTxContext_CANTEST_TX_TEST;
static Com_IPduRxContextType Com_IPduRxContext_CANTEST_RX_TEST;

#ifdef COM_USE_SIGNAL_CONFIG
static const Com_SignalTxConfigType Com_SignalTxConfig_BCM_LowBeamSts = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_BCM_HighBeamSts = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_BCM_FrontFogSts = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_BCM_TurnRLightSts = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_BCM_TurnLLightSts = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_BCM_DRLSts = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_BCM_PositionLightSts = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_BCM_RearFogSts = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_BackUpLightSt = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_BrakelightST = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_InteriorLampSt = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_BCM_PassWindowLcokSw = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_CentralLockSw = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_MRightFrontWinSw = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_MLeftFrontWinSw = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_RightFrontWinSw = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_MRightRearWinSw = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_MLeftRearWinSw = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_RightRearWinSw = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_LeftRearWinSw = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_BCM_Ctrl_TX_MechKeySt = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_LeftFrontWinSt = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_RightFrontWinSt = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_LeftRearWinSt = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_RightRearWinSt = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_DoorLockMotorState = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_RemoteDoorState = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_LeftFrontWinErrorSt = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_RightFrontWinErrorSt = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_LeftRearWinErrorSt = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_RightRearWinErrorSt = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_HazardSw = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_HazardSt = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_WiperSt = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_SKC_u8PEPSICUIndCnt_WF = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_PRM_u8PEPSICUIndCnt_WF = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_ATP_u8DrvLockRotor_WF = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_ESCL_u8AuthReqCnt_WF = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_BCM_OpenStatusofDdoor = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_BCM_OpenStatusofPdoor = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_BCM_OpenStatusofLeftReardoor = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_BCM_OpenStatusofRightReardoor = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_BASE_u8AuthResultCnt_WF = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_BSW_TPMS_FrameCnt_WF = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_PAM_u8SleepFlag_WF = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_ATP_u8PasLockRotor_WF = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_FEE_APPWriteIdleFlag_WF = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_FEE_BOOTWriteIdleFlag_WF = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_WIN_u8DrvWinCmdCAN_WF = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_WIN_u8PasWinCmdCAN_WF = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_TUL_u8HonkingStyle_WF = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_DLC_u8LockSource_WF = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_HornRelaySt = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_BrakeLightWarning = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_LF_SendCounter_WF = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_LF_Commond_WF = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_DM1_MalfunctionIndicatorLampStatus = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_DM1_RedStopLampState = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_BCM_LeastByteofSPN = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_BCM_SecondByteofSPN = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_BCM_FMI = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_BCM_3MostBitofSPN = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_BCM_OC = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_BCM_CM = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static Com_SignalRxContextType Com_SignalRxContext_SRS_Crash_Type;
static const Com_SignalRxConfigType Com_SignalRxConfig_SRS_Crash_Type = {
  &Com_SignalRxContext_SRS_Crash_Type,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_AMB_BarometricPress;
static const Com_SignalRxConfigType Com_SignalRxConfig_AMB_BarometricPress = {
  &Com_SignalRxContext_AMB_BarometricPress,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_LFE1_AmbientAirTemp;
static const Com_SignalRxConfigType Com_SignalRxConfig_LFE1_AmbientAirTemp = {
  &Com_SignalRxContext_LFE1_AmbientAirTemp,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_LFE1_EngAirIntakeTemp;
static const Com_SignalRxConfigType Com_SignalRxConfig_LFE1_EngAirIntakeTemp = {
  &Com_SignalRxContext_LFE1_EngAirIntakeTemp,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_PEPsKeyInState;
static const Com_SignalRxConfigType Com_SignalRxConfig_PEPsKeyInState = {
  &Com_SignalRxContext_PEPsKeyInState,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_PEPS_PkeLockCmd;
static const Com_SignalRxConfigType Com_SignalRxConfig_PEPS_PkeLockCmd = {
  &Com_SignalRxContext_PEPS_PkeLockCmd,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_PEPS_PowerMode;
static const Com_SignalRxConfigType Com_SignalRxConfig_PEPS_PowerMode = {
  &Com_SignalRxContext_PEPS_PowerMode,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_PEPS_ESCLInhabitSt;
static const Com_SignalRxConfigType Com_SignalRxConfig_PEPS_ESCLInhabitSt = {
  &Com_SignalRxContext_PEPS_ESCLInhabitSt,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_PEPS_EmergencyST;
static const Com_SignalRxConfigType Com_SignalRxConfig_PEPS_EmergencyST = {
  &Com_SignalRxContext_PEPS_EmergencyST,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_PEPS_KeyAuthenticationSt_PEPS;
static const Com_SignalRxConfigType Com_SignalRxConfig_PEPS_KeyAuthenticationSt_PEPS = {
  &Com_SignalRxContext_PEPS_KeyAuthenticationSt_PEPS,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_ESCL_failure;
static const Com_SignalRxConfigType Com_SignalRxConfig_ESCL_failure = {
  &Com_SignalRxContext_ESCL_failure,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_PEPS_failure;
static const Com_SignalRxConfigType Com_SignalRxConfig_PEPS_failure = {
  &Com_SignalRxContext_PEPS_failure,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Key_Not_Found;
static const Com_SignalRxConfigType Com_SignalRxConfig_Key_Not_Found = {
  &Com_SignalRxContext_Key_Not_Found,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Key_Battery_Low;
static const Com_SignalRxConfigType Com_SignalRxConfig_Key_Battery_Low = {
  &Com_SignalRxContext_Key_Battery_Low,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_PEPS_PEPSICUInd;
static const Com_SignalRxConfigType Com_SignalRxConfig_PEPS_PEPSICUInd = {
  &Com_SignalRxContext_PEPS_PEPSICUInd,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_PEPsKeyInFeedback;
static const Com_SignalRxConfigType Com_SignalRxConfig_PEPsKeyInFeedback = {
  &Com_SignalRxContext_PEPsKeyInFeedback,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_ACC_FB;
static const Com_SignalRxConfigType Com_SignalRxConfig_ACC_FB = {
  &Com_SignalRxContext_ACC_FB,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_IGN1_FB;
static const Com_SignalRxConfigType Com_SignalRxConfig_IGN1_FB = {
  &Com_SignalRxContext_IGN1_FB,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_PEPsKeyOutFeedback;
static const Com_SignalRxConfigType Com_SignalRxConfig_PEPsKeyOutFeedback = {
  &Com_SignalRxContext_PEPsKeyOutFeedback,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Alive_counter;
static const Com_SignalRxConfigType Com_SignalRxConfig_Alive_counter = {
  &Com_SignalRxContext_Alive_counter,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_PEPS1_RX_CRC;
static const Com_SignalRxConfigType Com_SignalRxConfig_PEPS1_RX_CRC = {
  &Com_SignalRxContext_PEPS1_RX_CRC,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Key1_Inside_St;
static const Com_SignalRxConfigType Com_SignalRxConfig_Key1_Inside_St = {
  &Com_SignalRxContext_Key1_Inside_St,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Key2_Inside_St;
static const Com_SignalRxConfigType Com_SignalRxConfig_Key2_Inside_St = {
  &Com_SignalRxContext_Key2_Inside_St,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Key3_Inside_St;
static const Com_SignalRxConfigType Com_SignalRxConfig_Key3_Inside_St = {
  &Com_SignalRxContext_Key3_Inside_St,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Key4_Inside_St;
static const Com_SignalRxConfigType Com_SignalRxConfig_Key4_Inside_St = {
  &Com_SignalRxContext_Key4_Inside_St,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Key1_Inhibit_St;
static const Com_SignalRxConfigType Com_SignalRxConfig_Key1_Inhibit_St = {
  &Com_SignalRxContext_Key1_Inhibit_St,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Key2_Inhibit_St;
static const Com_SignalRxConfigType Com_SignalRxConfig_Key2_Inhibit_St = {
  &Com_SignalRxContext_Key2_Inhibit_St,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Key3_Inhibit_St;
static const Com_SignalRxConfigType Com_SignalRxConfig_Key3_Inhibit_St = {
  &Com_SignalRxContext_Key3_Inhibit_St,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Key4_Inhibit_St;
static const Com_SignalRxConfigType Com_SignalRxConfig_Key4_Inhibit_St = {
  &Com_SignalRxContext_Key4_Inhibit_St,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_RKE_u8UnlockCounter_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_RKE_u8UnlockCounter_WF = {
  &Com_SignalRxContext_RKE_u8UnlockCounter_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_RKE_u8SearchCounter_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_RKE_u8SearchCounter_WF = {
  &Com_SignalRxContext_RKE_u8SearchCounter_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_KE_u8LockCounter_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_KE_u8LockCounter_WF = {
  &Com_SignalRxContext_KE_u8LockCounter_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_PKE_Count_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_PKE_Count_WF = {
  &Com_SignalRxContext_PKE_Count_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_WKUPFALG_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_WKUPFALG_WF = {
  &Com_SignalRxContext_WKUPFALG_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_DLC_u8DrvPESts_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_DLC_u8DrvPESts_WF = {
  &Com_SignalRxContext_DLC_u8DrvPESts_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_SSB_u8SWSts_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_SSB_u8SWSts_WF = {
  &Com_SignalRxContext_SSB_u8SWSts_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_PKE_AuthResult_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_PKE_AuthResult_WF = {
  &Com_SignalRxContext_PKE_AuthResult_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_FEE_DTCWriteIdleFlag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_FEE_DTCWriteIdleFlag_WF = {
  &Com_SignalRxContext_FEE_DTCWriteIdleFlag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_PMM_u8PwrStsLoad_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_PMM_u8PwrStsLoad_WF = {
  &Com_SignalRxContext_PMM_u8PwrStsLoad_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_SWK_u8NmSleepSt_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_SWK_u8NmSleepSt_WF = {
  &Com_SignalRxContext_SWK_u8NmSleepSt_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_DLC_u8PasPESts_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_DLC_u8PasPESts_WF = {
  &Com_SignalRxContext_DLC_u8PasPESts_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_PEPS_SUB_ID;
static const Com_SignalRxConfigType Com_SignalRxConfig_PEPS_SUB_ID = {
  &Com_SignalRxContext_PEPS_SUB_ID,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_PEPS_AuthResp;
static const Com_SignalRxConfigType Com_SignalRxConfig_PEPS_AuthResp = {
  &Com_SignalRxContext_PEPS_AuthResp,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_ManufacturerCode;
static const Com_SignalRxConfigType Com_SignalRxConfig_ManufacturerCode = {
  &Com_SignalRxContext_ManufacturerCode,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_EngOperatingState;
static const Com_SignalRxConfigType Com_SignalRxConfig_EngOperatingState = {
  &Com_SignalRxContext_EngOperatingState,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_TransCurrentGear;
static const Com_SignalRxConfigType Com_SignalRxConfig_TransCurrentGear = {
  &Com_SignalRxContext_TransCurrentGear,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_ESCL_St;
static const Com_SignalRxConfigType Com_SignalRxConfig_ESCL_St = {
  &Com_SignalRxContext_ESCL_St,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_ESCL_WarnSafety;
static const Com_SignalRxConfigType Com_SignalRxConfig_ESCL_WarnSafety = {
  &Com_SignalRxContext_ESCL_WarnSafety,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_ESCL_PromptRotateSteerWheel;
static const Com_SignalRxConfigType Com_SignalRxConfig_ESCL_PromptRotateSteerWheel = {
  &Com_SignalRxContext_ESCL_PromptRotateSteerWheel,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_AliveCounter;
static const Com_SignalRxConfigType Com_SignalRxConfig_AliveCounter = {
  &Com_SignalRxContext_AliveCounter,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_ESCL1_RX_CRC;
static const Com_SignalRxConfigType Com_SignalRxConfig_ESCL1_RX_CRC = {
  &Com_SignalRxContext_ESCL1_RX_CRC,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_ESCL_SUB_ID;
static const Com_SignalRxConfigType Com_SignalRxConfig_ESCL_SUB_ID = {
  &Com_SignalRxContext_ESCL_SUB_ID,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_ESCL_AuthChallenge;
static const Com_SignalRxConfigType Com_SignalRxConfig_ESCL_AuthChallenge = {
  &Com_SignalRxContext_ESCL_AuthChallenge,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_ESCL_AuthResult;
static const Com_SignalRxConfigType Com_SignalRxConfig_ESCL_AuthResult = {
  &Com_SignalRxContext_ESCL_AuthResult,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Destination_Address;
static const Com_SignalRxConfigType Com_SignalRxConfig_Destination_Address = {
  &Com_SignalRxContext_Destination_Address,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_SecAlarm;
static const Com_SignalRxConfigType Com_SignalRxConfig_SecAlarm = {
  &Com_SignalRxContext_SecAlarm,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_ESCL_u8SleepFlag_NM_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_ESCL_u8SleepFlag_NM_WF = {
  &Com_SignalRxContext_ESCL_u8SleepFlag_NM_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_WIN_u8SleepFlag_NM_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_WIN_u8SleepFlag_NM_WF = {
  &Com_SignalRxContext_WIN_u8SleepFlag_NM_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_ACC_u8SleepFlag_NM_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_ACC_u8SleepFlag_NM_WF = {
  &Com_SignalRxContext_ACC_u8SleepFlag_NM_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_RMH_u8SleepFlag_NM_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_RMH_u8SleepFlag_NM_WF = {
  &Com_SignalRxContext_RMH_u8SleepFlag_NM_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_DLC_u8SleepFlag_NM_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_DLC_u8SleepFlag_NM_WF = {
  &Com_SignalRxContext_DLC_u8SleepFlag_NM_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_SAC_u8SleepFlag_NM_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_SAC_u8SleepFlag_NM_WF = {
  &Com_SignalRxContext_SAC_u8SleepFlag_NM_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_HORN_u8SleepFlag_NM_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_HORN_u8SleepFlag_NM_WF = {
  &Com_SignalRxContext_HORN_u8SleepFlag_NM_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_TUL_u8SleepFlag_NM_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_TUL_u8SleepFlag_NM_WF = {
  &Com_SignalRxContext_TUL_u8SleepFlag_NM_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_FMHL_u8SleepFlag_NM_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_FMHL_u8SleepFlag_NM_WF = {
  &Com_SignalRxContext_FMHL_u8SleepFlag_NM_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_AHL_u8SleepFlag_NM_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_AHL_u8SleepFlag_NM_WF = {
  &Com_SignalRxContext_AHL_u8SleepFlag_NM_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_POL_u8SleepFlag_NM_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_POL_u8SleepFlag_NM_WF = {
  &Com_SignalRxContext_POL_u8SleepFlag_NM_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_LBL_u8SleepFlag_NM_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_LBL_u8SleepFlag_NM_WF = {
  &Com_SignalRxContext_LBL_u8SleepFlag_NM_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_HBL_u8SleepFlag_NM_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_HBL_u8SleepFlag_NM_WF = {
  &Com_SignalRxContext_HBL_u8SleepFlag_NM_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_FFL_u8SleepFlag_NM_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_FFL_u8SleepFlag_NM_WF = {
  &Com_SignalRxContext_FFL_u8SleepFlag_NM_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_DW_State_RX_MechKeySt;
static const Com_SignalRxConfigType Com_SignalRxConfig_DW_State_RX_MechKeySt = {
  &Com_SignalRxContext_DW_State_RX_MechKeySt,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_RFL_u8SleepFlag_NM_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_RFL_u8SleepFlag_NM_WF = {
  &Com_SignalRxContext_RFL_u8SleepFlag_NM_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_DRL_u8SleepFlag_NM_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_DRL_u8SleepFlag_NM_WF = {
  &Com_SignalRxContext_DRL_u8SleepFlag_NM_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_BRL_u8SleepFlag_NM_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_BRL_u8SleepFlag_NM_WF = {
  &Com_SignalRxContext_BRL_u8SleepFlag_NM_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_SLED_u8SleepFlag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_SLED_u8SleepFlag_WF = {
  &Com_SignalRxContext_SLED_u8SleepFlag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_DML_u8LampSleepFlag_NM_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_DML_u8LampSleepFlag_NM_WF = {
  &Com_SignalRxContext_DML_u8LampSleepFlag_NM_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_LOL_u8SleepFlag_NM_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_LOL_u8SleepFlag_NM_WF = {
  &Com_SignalRxContext_LOL_u8SleepFlag_NM_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_WDIL_u8SleepFlag_NM_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_WDIL_u8SleepFlag_NM_WF = {
  &Com_SignalRxContext_WDIL_u8SleepFlag_NM_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_SKC_u8SleepFlag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_SKC_u8SleepFlag_WF = {
  &Com_SignalRxContext_SKC_u8SleepFlag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_DLC_u8UnlockSource_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_DLC_u8UnlockSource_WF = {
  &Com_SignalRxContext_DLC_u8UnlockSource_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_ON_SW_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_ON_SW_WF = {
  &Com_SignalRxContext_ON_SW_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_ST_SW_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_ST_SW_WF = {
  &Com_SignalRxContext_ST_SW_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_ACC_SW_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_ACC_SW_WF = {
  &Com_SignalRxContext_ACC_SW_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Lighting_Sensor_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_Lighting_Sensor_WF = {
  &Com_SignalRxContext_Lighting_Sensor_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_VehicleVoltage;
static const Com_SignalRxConfigType Com_SignalRxConfig_VehicleVoltage = {
  &Com_SignalRxContext_VehicleVoltage,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Mirror_Heat_SW_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_Mirror_Heat_SW_WF = {
  &Com_SignalRxContext_Mirror_Heat_SW_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_LOGO_SW_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_LOGO_SW_WF = {
  &Com_SignalRxContext_LOGO_SW_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Window_Inhibite_SW_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_Window_Inhibite_SW_WF = {
  &Com_SignalRxContext_Window_Inhibite_SW_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Key_IN_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_Key_IN_WF = {
  &Com_SignalRxContext_Key_IN_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Reserve1_SW_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_Reserve1_SW_WF = {
  &Com_SignalRxContext_Reserve1_SW_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Reserve5_SW_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_Reserve5_SW_WF = {
  &Com_SignalRxContext_Reserve5_SW_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_FL_TL_LED_Fb_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_FL_TL_LED_Fb_WF = {
  &Com_SignalRxContext_FL_TL_LED_Fb_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_FR_TL_LED_Fb_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_FR_TL_LED_Fb_WF = {
  &Com_SignalRxContext_FR_TL_LED_Fb_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Reserve2_SW_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_Reserve2_SW_WF = {
  &Com_SignalRxContext_Reserve2_SW_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Reserve3_SW_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_Reserve3_SW_WF = {
  &Com_SignalRxContext_Reserve3_SW_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Reserve4_SW_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_Reserve4_SW_WF = {
  &Com_SignalRxContext_Reserve4_SW_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_DIL_Brake_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_DIL_Brake_WF = {
  &Com_SignalRxContext_DIL_Brake_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_SSB_SW1_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_SSB_SW1_WF = {
  &Com_SignalRxContext_SSB_SW1_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_DIH_SSB_SW2_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_DIH_SSB_SW2_WF = {
  &Com_SignalRxContext_DIH_SSB_SW2_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_RDoor_SW_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_RDoor_SW_WF = {
  &Com_SignalRxContext_RDoor_SW_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_LDoor_SW_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_LDoor_SW_WF = {
  &Com_SignalRxContext_LDoor_SW_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_DoorOpenSw;
static const Com_SignalRxConfigType Com_SignalRxConfig_DoorOpenSw = {
  &Com_SignalRxContext_DoorOpenSw,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_EEC1_EngTorqueMode;
static const Com_SignalRxConfigType Com_SignalRxConfig_EEC1_EngTorqueMode = {
  &Com_SignalRxContext_EEC1_EngTorqueMode,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_EEC1_ActlEngPrcntTrqueHighResolution;
static const Com_SignalRxConfigType Com_SignalRxConfig_EEC1_ActlEngPrcntTrqueHighResolution = {
  &Com_SignalRxContext_EEC1_ActlEngPrcntTrqueHighResolution,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_EEC1_DriversDemandPercentTorque;
static const Com_SignalRxConfigType Com_SignalRxConfig_EEC1_DriversDemandPercentTorque = {
  &Com_SignalRxContext_EEC1_DriversDemandPercentTorque,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_EEC1_ActualEngPercentTorque;
static const Com_SignalRxConfigType Com_SignalRxConfig_EEC1_ActualEngPercentTorque = {
  &Com_SignalRxContext_EEC1_ActualEngPercentTorque,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_EEC1_EngSpeed;
static const Com_SignalRxConfigType Com_SignalRxConfig_EEC1_EngSpeed = {
  &Com_SignalRxContext_EEC1_EngSpeed,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_EEC1_ECU_SA;
static const Com_SignalRxConfigType Com_SignalRxConfig_EEC1_ECU_SA = {
  &Com_SignalRxContext_EEC1_ECU_SA,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_EEC1_EngDemandPercentTorque;
static const Com_SignalRxConfigType Com_SignalRxConfig_EEC1_EngDemandPercentTorque = {
  &Com_SignalRxContext_EEC1_EngDemandPercentTorque,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_ParkingBrakeSwitch;
static const Com_SignalRxConfigType Com_SignalRxConfig_ParkingBrakeSwitch = {
  &Com_SignalRxContext_ParkingBrakeSwitch,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_VBUS_VCU4_N_VehicleSpeed;
static const Com_SignalRxConfigType Com_SignalRxConfig_VBUS_VCU4_N_VehicleSpeed = {
  &Com_SignalRxContext_VBUS_VCU4_N_VehicleSpeed,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_VBUS_VCU4_St_Gears;
static const Com_SignalRxConfigType Com_SignalRxConfig_VBUS_VCU4_St_Gears = {
  &Com_SignalRxContext_VBUS_VCU4_St_Gears,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_VBUS_VCU4_St_Ready;
static const Com_SignalRxConfigType Com_SignalRxConfig_VBUS_VCU4_St_Ready = {
  &Com_SignalRxContext_VBUS_VCU4_St_Ready,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_VBUS_VCU4_St_BrakeSta;
static const Com_SignalRxConfigType Com_SignalRxConfig_VBUS_VCU4_St_BrakeSta = {
  &Com_SignalRxContext_VBUS_VCU4_St_BrakeSta,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_TachographVehicleSpeed;
static const Com_SignalRxConfigType Com_SignalRxConfig_TachographVehicleSpeed = {
  &Com_SignalRxContext_TachographVehicleSpeed,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_TireLocation;
static const Com_SignalRxConfigType Com_SignalRxConfig_TireLocation = {
  &Com_SignalRxContext_TireLocation,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_TirePressure;
static const Com_SignalRxConfigType Com_SignalRxConfig_TirePressure = {
  &Com_SignalRxContext_TirePressure,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_TireTemperature;
static const Com_SignalRxConfigType Com_SignalRxConfig_TireTemperature = {
  &Com_SignalRxContext_TireTemperature,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_WheelSensorStatus;
static const Com_SignalRxConfigType Com_SignalRxConfig_WheelSensorStatus = {
  &Com_SignalRxContext_WheelSensorStatus,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_TireStatus;
static const Com_SignalRxConfigType Com_SignalRxConfig_TireStatus = {
  &Com_SignalRxContext_TireStatus,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Tire_Sensor_Electrical_Fault;
static const Com_SignalRxConfigType Com_SignalRxConfig_Tire_Sensor_Electrical_Fault = {
  &Com_SignalRxContext_Tire_Sensor_Electrical_Fault,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Tire_Air_Leakage_Rate;
static const Com_SignalRxConfigType Com_SignalRxConfig_Tire_Air_Leakage_Rate = {
  &Com_SignalRxContext_Tire_Air_Leakage_Rate,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_TirePressureThresholdDetection;
static const Com_SignalRxConfigType Com_SignalRxConfig_TirePressureThresholdDetection = {
  &Com_SignalRxContext_TirePressureThresholdDetection,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_DM1_TPMS_ProtectLampStatus;
static const Com_SignalRxConfigType Com_SignalRxConfig_DM1_TPMS_ProtectLampStatus = {
  &Com_SignalRxContext_DM1_TPMS_ProtectLampStatus,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_DM1_TPMS_AmberWarningLampStatus;
static const Com_SignalRxConfigType Com_SignalRxConfig_DM1_TPMS_AmberWarningLampStatus = {
  &Com_SignalRxContext_DM1_TPMS_AmberWarningLampStatus,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_DM1_TPMS_RedStopLampState;
static const Com_SignalRxConfigType Com_SignalRxConfig_DM1_TPMS_RedStopLampState = {
  &Com_SignalRxContext_DM1_TPMS_RedStopLampState,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_LeastByteofSPN;
static const Com_SignalRxConfigType Com_SignalRxConfig_LeastByteofSPN = {
  &Com_SignalRxContext_LeastByteofSPN,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_SecondByteofSPN;
static const Com_SignalRxConfigType Com_SignalRxConfig_SecondByteofSPN = {
  &Com_SignalRxContext_SecondByteofSPN,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_FMI;
static const Com_SignalRxConfigType Com_SignalRxConfig_FMI = {
  &Com_SignalRxContext_FMI,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext__3MostBitofSPN;
static const Com_SignalRxConfigType Com_SignalRxConfig__3MostBitofSPN = {
  &Com_SignalRxContext__3MostBitofSPN,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_OC;
static const Com_SignalRxConfigType Com_SignalRxConfig_OC = {
  &Com_SignalRxContext_OC,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_CM;
static const Com_SignalRxConfigType Com_SignalRxConfig_CM = {
  &Com_SignalRxContext_CM,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_EBC1_ASREngCtrlActive;
static const Com_SignalRxConfigType Com_SignalRxConfig_EBC1_ASREngCtrlActive = {
  &Com_SignalRxContext_EBC1_ASREngCtrlActive,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_EBC1_ASRBrakeCtrlActive;
static const Com_SignalRxConfigType Com_SignalRxConfig_EBC1_ASRBrakeCtrlActive = {
  &Com_SignalRxContext_EBC1_ASRBrakeCtrlActive,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_EBC1_AntiLockBrakingActive;
static const Com_SignalRxConfigType Com_SignalRxConfig_EBC1_AntiLockBrakingActive = {
  &Com_SignalRxContext_EBC1_AntiLockBrakingActive,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_EBC1_EBSBrakeSwitch;
static const Com_SignalRxConfigType Com_SignalRxConfig_EBC1_EBSBrakeSwitch = {
  &Com_SignalRxContext_EBC1_EBSBrakeSwitch,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_EBC1_Brake_Pedal_Position;
static const Com_SignalRxConfigType Com_SignalRxConfig_EBC1_Brake_Pedal_Position = {
  &Com_SignalRxContext_EBC1_Brake_Pedal_Position,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_EBC1_ABS_OffRoad_switch;
static const Com_SignalRxConfigType Com_SignalRxConfig_EBC1_ABS_OffRoad_switch = {
  &Com_SignalRxContext_EBC1_ABS_OffRoad_switch,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_EBC1_ASR_OffRoad_switch;
static const Com_SignalRxConfigType Com_SignalRxConfig_EBC1_ASR_OffRoad_switch = {
  &Com_SignalRxContext_EBC1_ASR_OffRoad_switch,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_EBC1_ASR_HillHolder_switch;
static const Com_SignalRxConfigType Com_SignalRxConfig_EBC1_ASR_HillHolder_switch = {
  &Com_SignalRxContext_EBC1_ASR_HillHolder_switch,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_EBC1_Traction_ControlOverride_switch;
static const Com_SignalRxConfigType Com_SignalRxConfig_EBC1_Traction_ControlOverride_switch = {
  &Com_SignalRxContext_EBC1_Traction_ControlOverride_switch,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_ABS_Fully_Operational;
static const Com_SignalRxConfigType Com_SignalRxConfig_ABS_Fully_Operational = {
  &Com_SignalRxContext_ABS_Fully_Operational,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_EBC1_EBSRedWarningSignal;
static const Com_SignalRxConfigType Com_SignalRxConfig_EBC1_EBSRedWarningSignal = {
  &Com_SignalRxContext_EBC1_EBSRedWarningSignal,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_EBC1_ABS_EBSAmberWarningSignal;
static const Com_SignalRxConfigType Com_SignalRxConfig_EBC1_ABS_EBSAmberWarningSignal = {
  &Com_SignalRxContext_EBC1_ABS_EBSAmberWarningSignal,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_EBC1_ATC_ASRInformationSignal;
static const Com_SignalRxConfigType Com_SignalRxConfig_EBC1_ATC_ASRInformationSignal = {
  &Com_SignalRxContext_EBC1_ATC_ASRInformationSignal,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Foundation_Brake_Use;
static const Com_SignalRxConfigType Com_SignalRxConfig_Foundation_Brake_Use = {
  &Com_SignalRxContext_Foundation_Brake_Use,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_XBR_System_State;
static const Com_SignalRxConfigType Com_SignalRxConfig_XBR_System_State = {
  &Com_SignalRxContext_XBR_System_State,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_XBR_Active_Control_Mode;
static const Com_SignalRxConfigType Com_SignalRxConfig_XBR_Active_Control_Mode = {
  &Com_SignalRxContext_XBR_Active_Control_Mode,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_XBR_Acceleration_Limit;
static const Com_SignalRxConfigType Com_SignalRxConfig_XBR_Acceleration_Limit = {
  &Com_SignalRxContext_XBR_Acceleration_Limit,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Parking_Brake_Actuator_Fully_Activated;
static const Com_SignalRxConfigType Com_SignalRxConfig_Parking_Brake_Actuator_Fully_Activated = {
  &Com_SignalRxContext_Parking_Brake_Actuator_Fully_Activated,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Emergency_Braking_Active;
static const Com_SignalRxConfigType Com_SignalRxConfig_Emergency_Braking_Active = {
  &Com_SignalRxContext_Emergency_Braking_Active,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_DLCC1_EngAmberWarningLampCmd;
static const Com_SignalRxConfigType Com_SignalRxConfig_DLCC1_EngAmberWarningLampCmd = {
  &Com_SignalRxContext_DLCC1_EngAmberWarningLampCmd,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_DLCC1_EngRedStopLampCmd;
static const Com_SignalRxConfigType Com_SignalRxConfig_DLCC1_EngRedStopLampCmd = {
  &Com_SignalRxContext_DLCC1_EngRedStopLampCmd,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_DLCC1_OBDMalfunctionLampCmd;
static const Com_SignalRxConfigType Com_SignalRxConfig_DLCC1_OBDMalfunctionLampCmd = {
  &Com_SignalRxContext_DLCC1_OBDMalfunctionLampCmd,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_DLCC1_EngBrakeActiveLampCmd;
static const Com_SignalRxConfigType Com_SignalRxConfig_DLCC1_EngBrakeActiveLampCmd = {
  &Com_SignalRxContext_DLCC1_EngBrakeActiveLampCmd,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_DLCC1_EngOilPressLowLampCmd;
static const Com_SignalRxConfigType Com_SignalRxConfig_DLCC1_EngOilPressLowLampCmd = {
  &Com_SignalRxContext_DLCC1_EngOilPressLowLampCmd,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_DLCC1_EngCoolantTempHighLampCmd;
static const Com_SignalRxConfigType Com_SignalRxConfig_DLCC1_EngCoolantTempHighLampCmd = {
  &Com_SignalRxContext_DLCC1_EngCoolantTempHighLampCmd,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_DLCC1_EngCoolantLevelLowLampCmd;
static const Com_SignalRxConfigType Com_SignalRxConfig_DLCC1_EngCoolantLevelLowLampCmd = {
  &Com_SignalRxContext_DLCC1_EngCoolantLevelLowLampCmd,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_CCVS1_TwoSpeedAxleSwitch;
static const Com_SignalRxConfigType Com_SignalRxConfig_CCVS1_TwoSpeedAxleSwitch = {
  &Com_SignalRxContext_CCVS1_TwoSpeedAxleSwitch,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_CCVS1_ParkingBrakeSwitch;
static const Com_SignalRxConfigType Com_SignalRxConfig_CCVS1_ParkingBrakeSwitch = {
  &Com_SignalRxContext_CCVS1_ParkingBrakeSwitch,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_CCVS1_WheelBasedVehicleSpeed;
static const Com_SignalRxConfigType Com_SignalRxConfig_CCVS1_WheelBasedVehicleSpeed = {
  &Com_SignalRxContext_CCVS1_WheelBasedVehicleSpeed,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_CCVS1_CruiseCtrlActive;
static const Com_SignalRxConfigType Com_SignalRxConfig_CCVS1_CruiseCtrlActive = {
  &Com_SignalRxContext_CCVS1_CruiseCtrlActive,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_CCVS1_CruiseCtrlEnableSwitch;
static const Com_SignalRxConfigType Com_SignalRxConfig_CCVS1_CruiseCtrlEnableSwitch = {
  &Com_SignalRxContext_CCVS1_CruiseCtrlEnableSwitch,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_CCVS1_BrakeSwitch;
static const Com_SignalRxConfigType Com_SignalRxConfig_CCVS1_BrakeSwitch = {
  &Com_SignalRxContext_CCVS1_BrakeSwitch,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_CCVS1_ClutchSwitch;
static const Com_SignalRxConfigType Com_SignalRxConfig_CCVS1_ClutchSwitch = {
  &Com_SignalRxContext_CCVS1_ClutchSwitch,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_CCVS1_CruiseCtrlSetSwitch;
static const Com_SignalRxConfigType Com_SignalRxConfig_CCVS1_CruiseCtrlSetSwitch = {
  &Com_SignalRxContext_CCVS1_CruiseCtrlSetSwitch,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_CCVS1_CruiseCtrlCoastSwitch;
static const Com_SignalRxConfigType Com_SignalRxConfig_CCVS1_CruiseCtrlCoastSwitch = {
  &Com_SignalRxContext_CCVS1_CruiseCtrlCoastSwitch,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_CCVS1_CruiseCtrlResumeSwitch;
static const Com_SignalRxConfigType Com_SignalRxConfig_CCVS1_CruiseCtrlResumeSwitch = {
  &Com_SignalRxContext_CCVS1_CruiseCtrlResumeSwitch,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_CCVS1_CruiseCtrlAccelerateSwitch;
static const Com_SignalRxConfigType Com_SignalRxConfig_CCVS1_CruiseCtrlAccelerateSwitch = {
  &Com_SignalRxContext_CCVS1_CruiseCtrlAccelerateSwitch,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_CCVS1_CruiseCtrlSetSpeed;
static const Com_SignalRxConfigType Com_SignalRxConfig_CCVS1_CruiseCtrlSetSpeed = {
  &Com_SignalRxContext_CCVS1_CruiseCtrlSetSpeed,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_CCVS1_PTOGovernorState;
static const Com_SignalRxConfigType Com_SignalRxConfig_CCVS1_PTOGovernorState = {
  &Com_SignalRxContext_CCVS1_PTOGovernorState,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_CCVS1_CruiseCtrlStates;
static const Com_SignalRxConfigType Com_SignalRxConfig_CCVS1_CruiseCtrlStates = {
  &Com_SignalRxContext_CCVS1_CruiseCtrlStates,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_VDC1_VDCInformationSignal;
static const Com_SignalRxConfigType Com_SignalRxConfig_VDC1_VDCInformationSignal = {
  &Com_SignalRxContext_VDC1_VDCInformationSignal,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_VDC1_VDCFullyOperational;
static const Com_SignalRxConfigType Com_SignalRxConfig_VDC1_VDCFullyOperational = {
  &Com_SignalRxContext_VDC1_VDCFullyOperational,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_VDC1_VDC_brake_light_request;
static const Com_SignalRxConfigType Com_SignalRxConfig_VDC1_VDC_brake_light_request = {
  &Com_SignalRxContext_VDC1_VDC_brake_light_request,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_VDC1_ROPEngCtrlActive;
static const Com_SignalRxConfigType Com_SignalRxConfig_VDC1_ROPEngCtrlActive = {
  &Com_SignalRxContext_VDC1_ROPEngCtrlActive,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_VDC1_ROPBrakeCtrlActive;
static const Com_SignalRxConfigType Com_SignalRxConfig_VDC1_ROPBrakeCtrlActive = {
  &Com_SignalRxContext_VDC1_ROPBrakeCtrlActive,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_VDC1_YCEngCtrlActive;
static const Com_SignalRxConfigType Com_SignalRxConfig_VDC1_YCEngCtrlActive = {
  &Com_SignalRxContext_VDC1_YCEngCtrlActive,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_VDC1_YCBrakeCtrlActive;
static const Com_SignalRxConfigType Com_SignalRxConfig_VDC1_YCBrakeCtrlActive = {
  &Com_SignalRxContext_VDC1_YCBrakeCtrlActive,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_ERC1_RX_ERC1_ActualRetarderPercentTorque;
static const Com_SignalRxConfigType Com_SignalRxConfig_ERC1_RX_ERC1_ActualRetarderPercentTorque = {
  &Com_SignalRxContext_ERC1_RX_ERC1_ActualRetarderPercentTorque,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_ERC3_RX_ERC1_ActualRetarderPercentTorque;
static const Com_SignalRxConfigType Com_SignalRxConfig_ERC3_RX_ERC1_ActualRetarderPercentTorque = {
  &Com_SignalRxContext_ERC3_RX_ERC1_ActualRetarderPercentTorque,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_TransReverseDirectionSw;
static const Com_SignalRxConfigType Com_SignalRxConfig_TransReverseDirectionSw = {
  &Com_SignalRxContext_TransReverseDirectionSw,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_TransNeutralSwitch;
static const Com_SignalRxConfigType Com_SignalRxConfig_TransNeutralSwitch = {
  &Com_SignalRxContext_TransNeutralSwitch,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_ECC_Work_Switch;
static const Com_SignalRxConfigType Com_SignalRxConfig_ECC_Work_Switch = {
  &Com_SignalRxContext_ECC_Work_Switch,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_ECC_COMP_ReqSwitch;
static const Com_SignalRxConfigType Com_SignalRxConfig_ECC_COMP_ReqSwitch = {
  &Com_SignalRxContext_ECC_COMP_ReqSwitch,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_ECC_WPTC_ReqSwitch;
static const Com_SignalRxConfigType Com_SignalRxConfig_ECC_WPTC_ReqSwitch = {
  &Com_SignalRxContext_ECC_WPTC_ReqSwitch,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_REC_Switch;
static const Com_SignalRxConfigType Com_SignalRxConfig_REC_Switch = {
  &Com_SignalRxContext_REC_Switch,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Fan_Gear_Switch;
static const Com_SignalRxConfigType Com_SignalRxConfig_Fan_Gear_Switch = {
  &Com_SignalRxContext_Fan_Gear_Switch,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_HVAC_MODE_Switch;
static const Com_SignalRxConfigType Com_SignalRxConfig_HVAC_MODE_Switch = {
  &Com_SignalRxContext_HVAC_MODE_Switch,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_HVAC_SET_Temp_Switch;
static const Com_SignalRxConfigType Com_SignalRxConfig_HVAC_SET_Temp_Switch = {
  &Com_SignalRxContext_HVAC_SET_Temp_Switch,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_One_click_defrosting;
static const Com_SignalRxConfigType Com_SignalRxConfig_One_click_defrosting = {
  &Com_SignalRxContext_One_click_defrosting,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_ECC_Work_Status;
static const Com_SignalRxConfigType Com_SignalRxConfig_ECC_Work_Status = {
  &Com_SignalRxContext_ECC_Work_Status,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_ECC_COMP_ReqStatus;
static const Com_SignalRxConfigType Com_SignalRxConfig_ECC_COMP_ReqStatus = {
  &Com_SignalRxContext_ECC_COMP_ReqStatus,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_REC_Status;
static const Com_SignalRxConfigType Com_SignalRxConfig_REC_Status = {
  &Com_SignalRxContext_REC_Status,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Fan_Gear;
static const Com_SignalRxConfigType Com_SignalRxConfig_Fan_Gear = {
  &Com_SignalRxContext_Fan_Gear,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_HVAC_MODE_Status;
static const Com_SignalRxConfigType Com_SignalRxConfig_HVAC_MODE_Status = {
  &Com_SignalRxContext_HVAC_MODE_Status,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_HVAC_SET_Temp;
static const Com_SignalRxConfigType Com_SignalRxConfig_HVAC_SET_Temp = {
  &Com_SignalRxContext_HVAC_SET_Temp,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_EVAP_Temp;
static const Com_SignalRxConfigType Com_SignalRxConfig_EVAP_Temp = {
  &Com_SignalRxContext_EVAP_Temp,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_MID_PRESS_Status;
static const Com_SignalRxConfigType Com_SignalRxConfig_MID_PRESS_Status = {
  &Com_SignalRxContext_MID_PRESS_Status,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_H_L_PRESS_Sta;
static const Com_SignalRxConfigType Com_SignalRxConfig_H_L_PRESS_Sta = {
  &Com_SignalRxContext_H_L_PRESS_Sta,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_One_click_defrosting_Status;
static const Com_SignalRxConfigType Com_SignalRxConfig_One_click_defrosting_Status = {
  &Com_SignalRxContext_One_click_defrosting_Status,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_N_Shift_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_N_Shift_WF = {
  &Com_SignalRxContext_N_Shift_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_AI_Clutch_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_AI_Clutch_WF = {
  &Com_SignalRxContext_AI_Clutch_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_StartupSts_Fb_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_StartupSts_Fb_WF = {
  &Com_SignalRxContext_StartupSts_Fb_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_High_low_Voltage_SW_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_High_low_Voltage_SW_WF = {
  &Com_SignalRxContext_High_low_Voltage_SW_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_AC_DOH_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_AC_DOH_WF = {
  &Com_SignalRxContext_AC_DOH_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_D1_Diag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_D1_Diag_WF = {
  &Com_SignalRxContext_D1_Diag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_D2_Diag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_D2_Diag_WF = {
  &Com_SignalRxContext_D2_Diag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_D3_Diag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_D3_Diag_WF = {
  &Com_SignalRxContext_D3_Diag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_D4_Diag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_D4_Diag_WF = {
  &Com_SignalRxContext_D4_Diag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_D5_Diag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_D5_Diag_WF = {
  &Com_SignalRxContext_D5_Diag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_D6_Diag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_D6_Diag_WF = {
  &Com_SignalRxContext_D6_Diag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_D7_Diag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_D7_Diag_WF = {
  &Com_SignalRxContext_D7_Diag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_D8_Diag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_D8_Diag_WF = {
  &Com_SignalRxContext_D8_Diag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_D9_Diag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_D9_Diag_WF = {
  &Com_SignalRxContext_D9_Diag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_D10_Diag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_D10_Diag_WF = {
  &Com_SignalRxContext_D10_Diag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_D11_Diag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_D11_Diag_WF = {
  &Com_SignalRxContext_D11_Diag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_D12_Diag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_D12_Diag_WF = {
  &Com_SignalRxContext_D12_Diag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_D13_Diag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_D13_Diag_WF = {
  &Com_SignalRxContext_D13_Diag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_D14_Diag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_D14_Diag_WF = {
  &Com_SignalRxContext_D14_Diag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_D15_Diag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_D15_Diag_WF = {
  &Com_SignalRxContext_D15_Diag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_D16_Diag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_D16_Diag_WF = {
  &Com_SignalRxContext_D16_Diag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_D17_Diag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_D17_Diag_WF = {
  &Com_SignalRxContext_D17_Diag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_D18_Diag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_D18_Diag_WF = {
  &Com_SignalRxContext_D18_Diag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_D19_Diag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_D19_Diag_WF = {
  &Com_SignalRxContext_D19_Diag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_D20_Diag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_D20_Diag_WF = {
  &Com_SignalRxContext_D20_Diag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_D21_Diag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_D21_Diag_WF = {
  &Com_SignalRxContext_D21_Diag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_D22_Diag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_D22_Diag_WF = {
  &Com_SignalRxContext_D22_Diag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_D23_Diag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_D23_Diag_WF = {
  &Com_SignalRxContext_D23_Diag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_D24_Diag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_D24_Diag_WF = {
  &Com_SignalRxContext_D24_Diag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_D25_Diag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_D25_Diag_WF = {
  &Com_SignalRxContext_D25_Diag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_D26_Diag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_D26_Diag_WF = {
  &Com_SignalRxContext_D26_Diag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_D27_Diag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_D27_Diag_WF = {
  &Com_SignalRxContext_D27_Diag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_D28_Diag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_D28_Diag_WF = {
  &Com_SignalRxContext_D28_Diag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_D29_Diag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_D29_Diag_WF = {
  &Com_SignalRxContext_D29_Diag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_D30_Diag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_D30_Diag_WF = {
  &Com_SignalRxContext_D30_Diag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_D31_Diag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_D31_Diag_WF = {
  &Com_SignalRxContext_D31_Diag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_D32_Diag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_D32_Diag_WF = {
  &Com_SignalRxContext_D32_Diag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_D33_Diag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_D33_Diag_WF = {
  &Com_SignalRxContext_D33_Diag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_D34_Diag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_D34_Diag_WF = {
  &Com_SignalRxContext_D34_Diag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_D35_Diag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_D35_Diag_WF = {
  &Com_SignalRxContext_D35_Diag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_D36_Diag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_D36_Diag_WF = {
  &Com_SignalRxContext_D36_Diag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_D38_Diag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_D38_Diag_WF = {
  &Com_SignalRxContext_D38_Diag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_D39_Diag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_D39_Diag_WF = {
  &Com_SignalRxContext_D39_Diag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_D40_Diag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_D40_Diag_WF = {
  &Com_SignalRxContext_D40_Diag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_D41_Diag_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_D41_Diag_WF = {
  &Com_SignalRxContext_D41_Diag_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Wiper_H_RlyCoil_Ctrl_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_Wiper_H_RlyCoil_Ctrl_WF = {
  &Com_SignalRxContext_Wiper_H_RlyCoil_Ctrl_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Blower_RlyCoil_Ctrl_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_Blower_RlyCoil_Ctrl_WF = {
  &Com_SignalRxContext_Blower_RlyCoil_Ctrl_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_IG_Fb_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_IG_Fb_WF = {
  &Com_SignalRxContext_IG_Fb_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_IG_RlyCoil_Ctrl_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_IG_RlyCoil_Ctrl_WF = {
  &Com_SignalRxContext_IG_RlyCoil_Ctrl_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_ACC_Fb_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_ACC_Fb_WF = {
  &Com_SignalRxContext_ACC_Fb_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_ACC_RlyCoil_Ctrl_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_ACC_RlyCoil_Ctrl_WF = {
  &Com_SignalRxContext_ACC_RlyCoil_Ctrl_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Horn_RlyCoil_Ctrl_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_Horn_RlyCoil_Ctrl_WF = {
  &Com_SignalRxContext_Horn_RlyCoil_Ctrl_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Wiper_Power_RlyCoil_Ctrl_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_Wiper_Power_RlyCoil_Ctrl_WF = {
  &Com_SignalRxContext_Wiper_Power_RlyCoil_Ctrl_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Startup_SIG_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_Startup_SIG_WF = {
  &Com_SignalRxContext_Startup_SIG_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_F_LOGO_Lamp_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_F_LOGO_Lamp_WF = {
  &Com_SignalRxContext_F_LOGO_Lamp_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Washer_Motor_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_Washer_Motor_WF = {
  &Com_SignalRxContext_Washer_Motor_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_HSD1_Reserve_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_HSD1_Reserve_WF = {
  &Com_SignalRxContext_HSD1_Reserve_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Battery_Saver_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_Battery_Saver_WF = {
  &Com_SignalRxContext_Battery_Saver_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Dome_Lamp_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_Dome_Lamp_WF = {
  &Com_SignalRxContext_Dome_Lamp_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_LSD1_Reserve_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_LSD1_Reserve_WF = {
  &Com_SignalRxContext_LSD1_Reserve_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_LSD2_Reserve_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_LSD2_Reserve_WF = {
  &Com_SignalRxContext_LSD2_Reserve_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Window_Indication_Lamp_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_Window_Indication_Lamp_WF = {
  &Com_SignalRxContext_Window_Indication_Lamp_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_IDM_COMP_ReqStatus;
static const Com_SignalRxConfigType Com_SignalRxConfig_IDM_COMP_ReqStatus = {
  &Com_SignalRxContext_IDM_COMP_ReqStatus,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_F_FOG_RlyCoil_Ctrl_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_F_FOG_RlyCoil_Ctrl_WF = {
  &Com_SignalRxContext_F_FOG_RlyCoil_Ctrl_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_POS_RlyCoil_Ctrl_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_POS_RlyCoil_Ctrl_WF = {
  &Com_SignalRxContext_POS_RlyCoil_Ctrl_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_LB_RlyCoil_Ctrl_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_LB_RlyCoil_Ctrl_WF = {
  &Com_SignalRxContext_LB_RlyCoil_Ctrl_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_HB_RlyCoil_Ctrl_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_HB_RlyCoil_Ctrl_WF = {
  &Com_SignalRxContext_HB_RlyCoil_Ctrl_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_FL_Wind_Up_RlyCoil_Ctrl_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_FL_Wind_Up_RlyCoil_Ctrl_WF = {
  &Com_SignalRxContext_FL_Wind_Up_RlyCoil_Ctrl_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_FL_Wind_Down_RlyCoil_Ctrl_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_FL_Wind_Down_RlyCoil_Ctrl_WF = {
  &Com_SignalRxContext_FL_Wind_Down_RlyCoil_Ctrl_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_FR_Wind_Up_RlyCoil_Ctrl_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_FR_Wind_Up_RlyCoil_Ctrl_WF = {
  &Com_SignalRxContext_FR_Wind_Up_RlyCoil_Ctrl_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_FR_Wind_Down_RlyCoil_Ctrl_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_FR_Wind_Down_RlyCoil_Ctrl_WF = {
  &Com_SignalRxContext_FR_Wind_Down_RlyCoil_Ctrl_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_RL_Wind_Up_RlyCoil_Ctrl_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_RL_Wind_Up_RlyCoil_Ctrl_WF = {
  &Com_SignalRxContext_RL_Wind_Up_RlyCoil_Ctrl_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_RL_Wind_Down_RlyCoil_Ctrl_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_RL_Wind_Down_RlyCoil_Ctrl_WF = {
  &Com_SignalRxContext_RL_Wind_Down_RlyCoil_Ctrl_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_RR_Wind_Up_RlyCoil_Ctrl_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_RR_Wind_Up_RlyCoil_Ctrl_WF = {
  &Com_SignalRxContext_RR_Wind_Up_RlyCoil_Ctrl_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_RR_Wind_Down_RlyCoil_Ctrl_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_RR_Wind_Down_RlyCoil_Ctrl_WF = {
  &Com_SignalRxContext_RR_Wind_Down_RlyCoil_Ctrl_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Center_Unlock_RlyCoil_Ctrl_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_Center_Unlock_RlyCoil_Ctrl_WF = {
  &Com_SignalRxContext_Center_Unlock_RlyCoil_Ctrl_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Center_Lock_RlyCoil_Ctrl_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_Center_Lock_RlyCoil_Ctrl_WF = {
  &Com_SignalRxContext_Center_Lock_RlyCoil_Ctrl_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Mirror_Heat_RlyCoil_Ctrl_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_Mirror_Heat_RlyCoil_Ctrl_WF = {
  &Com_SignalRxContext_Mirror_Heat_RlyCoil_Ctrl_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Horn_SW_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_Horn_SW_WF = {
  &Com_SignalRxContext_Horn_SW_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_FL_Wind_Gnd_Ctrl_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_FL_Wind_Gnd_Ctrl_WF = {
  &Com_SignalRxContext_FL_Wind_Gnd_Ctrl_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_FR_Wind_Gnd_Ctrl_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_FR_Wind_Gnd_Ctrl_WF = {
  &Com_SignalRxContext_FR_Wind_Gnd_Ctrl_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_RL_Wind_Gnd_Ctrl_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_RL_Wind_Gnd_Ctrl_WF = {
  &Com_SignalRxContext_RL_Wind_Gnd_Ctrl_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_RR_Wind_Gnd_Ctrl_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_RR_Wind_Gnd_Ctrl_WF = {
  &Com_SignalRxContext_RR_Wind_Gnd_Ctrl_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_LSD_SSB_LED3_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_LSD_SSB_LED3_WF = {
  &Com_SignalRxContext_LSD_SSB_LED3_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_LSD_SSB_LED2_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_LSD_SSB_LED2_WF = {
  &Com_SignalRxContext_LSD_SSB_LED2_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_LSD_SSB_LED1_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_LSD_SSB_LED1_WF = {
  &Com_SignalRxContext_LSD_SSB_LED1_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Condensing_Fan_Low_Ctrl_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_Condensing_Fan_Low_Ctrl_WF = {
  &Com_SignalRxContext_Condensing_Fan_Low_Ctrl_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Condensing_Fan_High_Ctrl_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_Condensing_Fan_High_Ctrl_WF = {
  &Com_SignalRxContext_Condensing_Fan_High_Ctrl_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Int_Ext_Motor_Inc_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_Int_Ext_Motor_Inc_WF = {
  &Com_SignalRxContext_Int_Ext_Motor_Inc_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Int_Ext_Motor_Dec_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_Int_Ext_Motor_Dec_WF = {
  &Com_SignalRxContext_Int_Ext_Motor_Dec_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Cold_Heat_Motor_Inc_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_Cold_Heat_Motor_Inc_WF = {
  &Com_SignalRxContext_Cold_Heat_Motor_Inc_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Cold_Heat_Motor_Dec_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_Cold_Heat_Motor_Dec_WF = {
  &Com_SignalRxContext_Cold_Heat_Motor_Dec_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Mode_Motor_Inc_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_Mode_Motor_Inc_WF = {
  &Com_SignalRxContext_Mode_Motor_Inc_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Mode_MotoR_Dec_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_Mode_MotoR_Dec_WF = {
  &Com_SignalRxContext_Mode_MotoR_Dec_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_IDM_LPOWER;
static const Com_SignalRxConfigType Com_SignalRxConfig_IDM_LPOWER = {
  &Com_SignalRxContext_IDM_LPOWER,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_FL_Gnd_Ctrl_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_FL_Gnd_Ctrl_WF = {
  &Com_SignalRxContext_FL_Gnd_Ctrl_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_FR_Gnd_Ctrl_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_FR_Gnd_Ctrl_WF = {
  &Com_SignalRxContext_FR_Gnd_Ctrl_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_RL_Wind_Samp_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_RL_Wind_Samp_WF = {
  &Com_SignalRxContext_RL_Wind_Samp_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_RR_Wind_Samp_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_RR_Wind_Samp_WF = {
  &Com_SignalRxContext_RR_Wind_Samp_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Blower_Analog_Out_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_Blower_Analog_Out_WF = {
  &Com_SignalRxContext_Blower_Analog_Out_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Cold_Heat_Motor_Fb_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_Cold_Heat_Motor_Fb_WF = {
  &Com_SignalRxContext_Cold_Heat_Motor_Fb_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_Mode_MotoR_WF;
static const Com_SignalRxConfigType Com_SignalRxConfig_Mode_MotoR_WF = {
  &Com_SignalRxContext_Mode_MotoR_WF,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_ControlByte;
static const Com_SignalRxConfigType Com_SignalRxConfig_ControlByte = {
  &Com_SignalRxContext_ControlByte,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_TotalNumberOfBbytes;
static const Com_SignalRxConfigType Com_SignalRxConfig_TotalNumberOfBbytes = {
  &Com_SignalRxContext_TotalNumberOfBbytes,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_TotalNumberOfPackets;
static const Com_SignalRxConfigType Com_SignalRxConfig_TotalNumberOfPackets = {
  &Com_SignalRxContext_TotalNumberOfPackets,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_ParameterGroupNumber;
static const Com_SignalRxConfigType Com_SignalRxConfig_ParameterGroupNumber = {
  &Com_SignalRxContext_ParameterGroupNumber,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_SequenceNumber;
static const Com_SignalRxConfigType Com_SignalRxConfig_SequenceNumber = {
  &Com_SignalRxContext_SequenceNumber,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  0, /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_NONE, /* RxDataTimeoutAction */
};

static const Com_SignalTxConfigType Com_SignalTxConfig_TX_COUNTER = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_TX_FLAG = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_TX_LEVEL = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_LedRunMode = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_LedOut = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_LedBlinkPhase = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_LedFaultTimeout = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static const Com_SignalTxConfigType Com_SignalTxConfig_LedFaultCmd = {
  #ifdef COM_USE_SIGNAL_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_SIGNAL_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #if !defined(COM_USE_SIGNAL_TX_ERROR_NOTIFICATION) && !defined(COM_USE_SIGNAL_TX_NOTIFICATION)
  0,
  #endif
};

static Com_SignalRxContextType Com_SignalRxContext_RX_COUNTER;
static const Com_SignalRxConfigType Com_SignalRxConfig_RX_COUNTER = {
  &Com_SignalRxContext_RX_COUNTER,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  &RX_COUNTER_TimeoutSubstitutionValue,
  0, /* FirstTimeout */
  COM_CONVERT_MS_TO_MAIN_CYCLES(1000u), /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_SUBSTITUTE, /* RxDataTimeoutAction */
};

static Com_SignalRxContextType Com_SignalRxContext_RX_TEMP;
static const Com_SignalRxConfigType Com_SignalRxConfig_RX_TEMP = {
  &Com_SignalRxContext_RX_TEMP,
  #ifdef COM_USE_SIGNAL_RX_INVALID_NOTIFICATION
  NULL, /* InvalidNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_SIGNAL_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  NULL, /* TimeoutSubstitutionValue */
  0, /* FirstTimeout */
  COM_CONVERT_MS_TO_MAIN_CYCLES(1000u), /* Timeout */
  COM_ACTION_NOTIFY, /* DataInvalidAction */
  COM_ACTION_REPLACE, /* RxDataTimeoutAction */
};

#endif /* COM_USE_SIGNAL_CONFIG */
static const Com_SignalConfigType Com_SignalConfigs[] = {
  {
#ifdef USE_SHELL
    "BCM_LowBeamSts",
#endif
    &Com_PduData_BCM_LCSF_TX[0], /* ptr */
    &BCM_LowBeamSts_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_BCM_LowBeamSts, /* txConfig */
#endif
    COM_SID_BCM_LowBeamSts, /* HandleId */
    COM_CAN1_BCM_LCSF_TX, /* PduId */
    4, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "BCM_HighBeamSts",
#endif
    &Com_PduData_BCM_LCSF_TX[0], /* ptr */
    &BCM_HighBeamSts_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_BCM_HighBeamSts, /* txConfig */
#endif
    COM_SID_BCM_HighBeamSts, /* HandleId */
    COM_CAN1_BCM_LCSF_TX, /* PduId */
    6, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "BCM_FrontFogSts",
#endif
    &Com_PduData_BCM_LCSF_TX[1], /* ptr */
    &BCM_FrontFogSts_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_BCM_FrontFogSts, /* txConfig */
#endif
    COM_SID_BCM_FrontFogSts, /* HandleId */
    COM_CAN1_BCM_LCSF_TX, /* PduId */
    0, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "BCM_TurnRLightSts",
#endif
    &Com_PduData_BCM_LCSF_TX[1], /* ptr */
    &BCM_TurnRLightSts_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_BCM_TurnRLightSts, /* txConfig */
#endif
    COM_SID_BCM_TurnRLightSts, /* HandleId */
    COM_CAN1_BCM_LCSF_TX, /* PduId */
    4, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "BCM_TurnLLightSts",
#endif
    &Com_PduData_BCM_LCSF_TX[1], /* ptr */
    &BCM_TurnLLightSts_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_BCM_TurnLLightSts, /* txConfig */
#endif
    COM_SID_BCM_TurnLLightSts, /* HandleId */
    COM_CAN1_BCM_LCSF_TX, /* PduId */
    6, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "BCM_DRLSts",
#endif
    &Com_PduData_BCM_LCSF_TX[3], /* ptr */
    &BCM_DRLSts_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_BCM_DRLSts, /* txConfig */
#endif
    COM_SID_BCM_DRLSts, /* HandleId */
    COM_CAN1_BCM_LCSF_TX, /* PduId */
    0, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "BCM_PositionLightSts",
#endif
    &Com_PduData_BCM_LCSF_TX[3], /* ptr */
    &BCM_PositionLightSts_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_BCM_PositionLightSts, /* txConfig */
#endif
    COM_SID_BCM_PositionLightSts, /* HandleId */
    COM_CAN1_BCM_LCSF_TX, /* PduId */
    6, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "BCM_RearFogSts",
#endif
    &Com_PduData_BCM_LCSF_TX[4], /* ptr */
    &BCM_RearFogSts_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_BCM_RearFogSts, /* txConfig */
#endif
    COM_SID_BCM_RearFogSts, /* HandleId */
    COM_CAN1_BCM_LCSF_TX, /* PduId */
    0, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "BackUpLightSt",
#endif
    &Com_PduData_BCM_LCSF_TX[5], /* ptr */
    &BackUpLightSt_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_BackUpLightSt, /* txConfig */
#endif
    COM_SID_BackUpLightSt, /* HandleId */
    COM_CAN1_BCM_LCSF_TX, /* PduId */
    4, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "BrakelightST",
#endif
    &Com_PduData_BCM_LCSF_TX[5], /* ptr */
    &BrakelightST_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_BrakelightST, /* txConfig */
#endif
    COM_SID_BrakelightST, /* HandleId */
    COM_CAN1_BCM_LCSF_TX, /* PduId */
    6, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "InteriorLampSt",
#endif
    &Com_PduData_BCM_LCSF_TX[6], /* ptr */
    &InteriorLampSt_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_InteriorLampSt, /* txConfig */
#endif
    COM_SID_InteriorLampSt, /* HandleId */
    COM_CAN1_BCM_LCSF_TX, /* PduId */
    0, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "BCM_PassWindowLcokSw",
#endif
    &Com_PduData_BCM_Ctrl_TX[0], /* ptr */
    &BCM_PassWindowLcokSw_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_BCM_PassWindowLcokSw, /* txConfig */
#endif
    COM_SID_BCM_PassWindowLcokSw, /* HandleId */
    COM_CAN1_BCM_CTRL_TX, /* PduId */
    0, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "CentralLockSw",
#endif
    &Com_PduData_BCM_Ctrl_TX[0], /* ptr */
    &CentralLockSw_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_CentralLockSw, /* txConfig */
#endif
    COM_SID_CentralLockSw, /* HandleId */
    COM_CAN1_BCM_CTRL_TX, /* PduId */
    2, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "MRightFrontWinSw",
#endif
    &Com_PduData_BCM_Ctrl_TX[0], /* ptr */
    &MRightFrontWinSw_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_MRightFrontWinSw, /* txConfig */
#endif
    COM_SID_MRightFrontWinSw, /* HandleId */
    COM_CAN1_BCM_CTRL_TX, /* PduId */
    4, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "MLeftFrontWinSw",
#endif
    &Com_PduData_BCM_Ctrl_TX[0], /* ptr */
    &MLeftFrontWinSw_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_MLeftFrontWinSw, /* txConfig */
#endif
    COM_SID_MLeftFrontWinSw, /* HandleId */
    COM_CAN1_BCM_CTRL_TX, /* PduId */
    6, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "RightFrontWinSw",
#endif
    &Com_PduData_BCM_Ctrl_TX[1], /* ptr */
    &RightFrontWinSw_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_RightFrontWinSw, /* txConfig */
#endif
    COM_SID_RightFrontWinSw, /* HandleId */
    COM_CAN1_BCM_CTRL_TX, /* PduId */
    2, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "MRightRearWinSw",
#endif
    &Com_PduData_BCM_Ctrl_TX[1], /* ptr */
    &MRightRearWinSw_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_MRightRearWinSw, /* txConfig */
#endif
    COM_SID_MRightRearWinSw, /* HandleId */
    COM_CAN1_BCM_CTRL_TX, /* PduId */
    4, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "MLeftRearWinSw",
#endif
    &Com_PduData_BCM_Ctrl_TX[1], /* ptr */
    &MLeftRearWinSw_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_MLeftRearWinSw, /* txConfig */
#endif
    COM_SID_MLeftRearWinSw, /* HandleId */
    COM_CAN1_BCM_CTRL_TX, /* PduId */
    6, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "RightRearWinSw",
#endif
    &Com_PduData_BCM_Ctrl_TX[2], /* ptr */
    &RightRearWinSw_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_RightRearWinSw, /* txConfig */
#endif
    COM_SID_RightRearWinSw, /* HandleId */
    COM_CAN1_BCM_CTRL_TX, /* PduId */
    0, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "LeftRearWinSw",
#endif
    &Com_PduData_BCM_Ctrl_TX[2], /* ptr */
    &LeftRearWinSw_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_LeftRearWinSw, /* txConfig */
#endif
    COM_SID_LeftRearWinSw, /* HandleId */
    COM_CAN1_BCM_CTRL_TX, /* PduId */
    2, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "BCM_Ctrl_TX_MechKeySt",
#endif
    &Com_PduData_BCM_Ctrl_TX[2], /* ptr */
    &BCM_Ctrl_TX_MechKeySt_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_BCM_Ctrl_TX_MechKeySt, /* txConfig */
#endif
    COM_SID_BCM_Ctrl_TX_MechKeySt, /* HandleId */
    COM_CAN1_BCM_CTRL_TX, /* PduId */
    4, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "LeftFrontWinSt",
#endif
    &Com_PduData_BCM_Ctrl_TX[2], /* ptr */
    &LeftFrontWinSt_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_LeftFrontWinSt, /* txConfig */
#endif
    COM_SID_LeftFrontWinSt, /* HandleId */
    COM_CAN1_BCM_CTRL_TX, /* PduId */
    6, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "RightFrontWinSt",
#endif
    &Com_PduData_BCM_Ctrl_TX[3], /* ptr */
    &RightFrontWinSt_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_RightFrontWinSt, /* txConfig */
#endif
    COM_SID_RightFrontWinSt, /* HandleId */
    COM_CAN1_BCM_CTRL_TX, /* PduId */
    0, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "LeftRearWinSt",
#endif
    &Com_PduData_BCM_Ctrl_TX[3], /* ptr */
    &LeftRearWinSt_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_LeftRearWinSt, /* txConfig */
#endif
    COM_SID_LeftRearWinSt, /* HandleId */
    COM_CAN1_BCM_CTRL_TX, /* PduId */
    2, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "RightRearWinSt",
#endif
    &Com_PduData_BCM_Ctrl_TX[3], /* ptr */
    &RightRearWinSt_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_RightRearWinSt, /* txConfig */
#endif
    COM_SID_RightRearWinSt, /* HandleId */
    COM_CAN1_BCM_CTRL_TX, /* PduId */
    4, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "DoorLockMotorState",
#endif
    &Com_PduData_BCM_Ctrl_TX[3], /* ptr */
    &DoorLockMotorState_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_DoorLockMotorState, /* txConfig */
#endif
    COM_SID_DoorLockMotorState, /* HandleId */
    COM_CAN1_BCM_CTRL_TX, /* PduId */
    6, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "RemoteDoorState",
#endif
    &Com_PduData_BCM_Ctrl_TX[4], /* ptr */
    &RemoteDoorState_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_RemoteDoorState, /* txConfig */
#endif
    COM_SID_RemoteDoorState, /* HandleId */
    COM_CAN1_BCM_CTRL_TX, /* PduId */
    0, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "LeftFrontWinErrorSt",
#endif
    &Com_PduData_BCM_Ctrl_TX[6], /* ptr */
    &LeftFrontWinErrorSt_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_LeftFrontWinErrorSt, /* txConfig */
#endif
    COM_SID_LeftFrontWinErrorSt, /* HandleId */
    COM_CAN1_BCM_CTRL_TX, /* PduId */
    0, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "RightFrontWinErrorSt",
#endif
    &Com_PduData_BCM_Ctrl_TX[6], /* ptr */
    &RightFrontWinErrorSt_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_RightFrontWinErrorSt, /* txConfig */
#endif
    COM_SID_RightFrontWinErrorSt, /* HandleId */
    COM_CAN1_BCM_CTRL_TX, /* PduId */
    2, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "LeftRearWinErrorSt",
#endif
    &Com_PduData_BCM_Ctrl_TX[6], /* ptr */
    &LeftRearWinErrorSt_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_LeftRearWinErrorSt, /* txConfig */
#endif
    COM_SID_LeftRearWinErrorSt, /* HandleId */
    COM_CAN1_BCM_CTRL_TX, /* PduId */
    4, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "RightRearWinErrorSt",
#endif
    &Com_PduData_BCM_Ctrl_TX[6], /* ptr */
    &RightRearWinErrorSt_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_RightRearWinErrorSt, /* txConfig */
#endif
    COM_SID_RightRearWinErrorSt, /* HandleId */
    COM_CAN1_BCM_CTRL_TX, /* PduId */
    6, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "HazardSw",
#endif
    &Com_PduData_BCM_OEL_TX[1], /* ptr */
    &HazardSw_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_HazardSw, /* txConfig */
#endif
    COM_SID_HazardSw, /* HandleId */
    COM_CAN1_BCM_OEL_TX, /* PduId */
    4, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "HazardSt",
#endif
    &Com_PduData_BCM_OEL_TX[5], /* ptr */
    &HazardSt_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_HazardSt, /* txConfig */
#endif
    COM_SID_HazardSt, /* HandleId */
    COM_CAN1_BCM_OEL_TX, /* PduId */
    0, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "WiperSt",
#endif
    &Com_PduData_BCM_OWW_TX[1], /* ptr */
    &WiperSt_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_WiperSt, /* txConfig */
#endif
    COM_SID_WiperSt, /* HandleId */
    COM_CAN1_BCM_OWW_TX, /* PduId */
    0, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "SKC_u8PEPSICUIndCnt_WF",
#endif
    &Com_PduData_BCM_DoorCtrl_TX[0], /* ptr */
    &SKC_u8PEPSICUIndCnt_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_SKC_u8PEPSICUIndCnt_WF, /* txConfig */
#endif
    COM_SID_SKC_u8PEPSICUIndCnt_WF, /* HandleId */
    COM_CAN1_BCM_DOOR_CTRL_TX, /* PduId */
    0, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "PRM_u8PEPSICUIndCnt_WF",
#endif
    &Com_PduData_BCM_DoorCtrl_TX[0], /* ptr */
    &PRM_u8PEPSICUIndCnt_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_PRM_u8PEPSICUIndCnt_WF, /* txConfig */
#endif
    COM_SID_PRM_u8PEPSICUIndCnt_WF, /* HandleId */
    COM_CAN1_BCM_DOOR_CTRL_TX, /* PduId */
    2, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "ATP_u8DrvLockRotor_WF",
#endif
    &Com_PduData_BCM_DoorCtrl_TX[0], /* ptr */
    &ATP_u8DrvLockRotor_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_ATP_u8DrvLockRotor_WF, /* txConfig */
#endif
    COM_SID_ATP_u8DrvLockRotor_WF, /* HandleId */
    COM_CAN1_BCM_DOOR_CTRL_TX, /* PduId */
    4, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "ESCL_u8AuthReqCnt_WF",
#endif
    &Com_PduData_BCM_DoorCtrl_TX[0], /* ptr */
    &ESCL_u8AuthReqCnt_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_ESCL_u8AuthReqCnt_WF, /* txConfig */
#endif
    COM_SID_ESCL_u8AuthReqCnt_WF, /* HandleId */
    COM_CAN1_BCM_DOOR_CTRL_TX, /* PduId */
    6, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "BCM_OpenStatusofDdoor",
#endif
    &Com_PduData_BCM_DoorCtrl_TX[1], /* ptr */
    &BCM_OpenStatusofDdoor_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_BCM_OpenStatusofDdoor, /* txConfig */
#endif
    COM_SID_BCM_OpenStatusofDdoor, /* HandleId */
    COM_CAN1_BCM_DOOR_CTRL_TX, /* PduId */
    0, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "BCM_OpenStatusofPdoor",
#endif
    &Com_PduData_BCM_DoorCtrl_TX[1], /* ptr */
    &BCM_OpenStatusofPdoor_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_BCM_OpenStatusofPdoor, /* txConfig */
#endif
    COM_SID_BCM_OpenStatusofPdoor, /* HandleId */
    COM_CAN1_BCM_DOOR_CTRL_TX, /* PduId */
    2, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "BCM_OpenStatusofLeftReardoor",
#endif
    &Com_PduData_BCM_DoorCtrl_TX[1], /* ptr */
    &BCM_OpenStatusofLeftReardoor_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_BCM_OpenStatusofLeftReardoor, /* txConfig */
#endif
    COM_SID_BCM_OpenStatusofLeftReardoor, /* HandleId */
    COM_CAN1_BCM_DOOR_CTRL_TX, /* PduId */
    4, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "BCM_OpenStatusofRightReardoor",
#endif
    &Com_PduData_BCM_DoorCtrl_TX[1], /* ptr */
    &BCM_OpenStatusofRightReardoor_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_BCM_OpenStatusofRightReardoor, /* txConfig */
#endif
    COM_SID_BCM_OpenStatusofRightReardoor, /* HandleId */
    COM_CAN1_BCM_DOOR_CTRL_TX, /* PduId */
    6, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "BASE_u8AuthResultCnt_WF",
#endif
    &Com_PduData_BCM_DoorCtrl_TX[2], /* ptr */
    &BASE_u8AuthResultCnt_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_BASE_u8AuthResultCnt_WF, /* txConfig */
#endif
    COM_SID_BASE_u8AuthResultCnt_WF, /* HandleId */
    COM_CAN1_BCM_DOOR_CTRL_TX, /* PduId */
    0, /* BitPosition */
    3, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "BSW_TPMS_FrameCnt_WF",
#endif
    &Com_PduData_BCM_DoorCtrl_TX[2], /* ptr */
    &BSW_TPMS_FrameCnt_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_BSW_TPMS_FrameCnt_WF, /* txConfig */
#endif
    COM_SID_BSW_TPMS_FrameCnt_WF, /* HandleId */
    COM_CAN1_BCM_DOOR_CTRL_TX, /* PduId */
    3, /* BitPosition */
    4, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "PAM_u8SleepFlag_WF",
#endif
    &Com_PduData_BCM_DoorCtrl_TX[2], /* ptr */
    &PAM_u8SleepFlag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_PAM_u8SleepFlag_WF, /* txConfig */
#endif
    COM_SID_PAM_u8SleepFlag_WF, /* HandleId */
    COM_CAN1_BCM_DOOR_CTRL_TX, /* PduId */
    7, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "ATP_u8PasLockRotor_WF",
#endif
    &Com_PduData_BCM_DoorCtrl_TX[3], /* ptr */
    &ATP_u8PasLockRotor_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_ATP_u8PasLockRotor_WF, /* txConfig */
#endif
    COM_SID_ATP_u8PasLockRotor_WF, /* HandleId */
    COM_CAN1_BCM_DOOR_CTRL_TX, /* PduId */
    0, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "FEE_APPWriteIdleFlag_WF",
#endif
    &Com_PduData_BCM_DoorCtrl_TX[3], /* ptr */
    &FEE_APPWriteIdleFlag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_FEE_APPWriteIdleFlag_WF, /* txConfig */
#endif
    COM_SID_FEE_APPWriteIdleFlag_WF, /* HandleId */
    COM_CAN1_BCM_DOOR_CTRL_TX, /* PduId */
    4, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "FEE_BOOTWriteIdleFlag_WF",
#endif
    &Com_PduData_BCM_DoorCtrl_TX[3], /* ptr */
    &FEE_BOOTWriteIdleFlag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_FEE_BOOTWriteIdleFlag_WF, /* txConfig */
#endif
    COM_SID_FEE_BOOTWriteIdleFlag_WF, /* HandleId */
    COM_CAN1_BCM_DOOR_CTRL_TX, /* PduId */
    6, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "WIN_u8DrvWinCmdCAN_WF",
#endif
    &Com_PduData_BCM_DoorCtrl_TX[4], /* ptr */
    &WIN_u8DrvWinCmdCAN_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_WIN_u8DrvWinCmdCAN_WF, /* txConfig */
#endif
    COM_SID_WIN_u8DrvWinCmdCAN_WF, /* HandleId */
    COM_CAN1_BCM_DOOR_CTRL_TX, /* PduId */
    0, /* BitPosition */
    4, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "WIN_u8PasWinCmdCAN_WF",
#endif
    &Com_PduData_BCM_DoorCtrl_TX[4], /* ptr */
    &WIN_u8PasWinCmdCAN_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_WIN_u8PasWinCmdCAN_WF, /* txConfig */
#endif
    COM_SID_WIN_u8PasWinCmdCAN_WF, /* HandleId */
    COM_CAN1_BCM_DOOR_CTRL_TX, /* PduId */
    4, /* BitPosition */
    4, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "TUL_u8HonkingStyle_WF",
#endif
    &Com_PduData_BCM_DoorCtrl_TX[5], /* ptr */
    &TUL_u8HonkingStyle_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_TUL_u8HonkingStyle_WF, /* txConfig */
#endif
    COM_SID_TUL_u8HonkingStyle_WF, /* HandleId */
    COM_CAN1_BCM_DOOR_CTRL_TX, /* PduId */
    0, /* BitPosition */
    4, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "DLC_u8LockSource_WF",
#endif
    &Com_PduData_BCM_DoorCtrl_TX[5], /* ptr */
    &DLC_u8LockSource_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_DLC_u8LockSource_WF, /* txConfig */
#endif
    COM_SID_DLC_u8LockSource_WF, /* HandleId */
    COM_CAN1_BCM_DOOR_CTRL_TX, /* PduId */
    4, /* BitPosition */
    4, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "HornRelaySt",
#endif
    &Com_PduData_BCM_DoorCtrl_TX[6], /* ptr */
    &HornRelaySt_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_HornRelaySt, /* txConfig */
#endif
    COM_SID_HornRelaySt, /* HandleId */
    COM_CAN1_BCM_DOOR_CTRL_TX, /* PduId */
    0, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "BrakeLightWarning",
#endif
    &Com_PduData_BCM_DoorCtrl_TX[6], /* ptr */
    &BrakeLightWarning_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_BrakeLightWarning, /* txConfig */
#endif
    COM_SID_BrakeLightWarning, /* HandleId */
    COM_CAN1_BCM_DOOR_CTRL_TX, /* PduId */
    2, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "LF_SendCounter_WF",
#endif
    &Com_PduData_BCM_DoorCtrl_TX[7], /* ptr */
    &LF_SendCounter_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_LF_SendCounter_WF, /* txConfig */
#endif
    COM_SID_LF_SendCounter_WF, /* HandleId */
    COM_CAN1_BCM_DOOR_CTRL_TX, /* PduId */
    0, /* BitPosition */
    4, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "LF_Commond_WF",
#endif
    &Com_PduData_BCM_DoorCtrl_TX[7], /* ptr */
    &LF_Commond_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_LF_Commond_WF, /* txConfig */
#endif
    COM_SID_LF_Commond_WF, /* HandleId */
    COM_CAN1_BCM_DOOR_CTRL_TX, /* PduId */
    4, /* BitPosition */
    4, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "DM1_MalfunctionIndicatorLampStatus",
#endif
    &Com_PduData_BCM_DM1_TX[0], /* ptr */
    &DM1_MalfunctionIndicatorLampStatus_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_DM1_MalfunctionIndicatorLampStatus, /* txConfig */
#endif
    COM_SID_DM1_MalfunctionIndicatorLampStatus, /* HandleId */
    COM_CAN1_BCM_DM1_TX, /* PduId */
    2, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "DM1_RedStopLampState",
#endif
    &Com_PduData_BCM_DM1_TX[0], /* ptr */
    &DM1_RedStopLampState_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_DM1_RedStopLampState, /* txConfig */
#endif
    COM_SID_DM1_RedStopLampState, /* HandleId */
    COM_CAN1_BCM_DM1_TX, /* PduId */
    4, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "BCM_LeastByteofSPN",
#endif
    &Com_PduData_BCM_DM1_TX[2], /* ptr */
    &BCM_LeastByteofSPN_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_BCM_LeastByteofSPN, /* txConfig */
#endif
    COM_SID_BCM_LeastByteofSPN, /* HandleId */
    COM_CAN1_BCM_DM1_TX, /* PduId */
    0, /* BitPosition */
    8, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "BCM_SecondByteofSPN",
#endif
    &Com_PduData_BCM_DM1_TX[3], /* ptr */
    &BCM_SecondByteofSPN_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_BCM_SecondByteofSPN, /* txConfig */
#endif
    COM_SID_BCM_SecondByteofSPN, /* HandleId */
    COM_CAN1_BCM_DM1_TX, /* PduId */
    0, /* BitPosition */
    8, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "BCM_FMI",
#endif
    &Com_PduData_BCM_DM1_TX[4], /* ptr */
    &BCM_FMI_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_BCM_FMI, /* txConfig */
#endif
    COM_SID_BCM_FMI, /* HandleId */
    COM_CAN1_BCM_DM1_TX, /* PduId */
    0, /* BitPosition */
    5, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "BCM_3MostBitofSPN",
#endif
    &Com_PduData_BCM_DM1_TX[4], /* ptr */
    &BCM_3MostBitofSPN_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_BCM_3MostBitofSPN, /* txConfig */
#endif
    COM_SID_BCM_3MostBitofSPN, /* HandleId */
    COM_CAN1_BCM_DM1_TX, /* PduId */
    5, /* BitPosition */
    3, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "BCM_OC",
#endif
    &Com_PduData_BCM_DM1_TX[5], /* ptr */
    &BCM_OC_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_BCM_OC, /* txConfig */
#endif
    COM_SID_BCM_OC, /* HandleId */
    COM_CAN1_BCM_DM1_TX, /* PduId */
    0, /* BitPosition */
    7, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "BCM_CM",
#endif
    &Com_PduData_BCM_DM1_TX[5], /* ptr */
    &BCM_CM_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_BCM_CM, /* txConfig */
#endif
    COM_SID_BCM_CM, /* HandleId */
    COM_CAN1_BCM_DM1_TX, /* PduId */
    7, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "SRS_Crash_Type",
#endif
    &Com_PduData_Crash_Notification_RX[0], /* ptr */
    &SRS_Crash_Type_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_SRS_Crash_Type, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_SRS_Crash_Type, /* HandleId */
    COM_CAN1_CRASH_NOTIFICATION_RX, /* PduId */
    0, /* BitPosition */
    5, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "AMB_BarometricPress",
#endif
    &Com_PduData_AMB_Ambient_Conditions_RX[0], /* ptr */
    &AMB_BarometricPress_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_AMB_BarometricPress, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_AMB_BarometricPress, /* HandleId */
    COM_CAN1_AMB_AMBIENT_CONDITIONS_RX, /* PduId */
    0, /* BitPosition */
    8, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "LFE1_AmbientAirTemp",
#endif
    &Com_PduData_AMB_Ambient_Conditions_RX[3], /* ptr */
    &LFE1_AmbientAirTemp_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_LFE1_AmbientAirTemp, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_LFE1_AmbientAirTemp, /* HandleId */
    COM_CAN1_AMB_AMBIENT_CONDITIONS_RX, /* PduId */
    0, /* BitPosition */
    16, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT16, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "LFE1_EngAirIntakeTemp",
#endif
    &Com_PduData_AMB_Ambient_Conditions_RX[5], /* ptr */
    &LFE1_EngAirIntakeTemp_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_LFE1_EngAirIntakeTemp, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_LFE1_EngAirIntakeTemp, /* HandleId */
    COM_CAN1_AMB_AMBIENT_CONDITIONS_RX, /* PduId */
    0, /* BitPosition */
    8, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "PEPsKeyInState",
#endif
    &Com_PduData_PEPS1_RX[0], /* ptr */
    &PEPsKeyInState_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_PEPsKeyInState, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_PEPsKeyInState, /* HandleId */
    COM_CAN1_PEPS1_RX, /* PduId */
    2, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "PEPS_PkeLockCmd",
#endif
    &Com_PduData_PEPS1_RX[1], /* ptr */
    &PEPS_PkeLockCmd_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_PEPS_PkeLockCmd, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_PEPS_PkeLockCmd, /* HandleId */
    COM_CAN1_PEPS1_RX, /* PduId */
    0, /* BitPosition */
    4, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "PEPS_PowerMode",
#endif
    &Com_PduData_PEPS1_RX[2], /* ptr */
    &PEPS_PowerMode_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_PEPS_PowerMode, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_PEPS_PowerMode, /* HandleId */
    COM_CAN1_PEPS1_RX, /* PduId */
    5, /* BitPosition */
    3, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "PEPS_ESCLInhabitSt",
#endif
    &Com_PduData_PEPS1_RX[3], /* ptr */
    &PEPS_ESCLInhabitSt_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_PEPS_ESCLInhabitSt, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_PEPS_ESCLInhabitSt, /* HandleId */
    COM_CAN1_PEPS1_RX, /* PduId */
    0, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "PEPS_EmergencyST",
#endif
    &Com_PduData_PEPS1_RX[3], /* ptr */
    &PEPS_EmergencyST_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_PEPS_EmergencyST, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_PEPS_EmergencyST, /* HandleId */
    COM_CAN1_PEPS1_RX, /* PduId */
    4, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "PEPS_KeyAuthenticationSt_PEPS",
#endif
    &Com_PduData_PEPS1_RX[3], /* ptr */
    &PEPS_KeyAuthenticationSt_PEPS_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_PEPS_KeyAuthenticationSt_PEPS, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_PEPS_KeyAuthenticationSt_PEPS, /* HandleId */
    COM_CAN1_PEPS1_RX, /* PduId */
    6, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "ESCL_failure",
#endif
    &Com_PduData_PEPS1_RX[4], /* ptr */
    &ESCL_failure_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_ESCL_failure, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_ESCL_failure, /* HandleId */
    COM_CAN1_PEPS1_RX, /* PduId */
    0, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "PEPS_failure",
#endif
    &Com_PduData_PEPS1_RX[4], /* ptr */
    &PEPS_failure_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_PEPS_failure, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_PEPS_failure, /* HandleId */
    COM_CAN1_PEPS1_RX, /* PduId */
    1, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Key_Not_Found",
#endif
    &Com_PduData_PEPS1_RX[4], /* ptr */
    &Key_Not_Found_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Key_Not_Found, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Key_Not_Found, /* HandleId */
    COM_CAN1_PEPS1_RX, /* PduId */
    2, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Key_Battery_Low",
#endif
    &Com_PduData_PEPS1_RX[4], /* ptr */
    &Key_Battery_Low_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Key_Battery_Low, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Key_Battery_Low, /* HandleId */
    COM_CAN1_PEPS1_RX, /* PduId */
    3, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "PEPS_PEPSICUInd",
#endif
    &Com_PduData_PEPS1_RX[4], /* ptr */
    &PEPS_PEPSICUInd_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_PEPS_PEPSICUInd, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_PEPS_PEPSICUInd, /* HandleId */
    COM_CAN1_PEPS1_RX, /* PduId */
    4, /* BitPosition */
    4, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "PEPsKeyInFeedback",
#endif
    &Com_PduData_PEPS1_RX[5], /* ptr */
    &PEPsKeyInFeedback_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_PEPsKeyInFeedback, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_PEPsKeyInFeedback, /* HandleId */
    COM_CAN1_PEPS1_RX, /* PduId */
    0, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "ACC_FB",
#endif
    &Com_PduData_PEPS1_RX[5], /* ptr */
    &ACC_FB_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_ACC_FB, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_ACC_FB, /* HandleId */
    COM_CAN1_PEPS1_RX, /* PduId */
    2, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "IGN1_FB",
#endif
    &Com_PduData_PEPS1_RX[5], /* ptr */
    &IGN1_FB_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_IGN1_FB, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_IGN1_FB, /* HandleId */
    COM_CAN1_PEPS1_RX, /* PduId */
    3, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "PEPsKeyOutFeedback",
#endif
    &Com_PduData_PEPS1_RX[5], /* ptr */
    &PEPsKeyOutFeedback_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_PEPsKeyOutFeedback, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_PEPsKeyOutFeedback, /* HandleId */
    COM_CAN1_PEPS1_RX, /* PduId */
    6, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Alive_counter",
#endif
    &Com_PduData_PEPS1_RX[6], /* ptr */
    &Alive_counter_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Alive_counter, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Alive_counter, /* HandleId */
    COM_CAN1_PEPS1_RX, /* PduId */
    0, /* BitPosition */
    8, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "PEPS1_RX_CRC",
#endif
    &Com_PduData_PEPS1_RX[7], /* ptr */
    &PEPS1_RX_CRC_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_PEPS1_RX_CRC, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_PEPS1_RX_CRC, /* HandleId */
    COM_CAN1_PEPS1_RX, /* PduId */
    0, /* BitPosition */
    8, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Key1_Inside_St",
#endif
    &Com_PduData_PEPS2_RX[0], /* ptr */
    &Key1_Inside_St_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Key1_Inside_St, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Key1_Inside_St, /* HandleId */
    COM_CAN1_PEPS2_RX, /* PduId */
    0, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Key2_Inside_St",
#endif
    &Com_PduData_PEPS2_RX[0], /* ptr */
    &Key2_Inside_St_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Key2_Inside_St, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Key2_Inside_St, /* HandleId */
    COM_CAN1_PEPS2_RX, /* PduId */
    1, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Key3_Inside_St",
#endif
    &Com_PduData_PEPS2_RX[0], /* ptr */
    &Key3_Inside_St_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Key3_Inside_St, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Key3_Inside_St, /* HandleId */
    COM_CAN1_PEPS2_RX, /* PduId */
    2, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Key4_Inside_St",
#endif
    &Com_PduData_PEPS2_RX[0], /* ptr */
    &Key4_Inside_St_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Key4_Inside_St, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Key4_Inside_St, /* HandleId */
    COM_CAN1_PEPS2_RX, /* PduId */
    3, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Key1_Inhibit_St",
#endif
    &Com_PduData_PEPS2_RX[0], /* ptr */
    &Key1_Inhibit_St_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Key1_Inhibit_St, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Key1_Inhibit_St, /* HandleId */
    COM_CAN1_PEPS2_RX, /* PduId */
    4, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Key2_Inhibit_St",
#endif
    &Com_PduData_PEPS2_RX[0], /* ptr */
    &Key2_Inhibit_St_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Key2_Inhibit_St, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Key2_Inhibit_St, /* HandleId */
    COM_CAN1_PEPS2_RX, /* PduId */
    5, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Key3_Inhibit_St",
#endif
    &Com_PduData_PEPS2_RX[0], /* ptr */
    &Key3_Inhibit_St_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Key3_Inhibit_St, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Key3_Inhibit_St, /* HandleId */
    COM_CAN1_PEPS2_RX, /* PduId */
    6, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Key4_Inhibit_St",
#endif
    &Com_PduData_PEPS2_RX[0], /* ptr */
    &Key4_Inhibit_St_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Key4_Inhibit_St, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Key4_Inhibit_St, /* HandleId */
    COM_CAN1_PEPS2_RX, /* PduId */
    7, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "RKE_u8UnlockCounter_WF",
#endif
    &Com_PduData_PEPS2_RX[1], /* ptr */
    &RKE_u8UnlockCounter_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_RKE_u8UnlockCounter_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_RKE_u8UnlockCounter_WF, /* HandleId */
    COM_CAN1_PEPS2_RX, /* PduId */
    0, /* BitPosition */
    4, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "RKE_u8SearchCounter_WF",
#endif
    &Com_PduData_PEPS2_RX[1], /* ptr */
    &RKE_u8SearchCounter_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_RKE_u8SearchCounter_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_RKE_u8SearchCounter_WF, /* HandleId */
    COM_CAN1_PEPS2_RX, /* PduId */
    4, /* BitPosition */
    4, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "KE_u8LockCounter_WF",
#endif
    &Com_PduData_PEPS2_RX[2], /* ptr */
    &KE_u8LockCounter_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_KE_u8LockCounter_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_KE_u8LockCounter_WF, /* HandleId */
    COM_CAN1_PEPS2_RX, /* PduId */
    0, /* BitPosition */
    4, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "PKE_Count_WF",
#endif
    &Com_PduData_PEPS2_RX[2], /* ptr */
    &PKE_Count_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_PKE_Count_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_PKE_Count_WF, /* HandleId */
    COM_CAN1_PEPS2_RX, /* PduId */
    4, /* BitPosition */
    4, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "WKUPFALG_WF",
#endif
    &Com_PduData_PEPS2_RX[3], /* ptr */
    &WKUPFALG_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_WKUPFALG_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_WKUPFALG_WF, /* HandleId */
    COM_CAN1_PEPS2_RX, /* PduId */
    0, /* BitPosition */
    30, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT32, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "DLC_u8DrvPESts_WF",
#endif
    &Com_PduData_PEPS2_RX[6], /* ptr */
    &DLC_u8DrvPESts_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_DLC_u8DrvPESts_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_DLC_u8DrvPESts_WF, /* HandleId */
    COM_CAN1_PEPS2_RX, /* PduId */
    6, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "SSB_u8SWSts_WF",
#endif
    &Com_PduData_PEPS2_RX[6], /* ptr */
    &SSB_u8SWSts_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_SSB_u8SWSts_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_SSB_u8SWSts_WF, /* HandleId */
    COM_CAN1_PEPS2_RX, /* PduId */
    7, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "PKE_AuthResult_WF",
#endif
    &Com_PduData_PEPS2_RX[7], /* ptr */
    &PKE_AuthResult_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_PKE_AuthResult_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_PKE_AuthResult_WF, /* HandleId */
    COM_CAN1_PEPS2_RX, /* PduId */
    0, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "FEE_DTCWriteIdleFlag_WF",
#endif
    &Com_PduData_PEPS2_RX[7], /* ptr */
    &FEE_DTCWriteIdleFlag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_FEE_DTCWriteIdleFlag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_FEE_DTCWriteIdleFlag_WF, /* HandleId */
    COM_CAN1_PEPS2_RX, /* PduId */
    2, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "PMM_u8PwrStsLoad_WF",
#endif
    &Com_PduData_PEPS2_RX[7], /* ptr */
    &PMM_u8PwrStsLoad_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_PMM_u8PwrStsLoad_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_PMM_u8PwrStsLoad_WF, /* HandleId */
    COM_CAN1_PEPS2_RX, /* PduId */
    4, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "SWK_u8NmSleepSt_WF",
#endif
    &Com_PduData_PEPS2_RX[7], /* ptr */
    &SWK_u8NmSleepSt_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_SWK_u8NmSleepSt_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_SWK_u8NmSleepSt_WF, /* HandleId */
    COM_CAN1_PEPS2_RX, /* PduId */
    6, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "DLC_u8PasPESts_WF",
#endif
    &Com_PduData_PEPS2_RX[7], /* ptr */
    &DLC_u8PasPESts_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_DLC_u8PasPESts_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_DLC_u8PasPESts_WF, /* HandleId */
    COM_CAN1_PEPS2_RX, /* PduId */
    7, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "PEPS_SUB_ID",
#endif
    &Com_PduData_PEPS_ESCLM_RX[0], /* ptr */
    &PEPS_SUB_ID_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_PEPS_SUB_ID, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_PEPS_SUB_ID, /* HandleId */
    COM_CAN1_PEPS_ESCLM_RX, /* PduId */
    0, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "PEPS_AuthResp",
#endif
    &Com_PduData_PEPS_ESCLM_RX[1], /* ptr */
    &PEPS_AuthResp_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_PEPS_AuthResp, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_PEPS_AuthResp, /* HandleId */
    COM_CAN1_PEPS_ESCLM_RX, /* PduId */
    0, /* BitPosition */
    32, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT32, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "ManufacturerCode",
#endif
    &Com_PduData_ACL_RX[2], /* ptr */
    &ManufacturerCode_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_ManufacturerCode, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_ManufacturerCode, /* HandleId */
    COM_CAN1_ACL_RX, /* PduId */
    5, /* BitPosition */
    11, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT16, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "EngOperatingState",
#endif
    &Com_PduData_EOI_RX[0], /* ptr */
    &EngOperatingState_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_EngOperatingState, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_EngOperatingState, /* HandleId */
    COM_CAN1_EOI_RX, /* PduId */
    0, /* BitPosition */
    4, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "TransCurrentGear",
#endif
    &Com_PduData_ETC2_RX[3], /* ptr */
    &TransCurrentGear_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_TransCurrentGear, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_TransCurrentGear, /* HandleId */
    COM_CAN1_ETC2_RX, /* PduId */
    0, /* BitPosition */
    8, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "ESCL_St",
#endif
    &Com_PduData_ESCL1_RX[0], /* ptr */
    &ESCL_St_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_ESCL_St, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_ESCL_St, /* HandleId */
    COM_CAN1_ESCL1_RX, /* PduId */
    0, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "ESCL_WarnSafety",
#endif
    &Com_PduData_ESCL1_RX[0], /* ptr */
    &ESCL_WarnSafety_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_ESCL_WarnSafety, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_ESCL_WarnSafety, /* HandleId */
    COM_CAN1_ESCL1_RX, /* PduId */
    2, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "ESCL_PromptRotateSteerWheel",
#endif
    &Com_PduData_ESCL1_RX[0], /* ptr */
    &ESCL_PromptRotateSteerWheel_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_ESCL_PromptRotateSteerWheel, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_ESCL_PromptRotateSteerWheel, /* HandleId */
    COM_CAN1_ESCL1_RX, /* PduId */
    4, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "AliveCounter",
#endif
    &Com_PduData_ESCL1_RX[6], /* ptr */
    &AliveCounter_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_AliveCounter, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_AliveCounter, /* HandleId */
    COM_CAN1_ESCL1_RX, /* PduId */
    0, /* BitPosition */
    8, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "ESCL1_RX_CRC",
#endif
    &Com_PduData_ESCL1_RX[7], /* ptr */
    &ESCL1_RX_CRC_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_ESCL1_RX_CRC, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_ESCL1_RX_CRC, /* HandleId */
    COM_CAN1_ESCL1_RX, /* PduId */
    0, /* BitPosition */
    8, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "ESCL_SUB_ID",
#endif
    &Com_PduData_ESCLM_PEPS_RX[0], /* ptr */
    &ESCL_SUB_ID_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_ESCL_SUB_ID, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_ESCL_SUB_ID, /* HandleId */
    COM_CAN1_ESCLM_PEPS_RX, /* PduId */
    0, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "ESCL_AuthChallenge",
#endif
    &Com_PduData_ESCLM_PEPS_RX[1], /* ptr */
    &ESCL_AuthChallenge_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_ESCL_AuthChallenge, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_ESCL_AuthChallenge, /* HandleId */
    COM_CAN1_ESCLM_PEPS_RX, /* PduId */
    0, /* BitPosition */
    32, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT32, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "ESCL_AuthResult",
#endif
    &Com_PduData_ESCLM_PEPS_RX[5], /* ptr */
    &ESCL_AuthResult_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_ESCL_AuthResult, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_ESCL_AuthResult, /* HandleId */
    COM_CAN1_ESCLM_PEPS_RX, /* PduId */
    0, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Destination_Address",
#endif
    &Com_PduData_ESCL_NM_RX[0], /* ptr */
    &Destination_Address_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Destination_Address, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Destination_Address, /* HandleId */
    COM_CAN1_ESCL_NM_RX, /* PduId */
    0, /* BitPosition */
    8, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "SecAlarm",
#endif
    &Com_PduData_DW_State_RX[0], /* ptr */
    &SecAlarm_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_SecAlarm, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_SecAlarm, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    0, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "ESCL_u8SleepFlag_NM_WF",
#endif
    &Com_PduData_DW_State_RX[0], /* ptr */
    &ESCL_u8SleepFlag_NM_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_ESCL_u8SleepFlag_NM_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_ESCL_u8SleepFlag_NM_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    2, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "WIN_u8SleepFlag_NM_WF",
#endif
    &Com_PduData_DW_State_RX[0], /* ptr */
    &WIN_u8SleepFlag_NM_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_WIN_u8SleepFlag_NM_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_WIN_u8SleepFlag_NM_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    3, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "ACC_u8SleepFlag_NM_WF",
#endif
    &Com_PduData_DW_State_RX[0], /* ptr */
    &ACC_u8SleepFlag_NM_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_ACC_u8SleepFlag_NM_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_ACC_u8SleepFlag_NM_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    4, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "RMH_u8SleepFlag_NM_WF",
#endif
    &Com_PduData_DW_State_RX[0], /* ptr */
    &RMH_u8SleepFlag_NM_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_RMH_u8SleepFlag_NM_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_RMH_u8SleepFlag_NM_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    5, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "DLC_u8SleepFlag_NM_WF",
#endif
    &Com_PduData_DW_State_RX[0], /* ptr */
    &DLC_u8SleepFlag_NM_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_DLC_u8SleepFlag_NM_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_DLC_u8SleepFlag_NM_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    6, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "SAC_u8SleepFlag_NM_WF",
#endif
    &Com_PduData_DW_State_RX[0], /* ptr */
    &SAC_u8SleepFlag_NM_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_SAC_u8SleepFlag_NM_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_SAC_u8SleepFlag_NM_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    7, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "HORN_u8SleepFlag_NM_WF",
#endif
    &Com_PduData_DW_State_RX[1], /* ptr */
    &HORN_u8SleepFlag_NM_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_HORN_u8SleepFlag_NM_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_HORN_u8SleepFlag_NM_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    0, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "TUL_u8SleepFlag_NM_WF",
#endif
    &Com_PduData_DW_State_RX[1], /* ptr */
    &TUL_u8SleepFlag_NM_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_TUL_u8SleepFlag_NM_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_TUL_u8SleepFlag_NM_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    1, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "FMHL_u8SleepFlag_NM_WF",
#endif
    &Com_PduData_DW_State_RX[1], /* ptr */
    &FMHL_u8SleepFlag_NM_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_FMHL_u8SleepFlag_NM_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_FMHL_u8SleepFlag_NM_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    2, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "AHL_u8SleepFlag_NM_WF",
#endif
    &Com_PduData_DW_State_RX[1], /* ptr */
    &AHL_u8SleepFlag_NM_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_AHL_u8SleepFlag_NM_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_AHL_u8SleepFlag_NM_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    3, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "POL_u8SleepFlag_NM_WF",
#endif
    &Com_PduData_DW_State_RX[1], /* ptr */
    &POL_u8SleepFlag_NM_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_POL_u8SleepFlag_NM_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_POL_u8SleepFlag_NM_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    4, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "LBL_u8SleepFlag_NM_WF",
#endif
    &Com_PduData_DW_State_RX[1], /* ptr */
    &LBL_u8SleepFlag_NM_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_LBL_u8SleepFlag_NM_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_LBL_u8SleepFlag_NM_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    5, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "HBL_u8SleepFlag_NM_WF",
#endif
    &Com_PduData_DW_State_RX[1], /* ptr */
    &HBL_u8SleepFlag_NM_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_HBL_u8SleepFlag_NM_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_HBL_u8SleepFlag_NM_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    6, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "FFL_u8SleepFlag_NM_WF",
#endif
    &Com_PduData_DW_State_RX[1], /* ptr */
    &FFL_u8SleepFlag_NM_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_FFL_u8SleepFlag_NM_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_FFL_u8SleepFlag_NM_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    7, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "DW_State_RX_MechKeySt",
#endif
    &Com_PduData_DW_State_RX[2], /* ptr */
    &DW_State_RX_MechKeySt_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_DW_State_RX_MechKeySt, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_DW_State_RX_MechKeySt, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    4, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "RFL_u8SleepFlag_NM_WF",
#endif
    &Com_PduData_DW_State_RX[3], /* ptr */
    &RFL_u8SleepFlag_NM_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_RFL_u8SleepFlag_NM_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_RFL_u8SleepFlag_NM_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    0, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "DRL_u8SleepFlag_NM_WF",
#endif
    &Com_PduData_DW_State_RX[3], /* ptr */
    &DRL_u8SleepFlag_NM_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_DRL_u8SleepFlag_NM_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_DRL_u8SleepFlag_NM_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    1, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "BRL_u8SleepFlag_NM_WF",
#endif
    &Com_PduData_DW_State_RX[3], /* ptr */
    &BRL_u8SleepFlag_NM_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_BRL_u8SleepFlag_NM_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_BRL_u8SleepFlag_NM_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    2, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "SLED_u8SleepFlag_WF",
#endif
    &Com_PduData_DW_State_RX[3], /* ptr */
    &SLED_u8SleepFlag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_SLED_u8SleepFlag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_SLED_u8SleepFlag_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    3, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "DML_u8LampSleepFlag_NM_WF",
#endif
    &Com_PduData_DW_State_RX[3], /* ptr */
    &DML_u8LampSleepFlag_NM_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_DML_u8LampSleepFlag_NM_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_DML_u8LampSleepFlag_NM_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    4, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "LOL_u8SleepFlag_NM_WF",
#endif
    &Com_PduData_DW_State_RX[3], /* ptr */
    &LOL_u8SleepFlag_NM_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_LOL_u8SleepFlag_NM_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_LOL_u8SleepFlag_NM_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    5, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "WDIL_u8SleepFlag_NM_WF",
#endif
    &Com_PduData_DW_State_RX[3], /* ptr */
    &WDIL_u8SleepFlag_NM_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_WDIL_u8SleepFlag_NM_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_WDIL_u8SleepFlag_NM_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    6, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "SKC_u8SleepFlag_WF",
#endif
    &Com_PduData_DW_State_RX[3], /* ptr */
    &SKC_u8SleepFlag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_SKC_u8SleepFlag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_SKC_u8SleepFlag_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    7, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "DLC_u8UnlockSource_WF",
#endif
    &Com_PduData_DW_State_RX[4], /* ptr */
    &DLC_u8UnlockSource_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_DLC_u8UnlockSource_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_DLC_u8UnlockSource_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    0, /* BitPosition */
    4, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "ON_SW_WF",
#endif
    &Com_PduData_DW_State_RX[4], /* ptr */
    &ON_SW_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_ON_SW_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_ON_SW_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    4, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "ST_SW_WF",
#endif
    &Com_PduData_DW_State_RX[4], /* ptr */
    &ST_SW_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_ST_SW_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_ST_SW_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    5, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "ACC_SW_WF",
#endif
    &Com_PduData_DW_State_RX[4], /* ptr */
    &ACC_SW_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_ACC_SW_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_ACC_SW_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    6, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Lighting_Sensor_WF",
#endif
    &Com_PduData_DW_State_RX[4], /* ptr */
    &Lighting_Sensor_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Lighting_Sensor_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Lighting_Sensor_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    7, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "VehicleVoltage",
#endif
    &Com_PduData_DW_State_RX[5], /* ptr */
    &VehicleVoltage_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_VehicleVoltage, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_VehicleVoltage, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    6, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Mirror_Heat_SW_WF",
#endif
    &Com_PduData_DW_State_RX[6], /* ptr */
    &Mirror_Heat_SW_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Mirror_Heat_SW_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Mirror_Heat_SW_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    0, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "LOGO_SW_WF",
#endif
    &Com_PduData_DW_State_RX[6], /* ptr */
    &LOGO_SW_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_LOGO_SW_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_LOGO_SW_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    1, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Window_Inhibite_SW_WF",
#endif
    &Com_PduData_DW_State_RX[6], /* ptr */
    &Window_Inhibite_SW_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Window_Inhibite_SW_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Window_Inhibite_SW_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    2, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Key_IN_WF",
#endif
    &Com_PduData_DW_State_RX[6], /* ptr */
    &Key_IN_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Key_IN_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Key_IN_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    3, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Reserve1_SW_WF",
#endif
    &Com_PduData_DW_State_RX[6], /* ptr */
    &Reserve1_SW_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Reserve1_SW_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Reserve1_SW_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    4, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Reserve5_SW_WF",
#endif
    &Com_PduData_DW_State_RX[6], /* ptr */
    &Reserve5_SW_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Reserve5_SW_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Reserve5_SW_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    5, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "FL_TL_LED_Fb_WF",
#endif
    &Com_PduData_DW_State_RX[6], /* ptr */
    &FL_TL_LED_Fb_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_FL_TL_LED_Fb_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_FL_TL_LED_Fb_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    6, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "FR_TL_LED_Fb_WF",
#endif
    &Com_PduData_DW_State_RX[6], /* ptr */
    &FR_TL_LED_Fb_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_FR_TL_LED_Fb_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_FR_TL_LED_Fb_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    7, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Reserve2_SW_WF",
#endif
    &Com_PduData_DW_State_RX[7], /* ptr */
    &Reserve2_SW_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Reserve2_SW_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Reserve2_SW_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    0, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Reserve3_SW_WF",
#endif
    &Com_PduData_DW_State_RX[7], /* ptr */
    &Reserve3_SW_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Reserve3_SW_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Reserve3_SW_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    1, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Reserve4_SW_WF",
#endif
    &Com_PduData_DW_State_RX[7], /* ptr */
    &Reserve4_SW_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Reserve4_SW_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Reserve4_SW_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    2, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "DIL_Brake_WF",
#endif
    &Com_PduData_DW_State_RX[7], /* ptr */
    &DIL_Brake_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_DIL_Brake_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_DIL_Brake_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    3, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "SSB_SW1_WF",
#endif
    &Com_PduData_DW_State_RX[7], /* ptr */
    &SSB_SW1_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_SSB_SW1_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_SSB_SW1_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    4, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "DIH_SSB_SW2_WF",
#endif
    &Com_PduData_DW_State_RX[7], /* ptr */
    &DIH_SSB_SW2_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_DIH_SSB_SW2_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_DIH_SSB_SW2_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    5, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "RDoor_SW_WF",
#endif
    &Com_PduData_DW_State_RX[7], /* ptr */
    &RDoor_SW_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_RDoor_SW_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_RDoor_SW_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    6, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "LDoor_SW_WF",
#endif
    &Com_PduData_DW_State_RX[7], /* ptr */
    &LDoor_SW_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_LDoor_SW_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_LDoor_SW_WF, /* HandleId */
    COM_CAN1_DW_STATE_RX, /* PduId */
    7, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "DoorOpenSw",
#endif
    &Com_PduData_IC_MSG_RX[1], /* ptr */
    &DoorOpenSw_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_DoorOpenSw, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_DoorOpenSw, /* HandleId */
    COM_CAN1_IC_MSG_RX, /* PduId */
    4, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "EEC1_EngTorqueMode",
#endif
    &Com_PduData_EEC1_Electronic_Engine_Controller_1_RX[0], /* ptr */
    &EEC1_EngTorqueMode_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_EEC1_EngTorqueMode, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_EEC1_EngTorqueMode, /* HandleId */
    COM_CAN1_EEC1_ELECTRONIC_ENGINE_CONTROLLER_1_RX, /* PduId */
    0, /* BitPosition */
    4, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "EEC1_ActlEngPrcntTrqueHighResolution",
#endif
    &Com_PduData_EEC1_Electronic_Engine_Controller_1_RX[0], /* ptr */
    &EEC1_ActlEngPrcntTrqueHighResolution_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_EEC1_ActlEngPrcntTrqueHighResolution, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_EEC1_ActlEngPrcntTrqueHighResolution, /* HandleId */
    COM_CAN1_EEC1_ELECTRONIC_ENGINE_CONTROLLER_1_RX, /* PduId */
    4, /* BitPosition */
    4, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "EEC1_DriversDemandPercentTorque",
#endif
    &Com_PduData_EEC1_Electronic_Engine_Controller_1_RX[1], /* ptr */
    &EEC1_DriversDemandPercentTorque_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_EEC1_DriversDemandPercentTorque, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_EEC1_DriversDemandPercentTorque, /* HandleId */
    COM_CAN1_EEC1_ELECTRONIC_ENGINE_CONTROLLER_1_RX, /* PduId */
    0, /* BitPosition */
    8, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "EEC1_ActualEngPercentTorque",
#endif
    &Com_PduData_EEC1_Electronic_Engine_Controller_1_RX[2], /* ptr */
    &EEC1_ActualEngPercentTorque_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_EEC1_ActualEngPercentTorque, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_EEC1_ActualEngPercentTorque, /* HandleId */
    COM_CAN1_EEC1_ELECTRONIC_ENGINE_CONTROLLER_1_RX, /* PduId */
    0, /* BitPosition */
    8, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "EEC1_EngSpeed",
#endif
    &Com_PduData_EEC1_Electronic_Engine_Controller_1_RX[3], /* ptr */
    &EEC1_EngSpeed_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_EEC1_EngSpeed, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_EEC1_EngSpeed, /* HandleId */
    COM_CAN1_EEC1_ELECTRONIC_ENGINE_CONTROLLER_1_RX, /* PduId */
    0, /* BitPosition */
    16, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT16, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "EEC1_ECU_SA",
#endif
    &Com_PduData_EEC1_Electronic_Engine_Controller_1_RX[5], /* ptr */
    &EEC1_ECU_SA_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_EEC1_ECU_SA, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_EEC1_ECU_SA, /* HandleId */
    COM_CAN1_EEC1_ELECTRONIC_ENGINE_CONTROLLER_1_RX, /* PduId */
    0, /* BitPosition */
    8, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "EEC1_EngDemandPercentTorque",
#endif
    &Com_PduData_EEC1_Electronic_Engine_Controller_1_RX[7], /* ptr */
    &EEC1_EngDemandPercentTorque_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_EEC1_EngDemandPercentTorque, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_EEC1_EngDemandPercentTorque, /* HandleId */
    COM_CAN1_EEC1_ELECTRONIC_ENGINE_CONTROLLER_1_RX, /* PduId */
    0, /* BitPosition */
    8, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "ParkingBrakeSwitch",
#endif
    &Com_PduData_CCVS_RX[0], /* ptr */
    &ParkingBrakeSwitch_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_ParkingBrakeSwitch, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_ParkingBrakeSwitch, /* HandleId */
    COM_CAN1_CCVS_RX, /* PduId */
    2, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "VBUS_VCU4_N_VehicleSpeed",
#endif
    &Com_PduData_VCU_4_RX[0], /* ptr */
    &VBUS_VCU4_N_VehicleSpeed_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_VBUS_VCU4_N_VehicleSpeed, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_VBUS_VCU4_N_VehicleSpeed, /* HandleId */
    COM_CAN1_VCU_4_RX, /* PduId */
    0, /* BitPosition */
    16, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT16, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "VBUS_VCU4_St_Gears",
#endif
    &Com_PduData_VCU_4_RX[4], /* ptr */
    &VBUS_VCU4_St_Gears_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_VBUS_VCU4_St_Gears, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_VBUS_VCU4_St_Gears, /* HandleId */
    COM_CAN1_VCU_4_RX, /* PduId */
    0, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "VBUS_VCU4_St_Ready",
#endif
    &Com_PduData_VCU_4_RX[4], /* ptr */
    &VBUS_VCU4_St_Ready_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_VBUS_VCU4_St_Ready, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_VBUS_VCU4_St_Ready, /* HandleId */
    COM_CAN1_VCU_4_RX, /* PduId */
    2, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "VBUS_VCU4_St_BrakeSta",
#endif
    &Com_PduData_VCU_4_RX[7], /* ptr */
    &VBUS_VCU4_St_BrakeSta_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_VBUS_VCU4_St_BrakeSta, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_VBUS_VCU4_St_BrakeSta, /* HandleId */
    COM_CAN1_VCU_4_RX, /* PduId */
    2, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "TachographVehicleSpeed",
#endif
    &Com_PduData_TCO1_RX[6], /* ptr */
    &TachographVehicleSpeed_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_TachographVehicleSpeed, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_TachographVehicleSpeed, /* HandleId */
    COM_CAN1_TCO1_RX, /* PduId */
    0, /* BitPosition */
    16, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT16, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "TireLocation",
#endif
    &Com_PduData_TireCondition_RX[0], /* ptr */
    &TireLocation_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_TireLocation, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_TireLocation, /* HandleId */
    COM_CAN1_TIRE_CONDITION_RX, /* PduId */
    0, /* BitPosition */
    8, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "TirePressure",
#endif
    &Com_PduData_TireCondition_RX[1], /* ptr */
    &TirePressure_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_TirePressure, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_TirePressure, /* HandleId */
    COM_CAN1_TIRE_CONDITION_RX, /* PduId */
    0, /* BitPosition */
    8, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "TireTemperature",
#endif
    &Com_PduData_TireCondition_RX[2], /* ptr */
    &TireTemperature_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_TireTemperature, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_TireTemperature, /* HandleId */
    COM_CAN1_TIRE_CONDITION_RX, /* PduId */
    0, /* BitPosition */
    16, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT16, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "WheelSensorStatus",
#endif
    &Com_PduData_TireCondition_RX[4], /* ptr */
    &WheelSensorStatus_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_WheelSensorStatus, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_WheelSensorStatus, /* HandleId */
    COM_CAN1_TIRE_CONDITION_RX, /* PduId */
    0, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "TireStatus",
#endif
    &Com_PduData_TireCondition_RX[4], /* ptr */
    &TireStatus_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_TireStatus, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_TireStatus, /* HandleId */
    COM_CAN1_TIRE_CONDITION_RX, /* PduId */
    2, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Tire_Sensor_Electrical_Fault",
#endif
    &Com_PduData_TireCondition_RX[4], /* ptr */
    &Tire_Sensor_Electrical_Fault_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Tire_Sensor_Electrical_Fault, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Tire_Sensor_Electrical_Fault, /* HandleId */
    COM_CAN1_TIRE_CONDITION_RX, /* PduId */
    4, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Tire_Air_Leakage_Rate",
#endif
    &Com_PduData_TireCondition_RX[5], /* ptr */
    &Tire_Air_Leakage_Rate_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Tire_Air_Leakage_Rate, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Tire_Air_Leakage_Rate, /* HandleId */
    COM_CAN1_TIRE_CONDITION_RX, /* PduId */
    0, /* BitPosition */
    16, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT16, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "TirePressureThresholdDetection",
#endif
    &Com_PduData_TireCondition_RX[7], /* ptr */
    &TirePressureThresholdDetection_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_TirePressureThresholdDetection, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_TirePressureThresholdDetection, /* HandleId */
    COM_CAN1_TIRE_CONDITION_RX, /* PduId */
    5, /* BitPosition */
    3, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "DM1_TPMS_ProtectLampStatus",
#endif
    &Com_PduData_DM1_TPMS_RX[0], /* ptr */
    &DM1_TPMS_ProtectLampStatus_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_DM1_TPMS_ProtectLampStatus, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_DM1_TPMS_ProtectLampStatus, /* HandleId */
    COM_CAN1_DM1_TPMS_RX, /* PduId */
    0, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "DM1_TPMS_AmberWarningLampStatus",
#endif
    &Com_PduData_DM1_TPMS_RX[0], /* ptr */
    &DM1_TPMS_AmberWarningLampStatus_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_DM1_TPMS_AmberWarningLampStatus, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_DM1_TPMS_AmberWarningLampStatus, /* HandleId */
    COM_CAN1_DM1_TPMS_RX, /* PduId */
    2, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "DM1_TPMS_RedStopLampState",
#endif
    &Com_PduData_DM1_TPMS_RX[0], /* ptr */
    &DM1_TPMS_RedStopLampState_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_DM1_TPMS_RedStopLampState, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_DM1_TPMS_RedStopLampState, /* HandleId */
    COM_CAN1_DM1_TPMS_RX, /* PduId */
    4, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "LeastByteofSPN",
#endif
    &Com_PduData_DM1_TPMS_RX[2], /* ptr */
    &LeastByteofSPN_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_LeastByteofSPN, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_LeastByteofSPN, /* HandleId */
    COM_CAN1_DM1_TPMS_RX, /* PduId */
    0, /* BitPosition */
    8, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "SecondByteofSPN",
#endif
    &Com_PduData_DM1_TPMS_RX[3], /* ptr */
    &SecondByteofSPN_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_SecondByteofSPN, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_SecondByteofSPN, /* HandleId */
    COM_CAN1_DM1_TPMS_RX, /* PduId */
    0, /* BitPosition */
    8, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "FMI",
#endif
    &Com_PduData_DM1_TPMS_RX[4], /* ptr */
    &FMI_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_FMI, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_FMI, /* HandleId */
    COM_CAN1_DM1_TPMS_RX, /* PduId */
    0, /* BitPosition */
    5, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "_3MostBitofSPN",
#endif
    &Com_PduData_DM1_TPMS_RX[4], /* ptr */
    &_3MostBitofSPN_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig__3MostBitofSPN, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID__3MostBitofSPN, /* HandleId */
    COM_CAN1_DM1_TPMS_RX, /* PduId */
    5, /* BitPosition */
    3, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "OC",
#endif
    &Com_PduData_DM1_TPMS_RX[5], /* ptr */
    &OC_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_OC, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_OC, /* HandleId */
    COM_CAN1_DM1_TPMS_RX, /* PduId */
    0, /* BitPosition */
    7, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "CM",
#endif
    &Com_PduData_DM1_TPMS_RX[5], /* ptr */
    &CM_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_CM, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_CM, /* HandleId */
    COM_CAN1_DM1_TPMS_RX, /* PduId */
    7, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "EBC1_ASREngCtrlActive",
#endif
    &Com_PduData_EBC1_Electronic_Brake_Controller_1_RX[0], /* ptr */
    &EBC1_ASREngCtrlActive_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_EBC1_ASREngCtrlActive, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_EBC1_ASREngCtrlActive, /* HandleId */
    COM_CAN1_EBC1_ELECTRONIC_BRAKE_CONTROLLER_1_RX, /* PduId */
    0, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "EBC1_ASRBrakeCtrlActive",
#endif
    &Com_PduData_EBC1_Electronic_Brake_Controller_1_RX[0], /* ptr */
    &EBC1_ASRBrakeCtrlActive_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_EBC1_ASRBrakeCtrlActive, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_EBC1_ASRBrakeCtrlActive, /* HandleId */
    COM_CAN1_EBC1_ELECTRONIC_BRAKE_CONTROLLER_1_RX, /* PduId */
    2, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "EBC1_AntiLockBrakingActive",
#endif
    &Com_PduData_EBC1_Electronic_Brake_Controller_1_RX[0], /* ptr */
    &EBC1_AntiLockBrakingActive_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_EBC1_AntiLockBrakingActive, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_EBC1_AntiLockBrakingActive, /* HandleId */
    COM_CAN1_EBC1_ELECTRONIC_BRAKE_CONTROLLER_1_RX, /* PduId */
    4, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "EBC1_EBSBrakeSwitch",
#endif
    &Com_PduData_EBC1_Electronic_Brake_Controller_1_RX[0], /* ptr */
    &EBC1_EBSBrakeSwitch_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_EBC1_EBSBrakeSwitch, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_EBC1_EBSBrakeSwitch, /* HandleId */
    COM_CAN1_EBC1_ELECTRONIC_BRAKE_CONTROLLER_1_RX, /* PduId */
    6, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "EBC1_Brake_Pedal_Position",
#endif
    &Com_PduData_EBC1_Electronic_Brake_Controller_1_RX[1], /* ptr */
    &EBC1_Brake_Pedal_Position_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_EBC1_Brake_Pedal_Position, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_EBC1_Brake_Pedal_Position, /* HandleId */
    COM_CAN1_EBC1_ELECTRONIC_BRAKE_CONTROLLER_1_RX, /* PduId */
    0, /* BitPosition */
    8, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "EBC1_ABS_OffRoad_switch",
#endif
    &Com_PduData_EBC1_Electronic_Brake_Controller_1_RX[2], /* ptr */
    &EBC1_ABS_OffRoad_switch_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_EBC1_ABS_OffRoad_switch, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_EBC1_ABS_OffRoad_switch, /* HandleId */
    COM_CAN1_EBC1_ELECTRONIC_BRAKE_CONTROLLER_1_RX, /* PduId */
    0, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "EBC1_ASR_OffRoad_switch",
#endif
    &Com_PduData_EBC1_Electronic_Brake_Controller_1_RX[2], /* ptr */
    &EBC1_ASR_OffRoad_switch_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_EBC1_ASR_OffRoad_switch, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_EBC1_ASR_OffRoad_switch, /* HandleId */
    COM_CAN1_EBC1_ELECTRONIC_BRAKE_CONTROLLER_1_RX, /* PduId */
    2, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "EBC1_ASR_HillHolder_switch",
#endif
    &Com_PduData_EBC1_Electronic_Brake_Controller_1_RX[2], /* ptr */
    &EBC1_ASR_HillHolder_switch_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_EBC1_ASR_HillHolder_switch, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_EBC1_ASR_HillHolder_switch, /* HandleId */
    COM_CAN1_EBC1_ELECTRONIC_BRAKE_CONTROLLER_1_RX, /* PduId */
    4, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "EBC1_Traction_ControlOverride_switch",
#endif
    &Com_PduData_EBC1_Electronic_Brake_Controller_1_RX[2], /* ptr */
    &EBC1_Traction_ControlOverride_switch_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_EBC1_Traction_ControlOverride_switch, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_EBC1_Traction_ControlOverride_switch, /* HandleId */
    COM_CAN1_EBC1_ELECTRONIC_BRAKE_CONTROLLER_1_RX, /* PduId */
    6, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "ABS_Fully_Operational",
#endif
    &Com_PduData_EBC1_Electronic_Brake_Controller_1_RX[5], /* ptr */
    &ABS_Fully_Operational_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_ABS_Fully_Operational, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_ABS_Fully_Operational, /* HandleId */
    COM_CAN1_EBC1_ELECTRONIC_BRAKE_CONTROLLER_1_RX, /* PduId */
    0, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "EBC1_EBSRedWarningSignal",
#endif
    &Com_PduData_EBC1_Electronic_Brake_Controller_1_RX[5], /* ptr */
    &EBC1_EBSRedWarningSignal_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_EBC1_EBSRedWarningSignal, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_EBC1_EBSRedWarningSignal, /* HandleId */
    COM_CAN1_EBC1_ELECTRONIC_BRAKE_CONTROLLER_1_RX, /* PduId */
    2, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "EBC1_ABS_EBSAmberWarningSignal",
#endif
    &Com_PduData_EBC1_Electronic_Brake_Controller_1_RX[5], /* ptr */
    &EBC1_ABS_EBSAmberWarningSignal_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_EBC1_ABS_EBSAmberWarningSignal, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_EBC1_ABS_EBSAmberWarningSignal, /* HandleId */
    COM_CAN1_EBC1_ELECTRONIC_BRAKE_CONTROLLER_1_RX, /* PduId */
    4, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "EBC1_ATC_ASRInformationSignal",
#endif
    &Com_PduData_EBC1_Electronic_Brake_Controller_1_RX[5], /* ptr */
    &EBC1_ATC_ASRInformationSignal_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_EBC1_ATC_ASRInformationSignal, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_EBC1_ATC_ASRInformationSignal, /* HandleId */
    COM_CAN1_EBC1_ELECTRONIC_BRAKE_CONTROLLER_1_RX, /* PduId */
    6, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Foundation_Brake_Use",
#endif
    &Com_PduData_EBC5_Electronic_Brake_Controller_5_RX[1], /* ptr */
    &Foundation_Brake_Use_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Foundation_Brake_Use, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Foundation_Brake_Use, /* HandleId */
    COM_CAN1_EBC5_ELECTRONIC_BRAKE_CONTROLLER_5_RX, /* PduId */
    0, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "XBR_System_State",
#endif
    &Com_PduData_EBC5_Electronic_Brake_Controller_5_RX[1], /* ptr */
    &XBR_System_State_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_XBR_System_State, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_XBR_System_State, /* HandleId */
    COM_CAN1_EBC5_ELECTRONIC_BRAKE_CONTROLLER_5_RX, /* PduId */
    2, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "XBR_Active_Control_Mode",
#endif
    &Com_PduData_EBC5_Electronic_Brake_Controller_5_RX[1], /* ptr */
    &XBR_Active_Control_Mode_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_XBR_Active_Control_Mode, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_XBR_Active_Control_Mode, /* HandleId */
    COM_CAN1_EBC5_ELECTRONIC_BRAKE_CONTROLLER_5_RX, /* PduId */
    4, /* BitPosition */
    4, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "XBR_Acceleration_Limit",
#endif
    &Com_PduData_EBC5_Electronic_Brake_Controller_5_RX[2], /* ptr */
    &XBR_Acceleration_Limit_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_XBR_Acceleration_Limit, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_XBR_Acceleration_Limit, /* HandleId */
    COM_CAN1_EBC5_ELECTRONIC_BRAKE_CONTROLLER_5_RX, /* PduId */
    0, /* BitPosition */
    8, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Parking_Brake_Actuator_Fully_Activated",
#endif
    &Com_PduData_EBC5_Electronic_Brake_Controller_5_RX[3], /* ptr */
    &Parking_Brake_Actuator_Fully_Activated_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Parking_Brake_Actuator_Fully_Activated, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Parking_Brake_Actuator_Fully_Activated, /* HandleId */
    COM_CAN1_EBC5_ELECTRONIC_BRAKE_CONTROLLER_5_RX, /* PduId */
    0, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Emergency_Braking_Active",
#endif
    &Com_PduData_EBC5_Electronic_Brake_Controller_5_RX[3], /* ptr */
    &Emergency_Braking_Active_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Emergency_Braking_Active, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Emergency_Braking_Active, /* HandleId */
    COM_CAN1_EBC5_ELECTRONIC_BRAKE_CONTROLLER_5_RX, /* PduId */
    2, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "DLCC1_EngAmberWarningLampCmd",
#endif
    &Com_PduData_DLCC1_Direct_Lamp_Control_Command_1_RX[0], /* ptr */
    &DLCC1_EngAmberWarningLampCmd_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_DLCC1_EngAmberWarningLampCmd, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_DLCC1_EngAmberWarningLampCmd, /* HandleId */
    COM_CAN1_DLCC1_DIRECT_LAMP_CONTROL_COMMAND_1_RX, /* PduId */
    2, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "DLCC1_EngRedStopLampCmd",
#endif
    &Com_PduData_DLCC1_Direct_Lamp_Control_Command_1_RX[0], /* ptr */
    &DLCC1_EngRedStopLampCmd_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_DLCC1_EngRedStopLampCmd, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_DLCC1_EngRedStopLampCmd, /* HandleId */
    COM_CAN1_DLCC1_DIRECT_LAMP_CONTROL_COMMAND_1_RX, /* PduId */
    4, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "DLCC1_OBDMalfunctionLampCmd",
#endif
    &Com_PduData_DLCC1_Direct_Lamp_Control_Command_1_RX[0], /* ptr */
    &DLCC1_OBDMalfunctionLampCmd_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_DLCC1_OBDMalfunctionLampCmd, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_DLCC1_OBDMalfunctionLampCmd, /* HandleId */
    COM_CAN1_DLCC1_DIRECT_LAMP_CONTROL_COMMAND_1_RX, /* PduId */
    6, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "DLCC1_EngBrakeActiveLampCmd",
#endif
    &Com_PduData_DLCC1_Direct_Lamp_Control_Command_1_RX[1], /* ptr */
    &DLCC1_EngBrakeActiveLampCmd_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_DLCC1_EngBrakeActiveLampCmd, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_DLCC1_EngBrakeActiveLampCmd, /* HandleId */
    COM_CAN1_DLCC1_DIRECT_LAMP_CONTROL_COMMAND_1_RX, /* PduId */
    0, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "DLCC1_EngOilPressLowLampCmd",
#endif
    &Com_PduData_DLCC1_Direct_Lamp_Control_Command_1_RX[1], /* ptr */
    &DLCC1_EngOilPressLowLampCmd_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_DLCC1_EngOilPressLowLampCmd, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_DLCC1_EngOilPressLowLampCmd, /* HandleId */
    COM_CAN1_DLCC1_DIRECT_LAMP_CONTROL_COMMAND_1_RX, /* PduId */
    4, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "DLCC1_EngCoolantTempHighLampCmd",
#endif
    &Com_PduData_DLCC1_Direct_Lamp_Control_Command_1_RX[1], /* ptr */
    &DLCC1_EngCoolantTempHighLampCmd_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_DLCC1_EngCoolantTempHighLampCmd, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_DLCC1_EngCoolantTempHighLampCmd, /* HandleId */
    COM_CAN1_DLCC1_DIRECT_LAMP_CONTROL_COMMAND_1_RX, /* PduId */
    6, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "DLCC1_EngCoolantLevelLowLampCmd",
#endif
    &Com_PduData_DLCC1_Direct_Lamp_Control_Command_1_RX[2], /* ptr */
    &DLCC1_EngCoolantLevelLowLampCmd_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_DLCC1_EngCoolantLevelLowLampCmd, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_DLCC1_EngCoolantLevelLowLampCmd, /* HandleId */
    COM_CAN1_DLCC1_DIRECT_LAMP_CONTROL_COMMAND_1_RX, /* PduId */
    0, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "CCVS1_TwoSpeedAxleSwitch",
#endif
    &Com_PduData_CCVS1_Cruise_Control_Vehicle_Speed_1_RX[0], /* ptr */
    &CCVS1_TwoSpeedAxleSwitch_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_CCVS1_TwoSpeedAxleSwitch, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_CCVS1_TwoSpeedAxleSwitch, /* HandleId */
    COM_CAN1_CCVS1_CRUISE_CONTROL_VEHICLE_SPEED_1_RX, /* PduId */
    0, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "CCVS1_ParkingBrakeSwitch",
#endif
    &Com_PduData_CCVS1_Cruise_Control_Vehicle_Speed_1_RX[0], /* ptr */
    &CCVS1_ParkingBrakeSwitch_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_CCVS1_ParkingBrakeSwitch, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_CCVS1_ParkingBrakeSwitch, /* HandleId */
    COM_CAN1_CCVS1_CRUISE_CONTROL_VEHICLE_SPEED_1_RX, /* PduId */
    2, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "CCVS1_WheelBasedVehicleSpeed",
#endif
    &Com_PduData_CCVS1_Cruise_Control_Vehicle_Speed_1_RX[1], /* ptr */
    &CCVS1_WheelBasedVehicleSpeed_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_CCVS1_WheelBasedVehicleSpeed, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_CCVS1_WheelBasedVehicleSpeed, /* HandleId */
    COM_CAN1_CCVS1_CRUISE_CONTROL_VEHICLE_SPEED_1_RX, /* PduId */
    0, /* BitPosition */
    16, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT16, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "CCVS1_CruiseCtrlActive",
#endif
    &Com_PduData_CCVS1_Cruise_Control_Vehicle_Speed_1_RX[3], /* ptr */
    &CCVS1_CruiseCtrlActive_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_CCVS1_CruiseCtrlActive, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_CCVS1_CruiseCtrlActive, /* HandleId */
    COM_CAN1_CCVS1_CRUISE_CONTROL_VEHICLE_SPEED_1_RX, /* PduId */
    0, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "CCVS1_CruiseCtrlEnableSwitch",
#endif
    &Com_PduData_CCVS1_Cruise_Control_Vehicle_Speed_1_RX[3], /* ptr */
    &CCVS1_CruiseCtrlEnableSwitch_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_CCVS1_CruiseCtrlEnableSwitch, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_CCVS1_CruiseCtrlEnableSwitch, /* HandleId */
    COM_CAN1_CCVS1_CRUISE_CONTROL_VEHICLE_SPEED_1_RX, /* PduId */
    2, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "CCVS1_BrakeSwitch",
#endif
    &Com_PduData_CCVS1_Cruise_Control_Vehicle_Speed_1_RX[3], /* ptr */
    &CCVS1_BrakeSwitch_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_CCVS1_BrakeSwitch, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_CCVS1_BrakeSwitch, /* HandleId */
    COM_CAN1_CCVS1_CRUISE_CONTROL_VEHICLE_SPEED_1_RX, /* PduId */
    4, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "CCVS1_ClutchSwitch",
#endif
    &Com_PduData_CCVS1_Cruise_Control_Vehicle_Speed_1_RX[3], /* ptr */
    &CCVS1_ClutchSwitch_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_CCVS1_ClutchSwitch, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_CCVS1_ClutchSwitch, /* HandleId */
    COM_CAN1_CCVS1_CRUISE_CONTROL_VEHICLE_SPEED_1_RX, /* PduId */
    6, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "CCVS1_CruiseCtrlSetSwitch",
#endif
    &Com_PduData_CCVS1_Cruise_Control_Vehicle_Speed_1_RX[4], /* ptr */
    &CCVS1_CruiseCtrlSetSwitch_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_CCVS1_CruiseCtrlSetSwitch, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_CCVS1_CruiseCtrlSetSwitch, /* HandleId */
    COM_CAN1_CCVS1_CRUISE_CONTROL_VEHICLE_SPEED_1_RX, /* PduId */
    0, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "CCVS1_CruiseCtrlCoastSwitch",
#endif
    &Com_PduData_CCVS1_Cruise_Control_Vehicle_Speed_1_RX[4], /* ptr */
    &CCVS1_CruiseCtrlCoastSwitch_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_CCVS1_CruiseCtrlCoastSwitch, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_CCVS1_CruiseCtrlCoastSwitch, /* HandleId */
    COM_CAN1_CCVS1_CRUISE_CONTROL_VEHICLE_SPEED_1_RX, /* PduId */
    2, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "CCVS1_CruiseCtrlResumeSwitch",
#endif
    &Com_PduData_CCVS1_Cruise_Control_Vehicle_Speed_1_RX[4], /* ptr */
    &CCVS1_CruiseCtrlResumeSwitch_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_CCVS1_CruiseCtrlResumeSwitch, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_CCVS1_CruiseCtrlResumeSwitch, /* HandleId */
    COM_CAN1_CCVS1_CRUISE_CONTROL_VEHICLE_SPEED_1_RX, /* PduId */
    4, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "CCVS1_CruiseCtrlAccelerateSwitch",
#endif
    &Com_PduData_CCVS1_Cruise_Control_Vehicle_Speed_1_RX[4], /* ptr */
    &CCVS1_CruiseCtrlAccelerateSwitch_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_CCVS1_CruiseCtrlAccelerateSwitch, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_CCVS1_CruiseCtrlAccelerateSwitch, /* HandleId */
    COM_CAN1_CCVS1_CRUISE_CONTROL_VEHICLE_SPEED_1_RX, /* PduId */
    6, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "CCVS1_CruiseCtrlSetSpeed",
#endif
    &Com_PduData_CCVS1_Cruise_Control_Vehicle_Speed_1_RX[5], /* ptr */
    &CCVS1_CruiseCtrlSetSpeed_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_CCVS1_CruiseCtrlSetSpeed, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_CCVS1_CruiseCtrlSetSpeed, /* HandleId */
    COM_CAN1_CCVS1_CRUISE_CONTROL_VEHICLE_SPEED_1_RX, /* PduId */
    0, /* BitPosition */
    8, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "CCVS1_PTOGovernorState",
#endif
    &Com_PduData_CCVS1_Cruise_Control_Vehicle_Speed_1_RX[6], /* ptr */
    &CCVS1_PTOGovernorState_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_CCVS1_PTOGovernorState, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_CCVS1_PTOGovernorState, /* HandleId */
    COM_CAN1_CCVS1_CRUISE_CONTROL_VEHICLE_SPEED_1_RX, /* PduId */
    0, /* BitPosition */
    5, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "CCVS1_CruiseCtrlStates",
#endif
    &Com_PduData_CCVS1_Cruise_Control_Vehicle_Speed_1_RX[6], /* ptr */
    &CCVS1_CruiseCtrlStates_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_CCVS1_CruiseCtrlStates, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_CCVS1_CruiseCtrlStates, /* HandleId */
    COM_CAN1_CCVS1_CRUISE_CONTROL_VEHICLE_SPEED_1_RX, /* PduId */
    5, /* BitPosition */
    3, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "VDC1_VDCInformationSignal",
#endif
    &Com_PduData_VDC1_Vehicle_Dynamic_Stability_Control_1_RX[0], /* ptr */
    &VDC1_VDCInformationSignal_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_VDC1_VDCInformationSignal, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_VDC1_VDCInformationSignal, /* HandleId */
    COM_CAN1_VDC1_VEHICLE_DYNAMIC_STABILITY_CONTROL_1_RX, /* PduId */
    0, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "VDC1_VDCFullyOperational",
#endif
    &Com_PduData_VDC1_Vehicle_Dynamic_Stability_Control_1_RX[0], /* ptr */
    &VDC1_VDCFullyOperational_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_VDC1_VDCFullyOperational, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_VDC1_VDCFullyOperational, /* HandleId */
    COM_CAN1_VDC1_VEHICLE_DYNAMIC_STABILITY_CONTROL_1_RX, /* PduId */
    2, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "VDC1_VDC_brake_light_request",
#endif
    &Com_PduData_VDC1_Vehicle_Dynamic_Stability_Control_1_RX[0], /* ptr */
    &VDC1_VDC_brake_light_request_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_VDC1_VDC_brake_light_request, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_VDC1_VDC_brake_light_request, /* HandleId */
    COM_CAN1_VDC1_VEHICLE_DYNAMIC_STABILITY_CONTROL_1_RX, /* PduId */
    4, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "VDC1_ROPEngCtrlActive",
#endif
    &Com_PduData_VDC1_Vehicle_Dynamic_Stability_Control_1_RX[1], /* ptr */
    &VDC1_ROPEngCtrlActive_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_VDC1_ROPEngCtrlActive, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_VDC1_ROPEngCtrlActive, /* HandleId */
    COM_CAN1_VDC1_VEHICLE_DYNAMIC_STABILITY_CONTROL_1_RX, /* PduId */
    0, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "VDC1_ROPBrakeCtrlActive",
#endif
    &Com_PduData_VDC1_Vehicle_Dynamic_Stability_Control_1_RX[1], /* ptr */
    &VDC1_ROPBrakeCtrlActive_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_VDC1_ROPBrakeCtrlActive, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_VDC1_ROPBrakeCtrlActive, /* HandleId */
    COM_CAN1_VDC1_VEHICLE_DYNAMIC_STABILITY_CONTROL_1_RX, /* PduId */
    2, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "VDC1_YCEngCtrlActive",
#endif
    &Com_PduData_VDC1_Vehicle_Dynamic_Stability_Control_1_RX[1], /* ptr */
    &VDC1_YCEngCtrlActive_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_VDC1_YCEngCtrlActive, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_VDC1_YCEngCtrlActive, /* HandleId */
    COM_CAN1_VDC1_VEHICLE_DYNAMIC_STABILITY_CONTROL_1_RX, /* PduId */
    4, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "VDC1_YCBrakeCtrlActive",
#endif
    &Com_PduData_VDC1_Vehicle_Dynamic_Stability_Control_1_RX[1], /* ptr */
    &VDC1_YCBrakeCtrlActive_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_VDC1_YCBrakeCtrlActive, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_VDC1_YCBrakeCtrlActive, /* HandleId */
    COM_CAN1_VDC1_VEHICLE_DYNAMIC_STABILITY_CONTROL_1_RX, /* PduId */
    6, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "ERC1_RX_ERC1_ActualRetarderPercentTorque",
#endif
    &Com_PduData_ERC1_RX[1], /* ptr */
    &ERC1_RX_ERC1_ActualRetarderPercentTorque_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_ERC1_RX_ERC1_ActualRetarderPercentTorque, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_ERC1_RX_ERC1_ActualRetarderPercentTorque, /* HandleId */
    COM_CAN1_ERC1_RX, /* PduId */
    0, /* BitPosition */
    8, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "ERC3_RX_ERC1_ActualRetarderPercentTorque",
#endif
    &Com_PduData_ERC3_RX[1], /* ptr */
    &ERC3_RX_ERC1_ActualRetarderPercentTorque_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_ERC3_RX_ERC1_ActualRetarderPercentTorque, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_ERC3_RX_ERC1_ActualRetarderPercentTorque, /* HandleId */
    COM_CAN1_ERC3_RX, /* PduId */
    0, /* BitPosition */
    8, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "TransReverseDirectionSw",
#endif
    &Com_PduData_ETC5_RX[1], /* ptr */
    &TransReverseDirectionSw_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_TransReverseDirectionSw, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_TransReverseDirectionSw, /* HandleId */
    COM_CAN1_ETC5_RX, /* PduId */
    0, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "TransNeutralSwitch",
#endif
    &Com_PduData_ETC5_RX[1], /* ptr */
    &TransNeutralSwitch_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_TransNeutralSwitch, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_TransNeutralSwitch, /* HandleId */
    COM_CAN1_ETC5_RX, /* PduId */
    2, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "ECC_Work_Switch",
#endif
    &Com_PduData_EEC3_RX[0], /* ptr */
    &ECC_Work_Switch_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_ECC_Work_Switch, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_ECC_Work_Switch, /* HandleId */
    COM_CAN1_EEC3_RX, /* PduId */
    0, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "ECC_COMP_ReqSwitch",
#endif
    &Com_PduData_EEC3_RX[0], /* ptr */
    &ECC_COMP_ReqSwitch_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_ECC_COMP_ReqSwitch, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_ECC_COMP_ReqSwitch, /* HandleId */
    COM_CAN1_EEC3_RX, /* PduId */
    1, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "ECC_WPTC_ReqSwitch",
#endif
    &Com_PduData_EEC3_RX[0], /* ptr */
    &ECC_WPTC_ReqSwitch_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_ECC_WPTC_ReqSwitch, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_ECC_WPTC_ReqSwitch, /* HandleId */
    COM_CAN1_EEC3_RX, /* PduId */
    2, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "REC_Switch",
#endif
    &Com_PduData_EEC3_RX[0], /* ptr */
    &REC_Switch_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_REC_Switch, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_REC_Switch, /* HandleId */
    COM_CAN1_EEC3_RX, /* PduId */
    3, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Fan_Gear_Switch",
#endif
    &Com_PduData_EEC3_RX[0], /* ptr */
    &Fan_Gear_Switch_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Fan_Gear_Switch, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Fan_Gear_Switch, /* HandleId */
    COM_CAN1_EEC3_RX, /* PduId */
    4, /* BitPosition */
    4, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "HVAC_MODE_Switch",
#endif
    &Com_PduData_EEC3_RX[1], /* ptr */
    &HVAC_MODE_Switch_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_HVAC_MODE_Switch, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_HVAC_MODE_Switch, /* HandleId */
    COM_CAN1_EEC3_RX, /* PduId */
    0, /* BitPosition */
    3, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "HVAC_SET_Temp_Switch",
#endif
    &Com_PduData_EEC3_RX[1], /* ptr */
    &HVAC_SET_Temp_Switch_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_HVAC_SET_Temp_Switch, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_HVAC_SET_Temp_Switch, /* HandleId */
    COM_CAN1_EEC3_RX, /* PduId */
    3, /* BitPosition */
    5, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "One_click_defrosting",
#endif
    &Com_PduData_EEC3_RX[5], /* ptr */
    &One_click_defrosting_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_One_click_defrosting, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_One_click_defrosting, /* HandleId */
    COM_CAN1_EEC3_RX, /* PduId */
    7, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "ECC_Work_Status",
#endif
    &Com_PduData_ECC2_RX[0], /* ptr */
    &ECC_Work_Status_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_ECC_Work_Status, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_ECC_Work_Status, /* HandleId */
    COM_CAN1_ECC2_RX, /* PduId */
    0, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "ECC_COMP_ReqStatus",
#endif
    &Com_PduData_ECC2_RX[0], /* ptr */
    &ECC_COMP_ReqStatus_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_ECC_COMP_ReqStatus, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_ECC_COMP_ReqStatus, /* HandleId */
    COM_CAN1_ECC2_RX, /* PduId */
    1, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "REC_Status",
#endif
    &Com_PduData_ECC2_RX[0], /* ptr */
    &REC_Status_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_REC_Status, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_REC_Status, /* HandleId */
    COM_CAN1_ECC2_RX, /* PduId */
    3, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Fan_Gear",
#endif
    &Com_PduData_ECC2_RX[0], /* ptr */
    &Fan_Gear_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Fan_Gear, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Fan_Gear, /* HandleId */
    COM_CAN1_ECC2_RX, /* PduId */
    4, /* BitPosition */
    4, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "HVAC_MODE_Status",
#endif
    &Com_PduData_ECC2_RX[1], /* ptr */
    &HVAC_MODE_Status_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_HVAC_MODE_Status, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_HVAC_MODE_Status, /* HandleId */
    COM_CAN1_ECC2_RX, /* PduId */
    0, /* BitPosition */
    3, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "HVAC_SET_Temp",
#endif
    &Com_PduData_ECC2_RX[1], /* ptr */
    &HVAC_SET_Temp_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_HVAC_SET_Temp, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_HVAC_SET_Temp, /* HandleId */
    COM_CAN1_ECC2_RX, /* PduId */
    3, /* BitPosition */
    5, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "EVAP_Temp",
#endif
    &Com_PduData_ECC2_RX[3], /* ptr */
    &EVAP_Temp_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_EVAP_Temp, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_EVAP_Temp, /* HandleId */
    COM_CAN1_ECC2_RX, /* PduId */
    0, /* BitPosition */
    8, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "MID_PRESS_Status",
#endif
    &Com_PduData_ECC2_RX[5], /* ptr */
    &MID_PRESS_Status_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_MID_PRESS_Status, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_MID_PRESS_Status, /* HandleId */
    COM_CAN1_ECC2_RX, /* PduId */
    2, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "H_L_PRESS_Sta",
#endif
    &Com_PduData_ECC2_RX[5], /* ptr */
    &H_L_PRESS_Sta_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_H_L_PRESS_Sta, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_H_L_PRESS_Sta, /* HandleId */
    COM_CAN1_ECC2_RX, /* PduId */
    3, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "One_click_defrosting_Status",
#endif
    &Com_PduData_ECC2_RX[5], /* ptr */
    &One_click_defrosting_Status_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_One_click_defrosting_Status, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_One_click_defrosting_Status, /* HandleId */
    COM_CAN1_ECC2_RX, /* PduId */
    7, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "N_Shift_WF",
#endif
    &Com_PduData_ID1_RX[0], /* ptr */
    &N_Shift_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_N_Shift_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_N_Shift_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    0, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "AI_Clutch_WF",
#endif
    &Com_PduData_ID1_RX[0], /* ptr */
    &AI_Clutch_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_AI_Clutch_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_AI_Clutch_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    1, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "StartupSts_Fb_WF",
#endif
    &Com_PduData_ID1_RX[0], /* ptr */
    &StartupSts_Fb_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_StartupSts_Fb_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_StartupSts_Fb_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    2, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "High_low_Voltage_SW_WF",
#endif
    &Com_PduData_ID1_RX[0], /* ptr */
    &High_low_Voltage_SW_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_High_low_Voltage_SW_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_High_low_Voltage_SW_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    3, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "AC_DOH_WF",
#endif
    &Com_PduData_ID1_RX[0], /* ptr */
    &AC_DOH_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_AC_DOH_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_AC_DOH_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    4, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "D1_Diag_WF",
#endif
    &Com_PduData_ID1_RX[0], /* ptr */
    &D1_Diag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_D1_Diag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_D1_Diag_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    5, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "D2_Diag_WF",
#endif
    &Com_PduData_ID1_RX[0], /* ptr */
    &D2_Diag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_D2_Diag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_D2_Diag_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    6, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "D3_Diag_WF",
#endif
    &Com_PduData_ID1_RX[0], /* ptr */
    &D3_Diag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_D3_Diag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_D3_Diag_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    7, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "D4_Diag_WF",
#endif
    &Com_PduData_ID1_RX[1], /* ptr */
    &D4_Diag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_D4_Diag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_D4_Diag_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    0, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "D5_Diag_WF",
#endif
    &Com_PduData_ID1_RX[1], /* ptr */
    &D5_Diag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_D5_Diag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_D5_Diag_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    1, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "D6_Diag_WF",
#endif
    &Com_PduData_ID1_RX[1], /* ptr */
    &D6_Diag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_D6_Diag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_D6_Diag_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    2, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "D7_Diag_WF",
#endif
    &Com_PduData_ID1_RX[1], /* ptr */
    &D7_Diag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_D7_Diag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_D7_Diag_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    3, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "D8_Diag_WF",
#endif
    &Com_PduData_ID1_RX[1], /* ptr */
    &D8_Diag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_D8_Diag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_D8_Diag_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    4, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "D9_Diag_WF",
#endif
    &Com_PduData_ID1_RX[1], /* ptr */
    &D9_Diag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_D9_Diag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_D9_Diag_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    5, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "D10_Diag_WF",
#endif
    &Com_PduData_ID1_RX[1], /* ptr */
    &D10_Diag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_D10_Diag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_D10_Diag_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    6, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "D11_Diag_WF",
#endif
    &Com_PduData_ID1_RX[1], /* ptr */
    &D11_Diag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_D11_Diag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_D11_Diag_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    7, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "D12_Diag_WF",
#endif
    &Com_PduData_ID1_RX[2], /* ptr */
    &D12_Diag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_D12_Diag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_D12_Diag_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    0, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "D13_Diag_WF",
#endif
    &Com_PduData_ID1_RX[2], /* ptr */
    &D13_Diag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_D13_Diag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_D13_Diag_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    1, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "D14_Diag_WF",
#endif
    &Com_PduData_ID1_RX[2], /* ptr */
    &D14_Diag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_D14_Diag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_D14_Diag_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    2, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "D15_Diag_WF",
#endif
    &Com_PduData_ID1_RX[2], /* ptr */
    &D15_Diag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_D15_Diag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_D15_Diag_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    3, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "D16_Diag_WF",
#endif
    &Com_PduData_ID1_RX[2], /* ptr */
    &D16_Diag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_D16_Diag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_D16_Diag_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    4, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "D17_Diag_WF",
#endif
    &Com_PduData_ID1_RX[2], /* ptr */
    &D17_Diag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_D17_Diag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_D17_Diag_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    5, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "D18_Diag_WF",
#endif
    &Com_PduData_ID1_RX[2], /* ptr */
    &D18_Diag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_D18_Diag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_D18_Diag_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    6, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "D19_Diag_WF",
#endif
    &Com_PduData_ID1_RX[2], /* ptr */
    &D19_Diag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_D19_Diag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_D19_Diag_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    7, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "D20_Diag_WF",
#endif
    &Com_PduData_ID1_RX[3], /* ptr */
    &D20_Diag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_D20_Diag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_D20_Diag_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    0, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "D21_Diag_WF",
#endif
    &Com_PduData_ID1_RX[3], /* ptr */
    &D21_Diag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_D21_Diag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_D21_Diag_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    1, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "D22_Diag_WF",
#endif
    &Com_PduData_ID1_RX[3], /* ptr */
    &D22_Diag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_D22_Diag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_D22_Diag_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    2, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "D23_Diag_WF",
#endif
    &Com_PduData_ID1_RX[3], /* ptr */
    &D23_Diag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_D23_Diag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_D23_Diag_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    3, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "D24_Diag_WF",
#endif
    &Com_PduData_ID1_RX[3], /* ptr */
    &D24_Diag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_D24_Diag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_D24_Diag_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    4, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "D25_Diag_WF",
#endif
    &Com_PduData_ID1_RX[3], /* ptr */
    &D25_Diag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_D25_Diag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_D25_Diag_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    5, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "D26_Diag_WF",
#endif
    &Com_PduData_ID1_RX[3], /* ptr */
    &D26_Diag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_D26_Diag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_D26_Diag_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    6, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "D27_Diag_WF",
#endif
    &Com_PduData_ID1_RX[3], /* ptr */
    &D27_Diag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_D27_Diag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_D27_Diag_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    7, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "D28_Diag_WF",
#endif
    &Com_PduData_ID1_RX[4], /* ptr */
    &D28_Diag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_D28_Diag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_D28_Diag_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    0, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "D29_Diag_WF",
#endif
    &Com_PduData_ID1_RX[4], /* ptr */
    &D29_Diag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_D29_Diag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_D29_Diag_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    1, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "D30_Diag_WF",
#endif
    &Com_PduData_ID1_RX[4], /* ptr */
    &D30_Diag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_D30_Diag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_D30_Diag_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    2, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "D31_Diag_WF",
#endif
    &Com_PduData_ID1_RX[4], /* ptr */
    &D31_Diag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_D31_Diag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_D31_Diag_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    3, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "D32_Diag_WF",
#endif
    &Com_PduData_ID1_RX[4], /* ptr */
    &D32_Diag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_D32_Diag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_D32_Diag_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    4, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "D33_Diag_WF",
#endif
    &Com_PduData_ID1_RX[4], /* ptr */
    &D33_Diag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_D33_Diag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_D33_Diag_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    5, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "D34_Diag_WF",
#endif
    &Com_PduData_ID1_RX[4], /* ptr */
    &D34_Diag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_D34_Diag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_D34_Diag_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    6, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "D35_Diag_WF",
#endif
    &Com_PduData_ID1_RX[4], /* ptr */
    &D35_Diag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_D35_Diag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_D35_Diag_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    7, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "D36_Diag_WF",
#endif
    &Com_PduData_ID1_RX[5], /* ptr */
    &D36_Diag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_D36_Diag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_D36_Diag_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    0, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "D38_Diag_WF",
#endif
    &Com_PduData_ID1_RX[5], /* ptr */
    &D38_Diag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_D38_Diag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_D38_Diag_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    1, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "D39_Diag_WF",
#endif
    &Com_PduData_ID1_RX[5], /* ptr */
    &D39_Diag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_D39_Diag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_D39_Diag_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    2, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "D40_Diag_WF",
#endif
    &Com_PduData_ID1_RX[5], /* ptr */
    &D40_Diag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_D40_Diag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_D40_Diag_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    3, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "D41_Diag_WF",
#endif
    &Com_PduData_ID1_RX[5], /* ptr */
    &D41_Diag_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_D41_Diag_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_D41_Diag_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    4, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Wiper_H_RlyCoil_Ctrl_WF",
#endif
    &Com_PduData_ID1_RX[5], /* ptr */
    &Wiper_H_RlyCoil_Ctrl_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Wiper_H_RlyCoil_Ctrl_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Wiper_H_RlyCoil_Ctrl_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    5, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Blower_RlyCoil_Ctrl_WF",
#endif
    &Com_PduData_ID1_RX[5], /* ptr */
    &Blower_RlyCoil_Ctrl_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Blower_RlyCoil_Ctrl_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Blower_RlyCoil_Ctrl_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    6, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "IG_Fb_WF",
#endif
    &Com_PduData_ID1_RX[5], /* ptr */
    &IG_Fb_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_IG_Fb_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_IG_Fb_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    7, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "IG_RlyCoil_Ctrl_WF",
#endif
    &Com_PduData_ID1_RX[6], /* ptr */
    &IG_RlyCoil_Ctrl_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_IG_RlyCoil_Ctrl_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_IG_RlyCoil_Ctrl_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    0, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "ACC_Fb_WF",
#endif
    &Com_PduData_ID1_RX[6], /* ptr */
    &ACC_Fb_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_ACC_Fb_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_ACC_Fb_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    1, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "ACC_RlyCoil_Ctrl_WF",
#endif
    &Com_PduData_ID1_RX[6], /* ptr */
    &ACC_RlyCoil_Ctrl_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_ACC_RlyCoil_Ctrl_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_ACC_RlyCoil_Ctrl_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    2, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Horn_RlyCoil_Ctrl_WF",
#endif
    &Com_PduData_ID1_RX[6], /* ptr */
    &Horn_RlyCoil_Ctrl_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Horn_RlyCoil_Ctrl_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Horn_RlyCoil_Ctrl_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    3, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Wiper_Power_RlyCoil_Ctrl_WF",
#endif
    &Com_PduData_ID1_RX[6], /* ptr */
    &Wiper_Power_RlyCoil_Ctrl_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Wiper_Power_RlyCoil_Ctrl_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Wiper_Power_RlyCoil_Ctrl_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    4, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Startup_SIG_WF",
#endif
    &Com_PduData_ID1_RX[6], /* ptr */
    &Startup_SIG_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Startup_SIG_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Startup_SIG_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    5, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "F_LOGO_Lamp_WF",
#endif
    &Com_PduData_ID1_RX[6], /* ptr */
    &F_LOGO_Lamp_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_F_LOGO_Lamp_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_F_LOGO_Lamp_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    6, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Washer_Motor_WF",
#endif
    &Com_PduData_ID1_RX[6], /* ptr */
    &Washer_Motor_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Washer_Motor_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Washer_Motor_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    7, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "HSD1_Reserve_WF",
#endif
    &Com_PduData_ID1_RX[7], /* ptr */
    &HSD1_Reserve_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_HSD1_Reserve_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_HSD1_Reserve_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    0, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Battery_Saver_WF",
#endif
    &Com_PduData_ID1_RX[7], /* ptr */
    &Battery_Saver_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Battery_Saver_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Battery_Saver_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    1, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Dome_Lamp_WF",
#endif
    &Com_PduData_ID1_RX[7], /* ptr */
    &Dome_Lamp_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Dome_Lamp_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Dome_Lamp_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    2, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "LSD1_Reserve_WF",
#endif
    &Com_PduData_ID1_RX[7], /* ptr */
    &LSD1_Reserve_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_LSD1_Reserve_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_LSD1_Reserve_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    3, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "LSD2_Reserve_WF",
#endif
    &Com_PduData_ID1_RX[7], /* ptr */
    &LSD2_Reserve_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_LSD2_Reserve_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_LSD2_Reserve_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    4, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Window_Indication_Lamp_WF",
#endif
    &Com_PduData_ID1_RX[7], /* ptr */
    &Window_Indication_Lamp_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Window_Indication_Lamp_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Window_Indication_Lamp_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    5, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "IDM_COMP_ReqStatus",
#endif
    &Com_PduData_ID1_RX[7], /* ptr */
    &IDM_COMP_ReqStatus_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_IDM_COMP_ReqStatus, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_IDM_COMP_ReqStatus, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    6, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "F_FOG_RlyCoil_Ctrl_WF",
#endif
    &Com_PduData_ID1_RX[7], /* ptr */
    &F_FOG_RlyCoil_Ctrl_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_F_FOG_RlyCoil_Ctrl_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_F_FOG_RlyCoil_Ctrl_WF, /* HandleId */
    COM_CAN1_ID1_RX, /* PduId */
    7, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "POS_RlyCoil_Ctrl_WF",
#endif
    &Com_PduData_ID2_RX[0], /* ptr */
    &POS_RlyCoil_Ctrl_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_POS_RlyCoil_Ctrl_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_POS_RlyCoil_Ctrl_WF, /* HandleId */
    COM_CAN1_ID2_RX, /* PduId */
    0, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "LB_RlyCoil_Ctrl_WF",
#endif
    &Com_PduData_ID2_RX[0], /* ptr */
    &LB_RlyCoil_Ctrl_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_LB_RlyCoil_Ctrl_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_LB_RlyCoil_Ctrl_WF, /* HandleId */
    COM_CAN1_ID2_RX, /* PduId */
    1, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "HB_RlyCoil_Ctrl_WF",
#endif
    &Com_PduData_ID2_RX[0], /* ptr */
    &HB_RlyCoil_Ctrl_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_HB_RlyCoil_Ctrl_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_HB_RlyCoil_Ctrl_WF, /* HandleId */
    COM_CAN1_ID2_RX, /* PduId */
    2, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "FL_Wind_Up_RlyCoil_Ctrl_WF",
#endif
    &Com_PduData_ID2_RX[0], /* ptr */
    &FL_Wind_Up_RlyCoil_Ctrl_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_FL_Wind_Up_RlyCoil_Ctrl_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_FL_Wind_Up_RlyCoil_Ctrl_WF, /* HandleId */
    COM_CAN1_ID2_RX, /* PduId */
    3, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "FL_Wind_Down_RlyCoil_Ctrl_WF",
#endif
    &Com_PduData_ID2_RX[0], /* ptr */
    &FL_Wind_Down_RlyCoil_Ctrl_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_FL_Wind_Down_RlyCoil_Ctrl_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_FL_Wind_Down_RlyCoil_Ctrl_WF, /* HandleId */
    COM_CAN1_ID2_RX, /* PduId */
    4, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "FR_Wind_Up_RlyCoil_Ctrl_WF",
#endif
    &Com_PduData_ID2_RX[0], /* ptr */
    &FR_Wind_Up_RlyCoil_Ctrl_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_FR_Wind_Up_RlyCoil_Ctrl_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_FR_Wind_Up_RlyCoil_Ctrl_WF, /* HandleId */
    COM_CAN1_ID2_RX, /* PduId */
    5, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "FR_Wind_Down_RlyCoil_Ctrl_WF",
#endif
    &Com_PduData_ID2_RX[0], /* ptr */
    &FR_Wind_Down_RlyCoil_Ctrl_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_FR_Wind_Down_RlyCoil_Ctrl_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_FR_Wind_Down_RlyCoil_Ctrl_WF, /* HandleId */
    COM_CAN1_ID2_RX, /* PduId */
    6, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "RL_Wind_Up_RlyCoil_Ctrl_WF",
#endif
    &Com_PduData_ID2_RX[0], /* ptr */
    &RL_Wind_Up_RlyCoil_Ctrl_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_RL_Wind_Up_RlyCoil_Ctrl_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_RL_Wind_Up_RlyCoil_Ctrl_WF, /* HandleId */
    COM_CAN1_ID2_RX, /* PduId */
    7, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "RL_Wind_Down_RlyCoil_Ctrl_WF",
#endif
    &Com_PduData_ID2_RX[1], /* ptr */
    &RL_Wind_Down_RlyCoil_Ctrl_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_RL_Wind_Down_RlyCoil_Ctrl_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_RL_Wind_Down_RlyCoil_Ctrl_WF, /* HandleId */
    COM_CAN1_ID2_RX, /* PduId */
    0, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "RR_Wind_Up_RlyCoil_Ctrl_WF",
#endif
    &Com_PduData_ID2_RX[1], /* ptr */
    &RR_Wind_Up_RlyCoil_Ctrl_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_RR_Wind_Up_RlyCoil_Ctrl_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_RR_Wind_Up_RlyCoil_Ctrl_WF, /* HandleId */
    COM_CAN1_ID2_RX, /* PduId */
    1, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "RR_Wind_Down_RlyCoil_Ctrl_WF",
#endif
    &Com_PduData_ID2_RX[1], /* ptr */
    &RR_Wind_Down_RlyCoil_Ctrl_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_RR_Wind_Down_RlyCoil_Ctrl_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_RR_Wind_Down_RlyCoil_Ctrl_WF, /* HandleId */
    COM_CAN1_ID2_RX, /* PduId */
    2, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Center_Unlock_RlyCoil_Ctrl_WF",
#endif
    &Com_PduData_ID2_RX[1], /* ptr */
    &Center_Unlock_RlyCoil_Ctrl_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Center_Unlock_RlyCoil_Ctrl_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Center_Unlock_RlyCoil_Ctrl_WF, /* HandleId */
    COM_CAN1_ID2_RX, /* PduId */
    3, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Center_Lock_RlyCoil_Ctrl_WF",
#endif
    &Com_PduData_ID2_RX[1], /* ptr */
    &Center_Lock_RlyCoil_Ctrl_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Center_Lock_RlyCoil_Ctrl_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Center_Lock_RlyCoil_Ctrl_WF, /* HandleId */
    COM_CAN1_ID2_RX, /* PduId */
    4, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Mirror_Heat_RlyCoil_Ctrl_WF",
#endif
    &Com_PduData_ID2_RX[1], /* ptr */
    &Mirror_Heat_RlyCoil_Ctrl_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Mirror_Heat_RlyCoil_Ctrl_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Mirror_Heat_RlyCoil_Ctrl_WF, /* HandleId */
    COM_CAN1_ID2_RX, /* PduId */
    5, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Horn_SW_WF",
#endif
    &Com_PduData_ID2_RX[1], /* ptr */
    &Horn_SW_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Horn_SW_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Horn_SW_WF, /* HandleId */
    COM_CAN1_ID2_RX, /* PduId */
    6, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "FL_Wind_Gnd_Ctrl_WF",
#endif
    &Com_PduData_ID2_RX[1], /* ptr */
    &FL_Wind_Gnd_Ctrl_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_FL_Wind_Gnd_Ctrl_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_FL_Wind_Gnd_Ctrl_WF, /* HandleId */
    COM_CAN1_ID2_RX, /* PduId */
    7, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "FR_Wind_Gnd_Ctrl_WF",
#endif
    &Com_PduData_ID2_RX[2], /* ptr */
    &FR_Wind_Gnd_Ctrl_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_FR_Wind_Gnd_Ctrl_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_FR_Wind_Gnd_Ctrl_WF, /* HandleId */
    COM_CAN1_ID2_RX, /* PduId */
    0, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "RL_Wind_Gnd_Ctrl_WF",
#endif
    &Com_PduData_ID2_RX[2], /* ptr */
    &RL_Wind_Gnd_Ctrl_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_RL_Wind_Gnd_Ctrl_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_RL_Wind_Gnd_Ctrl_WF, /* HandleId */
    COM_CAN1_ID2_RX, /* PduId */
    1, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "RR_Wind_Gnd_Ctrl_WF",
#endif
    &Com_PduData_ID2_RX[2], /* ptr */
    &RR_Wind_Gnd_Ctrl_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_RR_Wind_Gnd_Ctrl_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_RR_Wind_Gnd_Ctrl_WF, /* HandleId */
    COM_CAN1_ID2_RX, /* PduId */
    2, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "LSD_SSB_LED3_WF",
#endif
    &Com_PduData_ID2_RX[2], /* ptr */
    &LSD_SSB_LED3_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_LSD_SSB_LED3_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_LSD_SSB_LED3_WF, /* HandleId */
    COM_CAN1_ID2_RX, /* PduId */
    3, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "LSD_SSB_LED2_WF",
#endif
    &Com_PduData_ID2_RX[2], /* ptr */
    &LSD_SSB_LED2_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_LSD_SSB_LED2_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_LSD_SSB_LED2_WF, /* HandleId */
    COM_CAN1_ID2_RX, /* PduId */
    4, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "LSD_SSB_LED1_WF",
#endif
    &Com_PduData_ID2_RX[2], /* ptr */
    &LSD_SSB_LED1_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_LSD_SSB_LED1_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_LSD_SSB_LED1_WF, /* HandleId */
    COM_CAN1_ID2_RX, /* PduId */
    5, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Condensing_Fan_Low_Ctrl_WF",
#endif
    &Com_PduData_ID2_RX[2], /* ptr */
    &Condensing_Fan_Low_Ctrl_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Condensing_Fan_Low_Ctrl_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Condensing_Fan_Low_Ctrl_WF, /* HandleId */
    COM_CAN1_ID2_RX, /* PduId */
    6, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Condensing_Fan_High_Ctrl_WF",
#endif
    &Com_PduData_ID2_RX[2], /* ptr */
    &Condensing_Fan_High_Ctrl_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Condensing_Fan_High_Ctrl_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Condensing_Fan_High_Ctrl_WF, /* HandleId */
    COM_CAN1_ID2_RX, /* PduId */
    7, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Int_Ext_Motor_Inc_WF",
#endif
    &Com_PduData_ID2_RX[3], /* ptr */
    &Int_Ext_Motor_Inc_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Int_Ext_Motor_Inc_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Int_Ext_Motor_Inc_WF, /* HandleId */
    COM_CAN1_ID2_RX, /* PduId */
    0, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Int_Ext_Motor_Dec_WF",
#endif
    &Com_PduData_ID2_RX[3], /* ptr */
    &Int_Ext_Motor_Dec_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Int_Ext_Motor_Dec_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Int_Ext_Motor_Dec_WF, /* HandleId */
    COM_CAN1_ID2_RX, /* PduId */
    1, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Cold_Heat_Motor_Inc_WF",
#endif
    &Com_PduData_ID2_RX[3], /* ptr */
    &Cold_Heat_Motor_Inc_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Cold_Heat_Motor_Inc_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Cold_Heat_Motor_Inc_WF, /* HandleId */
    COM_CAN1_ID2_RX, /* PduId */
    2, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Cold_Heat_Motor_Dec_WF",
#endif
    &Com_PduData_ID2_RX[3], /* ptr */
    &Cold_Heat_Motor_Dec_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Cold_Heat_Motor_Dec_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Cold_Heat_Motor_Dec_WF, /* HandleId */
    COM_CAN1_ID2_RX, /* PduId */
    3, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Mode_Motor_Inc_WF",
#endif
    &Com_PduData_ID2_RX[3], /* ptr */
    &Mode_Motor_Inc_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Mode_Motor_Inc_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Mode_Motor_Inc_WF, /* HandleId */
    COM_CAN1_ID2_RX, /* PduId */
    4, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Mode_MotoR_Dec_WF",
#endif
    &Com_PduData_ID2_RX[3], /* ptr */
    &Mode_MotoR_Dec_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Mode_MotoR_Dec_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Mode_MotoR_Dec_WF, /* HandleId */
    COM_CAN1_ID2_RX, /* PduId */
    5, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "IDM_LPOWER",
#endif
    &Com_PduData_ID2_RX[3], /* ptr */
    &IDM_LPOWER_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_IDM_LPOWER, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_IDM_LPOWER, /* HandleId */
    COM_CAN1_ID2_RX, /* PduId */
    6, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "FL_Gnd_Ctrl_WF",
#endif
    &Com_PduData_ID2_RX[4], /* ptr */
    &FL_Gnd_Ctrl_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_FL_Gnd_Ctrl_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_FL_Gnd_Ctrl_WF, /* HandleId */
    COM_CAN1_ID2_RX, /* PduId */
    0, /* BitPosition */
    12, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT16, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "FR_Gnd_Ctrl_WF",
#endif
    &Com_PduData_ID2_RX[5], /* ptr */
    &FR_Gnd_Ctrl_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_FR_Gnd_Ctrl_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_FR_Gnd_Ctrl_WF, /* HandleId */
    COM_CAN1_ID2_RX, /* PduId */
    4, /* BitPosition */
    12, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT16, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "RL_Wind_Samp_WF",
#endif
    &Com_PduData_ID3_RX[0], /* ptr */
    &RL_Wind_Samp_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_RL_Wind_Samp_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_RL_Wind_Samp_WF, /* HandleId */
    COM_CAN1_ID3_RX, /* PduId */
    0, /* BitPosition */
    12, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT16, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "RR_Wind_Samp_WF",
#endif
    &Com_PduData_ID3_RX[1], /* ptr */
    &RR_Wind_Samp_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_RR_Wind_Samp_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_RR_Wind_Samp_WF, /* HandleId */
    COM_CAN1_ID3_RX, /* PduId */
    4, /* BitPosition */
    12, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT16, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Blower_Analog_Out_WF",
#endif
    &Com_PduData_ID3_RX[3], /* ptr */
    &Blower_Analog_Out_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Blower_Analog_Out_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Blower_Analog_Out_WF, /* HandleId */
    COM_CAN1_ID3_RX, /* PduId */
    0, /* BitPosition */
    12, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT16, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Cold_Heat_Motor_Fb_WF",
#endif
    &Com_PduData_ID3_RX[4], /* ptr */
    &Cold_Heat_Motor_Fb_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Cold_Heat_Motor_Fb_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Cold_Heat_Motor_Fb_WF, /* HandleId */
    COM_CAN1_ID3_RX, /* PduId */
    4, /* BitPosition */
    12, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT16, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "Mode_MotoR_WF",
#endif
    &Com_PduData_ID3_RX[6], /* ptr */
    &Mode_MotoR_WF_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_Mode_MotoR_WF, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_Mode_MotoR_WF, /* HandleId */
    COM_CAN1_ID3_RX, /* PduId */
    0, /* BitPosition */
    12, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT16, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "ControlByte",
#endif
    &Com_PduData_TP_CM_RX[0], /* ptr */
    &ControlByte_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_ControlByte, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_ControlByte, /* HandleId */
    COM_CAN1_TP_CM_RX, /* PduId */
    0, /* BitPosition */
    8, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "TotalNumberOfBbytes",
#endif
    &Com_PduData_TP_CM_RX[1], /* ptr */
    &TotalNumberOfBbytes_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_TotalNumberOfBbytes, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_TotalNumberOfBbytes, /* HandleId */
    COM_CAN1_TP_CM_RX, /* PduId */
    0, /* BitPosition */
    16, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT16, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "TotalNumberOfPackets",
#endif
    &Com_PduData_TP_CM_RX[3], /* ptr */
    &TotalNumberOfPackets_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_TotalNumberOfPackets, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_TotalNumberOfPackets, /* HandleId */
    COM_CAN1_TP_CM_RX, /* PduId */
    0, /* BitPosition */
    8, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "ParameterGroupNumber",
#endif
    &Com_PduData_TP_CM_RX[5], /* ptr */
    &ParameterGroupNumber_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_ParameterGroupNumber, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_ParameterGroupNumber, /* HandleId */
    COM_CAN1_TP_CM_RX, /* PduId */
    0, /* BitPosition */
    24, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT32, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "SequenceNumber",
#endif
    &Com_PduData_TP_DT_RX[0], /* ptr */
    &SequenceNumber_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_SequenceNumber, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_SequenceNumber, /* HandleId */
    COM_CAN1_TP_DT_RX, /* PduId */
    0, /* BitPosition */
    8, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "TX_COUNTER",
#endif
    &Com_PduData_CANTEST_TX_TEST[0], /* ptr */
    &TX_COUNTER_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_TX_COUNTER, /* txConfig */
#endif
    COM_SID_TX_COUNTER, /* HandleId */
    COM_CANTEST_TX_TEST, /* PduId */
    0, /* BitPosition */
    8, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "TX_FLAG",
#endif
    &Com_PduData_CANTEST_TX_TEST[1], /* ptr */
    &TX_FLAG_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_TX_FLAG, /* txConfig */
#endif
    COM_SID_TX_FLAG, /* HandleId */
    COM_CANTEST_TX_TEST, /* PduId */
    1, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "TX_LEVEL",
#endif
    &Com_PduData_CANTEST_TX_TEST[2], /* ptr */
    &TX_LEVEL_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_TX_LEVEL, /* txConfig */
#endif
    COM_SID_TX_LEVEL, /* HandleId */
    COM_CANTEST_TX_TEST, /* PduId */
    0, /* BitPosition */
    12, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT16, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "LedRunMode",
#endif
    &Com_PduData_CANTEST_TX_TEST[1], /* ptr */
    &LedRunMode_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_LedRunMode, /* txConfig */
#endif
    COM_SID_LedRunMode, /* HandleId */
    COM_CANTEST_TX_TEST, /* PduId */
    2, /* BitPosition */
    2, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "LedOut",
#endif
    &Com_PduData_CANTEST_TX_TEST[1], /* ptr */
    &LedOut_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_LedOut, /* txConfig */
#endif
    COM_SID_LedOut, /* HandleId */
    COM_CANTEST_TX_TEST, /* PduId */
    4, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "LedBlinkPhase",
#endif
    &Com_PduData_CANTEST_TX_TEST[1], /* ptr */
    &LedBlinkPhase_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_LedBlinkPhase, /* txConfig */
#endif
    COM_SID_LedBlinkPhase, /* HandleId */
    COM_CANTEST_TX_TEST, /* PduId */
    5, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "LedFaultTimeout",
#endif
    &Com_PduData_CANTEST_TX_TEST[1], /* ptr */
    &LedFaultTimeout_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_LedFaultTimeout, /* txConfig */
#endif
    COM_SID_LedFaultTimeout, /* HandleId */
    COM_CANTEST_TX_TEST, /* PduId */
    6, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "LedFaultCmd",
#endif
    &Com_PduData_CANTEST_TX_TEST[1], /* ptr */
    &LedFaultCmd_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    NULL, /* rxConfig */
    &Com_SignalTxConfig_LedFaultCmd, /* txConfig */
#endif
    COM_SID_LedFaultCmd, /* HandleId */
    COM_CANTEST_TX_TEST, /* PduId */
    7, /* BitPosition */
    1, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "RX_COUNTER",
#endif
    &Com_PduData_CANTEST_RX_TEST[0], /* ptr */
    &RX_COUNTER_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_RX_COUNTER, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_RX_COUNTER, /* HandleId */
    COM_CANTEST_RX_TEST, /* PduId */
    0, /* BitPosition */
    8, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT8, /* type */
    COM_LITTLE_ENDIAN, /* Endianness */
    FALSE,
  },
  {
#ifdef USE_SHELL
    "RX_TEMP",
#endif
    &Com_PduData_CANTEST_RX_TEST[2], /* ptr */
    &RX_TEMP_InitialValue, /* initPtr */
#ifdef COM_USE_SIGNAL_CONFIG
    &Com_SignalRxConfig_RX_TEMP, /* rxConfig */
    NULL, /* txConfig */
#endif
    COM_SID_RX_TEMP, /* HandleId */
    COM_CANTEST_RX_TEST, /* PduId */
    7, /* BitPosition */
    16, /* BitSize */
#ifdef COM_USE_SIGNAL_UPDATE_BIT
    COM_UPDATE_BIT_NOT_USED, /* UpdateBit */
#endif
    COM_UINT16, /* type */
    COM_BIG_ENDIAN, /* Endianness */
    FALSE,
  },
};

static const Com_SignalConfigType* Com_IPduSignals_BCM_LCSF_TX[] = {
  &Com_SignalConfigs[COM_SID_BCM_LowBeamSts],
  &Com_SignalConfigs[COM_SID_BCM_HighBeamSts],
  &Com_SignalConfigs[COM_SID_BCM_FrontFogSts],
  &Com_SignalConfigs[COM_SID_BCM_TurnRLightSts],
  &Com_SignalConfigs[COM_SID_BCM_TurnLLightSts],
  &Com_SignalConfigs[COM_SID_BCM_DRLSts],
  &Com_SignalConfigs[COM_SID_BCM_PositionLightSts],
  &Com_SignalConfigs[COM_SID_BCM_RearFogSts],
  &Com_SignalConfigs[COM_SID_BackUpLightSt],
  &Com_SignalConfigs[COM_SID_BrakelightST],
  &Com_SignalConfigs[COM_SID_InteriorLampSt],
};

static const Com_SignalConfigType* Com_IPduSignals_BCM_Ctrl_TX[] = {
  &Com_SignalConfigs[COM_SID_BCM_PassWindowLcokSw],
  &Com_SignalConfigs[COM_SID_CentralLockSw],
  &Com_SignalConfigs[COM_SID_MRightFrontWinSw],
  &Com_SignalConfigs[COM_SID_MLeftFrontWinSw],
  &Com_SignalConfigs[COM_SID_RightFrontWinSw],
  &Com_SignalConfigs[COM_SID_MRightRearWinSw],
  &Com_SignalConfigs[COM_SID_MLeftRearWinSw],
  &Com_SignalConfigs[COM_SID_RightRearWinSw],
  &Com_SignalConfigs[COM_SID_LeftRearWinSw],
  &Com_SignalConfigs[COM_SID_BCM_Ctrl_TX_MechKeySt],
  &Com_SignalConfigs[COM_SID_LeftFrontWinSt],
  &Com_SignalConfigs[COM_SID_RightFrontWinSt],
  &Com_SignalConfigs[COM_SID_LeftRearWinSt],
  &Com_SignalConfigs[COM_SID_RightRearWinSt],
  &Com_SignalConfigs[COM_SID_DoorLockMotorState],
  &Com_SignalConfigs[COM_SID_RemoteDoorState],
  &Com_SignalConfigs[COM_SID_LeftFrontWinErrorSt],
  &Com_SignalConfigs[COM_SID_RightFrontWinErrorSt],
  &Com_SignalConfigs[COM_SID_LeftRearWinErrorSt],
  &Com_SignalConfigs[COM_SID_RightRearWinErrorSt],
};

static const Com_SignalConfigType* Com_IPduSignals_BCM_OEL_TX[] = {
  &Com_SignalConfigs[COM_SID_HazardSw],
  &Com_SignalConfigs[COM_SID_HazardSt],
};

static const Com_SignalConfigType* Com_IPduSignals_BCM_OWW_TX[] = {
  &Com_SignalConfigs[COM_SID_WiperSt],
};

static const Com_SignalConfigType* Com_IPduSignals_BCM_DoorCtrl_TX[] = {
  &Com_SignalConfigs[COM_SID_SKC_u8PEPSICUIndCnt_WF],
  &Com_SignalConfigs[COM_SID_PRM_u8PEPSICUIndCnt_WF],
  &Com_SignalConfigs[COM_SID_ATP_u8DrvLockRotor_WF],
  &Com_SignalConfigs[COM_SID_ESCL_u8AuthReqCnt_WF],
  &Com_SignalConfigs[COM_SID_BCM_OpenStatusofDdoor],
  &Com_SignalConfigs[COM_SID_BCM_OpenStatusofPdoor],
  &Com_SignalConfigs[COM_SID_BCM_OpenStatusofLeftReardoor],
  &Com_SignalConfigs[COM_SID_BCM_OpenStatusofRightReardoor],
  &Com_SignalConfigs[COM_SID_BASE_u8AuthResultCnt_WF],
  &Com_SignalConfigs[COM_SID_BSW_TPMS_FrameCnt_WF],
  &Com_SignalConfigs[COM_SID_PAM_u8SleepFlag_WF],
  &Com_SignalConfigs[COM_SID_ATP_u8PasLockRotor_WF],
  &Com_SignalConfigs[COM_SID_FEE_APPWriteIdleFlag_WF],
  &Com_SignalConfigs[COM_SID_FEE_BOOTWriteIdleFlag_WF],
  &Com_SignalConfigs[COM_SID_WIN_u8DrvWinCmdCAN_WF],
  &Com_SignalConfigs[COM_SID_WIN_u8PasWinCmdCAN_WF],
  &Com_SignalConfigs[COM_SID_TUL_u8HonkingStyle_WF],
  &Com_SignalConfigs[COM_SID_DLC_u8LockSource_WF],
  &Com_SignalConfigs[COM_SID_HornRelaySt],
  &Com_SignalConfigs[COM_SID_BrakeLightWarning],
  &Com_SignalConfigs[COM_SID_LF_SendCounter_WF],
  &Com_SignalConfigs[COM_SID_LF_Commond_WF],
};

static const Com_SignalConfigType* Com_IPduSignals_BCM_DM1_TX[] = {
  &Com_SignalConfigs[COM_SID_DM1_MalfunctionIndicatorLampStatus],
  &Com_SignalConfigs[COM_SID_DM1_RedStopLampState],
  &Com_SignalConfigs[COM_SID_BCM_LeastByteofSPN],
  &Com_SignalConfigs[COM_SID_BCM_SecondByteofSPN],
  &Com_SignalConfigs[COM_SID_BCM_FMI],
  &Com_SignalConfigs[COM_SID_BCM_3MostBitofSPN],
  &Com_SignalConfigs[COM_SID_BCM_OC],
  &Com_SignalConfigs[COM_SID_BCM_CM],
};

static const Com_SignalConfigType* Com_IPduSignals_Crash_Notification_RX[] = {
  &Com_SignalConfigs[COM_SID_SRS_Crash_Type],
};

static const Com_SignalConfigType* Com_IPduSignals_AMB_Ambient_Conditions_RX[] = {
  &Com_SignalConfigs[COM_SID_AMB_BarometricPress],
  &Com_SignalConfigs[COM_SID_LFE1_AmbientAirTemp],
  &Com_SignalConfigs[COM_SID_LFE1_EngAirIntakeTemp],
};

static const Com_SignalConfigType* Com_IPduSignals_PEPS1_RX[] = {
  &Com_SignalConfigs[COM_SID_PEPsKeyInState],
  &Com_SignalConfigs[COM_SID_PEPS_PkeLockCmd],
  &Com_SignalConfigs[COM_SID_PEPS_PowerMode],
  &Com_SignalConfigs[COM_SID_PEPS_ESCLInhabitSt],
  &Com_SignalConfigs[COM_SID_PEPS_EmergencyST],
  &Com_SignalConfigs[COM_SID_PEPS_KeyAuthenticationSt_PEPS],
  &Com_SignalConfigs[COM_SID_ESCL_failure],
  &Com_SignalConfigs[COM_SID_PEPS_failure],
  &Com_SignalConfigs[COM_SID_Key_Not_Found],
  &Com_SignalConfigs[COM_SID_Key_Battery_Low],
  &Com_SignalConfigs[COM_SID_PEPS_PEPSICUInd],
  &Com_SignalConfigs[COM_SID_PEPsKeyInFeedback],
  &Com_SignalConfigs[COM_SID_ACC_FB],
  &Com_SignalConfigs[COM_SID_IGN1_FB],
  &Com_SignalConfigs[COM_SID_PEPsKeyOutFeedback],
  &Com_SignalConfigs[COM_SID_Alive_counter],
  &Com_SignalConfigs[COM_SID_PEPS1_RX_CRC],
};

static const Com_SignalConfigType* Com_IPduSignals_PEPS2_RX[] = {
  &Com_SignalConfigs[COM_SID_Key1_Inside_St],
  &Com_SignalConfigs[COM_SID_Key2_Inside_St],
  &Com_SignalConfigs[COM_SID_Key3_Inside_St],
  &Com_SignalConfigs[COM_SID_Key4_Inside_St],
  &Com_SignalConfigs[COM_SID_Key1_Inhibit_St],
  &Com_SignalConfigs[COM_SID_Key2_Inhibit_St],
  &Com_SignalConfigs[COM_SID_Key3_Inhibit_St],
  &Com_SignalConfigs[COM_SID_Key4_Inhibit_St],
  &Com_SignalConfigs[COM_SID_RKE_u8UnlockCounter_WF],
  &Com_SignalConfigs[COM_SID_RKE_u8SearchCounter_WF],
  &Com_SignalConfigs[COM_SID_KE_u8LockCounter_WF],
  &Com_SignalConfigs[COM_SID_PKE_Count_WF],
  &Com_SignalConfigs[COM_SID_WKUPFALG_WF],
  &Com_SignalConfigs[COM_SID_DLC_u8DrvPESts_WF],
  &Com_SignalConfigs[COM_SID_SSB_u8SWSts_WF],
  &Com_SignalConfigs[COM_SID_PKE_AuthResult_WF],
  &Com_SignalConfigs[COM_SID_FEE_DTCWriteIdleFlag_WF],
  &Com_SignalConfigs[COM_SID_PMM_u8PwrStsLoad_WF],
  &Com_SignalConfigs[COM_SID_SWK_u8NmSleepSt_WF],
  &Com_SignalConfigs[COM_SID_DLC_u8PasPESts_WF],
};

static const Com_SignalConfigType* Com_IPduSignals_PEPS_ESCLM_RX[] = {
  &Com_SignalConfigs[COM_SID_PEPS_SUB_ID],
  &Com_SignalConfigs[COM_SID_PEPS_AuthResp],
};

static const Com_SignalConfigType* Com_IPduSignals_ACL_RX[] = {
  &Com_SignalConfigs[COM_SID_ManufacturerCode],
};

static const Com_SignalConfigType* Com_IPduSignals_EOI_RX[] = {
  &Com_SignalConfigs[COM_SID_EngOperatingState],
};

static const Com_SignalConfigType* Com_IPduSignals_ETC2_RX[] = {
  &Com_SignalConfigs[COM_SID_TransCurrentGear],
};

static const Com_SignalConfigType* Com_IPduSignals_ESCL1_RX[] = {
  &Com_SignalConfigs[COM_SID_ESCL_St],
  &Com_SignalConfigs[COM_SID_ESCL_WarnSafety],
  &Com_SignalConfigs[COM_SID_ESCL_PromptRotateSteerWheel],
  &Com_SignalConfigs[COM_SID_AliveCounter],
  &Com_SignalConfigs[COM_SID_ESCL1_RX_CRC],
};

static const Com_SignalConfigType* Com_IPduSignals_ESCLM_PEPS_RX[] = {
  &Com_SignalConfigs[COM_SID_ESCL_SUB_ID],
  &Com_SignalConfigs[COM_SID_ESCL_AuthChallenge],
  &Com_SignalConfigs[COM_SID_ESCL_AuthResult],
};

static const Com_SignalConfigType* Com_IPduSignals_ESCL_NM_RX[] = {
  &Com_SignalConfigs[COM_SID_Destination_Address],
};

static const Com_SignalConfigType* Com_IPduSignals_DW_State_RX[] = {
  &Com_SignalConfigs[COM_SID_SecAlarm],
  &Com_SignalConfigs[COM_SID_ESCL_u8SleepFlag_NM_WF],
  &Com_SignalConfigs[COM_SID_WIN_u8SleepFlag_NM_WF],
  &Com_SignalConfigs[COM_SID_ACC_u8SleepFlag_NM_WF],
  &Com_SignalConfigs[COM_SID_RMH_u8SleepFlag_NM_WF],
  &Com_SignalConfigs[COM_SID_DLC_u8SleepFlag_NM_WF],
  &Com_SignalConfigs[COM_SID_SAC_u8SleepFlag_NM_WF],
  &Com_SignalConfigs[COM_SID_HORN_u8SleepFlag_NM_WF],
  &Com_SignalConfigs[COM_SID_TUL_u8SleepFlag_NM_WF],
  &Com_SignalConfigs[COM_SID_FMHL_u8SleepFlag_NM_WF],
  &Com_SignalConfigs[COM_SID_AHL_u8SleepFlag_NM_WF],
  &Com_SignalConfigs[COM_SID_POL_u8SleepFlag_NM_WF],
  &Com_SignalConfigs[COM_SID_LBL_u8SleepFlag_NM_WF],
  &Com_SignalConfigs[COM_SID_HBL_u8SleepFlag_NM_WF],
  &Com_SignalConfigs[COM_SID_FFL_u8SleepFlag_NM_WF],
  &Com_SignalConfigs[COM_SID_DW_State_RX_MechKeySt],
  &Com_SignalConfigs[COM_SID_RFL_u8SleepFlag_NM_WF],
  &Com_SignalConfigs[COM_SID_DRL_u8SleepFlag_NM_WF],
  &Com_SignalConfigs[COM_SID_BRL_u8SleepFlag_NM_WF],
  &Com_SignalConfigs[COM_SID_SLED_u8SleepFlag_WF],
  &Com_SignalConfigs[COM_SID_DML_u8LampSleepFlag_NM_WF],
  &Com_SignalConfigs[COM_SID_LOL_u8SleepFlag_NM_WF],
  &Com_SignalConfigs[COM_SID_WDIL_u8SleepFlag_NM_WF],
  &Com_SignalConfigs[COM_SID_SKC_u8SleepFlag_WF],
  &Com_SignalConfigs[COM_SID_DLC_u8UnlockSource_WF],
  &Com_SignalConfigs[COM_SID_ON_SW_WF],
  &Com_SignalConfigs[COM_SID_ST_SW_WF],
  &Com_SignalConfigs[COM_SID_ACC_SW_WF],
  &Com_SignalConfigs[COM_SID_Lighting_Sensor_WF],
  &Com_SignalConfigs[COM_SID_VehicleVoltage],
  &Com_SignalConfigs[COM_SID_Mirror_Heat_SW_WF],
  &Com_SignalConfigs[COM_SID_LOGO_SW_WF],
  &Com_SignalConfigs[COM_SID_Window_Inhibite_SW_WF],
  &Com_SignalConfigs[COM_SID_Key_IN_WF],
  &Com_SignalConfigs[COM_SID_Reserve1_SW_WF],
  &Com_SignalConfigs[COM_SID_Reserve5_SW_WF],
  &Com_SignalConfigs[COM_SID_FL_TL_LED_Fb_WF],
  &Com_SignalConfigs[COM_SID_FR_TL_LED_Fb_WF],
  &Com_SignalConfigs[COM_SID_Reserve2_SW_WF],
  &Com_SignalConfigs[COM_SID_Reserve3_SW_WF],
  &Com_SignalConfigs[COM_SID_Reserve4_SW_WF],
  &Com_SignalConfigs[COM_SID_DIL_Brake_WF],
  &Com_SignalConfigs[COM_SID_SSB_SW1_WF],
  &Com_SignalConfigs[COM_SID_DIH_SSB_SW2_WF],
  &Com_SignalConfigs[COM_SID_RDoor_SW_WF],
  &Com_SignalConfigs[COM_SID_LDoor_SW_WF],
};

static const Com_SignalConfigType* Com_IPduSignals_IC_MSG_RX[] = {
  &Com_SignalConfigs[COM_SID_DoorOpenSw],
};

static const Com_SignalConfigType* Com_IPduSignals_EEC1_Electronic_Engine_Controller_1_RX[] = {
  &Com_SignalConfigs[COM_SID_EEC1_EngTorqueMode],
  &Com_SignalConfigs[COM_SID_EEC1_ActlEngPrcntTrqueHighResolution],
  &Com_SignalConfigs[COM_SID_EEC1_DriversDemandPercentTorque],
  &Com_SignalConfigs[COM_SID_EEC1_ActualEngPercentTorque],
  &Com_SignalConfigs[COM_SID_EEC1_EngSpeed],
  &Com_SignalConfigs[COM_SID_EEC1_ECU_SA],
  &Com_SignalConfigs[COM_SID_EEC1_EngDemandPercentTorque],
};

static const Com_SignalConfigType* Com_IPduSignals_CCVS_RX[] = {
  &Com_SignalConfigs[COM_SID_ParkingBrakeSwitch],
};

static const Com_SignalConfigType* Com_IPduSignals_VCU_4_RX[] = {
  &Com_SignalConfigs[COM_SID_VBUS_VCU4_N_VehicleSpeed],
  &Com_SignalConfigs[COM_SID_VBUS_VCU4_St_Gears],
  &Com_SignalConfigs[COM_SID_VBUS_VCU4_St_Ready],
  &Com_SignalConfigs[COM_SID_VBUS_VCU4_St_BrakeSta],
};

static const Com_SignalConfigType* Com_IPduSignals_TCO1_RX[] = {
  &Com_SignalConfigs[COM_SID_TachographVehicleSpeed],
};

static const Com_SignalConfigType* Com_IPduSignals_TireCondition_RX[] = {
  &Com_SignalConfigs[COM_SID_TireLocation],
  &Com_SignalConfigs[COM_SID_TirePressure],
  &Com_SignalConfigs[COM_SID_TireTemperature],
  &Com_SignalConfigs[COM_SID_WheelSensorStatus],
  &Com_SignalConfigs[COM_SID_TireStatus],
  &Com_SignalConfigs[COM_SID_Tire_Sensor_Electrical_Fault],
  &Com_SignalConfigs[COM_SID_Tire_Air_Leakage_Rate],
  &Com_SignalConfigs[COM_SID_TirePressureThresholdDetection],
};

static const Com_SignalConfigType* Com_IPduSignals_DM1_TPMS_RX[] = {
  &Com_SignalConfigs[COM_SID_DM1_TPMS_ProtectLampStatus],
  &Com_SignalConfigs[COM_SID_DM1_TPMS_AmberWarningLampStatus],
  &Com_SignalConfigs[COM_SID_DM1_TPMS_RedStopLampState],
  &Com_SignalConfigs[COM_SID_LeastByteofSPN],
  &Com_SignalConfigs[COM_SID_SecondByteofSPN],
  &Com_SignalConfigs[COM_SID_FMI],
  &Com_SignalConfigs[COM_SID__3MostBitofSPN],
  &Com_SignalConfigs[COM_SID_OC],
  &Com_SignalConfigs[COM_SID_CM],
};

static const Com_SignalConfigType* Com_IPduSignals_EBC1_Electronic_Brake_Controller_1_RX[] = {
  &Com_SignalConfigs[COM_SID_EBC1_ASREngCtrlActive],
  &Com_SignalConfigs[COM_SID_EBC1_ASRBrakeCtrlActive],
  &Com_SignalConfigs[COM_SID_EBC1_AntiLockBrakingActive],
  &Com_SignalConfigs[COM_SID_EBC1_EBSBrakeSwitch],
  &Com_SignalConfigs[COM_SID_EBC1_Brake_Pedal_Position],
  &Com_SignalConfigs[COM_SID_EBC1_ABS_OffRoad_switch],
  &Com_SignalConfigs[COM_SID_EBC1_ASR_OffRoad_switch],
  &Com_SignalConfigs[COM_SID_EBC1_ASR_HillHolder_switch],
  &Com_SignalConfigs[COM_SID_EBC1_Traction_ControlOverride_switch],
  &Com_SignalConfigs[COM_SID_ABS_Fully_Operational],
  &Com_SignalConfigs[COM_SID_EBC1_EBSRedWarningSignal],
  &Com_SignalConfigs[COM_SID_EBC1_ABS_EBSAmberWarningSignal],
  &Com_SignalConfigs[COM_SID_EBC1_ATC_ASRInformationSignal],
};

static const Com_SignalConfigType* Com_IPduSignals_EBC5_Electronic_Brake_Controller_5_RX[] = {
  &Com_SignalConfigs[COM_SID_Foundation_Brake_Use],
  &Com_SignalConfigs[COM_SID_XBR_System_State],
  &Com_SignalConfigs[COM_SID_XBR_Active_Control_Mode],
  &Com_SignalConfigs[COM_SID_XBR_Acceleration_Limit],
  &Com_SignalConfigs[COM_SID_Parking_Brake_Actuator_Fully_Activated],
  &Com_SignalConfigs[COM_SID_Emergency_Braking_Active],
};

static const Com_SignalConfigType* Com_IPduSignals_DLCC1_Direct_Lamp_Control_Command_1_RX[] = {
  &Com_SignalConfigs[COM_SID_DLCC1_EngAmberWarningLampCmd],
  &Com_SignalConfigs[COM_SID_DLCC1_EngRedStopLampCmd],
  &Com_SignalConfigs[COM_SID_DLCC1_OBDMalfunctionLampCmd],
  &Com_SignalConfigs[COM_SID_DLCC1_EngBrakeActiveLampCmd],
  &Com_SignalConfigs[COM_SID_DLCC1_EngOilPressLowLampCmd],
  &Com_SignalConfigs[COM_SID_DLCC1_EngCoolantTempHighLampCmd],
  &Com_SignalConfigs[COM_SID_DLCC1_EngCoolantLevelLowLampCmd],
};

static const Com_SignalConfigType* Com_IPduSignals_CCVS1_Cruise_Control_Vehicle_Speed_1_RX[] = {
  &Com_SignalConfigs[COM_SID_CCVS1_TwoSpeedAxleSwitch],
  &Com_SignalConfigs[COM_SID_CCVS1_ParkingBrakeSwitch],
  &Com_SignalConfigs[COM_SID_CCVS1_WheelBasedVehicleSpeed],
  &Com_SignalConfigs[COM_SID_CCVS1_CruiseCtrlActive],
  &Com_SignalConfigs[COM_SID_CCVS1_CruiseCtrlEnableSwitch],
  &Com_SignalConfigs[COM_SID_CCVS1_BrakeSwitch],
  &Com_SignalConfigs[COM_SID_CCVS1_ClutchSwitch],
  &Com_SignalConfigs[COM_SID_CCVS1_CruiseCtrlSetSwitch],
  &Com_SignalConfigs[COM_SID_CCVS1_CruiseCtrlCoastSwitch],
  &Com_SignalConfigs[COM_SID_CCVS1_CruiseCtrlResumeSwitch],
  &Com_SignalConfigs[COM_SID_CCVS1_CruiseCtrlAccelerateSwitch],
  &Com_SignalConfigs[COM_SID_CCVS1_CruiseCtrlSetSpeed],
  &Com_SignalConfigs[COM_SID_CCVS1_PTOGovernorState],
  &Com_SignalConfigs[COM_SID_CCVS1_CruiseCtrlStates],
};

static const Com_SignalConfigType* Com_IPduSignals_VDC1_Vehicle_Dynamic_Stability_Control_1_RX[] = {
  &Com_SignalConfigs[COM_SID_VDC1_VDCInformationSignal],
  &Com_SignalConfigs[COM_SID_VDC1_VDCFullyOperational],
  &Com_SignalConfigs[COM_SID_VDC1_VDC_brake_light_request],
  &Com_SignalConfigs[COM_SID_VDC1_ROPEngCtrlActive],
  &Com_SignalConfigs[COM_SID_VDC1_ROPBrakeCtrlActive],
  &Com_SignalConfigs[COM_SID_VDC1_YCEngCtrlActive],
  &Com_SignalConfigs[COM_SID_VDC1_YCBrakeCtrlActive],
};

static const Com_SignalConfigType* Com_IPduSignals_ERC1_RX[] = {
  &Com_SignalConfigs[COM_SID_ERC1_RX_ERC1_ActualRetarderPercentTorque],
};

static const Com_SignalConfigType* Com_IPduSignals_ERC3_RX[] = {
  &Com_SignalConfigs[COM_SID_ERC3_RX_ERC1_ActualRetarderPercentTorque],
};

static const Com_SignalConfigType* Com_IPduSignals_ETC5_RX[] = {
  &Com_SignalConfigs[COM_SID_TransReverseDirectionSw],
  &Com_SignalConfigs[COM_SID_TransNeutralSwitch],
};

static const Com_SignalConfigType* Com_IPduSignals_EEC3_RX[] = {
  &Com_SignalConfigs[COM_SID_ECC_Work_Switch],
  &Com_SignalConfigs[COM_SID_ECC_COMP_ReqSwitch],
  &Com_SignalConfigs[COM_SID_ECC_WPTC_ReqSwitch],
  &Com_SignalConfigs[COM_SID_REC_Switch],
  &Com_SignalConfigs[COM_SID_Fan_Gear_Switch],
  &Com_SignalConfigs[COM_SID_HVAC_MODE_Switch],
  &Com_SignalConfigs[COM_SID_HVAC_SET_Temp_Switch],
  &Com_SignalConfigs[COM_SID_One_click_defrosting],
};

static const Com_SignalConfigType* Com_IPduSignals_ECC2_RX[] = {
  &Com_SignalConfigs[COM_SID_ECC_Work_Status],
  &Com_SignalConfigs[COM_SID_ECC_COMP_ReqStatus],
  &Com_SignalConfigs[COM_SID_REC_Status],
  &Com_SignalConfigs[COM_SID_Fan_Gear],
  &Com_SignalConfigs[COM_SID_HVAC_MODE_Status],
  &Com_SignalConfigs[COM_SID_HVAC_SET_Temp],
  &Com_SignalConfigs[COM_SID_EVAP_Temp],
  &Com_SignalConfigs[COM_SID_MID_PRESS_Status],
  &Com_SignalConfigs[COM_SID_H_L_PRESS_Sta],
  &Com_SignalConfigs[COM_SID_One_click_defrosting_Status],
};

static const Com_SignalConfigType* Com_IPduSignals_ID1_RX[] = {
  &Com_SignalConfigs[COM_SID_N_Shift_WF],
  &Com_SignalConfigs[COM_SID_AI_Clutch_WF],
  &Com_SignalConfigs[COM_SID_StartupSts_Fb_WF],
  &Com_SignalConfigs[COM_SID_High_low_Voltage_SW_WF],
  &Com_SignalConfigs[COM_SID_AC_DOH_WF],
  &Com_SignalConfigs[COM_SID_D1_Diag_WF],
  &Com_SignalConfigs[COM_SID_D2_Diag_WF],
  &Com_SignalConfigs[COM_SID_D3_Diag_WF],
  &Com_SignalConfigs[COM_SID_D4_Diag_WF],
  &Com_SignalConfigs[COM_SID_D5_Diag_WF],
  &Com_SignalConfigs[COM_SID_D6_Diag_WF],
  &Com_SignalConfigs[COM_SID_D7_Diag_WF],
  &Com_SignalConfigs[COM_SID_D8_Diag_WF],
  &Com_SignalConfigs[COM_SID_D9_Diag_WF],
  &Com_SignalConfigs[COM_SID_D10_Diag_WF],
  &Com_SignalConfigs[COM_SID_D11_Diag_WF],
  &Com_SignalConfigs[COM_SID_D12_Diag_WF],
  &Com_SignalConfigs[COM_SID_D13_Diag_WF],
  &Com_SignalConfigs[COM_SID_D14_Diag_WF],
  &Com_SignalConfigs[COM_SID_D15_Diag_WF],
  &Com_SignalConfigs[COM_SID_D16_Diag_WF],
  &Com_SignalConfigs[COM_SID_D17_Diag_WF],
  &Com_SignalConfigs[COM_SID_D18_Diag_WF],
  &Com_SignalConfigs[COM_SID_D19_Diag_WF],
  &Com_SignalConfigs[COM_SID_D20_Diag_WF],
  &Com_SignalConfigs[COM_SID_D21_Diag_WF],
  &Com_SignalConfigs[COM_SID_D22_Diag_WF],
  &Com_SignalConfigs[COM_SID_D23_Diag_WF],
  &Com_SignalConfigs[COM_SID_D24_Diag_WF],
  &Com_SignalConfigs[COM_SID_D25_Diag_WF],
  &Com_SignalConfigs[COM_SID_D26_Diag_WF],
  &Com_SignalConfigs[COM_SID_D27_Diag_WF],
  &Com_SignalConfigs[COM_SID_D28_Diag_WF],
  &Com_SignalConfigs[COM_SID_D29_Diag_WF],
  &Com_SignalConfigs[COM_SID_D30_Diag_WF],
  &Com_SignalConfigs[COM_SID_D31_Diag_WF],
  &Com_SignalConfigs[COM_SID_D32_Diag_WF],
  &Com_SignalConfigs[COM_SID_D33_Diag_WF],
  &Com_SignalConfigs[COM_SID_D34_Diag_WF],
  &Com_SignalConfigs[COM_SID_D35_Diag_WF],
  &Com_SignalConfigs[COM_SID_D36_Diag_WF],
  &Com_SignalConfigs[COM_SID_D38_Diag_WF],
  &Com_SignalConfigs[COM_SID_D39_Diag_WF],
  &Com_SignalConfigs[COM_SID_D40_Diag_WF],
  &Com_SignalConfigs[COM_SID_D41_Diag_WF],
  &Com_SignalConfigs[COM_SID_Wiper_H_RlyCoil_Ctrl_WF],
  &Com_SignalConfigs[COM_SID_Blower_RlyCoil_Ctrl_WF],
  &Com_SignalConfigs[COM_SID_IG_Fb_WF],
  &Com_SignalConfigs[COM_SID_IG_RlyCoil_Ctrl_WF],
  &Com_SignalConfigs[COM_SID_ACC_Fb_WF],
  &Com_SignalConfigs[COM_SID_ACC_RlyCoil_Ctrl_WF],
  &Com_SignalConfigs[COM_SID_Horn_RlyCoil_Ctrl_WF],
  &Com_SignalConfigs[COM_SID_Wiper_Power_RlyCoil_Ctrl_WF],
  &Com_SignalConfigs[COM_SID_Startup_SIG_WF],
  &Com_SignalConfigs[COM_SID_F_LOGO_Lamp_WF],
  &Com_SignalConfigs[COM_SID_Washer_Motor_WF],
  &Com_SignalConfigs[COM_SID_HSD1_Reserve_WF],
  &Com_SignalConfigs[COM_SID_Battery_Saver_WF],
  &Com_SignalConfigs[COM_SID_Dome_Lamp_WF],
  &Com_SignalConfigs[COM_SID_LSD1_Reserve_WF],
  &Com_SignalConfigs[COM_SID_LSD2_Reserve_WF],
  &Com_SignalConfigs[COM_SID_Window_Indication_Lamp_WF],
  &Com_SignalConfigs[COM_SID_IDM_COMP_ReqStatus],
  &Com_SignalConfigs[COM_SID_F_FOG_RlyCoil_Ctrl_WF],
};

static const Com_SignalConfigType* Com_IPduSignals_ID2_RX[] = {
  &Com_SignalConfigs[COM_SID_POS_RlyCoil_Ctrl_WF],
  &Com_SignalConfigs[COM_SID_LB_RlyCoil_Ctrl_WF],
  &Com_SignalConfigs[COM_SID_HB_RlyCoil_Ctrl_WF],
  &Com_SignalConfigs[COM_SID_FL_Wind_Up_RlyCoil_Ctrl_WF],
  &Com_SignalConfigs[COM_SID_FL_Wind_Down_RlyCoil_Ctrl_WF],
  &Com_SignalConfigs[COM_SID_FR_Wind_Up_RlyCoil_Ctrl_WF],
  &Com_SignalConfigs[COM_SID_FR_Wind_Down_RlyCoil_Ctrl_WF],
  &Com_SignalConfigs[COM_SID_RL_Wind_Up_RlyCoil_Ctrl_WF],
  &Com_SignalConfigs[COM_SID_RL_Wind_Down_RlyCoil_Ctrl_WF],
  &Com_SignalConfigs[COM_SID_RR_Wind_Up_RlyCoil_Ctrl_WF],
  &Com_SignalConfigs[COM_SID_RR_Wind_Down_RlyCoil_Ctrl_WF],
  &Com_SignalConfigs[COM_SID_Center_Unlock_RlyCoil_Ctrl_WF],
  &Com_SignalConfigs[COM_SID_Center_Lock_RlyCoil_Ctrl_WF],
  &Com_SignalConfigs[COM_SID_Mirror_Heat_RlyCoil_Ctrl_WF],
  &Com_SignalConfigs[COM_SID_Horn_SW_WF],
  &Com_SignalConfigs[COM_SID_FL_Wind_Gnd_Ctrl_WF],
  &Com_SignalConfigs[COM_SID_FR_Wind_Gnd_Ctrl_WF],
  &Com_SignalConfigs[COM_SID_RL_Wind_Gnd_Ctrl_WF],
  &Com_SignalConfigs[COM_SID_RR_Wind_Gnd_Ctrl_WF],
  &Com_SignalConfigs[COM_SID_LSD_SSB_LED3_WF],
  &Com_SignalConfigs[COM_SID_LSD_SSB_LED2_WF],
  &Com_SignalConfigs[COM_SID_LSD_SSB_LED1_WF],
  &Com_SignalConfigs[COM_SID_Condensing_Fan_Low_Ctrl_WF],
  &Com_SignalConfigs[COM_SID_Condensing_Fan_High_Ctrl_WF],
  &Com_SignalConfigs[COM_SID_Int_Ext_Motor_Inc_WF],
  &Com_SignalConfigs[COM_SID_Int_Ext_Motor_Dec_WF],
  &Com_SignalConfigs[COM_SID_Cold_Heat_Motor_Inc_WF],
  &Com_SignalConfigs[COM_SID_Cold_Heat_Motor_Dec_WF],
  &Com_SignalConfigs[COM_SID_Mode_Motor_Inc_WF],
  &Com_SignalConfigs[COM_SID_Mode_MotoR_Dec_WF],
  &Com_SignalConfigs[COM_SID_IDM_LPOWER],
  &Com_SignalConfigs[COM_SID_FL_Gnd_Ctrl_WF],
  &Com_SignalConfigs[COM_SID_FR_Gnd_Ctrl_WF],
};

static const Com_SignalConfigType* Com_IPduSignals_ID3_RX[] = {
  &Com_SignalConfigs[COM_SID_RL_Wind_Samp_WF],
  &Com_SignalConfigs[COM_SID_RR_Wind_Samp_WF],
  &Com_SignalConfigs[COM_SID_Blower_Analog_Out_WF],
  &Com_SignalConfigs[COM_SID_Cold_Heat_Motor_Fb_WF],
  &Com_SignalConfigs[COM_SID_Mode_MotoR_WF],
};

static const Com_SignalConfigType* Com_IPduSignals_TP_CM_RX[] = {
  &Com_SignalConfigs[COM_SID_ControlByte],
  &Com_SignalConfigs[COM_SID_TotalNumberOfBbytes],
  &Com_SignalConfigs[COM_SID_TotalNumberOfPackets],
  &Com_SignalConfigs[COM_SID_ParameterGroupNumber],
};

static const Com_SignalConfigType* Com_IPduSignals_TP_DT_RX[] = {
  &Com_SignalConfigs[COM_SID_SequenceNumber],
};

static const Com_SignalConfigType* Com_IPduSignals_CANTEST_TX_TEST[] = {
  &Com_SignalConfigs[COM_SID_TX_COUNTER],
  &Com_SignalConfigs[COM_SID_TX_FLAG],
  &Com_SignalConfigs[COM_SID_TX_LEVEL],
  &Com_SignalConfigs[COM_SID_LedRunMode],
  &Com_SignalConfigs[COM_SID_LedOut],
  &Com_SignalConfigs[COM_SID_LedBlinkPhase],
  &Com_SignalConfigs[COM_SID_LedFaultTimeout],
  &Com_SignalConfigs[COM_SID_LedFaultCmd],
};

static const Com_SignalConfigType* Com_IPduSignals_CANTEST_RX_TEST[] = {
  &Com_SignalConfigs[COM_SID_RX_COUNTER],
  &Com_SignalConfigs[COM_SID_RX_TEMP],
};

static const Com_IPduTxConfigType Com_IPduTxConfig_BCM_LCSF_TX = {
  &Com_IPduTxContext_BCM_LCSF_TX,
  #ifdef COM_USE_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #ifdef COM_USE_TX_IPDU_CALLOUT
  NULL, /* TxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTime */
  COM_CONVERT_MS_TO_MAIN_CYCLES(50u), /* CycleTime */
#ifdef USE_PDUR
  PDUR_CAN1_BCM_LCSF_TX,
#else
  COM_ECUC_PDUID_OFFSET + COM_CAN1_BCM_LCSF_TX,
#endif
};

static const Com_IPduTxConfigType Com_IPduTxConfig_BCM_Ctrl_TX = {
  &Com_IPduTxContext_BCM_Ctrl_TX,
  #ifdef COM_USE_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #ifdef COM_USE_TX_IPDU_CALLOUT
  NULL, /* TxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTime */
  COM_CONVERT_MS_TO_MAIN_CYCLES(100u), /* CycleTime */
#ifdef USE_PDUR
  PDUR_CAN1_BCM_CTRL_TX,
#else
  COM_ECUC_PDUID_OFFSET + COM_CAN1_BCM_CTRL_TX,
#endif
};

static const Com_IPduTxConfigType Com_IPduTxConfig_BCM_OEL_TX = {
  &Com_IPduTxContext_BCM_OEL_TX,
  #ifdef COM_USE_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #ifdef COM_USE_TX_IPDU_CALLOUT
  NULL, /* TxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTime */
  COM_CONVERT_MS_TO_MAIN_CYCLES(100u), /* CycleTime */
#ifdef USE_PDUR
  PDUR_CAN1_BCM_OEL_TX,
#else
  COM_ECUC_PDUID_OFFSET + COM_CAN1_BCM_OEL_TX,
#endif
};

static const Com_IPduTxConfigType Com_IPduTxConfig_BCM_OWW_TX = {
  &Com_IPduTxContext_BCM_OWW_TX,
  #ifdef COM_USE_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #ifdef COM_USE_TX_IPDU_CALLOUT
  NULL, /* TxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTime */
  COM_CONVERT_MS_TO_MAIN_CYCLES(200u), /* CycleTime */
#ifdef USE_PDUR
  PDUR_CAN1_BCM_OWW_TX,
#else
  COM_ECUC_PDUID_OFFSET + COM_CAN1_BCM_OWW_TX,
#endif
};

static const Com_IPduTxConfigType Com_IPduTxConfig_BCM_DoorCtrl_TX = {
  &Com_IPduTxContext_BCM_DoorCtrl_TX,
  #ifdef COM_USE_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #ifdef COM_USE_TX_IPDU_CALLOUT
  NULL, /* TxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTime */
  COM_CONVERT_MS_TO_MAIN_CYCLES(100u), /* CycleTime */
#ifdef USE_PDUR
  PDUR_CAN1_BCM_DOOR_CTRL_TX,
#else
  COM_ECUC_PDUID_OFFSET + COM_CAN1_BCM_DOOR_CTRL_TX,
#endif
};

static const Com_IPduTxConfigType Com_IPduTxConfig_BCM_DM1_TX = {
  &Com_IPduTxContext_BCM_DM1_TX,
  #ifdef COM_USE_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #ifdef COM_USE_TX_IPDU_CALLOUT
  NULL, /* TxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTime */
  COM_CONVERT_MS_TO_MAIN_CYCLES(1000u), /* CycleTime */
#ifdef USE_PDUR
  PDUR_CAN1_BCM_DM1_TX,
#else
  COM_ECUC_PDUID_OFFSET + COM_CAN1_BCM_DM1_TX,
#endif
};

static const Com_IPduRxConfigType Com_IPduRxConfig_Crash_Notification_RX = {
  &Com_IPduRxContext_Crash_Notification_RX,
  #ifdef COM_USE_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  #ifdef COM_USE_RX_IPDU_CALLOUT
  NULL, /* RxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTimeout */
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* Timeout */
};

static const Com_IPduRxConfigType Com_IPduRxConfig_AMB_Ambient_Conditions_RX = {
  &Com_IPduRxContext_AMB_Ambient_Conditions_RX,
  #ifdef COM_USE_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  #ifdef COM_USE_RX_IPDU_CALLOUT
  NULL, /* RxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTimeout */
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* Timeout */
};

static const Com_IPduRxConfigType Com_IPduRxConfig_PEPS1_RX = {
  &Com_IPduRxContext_PEPS1_RX,
  #ifdef COM_USE_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  #ifdef COM_USE_RX_IPDU_CALLOUT
  NULL, /* RxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTimeout */
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* Timeout */
};

static const Com_IPduRxConfigType Com_IPduRxConfig_PEPS2_RX = {
  &Com_IPduRxContext_PEPS2_RX,
  #ifdef COM_USE_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  #ifdef COM_USE_RX_IPDU_CALLOUT
  NULL, /* RxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTimeout */
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* Timeout */
};

static const Com_IPduRxConfigType Com_IPduRxConfig_PEPS_ESCLM_RX = {
  &Com_IPduRxContext_PEPS_ESCLM_RX,
  #ifdef COM_USE_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  #ifdef COM_USE_RX_IPDU_CALLOUT
  NULL, /* RxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTimeout */
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* Timeout */
};

static const Com_IPduRxConfigType Com_IPduRxConfig_ACL_RX = {
  &Com_IPduRxContext_ACL_RX,
  #ifdef COM_USE_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  #ifdef COM_USE_RX_IPDU_CALLOUT
  NULL, /* RxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTimeout */
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* Timeout */
};

static const Com_IPduRxConfigType Com_IPduRxConfig_EOI_RX = {
  &Com_IPduRxContext_EOI_RX,
  #ifdef COM_USE_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  #ifdef COM_USE_RX_IPDU_CALLOUT
  NULL, /* RxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTimeout */
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* Timeout */
};

static const Com_IPduRxConfigType Com_IPduRxConfig_ETC2_RX = {
  &Com_IPduRxContext_ETC2_RX,
  #ifdef COM_USE_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  #ifdef COM_USE_RX_IPDU_CALLOUT
  NULL, /* RxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTimeout */
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* Timeout */
};

static const Com_IPduRxConfigType Com_IPduRxConfig_ESCL1_RX = {
  &Com_IPduRxContext_ESCL1_RX,
  #ifdef COM_USE_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  #ifdef COM_USE_RX_IPDU_CALLOUT
  NULL, /* RxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTimeout */
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* Timeout */
};

static const Com_IPduRxConfigType Com_IPduRxConfig_ESCLM_PEPS_RX = {
  &Com_IPduRxContext_ESCLM_PEPS_RX,
  #ifdef COM_USE_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  #ifdef COM_USE_RX_IPDU_CALLOUT
  NULL, /* RxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTimeout */
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* Timeout */
};

static const Com_IPduRxConfigType Com_IPduRxConfig_ESCL_NM_RX = {
  &Com_IPduRxContext_ESCL_NM_RX,
  #ifdef COM_USE_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  #ifdef COM_USE_RX_IPDU_CALLOUT
  NULL, /* RxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTimeout */
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* Timeout */
};

static const Com_IPduRxConfigType Com_IPduRxConfig_DW_State_RX = {
  &Com_IPduRxContext_DW_State_RX,
  #ifdef COM_USE_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  #ifdef COM_USE_RX_IPDU_CALLOUT
  NULL, /* RxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTimeout */
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* Timeout */
};

static const Com_IPduRxConfigType Com_IPduRxConfig_IC_MSG_RX = {
  &Com_IPduRxContext_IC_MSG_RX,
  #ifdef COM_USE_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  #ifdef COM_USE_RX_IPDU_CALLOUT
  NULL, /* RxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTimeout */
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* Timeout */
};

static const Com_IPduRxConfigType Com_IPduRxConfig_EEC1_Electronic_Engine_Controller_1_RX = {
  &Com_IPduRxContext_EEC1_Electronic_Engine_Controller_1_RX,
  #ifdef COM_USE_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  #ifdef COM_USE_RX_IPDU_CALLOUT
  NULL, /* RxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTimeout */
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* Timeout */
};

static const Com_IPduRxConfigType Com_IPduRxConfig_CCVS_RX = {
  &Com_IPduRxContext_CCVS_RX,
  #ifdef COM_USE_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  #ifdef COM_USE_RX_IPDU_CALLOUT
  NULL, /* RxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTimeout */
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* Timeout */
};

static const Com_IPduRxConfigType Com_IPduRxConfig_VCU_4_RX = {
  &Com_IPduRxContext_VCU_4_RX,
  #ifdef COM_USE_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  #ifdef COM_USE_RX_IPDU_CALLOUT
  NULL, /* RxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTimeout */
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* Timeout */
};

static const Com_IPduRxConfigType Com_IPduRxConfig_TCO1_RX = {
  &Com_IPduRxContext_TCO1_RX,
  #ifdef COM_USE_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  #ifdef COM_USE_RX_IPDU_CALLOUT
  NULL, /* RxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTimeout */
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* Timeout */
};

static const Com_IPduRxConfigType Com_IPduRxConfig_TireCondition_RX = {
  &Com_IPduRxContext_TireCondition_RX,
  #ifdef COM_USE_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  #ifdef COM_USE_RX_IPDU_CALLOUT
  NULL, /* RxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTimeout */
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* Timeout */
};

static const Com_IPduRxConfigType Com_IPduRxConfig_DM1_TPMS_RX = {
  &Com_IPduRxContext_DM1_TPMS_RX,
  #ifdef COM_USE_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  #ifdef COM_USE_RX_IPDU_CALLOUT
  NULL, /* RxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTimeout */
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* Timeout */
};

static const Com_IPduRxConfigType Com_IPduRxConfig_EBC1_Electronic_Brake_Controller_1_RX = {
  &Com_IPduRxContext_EBC1_Electronic_Brake_Controller_1_RX,
  #ifdef COM_USE_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  #ifdef COM_USE_RX_IPDU_CALLOUT
  NULL, /* RxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTimeout */
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* Timeout */
};

static const Com_IPduRxConfigType Com_IPduRxConfig_EBC5_Electronic_Brake_Controller_5_RX = {
  &Com_IPduRxContext_EBC5_Electronic_Brake_Controller_5_RX,
  #ifdef COM_USE_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  #ifdef COM_USE_RX_IPDU_CALLOUT
  NULL, /* RxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTimeout */
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* Timeout */
};

static const Com_IPduRxConfigType Com_IPduRxConfig_DLCC1_Direct_Lamp_Control_Command_1_RX = {
  &Com_IPduRxContext_DLCC1_Direct_Lamp_Control_Command_1_RX,
  #ifdef COM_USE_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  #ifdef COM_USE_RX_IPDU_CALLOUT
  NULL, /* RxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTimeout */
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* Timeout */
};

static const Com_IPduRxConfigType Com_IPduRxConfig_CCVS1_Cruise_Control_Vehicle_Speed_1_RX = {
  &Com_IPduRxContext_CCVS1_Cruise_Control_Vehicle_Speed_1_RX,
  #ifdef COM_USE_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  #ifdef COM_USE_RX_IPDU_CALLOUT
  NULL, /* RxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTimeout */
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* Timeout */
};

static const Com_IPduRxConfigType Com_IPduRxConfig_VDC1_Vehicle_Dynamic_Stability_Control_1_RX = {
  &Com_IPduRxContext_VDC1_Vehicle_Dynamic_Stability_Control_1_RX,
  #ifdef COM_USE_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  #ifdef COM_USE_RX_IPDU_CALLOUT
  NULL, /* RxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTimeout */
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* Timeout */
};

static const Com_IPduRxConfigType Com_IPduRxConfig_ERC1_RX = {
  &Com_IPduRxContext_ERC1_RX,
  #ifdef COM_USE_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  #ifdef COM_USE_RX_IPDU_CALLOUT
  NULL, /* RxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTimeout */
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* Timeout */
};

static const Com_IPduRxConfigType Com_IPduRxConfig_ERC3_RX = {
  &Com_IPduRxContext_ERC3_RX,
  #ifdef COM_USE_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  #ifdef COM_USE_RX_IPDU_CALLOUT
  NULL, /* RxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTimeout */
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* Timeout */
};

static const Com_IPduRxConfigType Com_IPduRxConfig_ETC5_RX = {
  &Com_IPduRxContext_ETC5_RX,
  #ifdef COM_USE_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  #ifdef COM_USE_RX_IPDU_CALLOUT
  NULL, /* RxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTimeout */
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* Timeout */
};

static const Com_IPduRxConfigType Com_IPduRxConfig_EEC3_RX = {
  &Com_IPduRxContext_EEC3_RX,
  #ifdef COM_USE_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  #ifdef COM_USE_RX_IPDU_CALLOUT
  NULL, /* RxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTimeout */
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* Timeout */
};

static const Com_IPduRxConfigType Com_IPduRxConfig_ECC2_RX = {
  &Com_IPduRxContext_ECC2_RX,
  #ifdef COM_USE_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  #ifdef COM_USE_RX_IPDU_CALLOUT
  NULL, /* RxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTimeout */
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* Timeout */
};

static const Com_IPduRxConfigType Com_IPduRxConfig_ID1_RX = {
  &Com_IPduRxContext_ID1_RX,
  #ifdef COM_USE_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  #ifdef COM_USE_RX_IPDU_CALLOUT
  NULL, /* RxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTimeout */
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* Timeout */
};

static const Com_IPduRxConfigType Com_IPduRxConfig_ID2_RX = {
  &Com_IPduRxContext_ID2_RX,
  #ifdef COM_USE_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  #ifdef COM_USE_RX_IPDU_CALLOUT
  NULL, /* RxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTimeout */
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* Timeout */
};

static const Com_IPduRxConfigType Com_IPduRxConfig_ID3_RX = {
  &Com_IPduRxContext_ID3_RX,
  #ifdef COM_USE_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  #ifdef COM_USE_RX_IPDU_CALLOUT
  NULL, /* RxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTimeout */
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* Timeout */
};

static const Com_IPduRxConfigType Com_IPduRxConfig_TP_CM_RX = {
  &Com_IPduRxContext_TP_CM_RX,
  #ifdef COM_USE_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  #ifdef COM_USE_RX_IPDU_CALLOUT
  NULL, /* RxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTimeout */
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* Timeout */
};

static const Com_IPduRxConfigType Com_IPduRxConfig_TP_DT_RX = {
  &Com_IPduRxContext_TP_DT_RX,
  #ifdef COM_USE_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  #ifdef COM_USE_RX_IPDU_CALLOUT
  NULL, /* RxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTimeout */
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* Timeout */
};

static const Com_IPduTxConfigType Com_IPduTxConfig_CANTEST_TX_TEST = {
  &Com_IPduTxContext_CANTEST_TX_TEST,
  #ifdef COM_USE_TX_ERROR_NOTIFICATION
  NULL, /* ErrorNotification */
  #endif
  #ifdef COM_USE_TX_NOTIFICATION
  NULL, /* TxNotification */
  #endif
  #ifdef COM_USE_TX_IPDU_CALLOUT
  NULL, /* TxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTime */
  COM_CONVERT_MS_TO_MAIN_CYCLES(100u), /* CycleTime */
#ifdef USE_PDUR
  PDUR_CANTEST_TX_TEST,
#else
  COM_ECUC_PDUID_OFFSET + COM_CANTEST_TX_TEST,
#endif
};

static const Com_IPduRxConfigType Com_IPduRxConfig_CANTEST_RX_TEST = {
  &Com_IPduRxContext_CANTEST_RX_TEST,
  #ifdef COM_USE_RX_NOTIFICATION
  NULL, /* RxNotification */
  #endif
  #ifdef COM_USE_RX_TIMEOUT
  NULL, /* RxTOut */
  #endif
  #ifdef COM_USE_RX_IPDU_CALLOUT
  NULL, /* RxIpduCallout */
  #endif
  COM_CONVERT_MS_TO_MAIN_CYCLES(0u), /* FirstTimeout */
  COM_CONVERT_MS_TO_MAIN_CYCLES(1000u), /* Timeout */
};

static const Com_IPduConfigType Com_IPduConfigs[] = {
  {
#ifdef USE_SHELL
    "BCM_LCSF_TX",
#endif
    Com_PduData_BCM_LCSF_TX, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_BCM_LCSF_TX, /* signals */
    NULL, /* rxConfig */
    &Com_IPduTxConfig_BCM_LCSF_TX, /* txConfig */
    Com_IPduBCM_LCSF_TX_GroupRefMask,
    sizeof(Com_PduData_BCM_LCSF_TX), /* length */
    ARRAY_SIZE(Com_IPduSignals_BCM_LCSF_TX), /* numOfSignals */
  },
  {
#ifdef USE_SHELL
    "BCM_Ctrl_TX",
#endif
    Com_PduData_BCM_Ctrl_TX, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_BCM_Ctrl_TX, /* signals */
    NULL, /* rxConfig */
    &Com_IPduTxConfig_BCM_Ctrl_TX, /* txConfig */
    Com_IPduBCM_Ctrl_TX_GroupRefMask,
    sizeof(Com_PduData_BCM_Ctrl_TX), /* length */
    ARRAY_SIZE(Com_IPduSignals_BCM_Ctrl_TX), /* numOfSignals */
  },
  {
#ifdef USE_SHELL
    "BCM_OEL_TX",
#endif
    Com_PduData_BCM_OEL_TX, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_BCM_OEL_TX, /* signals */
    NULL, /* rxConfig */
    &Com_IPduTxConfig_BCM_OEL_TX, /* txConfig */
    Com_IPduBCM_OEL_TX_GroupRefMask,
    sizeof(Com_PduData_BCM_OEL_TX), /* length */
    ARRAY_SIZE(Com_IPduSignals_BCM_OEL_TX), /* numOfSignals */
  },
  {
#ifdef USE_SHELL
    "BCM_OWW_TX",
#endif
    Com_PduData_BCM_OWW_TX, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_BCM_OWW_TX, /* signals */
    NULL, /* rxConfig */
    &Com_IPduTxConfig_BCM_OWW_TX, /* txConfig */
    Com_IPduBCM_OWW_TX_GroupRefMask,
    sizeof(Com_PduData_BCM_OWW_TX), /* length */
    ARRAY_SIZE(Com_IPduSignals_BCM_OWW_TX), /* numOfSignals */
  },
  {
#ifdef USE_SHELL
    "BCM_DoorCtrl_TX",
#endif
    Com_PduData_BCM_DoorCtrl_TX, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_BCM_DoorCtrl_TX, /* signals */
    NULL, /* rxConfig */
    &Com_IPduTxConfig_BCM_DoorCtrl_TX, /* txConfig */
    Com_IPduBCM_DoorCtrl_TX_GroupRefMask,
    sizeof(Com_PduData_BCM_DoorCtrl_TX), /* length */
    ARRAY_SIZE(Com_IPduSignals_BCM_DoorCtrl_TX), /* numOfSignals */
  },
  {
#ifdef USE_SHELL
    "BCM_DM1_TX",
#endif
    Com_PduData_BCM_DM1_TX, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_BCM_DM1_TX, /* signals */
    NULL, /* rxConfig */
    &Com_IPduTxConfig_BCM_DM1_TX, /* txConfig */
    Com_IPduBCM_DM1_TX_GroupRefMask,
    sizeof(Com_PduData_BCM_DM1_TX), /* length */
    ARRAY_SIZE(Com_IPduSignals_BCM_DM1_TX), /* numOfSignals */
  },
  {
#ifdef USE_SHELL
    "Crash_Notification_RX",
#endif
    Com_PduData_Crash_Notification_RX, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_Crash_Notification_RX, /* signals */
    &Com_IPduRxConfig_Crash_Notification_RX, /* rxConfig */
    NULL, /* txConfig */
    Com_IPduCrash_Notification_RX_GroupRefMask,
    sizeof(Com_PduData_Crash_Notification_RX), /* length */
    ARRAY_SIZE(Com_IPduSignals_Crash_Notification_RX), /* numOfSignals */
  },
  {
#ifdef USE_SHELL
    "AMB_Ambient_Conditions_RX",
#endif
    Com_PduData_AMB_Ambient_Conditions_RX, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_AMB_Ambient_Conditions_RX, /* signals */
    &Com_IPduRxConfig_AMB_Ambient_Conditions_RX, /* rxConfig */
    NULL, /* txConfig */
    Com_IPduAMB_Ambient_Conditions_RX_GroupRefMask,
    sizeof(Com_PduData_AMB_Ambient_Conditions_RX), /* length */
    ARRAY_SIZE(Com_IPduSignals_AMB_Ambient_Conditions_RX), /* numOfSignals */
  },
  {
#ifdef USE_SHELL
    "PEPS1_RX",
#endif
    Com_PduData_PEPS1_RX, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_PEPS1_RX, /* signals */
    &Com_IPduRxConfig_PEPS1_RX, /* rxConfig */
    NULL, /* txConfig */
    Com_IPduPEPS1_RX_GroupRefMask,
    sizeof(Com_PduData_PEPS1_RX), /* length */
    ARRAY_SIZE(Com_IPduSignals_PEPS1_RX), /* numOfSignals */
  },
  {
#ifdef USE_SHELL
    "PEPS2_RX",
#endif
    Com_PduData_PEPS2_RX, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_PEPS2_RX, /* signals */
    &Com_IPduRxConfig_PEPS2_RX, /* rxConfig */
    NULL, /* txConfig */
    Com_IPduPEPS2_RX_GroupRefMask,
    sizeof(Com_PduData_PEPS2_RX), /* length */
    ARRAY_SIZE(Com_IPduSignals_PEPS2_RX), /* numOfSignals */
  },
  {
#ifdef USE_SHELL
    "PEPS_ESCLM_RX",
#endif
    Com_PduData_PEPS_ESCLM_RX, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_PEPS_ESCLM_RX, /* signals */
    &Com_IPduRxConfig_PEPS_ESCLM_RX, /* rxConfig */
    NULL, /* txConfig */
    Com_IPduPEPS_ESCLM_RX_GroupRefMask,
    sizeof(Com_PduData_PEPS_ESCLM_RX), /* length */
    ARRAY_SIZE(Com_IPduSignals_PEPS_ESCLM_RX), /* numOfSignals */
  },
  {
#ifdef USE_SHELL
    "ACL_RX",
#endif
    Com_PduData_ACL_RX, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_ACL_RX, /* signals */
    &Com_IPduRxConfig_ACL_RX, /* rxConfig */
    NULL, /* txConfig */
    Com_IPduACL_RX_GroupRefMask,
    sizeof(Com_PduData_ACL_RX), /* length */
    ARRAY_SIZE(Com_IPduSignals_ACL_RX), /* numOfSignals */
  },
  {
#ifdef USE_SHELL
    "EOI_RX",
#endif
    Com_PduData_EOI_RX, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_EOI_RX, /* signals */
    &Com_IPduRxConfig_EOI_RX, /* rxConfig */
    NULL, /* txConfig */
    Com_IPduEOI_RX_GroupRefMask,
    sizeof(Com_PduData_EOI_RX), /* length */
    ARRAY_SIZE(Com_IPduSignals_EOI_RX), /* numOfSignals */
  },
  {
#ifdef USE_SHELL
    "ETC2_RX",
#endif
    Com_PduData_ETC2_RX, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_ETC2_RX, /* signals */
    &Com_IPduRxConfig_ETC2_RX, /* rxConfig */
    NULL, /* txConfig */
    Com_IPduETC2_RX_GroupRefMask,
    sizeof(Com_PduData_ETC2_RX), /* length */
    ARRAY_SIZE(Com_IPduSignals_ETC2_RX), /* numOfSignals */
  },
  {
#ifdef USE_SHELL
    "ESCL1_RX",
#endif
    Com_PduData_ESCL1_RX, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_ESCL1_RX, /* signals */
    &Com_IPduRxConfig_ESCL1_RX, /* rxConfig */
    NULL, /* txConfig */
    Com_IPduESCL1_RX_GroupRefMask,
    sizeof(Com_PduData_ESCL1_RX), /* length */
    ARRAY_SIZE(Com_IPduSignals_ESCL1_RX), /* numOfSignals */
  },
  {
#ifdef USE_SHELL
    "ESCLM_PEPS_RX",
#endif
    Com_PduData_ESCLM_PEPS_RX, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_ESCLM_PEPS_RX, /* signals */
    &Com_IPduRxConfig_ESCLM_PEPS_RX, /* rxConfig */
    NULL, /* txConfig */
    Com_IPduESCLM_PEPS_RX_GroupRefMask,
    sizeof(Com_PduData_ESCLM_PEPS_RX), /* length */
    ARRAY_SIZE(Com_IPduSignals_ESCLM_PEPS_RX), /* numOfSignals */
  },
  {
#ifdef USE_SHELL
    "ESCL_NM_RX",
#endif
    Com_PduData_ESCL_NM_RX, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_ESCL_NM_RX, /* signals */
    &Com_IPduRxConfig_ESCL_NM_RX, /* rxConfig */
    NULL, /* txConfig */
    Com_IPduESCL_NM_RX_GroupRefMask,
    sizeof(Com_PduData_ESCL_NM_RX), /* length */
    ARRAY_SIZE(Com_IPduSignals_ESCL_NM_RX), /* numOfSignals */
  },
  {
#ifdef USE_SHELL
    "DW_State_RX",
#endif
    Com_PduData_DW_State_RX, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_DW_State_RX, /* signals */
    &Com_IPduRxConfig_DW_State_RX, /* rxConfig */
    NULL, /* txConfig */
    Com_IPduDW_State_RX_GroupRefMask,
    sizeof(Com_PduData_DW_State_RX), /* length */
    ARRAY_SIZE(Com_IPduSignals_DW_State_RX), /* numOfSignals */
  },
  {
#ifdef USE_SHELL
    "IC_MSG_RX",
#endif
    Com_PduData_IC_MSG_RX, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_IC_MSG_RX, /* signals */
    &Com_IPduRxConfig_IC_MSG_RX, /* rxConfig */
    NULL, /* txConfig */
    Com_IPduIC_MSG_RX_GroupRefMask,
    sizeof(Com_PduData_IC_MSG_RX), /* length */
    ARRAY_SIZE(Com_IPduSignals_IC_MSG_RX), /* numOfSignals */
  },
  {
#ifdef USE_SHELL
    "EEC1_Electronic_Engine_Controller_1_RX",
#endif
    Com_PduData_EEC1_Electronic_Engine_Controller_1_RX, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_EEC1_Electronic_Engine_Controller_1_RX, /* signals */
    &Com_IPduRxConfig_EEC1_Electronic_Engine_Controller_1_RX, /* rxConfig */
    NULL, /* txConfig */
    Com_IPduEEC1_Electronic_Engine_Controller_1_RX_GroupRefMask,
    sizeof(Com_PduData_EEC1_Electronic_Engine_Controller_1_RX), /* length */
    ARRAY_SIZE(Com_IPduSignals_EEC1_Electronic_Engine_Controller_1_RX), /* numOfSignals */
  },
  {
#ifdef USE_SHELL
    "CCVS_RX",
#endif
    Com_PduData_CCVS_RX, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_CCVS_RX, /* signals */
    &Com_IPduRxConfig_CCVS_RX, /* rxConfig */
    NULL, /* txConfig */
    Com_IPduCCVS_RX_GroupRefMask,
    sizeof(Com_PduData_CCVS_RX), /* length */
    ARRAY_SIZE(Com_IPduSignals_CCVS_RX), /* numOfSignals */
  },
  {
#ifdef USE_SHELL
    "VCU_4_RX",
#endif
    Com_PduData_VCU_4_RX, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_VCU_4_RX, /* signals */
    &Com_IPduRxConfig_VCU_4_RX, /* rxConfig */
    NULL, /* txConfig */
    Com_IPduVCU_4_RX_GroupRefMask,
    sizeof(Com_PduData_VCU_4_RX), /* length */
    ARRAY_SIZE(Com_IPduSignals_VCU_4_RX), /* numOfSignals */
  },
  {
#ifdef USE_SHELL
    "TCO1_RX",
#endif
    Com_PduData_TCO1_RX, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_TCO1_RX, /* signals */
    &Com_IPduRxConfig_TCO1_RX, /* rxConfig */
    NULL, /* txConfig */
    Com_IPduTCO1_RX_GroupRefMask,
    sizeof(Com_PduData_TCO1_RX), /* length */
    ARRAY_SIZE(Com_IPduSignals_TCO1_RX), /* numOfSignals */
  },
  {
#ifdef USE_SHELL
    "TireCondition_RX",
#endif
    Com_PduData_TireCondition_RX, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_TireCondition_RX, /* signals */
    &Com_IPduRxConfig_TireCondition_RX, /* rxConfig */
    NULL, /* txConfig */
    Com_IPduTireCondition_RX_GroupRefMask,
    sizeof(Com_PduData_TireCondition_RX), /* length */
    ARRAY_SIZE(Com_IPduSignals_TireCondition_RX), /* numOfSignals */
  },
  {
#ifdef USE_SHELL
    "DM1_TPMS_RX",
#endif
    Com_PduData_DM1_TPMS_RX, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_DM1_TPMS_RX, /* signals */
    &Com_IPduRxConfig_DM1_TPMS_RX, /* rxConfig */
    NULL, /* txConfig */
    Com_IPduDM1_TPMS_RX_GroupRefMask,
    sizeof(Com_PduData_DM1_TPMS_RX), /* length */
    ARRAY_SIZE(Com_IPduSignals_DM1_TPMS_RX), /* numOfSignals */
  },
  {
#ifdef USE_SHELL
    "EBC1_Electronic_Brake_Controller_1_RX",
#endif
    Com_PduData_EBC1_Electronic_Brake_Controller_1_RX, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_EBC1_Electronic_Brake_Controller_1_RX, /* signals */
    &Com_IPduRxConfig_EBC1_Electronic_Brake_Controller_1_RX, /* rxConfig */
    NULL, /* txConfig */
    Com_IPduEBC1_Electronic_Brake_Controller_1_RX_GroupRefMask,
    sizeof(Com_PduData_EBC1_Electronic_Brake_Controller_1_RX), /* length */
    ARRAY_SIZE(Com_IPduSignals_EBC1_Electronic_Brake_Controller_1_RX), /* numOfSignals */
  },
  {
#ifdef USE_SHELL
    "EBC5_Electronic_Brake_Controller_5_RX",
#endif
    Com_PduData_EBC5_Electronic_Brake_Controller_5_RX, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_EBC5_Electronic_Brake_Controller_5_RX, /* signals */
    &Com_IPduRxConfig_EBC5_Electronic_Brake_Controller_5_RX, /* rxConfig */
    NULL, /* txConfig */
    Com_IPduEBC5_Electronic_Brake_Controller_5_RX_GroupRefMask,
    sizeof(Com_PduData_EBC5_Electronic_Brake_Controller_5_RX), /* length */
    ARRAY_SIZE(Com_IPduSignals_EBC5_Electronic_Brake_Controller_5_RX), /* numOfSignals */
  },
  {
#ifdef USE_SHELL
    "DLCC1_Direct_Lamp_Control_Command_1_RX",
#endif
    Com_PduData_DLCC1_Direct_Lamp_Control_Command_1_RX, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_DLCC1_Direct_Lamp_Control_Command_1_RX, /* signals */
    &Com_IPduRxConfig_DLCC1_Direct_Lamp_Control_Command_1_RX, /* rxConfig */
    NULL, /* txConfig */
    Com_IPduDLCC1_Direct_Lamp_Control_Command_1_RX_GroupRefMask,
    sizeof(Com_PduData_DLCC1_Direct_Lamp_Control_Command_1_RX), /* length */
    ARRAY_SIZE(Com_IPduSignals_DLCC1_Direct_Lamp_Control_Command_1_RX), /* numOfSignals */
  },
  {
#ifdef USE_SHELL
    "CCVS1_Cruise_Control_Vehicle_Speed_1_RX",
#endif
    Com_PduData_CCVS1_Cruise_Control_Vehicle_Speed_1_RX, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_CCVS1_Cruise_Control_Vehicle_Speed_1_RX, /* signals */
    &Com_IPduRxConfig_CCVS1_Cruise_Control_Vehicle_Speed_1_RX, /* rxConfig */
    NULL, /* txConfig */
    Com_IPduCCVS1_Cruise_Control_Vehicle_Speed_1_RX_GroupRefMask,
    sizeof(Com_PduData_CCVS1_Cruise_Control_Vehicle_Speed_1_RX), /* length */
    ARRAY_SIZE(Com_IPduSignals_CCVS1_Cruise_Control_Vehicle_Speed_1_RX), /* numOfSignals */
  },
  {
#ifdef USE_SHELL
    "VDC1_Vehicle_Dynamic_Stability_Control_1_RX",
#endif
    Com_PduData_VDC1_Vehicle_Dynamic_Stability_Control_1_RX, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_VDC1_Vehicle_Dynamic_Stability_Control_1_RX, /* signals */
    &Com_IPduRxConfig_VDC1_Vehicle_Dynamic_Stability_Control_1_RX, /* rxConfig */
    NULL, /* txConfig */
    Com_IPduVDC1_Vehicle_Dynamic_Stability_Control_1_RX_GroupRefMask,
    sizeof(Com_PduData_VDC1_Vehicle_Dynamic_Stability_Control_1_RX), /* length */
    ARRAY_SIZE(Com_IPduSignals_VDC1_Vehicle_Dynamic_Stability_Control_1_RX), /* numOfSignals */
  },
  {
#ifdef USE_SHELL
    "ERC1_RX",
#endif
    Com_PduData_ERC1_RX, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_ERC1_RX, /* signals */
    &Com_IPduRxConfig_ERC1_RX, /* rxConfig */
    NULL, /* txConfig */
    Com_IPduERC1_RX_GroupRefMask,
    sizeof(Com_PduData_ERC1_RX), /* length */
    ARRAY_SIZE(Com_IPduSignals_ERC1_RX), /* numOfSignals */
  },
  {
#ifdef USE_SHELL
    "ERC3_RX",
#endif
    Com_PduData_ERC3_RX, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_ERC3_RX, /* signals */
    &Com_IPduRxConfig_ERC3_RX, /* rxConfig */
    NULL, /* txConfig */
    Com_IPduERC3_RX_GroupRefMask,
    sizeof(Com_PduData_ERC3_RX), /* length */
    ARRAY_SIZE(Com_IPduSignals_ERC3_RX), /* numOfSignals */
  },
  {
#ifdef USE_SHELL
    "ETC5_RX",
#endif
    Com_PduData_ETC5_RX, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_ETC5_RX, /* signals */
    &Com_IPduRxConfig_ETC5_RX, /* rxConfig */
    NULL, /* txConfig */
    Com_IPduETC5_RX_GroupRefMask,
    sizeof(Com_PduData_ETC5_RX), /* length */
    ARRAY_SIZE(Com_IPduSignals_ETC5_RX), /* numOfSignals */
  },
  {
#ifdef USE_SHELL
    "EEC3_RX",
#endif
    Com_PduData_EEC3_RX, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_EEC3_RX, /* signals */
    &Com_IPduRxConfig_EEC3_RX, /* rxConfig */
    NULL, /* txConfig */
    Com_IPduEEC3_RX_GroupRefMask,
    sizeof(Com_PduData_EEC3_RX), /* length */
    ARRAY_SIZE(Com_IPduSignals_EEC3_RX), /* numOfSignals */
  },
  {
#ifdef USE_SHELL
    "ECC2_RX",
#endif
    Com_PduData_ECC2_RX, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_ECC2_RX, /* signals */
    &Com_IPduRxConfig_ECC2_RX, /* rxConfig */
    NULL, /* txConfig */
    Com_IPduECC2_RX_GroupRefMask,
    sizeof(Com_PduData_ECC2_RX), /* length */
    ARRAY_SIZE(Com_IPduSignals_ECC2_RX), /* numOfSignals */
  },
  {
#ifdef USE_SHELL
    "ID1_RX",
#endif
    Com_PduData_ID1_RX, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_ID1_RX, /* signals */
    &Com_IPduRxConfig_ID1_RX, /* rxConfig */
    NULL, /* txConfig */
    Com_IPduID1_RX_GroupRefMask,
    sizeof(Com_PduData_ID1_RX), /* length */
    ARRAY_SIZE(Com_IPduSignals_ID1_RX), /* numOfSignals */
  },
  {
#ifdef USE_SHELL
    "ID2_RX",
#endif
    Com_PduData_ID2_RX, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_ID2_RX, /* signals */
    &Com_IPduRxConfig_ID2_RX, /* rxConfig */
    NULL, /* txConfig */
    Com_IPduID2_RX_GroupRefMask,
    sizeof(Com_PduData_ID2_RX), /* length */
    ARRAY_SIZE(Com_IPduSignals_ID2_RX), /* numOfSignals */
  },
  {
#ifdef USE_SHELL
    "ID3_RX",
#endif
    Com_PduData_ID3_RX, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_ID3_RX, /* signals */
    &Com_IPduRxConfig_ID3_RX, /* rxConfig */
    NULL, /* txConfig */
    Com_IPduID3_RX_GroupRefMask,
    sizeof(Com_PduData_ID3_RX), /* length */
    ARRAY_SIZE(Com_IPduSignals_ID3_RX), /* numOfSignals */
  },
  {
#ifdef USE_SHELL
    "TP_CM_RX",
#endif
    Com_PduData_TP_CM_RX, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_TP_CM_RX, /* signals */
    &Com_IPduRxConfig_TP_CM_RX, /* rxConfig */
    NULL, /* txConfig */
    Com_IPduTP_CM_RX_GroupRefMask,
    sizeof(Com_PduData_TP_CM_RX), /* length */
    ARRAY_SIZE(Com_IPduSignals_TP_CM_RX), /* numOfSignals */
  },
  {
#ifdef USE_SHELL
    "TP_DT_RX",
#endif
    Com_PduData_TP_DT_RX, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_TP_DT_RX, /* signals */
    &Com_IPduRxConfig_TP_DT_RX, /* rxConfig */
    NULL, /* txConfig */
    Com_IPduTP_DT_RX_GroupRefMask,
    sizeof(Com_PduData_TP_DT_RX), /* length */
    ARRAY_SIZE(Com_IPduSignals_TP_DT_RX), /* numOfSignals */
  },
  {
#ifdef USE_SHELL
    "CANTEST_TX_TEST",
#endif
    Com_PduData_CANTEST_TX_TEST, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_CANTEST_TX_TEST, /* signals */
    NULL, /* rxConfig */
    &Com_IPduTxConfig_CANTEST_TX_TEST, /* txConfig */
    Com_IPduCANTEST_TX_TEST_GroupRefMask,
    sizeof(Com_PduData_CANTEST_TX_TEST), /* length */
    ARRAY_SIZE(Com_IPduSignals_CANTEST_TX_TEST), /* numOfSignals */
  },
  {
#ifdef USE_SHELL
    "CANTEST_RX_TEST",
#endif
    Com_PduData_CANTEST_RX_TEST, /* ptr */
    NULL, /* dynLen */
    Com_IPduSignals_CANTEST_RX_TEST, /* signals */
    &Com_IPduRxConfig_CANTEST_RX_TEST, /* rxConfig */
    NULL, /* txConfig */
    Com_IPduCANTEST_RX_TEST_GroupRefMask,
    sizeof(Com_PduData_CANTEST_RX_TEST), /* length */
    ARRAY_SIZE(Com_IPduSignals_CANTEST_RX_TEST), /* numOfSignals */
  },
};

static Com_GlobalContextType Com_GlobalContext;
const Com_ConfigType Com_Config = {
  Com_IPduConfigs,
  Com_SignalConfigs,
  &Com_GlobalContext,
  ARRAY_SIZE(Com_IPduConfigs),
  ARRAY_SIZE(Com_SignalConfigs),
  2 /* numOfGroups */,
};

/* ================================ [ LOCALS    ] ============================================== */
/* ================================ [ FUNCTIONS ] ============================================== */
#ifdef USE_E2E
#include "E2E.h"
#include "E2E_Cfg.h"
#endif /* USE_E2E */

