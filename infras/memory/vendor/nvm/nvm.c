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

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "nvm_extra.h"
#include "nvm_block.h"
#include "nvm_queue.h"
#include "nvm.h"

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
void Nvm_Configure(const NvmType *obj)
{
    /* Initialize job queue. */
    Nvm_Queue_Init(obj->runtime->queue);

    /* Initialize mainfunction state machine. */
    obj->runtime->state     = NVM_STATE_IDLE;
    obj->runtime->nextState = FEE_STATE_INVALID;
}

void Nvm_MainFunction(const NvmType *obj)
{
    /* Check if the state is illegal and if the state function is a null pointer. */
    if((FEE_STATE_INVALID > obj->runtime->state) && (NULL != obj->stateMachine[obj->runtime->state].fn))
    {
        obj->stateMachine[obj->runtime->state].fn(obj);
    }

    /* Check if the jump state is illegal and determine if there is a state that needs to be jumped. */
    if((FEE_STATE_INVALID > obj->runtime->nextState))
    {
        /* Jump Status Management. */
        obj->runtime->state     = obj->runtime->nextState;
        obj->runtime->nextState = FEE_STATE_INVALID;
        /* Check if there are entry functions for executing jump states. */
        if(NULL != obj->stateMachine[obj->runtime->state].onEntry)
        {
            /* Entry function for executing jump state. */
            obj->stateMachine[obj->runtime->state].onEntry(obj);
        }
    }
}

Nvm_ReturnType Nvm_Read(const NvmType *obj, uint16_t blockNumber, uint8_t *dataBuffer)
{
    Nvm_ReturnType      ret = NVM_RETURN_NOT_OK;
    uint16_t            blockIdx;
    Nvm_QueueMemberType member;
    uint8_t             priority;
    uint16_t            blockBaseNumber;
    uint16_t            blockEcuNumber;

    /* Check if mainfunction can respond to read job. */
    if(NVM_STATE_UNINIT != obj->runtime->state)
    {
        /* Data required to initialize read job. */
        blockBaseNumber = NVM_GET_BLOCKNUMBER(blockNumber);
        blockEcuNumber  = NVM_GET_BLOCKDATASETNUMBER(blockNumber);
        blockIdx        = Nvm_Block_Search(obj->blockTable, blockBaseNumber);
        priority        = NVM_BLOCK_GET_PRIORITY(obj->blockTable, blockIdx);

        /* Check if the block is an undefined block. */
        if(NVM_BLOCK_INVALID_IDX != blockIdx)
        {
            /* Initialize read job as a member of the user job queue. */
            Nvm_Queue_InitMember(&member, blockIdx, blockEcuNumber, NVM_STATE_READ, priority, dataBuffer);

            /* Check if the user job queue is full. */
            if(NVM_RETURN_NOT_OK == Nvm_Queue_CheckFull(obj->runtime->queue))
            {
                /* Insert read job members into the user job queue based on priority. */
                Nvm_Queue_Insert(obj->runtime->queue, &member);
                ret = NVM_RETURN_OK;
            }
        }
    }

    return ret;
}

Nvm_ReturnType Nvm_ReadAll(const NvmType *obj)
{
    Nvm_ReturnType      ret = NVM_RETURN_NOT_OK;
    Nvm_QueueMemberType member;

    /* Check if mainfunction can respond to readAll job. */
    if(NVM_STATE_UNINIT != obj->runtime->state)
    {
        /* Initialize readAll job as a member of the system job queue. */
        NVM_QUEUE_SYSMEMBER(&member, NVM_STATE_READALL);

        /* Check if the system job queue is full */
        if(NVM_RETURN_NOT_OK == Nvm_Queue_CheckFull(obj->runtime->queue))
        {
            /* Insert readAll job members into the system job queue based on priority. */
            Nvm_Queue_Insert(obj->runtime->queue, &member);
            ret = NVM_RETURN_OK;
        }
    }

    return ret;
}

Nvm_ReturnType Nvm_Write(const NvmType *obj, uint16_t blockNumber, uint8_t *dataBuffer)
{
    Nvm_ReturnType      ret = NVM_RETURN_NOT_OK;
    Nvm_QueueMemberType member;
    uint8_t             priority;
    uint16_t            blockIdx;
    uint16_t            blockBaseNumber;
    uint16_t            blockEcuNumber;

    /* Check if mainfunction can respond to write job. */
    if(NVM_STATE_UNINIT != obj->runtime->state)
    {
        /* Data required to initialize write job. */
        blockBaseNumber = NVM_GET_BLOCKNUMBER(blockNumber);
        blockEcuNumber  = NVM_GET_BLOCKDATASETNUMBER(blockNumber);
        blockIdx        = Nvm_Block_Search(obj->blockTable, blockBaseNumber);
        priority        = NVM_BLOCK_GET_PRIORITY(obj->blockTable, blockIdx);

        /* Check if the block is an undefined block. */
        if(NVM_BLOCK_INVALID_IDX != blockIdx)
        {
            /* Initialize write job as a member of the user job queue. */
            Nvm_Queue_InitMember(&member, blockIdx, blockEcuNumber, NVM_STATE_WRITE, priority, dataBuffer);

            /* Check if the user job queue is full. */
            if(NVM_RETURN_NOT_OK == Nvm_Queue_CheckFull(obj->runtime->queue))
            {
                /* Insert write job members into the user job queue based on priority. */
                Nvm_Queue_Insert(obj->runtime->queue, &member);
                ret = NVM_RETURN_OK;
            }
        }
    }

    return ret;
}

Nvm_ReturnType Nvm_WriteAll(const NvmType *obj)
{
    Nvm_ReturnType      ret = NVM_RETURN_NOT_OK;
    Nvm_QueueMemberType member;

    /* Check if mainfunction can respond to writeAll job. */
    if(NVM_STATE_UNINIT != obj->runtime->state)
    {
        /* Initialize writeAll job as a member of the system job queue. */
        NVM_QUEUE_SYSMEMBER(&member, NVM_STATE_WRITEALL);

        /* Check if the system job queue is full. */
        if(NVM_RETURN_NOT_OK == Nvm_Queue_CheckFull(obj->runtime->queue))
        {
            /* Insert writeAll job members into the system job queue based on priority. */
            Nvm_Queue_Insert(obj->runtime->queue, &member);
            ret = NVM_RETURN_OK;
        }
    }

    return ret;
}

Nvm_ReturnType Nvm_Erase(const NvmType *obj, uint16_t blockNumber)
{
    Nvm_ReturnType      ret = NVM_RETURN_NOT_OK;
    Nvm_QueueMemberType member;
    uint8_t             priority;
    uint16_t            blockIdx;
    uint16_t            blockBaseNumber;
    uint16_t            blockEcuNumber;
    uint8_t            *dataBuffer;

    /* Check if mainfunction can respond to erase job. */
    if(NVM_STATE_UNINIT != obj->runtime->state)
    {
        /* Initialize the data required for erase job. */
        blockBaseNumber = NVM_GET_BLOCKNUMBER(blockNumber);
        blockEcuNumber  = NVM_GET_BLOCKDATASETNUMBER(blockNumber);
        blockIdx        = Nvm_Block_Search(obj->blockTable, blockBaseNumber);
        priority        = NVM_BLOCK_GET_PRIORITY(obj->blockTable, blockIdx);
        dataBuffer      = NVM_BLOCK_GET_ROM_BUFF_PTR(obj->blockTable, blockIdx, blockEcuNumber);

        /* Check if the block is an undefined block. */
        if(NVM_BLOCK_INVALID_IDX != blockIdx)
        {
            /* Initialize write job as a member of the user job queue. */
            Nvm_Queue_InitMember(&member, blockIdx, blockEcuNumber, NVM_STATE_ERASE, priority, dataBuffer);

            /* Check if the user job queue is full. */
            if(NVM_RETURN_NOT_OK == Nvm_Queue_CheckFull(obj->runtime->queue))
            {
                /* Insert write job members into the user job queue based on priority. */
                Nvm_Queue_Insert(obj->runtime->queue, &member);
                ret = NVM_RETURN_OK;
            }
        }
    }

    return ret;
}

Nvm_ReturnType Nvm_EraseAll(const NvmType *obj)
{
    Nvm_ReturnType      ret = NVM_RETURN_NOT_OK;
    Nvm_QueueMemberType member;

    /* Check if mainfunction can respond to writeAll job. */
    if(NVM_STATE_UNINIT != obj->runtime->state)
    {
        /* Initialize writeAll job as a member of the system job queue. */
        NVM_QUEUE_SYSMEMBER(&member, NVM_STATE_ERASEALL);

        /* Check if the system job queue is full. */
        if(NVM_RETURN_NOT_OK == Nvm_Queue_CheckFull(obj->runtime->queue))
        {
            /* Insert writeAll job members into the system job queue based on priority. */
            Nvm_Queue_Insert(obj->runtime->queue, &member);
            ret = NVM_RETURN_OK;
        }
    }

    return ret;
}

void Nvm_CancelJob(const NvmType *obj)
{
    /* Remove unresponsive jobs from the user queue. */
    Nvm_Queue_RemoveLastItem(obj->runtime->queue);
}

Nvm_stateType Nvm_GetStatus(const NvmType *obj)
{
    /* Obtain the internal state of NVM. */
    return obj->runtime->state;
}

Nvm_BlockState Nvm_GetBlockStatus(const NvmType *obj, uint16_t blockNumber)
{
    Nvm_BlockState ret = NVM_REQ_ERROR;
    uint16_t       blockBaseNumber;
    uint16_t       blockDatasetNumber;
    uint16_t       blockIdx;

    blockBaseNumber = NVM_GET_BLOCKNUMBER(blockNumber);
    blockDatasetNumber  = NVM_GET_BLOCKDATASETNUMBER(blockNumber);

    /* Find the index of the block. */
    blockIdx = Nvm_Block_Search(obj->blockTable, blockBaseNumber);

    /* Check if the block is an undefined block. */
    if(NVM_BLOCK_INVALID_IDX != blockIdx)
    {
        /* Obtain the status of the block. */
        ret = NVM_BLOCK_GET_STATE(obj->blockTable, blockIdx, blockDatasetNumber);
    }

    return ret;
}

void Nvm_GetVersionInfo(Nvm_VersionInfoType *versionInfoPtr)
{
    /* Check if it is a null pointer. */
    if(NULL != versionInfoPtr)
    {
        versionInfoPtr->sw_major_version = NVM_SW_MAJOR_VERSION;
        versionInfoPtr->sw_minor_version = NVM_SW_MINOR_VERSION;
        versionInfoPtr->sw_patch_version = NVM_SW_PATCH_VERSION;
    }
}
