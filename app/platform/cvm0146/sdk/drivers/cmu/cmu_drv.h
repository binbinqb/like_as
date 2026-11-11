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

#ifndef _CMU_DRV_H_
#define _CMU_DRV_H_

/*! \brief Contains public interface to various functions related
 *         to the driver of CMU module
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/*! \addtogroup cmu_drv
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

/*! \brief CMU type of interrupt or reset enable
 */
typedef enum
{
    CMUDRV_DISABLE_INT_AND_RST    = 0, /*!< disable interrupt, disable reset */
    CMUDRV_ENABLE_INT_DISABLE_RST = 1, /*!< enable interrupt, disable reset */
    CMUDRV_DISABLE_INT_ENABLE_RST = 2, /*!< disable interrupt, enable reset */
} CmuDrv_EventStateType;

/*! \brief Definition of configuration of CMU driver
 */
typedef struct _CmuDrv_ConfigType_
{
    uint32_t              refClkCnt;       /*!< Reference frequency cnt Max Value. */
    uint32_t              highRefFreq;     /*!< high frequency threshod value. */
    uint32_t              lowRefFreq;      /*!< low frequency threshod value. */
    CmuDrv_EventStateType highFreqEventSt; /*!< State of high interrupt or reset enable. */
    CmuDrv_EventStateType lowFreqEventSt;  /*!< State of low interrupt or reset enable. */
} CmuDrv_ConfigType;

/* Forward declaration of CMU register */
struct _CmuRegType_;

/*! \brief The definition of CMU driver class
 */
typedef struct _CmuDrvType_
{
    struct _CmuRegType_ *reg;
} CmuDrvType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Initializes the CMU driver module
 *
 * This function initializes CMU driver by setting the register
 * instance to it.
 *
 * \param[in] obj : pointer to CMU driver instance
 * \param[in] reg : pointer to CMU register instance
 */
extern void CmuDrv_Init(CmuDrvType *obj, struct _CmuRegType_ *reg);

/*! \brief Configures the CMU module from a user configuration structure
 *
 * This function configures the CMU module from a user configuration structure
 *
 * \param[in] obj : pointer to CMU driver instance
 * \param[in] userConfig : pointer to configuration structure
 */
extern void CmuDrv_Configure(CmuDrvType *obj, const CmuDrv_ConfigType *userConfig);

/*! \brief Get configures of the CMU module currently
 *
 * This function gets configures of the CMU module currently
 *
 * \param[in] obj : pointer to CMU driver instance
 * \param[out] userConfig : pointer to configuration structure
 */
extern void CmuDrv_GetConfig(const CmuDrvType *obj, CmuDrv_ConfigType *userConfig);

/*! \brief Get default configures the CMU module for configuration structure
 *
 * This function gets default configures the CMU module for user configuration structure
 *
 * \note This function is a "static" function regardless of instances
 *
 * \param[out] userConfig : pointer to configuration structure
 */
extern void CmuDrv_GetDefaultConfig(CmuDrv_ConfigType *userConfig);

/*! \brief Get the state of frequency check enable
 *
 * This function gets the state of frequency check enable
 *
 * \param[in] obj : pointer to CMU driver instance
 * \return state of frequency check enable
 */
extern bool CmuDrv_IsFreqCheckEnable(const CmuDrvType *obj);

/*! \brief Set the state of frequency check enable
 *
 * This function sets the state of frequency check enable
 *
 * \param[in] obj : pointer to frequency check driver instance
 * \param[in] state of CMU enable
 */
extern void CmuDrv_EnableFreqCheck(const CmuDrvType *obj, bool enable);

/*! \brief Get the state of CMU run
 *
 * This function gets the state of CMU run
 *
 * \param[in] obj : pointer to CMU driver instance
 * \return state of CMU run
 */
extern bool CmuDrv_IsCmuRun(const CmuDrvType *obj);

/*! \brief Get the flag of frequency high
 *
 * This function gets the flag of frequency high
 *
 * \param[in] obj : pointer to CMU driver instance
 * \return the flag of frequency high
 */
extern bool CmuDrv_IsFreqHighEventAcvt(const CmuDrvType *obj);

/*! \brief Clear the flag of frequency high
 *
 * This function clears the flag of frequency high
 *
 * \param[in] obj : pointer to CMU driver instance
 * \return none
 */
extern void CmuDrv_ClearFreqHighEventFlag(CmuDrvType *obj);

/*! \brief Get the flag of frequency low
 *
 * This function gets the flag of frequency low
 *
 * \param[in] obj : pointer to CMU driver instance
 * \return the flag of frequency low
 */
extern bool CmuDrv_IsFreqLowEventAcvt(const CmuDrvType *obj);

/*! \brief Clear the flag of frequency low
 *
 * This function clears the flag of frequency low
 *
 * \param[in] obj : pointer to CMU driver instance
 * \return none
 */
extern void CmuDrv_ClearFreqLowEventFlag(CmuDrvType *obj);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _CMU_DRV_H_ */
