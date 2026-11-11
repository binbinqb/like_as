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

#ifndef _PWMLITE_DRV_H_
#define _PWMLITE_DRV_H_

/*! \brief Contains public interface to various functions related
 *         to the driver of PWMLITE
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/*! \addtogroup pwmlite_drv
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

typedef enum
{
    PWMLITEDRV_PWM_CH0 = 0x0U, /*!< Pwm0/1 channel0 */
    PWMLITEDRV_PWM_CH1 = 0x1U, /*!< Pwm0/1 channel1 */
    PWMLITEDRV_PWM_CH2 = 0x2U, /*!< Pwm0/1 channel2 */
    PWMLITEDRV_PWM_CH3 = 0x3U, /*!< Pwm0/1 channel3 */
    PWMLITEDRV_PWM_CH4 = 0x4U, /*!< Pwm0/1 channel4 */
    PWMLITEDRV_PWM_CH5 = 0x5U, /*!< Pwm0/1 channel5 */
    PWMLITEDRV_PWM_CH6 = 0x6U, /*!< Pwm0/1 channel6 */
    PWMLITEDRV_PWM_CH7 = 0x7U, /*!< Pwm0/1 channel7 */

    PWMLITEDRV_PWM_CH_NUM,
} PwmLiteDrv_PwmChannelType;

typedef enum
{
    PWMLITEDRV_MUX_PWM0_CH0 = 0x0U,  /*!< Pwm0 channel0 */
    PWMLITEDRV_MUX_PWM0_CH1 = 0x1U,  /*!< Pwm0 channel1 */
    PWMLITEDRV_MUX_PWM0_CH2 = 0x2U,  /*!< Pwm0 channel2 */
    PWMLITEDRV_MUX_PWM0_CH3 = 0x3U,  /*!< Pwm0 channel3 */
    PWMLITEDRV_MUX_PWM0_CH4 = 0x4U,  /*!< Pwm0 channel4 */
    PWMLITEDRV_MUX_PWM0_CH5 = 0x5U,  /*!< Pwm0 channel5 */
    PWMLITEDRV_MUX_PWM0_CH6 = 0x6U,  /*!< Pwm0 channel6 */
    PWMLITEDRV_MUX_PWM0_CH7 = 0x7U,  /*!< Pwm0 channel7 */
    PWMLITEDRV_MUX_PWM1_CH0 = 0x8U,  /*!< Pwm1 channel0 */
    PWMLITEDRV_MUX_PWM1_CH1 = 0x9U,  /*!< Pwm1 channel1 */
    PWMLITEDRV_MUX_PWM1_CH2 = 0xAU,  /*!< Pwm1 channel2 */
    PWMLITEDRV_MUX_PWM1_CH3 = 0xBU,  /*!< Pwm1 channel3 */
    PWMLITEDRV_MUX_PWM1_CH4 = 0xCU,  /*!< Pwm1 channel4 */
    PWMLITEDRV_MUX_PWM1_CH5 = 0xDU,  /*!< Pwm1 channel5 */
    PWMLITEDRV_MUX_PWM1_CH6 = 0xEU,  /*!< Pwm1 channel6 */
    PWMLITEDRV_MUX_PWM1_CH7 = 0xFU,  /*!< Pwm1 channel7 */
    PWMLITEDRV_MUX_PWM2_CH0 = 0x10U, /*!< Pwm2 channel0 */
    PWMLITEDRV_MUX_PWM2_CH1 = 0x11U, /*!< Pwm2 channel1 */
    PWMLITEDRV_MUX_PWM2_CH2 = 0x12U, /*!< Pwm2 channel2 */
    PWMLITEDRV_MUX_PWM2_CH3 = 0x13U, /*!< Pwm2 channel3 */
    PWMLITEDRV_MUX_PWM2_CH4 = 0x14U, /*!< Pwm2 channel4 */
    PWMLITEDRV_MUX_PWM2_CH5 = 0x15U, /*!< Pwm2 channel5 */
    PWMLITEDRV_MUX_PWM2_CH6 = 0x16U, /*!< Pwm2 channel6 */
    PWMLITEDRV_MUX_PWM2_CH7 = 0x17U, /*!< Pwm2 channel7 */
    PWMLITEDRV_MUX_PWM3_CH0 = 0x18U, /*!< Pwm3 channel0 */
    PWMLITEDRV_MUX_PWM3_CH1 = 0x19U, /*!< Pwm3 channel1 */
    PWMLITEDRV_MUX_PWM3_CH2 = 0x1AU, /*!< Pwm3 channel2 */
    PWMLITEDRV_MUX_PWM3_CH3 = 0x1BU, /*!< Pwm3 channel3 */
    PWMLITEDRV_MUX_PWM3_CH4 = 0x1CU, /*!< Pwm3 channel4 */
    PWMLITEDRV_MUX_PWM3_CH5 = 0x1DU, /*!< Pwm3 channel5 */
    PWMLITEDRV_MUX_PWM3_CH6 = 0x1EU, /*!< Pwm3 channel6 */
    PWMLITEDRV_MUX_PWM3_CH7 = 0x1FU, /*!< Pwm3 channel7 */
    PWMLITEDRV_MUX_PWM4_CH0 = 0x20U, /*!< Pwm4 channel0 */
    PWMLITEDRV_MUX_PWM4_CH1 = 0x21U, /*!< Pwm4 channel1 */
    PWMLITEDRV_MUX_PWM4_CH2 = 0x22U, /*!< Pwm4 channel2 */
    PWMLITEDRV_MUX_PWM4_CH3 = 0x23U, /*!< Pwm4 channel3 */
    PWMLITEDRV_MUX_PWM4_CH4 = 0x24U, /*!< Pwm4 channel4 */
    PWMLITEDRV_MUX_PWM4_CH5 = 0x25U, /*!< Pwm4 channel5 */
    PWMLITEDRV_MUX_PWM4_CH6 = 0x26U, /*!< Pwm4 channel6 */
    PWMLITEDRV_MUX_PWM4_CH7 = 0x27U, /*!< Pwm4 channel7 */

    PWMLITEDRV_MUX_PWM_CH_INVALID,
} PwmLiteDrv_PwmMuxChannelType;

typedef enum
{
    PWMLITEDRV_MUX_PAD_PWM0 = 0x0U, /*!< MUX PWM00 PAD */
    PWMLITEDRV_MUX_PAD_PWM1 = 0x1U, /*!< MUX PWM01 PAD */
    PWMLITEDRV_MUX_PAD_PWM2 = 0x2U, /*!< MUX PWM02 PAD */
    PWMLITEDRV_MUX_PAD_PWM3 = 0x3U, /*!< MUX PWM03 PAD */
    PWMLITEDRV_MUX_PAD_PWM4 = 0x4U, /*!< MUX PWM04 PAD */
    PWMLITEDRV_MUX_PAD_PWM5 = 0x5U, /*!< MUX PWM05 PAD */
    PWMLITEDRV_MUX_PAD_PWM6 = 0x6U, /*!< MUX PWM06 PAD */
    PWMLITEDRV_MUX_PAD_PWM7 = 0x7U, /*!< MUX PWM07 PAD */

    PWMLITEDRV_MUX_PAD_PWM_NUM,
} PwmLiteDrv_PwmMuxPadNumType;

typedef enum
{
    PWMLITEDRV_SYNC_AT_RUNNING = 0x0U, /*!< Sync at running */
    PWMLITEDRV_SYNC_AT_PERIOD  = 0x1U  /*!< Sync at period */
} PwmLiteDrv_SyncType;

typedef enum
{
    PWMLITEDRV_KEEP_AT_REACH   = 0x0U, /*!< Output keep at reach match value */
    PWMLITEDRV_LOW_AT_REACH    = 0x1U, /*!< Output set low at reach match value */
    PWMLITEDRV_HIGH_AT_REACH   = 0x2U, /*!< Output set high at reach match value */
    PWMLITEDRV_TOGGLE_AT_REACH = 0x3U  /*!< Output toggle at reach match value */
} PwmLiteDrv_OutBehaviorType;

/*! \brief The definition of PWMLITE driver class
 */
typedef struct _PwmLiteDrvType_
{
    struct _PwmLiteRegType_ *pwmLiteReg;
    struct _SimRegType_     *simReg;
} PwmLiteDrvType;

typedef struct _PwmLiteDrv_PwmMuxConfigType_
{
    PwmLiteDrv_PwmMuxChannelType channelNumber; /*!< The pwmlite channel number */
    PwmLiteDrv_PwmMuxPadNumType  padNumber;     /*!< The target pad number */
} PwmLiteDrv_PwmMuxConfigType;

typedef struct _PwmLiteDrv_ModuleConfigType_
{
    uint32_t            period;   /*!< Pwm period value */
    PwmLiteDrv_SyncType syncType; /*!< Module sync type */

} PwmLiteDrv_ModuleConfigType;

typedef struct _PwmLiteDrv_ChannelConfigType_
{
    PwmLiteDrv_PwmMuxConfigType pwmMuxType; /*!< Pwm mux output type */

    uint32_t                   threshold0; /*!< Threshold0 of the channel */
    uint32_t                   threshold1; /*!< Threshold1 of the channel */
    PwmLiteDrv_OutBehaviorType behavior0;  /*!< Behavior0 on reach threshold0 */
    PwmLiteDrv_OutBehaviorType behavior1;  /*!< Behavior1 on reach threshold1 */
} PwmLiteDrv_ChannelConfigType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Initializes the PWMlite reg
 *
 *
 * \param[in] obj : pointer to PWMLITE driver instance
 * \param[in] pwmLiteReg : pointer to PWMLITE register instance
 * \param[in] simReg : pointer to SIM register instance
 */
extern void PwmLiteDrv_Init(PwmLiteDrvType *obj, struct _PwmLiteRegType_ *pwmLiteReg, struct _SimRegType_ *simReg);

/*! \brief Get default configures the PWMLITE module for configuration structure
 *
 * This function gets default configures the PWMLITE module for user configuration structure
 *
 * \param[in] obj : pointer to PWMLITE driver instance
 *
 */
extern void PwmLiteDrv_GetDefaultModuleConfig(PwmLiteDrv_ModuleConfigType *ModuleConfigType);

/*! \brief config the pwm module according to user config
 *
 *
 * \param[in] obj : pointer to PWMLITE driver instance
 * \param[in] userConfig : pointer to the user config structure
 */
extern void PwmLiteDrv_ModuleConfig(PwmLiteDrvType *obj, const PwmLiteDrv_ModuleConfigType *userConfig);

/*! \brief Get default configures the PWMLITE module channel for configuration structure
 *
 * This function gets default configures the PWMLITE module channel for user configuration structure
 *
 * \param[in] obj : pointer to PWMLITE driver instance
 *
 */
extern void PwmLiteDrv_GetDefaultChannelConfig(PwmLiteDrv_ChannelConfigType *userConfig);

/*! \brief config the pwm channel according to user config
 *
 *
 * \param[in] obj : pointer to PWMLITE driver instance
 * \param[in] channel : the pwm channel number
 * \param[in] userConfig : pointer to the user config structure
 */
extern void PwmLiteDrv_ConfigChannel(PwmLiteDrvType *obj, uint8_t channel, const PwmLiteDrv_ChannelConfigType *userConfig);

/*! \brief update the Pwm duty value at running
 *
 *
 * \param[in] obj : pointer to PWMLITE driver instance
 * \param[in] channel : the pwm channel number
 * \param[in] threshold0 : new threshold0 value
 * \param[in] threshold1 : new threshold1 value
 */
extern void PwmLiteDrv_UpdatePwmThresholdAtRunning(PwmLiteDrvType *obj, uint8_t channel, uint32_t threshold0, uint32_t threshold1);

/*! \brief update the Pwm duty value at sync time
 *
 *
 * \param[in] obj : pointer to PWMLITE driver instance
 * \param[in] channel : the pwm channel number
 * \param[in] threshold0 : new threshold0 value
 * \param[in] threshold1 : new threshold1 value
 */
extern void PwmLiteDrv_UpdatePwmThresholdAtSync(PwmLiteDrvType *obj, uint8_t channel, uint32_t threshold0, uint32_t threshold1);

/*! \brief mux the pwm channels to target pad channel through SIM
 *
 *
 * \param[in] channel : the pwm channel number
 * \param[in] number : the target pad number
 */
extern void PwmLiteDrv_OutputMux(PwmLiteDrvType *obj, PwmLiteDrv_PwmMuxChannelType channel, PwmLiteDrv_PwmMuxPadNumType number);

/*! \brief resume the pwm module output
 *
 *
 * \param[in] obj : pointer to PWMLITE driver instance
 */
extern void PwmLiteDrv_Resume(PwmLiteDrvType *obj);

/*! \brief pause the pwm module output
 *
 *
 * \param[in] obj : pointer to PWMLITE driver instance
 */
extern void PwmLiteDrv_Pause(PwmLiteDrvType *obj);

/*! \brief enable the pwm module
 *
 *
 * \param[in] obj : pointer to PWMLITE driver instance
 */
extern void PwmLiteDrv_EnableModule(PwmLiteDrvType *obj);

/*! \brief disable the pwm module
 *
 *
 * \param[in] obj : pointer to PWMLITE driver instance
 */
extern void PwmLiteDrv_DisableModule(PwmLiteDrvType *obj);

/*! \brief get the sync result
 *
 *
 * \param[in] obj : pointer to PWMLITE driver instance
 * \param[out] bool : result
 *             - 0 : update done
 *             - 1 : during update
 */
extern uint8_t PwmLiteDrv_GetSyncResult(PwmLiteDrvType *obj);

/*! \brief trig the sync action
 *
 *
 * \param[in] obj : pointer to PWMLITE driver instance
 */
extern void PwmLiteDrv_TrigSync(PwmLiteDrvType *obj);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _PWMLITE_DRV_H_ */
