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

#ifndef _TRGMUX_REG_H_
#define _TRGMUX_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the TRGMUX Registers
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

/* DMAMUX0 Bit Fields */
#define TRGMUX_DMAMUX0_LK_MASK    (0x80000000u)
#define TRGMUX_DMAMUX0_LK_SHIFT   (31u)
#define TRGMUX_DMAMUX0_LK_WIDTH   (1u)
#define TRGMUX_DMAMUX0_SEL3_MASK  (0x7F000000u)
#define TRGMUX_DMAMUX0_SEL3_SHIFT (24u)
#define TRGMUX_DMAMUX0_SEL3_WIDTH (7u)
#define TRGMUX_DMAMUX0_SEL2_MASK  (0x7F0000u)
#define TRGMUX_DMAMUX0_SEL2_SHIFT (16u)
#define TRGMUX_DMAMUX0_SEL2_WIDTH (7u)
#define TRGMUX_DMAMUX0_SEL1_MASK  (0x7F00u)
#define TRGMUX_DMAMUX0_SEL1_SHIFT (8u)
#define TRGMUX_DMAMUX0_SEL1_WIDTH (7u)
#define TRGMUX_DMAMUX0_SEL0_MASK  (0x7Fu)
#define TRGMUX_DMAMUX0_SEL0_SHIFT (0u)
#define TRGMUX_DMAMUX0_SEL0_WIDTH (7u)

/* EXTOUT0 Bit Fields */
#define TRGMUX_EXTOUT0_LK_MASK    (0x80000000u)
#define TRGMUX_EXTOUT0_LK_SHIFT   (31u)
#define TRGMUX_EXTOUT0_LK_WIDTH   (1u)
#define TRGMUX_EXTOUT0_SEL3_MASK  (0x7F000000u)
#define TRGMUX_EXTOUT0_SEL3_SHIFT (24u)
#define TRGMUX_EXTOUT0_SEL3_WIDTH (7u)
#define TRGMUX_EXTOUT0_SEL2_MASK  (0x7F0000u)
#define TRGMUX_EXTOUT0_SEL2_SHIFT (16u)
#define TRGMUX_EXTOUT0_SEL2_WIDTH (7u)
#define TRGMUX_EXTOUT0_SEL1_MASK  (0x7F00u)
#define TRGMUX_EXTOUT0_SEL1_SHIFT (8u)
#define TRGMUX_EXTOUT0_SEL1_WIDTH (7u)
#define TRGMUX_EXTOUT0_SEL0_MASK  (0x7Fu)
#define TRGMUX_EXTOUT0_SEL0_SHIFT (0u)
#define TRGMUX_EXTOUT0_SEL0_WIDTH (7u)

/* EXTOUT1 Bit Fields */
#define TRGMUX_EXTOUT1_LK_MASK    (0x80000000u)
#define TRGMUX_EXTOUT1_LK_SHIFT   (31u)
#define TRGMUX_EXTOUT1_LK_WIDTH   (1u)
#define TRGMUX_EXTOUT1_SEL3_MASK  (0x7F000000u)
#define TRGMUX_EXTOUT1_SEL3_SHIFT (24u)
#define TRGMUX_EXTOUT1_SEL3_WIDTH (7u)
#define TRGMUX_EXTOUT1_SEL2_MASK  (0x7F0000u)
#define TRGMUX_EXTOUT1_SEL2_SHIFT (16u)
#define TRGMUX_EXTOUT1_SEL2_WIDTH (7u)
#define TRGMUX_EXTOUT1_SEL1_MASK  (0x7F00u)
#define TRGMUX_EXTOUT1_SEL1_SHIFT (8u)
#define TRGMUX_EXTOUT1_SEL1_WIDTH (7u)
#define TRGMUX_EXTOUT1_SEL0_MASK  (0x7Fu)
#define TRGMUX_EXTOUT1_SEL0_SHIFT (0u)
#define TRGMUX_EXTOUT1_SEL0_WIDTH (7u)

/* ADC0 Bit Fields */
#define TRGMUX_ADC0_LK_MASK       (0x80000000u)
#define TRGMUX_ADC0_LK_SHIFT      (31u)
#define TRGMUX_ADC0_LK_WIDTH      (1u)
#define TRGMUX_ADC0_SEL3_MASK     (0x7F000000u)
#define TRGMUX_ADC0_SEL3_SHIFT    (24u)
#define TRGMUX_ADC0_SEL3_WIDTH    (7u)
#define TRGMUX_ADC0_SEL2_MASK     (0x7F0000u)
#define TRGMUX_ADC0_SEL2_SHIFT    (16u)
#define TRGMUX_ADC0_SEL2_WIDTH    (7u)
#define TRGMUX_ADC0_SEL1_MASK     (0x7F00u)
#define TRGMUX_ADC0_SEL1_SHIFT    (8u)
#define TRGMUX_ADC0_SEL1_WIDTH    (7u)
#define TRGMUX_ADC0_SEL0_MASK     (0x7Fu)
#define TRGMUX_ADC0_SEL0_SHIFT    (0u)
#define TRGMUX_ADC0_SEL0_WIDTH    (7u)

/* ADC1 Bit Fields */
#define TRGMUX_ADC1_LK_MASK       (0x80000000u)
#define TRGMUX_ADC1_LK_SHIFT      (31u)
#define TRGMUX_ADC1_LK_WIDTH      (1u)
#define TRGMUX_ADC1_SEL3_MASK     (0x7F000000u)
#define TRGMUX_ADC1_SEL3_SHIFT    (24u)
#define TRGMUX_ADC1_SEL3_WIDTH    (7u)
#define TRGMUX_ADC1_SEL2_MASK     (0x7F0000u)
#define TRGMUX_ADC1_SEL2_SHIFT    (16u)
#define TRGMUX_ADC1_SEL2_WIDTH    (7u)
#define TRGMUX_ADC1_SEL1_MASK     (0x7F00u)
#define TRGMUX_ADC1_SEL1_SHIFT    (8u)
#define TRGMUX_ADC1_SEL1_WIDTH    (7u)
#define TRGMUX_ADC1_SEL0_MASK     (0x7Fu)
#define TRGMUX_ADC1_SEL0_SHIFT    (0u)
#define TRGMUX_ADC1_SEL0_WIDTH    (7u)

/* CMP Bit Fields */
#define TRGMUX_CMP_LK_MASK        (0x80000000u)
#define TRGMUX_CMP_LK_SHIFT       (31u)
#define TRGMUX_CMP_LK_WIDTH       (1u)
#define TRGMUX_CMP_SEL0_MASK      (0x7Fu)
#define TRGMUX_CMP_SEL0_SHIFT     (0u)
#define TRGMUX_CMP_SEL0_WIDTH     (7u)

/* MFT0 Bit Fields */
#define TRGMUX_MFT0_LK_MASK       (0x80000000u)
#define TRGMUX_MFT0_LK_SHIFT      (31u)
#define TRGMUX_MFT0_LK_WIDTH      (1u)
#define TRGMUX_MFT0_SEL3_MASK     (0x7F000000u)
#define TRGMUX_MFT0_SEL3_SHIFT    (24u)
#define TRGMUX_MFT0_SEL3_WIDTH    (7u)
#define TRGMUX_MFT0_SEL2_MASK     (0x7F0000u)
#define TRGMUX_MFT0_SEL2_SHIFT    (16u)
#define TRGMUX_MFT0_SEL2_WIDTH    (7u)
#define TRGMUX_MFT0_SEL1_MASK     (0x7F00u)
#define TRGMUX_MFT0_SEL1_SHIFT    (8u)
#define TRGMUX_MFT0_SEL1_WIDTH    (7u)
#define TRGMUX_MFT0_SEL0_MASK     (0x7Fu)
#define TRGMUX_MFT0_SEL0_SHIFT    (0u)
#define TRGMUX_MFT0_SEL0_WIDTH    (7u)

/* MFT1 Bit Fields */
#define TRGMUX_MFT1_LK_MASK       (0x80000000u)
#define TRGMUX_MFT1_LK_SHIFT      (31u)
#define TRGMUX_MFT1_LK_WIDTH      (1u)
#define TRGMUX_MFT1_SEL3_MASK     (0x7F000000u)
#define TRGMUX_MFT1_SEL3_SHIFT    (24u)
#define TRGMUX_MFT1_SEL3_WIDTH    (7u)
#define TRGMUX_MFT1_SEL2_MASK     (0x7F0000u)
#define TRGMUX_MFT1_SEL2_SHIFT    (16u)
#define TRGMUX_MFT1_SEL2_WIDTH    (7u)
#define TRGMUX_MFT1_SEL1_MASK     (0x7F00u)
#define TRGMUX_MFT1_SEL1_SHIFT    (8u)
#define TRGMUX_MFT1_SEL1_WIDTH    (7u)
#define TRGMUX_MFT1_SEL0_MASK     (0x7Fu)
#define TRGMUX_MFT1_SEL0_SHIFT    (0u)
#define TRGMUX_MFT1_SEL0_WIDTH    (7u)

/* MFT2 Bit Fields */
#define TRGMUX_MFT2_LK_MASK       (0x80000000u)
#define TRGMUX_MFT2_LK_SHIFT      (31u)
#define TRGMUX_MFT2_LK_WIDTH      (1u)
#define TRGMUX_MFT2_SEL3_MASK     (0x7F000000u)
#define TRGMUX_MFT2_SEL3_SHIFT    (24u)
#define TRGMUX_MFT2_SEL3_WIDTH    (7u)
#define TRGMUX_MFT2_SEL2_MASK     (0x7F0000u)
#define TRGMUX_MFT2_SEL2_SHIFT    (16u)
#define TRGMUX_MFT2_SEL2_WIDTH    (7u)
#define TRGMUX_MFT2_SEL1_MASK     (0x7F00u)
#define TRGMUX_MFT2_SEL1_SHIFT    (8u)
#define TRGMUX_MFT2_SEL1_WIDTH    (7u)
#define TRGMUX_MFT2_SEL0_MASK     (0x7Fu)
#define TRGMUX_MFT2_SEL0_SHIFT    (0u)
#define TRGMUX_MFT2_SEL0_WIDTH    (7u)

/* MFT3 Bit Fields */
#define TRGMUX_MFT3_LK_MASK       (0x80000000u)
#define TRGMUX_MFT3_LK_SHIFT      (31u)
#define TRGMUX_MFT3_LK_WIDTH      (1u)
#define TRGMUX_MFT3_SEL3_MASK     (0x7F000000u)
#define TRGMUX_MFT3_SEL3_SHIFT    (24u)
#define TRGMUX_MFT3_SEL3_WIDTH    (7u)
#define TRGMUX_MFT3_SEL2_MASK     (0x7F0000u)
#define TRGMUX_MFT3_SEL2_SHIFT    (16u)
#define TRGMUX_MFT3_SEL2_WIDTH    (7u)
#define TRGMUX_MFT3_SEL1_MASK     (0x7F00u)
#define TRGMUX_MFT3_SEL1_SHIFT    (8u)
#define TRGMUX_MFT3_SEL1_WIDTH    (7u)
#define TRGMUX_MFT3_SEL0_MASK     (0x7Fu)
#define TRGMUX_MFT3_SEL0_SHIFT    (0u)
#define TRGMUX_MFT3_SEL0_WIDTH    (7u)

/* MFT4 Bit Fields */
#define TRGMUX_MFT4_LK_MASK       (0x80000000u)
#define TRGMUX_MFT4_LK_SHIFT      (31u)
#define TRGMUX_MFT4_LK_WIDTH      (1u)
#define TRGMUX_MFT4_SEL3_MASK     (0x7F000000u)
#define TRGMUX_MFT4_SEL3_SHIFT    (24u)
#define TRGMUX_MFT4_SEL3_WIDTH    (7u)
#define TRGMUX_MFT4_SEL2_MASK     (0x7F0000u)
#define TRGMUX_MFT4_SEL2_SHIFT    (16u)
#define TRGMUX_MFT4_SEL2_WIDTH    (7u)
#define TRGMUX_MFT4_SEL1_MASK     (0x7F00u)
#define TRGMUX_MFT4_SEL1_SHIFT    (8u)
#define TRGMUX_MFT4_SEL1_WIDTH    (7u)
#define TRGMUX_MFT4_SEL0_MASK     (0x7Fu)
#define TRGMUX_MFT4_SEL0_SHIFT    (0u)
#define TRGMUX_MFT4_SEL0_WIDTH    (7u)

/* MFT5 Bit Fields */
#define TRGMUX_MFT5_LK_MASK       (0x80000000u)
#define TRGMUX_MFT5_LK_SHIFT      (31u)
#define TRGMUX_MFT5_LK_WIDTH      (1u)
#define TRGMUX_MFT5_SEL3_MASK     (0x7F000000u)
#define TRGMUX_MFT5_SEL3_SHIFT    (24u)
#define TRGMUX_MFT5_SEL3_WIDTH    (7u)
#define TRGMUX_MFT5_SEL2_MASK     (0x7F0000u)
#define TRGMUX_MFT5_SEL2_SHIFT    (16u)
#define TRGMUX_MFT5_SEL2_WIDTH    (7u)
#define TRGMUX_MFT5_SEL1_MASK     (0x7F00u)
#define TRGMUX_MFT5_SEL1_SHIFT    (8u)
#define TRGMUX_MFT5_SEL1_WIDTH    (7u)
#define TRGMUX_MFT5_SEL0_MASK     (0x7Fu)
#define TRGMUX_MFT5_SEL0_SHIFT    (0u)
#define TRGMUX_MFT5_SEL0_WIDTH    (7u)

/* PDB0 Bit Fields */
#define TRGMUX_PDB0_LK_MASK       (0x80000000u)
#define TRGMUX_PDB0_LK_SHIFT      (31u)
#define TRGMUX_PDB0_LK_WIDTH      (1u)
#define TRGMUX_PDB0_SEL0_MASK     (0x7Fu)
#define TRGMUX_PDB0_SEL0_SHIFT    (0u)
#define TRGMUX_PDB0_SEL0_WIDTH    (7u)

/* PDB1 Bit Fields */
#define TRGMUX_PDB1_LK_MASK       (0x80000000u)
#define TRGMUX_PDB1_LK_SHIFT      (31u)
#define TRGMUX_PDB1_LK_WIDTH      (1u)
#define TRGMUX_PDB1_SEL0_MASK     (0x7Fu)
#define TRGMUX_PDB1_SEL0_SHIFT    (0u)
#define TRGMUX_PDB1_SEL0_WIDTH    (7u)

/* LPIT Bit Fields */
#define TRGMUX_LPIT_LK_MASK       (0x80000000u)
#define TRGMUX_LPIT_LK_SHIFT      (31u)
#define TRGMUX_LPIT_LK_WIDTH      (1u)
#define TRGMUX_LPIT_SEL3_MASK     (0x7F000000u)
#define TRGMUX_LPIT_SEL3_SHIFT    (24u)
#define TRGMUX_LPIT_SEL3_WIDTH    (7u)
#define TRGMUX_LPIT_SEL2_MASK     (0x7F0000u)
#define TRGMUX_LPIT_SEL2_SHIFT    (16u)
#define TRGMUX_LPIT_SEL2_WIDTH    (7u)
#define TRGMUX_LPIT_SEL1_MASK     (0x7F00u)
#define TRGMUX_LPIT_SEL1_SHIFT    (8u)
#define TRGMUX_LPIT_SEL1_WIDTH    (7u)
#define TRGMUX_LPIT_SEL0_MASK     (0x7Fu)
#define TRGMUX_LPIT_SEL0_SHIFT    (0u)
#define TRGMUX_LPIT_SEL0_WIDTH    (7u)

/* LPTMR Bit Fields */
#define TRGMUX_LPTMR_LK_MASK      (0x80000000u)
#define TRGMUX_LPTMR_LK_SHIFT     (31u)
#define TRGMUX_LPTMR_LK_WIDTH     (1u)
#define TRGMUX_LPTMR_SEL0_MASK    (0x7Fu)
#define TRGMUX_LPTMR_SEL0_SHIFT   (0u)
#define TRGMUX_LPTMR_SEL0_WIDTH   (7u)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief The definition of TRGMUX registers
 */
typedef struct _TrgMuxRegType_
{
    volatile uint32_t DMAMUX0; /*!< TRGMUX DMAMUX0 register, offset: 0x0   */
    volatile uint32_t EXTOUT0; /*!< TRGMUX EXTOUT0 register, offset: 0x4   */
    volatile uint32_t EXTOUT1; /*!< TRGMUX EXTOUT1 register, offset: 0x08  */
    volatile uint32_t ADC0;    /*!< TRGMUX ADC0 register, offset: 0x0C     */
    volatile uint32_t ADC1;    /*!< TRGMUX ADC1 register, offset: 0x10     */
    volatile uint32_t CMP;     /*!< TRGMUX CMP register, offset: 0x014     */
    volatile uint32_t MFT0;    /*!< TRGMUX MFT0 register, offset: 0x18     */
    volatile uint32_t MFT1;    /*!< TRGMUX MFT1 register, offset: 0x1C     */
    volatile uint32_t MFT2;    /*!< TRGMUX MFT2 register, offset: 0x20     */
    volatile uint32_t MFT3;    /*!< TRGMUX MFT3 register, offset: 0x24     */
    volatile uint32_t MFT4;    /*!< TRGMUX MFT4 register, offset: 0x28     */
    volatile uint32_t MFT5;    /*!< TRGMUX MFT5 register, offset: 0x2C     */
    volatile uint32_t PDB0;    /*!< TRGMUX PDB0 register, offset: 0x30     */
    volatile uint32_t PDB1;    /*!< TRGMUX PDB1 register, offset: 0x34     */
    volatile uint32_t LPIT;    /*!< TRGMUX LPIT register, offset: 0x38     */
    volatile uint32_t LPTMR;   /*!< TRGMUX LPTMR register, offset: 0x3C    */
} TrgMuxRegType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Gets the TRGMUX DMAMUX0 register lock
 *
 * This function gets the current TRGMUX DMAMUX0 register lock.
 * This bit shows whether the register can be written or not.
 * The LK bit can only be written once after any system reset.
 * Once LK is set, the SELx bits in this TRGMUX register cannot be changed until the next system reset clears LK.
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return TRGMUX DMAMUX0 register lock
 *         - 0b : Register can be written.
 *         - 1b : Register cannot be written until the next system Reset.
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetDmaMux0Lk(const TrgMuxRegType *obj)
{
    return ((obj->DMAMUX0 & TRGMUX_DMAMUX0_LK_MASK) >> TRGMUX_DMAMUX0_LK_SHIFT);
}

/*! \brief Sets the TRGMUX DMAMUX0 register lock
 *
 * This function sets the TRGMUX DMAMUX0 register lock.
 * This bit shows whether the register can be written or not.
 * The LK bit can only be written once after any system reset.
 * Once LK is set, the SELx bits in this TRGMUX register cannot be changed until the next system reset clears LK.
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of TRGMUX DMAMUX0 register lock
 *                    - 0b : Register can be written.
 *                    - 1b : Register cannot be written until the next system Reset.
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetDmaMux0Lk(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->DMAMUX0;

    tmp &= ~TRGMUX_DMAMUX0_LK_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_DMAMUX0_LK_SHIFT)) & TRGMUX_DMAMUX0_LK_MASK);
    obj->DMAMUX0 = tmp;
}

/*! \brief Gets the Selected source for output 3 of this module
 *
 * This function gets the current Selected source for output 3 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 3 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetDmaMux0Sel3(const TrgMuxRegType *obj)
{
    return ((obj->DMAMUX0 & TRGMUX_DMAMUX0_SEL3_MASK) >> TRGMUX_DMAMUX0_SEL3_SHIFT);
}

/*! \brief Sets the Selected source for output 3 of this module
 *
 * This function sets the Selected source for output 3 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 3 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetDmaMux0Sel3(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->DMAMUX0;

    tmp &= ~TRGMUX_DMAMUX0_SEL3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_DMAMUX0_SEL3_SHIFT)) & TRGMUX_DMAMUX0_SEL3_MASK);
    obj->DMAMUX0 = tmp;
}

/*! \brief Gets the Selected source for output 2 of this module
 *
 * This function gets the current Selected source for output 2 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 2 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetDmaMux0Sel2(const TrgMuxRegType *obj)
{
    return ((obj->DMAMUX0 & TRGMUX_DMAMUX0_SEL2_MASK) >> TRGMUX_DMAMUX0_SEL2_SHIFT);
}

/*! \brief Sets the Selected source for output 2 of this module
 *
 * This function sets the Selected source for output 2 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 2 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetDmaMux0Sel2(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->DMAMUX0;

    tmp &= ~TRGMUX_DMAMUX0_SEL2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_DMAMUX0_SEL2_SHIFT)) & TRGMUX_DMAMUX0_SEL2_MASK);
    obj->DMAMUX0 = tmp;
}

/*! \brief Gets the Selected source for output 1 of this module
 *
 * This function gets the current Selected source for output 1 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 1 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetDmaMux0Sel1(const TrgMuxRegType *obj)
{
    return ((obj->DMAMUX0 & TRGMUX_DMAMUX0_SEL1_MASK) >> TRGMUX_DMAMUX0_SEL1_SHIFT);
}

/*! \brief Sets the Selected source for output 1 of this module
 *
 * This function sets the Selected source for output 1 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 1 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetDmaMux0Sel1(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->DMAMUX0;

    tmp &= ~TRGMUX_DMAMUX0_SEL1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_DMAMUX0_SEL1_SHIFT)) & TRGMUX_DMAMUX0_SEL1_MASK);
    obj->DMAMUX0 = tmp;
}

/*! \brief Gets the Selected source for output 0 of this module
 *
 * This function gets the current Selected source for output 0 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 0 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetDmaMux0Sel0(const TrgMuxRegType *obj)
{
    return ((obj->DMAMUX0 & TRGMUX_DMAMUX0_SEL0_MASK) >> TRGMUX_DMAMUX0_SEL0_SHIFT);
}

/*! \brief Sets the Selected source for output 0 of this module
 *
 * This function sets the Selected source for output 0 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 0 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetDmaMux0Sel0(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->DMAMUX0;

    tmp &= ~TRGMUX_DMAMUX0_SEL0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_DMAMUX0_SEL0_SHIFT)) & TRGMUX_DMAMUX0_SEL0_MASK);
    obj->DMAMUX0 = tmp;
}

/*! \brief Gets the TRGMUX EXTOUT0 register lock
 *
 * This function gets the current TRGMUX EXTOUT0 register lock.
 * This bit shows whether the register can be written or not.
 * The LK bit can only be written once after any system reset.
 * Once LK is set, the SELx bits in this TRGMUX register cannot be changed until the next system reset clears LK.
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return TRGMUX EXTOUT0 register lock
 *         - 0b : Register can be written.
 *         - 1b : Register cannot be written until the next system Reset.
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetExtOut0Lk(const TrgMuxRegType *obj)
{
    return ((obj->EXTOUT0 & TRGMUX_EXTOUT0_LK_MASK) >> TRGMUX_EXTOUT0_LK_SHIFT);
}

/*! \brief Sets the TRGMUX EXTOUT0 register lock
 *
 * This function sets the TRGMUX EXTOUT0 register lock.
 * This bit shows whether the register can be written or not.
 * The LK bit can only be written once after any system reset.
 * Once LK is set, the SELx bits in this TRGMUX register cannot be changed until the next system reset clears LK.
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of TRGMUX EXTOUT0 register lock
 *                    - 0b : Register can be written.
 *                    - 1b : Register cannot be written until the next system Reset.
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetExtOut0Lk(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->EXTOUT0;

    tmp &= ~TRGMUX_EXTOUT0_LK_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_EXTOUT0_LK_SHIFT)) & TRGMUX_EXTOUT0_LK_MASK);
    obj->EXTOUT0 = tmp;
}

/*! \brief Gets the Selected source for output 3 of this module
 *
 * This function gets the current Selected source for output 3 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 3 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetExtOut0Sel3(const TrgMuxRegType *obj)
{
    return ((obj->EXTOUT0 & TRGMUX_EXTOUT0_SEL3_MASK) >> TRGMUX_EXTOUT0_SEL3_SHIFT);
}

/*! \brief Sets the Selected source for output 3 of this module
 *
 * This function sets the Selected source for output 3 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 3 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetExtOut0Sel3(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->EXTOUT0;

    tmp &= ~TRGMUX_EXTOUT0_SEL3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_EXTOUT0_SEL3_SHIFT)) & TRGMUX_EXTOUT0_SEL3_MASK);
    obj->EXTOUT0 = tmp;
}

/*! \brief Gets the Selected source for output 2 of this module
 *
 * This function gets the current Selected source for output 2 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 2 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetExtOut0Sel2(const TrgMuxRegType *obj)
{
    return ((obj->EXTOUT0 & TRGMUX_EXTOUT0_SEL2_MASK) >> TRGMUX_EXTOUT0_SEL2_SHIFT);
}

/*! \brief Sets the Selected source for output 2 of this module
 *
 * This function sets the Selected source for output 2 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 2 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetExtOut0Sel2(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->EXTOUT0;

    tmp &= ~TRGMUX_EXTOUT0_SEL2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_EXTOUT0_SEL2_SHIFT)) & TRGMUX_EXTOUT0_SEL2_MASK);
    obj->EXTOUT0 = tmp;
}

/*! \brief Gets the Selected source for output 1 of this module
 *
 * This function gets the current Selected source for output 1 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 1 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetExtOut0Sel1(const TrgMuxRegType *obj)
{
    return ((obj->EXTOUT0 & TRGMUX_EXTOUT0_SEL1_MASK) >> TRGMUX_EXTOUT0_SEL1_SHIFT);
}

/*! \brief Sets the Selected source for output 1 of this module
 *
 * This function sets the Selected source for output 1 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 1 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetExtOut0Sel1(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->EXTOUT0;

    tmp &= ~TRGMUX_EXTOUT0_SEL1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_EXTOUT0_SEL1_SHIFT)) & TRGMUX_EXTOUT0_SEL1_MASK);
    obj->EXTOUT0 = tmp;
}

/*! \brief Gets the Selected source for output 0 of this module
 *
 * This function gets the current Selected source for output 0 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 0 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetExtOut0Sel0(const TrgMuxRegType *obj)
{
    return ((obj->EXTOUT0 & TRGMUX_EXTOUT0_SEL0_MASK) >> TRGMUX_EXTOUT0_SEL0_SHIFT);
}

/*! \brief Sets the Selected source for output 0 of this module
 *
 * This function sets the Selected source for output 0 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 0 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetExtOut0Sel0(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->EXTOUT0;

    tmp &= ~TRGMUX_EXTOUT0_SEL0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_EXTOUT0_SEL0_SHIFT)) & TRGMUX_EXTOUT0_SEL0_MASK);
    obj->EXTOUT0 = tmp;
}

/*! \brief Gets the TRGMUX EXTOUT1 register lock
 *
 * This function gets the current TRGMUX EXTOUT1 register lock.
 * This bit shows whether the register can be written or not.
 * The LK bit can only be written once after any system reset.
 * Once LK is set, the SELx bits in this TRGMUX register cannot be changed until the next system reset clears LK.
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return TRGMUX EXTOUT1 register lock
 *         - 0b : Register can be written.
 *         - 1b : Register cannot be written until the next system Reset.
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetExtOut1Lk(const TrgMuxRegType *obj)
{
    return ((obj->EXTOUT1 & TRGMUX_EXTOUT1_LK_MASK) >> TRGMUX_EXTOUT1_LK_SHIFT);
}

/*! \brief Sets the TRGMUX EXTOUT1 register lock
 *
 * This function sets the TRGMUX EXTOUT1 register lock.
 * This bit shows whether the register can be written or not.
 * The LK bit can only be written once after any system reset.
 * Once LK is set, the SELx bits in this TRGMUX register cannot be changed until the next system reset clears LK.
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of TRGMUX EXTOUT1 register lock
 *                    - 0b : Register can be written.
 *                    - 1b : Register cannot be written until the next system Reset.
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetExtOut1Lk(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->EXTOUT1;

    tmp &= ~TRGMUX_EXTOUT1_LK_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_EXTOUT1_LK_SHIFT)) & TRGMUX_EXTOUT1_LK_MASK);
    obj->EXTOUT1 = tmp;
}

/*! \brief Gets the Selected source for output 3 of this module
 *
 * This function gets the current Selected source for output 3 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 3 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetExtOut1Sel3(const TrgMuxRegType *obj)
{
    return ((obj->EXTOUT1 & TRGMUX_EXTOUT1_SEL3_MASK) >> TRGMUX_EXTOUT1_SEL3_SHIFT);
}

/*! \brief Sets the Selected source for output 3 of this module
 *
 * This function sets the Selected source for output 3 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 3 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetExtOut1Sel3(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->EXTOUT1;

    tmp &= ~TRGMUX_EXTOUT1_SEL3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_EXTOUT1_SEL3_SHIFT)) & TRGMUX_EXTOUT1_SEL3_MASK);
    obj->EXTOUT1 = tmp;
}

/*! \brief Gets the Selected source for output 2 of this module
 *
 * This function gets the current Selected source for output 2 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 2 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetExtOut1Sel2(const TrgMuxRegType *obj)
{
    return ((obj->EXTOUT1 & TRGMUX_EXTOUT1_SEL2_MASK) >> TRGMUX_EXTOUT1_SEL2_SHIFT);
}

/*! \brief Sets the Selected source for output 2 of this module
 *
 * This function sets the Selected source for output 2 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 2 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetExtOut1Sel2(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->EXTOUT1;

    tmp &= ~TRGMUX_EXTOUT1_SEL2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_EXTOUT1_SEL2_SHIFT)) & TRGMUX_EXTOUT1_SEL2_MASK);
    obj->EXTOUT1 = tmp;
}

/*! \brief Gets the Selected source for output 1 of this module
 *
 * This function gets the current Selected source for output 1 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 1 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetExtOut1Sel1(const TrgMuxRegType *obj)
{
    return ((obj->EXTOUT1 & TRGMUX_EXTOUT1_SEL1_MASK) >> TRGMUX_EXTOUT1_SEL1_SHIFT);
}

/*! \brief Sets the Selected source for output 1 of this module
 *
 * This function sets the Selected source for output 1 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 1 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetExtOut1Sel1(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->EXTOUT1;

    tmp &= ~TRGMUX_EXTOUT1_SEL1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_EXTOUT1_SEL1_SHIFT)) & TRGMUX_EXTOUT1_SEL1_MASK);
    obj->EXTOUT1 = tmp;
}

/*! \brief Gets the Selected source for output 0 of this module
 *
 * This function gets the current Selected source for output 0 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 0 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetExtOut1Sel0(const TrgMuxRegType *obj)
{
    return ((obj->EXTOUT1 & TRGMUX_EXTOUT1_SEL0_MASK) >> TRGMUX_EXTOUT1_SEL0_SHIFT);
}

/*! \brief Sets the Selected source for output 0 of this module
 *
 * This function sets the Selected source for output 0 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 0 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetExtOut1Sel0(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->EXTOUT1;

    tmp &= ~TRGMUX_EXTOUT1_SEL0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_EXTOUT1_SEL0_SHIFT)) & TRGMUX_EXTOUT1_SEL0_MASK);
    obj->EXTOUT1 = tmp;
}

/*! \brief Gets the TRGMUX ADC0 register lock
 *
 * This function gets the current TRGMUX ADC0 register lock.
 * This bit shows whether the register can be written or not.
 * The LK bit can only be written once after any system reset.
 * Once LK is set, the SELx bits in this TRGMUX register cannot be changed until the next system reset clears LK.
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return TRGMUX ADC0 register lock
 *         - 0b : Register can be written.
 *         - 1b : Register cannot be written until the next system Reset.
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetAdc0Lk(const TrgMuxRegType *obj)
{
    return ((obj->ADC0 & TRGMUX_ADC0_LK_MASK) >> TRGMUX_ADC0_LK_SHIFT);
}

/*! \brief Sets the TRGMUX ADC0 register lock
 *
 * This function sets the TRGMUX ADC0 register lock.
 * This bit shows whether the register can be written or not.
 * The LK bit can only be written once after any system reset.
 * Once LK is set, the SELx bits in this TRGMUX register cannot be changed until the next system reset clears LK.
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of TRGMUX ADC0 register lock
 *                    - 0b : Register can be written.
 *                    - 1b : Register cannot be written until the next system Reset.
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetAdc0Lk(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->ADC0;

    tmp &= ~TRGMUX_ADC0_LK_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_ADC0_LK_SHIFT)) & TRGMUX_ADC0_LK_MASK);
    obj->ADC0 = tmp;
}

/*! \brief Gets the Selected source for output 3 of this module
 *
 * This function gets the current Selected source for output 3 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 3 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetAdc0Sel3(const TrgMuxRegType *obj)
{
    return ((obj->ADC0 & TRGMUX_ADC0_SEL3_MASK) >> TRGMUX_ADC0_SEL3_SHIFT);
}

/*! \brief Sets the Selected source for output 3 of this module
 *
 * This function sets the Selected source for output 3 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 3 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetAdc0Sel3(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->ADC0;

    tmp &= ~TRGMUX_ADC0_SEL3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_ADC0_SEL3_SHIFT)) & TRGMUX_ADC0_SEL3_MASK);
    obj->ADC0 = tmp;
}

/*! \brief Gets the Selected source for output 2 of this module
 *
 * This function gets the current Selected source for output 2 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 2 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetAdc0Sel2(const TrgMuxRegType *obj)
{
    return ((obj->ADC0 & TRGMUX_ADC0_SEL2_MASK) >> TRGMUX_ADC0_SEL2_SHIFT);
}

/*! \brief Sets the Selected source for output 2 of this module
 *
 * This function sets the Selected source for output 2 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 2 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetAdc0Sel2(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->ADC0;

    tmp &= ~TRGMUX_ADC0_SEL2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_ADC0_SEL2_SHIFT)) & TRGMUX_ADC0_SEL2_MASK);
    obj->ADC0 = tmp;
}

/*! \brief Gets the Selected source for output 1 of this module
 *
 * This function gets the current Selected source for output 1 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 1 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetAdc0Sel1(const TrgMuxRegType *obj)
{
    return ((obj->ADC0 & TRGMUX_ADC0_SEL1_MASK) >> TRGMUX_ADC0_SEL1_SHIFT);
}

/*! \brief Sets the Selected source for output 1 of this module
 *
 * This function sets the Selected source for output 1 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 1 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetAdc0Sel1(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->ADC0;

    tmp &= ~TRGMUX_ADC0_SEL1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_ADC0_SEL1_SHIFT)) & TRGMUX_ADC0_SEL1_MASK);
    obj->ADC0 = tmp;
}

/*! \brief Gets the Selected source for output 0 of this module
 *
 * This function gets the current Selected source for output 0 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 0 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetAdc0Sel0(const TrgMuxRegType *obj)
{
    return ((obj->ADC0 & TRGMUX_ADC0_SEL0_MASK) >> TRGMUX_ADC0_SEL0_SHIFT);
}

/*! \brief Sets the Selected source for output 0 of this module
 *
 * This function sets the Selected source for output 0 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 0 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetAdc0Sel0(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->ADC0;

    tmp &= ~TRGMUX_ADC0_SEL0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_ADC0_SEL0_SHIFT)) & TRGMUX_ADC0_SEL0_MASK);
    obj->ADC0 = tmp;
}

/*! \brief Gets the TRGMUX ADC1 register lock
 *
 * This function gets the current TRGMUX ADC1 register lock.
 * This bit shows whether the register can be written or not.
 * The LK bit can only be written once after any system reset.
 * Once LK is set, the SELx bits in this TRGMUX register cannot be changed until the next system reset clears LK.
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return TRGMUX ADC1 register lock
 *         - 0b : Register can be written.
 *         - 1b : Register cannot be written until the next system Reset.
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetAdc1Lk(const TrgMuxRegType *obj)
{
    return ((obj->ADC1 & TRGMUX_ADC1_LK_MASK) >> TRGMUX_ADC1_LK_SHIFT);
}

/*! \brief Sets the TRGMUX ADC1 register lock
 *
 * This function sets the TRGMUX ADC1 register lock.
 * This bit shows whether the register can be written or not.
 * The LK bit can only be written once after any system reset.
 * Once LK is set, the SELx bits in this TRGMUX register cannot be changed until the next system reset clears LK.
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of TRGMUX ADC1 register lock
 *                    - 0b : Register can be written.
 *                    - 1b : Register cannot be written until the next system Reset.
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetAdc1Lk(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->ADC1;

    tmp &= ~TRGMUX_ADC1_LK_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_ADC1_LK_SHIFT)) & TRGMUX_ADC1_LK_MASK);
    obj->ADC1 = tmp;
}

/*! \brief Gets the Selected source for output 3 of this module
 *
 * This function gets the current Selected source for output 3 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 3 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetAdc1Sel3(const TrgMuxRegType *obj)
{
    return ((obj->ADC1 & TRGMUX_ADC1_SEL3_MASK) >> TRGMUX_ADC1_SEL3_SHIFT);
}

/*! \brief Sets the Selected source for output 3 of this module
 *
 * This function sets the Selected source for output 3 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 3 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetAdc1Sel3(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->ADC1;

    tmp &= ~TRGMUX_ADC1_SEL3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_ADC1_SEL3_SHIFT)) & TRGMUX_ADC1_SEL3_MASK);
    obj->ADC1 = tmp;
}

/*! \brief Gets the Selected source for output 2 of this module
 *
 * This function gets the current Selected source for output 2 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 2 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetAdc1Sel2(const TrgMuxRegType *obj)
{
    return ((obj->ADC1 & TRGMUX_ADC1_SEL2_MASK) >> TRGMUX_ADC1_SEL2_SHIFT);
}

/*! \brief Sets the Selected source for output 2 of this module
 *
 * This function sets the Selected source for output 2 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 2 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetAdc1Sel2(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->ADC1;

    tmp &= ~TRGMUX_ADC1_SEL2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_ADC1_SEL2_SHIFT)) & TRGMUX_ADC1_SEL2_MASK);
    obj->ADC1 = tmp;
}

/*! \brief Gets the Selected source for output 1 of this module
 *
 * This function gets the current Selected source for output 1 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 1 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetAdc1Sel1(const TrgMuxRegType *obj)
{
    return ((obj->ADC1 & TRGMUX_ADC1_SEL1_MASK) >> TRGMUX_ADC1_SEL1_SHIFT);
}

/*! \brief Sets the Selected source for output 1 of this module
 *
 * This function sets the Selected source for output 1 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 1 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetAdc1Sel1(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->ADC1;

    tmp &= ~TRGMUX_ADC1_SEL1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_ADC1_SEL1_SHIFT)) & TRGMUX_ADC1_SEL1_MASK);
    obj->ADC1 = tmp;
}

/*! \brief Gets the Selected source for output 0 of this module
 *
 * This function gets the current Selected source for output 0 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 0 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetAdc1Sel0(const TrgMuxRegType *obj)
{
    return ((obj->ADC1 & TRGMUX_ADC1_SEL0_MASK) >> TRGMUX_ADC1_SEL0_SHIFT);
}

/*! \brief Sets the Selected source for output 0 of this module
 *
 * This function sets the Selected source for output 0 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 0 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetAdc1Sel0(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->ADC1;

    tmp &= ~TRGMUX_ADC1_SEL0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_ADC1_SEL0_SHIFT)) & TRGMUX_ADC1_SEL0_MASK);
    obj->ADC1 = tmp;
}

/*! \brief Gets the TRGMUX CMP register lock
 *
 * This function gets the current TRGMUX CMP register lock.
 * This bit shows whether the register can be written or not.
 * The LK bit can only be written once after any system reset.
 * Once LK is set, the SELx bits in this TRGMUX register cannot be changed until the next system reset clears LK.
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return TRGMUX CMP register lock
 *         - 0b : Register can be written.
 *         - 1b : Register cannot be written until the next system Reset.
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetCmpLk(const TrgMuxRegType *obj)
{
    return ((obj->CMP & TRGMUX_CMP_LK_MASK) >> TRGMUX_CMP_LK_SHIFT);
}

/*! \brief Sets the TRGMUX CMP register lock
 *
 * This function sets the TRGMUX CMP register lock.
 * This bit shows whether the register can be written or not.
 * The LK bit can only be written once after any system reset.
 * Once LK is set, the SELx bits in this TRGMUX register cannot be changed until the next system reset clears LK.
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of TRGMUX CMP register lock
 *                    - 0b : Register can be written.
 *                    - 1b : Register cannot be written until the next system Reset.
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetCmpLk(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CMP;

    tmp &= ~TRGMUX_CMP_LK_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_CMP_LK_SHIFT)) & TRGMUX_CMP_LK_MASK);
    obj->CMP = tmp;
}

/*! \brief Gets the Selected source for output 0 of this module
 *
 * This function gets the current Selected source for output 0 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 0 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetCmpSel0(const TrgMuxRegType *obj)
{
    return ((obj->CMP & TRGMUX_CMP_SEL0_MASK) >> TRGMUX_CMP_SEL0_SHIFT);
}

/*! \brief Sets the Selected source for output 0 of this module
 *
 * This function sets the Selected source for output 0 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 0 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetCmpSel0(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CMP;

    tmp &= ~TRGMUX_CMP_SEL0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_CMP_SEL0_SHIFT)) & TRGMUX_CMP_SEL0_MASK);
    obj->CMP = tmp;
}

/*! \brief Gets the TRGMUX MFT0 register lock
 *
 * This function gets the current TRGMUX MFT0 register lock.
 * This bit shows whether the register can be written or not.
 * The LK bit can only be written once after any system reset.
 * Once LK is set, the SELx bits in this TRGMUX register cannot be changed until the next system reset clears LK.
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return TRGMUX MFT0 register lock
 *         - 0b : Register can be written.
 *         - 1b : Register cannot be written until the next system Reset.
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetMft0Lk(const TrgMuxRegType *obj)
{
    return ((obj->MFT0 & TRGMUX_MFT0_LK_MASK) >> TRGMUX_MFT0_LK_SHIFT);
}

/*! \brief Sets the TRGMUX MFT0 register lock
 *
 * This function sets the TRGMUX MFT0 register lock.
 * This bit shows whether the register can be written or not.
 * The LK bit can only be written once after any system reset.
 * Once LK is set, the SELx bits in this TRGMUX register cannot be changed until the next system reset clears LK.
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of TRGMUX MFT0 register lock
 *                    - 0b : Register can be written.
 *                    - 1b : Register cannot be written until the next system Reset.
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetMft0Lk(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT0;

    tmp &= ~TRGMUX_MFT0_LK_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_MFT0_LK_SHIFT)) & TRGMUX_MFT0_LK_MASK);
    obj->MFT0 = tmp;
}

/*! \brief Gets the Selected source for output 3 of this module
 *
 * This function gets the current Selected source for output 3 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 3 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetMft0Sel3(const TrgMuxRegType *obj)
{
    return ((obj->MFT0 & TRGMUX_MFT0_SEL3_MASK) >> TRGMUX_MFT0_SEL3_SHIFT);
}

/*! \brief Sets the Selected source for output 3 of this module
 *
 * This function sets the Selected source for output 3 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 3 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetMft0Sel3(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT0;

    tmp &= ~TRGMUX_MFT0_SEL3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_MFT0_SEL3_SHIFT)) & TRGMUX_MFT0_SEL3_MASK);
    obj->MFT0 = tmp;
}

/*! \brief Gets the Selected source for output 2 of this module
 *
 * This function gets the current Selected source for output 2 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 2 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetMft0Sel2(const TrgMuxRegType *obj)
{
    return ((obj->MFT0 & TRGMUX_MFT0_SEL2_MASK) >> TRGMUX_MFT0_SEL2_SHIFT);
}

/*! \brief Sets the Selected source for output 2 of this module
 *
 * This function sets the Selected source for output 2 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 2 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetMft0Sel2(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT0;

    tmp &= ~TRGMUX_MFT0_SEL2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_MFT0_SEL2_SHIFT)) & TRGMUX_MFT0_SEL2_MASK);
    obj->MFT0 = tmp;
}

/*! \brief Gets the Selected source for output 1 of this module
 *
 * This function gets the current Selected source for output 1 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 1 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetMft0Sel1(const TrgMuxRegType *obj)
{
    return ((obj->MFT0 & TRGMUX_MFT0_SEL1_MASK) >> TRGMUX_MFT0_SEL1_SHIFT);
}

/*! \brief Sets the Selected source for output 1 of this module
 *
 * This function sets the Selected source for output 1 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 1 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetMft0Sel1(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT0;

    tmp &= ~TRGMUX_MFT0_SEL1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_MFT0_SEL1_SHIFT)) & TRGMUX_MFT0_SEL1_MASK);
    obj->MFT0 = tmp;
}

/*! \brief Gets the Selected source for output 0 of this module
 *
 * This function gets the current Selected source for output 0 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 0 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetMft0Sel0(const TrgMuxRegType *obj)
{
    return ((obj->MFT0 & TRGMUX_MFT0_SEL0_MASK) >> TRGMUX_MFT0_SEL0_SHIFT);
}

/*! \brief Sets the Selected source for output 0 of this module
 *
 * This function sets the Selected source for output 0 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 0 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetMft0Sel0(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT0;

    tmp &= ~TRGMUX_MFT0_SEL0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_MFT0_SEL0_SHIFT)) & TRGMUX_MFT0_SEL0_MASK);
    obj->MFT0 = tmp;
}

/*! \brief Gets the TRGMUX MFT1 register lock
 *
 * This function gets the current TRGMUX MFT1 register lock.
 * This bit shows whether the register can be written or not.
 * The LK bit can only be written once after any system reset.
 * Once LK is set, the SELx bits in this TRGMUX register cannot be changed until the next system reset clears LK.
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return TRGMUX MFT1 register lock
 *         - 0b : Register can be written.
 *         - 1b : Register cannot be written until the next system Reset.
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetMft1Lk(const TrgMuxRegType *obj)
{
    return ((obj->MFT1 & TRGMUX_MFT1_LK_MASK) >> TRGMUX_MFT1_LK_SHIFT);
}

/*! \brief Sets the TRGMUX MFT1 register lock
 *
 * This function sets the TRGMUX MFT1 register lock.
 * This bit shows whether the register can be written or not.
 * The LK bit can only be written once after any system reset.
 * Once LK is set, the SELx bits in this TRGMUX register cannot be changed until the next system reset clears LK.
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of TRGMUX MFT1 register lock
 *                    - 0b : Register can be written.
 *                    - 1b : Register cannot be written until the next system Reset.
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetMft1Lk(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT1;

    tmp &= ~TRGMUX_MFT1_LK_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_MFT1_LK_SHIFT)) & TRGMUX_MFT1_LK_MASK);
    obj->MFT1 = tmp;
}

/*! \brief Gets the Selected source for output 3 of this module
 *
 * This function gets the current Selected source for output 3 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 3 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetMft1Sel3(const TrgMuxRegType *obj)
{
    return ((obj->MFT1 & TRGMUX_MFT1_SEL3_MASK) >> TRGMUX_MFT1_SEL3_SHIFT);
}

/*! \brief Sets the Selected source for output 3 of this module
 *
 * This function sets the Selected source for output 3 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 3 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetMft1Sel3(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT1;

    tmp &= ~TRGMUX_MFT1_SEL3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_MFT1_SEL3_SHIFT)) & TRGMUX_MFT1_SEL3_MASK);
    obj->MFT1 = tmp;
}

/*! \brief Gets the Selected source for output 2 of this module
 *
 * This function gets the current Selected source for output 2 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 2 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetMft1Sel2(const TrgMuxRegType *obj)
{
    return ((obj->MFT1 & TRGMUX_MFT1_SEL2_MASK) >> TRGMUX_MFT1_SEL2_SHIFT);
}

/*! \brief Sets the Selected source for output 2 of this module
 *
 * This function sets the Selected source for output 2 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 2 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetMft1Sel2(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT1;

    tmp &= ~TRGMUX_MFT1_SEL2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_MFT1_SEL2_SHIFT)) & TRGMUX_MFT1_SEL2_MASK);
    obj->MFT1 = tmp;
}

/*! \brief Gets the Selected source for output 1 of this module
 *
 * This function gets the current Selected source for output 1 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 1 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetMft1Sel1(const TrgMuxRegType *obj)
{
    return ((obj->MFT1 & TRGMUX_MFT1_SEL1_MASK) >> TRGMUX_MFT1_SEL1_SHIFT);
}

/*! \brief Sets the Selected source for output 1 of this module
 *
 * This function sets the Selected source for output 1 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 1 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetMft1Sel1(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT1;

    tmp &= ~TRGMUX_MFT1_SEL1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_MFT1_SEL1_SHIFT)) & TRGMUX_MFT1_SEL1_MASK);
    obj->MFT1 = tmp;
}

/*! \brief Gets the Selected source for output 0 of this module
 *
 * This function gets the current Selected source for output 0 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 0 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetMft1Sel0(const TrgMuxRegType *obj)
{
    return ((obj->MFT1 & TRGMUX_MFT1_SEL0_MASK) >> TRGMUX_MFT1_SEL0_SHIFT);
}

/*! \brief Sets the Selected source for output 0 of this module
 *
 * This function sets the Selected source for output 0 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 0 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetMft1Sel0(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT1;

    tmp &= ~TRGMUX_MFT1_SEL0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_MFT1_SEL0_SHIFT)) & TRGMUX_MFT1_SEL0_MASK);
    obj->MFT1 = tmp;
}

/*! \brief Gets the TRGMUX MFT2 register lock
 *
 * This function gets the current TRGMUX MFT2 register lock.
 * This bit shows whether the register can be written or not.
 * The LK bit can only be written once after any system reset.
 * Once LK is set, the SELx bits in this TRGMUX register cannot be changed until the next system reset clears LK.
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return TRGMUX MFT2 register lock
 *         - 0b : Register can be written.
 *         - 1b : Register cannot be written until the next system Reset.
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetMft2Lk(const TrgMuxRegType *obj)
{
    return ((obj->MFT2 & TRGMUX_MFT2_LK_MASK) >> TRGMUX_MFT2_LK_SHIFT);
}

/*! \brief Sets the TRGMUX MFT2 register lock
 *
 * This function sets the TRGMUX MFT2 register lock.
 * This bit shows whether the register can be written or not.
 * The LK bit can only be written once after any system reset.
 * Once LK is set, the SELx bits in this TRGMUX register cannot be changed until the next system reset clears LK.
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of TRGMUX MFT2 register lock
 *                    - 0b : Register can be written.
 *                    - 1b : Register cannot be written until the next system Reset.
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetMft2Lk(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT2;

    tmp &= ~TRGMUX_MFT2_LK_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_MFT2_LK_SHIFT)) & TRGMUX_MFT2_LK_MASK);
    obj->MFT2 = tmp;
}

/*! \brief Gets the Selected source for output 3 of this module
 *
 * This function gets the current Selected source for output 3 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 3 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetMft2Sel3(const TrgMuxRegType *obj)
{
    return ((obj->MFT2 & TRGMUX_MFT2_SEL3_MASK) >> TRGMUX_MFT2_SEL3_SHIFT);
}

/*! \brief Sets the Selected source for output 3 of this module
 *
 * This function sets the Selected source for output 3 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 3 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetMft2Sel3(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT2;

    tmp &= ~TRGMUX_MFT2_SEL3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_MFT2_SEL3_SHIFT)) & TRGMUX_MFT2_SEL3_MASK);
    obj->MFT2 = tmp;
}

/*! \brief Gets the Selected source for output 2 of this module
 *
 * This function gets the current Selected source for output 2 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 2 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetMft2Sel2(const TrgMuxRegType *obj)
{
    return ((obj->MFT2 & TRGMUX_MFT2_SEL2_MASK) >> TRGMUX_MFT2_SEL2_SHIFT);
}

/*! \brief Sets the Selected source for output 2 of this module
 *
 * This function sets the Selected source for output 2 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 2 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetMft2Sel2(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT2;

    tmp &= ~TRGMUX_MFT2_SEL2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_MFT2_SEL2_SHIFT)) & TRGMUX_MFT2_SEL2_MASK);
    obj->MFT2 = tmp;
}

/*! \brief Gets the Selected source for output 1 of this module
 *
 * This function gets the current Selected source for output 1 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 1 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetMft2Sel1(const TrgMuxRegType *obj)
{
    return ((obj->MFT2 & TRGMUX_MFT2_SEL1_MASK) >> TRGMUX_MFT2_SEL1_SHIFT);
}

/*! \brief Sets the Selected source for output 1 of this module
 *
 * This function sets the Selected source for output 1 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 1 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetMft2Sel1(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT2;

    tmp &= ~TRGMUX_MFT2_SEL1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_MFT2_SEL1_SHIFT)) & TRGMUX_MFT2_SEL1_MASK);
    obj->MFT2 = tmp;
}

/*! \brief Gets the Selected source for output 0 of this module
 *
 * This function gets the current Selected source for output 0 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 0 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetMft2Sel0(const TrgMuxRegType *obj)
{
    return ((obj->MFT2 & TRGMUX_MFT2_SEL0_MASK) >> TRGMUX_MFT2_SEL0_SHIFT);
}

/*! \brief Sets the Selected source for output 0 of this module
 *
 * This function sets the Selected source for output 0 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 0 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetMft2Sel0(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT2;

    tmp &= ~TRGMUX_MFT2_SEL0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_MFT2_SEL0_SHIFT)) & TRGMUX_MFT2_SEL0_MASK);
    obj->MFT2 = tmp;
}

/*! \brief Gets the TRGMUX MFT3 register lock
 *
 * This function gets the current TRGMUX MFT3 register lock.
 * This bit shows whether the register can be written or not.
 * The LK bit can only be written once after any system reset.
 * Once LK is set, the SELx bits in this TRGMUX register cannot be changed until the next system reset clears LK.
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return TRGMUX MFT3 register lock
 *         - 0b : Register can be written.
 *         - 1b : Register cannot be written until the next system Reset.
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetMft3Lk(const TrgMuxRegType *obj)
{
    return ((obj->MFT3 & TRGMUX_MFT3_LK_MASK) >> TRGMUX_MFT3_LK_SHIFT);
}

/*! \brief Sets the TRGMUX MFT3 register lock
 *
 * This function sets the TRGMUX MFT3 register lock.
 * This bit shows whether the register can be written or not.
 * The LK bit can only be written once after any system reset.
 * Once LK is set, the SELx bits in this TRGMUX register cannot be changed until the next system reset clears LK.
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of TRGMUX MFT3 register lock
 *                    - 0b : Register can be written.
 *                    - 1b : Register cannot be written until the next system Reset.
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetMft3Lk(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT3;

    tmp &= ~TRGMUX_MFT3_LK_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_MFT3_LK_SHIFT)) & TRGMUX_MFT3_LK_MASK);
    obj->MFT3 = tmp;
}

/*! \brief Gets the Selected source for output 3 of this module
 *
 * This function gets the current Selected source for output 3 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 3 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetMft3Sel3(const TrgMuxRegType *obj)
{
    return ((obj->MFT3 & TRGMUX_MFT3_SEL3_MASK) >> TRGMUX_MFT3_SEL3_SHIFT);
}

/*! \brief Sets the Selected source for output 3 of this module
 *
 * This function sets the Selected source for output 3 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 3 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetMft3Sel3(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT3;

    tmp &= ~TRGMUX_MFT3_SEL3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_MFT3_SEL3_SHIFT)) & TRGMUX_MFT3_SEL3_MASK);
    obj->MFT3 = tmp;
}

/*! \brief Gets the Selected source for output 2 of this module
 *
 * This function gets the current Selected source for output 2 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 2 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetMft3Sel2(const TrgMuxRegType *obj)
{
    return ((obj->MFT3 & TRGMUX_MFT3_SEL2_MASK) >> TRGMUX_MFT3_SEL2_SHIFT);
}

/*! \brief Sets the Selected source for output 2 of this module
 *
 * This function sets the Selected source for output 2 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 2 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetMft3Sel2(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT3;

    tmp &= ~TRGMUX_MFT3_SEL2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_MFT3_SEL2_SHIFT)) & TRGMUX_MFT3_SEL2_MASK);
    obj->MFT3 = tmp;
}

/*! \brief Gets the Selected source for output 1 of this module
 *
 * This function gets the current Selected source for output 1 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 1 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetMft3Sel1(const TrgMuxRegType *obj)
{
    return ((obj->MFT3 & TRGMUX_MFT3_SEL1_MASK) >> TRGMUX_MFT3_SEL1_SHIFT);
}

/*! \brief Sets the Selected source for output 1 of this module
 *
 * This function sets the Selected source for output 1 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 1 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetMft3Sel1(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT3;

    tmp &= ~TRGMUX_MFT3_SEL1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_MFT3_SEL1_SHIFT)) & TRGMUX_MFT3_SEL1_MASK);
    obj->MFT3 = tmp;
}

/*! \brief Gets the Selected source for output 0 of this module
 *
 * This function gets the current Selected source for output 0 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 0 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetMft3Sel0(const TrgMuxRegType *obj)
{
    return ((obj->MFT3 & TRGMUX_MFT3_SEL0_MASK) >> TRGMUX_MFT3_SEL0_SHIFT);
}

/*! \brief Sets the Selected source for output 0 of this module
 *
 * This function sets the Selected source for output 0 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 0 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetMft3Sel0(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT3;

    tmp &= ~TRGMUX_MFT3_SEL0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_MFT3_SEL0_SHIFT)) & TRGMUX_MFT3_SEL0_MASK);
    obj->MFT3 = tmp;
}

/*! \brief Gets the TRGMUX register lock
 *
 * This function gets the current TRGMUX register lock.
 * This bit shows whether the register can be written or not.
 * The LK bit can only be written once after any system reset.
 * Once LK is set, the SELx bits in this TRGMUX register cannot be changed until the next system reset clears LK.
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return TRGMUX register lock
 *         - 0b : Register can be written.
 *         - 1b : Register cannot be written until the next system Reset.
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetMft4Lk(const TrgMuxRegType *obj)
{
    return ((obj->MFT4 & TRGMUX_MFT4_LK_MASK) >> TRGMUX_MFT4_LK_SHIFT);
}

/*! \brief Sets the TRGMUX register lock
 *
 * This function sets the TRGMUX register lock.
 * This bit shows whether the register can be written or not.
 * The LK bit can only be written once after any system reset.
 * Once LK is set, the SELx bits in this TRGMUX register cannot be changed until the next system reset clears LK.
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of TRGMUX register lock
 *                    - 0b : Register can be written.
 *                    - 1b : Register cannot be written until the next system Reset.
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetMft4Lk(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT4;

    tmp &= ~TRGMUX_MFT4_LK_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_MFT4_LK_SHIFT)) & TRGMUX_MFT4_LK_MASK);
    obj->MFT4 = tmp;
}

/*! \brief Gets the Selected source for output 3 of this module
 *
 * This function gets the current Selected source for output 3 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 3 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetMft4Sel3(const TrgMuxRegType *obj)
{
    return ((obj->MFT4 & TRGMUX_MFT4_SEL3_MASK) >> TRGMUX_MFT4_SEL3_SHIFT);
}

/*! \brief Sets the Selected source for output 3 of this module
 *
 * This function sets the Selected source for output 3 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 3 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetMft4Sel3(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT4;

    tmp &= ~TRGMUX_MFT4_SEL3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_MFT4_SEL3_SHIFT)) & TRGMUX_MFT4_SEL3_MASK);
    obj->MFT4 = tmp;
}

/*! \brief Gets the Selected source for output 2 of this module
 *
 * This function gets the current Selected source for output 2 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 2 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetMft4Sel2(const TrgMuxRegType *obj)
{
    return ((obj->MFT4 & TRGMUX_MFT4_SEL2_MASK) >> TRGMUX_MFT4_SEL2_SHIFT);
}

/*! \brief Sets the Selected source for output 2 of this module
 *
 * This function sets the Selected source for output 2 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 2 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetMft4Sel2(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT4;

    tmp &= ~TRGMUX_MFT4_SEL2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_MFT4_SEL2_SHIFT)) & TRGMUX_MFT4_SEL2_MASK);
    obj->MFT4 = tmp;
}

/*! \brief Gets the Selected source for output 1 of this module
 *
 * This function gets the current Selected source for output 1 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 1 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetMft4Sel1(const TrgMuxRegType *obj)
{
    return ((obj->MFT4 & TRGMUX_MFT4_SEL1_MASK) >> TRGMUX_MFT4_SEL1_SHIFT);
}

/*! \brief Sets the Selected source for output 1 of this module
 *
 * This function sets the Selected source for output 1 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 1 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetMft4Sel1(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT4;

    tmp &= ~TRGMUX_MFT4_SEL1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_MFT4_SEL1_SHIFT)) & TRGMUX_MFT4_SEL1_MASK);
    obj->MFT4 = tmp;
}

/*! \brief Gets the Selected source for output 0 of this module
 *
 * This function gets the current Selected source for output 0 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 0 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetMft4Sel0(const TrgMuxRegType *obj)
{
    return ((obj->MFT4 & TRGMUX_MFT4_SEL0_MASK) >> TRGMUX_MFT4_SEL0_SHIFT);
}

/*! \brief Sets the Selected source for output 0 of this module
 *
 * This function sets the Selected source for output 0 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 0 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetMft4Sel0(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT4;

    tmp &= ~TRGMUX_MFT4_SEL0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_MFT4_SEL0_SHIFT)) & TRGMUX_MFT4_SEL0_MASK);
    obj->MFT4 = tmp;
}

/*! \brief Gets the TRGMUX register lock
 *
 * This function gets the current TRGMUX register lock.
 * This bit shows whether the register can be written or not.
 * The LK bit can only be written once after any system reset.
 * Once LK is set, the SELx bits in this TRGMUX register cannot be changed until the next system reset clears LK.
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return TRGMUX register lock
 *         - 0b : Register can be written.
 *         - 1b : Register cannot be written until the next system Reset.
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetMft5Lk(const TrgMuxRegType *obj)
{
    return ((obj->MFT5 & TRGMUX_MFT5_LK_MASK) >> TRGMUX_MFT5_LK_SHIFT);
}

/*! \brief Sets the TRGMUX register lock
 *
 * This function sets the TRGMUX register lock.
 * This bit shows whether the register can be written or not.
 * The LK bit can only be written once after any system reset.
 * Once LK is set, the SELx bits in this TRGMUX register cannot be changed until the next system reset clears LK.
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of TRGMUX register lock
 *                    - 0b : Register can be written.
 *                    - 1b : Register cannot be written until the next system Reset.
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetMft5Lk(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT5;

    tmp &= ~TRGMUX_MFT5_LK_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_MFT5_LK_SHIFT)) & TRGMUX_MFT5_LK_MASK);
    obj->MFT5 = tmp;
}

/*! \brief Gets the Selected source for output 3 of this module
 *
 * This function gets the current Selected source for output 3 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 3 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetMft5Sel3(const TrgMuxRegType *obj)
{
    return ((obj->MFT5 & TRGMUX_MFT5_SEL3_MASK) >> TRGMUX_MFT5_SEL3_SHIFT);
}

/*! \brief Sets the Selected source for output 3 of this module
 *
 * This function sets the Selected source for output 3 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 3 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetMft5Sel3(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT5;

    tmp &= ~TRGMUX_MFT5_SEL3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_MFT5_SEL3_SHIFT)) & TRGMUX_MFT5_SEL3_MASK);
    obj->MFT5 = tmp;
}

/*! \brief Gets the Selected source for output 2 of this module
 *
 * This function gets the current Selected source for output 2 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 2 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetMft5Sel2(const TrgMuxRegType *obj)
{
    return ((obj->MFT5 & TRGMUX_MFT5_SEL2_MASK) >> TRGMUX_MFT5_SEL2_SHIFT);
}

/*! \brief Sets the Selected source for output 2 of this module
 *
 * This function sets the Selected source for output 2 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 2 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetMft5Sel2(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT5;

    tmp &= ~TRGMUX_MFT5_SEL2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_MFT5_SEL2_SHIFT)) & TRGMUX_MFT5_SEL2_MASK);
    obj->MFT5 = tmp;
}

/*! \brief Gets the Selected source for output 1 of this module
 *
 * This function gets the current Selected source for output 1 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 1 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetMft5Sel1(const TrgMuxRegType *obj)
{
    return ((obj->MFT5 & TRGMUX_MFT5_SEL1_MASK) >> TRGMUX_MFT5_SEL1_SHIFT);
}

/*! \brief Sets the Selected source for output 1 of this module
 *
 * This function sets the Selected source for output 1 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 1 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetMft5Sel1(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT5;

    tmp &= ~TRGMUX_MFT5_SEL1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_MFT5_SEL1_SHIFT)) & TRGMUX_MFT5_SEL1_MASK);
    obj->MFT5 = tmp;
}

/*! \brief Gets the Selected source for output 0 of this module
 *
 * This function gets the current Selected source for output 0 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 0 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetMft5Sel0(const TrgMuxRegType *obj)
{
    return ((obj->MFT5 & TRGMUX_MFT5_SEL0_MASK) >> TRGMUX_MFT5_SEL0_SHIFT);
}

/*! \brief Sets the Selected source for output 0 of this module
 *
 * This function sets the Selected source for output 0 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 0 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetMft5Sel0(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT5;

    tmp &= ~TRGMUX_MFT5_SEL0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_MFT5_SEL0_SHIFT)) & TRGMUX_MFT5_SEL0_MASK);
    obj->MFT5 = tmp;
}

/*! \brief Gets the TRGMUX PDB0 register lock
 *
 * This function gets the current TRGMUX PDB0 register lock.
 * This bit shows whether the register can be written or not.
 * The LK bit can only be written once after any system reset.
 * Once LK is set, the SELx bits in this TRGMUX register cannot be changed until the next system reset clears LK.
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return TRGMUX PDB0 register lock
 *         - 0b : Register can be written.
 *         - 1b : Register cannot be written until the next system Reset.
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetPdb0Lk(const TrgMuxRegType *obj)
{
    return ((obj->PDB0 & TRGMUX_PDB0_LK_MASK) >> TRGMUX_PDB0_LK_SHIFT);
}

/*! \brief Sets the TRGMUX PDB0 register lock
 *
 * This function sets the TRGMUX PDB0 register lock.
 * This bit shows whether the register can be written or not.
 * The LK bit can only be written once after any system reset.
 * Once LK is set, the SELx bits in this TRGMUX register cannot be changed until the next system reset clears LK.
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of TRGMUX PDB0 register lock
 *                    - 0b : Register can be written.
 *                    - 1b : Register cannot be written until the next system Reset.
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetPdb0Lk(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PDB0;

    tmp &= ~TRGMUX_PDB0_LK_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_PDB0_LK_SHIFT)) & TRGMUX_PDB0_LK_MASK);
    obj->PDB0 = tmp;
}

/*! \brief Gets the Selected source for output 0 of this module
 *
 * This function gets the current Selected source for output 0 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 0 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetPdb0Sel0(const TrgMuxRegType *obj)
{
    return ((obj->PDB0 & TRGMUX_PDB0_SEL0_MASK) >> TRGMUX_PDB0_SEL0_SHIFT);
}

/*! \brief Sets the Selected source for output 0 of this module
 *
 * This function sets the Selected source for output 0 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 0 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetPdb0Sel0(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PDB0;

    tmp &= ~TRGMUX_PDB0_SEL0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_PDB0_SEL0_SHIFT)) & TRGMUX_PDB0_SEL0_MASK);
    obj->PDB0 = tmp;
}

/*! \brief Gets the TRGMUX PDB1 register lock
 *
 * This function gets the current TRGMUX PDB1 register lock.
 * This bit shows whether the register can be written or not.
 * The LK bit can only be written once after any system reset.
 * Once LK is set, the SELx bits in this TRGMUX register cannot be changed until the next system reset clears LK.
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return TRGMUX PDB1 register lock
 *         - 0b : Register can be written.
 *         - 1b : Register cannot be written until the next system Reset.
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetPdb1Lk(const TrgMuxRegType *obj)
{
    return ((obj->PDB1 & TRGMUX_PDB1_LK_MASK) >> TRGMUX_PDB1_LK_SHIFT);
}

/*! \brief Sets the TRGMUX PDB1 register lock
 *
 * This function sets the TRGMUX PDB1 register lock.
 * This bit shows whether the register can be written or not.
 * The LK bit can only be written once after any system reset.
 * Once LK is set, the SELx bits in this TRGMUX register cannot be changed until the next system reset clears LK.
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of TRGMUX PDB1 register lock
 *                    - 0b : Register can be written.
 *                    - 1b : Register cannot be written until the next system Reset.
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetPdb1Lk(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PDB1;

    tmp &= ~TRGMUX_PDB1_LK_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_PDB1_LK_SHIFT)) & TRGMUX_PDB1_LK_MASK);
    obj->PDB1 = tmp;
}

/*! \brief Gets the Selected source for output 0 of this module
 *
 * This function gets the current Selected source for output 0 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 0 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetPdb1Sel0(const TrgMuxRegType *obj)
{
    return ((obj->PDB1 & TRGMUX_PDB1_SEL0_MASK) >> TRGMUX_PDB1_SEL0_SHIFT);
}

/*! \brief Sets the Selected source for output 0 of this module
 *
 * This function sets the Selected source for output 0 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 0 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetPdb1Sel0(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PDB1;

    tmp &= ~TRGMUX_PDB1_SEL0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_PDB1_SEL0_SHIFT)) & TRGMUX_PDB1_SEL0_MASK);
    obj->PDB1 = tmp;
}

/*! \brief Gets the TRGMUX LPIT register lock
 *
 * This function gets the current TRGMUX LPIT register lock.
 * This bit shows whether the register can be written or not.
 * The LK bit can only be written once after any system reset.
 * Once LK is set, the SELx bits in this TRGMUX register cannot be changed until the next system reset clears LK.
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return TRGMUX LPIT register lock
 *         - 0b : Register can be written.
 *         - 1b : Register cannot be written until the next system Reset.
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetLpitLk(const TrgMuxRegType *obj)
{
    return ((obj->LPIT & TRGMUX_LPIT_LK_MASK) >> TRGMUX_LPIT_LK_SHIFT);
}

/*! \brief Sets the TRGMUX LPIT register lock
 *
 * This function sets the TRGMUX LPIT register lock.
 * This bit shows whether the register can be written or not.
 * The LK bit can only be written once after any system reset.
 * Once LK is set, the SELx bits in this TRGMUX register cannot be changed until the next system reset clears LK.
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of TRGMUX LPIT register lock
 *                    - 0b : Register can be written.
 *                    - 1b : Register cannot be written until the next system Reset.
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetLpitLk(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->LPIT;

    tmp &= ~TRGMUX_LPIT_LK_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_LPIT_LK_SHIFT)) & TRGMUX_LPIT_LK_MASK);
    obj->LPIT = tmp;
}

/*! \brief Gets the Selected source for output 3 of this module
 *
 * This function gets the current Selected source for output 3 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 3 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetLpitSel3(const TrgMuxRegType *obj)
{
    return ((obj->LPIT & TRGMUX_LPIT_SEL3_MASK) >> TRGMUX_LPIT_SEL3_SHIFT);
}

/*! \brief Sets the Selected source for output 3 of this module
 *
 * This function sets the Selected source for output 3 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 3 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetLpitSel3(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->LPIT;

    tmp &= ~TRGMUX_LPIT_SEL3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_LPIT_SEL3_SHIFT)) & TRGMUX_LPIT_SEL3_MASK);
    obj->LPIT = tmp;
}

/*! \brief Gets the Selected source for output 2 of this module
 *
 * This function gets the current Selected source for output 2 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 2 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetLpitSel2(const TrgMuxRegType *obj)
{
    return ((obj->LPIT & TRGMUX_LPIT_SEL2_MASK) >> TRGMUX_LPIT_SEL2_SHIFT);
}

/*! \brief Sets the Selected source for output 2 of this module
 *
 * This function sets the Selected source for output 2 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 2 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetLpitSel2(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->LPIT;

    tmp &= ~TRGMUX_LPIT_SEL2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_LPIT_SEL2_SHIFT)) & TRGMUX_LPIT_SEL2_MASK);
    obj->LPIT = tmp;
}

/*! \brief Gets the Selected source for output 1 of this module
 *
 * This function gets the current Selected source for output 1 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 1 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetLpitSel1(const TrgMuxRegType *obj)
{
    return ((obj->LPIT & TRGMUX_LPIT_SEL1_MASK) >> TRGMUX_LPIT_SEL1_SHIFT);
}

/*! \brief Sets the Selected source for output 1 of this module
 *
 * This function sets the Selected source for output 1 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 1 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetLpitSel1(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->LPIT;

    tmp &= ~TRGMUX_LPIT_SEL1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_LPIT_SEL1_SHIFT)) & TRGMUX_LPIT_SEL1_MASK);
    obj->LPIT = tmp;
}

/*! \brief Gets the Selected source for output 0 of this module
 *
 * This function gets the current Selected source for output 0 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 0 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetLpitSel0(const TrgMuxRegType *obj)
{
    return ((obj->LPIT & TRGMUX_LPIT_SEL0_MASK) >> TRGMUX_LPIT_SEL0_SHIFT);
}

/*! \brief Sets the Selected source for output 0 of this module
 *
 * This function sets the Selected source for output 0 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 0 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetLpitSel0(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->LPIT;

    tmp &= ~TRGMUX_LPIT_SEL0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_LPIT_SEL0_SHIFT)) & TRGMUX_LPIT_SEL0_MASK);
    obj->LPIT = tmp;
}

/*! \brief Gets the TRGMUX LPTMR register lock
 *
 * This function gets the current TRGMUX LPTMR register lock.
 * This bit shows whether the register can be written or not.
 * The LK bit can only be written once after any system reset.
 * Once LK is set, the SELx bits in this TRGMUX register cannot be changed until the next system reset clears LK.
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return TRGMUX LPTMR register lock
 *         - 0b : Register can be written.
 *         - 1b : Register cannot be written until the next system Reset.
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetLptmrLk(const TrgMuxRegType *obj)
{
    return ((obj->LPTMR & TRGMUX_LPTMR_LK_MASK) >> TRGMUX_LPTMR_LK_SHIFT);
}

/*! \brief Sets the TRGMUX LPTMR register lock
 *
 * This function sets the TRGMUX LPTMR register lock.
 * This bit shows whether the register can be written or not.
 * The LK bit can only be written once after any system reset.
 * Once LK is set, the SELx bits in this TRGMUX register cannot be changed until the next system reset clears LK.
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of TRGMUX LPTMR register lock
 *                    - 0b : Register can be written.
 *                    - 1b : Register cannot be written until the next system Reset.
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetLptmrLk(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->LPTMR;

    tmp &= ~TRGMUX_LPTMR_LK_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_LPTMR_LK_SHIFT)) & TRGMUX_LPTMR_LK_MASK);
    obj->LPTMR = tmp;
}

/*! \brief Gets the Selected source for output 0 of this module
 *
 * This function gets the current Selected source for output 0 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \return Selected source for output 0 of this module
 */
__attribute__((always_inline)) static inline uint8_t TrgMuxReg_GetLptmrSel0(const TrgMuxRegType *obj)
{
    return ((obj->LPTMR & TRGMUX_LPTMR_SEL0_MASK) >> TRGMUX_LPTMR_SEL0_SHIFT);
}

/*! \brief Sets the Selected source for output 0 of this module
 *
 * This function sets the Selected source for output 0 of this module.
 * Refer to user manual for signal encoding details
 *
 * \param[in] obj : pointer to TRGMUX register instance
 * \param[in] value : the value of Selected source for output 0 of this module
 */
__attribute__((always_inline)) static inline void TrgMuxReg_SetLptmrSel0(TrgMuxRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->LPTMR;

    tmp &= ~TRGMUX_LPTMR_SEL0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << TRGMUX_LPTMR_SEL0_SHIFT)) & TRGMUX_LPTMR_SEL0_MASK);
    obj->LPTMR = tmp;
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _TRGMUX_REG_H_ */
