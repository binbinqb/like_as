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

#ifndef _MFT_PWM_DRV_H_
#define _MFT_PWM_DRV_H_

/*! \brief Contains public interface to various functions related
 *         to the PWM driver of MFT
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "../mft_drv.h"
#include "mft_pwm_ch.h"

/*! \addtogroup mft_pwm_drv
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

/*! \brief MFT fault control mode
 */
typedef enum
{
    MFTPWMDRV_FAULT_CTRL_DISABLED = 0x00U, /*!< Fault control is disabled for all channels */
    MFTPWMDRV_FAULT_CTRL_MAN_EVEN = 0x01U, /*!< Fault control is enabled for even channels
                                            *   only (channels 0, 2, 4, and 6), and the selected
                                            *   mode is the manual fault clearing */
    MFTPWMDRV_FAULT_CTRL_MAN_ALL = 0x02U,  /*!< Fault control is enabled for all channels,
                                            *   and the selected mode is the manual fault clearing */
    MFTPWMDRV_FAULT_CTRL_AUTO_ALL = 0x03U  /*!< Fault control is enabled for all channels, and
                                            *   the selected mode is the automatic fault clearing */
} MftPwmDrv_FaultModeType;

/*! \brief MFT PWM Fault channel polarity
 */
typedef enum
{
    MFTPWMDRV_FAULT_ACTIVE_HIGH = 0x00U, /*!< The fault occurs on the input (n) when it's HIGH, the input is LOW when no fault */
    MFTPWMDRV_FAULT_ACTIVE_LOW  = 0x01U  /*!< The fault occurs on the input (n) when it's LOW, the input is HIGH when no fault */
} MftPwmDrv_FaultChannelPolarityType;

/*! \brief MFT PWM Fault channel parameters
 */
typedef struct
{
    bool                               enabled;       /*!< Fault channel state */
    bool                               filterEnabled; /*!< Fault channel filter state */
    MftPwmDrv_FaultChannelPolarityType inputPolarity; /*!< Fault channel input polarity */
} MftPwmDrv_FaultChannelConfigType;

/*! \brief FlexTimer driver PWM Fault parameter
 */
typedef struct
{
    bool                             enableTriStateOnFault;           /*!< Output pin state on fault (safe state or tri-state) */
    uint8_t                          faultFilterValue;                /*!< Fault filter value */
    MftPwmDrv_FaultModeType          faultMode;                       /*!< Fault mode */
    MftPwmDrv_FaultChannelConfigType faultInput[MFT_FAULT_INPUT_NUM]; /*!< fault channels */
} MftPwmDrv_FaultConfigType;

/*! \brief MFT sync source
 */
typedef enum
{
    MFTPWMDRV_SYSTEM_CLOCK = 0U, /*!< Register is updated with its buffer value at all rising edges of system clock */
    MFTPWMDRV_PWM_SYNC     = 1U  /*!< Register is updated with its buffer value at the MFT synchronization */
} MftPwmDrv_UpdateConfigType;

/*! \brief MFT updated config
 */
typedef enum
{
    MFTPWMDRV_WAIT_LOADING_POINTS = 0U, /*!< MFT register is updated at first loading point */
    MFTPWMDRV_UPDATE_NOW          = 1U  /*!< MFT register is updated immediately */
} MftPwmDrv_SyncModeConfigType;

/*! \brief MFT pwm sync structure
 */
typedef struct _MftPwmDrv_SyncType_
{
    bool                         softwareSync;     /*!< True - enable software sync, False - disable software sync */
    bool                         hardwareSync0;    /*!< True - enable hardware 0 sync, False - disable hardware 0 sync */
    bool                         hardwareSync1;    /*!< True - enable hardware 1 sync, False - disable hardware 1 sync */
    bool                         hardwareSync2;    /*!< True - enable hardware 2 sync, False - disable hardware 2 sync */
    bool                         maxLoadingPoint;  /*!< True - enable maximum loading point, False - disable maximum loading point */
    bool                         minLoadingPoint;  /*!< True - enable minimum loading point, False - disable minimum loading point */
    MftPwmDrv_UpdateConfigType   inverterSync;     /*!< Configures INVCTRL sync */
    MftPwmDrv_UpdateConfigType   outRegSync;       /*!< Configures SWOCTRL sync */
    MftPwmDrv_UpdateConfigType   maskRegSync;      /*!< Configures OUTMASK sync */
    MftPwmDrv_UpdateConfigType   initCounterSync;  /*!< Configures CNTIN sync */
    bool                         autoClearTrigger; /*!< Available only for hardware trigger */
    MftPwmDrv_SyncModeConfigType syncPoint;        /*!< Configure synchronization method(waiting next loading point or immediate) */
} MftPwmDrv_SyncType;

/*! \brief MFT pre-scaler factor for the dead-time insertion
 */
typedef enum
{
    MFTPWMDRV_DEADTIME_DIVID_BY_1  = 0x01U, /*!< Divide by 1   */
    MFTPWMDRV_DEADTIME_DIVID_BY_4  = 0x02U, /*!< Divide by 4   */
    MFTPWMDRV_DEADTIME_DIVID_BY_16 = 0x03U  /*!< Divide by 16  */
} MftPwmDrv_DeadTimePrescalerType;

/*! \brief MFT PWM driver parameters
 */
typedef struct _MftPwmDrv_ConfigType_
{
    uint32_t                        periodValue;       /*!< PWM period ticks */
    MftPwmDrv_SyncType              syncMethod;        /*!< Register sync options */
    MftPwmDrv_FaultConfigType       faultConfig;       /*!< Fault configuration */
    uint8_t                         deadTimeCount;     /*!< Dead time value in [ticks], only available in complementary mode */
    MftPwmDrv_DeadTimePrescalerType deadTimePrescaler; /*!< Dead time pre-scaler value, only available in complementary mode */
} MftPwmDrv_ConfigType;

/*! \brief The definition of MFT PWM driver prototype
 * \details Derived from MFT driver
 */
typedef struct _MftPwmDrvType_
{
    MftDrvType  *base;                     /*!< base class pointer */
    MftPwmChType channel[MFT_CHANNEL_NUM]; /*!< channels of the PWM mode */
} MftPwmDrvType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Initializes the MFT PWM channel instance
 *
 * This function initializes MFT PWM channel instance by setting the MFT driver
 * instance to it.
 *
 * \param[in] obj : pointer to MFT PWM driver instance
 * \param[in] base : pointer to MFT driver instance
 */
extern void MftPwmDrv_Init(MftPwmDrvType *obj, MftDrvType *base);

/*! \brief Get default configuration of the MFT PWM module
 *
 * This function gets default configuration of the MFT PWM module for user configuration structure
 *
 * \note This function is a "static" function regardless of instances
 *
 * \param[out] userConfig : pointer to configuration structure
 */
extern void MftPwmDrv_GetDefaultConfig(MftPwmDrv_ConfigType *userConfig);

/*! \brief Configure the MFT PWM module
 *
 * This function configures the MFT PWM module.
 *
 * \param[in] obj : pointer to MFT PWM driver instance
 * \param[in] userConfig : pointer to configuration structure
 */
extern void MftPwmDrv_Config(MftPwmDrvType *obj, const MftPwmDrv_ConfigType *userConfig);

/*! \brief Initializes the channels output.
 *
 * This function initializes the channels output.
 *
 * \note Normally it should be called after setup of channels
 *
 * \param[in] obj : pointer to MFT PWM driver instance
 * \param[in] enable : Initialize the channels output
 *                     - true : The channels output is initialized according to the state of OUTINIT reg
 *                     - false: No effect
 */
extern void MftPwmDrv_SetInitOutputCmd(MftPwmDrvType *obj, bool enable);

/*! \brief Configure the MFT PWM module
 *
 * This function configures the MFT PWM module.
 *
 * \param[in] obj : pointer to MFT PWM driver instance
 * \param[in] value : the period value in ticks
 */
extern void MftPwmDrv_SetPeriod(MftPwmDrvType *obj, uint16_t value);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _MFT_PWM_DRV_H_ */
