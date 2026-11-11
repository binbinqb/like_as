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

#ifndef _NVM_TYPES_H_
#define _NVM_TYPES_H_

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdio.h>
#include "nvm_extra.h"

/*! \addtogroup NVRAM Manager
 *  @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * the defines
 ******************************************************************************/
struct _NvmType_;

/*******************************************************************************
 * the typedefs
 ******************************************************************************/
/*! \brief The return value type of the public method of the nvm module.
 */
typedef enum
{
    NVM_RETURN_OK     = 0X00,
    NVM_RETURN_NOT_OK = 0X01,
} Nvm_ReturnType;

/*! \brief Define block types.
 */
typedef enum
{
    NVM_BLOCK_NORMAL    = 0x00,
    NVM_BLOCK_REDUNDANT = 0x01,
    NVM_BLOCK_DATASET   = 0x02,
} Nvm_BlockOpType;

/*! \brief Used to define whether crc is required in a block.
 */
typedef enum
{
    NVM_CRC_NONE = 0x00,
    NVM_CRC8     = 0x01,
} Nvm_BlockCrcType;

/*! \brief Define the type of block state.
 */
typedef enum
{
    NVM_REQ_UNINT            = 0X00,
    NVM_REQ_PENDING          = 0X01,
    NVM_REQ_ERASE            = 0x02,
    NVM_REQ_NOT_OK           = 0x03,
    NVM_REQ_INTEGRITY_FAILED = 0x04,
    NVM_REQ_OK               = 0x05,
    NVM_REQ_ERROR            = 0xFF,
} Nvm_BlockState;

/*! \brief Define the type of NVM module state.
 */
typedef enum
{
    NVM_STATE_UNINIT   = 0x00,
    NVM_STATE_IDLE     = 0x01,
    NVM_STATE_READ     = 0x02,
    NVM_STATE_WRITE    = 0x03,
    NVM_STATE_READALL  = 0x04,
    NVM_STATE_WRITEALL = 0x05,
    NVM_STATE_ERASE    = 0x06,
    NVM_STATE_ERASEALL = 0x07,
    FEE_STATE_INVALID  = 0x08,
} Nvm_stateType;

/*! \brief Define the type of queue member status markers.
 */
typedef enum
{
    NVM_QUEUEMEMBERSTATE_UNUSED = 0x01,
    NVM_QUEUEMEMBERSTATE_USED   = 0x02,
    NVM_QUEUEMEMBERSTATE_LOCK   = 0x03,
} Nvm_QueueMemberStateType;

/*! \brief Define the type of state for NVM erase tasks.
 */
typedef enum
{
    NVM_ERASEFSM_INIT               = 0x01,
    NVM_ERASEFSM_IMMEDIATE          = 0x02,
    NVM_ERASEFSM_REDUNDANT_MAIN     = 0X03,
    NVM_ERASEFSM_REDUNDANT_BACKUP   = 0X04,
    NVM_ERASEFSM_READBACK           = 0x05,
    NVM_ERASEFSM_CHECK              = 0x06,
    NVM_ERASEFSM_FINISH             = 0x07,
    NVM_ERASEFSM_ERASEERROR         = 0x08,
    NVM_ERASEFSM_ERROR              = 0xFF,
} NVM_EraseFsmType;

/*! \brief Define the type of state that NVM writes to the job.
 */
typedef enum
{
    NVM_WRITEFSM_INIT               = 0x01,
    NVM_WRITEFSM_IMMEDIATE          = 0x02,
    NVM_WRITEFSM_READBACK           = 0x03,
    NVM_WRITEFSM_CHECK              = 0x04,
    NVM_WRITEFSM_NORMAL             = 0x05,
    NVM_WRITEFSM_REDUNDANT_MAIN     = 0x06,
    NVM_WRITEFSM_REDUNDANT_BACKUP   = 0X07,
    NVM_WRITEFSM_FINISH             = 0x08,
    NVM_WRITEFSM_WRITEERROR         = 0x09,
    NVM_WRITEFSM_ERROR              = 0xFF,
} NVM_WriteFsmType;

/*! \brief Define the type of NVM immediate read job status.
 */
typedef enum
{
    NVM_IMMEDIATEREADFSM_MAIN         = 0x01,
    NVM_IMMEDIATEREADFSM_MAIN_RETRY   = 0x02,
    NVM_IMMEDIATEREADFSM_WMF          = 0x03,
    NVM_IMMEDIATEREADFSM_FINISH       = 0x04,
    NVM_IMMEDIATEREADFSM_READERROR    = 0x05,
    NVM_IMMEDIATEREADFSM_ERROR        = 0xFF,
} NVM_ImmediateReadFsmType;

/*! \brief Define the type of state where NVM immediately writes jobs.
 */
typedef enum
{
    NVM_IMMEDIATEWRITEFSM_MAIN       = 0x01,
    NVM_IMMEDIATEWRITEFSM_RETRY      = 0x02,
    NVM_IMMEDIATEWRITEFSM_WMF        = 0x03,
    NVM_IMMEDIATEWRITEFSM_FINISH     = 0x04,
    NVM_IMMEDIATEWRITEFSM_WRITEERROR = 0x05,
    NVM_IMMEDIATEWRITEFSM_WAITMANAGE = 0X06,
    NVM_IMMEDIATEWRITEFSM_ERROR      = 0xFF,
} NVM_ImmediateWriteFsmType;

/*! \brief Define the type of state for nvm readAll job.
 */
typedef enum
{
    NVM_READALLFSM_READBLOCK = 0x01,
    NVM_READALLFSM_READENTRY = 0x02,
    NVM_READALLFSM_READ      = 0x03,
    NVM_READALLFSM_CHECK     = 0x04,
    NVM_READALLFSM_FINISH    = 0x05,
    NVM_READALLFSM_ERROR     = 0xFF,
} NVM_ReadAllFsmType;

/*! \brief Define the type of state for nvm writeAll job.
 */
typedef enum
{
    NVM_WRITEALLFSM_WRITEBLOCK = 0x01,
    NVM_WRITEALLFSM_WRITEENTRY = 0x02,
    NVM_WRITEALLFSM_WRITE      = 0x03,
    NVM_WRITEALLFSM_FINISH     = 0x04,
    NVM_WRITEALLFSM_ERROR      = 0xFF,
} NVM_WriteAllFsmType;

/*! \brief Define the type of state for nvm eraseAll job.
 */
typedef enum
{
    NVM_ERASEALLFSM_ERASEBLOCK = 0x01,
    NVM_ERASEALLFSM_ERASEENTRY = 0x02,
    NVM_ERASEALLFSM_ERASE      = 0x03,
    NVM_ERASEALLFSM_READBACK   = 0x04,
    NVM_ERASEALLFSM_FINISH     = 0x05,
    NVM_ERASEALLFSM_ERROR      = 0xFF,
} NVM_EraseAllFsmType;

/*! \brief Define the type of block management data.
 */
typedef struct _Nvm_BlockInfoType_
{
    Nvm_BlockState state;
    Nvm_BlockState internalState;
    uint8_t        integrity;
} Nvm_BlockInfoType;

/*! \brief Define the type of block buff.
 */
typedef struct _Nvm_BlockBuffType_
{
    const uint8_t* const romBuffPtr;
    uint8_t* const       ramBuffPtr;
} Nvm_BlockBuffType;

/*! \brief Define the type of state function.
 */
typedef void (*Nvm_StateMachine_Fun_Type)(const struct _NvmType_ *obj);

/*! \brief Define the types of queue members.
 */
typedef struct _Nvm_QueueMemberType_
{
    uint16_t                 blockIdx;
    uint8_t*                 databuff;
    uint16_t                 datasetIdx;
    Nvm_stateType            op;
    uint8_t                  priority;
    Nvm_QueueMemberStateType state;
} Nvm_QueueMemberType;

/*! \brief Define the type of queue.
 */
typedef struct _Nvm_QueueType_
{
    uint16_t                            index;
    const uint8_t                       memberNum;
    struct _Nvm_QueueMemberType_* const members;
} Nvm_QueueType;

/*! \brief Define the type of description block.
 */
typedef struct _Nvm_BlockItemType_
{
    uint16_t                          number;
    uint16_t                          dataSize;
    Nvm_BlockOpType                   type;
    uint8_t                           datasetNum;
    bool                              immediate;
    Nvm_BlockCrcType                  crc;
    uint8_t                           priority;
    const struct _Nvm_BlockBuffType_* buff;
    struct _Nvm_BlockInfoType_* const info;
    uint8_t* const                    tempRamBuffPtr;
} Nvm_BlockItemType;

/*! \brief Define the type of blocks.
 */
typedef struct _Nvm_BlockType_
{
    uint16_t                          itemsNum;
    const struct _Nvm_BlockItemType_* items;
} Nvm_BlockType;

/*! \brief Define the type of state machine.
 */
typedef struct _Nvm_StateMachineType_
{
    Nvm_StateMachine_Fun_Type onEntry;
    Nvm_StateMachine_Fun_Type fn;
} Nvm_StateMachineType;

/*! \brief Define the type of erase job.
 */
typedef struct _Nvm_EraseJobType_
{
    NVM_EraseFsmType     job;
    NVM_NotificationType result;
    uint16_t             blockIdx;
    uint16_t             blockNumber;
    uint8_t              datasetIdx;
    bool                 blockBackUp;
    uint8_t*             blockDatabuff;
    uint8_t*             userBuff;
    uint32_t             useSize;
} Nvm_EraseJobType;

/*! \brief Define the type of write job.
 */
typedef struct _Nvm_WriteJobType_
{
    NVM_WriteFsmType     job;
    NVM_NotificationType result;
    uint16_t             blockIdx;
    uint16_t             blockNumber;
    uint8_t              datasetIdx;
    bool                 blockBackUp;
    uint8_t*             blockDatabuff;
    uint8_t*             userBuff;
    uint32_t             useSize;
} Nvm_WriteJobType;

/*! \brief Define the type of read job.
 */
typedef struct _Nvm_ReadJobType_
{
    uint16_t blockIdx;
    uint8_t  datasetIdx;
    uint32_t datasize;
    uint8_t* userBuff;
    uint8_t* cpyBuff;
} Nvm_ReadJobType;

/*! \brief Define the type of writeAll job.
 */
typedef struct _Nvm_WriteAllJobType_
{
    NVM_WriteAllFsmType job;
    uint16_t            blockIdx;
    uint16_t            blockNumber;
    uint8_t             datasetIdx;
    bool                blockBackUp;
    uint8_t*            blockDatabuff;
    uint32_t            blockUseSize;
} Nvm_WriteAllJobType;

/*! \brief Define the type of eraseAll job.
 */
typedef struct _Nvm_EraseAllJobType_
{
    NVM_EraseAllFsmType job;
    uint16_t            blockIdx;
    uint16_t            blockNumber;
    uint8_t             datasetIdx;
    bool                blockBackUp;
    uint8_t*            blockDatabuff;
    uint8_t*            blockRombuff;
    uint32_t            blockUseSize;
} Nvm_EraseAllJobType;

/*! \brief Define the type of readAll job.
 */
typedef struct _Nvm_ReadAllJobType_
{
    NVM_ReadAllFsmType job;
    uint16_t           blockIdx;
    uint16_t           blockNumber;
    uint8_t            datasetIdx;
    bool               blockBackUp;
    uint8_t*           blockDatabuff;
    uint32_t           blockUseSize;
} Nvm_ReadAllJobType;

/*! \brief Define the type of immediateWrite job.
 */
typedef struct _Nvm_ImmediateWriteJobType_
{
    NVM_ImmediateWriteFsmType job;
    NvmNotificationPtrType    notificationPtr;
    uint16_t                  blockIdx;
    uint16_t                  blockNumber;
    uint8_t                   datasetIdx;
    uint8_t*                  blockDatabuff;
    uint8_t                   retry;
} Nvm_ImmediateWriteJobType;

/*! \brief Define the type of immediateRead job.
 */
typedef struct _Nvm_ImmediateReadJobType_
{
    NVM_ImmediateReadFsmType job;
    NvmNotificationPtrType   notificationPtr;
    uint16_t                 blockIdx;
    uint16_t                 blockNumber;
    uint8_t                  datasetIdx;
    uint8_t*                 blockDatabuff;
    uint32_t                 blockUseSize;
    uint8_t                  mainRetryCnt;
    uint8_t                  backupRetryCnt;
} Nvm_ImmediateReadJobType;

/*! \brief Define the type of NVM module runtime.
 */
typedef struct _Nvm_RunTimeType_
{
    Nvm_stateType                       state;
    Nvm_stateType                       nextState;
    struct _Nvm_QueueType_*             queue;
    struct _Nvm_EraseJobType_*          eraseJob;
    struct _Nvm_ReadJobType_*           readJob;
    struct _Nvm_WriteJobType_*          writeJob;
    struct _Nvm_ReadAllJobType_*        readAllJob;
    struct _Nvm_WriteAllJobType_*       writeAllJob;
    struct _Nvm_EraseAllJobType_*       eraseAllJob;
    struct _Nvm_ImmediateReadJobType_*  immediateReadJob;
    struct _Nvm_ImmediateWriteJobType_* immediateWriteJob;
} Nvm_RunTimeType;

/*! \brief Define the type of nvm.
 */
typedef struct _NvmType_
{
    const struct _Nvm_BlockType_*        blockTable;
    const struct _Nvm_StateMachineType_* stateMachine;
    const struct _Nvm_MethodType_*       method;
    struct _Nvm_RunTimeType_*            runtime;
} NvmType;
/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _NVM_TYPES_H_ */
