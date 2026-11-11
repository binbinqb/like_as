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

/*! \brief This function configures sync mechanism for some MFT registers
 *
 * This function configure the synchronization for PWM register (CnV, MOD, CINT, HCR, OUTMASK).
 * If this function is used whit wrong parameters it's possible to generate wrong waveform.
 * Registers synchronization need to be configured for PWM and output compare mode.
 *
 * \param[in] obj : pointer to MFT driver instance
 * \param[in] param : pwm sync config
 * \return The result of the operation
 *         - true : success
 *         - false : failed
 */
bool MftPwmDrv_SetSync(MftPwmDrvType *obj, const MftPwmDrv_SyncType *param)
{
    bool hardwareSync = param->hardwareSync0 || param->hardwareSync1 || param->hardwareSync2;

    /* Software and hardware triggers are not allowed in the same time */
    if((param->softwareSync && hardwareSync) || (true != (param->softwareSync || hardwareSync)))
    {
        return false;
    }

    if(param->softwareSync)
    {
        /* Configure sync for OUTMASK register */
        MftReg_SetSynConfSwOM(obj->base->reg, 1);
        /* Configure sync for INVCTRL register */
        MftReg_SetSynConfSwInvC(obj->base->reg, 1);
        /* Configure sync for SWOCTRL register */
        MftReg_SetSynConfSwSoc(obj->base->reg, 1);
        /* Configure sync for MOD, HCR, CNTIN, and CnV registers */
        MftReg_SetSynConfSwWrbuf(obj->base->reg, 1);
        /* Configure synchronization method (waiting next loading point or now) */
        MftReg_SetSynConfSwRstCnt(obj->base->reg, param->syncPoint);
    }
    else
    {
        /* Configure sync for OUTMASK register */
        MftReg_SetSynConfHwOM(obj->base->reg, 1);
        /* Configure sync for INVCTRL register */
        MftReg_SetSynConfHwInvC(obj->base->reg, 1);
        /* Configure sync for SWOCTRL register */
        MftReg_SetSynConfHwSoc(obj->base->reg, 1);
        /* Configure sync for MOD, HCR, CNTIN, and CnV registers */
        MftReg_SetSynConfHwWrbuf(obj->base->reg, 1);
        /* Configure synchronization method (waiting next loading point or now) */
        MftReg_SetSynConfHwRstCnt(obj->base->reg, param->syncPoint);
    }

    /* Enhanced PWM sync is used */
    MftReg_SetSynConfSyncMode(obj->base->reg, 1);
    /* Configure trigger source for sync */
    MftReg_SetSyncTrig0(obj->base->reg, param->hardwareSync0 ? 1 : 0);
    MftReg_SetSyncTrig1(obj->base->reg, param->hardwareSync1 ? 1 : 0);
    MftReg_SetSyncTrig2(obj->base->reg, param->hardwareSync2 ? 1 : 0);
    /* Configure loading points */
    MftReg_SetSyncCntMax(obj->base->reg, param->maxLoadingPoint);
    MftReg_SetSyncCntMin(obj->base->reg, param->minLoadingPoint);
    /* Configure sync for OUTMASK register */
    MftReg_SetSyncSynchOM(obj->base->reg, (bool)param->maskRegSync);
    /* Configure sync for INVCTRL register */
    MftReg_SetSynConfInvC(obj->base->reg, param->inverterSync);
    /* Configure sync for SWOCTRL register */
    MftReg_SetSynConfSwOC(obj->base->reg, param->outRegSync);
    /* Configure sync for CNTIN register */
    MftReg_SetSynConfCntInC(obj->base->reg, param->initCounterSync);
    /* Configure hardware trigger mode */
    MftReg_SetSynConfHwTrigMode(obj->base->reg, param->autoClearTrigger);

    return true;
}

void MftPwmDrv_Init(MftPwmDrvType *obj, MftDrvType *base)
{
    obj->base = base;

    uint8_t i = 0;
    for(i = 0; i < MFT_CHANNEL_NUM; ++i)
    {
        MftPwmCh_Init(&obj->channel[i], obj);
    }
}

void MftPwmDrv_GetDefaultConfig(MftPwmDrv_ConfigType *userConfig)
{
    userConfig->periodValue = 65536;

    userConfig->syncMethod.softwareSync     = true;
    userConfig->syncMethod.hardwareSync0    = false;
    userConfig->syncMethod.hardwareSync1    = false;
    userConfig->syncMethod.hardwareSync2    = false;
    userConfig->syncMethod.maxLoadingPoint  = false;
    userConfig->syncMethod.minLoadingPoint  = false;
    userConfig->syncMethod.inverterSync     = MFTPWMDRV_SYSTEM_CLOCK;
    userConfig->syncMethod.outRegSync       = MFTPWMDRV_SYSTEM_CLOCK;
    userConfig->syncMethod.maskRegSync      = MFTPWMDRV_SYSTEM_CLOCK;
    userConfig->syncMethod.initCounterSync  = MFTPWMDRV_SYSTEM_CLOCK;
    userConfig->syncMethod.autoClearTrigger = true;
    userConfig->syncMethod.syncPoint        = MFTPWMDRV_WAIT_LOADING_POINTS;

    userConfig->faultConfig.enableTriStateOnFault = false;
    userConfig->faultConfig.faultFilterValue      = 0;
    userConfig->faultConfig.faultMode             = MFTPWMDRV_FAULT_CTRL_DISABLED;
    uint8_t i                                     = 0;
    for(i = 0; i < MFT_FAULT_INPUT_NUM; ++i)
    {
        userConfig->faultConfig.faultInput[i].enabled       = false;
        userConfig->faultConfig.faultInput[i].filterEnabled = false;
        userConfig->faultConfig.faultInput[i].inputPolarity = MFTPWMDRV_FAULT_ACTIVE_HIGH;
    }

    userConfig->deadTimeCount     = 0;
    userConfig->deadTimePrescaler = MFTPWMDRV_DEADTIME_DIVID_BY_1;
}

void MftPwmDrv_Config(MftPwmDrvType *obj, const MftPwmDrv_ConfigType *userConfig)
{
    /* Configure MFT PWM module */
    /* WPDIS = 1, disable write protection */
    MftReg_SetModeWpDis(obj->base->reg, 1);

    /* In PWM mode CNTIN is to be set 0*/
    MftReg_SetCntInCntInit(obj->base->reg, 0U);
    /* Set period */
    MftReg_SetModuloMod(obj->base->reg, userConfig->periodValue);
    /* Sync config */
    MftPwmDrv_SetSync(obj, &userConfig->syncMethod);

    /* Enable faults (if faults were configured) */
    if(userConfig->faultConfig.faultMode != MFTPWMDRV_FAULT_CTRL_DISABLED)
    {
        /* Configure PWM Output behavior */
        MftReg_SetFltCtrlFstate(obj->base->reg, userConfig->faultConfig.enableTriStateOnFault ? 1 : 0);
        /* Configure fault filter value */
        MftReg_SetFltCtrlFFVal(obj->base->reg, userConfig->faultConfig.faultFilterValue);
        uint8_t i = 0;
        for(i = 0; i < MFT_FAULT_INPUT_NUM; ++i)
        {
            /* polyspace-begin DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */
            switch(i)
            {
            case 0:
                MftReg_SetFltCtrlFault0En(obj->base->reg, userConfig->faultConfig.faultInput[0].enabled ? 1 : 0);
                MftReg_SetFltCtrlFFltr0En(obj->base->reg, userConfig->faultConfig.faultInput[0].filterEnabled ? 1 : 0);
                MftReg_SetFltPolFlt0Pol(obj->base->reg, userConfig->faultConfig.faultInput[0].inputPolarity);
                break;
            case 1:
                MftReg_SetFltCtrlFault1En(obj->base->reg, userConfig->faultConfig.faultInput[1].enabled ? 1 : 0);
                MftReg_SetFltCtrlFFltr1En(obj->base->reg, userConfig->faultConfig.faultInput[1].filterEnabled ? 1 : 0);
                MftReg_SetFltPolFlt1Pol(obj->base->reg, userConfig->faultConfig.faultInput[1].inputPolarity);
                break;
            case 2:
                MftReg_SetFltCtrlFault2En(obj->base->reg, userConfig->faultConfig.faultInput[2].enabled ? 1 : 0);
                MftReg_SetFltCtrlFFltr2En(obj->base->reg, userConfig->faultConfig.faultInput[2].filterEnabled ? 1 : 0);
                MftReg_SetFltPolFlt2Pol(obj->base->reg, userConfig->faultConfig.faultInput[2].inputPolarity);
                break;
            case 3:
                MftReg_SetFltCtrlFault3En(obj->base->reg, userConfig->faultConfig.faultInput[3].enabled ? 1 : 0);
                MftReg_SetFltCtrlFFltr3En(obj->base->reg, userConfig->faultConfig.faultInput[3].filterEnabled ? 1 : 0);
                MftReg_SetFltPolFlt3Pol(obj->base->reg, userConfig->faultConfig.faultInput[3].inputPolarity);
                break;
            default:
                break;
            }
            /* polyspace-end DEFECT:DEAD_CODE [No action planned:Low] "Still keep default though it's not reachable" */
        }
        MftReg_SetModeFaultM(obj->base->reg, userConfig->faultConfig.faultMode);
    }

    MftReg_SetDeadTimeDtPs(obj->base->reg, userConfig->deadTimePrescaler);
    MftReg_SetDeadTimeDtVal(obj->base->reg, userConfig->deadTimeCount);

    /* WPEN = 1, enable write protection */
    MftReg_SetFmsWpEn(obj->base->reg, 1);
}

void MftPwmDrv_SetInitOutputCmd(MftPwmDrvType *obj, bool enable)
{
    /* Set enable outputs to be set to Initial/default value */
    MftReg_SetModeInit(obj->base->reg, 1);
}

void MftPwmDrv_SetPeriod(MftPwmDrvType *obj, uint16_t value)
{
    MftReg_SetModuloMod(obj->base->reg, value);
}
