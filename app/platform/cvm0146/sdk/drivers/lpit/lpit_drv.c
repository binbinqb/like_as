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

#include "lpit_drv.h"
#include "lpit_reg.h"

/*******************************************************************************
 * the defines
 ******************************************************************************/

/* Max period in count of all operation mode except for dual 16 bit periodic counter mode */
#define MAX_PERIOD_COUNT                    (0xFFFFFFFFU)

/* Max period in count of dual 16 bit periodic counter mode */
#define MAX_PERIOD_COUNT_IN_DUAL_16BIT_MODE (0x1FFFEU)

/* Max count of 16 bit */
#define MAX_PERIOD_COUNT_16_BIT             (0xFFFFU)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the functions
 ******************************************************************************/

void LpitDrv_Init(LpitDrvType *obj, struct _LpitRegType_ *reg)
{
    obj->reg = reg;
}

void LpitDrv_GetDefaultConfig(LpitDrv_ConfigType *userConfig)
{
    userConfig->enableRunInDebug    = false;
    userConfig->enableRunInLowPower = false;
}

void LpitDrv_Configure(LpitDrvType *obj, const LpitDrv_ConfigType *userConfig)
{
    /* Enables functional clock of LPIT module*/
    LpitReg_Enable(obj->reg);
    /* Sets LPIT operation in Debug and LowPower mode*/
    LpitReg_SetDebugModeCmd(obj->reg, userConfig->enableRunInDebug ? 1 : 0);
    LpitReg_SetLpModeCmd(obj->reg, userConfig->enableRunInLowPower ? 1 : 0);
}

void LpitDrv_GetDefaultChannelConfig(LpitDrv_ChannelConfigType *userChannelConfig)
{
    userChannelConfig->timerMode             = LPITDRV_PERIODIC_COUNTER;
    userChannelConfig->period                = 1000000U;
    userChannelConfig->triggerSource         = LPITDRV_TRIGGERSOURCE_EXTERNAL;
    userChannelConfig->triggerSelect         = 0U;
    userChannelConfig->enableReloadOnTrigger = false;
    userChannelConfig->enableStopOnInterrupt = false;
    userChannelConfig->enableStartOnTrigger  = false;
    userChannelConfig->chainChannel          = false;
    userChannelConfig->isInterruptEnabled    = true;
}

bool LpitDrv_ConfigureChannel(LpitDrvType *obj, uint8_t channel, const LpitDrv_ChannelConfigType *userChannelConfig)
{
    /* Checks channel range */
    if(channel >= LPIT_TMR_COUNT)
    {
        return false;
    }

    /* Setups the timer channel chaining  */
    LpitReg_SetTimerChannelChainCmd(obj->reg, channel, (uint8_t)userChannelConfig->chainChannel);
    /* Setups the timer channel operation mode */
    LpitReg_SetTimerChannelModeCmd(obj->reg, channel, (uint8_t)userChannelConfig->timerMode);

    /* Setups timer channel period in count unit */
    LpitReg_SetTimerPeriodByCount(obj->reg, channel, userChannelConfig->period);

    /* Setups the timer channel trigger source, trigger select, reload on trigger,
    stop on timeout, start on trigger and channel chaining */
    LpitReg_SetTriggerSourceCmd(obj->reg, channel, userChannelConfig->triggerSource);
    LpitReg_SetTriggerSelectCmd(obj->reg, channel, userChannelConfig->triggerSelect);
    LpitReg_SetReloadOnTriggerCmd(obj->reg, channel, userChannelConfig->enableReloadOnTrigger ? 1 : 0);
    LpitReg_SetStopOnInterruptCmd(obj->reg, channel, userChannelConfig->enableStopOnInterrupt ? 1 : 0);
    LpitReg_SetStartOnTriggerCmd(obj->reg, channel, userChannelConfig->enableStartOnTrigger ? 1 : 0);
    /* Setups interrupt generation for timer channel */
    if(userChannelConfig->isInterruptEnabled)
    {
        /* Enables interrupt generation */
        LpitReg_EnableInterruptTimerChannels(obj->reg, (uint32_t)1U << channel);
    }
    else
    {
        /* Disables interrupt generation */
        LpitReg_DisableInterruptTimerChannels(obj->reg, (uint32_t)1U << channel);
    }

    return true;
}

void LpitDrv_StartTimerChannels(LpitDrvType *obj, uint32_t mask)
{
    /* Checks the mask range */
    if(mask >= (1UL << LPIT_TMR_COUNT))
    {
        return;
    }
    /* Start timer channels */
    LpitReg_StartTimerChannels(obj->reg, mask);
}

void LpitDrv_StopTimerChannels(LpitDrvType *obj, uint32_t mask)
{
    /* Checks the mask range */
    if(mask >= (1UL << LPIT_TMR_COUNT))
    {
        return;
    }
    /* Stop timer channels */
    LpitReg_StopTimerChannels(obj->reg, mask);
}

void LpitDrv_SetTimerPeriodByCount(LpitDrvType *obj, uint8_t channel, uint32_t count)
{
    /* Checks the channel range */
    if(channel >= LPIT_TMR_COUNT)
    {
        return;
    }

    LpitReg_SetTimerPeriodByCount(obj->reg, channel, count);
}

void LpitDrv_SetTimerPeriodInDual16ModeByCount(LpitDrvType *obj, uint8_t channel, uint16_t periodHigh, uint16_t periodLow)
{
    /* Checks the channel range */
    if(channel >= LPIT_TMR_COUNT)
    {
        return;
    }

    uint32_t period = ((uint32_t)periodHigh << 16U) | periodLow;
    /* Sets the timer channel period in count unit */
    LpitReg_SetTimerPeriodByCount(obj->reg, channel, period);
}

bool LpitDrv_GetTimerPeriodByCount(const LpitDrvType *obj, uint8_t channel, uint32_t *period)
{
    /* Checks the channel range */
    if(channel >= LPIT_TMR_COUNT)
    {
        return false;
    }

    /* Gets current timer channel period by count.*/
    uint32_t currentPeriod = LpitReg_GetTimerPeriodByCount(obj->reg, channel);
    /* Gets current timer channel operation mode */
    if(LpitReg_GetTimerChannelModeCmd(obj->reg, channel) == LPITDRV_DUAL_PERIODIC_COUNTER)
    {
        /* Calculates the period for dual 16 bit periodic counter mode */
        currentPeriod = (currentPeriod >> 16U) + (currentPeriod & MAX_PERIOD_COUNT_16_BIT);
    }

    *period = currentPeriod;
    return true;
}

bool LpitDrv_GetCurrentTimerCount(const LpitDrvType *obj, uint8_t channel, uint32_t *time)
{
    /* Checks the channel range */
    if(channel >= LPIT_TMR_COUNT)
    {
        return false;
    }

    /* Gets current timer channel counting value */
    uint32_t currentTime = LpitReg_GetCurrentTimerCount(obj->reg, channel);
    /* Gets current timer channel operation mode */
    if(LpitReg_GetTimerChannelModeCmd(obj->reg, channel) == LPITDRV_DUAL_PERIODIC_COUNTER)
    {
        /* Calculates the current counting value for dual 16 bit periodic counter mode */
        currentTime = (currentTime >> 16U) + (currentTime & MAX_PERIOD_COUNT_16_BIT);
    }
    *time = currentTime;
    return true;
}

void LpitDrv_EnableTimerChannelInterrupt(LpitDrvType *obj, uint32_t mask)
{
    /* Checks the mask range */
    if(mask >= (1UL << LPIT_TMR_COUNT))
    {
        return;
    }
    /* Enable interrupt of timer channels */
    LpitReg_EnableInterruptTimerChannels(obj->reg, mask);
}

void LpitDrv_DisableTimerChannelInterrupt(LpitDrvType *obj, uint32_t mask)
{
    /* Checks the mask range */
    if(mask >= (1UL << LPIT_TMR_COUNT))
    {
        return;
    }
    /* Enable interrupt of timer channels */
    LpitReg_DisableInterruptTimerChannels(obj->reg, mask);
}

uint32_t LpitDrv_GetInterruptFlagTimerChannels(const LpitDrvType *obj, uint32_t mask)
{
    /* Checks the mask range */
    if(mask >= (1UL << LPIT_TMR_COUNT))
    {
        return 0;
    }
    /* Gets the interrupt flag for timer channels */
    return LpitReg_GetInterruptFlag(obj->reg, mask);
}

void LpitDrv_ClearInterruptFlagTimerChannels(LpitDrvType *obj, uint32_t mask)
{
    /* Checks the mask range */
    if(mask >= (1UL << LPIT_TMR_COUNT))
    {
        return;
    }
    /* Clears the interrupt flag for timer channels */
    LpitReg_ClearInterruptFlag(obj->reg, mask);
}
