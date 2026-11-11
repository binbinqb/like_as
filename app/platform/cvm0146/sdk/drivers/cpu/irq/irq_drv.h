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

#ifndef _IRQ_DRV_H_
#define _IRQ_DRV_H_

/*! \brief Contains public interface to various functions related
 *         to the driver of interrupt requests
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/*! \addtogroup irq_drv
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

/*! \brief Interrupt handler type */
typedef void (*IrqHandlerType)(void);

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Installs an interrupt handler routine for a given IRQ number.
 *
 * This function lets the application register/replace the interrupt
 * handler for a specified IRQ number. See a chip-specific reference
 * manual for details and the  startup_<SoC>.s file for each chip
 * family to find out the default interrupt handler for each device.
 *
 * \note This method is applicable only if interrupt vector is copied in RAM.
 *
 * \param[in] irqNumber : IRQ number
 * \param[in] newHandler : New interrupt handler routine address pointer
 * \param[in] oldHandler : Pointer to a location to store current interrupt handler
 */
extern void IrqDrv_InstallHandler(uint16_t irqNumber, IrqHandlerType newHandler, IrqHandlerType *oldHandler);

/*! \brief Enables system interrupt.
 *
 * This function enables the global interrupt by calling the core API.
 *
 */
extern void IrqDrv_EnableGlobalInterrupt(void);

/*! \brief Disable system interrupt.
 *
 * This function disables the global interrupt by calling the core API.
 *
 */
extern void IrqDrv_DisableGlobalInterrupt(void);

/*! \brief Enables an interrupt for a given IRQ number.
 *
 * This function  enables the individual interrupt for a specified IRQ number.
 *
 * \param[in] irqNumber : IRQ number
 */
extern void IrqDrv_EnableIrq(uint16_t irqNumber);

/*! \brief Disables an interrupt for a given IRQ number.
 *
 * This function disables the individual interrupt for a specified IRQ number.
 *
 * \param[in] irqNumber : IRQ number
 */
extern void IrqDrv_DisableIrq(uint16_t irqNumber);

/*! \brief Set Priority Grouping
 *
 * Sets the priority grouping field using the required unlock sequence.
 * The parameter PriorityGroup is assigned to the field SCB->AIRCR [10:8] PRIGROUP field.
 * __NVIC_PRIO_BITS is 4, so only values from 3..7 are used.
 * In case of a conflict between priority grouping and available
 * priority bits (__NVIC_PRIO_BITS), the smallest possible priority group is set.
 * The relation between priorityGroup and preemptPriority/subPriority is as the following table:
 * |---------------------|----------------------|------------------|------------------------|--------------------|
 * | priorityGroup value | preemptPriority bits | subPriority bits | preemptPriority number | subPriority number |
 * |---------------------|----------------------|------------------|------------------------|--------------------|
 * |          3          |        [7:4]         |         -        |        16 (0~15)       |       1 (0)        |
 * |          4          |        [7:5]         |        [4]       |         8 (0~7)        |       2 (0~1)      |
 * |          5          |        [7:6]         |       [5:4]      |         4 (0~3)        |       4 (0~3)      |
 * |          6          |         [7]          |       [6:4]      |         2 (0~1)        |       8 (0~7)      |
 * |          7          |          -           |       [7:4]      |         1 (0)          |      16 (0~15)     |
 * |---------------------|----------------------|------------------|------------------------|--------------------|
 *
 * \param[in] priorityGroup : Priority grouping field.
 */
extern void IrqDrv_SetPriorityGrouping(uint32_t priorityGroup);

/*! \brief  Set Interrupt Priority
 *
 * The function sets the priority of an interrupt.
 *
 * \param[in] irqNumber : Interrupt number
 * \param[in] preemptPriority : Preemptive priority value (starting from 0).
 * \param[in] subPriority : Subpriority value (starting from 0).
 */
extern void IrqDrv_SetPriority(uint16_t irqNumber, uint32_t preemptPriority, uint32_t subPriority);

/*! \brief  Get Interrupt Priority
 *
 * The function gets the priority of an interrupt.
 *
 * \param[in] irqNumber : Interrupt number.
 * \param[out] pPreemptPriority : Preemptive priority value (starting from 0).
 * \param[out] pSubPriority : Subpriority value (starting from 0).
 */
extern void IrqDrv_GetPriority(uint16_t irqNumber, uint32_t *pPreemptPriority, uint32_t *pSubPriority);

/*! \brief Clear Pending Interrupt
 *
 * The function clears the pending bit of a peripheral interrupt
 * or a directed interrupt to this CPU (if available).
 *
 * \param[in] irqNumber : IRQ number
 */
extern void IrqDrv_ClearPending(uint16_t irqNumber);

/*! \brief Set Pending Interrupt
 *
 * The function configures the pending bit of a peripheral interrupt.
 *
 * \param[in] irqNumber : IRQ number
 */
extern void IrqDrv_SetPending(uint16_t irqNumber);

/*! \brief Whether the Interrupt is Pending
 *
 * The function gets the pending bit of a peripheral interrupt
 * or a directed interrupt to this CPU (if available).
 *
 * \param[in] irqNumber : IRQ number
 * \return pending status
 *         - false : Interrupt status is not pending.
 *         - true : Interrupt status is pending.
 */
extern bool IrqDrv_IsPending(uint16_t irqNumber);

/*! \brief Whether the interrupt is active
 *
 * The function gets the active state of a peripheral interrupt.
 *
 * \param[in] irqNumber : IRQ number
 * \return active status
 *         - false : Interrupt status is not active.
 *         - true : Interrupt status is active.
 */
extern bool IrqDrv_IsActive(uint16_t irqNumber);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _IRQ_DRV_H_ */
