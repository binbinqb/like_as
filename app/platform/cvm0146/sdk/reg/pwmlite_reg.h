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

#ifndef _PWMLITE_REG_H_
#define _PWMLITE_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the PWMLITE Registers
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

/*! The number of PWMLITE channels */
#define PWMLITE_CHANNEL_NUM          (8)

/* CTRL Bit Fields */
#define PWMLITE_CTRL_SYNC_MODE_MASK  (0x02u)
#define PWMLITE_CTRL_SYNC_MODE_SHIFT (1u)
#define PWMLITE_CTRL_SYNC_MODE_WIDTH (1u)
#define PWMLITE_CTRL_EN_MASK         (0x01u)
#define PWMLITE_CTRL_EN_SHIFT        (0u)
#define PWMLITE_CTRL_EN_WIDTH        (1u)

/* PRD Bit Fields */
#define PWMLITE_PRD_PERIOD_MASK      (0xFFFFFFFFu)
#define PWMLITE_PRD_PERIOD_SHIFT     (0u)
#define PWMLITE_PRD_PERIOD_WIDTH     (32u)

/* STOP Bit Fields */
#define PWMLITE_STOP_PAUSE_MASK      (0x01u)
#define PWMLITE_STOP_PAUSE_SHIFT     (0u)
#define PWMLITE_STOP_PAUSE_WIDTH     (1u)

/* SYNC Bit Fields */
#define PWMLITE_SYNC_START_MASK      (0x02u)
#define PWMLITE_SYNC_START_SHIFT     (1u)
#define PWMLITE_SYNC_START_WIDTH     (1u)
#define PWMLITE_SYNC_STATUS_MASK     (0x01u)
#define PWMLITE_SYNC_STATUS_SHIFT    (0u)
#define PWMLITE_SYNC_STATUS_WIDTH    (1u)

/* CH_CTRL Bit Fields */
#define PWMLITE_CH_CTRL_CTRL1_MASK   (0x0Cu)
#define PWMLITE_CH_CTRL_CTRL1_SHIFT  (2u)
#define PWMLITE_CH_CTRL_CTRL1_WIDTH  (2u)
#define PWMLITE_CH_CTRL_CTRL0_MASK   (0x03u)
#define PWMLITE_CH_CTRL_CTRL0_SHIFT  (0u)
#define PWMLITE_CH_CTRL_CTRL0_WIDTH  (2u)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief The definition of PWMLITE registers
 */
typedef struct _PwmLiteRegType_
{
    volatile uint32_t CTRL;             /*!< PWMLITE control, offset: 0x00 */
    volatile uint32_t PRD;              /*!< PWMLITE counter period, offset: 0x04 */
    volatile uint32_t STOP;             /*!< pause module register, offset: 0x08 */
    volatile uint32_t SYNC;             /*!< register sync control and status, offset: 0x0C */
    struct                              
    {                                   
        volatile uint32_t CTRL;         /*!< channel n control, offset: 0x00 */
        volatile uint32_t THR0;         /*!< channel n threshold0, offset: 0x04 */
        volatile uint32_t THR1;         /*!< channel n threshold1, offset: 0x08 */
        uint32_t          RESERVED0[1]; /*!< Reserverd block, offset: 0x0C */
    } CH[PWMLITE_CHANNEL_NUM];
} PwmLiteRegType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Gets the register update mode
 *
 * This function gets the current register update mode.
 *
 * \param[in] obj : pointer to PWMLITE register instance
 * \return register update mode
 *         - 0b : async update, update when the register is configured
 *         - 1b : sync update
 */
__attribute__((always_inline)) static inline uint8_t PwmLiteReg_GetCtrlSyncMode(const PwmLiteRegType *obj)
{
    return ((obj->CTRL & PWMLITE_CTRL_SYNC_MODE_MASK) >> PWMLITE_CTRL_SYNC_MODE_SHIFT);
}

/*! \brief Sets the register update mode
 *
 * This function sets the register update mode.
 *
 * \param[in] obj : pointer to PWMLITE register instance
 * \param[in] value : the value of register update mode
 *                    - 0b : async update,update when the register is configured
 *                    - 1b : sync update
 */
__attribute__((always_inline)) static inline void PwmLiteReg_SetCtrlSyncMode(PwmLiteRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CTRL;

    tmp &= ~PWMLITE_CTRL_SYNC_MODE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PWMLITE_CTRL_SYNC_MODE_SHIFT)) & PWMLITE_CTRL_SYNC_MODE_MASK);
    obj->CTRL = tmp;
}

/*! \brief Gets the pwm module enable
 *
 * This function gets the current pwm module enable.
 *
 * \param[in] obj : pointer to PWMLITE register instance
 * \return pwm module enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PwmLiteReg_GetCtrlEn(const PwmLiteRegType *obj)
{
    return ((obj->CTRL & PWMLITE_CTRL_EN_MASK) >> PWMLITE_CTRL_EN_SHIFT);
}

/*! \brief Sets the pwm module enable
 *
 * This function sets the pwm module enable.
 *
 * \param[in] obj : pointer to PWMLITE register instance
 * \param[in] value : the value of pwm module enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PwmLiteReg_SetCtrlEn(PwmLiteRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CTRL;

    tmp &= ~PWMLITE_CTRL_EN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PWMLITE_CTRL_EN_SHIFT)) & PWMLITE_CTRL_EN_MASK);
    obj->CTRL = tmp;
}

/*! \brief Gets the pwm counter period
 *
 * This function gets the current pwm counter period.
 *
 * \note This value should be > 0, if configured 0, the real period is 0x100000000.
 *
 * \param[in] obj : pointer to PWMLITE register instance
 * \return pwm counter period
 *         - 0h : 0xFFFFFFFF
 *         - 1 : 1
 *         - 2 : 2
 *          ...
 *         - 0xFFFFFFFF : 0xFFFFFFFF
 */
__attribute__((always_inline)) static inline uint32_t PwmLiteReg_GetPrdPeriod(const PwmLiteRegType *obj)
{
    return ((obj->PRD & PWMLITE_PRD_PERIOD_MASK) >> PWMLITE_PRD_PERIOD_SHIFT);
}

/*! \brief Sets the pwm counter period
 *
 * This function sets the pwm counter period.
 *
 * \note This value should be > 0, if configured 0, the real period is 0x100000000.
 *
 * \param[in] obj : pointer to PWMLITE register instance
 * \param[in] value : the value of pwm counter period
 *                    - 0h : 0xFFFF_FFFF
 *                    - 1h : 1
 *                    - 2h : 2
 *                      ...
 *                    - 0xFFFFFFFF : 0xFFFFFFFF
 */
__attribute__((always_inline)) static inline void PwmLiteReg_SetPrdPeriod(PwmLiteRegType *obj, uint32_t value)
{
    uint32_t tmp = obj->PRD;

    tmp &= ~PWMLITE_PRD_PERIOD_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PWMLITE_PRD_PERIOD_SHIFT)) & PWMLITE_PRD_PERIOD_MASK);
    obj->PRD = tmp;
}

/*! \brief Gets the pwm module pause
 *
 * This function gets the current pwm module pause.
 *
 * \param[in] obj : pointer to PWMLITE register instance
 * \return pwm module pause
 *         - 0b : counter is working
 *         - 1b : stop counter
 */
__attribute__((always_inline)) static inline uint8_t PwmLiteReg_GetStopPause(const PwmLiteRegType *obj)
{
    return ((obj->STOP & PWMLITE_STOP_PAUSE_MASK) >> PWMLITE_STOP_PAUSE_SHIFT);
}

/*! \brief Sets the pwm module pause
 *
 * This function sets the pwm module pause.
 *
 * \param[in] obj : pointer to PWMLITE register instance
 * \param[in] value : the value of pwm module pause
 *                    - 0b : counter is working
 *                    - 1b : stop counter
 */
__attribute__((always_inline)) static inline void PwmLiteReg_SetStopPause(PwmLiteRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->STOP;

    tmp &= ~PWMLITE_STOP_PAUSE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PWMLITE_STOP_PAUSE_SHIFT)) & PWMLITE_STOP_PAUSE_MASK);
    obj->STOP = tmp;
}

/*! \brief Sets the update register action
 *
 * This function sets the update register action.
 * write to this register shall cause all registers take effect when counter reaches the PWM_PRD register
 *
 * \param[in] obj : pointer to PWMLITE register instance
 * \param[in] value : the value of update register action
 */
__attribute__((always_inline)) static inline void PwmLiteReg_SetSyncStart(PwmLiteRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SYNC;

    tmp &= ~PWMLITE_SYNC_START_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PWMLITE_SYNC_START_SHIFT)) & PWMLITE_SYNC_START_MASK);
    obj->SYNC = tmp;
}

/*! \brief Gets the configuration update status
 *
 * This function gets the current configuration update status.
 *
 * \param[in] obj : pointer to PWMLITE register instance
 * \return configuration update status
 *         - 0b : update done
 *         - 1b : during update
 */
__attribute__((always_inline)) static inline uint8_t PwmLiteReg_GetSyncStatus(const PwmLiteRegType *obj)
{
    return ((obj->SYNC & PWMLITE_SYNC_STATUS_MASK) >> PWMLITE_SYNC_STATUS_SHIFT);
}

/*! \brief Gets the action when counter reaches threshold1
 *
 * This function gets the current action when counter reaches threshold1.
 * When channel counter reaches the threshold PWMn_THR1, pwm output should be one of the following
 * - 0h : keep
 * - 1h : low
 * - 2h : high
 * - 3h : toggle
 *
 * \param[in] obj : pointer to PWMLITE register instance
 * \param[in] channel : the channel number, 0-7
 * \return action when counter reaches threshold1
 *         - 0h : keep
 *         - 1h : low
 *         - 2h : high
 *         - 3h : toggle
 */
__attribute__((always_inline)) static inline uint8_t PwmLiteReg_GetChCtrl1(const PwmLiteRegType *obj, uint8_t channel)
{
    return ((obj->CH[channel].CTRL & PWMLITE_CH_CTRL_CTRL1_MASK) >> PWMLITE_CH_CTRL_CTRL1_SHIFT);
}

/*! \brief Sets the action when counter reaches threshold1
 *
 * This function sets the action when counter reaches threshold1.
 * When channel counter reaches the threshold PWMn_THR1, pwm output should be one of the following
 * - 0h : keep
 * - 1h : low
 * - 2h : high
 * - 3h : toggle
 *
 * \param[in] obj : pointer to PWMLITE register instance
 * \param[in] channel : the channel number, 0-7
 * \param[in] value : the value of action when counter reaches threshold1
 *                    - 0h : keep
 *                    - 1h : low
 *                    - 2h : high
 *                    - 3h : toggle
 */
__attribute__((always_inline)) static inline void PwmLiteReg_SetChCtrl1(PwmLiteRegType *obj, uint8_t channel, uint8_t value)
{
    uint32_t tmp = obj->CH[channel].CTRL;

    tmp &= ~PWMLITE_CH_CTRL_CTRL1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PWMLITE_CH_CTRL_CTRL1_SHIFT)) & PWMLITE_CH_CTRL_CTRL1_MASK);
    obj->CH[channel].CTRL = tmp;
}

/*! \brief Gets the action when counter reaches threshold0
 *
 * This function gets the current action when counter reaches threshold0.
 * When channel counter reaches the threshold PWM0_THR0, pwm output should be one of the following
 * - 0h : keep
 * - 1h : low
 * - 2h : high
 * - 3h : toggle
 *
 * \param[in] obj : pointer to PWMLITE register instance
 * \param[in] channel : the channel number, 0-7
 * \return action when counter reaches threshold0
 *         - 0h : keep
 *         - 1h : low
 *         - 2h : high
 *         - 3h : toggle
 */
__attribute__((always_inline)) static inline uint8_t PwmLiteReg_GetChCtrl0(const PwmLiteRegType *obj, uint8_t channel)
{
    return ((obj->CH[channel].CTRL & PWMLITE_CH_CTRL_CTRL0_MASK) >> PWMLITE_CH_CTRL_CTRL0_SHIFT);
}

/*! \brief Sets the action when counter reaches threshold0
 *
 * This function sets the action when counter reaches threshold0.
 * When channel counter reaches the threshold PWM0_THR0, pwm output should be one of the following
 * - 0h : keep
 * - 1h : low
 * - 2h : high
 * - 3h : toggle
 *
 * \param[in] obj : pointer to PWMLITE register instance
 * \param[in] channel : the channel number, 0-7
 * \param[in] value : the value of action when counter reaches threshold0
 *                    - 0h : keep
 *                    - 1h : low
 *                    - 2h : high
 *                    - 3h : toggle
 */
__attribute__((always_inline)) static inline void PwmLiteReg_SetChCtrl0(PwmLiteRegType *obj, uint8_t channel, uint8_t value)
{
    uint32_t tmp = obj->CH[channel].CTRL;

    tmp &= ~PWMLITE_CH_CTRL_CTRL0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PWMLITE_CH_CTRL_CTRL0_SHIFT)) & PWMLITE_CH_CTRL_CTRL0_MASK);
    obj->CH[channel].CTRL = tmp;
}

/*! \brief Gets the channel threshold0
 *
 * This function gets the current channel threshold0.
 * This value should be > 0, if configured 0, the real threshold is PWM_PR
 *
 * \param[in] obj : pointer to PWMLITE register instance
 * \param[in] channel : the channel number, 0-7
 * \return channel threshold0
 */
__attribute__((always_inline)) static inline uint32_t PwmLiteReg_GetChThr0(const PwmLiteRegType *obj, uint8_t channel)
{
    return obj->CH[channel].THR0;
}

/*! \brief Sets the channel threshold0
 *
 * This function sets the channel threshold0.
 * This value should be > 0, if configured 0, the real threshold is PWM_PR
 *
 * \param[in] obj : pointer to PWMLITE register instance
 * \param[in] channel : the channel number, 0-7
 * \param[in] value : the value of channel threshold0
 */
__attribute__((always_inline)) static inline void PwmLiteReg_SetChThr0(PwmLiteRegType *obj, uint8_t channel, uint32_t value)
{
    obj->CH[channel].THR0 = value;
}

/*! \brief Gets the channel threshold1
 *
 * This function gets the current channel threshold1.
 * This value should be > 0, if configured 0, the real threshold is PWM_PR
 *
 * \param[in] obj : pointer to PWMLITE register instance
 * \param[in] channel : the channel number, 0-7
 * \return channel threshold1
 */
__attribute__((always_inline)) static inline uint32_t PwmLiteReg_GetChThr1(const PwmLiteRegType *obj, uint8_t channel)
{
    return obj->CH[channel].THR1;
}

/*! \brief Sets the channel threshold1
 *
 * This function sets the channel threshold1.
 * This value should be > 0, if configured 0, the real threshold is PWM_PR
 *
 * \param[in] obj : pointer to PWMLITE register instance
 * \param[in] channel : the channel number, 0-7
 * \param[in] value : the value of channel threshold1
 */
__attribute__((always_inline)) static inline void PwmLiteReg_SetChThr1(PwmLiteRegType *obj, uint8_t channel, uint32_t value)
{
    obj->CH[channel].THR1 = value;
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _PWMLITE_REG_H_ */
