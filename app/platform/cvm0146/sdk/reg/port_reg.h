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

#ifndef _PORT_REG_H_
#define _PORT_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the PORT Registers
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

/* Length of PCR register array */
#define PORT_PCR_COUNT            (32U)

/* PCR Bit Fields */
#define PORT_PCR_ISF_MASK         (0x1000000u)
#define PORT_PCR_ISF_SHIFT        (24u)
#define PORT_PCR_ISF_WIDTH        (1u)
#define PORT_PCR_IRQ_CFG_MASK     (0xF0000u)
#define PORT_PCR_IRQ_CFG_SHIFT    (16u)
#define PORT_PCR_IRQ_CFG_WIDTH    (4u)
#define PORT_PCR_LOCK_MASK        (0x8000u)
#define PORT_PCR_LOCK_SHIFT       (15u)
#define PORT_PCR_LOCK_WIDTH       (1u)
#define PORT_PCR_FAST_MASK        (0x800u)
#define PORT_PCR_FAST_SHIFT       (11u)
#define PORT_PCR_FAST_WIDTH       (1u)
#define PORT_PCR_MUX_MASK         (0x700u)
#define PORT_PCR_MUX_SHIFT        (8u)
#define PORT_PCR_MUX_WIDTH        (3u)
#define PORT_PCR_ODE_MASK         (0x80u)
#define PORT_PCR_ODE_SHIFT        (7u)
#define PORT_PCR_ODE_WIDTH        (1u)
#define PORT_PCR_DRV_STR_MASK     (0x40u)
#define PORT_PCR_DRV_STR_SHIFT    (6u)
#define PORT_PCR_DRV_STR_WIDTH    (1u)
#define PORT_PCR_SR_MASK          (0x20u)
#define PORT_PCR_SR_SHIFT         (5u)
#define PORT_PCR_SR_WIDTH         (1u)
#define PORT_PCR_PAS_FLT_MASK     (0x10u)
#define PORT_PCR_PAS_FLT_SHIFT    (4u)
#define PORT_PCR_PAS_FLT_WIDTH    (1u)
#define PORT_PCR_AEN_MASK         (0x04u)
#define PORT_PCR_AEN_SHIFT        (2u)                                          
#define PORT_PCR_AEN_WIDTH        (1u)                                          
#define PORT_PCR_PDE_MASK         (0x02u)
#define PORT_PCR_PDE_SHIFT        (1u)
#define PORT_PCR_PDE_WIDTH        (1u)
#define PORT_PCR_PUE_MASK         (0x01u)
#define PORT_PCR_PUE_SHIFT        (0u)
#define PORT_PCR_PUE_WIDTH        (1u)

/* GPCLR Bit Fields */
#define PORT_GPCLR_LDAT_MASK      (0xFFFF0000u)
#define PORT_GPCLR_LDAT_SHIFT     (16u)
#define PORT_GPCLR_LDAT_WIDTH     (16u)
#define PORT_GPCLR_LWEN_MASK      (0xFFFFu)
#define PORT_GPCLR_LWEN_SHIFT     (0u)
#define PORT_GPCLR_LWEN_WIDTH     (16u)

/* GPCHR Bit Fields */
#define PORT_GPCHR_HDAT_MASK      (0xFFFF0000u)
#define PORT_GPCHR_HDAT_SHIFT     (16u)
#define PORT_GPCHR_HDAT_WIDTH     (16u)
#define PORT_GPCHR_HWEN_MASK      (0xFFFFu)
#define PORT_GPCHR_HWEN_SHIFT     (0u)
#define PORT_GPCHR_HWEN_WIDTH     (16u)

/* GICLR Bit Fields */
#define PORT_GICLR_INT_LDAT_MASK  (0xFFFF0000u)
#define PORT_GICLR_INT_LDAT_SHIFT (16u)
#define PORT_GICLR_INT_LDAT_WIDTH (16u)
#define PORT_GICLR_INT_LWEN_MASK  (0xFFFFu)
#define PORT_GICLR_INT_LWEN_SHIFT (0u)
#define PORT_GICLR_INT_LWEN_WIDTH (16u)

/* GICHR Bit Fields */
#define PORT_GICHR_INT_HDAT_MASK  (0xFFFF0000u)
#define PORT_GICHR_INT_HDAT_SHIFT (16u)
#define PORT_GICHR_INT_HDAT_WIDTH (16u)
#define PORT_GICHR_INT_HWEN_MASK  (0xFFFFu)
#define PORT_GICHR_INT_HWEN_SHIFT (0u)
#define PORT_GICHR_INT_HWEN_WIDTH (16u)

/* DFWR Bit Fields */
#define PORT_DFWR_LEN_MASK        (0x1Fu)
#define PORT_DFWR_LEN_SHIFT       (0u)
#define PORT_DFWR_LEN_WIDTH       (5u)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief The definition of PORT registers
 */
typedef struct _PortRegType_
{
    volatile uint32_t PCR[PORT_PCR_COUNT]; /*!< PORT control, offset: 0x00 */
    volatile uint32_t GPCLR;               /*!< Global Pin Control Low bits, offset: 0x80 */
    volatile uint32_t GPCHR;               /*!< Global pin control high bits, offset: 0x84 */
    volatile uint32_t GICLR;               /*!< Global Interrupt Control Low, offset: 0x88 */
    volatile uint32_t GICHR;               /*!< Global Interrupt Control High, offset: 0x8C */
    uint32_t          RESERVED1[4];        /*!< Reserved registers, offset: 0x90 */
    volatile uint32_t ISFR;                /*!< Interrupt Status Flag, offset: 0xA0 */
    uint32_t          RESERVED2[7];        /*!< Reserved registers, offset: 0xA4 */
    volatile uint32_t DFER;                /*!< Digital Filter Enable, offset: 0xC0 */
    uint32_t          RESERVED3;           /*!< Reserved register, offset: 0xC4 */
    volatile uint32_t DFWR;                /*!< Digital Filter Width, offset: 0xC8 */
} PortRegType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Gets the Interrupt Status Flag
 *
 * This function gets the current Interrupt Status Flag.
 * The pin interrupt configuration is valid in all digital pin muxing modes.
 *
 * \note If the pin is configured to generate a DMA request,
 *       then the corresponding flag will be cleared automatically at the completion of the requested DMA transfer.
 *       Otherwise, the flag remains set until a logic 1 is written to the flag.
 *       If the pin is configured for a level sensitive interrupt and the pin remains asserted,
 *       then the flag is set again immediately after it is cleared.
 *
 * \param[in] obj : pointer to PORT register instance
 * \param[in] pin : pin number
 * \return Interrupt Status Flag
 *         - 0b : Configured interrupt is not detected.
 *         - 1b : Configured interrupt is detected.
 */
__attribute__((always_inline)) static inline uint8_t PortReg_GetPcrIsf(const PortRegType *obj, uint32_t pin)
{
    return ((obj->PCR[pin] & PORT_PCR_ISF_MASK) >> PORT_PCR_ISF_SHIFT);
}

/*! \brief Sets the Interrupt Status Flag
 *
 * This function sets the Interrupt Status Flag.
 * The pin interrupt configuration is valid in all digital pin muxing modes.
 *
 * \note If the pin is configured to generate a DMA request,
 *       then the corresponding flag will be cleared automatically at the completion of the requested DMA transfer.
 *       Otherwise, the flag remains set until a logic 1 is written to the flag.
 *       If the pin is configured for a level sensitive interrupt and the pin remains asserted,
 *       then the flag is set again immediately after it is cleared.
 *
 * \param[in] obj : pointer to PORT register instance
 * \param[in] pin : pin number
 * \param[in] value : the value of Interrupt Status Flag
 *                    - 0b : Configured interrupt is not detected.
 *                    - 1b : Configured interrupt is detected.
 */
__attribute__((always_inline)) static inline void PortReg_SetPcrIsf(PortRegType *obj, uint32_t pin, uint8_t value)
{
    uint32_t tmp = obj->PCR[pin];

    tmp &= ~PORT_PCR_ISF_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PORT_PCR_ISF_SHIFT)) & PORT_PCR_ISF_MASK);
    obj->PCR[pin] = tmp;
    /* Read back to avoid problem */
    (void)obj->PCR[pin];
}

/*! \brief Gets the Interrupt Configuration
 *
 * This function gets the current Interrupt Configuration.
 * The pin interrupt configuration is valid in all digital pin muxing modes.
 *
 * \param[in] obj : pointer to PORT register instance
 * \param[in] pin : pin number
 * \return Interrupt Configuration
 *         - 0000b : Interrupt Status Flag (ISF) is disabled.
 *         - 0001b : ISF flag and DMA request on rising edge.
 *         - 0010b : ISF flag and DMA request on falling edge.
 *         - 0011b : ISF flag and DMA request on either edge.
 *         - 0100b : Reserved.
 *         - 0101b : Reserved.
 *         - 0110b : Reserved.
 *         - 0111b : Reserved.
 *         - 1000b : ISF flag and Interrupt when logic 0.
 *         - 1001b : ISF flag and Interrupt on rising-edge.
 *         - 1010b : ISF flag and Interrupt on falling-edge.
 *         - 1011b : ISF flag and Interrupt on either edge.
 *         - 1100b : ISF flag and Interrupt when logic 1.
 *         - 1101b : Reserved.
 *         - 1110b : Reserved.
 *         - 1111b : Reserved
 */
__attribute__((always_inline)) static inline uint8_t PortReg_GetPcrIrqCfg(const PortRegType *obj, uint32_t pin)
{
    return ((obj->PCR[pin] & PORT_PCR_IRQ_CFG_MASK) >> PORT_PCR_IRQ_CFG_SHIFT);
}

/*! \brief Sets the Interrupt Configuration
 *
 * This function sets the Interrupt Configuration.
 * The pin interrupt configuration is valid in all digital pin muxing modes.
 *
 * \param[in] obj : pointer to PORT register instance
 * \param[in] pin : pin number
 * \param[in] value : the value of Interrupt Configuration
 *                    - 0000b : Interrupt Status Flag (ISF) is disabled.
 *                    - 0001b : ISF flag and DMA request on rising edge.
 *                    - 0010b : ISF flag and DMA request on falling edge.
 *                    - 0011b : ISF flag and DMA request on either edge.
 *                    - 0100b : Reserved.
 *                    - 0101b : Reserved.
 *                    - 0110b : Reserved.
 *                    - 0111b : Reserved.
 *                    - 1000b : ISF flag and Interrupt when logic 0.
 *                    - 1001b : ISF flag and Interrupt on rising-edge.
 *                    - 1010b : ISF flag and Interrupt on falling-edge.
 *                    - 1011b : ISF flag and Interrupt on either edge.
 *                    - 1100b : ISF flag and Interrupt when logic 1.
 *                    - 1101b : Reserved.
 *                    - 1110b : Reserved.
 *                    - 1111b : Reserved
 */
__attribute__((always_inline)) static inline void PortReg_SetPcrIrqCfg(PortRegType *obj, uint32_t pin, uint8_t value)
{
    uint32_t tmp = obj->PCR[pin];

    tmp &= ~PORT_PCR_IRQ_CFG_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PORT_PCR_IRQ_CFG_SHIFT)) & PORT_PCR_IRQ_CFG_MASK);
    obj->PCR[pin] = tmp;
}

/*! \brief Gets the Lock Register
 *
 * This function gets the current Lock Register.
 *
 * \param[in] obj : pointer to PORT register instance
 * \param[in] pin : pin number
 * \return Lock Register
 *         - 0b : Pin Control Register fields [15:0] are not locked.
 *         - 1b : Pin Control Register fields [15:0] are locked and cannot be updated until the next system reset
 */
__attribute__((always_inline)) static inline uint8_t PortReg_GetPcrLock(const PortRegType *obj, uint32_t pin)
{
    return ((obj->PCR[pin] & PORT_PCR_LOCK_MASK) >> PORT_PCR_LOCK_SHIFT);
}

/*! \brief Sets the Lock Register
 *
 * This function sets the Lock Register.
 *
 * \param[in] obj : pointer to PORT register instance
 * \param[in] pin : pin number
 * \param[in] value : the value of Lock Register
 *                    - 0b : Pin Control Register fields [15:0] are not locked.
 *                    - 1b : Pin Control Register fields [15:0] are locked and cannot be updated until the next system reset
 */
__attribute__((always_inline)) static inline void PortReg_SetPcrLock(PortRegType *obj, uint32_t pin, uint8_t value)
{
    uint32_t tmp = obj->PCR[pin];

    tmp &= ~PORT_PCR_LOCK_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PORT_PCR_LOCK_SHIFT)) & PORT_PCR_LOCK_MASK);
    obj->PCR[pin] = tmp;
}

/*! \brief Gets the FAST mode
 *
 * This function gets the current FAST mode.
 *
 * \param[in] obj : pointer to PORT register instance
 * \param[in] pin : pin number
 * \return FAST mode
 *         - 0b : low speed
 *         - 1b : high speed
 */
__attribute__((always_inline)) static inline uint8_t PortReg_GetPcrFast(const PortRegType *obj, uint32_t pin)
{
    return ((obj->PCR[pin] & PORT_PCR_FAST_MASK) >> PORT_PCR_FAST_SHIFT);
}

/*! \brief Sets the FAST mode
 *
 * This function sets the FAST mode.
 *
 * \param[in] obj : pointer to PORT register instance
 * \param[in] pin : pin number
 * \param[in] value : the value of FAST mode
 *                    - 0b : low speed
 *                    - 1b : high speed
 */
__attribute__((always_inline)) static inline void PortReg_SetPcrFast(PortRegType *obj, uint32_t pin, uint8_t value)
{
    uint32_t tmp = obj->PCR[pin];

    tmp &= ~PORT_PCR_FAST_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PORT_PCR_FAST_SHIFT)) & PORT_PCR_FAST_MASK);
    obj->PCR[pin] = tmp;
}

/*! \brief Gets the Pin Mux Control
 *
 * This function gets the current Pin Mux Control.
 * Not all pins support all pin muxing slots.
 * Unimplemented pin muxing slots are reserved and may result in configuring the pin for a different pin muxing slot.
 *
 * \param[in] obj : pointer to PORT register instance
 * \param[in] pin : pin number
 * \return Pin Mux Control
 *         - 000b : Pin disabled (Alternative 0) (analog).
 *         - 001b : Alternative 1 (GPIO).
 *         - 010b : Alternative 2 (chip-specific).
 *         - 011b : Alternative 3 (chip-specific).
 *         - 100b : Alternative 4 (chip-specific).
 *         - 101b : Alternative 5 (chip-specific).
 *         - 110b : Alternative 6 (chip-specific).
 *         - 111b : Alternative 7 (chip-specific)
 */
__attribute__((always_inline)) static inline uint8_t PortReg_GetPcrMux(const PortRegType *obj, uint32_t pin)
{
    return ((obj->PCR[pin] & PORT_PCR_MUX_MASK) >> PORT_PCR_MUX_SHIFT);
}

/*! \brief Sets the Pin Mux Control
 *
 * This function sets the Pin Mux Control.
 * Not all pins support all pin muxing slots.
 * Unimplemented pin muxing slots are reserved and may result in configuring the pin for a different pin muxing slot.
 *
 * \param[in] obj : pointer to PORT register instance
 * \param[in] pin : pin number
 * \param[in] value : the value of Pin Mux Control
 *                    - 000b : Pin disabled (Alternative 0) (analog).
 *                    - 001b : Alternative 1 (GPIO).
 *                    - 010b : Alternative 2 (chip-specific).
 *                    - 011b : Alternative 3 (chip-specific).
 *                    - 100b : Alternative 4 (chip-specific).
 *                    - 101b : Alternative 5 (chip-specific).
 *                    - 110b : Alternative 6 (chip-specific).
 *                    - 111b : Alternative 7 (chip-specific)
 */
__attribute__((always_inline)) static inline void PortReg_SetPcrMux(PortRegType *obj, uint32_t pin, uint8_t value)
{
    uint32_t tmp = obj->PCR[pin];

    tmp &= ~PORT_PCR_MUX_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PORT_PCR_MUX_SHIFT)) & PORT_PCR_MUX_MASK);
    obj->PCR[pin] = tmp;
}

/*! \brief Gets the Open drain enable
 *
 * This function gets the current Open drain enable.
 *
 * \param[in] obj : pointer to PORT register instance
 * \param[in] pin : pin number
 * \return Open drain enable
 *         - 0b : push pull
 *         - 1b : open drain
 */
__attribute__((always_inline)) static inline uint8_t PortReg_GetPcrOde(const PortRegType *obj, uint32_t pin)
{
    return ((obj->PCR[pin] & PORT_PCR_ODE_MASK) >> PORT_PCR_ODE_SHIFT);
}

/*! \brief Sets the Open drain enable
 *
 * This function sets the Open drain enable.
 *
 * \param[in] obj : pointer to PORT register instance
 * \param[in] pin : pin number
 * \param[in] value : the value of Open drain enable
 *                    - 0b : push pull
 *                    - 1b : open drain
 */
__attribute__((always_inline)) static inline void PortReg_SetPcrOde(PortRegType *obj, uint32_t pin, uint8_t value)
{
    uint32_t tmp = obj->PCR[pin];

    tmp &= ~PORT_PCR_ODE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PORT_PCR_ODE_SHIFT)) & PORT_PCR_ODE_MASK);
    obj->PCR[pin] = tmp;
}

/*! \brief Gets the Drive Strength Enable
 *
 * This function gets the current Drive Strength Enable.
 * Drive strength configuration is valid in all digital pin muxing modes.
 *
 * \param[in] obj : pointer to PORT register instance
 * \param[in] pin : pin number
 * \return Drive Strength Enable
 *         - 0b : Low drive strength is configured on the corresponding pin, if pin is configured as a digital output.
 *         - 1b : High drive strength is configured on the corresponding pin, if pin is configured as a digital output.
 */
__attribute__((always_inline)) static inline uint8_t PortReg_GetPcrDrvStr(const PortRegType *obj, uint32_t pin)
{
    return ((obj->PCR[pin] & PORT_PCR_DRV_STR_MASK) >> PORT_PCR_DRV_STR_SHIFT);
}

/*! \brief Sets the Drive Strength Enable
 *
 * This function sets the Drive Strength Enable.
 * Drive strength configuration is valid in all digital pin muxing modes.
 *
 * \param[in] obj : pointer to PORT register instance
 * \param[in] pin : pin number
 * \param[in] value : the value of Drive Strength Enable
 *                    - 0b : Low drive strength is configured on the corresponding pin, if pin is configured as a digital output.
 *                    - 1b : High drive strength is configured on the corresponding pin, if pin is configured as a digital output.
 */
__attribute__((always_inline)) static inline void PortReg_SetPcrDrvStr(PortRegType *obj, uint32_t pin, uint8_t value)
{
    uint32_t tmp = obj->PCR[pin];

    tmp &= ~PORT_PCR_DRV_STR_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PORT_PCR_DRV_STR_SHIFT)) & PORT_PCR_DRV_STR_MASK);
    obj->PCR[pin] = tmp;
}

/*! \brief Gets the slew rate
 *
 * This function gets the current slew rate.
 *
 * \param[in] obj : pointer to PORT register instance
 * \param[in] pin : pin number
 * \return slew rate
 *         - 0b : slow slew rate
 *         - 1b : fast slew rate
 */
__attribute__((always_inline)) static inline uint8_t PortReg_GetPcrSr(const PortRegType *obj, uint32_t pin)
{
    return ((obj->PCR[pin] & PORT_PCR_SR_MASK) >> PORT_PCR_SR_SHIFT);
}

/*! \brief Sets the slew rate
 *
 * This function sets the slew rate.
 *
 * \param[in] obj : pointer to PORT register instance
 * \param[in] pin : pin number
 * \param[in] value : the value of slew rate
 *                    - 0b : slow slew rate
 *                    - 1b : fast slew rate
 */
__attribute__((always_inline)) static inline void PortReg_SetPcrSr(PortRegType *obj, uint32_t pin, uint8_t value)
{
    uint32_t tmp = obj->PCR[pin];

    tmp &= ~PORT_PCR_SR_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PORT_PCR_SR_SHIFT)) & PORT_PCR_SR_MASK);
    obj->PCR[pin] = tmp;
}

/*! \brief Gets the Passive Filter Enable
 *
 * This function gets the current Passive Filter Enable.
 * Passive filter configuration is valid in all digital pin muxing modes.
 *
 * \param[in] obj : pointer to PORT register instance
 * \param[in] pin : pin number
 * \return Passive Filter Enable
 *         - 0b : Passive input filter is disabled on the corresponding pin.
 *         - 1b : Passive input filter is enabled on the corresponding pin, if the pin is configured as a digital input.
 */
__attribute__((always_inline)) static inline uint8_t PortReg_GetPcrPasFlt(const PortRegType *obj, uint32_t pin)
{
    return ((obj->PCR[pin] & PORT_PCR_PAS_FLT_MASK) >> PORT_PCR_PAS_FLT_SHIFT);
}

/*! \brief Sets the Passive Filter Enable
 *
 * This function sets the Passive Filter Enable.
 * Passive filter configuration is valid in all digital pin muxing modes.
 *
 * \param[in] obj : pointer to PORT register instance
 * \param[in] pin : pin number
 * \param[in] value : the value of Passive Filter Enable
 *                    - 0b : Passive input filter is disabled on the corresponding pin.
 *                    - 1b : Passive input filter is enabled on the corresponding pin, if the pin is configured as a digital input.
 */
__attribute__((always_inline)) static inline void PortReg_SetPcrPasFlt(PortRegType *obj, uint32_t pin, uint8_t value)
{
    uint32_t tmp = obj->PCR[pin];

    tmp &= ~PORT_PCR_PAS_FLT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PORT_PCR_PAS_FLT_SHIFT)) & PORT_PCR_PAS_FLT_MASK);
    obj->PCR[pin] = tmp;
}

/*! \brief Gets the Analog mode enable
 *
 * This function gets the current Analog mode enable.
 *
 * \param[in] obj : pointer to PORT register instance
 * \param[in] pin : pin number
 * \return Analog mode enable
 *         - 0b : analog mode is disabled on the corresponding pin
 *         - 1b : analog mode is enabled on the corresponding pin
 */
__attribute__((always_inline)) static inline uint8_t PortReg_GetPcrAen(const PortRegType *obj, uint32_t pin)
{
    return ((obj->PCR[pin] & PORT_PCR_AEN_MASK) >> PORT_PCR_AEN_SHIFT);
}

/*! \brief Sets the Analog mode enable
 *
 * This function sets the Analog mode enable.
 *
 * \param[in] obj : pointer to PORT register instance
 * \param[in] pin : pin number
 * \param[in] value : the value of Analog mode enable
 *                    - 0b : analog mode is disabled on the corresponding pin
 *                    - 1b : analog mode is enabled on the corresponding pin
 */
__attribute__((always_inline)) static inline void PortReg_SetPcrAen(PortRegType *obj, uint32_t pin, uint8_t value)
{
    uint32_t tmp = obj->PCR[pin];

    tmp &= ~PORT_PCR_AEN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PORT_PCR_AEN_SHIFT)) & PORT_PCR_AEN_MASK);
    obj->PCR[pin] = tmp;
}

/*! \brief Gets the Pull down enable
 *
 * This function gets the current Pull down enable.
 * Pull configuration is valid in all digital pin muxing modes.
 *
 * \param[in] obj : pointer to PORT register instance
 * \param[in] pin : pin number
 * \return Pull down enable
 *         - 0b : Internal pulldown resistor is disabled
 *         - 1b : Internal pulldown resistor is enabled
 */
__attribute__((always_inline)) static inline uint8_t PortReg_GetPcrPde(const PortRegType *obj, uint32_t pin)
{
    return ((obj->PCR[pin] & PORT_PCR_PDE_MASK) >> PORT_PCR_PDE_SHIFT);
}

/*! \brief Sets the Pull down enable
 *
 * This function sets the Pull down enable.
 * Pull configuration is valid in all digital pin muxing modes.
 *
 * \param[in] obj : pointer to PORT register instance
 * \param[in] pin : pin number
 * \param[in] value : the value of Pull down enable
 *                    - 0b : Internal pulldown resistor is disabled
 *                    - 1b : Internal pulldown resistor is enabled
 */
__attribute__((always_inline)) static inline void PortReg_SetPcrPde(PortRegType *obj, uint32_t pin, uint8_t value)
{
    uint32_t tmp = obj->PCR[pin];

    tmp &= ~PORT_PCR_PDE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PORT_PCR_PDE_SHIFT)) & PORT_PCR_PDE_MASK);
    obj->PCR[pin] = tmp;
}

/*! \brief Gets the Pull up enable
 *
 * This function gets the current Pull up enable.
 * Pull configuration is valid in all digital pin muxing modes.
 *
 * \param[in] obj : pointer to PORT register instance
 * \param[in] pin : pin number
 * \return Pull up enable
 *         - 0b : Internal pullup resistor is disabled
 *         - 1b : Internal pullup resistor is enabled
 */
__attribute__((always_inline)) static inline uint8_t PortReg_GetPcrPue(const PortRegType *obj, uint32_t pin)
{
    return ((obj->PCR[pin] & PORT_PCR_PUE_MASK) >> PORT_PCR_PUE_SHIFT);
}

/*! \brief Sets the Pull up enable
 *
 * This function sets the Pull up enable.
 * Pull configuration is valid in all digital pin muxing modes.
 *
 * \param[in] obj : pointer to PORT register instance
 * \param[in] pin : pin number
 * \param[in] value : the value of Pull up enable
 *                    - 0b : Internal pullup resistor is disabled
 *                    - 1b : Internal pullup resistor is enabled
 */
__attribute__((always_inline)) static inline void PortReg_SetPcrPue(PortRegType *obj, uint32_t pin, uint8_t value)
{
    uint32_t tmp = obj->PCR[pin];

    tmp &= ~PORT_PCR_PUE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PORT_PCR_PUE_SHIFT)) & PORT_PCR_PUE_MASK);
    obj->PCR[pin] = tmp;
}

/*! \brief Sets the Global Pin Control register low 16 bits
 *
 * This function sets the Global Pin Control register low 16 bits
 * Write value that is written to all Pin Control Registers bits [15:0] that are selected by GPWE
 *
 * \param[in] obj : pointer to PORT register instance
 * \param[in] value : the value of Global Pin Write Data and write Enable
 */
__attribute__((always_inline)) static inline void PortReg_SetGpclr(PortRegType *obj, uint32_t value)
{
    obj->GPCLR = value;
}

/*! \brief Sets the global Pin Control register high 16 bits
 *
 * This function sets the global Pin Control register high 16 bits.
 * Write value that is written to all Pin Control Registers bits [15:0] that are selected by GPWE
 *
 * \param[in] obj : pointer to PORT register instance
 * \param[in] value : the value of global write data and write enable
 */
__attribute__((always_inline)) static inline void PortReg_SetGpchr(PortRegType *obj, uint32_t value)
{
    obj->GPCHR = value;
}

/*! \brief Sets the Global Interrupt register low 16 bits
 *
 * This function sets the Global Interrupt register low 16 bits.
 * Write value that is written to all Pin Control Registers bits [31:16] that are selected by [15:0]
 *
 * \param[in] obj : pointer to PORT register instance
 * \param[in] value : the value of Global Interrupt write data and write enable
 */
__attribute__((always_inline)) static inline void PortReg_SetGiclrInt(PortRegType *obj, uint32_t value)
{
    obj->GICLR = value;
}

/*! \brief Sets the Global Interrupt register high 16 bits
 *
 * This function sets the Global Interrupt register high 16 bits.
 * Write value that is written to all Pin Control Registers bits [31:16] that are selected by [15:0]
 *
 * \param[in] obj : pointer to PORT register instance
 * \param[in] value : the value of Global Interrupt write data and enable
 */
__attribute__((always_inline)) static inline void PortReg_SetGichrInt(PortRegType *obj, uint32_t value)
{
    obj->GICHR = value;
}

/*! \brief Gets the Interrupt Status Flag
 *
 * This function gets the current Interrupt Status Flag.
 * Each bit in the field indicates the detection of the configured interrupt of the same number as the field.
 *
 * \note If the pin is configured to generate a DMA request,
 *       then the corresponding flag will be cleared automatically at the completion of the requested DMA transfer.
 *       Otherwise, the flag remains set until a logic 1 is written to the flag.
 *       If the pin is configured for a level sensitive interrupt and the pin remains asserted,
 *       then the flag is set again immediately after it is cleared.
 *
 * \param[in] obj : pointer to PORT register instance
 * \return Interrupt Status Flag
 *         - 0b : Configured interrupt is not detected.
 *         - 1b : Configured interrupt is detected.
 */
__attribute__((always_inline)) static inline uint32_t PortReg_GetIsfrIsf(const PortRegType *obj)
{
    return obj->ISFR;
}

/*! \brief Sets the Interrupt Status Flag
 *
 * This function sets the Interrupt Status Flag.
 * Each bit in the field indicates the detection of the configured interrupt of the same number as the field.
 *
 * \note If the pin is configured to generate a DMA request,
 *       then the corresponding flag will be cleared automatically at the completion of the requested DMA transfer.
 *       Otherwise, the flag remains set until a logic 1 is written to the flag.
 *       If the pin is configured for a level sensitive interrupt and the pin remains asserted,
 *       then the flag is set again immediately after it is cleared.
 *
 * \param[in] obj : pointer to PORT register instance
 * \param[in] value : the value of Interrupt Status Flag
 *                    - 0b : corresponding interrupt is not cleared.
 *                    - 1b : corresponding interrupt is cleared.
 */
__attribute__((always_inline)) static inline void PortReg_SetIsfrIsf(PortRegType *obj, uint32_t value)
{
    obj->ISFR = value;
    /* Read back to avoid problem */
    (void)obj->ISFR;
}

/*! \brief Gets the Digital Filter Enable
 *
 * This function gets the current Digital Filter Enable.
 * The digital filter configuration is valid in all digital pin muxing modes.
 * The output of each digital filter is reset to zero at system reset and whenever the digital filter is disabled.
 * Each bit in the field enables the digital filter of the same number as the field.
 *
 * \param[in] obj : pointer to PORT register instance
 * \return Digital Filter Enable
 *         - 0b : Digital filter is disabled on the corresponding pin and output of the digital filter is reset to zero.
 *         - 1b : Digital filter is enabled on the corresponding pin, if the pin is configured as a digital input.
 */
__attribute__((always_inline)) static inline uint32_t PortReg_GetDferEn(const PortRegType *obj)
{
    return obj->DFER;
}

/*! \brief Sets the Digital Filter Enable
 *
 * This function sets the Digital Filter Enable.
 * The digital filter configuration is valid in all digital pin muxing modes.
 * The output of each digital filter is reset to zero at system reset and whenever the digital filter is disabled.
 * Each bit in the field enables the digital filter of the same number as the field.
 *
 * \param[in] obj : pointer to PORT register instance
 * \param[in] value : the value of Digital Filter Enable
 *                    - 0b : Digital filter is disabled on the corresponding pin and output of the digital filter is reset to zero.
 *                    - 1b : Digital filter is enabled on the corresponding pin, if the pin is configured as a digital input.
 */
__attribute__((always_inline)) static inline void PortReg_SetDferEn(PortRegType *obj, uint32_t value)
{
    obj->DFER = value;
}

/*! \brief Gets the Filter Length
 *
 * This function gets the current Filter Length.
 * The digital filter configuration is valid in all digital pin muxing modes.
 * Configures the maximum size of the glitches, in clock cycles,
 * that the digital filter absorbs for the enabled digital filters.
 * Glitches that are longer than this register setting will pass through the digital filter,
 * and glitches that are equal to or less than this register setting are filtered.
 * Changing the filter length must be done only after all filters are disable
 *
 * \param[in] obj : pointer to PORT register instance
 * \return Filter Length
 */
__attribute__((always_inline)) static inline uint8_t PortReg_GetDfwrLen(const PortRegType *obj)
{
    return ((obj->DFWR & PORT_DFWR_LEN_MASK) >> PORT_DFWR_LEN_SHIFT);
}

/*! \brief Sets the Filter Length
 *
 * This function sets the Filter Length.
 * The digital filter configuration is valid in all digital pin muxing modes.
 * Configures the maximum size of the glitches, in clock cycles,
 * that the digital filter absorbs for the enabled digital filters.
 * Glitches that are longer than this register setting will pass through the digital filter,
 * and glitches that are equal to or less than this register setting are filtered.
 * Changing the filter length must be done only after all filters are disable
 *
 * \param[in] obj : pointer to PORT register instance
 * \param[in] value : the value of Filter Length
 */
__attribute__((always_inline)) static inline void PortReg_SetDfwrLen(PortRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->DFWR;

    tmp &= ~PORT_DFWR_LEN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PORT_DFWR_LEN_SHIFT)) & PORT_DFWR_LEN_MASK);
    obj->DFWR = tmp;
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _PORT_REG_H_ */
