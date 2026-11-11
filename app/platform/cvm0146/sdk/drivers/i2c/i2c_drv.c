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

/******************************************************************************
 * the includes
 *****************************************************************************/

#include "i2c_drv.h"

/******************************************************************************
 * the defines
 *****************************************************************************/

#define I2CDRV_MILLI_RATE (1000ul)

/******************************************************************************
 * the typedefs
 *****************************************************************************/

/******************************************************************************
 * the globals
 *****************************************************************************/

/******************************************************************************
 * the static function declarations
 *****************************************************************************/
static void I2cDrv_InitBasicParameters(I2cRegType *pReg, const I2cDrv_BasicParametersType *pBasicParameters);
static void I2cDrv_InitExtendParameters(I2cRegType *pReg, const I2cDrv_ExtendFeaturesType *pExtendFeatures, const I2cDrv_ExtendParametersType *pExtendParameters, uint32_t busClockFreq);

/******************************************************************************
 * the functions
 *****************************************************************************/

/*! \brief Config the basic parameter and features
 *
 * This function initialize the basic features with the parameters
 *
 * \param[in] pReg: pointer to I2C driver instance
 * \param[in] pBasicParameters: the conbination of basic parameters
 * \return: void
 */
static void I2cDrv_InitBasicParameters(I2cRegType *pReg, const I2cDrv_BasicParametersType *pBasicParameters)
{
    if(pBasicParameters->nodeMode == I2CDRV_NODE_MODE_AS_MASTER)
    {
        /* Node as Master */
        I2cReg_SetMasterMode(pReg, true);

        /* Set address mode: 7bits or 10bits */
        I2cReg_SetMasterAddressMode(pReg, pBasicParameters->addressMode);

        /* Set target address */
        I2cReg_SetTargetAddress(pReg, pBasicParameters->targetAddress);

        I2cReg_SetMasterRestartEnable(pReg, pBasicParameters->restartBitEn);

        I2cReg_SetSlaveModeDisable(pReg, true);
    }
    else
    {
        I2cReg_SetMasterMode(pReg, false);

        I2cReg_SetSlaveAddressMode(pReg, pBasicParameters->addressMode);

        I2cReg_SetSlaveAddress(pReg, pBasicParameters->ownAddress);

        I2cReg_SetSlaveModeDisable(pReg, false);
    }

    I2cReg_SetSpeedMode(pReg, pBasicParameters->speedMode);

    if(pBasicParameters->speedMode == I2CDRV_SPEED_MODE_STANDARD_100KBIT)
    {
        if(pBasicParameters->sclFreq <= I2CDRV_STANDARDSPEED_UPPER_FREQ_VALUE)
        {
            uint16_t tCnt = 0;

            tCnt = (uint16_t)(pBasicParameters->busClockFreq / pBasicParameters->sclFreq);

            /* 50% + 50% */
            tCnt >>= 1;

            I2cReg_SetStandardModeHighLevelCount(pReg, tCnt);

            I2cReg_SetStandardModeLowLevelCount(pReg, tCnt);
        }
    }
    else if(pBasicParameters->speedMode == I2CDRV_SPEED_MODE_FAST_400KBIT_1000KBIT)
    {
        if(pBasicParameters->sclFreq <= I2CDRV_FASTSPEED_UPPER_FREQ_VALUE)
        {
            uint16_t tCnt = 0;

            tCnt = (uint16_t)(pBasicParameters->busClockFreq / pBasicParameters->sclFreq);

            /* 50% + 50% */
            tCnt >>= 1;

            I2cReg_SetFastModeHighLevelCount(pReg, tCnt);

            I2cReg_SetFastModeLowLevelCount(pReg, tCnt);
        }
    }
    else
    {
        /* Not support high-speed mode feature */
    }
}

/*! \brief Config the module extend parameters and features
 *
 * This function initializes the extend features with the parameters
 *
 * \param[in] pReg: pointer to I2C driver instance
 * \param[in] pExtendFeatures: the conbination of extend parameters
 * \param[in] pExtendParameters: the conbination of extendFeatures
 * \param[in] busClockFreq: the bus clock for i2c module
 * \return: void
 */
static void I2cDrv_InitExtendParameters(I2cRegType *pReg, const I2cDrv_ExtendFeaturesType *pExtendFeatures, const I2cDrv_ExtendParametersType *pExtendParameters, uint32_t busClockFreq)
{
    if(pExtendFeatures->dmaRxEn == true)
    {
        I2cReg_SetDmaRxLevel(pReg, pExtendParameters->dmaRxDataLevel);
    }

    I2cReg_SetRxDmaEnable(pReg, pExtendFeatures->dmaRxEn);

    if(pExtendFeatures->dmaTxEn == true)
    {
        I2cReg_SetDmaTxLevel(pReg, pExtendParameters->dmaTxDataLevel);
    }

    I2cReg_SetTxDmaEnable(pReg, pExtendFeatures->dmaTxEn);

    /* Special cmd selection config */
    I2cReg_SetSpecialCommand(pReg, pExtendFeatures->specialCmdEn);

    if(pExtendFeatures->specialCmdEn == true)
    {
        I2cReg_SetSpecialCmdType(pReg, pExtendParameters->specialCmdType);
    }

    I2cReg_SetAckForGeneralCall(pReg, pExtendFeatures->ackForGeneralCallEn);

    I2cReg_SetTxEmptyCtrl(pReg, pExtendParameters->txEmptyCtrl);

    {
        /* Spike suppression */
        uint32_t tSpikCnt = 0;

        tSpikCnt = ((uint32_t)pExtendParameters->spikeSuppressionTime_ns / ((I2CDRV_MILLI_RATE * I2CDRV_MILLI_RATE) / (busClockFreq / I2CDRV_MILLI_RATE)));
        I2cReg_SetSpikeLen(pReg, (tSpikCnt & 0xFF));
    }

    {
        uint16_t             tCnt          = 0;
        uint16_t             tHighLevelCnt = 0;
        uint16_t             tLowLevelCnt  = 0;
        uint8_t              tSpkLen       = 0;
        I2cDrv_SpeedModeType tSpeedMode;

        tSpeedMode = (I2cDrv_SpeedModeType)I2cReg_GetSpeedMode(pReg);

        tSpkLen = I2cReg_GetSpikeLen(pReg);

        if(tSpeedMode == I2CDRV_SPEED_MODE_STANDARD_100KBIT)
        {
            tHighLevelCnt = I2cReg_GetStandardModeHighLevelCount(pReg);
            tLowLevelCnt  = I2cReg_GetStandardModeLowLevelCount(pReg);

            /* modify the high counter, accord to the datasheet */
            if(tHighLevelCnt > (tSpkLen + 3u))
            {
                I2cReg_SetStandardModeHighLevelCount(pReg, tHighLevelCnt - tSpkLen - 3u);
                tHighLevelCnt = I2cReg_GetStandardModeHighLevelCount(pReg);
            }
        }
        else if(tSpeedMode == I2CDRV_SPEED_MODE_FAST_400KBIT_1000KBIT)
        {
            tHighLevelCnt = I2cReg_GetFastModeHighLevelCount(pReg);
            tLowLevelCnt  = I2cReg_GetFastModeLowLevelCount(pReg);

            /* modify the high counter, accord to the datasheet */
            if(tHighLevelCnt > (tSpkLen + 3u))
            {
                I2cReg_SetFastModeHighLevelCount(pReg, tHighLevelCnt - tSpkLen - 3u);

                tHighLevelCnt = I2cReg_GetFastModeHighLevelCount(pReg);
            }
        }
        else
        {
            /* Not support high-speed mode */
        }

        if(I2cReg_GetModuleAsMaster(pReg) == true)
        {
            /* Rx Hold time */
            tCnt = (uint16_t)((uint32_t)pExtendParameters->rxHoldTime_ns / ((I2CDRV_MILLI_RATE * I2CDRV_MILLI_RATE) / (busClockFreq / I2CDRV_MILLI_RATE)));
            if(tCnt <= (tHighLevelCnt - tSpkLen - 3u))
            {
                I2cReg_SetRxDataHoldTime(pReg, tCnt);
            }

            /* Tx Hold time */
            tCnt = (uint16_t)((uint32_t)pExtendParameters->txHoldTime_ns / ((I2CDRV_MILLI_RATE * I2CDRV_MILLI_RATE) / (busClockFreq / I2CDRV_MILLI_RATE)));
            if(tCnt < (tLowLevelCnt - 2u))
            {
                I2cReg_SetTxDataHoldTime(pReg, tCnt);
            }
        }
        else
        {
            /* TODO: Rx Hold time, < tf (scl from high to low duration ) */
            tCnt = (uint16_t)((uint32_t)pExtendParameters->rxHoldTime_ns / ((I2CDRV_MILLI_RATE * I2CDRV_MILLI_RATE) / (busClockFreq / I2CDRV_MILLI_RATE)));
            if(tCnt < (tHighLevelCnt - tSpkLen - 3u))
            {
                I2cReg_SetRxDataHoldTime(pReg, tCnt);
            }

            /* Tx Hold time */
            tCnt = (uint16_t)((uint32_t)pExtendParameters->txHoldTime_ns / ((I2CDRV_MILLI_RATE * I2CDRV_MILLI_RATE) / (busClockFreq / I2CDRV_MILLI_RATE)));
            if((tCnt >= (tSpkLen + 7u)) && (tCnt < (tLowLevelCnt - 2u)))
            {
                I2cReg_SetTxDataHoldTime(pReg, tCnt);
            }
            else
            {
                I2cReg_SetTxDataHoldTime(pReg, (tSpkLen + 7u));
            }

            I2cReg_SetSlaveDetectStopBitMode(pReg, pExtendParameters->slaveDetectStopBitCondition);
        }
    }

    if(I2cReg_GetModuleAsMaster(pReg) == false)
    {
        uint16_t tCnt = 0;

        /* Data setup time,The IC_SDA_SETUP register is only used by the DW_apb_i2c when operating as a slave transmitter */
        tCnt = (uint16_t)((uint32_t)pExtendParameters->dataSetUpTime_ns / ((I2CDRV_MILLI_RATE * I2CDRV_MILLI_RATE) / (busClockFreq / I2CDRV_MILLI_RATE)));

        I2cReg_SetDataSetUpTime(pReg, (uint8_t)(tCnt + 1u));
    }
}

/*! \brief Enable or Disable one or more than one interrupt source
 *
 * This function set the interrupt request action if condition matched
 *
 * \param[in] obj :pointer to I2C driver instance
 * \param[in] isrSrc :can used the more than one interrupt source once
 * \param[in] isrEn :True(Enable) or false(Disable)
 * \return: void
 */
void I2cDrv_SetInterruptReq(I2cDrvType *obj, uint32_t isrSrc, bool isrEn)
{
    if(isrSrc > I2CDRV_ISR_SRC_ALL)
    {
        return;
    }
    I2cReg_SetInterruptMask(obj->reg, isrSrc, isrEn);
}

/*! \brief Clear one interrupt flag
 *
 * This function clear the interrupt flag if condition matched
 *
 * \param[in] obj :pointer to I2C driver instance
 * \param[in] isrSrc :can use one interrupt source once
 * \return: void
 */
void I2cDrv_ClrInterruptFlag(I2cDrvType *obj, uint32_t isrSrc)
{
    if(isrSrc > I2CDRV_ISR_SRC_ALL)
    {
        return;
    }
    switch(isrSrc)
    {
    case I2CDRV_ISR_SRC_ALL:
        I2cReg_ClearAllInterruptStatus(obj->reg);
        break;
    case I2CDRV_ISR_SRC_RX_UNDER:
        I2cReg_ClearRxUnderStatus(obj->reg);
        break;
    case I2CDRV_ISR_SRC_RX_OVER:
        I2cReg_ClearRxOverStatus(obj->reg);
        break;
    case I2CDRV_ISR_SRC_TX_OVER:
        I2cReg_ClearTxOverStatus(obj->reg);
        break;
    case I2CDRV_ISR_SRC_RD_REQ:
        I2cReg_ClearReadReqStatus(obj->reg);
        break;
    case I2CDRV_ISR_SRC_TX_ABRT:
        I2cReg_ClearTxAbortStatus(obj->reg);
        break;
    case I2CDRV_ISR_SRC_RX_DONE:
        I2cReg_ClearRxDoneStatus(obj->reg);
        break;
    case I2CDRV_ISR_SRC_ACTIVITY:
        I2cReg_ClearActivityStatus(obj->reg);
        break;
    case I2CDRV_ISR_SRC_STOP_DET:
        I2cReg_ClearStopBitDetectStatus(obj->reg);
        break;
    case I2CDRV_ISR_SRC_START_DET:
        I2cReg_ClearStartBitDetectStatus(obj->reg);
        break;
    case I2CDRV_ISR_SRC_GEN_CALL:
        I2cReg_ClearGeneralCallStatus(obj->reg);
        break;

    default:
        break;
    }
}

/*! \brief Get the current interrupt status
 *
 * This function get the current inyrttupy is enabled or disabled
 *
 * \param[in] obj :pointer to I2C driver instance
 * \param[in] isrSrc: Interrupt source
 * \return: bool
 *          true: is enabled
 *          false: is disabled
 */
bool I2cDrv_GetInterruptIsEnabled(I2cDrvType *obj, I2cDrv_IsrSrcType isrSrc)
{
    return I2cReg_GetInterruptIsEnabled(obj->reg, isrSrc);
}

/*! \brief Get I2C interrupt status
 *
 * this function get the special interrupt status
 *
 * \param[in] obj :pointer to I2C driver instance
 * \param[in] isrSrc: Interrupt source
 * \return: bool
 *          0h: inactive
 *          1h: active
 */
bool I2cDrv_GetInterruptStatus(I2cDrvType *obj, I2cDrv_IsrSrcType isrSrc)
{
    return I2cReg_GetInterruptStatus(obj->reg, isrSrc);
}

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
bool I2cDrv_GetInterruptRawStatus(I2cDrvType *obj, I2cDrv_IsrSrcType isrSrc)
{
    return I2cReg_GetInterruptRawStatus(obj->reg, isrSrc);
}

/*! \brief Contains the number of valid data entries in the receive FIFO.
 *
 * this function get the number of valid data entries in the receive FIFO.
 *
 * \param[in] obj :pointer to I2C driver instance
 * \return: the number of valid data entries in the receive FIFO.
 */
uint8_t I2cDrv_GetRxFifoLevel(I2cDrvType *obj)
{
    return I2cReg_GetRxFifoLevel(obj->reg);
}

/*! \brief Set RX FIFO threshold
 *
 * I2C RX FIFO threshold FIFO depth is 16
 *
 * \param[in] obj :pointer to I2C driver instance
 * \param[in] rxFifoThreshold: RX FIFO threshold value
 * \return: void
 */
void I2cDrv_SetRxFifoThreshold(I2cDrvType *obj, uint8_t rxFifoThreshold)
{
    I2cReg_SetRxFifoThreshold(obj->reg, rxFifoThreshold);
}

/*! \brief Set TX FIFO threshold
 *
 * I2C TX FIFO threshold FIFO depth is 16
 *
 * \param[in] obj :pointer to I2C driver instance
 * \param[in] txFifoThreshold: TX FIFO threshold value
 * \return: void
 */
void I2cDrv_SetTxFifoThreshold(I2cDrvType *obj, uint8_t txFifoThreshold)
{
    I2cReg_SetTxFifoThreshold(obj->reg, txFifoThreshold);
}

/*! \brief Get default configures the I2C module for configuration structure
 *
 * This function gets default configures the I2C module for user configuration structure
 *
 * \param[in] pInitCfg: pointer to configuration structure
 * \return: void
 */
void I2cDrv_GetDefaultConfig(I2cDrv_InitCfgType *pInitCfg)
{
    pInitCfg->basicParameters.busClockFreq  = 48000000ul;
    pInitCfg->basicParameters.sclFreq       = 20000;
    pInitCfg->basicParameters.addressMode   = I2CDRV_ADDR_MODE_7BIT;
    pInitCfg->basicParameters.nodeMode      = I2CDRV_NODE_MODE_AS_MASTER;
    pInitCfg->basicParameters.ownAddress    = 0x75;
    pInitCfg->basicParameters.targetAddress = 0x28;
    pInitCfg->basicParameters.restartBitEn  = true;
    pInitCfg->basicParameters.speedMode     = I2CDRV_SPEED_MODE_STANDARD_100KBIT;

    pInitCfg->extendFeatures.dmaRxEn             = false;
    pInitCfg->extendFeatures.dmaTxEn             = false;
    pInitCfg->extendFeatures.ackForGeneralCallEn = false;
    pInitCfg->extendFeatures.specialCmdEn        = false;

    pInitCfg->extendParameters.spikeSuppressionTime_ns     = 50;
    pInitCfg->extendParameters.rxHoldTime_ns               = 2;
    pInitCfg->extendParameters.txHoldTime_ns               = 100;
    pInitCfg->extendParameters.dataSetUpTime_ns            = 100;
    pInitCfg->extendParameters.dmaTxDataLevel              = 0;
    pInitCfg->extendParameters.dmaRxDataLevel              = 0;
    pInitCfg->extendParameters.specialCmdType              = I2CDRV_SPECIAL_CMD_GENERAL_CALL;
    pInitCfg->extendParameters.slaveDetectStopBitCondition = I2CDRV_SLAVE_DETECT_STOPBIT_CONDITION_IN_ADDR_MATCH;
    pInitCfg->extendParameters.txEmptyCtrl                 = I2CDRV_TX_EMPTY_AT_TXFIFO_LESSTHAN_TXTL;
}

/*! \brief Set the module function with the configuration
 *
 * This function initializes the run-time state structure to provide for module configuration
 *
 * \param[in] obj : pointer to I2C driver instance
 * \param[in] pInitCfg : point to the I2C initialize configuration
 * \return: void
 */
void I2cDrv_SetConfig(I2cDrvType *obj, const I2cDrv_InitCfgType *pInitCfg)
{
    I2cReg_SetModuleEnable(obj->reg, false);

    /* Disable all interrupt req */
    I2cReg_SetInterruptMask(obj->reg, 0xFFFFFFFF, false);

    /* Clear all status that can be cleared by software except be cleared by hardware */
    I2cReg_ClearAllInterruptStatus(obj->reg);

    if(pInitCfg->basicParameters.nodeMode == I2CDRV_NODE_MODE_AS_SLAVE)
    {
        /* Disable slave mode */
        I2cReg_SetSlaveModeDisable(obj->reg, true);
    }

    I2cDrv_InitBasicParameters(obj->reg, &pInitCfg->basicParameters);

    I2cDrv_InitExtendParameters(obj->reg, &pInitCfg->extendFeatures, &pInitCfg->extendParameters, pInitCfg->basicParameters.busClockFreq);

    I2cReg_SetModuleEnable(obj->reg, true);
}

/*! \brief Resets the I2C internal logic and registers to their default settings
 *
 * This function initializes I2C driver by setting the register instance to it.
 *
 * \param[in] obj: pointer to I2C driver instance
 * \param[in] pReg: pointer to I2C register instance
 * \return: void
 */
void I2cDrv_Init(I2cDrvType *obj, I2cRegType *pReg)
{
    obj->reg = pReg;

    /* Disable module to make sure some register have been configurated successfully */
    I2cReg_SetModuleEnable(obj->reg, false);

    /* Clear all status that can be cleared by software except be cleared by hardware */
    I2cReg_ClearAllInterruptStatus(obj->reg);
}

/*! \brief Deinit module into default state
 *
 * Call back in the usage of low power or sleep requirements
 *
 * \param[in] obj: pointer to I2C driver instance
 * \return: void
 */
void I2cDrv_DeInit(I2cDrvType *obj)
{
    /* Disable module to make sure some register have been configurated successfully */
    I2cReg_SetModuleEnable(obj->reg, false);
}

/*! \brief transmit data to other node
 *
 * This function request data to be sent
 *
 * \param[in] obj: pointer to I2C driver instance
 * \param[in] pTxBuf: the pointer tx data
 * \param[in] txBytesNum: how many bytes to be sent
 * \return: bool
 *          true: request successful
 *          false: no enouth space for the current tx request
 */
bool I2cDrv_RequestWriteData(I2cDrvType *obj, const uint8_t *pTxBuf, uint8_t txBytesNum)
{
    bool tRtn = true;

    uint8_t i = 0;

    if((I2CDRV_TX_FIFO_DEPTH - I2cReg_GetTxFifoLevel(obj->reg)) >= txBytesNum)
    {
        for(i = 0; i < txBytesNum; i++)
        {
            I2cReg_SetDataAndCmd(obj->reg, pTxBuf[i], false);
        }
    }
    else
    {
        tRtn = false;
    }

    return tRtn;
}

/*! \brief Receive data from other node
 *
 * This function request to received data
 *
 * \param[in] obj: pointer to I2C driver instance
 * \param[in] rxBytesNum: how many bytes to be read out
 * \return: void
 */
bool I2cDrv_RequestReadData(I2cDrvType *obj, uint8_t rxBytesNum)
{
    bool    tRtn = true;
    uint8_t i    = 0;

    if((I2CDRV_TX_FIFO_DEPTH - I2cReg_GetTxFifoLevel(obj->reg)) >= rxBytesNum)
    {
        for(i = 0; i < rxBytesNum; i++)
        {
            I2cReg_SetDataAndCmd(obj->reg, 0u, true);
        }
    }
    else
    {
        tRtn = false;
    }

    return tRtn;
}

/*! \brief Read received data from rx fifo
 *
 * This function read data from rx fifo
 *
 * \param[in] obj: pointer to I2C driver instance
 * \param[in] pRxBuf : the space for read-out data
 * \return: return how many bytes are received
 */
uint8_t I2cDrv_GetReceivedData(const I2cDrvType *obj, uint8_t *pRxBuf)
{
    uint8_t tRxBytesNum = 0, i = 0;

    tRxBytesNum = I2cReg_GetRxFifoLevel(obj->reg);

    if(tRxBytesNum > 0u)
    {
        for(i = 0; i < tRxBytesNum; i++)
        {
            pRxBuf[i] = I2cReg_GetData(obj->reg);
        }
    }

    return tRxBytesNum;
}

/*! \brief Master request to abort current transfer
 *
 * This function request to abort the current transfer process
 *
 * \param[in] obj: pointer to I2C driver instance
 * \return: void
 */
void I2cDrv_MasterAbortTransfer(I2cDrvType *obj)
{
    if(I2cReg_GetDmaTxIsEnabled(obj->reg) == true)
    {
        I2cReg_SetTxDmaEnable(obj->reg, false);
    }

    /* TODO: Generate an interrupt event after abort operation? */
    I2cReg_SetInterruptMask(obj->reg, I2C_INTR_MASK_TX_ABRT_MASK, false);

    I2cReg_SetAbortReq(obj->reg);

    /* Wait tx abort status set to 1 */
    while(I2cReg_GetInterruptRawStatus(obj->reg, I2C_INTR_STAT_TX_ABRT_MASK) == false)
    {
    }

    /* Check the current abort request is from master request */
    if(I2cReg_GetTxAbortInfo(obj->reg, I2C_TX_ABRT_SOURCE_ABRT_USER_ABRT_MASK) == true)
    {
    }
}
