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

#ifndef _SPI_REG_H_
#define _SPI_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the driver of SPI module
 */

/******************************************************************************
 * the includes
 *****************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 * the defines
 *****************************************************************************/

/* PARAM Bit fields */
#define SPI_PARAM_TX_FIFO_DEPTH_MASK       (0x000000FFul)
#define SPI_PARAM_TX_FIFO_DEPTH_SHIFT      (0u)
#define SPI_PARAM_TX_FIFO_DEPTH_WIDTH      (8u)

#define SPI_PARAM_RX_FIFO_DEPTH_MASK       (0x0000FF00ul)
#define SPI_PARAM_RX_FIFO_DEPTH_SHIFT      (8u)
#define SPI_PARAM_RX_FIFO_DEPTH_WIDTH      (8u)

/* CR Bit fields */
#define SPI_CR_EN_MASK                     (0x00000001ul)
#define SPI_CR_EN_SHIFT                    (0u)
#define SPI_CR_EN_WIDTH                    (1u)

#define SPI_CR_RESET_MASK                  (0x00000002ul)
#define SPI_CR_RESET_SHIFT                 (1u)
#define SPI_CR_RESET_WIDTH                 (1u)

#define SPI_CR_DOZE_EN_MASK                (0x00000004ul)
#define SPI_CR_DOZE_EN_SHIFT               (2u)
#define SPI_CR_DOZE_EN_WIDTH               (1u)

#define SPI_CR_DBG_EN_MASK                 (0x00000008ul)
#define SPI_CR_DBG_EN_SHIFT                (3u)
#define SPI_CR_DBG_EN_WIDTH                (1u)

#define SPI_CR_RESET_TXFIFO_MASK           (0x00000100ul)
#define SPI_CR_RESET_TXFIFO_SHIFT          (8u)
#define SPI_CR_RESET_TXFIFO_WIDTH          (1u)

#define SPI_CR_RESET_RXFIFO_MASK           (0x00000200ul)
#define SPI_CR_RESET_RXFIFO_SHIFT          (9u)
#define SPI_CR_RESET_RXFIFO_WIDTH          (1u)

/* SR Bit fields */
#define SPI_SR_TX_DATA_FLAG_MASK           (0x00000001ul)
#define SPI_SR_TX_DATA_FLAG_SHIFT          (0u)
#define SPI_SR_TX_DATA_FLAG_WIDTH          (1u)

#define SPI_SR_RX_DATA_FLAG_MASK           (0x00000002ul)
#define SPI_SR_RX_DATA_FLAG_SHIFT          (1u)
#define SPI_SR_RX_DATA_FLAG_WIDTH          (1u)

#define SPI_SR_RX_WORD_DONE_FLAG_MASK      (0x00000100ul)
#define SPI_SR_RX_WORD_DONE_FLAG_SHIFT     (8u)
#define SPI_SR_RX_WORD_DONE_FLAG_WIDTH     (1u)

#define SPI_SR_FRAME_DONE_FLAG_MASK        (0x00000200ul)
#define SPI_SR_FRAME_DONE_FLAG_SHIFT       (9u)
#define SPI_SR_FRAME_DONE_FLAG_WIDTH       (1u)

#define SPI_SR_XFR_DONE_FLAG_MASK          (0x00000400ul)
#define SPI_SR_XFR_DONE_FLAG_SHIFT         (10u)
#define SPI_SR_XFR_DONE_FLAG_WIDTH         (1u)

#define SPI_SR_TX_UF_FLAG_MASK             (0x00000800ul)
#define SPI_SR_TX_UF_FLAG_SHIFT            (11u)
#define SPI_SR_TX_UF_FLAG_WIDTH            (1u)

#define SPI_SR_RX_OF_FLAG_MASK             (0x00001000ul)
#define SPI_SR_RX_OF_FLAG_SHIFT            (12u)
#define SPI_SR_RX_OF_FLAG_WIDTH            (1u)

#define SPI_SR_BUSY_FLAG_MASK              (0x01000000ul)
#define SPI_SR_BUSY_FLAG_SHIFT             (24u)
#define SPI_SR_BUSY_FLAG_WIDTH             (1u)

/* IER Bit fields */
#define SPI_IER_TX_DATA_IE_MASK            (0x00000001ul)
#define SPI_IER_TX_DATA_IE_SHIFT           (0u)
#define SPI_IER_TX_DATA_IE_WIDTH           (1u)

#define SPI_IER_RX_DATA_IE_MASK            (0x00000002ul)
#define SPI_IER_RX_DATA_IE_SHIFT           (1u)
#define SPI_IER_RX_DATA_IE_WIDTH           (1u)

#define SPI_IER_RX_WORD_DONE_IE_MASK       (0x00000100ul)
#define SPI_IER_RX_WORD_DONE_IE_SHIFT      (8u)
#define SPI_IER_RX_WORD_DONE_IE_WIDTH      (1u)

#define SPI_IER_FRAME_DONE_IE_MASK         (0x00000200ul)
#define SPI_IER_FRAME_DONE_IE_SHIFT        (9u)
#define SPI_IER_FRAME_DONE_IE_WIDTH        (1u)

#define SPI_IER_MST_TRANSFER_DONE_IE_MASK  (0x00000400ul)
#define SPI_IER_MST_TRANSFER_DONE_IE_SHIFT (10u)
#define SPI_IER_MST_TRANSFER_DONE_IE_WIDTH (1u)

#define SPI_IER_TX_UF_IE_MASK              (0x00000800ul)
#define SPI_IER_TX_UF_IE_SHIFT             (11u)
#define SPI_IER_TX_UF_IE_WIDTH             (1u)

#define SPI_IER_RX_OF_IE_MASK              (0x00001000ul)
#define SPI_IER_RX_OF_IE_SHIFT             (12u)
#define SPI_IER_RX_OF_IE_WIDTH             (1u)

#define SPI_IER_ALL_ISR_IE_MASK            (0x00001FFFul)
#define SPI_IER_ALL_ISR_IE_SHIFT           (0u)
#define SPI_IER_ALL_ISR_IE_WIDTH           (13u)

/* DER Bit fields */
#define SPI_DER_DMA_TX_EN_MASK             (0x00000001ul)
#define SPI_DER_DMA_TX_EN_SHIFT            (0u)
#define SPI_DER_DMA_TX_EN_WIDTH            (1u)

#define SPI_DER_DMA_RX_EN_MASK             (0x00000002ul)
#define SPI_DER_DMA_RX_EN_SHIFT            (1u)
#define SPI_DER_DMA_RX_EN_WIDTH            (1u)

/* CFGR0 Bit fields */
#define SPI_CFGR0_CIRCULAR_FIFO_EN_MASK    (0x00000100ul)
#define SPI_CFGR0_CIRCULAR_FIFO_EN_SHIFT   (8u)
#define SPI_CFGR0_CIRCULAR_FIFO_EN_WIDTH   (1u)

/* CFGR1 Bit fields */
#define SPI_CFGR1_MASTER_EN_MASK           (0x00000001ul)
#define SPI_CFGR1_MASTER_EN_SHIFT          (0u)
#define SPI_CFGR1_MASTER_EN_WIDTH          (1u)

#define SPI_CFGR1_AUTO_PCS_MASK            (0x00000004ul)
#define SPI_CFGR1_AUTO_PCS_SHIFT           (2u)
#define SPI_CFGR1_AUTO_PCS_WIDTH           (1u)

#define SPI_CFGR1_NO_STALL_MASK            (0x00000008ul)
#define SPI_CFGR1_NO_STALL_SHIFT           (3u)
#define SPI_CFGR1_NO_STALL_WIDTH           (1u)

#define SPI_CFGR1_MST_SCK_DLY_MASK         (0x00000070ul)
#define SPI_CFGR1_MST_SCK_DLY_SHIFT        (4u)
#define SPI_CFGR1_MST_SCK_DLY_WIDTH        (3u)

#define SPI_CFGR1_PCS_POL_MASK             (0x00000F00ul)
#define SPI_CFGR1_PCS_POL_SHIFT            (8u)
#define SPI_CFGR1_PCS_POL_WIDTH            (4u)

#define SPI_CFGR1_PIN_CFG_MASK             (0x03000000ul)
#define SPI_CFGR1_PIN_CFG_SHIFT            (24u)
#define SPI_CFGR1_PIN_CFG_WIDTH            (2u)

#define SPI_CFGR1_OUT_CFG_MASK             (0x04000000ul)
#define SPI_CFGR1_OUT_CFG_SHIFT            (26u)
#define SPI_CFGR1_OUT_CFG_WIDTH            (1u)

/* CCR Bit fields */
#define SPI_CCR_SCK_DIV_MASK               (0x000000FFul)
#define SPI_CCR_SCK_DIV_SHIFT              (0u)
#define SPI_CCR_SCK_DIV_WIDTH              (8u)

#define SPI_CCR_DBT_MASK                   (0x0000FF00ul)
#define SPI_CCR_DBT_SHIFT                  (8u)
#define SPI_CCR_DBT_WIDTH                  (8u)

#define SPI_CCR_PCS_SCK_MASK               (0x00FF0000ul)
#define SPI_CCR_PCS_SCK_SHIFT              (16u)
#define SPI_CCR_PCS_SCK_WIDTH              (8u)

#define SPI_CCR_SCK_PCS_MASK               (0xFF000000ul)
#define SPI_CCR_SCK_PCS_SHIFT              (24u)
#define SPI_CCR_SCK_PCS_WIDTH              (8u)

/* FCR Bit fields */
#define SPI_FCR_TX_FIFO_WATER_MASK         (0x0000001Ful)
#define SPI_FCR_TX_FIFO_WATER_SHIFT        (0u)
#define SPI_FCR_TX_FIFO_WATER_WIDTH        (5u)

#define SPI_FCR_RX_FIFO_WATER_MASK         (0x001F0000ul)
#define SPI_FCR_RX_FIFO_WATER_SHIFT        (16u)
#define SPI_FCR_RX_FIFO_WATER_WIDTH        (5u)

/* FSR Bit fields */
#define SPI_FSR_TX_FIFO_CNT_MASK           (0x0000001Ful)
#define SPI_FSR_TX_FIFO_CNT_SHIFT          (0u)
#define SPI_FSR_TX_FIFO_CNT_WIDTH          (5u)

#define SPI_FSR_RX_FIFO_CNT_MASK           (0x001F0000ul)
#define SPI_FSR_RX_FIFO_CNT_SHIFT          (16u)
#define SPI_FSR_RX_FIFO_CNT_WIDTH          (5u)

/* TCR Bit fields */
#define SPI_TCR_FRAME_SIZE_MASK            (0x00000FFFul)
#define SPI_TCR_FRAME_SIZE_SHIFT           (0u)
#define SPI_TCR_FRAME_SIZE_WIDTH           (12u)

#define SPI_TCR_TRANSFER_WIDTH_MASK        (0x00030000ul)
#define SPI_TCR_TRANSFER_WIDTH_SHIFT       (16u)
#define SPI_TCR_TRANSFER_WIDTH_WIDTH       (2u)

#define SPI_TCR_TX_MASK_MASK               (0x00040000ul)
#define SPI_TCR_TX_MASK_SHIFT              (18u)
#define SPI_TCR_TX_MASK_WIDTH              (1u)

#define SPI_TCR_RX_MASK_MASK               (0x00080000ul)
#define SPI_TCR_RX_MASK_SHIFT              (19u)
#define SPI_TCR_RX_MASK_WIDTH              (1u)

#define SPI_TCR_CONTINUE_CMD_MASK          (0x00100000ul)
#define SPI_TCR_CONTINUE_CMD_SHIFT         (20u)
#define SPI_TCR_CONTINUE_CMD_WIDTH         (1u)

#define SPI_TCR_CONTINUE_TRANSFER_MASK     (0x00200000ul)
#define SPI_TCR_CONTINUE_TRANSFER_SHIFT    (21u)
#define SPI_TCR_CONTINUE_TRANSFER_WIDTH    (1u)

#define SPI_TCR_BYTE_SWAP_MASK             (0x00400000ul)
#define SPI_TCR_BYTE_SWAP_SHIFT            (22u)
#define SPI_TCR_BYTE_SWAP_WIDTH            (1u)

#define SPI_TCR_LSB_FIRST_MASK             (0x00800000ul)
#define SPI_TCR_LSB_FIRST_SHIFT            (23u)
#define SPI_TCR_LSB_FIRST_WIDTH            (1u)

#define SPI_TCR_PCS_SEL_MASK               (0x03000000ul)
#define SPI_TCR_PCS_SEL_SHIFT              (24u)
#define SPI_TCR_PCS_SEL_WIDTH              (2u)

#define SPI_TCR_PRESCALER_MASK             (0x38000000ul)
#define SPI_TCR_PRESCALER_SHIFT            (27u)
#define SPI_TCR_PRESCALER_WIDTH            (3u)

#define SPI_TCR_CPHA_MASK                  (0x40000000ul)
#define SPI_TCR_CPHA_SHIFT                 (30u)
#define SPI_TCR_CPHA_WIDTH                 (1u)

#define SPI_TCR_CPOL_MASK                  (0x80000000ul)
#define SPI_TCR_CPOL_SHIFT                 (31u)
#define SPI_TCR_CPOL_WIDTH                 (1u)

/* TDR Bit fields */
#define SPI_TDR_DATA_MASK                  (0xFFFFFFFFul)
#define SPI_TDR_DATA_SHIFT                 (0u)
#define SPI_TDR_DATA_WIDTH                 (32u)

/* RSR Bit fields */
#define SPI_RSR_SOF_MASK                   (0x00000001ul)
#define SPI_RSR_SOF_SHIFT                  (0u)
#define SPI_RSR_SOF_WIDTH                  (1u)

#define SPI_RSR_RX_FIFO_EMPTY_MASK         (0x00000002ul)
#define SPI_RSR_RX_FIFO_EMPTY_SHIFT        (1u)
#define SPI_RSR_RX_FIFO_EMPTY_WIDTH        (1u)

/* RDR Bit fields */
#define SPI_RDR_DATA_MASK                  (0xFFFFFFFFul)
#define SPI_RDR_DATA_SHIFT                 (0u)
#define SPI_RDR_DATA_WIDTH                 (32u)

/******************************************************************************
 * the typedefs
 *****************************************************************************/

/*! \brief the definition of spi register */
typedef struct _SpiRegType_
{
    volatile uint32_t VERID;   /*!< SPI Version ID Register, offset: 0x00 */
    volatile uint32_t PARAM;   /*!< SPI Parameters Register, offset: 0x04 */
    uint32_t          RES1[2]; /*!< SPI Res, offset: 0x08 */
    volatile uint32_t CR;      /*!< SPI Control Register, offset: 0x10 */
    volatile uint32_t SR;      /*!< SPI Status Register, offset: 0x14 */
    volatile uint32_t IER;     /*!< SPI Interrupt Enable Register, offset: 0x18 */
    volatile uint32_t DER;     /*!< SPI DMA control Register, offset: 0x1C */
    volatile uint32_t CFGR0;   /*!< SPI Configuration 0 Register, offset: 0x20 */
    volatile uint32_t CFGR1;   /*!< SPI Configuration 1 Register, offset: 0x24 */
    uint32_t          RES2[6]; /*!< SPI Res, offset: 0x28 */
    volatile uint32_t CCR;     /*!< SPI Clock Configuration Register, offset: 0x40 */
    uint32_t          RES3[5]; /*!< SPI  Res Register, offset: 0x44 */
    volatile uint32_t FCR;     /*!< SPI FIFO Control Register, offset: 0x58 */
    volatile uint32_t FSR;     /*!< SPI FIFO Status Register, offset: 0x5C */
    volatile uint32_t TCR;     /*!< SPI Transmit Control Register, offset: 0x60 */
    volatile uint32_t TDR;     /*!< SPI Transmit Data Register, offset: 0x64 */
    uint32_t          RES4[2]; /*!< SPI Res Register, offset: 0x68 */
    volatile uint32_t RSR;     /*!< SPI Receive Status Register, offset: 0x70 */
    volatile uint32_t RDR;     /*!< SPI Receive Data Register, offset: 0x74 */
} SpiRegType;

/******************************************************************************
 * the globals
 *****************************************************************************/

/******************************************************************************
 * the function prototypes
 *****************************************************************************/

/*! \brief Get the tx fifo depth size that the hardware supports
 *
 * this function get the tx fifo depth how many the hardware supported
 *
 * \param[in] obj : base address for the SPI instance
 * \return: uint8_t : Real depth =  2^(TX_FIFO_DEPTH)
 *           0h:1
 *           1h:2
 *           2h:4
 *           3h:8
 *           4h:16
 */
__attribute__((always_inline)) static inline uint8_t SpiReg_GetTxFifoDepth(SpiRegType *obj)
{
    uint8_t tRtn          = 0;
    uint8_t tFifoDepth[5] = {1, 2, 4, 8, 16};

    tRtn = (((obj->PARAM & SPI_PARAM_TX_FIFO_DEPTH_MASK) >> SPI_PARAM_TX_FIFO_DEPTH_SHIFT) & 0xFF);
    tRtn = tRtn < 4 ? tRtn : 4;

    return tFifoDepth[tRtn];
}

/*! \brief Get the rx fifo depth size that the hardware supports
 *
 * this function get the rx fifo depth how many the hardware supported
 *
 * \param[in] obj : base address for the SPI instance
 * \return: uint8_t : Real depth =  2^(RX_FIFO_DEPTH)
 *           0h:1
 *           1h:2
 *           2h:4
 *           3h:8
 *           4h:16
 */
__attribute__((always_inline)) static inline uint8_t SpiReg_GetRxFifoDepth(const SpiRegType *obj)
{
    uint8_t tRtn          = 0;
    uint8_t tFifoDepth[5] = {1, 2, 4, 8, 16};

    tRtn = (((obj->PARAM & SPI_PARAM_RX_FIFO_DEPTH_MASK) >> SPI_PARAM_RX_FIFO_DEPTH_SHIFT) & 0xFF);
    tRtn = tRtn < 4 ? tRtn : 4;

    return tFifoDepth[tRtn];
}

/*! \brief spi module enable
 *
 * this function enable the module
 *
 * \param[in] obj: base address for the SPI instance
 * \param[in] enable : enable or disable module
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_EnableModule(SpiRegType *obj, bool enable)
{
    uint32_t tRegValue = obj->CR;

    if(enable == true)
    {
        obj->CR = ((1ul << SPI_CR_EN_SHIFT) | ((~SPI_CR_EN_MASK) & tRegValue));
    }
    else
    {
        obj->CR = ((0ul << SPI_CR_EN_SHIFT) | ((~SPI_CR_EN_MASK) & tRegValue));
    }
}

/*! \brief module software reset
 *
 * Reset all internal logic and registers, except the Control Register.
 *       RST remains set until cleared by software.
 *
 * \param[in] obj: base address for the SPI instance
 * \param[in] reset: enable or disable reset module
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_ResetModule(SpiRegType *obj, bool reset)
{
    uint32_t tRegValue = obj->CR;

    if(reset == true)
    {
        obj->CR = ((1ul << SPI_CR_RESET_SHIFT) | ((~SPI_CR_RESET_MASK) & tRegValue));
    }
    else
    {
        obj->CR = ((0ul << SPI_CR_RESET_SHIFT) | ((~SPI_CR_RESET_MASK) & tRegValue));
    }
}

/*! \brief STOP/DEBUG Mode Enable
 *
 * Enables or disables the SPI module in STOP and DEBUG mode.
 *       This bit should be updated only when the SPI module is disabled.
 *
 * \param[in] obj: base address for the SPI instance
 * \param[in] enable: enable or disable doze mode
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_EnableDozeMode(SpiRegType *obj, bool enable)
{
    uint32_t tRegValue = obj->CR;

    if(enable == true)
    {
        obj->CR = ((1ul << SPI_CR_DOZE_EN_SHIFT) | ((~SPI_CR_DOZE_EN_MASK) & tRegValue));
    }
    else
    {
        obj->CR = ((0ul << SPI_CR_DOZE_EN_SHIFT) | ((~SPI_CR_DOZE_EN_MASK) & tRegValue));
    }
}

/*! \brief Debug Enable
 *
 * Enables or disables the SPI module in debug mode.
 *       Debug Enable bit should be updated only when the SPI module is disabled.
 *
 * \param[in] obj: base address for the SPI instance
 * \param[in] enable: enable or disable debug mode
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_EnableDebugMode(SpiRegType *obj, bool enable)
{
    uint32_t tRegValue = obj->CR;

    if(enable == true)
    {
        obj->CR = ((1ul << SPI_CR_DBG_EN_SHIFT) | ((~SPI_CR_DBG_EN_MASK) & tRegValue));
    }
    else
    {
        obj->CR = ((0ul << SPI_CR_DBG_EN_SHIFT) | ((~SPI_CR_DBG_EN_MASK) & tRegValue));
    }
}

/*! \brief Reset Transmit FIFO
 *
 * the bit is WO
 *
 * \param[in] obj: base address for the SPI instance
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_ResetTxFIFO(SpiRegType *obj)
{
    uint32_t tRegValue = obj->CR;

    obj->CR = ((1ul << SPI_CR_RESET_TXFIFO_SHIFT) | ((~SPI_CR_RESET_TXFIFO_MASK) & tRegValue));
}

/*! \brief Reset Receive FIFO
 *
 * the bit is WO
 *
 * \param[in] obj: base address for the SPI instance
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_ResetRxFIFO(SpiRegType *obj)
{
    uint32_t tRegValue = obj->CR;

    obj->CR = ((1ul << SPI_CR_RESET_RXFIFO_SHIFT) | ((~SPI_CR_RESET_RXFIFO_MASK) & tRegValue));
}

/*! \brief Transmit Data Flag
 *
 * The Transmit Data Flag is set whenever the number of words in the transmit FIFO is equal or less than FCR[TXWATER]
 *       (FIFO Control Register)
 *
 * \param[in] obj: base address for the SPI instance
 * \return: uint8_t
 *          0b - Transmit data not requested
 *          1b - Transmit data is requested
 */
__attribute__((always_inline)) static inline uint8_t SpiReg_GetTxDataFlag(const SpiRegType *obj)
{
    uint8_t tRtn = 0;

    tRtn = ((obj->SR & SPI_SR_TX_DATA_FLAG_MASK) >> SPI_SR_TX_DATA_FLAG_SHIFT) & 0xFF;

    return tRtn;
}

/*! \brief Receive Data Flag
 *
 * The Receive Data Flag is set whenever the number of words in the receive FIFO is greater than
 *       FCR[RXWATER] (FIFO Control Register)
 *
 * \param[in] obj: base address for the SPI instance
 * \return: uint8_t
 *          0b - Receive Data is not ready
 *          1b - Receive data is ready
 */
__attribute__((always_inline)) static inline uint8_t SpiReg_GetRxDataFlag(const SpiRegType *obj)
{
    uint8_t tRtn = 0;

    tRtn = (((obj->SR & SPI_SR_RX_DATA_FLAG_MASK) >> SPI_SR_RX_DATA_FLAG_SHIFT) & 0xFF);

    return tRtn;
}

/*! \brief Get Receive Word Complete Flag
 *
 * The Word Complete Flag will set when the last bit of a received word is sampled.
 *
 * \param[in] obj: base address for the SPI instance
 * \return: uint8_t
 *          0b : Transfer of a received word has not yet completed
 *          1b : Transfer of a received word has completed
 */
__attribute__((always_inline)) static inline uint8_t SpiReg_GetRxWordDoneFlag(const SpiRegType *obj)
{
    uint8_t tRtn = 0;

    tRtn = (((obj->SR & SPI_SR_RX_WORD_DONE_FLAG_MASK) >> SPI_SR_RX_WORD_DONE_FLAG_SHIFT) & 0xFF);

    return tRtn;
}

/*! \brief Clear Receive Word Complete Flag
 *
 * this flag is clear by write one to the referenced bit
 *
 * \param[in] obj: base address for the SPI instance
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_ClearRxWordDoneFlag(SpiRegType *obj)
{
    obj->SR |= SPI_SR_RX_WORD_DONE_FLAG_MASK;
}

/*! \brief Get Frame Complete Flag
 *
 * The Frame Complete Flag will set at the end of each frame transfer.
 *
 * \param[in] obj: base address for the SPI instance
 * \return: uint8_t
 *          0b : Frame transfer has not completed
 *          1b : Frame transfer has completed
 */
__attribute__((always_inline)) static inline uint8_t SpiReg_GetFrameDoneFlag(const SpiRegType *obj)
{
    uint8_t tRtn = 0;

    tRtn = (((obj->SR & SPI_SR_FRAME_DONE_FLAG_MASK) >> SPI_SR_FRAME_DONE_FLAG_SHIFT) & 0xFF);

    return tRtn;
}

/*! \brief Clear Frame Complete Flag
 *
 * this flag is clear by write one to the referenced bit
 *
 * \param[in] obj: base address for the SPI instance
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_ClearFrameDoneFlag(SpiRegType *obj)
{
    obj->SR |= SPI_SR_FRAME_DONE_FLAG_MASK;
}

/*! \brief Get Master Transfer Complete Flag
 *
 * In master mode when the SPI returns to idle state，when the PCS negates,
         the Transfer Complete Flag will set.
 *
 * \param[in] obj: base address for the SPI instance
 * \return: uint8_t
 *          0b : All transfers have not completed
 *          1b : All transfers have completed
 */
__attribute__((always_inline)) static inline uint8_t SpiReg_GetMasterTransferDoneFlag(const SpiRegType *obj)
{
    uint8_t tRtn = 0;

    tRtn = (((obj->SR & SPI_SR_XFR_DONE_FLAG_MASK) >> SPI_SR_XFR_DONE_FLAG_SHIFT) & 0xFF);

    return tRtn;
}

/*! \brief Clear Master Transfer Complete Flag
 *
 * this flag is clear by write one to the referenced bit
 *
 * \param[in] obj: base address for the SPI instance
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_ClearMasterTransferDoneFlag(SpiRegType *obj)
{
    obj->SR |= SPI_SR_XFR_DONE_FLAG_MASK;
}

/*! \brief Get Transmit FIFO underflow Flag
 *
 * The Transmit Error Flag will set when the Transmit FIFO under runs
 *
 * \param[in] obj: base address for the SPI instance
 * \return: uint8_t
 *          0b : Transmit FIFO underrun has not occurred
 *          1b : Transmit FIFO underrun has occurred
 */
__attribute__((always_inline)) static inline uint8_t SpiReg_GetTxUnderFlowFlag(const SpiRegType *obj)
{
    uint8_t tRtn = 0;

    tRtn = (((obj->SR & SPI_SR_TX_UF_FLAG_MASK) >> SPI_SR_TX_UF_FLAG_SHIFT) & 0xFF);

    return tRtn;
}

/*! \brief Clear Transmit FIFO underflow Flag
 *
 * this flag is clear by write one to the referenced bit
 *
 * \param[in] obj: base address for the SPI instance
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_ClearTxUnderFlowFlag(SpiRegType *obj)
{
    obj->SR |= SPI_SR_TX_UF_FLAG_MASK;
}

/*! \brief Get RX FIFO overflow flag
 *
 * The Receive Error Flag will set when the Receiver FIFO overflows. When the Receive Error Flag is set
 *
 * \param[in] obj: base address for the SPI instance
 * \return: uint8_t
 *          0b : Receive FIFO has not overflowed
 *          1b : Receive FIFO has overflowed
 */
__attribute__((always_inline)) static inline uint8_t SpiReg_GetRxOverFlowFlag(const SpiRegType *obj)
{
    uint8_t tRtn = 0;

    tRtn = (((obj->SR & SPI_SR_RX_OF_FLAG_MASK) >> SPI_SR_RX_OF_FLAG_SHIFT) & 0xFF);

    return tRtn;
}

/*! \brief Clear RX FIFO overflow flag
 *
 * this flag is clear by write one to the referenced bit
 *
 * \param[in] obj: base address for the SPI instance
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_ClearRxOverFlowFlag(SpiRegType *obj)
{
    obj->SR |= SPI_SR_RX_OF_FLAG_MASK;
}

/*! \brief Module Busy Flag
 *
 * this function get the current status about the module
 *
 * \param[in] obj: base address for the SPI instance
 * \return: uint8_t
 *          0b : SPI is idle
 *          1b : SPI is busy
 */
__attribute__((always_inline)) static inline uint8_t SpiReg_GetBusyFlag(const SpiRegType *obj)
{
    uint8_t tRtn = 0;

    tRtn = (((obj->SR & SPI_SR_BUSY_FLAG_MASK) >> SPI_SR_BUSY_FLAG_SHIFT) & 0xFF);

    return tRtn;
}

/*! \brief RX FIFO overflow interrupt enable or disable
 *
 * this function enable the rx overflow interrupt request if the condition is matched
 *
 * \param[in] obj: base address for the SPI instance
 * \param[in] enable: RX FIFO overflow interrupt enable
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_SetRxOverflowIsr(SpiRegType *obj, bool enable)
{
    uint32_t tRegValue = obj->IER;

    if(enable == true)
    {
        obj->IER = ((1ul << SPI_IER_RX_OF_IE_SHIFT) | ((~SPI_IER_RX_OF_IE_MASK) & tRegValue));
    }
    else
    {
        obj->IER = ((0ul << SPI_IER_RX_OF_IE_SHIFT) | ((~SPI_IER_RX_OF_IE_MASK) & tRegValue));
    }
}

/*! \brief Transmit FIFO underflow interrupt enable or disable
 *
 * this function enable the tx underflow interrupt request if the condition is matched
 *
 * \param[in] obj: base address for the SPI instance
 * \param[in] enable: Transmit FIFO underflow interrupt enable
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_SetTxUnderflowIsr(SpiRegType *obj, bool enable)
{
    uint32_t tRegValue = obj->IER;

    if(enable == true)
    {
        obj->IER = ((1ul << SPI_IER_TX_UF_IE_SHIFT) | ((~SPI_IER_TX_UF_IE_MASK) & tRegValue));
    }
    else
    {
        obj->IER = ((0ul << SPI_IER_TX_UF_IE_SHIFT) | ((~SPI_IER_TX_UF_IE_MASK) & tRegValue));
    }
}

/*! \brief Master Transfer Complete interrupt enable or disable
 *
 * this function enable the tx transfer done interrupt request if the condition is matched
 *
 * \param[in] obj: base address for the SPI instance
 * \param[in] enable: Master Transfer Complete interrupt enable
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_SetTxTransferDoneIsr(SpiRegType *obj, bool enable)
{
    uint32_t tRegValue = obj->IER;

    if(enable == true)
    {
        obj->IER = ((1ul << SPI_IER_MST_TRANSFER_DONE_IE_SHIFT) | ((~SPI_IER_MST_TRANSFER_DONE_IE_MASK) & tRegValue));
    }
    else
    {
        obj->IER = ((0ul << SPI_IER_MST_TRANSFER_DONE_IE_SHIFT) | ((~SPI_IER_MST_TRANSFER_DONE_IE_MASK) & tRegValue));
    }
}

/*! \brief Master Transfer Complete interrupt enable or disable
 *
 * this function enable the frame done interrupt request if the condition is matched
 *
 * \param[in] obj: base address for the SPI instance
 * \param[in] enable: Frame Complete interrupt enable
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_SetFrameDoneIsr(SpiRegType *obj, bool enable)
{
    uint32_t tRegValue = obj->IER;

    if(enable == true)
    {
        obj->IER = ((1ul << SPI_IER_FRAME_DONE_IE_SHIFT) | ((~SPI_IER_FRAME_DONE_IE_MASK) & tRegValue));
    }
    else
    {
        obj->IER = ((0ul << SPI_IER_FRAME_DONE_IE_SHIFT) | ((~SPI_IER_FRAME_DONE_IE_MASK) & tRegValue));
    }
}

/*! \brief Receive Word Complete interrupt enable or disable
 *
 * this function enable the rx word done interrupt request if the condition is matched
 *
 * \param[in] obj: base address for the SPI instance
 * \param[in] enable: Receive Word Complete interrupt enable
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_SetRxWordDoneIsr(SpiRegType *obj, bool enable)
{
    uint32_t tRegValue = obj->IER;

    if(enable == true)
    {
        obj->IER = ((1ul << SPI_IER_RX_WORD_DONE_IE_SHIFT) | ((~SPI_IER_RX_WORD_DONE_IE_MASK) & tRegValue));
    }
    else
    {
        obj->IER = ((0ul << SPI_IER_RX_WORD_DONE_IE_SHIFT) | ((~SPI_IER_RX_WORD_DONE_IE_MASK) & tRegValue));
    }
}

/*! \brief Receive Data interrupt enable
 *
 * this function enable the rx data interrupt request if the condition is matched
 *
 * \param[in] obj: base address for the SPI instance
 * \param[in] enable: Receive Data interrupt enable
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_SetRxDataIsr(SpiRegType *obj, bool enable)
{
    uint32_t tRegValue = obj->IER;

    if(enable == true)
    {
        obj->IER = ((1ul << SPI_IER_RX_DATA_IE_SHIFT) | ((~SPI_IER_RX_DATA_IE_MASK) & tRegValue));
    }
    else
    {
        obj->IER = ((0ul << SPI_IER_RX_DATA_IE_SHIFT) | ((~SPI_IER_RX_DATA_IE_MASK) & tRegValue));
    }
}

/*! \brief Transmit Data interrupt enable or disable
 *
 * this function enable the tx data interrupt request if the condition is matched
 *
 * \param[in] obj: base address for the SPI instance
 * \param[in] enable: Transmit Data interrupt enable
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_SetTxDataIsr(SpiRegType *obj, bool enable)
{
    uint32_t tRegValue = obj->IER;

    if(enable == true)
    {
        obj->IER = ((1ul << SPI_IER_TX_DATA_IE_SHIFT) | ((~SPI_IER_TX_DATA_IE_MASK) & tRegValue));
    }
    else
    {
        obj->IER = ((0ul << SPI_IER_TX_DATA_IE_SHIFT) | ((~SPI_IER_TX_DATA_IE_MASK) & tRegValue));
    }
}

/*! \brief Enable the interrupt request with combination
 *
 * this function enable the interrupt request with the intMask
 *
 * \param[in] obj :: base address for the SPI instance
 * \param[in] intMask : which interrupt request to be operated
 *            example : SPI_IER_RX_DATA_IE_MASK | SPI_IER_TX_DATA_IE_MASK
 * \param[in] enable : enable or disable
 * \return void
 */
__attribute__((always_inline)) static inline void SpiReg_EnableIntReq(SpiRegType *obj, uint32_t intMask, bool enable)
{
    uint32_t tRegValue = obj->IER;

    if(enable == true)
    {
        obj->IER = (intMask | ((~intMask) & tRegValue));
    }
    else
    {
        obj->IER = ((~intMask) & tRegValue);
    }
}

/*! \brief Get the interrupt request is enabled or not
 *
 * this function enable the interrupt request with the intMask
 *
 * \param[in] obj :: base address for the SPI instance
 * \param[in] intMask : which interrupt request to be operated
 * \return bool
 *          true: the interrupt is enabled
 *          false: the interrupt is disabled
 */
__attribute__((always_inline)) static inline bool SpiReg_GetIntReqEnableState(const SpiRegType *obj, uint32_t intMask)
{
    bool tRtn = false;

    if((obj->IER & intMask) == intMask)
    {
        tRtn = true;
    }

    return tRtn;
}

/*! \brief receive dma enable or disable
 *
 * this function enable the rx with dma method
 *
 * \param[in] obj: base address for the SPI instance
 * \param[in] enable: receive dma enable
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_SetRxDMA(SpiRegType *obj, bool enable)
{
    uint32_t tRegValue = obj->DER;

    if(enable == true)
    {
        obj->DER = ((1ul << SPI_DER_DMA_RX_EN_SHIFT) | ((~SPI_DER_DMA_RX_EN_MASK) & tRegValue));
    }
    else
    {
        obj->DER = ((0ul << SPI_DER_DMA_RX_EN_SHIFT) | ((~SPI_DER_DMA_RX_EN_MASK) & tRegValue));
    }
}

/*! \brief transmit dma enable or disable
 *
 * this function enable the tx with dma method
 *
 * \param[in] obj: base address for the SPI instance
 * \param[in] enable: transmit dma enable
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_SetTxDMA(SpiRegType *obj, bool enable)
{
    uint32_t tRegValue = obj->DER;

    if(enable == true)
    {
        obj->DER = ((1ul << SPI_DER_DMA_TX_EN_SHIFT) | ((~SPI_DER_DMA_TX_EN_MASK) & tRegValue));
    }
    else
    {
        obj->DER = ((0ul << SPI_DER_DMA_TX_EN_SHIFT) | ((~SPI_DER_DMA_TX_EN_MASK) & tRegValue));
    }
}

/*! \brief Set Clock Polarity
 *
 * The Clock Polarity field is only updated when PCS negated.
 *
 * \param[in] obj : base address for the SPI instance
 * \param[in] clockPolarity :
 *            0b : The inactive state value of SCK is low
 *            1b : The inactive state value of SCK is high
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_SetClockPolarity(SpiRegType *obj, uint8_t clockPolarity)
{
    uint32_t tmp = obj->TCR;

    tmp &= ~SPI_TCR_CPOL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(clockPolarity)) << SPI_TCR_CPOL_SHIFT)) & SPI_TCR_CPOL_MASK);
    obj->TCR = tmp;
}

/*! \brief Set Clock Phase
 *
 * The Clock Phase field is only updated when PCS negated.
 *
 * \param[in] obj : base address for the SPI instance
 * \param[in] clockPhase :
 *            0b : Data is captured on the leading edge of SCK and changed on the following edge of SCK
 *            1b : Data is changed on the leading edge of SCK and captured on the following edge of SCK
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_SetClockPhase(SpiRegType *obj, uint8_t clockPhase)
{
    uint32_t tmp = obj->TCR;

    tmp &= ~SPI_TCR_CPHA_MASK;
    tmp |= (((uint32_t)(((uint32_t)(clockPhase)) << SPI_TCR_CPHA_SHIFT)) & SPI_TCR_CPHA_MASK);
    obj->TCR = tmp;
}

/*! \brief Set Prescaler Value
 *
 * For all SPI bus transfers, the Prescaler value applied to the clock configuration register. The Prescaler Value field is only updated when PCS negated.
 *
 * \param[in] obj : base address for the SPI instance
 * \param[in] prescaler :
 *            000b : Divide by 1
 *            001b : Divide by 2
 *            010b : Divide by 4
 *            011b : Divide by 8
 *            100b : Divide by 16
 *            101b : Divide by 32
 *            110b : Divide by 64
 *            111b : Divide by 128
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_SetPrescaler(SpiRegType *obj, uint8_t prescaler)
{
    uint32_t tmp = obj->TCR;

    tmp &= ~SPI_TCR_PRESCALER_MASK;
    tmp |= (((uint32_t)(((uint32_t)(prescaler)) << SPI_TCR_PRESCALER_SHIFT)) & SPI_TCR_PRESCALER_MASK);
    obj->TCR = tmp;
}

/*! \brief Select Peripheral Chip
 *
 * Configures the peripheral chip select used for the transfer. The Peripheral Chip Select field is only updated when PCS negated.
 *
 * \param[in] obj : base address for the SPI instance
 * \param[in] pcsSelection :
 *            00b : Transfer using SPI_PCS[0]
 *            01b : Transfer using SPI_PCS[1]
 *            10b : Transfer using SPI_PCS[2]
 *            11b : Transfer using SPI_PCS[3]
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_SetPcsSelection(SpiRegType *obj, uint8_t pcsSelection)
{
    uint32_t tmp = obj->TCR;

    tmp &= ~SPI_TCR_PCS_SEL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(pcsSelection)) << SPI_TCR_PCS_SEL_SHIFT)) & SPI_TCR_PCS_SEL_MASK);
    obj->TCR = tmp;
}

/*! \brief Set data transfer bit direction
 *
 * Note:
 *
 * \param[in] obj : base address for the SPI instance
 * \param[in] lsbFirst :
 *            0b:Data is transferred MSB first
 *            1b:Data is transferred LSB first
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_SetLowBitFirstTransfer(SpiRegType *obj, uint8_t lsbFirst)
{
    uint32_t tmp = obj->TCR;

    tmp &= ~SPI_TCR_LSB_FIRST_MASK;
    tmp |= (((uint32_t)(((uint32_t)(lsbFirst)) << SPI_TCR_LSB_FIRST_SHIFT)) & SPI_TCR_LSB_FIRST_MASK);
    obj->TCR = tmp;
}

/*! \brief Get data transfer bit direction
 *
 *
 *
 * \param[in] obj: base address for the SPI instance
 * \return: transfer bit direction
 *          0b:Data is transferred MSB first
 *          1b:Data is transferred LSB first
 */
__attribute__((always_inline)) static inline uint8_t SpiReg_GetTransferDataBitLsbState(const SpiRegType *obj)
{
    uint8_t tRtn = 0;

    if((obj->TCR & SPI_TCR_LSB_FIRST_MASK) != 0u)
    {
        tRtn = 1;
    }

    return tRtn;
}

/*! \brief Set Byte Swap
 *
 * Byte swap will swap the contents of [31:24] with [7:0] and [23:16] with [15:8] for each transmit data word read from
 *       the FIFO and for each received data word stored to the FIFO
 *
 * \param[in] obj : base address for the SPI instance
 * \param[in] enable :
 *            0b:Byte swap is disabled
 *            1b:Byte swap is enabled
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_SetByteSwap(SpiRegType *obj, bool enable)
{
    uint32_t tRegValue = obj->TCR;

    if(enable == true)
    {
        obj->TCR = ((1ul << SPI_TCR_BYTE_SWAP_SHIFT) | ((~SPI_TCR_BYTE_SWAP_MASK) & tRegValue));
    }
    else
    {
        obj->TCR = ((0ul << SPI_TCR_BYTE_SWAP_SHIFT) | ((~SPI_TCR_BYTE_SWAP_MASK) & tRegValue));
    }
}

/*! \brief Set Continuous Transfer
 *
 * In master mode, continuous transfer will keep the PCS asserted at the end of the frame size,
 *       until a command word is received that starts a new frame.
 *       In slave mode, when continuous transfer is enabled, the SPI will only transmit the first FRAMESZ bits;
 *       after which the SPI will transmit received data (assuming a 32-bit shift register) until the next PCS negation.
 *
 * \param[in] obj : base address for the SPI instance
 * \param[in] enable :
 *            0b:Continuous transfer is disabled
 *            1b:Continuous transfer is enabled
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_SetContinuousTransfer(SpiRegType *obj, bool enable)
{
    uint32_t tRegValue = obj->TCR;

    if(enable == true)
    {
        obj->TCR = ((1ul << SPI_TCR_CONTINUE_TRANSFER_SHIFT) | ((~SPI_TCR_CONTINUE_TRANSFER_MASK) & tRegValue));
    }
    else
    {
        obj->TCR = ((0ul << SPI_TCR_CONTINUE_TRANSFER_SHIFT) | ((~SPI_TCR_CONTINUE_TRANSFER_MASK) & tRegValue));
    }
}

/*! \brief Set Continuing Command
 *
 * In master mode, the Continuing Command bit allows the command word to be changed within a transfer.
 *       1. in continuous transfer
 *       The initial command word must enable continuous transfer (CONT=1),
 *       the continuing command must set this bit (CONTC=1),
 *       the continuing command word must be loaded on a frame size boundary.
 *       2. in non-continuous transfer
 *       the continuing command must set this bit (CONTC=1),
 *       the continuing command word must be loaded on a frame size boundary.
 *
 * \param[in] obj : base address for the SPI instance
 * \param[in] cmd :
 *            0b:Command word for start of new transfer
 *            1b:Command word for continuing transfer
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_SetContinuousCmd(SpiRegType *obj, uint8_t cmd)
{
    uint32_t tmp = obj->TCR;

    tmp &= ~SPI_TCR_CONTINUE_CMD_MASK;
    tmp |= (((uint32_t)(((uint32_t)(cmd)) << SPI_TCR_CONTINUE_CMD_SHIFT)) & SPI_TCR_CONTINUE_CMD_MASK);
    obj->TCR = tmp;
}

/*! \brief Set Receive Data Mask
 *
 * When set, receive data is masked (receive data is not stored in receive FIFO).
 *
 * \param[in] obj : base address for the SPI instance
 * \param[in] enableMask :
 *            0b:Normal transfer
 *            1b:Receive data is masked
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_SetRxDataMask(SpiRegType *obj, bool enableMask)
{
    uint32_t tRegValue = obj->TCR;

    if(enableMask == true)
    {
        obj->TCR = ((1ul << SPI_TCR_RX_MASK_SHIFT) | ((~SPI_TCR_RX_MASK_MASK) & tRegValue));
    }
    else
    {
        obj->TCR = ((0ul << SPI_TCR_RX_MASK_SHIFT) | ((~SPI_TCR_RX_MASK_MASK) & tRegValue));
    }
}

/*! \brief Set Transmit Data Mask
 *
 * When set, transmit data is masked (no data is loaded from transmit FIFO and output pin is tristated).
 *       In master mode, the Transmit Data Mask bit will initiate a new transfer
 *       which cannot be aborted by another command word; TXMSK bit will be cleared by hardware at the end of the transfer.
 *
 * \param[in] obj : base address for the SPI instance
 * \param[in] enableMask :
 *            0b:Normal transfer
 *            1b:Mask transmit data
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_SetTxDataMask(SpiRegType *obj, bool enableMask)
{
    uint32_t tRegValue = obj->TCR;

    if(enableMask == true)
    {
        obj->TCR = ((1ul << SPI_TCR_TX_MASK_SHIFT) | ((~SPI_TCR_TX_MASK_MASK) & tRegValue));
    }
    else
    {
        obj->TCR = ((0ul << SPI_TCR_TX_MASK_SHIFT) | ((~SPI_TCR_TX_MASK_MASK) & tRegValue));
    }
}

/*! \brief Set Transfer data Width
 *
 * Configures between serial (1-bit) or parallel transfers. For half-duplex parallel transfers, either Receive Data Mask (RXMSK) or Transmit Data Mask (TXMSK) must be set.
 *
 * \param[in] obj : base address for the SPI instance
 * \param[in] transferWidth :
 *            00b:1 bit transfer
 *            01b:2 bit transfer
 *            10b:Reserved
 *            11b:Reserved
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_SetTransferWidth(SpiRegType *obj, uint8_t transferWidth)
{
    uint32_t tmp = obj->TCR;

    tmp &= ~SPI_TCR_TRANSFER_WIDTH_MASK;
    tmp |= (((uint32_t)(((uint32_t)(transferWidth)) << SPI_TCR_TRANSFER_WIDTH_SHIFT)) & SPI_TCR_TRANSFER_WIDTH_MASK);
    obj->TCR = tmp;
}

/*! \brief Set Frame Size
 *
 * The minimum frame size is 8 bits, The minimum word size is 2 bits; a frame size of 33 bits (or similar) is not supported.
 *       If the frame size is larger than 32 bits, then the frame is divided into multiple words of 32-bits;
 *       each word is loaded from the transmit FIFO and stored in the receive FIFO separately.
 *       If the size of the frame is not divisible by 32, then the last load of the transmit FIFO and store of the receive FIFO will contain the remainder bits.
 *       For example, a 72-bit transfer will consist of 3 words: the 1st and 2nd words are 32 bits, and the 3rd word is 8 bits.
 *
 * \param[in] obj : base address for the SPI instance
 * \param[in] frameSize :Configures the frame size in number of bits equal to (FRAMESZ + 1)
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_SetFrameSize(SpiRegType *obj, uint16_t frameSize)
{
    uint32_t tmp = obj->TCR;

    tmp &= ~SPI_TCR_FRAME_SIZE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(frameSize)) << SPI_TCR_FRAME_SIZE_SHIFT)) & SPI_TCR_FRAME_SIZE_MASK);
    obj->TCR = tmp;
}

/*! \brief Get Frame Size
 *
 * \param[in] obj : base address for the SPI instance
 * \return : Return the frame size in number of bits equal to (FRAMESZ + 1)
 */
__attribute__((always_inline)) static inline uint16_t SpiReg_GetFrameSize(const SpiRegType *obj)
{
    uint16_t tRtn = 0;

    tRtn = ((obj->TCR & SPI_TCR_FRAME_SIZE_MASK) >> SPI_TCR_FRAME_SIZE_SHIFT);
    return tRtn;
}

/*! \brief Transmit Command config
 *
 * this function config the clock polarity, clock phase prescaler value and transfer mode ....
 *
 * \param[in] obj: base address for the SPI instance
 * \param[in] tcr: Transmit Command
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_SetTcr(SpiRegType *obj, uint32_t tcr)
{
    obj->TCR = tcr;
}

/*! \brief Get Transmit Command config
 *
 * this function config get the clock polarity, clock phase prescaler value and transfer mode ....
 *
 * \param[in] obj: base address for the SPI instance
 * \return: Transmit Command
 */
__attribute__((always_inline)) static inline uint32_t SpiReg_GetTcr(const SpiRegType *obj)
{
    return obj->TCR;
}

/*! \brief Circular FIFO Enable or disable
 *
 * this function enable the tx circular fifo mode
 *
 * \param[in] obj: base address for the SPI instance
 * \param[in] enable:
 *                     0b : disabled
 *                     1b : enabled
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_SetCircularFIFO(SpiRegType *obj, bool enable)
{
    uint32_t tRegValue = obj->CFGR0;

    if(enable == true)
    {
        obj->CFGR0 = ((1ul << SPI_CFGR0_CIRCULAR_FIFO_EN_SHIFT) | ((~SPI_CFGR0_CIRCULAR_FIFO_EN_MASK) & tRegValue));
    }
    else
    {
        obj->CFGR0 = ((0ul << SPI_CFGR0_CIRCULAR_FIFO_EN_SHIFT) | ((~SPI_CFGR0_CIRCULAR_FIFO_EN_MASK) & tRegValue));
    }
}

/*! \brief Output Configuration
 *
 * Configures if the output data is tristate between accesses (SPI_PCS is negated). If performing half-
 *       duplex transfers, this bit must be set.
 *
 * \param[in] obj: base address for the SPI instance
 * \param[in] enableTristate
 *               false : Output data retains last value when PCS is negated
 *               true  : Output data is tristate when PCS is negated
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_SetOutCfg(SpiRegType *obj, bool enableTristate)
{
    uint32_t tRegValue = obj->CFGR1;

    if(enableTristate == true)
    {
        obj->CFGR1 = ((1ul << SPI_CFGR1_OUT_CFG_SHIFT) | ((~SPI_CFGR1_OUT_CFG_MASK) & tRegValue));
    }
    else
    {
        obj->CFGR1 = ((0ul << SPI_CFGR1_OUT_CFG_SHIFT) | ((~SPI_CFGR1_OUT_CFG_MASK) & tRegValue));
    }
}

/*! \brief Pin Configuration
 *
 * Configures which pins are used for input and output data during serial transfers.
 *
 * \param[in] obj: base address for the SPI instance
 * \param[in] pin_cfg
 *               00b : SIN is used for input data and SOUT is used for output data
 *               01b : SIN is used for both input and output data, only half-duplex serial transfers are supported
 *               10b : SOUT is used for both input and output data, only half-duplex serial transfers are supported
 *               11b : SOUT is used for input data and SIN is used for output data
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_SetPinCfg(SpiRegType *obj, uint8_t pin_cfg)
{
    uint32_t tmp = obj->CFGR1;

    tmp &= ~SPI_CFGR1_PIN_CFG_MASK;
    tmp |= (((uint32_t)(((uint32_t)(pin_cfg)) << SPI_CFGR1_PIN_CFG_SHIFT)) & SPI_CFGR1_PIN_CFG_MASK);
    obj->CFGR1 = tmp;
}

/*! \brief Peripheral Chip Select Polarity
 *
 * Configures the polarity of each Peripheral Chip Select pin. Each PCS_POL bit position corresponds to a PCS[n] pin.
 *
 * \param[in] obj: base address for the SPI instance
 * \param[in] polarity
 *               0b: the PCS[n] pin is active low.
 *               1b: the PCS[n] pin is active high.
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_SetPcsPolarity(SpiRegType *obj, uint8_t polarity)
{
    uint32_t tmp = obj->CFGR1;

    tmp &= ~SPI_CFGR1_PCS_POL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(polarity)) << SPI_CFGR1_PCS_POL_SHIFT)) & SPI_CFGR1_PCS_POL_MASK);
    obj->CFGR1 = tmp;
}

/*! \brief Set master sck delay
 *
 * this function set the sck delay ticks
 *
 * \param[in] obj: base address for the SPI instance
 * \param[in] delaytick: delay tick
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_SetMstSckDelay(SpiRegType *obj, uint8_t delaytick)
{
    uint32_t tmp = obj->CFGR1;

    tmp &= ~SPI_CFGR1_MST_SCK_DLY_MASK;
    tmp |= (((uint32_t)(((uint32_t)(delaytick)) << SPI_CFGR1_MST_SCK_DLY_SHIFT)) & SPI_CFGR1_MST_SCK_DLY_MASK);
    obj->CFGR1 = tmp;
}

/*! \brief Master mode No Stall enable or disable
 *
 * In master mode, the SPI will stall transfers when the transmit FIFO is empty,
 *       ensuring that no transmit FIFO underrun can occur. Setting the No Stall bit will disable this functionality.
 *
 * \param[in] obj: base address for the SPI instance
 * \param[in] enable
 *            0b : Transfers will stall when the transmit FIFO is empty
 *            1b : Transfers will not stall, allowing transmit FIFO underruns to occur
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_SetNoStallMode(SpiRegType *obj, bool enable)
{
    uint32_t tRegValue = obj->CFGR1;

    if(enable == true)
    {
        obj->CFGR1 = ((1ul << SPI_CFGR1_NO_STALL_SHIFT) | ((~SPI_CFGR1_NO_STALL_MASK) & tRegValue));
    }
    else
    {
        obj->CFGR1 = ((0ul << SPI_CFGR1_NO_STALL_SHIFT) | ((~SPI_CFGR1_NO_STALL_MASK) & tRegValue));
    }
}

/*! \brief Automatic PCS enable or disable in slave mode
 *
 * The module normally requires the PCS to negate between frames. Setting this bit will cause the module to generate an internal PCS signal
 *       at the end of each transfer word when the Clock Phase bit TCR[CPHA] = 1.
 *
 * \param[in] obj: base address for the SPI instance
 * \param[in] enable: Automatic PCS in slave mode
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_SetAutoCS(SpiRegType *obj, bool enable)
{
    uint32_t tRegValue = obj->CFGR1;

    if(enable == true)
    {
        obj->CFGR1 = ((1ul << SPI_CFGR1_AUTO_PCS_SHIFT) | ((~SPI_CFGR1_AUTO_PCS_MASK) & tRegValue));
    }
    else
    {
        obj->CFGR1 = ((0ul << SPI_CFGR1_AUTO_PCS_SHIFT) | ((~SPI_CFGR1_AUTO_PCS_MASK) & tRegValue));
    }
}

/*! \brief Configures the module in master or slave mode
 *
 * this function set the node word mode in master or slave
 *
 * \param[in] obj: base address for the SPI instance
 * \param[in] ismaster:
 *            false:as slave
 *            true: as master
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_SetNodeMode(SpiRegType *obj, bool ismaster)
{
    uint32_t tRegValue = obj->CFGR1;

    if(ismaster == true)
    {
        obj->CFGR1 = ((1ul << SPI_CFGR1_MASTER_EN_SHIFT) | ((~SPI_CFGR1_MASTER_EN_MASK) & tRegValue));
    }
    else
    {
        obj->CFGR1 = ((0ul << SPI_CFGR1_MASTER_EN_SHIFT) | ((~SPI_CFGR1_MASTER_EN_MASK) & tRegValue));
    }
}

/*! \brief Get the module in master or slave mode
 *
 *
 *
 * \param[in] obj : base address for the SPI instance
 * \return bool
 *         false: is slave node
 *         true: is master node
 */
__attribute__((always_inline)) static inline bool SpiReg_GetNodeMasterState(const SpiRegType *obj)
{
    bool tRtn = false;

    if((obj->CFGR1 & SPI_CFGR1_MASTER_EN_MASK) != 0u)
    {
        tRtn = true;
    }

    return tRtn;
}

/*! \brief configures the delay from the last SCK edge to the PCS negation
 *
 * The delay is equal to (SCKPCS + 1) cycles of the SPI functional clock divided by the Prescaler Value TCR[PRESCALE] configuration.
 *       The minimum delay is 1 cycle.
 *
 * \param[in] obj: base address for the SPI instance
 * \param[in] delaytick: SCK-to-PCS Delay
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_SetDelaySckToPcs(SpiRegType *obj, uint8_t delaytick)
{
    uint32_t tmp = obj->CCR;

    tmp &= ~SPI_CCR_SCK_PCS_MASK;
    tmp |= (((uint32_t)(((uint32_t)(delaytick)) << SPI_CCR_SCK_PCS_SHIFT)) & SPI_CCR_SCK_PCS_MASK);
    obj->CCR = tmp;
}

/*! \brief configures the delay from the PCS assertion to the first SCK edge.
 *
 * The delay is equal to (PCSSCK + 1) cycles of the SPI functional clock divided by the Prescaler Value TCR[PRESCALE] configuration
 *        The minimum delay is 1 cycle.
 *
 * \param[in] obj: base address for the SPI instance
 * \param[in] delaytick: PCS-to-SCK Delay
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_SetDelayPcsToSck(SpiRegType *obj, uint8_t delaytick)
{
    uint32_t tmp = obj->CCR;

    tmp &= ~SPI_CCR_PCS_SCK_MASK;
    tmp |= (((uint32_t)(((uint32_t)(delaytick)) << SPI_CCR_PCS_SCK_SHIFT)) & SPI_CCR_PCS_SCK_MASK);
    obj->CCR = tmp;
}

/*! \brief Configures the delay from the PCS negation to the next PCS assertion.
 *
 * The delay is equal to (DBT + 2) cycles of the SPI functional clock divided by the Prescaler.
 *       The minimum delay is 2 cycles.
 *
 * \param[in] obj: base address for the SPI instance
 * \param[in] delaytick: Delay Between Transfers
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_SetDelayDBT(SpiRegType *obj, uint8_t delaytick)
{
    uint32_t tmp = obj->CCR;

    tmp &= ~SPI_CCR_DBT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(delaytick)) << SPI_CCR_DBT_SHIFT)) & SPI_CCR_DBT_MASK);
    obj->CCR = tmp;
}

/*! \brief the SCK Divider configures the divide ratio of the SCK pin
 *
 * The SCK period is equal to (SCKDIV+2) cycles of the SPI functional clock divided by the Prescaler Value TCR[PRESCALE] configuration.
 *       The minimum SCK period is 2 cycles.
 *
 * \param[in] obj: base address for the SPI instance
 * \param[in] sckdiv: SCK Divider
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_SetSckDiv(SpiRegType *obj, uint8_t sckdiv)
{
    uint32_t tmp = obj->CCR;

    tmp &= ~SPI_CCR_SCK_DIV_MASK;
    tmp |= (((uint32_t)(((uint32_t)(sckdiv)) << SPI_CCR_SCK_DIV_SHIFT)) & SPI_CCR_SCK_DIV_MASK);
    obj->CCR = tmp;
}

/*! \brief Transmit FIFO water mark
 *
 * The Transmit Data Flag is set whenever the number of words in the transmit FIFO is equal or less than TX_WATER
 *
 * \param[in] obj: base address for the SPI instance
 * \param[in] txWaterMark: Transmit FIFO water mark
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_SetTxFifoWaterMark(SpiRegType *obj, uint8_t txWaterMark)
{
    uint32_t tmp = obj->FCR;

    tmp &= ~SPI_FCR_TX_FIFO_WATER_MASK;
    tmp |= (((uint32_t)(((uint32_t)(txWaterMark)) << SPI_FCR_TX_FIFO_WATER_SHIFT)) & SPI_FCR_TX_FIFO_WATER_MASK);
    obj->FCR = tmp;
}

/*! \brief Get Tx FIFO water mark
 *
 * this function get the tx fifo water mark
 *
 * \param[in] obj: base address for the SPI instance
 * \return: return tx fifo water mark value
 */
__attribute__((always_inline)) static inline uint8_t SpiReg_GetTxFifoWaterMark(const SpiRegType *obj)
{
    uint8_t tTxWaterMark = 0;

    tTxWaterMark = ((obj->FCR & SPI_FCR_TX_FIFO_WATER_MASK) >> SPI_FCR_TX_FIFO_WATER_SHIFT);

    return tTxWaterMark;
}

/*! \brief Receive FIFO Watermark
 *
 * The Receive Data Flag is set whenever the number of words in the receive FIFO is greater than RX_WATER
 *
 * \param[in] obj: base address for the SPI instance
 * \param[in] rxWaterMark: Receive FIFO Watermark
 * \return: void
 */
__attribute__((always_inline)) static inline void SpiReg_SetRxFifoWaterMark(SpiRegType *obj, uint8_t rxWaterMark)
{
    uint32_t tmp = obj->FCR;

    tmp &= ~SPI_FCR_RX_FIFO_WATER_MASK;
    tmp |= (((uint32_t)(((uint32_t)(rxWaterMark)) << SPI_FCR_RX_FIFO_WATER_SHIFT)) & SPI_FCR_RX_FIFO_WATER_MASK);
    obj->FCR = tmp;
}

/*! \brief Get Rx FIFO water mark
 *
 * this function get the rx fifo water mark
 *
 * \param[in] obj: base address for the SPI instance
 * \return: return rx fifo water mark value
 */
__attribute__((always_inline)) static inline uint8_t SpiReg_GetRxFifoWaterMark(const SpiRegType *obj)
{
    uint8_t tRxWaterMark = 0;

    tRxWaterMark = ((obj->FCR & SPI_FCR_RX_FIFO_WATER_MASK) >> SPI_FCR_RX_FIFO_WATER_SHIFT);

    return tRxWaterMark;
}

/*! \brief Transmit FIFO Count
 *
 * Returns the number of words currently stored in the transmit FIFO.
 *
 * \param[in] obj: base address for the SPI instance
 * \return: uint8_t: return tx fifo counter value
 */
__attribute__((always_inline)) static inline uint8_t SpiReg_GetTxFifoCounter(const SpiRegType *obj)
{
    uint8_t tTxFifoCnt = 0;

    tTxFifoCnt = ((obj->FSR & SPI_FSR_TX_FIFO_CNT_MASK) >> SPI_FSR_TX_FIFO_CNT_SHIFT);

    return tTxFifoCnt;
}

/*! \brief Receive FIFO Count
 *
 * Returns the number of words currently stored in the receive FIFO.
 *
 * \param[in] obj: base address for the SPI instance
 * \return: return received rx fifo counter value
 */
__attribute__((always_inline)) static inline uint8_t SpiReg_GetRxFifoCounter(const SpiRegType *obj)
{
    uint8_t tRxFifoCnt = 0;

    tRxFifoCnt = ((obj->FSR & SPI_FSR_RX_FIFO_CNT_MASK) >> SPI_FSR_RX_FIFO_CNT_SHIFT);

    return tRxFifoCnt;
}

/*! \brief Set TX FIFO data
 *
 * this function is write data to hardware fifo
 *
 * \param[in] obj: base address for the SPI instance
 * \param[in] dat: TX FIFO data
 */
__attribute__((always_inline)) static inline void SpiReg_SetTxFifoData(SpiRegType *obj, uint32_t dat)
{
    obj->TDR = dat;
}

/*! \brief Get RX FIFO data
 *
 * this function read out the received data from hardware fifo
 *
 * \param[in] obj: base address for the SPI instance
 * \return: RX FIFO data
 */
__attribute__((always_inline)) static inline uint32_t SpiReg_GetRxFiFoData(const SpiRegType *obj)
{
    return obj->RDR;
}

/*! \brief RX FIFO Empty status
 *
 * this function get the current rx fifo status
 *
 * \param[in] obj: base address for the SPI instance
 * \return: RX FIFO Empty status
 *          false:RX FIFO is not empty
 *          true:RX FIFO is empty
 */
__attribute__((always_inline)) static inline bool SpiReg_GetRxFifoEmptyState(const SpiRegType *obj)
{
    bool tRtn = false;

    if(((obj->RSR & SPI_RSR_RX_FIFO_EMPTY_MASK) >> SPI_RSR_RX_FIFO_EMPTY_SHIFT) != 0u)
    {
        tRtn = true;
    }

    return tRtn;
}

/*! \brief Indicates that this is the first data word received after PCS assertion.
 *
 * this function get the current received data that is the first time to received
 *
 * \param[in] obj: base address for the SPI instance
 * \return: the first data word received
 *          false:The first word after PCS assertion is read by software or has no data after PCS assertion.
 *          true:receive the first word after PCS assertion
 */
__attribute__((always_inline)) static inline bool SpiReg_GetStartOfFrameIndicate(const SpiRegType *obj)
{
    bool tRtn = false;

    if(((obj->RSR & SPI_RSR_SOF_MASK) >> SPI_RSR_SOF_SHIFT) != 0u)
    {
        tRtn = true;
    }

    return tRtn;
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _SPI_REG_H_ */
