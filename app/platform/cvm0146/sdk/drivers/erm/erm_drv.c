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

#include "erm_drv.h"
#include "erm_reg.h"

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

void ErmDrv_Init(ErmDrvType *obj, struct _ErmRegType_ *ermReg)
{
    obj->reg = ermReg;
}

void ErmDrv_GetDefaultConfig(ErmDrv_ChnErrConfigType *userConfig)
{
    uint8_t chnNum;
    uint8_t ctrlChnNum;

    for(chnNum = 0; chnNum < ERMDRV_CH_TOTAL_NUM; chnNum++)
    {
        /* ERM channel Irq enable, default: false */
        userConfig->chnIrq[chnNum] = false;
        /* ERM channel error status, default: false */
        userConfig->chnEvent[chnNum] = false;
    }

    for(ctrlChnNum = 0; ctrlChnNum < ERMDRV_CH_CTRL_TOTAL_NUM; ctrlChnNum++)
    {
        /* ERM channel 0~3 control error address, default: 0 */
        userConfig->chnStatus[ctrlChnNum].errAddr = 0;
        /* ERM channel 0~3 control error position, default: 0 */
        userConfig->chnStatus[ctrlChnNum].errPos = 0;
        /* ERM channel 0~3 control recover error num, default: 0 */
        userConfig->chnStatus[ctrlChnNum].errRecoverNum = 0;
    }
    /* ERM channel 4 control recover error num, default: 0 */
    userConfig->chnStatus[ERMDRV_CH4].errRecoverNum = 0;
}

void ErmDrv_SetChnErrIrqEnable(ErmDrvType *obj, ErmDrv_ChnNumType chnNum, bool enable)
{
    uint16_t chnStatusCtrl = 0;

    if(chnNum > ERMDRV_CH4_NONRECOVER_IRQ)
    {
        return;
    }

    /* Set ERM channel number enable */
    chnStatusCtrl = ErmReg_GetChnEnable(obj->reg);
    if(enable)
    {
        chnStatusCtrl |= (1 << chnNum);
    }
    else
    {
        chnStatusCtrl &= (0 << chnNum);
    }
    ErmReg_SetChnEnable(obj->reg, chnStatusCtrl);
}

bool ErmDrv_GetChnErrIrqEnable(ErmDrvType *obj, ErmDrv_ChnNumType chnNum)
{
    uint16_t temp;

    if(chnNum > ERMDRV_CH4_NONRECOVER_IRQ)
    {
        return false;
    }

    /* Get ERM channel number enable */
    temp = ErmReg_GetChnEnable(obj->reg);

    return (bool)(temp >> chnNum & 0x1);
}

bool ErmDrv_GetChnErrInfoStatus(ErmDrvType *obj, ErmDrv_ChnNumType chnNum)
{
    uint16_t temp;

    if(chnNum > ERMDRV_CH4_NONRECOVER_IRQ)
    {
        return false;
    }

    /* Get channel error status */
    temp = ErmReg_GetChnErrStatus(obj->reg);

    return (bool)(temp >> chnNum & 0x1);
}

void ErmDrv_ClrChnErrInfoStatus(ErmDrvType *obj, ErmDrv_ChnNumType chnNum)
{
    if(chnNum > ERMDRV_CH4_NONRECOVER_IRQ)
    {
        return;
    }

    /* Clear channel error status */
    ErmReg_ClrChnErrStatus(obj->reg, chnNum);
}

void ErmDrv_GetChnNumCfg(ErmDrvType *obj, ErmDrv_ChnNumInfoType *chnNumInfo, ErmDrv_CtrlChnNumType ctrlChnNum)
{
    if(ctrlChnNum < ERMDRV_CH4)
    {
        /* Get channel 0~3 error address */
        chnNumInfo->errAddr = ErmReg_GetErrAddr(obj->reg, ctrlChnNum);
        /* Get channel 0~3 error position */
        chnNumInfo->errPos = ErmReg_GetErrPos(obj->reg, ctrlChnNum);
        /* Get channel 0~3 error total num */
        chnNumInfo->errRecoverNum = ErmReg_GetErrNum(obj->reg, ctrlChnNum);
    }
    else if(ctrlChnNum == ERMDRV_CH4)
    {
        /* Get channel 4 error address not support */
        chnNumInfo->errAddr = 0xFFFFFFFF;
        /* Get channel 4 error poisition not support */
        chnNumInfo->errPos = 0xFF000000;
        /* Get channel 4 error total num */
        chnNumInfo->errRecoverNum = ErmReg_GetErrChn4Num(obj->reg);
    }
    else
    {
        return;
    }
}

void ErmDrv_ClrChnNumCfg(ErmDrvType *obj, ErmDrv_CtrlChnNumType ctrlChnNum)
{
    if(ctrlChnNum < ERMDRV_CH4)
    {
        /* Clear channel 4 error total num */
        ErmReg_ClrErrNum(obj->reg, ctrlChnNum, ERMDRV_RECOVER_ERRNUM_CLR);
    }
    else if(ctrlChnNum == ERMDRV_CH4)
    {
        /* Clear channel 4 error total num */
        ErmReg_ClrErrChn4Num(obj->reg, ERMDRV_RECOVER_ERRNUM_CLR);
    }
    else
    {
        return;
    }
}
