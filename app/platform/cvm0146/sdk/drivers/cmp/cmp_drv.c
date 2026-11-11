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

#include "cmp_drv.h"
#include "cmp_reg.h"

/*******************************************************************************
 * the defines
 ******************************************************************************/

#define CMP_TEST_VOLTAGE_ENABLE   (0U)
#define CMP_TEST_VOLTAGE_DISABLE  (1U)
#define CMP_STATE_SE_SHIFT        (0U)
#define CMP_STATE_WE_SHIFT        (1U)
#define CMP_STATE_EN_SHIFT        (2U)

#define CMP_TRIGGER_FALLING_SHIFT (0U)
#define CMP_TRIGGER_RISING_SHIFT  (1U)
#define CMP_TRIGGER_MASK          (1U)

#define CMP_CHANNELSTATE_MASK     (1U)
#define CMP_CHANNEL_PRESTATE_MASK (1U)
#define CMP_CHNF_MASK             (1U)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

typedef enum
{
    CMPDRV_STATE_DISABLE0 = 0U,
    CMPDRV_STATE_DISABLE1 = 1U,
    CMPDRV_STATE_DISABLE2 = 2U,
    CMPDRV_STATE_DISABLE3 = 3U,
    CMPDRV_STATE_NOSAMPLE = 4U,
    CMPDRV_STATE_SE       = 5U,
    CMPDRV_STATE_WE       = 6U,
    CMPDRV_STATE_WE_SE    = 7U,
} CmpDrv_StateType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the functions
 ******************************************************************************/

/* Forward declaration */
CmpDrv_TriggerType CmpDrv_GetTriggerMode(const CmpDrvType *obj);

void CmpDrv_SetTriggerMode(CmpDrvType *obj, const CmpDrv_TriggerType mode);

CmpDrv_ModeType CmpDrv_GetMode(const CmpDrvType *obj);

void CmpDrv_SetMode(CmpDrvType *obj, const CmpDrv_ModeType mode, const uint8_t filter_sample_count, const uint8_t filter_sample_period);

uint8_t CmpDrv_GetChannelState(const CmpDrvType *obj);

void CmpDrv_SetChannelState(CmpDrvType *obj, const uint8_t channelState);

uint8_t CmpDrv_GetChannelPreState(const CmpDrvType *obj);

/* Forward declaration end */

void CmpDrv_Init(CmpDrvType *obj, struct _CmpRegType_ *reg)
{
    obj->reg = reg;
}

void CmpDrv_ConfigureNormal(CmpDrvType *obj, const CmpDrv_ConfigType *userConfig)
{
    /* Unclock CMP */
    CmpReg_UnlockReg(obj->reg);

    /* Disable CMP */
    CmpReg_SetEnReg(obj->reg, false);

    /* Get configuration of normal modes */
    CmpReg_SetDmaenReg(obj->reg, userConfig->normalCfg.dmaEnable);
    CmpDrv_SetTriggerMode(obj, userConfig->normalCfg.triggerMode);
    CmpDrv_SetMode(obj, userConfig->normalCfg.mode, userConfig->normalCfg.filterSampleCount, userConfig->normalCfg.filterSamplePeriod);
    CmpReg_SetPmodeReg(obj->reg, userConfig->normalCfg.powerMode);
    CmpReg_SetInvtReg(obj->reg, userConfig->normalCfg.inverterState);
    CmpReg_SetOpeReg(obj->reg, userConfig->normalCfg.pinState);
    CmpReg_SetCosReg(obj->reg, userConfig->normalCfg.outputSelect);
    CmpReg_SetHystctrReg(obj->reg, userConfig->normalCfg.hystLvl);
    CmpReg_SetOffsetReg(obj->reg, userConfig->normalCfg.hystOffsetState);
    CmpReg_SetLpfselReg(obj->reg, userConfig->normalCfg.lpfsel);

    /* Configuration of DAC */
    CmpReg_SetVrselReg(obj->reg, userConfig->dacCfg.dacVoltInSel);
    CmpReg_SetVoselReg(obj->reg, userConfig->dacCfg.dacVoltScale);
    CmpReg_SetDacenReg(obj->reg, userConfig->dacCfg.state);

    /* Configuration of analog mux */
    CmpReg_SetInpselReg(obj->reg, userConfig->muxCfg.posPortMux);
    CmpReg_SetInnselReg(obj->reg, userConfig->muxCfg.negPortMux);
    CmpReg_SetPselReg(obj->reg, userConfig->muxCfg.posInputMux);
    CmpReg_SetMselReg(obj->reg, userConfig->muxCfg.negInputMux);

    /* Disable Round-Robin mode & disable Round-Robin interrupt */
    CmpReg_SetRreReg(obj->reg, false);
    CmpReg_SetRrieReg(obj->reg, false);

    /* Clear all flags*/
    CmpDrv_ClearOutputFlags(obj);
    CmpDrv_ClearInputFlags(obj);

    /* lock CMP */
    CmpReg_LockReg(obj->reg);

    /*! \note When enable CMP depend on user(use CmpDrv_SetCmpState for enable CMP) */
}

void CmpDrv_ConfigureTriggerMode(CmpDrvType *obj, const CmpDrv_ConfigType *userConfig)
{
    /* Unclock CMP */
    CmpReg_UnlockReg(obj->reg);

    /* Disable CMP */
    CmpReg_SetEnReg(obj->reg, false);

    /* Get configuration of normal modes*/
    CmpReg_SetDmaenReg(obj->reg, userConfig->normalCfg.dmaEnable);
    CmpDrv_SetTriggerMode(obj, userConfig->normalCfg.triggerMode);
    CmpDrv_SetMode(obj, CMP_CONTINUOUS, userConfig->normalCfg.filterSampleCount, userConfig->normalCfg.filterSamplePeriod);
    CmpReg_SetPmodeReg(obj->reg, userConfig->normalCfg.powerMode);
    CmpReg_SetInvtReg(obj->reg, userConfig->normalCfg.inverterState);
    CmpReg_SetOpeReg(obj->reg, userConfig->normalCfg.pinState);
    CmpReg_SetCosReg(obj->reg, userConfig->normalCfg.outputSelect);
    CmpReg_SetHystctrReg(obj->reg, userConfig->normalCfg.hystLvl);
    CmpReg_SetOffsetReg(obj->reg, userConfig->normalCfg.hystOffsetState);
    CmpReg_SetLpfselReg(obj->reg, userConfig->normalCfg.lpfsel);

    /* Configuration of DAC */
    CmpReg_SetVrselReg(obj->reg, userConfig->dacCfg.dacVoltInSel);
    CmpReg_SetVoselReg(obj->reg, userConfig->dacCfg.dacVoltScale);
    CmpReg_SetDacenReg(obj->reg, userConfig->dacCfg.state);

    /* Configuration of analog mux */
    CmpReg_SetInpselReg(obj->reg, userConfig->muxCfg.posPortMux);
    CmpReg_SetInnselReg(obj->reg, userConfig->muxCfg.negPortMux);
    CmpReg_SetPselReg(obj->reg, userConfig->muxCfg.posInputMux);
    CmpReg_SetMselReg(obj->reg, userConfig->muxCfg.negInputMux);

    /* Configuration of round robin modes(disable) */
    CmpReg_SetRreReg(obj->reg, true);
    CmpReg_SetRrieReg(obj->reg, userConfig->rrCfg.intrEnable);
    CmpReg_SetFxmpReg(obj->reg, userConfig->rrCfg.fixedMuxPort);
    CmpReg_SetFxmxchReg(obj->reg, userConfig->rrCfg.fixedChnSel);
    CmpReg_SetNsamReg(obj->reg, userConfig->rrCfg.sampleCnt);
    CmpReg_SetInitmodReg(obj->reg, userConfig->rrCfg.initDelayCnt);
    CmpDrv_SetChannelState(obj, userConfig->rrCfg.channelState);
    CmpDrv_SetChannelPreState(obj, userConfig->rrCfg.channelPreState);

    /* Clear all flags */
    CmpDrv_ClearOutputFlags(obj);
    CmpDrv_ClearInputFlags(obj);

    /* lock CMP */
    CmpReg_LockReg(obj->reg);

    /*! \note When enable CMP depend on user(use CmpDrv_SetCmpState for enable CMP)*/
}

void CmpDrv_GetConfig(const CmpDrvType *obj, CmpDrv_ConfigType *userConfig)
{
    /* Get configuration of normal modes */
    userConfig->normalCfg.dmaEnable          = CmpReg_GetDmaenReg(obj->reg);
    userConfig->normalCfg.triggerMode        = CmpDrv_GetTriggerMode(obj);
    userConfig->normalCfg.mode               = CmpDrv_GetMode(obj);
    userConfig->normalCfg.filterSamplePeriod = CmpReg_GetFprReg(obj->reg);
    userConfig->normalCfg.filterSampleCount  = CmpReg_GetFilterCntReg(obj->reg);
    userConfig->normalCfg.powerMode          = (CmpDrv_PmodeType)(CmpReg_GetPmodeReg(obj->reg));
    userConfig->normalCfg.inverterState      = (CmpDrv_InvtType)(CmpReg_GetInvtReg(obj->reg));
    userConfig->normalCfg.pinState           = CmpReg_GetOpeReg(obj->reg);
    userConfig->normalCfg.outputSelect       = (CmpDrv_CosType)(CmpReg_GetCosReg(obj->reg));
    userConfig->normalCfg.hystLvl            = (CmpDrv_HystctrType)(CmpReg_GetHystctrReg(obj->reg));
    userConfig->normalCfg.hystOffsetState    = (CmpDrv_OffsetType)(CmpReg_GetOffsetReg(obj->reg));
    userConfig->normalCfg.lpfsel             = (CmpDrv_LpfselType)(CmpReg_GetLpfselReg(obj->reg));

    /* Configuration of DAC */
    userConfig->dacCfg.dacVoltInSel = (CmpDrv_VrselType)(CmpReg_GetVrselReg(obj->reg));
    userConfig->dacCfg.dacVoltScale = CmpReg_GetVoselReg(obj->reg);
    userConfig->dacCfg.state        = CmpReg_GetDacenReg(obj->reg);

    /* Get configuration of analog mux */
    userConfig->muxCfg.posPortMux  = (CmpDrv_InPortType)(CmpReg_GetInpselReg(obj->reg));
    userConfig->muxCfg.negPortMux  = (CmpDrv_InPortType)(CmpReg_GetInnselReg(obj->reg));
    userConfig->muxCfg.posInputMux = (CmpDrv_ChSelType)(CmpReg_GetPselReg(obj->reg));
    userConfig->muxCfg.negInputMux = (CmpDrv_ChSelType)(CmpReg_GetMselReg(obj->reg));

    /* Configuration of round robin modes */
    userConfig->rrCfg.intrEnable      = CmpReg_GetRrieReg(obj->reg);
    userConfig->rrCfg.fixedMuxPort    = (CmpDrv_FxmpType)(CmpReg_GetFxmpReg(obj->reg));
    userConfig->rrCfg.fixedChnSel     = (CmpDrv_ChSelType)(CmpReg_GetFxmxchReg(obj->reg));
    userConfig->rrCfg.sampleCnt       = CmpReg_GetNsamReg(obj->reg);
    userConfig->rrCfg.initDelayCnt    = CmpReg_GetInitmodReg(obj->reg);
    userConfig->rrCfg.channelState    = CmpDrv_GetChannelState(obj);
    userConfig->rrCfg.channelPreState = CmpDrv_GetChannelPreState(obj);
}

void CmpDrv_GetDefaultConfig(CmpDrv_ConfigType *userConfig)
{
    /* Configuration of normal modes */
    userConfig->normalCfg.dmaEnable          = false;
    userConfig->normalCfg.triggerMode        = CMP_BOTH_EDGES;
    userConfig->normalCfg.mode               = CMP_CONTINUOUS;
    userConfig->normalCfg.filterSamplePeriod = 0;
    userConfig->normalCfg.filterSampleCount  = 0;
    userConfig->normalCfg.powerMode          = CMPDRV_PMODE_LS;
    userConfig->normalCfg.inverterState      = CMPDRV_INVT_NORMAL;
    userConfig->normalCfg.pinState           = false;
    userConfig->normalCfg.outputSelect       = CMPDRV_COS_COUT;
    userConfig->normalCfg.hystLvl            = CMPDRV_HYSTCTR_LEVEL_0;
    userConfig->normalCfg.hystOffsetState    = CMPDRV_OFFSET_LEVEL_0;
    userConfig->normalCfg.lpfsel             = CMPDRV_LPFSEL_10MHz;

    /* Configuration of DAC */
    userConfig->dacCfg.dacVoltInSel = CMPDRV_VRSEL_VIN1;
    userConfig->dacCfg.dacVoltScale = 127U;
    userConfig->dacCfg.state        = true;

    /* Configuration of analog mux */
    userConfig->muxCfg.posPortMux = CMPDRV_MUX;
    userConfig->muxCfg.negPortMux = CMPDRV_DAC;

    /*! \note Advise to make posInputMux = negInputMux when using DAC */
    userConfig->muxCfg.posInputMux = CMPDRV_CHANNEL_IN1;
    userConfig->muxCfg.negInputMux = CMPDRV_CHANNEL_IN1;
}

CmpDrv_TriggerType CmpDrv_GetTriggerMode(const CmpDrvType *obj)
{
    uint8_t IER = CmpReg_GetIerReg(obj->reg);
    uint8_t IEF = CmpReg_GetIefReg(obj->reg);
    return ((CmpDrv_TriggerType)((IER << CMP_TRIGGER_RISING_SHIFT) | (IEF << CMP_TRIGGER_FALLING_SHIFT)));
}

void CmpDrv_SetTriggerMode(CmpDrvType *obj, const CmpDrv_TriggerType mode)
{
    uint8_t IER = (mode >> CMP_TRIGGER_RISING_SHIFT) & CMP_TRIGGER_MASK;
    uint8_t IEF = (mode >> CMP_TRIGGER_FALLING_SHIFT) & CMP_TRIGGER_MASK;
    CmpReg_SetIerReg(obj->reg, IER);
    CmpReg_SetIefReg(obj->reg, IEF);
}

CmpDrv_ModeType CmpDrv_GetMode(const CmpDrvType *obj)
{
    uint8_t         state;
    CmpDrv_ModeType mode = CMP_DISABLED;
    state                = CmpReg_GetEnReg(obj->reg) << CMP_STATE_EN_SHIFT;
    state |= CmpReg_GetWeReg(obj->reg) << CMP_STATE_WE_SHIFT;
    state |= CmpReg_GetSeReg(obj->reg) << CMP_STATE_SE_SHIFT;
    uint8_t filter_sample_period = CmpReg_GetFprReg(obj->reg);
    uint8_t filter_sample_count  = CmpReg_GetFilterCntReg(obj->reg);

    switch(state)
    {
    case CMPDRV_STATE_NOSAMPLE:
        if((filter_sample_period == 0U) || (filter_sample_count == 0U))
        {
            mode = CMP_CONTINUOUS;
        }
        else if(filter_sample_count == 1U)
        {
            mode = CMP_SAMPLED_NONFILTRED_INT_CLK;
        }
        else
        {
            mode = CMP_SAMPLED_FILTRED_INT_CLK;
        }
        break;
    case CMPDRV_STATE_SE:
        if(filter_sample_count == 1U)
        {
            mode = CMP_SAMPLED_NONFILTRED_EXT_CLK;
        }
        else
        {
            mode = CMP_SAMPLED_FILTRED_EXT_CLK;
        }
        break;
    case CMPDRV_STATE_WE:
        if((filter_sample_period == 0U) || (filter_sample_count == 0U))
        {
            mode = CMP_WINDOWED;
        }
        else if(filter_sample_count == 1U)
        {
            mode = CMP_WINDOWED_RESAMPLED;
        }
        else
        {
            mode = CMP_WINDOWED_FILTRED;
        }
        break;
    case CMPDRV_STATE_WE_SE:
        /*! \note If a write to this register sets both bits to 1, then ONLY SE will be treated as valid and WE is ignored*/
        if(filter_sample_count == 1U)
        {
            mode = CMP_SAMPLED_NONFILTRED_EXT_CLK;
        }
        else
        {
            mode = CMP_SAMPLED_FILTRED_EXT_CLK;
        }
        break;
    default:
        /* Disable case */
        break;
    }

    return (mode);
}

void CmpDrv_SetMode(CmpDrvType *obj, const CmpDrv_ModeType mode, const uint8_t filter_sample_count, const uint8_t filter_sample_period)
{
    switch(mode)
    {
    case CMP_DISABLED:
        break;
    case CMP_CONTINUOUS:
        CmpReg_SetWeReg(obj->reg, false);
        CmpReg_SetSeReg(obj->reg, false);
        /*! \note: filter_sample_count or filter_sample_period should equal to 0*/
        CmpReg_SetFprReg(obj->reg, 0U);
        CmpReg_SetFilterCntReg(obj->reg, 0U);
        break;
    case CMP_SAMPLED_NONFILTRED_INT_CLK:
        CmpReg_SetWeReg(obj->reg, false);
        CmpReg_SetSeReg(obj->reg, false);
        CmpReg_SetFilterCntReg(obj->reg, 1U);
        CmpReg_SetFprReg(obj->reg, filter_sample_period);
        break;
    case CMP_SAMPLED_NONFILTRED_EXT_CLK:
        CmpReg_SetWeReg(obj->reg, false);
        CmpReg_SetSeReg(obj->reg, true);
        CmpReg_SetFilterCntReg(obj->reg, 1U);
        CmpReg_SetFprReg(obj->reg, filter_sample_period);
        break;
    case CMP_SAMPLED_FILTRED_INT_CLK:
        CmpReg_SetWeReg(obj->reg, false);
        CmpReg_SetSeReg(obj->reg, false);
        CmpReg_SetFilterCntReg(obj->reg, filter_sample_count);
        CmpReg_SetFprReg(obj->reg, filter_sample_period);
        break;
    case CMP_SAMPLED_FILTRED_EXT_CLK:
        CmpReg_SetWeReg(obj->reg, false);
        CmpReg_SetSeReg(obj->reg, true);
        CmpReg_SetFilterCntReg(obj->reg, filter_sample_count);
        CmpReg_SetFprReg(obj->reg, filter_sample_period);
        break;
    case CMP_WINDOWED:
        CmpReg_SetWeReg(obj->reg, true);
        CmpReg_SetSeReg(obj->reg, false);
        /*! \note: filter_sample_count or filter_sample_period should equal to 0*/
        CmpReg_SetFprReg(obj->reg, 0U);
        CmpReg_SetFilterCntReg(obj->reg, 0U);
        break;
    case CMP_WINDOWED_RESAMPLED:
        CmpReg_SetWeReg(obj->reg, true);
        CmpReg_SetSeReg(obj->reg, false);
        CmpReg_SetFilterCntReg(obj->reg, 1U);
        CmpReg_SetFprReg(obj->reg, filter_sample_period);
        break;
    case CMP_WINDOWED_FILTRED:
        CmpReg_SetWeReg(obj->reg, true);
        CmpReg_SetSeReg(obj->reg, false);
        CmpReg_SetFilterCntReg(obj->reg, filter_sample_count);
        CmpReg_SetFprReg(obj->reg, filter_sample_period);
        break;
    default:
        /* Impossible case*/
        break;
    }
}

uint8_t CmpDrv_GetChannelState(const CmpDrvType *obj)
{
    uint8_t tmp;
    tmp = ((CmpReg_GetChn0Reg(obj->reg) & CMP_CHANNELSTATE_MASK) << CMPDRV_CHANNEL_IN0)
          | ((CmpReg_GetChn1Reg(obj->reg) & CMP_CHANNELSTATE_MASK) << CMPDRV_CHANNEL_IN1)
          | ((CmpReg_GetChn2Reg(obj->reg) & CMP_CHANNELSTATE_MASK) << CMPDRV_CHANNEL_IN2)
          | ((CmpReg_GetChn3Reg(obj->reg) & CMP_CHANNELSTATE_MASK) << CMPDRV_CHANNEL_IN3)
          | ((CmpReg_GetChn4Reg(obj->reg) & CMP_CHANNELSTATE_MASK) << CMPDRV_CHANNEL_IN4)
          | ((CmpReg_GetChn5Reg(obj->reg) & CMP_CHANNELSTATE_MASK) << CMPDRV_CHANNEL_IN5)
          | ((CmpReg_GetChn6Reg(obj->reg) & CMP_CHANNELSTATE_MASK) << CMPDRV_CHANNEL_IN6)
          | ((CmpReg_GetChn7Reg(obj->reg) & CMP_CHANNELSTATE_MASK) << CMPDRV_CHANNEL_IN7);
    return (tmp);
}

void CmpDrv_SetChannelState(CmpDrvType *obj, const uint8_t channelState)
{
    CmpReg_SetChn0Reg(obj->reg, (channelState >> CMPDRV_CHANNEL_IN0) & CMP_CHANNELSTATE_MASK);
    CmpReg_SetChn1Reg(obj->reg, (channelState >> CMPDRV_CHANNEL_IN1) & CMP_CHANNELSTATE_MASK);
    CmpReg_SetChn2Reg(obj->reg, (channelState >> CMPDRV_CHANNEL_IN2) & CMP_CHANNELSTATE_MASK);
    CmpReg_SetChn3Reg(obj->reg, (channelState >> CMPDRV_CHANNEL_IN3) & CMP_CHANNELSTATE_MASK);
    CmpReg_SetChn4Reg(obj->reg, (channelState >> CMPDRV_CHANNEL_IN4) & CMP_CHANNELSTATE_MASK);
    CmpReg_SetChn5Reg(obj->reg, (channelState >> CMPDRV_CHANNEL_IN5) & CMP_CHANNELSTATE_MASK);
    CmpReg_SetChn6Reg(obj->reg, (channelState >> CMPDRV_CHANNEL_IN6) & CMP_CHANNELSTATE_MASK);
    CmpReg_SetChn7Reg(obj->reg, (channelState >> CMPDRV_CHANNEL_IN7) & CMP_CHANNELSTATE_MASK);
}

uint8_t CmpDrv_GetChannelPreState(const CmpDrvType *obj)
{
    uint8_t tmp;
    tmp = ((CmpReg_GetAco0Reg(obj->reg) & CMP_CHANNEL_PRESTATE_MASK) << CMPDRV_CHANNEL_IN0)
          | ((CmpReg_GetAco1Reg(obj->reg) & CMP_CHANNEL_PRESTATE_MASK) << CMPDRV_CHANNEL_IN1)
          | ((CmpReg_GetAco2Reg(obj->reg) & CMP_CHANNEL_PRESTATE_MASK) << CMPDRV_CHANNEL_IN2)
          | ((CmpReg_GetAco3Reg(obj->reg) & CMP_CHANNEL_PRESTATE_MASK) << CMPDRV_CHANNEL_IN3)
          | ((CmpReg_GetAco4Reg(obj->reg) & CMP_CHANNEL_PRESTATE_MASK) << CMPDRV_CHANNEL_IN4)
          | ((CmpReg_GetAco5Reg(obj->reg) & CMP_CHANNEL_PRESTATE_MASK) << CMPDRV_CHANNEL_IN5)
          | ((CmpReg_GetAco6Reg(obj->reg) & CMP_CHANNEL_PRESTATE_MASK) << CMPDRV_CHANNEL_IN6)
          | ((CmpReg_GetAco7Reg(obj->reg) & CMP_CHANNEL_PRESTATE_MASK) << CMPDRV_CHANNEL_IN7);
    return (tmp);
}

void CmpDrv_SetChannelPreState(CmpDrvType *obj, const uint8_t channelPreState)
{
    CmpReg_SetAco0Reg(obj->reg, (channelPreState >> CMPDRV_CHANNEL_IN0) & CMP_CHANNEL_PRESTATE_MASK);
    CmpReg_SetAco1Reg(obj->reg, (channelPreState >> CMPDRV_CHANNEL_IN1) & CMP_CHANNEL_PRESTATE_MASK);
    CmpReg_SetAco2Reg(obj->reg, (channelPreState >> CMPDRV_CHANNEL_IN2) & CMP_CHANNEL_PRESTATE_MASK);
    CmpReg_SetAco3Reg(obj->reg, (channelPreState >> CMPDRV_CHANNEL_IN3) & CMP_CHANNEL_PRESTATE_MASK);
    CmpReg_SetAco4Reg(obj->reg, (channelPreState >> CMPDRV_CHANNEL_IN4) & CMP_CHANNEL_PRESTATE_MASK);
    CmpReg_SetAco5Reg(obj->reg, (channelPreState >> CMPDRV_CHANNEL_IN5) & CMP_CHANNEL_PRESTATE_MASK);
    CmpReg_SetAco6Reg(obj->reg, (channelPreState >> CMPDRV_CHANNEL_IN6) & CMP_CHANNEL_PRESTATE_MASK);
    CmpReg_SetAco7Reg(obj->reg, (channelPreState >> CMPDRV_CHANNEL_IN7) & CMP_CHANNEL_PRESTATE_MASK);
}

void CmpDrv_SetCmpState(CmpDrvType *obj, const bool state)
{
    /* Unclock CMP */
    CmpReg_UnlockReg(obj->reg);

    /* Set CMP state */
    CmpReg_SetEnReg(obj->reg, state);

    /* lock CMP */
    CmpReg_LockReg(obj->reg);
}

CmpDrv_TriggerType CmpDrv_GetOutputFlags(const CmpDrvType *obj)
{
    uint8_t CFF;
    uint8_t CFR;
    CFF = CmpReg_GetCffReg(obj->reg) & CMP_TRIGGER_MASK;
    CFR = CmpReg_GetCfrReg(obj->reg) & CMP_TRIGGER_MASK;
    return ((CmpDrv_TriggerType)((CFF << CMP_TRIGGER_FALLING_SHIFT) | (CFR << CMP_TRIGGER_RISING_SHIFT)));
}

void CmpDrv_ClearOutputFlags(CmpDrvType *obj)
{
    CmpReg_ClearCffReg(obj->reg);
    CmpReg_ClearCfrReg(obj->reg);
}

uint8_t CmpDrv_GetInputFlags(const CmpDrvType *obj)
{
    uint8_t tmp;
    tmp = ((CmpReg_GetCh0fReg(obj->reg) & CMP_CHNF_MASK) << CMPDRV_CHANNEL_IN0)
          | ((CmpReg_GetCh1fReg(obj->reg) & CMP_CHNF_MASK) << CMPDRV_CHANNEL_IN1)
          | ((CmpReg_GetCh2fReg(obj->reg) & CMP_CHNF_MASK) << CMPDRV_CHANNEL_IN2)
          | ((CmpReg_GetCh3fReg(obj->reg) & CMP_CHNF_MASK) << CMPDRV_CHANNEL_IN3)
          | ((CmpReg_GetCh4fReg(obj->reg) & CMP_CHNF_MASK) << CMPDRV_CHANNEL_IN4)
          | ((CmpReg_GetCh5fReg(obj->reg) & CMP_CHNF_MASK) << CMPDRV_CHANNEL_IN5)
          | ((CmpReg_GetCh6fReg(obj->reg) & CMP_CHNF_MASK) << CMPDRV_CHANNEL_IN6)
          | ((CmpReg_GetCh7fReg(obj->reg) & CMP_CHNF_MASK) << CMPDRV_CHANNEL_IN7);
    return (tmp);
}

void CmpDrv_ClearInputFlags(CmpDrvType *obj)
{
    CmpReg_ClearCh0fReg(obj->reg);
    CmpReg_ClearCh1fReg(obj->reg);
    CmpReg_ClearCh2fReg(obj->reg);
    CmpReg_ClearCh3fReg(obj->reg);
    CmpReg_ClearCh4fReg(obj->reg);
    CmpReg_ClearCh5fReg(obj->reg);
    CmpReg_ClearCh6fReg(obj->reg);
    CmpReg_ClearCh7fReg(obj->reg);
}

void CmpDrv_ConfigureDac(CmpDrvType *obj, const CmpDrv_DacCfgType *userConfig)
{
    /* Unclock CMP */
    CmpReg_UnlockReg(obj->reg);

    /* Disable CMP first */
    CmpReg_SetEnReg(obj->reg, false);

    /* Configuration of DAC */
    CmpReg_SetVrselReg(obj->reg, userConfig->dacVoltInSel);
    CmpReg_SetVoselReg(obj->reg, userConfig->dacVoltScale);
    CmpReg_SetDacenReg(obj->reg, userConfig->state);

    /* lock CMP */
    CmpReg_LockReg(obj->reg);

    /*! \note When enable CMP depend on user(use CmpDrv_SetCmpState for enable CMP)*/
}

void CmpDrv_GetDacConfig(const CmpDrvType *obj, CmpDrv_DacCfgType *userConfig)
{
    userConfig->dacVoltInSel = (CmpDrv_VrselType)(CmpReg_GetVrselReg(obj->reg));
    userConfig->dacVoltScale = CmpReg_GetVoselReg(obj->reg);
    userConfig->state        = CmpReg_GetDacenReg(obj->reg);
}

void CmpDrv_ConfigureMux(CmpDrvType *obj, const CmpDrv_MuxCfgType *userConfig)
{
    /* Unclock CMP */
    CmpReg_UnlockReg(obj->reg);

    /* Disable CMP */
    CmpReg_SetEnReg(obj->reg, false);

    /* Configuration of analog mux */
    CmpReg_SetInpselReg(obj->reg, userConfig->posPortMux);
    CmpReg_SetInnselReg(obj->reg, userConfig->negPortMux);
    CmpReg_SetPselReg(obj->reg, userConfig->posInputMux);
    CmpReg_SetMselReg(obj->reg, userConfig->negInputMux);

    /* lock CMP*/
    CmpReg_LockReg(obj->reg);

    /*! \note When enable CMP depend on user(use CmpDrv_SetCmpState for enable CMP)*/
}

void CmpDrv_GetMuxConfig(const CmpDrvType *obj, CmpDrv_MuxCfgType *userConfig)
{
    userConfig->posPortMux  = (CmpDrv_InPortType)(CmpReg_GetInpselReg(obj->reg));
    userConfig->negPortMux  = (CmpDrv_InPortType)(CmpReg_GetInnselReg(obj->reg));
    userConfig->posInputMux = (CmpDrv_ChSelType)(CmpReg_GetPselReg(obj->reg));
    userConfig->negInputMux = (CmpDrv_ChSelType)(CmpReg_GetMselReg(obj->reg));
}
