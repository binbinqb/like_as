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

#ifndef _LPIT_DRV_H_
#define _LPIT_DRV_H_

/*! \brief Contains public interface to various functions related
 *         to the driver of LPIT (Low Power Interrupt Timer)
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * the defines
 ******************************************************************************/

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief Definition of mode options available for the LPIT timer
 */
typedef enum
{
    LPITDRV_PERIODIC_COUNTER      = 0x00U, /*!< 32-bit Periodic Counter        */
    LPITDRV_DUAL_PERIODIC_COUNTER = 0x01U, /*!< Dual 16-bit Periodic Counter   */
    LPITDRV_TRIGGER_ACCUMULATOR   = 0x02U, /*!< 32-bit Trigger Accumulator     */
    LPITDRV_INPUT_CAPTURE         = 0x03U  /*!< 32-bit Trigger Input Capture   */
} LpitDrv_TimerModesType;

/*! \brief Definition of trigger source options.
 */
typedef enum
{
    LPITDRV_TRIGGERSOURCE_EXTERNAL = 0x00U, /*!< Use external trigger  */
    LPITDRV_TRIGGERSOURCE_INTERNAL = 0x01U  /*!< Use internal trigger  */
} LpitDrv_TriggerSourceType;

/*! \brief Definition of configuration of LPIT timer channel
 */
typedef struct _LpitDrv_ChannelConfigType_
{
    LpitDrv_TimerModesType    timerMode;     /*!< Operation mode of timer channel                               */
    uint32_t                  period;        /*!< Period of timer channel                                       */
    LpitDrv_TriggerSourceType triggerSource; /*!< Selects between internal and external trigger sources         */
    uint32_t                  triggerSelect; /*!< Selects one trigger from the internal trigger sources
                                                  this field makes sense if trigger source is internal          */
    bool enableReloadOnTrigger;              /*!< True: Timer channel will reload on selected trigger
                                                  False: Timer channel will not reload on selected trigger      */
    bool enableStopOnInterrupt;              /*!< True: Timer will stop after timeout
                                                  False: Timer channel does not stop after timeout              */
    bool enableStartOnTrigger;               /*!< True: Timer channel starts to decrement when rising edge
                                                  on selected trigger is detected.
                                                  False: Timer starts to decrement immediately based on
                                                  restart condition                                             */
    bool chainChannel;                       /*!< Channel chaining enable                                       */
    bool isInterruptEnabled;                 /*!< Timer channel interrupt generation enable                     */
} LpitDrv_ChannelConfigType;

/*! \brief Definition of configuration of LPIT driver
 */
typedef struct _LpitDrv_ConfigType_
{
    bool enableRunInDebug;    /*!< True: Timer channels continue to run in debug mode
                                   False: Timer channels stop in debug mode               */
    bool enableRunInLowPower; /*!< True: Timer channels continue to run in low power mode
                                   False: Timer channels stop in low power mode           */
} LpitDrv_ConfigType;

/* Forward declaration of LPIT register */
struct _LpitRegType_;

/*! \brief The definition of LPIT driver class
 */
typedef struct _LpitDrvType_
{
    struct _LpitRegType_ *reg;
} LpitDrvType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Initializes the LPIT driver module
 *
 * This function initializes LPIT driver by setting the register
 * instance to it.
 *
 * \param[in] obj : pointer to LPIT driver instance
 * \param[in] reg : pointer to LPIT register instance
 */
extern void LpitDrv_Init(LpitDrvType *obj, struct _LpitRegType_ *reg);

/*! \brief Get default configures the LPIT module for configuration structure
 *
 * This function gets default configures the LPIT module for user configuration structure
 *
 * \note This function is a "static" function regardless of instances
 *
 * \param[out] userConfig : pointer to configuration structure
 */
extern void LpitDrv_GetDefaultConfig(LpitDrv_ConfigType *userConfig);

/*! \brief Configures the LPIT module from a user configuration structure
 *
 * This function resets LPIT module, enables the LPIT module, configures LPIT
 * module operation in Debug and LowPower mode. The LPIT configuration structure shall
 * be passed as arguments.
 * This configuration structure affects all timer channels.
 * This function should be called before calling any other LPIT driver function.
 *
 * This is an example demonstrating how to define a LPIT configuration structure:
   \code
   LpitDrv_ConfigType lpitConfig =
   {
       .enableRunInDebug = false,
       .enableRunInLowPower = true
   };
   \endcode
 *
 * \param[in] obj : pointer to LPIT driver instance
 * \param[in] userConfig : pointer to configuration structure
 */
extern void LpitDrv_Configure(LpitDrvType *obj, const LpitDrv_ConfigType *userConfig);

/*! \brief Gets the default timer channel configuration
 *
 * This function gets the default timer channel configuration structure, with the following settings:
 * - Timer mode: 32-bit Periodic Counter
 * - Period: 1000000
 * - Trigger sources: External trigger
 * - Trigger select: Trigger from channel 0
 * - Reload on trigger: Disable
 * - Stop on interrupt : Disable
 * - Start on trigger: Disable
 * - Channel chaining: Disable
 * - Interrupt generating: Enable
 *
 * \note This function is a "static" function regardless of instances
 *
 * \param[out] userChannelConfig : pointer to channel configuration structure
 */
extern void LpitDrv_GetDefaultChannelConfig(LpitDrv_ChannelConfigType *userChannelConfig);

/*! \brief Initializes the LPIT channel.
 *
 * This function initializes the LPIT timers by using a channel, this function
 * configures timer channel chaining, timer channel mode, timer channel period,
 * interrupt generation, trigger source, trigger select, reload on trigger,
 * stop on interrupt and start on trigger.
 * The timer channel number and its configuration structure shall be passed as arguments.
 * Timer channels do not start counting by default after calling this function.
 *
 * The function 'StartTimerChannels' must be called to start the timer channel counting.
 * In order to re-configures the period, call the 'SetTimerPeriodByCount'.
 *
 * This is an example demonstrating how to define a LPIT channel configuration structure:
   \code
   LpitDrv_ChannelConfigType lpitInitConfig =
   {
       .timerMode = LPITDRV_PERIODIC_COUNTER,
       .period = 1000000U,
       .triggerSource = LPITDRV_TRIGGERSOURCE_INTERNAL,
       .triggerSelect = 1U,
       .enableReloadOnTrigger = false,
       .enableStopOnInterrupt = false,
       .enableStartOnTrigger = false,
       .chainChannel = false,
       .isInterruptEnabled = true
   };
   \endcode
 *
 * \param[in] obj : pointer to LPIT driver instance
 * \param[in] channel : timer channel number
 * \param[in] userChannelConfig : pointer to configuration structure
 * \return The result of configuring channel
 *         - false : failed
 *         - true : success
 */
extern bool LpitDrv_ConfigureChannel(LpitDrvType *obj, uint8_t channel, const LpitDrv_ChannelConfigType *userChannelConfig);

/*! \brief Starts the timer channel counting.
 *
 * This function allows starting timer channels simultaneously .
 * After calling this function, timer channels are going operate depend on mode and
 * control bits which controls timer channel start, reload and restart.
 *
 * \param[in] obj : pointer to LPIT driver instance
 * \param[in] mask : timer channels starting mask that decides which channels will be started
 *            For example:
 *            - with mask = 0x01U then channel 0 will be started
 *            - with mask = 0x02U then channel 1 will be started
 *            - with mask = 0x03U then channel 0 and channel 1 will be started
 */
extern void LpitDrv_StartTimerChannels(LpitDrvType *obj, uint32_t mask);

/*! \brief Stops the timer channel counting.
 *
 * This function allows stop timer channels simultaneously from counting.
 * Timer channels reload their periods respectively after the next time
 * they call the LPIT_DRV_StartTimerChannels. Note that: In 32-bit Trigger Accumulator
 * mode, the counter will load on the first trigger rising edge.
 *
 * \param[in] obj : pointer to LPIT driver instance
 * \param[in] mask : timer channels stopping mask that decides which channels will be stopped
 *            For example:
 *            - with mask = 0x01U then channel 0 will be stopped
 *            - with mask = 0x02U then channel 1 will be stopped
 *            - with mask = 0x03U then channel 0 and channel 1 will be stopped
 */
extern void LpitDrv_StopTimerChannels(LpitDrvType *obj, uint32_t mask);

/*! \brief Sets the timer channel period in count unit.
 *
 * This function sets the timer channel period in count unit.
 * The counter period of a running timer channel can be modified by first setting
 * a new load value, the value will be loaded after the timer channel expires.
 * To abort the current cycle and start a timer channel period with the new value,
 * the timer channel must be disabled and enabled again.
 *
 * \param[in] obj : pointer to LPIT driver instance
 * \param[in] channel : timer channel number
 * \param[in] count : timer channel period in count unit
 */
extern void LpitDrv_SetTimerPeriodByCount(LpitDrvType *obj, uint8_t channel, uint32_t count);

/*! \brief Sets the timer channel period in count unit.
 *
 * This function sets the timer channel period in count unit when timer channel
 * mode is dual 16 periodic counter mode.
 * The counter period of a running timer channel can be modified by first setting
 * a new load value, the value will be loaded after the timer channel expires.
 * To abort the current cycle and start a timer channel period with the new value,
 * the timer channel must be disabled and enabled again.
 *
 * \param[in] obj : pointer to LPIT driver instance
 * \param[in] channel : timer channel number
 * \param[in] periodHigh : period of higher 16 bit in count unit
 * \param[in] periodLow : period of lower 16 bit in count unit
 */
extern void LpitDrv_SetTimerPeriodInDual16ModeByCount(LpitDrvType *obj, uint8_t channel, uint16_t periodHigh, uint16_t periodLow);

/*! \brief Gets the current timer channel period in count unit.
 *
 * This function returns current period of timer channel given as argument.
 *
 * \param[in] obj : pointer to LPIT driver instance
 * \param[in] channel : timer channel number
 * \param[out] period : pointer to the timer channel period in count unit
 * \return the result of getting period
 *         - false : failed
 *         - true : success
 */
extern bool LpitDrv_GetTimerPeriodByCount(const LpitDrvType *obj, uint8_t channel, uint32_t *period);

/*! \brief Gets the current timer channel counting value in count.
 *
 * This function returns the real-time timer channel counting value, the value in
 * a range from 0 to timer channel period.
 * Need to make sure the running time does not exceed the timer channel period.
 *
 * \param[in] obj : pointer to LPIT driver instance
 * \param[in] channel : timer channel number
 * \param[out] time : current timer channel counting value in count
 * \return the result of getting counting value
 *         - false : failed
 *         - true : success
 */
extern bool LpitDrv_GetCurrentTimerCount(const LpitDrvType *obj, uint8_t channel, uint32_t *time);

/*! \brief Enables the interrupt generation of timer channel.
 *
 * This function allows enabling interrupt generation of timer channel
 * when timeout occurs or input trigger occurs.
 *
 * \param[in] obj : pointer to LPIT driver instance
 * \param[in] mask : the mask that decides which channels will be enabled interrupt.
 *            For example:
 *            - with mask = 0x01u then the interrupt of channel 0 will be enabled
 *            - with mask = 0x02u then the interrupt of channel 1 will be enabled
 *            - with mask = 0x03u then the interrupt of channel 0 and channel 1 will be enabled
 */
extern void LpitDrv_EnableTimerChannelInterrupt(LpitDrvType *obj, uint32_t mask);

/*! \brief Disables the interrupt generation of timer channel.
 *
 * This function allows disabling interrupt generation of timer channel
 * when timeout occurs or input trigger occurs.
 *
 * \param[in] obj : pointer to LPIT driver instance
 * \param[in] mask : the mask that decides which channels will be disable interrupt.
 *            For example:
 *            - with mask = 0x01u then the interrupt of channel 0 will be disable
 *            - with mask = 0x02u then the interrupt of channel 1 will be disable
 *            - with mask = 0x03u then the interrupt of channel 0 and channel 1 will be disable
 */
extern void LpitDrv_DisableTimerChannelInterrupt(LpitDrvType *obj, uint32_t mask);

/*! \brief Gets the current interrupt flag of timer channels.
 *
 * This function gets the current interrupt flag of timer channels.
 * In compare modes, the flag sets to 1 at the end of the timer period.
 * In capture modes, the flag sets to 1 when the trigger asserts.
 *
 * \param[in] obj : pointer to LPIT driver instance
 * \param[in] mask : the interrupt flag getting mask that decides which channels will be got interrupt flag.
 *            For example:
 *            - with mask = 0x01u then the interrupt flag of channel 0 only will be got
 *            - with mask = 0x02u then the interrupt flag of channel 1 only will be got
 *            - with mask = 0x03u then the interrupt flags of channel 0 and channel 1 will be got
 * \return current interrupt flag of timer channels
 * \note return 0 if mask is invalid
 */
extern uint32_t LpitDrv_GetInterruptFlagTimerChannels(const LpitDrvType *obj, uint32_t mask);

/*! \brief Clears the interrupt flag of timer channels.
 *
 * This function clears the interrupt flag of timer channels after
 * their interrupt event occurred.
 *
 * \param[in] obj : pointer to LPIT driver instance
 * \param[in] mask : the interrupt flag clearing mask that decides which channels will be cleared interrupt flag
 *            For example:
 *            - with mask = 0x01u then the interrupt flag of channel 0 only will be cleared
 *            - with mask = 0x02u then the interrupt flag of channel 1 only will be cleared
 *            - with mask = 0x03u then the interrupt flags of channel 0 and channel 1 will be cleared
 */
extern void LpitDrv_ClearInterruptFlagTimerChannels(LpitDrvType *obj, uint32_t mask);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _LPIT_DRV_H_ */
