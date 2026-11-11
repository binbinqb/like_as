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

#include "reset_drv.h"
#include "rcm_reg.h"
#include "apc_reg.h"
#include "pcc_reg.h"
#include "../cpu/cpu_drv.h"

/*******************************************************************************
 * the defines
 ******************************************************************************/

#define RESET_RCM_UNLOCK (0x43524155u)
#define RESET_APC_UNLOCK (0xC1C51F9Cu)
#define RESET_PCC_UNLOCK (0x70637577u)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the functions
 ******************************************************************************/

void ResetDrv_Init(ResetDrvType *obj, struct _RcmRegType_ *rcmReg, struct _PccRegType_ *pccReg, struct _ApcRegType_ *apcReg)
{
    obj->rcmReg = rcmReg;
    obj->pccReg = pccReg;
    obj->apcReg = apcReg;
}

void ResetDrv_GetDefaultConfig(ResetDrv_ConfigType *userConfig)
{
    userConfig->enableExtFlt         = false;
    userConfig->extFltLen            = 16;
    userConfig->enableResetInterrupt = false;
    userConfig->delay                = RESETDRV_RESETDELAY_514LPOCYCLES;
}

void ResetDrv_Configure(ResetDrvType *obj, const ResetDrv_ConfigType *userConfig)
{
    if((userConfig->extFltLen > 32) || (userConfig->extFltLen < 1))
    {
        return;
    }
    if(userConfig->delay > RESETDRV_RESETDELAY_514LPOCYCLES)
    {
        return;
    }

    RcmReg_SetLockKey(obj->rcmReg, RESET_RCM_UNLOCK); /* Unlock RCM */

    RcmReg_SetExtRstFltEn(obj->rcmReg, userConfig->enableExtFlt);
    RcmReg_SetExtRstFltLen(obj->rcmReg, (uint8_t)(userConfig->extFltLen - 1));
    RcmReg_SetRstCtrlGlobalIE(obj->rcmReg, userConfig->enableResetInterrupt);
    RcmReg_SetRstCtrlRstDelay(obj->rcmReg, userConfig->delay);

    RcmReg_SetLockKey(obj->rcmReg, 0); /* Lock RCM again */
}

bool ResetDrv_IsResetCaused(const ResetDrvType *obj, ResetDrv_SourceType source)
{
    bool retval = false;
    if(source >= RESETDRV_SOURCE_NUM)
    {
        return retval;
    }
    /* polyspace-begin DEFECT:DEAD_CODE [No action planned:low] "still keep default though it's not reachable" */
    switch(source)
    {
    case RESETDRV_SOURCE_WDG:
        retval = RcmReg_GetRstFlagWdgRst(obj->rcmReg) == 1;
        break;
    case RESETDRV_SOURCE_SYS:
        retval = RcmReg_GetRstFlagSysRst(obj->rcmReg) == 1;
        break;
    case RESETDRV_SOURCE_LOCKUP:
        retval = RcmReg_GetRstFlagLockupRst(obj->rcmReg) == 1;
        break;
    case RESETDRV_SOURCE_PIN:
        retval = RcmReg_GetRstFlagPinRst(obj->rcmReg) == 1;
        break;
    case RESETDRV_SOURCE_MDMAP:
        retval = RcmReg_GetRstFlagMdmApRst(obj->rcmReg) == 1;
        break;
    case RESETDRV_SOURCE_PLL_LOSS:
        retval = RcmReg_GetRstFlagPllLoss(obj->rcmReg) == 1;
        break;
    case RESETDRV_SOURCE_CMUF:
        retval = RcmReg_GetRstFlagCmuFirc(obj->rcmReg) == 1;
        break;
    case RESETDRV_SOURCE_CMUP:
        retval = RcmReg_GetRstFlagCmuPll(obj->rcmReg) == 1;
        break;
    case RESETDRV_SOURCE_CMUS:
        retval = RcmReg_GetRstFlagCmuSosc(obj->rcmReg) == 1;
        break;
    case RESETDRV_SOURCE_FCCU:
        retval = RcmReg_GetRstFlagFccuReset(obj->rcmReg) == 1;
        break;
    case RESETDRV_SOURCE_STDBY_EXIT:
        retval = RcmReg_GetRstFlagStdbyExit(obj->rcmReg) == 1;
        break;
    case RESETDRV_SOURCE_FLS_INITIAL:
        retval = RcmReg_GetRstFlagFlsInitial(obj->rcmReg) == 1;
        break;
    case RESETDRV_SOURCE_LVR:
        retval = RcmReg_GetRstFlagLvrRst(obj->rcmReg) == 1;
        break;
    case RESETDRV_SOURCE_POR:
        retval = RcmReg_GetRstFlagPorRst(obj->rcmReg) == 1;
        break;
    default:
        /* Should not get here */
        break;
    }
    /* polyspace-end DEFECT:DEAD_CODE [No action planned:low] "still keep default though it's not reachable" */
    return retval;
}

bool ResetDrv_IsResetSticky(const ResetDrvType *obj, ResetDrv_SourceType source)
{
    bool retval = false;
    if(source >= RESETDRV_SOURCE_NUM)
    {
        return retval;
    }
    /* polyspace-begin DEFECT:DEAD_CODE [No action planned:low] "still keep default though it's not reachable" */
    switch(source)
    {
    case RESETDRV_SOURCE_WDG:
        retval = RcmReg_GetRstSFlagWdgRst(obj->rcmReg) == 1;
        break;
    case RESETDRV_SOURCE_SYS:
        retval = RcmReg_GetRstSFlagSysRst(obj->rcmReg) == 1;
        break;
    case RESETDRV_SOURCE_LOCKUP:
        retval = RcmReg_GetRstSFlagLockupRst(obj->rcmReg) == 1;
        break;
    case RESETDRV_SOURCE_PIN:
        retval = RcmReg_GetRstSFlagPinRst(obj->rcmReg) == 1;
        break;
    case RESETDRV_SOURCE_MDMAP:
        retval = RcmReg_GetRstSFlagMdmApRst(obj->rcmReg) == 1;
        break;
    case RESETDRV_SOURCE_PLL_LOSS:
        retval = RcmReg_GetRstSFlagPllLoss(obj->rcmReg) == 1;
        break;
    case RESETDRV_SOURCE_CMUF:
        retval = RcmReg_GetRstSFlagCmuFirc(obj->rcmReg) == 1;
        break;
    case RESETDRV_SOURCE_CMUP:
        retval = RcmReg_GetRstSFlagCmuPll(obj->rcmReg) == 1;
        break;
    case RESETDRV_SOURCE_CMUS:
        retval = RcmReg_GetRstSFlagCmuSosc(obj->rcmReg) == 1;
        break;
    case RESETDRV_SOURCE_FCCU:
        retval = RcmReg_GetRstSFlagFccuReset(obj->rcmReg) == 1;
        break;
    case RESETDRV_SOURCE_STDBY_EXIT:
        retval = RcmReg_GetRstSFlagStdbyExit(obj->rcmReg) == 1;
        break;
    case RESETDRV_SOURCE_FLS_INITIAL:
        retval = RcmReg_GetRstSFlagFlsInitial(obj->rcmReg) == 1;
        break;
    case RESETDRV_SOURCE_LVR:
        retval = RcmReg_GetRstSFlagLvrRst(obj->rcmReg) == 1;
        break;
    case RESETDRV_SOURCE_POR:
        retval = RcmReg_GetRstSFlagPorRst(obj->rcmReg) == 1;
        break;
    default:
        /* Should not get here */
        break;
    }
    /* polyspace-end DEFECT:DEAD_CODE [No action planned:low] "still keep default though it's not reachable" */
    return retval;
}

void ResetDrv_ClrResetStickyFlag(ResetDrvType *obj, ResetDrv_SourceType source)
{
    if(source >= RESETDRV_SOURCE_NUM)
    {
        return;
    }
    RcmReg_SetLockKey(obj->rcmReg, RESET_RCM_UNLOCK); /* Unlock RCM */
    /* polyspace-begin DEFECT:DEAD_CODE [No action planned:low] "still keep default though it's not reachable" */
    switch(source)
    {
    case RESETDRV_SOURCE_WDG:
        RcmReg_SetRstSFlagWdgRst(obj->rcmReg, 1);
        break;
    case RESETDRV_SOURCE_SYS:
        RcmReg_SetRstSFlagSysRst(obj->rcmReg, 1);
        break;
    case RESETDRV_SOURCE_LOCKUP:
        RcmReg_SetRstSFlagLockupRst(obj->rcmReg, 1);
        break;
    case RESETDRV_SOURCE_PIN:
        RcmReg_SetRstSFlagPinRst(obj->rcmReg, 1);
        break;
    case RESETDRV_SOURCE_MDMAP:
        RcmReg_SetRstSFlagMdmApRst(obj->rcmReg, 1);
        break;
    case RESETDRV_SOURCE_PLL_LOSS:
        RcmReg_SetRstSFlagPllLoss(obj->rcmReg, 1);
        break;
    case RESETDRV_SOURCE_CMUF:
        RcmReg_SetRstSFlagCmuFirc(obj->rcmReg, 1);
        break;
    case RESETDRV_SOURCE_CMUP:
        RcmReg_SetRstSFlagCmuPll(obj->rcmReg, 1);
        break;
    case RESETDRV_SOURCE_CMUS:
        RcmReg_SetRstSFlagCmuSosc(obj->rcmReg, 1);
        break;
    case RESETDRV_SOURCE_FCCU:
        RcmReg_SetRstSFlagFccuReset(obj->rcmReg, 1);
        break;
    case RESETDRV_SOURCE_STDBY_EXIT:
        RcmReg_SetRstSFlagStdbyExit(obj->rcmReg, 1);
        break;
    case RESETDRV_SOURCE_FLS_INITIAL:
        RcmReg_SetRstSFlagFlsInitial(obj->rcmReg, 1);
        break;
    case RESETDRV_SOURCE_LVR:
        RcmReg_SetRstSFlagLvrRst(obj->rcmReg, 1);
        break;
    case RESETDRV_SOURCE_POR:
        RcmReg_SetRstSFlagPorRst(obj->rcmReg, 1);
        break;
    default:
        /* Should not get here */
        break;
    }
    /* polyspace-end DEFECT:DEAD_CODE [No action planned:low] "still keep default though it's not reachable" */
    RcmReg_SetLockKey(obj->rcmReg, 0); /* Lock RCM again */
}

void ResetDrv_EnableResetInterrupt(ResetDrvType *obj, ResetDrv_ResetIntModuleType module, bool enable)
{
    RcmReg_SetLockKey(obj->rcmReg, RESET_RCM_UNLOCK); /* Unlock RCM */
    switch(module)
    {
    case RESETDRV_RESETINT_WDG:
        RcmReg_SetRstCtrlWdgRstIE(obj->rcmReg, enable ? 1 : 0);
        break;
    case RESETDRV_RESETINT_SYS:
        RcmReg_SetRstCtrlSysRstIE(obj->rcmReg, enable ? 1 : 0);
        break;
    case RESETDRV_RESETINT_PIN:
        RcmReg_SetRstCtrlPinRstIE(obj->rcmReg, enable ? 1 : 0);
        break;
    case RESETDRV_RESETINT_MDMAP:
        RcmReg_SetRstCtrlMdmApRstIE(obj->rcmReg, enable ? 1 : 0);
        break;
    case RESETDRV_RESETINT_PLL_LOSS:
        RcmReg_SetRstCtrlPllLossIE(obj->rcmReg, enable ? 1 : 0);
        break;
    case RESETDRV_RESETINT_CMUF:
        RcmReg_SetRstCtrlCmuFircIE(obj->rcmReg, enable ? 1 : 0);
        break;
    case RESETDRV_RESETINT_CMUP:
        RcmReg_SetRstCtrlCmuPllIE(obj->rcmReg, enable ? 1 : 0);
        break;
    case RESETDRV_RESETINT_CMUS:
        RcmReg_SetRstCtrlCmuSoscIE(obj->rcmReg, enable ? 1 : 0);
        break;
    default:
        /* Should not get here */
        break;
    }
    RcmReg_SetLockKey(obj->rcmReg, 0); /* Lock RCM again */
}

bool ResetDrv_IsResetInterrupt(const ResetDrvType *obj, ResetDrv_ResetIntModuleType module)
{
    uint8_t retval = 0x0u;
    switch(module)
    {
    case RESETDRV_RESETINT_WDG:
        retval = RcmReg_GetRstIrqWdg(obj->rcmReg);
        break;
    case RESETDRV_RESETINT_SYS:
        retval = RcmReg_GetRstIrqSys(obj->rcmReg);
        break;
    case RESETDRV_RESETINT_PIN:
        retval = RcmReg_GetRstIrqPin(obj->rcmReg);
        break;
    case RESETDRV_RESETINT_MDMAP:
        retval = RcmReg_GetRstIrqMdmap(obj->rcmReg);
        break;
    case RESETDRV_RESETINT_PLL_LOSS:
        retval = RcmReg_GetRstIrqPllLoss(obj->rcmReg);
        break;
    case RESETDRV_RESETINT_CMUF:
        retval = RcmReg_GetRstIrqCmuFirc(obj->rcmReg);
        break;
    case RESETDRV_RESETINT_CMUP:
        retval = RcmReg_GetRstIrqCmuPll(obj->rcmReg);
        break;
    case RESETDRV_RESETINT_CMUS:
        retval = RcmReg_GetRstIrqCmuSosc(obj->rcmReg);
        break;
    default:
        /* Should not get here */
        break;
    }
    return (retval == 0x1u);
}

void ResetDrv_EnableReset(ResetDrvType *obj, ResetDrv_ResetEnModuleType module, bool enable)
{
    RcmReg_SetLockKey(obj->rcmReg, RESET_RCM_UNLOCK); /* Unlock RCM */
    switch(module)
    {
    case RESETDRV_RESETEN_PLL_LOSS:
        RcmReg_SetRstCtrlPllLossEn(obj->rcmReg, enable ? 1 : 0);
        break;
    case RESETDRV_RESETEN_LOCKUP:
        RcmReg_SetRstCtrlLockupEn(obj->rcmReg, enable ? 1 : 0);
        break;
    default:
        /* Should not get here */
        break;
    }
    RcmReg_SetLockKey(obj->rcmReg, 0); /* Lock RCM again */
}

void ResetDrv_SoftwareResetModule(ResetDrvType *obj, ResetDrv_SwResetModuleType module)
{
    ApcReg_SetLockKey(obj->apcReg, RESET_APC_UNLOCK); /* Unlock APC */
    PccReg_SetLockKey(obj->pccReg, RESET_PCC_UNLOCK); /* Unlock PCC */
    switch(module)
    {
    case RESETDRV_SWRESET_WDG:
        ApcReg_SetSwRstWdg(obj->apcReg, 1);
        ApcReg_SetSwRstWdg(obj->apcReg, 0);
        break;
    case RESETDRV_SWRESET_LPTMR:
        ApcReg_SetSwRstLptmr(obj->apcReg, 1);
        ApcReg_SetSwRstLptmr(obj->apcReg, 0);
        break;
    case RESETDRV_SWRESET_CMP:
        ApcReg_SetSwRstCmp0(obj->apcReg, 1);
        ApcReg_SetSwRstCmp0(obj->apcReg, 0);
        break;
    case RESETDRV_SWRESET_LPIT:
        ApcReg_SetSwRstLpit(obj->apcReg, 1);
        ApcReg_SetSwRstLpit(obj->apcReg, 0);
        break;
    case RESETDRV_SWRESET_PORTA:
        ApcReg_SetSwRstPortA(obj->apcReg, 1);
        ApcReg_SetSwRstPortA(obj->apcReg, 0);
        break;
    case RESETDRV_SWRESET_PORTB:
        ApcReg_SetSwRstPortB(obj->apcReg, 1);
        ApcReg_SetSwRstPortB(obj->apcReg, 0);
        break;
    case RESETDRV_SWRESET_PORTC:
        ApcReg_SetSwRstPortC(obj->apcReg, 1);
        ApcReg_SetSwRstPortC(obj->apcReg, 0);
        break;
    case RESETDRV_SWRESET_PORTD:
        ApcReg_SetSwRstPortD(obj->apcReg, 1);
        ApcReg_SetSwRstPortD(obj->apcReg, 0);
        break;
    case RESETDRV_SWRESET_PORTE:
        ApcReg_SetSwRstPortE(obj->apcReg, 1);
        ApcReg_SetSwRstPortE(obj->apcReg, 0);
        break;
    case RESETDRV_SWRESET_FLS:
        PccReg_SetSwRst0Fls(obj->pccReg, 1);
        PccReg_SetSwRst0Fls(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_DMA:
        PccReg_SetSwRst0Dma(obj->pccReg, 1);
        PccReg_SetSwRst0Dma(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_EIM:
        PccReg_SetSwRst0Eim(obj->pccReg, 1);
        PccReg_SetSwRst0Eim(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_ERM:
        PccReg_SetSwRst0Erm(obj->pccReg, 1);
        PccReg_SetSwRst0Erm(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_MSCM:
        PccReg_SetSwRst0Mscm(obj->pccReg, 1);
        PccReg_SetSwRst0Mscm(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_MPU:
        PccReg_SetSwRst0Mpu(obj->pccReg, 1);
        PccReg_SetSwRst0Mpu(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_EWM:
        PccReg_SetSwRst0Ewm(obj->pccReg, 1);
        PccReg_SetSwRst0Ewm(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_DMAMUX:
        PccReg_SetSwRst0DmaMux(obj->pccReg, 1);
        PccReg_SetSwRst0DmaMux(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_CAN0:
        PccReg_SetSwRst0Can0(obj->pccReg, 1);
        PccReg_SetSwRst0Can0(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_CAN1:
        PccReg_SetSwRst0Can1(obj->pccReg, 1);
        PccReg_SetSwRst0Can1(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_CAN2:
        PccReg_SetSwRst0Can2(obj->pccReg, 1);
        PccReg_SetSwRst0Can2(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_CAN3:
        PccReg_SetSwRst0Can3(obj->pccReg, 1);
        PccReg_SetSwRst0Can3(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_ADC0:
        PccReg_SetSwRst0Adc0(obj->pccReg, 1);
        PccReg_SetSwRst0Adc0(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_ADC1:
        PccReg_SetSwRst0Adc1(obj->pccReg, 1);
        PccReg_SetSwRst0Adc1(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_PDB0:
        PccReg_SetSwRst0Pdb0(obj->pccReg, 1);
        PccReg_SetSwRst0Pdb0(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_PDB1:
        PccReg_SetSwRst0Pdb1(obj->pccReg, 1);
        PccReg_SetSwRst0Pdb1(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_SPI0:
        PccReg_SetSwRst0Spi0(obj->pccReg, 1);
        PccReg_SetSwRst0Spi0(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_SPI1:
        PccReg_SetSwRst0Spi1(obj->pccReg, 1);
        PccReg_SetSwRst0Spi1(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_SPI2:
        PccReg_SetSwRst0Spi2(obj->pccReg, 1);
        PccReg_SetSwRst0Spi2(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_SPI3:
        PccReg_SetSwRst0Spi3(obj->pccReg, 1);
        PccReg_SetSwRst0Spi3(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_UART0:
        PccReg_SetSwRst0Uart0(obj->pccReg, 1);
        PccReg_SetSwRst0Uart0(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_UART1:
        PccReg_SetSwRst0Uart1(obj->pccReg, 1);
        PccReg_SetSwRst0Uart1(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_UART2:
        PccReg_SetSwRst0Uart2(obj->pccReg, 1);
        PccReg_SetSwRst0Uart2(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_UART3:
        PccReg_SetSwRst0Uart3(obj->pccReg, 1);
        PccReg_SetSwRst0Uart3(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_I2C:
        PccReg_SetSwRst0I2C(obj->pccReg, 1);
        PccReg_SetSwRst0I2C(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_I2SM:
        PccReg_SetSwRst0I2SM(obj->pccReg, 1);
        PccReg_SetSwRst0I2SM(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_I2SS:
        PccReg_SetSwRst0I2SS(obj->pccReg, 1);
        PccReg_SetSwRst0I2SS(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_CRC:
        PccReg_SetSwRst0Crc(obj->pccReg, 1);
        PccReg_SetSwRst0Crc(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_CSE:
        PccReg_SetSwRst0Cse(obj->pccReg, 1);
        PccReg_SetSwRst0Cse(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_PRNG:
        PccReg_SetSwRst0Prng(obj->pccReg, 1);
        PccReg_SetSwRst0Prng(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_MFT0:
        PccReg_SetSwRst1Mft0(obj->pccReg, 1);
        PccReg_SetSwRst1Mft0(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_MFT1:
        PccReg_SetSwRst1Mft1(obj->pccReg, 1);
        PccReg_SetSwRst1Mft1(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_MFT2:
        PccReg_SetSwRst1Mft2(obj->pccReg, 1);
        PccReg_SetSwRst1Mft2(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_MFT3:
        PccReg_SetSwRst1Mft3(obj->pccReg, 1);
        PccReg_SetSwRst1Mft3(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_MFT4:
        PccReg_SetSwRst1Mft4(obj->pccReg, 1);
        PccReg_SetSwRst1Mft4(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_MFT5:
        PccReg_SetSwRst1Mft5(obj->pccReg, 1);
        PccReg_SetSwRst1Mft5(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_PWMLITE0:
        PccReg_SetSwRst1Pwm0(obj->pccReg, 1);
        PccReg_SetSwRst1Pwm0(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_PWMLITE1:
        PccReg_SetSwRst1Pwm1(obj->pccReg, 1);
        PccReg_SetSwRst1Pwm1(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_PWMLITE2:
        PccReg_SetSwRst1Pwm2(obj->pccReg, 1);
        PccReg_SetSwRst1Pwm2(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_PWMLITE3:
        PccReg_SetSwRst1Pwm3(obj->pccReg, 1);
        PccReg_SetSwRst1Pwm3(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_PWMLITE4:
        PccReg_SetSwRst1Pwm4(obj->pccReg, 1);
        PccReg_SetSwRst1Pwm4(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_GPIO:
        PccReg_SetSwRst1Gpio(obj->pccReg, 1);
        PccReg_SetSwRst1Gpio(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_CMUF:
        PccReg_SetSwRst1Cmuf(obj->pccReg, 1);
        PccReg_SetSwRst1Cmuf(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_CMUP:
        PccReg_SetSwRst1Cmup(obj->pccReg, 1);
        PccReg_SetSwRst1Cmup(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_CMUS:
        PccReg_SetSwRst1Cmus(obj->pccReg, 1);
        PccReg_SetSwRst1Cmus(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_FCCU:
        PccReg_SetSwRst1Fccu(obj->pccReg, 1);
        PccReg_SetSwRst1Fccu(obj->pccReg, 0);
        break;
    case RESETDRV_SWRESET_SYS:
        NVIC_SystemReset();
        break;
    default:
        /* Should not get here */
        break;
    }
    ApcReg_SetLockKey(obj->apcReg, 0); /* Lock APC again */
    PccReg_SetLockKey(obj->pccReg, 0); /* Lock PCC again */
}
