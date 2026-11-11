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

#ifndef _FEE_H_
#define _FEE_H_

/*! \brief Contains public interface to various functions related
 *         to the FEE (Flash EEPROM Emulation) module
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "fee_types.h"
#include "fee_extra.h"
#include "fee_version.h"

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

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Configures the FEE driver
 *
 * This function configures the FEE driver
 *
 * \param[in] obj : pointer to FEE driver instance
 */
extern void Fee_Configure(const FeeType *obj);

/*! \brief Main function of FEE driver
 *
 * This function is the main process of running the FEE driver
 *
 * \param[in] obj : pointer to FEE driver instance
 */
extern void Fee_MainFunction(const FeeType *obj);

/*! \brief Read the data from FEE
 *
 * This function reads the data from FEE with given parameters
 *
 * \param[in] obj : pointer to FEE driver instance
 * \param[in] blockNumber : block number to read
 * \param[in] blockOffset : offset of dataset defined by user in block
 * \param[out] dataBuffer : pointer to the result data buffer
 * \param[in] notificationPtr : pointer to the notification callback function
 */
extern Fee_ReturnType Fee_Read(const FeeType *obj, uint16_t blockNumber, uint16_t blockOffset, uint8_t *dataBuffer, NotificationPtrType notificationPtr);

/*! \brief Write the data to FEE
 *
 * This function writed the data to FEE with given parameters
 *
 * \param[in] obj : pointer to FEE driver instance
 * \param[in] blockNumber : block number to write
 * \param[in] dataBuffer : pointer to the data buffer to write
 * \param[in] notificationPtr : pointer to the notification callback function
 */
extern Fee_ReturnType Fee_Write(const FeeType *obj, uint16_t blockNumber, uint8_t *dataBuffer, NotificationPtrType notificationPtr);

/*! \brief Cancel the newest request
 *
 * This function cancels the newest request in the request buffer
 *
 * \param[in] obj : pointer to FEE driver instance
 */
extern Fee_ReturnType Fee_Cancel(const FeeType *obj);

/*! \brief Get the prev job result
 *
 * This function gets the prev job result of block
 *
 * \param[in] obj : pointer to FEE driver instance
 */
extern Fee_JobResultType Fee_GetJobResult(const FeeType *obj);

/*! \brief Get the current running status
 *
 * This function gets the current running status of FEE
 *
 * \param[in] obj : pointer to FEE driver instance
 */
extern Fee_StatusType Fee_GetStatus(const FeeType *obj);

/*! \brief Get the version information of this driver
 *
 * This function gets the version information of this driver.
 *
 * \param[out] versionInfoPtr : pointer to the version object
 */
extern void Fee_GetVersionInfo(Fee_VersionInfoType *versionInfoPtr);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _FEE_H_ */
