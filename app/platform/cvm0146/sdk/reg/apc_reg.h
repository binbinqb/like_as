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

#ifndef _APC_REG_H_
#define _APC_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the APC Registers
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

/* CLK_CFG Bit Fields */
#define APC_CLK_CFG_SRC_PORTE_FLT_MASK  (0x10000000u)
#define APC_CLK_CFG_SRC_PORTE_FLT_SHIFT (28u)
#define APC_CLK_CFG_SRC_PORTE_FLT_WIDTH (1u)
#define APC_CLK_CFG_SRC_PORTD_FLT_MASK  (0x8000000u)
#define APC_CLK_CFG_SRC_PORTD_FLT_SHIFT (27u)
#define APC_CLK_CFG_SRC_PORTD_FLT_WIDTH (1u)
#define APC_CLK_CFG_SRC_PORTC_FLT_MASK  (0x4000000u)
#define APC_CLK_CFG_SRC_PORTC_FLT_SHIFT (26u)
#define APC_CLK_CFG_SRC_PORTC_FLT_WIDTH (1u)
#define APC_CLK_CFG_SRC_PORTB_FLT_MASK  (0x2000000u)
#define APC_CLK_CFG_SRC_PORTB_FLT_SHIFT (25u)
#define APC_CLK_CFG_SRC_PORTB_FLT_WIDTH (1u)
#define APC_CLK_CFG_SRC_PORTA_FLT_MASK  (0x1000000u)
#define APC_CLK_CFG_SRC_PORTA_FLT_SHIFT (24u)
#define APC_CLK_CFG_SRC_PORTA_FLT_WIDTH (1u)
#define APC_CLK_CFG_SRC_CMP0_MASK       (0x800000u)
#define APC_CLK_CFG_SRC_CMP0_SHIFT      (23u)
#define APC_CLK_CFG_SRC_CMP0_WIDTH      (1u)
#define APC_CLK_CFG_DIV_LPTMR_MASK      (0x700000u)
#define APC_CLK_CFG_DIV_LPTMR_SHIFT     (20u)
#define APC_CLK_CFG_DIV_LPTMR_WIDTH     (3u)
#define APC_CLK_CFG_SRC_LPTMR_MASK      (0x70000u)
#define APC_CLK_CFG_SRC_LPTMR_SHIFT     (16u)
#define APC_CLK_CFG_SRC_LPTMR_WIDTH     (3u)
#define APC_CLK_CFG_SRC_LPIT_MASK       (0xE000u)
#define APC_CLK_CFG_SRC_LPIT_SHIFT      (13u)
#define APC_CLK_CFG_SRC_LPIT_WIDTH      (3u)
#define APC_CLK_CFG_SRC_EXT_FLT_MASK    (0x1000u)
#define APC_CLK_CFG_SRC_EXT_FLT_SHIFT   (12u)
#define APC_CLK_CFG_SRC_EXT_FLT_WIDTH   (1u)
#define APC_CLK_CFG_SRC_RTC_CNT_MASK    (0x20u)
#define APC_CLK_CFG_SRC_RTC_CNT_SHIFT   (5u)
#define APC_CLK_CFG_SRC_RTC_CNT_WIDTH   (1u)
#define APC_CLK_CFG_SRC_RTC_SRC_MASK    (0x10u)
#define APC_CLK_CFG_SRC_RTC_SRC_SHIFT   (4u)
#define APC_CLK_CFG_SRC_RTC_SRC_WIDTH   (1u)

/* CLK_EN Bit Fields */
#define APC_CLK_EN_PORTE_MASK           (0x1000u)
#define APC_CLK_EN_PORTE_SHIFT          (12u)
#define APC_CLK_EN_PORTE_WIDTH          (1u)
#define APC_CLK_EN_PORTD_MASK           (0x800u)
#define APC_CLK_EN_PORTD_SHIFT          (11u)
#define APC_CLK_EN_PORTD_WIDTH          (1u)
#define APC_CLK_EN_PORTC_MASK           (0x400u)
#define APC_CLK_EN_PORTC_SHIFT          (10u)
#define APC_CLK_EN_PORTC_WIDTH          (1u)
#define APC_CLK_EN_PORTB_MASK           (0x200u)
#define APC_CLK_EN_PORTB_SHIFT          (9u)
#define APC_CLK_EN_PORTB_WIDTH          (1u)
#define APC_CLK_EN_PORTA_MASK           (0x100u)
#define APC_CLK_EN_PORTA_SHIFT          (8u)
#define APC_CLK_EN_PORTA_WIDTH          (1u)
#define APC_CLK_EN_LPIT_MASK            (0x40u)
#define APC_CLK_EN_LPIT_SHIFT           (6u)
#define APC_CLK_EN_LPIT_WIDTH           (1u)
#define APC_CLK_EN_CMP0_MASK            (0x20u)
#define APC_CLK_EN_CMP0_SHIFT           (5u)
#define APC_CLK_EN_CMP0_WIDTH           (1u)
#define APC_CLK_EN_LPO32_MASK           (0x10u)
#define APC_CLK_EN_LPO32_SHIFT          (4u)
#define APC_CLK_EN_LPO32_WIDTH          (1u)
#define APC_CLK_EN_LPO1_MASK            (0x08u)
#define APC_CLK_EN_LPO1_SHIFT           (3u)
#define APC_CLK_EN_LPO1_WIDTH           (1u)
#define APC_CLK_EN_LPTMR_MASK           (0x04u)
#define APC_CLK_EN_LPTMR_SHIFT          (2u)
#define APC_CLK_EN_LPTMR_WIDTH          (1u)
#define APC_CLK_EN_RTC_SRC_MASK         (0x02u)
#define APC_CLK_EN_RTC_SRC_SHIFT        (1u)
#define APC_CLK_EN_RTC_SRC_WIDTH        (1u)
#define APC_CLK_EN_RTC_CNT_MASK         (0x01u)
#define APC_CLK_EN_RTC_CNT_SHIFT        (0u)
#define APC_CLK_EN_RTC_CNT_WIDTH        (1u)

/* SW_RST Bit Fields */
#define APC_SW_RST_PORTE_MASK           (0x1000u)
#define APC_SW_RST_PORTE_SHIFT          (12u)
#define APC_SW_RST_PORTE_WIDTH          (1u)
#define APC_SW_RST_PORTD_MASK           (0x800u)
#define APC_SW_RST_PORTD_SHIFT          (11u)
#define APC_SW_RST_PORTD_WIDTH          (1u)
#define APC_SW_RST_PORTC_MASK           (0x400u)
#define APC_SW_RST_PORTC_SHIFT          (10u)
#define APC_SW_RST_PORTC_WIDTH          (1u)
#define APC_SW_RST_PORTB_MASK           (0x200u)
#define APC_SW_RST_PORTB_SHIFT          (9u)
#define APC_SW_RST_PORTB_WIDTH          (1u)
#define APC_SW_RST_PORTA_MASK           (0x100u)
#define APC_SW_RST_PORTA_SHIFT          (8u)
#define APC_SW_RST_PORTA_WIDTH          (1u)
#define APC_SW_RST_LPIT_MASK            (0x40u)
#define APC_SW_RST_LPIT_SHIFT           (6u)
#define APC_SW_RST_LPIT_WIDTH           (1u)
#define APC_SW_RST_CMP0_MASK            (0x20u)
#define APC_SW_RST_CMP0_SHIFT           (5u)
#define APC_SW_RST_CMP0_WIDTH           (1u)
#define APC_SW_RST_LPTMR_MASK           (0x04u)
#define APC_SW_RST_LPTMR_SHIFT          (2u)
#define APC_SW_RST_LPTMR_WIDTH          (1u)
#define APC_SW_RST_WDG_MASK             (0x02u)
#define APC_SW_RST_WDG_SHIFT            (1u)
#define APC_SW_RST_WDG_WIDTH            (1u)

/* RST_ST Bit Fields */
#define APC_RST_ST_PORTE_MASK           (0x1000u)
#define APC_RST_ST_PORTE_SHIFT          (12u)
#define APC_RST_ST_PORTE_WIDTH          (1u)
#define APC_RST_ST_PORTD_MASK           (0x800u)
#define APC_RST_ST_PORTD_SHIFT          (11u)
#define APC_RST_ST_PORTD_WIDTH          (1u)
#define APC_RST_ST_PORTC_MASK           (0x400u)
#define APC_RST_ST_PORTC_SHIFT          (10u)
#define APC_RST_ST_PORTC_WIDTH          (1u)
#define APC_RST_ST_PORTB_MASK           (0x200u)
#define APC_RST_ST_PORTB_SHIFT          (9u)
#define APC_RST_ST_PORTB_WIDTH          (1u)
#define APC_RST_ST_PORTA_MASK           (0x100u)
#define APC_RST_ST_PORTA_SHIFT          (8u)
#define APC_RST_ST_PORTA_WIDTH          (1u)
#define APC_RST_ST_LPIT_MASK            (0x40u)
#define APC_RST_ST_LPIT_SHIFT           (6u)
#define APC_RST_ST_LPIT_WIDTH           (1u)
#define APC_RST_ST_CMP0_MASK            (0x20u)
#define APC_RST_ST_CMP0_SHIFT           (5u)
#define APC_RST_ST_CMP0_WIDTH           (1u)
#define APC_RST_ST_LPTMR_MASK           (0x04u)
#define APC_RST_ST_LPTMR_SHIFT          (2u)
#define APC_RST_ST_LPTMR_WIDTH          (1u)
#define APC_RST_ST_WDG_MASK             (0x02u)
#define APC_RST_ST_WDG_SHIFT            (1u)
#define APC_RST_ST_WDG_WIDTH            (1u)
#define APC_RST_ST_RTC_MASK             (0x01u)
#define APC_RST_ST_RTC_SHIFT            (0u)
#define APC_RST_ST_RTC_WIDTH            (1u)

/* LOCK Bit Fields */
#define APC_LOCK_KEY_MASK               (0xFFFFFFFFu)
#define APC_LOCK_KEY_SHIFT              (0u)
#define APC_LOCK_KEY_WIDTH              (32u)

/* LOCK_ST Bit Fields */
#define APC_LOCK_ST_LOCK_MASK           (0x01u)
#define APC_LOCK_ST_LOCK_SHIFT          (0u)
#define APC_LOCK_ST_LOCK_WIDTH          (1u)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief The definition of APC registers
 */
typedef struct _ApcRegType_
{
    volatile uint32_t       CLK_CFG;       /*!< Clock control register, offset: 0x00 */
    volatile uint32_t       CLK_EN;        /*!< Perpherial module clock enable register, offset: 0x04 */
    volatile uint32_t       SW_RST;        /*!< Perpherial module software reset register, offset: 0x08 */
    const volatile uint32_t RST_ST;        /*!< Perpherial module reset status register, offset: 0x0C */
    uint32_t                RESERVED0[12]; /*!< Reserverd block, offset: 0x10 */
    volatile uint32_t       LOCK;          /*!< APC module unlock/lock control, offset: 0x40 */
    const volatile uint32_t LOCK_ST;       /*!< APC module lock status register, offset: 0x44 */
} ApcRegType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Gets the PORTE digital filter clock source
 *
 * This function gets the current PORTE digital filter clock source.
 * Changing the filter clock source must be done only when all digital filters are disabled.
 *
 * \param[in] obj : pointer to APC register instance
 * \return PORTE digital filter clock source
 *         - 0b : clk_apb
 *         - 1b : clk_lpo128
 */
__attribute__((always_inline)) static inline uint8_t ApcReg_GetClkCfgSrcPortEFlt(const ApcRegType *obj)
{
    return ((obj->CLK_CFG & APC_CLK_CFG_SRC_PORTE_FLT_MASK) >> APC_CLK_CFG_SRC_PORTE_FLT_SHIFT);
}

/*! \brief Sets the PORTE digital filter clock source
 *
 * This function sets the PORTE digital filter clock source.
 * Changing the filter clock source must be done only when all digital filters are disabled.
 *
 * \param[in] obj : pointer to APC register instance
 * \param[in] value : the value of PORTE digital filter clock source
 *                    - 0b : clk_apb
 *                    - 1b : clk_lpo128
 */
__attribute__((always_inline)) static inline void ApcReg_SetClkCfgSrcPortEFlt(ApcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CLK_CFG;

    tmp &= ~APC_CLK_CFG_SRC_PORTE_FLT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << APC_CLK_CFG_SRC_PORTE_FLT_SHIFT)) & APC_CLK_CFG_SRC_PORTE_FLT_MASK);
    obj->CLK_CFG = tmp;
}

/*! \brief Gets the PORTD digital filter clock source
 *
 * This function gets the current PORTD digital filter clock source.
 * Changing the filter clock source must be done only when all digital filters are disabled.
 *
 * \param[in] obj : pointer to APC register instance
 * \return PORTD digital filter clock source
 *         - 0b : clk_apb
 *         - 1b : clk_lpo128
 */
__attribute__((always_inline)) static inline uint8_t ApcReg_GetClkCfgSrcPortDFlt(const ApcRegType *obj)
{
    return ((obj->CLK_CFG & APC_CLK_CFG_SRC_PORTD_FLT_MASK) >> APC_CLK_CFG_SRC_PORTD_FLT_SHIFT);
}

/*! \brief Sets the PORTD digital filter clock source
 *
 * This function sets the PORTD digital filter clock source.
 * Changing the filter clock source must be done only when all digital filters are disabled.
 *
 * \param[in] obj : pointer to APC register instance
 * \param[in] value : the value of PORTD digital filter clock source
 *                    - 0b : clk_apb
 *                    - 1b : clk_lpo128
 */
__attribute__((always_inline)) static inline void ApcReg_SetClkCfgSrcPortDFlt(ApcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CLK_CFG;

    tmp &= ~APC_CLK_CFG_SRC_PORTD_FLT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << APC_CLK_CFG_SRC_PORTD_FLT_SHIFT)) & APC_CLK_CFG_SRC_PORTD_FLT_MASK);
    obj->CLK_CFG = tmp;
}

/*! \brief Gets the PORTC digital filter clock source
 *
 * This function gets the current PORTC digital filter clock source.
 * Changing the filter clock source must be done only when all digital filters are disabled.
 *
 * \param[in] obj : pointer to APC register instance
 * \return PORTC digital filter clock source
 *         - 0b : clk_apb
 *         - 1b : clk_lpo128
 */
__attribute__((always_inline)) static inline uint8_t ApcReg_GetClkCfgSrcPortCFlt(const ApcRegType *obj)
{
    return ((obj->CLK_CFG & APC_CLK_CFG_SRC_PORTC_FLT_MASK) >> APC_CLK_CFG_SRC_PORTC_FLT_SHIFT);
}

/*! \brief Sets the PORTC digital filter clock source
 *
 * This function sets the PORTC digital filter clock source.
 * Changing the filter clock source must be done only when all digital filters are disabled.
 *
 * \param[in] obj : pointer to APC register instance
 * \param[in] value : the value of PORTC digital filter clock source
 *                    - 0b : clk_apb
 *                    - 1b : clk_lpo128
 */
__attribute__((always_inline)) static inline void ApcReg_SetClkCfgSrcPortCFlt(ApcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CLK_CFG;

    tmp &= ~APC_CLK_CFG_SRC_PORTC_FLT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << APC_CLK_CFG_SRC_PORTC_FLT_SHIFT)) & APC_CLK_CFG_SRC_PORTC_FLT_MASK);
    obj->CLK_CFG = tmp;
}

/*! \brief Gets the PORTB digital filter clock source
 *
 * This function gets the current PORTB digital filter clock source.
 * Changing the filter clock source must be done only when all digital filters are disabled.
 *
 * \param[in] obj : pointer to APC register instance
 * \return PORTB digital filter clock source
 *         - 0b : clk_apb
 *         - 1b : clk_lpo128
 */
__attribute__((always_inline)) static inline uint8_t ApcReg_GetClkCfgSrcPortBFlt(const ApcRegType *obj)
{
    return ((obj->CLK_CFG & APC_CLK_CFG_SRC_PORTB_FLT_MASK) >> APC_CLK_CFG_SRC_PORTB_FLT_SHIFT);
}

/*! \brief Sets the PORTB digital filter clock source
 *
 * This function sets the PORTB digital filter clock source.
 * Changing the filter clock source must be done only when all digital filters are disabled.
 *
 * \param[in] obj : pointer to APC register instance
 * \param[in] value : the value of PORTB digital filter clock source
 *                    - 0b : clk_apb
 *                    - 1b : clk_lpo128
 */
__attribute__((always_inline)) static inline void ApcReg_SetClkCfgSrcPortBFlt(ApcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CLK_CFG;

    tmp &= ~APC_CLK_CFG_SRC_PORTB_FLT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << APC_CLK_CFG_SRC_PORTB_FLT_SHIFT)) & APC_CLK_CFG_SRC_PORTB_FLT_MASK);
    obj->CLK_CFG = tmp;
}

/*! \brief Gets the PORTA digital filter clock source
 *
 * This function gets the current PORTA digital filter clock source.
 * Changing the filter clock source must be done only when all digital filters are disabled.
 *
 * \param[in] obj : pointer to APC register instance
 * \return PORTA digital filter clock source
 *         - 0b : clk_apb
 *         - 1b : clk_lpo128
 */
__attribute__((always_inline)) static inline uint8_t ApcReg_GetClkCfgSrcPortAFlt(const ApcRegType *obj)
{
    return ((obj->CLK_CFG & APC_CLK_CFG_SRC_PORTA_FLT_MASK) >> APC_CLK_CFG_SRC_PORTA_FLT_SHIFT);
}

/*! \brief Sets the PORTA digital filter clock source
 *
 * This function sets the PORTA digital filter clock source.
 * Changing the filter clock source must be done only when all digital filters are disabled.
 *
 * \param[in] obj : pointer to APC register instance
 * \param[in] value : the value of PORTA digital filter clock source
 *                    - 0b : clk_apb
 *                    - 1b : clk_lpo128
 */
__attribute__((always_inline)) static inline void ApcReg_SetClkCfgSrcPortAFlt(ApcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CLK_CFG;

    tmp &= ~APC_CLK_CFG_SRC_PORTA_FLT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << APC_CLK_CFG_SRC_PORTA_FLT_SHIFT)) & APC_CLK_CFG_SRC_PORTA_FLT_MASK);
    obj->CLK_CFG = tmp;
}

/*! \brief Gets the CMP module function clock source
 *
 * This function gets the current CMP module function clock source.
 * In RUN mode, the source should be clk_apb. In STOP and STANDBY mode, the source may be changed to clk_lptmr.
 *
 * \param[in] obj : pointer to APC register instance
 * \return CMP module function clock source
 *         - 0b : clk_apb
 *         - 1b : clk_lptmr
 */
__attribute__((always_inline)) static inline uint8_t ApcReg_GetClkCfgSrcCmp0(const ApcRegType *obj)
{
    return ((obj->CLK_CFG & APC_CLK_CFG_SRC_CMP0_MASK) >> APC_CLK_CFG_SRC_CMP0_SHIFT);
}

/*! \brief Sets the CMP module function clock source
 *
 * This function sets the CMP module function clock source.
 * In RUN mode, the source should be clk_apb. In STOP and STANDBY mode, the source may be changed to clk_lptmr.
 *
 * \param[in] obj : pointer to APC register instance
 * \param[in] value : the value of CMP module function clock source
 *                    - 0b : clk_apb
 *                    - 1b : clk_lptmr
 */
__attribute__((always_inline)) static inline void ApcReg_SetClkCfgSrcCmp0(ApcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CLK_CFG;

    tmp &= ~APC_CLK_CFG_SRC_CMP0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << APC_CLK_CFG_SRC_CMP0_SHIFT)) & APC_CLK_CFG_SRC_CMP0_MASK);
    obj->CLK_CFG = tmp;
}

/*! \brief Gets the LPTMR module function clock divide ratio
 *
 * This function gets the current LPTMR module function clock divide ratio .
 * This register should be changed after the clock is disabled at least 2 pre-changed clock cycles and 2 after-changed clock cycles.
 * Reset by POR/LVR only
 *
 * \param[in] obj : pointer to APC register instance
 * \return LPTMR module function clock divide ratio
 *         - 0h : 1
 *         - 1h : 2
 *         - 2h : 3
 *         - 3h : 4
 *         - 4h : 5
 *         - 5h : 6
 *         - 6h : 7
 *         - 7h : 8
 */
__attribute__((always_inline)) static inline uint8_t ApcReg_GetClkCfgDivLptmr(const ApcRegType *obj)
{
    return ((obj->CLK_CFG & APC_CLK_CFG_DIV_LPTMR_MASK) >> APC_CLK_CFG_DIV_LPTMR_SHIFT);
}

/*! \brief Sets the LPTMR module function clock divide ratio
 *
 * This function sets the LPTMR module function clock divide ratio .
 * This register should be changed after the clock is disabled at least 2 pre-changed clock cycles and 2 after-changed clock cycles.
 * Reset by POR/LVR only
 *
 * \param[in] obj : pointer to APC register instance
 * \param[in] value : the value of LPTMR module function clock divide ratio
 *                    - 0h : 1
 *                    - 1h : 2
 *                    - 2h : 3
 *                    - 3h : 4
 *                    - 4h : 5
 *                    - 5h : 6
 *                    - 6h : 7
 *                    - 7h : 8
 */
__attribute__((always_inline)) static inline void ApcReg_SetClkCfgDivLptmr(ApcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CLK_CFG;

    tmp &= ~APC_CLK_CFG_DIV_LPTMR_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << APC_CLK_CFG_DIV_LPTMR_SHIFT)) & APC_CLK_CFG_DIV_LPTMR_MASK);
    obj->CLK_CFG = tmp;
}

/*! \brief Gets the LPTMR module function clock source
 *
 * This function gets the current LPTMR module function clock source.
 * Reset by POR/LVR only
 * This register should be changed after the clock is disabled at least 2 pre-changed clock cycles and 2 after-changed clock cycles.
 *
 * \param[in] obj : pointer to APC register instance
 * \return LPTMR module function clock source
 *         - 0h : clk_firc_div2
 *         - 1h : clk_sosc_div2
 *         - 2h : clk_pll_div2
 *         - 3h : clk_sirc_div2
 *         - 4h : clk_lpo128
 *         - 5h : clk_lpo1
 *         - 6h : clk_lpo32
 *         - 7h : RTC_CLKIN from PAD_PTA7
 */
__attribute__((always_inline)) static inline uint8_t ApcReg_GetClkCfgSrcLptmr(const ApcRegType *obj)
{
    return ((obj->CLK_CFG & APC_CLK_CFG_SRC_LPTMR_MASK) >> APC_CLK_CFG_SRC_LPTMR_SHIFT);
}

/*! \brief Sets the LPTMR module function clock source
 *
 * This function sets the LPTMR module function clock source.
 * Reset by POR/LVR only
 * This register should be changed after the clock is disabled at least 2 pre-changed clock cycles and 2 after-changed clock cycles.
 *
 * \param[in] obj : pointer to APC register instance
 * \param[in] value : the value of LPTMR module function clock source
 *                    - 0h : clk_firc_div2
 *                    - 1h : clk_sosc_div2
 *                    - 2h : clk_pll_div2
 *                    - 3h : clk_sirc_div2
 *                    - 4h : clk_lpo128
 *                    - 5h : clk_lpo1
 *                    - 6h : clk_lpo32
 *                    - 7h : RTC_CLKIN from PAD_PTA7
 */
__attribute__((always_inline)) static inline void ApcReg_SetClkCfgSrcLptmr(ApcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CLK_CFG;

    tmp &= ~APC_CLK_CFG_SRC_LPTMR_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << APC_CLK_CFG_SRC_LPTMR_SHIFT)) & APC_CLK_CFG_SRC_LPTMR_MASK);
    obj->CLK_CFG = tmp;
}

/*! \brief Gets the LPIT module function clock source
 *
 * This function gets the current LPIT module function clock source.
 * This register should be changed after the clock is disabled at least 2 pre-changed clock cycles and 2 after-changed clock cycles.
 *
 * \param[in] obj : pointer to APC register instance
 * \return LPIT module function clock source
 *         - 0h : clk_firc_div2
 *         - 1h : clk_sosc_div2
 *         - 2h : clk_pll_div2
 *         - 3h : clk_sirc_div2
 *         - 4h : clk_lpo128
 *         - others : reserved
 */
__attribute__((always_inline)) static inline uint8_t ApcReg_GetClkCfgSrcLpit(const ApcRegType *obj)
{
    return ((obj->CLK_CFG & APC_CLK_CFG_SRC_LPIT_MASK) >> APC_CLK_CFG_SRC_LPIT_SHIFT);
}

/*! \brief Sets the LPIT module function clock source
 *
 * This function sets the LPIT module function clock source.
 * This register should be changed after the clock is disabled at least 2 pre-changed clock cycles and 2 after-changed clock cycles.
 *
 * \param[in] obj : pointer to APC register instance
 * \param[in] value : the value of LPIT module function clock source
 *                    - 0h : clk_firc_div2
 *                    - 1h : clk_sosc_div2
 *                    - 2h : clk_pll_div2
 *                    - 3h : clk_sirc_div2
 *                    - 4h : clk_lpo128
 *                    - others : reserved
 */
__attribute__((always_inline)) static inline void ApcReg_SetClkCfgSrcLpit(ApcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CLK_CFG;

    tmp &= ~APC_CLK_CFG_SRC_LPIT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << APC_CLK_CFG_SRC_LPIT_SHIFT)) & APC_CLK_CFG_SRC_LPIT_MASK);
    obj->CLK_CFG = tmp;
}

/*! \brief Gets the clock source of PIN Reset digital filter
 *
 * This function gets the current clock source of PIN Reset digital filter.
 * This register should be changed after the clock is disabled at least 2 pre-changed clock cycles and 2 after-changed clock cycles.

 *
 * \param[in] obj : pointer to APC register instance
 * \return clock source of PIN Reset digital filter
 *         - 0b : clk_apb
 *         - 1b : clk_lpo128
 */
__attribute__((always_inline)) static inline uint8_t ApcReg_GetClkCfgSrcExtFlt(const ApcRegType *obj)
{
    return ((obj->CLK_CFG & APC_CLK_CFG_SRC_EXT_FLT_MASK) >> APC_CLK_CFG_SRC_EXT_FLT_SHIFT);
}

/*! \brief Sets the clock source of PIN Reset digital filter
 *
 * This function sets the clock source of PIN Reset digital filter.
 * This register should be changed after the clock is disabled at least 2 pre-changed clock cycles and 2 after-changed clock cycles.

 *
 * \param[in] obj : pointer to APC register instance
 * \param[in] value : the value of clock source of PIN Reset digital filter
 *                    - 0b : clk_apb
 *                    - 1b : clk_lpo128
 */
__attribute__((always_inline)) static inline void ApcReg_SetClkCfgSrcExtFlt(ApcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CLK_CFG;

    tmp &= ~APC_CLK_CFG_SRC_EXT_FLT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << APC_CLK_CFG_SRC_EXT_FLT_SHIFT)) & APC_CLK_CFG_SRC_EXT_FLT_MASK);
    obj->CLK_CFG = tmp;
}

/*! \brief Gets the RTC module clock source select
 *
 * This function gets the current RTC module clock source select.
 * This register should be changed after the clock is disabled at least 2 pre-changed clock cycles and 2 after-changed clock cycles.

 *
 * \param[in] obj : pointer to APC register instance
 * \return RTC module clock source select
 *         - 0b : clk_rtc
 *         - 1b : clk_lpo1
 */
__attribute__((always_inline)) static inline uint8_t ApcReg_GetClkCfgSrcRtcCnt(const ApcRegType *obj)
{
    return ((obj->CLK_CFG & APC_CLK_CFG_SRC_RTC_CNT_MASK) >> APC_CLK_CFG_SRC_RTC_CNT_SHIFT);
}

/*! \brief Sets the RTC module clock source select
 *
 * This function sets the RTC module clock source select.
 * This register should be changed after the clock is disabled at least 2 pre-changed clock cycles and 2 after-changed clock cycles.

 *
 * \param[in] obj : pointer to APC register instance
 * \param[in] value : the value of RTC module clock source select
 *                    - 0b : clk_rtc
 *                    - 1b : clk_lpo1
 */
__attribute__((always_inline)) static inline void ApcReg_SetClkCfgSrcRtcCnt(ApcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CLK_CFG;

    tmp &= ~APC_CLK_CFG_SRC_RTC_CNT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << APC_CLK_CFG_SRC_RTC_CNT_SHIFT)) & APC_CLK_CFG_SRC_RTC_CNT_MASK);
    obj->CLK_CFG = tmp;
}

/*! \brief Gets the clk_rtc for rtc module , MFT fixed clock and PAD: clk_rtc select
 *
 * This function gets the current clk_rtc for rtc module , MFT fixed clock and PAD: clk_rtc select.
 * This register should be changed after the clock is disabled at least 2 pre-changed clock cycles and 2 after-changed clock cycles.
 *
 * \note It is not just for RTC module
 *
 * \param[in] obj : pointer to APC register instance
 * \return clk_rtc for rtc module , MFT fixed clock and PAD: clk_rtc select
 *         - 0b : clk_lpo32
 *         - 1b : RTC_CLKIN from PAD_PTA7
 */
__attribute__((always_inline)) static inline uint8_t ApcReg_GetClkCfgSrcRtcSrc(const ApcRegType *obj)
{
    return ((obj->CLK_CFG & APC_CLK_CFG_SRC_RTC_SRC_MASK) >> APC_CLK_CFG_SRC_RTC_SRC_SHIFT);
}

/*! \brief Sets the clk_rtc for rtc module , MFT fixed clock and PAD: clk_rtc select
 *
 * This function sets the clk_rtc for rtc module , MFT fixed clock and PAD: clk_rtc select.
 * This register should be changed after the clock is disabled at least 2 pre-changed clock cycles and 2 after-changed clock cycles.
 *
 * \note It is not just for RTC module
 *
 * \param[in] obj : pointer to APC register instance
 * \param[in] value : the value of clk_rtc for rtc module , MFT fixed clock and PAD: clk_rtc select
 *                    - 0b : clk_lpo32
 *                    - 1b : RTC_CLKIN from PAD_PTA7
 */
__attribute__((always_inline)) static inline void ApcReg_SetClkCfgSrcRtcSrc(ApcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CLK_CFG;

    tmp &= ~APC_CLK_CFG_SRC_RTC_SRC_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << APC_CLK_CFG_SRC_RTC_SRC_SHIFT)) & APC_CLK_CFG_SRC_RTC_SRC_MASK);
    obj->CLK_CFG = tmp;
}

/*! \brief Gets the PORTE module clock enable for both config clock and function
 *
 * This function gets the current PORTE module clock enable for both config clock and function.
 *
 * \param[in] obj : pointer to APC register instance
 * \return PORTE module clock enable for both config clock and function
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t ApcReg_GetClkEnPortE(const ApcRegType *obj)
{
    return ((obj->CLK_EN & APC_CLK_EN_PORTE_MASK) >> APC_CLK_EN_PORTE_SHIFT);
}

/*! \brief Sets the PORTE module clock enable for both config clock and function
 *
 * This function sets the PORTE module clock enable for both config clock and function.
 *
 * \param[in] obj : pointer to APC register instance
 * \param[in] value : the value of PORTE module clock enable for both config clock and function
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void ApcReg_SetClkEnPortE(ApcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CLK_EN;

    tmp &= ~APC_CLK_EN_PORTE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << APC_CLK_EN_PORTE_SHIFT)) & APC_CLK_EN_PORTE_MASK);
    obj->CLK_EN = tmp;
}

/*! \brief Gets the PORTD module clock enable for both config clock and function
 *
 * This function gets the current PORTD module clock enable for both config clock and function.
 *
 * \param[in] obj : pointer to APC register instance
 * \return PORTD module clock enable for both config clock and function
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t ApcReg_GetClkEnPortD(const ApcRegType *obj)
{
    return ((obj->CLK_EN & APC_CLK_EN_PORTD_MASK) >> APC_CLK_EN_PORTD_SHIFT);
}

/*! \brief Sets the PORTD module clock enable for both config clock and function
 *
 * This function sets the PORTD module clock enable for both config clock and function.
 *
 * \param[in] obj : pointer to APC register instance
 * \param[in] value : the value of PORTD module clock enable for both config clock and function
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void ApcReg_SetClkEnPortD(ApcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CLK_EN;

    tmp &= ~APC_CLK_EN_PORTD_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << APC_CLK_EN_PORTD_SHIFT)) & APC_CLK_EN_PORTD_MASK);
    obj->CLK_EN = tmp;
}

/*! \brief Gets the PORTC module clock enable for both config clock and function
 *
 * This function gets the current PORTC module clock enable for both config clock and function.
 *
 * \param[in] obj : pointer to APC register instance
 * \return PORTC module clock enable for both config clock and function
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t ApcReg_GetClkEnPortC(const ApcRegType *obj)
{
    return ((obj->CLK_EN & APC_CLK_EN_PORTC_MASK) >> APC_CLK_EN_PORTC_SHIFT);
}

/*! \brief Sets the PORTC module clock enable for both config clock and function
 *
 * This function sets the PORTC module clock enable for both config clock and function.
 *
 * \param[in] obj : pointer to APC register instance
 * \param[in] value : the value of PORTC module clock enable for both config clock and function
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void ApcReg_SetClkEnPortC(ApcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CLK_EN;

    tmp &= ~APC_CLK_EN_PORTC_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << APC_CLK_EN_PORTC_SHIFT)) & APC_CLK_EN_PORTC_MASK);
    obj->CLK_EN = tmp;
}

/*! \brief Gets the PORTB module clock enable for both config clock and function
 *
 * This function gets the current PORTB module clock enable for both config clock and function.
 *
 * \param[in] obj : pointer to APC register instance
 * \return PORTB module clock enable for both config clock and function
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t ApcReg_GetClkEnPortB(const ApcRegType *obj)
{
    return ((obj->CLK_EN & APC_CLK_EN_PORTB_MASK) >> APC_CLK_EN_PORTB_SHIFT);
}

/*! \brief Sets the PORTB module clock enable for both config clock and function
 *
 * This function sets the PORTB module clock enable for both config clock and function.
 *
 * \param[in] obj : pointer to APC register instance
 * \param[in] value : the value of PORTB module clock enable for both config clock and function
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void ApcReg_SetClkEnPortB(ApcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CLK_EN;

    tmp &= ~APC_CLK_EN_PORTB_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << APC_CLK_EN_PORTB_SHIFT)) & APC_CLK_EN_PORTB_MASK);
    obj->CLK_EN = tmp;
}

/*! \brief Gets the PORTA module clock enable for both config clock and function
 *
 * This function gets the current PORTA module clock enable for both config clock and function.
 *
 * \param[in] obj : pointer to APC register instance
 * \return PORTA module clock enable for both config clock and function
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t ApcReg_GetClkEnPortA(const ApcRegType *obj)
{
    return ((obj->CLK_EN & APC_CLK_EN_PORTA_MASK) >> APC_CLK_EN_PORTA_SHIFT);
}

/*! \brief Sets the PORTA module clock enable for both config clock and function
 *
 * This function sets the PORTA module clock enable for both config clock and function.
 *
 * \param[in] obj : pointer to APC register instance
 * \param[in] value : the value of PORTA module clock enable for both config clock and function
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void ApcReg_SetClkEnPortA(ApcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CLK_EN;

    tmp &= ~APC_CLK_EN_PORTA_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << APC_CLK_EN_PORTA_SHIFT)) & APC_CLK_EN_PORTA_MASK);
    obj->CLK_EN = tmp;
}

/*! \brief Gets the LPIT module clock enable for both config clock and function
 *
 * This function gets the current LPIT module clock enable for both config clock and function.
 *
 * \param[in] obj : pointer to APC register instance
 * \return LPIT module clock enable for both config clock and function
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t ApcReg_GetClkEnLpit(const ApcRegType *obj)
{
    return ((obj->CLK_EN & APC_CLK_EN_LPIT_MASK) >> APC_CLK_EN_LPIT_SHIFT);
}

/*! \brief Sets the LPIT module clock enable for both config clock and function
 *
 * This function sets the LPIT module clock enable for both config clock and function.
 *
 * \param[in] obj : pointer to APC register instance
 * \param[in] value : the value of LPIT module clock enable for both config clock and function
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void ApcReg_SetClkEnLpit(ApcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CLK_EN;

    tmp &= ~APC_CLK_EN_LPIT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << APC_CLK_EN_LPIT_SHIFT)) & APC_CLK_EN_LPIT_MASK);
    obj->CLK_EN = tmp;
}

/*! \brief Gets the CMP module clock enable for both config clock and function
 *
 * This function gets the current CMP module clock enable for both config clock and function .
 *
 * \param[in] obj : pointer to APC register instance
 * \return CMP module clock enable for both config clock and function
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t ApcReg_GetClkEnCmp0(const ApcRegType *obj)
{
    return ((obj->CLK_EN & APC_CLK_EN_CMP0_MASK) >> APC_CLK_EN_CMP0_SHIFT);
}

/*! \brief Sets the CMP module clock enable for both config clock and function
 *
 * This function sets the CMP module clock enable for both config clock and function .
 *
 * \param[in] obj : pointer to APC register instance
 * \param[in] value : the value of CMP module clock enable for both config clock and function
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void ApcReg_SetClkEnCmp0(ApcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CLK_EN;

    tmp &= ~APC_CLK_EN_CMP0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << APC_CLK_EN_CMP0_SHIFT)) & APC_CLK_EN_CMP0_MASK);
    obj->CLK_EN = tmp;
}

/*! \brief Gets the clk_lpo32 enable
 *
 * This function gets the current clk_lpo32 enable.
 * Reset by POR/LVR only
 *
 * \param[in] obj : pointer to APC register instance
 * \return clk_lpo32 enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t ApcReg_GetClkEnLpo32(const ApcRegType *obj)
{
    return ((obj->CLK_EN & APC_CLK_EN_LPO32_MASK) >> APC_CLK_EN_LPO32_SHIFT);
}

/*! \brief Sets the clk_lpo32 enable
 *
 * This function sets the clk_lpo32 enable.
 * Reset by POR/LVR only
 *
 * \param[in] obj : pointer to APC register instance
 * \param[in] value : the value of clk_lpo32 enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void ApcReg_SetClkEnLpo32(ApcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CLK_EN;

    tmp &= ~APC_CLK_EN_LPO32_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << APC_CLK_EN_LPO32_SHIFT)) & APC_CLK_EN_LPO32_MASK);
    obj->CLK_EN = tmp;
}

/*! \brief Gets the clk_lpo1 enable
 *
 * This function gets the current clk_lpo1 enable.
 * Reset by POR/LVR only
 *
 * \param[in] obj : pointer to APC register instance
 * \return clk_lpo1 enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t ApcReg_GetClkEnLpo1(const ApcRegType *obj)
{
    return ((obj->CLK_EN & APC_CLK_EN_LPO1_MASK) >> APC_CLK_EN_LPO1_SHIFT);
}

/*! \brief Sets the clk_lpo1 enable
 *
 * This function sets the clk_lpo1 enable.
 * Reset by POR/LVR only
 *
 * \param[in] obj : pointer to APC register instance
 * \param[in] value : the value of clk_lpo1 enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void ApcReg_SetClkEnLpo1(ApcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CLK_EN;

    tmp &= ~APC_CLK_EN_LPO1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << APC_CLK_EN_LPO1_SHIFT)) & APC_CLK_EN_LPO1_MASK);
    obj->CLK_EN = tmp;
}

/*! \brief Gets the LPTMR module clock enable for both config clock and function clock
 *
 * This function gets the current LPTMR module clock enable for both config clock and function clock.
 * Reset by POR/LVR only
 *
 * \param[in] obj : pointer to APC register instance
 * \return LPTMR module clock enable for both config clock and function clock
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t ApcReg_GetClkEnLptmr(const ApcRegType *obj)
{
    return ((obj->CLK_EN & APC_CLK_EN_LPTMR_MASK) >> APC_CLK_EN_LPTMR_SHIFT);
}

/*! \brief Sets the LPTMR module clock enable for both config clock and function clock
 *
 * This function sets the LPTMR module clock enable for both config clock and function clock.
 * Reset by POR/LVR only
 *
 * \param[in] obj : pointer to APC register instance
 * \param[in] value : the value of LPTMR module clock enable for both config clock and function clock
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void ApcReg_SetClkEnLptmr(ApcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CLK_EN;

    tmp &= ~APC_CLK_EN_LPTMR_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << APC_CLK_EN_LPTMR_SHIFT)) & APC_CLK_EN_LPTMR_MASK);
    obj->CLK_EN = tmp;
}

/*! \brief Gets the clk_rtc enable for RTC module and MFT
 *
 * This function gets the current clk_rtc enable for RTC module and MFT.
 *
 * \param[in] obj : pointer to APC register instance
 * \return clk_rtc enable for RTC module and MFT
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t ApcReg_GetClkEnRtcSrc(const ApcRegType *obj)
{
    return ((obj->CLK_EN & APC_CLK_EN_RTC_SRC_MASK) >> APC_CLK_EN_RTC_SRC_SHIFT);
}

/*! \brief Sets the clk_rtc enable for RTC module and MFT
 *
 * This function sets the clk_rtc enable for RTC module and MFT.
 *
 * \param[in] obj : pointer to APC register instance
 * \param[in] value : the value of clk_rtc enable for RTC module and MFT
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void ApcReg_SetClkEnRtcSrc(ApcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CLK_EN;

    tmp &= ~APC_CLK_EN_RTC_SRC_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << APC_CLK_EN_RTC_SRC_SHIFT)) & APC_CLK_EN_RTC_SRC_MASK);
    obj->CLK_EN = tmp;
}

/*! \brief Gets the RTC module clock enable for both config clock and function clock
 *
 * This function gets the current RTC module clock enable for both config clock and function clock.
 *
 * \param[in] obj : pointer to APC register instance
 * \return RTC module clock enable for both config clock and function clock
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t ApcReg_GetClkEnRtcCnt(const ApcRegType *obj)
{
    return ((obj->CLK_EN & APC_CLK_EN_RTC_CNT_MASK) >> APC_CLK_EN_RTC_CNT_SHIFT);
}

/*! \brief Sets the RTC module clock enable for both config clock and function clock
 *
 * This function sets the RTC module clock enable for both config clock and function clock.
 *
 * \param[in] obj : pointer to APC register instance
 * \param[in] value : the value of RTC module clock enable for both config clock and function clock
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void ApcReg_SetClkEnRtcCnt(ApcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CLK_EN;

    tmp &= ~APC_CLK_EN_RTC_CNT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << APC_CLK_EN_RTC_CNT_SHIFT)) & APC_CLK_EN_RTC_CNT_MASK);
    obj->CLK_EN = tmp;
}

/*! \brief Sets the PORTE module software reset for both config clock domain and function clock domain
 *
 * This function sets the PORTE module software reset for both config clock domain and function clock domain.
 *
 * \param[in] obj : pointer to APC register instance
 * \param[in] value : the value of PORTE module software reset for both config clock domain and function clock domain
 *                    - 0b : not reset
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void ApcReg_SetSwRstPortE(ApcRegType *obj, uint8_t value)
{
    obj->SW_RST = (((uint32_t)(((uint32_t)(value)) << APC_SW_RST_PORTE_SHIFT)) & APC_SW_RST_PORTE_MASK);
}

/*! \brief Sets the PORTD module software reset for both config clock domain and function clock domain
 *
 * This function sets the PORTD module software reset for both config clock domain and function clock domain.
 *
 * \param[in] obj : pointer to APC register instance
 * \param[in] value : the value of PORTD module software reset for both config clock domain and function clock domain
 *                    - 0b : not reset
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void ApcReg_SetSwRstPortD(ApcRegType *obj, uint8_t value)
{
    obj->SW_RST = (((uint32_t)(((uint32_t)(value)) << APC_SW_RST_PORTD_SHIFT)) & APC_SW_RST_PORTD_MASK);
}

/*! \brief Sets the PORTC module software reset for both config clock domain and function clock domain
 *
 * This function sets the PORTC module software reset for both config clock domain and function clock domain.
 *
 * \param[in] obj : pointer to APC register instance
 * \param[in] value : the value of PORTC module software reset for both config clock domain and function clock domain
 *                    - 0b : not reset
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void ApcReg_SetSwRstPortC(ApcRegType *obj, uint8_t value)
{
    obj->SW_RST = (((uint32_t)(((uint32_t)(value)) << APC_SW_RST_PORTC_SHIFT)) & APC_SW_RST_PORTC_MASK);
}

/*! \brief Sets the PORTB module software reset for both config clock domain and function clock domain
 *
 * This function sets the PORTB module software reset for both config clock domain and function clock domain.
 *
 * \param[in] obj : pointer to APC register instance
 * \param[in] value : the value of PORTB module software reset for both config clock domain and function clock domain
 *                    - 0b : not reset
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void ApcReg_SetSwRstPortB(ApcRegType *obj, uint8_t value)
{
    obj->SW_RST = (((uint32_t)(((uint32_t)(value)) << APC_SW_RST_PORTB_SHIFT)) & APC_SW_RST_PORTB_MASK);
}

/*! \brief Sets the PORTA module software reset for both config clock domain and function clock domain
 *
 * This function sets the PORTA module software reset for both config clock domain and function clock domain.
 *
 * \param[in] obj : pointer to APC register instance
 * \param[in] value : the value of PORTA module software reset for both config clock domain and function clock domain
 *                    - 0b : not reset
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void ApcReg_SetSwRstPortA(ApcRegType *obj, uint8_t value)
{
    obj->SW_RST = (((uint32_t)(((uint32_t)(value)) << APC_SW_RST_PORTA_SHIFT)) & APC_SW_RST_PORTA_MASK);
}

/*! \brief Sets the LPIT module software reset for both config clock domain and function clock domain
 *
 * This function sets the LPIT module software reset for both config clock domain and function clock domain.
 *
 * \param[in] obj : pointer to APC register instance
 * \param[in] value : the value of LPIT module software reset for both config clock domain and function clock domain
 *                    - 0b : not reset
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void ApcReg_SetSwRstLpit(ApcRegType *obj, uint8_t value)
{
    obj->SW_RST = (((uint32_t)(((uint32_t)(value)) << APC_SW_RST_LPIT_SHIFT)) & APC_SW_RST_LPIT_MASK);
}

/*! \brief Sets the CMP0 module software reset for both config clock domain and function clock domain
 *
 * This function sets the CMP0 module software reset for both config clock domain and function clock domain.
 *
 * \param[in] obj : pointer to APC register instance
 * \param[in] value : the value of CMP0 module software reset for both config clock domain and function clock domain
 *                    - 0b : not reset
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void ApcReg_SetSwRstCmp0(ApcRegType *obj, uint8_t value)
{
    obj->SW_RST = (((uint32_t)(((uint32_t)(value)) << APC_SW_RST_CMP0_SHIFT)) & APC_SW_RST_CMP0_MASK);
}

/*! \brief Sets the LPTMR module software reset for both config clock domain and function clock domain
 *
 * This function sets the LPTMR module software reset for both config clock domain and function clock domain.
 * Reset by POR/LVR only
 *
 * \param[in] obj : pointer to APC register instance
 * \param[in] value : the value of LPTMR module software reset for both config clock domain and function clock domain
 *                    - 0b : not reset
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void ApcReg_SetSwRstLptmr(ApcRegType *obj, uint8_t value)
{
    obj->SW_RST = (((uint32_t)(((uint32_t)(value)) << APC_SW_RST_LPTMR_SHIFT)) & APC_SW_RST_LPTMR_MASK);
}

/*! \brief Sets the WDG module software reset for both config clock domain and function clock domain
 *
 * This function sets the WDG module software reset for both config clock domain and function clock domain.
 *
 * \param[in] obj : pointer to APC register instance
 * \param[in] value : the value of WDG module software reset for both config clock domain and function clock domain
 *                    - 0b : not reset
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void ApcReg_SetSwRstWdg(ApcRegType *obj, uint8_t value)
{
    obj->SW_RST = (((uint32_t)(((uint32_t)(value)) << APC_SW_RST_WDG_SHIFT)) & APC_SW_RST_WDG_MASK);
}

/*! \brief Gets the PORTE module software reset for both config clock domain and function clock domain
 *
 * This function gets the current PORTE module software reset for both config clock domain and function clock domain.
 *
 * \param[in] obj : pointer to APC register instance
 * \return PORTE module software reset for both config clock domain and function clock domain
 *         - 0b : not reset
 *         - 1b : reset
 */
__attribute__((always_inline)) static inline uint8_t ApcReg_GetRstStPortE(const ApcRegType *obj)
{
    return ((obj->RST_ST & APC_RST_ST_PORTE_MASK) >> APC_RST_ST_PORTE_SHIFT);
}

/*! \brief Gets the PORTD module software reset for both config clock domain and function clock domain
 *
 * This function gets the current PORTD module software reset for both config clock domain and function clock domain.
 *
 * \param[in] obj : pointer to APC register instance
 * \return PORTD module software reset for both config clock domain and function clock domain
 *         - 0b : not reset
 *         - 1b : reset
 */
__attribute__((always_inline)) static inline uint8_t ApcReg_GetRstStPortD(const ApcRegType *obj)
{
    return ((obj->RST_ST & APC_RST_ST_PORTD_MASK) >> APC_RST_ST_PORTD_SHIFT);
}

/*! \brief Gets the PORTC module software reset for both config clock domain and function clock domain
 *
 * This function gets the current PORTC module software reset for both config clock domain and function clock domain.
 *
 * \param[in] obj : pointer to APC register instance
 * \return PORTC module software reset for both config clock domain and function clock domain
 *         - 0b : not reset
 *         - 1b : reset
 */
__attribute__((always_inline)) static inline uint8_t ApcReg_GetRstStPortC(const ApcRegType *obj)
{
    return ((obj->RST_ST & APC_RST_ST_PORTC_MASK) >> APC_RST_ST_PORTC_SHIFT);
}

/*! \brief Gets the PORTB module software reset for both config clock domain and function clock domain
 *
 * This function gets the current PORTB module software reset for both config clock domain and function clock domain.
 *
 * \param[in] obj : pointer to APC register instance
 * \return PORTB module software reset for both config clock domain and function clock domain
 *         - 0b : not reset
 *         - 1b : reset
 */
__attribute__((always_inline)) static inline uint8_t ApcReg_GetRstStPortB(const ApcRegType *obj)
{
    return ((obj->RST_ST & APC_RST_ST_PORTB_MASK) >> APC_RST_ST_PORTB_SHIFT);
}

/*! \brief Gets the PORTA module software reset for both config clock domain and function clock domain
 *
 * This function gets the current PORTA module software reset for both config clock domain and function clock domain.
 *
 * \param[in] obj : pointer to APC register instance
 * \return PORTA module software reset for both config clock domain and function clock domain
 *         - 0b : not reset
 *         - 1b : reset
 */
__attribute__((always_inline)) static inline uint8_t ApcReg_GetRstStPortA(const ApcRegType *obj)
{
    return ((obj->RST_ST & APC_RST_ST_PORTA_MASK) >> APC_RST_ST_PORTA_SHIFT);
}

/*! \brief Gets the LPIT module software reset for both config clock domain and function clock domain
 *
 * This function gets the current LPIT module software reset for both config clock domain and function clock domain.
 *
 * \param[in] obj : pointer to APC register instance
 * \return LPIT module software reset for both config clock domain and function clock domain
 *         - 0b : not reset
 *         - 1b : reset
 */
__attribute__((always_inline)) static inline uint8_t ApcReg_GetRstStLpit(const ApcRegType *obj)
{
    return ((obj->RST_ST & APC_RST_ST_LPIT_MASK) >> APC_RST_ST_LPIT_SHIFT);
}

/*! \brief Gets the CMP0 module software reset for both config clock domain and function clock domain
 *
 * This function gets the current CMP0 module software reset for both config clock domain and function clock domain.
 *
 * \param[in] obj : pointer to APC register instance
 * \return CMP0 module software reset for both config clock domain and function clock domain
 *         - 0b : not reset
 *         - 1b : reset
 */
__attribute__((always_inline)) static inline uint8_t ApcReg_GetRstStCmp0(const ApcRegType *obj)
{
    return ((obj->RST_ST & APC_RST_ST_CMP0_MASK) >> APC_RST_ST_CMP0_SHIFT);
}

/*! \brief Gets the LPTMR module software reset for both config clock domain and function clock domain
 *
 * This function gets the current LPTMR module software reset for both config clock domain and function clock domain.
 *
 * \param[in] obj : pointer to APC register instance
 * \return LPTMR module software reset for both config clock domain and function clock domain
 *         - 0b : not reset
 *         - 1b : reset
 */
__attribute__((always_inline)) static inline uint8_t ApcReg_GetRstStLptmr(const ApcRegType *obj)
{
    return ((obj->RST_ST & APC_RST_ST_LPTMR_MASK) >> APC_RST_ST_LPTMR_SHIFT);
}

/*! \brief Gets the WDG module software reset for both config clock domain and function clock domain
 *
 * This function gets the current WDG module software reset for both config clock domain and function clock domain.
 *
 * \param[in] obj : pointer to APC register instance
 * \return WDG module software reset for both config clock domain and function clock domain
 *         - 0b : not reset
 *         - 1b : reset
 */
__attribute__((always_inline)) static inline uint8_t ApcReg_GetRstStWdg(const ApcRegType *obj)
{
    return ((obj->RST_ST & APC_RST_ST_WDG_MASK) >> APC_RST_ST_WDG_SHIFT);
}

/*! \brief Gets the RTC module software reset for both config clock domain and function clock domain
 *
 * This function gets the current RTC module software reset for both config clock domain and function clock domain.
 *
 * \param[in] obj : pointer to APC register instance
 * \return RTC module software reset for both config clock domain and function clock domain
 *         - 0b : not reset
 *         - 1b : reset
 */
__attribute__((always_inline)) static inline uint8_t ApcReg_GetRstStRtc(const ApcRegType *obj)
{
    return ((obj->RST_ST & APC_RST_ST_RTC_MASK) >> APC_RST_ST_RTC_SHIFT);
}

/*! \brief Sets the APC register unlock key
 *
 * This function sets the APC register unlock key.
 * Registers in APC is locked by default. Before writing registers in APC, write unlock key to this register.
 *
 * \param[in] obj : pointer to APC register instance
 * \param[in] value : the value of APC register unlock key
 *                    - 0xC1C51F9C : unlock
 *                    - other : lock
 */
__attribute__((always_inline)) static inline void ApcReg_SetLockKey(ApcRegType *obj, uint32_t value)
{
    obj->LOCK = value;
}

/*! \brief Gets the APC register configuration lock status
 *
 * This function gets the current APC register configuration lock status.
 *
 * \param[in] obj : pointer to APC register instance
 * \return APC register configuration lock status
 *         - 0b : unlock
 *         - 1b : lock
 */
__attribute__((always_inline)) static inline uint8_t ApcReg_GetLockStLock(const ApcRegType *obj)
{
    return ((obj->LOCK_ST & APC_LOCK_ST_LOCK_MASK) >> APC_LOCK_ST_LOCK_SHIFT);
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _APC_REG_H_ */
