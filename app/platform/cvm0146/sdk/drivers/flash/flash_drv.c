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

#include "flash_drv.h"
#include "ftfc_reg.h"
#include "../CVM014x_features.h"

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

static void            FlashDrv_ClearCommandState(FlashDrvType *obj);
static FlashDrv_Status FlashDrv_CommandSequence(FlashDrvType *obj);

void FlashDrv_Init(FlashDrvType *obj, struct _FtfcRegType_ *reg)
{
    obj->reg        = reg;
    obj->eeevld     = FlashDrv_GetEeeEn(obj);
    obj->pflashbase = 0x0;
    obj->pflashsize = FEATURE_PFLASH_SIZE;
    obj->dflashbase = 0x10020000 - FEATURE_DFLASH_SIZE;
    if(obj->eeevld)
    {
        obj->dflashsize = FEATURE_DFLASH_SIZE;
    }
    else
    {
        obj->dflashsize = FEATURE_DFLASH_SIZE + 0x20000; /* No extra dflash occupied if EEEPROM not available */
    }
}

void FlashDrv_GetConfig(const FlashDrvType  *obj,
                        FlashDrv_ConfigType *userconfig)
{
    userconfig->pflashbase = obj->pflashbase;
    userconfig->pflashsize = obj->pflashsize;
    userconfig->dflashbase = obj->dflashbase;
    userconfig->dflashsize = obj->dflashsize;
    userconfig->eeevld     = obj->eeevld;
    userconfig->callback   = obj->callback;
}

void FlashDrv_GetDefaultConfig(FlashDrv_ConfigType *userconfig)
{
    userconfig->eeevld     = false;
    userconfig->callback   = NULL;
    userconfig->pflashbase = 0x0;
    userconfig->pflashsize = FEATURE_PFLASH_SIZE;
    userconfig->dflashbase = 0x10020000 - FEATURE_DFLASH_SIZE;
    userconfig->dflashsize = FEATURE_DFLASH_SIZE + 0x20000; /* No extra dflash occupied if EEEPROM not available */
}

void FlashDrv_Configure(FlashDrvType              *obj,
                        const FlashDrv_ConfigType *userconfig)
{
    /* Only callback function is configurable. Other paramaters shoud NOT be changed */
    obj->callback = userconfig->callback;
}

static void FlashDrv_ClearCommandState(FlashDrvType *obj)
{
    FtfcReg_SetFstatProtViolF(obj->reg, 1);
    FtfcReg_SetFstatAccErrF(obj->reg, 1);
    FtfcReg_SetFstatRdColF(obj->reg, 1);
    FtfcReg_SetFstatFtfcSecF(obj->reg, 1);
    FtfcReg_SetFstatFtfcDedF(obj->reg, 1);
    FtfcReg_SetFstatAhbSecF(obj->reg, 1);
    FtfcReg_SetFstatAhbDedF(obj->reg, 1);
}

static FlashDrv_Status FlashDrv_CommandSequence(FlashDrvType *obj)
{
    FlashDrv_Status ret = FLASHDRV_STATUS_SUCCESS;

    FtfcReg_SetFstatCcif(obj->reg, 1);

    while(0U == FtfcReg_GetFstatCcif(obj->reg))
    {
    }

    if(FtfcReg_GetFstatAccErrF(obj->reg) || FtfcReg_GetFstatProtViolF(obj->reg) || FtfcReg_GetFstatMgStat(obj->reg))
    {
        ret = FLASHDRV_STATUS_ERROR;
    }

    return ret;
}

FlashDrv_Status FlashDrv_Read1sBlock(FlashDrvType *obj, uint32_t *destaddr)
{
    FlashDrv_Status ret  = FLASHDRV_STATUS_SUCCESS;
    uint32_t        dest = (uint32_t)destaddr;

    dest = ALIGNED(dest, (uint32_t)8);

    if((dest >= (obj->pflashbase + obj->pflashsize) && dest < obj->dflashbase) || (obj->dflashsize > 0 && dest >= (obj->dflashbase + obj->dflashsize)) || (dest >= obj->dflashbase && obj->eeevld))
    {
        ret = FLASHDRV_STATUS_ERROR;
    }

    if(ret == FLASHDRV_STATUS_SUCCESS)
    {
        if(0U == FtfcReg_GetFstatCcif(obj->reg))
        {
            ret = FLASHDRV_STATUS_BUSY;
        }
        else
        {
            FlashDrv_ClearCommandState(obj);
            FtfcReg_SetFccob(obj->reg, 0, FLASHDRV_OPCMD_BLKRD1S);
            FtfcReg_SetFccob(obj->reg, 1, FCCOBADDRLOW(dest));
            FtfcReg_SetFccob(obj->reg, 2, FCCOBADDRMDLOW(dest));
            FtfcReg_SetFccob(obj->reg, 3, FCCOBADDRMDHIG(dest));
            FtfcReg_SetFccob(obj->reg, 4, FCCOBADDRHIG(dest));
            FtfcReg_SetFccob(obj->reg, 5, 0);

            ret = FlashDrv_CommandSequence(obj);
        }
    }

    return ret;
}

FlashDrv_Status FlashDrv_Read1sSection(FlashDrvType *obj, uint32_t *destaddr, uint32_t rdsize)
{
    FlashDrv_Status ret   = FLASHDRV_STATUS_SUCCESS;
    uint32_t        dest  = (uint32_t)destaddr;
    uint32_t        sctsz = 1024;

    if(!IS_ALIGNED(dest, 8) || !IS_ALIGNED(rdsize, 8))
    {
        ret = FLASHDRV_STATUS_ERROR;
    }
    if(dest < (obj->pflashbase + obj->pflashsize))
    {
        sctsz = FLASHDRV_PFLASH_SECTOR_SIZE;
    }
    else if(dest >= obj->dflashbase && dest < (obj->dflashbase + obj->dflashsize))
    {
        sctsz = FLASHDRV_DFLASH_SECTOR_SIZE;
    }
    else
    {
        ret = FLASHDRV_STATUS_ERROR;
    }

    if(ALIGNED(dest + rdsize - 1, sctsz) > ALIGNED(dest, sctsz))
    {
        ret = FLASHDRV_STATUS_ERROR;
    }

    if(ret == FLASHDRV_STATUS_SUCCESS)
    {
        if(0U == FtfcReg_GetFstatCcif(obj->reg))
        {
            ret = FLASHDRV_STATUS_BUSY;
        }
        else
        {
            FlashDrv_ClearCommandState(obj);
            FtfcReg_SetFccob(obj->reg, 0, FLASHDRV_OPCMD_SCTRD1S);
            FtfcReg_SetFccob(obj->reg, 1, FCCOBADDRLOW(dest));
            FtfcReg_SetFccob(obj->reg, 2, FCCOBADDRMDLOW(dest));
            FtfcReg_SetFccob(obj->reg, 3, FCCOBADDRMDHIG(dest));
            FtfcReg_SetFccob(obj->reg, 4, FCCOBADDRHIG(dest));
            FtfcReg_SetFccob(obj->reg, 5, (uint8_t)((rdsize / FLASHDRV_PHRASE_SIZE) - 1));

            ret = FlashDrv_CommandSequence(obj);
        }
    }

    return ret;
}

FlashDrv_Status FlashDrv_CheckPhrase(FlashDrvType *obj, uint32_t *destaddr, uint8_t *expdata)
{
    FlashDrv_Status ret  = FLASHDRV_STATUS_SUCCESS;
    uint32_t        dest = (uint32_t)destaddr;
    uint32_t        i    = 0;

    if(!IS_ALIGNED(dest, 8))
    {
        ret = FLASHDRV_STATUS_ERROR;
    }

    if((dest >= (obj->pflashbase + obj->pflashsize) && dest < obj->dflashbase) || (dest >= (obj->dflashbase + obj->dflashsize)))
    {
        ret = FLASHDRV_STATUS_ERROR;
    }

    if(expdata == NULL)
    {
        ret = FLASHDRV_STATUS_ERROR;
    }

    if(ret == FLASHDRV_STATUS_SUCCESS)
    {
        if(0U == FtfcReg_GetFstatCcif(obj->reg))
        {
            ret = FLASHDRV_STATUS_BUSY;
        }
        else
        {
            FlashDrv_ClearCommandState(obj);
            FtfcReg_SetFccob(obj->reg, 0, FLASHDRV_OPCMD_PRSCHK);
            FtfcReg_SetFccob(obj->reg, 1, FCCOBADDRLOW(dest));
            FtfcReg_SetFccob(obj->reg, 2, FCCOBADDRMDLOW(dest));
            FtfcReg_SetFccob(obj->reg, 3, FCCOBADDRMDHIG(dest));
            FtfcReg_SetFccob(obj->reg, 4, FCCOBADDRHIG(dest));
            for(i = 0; i < FLASHDRV_PHRASE_SIZE; i++)
            {
                FtfcReg_SetFccob(obj->reg, (uint8_t)(5 + i), expdata[i]);
            }
            ret = FlashDrv_CommandSequence(obj);
            ret |= ((FtfcReg_GetFstatFtfcSecF(obj->reg) | FtfcReg_GetFstatFtfcDedF(obj->reg)) == 1) ? FLASHDRV_STATUS_WARNING : FLASHDRV_STATUS_SUCCESS;
        }
    }
    return ret;
}

FlashDrv_Status FlashDrv_CheckEccState(FlashDrvType *obj, uint32_t *destaddr)
{
    FlashDrv_Status ret  = FLASHDRV_STATUS_SUCCESS;
    uint32_t        dest = (uint32_t)destaddr;
    uint32_t        i    = 0;

    if(!IS_ALIGNED(dest, 8))
    {
        ret = FLASHDRV_STATUS_ERROR;
    }

    if((dest >= (obj->pflashbase + obj->pflashsize) && dest < obj->dflashbase) || (dest >= (obj->dflashbase + obj->dflashsize)))
    {
        ret = FLASHDRV_STATUS_ERROR;
    }

    if(ret == FLASHDRV_STATUS_SUCCESS)
    {
        if(0U == FtfcReg_GetFstatCcif(obj->reg))
        {
            ret = FLASHDRV_STATUS_BUSY;
        }
        else
        {
            FlashDrv_ClearCommandState(obj);
            FtfcReg_SetFccob(obj->reg, 0, FLASHDRV_OPCMD_PRSCHK);
            FtfcReg_SetFccob(obj->reg, 1, FCCOBADDRLOW(dest));
            FtfcReg_SetFccob(obj->reg, 2, FCCOBADDRMDLOW(dest));
            FtfcReg_SetFccob(obj->reg, 3, FCCOBADDRMDHIG(dest));
            FtfcReg_SetFccob(obj->reg, 4, FCCOBADDRHIG(dest));

            for(i = 0; i < FLASHDRV_PHRASE_SIZE; i++)
            {
                FtfcReg_SetFccob(obj->reg, 5 + i, 0xFF);
            }
            FlashDrv_CommandSequence(obj);
            ret = (FtfcReg_GetFstatFtfcSecF(obj->reg) == 1) ? FLASHDRV_STATUS_WARNING : FLASHDRV_STATUS_SUCCESS;
            ret |= (FtfcReg_GetFstatFtfcDedF(obj->reg) == 1) ? FLASHDRV_STATUS_ERROR : FLASHDRV_STATUS_SUCCESS;
        }
    }
    return ret;
}

FlashDrv_Status FlashDrv_ProgramPhrase(FlashDrvType *obj, uint32_t *destaddr, uint8_t *expdata, bool hweccen)
{
    FlashDrv_Status ret  = FLASHDRV_STATUS_SUCCESS;
    uint32_t        dest = (uint32_t)destaddr;
    uint32_t        i    = 0;

    if(!IS_ALIGNED(dest, 8))
    {
        ret = FLASHDRV_STATUS_ERROR;
    }

    if((dest >= (obj->pflashbase + obj->pflashsize) && dest < obj->dflashbase) || (dest >= (obj->dflashbase + obj->dflashsize)))
    {
        ret = FLASHDRV_STATUS_ERROR;
    }

    if(expdata == NULL)
    {
        ret = FLASHDRV_STATUS_ERROR;
    }

    if(ret == FLASHDRV_STATUS_SUCCESS)
    {
        if(0U == FtfcReg_GetFstatCcif(obj->reg))
        {
            ret = FLASHDRV_STATUS_BUSY;
        }
        else
        {
            FlashDrv_ClearCommandState(obj);
            FtfcReg_SetFccob(obj->reg, 0, FLASHDRV_OPCMD_PRSPGM);
            FtfcReg_SetFccob(obj->reg, 1, FCCOBADDRLOW(dest));
            FtfcReg_SetFccob(obj->reg, 2, FCCOBADDRMDLOW(dest));
            FtfcReg_SetFccob(obj->reg, 3, FCCOBADDRMDHIG(dest));
            FtfcReg_SetFccob(obj->reg, 4, FCCOBADDRHIG(dest));
            FtfcReg_SetFccob(obj->reg, 5, (hweccen ? 1 : 0));
            for(i = 0; i < FLASHDRV_PHRASE_SIZE; i++)
            {
                FtfcReg_SetFccob(obj->reg, (uint8_t)(6 + i), expdata[i]);
            }
            if(!hweccen)
            {
                FtfcReg_SetFccob(obj->reg, 14, expdata[8]);
            }

            ret = FlashDrv_CommandSequence(obj);
            ret |= ((FtfcReg_GetFstatFtfcSecF(obj->reg) | FtfcReg_GetFstatFtfcDedF(obj->reg)) == 1) ? FLASHDRV_STATUS_WARNING : FLASHDRV_STATUS_SUCCESS;
        }
    }
    return ret;
}

FlashDrv_Status FlashDrv_EraseBlock(FlashDrvType *obj, uint32_t *destaddr, FlashDrv_SectorErase_t erasetype)
{
    FlashDrv_Status ret  = FLASHDRV_STATUS_SUCCESS;
    uint32_t        dest = (uint32_t)destaddr;

    dest = ALIGNED(dest, (uint32_t)8);

    if((dest >= (obj->pflashbase + obj->pflashsize) && dest < obj->dflashbase) || (obj->dflashsize > 0 && dest >= (obj->dflashbase + obj->dflashsize)) || (dest >= obj->dflashbase && obj->eeevld))
    {
        ret = FLASHDRV_STATUS_ERROR;
    }

    if(ret == FLASHDRV_STATUS_SUCCESS)
    {
        if(0U == FtfcReg_GetFstatCcif(obj->reg))
        {
            ret = FLASHDRV_STATUS_BUSY;
        }
        else
        {
            FlashDrv_ClearCommandState(obj);
            FtfcReg_SetFccob(obj->reg, 0, FLASHDRV_OPCMD_BLKERS);
            FtfcReg_SetFccob(obj->reg, 1, FCCOBADDRLOW(dest));
            FtfcReg_SetFccob(obj->reg, 2, FCCOBADDRMDLOW(dest));
            FtfcReg_SetFccob(obj->reg, 3, FCCOBADDRMDHIG(dest));
            FtfcReg_SetFccob(obj->reg, 4, FCCOBADDRHIG(dest));
            FtfcReg_SetFccob(obj->reg, 5, erasetype);

            ret = FlashDrv_CommandSequence(obj);
        }
    }

    return ret;
}

FlashDrv_Status FlashDrv_EraseSector(FlashDrvType *obj, uint32_t *destaddr, FlashDrv_SectorErase_t erasetype)
{
    FlashDrv_Status ret  = FLASHDRV_STATUS_SUCCESS;
    uint32_t        dest = (uint32_t)destaddr;

    dest = ALIGNED(dest, (uint32_t)8);

    if((dest >= (obj->pflashbase + obj->pflashsize) && dest < obj->dflashbase) || (dest >= (obj->dflashbase + obj->dflashsize)))
    {
        ret = FLASHDRV_STATUS_ERROR;
    }

    if(ret == FLASHDRV_STATUS_SUCCESS)
    {
        if(0U == FtfcReg_GetFstatCcif(obj->reg))
        {
            ret = FLASHDRV_STATUS_BUSY;
        }
        else
        {
            FlashDrv_ClearCommandState(obj);
            FtfcReg_SetFccob(obj->reg, 0, FLASHDRV_OPCMD_SCTERS);
            FtfcReg_SetFccob(obj->reg, 1, FCCOBADDRLOW(dest));
            FtfcReg_SetFccob(obj->reg, 2, FCCOBADDRMDLOW(dest));
            FtfcReg_SetFccob(obj->reg, 3, FCCOBADDRMDHIG(dest));
            FtfcReg_SetFccob(obj->reg, 4, FCCOBADDRHIG(dest));
            FtfcReg_SetFccob(obj->reg, 5, erasetype);

            ret = FlashDrv_CommandSequence(obj);
        }
    }

    return ret;
}

FlashDrv_Status FlashDrv_ProgramSection(FlashDrvType *obj, uint32_t *destaddr, uint32_t len, uint8_t *databuf)
{
    FlashDrv_Status ret   = FLASHDRV_STATUS_SUCCESS;
    uint32_t        dest  = (uint32_t)destaddr;
    uint32_t        sctsz = 1024, i = 0, offset = 0;
    bool            eeeramrdy = false;
    uint8_t        *pfastram, *pdata;

    if(!IS_ALIGNED(dest, 256) || !IS_ALIGNED(len, 256))
    {
        ret = FLASHDRV_STATUS_ERROR;
    }

    if(dest < (obj->pflashbase + obj->pflashsize))
    {
        sctsz = FLASHDRV_PFLASH_SECTOR_SIZE;
    }
    else if(dest >= obj->dflashbase && dest < (obj->dflashbase + obj->dflashsize))
    {
        sctsz = FLASHDRV_DFLASH_SECTOR_SIZE;
    }
    else
    {
        ret = FLASHDRV_STATUS_ERROR;
    }

    if(ALIGNED(dest + len - 1, sctsz) > ALIGNED(dest, sctsz))
    {
        ret = FLASHDRV_STATUS_ERROR;
    }

    eeeramrdy = (FtfcReg_GetFstatEeeRamRdy(obj->reg) == 1);

    if(eeeramrdy)
    {
        FlashDrv_SetFlexRam(obj, false);
    }

    offset   = dest & (sctsz - 1);
    pfastram = (uint8_t *)(FLASHDRV_FLEXRAM_ADDR + offset);
    pdata    = databuf;
    for(i = 0; i < len; i++)
    {
        *pfastram = *pdata;
        pfastram++;
        pdata++;
    }

    if(ret == FLASHDRV_STATUS_SUCCESS)
    {
        if(0U == FtfcReg_GetFstatCcif(obj->reg))
        {
            ret = FLASHDRV_STATUS_BUSY;
        }
        else
        {
            FlashDrv_ClearCommandState(obj);
            FtfcReg_SetFccob(obj->reg, 0, FLASHDRV_OPCMD_SCTPGM);
            FtfcReg_SetFccob(obj->reg, 1, FCCOBADDRLOW(dest));
            FtfcReg_SetFccob(obj->reg, 2, FCCOBADDRMDLOW(dest));
            FtfcReg_SetFccob(obj->reg, 3, FCCOBADDRMDHIG(dest));
            FtfcReg_SetFccob(obj->reg, 4, FCCOBADDRHIG(dest));
            FtfcReg_SetFccob(obj->reg, 5, (uint8_t)((len / FLASHDRV_PHRASE_SIZE) - 1));

            ret = FlashDrv_CommandSequence(obj);
            ret |= ((FtfcReg_GetFstatFtfcSecF(obj->reg) | FtfcReg_GetFstatFtfcDedF(obj->reg)) == 1) ? FLASHDRV_STATUS_WARNING : FLASHDRV_STATUS_SUCCESS;
        }
    }
    if(eeeramrdy)
    {
        FlashDrv_SetFlexRam(obj, true);
    }

    return ret;
}

FlashDrv_Status FlashDrv_ProgramSectionFast(FlashDrvType *obj, uint32_t *destaddr, uint32_t len)
{
    FlashDrv_Status ret      = FLASHDRV_STATUS_SUCCESS;
    uint32_t        dest     = (uint32_t)destaddr;
    uint32_t        sctsz    = 1024;
    bool            eeeramrdy = false;

    if(!IS_ALIGNED(dest, 256) || !IS_ALIGNED(len, 256))
    {
        ret = FLASHDRV_STATUS_ERROR;
    }

    if(dest < (obj->pflashbase + obj->pflashsize))
    {
        sctsz = FLASHDRV_PFLASH_SECTOR_SIZE;
    }
    else if(dest >= obj->dflashbase && dest < (obj->dflashbase + obj->dflashsize))
    {
        sctsz = FLASHDRV_DFLASH_SECTOR_SIZE;
    }
    else
    {
        ret = FLASHDRV_STATUS_ERROR;
    }

    if(ALIGNED(dest + len - 1, sctsz) > ALIGNED(dest, sctsz))
    {
        ret = FLASHDRV_STATUS_ERROR;
    }

    eeeramrdy = (FtfcReg_GetFstatEeeRamRdy(obj->reg) == 1);

    if(eeeramrdy)
    {
        FlashDrv_SetFlexRam(obj, false);
    }

    if(ret == FLASHDRV_STATUS_SUCCESS)
    {
        if(0U == FtfcReg_GetFstatCcif(obj->reg))
        {
            ret = FLASHDRV_STATUS_BUSY;
        }
        else
        {
            FlashDrv_ClearCommandState(obj);
            FtfcReg_SetFccob(obj->reg, 0, FLASHDRV_OPCMD_SCTPGM);
            FtfcReg_SetFccob(obj->reg, 1, FCCOBADDRLOW(dest));
            FtfcReg_SetFccob(obj->reg, 2, FCCOBADDRMDLOW(dest));
            FtfcReg_SetFccob(obj->reg, 3, FCCOBADDRMDHIG(dest));
            FtfcReg_SetFccob(obj->reg, 4, FCCOBADDRHIG(dest));
            FtfcReg_SetFccob(obj->reg, 5, (uint8_t)((len / FLASHDRV_PHRASE_SIZE) - 1));

            ret = FlashDrv_CommandSequence(obj);
            ret |= ((FtfcReg_GetFstatFtfcSecF(obj->reg) | FtfcReg_GetFstatFtfcDedF(obj->reg)) == 1) ? FLASHDRV_STATUS_WARNING : FLASHDRV_STATUS_SUCCESS;
        }
    }
    if(eeeramrdy)
    {
        FlashDrv_SetFlexRam(obj, true);
    }

    return ret;
}

FlashDrv_Status FlashDrv_Read1sAllBlock(FlashDrvType *obj)
{
    FlashDrv_Status ret = FLASHDRV_STATUS_SUCCESS;
    if(0U == FtfcReg_GetFstatCcif(obj->reg))
    {
        ret = FLASHDRV_STATUS_BUSY;
    }
    else
    {
        FlashDrv_ClearCommandState(obj);
        FtfcReg_SetFccob(obj->reg, 0, FLASHDRV_OPCMD_ALBLKRD1S);
        FtfcReg_SetFccob(obj->reg, 1, 0);

        ret = FlashDrv_CommandSequence(obj);
    }
    return ret;
}

FlashDrv_Status FlashDrv_ReadInfoRegion(FlashDrvType         *obj,
                                        FlashDrv_InfoRegion_t regionid,
                                        uint32_t              phraseid,
                                        uint8_t              *databuf)
{
    FlashDrv_Status ret = FLASHDRV_STATUS_SUCCESS;
    uint32_t        i   = 0;

    if(regionid <= FLASHDRV_INFORG1 && phraseid >= 256)
    {
        ret = FLASHDRV_STATUS_ERROR;
    }
    else if(regionid == FLASHDRV_INFORG2 && phraseid >= 128)
    {
        ret = FLASHDRV_STATUS_ERROR;
    }

    if(databuf == NULL)
    {
        ret = FLASHDRV_STATUS_ERROR;
    }

    if(ret == FLASHDRV_STATUS_SUCCESS)
    {
        if(0U == FtfcReg_GetFstatCcif(obj->reg))
        {
            ret = FLASHDRV_STATUS_BUSY;
        }
        else
        {
            FlashDrv_ClearCommandState(obj);
            FtfcReg_SetFccob(obj->reg, 0, FLASHDRV_OPCMD_RDINFORG);
            FtfcReg_SetFccob(obj->reg, 1, (uint8_t)phraseid);
            FtfcReg_SetFccob(obj->reg, 2, regionid);

            ret = FlashDrv_CommandSequence(obj);
        }
    }
    if(ret == FLASHDRV_STATUS_SUCCESS)
    {
        for(i = 0; i < FLASHDRV_PHRASE_SIZE; i++)
        {
            databuf[i] = FtfcReg_GetFccob(obj->reg, (uint8_t)(7 + i));
        }
    }
    ret |= (FtfcReg_GetFstatFtfcSecF(obj->reg) == 1) ? FLASHDRV_STATUS_WARNING : FLASHDRV_STATUS_SUCCESS;
    ret |= (FtfcReg_GetFstatFtfcDedF(obj->reg) == 1) ? FLASHDRV_STATUS_ERROR : FLASHDRV_STATUS_SUCCESS;
    return ret;
}

FlashDrv_Status FlashDrv_ProgramInfoRegion(FlashDrvType         *obj,
                                           FlashDrv_InfoRegion_t regionid,
                                           uint32_t              phraseid,
                                           uint8_t              *databuf)
{
    FlashDrv_Status ret = FLASHDRV_STATUS_SUCCESS;
    uint32_t        i   = 0;

    if(regionid <= FLASHDRV_INFORG1 && phraseid >= 256)
    {
        ret = FLASHDRV_STATUS_ERROR;
    }
    else if(regionid == FLASHDRV_INFORG2 && phraseid >= 128)
    {
        ret = FLASHDRV_STATUS_ERROR;
    }

    if(databuf == NULL)
    {
        ret = FLASHDRV_STATUS_ERROR;
    }

    if(ret == FLASHDRV_STATUS_SUCCESS)
    {
        if(0U == FtfcReg_GetFstatCcif(obj->reg))
        {
            ret = FLASHDRV_STATUS_BUSY;
        }
        else
        {
            FlashDrv_ClearCommandState(obj);
            FtfcReg_SetFccob(obj->reg, 0, FLASHDRV_OPCMD_PGMINFORG);
            FtfcReg_SetFccob(obj->reg, 1, (uint8_t)phraseid);
            FtfcReg_SetFccob(obj->reg, 2, regionid);

            for(i = 0; i < FLASHDRV_PHRASE_SIZE; i++)
            {
                FtfcReg_SetFccob(obj->reg, (uint8_t)(4 + i), databuf[i]);
            }

            ret = FlashDrv_CommandSequence(obj);
            ret |= ((FtfcReg_GetFstatFtfcSecF(obj->reg) | FtfcReg_GetFstatFtfcDedF(obj->reg)) == 1) ? FLASHDRV_STATUS_WARNING : FLASHDRV_STATUS_SUCCESS;
        }
    }

    return ret;
}

FlashDrv_Status FlashDrv_EraseAllBlock(FlashDrvType *obj)
{
    FlashDrv_Status ret = FLASHDRV_STATUS_SUCCESS;
    if(0U == FtfcReg_GetFstatCcif(obj->reg))
    {
        ret = FLASHDRV_STATUS_BUSY;
    }
    else
    {
        FlashDrv_ClearCommandState(obj);
        FtfcReg_SetFccob(obj->reg, 0, FLASHDRV_OPCMD_ALBLKERS);
        FtfcReg_SetFccob(obj->reg, 1, 0);

        ret = FlashDrv_CommandSequence(obj);
    }
    return ret;
}

FlashDrv_Status FlashDrv_EraseAllBlockUnsecure(FlashDrvType *obj)
{
    FlashDrv_Status ret = FLASHDRV_STATUS_SUCCESS;
    if(0U == FtfcReg_GetFstatCcif(obj->reg))
    {
        ret = FLASHDRV_STATUS_BUSY;
    }
    else
    {
        FlashDrv_ClearCommandState(obj);
        FtfcReg_SetFccob(obj->reg, 0, (uint8_t)FLASHDRV_OPCMD_ALBLKUERS);
        FtfcReg_SetFccob(obj->reg, 1, 0);

        ret = FlashDrv_CommandSequence(obj);
    }
    return ret;
}

FlashDrv_Status FlashDrv_EraseCseSector(FlashDrvType          *obj,
                                        FlashDrv_SectorErase_t erasetype)
{
    FlashDrv_Status ret  = FLASHDRV_STATUS_SUCCESS;
    uint32_t        dest = (uint32_t)FLASHDRV_KEYSECTOR_ADDR;

    dest = ALIGNED(dest, (uint32_t)8);

    FtfcReg_SetCseBk(obj->reg, 0x43534543);

    if(0U == FtfcReg_GetFstatCcif(obj->reg))
    {
        ret = FLASHDRV_STATUS_BUSY;
    }
    else
    {
        FlashDrv_ClearCommandState(obj);
        FtfcReg_SetFccob(obj->reg, 0, FLASHDRV_OPCMD_CSE_SCTERS);
        FtfcReg_SetFccob(obj->reg, 1, FCCOBADDRLOW(dest));
        FtfcReg_SetFccob(obj->reg, 2, FCCOBADDRMDLOW(dest));
        FtfcReg_SetFccob(obj->reg, 3, FCCOBADDRMDHIG(dest));
        FtfcReg_SetFccob(obj->reg, 4, FCCOBADDRHIG(dest));
        FtfcReg_SetFccob(obj->reg, 5, erasetype);

        ret = FlashDrv_CommandSequence(obj);
    }

    FtfcReg_SetCseBk(obj->reg, 0x0);

    return ret;
}

FlashDrv_Status FlashDrv_ProgramCseSection(FlashDrvType *obj,
                                           uint32_t     *destaddr,
                                           uint32_t      len)
{
    FlashDrv_Status ret  = FLASHDRV_STATUS_SUCCESS;
    uint32_t        dest = (uint32_t)destaddr;

    if(!IS_ALIGNED(dest, 16) || !IS_ALIGNED(len, 16))
    {
        ret = FLASHDRV_STATUS_ERROR;
    }
    if(ALIGNED(dest + len - 1, FLASHDRV_KEY_SECTOR_SIZE) > ALIGNED(dest, FLASHDRV_KEY_SECTOR_SIZE))
    {
        ret = FLASHDRV_STATUS_ERROR;
    }

    if((dest < (uint32_t)FLASHDRV_KEYSECTOR_ADDR) || (dest >= (uint32_t)(FLASHDRV_KEYSECTOR_ADDR + FLASHDRV_KEY_SECTOR_SIZE)))
    {
        ret = FLASHDRV_STATUS_ERROR;
    }
    FtfcReg_SetCseBk(obj->reg, 0x43534543);
    if(ret == FLASHDRV_STATUS_SUCCESS)
    {
        if(0U == FtfcReg_GetFstatCcif(obj->reg))
        {
            ret = FLASHDRV_STATUS_BUSY;
        }
        else
        {
            FlashDrv_ClearCommandState(obj);
            FtfcReg_SetFccob(obj->reg, 0, FLASHDRV_OPCMD_CSE_SCTPGM);
            FtfcReg_SetFccob(obj->reg, 1, FCCOBADDRLOW(dest));
            FtfcReg_SetFccob(obj->reg, 2, FCCOBADDRMDLOW(dest));
            FtfcReg_SetFccob(obj->reg, 3, FCCOBADDRMDHIG(dest));
            FtfcReg_SetFccob(obj->reg, 4, FCCOBADDRHIG(dest));
            FtfcReg_SetFccob(obj->reg, 5, (uint8_t)((len / FLASHDRV_PHRASE_SIZE) - 1));

            ret = FlashDrv_CommandSequence(obj);
            ret |= ((FtfcReg_GetFstatFtfcSecF(obj->reg) | FtfcReg_GetFstatFtfcDedF(obj->reg)) == 1) ? FLASHDRV_STATUS_WARNING : FLASHDRV_STATUS_SUCCESS;
        }
    }
    FtfcReg_SetCseBk(obj->reg, 0x0);
    return ret;
}

FlashDrv_Status FlashDrv_VerifyUserKey(FlashDrvType *obj, uint8_t *expdata)
{
    FlashDrv_Status ret = FLASHDRV_STATUS_SUCCESS;
    uint32_t        i   = 0;

    if(expdata == NULL)
    {
        ret = FLASHDRV_STATUS_ERROR;
    }

    if(ret == FLASHDRV_STATUS_SUCCESS)
    {
        if(0U == FtfcReg_GetFstatCcif(obj->reg))
        {
            ret = FLASHDRV_STATUS_BUSY;
        }
        else
        {
            FlashDrv_ClearCommandState(obj);
            FtfcReg_SetFccob(obj->reg, 0, FLASHDRV_OPCMD_VRFYKEY);

            for(i = 0; i < FLASHDRV_PHRASE_SIZE; i++)
            {
                FtfcReg_SetFccob(obj->reg, (uint8_t)(1 + i), expdata[i]);
            }
            ret = FlashDrv_CommandSequence(obj);
        }
    }
    return ret;
}

void FlashDrv_IrqHandler(FlashDrvType *obj)
{
    FtfcReg_SetFstatCcifClr(obj->reg, 1);
    if(obj->callback != NULL)
    {
        obj->callback();
    }
}

void FlashDrv_SetCmdDoneIrqEn(FlashDrvType *obj, bool en)
{
    FtfcReg_SetFcnfgCcifIE(obj->reg, en ? 1 : 0);
}

FlashDrv_Status FlashDrv_SetFlexRam(FlashDrvType *obj, bool eeeramen)
{
    FlashDrv_Status ret = FLASHDRV_STATUS_SUCCESS;

    if(0U == FtfcReg_GetFstatCcif(obj->reg))
    {
        ret = FLASHDRV_STATUS_BUSY;
    }
    else
    {
        FlashDrv_ClearCommandState(obj);
        FtfcReg_SetFccob(obj->reg, 0, FLASHDRV_OPCMD_SETFRAM);
        FtfcReg_SetFccob(obj->reg, 1, eeeramen ? 1 : 0);
        ret = FlashDrv_CommandSequence(obj);

        if(eeeramen && !FtfcReg_GetFstatEeeRamRdy(obj->reg))
        {
            ret |= FLASHDRV_STATUS_ERROR;
        }

        if(!eeeramen && !FtfcReg_GetFstatRamRdy(obj->reg))
        {
            ret |= FLASHDRV_STATUS_ERROR;
        }
        ret |= ((FtfcReg_GetFstatFtfcSecF(obj->reg) | FtfcReg_GetFstatFtfcDedF(obj->reg)) == 1) ? FLASHDRV_STATUS_WARNING : FLASHDRV_STATUS_SUCCESS;
        ret |= (FtfcReg_GetFstatEeeStpgErrF(obj->reg) == 1) ? FLASHDRV_STATUS_ERROR: FLASHDRV_STATUS_SUCCESS;
    }

    return ret;
}

FlashDrv_Status FlashDrv_UpdateEeeRam(FlashDrvType *obj, uint32_t offset, uint8_t *srcdata, uint32_t sz)
{
    FlashDrv_Status ret = FLASHDRV_STATUS_SUCCESS;

    uint8_t  *pdsteram8  = 0;
    uint16_t *pdsteram16 = 0;
    uint32_t *pdsteram32 = 0;
    uint8_t  *psrc8      = 0;
    uint16_t *psrc16     = 0;
    uint32_t *psrc32     = 0;
    uint32_t  i = 0, cnt = 0;

    if(!(obj->eeevld) || FtfcReg_GetFstatRamRdy(obj->reg) == 1 || FtfcReg_GetFstatEeeFlov(obj->reg) == 1 || FtfcReg_GetEfProtection(obj->reg) != 0x0)
    {
        ret = FLASHDRV_STATUS_ERROR;
    }

    if(offset + sz > FLASHDRV_FLEXRAM_SIZE || sz == 0)
    {
        ret = FLASHDRV_STATUS_ERROR;
    }

    if(ret != FLASHDRV_STATUS_SUCCESS)
    {
        return ret;
    }

    if(FtfcReg_GetFcnfgAutoGc(obj->reg) == 0)
    {
        FtfcReg_SetFcnfgAutoGc(obj->reg, 1);
    }
    pdsteram8 = (uint8_t *)(FLASHDRV_FLEXRAM_ADDR + offset);
    FlashDrv_ClearCommandState(obj);
    if(IS_ALIGNED(offset, (uint32_t)4) && IS_ALIGNED(sz, (uint32_t)4))
    {
        pdsteram32 = (uint32_t *)pdsteram8;
        psrc32      = (uint32_t *)srcdata;
        cnt          = sz / 4;
        for(i = 0; i < cnt; i++)
        {
            pdsteram32[i] = psrc32[i];
            while(0 == FtfcReg_GetFstatEeeRamRdy(obj->reg))
            {
            }
        }
    }
    else if(IS_ALIGNED(offset, (uint32_t)2) && IS_ALIGNED(sz, (uint32_t)2))
    {
        pdsteram16 = (uint16_t *)pdsteram8;
        psrc16      = (uint16_t *)srcdata;
        cnt          = sz / 2;
        for(i = 0; i < cnt; i++)
        {
            pdsteram16[i] = psrc16[i];
            while(0 == FtfcReg_GetFstatEeeRamRdy(obj->reg))
            {
            }
        }
    }
    else
    {
        psrc8 = (uint8_t *)srcdata;
        cnt    = sz;
        for(i = 0; i < cnt; i++)
        {
            pdsteram8[i] = psrc8[i];
            while(0 == FtfcReg_GetFstatEeeRamRdy(obj->reg))
            {
            }
        }
    }

    ret |= ((FtfcReg_GetFstatFtfcSecF(obj->reg) | FtfcReg_GetFstatFtfcDedF(obj->reg)) == 1) ? FLASHDRV_STATUS_WARNING : FLASHDRV_STATUS_SUCCESS;
    ret |= ((FtfcReg_GetFstatEeeFlov(obj->reg) | FtfcReg_GetFstatEeeStpgErrF(obj->reg)) == 1) ? FLASHDRV_STATUS_ERROR: FLASHDRV_STATUS_SUCCESS;
    return ret;
}

bool FlashDrv_GetEeeAutoGcEn(FlashDrvType *obj)
{
    bool eeegcen = false;

    eeegcen = (FtfcReg_GetFcnfgAutoGc(obj->reg) == 1);

    return eeegcen;
}

void FlashDrv_SetEeeAutoGcEn(FlashDrvType *obj, bool eeegcen)
{
    FtfcReg_SetFcnfgAutoGc(obj->reg, eeegcen ? 1 : 0);
}

bool FlashDrv_GetEeeEn(FlashDrvType *obj)
{
    bool eeeen = false;

    eeeen = (FtfcReg_GetFstatEeeVld(obj->reg) == 1);

    return eeeen;
}

bool FlashDrv_GetEeeRamRdy(FlashDrvType *obj)
{
    bool eeeramrdy = false;

    eeeramrdy = (FtfcReg_GetFstatEeeRamRdy(obj->reg) == 1);

    return eeeramrdy;
}

FlashDrv_Status FlashDrv_GetEeeRamProtection(FlashDrvType *obj, uint8_t *protectstatus)
{
    FlashDrv_Status ret = FLASHDRV_STATUS_SUCCESS;

    if(!(obj->eeevld))
    {
        ret = FLASHDRV_STATUS_UNSUPPORTED;
    }
    else
    {
        *protectstatus = FtfcReg_GetEfProtection(obj->reg);
    }

    return ret;
}

FlashDrv_Status FlashDrv_GetPFlashProtection(FlashDrvType *obj, uint32_t *protectstatus0, uint32_t *protectstatus1)
{
    FlashDrv_Status ret = FLASHDRV_STATUS_SUCCESS;

    *protectstatus0 = FtfcReg_GetPfProtection0(obj->reg);
    *protectstatus1 = FtfcReg_GetPfProtection1(obj->reg);

    return ret;
}

FlashDrv_Status FlashDrv_GetDFlashProtection(FlashDrvType *obj, uint16_t *protectstatus)
{
    FlashDrv_Status ret = FLASHDRV_STATUS_SUCCESS;

    *protectstatus = FtfcReg_GetDfProtection(obj->reg);

    return ret;
}

FlashDrv_Status FlashDrv_GetSecProtection(FlashDrvType *obj, uint8_t *protectstatus)
{
    FlashDrv_Status ret = FLASHDRV_STATUS_SUCCESS;

    *protectstatus = FtfcReg_GetSecProtection(obj->reg);

    return ret;
}

FlashDrv_Status FlashDrv_SetSecProtection(FlashDrvType *obj, uint8_t prctval)
{
    FlashDrv_Status ret = FLASHDRV_STATUS_SUCCESS;
    uint8_t prctvalrl =0;
    FtfcReg_SetSecProtection(obj->reg, prctval);
    prctvalrl = FtfcReg_GetSecProtection(obj->reg);
    ret = ((prctval ^ prctvalrl) == 0) ? FLASHDRV_STATUS_SUCCESS : FLASHDRV_STATUS_WARNING;

    return ret;
}

FlashDrv_Status FlashDrv_SetEeeRamProtection(FlashDrvType *obj, uint8_t prctval)
{
    FlashDrv_Status ret = FLASHDRV_STATUS_SUCCESS;
    uint8_t prctvalrl =0;
    if(!(obj->eeevld))
    {
        ret = FLASHDRV_STATUS_UNSUPPORTED;
    }
    else
    {
        FtfcReg_SetEfProtection(obj->reg, prctval);
        prctvalrl = FtfcReg_GetEfProtection(obj->reg);
        ret = ((prctval ^ prctvalrl) == 0) ? FLASHDRV_STATUS_SUCCESS : FLASHDRV_STATUS_WARNING;
    }

    return ret;
}

FlashDrv_Status FlashDrv_SetPFlashProtection(FlashDrvType *obj, uint32_t prctval0, uint32_t prctval1)
{
    FlashDrv_Status ret = FLASHDRV_STATUS_SUCCESS;
    uint32_t prctvalrl =0;
    FtfcReg_SetPfProtection0(obj->reg, prctval0);
    FtfcReg_SetPfProtection1(obj->reg, prctval1);

    prctvalrl = FtfcReg_GetPfProtection0(obj->reg);
    ret = ((prctval0 ^ prctvalrl) == 0) ? FLASHDRV_STATUS_SUCCESS : FLASHDRV_STATUS_WARNING;
    prctvalrl = FtfcReg_GetPfProtection1(obj->reg);
    ret |= ((prctval1 ^ prctvalrl) == 0) ? FLASHDRV_STATUS_SUCCESS : FLASHDRV_STATUS_WARNING;

    return ret;
}

FlashDrv_Status FlashDrv_SetDFlashProtection(FlashDrvType *obj, uint16_t prctval)
{
    FlashDrv_Status ret = FLASHDRV_STATUS_SUCCESS;
    uint32_t prctvalrl =0;

    FtfcReg_SetDfProtection(obj->reg, prctval);
    prctvalrl = FtfcReg_GetDfProtection(obj->reg);
    ret = ((prctval ^ prctvalrl) == 0) ? FLASHDRV_STATUS_SUCCESS : FLASHDRV_STATUS_WARNING;

    return ret;
}
