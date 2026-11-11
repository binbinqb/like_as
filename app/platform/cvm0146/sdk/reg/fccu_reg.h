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

#ifndef _FCCU_REG_H_
#define _FCCU_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the FCCU Registers
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

/* CTRL Bit Fields */
#define FCCU_CTRL_DEBUG_MASK        (0x200u)
#define FCCU_CTRL_DEBUG_SHIFT       (9u)
#define FCCU_CTRL_DEBUG_WIDTH       (1u)
#define FCCU_CTRL_CFG_TO_IEN_MASK   (0x01u)
#define FCCU_CTRL_CFG_TO_IEN_SHIFT  (0u)
#define FCCU_CTRL_CFG_TO_IEN_WIDTH  (1u)

/* OP_CTRL Bit Fields */
#define FCCU_OP_CTRL_OPR_MASK       (0x1Fu)
#define FCCU_OP_CTRL_OPR_SHIFT      (0u)
#define FCCU_OP_CTRL_OPR_WIDTH      (5u)

/* OP_ST Bit Fields */
#define FCCU_OP_ST_OPS_MASK         (0x03u)
#define FCCU_OP_ST_OPS_SHIFT        (0u)
#define FCCU_OP_ST_OPS_WIDTH        (2u)

/* TRANS_LOCK Bit Fields */
#define FCCU_TRANS_LOCK_KEY_MASK    (0xFFFFFFFFu)
#define FCCU_TRANS_LOCK_KEY_SHIFT   (0u)
#define FCCU_TRANS_LOCK_KEY_WIDTH   (32u)

/* PERMNT_LOCK Bit Fields */
#define FCCU_PERMNT_LOCK_KEY_MASK   (0xFFFFFFFFu)
#define FCCU_PERMNT_LOCK_KEY_SHIFT  (0u)
#define FCCU_PERMNT_LOCK_KEY_WIDTH  (32u)

/* CFG Bit Fields */
#define FCCU_CFG_MASK               (0xFFFFFFFFu)
#define FCCU_CFG_SHIFT              (0u)
#define FCCU_CFG_WIDTH              (32u)

/* IRQ_EN Bit Fields */
#define FCCU_IRQ_EN_ALARM_MASK      (0xFFFFFFFFu)
#define FCCU_IRQ_EN_ALARM_SHIFT     (0u)
#define FCCU_IRQ_EN_ALARM_WIDTH     (32u)

/* TYPE Bit Fields */
#define FCCU_TYPE_ALARM_MASK        (0xFFFFFFFFu)
#define FCCU_TYPE_ALARM_SHIFT       (0u)
#define FCCU_TYPE_ALARM_WIDTH       (32u)

/* CFG_TO Bit Fields */
#define FCCU_CFG_TO_CFG_TO_MASK     (0x07u)
#define FCCU_CFG_TO_CFG_TO_SHIFT    (0u)
#define FCCU_CFG_TO_CFG_TO_WIDTH    (3u)

/* ST Bit Fields */
#define FCCU_ST_CFG_REG_LOCK_MASK   (0x80000000u)
#define FCCU_ST_CFG_REG_LOCK_SHIFT  (31u)
#define FCCU_ST_CFG_REG_LOCK_WIDTH  (1u)
#define FCCU_ST_ERR_IN_MASK         (0x10u)
#define FCCU_ST_ERR_IN_SHIFT        (4u)
#define FCCU_ST_ERR_IN_WIDTH        (1u)
#define FCCU_ST_FSM_MASK            (0x03u)
#define FCCU_ST_FSM_SHIFT           (0u)
#define FCCU_ST_FSM_WIDTH           (2u)

/* FAKE Bit Fields */
#define FCCU_FAKE_FAULT_FAKE_MASK   (0xFFFFFFFFu)
#define FCCU_FAKE_FAULT_FAKE_SHIFT  (0u)
#define FCCU_FAKE_FAULT_FAKE_WIDTH  (32u)

/* DBG_ST1 Bit Fields */
#define FCCU_DBG_ST1_N2A_SRC_MASK   (0xFFFFFFFFu)
#define FCCU_DBG_ST1_N2A_SRC_SHIFT  (0u)
#define FCCU_DBG_ST1_N2A_SRC_WIDTH  (32u)

/* DBG_ST2 Bit Fields */
#define FCCU_DBG_ST2_A2F_SRC0_MASK  (0xFFFFFFFFu)
#define FCCU_DBG_ST2_A2F_SRC0_SHIFT (0u)
#define FCCU_DBG_ST2_A2F_SRC0_WIDTH (32u)

/* DBG_ST3 Bit Fields */
#define FCCU_DBG_ST3_A2F_SRC1_MASK  (0xFFFFFFFFu)
#define FCCU_DBG_ST3_A2F_SRC1_SHIFT (0u)
#define FCCU_DBG_ST3_A2F_SRC1_WIDTH (32u)

/* DBG_ST4 Bit Fields */
#define FCCU_DBG_ST4_N2F_SRC_MASK   (0xFFFFFFFFu)
#define FCCU_DBG_ST4_N2F_SRC_SHIFT  (0u)
#define FCCU_DBG_ST4_N2F_SRC_WIDTH  (32u)

/* DBG_ST5 Bit Fields */
#define FCCU_DBG_ST5_F2A_SRC_MASK   (0xFFFFFFFFu)
#define FCCU_DBG_ST5_F2A_SRC_SHIFT  (0u)
#define FCCU_DBG_ST5_F2A_SRC_WIDTH  (32u)

/* IRQ_ST Bit Fields */
#define FCCU_IRQ_ST_NMI_MASK        (0x04u)
#define FCCU_IRQ_ST_NMI_SHIFT       (2u)
#define FCCU_IRQ_ST_NMI_WIDTH       (1u)
#define FCCU_IRQ_ST_ALARM_MASK      (0x02u)
#define FCCU_IRQ_ST_ALARM_SHIFT     (1u)
#define FCCU_IRQ_ST_ALARM_WIDTH     (1u)
#define FCCU_IRQ_ST_CFG_TO_MASK     (0x01u)
#define FCCU_IRQ_ST_CFG_TO_SHIFT    (0u)
#define FCCU_IRQ_ST_CFG_TO_WIDTH    (1u)

/* TMR_ALARM Bit Fields */
#define FCCU_TMR_ALARM_CNT_MASK     (0xFFFFFFFFu)
#define FCCU_TMR_ALARM_CNT_SHIFT    (0u)
#define FCCU_TMR_ALARM_CNT_WIDTH    (32u)

/* TMR_CFG Bit Fields */
#define FCCU_TMR_CFG_CNT_MASK       (0xFFFFFFFFu)
#define FCCU_TMR_CFG_CNT_SHIFT      (0u)
#define FCCU_TMR_CFG_CNT_WIDTH      (32u)

/* TMR_EOUT Bit Fields */
#define FCCU_TMR_EOUT_CNT_MASK      (0xFFFFFFFFu)
#define FCCU_TMR_EOUT_CNT_SHIFT     (0u)
#define FCCU_TMR_EOUT_CNT_WIDTH     (32u)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief The definition of FCCU registers
 */
typedef struct _FccuRegType_
{
    volatile uint32_t       CTRL;         /*!< Control Register, offset: 0x0 */
    volatile uint32_t       OP_CTRLK;     /*!< Operate Key Register, offset: 0x4 */
    volatile uint32_t       OP_CTRL;      /*!< Operate Control Register, offset: 0x8 */
    const volatile uint32_t OP_ST;        /*!< Excute Status Register, offset: 0xC */
    volatile uint32_t       TRANS_LOCK;   /*!< Transient Lock Register, offset: 0x10 */
    volatile uint32_t       PERMNT_LOCK;  /*!< Permanent Lock Register, offset: 0x14 */
    uint32_t                RESERVE0[2];  /*!< Reserverd block, offset: 0x18 */
    volatile uint32_t       CFG;          /*!< Config Register, offset: 0x20 */
    volatile uint32_t       DELTA_T;      /*!< EOut Min hold time Register, offset: 0x24 */
    volatile uint32_t       RST_EN;       /*!< Reset Enable Register, offset: 0x28 */
    volatile uint32_t       IRQ_EN;       /*!< Alarm Irq Enable Register, offset: 0x2C */
    volatile uint32_t       NMI_EN;       /*!< NMI Irq Enable Register, offset: 0x30 */
    volatile uint32_t       EOUT_EN;      /*!< EOut output Enable Register, offset: 0x34 */
    volatile uint32_t       CHE;          /*!< Error Channel Enable Register, offset: 0x38 */
    volatile uint32_t       TYPE;         /*!< Error Type Register, offset: 0x3C */
    volatile uint32_t       ALARM_TO;     /*!< Alarm Status Timeout Register, offset: 0x40 */
    volatile uint32_t       CFG_TO;       /*!< Config Status Timeout Register, offset: 0x44 */
    uint32_t                RESERVE1[22]; /*!< Reserverd block, offset: 0x48 */
    volatile uint32_t       FST;          /*!< Config Status Register, offset: 0xA0 */
    volatile uint32_t       FSTK;         /*!< FST Key Register, offset: 0xA4 */
    const volatile uint32_t STAT;         /*!< FSM Module Register, offset: 0xA8 */
    volatile uint32_t       FAKE;         /*!< Software error in fake Register, offset: 0xAC */
    const volatile uint32_t DBG_ST1;      /*!< Status Change Register1, offset: 0xB0 */
    const volatile uint32_t DBG_ST2;      /*!< Status Change Register2, offset: 0xB4 */
    const volatile uint32_t DBG_ST3;      /*!< Status Change Register3, offset: 0xB8 */
    const volatile uint32_t DBG_ST4;      /*!< Status Change Register4, offset: 0xBC */
    const volatile uint32_t DBG_ST5;      /*!< Status Change Register5, offset: 0xC0 */
    volatile uint32_t       IRQ_ST;       /*!< Irq Status Register, offset: 0xC4 */
    const volatile uint32_t TMR_ALARM;    /*!< Alarm timer Register, offset: 0xC8 */
    const volatile uint32_t TMR_CFG;      /*!< CONFIG timer Register, offset: 0xCC */
    const volatile uint32_t TMR_EOUT;     /*!< EOUT timer Register, offset: 0xD0 */
} FccuRegType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Gets the Debug Mode Enable
 *
 * This function gets the current Debug Mode Enable.
 * FCCU module can be contrlled when system enters debug mode.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \return Debug Mode Enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t FccuReg_GetCtrlDebug(const FccuRegType *obj)
{
    return ((obj->CTRL & FCCU_CTRL_DEBUG_MASK) >> FCCU_CTRL_DEBUG_SHIFT);
}

/*! \brief Sets the Debug Mode Enable
 *
 * This function sets the Debug Mode Enable.
 * FCCU module can be contrlled when system enters debug mode.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \param[in] value : the value of Debug Mode Enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void FccuReg_SetCtrlDebug(FccuRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CTRL;

    tmp &= ~FCCU_CTRL_DEBUG_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << FCCU_CTRL_DEBUG_SHIFT)) & FCCU_CTRL_DEBUG_MASK);
    obj->CTRL = tmp;
}

/*! \brief Gets the configure state timeout interrupt enable
 *
 * This function gets the current configure state timeout interrupt enable.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \return configure state timeout interrupt enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t FccuReg_GetCtrlCfgToIEn(const FccuRegType *obj)
{
    return ((obj->CTRL & FCCU_CTRL_CFG_TO_IEN_MASK) >> FCCU_CTRL_CFG_TO_IEN_SHIFT);
}

/*! \brief Sets the configure state timeout interrupt enable
 *
 * This function sets the configure state timeout interrupt enable.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \param[in] value : the value of configure state timeout interrupt enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void FccuReg_SetCtrlCfgToIEn(FccuRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CTRL;

    tmp &= ~FCCU_CTRL_CFG_TO_IEN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << FCCU_CTRL_CFG_TO_IEN_SHIFT)) & FCCU_CTRL_CFG_TO_IEN_MASK);
    obj->CTRL = tmp;
}

/*! \brief Sets the operation control lock/unlock key
 *
 * This function sets the operation control lock/unlock key.
 * Register OP_CTRL can only be modified before operation control key OP_CTRLK is configured.
 * If any other read/write happened after unlock, the operation control is locked again.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \param[in] value : the value of operation control lock/unlock key
 *                    - 2505_D287h : Unlock OP1.
 *                    - 0x0E11_47D7h : Unlock OP2.
 *                    - else : Do nothing.
 */
__attribute__((always_inline)) static inline void FccuReg_SetOpCtrlKey(FccuRegType *obj, uint32_t value)
{
    obj->OP_CTRLK = value;
}

/*! \brief Gets the Operation control
 *
 * This function gets the current Operation control.
 * If OPS is in progress, modify OPS has no work. Configure OPR may change the FSM and status of FCCU.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \return Operation control
 *         - 0h : OP0 - no operation
 *         - 1h : OP1 - FSM changed from NORMAL to CONFIG.
 *         - 2h : OP2 - FSM jumped from CONFIG to NORMAL.
 *         - Ch : OP12 - hardware triggered when clearning FST.
 *         - Dh : OP13 - clear freeze status register
 *         - Eh : OP14 - hardware triggered when configuration is timeout
 *         - Fh : OP15 - clear OP_STAT to IDLE.
 *         - others : reserved
 */
__attribute__((always_inline)) static inline uint8_t FccuReg_GetOpCtrlOpr(const FccuRegType *obj)
{
    return ((obj->OP_CTRL & FCCU_OP_CTRL_OPR_MASK) >> FCCU_OP_CTRL_OPR_SHIFT);
}

/*! \brief Sets the Operation control
 *
 * This function sets the Operation control.
 * If OPS is in progress, modify OPS has no work. Configure OPR may change the FSM and status of FCCU.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \param[in] value : the value of Operation control
 *                    - 0h : OP0 - no operation
 *                    - 1h : OP1 - FSM changed from NORMAL to CONFIG.
 *                    - 2h : OP2 - FSM jumped from CONFIG to NORMAL.
 *                    - Ch : OP12 - hardware triggered when clearning FST.
 *                    - Dh : OP13 - clear freeze status register
 *                    - Eh : OP14 - hardware triggered when configuration is timeout
 *                    - Fh : OP15 - clear OP_STAT to IDLE.
 *                    - others : reserved
 */
__attribute__((always_inline)) static inline void FccuReg_SetOpCtrlOpr(FccuRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->OP_CTRL;

    tmp &= ~FCCU_OP_CTRL_OPR_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << FCCU_OP_CTRL_OPR_SHIFT)) & FCCU_OP_CTRL_OPR_MASK);
    obj->OP_CTRL = tmp;
}

/*! \brief Gets the Operation Status
 *
 * This function gets the current Operation Status.
 * The status is cleared to IDLE after OP15.
 * Some situtation wil cause Abort :
 * - don't unlock FSTK before writing FST register
 * - don't unlock before running OP1/OP2
 * - start OP1 in non-NORMAL FSM;
 * - Start OP1 with configuration register locked.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \return Operation Status
 *         - 0h : Idle
 *         - 1h : In progress
 *         - 2h : Abort
 *         - 3h : Successful
 */
__attribute__((always_inline)) static inline uint8_t FccuReg_GetOpStOpS(const FccuRegType *obj)
{
    return ((obj->OP_ST & FCCU_OP_ST_OPS_MASK) >> FCCU_OP_ST_OPS_SHIFT);
}

/*! \brief Sets the configuration registers temporany lock
 *
 * This function sets the configuration registers temporany lock.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \param[in] value : the value of configuration registers temporany lock
 *                    - A4h : unlock
 *                    - else : lock
 */
__attribute__((always_inline)) static inline void FccuReg_SetTransLockKey(FccuRegType *obj, uint32_t value)
{
    uint32_t tmp = obj->TRANS_LOCK;

    tmp &= ~FCCU_TRANS_LOCK_KEY_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << FCCU_TRANS_LOCK_KEY_SHIFT)) & FCCU_TRANS_LOCK_KEY_MASK);
    obj->TRANS_LOCK = tmp;
}

/*! \brief Sets the configuration registers lock permanently
 *
 * This function sets the configuration registers lock permanently.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \param[in] value : the value of configuration registers lock permanently
 *                    - 68h : lock
 *                    - else : keep
 */
__attribute__((always_inline)) static inline void FccuReg_SetPermntLockKey(FccuRegType *obj, uint32_t value)
{
    uint32_t tmp = obj->PERMNT_LOCK;

    tmp &= ~FCCU_PERMNT_LOCK_KEY_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << FCCU_PERMNT_LOCK_KEY_SHIFT)) & FCCU_PERMNT_LOCK_KEY_MASK);
    obj->PERMNT_LOCK = tmp;
}

/*! \brief Gets the Max of EOut output counter
 *
 * This function gets the current eout counter.
 * Duty cycle is 50%
 * Polarity of output signal in FAULT status.
 * Current EOUT PAD enable.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \return config parameters of eout
 */
__attribute__((always_inline)) static inline uint32_t FccuReg_GetEOutCfg(const FccuRegType *obj)
{
    return obj->CFG;
}

/*! \brief Sets the Max of EOut output counter
 *
 * This function sets the current eout counter.
 * Duty cycle is 50%
 * Polarity of output signal in FAULT status.
 * Current EOUT PAD enable.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \param[in] val : config parameters of eout
 */
__attribute__((always_inline)) static inline void FccuReg_SetEOutCfg(FccuRegType *obj, uint32_t val)
{
    obj->CFG = val;
}

/*! \brief Gets the minimum time of EOUT in FAULT status
 *
 * This function gets the current minimum time of EOUT in FAULT status.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \return minimum time of EOUT in FAULT status
 */
__attribute__((always_inline)) static inline uint32_t FccuReg_GetDeltaT(const FccuRegType *obj)
{
    return obj->DELTA_T;
}

/*! \brief Sets the minimum time of EOUT in FAULT status
 *
 * This function sets the minimum time of EOUT in FAULT status.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \param[in] value : the value of minimum time of EOUT in FAULT status
 */
__attribute__((always_inline)) static inline void FccuReg_SetDeltaT(FccuRegType *obj, uint32_t value)
{
    obj->DELTA_T = value;
}

/*! \brief Gets the channel reset action enable
 *
 * This function gets the current channel reset action enable.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \return channel reset action enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint32_t FccuReg_GetRstEn(const FccuRegType *obj)
{
    return obj->RST_EN;
}

/*! \brief Sets the channel reset action enable
 *
 * This function sets the channel reset action enable.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \param[in] value : the value of channel reset action enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void FccuReg_SetRstEn(FccuRegType *obj, uint32_t value)
{
    obj->RST_EN = value;
}

/*! \brief Gets the channel's interrupt enable in ALARM FSM
 *
 * This function gets the current channel's interrupt enable in ALARM FSM.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \return channel's interrupt enable in ALARM FSM
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint32_t FccuReg_GetIrqEnAlarm(const FccuRegType *obj)
{
    return ((obj->IRQ_EN & FCCU_IRQ_EN_ALARM_MASK) >> FCCU_IRQ_EN_ALARM_SHIFT);
}

/*! \brief Sets the channel's interrupt enable in ALARM FSM
 *
 * This function sets the channel's interrupt enable in ALARM FSM.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \param[in] value : the value of channel's interrupt enable in ALARM FSM
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void FccuReg_SetIrqEnAlarm(FccuRegType *obj, uint32_t value)
{
    uint32_t tmp = obj->IRQ_EN;

    tmp &= ~FCCU_IRQ_EN_ALARM_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << FCCU_IRQ_EN_ALARM_SHIFT)) & FCCU_IRQ_EN_ALARM_MASK);
    obj->IRQ_EN = tmp;
}

/*! \brief Gets the channel's interrupt enable in FAULT FSM
 *
 * This function gets the current channel's interrupt enable in FAULT FSM.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \return channel's interrupt enable in FAULT FSM
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint32_t FccuReg_GetNmiEn(const FccuRegType *obj)
{
    return obj->NMI_EN;
}

/*! \brief Sets the channel's interrupt enable in FAULT FSM
 *
 * This function sets the channel's interrupt enable in FAULT FSM.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \param[in] value : the value of channel's interrupt enable in FAULT FSM
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void FccuReg_SetNmiEn(FccuRegType *obj, uint32_t value)
{
    obj->NMI_EN = value;
}

/*! \brief Gets the EOUT output channel enable
 *
 * This function gets the current EOUT output channel enable.
 * The register enables tied value in FAULT FSM.
 * And the PAD reflects EOUT only when PWM_EN=1.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \return EOUT output channel enable
 *         - 0b : keep PWM output in FAULT FSM
 *         - 1b : keep high/low output in FAUT FSM
 */
__attribute__((always_inline)) static inline uint32_t FccuReg_GetEOutEn(const FccuRegType *obj)
{
    return obj->EOUT_EN;
}

/*! \brief Sets the EOUT output channel enable
 *
 * This function sets the EOUT output channel enable.
 * The register enables tied value in FAULT FSM.
 * And the PAD reflects EOUT only when PWM_EN=1.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \param[in] value : the value of EOUT output channel enable
 *                    - 0b : keep PWM output in FAULT FSM
 *                    - 1b : keep high/low output in FAUT FSM
 */
__attribute__((always_inline)) static inline void FccuReg_SetEOutEn(FccuRegType *obj, uint32_t value)
{
    obj->EOUT_EN = value;
}

/*! \brief Gets the channel's fault enable
 *
 * This function gets the current channel's fault enable.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \return channel's fault enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint32_t FccuReg_GetChE(const FccuRegType *obj)
{
    return obj->CHE;
}

/*! \brief Sets the channel's fault enable
 *
 * This function sets the channel's fault enable.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \param[in] value : the value of channel's fault enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void FccuReg_SetChE(FccuRegType *obj, uint32_t value)
{
    obj->CHE = value;
}

/*! \brief Gets the channel's fault type
 *
 * This function gets the current channel's fault type.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \return channel's fault type
 *         - 0b : critical fault
 *         - 1b : non-critical fault
 */
__attribute__((always_inline)) static inline uint32_t FccuReg_GetTypeAlarm(const FccuRegType *obj)
{
    return ((obj->TYPE & FCCU_TYPE_ALARM_MASK) >> FCCU_TYPE_ALARM_SHIFT);
}

/*! \brief Sets the channel's fault type
 *
 * This function sets the channel's fault type.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \param[in] value : the value of channel's fault type
 *                    - 0b : critical fault
 *                    - 1b : non-critical fault
 */
__attribute__((always_inline)) static inline void FccuReg_SetTypeAlarm(FccuRegType *obj, uint32_t value)
{
    uint32_t tmp = obj->TYPE;

    tmp &= ~FCCU_TYPE_ALARM_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << FCCU_TYPE_ALARM_SHIFT)) & FCCU_TYPE_ALARM_MASK);
    obj->TYPE = tmp;
}

/*! \brief Gets the ALARM FSM timer threshold
 *
 * This function gets the current ALARM FSM timer threshold.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \return ALARM FSM timer threshold
 */
__attribute__((always_inline)) static inline uint32_t FccuReg_GetAlarmTO(const FccuRegType *obj)
{
    return obj->ALARM_TO;
}

/*! \brief Sets the ALARM FSM timer threshold
 *
 * This function sets the ALARM FSM timer threshold.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \param[in] value : the value of ALARM FSM timer threshold
 */
__attribute__((always_inline)) static inline void FccuReg_SetAlarmTO(FccuRegType *obj, uint32_t value)
{
    obj->ALARM_TO = value;
}

/*! \brief Gets the CONFIG FSM timeout threshold
 *
 * This function gets the current CONFIG FSM timeout threshold.
 * The threshold is 2^(CFGTO+13)
 *
 * \param[in] obj : pointer to FCCU register instance
 * \return CONFIG FSM timeout threshold
 */
__attribute__((always_inline)) static inline uint8_t FccuReg_GetCfgTO(const FccuRegType *obj)
{
    return ((obj->CFG_TO & FCCU_CFG_TO_CFG_TO_MASK) >> FCCU_CFG_TO_CFG_TO_SHIFT);
}

/*! \brief Sets the CONFIG FSM timeout threshold
 *
 * This function sets the CONFIG FSM timeout threshold.
 * The threshold is 2^(CFGTO+13)
 *
 * \param[in] obj : pointer to FCCU register instance
 * \param[in] value : the value of CONFIG FSM timeout threshold
 */
__attribute__((always_inline)) static inline void FccuReg_SetCfgTO(FccuRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CFG_TO;

    tmp &= ~FCCU_CFG_TO_CFG_TO_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << FCCU_CFG_TO_CFG_TO_SHIFT)) & FCCU_CFG_TO_CFG_TO_MASK);
    obj->CFG_TO = tmp;
}

/*! \brief Gets the channel's status
 *
 * This function gets the channel's status.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \return the value of channel's status
 *                    - 0b : fault recovery
 *                    - 1b : fault exist
 */
__attribute__((always_inline)) static inline uint32_t FccuReg_GetFst(FccuRegType *obj)
{
    return obj->FST;
}


/*! \brief Sets the channel's status
 *
 * This function sets the channel's status.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \param[in] value : the value of channel's status
 *                    - 0b : fault recovery
 *                    - 1b : fault exist
 */
__attribute__((always_inline)) static inline void FccuReg_SetFst(FccuRegType *obj, uint32_t value)
{
    obj->FST = value;
}

/*! \brief Sets the FST lock/unlock key
 *
 * This function sets the FST lock/unlock key.
 * FST recovery should be after FSTK cfg, otherwise it will be lock again.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \param[in] value : the value of FST lock/unlock key
 *                    - 0x66EA_ABF3: unlock
 *                    - others : lock
 */
__attribute__((always_inline)) static inline void FccuReg_SetFstKey(FccuRegType *obj, uint32_t value)
{
    obj->FSTK = value;
}

/*! \brief Gets the configuration register lock status
 *
 * This function gets the current configuration register lock status.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \return configuration register lock status
 *         - 0b : unlock
 *         - 1b : lock
 */
__attribute__((always_inline)) static inline uint8_t FccuReg_GetStCfgRegLock(const FccuRegType *obj)
{
    return ((obj->STAT & FCCU_ST_CFG_REG_LOCK_MASK) >> FCCU_ST_CFG_REG_LOCK_SHIFT);
}

/*! \brief Gets the error input from PAD
 *
 * This function gets the current error input from PAD.
 * active low
 *
 * \param[in] obj : pointer to FCCU register instance
 * \return error input from PAD
 *         - 0b : error
 *         - 1b : normal
 */
__attribute__((always_inline)) static inline uint8_t FccuReg_GetStErrIn(const FccuRegType *obj)
{
    return ((obj->STAT & FCCU_ST_ERR_IN_MASK) >> FCCU_ST_ERR_IN_SHIFT);
}

/*! \brief Gets the FCCU FSM status
 *
 * This function gets the current FCCU FSM status.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \return FCCU FSM status
 *         - 0h : NORMAL
 *         - 1h : CONFIG
 *         - 2h : ALARM
 *         - 3h : FAULT
 */
__attribute__((always_inline)) static inline uint8_t FccuReg_GetStFsm(const FccuRegType *obj)
{
    return ((obj->STAT & FCCU_ST_FSM_MASK) >> FCCU_ST_FSM_SHIFT);
}

/*! \brief Gets the Fake fault
 *
 * This function gets the current Fake fault.
 * Insert fault for each channe
 *
 * \param[in] obj : pointer to FCCU register instance
 * \return Fake fault
 */
__attribute__((always_inline)) static inline uint32_t FccuReg_GetFakeFault(const FccuRegType *obj)
{
    return ((obj->FAKE & FCCU_FAKE_FAULT_FAKE_MASK) >> FCCU_FAKE_FAULT_FAKE_SHIFT);
}

/*! \brief Sets the Fake fault
 *
 * This function sets the Fake fault.
 * Insert fault for each channe
 *
 * \param[in] obj : pointer to FCCU register instance
 * \param[in] value : the value of Fake fault
 */
__attribute__((always_inline)) static inline void FccuReg_SetFakeFault(FccuRegType *obj, uint32_t value)
{
    uint32_t tmp = obj->FAKE;

    tmp &= ~FCCU_FAKE_FAULT_FAKE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << FCCU_FAKE_FAULT_FAKE_SHIFT)) & FCCU_FAKE_FAULT_FAKE_MASK);
    obj->FAKE = tmp;
}

/*! \brief Gets the Normal-to-Alarm Freeze Status
 *
 * This function gets the current Normal-to-Alarm Freeze Status.
 * Each bit shows the corresponding channel status.
 * This register shows the first reason which caused the FSM from ALARM to FAULT after clearing the freeze status.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \return Normal-to-Alarm Freeze Status
 *         - 0000_0000h : state after clearing freeze status
 *         - 0000_0001h : channel 0
 *         - 0000_0002h : channel 1
 *         - 0000_0003h : channel 0 and channel 1
 *         -  ...
 *         - FFFF_FFFFh : all channels
 */
__attribute__((always_inline)) static inline uint32_t FccuReg_GetDbgSt1N2ASrc(const FccuRegType *obj)
{
    return ((obj->DBG_ST1 & FCCU_DBG_ST1_N2A_SRC_MASK) >> FCCU_DBG_ST1_N2A_SRC_SHIFT);
}

/*! \brief Gets the Alarm-to-Fault Freeze Status
 *
 * This function gets the current Alarm-to-Fault Freeze Status.
 * Each bit shows the corresponding channel status.
 * This register shows the first reason which caused the FSM from ALARM to FAULT after clearing the freeze status.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \return Alarm-to-Fault Freeze Status
 *         - 0000_0000h : state after clearing freeze status
 *         - 0000_0001h : channel 0
 *         - 0000_0002h : channel 1
 *         - 0000_0003h : channel 0 and channel 1
 *         -  ...
 *         - FFFF_FFFFh : all channels
 */
__attribute__((always_inline)) static inline uint32_t FccuReg_GetDbgSt2A2FSrc0(const FccuRegType *obj)
{
    return ((obj->DBG_ST2 & FCCU_DBG_ST2_A2F_SRC0_MASK) >> FCCU_DBG_ST2_A2F_SRC0_SHIFT);
}

/*! \brief Gets the Alarm-to-Fault Freeze Status
 *
 * This function gets the current Alarm-to-Fault Freeze Status.
 * Each bit shows the corresponding channel status.
 * This register shows the first reason which caused the FSM from ALARM to FAULT after clearing the freeze status.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \return Alarm-to-Fault Freeze Status
 *         - 0000_0000h : state after clearing freeze status
 *         - 0000_0001h : channel 0
 *         - 0000_0002h : channel 1
 *         - 0000_0003h : channel 0 and channel 1
 *         -  ...
 *         - FFFF_FFFFh : all channels
 */
__attribute__((always_inline)) static inline uint32_t FccuReg_GetDbgSt3A2FSrc1(const FccuRegType *obj)
{
    return ((obj->DBG_ST3 & FCCU_DBG_ST3_A2F_SRC1_MASK) >> FCCU_DBG_ST3_A2F_SRC1_SHIFT);
}

/*! \brief Gets the Normal-to-Fault Freeze Status
 *
 * This function gets the current Normal-to-Fault Freeze Status.
 * Each bit shows the corresponding channel status.
 * This register shows the first reason which caused the FSM from NORMAL to FAULT after clearing the freeze status.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \return Normal-to-Fault Freeze Status
 *         - 0000_0000h : state after clearing freeze status
 *         - 0000_0001h : channel 0
 *         - 0000_0002h : channel 1
 *         - 0000_0003h : channel 0 and channel 1
 *         -  ...
 *         - FFFF_FFFFh : all channels
 */
__attribute__((always_inline)) static inline uint32_t FccuReg_GetDbgSt4N2FSrc(const FccuRegType *obj)
{
    return ((obj->DBG_ST4 & FCCU_DBG_ST4_N2F_SRC_MASK) >> FCCU_DBG_ST4_N2F_SRC_SHIFT);
}

/*! \brief Gets the Normal-to-ALARM Freeze Status
 *
 * This function gets the current Normal-to-ALARM Freeze Status.
 * Each bit shows the corresponding channel status.
 * This register shows the first reason which caused the FSM from NORMAL to ALARM after clearing the freeze status.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \return Normal-to-ALARM Freeze Status
 *         - 0000_0000h : state after clearing freeze status
 *         - 0000_0001h : channel 0
 *         - 0000_0002h : channel 1
 *         - 0000_0003h : channel 0 and channel 1
 *         -  ...
 *         - FFFF_FFFFh : all channels
 */
__attribute__((always_inline)) static inline uint32_t FccuReg_GetDbgSt5F2ASrc(const FccuRegType *obj)
{
    return ((obj->DBG_ST5 & FCCU_DBG_ST5_F2A_SRC_MASK) >> FCCU_DBG_ST5_F2A_SRC_SHIFT);
}

/*! \brief Gets the NMI interrupt in Fault FSM
 *
 * This function gets the current NMI interrupt in Fault FSM.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \return NMI interrupt in Fault FSM
 *         - 0b : no interrupt
 *         - 1b : interrupt exist
 */
__attribute__((always_inline)) static inline uint8_t FccuReg_GetIrqStNmi(const FccuRegType *obj)
{
    return ((obj->IRQ_ST & FCCU_IRQ_ST_NMI_MASK) >> FCCU_IRQ_ST_NMI_SHIFT);
}

/*! \brief Gets the CFG FSM timeout interrupt status
 *
 * This function gets the CFG FSM timeout interrupt status.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \return the value of CFG FSM timeout interrupt status
 *                    - 0b : no interrupt
 *                    - 1b : interrupt exist
 */
__attribute__((always_inline)) static inline uint8_t FccuReg_GetIrqStCfgTO(FccuRegType *obj)
{
    return ((obj->IRQ_ST & FCCU_IRQ_ST_CFG_TO_MASK) >> FCCU_IRQ_ST_CFG_TO_SHIFT);
}

/*! \brief Gets the ALARM FSM interrupt status
 *
 * This function gets the ALARM FSM interrupt status.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \return the value of ALARM FSM interrupt status
 *                    - 0b : no interrupt
 *                    - 1b : interrupt exist
 */
__attribute__((always_inline)) static inline uint8_t FccuReg_GetIrqStAlarm(FccuRegType *obj)
{
    return ((obj->IRQ_ST & FCCU_IRQ_ST_ALARM_MASK) >> FCCU_IRQ_ST_ALARM_SHIFT);
}

/*! \brief Sets the ALARM FSM interrupt status
 *
 * This function sets the ALARM FSM interrupt status.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \param[in] value : the value of ALARM FSM interrupt status
 *                    - 0b : no interrupt
 *                    - 1b : interrupt exist
 */
__attribute__((always_inline)) static inline void FccuReg_SetIrqStAlarm(FccuRegType *obj, uint8_t value)
{
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    obj->IRQ_ST = (((uint32_t)(((uint32_t)(value)) << FCCU_IRQ_ST_ALARM_SHIFT)) & FCCU_IRQ_ST_ALARM_MASK);
    (void)obj->IRQ_ST;
}

/*! \brief Sets the CFG FSM timeout interrupt status
 *
 * This function sets the CFG FSM timeout interrupt status.
 *
 * \param[in] obj : pointer to FCCU register instance
 * \param[in] value : the value of CFG FSM timeout interrupt status
 *                    - 0b : no interrupt
 *                    - 1b : interrupt exist
 */
__attribute__((always_inline)) static inline void FccuReg_SetIrqStCfgTO(FccuRegType *obj, uint8_t value)
{
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    obj->IRQ_ST = (((uint32_t)(((uint32_t)(value)) << FCCU_IRQ_ST_CFG_TO_SHIFT)) & FCCU_IRQ_ST_CFG_TO_MASK);
    (void)obj->IRQ_ST;
}

/*! \brief Gets the ALARM state timer register
 *
 * This function gets the current ALARM state timer register.
 * CONFIG FSM : 0
 * NORMAL FSM : 0x3A980
 * ALARM FSM : real value
 * FAULT FSM : keep the latched value from last FSM
 *
 * \param[in] obj : pointer to FCCU register instance
 * \return ALARM state timer register
 */
__attribute__((always_inline)) static inline uint32_t FccuReg_GetTmrAlarmCnt(const FccuRegType *obj)
{
    return ((obj->TMR_ALARM & FCCU_TMR_ALARM_CNT_MASK) >> FCCU_TMR_ALARM_CNT_SHIFT);
}

/*! \brief Gets the CONFIG state timer register
 *
 * This function gets the current CONFIG state timer register.
 * CONFIG FSM : real value
 * other FSM : 0xF_FFFF
 *
 * \param[in] obj : pointer to FCCU register instance
 * \return CONFIG state timer register
 */
__attribute__((always_inline)) static inline uint32_t FccuReg_GetTmrCfgCnt(const FccuRegType *obj)
{
    return ((obj->TMR_CFG & FCCU_TMR_CFG_CNT_MASK) >> FCCU_TMR_CFG_CNT_SHIFT);
}

/*! \brief Gets the EOUT timer register
 *
 * This function gets the current EOUT timer register.
 * FAULT FSM : real value
 * other FSM : 0
 *
 * \param[in] obj : pointer to FCCU register instance
 * \return EOUT timer register
 */
__attribute__((always_inline)) static inline uint32_t FccuReg_GetTmrEOutCnt(const FccuRegType *obj)
{
    return ((obj->TMR_EOUT & FCCU_TMR_EOUT_CNT_MASK) >> FCCU_TMR_EOUT_CNT_SHIFT);
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _FCCU_REG_H_ */
