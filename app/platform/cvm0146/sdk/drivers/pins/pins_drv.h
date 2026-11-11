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

#ifndef _PINS_DRV_H_
#define _PINS_DRV_H_

/*! \brief Contains public interface to various functions related
 *         to the driver of pins
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/*! \addtogroup pins_drv
 *  @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * the defines
 ******************************************************************************/

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief Internal resistor pull feature selection
 */
typedef enum
{
    PINSDRV_INTERNAL_NO_PULL   = 0x00U, /*!< Internal pull-down or pull-up resistor is not enabled */
    PINSDRV_INTERNAL_PULL_DOWN = 0x01U, /*!< Internal pull-down resistor is enabled */
    PINSDRV_INTERNAL_PULL_UP   = 0x02U, /*!< Internal pull-up resistor is enabled */
} PinsDrv_InternalPullModeType;

/*! \brief Configures the Pin mux selection
 */
typedef enum
{
    PINSDRV_PIN_DISABLED = 0U, /*!< corresponding pin is disabled, but is used as an analog pin       */
    PINSDRV_MUX_AS_GPIO  = 1U, /*!< corresponding pin is configured as GPIO                           */
    PINSDRV_MUX_ALT2     = 2U, /*!< chip-specific                                                     */
    PINSDRV_MUX_ALT3     = 3U, /*!< chip-specific                                                     */
    PINSDRV_MUX_ALT4     = 4U, /*!< chip-specific                                                     */
    PINSDRV_MUX_ALT5     = 5U, /*!< chip-specific                                                     */
    PINSDRV_MUX_ALT6     = 6U, /*!< chip-specific                                                     */
    PINSDRV_MUX_ALT7     = 7U, /*!< chip-specific                                                     */
} PinsDrv_MuxType;

/*! \brief Configures the interrupt generation condition.
 */
typedef enum
{
    PINSDRV_DMA_INT_DISABLED = 0x0U, /*!< Interrupt/DMA request is disabled. */
    PINSDRV_DMA_RISING_EDGE  = 0x1U, /*!< DMA request on rising edge. */
    PINSDRV_DMA_FALLING_EDGE = 0x2U, /*!< DMA request on falling edge. */
    PINSDRV_DMA_EITHER_EDGE  = 0x3U, /*!< DMA request on either edge. */
    PINSDRV_INT_LOGIC_ZERO   = 0x8U, /*!< Interrupt when logic 0. */
    PINSDRV_INT_RISING_EDGE  = 0x9U, /*!< Interrupt on rising edge. */
    PINSDRV_INT_FALLING_EDGE = 0xAU, /*!< Interrupt on falling edge. */
    PINSDRV_INT_EITHER_EDGE  = 0xBU, /*!< Interrupt on either edge. */
    PINSDRV_INT_LOGIC_ONE    = 0xCU, /*!< Interrupt when logic 1. */
    PINSDRV_DMA_INT_RESERVED = 0xFU, /*!< reserved. */
} PinsDrv_InterruptConfigType;

/*! \brief The digital filter configuration
 */
typedef struct
{
    uint8_t width; /*!< The digital filter width value */
} PinsDrv_FilterConfigType;

/*! \brief The port global pin/interuppt control registers
 */
typedef enum
{
    PINDRV_GLOBAL_CONTROL_LOWER_HALF_PINS = 0U, /*!< the lower of pins is configured */
    PINDRV_GLOBAL_CONTROL_UPPER_HALF_PINS = 1U  /*!< the upper of pins is configured */
} PinsDrv_GlobalControlPinsType;

/* Forward declaration of PORT register */
struct _PortRegType_;
/* Forward declaration of PORT register */
struct _GpioRegType_;

/*! \brief The definition of pins driver class
 */
typedef struct _PinsDrvType_
{
    struct _PortRegType_ *port; /*!< pointer to the port register */
    struct _GpioRegType_ *gpio; /*!< pointer to the gpio register */
} PinsDrvType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Initializes the pins driver module
 *
 * This function initializes pins driver by setting the register
 * instance to it.
 *
 * \param[in] obj : pointer to pins driver instance
 * \param[in] port : pointer to PORT register instance
 * \param[in] gpio : pointer to GPIO register instance
 * \param[in] func : the function of setting digital filter clock
 */
extern void PinsDrv_Init(PinsDrvType *obj, struct _PortRegType_ *port, struct _GpioRegType_ *gpio);

/*! \brief Configures the internal resistor.
 *
 * This function configures the internal resistor.
 *
 * \param[in] obj : pointer to pins driver instance
 * \param[in] pin : pin number
 * \param[in] pullMode : the pull mode
 */
extern void PinsDrv_SetPullSel(PinsDrvType *obj, uint32_t pin, PinsDrv_InternalPullModeType pullMode);

/*! \brief Configures the pin muxing.
 *
 * This function configures the pin muxing.
 *
 * \param[in] obj : pointer to pins driver instance
 * \param[in] pin : pin number
 * \param[in] mux : Pin muxing slot selection
 */
extern void PinsDrv_SetMuxModeSel(PinsDrvType *obj, uint32_t pin, PinsDrv_MuxType mux);

/*! \brief Configures the port pin interrupt/DMA request.
 *
 * This function configures the port pin interrupt/DMA request.
 *
 * \param[in] obj : pointer to pins driver instance
 * \param[in] pin : pin number
 * \param[in] intConfig : Interrupt configuration
 */
extern void PinsDrv_SetPinIntSel(PinsDrvType *obj, uint32_t pin, PinsDrv_InterruptConfigType intConfig);

/*! \brief Gets the current port pin interrupt/DMA request configuration.
 *
 * This function gets the current port pin interrupt/DMA request configuration.
 *
 * \param[in] obj : pointer to pins driver instance
 * \param[in] pin : pin number
 * \return Interrupt configuration
 */
extern PinsDrv_InterruptConfigType PinsDrv_GetPinIntSel(const PinsDrvType *obj, uint32_t pin);

/*! \brief Clears the individual pin-interrupt status flag.
 *
 * This function clears the individual pin-interrupt status flag.
 *
 * \param[in] obj : pointer to pins driver instance
 * \param[in] pin : pin number
 */
extern void PinsDrv_ClearPinIntFlagCmd(PinsDrvType *obj, uint32_t pin);

/*! \brief Enables digital filter for digital pin muxing
 *
 * This function enables digital filter feature for digital pin muxing
 *
 * \param[in] obj : pointer to pins driver instance
 * \param[in] pin : pin number
 */
extern void PinsDrv_EnableDigitalFilter(PinsDrvType *obj, uint32_t pin);

/*! \brief Disables digital filter for digital pin muxing
 *
 * This function disables digital filter feature for digital pin muxing
 *
 * \param[in] obj : pointer to pins driver instance
 * \param[in] pin : pin number
 */
extern void PinsDrv_DisableDigitalFilter(PinsDrvType *obj, uint32_t pin);

/*! \brief Configures digital filter for port with given configuration
 *
 * This function configures digital filter for port with given configuration.
 *
 * User should configure the port filter clock first with the clock module.
 *
 * \note Updating the filter configuration must be done only after all filters are disabled.
 *
 * \param[in] obj : pointer to pins driver instance
 * \param[in] config : the digital filter configuration struct
 */
extern void PinsDrv_ConfigDigitalFilter(PinsDrvType *obj, const PinsDrv_FilterConfigType *config);

/*! \brief Reads the entire port interrupt status flag
 *
 * This function reads the entire port interrupt status flag.
 *
 * \param[in] obj : pointer to pins driver instance
 * \return All 32 pin interrupt status flags
 */
extern uint32_t PinsDrv_GetPortIntFlag(const PinsDrvType *obj);

/*! \brief Clears the entire port interrupt status flag.
 *
 * This function clears the entire port interrupt status flag.
 *
 * \param[in] obj : pointer to pins driver instance
 */
extern void PinsDrv_ClearPortIntFlagCmd(PinsDrvType *obj);

/*! \brief Sets PCR of corresponding pins to floating state(value = 0) .
 *
 * This function sets PCR of corresponding pins to floating state(value = 0)
 * \param[in] obj : pointer to pins driver instance
 * \param[in] pins : Pin mask, each bit corresponding one pin. For each bit:
 *                   - 0 : the PCR of the corresponding pins will not be updated
 *                   - 1 : the PCR of the corresponding pins will be updated as 0
 */
extern void PinsDrv_SetPinsFloating(PinsDrvType *obj, uint16_t pins);

/*! \brief Quickly configures multiple pins with the same pin configuration.
 *
 * This function quickly configures multiple pins within the one port for the same peripheral
 * function with the same pin configuration. Supports up to 16 pins with the lower or upper
 * half of pin registers at the same port.
 *
 * \note The set global interrupt control function (PinsDrv_SetGlobalIntControl) cannot be
 *       configured if you ever used this function at the same port
 *
 * \param[in] obj : pointer to pins driver instance
 * \param[in] pins : Pin mask where each bit represents one pin. For each bit:
 *                   - 0 : pins corresponding to bits with value of '1' is updated with the value input
 *                   - 1 : pins corresponding to bits with value of '0' is not updated with the value input
 * \param[in] value : the config value will be updated for the pins are set to '1'
 * \param[in] whichHalf : the lower or upper half of pin registers at the same port
 */
extern void PinsDrv_SetGlobalPinControl(PinsDrvType *obj, uint16_t pins, uint16_t value, PinsDrv_GlobalControlPinsType whichHalf);

/*! \brief Quickly configures multiple pins with the same interrupt configuration.
 *
 * This function quickly configures multiple pins within the one port for the same peripheral
 * function with the same interrupt configuration. Supports up to 16 pins with the lower or
 * upper half of pin registers at the same port.
 *
 * \note The set global pin control function (PinsDrv_SetGlobalPinControl) cannot be
 *       configured if you ever used this function at the same port
 *
 * \param[in] obj : pointer to pins driver instance
 * \param[in] pins : Pin mask where each bit represents one pin. For each bit:
 *                   - 0 : pins corresponding to bits with value of '1' is updated with the value input
 *                   - 1 : pins corresponding to bits with value of '0' is not updated with the value input
 * \param[in] value : the config value will be updated for the pins are set to '1'
 * \param[in] whichHalf : the lower or upper half of pin registers at the same port
 */
extern void PinsDrv_SetGlobalIntControl(PinsDrvType *obj, uint16_t pins, uint16_t value, PinsDrv_GlobalControlPinsType whichHalf);

/*! \brief Get the pins directions configuration for a port
 *
 * This function returns the current pins directions for a port. Pins
 * corresponding to bits with value of '1' are configured as output and
 * pins corresponding to bits with value of '0' are configured as input.
 *
 * \param[in] obj : pointer to pins driver instance
 * \return GPIO directions. Each bit represents one pin (LSB is pin 0, MSB is pin 31).
 *         For each bit:
 *         - 0 : corresponding pin is set to input
 *         - 1 : corresponding pin is set to output
 */
extern uint32_t PinsDrv_GetPinsDirection(const PinsDrvType *obj);

/*! \brief Configure the direction for a certain pin from a port
 *
 * This function configures the direction for the given pin, with the
 * given value('1' for pin to be configured as output and '0' for pin to
 * be configured as input)
 *
 * \note With some platforms when you want to set a pin as output only and disable
 *       input completely, it is required to call PinsDrv_SetPortInputDisable if platform
 *       has this feature.
 *
 * \param[in] obj : pointer to pins driver instance
 * \param[in] pin : pin number for which to configure the direction
 * \param[in] direction : pin direction
 *                        - 0 : corresponding pin is set to input
 *                        - 1 : corresponding pin is set to output
 */
extern void PinsDrv_SetPinDirection(PinsDrvType *obj, uint32_t pin, uint8_t direction);

/*! \brief Set the pins input disable state for a port
 *
 * This function sets the pins input state for a port.
 * Pins corresponding to bits with value of '1' will not be configured as input
 * and pins corresponding to bits with value of '0' will be configured
 * as input.
 *
 * \param[in] obj : pointer to pins driver instance
 * \param[in] mask : pin mask where each bit represents one pin (LSB is pin 0, MSB is pin 31).
 *                   For each bit:
 *                   - 0 : corresponding pin is set to input
 *                   - 1 : corresponding pin is not set to input
 */
extern void PinsDrv_SetPortInputDisable(PinsDrvType *obj, uint32_t mask);

/*! \brief Get the pins input disable state for a port
 *
 * This function returns the current pins input state for a port. Pins
 * corresponding to bits with value of '1' are not configured as input and
 * pins corresponding to bits with value of '0' are configured as input.
 *
 * \param[in] obj : pointer to pins driver instance
 * \return GPIO input state. Each bit represents one pin (LSB is pin 0, MSB is pin 31).
 *         For each bit:
 *         - 0 : corresponding pin is set to input
 *         - 1 : corresponding pin is not set to input
 */
extern uint32_t PinsDrv_GetPortInputDisable(const PinsDrvType *obj);

/*! \brief Write a pin of a port with a given value
 *
 * This function writes the given pin from a port, with the given value
 * ('0' represents LOW, '1' represents HIGH).
 *
 * \param[in] obj : pointer to pins driver instance
 * \param[in] pin : pin number to be written
 * \param[in] value : pin value to be written
 *                    - 0 : corresponding pin is set to LOW
 *                    - 1 : corresponding pin is set to HIGH
 */
extern void PinsDrv_WritePin(PinsDrvType *obj, uint32_t pin, uint8_t value);

/*! \brief Write all pins of a port
 *
 * This function writes all pins configured as output with the values given in
 * the parameter pins. '0' represents LOW, '1' represents HIGH.
 *
 * \param[in] obj : pointer to pins driver instance
 * \param[in] mask : pin mask to be written
 *                   - 0 : corresponding pin is set to LOW
 *                   - 1 : corresponding pin is set to HIGH
 */
extern void PinsDrv_WritePins(PinsDrvType *obj, uint32_t mask);

/*! \brief Get the current output from a pin
 *
 * This function returns the current output that is written to a pin. Only pin
 * that are configured as output will have meaningful values.
 *
 * \param[in] obj : pointer to pins driver instance
 * \param[in] pin : pin number to be read
 * \return GPIO pin output
 *         - 0 : corresponding pin is set to LOW
 *         - 1 : corresponding pin is set to HIGH
 */
extern uint8_t PinsDrv_GetPinOutput(const PinsDrvType *obj, uint32_t pin);

/*! \brief Get the current output from a port
 *
 * This function returns the current output that is written to a port. Only pins
 * that are configured as output will have meaningful values.
 *
 * \param[in] obj : pointer to pins driver instance
 * \return GPIO outputs. Each bit represents one pin (LSB is pin 0, MSB is pin 31).
 *         For each bit:
 *         - 0 : corresponding pin is set to LOW
 *         - 1 : corresponding pin is set to HIGH
 */
extern uint32_t PinsDrv_GetPinsOutput(const PinsDrvType *obj);

/*! \brief Write pin with 'Set' value
 *
 * This function configures output pin in parameter to have a value of 'set' (HIGH).
 *
 * \param[in] obj : pointer to pins driver instance
 * \param[in] pin : Pin that will be set.
 */
extern void PinsDrv_SetPin(PinsDrvType *obj, uint32_t pin);

/*! \brief Write pins with 'Set' value
 *
 * This function configures output pins listed in parameter pins (bits that are
 * '1') to have a value of 'set' (HIGH). Pins corresponding to '0' will be
 * unaffected.
 *
 * \param[in] obj : pointer to pins driver instance
 * \param[in] mask : Pin mask of bits to be set. Each bit represents one pin (LSB is pin 0, MSB is pin 31).
 *                   For each bit:
 *                   - 0: corresponding pin is unaffected
 *                   - 1: corresponding pin is set to HIGH
 */
extern void PinsDrv_SetPins(PinsDrvType *obj, uint32_t mask);

/*! \brief Write pin to 'Clear' value
 *
 * This function configures output pin in parameter to have a 'cleared' value (LOW).
 *
 * \param[in] obj : pointer to pins driver instance
 * \param[in] pin : Pin that will be cleared.
 */
extern void PinsDrv_ClearPin(PinsDrvType *obj, uint32_t pin);

/*! \brief Write pins to 'Clear' value
 *
 * This function configures output pins listed in parameter pins (bits that are
 * '1') to have a 'cleared' value (LOW). Pins corresponding to '0' will be
 * unaffected.
 *
 * \param[in] obj : pointer to pins driver instance
 * \param[in] mask : Pin mask of bits to be cleared. Each bit represents one pin (LSB is pin 0, MSB is pin 31).
 *                   For each bit:
 *                   - 0 : corresponding pin is unaffected
 *                   - 1 : corresponding pin is cleared(set to LOW)
 */
extern void PinsDrv_ClearPins(PinsDrvType *obj, uint32_t mask);

/*! \brief Toggle pin value
 *
 * This function toggles output pin in parameter.
 *
 * \param[in] obj : pointer to pins driver instance
 * \param[in] pin : Pin that will be toggled.
 */
extern void PinsDrv_TogglePin(PinsDrvType *obj, uint32_t pin);

/*! \brief Toggle pins value
 *
 * This function toggles output pins listed in parameter pins (bits that are
 * '1'). Pins corresponding to '0' will be unaffected.
 *
 * \param[in] obj : pointer to pins driver instance
 * \param[in] mask : Pin mask of bits to be toggled.  Each bit represents one pin (LSB is pin 0, MSB is pin 31).
 *                   For each bit:
 *                   - 0 : corresponding pin is unaffected
 *                   - 1 : corresponding pin is toggled
 */
extern void PinsDrv_TogglePins(PinsDrvType *obj, uint32_t mask);

/*! \brief Read a pin of a port
 *
 * This function returns the current input value of the given pin from a port.
 * Only pins configured as input will have meaningful values.
 *
 * \param[in] obj : pointer to pins driver instance
 * \param[in] pin : pin number to read
 * \return pin value
 *         - 0 : corresponding pin is read as LOW
 *         - 1 : corresponding pin is read as HIGH
 */
extern uint8_t PinsDrv_ReadPin(PinsDrvType *obj, uint32_t pin);

/*! \brief Read input pins
 *
 * This function returns the current input values from a port. Only pins
 * configured as input will have meaningful values.
 *
 * \param[in] obj : pointer to pins driver instance
 * \return GPIO inputs. Each bit represents one pin (LSB is pin 0, MSB is pin 31).
 *         For each bit:
 *         - 0 : corresponding pin is read as LOW
 *         - 1 : corresponding pin is read as HIGH
 */
extern uint32_t PinsDrv_ReadPins(const PinsDrvType *obj);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _PINS_DRV_H_ */
