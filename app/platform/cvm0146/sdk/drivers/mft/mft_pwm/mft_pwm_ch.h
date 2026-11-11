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

#ifndef _MFT_PWM_CH_H_
#define _MFT_PWM_CH_H_

/*! \brief Contains public interface to various functions related
 *         to the PWM output channel of MFT
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/*! \addtogroup mft_pwm_ch
 *  \ingroup mft_pwm_drv
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

/*! \brief The polarity of the channel output is configured in PWM signal
 */
typedef enum
{
    MFTPWMCH_ACTIVE_HIGH  = 0x00U, /*!< The channel polarity is active HIGH */
    MFTPWMCH_ACTIVE_LOW   = 0x01U  /*!< The channel polarity is active LOW */
} MftPwmCh_PolarityType;

/*! \brief The pulse mode of PWM
 */
typedef enum
{
    MFTPWMCH_SET_ON_MATCH_UP,  /*!< The channel set when counter matches CV in up-counting */
    MFTPWMCH_CLEAR_ON_MATCH_UP /*!< The channel clear when counter matches CV in up-counting */
} MftPwmCh_PulseModeType;

/*! \brief MFT driver combined PWM parameter
 */
typedef struct
{
    /* Independent channel configuration */
    uint8_t                hwChannelId;           /*!< Physical hardware channel ID for channel (n) */
    MftPwmCh_PulseModeType pulseMode;             /*!< The mode of pulse */
    MftPwmCh_PolarityType  mainChannelPolarity;   /*!< Polarity of the PWM signal generated on MCU pin for channel n.*/
    bool                   enableExternalTrigger; /*!< The generation of the channel (n) trigger */
    bool                   enableFaultCtrl;       /*!< Enable/disable fault control for this pair */
    /* Dual channels configuration */
    bool                  enableSecondChannelOutput;      /*!< Select if channel (n+1)  output is enabled/disabled for the complementary mode */
    bool                  enableComplementary;            /*!< Enable the complementary mode for channels (n) and (n+1) */
    bool                  enableCombine;                  /*!< Enable the combine mode for channels (n) and (n+1) */
    bool                  enableModifiedCombine;          /*!< Enable the modified combine mode for channels (n) and (n+1) */
    bool                  deadTime;                       /*!< Enable/disable dead time for channel */
    MftPwmCh_PolarityType secondChannelPolarity;          /*!< Select channel (n+1) polarity relative to channel (n) in the complementary mode */
    bool                  enableExternalTriggerOnNextChn; /*!< The generation of the channel (n+1) trigger */
} MftPwmCh_ConfigType;

/* Forward declaration of MFT PWM driver */
struct _MftPwmDrvType_;

/*! \brief The definition of MFT PWM channel prototype
 */
typedef struct _MftPwmChType_
{
    struct _MftPwmDrvType_ *pwmDrv; /*!< pointer to the PWM driver instance */
    MftPwmCh_ConfigType     config; /*!< configuration of this channel */
} MftPwmChType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Initializes the MFT PWM channel
 *
 * This function initializes MFT PWM channel.
 *
 * \param[in] obj : pointer to MFT PWM channel instance
 * \param[in] base : pointer to MFT driver instance
 */
extern void MftPwmCh_Init(MftPwmChType *obj, struct _MftPwmDrvType_ *pwmDrv);

/*! \brief Get default configures the MFT PWM module for configuration structure
 *
 * This function gets default configures the MFT PWM module for user configuration structure
 *
 * \note This function is a "static" function regardless of instances
 *
 * \param[out] userConfig : pointer to configuration structure
 */
extern void MftPwmCh_GetDefaultConfig(MftPwmCh_ConfigType *userConfig);

/*! \brief Configure the MFT PWM channel
 *
 * This function configures the channel in the PWM mode. The channel can
 * be both independent mode or combined mode.
 *
 * \param[in] obj : pointer to MFT PWM channel instance
 * \param[in] userConfig : pointer to configuration structure
 * \return The result of the operation
 *         - true : success
 *         - false : failed
 */
extern bool MftPwmCh_Config(MftPwmChType *obj, const MftPwmCh_ConfigType *userConfig);

/*! \brief Set the MFT PWM channel value
 *
 * This function set the MFT channel value.
 *
 * \note If the channel is independent, the second value has no effect.
 *       If the channel is in complementary mode, the second value also
 *       has no effect.
 *
 * \param[in] obj : pointer to MFT PWM channel instance
 * \param[in] firstValue : the value of first channel
 * \param[in] secondValue : the value of second channel
 *                          if the first channel is independent, this value has no effect
 */
extern void MftPwmCh_SetChannelValue(MftPwmChType *obj, uint16_t firstValue, uint16_t secondValue);

/*! \brief Enables or disables the channel output
 *
 * This function enables or disables the channel output
 *
 * \param[in] obj : pointer to MFT PWM channel instance
 * \param[in] enable : whether to enable channel output
 *                     - true : enable PWM output
 *                     - false : disable PWM output
 */
extern void MftPwmCh_EnableOutput(MftPwmChType *obj, bool enable);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _MFT_PWM_CH_H_ */
