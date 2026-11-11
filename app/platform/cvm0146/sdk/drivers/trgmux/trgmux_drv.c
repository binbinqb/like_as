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
#include "trgmux_drv.h"
#include "trgmux_reg.h"
#include "sim_reg.h"

/*******************************************************************************
 * the defines
 ******************************************************************************/

/* Number of target modules for TRGMUX IP */
#define TRGMUXDRV_MODULE_NUM (sizeof(TrgMuxRegType) / sizeof(uint32_t))
/* Number of output ports in one target module */
#define TRGMUXDRV_TARGET_NUM (4)
/* Sim software trigger delay */
#define TRGMUXDRV_DELAY(x)                        \
    do                                            \
    {                                             \
        for(volatile int cnt = 0; cnt < x; cnt++) \
        {                                         \
            ;                                     \
        }                                         \
    } while(0)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/* Definition of function prototype of getting module's lock state */
typedef uint8_t (*TrgMuxReg_GetModuleLockFunc)(const TrgMuxRegType *obj);
/* Definition of function prototype of locking module selection */
typedef void (*TrgMuxReg_SetModuleLockFunc)(TrgMuxRegType *obj, uint8_t value);
/* Definition of function prototype of getting module selection */
typedef uint8_t (*TrgMuxReg_GetModuleSelFunc)(const TrgMuxRegType *obj);
/* Definition of function prototype of setting module selection */
typedef void (*TrgMuxReg_SetModuleSelFunc)(TrgMuxRegType *obj, uint8_t value);

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the constants
 ******************************************************************************/

/* Definition of the table of getting module's lock state functions */
static const TrgMuxReg_GetModuleLockFunc c_getModuleLockFuncTable[TRGMUXDRV_MODULE_NUM] = {
    TrgMuxReg_GetDmaMux0Lk,
    TrgMuxReg_GetExtOut0Lk,
    TrgMuxReg_GetExtOut1Lk,
    TrgMuxReg_GetAdc0Lk,
    TrgMuxReg_GetAdc1Lk,
    TrgMuxReg_GetCmpLk,
    TrgMuxReg_GetMft0Lk,
    TrgMuxReg_GetMft1Lk,
    TrgMuxReg_GetMft2Lk,
    TrgMuxReg_GetMft3Lk,
    TrgMuxReg_GetMft4Lk,
    TrgMuxReg_GetMft5Lk,
    TrgMuxReg_GetPdb0Lk,
    TrgMuxReg_GetPdb1Lk,
    TrgMuxReg_GetLpitLk,
    TrgMuxReg_GetLptmrLk};

/* Definition of the table of setting module's lock state functions */
static const TrgMuxReg_SetModuleLockFunc c_setModuleLockFuncTable[TRGMUXDRV_MODULE_NUM] = {
    TrgMuxReg_SetDmaMux0Lk,
    TrgMuxReg_SetExtOut0Lk,
    TrgMuxReg_SetExtOut1Lk,
    TrgMuxReg_SetAdc0Lk,
    TrgMuxReg_SetAdc1Lk,
    TrgMuxReg_SetCmpLk,
    TrgMuxReg_SetMft0Lk,
    TrgMuxReg_SetMft1Lk,
    TrgMuxReg_SetMft2Lk,
    TrgMuxReg_SetMft3Lk,
    TrgMuxReg_SetMft4Lk,
    TrgMuxReg_SetMft5Lk,
    TrgMuxReg_SetPdb0Lk,
    TrgMuxReg_SetPdb1Lk,
    TrgMuxReg_SetLpitLk,
    TrgMuxReg_SetLptmrLk};

/* Definition of the table of getting module's selection functions */
static const TrgMuxReg_GetModuleSelFunc c_getModuleSelFuncTable[TRGMUXDRV_MODULE_NUM][TRGMUXDRV_TARGET_NUM] = {
    {TrgMuxReg_GetDmaMux0Sel0, TrgMuxReg_GetDmaMux0Sel1, TrgMuxReg_GetDmaMux0Sel2, TrgMuxReg_GetDmaMux0Sel3},
    {TrgMuxReg_GetExtOut0Sel0, TrgMuxReg_GetExtOut0Sel1, TrgMuxReg_GetExtOut0Sel2, TrgMuxReg_GetExtOut0Sel3},
    {TrgMuxReg_GetExtOut1Sel0, TrgMuxReg_GetExtOut1Sel1, TrgMuxReg_GetExtOut1Sel2, TrgMuxReg_GetExtOut1Sel3},
    {TrgMuxReg_GetAdc0Sel0,    TrgMuxReg_GetAdc0Sel1,    TrgMuxReg_GetAdc0Sel2,    TrgMuxReg_GetAdc0Sel3   },
    {TrgMuxReg_GetAdc1Sel0,    TrgMuxReg_GetAdc1Sel1,    TrgMuxReg_GetAdc1Sel2,    TrgMuxReg_GetAdc1Sel3   },
    {TrgMuxReg_GetCmpSel0,     NULL,                     NULL,                     NULL                    },
    {TrgMuxReg_GetMft0Sel0,    TrgMuxReg_GetMft0Sel1,    TrgMuxReg_GetMft0Sel2,    TrgMuxReg_GetMft0Sel3   },
    {TrgMuxReg_GetMft1Sel0,    TrgMuxReg_GetMft1Sel1,    TrgMuxReg_GetMft1Sel2,    TrgMuxReg_GetMft1Sel3   },
    {TrgMuxReg_GetMft2Sel0,    TrgMuxReg_GetMft2Sel1,    TrgMuxReg_GetMft2Sel2,    TrgMuxReg_GetMft2Sel3   },
    {TrgMuxReg_GetMft3Sel0,    TrgMuxReg_GetMft3Sel1,    TrgMuxReg_GetMft3Sel2,    TrgMuxReg_GetMft3Sel3   },
    {TrgMuxReg_GetMft4Sel0,    TrgMuxReg_GetMft4Sel1,    TrgMuxReg_GetMft4Sel2,    TrgMuxReg_GetMft4Sel3   },
    {TrgMuxReg_GetMft5Sel0,    TrgMuxReg_GetMft5Sel1,    TrgMuxReg_GetMft5Sel2,    TrgMuxReg_GetMft5Sel3   },
    {TrgMuxReg_GetPdb0Sel0,    NULL,                     NULL,                     NULL                    },
    {TrgMuxReg_GetPdb1Sel0,    NULL,                     NULL,                     NULL                    },
    {TrgMuxReg_GetLpitSel0,    TrgMuxReg_GetLpitSel1,    TrgMuxReg_GetLpitSel2,    TrgMuxReg_GetLpitSel3   },
    {TrgMuxReg_GetLptmrSel0,   NULL,                     NULL,                     NULL                    },
};

/* Definition of the table of setting module's selection functions */
static const TrgMuxReg_SetModuleSelFunc c_setModuleSelFuncTable[TRGMUXDRV_MODULE_NUM][TRGMUXDRV_TARGET_NUM] = {
    {TrgMuxReg_SetDmaMux0Sel0, TrgMuxReg_SetDmaMux0Sel1, TrgMuxReg_SetDmaMux0Sel2, TrgMuxReg_SetDmaMux0Sel3},
    {TrgMuxReg_SetExtOut0Sel0, TrgMuxReg_SetExtOut0Sel1, TrgMuxReg_SetExtOut0Sel2, TrgMuxReg_SetExtOut0Sel3},
    {TrgMuxReg_SetExtOut1Sel0, TrgMuxReg_SetExtOut1Sel1, TrgMuxReg_SetExtOut1Sel2, TrgMuxReg_SetExtOut1Sel3},
    {TrgMuxReg_SetAdc0Sel0,    TrgMuxReg_SetAdc0Sel1,    TrgMuxReg_SetAdc0Sel2,    TrgMuxReg_SetAdc0Sel3   },
    {TrgMuxReg_SetAdc1Sel0,    TrgMuxReg_SetAdc1Sel1,    TrgMuxReg_SetAdc1Sel2,    TrgMuxReg_SetAdc1Sel3   },
    {TrgMuxReg_SetCmpSel0,     NULL,                     NULL,                     NULL                    },
    {TrgMuxReg_SetMft0Sel0,    TrgMuxReg_SetMft0Sel1,    TrgMuxReg_SetMft0Sel2,    TrgMuxReg_SetMft0Sel3   },
    {TrgMuxReg_SetMft1Sel0,    TrgMuxReg_SetMft1Sel1,    TrgMuxReg_SetMft1Sel2,    TrgMuxReg_SetMft1Sel3   },
    {TrgMuxReg_SetMft2Sel0,    TrgMuxReg_SetMft2Sel1,    TrgMuxReg_SetMft2Sel2,    TrgMuxReg_SetMft2Sel3   },
    {TrgMuxReg_SetMft3Sel0,    TrgMuxReg_SetMft3Sel1,    TrgMuxReg_SetMft3Sel2,    TrgMuxReg_SetMft3Sel3   },
    {TrgMuxReg_SetMft4Sel0,    TrgMuxReg_SetMft4Sel1,    TrgMuxReg_SetMft4Sel2,    TrgMuxReg_SetMft4Sel3   },
    {TrgMuxReg_SetMft5Sel0,    TrgMuxReg_SetMft5Sel1,    TrgMuxReg_SetMft5Sel2,    TrgMuxReg_SetMft5Sel3   },
    {TrgMuxReg_SetPdb0Sel0,    NULL,                     NULL,                     NULL                    },
    {TrgMuxReg_SetPdb1Sel0,    NULL,                     NULL,                     NULL                    },
    {TrgMuxReg_SetLpitSel0,    TrgMuxReg_SetLpitSel1,    TrgMuxReg_SetLpitSel2,    TrgMuxReg_SetLpitSel3   },
    {TrgMuxReg_SetLptmrSel0,   NULL,                     NULL,                     NULL                    },
};

/*******************************************************************************
 * the functions
 ******************************************************************************/

void TrgMuxDrv_Init(TrgMuxDrvType *obj, struct _TrgMuxRegType_ *trgMuxReg, struct _SimRegType_ *simReg)
{
    obj->trgMuxReg = trgMuxReg;
    obj->simReg    = simReg;
}

void TrgMuxDrv_Configure(TrgMuxDrvType *obj, const TrgMuxDrv_ConfigType *userConfig)
{
    uint16_t index;

    if((obj == NULL)
       || (userConfig == NULL)
       || (userConfig->numOfInOutMappings == 0))
    {
        return;
    }

    for(index = 0; index < userConfig->numOfInOutMappings; index++)
    {
        TrgMuxDrv_SetTrigSourceForTargetModule(obj,
                                               userConfig->inOutMapping[index].triggerSource,
                                               userConfig->inOutMapping[index].targetModule);
    }
    for(index = 0; index < userConfig->numOfInOutMappings; index++)
    {
        if(userConfig->inOutMapping[index].lockTargetModuleReg)
        {
            TrgMuxDrv_SetLockForTargetModule(obj, userConfig->inOutMapping[index].targetModule);
        }
    }
}

bool TrgMuxDrv_SetTrigSourceForTargetModule(TrgMuxDrvType *obj, TrgMuxDrv_TrigSourceType triggerSource, TrgMuxDrv_TargetModuleType targetModule)
{
    bool retval;

    if(TrgMuxDrv_GetLockForTargetModule(obj, targetModule) == true)
    {
        retval = false;
    }
    else
    {
        /* Configure link between trigger source and target module. */
        uint8_t moduleIndex = (uint8_t)((uint32_t)targetModule / 4);
        uint8_t sourceIndex = (uint8_t)((uint32_t)targetModule % 4);
        if(c_setModuleSelFuncTable[moduleIndex][sourceIndex] != NULL)
        {
            c_setModuleSelFuncTable[moduleIndex][sourceIndex](obj->trgMuxReg, triggerSource);
            retval = true;
        }
        else
        {
            retval = false;
        }
    }

    return retval;
}

TrgMuxDrv_TrigSourceType TrgMuxDrv_GetTrigSourceForTargetModule(const TrgMuxDrvType *obj, TrgMuxDrv_TargetModuleType targetModule)
{
    TrgMuxDrv_TrigSourceType retval      = TRGMUXDRV_TRIGSOURCE_SIG0;
    uint8_t                  moduleIndex = (uint8_t)((uint32_t)targetModule / 4);
    uint8_t                  sourceIndex = (uint8_t)((uint32_t)targetModule % 4);
    if(c_getModuleSelFuncTable[moduleIndex][sourceIndex] != NULL)
    {
        retval = (TrgMuxDrv_TrigSourceType)c_getModuleSelFuncTable[moduleIndex][sourceIndex](obj->trgMuxReg);
    }

    return retval;
}

void TrgMuxDrv_SetLockForTargetModule(TrgMuxDrvType *obj, TrgMuxDrv_TargetModuleType targetModule)
{
    uint8_t moduleIndex = (uint8_t)((uint32_t)targetModule / 4);
    if(c_setModuleLockFuncTable[moduleIndex] != NULL)
    {
        c_setModuleLockFuncTable[moduleIndex](obj->trgMuxReg, 1);
    }
}

bool TrgMuxDrv_GetLockForTargetModule(const TrgMuxDrvType *obj, TrgMuxDrv_TargetModuleType targetModule)
{
    bool    retval      = true;
    uint8_t moduleIndex = (uint8_t)((uint32_t)targetModule / 4);
    if(c_getModuleLockFuncTable[moduleIndex] != NULL)
    {
        retval = (c_getModuleLockFuncTable[moduleIndex](obj->trgMuxReg) == 1);
    }

    return retval;
}

void TrgMuxDrv_GenSWTrigger(TrgMuxDrvType *obj, uint32_t delay)
{
    /* The trigger is generated only when writing from 0 to 1*/
    SimReg_SetSwTrg(obj->simReg, 0);
    TRGMUXDRV_DELAY(delay);
    SimReg_SetSwTrg(obj->simReg, 1);
}
