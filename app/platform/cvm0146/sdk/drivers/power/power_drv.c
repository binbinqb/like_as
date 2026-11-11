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

#include "../cpu/cpu_drv.h"
#include "power_drv.h"
#include "pmc_reg.h"

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

void PowerDrv_Init(PowerDrvType *obj, struct _PmcRegType_ *pmcReg, struct _AcgRegType_ *acgReg)
{
    obj->pmcReg = pmcReg;
    obj->acgReg = acgReg;
}

void PowerDrv_UnlockRegWriteAccess(PowerDrvType *obj)
{
    PmcReg_SetKeyVal(obj->pmcReg, 0x1015ff11);
}

void PowerDrv_LockRegWriteAccess(PowerDrvType *obj)
{
    PmcReg_SetKeyVal(obj->pmcReg, 0);
}

void PowerDrv_EnableLvwWarning(PowerDrvType *obj)
{
    PmcReg_SetAnaCtrlDaPmcEnLvw(obj->pmcReg, true);
}

void PowerDrv_DisableLvwWarning(PowerDrvType *obj)
{
    PmcReg_SetAnaCtrlDaPmcEnLvw(obj->pmcReg, false);
}

void PowerDrv_SetLvwLevel(PowerDrvType *obj, PowerDrvLvwLevelType level)
{
    PmcReg_SetAnaCtrlDaPmcSelLvw(obj->pmcReg, level);
}

void PowerDrv_EnableLvdDetect(PowerDrvType *obj)
{
    PmcReg_SetAnaCtrlDaPmcEnLvd(obj->pmcReg, true);
}

void PowerDrv_DisableLvdDetect(PowerDrvType *obj)
{
    PmcReg_SetAnaCtrlDaPmcEnLvd(obj->pmcReg, false);
}

void PowerDrv_EnableOtpWarning(PowerDrvType *obj)
{
    PmcReg_SetAnaCtrlDaHpbgOtpEn(obj->pmcReg, true);
}

void PowerDrv_DisableOtpWarning(PowerDrvType *obj)
{
    PmcReg_SetAnaCtrlDaHpbgOtpEn(obj->pmcReg, false);
}

void PowerDrv_EnableFldoDetect(PowerDrvType *obj)
{
    PmcReg_SetAnaCtrlDaPmcEnFldoVdet(obj->pmcReg, true);
}

void PowerDrv_DisableFldoDetect(PowerDrvType *obj)
{
    PmcReg_SetAnaCtrlDaPmcEnFldoVdet(obj->pmcReg, false);
}

void PowerDrv_EnableOvdDetect(PowerDrvType *obj)
{
    PmcReg_SetAnaCtrlDaPmcEnOvd(obj->pmcReg, true);
}

void PowerDrv_DisableOvdDetect(PowerDrvType *obj)
{
    PmcReg_SetAnaCtrlDaPmcEnOvd(obj->pmcReg, false);
}

void PowerDrv_EnableLpbgOvdDetect(PowerDrvType *obj)
{
    PmcReg_SetUidetDaPmcEnLpbgOvd(obj->pmcReg, true);
}

void PowerDrv_DisableLpbgOvdDetect(PowerDrvType *obj)
{
    PmcReg_SetUidetDaPmcEnLpbgOvd(obj->pmcReg, false);
}

void PowerDrv_EnableLpbgLvdDetect(PowerDrvType *obj)
{
    PmcReg_SetUidetDaPmcEnLpbgLvd(obj->pmcReg, true);
}

void PowerDrv_DisableLpbgLvdDetect(PowerDrvType *obj)
{
    PmcReg_SetUidetDaPmcEnLpbgLvd(obj->pmcReg, false);
}

void PowerDrv_EnableOvd11Detect(PowerDrvType *obj)
{
    PmcReg_SetAnaCtrlDaPmcEnOvd11(obj->pmcReg, true);
}

void PowerDrv_DisableOvd11Detect(PowerDrvType *obj)
{
    PmcReg_SetAnaCtrlDaPmcEnOvd11(obj->pmcReg, false);
}

void PowerDrv_ReleasePadKeep(PowerDrvType *obj)
{
    /* this bit is W1C, user should release it as early as possible */
    PowerDrv_UnlockRegWriteAccess(obj);
    PmcReg_SetPkpPadKeep(obj->pmcReg, true);
    PowerDrv_LockRegWriteAccess(obj);
}

PowerDrvPowerModeType PowerDrv_GetPreviousPmcMode(PowerDrvType *obj)
{
    PowerDrvPowerModeType rtv = POWERDRV_POWER_MODE_RUN;
    PowerDrv_UnlockRegWriteAccess(obj);
    if(PmcReg_GetWkSrcStopStFlg(obj->pmcReg))
    {
        rtv = POWERDRV_POWER_MODE_STOP;
    }
    else if(PmcReg_GetWkSrcStbyStFlg(obj->pmcReg))
    {
        rtv = POWERDRV_POWER_MODE_STANDBY_WITH_CPU_RETENTION;
    }
    else
    {
    }
    PowerDrv_LockRegWriteAccess(obj);
    return rtv;
}

void PowerDrv_ClrPreviousPmcMode(PowerDrvType *obj)
{
    PowerDrv_UnlockRegWriteAccess(obj);
    PmcReg_SetWkSrcStopStFlg(obj->pmcReg, 1);
    PmcReg_SetWkSrcStbyStFlg(obj->pmcReg, 1);
    PowerDrv_LockRegWriteAccess(obj);
}

void PowerDrv_ClrAllWakupFlags(PowerDrvType *obj)
{
    /* clear all the wakeup flags */
    PowerDrv_UnlockRegWriteAccess(obj);
    PmcReg_SetWkSrcCmpWakeup(obj->pmcReg, 1);
    PmcReg_SetWkSrcLptmrWakeup(obj->pmcReg, 1);
    PmcReg_SetWkSrcLpitWakeup(obj->pmcReg, 1);
    PmcReg_SetWkSrcRtcWakeup(obj->pmcReg, 1);
    PmcReg_SetWkSrcResetWakeup(obj->pmcReg, 1);
    PmcReg_SetWkSrcPortEWakeup(obj->pmcReg, 1);
    PmcReg_SetWkSrcPortDWakeup(obj->pmcReg, 1);
    PmcReg_SetWkSrcPortCWakeup(obj->pmcReg, 1);
    PmcReg_SetWkSrcPortBWakeup(obj->pmcReg, 1);
    PmcReg_SetWkSrcPortAWakeup(obj->pmcReg, 1);
    PowerDrv_LockRegWriteAccess(obj);
}

void PowerDrv_ClrWakeupFlag(PowerDrvType *obj, PowerDrvWakeupFlagType flag)
{
    PowerDrv_UnlockRegWriteAccess(obj);
    switch(flag)
    {
    case POWERDRV_PORTA_WU:
        PmcReg_SetWkSrcPortAWakeup(obj->pmcReg, 1);
        break;
    case POWERDRV_PORTB_WU:
        PmcReg_SetWkSrcPortBWakeup(obj->pmcReg, 1);
        break;
    case POWERDRV_PORTC_WU:
        PmcReg_SetWkSrcPortCWakeup(obj->pmcReg, 1);
        break;
    case POWERDRV_PORTD_WU:
        PmcReg_SetWkSrcPortDWakeup(obj->pmcReg, 1);
        break;
    case POWERDRV_PORTE_WU:
        PmcReg_SetWkSrcPortEWakeup(obj->pmcReg, 1);
        break;
    case POWERDRV_RSTPIN_WU:
        PmcReg_SetWkSrcResetWakeup(obj->pmcReg, 1);
        break;
    case POWERDRV_RTC_WU:
        PmcReg_SetWkSrcRtcWakeup(obj->pmcReg, 1);
        break;
    case POWERDRV_LPIT_WU:
        PmcReg_SetWkSrcLpitWakeup(obj->pmcReg, 1);
        break;
    case POWERDRV_LPTMR_WU:
        PmcReg_SetWkSrcLptmrWakeup(obj->pmcReg, 1);
        break;
    case POWERDRV_CMP_WU:
        PmcReg_SetWkSrcCmpWakeup(obj->pmcReg, 1);
        break;
    default:
        break;
    }
    PowerDrv_LockRegWriteAccess(obj);
}

PowerDrvWakeupFlagType PowerDrv_GetWakeupSource(PowerDrvType *obj)
{
    PowerDrvWakeupFlagType rtv = POWERDRV_NO_WU;
    /* scan and return the wakeup flag which is set */
    for(uint8_t i = POWERDRV_PORTA_WU; i <= POWERDRV_CMP_WU; i++)
    {
        uint32_t temp = 1;
        temp <<= i;
        if(obj->pmcReg->WKSRC & temp)
        {
            rtv = (PowerDrvWakeupFlagType)i;
        }
    }
    return rtv;
}

void PowerDrv_StandbyModePreTask(PowerDrvType *obj)
{
    /* make sure these bits setting are correct before standby mode */
    PowerDrv_DisableOtpWarning(obj);
    PowerDrv_DisableLvdDetect(obj);
    PowerDrv_DisableLvwWarning(obj);
    PowerDrv_DisableOvdDetect(obj);
    PowerDrv_DisableOvd11Detect(obj);
    PowerDrv_DisableLpbgLvdDetect(obj);
    PowerDrv_DisableLpbgOvdDetect(obj);
    AcgReg_SetEnSosc(obj->acgReg, 0);
    AcgReg_SetOscExt(obj->acgReg, 0);
    AcgReg_SetEnPll(obj->acgReg, 0);
}

void PowerDrv_SetPowerMode(PowerDrvType *obj, PowerDrvPowerModeType mode)
{
    PowerDrv_UnlockRegWriteAccess(obj);
    /* target mode is stop mode */
    if(mode == POWERDRV_POWER_MODE_STOP)
    {
        PowerDrv_LockRegWriteAccess(obj);
        SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
        __WFI();
    }
    /* target mode is standby mode */
    else if(mode == POWERDRV_POWER_MODE_STANDBY_WITH_CPU_RETENTION)
    {
        AcgReg_SetLockKey(obj->acgReg, 0xFA8623E4);
        AcgReg_SetSysSrcSys(obj->acgReg, 0);
        while(AcgReg_GetStSysSt(obj->acgReg) != 0)
        {
            ;
        }
        PowerDrv_StandbyModePreTask(obj);
        AcgReg_SetLockKey(obj->acgReg, 0x00000000);
        PowerDrv_ClrAllWakupFlags(obj);
        PowerDrv_LockRegWriteAccess(obj);
        SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
        __WFI();
    }
    else
    {
    }
}
