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

#include "adc_drv.h"
#include "adc_reg.h"
#include "sim_reg.h"
#include "../cpu/cpu_drv.h"

/*******************************************************************************
 * the defines
 ******************************************************************************/
#define ADC_INTERLEAVE_ENABLE      (1U)
#define ADC_LEN_PWR_ON_DEFAULT     (11U)
#define ADC_LEN_SMPL_1ST_DEFAULT   (48U)
#define ADC_LEN_SMPL_DEFAULT       (4U)
/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief ADC type of enable selection
 */
typedef enum
{
    ADCDRV_POWER_ON   = 0x0U,
    ADCDRV_POWER_DOWN = 0x1U,
} AdcDrv_PowerEnable;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the functions
 ******************************************************************************/

void AdcDrv_Init(AdcDrvType *obj, struct _AdcRegType_ *adcReg, struct _SimRegType_ *simReg, const AdcDrv_InitParamsType *initParams)
{
    obj->adcReg    = adcReg;
    obj->simReg    = simReg;
    obj->adcNumber = initParams->adcNumber;
}

void AdcDrv_SetInterleave(AdcDrvType *obj, const AdcDrv_InterleaveType *userConfig)
{
    uint8_t interleave = 0;
    uint8_t i;
    for(i = ADCDRV_INTERLEAVE_ADC0SE4_ADC1SE14; i < ADCDRV_INTERLEAVE_CHANNEL_NUMBER; i++)
    {
        if(userConfig->state[i])
        {
            interleave |= ADC_INTERLEAVE_ENABLE << i;
        }
    }
    SimReg_SetAdcILSrc(obj->simReg, interleave);
}

void AdcDrv_GetInterleave(AdcDrvType *obj, AdcDrv_InterleaveType *interleaveState)
{
    uint8_t interleave = SimReg_GetAdcILSrc(obj->simReg);
    uint8_t i;
    for(i = ADCDRV_INTERLEAVE_ADC0SE4_ADC1SE14; i < ADCDRV_INTERLEAVE_CHANNEL_NUMBER; i++)
    {
        uint8_t tmp;
        tmp = (interleave >> i) & ADC_INTERLEAVE_ENABLE;
        if(tmp == ADC_INTERLEAVE_ENABLE)
        {
            interleaveState->state[i] = true;
        }
        else
        {
            interleaveState->state[i] = false;
        }
    }
}

void AdcDrv_GetCmpCfg(AdcDrvType *obj, AdcDrv_CmpCfgType *currentConfig)
{
    bool     acfe  = AdcReg_GetSc2Acfe(obj->adcReg);
    bool     acfgt = AdcReg_GetSc2AcFgt(obj->adcReg);
    bool     acren = AdcReg_GetSc2AcREn(obj->adcReg);
    uint16_t cv1   = AdcReg_GetCv1Cv(obj->adcReg);
    uint16_t cv2   = AdcReg_GetCv2Cv(obj->adcReg);
    if(acfe == false)
    {
        currentConfig->cmpMode  = ADCDRV_CMPMODE_NO_COMPARE;
        currentConfig->lowerLim = 0;
        currentConfig->upperLim = 0;
    }
    else
    {
        if(acfgt == false && acren == false)
        {
            currentConfig->cmpMode  = ADCDRV_CMPMODE_LESSTHAN;
            currentConfig->lowerLim = cv1;
            currentConfig->upperLim = 0;
        }
        else if(acfgt == true && acren == false)
        {
            currentConfig->cmpMode  = ADCDRV_CMPMODE_GREATER_OR_EQUTHAN;
            currentConfig->lowerLim = cv1;
            currentConfig->upperLim = 0;
        }
        else if(acfgt == false && acren == true && cv1 <= cv2)
        {
            currentConfig->cmpMode  = ADCDRV_CMPMODE_OUTSIDE_EXCLUDE_BOUNDARIES;
            currentConfig->lowerLim = cv1;
            currentConfig->upperLim = cv2;
        }
        else if(acfgt == false && acren == true && cv1 > cv2)
        {
            currentConfig->cmpMode  = ADCDRV_CMPMODE_INSIDE_EXCLUDE_BOUNDARIES;
            currentConfig->lowerLim = cv2;
            currentConfig->upperLim = cv1;
        }
        else if(acfgt == true && acren == true && cv1 <= cv2)
        {
            currentConfig->cmpMode  = ADCDRV_CMPMODE_INSIDE_INCLUDE_BOUNDARIES;
            currentConfig->lowerLim = cv1;
            currentConfig->upperLim = cv2;
        }
        else if(acfgt == true && acren == true && cv1 > cv2)
        {
            currentConfig->cmpMode  = ADCDRV_CMPMODE_OUTSIDE_INCLUDE_BOUNDARIES;
            currentConfig->lowerLim = cv2;
            currentConfig->upperLim = cv1;
        }
    }
}

void AdcDrv_CfgCompare(AdcDrvType *obj, const AdcDrv_CmpCfgType *userConfig)
{
    switch(userConfig->cmpMode)
    {
    case(ADCDRV_CMPMODE_NO_COMPARE):
        AdcReg_SetSc2Acfe(obj->adcReg, false);
        break;
    case(ADCDRV_CMPMODE_LESSTHAN):
        AdcReg_SetSc2Acfe(obj->adcReg, true);
        AdcReg_SetSc2AcFgt(obj->adcReg, false);
        AdcReg_SetSc2AcREn(obj->adcReg, false);
        AdcReg_SetCv1Cv(obj->adcReg, userConfig->lowerLim);
        AdcReg_SetCv2Cv(obj->adcReg, 0u);
        break;
    case(ADCDRV_CMPMODE_GREATER_OR_EQUTHAN):
        AdcReg_SetSc2Acfe(obj->adcReg, true);
        AdcReg_SetSc2AcFgt(obj->adcReg, true);
        AdcReg_SetSc2AcREn(obj->adcReg, false);
        AdcReg_SetCv1Cv(obj->adcReg, userConfig->lowerLim);
        AdcReg_SetCv2Cv(obj->adcReg, 0u);
        break;
    case(ADCDRV_CMPMODE_OUTSIDE_EXCLUDE_BOUNDARIES):
        AdcReg_SetSc2Acfe(obj->adcReg, true);
        AdcReg_SetSc2AcFgt(obj->adcReg, false);
        AdcReg_SetSc2AcREn(obj->adcReg, true);
        AdcReg_SetCv1Cv(obj->adcReg, userConfig->lowerLim);
        AdcReg_SetCv2Cv(obj->adcReg, userConfig->upperLim);
        break;
    case(ADCDRV_CMPMODE_INSIDE_EXCLUDE_BOUNDARIES):
        AdcReg_SetSc2Acfe(obj->adcReg, true);
        AdcReg_SetSc2AcFgt(obj->adcReg, false);
        AdcReg_SetSc2AcREn(obj->adcReg, true);
        AdcReg_SetCv1Cv(obj->adcReg, userConfig->upperLim);
        AdcReg_SetCv2Cv(obj->adcReg, userConfig->lowerLim);
        break;
    case(ADCDRV_CMPMODE_INSIDE_INCLUDE_BOUNDARIES):
        AdcReg_SetSc2Acfe(obj->adcReg, true);
        AdcReg_SetSc2AcFgt(obj->adcReg, true);
        AdcReg_SetSc2AcREn(obj->adcReg, true);
        AdcReg_SetCv1Cv(obj->adcReg, userConfig->lowerLim);
        AdcReg_SetCv2Cv(obj->adcReg, userConfig->upperLim);
        break;
    case(ADCDRV_CMPMODE_OUTSIDE_INCLUDE_BOUNDARIES):
        AdcReg_SetSc2Acfe(obj->adcReg, true);
        AdcReg_SetSc2AcFgt(obj->adcReg, true);
        AdcReg_SetSc2AcREn(obj->adcReg, true);
        AdcReg_SetCv1Cv(obj->adcReg, userConfig->upperLim);
        AdcReg_SetCv2Cv(obj->adcReg, userConfig->lowerLim);
        break;
    default:
        /* Impossible case */
        break;
    }
}

void AdcDrv_Configure(AdcDrvType *obj, const AdcDrv_ConfigType *userConfig)
{
    /* disable ADC first */
    AdcReg_SetSc3AdcPD(obj->adcReg, ADCDRV_POWER_DOWN);

    /* select the conversion conversionMode */
    AdcReg_SetCfg1Mode(obj->adcReg, (uint8_t)userConfig->conversionMode);

    /* select the ADC sample length */
    AdcReg_SetCfg2LenSmpl(obj->adcReg, userConfig->sampleLen);

    /* select the ADC sample length after the 1st cycle
     * change the input channel select(ADCH) */
    AdcReg_SetCfg2LenSmpl1st(obj->adcReg, userConfig->firstSampleLen);

    /* select the ADC sample length after power on */
    AdcReg_SetCfg2LenPwrOn(obj->adcReg, userConfig->pwrOnLen);

    /* select ADC reference voltage */
    AdcReg_SetSc2RefSel(obj->adcReg, (uint8_t)userConfig->refVolSel);

    /* enable DMA */
    AdcReg_SetSc2DmaEn(obj->adcReg, userConfig->dmaEnable);

    /* Enable trigger*/
    AdcReg_SetSc2AdTrg(obj->adcReg, 1);

    if(obj->adcNumber == ADCDRV_INSTANCE_0)
    {
        /* select hardware trigger source */
        SimReg_SetAdcTrg0Src(obj->simReg, (uint8_t)userConfig->trgSrcCfg.hwTrgSrc);

        /* select software pretrigger source */
        SimReg_SetAdcPreTrg0SwSrc(obj->simReg, (uint8_t)userConfig->trgSrcCfg.swPretrgSrc);

        /* set pretrigger source */
        SimReg_SetAdcPreTrg0Src(obj->simReg, (uint8_t)userConfig->trgSrcCfg.pretrgSrc);
    }
    else if(obj->adcNumber == ADCDRV_INSTANCE_1)
    {
        /* select hardware trigger source */
        SimReg_SetAdcTrg1Src(obj->simReg, (uint8_t)userConfig->trgSrcCfg.hwTrgSrc);

        /* select software pretrigger source */
        SimReg_SetAdcPreTrg1SwSrc(obj->simReg, (uint8_t)userConfig->trgSrcCfg.swPretrgSrc);

        /* select pretrigger source */
        SimReg_SetAdcPreTrg1Src(obj->simReg, (uint8_t)userConfig->trgSrcCfg.pretrgSrc);
    }

    /* select the continuous / one shot conversion */
    AdcReg_SetSc3Adco(obj->adcReg, (uint8_t)userConfig->continuousMode);

    /* configure the ADC compare function */
    AdcDrv_CfgCompare(obj, &(userConfig->cmpCfg));

    /* enable hardware average sample */
    AdcReg_SetSc3AvgE(obj->adcReg, userConfig->avgEnable);
    if(userConfig->avgEnable)
    {
        /* select the hardware average sample number */
        AdcReg_SetSc3AvgS(obj->adcReg, (uint8_t)userConfig->avgSamplesSel);
    }

    /* configure for each ADC channel */
    uint8_t i;
    for(i = 0; i < ADCDRV_CHANNEL_NUM; i++)
    {
        /* select the ADC channel input */
        AdcReg_SetScAdCh(obj->adcReg, i, (uint8_t)userConfig->chnCfg[i].chnSel);

        /* enable the interrupt for ADC channel */
        AdcReg_SetScAIEn(obj->adcReg, i, userConfig->chnCfg[i].intEnable);
    }

    /* select interleave channel state */
    AdcDrv_SetInterleave(obj, &(userConfig->interleaveMode));

    /* enable ADC */
    AdcReg_SetSc3AdcPD(obj->adcReg, ADCDRV_POWER_ON);
}

void AdcDrv_GetDefaultConfig(AdcDrv_ConfigType *userConfig)
{
    uint8_t i = 0U;

    userConfig->conversionMode  = ADCDRV_CONVERSION_12BIT;
    userConfig->sampleLen       = ADC_LEN_SMPL_DEFAULT;
    userConfig->firstSampleLen  = ADC_LEN_SMPL_1ST_DEFAULT;
    userConfig->pwrOnLen        = ADC_LEN_PWR_ON_DEFAULT;
    userConfig->refVolSel       = ADCDRV_REFVOLT_VDDA;
    userConfig->dmaEnable       = false;
    userConfig->cmpCfg.lowerLim = 0;
    userConfig->cmpCfg.upperLim = 0;
    userConfig->cmpCfg.cmpMode  = ADCDRV_CMPMODE_NO_COMPARE;
    userConfig->continuousMode  = ADCDRV_ONESHOT;
    userConfig->avgSamplesSel   = ADCDRV_AVERAGE_4;
    userConfig->avgEnable       = true;
    for(i = ADCDRV_INTERLEAVE_ADC0SE4_ADC1SE14; i < ADCDRV_INTERLEAVE_CHANNEL_NUMBER; i++)
    {
        userConfig->interleaveMode.state[i] = false;
    }

    userConfig->trgSrcCfg.hwTrgSrc    = ADCDRV_HW_TRGSRC_PDB;
    userConfig->trgSrcCfg.swPretrgSrc = ADCDRV_SWPRETRG_PRETRIGGER_0;
    userConfig->trgSrcCfg.pretrgSrc   = ADCDRV_PRETRG_PDB_PRETRIGGER;

    for(i = 0; i < ADCDRV_CHANNEL_NUM; i++)
    {
        userConfig->chnCfg[i].chnSel    = (AdcDrv_InChnType)i;
        userConfig->chnCfg[i].intEnable = false;
    }
}

void AdcDrv_ClrLockTrg(AdcDrvType *obj)
{
    AdcReg_ClrTrg(obj->adcReg);
}

uint16_t AdcDrv_GetRn(AdcDrvType *obj, uint8_t chn)
{
    return (AdcReg_GetRData(obj->adcReg, (uint8_t)chn));
}

bool AdcDrv_GetCocon(AdcDrvType *obj, uint8_t chn)
{
    if(AdcReg_GetScCoCo(obj->adcReg, (uint8_t)chn) > 0)
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

void AdcDrv_DisableAdc(AdcDrvType *obj)
{
    AdcReg_SetSc3AdcPD(obj->adcReg, ADCDRV_POWER_DOWN);
}

void AdcDrv_EnableAdc(AdcDrvType *obj)
{
    AdcReg_SetSc3AdcPD(obj->adcReg, ADCDRV_POWER_ON);
}

void AdcDrv_AbortChn(AdcDrvType *obj, uint8_t chn)
{
    AdcReg_AbortChn(obj->adcReg, chn);
}

void AdcDrv_ConfigureChn(AdcDrvType *obj, uint8_t chn, AdcDrv_InChnType state)
{
    AdcReg_SetScAdCh(obj->adcReg, chn, state);
}

void AdcDrv_GetConfig(AdcDrvType *obj, AdcDrv_ConfigType *currentConfig)
{
    /* get the conversion conversionMode */
    currentConfig->conversionMode = (AdcDrv_ConversionMode)AdcReg_GetCfg1Mode(obj->adcReg);

    /* get the ADC sample length */
    currentConfig->sampleLen = AdcReg_GetCfg2LenSmpl(obj->adcReg);

    /* get the ADC sample length after the 1st cycle
     * change the input channel select(ADCH) */
    currentConfig->firstSampleLen = AdcReg_GetCfg2LenSmpl1st(obj->adcReg);

    /* get the ADC sample length after power on */
    currentConfig->pwrOnLen = AdcReg_GetCfg2LenPwrOn(obj->adcReg);

    /* get ADC reference voltage */
    currentConfig->refVolSel = (AdcDrv_RefVolt)AdcReg_GetSc2RefSel(obj->adcReg);

    /* get enable DMA */
    currentConfig->dmaEnable = AdcReg_GetSc2DmaEn(obj->adcReg);

    if(obj->adcNumber == ADCDRV_INSTANCE_0)
    {
        /* get hardware trigger source */
        currentConfig->trgSrcCfg.hwTrgSrc = (AdcDrv_HwTrgSrc)SimReg_GetAdcTrg0Src(obj->simReg);

        /* get software pretrigger source */
        currentConfig->trgSrcCfg.swPretrgSrc = (ADCDRV_SwPretrgSrc)SimReg_GetAdcPreTrg0SwSrc(obj->simReg);

        /* get pretrigger source */
        currentConfig->trgSrcCfg.pretrgSrc = (ADCDRV_PretrgSrc)SimReg_GetAdcPreTrg0Src(obj->simReg);
    }
    else if(obj->adcNumber == ADCDRV_INSTANCE_1)
    {
        /* get hardware trigger source */
        currentConfig->trgSrcCfg.hwTrgSrc = (AdcDrv_HwTrgSrc)SimReg_GetAdcTrg1Src(obj->simReg);

        /* get software pretrigger source */
        currentConfig->trgSrcCfg.swPretrgSrc = (ADCDRV_SwPretrgSrc)SimReg_GetAdcPreTrg1SwSrc(obj->simReg);

        /* get pretrigger source */
        currentConfig->trgSrcCfg.pretrgSrc = (ADCDRV_PretrgSrc)SimReg_GetAdcPreTrg1Src(obj->simReg);
    }

    /* get the continuous mode */
    currentConfig->continuousMode = (AdcDrv_ContinuousMode)AdcReg_GetSc3Adco(obj->adcReg);

    /* get configuration the ADC compare function */
    AdcDrv_GetCmpCfg(obj, &currentConfig->cmpCfg);

    /* get hardware average sample configuration*/
    currentConfig->avgEnable = AdcReg_GetSc3AvgE(obj->adcReg);

    /* get the hardware average sample number */
    currentConfig->avgSamplesSel = (AdcDrv_AverageMode)AdcReg_GetSc3AvgS(obj->adcReg);

    /* get configuration for each ADC channel */
    uint8_t i;
    for(i = 0; i < ADCDRV_CHANNEL_NUM; i++)
    {
        /* get the ADC channel input */
        currentConfig->chnCfg[i].chnSel = (AdcDrv_InChnType)AdcReg_GetScAdCh(obj->adcReg, i);

        /* get the interrupt for ADC channel state*/
        currentConfig->chnCfg[i].intEnable = AdcReg_GetScAIEn(obj->adcReg, i);
    }

    /* get interleave channel state */
    AdcDrv_GetInterleave(obj, &(currentConfig->interleaveMode));
}
