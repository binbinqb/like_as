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

#include "cmu_drv.h"
#include "cmu_reg.h"

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

void CmuDrv_Init(CmuDrvType *obj, struct _CmuRegType_ *reg)
{
    obj->reg = reg;
}

void CmuDrv_Configure(CmuDrvType *obj, const CmuDrv_ConfigType *userConfig)
{
    /* Set referency frequency cnt */
    CmuReg_SetRefCnt(obj->reg, userConfig->refClkCnt);
    /* Set the high threshold value */
    CmuReg_SetFreqHighRefValue(obj->reg, userConfig->highRefFreq);
    /* Set the low threshold value */
    CmuReg_SetFreqLowRefValue(obj->reg, userConfig->lowRefFreq);
    /* Set high event state */
    CmuReg_SetFreqHighEventState(obj->reg, (uint8_t)userConfig->highFreqEventSt);
    /* Set low event state */
    CmuReg_SetFreqLowEventState(obj->reg, (uint8_t)userConfig->lowFreqEventSt);
}

void CmuDrv_GetConfig(const CmuDrvType *obj, CmuDrv_ConfigType *userConfig)
{
    /* Get referency frequency cnt */
    userConfig->refClkCnt = CmuReg_GetRefCnt(obj->reg);
    /* Get the high threshold value */
    userConfig->highRefFreq = CmuReg_GetFreqHighRefValue(obj->reg);
    /* Get the low threshold value */
    userConfig->lowRefFreq = CmuReg_GetFreqLowRefValue(obj->reg);
    /* Get high event state */
    userConfig->highFreqEventSt = (CmuDrv_EventStateType)CmuReg_GetFreqHighEventState(obj->reg);
    /* Get low event state */
    userConfig->lowFreqEventSt = (CmuDrv_EventStateType)CmuReg_GetFreqLowEventState(obj->reg);
}

void CmuDrv_GetDefaultConfig(CmuDrv_ConfigType *userConfig)
{
    /* Get referency frequency cnt */
    userConfig->refClkCnt = 0U;
    /* Get the high threshold value */
    userConfig->highRefFreq = 0U;
    /* Get the low threshold value */
    userConfig->lowRefFreq = 0U;
    /* Get high event state */
    userConfig->highFreqEventSt = CMUDRV_DISABLE_INT_AND_RST;
    /* Get low event state */
    userConfig->lowFreqEventSt = CMUDRV_DISABLE_INT_AND_RST;
}

bool CmuDrv_IsFreqCheckEnable(const CmuDrvType *obj)
{
    /* Get CMU enable state */
    return (bool)(CmuReg_GetEnable(obj->reg));
}

void CmuDrv_EnableFreqCheck(const CmuDrvType *obj, bool enable)
{
    /* Set CMU enable state */
    CmuReg_SetEnable(obj->reg, enable);
}

bool CmuDrv_IsCmuRun(const CmuDrvType *obj)
{
    /* Get CMU run state */
    return (bool)(CmuReg_GetRunStatus(obj->reg));
}

bool CmuDrv_IsFreqHighEventAcvt(const CmuDrvType *obj)
{
    /* Get the frequency high event flag */
    return (bool)(CmuReg_GetFreqHighEventFlag(obj->reg));
}

void CmuDrv_ClearFreqHighEventFlag(CmuDrvType *obj)
{
    /* Clear the frequency high event flag */
    CmuReg_ClearFreqHighEventFlag(obj->reg);
}

bool CmuDrv_IsFreqLowEventAcvt(const CmuDrvType *obj)
{
    /* Get the frequency low event flag */
    return (bool)(CmuReg_GetFreqLowEventFlag(obj->reg));
}

void CmuDrv_ClearFreqLowEventFlag(CmuDrvType *obj)
{
    /* Clear the frequency low event flag */
    CmuReg_ClearFreqLowEventFlag(obj->reg);
}
