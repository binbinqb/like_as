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

#include "wdg_drv.h"
#include "wdg_reg.h"

/*******************************************************************************
 * the defines
 ******************************************************************************/

#define WDGDRV_REFRESH_VALUE        (0xB480A602U) /* refresh wdg counter value */
#define WDGDRV_UNLOCK_VALUE         (0xD928C520U) /* unlock wdg reg */
#define WDGDRV_TO_RESET_VALUE       (0xFFFFU)     /* the wdg TOVAL configuration default value */
#define WDGDRV_WIN_RESET_VALUE      (0x0U)        /* the wdg WIN configuration default value */
#define WDGDRV_CLEAR_INT_FLAG_VALUE (0x1U)        /* W1C, the wdg clear interrupt flag value */
#define WDGDRV_CLEAR_TST_FLAG_VALUE (0x1U)        /* W1C, the wdg clear test flag value */

/* Unlock WDG register */
#define WDGDRV_UNLOCK(x)            ((x)->CNT = WDGDRV_UNLOCK_VALUE)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the functions
 ******************************************************************************/

void WdgDrv_Init(WdgDrvType *obj, struct _WdgRegType_ *reg)
{
    obj->reg = reg;
}

void WdgDrv_Configure(WdgDrvType *obj, const WdgDrv_ConfigureType *userConfig)
{
    uint8_t enable = WdgReg_IsEnabled(obj->reg);
    uint8_t update = WdgReg_IsEnabledUpdate(obj->reg);
    uint8_t csd    = WdgReg_IsDoneConfigSync(obj->reg);

    if((enable == 0x0u) && (update == 0x01u) && (csd == 0x01u))
    {
        /* Clear the bits used for configuration */
        WdgRegType preReg = {0};
        preReg.CS &= ~(WDG_CS_CLK_MASK
                       | WDG_CS_WIN_MASK
                       | WDG_CS_PRES_MASK
                       | WDG_CS_INTR_MASK
                       | WDG_CS_UPDATE_MASK
                       | WDG_CS_DEBUG_MASK
                       | WDG_CS_STOP_MASK);
        /* pre-configuration: Construct CS register new value */
        WdgReg_SetClockSource(&preReg, (uint8_t)userConfig->clkSource);
        WdgReg_EnableWinMode(&preReg, userConfig->winEnable);
        WdgReg_EnablePrescaler(&preReg, userConfig->prescalerEnable);
        WdgReg_EnableInterrupt(&preReg, userConfig->intEnable);
        WdgReg_EnableUpdate(&preReg, userConfig->updateEnable);
        WdgReg_EnableDebugMode(&preReg, userConfig->debugModeEnable);
        WdgReg_EnableStopMode(&preReg, userConfig->stopModeEnable);
        WdgReg_ClearInterruptFlag(&preReg, userConfig->flag);
        WdgReg_Enable(&preReg, userConfig->enable);
        if(userConfig->tstRstFlg)
        {
            WdgReg_ClrTesRstFlag(&preReg);
        }
        WdgReg_EnableTstRst(&preReg, userConfig->tstRstEn);
        WdgReg_SetTestMode(&preReg, (uint8_t)userConfig->testMode);
        /* configuration: Construct register new value */
        WDGDRV_UNLOCK(obj->reg);
        obj->reg->CS    = preReg.CS;
        obj->reg->TOVAL = userConfig->timeoutValue;
        while(!WdgReg_IsSuccessConfig(obj->reg))
        {
            /* Wait until the reconfiguration successful */
        }
        while(!WdgReg_IsDoneConfigSync(obj->reg))
        {
            /* Wait until the synchronization of new configuration done */
        }
        if(userConfig->winEnable)
        {
            WdgReg_SetCntVal(obj->reg, WDGDRV_REFRESH_VALUE);
            WDGDRV_UNLOCK(obj->reg);
            obj->reg->WIN = userConfig->windowValue;
            while(!WdgReg_IsDoneConfigSync(obj->reg))
            {
                /* Wait until the synchronization of new configuration done */
            }
        }
    }
}

void WdgDrv_GetDefaultConfig(WdgDrv_ConfigureType *userConfig)
{
    userConfig->clkSource       = WDGDRV_CLK_SRC_LPO128K;
    userConfig->winEnable       = 0x0u;
    userConfig->flag            = WDGDRV_CLEAR_INT_FLAG_VALUE;
    userConfig->prescalerEnable = 0x0u;
    userConfig->enable          = 0x0u;
    userConfig->intEnable       = 0x0u;
    userConfig->updateEnable    = 0x1u;
    userConfig->debugModeEnable = 0x0u;
    userConfig->stopModeEnable  = 0x0u;
    userConfig->timeoutValue    = WDGDRV_TO_RESET_VALUE;
    userConfig->windowValue     = WDGDRV_WIN_RESET_VALUE;
    userConfig->testMode        = WDGDRV_TEST_MODE_DISABLED;
    userConfig->tstRstFlg       = WDGDRV_CLEAR_TST_FLAG_VALUE;
    userConfig->tstRstEn        = 0x0u;
}

void WdgDrv_GetCurrentConfig(const WdgDrvType *obj, WdgDrv_ConfigureType *userConfig)
{
    userConfig->clkSource       = (WdgDrv_ClkSrcType)WdgReg_GetClockSource(obj->reg);
    userConfig->winEnable       = WdgReg_IsEnabledWinMode(obj->reg);
    userConfig->flag            = WdgReg_GetInterruptFlag(obj->reg);
    userConfig->prescalerEnable = WdgReg_IsEnabledPrescaler(obj->reg);
    userConfig->enable          = WdgReg_IsEnabled(obj->reg);
    userConfig->intEnable       = WdgReg_IsEnabledInterrupt(obj->reg);
    userConfig->updateEnable    = WdgReg_IsEnabledUpdate(obj->reg);
    userConfig->debugModeEnable = WdgReg_IsEnabledDebugMode(obj->reg);
    userConfig->stopModeEnable  = WdgReg_IsEnabledStopMode(obj->reg);
    userConfig->timeoutValue    = WdgReg_GetToval(obj->reg);
    userConfig->windowValue     = WdgReg_GetWinVal(obj->reg);
    userConfig->testMode        = (WdgDrv_TestModeType)WdgReg_GetTestModeStatus(obj->reg);
    userConfig->tstRstFlg       = WdgReg_GetTesRstFlag(obj->reg);
    userConfig->tstRstEn        = WdgReg_IsEnabledTstRst(obj->reg);
}

void WdgDrv_Enable(WdgDrvType *obj)
{
    uint8_t update = WdgReg_IsEnabledUpdate(obj->reg);
    /* If allowed reconfigures WDG */
    if(update == 0x01u)
    {
        uint32_t csTmp = obj->reg->CS;
        csTmp &= ~(WDG_CS_EN_MASK);
        csTmp |= (((uint32_t)(((uint32_t)(true)) << WDG_CS_EN_SHIFT)) & WDG_CS_EN_MASK);
        WDGDRV_UNLOCK(obj->reg);
        obj->reg->CS = csTmp;
        while(WdgReg_IsUnlocked(obj->reg))
        {
            /* Wait until the unlock window closes */
        }
    }
}

void WdgDrv_Disable(WdgDrvType *obj)
{
    uint8_t update = WdgReg_IsEnabledUpdate(obj->reg);
    /* If allowed reconfigures WDG */
    if(update == 0x01u)
    {
        WDGDRV_UNLOCK(obj->reg);
        obj->reg->CS &= ~((uint32_t)WDG_CS_EN_MASK);
        /* reset timeout value for the WDG */
        obj->reg->TOVAL = WDGDRV_TO_RESET_VALUE;
        while(WdgReg_IsUnlocked(obj->reg))
        {
            /* Wait until the unlock window closes */
        }
        while(!WdgReg_IsDoneConfigSync(obj->reg))
        {
            /* Wait until the synchronization of new configuration done */
        }
    }
}

void WdgDrv_SetInt(WdgDrvType *obj, bool enable)
{
    uint8_t update = WdgReg_IsEnabledUpdate(obj->reg);
    /* If allowed reconfigures WDG */
    if(update == 0x01u)
    {
        uint32_t csTmp = obj->reg->CS;
        csTmp &= ~(WDG_CS_INTR_MASK);
        csTmp |= (((uint32_t)(((uint32_t)(enable)) << WDG_CS_INTR_SHIFT)) & WDG_CS_INTR_MASK);
        WDGDRV_UNLOCK(obj->reg);
        obj->reg->CS = csTmp;
        while(WdgReg_IsUnlocked(obj->reg))
        {
            /* Wait until the unlock window closes */
        }
    }
}

void WdgDrv_ClearIntFlag(WdgDrvType *obj)
{
    /* Clear interrupt flag of the WDG, W1C*/
    WDGDRV_UNLOCK(obj->reg);
    WdgReg_ClearInterruptFlag(obj->reg, WDGDRV_CLEAR_INT_FLAG_VALUE);
}

void WdgDrv_Refresh(WdgDrvType *obj)
{
    WdgReg_SetCntVal(obj->reg, WDGDRV_REFRESH_VALUE);
}

uint32_t WdgDrv_GetCnt(const WdgDrvType *obj)
{
    return WdgReg_GetCntVal(obj->reg);
}

void WdgDrv_SetWindow(WdgDrvType *obj, uint32_t winVal, bool enable)
{
    uint8_t update = WdgReg_IsEnabledUpdate(obj->reg);
    /* If allowed reconfigures WDG */
    if(update == 0x01u)
    {
        uint32_t csTmp = obj->reg->CS;
        csTmp &= ~(WDG_CS_WIN_MASK);
        csTmp |= (((uint32_t)(((uint32_t)(enable)) << WDG_CS_WIN_SHIFT)) & WDG_CS_WIN_MASK);
        WDGDRV_UNLOCK(obj->reg);
        obj->reg->CS = csTmp;
        /* Set window value for the WDG */
        obj->reg->WIN = winVal;
        while(WdgReg_IsUnlocked(obj->reg))
        {
            /* Wait until the unlock window closes */
        }
    }
}

void WdgDrv_SetStopMode(WdgDrvType *obj, bool enable)
{
    uint8_t update = WdgReg_IsEnabledUpdate(obj->reg);
    /* If allowed reconfigures WDG */
    if(update == 0x01u)
    {
        uint32_t csTmp = obj->reg->CS;
        csTmp &= ~(WDG_CS_STOP_MASK);
        csTmp |= (((uint32_t)(((uint32_t)(enable)) << WDG_CS_STOP_SHIFT)) & WDG_CS_STOP_MASK);
        WDGDRV_UNLOCK(obj->reg);
        /* Set stop mode */
        obj->reg->CS = csTmp;
        while(WdgReg_IsUnlocked(obj->reg))
        {
            /* Wait until the unlock window closes */
        }
    }
}

void WdgDrv_SetTimeout(WdgDrvType *obj, uint32_t toval)
{
    uint8_t update = WdgReg_IsEnabledUpdate(obj->reg);
    /* If allowed reconfigures WDG */
    if(update == 0x01u)
    {
        WDGDRV_UNLOCK(obj->reg);
        /* Set timeout value for the WDG */
        WdgReg_SetToval(obj->reg, toval);
        while(WdgReg_IsUnlocked(obj->reg))
        {
            /* Wait until the unlock window closes */
        }
    }
}

void WdgDrv_SetTestMode(WdgDrvType *obj, WdgDrv_TestModeType type)
{
    uint8_t update = WdgReg_IsEnabledUpdate(obj->reg);
    /* If allowed reconfigures WDG */
    if(update == 0x01u)
    {
        uint32_t csTmp = obj->reg->CS;
        csTmp &= ~(WDG_TST_MASK | WDG_CS_EN_MASK);
        csTmp |= (((uint32_t)(((uint32_t)(type)) << WDG_TST_SHIFT)) & WDG_TST_MASK);
        csTmp |= (((uint32_t)(((uint32_t)(1)) << WDG_CS_EN_SHIFT)) & WDG_CS_EN_MASK);
        WDGDRV_UNLOCK(obj->reg);
        /* Set test mode */
        obj->reg->CS = csTmp;
        while(WdgReg_IsUnlocked(obj->reg))
        {
            /* Wait until the unlock window closes */
        }
    }
}

WdgDrv_TestModeType WdgDrv_GetTestMode(const WdgDrvType *obj)
{
    /* Get test mode configuration type */
    uint8_t testModeType = WdgReg_GetTestModeStatus(obj->reg);
    /* Gets test mode */
    return ((WdgDrv_TestModeType)testModeType);
}
