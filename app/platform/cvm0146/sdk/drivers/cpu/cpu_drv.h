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

#ifndef _CPU_DRV_H_
#define _CPU_DRV_H_

/*! \brief Contains public interface to various functions related
 *         to the CPU
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include "cva/CVM014x.h"
#include "irq/irq_drv.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * the defines
 ******************************************************************************/

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Enter supervisor mode
 *
 * This function convert the CPU into supervisor mode.
 *
 */
static inline void CpuDrv_EnterSupervisorMode(void)
{
    /* if CPU in user mode */
    if ((__get_CONTROL() & 0x1) == 1) 
    {   
        /* change to privilege mode */
        __asm("svc #0x32");
    }
}

/*! \brief Change to supervisor mode
 *
 * This function change the CPU into supervisor mode.
 *
 */
static inline void CpuDrv_ChangeToSupervisorMode(void)
{
    __asm(" MOVS R0, #0x0 ");
    __asm(" MSR CONTROL, R0 ");
    __asm("DSB");
    __asm("ISB");
}

/*! \brief Enter user mode
 *
 * This function change the CPU into user mode.
 *
 */
static inline void CpuDrv_EnterUserMode(void)
{
    __asm(" MOVS R0, #0x1 ");
    __asm(" MSR CONTROL, R0 ");
    __asm("DSB");
    __asm("ISB");
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _CPU_DRV_H_ */
