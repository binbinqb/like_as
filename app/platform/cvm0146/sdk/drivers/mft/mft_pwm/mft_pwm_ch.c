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
#include "mft_pwm_ch.h"
#include "mft_pwm_drv.h"

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

/*! \brief Set the polarity of the channel
 *
 * This function sets the polarity of the channel
 *
 * \param[in] obj : pointer to MFT driver instance
 * \param[in] channel : The MFT peripheral channel number
 * \param[in] polarity : the polarity of the channel
 */
static inline void MftPwmCh_SetPolarity(MftPwmChType *obj, uint8_t channel, MftPwmCh_PolarityType polarity)
{
    switch(channel)
    {
    case 0:
        MftReg_SetPolPol0(obj->pwmDrv->base->reg, (uint8_t)polarity);
        break;
    case 1:
        MftReg_SetPolPol1(obj->pwmDrv->base->reg, (uint8_t)polarity);
        break;
    case 2:
        MftReg_SetPolPol2(obj->pwmDrv->base->reg, (uint8_t)polarity);
        break;
    case 3:
        MftReg_SetPolPol3(obj->pwmDrv->base->reg, (uint8_t)polarity);
        break;
    case 4:
        MftReg_SetPolPol4(obj->pwmDrv->base->reg, (uint8_t)polarity);
        break;
    case 5:
        MftReg_SetPolPol5(obj->pwmDrv->base->reg, (uint8_t)polarity);
        break;
    case 6:
        MftReg_SetPolPol6(obj->pwmDrv->base->reg, (uint8_t)polarity);
        break;
    case 7:
        MftReg_SetPolPol7(obj->pwmDrv->base->reg, (uint8_t)polarity);
        break;
    default:
        break;
    }
}

/*! \brief Enables or disables PWM channel pair deadtime insertion.
 *
 * This function enables or disables PWM channel pair deadtime insertion.
 *
 * \param[in] obj : pointer to MFT driver instance
 * \param[in] pairNum : The MFT peripheral channel number
 * \param[in] enable : whether to enable PWM channel pair deadtime insertion.
 *                     - true : enable PWM channel pair deadtime insertion.
 *                     - false : disable PWM channel pair deadtime insertion.
 */
static inline void MftPwmCh_SetDualChannelDeadtimeCmd(MftPwmChType *obj, uint8_t pairNum, bool enable)
{
    uint8_t enableValue = enable ? 1 : 0;
    switch(pairNum)
    {
    case 0:
        MftReg_SetCombineDtEn0(obj->pwmDrv->base->reg, enableValue);
        break;
    case 1:
        MftReg_SetCombineDtEn1(obj->pwmDrv->base->reg, enableValue);
        break;
    case 2:
        MftReg_SetCombineDtEn2(obj->pwmDrv->base->reg, enableValue);
        break;
    case 3:
        MftReg_SetCombineDtEn3(obj->pwmDrv->base->reg, enableValue);
        break;
    default:
        break;
    }
}

void MftPwmCh_Init(MftPwmChType *obj, struct _MftPwmDrvType_ *pwmDrv)
{
    obj->pwmDrv = pwmDrv;
}

void MftPwmCh_GetDefaultConfig(MftPwmCh_ConfigType *userConfig)
{
    userConfig->hwChannelId                    = 0;
    userConfig->pulseMode                      = MFTPWMCH_SET_ON_MATCH_UP;
    userConfig->mainChannelPolarity            = MFTPWMCH_ACTIVE_HIGH;
    userConfig->enableExternalTrigger          = false;
    userConfig->enableFaultCtrl                = false;
    userConfig->enableSecondChannelOutput      = false;
    userConfig->enableComplementary            = false;
    userConfig->enableCombine                  = false;
    userConfig->enableModifiedCombine          = false;
    userConfig->deadTime                       = false;
    userConfig->secondChannelPolarity          = MFTPWMCH_ACTIVE_HIGH;
    userConfig->enableExternalTriggerOnNextChn = false;
}

bool MftPwmCh_Config(MftPwmChType *obj, const MftPwmCh_ConfigType *userConfig)
{
    bool status = true;
    /* WPDIS = 1, disable write protection */
    MftReg_SetModeWpDis(obj->pwmDrv->base->reg, 1);

    obj->config.hwChannelId = userConfig->hwChannelId;
    /* MSB:MSA = 1:1 */
    MftReg_SetCscMsb(obj->pwmDrv->base->reg, obj->config.hwChannelId, 1);
    MftReg_SetCscMsa(obj->pwmDrv->base->reg, obj->config.hwChannelId, 1);

    if(false == userConfig->enableSecondChannelOutput)
    {
        /* Independent channel */
        /* Set Polarity */
        MftPwmCh_SetPolarity(obj, userConfig->hwChannelId, userConfig->mainChannelPolarity);
        /* Set pulse mode */
        if(MFTPWMCH_CLEAR_ON_MATCH_UP == userConfig->pulseMode)
        {
            /* ELSnB:ELSnA = 1:0 */
            MftReg_SetCscElsb(obj->pwmDrv->base->reg, userConfig->hwChannelId, 1);
            MftReg_SetCscElsa(obj->pwmDrv->base->reg, userConfig->hwChannelId, 0);
        }
        else if(MFTPWMCH_SET_ON_MATCH_UP == userConfig->pulseMode)
        {
            /* ELSnB:ELSnA = 0:1 */
            MftReg_SetCscElsb(obj->pwmDrv->base->reg, userConfig->hwChannelId, 0);
            MftReg_SetCscElsa(obj->pwmDrv->base->reg, userConfig->hwChannelId, 1);
        }
        uint8_t pairNum = userConfig->hwChannelId >> 1;
        /* COMP = 0 */
        MftDrv_SetDualChannelComp(obj->pwmDrv->base, pairNum, false);
        /* COMBINE = 0 */
        MftDrv_SetDualChannelCombine(obj->pwmDrv->base, pairNum, false);
        /* MCOMBINE = 0 */
        MftDrv_SetDualChannelModifiedCombine(obj->pwmDrv->base, pairNum, false);
        /* DECAP = 0 */
        MftDrv_SetDualChannelDecap(obj->pwmDrv->base, pairNum, false);
        /* FAULTEN */
        MftDrv_SetDualChannelFault(obj->pwmDrv->base, pairNum, userConfig->enableFaultCtrl);
        /* PWMSYNC */
        MftDrv_SetDualChannelPwmSync(obj->pwmDrv->base, pairNum, true);
        /* External trigger */
        MftDrv_SetChannelTriggerCmd(obj->pwmDrv->base, userConfig->hwChannelId, userConfig->enableExternalTrigger);
        /* Enable PWM output on channel (n) */
        MftDrv_EnablePwmChannelOutputs(obj->pwmDrv->base, userConfig->hwChannelId, true);
    }
    else
    {
        if(userConfig->hwChannelId % 2 != 0)
        {
            /* Must be even */
            return false;
        }
        /* MSB:MSA = 1:1 */
        MftReg_SetCscMsb(obj->pwmDrv->base->reg, userConfig->hwChannelId + 1, 1);
        MftReg_SetCscMsa(obj->pwmDrv->base->reg, userConfig->hwChannelId + 1, 1);

        /* Dual channel modes */
        uint8_t pairNum = userConfig->hwChannelId >> 1;
        /* DECAP = 0 */
        MftDrv_SetDualChannelDecap(obj->pwmDrv->base, pairNum, false);
        /* PWMSYNC */
        MftDrv_SetDualChannelPwmSync(obj->pwmDrv->base, pairNum, true);
        /* Set Polarity */
        MftPwmCh_SetPolarity(obj, userConfig->hwChannelId, userConfig->mainChannelPolarity);
        MftPwmCh_SetPolarity(obj, userConfig->hwChannelId + 1, userConfig->secondChannelPolarity);
        /* External trigger */
        MftDrv_SetChannelTriggerCmd(obj->pwmDrv->base, userConfig->hwChannelId, userConfig->enableExternalTrigger);
        MftDrv_SetChannelTriggerCmd(obj->pwmDrv->base, userConfig->hwChannelId + 1, userConfig->enableExternalTriggerOnNextChn);
        /* Enable PWM output on channel (n) and channel (n+1) */
        MftDrv_EnablePwmChannelOutputs(obj->pwmDrv->base, userConfig->hwChannelId, true);
        MftDrv_EnablePwmChannelOutputs(obj->pwmDrv->base, userConfig->hwChannelId + 1, true);
        /* FAULTEN */
        MftDrv_SetDualChannelFault(obj->pwmDrv->base, pairNum, userConfig->enableFaultCtrl);
        
        if(true == userConfig->enableComplementary)
        {
            /* Complementary Mode, this configure has higher priority than combined/mcombined mode */
            /* COMP = 1 */
            MftDrv_SetDualChannelComp(obj->pwmDrv->base, pairNum, true);

            /* MCOMBINE = 0 */
            MftDrv_SetDualChannelModifiedCombine(obj->pwmDrv->base, pairNum, false);
            /* Dead time */
            MftPwmCh_SetDualChannelDeadtimeCmd(obj, pairNum, userConfig->deadTime);

            if(MftReg_GetScCPwms(obj->pwmDrv->base->reg))
            {
                /* COMBINE = 0 */
                MftDrv_SetDualChannelCombine(obj->pwmDrv->base, pairNum, false);
                /* Set pulse mode */
                if(MFTPWMCH_CLEAR_ON_MATCH_UP == userConfig->pulseMode)
                {
                    /* ELSnB:ELSnA = 1:0 */
                    /* ELSnB:ELSnA of channel (n+1) not used */
                    MftReg_SetCscElsb(obj->pwmDrv->base->reg, userConfig->hwChannelId, 1);
                    MftReg_SetCscElsa(obj->pwmDrv->base->reg, userConfig->hwChannelId, 0);
                }
                else if(MFTPWMCH_SET_ON_MATCH_UP == userConfig->pulseMode)
                {
                    /* ELSnB:ELSnA = 0:1 */
                    /* ELSnB:ELSnA of channel (n+1) not used */
                    MftReg_SetCscElsb(obj->pwmDrv->base->reg, userConfig->hwChannelId, 0);
                    MftReg_SetCscElsa(obj->pwmDrv->base->reg, userConfig->hwChannelId, 1);
                }
            }
            else
            {
                /* COMBINE = 1 */
                MftDrv_SetDualChannelCombine(obj->pwmDrv->base, pairNum, true);

                /* Set pulse mode */
                if(MFTPWMCH_SET_ON_MATCH_UP == userConfig->pulseMode)
                {
                    /* ELSnB:ELSnA = 1:0 */
                    /* ELSnB:ELSnA of channel (n+1) not used */
                    MftReg_SetCscElsb(obj->pwmDrv->base->reg, userConfig->hwChannelId, 1);
                    MftReg_SetCscElsa(obj->pwmDrv->base->reg, userConfig->hwChannelId, 0);
                }
                else if(MFTPWMCH_CLEAR_ON_MATCH_UP == userConfig->pulseMode)
                {
                    /* ELSnB:ELSnA = 0:1 */
                    /* ELSnB:ELSnA of channel (n+1) not used */
                    MftReg_SetCscElsb(obj->pwmDrv->base->reg, userConfig->hwChannelId, 0);
                    MftReg_SetCscElsa(obj->pwmDrv->base->reg, userConfig->hwChannelId, 1);
                }
            }
        }
        else if(false == userConfig->enableModifiedCombine
                && true == userConfig->enableCombine)
        {
            if(MftReg_GetScCPwms(obj->pwmDrv->base->reg))
            {
                /* CPWM does not support Combine mode*/
                status = false;
            }
            else
            {
                /* Combine Mode */
                /* COMP = 0 */
                MftDrv_SetDualChannelComp(obj->pwmDrv->base, pairNum, false);
                /* COMBINE = 1 */
                MftDrv_SetDualChannelCombine(obj->pwmDrv->base, pairNum, true);
                /* MCOMBINE = 0 */
                MftDrv_SetDualChannelModifiedCombine(obj->pwmDrv->base, pairNum, false);
                /* Set pulse mode */
                if(MFTPWMCH_SET_ON_MATCH_UP == userConfig->pulseMode)
                {
                    /* ELSnB:ELSnA = 1:0 */
                    /* ELSnB:ELSnA of channel (n+1) not used */
                    MftReg_SetCscElsb(obj->pwmDrv->base->reg, userConfig->hwChannelId, 1);
                    MftReg_SetCscElsa(obj->pwmDrv->base->reg, userConfig->hwChannelId, 0);
                }
                else if(MFTPWMCH_CLEAR_ON_MATCH_UP == userConfig->pulseMode)
                {
                    /* ELSnB:ELSnA = 0:1 */
                    /* ELSnB:ELSnA of channel (n+1) not used */
                    MftReg_SetCscElsb(obj->pwmDrv->base->reg, userConfig->hwChannelId, 0);
                    MftReg_SetCscElsa(obj->pwmDrv->base->reg, userConfig->hwChannelId, 1);
                }
            }
        }
        else if(true == userConfig->enableModifiedCombine
                && true == userConfig->enableCombine)
        {
            if(MftReg_GetScCPwms(obj->pwmDrv->base->reg))
            {
                /* CPWM does not support Combine mode */
                status = false;
            }
            else
            {
                /* Modified combine Mode */
                /* COMP = 0 */
                MftDrv_SetDualChannelComp(obj->pwmDrv->base, pairNum, false);
                /* COMBINE = 1 */
                MftDrv_SetDualChannelCombine(obj->pwmDrv->base, pairNum, true);
                /* MCOMBINE = 1 */
                MftDrv_SetDualChannelModifiedCombine(obj->pwmDrv->base, pairNum, true);
                /* Set pulse mode */
                if(MFTPWMCH_SET_ON_MATCH_UP == userConfig->pulseMode)
                {
                    /* ELSnB:ELSnA = 1:0 */
                    /* ELSnB:ELSnA of channel (n+1) not used */
                    MftReg_SetCscElsb(obj->pwmDrv->base->reg, userConfig->hwChannelId, 1);
                    MftReg_SetCscElsa(obj->pwmDrv->base->reg, userConfig->hwChannelId, 0);
                }
                else if(MFTPWMCH_CLEAR_ON_MATCH_UP == userConfig->pulseMode)
                {
                    /* ELSnB:ELSnA = 0:1 */
                    /* ELSnB:ELSnA of channel (n+1) not used */
                    MftReg_SetCscElsb(obj->pwmDrv->base->reg, userConfig->hwChannelId, 0);
                    MftReg_SetCscElsa(obj->pwmDrv->base->reg, userConfig->hwChannelId, 1);
                }
            }
        }
    }

    /* WPEN = 1, enable write protection */
    MftReg_SetFmsWpEn(obj->pwmDrv->base->reg, 1);

    obj->config = *userConfig;

    return status;
}

void MftPwmCh_SetChannelValue(MftPwmChType *obj, uint16_t firstValue, uint16_t secondValue)
{
    if(MftReg_GetScCPwms(obj->pwmDrv->base->reg) == MFTDRV_UP_DOWN_COUNTING)
    {
        volatile uint16_t cntin;
        cntin = MftReg_GetCntInCntInit(obj->pwmDrv->base->reg);
        /* In CPWM mode, there is a problem with output when CNTIN=CnV and CNTIN=CnV+1 */
        if((firstValue == cntin) || (firstValue == cntin + 1))
        {
            firstValue = cntin + 2;
        }
    }
    MftReg_SetCvVal(obj->pwmDrv->base->reg, obj->config.hwChannelId, firstValue);
    if(obj->config.enableSecondChannelOutput)
    {
        MftReg_SetCvVal(obj->pwmDrv->base->reg, obj->config.hwChannelId + 1, secondValue);
    }
}

void MftPwmCh_EnableOutput(MftPwmChType *obj, bool enable)
{
    MftDrv_EnablePwmChannelOutputs(obj->pwmDrv->base, obj->config.hwChannelId, enable);
}
