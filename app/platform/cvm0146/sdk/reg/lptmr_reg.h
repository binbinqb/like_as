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

#ifndef _LPTMR_REG_H_
#define _LPTMR_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the LPTMR (Low Power Timer) Registers
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
#define LPTMR_CSR_TEN_MASK       (0x1u)
#define LPTMR_CSR_TEN_SHIFT      (0u)
#define LPTMR_CSR_TEN_WIDTH      (1u)
#define LPTMR_CSR_TMS_MASK       (0x2u)
#define LPTMR_CSR_TMS_SHIFT      (1u)
#define LPTMR_CSR_TMS_WIDTH      (1u)
#define LPTMR_CSR_TFC_MASK       (0x4u)
#define LPTMR_CSR_TFC_SHIFT      (2u)
#define LPTMR_CSR_TFC_WIDTH      (1u)
#define LPTMR_CSR_TPP_MASK       (0x8u)
#define LPTMR_CSR_TPP_SHIFT      (3u)
#define LPTMR_CSR_TPP_WIDTH      (1u)
#define LPTMR_CSR_TPS_MASK       (0x30u)
#define LPTMR_CSR_TPS_SHIFT      (4u)
#define LPTMR_CSR_TPS_WIDTH      (2u)
#define LPTMR_CSR_TIE_MASK       (0x40u)
#define LPTMR_CSR_TIE_SHIFT      (6u)
#define LPTMR_CSR_TIE_WIDTH      (1u)
#define LPTMR_CSR_TCF_MASK       (0x80u)
#define LPTMR_CSR_TCF_SHIFT      (7u)
#define LPTMR_CSR_TCF_WIDTH      (1u)
#define LPTMR_CSR_TDRE_MASK      (0x100u)
#define LPTMR_CSR_TDRE_SHIFT     (8u)
#define LPTMR_CSR_TDRE_WIDTH     (1u)

/* PSR Bit Fields */
#define LPTMR_PSR_PBYP_MASK      (0x4u)
#define LPTMR_PSR_PBYP_SHIFT     (2u)
#define LPTMR_PSR_PBYP_WIDTH     (1u)
#define LPTMR_PSR_PRESCALE_MASK  (0x78u)
#define LPTMR_PSR_PRESCALE_SHIFT (3u)
#define LPTMR_PSR_PRESCALE_WIDTH (4u)

/* CMR Bit Fields */
#define LPTMR_CMR_COMPARE_MASK   (0xFFFFu)
#define LPTMR_CMR_COMPARE_SHIFT  (0u)
#define LPTMR_CMR_COMPARE_WIDTH  (16u)

/* CNR Bit Fields */
#define LPTMR_CNR_COUNTER_MASK   (0xFFFFu)
#define LPTMR_CNR_COUNTER_SHIFT  (0u)
#define LPTMR_CNR_COUNTER_WIDTH  (16u)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief The definition of LPTMR registers
 */
typedef struct _LptmrRegType_
{
    volatile uint32_t CSR; /*!< Low Power Timer Control Status Register, offset: 0x0 */
    volatile uint32_t PSR; /*!< Low Power Timer Prescale Register, offset: 0x4 */
    volatile uint32_t CMR; /*!< Low Power Timer Compare Register, offset: 0x8 */
    volatile uint32_t CNR; /*!< Low Power Timer Counter Register, offset: 0xC */
} LptmrRegType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Get the Enable state.
 *
 * This function get the enable state of LPTMR.
 * When TEN is clear, it resets the LPTMR internal logic, including the CNR and TCF.
 * When TEN is set, the LPTMR is enabled.
 *
 * \param[in] obj : pointer to LPTMR register instance
 * \return the state of the LPTMR
 *         - 0 : LPTMR is disabled and internal logic is reset.
 *         - 1 : LPTMR is enabled.
 */
__attribute__((always_inline)) static inline uint8_t LptmrReg_GetEnable(const LptmrRegType *obj)
{
    return ((obj->CSR & LPTMR_CSR_TEN_MASK) >> LPTMR_CSR_TEN_SHIFT);
}

/*! \brief Set the 32 bits of LPTMR data register
 *
 * This function write new data to LPTMR calculator
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to LPTMR register instance
 * \param[in] value : the state of the LPTMR
 *                    - 0 : LPTMR is disabled and internal logic is reset.
 *                    - 1 : LPTMR is enabled.
 */
__attribute__((always_inline)) static inline void LptmrReg_SetEnable(LptmrRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CSR;
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    tmp &= ~(LPTMR_CSR_TEN_MASK | LPTMR_CSR_TCF_MASK);
    tmp |= (((uint32_t)(((uint32_t)(value)) << LPTMR_CSR_TEN_SHIFT)) & LPTMR_CSR_TEN_MASK);
    obj->CSR = tmp;
}

/*! \brief Get current Work Mode.
 *
 * This function returns the currently configured Work Mode for the LPTMR.
 *
 * \param[in] obj : pointer to LPTMR register instance
 * \return Work Mode
 *         - 0 : Timer Counter Mode
 *         - 1 : Pulse Counter Mode
 */
__attribute__((always_inline)) static inline uint8_t LptmrReg_GetWorkMode(const LptmrRegType *obj)
{
    return ((obj->CSR & LPTMR_CSR_TMS_MASK) >> LPTMR_CSR_TMS_SHIFT);
}

/*! \brief Set the Work Mode of LPTMR
 *
 * This function configures the Work Mode for the LPTMR.
 *
 * \note TMS must be altered only when the LPTMR is disabled.
 *
 * \param[in] obj : pointer to LPTMR register instance
 * \param[in] value : the work mode of the LPTMR
 *                    - 0 : Timer Counter Mode.
 *                    - 1 : Pulse Counter Mode.
 */
__attribute__((always_inline)) static inline void LptmrReg_SetWorkMode(LptmrRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CSR;
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    tmp &= ~(LPTMR_CSR_TMS_MASK | LPTMR_CSR_TCF_MASK);
    tmp |= (((uint32_t)(((uint32_t)(value)) << LPTMR_CSR_TMS_SHIFT)) & LPTMR_CSR_TMS_MASK);
    obj->CSR = tmp;
}

/*! \brief Get Free Running state
 *
 * This function checks whether the Free Running feature of the LPTMR is enabled or disabled.
 * When clear, TFC configures the CNR to reset whenever TCF is set.
 * When set, TFC configures the CNR to reset on overflow
 *
 * \param[in] obj : pointer to LPTMR register instance
 * \return free running mode state
 *         - 0 : CNR is reset whenever TCF is set
 *         - 1 : CNR is reset on overflow
 */
__attribute__((always_inline)) static inline uint8_t LptmrReg_GetFreeRunning(const LptmrRegType *obj)
{
    return ((obj->CSR & LPTMR_CSR_TFC_MASK) >> LPTMR_CSR_TFC_SHIFT);
}

/*! \brief Set the Free Running state
 *
 * This function configures the Free Running state for the LPTMR.
 * When clear, TFC configures the CNR to reset whenever TCF is set.
 * When set, TFC configures the CNR to reset on overflow
 *
 * \note TFC must be altered only when the LPTMR is disabled.
 *
 * \param[in] obj : pointer to LPTMR register instance
 * \param[in] value : free running mode state
 *                    - 0 : CNR is reset whenever TCF is set
 *                    - 1 : CNR is reset on overflow
 */
__attribute__((always_inline)) static inline void LptmrReg_SetFreeRunning(LptmrRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CSR;
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    tmp &= ~(LPTMR_CSR_TFC_MASK | LPTMR_CSR_TCF_MASK);
    tmp |= (((uint32_t)(((uint32_t)(value)) << LPTMR_CSR_TFC_SHIFT)) & LPTMR_CSR_TFC_MASK);
    obj->CSR = tmp;
}

/*! \brief Get Pin Polarity for Pulse Counter Mode
 *
 * This function returns the configured pin polarity that triggers an increment
 * in Pulse Counter Mode.
 *
 * \param[in] obj : pointer to LPTMR register instance
 * \return the pin polarity for Pulse Counter Mode
 *         - 0 : Pulse Counter input source is active-high, and the CNR increments on the rising-edge.
 *         - 1 : Pulse Counter input source is active-low, and the CNR increments on the falling-edge.
 */
__attribute__((always_inline)) static inline uint8_t LptmrReg_GetPinPolarity(const LptmrRegType *obj)
{
    return ((obj->CSR & LPTMR_CSR_TPP_MASK) >> LPTMR_CSR_TPP_SHIFT);
}

/*! \brief Set Pin Polarity for Pulse Counter Mode
 *
 * This function configures the pin polarity that triggers an increment in Pulse
 * Counter Mode. This feature can be configured only when the LPTMR is disabled.
 *
 * \note TPP must be changed only when the LPTMR is disabled.
 *
 * \param[in] obj : pointer to LPTMR register instance
 * \param[in] value : the pin polarity to count in Pulse Counter Mode
 *                    - 0 : Pulse Counter input source is active-high, and the CNR increments on the rising-edge.
 *                    - 1 : Pulse Counter input source is active-low, and the CNR increments on the falling-edge.
 */
__attribute__((always_inline)) static inline void LptmrReg_SetPinPolarity(LptmrRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CSR;
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    tmp &= ~(LPTMR_CSR_TPP_MASK | LPTMR_CSR_TCF_MASK);
    tmp |= (((uint32_t)(((uint32_t)(value)) << LPTMR_CSR_TPP_SHIFT)) & LPTMR_CSR_TPP_MASK);
    obj->CSR = tmp;
}

/*! \brief Get the Pin select for Counter Mode
 *
 * This function returns the configured Input Pin for Pulse Counter Mode.
 * The input connections vary by device. See the chip configuration information
 * about connections to these inputs.
 *
 * \param[in] obj : pointer to LPTMR register instance
 * \return pin selection
 *         - 0 : Pulse counter input 0 is selected.
 *         - 1 : Pulse counter input 1 is selected.
 *         - 2 : Pulse counter input 2 is selected.
 *         - 3 : Pulse counter input 3 is selected.
 */
__attribute__((always_inline)) static inline uint8_t LptmrReg_GetPinSelect(const LptmrRegType *obj)
{
    return ((obj->CSR & LPTMR_CSR_TPS_MASK) >> LPTMR_CSR_TPS_SHIFT);
}

/*! \brief Set the Pin selection for Pulse Counter Mode
 *
 * This function configures the input source to be used in Pulse Counter mode.
 * The input connections vary by device. See the chip configuration information
 * about connections to these inputs.
 *
 * \note TPS must be altered only when the LPTMR is disabled.
 *
 * \param[in] obj : pointer to LPTMR register instance
 * \param[in] value : pin selection
 *                    - 0 : Pulse counter input 0 is selected.
 *                    - 1 : Pulse counter input 1 is selected.
 *                    - 2 : Pulse counter input 2 is selected.
 *                    - 3 : Pulse counter input 3 is selected.
 */
__attribute__((always_inline)) static inline void LptmrReg_SetPinSelect(LptmrRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CSR;
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    tmp &= ~(LPTMR_CSR_TPS_MASK | LPTMR_CSR_TCF_MASK);
    tmp |= (((uint32_t)(((uint32_t)(value)) << LPTMR_CSR_TPS_SHIFT)) & LPTMR_CSR_TPS_MASK);
    obj->CSR = tmp;
}

/*! \brief Get the Interrupt Enable state
 *
 * This function returns the Interrupt Enable state for the LPTMR. If enabled,
 * an interrupt is generated when a Compare Match event occurs.
 *
 * \param[in] obj : pointer to LPTMR register instance
 * \return interrupt enable state
 *         - 0 : timer interrupt disabled.
 *         - 1 : timer interrupt enabled.
 */
__attribute__((always_inline)) static inline uint8_t LptmrReg_GetInterruptEnable(const LptmrRegType *obj)
{
    return ((obj->CSR & LPTMR_CSR_TIE_MASK) >> LPTMR_CSR_TIE_SHIFT);
}

/*! \brief Set the Interrupt Enable state
 *
 * This function configures the Interrupt Enable state for the LPTMR. If enabled,
 * an interrupt is generated when a Compare Match event occurs.
 *
 * \note Either TIE or TDRE can be valid at the same time.
 * \note Must be altered only when the LPTMR is disabled.
 *
 * \param[in] obj : pointer to LPTMR register instance
 * \param[in] value : The new state for the interrupt
 *                    - 0 : disable Interrupt.
 *                    - 1 : enable Interrupt.
 */
__attribute__((always_inline)) static inline void LptmrReg_SetInterrupt(LptmrRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CSR;
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    tmp &= ~(LPTMR_CSR_TIE_MASK | LPTMR_CSR_TCF_MASK);
    tmp |= (((uint32_t)(((uint32_t)(value)) << LPTMR_CSR_TIE_SHIFT)) & LPTMR_CSR_TIE_MASK);
    obj->CSR = tmp;
}

/*! \brief Get the Compare Flag state
 *
 * This function checks whether a Compare Match event has occurred or if there is
 * an Interrupt Pending.
 * TCF is set when the LPTMR is enabled and the CNR equals the CMR and increments.
 * TCF is cleared when the LPTMR is disabled or a logic 1 is written to it.
 *
 * \param[in] obj : pointer to LPTMR register instance
 * \return the Compare Flag state
 *         - 0 : the value of CNR is not equal to CMR and increments.
 *         - 1 : the value of CNR is equal to CMR and increments.
 */
__attribute__((always_inline)) static inline uint8_t LptmrReg_GetCompareFlag(const LptmrRegType *obj)
{
    return ((obj->CSR & LPTMR_CSR_TCF_MASK) >> LPTMR_CSR_TCF_SHIFT);
}

/*! \brief Clear the Compare Flag
 *
 * This function clears the Compare Flag/Interrupt Pending state.
 * TCF is set when the LPTMR is enabled and the CNR equals the CMR and increments.
 * TCF is cleared when the LPTMR is disabled or a logic 1 is written to it.
 *
 * \note Ensure to clear this field before enabling the Timer interrupt or DMA request.
 *
 * \param[in] obj : pointer to LPTMR register instance
 */
__attribute__((always_inline)) static inline void LptmrReg_ClearCompareFlag(LptmrRegType *obj)
{
    uint32_t tmp = obj->CSR;
    tmp |= (LPTMR_CSR_TCF_MASK);
    obj->CSR = tmp;
    /* Read back to avoid problem */
    (void)obj->CSR;
}

/*! \brief Get the DMA Request Enable Flag
 *
 * This function checks whether a DMA Request feature of the LPTMR is enabled.
 * The DMA Request is issued when a Compare Match is asserted.
 * If enabled, the Compare Match/Interrupt Pending flag is cleared when
 * the DMA controller is done.
 *
 * \param[in] obj : pointer to LPTMR register instance
 * \return DMA Request enable
 *         - 0 : timer DMA Request disabled.
 *         - 1 : timer DMA Request enabled.
 */
__attribute__((always_inline)) static inline uint8_t LptmrReg_GetDmaRequest(const LptmrRegType *obj)
{
    return ((obj->CSR & LPTMR_CSR_TDRE_MASK) >> LPTMR_CSR_TDRE_SHIFT);
}

/*! \brief Configure the DMA Request Enable Flag state
 *
 * This function configures the DMA Request feature of the LPTMR.
 * If enabled, a DMA Request is issued when the Compare Match event occurs.
 * If enabled, the Compare Match/Interrupt Pending flag is cleared when the DMA controller is done.
 *
 * \note Either TIE or TDRE can be valid at the same time.
 * \note Must be altered only when the LPTMR is disabled.
 *
 * \param[in] obj : pointer to LPTMR register instance
 * \param[in] value : the new state for DMA Request Enable Flag
 *                    - 0 : disable DMA Request
 *                    - 1 : enable DMA Request
 */
__attribute__((always_inline)) static inline void LptmrReg_SetDmaRequest(LptmrRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CSR;
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    tmp &= ~(LPTMR_CSR_TDRE_MASK | LPTMR_CSR_TCF_MASK);
    tmp |= (((uint32_t)(((uint32_t)(value)) << LPTMR_CSR_TDRE_SHIFT)) & LPTMR_CSR_TDRE_MASK);
    obj->CSR = tmp;
}

/*! \brief Get the Prescaler/Glitch Filter Bypass enable state
 *
 * This function checks whether the Prescaler/Glitch Filter Bypass is enabled.
 * When PBYP is set, the selected prescaler clock in Time Counter mode or
 * selected input source in Pulse Counter mode directly clocks the CNR.
 * When PBYP is clear, the CNR is clocked by the output of the prescaler/glitch filter.
 *
 * \param[in] obj : pointer to LPTMR register instance
 * \return the Prescaler Bypass state
 *         - 0 : prescaler/glitch filter is used.
 *         - 1 : prescaler/glitch filter is bypassed.
 */
__attribute__((always_inline)) static inline uint8_t LptmrReg_GetBypass(const LptmrRegType *obj)
{
    return ((obj->PSR & LPTMR_PSR_PBYP_MASK) >> LPTMR_PSR_PBYP_SHIFT);
}

/*! \brief Configure the Prescaler/Glitch Filter Bypass enable state
 *
 * This function configures the Prescaler/Glitch filter Bypass.
 *
 * \note Must be altered only when the LPTMR is disabled.
 *
 * \param[in] obj : pointer to LPTMR register instance
 * \param[in] value : the new Prescaler/Glitch Filter Bypass state
 *                    - 0 : use rescaler/glitch filter
 *                    - 1 : bypass rescaler/glitch filter
 */
__attribute__((always_inline)) static inline void LptmrReg_SetBypass(LptmrRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PSR;
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    tmp &= ~(LPTMR_PSR_PBYP_MASK);
    tmp |= (((uint32_t)(((uint32_t)(value)) << LPTMR_PSR_PBYP_SHIFT)) & LPTMR_PSR_PBYP_MASK);
    obj->PSR = tmp;
}

/*! \brief Get Prescaler/Glitch Filter divider value
 *
 * This function returns the currently configured Prescaler/Glitch Filter divider value.
 * Prescale Value configures the size of the Prescaler in Time Counter mode or width of the
 * glitch filter in Pulse Counter mode.
 * The width of the glitch filter can vary by 1 cycle due to synchronization of the pulse counter input.
 *
 * \param[in] obj : pointer to LPTMR register instance
 * \return the Prescaler/Glitch filter value
 *         - 0 : Prescaler divides the prescaler clock by 2; glitch filter does not support this configuration.
 *         - 1 : Prescaler divides the prescaler clock by 4; glitch filter recognizes change on input pin after 2 rising clock edges.
 *         - 2 : Prescaler divides the prescaler clock by 8; glitch filter recognizes change on input pin after 4 rising clock edges.
 *         - 3 : Prescaler divides the prescaler clock by 16; glitch filter recognizes change on input pin after 8 rising clock edges.
 *         - 4 : Prescaler divides the prescaler clock by 32; glitch filter recognizes change on input pin after 16 rising clock edges.
 *         - 5 : Prescaler divides the prescaler clock by 64; glitch filter recognizes change on input pin after 32 rising clock edges.
 *         - 6 : Prescaler divides the prescaler clock by 128; glitch filter recognizes change on input pin after 64 rising clock edges.
 *         - 7 : Prescaler divides the prescaler clock by 256; glitch filter recognizes change on input pin after 128 rising clock edges.
 *         - 8 : Prescaler divides the prescaler clock by 512; glitch filter recognizes change on input pin after 256 rising clock edges.
 *         - 9 : Prescaler divides the prescaler clock by 1024; glitch filter recognizes change on input pin after 512 rising clock edges.
 *         - 10 : Prescaler divides the prescaler clock by 2048; glitch filter recognizes change on input pin after 1024 rising clock edges.
 *         - 11 : Prescaler divides the prescaler clock by 4096; glitch filter recognizes change on input pin after 2048 rising clock edges.
 *         - 12 : Prescaler divides the prescaler clock by 8192; glitch filter recognizes change on input pin after 4096 rising clock edges.
 *         - 13 : Prescaler divides the prescaler clock by 16,384; glitch filter recognizes change on input pin after 8192 rising clock edges.
 *         - 14 : Prescaler divides the prescaler clock by 32,768; glitch filter recognizes change on input pin after 16,384 rising clock edges.
 *         - 15 : Prescaler divides the prescaler clock by 65,536; glitch filter recognizes change on input pin after 32,768 rising clock edges.
 */
__attribute__((always_inline)) static inline uint8_t LptmrReg_GetPrescaler(const LptmrRegType *obj)
{
    return ((obj->PSR & LPTMR_PSR_PRESCALE_MASK) >> LPTMR_PSR_PRESCALE_SHIFT);
}

/*! \brief Configure the Prescaler/Glitch Filter divider value
 *
 * This function configures the value for the Prescaler/Glitch Filter.
 *
 * \note Must be altered only when the LPTMR is disabled.
 *
 * \param[in] obj : pointer to LPTMR register instance
 * \param[in] value : the new Prescaler value
 *                    - 0 : Prescaler divides the prescaler clock by 2; glitch filter does not support this configuration.
 *                    - 1 : Prescaler divides the prescaler clock by 4; glitch filter recognizes change on input pin after 2 rising clock edges.
 *                    - 2 : Prescaler divides the prescaler clock by 8; glitch filter recognizes change on input pin after 4 rising clock edges.
 *                    - 3 : Prescaler divides the prescaler clock by 16; glitch filter recognizes change on input pin after 8 rising clock edges.
 *                    - 4 : Prescaler divides the prescaler clock by 32; glitch filter recognizes change on input pin after 16 rising clock edges.
 *                    - 5 : Prescaler divides the prescaler clock by 64; glitch filter recognizes change on input pin after 32 rising clock edges.
 *                    - 6 : Prescaler divides the prescaler clock by 128; glitch filter recognizes change on input pin after 64 rising clock edges.
 *                    - 7 : Prescaler divides the prescaler clock by 256; glitch filter recognizes change on input pin after 128 rising clock edges.
 *                    - 8 : Prescaler divides the prescaler clock by 512; glitch filter recognizes change on input pin after 256 rising clock edges.
 *                    - 9 : Prescaler divides the prescaler clock by 1024; glitch filter recognizes change on input pin after 512 rising clock edges.
 *                    - 10 : Prescaler divides the prescaler clock by 2048; glitch filter recognizes change on input pin after 1024 rising clock edges.
 *                    - 11 : Prescaler divides the prescaler clock by 4096; glitch filter recognizes change on input pin after 2048 rising clock edges.
 *                    - 12 : Prescaler divides the prescaler clock by 8192; glitch filter recognizes change on input pin after 4096 rising clock edges.
 *                    - 13 : Prescaler divides the prescaler clock by 16,384; glitch filter recognizes change on input pin after 8192 rising clock edges.
 *                    - 14 : Prescaler divides the prescaler clock by 32,768; glitch filter recognizes change on input pin after 16,384 rising clock edges.
 *                    - 15 : Prescaler divides the prescaler clock by 65,536; glitch filter recognizes change on input pin after 32,768 rising clock edges.
 */
__attribute__((always_inline)) static inline void LptmrReg_SetPrescaler(LptmrRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PSR;
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    tmp &= ~(LPTMR_PSR_PRESCALE_MASK);
    tmp |= (((uint32_t)(((uint32_t)(value)) << LPTMR_PSR_PRESCALE_SHIFT)) & LPTMR_PSR_PRESCALE_MASK);
    obj->PSR = tmp;
}

/*! \brief Get the Compare Value
 *
 * This function returns the current Compare Value.
 *
 * \param[in] obj : pointer to LPTMR register instance
 * \return the Compare Value
 */
__attribute__((always_inline)) static inline uint16_t LptmrReg_GetCompareValue(const LptmrRegType *obj)
{
    return ((obj->CMR & LPTMR_CMR_COMPARE_MASK) >> LPTMR_CMR_COMPARE_SHIFT);
}

/*! \brief Configure the Prescaler/Glitch Filter Bypass enable state
 *
 * This function configures the Compare Value. If set to 0, the Compare Match
 * event and the hardware trigger assert and remain asserted until the timer is
 * disabled.
 *
 * \note Must be altered only when the LPTMR is disabled.
 *
 * \param[in] obj : pointer to LPTMR register instance
 * \param[in] value : the new Compare Value
 */
__attribute__((always_inline)) static inline void LptmrReg_SetCompareValue(LptmrRegType *obj, uint16_t value)
{
    uint32_t tmp = obj->CMR;
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    tmp &= ~(LPTMR_CMR_COMPARE_MASK);
    tmp |= (((uint32_t)(((uint32_t)(value)) << LPTMR_CMR_COMPARE_SHIFT)) & LPTMR_CMR_COMPARE_MASK);
    obj->CMR = tmp;
}

/*! \brief Get the current Counter Value
 *
 * This function returns the Counter Value.
 * The CNR returns the current value of the LPTMR counter at the time this register was last written.
 * Cannot write directly.
 *
 * \param[in] obj : pointer to LPTMR register instance
 * \return the Counter Value
 */
__attribute__((always_inline)) static inline uint16_t LptmrReg_GetCounterValue(const LptmrRegType *obj)
{
    return ((obj->CNR & LPTMR_CNR_COUNTER_MASK) >> LPTMR_CNR_COUNTER_SHIFT);
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _LPTMR_REG_H_ */
