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
#include "mft_oc_ch.h"
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

void MftOcCh_Init(MftOcChType *obj, struct _MftOcDrvType_ *ocDrv)
{
    obj->ocDrv = ocDrv;
}

void MftOcCh_GetDefaultConfig(MftOcCh_ConfigType *userConfig)
{
    userConfig->hwChannelId           = 0;                       /* Channel Id */
    userConfig->outputMode            = MFTOCCH_TOGGLE_ON_MATCH; /* Output toggle on match */
    userConfig->enableExternalTrigger = false;                   /* Disable the generation of a trigger */
    userConfig->callbacksParams       = NULL;                    /* Callback parameters for channel events */
    userConfig->callbackFunc          = NULL;                    /* Callback function for channels events */
}

void MftOcCh_Config(MftOcChType *obj, const MftOcCh_ConfigType *userConfig)
{
    uint8_t hwChannel   = 0U;
    uint8_t chnlPairNum = 0U;
    /* Check Channel Id */
    if(userConfig->hwChannelId >= MFT_CHANNEL_NUM)
    {
        return;
    }
    hwChannel = userConfig->hwChannelId;

    /* WPDIS = 1, disable write protection */
    MftReg_SetModeWpDis(obj->ocDrv->base->reg, 1);

    /* MSB:MSA = 0:1 set output compare mode*/
    MftReg_SetCscMsb(obj->ocDrv->base->reg, hwChannel, 0);
    MftReg_SetCscMsa(obj->ocDrv->base->reg, hwChannel, 1);

    chnlPairNum = (uint8_t)(hwChannel >> 1U);
    MftDrv_SetDualChannelComp(obj->ocDrv->base, chnlPairNum, false);
    MftDrv_SetDualChannelCombine(obj->ocDrv->base, chnlPairNum, false);
    MftDrv_SetDualEdgeCaptureCmd(obj->ocDrv->base, chnlPairNum, false);
    /* Set Channel Output mode */
    MftDrv_SetOutputlevel(obj->ocDrv->base, hwChannel, userConfig->outputMode);

    /* Write initial count value for channel */
    MftReg_SetCvVal(obj->ocDrv->base->reg, hwChannel, userConfig->comparedValue);
    /* Enable channel output */
    MftDrv_EnablePwmChannelOutputs(obj->ocDrv->base, hwChannel, true);
    /* External trigger */
    MftDrv_SetChannelTriggerCmd(obj->ocDrv->base, hwChannel, userConfig->enableExternalTrigger);
    /* Enable interrupt request for the current channel */
    MftReg_SetCscChie(obj->ocDrv->base->reg, userConfig->hwChannelId, 1);

    /* WPEN = 1, enable write protection */
    MftReg_SetFmsWpEn(obj->ocDrv->base->reg, 1);

    /* Remember the configuration */
    obj->config = *userConfig;
}

void MftOcCh_Disarm(MftOcChType *obj)
{
    /* WPDIS = 1, disable write protection */
    MftReg_SetModeWpDis(obj->ocDrv->base->reg, 1);

    /* Clear combine mode */
    MftReg_SetCombineCombine0(obj->ocDrv->base->reg, 0);
    MftReg_SetCombineCombine1(obj->ocDrv->base->reg, 0);
    MftReg_SetCombineCombine2(obj->ocDrv->base->reg, 0);
    MftReg_SetCombineCombine3(obj->ocDrv->base->reg, 0);
    MftDrv_SetDualEdgeCaptureCmd(obj->ocDrv->base, obj->config.hwChannelId >> 1, false);
    /* ELSnB:ELSnA = 0:0 (no edge) */
    MftReg_SetCscElsb(obj->ocDrv->base->reg, obj->config.hwChannelId, 0);
    MftReg_SetCscElsa(obj->ocDrv->base->reg, obj->config.hwChannelId, 0);
    /* Disable interrupt */
    MftReg_SetCscChie(obj->ocDrv->base->reg, obj->config.hwChannelId, 0);
    /* Clear channel event flag */
    MftReg_SetCscChf(obj->ocDrv->base->reg, obj->config.hwChannelId, 0);
    /* Disarm for channel (n+1) */
    /* ELSnB:ELSnA = 0:0 (no edge) */
    MftReg_SetCscElsb(obj->ocDrv->base->reg, (obj->config.hwChannelId | 1U), 0);
    MftReg_SetCscElsa(obj->ocDrv->base->reg, (obj->config.hwChannelId | 1U), 0);
    /* Disable interrupt */
    MftReg_SetCscChie(obj->ocDrv->base->reg, (obj->config.hwChannelId | 1U), 0);
    /* Clear channel event flag */
    MftReg_SetCscChf(obj->ocDrv->base->reg, (obj->config.hwChannelId | 1U), 0);

    /* WPEN = 1, enable write protection */
    MftReg_SetFmsWpEn(obj->ocDrv->base->reg, 1);
}

bool MftOcCh_UpdateOutputCompare(MftOcChType                    *obj,
                                 uint16_t                        nextCompareMatchValue,
                                 MftOcCh_OutputCompareUpdateType update,
                                 bool                            softWareTrigger)
{
    bool     retval          = false;
    uint16_t counterValue    = MftReg_GetCntCount(obj->ocDrv->base->reg);
    uint16_t compareValue    = 0U;
    uint16_t maxCounterValue = MftReg_GetModuloMod(obj->ocDrv->base->reg);

    if(update == MFTOCCH_RELATIVE_VALUE)
    {
        /* Configure channel compare register */
        if(nextCompareMatchValue > (maxCounterValue - counterValue))
        {
            compareValue = (uint16_t)(nextCompareMatchValue - (maxCounterValue - counterValue));
        }
        else
        {
            compareValue = (uint16_t)(counterValue + nextCompareMatchValue);
        }
    }
    else
    {
        compareValue = nextCompareMatchValue;
    }
    /* Set CnV value and use software trigger for sync */
    MftReg_SetCvVal(obj->ocDrv->base->reg, obj->config.hwChannelId, compareValue);
    MftReg_SetSyncSwSync(obj->ocDrv->base->reg, softWareTrigger);
    return retval;
}
