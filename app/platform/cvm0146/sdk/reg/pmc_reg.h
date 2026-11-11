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

#ifndef _PMC_REG_H_
#define _PMC_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the PMC Registers
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

/* WKSRC Bit Fields */
#define PMC_WKSRC_STOP_ST_FLG_MASK            (0x800u)
#define PMC_WKSRC_STOP_ST_FLG_SHIFT           (11u)
#define PMC_WKSRC_STOP_ST_FLG_WIDTH           (1u)
#define PMC_WKSRC_STBY_ST_FLG_MASK            (0x400u)
#define PMC_WKSRC_STBY_ST_FLG_SHIFT           (10u)
#define PMC_WKSRC_STBY_ST_FLG_WIDTH           (1u)
#define PMC_WKSRC_CMP_WAKEUP_MASK             (0x200u)
#define PMC_WKSRC_CMP_WAKEUP_SHIFT            (9u)
#define PMC_WKSRC_CMP_WAKEUP_WIDTH            (1u)
#define PMC_WKSRC_LPTMR_WAKEUP_MASK           (0x100u)
#define PMC_WKSRC_LPTMR_WAKEUP_SHIFT          (8u)
#define PMC_WKSRC_LPTMR_WAKEUP_WIDTH          (1u)
#define PMC_WKSRC_LPIT_WAKEUP_MASK            (0x80u)
#define PMC_WKSRC_LPIT_WAKEUP_SHIFT           (7u)
#define PMC_WKSRC_LPIT_WAKEUP_WIDTH           (1u)
#define PMC_WKSRC_RTC_WAKEUP_MASK             (0x40u)
#define PMC_WKSRC_RTC_WAKEUP_SHIFT            (6u)
#define PMC_WKSRC_RTC_WAKEUP_WIDTH            (1u)
#define PMC_WKSRC_RESET_WAKEUP_MASK           (0x20u)
#define PMC_WKSRC_RESET_WAKEUP_SHIFT          (5u)
#define PMC_WKSRC_RESET_WAKEUP_WIDTH          (1u)
#define PMC_WKSRC_PORTE_WAKEUP_MASK           (0x10u)
#define PMC_WKSRC_PORTE_WAKEUP_SHIFT          (4u)
#define PMC_WKSRC_PORTE_WAKEUP_WIDTH          (1u)
#define PMC_WKSRC_PORTD_WAKEUP_MASK           (0x08u)
#define PMC_WKSRC_PORTD_WAKEUP_SHIFT          (3u)
#define PMC_WKSRC_PORTD_WAKEUP_WIDTH          (1u)
#define PMC_WKSRC_PORTC_WAKEUP_MASK           (0x04u)
#define PMC_WKSRC_PORTC_WAKEUP_SHIFT          (2u)
#define PMC_WKSRC_PORTC_WAKEUP_WIDTH          (1u)
#define PMC_WKSRC_PORTB_WAKEUP_MASK           (0x02u)
#define PMC_WKSRC_PORTB_WAKEUP_SHIFT          (1u)
#define PMC_WKSRC_PORTB_WAKEUP_WIDTH          (1u)
#define PMC_WKSRC_PORTA_WAKEUP_MASK           (0x01u)
#define PMC_WKSRC_PORTA_WAKEUP_SHIFT          (0u)
#define PMC_WKSRC_PORTA_WAKEUP_WIDTH          (1u)

/* PKP Bit Fields */
#define PMC_PKP_PAD_KEEP_MASK                 (0x01u)
#define PMC_PKP_PAD_KEEP_SHIFT                (0u)
#define PMC_PKP_PAD_KEEP_WIDTH                (1u)

/* ANACTRL Bit Fields */
#define PMC_ANACTRL_AD_HPBG_OTP_MASK          (0x200000u)
#define PMC_ANACTRL_AD_HPBG_OTP_SHIFT         (21u)
#define PMC_ANACTRL_AD_HPBG_OTP_WIDTH         (1u)
#define PMC_ANACTRL_AD_PMC_FLDO_LVD_MASK      (0x100000u)
#define PMC_ANACTRL_AD_PMC_FLDO_LVD_SHIFT     (20u)
#define PMC_ANACTRL_AD_PMC_FLDO_LVD_WIDTH     (1u)
#define PMC_ANACTRL_AD_PMC_OVD11_MASK         (0x80000u)
#define PMC_ANACTRL_AD_PMC_OVD11_SHIFT        (19u)
#define PMC_ANACTRL_AD_PMC_OVD11_WIDTH        (1u)
#define PMC_ANACTRL_AD_PMC_OVD_MASK           (0x40000u)
#define PMC_ANACTRL_AD_PMC_OVD_SHIFT          (18u)
#define PMC_ANACTRL_AD_PMC_OVD_WIDTH          (1u)
#define PMC_ANACTRL_AD_PMC_LVD_MASK           (0x20000u)
#define PMC_ANACTRL_AD_PMC_LVD_SHIFT          (17u)
#define PMC_ANACTRL_AD_PMC_LVD_WIDTH          (1u)
#define PMC_ANACTRL_AD_PMC_LVW_MASK           (0x10000u)
#define PMC_ANACTRL_AD_PMC_LVW_SHIFT          (16u)
#define PMC_ANACTRL_AD_PMC_LVW_WIDTH          (1u)
#define PMC_ANACTRL_DA_HPBG_OTP_EN_MASK       (0x80u)
#define PMC_ANACTRL_DA_HPBG_OTP_EN_SHIFT      (7u)
#define PMC_ANACTRL_DA_HPBG_OTP_EN_WIDTH      (1u)
#define PMC_ANACTRL_DA_PMC_SEL_LVW_MASK       (0x60u)
#define PMC_ANACTRL_DA_PMC_SEL_LVW_SHIFT      (5u)
#define PMC_ANACTRL_DA_PMC_SEL_LVW_WIDTH      (2u)
#define PMC_ANACTRL_DA_PMC_EN_FLDO_VDET_MASK  (0x10u)
#define PMC_ANACTRL_DA_PMC_EN_FLDO_VDET_SHIFT (4u)
#define PMC_ANACTRL_DA_PMC_EN_FLDO_VDET_WIDTH (1u)
#define PMC_ANACTRL_DA_PMC_EN_OVD11_MASK      (0x08u)
#define PMC_ANACTRL_DA_PMC_EN_OVD11_SHIFT     (3u)
#define PMC_ANACTRL_DA_PMC_EN_OVD11_WIDTH     (1u)
#define PMC_ANACTRL_DA_PMC_EN_OVD_MASK        (0x04u)
#define PMC_ANACTRL_DA_PMC_EN_OVD_SHIFT       (2u)
#define PMC_ANACTRL_DA_PMC_EN_OVD_WIDTH       (1u)
#define PMC_ANACTRL_DA_PMC_EN_LVD_MASK        (0x02u)
#define PMC_ANACTRL_DA_PMC_EN_LVD_SHIFT       (1u)
#define PMC_ANACTRL_DA_PMC_EN_LVD_WIDTH       (1u)
#define PMC_ANACTRL_DA_PMC_EN_LVW_MASK        (0x01u)
#define PMC_ANACTRL_DA_PMC_EN_LVW_SHIFT       (0u)
#define PMC_ANACTRL_DA_PMC_EN_LVW_WIDTH       (1u)

/* UIDET Bit Fields */
#define PMC_UIDET_AD_PMC_LPBG_LVD_MASK        (0x20000u)
#define PMC_UIDET_AD_PMC_LPBG_LVD_SHIFT       (17u)
#define PMC_UIDET_AD_PMC_LPBG_LVD_WIDTH       (1u)
#define PMC_UIDET_AD_PMC_LPBG_OVD_MASK        (0x10000u)
#define PMC_UIDET_AD_PMC_LPBG_OVD_SHIFT       (16u)
#define PMC_UIDET_AD_PMC_LPBG_OVD_WIDTH       (1u)
#define PMC_UIDET_DA_PMC_EN_LPBG_OVD_MASK     (0x02u)
#define PMC_UIDET_DA_PMC_EN_LPBG_OVD_SHIFT    (1u)
#define PMC_UIDET_DA_PMC_EN_LPBG_OVD_WIDTH    (1u)
#define PMC_UIDET_DA_PMC_EN_LPBG_LVD_MASK     (0x01u)
#define PMC_UIDET_DA_PMC_EN_LPBG_LVD_SHIFT    (0u)
#define PMC_UIDET_DA_PMC_EN_LPBG_LVD_WIDTH    (1u)

/* KEY Bit Fields */
#define PMC_KEY_KEY_VAL_MASK                  (0xFFFFFFFFu)
#define PMC_KEY_KEY_VAL_SHIFT                 (0u)
#define PMC_KEY_KEY_VAL_WIDTH                 (32u)

/* UNLOCK Bit Fields */
#define PMC_UNLOCK_UNLOCK_MASK                (0x01u)
#define PMC_UNLOCK_UNLOCK_SHIFT               (0u)
#define PMC_UNLOCK_UNLOCK_WIDTH               (1u)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief The definition of PMC registers
 */
typedef struct _PmcRegType_
{
    volatile uint32_t WKSRC;        /*!< PMC wakeup source regsiter, offset: 0x00 */
    volatile uint32_t PKP;          /*!< PMC pad keep control register, offset: 0x04 */
    volatile uint32_t ANACTRL;      /*!< PMC analog interface signal control register, offset: 0x08 */
    volatile uint32_t UIDET;        /*!< PMC analog abnormal state detection register, offset: 0x0C */
    uint32_t          RESERVED2[8]; /*!< Reserverd block, offset: 0x10 */
    volatile uint32_t KEY;       /*!< PMC key register, offset: 0x30 */
    volatile uint32_t UNLOCK;   /*!< PMC key unlock indicator register, offset: 0x34 */
} PmcRegType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Gets the STOP state flag
 *
 * This function gets the current STOP state flag.
 * This bit indicates that PMC went through STOP mode before. Write 1 to this bit clears it.
 *
 * \param[in] obj : pointer to PMC register instance
 * \return STOP state flag
 *         - 0b : PMC did not go through STOP mode
 *         - 1b : PMC went through STOP mode
 */
__attribute__((always_inline)) static inline uint8_t PmcReg_GetWkSrcStopStFlg(const PmcRegType *obj)
{
    return ((obj->WKSRC & PMC_WKSRC_STOP_ST_FLG_MASK) >> PMC_WKSRC_STOP_ST_FLG_SHIFT);
}

/*! \brief Sets the STOP state flag
 *
 * This function sets the STOP state flag.
 * This bit indicates that PMC went through STOP mode before. Write 1 to this bit clears it.
 *
 * \param[in] obj : pointer to PMC register instance
 * \param[in] value : the value of STOP state flag
 *                    - 0b : PMC did not go through STOP mode
 *                    - 1b : PMC went through STOP mode
 */
__attribute__((always_inline)) static inline void PmcReg_SetWkSrcStopStFlg(PmcRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << PMC_WKSRC_STOP_ST_FLG_SHIFT)) & PMC_WKSRC_STOP_ST_FLG_MASK);
    obj->WKSRC   = tmp;
}

/*! \brief Gets the STANDBY state flag
 *
 * This function gets the current STANDBY state flag.
 * This bit indicates that PMC went through STANDBY mode before.  If power state transfer to STANDBY mode is aborted, this bit will not be asserted. Write 1 to this bit clears it.
 *
 * \param[in] obj : pointer to PMC register instance
 * \return STANDBY state flag
 *         - 0b : PMC did not go through STANDBY mode
 *         - 1b : PMC went through STANDBY mode
 */
__attribute__((always_inline)) static inline uint8_t PmcReg_GetWkSrcStbyStFlg(const PmcRegType *obj)
{
    return ((obj->WKSRC & PMC_WKSRC_STBY_ST_FLG_MASK) >> PMC_WKSRC_STBY_ST_FLG_SHIFT);
}

/*! \brief Sets the STANDBY state flag
 *
 * This function sets the STANDBY state flag.
 * This bit indicates that PMC went through STANDBY mode before.  If power state transfer to STANDBY mode is aborted, this bit will not be asserted. Write 1 to this bit clears it.
 *
 * \param[in] obj : pointer to PMC register instance
 * \param[in] value : the value of STANDBY state flag
 *                    - 0b : PMC did not go through STANDBY mode
 *                    - 1b : PMC went through STANDBY mode
 */
__attribute__((always_inline)) static inline void PmcReg_SetWkSrcStbyStFlg(PmcRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << PMC_WKSRC_STBY_ST_FLG_SHIFT)) & PMC_WKSRC_STBY_ST_FLG_MASK);
    obj->WKSRC   = tmp;
}

/*! \brief Gets the CMP wake up source flag
 *
 * This function gets the current CMP wake up source flag.
 *
 * \param[in] obj : pointer to PMC register instance
 * \return CMP wake up source flag
 *         - 0b : Wake up source not asserted
 *         - 1b : Wake up source asserted
 */
__attribute__((always_inline)) static inline uint8_t PmcReg_GetWkSrcCmpWakeup(const PmcRegType *obj)
{
    return ((obj->WKSRC & PMC_WKSRC_CMP_WAKEUP_MASK) >> PMC_WKSRC_CMP_WAKEUP_SHIFT);
}

/*! \brief Sets the CMP wake up source flag
 *
 * This function sets the CMP wake up source flag.
 *
 * \param[in] obj : pointer to PMC register instance
 * \param[in] value : the value of CMP wake up source flag
 *                    - 0b : Wake up source not asserted
 *                    - 1b : Wake up source asserted
 */
__attribute__((always_inline)) static inline void PmcReg_SetWkSrcCmpWakeup(PmcRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << PMC_WKSRC_CMP_WAKEUP_SHIFT)) & PMC_WKSRC_CMP_WAKEUP_MASK);
    obj->WKSRC   = tmp;
}

/*! \brief Gets the LPTMR wake up source flag
 *
 * This function gets the current LPTMR wake up source flag.
 *
 * \param[in] obj : pointer to PMC register instance
 * \return LPTMR wake up source flag
 *         - 0b : Wake up source not asserted
 *         - 1b : Wake up source asserted
 */
__attribute__((always_inline)) static inline uint8_t PmcReg_GetWkSrcLptmrWakeup(const PmcRegType *obj)
{
    return ((obj->WKSRC & PMC_WKSRC_LPTMR_WAKEUP_MASK) >> PMC_WKSRC_LPTMR_WAKEUP_SHIFT);
}

/*! \brief Sets the LPTMR wake up source flag
 *
 * This function sets the LPTMR wake up source flag.
 *
 * \param[in] obj : pointer to PMC register instance
 * \param[in] value : the value of LPTMR wake up source flag
 *                    - 0b : Wake up source not asserted
 *                    - 1b : Wake up source asserted
 */
__attribute__((always_inline)) static inline void PmcReg_SetWkSrcLptmrWakeup(PmcRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << PMC_WKSRC_LPTMR_WAKEUP_SHIFT)) & PMC_WKSRC_LPTMR_WAKEUP_MASK);
    obj->WKSRC   = tmp;
}

/*! \brief Gets the LPIT wake up source flag
 *
 * This function gets the current LPIT wake up source flag.
 *
 * \param[in] obj : pointer to PMC register instance
 * \return LPIT wake up source flag
 *         - 0b : Wake up source not asserted
 *         - 1b : Wake up source asserted
 */
__attribute__((always_inline)) static inline uint8_t PmcReg_GetWkSrcLpitWakeup(const PmcRegType *obj)
{
    return ((obj->WKSRC & PMC_WKSRC_LPIT_WAKEUP_MASK) >> PMC_WKSRC_LPIT_WAKEUP_SHIFT);
}

/*! \brief Sets the LPIT wake up source flag
 *
 * This function sets the LPIT wake up source flag.
 *
 * \param[in] obj : pointer to PMC register instance
 * \param[in] value : the value of LPIT wake up source flag
 *                    - 0b : Wake up source not asserted
 *                    - 1b : Wake up source asserted
 */
__attribute__((always_inline)) static inline void PmcReg_SetWkSrcLpitWakeup(PmcRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << PMC_WKSRC_LPIT_WAKEUP_SHIFT)) & PMC_WKSRC_LPIT_WAKEUP_MASK);
    obj->WKSRC   = tmp;
}

/*! \brief Gets the RTC wake up source flag
 *
 * This function gets the current RTC wake up source flag.
 *
 * \param[in] obj : pointer to PMC register instance
 * \return RTC wake up source flag
 *         - 0b : Wake up source not asserted
 *         - 1b : Wake up source asserted
 */
__attribute__((always_inline)) static inline uint8_t PmcReg_GetWkSrcRtcWakeup(const PmcRegType *obj)
{
    return ((obj->WKSRC & PMC_WKSRC_RTC_WAKEUP_MASK) >> PMC_WKSRC_RTC_WAKEUP_SHIFT);
}

/*! \brief Sets the RTC wake up source flag
 *
 * This function sets the RTC wake up source flag.
 *
 * \param[in] obj : pointer to PMC register instance
 * \param[in] value : the value of RTC wake up source flag
 *                    - 0b : Wake up source not asserted
 *                    - 1b : Wake up source asserted
 */
__attribute__((always_inline)) static inline void PmcReg_SetWkSrcRtcWakeup(PmcRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << PMC_WKSRC_RTC_WAKEUP_SHIFT)) & PMC_WKSRC_RTC_WAKEUP_MASK);
    obj->WKSRC   = tmp;
}

/*! \brief Gets the RESET wake up source flag
 *
 * This function gets the current RESET wake up source flag.
 *
 * \param[in] obj : pointer to PMC register instance
 * \return RESET wake up source flag
 *         - 0b : Wake up source not asserted
 *         - 1b : Wake up source asserted
 */
__attribute__((always_inline)) static inline uint8_t PmcReg_GetWkSrcResetWakeup(const PmcRegType *obj)
{
    return ((obj->WKSRC & PMC_WKSRC_RESET_WAKEUP_MASK) >> PMC_WKSRC_RESET_WAKEUP_SHIFT);
}

/*! \brief Sets the RESET wake up source flag
 *
 * This function sets the RESET wake up source flag.
 *
 * \param[in] obj : pointer to PMC register instance
 * \param[in] value : the value of RESET wake up source flag
 *                    - 0b : Wake up source not asserted
 *                    - 1b : Wake up source asserted
 */
__attribute__((always_inline)) static inline void PmcReg_SetWkSrcResetWakeup(PmcRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << PMC_WKSRC_RESET_WAKEUP_SHIFT)) & PMC_WKSRC_RESET_WAKEUP_MASK);
    obj->WKSRC   = tmp;
}

/*! \brief Gets the PORTE wake up source flag
 *
 * This function gets the current PORTE wake up source flag.
 *
 * \param[in] obj : pointer to PMC register instance
 * \return PORTE wake up source flag
 *         - 0b : Wake up source not asserted
 *         - 1b : Wake up source asserted
 */
__attribute__((always_inline)) static inline uint8_t PmcReg_GetWkSrcPortEWakeup(const PmcRegType *obj)
{
    return ((obj->WKSRC & PMC_WKSRC_PORTE_WAKEUP_MASK) >> PMC_WKSRC_PORTE_WAKEUP_SHIFT);
}

/*! \brief Sets the PORTE wake up source flag
 *
 * This function sets the PORTE wake up source flag.
 *
 * \param[in] obj : pointer to PMC register instance
 * \param[in] value : the value of PORTE wake up source flag
 *                    - 0b : Wake up source not asserted
 *                    - 1b : Wake up source asserted
 */
__attribute__((always_inline)) static inline void PmcReg_SetWkSrcPortEWakeup(PmcRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << PMC_WKSRC_PORTE_WAKEUP_SHIFT)) & PMC_WKSRC_PORTE_WAKEUP_MASK);
    obj->WKSRC   = tmp;
}

/*! \brief Gets the PORTD wake up source flag
 *
 * This function gets the current PORTD wake up source flag.
 *
 * \param[in] obj : pointer to PMC register instance
 * \return PORTD wake up source flag
 *         - 0b : Wake up source not asserted
 *         - 1b : Wake up source asserted
 */
__attribute__((always_inline)) static inline uint8_t PmcReg_GetWkSrcPortDWakeup(const PmcRegType *obj)
{
    return ((obj->WKSRC & PMC_WKSRC_PORTD_WAKEUP_MASK) >> PMC_WKSRC_PORTD_WAKEUP_SHIFT);
}

/*! \brief Sets the PORTD wake up source flag
 *
 * This function sets the PORTD wake up source flag.
 *
 * \param[in] obj : pointer to PMC register instance
 * \param[in] value : the value of PORTD wake up source flag
 *                    - 0b : Wake up source not asserted
 *                    - 1b : Wake up source asserted
 */
__attribute__((always_inline)) static inline void PmcReg_SetWkSrcPortDWakeup(PmcRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << PMC_WKSRC_PORTD_WAKEUP_SHIFT)) & PMC_WKSRC_PORTD_WAKEUP_MASK);
    obj->WKSRC   = tmp;
}

/*! \brief Gets the PORTC wake up source flag
 *
 * This function gets the current PORTC wake up source flag.
 *
 * \param[in] obj : pointer to PMC register instance
 * \return PORTC wake up source flag
 *         - 0b : Wake up source not asserted
 *         - 1b : Wake up source asserted
 */
__attribute__((always_inline)) static inline uint8_t PmcReg_GetWkSrcPortCWakeup(const PmcRegType *obj)
{
    return ((obj->WKSRC & PMC_WKSRC_PORTC_WAKEUP_MASK) >> PMC_WKSRC_PORTC_WAKEUP_SHIFT);
}

/*! \brief Sets the PORTC wake up source flag
 *
 * This function sets the PORTC wake up source flag.
 *
 * \param[in] obj : pointer to PMC register instance
 * \param[in] value : the value of PORTC wake up source flag
 *                    - 0b : Wake up source not asserted
 *                    - 1b : Wake up source asserted
 */
__attribute__((always_inline)) static inline void PmcReg_SetWkSrcPortCWakeup(PmcRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << PMC_WKSRC_PORTC_WAKEUP_SHIFT)) & PMC_WKSRC_PORTC_WAKEUP_MASK);
    obj->WKSRC   = tmp;
}

/*! \brief Gets the PORTB wake up source flag
 *
 * This function gets the current PORTB wake up source flag.
 *
 * \param[in] obj : pointer to PMC register instance
 * \return PORTB wake up source flag
 *         - 0b : Wake up source not asserted
 *         - 1b : Wake up source asserted
 */
__attribute__((always_inline)) static inline uint8_t PmcReg_GetWkSrcPortBWakeup(const PmcRegType *obj)
{
    return ((obj->WKSRC & PMC_WKSRC_PORTB_WAKEUP_MASK) >> PMC_WKSRC_PORTB_WAKEUP_SHIFT);
}

/*! \brief Sets the PORTB wake up source flag
 *
 * This function sets the PORTB wake up source flag.
 *
 * \param[in] obj : pointer to PMC register instance
 * \param[in] value : the value of PORTB wake up source flag
 *                    - 0b : Wake up source not asserted
 *                    - 1b : Wake up source asserted
 */
__attribute__((always_inline)) static inline void PmcReg_SetWkSrcPortBWakeup(PmcRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << PMC_WKSRC_PORTB_WAKEUP_SHIFT)) & PMC_WKSRC_PORTB_WAKEUP_MASK);
    obj->WKSRC   = tmp;
}

/*! \brief Gets the PORTA wake up source flag
 *
 * This function gets the current PORTA wake up source flag.
 *
 * \param[in] obj : pointer to PMC register instance
 * \return PORTA wake up source flag
 *         - 0b : Wake up source not asserted
 *         - 1b : Wake up source asserted
 */
__attribute__((always_inline)) static inline uint8_t PmcReg_GetWkSrcPortAWakeup(const PmcRegType *obj)
{
    return ((obj->WKSRC & PMC_WKSRC_PORTA_WAKEUP_MASK) >> PMC_WKSRC_PORTA_WAKEUP_SHIFT);
}

/*! \brief Sets the PORTA wake up source flag
 *
 * This function sets the PORTA wake up source flag.
 *
 * \param[in] obj : pointer to PMC register instance
 * \param[in] value : the value of PORTA wake up source flag
 *                    - 0b : Wake up source not asserted
 *                    - 1b : Wake up source asserted
 */
__attribute__((always_inline)) static inline void PmcReg_SetWkSrcPortAWakeup(PmcRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << PMC_WKSRC_PORTA_WAKEUP_SHIFT)) & PMC_WKSRC_PORTA_WAKEUP_MASK);
    obj->WKSRC   = tmp;
}

/*! \brief Gets the PAD keep enable
 *
 * This function gets the current PAD keep enable.
 * This bit can be set by hardware only. When this bit is set, SHUT domain PAD remains at the state at when it goes into STANDBY mode. Writing 1 to this bit clears it, and PAD can toggle with SHUT domain modules.
 *
 * \param[in] obj : pointer to PMC register instance
 * \return PAD keep enable
 *         - 0b : PAD keep is not enabled
 *         - 1b : PAD keep is enabled
 */
__attribute__((always_inline)) static inline uint8_t PmcReg_GetPkpPadKeep(const PmcRegType *obj)
{
    return ((obj->PKP & PMC_PKP_PAD_KEEP_MASK) >> PMC_PKP_PAD_KEEP_SHIFT);
}

/*! \brief Sets the PAD keep enable
 *
 * This function sets the PAD keep enable.
 * This bit can be set by hardware only. When this bit is set, SHUT domain PAD remains at the state at when it goes into STANDBY mode. Writing 1 to this bit clears it, and PAD can toggle with SHUT domain modules.
 *
 * \param[in] obj : pointer to PMC register instance
 * \param[in] value : the value of PAD keep enable
 *                    - 0b : PAD keep is not enabled
 *                    - 1b : PAD keep is enabled
 */
__attribute__((always_inline)) static inline void PmcReg_SetPkpPadKeep(PmcRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << PMC_PKP_PAD_KEEP_SHIFT)) & PMC_PKP_PAD_KEEP_MASK);
    obj->PKP     = tmp;
}

/*! \brief Gets the Over temperature protection flag signal
 *
 * This function gets the current Over temperature protection flag signal.
 *
 * \param[in] obj : pointer to PMC register instance
 * \return Over temperature protection flag signal
 *         - 0b : Temperature low than 160 degree(Normal work state)
 *         - 1b : Temperature over 160 degree(OTP event happen)
 */
__attribute__((always_inline)) static inline uint8_t PmcReg_GetAnaCtrlAdHpbgOtp(const PmcRegType *obj)
{
    return ((obj->ANACTRL & PMC_ANACTRL_AD_HPBG_OTP_MASK) >> PMC_ANACTRL_AD_HPBG_OTP_SHIFT);
}

/*! \brief Gets the FLDO Low Voltage Detect State
 *
 * This function gets the current FLDO Low Voltage Detect State.
 *
 * \param[in] obj : pointer to PMC register instance
 * \return FLDO Low Voltage Detect State
 *         - 0b : normal state
 *         - 1b : low voltage detect state
 */
__attribute__((always_inline)) static inline uint8_t PmcReg_GetAnaCtrlAdPmcFldoLvd(const PmcRegType *obj)
{
    return ((obj->ANACTRL & PMC_ANACTRL_AD_PMC_FLDO_LVD_MASK) >> PMC_ANACTRL_AD_PMC_FLDO_LVD_SHIFT);
}

/*! \brief Gets the Over Voltage Detect for DVDD11 State
 *
 * This function gets the current Over Voltage Detect for DVDD11 State.
 *
 * \param[in] obj : pointer to PMC register instance
 * \return Over Voltage Detect for DVDD11 State
 *         - 0b : normal state
 *         - 1b : over voltage detect state
 */
__attribute__((always_inline)) static inline uint8_t PmcReg_GetAnaCtrlAdPmcOvd11(const PmcRegType *obj)
{
    return ((obj->ANACTRL & PMC_ANACTRL_AD_PMC_OVD11_MASK) >> PMC_ANACTRL_AD_PMC_OVD11_SHIFT);
}

/*! \brief Gets the Over Voltage Detect State
 *
 * This function gets the current Over Voltage Detect State.
 *
 * \param[in] obj : pointer to PMC register instance
 * \return Over Voltage Detect State
 *         - 0b : normal state
 *         - 1b : over voltage detect state
 */
__attribute__((always_inline)) static inline uint8_t PmcReg_GetAnaCtrlAdPmcOvd(const PmcRegType *obj)
{
    return ((obj->ANACTRL & PMC_ANACTRL_AD_PMC_OVD_MASK) >> PMC_ANACTRL_AD_PMC_OVD_SHIFT);
}

/*! \brief Gets the Low Voltage Detect State
 *
 * This function gets the current Low Voltage Detect State.
 *
 * \param[in] obj : pointer to PMC register instance
 * \return Low Voltage Detect State
 *         - 0b : normal state
 *         - 1b : low voltage detect state
 */
__attribute__((always_inline)) static inline uint8_t PmcReg_GetAnaCtrlAdPmcLvd(const PmcRegType *obj)
{
    return ((obj->ANACTRL & PMC_ANACTRL_AD_PMC_LVD_MASK) >> PMC_ANACTRL_AD_PMC_LVD_SHIFT);
}

/*! \brief Gets the Low Voltage Warning State
 *
 * This function gets the current Low Voltage Warning State.
 *
 * \param[in] obj : pointer to PMC register instance
 * \return Low Voltage Warning State
 *         - 0b : normal state
 *         - 1b : low voltage warning state
 */
__attribute__((always_inline)) static inline uint8_t PmcReg_GetAnaCtrlAdPmcLvw(const PmcRegType *obj)
{
    return ((obj->ANACTRL & PMC_ANACTRL_AD_PMC_LVW_MASK) >> PMC_ANACTRL_AD_PMC_LVW_SHIFT);
}

/*! \brief Gets the OTP function enable control
 *
 * This function gets the current OTP function enable control.
 *
 * \param[in] obj : pointer to PMC register instance
 * \return OTP function enable control
 *         - 0b : Disable
 *         - 1b : Enable;
 */
__attribute__((always_inline)) static inline uint8_t PmcReg_GetAnaCtrlDaHpbgOtpEn(const PmcRegType *obj)
{
    return ((obj->ANACTRL & PMC_ANACTRL_DA_HPBG_OTP_EN_MASK) >> PMC_ANACTRL_DA_HPBG_OTP_EN_SHIFT);
}

/*! \brief Sets the OTP function enable control
 *
 * This function sets the OTP function enable control.
 *
 * \param[in] obj : pointer to PMC register instance
 * \param[in] value : the value of OTP function enable control
 *                    - 0b : Disable
 *                    - 1b : Enable;
 */
__attribute__((always_inline)) static inline void PmcReg_SetAnaCtrlDaHpbgOtpEn(PmcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->ANACTRL;

    tmp &= ~PMC_ANACTRL_DA_HPBG_OTP_EN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PMC_ANACTRL_DA_HPBG_OTP_EN_SHIFT)) & PMC_ANACTRL_DA_HPBG_OTP_EN_MASK);
    obj->ANACTRL = tmp;
}

/*! \brief Gets the Low voltage warning(LVW) level select
 *
 * This function gets the current Low voltage warning(LVW) level select.
 *
 * \param[in] obj : pointer to PMC register instance
 * \return Low voltage warning(LVW) level select
 *         - 00b : V_LVW1
 *         - 01b : V_LVW2
 *         - 01b : V_LVW3
 *         - 11b : Not defined
 */
__attribute__((always_inline)) static inline uint8_t PmcReg_GetAnaCtrlDaPmcSelLvw(const PmcRegType *obj)
{
    return ((obj->ANACTRL & PMC_ANACTRL_DA_PMC_SEL_LVW_MASK) >> PMC_ANACTRL_DA_PMC_SEL_LVW_SHIFT);
}

/*! \brief Sets the Low voltage warning(LVW) level select
 *
 * This function sets the Low voltage warning(LVW) level select.
 *
 * \param[in] obj : pointer to PMC register instance
 * \param[in] value : the value of Low voltage warning(LVW) level select
 *                    - 00b : V_LVW1
 *                    - 01b : V_LVW2
 *                    - 01b : V_LVW3
 *                    - 11b : Not defined
 */
__attribute__((always_inline)) static inline void PmcReg_SetAnaCtrlDaPmcSelLvw(PmcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->ANACTRL;

    tmp &= ~PMC_ANACTRL_DA_PMC_SEL_LVW_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PMC_ANACTRL_DA_PMC_SEL_LVW_SHIFT)) & PMC_ANACTRL_DA_PMC_SEL_LVW_MASK);
    obj->ANACTRL = tmp;
}

/*! \brief Gets the Low voltage detect(LVD) for FLDO control
 *
 * This function gets the current Low voltage detect(LVD) for FLDO control.
 *
 * \param[in] obj : pointer to PMC register instance
 * \return Low voltage detect(LVD) for FLDO control
 *         - 0b : Disable low voltage detect function
 *         - 1b : Enable low voltage detect function
 */
__attribute__((always_inline)) static inline uint8_t PmcReg_GetAnaCtrlDaPmcEnFldoVdet(const PmcRegType *obj)
{
    return ((obj->ANACTRL & PMC_ANACTRL_DA_PMC_EN_FLDO_VDET_MASK) >> PMC_ANACTRL_DA_PMC_EN_FLDO_VDET_SHIFT);
}

/*! \brief Sets the Low voltage detect(LVD) for FLDO control
 *
 * This function sets the Low voltage detect(LVD) for FLDO control.
 *
 * \param[in] obj : pointer to PMC register instance
 * \param[in] value : the value of Low voltage detect(LVD) for FLDO control
 *                    - 0b : Disable low voltage detect function
 *                    - 1b : Enable low voltage detect function
 */
__attribute__((always_inline)) static inline void PmcReg_SetAnaCtrlDaPmcEnFldoVdet(PmcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->ANACTRL;

    tmp &= ~PMC_ANACTRL_DA_PMC_EN_FLDO_VDET_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PMC_ANACTRL_DA_PMC_EN_FLDO_VDET_SHIFT)) & PMC_ANACTRL_DA_PMC_EN_FLDO_VDET_MASK);
    obj->ANACTRL = tmp;
}

/*! \brief Gets the Over voltage Detect(OVD) for DVDD11 control
 *
 * This function gets the current Over voltage Detect(OVD) for DVDD11 control.
 *
 * \param[in] obj : pointer to PMC register instance
 * \return Over voltage Detect(OVD) for DVDD11 control
 *         - 0b : Disable over voltage detect function
 *         - 1b : Enable over voltage detect function
 */
__attribute__((always_inline)) static inline uint8_t PmcReg_GetAnaCtrlDaPmcEnOvd11(const PmcRegType *obj)
{
    return ((obj->ANACTRL & PMC_ANACTRL_DA_PMC_EN_OVD11_MASK) >> PMC_ANACTRL_DA_PMC_EN_OVD11_SHIFT);
}

/*! \brief Sets the Over voltage Detect(OVD) for DVDD11 control
 *
 * This function sets the Over voltage Detect(OVD) for DVDD11 control.
 *
 * \param[in] obj : pointer to PMC register instance
 * \param[in] value : the value of Over voltage Detect(OVD) for DVDD11 control
 *                    - 0b : Disable over voltage detect function
 *                    - 1b : Enable over voltage detect function
 */
__attribute__((always_inline)) static inline void PmcReg_SetAnaCtrlDaPmcEnOvd11(PmcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->ANACTRL;

    tmp &= ~PMC_ANACTRL_DA_PMC_EN_OVD11_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PMC_ANACTRL_DA_PMC_EN_OVD11_SHIFT)) & PMC_ANACTRL_DA_PMC_EN_OVD11_MASK);
    obj->ANACTRL = tmp;
}

/*! \brief Gets the Over voltage Detect(OVD) control
 *
 * This function gets the current Over voltage Detect(OVD) control.
 *
 * \param[in] obj : pointer to PMC register instance
 * \return Over voltage Detect(OVD) control
 *         - 0b : Disable over voltage detect function
 *         - 1b : Enable over voltage detect function
 */
__attribute__((always_inline)) static inline uint8_t PmcReg_GetAnaCtrlDaPmcEnOvd(const PmcRegType *obj)
{
    return ((obj->ANACTRL & PMC_ANACTRL_DA_PMC_EN_OVD_MASK) >> PMC_ANACTRL_DA_PMC_EN_OVD_SHIFT);
}

/*! \brief Sets the Over voltage Detect(OVD) control
 *
 * This function sets the Over voltage Detect(OVD) control.
 *
 * \param[in] obj : pointer to PMC register instance
 * \param[in] value : the value of Over voltage Detect(OVD) control
 *                    - 0b : Disable over voltage detect function
 *                    - 1b : Enable over voltage detect function
 */
__attribute__((always_inline)) static inline void PmcReg_SetAnaCtrlDaPmcEnOvd(PmcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->ANACTRL;

    tmp &= ~PMC_ANACTRL_DA_PMC_EN_OVD_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PMC_ANACTRL_DA_PMC_EN_OVD_SHIFT)) & PMC_ANACTRL_DA_PMC_EN_OVD_MASK);
    obj->ANACTRL = tmp;
}

/*! \brief Gets the Low voltage detect(LVD) control
 *
 * This function gets the current Low voltage detect(LVD) control.
 *
 * \param[in] obj : pointer to PMC register instance
 * \return Low voltage detect(LVD) control
 *         - 0b : Disable low voltage detect function
 *         - 1b : Enable low voltage detect function
 */
__attribute__((always_inline)) static inline uint8_t PmcReg_GetAnaCtrlDaPmcEnLvd(const PmcRegType *obj)
{
    return ((obj->ANACTRL & PMC_ANACTRL_DA_PMC_EN_LVD_MASK) >> PMC_ANACTRL_DA_PMC_EN_LVD_SHIFT);
}

/*! \brief Sets the Low voltage detect(LVD) control
 *
 * This function sets the Low voltage detect(LVD) control.
 *
 * \param[in] obj : pointer to PMC register instance
 * \param[in] value : the value of Low voltage detect(LVD) control
 *                    - 0b : Disable low voltage detect function
 *                    - 1b : Enable low voltage detect function
 */
__attribute__((always_inline)) static inline void PmcReg_SetAnaCtrlDaPmcEnLvd(PmcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->ANACTRL;

    tmp &= ~PMC_ANACTRL_DA_PMC_EN_LVD_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PMC_ANACTRL_DA_PMC_EN_LVD_SHIFT)) & PMC_ANACTRL_DA_PMC_EN_LVD_MASK);
    obj->ANACTRL = tmp;
}

/*! \brief Gets the Low voltage warning(LVW) control
 *
 * This function gets the current Low voltage warning(LVW) control.
 *
 * \param[in] obj : pointer to PMC register instance
 * \return Low voltage warning(LVW) control
 *         - 0b : Disable low voltage warning function
 *         - 1b : Enable low voltage warning function
 */
__attribute__((always_inline)) static inline uint8_t PmcReg_GetAnaCtrlDaPmcEnLvw(const PmcRegType *obj)
{
    return ((obj->ANACTRL & PMC_ANACTRL_DA_PMC_EN_LVW_MASK) >> PMC_ANACTRL_DA_PMC_EN_LVW_SHIFT);
}

/*! \brief Sets the Low voltage warning(LVW) control
 *
 * This function sets the Low voltage warning(LVW) control.
 *
 * \param[in] obj : pointer to PMC register instance
 * \param[in] value : the value of Low voltage warning(LVW) control
 *                    - 0b : Disable low voltage warning function
 *                    - 1b : Enable low voltage warning function
 */
__attribute__((always_inline)) static inline void PmcReg_SetAnaCtrlDaPmcEnLvw(PmcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->ANACTRL;

    tmp &= ~PMC_ANACTRL_DA_PMC_EN_LVW_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PMC_ANACTRL_DA_PMC_EN_LVW_SHIFT)) & PMC_ANACTRL_DA_PMC_EN_LVW_MASK);
    obj->ANACTRL = tmp;
}

/*! \brief Gets the LPBG Low voltage detection(LVD) state
 *
 * This function gets the current LPBG Low voltage detection(LVD) state.
 *
 * \param[in] obj : pointer to PMC register instance
 * \return LPBG Low voltage detection(LVD) state
 *         - 0b : normal state
 *         - 1b : low voltage detect state
 */
__attribute__((always_inline)) static inline uint8_t PmcReg_GetUidetAdPmcLpbgLvd(const PmcRegType *obj)
{
    return ((obj->UIDET & PMC_UIDET_AD_PMC_LPBG_LVD_MASK) >> PMC_UIDET_AD_PMC_LPBG_LVD_SHIFT);
}

/*! \brief Gets the LPBG Over voltage detection(OVD) state
 *
 * This function gets the current LPBG Over voltage detection(OVD) state.
 *
 * \param[in] obj : pointer to PMC register instance
 * \return LPBG Over voltage detection(OVD) state
 *         - 0b : normal state
 *         - 1b : over voltage detect state
 */
__attribute__((always_inline)) static inline uint8_t PmcReg_GetUidetAdPmcLpbgOvd(const PmcRegType *obj)
{
    return ((obj->UIDET & PMC_UIDET_AD_PMC_LPBG_OVD_MASK) >> PMC_UIDET_AD_PMC_LPBG_OVD_SHIFT);
}

/*! \brief Gets the LPBG Over voltage detection(OVD) control
 *
 * This function gets the current LPBG Over voltage detection(OVD) control.
 *
 * \param[in] obj : pointer to PMC register instance
 * \return LPBG Over voltage detection(OVD) control
 *         - 0b : Disable LPGB over voltage detection function
 *         - 1b : Enable LPBG over voltage detction function
 */
__attribute__((always_inline)) static inline uint8_t PmcReg_GetUidetDaPmcEnLpbgOvd(const PmcRegType *obj)
{
    return ((obj->UIDET & PMC_UIDET_DA_PMC_EN_LPBG_OVD_MASK) >> PMC_UIDET_DA_PMC_EN_LPBG_OVD_SHIFT);
}

/*! \brief Sets the LPBG over voltage detection(OVD) control
 *
 * This function sets the LPBG over voltage detection(OVD) control.
 *
 * \param[in] obj : pointer to PMC register instance
 * \param[in] value : the value of LPBG over voltage detection(OVD) control
 *                    - 0b : Disable LPBG over voltage detection function
 *                    - 1b : Enable LPBG over voltage detection function
 */
__attribute__((always_inline)) static inline void PmcReg_SetUidetDaPmcEnLpbgOvd(PmcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->UIDET;

    tmp &= ~PMC_UIDET_DA_PMC_EN_LPBG_OVD_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PMC_UIDET_DA_PMC_EN_LPBG_OVD_SHIFT)) & PMC_UIDET_DA_PMC_EN_LPBG_OVD_MASK);
    obj->UIDET = tmp;
}

/*! \brief Gets the LPBG Low voltage detection(LVD) control
 *
 * This function gets the current LPBG Low voltage detection(LVD) control.
 *
 * \param[in] obj : pointer to PMC register instance
 * \return LPBG Low voltage detection(LVD) control
 *         - 0b : Disable LPGB low voltage detection function
 *         - 1b : Enable LPBG low voltage detction function
 */
__attribute__((always_inline)) static inline uint8_t PmcReg_GetUidetDaPmcEnLpbgLvd(const PmcRegType *obj)
{
    return ((obj->UIDET & PMC_UIDET_DA_PMC_EN_LPBG_LVD_MASK) >> PMC_UIDET_DA_PMC_EN_LPBG_LVD_SHIFT);
}

/*! \brief Sets the LPBG Low voltage detection(LVD) control
 *
 * This function sets the LPBG Low voltage detection(LVD) control.
 *
 * \param[in] obj : pointer to PMC register instance
 * \param[in] value : the value of LPBG Low voltage detection(LVD) control
 *                    - 0b : Disable LPBG low voltage detection function
 *                    - 1b : Enable LPBG low voltage detection function
 */
__attribute__((always_inline)) static inline void PmcReg_SetUidetDaPmcEnLpbgLvd(PmcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->UIDET;

    tmp &= ~PMC_UIDET_DA_PMC_EN_LPBG_LVD_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PMC_UIDET_DA_PMC_EN_LPBG_LVD_SHIFT)) & PMC_UIDET_DA_PMC_EN_LPBG_LVD_MASK);
    obj->UIDET = tmp;
}

/*! \brief Gets the PMC Key Value
 *
 * This function gets the current PMC Key Value.
 * In order to config RWP registers, writing  0x1015_FF11 to KEY_VAL to unlock key. When key is locked, RWP registers are read only.
 *
 * \param[in] obj : pointer to PMC register instance
 * \return PMC Key Value
 *         - 0x1015_FF11 : key is unlocked
 *         - others : key is locked
 */
__attribute__((always_inline)) static inline uint32_t PmcReg_GetKeyVal(const PmcRegType *obj)
{
    return ((obj->KEY & PMC_KEY_KEY_VAL_MASK) >> PMC_KEY_KEY_VAL_SHIFT);
}

/*! \brief Sets the PMC Key Value
 *
 * This function sets the PMC Key Value.
 * In order to config RWP registers, writing  0x1015_FF11 to KEY_VAL to unlock key. When key is locked, RWP registers are read only.
 *
 * \param[in] obj : pointer to PMC register instance
 * \param[in] value : the value of PMC Key Value
 *                    - 0x1015_FF11 : key is unlocked
 *                    - others : key is locked
 */
__attribute__((always_inline)) static inline void PmcReg_SetKeyVal(PmcRegType *obj, uint32_t value)
{
    uint32_t tmp = 0;

    tmp &= ~PMC_KEY_KEY_VAL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PMC_KEY_KEY_VAL_SHIFT)) & PMC_KEY_KEY_VAL_MASK);
    obj->KEY = tmp;
}

/*! \brief Gets the PMC Public Register Unlock
 *
 * This function gets the current PMC Public Register Unlock.
 * For all registers that has write protection, UNLOCK must be 1 to grant write access. When UNLOCK is 0, write access is ignored, and read access executes normally.
Write to KEY to change UNLOCK bit.
 *
 * \param[in] obj : pointer to PMC register instance
 * \return PMC Public Register Unlock
 *         - 0b : write protected registers are locked
 *         - 1b : write protected registers are unlocked
 */
__attribute__((always_inline)) static inline uint8_t PmcReg_GetUnlock(const PmcRegType *obj)
{
    return ((obj->UNLOCK & PMC_UNLOCK_UNLOCK_MASK) >> PMC_UNLOCK_UNLOCK_SHIFT);
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _PMC_REG_H_ */
