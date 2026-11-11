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
#include "i2sm_drv.h"
#include "i2sm_reg.h"

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

void I2smDrv_Init(I2smDrvType *obj, struct _I2smRegType_ *reg1, struct _SimRegType_ *reg2)
{
    obj->regI2sm = reg1;
    obj->regSim  = reg2;
}

void I2smDrv_GetDefaultConfig(I2smDrv_ConfigType *userConfig)
{
    userConfig->txFifoTriggerLevel   = 3;
    userConfig->wsCycle              = I2SMDRV_CLOCK_CYCLES_32;
    userConfig->sclkGateCycle        = I2SMDRV_NO_CLOCK_GATE;
    userConfig->dataResolution       = I2SMDRV_RESOLUTION_32;
    userConfig->txFifoEmptyIntMask   = 1;
    userConfig->txFifoOverrunIntMask = 1;
}

void I2smDrv_Config(I2smDrvType *obj, const I2smDrv_ConfigType *userConfig)
{
    /* select I2S as master mode */
    SimReg_SetI2sMode(obj->regSim, 1);
    /* enable I2S module */
    I2smReg_SetIerEn(obj->regI2sm, 1);
    /* set FIFO threshold */
    I2smReg_SetTfcr0Tfcr0(obj->regI2sm, userConfig->txFifoTriggerLevel);
    /* set ws cycle */
    I2smReg_SetCcrWss(obj->regI2sm, userConfig->wsCycle);
    /* set clock gate cycle */
    I2smReg_SetCcrSclkg(obj->regI2sm, userConfig->sclkGateCycle);
    /* set data resolution */
    I2smReg_SetTcr0TxWLen(obj->regI2sm, userConfig->dataResolution);
    /* config interrupt mask for fifo empty */
    I2smReg_SetImr0TxFem(obj->regI2sm, userConfig->txFifoEmptyIntMask);
    /* config interrupt mask for fifo overrun */
    I2smReg_SetImr0TxFom(obj->regI2sm, userConfig->txFifoOverrunIntMask);
    /* enable tx block */
    I2smReg_SetIterTxEn(obj->regI2sm, 1);
    /* enable tx channel0 */
    I2smReg_SetTer0TxChEn0(obj->regI2sm, 1);
}

void I2smDrv_FillFifoByDma(I2smDrvType *obj, uint32_t *data, uint8_t len)
{
    for(uint8_t i = 0; i < len; i++)
    {
        I2smReg_SetTxDmaTxDma(obj->regI2sm, data[i]);
    }
}

void I2smDrv_FillFifoByBuffer(I2smDrvType *obj, uint32_t *data, uint8_t len)
{
    for(uint8_t i = 0; i < len; i += 2)
    {
        I2smReg_SetLthr0Lthr0(obj->regI2sm, data[i]);
        I2smReg_SetRthr0Rthr0(obj->regI2sm, data[i + 1]);
    }
}

void I2smDrv_StartTransmit(I2smDrvType *obj)
{
    /* enable the clock */
    I2smReg_SetCerClkEn(obj->regI2sm, 1);
}

void I2smDrv_StopTransmit(I2smDrvType *obj)
{
    /* disable the clock */
    I2smReg_SetCerClkEn(obj->regI2sm, 0);
}

void I2smDrv_FlushTxFifo(I2smDrvType *obj)
{
    /* flush tx fifo 0 */
    I2smReg_SetTff0TxChfr0(obj->regI2sm, 1);
}

bool I2smDrv_GetFifoOverrunFlag(I2smDrvType *obj)
{
    bool flag = 0;
    flag      = I2smReg_GetIsr0TxFO(obj->regI2sm);
    return flag;
}

bool I2smDrv_GetFifoLevelTrigFlag(I2smDrvType *obj)
{
    bool flag = 0;
    flag      = I2smReg_GetIsr0TxFE(obj->regI2sm);
    return flag;
}
