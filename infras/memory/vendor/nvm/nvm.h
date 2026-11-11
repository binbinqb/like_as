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

#ifndef _NVM_H_
#define _NVM_H_

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
#include "nvm_version.h"

/*! \addtogroup NVRAM Manager
 *  @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * the defines
 ******************************************************************************/
/*! \brief Macro for the value range of the nvm module dataset section.
 */
#ifndef NVM_DATASET_SELECTION_BITS
#define NVM_DATASET_SELECTION_BITS              (4)
#endif

/*! \brief Macro for masking the value range of the nvm module dataset section.
 */
#define NVM_DATASET_SELECTION_MASK              ((1 << NVM_DATASET_SELECTION_BITS) - 1)

/*! \brief Macro for masking the value range of the nvm module dataset section.
 */
#define NVM_NUMBER_SELECTION_MASK               (~NVM_DATASET_SELECTION_MASK)

/*! \brief Macro for NVM module to obtain block id field in blocknumber.
 */
#define NVM_GET_BLOCKNUMBER(blockNumber)        (blockNumber & NVM_NUMBER_SELECTION_MASK)

/*! \brief NVM module obtains macro for dataset field in blocknumber.
 */
#define NVM_GET_BLOCKDATASETNUMBER(blockNumber) (blockNumber & NVM_DATASET_SELECTION_MASK)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Configures the NVM driver
 *
 * This function configures the NVM driver
 *
 * \param[in] obj : pointer to NVM driver instance
 */
extern void Nvm_Configure(const NvmType *obj);

/*! \brief Main function of NVM driver
 *
 * This function is the main process of running the NVM driver
 *
 * \param[in] obj : pointer to NVM driver instance
 */
extern void Nvm_MainFunction(const NvmType *obj);

/*! \brief Read the data from NVM
 *
 * This function reads the data from NVM with given parameters
 *
 * \param[in] obj : pointer to NVM driver instance
 * \param[in] block : block to read
 * \param[out] dataBuffer : pointer to the result data buffer
 * \param[in] notificationPtr : pointer to the notification callback function
 */
extern Nvm_ReturnType Nvm_Read(const NvmType *obj, uint16_t blockNumber, uint8_t *dataBuffer);

/*! \brief Read the all block data to NVM
 *
 * This function reads the data from NVM with given parameters
 *
 * \param[in] obj : pointer to NVM driver instance
 */
extern Nvm_ReturnType Nvm_ReadAll(const NvmType *obj);

/*! \brief Write the data to NVM
 *
 * This function writed the data to NVM with given parameters
 *
 * \param[in] obj : pointer to FEE driver instance
 * \param[in] block : block number to write
 * \param[in] dataBuffer : pointer to the data buffer to write
 * \param[in] notificationPtr : pointer to the notification callback function
 */
extern Nvm_ReturnType Nvm_Write(const NvmType *obj, uint16_t blockNumber, uint8_t *dataBuffer);

/*! \brief Write the all block data
 *
 * This function writed the data to NVM with given parameters
 *
 * \param[in] obj : pointer to FEE driver instance
 */
extern Nvm_ReturnType Nvm_WriteAll(const NvmType *obj);

/*! \brief Erase NVM Block
 *
 * This function Erase NVM Block with given parameters
 *
 * \param[in] obj : pointer to FEE driver instance
 * \param[in] blockNumber : block to write
 */
extern Nvm_ReturnType Nvm_Erase(const NvmType *obj, uint16_t blockNumber);

/*! \brief Erase NVM All Block
 *
 * This function Erase NVM All Block with given parameters
 *
 * \param[in] obj : pointer to FEE driver instance
 */
extern Nvm_ReturnType Nvm_EraseAll(const NvmType *obj);

/*! \brief Get Nvm Status
 *
 * This function Get NVM module status with given parameters
 *
 * \param[in] obj : pointer to FEE driver instance
 */
extern Nvm_stateType Nvm_GetStatus(const NvmType *obj);

/*! \brief Cancel Nvm Job
 *
 * This function Cancel NVM Queue Last Job
 *
 * \param[in] obj : pointer to FEE driver instance
 */
extern void Nvm_CancelJob(const NvmType *obj);

/*! \brief Get Block Status
 *
 * This function Get NVM Block status with given parameters
 *
 * \param[in] obj : pointer to FEE driver instance
 * \param[in] blockNumber : block
 */
extern Nvm_BlockState Nvm_GetBlockStatus(const NvmType *obj, uint16_t blockNumber);

/*! \brief Get the version information of this driver
 *
 * This function gets the version information of this driver.
 *
 * \param[out] versionInfoPtr : pointer to the version object
 */
extern void Nvm_GetVersionInfo(Nvm_VersionInfoType *versionInfoPtr);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _NVM_H_ */
