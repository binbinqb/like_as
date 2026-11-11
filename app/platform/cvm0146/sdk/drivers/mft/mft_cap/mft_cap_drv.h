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

#ifndef _MFT_CAP_DRV_H_
#define _MFT_CAP_DRV_H_

/*! \brief Contains public interface to various functions related
 *         to the input Capture driver of MFT
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "../mft_drv.h"
#include "mft_cap_ch.h"

/*! \addtogroup mft_cap_drv
 *  \ingroup mft_drv
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

/*! \brief MFT Input capture driver configuration
 */
typedef struct _MftCapDrv_ConfigType_
{
    uint16_t maxCountValue; /*!< Maximum counter value. Minimum value is 0 for this mode */
} MftCapDrv_ConfigType;

/*! \brief The definition of MFT capture driver prototype
 * \details Derived from MFT driver
 */
typedef struct _MftCapDrvType_
{
    MftDrvType  *base;                     /*!< base class of capture driver */
    MftCapChType channel[MFT_CHANNEL_NUM]; /*!< channels of the capture mode */
} MftCapDrvType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Initializes the MFT CAP module
 *
 * This function initializes MFT CAP driver by setting the MFT driver
 * instance to it.
 *
 * \param[in] obj : pointer to MFT CAP channel instance
 * \param[in] base : pointer to MFT driver instance
 */
extern void MftCapDrv_Init(MftCapDrvType *obj, MftDrvType *base);

/*! \brief Get default configures the MFT capture module for configuration structure
 *
 * This function gets default configures the MFT capture module for user configuration structure
 *
 * \note This function is a "static" function regardless of instances
 *
 * \param[out] userConfig : pointer to configuration structure
 */
extern void MftCapDrv_GetDefaultConfig(MftCapDrv_ConfigType *userConfig);

/*! \brief Configure the MFT capture module
 *
 * This function configures the MFT capture module.
 *
 * \param[in] obj : pointer to MFT CAP channel instance
 * \param[in] userConfig : pointer to configuration structure
 */
extern void MftCapDrv_Config(MftCapDrvType *obj, const MftCapDrv_ConfigType *userConfig);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _MFT_CAP_DRV_H_ */
