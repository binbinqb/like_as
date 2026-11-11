/*
 * Copyright (c) 2022, Shenzhen CVA Innovation CO.,LTD
 * All rights reserved.
 *
 * Shenzhen CVA Innovation CO.,LTD (CVA chip) is supplying this file for use
 * exclusively with CVA's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * CVA SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/
#include "../cpu/cpu_drv.h"
#include "fccu_drv.h"
#include "fccu_reg.h"

/*******************************************************************************
 * the defines
 ******************************************************************************/

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the functions
 ******************************************************************************/

void FccuDrv_Init(FccuDrvType *obj, struct _FccuRegType_ *fccuReg, struct _SimRegType_ *simReg)
{
    obj->regFccu = fccuReg;
    obj->regSim  = simReg;
}

void FccuDrv_SetOptFlowNormal2Config(FccuDrvType *obj)
{
    obj->regFccu->OP_CTRLK = FCCUDRV_UNLOCK_KEY_OP1;
    obj->regFccu->OP_CTRL  = FCCUDRV_SEL_CTRL_OP1;
}

void FccuDrv_SetOptFlowConfig2Normal(FccuDrvType *obj)
{
    obj->regFccu->OP_CTRLK = FCCUDRV_UNLOCK_KEY_OP2;
    obj->regFccu->OP_CTRL  = FCCUDRV_SEL_CTRL_OP2;
}

void FccuDrv_ClrDbgStatusRcd(FccuDrvType *obj)
{
    obj->regFccu->OP_CTRL  = FCCUDRV_SEL_CTRL_OP13;
}

void FccuDrv_OpBackToIdle(FccuDrvType *obj)
{
    obj->regFccu->OP_CTRL  = FCCUDRV_SEL_CTRL_OP15;
}

void FccuDrv_SetConfigTimeoutIrqMode(FccuDrvType *obj, bool enable)
{
    /* Set config mode timeout Irq enable */
    FccuReg_SetCtrlCfgToIEn(obj->regFccu, enable);
}

bool FccuDrv_GetConfigTimeoutIrqMode(FccuDrvType *obj)
{
    /* Get config mode timeout Irq enable status */
    return FccuReg_GetCtrlCfgToIEn(obj->regFccu);
}

void FccuDrv_SetDebugMode(FccuDrvType *obj, bool enable)
{
    /* Set debug mode enable */
    FccuReg_SetCtrlDebug(obj->regFccu, enable);
}

bool FccuDrv_GetDebugMode(FccuDrvType *obj)
{
    /* Get debug mode enable */
    return FccuReg_GetCtrlDebug(obj->regFccu);
}

bool FccuDrv_SetOpCtrl(FccuDrvType *obj, FccuDrv_OpSelType opType)
{
    uint8_t delay_cnt = 0xFF;

    if(opType > FCCUDRV_SEL_CTRL_OP15)
    {
        return false;
    }

    /* waiting for OP status not in excuting */
    while ((FccuReg_GetOpStOpS(obj->regFccu) == FCCUDRV_OP_EXCUTING) && delay_cnt--)
    {
        ;
    }
    
    if (!delay_cnt)
    {
        return false;
    }

    if (opType == FCCUDRV_SEL_CTRL_OP1)
    {
        /* Option1 operate atom */
        FccuDrv_SetOptFlowNormal2Config(obj);
    }

    if (opType == FCCUDRV_SEL_CTRL_OP2)
    {
        /* Option2 operate atom */
        FccuDrv_SetOptFlowConfig2Normal(obj);
    }

    if (opType == FCCUDRV_SEL_CTRL_OP13)
    {
        /* Option13 operate, clear debug status */
        FccuDrv_ClrDbgStatusRcd(obj);
    }

    if (opType == FCCUDRV_SEL_CTRL_OP15)
    {
        /* Option15 operate, operation back to idle */
        FccuDrv_OpBackToIdle(obj);
    }

    return true;
}

FccuDrv_OpSelType FccuDrv_GetOpCtrl(FccuDrvType *obj)
{
    /* Get OP ctrl type */
    return (FccuDrv_OpSelType)FccuReg_GetOpCtrlOpr(obj->regFccu);
}

FccuDrv_OpStatusType FccuDrv_GetOpStatus(FccuDrvType *obj)
{
    /* Get OP ctrl operate result */
    return (FccuDrv_OpStatusType)FccuReg_GetOpStOpS(obj->regFccu);
}

void FccuDrv_SetTransLock(FccuDrvType *obj)
{
    /* Set Transient lock */
    FccuReg_SetTransLockKey(obj->regFccu, (uint32_t)~FCCUDRV_TRANS_UNLOCK_KEY);
}

void FccuDrv_SetTransUnlock(FccuDrvType *obj)
{
    /* Set Transient unlock */
    FccuReg_SetTransLockKey(obj->regFccu, FCCUDRV_TRANS_UNLOCK_KEY);
}

void FccuDrv_SetPermntLock(FccuDrvType *obj)
{
    /* Set Permanent unlock, unlock by MCU reset */
    FccuReg_SetPermntLockKey(obj->regFccu, FCCUDRV_PERMNT_LOCK_KEY);
}

bool FccuDrv_EnterConfigMode(FccuDrvType *obj)
{
    uint8_t delay_cnt = 0xFF;

    /* if FSM on CONFIG mode, don't need config */
    if(FccuReg_GetStFsm(obj->regFccu) == FCCUDRV_FSM_CONFIG)
    {
        return true;
    }

    /* if FSM on NORMAL mode, convert to CONFIG mode */
    if(FccuReg_GetStFsm(obj->regFccu) == FCCUDRV_FSM_NORMAL)
    {
        /* excute OP1, FSM convert from NORMAL to CONFIG */
        FccuDrv_SetOpCtrl(obj, FCCUDRV_SEL_CTRL_OP1);

        /* wait for FSM change to CONFIG mode */
        while ((FccuReg_GetStFsm(obj->regFccu) != FCCUDRV_FSM_CONFIG) && delay_cnt--)
        {
            ;
        }

        /* timeout then return */
        if (!delay_cnt)
        {
            return false;
        }

        /* FSM change to NORMAL success */
        return true;
    }

    /* if FSM on ALARM or FAULT status, return false */
    return false;
}

bool FccuDrv_ExitConfigMode(FccuDrvType *obj)
{
    uint8_t delay_cnt = 0xFF;

    /* Option2 operate atom */
    FccuDrv_SetOptFlowConfig2Normal(obj);

    /* wait for FSM change to CONFIG mode */
    while ((FccuReg_GetStFsm(obj->regFccu) != FCCUDRV_FSM_NORMAL) && delay_cnt--)
    {
        ;
    }

    /* timeout then return */
    if (!delay_cnt)
    {
        return false;
    }

    /* FSM change to NORMAL mode */
    return true;
}

void FccuDrv_SetEOutConfig(FccuDrvType *obj, FccuDrv_EOutCtrlType *eoutCtrl)
{
    uint32_t temp = 0;

    /* Transient unlock */
    FccuDrv_SetTransUnlock(obj);

    if(FccuDrv_EnterConfigMode(obj))
    {
        temp = (((uint32_t)eoutCtrl->eoutPwmFreq << 16) | ((uint32_t)eoutCtrl->eoutTstEnable << 2) | 
                ((uint32_t)eoutCtrl->eoutPsStatus << 1) | (uint32_t)eoutCtrl->eoutPadEnable);
        /* EOut Pwm parameter */
        FccuReg_SetEOutCfg(obj->regFccu, temp);

        /* EOut min hold time */
        FccuReg_SetDeltaT(obj->regFccu, eoutCtrl->eoutMinHoldTime);
    }
    /* Exit Config mode */
    FccuDrv_ExitConfigMode(obj);

    /* Transietn Lock */
    FccuDrv_SetTransLock(obj);
}

void FccuDrv_GetEOutConfig(FccuDrvType *obj, FccuDrv_EOutCtrlType *eoutCtrl)
{
    uint32_t temp = FccuReg_GetEOutCfg(obj->regFccu);
    /* Get EOut Pad enable Status */
    eoutCtrl->eoutPadEnable = (FccuDrv_EOutPadStatusType)(temp & 0x01);

    /* Get EOut polarity Status */
    eoutCtrl->eoutPsStatus = (FccuDrv_EOutPsStatusType)((temp >> 1) & 0x01);

    /* Get Eout Test Pad status */
    eoutCtrl->eoutTstEnable = ((temp >> 2) & 0x01);

    /* Get EOut PWM Frequency */
    eoutCtrl->eoutPwmFreq = ((temp >> 16) & 0xFFFF);

    /* Get EOut min hold time */
    eoutCtrl->eoutMinHoldTime = FccuReg_GetDeltaT(obj->regFccu);
}

void FccuDrv_SetChnConfig(FccuDrvType *obj, FccuDrv_ChnCtrlType *chnCtrl)
{
    /* Transient unlock */
    FccuDrv_SetTransUnlock(obj);

    if(FccuDrv_EnterConfigMode(obj) == false)
    {
        return;
    }

    /* Set all channel exception rst status */
    FccuReg_SetRstEn(obj->regFccu, chnCtrl->chnRstEn);

    /* Set all channel exception Alarm Irq status */
    FccuReg_SetIrqEnAlarm(obj->regFccu, chnCtrl->chnAlarmIrqEn);

    /* Set all channel exception NMI status */
    FccuReg_SetNmiEn(obj->regFccu, chnCtrl->chnNmiEn);

    /* Set all channel exception Error Injection status */
    FccuReg_SetEOutEn(obj->regFccu, chnCtrl->chnEOutEn);

    /* Set all channel EOut status */
    FccuReg_SetChE(obj->regFccu, chnCtrl->chnErrInEn);

    /* Set all channel EOut Error type status */
    FccuReg_SetTypeAlarm(obj->regFccu, chnCtrl->chnErrTypeSet);

    if(FccuDrv_ExitConfigMode(obj) == false)
    {
        return;
    }

    FccuDrv_SetTransLock(obj);
}

void FccuDrv_GetChnConfig(FccuDrvType *obj, FccuDrv_ChnCtrlType *chnCtrl)
{
    /* Get all channel exception rst status */
    chnCtrl->chnRstEn = FccuReg_GetRstEn(obj->regFccu);

    /* Get all channel exception Alarm Irq status */
    chnCtrl->chnAlarmIrqEn = FccuReg_GetIrqEnAlarm(obj->regFccu);

    /* Get all channel exception NMI status */
    chnCtrl->chnNmiEn = FccuReg_GetNmiEn(obj->regFccu);

    /* Get all channel exception Error Injection status */
    chnCtrl->chnErrInEn = FccuReg_GetChE(obj->regFccu);

    /* Get all channel EOut status */
    chnCtrl->chnEOutEn = FccuReg_GetEOutEn(obj->regFccu);

    /* Get all channel EOut Error type status */
    chnCtrl->chnErrTypeSet = FccuReg_GetTypeAlarm(obj->regFccu);
}

void FccuDrv_SetChnFakeIn(FccuDrvType *obj, uint32_t fakeIn)
{
    /* Set all channel Error Fake in status */
    FccuReg_SetFakeFault(obj->regFccu, fakeIn);
}

uint32_t FccuDrv_GetChnFakeIn(FccuDrvType *obj)
{
    /* Get all channel Error Fake in status */
    return FccuReg_GetFakeFault(obj->regFccu);
}

void FccuDrv_SetAlarmModeTimeoutThreshold(FccuDrvType *obj, uint32_t timeCnt)
{
    /* Transient unlock */
    FccuDrv_SetTransUnlock(obj);

    if(FccuDrv_EnterConfigMode(obj) == false)
    {
        return;
    }

    /* Set Alarm mode timeout threshold */
    FccuReg_SetAlarmTO(obj->regFccu, timeCnt);

    if(FccuDrv_ExitConfigMode(obj) == false)
    {
        return;
    }

    FccuDrv_SetTransLock(obj);
}

uint32_t FccuDrv_GetAlarmModeTimeoutThreshold(FccuDrvType *obj)
{
    /* Get Alarm mode timeout threshold */
    return FccuReg_GetAlarmTO(obj->regFccu);
}

void FccuDrv_SetConfigModeTimeoutThreshold(FccuDrvType *obj, uint8_t timeCnt)
{
    if(FccuDrv_ExitConfigMode(obj) != true)
    {
        return;
    }
    
    /* Set Config mode timeout threshold */
    FccuReg_SetCfgTO(obj->regFccu, timeCnt);
}

uint8_t FccuDrv_GetConfigModeTimeoutThreshold(FccuDrvType *obj)
{
    /* Get Config mode timeout threshold */
    return FccuReg_GetCfgTO(obj->regFccu);
}

void FccuDrv_GetFsmStatusChangeRecord(FccuDrvType *obj, FccuDrv_FsmStausChgRecordType *fsmChgRecord)
{
    /* Record FSM change from NORMAL to ALARM */
    fsmChgRecord->fsmNormalToAlarmSrc = FccuReg_GetDbgSt1N2ASrc(obj->regFccu);

    /* Record FSM change from ALARM to FAULT, because of timeout */
    fsmChgRecord->fsmAlarmToFaultSrc0 = FccuReg_GetDbgSt2A2FSrc0(obj->regFccu);

    /* Record FSM change from ALARM to FAULT, because of critical fault */
    fsmChgRecord->fsmAlarmToFaultSrc1 = FccuReg_GetDbgSt3A2FSrc1(obj->regFccu);

    /* Record FSM change from NORMAL to FAULT, because of critical fault */
    fsmChgRecord->fsmNormalToFaultSrc = FccuReg_GetDbgSt4N2FSrc(obj->regFccu);

    /* Record FSM change from FAULT to ALARM, because of critical fault clear */
    fsmChgRecord->fsmFaultToAlarmSrc = FccuReg_GetDbgSt5F2ASrc(obj->regFccu);
}

uint32_t FccuDrv_GetChnStatus(FccuDrvType *obj)
{
    /* unlock channel config register */
    FccuReg_SetFstKey(obj->regFccu, FCCUDRV_FST_UNLOCK_KEY);

    /* Get All Channel status */
    return FccuReg_GetFst(obj->regFccu);
}

void FccuDrv_SetChnErrorStatusClear(FccuDrvType *obj, uint32_t chnClrMask)
{
    /* unlock channel config register */
    FccuReg_SetFstKey(obj->regFccu, FCCUDRV_FST_UNLOCK_KEY);

    /* Selected channel to clear */
    FccuReg_SetFst(obj->regFccu, chnClrMask);
}

FccuDrv_ConfigRegStatusType FccuDrv_GetConfigRegLockStatus(FccuDrvType *obj)
{
    /* Get CONFIG mode lock status */
    return (FccuDrv_ConfigRegStatusType)FccuReg_GetStCfgRegLock(obj->regFccu);
}

FccuDrv_FakeStatusType FccuDrv_GetErrInjectStatus(FccuDrvType *obj)
{
    /* Get Error Inject status */
    return (FccuDrv_FakeStatusType)FccuReg_GetFakeFault(obj->regFccu);
}

FccuDrv_FsmStatusType FccuDrv_GetFsmStatus(FccuDrvType *obj)
{
    /* Get Current FSM status */
    return (FccuDrv_FsmStatusType)FccuReg_GetStFsm(obj->regFccu);
}

void FccuDrv_GetIrqStatus(FccuDrvType *obj, FccuDrv_irqStatusdType *irqStatus)
{
    /* Get Config Timeout Status */
    irqStatus->irqConfigStatus = FccuReg_GetIrqStCfgTO(obj->regFccu);

    /* Get Alarm Interrupt Status */
    irqStatus->irqAlarmStatus = FccuReg_GetIrqStAlarm(obj->regFccu);

    /* Get NMI Interrupt Status */
    irqStatus->irqNmiStatus = FccuReg_GetIrqStNmi(obj->regFccu);
}

void FccuDrv_AlarmIrqStatusClr(FccuDrvType *obj)
{
    /* Alarm Irq status clear */
    FccuReg_SetIrqStAlarm(obj->regFccu, FCCUDRV_ALARM_STS_CLEAR);
}

void FccuDrv_ClrConfigTimeoutStatus(FccuDrvType *obj)
{
    /* Clear CONFIG mode timeout irq status */
    FccuReg_SetIrqStCfgTO(obj->regFccu, FCCUDRV_CONFIG_IRQ_CLEAR_MASK);
}

uint32_t FccuDrv_GetFsmAlarmTmrValue(FccuDrvType *obj)
{
    /* Get FSM on Alarm status timer count value */
    return FccuReg_GetTmrAlarmCnt(obj->regFccu);
}

uint32_t FccuDrv_GetFsmConfigTmrValue(FccuDrvType *obj)
{
    /* Get FSM on Config status timer count value */
    return FccuReg_GetTmrCfgCnt(obj->regFccu);
}

uint32_t FccuDrv_GetEOutTmrValue(FccuDrvType *obj)
{
    /* Get Eout count value */
    return FccuReg_GetTmrEOutCnt(obj->regFccu);
}

bool FccuDrv_InitialToNormal(FccuDrvType *obj)
{
    bool                  res = true;
    FccuDrv_FsmStatusType fsm_status;
    FccuDrv_ChnCtrlType   chnCtrl = {0};

    /* Judgement FSM current status */
    fsm_status = FccuDrv_GetFsmStatus(obj);

    /* polyspace-begin DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */
    /* All status convert to initial status: Normal Mode */
    switch (fsm_status)
    {
        case FCCUDRV_FSM_NORMAL:
            /* do nothing */    
            break;

        case FCCUDRV_FSM_CONFIG:
            FccuDrv_SetOptFlowConfig2Normal(obj);
            fsm_status = FccuDrv_GetFsmStatus(obj);
            if (fsm_status != FCCUDRV_FSM_NORMAL)
            {
                res = false;
            }
            break;

        case FCCUDRV_FSM_ALARM:
            /* close all type of channel */
            FccuDrv_SetChnConfig(obj, &chnCtrl);
            /* FSM recover to Normal mode */
            res = FccuDrv_SetOpCtrl(obj, FCCUDRV_SEL_CTRL_OP15);
            break;

        case FCCUDRV_FSM_FAULT:
            /* close all type of channel */
            FccuDrv_SetChnConfig(obj, &chnCtrl);
            /* FSM recover to Normal mode */
            res = FccuDrv_SetOpCtrl(obj, FCCUDRV_SEL_CTRL_OP15);
            break;

        default:
            break;
    }
    /* polyspace-end DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */

    return res;
}
