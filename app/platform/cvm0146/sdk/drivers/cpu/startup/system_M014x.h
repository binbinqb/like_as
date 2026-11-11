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

#ifndef _SYSTEM_M014X_H_
#define _SYSTEM_M014X_H_

/*! \brief Contains public interface to various functions related
 *         to the System module of CVM014x series chips
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

/* Value of the external crystal or oscillator clock frequency in Hz */
#define CPU_XTAL_CLK_HZ               (16000000u)
#if CPU_XTAL_CLK_HZ > 40000000
#error "The external crystal or oscillator clock frequency is out of range."
#endif

/* Value of the fast internal oscillator clock frequency in Hz  */
#define CPU_INT_FAST_CLK_HZ           (48000000u)

/* Value of the slow internal oscillator clock frequency in Hz  */
#define CPU_INT_SLOW_CLK_HZ           (8000000u)

/* Default System clock value for the user code after SystemInit called */
#define DEFAULT_SYSTEM_CLOCK          (120000000u)


/*******************************************************************************
 * the typedefs
 ******************************************************************************/


/*******************************************************************************
 * the globals
 ******************************************************************************/


/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Setup the SoC.
 *
 * This function disables the watchdog, enables FPU.
 * if the corresponding feature macro is enabled.
 * SystemInit is called from startup_device file.
 */
extern void SystemInit(void);


#ifdef __cplusplus
}
#endif /* extern "C" */


#endif /* _SYSTEM_M014X_H_ */
