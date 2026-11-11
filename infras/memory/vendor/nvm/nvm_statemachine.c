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

#include <string.h>
#include "nvm_statemachine.h"
#include "nvm_queue.h"
#include "nvm_block.h"
#include "nvm_extra.h"

/*******************************************************************************
 * the defines
 ******************************************************************************/
/*! \brief Macro that defines whether to complete immediate writing.
 */
#define NVM_IMMEDIATE_WRITE_FINISH(obj) (NVM_IMMEDIATEWRITEFSM_FINISH == obj->runtime->immediateWriteJob->job)

/*! \brief Define macros that immediately fail to write.
 */
#define NVM_IMMEDIATE_WRITE_FAIL(obj)   (NVM_IMMEDIATEWRITEFSM_WRITEERROR == obj->runtime->immediateWriteJob->job)

/*! \brief Define macros that immediately write errors.
 */
#define NVM_IMMEDIATE_WRITE_FATAL(obj)  (NVM_IMMEDIATEWRITEFSM_ERROR == obj->runtime->immediateWriteJob->job)

/*! \brief Define immediate read completion macros.
 */
#define NVM_IMMEDIATE_READ_FINISH(obj)  (NVM_IMMEDIATEREADFSM_FINISH == obj->runtime->immediateReadJob->job)

/*! \brief Define macros that immediately fail to read.
 */
#define NVM_IMMEDIATE_READ_FAIL(obj)    (NVM_IMMEDIATEREADFSM_READERROR == obj->runtime->immediateReadJob->job)

/*! \brief Define macros for immediate read errors.
 */
#define NVM_IMMEDIATE_READ_FATAL(obj)   (NVM_IMMEDIATEREADFSM_ERROR == obj->runtime->immediateReadJob->job)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*******************************************************************************
 * the globals
 ******************************************************************************/
static void Nvm_StateMachine_Immediate_Read_Entry(const NvmType *obj, uint16_t blockIdx, uint16_t datasetIdx, uint8_t retry, NvmNotificationPtrType notificationPtr);
static void Nvm_StateMachine_Immediate_Read(const NvmType *obj);
static void Nvm_StateMachine_Immediate_Write_Entry(const NvmType *obj, uint16_t blockIdx, uint16_t datasetIdx, uint8_t retry, NvmNotificationPtrType notificationPtr);
static void Nvm_StateMachine_Immediate_Write(const NvmType *obj);

/*******************************************************************************
 * the functions
 ******************************************************************************/
void Nvm_StateMachine_Idle(const NvmType *obj)
{
    /* Check if the lower level module status is idle. */
    if(NVM_STATUS_IDLE == obj->method->getStatus())
    {
        /* Check if the job queue is empty. */
        if(NVM_RETURN_NOT_OK == Nvm_Queue_CheckEmpty(obj->runtime->queue))
        {
            /* Check if the header members of the queue are valid. */
            if(NVM_QUEUE_FISTMEMBER_VALID(obj->runtime->queue))
            {
                /* Lock the header member of the queue */
                NVM_QUEUE_LOCK_FIRST_JOB(obj->runtime->queue);
                /* Responding to job requests. */
                obj->runtime->nextState = NVM_QUEUE_FISTMEMBER_OP(obj->runtime->queue);
            }
            else
            {
                /* When the header member of the queue is an invalid request, the member will be removed. */
                Nvm_Queue_RemoveFirstItem(obj->runtime->queue);
            }
        }
    }
}

void Nvm_StateMachine_Read_Entry(const NvmType *obj)
{
    uint16_t localBlockIdx;
    uint16_t localDatasetIdx;

    localBlockIdx = NVM_QUEUE_FIRST_JOB(obj->runtime->queue).blockIdx;
    localDatasetIdx   = NVM_QUEUE_FIRST_JOB(obj->runtime->queue).datasetIdx;

    Nvm_Block_SetState(obj->blockTable, localBlockIdx, localDatasetIdx, NVM_REQ_PENDING);

    obj->runtime->readJob->blockIdx     = localBlockIdx;
    obj->runtime->readJob->datasetIdx   = localDatasetIdx;
    obj->runtime->readJob->cpyBuff      = NVM_BLOCK_GET_RAM_BUFF_PTR(obj->blockTable, localBlockIdx, localDatasetIdx);
    obj->runtime->readJob->userBuff     = NVM_QUEUE_FIRST_JOB(obj->runtime->queue).databuff;
    obj->runtime->readJob->datasize     = NVM_BLOCK_GET_DATASIZE(obj->blockTable, localBlockIdx);
}

void Nvm_StateMachine_Read(const NvmType *obj)
{
    /* Verify the data validity of the block. */
    Nvm_Block_DataRepair(obj->blockTable, obj->method, obj->runtime->readJob->blockIdx, obj->runtime->readJob->datasetIdx);

    /* Copy block data to user buff. */
    memcpy((void *)obj->runtime->readJob->userBuff, obj->runtime->readJob->cpyBuff, obj->runtime->readJob->datasize);

    /* Mark the external state of the block as NVM_REQ_OK. */
    Nvm_Block_SetState(obj->blockTable, obj->runtime->readJob->blockIdx, obj->runtime->readJob->datasetIdx, NVM_REQ_OK);
    /* Remove the request. */
    Nvm_Queue_RemoveFirstItem(obj->runtime->queue);
    /* Switch nvm state to idle. */
    obj->runtime->nextState = NVM_STATE_IDLE;
}

void Nvm_StateMachine_Write_Entry(const NvmType *obj)
{
    uint16_t localBlockIdx;
    uint16_t localDatasetIdx;

    localBlockIdx     = NVM_QUEUE_FIRST_JOB(obj->runtime->queue).blockIdx;
    localDatasetIdx   = NVM_QUEUE_FIRST_JOB(obj->runtime->queue).datasetIdx;

    Nvm_Block_SetState(obj->blockTable, localBlockIdx, localDatasetIdx, NVM_REQ_PENDING);

    obj->runtime->writeJob->blockIdx      = localBlockIdx;
    obj->runtime->writeJob->datasetIdx    = localDatasetIdx;
    obj->runtime->writeJob->blockDatabuff = NVM_BLOCK_GET_TEMP_RAM_BUFF_PTR(obj->blockTable, localBlockIdx);
    obj->runtime->writeJob->userBuff      = NVM_QUEUE_FIRST_JOB(obj->runtime->queue).databuff;
    obj->runtime->writeJob->useSize       = NVM_BLOCK_GET_DATASIZE(obj->blockTable, localBlockIdx);
    obj->runtime->writeJob->job           = NVM_WRITEFSM_INIT;

    Nvm_Block_SetTempRamBuffDefaultVal(obj->blockTable, localBlockIdx, localDatasetIdx);
}

void Nvm_StateMachine_Write(const NvmType *obj)
{
    switch(obj->runtime->writeJob->job)
    {
    case NVM_WRITEFSM_INIT:
        {
            /* If the type of the block is REDUNDANT, the state machine will be marked as a redundant write state. */
            /* If not, it will be judged whether it is an immediate write state. */
            /* If not, the state machine will be marked as a normal write state. */
            /* Otherwise, it will be marked as an immediate write state. */
            memcpy((void *)obj->runtime->writeJob->blockDatabuff, (void *)obj->runtime->writeJob->userBuff, obj->runtime->writeJob->useSize);

            if(NVM_BLOCK_IS_REDUNDANT(obj->blockTable, obj->runtime->writeJob->blockIdx))
            {
                obj->runtime->writeJob->job = NVM_WRITEFSM_REDUNDANT_MAIN;
            }
            else if(NVM_BLOCK_IS_IMMEDIATE(obj->blockTable, obj->runtime->writeJob->blockIdx))
            {
                Nvm_StateMachine_Immediate_Write_Entry(obj, obj->runtime->writeJob->blockIdx, obj->runtime->writeJob->datasetIdx, NVM_BLOCK_RETRY_NUM, NULL);
                obj->runtime->writeJob->job = NVM_WRITEFSM_IMMEDIATE;
            }
            else
            {
                obj->runtime->writeJob->job = NVM_WRITEFSM_NORMAL;
            }
            break;
        }
    case NVM_WRITEFSM_IMMEDIATE:
        {
            /* If the immediate write execution is successful or an error occurs, */
            /* mark the state machine to the read back state, otherwise mark the state machine to the normal state. */
            Nvm_StateMachine_Immediate_Write(obj);
            if(NVM_IMMEDIATE_WRITE_FINISH(obj) || NVM_IMMEDIATE_WRITE_FATAL(obj))
            {
                Nvm_StateMachine_Immediate_Read_Entry(obj, obj->runtime->writeJob->blockIdx, obj->runtime->writeJob->datasetIdx, NVM_BLOCK_RETRY_NUM, NULL);
                obj->runtime->writeJob->job = NVM_WRITEFSM_READBACK;
            }
            else if(NVM_IMMEDIATE_WRITE_FAIL(obj))
            {
                obj->runtime->writeJob->job = NVM_WRITEFSM_NORMAL;
            }
            break;
        }
    case NVM_WRITEFSM_REDUNDANT_MAIN:
        {
            /* Execute the write main area of a REDUNDANT type block. */
            obj->runtime->writeJob->blockBackUp = false;
            obj->runtime->writeJob->datasetIdx = NVM_BLOCK_MAIN_IDX;
            if(NVM_BLOCK_IS_IMMEDIATE(obj->blockTable, obj->runtime->writeJob->blockIdx))
            {
                Nvm_StateMachine_Immediate_Write_Entry(obj, obj->runtime->writeJob->blockIdx, obj->runtime->writeJob->datasetIdx, NVM_BLOCK_RETRY_NUM, NULL);
                obj->runtime->writeJob->job = NVM_WRITEFSM_IMMEDIATE;
            }
            else
            {
                obj->runtime->writeJob->job = NVM_WRITEFSM_NORMAL;
            }
            break;
        }
    case NVM_WRITEFSM_REDUNDANT_BACKUP:
    {
        /* Execute the write backup area of a REDUNDANT type block. */
        obj->runtime->writeJob->blockBackUp = true;
        obj->runtime->writeJob->datasetIdx = NVM_BLOCK_BACKUP_IDX;
        if(NVM_BLOCK_IS_IMMEDIATE(obj->blockTable, obj->runtime->writeJob->blockIdx))
        {
            Nvm_StateMachine_Immediate_Write_Entry(obj, obj->runtime->writeJob->blockIdx, obj->runtime->writeJob->datasetIdx, NVM_BLOCK_RETRY_NUM, NULL);
            obj->runtime->writeJob->job = NVM_WRITEFSM_IMMEDIATE;
        }
        else
        {
            obj->runtime->writeJob->job = NVM_WRITEFSM_NORMAL;
        }
        break;
    }
    case NVM_WRITEFSM_READBACK:
        {
            /* Performing operations to read back data. */
            Nvm_StateMachine_Immediate_Read(obj);
            if(NVM_IMMEDIATE_READ_FINISH(obj) || NVM_IMMEDIATE_READ_FATAL(obj))
            {
                obj->runtime->writeJob->job = NVM_WRITEFSM_CHECK;
            }
            else if(NVM_IMMEDIATE_READ_FAIL(obj))
            {
                obj->runtime->writeJob->job = NVM_WRITEFSM_NORMAL;  
            }
            break;
        }
    case NVM_WRITEFSM_CHECK:
        {
            /* Check the validity of data within the block. */
            Nvm_Block_DataRepair(obj->blockTable, obj->method, obj->runtime->writeJob->blockIdx, obj->runtime->writeJob->datasetIdx);
            Nvm_Block_SetState(obj->blockTable, obj->runtime->writeJob->blockIdx, obj->runtime->writeJob->datasetIdx, NVM_BLOCK_GET_INT_STATE(obj->blockTable, obj->runtime->writeJob->blockIdx, obj->runtime->writeJob->datasetIdx));
            if(NVM_BLOCK_IS_REDUNDANT(obj->blockTable, obj->runtime->writeJob->blockIdx))
            {
                if(obj->runtime->writeJob->blockBackUp)
                {
                    obj->runtime->writeJob->job = NVM_WRITEFSM_FINISH;
                }else
                {
                   obj->runtime->writeJob->job = NVM_WRITEFSM_REDUNDANT_BACKUP; 
                }
            }
            else
            {
                obj->runtime->writeJob->job = NVM_WRITEFSM_FINISH;
            }
            break;
        }
    case NVM_WRITEFSM_NORMAL:
        {
            /* Write data to the ram area of the block. */
            Nvm_Block_WriteDataToRamBlock(obj->blockTable, obj->method, obj->runtime->writeJob->blockIdx, obj->runtime->writeJob->datasetIdx, obj->runtime->writeJob->userBuff);
            Nvm_Block_SetState(obj->blockTable, obj->runtime->writeJob->blockIdx, obj->runtime->writeJob->datasetIdx, NVM_REQ_OK);
            if(NVM_BLOCK_IS_REDUNDANT(obj->blockTable, obj->runtime->writeJob->blockIdx))
            {
                if(obj->runtime->writeJob->blockBackUp)
                {
                    obj->runtime->writeJob->job = NVM_WRITEFSM_FINISH;
                }
                else
                {
                    obj->runtime->writeJob->job = NVM_WRITEFSM_REDUNDANT_BACKUP;
                }
            }
            else
            {
                obj->runtime->writeJob->job = NVM_WRITEFSM_FINISH;
            }
            break;
        }
    case NVM_WRITEFSM_FINISH:
        {
            /* Complete response request. */
            Nvm_Queue_RemoveFirstItem(obj->runtime->queue);
            obj->runtime->nextState = NVM_STATE_IDLE;
            break;
        }
    case NVM_WRITEFSM_WRITEERROR:
        {
            /* Complete response request. */
            Nvm_Queue_RemoveFirstItem(obj->runtime->queue);
            obj->runtime->nextState = NVM_STATE_IDLE;
            break;
        }
    default:
        {
            break;
        }
    }
}

void Nvm_StateMachine_ReadAll_Entry(const NvmType *obj)
{
    obj->runtime->readAllJob->job      = NVM_READALLFSM_READBLOCK;
    obj->runtime->readAllJob->blockIdx = 0;
}

void Nvm_StateMachine_ReadAll(const NvmType *obj)
{
    switch(obj->runtime->readAllJob->job)
    {
    case NVM_READALLFSM_READBLOCK:
        {
            /* Mark the state machine as finished after traversing all blocks. */
            if(obj->runtime->readAllJob->blockIdx < obj->blockTable->itemsNum)
            {
                obj->runtime->readAllJob->datasetIdx = 0;
                obj->runtime->readAllJob->job        = NVM_READALLFSM_READENTRY;
            }
            else
            {
                obj->runtime->readAllJob->job = NVM_READALLFSM_FINISH;
            }
            break;
        }
    case NVM_READALLFSM_READENTRY:
        {
            /* Execute the preparation program before immediate reading. */
            if(obj->runtime->readAllJob->datasetIdx < NVM_BLOCK_GET_DATASETNUM(obj->blockTable, obj->runtime->readAllJob->blockIdx))
            {
                Nvm_Block_SetState(obj->blockTable, obj->runtime->readAllJob->blockIdx, obj->runtime->readAllJob->datasetIdx, NVM_REQ_PENDING);
                Nvm_StateMachine_Immediate_Read_Entry(obj, obj->runtime->readAllJob->blockIdx, obj->runtime->readAllJob->datasetIdx, NVM_BLOCK_RETRY_NUM, NULL);
                obj->runtime->readAllJob->job = NVM_READALLFSM_READ;
            }
            else
            {
                obj->runtime->readAllJob->blockIdx++;
                obj->runtime->readAllJob->job = NVM_READALLFSM_READBLOCK;
            }
            break;
        }
    case NVM_READALLFSM_READ:
        {
            /* Execute immediate read. */
            Nvm_StateMachine_Immediate_Read(obj);
            if(NVM_IMMEDIATE_READ_FINISH(obj) || NVM_IMMEDIATE_READ_FAIL(obj) || NVM_IMMEDIATE_READ_FATAL(obj))
            {
                obj->runtime->readAllJob->job = NVM_READALLFSM_CHECK;
            }
            break;
        }
    case NVM_READALLFSM_CHECK:
        {
            /* Check the validity of data within the block. */
            Nvm_Block_DataRepair(obj->blockTable, obj->method, obj->runtime->readAllJob->blockIdx, obj->runtime->readAllJob->datasetIdx);
            Nvm_Block_SetState(obj->blockTable, obj->runtime->readAllJob->blockIdx, obj->runtime->readAllJob->datasetIdx, NVM_BLOCK_GET_INT_STATE(obj->blockTable, obj->runtime->readAllJob->blockIdx, obj->runtime->readAllJob->datasetIdx));
            obj->runtime->readAllJob->datasetIdx++;
            obj->runtime->readAllJob->job = NVM_READALLFSM_READENTRY;
            break;
        }
    case NVM_READALLFSM_FINISH:
        {
            /* Complete response request. */
            Nvm_Queue_RemoveFirstItem(obj->runtime->queue);
            obj->runtime->nextState = NVM_STATE_IDLE;
            break;
        }
    case NVM_READALLFSM_ERROR:
        {
            /* Complete response request. */
            Nvm_Queue_RemoveFirstItem(obj->runtime->queue);
            obj->runtime->nextState = NVM_STATE_IDLE;
            break;
        }
    default:
        {
            break;
        }
    }
}

void Nvm_StateMachine_WriteAll_Entry(const NvmType *obj)
{
    obj->runtime->writeAllJob->job      = NVM_WRITEALLFSM_WRITEBLOCK;
    obj->runtime->writeAllJob->blockIdx = 0;
}

void Nvm_StateMachine_WriteAll(const NvmType *obj)
{
    switch(obj->runtime->writeAllJob->job)
    {
    case NVM_WRITEALLFSM_WRITEBLOCK:
        {
            /* Mark the state machine as finished after traversing all blocks. */
            if(obj->runtime->writeAllJob->blockIdx < obj->blockTable->itemsNum)
            {
                if(NVM_BLOCK_IS_NORMAL(obj->blockTable, obj->runtime->writeAllJob->blockIdx))
                {
                    obj->runtime->writeAllJob->datasetIdx = 0;
                    obj->runtime->writeAllJob->job    = NVM_WRITEALLFSM_WRITEENTRY;
                }
                else
                {
                    obj->runtime->writeAllJob->blockIdx++;
                }
            }
            else
            {
                obj->runtime->writeAllJob->job = NVM_WRITEALLFSM_FINISH;
            }
            break;
        }
    case NVM_WRITEALLFSM_WRITEENTRY:
        {
            /* Execute the preparation program before immediate writeing. */
            if(obj->runtime->writeAllJob->datasetIdx < NVM_BLOCK_GET_DATASETNUM(obj->blockTable, obj->runtime->writeAllJob->blockIdx))
            {
                obj->runtime->writeAllJob->blockDatabuff = NVM_BLOCK_GET_TEMP_RAM_BUFF_PTR(obj->blockTable, obj->runtime->writeAllJob->blockIdx);
                if(Nvm_Block_GetWriteData(obj->blockTable, obj->runtime->writeAllJob->blockIdx, obj->runtime->writeAllJob->datasetIdx, obj->method, obj->runtime->writeAllJob->blockDatabuff))
                {
                    Nvm_Block_SetState(obj->blockTable, obj->runtime->writeAllJob->blockIdx, obj->runtime->writeAllJob->datasetIdx, NVM_REQ_PENDING);
                    Nvm_StateMachine_Immediate_Write_Entry(obj, obj->runtime->writeAllJob->blockIdx, obj->runtime->writeAllJob->datasetIdx, NVM_BLOCK_RETRY_NUM, NULL);
                    obj->runtime->writeAllJob->job = NVM_WRITEALLFSM_WRITE;
                }
                else
                {
                    obj->runtime->writeAllJob->datasetIdx++;
                }
            }
            else
            {
                obj->runtime->writeAllJob->blockIdx++;
                obj->runtime->writeAllJob->job = NVM_WRITEALLFSM_WRITEBLOCK;
            }
            break;
        }
    case NVM_WRITEALLFSM_WRITE:
        {
            /* Execute immediate write. */
            Nvm_StateMachine_Immediate_Write(obj);
            if(NVM_IMMEDIATE_WRITE_FINISH(obj) || NVM_IMMEDIATE_WRITE_FAIL(obj) || NVM_IMMEDIATE_WRITE_FATAL(obj))
            {
                Nvm_Block_SetState(obj->blockTable, obj->runtime->writeAllJob->blockIdx, obj->runtime->writeAllJob->datasetIdx, NVM_BLOCK_GET_INT_STATE(obj->blockTable, obj->runtime->writeAllJob->blockIdx, obj->runtime->writeAllJob->datasetIdx));
                obj->runtime->writeAllJob->datasetIdx++;
                obj->runtime->writeAllJob->job = NVM_WRITEALLFSM_WRITEENTRY;
            }
            break;
        }
    case NVM_WRITEALLFSM_FINISH:
        {
            /* Complete response request. */
            Nvm_Queue_RemoveFirstItem(obj->runtime->queue);
            obj->runtime->nextState = NVM_STATE_IDLE;
            break;
        }
    case NVM_WRITEALLFSM_ERROR:
        {
            /* Complete response request. */
            Nvm_Queue_RemoveFirstItem(obj->runtime->queue);
            obj->runtime->nextState = NVM_STATE_IDLE;
            break;
        }
    default:
        {
            break;
        }
    }
}

void Nvm_StateMachine_EraseAll_Entry(const NvmType *obj)
{
    obj->runtime->eraseAllJob->blockIdx = 0;
    obj->runtime->eraseAllJob->job      = NVM_ERASEALLFSM_ERASEBLOCK;
}

void Nvm_StateMachine_EraseAll(const NvmType *obj)
{
    switch(obj->runtime->eraseAllJob->job)
    {
    case NVM_ERASEALLFSM_ERASEBLOCK:
        {
            /* Mark the state machine as finished after traversing all blocks. */
            if(obj->runtime->eraseAllJob->blockIdx < obj->blockTable->itemsNum)
            {
                obj->runtime->eraseAllJob->datasetIdx = 0;
                obj->runtime->eraseAllJob->job    = NVM_ERASEALLFSM_ERASEENTRY;
            }
            else
            {
                obj->runtime->eraseAllJob->job = NVM_ERASEALLFSM_FINISH;
            }
            break;
        }
    case NVM_ERASEALLFSM_ERASEENTRY:
        {
            /* Execute the preparation program before erasing immediately. */
            if(obj->runtime->eraseAllJob->datasetIdx < NVM_BLOCK_GET_DATASETNUM(obj->blockTable, obj->runtime->eraseAllJob->blockIdx))
            {
                obj->runtime->eraseAllJob->blockDatabuff = NVM_BLOCK_GET_TEMP_RAM_BUFF_PTR(obj->blockTable, obj->runtime->eraseAllJob->blockIdx);
                Nvm_Block_GetRomData(obj->blockTable, obj->runtime->eraseAllJob->blockIdx, obj->runtime->eraseAllJob->datasetIdx, obj->runtime->eraseAllJob->blockDatabuff);
                Nvm_Block_SetState(obj->blockTable, obj->runtime->eraseAllJob->blockIdx, obj->runtime->eraseAllJob->datasetIdx, NVM_REQ_PENDING);
                Nvm_StateMachine_Immediate_Write_Entry(obj, obj->runtime->eraseAllJob->blockIdx, obj->runtime->eraseAllJob->datasetIdx, NVM_BLOCK_RETRY_NUM, NULL);
                obj->runtime->eraseAllJob->job = NVM_ERASEALLFSM_ERASE;
            }
            else
            {
                obj->runtime->eraseAllJob->blockIdx++;
                obj->runtime->eraseAllJob->job = NVM_ERASEALLFSM_ERASEBLOCK;
            }
            break;
        }
    case NVM_ERASEALLFSM_ERASE:
        {
            /* Execute immediate erase. */
            Nvm_StateMachine_Immediate_Write(obj);
            if(NVM_IMMEDIATE_WRITE_FINISH(obj) || NVM_IMMEDIATE_WRITE_FAIL(obj) || NVM_IMMEDIATE_WRITE_FATAL(obj))
            {
                obj->runtime->eraseAllJob->job = NVM_ERASEALLFSM_READBACK;
            }
            break;
        }
    case NVM_ERASEALLFSM_READBACK:
        {
            /* Performing operations to read back data. */
            obj->runtime->eraseAllJob->blockRombuff = NVM_BLOCK_GET_ROM_BUFF_PTR(obj->blockTable, obj->runtime->eraseAllJob->blockIdx, obj->runtime->eraseAllJob->datasetIdx);
            Nvm_Block_WriteDataToRamBlock(obj->blockTable, obj->method, obj->runtime->eraseAllJob->blockIdx, obj->runtime->eraseAllJob->datasetIdx, obj->runtime->eraseAllJob->blockRombuff);
            Nvm_Block_SetState(obj->blockTable, obj->runtime->eraseAllJob->blockIdx, obj->runtime->eraseAllJob->datasetIdx, NVM_BLOCK_GET_INT_STATE(obj->blockTable, obj->runtime->eraseAllJob->blockIdx, obj->runtime->eraseAllJob->datasetIdx));
            obj->runtime->eraseAllJob->datasetIdx++;
            obj->runtime->eraseAllJob->job = NVM_ERASEALLFSM_ERASEENTRY;
            break;
        }
    case NVM_ERASEALLFSM_FINISH:
        {
            /* Complete response request. */
            Nvm_Queue_RemoveFirstItem(obj->runtime->queue);
            obj->runtime->nextState = NVM_STATE_IDLE;
            break;
        }
    case NVM_WRITEALLFSM_ERROR:
        {
            /* Complete response request. */
            Nvm_Queue_RemoveFirstItem(obj->runtime->queue);
            obj->runtime->nextState = NVM_STATE_IDLE;
            break;
        }
    default:
        {
            break;
        }
    }
}

void Nvm_StateMachine_Erase_Entry(const NvmType *obj)
{
    uint16_t localBlockIdx;
    uint16_t localDatasetIdx;

    localBlockIdx     = obj->runtime->queue->members[0].blockIdx;
    localDatasetIdx   = obj->runtime->queue->members[0].datasetIdx;

    Nvm_Block_SetState(obj->blockTable, localBlockIdx, localDatasetIdx, NVM_REQ_PENDING);

    obj->runtime->eraseJob->blockIdx      = localBlockIdx;
    obj->runtime->eraseJob->datasetIdx    = localDatasetIdx;
    obj->runtime->eraseJob->blockDatabuff = NVM_BLOCK_GET_TEMP_RAM_BUFF_PTR(obj->blockTable, localBlockIdx);
    obj->runtime->eraseJob->job           = NVM_ERASEFSM_INIT;

    Nvm_Block_GetRomData(obj->blockTable, obj->runtime->eraseJob->blockIdx, obj->runtime->eraseJob->datasetIdx, obj->runtime->eraseJob->blockDatabuff);
}

void Nvm_StateMachine_Erase(const NvmType *obj)
{
    switch(obj->runtime->eraseJob->job)
    {
    case NVM_ERASEFSM_INIT:
        {
            /* If the type of the block is REDUNDANT, the state machine will be marked as a redundant state. */
            /* If not, it will be judged whether it is an immediate state. */
            /* Otherwise, it will be marked as an immediate state. */
            if(NVM_BLOCK_IS_REDUNDANT(obj->blockTable, obj->runtime->eraseJob->blockIdx))
            {
                obj->runtime->eraseJob->job = NVM_ERASEFSM_REDUNDANT_MAIN;   
            }
            else
            {
                Nvm_StateMachine_Immediate_Write_Entry(obj, obj->runtime->eraseJob->blockIdx, obj->runtime->eraseJob->datasetIdx, NVM_BLOCK_RETRY_NUM, NULL);
                obj->runtime->eraseJob->job = NVM_ERASEFSM_IMMEDIATE; 
            }
            break;
        }
    case NVM_ERASEFSM_IMMEDIATE:
        {
            
            /* If the immediate execution is successful or an error occurs, */
            /* mark the state machine to the read back state.*/
            Nvm_StateMachine_Immediate_Write(obj);
            if(NVM_IMMEDIATE_WRITE_FINISH(obj) || NVM_IMMEDIATE_WRITE_FAIL(obj) || NVM_IMMEDIATE_WRITE_FATAL(obj))
            {
                Nvm_StateMachine_Immediate_Read_Entry(obj, obj->runtime->eraseJob->blockIdx, obj->runtime->eraseJob->datasetIdx, NVM_BLOCK_RETRY_NUM, NULL);
                obj->runtime->eraseJob->job = NVM_ERASEFSM_READBACK;
            }
            break;
        }
    case  NVM_ERASEFSM_REDUNDANT_MAIN:
        {
            /* Execute the erase main area of a REDUNDANT type block. */
            obj->runtime->writeJob->blockBackUp = false;
            obj->runtime->writeJob->datasetIdx = NVM_BLOCK_MAIN_IDX;
            Nvm_StateMachine_Immediate_Write_Entry(obj, obj->runtime->writeJob->blockIdx, obj->runtime->writeJob->datasetIdx, NVM_BLOCK_RETRY_NUM, NULL);
            obj->runtime->writeJob->job = NVM_WRITEFSM_IMMEDIATE;
            break;
        }
    case NVM_ERASEFSM_REDUNDANT_BACKUP:
        {
            /* Execute the erase backup area of a REDUNDANT type block. */
            obj->runtime->writeJob->blockBackUp = true;
            obj->runtime->writeJob->datasetIdx = NVM_BLOCK_BACKUP_IDX;
            Nvm_StateMachine_Immediate_Write_Entry(obj, obj->runtime->writeJob->blockIdx, obj->runtime->writeJob->datasetIdx, NVM_BLOCK_RETRY_NUM, NULL);
            obj->runtime->writeJob->job = NVM_WRITEFSM_IMMEDIATE;
            break;
        }
    case NVM_ERASEFSM_READBACK:
        {
            /* Performing operations to read back data. */
            Nvm_StateMachine_Immediate_Read(obj);
            if(NVM_IMMEDIATE_READ_FINISH(obj) || NVM_IMMEDIATE_READ_FAIL(obj) || NVM_IMMEDIATE_READ_FATAL(obj))
            {
                obj->runtime->eraseJob->job = NVM_ERASEFSM_CHECK;
            }
            break;
        }
    case NVM_ERASEFSM_CHECK:
        {
            /* Check the validity of data within the block. */
            Nvm_Block_DataRepair(obj->blockTable, obj->method, obj->runtime->eraseJob->blockIdx, obj->runtime->eraseJob->datasetIdx);
            Nvm_Block_SetState(obj->blockTable, obj->runtime->eraseJob->blockIdx, obj->runtime->eraseJob->datasetIdx, NVM_BLOCK_GET_INT_STATE(obj->blockTable, obj->runtime->eraseJob->blockIdx, obj->runtime->eraseJob->datasetIdx));
            /* Determine the type of block. */
            if(NVM_BLOCK_IS_REDUNDANT(obj->blockTable, obj->runtime->eraseJob->blockIdx))
            {
                if(obj->runtime->eraseJob->blockBackUp)
                {
                    obj->runtime->eraseJob->job = NVM_ERASEFSM_FINISH;
                }
                else
                {
                    obj->runtime->eraseJob->job = NVM_ERASEFSM_REDUNDANT_BACKUP;   
                }
            }
            else
            {
                obj->runtime->eraseJob->job = NVM_ERASEFSM_FINISH;
            }
            break;
        }
    case NVM_ERASEFSM_FINISH:
        {
            /* Complete response request. */
            Nvm_Queue_RemoveFirstItem(obj->runtime->queue);
            obj->runtime->nextState = NVM_STATE_IDLE;
            break;
        }
    case NVM_ERASEFSM_ERASEERROR:
        {
            /* Complete response request. */
            Nvm_Queue_RemoveFirstItem(obj->runtime->queue);
            obj->runtime->nextState = NVM_STATE_IDLE;
            break;
        }
    default:
        {
            break;
        }
    }
}

void Nvm_StateMachine_Immediate_Read_Entry(const NvmType *obj, uint16_t blockIdx, uint16_t datasetIdx, uint8_t retry, NvmNotificationPtrType notificationPtr)
{
    obj->runtime->immediateReadJob->job = NVM_IMMEDIATEREADFSM_MAIN;

    Nvm_Block_SetInternalState(obj->blockTable, blockIdx, datasetIdx, NVM_REQ_PENDING);

    Nvm_Block_ClrRamBuff(obj->blockTable, blockIdx, datasetIdx);

    obj->runtime->immediateReadJob->mainRetryCnt    = retry;
    obj->runtime->immediateReadJob->backupRetryCnt  = retry;
    obj->runtime->immediateReadJob->notificationPtr = notificationPtr;
    obj->runtime->immediateReadJob->blockIdx        = blockIdx;
    obj->runtime->immediateReadJob->datasetIdx      = datasetIdx;
    obj->runtime->immediateReadJob->blockNumber     = obj->blockTable->items[blockIdx].number + datasetIdx;
    obj->runtime->immediateReadJob->blockDatabuff   = NVM_BLOCK_GET_TEMP_RAM_BUFF_PTR(obj->blockTable, blockIdx);
    obj->runtime->immediateReadJob->blockUseSize    = ALIGN8BYTE(Nvm_Block_CalcUseSize(obj->blockTable, blockIdx));
}

static void Nvm_StateMachine_Immediate_Read(const NvmType *obj)
{
    switch(obj->runtime->immediateReadJob->job)
    {
    case NVM_IMMEDIATEREADFSM_MAIN:
        {
            /* Obtain lower level module status. */
            if(NVM_STATUS_IDLE == obj->method->getStatus())
            {
                /* Request lower level module to read data. */
                if(obj->method->read(obj->runtime->immediateReadJob->blockNumber, NVM_BLOCK_MAIN_IDX, obj->runtime->immediateReadJob->blockDatabuff, obj->runtime->immediateReadJob->notificationPtr))
                {
                    /* Request successful, waiting for the response from the lower level module to complete. */
                    obj->runtime->immediateReadJob->job = NVM_IMMEDIATEREADFSM_WMF;
                }
                else
                {
                    /* If the request fails, it will be retried. */
                    Nvm_Block_SetInternalState(obj->blockTable, obj->runtime->immediateReadJob->blockIdx, obj->runtime->immediateReadJob->datasetIdx, NVM_REQ_NOT_OK);
                    obj->runtime->immediateReadJob->job = NVM_IMMEDIATEREADFSM_MAIN_RETRY;
                }
            }
            break;
        }
    case NVM_IMMEDIATEREADFSM_MAIN_RETRY:
        {
            /* Wait for an attempt to resend the request to the lower module. */
            if(obj->runtime->immediateReadJob->mainRetryCnt > 0)
            {
                obj->runtime->immediateReadJob->mainRetryCnt--;
                obj->runtime->immediateReadJob->job = NVM_IMMEDIATEREADFSM_MAIN;
            }
            else
            {
                /* If the retry count exceeds the threshold, mark the state machine as an error. */
                obj->runtime->immediateReadJob->job = NVM_IMMEDIATEREADFSM_READERROR;
            }
            break;
        }
    case NVM_IMMEDIATEREADFSM_WMF:
        {
            /* Waiting for lower level request status to respond successfully, response not successful, response error. */
            if(NVM_JOB_RESULT_OK == obj->method->getJobResult())
            {
                /* Wait for the lower level request status to respond successfully, then mark the internal management status of the block as FINISH. */
                Nvm_Block_WriteDataToBuff(obj->blockTable, obj->method, obj->runtime->immediateReadJob->blockIdx, obj->runtime->immediateReadJob->datasetIdx, obj->runtime->immediateReadJob->blockDatabuff);
                Nvm_Block_SetInternalState(obj->blockTable, obj->runtime->immediateReadJob->blockIdx, obj->runtime->immediateReadJob->datasetIdx, NVM_REQ_OK);
                obj->runtime->immediateReadJob->job = NVM_IMMEDIATEREADFSM_FINISH;
            }
            else if(NVM_JOB_RESULT_NOT_OK == obj->method->getJobResult())
            {
                /* If the request status at the lower level is unsuccessful, mark the internal management status of the block as ERROR. */
                Nvm_Block_ClrBlockRamBuff(obj->blockTable, obj->runtime->immediateReadJob->blockIdx, obj->runtime->immediateReadJob->datasetIdx);
                Nvm_Block_SetInternalState(obj->blockTable, obj->runtime->immediateReadJob->blockIdx, obj->runtime->immediateReadJob->datasetIdx, NVM_REQ_NOT_OK);
                obj->runtime->immediateReadJob->job = NVM_IMMEDIATEREADFSM_READERROR;
            }
            else if(NVM_JOB_RESULT_BL_INCONSISTENT == obj->method->getJobResult())
            {
                /* Wait for the lower level request status to be block integrity error, then mark the internal management status of the block as ERROR. */
                Nvm_Block_ClrBlockRamBuff(obj->blockTable, obj->runtime->immediateReadJob->blockIdx, obj->runtime->immediateReadJob->datasetIdx);
                Nvm_Block_SetInternalState(obj->blockTable, obj->runtime->immediateReadJob->blockIdx, obj->runtime->immediateReadJob->datasetIdx, NVM_REQ_INTEGRITY_FAILED);
                obj->runtime->immediateReadJob->job = NVM_IMMEDIATEREADFSM_READERROR;
            }
            else if(NVM_JOB_RESULT_BL_INVALID == obj->method->getJobResult())
            {
                /* If the request status of the lower level is an undefined block, the internal management status of the block will be marked as ERROR. */
                Nvm_Block_ClrBlockRamBuff(obj->blockTable, obj->runtime->immediateReadJob->blockIdx, obj->runtime->immediateReadJob->datasetIdx);
                Nvm_Block_SetInternalState(obj->blockTable, obj->runtime->immediateReadJob->blockIdx, obj->runtime->immediateReadJob->datasetIdx, NVM_REQ_UNINT);
                obj->runtime->immediateReadJob->job = NVM_IMMEDIATEREADFSM_READERROR;
            }
            break;
        }
    case NVM_IMMEDIATEREADFSM_FINISH:
        {
            break;
        }
    case NVM_IMMEDIATEREADFSM_READERROR:
        {
            break;
        }
    default:
        {
            break;
        }
    }
}

static void Nvm_StateMachine_Immediate_Write_Entry(const NvmType *obj, uint16_t blockIdx, uint16_t datasetIdx, uint8_t retry, NvmNotificationPtrType notificationPtr)
{
    uint16_t crcLen;
    
    
    obj->runtime->immediateWriteJob->job = NVM_IMMEDIATEWRITEFSM_MAIN;

    Nvm_Block_SetInternalState(obj->blockTable, blockIdx, datasetIdx, NVM_REQ_PENDING);

    obj->runtime->immediateWriteJob->retry           = retry;
    obj->runtime->immediateWriteJob->notificationPtr = notificationPtr;
    obj->runtime->immediateWriteJob->blockIdx        = blockIdx;
    obj->runtime->immediateWriteJob->datasetIdx      = datasetIdx;
    obj->runtime->immediateWriteJob->blockNumber     = obj->blockTable->items[blockIdx].number + datasetIdx;
    obj->runtime->immediateWriteJob->blockDatabuff   = NVM_BLOCK_GET_TEMP_RAM_BUFF_PTR(obj->blockTable, blockIdx);

    if(NVM_BLOCK_IS_CRC(obj->blockTable, obj->runtime->immediateWriteJob->blockIdx))
    {
        crcLen                                                 = NVM_BLOCK_GET_CRC_LEN(obj->blockTable, obj->runtime->immediateWriteJob->blockIdx);
        obj->runtime->immediateWriteJob->blockDatabuff[crcLen] = obj->method->crc8(obj->runtime->immediateWriteJob->blockDatabuff, crcLen);
    }
}

static void Nvm_StateMachine_Immediate_Write(const NvmType *obj)
{
    switch(obj->runtime->immediateWriteJob->job)
    {
    case NVM_IMMEDIATEWRITEFSM_MAIN:
        {
            /* Obtain lower level module status. */
            if(NVM_STATUS_IDLE == obj->method->getStatus())
            {
                /* Request lower level module to write data. */
                if(obj->method->write(obj->runtime->immediateWriteJob->blockNumber, obj->runtime->immediateWriteJob->blockDatabuff, obj->runtime->immediateWriteJob->notificationPtr))
                {
                    /* Request successful, waiting for the response from the lower level module to complete. */
                    obj->runtime->immediateWriteJob->job = NVM_IMMEDIATEWRITEFSM_WMF;
                }
                else
                {
                    /* If the request fails, it will be retried. */
                    obj->runtime->immediateWriteJob->job = NVM_IMMEDIATEWRITEFSM_RETRY;
                }
            }
            /* If the lower level module is in a state of responding to a request, calibrate the state machine to WAITMANAGE. */
            else if(NVM_STATUS_GC == obj->method->getStatus())
            {
                obj->runtime->immediateWriteJob->job = NVM_IMMEDIATEWRITEFSM_WAITMANAGE;
            }
            else if(NVM_STATUS_READ == obj->method->getStatus())
            {
                obj->runtime->immediateWriteJob->job = NVM_IMMEDIATEWRITEFSM_WAITMANAGE;
            }
            else if(NVM_STATUS_WRITE == obj->method->getStatus())
            {
                obj->runtime->immediateWriteJob->job = NVM_IMMEDIATEWRITEFSM_WAITMANAGE;
            }
            else
            {
                obj->runtime->immediateWriteJob->job = NVM_IMMEDIATEWRITEFSM_ERROR;
            }
            break;
        }
    case NVM_IMMEDIATEWRITEFSM_RETRY:
        {
            /* Wait for an attempt to resend the request to the lower module. */
            if(obj->runtime->immediateWriteJob->retry > 0)
            {
                obj->runtime->immediateWriteJob->retry--;
                obj->runtime->immediateWriteJob->job = NVM_IMMEDIATEWRITEFSM_MAIN;
            }
            else
            {
                /* If the retry count exceeds the threshold, mark the state machine as an error. */
                obj->runtime->immediateWriteJob->job = NVM_IMMEDIATEWRITEFSM_WRITEERROR;
            }
            break;
        }
    case NVM_IMMEDIATEWRITEFSM_WMF:
        {
            /* Waiting for lower level request status to respond successfully, response not successful, response error. */
            if(NVM_JOB_RESULT_OK == obj->method->getJobResult())
            {
                /* Wait for the lower level request status to respond successfully, then mark the internal management status of the block as FINISH. */
                Nvm_Block_SetInternalState(obj->blockTable, obj->runtime->immediateWriteJob->blockIdx, obj->runtime->immediateWriteJob->datasetIdx, NVM_REQ_OK);
                obj->runtime->immediateWriteJob->job = NVM_IMMEDIATEWRITEFSM_FINISH;
            }
            else if(NVM_JOB_RESULT_NOT_OK == obj->method->getJobResult())
            {
                /* If the request status at the lower level is unsuccessful, mark the internal management status of the block as ERROR. */
                Nvm_Block_SetInternalState(obj->blockTable, obj->runtime->immediateWriteJob->blockIdx, obj->runtime->immediateWriteJob->datasetIdx, NVM_REQ_NOT_OK);
                obj->runtime->immediateWriteJob->job = NVM_IMMEDIATEWRITEFSM_WRITEERROR;
            }
            else if(NVM_JOB_RESULT_BL_INCONSISTENT == obj->method->getJobResult())
            {
                /* Wait for the lower level request status to be block integrity error, then mark the internal management status of the block as ERROR. */
                Nvm_Block_SetInternalState(obj->blockTable, obj->runtime->immediateWriteJob->blockIdx, obj->runtime->immediateWriteJob->datasetIdx, NVM_REQ_INTEGRITY_FAILED);
                obj->runtime->immediateWriteJob->job = NVM_IMMEDIATEWRITEFSM_WRITEERROR;
            }
            else if(NVM_JOB_RESULT_BL_INVALID == obj->method->getJobResult())
            {
                /* If the request status of the lower level is an undefined block, the internal management status of the block will be marked as ERROR. */
                Nvm_Block_SetInternalState(obj->blockTable, obj->runtime->immediateWriteJob->blockIdx, obj->runtime->immediateWriteJob->datasetIdx, NVM_REQ_UNINT);
                obj->runtime->immediateWriteJob->job = NVM_IMMEDIATEWRITEFSM_WRITEERROR;
            }
            break;
        }
    case NVM_IMMEDIATEWRITEFSM_FINISH:
        {
            break;
        }
    case NVM_IMMEDIATEWRITEFSM_WRITEERROR:
        {
            break;
        }
    case NVM_IMMEDIATEWRITEFSM_WAITMANAGE:
        {
            /* When waiting for the status of the lower level module to be idle, mark the status as requesting the lower level module to write. */
            if(NVM_STATUS_IDLE == obj->method->getStatus())
            {
                obj->runtime->immediateWriteJob->job = NVM_IMMEDIATEWRITEFSM_MAIN;
            }
            break;
        }
    default:
        {
            break;
        }
    }
}
