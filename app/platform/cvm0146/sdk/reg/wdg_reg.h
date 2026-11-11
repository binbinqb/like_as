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

#ifndef _WDG_REG_H_
#define _WDG_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the WDG (Watch Dog) Registers
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

/* CS Bit Fields */
#define WDG_CS_CLK_MASK       (0x70000u)
#define WDG_CS_CLK_SHIFT      (16u)
#define WDG_CS_CLK_WIDTH      (3u)
#define WDG_CS_WIN_MASK       (0x8000u)
#define WDG_CS_WIN_SHIFT      (15u)
#define WDG_CS_WIN_WIDTH      (1u)
#define WDG_CS_FLG_MASK       (0x4000u)
#define WDG_CS_FLG_SHIFT      (14u)
#define WDG_CS_FLG_WIDTH      (1u)
#define WDG_CS_PRES_MASK      (0x1000u)
#define WDG_CS_PRES_SHIFT     (12u)
#define WDG_CS_PRES_WIDTH     (1u)
#define WDG_CS_ULK_MASK       (0x800u)
#define WDG_CS_ULK_SHIFT      (11u)
#define WDG_CS_ULK_WIDTH      (1u)
#define WDG_CS_RCS_MASK       (0x400u)
#define WDG_CS_RCS_SHIFT      (10u)
#define WDG_CS_RCS_WIDTH      (1u)
#define WDG_CS_CSD_MASK       (0x200u)
#define WDG_CS_CSD_SHIFT      (9)
#define WDG_CS_CSD_WIDTH      (1)
#define WDG_CS_EN_MASK        (0x80u)
#define WDG_CS_EN_SHIFT       (7u)
#define WDG_CS_EN_WIDTH       (1u)
#define WDG_CS_INTR_MASK      (0x40u)
#define WDG_CS_INTR_SHIFT     (6u)
#define WDG_CS_INTR_WIDTH     (1u)
#define WDG_CS_UPDATE_MASK    (0x20u)
#define WDG_CS_UPDATE_SHIFT   (5u)
#define WDG_CS_UPDATE_WIDTH   (1u)
#define WDG_CS_DEBUG_MASK     (0x02u)
#define WDG_CS_DEBUG_SHIFT    (1)
#define WDG_CS_DEBUG_WIDTH    (1)
#define WDG_CS_STOP_MASK      (0x01u)
#define WDG_CS_STOP_SHIFT     (0u)
#define WDG_CS_STOP_WIDTH     (1u)

/* CNT Bit Fields */
#define WDG_CNT_HIGH_MASK     (0xFF00u)
#define WDG_CNT_HIGH_SHIFT    (8u)
#define WDG_CNT_HIGH_WIDTH    (8u)
#define WDG_CNT_LOW_MASK      (0xFFu)
#define WDG_CNT_LOW_SHIFT     (0u)
#define WDG_CNT_LOW_WIDTH     (8u)

/* TOVAL Bit Fields */
#define WDG_TOVAL_HIGH_MASK   (0xFF00u)
#define WDG_TOVAL_HIGH_SHIFT  (8u)
#define WDG_TOVAL_HIGH_WIDTH  (8u)
#define WDG_TOVAL_LOW_MASK    (0xFFu)
#define WDG_TOVAL_LOW_SHIFT   (0u)
#define WDG_TOVAL_LOW_WIDTH   (8u)

/* WIN Bit Fields */
#define WDG_WIN_HIGH_MASK     (0xFF00u)
#define WDG_WIN_HIGH_SHIFT    (8u)
#define WDG_WIN_HIGH_WIDTH    (8u)
#define WDG_WIN_LOW_MASK      (0xFFu)
#define WDG_WIN_LOW_SHIFT     (0u)
#define WDG_WIN_LOW_WIDTH     (8u)

/* TST Bit Fields */
#define WDG_TST_RST_FLG_MASK  (0x8u)
#define WDG_TST_RST_FLG_SHIFT (3)
#define WDG_TST_RST_FLG_WIDTH (1)
#define WDG_TST_RST_EN_MASK   (0x4u)
#define WDG_TST_RST_EN_SHIFT  (2)
#define WDG_TST_RST_EN_WIDTH  (1)
#define WDG_TST_MASK          (0x3u)
#define WDG_TST_SHIFT         (0)
#define WDG_TST_WIDTH         (2)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief The definition of WDG registers
 */
typedef struct _WdgRegType_
{
    volatile uint32_t CS;       /*!< 0000H */
    volatile uint32_t CNT;      /*!< 0004H */
    volatile uint32_t TOVAL;    /*!< 0008H */
    volatile uint32_t WIN;      /*!< 000CH */
    const uint32_t    Reserved; /*!< 0010H */
    volatile uint32_t TEST;     /*!< 0014H */
} WdgRegType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Gets the WDG CS value.
 *
 * the function gets the WDG CS value.
 *
 * \param[in] obj : pointer to WDG register instance
 * \return : pointer to CS current value
 *
 */
__attribute__((always_inline)) static inline uint32_t WdgReg_GetCsVal(const WdgRegType *obj)
{
    return obj->CS;
}

/*! \brief Sets the WDG CS unlock key
 *
 * The WDG CS registers is locked by default.
 * Before writing registers, write unlock key to this register or refresh this register.
 *
 * \param[in] obj : pointer to WDG register instance
 * \param[in] value : pointer to the value
 */
__attribute__((always_inline)) static inline void WdgReg_SetCsVal(WdgRegType *obj, uint32_t value)
{
    obj->CS = value;
}

/*! \brief Gets the WDG input clock source
 *
 * This function gets the WDG input clock source
 *
 * \param[in] obj : pointer to WDG register instance
 * \return indicate the clock source that feeds the watchdog counter
 *                    - 000b : BUS clock as source;
 *                    - 001b : LPO_CLK_128 clock as source;
 *                    - 010b : SOSC clock as source;
 *                    - 011b : SIRC clock as source;
 *                    - 100b : LPO_CLK_32 clock as source;
 *                    - 101b : LPO_CLK_1 clock as source;
 */
__attribute__((always_inline)) static inline uint8_t WdgReg_GetClockSource(const WdgRegType *obj)
{
    return ((obj->CS & WDG_CS_CLK_MASK) >> WDG_CS_CLK_SHIFT);
}

/*! \brief Sets the WDG input clock source
 *
 * This function sets the WDG input clock source
 *
 * \param[in] obj : pointer to WDG register instance
 * \param[in] value : the value of WDG input clock source
 *                    - 000b : BUS clock as source;
 *                    - 001b : LPO_CLK_128 clock as source;
 *                    - 010b : SOSC clock as source;
 *                    - 011b : SIRC clock as source;
 *                    - 100b : LPO_CLK_32 clock as source;
 *                    - 101b : LPO_CLK_1 clock as source;
 */
__attribute__((always_inline)) static inline void WdgReg_SetClockSource(WdgRegType *obj, uint8_t value)
{
    uint32_t csTmp = obj->CS;

    csTmp &= ~(WDG_CS_CLK_MASK);
    csTmp |= (((uint32_t)(((uint32_t)(value)) << WDG_CS_CLK_SHIFT)) & WDG_CS_CLK_MASK);
    obj->CS = csTmp;
}

/*! \brief Verifies if the WDG windouw mode is enabled.
 *
 * This function verifies if the WDG windouw mode is enabled.
 *
 * \param[in] obj : pointer to WDG register instance
 * \return  Verifies if the WDG windouw mode is enabled
 *                    - 000b : window mode is disabled;
 *                    - 001b : window mode is enabled;
 */
__attribute__((always_inline)) static inline uint8_t WdgReg_IsEnabledWinMode(const WdgRegType *obj)
{
    return ((obj->CS & WDG_CS_WIN_MASK) >> WDG_CS_WIN_SHIFT);
}

/*! \brief Enable/disable the WDG windouw mode.
 *
 * This function enable/disable the WDG windouw mode.
 *
 * \param[in] obj : pointer to WDG register instance
 * \param[in] value : Enable/disable
 *                    - 000b : disable;
 *                    - 001b : enable;
 */
__attribute__((always_inline)) static inline void WdgReg_EnableWinMode(WdgRegType *obj, uint8_t value)
{
    uint32_t csTmp = obj->CS;

    csTmp &= ~(WDG_CS_WIN_MASK);
    csTmp |= (((uint32_t)(((uint32_t)(value)) << WDG_CS_WIN_SHIFT)) & WDG_CS_WIN_MASK);
    obj->CS = csTmp;
}

/*! \brief Gets the WDG interrupt flag.
 *
 * This function gets the WDG interript flag.
 *
 * \param[in] obj : pointer to WDG register instance
 * \return  the WDG interrupt flag
 *                    - 000b : disable;
 *                    - 001b : enable;
 */
__attribute__((always_inline)) static inline uint8_t WdgReg_GetInterruptFlag(WdgRegType *obj)
{
    return ((obj->CS & WDG_CS_FLG_MASK) >> WDG_CS_FLG_SHIFT);
}

/*! \brief Sets the WDG interrupt flag.
 *
 * This bit is an interrupt indicator when INT is set in control and status register 1. Write 1 to clear it.
 *
 * \param[in] obj : pointer to WDG register instance
 * \param[in] value : pointer to clear value
 *                    - 000b: No occurred.
 *                    - 001b: clear interrupt flag
 */
__attribute__((always_inline)) static inline void WdgReg_ClearInterruptFlag(WdgRegType *obj, uint16_t value)
{
    uint32_t csTmp = obj->CS;

    csTmp &= ~(WDG_CS_FLG_MASK);
    csTmp |= (((uint32_t)(((uint32_t)(value)) << WDG_CS_FLG_SHIFT)) & WDG_CS_FLG_MASK);
    obj->CS = csTmp;
    /* Read back to avoid problem */
    (void)obj->CS;
}

/*! \brief Verifies if the WDG prescaler is enabled.
 *
 * This bit is an interrupt indicator when INT is set in control and status register 1. Write 1 to clear it.
 *
 * \param[in] obj : pointer to WDG register instance
 * \return : pointer to prescaler status
 *                    - 000b: No occurred.
 *                    - 001b: clear interrupt flag
 */
__attribute__((always_inline)) static inline uint8_t WdgReg_IsEnabledPrescaler(const WdgRegType *obj)
{
    return ((obj->CS & WDG_CS_PRES_MASK) >> WDG_CS_PRES_SHIFT);
}

/*! \brief Enable/disable the WDG prescaler.
 *
 * This function enable/disable the WDG prescaler.
 *
 * \param[in] obj : pointer to WDG register instance
 * \param[in] value : Enable/disable
 *                    - 000b : disable;
 *                    - 001b : enable;
 */
__attribute__((always_inline)) static inline void WdgReg_EnablePrescaler(WdgRegType *obj, uint8_t value)
{
    uint32_t csTmp = obj->CS;

    csTmp &= ~(WDG_CS_PRES_MASK);
    csTmp |= (((uint32_t)(((uint32_t)(value)) << WDG_CS_PRES_SHIFT)) & WDG_CS_PRES_MASK);
    obj->CS = csTmp;
}

/*! \brief Verifies if the WDG prescaler is unlocked.
 *
 * this read-only bit indicates whether WDOG is unlocked or not.
 *
 * \param[in] obj : pointer to WDG register instance
 * \return : pointer to unlock status
 *                    - 000b: WDG is locked.
 *                    - 001b: WDG is unlocked.
 */
__attribute__((always_inline)) static inline uint8_t WdgReg_IsUnlocked(WdgRegType *obj)
{
    return ((uint8_t)((obj->CS & WDG_CS_ULK_MASK) >> WDG_CS_ULK_SHIFT));
}

/*! \brief Verifies if the WDG configuration is successful.
 *
 * this read-only bit indicates whether the configuration is successful or not.
 *
 * \param[in] obj : pointer to WDG register instance
 * \return : pointer to configuration status
 *                    - 000b: configuring WDG.
 *                    - 001b: configuration is successful.
 */
__attribute__((always_inline)) static inline uint8_t WdgReg_IsSuccessConfig(WdgRegType *obj)
{
    return ((uint8_t)((obj->CS & WDG_CS_RCS_MASK) >> WDG_CS_RCS_SHIFT));
}

/*! \brief Verifies if the synchronization of the WDG new configuration is done
 *
 * this flag indicate the synchronization of new configuration is done, next unlock seq is allowed if required
 *
 * \param[in] obj : pointer to WDG register instance
 * \return : pointer to configuration status
 *                    - 000b: synchronization is ongoing, next unlock seq is not allowed.
 *                    - 001b: synchronization is done, next unlock seq is allowed if required.
 */
__attribute__((always_inline)) static inline uint8_t WdgReg_IsDoneConfigSync(WdgRegType *obj)
{
    return ((uint8_t)((obj->CS & WDG_CS_CSD_MASK) >> WDG_CS_CSD_SHIFT));
}

/*! \brief Verifies if the WDG is enabled.
 *
 * Verifies if the WDG is enabled.
 *
 * \param[in] obj : pointer to WDG register instance
 * \return : pointer to enable status
 *                    - 000b: watchdog disabled.
 *                    - 001b: watchdog enabled.
 */
__attribute__((always_inline)) static inline uint8_t WdgReg_IsEnabled(const WdgRegType *obj)
{
    return ((obj->CS & WDG_CS_EN_MASK) >> WDG_CS_EN_SHIFT);
}

/*! \brief Enable/Disable the WDG .
 *
 * the function enable/disable the WDG .
 *
 * \param[in] obj : pointer to WDG register instance
 * \param[in] value : pointer to WDG enable value
 *                    - 000b: watchdog disable.
 *                    - 001b: watchdog enable.
 */
__attribute__((always_inline)) static inline void WdgReg_Enable(WdgRegType *obj, uint8_t value)
{
    uint32_t csTmp = obj->CS;

    csTmp &= ~(WDG_CS_EN_MASK);
    csTmp |= (((uint32_t)(((uint32_t)(value)) << WDG_CS_EN_SHIFT)) & WDG_CS_EN_MASK);
    obj->CS = csTmp;
}

/*! \brief Verifies if the WDG interrupt is enabled..
 *
 * the function verifies if the WDG interrupt is enabled .
 *
 * \param[in] obj : pointer to WDG register instance
 * \return : pointer to enable status
 *                    - 000b: disabled.
 *                    - 001b: enabled.
 */
__attribute__((always_inline)) static inline uint8_t WdgReg_IsEnabledInterrupt(const WdgRegType *obj)
{
    return ((obj->CS & WDG_CS_INTR_MASK) >> WDG_CS_INTR_SHIFT);
}

/*! \brief Enable/Disable the WDG interrupt.
 *
 * the function enable/disable the WDG interrupt.
 *
 * \param[in] obj : pointer to WDG register instance
 * \param[in] value : pointer to WDG enable value
 *                    - 000b: disable.
 *                    - 001b: enable.
 */
__attribute__((always_inline)) static inline void WdgReg_EnableInterrupt(WdgRegType *obj, uint8_t value)
{
    uint32_t csTmp = obj->CS;

    csTmp &= ~(WDG_CS_INTR_MASK);
    csTmp |= (((uint32_t)(((uint32_t)(value)) << WDG_CS_INTR_SHIFT)) & WDG_CS_INTR_MASK);
    obj->CS = csTmp;
}

/*! \brief Verifies if allow update register.
 *
 * the function verifies if allow update register.
 *
 * \param[in] obj : pointer to WDG register instance
 * \return : pointer to allow status
 *                    - 000b: updates not allowed.
 *                    - 001b: update allowed.
 */
__attribute__((always_inline)) static inline uint8_t WdgReg_IsEnabledUpdate(const WdgRegType *obj)
{
    return ((obj->CS & WDG_CS_UPDATE_MASK) >> WDG_CS_UPDATE_SHIFT);
}

/*! \brief Enable/Disable the WDG update register.
 *
 * the function enable/disable the WDG update register.
 *
 * \param[in] obj : pointer to WDG register instance
 * \param[in] value : pointer to WDG enable value
 *                    - 000b: disable.
 *                    - 001b: enable.
 */
__attribute__((always_inline)) static inline void WdgReg_EnableUpdate(WdgRegType *obj, uint8_t value)
{
    uint32_t csTmp = obj->CS;

    csTmp &= ~(WDG_CS_UPDATE_MASK);
    csTmp |= (((uint32_t)(((uint32_t)(value)) << WDG_CS_UPDATE_SHIFT)) & WDG_CS_UPDATE_MASK);
    obj->CS = csTmp;
}

/*! \brief Verifies if enable debug mode.
 *
 * the function verifies if enable the WDG in debug mode.
 *
 * \param[in] obj : pointer to WDG register instance
 * \return : pointer to allow status
 *                    - 000b: watchdog disable in chip debug mode.
 *                    - 001b: watchdog enabled in chip debug mode
 */
__attribute__((always_inline)) static inline uint8_t WdgReg_IsEnabledDebugMode(const WdgRegType *obj)
{
    return ((obj->CS & WDG_CS_DEBUG_MASK) >> WDG_CS_DEBUG_SHIFT);
}

/*! \brief Enable/Disable the WDG in debug mode.
 *
 * the function enable/disable the WDG in debug mode.
 * the reg is write-once bit.
 *
 * \param[in] obj : pointer to WDG register instance
 * \param[in] value : pointer to WDG enable value
 *                    - 000b: watchdog disable in chip debug mode.
 *                    - 001b: watchdog enabled in chip debug mode.
 */
__attribute__((always_inline)) static inline void WdgReg_EnableDebugMode(WdgRegType *obj, uint8_t value)
{
    uint32_t csTmp = obj->CS;

    csTmp &= ~(WDG_CS_DEBUG_MASK);
    csTmp |= (((uint32_t)(((uint32_t)(value)) << WDG_CS_DEBUG_SHIFT)) & WDG_CS_DEBUG_MASK);
    obj->CS = csTmp;
}

/*! \brief Verifies if the WDG has reset triggering event occurred in test mode
 *
 * the function verifies if has reset triggering event occurred during test mode
 *
 * \param[in] obj : pointer to WDG register instance
 * \return : pointer to status
 *                    - 000b: No reset triggering event occurred during test mode.
 *                    - 001b: An reset triggering event occurred during test mode.
 */
__attribute__((always_inline)) static inline uint8_t WdgReg_GetTesRstFlag(const WdgRegType *obj)
{
    return ((obj->TEST & WDG_TST_RST_FLG_MASK) >> WDG_TST_RST_FLG_SHIFT);
}

/*! \brief Clear the WDG reset triggering event occurred flag in test mode
 *
 * This function is to write 1 clear 0.
 *
 * \param[in] obj : pointer to WDG register instance
 */
__attribute__((always_inline)) static inline void WdgReg_ClrTesRstFlag(WdgRegType *obj)
{
    uint32_t tstTmp = obj->TEST;

    tstTmp &= ~(WDG_TST_RST_FLG_MASK);
    tstTmp |= (((uint32_t)(((uint32_t)(0x1u)) << WDG_TST_RST_FLG_SHIFT)) & WDG_TST_RST_FLG_MASK);
    obj->TEST = tstTmp;
}

/*! \brief Verifies if enable reset function in test mode
 *
 * the function verifies if enable reset function in test mode
 *
 * \param[in] obj : pointer to WDG register instance
 * \return : pointer to status
 *                    - 000b: disable.
 *                    - 001b: enable.
 */
__attribute__((always_inline)) static inline uint8_t WdgReg_IsEnabledTstRst(const WdgRegType *obj)
{
    return ((obj->TEST & WDG_TST_RST_EN_MASK) >> WDG_TST_RST_EN_SHIFT);
}

/*! \brief Enable/disable reset upon a reset triggering event
 *
 * when wdg in test mode, enable/disable reset upon a reset triggering event (timeout or illegal write to the watchdog).
 *
 * \param[in] obj : pointer to WDG register instance
 * \param[in] value : pointer to WDG enable value
 *                    - 000b: reset won't happen upon a reset triggering event,only TST_RST_FLG set.
 *                    - 001b: reset happens upon a reset triggering event, and TST_RST_FLG  set.
 */
__attribute__((always_inline)) static inline void WdgReg_EnableTstRst(WdgRegType *obj, uint8_t value)
{
    uint32_t tstTmp = obj->TEST;

    tstTmp &= ~(WDG_TST_RST_EN_MASK);
    tstTmp |= (((uint32_t)(((uint32_t)(value)) << WDG_TST_RST_EN_SHIFT)) & WDG_TST_RST_EN_MASK);
    obj->TEST = tstTmp;
}

/*! \brief Verifies if test mode is enabled.
 *
 * the function TST is cleared (0:0) on POR only.
 * Any other reset does not affect the value of this field.
 *
 * \param[in] obj : pointer to WDG register instance
 * \return : pointer to status
 *                    - 000b: watchdog test mode disable
 *                    - 001b: watchdog user mode enable. (watchdog test mode disabled)
 *                    - 010b: watchdog test mode enabled, only the low byte is used.
 *                    - 011b: watchdog test mode enabled, only the high byte is used.
 */
__attribute__((always_inline)) static inline uint8_t WdgReg_GetTestModeStatus(const WdgRegType *obj)
{
    return ((obj->TEST & WDG_TST_MASK) >> WDG_TST_SHIFT);
}

/*! \brief Enable/Disable the WDG test mode.
 *
 * the function enable/disable the WDG test mode.
 *
 * \param[in] obj : pointer to WDG register instance
 * \param[in] value : pointer to WDG enable value
 *                    - 000b: watchdog test mode disable
 *                    - 001b: watchdog user mode enable. (watchdog test mode disabled)
 *                    - 010b: watchdog test mode enabled, only the low byte is used.
 *                    - 011b: watchdog test mode enabled, only the high byte is used.
 */
__attribute__((always_inline)) static inline void WdgReg_SetTestMode(WdgRegType *obj, uint8_t value)
{
    uint32_t tstTmp = obj->TEST;

    tstTmp &= ~(WDG_TST_MASK);
    tstTmp |= (((uint32_t)(((uint32_t)(value)) << WDG_TST_SHIFT)) & WDG_TST_MASK);
    obj->TEST = tstTmp;
}

/*! \brief Gets the WDG Test configuration value.
 *
 * the function sets the WDG test configuration value.
 *
 * \param[in] obj : pointer to WDG register instance
 * \param[in] value: pointer to test value
 *
 */
__attribute__((always_inline)) static inline void WdgReg_SetTestVal(WdgRegType *obj, uint8_t value)
{
    obj->TEST = value;
}

/*! \brief Verifies if the WDG stop mode.
 *
 * the function verifies if the watchdog is eabled to operate in stop mode.
 *
 * \param[in] obj : pointer to WDG register instance
 * \return : pointer to status
 *                    - 000b: disabled.
 *                    - 001b: enabled.
 */
__attribute__((always_inline)) static inline uint8_t WdgReg_IsEnabledStopMode(WdgRegType *obj)
{
    return ((obj->CS & WDG_CS_STOP_MASK) >> WDG_CS_STOP_SHIFT);
}

/*! \brief Enable/Disable the WDG stop mode.
 *
 * the function enable/disable the WDG stop mode.
 *
 * \param[in] obj : pointer to WDG register instance
 * \param[in] value : pointer to WDG enable value
 *                    - 000b: disable.
 *                    - 001b: enable.
 */
__attribute__((always_inline)) static inline void WdgReg_EnableStopMode(WdgRegType *obj, uint8_t value)
{
    uint32_t csTmp = obj->CS;

    csTmp &= ~(WDG_CS_STOP_MASK);
    csTmp |= (((uint32_t)(((uint32_t)(value)) << WDG_CS_STOP_SHIFT)) & WDG_CS_STOP_MASK);
    obj->CS = csTmp;
}

/*! \brief Gets the WDG CNT value.
 *
 * the function gets the WDG CNT value.
 *
 * \param[in] obj : pointer to WDG register instance
 * \return : pointer to CNT current value
 *
 */
__attribute__((always_inline)) static inline uint32_t WdgReg_GetCntVal(const WdgRegType *obj)
{
    return obj->CNT;
}

/*! \brief Sets the WDG CNT unlock key
 *
 * The WDG CNT registers is locked by default.
 * Before writing registers, write unlock key to this register or refresh this register.
 *
 * \param[in] obj : pointer to WDG register instance
 * \param[in] value : CNT value
 */
__attribute__((always_inline)) static inline void WdgReg_SetCntVal(WdgRegType *obj, uint32_t value)
{
    obj->CNT = value;
}

/*! \brief Gets the WDG CNT high 8 bits value .
 *
 * the function gets he WDG CNT high 8 bits value.
 *
 * \param[in] obj : pointer to WDG register instance
 * \return : pointer to CNT current high 8 bits value
 *
 */
__attribute__((always_inline)) static inline uint32_t WdgReg_GetCntValHighBits(WdgRegType *obj)
{
    return ((obj->CNT & WDG_CNT_HIGH_MASK) >> WDG_CNT_HIGH_SHIFT);
}

/*! \brief Gets the WDG CNT low 8 bits value .
 *
 * the function gets he WDG CNT low 8 bits value.
 *
 * \param[in] obj : pointer to WDG register instance
 * \return : pointer to CNT current low 8 bits value
 *
 */
__attribute__((always_inline)) static inline uint32_t WdgReg_GetCntValLowBits(WdgRegType *obj)
{
    return ((obj->CNT & WDG_CNT_LOW_MASK) >> WDG_CNT_LOW_SHIFT);
}

/*! \brief Gets the WDG Timeout configuration value.
 *
 * the function gets the WDG Timeout configuration value.
 *
 * \param[in] obj : pointer to WDG register instance
 * \return : pointer to TOVAL current value
 *
 */
__attribute__((always_inline)) static inline uint32_t WdgReg_GetToval(const WdgRegType *obj)
{
    return obj->TOVAL;
}

/*! \brief Sets the WDG Timeout Configuration value
 *
 * The WDG TOVAL registers is locked by default.
 * Before writing registers, write unlock key to CNT register.
 *
 * \param[in] obj : pointer to WDG register instance
 * \param[in] value : pointer to configuration value
 */
__attribute__((always_inline)) static inline void WdgReg_SetToval(WdgRegType *obj, uint32_t value)
{
    obj->TOVAL = value;
}

/*! \brief Gets the WDG Timeout high 8 bits value .
 *
 * the function gets he WDG Timeout high8 bits value.
 *
 * \param[in] obj : pointer to WDG register instance
 * \return : pointer to current Timeout high 8 bits value
 *
 */
__attribute__((always_inline)) static inline uint32_t WdgReg_GetTovalHighBits(WdgRegType *obj)
{
    return ((obj->TOVAL & WDG_TOVAL_HIGH_MASK) >> WDG_TOVAL_HIGH_SHIFT);
}

/*! \brief Gets the WDG Timeout low 8 bits value .
 *
 * the function gets he WDG Timeout low 8 bits value.
 *
 * \param[in] obj : pointer to WDG register instance
 * \return : pointer to Timeout current low 8 bits value
 *
 */
__attribute__((always_inline)) static inline uint32_t WdgReg_GetTovalLowBits(WdgRegType *obj)
{
    return ((obj->TOVAL & WDG_TOVAL_LOW_MASK) >> WDG_TOVAL_LOW_SHIFT);
}

/*! \brief Gets the WDG window configuration value.
 *
 * the function gets the WDG window configuration value.
 *
 * \param[in] obj : pointer to WDG register instance
 * \return : pointer to TOVAL current value
 *
 */
__attribute__((always_inline)) static inline uint32_t WdgReg_GetWinVal(const WdgRegType *obj)
{
    return obj->WIN;
}

/*! \brief Sets the WDG window Configuration value
 *
 * The WDG WIN registers is locked by default.
 * Before writing registers, write unlock key to CNT register.
 *
 * \param[in] obj : pointer to WDG register instance
 * \param[in] value : pointer to configuration value
 */
__attribute__((always_inline)) static inline void WdgReg_SetWinVal(WdgRegType *obj, uint32_t value)
{
    obj->WIN = value;
}

/*! \brief Gets the WDG window high 8 bits value .
 *
 * the function gets he WDG window high8 bits value.
 *
 * \param[in] obj : pointer to WDG register instance
 * \return : pointer to current window high 8 bits value
 *
 */
__attribute__((always_inline)) static inline uint32_t WdgReg_GetWinValHighBits(WdgRegType *obj)
{
    return ((obj->WIN & WDG_WIN_HIGH_MASK) >> WDG_WIN_HIGH_SHIFT);
}

/*! \brief Gets the WDG window low 8 bits value .
 *
 * the function gets he WDG window low 8 bits value.
 *
 * \param[in] obj : pointer to WDG register instance
 * \return : pointer to window current low 8 bits value
 *
 */
__attribute__((always_inline)) static inline uint32_t WdgReg_GetWinValLowBits(WdgRegType *obj)
{
    return ((obj->WIN & WDG_WIN_LOW_MASK) >> WDG_WIN_LOW_SHIFT);
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _WDG_REG_H_ */
