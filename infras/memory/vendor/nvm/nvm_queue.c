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

#include "nvm_queue.h"

/*******************************************************************************
 * the defines
 ******************************************************************************/

#define NVM_QUEUE_FULL(OBJ)        (OBJ->index >= OBJ->memberNum)
#define NVM_QUEUE_EMPTY(OBJ)       (OBJ->index == 0)

#define NVM_QUEUE_BLOCK_UNVALID    (0xFFFF)
#define NVM_QUEUE_DATASET_UNVALID  (0xFFFF)
#define NVM_QUEUE_PRIORITY_UNVALID (0xFF)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the static
 ******************************************************************************/
static void     Nvm_Queue_Append(Nvm_QueueType *obj, Nvm_QueueMemberType *member);

/*******************************************************************************
 * the functions
 ******************************************************************************/

void Nvm_Queue_Init(Nvm_QueueType *obj)
{
    uint8_t idx;
    /* Initialize all members of the queue. */
    for(idx = 0; idx < obj->memberNum; idx++)
    {
        obj->members[idx].blockIdx = NVM_QUEUE_BLOCK_UNVALID;
        obj->members[idx].datasetIdx   = NVM_QUEUE_DATASET_UNVALID;
        obj->members[idx].op       = FEE_STATE_INVALID;
        obj->members[idx].priority = NVM_QUEUE_PRIORITY_UNVALID;
        obj->members[idx].state    = NVM_QUEUEMEMBERSTATE_UNUSED;
    }
    
    /* The index value of the queue points to the header of the queue. */
    obj->index = 0;
}

void Nvm_Queue_InitMember(Nvm_QueueMemberType *member, uint16_t blockIdx, uint16_t datasetIdx, Nvm_stateType op, uint8_t priority, uint8_t *databuff)
{
    /* Initialize members of the queue. */
    member->blockIdx     = blockIdx;
    member->datasetIdx   = datasetIdx;
    member->op           = op;
    member->databuff     = databuff;
    member->priority     = priority;
    member->state        = NVM_QUEUEMEMBERSTATE_USED;
}

void Nvm_Queue_Insert(Nvm_QueueType *obj, Nvm_QueueMemberType *member)
{
    uint8_t             localIdx;

    /* Check if the queue is empty. */
    if(NVM_RETURN_NOT_OK == Nvm_Queue_CheckEmpty(obj))
    {
        /* Insert members into the queue according to priority. */
        for(localIdx = obj->index; localIdx > 0; localIdx--)
        {
            if(obj->members[localIdx - 1].priority > member->priority)
            {
                if(NVM_QUEUEMEMBERSTATE_LOCK != obj->members[localIdx - 1].state)
                {
                    obj->members[localIdx] = obj->members[localIdx - 1];
                }
                else
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }

        obj->members[localIdx]       = *member;
        obj->members[localIdx].state = NVM_QUEUEMEMBERSTATE_USED;
        obj->index++;
    }
    else
    {
        /* Append member to queue. */
        Nvm_Queue_Append(obj, member);
    }
}

void Nvm_Queue_RemoveLastItem(Nvm_QueueType *obj)
{
    Nvm_QueueMemberType member;

    /* Set the member of the queue to the default value. */
    member.blockIdx = NVM_QUEUE_BLOCK_UNVALID;
    member.datasetIdx   = NVM_QUEUE_DATASET_UNVALID;
    member.op       = FEE_STATE_INVALID;
    member.priority = NVM_QUEUE_PRIORITY_UNVALID;
    member.state    = NVM_QUEUEMEMBERSTATE_UNUSED;
    member.databuff = NULL;

    /* Remove member from queue. */
    if(NVM_QUEUEMEMBERSTATE_LOCK != obj->members[obj->index - 1].state)
    {
        obj->members[obj->index - 1] = member;
        obj->index--;
    }
}

void Nvm_Queue_RemoveFirstItem(Nvm_QueueType *obj)
{
    uint8_t localIdx;

    /* Check if the queue is not empty. */
    if(NVM_RETURN_NOT_OK == Nvm_Queue_CheckEmpty(obj))
    {
        /* Remove member from queue. */
        for(localIdx = 0; localIdx < obj->index; localIdx++)
        {
            if((localIdx + 1) >= obj->index)
            {
                /* Set the member of the queue to the default value. */
                obj->members[localIdx].blockIdx     = NVM_QUEUE_BLOCK_UNVALID;
                obj->members[localIdx].datasetIdx   = NVM_QUEUE_DATASET_UNVALID;
                obj->members[localIdx].op           = FEE_STATE_INVALID;
                obj->members[localIdx].priority     = NVM_QUEUE_PRIORITY_UNVALID;
                obj->members[localIdx].state        = NVM_QUEUEMEMBERSTATE_UNUSED;
            }
            else
            {
                obj->members[localIdx] = obj->members[localIdx + 1];
            }
        }
        obj->index--;
    }
}

Nvm_ReturnType Nvm_Queue_CheckFull(Nvm_QueueType *obj)
{
    Nvm_ReturnType ret = NVM_RETURN_NOT_OK;

    /* When the index value points to the end of the queue, it indicates that the queue is full. */
    if(obj->index >= obj->memberNum)
    {
        ret = NVM_RETURN_OK;
    }
    return ret;
}

Nvm_ReturnType Nvm_Queue_CheckEmpty(Nvm_QueueType *obj)
{
    Nvm_ReturnType ret = NVM_RETURN_NOT_OK;

    /* When the index value points to the queue header, it indicates that the queue is empty. */
    if(obj->index == 0)
    {
        ret = NVM_RETURN_OK;
    }

    return ret;
}

static void Nvm_Queue_Append(Nvm_QueueType *obj, Nvm_QueueMemberType *member)
{
    /* Append member to the end of the queue. */
    obj->members[obj->index]       = (*member);
    obj->members[obj->index].state = NVM_QUEUEMEMBERSTATE_USED;
    obj->index++;
}
