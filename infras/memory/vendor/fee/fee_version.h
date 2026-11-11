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

#ifndef _FEE_VERSION_H_
#define _FEE_VERSION_H_

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdio.h>

/*! \addtogroup Flash EEPROM Emulation
 *  @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * the defines
 ******************************************************************************/

/*! \brief Macro for the major version number of the software of the fee module.
 */
#if(defined FEE_SW_MAJOR_VERSION)
#error FEE_SW_MAJOR_VERSION already defined
#endif
#define FEE_SW_MAJOR_VERSION (1U)

/*! \brief Macro for the software version number of the fee module.
 */
#if(defined FEE_SW_MINOR_VERSION)
#error FEE_SW_MINOR_VERSION already defined
#endif
#define FEE_SW_MINOR_VERSION (0U)

/*! \brief Macro for the software patch version number of the fee module.
 */
#if(defined FEE_SW_PATCH_VERSION)
#error FEE_SW_PATCH_VERSION already defined
#endif
#define FEE_SW_PATCH_VERSION (0U)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief Type of software version number of the fee module.
 */
typedef struct _Fee_VersionInfoType_
{
    uint8_t sw_major_version;
    uint8_t sw_minor_version;
    uint8_t sw_patch_version;
} Fee_VersionInfoType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _FEE_VERSION_H_ */