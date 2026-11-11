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

#include "spi_drv.h"

/******************************************************************************
 * the defines
 *****************************************************************************/

/******************************************************************************
 * the typedefs
 *****************************************************************************/

/******************************************************************************
 * the globals
 *****************************************************************************/

/******************************************************************************
 * the static function declarations
 *****************************************************************************/
static void                     SpiDrv_GoldenSectionAlgorithm(SpiDrv_GoldenSectionInfoType *pGoldenSectionInfo);
static void                     SpiDrv_InitTxCommand(SpiRegType *obj, const SpiDrv_InitCfgType *pInitCfg);
static void                     SpiDrv_InitBasicParameters(SpiRegType *obj, const SpiDrv_BasicParametersType *pBasicParameters);
static void                     SpiDrv_InitExtendParameters(SpiRegType *obj, const SpiDrv_ExtendParametersType *pExtendParameters, const SpiDrv_ExtendFeaturesType *pExtendFeatures);
static SpiDrv_ShiftFirstBitType SpiDrv_GetDataShiftDirection(const SpiDrvType *obj);

/******************************************************************************
 * the functions
 *****************************************************************************/

/*! \brief the algorithm of golden section
 *
 * the algorithm of golden section
 *
 * \param[in] pGoldenSectionInfo : the golden section structure
 * \return: void
 */
static void SpiDrv_GoldenSectionAlgorithm(SpiDrv_GoldenSectionInfoType *pGoldenSectionInfo)
{
    uint8_t  tPrescalerIdx = 0;
    uint8_t  tMinIdx       = 0;
    uint32_t tDiffMin      = 0;
    uint32_t tFreq         = 0;
    uint16_t tDivIdx       = 0;
    bool     tScanOver     = false;

    SpiDrv_CalculateTblType tCalculateTbl[8] = {0};
    const uint32_t          prescalerList[8] = {1, 2, 4, 8, 16, 32, 64, 128};
    const uint8_t           prescalerNums    = 8;
    const uint32_t          maxDivValue      = 0xFF + 2;

    for(tPrescalerIdx = 0; tPrescalerIdx < prescalerNums; tPrescalerIdx++)
    {
        tCalculateTbl[tPrescalerIdx].diff = 0xFFFFFFFF;
        tCalculateTbl[tPrescalerIdx].div  = 0;
    }

    for(tPrescalerIdx = 0; tPrescalerIdx < prescalerNums; tPrescalerIdx++)
    {
        for(tDivIdx = 2; tDivIdx <= maxDivValue; tDivIdx++)
        {
            tFreq = (pGoldenSectionInfo->freqInput / prescalerList[tPrescalerIdx]) / tDivIdx;

            if(tFreq == pGoldenSectionInfo->freqTargetOut)
            {
                tCalculateTbl[tPrescalerIdx].div          = tDivIdx;
                tCalculateTbl[tPrescalerIdx].prescalerIdx = tPrescalerIdx;
                tCalculateTbl[tPrescalerIdx].diff         = 0;

                tScanOver = true;
                break;
            }
            else if(tFreq < pGoldenSectionInfo->freqTargetOut)
            {
                tCalculateTbl[tPrescalerIdx].div          = tDivIdx;
                tCalculateTbl[tPrescalerIdx].prescalerIdx = tPrescalerIdx;
                tCalculateTbl[tPrescalerIdx].diff         = pGoldenSectionInfo->freqTargetOut - tFreq;
                break;
            }
        }

        if(tScanOver == true)
        {
            break;
        }
    }

    tMinIdx  = 0;
    tDiffMin = tCalculateTbl[tMinIdx].diff;
    for(tPrescalerIdx = 1; tPrescalerIdx < prescalerNums; tPrescalerIdx++)
    {
        if(tCalculateTbl[tPrescalerIdx].diff < tDiffMin)
        {
            tDiffMin = tCalculateTbl[tPrescalerIdx].diff;
            tMinIdx  = tPrescalerIdx;
        }
    }

    if(tCalculateTbl[tMinIdx].div < 2)
    {
        tFreq = (pGoldenSectionInfo->freqInput / prescalerList[prescalerNums - 1]) / maxDivValue;

        pGoldenSectionInfo->bestOutPrescaler = prescalerNums - 1;
        pGoldenSectionInfo->bestOutDiv       = maxDivValue - 2;
        pGoldenSectionInfo->bestOutFreq      = tFreq;
    }
    else
    {
        pGoldenSectionInfo->bestOutPrescaler = tCalculateTbl[tMinIdx].prescalerIdx;
        pGoldenSectionInfo->bestOutDiv       = tCalculateTbl[tMinIdx].div - 2;
        pGoldenSectionInfo->bestOutFreq      = (uint32_t)(pGoldenSectionInfo->freqTargetOut - tCalculateTbl[tMinIdx].diff);
    }
}

/*! \brief Sets the Transmit Command Register (TCR) parameters
 *
 * this function initial the spi parameters about clock polarity and other parameters
 *
 * \param[in] obj : base reg address for the SPI instance
 * \param[in] pInitCfg : Structure that contains the settings
 * \return: void
 */
static void SpiDrv_InitTxCommand(SpiRegType *obj, const SpiDrv_InitCfgType *pInitCfg)
{
    uint32_t tTcr       = 0;
    uint8_t  tPrescaler = 0;
    uint32_t tDiv       = 0;

    tTcr = SpiReg_GetTcr(obj);

    /* Normal transfer, used the default configuration, set it again if extend features used */
    SpiDrv_SetTxDataMask(&tTcr, false);
    SpiDrv_SetRxDataMask(&tTcr, false);

    /* First Bit shift */
    SpiDrv_SetLowBitFirstTransfer(&tTcr, pInitCfg->basicParameters.dataShiftFirstBit);

    /* CPHA */
    SpiDrv_SetClockPhase(&tTcr, pInitCfg->basicParameters.clockPhase);

    /* CPOL */
    SpiDrv_SetClockPolarity(&tTcr, pInitCfg->basicParameters.clockPolarity);

    {
        SpiDrv_GoldenSectionInfoType tGoldenSectionInfo;

        tGoldenSectionInfo.freqTargetOut = pInitCfg->basicParameters.baudRate;
        tGoldenSectionInfo.freqInput     = pInitCfg->basicParameters.busClockFreq;

        SpiDrv_GoldenSectionAlgorithm(&tGoldenSectionInfo);

        tPrescaler = (uint8_t)tGoldenSectionInfo.bestOutPrescaler;
        tDiv       = tGoldenSectionInfo.bestOutDiv;
        /* SCK Div */
        SpiReg_SetSckDiv(obj, (uint8_t)tDiv);
    }

    /* Prescaler */
    SpiDrv_SetPrescaler(&tTcr, tPrescaler);

    /* Frame Size */
    SpiDrv_SetFrameSize(&tTcr, (uint16_t)(pInitCfg->basicParameters.frameBitSize - 1u));

    /* Byte-Swap, only in the frame size /32 != 0u case, can used the byte swap */
    if((pInitCfg->basicParameters.frameBitSize & SPIDRV_ONE_FRAME_BITS_MAX_NUM) != 0u)
    {
        SpiDrv_SetByteSwap(&tTcr, pInitCfg->extendFeatures.byteSwapEn);
    }
    else
    {
        SpiDrv_SetByteSwap(&tTcr, 0u);
    }

    /* Select PCS */
    SpiDrv_SetPcsSelection(&tTcr, pInitCfg->basicParameters.pcsSelection);

    /* PIN Cfg */
    switch(pInitCfg->extendParameters.pinCfg)
    {
    case SPIDRV_PIN_CFG_SIN_IN_SOUT_OUT:
        /* only support single-full duplex */
        SpiDrv_SetTransferWidth(&tTcr, 0);

        /* TX RX MASK */
        SpiDrv_SetRxDataMask(&tTcr, pInitCfg->extendFeatures.rxMaskEn);
        SpiDrv_SetTxDataMask(&tTcr, pInitCfg->extendFeatures.txMaskEn);
        break;

    case SPIDRV_PIN_CFG_HALF_DUPLEX_SIN:
        /* For half-duplex parallel transfers, either Receive Data Mask (RXMSK) or Transmit Data Mask (TXMSK) must be set */
        SpiDrv_SetRxDataMask(&tTcr, 1);
        SpiDrv_SetTxDataMask(&tTcr, 0);

        /* Duplex, single line or double line */
        if(pInitCfg->extendParameters.duplexType == SPIDRV_DUPLEX_HALF_DUPLEX_IN_SINGLE_LINE)
        {
            SpiDrv_SetTransferWidth(&tTcr, 0);
        }
        else if(pInitCfg->extendParameters.duplexType == SPIDRV_DUPLEX_HALF_DUPLEX_IN_DOUBLE_LINE)
        {
            SpiDrv_SetTransferWidth(&tTcr, 1);
        }
        break;

    case SPIDRV_PIN_CFG_HALF_DUPLEX_SOUT:
        /* Duplex, single line or double line */
        if(pInitCfg->extendParameters.duplexType == SPIDRV_DUPLEX_HALF_DUPLEX_IN_SINGLE_LINE)
        {
            SpiDrv_SetTransferWidth(&tTcr, 0);
        }
        else if(pInitCfg->extendParameters.duplexType == SPIDRV_DUPLEX_HALF_DUPLEX_IN_DOUBLE_LINE)
        {
            SpiDrv_SetTransferWidth(&tTcr, 1);
        }

        /* For half-duplex parallel transfers, either Receive Data Mask (RXMSK) or Transmit Data Mask (TXMSK) must be set */
        SpiDrv_SetRxDataMask(&tTcr, 1);
        SpiDrv_SetTxDataMask(&tTcr, 0);
        break;

    case SPIDRV_PIN_CFG_SIN_OUT_SOUT_IN:
        /* only support single-full duplex */
        SpiDrv_SetTransferWidth(&tTcr, 0);

        /* TX RX MASK */
        SpiDrv_SetRxDataMask(&tTcr, pInitCfg->extendFeatures.rxMaskEn);
        SpiDrv_SetTxDataMask(&tTcr, pInitCfg->extendFeatures.txMaskEn);
        break;

    default:
        /* only support single-full duplex */
        SpiDrv_SetTransferWidth(&tTcr, 0);

        /* TX RX MASK */
        SpiDrv_SetRxDataMask(&tTcr, pInitCfg->extendFeatures.rxMaskEn);
        SpiDrv_SetTxDataMask(&tTcr, pInitCfg->extendFeatures.txMaskEn);
        break;
    }

    obj->TCR = tTcr;
}

/*! \brief Init the spi module basic parameters and basic functions
 *
 * this function initializes the basic features with the parameters
 *
 * \param[in] obj : pointer to the instance
 * \param[in] pBasicParameters : the conbination of basic parameters
 * \return: void
 */
static void SpiDrv_InitBasicParameters(SpiRegType *obj, const SpiDrv_BasicParametersType *pBasicParameters)
{
    /* Configures the SPI in master or slave mode */
    SpiReg_SetNodeMode(obj, pBasicParameters->isMasterNode);

    /* Peripheral Chip Select Polarity */
    SpiReg_SetPcsPolarity(obj, (uint8_t)(((uint8_t)pBasicParameters->pcsPolarity) << ((uint8_t)pBasicParameters->pcsSelection)));
}

/*! \brief Init the spi module extend parameters and extend functions
 *
 * this function initializes the extend features with the parameters
 *
 * \param[in] obj : pointer to the instance
 * \param[in] pExtendParameters: the conbination of all extend parameters
 * \param[in] pExtendFeatures: the conbination of the all extend features
 * \return: void
 */
static void SpiDrv_InitExtendParameters(SpiRegType *obj, const SpiDrv_ExtendParametersType *pExtendParameters, const SpiDrv_ExtendFeaturesType *pExtendFeatures)
{
    /* DMA TX */
    SpiReg_SetTxDMA(obj, pExtendFeatures->dmaTxEn);

    /* DMA RX */
    SpiReg_SetRxDMA(obj, pExtendFeatures->dmaRxEn);

    /* NO-STALL */
    SpiReg_SetNoStallMode(obj, pExtendFeatures->noStallEn);

    /* CIRCULAR FIFO */
    SpiReg_SetCircularFIFO(obj, pExtendFeatures->circularFifoEn);

    /* Slave AUTO-PCS */
    if(SpiReg_GetNodeMasterState(obj) == false)
    {
        SpiReg_SetAutoCS(obj, pExtendFeatures->slaveAutoPcsEn);
    }

    /* Stop or Debug to use module */
    SpiReg_EnableDozeMode(obj, pExtendFeatures->stopEn);
    SpiReg_EnableDebugMode(obj, pExtendFeatures->dbgEn);

    /* Delay between transfers */
    SpiReg_SetDelayDBT(obj, pExtendParameters->delayBetweenTransfer);

    /* Delay from pcs to sck */
    SpiReg_SetDelayPcsToSck(obj, pExtendParameters->delayFromPcsToSck);

    /* Delay from sck to pcs */
    SpiReg_SetDelaySckToPcs(obj, pExtendParameters->delayFromSckToPcs);

    /* Master sck delay ticks */
    SpiReg_SetMstSckDelay(obj, pExtendParameters->masterSampleSckDelay);

    /* PIN Cfg */
    switch(pExtendParameters->pinCfg)
    {
    case SPIDRV_PIN_CFG_SIN_IN_SOUT_OUT:
        SpiReg_SetOutCfg(obj, pExtendParameters->outCfg);
        SpiReg_SetPinCfg(obj, 0);
        break;

    case SPIDRV_PIN_CFG_HALF_DUPLEX_SIN:
        SpiReg_SetPinCfg(obj, 1);
        /* If performing half-duplex transfers, this bit must be set */
        SpiReg_SetOutCfg(obj, 1);
        break;

    case SPIDRV_PIN_CFG_HALF_DUPLEX_SOUT:
        SpiReg_SetPinCfg(obj, 2);
        /* If performing half-duplex transfers, this bit must be set */
        SpiReg_SetOutCfg(obj, 1);
        break;

    case SPIDRV_PIN_CFG_SIN_OUT_SOUT_IN:
        SpiReg_SetOutCfg(obj, pExtendParameters->outCfg);
        SpiReg_SetPinCfg(obj, 3);
        break;

    default:
        SpiReg_SetOutCfg(obj, pExtendParameters->outCfg);
        SpiReg_SetPinCfg(obj, 0);
        break;
    }
}

/*! \brief Get default configures the module for configuration structure
 *
 * This function gets default configures the module for user configuration structure
 *
 * \param[out] pInitCfg :pointer to configuration structure
 * \return: void
 */
void SpiDrv_GetDefaultConfig(SpiDrv_InitCfgType *pInitCfg)
{
    /* If no user configuration, used the default configuration */
    pInitCfg->basicParameters.busClockFreq      = 120000000ul;
    pInitCfg->basicParameters.baudRate          = 1000000ul;
    pInitCfg->basicParameters.isMasterNode      = true;
    pInitCfg->basicParameters.clockPhase        = SPIDRV_CLK_PHASE_DATA_SAMPLE_ON_LEADING_EDGE;
    pInitCfg->basicParameters.clockPolarity     = SPIDRV_CLK_POLARITY_IDLE_IN_LOW;
    pInitCfg->basicParameters.pcsSelection      = SPIDRV_PCS_SEL_PCS0;
    pInitCfg->basicParameters.pcsPolarity       = SPIDRV_PCS_POLARITY_ACTIVE_LOW;
    pInitCfg->basicParameters.dataShiftFirstBit = SPIDRV_SHIFT_FIRST_BIT_LSB;
    pInitCfg->basicParameters.frameBitSize      = 8;

    pInitCfg->extendFeatures.dmaTxEn        = false;
    pInitCfg->extendFeatures.dmaRxEn        = false;
    pInitCfg->extendFeatures.noStallEn      = false;
    pInitCfg->extendFeatures.circularFifoEn = false;
    pInitCfg->extendFeatures.byteSwapEn     = false;
    pInitCfg->extendFeatures.slaveAutoPcsEn = false;
    pInitCfg->extendFeatures.dbgEn          = false;
    pInitCfg->extendFeatures.rxMaskEn       = false;
    pInitCfg->extendFeatures.txMaskEn       = false;
    pInitCfg->extendFeatures.stopEn         = false;

    pInitCfg->extendParameters.duplexType           = SPIDRV_DUPLEX_FULL_DUPLEX;
    pInitCfg->extendParameters.delayBetweenTransfer = 10; /* N* fModule (Busclock / Prescaler) */
    pInitCfg->extendParameters.delayFromPcsToSck    = 10; /* N* fModule (Busclock / Prescaler) */
    pInitCfg->extendParameters.delayFromSckToPcs    = 10; /* N* fModule (Busclock / Prescaler) */
    pInitCfg->extendParameters.masterSampleSckDelay = 0;
    pInitCfg->extendParameters.pinCfg               = SPIDRV_PIN_CFG_SIN_IN_SOUT_OUT;
    pInitCfg->extendParameters.outCfg               = SPIDRV_OUTCFG_IN_OLD_VALUE;
}

/*! \brief Set the spi module parameters include basic&extend features
 *
 * this function initializes the run-time state structure to provide for module configuration
 *
 * \param[in] obj : pointer to the instance
 * \param[in] pInitCfg: the pointer to the user configuration
 * \return: void
 */
void SpiDrv_SetConfig(SpiDrvType *obj, const SpiDrv_InitCfgType *pInitCfg)
{
    /* Disable the Module to make sure that some register be configured successfully */
    SpiReg_EnableModule(obj->reg, false);

    /* clear Tx&Rx FIFO */
    SpiReg_ResetTxFIFO(obj->reg);
    SpiReg_ResetRxFIFO(obj->reg);

    /* set some duration after reset the module */
    __asm volatile("nop");
    __asm volatile("nop");
    __asm volatile("nop");

    /* Set the basic parameters */
    SpiDrv_InitBasicParameters(obj->reg, &pInitCfg->basicParameters);

    /* Set the extend features if used */
    SpiDrv_InitExtendParameters(obj->reg, &pInitCfg->extendParameters, &pInitCfg->extendFeatures);

    /* Enable the module */
    SpiReg_EnableModule(obj->reg, true);

    /* Configure the tx parameters */
    SpiDrv_InitTxCommand(obj->reg, pInitCfg);
}

/*! \brief Resets the SPI internal logic and registers to their default settings
 *
 * this function instance an object and reset module
 *
 * \param[in/out] this : pointer to the instance
 * \param[in] pReg : the phycial module base address pointer
 * \return: void
 */
void SpiDrv_Init(SpiDrvType *obj, SpiRegType *pReg)
{
    obj->reg = pReg;

    /* Reset tx&rx fifo first after reset or reinit or power-on */
    SpiReg_ResetTxFIFO(obj->reg);
    SpiReg_ResetRxFIFO(obj->reg);

    /* Reset the module */
    SpiReg_ResetModule(obj->reg, true);

    /* set some duration after reset the module */
    __asm volatile("nop");
    __asm volatile("nop");
    __asm volatile("nop");
    /* Notice: the reset bit should be clear by software, 7/5/2022 Changed by CVAchip */
    obj->reg->CR = 0;
}

/*! \brief Set the module to special condition
 *
 * call back in the usage of Low power or sleep requirements
 *
 * \param[in] obj : pointer to the instance
 * \return: void
 */
void SpiDrv_DeInit(SpiDrvType *obj)
{
    /* clear Tx&Rx FIFO */
    SpiReg_ResetTxFIFO(obj->reg);
    SpiReg_ResetRxFIFO(obj->reg);
    __asm volatile("nop");
    __asm volatile("nop");
    __asm volatile("nop");

    SpiReg_ResetModule(obj->reg, true);
    /* set some duration after reset the module */
    __asm volatile("nop");
    __asm volatile("nop");
    __asm volatile("nop");
    /* Notice: the reset bit should be clear by software, 7/5/2022 Changed by CVAchip */
    SpiReg_ResetModule(obj->reg, false);

    /* Disable the Module */
    SpiReg_EnableModule(obj->reg, false);
}

/*! \brief Get the data shift direction of transfer
 *
 * this function get the current configuration about data shift method
 *
 * \param[in] obj : pointer to the instance
 * \return: return the data shift direction
 */
static SpiDrv_ShiftFirstBitType SpiDrv_GetDataShiftDirection(const SpiDrvType *obj)
{
    SpiDrv_ShiftFirstBitType tRtn = SPIDRV_SHIFT_FIRST_BIT_MSB;

    if(SpiReg_GetTransferDataBitLsbState(obj->reg) == true)
    {
        tRtn = SPIDRV_SHIFT_FIRST_BIT_LSB;
    }

    return tRtn;
}

/*! \brief Get the status of the SpiDrv_StatusType of event
 *
 * this function read out the special status what want to be read
 *
 * \param[in] obj : pointer to the instance
 * \param[in] status: which status to be read out
 * \return: bool
 *         true: The status is exist
 *         false: The status is not exist
 */
bool SpiDrv_GetStatus(const SpiDrvType *obj, SpiDrv_StatusType status)
{
    bool tRtn = false;

    uint32_t tRegValue = 0;

    switch(status)
    {
    case SPIDRV_STATUS_TX_DATA:
        tRegValue = SpiReg_GetTxDataFlag(obj->reg);
        break;

    case SPIDRV_STATUS_RX_DATA:
        tRegValue = SpiReg_GetRxDataFlag(obj->reg);
        break;

    case SPIDRV_STATUS_RX_WORD_DONE:
        tRegValue = SpiReg_GetRxWordDoneFlag(obj->reg);
        break;

    case SPIDRV_STATUS_FRAME_DONE:
        tRegValue = SpiReg_GetFrameDoneFlag(obj->reg);
        break;

    case SPIDRV_STATUS_XFR_DONE:
        tRegValue = SpiReg_GetMasterTransferDoneFlag(obj->reg);
        break;

    case SPIDRV_STATUS_TX_UF:
        tRegValue = SpiReg_GetTxUnderFlowFlag(obj->reg);
        break;

    case SPIDRV_STATUS_RX_OF:
        tRegValue = SpiReg_GetRxOverFlowFlag(obj->reg);
        break;

    case SPIDRV_STATUS_BUSY:
        tRegValue = SpiReg_GetBusyFlag(obj->reg);
        break;

    default:
        break;
    }

    if(tRegValue != 0ul)
    {
        tRtn = true;
    }

    return tRtn;
}

/*! \brief Clear the status
 *
 * this function clear the special status falg
 *
 * \param[in] obj : pointer to the instance
 * \param[in] status : combination of any SpiDrv_StatusType event
 *           example: Status = (SPIDRV_STATUS_RX_WORD_DONE | SPIDRV_STATUS_FRAME_DONE)
 * \return: void
 */
void SpiDrv_ClearStatus(SpiDrvType *obj, uint32_t status)
{
    /* RX_WORD_DONE */
    if((status & SPIDRV_STATUS_RX_WORD_DONE) != 0ul)
    {
        SpiReg_ClearRxWordDoneFlag(obj->reg);
    }

    /* FRAME_DONE */
    if((status & SPIDRV_STATUS_FRAME_DONE) != 0ul)
    {
        SpiReg_ClearFrameDoneFlag(obj->reg);
    }

    /* MST_TRANSFER_DONE */
    if((status & SPIDRV_STATUS_XFR_DONE) != 0ul)
    {
        SpiReg_ClearMasterTransferDoneFlag(obj->reg);
    }

    /* TX_UF */
    if((status & SPIDRV_STATUS_TX_UF) != 0ul)
    {
        SpiReg_ClearTxUnderFlowFlag(obj->reg);
    }

    /* RX_OF */
    if((status & SPIDRV_STATUS_RX_OF) != 0ul)
    {
        SpiReg_ClearRxOverFlowFlag(obj->reg);
    }
}

/*! \brief Master Sync tx data, sent and received data from other node
 *
 *      _____  DATA DATA DATA DATA __________
 * PCS       |_____________________|
 *
 * \param[in] obj : pointer to the instance
 * \param[in] frameSizeBitType: the data width to describe the pTxBuffer
 * \param[in] txFrameNums: the nums data to be sent
 * \param[in] pTxBuffer: the transmit data buffer pointer
 * \param[in] pRxBuffer: the pointer for the read-out datas
 * \return: bool
 *         false: the current tx fifo is full, no enough space for this transmit
 *         true: no error
 */
bool SpiDrv_MasterSyncTransfer(SpiDrvType *obj, SpiDrv_FrameSizeBitType frameSizeBitType, uint16_t txFrameNums, const void *pTxBuffer, void *pRxBuffer)
{
    bool    tRtn        = true;
    uint8_t tTxFreeNums = 0;

    tTxFreeNums = SPIDRV_TX_FIFO_SIZE - SpiReg_GetTxFifoCounter(obj->reg);

    if(tTxFreeNums >= txFrameNums)
    {
        uint32_t tTcr = 0, tTimeout = 0;
        uint16_t x = 0;

        tTcr = SpiReg_GetTcr(obj->reg);
        SpiDrv_SetContinuousCmd(&tTcr, false);
        SpiDrv_SetContinuousTransfer(&tTcr, true);
        SpiDrv_SetTxDataMask(&tTcr, false);
        SpiDrv_SetRxDataMask(&tTcr, false);
        SpiDrv_SetFrameSize(&tTcr, (uint16_t)((uint16_t)frameSizeBitType * 8u - 1u));
        SpiReg_SetTcr(obj->reg, tTcr);

        for(x = 0; x < txFrameNums; x++)
        {
            while(SpiReg_GetTxDataFlag(obj->reg) == false)
            {
                /* Wait tx fifo avaliable */
                tTimeout++;
                if(tTimeout > 1000ul)
                {
                    tRtn = false;
                    break;
                }
            }

            /* Transmit data */
            if(frameSizeBitType == SPIDRV_FRAME_SIZE_BIT_TYPE_BYTE)
            {
                obj->reg->TDR = ((uint8_t *)pTxBuffer)[x];
            }
            else if(frameSizeBitType == SPIDRV_FRAME_SIZE_BIT_TYPE_HALF_WORD)
            {
                obj->reg->TDR = ((uint16_t *)pTxBuffer)[x];
            }
            else
            {
                obj->reg->TDR = ((uint32_t *)pTxBuffer)[x];
            }

            tTimeout = 0;

            while((SpiReg_GetRxFifoEmptyState(obj->reg) == true))
            {
                tTimeout++;
                if(tTimeout > 1000ul)
                {
                    tRtn = false;
                    break;
                }
            }

            if(frameSizeBitType == SPIDRV_FRAME_SIZE_BIT_TYPE_BYTE)
            {
                ((uint8_t *)pRxBuffer)[x] = (obj->reg->RDR & 0xFF);
            }
            else if(frameSizeBitType == SPIDRV_FRAME_SIZE_BIT_TYPE_HALF_WORD)
            {
                ((uint16_t *)pRxBuffer)[x] = (obj->reg->RDR & 0xFFFF);
            }
            else
            {
                ((uint32_t *)pRxBuffer)[x] = obj->reg->RDR;
            }
        }

        SpiDrv_SetContinuousCmd(&tTcr, false);
        SpiDrv_SetContinuousTransfer(&tTcr, false);
        SpiReg_SetTcr(obj->reg, tTcr);
    }
    else
    {
        /* Transfer by byte, but not enough space to fill tx datas in bytes */
        tRtn = false;
    }

    return tRtn;
}

/*! \brief Send one short frame each frame bits numbers is equal to or less than 32bits, every time hard set pcs signal again
 *        the DBT feature is valid
 *      _____   DATA (DBT)  _________   DATA(DBT)   __________
 * PCS       |_____________|         |_____________|
 *
 * \param[in] obj : pointer to the instance
 * \param[in] txData:data to be sent
 * \param[in] frameSizeBitType:the frame bit width(8bit/16bit/32bit) to describe the pTxBuffer data width type
 * \return: bool
 *         true: no err
 *         false: no enough space for the current tx requirement
 */
bool SpiDrv_AsyncSingleFrameTransfer(SpiDrvType *obj, uint32_t txData, SpiDrv_FrameSizeBitType frameSizeBitType)
{
    bool    tRtn        = true;
    uint8_t tTxFreeNums = 0;

    tTxFreeNums = SPIDRV_TX_FIFO_SIZE - SpiReg_GetTxFifoCounter(obj->reg) - 1u;

    if(tTxFreeNums > 0)
    {
        uint32_t tTcr = 0;

        tTcr = SpiReg_GetTcr(obj->reg);
        SpiDrv_SetContinuousCmd(&tTcr, false);
        SpiDrv_SetContinuousTransfer(&tTcr, false);
        SpiDrv_SetFrameSize(&tTcr, (uint16_t)((uint16_t)frameSizeBitType * 8u - 1u));
        SpiReg_SetTcr(obj->reg, tTcr);

        if(frameSizeBitType == SPIDRV_FRAME_SIZE_BIT_TYPE_BYTE)
        {
            /* Transmit data */
            obj->reg->TDR = (txData & 0xFF);
        }
        else if(frameSizeBitType == SPIDRV_FRAME_SIZE_BIT_TYPE_HALF_WORD)
        {
            /* Transmit data */
            obj->reg->TDR = (txData & 0xFFFF);
        }
        else
        {
            /* Transmit data */
            obj->reg->TDR = txData;
        }
    }
    else
    {
        /* Transfer by byte, but not enough space to fill tx datas in bytes */
        tRtn = false;
    }

    return tRtn;
}

/*! \brief Send more than 32bits frame one time, the DBT feature is invalid
 *
 *      _____  DATA DATA DATA DATA __________
 * PCS       |_____________________|
 *
 * \param[in] obj : pointer to the instance
 * \param[in] txFrameNums: the nums data to be sent
 * \param[in] pTxBuffer: th pointer of which data to be sent
 * \param[in] frameSizeBitType:the frame bit width(8bit/16bit/32bit) to describe the pTxBuffer data width type
 * \param[in] littleEndDian: transfer byte turn
 * \return: bool
 *         true: no err
 *         false: no enough space for the current tx requirement
 */
bool SpiDrv_AsyncLongFrameTransfer(SpiDrvType *obj, uint16_t txFrameNums, const void *pTxBuffer, SpiDrv_FrameSizeBitType frameSizeBitType, bool littleEndDian)
{
    bool     tRtn         = true;
    uint8_t  tTxFreeNums  = 0;
    uint16_t tTxBytesNums = txFrameNums * (uint16_t)frameSizeBitType;

    tTxFreeNums = SPIDRV_TX_FIFO_SIZE - SpiReg_GetTxFifoCounter(obj->reg);

    if(tTxFreeNums >= ((tTxBytesNums + 3) / 4u))
    {
        uint32_t tTcr = 0;

        tTcr = SpiReg_GetTcr(obj->reg);
        SpiDrv_SetContinuousCmd(&tTcr, false);
        SpiDrv_SetContinuousTransfer(&tTcr, false);
        SpiDrv_SetFrameSize(&tTcr, (uint16_t)(tTxBytesNums * 8u - 1u));
        SpiReg_SetTcr(obj->reg, tTcr);

        tRtn = SpiDrv_AsyncBitDataWriteIntoHwTxBuffer(obj, (uint16_t)(tTxBytesNums * 8u), pTxBuffer, littleEndDian);
    }
    else
    {
        /* Transfer by byte, but not enough space to fill tx datas in bytes */
        tRtn = false;
    }

    return tRtn;
}

/*! \brief continue Send constinues frame,each frame bits numbers is equal to or less than 32bits
 *        the DBT feature is valid
 *      _____   DATA(xbits) (DBT) DATA(xBits)__________
 * PCS       |_______________________________|
 *
 * \param[in] obj : pointer to the instance
 * \param[in] txFrameNums: the nums data to be sent
 * \param[in] pTxBuffer: th pointer of which data to be sent
 * \param[in] frameSizeBitType:the frame bit width(8bit/16bit/32bit) to describe the pTxBuffer data width type
 * \return: bool
 *         true: no err
 *         false: no enough space for the current tx requirement
 */
bool SpiDrv_AsyncContinueFrameTransfer(SpiDrvType *obj, uint16_t txFrameNums, const void *pTxBuffer, SpiDrv_FrameSizeBitType frameSizeBitType)
{
    bool    tRtn        = true;
    uint8_t tTxFreeNums = 0;

    tTxFreeNums = SPIDRV_TX_FIFO_SIZE - SpiReg_GetTxFifoCounter(obj->reg);

    if(tTxFreeNums >= txFrameNums)
    {
        uint32_t tTcr = 0;
        uint16_t i    = 0;

        tTcr = SpiReg_GetTcr(obj->reg);
        SpiDrv_SetContinuousCmd(&tTcr, false);
        SpiDrv_SetContinuousTransfer(&tTcr, true);
        SpiDrv_SetFrameSize(&tTcr, (uint16_t)((uint16_t)frameSizeBitType * 8u - 1u));
        SpiReg_SetTcr(obj->reg, tTcr);

        if(frameSizeBitType == SPIDRV_FRAME_SIZE_BIT_TYPE_BYTE)
        {
            for(i = 0; i < txFrameNums; i++)
            {
                /* Transmit data */
                obj->reg->TDR = ((uint8_t *)pTxBuffer)[i];
            }
        }
        else if(frameSizeBitType == SPIDRV_FRAME_SIZE_BIT_TYPE_HALF_WORD)
        {
            for(i = 0; i < txFrameNums; i++)
            {
                /* Transmit data */
                obj->reg->TDR = ((uint16_t *)pTxBuffer)[i];
            }
        }
        else
        {
            for(i = 0; i < txFrameNums; i++)
            {
                /* Transmit data */
                obj->reg->TDR = ((uint32_t *)pTxBuffer)[i];
            }
        }

        SpiDrv_SetContinuousTransfer(&tTcr, false);
        SpiReg_SetTcr(obj->reg, tTcr);
    }
    else
    {
        /* Transfer by byte, but not enough space to fill tx datas in bytes */
        tRtn = false;
    }

    return tRtn;
}

/*! \brief Set the link route function in the slave node with byte transfer
 *
 * this function is used for slave node to link transfer from master to other node with bytes
 *
 * \param[in] obj : pointer to the instance
 * \param[in] txBytesCnt: the data bytes to be sent
 * \param[in] pTxByteBuffer: pointer to the tx data byte buffer
 *           the tx data will fill or not by special requirement
 * \return: void
 */
void SpiDrv_SlaveAsyncLinkTransferBytes(SpiDrvType *obj, uint16_t txBytesCnt, const uint8_t *pTxByteBuffer)
{
    uint8_t tTxFreeNums = 0;

    tTxFreeNums = SPIDRV_TX_FIFO_SIZE - SpiReg_GetTxFifoCounter(obj->reg);

    if(tTxFreeNums > ((txBytesCnt + 3u) / 4u))
    {
        uint32_t tTcr           = 0;
        uint32_t i              = 0;
        uint8_t  tMultFrameNums = 0, tRestNums = 0;

        if(txBytesCnt > 0)
        {
            uint8_t tBufferIdx = 0;

            tTcr = SpiReg_GetTcr(obj->reg);
            SpiDrv_SetContinuousCmd(&tTcr, false);
            SpiDrv_SetContinuousTransfer(&tTcr, true);
            SpiDrv_SetTxDataMask(&tTcr, false);
            SpiDrv_SetRxDataMask(&tTcr, false);
            SpiDrv_SetFrameSize(&tTcr, 7u);
            SpiReg_SetTcr(obj->reg, tTcr);

            tMultFrameNums = (uint8_t)(txBytesCnt / 4u);
            tRestNums      = (txBytesCnt & 0x03);

            if(tMultFrameNums > 0)
            {
                for(i = 0; i < tMultFrameNums; i++)
                {
                    /* Transmit data */
                    obj->reg->TDR = *((uint32_t *)&pTxByteBuffer[tBufferIdx]);
                    tBufferIdx += 4;
                }
            }

            if(tRestNums > 0)
            {
                uint8_t                x = 0;
                SpiDrv_DataAlignedType tTxDataAligned;

                tTxDataAligned.wordData = 0;

                /* The rest bytes filled action */
                if(SpiDrv_GetDataShiftDirection(obj) == SPIDRV_SHIFT_FIRST_BIT_LSB)
                {
                    for(x = 0; x < tRestNums; x++)
                    {
                        tTxDataAligned.byteData[tRestNums - 1 - x] = pTxByteBuffer[tBufferIdx];
                        tBufferIdx++;
                    }
                }
                else
                {
                    for(x = 0; x < tRestNums; x++)
                    {
                        tTxDataAligned.byteData[x] = pTxByteBuffer[tBufferIdx];
                        tBufferIdx++;
                    }
                }

                /* Transmit data */
                obj->reg->TDR = tTxDataAligned.wordData;
            }
        }
    }
}

/*! \brief Set the link route function in the slave node with halfword transfer
 *
 * this function is used for slave node to link transfer from master to other node with halfwords
 *
 * \param[in] obj : pointer to the instance
 * \param[in] txHalfWordsCnt: the data halfwords to be sent
 * \param[in] pTxHalfWordBuffer: pointer to the tx data halfword buffer
 *           the tx data will fill or not by special requirement
 * \return: void
 */
void SpiDrv_SlaveAsyncLinkTransferHalfWords(SpiDrvType *obj, uint16_t txHalfWordsCnt, const uint16_t *pTxHalfWordBuffer)
{
    uint8_t tTxFreeNums = 0;

    tTxFreeNums = SPIDRV_TX_FIFO_SIZE - SpiReg_GetTxFifoCounter(obj->reg);

    if(tTxFreeNums > ((txHalfWordsCnt + 1u) / 2u))
    {
        uint32_t tTcr = 0, i = 0;
        uint16_t tMultFrameNums = 0, tRestNums = 0;

        if(txHalfWordsCnt > 0)
        {
            uint8_t tBufferIdx = 0;

            tTcr = SpiReg_GetTcr(obj->reg);
            SpiDrv_SetContinuousCmd(&tTcr, false);
            SpiDrv_SetContinuousTransfer(&tTcr, true);
            SpiDrv_SetTxDataMask(&tTcr, false);
            SpiDrv_SetRxDataMask(&tTcr, false);
            SpiDrv_SetFrameSize(&tTcr, 15u);
            SpiReg_SetTcr(obj->reg, tTcr);

            tMultFrameNums = txHalfWordsCnt;
            tRestNums      = (txHalfWordsCnt & 0x01);

            for(i = 0; i < tMultFrameNums; i++)
            {
                /* Transmit data */
                obj->reg->TDR = *((uint32_t *)&pTxHalfWordBuffer[tBufferIdx]);
                tBufferIdx += 2;
            }

            if(tRestNums > 0)
            {
                uint8_t                x = 0;
                SpiDrv_DataAlignedType tTxDataAligned;

                tTxDataAligned.wordData = 0;

                /* The rest bytes filled action */
                if(SpiDrv_GetDataShiftDirection(obj) == SPIDRV_SHIFT_FIRST_BIT_LSB)
                {
                    for(x = 0; x < tRestNums; x++)
                    {
                        tTxDataAligned.halfWordData[tRestNums - 1 - x] = pTxHalfWordBuffer[tBufferIdx];
                        tBufferIdx++;
                    }
                }
                else
                {
                    for(x = 0; x < tRestNums; x++)
                    {
                        tTxDataAligned.halfWordData[x] = pTxHalfWordBuffer[tBufferIdx];
                        tBufferIdx++;
                    }
                }

                /* Transmit data */
                obj->reg->TDR = tTxDataAligned.wordData;
            }
        }
    }
}

/*! \brief  Set the link route function in the slave node with word transfer
 *
 * this function is used for slave node to link transfer from master to other node with words
 *
 * \param[in] obj : base address for the SPI instance
 * \param[in] txWodsCnt: the data words to be sent
 * \param[in] pTxWordBuffer: pointer to the tx data word buffer
 *           the tx data will fill or not by special requirement
 * \return: void
 */
void SpiDrv_SlaveAsyncLinkTransferWords(SpiDrvType *obj, uint16_t txWodsCnt, const uint32_t *pTxWordBuffer)
{
    uint8_t tTxFreeNums = 0;

    tTxFreeNums = SPIDRV_TX_FIFO_SIZE - SpiReg_GetTxFifoCounter(obj->reg);

    if(tTxFreeNums > txWodsCnt)
    {
        uint32_t tTcr = 0, i = 0;

        if(txWodsCnt > 0)
        {
            tTcr = SpiReg_GetTcr(obj->reg);
            SpiDrv_SetContinuousCmd(&tTcr, false);
            SpiDrv_SetContinuousTransfer(&tTcr, true);
            SpiDrv_SetTxDataMask(&tTcr, false);
            SpiDrv_SetRxDataMask(&tTcr, false);
            SpiDrv_SetFrameSize(&tTcr, 31u);
            SpiReg_SetTcr(obj->reg, tTcr);

            for(i = 0; i < txWodsCnt; i++)
            {
                /* Transmit data */
                obj->reg->TDR = pTxWordBuffer[i];
            }
        }
    }
}

/*! \brief Update Transmit Command Register configuration structure
 *
 * Any writes to the TCR will cause the entire TCR contents to be pushed to the TX FIFO.
 * Therefore any updates to the TCR should include updates to all of the register
 * bit fields to form a 32-bit write to the TCR.
 *
 * \param[in] obj : pointer to the instance
 * \param[in] pTcrInfo : Transmit Command Register configuration structure
 * \return void
 */
void SpiDrv_SetTcrCmdConfig(SpiDrvType *obj, const SpiDrv_TcrInfoType *pTcrInfo)
{
    uint32_t tTcr = 0;

    tTcr = SpiReg_GetTcr(obj->reg);

    /* TX RX MASK */
    SpiDrv_SetTxDataMask(&tTcr, pTcrInfo->txMask);
    SpiDrv_SetRxDataMask(&tTcr, pTcrInfo->rxMask);

    /* Byte-Swap, only in the frame size /32 != 0u case, can used the byte swap */
    SpiDrv_SetByteSwap(&tTcr, pTcrInfo->byteSwap);

    /* First Bit shift */
    SpiDrv_SetLowBitFirstTransfer(&tTcr, pTcrInfo->dataShiftFirstBit);

    /* CPHA */
    SpiDrv_SetClockPhase(&tTcr, pTcrInfo->clockPhase);

    /* CPOL */
    SpiDrv_SetClockPolarity(&tTcr, pTcrInfo->clockPolarity);

    /* Select PCS */
    SpiDrv_SetPcsSelection(&tTcr, pTcrInfo->pcsSelection);

    /* Continuous transfer */
    SpiDrv_SetContinuousTransfer(&tTcr, pTcrInfo->continuousTransfer);

    /* Continuous command */
    SpiDrv_SetContinuousCmd(&tTcr, pTcrInfo->continuousCmd);

    /* Frame Size */
    SpiDrv_SetFrameSize(&tTcr, pTcrInfo->frameBitSize);

    /* Transfer width */
    SpiDrv_SetTransferWidth(&tTcr, pTcrInfo->transferWidth);

    /* Update the tcr register */
    SpiReg_SetTcr(obj->reg, tTcr);
}

/*! \brief Get Transmit Command Register configuration structure
 *
 * This function get the current tcr register value
 *
 * \param[in] obj : pointer to the instance
 * \return: Transmit Command Register configuration structure
 */
SpiDrv_TcrInfoType SpiDrv_GetTcrCmdConfig(const SpiDrvType *obj)
{
    SpiDrv_TcrInfoType tTcrInfo;
    uint32_t           tTcr = 0;

    tTcr = SpiReg_GetTcr(obj->reg);

    if((tTcr & SPI_TCR_CPHA_MASK) != 0u)
    {
        tTcrInfo.clockPhase = SPIDRV_CLK_PHASE_DATA_SAMPLE_ON_TRAILING_EDGE;
    }
    else
    {
        tTcrInfo.clockPhase = SPIDRV_CLK_PHASE_DATA_SAMPLE_ON_LEADING_EDGE;
    }

    if((tTcr & SPI_TCR_CPOL_MASK) != 0u)
    {
        tTcrInfo.clockPolarity = SPIDRV_CLK_POLARITY_IDLE_IN_HIGH;
    }
    else
    {
        tTcrInfo.clockPolarity = SPIDRV_CLK_POLARITY_IDLE_IN_LOW;
    }

    if((((tTcr & SPI_TCR_PCS_SEL_MASK) >> SPI_TCR_PCS_SEL_SHIFT) & 0xFF) == 0u)
    {
        tTcrInfo.pcsSelection = SPIDRV_PCS_SEL_PCS0;
    }
    else if((((tTcr & SPI_TCR_PCS_SEL_MASK) >> SPI_TCR_PCS_SEL_SHIFT) & 0xFF) == 1u)
    {
        tTcrInfo.pcsSelection = SPIDRV_PCS_SEL_PCS1;
    }
    else if((((tTcr & SPI_TCR_PCS_SEL_MASK) >> SPI_TCR_PCS_SEL_SHIFT) & 0xFF) == 2u)
    {
        tTcrInfo.pcsSelection = SPIDRV_PCS_SEL_PCS2;
    }
    else if((((tTcr & SPI_TCR_PCS_SEL_MASK) >> SPI_TCR_PCS_SEL_SHIFT) & 0xFF) == 3u)
    {
        tTcrInfo.pcsSelection = SPIDRV_PCS_SEL_PCS3;
    }

    if((tTcr & SPI_TCR_LSB_FIRST_MASK) != 0u)
    {
        tTcrInfo.dataShiftFirstBit = SPIDRV_SHIFT_FIRST_BIT_LSB;
    }
    else
    {
        tTcrInfo.dataShiftFirstBit = SPIDRV_SHIFT_FIRST_BIT_MSB;
    }

    tTcrInfo.frameBitSize  = (((tTcr & SPI_TCR_FRAME_SIZE_MASK) >> SPI_TCR_FRAME_SIZE_SHIFT) & 0xFFF);
    tTcrInfo.transferWidth = (((tTcr & SPI_TCR_TRANSFER_WIDTH_MASK) >> SPI_TCR_TRANSFER_WIDTH_SHIFT) & 0x03u);
    tTcrInfo.prescaler     = (((tTcr & SPI_TCR_PRESCALER_MASK) >> SPI_TCR_PRESCALER_SHIFT) & 0xFF);

    if((tTcr & SPI_TCR_RX_MASK_MASK) != 0u)
    {
        tTcrInfo.rxMask = true;
    }
    else
    {
        tTcrInfo.rxMask = false;
    }

    if((tTcr & SPI_TCR_TX_MASK_MASK) != 0u)
    {
        tTcrInfo.txMask = true;
    }
    else
    {
        tTcrInfo.txMask = false;
    }

    if((tTcr & SPI_TCR_BYTE_SWAP_MASK) != 0u)
    {
        tTcrInfo.byteSwap = true;
    }
    else
    {
        tTcrInfo.byteSwap = false;
    }

    tTcrInfo.continuousTransfer = (((tTcr & SPI_TCR_CONTINUE_TRANSFER_MASK) >> SPI_TCR_CONTINUE_TRANSFER_SHIFT) & 0x01);
    tTcrInfo.continuousCmd      = (((tTcr & SPI_TCR_CONTINUE_CMD_MASK) >> SPI_TCR_CONTINUE_CMD_SHIFT) & 0x01);

    return tTcrInfo;
}

/*! \brief Set Slave rx fifo water mark
 *
 * the max water mark is must less than the supported depth
 *
 * \param[in] obj : pointer to the instance
 * \param[in] txFrameNums: the tx frame to be sent
 * \param[in] frameSizeBitType: frame bit width(8bit/16bit/32bit)
 * \return: bool
 *         false: the current water is more than the actual max supported depth
 *         true: no error
 */
bool SpiDrv_SlaveSetRxWaterMark(SpiDrvType *obj, uint16_t txFrameNums, SpiDrv_FrameSizeBitType frameSizeBitType)
{
    bool     tRtn           = false;
    uint8_t  tMultFrameNums = 0, tRestNums = 0;
    uint16_t tTxBytesNum = 0;

    if(frameSizeBitType == SPIDRV_FRAME_SIZE_BIT_TYPE_BYTE)
    {
        tTxBytesNum = txFrameNums;
    }
    else if(frameSizeBitType == SPIDRV_FRAME_SIZE_BIT_TYPE_HALF_WORD)
    {
        tTxBytesNum = txFrameNums * 2;
    }
    else
    {
        tTxBytesNum = txFrameNums * 4;
    }

    tMultFrameNums = (uint8_t)(tTxBytesNum / 4u);
    tRestNums      = (tTxBytesNum & 0x03);

    if(tMultFrameNums < (SpiReg_GetRxFifoDepth(obj->reg) - SpiReg_GetRxFifoCounter(obj->reg)))
    {
        if(tRestNums > 0)
        {
            SpiReg_SetRxFifoWaterMark(obj->reg, tMultFrameNums);
        }
        else
        {
            if(tMultFrameNums > 0)
            {
                SpiReg_SetRxFifoWaterMark(obj->reg, (uint8_t)(tMultFrameNums - 1u));
            }
            else
            {
                SpiReg_SetRxFifoWaterMark(obj->reg, 0u);
            }
        }

        tRtn = true;
    }

    return tRtn;
}

/*! \brief Async bit data write to hardware tx data buffer
 *
 * this function just only fill datas to tx fifo, but not read out datas from rx fifo
 *
 * \param[in] obj : pointer to the instance
 * \param[in] txBitNums: the tx data bits numbers to be write
 * \param[in] pTxBuffer: write data buffer, notice: aligned with 32bits
 * \param[in] littleEndDian: write bit flow turn
 * \return: bool
 *         false: error
 *         true: no error
 */
bool SpiDrv_AsyncBitDataWriteIntoHwTxBuffer(SpiDrvType *obj, uint16_t txBitNums, const void *pTxBuffer, bool littleEndDian)
{
    bool                   tRtn         = true;
    uint16_t               tRestBitNums = 0, i = 0;
    uint8_t                tBufferIdx = 0;
    uint32_t               timeOutCnt = 0;
    SpiDrv_DataAlignedType tDataAligned;

    tRestBitNums = txBitNums;
    do
    {
        if(SpiReg_GetTxFifoCounter(obj->reg) <= (SPIDRV_TX_FIFO_SIZE - 1u))
        {
            tDataAligned.wordData = 0;

            if(tRestBitNums >= (SPIDRV_FRAME_SIZE_WORD + 1u))
            {
                if(littleEndDian == false)
                {
                    for(i = 0u; i < 4; i++)
                    {
                        tDataAligned.byteData[i] = ((uint8_t *)pTxBuffer)[tBufferIdx + 3 - i];
                    }
                }
                else
                {
                    for(i = 0; i < 4u; i++)
                    {
                        tDataAligned.byteData[i] = ((uint8_t *)pTxBuffer)[tBufferIdx + i];
                    }
                }

                obj->reg->TDR = tDataAligned.wordData;
                tRestBitNums -= 32u;
                tBufferIdx += 4u;
                while(SpiDrv_GetStatus(obj, SPIDRV_STATUS_TX_DATA) == false);
            }
            else if(tRestBitNums >= (SPIDRV_FRAME_SIZE_HALF_WORD + 1u))
            {
                if(tRestBitNums > 24u)
                {
                    if(littleEndDian == false)
                    {
                        for(i = 0u; i < 4; i++)
                        {
                            tDataAligned.byteData[i] = ((uint8_t *)pTxBuffer)[tBufferIdx + 3 - i];
                        }
                    }
                    else
                    {
                        for(i = 0; i < 4u; i++)
                        {
                            tDataAligned.byteData[i] = ((uint8_t *)pTxBuffer)[tBufferIdx + i];
                        }
                    }

                    tBufferIdx += 4u;
                }
                else if(tRestBitNums > 16u)
                {
                    if(littleEndDian == false)
                    {
                        for(i = 0u; i < 3; i++)
                        {
                            tDataAligned.byteData[i] = ((uint8_t *)pTxBuffer)[tBufferIdx + 2 - i];
                        }
                    }
                    else
                    {
                        for(i = 0; i < 3u; i++)
                        {
                            tDataAligned.byteData[i] = ((uint8_t *)pTxBuffer)[tBufferIdx + i];
                        }
                    }

                    tBufferIdx += 3u;
                }
                else
                {
                    if(littleEndDian == false)
                    {
                        for(i = 0u; i < 2; i++)
                        {
                            tDataAligned.byteData[i] = ((uint8_t *)pTxBuffer)[tBufferIdx + 1 - i];
                        }
                    }
                    else
                    {
                        for(i = 0; i < 2u; i++)
                        {
                            tDataAligned.byteData[i] = ((uint8_t *)pTxBuffer)[tBufferIdx + i];
                        }
                    }

                    tBufferIdx += 2u;
                }

                tRestBitNums  = 0u;
                obj->reg->TDR = tDataAligned.wordData;
                while(SpiDrv_GetStatus(obj, SPIDRV_STATUS_TX_DATA) == false);
            }
            else if(tRestBitNums >= (SPIDRV_FRAME_SIZE_BYTE + 1u))
            {
                if(tRestBitNums > 8u)
                {
                    if(littleEndDian == false)
                    {
                        for(i = 0u; i < 2u; i++)
                        {
                            tDataAligned.byteData[i] = ((uint8_t *)pTxBuffer)[tBufferIdx + 1 - i];
                        }
                    }
                    else
                    {
                        for(i = 0; i < 2u; i++)
                        {
                            tDataAligned.byteData[i] = ((uint8_t *)pTxBuffer)[tBufferIdx + i];
                        }
                    }

                    tBufferIdx += 2u;
                }
                else
                {
                    tDataAligned.byteData[0] = (((uint8_t *)pTxBuffer)[tBufferIdx]);
                }

                obj->reg->TDR = tDataAligned.wordData;
                tRestBitNums  = 0u;
                tBufferIdx += 1u;
                while(SpiDrv_GetStatus(obj, SPIDRV_STATUS_TX_DATA) == false);
            }
            else
            {
                obj->reg->TDR = (((uint8_t *)pTxBuffer)[tBufferIdx]);
                tRestBitNums  = 0;
                tBufferIdx++;
                while(SpiDrv_GetStatus(obj, SPIDRV_STATUS_TX_DATA) == false);
            }

            timeOutCnt = 0;
        }
        else
        {
            timeOutCnt++;
        }

    } while((tRestBitNums > 0u) && (timeOutCnt < SPIDRV_TX_TIMEOUT_CNT));

    if(timeOutCnt >= SPIDRV_TX_TIMEOUT_CNT)
    {
        tRtn = false;
    }

    return tRtn;
}

/*! \brief Async tx data with any length of bits
 *
 * this function just only fill datas to tx fifo, but not read out datas from rx fifo, the bits num should be multile by 2!
 *
 * \param[in] obj : pointer to the instance
 * \param[in] txBitNums: the nums bits of data to be sent
 * \param[in] pBuffer: th pointer of which data to be sent;if in half duplex mode, and the txmask is true, no care about this parameter,
 * notice: aligned with 32bits
 * \param[in] txMask: tx mask bit
 * \param[in] rxMask: rx mask bit
 * \param[in] littleEndDian: transfer data flow
 * \return: bool
 *         true: no error
 *         false: error
 */
bool SpiDrv_AsyncBitsTransfer(SpiDrvType *obj, uint16_t txBitNums, const void *pBuffer, bool txMask, bool rxMask, bool littleEndDian)
{
    bool               tRtn = true;
    SpiDrv_TcrInfoType tcrInfo;

    tcrInfo              = SpiDrv_GetTcrCmdConfig(obj);
    tcrInfo.frameBitSize = txBitNums - 1u;
    tcrInfo.txMask       = txMask;
    tcrInfo.rxMask       = rxMask;

    SpiDrv_SetTcrCmdConfig(obj, &tcrInfo);

    if(tcrInfo.txMask == false)
    {
        tRtn = SpiDrv_AsyncBitDataWriteIntoHwTxBuffer(obj, txBitNums, pBuffer, littleEndDian);
    }

    return tRtn;
}

/*! \brief Async bits Received
 *
 * this function read the datas from rx fifo, and return the bytes nums have been readout.
 * Notice: Returns the number of words currently stored in the receive FIFO, may be just one byte in rx fifo, but still return four bytes
 * so the total read out bytes number must be more than the actual useful numbers
 *
 * \param[in] obj : pointer to the instance
 * \param[in] pBuffer: th pointer of which data to be stored, Notice: the address must be aligned with word!!!!
 * \param[in] littleEndDian: transfer data flow
 * \return: the bytes in the rx fifo
 */
uint8_t SpiDrv_AsyncReceive(SpiDrvType *obj, void *pBuffer, bool littleEndDian)
{
    uint8_t retBytesNum = 0;

    if(SpiReg_GetRxFifoEmptyState(obj->reg) == false)
    {
        uint8_t                tRxFifoCnt = 0, tWriteByteIdx = 0;
        uint16_t               i = 0, y = 0;
        SpiDrv_DataAlignedType tDataAligned;
        uint32_t               frameBitSize = 0;

        /* Read out the number of words currently stored in the receive FIFO. */
        tRxFifoCnt   = SpiReg_GetRxFifoCounter(obj->reg);
        frameBitSize = SpiReg_GetFrameSize(obj->reg);

        /* the rx fifo counter is aligned with word , so may by just read out less than 4bytes, also return 4bytes! */
        if(frameBitSize > SPIDRV_FRAME_SIZE_HALF_WORD)
        {
            retBytesNum = tRxFifoCnt << 2;

            for(i = 0; i < tRxFifoCnt; i++)
            {
                tDataAligned.wordData = obj->reg->RDR;

                if(littleEndDian == true)
                {
                    for(y = 0; y < 4u; y++)
                    {
                        ((uint8_t *)pBuffer)[tWriteByteIdx++] = tDataAligned.byteData[y];
                    }
                }
                else
                {
                    for(y = 0; y < 4u; y++)
                    {
                        ((uint8_t *)pBuffer)[tWriteByteIdx++] = tDataAligned.byteData[3 - y];
                    }
                }
            }
        }
        else if(frameBitSize > SPIDRV_FRAME_SIZE_BYTE)
        {
            retBytesNum = tRxFifoCnt << 1;

            for(i = 0; i < tRxFifoCnt; i++)
            {
                tDataAligned.wordData = obj->reg->RDR;

                if(littleEndDian == true)
                {
                    for(y = 0; y < 2u; y++)
                    {
                        ((uint8_t *)pBuffer)[tWriteByteIdx++] = tDataAligned.byteData[y];
                    }
                }
                else
                {
                    for(y = 0; y < 2u; y++)
                    {
                        ((uint8_t *)pBuffer)[tWriteByteIdx++] = tDataAligned.byteData[1 - y];
                    }
                }
            }
        }
        else
        {
            retBytesNum = tRxFifoCnt;

            for(i = 0; i < tRxFifoCnt; i++)
            {
                ((uint8_t *)pBuffer)[tWriteByteIdx++] = obj->reg->RDR;
            }
        }
    }

    return retBytesNum;
}

/*! \brief Set SPI interrupt config
 *
 * \param[in] obj : pointer to the instance
 * \param[in] isrSrc: interrupt source
 * \param[in] enabled: config status
 * \return: void
 */
void SpiDrv_SetIsrConfig(SpiDrvType *obj, SpiDrv_IsrSrcType isrSrc, bool enabled)
{
    switch(isrSrc)
    {
    case SPIDRV_ISR_SRC_TX_DATA:
        SpiReg_SetTxDataIsr(obj->reg, enabled);
        break;

    case SPIDRV_ISR_SRC_RX_DATA:
        SpiReg_SetRxDataIsr(obj->reg, enabled);
        break;

    case SPIDRV_ISR_SRC_RX_WORD_DONE:
        SpiReg_SetRxWordDoneIsr(obj->reg, enabled);
        break;

    case SPIDRV_ISR_SRC_FRAME_DONE:
        SpiReg_SetFrameDoneIsr(obj->reg, enabled);
        break;

    case SPIDRV_ISR_SRC_MASTER_XFR_DONE:
        SpiReg_SetTxTransferDoneIsr(obj->reg, enabled);
        break;

    case SPIDRV_ISR_SRC_TX_UF:
        SpiReg_SetTxUnderflowIsr(obj->reg, enabled);
        break;

    case SPIDRV_ISR_SRC_RX_OF:
        SpiReg_SetRxOverflowIsr(obj->reg, enabled);
        break;

    default:
        break;
    }
}

/*! \brief Get SPI interrupt config
 *
 * \param[in] obj : pointer to the instance
 * \param[in] isrSrc: interrupt source
 * \return: config status
 */
bool SpiDrv_GetIsrConfig(SpiDrvType *obj, SpiDrv_IsrSrcType isrSrc)
{
    bool isrCfg = false;

    switch(isrSrc)
    {
    case SPIDRV_ISR_SRC_TX_DATA:
        isrCfg = SpiReg_GetIntReqEnableState(obj->reg, SPI_IER_TX_DATA_IE_MASK);
        break;

    case SPIDRV_ISR_SRC_RX_DATA:
        isrCfg = SpiReg_GetIntReqEnableState(obj->reg, SPI_IER_RX_DATA_IE_MASK);
        break;

    case SPIDRV_ISR_SRC_RX_WORD_DONE:
        isrCfg = SpiReg_GetIntReqEnableState(obj->reg, SPI_IER_RX_WORD_DONE_IE_MASK);
        break;

    case SPIDRV_ISR_SRC_FRAME_DONE:
        isrCfg = SpiReg_GetIntReqEnableState(obj->reg, SPI_IER_FRAME_DONE_IE_MASK);
        break;

    case SPIDRV_ISR_SRC_MASTER_XFR_DONE:
        isrCfg = SpiReg_GetIntReqEnableState(obj->reg, SPI_IER_MST_TRANSFER_DONE_IE_MASK);
        break;

    case SPIDRV_ISR_SRC_TX_UF:
        isrCfg = SpiReg_GetIntReqEnableState(obj->reg, SPI_IER_TX_UF_IE_MASK);
        break;

    case SPIDRV_ISR_SRC_RX_OF:
        isrCfg = SpiReg_GetIntReqEnableState(obj->reg, SPI_IER_RX_OF_IE_MASK);
        break;

    default:
        break;
    }

    return isrCfg;
}

/*! \brief Set rx fifo water mask
 *
 * \param[in] obj : pointer to the instance
 * \param[in] waterMask: fifo water mask
 * \return: void
 */
void SpiDrv_SetRxFifoWaterMask(SpiDrvType *obj, uint8_t waterMask)
{
    SpiReg_SetRxFifoWaterMark(obj->reg, waterMask);
}

/*! \brief Set tx fifo water mask
 *
 * \param[in] obj : pointer to the instance
 * \param[in] waterMask: fifo water mask
 * \return: void
 */
void SpiDrv_SetTxFifoWaterMask(SpiDrvType *obj, uint8_t waterMask)
{
    SpiReg_SetTxFifoWaterMark(obj->reg, waterMask);
}

/*! \brief Set Clock Polarity
 *
 * The Clock Polarity field is only updated when PCS negated.
 *
 * \param[in] pTcr : TCR variable instance
 * \param[in] clockPolarity :
 *           0b : The inactive state value of SCK is low
 *           1b : The inactive state value of SCK is high
 * \return: void
 */
void SpiDrv_SetClockPolarity(uint32_t *pTcr, uint8_t clockPolarity)
{
    uint32_t tmp = *pTcr;

    tmp &= ~SPI_TCR_CPOL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(clockPolarity)) << SPI_TCR_CPOL_SHIFT)) & SPI_TCR_CPOL_MASK);
    *pTcr = tmp;
}

/*! \brief Set Clock Phase
 *
 * The Clock Phase field is only updated when PCS negated.
 *
 * \param[in] pTcr : TCR variable instance
 * \param[in] clockPhase :
 *           0b : Data is captured on the leading edge of SCK and changed on the following edge of SCK
 *           1b : Data is changed on the leading edge of SCK and captured on the following edge of SCK
 * \return: void
 */
void SpiDrv_SetClockPhase(uint32_t *pTcr, uint8_t clockPhase)
{
    uint32_t tmp = *pTcr;

    tmp &= ~SPI_TCR_CPHA_MASK;
    tmp |= (((uint32_t)(((uint32_t)(clockPhase)) << SPI_TCR_CPHA_SHIFT)) & SPI_TCR_CPHA_MASK);
    *pTcr = tmp;
}

/*! \brief Set Prescaler Value
 *
 * For all SPI bus transfers, the Prescaler value applied to the clock configuration register. The Prescaler Value field is only updated when PCS negated.
 *
 * \param[in] pTcr : TCR variable instance
 * \param[in] prescaler :
 *           000b : Divide by 1
 *           001b : Divide by 2
 *           010b : Divide by 4
 *           011b : Divide by 8
 *           100b : Divide by 16
 *           101b : Divide by 32
 *           110b : Divide by 64
 *           111b : Divide by 128
 * \return: void
 */
void SpiDrv_SetPrescaler(uint32_t *pTcr, uint8_t prescaler)
{
    uint32_t tmp = *pTcr;

    tmp &= ~SPI_TCR_PRESCALER_MASK;
    tmp |= (((uint32_t)(((uint32_t)(prescaler)) << SPI_TCR_PRESCALER_SHIFT)) & SPI_TCR_PRESCALER_MASK);
    *pTcr = tmp;
}

/*! \brief Select Peripheral Chip
 *
 * Configures the peripheral chip select used for the transfer. The Peripheral Chip Select field is only updated when PCS negated.
 *
 * \param[in] pTcr : TCR variable instance
 * \param[in] pcsSelection :
 *           00b : Transfer using SPI_PCS[0]
 *           01b : Transfer using SPI_PCS[1]
 *           10b : Transfer using SPI_PCS[2]
 *           11b : Transfer using SPI_PCS[3]
 * \return: void
 */
void SpiDrv_SetPcsSelection(uint32_t *pTcr, uint8_t pcsSelection)
{
    uint32_t tmp = *pTcr;

    tmp &= ~SPI_TCR_PCS_SEL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(pcsSelection)) << SPI_TCR_PCS_SEL_SHIFT)) & SPI_TCR_PCS_SEL_MASK);
    *pTcr = tmp;
}

/*! \brief Set data transfer direction
 *
 *
 *
 * \param[in] pTcr : TCR variable instance
 * \param[in] lsbFirst :
 *           0b:Data is transferred MSB first
 *           1b:Data is transferred LSB first
 * \return: void
 */
void SpiDrv_SetLowBitFirstTransfer(uint32_t *pTcr, uint8_t lsbFirst)
{
    uint32_t tmp = *pTcr;

    tmp &= ~SPI_TCR_LSB_FIRST_MASK;
    tmp |= (((uint32_t)(((uint32_t)(lsbFirst)) << SPI_TCR_LSB_FIRST_SHIFT)) & SPI_TCR_LSB_FIRST_MASK);
    *pTcr = tmp;
}

/*! \brief Set Byte Swap
 *
 * Byte swap will swap the contents of [31:24] with [7:0] and [23:16] with [15:8] for each transmit data word read from
 *      the FIFO and for each received data word stored to the FIFO
 *
 * \param[in] pTcr : TCR variable instance
 * \param[in] enable :
 *           0b:Byte swap is disabled
 *           1b:Byte swap is enabled
 * \return: void
 */
void SpiDrv_SetByteSwap(uint32_t *pTcr, bool enable)
{
    uint32_t tRegValue = *pTcr;

    if(enable == true)
    {
        *pTcr = ((1ul << SPI_TCR_BYTE_SWAP_SHIFT) | ((~SPI_TCR_BYTE_SWAP_MASK) & tRegValue));
    }
    else
    {
        *pTcr = ((0ul << SPI_TCR_BYTE_SWAP_SHIFT) | ((~SPI_TCR_BYTE_SWAP_MASK) & tRegValue));
    }
}

/*! \brief Set Continuous Transfer
 *
 * In master mode, continuous transfer will keep the PCS asserted at the end of the frame size,
 *      until a command word is received that starts a new frame.
 *      In slave mode, when continuous transfer is enabled, the SPI will only transmit the first FRAMESZ bits;
 *      after which the SPI will transmit received data (assuming a 32-bit shift register) until the next PCS negation.
 *
 * \param[in] pTcr : TCR variable instance
 * \param[in] enable :
 *           0b:Continuous transfer is disabled
 *           1b:Continuous transfer is enabled
 * \return: void
 */
void SpiDrv_SetContinuousTransfer(uint32_t *pTcr, bool enable)
{
    uint32_t tRegValue = *pTcr;

    if(enable == true)
    {
        *pTcr = ((1ul << SPI_TCR_CONTINUE_TRANSFER_SHIFT) | ((~SPI_TCR_CONTINUE_TRANSFER_MASK) & tRegValue));
    }
    else
    {
        *pTcr = ((0ul << SPI_TCR_CONTINUE_TRANSFER_SHIFT) | ((~SPI_TCR_CONTINUE_TRANSFER_MASK) & tRegValue));
    }
}

/*! \brief Set Continuing Command
 *
 * In master mode, the Continuing Command bit allows the command word to be changed within a transfer.
 *      1. in continuous transfer
 *      - the initial command word must enable continuous transfer (CONT=1),
 *      - the continuing command must set this bit (CONTC=1),
 *      - the continuing command word must be loaded on a frame size boundary.
 *      2. in non-continuous transfer
 *      - the continuing command must set this bit (CONTC=1),
 *      - the continuing command word must be loaded on a frame size boundary.
 *
 * \param[in] pTcr : TCR variable instance
 * \param[in] cmd :
 *           0b:Command word for start of new transfer
 *           1b:Command word for continuing transfer
 * \return: void
 */
void SpiDrv_SetContinuousCmd(uint32_t *pTcr, uint8_t cmd)
{
    uint32_t tmp = *pTcr;

    tmp &= ~SPI_TCR_CONTINUE_CMD_MASK;
    tmp |= (((uint32_t)(((uint32_t)(cmd)) << SPI_TCR_CONTINUE_CMD_SHIFT)) & SPI_TCR_CONTINUE_CMD_MASK);
    *pTcr = tmp;
}

/*! \brief Set Receive Data Mask
 *
 * When set, receive data is masked (receive data is not stored in receive FIFO).
 *
 * \param[in] pTcr : TCR variable instance
 * \param[in] enableMask :
 *           0b:Normal transfer
 *           1b:Receive data is masked
 * \return: void
 */
void SpiDrv_SetRxDataMask(uint32_t *pTcr, bool enableMask)
{
    uint32_t tRegValue = *pTcr;

    if(enableMask == true)
    {
        *pTcr = ((1ul << SPI_TCR_RX_MASK_SHIFT) | ((~SPI_TCR_RX_MASK_MASK) & tRegValue));
    }
    else
    {
        *pTcr = ((0ul << SPI_TCR_RX_MASK_SHIFT) | ((~SPI_TCR_RX_MASK_MASK) & tRegValue));
    }
}

/*! \brief Set Transmit Data Mask
 *
 * When set, transmit data is masked (no data is loaded from transmit FIFO and output pin is tristated).
 *      In master mode, the Transmit Data Mask bit will initiate a new transfer
 *      which cannot be aborted by another command word; TXMSK bit will be cleared by hardware at the end of the transfer.
 *
 * \param[in] pTcr : TCR variable instance
 * \param[in] enableMask :
 *           0b:Normal transfer
 *           1b:Mask transmit data
 * \return: void
 */
void SpiDrv_SetTxDataMask(uint32_t *pTcr, bool enableMask)
{
    uint32_t tRegValue = *pTcr;

    if(enableMask == true)
    {
        *pTcr = ((1ul << SPI_TCR_TX_MASK_SHIFT) | ((~SPI_TCR_TX_MASK_MASK) & tRegValue));
    }
    else
    {
        *pTcr = ((0ul << SPI_TCR_TX_MASK_SHIFT) | ((~SPI_TCR_TX_MASK_MASK) & tRegValue));
    }
}

/*! \brief Set Transfer data Width
 *
 * Configures between serial (1-bit) or parallel transfers. For half-duplex parallel transfers, either Receive Data Mask (RXMSK) or Transmit Data Mask (TXMSK) must be set.
 *
 * \param[in] pTcr : TCR variable instance
 * \param[in] transferWidth :
 *           00b:1 bit transfer
 *           01b:2 bit transfer
 *           10b:Reserved
 *           11b:Reserved
 * \return: void
 */
void SpiDrv_SetTransferWidth(uint32_t *pTcr, uint8_t transferWidth)
{
    uint32_t tmp = *pTcr;

    tmp &= ~SPI_TCR_TRANSFER_WIDTH_MASK;
    tmp |= (((uint32_t)(((uint32_t)(transferWidth)) << SPI_TCR_TRANSFER_WIDTH_SHIFT)) & SPI_TCR_TRANSFER_WIDTH_MASK);
    *pTcr = tmp;
}

/*! \brief Set Frame Size
 *
 * The minimum frame size is 8 bits, The minimum word size is 2 bits; a frame size of 33 bits (or similar) is not supported.
 *      If the frame size is larger than 32 bits, then the frame is divided into multiple words of 32-bits;
 *      each word is loaded from the transmit FIFO and stored in the receive FIFO separately.
 *      If the size of the frame is not divisible by 32, then the last load of the transmit FIFO and store of the receive FIFO will contain the remainder bits.
 *      For example, a 72-bit transfer will consist of 3 words: the 1st and 2nd words are 32 bits, and the 3rd word is 8 bits.
 *
 * \param[in] pTcr : TCR variable instance
 * \param[in] frameSize :Configures the frame size in number of bits equal to (FRAMESZ + 1)
 * \return: void
 */
void SpiDrv_SetFrameSize(uint32_t *pTcr, uint16_t frameSize)
{
    uint32_t tmp = *pTcr;

    tmp &= ~SPI_TCR_FRAME_SIZE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(frameSize)) << SPI_TCR_FRAME_SIZE_SHIFT)) & SPI_TCR_FRAME_SIZE_MASK);
    *pTcr = tmp;
}

/*! \brief Transmit Command config
 *
 * this function config the clock polarity, clock phase prescaler value and transfer mode ....
 *
 * \param[in] obj: pointer to the instance
 * \param[in] tcr: Transmit Command
 * \return: void
 */
void SpiDrv_SetTcr(SpiDrvType *obj, uint32_t tcr)
{
    SpiReg_SetTcr(obj->reg, tcr);
}

/*! \brief Get Transmit Command config
 *
 * this function config get the clock polarity, clock phase prescaler value and transfer mode ....
 *
 * \param[in] obj: pointer to the instance
 * \return: Transmit Command
 */
uint32_t SpiDrv_GetTcr(const SpiDrvType *obj)
{
    return SpiReg_GetTcr(obj->reg);
}
