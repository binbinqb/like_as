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

#ifndef _FEE_JOBS_H_
#define _FEE_JOBS_H_

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "fee_extra.h"

/*! \addtogroup Flash EEPROM Emulation
 *  @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * the defines
 ******************************************************************************/

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief Job's request type definition.
 */
typedef enum
{
    FEE_JOB_OP_UNDEFINE = 0x00,
    FEE_JOB_OP_READ     = 0x01,
    FEE_JOB_OP_WRITE    = 0x02,
    FEE_JOB_OP_GC       = 0x03,
} Fee_JobOpType;

/*! \brief Definition of mutex type for job.
 */
typedef enum
{
    FEE_JOB_LOCK   = 0x01,
    FEE_JOB_UNLOCK = 0x02,
} Fee_JobLockType;

/*! \brief Control block type definition for job.
 */
typedef struct _Fee_JobControlBlockType_
{
    Fee_JobLockType     lock;
    uint16_t            blockIdx;
    uint16_t            blockOffset;
    Fee_JobOpType       op;
    uint8_t            *dataBuffPtr;
    NotificationPtrType notificationPtr;
} Fee_JobControlBlockType;

/*! \brief Job object type definition.
 */
typedef struct _Fee_JobsType_
{
    bool                              accept;
    struct _Fee_JobControlBlockType_ *userJob;
    struct _Fee_JobControlBlockType_ *sysJob;
} Fee_JobsType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

__attribute__((always_inline)) static inline void Fee_InitJob(Fee_JobControlBlockType *obj)
{
    obj->lock            = FEE_JOB_UNLOCK;
    obj->blockIdx        = 0x0000;
    obj->blockOffset     = 0x0000;
    obj->op              = FEE_JOB_OP_UNDEFINE;
    obj->dataBuffPtr     = NULL;
    obj->notificationPtr = NULL;
}

__attribute__((always_inline)) static inline void Fee_DisableJobs(Fee_JobsType *obj)
{
    obj->accept = false;
}

__attribute__((always_inline)) static inline void Fee_EnableJobs(Fee_JobsType *obj)
{
    obj->accept = true;
}

__attribute__((always_inline)) static inline bool Fee_QueryUserJobIsLock(Fee_JobsType *obj)
{
    bool result = false;

    /* Check whether the mutex of the user job is locked. */
    /* If it is locked, return true. */
    if(FEE_JOB_LOCK == obj->userJob->lock)
    {
        result = true;
    }

    return result;
}

__attribute__((always_inline)) static inline bool Fee_QuerySysJobIsLock(Fee_JobsType *obj)
{
    bool result = false;

    /* Check whether the mutex of the system job is locked. */
    /* If it is locked, return true. */
    if(FEE_JOB_LOCK == obj->sysJob->lock)
    {
        result = true;
    }

    return result;
}

__attribute__((always_inline)) static inline bool Fee_GetUserJob(Fee_JobsType *obj, Fee_JobControlBlockType *config)
{
    bool result = false;

    if(Fee_QueryUserJobIsLock(obj))
    {
        (*config) = *obj->userJob;
        result    = true;
    }

    return result;
}

__attribute__((always_inline)) static inline bool Fee_GetSysJob(Fee_JobsType *obj, Fee_JobControlBlockType *config)
{
    bool result = false;
    
    if(Fee_QuerySysJobIsLock(obj))
    {
        (*config) = *obj->sysJob;
        result    = true;
    }
    
    return result;
}

__attribute__((always_inline)) static inline bool Fee_SetUserJob(Fee_JobsType *obj, Fee_JobControlBlockType *config)
{
    bool result = false;

    /* To check whether the user job can accept requests, */
    /* it is necessary to check whether the user job is allowed to accept requests by the feed. */
    /* In addition, it is also necessary to check whether the user job mutex is unlocked. */
    if((obj->accept) && (false == Fee_QueryUserJobIsLock(obj)))
    {
        *obj->userJob      = *config;
        obj->userJob->lock = FEE_JOB_LOCK;
        result             = true;
    }

    return result;
}

__attribute__((always_inline)) static inline bool Fee_SetSysJob(Fee_JobsType *obj, Fee_JobControlBlockType *config)
{
    bool result = false;

    /* To check whether the system job can accept requests, */
    /* it is necessary to check whether the user job is allowed to accept requests by the feed. */
    /* In addition, it is also necessary to check whether the system job mutex is unlocked. */
    if((obj->accept) && (false == Fee_QuerySysJobIsLock(obj)))
    {
        *obj->sysJob      = *config;
        obj->sysJob->lock = FEE_JOB_LOCK;
        result            = true;
    }

    return result;
}

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _FEE_JOBS_H_ */
