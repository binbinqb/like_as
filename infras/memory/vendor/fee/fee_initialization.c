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
#include "fee_initialization.h"
#include "fee_extra.h"
#include "fee_types.h"
#include "fee_trace.h"

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
 * the static
 ******************************************************************************/
static void Fee_InitializationCheckSector(const FeeType *obj);
static void Fee_InitializationSector(const FeeType *obj);
static void Fee_InitializationFindActiveSector(const FeeType *obj);
static void Fee_InitializationGcRepairSector(const FeeType *obj);
static void Fee_InitializationFirstSector(const FeeType *obj);
static void Fee_InitializationUnEraseSector(const FeeType *obj);
static void Fee_InitializationEraseSector(const FeeType *obj);
static void Fee_InitializationFinish(const FeeType *obj);

/*******************************************************************************
 * the functions
 ******************************************************************************/
void Fee_EntryInitialization(const FeeType *obj)
{
    obj->runtime->initializationFsm = FEE_INITIALIZATION_SECTOR;
}

bool Fee_InitializationJob(const FeeType *obj)
{
    bool ret = false;
    switch(obj->runtime->initializationFsm)
    {
    case FEE_INITIALIZATION_SECTOR:
        {
            Fee_InitializationSector(obj);
            break;
        }
    case FEE_INITIALIZATION_CHECK_SECTOR:
        {
            Fee_InitializationCheckSector(obj);
            break;
        }
    case FEE_INITIALIZATION_FIND_ACTIVE_SECTOR:
        {
            Fee_InitializationFindActiveSector(obj);
            break;
        }
    case FEE_INITIALIZATION_ERASE_SECTOR:
        {
            Fee_InitializationEraseSector(obj);
            break;
        }
    case FEE_INITIALIZATION_UNINITIALIZATION_ERASE_SECTOR:
        {
            Fee_InitializationUnEraseSector(obj);
            break;
        }
    case FEE_INITIALIZATION_UNINITIALIZATION:
        {
            Fee_InitializationFirstSector(obj);
            break;
        }
    case FEE_INITIALIZATION_GC_REPAIR_SECTOR:
        {
            Fee_InitializationGcRepairSector(obj);
            break;
        }
    case FEE_INITIALIZATION_FINISH:
        {
            Fee_InitializationFinish(obj);
            ret = true;
            break;
        }
    default:
        {
            FEE_DBG_INITIALIZATION_FSM_ERROR_ENTRY();
            break;
        }
    }
    return ret;
}

static void Fee_InitializationCheckSector(const FeeType *obj)
{
    int sectorIdx;

    for(sectorIdx = 0; sectorIdx < obj->sector->sectorSize; sectorIdx++)
    {
        Fee_SectorCheckErase(&obj->sector->sectors[sectorIdx], obj->flsMethod);
        if (FEE_SECTOR_ERASE != Fee_SectorGetStatus(&obj->sector->sectors[sectorIdx]))
        {
            Fee_CheckSectorIsValid(&obj->sector->sectors[sectorIdx], obj->flsMethod, (uint8_t *)obj->buff);
        }
    }

     /* Initialize the state machine to the next state */
    obj->runtime->initializationFsm = FEE_INITIALIZATION_FIND_ACTIVE_SECTOR;
}

static void Fee_InitializationSector(const FeeType *obj)
{
    /* Initialize sector runtime data. */
    Fee_SectorsInit(obj->sector, obj->flsMethod, obj->buff);

    /* Initialize the state machine to the default state. */
    obj->runtime->initializationFsm = FEE_INITIALIZATION_CHECK_SECTOR;
}

static void Fee_InitializationFindActiveSector(const FeeType *obj)
{
    const Fee_SectorConfigType *activeSector;
    const Fee_SectorConfigType *gcSector;

    /* Initialize the state machine. */
    obj->runtime->initializationFsm = FEE_INITIALIZATION_UNINITIALIZATION;

    /* The activity sector value is NULL. */
    obj->runtime->activeSector = NULL;

    /* Find the active sector. */
    activeSector = Fee_SearchValidSector(obj->sector);

    /* Check if the active sector is found. */
    if(activeSector != NULL)
    {
        obj->runtime->activeSector      = activeSector;
        obj->runtime->initializationFsm = FEE_INITIALIZATION_FINISH;
    }

    /* The backup sector value is NULL. */
    obj->runtime->gcRuntime->backupSector = NULL;

    /* Find the backup sector. */
    gcSector = Fee_SearchGcSector(obj->sector);

    /* Check if the backup sector is found. */
    if(gcSector != NULL)
    {
        /* Check whether the backup section is in the transportation completion state. */
        /* If not, check whether it is in the state before the transportation is completed. */
        if(FEE_SECTOR_END_HAND_FINISH == gcSector->info->status)
        {
            /* Execute the sector repair program. */
            obj->runtime->gcRuntime->backupSector = gcSector;
            obj->runtime->initializationFsm       = FEE_INITIALIZATION_GC_REPAIR_SECTOR;
        }
        else if(FEE_SECTOR_END_HAND_FINISH > gcSector->info->status)
        {
            /* Check whether there is an active sector. */
            if(NULL == obj->runtime->activeSector)
            {
                /* Execute the reinitialization of the sector program. */
                obj->runtime->initializationFsm = FEE_INITIALIZATION_UNINITIALIZATION;
            }
        }
    }
}

static void Fee_InitializationGcRepairSector(const FeeType *obj)
{
    /* If there is no active sector, flip the backup sector to the active state. */
    if(NULL == obj->runtime->activeSector)
    {
        obj->runtime->activeSector = obj->runtime->gcRuntime->backupSector;
    }
    obj->runtime->initializationFsm = FEE_INITIALIZATION_FINISH;
}

static void Fee_InitializationFirstSector(const FeeType *obj)
{
    const Fee_SectorConfigType *activeSector;

    /* Get the first sector. */
    activeSector = Fee_GetFirstSector(obj->sector);

    /* Check whether the active sector is found. */
    if(activeSector != NULL)
    {
        /* Initialize the active sector. */
        obj->runtime->activeSector = activeSector;
        Fee_InitEraseSector(obj->runtime->activeSector);
        obj->runtime->initializationFsm = FEE_INITIALIZATION_UNINITIALIZATION_ERASE_SECTOR;
    }
    else
    {
        obj->runtime->initializationFsm = FEE_INITIALIZATION_ERROR;
    }
}

static void Fee_InitializationUnEraseSector(const FeeType *obj)
{
    /* Erase active sector. */
    Fee_EraseSector(obj->runtime->activeSector, obj->flsMethod);

    /* Check whether the active sector is in the error state. */
    /* If not, check whether it is in the erase state. */
    if(FEE_SECTOR_NOT_ERROR != obj->runtime->activeSector->info->errors)
    {
        obj->runtime->initializationFsm = FEE_INITIALIZATION_ERROR;
    }
    else if(FEE_SECTOR_ERASE == obj->runtime->activeSector->info->status)
    {
        /* Initialize the active sector. */
        obj->runtime->activeSector->info->status = FEE_SECTOR_UNUSED;
        Fee_SectorWriteHeadInfo(obj->runtime->activeSector, obj->flsMethod, obj->buff);
        obj->runtime->initializationFsm = FEE_INITIALIZATION_FINISH;
    }
}

static void Fee_InitializationEraseSector(const FeeType *obj)
{
    /* Erase active sector. */
    Fee_EraseSector(obj->runtime->activeSector, obj->flsMethod);

    /* Check whether the active sector is in the error state. */
    /* If not, check whether it is in the erase state. */
    if(FEE_SECTOR_NOT_ERROR != obj->runtime->activeSector->info->errors)
    {
        obj->runtime->initializationFsm = FEE_INITIALIZATION_ERROR;
    }
    else if(FEE_SECTOR_ERASE == obj->runtime->activeSector->info->status)
    {
        obj->runtime->initializationFsm = FEE_INITIALIZATION_FINISH;
    }
}

static void Fee_InitializationFinish(const FeeType *obj)
{
    /* Check whether the active sector is NULL. */
    if(obj->runtime->activeSector != NULL)
    {
        /* Set the state of the active sector to the actvie state. */
        obj->runtime->activeSector->info->status = FEE_SECTOR_ACTIVE;
    }
    else
    {
        /* An irretrievable mistake. */
        FEE_DBG_STORAGE_ERROR_ENTRY();
    }
}
