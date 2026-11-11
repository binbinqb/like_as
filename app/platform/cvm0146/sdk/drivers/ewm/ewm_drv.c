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

#include "ewm_drv.h"
#include "ewm_reg.h"

/*******************************************************************************
 * the defines
 ******************************************************************************/

/* EWM Compare High register maximum value */
#define EWMDRV_CMPH_MAX_VALUE (0xFEU)

/* EWM Service key */
#define EWMDRV_SERVICE_KEY    (0x2CB4)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the functions
 ******************************************************************************/

void EwmDrv_Init(EwmDrvType *obj, struct _EwmRegType_ *reg)
{
    obj->reg = reg;
}

void EwmDrv_GetDefaultConfig(EwmDrv_ConfigType *userConfig)
{
    /* Disable interrupts */
    userConfig->interruptEnable = false;
    /* Input pin enabled and configured to assert on logic 0 */
    userConfig->assertLogic = EWMDRV_IN_ASSERT_ON_LOGIC_ZERO;
    /* Maximum prescaler */
    userConfig->prescaler = 255U;
    /* Maximum service window */
    userConfig->compareHigh = EWMDRV_CMPH_MAX_VALUE;
    userConfig->compareLow  = 0;
}

void EwmDrv_Configure(EwmDrvType *obj, const EwmDrv_ConfigType *userConfig)
{
    /* Check if the EWM instance is already enabled or if the windows values are not correct */
    if(EwmReg_GetCtrlEwmEn(obj->reg) == 1
       || userConfig->compareHigh <= userConfig->compareLow
       || userConfig->compareHigh > EWMDRV_CMPH_MAX_VALUE)
    {
        return;
    }

    /* Set clock prescaler */
    EwmReg_SetClkPrescalerDiv(obj->reg, userConfig->prescaler);
    /* Set compare high and low values */
    EwmReg_SetCmpHCompareH(obj->reg, userConfig->compareHigh);
    EwmReg_SetCmpLCompareL(obj->reg, userConfig->compareLow);

    uint32_t ctrlRegValue = 0U;

    ctrlRegValue |= (userConfig->interruptEnable ? EWM_CTRL_INTEN_MASK : 0);
    /* Depending how the input pin is configured set the values into the
     * temporary variable
     */
    switch(userConfig->assertLogic)
    {
    case EWMDRV_IN_ASSERT_ON_LOGIC_ZERO:
        /* Input pin enabled, Input asserted on logic 0 */
        ctrlRegValue |= EWM_CTRL_INEN_MASK;
        break;
    case EWMDRV_IN_ASSERT_ON_LOGIC_ONE:
        /* Input pin enabled, Input asserted on logic 1 */
        ctrlRegValue |= (uint8_t)(EWM_CTRL_INEN_MASK | EWM_CTRL_ASSIN_MASK);
        break;
    case EWMDRV_IN_ASSERT_DISABLED:
    default:
        /* Input pin disabled */
        break;
    }
    /* Enable EWM */
    ctrlRegValue |= EWM_CTRL_EWMEN_MASK;

    EwmReg_SetCtrl(obj->reg, ctrlRegValue);
}

void EwmDrv_ClearInterruptFlag(EwmDrvType *obj)
{
    EwmReg_SetCtrlIntEn(obj->reg, 0);
}

void EwmDrv_Refresh(EwmDrvType *obj)
{
    EwmReg_SetService(obj->reg, EWMDRV_SERVICE_KEY);
}

EwmDrv_InAssertLogicType EwmDrv_GetInputPinAssertLogic(const EwmDrvType *obj)
{
    EwmDrv_InAssertLogicType retval = EWMDRV_IN_ASSERT_DISABLED;

    if(EwmReg_GetCtrlInEn(obj->reg) == 1)
    {
        if(EwmReg_GetCtrlAssIn(obj->reg) == 1)
        {
            retval = EWMDRV_IN_ASSERT_ON_LOGIC_ONE;
        }
        else
        {
            retval = EWMDRV_IN_ASSERT_ON_LOGIC_ZERO;
        }
    }
    return retval;
}
