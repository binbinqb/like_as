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

#ifndef _CRC_REG_H_
#define _CRC_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the CRC Registers
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

/* DR Bit Fields */
#define CRC_DR_DR_MASK        (0xFFFFFFFFu)
#define CRC_DR_DR_SHIFT       (0u)
#define CRC_DR_DR_WIDTH       (32u)

/* IDR Bit Fields */
#define CRC_IDR_COUNTER_MASK  (0xFu)
#define CRC_IDR_COUNTER_SHIFT (0u)
#define CRC_IDR_COUNTER_WIDTH (4u)

/* CR Bit Fields */
#define CRC_CR_RESET_MASK     (0x1u)
#define CRC_CR_RESET_SHIFT    (0u)
#define CRC_CR_RESET_WIDTH    (1u)
#define CRC_CR_REVIN_MASK     (0x60u)
#define CRC_CR_REVIN_SHIFT    (5u)
#define CRC_CR_REVIN_WIDTH    (2u)
#define CRC_CR_REVOUT_MASK    (0x300u)
#define CRC_CR_REVOUT_SHIFT   (8u)
#define CRC_CR_REVOUT_WIDTH   (2u)
#define CRC_CR_FXOR_MASK      (0x800u)
#define CRC_CR_FXOR_SHIFT     (11u)
#define CRC_CR_FXOR_WIDTH     (1u)
#define CRC_CR_TCRC_MASK      (0x1000u)
#define CRC_CR_TCRC_SHIFT     (12u)
#define CRC_CR_TCRC_WIDTH     (1u)

/* INIT Bit Fields */
#define CRC_INIT_INIT_MASK    (0xFFFFFFFFu)
#define CRC_INIT_INIT_SHIFT   (0u)
#define CRC_INIT_INIT_WIDTH   (32u)

/* POL Bit Fields */
#define CRC_POL_POL_MASK      (0xFFFFFFFFu)
#define CRC_POL_POL_SHIFT     (0u)
#define CRC_POL_POL_WIDTH     (32u)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief The definition of CRC registers
 */
typedef struct _CrcRegType_
{
    union
    {
        volatile uint32_t DATA_32; /*!< CRC data storage register, offset: 0x0 */
        struct
        {
            volatile uint16_t L; /*!< CRC_DR_L, offset: 0x0 */
            volatile uint16_t H; /*!< CRC_DR_L, offset: 0x2 */
        } DATA_16;
        struct
        {
            volatile uint8_t LL; /*!< CRC_DR_LL, offset: 0x0 */
            volatile uint8_t LU; /*!< CRC_DR_LU, offset: 0x1 */
            volatile uint8_t HL; /*!< CRC_DR_HL, offset: 0x2 */
            volatile uint8_t HU; /*!< CRC_DR_HU, offset: 0x3 */
        } DATA_8;
    } DR;
    volatile uint32_t IDR;      /*!< CRC data length register, offset: 0x4 */
    volatile uint32_t CR;       /*!< CRC control register, offset: 0x8 */
    uint32_t          RESERVED; /*!< Reserved register, offset: 0xC */
    volatile uint32_t INIT;     /*!< Initial seed value register, offset: 0x10 */
    volatile uint32_t POL;      /*!< Initial value of polynormal register, offset: 0x14 */
} CrcRegType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Get the current CRC data register
 *
 * This function gets the current CRC calculation result.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 * If CR.RESET happen, it holds the crc_init value
 *
 * \param[in] obj : pointer to CRC register instance
 * \return the current CRC calculation result
 */
__attribute__((always_inline)) static inline uint32_t CrcReg_GetDataReg(const CrcRegType *obj)
{
    return obj->DR.DATA_32;
}

/*! \brief Set the 32 bits of CRC data register
 *
 * This function writes new 32 bits data to CRC calculator
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CRC register instance
 * \param[in] value : current CRC calculation data
 */
__attribute__((always_inline)) static inline void CrcReg_SetDataReg(CrcRegType *obj, uint32_t value)
{
    obj->DR.DATA_32 = value;
}

/*! \brief Set the 16 bits of CRC data register
 *
 * This function writes new 16 bits data to CRC calculator
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CRC register instance
 * \param[in] value : current CRC calculation data
 */
__attribute__((always_inline)) static inline void CrcReg_SetData16Reg(CrcRegType *obj, uint16_t value)
{
    obj->DR.DATA_16.L = value;
}

/*! \brief Set the 8 bits of CRC data register
 *
 * This function writes new 8 bits data to CRC calculator
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CRC register instance
 * \param[in] value : current CRC calculation data
 */
__attribute__((always_inline)) static inline void CrcReg_SetData8Reg(CrcRegType *obj, uint8_t value)
{
    obj->DR.DATA_8.LL = value;
}

/*! \brief Get the remain number of data in FIFO
 *
 * Total depth is 8, the register shows the remain number of data in fifo
 * Counter reset to 0 if CR.RESET happened
 * This register is read-only
 *
 * \param[in] obj : pointer to CRC register instance
 * \return the remain number of data in fifo
 */
__attribute__((always_inline)) static inline uint32_t CrcReg_GetDataNumInFifo(const CrcRegType *obj)
{
    return ((obj->IDR & CRC_IDR_COUNTER_MASK) >> CRC_IDR_COUNTER_SHIFT);
}

/*! \brief Get the reset bit in CR register
 *
 * This bit is automatically cleared by hardware.
 * Read as 1 , assert to 1 after reading
 *
 * \param[in] obj : pointer to CRC register instance
 * \return the reset bit value
 */
__attribute__((always_inline)) static inline uint8_t CrcReg_GetCrReset(const CrcRegType *obj)
{
    return ((obj->CR & CRC_CR_RESET_MASK) >> CRC_CR_RESET_SHIFT);
}

/*! \brief Set the reset bit in CR register
 *
 * This bit is set to reset CRC calculation unit and set data register to the value stored in CRC_INIT
 *
 * \param[in] obj : pointer to CRC register instance
 */
__attribute__((always_inline)) static inline void CrcReg_SetCrReset(CrcRegType *obj)
{
    uint32_t crTmp = obj->CR;

    crTmp &= ~(CRC_CR_RESET_MASK);
    crTmp |= (((uint32_t)(((uint32_t)(1u)) << CRC_CR_RESET_SHIFT)) & CRC_CR_RESET_MASK);
    obj->CR = crTmp;
}

/*! \brief Get the reversal of bit order of the input data
 *
 * These bits control the reversal of the bit order of the input data
 * This register is not affected by CRC resets generated by the reset bit in the CRC_CR register
 *
 * \param[in] obj : pointer to CRC register instance
 * \return the value of reversal of bit order
 *         - 0 : No transposition.
 *         - 1 : Bits in bytes are transposed; bytes are not transposed.
 *         - 2 : Both bits in bytes and bytes are transposed
 *         - 3 : Only bytes are transposed; no bits in a byte are transposed
 */
__attribute__((always_inline)) static inline uint8_t CrcReg_GetCrReverseIn(const CrcRegType *obj)
{
    return ((obj->CR & CRC_CR_REVIN_MASK) >> CRC_CR_REVIN_SHIFT);
}

/*! \brief Set the reversal of bit order of the input data
 *
 * These bits control the reversal of the bit order of the input data
 * This register is not affected by CRC resets generated by the reset bit in the CRC_CR register
 *
 * \param[in] obj : pointer to CRC register instance
 * \param[in] value : the value of reversal of bit order
 *            - 0 : No transposition.
 *            - 1 : Bits in bytes are transposed; bytes are not transposed.
 *            - 2 : Both bits in bytes and bytes are transposed
 *            - 3 : Only bytes are transposed; no bits in a byte are transposed
 */
__attribute__((always_inline)) static inline void CrcReg_SetCrReverseIn(CrcRegType *obj, uint8_t value)
{
    uint32_t crTmp = obj->CR;

    crTmp &= ~(CRC_CR_REVIN_MASK);
    crTmp |= (((uint32_t)(((uint32_t)(value)) << CRC_CR_REVIN_SHIFT)) & CRC_CR_REVIN_MASK);
    obj->CR = crTmp;
}

/*! \brief Get the reversal of bit order of the output data
 *
 * These bits control the reversal of the bit order of the output data
 * This register is not affected by CRC resets generated by the reset bit in the CRC_CR register
 *
 * \param[in] obj : pointer to CRC register instance
 * \return the value of reversal of bit order
 *         - 0 : No transposition.
 *         - 1 : Bits in bytes are transposed; bytes are not transposed.
 *         - 2 : Both bits in bytes and bytes are transposed
 *         - 3 : Only bytes are transposed; no bits in a byte are transposed
 */
__attribute__((always_inline)) static inline uint8_t CrcReg_GetCrReverseOut(const CrcRegType *obj)
{
    return ((obj->CR & CRC_CR_REVOUT_MASK) >> CRC_CR_REVOUT_SHIFT);
}

/*! \brief Set the reversal of bit order of the output data
 *
 * These bits control the reversal of the bit order of the output data
 * This register is not affected by CRC resets generated by the reset bit in the CRC_CR register
 *
 * \param[in] obj : pointer to CRC register instance
 * \param[in] value : the value of reversal of bit order
 *            - 0 : No transposition.
 *            - 1 : Bits in bytes are transposed; bytes are not transposed.
 *            - 2 : Both bits in bytes and bytes are transposed
 *            - 3 : Only bytes are transposed; no bits in a byte are transposed
 */
__attribute__((always_inline)) static inline void CrcReg_SetCrReverseOut(CrcRegType *obj, uint8_t value)
{
    uint32_t crTmp = obj->CR;

    crTmp &= ~(CRC_CR_REVOUT_MASK);
    crTmp |= (((uint32_t)(((uint32_t)(value)) << CRC_CR_REVOUT_SHIFT)) & CRC_CR_REVOUT_MASK);
    obj->CR = crTmp;
}

/*! \brief Get complement read of CRC data register
 *
 * Some CRC protocols require the final checksum to be XORed with 0xFFFFFFFF or 0xFFFF.
 * Asserting this bit enables on the fly complementing of read data.
 * This register is not affected by CRC resets generated by the reset bit in the CRC_CR register.
 *
 * \param[in] obj : pointer to CRC register instance
 * \return the value of complement read
 *         - 0 : No XOR on reading.
 *         - 1 : Invert or complement the read value of the CRC Data register.
 */
__attribute__((always_inline)) static inline uint8_t CrcReg_GetCrFXor(const CrcRegType *obj)
{
    return ((obj->CR & CRC_CR_FXOR_MASK) >> CRC_CR_FXOR_SHIFT);
}

/*! \brief Set complement read of CRC data register
 *
 * Some CRC protocols require the final checksum to be XORed with 0xFFFFFFFF or 0xFFFF.
 * Asserting this bit enables on the fly complementing of read data.
 * This register is not affected by CRC resets generated by the reset bit in the CRC_CR register.
 *
 * \param[in] obj : pointer to CRC register instance
 * \param[in] value : the value of complement read
 *            - 0 : No XOR on reading.
 *            - 1 : Invert or complement the read value of the CRC Data register.
 */
__attribute__((always_inline)) static inline void CrcReg_SetCrFXor(CrcRegType *obj, uint8_t value)
{
    uint32_t crTmp = obj->CR;

    crTmp &= ~(CRC_CR_FXOR_MASK);
    crTmp |= (((uint32_t)(((uint32_t)(value)) << CRC_CR_FXOR_SHIFT)) & CRC_CR_FXOR_MASK);
    obj->CR = crTmp;
}

/*! \brief Get the width of CRC protocol (poly)
 *
 * This function gets the width of CRC protocol (poly).
 * This register is not affected by CRC resets generated by the reset bit in the CRC_CR register.
 *
 * \param[in] obj : pointer to CRC register instance
 * \return the value of reversal of bit order
 *         - 0 : 16-bit CRC protocol.
 *         - 1 : 32-bit CRC protocol.
 */
__attribute__((always_inline)) static inline uint8_t CrcReg_GetCrProtocolWidth(const CrcRegType *obj)
{
    return ((obj->CR & CRC_CR_TCRC_MASK) >> CRC_CR_TCRC_SHIFT);
}

/*! \brief Set the width of CRC protocol (poly)
 *
 * This function sets the width of CRC protocol (poly).
 * This register is not affected by CRC resets generated by the reset bit in the CRC_CR register.
 *
 * \param[in] obj : pointer to CRC register instance
 * \param[in] value : the value of reversal of bit order
 *            - 0 : 16-bit CRC protocol.
 *            - 1 : 32-bit CRC protocol.
 */
__attribute__((always_inline)) static inline void CrcReg_SetCrProtocolWidth(CrcRegType *obj, uint8_t value)
{
    uint32_t crTmp = obj->CR;

    crTmp &= ~(CRC_CR_TCRC_MASK);
    crTmp |= (((uint32_t)(((uint32_t)(value)) << CRC_CR_TCRC_SHIFT)) & CRC_CR_TCRC_MASK);
    obj->CR = crTmp;
}

/*! \brief Get the initial seed register value
 *
 * This function gets the initial seed register value.
 *
 * \param[in] obj : pointer to CRC register instance
 * \return the initial seed register value
 */
__attribute__((always_inline)) static inline uint32_t CrcReg_GetInitReg(const CrcRegType *obj)
{
    return obj->INIT;
}

/*! \brief Set the initial seed register
 *
 * This function sets the initial seed register.
 * Write this reg also can reset CRC calculation unit.
 *
 * \param[in] obj : pointer to CRC register instance
 * \param[in] value : initial seed
 */
__attribute__((always_inline)) static inline void CrcReg_SetInitReg(CrcRegType *obj, uint32_t value)
{
    obj->INIT = value;
}

/*! \brief Get the initial value of polynomial
 *
 * This function gets the initial value of polynomial.
 * This register is not affected by CRC resets generated
 * by the reset bit in the CRC_CR register.
 *
 * \param[in] obj : pointer to CRC register instance
 * \return the initial value of polynomial
 */
__attribute__((always_inline)) static inline uint32_t CrcReg_GetPolyReg(const CrcRegType *obj)
{
    return obj->POL;
}

/*! \brief Set initial value of polynomial
 *
 * This function sets initial value of polynomial.
 * This register is not affected by CRC resets generated
 * by the reset bit in the CRC_CR register.
 *
 * \param[in] obj : pointer to CRC register instance
 * \param[in] value : the initial value of polynomial
 */
__attribute__((always_inline)) static inline void CrcReg_SetPolyReg(CrcRegType *obj, uint32_t value)
{
    obj->POL = value;
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _CRC_REG_H_ */
