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

#include "pwmlite_drv.h"
#include "pwmlite_reg.h"
#include "sim_reg.h"

/*******************************************************************************
 * the defines
 ******************************************************************************/

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

typedef void (*setPwmLiteMuxFunc)(SimRegType *obj, uint8_t value);

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the constants
 ******************************************************************************/

const setPwmLiteMuxFunc c_pwmLiteMuxFuncTable[PWMLITEDRV_MUX_PAD_PWM_NUM] = {
    SimReg_SetPwmCtrl0PwmFunc0,
    SimReg_SetPwmCtrl0PwmFunc1,
    SimReg_SetPwmCtrl0PwmFunc2,
    SimReg_SetPwmCtrl0PwmFunc3,

    SimReg_SetPwmCtrl1PwmFunc4,
    SimReg_SetPwmCtrl1PwmFunc5,
    SimReg_SetPwmCtrl1PwmFunc6,
    SimReg_SetPwmCtrl1PwmFunc7,
};

const PwmLiteDrv_PwmMuxPadNumType c_pwmLiteMuxPadIndex[] = {
    PWMLITEDRV_MUX_PAD_PWM0,
    PWMLITEDRV_MUX_PAD_PWM1,
    PWMLITEDRV_MUX_PAD_PWM2,
    PWMLITEDRV_MUX_PAD_PWM3,
    PWMLITEDRV_MUX_PAD_PWM4,
    PWMLITEDRV_MUX_PAD_PWM5,
    PWMLITEDRV_MUX_PAD_PWM6,
    PWMLITEDRV_MUX_PAD_PWM7,
};
#define PWMLITE_PWMMUXINDEX_MAX (sizeof(c_pwmLiteMuxPadIndex) / sizeof(PwmLiteDrv_PwmMuxPadNumType))

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

void PwmLiteDrv_Init(PwmLiteDrvType *obj, struct _PwmLiteRegType_ *pwmLiteReg, struct _SimRegType_ *simReg)
{
    uint16_t i;

    obj->pwmLiteReg = pwmLiteReg;
    obj->simReg     = simReg;
    /* disable the mux pwm output */
    for(i = 0; i < PWMLITE_PWMMUXINDEX_MAX; i++)
    {
        PwmLiteDrv_OutputMux(obj, PWMLITEDRV_MUX_PWM_CH_INVALID, c_pwmLiteMuxPadIndex[i]);
    }
}

void PwmLiteDrv_ModuleConfig(PwmLiteDrvType *obj, const PwmLiteDrv_ModuleConfigType *userConfig)
{
    /* disable the module first */
    PwmLiteDrv_DisableModule(obj);
    /* Set the pwm period value */
    PwmLiteReg_SetPrdPeriod(obj->pwmLiteReg, userConfig->period);
    /* Set the syne type of the module */
    PwmLiteReg_SetCtrlSyncMode(obj->pwmLiteReg, userConfig->syncType);
}

void PwmLiteDrv_GetDefaultModuleConfig(PwmLiteDrv_ModuleConfigType *ModuleConfigType)
{
    ModuleConfigType->period   = 0;
    ModuleConfigType->syncType = PWMLITEDRV_SYNC_AT_RUNNING;
}

void PwmLiteDrv_ConfigChannel(PwmLiteDrvType *obj, uint8_t channel, const PwmLiteDrv_ChannelConfigType *userConfig)
{
    if(channel >= PWMLITEDRV_PWM_CH_NUM)
    {
        return;
    }
    /* disable the module first */
    PwmLiteDrv_DisableModule(obj);
    /* Set the pwm channels to target pad channel through SIM */
    PwmLiteDrv_OutputMux(obj, userConfig->pwmMuxType.channelNumber, userConfig->pwmMuxType.padNumber);
    /* Set pwm threshold0/1 value */
    PwmLiteDrv_UpdatePwmThresholdAtRunning(obj, channel, userConfig->threshold0, userConfig->threshold1);
    /* Set pwm threshold0 behavior */
    PwmLiteReg_SetChCtrl0(obj->pwmLiteReg, channel, userConfig->behavior0);
    /* Set pwm threshold1 behavior */
    PwmLiteReg_SetChCtrl1(obj->pwmLiteReg, channel, userConfig->behavior1);
}

void PwmLiteDrv_GetDefaultChannelConfig(PwmLiteDrv_ChannelConfigType *ChannelConfigType)
{
    ChannelConfigType->behavior0  = PWMLITEDRV_TOGGLE_AT_REACH;
    ChannelConfigType->behavior1  = PWMLITEDRV_TOGGLE_AT_REACH;
    ChannelConfigType->threshold0 = 0;
    ChannelConfigType->threshold1 = 0;
}

void PwmLiteDrv_EnableModule(PwmLiteDrvType *obj)
{
    PwmLiteReg_SetCtrlEn(obj->pwmLiteReg, 1);
}

void PwmLiteDrv_DisableModule(PwmLiteDrvType *obj)
{
    PwmLiteReg_SetCtrlEn(obj->pwmLiteReg, 0);
}

void PwmLiteDrv_Resume(PwmLiteDrvType *obj)
{
    PwmLiteReg_SetStopPause(obj->pwmLiteReg, 0);
}

void PwmLiteDrv_Pause(PwmLiteDrvType *obj)
{
    PwmLiteReg_SetStopPause(obj->pwmLiteReg, 1);
}

void PwmLiteDrv_UpdatePwmThresholdAtRunning(PwmLiteDrvType *obj, uint8_t channel, uint32_t threshold0, uint32_t threshold1)
{
    uint32_t prd = PwmLiteReg_GetPrdPeriod(obj->pwmLiteReg);
    if(threshold1 == threshold0) /* DUTY: 0% */
    {
        /* Set pwm threshold0 value */
        PwmLiteReg_SetChThr0(obj->pwmLiteReg, channel, 0x1u);
        /* Set pwm threshold1 value */
        PwmLiteReg_SetChThr1(obj->pwmLiteReg, channel, 0x1u);
    }
    else if(threshold1 - threshold0 == prd) /* DUTY: 100% */
    {
        /* Set pwm threshold0 value */
        PwmLiteReg_SetChThr0(obj->pwmLiteReg, channel, 0x1u);
        /* Set pwm threshold1 value */
        PwmLiteReg_SetChThr1(obj->pwmLiteReg, channel, (prd + 0x1u));
    }
    else /* DUTY: 0~100% */
    {
        /* Set pwm threshold0 value */
        PwmLiteReg_SetChThr0(obj->pwmLiteReg, channel, (threshold0 + 0x1u));
        /* Set pwm threshold1 value */
        PwmLiteReg_SetChThr1(obj->pwmLiteReg, channel, (threshold1 + 0x1u));
    }
}

void PwmLiteDrv_UpdatePwmThresholdAtSync(PwmLiteDrvType *obj, uint8_t channel, uint32_t threshold0, uint32_t threshold1)
{
    uint32_t prd = PwmLiteReg_GetPrdPeriod(obj->pwmLiteReg);
    if(threshold1 == threshold0) /* DUTY: 0% */
    {
        /* Set pwm threshold0 value */
        PwmLiteReg_SetChThr0(obj->pwmLiteReg, channel, 0x1u);
        /* Set pwm threshold1 value */
        PwmLiteReg_SetChThr1(obj->pwmLiteReg, channel, 0x1u);
    }
    else if(threshold1 - threshold0 == prd) /* DUTY: 100% */
    {
        /* Set pwm threshold0 value */
        PwmLiteReg_SetChThr0(obj->pwmLiteReg, channel, 0x1u);
        /* Set pwm threshold1 value */
        PwmLiteReg_SetChThr1(obj->pwmLiteReg, channel, (prd + 0x1u));
    }
    else /* DUTY: 0~100% */
    {
        /* Set pwm threshold0 value */
        PwmLiteReg_SetChThr0(obj->pwmLiteReg, channel, (threshold0 + 0x1u));
        /* Set pwm threshold1 value */
        PwmLiteReg_SetChThr1(obj->pwmLiteReg, channel, (threshold1 + 0x1u));
    }
    PwmLiteDrv_TrigSync(obj);
}

void PwmLiteDrv_OutputMux(PwmLiteDrvType *obj, PwmLiteDrv_PwmMuxChannelType channel, PwmLiteDrv_PwmMuxPadNumType number)
{
    if(number >= PWMLITEDRV_MUX_PAD_PWM_NUM)
    {
        return;
    }
    /* select the correct path through target channel number */
    c_pwmLiteMuxFuncTable[number](obj->simReg, (uint8_t)channel);
}

uint8_t PwmLiteDrv_GetSyncResult(PwmLiteDrvType *obj)
{
    uint8_t result = 0;
    result         = PwmLiteReg_GetSyncStatus(obj->pwmLiteReg);
    return result;
}

void PwmLiteDrv_TrigSync(PwmLiteDrvType *obj)
{
    PwmLiteReg_SetSyncStart(obj->pwmLiteReg, 1);
}
