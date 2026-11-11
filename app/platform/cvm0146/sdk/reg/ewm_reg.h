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

#ifndef _EWM_REG_H_
#define _EWM_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the EWM (External Watchdog Monitor) Registers
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

/* CTRL Bit Fields */
#define EWM_CTRL_INTEN_MASK            (0x08u)
#define EWM_CTRL_INTEN_SHIFT           (3u)
#define EWM_CTRL_INTEN_WIDTH           (1u)
#define EWM_CTRL_INEN_MASK             (0x04u)
#define EWM_CTRL_INEN_SHIFT            (2u)
#define EWM_CTRL_INEN_WIDTH            (1u)
#define EWM_CTRL_ASSIN_MASK            (0x02u)
#define EWM_CTRL_ASSIN_SHIFT           (1u)
#define EWM_CTRL_ASSIN_WIDTH           (1u)
#define EWM_CTRL_EWMEN_MASK            (0x01u)
#define EWM_CTRL_EWMEN_SHIFT           (0u)
#define EWM_CTRL_EWMEN_WIDTH           (1u)

/* SERV Bit Fields */
#define EWM_SERV_SERVICE_MASK          (0xFFFFu)
#define EWM_SERV_SERVICE_SHIFT         (0u)
#define EWM_SERV_SERVICE_WIDTH         (16u)

/* CMPL Bit Fields */
#define EWM_CMPL_COMPAREL_MASK         (0xFFu)
#define EWM_CMPL_COMPAREL_SHIFT        (0u)
#define EWM_CMPL_COMPAREL_WIDTH        (8u)

/* CMPH Bit Fields */
#define EWM_CMPH_COMPAREH_MASK         (0xFFu)
#define EWM_CMPH_COMPAREH_SHIFT        (0u)
#define EWM_CMPH_COMPAREH_WIDTH        (8u)

/* CLKPRESCALER Bit Fields */
#define EWM_CLKPRESCALER_CLK_DIV_MASK  (0xFFu)
#define EWM_CLKPRESCALER_CLK_DIV_SHIFT (0u)
#define EWM_CLKPRESCALER_CLK_DIV_WIDTH (8u)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief The definition of EWM registers
 */
typedef struct _EwmRegType_
{
    volatile uint8_t  CTRL;         /*!< config register, offset: 0x0 */
    uint8_t           RESERVED0[3]; /*!< reserved */
    volatile uint16_t SERV;         /*!< refresh register, offset: 0x4 */
    uint8_t           RESERVED1[2]; /*!< reserved */
    volatile uint8_t  CMPL;         /*!< compare value low 8bits register, offset: 0x8 */
    uint8_t           RESERVED2[3]; /*!< reserved */
    volatile uint8_t  CMPH;         /*!< compare value high 8bits register, offset: 0xC */
    uint8_t           RESERVED3[3]; /*!< reserved */
    volatile uint8_t  CLKPRESCALER; /*!< divider config register, offset: 0x10 */
} EwmRegType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Gets the value of the register CTRL
 *
 * This function gets the value of the register CTRL
 *
 * \param[in] obj : pointer to EWM register instance
 * \return the whole register value
 */
__attribute__((always_inline)) static inline uint8_t EwmReg_GetCtrl(const EwmRegType *obj)
{
    return obj->CTRL;
}

/*! \brief Sets the value of the register CTRL
 *
 * This function sets the value of the register CTRL
 *
 * \param[in] obj : pointer to EWM register instance
 * \param[in] value : the whole register value
 */
__attribute__((always_inline)) static inline void EwmReg_SetCtrl(EwmRegType *obj, uint8_t value)
{
    obj->CTRL = value;
}

/*! \brief Gets the Interrupt Enable
 *
 * This function gets the current Interrupt Enable.
 * This bit when set and EWM_OUT_b is asserted, an interrupt request is generated.
 * To de-assert interrupt request, user should clear this bit by writing 0.
 *
 * \param[in] obj : pointer to EWM register instance
 * \return Interrupt Enable
 *         - 0b : interrupt disabled.
 *         - 1b : interrupt enabled.
 */
__attribute__((always_inline)) static inline uint8_t EwmReg_GetCtrlIntEn(const EwmRegType *obj)
{
    return ((obj->CTRL & EWM_CTRL_INTEN_MASK) >> EWM_CTRL_INTEN_SHIFT);
}

/*! \brief Sets the Interrupt Enable
 *
 * This function sets the Interrupt Enable.
 * This bit when set and EWM_OUT_b is asserted, an interrupt request is generated.
 * To de-assert interrupt request, user should clear this bit by writing 0.
 *
 * \param[in] obj : pointer to EWM register instance
 * \param[in] value : the value of Interrupt Enable
 *                    - 0b : interrupt disabled.
 *                    - 1b : interrupt enabled.
 */
__attribute__((always_inline)) static inline void EwmReg_SetCtrlIntEn(EwmRegType *obj, uint8_t value)
{
    uint8_t tmp = obj->CTRL;

    tmp &= ~EWM_CTRL_INTEN_MASK;
    tmp |= (((uint8_t)(((uint8_t)(value)) << EWM_CTRL_INTEN_SHIFT)) & EWM_CTRL_INTEN_MASK);
    obj->CTRL = tmp;
}

/*! \brief Gets the EWM_in input Enable
 *
 * This function gets the current EWM_in input Enable.
 * write-once, should be configured before ewm_en
 * This bit when set, enables the EWM_in port
 *
 * \param[in] obj : pointer to EWM register instance
 * \return EWM_in input Enable
 *         - 0b : EWM_in input disabled.
 *         - 1b : EWM_in input enabled.
 */
__attribute__((always_inline)) static inline uint8_t EwmReg_GetCtrlInEn(const EwmRegType *obj)
{
    return ((obj->CTRL & EWM_CTRL_INEN_MASK) >> EWM_CTRL_INEN_SHIFT);
}

/*! \brief Sets the EWM_in input Enable
 *
 * This function sets the EWM_in input Enable.
 * write-once, should be configured before ewm_en
 * This bit when set, enables the EWM_in port
 *
 * \param[in] obj : pointer to EWM register instance
 * \param[in] value : the value of EWM_in input Enable
 *                    - 0b : EWM_in input disabled.
 *                    - 1b : EWM_in input enabled.
 */
__attribute__((always_inline)) static inline void EwmReg_SetCtrlInEn(EwmRegType *obj, uint8_t value)
{
    uint8_t tmp = obj->CTRL;

    tmp &= ~EWM_CTRL_INEN_MASK;
    tmp |= (((uint8_t)(((uint8_t)(value)) << EWM_CTRL_INEN_SHIFT)) & EWM_CTRL_INEN_MASK);
    obj->CTRL = tmp;
}

/*! \brief Gets the EWM_in's Assertion State Select
 *
 * This function gets the current EWM_in's Assertion State Select.
 * write-once, should be configured before ewm_en
 * Default assert state of the EWM_in signal is logic zero.
 * Setting the ASSIN bit inverts the assert state of EWM_in signal to a logic one
 *
 * \param[in] obj : pointer to EWM register instance
 * \return EWM_in's Assertion State Select
 *         - 0b : EWM_in active low
 *         - 1b : EWM_in active high
 */
__attribute__((always_inline)) static inline uint8_t EwmReg_GetCtrlAssIn(const EwmRegType *obj)
{
    return ((obj->CTRL & EWM_CTRL_ASSIN_MASK) >> EWM_CTRL_ASSIN_SHIFT);
}

/*! \brief Sets the EWM_in's Assertion State Select
 *
 * This function sets the EWM_in's Assertion State Select.
 * write-once, should be configured before ewm_en
 * Default assert state of the EWM_in signal is logic zero.
 * Setting the ASSIN bit inverts the assert state of EWM_in signal to a logic one
 *
 * \param[in] obj : pointer to EWM register instance
 * \param[in] value : the value of EWM_in's Assertion State Select
 *                    - 0b : EWM_in active low
 *                    - 1b : EWM_in active high
 */
__attribute__((always_inline)) static inline void EwmReg_SetCtrlAssIn(EwmRegType *obj, uint8_t value)
{
    uint8_t tmp = obj->CTRL;

    tmp &= ~EWM_CTRL_ASSIN_MASK;
    tmp |= (((uint8_t)(((uint8_t)(value)) << EWM_CTRL_ASSIN_SHIFT)) & EWM_CTRL_ASSIN_MASK);
    obj->CTRL = tmp;
}

/*! \brief Gets the EWM enable
 *
 * This function gets the current EWM enable.
 * write-once.
 * This bit when set, enables the EWM module.
 * This resets the EWM counter to zero and deasserts the EWM_OUT_b signal.
 * This bit when unset, keeps the EWM module disabled.
 * It cannot be re-enabled until a next reset, due to the write-once nature of this bit
 *
 * \param[in] obj : pointer to EWM register instance
 * \return EWM enable
 *         - 0b : EWM disabled
 *         - 1b : EWM enabled
 */
__attribute__((always_inline)) static inline uint8_t EwmReg_GetCtrlEwmEn(const EwmRegType *obj)
{
    return ((obj->CTRL & EWM_CTRL_EWMEN_MASK) >> EWM_CTRL_EWMEN_SHIFT);
}

/*! \brief Sets the EWM enable
 *
 * This function sets the EWM enable.
 * write-once.
 * This bit when set, enables the EWM module.
 * This resets the EWM counter to zero and deasserts the EWM_OUT_b signal.
 * This bit when unset, keeps the EWM module disabled.
 * It cannot be re-enabled until a next reset, due to the write-once nature of this bit
 *
 * \param[in] obj : pointer to EWM register instance
 * \param[in] value : the value of EWM enable
 *                    - 0b : EWM disabled
 *                    - 1b : EWM enabled
 */
__attribute__((always_inline)) static inline void EwmReg_SetCtrlEwmEn(EwmRegType *obj, uint8_t value)
{
    uint8_t tmp = obj->CTRL;

    tmp &= ~EWM_CTRL_EWMEN_MASK;
    tmp |= (((uint8_t)(((uint8_t)(value)) << EWM_CTRL_EWMEN_SHIFT)) & EWM_CTRL_EWMEN_MASK);
    obj->CTRL = tmp;
}

/*! \brief Sets the refresh register
 *
 * This function sets the refresh register.
 * The SERV register provides the interface from the CPU to the EWM module.
 * It is writeonly and reads of this register return zero.
 * The EWM refresh mechanism requires the CPU to write 0x2CB4 to the SERV register.
 *
 * \param[in] obj : pointer to EWM register instance
 * \param[in] value : the value of refresh register
 */
__attribute__((always_inline)) static inline void EwmReg_SetService(EwmRegType *obj, uint16_t value)
{
    uint16_t tmp = obj->SERV;

    tmp &= ~EWM_SERV_SERVICE_MASK;
    tmp |= (((uint16_t)(((uint16_t)(value)) << EWM_SERV_SERVICE_SHIFT)) & EWM_SERV_SERVICE_MASK);
    obj->SERV = tmp;
}

/*! \brief Gets the compare value low 8bits
 *
 * This function gets the current compare value low 8bits.
 * compare value low 8bit
 *
 * \param[in] obj : pointer to EWM register instance
 * \return compare value low 8bits
 */
__attribute__((always_inline)) static inline uint8_t EwmReg_GetCmpLCompareL(const EwmRegType *obj)
{
    return ((obj->CMPL & EWM_CMPL_COMPAREL_MASK) >> EWM_CMPL_COMPAREL_SHIFT);
}

/*! \brief Sets the compare value low 8bits
 *
 * This function sets the compare value low 8bits.
 * compare value low 8bit
 *
 * \param[in] obj : pointer to EWM register instance
 * \param[in] value : the value of compare value low 8bits
 */
__attribute__((always_inline)) static inline void EwmReg_SetCmpLCompareL(EwmRegType *obj, uint8_t value)
{
    uint8_t tmp = obj->CMPL;

    tmp &= ~EWM_CMPL_COMPAREL_MASK;
    tmp |= (((uint8_t)(((uint8_t)(value)) << EWM_CMPL_COMPAREL_SHIFT)) & EWM_CMPL_COMPAREL_MASK);
    obj->CMPL = tmp;
}

/*! \brief Gets the compare value high 8bits
 *
 * This function gets the current compare value high 8bits.
 * compare value high 8bit
 *
 * \param[in] obj : pointer to EWM register instance
 * \return compare value high 8bits
 */
__attribute__((always_inline)) static inline uint8_t EwmReg_GetCmpHCompareH(const EwmRegType *obj)
{
    return ((obj->CMPH & EWM_CMPH_COMPAREH_MASK) >> EWM_CMPH_COMPAREH_SHIFT);
}

/*! \brief Sets the compare value high 8bits
 *
 * This function sets the compare value high 8bits.
 * compare value high 8bit
 *
 * \param[in] obj : pointer to EWM register instance
 * \param[in] value : the value of compare value high 8bits
 */
__attribute__((always_inline)) static inline void EwmReg_SetCmpHCompareH(EwmRegType *obj, uint8_t value)
{
    uint8_t tmp = obj->CMPH;

    tmp &= ~EWM_CMPH_COMPAREH_MASK;
    tmp |= (((uint8_t)(((uint8_t)(value)) << EWM_CMPH_COMPAREH_SHIFT)) & EWM_CMPH_COMPAREH_MASK);
    obj->CMPH = tmp;
}

/*! \brief Gets the divider config register
 *
 * This function gets the current divider config register.
 * Selected low power clock source for running the EWM counter can be prescaled as below.
 * Prescaled clock frequency = low power clock source frequency / (1 + CLK_DIV)
 *
 * \param[in] obj : pointer to EWM register instance
 * \return divider config register
 */
__attribute__((always_inline)) static inline uint8_t EwmReg_GetClkPrescalerDiv(const EwmRegType *obj)
{
    return ((obj->CLKPRESCALER & EWM_CLKPRESCALER_CLK_DIV_MASK) >> EWM_CLKPRESCALER_CLK_DIV_SHIFT);
}

/*! \brief Sets the divider config register
 *
 * This function sets the divider config register.
 * Selected low power clock source for running the EWM counter can be prescaled as below.
 * Prescaled clock frequency = low power clock source frequency / (1 + CLK_DIV)
 *
 * \param[in] obj : pointer to EWM register instance
 * \param[in] value : the value of divider config register
 */
__attribute__((always_inline)) static inline void EwmReg_SetClkPrescalerDiv(EwmRegType *obj, uint8_t value)
{
    uint8_t tmp = obj->CLKPRESCALER;

    tmp &= ~EWM_CLKPRESCALER_CLK_DIV_MASK;
    tmp |= (((uint8_t)(((uint8_t)(value)) << EWM_CLKPRESCALER_CLK_DIV_SHIFT)) & EWM_CLKPRESCALER_CLK_DIV_MASK);
    obj->CLKPRESCALER = tmp;
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _EWM_REG_H_ */