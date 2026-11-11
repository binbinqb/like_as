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

#ifndef _NVM_BLOCK_H_
#define _NVM_BLOCK_H_

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
/*! \brief Define a macro for rampoff initialization data.
 */
#define NVM_BLOCK_RAMBUFF_DEFAULT_VALUE                                 (0x00)

/*! \brief Macro defining invalid block index.
 */
#define NVM_BLOCK_INVALID_IDX                                           (0xFFFF)

/*! \brief Define macros with invalid datasets.
 */
#define NVM_DATASET_INVALID_IDX                                         (0xFFFF)

/*! \brief The highest priority macro for the job.
 */
#define NVM_BLOCK_HIGHT_PRIORITY                                        (0)

/*! \brief Define the placeholder length for the effective storage of data in a block.
 */
#define NVM_BLOCK_PLACEHOLDER_BYTES                                     (0)

/*! \brief Define the CRC length for effective storage of data in a block.
 */
#define NVM_BLOCK_CRC_BYTES                                             (1)

/*! \brief Define macros that failed data validation.
 */
#define NVM_BLOCK_CRC_FAIL_MASK                                         (0x00)

/*! \brief Define macros for successful data validation.
 */
#define NVM_BLOCK_CRC_OK_MASK                                           (0x01)

/*! \brief Macro that defines the dataset value of the main region.
 */
#define NVM_BLOCK_MAIN_IDX                                              (0)

/*! \brief Macro that defines the dataset value of the backup region.
 */
#define NVM_BLOCK_BACKUP_IDX                                            (1)

/*! \brief Macro defining the number of failed retry attempts for request feed operations.
 */
#define NVM_BLOCK_RETRY_NUM                                             (3)

/*! \brief Define a macro to determine whether the block type is immediate.
 */
#define NVM_BLOCK_IS_IMMEDIATE(obj, blockIdx)                           (obj->items[blockIdx].immediate)

/*! \brief Define a macro to determine whether the block is configured with CRC.
 */
#define NVM_BLOCK_IS_CRC(obj, blockIdx)                                 (NVM_CRC8 == obj->items[blockIdx].crc)

/*! \brief Define a macro to determine whether a block is of normal type.
 */
#define NVM_BLOCK_IS_NORMAL(obj, blockIdx)                              (NVM_BLOCK_NORMAL == obj->items[blockIdx].type)

/*! \brief Define a macro to determine whether a block is a redundant type.
 */
#define NVM_BLOCK_IS_REDUNDANT(obj, blockIdx)                           (NVM_BLOCK_REDUNDANT == obj->items[blockIdx].type)

/*! \brief Define a macro to determine whether a block is a dataset type.
 */
#define NVM_BLOCK_IS_DATASET(obj, blockIdx)                             (NVM_BLOCK_DATASET == obj->items[blockIdx].type)

/*! \brief Define a macro to obtain the datasetN checksum bit in a block.
 */
#define NVM_BLOCK_GET_INTEGRITY(obj, blockIdx, datasetIdx)              (obj->items[blockIdx].info[datasetIdx].integrity)

/*! \brief Define a macro to obtain the status of datasetN in a block.
 */
#define NVM_BLOCK_GET_STATE(obj, blockIdx, datasetIdx)                  (obj->items[blockIdx].info[datasetIdx].state)

/*! \brief Define a macro to obtain the internal management status of datasetN in a block.
 */
#define NVM_BLOCK_GET_INT_STATE(obj, blockIdx, datasetIdx)              (obj->items[blockIdx].info[datasetIdx].internalState)

/*! \brief Define a macro to obtain the number of datasets in a block.
 */
#define NVM_BLOCK_GET_DATASETNUM(obj, blockIdx)                         (obj->items[blockIdx].datasetNum)

/*! \brief Define macros for obtaining priority in blocks.
 */
#define NVM_BLOCK_GET_PRIORITY(obj, blockIdx)                           (obj->items[blockIdx].priority)

/*! \brief Define macros for obtaining blockrambuff addresses.
 */
#define NVM_BLOCK_GET_RAM_BUFF_PTR(obj, blockIdx, datasetIdx)           ((uint8_t *)obj->items[blockIdx].buff[datasetIdx].ramBuffPtr)

/*! \brief Define macros for obtaining block tempbuff addresses.
 */
#define NVM_BLOCK_GET_TEMP_RAM_BUFF_PTR(obj, blockIdx)                  ((uint8_t *)obj->items[blockIdx].tempRamBuffPtr)

/*! \brief Define macros for obtaining block rombuff addresses.
 */
#define NVM_BLOCK_GET_ROM_BUFF_PTR(obj, blockIdx, datasetIdx)           ((uint8_t *)obj->items[blockIdx].buff[datasetIdx].romBuffPtr)

/*! \brief Define macros for obtaining block data length.
 */
#define NVM_BLOCK_GET_DATASIZE(obj, blockIdx)                           (obj->items[blockIdx].dataSize)

/*! \brief Define macros for obtaining block crc length.
 */
#define NVM_BLOCK_GET_CRC_LEN(obj, blockIdx)                            (obj->items[blockIdx].dataSize + NVM_BLOCK_PLACEHOLDER_BYTES)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/
void     Nvm_Block_Init(const Nvm_BlockType *obj);
void     Nvm_Block_DataRepair(const Nvm_BlockType *obj, const Nvm_MethodType *method, uint16_t blockIdx, uint16_t datasetIdx);
void     Nvm_Block_SetDefaultVal(const Nvm_BlockType *obj, const Nvm_MethodType *method, uint16_t blockIdx, uint16_t datasetIdx);
void     Nvm_Block_ClrRamBuff(const Nvm_BlockType *obj, uint16_t blockIdx, uint16_t datasetIdx);
void     Nvm_Block_ClrBlockRamBuff(const Nvm_BlockType *obj, uint16_t blockIdx, uint16_t datasetIdx);
void     Nvm_Block_SetState(const Nvm_BlockType *obj, uint16_t blockIdx, uint16_t datasetIdx, Nvm_BlockState state);
void     Nvm_Block_SetInternalState(const Nvm_BlockType *obj, uint16_t blockIdx, uint16_t datasetIdx, Nvm_BlockState state);
void     Nvm_Block_SetTempRamBuffDefaultVal(const Nvm_BlockType *obj, uint16_t blockIdx, uint16_t datasetIdx);
uint32_t Nvm_Block_CalcUseSize(const Nvm_BlockType *obj, uint16_t blockIdx);
void     Nvm_Block_GetRomData(const Nvm_BlockType *obj, uint16_t blockIdx, uint8_t datasetIdx, uint8_t *data);
bool     Nvm_Block_GetWriteData(const Nvm_BlockType *obj, uint16_t blockIdx, uint8_t datasetIdx, const Nvm_MethodType *method, uint8_t *data);
void     Nvm_Block_WriteDataToBuff(const Nvm_BlockType *obj, const Nvm_MethodType *method, uint16_t blockIdx, uint16_t datasetIdx, uint8_t *data);
void     Nvm_Block_IntegrityCheck(const Nvm_BlockType *obj, uint16_t blockIdx, uint8_t ecu, const Nvm_MethodType *method);
void     Nvm_Block_WriteDataToRamBlock(const Nvm_BlockType *obj, const Nvm_MethodType *method, uint16_t blockIdx, uint16_t datasetIdx, uint8_t *data);
uint16_t Nvm_Block_Search(const Nvm_BlockType *obj, uint16_t blockNumber);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _NVM_BLOCK_H_ */
