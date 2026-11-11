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

#ifndef _CMP_REG_H_
#define _CMP_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the CMP Registers
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

/* CMP Register Lock Key for unlock or lock */
#define UNLOCK_KEY              (0x5f5f0101u)
#define LOCK_KEY                (0x00000000u)

/* C0 Bit Fields */
#define CMP_C0_WITHOUT_W1C_MASK (0xF9FFFFFFu)
#define CMP_C0_HYSTCTR_MASK     (0x3u)
#define CMP_C0_HYSTCTR_SHIFT    (0u)
#define CMP_C0_HYSTCTR_WIDTH    (2u)
#define CMP_C0_OFFSET_MASK      (0x4u)
#define CMP_C0_OFFSET_SHIFT     (2u)
#define CMP_C0_OFFSET_WIDTH     (1u)
#define CMP_C0_FILTER_CNT_MASK  (0x70u)
#define CMP_C0_FILTER_CNT_SHIFT (4u)
#define CMP_C0_FILTER_CNT_WIDTH (3u)
#define CMP_C0_EN_MASK          (0x100u)
#define CMP_C0_EN_SHIFT         (8u)
#define CMP_C0_EN_WIDTH         (1u)
#define CMP_C0_OPE_MASK         (0x200u)
#define CMP_C0_OPE_SHIFT        (9u)
#define CMP_C0_OPE_WIDTH        (1u)
#define CMP_C0_COS_MASK         (0x400u)
#define CMP_C0_COS_SHIFT        (10u)
#define CMP_C0_COS_WIDTH        (1u)
#define CMP_C0_INVT_MASK        (0x800u)
#define CMP_C0_INVT_SHIFT       (11u)
#define CMP_C0_INVT_WIDTH       (1u)
#define CMP_C0_PMODE_MASK       (0x1000u)
#define CMP_C0_PMODE_SHIFT      (12u)
#define CMP_C0_PMODE_WIDTH      (1u)
#define CMP_C0_WE_MASK          (0x4000u)
#define CMP_C0_WE_SHIFT         (14u)
#define CMP_C0_WE_WIDTH         (1u)
#define CMP_C0_SE_MASK          (0x8000u)
#define CMP_C0_SE_SHIFT         (15u)
#define CMP_C0_SE_WIDTH         (1u)
#define CMP_C0_FPR_MASK         (0xFF0000u)
#define CMP_C0_FPR_SHIFT        (16u)
#define CMP_C0_FPR_WIDTH        (8u)
#define CMP_C0_COUT_MASK        (0x1000000u)
#define CMP_C0_COUT_SHIFT       (24u)
#define CMP_C0_COUT_WIDTH       (1u)
#define CMP_C0_CFF_MASK         (0x2000000u)
#define CMP_C0_CFF_SHIFT        (25u)
#define CMP_C0_CFF_WIDTH        (1u)
#define CMP_C0_CFR_MASK         (0x4000000u)
#define CMP_C0_CFR_SHIFT        (26u)
#define CMP_C0_CFR_WIDTH        (1u)
#define CMP_C0_IEF_MASK         (0x8000000u)
#define CMP_C0_IEF_SHIFT        (27u)
#define CMP_C0_IEF_WIDTH        (1u)
#define CMP_C0_IER_MASK         (0x10000000u)
#define CMP_C0_IER_SHIFT        (28u)
#define CMP_C0_IER_WIDTH        (1u)
#define CMP_C0_LPFSEL_MASK      (0x60000000u)
#define CMP_C0_LPFSEL_SHIFT     (29u)
#define CMP_C0_LPFSEL_WIDTH     (2u)
#define CMP_C0_DMAEN_MASK       (0x80000000u)
#define CMP_C0_DMAEN_SHIFT      (31u)
#define CMP_C0_DMAEN_WIDTH      (1u)

/* C1 Bit Fields */
#define CMP_C1_VOSEL_MASK       (0xFFu)
#define CMP_C1_VOSEL_SHIFT      (0u)
#define CMP_C1_VOSEL_WIDTH      (8u)
#define CMP_C1_MSEL_MASK        (0x700u)
#define CMP_C1_MSEL_SHIFT       (8u)
#define CMP_C1_MSEL_WIDTH       (3u)
#define CMP_C1_PSEL_MASK        (0x3800u)
#define CMP_C1_PSEL_SHIFT       (11u)
#define CMP_C1_PSEL_WIDTH       (3u)
#define CMP_C1_VRSEL_MASK       (0x4000u)
#define CMP_C1_VRSEL_SHIFT      (14u)
#define CMP_C1_VRSEL_WIDTH      (1u)
#define CMP_C1_DACEN_MASK       (0x8000u)
#define CMP_C1_DACEN_SHIFT      (15u)
#define CMP_C1_DACEN_WIDTH      (1u)
#define CMP_C1_CHN0_MASK        (0x10000u)
#define CMP_C1_CHN0_SHIFT       (16u)
#define CMP_C1_CHN0_WIDTH       (1u)
#define CMP_C1_CHN1_MASK        (0x20000u)
#define CMP_C1_CHN1_SHIFT       (17u)
#define CMP_C1_CHN1_WIDTH       (1u)
#define CMP_C1_CHN2_MASK        (0x40000u)
#define CMP_C1_CHN2_SHIFT       (18u)
#define CMP_C1_CHN2_WIDTH       (1u)
#define CMP_C1_CHN3_MASK        (0x80000u)
#define CMP_C1_CHN3_SHIFT       (19u)
#define CMP_C1_CHN3_WIDTH       (1u)
#define CMP_C1_CHN4_MASK        (0x100000u)
#define CMP_C1_CHN4_SHIFT       (20u)
#define CMP_C1_CHN4_WIDTH       (1u)
#define CMP_C1_CHN5_MASK        (0x200000u)
#define CMP_C1_CHN5_SHIFT       (21u)
#define CMP_C1_CHN5_WIDTH       (1u)
#define CMP_C1_CHN6_MASK        (0x400000u)
#define CMP_C1_CHN6_SHIFT       (22u)
#define CMP_C1_CHN6_WIDTH       (1u)
#define CMP_C1_CHN7_MASK        (0x800000u)
#define CMP_C1_CHN7_SHIFT       (23u)
#define CMP_C1_CHN7_WIDTH       (1u)
#define CMP_C1_INNSEL_MASK      (0x3000000u)
#define CMP_C1_INNSEL_SHIFT     (24u)
#define CMP_C1_INNSEL_WIDTH     (2u)
#define CMP_C1_INPSEL_MASK      (0x18000000u)
#define CMP_C1_INPSEL_SHIFT     (27u)
#define CMP_C1_INPSEL_WIDTH     (2u)

/* C2 Bit Fields */
#define CMP_C2_WITHOUT_W1C_MASK (0xFF00FFFFu)
#define CMP_C2_ACO0_MASK        (0x1u)
#define CMP_C2_ACO0_SHIFT       (0u)
#define CMP_C2_ACO0_WIDTH       (1u)
#define CMP_C2_ACO1_MASK        (0x2u)
#define CMP_C2_ACO1_SHIFT       (1u)
#define CMP_C2_ACO1_WIDTH       (1u)
#define CMP_C2_ACO2_MASK        (0x4u)
#define CMP_C2_ACO2_SHIFT       (2u)
#define CMP_C2_ACO2_WIDTH       (1u)
#define CMP_C2_ACO3_MASK        (0x8u)
#define CMP_C2_ACO3_SHIFT       (3u)
#define CMP_C2_ACO3_WIDTH       (1u)
#define CMP_C2_ACO4_MASK        (0x10u)
#define CMP_C2_ACO4_SHIFT       (4u)
#define CMP_C2_ACO4_WIDTH       (1u)
#define CMP_C2_ACO5_MASK        (0x20u)
#define CMP_C2_ACO5_SHIFT       (5u)
#define CMP_C2_ACO5_WIDTH       (1u)
#define CMP_C2_ACO6_MASK        (0x40u)
#define CMP_C2_ACO6_SHIFT       (6u)
#define CMP_C2_ACO6_WIDTH       (1u)
#define CMP_C2_ACO7_MASK        (0x80u)
#define CMP_C2_ACO7_SHIFT       (7u)
#define CMP_C2_ACO7_WIDTH       (1u)
#define CMP_C2_INITMOD_MASK     (0x3F00u)
#define CMP_C2_INITMOD_SHIFT    (8u)
#define CMP_C2_INITMOD_WIDTH    (6u)
#define CMP_C2_NSAM_MASK        (0xC000u)
#define CMP_C2_NSAM_SHIFT       (14u)
#define CMP_C2_NSAM_WIDTH       (2u)
#define CMP_C2_CHnF_MASK        (0xFF0000u)
#define CMP_C2_CH0F_MASK        (0x10000u)
#define CMP_C2_CH0F_SHIFT       (16u)
#define CMP_C2_CH0F_WIDTH       (1u)
#define CMP_C2_CH1F_MASK        (0x20000u)
#define CMP_C2_CH1F_SHIFT       (17u)
#define CMP_C2_CH1F_WIDTH       (1u)
#define CMP_C2_CH2F_MASK        (0x40000u)
#define CMP_C2_CH2F_SHIFT       (18u)
#define CMP_C2_CH2F_WIDTH       (1u)
#define CMP_C2_CH3F_MASK        (0x80000u)
#define CMP_C2_CH3F_SHIFT       (19u)
#define CMP_C2_CH3F_WIDTH       (1u)
#define CMP_C2_CH4F_MASK        (0x100000u)
#define CMP_C2_CH4F_SHIFT       (20u)
#define CMP_C2_CH4F_WIDTH       (1u)
#define CMP_C2_CH5F_MASK        (0x200000u)
#define CMP_C2_CH5F_SHIFT       (21u)
#define CMP_C2_CH5F_WIDTH       (1u)
#define CMP_C2_CH6F_MASK        (0x400000u)
#define CMP_C2_CH6F_SHIFT       (22u)
#define CMP_C2_CH6F_WIDTH       (1u)
#define CMP_C2_CH7F_MASK        (0x800000u)
#define CMP_C2_CH7F_SHIFT       (23u)
#define CMP_C2_CH7F_WIDTH       (1u)
#define CMP_C2_FXMXCH_MASK      (0xE000000u)
#define CMP_C2_FXMXCH_SHIFT     (25u)
#define CMP_C2_FXMXCH_WIDTH     (3u)
#define CMP_C2_FXMP_MASK        (0x20000000u)
#define CMP_C2_FXMP_SHIFT       (29u)
#define CMP_C2_FXMP_WIDTH       (1u)
#define CMP_C2_RRIE_MASK        (0x40000000u)
#define CMP_C2_RRIE_SHIFT       (30u)
#define CMP_C2_RRIE_WIDTH       (1u)
#define CMP_C2_RRE_MASK         (0x80000000u)
#define CMP_C2_RRE_SHIFT        (31u)
#define CMP_C2_RRE_WIDTH        (1u)

/* C4 Bit Fields */
#define CMP_C4_LOCK_KEY_MASK    (0xFFFFFFFFu)
#define CMP_C4_LOCK_KEY_SHIFT   (0u)
#define CMP_C4_LOCK_KEY_WIDTH   (32u)
/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief The definition of CMP registers
 */
typedef struct _CmpRegType_
{
    volatile       uint32_t C0; /*!< CMP control register 0, offset: 0x0  */
    volatile       uint32_t C1; /*!< CMP control register 1, offset: 0x4  */
    volatile       uint32_t C2; /*!< CMP control register 2, offset: 0x8  */
    const volatile uint32_t C3; /*!< CMP control register 3, offset: 0xC  */
    volatile       uint32_t C4; /*!< CMP control register 4, offset: 0x10 */
} CmpRegType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Get the current CMP LOCK_KEY register configuration
 *
 * This function gets the current CMP LOCK_KEY register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP LOCK_KEY register configuration.
 */
__attribute__((always_inline)) static inline uint32_t CmpReg_GetLockKeyReg(const CmpRegType *obj)
{
    return ((obj->C4 & CMP_C4_LOCK_KEY_MASK) >> CMP_C4_LOCK_KEY_SHIFT);
}

/*! \brief Set CMP LOCK_KEY configuration for lock
 *
 * This function writes new configuration to CMP LOCK_KEY register for lock
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj  : pointer to CMP register instance
 */
__attribute__((always_inline)) static inline void CmpReg_LockReg(CmpRegType *obj)
{
    uint32_t tmp = obj->C4;
    tmp &= ~(CMP_C4_LOCK_KEY_MASK);
    tmp |= (((uint32_t)(((uint32_t)(LOCK_KEY)) << CMP_C4_LOCK_KEY_SHIFT)) & CMP_C4_LOCK_KEY_MASK);
    obj->C4 = tmp;
}

/*! \brief Set CMP LOCK_KEY configuration for unlock
 *
 * This function writes new configuration to CMP LOCK_KEY register for unlock
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj  : pointer to CMP register instance
 */
__attribute__((always_inline)) static inline void CmpReg_UnlockReg(CmpRegType *obj)
{
    uint32_t tmp = obj->C4;
    tmp &= ~(CMP_C4_LOCK_KEY_MASK);
    tmp |= (((uint32_t)(((uint32_t)(UNLOCK_KEY)) << CMP_C4_LOCK_KEY_SHIFT)) & CMP_C4_LOCK_KEY_MASK);
    obj->C4 = tmp;
}

/*! \brief Get the current CMP HYSTCTR register configuration
 *
 * This function gets the current CMP HYSTCTR register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP HYSTCTR register configuration.
 * - 00b: The hard block output has level 0 hysteresis internally.
 * - 01b: The hard block output has level 1 hysteresis internally.
 * - 10b: The hard block output has level 2 hysteresis internally.
 * - 11b: The hard block output has level 3 hysteresis internally.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetHystctrReg(const CmpRegType *obj)
{
    return ((obj->C0 & CMP_C0_HYSTCTR_MASK) >> CMP_C0_HYSTCTR_SHIFT);
}

/*! \brief Set CMP HYSTCTR configuration
 *
 * This function writes new configuration to CMP HYSTCTR register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 * This register write protect by CMP_C4_LOCK_KEY
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP HYSTCTR register configuration
 * - 00b: The hard block output has level 0 hysteresis internally.
 * - 01b: The hard block output has level 1 hysteresis internally.
 * - 10b: The hard block output has level 2 hysteresis internally.
 * - 11b: The hard block output has level 3 hysteresis internally.
 */
__attribute__((always_inline)) static inline void CmpReg_SetHystctrReg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C0;
    tmp &= ~(CMP_C0_HYSTCTR_MASK);
    tmp &= CMP_C0_WITHOUT_W1C_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C0_HYSTCTR_SHIFT)) & CMP_C0_HYSTCTR_MASK);
    obj->C0 = tmp;
}

/*! \brief Get the current CMP OFFSET register configuration
 *
 * This function gets the current CMP OFFSET register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP OFFSET register configuration.
 * - 0b: The comparator hard block output has level 0 offset internally.
 * - 1b: The comparator hard block output has level 1 offset internally.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetOffsetReg(const CmpRegType *obj)
{
    return ((obj->C0 & CMP_C0_OFFSET_MASK) >> CMP_C0_OFFSET_SHIFT);
}

/*! \brief Set CMP OFFSET configuration
 *
 * This function writes new configuration to CMP OFFSET register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 * This register write protect by CMP_C4_LOCK_KEY
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP OFFSET register configuration
 * - 0b: The comparator hard block output has level 0 offset internally.
 * - 1b: The comparator hard block output has level 1 offset internally.
 */
__attribute__((always_inline)) static inline void CmpReg_SetOffsetReg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C0;
    tmp &= ~(CMP_C0_OFFSET_MASK);
    tmp &= CMP_C0_WITHOUT_W1C_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C0_OFFSET_SHIFT)) & CMP_C0_OFFSET_MASK);
    obj->C0 = tmp;
}

/*! \brief Get the current CMP FILTER_CNT register configuration
 *
 * This function gets the current CMP FILTER_CNT register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP FILTER_CNT register configuration.
 * - 000b: Filter is disabled. If SE = 1, then COUT is a logic zero (this is not a legal state, and is not recommended). If SE = 0, COUT = COUTA.
 * - 001b: 1 consecutive sample must agree (comparator output is simply sampled).
 * - 010b: 2 consecutive samples must agree.
 * - 011b: 3 consecutive samples must agree.
 * - 100b: 4 consecutive samples must agree.
 * - 101b: 5 consecutive samples must agree.
 * - 110b: 6 consecutive samples must agree.
 * - 111b: 7 consecutive samples must agree.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetFilterCntReg(const CmpRegType *obj)
{
    return ((obj->C0 & CMP_C0_FILTER_CNT_MASK) >> CMP_C0_FILTER_CNT_SHIFT);
}

/*! \brief Set CMP FILTER_CNT configuration
 *
 * This function writes new configuration to CMP FILTER_CNT register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP FILTER_CNT register configuration
 * - 000b: Filter is disabled. If SE = 1, then COUT is a logic zero (this is not a legal state, and is not recommended). If SE = 0, COUT = COUTA.
 * - 001b: 1 consecutive sample must agree (comparator output is simply sampled).
 * - 010b: 2 consecutive samples must agree.
 * - 011b: 3 consecutive samples must agree.
 * - 100b: 4 consecutive samples must agree.
 * - 101b: 5 consecutive samples must agree.
 * - 110b: 6 consecutive samples must agree.
 * - 111b: 7 consecutive samples must agree.
 */
__attribute__((always_inline)) static inline void CmpReg_SetFilterCntReg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C0;
    tmp &= ~(CMP_C0_FILTER_CNT_MASK);
    tmp &= CMP_C0_WITHOUT_W1C_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C0_FILTER_CNT_SHIFT)) & CMP_C0_FILTER_CNT_MASK);
    obj->C0 = tmp;
}

/*! \brief Get the current CMP EN register configuration
 *
 * This function gets the current CMP EN register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP EN register configuration.
 * - 0b: Analog Comparator is disabled.
 * - 1b: Analog Comparator is enabled.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetEnReg(const CmpRegType *obj)
{
    return ((obj->C0 & CMP_C0_EN_MASK) >> CMP_C0_EN_SHIFT);
}

/*! \brief Set CMP EN configuration
 *
 * This function writes new configuration to CMP EN register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 * This register write protect by CMP_C4_LOCK_KEY
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP EN register configuration
 * - 0b: Analog Comparator is disabled.
 * - 1b: Analog Comparator is enabled.
 */
__attribute__((always_inline)) static inline void CmpReg_SetEnReg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C0;
    tmp &= ~(CMP_C0_EN_MASK);
    tmp &= CMP_C0_WITHOUT_W1C_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C0_EN_SHIFT)) & CMP_C0_EN_MASK);
    obj->C0 = tmp;
}

/*! \brief Get the current CMP OPE register configuration
 *
 * This function gets the current CMP OPE register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP OPE register configuration.
 * - 0b: The comparator output (after window/filter settings dependent on software configuration) is not available to a packaged pin.
 * - 1b: If the software has configured the comparator to own a packaged pin, the comparator is available in a packaged pin.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetOpeReg(const CmpRegType *obj)
{
    return ((obj->C0 & CMP_C0_OPE_MASK) >> CMP_C0_OPE_SHIFT);
}

/*! \brief Set CMP OPE configuration
 *
 * This function writes new configuration to CMP OPE register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP OPE register configuration
 * - 0b: The comparator output (after window/filter settings dependent on software configuration) is not available to a packaged pin.
 * - 1b: If the software has configured the comparator to own a packaged pin, the comparator is available in a packaged pin.
 */
__attribute__((always_inline)) static inline void CmpReg_SetOpeReg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C0;
    tmp &= ~(CMP_C0_OPE_MASK);
    tmp &= CMP_C0_WITHOUT_W1C_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C0_OPE_SHIFT)) & CMP_C0_OPE_MASK);
    obj->C0 = tmp;
}

/*! \brief Get the current CMP COS register configuration
 *
 * This function gets the current CMP COS register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP COS register configuration.
 * - 0b: Set CMPO to equal COUT (filtered comparator output).
 * - 1b: Set CMPO to equal COUTA (unfiltered comparator output).
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetCosReg(const CmpRegType *obj)
{
    return ((obj->C0 & CMP_C0_COS_MASK) >> CMP_C0_COS_SHIFT);
}

/*! \brief Set CMP COS configuration
 *
 * This function writes new configuration to CMP COS register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP COS register configuration
 * - 0b: Set CMPO to equal COUT (filtered comparator output).
 * - 1b: Set CMPO to equal COUTA (unfiltered comparator output).
 */
__attribute__((always_inline)) static inline void CmpReg_SetCosReg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C0;
    tmp &= ~(CMP_C0_COS_MASK);
    tmp &= CMP_C0_WITHOUT_W1C_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C0_COS_SHIFT)) & CMP_C0_COS_MASK);
    obj->C0 = tmp;
}

/*! \brief Get the current CMP INVT register configuration
 *
 * This function gets the current CMP INVT register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP INVT register configuration.
 * - 0b: Does not invert the comparator output.
 * - 1b: Inverts the comparator output.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetInvtReg(const CmpRegType *obj)
{
    return ((obj->C0 & CMP_C0_INVT_MASK) >> CMP_C0_INVT_SHIFT);
}

/*! \brief Set CMP INVT configuration
 *
 * This function writes new configuration to CMP INVT register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP INVT register configuration
 * - 0b: Does not invert the comparator output.
 * - 1b: Inverts the comparator output.
 */
__attribute__((always_inline)) static inline void CmpReg_SetInvtReg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C0;
    tmp &= ~(CMP_C0_INVT_MASK);
    tmp &= CMP_C0_WITHOUT_W1C_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C0_INVT_SHIFT)) & CMP_C0_INVT_MASK);
    obj->C0 = tmp;
}

/*! \brief Get the current CMP PMODE register configuration
 *
 * This function gets the current CMP PMODE register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP PMODE register configuration.
 * - 0b: Low Speed (LS) comparison mode is selected.
 * - 1b: High Speed (HS) comparison mode is selected, in VLPx mode, or Stop mode switched to Low Speed (LS) mode.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetPmodeReg(const CmpRegType *obj)
{
    return ((obj->C0 & CMP_C0_PMODE_MASK) >> CMP_C0_PMODE_SHIFT);
}

/*! \brief Set CMP PMODE configuration
 *
 * This function writes new configuration to CMP PMODE register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 * This register write protect by CMP_C4_LOCK_KEY
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP PMODE register configuration
 * - 0b: Low Speed (LS) comparison mode is selected.
 * - 1b: High Speed (HS) comparison mode is selected, in VLPx mode, or Stop mode switched to Low Speed (LS) mode.
 */
__attribute__((always_inline)) static inline void CmpReg_SetPmodeReg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C0;
    tmp &= ~(CMP_C0_PMODE_MASK);
    tmp &= CMP_C0_WITHOUT_W1C_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C0_PMODE_SHIFT)) & CMP_C0_PMODE_MASK);
    obj->C0 = tmp;
}

/*! \brief Get the current CMP WE register configuration
 *
 * This function gets the current CMP WE register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP WE register configuration.
 * - 0b: Windowing mode is not selected.
 * - 1b: Windowing mode is selected.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetWeReg(const CmpRegType *obj)
{
    return ((obj->C0 & CMP_C0_WE_MASK) >> CMP_C0_WE_SHIFT);
}

/*! \brief Set CMP WE configuration
 *
 * This function writes new configuration to CMP WE register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP WE register configuration
 * - 0b: Windowing mode is not selected.
 * - 1b: Windowing mode is selected.
 */
__attribute__((always_inline)) static inline void CmpReg_SetWeReg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C0;
    tmp &= ~(CMP_C0_WE_MASK);
    tmp &= CMP_C0_WITHOUT_W1C_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C0_WE_SHIFT)) & CMP_C0_WE_MASK);
    obj->C0 = tmp;
}

/*! \brief Get the current CMP SE register configuration
 *
 * This function gets the current CMP SE register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP SE register configuration.
 * - 0b: Sampling mode is not selected.
 * - 1b: Sampling mode is selected.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetSeReg(const CmpRegType *obj)
{
    return ((obj->C0 & CMP_C0_SE_MASK) >> CMP_C0_SE_SHIFT);
}

/*! \brief Set CMP SE configuration
 *
 * This function writes new configuration to CMP SE register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP SE register configuration
 * - 0b: Sampling mode is not selected.
 * - 1b: Sampling mode is selected.
 */
__attribute__((always_inline)) static inline void CmpReg_SetSeReg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C0;
    tmp &= ~(CMP_C0_SE_MASK);
    tmp &= CMP_C0_WITHOUT_W1C_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C0_SE_SHIFT)) & CMP_C0_SE_MASK);
    obj->C0 = tmp;
}

/*! \brief Get the current CMP FPR register configuration
 *
 * This function gets the current CMP FPR register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP FPR register configuration.
 * Specifies the sampling period, in bus clock cycles, of the comparator output filter, when C0[SE] = 0.
 * -0b: disables the filter.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetFprReg(const CmpRegType *obj)
{
    return ((obj->C0 & CMP_C0_FPR_MASK) >> CMP_C0_FPR_SHIFT);
}

/*! \brief Set CMP FPR configuration
 *
 * This function writes new configuration to CMP FPR register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP FPR register configuration
 * Specifies the sampling period, in bus clock cycles, of the comparator output filter, when C0[SE] = 0.
 * -0b: disables the filter.
 */
__attribute__((always_inline)) static inline void CmpReg_SetFprReg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C0;
    tmp &= ~(CMP_C0_FPR_MASK);
    tmp &= CMP_C0_WITHOUT_W1C_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C0_FPR_SHIFT)) & CMP_C0_FPR_MASK);
    obj->C0 = tmp;
}

/*! \brief Get the current CMP COUT register
 *
 * This function gets the current CMP COUT register .
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 * This register read only
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP COUT register configuration.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetCoutReg(const CmpRegType *obj)
{
    return ((obj->C0 & CMP_C0_COUT_MASK) >> CMP_C0_COUT_SHIFT);
}

/*! \brief Get the current CMP CFF register
 *
 * This function gets the current CMP CFF register .
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP CFF register configuration.
 * - 0b: A falling edge has not been detected on COUT.
 * - 1b: A falling edge on COUT has occurred.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetCffReg(const CmpRegType *obj)
{
    return ((obj->C0 & CMP_C0_CFF_MASK) >> CMP_C0_CFF_SHIFT);
}

/*! \brief Clear CMP CFF register
 *
 * This function clear CMP CFF register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 * This register write 1 to Clear
 *
 * \param[in] obj  : pointer to CMP register instance
 */
__attribute__((always_inline)) static inline void CmpReg_ClearCffReg(CmpRegType *obj)
{
    uint32_t tmp = obj->C0;
    tmp &= ~(CMP_C0_CFF_MASK);
    tmp &= CMP_C0_WITHOUT_W1C_MASK;
    tmp |= (((uint32_t)(((uint32_t)(1u)) << CMP_C0_CFF_SHIFT)) & CMP_C0_CFF_MASK);
    obj->C0 = tmp;
    (void)(obj->C0);
}

/*! \brief Get the current CMP CFR register
 *
 * This function gets the current CMP CFR register .
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP CFR register configuration.
 * - 0b: A rising edge has not been detected on COUT.
 * - 1b: A rising edge on COUT has occurred.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetCfrReg(const CmpRegType *obj)
{
    return ((obj->C0 & CMP_C0_CFR_MASK) >> CMP_C0_CFR_SHIFT);
}

/*! \brief Clear CMP CFR register
 *
 * This function clear CMP CFR register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 * This register write 1 to Clear
 *
 * \param[in] obj  : pointer to CMP register instance
 */
__attribute__((always_inline)) static inline void CmpReg_ClearCfrReg(CmpRegType *obj)
{
    uint32_t tmp = obj->C0;
    tmp &= ~(CMP_C0_CFR_MASK);
    tmp &= CMP_C0_WITHOUT_W1C_MASK;
    tmp |= (((uint32_t)(((uint32_t)(1u)) << CMP_C0_CFR_SHIFT)) & CMP_C0_CFR_MASK);
    obj->C0 = tmp;
    (void)(obj->C0);
}

/*! \brief Get the current CMP IEF register configuration
 *
 * This function gets the current CMP IEF register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP IEF register configuration.
 * - 0b: Interrupt is disabled.
 * - 1b: Interrupt is enabled.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetIefReg(const CmpRegType *obj)
{
    return ((obj->C0 & CMP_C0_IEF_MASK) >> CMP_C0_IEF_SHIFT);
}

/*! \brief Set CMP IEF configuration
 *
 * This function writes new configuration to CMP IEF register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP IEF register configuration
 * - 0b: Interrupt is disabled.
 * - 1b: Interrupt is enabled.
 */
__attribute__((always_inline)) static inline void CmpReg_SetIefReg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C0;
    tmp &= ~(CMP_C0_IEF_MASK);
    tmp &= CMP_C0_WITHOUT_W1C_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C0_IEF_SHIFT)) & CMP_C0_IEF_MASK);
    obj->C0 = tmp;
}

/*! \brief Get the current CMP IER register configuration
 *
 * This function gets the current CMP IER register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP IER register configuration.
 * - 0b: Interrupt is disabled.
 * - 1b: Interrupt is enabled.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetIerReg(const CmpRegType *obj)
{
    return ((obj->C0 & CMP_C0_IER_MASK) >> CMP_C0_IER_SHIFT);
}

/*! \brief Set CMP IER configuration
 *
 * This function writes new configuration to CMP IER register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP IER register configuration
 * - 0b: Interrupt is disabled.
 * - 1b: Interrupt is enabled.
 */
__attribute__((always_inline)) static inline void CmpReg_SetIerReg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C0;
    tmp &= ~(CMP_C0_IER_MASK);
    tmp &= CMP_C0_WITHOUT_W1C_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C0_IER_SHIFT)) & CMP_C0_IER_MASK);
    obj->C0 = tmp;
}

/*! \brief Get the current CMP LPFSEL register configuration
 *
 * This function gets the current CMP LPFSEL register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP LPFSEL register configuration.
 * - 00b: 23MHz
 * - 01b: 16MHz
 * - 10b: 13MHz
 * - 11b: 10MHz
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetLpfselReg(const CmpRegType *obj)
{
    return ((obj->C0 & CMP_C0_LPFSEL_MASK) >> CMP_C0_LPFSEL_SHIFT);
}

/*! \brief Set CMP LPFSEL configuration
 *
 * This function writes new configuration to CMP LPFSEL register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 * This register write protect by CMP_C4_LOCK_KEY
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP LPFSEL register configuration
 * - 00b: 23MHz
 * - 01b: 16MHz
 * - 10b: 13MHz
 * - 11b: 10MHz
 */
__attribute__((always_inline)) static inline void CmpReg_SetLpfselReg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C0;
    tmp &= ~(CMP_C0_LPFSEL_MASK);
    tmp &= CMP_C0_WITHOUT_W1C_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C0_LPFSEL_SHIFT)) & CMP_C0_LPFSEL_MASK);
    obj->C0 = tmp;
}

/*! \brief Get the current CMP DMAEN register configuration
 *
 * This function gets the current CMP DMAEN register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP DMAEN register configuration.
 * - 0b: DMA is disabled.
 * - 1b: DMA is enabled.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetDmaenReg(const CmpRegType *obj)
{
    return ((obj->C0 & CMP_C0_DMAEN_MASK) >> CMP_C0_DMAEN_SHIFT);
}

/*! \brief Set CMP DMAEN configuration
 *
 * This function writes new configuration to CMP DMAEN register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP DMAEN register configuration
 * - 0b: DMA is disabled.
 * - 1b: DMA is enabled.
 */
__attribute__((always_inline)) static inline void CmpReg_SetDmaenReg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C0;
    tmp &= ~(CMP_C0_DMAEN_MASK);
    tmp &= CMP_C0_WITHOUT_W1C_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C0_DMAEN_SHIFT)) & CMP_C0_DMAEN_MASK);
    obj->C0 = tmp;
}

/*! \brief Get the current CMP VOSEL register configuration
 *
 * This function gets the current CMP VOSEL register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP VOSEL register configuration.
 * DAC Output Voltage = (Vin/256) × (VOSEL[7:0] + 1).
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetVoselReg(const CmpRegType *obj)
{
    return ((obj->C1 & CMP_C1_VOSEL_MASK) >> CMP_C1_VOSEL_SHIFT);
}

/*! \brief Set CMP VOSEL configuration
 *
 * This function writes new configuration to CMP LPFSEL register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 * This register write protect by CMP_C4_LOCK_KEY
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP VOSEL register configuration
 * DAC Output Voltage = (Vin/256) × (VOSEL[7:0] + 1).
 */
__attribute__((always_inline)) static inline void CmpReg_SetVoselReg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C1;
    tmp &= ~(CMP_C1_VOSEL_MASK);
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C1_VOSEL_SHIFT)) & CMP_C1_VOSEL_MASK);
    obj->C1 = tmp;
}

/*! \brief Get the current CMP MSEL register configuration
 *
 * This function gets the current CMP MSEL register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP MSEL register configuration.
 * - 000b: IN0
 * - 001b: IN1
 * - 010b: IN2
 * - 011b: IN3
 * - 100b: IN4
 * - 101b: IN5
 * - 110b: IN6
 * - 111b: IN7
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetMselReg(const CmpRegType *obj)
{
    return ((obj->C1 & CMP_C1_MSEL_MASK) >> CMP_C1_MSEL_SHIFT);
}

/*! \brief Set CMP MSEL configuration
 *
 * This function writes new configuration to CMP MSEL register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP MSEL register configuration
 * - 000b: IN0
 * - 001b: IN1
 * - 010b: IN2
 * - 011b: IN3
 * - 100b: IN4
 * - 101b: IN5
 * - 110b: IN6
 * - 111b: IN7
 */
__attribute__((always_inline)) static inline void CmpReg_SetMselReg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C1;
    tmp &= ~(CMP_C1_MSEL_MASK);
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C1_MSEL_SHIFT)) & CMP_C1_MSEL_MASK);
    obj->C1 = tmp;
}

/*! \brief Get the current CMP PSEL register configuration
 *
 * This function gets the current CMP PSEL register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP PSEL register configuration.
 * - 000b: IN0
 * - 001b: IN1
 * - 010b: IN2
 * - 011b: IN3
 * - 100b: IN4
 * - 101b: IN5
 * - 110b: IN6
 * - 111b: IN7
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetPselReg(const CmpRegType *obj)
{
    return ((obj->C1 & CMP_C1_PSEL_MASK) >> CMP_C1_PSEL_SHIFT);
}

/*! \brief Set CMP PSEL configuration
 *
 * This function writes new configuration to CMP PSEL register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP PSEL register configuration
 * - 000b: IN0
 * - 001b: IN1
 * - 010b: IN2
 * - 011b: IN3
 * - 100b: IN4
 * - 101b: IN5
 * - 110b: IN6
 * - 111b: IN7
 */
__attribute__((always_inline)) static inline void CmpReg_SetPselReg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C1;
    tmp &= ~(CMP_C1_PSEL_MASK);
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C1_PSEL_SHIFT)) & CMP_C1_PSEL_MASK);
    obj->C1 = tmp;
}

/*! \brief Get the current CMP VRSEL register configuration
 *
 * This function gets the current CMP VRSEL register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP VRSEL register configuration.
 * - 0b: Vin1 is selected as resistor ladder network supply reference Vin.
 * - 1b: Vin2 is selected as resistor ladder network supply reference Vin.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetVrselReg(const CmpRegType *obj)
{
    return ((obj->C1 & CMP_C1_VRSEL_MASK) >> CMP_C1_VRSEL_SHIFT);
}

/*! \brief Set CMP VRSEL configuration
 *
 * This function writes new configuration to CMP VRSEL register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 * This register write protect by CMP_C4_LOCK_KEY
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP VRSEL register configuration
 * - 0b: Vin1 is selected as resistor ladder network supply reference Vin.
 * - 1b: Vin2 is selected as resistor ladder network supply reference Vin.
 */
__attribute__((always_inline)) static inline void CmpReg_SetVrselReg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C1;
    tmp &= ~(CMP_C1_VRSEL_MASK);
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C1_VRSEL_SHIFT)) & CMP_C1_VRSEL_MASK);
    obj->C1 = tmp;
}

/*! \brief Get the current CMP DACEN register configuration
 *
 * This function gets the current CMP DACEN register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP DACEN register configuration.
 * - 0b: DAC is disabled.
 * - 1b: DAC is enabled.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetDacenReg(const CmpRegType *obj)
{
    return ((obj->C1 & CMP_C1_DACEN_MASK) >> CMP_C1_DACEN_SHIFT);
}

/*! \brief Set CMP DACEN configuration
 *
 * This function writes new configuration to CMP DACEN register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 * This register write protect by CMP_C4_LOCK_KEY
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP DACEN register configuration
 * - 0b: DAC is disabled.
 * - 1b: DAC is enabled.
 */
__attribute__((always_inline)) static inline void CmpReg_SetDacenReg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C1;
    tmp &= ~(CMP_C1_DACEN_MASK);
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C1_DACEN_SHIFT)) & CMP_C1_DACEN_MASK);
    obj->C1 = tmp;
}

/*! \brief Get the current CMP CHN0 register configuration
 *
 * This function gets the current CMP CHN0 register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * Channel 0 of the input enable for the round-robin checker.
 * If CHN0 is set, then the corresponding channel to the non-fixed mux port is
 * enabled to check its voltage value in the round-robin mode. If the same channel
 * is selected as the reference voltage, this bit has no effect.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP CHN0 register configuration.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetChn0Reg(const CmpRegType *obj)
{
    return ((obj->C1 & CMP_C1_CHN0_MASK) >> CMP_C1_CHN0_SHIFT);
}

/*! \brief Set CMP CHN0 configuration
 *
 * This function writes new configuration to CMP CHN0 register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * Set 1 for Channel 0 of the input enable for the round-robin checker.
 * If CHN0 is set, then the corresponding channel to the non-fixed mux port is
 * enabled to check its voltage value in the round-robin mode. If the same channel
 * is selected as the reference voltage, this bit has no effect.
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP CHN0 register configuration
 */
__attribute__((always_inline)) static inline void CmpReg_SetChn0Reg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C1;
    tmp &= ~(CMP_C1_CHN0_MASK);
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C1_CHN0_SHIFT)) & CMP_C1_CHN0_MASK);
    obj->C1 = tmp;
}

/*! \brief Get the current CMP CHN1 register configuration
 *
 * This function gets the current CMP CHN1 register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * Set 1 for Channel 1 of the input enable for the round-robin checker.
 * If CHN1 is set, then the corresponding channel to the non-fixed mux port is
 * enabled to check its voltage value in the round-robin mode. If the same channel
 * is selected as the reference voltage, this bit has no effect.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP CHN1 register configuration.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetChn1Reg(const CmpRegType *obj)
{
    return ((obj->C1 & CMP_C1_CHN1_MASK) >> CMP_C1_CHN1_SHIFT);
}

/*! \brief Set CMP CHN1 configuration
 *
 * This function writes new configuration to CMP CHN1 register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * Set 1 for Channel 1 of the input enable for the round-robin checker.
 * If CHN1 is set, then the corresponding channel to the non-fixed mux port is
 * enabled to check its voltage value in the round-robin mode. If the same channel
 * is selected as the reference voltage, this bit has no effect.
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP CHN1 register configuration
 */
__attribute__((always_inline)) static inline void CmpReg_SetChn1Reg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C1;
    tmp &= ~(CMP_C1_CHN1_MASK);
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C1_CHN1_SHIFT)) & CMP_C1_CHN1_MASK);
    obj->C1 = tmp;
}

/*! \brief Get the current CMP CHN2 register configuration
 *
 * This function gets the current CMP CHN2 register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * Set 1 for Channel 2 of the input enable for the round-robin checker.
 * If CHN2 is set, then the corresponding channel to the non-fixed mux port is
 * enabled to check its voltage value in the round-robin mode. If the same channel
 * is selected as the reference voltage, this bit has no effect.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP CHN2 register configuration.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetChn2Reg(const CmpRegType *obj)
{
    return ((obj->C1 & CMP_C1_CHN2_MASK) >> CMP_C1_CHN2_SHIFT);
}

/*! \brief Set CMP CHN2 configuration
 *
 * This function writes new configuration to CMP CHN2 register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * Set 1 for Channel 2 of the input enable for the round-robin checker.
 * If CHN2 is set, then the corresponding channel to the non-fixed mux port is
 * enabled to check its voltage value in the round-robin mode. If the same channel
 * is selected as the reference voltage, this bit has no effect.
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP CHN2 register configuration
 */
__attribute__((always_inline)) static inline void CmpReg_SetChn2Reg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C1;
    tmp &= ~(CMP_C1_CHN2_MASK);
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C1_CHN2_SHIFT)) & CMP_C1_CHN2_MASK);
    obj->C1 = tmp;
}

/*! \brief Get the current CMP CHN3 register configuration
 *
 * This function gets the current CMP CHN3 register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * Set 1 for Channel 3 of the input enable for the round-robin checker.
 * If CHN3 is set, then the corresponding channel to the non-fixed mux port is
 * enabled to check its voltage value in the round-robin mode. If the same channel
 * is selected as the reference voltage, this bit has no effect.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP CHN3 register configuration.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetChn3Reg(const CmpRegType *obj)
{
    return ((obj->C1 & CMP_C1_CHN3_MASK) >> CMP_C1_CHN3_SHIFT);
}

/*! \brief Set CMP CHN3 configuration
 *
 * This function writes new configuration to CMP CHN3 register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * Set 1 for Channel 3 of the input enable for the round-robin checker.
 * If CHN3 is set, then the corresponding channel to the non-fixed mux port is
 * enabled to check its voltage value in the round-robin mode. If the same channel
 * is selected as the reference voltage, this bit has no effect.
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP CHN3 register configuration
 */
__attribute__((always_inline)) static inline void CmpReg_SetChn3Reg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C1;
    tmp &= ~(CMP_C1_CHN3_MASK);
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C1_CHN3_SHIFT)) & CMP_C1_CHN3_MASK);
    obj->C1 = tmp;
}

/*! \brief Get the current CMP CHN4 register configuration
 *
 * This function gets the current CMP CHN4 register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * Set 1 for Channel 4 of the input enable for the round-robin checker.
 * If CHN4 is set, then the corresponding channel to the non-fixed mux port is
 * enabled to check its voltage value in the round-robin mode. If the same channel
 * is selected as the reference voltage, this bit has no effect.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP CHN4 register configuration.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetChn4Reg(const CmpRegType *obj)
{
    return ((obj->C1 & CMP_C1_CHN4_MASK) >> CMP_C1_CHN4_SHIFT);
}

/*! \brief Set CMP CHN4 configuration
 *
 * This function writes new configuration to CMP CHN4 register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * Set 1 for Channel 4 of the input enable for the round-robin checker.
 * If CHN4 is set, then the corresponding channel to the non-fixed mux port is
 * enabled to check its voltage value in the round-robin mode. If the same channel
 * is selected as the reference voltage, this bit has no effect.
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP CHN4 register configuration
 */
__attribute__((always_inline)) static inline void CmpReg_SetChn4Reg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C1;
    tmp &= ~(CMP_C1_CHN4_MASK);
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C1_CHN4_SHIFT)) & CMP_C1_CHN4_MASK);
    obj->C1 = tmp;
}

/*! \brief Get the current CMP CHN5 register configuration
 *
 * This function gets the current CMP CHN5 register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * Set 1 for Channel 5 of the input enable for the round-robin checker.
 * If CHN5 is set, then the corresponding channel to the non-fixed mux port is
 * enabled to check its voltage value in the round-robin mode. If the same channel
 * is selected as the reference voltage, this bit has no effect.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP CHN5 register configuration.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetChn5Reg(const CmpRegType *obj)
{
    return ((obj->C1 & CMP_C1_CHN5_MASK) >> CMP_C1_CHN5_SHIFT);
}

/*! \brief Set CMP CHN5 configuration
 *
 * This function writes new configuration to CMP CHN5 register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * Set 1 for Channel 5 of the input enable for the round-robin checker.
 * If CHN5 is set, then the corresponding channel to the non-fixed mux port is
 * enabled to check its voltage value in the round-robin mode. If the same channel
 * is selected as the reference voltage, this bit has no effect.
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP CHN5 register configuration
 */
__attribute__((always_inline)) static inline void CmpReg_SetChn5Reg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C1;
    tmp &= ~(CMP_C1_CHN5_MASK);
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C1_CHN5_SHIFT)) & CMP_C1_CHN5_MASK);
    obj->C1 = tmp;
}

/*! \brief Get the current CMP CHN6 register configuration
 *
 * This function gets the current CMP CHN6 register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * Set 1 for Channel 6 of the input enable for the round-robin checker.
 * If CHN6 is set, then the corresponding channel to the non-fixed mux port is
 * enabled to check its voltage value in the round-robin mode. If the same channel
 * is selected as the reference voltage, this bit has no effect.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP CHN6 register configuration.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetChn6Reg(const CmpRegType *obj)
{
    return ((obj->C1 & CMP_C1_CHN6_MASK) >> CMP_C1_CHN6_SHIFT);
}

/*! \brief Set CMP CHN6 configuration
 *
 * This function writes new configuration to CMP CHN6 register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * Set 1 for Channel 6 of the input enable for the round-robin checker.
 * If CHN6 is set, then the corresponding channel to the non-fixed mux port is
 * enabled to check its voltage value in the round-robin mode. If the same channel
 * is selected as the reference voltage, this bit has no effect.
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP CHN6 register configuration
 */
__attribute__((always_inline)) static inline void CmpReg_SetChn6Reg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C1;
    tmp &= ~(CMP_C1_CHN6_MASK);
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C1_CHN6_SHIFT)) & CMP_C1_CHN6_MASK);
    obj->C1 = tmp;
}

/*! \brief Get the current CMP CHN7 register configuration
 *
 * This function gets the current CMP CHN7 register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * Set 1 for Channel 7 of the input enable for the round-robin checker.
 * If CHN7 is set, then the corresponding channel to the non-fixed mux port is
 * enabled to check its voltage value in the round-robin mode. If the same channel
 * is selected as the reference voltage, this bit has no effect.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP CHN7 register configuration.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetChn7Reg(const CmpRegType *obj)
{
    return ((obj->C1 & CMP_C1_CHN7_MASK) >> CMP_C1_CHN7_SHIFT);
}

/*! \brief Set CMP CHN7 configuration
 *
 * This function writes new configuration to CMP CHN7 register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * Set 1 for Channel 7 of the input enable for the round-robin checker.
 * If CHN7 is set, then the corresponding channel to the non-fixed mux port is
 * enabled to check its voltage value in the round-robin mode. If the same channel
 * is selected as the reference voltage, this bit has no effect.
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP CHN7 register configuration
 */
__attribute__((always_inline)) static inline void CmpReg_SetChn7Reg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C1;
    tmp &= ~(CMP_C1_CHN7_MASK);
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C1_CHN7_SHIFT)) & CMP_C1_CHN7_MASK);
    obj->C1 = tmp;
}

/*! \brief Get the current CMP INNSEL register configuration
 *
 * This function gets the current CMP INNSEL register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP INNSEL register configuration.
 * - 00b: IN0, from the 8-bit DAC output
 * - 01b: IN1, from the analog 8-1 mux
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetInnselReg(const CmpRegType *obj)
{
    return ((obj->C1 & CMP_C1_INNSEL_MASK) >> CMP_C1_INNSEL_SHIFT);
}

/*! \brief Set CMP INNSEL configuration
 *
 * This function writes new configuration to CMP INNSEL register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 * This register write protect by CMP_C4_LOCK_KEY
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP INNSEL register configuration
 * - 00b: IN0, from the 8-bit DAC output
 * - 01b: IN1, from the analog 8-1 mux
 */
__attribute__((always_inline)) static inline void CmpReg_SetInnselReg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C1;
    tmp &= ~(CMP_C1_INNSEL_MASK);
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C1_INNSEL_SHIFT)) & CMP_C1_INNSEL_MASK);
    obj->C1 = tmp;
}

/*! \brief Get the current CMP INPSEL register configuration
 *
 * This function gets the current CMP INPSEL register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP INPSEL register configuration.
 * - 00b: IN0, from the 8-bit DAC output
 * - 01b: IN1, from the analog 8-1 mux
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetInpselReg(const CmpRegType *obj)
{
    return ((obj->C1 & CMP_C1_INPSEL_MASK) >> CMP_C1_INPSEL_SHIFT);
}

/*! \brief Set CMP INPSEL configuration
 *
 * This function writes new configuration to CMP INPSEL register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 * This register write protect by CMP_C4_LOCK_KEY
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP INPSEL register configuration
 * - 00b: IN0, from the 8-bit DAC output
 * - 01b: IN1, from the analog 8-1 mux
 */
__attribute__((always_inline)) static inline void CmpReg_SetInpselReg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C1;
    tmp &= ~(CMP_C1_INPSEL_MASK);
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C1_INPSEL_SHIFT)) & CMP_C1_INPSEL_MASK);
    obj->C1 = tmp;
}

/*! \brief Get the current CMP ACO0 register configuration
 *
 * This function gets the current CMP ACO0 register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP ACO0 register configuration.
 * This field stores the latest comparison result of the input channel 0 with the fixed mux port.
 * Reading this bit returns the latest comparison result.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetAco0Reg(const CmpRegType *obj)
{
    return ((obj->C2 & CMP_C2_ACO0_MASK) >> CMP_C2_ACO0_SHIFT);
}

/*! \brief Set CMP ACO0 configuration
 *
 * This function writes new configuration to CMP ACO0 register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 * Writing this field defines the pre-set state of channel 0.
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP ACO0 register configuration
 */
__attribute__((always_inline)) static inline void CmpReg_SetAco0Reg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C2;
    tmp &= ~(CMP_C2_ACO0_MASK);
    tmp &= CMP_C2_WITHOUT_W1C_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C2_ACO0_SHIFT)) & CMP_C2_ACO0_MASK);
    obj->C2 = tmp;
}

/*! \brief Get the current CMP ACO1 register configuration
 *
 * This function gets the current CMP ACO1 register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP ACO1 register configuration.
 * This field stores the latest comparison result of the input channel 1 with the fixed mux port.
 * Reading this bit returns the latest comparison result.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetAco1Reg(const CmpRegType *obj)
{
    return ((obj->C2 & CMP_C2_ACO1_MASK) >> CMP_C2_ACO1_SHIFT);
}

/*! \brief Set CMP ACO1 configuration
 *
 * This function writes new configuration to CMP ACO1 register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 * Writing this field defines the pre-set state of channel 1.
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP ACO1 register configuration
 */
__attribute__((always_inline)) static inline void CmpReg_SetAco1Reg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C2;
    tmp &= ~(CMP_C2_ACO1_MASK);
    tmp &= CMP_C2_WITHOUT_W1C_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C2_ACO1_SHIFT)) & CMP_C2_ACO1_MASK);
    obj->C2 = tmp;
}

/*! \brief Get the current CMP ACO2 register configuration
 *
 * This function gets the current CMP ACO2 register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP ACO2 register configuration.
 * This field stores the latest comparison result of the input channel 2 with the fixed mux port.
 * Reading this bit returns the latest comparison result.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetAco2Reg(const CmpRegType *obj)
{
    return ((obj->C2 & CMP_C2_ACO2_MASK) >> CMP_C2_ACO2_SHIFT);
}

/*! \brief Set CMP ACO2 configuration
 *
 * This function writes new configuration to CMP ACO2 register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 * Writing this field defines the pre-set state of channel 2.
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP ACO2 register configuration
 */
__attribute__((always_inline)) static inline void CmpReg_SetAco2Reg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C2;
    tmp &= ~(CMP_C2_ACO2_MASK);
    tmp &= CMP_C2_WITHOUT_W1C_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C2_ACO2_SHIFT)) & CMP_C2_ACO2_MASK);
    obj->C2 = tmp;
}

/*! \brief Get the current CMP ACO3 register configuration
 *
 * This function gets the current CMP ACO3 register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP ACO3 register configuration.
 * This field stores the latest comparison result of the input channel 3 with the fixed mux port.
 * Reading this bit returns the latest comparison result.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetAco3Reg(const CmpRegType *obj)
{
    return ((obj->C2 & CMP_C2_ACO3_MASK) >> CMP_C2_ACO3_SHIFT);
}

/*! \brief Set CMP ACO3 configuration
 *
 * This function writes new configuration to CMP ACO3 register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 * Writing this field defines the pre-set state of channel 3.
 *
 * \param[in] obj : pointer to CMP register instance
 * \param[in] value : expected CMP ACO3 register configuration
 */
__attribute__((always_inline)) static inline void CmpReg_SetAco3Reg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C2;
    tmp &= ~(CMP_C2_ACO3_MASK);
    tmp &= CMP_C2_WITHOUT_W1C_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C2_ACO3_SHIFT)) & CMP_C2_ACO3_MASK);
    obj->C2 = tmp;
}

/*! \brief Get the current CMP ACO4 register configuration
 *
 * This function gets the current CMP ACO4 register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP ACO4 register configuration.
 * This field stores the latest comparison result of the input channel 4 with the fixed mux port.
 * Reading this bit returns the latest comparison result.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetAco4Reg(const CmpRegType *obj)
{
    return ((obj->C2 & CMP_C2_ACO4_MASK) >> CMP_C2_ACO4_SHIFT);
}

/*! \brief Set CMP ACO4 configuration
 *
 * This function writes new configuration to CMP ACO4 register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 * Writing this field defines the pre-set state of channel 4.
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP ACO4 register configuration
 */
__attribute__((always_inline)) static inline void CmpReg_SetAco4Reg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C2;
    tmp &= ~(CMP_C2_ACO4_MASK);
    tmp &= CMP_C2_WITHOUT_W1C_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C2_ACO4_SHIFT)) & CMP_C2_ACO4_MASK);
    obj->C2 = tmp;
}

/*! \brief Get the current CMP ACO5 register configuration
 *
 * This function gets the current CMP ACO5 register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP ACO5 register configuration.
 * This field stores the latest comparison result of the input channel 5 with the fixed mux port.
 * Reading this bit returns the latest comparison result.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetAco5Reg(const CmpRegType *obj)
{
    return ((obj->C2 & CMP_C2_ACO5_MASK) >> CMP_C2_ACO5_SHIFT);
}

/*! \brief Set CMP ACO5 configuration
 *
 * This function writes new configuration to CMP ACO5 register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 * Writing this field defines the pre-set state of channel 5.
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP ACO5 register configuration
 */
__attribute__((always_inline)) static inline void CmpReg_SetAco5Reg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C2;
    tmp &= ~(CMP_C2_ACO5_MASK);
    tmp &= CMP_C2_WITHOUT_W1C_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C2_ACO5_SHIFT)) & CMP_C2_ACO5_MASK);
    obj->C2 = tmp;
}

/*! \brief Get the current CMP ACO6 register configuration
 *
 * This function gets the current CMP ACO6 register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP ACO6 register configuration.
 * This field stores the latest comparison result of the input channel 6 with the fixed mux port.
 * Reading this bit returns the latest comparison result.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetAco6Reg(const CmpRegType *obj)
{
    return ((obj->C2 & CMP_C2_ACO6_MASK) >> CMP_C2_ACO6_SHIFT);
}

/*! \brief Set CMP ACO6 configuration
 *
 * This function writes new configuration to CMP ACO6 register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 * Writing this field defines the pre-set state of channel 6.
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP ACO6 register configuration
 */
__attribute__((always_inline)) static inline void CmpReg_SetAco6Reg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C2;
    tmp &= ~(CMP_C2_ACO6_MASK);
    tmp &= CMP_C2_WITHOUT_W1C_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C2_ACO6_SHIFT)) & CMP_C2_ACO6_MASK);
    obj->C2 = tmp;
}

/*! \brief Get the current CMP ACO7 register configuration
 *
 * This function gets the current CMP ACO7 register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP ACO7 register configuration.
 * This field stores the latest comparison result of the input channel 7 with the fixed mux port.
 * Reading this bit returns the latest comparison result.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetAco7Reg(const CmpRegType *obj)
{
    return ((obj->C2 & CMP_C2_ACO7_MASK) >> CMP_C2_ACO7_SHIFT);
}

/*! \brief Set CMP ACO7 configuration
 *
 * This function writes new configuration to CMP ACO7 register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 * Writing this field defines the pre-set state of channel 7.
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP ACO7 register configuration
 */
__attribute__((always_inline)) static inline void CmpReg_SetAco7Reg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C2;
    tmp &= ~(CMP_C2_ACO7_MASK);
    tmp &= CMP_C2_WITHOUT_W1C_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C2_ACO7_SHIFT)) & CMP_C2_ACO7_MASK);
    obj->C2 = tmp;
}

/*! \brief Get the current CMP INITMOD register configuration
 *
 * This function gets the current CMP INITMOD register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP INITMOD register configuration.
 * These values specify the round robin clock cycles used to determine the comparator and DAC initialization delays.
 * - 000000b: The modulus is set to 64 (same with 111111).
 * other values Initialization delay is set to INITMOD × round robin clock period
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetInitmodReg(const CmpRegType *obj)
{
    return ((obj->C2 & CMP_C2_INITMOD_MASK) >> CMP_C2_INITMOD_SHIFT);
}

/*! \brief Set CMP INITMOD configuration
 *
 * This function writes new configuration to CMP INITMOD register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP INITMOD register configuration
 * These values specify the round robin clock cycles used to determine the comparator and DAC initialization delays.
 * - 000000b: The modulus is set to 64 (same with 111111).
 * other values Initialization delay is set to INITMOD × round robin clock period
 */
__attribute__((always_inline)) static inline void CmpReg_SetInitmodReg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C2;
    tmp &= ~(CMP_C2_INITMOD_MASK);
    tmp &= CMP_C2_WITHOUT_W1C_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C2_INITMOD_SHIFT)) & CMP_C2_INITMOD_MASK);
    obj->C2 = tmp;
}

/*! \brief Get the current CMP NSAM register configuration
 *
 * This function gets the current CMP NSAM register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP NSAM register configuration.
 * - 00b: The comparison result is sampled as soon as the active channel is scanned in one round-robin clock.
 * - 01b: The sampling takes place 1 round-robin clock cycle after the next cycle of the round-robin clock.
 * - 10b: The sampling takes place 2 round-robin clock cycles after the next cycle of the round-robin clock.
 * - 11b: The sampling takes place 3 round-robin clock cycles after the next cycle of the round-robin clock.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetNsamReg(const CmpRegType *obj)
{
    return ((obj->C2 & CMP_C2_NSAM_MASK) >> CMP_C2_NSAM_SHIFT);
}

/*! \brief Set CMP NSAM configuration
 *
 * This function writes new configuration to CMP NSAM register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP NSAM register configuration
 * - 00b: The comparison result is sampled as soon as the active channel is scanned in one round-robin clock.
 * - 01b: The sampling takes place 1 round-robin clock cycle after the next cycle of the round-robin clock.
 * - 10b: The sampling takes place 2 round-robin clock cycles after the next cycle of the round-robin clock.
 * - 11b: The sampling takes place 3 round-robin clock cycles after the next cycle of the round-robin clock.
 */
__attribute__((always_inline)) static inline void CmpReg_SetNsamReg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C2;
    tmp &= ~(CMP_C2_NSAM_MASK);
    tmp &= CMP_C2_WITHOUT_W1C_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C2_NSAM_SHIFT)) & CMP_C2_NSAM_MASK);
    obj->C2 = tmp;
}

/*! \brief Get the current CMP CH0F register
 *
 * This function gets the current CMP CH0F register .
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP CH0F register configuration.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetCh0fReg(const CmpRegType *obj)
{
    return ((obj->C2 & CMP_C2_CH0F_MASK) >> CMP_C2_CH0F_SHIFT);
}

/*! \brief Clear CMP CH0F register
 *
 * This function clear CMP CH0F register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 * This register write 1 to Clear
 *
 * \param[in] obj  : pointer to CMP register instance
 */
__attribute__((always_inline)) static inline void CmpReg_ClearCh0fReg(CmpRegType *obj)
{
    uint32_t tmp = obj->C2;
    tmp &= ~(CMP_C2_CHnF_MASK);
    tmp |= (((uint32_t)(((uint32_t)(1u)) << CMP_C2_CH0F_SHIFT)) & CMP_C2_CH0F_MASK);
    obj->C2 = tmp;
    (void)(obj->C2);
}

/*! \brief Get the current CMP CH1F register
 *
 * This function gets the current CMP CH1F register .
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP CH1F register configuration.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetCh1fReg(const CmpRegType *obj)
{
    return ((obj->C2 & CMP_C2_CH1F_MASK) >> CMP_C2_CH1F_SHIFT);
}

/*! \brief Clear CMP CH1F register
 *
 * This function clear CMP CH1F register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 * This register write 1 to Clear
 *
 * \param[in] obj  : pointer to CMP register instance
 */
__attribute__((always_inline)) static inline void CmpReg_ClearCh1fReg(CmpRegType *obj)
{
    uint32_t tmp = obj->C2;
    tmp &= ~(CMP_C2_CHnF_MASK);
    tmp |= (((uint32_t)(((uint32_t)(1u)) << CMP_C2_CH1F_SHIFT)) & CMP_C2_CH1F_MASK);
    obj->C2 = tmp;
    (void)(obj->C2);
}

/*! \brief Get the current CMP CH2F register
 *
 * This function gets the current CMP CH2F register .
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP CH2F register configuration.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetCh2fReg(const CmpRegType *obj)
{
    return ((obj->C2 & CMP_C2_CH2F_MASK) >> CMP_C2_CH2F_SHIFT);
}

/*! \brief Clear CMP CH2F register
 *
 * This function clear CMP CH2F register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 * This register write 1 to Clear
 *
 * \param[in] obj  : pointer to CMP register instance
 */
__attribute__((always_inline)) static inline void CmpReg_ClearCh2fReg(CmpRegType *obj)
{
    uint32_t tmp = obj->C2;
    tmp &= ~(CMP_C2_CHnF_MASK);
    tmp |= (((uint32_t)(((uint32_t)(1u)) << CMP_C2_CH2F_SHIFT)) & CMP_C2_CH2F_MASK);
    obj->C2 = tmp;
    (void)(obj->C2);
}

/*! \brief Get the current CMP CH3F register
 *
 * This function gets the current CMP CH3F register .
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP CH3F register configuration.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetCh3fReg(const CmpRegType *obj)
{
    return ((obj->C2 & CMP_C2_CH3F_MASK) >> CMP_C2_CH3F_SHIFT);
}

/*! \brief Clear CMP CH3F register
 *
 * This function clear CMP CH3F register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 * This register write 1 to Clear
 *
 * \param[in] obj  : pointer to CMP register instance
 */
__attribute__((always_inline)) static inline void CmpReg_ClearCh3fReg(CmpRegType *obj)
{
    uint32_t tmp = obj->C2;
    tmp &= ~(CMP_C2_CHnF_MASK);
    tmp |= (((uint32_t)(((uint32_t)(1u)) << CMP_C2_CH3F_SHIFT)) & CMP_C2_CH3F_MASK);
    obj->C2 = tmp;
    (void)(obj->C2);
}

/*! \brief Get the current CMP CH4F register
 *
 * This function gets the current CMP CH4F register .
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP CH4F register configuration.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetCh4fReg(const CmpRegType *obj)
{
    return ((obj->C2 & CMP_C2_CH4F_MASK) >> CMP_C2_CH4F_SHIFT);
}

/*! \brief Clear CMP CH4F register
 *
 * This function clear CMP CH4F register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 * This register write 1 to Clear
 *
 * \param[in] obj  : pointer to CMP register instance
 */
__attribute__((always_inline)) static inline void CmpReg_ClearCh4fReg(CmpRegType *obj)
{
    uint32_t tmp = obj->C2;
    tmp &= ~(CMP_C2_CHnF_MASK);
    tmp |= (((uint32_t)(((uint32_t)(1u)) << CMP_C2_CH4F_SHIFT)) & CMP_C2_CH4F_MASK);
    obj->C2 = tmp;
    (void)(obj->C2);
}

/*! \brief Get the current CMP CH5F register
 *
 * This function gets the current CMP CH5F register .
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP CH5F register configuration.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetCh5fReg(const CmpRegType *obj)
{
    return ((obj->C2 & CMP_C2_CH5F_MASK) >> CMP_C2_CH5F_SHIFT);
}

/*! \brief Clear CMP CH5F register
 *
 * This function clear CMP CH5F register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 * This register write 1 to Clear
 *
 * \param[in] obj  : pointer to CMP register instance
 */
__attribute__((always_inline)) static inline void CmpReg_ClearCh5fReg(CmpRegType *obj)
{
    uint32_t tmp = obj->C2;
    tmp &= ~(CMP_C2_CHnF_MASK);
    tmp |= (((uint32_t)(((uint32_t)(1u)) << CMP_C2_CH5F_SHIFT)) & CMP_C2_CH5F_MASK);
    obj->C2 = tmp;
    (void)(obj->C2);
}

/*! \brief Get the current CMP CH6F register
 *
 * This function gets the current CMP CH6F register .
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP CH6F register configuration.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetCh6fReg(const CmpRegType *obj)
{
    return ((obj->C2 & CMP_C2_CH6F_MASK) >> CMP_C2_CH6F_SHIFT);
}

/*! \brief Clear CMP CH6F register
 *
 * This function clear CMP CH6F register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 * This register write 1 to Clear
 *
 * \param[in] obj  : pointer to CMP register instance
 */
__attribute__((always_inline)) static inline void CmpReg_ClearCh6fReg(CmpRegType *obj)
{
    uint32_t tmp = obj->C2;
    tmp &= ~(CMP_C2_CHnF_MASK);
    tmp |= (((uint32_t)(((uint32_t)(1u)) << CMP_C2_CH6F_SHIFT)) & CMP_C2_CH6F_MASK);
    obj->C2 = tmp;
    (void)(obj->C2);
}

/*! \brief Get the current CMP CH7F register
 *
 * This function gets the current CMP CH6F register .
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP CH7F register configuration.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetCh7fReg(const CmpRegType *obj)
{
    return ((obj->C2 & CMP_C2_CH7F_MASK) >> CMP_C2_CH7F_SHIFT);
}

/*! \brief Clear CMP CH7F register
 *
 * This function clear CMP CH7F register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 * This register write 1 to Clear
 *
 * \param[in] obj  : pointer to CMP register instance
 */
__attribute__((always_inline)) static inline void CmpReg_ClearCh7fReg(CmpRegType *obj)
{
    uint32_t tmp = obj->C2;
    tmp &= ~(CMP_C2_CHnF_MASK);
    tmp |= (((uint32_t)(((uint32_t)(1u)) << CMP_C2_CH7F_SHIFT)) & CMP_C2_CH7F_MASK);
    obj->C2 = tmp;
    (void)(obj->C2);
}

/*! \brief Get the current CMP FXMXCH register
 *
 * This function gets the current CMP FXMXCH register .
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP FXMXCH register configuration.
 * - 000b: Channel 0 is selected as the fixed reference input for the fixed mux port.
 * - 001b: Channel 1 is selected as the fixed reference input for the fixed mux port.
 * - 010b: Channel 2 is selected as the fixed reference input for the fixed mux port.
 * - 011b: Channel 3 is selected as the fixed reference input for the fixed mux port.
 * - 100b: Channel 4 is selected as the fixed reference input for the fixed mux port.
 * - 101b: Channel 5 is selected as the fixed reference input for the fixed mux port.
 * - 110b: Channel 6 is selected as the fixed reference input for the fixed mux port.
 * - 111b: Channel 7 is selected as the fixed reference input for the fixed mux port.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetFxmxchReg(const CmpRegType *obj)
{
    return ((obj->C2 & CMP_C2_FXMXCH_MASK) >> CMP_C2_FXMXCH_SHIFT);
}

/*! \brief Set CMP FXMXCH configuration
 *
 * This function writes new configuration to CMP FXMXCH register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP FXMXCH register configuration
 * - 000b: Channel 0 is selected as the fixed reference input for the fixed mux port.
 * - 001b: Channel 1 is selected as the fixed reference input for the fixed mux port.
 * - 010b: Channel 2 is selected as the fixed reference input for the fixed mux port.
 * - 011b: Channel 3 is selected as the fixed reference input for the fixed mux port.
 * - 100b: Channel 4 is selected as the fixed reference input for the fixed mux port.
 * - 101b: Channel 5 is selected as the fixed reference input for the fixed mux port.
 * - 110b: Channel 6 is selected as the fixed reference input for the fixed mux port.
 * - 111b: Channel 7 is selected as the fixed reference input for the fixed mux port.
 */
__attribute__((always_inline)) static inline void CmpReg_SetFxmxchReg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C2;
    tmp &= ~(CMP_C2_FXMXCH_MASK);
    tmp &= CMP_C2_WITHOUT_W1C_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C2_FXMXCH_SHIFT)) & CMP_C2_FXMXCH_MASK);
    obj->C2 = tmp;
}

/*! \brief Get the current CMP FXMP register
 *
 * This function gets the current CMP FXMP register .
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP FXMP register configuration.
 * 0b: The Plus port is fixed. Only the inputs to the Minus port are swept in each round.
 * 1b: The Minus port is fixed. Only the inputs to the Plus port are swept in each round.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetFxmpReg(const CmpRegType *obj)
{
    return ((obj->C2 & CMP_C2_FXMP_MASK) >> CMP_C2_FXMP_SHIFT);
}

/*! \brief Set CMP FXMP configuration
 *
 * This function writes new configuration to CMP FXMP register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP FXMP register configuration
 * 0b: The Plus port is fixed. Only the inputs to the Minus port are swept in each round.
 * 1b: The Minus port is fixed. Only the inputs to the Plus port are swept in each round.
 */
__attribute__((always_inline)) static inline void CmpReg_SetFxmpReg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C2;
    tmp &= ~(CMP_C2_FXMP_MASK);
    tmp &= CMP_C2_WITHOUT_W1C_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C2_FXMP_SHIFT)) & CMP_C2_FXMP_MASK);
    obj->C2 = tmp;
}

/*! \brief Get the current CMP RRIE register
 *
 * This function gets the current CMP RRIE register .
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP RRIE register configuration.
 * - 0b: The round-robin interrupt is disabled.
 * - 1b: The round-robin interrupt is enabled when a comparison result changes from the last sample.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetRrieReg(const CmpRegType *obj)
{
    return ((obj->C2 & CMP_C2_RRIE_MASK) >> CMP_C2_RRIE_SHIFT);
}

/*! \brief Set CMP RRIE configuration
 *
 * This function writes new configuration to CMP RRIE register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP RRIE register configuration
 * - 0b: The round-robin interrupt is disabled.
 * - 1b: The round-robin interrupt is enabled when a comparison result changes from the last sample.
 */
__attribute__((always_inline)) static inline void CmpReg_SetRrieReg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C2;
    tmp &= ~(CMP_C2_RRIE_MASK);
    tmp &= CMP_C2_WITHOUT_W1C_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C2_RRIE_SHIFT)) & CMP_C2_RRIE_MASK);
    obj->C2 = tmp;
}

/*! \brief Get the current CMP RRE register
 *
 * This function gets the current CMP RRE register .
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to CMP register instance
 * \return the current CMP RRE register configuration.
 * - 0b: Round-robin operation is disabled.
 * - 1b: Round-robin operation is enabled.
 */
__attribute__((always_inline)) static inline uint8_t CmpReg_GetRreReg(const CmpRegType *obj)
{
    return ((obj->C2 & CMP_C2_RRE_MASK) >> CMP_C2_RRE_SHIFT);
}

/*! \brief Set CMP RRE configuration
 *
 * This function writes new configuration to CMP RRE register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj  : pointer to CMP register instance
 * \param[in] value : expected CMP RRE register configuration
 * - 0b: Round-robin operation is disabled.
 * - 1b: Round-robin operation is enabled.
 */
__attribute__((always_inline)) static inline void CmpReg_SetRreReg(CmpRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->C2;
    tmp &= ~(CMP_C2_RRE_MASK);
    tmp &= CMP_C2_WITHOUT_W1C_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMP_C2_RRE_SHIFT)) & CMP_C2_RRE_MASK);
    obj->C2 = tmp;
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _CMP_REG_H_ */
