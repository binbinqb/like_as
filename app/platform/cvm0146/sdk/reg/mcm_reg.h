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

#ifndef _MCM_REG_H_
#define _MCM_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the MCM Registers
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

/* CPCR Bit Fields */
#define MCM_CPCR_SRAML_WP_MASK   (0x40u)
#define MCM_CPCR_SRAML_WP_SHIFT  (6u)
#define MCM_CPCR_SRAML_WP_WIDTH  (1u)
#define MCM_CPCR_SRAML_ARB_MASK  (0x30u)
#define MCM_CPCR_SRAML_ARB_SHIFT (4u)
#define MCM_CPCR_SRAML_ARB_WIDTH (2u)
#define MCM_CPCR_SRAMU_WP_MASK   (0x04u)
#define MCM_CPCR_SRAMU_WP_SHIFT  (2u)
#define MCM_CPCR_SRAMU_WP_WIDTH  (1u)
#define MCM_CPCR_SRAMU_ARB_MASK  (0x03u)
#define MCM_CPCR_SRAMU_ARB_SHIFT (0u)
#define MCM_CPCR_SRAMU_ARB_WIDTH (2u)

/* INT_ST Bit Fields */
#define MCM_INT_ST_FIDC_MASK     (0x20u)
#define MCM_INT_ST_FIDC_SHIFT    (5u)
#define MCM_INT_ST_FIDC_WIDTH    (1u)
#define MCM_INT_ST_FIXC_MASK     (0x10u)
#define MCM_INT_ST_FIXC_SHIFT    (4u)
#define MCM_INT_ST_FIXC_WIDTH    (1u)
#define MCM_INT_ST_FUFC_MASK     (0x08u)
#define MCM_INT_ST_FUFC_SHIFT    (3u)
#define MCM_INT_ST_FUFC_WIDTH    (1u)
#define MCM_INT_ST_FOFC_MASK     (0x04u)
#define MCM_INT_ST_FOFC_SHIFT    (2u)
#define MCM_INT_ST_FOFC_WIDTH    (1u)
#define MCM_INT_ST_FDZC_MASK     (0x02u)
#define MCM_INT_ST_FDZC_SHIFT    (1u)
#define MCM_INT_ST_FDZC_WIDTH    (1u)
#define MCM_INT_ST_FIOC_MASK     (0x01u)
#define MCM_INT_ST_FIOC_SHIFT    (0u)
#define MCM_INT_ST_FIOC_WIDTH    (1u)

/* INT_EN Bit Fields */
#define MCM_INT_EN_FIDCE_MASK    (0x20u)
#define MCM_INT_EN_FIDCE_SHIFT   (5u)
#define MCM_INT_EN_FIDCE_WIDTH   (1u)
#define MCM_INT_EN_FIXCE_MASK    (0x10u)
#define MCM_INT_EN_FIXCE_SHIFT   (4u)
#define MCM_INT_EN_FIXCE_WIDTH   (1u)
#define MCM_INT_EN_FUFCE_MASK    (0x08u)
#define MCM_INT_EN_FUFCE_SHIFT   (3u)
#define MCM_INT_EN_FUFCE_WIDTH   (1u)
#define MCM_INT_EN_FOFCE_MASK    (0x04u)
#define MCM_INT_EN_FOFCE_SHIFT   (2u)
#define MCM_INT_EN_FOFCE_WIDTH   (1u)
#define MCM_INT_EN_FDZCE_MASK    (0x02u)
#define MCM_INT_EN_FDZCE_SHIFT   (1u)
#define MCM_INT_EN_FDZCE_WIDTH   (1u)
#define MCM_INT_EN_FIOCE_MASK    (0x01u)
#define MCM_INT_EN_FIOCE_SHIFT   (0u)
#define MCM_INT_EN_FIOCE_WIDTH   (1u)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief The definition of MCM registers
 */
typedef struct _McmRegType_
{
    volatile uint32_t       CPCR;   /*!< system sram protect schemes register, offset: 0x00 */
    const volatile uint32_t INT_ST; /*!< CPU Floating process unit status register, offset: 0x04 */
    volatile uint32_t       INT_EN; /*!< CPU Floating process unit enable register, offset: 0x08 */
} McmRegType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Gets the SRAML write protect
 *
 * This function gets the current SRAML write protect.
 * When this field is set, write to SRAM_U shall generate a bus error
 *
 * \param[in] obj : pointer to MCM register instance
 * \return SRAML write protect
 *         - 0b : write access
 *         - 1b : write deny
 */
__attribute__((always_inline)) static inline uint8_t McmReg_GetCpcrSRamLWp(const McmRegType *obj)
{
    return ((obj->CPCR & MCM_CPCR_SRAML_WP_MASK) >> MCM_CPCR_SRAML_WP_SHIFT);
}

/*! \brief Sets the SRAML write protect
 *
 * This function sets the SRAML write protect.
 * When this field is set, write to SRAM_U shall generate a bus error
 *
 * \param[in] obj : pointer to MCM register instance
 * \param[in] value : the value of SRAML write protect
 *                    - 0b : write access
 *                    - 1b : write deny
 */
__attribute__((always_inline)) static inline void McmReg_SetCpcrSRamLWp(McmRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CPCR;

    tmp &= ~MCM_CPCR_SRAML_WP_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MCM_CPCR_SRAML_WP_SHIFT)) & MCM_CPCR_SRAML_WP_MASK);
    obj->CPCR = tmp;
}

/*! \brief Gets the SRAML access arb between frontdoor
 *
 * This function gets the current SRAML access arb between frontdoor.
 * (CPU and debug) and backdoor(other masters: dma/cse)
 *
 * \param[in] obj : pointer to MCM register instance
 * \return SRAML access arb between frontdoor
 *         - 0h : Round Robin
 *         - 1h : Round Robin
 *         - 2h : Fixed priority with frontdoor first
 *         - 3h : Fixed priority with backdoor first
 */
__attribute__((always_inline)) static inline uint8_t McmReg_GetCpcrSRamLArb(const McmRegType *obj)
{
    return ((obj->CPCR & MCM_CPCR_SRAML_ARB_MASK) >> MCM_CPCR_SRAML_ARB_SHIFT);
}

/*! \brief Sets the SRAML access arb between frontdoor
 *
 * This function sets the SRAML access arb between frontdoor.
 * (CPU and debug) and backdoor(other masters: dma/cse)
 *
 * \param[in] obj : pointer to MCM register instance
 * \param[in] value : the value of SRAML access arb between frontdoor
 *                    - 0h : Round Robin
 *                    - 1h : Round Robin
 *                    - 2h : Fixed priority with frontdoor first
 *                    - 3h : Fixed priority with backdoor first
 */
__attribute__((always_inline)) static inline void McmReg_SetCpcrSRamLArb(McmRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CPCR;

    tmp &= ~MCM_CPCR_SRAML_ARB_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MCM_CPCR_SRAML_ARB_SHIFT)) & MCM_CPCR_SRAML_ARB_MASK);
    obj->CPCR = tmp;
}

/*! \brief Gets the SRAMU write protect
 *
 * This function gets the current SRAMU write protect.
 * When this field is set, write to SRAM_U shall generate a bus error
 *
 * \param[in] obj : pointer to MCM register instance
 * \return SRAMU write protect
 *         - 0b : write access
 *         - 1b : write deny
 */
__attribute__((always_inline)) static inline uint8_t McmReg_GetCpcrSRamUWp(const McmRegType *obj)
{
    return ((obj->CPCR & MCM_CPCR_SRAMU_WP_MASK) >> MCM_CPCR_SRAMU_WP_SHIFT);
}

/*! \brief Sets the SRAMU write protect
 *
 * This function sets the SRAMU write protect.
 * When this field is set, write to SRAM_U shall generate a bus error
 *
 * \param[in] obj : pointer to MCM register instance
 * \param[in] value : the value of SRAMU write protect
 *                    - 0b : write access
 *                    - 1b : write deny
 */
__attribute__((always_inline)) static inline void McmReg_SetCpcrSRamUWp(McmRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CPCR;

    tmp &= ~MCM_CPCR_SRAMU_WP_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MCM_CPCR_SRAMU_WP_SHIFT)) & MCM_CPCR_SRAMU_WP_MASK);
    obj->CPCR = tmp;
}

/*! \brief Gets the SRAMU access arb between frontdoor
 *
 * This function gets the current SRAMU access arb between frontdoor.
 * (CPU and debug) and backdoor(other masters: dma/cse)
 *
 * \param[in] obj : pointer to MCM register instance
 * \return SRAMU access arb between frontdoor
 *         - 0h : Round Robin
 *         - 1h : Round Robin
 *         - 2h : Fixed priority with frontdoor first
 *         - 3h : Fixed priority with backdoor first
 */
__attribute__((always_inline)) static inline uint8_t McmReg_GetCpcrSRamUArb(const McmRegType *obj)
{
    return ((obj->CPCR & MCM_CPCR_SRAMU_ARB_MASK) >> MCM_CPCR_SRAMU_ARB_SHIFT);
}

/*! \brief Sets the SRAMU access arb between frontdoor
 *
 * This function sets the SRAMU access arb between frontdoor.
 * (CPU and debug) and backdoor(other masters: dma/cse)
 *
 * \param[in] obj : pointer to MCM register instance
 * \param[in] value : the value of SRAMU access arb between frontdoor
 *                    - 0h : Round Robin
 *                    - 1h : Round Robin
 *                    - 2h : Fixed priority with frontdoor first
 *                    - 3h : Fixed priority with backdoor first
 */
__attribute__((always_inline)) static inline void McmReg_SetCpcrSRamUArb(McmRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CPCR;

    tmp &= ~MCM_CPCR_SRAMU_ARB_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MCM_CPCR_SRAMU_ARB_SHIFT)) & MCM_CPCR_SRAMU_ARB_MASK);
    obj->CPCR = tmp;
}

/*! \brief Gets the CPU FPU input normalization interrupt
 *
 * This function gets the current CPU FPU input normalization interrupt.
 *
 * \param[in] obj : pointer to MCM register instance
 * \return CPU FPU input normalization interrupt
 *         - 0b : no interrupt
 *         - 1b : interrupt occured
 */
__attribute__((always_inline)) static inline uint8_t McmReg_GetIntStFidc(const McmRegType *obj)
{
    return ((obj->INT_ST & MCM_INT_ST_FIDC_MASK) >> MCM_INT_ST_FIDC_SHIFT);
}

/*! \brief Gets the CPU FPU  inexact interrupt
 *
 * This function gets the current CPU FPU  inexact interrupt.
 *
 * \param[in] obj : pointer to MCM register instance
 * \return CPU FPU  inexact interrupt
 *         - 0b : no interrupt
 *         - 1b : interrupt occured
 */
__attribute__((always_inline)) static inline uint8_t McmReg_GetIntStFixc(const McmRegType *obj)
{
    return ((obj->INT_ST & MCM_INT_ST_FIXC_MASK) >> MCM_INT_ST_FIXC_SHIFT);
}

/*! \brief Gets the CPU FPU underflow interrupt
 *
 * This function gets the current CPU FPU underflow interrupt.
 *
 * \param[in] obj : pointer to MCM register instance
 * \return CPU FPU underflow interrupt
 *         - 0b : no interrupt
 *         - 1b : interrupt occured
 */
__attribute__((always_inline)) static inline uint8_t McmReg_GetIntStFufc(const McmRegType *obj)
{
    return ((obj->INT_ST & MCM_INT_ST_FUFC_MASK) >> MCM_INT_ST_FUFC_SHIFT);
}

/*! \brief Gets the CPU FPU overflow interrupt
 *
 * This function gets the current CPU FPU overflow interrupt.
 *
 * \param[in] obj : pointer to MCM register instance
 * \return CPU FPU overflow interrupt
 *         - 0b : no interrupt
 *         - 1b : interrupt occured
 */
__attribute__((always_inline)) static inline uint8_t McmReg_GetIntStFofc(const McmRegType *obj)
{
    return ((obj->INT_ST & MCM_INT_ST_FOFC_MASK) >> MCM_INT_ST_FOFC_SHIFT);
}

/*! \brief Gets the CPU FPU divide-by-zero interrupt
 *
 * This function gets the current CPU FPU divide-by-zero interrupt.
 *
 * \param[in] obj : pointer to MCM register instance
 * \return CPU FPU divide-by-zero interrupt
 *         - 0b : no interrupt
 *         - 1b : interrupt occured
 */
__attribute__((always_inline)) static inline uint8_t McmReg_GetIntStFdzc(const McmRegType *obj)
{
    return ((obj->INT_ST & MCM_INT_ST_FDZC_MASK) >> MCM_INT_ST_FDZC_SHIFT);
}

/*! \brief Gets the CPU FPU invalid operation interrupt
 *
 * This function gets the current CPU FPU invalid operation interrupt .
 *
 * \param[in] obj : pointer to MCM register instance
 * \return CPU FPU invalid operation interrupt
 *         - 0b : no interrupt
 *         - 1b : interrupt occured
 */
__attribute__((always_inline)) static inline uint8_t McmReg_GetIntStFioc(const McmRegType *obj)
{
    return ((obj->INT_ST & MCM_INT_ST_FIOC_MASK) >> MCM_INT_ST_FIOC_SHIFT);
}

/*! \brief Gets the CPU FPU input normalization interrupt enable
 *
 * This function gets the current CPU FPU input normalization interrupt enable.
 *
 * \param[in] obj : pointer to MCM register instance
 * \return CPU FPU input normalization interrupt enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t McmReg_GetIntEnFidce(const McmRegType *obj)
{
    return ((obj->INT_EN & MCM_INT_EN_FIDCE_MASK) >> MCM_INT_EN_FIDCE_SHIFT);
}

/*! \brief Sets the CPU FPU input normalization interrupt enable
 *
 * This function sets the CPU FPU input normalization interrupt enable.
 *
 * \param[in] obj : pointer to MCM register instance
 * \param[in] value : the value of CPU FPU input normalization interrupt enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void McmReg_SetIntEnFidce(McmRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->INT_EN;

    tmp &= ~MCM_INT_EN_FIDCE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MCM_INT_EN_FIDCE_SHIFT)) & MCM_INT_EN_FIDCE_MASK);
    obj->INT_EN = tmp;
}

/*! \brief Gets the CPU FPU  inexact interrupt enable
 *
 * This function gets the current CPU FPU  inexact interrupt enable.
 *
 * \param[in] obj : pointer to MCM register instance
 * \return CPU FPU  inexact interrupt enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t McmReg_GetIntEnFixce(const McmRegType *obj)
{
    return ((obj->INT_EN & MCM_INT_EN_FIXCE_MASK) >> MCM_INT_EN_FIXCE_SHIFT);
}

/*! \brief Sets the CPU FPU  inexact interrupt enable
 *
 * This function sets the CPU FPU  inexact interrupt enable.
 *
 * \param[in] obj : pointer to MCM register instance
 * \param[in] value : the value of CPU FPU  inexact interrupt enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void McmReg_SetIntEnFixce(McmRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->INT_EN;

    tmp &= ~MCM_INT_EN_FIXCE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MCM_INT_EN_FIXCE_SHIFT)) & MCM_INT_EN_FIXCE_MASK);
    obj->INT_EN = tmp;
}

/*! \brief Gets the CPU FPU underflow interrupt enable
 *
 * This function gets the current CPU FPU underflow interrupt enable.
 *
 * \param[in] obj : pointer to MCM register instance
 * \return CPU FPU underflow interrupt enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t McmReg_GetIntEnFufce(const McmRegType *obj)
{
    return ((obj->INT_EN & MCM_INT_EN_FUFCE_MASK) >> MCM_INT_EN_FUFCE_SHIFT);
}

/*! \brief Sets the CPU FPU underflow interrupt enable
 *
 * This function sets the CPU FPU underflow interrupt enable.
 *
 * \param[in] obj : pointer to MCM register instance
 * \param[in] value : the value of CPU FPU underflow interrupt enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void McmReg_SetIntEnFufce(McmRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->INT_EN;

    tmp &= ~MCM_INT_EN_FUFCE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MCM_INT_EN_FUFCE_SHIFT)) & MCM_INT_EN_FUFCE_MASK);
    obj->INT_EN = tmp;
}

/*! \brief Gets the CPU FPU overflow interrupt enable
 *
 * This function gets the current CPU FPU overflow interrupt enable.
 *
 * \param[in] obj : pointer to MCM register instance
 * \return CPU FPU overflow interrupt enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t McmReg_GetIntEnFofce(const McmRegType *obj)
{
    return ((obj->INT_EN & MCM_INT_EN_FOFCE_MASK) >> MCM_INT_EN_FOFCE_SHIFT);
}

/*! \brief Sets the CPU FPU overflow interrupt enable
 *
 * This function sets the CPU FPU overflow interrupt enable.
 *
 * \param[in] obj : pointer to MCM register instance
 * \param[in] value : the value of CPU FPU overflow interrupt enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void McmReg_SetIntEnFofce(McmRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->INT_EN;

    tmp &= ~MCM_INT_EN_FOFCE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MCM_INT_EN_FOFCE_SHIFT)) & MCM_INT_EN_FOFCE_MASK);
    obj->INT_EN = tmp;
}

/*! \brief Gets the CPU FPU divide-by-zero interrupt enable
 *
 * This function gets the current CPU FPU divide-by-zero interrupt enable.
 *
 * \param[in] obj : pointer to MCM register instance
 * \return CPU FPU divide-by-zero interrupt enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t McmReg_GetIntEnFdzce(const McmRegType *obj)
{
    return ((obj->INT_EN & MCM_INT_EN_FDZCE_MASK) >> MCM_INT_EN_FDZCE_SHIFT);
}

/*! \brief Sets the CPU FPU divide-by-zero interrupt enable
 *
 * This function sets the CPU FPU divide-by-zero interrupt enable.
 *
 * \param[in] obj : pointer to MCM register instance
 * \param[in] value : the value of CPU FPU divide-by-zero interrupt enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void McmReg_SetIntEnFdzce(McmRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->INT_EN;

    tmp &= ~MCM_INT_EN_FDZCE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MCM_INT_EN_FDZCE_SHIFT)) & MCM_INT_EN_FDZCE_MASK);
    obj->INT_EN = tmp;
}

/*! \brief Gets the CPU FPU invalid operation interrupt enable
 *
 * This function gets the current CPU FPU invalid operation interrupt enable.
 *
 * \param[in] obj : pointer to MCM register instance
 * \return CPU FPU invalid operation interrupt enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t McmReg_GetIntEnFioce(const McmRegType *obj)
{
    return ((obj->INT_EN & MCM_INT_EN_FIOCE_MASK) >> MCM_INT_EN_FIOCE_SHIFT);
}

/*! \brief Sets the CPU FPU invalid operation interrupt enable
 *
 * This function sets the CPU FPU invalid operation interrupt enable.
 *
 * \param[in] obj : pointer to MCM register instance
 * \param[in] value : the value of CPU FPU invalid operation interrupt enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void McmReg_SetIntEnFioce(McmRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->INT_EN;

    tmp &= ~MCM_INT_EN_FIOCE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MCM_INT_EN_FIOCE_SHIFT)) & MCM_INT_EN_FIOCE_MASK);
    obj->INT_EN = tmp;
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _MCM_REG_H_ */
