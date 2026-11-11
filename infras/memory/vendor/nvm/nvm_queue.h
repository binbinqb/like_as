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

#ifndef _NVM_QUEUE_H_
#define _NVM_QUEUE_H_

/*! \brief Contains public interface to various functions related
 *         to the NVM (NVRAM Manager) module
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "nvm_types.h"

/*! \addtogroup NVRAM Manager
 *  @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * the defines
 ******************************************************************************/
/*! \brief Define macro to obtain whether queue header members already exist.
 */
#define NVM_QUEUE_FISTMEMBER_VALID(OBJ) (NVM_QUEUEMEMBERSTATE_UNUSED != OBJ->members[0].state)

/*! \brief Define a macro to obtain the operation attribute of queue header members.
 */
#define NVM_QUEUE_FISTMEMBER_OP(OBJ)    (OBJ->members[0].op)

/*! \brief Define macros for adding system queue members.
 */
#define NVM_QUEUE_SYSMEMBER(member, op) Nvm_Queue_InitMember(member, NVM_BLOCK_INVALID_IDX, NVM_DATASET_INVALID_IDX, op, NVM_BLOCK_HIGHT_PRIORITY, NULL)

/*! \brief Define macros for locking queue header members.
 */
#define NVM_QUEUE_LOCK_FIRST_JOB(obj)   obj->members[0].state = NVM_QUEUEMEMBERSTATE_LOCK

/*! \brief Define macros for obtaining queue header members.
 */
#define NVM_QUEUE_FIRST_JOB(obj)        obj->members[0]

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/
void           Nvm_Queue_Init(Nvm_QueueType *obj);
void           Nvm_Queue_InitMember(Nvm_QueueMemberType *member, uint16_t blockIdx, uint16_t datasetIdx, Nvm_stateType op, uint8_t priority, uint8_t *databuff);
void           Nvm_Queue_Insert(Nvm_QueueType *obj, Nvm_QueueMemberType *member);
void           Nvm_Queue_RemoveLastItem(Nvm_QueueType *obj);
void           Nvm_Queue_RemoveFirstItem(Nvm_QueueType *obj);
Nvm_ReturnType Nvm_Queue_CheckFull(Nvm_QueueType *obj);
Nvm_ReturnType Nvm_Queue_CheckEmpty(Nvm_QueueType *obj);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _NVM_QUEUE_H_ */
