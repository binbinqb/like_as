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

#ifndef _I2SM_DRV_H_
#define _I2SM_DRV_H_

/*! \brief Contains public interface to various functions related
 *         to the driver of I2SM (I2S Master)
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/*! \addtogroup i2sm_drv
 *  @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * the defines
 ******************************************************************************/
#define TX_FIFO_DEPTH (16U) /*!< the tx fifo depth */

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

typedef enum
{
    I2SMDRV_CLOCK_CYCLES_16 = 0x0U, /*!< word select line stays 16 sclk cycles for left or right sample */
    I2SMDRV_CLOCK_CYCLES_24 = 0x1U, /*!< word select line stays 24 sclk cycles for left or right sample */
    I2SMDRV_CLOCK_CYCLES_32 = 0x2U  /*!< word select line stays 32 sclk cycles for left or right sample */
} I2smDrvWssType;

typedef enum
{
    I2SMDRV_NO_CLOCK_GATE = 0x0U, /*!< clock gate is disabled */
    I2SMDRV_CLOCK_GATE_12 = 0x1U, /*!< clock gate is setting at 12 cycles */
    I2SMDRV_CLOCK_GATE_16 = 0x2U, /*!< clock gate is setting at 16 cycles */
    I2SMDRV_CLOCK_GATE_20 = 0x3U, /*!< clock gate is setting at 20 cycles */
    I2SMDRV_CLOCK_GATE_24 = 0x4U  /*!< clock gate is setting at 24 cycles */
} I2smDrvSclkGateType;

typedef enum
{
    I2SMDRV_IGNORE_WORD_LEN = 0x0U, /*!< Ignore the word length */
    I2SMDRV_RESOLUTION_12   = 0x1U, /*!< data resolution is 12 bits */
    I2SMDRV_RESOLUTION_16   = 0x2U, /*!< data resolution is 16 bits */
    I2SMDRV_RESOLUTION_20   = 0x3U, /*!< data resolution is 20 bits */
    I2SMDRV_RESOLUTION_24   = 0x4U, /*!< data resolution is 24 bits */
    I2SMDRV_RESOLUTION_32   = 0x5U  /*!< data resolution is 32 bits */
} I2smDrvDataResolutionType;

/*! \brief The definition of I2SM driver class
 */
typedef struct _I2smDrvType_
{
    struct _I2smRegType_ *regI2sm;
    struct _SimRegType_  *regSim;
} I2smDrvType;

typedef struct _I2smDrv_ConfigType_
{
    I2smDrvWssType            wsCycle;              /*!< number of clk cyles for ws line in left or right sample mode */
    I2smDrvSclkGateType       sclkGateCycle;        /*!< clock gate of the sclk */
    I2smDrvDataResolutionType dataResolution;       /*!< data resolution of the transmitter */
    uint8_t                   txFifoTriggerLevel;   /*!< the threshold level of the tx fifo trigger */
    bool                      txFifoEmptyIntMask;   /*!< TXFE interrupt mask */
    bool                      txFifoOverrunIntMask; /*!< TXFO interrupt mask */
} I2smDrv_ConfigType;
/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Initializes the I2SM reg
 *
 *
 * \param[in] obj : pointer to I2SM driver instance
 * \param[in] reg1 : pointer to I2SM register instance
 * \param[in] reg2 : pointer to SIM register instance
 */
extern void I2smDrv_Init(I2smDrvType *obj, struct _I2smRegType_ *reg1, struct _SimRegType_ *reg2);

/*! \brief Get default configures the I2SM module for configuration structure
 *
 *
 * \param[in] userConfig : pointer to user config sturcture
 */
extern void I2smDrv_GetDefaultConfig(I2smDrv_ConfigType *userConfig);

/*! \brief config the I2SM module as userConfig
 *
 *
 * \param[in] obj : pointer to I2SM driver instance
 * \param[in] userConfig : pointer to user config sturcture
 */
extern void I2smDrv_Config(I2smDrvType *obj, const I2smDrv_ConfigType *userConfig);

/*! \brief fill the tx FIFO via DMA
 *
 *
 * \param[in] obj : pointer to I2SM driver instance
 * \param[in] data : pointer to user data
 * \param[in] len : the data length to transfer
 */
extern void I2smDrv_FillFifoByDma(I2smDrvType *obj, uint32_t *data, uint8_t len);

/*! \brief fill the tx FIFO via buffer
 *
 *
 * \param[in] obj : pointer to I2SM driver instance
 * \param[in] data : pointer to user data
 * \param[in] len : the data length to transfer
 */
extern void I2smDrv_FillFifoByBuffer(I2smDrvType *obj, uint32_t *data, uint8_t len);

/*! \brief start transmit data
 *
 *
 * \param[in] obj : pointer to I2SM driver instance
 */
extern void I2smDrv_StartTransmit(I2smDrvType *obj);

/*! \brief stop transmit data
 *
 *
 * \param[in] obj : pointer to I2SM driver instance
 */
extern void I2smDrv_StopTransmit(I2smDrvType *obj);

/*! \brief flush the tx fifo
 *
 *
 * \param[in] obj : pointer to I2SM driver instance
 */
extern void I2smDrv_FlushTxFifo(I2smDrvType *obj);

/*! \brief get the status flag of fifo overrun
 *
 *
 * \param[in] obj : pointer to I2SM driver instance
 * \param[out] bool : flag status
 *             - false : not overrun
 *             - true : overrun
 */
extern bool I2smDrv_GetFifoOverrunFlag(I2smDrvType *obj);

/*! \brief get the status flag of fifo level trig
 *
 *
 * \param[in] obj : pointer to I2SM driver instance
 * \param[out] bool : flag status
 *             - false : not reach the trig level
 *             - true : reach the trig level
 */
extern bool I2smDrv_GetFifoLevelTrigFlag(I2smDrvType *obj);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _I2SM_DRV_H_ */
