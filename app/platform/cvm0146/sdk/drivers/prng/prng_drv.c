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
#include "prng_drv.h"
#include "prng_reg.h"

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

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

void PrngDrv_Init(PrngDrvType *obj, struct _PrngRegType_ *reg)
{
    obj->reg = reg;
}

void PrngDrv_Run(PrngDrvType *obj, PrngCfgType *cfg)
{
    /* use secure mode */
    PrngReg_SetSecureMode(obj->reg, 1);
    /* set nonce mode enable */
    PrngReg_SetNonceModeEnable(obj->reg, 1);
    /* set random length mode as 128-bit */
    PrngReg_SetRandLen(obj->reg, 0);
    /* set random ready interrupt enable */
    if(cfg->randRdyIntEna == true)
    {
        PrngReg_SetGloalIntEnable(obj->reg, true);
        PrngReg_SetRandRdyIntEnable(obj->reg, true);
    }
    else
    {
        PrngReg_SetGloalIntEnable(obj->reg, false);
        PrngReg_SetRandRdyIntEnable(obj->reg, false);
    }

    /* run command */
    if(cfg->cmd == RANDCMDMODE_RAND)
    {
        /* check if seeded */
        if(PrngReg_GetSeedSts(obj->reg) == true)
        {
            /* run random generation command */
            PrngReg_SetCmd(obj->reg, RANDCMDMODE_RAND);
        }
        else
        {
            /* no seed existing cannot generate pseudo random number */
        }
    }
    else if(cfg->cmd == RANDCMDMODE_NONCE)
    {
        /* set seeds */
        PrngReg_SetSeedVal(obj->reg, cfg->seed);

        /* run NONCE command */
        PrngReg_SetCmd(obj->reg, RANDCMDMODE_NONCE);
    }
}