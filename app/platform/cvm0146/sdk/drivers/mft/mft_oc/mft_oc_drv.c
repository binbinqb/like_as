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

#include <stddef.h>
#include "mft_oc_drv.h"

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

void MftOcDrv_Init(MftOcDrvType *obj, MftDrvType *base)
{
    obj->base = base;

    uint8_t i = 0;
    for(i = 0; i < MFT_CHANNEL_NUM; ++i)
    {
        MftOcCh_Init(&obj->channel[i], obj);
    }
}

void MftOcDrv_GetDefaultConfig(MftOcDrv_ConfigType *userConfig)
{
    userConfig->maxCountValue = 65535;
}

void MftOcDrv_Config(MftOcDrvType *obj, const MftOcDrv_ConfigType *userConfig)
{
    /* WPDIS = 1, disable write protection */
    MftReg_SetModeWpDis(obj->base->reg, 1);

    /* CNTIN = 0 */
    MftReg_SetCntInCntInit(obj->base->reg, 0U);
    /* Set MOD */
    MftReg_SetModuloMod(obj->base->reg, userConfig->maxCountValue);

    /* Configure sync for OUTMASK register */
    MftReg_SetSynConfSwOM(obj->base->reg, 1);
    /* Configure sync for INVCTRL register */
    MftReg_SetSynConfSwInvC(obj->base->reg, 1);
    /* Configure sync for SWOCTRL register */
    MftReg_SetSynConfSwSoc(obj->base->reg, 1);
    /* Configure sync for MOD, HCR, CNTIN, and CnV registers */
    MftReg_SetSynConfSwWrbuf(obj->base->reg, 1);
    /* Configure synchronization method (waiting next loading point or now) */
    MftReg_SetSynConfSwRstCnt(obj->base->reg, 1);
    /* Enhanced PWM sync is used */
    MftReg_SetSynConfSyncMode(obj->base->reg, 1);
    /* Configure sync for CNTIN register updated with its buffer value at system_clock*/
    MftReg_SetSynConfCntInC(obj->base->reg, 0);

    /* WPEN = 1, enable write protection */
    MftReg_SetFmsWpEn(obj->base->reg, 1);
}
