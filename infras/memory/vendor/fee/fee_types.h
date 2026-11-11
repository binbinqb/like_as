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

#ifndef _FEE_TYPES_H_
#define _FEE_TYPES_H_

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdio.h>
#include "fee_sector.h"
#include "fee_jobs.h"
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

/*! \brief The return value type of the public method of the fee module.
 */
typedef enum
{
    FEE_RETURN_OK     = 0X00,
    FEE_RETURN_NOT_OK = 0X01,
} Fee_ReturnType;

/*! \brief fee module global state type.
 */
typedef enum
{
	FEE_STATUS_UNINIT = 0x00,
    FEE_STATUS_IDLE   = 0x01,
    FEE_STATUS_READ   = 0x02,
    FEE_STATUS_WRITE  = 0x03,
    FEE_STATUS_GC     = 0x04,
    FEE_STATUS_UNKNOW = 0x05,
    FEE_STATUS_ERROR  = 0x06,
} Fee_StatusType;

/*! \brief Returns the type of result that the module has processed this request.
 */
typedef enum
{
    FEE_JOB_RESULT_OK              = 0x00,
    FEE_JOB_RESULT_NOT_OK          = 0x01,
    FEE_JOB_RESULT_PENDING         = 0x02,
    FEE_JOB_RESULT_BL_INCONSISTENT = 0x03,
    FEE_JOB_RESULT_BL_INVALID      = 0x04,
} Fee_JobResultType;

/*! \brief Internal main state type of the fee module.
 */
typedef enum
{
    FEE_MAIN_FUN_FSM_INITIALIZATION = 0x00,
    FEE_MAIN_FUN_FSM_RETRIEVAL      = 0x01,
    FEE_MAIN_FUN_FSM_IDLE           = 0X02,
    FEE_MAIN_FUN_FSM_READ           = 0x03,
    FEE_MAIN_FUN_FSM_WRITE          = 0x04,
    FEE_MAIN_FUN_FSM_GC             = 0x05,
    FEE_MAIN_FUN_FSM_ERROR          = 0x06,
} Fee_MainFunFsmType;

/*! \brief The configuration type of the fee.
 */
typedef struct _Fee_ConfigType_
{
    uint32_t blockSize;
} Fee_ConfigType;

/*! \brief The sub state type of the initialization main state of the fee module.
 */
typedef enum
{
    FEE_INITIALIZATION_SECTOR                           = 0x00,
    FEE_INITIALIZATION_CHECK_SECTOR                     = 0x01,
    FEE_INITIALIZATION_FIND_ACTIVE_SECTOR               = 0x02,
    FEE_INITIALIZATION_GC_REPAIR_SECTOR                 = 0x03,
    FEE_INITIALIZATION_ERASE_SECTOR                     = 0x04,
    FEE_INITIALIZATION_UNINITIALIZATION_ERASE_SECTOR    = 0x05,
    FEE_INITIALIZATION_UNINITIALIZATION                 = 0X06,
    FEE_INITIALIZATION_FINISH                           = 0x07,
    FEE_INITIALIZATION_ERROR                            = 0x08,
} Fee_InitializationFsmType;

/*! \brief The sub state type of the feed's main page fee module state.
 */
typedef enum
{
    FEE_GC_INIT               = 0x00,
    FEE_GC_ERASE_BACKUPSECTOR = 0x01,
    FEE_GC_START              = 0x02,
    FEE_GC_FOUND_BLOCK        = 0x03,
    FEE_GC_COPY               = 0x04,
    FEE_GC_ERASE_ACTIVESECTOR = 0x05,
    FEE_GC_FINISH             = 0x06,
    FEE_GC_ERROR              = 0x07,
} Fee_GcFsmType;

/*! \brief The sub state type of the copy sub state of the feed's main page fee module state.
 */
typedef enum
{
    FEE_GC_COPY_WRITE_MARK = 0x01,
    FEE_GC_COPY_INIT       = 0x02,
    FEE_GC_COPY_WRITEBLOCK = 0x04,
    FEE_GC_COPY_FINISH     = 0x05,
    FEE_GC_COPY_ERROR      = 0x06,
} Fee_GcCopyFsmType;

/*! \brief Define the type of copy sub state execution results for the feed's main page fee module state.
 */
typedef enum
{
    FEE_GC_STATE_NO_ERROR                  = 0x00,
    FEE_GC_STATE_UNKNOW_ERROR              = 0x01,
    FEE_GC_STATE_WRITE_ERROR               = 0x02,
    FEE_GC_STATE_READ_ERROR                = 0x03,
    FEE_GC_STATE_NOT_FOUND_BACKUPSECTOR    = 0x04,
    FEE_GC_STATE_ERASE_BACKUP_SECTOR_ERROR = 0x05,
    FEE_GC_STATE_WRITE_INIT_MARK_ERROR     = 0x06,
    FEE_GC_STATE_COPY_ERROR                = 0x07,
    FEE_GC_STATE_ERASE_ACTIVE_SECTOR_ERROR = 0x08,
    FEE_GC_STATE_WRITE_ENA_MARK_ERROR      = 0x09,
} Fee_GcCopyStateType;

/*! \brief Defines the type of runtime for page fee module.
 */
typedef struct _Fee_GcRuntimeType_
{
    Fee_GcFsmType                        gcFsm;
    Fee_GcCopyFsmType                    copyFsm;
    const struct _Fee_SectorConfigType_* backupSector;
    uint32_t                             blockCnt;
    const struct _Fee_BlockType_*        currentBlock;
    Fee_AddressType                      searchAddr;
    Fee_AddressType                      copySrcDataAddr;
    Fee_GcCopyStateType                  state;
} Fee_GcRuntimeType;

/*! \brief Define the type of feed module runtime.
 */
typedef struct _Fee_RunTimeType_
{
    Fee_MainFunFsmType                      mainFunFsm;
    Fee_InitializationFsmType               initializationFsm;
    struct _Fee_JobsType_* const            jobs;
    const struct _Fee_SectorConfigType_*    activeSector;
    struct _Fee_JobControlBlockType_* const job;
    struct _Fee_GcRuntimeType_* const       gcRuntime;
    Fee_JobResultType                       jobResult;
} Fee_RunTimeType;

/*! \brief Define the type of the fee object.
 */
typedef struct _FeeType_
{
    const struct _Fee_SectorType_* sector;
    const struct _Fee_MethodType_* flsMethod;
    struct _Fee_RunTimeType_*      runtime;
    void* const                    buff;
} FeeType;

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

#endif /* _FEE_TYPES_H_ */
