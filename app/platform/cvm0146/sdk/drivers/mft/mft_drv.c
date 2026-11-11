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

#include "mft_drv.h"

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

/*! \brief Reset the MFT all registers
 *
 * This function resets MFT all registers.
 *
 * \param[in] obj : pointer to MFT driver instance
 */
void MftDrv_Reset(MftDrvType *obj)
{
    uint8_t channel   = 0;
    uint8_t pairIndex = 0;

    /* WPDIS is set when WPEN bit is read as a 1 and then 1 is written to WPDIS */
    obj->reg->FMS &= 0U;
    /* This is the reset value for MODE register. WPDIS bit is set to disable write protection */
    obj->reg->MODE = 0x00000004U;
    obj->reg->CNT  = 0U;
    obj->reg->SC &= 0U;
    obj->reg->MODULO = 0U;
    obj->reg->CNTIN  = 0U;
    obj->reg->STATUS &= 0U;
    obj->reg->SYNC     = 0U;
    obj->reg->OUTINIT  = 0U;
    obj->reg->OUTMASK  = 0U;
    obj->reg->COMBINE  = 0U;
    obj->reg->DEADTIME = 0U;
    obj->reg->EXTTRIG &= 0U;
    obj->reg->POL        = 0U;
    obj->reg->FILTER     = 0U;
    obj->reg->FLTCTRL    = 0U;
    obj->reg->QDCTRL     = 0U;
    obj->reg->CONF       = 0U;
    obj->reg->FLTPOL     = 0U;
    obj->reg->SYNCONF    = 0U;
    obj->reg->INVCTRL    = 0U;
    obj->reg->SWOCTRL    = 0U;
    obj->reg->PWMLOAD    = 0U;
    obj->reg->HCR        = 0U;
    obj->reg->MOD_MIRROR = 0U;
    obj->reg->SIM_OBE    = 0U;

    for(channel = 0; channel < MFT_CHANNEL_NUM; ++channel)
    {
        obj->reg->CH[channel].CSC    = 0;
        obj->reg->CH[channel].CV     = 0;
        obj->reg->MIRROR[channel].CV = 0;
    }
    for(pairIndex = 0; pairIndex < MFT_DEADTIME_PAIR; ++pairIndex)
    {
        obj->reg->PAIR[pairIndex].DEADTIME = 0;
    }
}

void MftDrv_Init(MftDrvType *obj, struct _MftRegType_ *reg)
{
    obj->reg = reg;
}

void MftDrv_GetDefaultConfig(MftDrv_ConfigType *userConfig)
{
    userConfig->clockSource  = MFTDRV_CLOCK_SOURCE_SYSTEMCLK;
    userConfig->countingMode = MFTDRV_UP_COUNTING;
    userConfig->prescaler    = MFTDRV_PRESCALE_DIV_BY_1;
    userConfig->bdmMode      = MFTDRV_BDM_MODE_11;
}

void MftDrv_Config(MftDrvType *obj, const MftDrv_ConfigType *userConfig)
{
    /* Reset the MFT module */
    MftDrv_Reset(obj);
    /* WPDIS = 1, disable write protection */
    MftReg_SetModeWpDis(obj->reg, 1);
    /* Enable MFT */
    MftReg_SetModeMftEn(obj->reg, 1);
    /* Set clock source */
    MftReg_SetScClks(obj->reg, userConfig->clockSource);
    /* Set the clock prescale */
    MftReg_SetScPs(obj->reg, userConfig->prescaler);
    /* Set BDM mode */
    MftReg_SetConfBdmMode(obj->reg, userConfig->bdmMode);
    /* Set Counting mode */
    MftReg_SetScCPwms(obj->reg, userConfig->countingMode == MFTDRV_UP_COUNTING ? 0 : 1);
    /* WPEN = 1, enable write protection */
    MftReg_SetFmsWpEn(obj->reg, 1);
}

void MftDrv_MaskOutputChannels(MftDrvType *obj, uint32_t channelsMask, bool softWareTrigger)
{
    obj->reg->OUTMASK = channelsMask;
    MftReg_SetSyncSwSync(obj->reg, softWareTrigger ? 1 : 0);
}

void MftDrv_SetInitialCounterValue(MftDrvType *obj, uint16_t counterValue, bool softWareTrigger)
{
    MftReg_SetCntInCntInit(obj->reg, counterValue);
    MftReg_SetSyncSwSync(obj->reg, softWareTrigger ? 1 : 0);
}

uint16_t MftDrv_GetChnCounterValue(MftDrvType *obj, uint8_t channel)
{
    return MftReg_GetCvVal(obj->reg, channel);
}

void MftDrv_SetHalfCycleReloadPoint(MftDrvType *obj, uint16_t reloadPoint, bool softWareTrigger)
{
    MftReg_SetHcrHCVal(obj->reg, reloadPoint);
    MftReg_SetSyncSwSync(obj->reg, softWareTrigger ? 1 : 0);
}

void MftDrv_SetSoftOutChnValue(MftDrvType *obj, uint8_t channelsValues, bool softWareTrigger)
{
    uint8_t  channelsMask = channelsValues ^ (uint8_t)obj->reg->POL;
    uint32_t mask         = MFT_SWOCTRL_CH0OCV_MASK | MFT_SWOCTRL_CH1OCV_MASK | MFT_SWOCTRL_CH2OCV_MASK | MFT_SWOCTRL_CH3OCV_MASK | MFT_SWOCTRL_CH4OCV_MASK | MFT_SWOCTRL_CH5OCV_MASK | MFT_SWOCTRL_CH6OCV_MASK | MFT_SWOCTRL_CH7OCV_MASK;
    obj->reg->SWOCTRL     = ((obj->reg->SWOCTRL) & (~(mask))) | ((uint32_t)channelsMask << MFT_SWOCTRL_CH0OCV_SHIFT);

    MftReg_SetSyncSwSync(obj->reg, softWareTrigger ? 1 : 0);
}

void MftDrv_SetSoftwareOutputChannelControl(MftDrvType *obj, uint8_t channelsMask, bool softWareTrigger)
{
    uint32_t mask     = MFT_SWOCTRL_CH0OC_MASK | MFT_SWOCTRL_CH1OC_MASK | MFT_SWOCTRL_CH2OC_MASK | MFT_SWOCTRL_CH3OC_MASK | MFT_SWOCTRL_CH4OC_MASK | MFT_SWOCTRL_CH5OC_MASK | MFT_SWOCTRL_CH6OC_MASK | MFT_SWOCTRL_CH7OC_MASK;
    obj->reg->SWOCTRL = ((obj->reg->SWOCTRL) & (~(mask))) | channelsMask;

    MftReg_SetSyncSwSync(obj->reg, softWareTrigger ? 1 : 0);
}

void MftDrv_SetAllChnSoftwareOutputControl(MftDrvType *obj, uint8_t channelMask, uint8_t channelValueMask, bool softWareTrigger)
{
    uint16_t value = 0U;

    value             = (uint16_t)(((uint16_t)channelValueMask ^ (uint16_t)obj->reg->POL) << (uint16_t)8U) | (uint16_t)channelMask;
    obj->reg->SWOCTRL = value;

    MftReg_SetSyncSwSync(obj->reg, softWareTrigger ? 1 : 0);
}

void MftDrv_SetInvertingControl(MftDrvType *obj, uint8_t channelsPairMask, bool softWareTrigger)
{
    obj->reg->INVCTRL = channelsPairMask;
    MftReg_SetSyncSwSync(obj->reg, softWareTrigger ? 1 : 0);
}

void MftDrv_SetModuloCounterValue(MftDrvType *obj, uint16_t counterValue, bool softWareTrigger)
{
    MftReg_SetModuloMod(obj->reg, counterValue);
    MftReg_SetSyncSwSync(obj->reg, softWareTrigger ? 1 : 0);
}

void MftDrv_SetOutputlevel(MftDrvType *obj, uint8_t channel, uint8_t level)
{
    MftReg_SetCscElsa(obj->reg, channel, (level & 0x01U));
    MftReg_SetCscElsb(obj->reg, channel, (level & 0x02U) >> 1U);
}

void MftDrv_EnableInterrupts(MftDrvType *obj, uint32_t interruptMask)
{
    uint32_t chnlInts = (interruptMask & 0x000000FFU);
    uint8_t  channel  = 0U;

    /* Enable the timer overflow interrupt */
    if((interruptMask & (uint32_t)MFTDRV_TIME_OVERFLOW_INT_ENABLE) != 0x0U)
    {
        MftReg_SetScToie(obj->reg, 1);
    }

    /* Enable the fault interrupt */
    if((interruptMask & (uint32_t)MFTDRV_FAULT_INT_ENABLE) != 0x0U)
    {
        MftReg_SetModeFaultIE(obj->reg, 1);
    }

    /* Enable the reload interrupt */
    if((interruptMask & (uint32_t)MFTDRV_RELOAD_INT_ENABLE) != 0x0U)
    {
        MftReg_SetScRie(obj->reg, 1);
    }

    /* Enable the channel interrupts */
    while(chnlInts != 0U)
    {
        if((chnlInts & 0x1U) != 0x0U)
        {
            MftReg_SetCscChie(obj->reg, channel, 1);
        }
        channel++;
        chnlInts = chnlInts >> 1U;
    }
}

void MftDrv_DisableInterrupts(MftDrvType *obj, uint32_t InterruptMask)
{
    uint32_t chnlInts = (InterruptMask & 0x000000FFU);
    uint8_t  channel  = 0U;

    /* Disable the timer overflow interrupt */
    if((InterruptMask & (uint32_t)MFTDRV_TIME_OVERFLOW_INT_ENABLE) != 0x0U)
    {
        MftReg_SetScToie(obj->reg, 0);
    }

    /* Disable the fault interrupt */
    if((InterruptMask & (uint32_t)MFTDRV_FAULT_INT_ENABLE) != 0x0U)
    {
        MftReg_SetModeFaultIE(obj->reg, 0);
    }

    /* Disable the reload interrupt */
    if((InterruptMask & (uint32_t)MFTDRV_RELOAD_INT_ENABLE) != 0x0U)
    {
        MftReg_SetScRie(obj->reg, 0);
    }

    /* Disable the channel interrupts */
    while(chnlInts != 0U)
    {
        if((chnlInts & 0x1U) != 0x0U)
        {
            MftReg_SetCscChie(obj->reg, channel, 0);
        }
        channel++;
        chnlInts = chnlInts >> 1U;
    }
}

uint32_t MftDrv_GetEnabledInterrupts(MftDrvType *obj)
{
    uint32_t enabledInterrupts = 0U;
    uint8_t  channel           = 0;

    /* Check if timer overflow interrupt is enabled */
    if(MftReg_GetScToie(obj->reg) == 1)
    {
        enabledInterrupts |= (uint32_t)MFTDRV_TIME_OVERFLOW_INT_ENABLE;
    }

    /* Check if fault interrupt is enabled */
    if(MftReg_GetModeFaultIE(obj->reg) == 1)
    {
        enabledInterrupts |= (uint32_t)MFTDRV_FAULT_INT_ENABLE;
    }

    /* Check if the reload interrupt is enabled */
    if(MftReg_GetScRie(obj->reg) == 1)
    {
        enabledInterrupts |= (uint32_t)MFTDRV_RELOAD_INT_ENABLE;
    }

    /* Check if the channel interrupts are enabled */
    for(channel = 0U; channel < MFT_CHANNEL_NUM; channel++)
    {
        if(MftReg_GetCscChie(obj->reg, channel) == 1)
        {
            enabledInterrupts |= (1UL << (uint32_t)channel);
        }
    }

    return enabledInterrupts;
}

uint32_t MftDrv_GetStatusFlags(MftDrvType *obj)
{
    uint8_t  channel     = 0U;
    uint32_t statusFlags = 0U;

    /* Check the timer flag */
    if(MftReg_GetScTof(obj->reg) == 1)
    {
        statusFlags |= (uint32_t)MFTDRV_TIME_OVER_FLOW_FLAG;
    }

    /* Check fault flag */
    if(MftReg_GetFmsFaultF(obj->reg) == 1)
    {
        statusFlags |= (uint32_t)MFTDRV_FAULT_FLAG;
    }

    /* Check reload flag */
    if(MftReg_GetScRf(obj->reg) == 1)
    {
        statusFlags |= (uint32_t)MFTDRV_RELOAD_FLAG;
    }

    /* Check channel trigger flag */
    if(MftReg_GetExtTrigTrigF(obj->reg) == 1)
    {
        statusFlags |= (uint32_t)MFTDRV_CHANNEL_TRIGGER_FLAG;
    }

    /* Lower 8 bits contain the channel status flags */
    for(channel = 0U; channel < MFT_CHANNEL_NUM; channel++)
    {
        if(MftReg_GetCscChf(obj->reg, channel) == 1)
        {
            statusFlags |= (1UL << (uint32_t)channel);
        }
    }

    return statusFlags;
}

void MftDrv_ClearStatusFlags(MftDrvType *obj, uint32_t flagMask)
{
    /* Clear the timer overflow flag by writing a 0 to the bit while it is set */
    if((flagMask & (uint32_t)MFTDRV_TIME_OVER_FLOW_FLAG) != 0x0U)
    {
        MftReg_SetScTof(obj->reg, 0);
    }

    /* Clear fault flag by writing a 0 to the bit while it is set */
    if((flagMask & (uint32_t)MFTDRV_FAULT_FLAG) != 0x0U)
    {
        MftReg_SetFmsFaultF0(obj->reg, 0);
        MftReg_SetFmsFaultF1(obj->reg, 0);
        MftReg_SetFmsFaultF2(obj->reg, 0);
        MftReg_SetFmsFaultF3(obj->reg, 0);
        /* FAULTF is also cleared when FAULTF bit of each enabled fault input is cleared */
        MftReg_SetFmsFaultF(obj->reg, 0);
    }

    /* Check reload flag by writing a 0 to the bit while it is set */
    if((flagMask & (uint32_t)MFTDRV_RELOAD_FLAG) != 0x0U)
    {
        MftReg_SetScRf(obj->reg, 0);
    }

    /* Clear channel trigger flag */
    if((flagMask & (uint32_t)MFTDRV_CHANNEL_TRIGGER_FLAG) != 0x0U)
    {
        MftReg_SetExtTrigTrigF(obj->reg, 0);
    }

    /* Clear the channel status flags by writing a 0 to the bit */
    if((flagMask & (uint32_t)MFTDRV_CHANNEL7_FLAG) != 0x0U)
    {
        MftReg_SetStatusCh7F(obj->reg, 0);
    }
    if((flagMask & (uint32_t)MFTDRV_CHANNEL6_FLAG) != 0x0U)
    {
        MftReg_SetStatusCh6F(obj->reg, 0);
    }
    if((flagMask & (uint32_t)MFTDRV_CHANNEL5_FLAG) != 0x0U)
    {
        MftReg_SetStatusCh5F(obj->reg, 0);
    }
    if((flagMask & (uint32_t)MFTDRV_CHANNEL4_FLAG) != 0x0U)
    {
        MftReg_SetStatusCh4F(obj->reg, 0);
    }
    if((flagMask & (uint32_t)MFTDRV_CHANNEL3_FLAG) != 0x0U)
    {
        MftReg_SetStatusCh3F(obj->reg, 0);
    }
    if((flagMask & (uint32_t)MFTDRV_CHANNEL2_FLAG) != 0x0U)
    {
        MftReg_SetStatusCh2F(obj->reg, 0);
    }
    if((flagMask & (uint32_t)MFTDRV_CHANNEL1_FLAG) != 0x0U)
    {
        MftReg_SetStatusCh1F(obj->reg, 0);
    }
    if((flagMask & (uint32_t)MFTDRV_CHANNEL0_FLAG) != 0x0U)
    {
        MftReg_SetStatusCh0F(obj->reg, 0);
    }
}

void MftDrv_CounterReset(MftDrvType *obj, bool softWareTrigger)
{
    /* Updates the counter with its initial value */
    MftReg_SetCntCount(obj->reg, 0U);
    /* Set a software trigger or waiting a hardware trigger */
    MftReg_SetSyncSwSync(obj->reg, softWareTrigger ? 1 : 0);
}

void MftDrv_SetDualEdgeCaptureCmd(MftDrvType *obj, uint8_t pairNum, bool enable)
{
    uint8_t enableValue = enable ? 1 : 0;
    switch(pairNum)
    {
    case 0:
        MftReg_SetCombineDecapEn0(obj->reg, enableValue);
        break;
    case 1:
        MftReg_SetCombineDecapEn1(obj->reg, enableValue);
        break;
    case 2:
        MftReg_SetCombineDecapEn2(obj->reg, enableValue);
        break;
    case 3:
        MftReg_SetCombineDecapEn3(obj->reg, enableValue);
        break;
    default:
        break;
    }
}

void MftDrv_SetDualChannelDecap(MftDrvType *obj, uint8_t pairNum, bool enable)
{
    uint8_t enableValue = enable ? 1 : 0;
    switch(pairNum)
    {
    case 0:
        MftReg_SetCombineDecap0(obj->reg, enableValue);
        break;
    case 1:
        MftReg_SetCombineDecap1(obj->reg, enableValue);
        break;
    case 2:
        MftReg_SetCombineDecap2(obj->reg, enableValue);
        break;
    case 3:
        MftReg_SetCombineDecap3(obj->reg, enableValue);
        break;
    default:
        break;
    }
}

bool MftDrv_GetDualEdgeCaptureCmd(MftDrvType *obj, uint8_t pairNum)
{
    bool retval = false;
    switch(pairNum)
    {
    case 0:
        retval = MftReg_GetCombineDecapEn0(obj->reg) == 1;
        break;
    case 1:
        retval = MftReg_GetCombineDecapEn1(obj->reg) == 1;
        break;
    case 2:
        retval = MftReg_GetCombineDecapEn2(obj->reg) == 1;
        break;
    case 3:
        retval = MftReg_GetCombineDecapEn3(obj->reg) == 1;
        break;
    default:
        break;
    }

    return retval;
}

void MftDrv_SetDualChannelComp(MftDrvType *obj, uint8_t pairNum, bool enable)
{
    uint8_t enableValue = enable ? 1 : 0;
    switch(pairNum)
    {
    case 0:
        MftReg_SetCombineComp0(obj->reg, enableValue);
        break;
    case 1:
        MftReg_SetCombineComp1(obj->reg, enableValue);
        break;
    case 2:
        MftReg_SetCombineComp2(obj->reg, enableValue);
        break;
    case 3:
        MftReg_SetCombineComp3(obj->reg, enableValue);
        break;
    default:
        break;
    }
}

void MftDrv_SetDualChannelCombine(MftDrvType *obj, uint8_t pairNum, bool enable)
{
    uint8_t enableValue = enable ? 1 : 0;
    switch(pairNum)
    {
    case 0:
        MftReg_SetCombineCombine0(obj->reg, enableValue);
        break;
    case 1:
        MftReg_SetCombineCombine1(obj->reg, enableValue);
        break;
    case 2:
        MftReg_SetCombineCombine2(obj->reg, enableValue);
        break;
    case 3:
        MftReg_SetCombineCombine3(obj->reg, enableValue);
        break;
    default:
        break;
    }
}

void MftDrv_SetDualChannelModifiedCombine(MftDrvType *obj, uint8_t pairNum, bool enable)
{
    uint8_t enableValue = enable ? 1 : 0;
    switch(pairNum)
    {
    case 0:
        MftReg_SetCombineMCombine0(obj->reg, enableValue);
        break;
    case 1:
        MftReg_SetCombineMCombine1(obj->reg, enableValue);
        break;
    case 2:
        MftReg_SetCombineMCombine2(obj->reg, enableValue);
        break;
    case 3:
        MftReg_SetCombineMCombine3(obj->reg, enableValue);
        break;
    default:
        break;
    }
}

void MftDrv_SetDualChannelFault(MftDrvType *obj, uint8_t pairNum, bool enable)
{
    uint8_t enableValue = enable ? 1 : 0;
    switch(pairNum)
    {
    case 0:
        MftReg_SetCombineFaultEn0(obj->reg, enableValue);
        break;
    case 1:
        MftReg_SetCombineFaultEn1(obj->reg, enableValue);
        break;
    case 2:
        MftReg_SetCombineFaultEn2(obj->reg, enableValue);
        break;
    case 3:
        MftReg_SetCombineFaultEn3(obj->reg, enableValue);
        break;
    default:
        break;
    }
}

void MftDrv_SetDualChannelPwmSync(MftDrvType *obj, uint8_t pairNum, bool enable)
{
    uint8_t enableValue = enable ? 1 : 0;
    switch(pairNum)
    {
    case 0:
        MftReg_SetCombineSyncEn0(obj->reg, enableValue);
        break;
    case 1:
        MftReg_SetCombineSyncEn1(obj->reg, enableValue);
        break;
    case 2:
        MftReg_SetCombineSyncEn2(obj->reg, enableValue);
        break;
    case 3:
        MftReg_SetCombineSyncEn3(obj->reg, enableValue);
        break;
    default:
        break;
    }
}

void MftDrv_EnablePwmChannelOutputs(MftDrvType *obj, uint8_t channel, bool enable)
{
    uint8_t enableValue = enable ? 1 : 0;
    switch(channel)
    {
    case 0:
        MftReg_SetScPwmEn0(obj->reg, enableValue);
        break;
    case 1:
        MftReg_SetScPwmEn1(obj->reg, enableValue);
        break;
    case 2:
        MftReg_SetScPwmEn2(obj->reg, enableValue);
        break;
    case 3:
        MftReg_SetScPwmEn3(obj->reg, enableValue);
        break;
    case 4:
        MftReg_SetScPwmEn4(obj->reg, enableValue);
        break;
    case 5:
        MftReg_SetScPwmEn5(obj->reg, enableValue);
        break;
    case 6:
        MftReg_SetScPwmEn6(obj->reg, enableValue);
        break;
    case 7:
        MftReg_SetScPwmEn7(obj->reg, enableValue);
        break;
    default:
        break;
    }
}

void MftDrv_SetChannelTriggerCmd(MftDrvType *obj, uint8_t channel, bool enable)
{
    uint8_t enableValue = enable ? 1 : 0;
    switch(channel)
    {
    case 0:
        MftReg_SetExtTrigCh0Trig(obj->reg, enableValue);
        break;
    case 1:
        MftReg_SetExtTrigCh1Trig(obj->reg, enableValue);
        break;
    case 2:
        MftReg_SetExtTrigCh2Trig(obj->reg, enableValue);
        break;
    case 3:
        MftReg_SetExtTrigCh3Trig(obj->reg, enableValue);
        break;
    case 4:
        MftReg_SetExtTrigCh4Trig(obj->reg, enableValue);
        break;
    case 5:
        MftReg_SetExtTrigCh5Trig(obj->reg, enableValue);
        break;
    case 6:
        MftReg_SetExtTrigCh6Trig(obj->reg, enableValue);
        break;
    case 7:
        MftReg_SetExtTrigCh7Trig(obj->reg, enableValue);
        break;
    default:
        break;
    }
}

void MftDrv_SoftWareTrigger(MftDrvType *obj)
{
    MftReg_SetSyncSwSync(obj->reg, 1);
}
