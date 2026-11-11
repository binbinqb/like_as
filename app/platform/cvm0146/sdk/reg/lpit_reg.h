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

#ifndef _LPIT_REG_H_
#define _LPIT_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the LPIT (Low Power Interrupt Timer) Registers
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

/* Size of TMR Registers Arrays */
#define LPIT_TMR_COUNT                  (4)

/* VERID Bit Fields */
#define LPIT_VERID_VERID_MASK           (0xFFFFFFFFu)
#define LPIT_VERID_VERID_SHIFT          (0u)
#define LPIT_VERID_VERID_WIDTH          (32u)

/* PARAM Bit Fields */
#define LPIT_PARAM_CHANNEL_MASK         (0xFFu)
#define LPIT_PARAM_CHANNEL_SHIFT        (0u)
#define LPIT_PARAM_CHANNEL_WIDTH        (8u)
#define LPIT_PARAM_EXT_TRIG_MASK        (0xFF00u)
#define LPIT_PARAM_EXT_TRIG_SHIFT       (8u)
#define LPIT_PARAM_EXT_TRIG_WIDTH       (8u)

/* MCR Bit Fields */
#define LPIT_MCR_M_CEN_MASK             (0x1u)
#define LPIT_MCR_M_CEN_SHIFT            (0u)
#define LPIT_MCR_M_CEN_WIDTH            (1u)
#define LPIT_MCR_LP_EN_MASK             (0x4u)
#define LPIT_MCR_LP_EN_SHIFT            (2u)
#define LPIT_MCR_LP_EN_WIDTH            (1u)
#define LPIT_MCR_DBG_EN_MASK            (0x8u)
#define LPIT_MCR_DBG_EN_SHIFT           (3u)
#define LPIT_MCR_DBG_EN_WIDTH           (1u)

/* MSR Bit Fields */
#define LPIT_MSR_TIF0_MASK              (0x1u)
#define LPIT_MSR_TIF0_SHIFT             (0u)
#define LPIT_MSR_TIF0_WIDTH             (1u)
#define LPIT_MSR_TIF1_MASK              (0x2u)
#define LPIT_MSR_TIF1_SHIFT             (1u)
#define LPIT_MSR_TIF1_WIDTH             (1u)
#define LPIT_MSR_TIF2_MASK              (0x4u)
#define LPIT_MSR_TIF2_SHIFT             (2u)
#define LPIT_MSR_TIF2_WIDTH             (1u)
#define LPIT_MSR_TIF3_MASK              (0x8u)
#define LPIT_MSR_TIF3_SHIFT             (3u)
#define LPIT_MSR_TIF3_WIDTH             (1u)

/* MIER Bit Fields */
#define LPIT_MIER_TIE0_MASK             (0x1u)
#define LPIT_MIER_TIE0_SHIFT            (0u)
#define LPIT_MIER_TIE0_WIDTH            (1u)
#define LPIT_MIER_TIE1_MASK             (0x2u)
#define LPIT_MIER_TIE1_SHIFT            (1u)
#define LPIT_MIER_TIE1_WIDTH            (1u)
#define LPIT_MIER_TIE2_MASK             (0x4u)
#define LPIT_MIER_TIE2_SHIFT            (2u)
#define LPIT_MIER_TIE2_WIDTH            (1u)
#define LPIT_MIER_TIE3_MASK             (0x8u)
#define LPIT_MIER_TIE3_SHIFT            (3u)
#define LPIT_MIER_TIE3_WIDTH            (1u)

/* SETTEN Bit Fields */
#define LPIT_SETTEN_SET_T_EN_0_MASK     (0x1u)
#define LPIT_SETTEN_SET_T_EN_0_SHIFT    (0u)
#define LPIT_SETTEN_SET_T_EN_0_WIDTH    (1u)
#define LPIT_SETTEN_SET_T_EN_1_MASK     (0x2u)
#define LPIT_SETTEN_SET_T_EN_1_SHIFT    (1u)
#define LPIT_SETTEN_SET_T_EN_1_WIDTH    (1u)
#define LPIT_SETTEN_SET_T_EN_2_MASK     (0x4u)
#define LPIT_SETTEN_SET_T_EN_2_SHIFT    (2u)
#define LPIT_SETTEN_SET_T_EN_2_WIDTH    (1u)
#define LPIT_SETTEN_SET_T_EN_3_MASK     (0x8u)
#define LPIT_SETTEN_SET_T_EN_3_SHIFT    (3u)
#define LPIT_SETTEN_SET_T_EN_3_WIDTH    (1u)

/* CLRTEN Bit Fields */
#define LPIT_CLRTEN_CLR_T_EN_0_MASK     (0x1u)
#define LPIT_CLRTEN_CLR_T_EN_0_SHIFT    (0u)
#define LPIT_CLRTEN_CLR_T_EN_0_WIDTH    (1u)
#define LPIT_CLRTEN_CLR_T_EN_1_MASK     (0x2u)
#define LPIT_CLRTEN_CLR_T_EN_1_SHIFT    (1u)
#define LPIT_CLRTEN_CLR_T_EN_1_WIDTH    (1u)
#define LPIT_CLRTEN_CLR_T_EN_2_MASK     (0x4u)
#define LPIT_CLRTEN_CLR_T_EN_2_SHIFT    (2u)
#define LPIT_CLRTEN_CLR_T_EN_2_WIDTH    (1u)
#define LPIT_CLRTEN_CLR_T_EN_3_MASK     (0x8u)
#define LPIT_CLRTEN_CLR_T_EN_3_SHIFT    (3u)
#define LPIT_CLRTEN_CLR_T_EN_3_WIDTH    (1u)

/* TMR_TVAL Bit Fields */
#define LPIT_TMR_TVAL_TMR_VAL_MASK      (0xFFFFFFFFu)
#define LPIT_TMR_TVAL_TMR_VAL_SHIFT     (0u)
#define LPIT_TMR_TVAL_TMR_VAL_WIDTH     (32u)

/* TMR_CVAL Bit Fields */
#define LPIT_TMR_CVAL_TMR_CUR_VAL_MASK  (0xFFFFFFFFu)
#define LPIT_TMR_CVAL_TMR_CUR_VAL_SHIFT (0u)
#define LPIT_TMR_CVAL_TMR_CUR_VAL_WIDTH (32u)

/* TMR_TCTRL Bit Fields */
#define LPIT_TMR_TCTRL_T_EN_MASK        (0x1u)
#define LPIT_TMR_TCTRL_T_EN_SHIFT       (0u)
#define LPIT_TMR_TCTRL_T_EN_WIDTH       (1u)
#define LPIT_TMR_TCTRL_CHAIN_MASK       (0x2u)
#define LPIT_TMR_TCTRL_CHAIN_SHIFT      (1u)
#define LPIT_TMR_TCTRL_CHAIN_WIDTH      (1u)
#define LPIT_TMR_TCTRL_MODE_MASK        (0xCu)
#define LPIT_TMR_TCTRL_MODE_SHIFT       (2u)
#define LPIT_TMR_TCTRL_MODE_WIDTH       (2u)
#define LPIT_TMR_TCTRL_TSOT_MASK        (0x10000u)
#define LPIT_TMR_TCTRL_TSOT_SHIFT       (16u)
#define LPIT_TMR_TCTRL_TSOT_WIDTH       (1u)
#define LPIT_TMR_TCTRL_TSOI_MASK        (0x20000u)
#define LPIT_TMR_TCTRL_TSOI_SHIFT       (17u)
#define LPIT_TMR_TCTRL_TSOI_WIDTH       (1u)
#define LPIT_TMR_TCTRL_TROT_MASK        (0x40000u)
#define LPIT_TMR_TCTRL_TROT_SHIFT       (18u)
#define LPIT_TMR_TCTRL_TROT_WIDTH       (1u)
#define LPIT_TMR_TCTRL_TRG_SRC_MASK     (0x800000u)
#define LPIT_TMR_TCTRL_TRG_SRC_SHIFT    (23u)
#define LPIT_TMR_TCTRL_TRG_SRC_WIDTH    (1u)
#define LPIT_TMR_TCTRL_TRG_SEL_MASK     (0xF000000u)
#define LPIT_TMR_TCTRL_TRG_SEL_SHIFT    (24u)
#define LPIT_TMR_TCTRL_TRG_SEL_WIDTH    (4u)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief The definition of LPIT registers
 */
typedef struct _LpitRegType_
{
    const volatile uint32_t VERID;    /*!< Version ID Register, offset: 0x0 */
    const volatile uint32_t PARAM;    /*!< Parameter Register, offset: 0x4 */
    volatile uint32_t       MCR;      /*!< Module Control Register, offset: 0x8 */
    volatile uint32_t       MSR;      /*!< Module Status Register, offset: 0xC */
    volatile uint32_t       MIER;     /*!< Module Interrupt Enable Register, offset: 0x10 */
    volatile uint32_t       SETTEN;   /*!< Set Timer Enable Register, offset: 0x14 */
    volatile uint32_t       CLRTEN;   /*!< Clear Timer Enable Register, offset: 0x18 */
    uint32_t                RESERVED; /*!< Reserved register, offset: 0x1C */
    struct
    {                                     /* offset: 0x20, array step: 0x10 */
        volatile uint32_t       TVAL;     /*!< Timer Value Register, array offset: 0x20, array step: 0x10 */
        const volatile uint32_t CVAL;     /*!< Current Timer Value, array offset: 0x24, array step: 0x10 */
        volatile uint32_t       TCTRL;    /*!< Timer Control Register, array offset: 0x28, array step: 0x10 */
        uint32_t                RESERVED; /*!< Reserved register, offset: 0x2C */
    } TMR[LPIT_TMR_COUNT];
} LpitRegType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Get the version ID of LPIT module.
 *
 * This function returns the version ID of LPIT module of this chip
 *
 * \param[in] obj : pointer to LPIT register instance
 * \return the version ID
 */
__attribute__((always_inline)) static inline uint32_t LpitReg_GetVersion(const LpitRegType *obj)
{
    return ((obj->VERID & LPIT_VERID_VERID_MASK) >> LPIT_VERID_VERID_SHIFT);
}

/*! \brief Get the number of Timer Channels.
 *
 * This function returns the number of Timer Channels in this device
 *
 * \param[in] obj : pointer to LPIT register instance
 * \return the number of Timer Channels
 */
__attribute__((always_inline)) static inline uint8_t LpitReg_GetTimerChannelNum(const LpitRegType *obj)
{
    return ((obj->PARAM & LPIT_PARAM_CHANNEL_MASK) >> LPIT_PARAM_CHANNEL_SHIFT);
}

/*! \brief Get the number of external triggers input.
 *
 * This function returns the external triggers implemented in this device
 *
 * \param[in] obj : pointer to LPIT register instance
 * \return the number of external triggers input
 */
__attribute__((always_inline)) static inline uint8_t LpitReg_GetExtTriggerNum(const LpitRegType *obj)
{
    return ((obj->PARAM & LPIT_PARAM_EXT_TRIG_MASK) >> LPIT_PARAM_EXT_TRIG_SHIFT);
}

/*! \brief Enables the LPIT module.
 *
 * This function enables the functional clock of LPIT module (it does not
 * affect the system clock gating control).
 *
 * \note The M_CEN bit must be asserted when accessing these registers:
 *       - Module Status Register (MSR)
 *       - Set Timer Enable Register (SETTEN)
 *       - Clear Timer Enable Register (CLRTEN)
 *       - Timer Value Registers (TVALn)
 *       - Current Timer Value Registers (CVALn)
 *       - Timer Control Registers (TCTRLn)
 *       Accessing the above mentioned registers while M_CEN = '0', will assert a transfer error for that bus cycle.
 *       - 0 : those registers above write disable
 *       - 1 : those registers above write enable
 *
 * \param[in] obj : pointer to LPIT register instance
 */
__attribute__((always_inline)) static inline void LpitReg_Enable(LpitRegType *obj)
{
    uint32_t tmp = obj->MCR;

    tmp &= ~LPIT_MCR_M_CEN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(1u)) << LPIT_MCR_M_CEN_SHIFT)) & LPIT_MCR_M_CEN_MASK);
    obj->MCR = tmp;
}

/*! \brief Disable the LPIT module.
 *
 * This function disables functional clock of LPIT module (it does not
 * affect the system clock gating control).
 *
 * \note The M_CEN bit must be asserted when accessing these registers:
 *       - Module Status Register (MSR)
 *       - Set Timer Enable Register (SETTEN)
 *       - Clear Timer Enable Register (CLRTEN)
 *       - Timer Value Registers (TVALn)
 *       - Current Timer Value Registers (CVALn)
 *       - Timer Control Registers (TCTRLn)
 *       Acessing the above mentioned registers while M_CEN = '0', will assert a transfer error for that bus cycle.
 *       - 0 : those registers above write disable
 *       - 1 : those registers above write enable
 *
 * \param[in] obj : pointer to LPIT register instance
 */
__attribute__((always_inline)) static inline void LpitReg_Disable(LpitRegType *obj)
{
    uint32_t tmp = obj->MCR;

    tmp &= ~LPIT_MCR_M_CEN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(0u)) << LPIT_MCR_M_CEN_SHIFT)) & LPIT_MCR_M_CEN_MASK);
    obj->MCR = tmp;
}

/*! \brief Get the current command of LowPower Mode
 *
 * This function returns the current command of LowPower Mode
 *
 * \param[in] obj : pointer to LPIT register instance
 * \return the current command of LP Mode
 *         - 0 : stop timer channels in LowPower mode
 *         - 1 : allow timer channels to continue to run in LP mode
 */
__attribute__((always_inline)) static inline uint8_t LpitReg_GetLpModeCmd(const LpitRegType *obj)
{
    return ((obj->MCR & LPIT_MCR_LP_EN_MASK) >> LPIT_MCR_LP_EN_SHIFT);
}

/*! \brief Sets operation of LPIT in LowPower Mode.
 *
 * When the device enters debug mode, the timer channels may or may not be frozen,
 * based on the configuration of this function. The LPIT must use an external or
 * internal clock source which remains operating during LowPower mode
 *
 * \param[in] obj : pointer to LPIT register instance
 * \param[in] value : the current command of LowPower Mode
 *            - 0 : stop timer channels in LP mode
 *            - 1 : allow timer channels to continue to run in LP mode
 */
__attribute__((always_inline)) static inline void LpitReg_SetLpModeCmd(LpitRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MCR;

    tmp &= ~LPIT_MCR_LP_EN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << LPIT_MCR_LP_EN_SHIFT)) & LPIT_MCR_LP_EN_MASK);
    obj->MCR = tmp;
}

/*! \brief Get the current command of debug mode
 *
 * This function returns the current command of debug mode
 *
 * \param[in] obj : pointer to LPIT register instance
 * \return the current command of debug mode
 *         - 0 : stop timer channels in debug mode
 *         - 1 : allow timer channels to continue to run in debug mode
 */
__attribute__((always_inline)) static inline uint8_t LpitReg_GetDebugModeCmd(const LpitRegType *obj)
{
    return ((obj->MCR & LPIT_MCR_DBG_EN_MASK) >> LPIT_MCR_DBG_EN_SHIFT);
}

/*! \brief Sets operation of LPIT in debug mode.
 *
 * When the device enters debug mode, the timer channels may or may not be frozen,
 * based on the configuration of this function. This is intended to aid software development,
 * allowing the developer to halt the processor, investigate the current state of
 * the system (for example, the timer channel values), and continue the operation.
 *
 * \param[in] obj : pointer to LPIT register instance
 * \param[in] value : the current command of debug mode
 *            - 0 : stop timer channels in debug mode
 *            - 1 : allow timer channels to continue to run in debug mode
 */
__attribute__((always_inline)) static inline void LpitReg_SetDebugModeCmd(LpitRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MCR;

    tmp &= ~LPIT_MCR_DBG_EN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << LPIT_MCR_DBG_EN_SHIFT)) & LPIT_MCR_DBG_EN_MASK);
    obj->MCR = tmp;
}

/*! \brief Gets the interrupt flag of timer channels.
 *
 * This function gets current interrupt flag of timer channels.
 *
 * \param[in] obj : pointer to LPIT register instance
 * \param[in] mask : the interrupt flag getting mask that decides which channels will be got interrupt flag.
 *            For example:
 *            - with mask = 0x01u then the interrupt flag of channel 0 only will be got
 *            - with mask = 0x02u then the interrupt flag of channel 1 only will be got
 *            - with mask = 0x03u then the interrupt flags of channel 0 and channel 1 will be got
 * \return the interrupt flag of timer channels.
 */
__attribute__((always_inline)) static inline uint32_t LpitReg_GetInterruptFlag(const LpitRegType *obj, uint32_t mask)
{
    return (obj->MSR) & mask;
}

/*! \brief Clears the interrupt flag of timer channels.
 *
 * This function clears current interrupt flag of timer channels.
 *
 * \param[in] obj : pointer to LPIT register instance
 * \param[in] mask : the interrupt flag getting mask that decides which channels will be got interrupt flag.
 *            For example:
 *            - with mask = 0x01u then the interrupt flag of channel 0 only will be cleared
 *            - with mask = 0x02u then the interrupt flag of channel 1 only will be cleared
 *            - with mask = 0x03u then the interrupt flags of channel 0 and channel 1 will be cleared
 */
__attribute__((always_inline)) static inline void LpitReg_ClearInterruptFlag(LpitRegType *obj, uint32_t mask)
{
    /* Write 1 to clear the interrupt flag. */
    obj->MSR = mask;
    /* Read back to avoid problem */
    (void)obj->MSR;
}

/*! \brief Enables the interrupt generation for timer channels.
 *
 * This function allows enabling interrupt generation for timer channels simultaneously.
 *
 * \param[in] obj : pointer to LPIT register instance
 * \param[in] mask : the interrupt enabling mask that decides which channels will be enabled interrupt.
 *            For example:
 *            - with mask = 0x01u then will enable interrupt for channel 0 only
 *            - with mask = 0x02u then will enable interrupt for channel 1 only
 *            - with mask = 0x03u then will enable interrupt for channel 0 and channel 1
 */
__attribute__((always_inline)) static inline void LpitReg_EnableInterruptTimerChannels(LpitRegType *obj, uint32_t mask)
{
    obj->MIER |= mask;
}

/*! \brief Clears the interrupt flag of timer channels.
 *
 * This function allows disabling interrupt generation for timer channels simultaneously.
 *
 * \param[in] obj : pointer to LPIT register instance
 * \param[in] mask : the interrupt disabling mask that decides which channels will be disabled interrupt.
 *            For example:
 *            - with mask = 0x01u then will disable interrupt for channel 0 only
 *            - with mask = 0x02u then will disable interrupt for channel 1 only
 *            - with mask = 0x03u then will disable interrupt for channel 0 and channel 1
 */
__attribute__((always_inline)) static inline void LpitReg_DisableInterruptTimerChannels(LpitRegType *obj, uint32_t mask)
{
    obj->MIER &= ~mask;
}

/*! \brief Starts the timer channel counting.
 *
 * This function allows starting timer channels simultaneously.
 * After calling this function, timer channels are going operate depend on mode and
 * control bits which controls timer channel start, reload and restart.
 *
 * \param[in] obj : pointer to LPIT register instance
 * \param[in] mask : timer channels starting mask that decides which channels will be started
 *            For example:
 *            - with mask = 0x01U then channel 0 will be started
 *            - with mask = 0x02U then channel 1 will be started
 *            - with mask = 0x03U then channel 0 and channel 1 will be started
 */
__attribute__((always_inline)) static inline void LpitReg_StartTimerChannels(LpitRegType *obj, uint32_t mask)
{
    obj->SETTEN |= mask;
}

/*! \brief Stops the timer channel from counting.
 *
 * This function allows stop timer channels simultaneously from counting.
 * Timer channels reload their periods respectively after the next time
 * they call the LPIT_DRV_StartTimerChannels. Note that: In 32-bit Trigger Accumulator
 * mode, the counter will load on the first trigger rising edge.
 *
 * \param[in] obj : pointer to LPIT register instance
 * \param[in] mask : timer channels stopping mask that decides which channels will be stopped
 *            For example:
 *            - with mask = 0x01U then channel 0 will be stopped
 *            - with mask = 0x02U then channel 1 will be stopped
 *            - with mask = 0x03U then channel 0 and channel 1 will be stopped
 */
__attribute__((always_inline)) static inline void LpitReg_StopTimerChannels(LpitRegType *obj, uint32_t mask)
{
    obj->CLRTEN |= mask;
}

/*! \brief Gets the timer channel period in count unit.
 *
 * This function returns current period of timer channel given as argument.
 *
 * \param[in] obj : pointer to LPIT register instance
 * \param[in] channel : timer channel number
 * \return timer channel period in count unit
 */
__attribute__((always_inline)) static inline uint32_t LpitReg_GetTimerPeriodByCount(const LpitRegType *obj, uint8_t channel)
{
    return obj->TMR[channel].TVAL;
}

/*! \brief Sets the timer channel period in count unit.
 *
 * This function sets the timer channel period in count unit.
 * - In compare mode: Timer Value (TMR_VAL) is the timer channel start value.
 * - The timer will count down until the timer reaches 0, then the timer will generate
 *   an interrupt and load the Timer Value register (TVALn) value again.
 * - Writing a new value to the Timer Value register (TVALn) will not restart the timer channel;
 *   instead the new value will be loaded after the timer expires.
 * - To abort the current timer cycle and start a timer period with a new value, the timer channel must be disabled and enabled again.
 * - In capture mode: whenever the trigger asserts, the Timer Value register stores the inverse of the counter value.
     - 00000000h : Invalid load value in compare mode
     - 00000001h : Invalid load value in compare mode
     - 00000002h-ffffffffh : In compare mode: the value to be loaded; in capture mode, the value of the timer
 *
 * \param[in] obj : pointer to LPIT register instance
 * \param[in] channel : timer channel number
 * \param[in] count : timer channel period in count unit
 */
__attribute__((always_inline)) static inline void LpitReg_SetTimerPeriodByCount(LpitRegType *obj, uint8_t channel, uint32_t count)
{
    obj->TMR[channel].TVAL = count;
}

/*! \brief Gets the current timer channel counting value.
 *
 * This function returns the real-time timer channel counting value, the value in
 * a range from 0 to timer channel period.
 * Need to make sure the running time does not exceed the timer channel period.
 *
 * \param[in] obj : pointer to LPIT register instance
 * \param[in] channel : timer channel number
 * \return current timer channel counting value
 */
__attribute__((always_inline)) static inline uint32_t LpitReg_GetCurrentTimerCount(const LpitRegType *obj, uint8_t channel)
{
    return obj->TMR[channel].CVAL;
}

/*! \brief Gets current state of time channel enable
 *
 * This function gets the current state of time channel enable
 *
 * \param[in] obj : pointer to LPIT register instance
 * \param[in] channel : timer channel number
 * \return the current state of time channel enable
 *         - 0 : timer Channel is disabled, counter reset to 0xffff_ffff
 *         - 1 : timer Channel is enabled
 */
__attribute__((always_inline)) static inline uint8_t LpitReg_GetTimerChannelEnable(const LpitRegType *obj, uint8_t channel)
{
    return ((obj->TMR[channel].TCTRL & LPIT_TMR_TCTRL_T_EN_MASK) >> LPIT_TMR_TCTRL_T_EN_SHIFT);
}

/*! \brief Enables or disables the Timer Channel
 *
 * This function enables or disables the Timer Channel
 *
 * \note If this bit is set, SET_T_EN_n will also be set
 *
 * \param[in] obj : pointer to LPIT register instance
 * \param[in] channel : timer channel number
 * \param[in] enable : operation mode of timer channel
 *            - 0 : timer Channel is disabled, counter reset to 0xffff_ffff
 *            - 1 : timer Channel is enabled
 */
__attribute__((always_inline)) static inline void LpitReg_SetTimerChannelEnable(LpitRegType *obj, uint8_t channel, uint8_t enable)
{
    uint32_t tmp = obj->TMR[channel].TCTRL;

    tmp &= ~LPIT_TMR_TCTRL_T_EN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(enable)) << LPIT_TMR_TCTRL_T_EN_SHIFT)) & LPIT_TMR_TCTRL_T_EN_MASK);
    obj->TMR[channel].TCTRL = tmp;
}

/*! \brief Gets current state of timer channel chaining.
 *
 * This function gets the current state of timer channel chaining.
 * When enabled, the timer channel will decrement when timer channel N-1 trigger asserts.
 *
 * \param[in] obj : pointer to LPIT register instance
 * \param[in] channel : timer channel number
 * \return the current state of timer channel chaining
 *         - 0 : Channel Chaining is disabled. The channel timer runs independently.
 *         - 1 : Channel Chaining is enabled. The timer decrements on the previous channel's timeout.
 */
__attribute__((always_inline)) static inline uint8_t LpitReg_GetTimerChannelChainCmd(const LpitRegType *obj, uint8_t channel)
{
    return ((obj->TMR[channel].TCTRL & LPIT_TMR_TCTRL_CHAIN_MASK) >> LPIT_TMR_TCTRL_CHAIN_SHIFT);
}

/*! \brief Sets timer channel chaining.
 *
 * This function sets the timer channel to be chained or not chained.
 * When enabled, the timer channel will decrement when timer channel N-1 trigger asserts.
 *
 * \note Timer channel 0 cannot be chained.
 *
 * \note If this bit is set, SET_T_EN_n will also be set
 *
 * \param[in] obj : pointer to LPIT register instance
 * \param[in] channel : timer channel number
 * \param[in] isChannelChained : timer channel chaining
 *            - 0 : Channel Chaining is disabled. The channel timer runs independently.
 *            - 1 : Channel Chaining is enabled. The timer decrements on the previous channel's timeout.
 */
__attribute__((always_inline)) static inline void LpitReg_SetTimerChannelChainCmd(LpitRegType *obj, uint8_t channel, uint8_t isChannelChained)
{
    uint32_t tmp = obj->TMR[channel].TCTRL;

    tmp &= ~LPIT_TMR_TCTRL_CHAIN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(isChannelChained)) << LPIT_TMR_TCTRL_CHAIN_SHIFT)) & LPIT_TMR_TCTRL_CHAIN_MASK);
    obj->TMR[channel].TCTRL = tmp;
}

/*! \brief Gets current operation mode of timer channel.
 *
 * This function gets current operation mode of the timer channel given as argument.
 *
 * \param[in] obj : pointer to LPIT register instance
 * \param[in] channel : timer channel number
 * \return operation mode of timer channel
 *         - 0 : 32-bit Periodic Counter
 *         - 1 : Dual 16-bit Periodic Counter
 *         - 2 : 32-bit Trigger Accumulator
 *         - 3 : 32-bit Trigger Input Capture
 */
__attribute__((always_inline)) static inline uint8_t LpitReg_GetTimerChannelModeCmd(const LpitRegType *obj, uint8_t channel)
{
    return ((obj->TMR[channel].TCTRL & LPIT_TMR_TCTRL_MODE_MASK) >> LPIT_TMR_TCTRL_MODE_SHIFT);
}

/*! \brief Sets operation mode of timer channel
 *
 * This function sets the timer channel operation mode which control how
 * the timer channel decrements.
 *
 * \param[in] obj : pointer to LPIT register instance
 * \param[in] channel : timer channel number
 * \param[in] mode : operation mode of timer channel
 *            - 0 : 32-bit Periodic Counter
 *            - 1 : Dual 16-bit Periodic Counter
 *            - 2 : 32-bit Trigger Accumulator
 *            - 3 : 32-bit Trigger Input Capture
 */
__attribute__((always_inline)) static inline void LpitReg_SetTimerChannelModeCmd(LpitRegType *obj, uint8_t channel, uint8_t mode)
{
    uint32_t tmp = obj->TMR[channel].TCTRL;

    tmp &= ~LPIT_TMR_TCTRL_MODE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(mode)) << LPIT_TMR_TCTRL_MODE_SHIFT)) & LPIT_TMR_TCTRL_MODE_MASK);
    obj->TMR[channel].TCTRL = tmp;
}

/*! \brief Gets current command of timer channel start on trigger.
 *
 * This function gets current command of timer channel start on trigger.
 *
 * \param[in] obj : pointer to LPIT register instance
 * \param[in] channel : timer channel number
 * \return current command of timer channel start on trigger.
 *         - 0 : Timer starts to decrement immediately based on the restart condition
 *               (controlled by the Timer Stop On Interrupt bit (TSOI))
 *         - 1 : Timer starts to decrement when a rising edge on a selected trigger is detected
 */
__attribute__((always_inline)) static inline uint8_t LpitReg_GetStartOnTriggerCmd(const LpitRegType *obj, uint8_t channel)
{
    return ((obj->TMR[channel].TCTRL & LPIT_TMR_TCTRL_TSOT_MASK) >> LPIT_TMR_TCTRL_TSOT_SHIFT);
}

/*! \brief Sets timer channel start on trigger.
 *
 * This function sets the timer channel to starts/don't start on trigger.
 *
 * \param[in] obj : pointer to LPIT register instance
 * \param[in] channel : timer channel number
 * \param[in] isStartOnTrigger : timer channel start on trigger
 *            - 0 : Timer starts to decrement immediately based on the restart condition
 *                  (controlled by the Timer Stop On Interrupt bit (TSOI))
 *            - 1 : Timer starts to decrement when a rising edge on a selected trigger is detected
 */
__attribute__((always_inline)) static inline void LpitReg_SetStartOnTriggerCmd(LpitRegType *obj, uint8_t channel, uint8_t isStartOnTrigger)
{
    uint32_t tmp = obj->TMR[channel].TCTRL;

    tmp &= ~LPIT_TMR_TCTRL_TSOT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(isStartOnTrigger)) << LPIT_TMR_TCTRL_TSOT_SHIFT)) & LPIT_TMR_TCTRL_TSOT_MASK);
    obj->TMR[channel].TCTRL = tmp;
}

/*! \brief Gets current command of timer channel stop on interrupt.
 *
 * This function gets current command of timer channel stop on interrupt.
 *
 * \param[in] obj : pointer to LPIT register instance
 * \param[in] channel : timer channel number
 * \return current command of timer channel stop on interrupt.
 *         - 0 : the channel timer does not stop after timeout
 *         - 1 : The channel timer will stop after a timeout,
 *               and the channel timer will restart based on Timer Start On Trigger bit (TSOT).
 *               When TSOT = 0, the channel timer will restart after a rising edge on the Timer Enable bit (T_EN) is detected
 *               (which means that the timer channel is disabled and then enabled).
 *               When TSOT = 1, the channel timer will restart after a rising edge on the selected trigger is detected.
 */
__attribute__((always_inline)) static inline uint8_t LpitReg_GetStopOnInterruptCmd(const LpitRegType *obj, uint8_t channel)
{
    return ((obj->TMR[channel].TCTRL & LPIT_TMR_TCTRL_TSOI_MASK) >> LPIT_TMR_TCTRL_TSOI_SHIFT);
}

/*! \brief Sets timer channel stop on interrupt.
 *
 * This function sets the timer channel to stop or don't stop after it times out.
 *
 * \param[in] obj : pointer to LPIT register instance
 * \param[in] channel : timer channel number
 * \param[in] isStopOnInterrupt : timer channel stop on interrupt
 *            - 0 : the channel timer does not stop after timeout
 *            - 1 : The channel timer will stop after a timeout,
 *                  and the channel timer will restart based on Timer Start On Trigger bit (TSOT).
 *                  When TSOT = 0, the channel timer will restart after a rising edge on the Timer Enable bit (T_EN) is detected
 *                  (which means that the timer channel is disabled and then enabled).
 *                  When TSOT = 1, the channel timer will restart after a rising edge on the selected trigger is detected.
 */
__attribute__((always_inline)) static inline void LpitReg_SetStopOnInterruptCmd(LpitRegType *obj, uint8_t channel, uint8_t isStopOnInterrupt)
{
    uint32_t tmp = obj->TMR[channel].TCTRL;

    tmp &= ~LPIT_TMR_TCTRL_TSOI_MASK;
    tmp |= (((uint32_t)(((uint32_t)(isStopOnInterrupt)) << LPIT_TMR_TCTRL_TSOI_SHIFT)) & LPIT_TMR_TCTRL_TSOI_MASK);
    obj->TMR[channel].TCTRL = tmp;
}

/*! \brief Gets current command of timer channel reload on trigger.
 *
 * This function gets current command of timer channel reload on trigger.
 *
 * \param[in] obj : pointer to LPIT register instance
 * \param[in] channel : timer channel number
 * \return current command of timer channel reload on trigger.
 *         - 0 : timer will not reload on the selected trigger
 *         - 1 : timer will reload on the selected trigger
 */
__attribute__((always_inline)) static inline uint8_t LpitReg_GetReloadOnTriggerCmd(const LpitRegType *obj, uint8_t channel)
{
    return ((obj->TMR[channel].TCTRL & LPIT_TMR_TCTRL_TROT_MASK) >> LPIT_TMR_TCTRL_TROT_SHIFT);
}

/*! \brief Sets timer channel reload on trigger.
 *
 * This function sets the timer channel to reload/don't reload on trigger.
 * When set, the LPIT timer will reload when a rising edge is detected on the selected trigger input.
 * The trigger input is ignored if the LPIT is disabled during debug mode (DBGEN = 0) or LowPower mode
 *
 * \param[in] obj : pointer to LPIT register instance
 * \param[in] channel : timer channel number
 * \param[in] isReloadOnTrigger : timer channel reload on trigger
 *            - 0 : timer will not reload on the selected trigger
 *            - 1 : timer will reload on the selected trigger
 */
__attribute__((always_inline)) static inline void LpitReg_SetReloadOnTriggerCmd(LpitRegType *obj, uint8_t channel, uint8_t isReloadOnTrigger)
{
    uint32_t tmp = obj->TMR[channel].TCTRL;

    tmp &= ~LPIT_TMR_TCTRL_TROT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(isReloadOnTrigger)) << LPIT_TMR_TCTRL_TROT_SHIFT)) & LPIT_TMR_TCTRL_TROT_MASK);
    obj->TMR[channel].TCTRL = tmp;
}

/*! \brief Gets current command of timer channel trigger source.
 *
 * This function gets current command of timer channel trigger source.
 *
 * \param[in] obj : pointer to LPIT register instance
 * \param[in] channel : timer channel number
 * \return current trigger source of timer channel.
 *         - 0 : selects external triggers
 *         - 1 : selects internal triggers
 */
__attribute__((always_inline)) static inline uint8_t LpitReg_GetTriggerSourceCmd(const LpitRegType *obj, uint8_t channel)
{
    return ((obj->TMR[channel].TCTRL & LPIT_TMR_TCTRL_TRG_SRC_MASK) >> LPIT_TMR_TCTRL_TRG_SRC_SHIFT);
}

/*! \brief Sets trigger source of timer channel.
 *
 * This function sets trigger source of the timer channel to be internal or external trigger.
 * Selects between internal or external trigger sources. The trigger to be used is selected using the TRG_SRC and TRG_SEL bits.
 * Refer to the chip configuration section for available external trigger options.
 * If a channel does not have an associated external trigger, then set the Trigger Source bit (TRG_SRC) = 1.
 *
 * \param[in] obj : pointer to LPIT register instance
 * \param[in] channel : timer channel number
 * \param[in] triggerSource : timer channel reload on trigger
 *            - 0 : selects external triggers
 *            - 1 : selects internal triggers
 */
__attribute__((always_inline)) static inline void LpitReg_SetTriggerSourceCmd(LpitRegType *obj, uint8_t channel, uint8_t triggerSource)
{
    uint32_t tmp = obj->TMR[channel].TCTRL;

    tmp &= ~LPIT_TMR_TCTRL_TRG_SRC_MASK;
    tmp |= (((uint32_t)(((uint32_t)(triggerSource)) << LPIT_TMR_TCTRL_TRG_SRC_SHIFT)) & LPIT_TMR_TCTRL_TRG_SRC_MASK);
    obj->TMR[channel].TCTRL = tmp;
}

/*! \brief Gets the selection of the trigger to use for starting and/or reloading the LPIT timer.
 *
 * This function gets the selection of the trigger to use for starting and/or reloading the LPIT timer.
 *
 * \param[in] obj : pointer to LPIT register instance
 * \param[in] channel : timer channel number
 * \return current selection.
 *         - 0 ~ 3 : timer channel 0 ~ 3 trigger source is selected
 *         - 4 ~ 15 : reserved
 */
__attribute__((always_inline)) static inline uint8_t LpitReg_GetTriggerSelectCmd(const LpitRegType *obj, uint8_t channel)
{
    return ((obj->TMR[channel].TCTRL & LPIT_TMR_TCTRL_TRG_SEL_MASK) >> LPIT_TMR_TCTRL_TRG_SEL_SHIFT);
}

/*! \brief Selects the trigger to use for starting and/or reloading the LPIT timer.
 *
 * This function selects the trigger to use for starting and/or reloading the LPIT timer.
 *
 * The TRG_SEL field selects one trigger from the set of internal or external triggers
 * that are selected by the Trigger Source bit (TRG_SRC)
 * Recall that the TRG_SRC bit selects between internal and external trigger signals for each channel
 *
 * \note The Trigger Select field should only be changed when the LPIT timer channel is disabled.
 *
 * \param[in] obj : pointer to LPIT register instance
 * \param[in] channel : timer channel number
 * \param[in] triggerChannelSelect : selection of the trigger
 *            - 0 ~ 3 : timer channel 0 ~ 3 trigger source is selected
 *            - 4 ~ 15 : reserved
 */
__attribute__((always_inline)) static inline void LpitReg_SetTriggerSelectCmd(LpitRegType *obj, uint8_t channel, uint8_t triggerChannelSelect)
{
    uint32_t tmp = obj->TMR[channel].TCTRL;

    tmp &= ~LPIT_TMR_TCTRL_TRG_SEL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(triggerChannelSelect)) << LPIT_TMR_TCTRL_TRG_SEL_SHIFT)) & LPIT_TMR_TCTRL_TRG_SEL_MASK);
    obj->TMR[channel].TCTRL = tmp;
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _LPIT_REG_H_ */
