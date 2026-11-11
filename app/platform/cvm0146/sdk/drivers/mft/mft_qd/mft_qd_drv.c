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
#include "mft_qd_drv.h"

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

void MftQdDrv_Init(MftQdDrvType *obj, MftDrvType *base)
{
    obj->base      = base;
    obj->isStarted = false;
}

void MftQdDrv_GetDefaultConfig(MftQdDrv_ConfigType *userConfig)
{
    userConfig->mode                          = MFTQDDRV_PHASE_ENCODE;
    userConfig->initialVal                    = 0U;
    userConfig->maxVal                        = 65535U;
    userConfig->phaseAConfig.phaseInputFilter = false;
    userConfig->phaseAConfig.phaseFilterVal   = 0U;
    userConfig->phaseAConfig.phasePolarity    = MFTQDDRV_PHASE_NORMAL;
    userConfig->phaseBConfig.phaseInputFilter = false;
    userConfig->phaseBConfig.phaseFilterVal   = 0U;
    userConfig->phaseBConfig.phasePolarity    = MFTQDDRV_PHASE_NORMAL;
    userConfig->phaseZConfig.phaseInputFilter = false;
    userConfig->phaseZConfig.phaseFilterVal   = 0U;
    userConfig->phaseZConfig.phasePolarity    = MFTQDDRV_PHASE_NORMAL;
    userConfig->phaseZClearMode               = MFTQDDRV_PHASEZ_CLEAR_NONE;
}

void MftQdDrv_ConfigAndStart(MftQdDrvType *obj, const MftQdDrv_ConfigType *userConfig)
{
    if(false == obj->isStarted)
    {
        /* WPDIS = 1, disable write protection */
        MftReg_SetModeWpDis(obj->base->reg, 1);

        /* Disable Quadrature Decoder */
        MftReg_SetQDCtrlQuadEn(obj->base->reg, 0);
        MftReg_SetScClks(obj->base->reg, 0);

        /* Configure Quadrature Decoder */
        /* Set phase Z clear mode */
        MftReg_SetQDCtrlPhzClearMode(obj->base->reg, userConfig->phaseZClearMode);
        /* Set decoder mode Speed and direction or Phase A and Phase B encoding */
        MftReg_SetQDCtrlQuadMode(obj->base->reg, (uint8_t)userConfig->mode);
        /* Set filter state for Phase A (enable/disable) */
        MftReg_SetQDCtrlPhaFltrEn(obj->base->reg, userConfig->phaseAConfig.phaseInputFilter ? 1 : 0);
        /* Set Phase A filter value if phase filter is enabled */
        if(userConfig->phaseAConfig.phaseInputFilter)
        {
            MftReg_SetFilterCh0FVal(obj->base->reg, userConfig->phaseAConfig.phaseFilterVal);
        }

        /* Set filter state for Phase B (enable/disable) */
        MftReg_SetQDCtrlPhbFltrEn(obj->base->reg, userConfig->phaseBConfig.phaseInputFilter ? 1 : 0);
        /* Set Phase B filter value if phase filter is enabled */
        if(userConfig->phaseBConfig.phaseInputFilter)
        {
            MftReg_SetFilterCh1FVal(obj->base->reg, userConfig->phaseBConfig.phaseFilterVal);
        }

        /* Set filter state for Phase Z (enable/disable) */
        MftReg_SetQDCtrlPhbFltrEn(obj->base->reg, userConfig->phaseZConfig.phaseInputFilter ? 1 : 0);
        /* Set Phase B filter value if phase filter is enabled */
        if(userConfig->phaseZConfig.phaseInputFilter)
        {
            MftReg_SetFilterCh2FVal(obj->base->reg, userConfig->phaseZConfig.phaseFilterVal);
        }

        /* Set polarity for Phase A and Phase B and Phase Z */
        MftReg_SetQDCtrlPhaPol(obj->base->reg, (uint8_t)userConfig->phaseAConfig.phasePolarity);
        MftReg_SetQDCtrlPhbPol(obj->base->reg, (uint8_t)userConfig->phaseBConfig.phasePolarity);
        MftReg_SetQDCtrlPhzPol(obj->base->reg, (uint8_t)userConfig->phaseZConfig.phasePolarity);

        /* Configure counter (initial value and maximum value) */
        MftReg_SetCntInCntInit(obj->base->reg, userConfig->initialVal);
        MftReg_SetModuloMod(obj->base->reg, userConfig->maxVal);
        MftReg_SetCntCount(obj->base->reg, userConfig->initialVal);
        /* Enable Quadrature Decoder */
        MftReg_SetQDCtrlQuadEn(obj->base->reg, 1);

        /* WPEN = 1, enable write protection */
        MftReg_SetFmsWpEn(obj->base->reg, 1);

        obj->isStarted = true;
    }
}

void MftQdDrv_QuadDecodeStop(MftQdDrvType *obj)
{
    /* WPDIS = 1, disable write protection */
    MftReg_SetModeWpDis(obj->base->reg, 1);
    /* Disable Quadrature decoder */
    MftReg_SetQDCtrlQuadEn(obj->base->reg, 0);
    /* WPEN = 1, enable write protection */
    MftReg_SetFmsWpEn(obj->base->reg, 1);
    obj->isStarted = false;
}

void MftQdDrv_GetState(MftQdDrvType *obj, MftQdDrv_StateType *state)
{
    state->counterDirection  = MftReg_GetQDCtrlQuaDir(obj->base->reg) == 1;
    state->overflowDirection = MftReg_GetQDCtrlTorDir(obj->base->reg) == 1;
    state->overflowFlag      = MftReg_GetScTof(obj->base->reg) == 1;
    state->counter           = MftReg_GetCntCount(obj->base->reg);
}
