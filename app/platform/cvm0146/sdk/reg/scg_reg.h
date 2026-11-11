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

#ifndef _SCG_REG_H_
#define _SCG_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the SCG Registers
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

/* CSR Bit Fields */
#define SCG_CSR_DIV_TRACE_MASK      (0x70000000u)
#define SCG_CSR_DIV_TRACE_SHIFT     (28u)
#define SCG_CSR_DIV_TRACE_WIDTH     (3u)
#define SCG_CSR_DIV_APB_MASK        (0xF00u)
#define SCG_CSR_DIV_APB_SHIFT       (8u)
#define SCG_CSR_DIV_APB_WIDTH       (4u)
#define SCG_CSR_DIV_CNT_FLS_MASK    (0x1Fu)
#define SCG_CSR_DIV_CNT_FLS_SHIFT   (0u)
#define SCG_CSR_DIV_CNT_FLS_WIDTH   (5u)

/* CKEN Bit Fields */
#define SCG_CKEN_EN_PLL_DIV2_MASK   (0x200u)
#define SCG_CKEN_EN_PLL_DIV2_SHIFT  (9u)
#define SCG_CKEN_EN_PLL_DIV2_WIDTH  (1u)
#define SCG_CKEN_EN_PLL_DIV1_MASK   (0x100u)
#define SCG_CKEN_EN_PLL_DIV1_SHIFT  (8u)
#define SCG_CKEN_EN_PLL_DIV1_WIDTH  (1u)
#define SCG_CKEN_EN_FIRC_DIV2_MASK  (0x80u)
#define SCG_CKEN_EN_FIRC_DIV2_SHIFT (7u)
#define SCG_CKEN_EN_FIRC_DIV2_WIDTH (1u)
#define SCG_CKEN_EN_FIRC_DIV1_MASK  (0x40u)
#define SCG_CKEN_EN_FIRC_DIV1_SHIFT (6u)
#define SCG_CKEN_EN_FIRC_DIV1_WIDTH (1u)
#define SCG_CKEN_EN_SIRC_DIV2_MASK  (0x20u)
#define SCG_CKEN_EN_SIRC_DIV2_SHIFT (5u)
#define SCG_CKEN_EN_SIRC_DIV2_WIDTH (1u)
#define SCG_CKEN_EN_SIRC_DIV1_MASK  (0x10u)
#define SCG_CKEN_EN_SIRC_DIV1_SHIFT (4u)
#define SCG_CKEN_EN_SIRC_DIV1_WIDTH (1u)
#define SCG_CKEN_EN_SOSC_DIV2_MASK  (0x08u)
#define SCG_CKEN_EN_SOSC_DIV2_SHIFT (3u)
#define SCG_CKEN_EN_SOSC_DIV2_WIDTH (1u)
#define SCG_CKEN_EN_SOSC_DIV1_MASK  (0x04u)
#define SCG_CKEN_EN_SOSC_DIV1_SHIFT (2u)
#define SCG_CKEN_EN_SOSC_DIV1_WIDTH (1u)
#define SCG_CKEN_EN_OUT_MASK        (0x02u)
#define SCG_CKEN_EN_OUT_SHIFT       (1u)
#define SCG_CKEN_EN_OUT_WIDTH       (1u)
#define SCG_CKEN_EN_TRACE_MASK      (0x01u)
#define SCG_CKEN_EN_TRACE_SHIFT     (0u)
#define SCG_CKEN_EN_TRACE_WIDTH     (1u)

/* CLKOUT Bit Fields */
#define SCG_CLKOUT_DIV_MASK         (0x700u)
#define SCG_CLKOUT_DIV_SHIFT        (8u)
#define SCG_CLKOUT_DIV_WIDTH        (3u)
#define SCG_CLKOUT_SRC_MASK         (0x70u)
#define SCG_CLKOUT_SRC_SHIFT        (4u)
#define SCG_CLKOUT_SRC_WIDTH        (3u)
#define SCG_CLKOUT_SCG_MASK         (0x07u)
#define SCG_CLKOUT_SCG_SHIFT        (0u)
#define SCG_CLKOUT_SCG_WIDTH        (3u)

/* SOSC_CFG Bit Fields */
#define SCG_SOSC_CFG_DIV2_MASK      (0x70u)
#define SCG_SOSC_CFG_DIV2_SHIFT     (4u)
#define SCG_SOSC_CFG_DIV2_WIDTH     (3u)
#define SCG_SOSC_CFG_DIV1_MASK      (0x07u)
#define SCG_SOSC_CFG_DIV1_SHIFT     (0u)
#define SCG_SOSC_CFG_DIV1_WIDTH     (3u)

/* SIRC_CFG Bit Fields */
#define SCG_SIRC_CFG_DIV2_MASK      (0x70u)
#define SCG_SIRC_CFG_DIV2_SHIFT     (4u)
#define SCG_SIRC_CFG_DIV2_WIDTH     (3u)
#define SCG_SIRC_CFG_DIV1_MASK      (0x07u)
#define SCG_SIRC_CFG_DIV1_SHIFT     (0u)
#define SCG_SIRC_CFG_DIV1_WIDTH     (3u)

/* FIRC_CFG Bit Fields */
#define SCG_FIRC_CFG_DIV2_MASK      (0x70u)
#define SCG_FIRC_CFG_DIV2_SHIFT     (4u)
#define SCG_FIRC_CFG_DIV2_WIDTH     (3u)
#define SCG_FIRC_CFG_DIV1_MASK      (0x07u)
#define SCG_FIRC_CFG_DIV1_SHIFT     (0u)
#define SCG_FIRC_CFG_DIV1_WIDTH     (3u)

/* PLL_CFG Bit Fields */
#define SCG_PLL_CFG_DIV2_MASK       (0x70u)
#define SCG_PLL_CFG_DIV2_SHIFT      (4u)
#define SCG_PLL_CFG_DIV2_WIDTH      (3u)
#define SCG_PLL_CFG_DIV1_MASK       (0x07u)
#define SCG_PLL_CFG_DIV1_SHIFT      (0u)
#define SCG_PLL_CFG_DIV1_WIDTH      (3u)

/* LOCK Bit Fields */
#define SCG_LOCK_KEY_MASK           (0xFFFFFFFFu)
#define SCG_LOCK_KEY_SHIFT          (0u)
#define SCG_LOCK_KEY_WIDTH          (32u)

/* LOCK_ST Bit Fields */
#define SCG_LOCK_ST_LOCK_MASK       (0x01u)
#define SCG_LOCK_ST_LOCK_SHIFT      (0u)
#define SCG_LOCK_ST_LOCK_WIDTH      (1u)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief The definition of SCG registers
 */
typedef struct _ScgRegType_
{
    volatile uint32_t       CSR;           /*!< System clock config, offset: 0x0 */
    volatile uint32_t       CKEN;          /*!< System clock enable, offset: 0x4 */
    volatile uint32_t       CLKOUT;        /*!< System clock out control, offset: 0x8 */
    uint32_t                RESERVED0[1];  /*!< Reserverd block, offset: 0xC */
    volatile uint32_t       SOSC_CFG;      /*!< SOSC clock div configuration, offset: 0x10 */
    uint32_t                RESERVED1[3];  /*!< Reserverd block, offset: 0x14 */
    volatile uint32_t       SIRC_CFG;      /*!< SIRC clock div configuration, offset: 0x20 */
    uint32_t                RESERVED2[3];  /*!< Reserverd block, offset: 0x24 */
    volatile uint32_t       FIRC_CFG;      /*!< FIRC clock div configuration, offset: 0x30 */
    uint32_t                RESERVED3[3];  /*!< Reserverd block, offset: 0x34 */
    volatile uint32_t       PLL_CFG;       /*!< PLL clock div configuration, offset: 0x40 */
    uint32_t                RESERVED4[15]; /*!< Reserverd block, offset: 0x44 */
    volatile uint32_t       LOCK;          /*!< SCG module lock/unlock register, offset: 0x80 */
    const volatile uint32_t LOCK_ST;       /*!< SCG unlock/lock flag, offset: 0x84 */
} ScgRegType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Gets the clk_trace(TRACE clock) divide ratio
 *
 * This function gets the current clk_trace(TRACE clock) divide ratio.
 * The source clock is clk_core.
 *
 * \param[in] obj : pointer to SCG register instance
 * \return clk_trace(TRACE clock) divide ratio
 *         - 0h : 1
 *         - 1h : 2
 *         - 2h : 3
 *         - 3h : 4
 *         - 4h : 5
 *         - 5h : 6
 *         - 6h : 7
 *         - 7h : 8
 */
__attribute__((always_inline)) static inline uint8_t ScgReg_GetCsrDivTrace(const ScgRegType *obj)
{
    return ((obj->CSR & SCG_CSR_DIV_TRACE_MASK) >> SCG_CSR_DIV_TRACE_SHIFT);
}

/*! \brief Sets the clk_trace(TRACE clock) divide ratio
 *
 * This function sets the clk_trace(TRACE clock) divide ratio.
 * The source clock is clk_core.
 *
 * \param[in] obj : pointer to SCG register instance
 * \param[in] value : the value of clk_trace(TRACE clock) divide ratio
 *                    - 0h : 1
 *                    - 1h : 2
 *                    - 2h : 3
 *                    - 3h : 4
 *                    - 4h : 5
 *                    - 5h : 6
 *                    - 6h : 7
 *                    - 7h : 8
 */
__attribute__((always_inline)) static inline void ScgReg_SetCsrDivTrace(ScgRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CSR;

    tmp &= ~SCG_CSR_DIV_TRACE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SCG_CSR_DIV_TRACE_SHIFT)) & SCG_CSR_DIV_TRACE_MASK);
    obj->CSR = tmp;
}

/*! \brief Gets the clk_apb(AIPS BUS Clock):Divide Ratio
 *
 * This function gets the current clk_apb(AIPS BUS Clock):Divide Ratio.
 * The source clock is clk_core and can be changed at anytime. 
 * This register should be configuraed properly before the core clock clk_core is switched to more higher frequency,
 * so the AIPS clock is always less or equal to max frequency 60M.
 *
 * \param[in] obj : pointer to SCG register instance
 * \return clk_apb(AIPS BUS Clock):Divide Ratio
 *         - 0000 : Divide-by-1
 *         - 0001 : Divide-by-2
 *         - 0010 : Divide-by-3
 *         - 0011 : Divide-by-4
 *         - 0100 : Divide-by-5
 *         - 0101 : Divide-by-6
 *         - 0110 : Divide-by-7
 *         - 0111 : Divide-by-8
 *         - 1000 : Divide-by-9
 *         - 1001 : Divide-by-10
 *         - 1010 : Divide-by-11
 *         - 1011 : Divide-by-12
 *         - 1100 : Divide-by-13
 *         - 1101 : Divide-by-14
 *         - 1110 : Divide-by-15
 *         - 1111 : Divide-by-16
The max frequency is 60M, so this bit should be configured properly.
 */
__attribute__((always_inline)) static inline uint8_t ScgReg_GetCsrDivApb(const ScgRegType *obj)
{
    return ((obj->CSR & SCG_CSR_DIV_APB_MASK) >> SCG_CSR_DIV_APB_SHIFT);
}

/*! \brief Sets the clk_apb(AIPS BUS Clock):Divide Ratio
 *
 * This function sets the clk_apb(AIPS BUS Clock):Divide Ratio.
 * The source clock is clk_core and can be changed at anytime. 
 * This register should be configuraed properly before the core clock clk_core is switched to more higher frequency,
 * so the AIPS clock is always less or equal to max frequency 60M.
 *
 * \param[in] obj : pointer to SCG register instance
 * \param[in] value : the value of clk_apb(AIPS BUS Clock):Divide Ratio
 *                    - 0000 : Divide-by-1
 *                    - 0001 : Divide-by-2
 *                    - 0010 : Divide-by-3
 *                    - 0011 : Divide-by-4
 *                    - 0100 : Divide-by-5
 *                    - 0101 : Divide-by-6
 *                    - 0110 : Divide-by-7
 *                    - 0111 : Divide-by-8
 *                    - 1000 : Divide-by-9
 *                    - 1001 : Divide-by-10
 *                    - 1010 : Divide-by-11
 *                    - 1011 : Divide-by-12
 *                    - 1100 : Divide-by-13
 *                    - 1101 : Divide-by-14
 *                    - 1110 : Divide-by-15
 *                    - 1111 : Divide-by-16
The max frequency is 60M, so this bit should be configured properly.
 */
__attribute__((always_inline)) static inline void ScgReg_SetCsrDivApb(ScgRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CSR;

    tmp &= ~SCG_CSR_DIV_APB_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SCG_CSR_DIV_APB_SHIFT)) & SCG_CSR_DIV_APB_MASK);
    obj->CSR = tmp;
}

/*! \brief Gets the clk_cnt_fls(flash Clock) Divide Ratio, source clock is clk_sys
 *
 * This function gets the current clk_cnt_fls(flash Clock) Divide Ratio, source clock is clk_sys.
 * This register is used for flash command.
 * Before flash command is excuted, this register should be configured to 8M and the clk_core should be more than 8M.
 *
 * \param[in] obj : pointer to SCG register instance
 * \return clk_cnt_fls(flash Clock) Divide Ratio, source clock is clk_core
 *         - 00000b : Divide-by-1
 *         - 00001b : Divide-by-2
 *         - 00010b : Divide-by-3
 *         - 00011b : Divide-by-4
 *         - 00100b : Divide-by-5
 *         - 00101b : Divide-by-6
 *         - 00110b : Divide-by-7
 *         - 00111b : Divide-by-8
 *         - 01000b : Divide-by-9
 *         - 01001b : Divide-by-10
 *         - 01010b : Divide-by-11
 *         - 01011b : Divide-by-12
 *         - 01100b : Divide-by-13
 *         - 01101b : Divide-by-14
 *         - 01110b : Divide-by-15
 *         - 01111b : Divide-by-16
 *         - 10000b : Divide-by-17
 *         - 10001b : Divide-by-18
 *         - 10010b : Divide-by-19
 *         - 10011b : Divide-by-20
 *         - 10100b : Divide-by-21
 */
__attribute__((always_inline)) static inline uint8_t ScgReg_GetCsrDivCntFls(const ScgRegType *obj)
{
    return ((obj->CSR & SCG_CSR_DIV_CNT_FLS_MASK) >> SCG_CSR_DIV_CNT_FLS_SHIFT);
}

/*! \brief Sets the clk_cnt_fls(flash Clock) Divide Ratio, source clock is clk_core
 *
 * This function gets the current clk_cnt_fls(flash Clock) Divide Ratio, source clock is clk_sys.
 * This register is used for flash command.
 * Before flash command is excuted, this register should be configured to 8M and the clk_core should be more than 8M.
 *
 * \param[in] obj : pointer to SCG register instance
 * \param[in] value : the value of clk_cnt_fls(flash Clock) Divide Ratio, source clock is clk_core
 *                    - 00000b : Divide-by-1
 *                    - 00001b : Divide-by-2
 *                    - 00010b : Divide-by-3
 *                    - 00011b : Divide-by-4
 *                    - 00100b : Divide-by-5
 *                    - 00101b : Divide-by-6
 *                    - 00110b : Divide-by-7
 *                    - 00111b : Divide-by-8
 *                    - 01000b : Divide-by-9
 *                    - 01001b : Divide-by-10
 *                    - 01010b : Divide-by-11
 *                    - 01011b : Divide-by-12
 *                    - 01100b : Divide-by-13
 *                    - 01101b : Divide-by-14
 *                    - 01110b : Divide-by-15
 *                    - 01111b : Divide-by-16
 *                    - 10000b : Divide-by-17
 *                    - 10001b : Divide-by-18
 *                    - 10010b : Divide-by-19
 *                    - 10011b : Divide-by-20
 *                    - 10100b : Divide-by-21
 */
__attribute__((always_inline)) static inline void ScgReg_SetCsrDivCntFls(ScgRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CSR;

    tmp &= ~SCG_CSR_DIV_CNT_FLS_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SCG_CSR_DIV_CNT_FLS_SHIFT)) & SCG_CSR_DIV_CNT_FLS_MASK);
    obj->CSR = tmp;
}

/*! \brief Gets the clk_pll_div2 clock enable
 *
 * This function gets the current clk_pll_div2 clock enable.
 *
 * \param[in] obj : pointer to SCG register instance
 * \return clk_pll_div2 clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t ScgReg_GetCkEnPllDiv2(const ScgRegType *obj)
{
    return ((obj->CKEN & SCG_CKEN_EN_PLL_DIV2_MASK) >> SCG_CKEN_EN_PLL_DIV2_SHIFT);
}

/*! \brief Sets the clk_pll_div2 clock enable
 *
 * This function sets the clk_pll_div2 clock enable.
 *
 * \param[in] obj : pointer to SCG register instance
 * \param[in] value : the value of clk_pll_div2 clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void ScgReg_SetCkEnPllDiv2(ScgRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CKEN;

    tmp &= ~SCG_CKEN_EN_PLL_DIV2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SCG_CKEN_EN_PLL_DIV2_SHIFT)) & SCG_CKEN_EN_PLL_DIV2_MASK);
    obj->CKEN = tmp;
}

/*! \brief Gets the clk_pll_div1 clock enable
 *
 * This function gets the current status of clk_pll_div1 clock enable.
 *
 * \param[in] obj : pointer to SCG register instance
 * \return clk_pll_div1 clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t ScgReg_GetCkEnPllDiv1(const ScgRegType *obj)
{
    return ((obj->CKEN & SCG_CKEN_EN_PLL_DIV1_MASK) >> SCG_CKEN_EN_PLL_DIV1_SHIFT);
}

/*! \brief Sets the clk_pll_div1 clock enable
 *
 * This function sets the clk_pll_div1 clock enable.
 *
 * \param[in] obj : pointer to SCG register instance
 * \param[in] value : the value of clk_pll_div1 clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void ScgReg_SetCkEnPllDiv1(ScgRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CKEN;

    tmp &= ~SCG_CKEN_EN_PLL_DIV1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SCG_CKEN_EN_PLL_DIV1_SHIFT)) & SCG_CKEN_EN_PLL_DIV1_MASK);
    obj->CKEN = tmp;
}

/*! \brief Gets the clk_firc_div2 clock enable
 *
 * This function gets the current clk_firc_div2 clock enable.
 *
 * \param[in] obj : pointer to SCG register instance
 * \return clk_firc_div2 clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t ScgReg_GetCkEnFircDiv2(const ScgRegType *obj)
{
    return ((obj->CKEN & SCG_CKEN_EN_FIRC_DIV2_MASK) >> SCG_CKEN_EN_FIRC_DIV2_SHIFT);
}

/*! \brief Sets the clk_firc_div2 clock enable
 *
 * This function sets the clk_firc_div2 clock enable.
 *
 * \param[in] obj : pointer to SCG register instance
 * \param[in] value : the value of clk_firc_div2 clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void ScgReg_SetCkEnFircDiv2(ScgRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CKEN;

    tmp &= ~SCG_CKEN_EN_FIRC_DIV2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SCG_CKEN_EN_FIRC_DIV2_SHIFT)) & SCG_CKEN_EN_FIRC_DIV2_MASK);
    obj->CKEN = tmp;
}

/*! \brief Gets the clk_firc_div1 clock enable
 *
 * This function gets the current clk_firc_div1 clock enable.
 *
 * \param[in] obj : pointer to SCG register instance
 * \return clk_firc_div1 clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t ScgReg_GetCkEnFircDiv1(const ScgRegType *obj)
{
    return ((obj->CKEN & SCG_CKEN_EN_FIRC_DIV1_MASK) >> SCG_CKEN_EN_FIRC_DIV1_SHIFT);
}

/*! \brief Sets the clk_firc_div1 clock enable
 *
 * This function sets the clk_firc_div1 clock enable.
 *
 * \param[in] obj : pointer to SCG register instance
 * \param[in] value : the value of clk_firc_div1 clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void ScgReg_SetCkEnFircDiv1(ScgRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CKEN;

    tmp &= ~SCG_CKEN_EN_FIRC_DIV1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SCG_CKEN_EN_FIRC_DIV1_SHIFT)) & SCG_CKEN_EN_FIRC_DIV1_MASK);
    obj->CKEN = tmp;
}

/*! \brief Gets the clk_sirc_div2 clock enable
 *
 * This function gets the current clk_sirc_div2 clock enable.
 *
 * \param[in] obj : pointer to SCG register instance
 * \return clk_sirc_div2 clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t ScgReg_GetCkEnSircDiv2(const ScgRegType *obj)
{
    return ((obj->CKEN & SCG_CKEN_EN_SIRC_DIV2_MASK) >> SCG_CKEN_EN_SIRC_DIV2_SHIFT);
}

/*! \brief Sets the clk_sirc_div2 clock enable
 *
 * This function sets the clk_sirc_div2 clock enable.
 *
 * \param[in] obj : pointer to SCG register instance
 * \param[in] value : the value of clk_sirc_div2 clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void ScgReg_SetCkEnSircDiv2(ScgRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CKEN;

    tmp &= ~SCG_CKEN_EN_SIRC_DIV2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SCG_CKEN_EN_SIRC_DIV2_SHIFT)) & SCG_CKEN_EN_SIRC_DIV2_MASK);
    obj->CKEN = tmp;
}

/*! \brief Gets the clk_sirc_div1 clock enable
 *
 * This function gets the current clk_sirc_div1 clock enable.
 *
 * \param[in] obj : pointer to SCG register instance
 * \return clk_sirc_div1 clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t ScgReg_GetCkEnSircDiv1(const ScgRegType *obj)
{
    return ((obj->CKEN & SCG_CKEN_EN_SIRC_DIV1_MASK) >> SCG_CKEN_EN_SIRC_DIV1_SHIFT);
}

/*! \brief Sets the clk_sirc_div1 clock enable
 *
 * This function sets the clk_sirc_div1 clock enable.
 *
 * \param[in] obj : pointer to SCG register instance
 * \param[in] value : the value of clk_sirc_div1 clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void ScgReg_SetCkEnSircDiv1(ScgRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CKEN;

    tmp &= ~SCG_CKEN_EN_SIRC_DIV1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SCG_CKEN_EN_SIRC_DIV1_SHIFT)) & SCG_CKEN_EN_SIRC_DIV1_MASK);
    obj->CKEN = tmp;
}

/*! \brief Gets the clk_sosc_div2 clock enable
 *
 * This function gets the current clk_sosc_div2 clock enable.
 *
 * \param[in] obj : pointer to SCG register instance
 * \return clk_sosc_div2 clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t ScgReg_GetCkEnSoscDiv2(const ScgRegType *obj)
{
    return ((obj->CKEN & SCG_CKEN_EN_SOSC_DIV2_MASK) >> SCG_CKEN_EN_SOSC_DIV2_SHIFT);
}

/*! \brief Sets the clk_sosc_div2 clock enable
 *
 * This function sets the clk_sosc_div2 clock enable.
 *
 * \param[in] obj : pointer to SCG register instance
 * \param[in] value : the value of clk_sosc_div2 clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void ScgReg_SetCkEnSoscDiv2(ScgRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CKEN;

    tmp &= ~SCG_CKEN_EN_SOSC_DIV2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SCG_CKEN_EN_SOSC_DIV2_SHIFT)) & SCG_CKEN_EN_SOSC_DIV2_MASK);
    obj->CKEN = tmp;
}

/*! \brief Gets the clk_sosc_div1 clock enable
 *
 * This function gets the current clk_sosc_div1 clock enable.
 *
 * \param[in] obj : pointer to SCG register instance
 * \return clk_sosc_div1 clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t ScgReg_GetCkEnSoscDiv1(const ScgRegType *obj)
{
    return ((obj->CKEN & SCG_CKEN_EN_SOSC_DIV1_MASK) >> SCG_CKEN_EN_SOSC_DIV1_SHIFT);
}

/*! \brief Sets the clk_sosc_div1 clock enable
 *
 * This function sets the clk_sosc_div1 clock enable.
 *
 * \param[in] obj : pointer to SCG register instance
 * \param[in] value : the value of clk_sosc_div1 clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void ScgReg_SetCkEnSoscDiv1(ScgRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CKEN;

    tmp &= ~SCG_CKEN_EN_SOSC_DIV1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SCG_CKEN_EN_SOSC_DIV1_SHIFT)) & SCG_CKEN_EN_SOSC_DIV1_MASK);
    obj->CKEN = tmp;
}

/*! \brief Gets the clock out enable
 *
 * This function gets the current clock out enable.
 *
 * \param[in] obj : pointer to SCG register instance
 * \return clock out enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t ScgReg_GetCkEnOut(const ScgRegType *obj)
{
    return ((obj->CKEN & SCG_CKEN_EN_OUT_MASK) >> SCG_CKEN_EN_OUT_SHIFT);
}

/*! \brief Sets the clock out enable
 *
 * This function sets the clock out enable.
 *
 * \param[in] obj : pointer to SCG register instance
 * \param[in] value : the value of clock out enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void ScgReg_SetCkEnOut(ScgRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CKEN;

    tmp &= ~SCG_CKEN_EN_OUT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SCG_CKEN_EN_OUT_SHIFT)) & SCG_CKEN_EN_OUT_MASK);
    obj->CKEN = tmp;
}

/*! \brief Gets the TRACE clock enable
 *
 * This function gets the current TRACE clock enable.
 *
 * \param[in] obj : pointer to SCG register instance
 * \return TRACE clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t ScgReg_GetCkEnTrace(const ScgRegType *obj)
{
    return ((obj->CKEN & SCG_CKEN_EN_TRACE_MASK) >> SCG_CKEN_EN_TRACE_SHIFT);
}

/*! \brief Sets the TRACE clock enable
 *
 * This function sets the TRACE clock enable.
 *
 * \param[in] obj : pointer to SCG register instance
 * \param[in] value : the value of TRACE clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void ScgReg_SetCkEnTrace(ScgRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CKEN;

    tmp &= ~SCG_CKEN_EN_TRACE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SCG_CKEN_EN_TRACE_SHIFT)) & SCG_CKEN_EN_TRACE_MASK);
    obj->CKEN = tmp;
}

/*! \brief Gets the clock out divide ratio
 *
 * This function gets the current clock out divide ratio.
 *
 * \note The max frequency is 24M, so this bit should be configured properly.
 *
 * \param[in] obj : pointer to SCG register instance
 * \return clock out divide ratio
 *         - 0b : 1
 *         - 1b : 2
 *         - 2h : 3
 *         - 3h : 4
 *         - 4h : 5
 *         - 5h : 6
 *         - 6h : 7
 *         - 7h : 8
 */
__attribute__((always_inline)) static inline uint8_t ScgReg_GetClkOutDiv(const ScgRegType *obj)
{
    return ((obj->CLKOUT & SCG_CLKOUT_DIV_MASK) >> SCG_CLKOUT_DIV_SHIFT);
}

/*! \brief Sets the clock out divide ratio
 *
 * This function sets the clock out divide ratio.
 *
 * \note The max frequency is 24M, so this bit should be configured properly.
 *
 * \param[in] obj : pointer to SCG register instance
 * \param[in] value : the value of clock out divide ratio
 *                    - 0b : 1
 *                    - 1b : 2
 *                    - 2h : 3
 *                    - 3h : 4
 *                    - 4h : 5
 *                    - 5h : 6
 *                    - 6h : 7
 *                    - 7h : 8
 */
__attribute__((always_inline)) static inline void ScgReg_SetClkOutDiv(ScgRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CLKOUT;

    tmp &= ~SCG_CLKOUT_DIV_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SCG_CLKOUT_DIV_SHIFT)) & SCG_CLKOUT_DIV_MASK);
    obj->CLKOUT = tmp;
}

/*! \brief Gets the clock out(to PAD) source
 *
 * This function gets the current clock out(to PAD) source.
 *
 * \param[in] obj : pointer to SCG register instance
 * \return clock out(to PAD) source
 *         - 0b : scg_out
 *         - 1b : clk_sosc_div2
 *         - 2h : clk_pll_div2
 *         - 3h : clk_sirc_div2
 *         - 4h : clk_lpo128
 *         - 5h : clk_lpo32
 *         - 6h : clk_lpo1
 *         - 7h : clk_rtc
 */
__attribute__((always_inline)) static inline uint8_t ScgReg_GetClkOutSrc(const ScgRegType *obj)
{
    return ((obj->CLKOUT & SCG_CLKOUT_SRC_MASK) >> SCG_CLKOUT_SRC_SHIFT);
}

/*! \brief Sets the clock out(to PAD) source
 *
 * This function sets the clock out(to PAD) source.
 *
 * \param[in] obj : pointer to SCG register instance
 * \param[in] value : the value of clock out(to PAD) source
 *                    - 0b : scg_out
 *                    - 1b : clk_sosc_div2
 *                    - 2h : clk_pll_div2
 *                    - 3h : clk_sirc_div2
 *                    - 4h : clk_lpo128
 *                    - 5h : clk_lpo32
 *                    - 6h : clk_lpo1
 *                    - 7h : clk_rtc
 */
__attribute__((always_inline)) static inline void ScgReg_SetClkOutSrc(ScgRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CLKOUT;

    tmp &= ~SCG_CLKOUT_SRC_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SCG_CLKOUT_SRC_SHIFT)) & SCG_CLKOUT_SRC_MASK);
    obj->CLKOUT = tmp;
}

/*! \brief Gets the scg clock out
 *
 * This function gets the current scg clock out.
 *
 * \param[in] obj : pointer to SCG register instance
 * \return scg clock out
 *         - 0b : clk_fls
 *         - 1b : clk_sosc
 *         - 2h : clk_sirc
 *         - 3h : clk_firc
 *         - 4h : clk_pll
 *         - 5h : clk_core
 *         - 6h : clk_apb
 *         - 7h : clk_firc_div2
 */
__attribute__((always_inline)) static inline uint8_t ScgReg_GetClkOutScg(const ScgRegType *obj)
{
    return ((obj->CLKOUT & SCG_CLKOUT_SCG_MASK) >> SCG_CLKOUT_SCG_SHIFT);
}

/*! \brief Sets the scg clock out
 *
 * This function sets the scg clock out.
 *
 * \param[in] obj : pointer to SCG register instance
 * \param[in] value : the value of scg clock out
 *                    - 0b : clk_fls
 *                    - 1b : clk_sosc
 *                    - 2h : clk_sirc
 *                    - 3h : clk_firc
 *                    - 4h : clk_pll
 *                    - 5h : clk_core
 *                    - 6h : clk_apb
 *                    - 7h : clk_firc_div2
 */
__attribute__((always_inline)) static inline void ScgReg_SetClkOutScg(ScgRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CLKOUT;

    tmp &= ~SCG_CLKOUT_SCG_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SCG_CLKOUT_SCG_SHIFT)) & SCG_CLKOUT_SCG_MASK);
    obj->CLKOUT = tmp;
}

/*! \brief Gets the SOSC_DIV2 clock diviation
 *
 * This function gets the current SOSC_DIV2 clock diviation.
 *
 * \param[in] obj : pointer to SCG register instance
 * \return SOSC_DIV2 clock diviation
 *         - 0b : Divide by 1
 *         - 1b : Divide by 2
 *         - 2h : Divide by 4
 *         - 3h : Divide by 8
 *         - 4h : Divide by 16
 *         - 5h : Divide by 32
 *         - 6h : Divide by 64
 *         - 7h : /
 */
__attribute__((always_inline)) static inline uint8_t ScgReg_GetSoscCfgDiv2(const ScgRegType *obj)
{
    return ((obj->SOSC_CFG & SCG_SOSC_CFG_DIV2_MASK) >> SCG_SOSC_CFG_DIV2_SHIFT);
}

/*! \brief Sets the SOSC_DIV2 clock diviation
 *
 * This function sets the SOSC_DIV2 clock diviation.
 *
 * \param[in] obj : pointer to SCG register instance
 * \param[in] value : the value of SOSC_DIV2 clock diviation
 *                    - 0b : Divide by 1
 *                    - 1b : Divide by 2
 *                    - 2h : Divide by 4
 *                    - 3h : Divide by 8
 *                    - 4h : Divide by 16
 *                    - 5h : Divide by 32
 *                    - 6h : Divide by 64
 *                    - 7h : /
 */
__attribute__((always_inline)) static inline void ScgReg_SetSoscCfgDiv2(ScgRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SOSC_CFG;

    tmp &= ~SCG_SOSC_CFG_DIV2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SCG_SOSC_CFG_DIV2_SHIFT)) & SCG_SOSC_CFG_DIV2_MASK);
    obj->SOSC_CFG = tmp;
}

/*! \brief Gets the SOSC_DIV1 clock diviation
 *
 * This function gets the current SOSC_DIV1 clock diviation.
 *
 * \param[in] obj : pointer to SCG register instance
 * \return SOSC_DIV1 clock diviation
 *         - 0b : Divide by 1
 *         - 1b : Divide by 2
 *         - 2h : Divide by 4
 *         - 3h : Divide by 8
 *         - 4h : Divide by 16
 *         - 5h : Divide by 32
 *         - 6h : Divide by 64
 *         - 7h : /
 */
__attribute__((always_inline)) static inline uint8_t ScgReg_GetSoscCfgDiv1(const ScgRegType *obj)
{
    return ((obj->SOSC_CFG & SCG_SOSC_CFG_DIV1_MASK) >> SCG_SOSC_CFG_DIV1_SHIFT);
}

/*! \brief Sets the SOSC_DIV1 clock diviation
 *
 * This function sets the SOSC_DIV1 clock diviation.
 *
 * \param[in] obj : pointer to SCG register instance
 * \param[in] value : the value of SOSC_DIV1 clock diviation
 *                    - 0b : Divide by 1
 *                    - 1b : Divide by 2
 *                    - 2h : Divide by 4
 *                    - 3h : Divide by 8
 *                    - 4h : Divide by 16
 *                    - 5h : Divide by 32
 *                    - 6h : Divide by 64
 *                    - 7h : /
 */
__attribute__((always_inline)) static inline void ScgReg_SetSoscCfgDiv1(ScgRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SOSC_CFG;

    tmp &= ~SCG_SOSC_CFG_DIV1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SCG_SOSC_CFG_DIV1_SHIFT)) & SCG_SOSC_CFG_DIV1_MASK);
    obj->SOSC_CFG = tmp;
}

/*! \brief Gets the SIRC_DIV2 clock diviation
 *
 * This function gets the current SIRC_DIV2 clock diviation.
 *
 * \param[in] obj : pointer to SCG register instance
 * \return SIRC_DIV2 clock diviation
 *         - 0b : Divide by 1
 *         - 1b : Divide by 2
 *         - 2h : Divide by 4
 *         - 3h : Divide by 8
 *         - 4h : Divide by 16
 *         - 5h : Divide by 32
 *         - 6h : Divide by 64
 *         - 7h : /
 */
__attribute__((always_inline)) static inline uint8_t ScgReg_GetSircCfgDiv2(const ScgRegType *obj)
{
    return ((obj->SIRC_CFG & SCG_SIRC_CFG_DIV2_MASK) >> SCG_SIRC_CFG_DIV2_SHIFT);
}

/*! \brief Sets the SIRC_DIV2 clock diviation
 *
 * This function sets the SIRC_DIV2 clock diviation.
 *
 * \param[in] obj : pointer to SCG register instance
 * \param[in] value : the value of SIRC_DIV2 clock diviation
 *                    - 0b : Divide by 1
 *                    - 1b : Divide by 2
 *                    - 2h : Divide by 4
 *                    - 3h : Divide by 8
 *                    - 4h : Divide by 16
 *                    - 5h : Divide by 32
 *                    - 6h : Divide by 64
 *                    - 7h : /
 */
__attribute__((always_inline)) static inline void ScgReg_SetSircCfgDiv2(ScgRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SIRC_CFG;

    tmp &= ~SCG_SIRC_CFG_DIV2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SCG_SIRC_CFG_DIV2_SHIFT)) & SCG_SIRC_CFG_DIV2_MASK);
    obj->SIRC_CFG = tmp;
}

/*! \brief Gets the SIRC_DIV1 clock diviation
 *
 * This function gets the current SIRC_DIV1 clock diviation.
 *
 * \param[in] obj : pointer to SCG register instance
 * \return SIRC_DIV1 clock diviation
 *         - 0b : Divide by 1
 *         - 1b : Divide by 2
 *         - 2h : Divide by 4
 *         - 3h : Divide by 8
 *         - 4h : Divide by 16
 *         - 5h : Divide by 32
 *         - 6h : Divide by 64
 *         - 7h : /
 */
__attribute__((always_inline)) static inline uint8_t ScgReg_GetSircCfgDiv1(const ScgRegType *obj)
{
    return ((obj->SIRC_CFG & SCG_SIRC_CFG_DIV1_MASK) >> SCG_SIRC_CFG_DIV1_SHIFT);
}

/*! \brief Sets the SIRC_DIV1 clock diviation
 *
 * This function sets the SIRC_DIV1 clock diviation.
 *
 * \param[in] obj : pointer to SCG register instance
 * \param[in] value : the value of SIRC_DIV1 clock diviation
 *                    - 0b : Divide by 1
 *                    - 1b : Divide by 2
 *                    - 2h : Divide by 4
 *                    - 3h : Divide by 8
 *                    - 4h : Divide by 16
 *                    - 5h : Divide by 32
 *                    - 6h : Divide by 64
 *                    - 7h : /
 */
__attribute__((always_inline)) static inline void ScgReg_SetSircCfgDiv1(ScgRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SIRC_CFG;

    tmp &= ~SCG_SIRC_CFG_DIV1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SCG_SIRC_CFG_DIV1_SHIFT)) & SCG_SIRC_CFG_DIV1_MASK);
    obj->SIRC_CFG = tmp;
}

/*! \brief Gets the FIRC_DIV2 clock diviation
 *
 * This function gets the current FIRC_DIV2 clock diviation.
 *
 * \param[in] obj : pointer to SCG register instance
 * \return FIRC_DIV2 clock diviation
 *         - 0b : Divide by 1
 *         - 1b : Divide by 2
 *         - 2h : Divide by 4
 *         - 3h : Divide by 8
 *         - 4h : Divide by 16
 *         - 5h : Divide by 32
 *         - 6h : Divide by 64
 *         - 7h : /
 */
__attribute__((always_inline)) static inline uint8_t ScgReg_GetFircCfgDiv2(const ScgRegType *obj)
{
    return ((obj->FIRC_CFG & SCG_FIRC_CFG_DIV2_MASK) >> SCG_FIRC_CFG_DIV2_SHIFT);
}

/*! \brief Sets the FIRC_DIV2 clock diviation
 *
 * This function sets the FIRC_DIV2 clock diviation.
 *
 * \param[in] obj : pointer to SCG register instance
 * \param[in] value : the value of FIRC_DIV2 clock diviation
 *                    - 0b : Divide by 1
 *                    - 1b : Divide by 2
 *                    - 2h : Divide by 4
 *                    - 3h : Divide by 8
 *                    - 4h : Divide by 16
 *                    - 5h : Divide by 32
 *                    - 6h : Divide by 64
 *                    - 7h : /
 */
__attribute__((always_inline)) static inline void ScgReg_SetFircCfgDiv2(ScgRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->FIRC_CFG;

    tmp &= ~SCG_FIRC_CFG_DIV2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SCG_FIRC_CFG_DIV2_SHIFT)) & SCG_FIRC_CFG_DIV2_MASK);
    obj->FIRC_CFG = tmp;
}

/*! \brief Gets the FIRC_DIV1 clock diviation
 *
 * This function gets the current FIRC_DIV1 clock diviation.
 *
 * \param[in] obj : pointer to SCG register instance
 * \return FIRC_DIV1 clock diviation
 *         - 0b : Divide by 1
 *         - 1b : Divide by 2
 *         - 2h : Divide by 4
 *         - 3h : Divide by 8
 *         - 4h : Divide by 16
 *         - 5h : Divide by 32
 *         - 6h : Divide by 64
 *         - 7h : /
 */
__attribute__((always_inline)) static inline uint8_t ScgReg_GetFircCfgDiv1(const ScgRegType *obj)
{
    return ((obj->FIRC_CFG & SCG_FIRC_CFG_DIV1_MASK) >> SCG_FIRC_CFG_DIV1_SHIFT);
}

/*! \brief Sets the FIRC_DIV1 clock diviation
 *
 * This function sets the FIRC_DIV1 clock diviation.
 *
 * \param[in] obj : pointer to SCG register instance
 * \param[in] value : the value of FIRC_DIV1 clock diviation
 *                    - 0b : Divide by 1
 *                    - 1b : Divide by 2
 *                    - 2h : Divide by 4
 *                    - 3h : Divide by 8
 *                    - 4h : Divide by 16
 *                    - 5h : Divide by 32
 *                    - 6h : Divide by 64
 *                    - 7h : /
 */
__attribute__((always_inline)) static inline void ScgReg_SetFircCfgDiv1(ScgRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->FIRC_CFG;

    tmp &= ~SCG_FIRC_CFG_DIV1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SCG_FIRC_CFG_DIV1_SHIFT)) & SCG_FIRC_CFG_DIV1_MASK);
    obj->FIRC_CFG = tmp;
}

/*! \brief Gets the PLL_DIV2 clock diviation
 *
 * This function gets the current PLL_DIV2 clock diviation.
 *
 * \param[in] obj : pointer to SCG register instance
 * \return PLL_DIV2 clock diviation
 *         - 0b : Divide by 1
 *         - 1b : Divide by 2
 *         - 2h : Divide by 4
 *         - 3h : Divide by 8
 *         - 4h : Divide by 16
 *         - 5h : Divide by 32
 *         - 6h : Divide by 64
 *         - 7h : /
 */
__attribute__((always_inline)) static inline uint8_t ScgReg_GetPllCfgDiv2(const ScgRegType *obj)
{
    return ((obj->PLL_CFG & SCG_PLL_CFG_DIV2_MASK) >> SCG_PLL_CFG_DIV2_SHIFT);
}

/*! \brief Sets the PLL_DIV2 clock diviation
 *
 * This function sets the PLL_DIV2 clock diviation.
 *
 * \param[in] obj : pointer to SCG register instance
 * \param[in] value : the value of PLL_DIV2 clock diviation
 *                    - 0b : Divide by 1
 *                    - 1b : Divide by 2
 *                    - 2h : Divide by 4
 *                    - 3h : Divide by 8
 *                    - 4h : Divide by 16
 *                    - 5h : Divide by 32
 *                    - 6h : Divide by 64
 *                    - 7h : /
 */
__attribute__((always_inline)) static inline void ScgReg_SetPllCfgDiv2(ScgRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PLL_CFG;

    tmp &= ~SCG_PLL_CFG_DIV2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SCG_PLL_CFG_DIV2_SHIFT)) & SCG_PLL_CFG_DIV2_MASK);
    obj->PLL_CFG = tmp;
}

/*! \brief Gets the PLL_DIV2 clock diviation
 *
 * This function gets the current PLL_DIV2 clock diviation.
 *
 * \param[in] obj : pointer to SCG register instance
 * \return PLL_DIV2 clock diviation
 *         - 0b : Divide by 1
 *         - 1b : Divide by 2
 *         - 2h : Divide by 4
 *         - 3h : Divide by 8
 *         - 4h : Divide by 16
 *         - 5h : Divide by 32
 *         - 6h : Divide by 64
 *         - 7h : /
 */
__attribute__((always_inline)) static inline uint8_t ScgReg_GetPllCfgDiv1(const ScgRegType *obj)
{
    return ((obj->PLL_CFG & SCG_PLL_CFG_DIV1_MASK) >> SCG_PLL_CFG_DIV1_SHIFT);
}

/*! \brief Sets the PLL_DIV2 clock diviation
 *
 * This function sets the PLL_DIV2 clock diviation.
 *
 * \param[in] obj : pointer to SCG register instance
 * \param[in] value : the value of PLL_DIV2 clock diviation
 *                    - 0b : Divide by 1
 *                    - 1b : Divide by 2
 *                    - 2h : Divide by 4
 *                    - 3h : Divide by 8
 *                    - 4h : Divide by 16
 *                    - 5h : Divide by 32
 *                    - 6h : Divide by 64
 *                    - 7h : /
 */
__attribute__((always_inline)) static inline void ScgReg_SetPllCfgDiv1(ScgRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PLL_CFG;

    tmp &= ~SCG_PLL_CFG_DIV1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SCG_PLL_CFG_DIV1_SHIFT)) & SCG_PLL_CFG_DIV1_MASK);
    obj->PLL_CFG = tmp;
}

/*! \brief Sets the SCG UNLOCK KEY
 *
 * This function sets the SCG UNLOCK KEY.
 * Registers in SCG module is locked by default.
 * Before writing registers in scg, write unlock key to this register.
 *
 * \param[in] obj : pointer to SCG register instance
 * \param[in] value : the value of SCG UNLOCK KEY
 *                    - 5343_6D65h : unlock
 *                    - others : lock
 */
__attribute__((always_inline)) static inline void ScgReg_SetLockKey(ScgRegType *obj, uint32_t value)
{
    obj->LOCK = value;
}

/*! \brief Gets the SCG register configuration lock status
 *
 * This function gets the current SCG register configuration lock status.
 *
 * \param[in] obj : pointer to SCG register instance
 * \return SCG register configuration lock status
 *         - 0b : unlock
 *         - 1b : lock
 */
__attribute__((always_inline)) static inline uint8_t ScgReg_GetLockStLock(const ScgRegType *obj)
{
    return ((obj->LOCK_ST & SCG_LOCK_ST_LOCK_MASK) >> SCG_LOCK_ST_LOCK_SHIFT);
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _SCG_REG_H_ */
