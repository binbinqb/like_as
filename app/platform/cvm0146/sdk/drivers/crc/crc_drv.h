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

#ifndef _CRC_DRV_H_
#define _CRC_DRV_H_

/*! \brief Contains public interface to various functions related
 *         to the driver of CRC module
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/*! \addtogroup crc_drv
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

/*! \brief CRC type of transpose of read write data
 */
typedef enum
{
    CRCDRV_TRANSPOSE_NONE           = 0, /*!< No transpose */
    CRCDRV_TRANSPOSE_BITS           = 1, /*!< Transpose bits in bytes */
    CRCDRV_TRANSPOSE_BITS_AND_BYTES = 2, /*!< Transpose bytes and bits in bytes */
    CRCDRV_TRANSPOSE_BYTES          = 3, /*!< Transpose bytes */
} CrcDrv_TransposeType;

/*! \brief CRC bit width
 */
typedef enum
{
    CRCDRV_BITWIDTH_16 = 0, /*!< No transpose */
    CRCDRV_BITWIDTH_32 = 1, /*!< Transpose bits in bytes */
} CrcDrv_BitWidthType;

/*! \brief Definition of configuration of CRC driver
 */
typedef struct _CrcDrv_ConfigType_
{
    CrcDrv_BitWidthType  crcWidth;           /*!< Selects 16-bit or 32-bit CRC protocol. */
    uint32_t             polynomial;         /*!< CRC Polynomial, MSBit first. */
    CrcDrv_TransposeType readTranspose;      /*!< Type of transpose when reading CRC result. */
    CrcDrv_TransposeType writeTranspose;     /*!< Type of transpose when writing CRC input data. */
    bool                 complementChecksum; /*!< True if the result shall be complement of the actual checksum. */
    uint32_t             seed;               /*!< Starting checksum value. */
} CrcDrv_ConfigType;

/* Forward declaration of CRC register */
struct _CrcRegType_;

/*! \brief The definition of CRC driver class
 */
typedef struct _CrcDrvType_
{
    struct _CrcRegType_ *reg;
} CrcDrvType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Initializes the CRC driver module
 *
 * This function initializes CRC driver by setting the register
 * instance to it.
 *
 * \param[in] obj : pointer to CRC driver instance
 * \param[in] reg : pointer to CRC register instance
 */
extern void CrcDrv_Init(CrcDrvType *obj, struct _CrcRegType_ *reg);

/*! \brief Configures the CRC module from a user configuration structure
 *
 * This function configures the CRC module from a user configuration structure
 *
 * \param[in] obj : pointer to CRC driver instance
 * \param[in] userConfig : pointer to configuration structure
 */
extern void CrcDrv_Configure(CrcDrvType *obj, const CrcDrv_ConfigType *userConfig);

/*! \brief Get configures of the CRC module currently
 *
 * This function gets configures of the CRC module currently
 *
 * \param[in] obj : pointer to CRC driver instance
 * \param[out] userConfig : pointer to configuration structure
 */
extern void CrcDrv_GetConfig(const CrcDrvType *obj, CrcDrv_ConfigType *userConfig);

/*! \brief Get default configures the CRC module for configuration structure
 *
 * This function gets default configures the CRC module for user configuration structure
 *
 * \note This function is a "static" function regardless of instances
 *
 * \param[out] userConfig : pointer to configuration structure
 */
extern void CrcDrv_GetDefaultConfig(CrcDrv_ConfigType *userConfig);

/*! \brief Sets a new seed to register CRC_INIT
 *
 * This function sets a new seed to register CRC_INIT
 * This operation will cause the value of register CRC_DR to be updated to the value of register CRC_INIT
 *
 * \param[in] obj : pointer to CRC driver instance
 * \param[in] seed : new seed will writed to CRC_INIT
 */
extern void CrcDrv_SetNewSeed(CrcDrvType *obj, uint32_t seed);

/*! \brief Executes CRC reset operation
 *
 * This function executes CRC reset operation
 * This opration will cause the value of register CRC_DR to be updated to the value of register CRC_INIT
 *
 * \param[in] obj : pointer to CRC driver instance
 */
extern void CrcDrv_CrcReset(CrcDrvType *obj);

/*! \brief Get the current result of the CRC calculation.
 *
 * This function returns the current result of the CRC calculation.
 *
 * \param[in] obj : pointer to CRC register instance
 * \return the current CRC calculation result
 */
extern uint32_t CrcDrv_GetCrcResult(CrcDrvType *obj);

/*! \brief Appends a block of 8 bits data to the current CRC calculation
 *
 * This function appends a block of 8 bits data to the current CRC calculation
 *
 * \param[in] obj : pointer to CRC driver instance
 * \param[in] data : pointer to input data for CRC calculation
 * \param[in] dataSize : length of 8 bits data to be calculated
 */
extern void CrcDrv_WriteData8(CrcDrvType *obj, const uint8_t *data, uint32_t dataSize);

/*! \brief Appends a block of 16 bits data to the current CRC calculation
 *
 * This function appends a block of 16 bits data to the current CRC calculation
 *
 * \param[in] obj : pointer to CRC driver instance
 * \param[in] data : pointer to input data for CRC calculation
 * \param[in] dataSize : length of 16 bits data to be calculated
 */
extern void CrcDrv_WriteData16(CrcDrvType *obj, const uint16_t *data, uint32_t dataSize);

/*! \brief Appends a block of 32 bits data to the current CRC calculation
 *
 * This function appends a block of 32 bits data to the current CRC calculation
 *
 * \param[in] obj : pointer to CRC driver instance
 * \param[in] data : pointer to input data for CRC calculation
 * \param[in] dataSize : length of 32 bits data to be calculated
 */
extern void CrcDrv_WriteData32(CrcDrvType *obj, const uint32_t *data, uint32_t dataSize);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _CRC_DRV_H_ */
