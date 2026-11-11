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
#include "fee.h"
#include "fee_initialization.h"
#include "fee_trace.h"

/*******************************************************************************
 * the defines
 ******************************************************************************/

/*! \brief Macro for the start address of the block data
 */
#define FEE_BLOCK_DATA_START_ADDR (((Fee_AddressType)obj->runtime->activeSector->startAddr) + FEE_SECTOR_HEAD_SIZE)

/*! \brief Macro for the end address of the block data
 */
#define FEE_BLOCK_DATA_ADDR       (obj->runtime->activeSector->endAddr)

/*! \brief Macro for the start address of the block info
 */
#define FEE_BLOCK_INFO_START_ADDR (((Fee_AddressType)obj->runtime->activeSector->endAddr) - FEE_SECTOR_HEAD_SIZE - FEE_BLOCK_HEAD_INFO_SIZE)

/*! \brief Macro for the end address of the block info
 */
#define FEE_BLOCK_INFO_END_ADDR   (obj->runtime->activeSector->startAddr + FEE_SECTOR_HEAD_SIZE)

/*! \brief Get a macro for a block object
 */
#define Fee_GetBlock(obj, idx)    (&obj->blocks[idx])

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the static
 ******************************************************************************/
static bool                        Fee_OnEntryRetrievalJob(const FeeType *obj);
static void                        Fee_ExitRetrievalJob(const FeeType *obj);
static bool                        Fee_RetrievalActiveSector(const FeeType *obj);
static bool                        Fee_ReadJob(const FeeType *obj);
static bool                        Fee_WriteJob(const FeeType *obj);
static void                        FEE_OnEntryGcJob(const FeeType *obj);
static bool                        Fee_GcJob(const FeeType *obj);
static void                        Fee_OnEntryGcCopyJob(const FeeType *obj);
static bool                        Fee_GcCopyJob(const FeeType *obj);
static bool                        Fee_GcInitBlockInfo(const FeeType *obj, const Fee_BlockType *block);
static bool                        Fee_GcWriteBlockToNewSector(const FeeType *obj);
static const Fee_SectorConfigType *Fee_FoundBackupSector(const FeeType *obj);
static uint16_t                    Fee_SearchBlock(const Fee_SectorType *obj, uint16_t blockNumber);

/*******************************************************************************
 * the functions
 ******************************************************************************/

void Fee_Configure(const FeeType *obj)
{
    /* Initialize system job request. */
    Fee_InitJob(obj->runtime->jobs->sysJob);

    /* Initialize user job request. */
    Fee_InitJob(obj->runtime->jobs->userJob);

    /* Initialize to reject request status. */
    obj->runtime->jobs->accept = false;

    /* Initialize the status of the main function. */
    obj->runtime->mainFunFsm = FEE_MAIN_FUN_FSM_INITIALIZATION;

    Fee_EntryInitialization(obj);
}

void Fee_MainFunction(const FeeType *obj)
{
    switch(obj->runtime->mainFunFsm)
    {
    case FEE_MAIN_FUN_FSM_INITIALIZATION:
        {
            if(Fee_InitializationJob(obj))
            {
                if(Fee_OnEntryRetrievalJob(obj))
                {
                    obj->runtime->mainFunFsm = FEE_MAIN_FUN_FSM_RETRIEVAL;
                }
                else
                {
                    obj->runtime->mainFunFsm = FEE_MAIN_FUN_FSM_ERROR;
                }
            }
            break;
        }
    case FEE_MAIN_FUN_FSM_RETRIEVAL:
        {
            if(Fee_RetrievalActiveSector(obj))
            {
                Fee_ExitRetrievalJob(obj);
                Fee_EnableJobs(obj->runtime->jobs);
                obj->runtime->mainFunFsm = FEE_MAIN_FUN_FSM_IDLE;
            }
            break;
        }
    case FEE_MAIN_FUN_FSM_IDLE:
        {
            if(Fee_GetSysJob(obj->runtime->jobs, obj->runtime->job))
            {
                if(obj->runtime->job->op == FEE_JOB_OP_GC)
                {
                    FEE_OnEntryGcJob(obj);
                }
            }
            else if(Fee_GetUserJob(obj->runtime->jobs, obj->runtime->job))
            {
                if(obj->runtime->job->op == FEE_JOB_OP_READ)
                {
                    obj->runtime->mainFunFsm = FEE_MAIN_FUN_FSM_READ;
                }
                else if(obj->runtime->job->op == FEE_JOB_OP_WRITE)
                {
                    obj->runtime->mainFunFsm = FEE_MAIN_FUN_FSM_WRITE;
                }
                else
                {
                    /* Do nothing. */
                }
            }
            break;
        }
    case FEE_MAIN_FUN_FSM_READ:
        {
            /* polyspace-begin DEFECT:USELESS_IF [ Not a defect: Medium ] "Ensure consistent code style between top and bottom." */
            if(Fee_ReadJob(obj))
            {
                /* Clear current request job. */
                Fee_InitJob(obj->runtime->jobs->userJob);
                obj->runtime->mainFunFsm = FEE_MAIN_FUN_FSM_IDLE;
            }
            /* polyspace-end DEFECT:USELESS_IF [ Not a defect: Medium ] "Ensure consistent code style between top and bottom." */
            break;
        }
    case FEE_MAIN_FUN_FSM_WRITE:
        {
            /* polyspace-begin DEFECT:USELESS_IF [ Not a defect: Medium ] "Ensure consistent code style between top and bottom." */
            if(Fee_WriteJob(obj))
            {
                /* Clear current request job. */
                Fee_InitJob(obj->runtime->jobs->userJob);
                obj->runtime->mainFunFsm = FEE_MAIN_FUN_FSM_IDLE;
            }
            /* polyspace-end DEFECT:USELESS_IF [ Not a defect: Medium ] "Ensure consistent code style between top and bottom." */
            break;
        }
    case FEE_MAIN_FUN_FSM_GC:
        {
            if(Fee_GcJob(obj))
            {
                /* Clear current request job. */
                Fee_InitJob(obj->runtime->jobs->sysJob);

                if(FEE_GC_ERROR == obj->runtime->gcRuntime->gcFsm)
                {
                    Fee_EntryInitialization(obj);
                    obj->runtime->mainFunFsm = FEE_MAIN_FUN_FSM_INITIALIZATION;
                }
                else if(FEE_GC_FINISH == obj->runtime->gcRuntime->gcFsm)
                {
                    obj->runtime->mainFunFsm = FEE_MAIN_FUN_FSM_IDLE;
                }
            }
            break;
        }
    default:
        {
            FEE_DBG_MAIN_FSM_ERROR_ENTRY();
            break;
        }
    }
}

Fee_ReturnType Fee_Read(const FeeType *obj, uint16_t blockNumber, uint16_t blockOffset, uint8_t *dataBuffer, NotificationPtrType notificationPtr)
{
    Fee_ReturnType          ret = FEE_RETURN_NOT_OK;
    Fee_JobControlBlockType config;
    uint16_t                blockIdx;

    /* Find the index of the block. */
    blockIdx = Fee_SearchBlock(obj->sector, blockNumber);

    /* Check whether the index is invalid. */
    if(FEE_INVALID_BLOCK_INDEX != blockIdx)
    {
        /* Initialize read request configuration. */
        config.blockIdx        = blockIdx;
        config.blockOffset     = blockOffset;
        config.dataBuffPtr     = dataBuffer;
        config.notificationPtr = notificationPtr;
        config.op              = FEE_JOB_OP_READ;
        config.lock            = FEE_JOB_LOCK;

        /* Check if there is already a request. */
        if(false == Fee_QueryUserJobIsLock(obj->runtime->jobs))
        {
            /* Configuration Request. */
            if(Fee_SetUserJob(obj->runtime->jobs, &config))
            {
                /* Configure job Status. */
                obj->runtime->jobResult = FEE_JOB_RESULT_PENDING;
                ret                     = FEE_RETURN_OK;
            }
        }
    }
    else
    {
        /* Configure job Status. */
        obj->runtime->jobResult = FEE_JOB_RESULT_BL_INVALID;
    }
    return ret;
}

Fee_ReturnType Fee_Write(const FeeType *obj, uint16_t blockNumber, uint8_t *dataBuffer, NotificationPtrType notificationPtr)
{
    Fee_ReturnType          ret = FEE_RETURN_NOT_OK;
    Fee_JobControlBlockType config;
    uint16_t                blockIdx;

    /* Find the index of the block. */
    blockIdx = Fee_SearchBlock(obj->sector, blockNumber);

    /* Check whether the index is invalid. */
    if(0xFFFF != blockIdx)
    {
        /* Check whether the remaining space is sufficient for storage. */
        if(Fee_CheckRemSpace(obj->runtime->activeSector, Fee_GetBlock(obj->sector, blockIdx)))
        {
            /* Initialize write request configuration. */
            config.blockIdx        = blockIdx;
            config.dataBuffPtr     = dataBuffer;
            config.notificationPtr = notificationPtr;
            config.op              = FEE_JOB_OP_WRITE;
            config.lock            = FEE_JOB_LOCK;

            /* Check if there is already a request. */
            if(false == Fee_QueryUserJobIsLock(obj->runtime->jobs))
            {
                /* Configuration User Request. */
                if(Fee_SetUserJob(obj->runtime->jobs, &config))
                {
                    /* Configure job Status. */
                    obj->runtime->jobResult = FEE_JOB_RESULT_PENDING;
                    ret                     = FEE_RETURN_OK;
                }
            }
        }
        else
        {
            /* Configure Request Recycling. */
            config.op = FEE_JOB_OP_GC;

            /* Check if there are already system requests. */
            if(false == Fee_QuerySysJobIsLock(obj->runtime->jobs))
            {
                /* Configuration System Request. */
                Fee_SetSysJob(obj->runtime->jobs, &config);
            }
        }
    }
    else
    {
        obj->runtime->jobResult = FEE_JOB_RESULT_BL_INVALID;
    }

    return ret;
}

Fee_JobResultType Fee_GetJobResult(const FeeType *obj)
{
    return obj->runtime->jobResult;
}

Fee_StatusType Fee_GetStatus(const FeeType *obj)
{
    Fee_StatusType ret = FEE_STATUS_UNKNOW;

    if(FEE_MAIN_FUN_FSM_GC == obj->runtime->mainFunFsm)
    {
        ret = FEE_STATUS_GC;
    }
    else if(FEE_MAIN_FUN_FSM_READ == obj->runtime->mainFunFsm)
    {
        ret = FEE_STATUS_READ;
    }
    else if(FEE_MAIN_FUN_FSM_WRITE == obj->runtime->mainFunFsm)
    {
        ret = FEE_STATUS_WRITE;
    }
    else if(FEE_MAIN_FUN_FSM_IDLE == obj->runtime->mainFunFsm)
    {
        ret = FEE_STATUS_IDLE;
    }
    else if(FEE_MAIN_FUN_FSM_ERROR == obj->runtime->mainFunFsm)
    {
        ret = FEE_STATUS_ERROR;
    }
    else if(FEE_MAIN_FUN_FSM_INITIALIZATION == obj->runtime->mainFunFsm)
	{
    	ret = FEE_STATUS_UNINIT;
	}
    else if(FEE_MAIN_FUN_FSM_RETRIEVAL == obj->runtime->mainFunFsm)
    {
    	ret = FEE_STATUS_UNINIT;
    }
    else
    {
        ret = FEE_STATUS_UNKNOW;
    }

    return ret;
}

void Fee_GetVersionInfo(Fee_VersionInfoType *versionInfoPtr)
{
    if(NULL != versionInfoPtr)
    {
        versionInfoPtr->sw_major_version = FEE_SW_MAJOR_VERSION;
        versionInfoPtr->sw_minor_version = FEE_SW_MINOR_VERSION;
        versionInfoPtr->sw_patch_version = FEE_SW_PATCH_VERSION;
    }
}

static bool Fee_OnEntryRetrievalJob(const FeeType *obj)
{
    bool ret = false;
    int  blockIdx;

    if(NULL != obj)
    {
        if(NULL != obj->runtime->activeSector)
        {
            /* Initialize the block index table. */
            for(blockIdx = 0; blockIdx < obj->sector->blockSize; blockIdx++)
            {
                Fee_BlockSetPhyAddr(obj->sector->blocks[blockIdx].info, NULL);
            }
            
            /* The variable search points to the bottom of the sector. */
            obj->runtime->activeSector->info->searchAddr = FEE_BLOCK_INFO_START_ADDR;
            /* Prepare to find the starting address of the remaining space. */
            obj->runtime->activeSector->info->remAddr = FEE_BLOCK_DATA_START_ADDR;
            /* Return true. */
            ret = true;
        }
    }
    return ret;
}

static void Fee_ExitRetrievalJob(const FeeType *obj)
{
    /* Find the starting address of the remaining space. */
    for(; FLS_STATE_NOT_WRITABLE == obj->flsMethod->isWriteable(obj->runtime->activeSector->info->remAddr, Fee_BLOCK_WRITE_ALIGNED_SIZE); obj->runtime->activeSector->info->remAddr += Fee_BLOCK_WRITE_ALIGNED_SIZE)
    {
    }
}

static bool Fee_RetrievalActiveSector(const FeeType *obj)
{
    bool                 ret   = false;
    const Fee_BlockType *block = NULL;

    /* Check the range of index addresses. */
    if(obj->runtime->activeSector->info->searchAddr > FEE_BLOCK_INFO_END_ADDR)
    {
        /* Check whether the flash space is not writable. */
        if(FLS_STATE_NOT_WRITABLE == obj->flsMethod->isWriteable(obj->runtime->activeSector->info->searchAddr, FEE_BLOCK_HEAD_INFO_SIZE))
        {
            /* Read flash data. */
            if(FLS_STATE_OK == obj->flsMethod->read(obj->runtime->activeSector->info->searchAddr, (uint8_t *)obj->buff, FEE_BLOCK_HEAD_INFO_SIZE))
            {
                /* Analyze the data and find the described block configuration. */
                block = Fee_MatchBlock(obj->sector, obj->flsMethod, (uint8_t *)obj->buff);

                /* If the block points to a null pointer, no matching block was found. */
                if(NULL != block)
                {
                    /* Create a block index table. */
                    Fee_BlockSetPhyAddr(block->info, Fee_GetBlockHeadPhyAddr((uint8_t *)obj->buff));
                    obj->runtime->activeSector->info->remAddr = block->info->phyAddr + FEE_BLOCKSIZE(block->cfg);
                }
            }

            /* Point to the next block info. */
            obj->runtime->activeSector->info->searchAddr -= FEE_BLOCK_HEAD_INFO_SIZE;
        }
        else
        {
            /* If a writable flash address is found, the traversal is considered complete. */
            obj->runtime->activeSector->info->headInfoAddr = obj->runtime->activeSector->info->searchAddr;
            ret                                            = true;
        }
    }
    else
    {
        FEE_DBG_STORAGE_ERROR_ENTRY();
    }

    return ret;
}

static bool Fee_ReadJob(const FeeType *obj)
{
    bool                 ret             = true;
    Fee_NotificationType notificationRet = FEE_JOBERRORNOTIFICATION;
    const Fee_BlockType *block;

    /* Reset job processing status. */
    obj->runtime->jobResult = FEE_JOB_RESULT_NOT_OK;

    /* Get block configuration. */
    block = Fee_GetBlock(obj->sector, obj->runtime->job->blockIdx);

    /* Check whether the block configuration is valid. */
    if(block != NULL)
    {
        /* Check whether the block has been assigned a flash address. */
        if(NULL != block->info->phyAddr)
        {
            /* Check the validity of the data stored on the flash by the block. */
            if(FLS_STATE_OK == obj->flsMethod->read(block->info->phyAddr, obj->runtime->job->dataBuffPtr, FEE_BLOCKSIZE(block->cfg)))
            {
                obj->runtime->jobResult = FEE_JOB_RESULT_OK;
                notificationRet         = FEE_JOBENDNOTIFICATION;
            }
            else
            {
                obj->runtime->jobResult = FEE_JOB_RESULT_BL_INCONSISTENT;
            }
        }
        else
        {
            obj->runtime->jobResult = FEE_JOB_RESULT_BL_INVALID;
        }
    }

    /* Callback notification function. */
    if(obj->runtime->job->notificationPtr != NULL)
    {
        obj->runtime->job->notificationPtr(notificationRet);
    }

    return ret;
}

static bool Fee_WriteJob(const FeeType *obj)
{
    bool                 ret             = true;
    Fee_NotificationType notificationRet = FEE_JOBERRORNOTIFICATION;
    const Fee_BlockType *block;
    uint16_t             blocksize;
    Fee_AddressType      tempPhyAddr;

    /* Reset job processing status. */
    obj->runtime->jobResult = FEE_JOB_RESULT_NOT_OK;

    block = Fee_GetBlock(obj->sector, obj->runtime->job->blockIdx);

    if(NULL != block)
    {
        blocksize = FEE_BLOCKSIZE(block->cfg);

        /* First write the block data to the flash, ensure safe writing, and then write the block header information. */
        if(FLS_STATE_OK == obj->flsMethod->write(obj->runtime->activeSector->info->remAddr, obj->runtime->job->dataBuffPtr, blocksize))
        {
            tempPhyAddr          = block->info->phyAddr;
            Fee_BlockSetPhyAddr(block->info, obj->runtime->activeSector->info->remAddr);
            Fee_WriteBlockHeadInfo(block, obj->flsMethod->crc8, (uint8_t *)obj->buff);
            if(FLS_STATE_OK == obj->flsMethod->write(obj->runtime->activeSector->info->headInfoAddr, obj->buff, FEE_BLOCK_HEAD_INFO_SIZE))
            {
                obj->runtime->jobResult = FEE_JOB_RESULT_OK;
                notificationRet         = FEE_JOBENDNOTIFICATION;
            }
            else
            {
                block->info->phyAddr = tempPhyAddr;
            }
            obj->runtime->activeSector->info->headInfoAddr -= FEE_BLOCK_HEAD_INFO_SIZE;
        }
        else
        {
            (void)obj->runtime->activeSector->info->remAddr;
        }
        obj->runtime->activeSector->info->remAddr += blocksize;
    }
    else
    {
        obj->runtime->jobResult = FEE_JOB_RESULT_BL_INVALID;
        notificationRet         = FEE_JOBENDNOTIFICATION;
    }

    /* Callback notification function. */
    if(obj->runtime->job->notificationPtr != NULL)
    {
        obj->runtime->job->notificationPtr(notificationRet);
    }
    return ret;
}

static void FEE_OnEntryGcJob(const FeeType *obj)
{
    obj->runtime->gcRuntime->state = FEE_GC_STATE_NO_ERROR;
    obj->runtime->gcRuntime->gcFsm = FEE_GC_INIT;
    obj->runtime->mainFunFsm       = FEE_MAIN_FUN_FSM_GC;
}

static bool Fee_GcJob(const FeeType *obj)
{
    bool ret = false;

    switch(obj->runtime->gcRuntime->gcFsm)
    {
    case FEE_GC_INIT:
        {
            /* Find backup sector. */
            obj->runtime->gcRuntime->backupSector = Fee_FoundBackupSector(obj);

            if(obj->runtime->gcRuntime->backupSector != NULL)
            {
                /* Information about initializing the backup sector. */
                Fee_SectorInitInfo(obj->runtime->gcRuntime->backupSector);

                /* Check whether all sectors have been erased. */
                if(false == Fee_SectorIsErase(obj->runtime->gcRuntime->backupSector, obj->flsMethod))
                {
                    /* Execute the sector erase action. */
                    obj->runtime->gcRuntime->gcFsm = FEE_GC_ERASE_BACKUPSECTOR;
                    Fee_InitEraseSector(obj->runtime->gcRuntime->backupSector);
                }
                else
                {
                    obj->runtime->gcRuntime->backupSector->info->status = FEE_SECTOR_UNUSED;
                    obj->runtime->gcRuntime->gcFsm                      = FEE_GC_START;
                }
            }
            else
            {
                /* If the backup sector is not found, it is considered a major configuration defect. */
                obj->runtime->gcRuntime->state = FEE_GC_STATE_NOT_FOUND_BACKUPSECTOR;
                obj->runtime->gcRuntime->gcFsm = FEE_GC_ERROR;
            }
            break;
        }
    case FEE_GC_ERASE_BACKUPSECTOR:
        {
            /* Erase the backed up sector. */
            Fee_EraseSector(obj->runtime->gcRuntime->backupSector, obj->flsMethod);
            if((FEE_SECTOR_NOT_ERROR == obj->runtime->gcRuntime->backupSector->info->errors) && (FEE_SECTOR_ERASE == obj->runtime->gcRuntime->backupSector->info->status))
            {
                obj->runtime->gcRuntime->gcFsm = FEE_GC_START;
            }
            else if(FEE_SECTOR_NOT_ERROR != obj->runtime->gcRuntime->backupSector->info->errors)
            {
                obj->runtime->gcRuntime->state = FEE_GC_STATE_ERASE_BACKUP_SECTOR_ERROR;
                obj->runtime->gcRuntime->gcFsm = FEE_GC_ERROR;
            }
            break;
        }
    case FEE_GC_START:
        {
            /* Write initialization completion flag bit. */
            Fee_SectorWriteInitMark(obj->runtime->gcRuntime->backupSector, obj->flsMethod, obj->buff);

            if(FEE_SECTOR_NOT_ERROR != obj->runtime->gcRuntime->backupSector->info->errors)
            {
                obj->runtime->gcRuntime->state = FEE_GC_STATE_WRITE_INIT_MARK_ERROR;
                obj->runtime->gcRuntime->gcFsm = FEE_GC_ERROR;
                FEE_DBG_GC_WRITE_INIT_MARK_ERROR_ENTRY();
            }
            else
            {
                Fee_OnEntryGcCopyJob(obj);
                obj->runtime->gcRuntime->gcFsm = FEE_GC_COPY;
            }
            break;
        }
    case FEE_GC_COPY:
        {
            /* Handling data job. */
            if(Fee_GcCopyJob(obj))
            {
                /* Erase the active sector after data GC is completed. */
                Fee_InitEraseSector(obj->runtime->activeSector);
                obj->runtime->activeSector->info->status = FEE_SECTOR_UNUSED;
                obj->runtime->gcRuntime->gcFsm           = FEE_GC_ERASE_ACTIVESECTOR;
            }
            if(FEE_GC_COPY_ERROR == obj->runtime->gcRuntime->copyFsm)
            {
                obj->runtime->gcRuntime->state = FEE_GC_STATE_COPY_ERROR;
                obj->runtime->gcRuntime->gcFsm = FEE_GC_ERROR;
            }
            else if(FEE_SECTOR_NOT_ERROR != obj->runtime->gcRuntime->backupSector->info->errors)
            {
                obj->runtime->gcRuntime->state = FEE_GC_STATE_COPY_ERROR;
                obj->runtime->gcRuntime->gcFsm = FEE_GC_ERROR;
            }
            else if(FEE_GC_STATE_NO_ERROR != obj->runtime->gcRuntime->state)
            {
                obj->runtime->gcRuntime->gcFsm = FEE_GC_ERROR;
            }
            break;
        }
    case FEE_GC_ERASE_ACTIVESECTOR:
        {
            /* Erase the active sector after data transfer is completed. */
            Fee_EraseSector(obj->runtime->activeSector, obj->flsMethod);

            if((FEE_SECTOR_NOT_ERROR == obj->runtime->activeSector->info->errors) && (FEE_SECTOR_ERASE == obj->runtime->activeSector->info->status))
            {
                obj->runtime->gcRuntime->gcFsm = FEE_GC_FINISH;
            }
            else if(FEE_SECTOR_NOT_ERROR != obj->runtime->activeSector->info->errors)
            {
                obj->runtime->gcRuntime->state = FEE_GC_STATE_ERASE_ACTIVE_SECTOR_ERROR;
                obj->runtime->gcRuntime->gcFsm = FEE_GC_ERROR;
                FEE_DBG_GC_ERASE_ACTIVE_SECTOR_ERROR_ENTRY();
            }
            break;
        }
    case FEE_GC_FINISH:
        {
            /* Write the flag bit of the active sector to the sector info. */
            Fee_SectorWriteEnableSectorMark(obj->runtime->gcRuntime->backupSector, obj->flsMethod, obj->buff);
            Fee_SectorFillHeadInfo(obj->runtime->gcRuntime->backupSector, obj->flsMethod, obj->buff);

            if(FEE_SECTOR_NOT_ERROR != obj->runtime->gcRuntime->backupSector->info->errors)
            {
                obj->runtime->gcRuntime->state = FEE_GC_STATE_WRITE_ENA_MARK_ERROR;
                obj->runtime->gcRuntime->gcFsm = FEE_GC_ERROR;
                FEE_DBG_GC_WRITE_ENABLE_MARK_ERROR_ENTRY();
            }
            else
            {
                obj->runtime->activeSector               = obj->runtime->gcRuntime->backupSector;
                obj->runtime->gcRuntime->backupSector    = NULL;
                obj->runtime->activeSector->info->status = FEE_SECTOR_ACTIVE;
                ret                                      = true;
            }
            break;
        }
    default:
        {
            ret = true;
            FEE_DBG_GC_FSM_ERROR_ENTRY();
            break;
        }
    }

    return ret;
}

static void Fee_OnEntryGcCopyJob(const FeeType *obj)
{
    obj->runtime->gcRuntime->copyFsm  = FEE_GC_COPY_WRITE_MARK;
    obj->runtime->gcRuntime->blockCnt = 0;
}

static bool Fee_GcCopyJob(const FeeType *obj)
{
    bool ret = false;
    switch(obj->runtime->gcRuntime->copyFsm)
    {
    case FEE_GC_COPY_WRITE_MARK:
        {
            /* Write the start transport flag bit to the backup sector. */
            Fee_SectorWriteStartHandMark(obj->runtime->gcRuntime->backupSector, obj->flsMethod, obj->buff);

            if(FEE_SECTOR_NOT_ERROR != obj->runtime->gcRuntime->backupSector->info->errors)
            {
                obj->runtime->gcRuntime->copyFsm = FEE_GC_COPY_ERROR;
                FEE_DBG_GC_WRITE_START_MARK_ERROR_ENTRY();
            }
            else
            {
                obj->runtime->gcRuntime->copyFsm = FEE_GC_COPY_INIT;
            }
            break;
        }
    case FEE_GC_COPY_INIT:
        {
            /* Latest data of index block. */
            if(obj->runtime->gcRuntime->blockCnt < obj->sector->blockSize)
            {
                if(Fee_GcInitBlockInfo(obj, &(obj->sector->blocks[obj->runtime->gcRuntime->blockCnt])))
                {
                    obj->runtime->gcRuntime->copyFsm = FEE_GC_COPY_WRITEBLOCK;
                }
                else if(FEE_GC_STATE_READ_ERROR == obj->runtime->gcRuntime->state)
                {
                    obj->runtime->gcRuntime->copyFsm = FEE_GC_COPY_ERROR;
                }
                obj->runtime->gcRuntime->blockCnt++;
            }
            else
            {
                obj->runtime->gcRuntime->copyFsm = FEE_GC_COPY_FINISH;
            }
            break;
        }
    case FEE_GC_COPY_WRITEBLOCK:
        {
            /* Write to backup sector. */
            if(Fee_GcWriteBlockToNewSector(obj))
            {
                obj->runtime->gcRuntime->copyFsm = FEE_GC_COPY_INIT;
            }
            break;
        }
    case FEE_GC_COPY_FINISH:
        {
            /* Write the completion handling flag bit to backup sector info. */
            Fee_SectorWriteEndHandMark(obj->runtime->gcRuntime->backupSector, obj->flsMethod, obj->buff);

            if(FEE_SECTOR_NOT_ERROR != obj->runtime->gcRuntime->backupSector->info->errors)
            {
                obj->runtime->gcRuntime->copyFsm = FEE_GC_COPY_ERROR;
                FEE_DBG_GC_WRITE_END_MARK_ERROR_ENTRY();
            }
            else
            {
                ret = true;
            }
            break;
        }
    default:
        {
            FEE_DBG_GC_COPY_FSM_ERROR_ENTRY();
            break;
        }
    }

    return ret;
}

static bool Fee_GcInitBlockInfo(const FeeType *obj, const Fee_BlockType *block)
{
    bool     ret = false;
    uint16_t blocksize;

    /* Calculate the location and data size of the valid data stored in the block. */
    if(NULL != block)
    {
        obj->runtime->gcRuntime->currentBlock = block;
        blocksize                             = FEE_BLOCKSIZE(obj->runtime->gcRuntime->currentBlock->cfg);

        if(NULL != Fee_BlockGetPhyAddr(obj->runtime->gcRuntime->currentBlock->info))
        {
            if(FLS_STATE_OK != obj->flsMethod->read(obj->runtime->gcRuntime->currentBlock->info->phyAddr, (uint8_t *)obj->buff, blocksize))
            {
                obj->runtime->gcRuntime->state = FEE_GC_STATE_READ_ERROR;
            }
            else
            {
                ret = true;
            }
        }
    }
    return ret;
}

static bool Fee_GcWriteBlockToNewSector(const FeeType *obj)
{
    bool            ret = false;
    uint16_t        blocksize;
    Fee_AddressType tempPhyaddr;

    /* Obtain the assigned address of the block in the backup sector. */
    blocksize = FEE_BLOCKSIZE(obj->runtime->gcRuntime->currentBlock->cfg);

    /* First write the block data to the flash, ensure safe writing, and then write the block header information. */
    if(FLS_STATE_OK == obj->flsMethod->write(obj->runtime->gcRuntime->backupSector->info->remAddr, (uint8_t *)obj->buff, blocksize))
    {
        tempPhyaddr = Fee_BlockGetPhyAddr(obj->runtime->gcRuntime->currentBlock->info);
        Fee_BlockSetPhyAddr(obj->runtime->gcRuntime->currentBlock->info, obj->runtime->gcRuntime->backupSector->info->remAddr);
        Fee_WriteBlockHeadInfo(obj->runtime->gcRuntime->currentBlock, obj->flsMethod->crc8, obj->buff);

        if(FLS_STATE_OK == obj->flsMethod->write(obj->runtime->gcRuntime->backupSector->info->headInfoAddr, (uint8_t *)obj->buff, FEE_BLOCK_HEAD_INFO_SIZE))
        {
            obj->runtime->gcRuntime->backupSector->info->headInfoAddr -= FEE_BLOCK_HEAD_INFO_SIZE;
            ret = true;
        }
        else
        {
            Fee_BlockSetPhyAddr(obj->runtime->gcRuntime->currentBlock->info, tempPhyaddr);
            obj->runtime->gcRuntime->state = FEE_GC_STATE_WRITE_ERROR;
            FEE_DBG_GC_WRITE_BLOCK_HEAD_INFO_ERROR_ENTRY();
        }

        obj->runtime->gcRuntime->backupSector->info->remAddr += blocksize;
    }
    else
    {
        obj->runtime->gcRuntime->state = FEE_GC_STATE_WRITE_ERROR;
        FEE_DBG_GC_WRITE_BLOCK_DATA_ERROR_ENTRY();
    }
    return ret;
}

static const Fee_SectorConfigType *Fee_FoundBackupSector(const FeeType *obj)
{
    const Fee_SectorConfigType *backupSector = NULL;
    int                         sectorIdx;

    /* Find the backup sector by checking the status of the sector. */
    for(sectorIdx = 0; sectorIdx < obj->sector->sectorSize; sectorIdx++)
    {
        if(FEE_SECTOR_ACTIVE != obj->sector->sectors[sectorIdx].info->status)
        {
            backupSector = &obj->sector->sectors[sectorIdx];
            break;
        }
    }

    return backupSector;
}

static uint16_t Fee_SearchBlock(const Fee_SectorType *obj, uint16_t blockNumber)
{
    uint16_t retBlock       = FEE_INVALID_BLOCK_INDEX;
    uint16_t blockStartIdx  = 0;
    uint16_t blockMiddleIdx = (obj->blockSize - 1) / 2;
    uint16_t blockEndIdx    = obj->blockSize - 1;
    bool     finishFlag     = false;

    while(false == finishFlag)
    {
        /* If the current block and the input block are the same. */
        if(Fee_BlockCheckBlockNumber(obj->blocks[blockMiddleIdx].cfg, blockNumber))
        {
            /* Returns the index of the block. */
            retBlock   = blockMiddleIdx;
            finishFlag = true;
        }
        else
        {
            /* Currently, there are only two or fewer blocks left that are not found, then check the other block. */
            if((blockEndIdx - blockStartIdx) <= 1)
            {
                finishFlag = true;
                if(Fee_BlockCheckBlockNumber(obj->blocks[blockEndIdx].cfg, blockNumber))
                {
                    retBlock = blockEndIdx;
                }
            }
            else
            {
                /* In descending order, first determine whether it is in the right range, */
                /* and then check whether it is in the left range. */
                if(obj->blocks[blockMiddleIdx].cfg->number < blockNumber)
                {
                    blockStartIdx = blockMiddleIdx + 1;
                }
                else
                {
                    blockEndIdx = blockMiddleIdx - 1;
                }

                /* Calculate Median. */
                blockMiddleIdx = blockEndIdx + blockStartIdx;
                blockMiddleIdx /= 2;
            }
        }
    }
    return retBlock;
}
