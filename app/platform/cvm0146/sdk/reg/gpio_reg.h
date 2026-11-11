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

#ifndef _GPIO_REG_H_
#define _GPIO_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the GPIO Registers
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

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief The definition of GPIO registers
 */
typedef struct _GpioRegType_
{
    volatile uint32_t       PDOR; /*!< Port data output, offset: 0x00 */
    volatile uint32_t       PSOR; /*!< Port Set Output, offset: 0x04 */
    volatile uint32_t       PCOR; /*!< Port clear output, offset: 0x08 */
    volatile uint32_t       PTOR; /*!< Port toggle output, offset: 0x0C */
    const volatile uint32_t PDIR; /*!< Port data input, offset: 0x10 */
    volatile uint32_t       PDDR; /*!< Port data direction, offset: 0x14 */
    volatile uint32_t       PIDR; /*!< Port input disable, offset: 0x18 */
} GpioRegType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Gets the Port Data Output
 *
 * This function gets the current Port Data Output.
 * Register bits for unbonded pins return an undefined value when read.
 *
 * \param[in] obj : pointer to GPIO register instance
 * \return Port Data Output
 *         - 0b : Logic level 0 is driven on pin, provided pin is configured for general-purpose output.
 *         - 1b : Logic level 1 is driven on pin, provided pin is configured for general-purpose output.
 */
__attribute__((always_inline)) static inline uint32_t GpioReg_GetPdorDatOut(const GpioRegType *obj)
{
    return obj->PDOR;
}

/*! \brief Sets the Port Data Output
 *
 * This function sets the Port Data Output.
 * Register bits for unbonded pins return an undefined value when read.
 *
 * \param[in] obj : pointer to GPIO register instance
 * \param[in] value : the value of Port Data Output
 *                    - 0b : Logic level 0 is driven on pin, provided pin is configured for general-purpose output.
 *                    - 1b : Logic level 1 is driven on pin, provided pin is configured for general-purpose output.
 */
__attribute__((always_inline)) static inline void GpioReg_SetPdorDatOut(GpioRegType *obj, uint32_t value)
{
    obj->PDOR = value;
}

/*! \brief Sets the Port Set Output
 *
 * This function sets the Port Set Output.
 * Writing to this register updates the contents of the corresponding bit in the PDOR
 *
 * \param[in] obj : pointer to GPIO register instance
 * \param[in] value : the value of Port Set Output
 *                    - 0b : Corresponding bit in PDORn does not change.
 *                    - 1b : Corresponding bit in PDORn is set to logic 1.
 */
__attribute__((always_inline)) static inline void GpioReg_SetPsorDatSet(GpioRegType *obj, uint32_t value)
{
    obj->PSOR = value;
}

/*! \brief Sets the Port Clear Output
 *
 * This function sets the Port Clear Output.
 * Writing to this register updates the contents of the corresponding bit in the Port Data Output Register (PDOR)
 *
 * \param[in] obj : pointer to GPIO register instance
 * \param[in] value : the value of Port Clear Output
 *                    - 0b : Corresponding bit in PDORn does not change.
 *                    - 1b : Corresponding bit in PDORn is cleared to logic 0.
 */
__attribute__((always_inline)) static inline void GpioReg_SetPcorDatClr(GpioRegType *obj, uint32_t value)
{
    obj->PCOR = value;
}

/*! \brief Sets the Port Toggle Output
 *
 * This function sets the Port Toggle Output.
 * Writing to this register updates the contents of the corresponding bit in the PDOR
 *
 * \param[in] obj : pointer to GPIO register instance
 * \param[in] value : the value of Port Toggle Output
 *                    - 0b : Corresponding bit in PDORn does not change.
 *                    - 1b : Corresponding bit in PDORn is set to the inverse of its existing logic state.
 */
__attribute__((always_inline)) static inline void GpioReg_SetPtorDatTog(GpioRegType *obj, uint32_t value)
{
    obj->PTOR = value;
}

/*! \brief Gets the Port Data Input
 *
 * This function gets the current Port Data Input.
 * Reads 0 at the unimplemented pins for a particular device.
 * Pins that are not configured for a digital function read 0.
 * If the Port Control and Interrupt module is disabled, then the corresponding bit in PDIR does not update.
 *
 * \param[in] obj : pointer to GPIO register instance
 * \return Port Data Input
 *         - 0b : Pin logic level is logic 0, or is not configured for use by digital function.
 *         - 1b : Pin logic level is logic 1.
 */
__attribute__((always_inline)) static inline uint32_t GpioReg_GetPdirDatIn(const GpioRegType *obj)
{
    return obj->PDIR;
}

/*! \brief Gets the Port Data Direction
 *
 * This function gets the current Port Data Direction.
 * Configures individual port pins for input or output.
 *
 * \param[in] obj : pointer to GPIO register instance
 * \return Port Data Direction
 *         - 0b : Pin is configured as general-purpose input, for the GPIO function.
 *                The pin will be high-Z if the port input is disabled in GPIOx_PIDR register.
 *         - 1b : Pin is configured as general-purpose output, for the GPIO function.
 */
__attribute__((always_inline)) static inline uint32_t GpioReg_GetPddrDir(const GpioRegType *obj)
{
    return obj->PDDR;
}

/*! \brief Sets the Port Data Direction
 *
 * This function sets the Port Data Direction.
 * Configures individual port pins for input or output.
 *
 * \param[in] obj : pointer to GPIO register instance
 * \param[in] value : the value of Port Data Direction
 *                    - 0b : Pin is configured as general-purpose input, for the GPIO function.
 *                           The pin will be high-Z if the port input is disabled in GPIOx_PIDR register.
 *                    - 1b : Pin is configured as general-purpose output, for the GPIO function.
 */
__attribute__((always_inline)) static inline void GpioReg_SetPddrDir(GpioRegType *obj, uint32_t value)
{
    obj->PDDR = value;
}

/*! \brief Gets the Port Input Disable
 *
 * This function gets the current Port Input Disable.
 *
 * \param[in] obj : pointer to GPIO register instance
 * \return Port Input Disable
 *         - 0b : Pin is configured for General Purpose Input, provided the pin is configured for any digital function.
 *         - 1b : Pin is not configured as General Purpose Input. Corresponding Port Data Input Register bit will read zero.
 */
__attribute__((always_inline)) static inline uint32_t GpioReg_GetPidrInDisable(const GpioRegType *obj)
{
    return obj->PIDR;
}

/*! \brief Sets the Port Input Disable
 *
 * This function sets the Port Input Disable.
 *
 * \param[in] obj : pointer to GPIO register instance
 * \param[in] value : the value of Port Input Disable
 *                    - 0b : Pin is configured for General Purpose Input, provided the pin is configured for any digital function.
 *                    - 1b : Pin is not configured as General Purpose Input. Corresponding Port Data Input Register bit will read zero.
 */
__attribute__((always_inline)) static inline void GpioReg_SetPidrInDisable(GpioRegType *obj, uint32_t value)
{
    obj->PIDR = value;
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _GPIO_REG_H_ */