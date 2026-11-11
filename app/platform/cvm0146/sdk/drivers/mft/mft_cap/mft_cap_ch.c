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
#include "mft_cap_ch.h"
#include "mft_cap_drv.h"

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

void MftCapCh_Init(MftCapChType *obj, struct _MftCapDrvType_ *capDrv)
{
    obj->capDrv = capDrv;
}

void MftCapCh_GetDefaultConfig(MftCapCh_ConfigType *userConfig)
{
    userConfig->hwChannelId      = 0;                       /* Channel Id */
    userConfig->inputMode        = MFTCAPCH_EDGE_DETECT;    /* Input capture operation Mode */
    userConfig->edgeAlignement   = MFTCAPCH_RISING_EDGE;    /* Edge alignment Mode */
    userConfig->measurementType  = MFTCAPCH_NO_MEASUREMENT; /* Signal measurement operation type */
    userConfig->filterValue      = 0;                       /* Filter value */
    userConfig->filterEn         = false;                   /* Filter disabled */
    userConfig->continuousModeEn = true;                    /* Continuous mode measurement */
    userConfig->callbacksParams  = NULL;                    /* Callback parameters for channel events */
    userConfig->callbackFunc     = NULL;                    /* Callback function for channels events */
}

void MftCapCh_Config(MftCapChType *obj, const MftCapCh_ConfigType *userConfig)
{
    /* Check Channel Id */
    if(userConfig->hwChannelId >= MFT_CHANNEL_NUM)
    {
        return;
    }

    /* WPDIS = 1, disable write protection */
    MftReg_SetModeWpDis(obj->capDrv->base->reg, 1);

    /* Filter Mode, only availabe for channel 0, 1, 2, 3 */
    uint16_t filterValue = userConfig->filterEn ? userConfig->filterValue : 0;
    switch(userConfig->hwChannelId)
    {
    case 0:
        MftReg_SetFilterCh0FVal(obj->capDrv->base->reg, filterValue);
        break;
    case 1:
        MftReg_SetFilterCh1FVal(obj->capDrv->base->reg, filterValue);
        break;
    case 2:
        MftReg_SetFilterCh2FVal(obj->capDrv->base->reg, filterValue);
        break;
    case 3:
        MftReg_SetFilterCh3FVal(obj->capDrv->base->reg, filterValue);
        break;
    default:
        /* Nothing to do, not available for other channels */
        break;
    }

    /* Input capture operation Mode, Edge alignment Mode, Signal measurement operation type */
    if(MFTCAPCH_EDGE_DETECT == userConfig->inputMode)
    {
        /* DECAPEN = 0 */
        MftDrv_SetDualEdgeCaptureCmd(obj->capDrv->base, userConfig->hwChannelId >> 1, false);
        /* MSB:MSA = 0:0 */
        MftReg_SetCscMsb(obj->capDrv->base->reg, userConfig->hwChannelId, 0);
        MftReg_SetCscMsa(obj->capDrv->base->reg, userConfig->hwChannelId, 0);
        /* ELSnB:ELSnA = 0:0 */
        MftReg_SetCscElsb(obj->capDrv->base->reg, userConfig->hwChannelId, (userConfig->edgeAlignement >> 1) & 0x01U);
        MftReg_SetCscElsa(obj->capDrv->base->reg, userConfig->hwChannelId, userConfig->edgeAlignement & 0x01U);
        /* Enable interrupt request for the current channel */
        MftReg_SetCscChie(obj->capDrv->base->reg, userConfig->hwChannelId, 1);
    }
    else if(MFTCAPCH_SIGNAL_MEASUREMENT == userConfig->inputMode)
    {
        /* DECAPEN = 1 */
        MftDrv_SetDualEdgeCaptureCmd(obj->capDrv->base, userConfig->hwChannelId >> 1, true);
        /* DECAP = 1 */
        MftDrv_SetDualChannelDecap(obj->capDrv->base, userConfig->hwChannelId >> 1, true);
        /* If continuous mode is set */
        if(true == userConfig->continuousModeEn)
        {
            /* MSB:MSA = 1:1 */
            MftReg_SetCscMsb(obj->capDrv->base->reg, userConfig->hwChannelId, 1);
            MftReg_SetCscMsa(obj->capDrv->base->reg, userConfig->hwChannelId, 1);
        }
        else
        {
            /* MSB:MSA = 1:0 */
            MftReg_SetCscMsb(obj->capDrv->base->reg, userConfig->hwChannelId, 1);
            MftReg_SetCscMsa(obj->capDrv->base->reg, userConfig->hwChannelId, 0);
        }
        /* Check If want to measure a pulse width or period of the signal */
        if((MFTCAPCH_PERIOD_ON_MEASUREMENT == userConfig->measurementType)
           || (MFTCAPCH_RISING_EDGE_PERIOD_MEASUREMENT == userConfig->measurementType))
        {
            /* ELSnB:ELSnA = 0:1 (rising edge) */
            MftReg_SetCscElsb(obj->capDrv->base->reg, userConfig->hwChannelId, 0);
            MftReg_SetCscElsa(obj->capDrv->base->reg, userConfig->hwChannelId, 1);
            if(MFTCAPCH_PERIOD_ON_MEASUREMENT == userConfig->measurementType)
            {
                /* Measure time between rising and falling edge - positive duty */
                /* ELSnB:ELSnA = 1:0 (falling edge) for channel (n+1)*/
                MftReg_SetCscElsb(obj->capDrv->base->reg, userConfig->hwChannelId + 1, 1);
                MftReg_SetCscElsa(obj->capDrv->base->reg, userConfig->hwChannelId + 1, 0);
            }
            else
            {
                /* If channel (n) is configured to capture falling edges (ELS(n)B:ELS(n)A = 0:1)
                 * then channel (n+1) also captures falling edges (ELS(n+1)B:ELS(n+1)A = 0:1) */
                MftReg_SetCscElsb(obj->capDrv->base->reg, userConfig->hwChannelId + 1, 0);
                MftReg_SetCscElsa(obj->capDrv->base->reg, userConfig->hwChannelId + 1, 1);
            }
        }
        else if((MFTCAPCH_PERIOD_OFF_MEASUREMENT == userConfig->measurementType)
                || (MFTCAPCH_FALLING_EDGE_PERIOD_MEASUREMENT == userConfig->measurementType))
        {
            /* ELSnB:ELSnA = 1:0 (falling edge) */
            MftReg_SetCscElsb(obj->capDrv->base->reg, userConfig->hwChannelId, 1);
            MftReg_SetCscElsa(obj->capDrv->base->reg, userConfig->hwChannelId, 0);
            if(MFTCAPCH_PERIOD_OFF_MEASUREMENT == userConfig->measurementType)
            {
                /* Measure time between falling and rising edge - negative duty */
                /* ELSnB:ELSnA = 0:1 (rising edge) for channel (n+1) */
                MftReg_SetCscElsb(obj->capDrv->base->reg, userConfig->hwChannelId + 1, 0);
                MftReg_SetCscElsa(obj->capDrv->base->reg, userConfig->hwChannelId + 1, 1);
            }
            else
            {
                /* If channel (n) is configured to capture rising edges (ELS(n)B:ELS(n)A = 1:0) than
                 * channel (n+1) is setup to capture also raising edges (ELS(n+1)B:ELS(n+1)A = 1:0) */
                MftReg_SetCscElsb(obj->capDrv->base->reg, userConfig->hwChannelId + 1, 1);
                MftReg_SetCscElsa(obj->capDrv->base->reg, userConfig->hwChannelId + 1, 0);
            }
        }

        /* Enable the interrupt request for the channel which will indicate that the measurement is done. */
        MftReg_SetCscChie(obj->capDrv->base->reg, userConfig->hwChannelId + 1, 1);
    }

    /* WPEN = 1, enable write protection */
    MftReg_SetFmsWpEn(obj->capDrv->base->reg, 1);

    /* Remember the configuration */
    obj->config = *userConfig;
}

void MftCapCh_Disarm(MftCapChType *obj)
{
    /* WPDIS = 1, disable write protection */
    MftReg_SetModeWpDis(obj->capDrv->base->reg, 1);

    /* Filter Mode, only availabe for channel 0, 1, 2, 3 */
    switch(obj->config.hwChannelId)
    {
    case 0:
        MftReg_SetFilterCh0FVal(obj->capDrv->base->reg, 0);
        break;
    case 1:
        MftReg_SetFilterCh1FVal(obj->capDrv->base->reg, 0);
        break;
    case 2:
        MftReg_SetFilterCh2FVal(obj->capDrv->base->reg, 0);
        break;
    case 3:
        MftReg_SetFilterCh3FVal(obj->capDrv->base->reg, 0);
        break;
    default:
        /* Nothing to do, not available for other channels */
        break;
    }

    /* Clear combine mode */
    MftReg_SetCombineCombine0(obj->capDrv->base->reg, 0);
    MftReg_SetCombineCombine1(obj->capDrv->base->reg, 0);
    MftReg_SetCombineCombine2(obj->capDrv->base->reg, 0);
    MftReg_SetCombineCombine3(obj->capDrv->base->reg, 0);
    MftDrv_SetDualEdgeCaptureCmd(obj->capDrv->base, obj->config.hwChannelId >> 1, false);
    /* ELSnB:ELSnA = 0:0 (no edge) */
    MftReg_SetCscElsb(obj->capDrv->base->reg, obj->config.hwChannelId, 0);
    MftReg_SetCscElsa(obj->capDrv->base->reg, obj->config.hwChannelId, 0);
    /* Disable interrupt */
    MftReg_SetCscChie(obj->capDrv->base->reg, obj->config.hwChannelId, 0);
    /* Clear channel event flag */
    MftReg_SetCscChf(obj->capDrv->base->reg, obj->config.hwChannelId, 0);
    /* Disarm for channel (n+1) */
    /* ELSnB:ELSnA = 0:0 (no edge) */
    MftReg_SetCscElsb(obj->capDrv->base->reg, (obj->config.hwChannelId | 1U), 0);
    MftReg_SetCscElsa(obj->capDrv->base->reg, (obj->config.hwChannelId | 1U), 0);
    /* Disable interrupt */
    MftReg_SetCscChie(obj->capDrv->base->reg, (obj->config.hwChannelId | 1U), 0);
    /* Clear channel event flag */
    MftReg_SetCscChf(obj->capDrv->base->reg, (obj->config.hwChannelId | 1U), 0);

    /* WPEN = 1, enable write protection */
    MftReg_SetFmsWpEn(obj->capDrv->base->reg, 1);
}

bool MftCapCh_StartNewSignalMeasurement(MftCapChType *obj)
{
    bool retval = false;
    /* Check if the channel is in single-shot mode */
    if(MftReg_GetCscMsa(obj->capDrv->base->reg, obj->config.hwChannelId) == 0
       && MftReg_GetCscMsb(obj->capDrv->base->reg, obj->config.hwChannelId) == 1)
    {
        if(MftDrv_GetDualEdgeCaptureCmd(obj->capDrv->base, obj->config.hwChannelId >> 1))
        {
            /* Clear event flags for channel n and n + 1 */
            MftReg_SetCscChf(obj->capDrv->base->reg, obj->config.hwChannelId + 1, 0);
            MftReg_SetCscChf(obj->capDrv->base->reg, obj->config.hwChannelId, 0);
            /* Set DECAP bit to start measurement */
            MftDrv_SetDualChannelDecap(obj->capDrv->base, obj->config.hwChannelId >> 1, true);
            retval = true;
        }
    }

    return retval;
}

void MftCapCh_SetChannelMode(MftCapChType *obj, MftCapCh_OpModeType inputMode, bool enableContinuousCapture)
{
    uint8_t level        = 1U;
    uint8_t nextChnlevel = 1U;
    uint8_t channelPair  = (uint8_t)(obj->config.hwChannelId >> 1U);

    /* WPDIS = 1, disable write protection */
    MftReg_SetModeWpDis(obj->capDrv->base->reg, 1);

    if(MFTCAPCH_DISABLE_OPERATION == inputMode)
    {
        /* Set the edge level to disable operation on the channel input */
        /* ELSnB:ELSnA = 0:0 (no edge) */
        MftReg_SetCscElsb(obj->capDrv->base->reg, obj->config.hwChannelId, 0);
        MftReg_SetCscElsa(obj->capDrv->base->reg, obj->config.hwChannelId, 0);
    }
    else if((MFTCAPCH_TIMESTAMP_RISING_EDGE == inputMode) || (MFTCAPCH_TIMESTAMP_FALLING_EDGE == inputMode) || (MFTCAPCH_TIMESTAMP_BOTH_EDGES == inputMode))
    {
        /* Disable the dual edge mode */
        MftDrv_SetDualEdgeCaptureCmd(obj->capDrv->base, channelPair, false);
        /* Set input capture mode, MSB:MSA = 0:0 */
        MftReg_SetCscMsb(obj->capDrv->base->reg, obj->config.hwChannelId, 0);
        MftReg_SetCscMsa(obj->capDrv->base->reg, obj->config.hwChannelId, 0);
        /* Set the event which will generate the interrupt */
        MftReg_SetCscElsb(obj->capDrv->base->reg, obj->config.hwChannelId, (inputMode >> 1) & 0x01U);
        MftReg_SetCscElsa(obj->capDrv->base->reg, obj->config.hwChannelId, inputMode & 0x01U);
        /* Enable interrupt request for the current channel */
        MftReg_SetCscChie(obj->capDrv->base->reg, obj->config.hwChannelId, 1);
    }
    else
    {
        /* Check the channel is even number */
        if((obj->config.hwChannelId % 2U) != 0U)
        {
            return;
        }
        /* Enable the dual edge mode */
        MftDrv_SetDualEdgeCaptureCmd(obj->capDrv->base, channelPair, true);
        /* Enable dual edge input capture */
        MftDrv_SetDualChannelDecap(obj->capDrv->base, channelPair, true);
        /* If continuous mode is set*/
        if(true == enableContinuousCapture)
        {
            /* MSB:MSA = 1:1 */
            MftReg_SetCscMsb(obj->capDrv->base->reg, obj->config.hwChannelId, 1);
            MftReg_SetCscMsa(obj->capDrv->base->reg, obj->config.hwChannelId, 1);
        }
        else
        {
            /* MSB:MSA = 1:0 */
            MftReg_SetCscMsb(obj->capDrv->base->reg, obj->config.hwChannelId, 1);
            MftReg_SetCscMsa(obj->capDrv->base->reg, obj->config.hwChannelId, 0);
        }

        /* Check If want to measure a pulse width or period of the signal */
        if((MFTCAPCH_MEASURE_PULSE_HIGH == inputMode) || (MFTCAPCH_MEASURE_RISING_EDGE_PERIOD == inputMode))
        {
            if(MFTCAPCH_MEASURE_PULSE_HIGH == inputMode)
            {
                /* Measure time between rising and falling edge - positive duty */
                nextChnlevel = 2U;
            }
        }
        else
        {
            level = 2U;
            if(MFTCAPCH_MEASURE_FALLING_EDGE_PERIOD == inputMode)
            {
                /* If channel (n) is configured to capture rising edges (ELS(n)B:ELS(n)A = 1:0) than
                 * channel (n+1) is setup to capture also raising edges (ELS(n+1)B:ELS(n+1)A = 1:0) */
                nextChnlevel = 2U;
            }
        }
        /* Edge selection for channel (n) */
        MftReg_SetCscElsb(obj->capDrv->base->reg, obj->config.hwChannelId, (level >> 1) & 0x01U);
        MftReg_SetCscElsa(obj->capDrv->base->reg, obj->config.hwChannelId, level & 0x01U);
        /* Edge selection for channel (n+1) */
        MftReg_SetCscElsb(obj->capDrv->base->reg, obj->config.hwChannelId + 1, (nextChnlevel >> 1) & 0x01U);
        MftReg_SetCscElsa(obj->capDrv->base->reg, obj->config.hwChannelId + 1, nextChnlevel & 0x01U);

        /* Disable interrupt request for the current channel */
        MftReg_SetCscChie(obj->capDrv->base->reg, obj->config.hwChannelId, 0);
        MftReg_SetCscChie(obj->capDrv->base->reg, obj->config.hwChannelId + 1, 1);
    }

    /* WPEN = 1, enable write protection */
    MftReg_SetFmsWpEn(obj->capDrv->base->reg, 1);
}
