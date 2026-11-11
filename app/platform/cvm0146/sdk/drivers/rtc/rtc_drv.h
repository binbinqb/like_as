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

#ifndef _RTC_DRV_H_
#define _RTC_DRV_H_

/*! \brief Contains public interface to various functions related
 *         to the driver of RTC (Real Time Clock)
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/*! \addtogroup rtc_drv
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

/*! \brief Definition of RTC CLKOUT Pin Configuration.
 */
typedef enum
{
    RTCDRV_CLKOUT_DISABLED = 0x00U, /*!< Clock out disabled                                                                                     */
    RTCDRV_CLKOUT_SRC_TSIC = 0x01U, /*!< The prescaler output clock (as configured by TSIC) is output on RTC_CLKOUT.                            */
    RTCDRV_CLKOUT_SRC_RTC  = 0x02U, /*!< The RTC source clock is output on RTC_CLKOUT, provided it is output to other peripherals.    */
} RtcDrv_ClkOutConfigType;

/*! \brief Definition of RTC Timer Seconds Interrupt Configuration.
 */
typedef enum
{
    RTCDRV_SECOND_INT_1HZ   = 0x00U, /*!< Timer Seconds Interrupt Configuration 1 Hz      */
    RTCDRV_SECOND_INT_2HZ   = 0x01U, /*!< Timer Seconds Interrupt Configuration 2 Hz      */
    RTCDRV_SECOND_INT_4HZ   = 0x02U, /*!< Timer Seconds Interrupt Configuration 4 Hz      */
    RTCDRV_SECOND_INT_8HZ   = 0x03U, /*!< Timer Seconds Interrupt Configuration 8 Hz      */
    RTCDRV_SECOND_INT_16HZ  = 0x04U, /*!< Timer Seconds Interrupt Configuration 16 Hz     */
    RTCDRV_SECOND_INT_32HZ  = 0x05U, /*!< Timer Seconds Interrupt Configuration 32 Hz     */
    RTCDRV_SECOND_INT_64HZ  = 0x06U, /*!< Timer Seconds Interrupt Configuration 64 Hz     */
    RTCDRV_SECOND_INT_128HZ = 0x07U  /*!< Timer Seconds Interrupt Configuration 128 Hz    */
} RtcDrv_SecondIntConfigType;

/*! \brief RTC Time TimeDate.
 */
typedef struct _RtcDrv_TimeDateType_
{
    uint16_t year;    /*!< Year.                  */
    uint16_t month;   /*!< Month.                 */
    uint16_t day;     /*!< Day.                   */
    uint16_t hour;    /*!< Hour.                  */
    uint16_t minutes; /*!< Minutes.               */
    uint8_t  seconds; /*!< Seconds.               */
} RtcDrv_TimeDateType;

/*! \brief RTC Register Lock configuration
 */
typedef struct _RtcDrv_RegLockConfigType_
{
    bool lockRegisterLock;    /*!< Lock state of the Lock Register              */
    bool statusRegisterLock;  /*!< Lock state of the Status Register            */
    bool controlRegisterLock; /*!< Lock state of the Control Register           */
} RtcDrv_RegLockConfigType;

/*! \brief RTC Interrupt configuration
 */
typedef struct _RtcDrv_InterruptConfigType_
{
    bool overflowIntEnable;                         /*!< Enable Time Overflow Interrupt.         */
    void (*overflowCallback)(void *callbackParams); /*!< OverFlow Interrupt callback.            */
    void *callbackParams;                           /*!< OverFlow Interrupt callback parameters. */
} RtcDrv_InterruptConfigType;

/*! \brief RTC Seconds Interrupt configuration
 */
typedef struct _RtcDrv_SecondsIntConfigType_
{
    RtcDrv_SecondIntConfigType secondIntConfig;    /*!< Seconds Interrupt Configures The Frequency.           */
    bool                       secondIntEnable;    /*!< Seconds Interrupt Enable.                             */
    void (*secondsCallback)(void *callbackParams); /*!< Seconds Interrupt Callback.                           */
    void *callbackParams;                          /*!< Seconds Interrupt Callback Parameters.                */
} RtcDrv_SecondsIntConfigType;

/*! \brief RTC Alarm Interrupt Configuration
 */
typedef struct _RtcDrv_AlarmConfigType_
{
    RtcDrv_TimeDateType alarmTime;               /*!< Alarm TimeData.                                    */
    uint32_t            repetitionInterval;      /*!< Interval of repetition in sec                      */
    uint32_t            numberOfRepeats;         /*!< Number of alarm repeats                            */
    bool                repeatForever;           /*!< Repeat forever if set, discard number of repeats   */
    bool                alarmIntEnable;          /*!< Enable alarm interrupt                             */
    void (*alarmCallback)(void *callbackParams); /*!< Pointer to the user callback method.               */
    void *callbackParams;                        /*!< Pointer to the callback parameters.                */
} RtcDrv_AlarmConfigType;

/*! \brief RTC Configuration
 */
typedef struct _RtcDrv_ConfigType_
{
    RtcDrv_ClkOutConfigType clockOutConfig;            /*!< RTC CLKOUT Pin Configuration.                              */
    bool                    updateEnable;              /*!< RTC Update Mode configuration.                             */
    bool                    nonSupervisorAccessEnable; /*!< RTC Supervisor Access.                                     */
} RtcDrv_ConfigType;

/*! \brief RTC runtime structure
 */
typedef struct _RtcDrv_RuntimeConfigType_
{
    bool                        isAlarmTimeNew;        /*!< Check if there is a new alarm          */
    bool                        isAlarmConfigSet;      /*!< If the alarm configure set             */
    RtcDrv_AlarmConfigType      alarmConfig;           /*!< Alarm configuration                    */
    bool                        isIntConfigSet;        /*!< If the interrupt configure set         */
    RtcDrv_InterruptConfigType  intConfig;             /*!< Interrupt configuration                */
    bool                        isSecondsIntConfigSet; /*!< If the seconds interrupt configure set */
    RtcDrv_SecondsIntConfigType secondsIntConfig;      /*!< Time seconds interrupt configuration   */
} RtcDrv_RuntimeConfigType;

/* Forward declaration of related register */
struct _RtcRegType_;

/*! \brief The definition of RTC driver class
 */
typedef struct _RtcDrvType_
{
    struct _RtcRegType_     *reg;           /*!< pointer to the RTC register*/
    RtcDrv_RuntimeConfigType runtimeConfig; /*!< runtime configuration      */
} RtcDrvType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Initializes the RTC driver module
 *
 * This function initializes RTC driver by setting the register
 * instance to it.
 *
 * \param[in] obj : pointer to RTC driver instance
 * \param[in] reg : pointer to RTC register instance
 */
extern void RtcDrv_Init(RtcDrvType *obj, struct _RtcRegType_ *reg);

/*! \brief Get default configures the RTC module for configuration structure
 *
 * This function gets default configures the Rtc module for user configuration structure
 *
 * \note This function is a "static" function regardless of instances
 *
 * \param[out] userConfig : pointer to configuration structure
 */
extern void RtcDrv_GetDefaultConfig(RtcDrv_ConfigType *userConfig);

/*! \brief Configures the RTC module from a user configuration structure
 *
 * This function configures the RTC instance with the settings
 * provided by the user via the userConfig parameter. The user must ensure
 * that clock is enabled for the RTC instance used.
 * In order to clear the CR Lock the user must perform a power-on reset.
 *
 * \param[in] obj : pointer to RTC driver instance
 * \param[in] userConfig : pointer to configuration structure
 * \return the result of the configure operation
 *         - false : configure failed
 *         - true : success
 */
extern bool RtcDrv_Configure(RtcDrvType *obj, const RtcDrv_ConfigType *userConfig);

/*! \brief Start RTC instance counter.
 *
 * This function starts the RTC counter.
 * Should use RtcDrv_Configure to configure the start time.
 *
 * \param[in] obj : pointer to RTC driver instance.
 */
extern bool RtcDrv_StartCounter(RtcDrvType *obj);

/*! \brief Disable RTC instance counter.
 *
 * This function stops the RTC counter
 *
 * \param[in] obj : pointer to RTC driver instance.
 */
extern bool RtcDrv_StopCounter(RtcDrvType *obj);

/*! \brief Get current TimeData from RTC instance.
 *
 * \param[in] obj : pointer to RTC driver instance.
 * \param[out] currentTime : pointer to Rtc TimeDate structure.
 * \return the result of the operation
 *         - false : the operation failed
 *         - true : success
 */
extern bool RtcDrv_GetCurrentTimeDate(RtcDrvType *obj, RtcDrv_TimeDateType *currentTime);

/*! \brief Set timedate for RTC instance.
 *
 * The user must stop the counter
 * before using this function. Otherwise it will return an error
 *
 * \param[in] obj : pointer to RTC driver instance.
 * \param[in] time : pointer to Rtc Time TimeDate structure.
 * \return the result of the operation
 *         - false : the operation failed, the time provided was invalid or the counter was not stopped
 *         - true : success
 */
extern bool RtcDrv_SetTimeDate(RtcDrvType *obj, const RtcDrv_TimeDateType *time);

/*! \brief This method configures register lock for the corresponding RTC instance.
 *
 * Remember that all the registers are unlocked only by software reset or power on reset.
 * (Except for CR that is unlocked only by POR).
 *
 * \param[in] obj : pointer to RTC driver instance.
 * \param[in] lockConfig : pointer to Rtc Register Lock structure.
 */
extern bool RtcDrv_ConfigureRegisterLock(RtcDrvType *obj, const RtcDrv_RegLockConfigType *lockConfig);

/*! \brief Get which registers are locked for RTC instance
 *
 * This function gets which registers are locked
 *
 * \param[in] obj : pointer to RTC driver instance.
 * \param[out] lockConfig : pointer to Rtc Register Lock structure.
 */
extern void RtcDrv_GetRegisterLock(RtcDrvType *obj, RtcDrv_RegLockConfigType *lockConfig);

/*! \brief Configure OverFlow Interrupt.
 *
 * This function configures the overflow interrupt
 *
 * \note Must disable the corresponding interrupt in the IRQ system
 *       before configure
 *
 * \param[in] obj : pointer to RTC driver instance.
 * \param[in] intConfig : pointer to the structure which holds the configuration
 */
extern void RtcDrv_ConfigureOverFlowInt(RtcDrvType *obj, const RtcDrv_InterruptConfigType *intConfig);

/*! \brief Configure Seconds Interrupt.
 *
 * This function configures the Seconds interrupt
 *
 * \note Must disable the corresponding interrupt in the IRQ system
 *       before configure
 *
 * \param[in] obj : pointer to RTC driver instance.
 * \param[in] intConfig : pointer to the structure which holds the configuration
 */
extern void RtcDrv_ConfigureSecondsInt(RtcDrvType *obj, const RtcDrv_SecondsIntConfigType *intConfig);

/*! \brief Configure alarm.
 *
 * This function configures the alarm with the configuration from the alarmConfig parameter
 *
 * \note Must disable the corresponding interrupt in the IRQ system
 *       before configure
 *
 * \param[in] obj : pointer to RTC driver instance.
 * \param[in] alarmConfig : pointer to Rtc Alarm Interrupt Configuration.
 * \return the result of the configure
 *         - false : the alarm time is invalid
 *         - true : configure success
 */
extern bool RtcDrv_ConfigureAlarm(RtcDrvType *obj, const RtcDrv_AlarmConfigType *alarmConfig);

/*! \brief Get alarm configuration for RTC instance
 *
 * This function gets the current alarm configuration
 *
 * \param[in] obj : pointer to RTC driver instance.
 * \param[out] alarmConfig : Pointer to the structure in which to store the alarm configuration
 */
extern void RtcDrv_GetAlarmConfig(const RtcDrvType *obj, RtcDrv_AlarmConfigType *alarmConfig);

/*! \brief Get Time Alarm Flag.
 *
 * This function gets the time alarm flag
 *
 * \param[in] obj : pointer to RTC driver instance.
 * \return if there is the alarm pending flag
 *         - false : no alarm pending
 *         - true : alarm is pending
 */
extern bool RtcDrv_IsAlarmPending(const RtcDrvType *obj);

/*! \brief Convert Seconds To TimeDate.
 *
 * This function converts the seconds to TimeDate format.
 *
 * \note This function is a "static" function regardless of instances
 *
 * \param[in] seconds : seconds.
 * \param[out] timeDate : pointer to Rtc TimeDate Structure.
 */
extern void RtcDrv_ConvertSecondsToTimeDate(uint32_t seconds, RtcDrv_TimeDateType *timeDate);

/*! \brief Convert TimeDate To Seconds.
 *
 * This function converts the TimeDate format to seconds
 *
 * \note This function is a "static" function regardless of instances
 *
 * \param[in] timeDate : Rtc TimeDate Structure.
 * \param[out] seconds : pointer to seconds.
 */
extern void RtcDrv_ConvertTimeDateToSeconds(const RtcDrv_TimeDateType *timeDate, uint32_t *seconds);

/*! \brief Check year is leap
 *
 * This function checks whether it's a leap year
 *
 * \note This function is a "static" function regardless of instances
 *
 * \param[in] year : Year to check
 * \return if the year is leap
 *         - false : not leap
 *         - true : the year is leap
 */
extern bool RtcDrv_IsYearLeap(uint16_t year);

/*! \brief Check if the date time struct is configured properly
 *
 * This function checks if the TimeDate format is valid.
 *
 * \note This function is a "static" function regardless of instances
 *
 * \param[in] config: timeDate Structure
 * \return if the time date is in the corrent format
 *         - false : not in the corrent format
 *         - true : the format is corrent
 */
extern bool RtcDrv_IsTimeDateCorrectFormat(const RtcDrv_TimeDateType *timeDate);

/*! \brief Gets the next alarm time
 *
 * \param[in] obj : pointer to RTC driver instance.
 * \param[in] config : pointer to Rtc Alarm Configuration Structure.
 * \param[in] gettime : pointer to Rtc TimeDate Structure.
 * \return the result of the operation
 *         - false : the get operation failed
 *         - true : success
 */
extern bool RtcDrv_GetNextAlarmTime(RtcDrvType *obj, RtcDrv_TimeDateType *alarmTime);

/*! \brief IRQ Handler
 *
 * This method is the API's Interrupt handler for generic and alarm IRQ.
 * It will handle the alarm repetition and calls the user callbacks if they
 * are not NULL.
 * Should be called in the IRQ handler of the IRQ system
 *
 * \param[in] obj : pointer to RTC driver instance.
 */
extern void RtcDrv_IrqHandler(RtcDrvType *obj);

/*! \brief Seconds IRQ Handler
 *
 * This method is the API's Interrupt handler for RTC Second
 * interrupt. This ISR will call the user callback if defined.
 * Should be called in the IRQ handler of the IRQ system
 *
 * \param[in] obj : pointer to RTC driver instance.
 */
extern void RtcDrv_SecondsIrqHandler(RtcDrvType *obj);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _RTC_REG_H_ */
