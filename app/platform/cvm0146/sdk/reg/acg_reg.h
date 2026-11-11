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

#ifndef _ACG_REG_H_
#define _ACG_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the ACG Registers
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

/* OSC Bit Fields */
#define ACG_OSC_EXT_MASK       (0x10u)
#define ACG_OSC_EXT_SHIFT      (4u)
#define ACG_OSC_EXT_WIDTH      (1u)
#define ACG_OSC_RANGE_MASK     (0x0Cu)
#define ACG_OSC_RANGE_SHIFT    (2u)
#define ACG_OSC_RANGE_WIDTH    (2u)

/* PLL Bit Fields */
#define ACG_PLL_FBKSEL_MASK    (0x10000u)
#define ACG_PLL_FBKSEL_SHIFT   (16u)
#define ACG_PLL_FBKSEL_WIDTH   (1u)
#define ACG_PLL_M_MASK         (0x7F00u)
#define ACG_PLL_M_SHIFT        (8u)
#define ACG_PLL_M_WIDTH        (7u)
#define ACG_PLL_POSDIV_MASK    (0x70u)
#define ACG_PLL_POSDIV_SHIFT   (4u)
#define ACG_PLL_POSDIV_WIDTH   (3u)
#define ACG_PLL_PREDIV_MASK    (0x0Cu)
#define ACG_PLL_PREDIV_SHIFT   (2u)
#define ACG_PLL_PREDIV_WIDTH   (2u)
#define ACG_PLL_CLKIN_MASK     (0x03u)
#define ACG_PLL_CLKIN_SHIFT    (0u)
#define ACG_PLL_CLKIN_WIDTH    (2u)

/* EN Bit Fields */
#define ACG_EN_PLL_MASK        (0x08u)
#define ACG_EN_PLL_SHIFT       (3u)
#define ACG_EN_PLL_WIDTH       (1u)
#define ACG_EN_SOSC_MASK       (0x04u)
#define ACG_EN_SOSC_SHIFT      (2u)
#define ACG_EN_SOSC_WIDTH      (1u)
#define ACG_EN_FIRC_MASK       (0x02u)
#define ACG_EN_FIRC_SHIFT      (1u)
#define ACG_EN_FIRC_WIDTH      (1u)
#define ACG_EN_SIRC_MASK       (0x01u)
#define ACG_EN_SIRC_SHIFT      (0u)
#define ACG_EN_SIRC_WIDTH      (1u)

/* ST Bit Fields */
#define ACG_ST_SYS_ST_MASK     (0x30u)
#define ACG_ST_SYS_ST_SHIFT    (4u)
#define ACG_ST_SYS_ST_WIDTH    (2u)
#define ACG_ST_PLL_LOCK_MASK   (0x08u)
#define ACG_ST_PLL_LOCK_SHIFT  (3u)
#define ACG_ST_PLL_LOCK_WIDTH  (1u)
#define ACG_ST_SOSC_RDY_MASK   (0x04u)
#define ACG_ST_SOSC_RDY_SHIFT  (2u)
#define ACG_ST_SOSC_RDY_WIDTH  (1u)
#define ACG_ST_FIRC_RDY_MASK   (0x02u)
#define ACG_ST_FIRC_RDY_SHIFT  (1u)
#define ACG_ST_FIRC_RDY_WIDTH  (1u)
#define ACG_ST_SIRC_RDY_MASK   (0x01u)
#define ACG_ST_SIRC_RDY_SHIFT  (0u)
#define ACG_ST_SIRC_RDY_WIDTH  (1u)

/* SYS Bit Fields */
#define ACG_SYS_DIV_CORE_MASK  (0xF0u)
#define ACG_SYS_DIV_CORE_SHIFT (4u)
#define ACG_SYS_DIV_CORE_WIDTH (4u)
#define ACG_SYS_SRC_SYS_MASK   (0x03u)
#define ACG_SYS_SRC_SYS_SHIFT  (0u)
#define ACG_SYS_SRC_SYS_WIDTH  (2u)

/* LOCK Bit Fields */
#define ACG_LOCK_KEY_MASK      (0xFFFFFFFFu)
#define ACG_LOCK_KEY_SHIFT     (0u)
#define ACG_LOCK_KEY_WIDTH     (32u)

/* LOCK_ST Bit Fields */
#define ACG_LOCK_ST_LOCK_MASK  (0x01u)
#define ACG_LOCK_ST_LOCK_SHIFT (0u)
#define ACG_LOCK_ST_LOCK_WIDTH (1u)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief The definition of ACG registers
 */
typedef struct _AcgRegType_
{
    volatile uint32_t       OSC;           /*!< Clock source control register 1, offset: 0x00 */
    volatile uint32_t       PLL;           /*!< Clock source control register 2, offset: 0x04 */
    volatile uint32_t       EN;            /*!< Clock source enable register, offset: 0x08 */
    const volatile uint32_t ST;            /*!< Clock status register, offset: 0x0C */
    volatile uint32_t       SYS;           /*!< System clock register, offset: 0x10 */
    uint32_t                RESERVED0[27]; /*!< Reserverd block, offset: 0x14 */
    volatile uint32_t       LOCK;          /*!< ACG lock/unlock register, offset: 0x80 */
    const volatile uint32_t LOCK_ST;       /*!< ACG unlock/lock flag, offset: 0x84 */
} AcgRegType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Gets the External clock mode enable
 *
 * This function gets the current External clock mode enable.
 * External clock input through XIN pin enable
 * The register can only be written when SOSC clock is disabled, otherwise new configuration is ignored and bus error generated.
 *
 * \param[in] obj : pointer to ACG register instance
 * \return External clock mode enable
 *         - 1b : Enable
 *         - 0b : Disable
 */
__attribute__((always_inline)) static inline uint8_t AcgReg_GetOscExt(const AcgRegType *obj)
{
    return ((obj->OSC & ACG_OSC_EXT_MASK) >> ACG_OSC_EXT_SHIFT);
}

/*! \brief Sets the External clock mode enable
 *
 * This function sets the External clock mode enable.
 * External clock input through XIN pin enable
 * The register can only be written when SOSC clock is disabled, otherwise new configuration is ignored and bus error generated.
 *
 * \param[in] obj : pointer to ACG register instance
 * \param[in] value : the value of External clock mode enable
 *                    - 1b : Enable
 *                    - 0b : Disable
 */
__attribute__((always_inline)) static inline void AcgReg_SetOscExt(AcgRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->OSC;

    tmp &= ~ACG_OSC_EXT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ACG_OSC_EXT_SHIFT)) & ACG_OSC_EXT_MASK);
    obj->OSC = tmp;
}

/*! \brief Gets the SOSC frequency range select
 *
 * This function gets the current SOSC frequency range select.
 * The register can only be written when SOSC clock is disabled,otherwise new configuration is ignored and bus error will be generated.
 *
 * \param[in] obj : pointer to ACG register instance
 * \return SOSC frequency range select
 *         - 00b : Low frequency range(4M);
 *         - 01b : Medium frequency range(4M~8M)
 *         - 10b : Medium frequency range(8M~24M)
 *         - 11b : High frequency range(24M~40M)
 */
__attribute__((always_inline)) static inline uint8_t AcgReg_GetOscRange(const AcgRegType *obj)
{
    return ((obj->OSC & ACG_OSC_RANGE_MASK) >> ACG_OSC_RANGE_SHIFT);
}

/*! \brief Sets the SOSC frequency range select
 *
 * This function sets the SOSC frequency range select.
 * The register can only be written when SOSC clock is disabled,otherwise new configuration is ignored and bus error will be generated.
 *
 * \param[in] obj : pointer to ACG register instance
 * \param[in] value : the value of SOSC frequency range select
 *                    - 00b : Low frequency range(4M);
 *                    - 01b : Medium frequency range(4M~8M)
 *                    - 10b : Medium frequency range(8M~24M)
 *                    - 11b : High frequency range(24M~40M)
 */
__attribute__((always_inline)) static inline void AcgReg_SetOscRange(AcgRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->OSC;

    tmp &= ~ACG_OSC_RANGE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ACG_OSC_RANGE_SHIFT)) & ACG_OSC_RANGE_MASK);
    obj->OSC = tmp;
}

/*! \brief Gets the PLL Feedback clock divider pre-scaler
 *
 * This function gets the current PLL Feedback clock divider pre-scaler.
 *
 * \param[in] obj : pointer to ACG register instance
 * \return PLL Feedback clock divider pre-scaler
 *         - 0b : 1
 *         - 1b : 2
 */
__attribute__((always_inline)) static inline uint8_t AcgReg_GetPllFbkSel(const AcgRegType *obj)
{
    return ((obj->PLL & ACG_PLL_FBKSEL_MASK) >> ACG_PLL_FBKSEL_SHIFT);
}

/*! \brief Sets the PLL Feedback clock divider pre-scaler
 *
 * This function sets the PLL Feedback clock divider pre-scaler.
 *
 * \param[in] obj : pointer to ACG register instance
 * \param[in] value : the value of PLL Feedback clock divider pre-scaler
 *                    - 0b : 1
 *                    - 1b : 2
 */
__attribute__((always_inline)) static inline void AcgReg_SetPllFbkSel(AcgRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PLL;

    tmp &= ~ACG_PLL_FBKSEL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ACG_PLL_FBKSEL_SHIFT)) & ACG_PLL_FBKSEL_MASK);
    obj->PLL = tmp;
}

/*! \brief Gets the PLL feedback divider setting
 *
 * This function gets the current PLL feedback divider setting.
 *
 * \param[in] obj : pointer to ACG register instance
 * \return PLL feedback divider setting
 *         - 1h : 1
 *         - 2h : 2
 *            .
 *            .
 *            .
 *         - 7Fh : 127
 *         - 0h : 128
 */
__attribute__((always_inline)) static inline uint8_t AcgReg_GetPllM(const AcgRegType *obj)
{
    return ((obj->PLL & ACG_PLL_M_MASK) >> ACG_PLL_M_SHIFT);
}

/*! \brief Sets the PLL feedback divider setting
 *
 * This function sets the PLL feedback divider setting.
 *
 * \param[in] obj : pointer to ACG register instance
 * \param[in] value : the value of PLL feedback divider setting
 *                    - 1h : 1
 *                    - 2h : 2
 *                       .
 *                       .
 *                       .
 *                    - 7Fh : 127
 *                    - 0h : 128
 */
__attribute__((always_inline)) static inline void AcgReg_SetPllM(AcgRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PLL;

    tmp &= ~ACG_PLL_M_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ACG_PLL_M_SHIFT)) & ACG_PLL_M_MASK);
    obj->PLL = tmp;
}

/*! \brief Gets the PLL post-divider setting
 *
 * This function gets the current PLL post-divider setting.
 *
 * \param[in] obj : pointer to ACG register instance
 * \return PLL post-divider setting
 *         - 000b : 8
 *         - 001b : 1
 *         - 010b : 2
 *         - 011b : 3
 *            .
 *            .
 *            .
 *         - 111b : 7
 */
__attribute__((always_inline)) static inline uint8_t AcgReg_GetPllPosDiv(const AcgRegType *obj)
{
    return ((obj->PLL & ACG_PLL_POSDIV_MASK) >> ACG_PLL_POSDIV_SHIFT);
}

/*! \brief Sets the PLL post-divider setting
 *
 * This function sets the PLL post-divider setting.
 *
 * \param[in] obj : pointer to ACG register instance
 * \param[in] value : the value of PLL post-divider setting
 *                    - 000b : 8
 *                    - 001b : 1
 *                    - 010b : 2
 *                    - 011b : 3
 *                       .
 *                       .
 *                       .
 *                    - 111b : 7
 */
__attribute__((always_inline)) static inline void AcgReg_SetPllPosDiv(AcgRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PLL;

    tmp &= ~ACG_PLL_POSDIV_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ACG_PLL_POSDIV_SHIFT)) & ACG_PLL_POSDIV_MASK);
    obj->PLL = tmp;
}

/*! \brief Gets the PLL pre-divider setting
 *
 * This function gets the current PLL pre-divider setting.
 *
 * \param[in] obj : pointer to ACG register instance
 * \return PLL pre-divider setting
 *         - 00b : /1
 *         - 01b : /2
 *         - 10b : /4
 *         - 11b : /8
 */
__attribute__((always_inline)) static inline uint8_t AcgReg_GetPllPreDiv(const AcgRegType *obj)
{
    return ((obj->PLL & ACG_PLL_PREDIV_MASK) >> ACG_PLL_PREDIV_SHIFT);
}

/*! \brief Sets the PLL pre-divider setting
 *
 * This function sets the PLL pre-divider setting.
 *
 * \param[in] obj : pointer to ACG register instance
 * \param[in] value : the value of PLL pre-divider setting
 *                    - 00b : /1
 *                    - 01b : /2
 *                    - 10b : /4
 *                    - 11b : /8
 */
__attribute__((always_inline)) static inline void AcgReg_SetPllPreDiv(AcgRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PLL;

    tmp &= ~ACG_PLL_PREDIV_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ACG_PLL_PREDIV_SHIFT)) & ACG_PLL_PREDIV_MASK);
    obj->PLL = tmp;
}

/*! \brief Gets the PLL input clock source
 *
 * This function gets the current PLL input clock source.
 *
 * \param[in] obj : pointer to ACG register instance
 * \return PLL input clock source
 *         - 00b : FIRC clock as source;
 *         - 01b : SIRC clock as source;
 *         - 10b : SOSC clock as source;
 *         - 11b : Reversed;
 */
__attribute__((always_inline)) static inline uint8_t AcgReg_GetPllClkIn(const AcgRegType *obj)
{
    return ((obj->PLL & ACG_PLL_CLKIN_MASK) >> ACG_PLL_CLKIN_SHIFT);
}

/*! \brief Sets the PLL input clock source
 *
 * This function sets the PLL input clock source.
 *
 * \param[in] obj : pointer to ACG register instance
 * \param[in] value : the value of PLL input clock source
 *                    - 00b : FIRC clock as source;
 *                    - 01b : SIRC clock as source;
 *                    - 10b : SOSC clock as source;
 *                    - 11b : Reversed;
 */
__attribute__((always_inline)) static inline void AcgReg_SetPllClkIn(AcgRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PLL;

    tmp &= ~ACG_PLL_CLKIN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ACG_PLL_CLKIN_SHIFT)) & ACG_PLL_CLKIN_MASK);
    obj->PLL = tmp;
}

/*! \brief Gets the PLL enable control
 *
 * This function gets the current PLL enable control.
 *
 * \param[in] obj : pointer to ACG register instance
 * \return PLL enable control
 *         - 0b : Disable
 *         - 1b : Enable
 */
__attribute__((always_inline)) static inline uint8_t AcgReg_GetEnPll(const AcgRegType *obj)
{
    return ((obj->EN & ACG_EN_PLL_MASK) >> ACG_EN_PLL_SHIFT);
}

/*! \brief Sets the PLL enable control
 *
 * This function sets the PLL enable control.
 *
 * \param[in] obj : pointer to ACG register instance
 * \param[in] value : the value of PLL enable control
 *                    - 0b : Disable
 *                    - 1b : Enable
 */
__attribute__((always_inline)) static inline void AcgReg_SetEnPll(AcgRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->EN;

    tmp &= ~ACG_EN_PLL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ACG_EN_PLL_SHIFT)) & ACG_EN_PLL_MASK);
    obj->EN = tmp;
}

/*! \brief Gets the System oscillator (crystal osc) enable control
 *
 * This function gets the current System oscillator (crystal osc) enable control.
 *
 * \param[in] obj : pointer to ACG register instance
 * \return System oscillator (crystal osc) enable control
 *         - 0b : Disable
 *         - 1b : Enable
 */
__attribute__((always_inline)) static inline uint8_t AcgReg_GetEnSosc(const AcgRegType *obj)
{
    return ((obj->EN & ACG_EN_SOSC_MASK) >> ACG_EN_SOSC_SHIFT);
}

/*! \brief Sets the System oscillator (crystal osc) enable control
 *
 * This function sets the System oscillator (crystal osc) enable control.
 *
 * \param[in] obj : pointer to ACG register instance
 * \param[in] value : the value of System oscillator (crystal osc) enable control
 *                    - 0b : Disable
 *                    - 1b : Enable
 */
__attribute__((always_inline)) static inline void AcgReg_SetEnSosc(AcgRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->EN;

    tmp &= ~ACG_EN_SOSC_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ACG_EN_SOSC_SHIFT)) & ACG_EN_SOSC_MASK);
    obj->EN = tmp;
}

/*! \brief Gets the Fast internal reference clock enable control
 *
 * This function gets the current Fast internal reference clock enable control.
 *
 * \param[in] obj : pointer to ACG register instance
 * \return Fast internal reference clock enable control
 *         - 0b : Disable
 *         - 1b : Enable
 */
__attribute__((always_inline)) static inline uint8_t AcgReg_GetEnFirc(const AcgRegType *obj)
{
    return ((obj->EN & ACG_EN_FIRC_MASK) >> ACG_EN_FIRC_SHIFT);
}

/*! \brief Sets the Fast internal reference clock enable control
 *
 * This function sets the Fast internal reference clock enable control.
 *
 * \param[in] obj : pointer to ACG register instance
 * \param[in] value : the value of Fast internal reference clock enable control
 *                    - 0b : Disable
 *                    - 1b : Enable
 */
__attribute__((always_inline)) static inline void AcgReg_SetEnFirc(AcgRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->EN;

    tmp &= ~ACG_EN_FIRC_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ACG_EN_FIRC_SHIFT)) & ACG_EN_FIRC_MASK);
    obj->EN = tmp;
}

/*! \brief Gets the Slow internal reference clock enable control
 *
 * This function gets the current Slow internal reference clock enable control.
 *
 * \param[in] obj : pointer to ACG register instance
 * \return Slow internal reference clock enable control
 *         - 0b : Disable
 *         - 1b : Enable
 */
__attribute__((always_inline)) static inline uint8_t AcgReg_GetEnSirc(const AcgRegType *obj)
{
    return ((obj->EN & ACG_EN_SIRC_MASK) >> ACG_EN_SIRC_SHIFT);
}

/*! \brief Sets the Slow internal reference clock enable control
 *
 * This function sets the Slow internal reference clock enable control.
 *
 * \param[in] obj : pointer to ACG register instance
 * \param[in] value : the value of Slow internal reference clock enable control
 *                    - 0b : Disable
 *                    - 1b : Enable
 */
__attribute__((always_inline)) static inline void AcgReg_SetEnSirc(AcgRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->EN;

    tmp &= ~ACG_EN_SIRC_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ACG_EN_SIRC_SHIFT)) & ACG_EN_SIRC_MASK);
    obj->EN = tmp;
}

/*! \brief Gets the system clock(clk_sys) source status
 *
 * This function gets the current system clock(clk_sys) source status.
 *
 * \param[in] obj : pointer to ACG register instance
 * \return system clock(clk_sys) source status
 *         - 0h : clk_firc
 *         - 1h : clk_sosc
 *         - 2h : clk_pll
 *         - 3h : clk_sirc
 */
__attribute__((always_inline)) static inline uint8_t AcgReg_GetStSysSt(const AcgRegType *obj)
{
    return ((obj->ST & ACG_ST_SYS_ST_MASK) >> ACG_ST_SYS_ST_SHIFT);
}

/*! \brief Gets the PLL lock state
 *
 * This function gets the current PLL lock state.
 *
 * \param[in] obj : pointer to ACG register instance
 * \return PLL lock state
 *         - 0b : Not lock state
 *         - 1b : Lock state
 */
__attribute__((always_inline)) static inline uint8_t AcgReg_GetStPllLock(const AcgRegType *obj)
{
    return ((obj->ST & ACG_ST_PLL_LOCK_MASK) >> ACG_ST_PLL_LOCK_SHIFT);
}

/*! \brief Gets the Sytem oscillator clock ready flag
 *
 * This function gets the current Sytem oscillator clock ready flag.
 * If use external, this flag no useful.
 *
 * \param[in] obj : pointer to ACG register instance
 * \return Sytem oscillator clock ready flag
 *         - 0b : not ready
 *         - 1b : ready
 */
__attribute__((always_inline)) static inline uint8_t AcgReg_GetStSoscRdy(const AcgRegType *obj)
{
    return ((obj->ST & ACG_ST_SOSC_RDY_MASK) >> ACG_ST_SOSC_RDY_SHIFT);
}

/*! \brief Gets the FIRC 48M clock ready flag
 *
 * This function gets the current FIRC 48M clock ready flag.
 *
 * \param[in] obj : pointer to ACG register instance
 * \return FIRC 48M clock ready flag
 *         - 0b : not ready
 *         - 1b : ready
 */
__attribute__((always_inline)) static inline uint8_t AcgReg_GetStFircRdy(const AcgRegType *obj)
{
    return ((obj->ST & ACG_ST_FIRC_RDY_MASK) >> ACG_ST_FIRC_RDY_SHIFT);
}

/*! \brief Gets the SIRC clock ready flag
 *
 * This function gets the current SIRC clock ready flag.
 *
 * \param[in] obj : pointer to ACG register instance
 * \return SIRC clock ready flag
 *         - 0b : not ready
 *         - 1b : ready
 */
__attribute__((always_inline)) static inline uint8_t AcgReg_GetStSircRdy(const AcgRegType *obj)
{
    return ((obj->ST & ACG_ST_SIRC_RDY_MASK) >> ACG_ST_SIRC_RDY_SHIFT);
}

/*! \brief Gets the clk_core(Core and AHB BUS Clock):Divide Ratio
 *
 * This function gets the current clk_core(Core and AHB BUS Clock):Divide Ratio.
 * The clock source is clk_sys.
 *
 * \note The mininual frequency is 8M and max frequency is 120M.
 *
 * \param[in] obj : pointer to ACG register instance
 * \return clk_core(Core and AHB BUS Clock):Divide Ratio
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
 */
__attribute__((always_inline)) static inline uint8_t AcgReg_GetSysDivCore(const AcgRegType *obj)
{
    return ((obj->SYS & ACG_SYS_DIV_CORE_MASK) >> ACG_SYS_DIV_CORE_SHIFT);
}

/*! \brief Sets the clk_core(Core and AHB BUS Clock):Divide Ratio
 *
 * This function sets the clk_core(Core and AHB BUS Clock):Divide Ratio.
 * The clock source is clk_sys.
 *
 * \note The mininual frequency is 8M and max frequency is 120M.
 *
 * \param[in] obj : pointer to ACG register instance
 * \param[in] value : the value of clk_core(Core and AHB BUS Clock):Divide Ratio
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
 */
__attribute__((always_inline)) static inline void AcgReg_SetSysDivCore(AcgRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SYS;

    tmp &= ~ACG_SYS_DIV_CORE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ACG_SYS_DIV_CORE_SHIFT)) & ACG_SYS_DIV_CORE_MASK);
    obj->SYS = tmp;
}

/*! \brief Gets the System Clock(clk_sys) source select
 *
 * This function gets the current System Clock(clk_sys) source select.
 *
 * \param[in] obj : pointer to ACG register instance
 * \return System Clock(clk_sys) source select
 *         - 0h : clk_firc
 *         - 1h : clk_sosc
 *         - 2h : clk_pll
 *         - 3h : clk_sirc
 */
__attribute__((always_inline)) static inline uint8_t AcgReg_GetSysSrcSys(const AcgRegType *obj)
{
    return ((obj->SYS & ACG_SYS_SRC_SYS_MASK) >> ACG_SYS_SRC_SYS_SHIFT);
}

/*! \brief Sets the System Clock(clk_sys) source select
 *
 * This function sets the System Clock(clk_sys) source select.
 *
 * \param[in] obj : pointer to ACG register instance
 * \param[in] value : the value of System Clock(clk_sys) source select
 *                    - 0h : clk_firc
 *                    - 1h : clk_sosc
 *                    - 2h : clk_pll
 *                    - 3h : clk_sirc
 */
__attribute__((always_inline)) static inline void AcgReg_SetSysSrcSys(AcgRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SYS;

    tmp &= ~ACG_SYS_SRC_SYS_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ACG_SYS_SRC_SYS_SHIFT)) & ACG_SYS_SRC_SYS_MASK);
    obj->SYS = tmp;
}

/*! \brief Sets the ACG unlock key
 *
 * This function sets the ACG unlock key.
 * The RST/SCG/PCC registers in ALON power domain is locked by default.
 * Before writing registers, write unlock key to this register.
 *
 * \param[in] obj : pointer to ACG register instance
 * \param[in] value : the value of ACG unlock key
 *                    - FA86_23E4h : unlock
 *                    - other : lock
 */
__attribute__((always_inline)) static inline void AcgReg_SetLockKey(AcgRegType *obj, uint32_t value)
{
    obj->LOCK = value;
}

/*! \brief Gets the ACG register lock flag
 *
 * This function gets the current ACG register lock flag.
 * Registers in ACG is locked by default. Before writing registers in rcm, write unlock key .
 *
 * \param[in] obj : pointer to ACG register instance
 * \return ACG register lock flag
 *         - 0b : unlock
 *         - 1b : lock
 */
__attribute__((always_inline)) static inline uint8_t AcgReg_GetLockStLock(const AcgRegType *obj)
{
    return ((obj->LOCK_ST & ACG_LOCK_ST_LOCK_MASK) >> ACG_LOCK_ST_LOCK_SHIFT);
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _ACG_REG_H_ */
