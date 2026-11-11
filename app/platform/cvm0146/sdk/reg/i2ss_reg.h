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

#ifndef _I2SS_REG_H_
#define _I2SS_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the I2SS Registers
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
#define I2SS_IER_EN_MASK        (0x01u)
#define I2SS_IER_EN_SHIFT       (0u)
#define I2SS_IER_EN_WIDTH       (1u)

/* IRER Bit Fields */
#define I2SS_IRER_RXEN_MASK     (0x01u)
#define I2SS_IRER_RXEN_SHIFT    (0u)
#define I2SS_IRER_RXEN_WIDTH    (1u)

/* RXFFR Bit Fields */
#define I2SS_RXFFR_RXFFR_MASK   (0x01u)
#define I2SS_RXFFR_RXFFR_SHIFT  (0u)
#define I2SS_RXFFR_RXFFR_WIDTH  (1u)

/* LRBR0 Bit Fields */
#define I2SS_LRBR0_LRBR0_MASK   (0x01u)
#define I2SS_LRBR0_LRBR0_SHIFT  (0u)
#define I2SS_LRBR0_LRBR0_WIDTH  (1u)

/* RRBR0 Bit Fields */
#define I2SS_RRBR0_RRBR0_MASK   (0x01u)
#define I2SS_RRBR0_RRBR0_SHIFT  (0u)
#define I2SS_RRBR0_RRBR0_WIDTH  (1u)

/* RER0 Bit Fields */
#define I2SS_RER0_CH0_MASK      (0x01u)
#define I2SS_RER0_CH0_SHIFT     (0u)
#define I2SS_RER0_CH0_WIDTH     (1u)

/* RCR0 Bit Fields */
#define I2SS_RCR0_RX_WLEN_MASK  (0x07u)
#define I2SS_RCR0_RX_WLEN_SHIFT (0u)
#define I2SS_RCR0_RX_WLEN_WIDTH (3u)

/* ISR0 Bit Fields */
#define I2SS_ISR0_RXFO_MASK     (0x02u)
#define I2SS_ISR0_RXFO_SHIFT    (1u)
#define I2SS_ISR0_RXFO_WIDTH    (1u)
#define I2SS_ISR0_RXDA_MASK     (0x01u)
#define I2SS_ISR0_RXDA_SHIFT    (0u)
#define I2SS_ISR0_RXDA_WIDTH    (1u)

/* IMR0 Bit Fields */
#define I2SS_IMR0_RXFOM_MASK    (0x02u)
#define I2SS_IMR0_RXFOM_SHIFT   (1u)
#define I2SS_IMR0_RXFOM_WIDTH   (1u)
#define I2SS_IMR0_RXDAM_MASK    (0x01u)
#define I2SS_IMR0_RXDAM_SHIFT   (0u)
#define I2SS_IMR0_RXDAM_WIDTH   (1u)

/* ROR0 Bit Fields */
#define I2SS_ROR0_RXCHO_MASK    (0x01u)
#define I2SS_ROR0_RXCHO_SHIFT   (0u)
#define I2SS_ROR0_RXCHO_WIDTH   (1u)

/* RFCR0 Bit Fields */
#define I2SS_RFCR0_RXCHDT_MASK  (0x0Fu)
#define I2SS_RFCR0_RXCHDT_SHIFT (0u)
#define I2SS_RFCR0_RXCHDT_WIDTH (4u)

/* RFF0 Bit Fields */
#define I2SS_RFF0_RXCHFR0_MASK  (0x01u)
#define I2SS_RFF0_RXCHFR0_SHIFT (0u)
#define I2SS_RFF0_RXCHFR0_WIDTH (1u)

/* RXDMA Bit Fields */
#define I2SS_RXDMA_RXDMA_MASK   (0xFFFFFFFFu)
#define I2SS_RXDMA_RXDMA_SHIFT  (0u)
#define I2SS_RXDMA_RXDMA_WIDTH  (32u)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief The definition of I2SS registers
 */
typedef struct _I2ssRegType_
{
    volatile uint32_t       IER;           /*!< module enable, offset: 0x00 */
    volatile uint32_t       IRER;          /*!< receiver block enable, offset: 0x04 */
    uint32_t                RESERVED0[3];  /*!< Reserverd block, offset: 0x08 */
    volatile uint32_t       RXFFR;         /*!< RX FIFO reset, offset: 0x14 */
    uint32_t                RESERVED1[2];  /*!< Reserverd block, offset: 0x18 */
    const volatile uint32_t LRBR0;         /*!< left receive buffer, offset: 0x20 */
    const volatile uint32_t RRBR0;         /*!< right receive buffer, offset: 0x24 */
    volatile uint32_t       RER0;          /*!< receive channel0 enable, offset: 0x28 */
    uint32_t                RESERVED2[1];  /*!< Reserverd block, offset: 0x2C */
    volatile uint32_t       RCR0;          /*!< receive configuration, offset: 0x30 */
    uint32_t                RESERVED3[1];  /*!< Reserverd block, offset: 0x34 */
    const volatile uint32_t ISR0;          /*!< interrupt status, offset: 0x38 */
    volatile uint32_t       IMR0;          /*!< interrupt mask, offset: 0x3C */
    volatile uint32_t       ROR0;          /*!< receive overrun, offset: 0x40 */
    uint32_t                RESERVED4[1];  /*!< Reserverd block, offset: 0x44 */
    volatile uint32_t       RFCR0;         /*!< RX FIFO configuration, offset: 0x48 */
    uint32_t                RESERVED5[1];  /*!< Reserverd block, offset: 0x4C */
    volatile uint32_t       RFF0;          /*!< RX FIFO flush, offset: 0x50 */
    uint32_t                RESERVED6[91]; /*!< Reserverd block, offset: 0x54 */
    const volatile uint32_t RXDMA;         /*!< Receive DMA register, offset: 0x1C0 */
} I2ssRegType;

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
 * \param[in] obj : pointer to I2SS register instance
 * \return IP enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t I2ssReg_GetIerEn(const I2ssRegType *obj)
{
    return ((obj->IER & I2SS_IER_EN_MASK) >> I2SS_IER_EN_SHIFT);
}

/*! \brief Sets the IP enable
 *
 * This function sets the IP enable.
 *
 * \param[in] obj : pointer to I2SS register instance
 * \param[in] value : the value of IP enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void I2ssReg_SetIerEn(I2ssRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->IER;

    tmp &= ~I2SS_IER_EN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << I2SS_IER_EN_SHIFT)) & I2SS_IER_EN_MASK);
    obj->IER = tmp;
}

/*! \brief Gets the receiver block enable
 *
 * This function gets the current receiver block enable.
 * It enables or disables the receiver.
 *
 * \param[in] obj : pointer to I2SS register instance
 * \return receiver block enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t I2ssReg_GetIrerRxEn(const I2ssRegType *obj)
{
    return ((obj->IRER & I2SS_IRER_RXEN_MASK) >> I2SS_IRER_RXEN_SHIFT);
}

/*! \brief Sets the receiver block enable
 *
 * This function sets the receiver block enable.
 * It enables or disables the receiver.
 *
 * \param[in] obj : pointer to I2SS register instance
 * \param[in] value : the value of receiver block enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void I2ssReg_SetIrerRxEn(I2ssRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->IRER;

    tmp &= ~I2SS_IRER_RXEN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << I2SS_IRER_RXEN_SHIFT)) & I2SS_IRER_RXEN_MASK);
    obj->IRER = tmp;
}

/*! \brief Sets the RX FIFO reset
 *
 * This function sets the RX FIFO reset.
 * Writing a 1 to this register flushes all the FIFOs (this is a self clearing bit).
 * The Transmitter Block must be disabled prior to writing this bit.
 *
 * \param[in] obj : pointer to I2SS register instance
 * \param[in] value : the value of RX FIFO reset
 *                    - 0b : does not flush the FIFO
 *                    - 1b : flush the FIFO
 */
__attribute__((always_inline)) static inline void I2ssReg_SetRxffrRxffr(I2ssRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->RXFFR;

    tmp &= ~I2SS_RXFFR_RXFFR_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << I2SS_RXFFR_RXFFR_SHIFT)) & I2SS_RXFFR_RXFFR_MASK);
    obj->RXFFR = tmp;
}

/*! \brief Gets the left stereo data
 *
 * This function gets the current left stereo data.
 * The left stereo data received serially from the receive channel input
 *
 * \param[in] obj : pointer to I2SS register instance
 * \return left stereo data
 */
__attribute__((always_inline)) static inline uint8_t I2ssReg_GetLrbr0Lrbr0(const I2ssRegType *obj)
{
    return ((obj->LRBR0 & I2SS_LRBR0_LRBR0_MASK) >> I2SS_LRBR0_LRBR0_SHIFT);
}

/*! \brief Gets the right stereo data
 *
 * This function gets the current right stereo data.
 * The right stereo data received serially from the receive channel input
 *
 * \param[in] obj : pointer to I2SS register instance
 * \return right stereo data
 */
__attribute__((always_inline)) static inline uint8_t I2ssReg_GetRrbr0Rrbr0(const I2ssRegType *obj)
{
    return ((obj->RRBR0 & I2SS_RRBR0_RRBR0_MASK) >> I2SS_RRBR0_RRBR0_SHIFT);
}

/*! \brief Gets the receive channel enable
 *
 * This function gets the current receive channel enable.
 *
 * \param[in] obj : pointer to I2SS register instance
 * \return receive channel enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t I2ssReg_GetRer0Ch0(const I2ssRegType *obj)
{
    return ((obj->RER0 & I2SS_RER0_CH0_MASK) >> I2SS_RER0_CH0_SHIFT);
}

/*! \brief Sets the receive channel enable
 *
 * This function sets the receive channel enable.
 *
 * \param[in] obj : pointer to I2SS register instance
 * \param[in] value : the value of receive channel enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void I2ssReg_SetRer0Ch0(I2ssRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->RER0;

    tmp &= ~I2SS_RER0_CH0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << I2SS_RER0_CH0_SHIFT)) & I2SS_RER0_CH0_MASK);
    obj->RER0 = tmp;
}

/*! \brief Gets the receive data width
 *
 * This function gets the current receive data width.
 * These bits are used to program the data resolution of the receiver and ensures the MSB of the data is transmitted first.
 *
 * \param[in] obj : pointer to I2SS register instance
 * \return receive data width
 *         - 0h : ignore
 *         - 1h : 12bit data
 *         - 2h : 16bit data
 *         - 3h : 20bit data
 *         - 4h : 24bit data
 *         - 5h : 32bit data
 */
__attribute__((always_inline)) static inline uint8_t I2ssReg_GetRcr0RxWLen(const I2ssRegType *obj)
{
    return ((obj->RCR0 & I2SS_RCR0_RX_WLEN_MASK) >> I2SS_RCR0_RX_WLEN_SHIFT);
}

/*! \brief Sets the receive data width
 *
 * This function sets the receive data width.
 * These bits are used to program the data resolution of the receiver and ensures the MSB of the data is transmitted first.
 *
 * \param[in] obj : pointer to I2SS register instance
 * \param[in] value : the value of receive data width
 *                    - 0h : ignore
 *                    - 1h : 12bit data
 *                    - 2h : 16bit data
 *                    - 3h : 20bit data
 *                    - 4h : 24bit data
 *                    - 5h : 32bit data
 */
__attribute__((always_inline)) static inline void I2ssReg_SetRcr0RxWLen(I2ssRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->RCR0;

    tmp &= ~I2SS_RCR0_RX_WLEN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << I2SS_RCR0_RX_WLEN_SHIFT)) & I2SS_RCR0_RX_WLEN_MASK);
    obj->RCR0 = tmp;
}

/*! \brief Gets the RX FIFO data overrun interrupt
 *
 * This function gets the current RX FIFO data overrun interrupt.
 * Incoming data lost due to a full RX FIFO.
 *
 * \param[in] obj : pointer to I2SS register instance
 * \return RX FIFO data overrun interrupt
 *         - 0b : RX FIFO write valid
 *         - 1b : RX FIFO write overrun
 */
__attribute__((always_inline)) static inline uint8_t I2ssReg_GetIsr0RxFo(const I2ssRegType *obj)
{
    return ((obj->ISR0 & I2SS_ISR0_RXFO_MASK) >> I2SS_ISR0_RXFO_SHIFT);
}

/*! \brief Gets the Status of Receive Data Available interrupt
 *
 * This function gets the current Status of Receive Data Available interrupt.
 * This bit denotes the status of the RX FIFO trigger level.
 *
 * \param[in] obj : pointer to I2SS register instance
 * \return Status of Receive Data Available interrupt
 *         - 0b : RX FIFO trigger level is reached
 *         - 1b : RX FIFO trigger level is not reached
 */
__attribute__((always_inline)) static inline uint8_t I2ssReg_GetIsr0RxDa(const I2ssRegType *obj)
{
    return ((obj->ISR0 & I2SS_ISR0_RXDA_MASK) >> I2SS_ISR0_RXDA_SHIFT);
}

/*! \brief Gets the RX FIFO overrun interrupt mask
 *
 * This function gets the current RX FIFO overrun interrupt mask.
 *
 * \param[in] obj : pointer to I2SS register instance
 * \return RX FIFO overrun interrupt mask
 *         - 0b : unmasks RX FIFO overrun interrupt
 *         - 1b : mask RX FIFO overrun interrupt
 */
__attribute__((always_inline)) static inline uint8_t I2ssReg_GetImr0RxFom(const I2ssRegType *obj)
{
    return ((obj->IMR0 & I2SS_IMR0_RXFOM_MASK) >> I2SS_IMR0_RXFOM_SHIFT);
}

/*! \brief Sets the RX FIFO overrun interrupt mask
 *
 * This function sets the RX FIFO overrun interrupt mask.
 *
 * \param[in] obj : pointer to I2SS register instance
 * \param[in] value : the value of RX FIFO overrun interrupt mask
 *                    - 0b : unmasks RX FIFO overrun interrupt
 *                    - 1b : mask RX FIFO overrun interrupt
 */
__attribute__((always_inline)) static inline void I2ssReg_SetImr0RxFom(I2ssRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->IMR0;

    tmp &= ~I2SS_IMR0_RXFOM_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << I2SS_IMR0_RXFOM_SHIFT)) & I2SS_IMR0_RXFOM_MASK);
    obj->IMR0 = tmp;
}

/*! \brief Gets the Mask RX FIFO Data Available interrupt.
 *
 * This function gets the current Mask RX FIFO Data Available interrupt.
 * This bit masks or unmasks an RX FIFO Data Available interrupt.
 *
 * \param[in] obj : pointer to I2SS register instance
 * \return Mask RX FIFO Data Available interrupt.
 *         - 1b : Masks RX FIFO data available interrupt
 *         - 0b : Unmasks RX FIFO data available interrupt
 */
__attribute__((always_inline)) static inline uint8_t I2ssReg_GetImr0RxDam(const I2ssRegType *obj)
{
    return ((obj->IMR0 & I2SS_IMR0_RXDAM_MASK) >> I2SS_IMR0_RXDAM_SHIFT);
}

/*! \brief Sets the Mask RX FIFO Data Available interrupt.
 *
 * This function sets the Mask RX FIFO Data Available interrupt.
 * This bit masks or unmasks an RX FIFO Data Available interrupt.
 *
 * \param[in] obj : pointer to I2SS register instance
 * \param[in] value : the value of Mask RX FIFO Data Available interrupt.
 *                    - 1b : Masks RX FIFO data available interrupt
 *                    - 0b : Unmasks RX FIFO data available interrupt
 */
__attribute__((always_inline)) static inline void I2ssReg_SetImr0RxDam(I2ssRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->IMR0;

    tmp &= ~I2SS_IMR0_RXDAM_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << I2SS_IMR0_RXDAM_SHIFT)) & I2SS_IMR0_RXDAM_MASK);
    obj->IMR0 = tmp;
}

/*! \brief Gets the RX FIFO write overrun
 *
 * This function gets the current RX FIFO write overrun.
 *
 * \param[in] obj : pointer to I2SS register instance
 * \return RX FIFO write overrun
 *         - 0b : RX FIFO write valid
 *         - 1b : RX FIFO write overrun
 */
__attribute__((always_inline)) static inline uint8_t I2ssReg_GetRor0RxChO(const I2ssRegType *obj)
{
    return ((obj->ROR0 & I2SS_ROR0_RXCHO_MASK) >> I2SS_ROR0_RXCHO_SHIFT);
}

/*! \brief Sets the RX FIFO write overrun
 *
 * This function sets the RX FIFO write overrun.
 *
 * \param[in] obj : pointer to I2SS register instance
 * \param[in] value : the value of RX FIFO write overrun
 *                    - 0b : RX FIFO write valid
 *                    - 1b : RX FIFO write overrun
 */
__attribute__((always_inline)) static inline void I2ssReg_SetRor0RxChO(I2ssRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->ROR0;

    tmp &= ~I2SS_ROR0_RXCHO_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << I2SS_ROR0_RXCHO_SHIFT)) & I2SS_ROR0_RXCHO_MASK);
    obj->ROR0 = tmp;
}

/*! \brief Gets the FIFO level trigger interrupt
 *
 * This function gets the current FIFO level trigger interrupt.
 * When the FIFO level reaches the register, interrupt triggers.
 *
 * \param[in] obj : pointer to I2SS register instance
 * \return FIFO level trigger interrupt
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
__attribute__((always_inline)) static inline uint8_t I2ssReg_GetRfcr0RxChdt(const I2ssRegType *obj)
{
    return ((obj->RFCR0 & I2SS_RFCR0_RXCHDT_MASK) >> I2SS_RFCR0_RXCHDT_SHIFT);
}

/*! \brief Sets the FIFO level trigger interrupt
 *
 * This function sets the FIFO level trigger interrupt.
 * When the FIFO level reaches the register, interrupt triggers.
 *
 * \param[in] obj : pointer to I2SS register instance
 * \param[in] value : the value of FIFO level trigger interrupt
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
__attribute__((always_inline)) static inline void I2ssReg_SetRfcr0RxChdt(I2ssRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->RFCR0;

    tmp &= ~I2SS_RFCR0_RXCHDT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << I2SS_RFCR0_RXCHDT_SHIFT)) & I2SS_RFCR0_RXCHDT_MASK);
    obj->RFCR0 = tmp;
}

/*! \brief Sets the RX FIFO flush
 *
 * This function sets the RX FIFO flush.
 * Writing a 1 to this register flushes an individual RX FIFO (This is a self clearing bit.).
 * A Rx channel or block must be disabled prior to writing to this bit.
 *
 * \param[in] obj : pointer to I2SS register instance
 * \param[in] value : the value of RX FIFO flush
 *                    - 0b : Does not flush an individual RX FIFO
 *                    - 1b : flush an individual RX FIFO
 */
__attribute__((always_inline)) static inline void I2ssReg_SetRff0RxChfr0(I2ssRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->RFF0;

    tmp &= ~I2SS_RFF0_RXCHFR0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << I2SS_RFF0_RXCHFR0_SHIFT)) & I2SS_RFF0_RXCHFR0_MASK);
    obj->RFF0 = tmp;
}

/*! \brief Gets the Receive Block DMA Register
 *
 * This function gets the current Receive Block DMA Register.
 * These bits are used to cycle repeatedly through the enabled receive channels (from lowest numbered to highest),
 * reading stereo data pairs
 *
 * \param[in] obj : pointer to I2SS register instance
 * \return Receive Block DMA Register
 */
__attribute__((always_inline)) static inline uint32_t I2ssReg_GetRxDmaRxDma(const I2ssRegType *obj)
{
    return ((obj->RXDMA & I2SS_RXDMA_RXDMA_MASK) >> I2SS_RXDMA_RXDMA_SHIFT);
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _I2SS_REG_H_ */
