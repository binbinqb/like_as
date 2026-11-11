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
#include "sim_reg.h"
#include "i2ss_drv.h"
#include "i2ss_reg.h"

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
 * the function prototypes
 ******************************************************************************/

void I2ssDrv_Init(I2ssDrvType *obj, struct _I2ssRegType_ *reg1, struct _SimRegType_ *reg2)
{
    obj->regI2ss = reg1;
    obj->regSim  = reg2;
}

void I2ssDrv_GetDefaultConfig(I2ssDrv_ConfigType *userConfig)
{
    userConfig->rxFifoTriggerLevel   = 3;
    userConfig->rxFifoEmptyIntMask   = 1;
    userConfig->rxFifoOverrunIntMask = 1;
}

void I2ssDrv_Config(I2ssDrvType *obj, const I2ssDrv_ConfigType *userConfig)
{
    /* select I2S as master mode */
    SimReg_SetI2sMode(obj->regSim, 0);
    /* enable I2S module */
    I2ssReg_SetIerEn(obj->regI2ss, 1);
    /* set FIFO threshold */
    I2ssReg_SetRff0RxChfr0(obj->regI2ss, userConfig->rxFifoTriggerLevel);
    /* config interrupt mask for fifo empty */
    I2ssReg_SetImr0RxDam(obj->regI2ss, userConfig->rxFifoEmptyIntMask);
    /* config interrupt mask for fifo overrun */
    I2ssReg_SetImr0RxFom(obj->regI2ss, userConfig->rxFifoOverrunIntMask);
    /* enable rx block */
    I2ssReg_SetIrerRxEn(obj->regI2ss, 1);
    /* enable rx channel0 */
    I2ssReg_SetRer0Ch0(obj->regI2ss, 1);
}

void I2ssDrv_ReadFifoByDma(I2ssDrvType *obj, uint32_t *data, uint8_t len)
{
    for(uint8_t i = 0; i < len; i++)
    {
        data[i] = I2ssReg_GetRxDmaRxDma(obj->regI2ss);
    }
}

void I2ssDrv_ReadFifoByBuffer(I2ssDrvType *obj, uint32_t *data, uint8_t len)
{
    for(uint8_t i = 0; i < len; i += 2)
    {
        data[i]     = I2ssReg_GetLrbr0Lrbr0(obj->regI2ss);
        data[i + 1] = I2ssReg_GetRrbr0Rrbr0(obj->regI2ss);
    }
}

void I2ssDrv_FlushRxFifo(I2ssDrvType *obj)
{
    /* flush rx fifo 0 */
    I2ssReg_SetRff0RxChfr0(obj->regI2ss, 1);
}

bool I2ssDrv_GetFifoOverrunFlag(I2ssDrvType *obj)
{
    bool flag = 0;
    flag      = I2ssReg_GetIsr0RxFo(obj->regI2ss);
    return flag;
}

bool I2ssDrv_GetFifoLevelTrigFlag(I2ssDrvType *obj)
{
    bool flag = 0;
    flag      = I2ssReg_GetIsr0RxDa(obj->regI2ss);
    return flag;
}
