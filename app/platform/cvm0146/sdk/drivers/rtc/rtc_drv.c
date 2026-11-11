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

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stddef.h>
#include "rtc_drv.h"
#include "rtc_reg.h"

/*******************************************************************************
 * the defines
 ******************************************************************************/

/* Constants to transfer between TimeData and seconds*/
#define SECONDS_IN_A_DAY    (86400UL)
#define SECONDS_IN_A_HOUR   (3600U)
#define SECONDS_IN_A_MIN    (60U)
#define MINS_IN_A_HOUR      (60U)
#define HOURS_IN_A_DAY      (24U)
#define DAYS_IN_A_YEAR      (365U)
#define DAYS_IN_A_LEAP_YEAR (366U)
#define YEAR_RANGE_START    (1970U)
#define YEAR_RANGE_END      (2099U)
#define MONTH_RANGE_START   (1U)
#define MONTH_RANGE_END     (12U)
#define DAY_RANGE_START     (1U)
#define DAY_RANGE_END       (31U)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief RTC register lock
 */
typedef enum
{
    RTCDRV_LOCK_REG_LOCK   = 0x00U, /*!< RTC Lock Register lock         */
    RTCDRV_STATUS_REG_LOCK = 0x01U, /*!< RTC Status Register lock       */
    RTCDRV_CTRL_REG_LOCK   = 0x02U, /*!< RTC Control Register lock      */
} RtcDrv_LockRegSelectType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/* Table of month length (in days) for the Un-leap-year*/
const uint8_t c_unLeapYear[] = {0U, 31U, 28U, 31U, 30U, 31U, 30U, 31U, 31U, 30U, 31U, 30U, 31U};

/* Table of month length (in days) for the Leap-year*/
const uint8_t c_leapYear[] = {0U, 31U, 29U, 31U, 30U, 31U, 30U, 31U, 31U, 30U, 31U, 30U, 31U};

/* Number of days from begin of the non Leap-year*/
const uint16_t c_monthDays[] = {0U, 0U, 31U, 59U, 90U, 120U, 151U, 181U, 212U, 243U, 273U, 304U, 334U};

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Gets the register lock status
 *
 * This function gets the register lock status
 *
 * \param[in] obj : pointer to RTC driver instance
 * \param[in] lockRegSelect : the select of register lock
 * \return the status of register lock
 *         - false : not locked
 *         - true : locked
 */
static inline bool RtcDrv_IsRegisterLocked(const RtcDrvType *obj, RtcDrv_LockRegSelectType lockRegSelect)
{
    bool result = false;

    switch(lockRegSelect)
    {
    case RTCDRV_LOCK_REG_LOCK:
        result = ((RtcReg_GetLrLrl(obj->reg) == 0) ? true : false);
        break;
    case RTCDRV_STATUS_REG_LOCK:
        result = ((RtcReg_GetLrSrl(obj->reg) == 0) ? true : false);
        break;
    case RTCDRV_CTRL_REG_LOCK:
        result = ((RtcReg_GetLrCrl(obj->reg) == 0) ? true : false);
        break;
    default:
        /* This statement should not be reached */
        break;
    }
    return result;
}

/*! \brief Configure the RTC Clock out pin
 *
 * This function allows you to configure the RTC Clock out pin.
 *
 * \param[in] obj : pointer to RTC driver instance
 * \param[in] config : the clock out configuration
 * \return the result of the configure operation
 *         - false : failed
 *         - true : success
 */
static inline bool RtcDrv_ConfigureClockOut(RtcDrvType *obj, RtcDrv_ClkOutConfigType config)
{
    bool result = true;

    if(RtcDrv_IsRegisterLocked(obj, RTCDRV_CTRL_REG_LOCK) == true)
    {
        result = false;
    }
    else
    {
        switch(config)
        {
        case RTCDRV_CLKOUT_DISABLED:
            RtcReg_SetCrCpe(obj->reg, 0);
            break;
        case RTCDRV_CLKOUT_SRC_TSIC:
            RtcReg_SetCrCps(obj->reg, 0);
            RtcReg_SetCrCpe(obj->reg, 1);
            break;
        case RTCDRV_CLKOUT_SRC_RTC:
            RtcReg_SetCrCps(obj->reg, 1);
            RtcReg_SetCrClkO(obj->reg, 0);
            RtcReg_SetCrCpe(obj->reg, 1);
            break;
        default:
            /* This statement should not be reached */
            break;
        }
    }
    return result;
}

/*! \brief Checks if the TCE can be written
 *
 * This function checks the following conditions to find if the
 * Time Counter Enable bit is writable.
 * - if Update Mode bitfield if 1 and:
 *   - Time is invalid or
 *   - Time Seconds Register has overflowed or
 *   - Time Counter is disabled,
 * then the TCE bit can be set even if Status Register is locked.
 *
 * \param[in] obj : pointer to RTC driver instance
 * \param[in] config : the clock out configuration
 * \return the result of the configure operation
 *         - false : failed
 *         - true : success
 */
static inline bool RtcDrv_CanWriteTce(const RtcDrvType *obj)
{
    bool result = false;

    /* Check if the status register is locked */
    if(RtcDrv_IsRegisterLocked(obj, RTCDRV_STATUS_REG_LOCK) == false)
    {
        result = true;
    }
    /* Get the Update Mode bit */
    else if(RtcReg_GetCrUm(obj->reg) == 1)
    {
        bool tifFlagSet = RtcReg_GetSrTif(obj->reg) == 1;
        bool tofFlagSet = RtcReg_GetSrTof(obj->reg) == 1;
        bool tceFlagSet = RtcReg_GetSrTce(obj->reg) == 1;

        /* Check for the specified conditions */
        if((tifFlagSet == true) || (tofFlagSet == true) || (tceFlagSet == false))
        {
            result = true;
        }
    }
    else
    {
        result = false;
    }

    /* Return the exit code */
    return result;
}

void RtcDrv_Init(RtcDrvType *obj, struct _RtcRegType_ *const reg)
{
    obj->reg = reg;

    /* Initialize runtime structure */
    obj->runtimeConfig.isAlarmTimeNew        = false;
    obj->runtimeConfig.isAlarmConfigSet      = false;
    obj->runtimeConfig.isIntConfigSet        = false;
    obj->runtimeConfig.isSecondsIntConfigSet = false;
}

void RtcDrv_GetDefaultConfig(RtcDrv_ConfigType *userConfig)
{
    userConfig->clockOutConfig            = RTCDRV_CLKOUT_DISABLED;
    userConfig->updateEnable              = true;
    userConfig->nonSupervisorAccessEnable = true;
}

bool RtcDrv_Configure(RtcDrvType *obj, const RtcDrv_ConfigType *userConfig)
{
    bool retval = false;

    if(RtcDrv_IsRegisterLocked(obj, RTCDRV_CTRL_REG_LOCK) == false)
    {                                 /* not locked */
        RtcReg_SetCrSwr(obj->reg, 1); /* Write 1 to reset */
        while(RtcReg_GetSrTif(obj->reg) == 0)
        {
            ;
        }
        RtcReg_SetCrSwr(obj->reg, 0);
        RtcDrv_ConfigureClockOut(obj, userConfig->clockOutConfig);
        RtcReg_SetCrUm(obj->reg, userConfig->updateEnable ? 1 : 0);
        RtcReg_SetCrSup(obj->reg, userConfig->nonSupervisorAccessEnable ? 1 : 0);
        retval = true;
    }

    return retval;
}

bool RtcDrv_StartCounter(RtcDrvType *obj)
{
    /* Check if the TCE is writable and return corresponding result */
    if(RtcDrv_CanWriteTce(obj) == false)
    {
        return false;
    }
    /* if the counter is already enabled */
    if(RtcReg_GetSrTce(obj->reg) == 1)
    {
        return false;
    }
    RtcReg_SetSrCsd(obj->reg, 1);
    /* if the counter is already CSD reg will set */
    while(RtcReg_GetSrCsd(obj->reg) == 0)
    {
        ;
    }
    RtcReg_SetSrTce(obj->reg, 1);
    return true;
}

bool RtcDrv_StopCounter(RtcDrvType *obj)
{
    /* Check if the TCE is writable and return corresponding result */
    if(RtcDrv_CanWriteTce(obj) == false)
    {
        return false;
    }
    /* if the counter is already enabled */
    if(RtcReg_GetSrTce(obj->reg) == 1)
    {
        RtcReg_SetSrTce(obj->reg, 0);
    }
    /* Read TCE bit to check if the counter is really disabled */
    return RtcReg_GetSrTce(obj->reg) == 0;
}

bool RtcDrv_GetCurrentTimeDate(RtcDrvType *obj, RtcDrv_TimeDateType *currentTime)
{
    bool     result = false;
    uint32_t seconds;
    uint32_t tempSeconds;

    /* Make two consecutive reads to ensure that the read was not
     * done when the counter is incrementing. */
    tempSeconds = RtcReg_GetTsr(obj->reg);
    seconds     = RtcReg_GetTsr(obj->reg);
    /* If the read was done when the counter was incrementing,
     * try and read again. */
    if(tempSeconds != seconds)
    {
        tempSeconds = RtcReg_GetTsr(obj->reg); /* get the current time again */
        if(tempSeconds == seconds)
        {
            /* Convert the current time from seconds to time date structure */
            RtcDrv_ConvertSecondsToTimeDate(seconds, currentTime);
            result = true;
        }
    }
    else
    {
        /* Convert the current time from seconds to time date structure */
        RtcDrv_ConvertSecondsToTimeDate(seconds, currentTime);
        result = true;
    }

    return result;
}

bool RtcDrv_SetTimeDate(RtcDrvType *obj, const RtcDrv_TimeDateType *time)
{
    /* Check if the TimeDate format is valid */
    if(RtcDrv_IsTimeDateCorrectFormat(time) == false)
    {
        return false;
    }
    /* Check if the TCE is writable and return corresponding result */
    if(RtcDrv_CanWriteTce(obj) == false)
    {
        return false;
    }
    /* Check if the counter is already started */
    if(RtcReg_GetSrTce(obj->reg) == 1)
    {
        return false;
    }

    /* Convert the desired time to seconds */
    uint32_t seconds = 0;
    RtcDrv_ConvertTimeDateToSeconds(time, &seconds);
    RtcReg_SetTsr(obj->reg, seconds);
    return true;
}

bool RtcDrv_ConfigureRegisterLock(RtcDrvType *obj, const RtcDrv_RegLockConfigType *lockConfig)
{
    if(RtcReg_GetLrLrl(obj->reg) == 0)
    {
        return false;
    }

    /* Configure Control register lock */
    if(lockConfig->controlRegisterLock)
    {
        RtcReg_SetLrCrl(obj->reg, 0); /* Write 0 to lock */
    }
    /* Configure Status register lock */
    if(lockConfig->statusRegisterLock)
    {
        RtcReg_SetLrSrl(obj->reg, 0); /* Write 0 to lock */
    }
    /* Configure Lock register lock */
    if(lockConfig->lockRegisterLock)
    {
        RtcReg_SetLrLrl(obj->reg, 0); /* Write 0 to lock */
    }
    return true;
}

void RtcDrv_GetRegisterLock(RtcDrvType *obj, RtcDrv_RegLockConfigType *lockConfig)
{
    /* For the Lock Register */
    lockConfig->lockRegisterLock = RtcDrv_IsRegisterLocked(obj, RTCDRV_LOCK_REG_LOCK);
    /* For the Control Register */
    lockConfig->controlRegisterLock = RtcDrv_IsRegisterLocked(obj, RTCDRV_CTRL_REG_LOCK);
    /* For the Status Register */
    lockConfig->statusRegisterLock = RtcDrv_IsRegisterLocked(obj, RTCDRV_STATUS_REG_LOCK);
}

void RtcDrv_ConfigureOverFlowInt(RtcDrvType *obj, const RtcDrv_InterruptConfigType *intConfig)
{
    obj->runtimeConfig.intConfig      = *intConfig;
    obj->runtimeConfig.isIntConfigSet = true;
    RtcReg_SetIerTioe(obj->reg, intConfig->overflowIntEnable ? 1 : 0);
}

void RtcDrv_ConfigureSecondsInt(RtcDrvType *obj, const RtcDrv_SecondsIntConfigType *intConfig)
{
    obj->runtimeConfig.secondsIntConfig      = *intConfig;
    obj->runtimeConfig.isSecondsIntConfigSet = true;

    RtcReg_SetIerTsie(obj->reg, 0);
    RtcReg_SetIerTsic(obj->reg, intConfig->secondIntConfig);
    RtcReg_SetIerTsie(obj->reg, intConfig->secondIntEnable ? 1 : 0);
}

bool RtcDrv_ConfigureAlarm(RtcDrvType *obj, const RtcDrv_AlarmConfigType *alarmConfig)
{
    bool     result = false;
    uint32_t alarmTime;
    uint32_t currentTime;

    /* Check if the alarm time is in a correct format */
    if(RtcDrv_IsTimeDateCorrectFormat(&alarmConfig->alarmTime) == true)
    {
        /* Convert the time date to seconds */
        RtcDrv_ConvertTimeDateToSeconds(&alarmConfig->alarmTime, &alarmTime);
        /* Get current time in seconds */
        currentTime = RtcReg_GetTsr(obj->reg);
        /* Check if the alarm time is greater than current time */
        if(alarmTime > currentTime)
        {
            obj->runtimeConfig.alarmConfig      = *alarmConfig;
            obj->runtimeConfig.isAlarmConfigSet = true;
            RtcReg_SetIerTaie(obj->reg, 0);
            RtcReg_SetTar(obj->reg, alarmTime);
            RtcReg_SetIerTaie(obj->reg, alarmConfig->alarmIntEnable);
        }
    }

    return result;
}

void RtcDrv_GetAlarmConfig(const RtcDrvType *obj, RtcDrv_AlarmConfigType *alarmConfig)
{
    if(obj->runtimeConfig.isAlarmConfigSet)
    {
        *alarmConfig = obj->runtimeConfig.alarmConfig;
    }
}

bool RtcDrv_IsAlarmPending(const RtcDrvType *obj)
{
    return RtcReg_GetSrTaf(obj->reg) == 1;
}

void RtcDrv_ConvertSecondsToTimeDate(uint32_t seconds, RtcDrv_TimeDateType *timeDate)
{
    uint8_t  i;
    bool     yearLeap     = false;
    uint32_t numberOfDays = 0U;
    uint32_t tempSeconds;
    uint16_t daysInYear;

    /* Because the starting year(1970) is not leap, set the daysInYear
     * variable with the number of the days in a normal year
     */
    daysInYear = DAYS_IN_A_YEAR;
    /* Set the year to the beginning of the range */
    timeDate->year = YEAR_RANGE_START;
    /* Get the number of days */
    numberOfDays = seconds / SECONDS_IN_A_DAY;
    /* Get the number of seconds remaining */
    tempSeconds = seconds % SECONDS_IN_A_DAY;
    /* Get the current hour */
    timeDate->hour = (uint16_t)(tempSeconds / SECONDS_IN_A_HOUR);
    /* Get the remaining seconds */
    tempSeconds = tempSeconds % SECONDS_IN_A_HOUR;
    /* Get the minutes */
    timeDate->minutes = (uint16_t)(tempSeconds / SECONDS_IN_A_MIN);
    /* Get seconds */
    timeDate->seconds = (uint8_t)(tempSeconds % SECONDS_IN_A_MIN);
    /* Get the current year */
    while(numberOfDays >= daysInYear)
    {
        /* Increment year if the number of days is greater than the ones in one year */
        timeDate->year++;
        /* Subtract the number of the days */
        numberOfDays -= daysInYear;

        /* Check if the year is leap or unleap */
        if(!RtcDrv_IsYearLeap(timeDate->year))
        {
            daysInYear = DAYS_IN_A_YEAR;
        }
        else
        {
            daysInYear = DAYS_IN_A_LEAP_YEAR;
        }
    }
    /* Add the current day */
    numberOfDays += 1U;
    /* Check if the current year is leap */
    yearLeap = RtcDrv_IsYearLeap(timeDate->year);
    /* Get the month */
    for(i = 1U; i <= 12U; i++)
    {
        uint32_t daysInCurrentMonth = ((yearLeap == true) ? (uint32_t)c_leapYear[i] : (uint32_t)c_unLeapYear[i]);
        if(numberOfDays <= daysInCurrentMonth)
        {
            timeDate->month = (uint16_t)i;
            break;
        }
        else
        {
            numberOfDays -= daysInCurrentMonth;
        }
    }
    /* Set the current day */
    timeDate->day = (uint16_t)numberOfDays;
}

void RtcDrv_ConvertTimeDateToSeconds(const RtcDrv_TimeDateType *timeDate, uint32_t *seconds)
{
    /* Declare local variables */
    uint16_t year;

    /* Convert years to seconds */
    (*seconds) = (uint32_t)(DAYS_IN_A_YEAR * (uint32_t)(SECONDS_IN_A_DAY));
    (*seconds) *= ((uint32_t)timeDate->year - YEAR_RANGE_START);

    /* Add the seconds from the leap years */
    for(year = YEAR_RANGE_START; year < timeDate->year; year++)
    {
        if(RtcDrv_IsYearLeap(year))
        {
            (*seconds) += SECONDS_IN_A_DAY;
        }
    }

    /* If the current year is leap and 29th of February has passed, add
     * another day to seconds passed.
     */
    if(RtcDrv_IsYearLeap(year) && timeDate->month > 2U)
    {
        (*seconds) += SECONDS_IN_A_DAY;
    }

    (*seconds) += c_monthDays[timeDate->month] * SECONDS_IN_A_DAY;
    (*seconds) += (uint32_t)(((uint32_t)timeDate->day - 1U) * (uint32_t)SECONDS_IN_A_DAY);
    (*seconds) += (uint32_t)((uint32_t)timeDate->hour * SECONDS_IN_A_HOUR) + (uint32_t)((uint32_t)timeDate->minutes * SECONDS_IN_A_MIN) + (uint32_t)((uint32_t)timeDate->seconds);
}

bool RtcDrv_IsYearLeap(uint16_t year)
{
    bool isYearLeap = false;

    if((year % 4U) > 0U)
    {
        isYearLeap = false;
    }
    else if((year % 100U) > 0U)
    {
        isYearLeap = true;
    }
    else if((year % 400U) > 0U)
    {
        isYearLeap = false;
    }
    else
    {
        isYearLeap = true;
    }

    return isYearLeap;
}

bool RtcDrv_IsTimeDateCorrectFormat(const RtcDrv_TimeDateType *timeDate)
{
    /* Declare local variables */
    bool           retval = true;
    const uint8_t *pDays;

    /* Set the days-in-month table for the corresponding year */
    pDays = RtcDrv_IsYearLeap(timeDate->year) ? (c_leapYear) : (c_unLeapYear);

    /* Check if the time and date are in the correct ranges */
    if((timeDate->year < YEAR_RANGE_START) || (timeDate->year > YEAR_RANGE_END)
       || (timeDate->month < 1U) || (timeDate->month > 12U)
       || (timeDate->day < 1U) || (timeDate->day > 31U)
       || (timeDate->hour >= HOURS_IN_A_DAY)
       || (timeDate->minutes >= MINS_IN_A_HOUR) || (timeDate->seconds >= SECONDS_IN_A_MIN))
    {
        retval = false;
    }
    /* Check if the day is a valid day from the corresponding month */
    else if(timeDate->day > pDays[timeDate->month])
    {
        retval = false;
    }
    else
    {
        retval = true;
    }

    return retval;
}

bool RtcDrv_GetNextAlarmTime(RtcDrvType *obj, RtcDrv_TimeDateType *alarmTime)
{
    bool     result = false;
    uint32_t alarmInSec;
    /* Check if is a new alarm and if true update alarm time date format from time seconds */
    if(obj->runtimeConfig.isAlarmTimeNew == true)
    {
        alarmInSec = RtcReg_GetTar(obj->reg);
        RtcDrv_ConvertSecondsToTimeDate(alarmInSec, alarmTime);
        result = true;
    }
    return result;
}

void RtcDrv_IrqHandler(RtcDrvType *obj)
{
    uint32_t tempSeconds;

    /* Check if an alarm has occurred */
    if(RtcReg_GetSrTaf(obj->reg) == 1)
    {
        /* If the alarm interrupt configuration has been defined process the
         * alarm IRQ
         */
        if(obj->runtimeConfig.isAlarmConfigSet)
        {
            /* If recurrence is enabled modify the alarm register to the next
             * alarm.
             */
            if((obj->runtimeConfig.alarmConfig.numberOfRepeats > 0UL) || (obj->runtimeConfig.alarmConfig.repeatForever == true))
            {
                /* Get current time */
                tempSeconds = RtcReg_GetTsr(obj->reg);
                /* Current time is incremented with the repetition value */
                tempSeconds += obj->runtimeConfig.alarmConfig.repetitionInterval;
                /* Set new value to trigger the alarm */
                RtcReg_SetTar(obj->reg, tempSeconds);

                obj->runtimeConfig.isAlarmTimeNew = true;
                /* If the alarm repeats forever, set number of repeats to 0
                 * to avoid an accidental trigger of the core overflow flag
                 */
                obj->runtimeConfig.alarmConfig.numberOfRepeats = (obj->runtimeConfig.alarmConfig.repeatForever == false) ? (obj->runtimeConfig.alarmConfig.numberOfRepeats - 1UL) : 0UL;
            }
            else
            {
                /* If the alarm does not repeat, write 0 to TAR to clear the
                 * alarm flag.
                 */
                RtcReg_SetTar(obj->reg, 0);
                obj->runtimeConfig.isAlarmTimeNew = false;
            }
            /* If the user has defined a callback, call it */
            if(obj->runtimeConfig.alarmConfig.alarmCallback != NULL)
            {
                obj->runtimeConfig.alarmConfig.alarmCallback(obj->runtimeConfig.alarmConfig.callbackParams);
            }
        }
    }

    /* Check if an overflow has occurred */
    if(RtcReg_GetSrTof(obj->reg) == 1)
    {
        /* If the overflow interrupt configuration has been defined process the IRQ */
        if(obj->runtimeConfig.isIntConfigSet)
        {
            if(obj->runtimeConfig.intConfig.overflowCallback != NULL)
            {
                obj->runtimeConfig.intConfig.overflowCallback(obj->runtimeConfig.intConfig.callbackParams);
            }
        }
    }
}

void RtcDrv_SecondsIrqHandler(RtcDrvType *obj)
{
    if(obj->runtimeConfig.isSecondsIntConfigSet && obj->runtimeConfig.secondsIntConfig.secondsCallback != NULL)
    {
        obj->runtimeConfig.secondsIntConfig.secondsCallback(obj->runtimeConfig.secondsIntConfig.callbackParams);
    }
}
