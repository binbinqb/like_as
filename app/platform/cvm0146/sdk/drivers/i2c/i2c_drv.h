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

#ifndef _I2C_DRV_H
#define _I2C_DRV_H

/*! \brief Contains public interface to various functions related
 *         to the driver of I2C module
 */

/******************************************************************************
 * the includes
 *****************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "i2c_reg.h"

/*! \addtogroup i2c_drv
 *  @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 * the defines
 *****************************************************************************/
#define I2CDRV_STANDARDSPEED_UPPER_FREQ_VALUE (100000ul)  /* Hz */
#define I2CDRV_FASTSPEED_UPPER_FREQ_VALUE     (1000000ul) /* Hz */

#define I2CDRV_TX_FIFO_DEPTH                  (16u)
#define I2CDRV_RX_FIFO_DEPTH                  (16u)

/******************************************************************************
 * the typedefs
 *****************************************************************************/
/*! \brief I2C node cosplayer */
typedef enum
{
    I2CDRV_NODE_MODE_AS_SLAVE = 0u,
    I2CDRV_NODE_MODE_AS_MASTER
} I2cDrv_NodeModeType;

/*! \brief I2C address bit type */
typedef enum
{
    I2CDRV_ADDR_MODE_7BIT = 0u,
    I2CDRV_ADDR_MODE_10BIT
} I2cDrv_AddressModeType;

/*! \brief I2C speed mode selection */
typedef enum
{
    I2CDRV_SPEED_MODE_STANDARD_100KBIT = 1u,
    I2CDRV_SPEED_MODE_FAST_400KBIT_1000KBIT,
    I2CDRV_SPEED_MODE_HIGH /* Not support in the current IP */
} I2cDrv_SpeedModeType;

/*! \brief I2C APB data width type */
typedef enum
{
    I2CDRV_APB_DATA_WIDTH_8BIT = 0u,
    I2CDRV_APB_DATA_WIDTH_16BIT,
    I2CDRV_APB_DATA_WIDTH_32BIT
} I2cDrv_ApbDataWidthType;

/*! \brief I2C special command selection */
typedef enum
{
    I2CDRV_SPECIAL_CMD_GENERAL_CALL = 0u,
    I2CDRV_SPECIAL_CMD_START_BYTE
} I2cDrv_SpecialCmdType;

/*! \brief I2C detect stop bit condition */
typedef enum
{
    I2CDRV_SLAVE_DETECT_STOPBIT_CONDITION_IN_ANYTIME = 0u,
    I2CDRV_SLAVE_DETECT_STOPBIT_CONDITION_IN_ADDR_MATCH
} I2cDrv_SlaveDetectStopBitConditionType;

/*! \brief I2C tx empty control selection */
typedef enum
{
    I2CDRV_TX_EMPTY_AT_TXFIFO_LESSTHAN_TXTL = 0u,
    I2CDRV_TX_EMPTY_AT_LAST_DATA_TRANSFERED
} I2cDrv_TxEmptyCtrlType;

/*! \brief Interrupt source */
typedef enum
{
    I2CDRV_ISR_SRC_RX_UNDER  = I2C_INTR_STAT_RX_UNDER_MASK,
    I2CDRV_ISR_SRC_RX_OVER   = I2C_INTR_STAT_RX_OVER_MASK,
    I2CDRV_ISR_SRC_RX_FULL   = I2C_INTR_STAT_RX_FULL_MASK,
    I2CDRV_ISR_SRC_TX_OVER   = I2C_INTR_STAT_TX_OVER_MASK,
    I2CDRV_ISR_SRC_TX_EMPTY  = I2C_INTR_STAT_TX_EMPTY_MASK,
    I2CDRV_ISR_SRC_RD_REQ    = I2C_INTR_STAT_RD_REQ_MASK,
    I2CDRV_ISR_SRC_TX_ABRT   = I2C_INTR_STAT_TX_ABRT_MASK,
    I2CDRV_ISR_SRC_RX_DONE   = I2C_INTR_STAT_RX_DONE_MASK,
    I2CDRV_ISR_SRC_ACTIVITY  = I2C_INTR_STAT_ACTIVITY_MASK,
    I2CDRV_ISR_SRC_STOP_DET  = I2C_INTR_STAT_STOP_DET_MASK,
    I2CDRV_ISR_SRC_START_DET = I2C_INTR_STAT_START_DET_MASK,
    I2CDRV_ISR_SRC_GEN_CALL  = I2C_INTR_STAT_GEN_CALL_MASK,
    I2CDRV_ISR_SRC_ALL       = 0XFFF
} I2cDrv_IsrSrcType;

/*! \brief I2C basic parameter information */
typedef struct _I2cDrv_BasicParametersType_
{
    uint32_t               busClockFreq;
    uint32_t               sclFreq;
    I2cDrv_NodeModeType    nodeMode;
    uint16_t               ownAddress;
    uint16_t               targetAddress;
    I2cDrv_AddressModeType addressMode;
    bool                   restartBitEn;
    I2cDrv_SpeedModeType   speedMode;
} I2cDrv_BasicParametersType;

/*! \brief I2C extend parameter information */
typedef struct _I2cDrv_ExtendParametersType_
{
    uint16_t                               spikeSuppressionTime_ns;
    uint16_t                               rxHoldTime_ns;
    uint16_t                               txHoldTime_ns;
    uint16_t                               dataSetUpTime_ns;
    uint8_t                                dmaTxDataLevel;
    uint8_t                                dmaRxDataLevel;
    I2cDrv_SpecialCmdType                  specialCmdType;
    I2cDrv_SlaveDetectStopBitConditionType slaveDetectStopBitCondition;
    I2cDrv_TxEmptyCtrlType                 txEmptyCtrl;
} I2cDrv_ExtendParametersType;

/*! \brief I2C extend feature information */
typedef struct _I2cDrv_ExtendFeaturesType_
{
    bool dmaTxEn;
    bool dmaRxEn;
    bool ackForGeneralCallEn;
    bool specialCmdEn;
} I2cDrv_ExtendFeaturesType;

/*! \brief I2C initialize configuration information */
typedef struct _I2cDrv_InitCfgType_
{
    I2cDrv_BasicParametersType  basicParameters;
    I2cDrv_ExtendParametersType extendParameters;
    I2cDrv_ExtendFeaturesType   extendFeatures;
} I2cDrv_InitCfgType;

/*! \brief I2C instance pointer */
typedef struct _I2cDrvType_
{
    I2cRegType *reg;
} I2cDrvType;

/******************************************************************************
 * the globals
 *****************************************************************************/

/******************************************************************************
 * the function prototypes
 *****************************************************************************/

/*! \brief Get default configures the I2C module for configuration structure
 *
 * Note: This function gets default configures the I2C module for user configuration structure
 *
 * \param[in] pInitCfg: pointer to configuration structure
 * \return: void
 */
extern void I2cDrv_GetDefaultConfig(I2cDrv_InitCfgType *pInitCfg);

/*! \brief Set the module function with the configuration
 *
 * Note: This function initializes the run-time state structure to provide for module configuration
 *
 * \param[in] obj : pointer to I2C driver instance
 * \param[in] pInitCfg : point to the I2C initialize configuration
 * \return: void
 */
extern void I2cDrv_SetConfig(I2cDrvType *obj, const I2cDrv_InitCfgType *pInitCfg);

/*! \brief Resets the I2C internal logic and registers to their default settings
 *
 * Note: This function initializes I2C driver by setting the register instance to it.
 *
 * \param[in] obj: pointer to I2C driver instance
 * \param[in] pReg: pointer to I2C register instance
 * \return: void
 */
extern void I2cDrv_Init(I2cDrvType *obj, I2cRegType *pReg);

/*! \brief Deinit module into default state
 *
 * Note: Call back in the usage of low power or sleep requirements
 *
 * \param[in] obj: pointer to I2C driver instance
 * \return: void
 */
extern void I2cDrv_DeInit(I2cDrvType *obj);

/*! \brief Enable or Disable one or more than one interrupt source
 *
 * This function set the interrupt request action if condition matched
 *
 * \param[in] obj :pointer to I2C driver instance
 * \param[in] isrSrc :can used the more than one interrupt source once
 * \param[in] isrEn :True(Enable) or false(Disable)
 * \return: void
 */
extern void I2cDrv_SetInterruptReq(I2cDrvType *obj, uint32_t isrSrc, bool isrEn);

/*! \brief Clear one interrupt flag
 *
 * This function clear the interrupt flag if condition matched
 *
 * \param[in] obj :pointer to I2C driver instance
 * \param[in] isrSrc :can use one interrupt source once
 * \return: void
 */
extern void I2cDrv_ClrInterruptFlag(I2cDrvType *obj, uint32_t isrSrc);

/*! \brief Get the current interrupt status
 *
 * This function get the current inyrttupy is enabled or disabled
 *
 * \param[in] obj :pointer to I2C driver instance
 * \param[in] interruptSource: Interrupt source
 * \return: bool
 *          true: is enabled
 *          false: is disabled
 */
bool I2cDrv_GetInterruptIsEnabled(I2cDrvType *obj, I2cDrv_IsrSrcType interruptSource);

/*! \brief Get I2C interrupt status
 *
 * this function get the special interrupt status
 *
 * \param[in] obj :pointer to I2C driver instance
 * \param[in] interruptSource: Interrupt source
 * \return: bool
 *          0h: inactive
 *          1h: active
 */
bool I2cDrv_GetInterruptStatus(I2cDrvType *obj, I2cDrv_IsrSrcType interruptSource);

/*! \brief Get I2C raw interrupt status
 *
 * this function get the interrupt raw status
 *
 * \param[in] obj :pointer to I2C driver instance
 * \param[in] isrSrc: Interrupt source
 * \return: bool
 *          0h: inactive
 *          1h: active
 */
bool I2cDrv_GetInterruptRawStatus(I2cDrvType *obj, I2cDrv_IsrSrcType isrSrc);

/*! \brief Contains the number of valid data entries in the receive FIFO.
 *
 * this function get the number of valid data entries in the receive FIFO.
 *
 * \param[in] obj :pointer to I2C driver instance
 * \return: the number of valid data entries in the receive FIFO.
 */
uint8_t I2cDrv_GetRxFifoLevel(I2cDrvType *obj);

/*! \brief Set RX FIFO threshold
 *
 * I2C RX FIFO threshold FIFO depth is 16
 *
 * \param[in] obj :pointer to I2C driver instance
 * \param[in] rxFifoThreshold: RX FIFO threshold value
 * \return: void
 */
void I2cDrv_SetRxFifoThreshold(I2cDrvType *obj, uint8_t rxFifoThreshold);

/*! \brief Set TX FIFO threshold
 *
 * I2C TX FIFO threshold FIFO depth is 16
 *
 * \param[in] obj :pointer to I2C driver instance
 * \param[in] txFifoThreshold: TX FIFO threshold value
 * \return: void
 */
void I2cDrv_SetTxFifoThreshold(I2cDrvType *obj, uint8_t txFifoThreshold);

/*! \brief transmit data to other node
 *
 * Note: This function request data to be sent
 *
 * \param[in] obj: pointer to I2C driver instance
 * \param[in] pTxBuf: the pointer tx data
 * \param[in] txBytesNum: how many bytes to be sent
 * \return: bool
 *          true: request successful
 *          false: no enouth space for the current tx request
 */
extern bool I2cDrv_RequestWriteData(I2cDrvType *obj, const uint8_t *pTxBuf, uint8_t txBytesNum);

/*! \brief Receive data from other node
 *
 * Note: This function request to received data
 *
 * \param[in] obj: pointer to I2C driver instance
 * \param[in] pRxBuf: the read-out data to be filled in
 * \param[in] rxBytesNum: how many bytes to be read out
 * \return: void
 */
extern bool I2cDrv_RequestReadData(I2cDrvType *obj, uint8_t rxBytesNum);

/*! \brief Read received data from rx fifo
 *
 * Note: This function read data from rx fifo
 *
 * \param[in] obj: pointer to I2C driver instance
 * \param[in] pRxBuf : the space for read-out data
 * \return: return how many bytes are received
 */
extern uint8_t I2cDrv_GetReceivedData(const I2cDrvType *obj, uint8_t *pRxBuf);

/*! \brief Master request to abort current transfer
 *
 * Note: This function request to abort the current transfer process
 *
 * \param[in] obj: pointer to I2C driver instance
 * \return: void
 */
extern void I2cDrv_MasterAbortTransfer(I2cDrvType *obj);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _I2C_DRV_H_ */
