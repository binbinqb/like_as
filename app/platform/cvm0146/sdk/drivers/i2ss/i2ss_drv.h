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

#ifndef _I2SS_DRV_H_
#define _I2SS_DRV_H_

/*! \brief Contains public interface to various functions related
 *         to the driver of I2SS (I2S Slave)
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/*! \addtogroup i2ss_drv
 *  @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * the defines
 ******************************************************************************/
#define RX_FIFO_DEPTH (16U) /*!< the rx fifo depth */

/*******************************************************************************
 * the typedefs
 ******************************************************************************/
typedef enum
{
    I2SSDRV_IGNORE_WORD_LEN = 0x0U, /*!< Ignore the word length */
    I2SSDRV_RESOLUTION_12   = 0x1U, /*!< data resolution is 12 bits */
    I2SSDRV_RESOLUTION_16   = 0x2U, /*!< data resolution is 16 bits */
    I2SSDRV_RESOLUTION_20   = 0x3U, /*!< data resolution is 20 bits */
    I2SSDRV_RESOLUTION_24   = 0x4U, /*!< data resolution is 24 bits */
    I2SSDRV_RESOLUTION_32   = 0x5U  /*!< data resolution is 32 bits */
} I2ssDrvDataResolutionType;

/*! \brief The definition of I2SS driver class
 */
typedef struct _I2ssDrvType_
{
    struct _I2ssRegType_ *regI2ss;
    struct _SimRegType_  *regSim;
} I2ssDrvType;

typedef struct _I2ssDrv_ConfigType_
{
    I2ssDrvDataResolutionType dataResolution;       /*!< data resolution of the receiver */
    uint8_t                   rxFifoTriggerLevel;   /*!< the threshold level of the rx fifo trigger */
    bool                      rxFifoEmptyIntMask;   /*!< RXFE interrupt mask */
    bool                      rxFifoOverrunIntMask; /*!< RXFO interrupt mask */
} I2ssDrv_ConfigType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Initializes the I2SS reg
 *
 *
 * \param[in] obj : pointer to I2SS driver instance
 * \param[in] reg1 : pointer to I2SS register instance
 * \param[in] reg2 : pointer to SIM register instance
 */
extern void I2ssDrv_Init(I2ssDrvType *obj, struct _I2ssRegType_ *reg1, struct _SimRegType_ *reg2);

/*! \brief Get default configures the I2SS module for configuration structure
 *
 *
 * \param[in] userConfig : pointer to user config sturcture
 */
extern void I2ssDrv_GetDefaultConfig(I2ssDrv_ConfigType *userConfig);

/*! \brief config the I2SS module as userConfig
 *
 *
 * \param[in] obj : pointer to I2SS driver instance
 * \param[in] userConfig : pointer to user config sturcture
 */
extern void I2ssDrv_Config(I2ssDrvType *obj, const I2ssDrv_ConfigType *userConfig);

/*! \brief read data from rx FIFO via DMA
 *
 *
 * \param[in] obj : pointer to I2SS driver instance
 * \param[in] data : pointer to user data
 * \param[in] len : the data length to transfer
 */
extern void I2ssDrv_ReadFifoByDma(I2ssDrvType *obj, uint32_t *data, uint8_t len);

/*! \brief read data from rx FIFO via buffer
 *
 *
 * \param[in] obj : pointer to I2SS driver instance
 * \param[in] data : pointer to user data
 * \param[in] len : the data length to transfer
 */
extern void I2ssDrv_ReadFifoByBuffer(I2ssDrvType *obj, uint32_t *data, uint8_t len);

/*! \brief flush the rx fifo
 *
 *
 * \param[in] obj : pointer to I2SS driver instance
 */
extern void I2ssDrv_FlushRxFifo(I2ssDrvType *obj);

/*! \brief get the status flag of fifo overrun
 *
 *
 * \param[in] obj : pointer to I2SS driver instance
 * \param[out] bool : flag status
 *             - false : not overrun
 *             - true : overrun
 */
extern bool I2ssDrv_GetFifoOverrunFlag(I2ssDrvType *obj);

/*! \brief get the status flag of fifo level trig
 *
 *
 * \param[in] obj : pointer to I2SS driver instance
 * \param[out] bool : flag status
 *             - false : not reach the trig level
 *             - true : reach the trig level
 */
extern bool I2ssDrv_GetFifoLevelTrigFlag(I2ssDrvType *obj);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _I2SS_DRV_H_ */
