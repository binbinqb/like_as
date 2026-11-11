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

#include "uart_drv.h"

/******************************************************************************
 * the defines
 *****************************************************************************/

/******************************************************************************
 * the globals
 ******************************************************************************/

/******************************************************************************
 * the Static Function Declarations
 ******************************************************************************/
static void UartDrv_InitBasicParameters(UartDrvType *obj, const UartDrv_BasicParametersType *pBasicParameters);
static void UartDrv_InitExtendParameters(UartDrvType *obj, const UartDrv_ExtendParametersType *pExtendParameters, const UartDrv_ExtendFeaturesType *pExtendFeatures);

/******************************************************************************
 * the functions
 *****************************************************************************/

/*! \brief Config the basic parameter of the usart basic feature
 *
 * This function initializes the basic features with the parameters
 *
 * \param[in] obj: pointer to UART driver instance
 * \param[in] pBasicParameters : the combination of basic parameters
 * \return: void
 */
static void UartDrv_InitBasicParameters(UartDrvType *obj, const UartDrv_BasicParametersType *pBasicParameters)
{
    /* Parity configuration setting */
    if(pBasicParameters->paritySelection < UARTDRV_PARITY_SELECT_UNUSED)
    {
        UartReg_SelectParity(obj->reg, pBasicParameters->paritySelection);
        UartReg_SetParityControlEnable(obj->reg, true);
    }
    else
    {
        UartReg_SetParityControlEnable(obj->reg, false);
    }

    /* Data length set */
    UartReg_SetWordLength(obj->reg, pBasicParameters->dataBitsNum);

    /* STOP Bit num */
    UartReg_SetStopBitNums(obj->reg, pBasicParameters->stopBitsNum);

    /* Data shift direction */
    UartReg_SetFirstBitShift(obj->reg, pBasicParameters->dataShiftDirection);

    /* Sampliing setting */
    UartReg_SetOverSamplingMode(obj->reg, pBasicParameters->overSamplingMode);

    /* note: When the one sample bit method is selected the noise detection flag (NF) is disabled */
    UartReg_SetSampleBitMethod(obj->reg, pBasicParameters->oneSampleBitMethod);

    if(pBasicParameters->baudRate != UARTDRV_BRAUD_RATE_INVALID)
    {
        /* TODO: How to get the system clock frequency? if  6/24/2022 Changed by %USERNAME% */
        uint32_t tDiv = 0;

        if(pBasicParameters->overSamplingMode == UARTDRV_OVERSAMPLING_MODE_BY_8)
        {
            /*
            -BRR[2:0] = UARTDIV[3:0] shifted 1 bit to the right
            -BRR[3] must be kept cleared
            -BRR[15:4] = UARTDIV[15:4]
            */
            tDiv = pBasicParameters->busClockFreq / (pBasicParameters->baudRate >> 1ul);
            tDiv = ((tDiv & UARTDRV_BRR_LOW_4BITS_MASK) >> 1u) | (tDiv & (~UARTDRV_BRR_LOW_4BITS_MASK));
        }
        else
        {
            /* overSamplingMode == 16, BRR = UARTDIV */
            tDiv = pBasicParameters->busClockFreq / pBasicParameters->baudRate;
        }

        UartReg_SetBaudRate(obj->reg, (uint16_t)(tDiv & 0xFFFF));

        /* Disable Auto detect baud rate feature */
        UartReg_EnableAutoBaudrateFeature(obj->reg, false);
    }

    /* Transceiver enable */
    switch(pBasicParameters->dataTransferDirect)
    {
    case UARTDRV_DATA_TRANSFER_TX_RX_EN:
        UartReg_SetReceiverEnable(obj->reg, true);
        UartReg_SetTransmitterEnable(obj->reg, true);
        break;

    case UARTDRV_DATA_TRANSFER_TX_ONLY:
        UartReg_SetReceiverEnable(obj->reg, false);
        UartReg_SetTransmitterEnable(obj->reg, true);
        break;

    case UARTDRV_DATA_TRANSFER_RX_ONLY:
        UartReg_SetReceiverEnable(obj->reg, true);
        UartReg_SetTransmitterEnable(obj->reg, false);
        break;

    case UARTDRV_DATA_TRANSFER_TX_RX_DIS:
        UartReg_SetReceiverEnable(obj->reg, false);
        UartReg_SetTransmitterEnable(obj->reg, false);
        break;

    default:
        UartReg_SetReceiverEnable(obj->reg, false);
        UartReg_SetTransmitterEnable(obj->reg, false);
        break;
    }
}

/*! \brief Set the extend parameter of the extend feature
 *
 * This function initializes the extend features with the parameters
 *
 * \param[in] obj: pointer to UART driver instance
 * \param[in] pExtendParameters: the combination of extend parameters
 * \param[in] pExtendFeatures: the combination of extendFeatures
 * \return: void
 */
static void UartDrv_InitExtendParameters(UartDrvType *obj, const UartDrv_ExtendParametersType *pExtendParameters, const UartDrv_ExtendFeaturesType *pExtendFeatures)
{
    /* Loops mode */
    UartReg_SetLoopsMode(obj->reg, pExtendFeatures->loopEn);

    switch(pExtendFeatures->cosplayer)
    {
    case UARTDRV_COSPLAY_LIN:
        UartReg_EnableCts(obj->reg, false);
        UartReg_EnableRts(obj->reg, false);
        UartReg_SetDriverEnableMode(obj->reg, false);
        UartReg_SetTxLinSyncBreakWidth(obj->reg, pExtendParameters->breakFieldSyncBreakTxBitsNum);
        UartReg_SetLinDelimitorWidth(obj->reg, pExtendParameters->breakFieldDelimiterTxBitsNum);
        UartReg_SetLinSyncBreakDetectLen(obj->reg, pExtendParameters->syncBreakRxBitsNum);
        UartReg_EnableLineBreakDetectFeature(obj->reg, pExtendFeatures->linBreakDetectEn);
        UartReg_EnableLineBaudrateAutoDetectFeature(obj->reg, pExtendFeatures->linBaudrateAutoDetectEn);
        if(pExtendFeatures->linBaudrateAutoDetectEn == true)
        {
            UartReg_SetLinBaudrateRxTimeout(obj->reg, pExtendParameters->linBaudrateRxTimeoutBitsNum);
        }
        break;

    case UARTDRV_COSPLAY_RS232:
        UartReg_EnableLineBreakDetectFeature(obj->reg, false);
        UartReg_SetDriverEnableMode(obj->reg, false);
        /* CTS Hardware flow control enable */
        UartReg_EnableCts(obj->reg, true);
        UartReg_EnableRts(obj->reg, true);
        break;

    case UARTDRV_COSPLAY_RS485:
        UartReg_EnableLineBreakDetectFeature(obj->reg, false);
        UartReg_SetDEDT(obj->reg, pExtendParameters->driverEnDeassertionTime);
        UartReg_SetDEAT(obj->reg, pExtendParameters->driverEnAssertionTime);
        UartReg_SetDriverPolarity(obj->reg, pExtendParameters->driverEnablePolarityActiveInLow);
        UartReg_SetDriverEnableMode(obj->reg, true);
        break;

    case UARTDRV_COSPLAY_UART:
    default:
        UartReg_EnableCts(obj->reg, false);
        UartReg_EnableRts(obj->reg, false);
        UartReg_SetDriverEnableMode(obj->reg, false);
        UartReg_EnableLineBreakDetectFeature(obj->reg, false);
        break;
    }

    /* Inversion in Rx&Tx Pin & Data */
    UartReg_EnableRxInverteFeature(obj->reg, pExtendFeatures->rxInvertEn);
    UartReg_EnableTxInverteFeature(obj->reg, pExtendFeatures->txInvertEn);
    UartReg_EnableDataInverteFeature(obj->reg, pExtendFeatures->dataInvertEn);

    if(pExtendFeatures->autoBaudRateDetectionEn == true)
    {
        /* Enable Auto detect baud rate feature */
        UartReg_EnableAutoBaudrateFeature(obj->reg, true);
        UartReg_SetAutoBaudrateMode(obj->reg, pExtendParameters->autoBaudRateMode);
    }
    else
    {
        UartReg_EnableAutoBaudrateFeature(obj->reg, false);
    }

    if(pExtendParameters->rxTimeoutBitsCnt > 0u)
    {
        /* This bit-field gives the Receiver timeout value in terms of number of bit duration */
        UartReg_SetRxTimeout(obj->reg, pExtendParameters->rxTimeoutBitsCnt);
        UartReg_EnableRxTimeoutFeature(obj->reg, true);
    }
    else
    {
        UartReg_EnableRxTimeoutFeature(obj->reg, false);
    }

    if(pExtendFeatures->wakeUpEn == true)
    {
        if(pExtendParameters->wakeSrc == UARTDRV_WAKE_SOURCE_ADDRESS_MARK)
        {
            UartReg_SetNodeAddress(obj->reg, pExtendParameters->addrMarkDetectValue);
            UartReg_SetAddreDetectMode(obj->reg, pExtendParameters->addrDetectMode);
        }
        else
        {
            UartReg_SetIdleConfig(obj->reg, pExtendParameters->idleCharNums);
        }

        UartReg_SetMuteMode(obj->reg, true);
        UartReg_SetWakeupMethod(obj->reg, pExtendParameters->wakeSrc);
    }
    else
    {
        UartReg_SetMuteMode(obj->reg, false);
        UartReg_SetIdleConfig(obj->reg, pExtendParameters->idleCharNums);
    }

    if(pExtendFeatures->dmaEn == true)
    {
        switch(pExtendParameters->dmaSelection)
        {
        case UARTDRV_DMA_SELECTION_TX_RX_DIS:
            UartReg_EnableRxDMA(obj->reg, false);
            UartReg_EnableTxDMA(obj->reg, false);
            break;

        case UARTDRV_DMA_SELECTION_TX_EN_RX_DIS:
            UartReg_EnableRxDMA(obj->reg, false);
            UartReg_EnableTxDMA(obj->reg, true);
            break;

        case UARTDRV_DMA_SELECTION_TX_DIS_RX_EN:
            UartReg_EnableRxDMA(obj->reg, true);
            UartReg_EnableTxDMA(obj->reg, false);
            break;

        case UARTDRV_DMA_SELECTION_TX_EN_RX_EN:
            UartReg_EnableRxDMA(obj->reg, true);
            UartReg_EnableTxDMA(obj->reg, true);
            break;

        default:
            UartReg_EnableRxDMA(obj->reg, false);
            UartReg_EnableTxDMA(obj->reg, false);
            break;
        }
    }
    else
    {
        UartReg_EnableRxDMA(obj->reg, false);
        UartReg_EnableTxDMA(obj->reg, false);
    }
}

/*! \brief Transmit one data
 *
 * This function write one data to tx fifo
 *
 * \param[in] obj :pointer to UART driver instance
 * \param[in] txDatabuf : the copy of data to be sent
 * \return: void
 */
void UartDrv_TxData(UartDrvType *obj, uint16_t txData)
{
    UartReg_TxData(obj->reg, txData);
}

/*! \brief Read out from the rx buffer to the specific address and indicated how
 *
 * This function read out received datas from rx fifo
 *
 * \param[in] obj : pointer to UART driver instance
 * \return: read-out value , if PE or FE or NF, return UARTDRV_READ_DATA_INVALID
 */
uint16_t UartDrv_RxData(const UartDrvType *obj)
{
    uint16_t tRtn = UARTDRV_READ_DATA_INVALID;

    uint32_t tRegValue = obj->reg->RDR;

    if((tRegValue & UART_RDR_ERR_MASK) == 0u)
    {
        tRtn = (((tRegValue & UART_RDR_RDR_MASK) >> UART_RDR_RDR_SHIFT) & 0x1FF);
    }

    return tRtn;
}

/*! \brief Read out the current status flag
 *
 * This function Get the expected status
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] status: which status want to get
 * \return : bool
 *           FALSE:
 *           TRUE: some event happend
 */
bool UartDrv_GetStatus(const UartDrvType *obj, UartDrv_StatusType status)
{
    bool tRtn = false;

    uint32_t tRegValue = 0;

    if(status <= UARTDRV_STATUS_RWU)
    {
        /* FIFO */
        if((status == UARTDRV_STATUS_RXUF) || (status == UARTDRV_STATUS_TXOF))
        {
            if(status == UARTDRV_STATUS_RXUF)
            {
                tRtn = UartReg_GetRxUnderflowFlag(obj->reg);
            }
            else
            {
                tRtn = UartReg_GetTxOverflowFlag(obj->reg);
            }
        }
        else
        {
            /* ISR */
            tRegValue = obj->reg->ISR;

            if((tRegValue & status) != 0u)
            {
                tRtn = true;
            }
        }
    }
    else if(status <= UARTDRV_STATUS_RX_EMPTY)
    {
        tRegValue = obj->reg->FIFO;

        if(status == UARTDRV_STATUS_RX_EMPTY)
        {
            if((tRegValue & UART_FIFO_RXEMPT_MASK) != 0u)
            {
                tRtn = true;
            }
        }
        else
        {
            if((tRegValue & UART_FIFO_TXEMPT_MASK) != 0u)
            {
                tRtn = true;
            }
        }
    }
    else
    {
        /* Nothing to do */
    }

    return tRtn;
}

/*! \brief Clear the expected status
 *
 * This function clear the special status , can be combination with more than one status
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] status: can used the combination of the UartDrv_IsrStatusIdxType to clear more than one bit interrupt flag;
 *            for example: if want to clear PE&FE: (UARTDRV_STATUS_RXUF | UART_STATUS_PE)
 * \return: void
 */
void UartDrv_ClearStatus(UartDrvType *obj, uint32_t status)
{
    /* FIFO */
    if(((status & UARTDRV_STATUS_RXUF) != 0ul) || ((status & UARTDRV_STATUS_TXOF) != 0ul))
    {
        if((status & UARTDRV_STATUS_TXOF) != 0ul)
        {
            UartReg_ClearTxOverflowFlag(obj->reg);
        }
        else
        {
            UartReg_ClearRxUnderflowFlag(obj->reg);
        }
    }
    else if((status & UARTDRV_STATUS_ABRE) != 0ul)
    {
        UartReg_ReqAutoBaudRate(obj->reg);
    }
    else if((status & UARTDRV_STATUS_LBDT_FAIL) != 0ul)
    {
        UartReg_ClearLinBreakDetectedResultFlag(obj->reg);
    }
    else
    {
        /* ISR */
        obj->reg->ICR = (uint32_t)status;
    }
}

/*! \brief Enable or Disable one or more than one interrupt source
 *
 * This function set the interrupt request action if condition matched
 *
 * \param[in] obj :pointer to UART driver instance
 * \param[in] isrSrc :can used the more than one interrupt source once
 * \param[in] isrEn :True(Enable) or false(Disable)
 * \return: void
 */
void UartDrv_SetInterruptReq(UartDrvType *obj, uint32_t isrSrc, bool isrEn)
{
    /* Tx interrupt configuration */
    /* Transmit overflow */
    if((isrSrc & UARTDRV_ISR_SRC_TX_OVERFLOW) != 0u)
    {
        UartReg_SetTxOverflowIsr(obj->reg, isrEn);
    }

    /* Transmit data register empty */
    if((isrSrc & UARTDRV_ISR_SRC_TX_EMPTY) != 0u)
    {
        UartReg_SetTxBufferEmptyIsr(obj->reg, isrEn);
    }
    /* Transmission Complete */
    if((isrSrc & UARTDRV_ISR_SRC_TX_COMPLETE) != 0u)
    {
        UartReg_SetTxCompletedIsr(obj->reg, isrEn);
    }
    /* Send break done flag */
    if((isrSrc & UARTDRV_ISR_SRC_TX_SYNC_BREAK) != 0u)
    {
        UartReg_SetBreakTxCompletedIsr(obj->reg, isrEn);
    }

    /* Rx interrupt configuration */
    /* Receive under flow */
    if((isrSrc & UARTDRV_ISR_SRC_RX_UNDERFLOW) != 0u)
    {
        UartReg_SetRxUnderflowIsr(obj->reg, isrEn);
    }

    /* Receive Data Register Full */
    if((isrSrc & UARTDRV_ISR_SRC_RX_FULL) != 0u)
    {
        UartReg_SetRxBufferFullIsr(obj->reg, isrEn);
    }

    /* Receiver timeout */
    if((isrSrc & UARTDRV_ISR_SRC_RX_TIMEOUT) != 0u)
    {
        UartReg_SetRxTimeoutIsr(obj->reg, isrEn);
    }

    /* LIN Break Detect Done */
    if((isrSrc & UARTDRV_ISR_SRC_RX_SYNC_BREAK) != 0u)
    {
        UartReg_SetLinBreakDetectedIsr(obj->reg, isrEn);
    }

    /* Idle line detected */
    if((isrSrc & UARTDRV_ISR_SRC_RX_IDLE) != 0u)
    {
        UartReg_SetIdleIsr(obj->reg, isrEn);
    }

    /* CTS */
    if((isrSrc & UARTDRV_ISR_SRC_RX_CTS) != 0u)
    {
        UartReg_SetCtsIsr(obj->reg, isrEn);
    }

    /* Err interrupt configuration */
    /* Parity error */
    if((isrSrc & UARTDRV_ISR_SRC_ERR_PARITY) != 0u)
    {
        UartReg_SetParityErrIsr(obj->reg, isrEn);
    }

    /* One of the frame err or noise err or over run err */
    if(((isrSrc & UARTDRV_ISR_SRC_ERR_FRAME) != 0u) || ((isrSrc & UARTDRV_ISR_SRC_ERR_NOISE) != 0u) || ((isrSrc & UARTDRV_ISR_SRC_ERR_OVER_RUN) != 0u))
    {
        UartReg_SetErrIsr(obj->reg, isrEn);
    }

    if((isrSrc & UARTDRV_ISR_SRC_ERR_ABRE_LBDT_FAIL) != 0u)
    {
        UartReg_SetAutoBaudrateOrLinBreakDetectedFailedIsr(obj->reg, isrEn);
    }
}

/*! \brief Get one interrupt source is enable or disable
 *
 * This function gets one interrupt source is enable or disable
 *
 * \param[in] obj :pointer to UART driver instance
 * \param[in] isrType :one interrupt source type
 * \return: True(Enable) or false(Disable)
 */
bool UartDrv_IsInterruptEnabled(UartDrvType *obj, UartDrv_IsrSrcType isrType)
{
    bool bRet = false;

    switch(isrType)
    {
    case UARTDRV_ISR_SRC_TX_OVERFLOW:
        bRet = UartReg_GetTxOverflowIsrIsEnabled(obj->reg);
        break;
    case UARTDRV_ISR_SRC_TX_EMPTY:
        bRet = UartReg_GetTxBufferEmptyIsrIsEnabled(obj->reg);
        break;
    case UARTDRV_ISR_SRC_TX_COMPLETE:
        bRet = UartReg_GetTxCompletedIsrIsEnabled(obj->reg);
        break;
    case UARTDRV_ISR_SRC_TX_SYNC_BREAK:
        bRet = UartReg_GetBreakTxCompletedIsrIsEnabled(obj->reg);
        break;
    case UARTDRV_ISR_SRC_RX_UNDERFLOW:
        bRet = UartReg_GetRxUnderflowIsrIsEnabled(obj->reg);
        break;
    case UARTDRV_ISR_SRC_RX_FULL:
        bRet = UartReg_GetRxBufferFullIsrIsEnabled(obj->reg);
        break;
    case UARTDRV_ISR_SRC_RX_TIMEOUT:
        bRet = UartReg_GetRxTimeoutIsrIsEnabled(obj->reg);
        break;
    case UARTDRV_ISR_SRC_RX_SYNC_BREAK:
        bRet = UartReg_GetLinBreakDetectedIsrIsEnabled(obj->reg);
        break;
    case UARTDRV_ISR_SRC_RX_IDLE:
        bRet = UartReg_GetIdleIsrIsEnabled(obj->reg);
        break;
    case UARTDRV_ISR_SRC_RX_CTS:
        bRet = UartReg_GetCtsIsrIsEnabled(obj->reg);
        break;
    case UARTDRV_ISR_SRC_ERR_PARITY:
        bRet = UartReg_GetParityErrIsrIsEnabled(obj->reg);
        break;
    case UARTDRV_ISR_SRC_ERR_FRAME:
    case UARTDRV_ISR_SRC_ERR_NOISE:
    case UARTDRV_ISR_SRC_ERR_OVER_RUN:
        bRet = UartReg_GetErrIsrIsEnabled(obj->reg);
        break;
    case UARTDRV_ISR_SRC_ERR_ABRE_LBDT_FAIL:
        bRet = UartReg_GetAutoBaudrateOrLinBreakDetectedFailedIsrIsEnabled(obj->reg);
        break;
    default:
        break;
    }

    return bRet;
}

/*! \brief Get default configures the UART module for configuration structure
 *
 * This function gets default configures the UART module for user configuration structure
 *
 * \param[out] userConfig : pointer to configuration structure
 * \return: void
 */
void UartDrv_GetDefaultConfig(UartDrv_InitCfgType *pInitCfg)
{
    pInitCfg->basicParameters.baudRate           = 19200;
    pInitCfg->basicParameters.dataBitsNum        = UARTDRV_DATA_BITS_NUM_8;
    pInitCfg->basicParameters.stopBitsNum        = UARTDRV_STOP_BITS_NUM_1;
    pInitCfg->basicParameters.dataShiftDirection = UARTDRV_DATA_SHIFT_DIRECTION_LSB;
    pInitCfg->basicParameters.paritySelection    = UARTDRV_PARITY_SELECT_UNUSED;
    pInitCfg->basicParameters.oneSampleBitMethod = UARTDRV_ONE_SAMPLE_BIT_METHOD_IN_3BITS;
    pInitCfg->basicParameters.overSamplingMode   = UARTDRV_OVERSAMPLING_MODE_BY_16;
    pInitCfg->basicParameters.dataTransferDirect = UARTDRV_DATA_TRANSFER_TX_RX_EN;

    pInitCfg->extendParameters.addrDetectMode      = UARTDRV_ADDR_DETECTION_MODE_ALL_BITS;
    pInitCfg->extendParameters.addrMarkDetectValue = 0x55;
    pInitCfg->extendParameters.idleCharNums        = UARTDRV_IDLE_CHAR_NUM_4;
    pInitCfg->extendParameters.wakeSrc             = UARTDRV_WAKE_SOURCE_IDLE_LINE;
    pInitCfg->extendParameters.rxTimeoutBitsCnt    = 0x00FF;

    pInitCfg->extendParameters.breakFieldSyncBreakTxBitsNum = UARTDRV_BREAK_FIELD_SYNC_BREAK_TX_BITS_NUM_13;
    pInitCfg->extendParameters.breakFieldDelimiterTxBitsNum = UARTDRV_BREAK_FIELD_DELIMITER_TX_BITS_NUM_1;
    pInitCfg->extendParameters.syncBreakRxBitsNum           = UARTDRV_LIN_SYNC_BREAK_RX_BITS_NUM_11;
    pInitCfg->extendParameters.linBaudrateRxTimeoutBitsNum  = 0x64;

    pInitCfg->extendParameters.autoBaudRateMode = UARTDRV_AUTO_BAUDRATE_MODE_0;

    pInitCfg->extendParameters.dmaSelection = UARTDRV_DMA_SELECTION_TX_RX_DIS;

    pInitCfg->extendParameters.driverEnAssertionTime           = 4;
    pInitCfg->extendParameters.driverEnDeassertionTime         = 2;
    pInitCfg->extendParameters.driverEnablePolarityActiveInLow = true;

    pInitCfg->extendFeatures.wakeUpEn                = false;
    pInitCfg->extendFeatures.dmaEn                   = false;
    pInitCfg->extendFeatures.autoBaudRateDetectionEn = false;
    pInitCfg->extendFeatures.rxInvertEn              = false;
    pInitCfg->extendFeatures.txInvertEn              = false;
    pInitCfg->extendFeatures.dataInvertEn            = false;
    pInitCfg->extendFeatures.loopEn                  = false;
    pInitCfg->extendFeatures.linBaudrateAutoDetectEn = false;
    pInitCfg->extendFeatures.linBreakDetectEn        = true;
    pInitCfg->extendFeatures.cosplayer               = UARTDRV_COSPLAY_UART;
}

/*! \brief Set the config for the uart module
 *
 * This function initializes the run-time state structure to provide for module configuration
 *
 * \param[in] obj :pointer to UART driver instance
 * \param[in] pInitCfg :the pointer to the user configuration
 * \return: void
 */
void UartDrv_SetConfig(UartDrvType *obj, const UartDrv_InitCfgType *pInitCfg)
{
    /* Disable Uart Module to make sure that some register be configured successfully */
    UartReg_EnableModule(obj->reg, false);

    /* Clear tx&rx fifo */
    UartReg_FlushTxFifo(obj->reg);

    UartReg_FlushRxFifo(obj->reg);

    UartDrv_InitBasicParameters(obj, &pInitCfg->basicParameters);

    UartDrv_InitExtendParameters(obj, &pInitCfg->extendParameters, &pInitCfg->extendFeatures);

    /* Enable Uart module */
    UartReg_EnableModule(obj->reg, true);

    /* Clear all Interrupt status or flag, avoid to enter interrupt routines only in Module is enabled */
    UartDrv_ClearStatus(obj, UARTDRV_STATUS_ISR_ALL);
}

/*! \brief Enable or disable the uart module
 *
 * This function enables or disables the uart module
 *
 * \param[in] obj :pointer to UART driver instance
 * \param[in] isEnable:
 *            0: UART disabled
 *            1: UART enabled
 * \return: void
 */
void UartDrv_EnableModule(UartDrvType *obj, bool isEnable)
{
    /* Enable or disable Uart module */
    UartReg_EnableModule(obj->reg, isEnable);
}

/*! \brief Get received data number in Rx FIFO
 *
 * This function gets received data number in Rx FIFO
 *
 * \param[in] obj : pointer to UART driver instance
 * \return : data counter in Rx FIFO
 */
uint8_t UartDrv_GetRxCounter(const UartDrvType *obj)
{
    return UartReg_GetRxCounter(obj->reg);
}

/*! \brief Get wait to transmit data number in Tx FIFO
 *
 * This function gets wait to transmit data number in Tx FIFO
 *
 * \param[in] obj : pointer to UART driver instance
 * \return : data counter in Tx FIFO
 */
uint8_t UartDrv_GetTxCounter(const UartDrvType *obj)
{
    return UartReg_GetTxCounter(obj->reg);
}

/*! \brief clear all data of Tx FIFO
 *
 * This function clears all data of Tx FIFO
 *
 * \param[in] obj : pointer to UART driver instance
 */
void UartDrv_ClearTxFifo(const UartDrvType *obj)
{
    /* Clear tx fifo */
    UartReg_FlushTxFifo(obj->reg);
}

/*! \brief clear all data of Rx FIFO
 *
 * This function clears all data of Rx FIFO
 *
 * \param[in] obj : pointer to UART driver instance
 */
void UartDrv_ClearRxFifo(const UartDrvType *obj)
{
    /* Clear rx fifo */
    UartReg_FlushRxFifo(obj->reg);
}

/*! \brief Set the threshold value of Rx FIFO
 *
 * This function sets the threshold value of Rx FIFO
 *
 * \param[in] obj : pointer to the instance
 * \param[in] txWater : threshold value (range 0 to 3)
 * \return : void
 */
void UartDrv_SetRxWater(const UartDrvType *obj, uint8_t rxWater)
{
    if(true == UartReg_GetEnable(obj->reg))
    {
        UartReg_EnableModule(obj->reg, false);
        UartReg_SetRxWater(obj->reg, rxWater);
        UartReg_EnableModule(obj->reg, true);
    }
    else
    {
        UartReg_SetRxWater(obj->reg, rxWater);
    }
}

/*! \brief Set the threshold value of Tx FIFO
 *
 * This function sets the threshold value of Tx FIFO
 *
 * \param[in] obj : pointer to the instance
 * \param[in] txWater : threshold value (range 0 to 3)
 * \return : void
 */
void UartDrv_SetTxWater(const UartDrvType *obj, uint8_t txWater)
{
    if(true == UartReg_GetEnable(obj->reg))
    {
        UartReg_EnableModule(obj->reg, false);
        UartReg_SetTxWater(obj->reg, txWater);
        UartReg_EnableModule(obj->reg, true);
    }
    else
    {
        UartReg_SetTxWater(obj->reg, txWater);
    }
}

/*! \brief Send lin sync break field
 *
 * This function sends lin sync break field
 *
 * \param[in] obj : pointer to UART driver instance
 * \return : void
 */
void UartDrv_SendLinBreakField(const UartDrvType *obj)
{
    UartReg_ReqTxBreak(obj->reg);
}

/*! \brief Enable or disable the Line break detect
 *
 * This function enables or disables the Line break detect
 *
 * \param[in] obj :pointer to UART driver instance
 * \param[in] isEnable:
 *            0: Line break detect disable
 *            1: Line break detect enable
 * \return: void
 */
void UartDrv_EnableLineBreakDetect(const UartDrvType *obj, bool isEnable)
{
    UartReg_EnableLineBreakDetectFeature(obj->reg, isEnable);
}

/*! \brief Set Auto baud rate enable or disable
 *
 *  this function enable auto baudrate features
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] enable:
 *            0: Auto baud rate detection is disabled.
 *            1: Auto baud rate detection is enabled.
 * \return: void
 */
void  UartDrv_EnableAutoBaudrateFeature(const UartDrvType *obj, bool enable)
{
    UartReg_EnableAutoBaudrateFeature(obj->reg, enable);
}

/*! \brief Initializes the UART driver module
 *
 * This function initializes UART driver by setting the register instance to it.
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] reg : pointer to UART register instance
 * \return: void
 */
void UartDrv_Init(UartDrvType *obj, UartRegType *pReg)
{
    obj->reg = pReg;

    /* Clear tx&rx fifo */
    UartReg_FlushTxFifo(obj->reg);

    UartReg_FlushRxFifo(obj->reg);

    obj->reg->CR1 = 0;
}

/*! \brief DeInit the uart module to default
 *
 * This function call back in the usage of low power or sleep requirements
 *
 * \param[in] obj : pointer to UART driver instance
 * \return: void
 */
void UartDrv_DeInit(UartDrvType *obj)
{
    /* Clear all Interrupt status or flag, avoid to enter interrupt routines only in Module is enabled */
    UartDrv_ClearStatus(obj, UARTDRV_STATUS_ISR_ALL);

    /* Disable all Interrupt enable bit */
    UartDrv_SetInterruptReq(obj, UARTDRV_ISR_SRC_ALL, false);

    /* Clear tx&rx fifo */
    UartReg_FlushTxFifo(obj->reg);
    UartReg_FlushRxFifo(obj->reg);

    /* Disable module */
    UartReg_EnableModule(obj->reg, false);
}
