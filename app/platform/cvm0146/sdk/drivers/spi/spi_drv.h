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

#ifndef _SPI_DRV_H_
#define _SPI_DRV_H_

/*! \brief Contains public interface to various functions related
 *         to the driver of SPI module
 */

/******************************************************************************
 * the includes
 *****************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "spi_reg.h"

/*! \addtogroup spi_drv
 *  @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 * the defines
 *****************************************************************************/

#define SPIDRV_ONE_FRAME_BITS_MAX_NUM (32u)
#define SPIDRV_TX_FIFO_SIZE           (16u)
#define SPIDRV_RX_FIFO_IN_WORD_SIZE   (16u)
#define SPIDRV_TX_TIMEOUT_CNT         (1000u)

/******************************************************************************
 * the typedefs
 *****************************************************************************/

/*! \brief SPI Peripheral Chip Select (PCS) configuration (which PCS to configure).*/
typedef enum
{
    SPIDRV_PCS_SEL_PCS0 = 0u,
    SPIDRV_PCS_SEL_PCS1,
    SPIDRV_PCS_SEL_PCS2,
    SPIDRV_PCS_SEL_PCS3,

    SPIDRV_PCS_SEL_NUM
} SpiDrv_PcsSelType;

/*! \brief SPI Signal (PCS and Host Request) Polarity configuration.*/
typedef enum
{
    SPIDRV_PCS_POLARITY_ACTIVE_LOW = 0u,
    SPIDRV_PCS_POLARITY_ACTIVE_HIGH,

    SPIDRV_PCS_POLARITY_NUM
} SpiDrv_PcsPolarityType;

/*! \brief SPI clock phase configuration.*/
typedef enum
{
    SPIDRV_CLK_PHASE_DATA_SAMPLE_ON_LEADING_EDGE = 0u,
    SPIDRV_CLK_PHASE_DATA_SAMPLE_ON_TRAILING_EDGE,

    SPIDRV_CLK_PHASE_NUM
} SpiDrv_ClockPhaseType;

/*! \brief SPI Clock Signal (SCK) Polarity configuration. */
typedef enum
{
    SPIDRV_CLK_POLARITY_IDLE_IN_LOW = 0u,
    SPIDRV_CLK_POLARITY_IDLE_IN_HIGH,

    SPIDRV_CLK_POLARITY_NUM
} SpiDrv_ClockPolarityType;

/*! \brief SPI Duplex mode selection */
typedef enum
{
    SPIDRV_DUPLEX_HALF_DUPLEX_IN_SINGLE_LINE = 0u,
    SPIDRV_DUPLEX_HALF_DUPLEX_IN_DOUBLE_LINE,
    SPIDRV_DUPLEX_FULL_DUPLEX,
    SPIDRV_DUPLEX_NUM
} SpiDrv_DuplexType;

/*! \brief SPI data shift direction  */
typedef enum
{
    SPIDRV_SHIFT_FIRST_BIT_MSB = 0u,
    SPIDRV_SHIFT_FIRST_BIT_LSB,

    SPIDRV_SHIFT_FIRST_BIT_NUM
} SpiDrv_ShiftFirstBitType;

/*! \brief SPI communication duplex pin configuration */
typedef enum
{
    SPIDRV_PIN_CFG_SIN_IN_SOUT_OUT = 0u,
    SPIDRV_PIN_CFG_HALF_DUPLEX_SIN,
    SPIDRV_PIN_CFG_HALF_DUPLEX_SOUT,
    SPIDRV_PIN_CFG_SIN_OUT_SOUT_IN,

    SPIDRV_PIN_CFG_NUM
} SpiDrv_PinCfgType;

/*! \brief SPI pin out level after transmit */
typedef enum
{
    SPIDRV_OUTCFG_IN_OLD_VALUE = 0u,
    SPIDRV_OUTCFG_IN_TRISTATE,

    SPIDRV_OUTCFG_NUM
} SpiDrv_OutCfgType;

/*! \brief SPI Frame size bit width */
typedef enum
{
    SPIDRV_FRAME_SIZE_BYTE      = 7u,
    SPIDRV_FRAME_SIZE_HALF_WORD = 15u,
    SPIDRV_FRAME_SIZE_WORD      = 31u
} SpiDrv_FrameSizeType;

/*! \brief SPI Frame size type */
typedef enum
{
    SPIDRV_FRAME_SIZE_BIT_TYPE_BYTE      = 1u,
    SPIDRV_FRAME_SIZE_BIT_TYPE_HALF_WORD = 2u,
    SPIDRV_FRAME_SIZE_BIT_TYPE_WORD      = 4u
} SpiDrv_FrameSizeBitType;

/*! \brief SPI Frame type selection */
typedef enum
{
    SPIDRV_FRAME_TRANSFER_SHORT_FRAME = 0u,
    SPIDRV_FRAME_TRANSFER_LONG_FRAME,
    SPIDRV_FRAME_TRANSFER_MULTI_FRAME
} SpiDrv_FrameTransferType;

/*! \brief Interrupt source */
typedef enum
{
    SPIDRV_ISR_SRC_TX_DATA         = 0x01ul,
    SPIDRV_ISR_SRC_RX_DATA         = 0x02ul,
    SPIDRV_ISR_SRC_RX_WORD_DONE    = 0x100ul,
    SPIDRV_ISR_SRC_FRAME_DONE      = 0x200ul,
    SPIDRV_ISR_SRC_MASTER_XFR_DONE = 0x400ul,
    SPIDRV_ISR_SRC_TX_UF           = 0x800ul,
    SPIDRV_ISR_SRC_RX_OF           = 0x1000ul,

    SPIDRV_ISR_SRC_ALL = 0xFFFFFFFF
} SpiDrv_IsrSrcType;

/*! \brief Status flag */
typedef enum
{
    SPIDRV_STATUS_TX_DATA      = 0x01ul,
    SPIDRV_STATUS_RX_DATA      = 0x02ul,
    SPIDRV_STATUS_RX_WORD_DONE = 0x100ul,
    SPIDRV_STATUS_FRAME_DONE   = 0x200ul,
    SPIDRV_STATUS_XFR_DONE     = 0x400ul,
    SPIDRV_STATUS_TX_UF        = 0x800ul,
    SPIDRV_STATUS_RX_OF        = 0x1000ul,
    SPIDRV_STATUS_BUSY         = 0x1000000ul,
    SPIDRV_STATUS_ALL          = 0x1FFFFFFul
} SpiDrv_StatusType;

/*! \brief golden section information diff table */
typedef struct _SpiDrv_CalculateTblType_
{
    uint32_t diff;
    uint16_t div;
    uint8_t  prescalerIdx;
} SpiDrv_CalculateTblType;

/*! \brief golden section information */
typedef struct
{
    uint32_t freqInput;
    uint32_t freqTargetOut;
    uint32_t bestOutPrescaler;
    uint32_t bestOutDiv;
    uint32_t bestOutFreq;
} SpiDrv_GoldenSectionInfoType;

/*! \brief data aligned union */
typedef union _SpiDrv_DataAlignedType_
{
    uint8_t  byteData[4];
    uint16_t halfWordData[2];
    uint32_t wordData;
} SpiDrv_DataAlignedType;

/*! \brief TCR information */
typedef struct _SpiDrv_TcrInfoType_
{
    SpiDrv_ClockPhaseType    clockPhase;
    SpiDrv_ClockPolarityType clockPolarity;
    SpiDrv_PcsSelType        pcsSelection;
    SpiDrv_ShiftFirstBitType dataShiftFirstBit;
    uint16_t                 frameBitSize;
    uint8_t                  transferWidth;
    uint8_t                  prescaler;
    bool                     txMask;
    bool                     rxMask;
    bool                     byteSwap;
    bool                     continuousTransfer;
    bool                     continuousCmd;
} SpiDrv_TcrInfoType;

/*! \brief SPI basic parameter information */
typedef struct _SpiDrv_BasicParametersType_
{
    uint32_t                 busClockFreq;
    uint32_t                 baudRate;
    bool                     isMasterNode;
    SpiDrv_ClockPhaseType    clockPhase;
    SpiDrv_ClockPolarityType clockPolarity;
    SpiDrv_PcsSelType        pcsSelection;
    SpiDrv_PcsPolarityType   pcsPolarity;
    SpiDrv_ShiftFirstBitType dataShiftFirstBit;
    uint16_t                 frameBitSize;
} SpiDrv_BasicParametersType;

/*! \brief SPI extend parameter inoformation */
typedef struct _SpiDrv_ExtendParametersType_
{
    SpiDrv_DuplexType duplexType;
    uint8_t           delayBetweenTransfer;
    uint8_t           delayFromPcsToSck;
    uint8_t           delayFromSckToPcs;
    uint8_t           masterSampleSckDelay;
    SpiDrv_PinCfgType pinCfg;
    SpiDrv_OutCfgType outCfg;
} SpiDrv_ExtendParametersType;

/*! \brief SPI extend feature information */
typedef struct _SpiDrv_ExtendFeaturesType_
{
    bool dmaTxEn;
    bool dmaRxEn;
    bool noStallEn;
    bool circularFifoEn;
    bool byteSwapEn;
    bool slaveAutoPcsEn;
    bool dbgEn;
    bool stopEn;
    bool rxMaskEn;
    bool txMaskEn;
} SpiDrv_ExtendFeaturesType;

/*! \brief SPI Isr access information */
typedef struct _SpiDrv_IsrAccessType_
{
    uint8_t txWatermark;
    uint8_t rxWatermark;
    bool    rxdataIsrEnable;
    bool    txdataIsrEnable;
    bool    rxWordDoneIsrEnable;
    bool    frameDoneIsrEnable;
    bool    masterTransferDoneIsrEnable;
    bool    rxOfIsrEnable;
    bool    txUfIsrEnable;
} SpiDrv_IsrAccessType;

/*! \brief SPI initialize configuration information */
typedef struct _SpiDrv_InitCfgType_
{
    SpiDrv_BasicParametersType  basicParameters;
    SpiDrv_ExtendParametersType extendParameters;
    SpiDrv_ExtendFeaturesType   extendFeatures;
} SpiDrv_InitCfgType;

/*! \brief SPI instance pointer */
typedef struct _SpiDrvType_
{
    SpiRegType *reg;
} SpiDrvType;

/******************************************************************************
 * the globals
 *****************************************************************************/

/******************************************************************************
 * the function prototypes
 *****************************************************************************/

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
extern void SpiDrv_SetClockPolarity(uint32_t *pTcr, uint8_t clockPolarity);

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
extern void SpiDrv_SetClockPhase(uint32_t *pTcr, uint8_t clockPhase);

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
extern void SpiDrv_SetPrescaler(uint32_t *pTcr, uint8_t prescaler);

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
extern void SpiDrv_SetPcsSelection(uint32_t *pTcr, uint8_t pcsSelection);

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
extern void SpiDrv_SetLowBitFirstTransfer(uint32_t *pTcr, uint8_t lsbFirst);

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
extern void SpiDrv_SetByteSwap(uint32_t *pTcr, bool enable);

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
extern void SpiDrv_SetContinuousTransfer(uint32_t *pTcr, bool enable);

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
extern void SpiDrv_SetContinuousCmd(uint32_t *pTcr, uint8_t cmd);

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
extern void SpiDrv_SetRxDataMask(uint32_t *pTcr, bool enableMask);

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
extern void SpiDrv_SetTxDataMask(uint32_t *pTcr, bool enableMask);

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
extern void SpiDrv_SetTransferWidth(uint32_t *pTcr, uint8_t transferWidth);

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
extern void SpiDrv_SetFrameSize(uint32_t *pTcr, uint16_t frameSize);

/*! \brief Transmit Command config
 *
 * this function config the clock polarity, clock phase prescaler value and transfer mode ....
 *
 * \param[in] obj: pointer to the instance
 * \param[in] tcr: Transmit Command
 * \return: void
 */
extern void SpiDrv_SetTcr(SpiDrvType *obj, uint32_t tcr);

/*! \brief Get Transmit Command config
 *
 * this function config get the clock polarity, clock phase prescaler value and transfer mode ....
 *
 * \param[in] obj: pointer to the instance
 * \return: Transmit Command
 */
extern uint32_t SpiDrv_GetTcr(const SpiDrvType *obj);

/*! \brief Get default configures the module for configuration structure
 *
 * This function gets default configures the module for user configuration structure
 *
 * \param[out] pInitCfg :pointer to configuration structure
 * \return: void
 */
extern void SpiDrv_GetDefaultConfig(SpiDrv_InitCfgType *pInitCfg);

/*! \brief Set the spi module parameters include basic&extend features
 *
 * this function initializes the run-time state structure to provide for module configuration
 *
 * \param[in] obj : pointer to the instance
 * \param[in] - const SpiDrv_InitCfgType * const pInitCfg: the pointer to the user configuration
 * \return: void
 */
extern void SpiDrv_SetConfig(SpiDrvType *obj, const SpiDrv_InitCfgType *pInitCfg);

/*! \brief Resets the SPI internal logic and registers to their default settings
 *
 * this function instance an object and reset module
 *
 * \param[in/out] : pointer to the instance
 * \param[in] pReg : the phycial module base address pointer
 * \return: void
 */
extern void SpiDrv_Init(SpiDrvType *obj, SpiRegType *pReg);

/*! \brief Set the module to special condition
 *
 * call back in the usage of Low power or sleep requirements
 *
 * \param[in] obj : pointer to the instance
 * \return: void
 */
extern void SpiDrv_DeInit(SpiDrvType *obj);

/*! \brief Get the status of the SpiDrv_StatusType of event
 *
 * this function read out the special status what want to be read
 *
 * \param[in] obj : pointer to the instance
 * \param[in] status : which status to be read out
 * \return: bool
 *          true: The status is exist
 *          false: The status is not exist
 */
extern bool SpiDrv_GetStatus(const SpiDrvType *obj, SpiDrv_StatusType status);

/*! \brief Clear the status
 *
 * this function clear the special status falg
 *
 * \param[in] obj : pointer to the instance
 * \param[in] status : combination of any SpiDrv_StatusType event
 * example: status = (SPIDRV_STATUS_RX_WORD_DONE | SPIDRV_STATUS_FRAME_DONE)
 * \return: void
 */
extern void SpiDrv_ClearStatus(SpiDrvType *obj, uint32_t status);

/*! \brief Set the link route function in the slave node with byte transfer
 *
 * this function is used for slave node to link transfer from master to other node with bytes
 *
 * \param[in] obj : pointer to the instance
 * \param[in] txBytesCnt: the data bytes to be sent
 * \param[in] pTxByteBuffer: pointer to the tx data byte buffer
 *            the tx data will fill or not by special requirement
 * \return: void
 */
extern void SpiDrv_SlaveAsyncLinkTransferBytes(SpiDrvType *obj, uint16_t txBytesCnt, const uint8_t *pTxByteBuffer);

/*! \brief Set the link route function in the slave node with halfword transfer
 *
 * this function is used for slave node to link transfer from master to other node with halfwords
 *
 * \param[in] obj : pointer to the instance
 * \param[in] txHalfWordsCnt: the data halfwords to be sent
 * \param[in] pTxHalfWordBuffer: pointer to the tx data halfword buffer
 *            the tx data will fill or not by special requirement
 * \return: void
 */
extern void SpiDrv_SlaveAsyncLinkTransferHalfWords(SpiDrvType *obj, uint16_t txHalfWordsCnt, const uint16_t *pTxHalfWordBuffer);

/*! \brief  Set the link route function in the slave node with word transfer
 *
 * this function is used for slave node to link transfer from master to other node with words
 *
 * \param[in] obj : pointer to the instance
 * \param[in] txWodsCnt: the data words to be sent
 * \param[in] pTxWordBuffer: pointer to the tx data word buffer
 *               the tx data will fill or not by special requirement
 * \return: void
 */
extern void SpiDrv_SlaveAsyncLinkTransferWords(SpiDrvType *obj, uint16_t txWodsCnt, const uint32_t *pTxWordBuffer);

/*! \brief Set Transmit Command Register configuration
 *
 * Any writes to the TCR will cause the entire TCR contents to be pushed to the TX FIFO.
 * Therefore any updates to the TCR should include updates to all of the register
 * bit fields to form a 32-bit write to the TCR.
 *
 * \param[in] obj : pointer to the instance
 * \param[in] pTcrInfo : Transmit Command Register configuration structure
 * \return void
 */
extern void SpiDrv_SetTcrCmdConfig(SpiDrvType *obj, const SpiDrv_TcrInfoType *pTcrInfo);

/*! \brief Get Transmit Command Register configuration structure
 *
 * This function get the current tcr register value
 *
 * \param[in] obj : pointer to the instance
 * \return: Transmit Command Register configuration structure
 */
extern SpiDrv_TcrInfoType SpiDrv_GetTcrCmdConfig(const SpiDrvType *obj);

/*! \brief Send one short frame each frame bits numbers is equal to or less than 32bits, every time hard set pcs signal again
 *         the DBT feature is valid
 *       _____   DATA (DBT)  _________   DATA(DBT)   __________
 *  PCS       |_____________|         |_____________|
 *
 * \param[in] obj : pointer to the instance
 * \param[in] txData:data to be sent
 * \param[in] frameSizeBitType:the frame bit width(8bit/16bit/32bit) to describe the pTxBuffer data width type
 * \return: bool
 *          true: no err
 *          false: no enough space for the current tx requirement
 */
extern bool SpiDrv_AsyncSingleFrameTransfer(SpiDrvType *obj, uint32_t txData, SpiDrv_FrameSizeBitType frameSizeBitType);

/*! \brief Send more than 32bits frame one time, the DBT feature is invalid
 *
 *       _____  DATA DATA DATA DATA __________
 *  PCS       |_____________________|
 *
 * \param[in] obj : pointer to the instance
 * \param[in] txFrameNums: the nums data to be sent
 * \param[in] pTxBuffer: th pointer of which data to be sent
 * \param[in] frameSizeBitType:the frame bit width(8bit/16bit/32bit) to describe the pTxBuffer data width type
 * \param[in] littleEndDian: transfer byte turn
 * \return: bool
 *          true: no err
 *          false: no enough space for the current tx requirement
 */
extern bool SpiDrv_AsyncLongFrameTransfer(SpiDrvType *obj, uint16_t txFrameNums, const void *pTxBuffer, SpiDrv_FrameSizeBitType frameSizeBitType, bool littleEndDian);

/*! \brief continue Send constinues frame,each frame bits numbers is equal to or less than 32bits
 *         the DBT feature is valid
 *       _____   DATA(xbits) (DBT) DATA(xBits)__________
 *  PCS       |_______________________________|
 *
 * \param[in] obj : pointer to the instance
 * \param[in] txFrameNums: the nums data to be sent
 * \param[in] pTxBuffer: th pointer of which data to be sent
 * \param[in] frameSizeBitType:the frame bit width(8bit/16bit/32bit) to describe the pTxBuffer data width type
 * \return: bool
 *          true: no err
 *          false: no enough space for the current tx requirement
 */
extern bool SpiDrv_AsyncContinueFrameTransfer(SpiDrvType *obj, uint16_t txFrameNums, const void *pTxBuffer, SpiDrv_FrameSizeBitType frameSizeBitType);

/*! \brief Async bit data write to hardware tx data buffer
 *
 * this function just only fill datas to tx fifo, but not read out datas from rx fifo
 *
 * \param[in] obj : pointer to the instance
 * \param[in] txBitNums: the tx data bits numbers to be write
 * \param[in] pTxBuffer: write data buffer , notice: aligned with 32bits
 * \param[in] littleEndDian: write bit flow turn
 * \return: bool
 *         false: error
 *         true: no error
 */
extern bool SpiDrv_AsyncBitDataWriteIntoHwTxBuffer(SpiDrvType *obj, uint16_t txBitNums, const void *pTxBuffer, bool littleEndDian);

/*! \brief Master Async tx data with any length of bits
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
extern bool SpiDrv_AsyncBitsTransfer(SpiDrvType *obj, uint16_t txBitNums, const void *pBuffer, bool txMask, bool rxMask, bool littleEndDian);

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
extern uint8_t SpiDrv_AsyncReceive(SpiDrvType *obj, void *pBuffer, bool littleEndDian);

/*! \brief Master Sync tx data, sent and received data from other node
 *
 *       _____  DATA DATA DATA DATA __________
 *  PCS       |_____________________|
 *
 * \param[in] obj : pointer to the instance
 * \param[in] frameSizeBitType: the data width to describe the pTxBuffer
 * \param[in] txFrameNums: the nums data to be sent
 * \param[in] pTxBuffer: the transmit data buffer pointer
 * \param[in] pRxBuffer: the pointer for the read-out datas
 * \return: bool
 *          false: the current tx fifo is full, no enough space for this transmit
 *          true: no error
 */
extern bool SpiDrv_MasterSyncTransfer(SpiDrvType *obj, SpiDrv_FrameSizeBitType frameSizeBitType, uint16_t txFrameNums, const void *pTxBuffer, void *pRxBuffer);

/*! \brief Set Slave rx fifo water mark
 *
 * the max water mark is must less than the supported depth
 *
 * \param[in] obj : pointer to the instance
 * \param[in] txFrameNums: the tx frame to be sent
 * \param[in] frameSizeBitType: frame bit width(8bit/16bit/32bit)
 * \return: bool
 *          false: the current water is more than the actual max supported depth
 *          true: no error
 */
extern bool SpiDrv_SlaveSetRxWaterMark(SpiDrvType *obj, uint16_t txFrameNums, SpiDrv_FrameSizeBitType frameSizeBitType);

/*! \brief Set rx fifo water mask
 *
 * \param[in] obj : pointer to the instance
 * \param[in] waterMask: fifo water mask
 * \return: void
 */
extern void SpiDrv_SetRxFifoWaterMask(SpiDrvType *obj, uint8_t waterMask);

/*! \brief Set tx fifo water mask
 *
 * \param[in] obj : pointer to the instance
 * \param[in] waterMask: fifo water mask
 * \return: void
 */
extern void SpiDrv_SetTxFifoWaterMask(SpiDrvType *obj, uint8_t waterMask);

/*! \brief Set SPI interrupt config
 *
 * \param[in] obj : pointer to the instance
 * \param[in] isrSrc: interrupt source
 * \param[in] enabled: config status
 * \return: void
 */
extern void SpiDrv_SetIsrConfig(SpiDrvType *obj, SpiDrv_IsrSrcType isrSrc, bool enabled);

/*! \brief Get SPI interrupt config
 *
 * \param[in] obj : pointer to the instance
 * \param[in] isrSrc: interrupt source
 * \return: config status
 */
extern bool SpiDrv_GetIsrConfig(SpiDrvType *obj, SpiDrv_IsrSrcType isrSrc);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _SPI_DRV_H_ */
