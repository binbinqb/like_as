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

#include "lptmr_drv.h"
#include "lptmr_reg.h"

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
void LptmrDrv_Init(LptmrDrvType *obj, struct _LptmrRegType_ *reg)
{
    obj->reg = reg;
}

void LptmrDrv_GetConfigure(LptmrDrvType *obj, LptmrDrv_ConfigType *userConfig)
{
    /* Get the work mode of LPTMR */
    userConfig->workMode = (LptmrDrv_WorkModeType)LptmrReg_GetWorkMode(obj->reg);
    /* Get the Free Running state */
    userConfig->freeRun = LptmrReg_GetFreeRunning(obj->reg);
    /* Get Pin Polarity for Pulse Counter Mode */
    userConfig->pinPolarity = (LptmrDrv_PinPolarityType)LptmrReg_GetPinPolarity(obj->reg);
    /* Get the Pin selection for Pulse Counter Mode */
    userConfig->pinSelect = (LptmrDrv_PinSelectType)LptmrReg_GetPinSelect(obj->reg);
    /* Get the Interrupt Enable state */
    userConfig->interruptEnable = LptmrReg_GetInterruptEnable(obj->reg);
    /* Get the DMA Request Enable Flag state */
    userConfig->dmaRequest = LptmrReg_GetDmaRequest(obj->reg);
    /* Get the Prescaler/Glitch Filter Bypass enable state */
    userConfig->bypassPrescaler = LptmrReg_GetBypass(obj->reg);
    /* Get the Prescaler/Glitch Filter divider value */
    userConfig->prescaler = (LptmrDrv_PrescaleType)LptmrReg_GetPrescaler(obj->reg);
    /* Get the Prescaler/Glitch Filter Bypass enable state */
    userConfig->compareValue = LptmrReg_GetCompareValue(obj->reg);
}

void LptmrDrv_GetDefaultConfig(LptmrDrv_ConfigType *userConfig)
{
    /* General parameters */
    userConfig->dmaRequest      = false;
    userConfig->interruptEnable = false;
    userConfig->freeRun         = false;
    userConfig->workMode        = LPTMRDRV_WORKMODE_TIMER;

    /* Counter parameters */
    userConfig->prescaler       = LPTMRDRV_PRESCALE_2;
    userConfig->bypassPrescaler = false;
    userConfig->compareValue    = 0u;

    /* Pulse Counter specific parameters */
    userConfig->pinSelect   = LPTMRDRV_PINSELECT_INPUT0;
    userConfig->pinPolarity = LPTMRDRV_PINPOLARITY_RISING;
}

void LptmrDrv_Configure(LptmrDrvType *obj, const LptmrDrv_ConfigType *userConfig)
{
    /* Disable LPTMR before configure */
    LptmrReg_SetEnable(obj->reg, false);
    /* Set the work mode of LPTMR */
    LptmrReg_SetWorkMode(obj->reg, (uint8_t)userConfig->workMode);
    /* Set the Free Running state */
    LptmrReg_SetFreeRunning(obj->reg, userConfig->freeRun);
    /* Set Pin Polarity for Pulse Counter Mode */
    LptmrReg_SetPinPolarity(obj->reg, (uint8_t)userConfig->pinPolarity);
    /* Set the Pin selection for Pulse Counter Mode */
    LptmrReg_SetPinSelect(obj->reg, (uint8_t)userConfig->pinSelect);
    /* Set the Interrupt Enable state */
    LptmrReg_SetInterrupt(obj->reg, userConfig->interruptEnable);
    /* Set the DMA Request Enable Flag state */
    LptmrReg_SetDmaRequest(obj->reg, userConfig->dmaRequest);
    /* Set the Prescaler/Glitch Filter Bypass enable state */
    LptmrReg_SetBypass(obj->reg, userConfig->bypassPrescaler);
    /* Set the Prescaler/Glitch Filter divider value */
    LptmrReg_SetPrescaler(obj->reg, (uint8_t)userConfig->prescaler);
    /* Set the Prescaler/Glitch Filter Bypass enable state */
    LptmrReg_SetCompareValue(obj->reg, userConfig->compareValue);
}

bool LptmrDrv_IsEnable(LptmrDrvType *obj)
{
    /* Get the Enable state */
    return (bool)(LptmrReg_GetEnable(obj->reg));
}

void LptmrDrv_Enable(LptmrDrvType *obj, bool enable)
{
    /* Set the Enable state */
    LptmrReg_SetEnable(obj->reg, enable);
}

bool LptmrDrv_IsCompareEventAcvt(LptmrDrvType *obj)
{
    /* Get the Compare Flag state */
    return (bool)(LptmrReg_GetCompareFlag(obj->reg));
}

void LptmrDrv_ClearCompareFlag(LptmrDrvType *obj)
{
    /* Clear the Compare Flag */
    LptmrReg_ClearCompareFlag(obj->reg);
}
