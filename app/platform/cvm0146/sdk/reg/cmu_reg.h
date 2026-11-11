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

#ifndef _CMU_REG_H_
#define _CMU_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the CMU Registers
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

/* GCR Bit Fields */
#define CMU_GCR_EN_MASK           (0x01u)
#define CMU_GCR_EN_SHIFT          (0u)
#define CMU_GCR_EN_WIDTH          (1u)

/* RCCR Bit Fields */
#define CMU_RCCR_REF_CNT_MASK     (0xFFFFu)
#define CMU_RCCR_REF_CNT_SHIFT    (0u)
#define CMU_RCCR_REF_CNT_WIDTH    (16u)

/* HTCR Bit Fields */
#define CMU_HTCR_HFREF_MASK       (0xFFFFFFu)
#define CMU_HTCR_HFREF_SHIFT      (0u)
#define CMU_HTCR_HFREF_WIDTH      (24u)

/* LTCR Bit Fields */
#define CMU_LTCR_LFREF_MASK       (0xFFFFFFu)
#define CMU_LTCR_LFREF_SHIFT      (0u)
#define CMU_LTCR_LFREF_WIDTH      (24u)

/* SR Bit Fields */
#define CMU_SR_RS_MASK            (0x10u)
#define CMU_SR_RS_SHIFT           (4u)
#define CMU_SR_RS_WIDTH           (1u)
#define CMU_SR_FHH_MASK           (0x02u)
#define CMU_SR_FHH_SHIFT          (1u)
#define CMU_SR_FHH_WIDTH          (1u)
#define CMU_SR_FLL_MASK           (0x01u)
#define CMU_SR_FLL_SHIFT          (0u)
#define CMU_SR_FLL_WIDTH          (1u)

/* IER Bit Fields */
#define CMU_IER_FHHIE_MASK        (0x0Cu)
#define CMU_IER_FHHIE_SHIFT       (2u)
#define CMU_IER_FHHIE_WIDTH       (2u)
#define CMU_IER_FLLIE_MASK        (0x03u)
#define CMU_IER_FLLIE_SHIFT       (0u)
#define CMU_IER_FLLIE_WIDTH       (2u)

/* PVT_KEY Bit Fields */
#define CMU_PVT_KEY_KEY_MASK      (0xFFFFFFFFu) /*!<CMU PVT_KEY: KEY Mask */
#define CMU_PVT_KEY_KEY_SHIFT     (0)           /*!<CMU PVT_KEY: KEY Position */
#define CMU_PVT_KEY_KEY_WIDTH     (32)          /*!<CMU PVT_KEY: KEY width */

/* PVT_LKST Bit Fields */
#define CMU_PVT_LKST_UNLOCK_MASK  (0x1u) /*!<CMU PVT_LKST: UNLOCK Mask */
#define CMU_PVT_LKST_UNLOCK_SHIFT (0)    /*!<CMU PVT_LKST: UNLOCK Position */
#define CMU_PVT_LKST_UNLOCK_WIDTH (1)    /*!<CMU PVT_LKST: UNLOCK width */

/* PVT_CR Bit Fields */
#define CMU_PVT_CR_TEST_MASK      (0x1u) /*!<CMU PVT_CR: TEST Mask */
#define CMU_PVT_CR_TEST_SHIFT     (0)    /*!<CMU PVT_CR: TEST Position */
#define CMU_PVT_CR_TEST_WIDTH     (1)    /*!<CMU PVT_CR: TEST width */

/* PVT_ST Bit Fields */
#define CMU_PVT_ST_MON_CNT_MASK   (0xFFFFFFu)  /*!<CMU PVT_ST: MON_CNT Mask */
#define CMU_PVT_ST_MON_CNT_SHIFT  (0)          /*!<CMU PVT_ST: MON_CNT Position */
#define CMU_PVT_ST_MON_CNT_WIDTH  (24)         /*!<CMU PVT_ST: MON_CNT width */
#define CMU_PVT_ST_CNT_VLD_MASK   (0x1000000u) /*!<CMU PVT_ST: CNT_VLD Mask */
#define CMU_PVT_ST_CNT_VLD_SHIFT  (24)         /*!<CMU PVT_ST: CNT_VLD Position */
#define CMU_PVT_ST_CNT_VLD_WIDTH  (1)          /*!<CMU PVT_ST: CNT_VLD width */

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief The definition of CMU registers
 */
typedef struct _CmuRegType_
{
    volatile uint32_t GCR;          /*!< CMU global config register, offset: 0x0 */
    volatile uint32_t RCCR;         /*!< CMU reference counter value config register, offset: 0x4 */
    volatile uint32_t HTCR;         /*!< CMU high threshold value config register, offset: 0x8 */
    volatile uint32_t LTCR;         /*!< CMU low threshold value config register, offset: 0xC */
    volatile uint32_t SR;           /*!< CMU status register, offset: 0x10 */
    volatile uint32_t IER;          /*!< CMU interrupt enable register, offset: 0x14 */
} CmuRegType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Gets the CMU enable
 *
 * This function gets the CMU enable
 *
 * \param[in] obj : pointer to CMU register instance
 * \return CMU enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t CmuReg_GetEnable(const CmuRegType *obj)
{
    return ((obj->GCR & CMU_GCR_EN_MASK) >> CMU_GCR_EN_SHIFT);
}

/*! \brief Sets the CMU enable
 *
 * This function sets the CMU enable
 *
 * \param[in] obj : pointer to CMU register instance
 * \param[in] value : the value of CMU enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline void CmuReg_SetEnable(CmuRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->GCR;

    tmp &= ~CMU_GCR_EN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMU_GCR_EN_SHIFT)) & CMU_GCR_EN_MASK);
    obj->GCR = tmp;
}

/*! \brief Gets the reference counter value
 *
 * This function gets the reference counter value
 *
 * \param[in] obj : pointer to CMU register instance
 * \return reference counter value
 *         - 0000h : 0
 *         - 0001h : 1
 *         - 0002h : 2
 *            .
 *            .
 *            .
 *         - FFFFh : 65535
 */
__attribute__((always_inline)) static inline uint32_t CmuReg_GetRefCnt(const CmuRegType *obj)
{
    return ((obj->RCCR & CMU_RCCR_REF_CNT_MASK) >> CMU_RCCR_REF_CNT_SHIFT);
}

/*! \brief Sets the reference counter value
 *
 * This function sets the reference counter value
 *
 * \param[in] obj : pointer to CMU register instance
 * \param[in] value : reference counter value
 *                    - 0000h : 0
 *                    - 0001h : 1
 *                    - 0002h : 2
 *                       .
 *                       .
 *                       .
 *                    - FFFFh : 65535
 */
__attribute__((always_inline)) static inline void CmuReg_SetRefCnt(CmuRegType *obj, uint32_t value)
{
    uint32_t tmp = obj->RCCR;

    tmp &= ~CMU_RCCR_REF_CNT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMU_RCCR_REF_CNT_SHIFT)) & CMU_RCCR_REF_CNT_MASK);
    obj->RCCR = tmp;
}

/*! \brief Gets the high threshold value
 *
 * This function gets the high threshold value
 *
 * \param[in] obj : pointer to CMU register instance
 * \return high threshold value
 *         - 000000h : 0
 *         - 000001h : 1
 *         - 000002h : 2
 *            .
 *            .
 *            .
 *         - FFFFFFh : 16,777,215
 */
__attribute__((always_inline)) static inline uint32_t CmuReg_GetFreqHighRefValue(const CmuRegType *obj)
{
    return ((obj->HTCR & CMU_HTCR_HFREF_MASK) >> CMU_HTCR_HFREF_SHIFT);
}

/*! \brief Sets the high threshold value
 *
 * This function sets the high threshold value
 *
 * \param[in] obj : pointer to CMU register instance
 * \param[in] value : high threshold value
 *                    - 000000h : 0
 *                    - 000001h : 1
 *                    - 000002h : 2
 *                       .
 *                       .
 *                       .
 *                    - FFFFFFh : 16,777,215
 */
__attribute__((always_inline)) static inline void CmuReg_SetFreqHighRefValue(CmuRegType *obj, uint32_t value)
{
    uint32_t tmp = obj->HTCR;

    tmp &= ~CMU_HTCR_HFREF_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMU_HTCR_HFREF_SHIFT)) & CMU_HTCR_HFREF_MASK);
    obj->HTCR = tmp;
}

/*! \brief Gets the low threshold value
 *
 * This function gets the low threshold value
 *
 * \param[in] obj : pointer to CMU register instance
 * \return low threshold value
 *         - 000000h : 0
 *         - 000001h : 1
 *         - 000002h : 2
 *            .
 *            .
 *            .
 *         - FFFFFFh : 16,777,215
 */
__attribute__((always_inline)) static inline uint32_t CmuReg_GetFreqLowRefValue(const CmuRegType *obj)
{
    return ((obj->LTCR & CMU_LTCR_LFREF_MASK) >> CMU_LTCR_LFREF_SHIFT);
}

/*! \brief Sets the low threshold value
 *
 * This function sets the low threshold value
 *
 * \param[in] obj : pointer to CMU register instance
 * \param[in] value : low threshold value
 *                    - 000000h : 0
 *                    - 000001h : 1
 *                    - 000002h : 2
 *                       .
 *                       .
 *                       .
 *                    - FFFFFFh : 16,777,215
 */
__attribute__((always_inline)) static inline void CmuReg_SetFreqLowRefValue(CmuRegType *obj, uint32_t value)
{
    uint32_t tmp = obj->LTCR;

    tmp &= ~CMU_LTCR_LFREF_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMU_LTCR_LFREF_SHIFT)) & CMU_LTCR_LFREF_MASK);
    obj->LTCR = tmp;
}

/*! \brief Gets the CMU run status
 *
 * Indicates the CMU run status
 *
 * \param[in] obj : pointer to CMU register instance
 * \return CMU run status
 *         - 0b : false
 *         - 1b : true
 */
__attribute__((always_inline)) static inline uint8_t CmuReg_GetRunStatus(const CmuRegType *obj)
{
    return ((obj->SR & CMU_SR_RS_MASK) >> CMU_SR_RS_SHIFT);
}

/*! \brief Gets the frequency higher event flag
 *
 * FHH is set when the CMU is enabled and the frequency detected is higher than high threshold value
 *
 * \param[in] obj : pointer to CMU register instance
 * \return frequency higher event flag
 *         - 0b : false
 *         - 1b : true
 */
__attribute__((always_inline)) static inline uint8_t CmuReg_GetFreqHighEventFlag(const CmuRegType *obj)
{
    return ((obj->SR & CMU_SR_FHH_MASK) >> CMU_SR_FHH_SHIFT);
}

/*! \brief Clear the frequency higher event flag
 *
 * FHH is cleared when a logic 1 is written to it.
 *
 * \param[in] obj : pointer to CMU register instance
 * \return none
 *
 */
__attribute__((always_inline)) static inline void CmuReg_ClearFreqHighEventFlag(CmuRegType *obj)
{
    uint32_t tmp = obj->SR;
    tmp &= ~(CMU_SR_FHH_MASK | CMU_SR_FLL_MASK);
    tmp |= (CMU_SR_FHH_MASK);
    obj->SR = tmp;
    /* Read back to avoid problem */
    (void)obj->SR;
}

/*! \brief Gets the frequency lower event flag
 *
 * FLL is set when the CMU is enabled and the frequency detected is lower than low threshold value
 *
 * \param[in] obj : pointer to CMU register instance
 * \return frequency Lower event flag
 *         - 0b : false
 *         - 1b : true
 */
__attribute__((always_inline)) static inline uint8_t CmuReg_GetFreqLowEventFlag(const CmuRegType *obj)
{
    return ((obj->SR & CMU_SR_FLL_MASK) >> CMU_SR_FLL_SHIFT);
}

/*! \brief Clear the frequency lower event flag
 *
 * FHH is cleared when a logic 1 is written to it.
 *
 * \param[in] obj : pointer to CMU register instance
 * \return none
 *
 */
__attribute__((always_inline)) static inline void CmuReg_ClearFreqLowEventFlag(CmuRegType *obj)
{
    uint32_t tmp = obj->SR;
    tmp &= ~(CMU_SR_FHH_MASK | CMU_SR_FLL_MASK);
    tmp |= (CMU_SR_FLL_MASK);
    obj->SR = tmp;
    /* Read back to avoid problem */
    (void)obj->SR;
}

/*! \brief Gets the frequency high event state
 *
 * This function gets the frequency high event state
 *
 * \param[in] obj : pointer to CMU register instance
 * \return frequency higher interrupt enable
 *         - 00b : interrupt and reset disable
 *         - 01b : interrupt enable, reset disable
 *         - 10b : interrupt disable, reset enable
 *         - 11b : interrupt disable, reset enable
 */
__attribute__((always_inline)) static inline uint8_t CmuReg_GetFreqHighEventState(const CmuRegType *obj)
{
    return ((obj->IER & CMU_IER_FHHIE_MASK) >> CMU_IER_FHHIE_SHIFT);
}

/*! \brief Sets the frequency high event state
 *
 * This function sets the frequency high event state
 *
 * \param[in] obj : pointer to CMU register instance
 * \param[in] value : the value of the frequency high event state
 *         - 00b : interrupt and reset disable
 *         - 01b : interrupt enable, reset disable
 *         - 10b : interrupt disable, reset enable
 *         - 11b : interrupt disable, reset enable
 */
__attribute__((always_inline)) static inline void CmuReg_SetFreqHighEventState(CmuRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->IER;

    tmp &= ~CMU_IER_FHHIE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMU_IER_FHHIE_SHIFT)) & CMU_IER_FHHIE_MASK);
    obj->IER = tmp;
}

/*! \brief Gets the frequency low event state
 *
 * This function gets the frequency low event state
 *
 * \param[in] obj : pointer to CMU register instance
 * \return frequency lower interrupt enable
 *         - 00b : interrupt and reset disable
 *         - 01b : interrupt enable, reset disable
 *         - 10b : interrupt disable, reset enable
 *         - 11b : interrupt disable, reset enable
 */
__attribute__((always_inline)) static inline uint8_t CmuReg_GetFreqLowEventState(const CmuRegType *obj)
{
    return ((obj->IER & CMU_IER_FLLIE_MASK) >> CMU_IER_FLLIE_SHIFT);
}

/*! \brief Sets the frequency low event state
 *
 * This function sets the frequency low event state
 *
 * \param[in] obj : pointer to CMU register instance
 * \param[in] value : the value of the frequency low event state
 *         - 00b : interrupt and reset disable
 *         - 01b : interrupt enable, reset disable
 *         - 10b : interrupt disable, reset enable
 *         - 11b : interrupt disable, reset enable
 */
__attribute__((always_inline)) static inline void CmuReg_SetFreqLowEventState(CmuRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->IER;

    tmp &= ~CMU_IER_FLLIE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << CMU_IER_FLLIE_SHIFT)) & CMU_IER_FLLIE_MASK);
    obj->IER = tmp;
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _CMU_REG_H_ */
