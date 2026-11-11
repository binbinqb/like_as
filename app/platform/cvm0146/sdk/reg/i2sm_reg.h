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

#ifndef _I2SM_REG_H_
#define _I2SM_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the I2SM Registers
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * the defines
 ******************************************************************************/

/* IER Bit Fields */
#define I2SM_IER_EN_MASK        (0x01u)
#define I2SM_IER_EN_SHIFT       (0u)
#define I2SM_IER_EN_WIDTH       (1u)

/* ITER Bit Fields */
#define I2SM_ITER_TXEN_MASK     (0x01u)
#define I2SM_ITER_TXEN_SHIFT    (0u)
#define I2SM_ITER_TXEN_WIDTH    (1u)

/* CER Bit Fields */
#define I2SM_CER_CLKEN_MASK     (0x01u)
#define I2SM_CER_CLKEN_SHIFT    (0u)
#define I2SM_CER_CLKEN_WIDTH    (1u)

/* CCR Bit Fields */
#define I2SM_CCR_WSS_MASK       (0x18u)
#define I2SM_CCR_WSS_SHIFT      (3u)
#define I2SM_CCR_WSS_WIDTH      (2u)
#define I2SM_CCR_SCLKG_MASK     (0x07u)
#define I2SM_CCR_SCLKG_SHIFT    (0u)
#define I2SM_CCR_SCLKG_WIDTH    (3u)

/* TXFFR Bit Fields */
#define I2SM_TXFFR_TXFFR_MASK   (0x01u)
#define I2SM_TXFFR_TXFFR_SHIFT  (0u)
#define I2SM_TXFFR_TXFFR_WIDTH  (1u)

/* LTHR0 Bit Fields */
#define I2SM_LTHR0_LTHR0_MASK   (0xFFFFFFFFu)
#define I2SM_LTHR0_LTHR0_SHIFT  (0u)
#define I2SM_LTHR0_LTHR0_WIDTH  (32u)

/* RTHR0 Bit Fields */
#define I2SM_RTHR0_RTHR0_MASK   (0xFFFFFFFFu)
#define I2SM_RTHR0_RTHR0_SHIFT  (0u)
#define I2SM_RTHR0_RTHR0_WIDTH  (32u)

/* TER0 Bit Fields */
#define I2SM_TER0_TXCHEN0_MASK  (0x01u)
#define I2SM_TER0_TXCHEN0_SHIFT (0u)
#define I2SM_TER0_TXCHEN0_WIDTH (1u)

/* TCR0 Bit Fields */
#define I2SM_TCR0_TX_WLEN_MASK  (0x07u)
#define I2SM_TCR0_TX_WLEN_SHIFT (0u)
#define I2SM_TCR0_TX_WLEN_WIDTH (3u)

/* ISR0 Bit Fields */
#define I2SM_ISR0_TXFO_MASK     (0x20u)
#define I2SM_ISR0_TXFO_SHIFT    (5u)
#define I2SM_ISR0_TXFO_WIDTH    (1u)
#define I2SM_ISR0_TXFE_MASK     (0x10u)
#define I2SM_ISR0_TXFE_SHIFT    (4u)
#define I2SM_ISR0_TXFE_WIDTH    (1u)

/* IMR0 Bit Fields */
#define I2SM_IMR0_TXFOM_MASK    (0x20u)
#define I2SM_IMR0_TXFOM_SHIFT   (5u)
#define I2SM_IMR0_TXFOM_WIDTH   (1u)
#define I2SM_IMR0_TXFEM_MASK    (0x10u)
#define I2SM_IMR0_TXFEM_SHIFT   (4u)
#define I2SM_IMR0_TXFEM_WIDTH   (1u)

/* TOR0 Bit Fields */
#define I2SM_TOR0_TXCHO_MASK    (0x01u)
#define I2SM_TOR0_TXCHO_SHIFT   (0u)
#define I2SM_TOR0_TXCHO_WIDTH   (1u)

/* TFCR0 Bit Fields */
#define I2SM_TFCR0_TFCR0_MASK   (0x0Fu)
#define I2SM_TFCR0_TFCR0_SHIFT  (0u)
#define I2SM_TFCR0_TFCR0_WIDTH  (4u)

/* TFF0 Bit Fields */
#define I2SM_TFF0_TXCHFR0_MASK  (0x01u)
#define I2SM_TFF0_TXCHFR0_SHIFT (0u)
#define I2SM_TFF0_TXCHFR0_WIDTH (1u)

/* TXDMA Bit Fields */
#define I2SM_TXDMA_TXDMA_MASK   (0xFFFFFFFFu)
#define I2SM_TXDMA_TXDMA_SHIFT  (0u)
#define I2SM_TXDMA_TXDMA_WIDTH  (32u)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief The definition of I2SM registers
 */
typedef struct _I2smRegType_
{
    volatile uint32_t IER;           /*!< module enable, offset: 0x00 */
    uint32_t          RESERVED0[1];  /*!< Reserverd block, offset: 0x04 */
    volatile uint32_t ITER;          /*!< transmit block enable, offset: 0x08 */
    volatile uint32_t CER;           /*!< clock enable, offset: 0x0C */
    volatile uint32_t CCR;           /*!< clock configuration register, offset: 0x10 */
    uint32_t          RESERVED1[1];  /*!< Reserverd block, offset: 0x14 */
    volatile uint32_t TXFFR;         /*!< TX FIFO reset, offset: 0x18 */
    uint32_t          RESERVED2[1];  /*!< Reserverd block, offset: 0x1C */
    volatile uint32_t LTHR0;         /*!< left stereo data, offset: 0x20 */
    volatile uint32_t RTHR0;         /*!< right stereo data, offset: 0x24 */
    uint32_t          RESERVED3[1];  /*!< Reserverd block, offset: 0x28 */
    volatile uint32_t TER0;          /*!< transmit channel enable, offset: 0x2C */
    uint32_t          RESERVED4[1];  /*!< Reserverd block, offset: 0x30 */
    volatile uint32_t TCR0;          /*!< transmit configuration, offset: 0x34 */
    volatile uint32_t ISR0;          /*!< interrupt status, offset: 0x38 */
    volatile uint32_t IMR0;          /*!< interrupt mask, offset: 0x3C */
    uint32_t          RESERVED5[1];  /*!< Reserverd block, offset: 0x40 */
    volatile uint32_t TOR0;          /*!< transmit overrun status, offset: 0x44 */
    uint32_t          RESERVED6[1];  /*!< Reserverd block, offset: 0x48 */
    volatile uint32_t TFCR0;         /*!< TX FIFO configuration, offset: 0x4C */
    uint32_t          RESERVED7[1];  /*!< Reserverd block, offset: 0x50 */
    volatile uint32_t TFF0;          /*!< TX FIFO flush, offset: 0x54 */
    uint32_t          RESERVED8[92]; /*!< Reserverd block, offset: 0x58 */
    volatile uint32_t TXDMA;         /*!< Transmit DMA register, offset: 0x1C8 */
} I2smRegType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Gets the IP enable
 *
 * This function gets the current IP enable.
 *
 * \param[in] obj : pointer to I2SM register instance
 * \return IP enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t I2smReg_GetIerEn(const I2smRegType *obj)
{
    return ((obj->IER & I2SM_IER_EN_MASK) >> I2SM_IER_EN_SHIFT);
}

/*! \brief Sets the IP enable
 *
 * This function sets the IP enable.
 *
 * \param[in] obj : pointer to I2SM register instance
 * \param[in] value : the value of IP enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void I2smReg_SetIerEn(I2smRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->IER;

    tmp &= ~I2SM_IER_EN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << I2SM_IER_EN_SHIFT)) & I2SM_IER_EN_MASK);
    obj->IER = tmp;
}

/*! \brief Gets the transmit block enable
 *
 * This function gets the current transmit block enable.
 * It enables or disables the transmit.
 *
 * \param[in] obj : pointer to I2SM register instance
 * \return transmit block enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t I2smReg_GetIterTxEn(const I2smRegType *obj)
{
    return ((obj->ITER & I2SM_ITER_TXEN_MASK) >> I2SM_ITER_TXEN_SHIFT);
}

/*! \brief Sets the transmit block enable
 *
 * This function sets the transmit block enable.
 * It enables or disables the transmit.
 *
 * \param[in] obj : pointer to I2SM register instance
 * \param[in] value : the value of transmit block enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void I2smReg_SetIterTxEn(I2smRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->ITER;

    tmp &= ~I2SM_ITER_TXEN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << I2SM_ITER_TXEN_SHIFT)) & I2SM_ITER_TXEN_MASK);
    obj->ITER = tmp;
}

/*! \brief Gets the master clock generation enable
 *
 * This function gets the current master clock generation enable.
 *
 * \param[in] obj : pointer to I2SM register instance
 * \return master clock generation enable
 */
__attribute__((always_inline)) static inline uint8_t I2smReg_GetCerClkEn(const I2smRegType *obj)
{
    return ((obj->CER & I2SM_CER_CLKEN_MASK) >> I2SM_CER_CLKEN_SHIFT);
}

/*! \brief Sets the master clock generation enable
 *
 * This function sets the master clock generation enable.
 *
 * \param[in] obj : pointer to I2SM register instance
 * \param[in] value : the value of master clock generation enable
 */
__attribute__((always_inline)) static inline void I2smReg_SetCerClkEn(I2smRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CER;

    tmp &= ~I2SM_CER_CLKEN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << I2SM_CER_CLKEN_SHIFT)) & I2SM_CER_CLKEN_MASK);
    obj->CER = tmp;
}

/*! \brief Gets the left/right channel period
 *
 * This function gets the current left/right channel period.
 * It is used to program the number of sclk cycles for which ws_out stays in the left or right sample mode.
 * The I2S Clock Generation block must be disabled (CER[0] = 0) prior to any changes in this value.
 *
 * \param[in] obj : pointer to I2SM register instance
 * \return left/right channel period
 *         - 0h : 16 sclk cycles
 *         - 1h : 24 sclk cycles
 *         - 2h : 32 sclk cycles
 */
__attribute__((always_inline)) static inline uint8_t I2smReg_GetCcrWss(const I2smRegType *obj)
{
    return ((obj->CCR & I2SM_CCR_WSS_MASK) >> I2SM_CCR_WSS_SHIFT);
}

/*! \brief Sets the left/right channel period
 *
 * This function sets the left/right channel period.
 * It is used to program the number of sclk cycles for which ws_out stays in the left or right sample mode.
 * The I2S Clock Generation block must be disabled (CER[0] = 0) prior to any changes in this value.
 *
 * \param[in] obj : pointer to I2SM register instance
 * \param[in] value : the value of left/right channel period
 *                    - 0h : 16 sclk cycles
 *                    - 1h : 24 sclk cycles
 *                    - 2h : 32 sclk cycles
 */
__attribute__((always_inline)) static inline void I2smReg_SetCcrWss(I2smRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CCR;

    tmp &= ~I2SM_CCR_WSS_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << I2SM_CCR_WSS_SHIFT)) & I2SM_CCR_WSS_MASK);
    obj->CCR = tmp;
}

/*! \brief Gets the clock gate period
 *
 * This function gets the current clock gate period.
 * It is used to program the gating of sclk.
 * The programmed gating value must be less than or equal to the largest configured/ programmed audio resolution
 * to prevent the truncating of RX/TX data.
 * The I2S Clock Generation block must be disabled (CER[0] = 0) before making any changes in this value.
 *
 * \param[in] obj : pointer to I2SM register instance
 * \return clock gate period
 *         - 0h : disabled
 *         - 1h : gating after 12 sclk cycles
 *         - 2h : gating after 16 sclk cycles
 *         - 3h : gating after 20 sclk cycles
 *         - 4h : gating after 24 sclk cycles
 */
__attribute__((always_inline)) static inline uint8_t I2smReg_GetCcrSclkg(const I2smRegType *obj)
{
    return ((obj->CCR & I2SM_CCR_SCLKG_MASK) >> I2SM_CCR_SCLKG_SHIFT);
}

/*! \brief Sets the clock gate period
 *
 * This function sets the clock gate period.
 * It is used to program the gating of sclk.
 * The programmed gating value must be less than or equal to the largest configured/ programmed audio resolution
 * to prevent the truncating of RX/TX data.
 * The I2S Clock Generation block must be disabled (CER[0] = 0) before making any changes in this value.
 *
 * \param[in] obj : pointer to I2SM register instance
 * \param[in] value : the value of clock gate period
 *                    - 0h : disabled
 *                    - 1h : gating after 12 sclk cycles
 *                    - 2h : gating after 16 sclk cycles
 *                    - 3h : gating after 20 sclk cycles
 *                    - 4h : gating after 24 sclk cycles
 */
__attribute__((always_inline)) static inline void I2smReg_SetCcrSclkg(I2smRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CCR;

    tmp &= ~I2SM_CCR_SCLKG_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << I2SM_CCR_SCLKG_SHIFT)) & I2SM_CCR_SCLKG_MASK);
    obj->CCR = tmp;
}

/*! \brief Sets the TX FIFO reset
 *
 * This function sets the TX FIFO reset.
 * Writing a 1 to this register flushes all the TX FIFOs (this is a self clearing bit).
 * The Transmitter Block must be disabled prior to writing this bit.
 *
 * \param[in] obj : pointer to I2SM register instance
 * \param[in] value : the value of TX FIFO reset
 *                    - 0b : does not flush the TX FIFO
 *                    - 1b : flush the TX FIFO
 */
__attribute__((always_inline)) static inline void I2smReg_SetTxffrTxFFR(I2smRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->TXFFR;

    tmp &= ~I2SM_TXFFR_TXFFR_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << I2SM_TXFFR_TXFFR_SHIFT)) & I2SM_TXFFR_TXFFR_MASK);
    obj->TXFFR = tmp;
}

/*! \brief Sets the left stereo data
 *
 * This function sets the left stereo data.
 * The left stereo data to be transmitted serially through the transmit channel output (sdox) is written through this register.
 * Writing is a two-stage process:
 * 1. A write to this register passes the left stereo sample to the transmitter.
 * 2. This MUST be followed by writing the right stereo sample to the RTHRx register
 *
 * \param[in] obj : pointer to I2SM register instance
 * \param[in] value : the value of left stereo data
 */
__attribute__((always_inline)) static inline void I2smReg_SetLthr0Lthr0(I2smRegType *obj, uint32_t value)
{
    uint32_t tmp = obj->LTHR0;

    tmp &= ~I2SM_LTHR0_LTHR0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << I2SM_LTHR0_LTHR0_SHIFT)) & I2SM_LTHR0_LTHR0_MASK);
    obj->LTHR0 = tmp;
}

/*! \brief Sets the right stereo data
 *
 * This function sets the right stereo data.
 * The right stereo data to be transmitted serially through the
 * transmit channel output (sdox) is written through this register.
 * Writing is a two-stage process:
 * 1. A left stereo sample MUST be written to the LTHRx register.
 * 2. A write to this register passes the right stereo sample to the transmitte
 *
 * \param[in] obj : pointer to I2SM register instance
 * \param[in] value : the value of right stereo data
 */
__attribute__((always_inline)) static inline void I2smReg_SetRthr0Rthr0(I2smRegType *obj, uint32_t value)
{
    uint32_t tmp = obj->RTHR0;

    tmp &= ~I2SM_RTHR0_RTHR0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << I2SM_RTHR0_RTHR0_SHIFT)) & I2SM_RTHR0_RTHR0_MASK);
    obj->RTHR0 = tmp;
}

/*! \brief Gets the transmit channel enable
 *
 * This function gets the current transmit channel enable.
 *
 * \param[in] obj : pointer to I2SM register instance
 * \return transmit channel enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t I2smReg_GetTer0TxChEn0(const I2smRegType *obj)
{
    return ((obj->TER0 & I2SM_TER0_TXCHEN0_MASK) >> I2SM_TER0_TXCHEN0_SHIFT);
}

/*! \brief Sets the transmit channel enable
 *
 * This function sets the transmit channel enable.
 *
 * \param[in] obj : pointer to I2SM register instance
 * \param[in] value : the value of transmit channel enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void I2smReg_SetTer0TxChEn0(I2smRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->TER0;

    tmp &= ~I2SM_TER0_TXCHEN0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << I2SM_TER0_TXCHEN0_SHIFT)) & I2SM_TER0_TXCHEN0_MASK);
    obj->TER0 = tmp;
}

/*! \brief Gets the transmit data width
 *
 * This function gets the current transmit data width.
 * These bits are used to program the data resolution of the transmitter and ensures the MSB of the data is transmitted first.
 *
 * \param[in] obj : pointer to I2SM register instance
 * \return transmit data width
 *         - 0h : ignore
 *         - 1h : 12bit data
 *         - 2h : 16bit data
 *         - 3h : 20bit data
 *         - 4h : 24bit data
 *         - 5h : 32bit data
 */
__attribute__((always_inline)) static inline uint8_t I2smReg_GetTcr0TxWLen(const I2smRegType *obj)
{
    return ((obj->TCR0 & I2SM_TCR0_TX_WLEN_MASK) >> I2SM_TCR0_TX_WLEN_SHIFT);
}

/*! \brief Sets the transmit data width
 *
 * This function sets the transmit data width.
 * These bits are used to program the data resolution of the transmitter and ensures the MSB of the data is transmitted first.
 *
 * \param[in] obj : pointer to I2SM register instance
 * \param[in] value : the value of transmit data width
 *                    - 0h : ignore
 *                    - 1h : 12bit data
 *                    - 2h : 16bit data
 *                    - 3h : 20bit data
 *                    - 4h : 24bit data
 *                    - 5h : 32bit data
 */
__attribute__((always_inline)) static inline void I2smReg_SetTcr0TxWLen(I2smRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->TCR0;

    tmp &= ~I2SM_TCR0_TX_WLEN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << I2SM_TCR0_TX_WLEN_SHIFT)) & I2SM_TCR0_TX_WLEN_MASK);
    obj->TCR0 = tmp;
}

/*! \brief Gets the TX FIFO write status
 *
 * This function gets the current TX FIFO write status.
 *
 * \param[in] obj : pointer to I2SM register instance
 * \return TX FIFO write status
 *         - 0b : TX FIFO write valid
 *         - 1b : TX FIFO write overrun
 */
__attribute__((always_inline)) static inline uint8_t I2smReg_GetIsr0TxFO(const I2smRegType *obj)
{
    return ((obj->ISR0 & I2SM_ISR0_TXFO_MASK) >> I2SM_ISR0_TXFO_SHIFT);
}

/*! \brief Gets the TX FIFO reached trigger level
 *
 * This function gets the current TX FIFO reached trigger level.
 * This bit specifies whether the TX FIFO trigger level has reached or not. TX FIFO is empty.
 *
 * \param[in] obj : pointer to I2SM register instance
 * \return TX FIFO reached trigger level
 *         - 0b : TX FIFO trigger level is reached
 *         - 1b : TX FIFO trigger level is not reached
 */
__attribute__((always_inline)) static inline uint8_t I2smReg_GetIsr0TxFE(const I2smRegType *obj)
{
    return ((obj->ISR0 & I2SM_ISR0_TXFE_MASK) >> I2SM_ISR0_TXFE_SHIFT);
}

/*! \brief Gets the TX FIFO overrun interrupt mask
 *
 * This function gets the current TX FIFO overrun interrupt mask.
 *
 * \param[in] obj : pointer to I2SM register instance
 * \return TX FIFO overrun interrupt mask
 *         - 0b : unmasks TX FIFO overrun interrupt
 *         - 1b : mask TX FIFO overrun interrupt
 */
__attribute__((always_inline)) static inline uint8_t I2smReg_GetImr0TxFom(const I2smRegType *obj)
{
    return ((obj->IMR0 & I2SM_IMR0_TXFOM_MASK) >> I2SM_IMR0_TXFOM_SHIFT);
}

/*! \brief Sets the TX FIFO overrun interrupt mask
 *
 * This function sets the TX FIFO overrun interrupt mask.
 *
 * \param[in] obj : pointer to I2SM register instance
 * \param[in] value : the value of TX FIFO overrun interrupt mask
 *                    - 0b : unmasks TX FIFO overrun interrupt
 *                    - 1b : mask TX FIFO overrun interrupt
 */
__attribute__((always_inline)) static inline void I2smReg_SetImr0TxFom(I2smRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->IMR0;

    tmp &= ~I2SM_IMR0_TXFOM_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << I2SM_IMR0_TXFOM_SHIFT)) & I2SM_IMR0_TXFOM_MASK);
    obj->IMR0 = tmp;
}

/*! \brief Gets the TX FIFO empty interrupt mask
 *
 * This function gets the current TX FIFO empty interrupt mask.
 *
 * \param[in] obj : pointer to I2SM register instance
 * \return TX FIFO empty interrupt mask
 *         - 0b : unmasks TX FIFO empty interrupt
 *         - 1b : mask TX FIFO empty interrupt
 */
__attribute__((always_inline)) static inline uint8_t I2smReg_GetImr0TxFem(const I2smRegType *obj)
{
    return ((obj->IMR0 & I2SM_IMR0_TXFEM_MASK) >> I2SM_IMR0_TXFEM_SHIFT);
}

/*! \brief Sets the TX FIFO empty interrupt mask
 *
 * This function sets the TX FIFO empty interrupt mask.
 *
 * \param[in] obj : pointer to I2SM register instance
 * \param[in] value : the value of TX FIFO empty interrupt mask
 *                    - 0b : unmasks TX FIFO empty interrupt
 *                    - 1b : mask TX FIFO empty interrupt
 */
__attribute__((always_inline)) static inline void I2smReg_SetImr0TxFem(I2smRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->IMR0;

    tmp &= ~I2SM_IMR0_TXFEM_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << I2SM_IMR0_TXFEM_SHIFT)) & I2SM_IMR0_TXFEM_MASK);
    obj->IMR0 = tmp;
}

/*! \brief Gets the TX FIFO write overrun
 *
 * This function gets the current TX FIFO write overrun.
 *
 * \param[in] obj : pointer to I2SM register instance
 * \return TX FIFO write overrun
 *         - 0b : TX FIFO write valid
 *         - 1b : TX FIFO write overrun
 */
__attribute__((always_inline)) static inline uint8_t I2smReg_GetTor0TxChO(const I2smRegType *obj)
{
    return ((obj->TOR0 & I2SM_TOR0_TXCHO_MASK) >> I2SM_TOR0_TXCHO_SHIFT);
}

/*! \brief Sets the TX FIFO write overrun
 *
 * This function sets the TX FIFO write overrun.
 *
 * \param[in] obj : pointer to I2SM register instance
 * \param[in] value : the value of TX FIFO write overrun
 *                    - 0b : TX FIFO write valid
 *                    - 1b : TX FIFO write overrun
 */
__attribute__((always_inline)) static inline void I2smReg_SetTor0TxChO(I2smRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->TOR0;

    tmp &= ~I2SM_TOR0_TXCHO_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << I2SM_TOR0_TXCHO_SHIFT)) & I2SM_TOR0_TXCHO_MASK);
    obj->TOR0 = tmp;
}

/*! \brief Gets the FIFO level trigger
 *
 * This function gets the current FIFO level trigger.
 * When the FIFO level reaches the register, interrupt triggers.
 * These bits program the trigger level in the RX FIFO at which the Received Data Available interrupt is generated.
 * Trigger Level = Programmed Value + 1
 * If an illegal value is programmed, these bits saturate to (I2S_RX_FIFO_x - 1).
 * The channel must be disabled prior to any changes in this value (that is, RER0[0] = 0).
 *
 * \param[in] obj : pointer to I2SM register instance
 * \return FIFO level trigger
 *         - 0h : 1
 *         - 1h : 2
 *         - 2h : 3
 *         - 3h : 4
 *         - 4h : 5
 *         - 5h : 6
 *         - 6h : 7
 *         - 7h : 8
 *         -  ...
 *         - Fh : 16
 */
__attribute__((always_inline)) static inline uint8_t I2smReg_GetTfcr0Tfcr0(const I2smRegType *obj)
{
    return ((obj->TFCR0 & I2SM_TFCR0_TFCR0_MASK) >> I2SM_TFCR0_TFCR0_SHIFT);
}

/*! \brief Sets the FIFO level trigger
 *
 * This function sets the FIFO level trigger.
 * When the FIFO level reaches the register, interrupt triggers.
 * These bits program the trigger level in the RX FIFO at which the Received Data Available interrupt is generated.
 * Trigger Level = Programmed Value + 1
 * If an illegal value is programmed, these bits saturate to (I2S_RX_FIFO_x - 1).
 * The channel must be disabled prior to any changes in this value (that is, RER0[0] = 0).
 *
 * \param[in] obj : pointer to I2SM register instance
 * \param[in] value : the value of FIFO level trigger
 *                    - 0h : 1
 *                    - 1h : 2
 *                    - 2h : 3
 *                    - 3h : 4
 *                    - 4h : 5
 *                    - 5h : 6
 *                    - 6h : 7
 *                    - 7h : 8
 *                    -  ...
 *                    - Fh : 16
 */
__attribute__((always_inline)) static inline void I2smReg_SetTfcr0Tfcr0(I2smRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->TFCR0;

    tmp &= ~I2SM_TFCR0_TFCR0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << I2SM_TFCR0_TFCR0_SHIFT)) & I2SM_TFCR0_TFCR0_MASK);
    obj->TFCR0 = tmp;
}

/*! \brief Sets the TX FIFO flush
 *
 * This function sets the TX FIFO flush.
 * Writing a 1 to this register flushes channel's TX FIFO (This is a self clearing bit.).
 * The TX channel or block must be disabled prior to writing to this bit.
 *
 * \param[in] obj : pointer to I2SM register instance
 * \param[in] value : the value of TX FIFO flush
 *                    - 0b : Does not flush an individual TX FIFO
 *                    - 1b : flush an individual TX FIFO
 */
__attribute__((always_inline)) static inline void I2smReg_SetTff0TxChfr0(I2smRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->TFF0;

    tmp &= ~I2SM_TFF0_TXCHFR0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << I2SM_TFF0_TXCHFR0_SHIFT)) & I2SM_TFF0_TXCHFR0_MASK);
    obj->TFF0 = tmp;
}

/*! \brief Sets the Transmitter Block DMA Register
 *
 * This function sets the Transmitter Block DMA Register.
 * The register bits can be used to cycle repeatedly through the enabled Transmit channels (from lowest numbered to
 * highest) to allow writing of stereo data pairs
 *
 * \param[in] obj : pointer to I2SM register instance
 * \param[in] value : the value of Transmitter Block DMA Register
 */
__attribute__((always_inline)) static inline void I2smReg_SetTxDmaTxDma(I2smRegType *obj, uint32_t value)
{
    uint32_t tmp = obj->TXDMA;

    tmp &= ~I2SM_TXDMA_TXDMA_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << I2SM_TXDMA_TXDMA_SHIFT)) & I2SM_TXDMA_TXDMA_MASK);
    obj->TXDMA = tmp;
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _I2SM_REG_H_ */
