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

#ifndef _RCM_REG_H_
#define _RCM_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the RCM Registers
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

/* EXTRST Bit Fields */
#define RCM_EXTRST_FLT_LEN_MASK         (0x1F00u)
#define RCM_EXTRST_FLT_LEN_SHIFT        (8u)
#define RCM_EXTRST_FLT_LEN_WIDTH        (5u)
#define RCM_EXTRST_FLT_EN_MASK          (0x01u)
#define RCM_EXTRST_FLT_EN_SHIFT         (0u)
#define RCM_EXTRST_FLT_EN_WIDTH         (1u)

/* RST_FLAG Bit Fields */
#define RCM_RST_FLAG_POR_RST_MASK       (0x2000u)
#define RCM_RST_FLAG_POR_RST_SHIFT      (13u)
#define RCM_RST_FLAG_POR_RST_WIDTH      (1u)
#define RCM_RST_FLAG_LVR_RST_MASK       (0x1000u)
#define RCM_RST_FLAG_LVR_RST_SHIFT      (12u)
#define RCM_RST_FLAG_LVR_RST_WIDTH      (1u)
#define RCM_RST_FLAG_FLS_INITIAL_MASK   (0x800u)
#define RCM_RST_FLAG_FLS_INITIAL_SHIFT  (11u)
#define RCM_RST_FLAG_FLS_INITIAL_WIDTH  (1u)
#define RCM_RST_FLAG_STDBY_EXIT_MASK    (0x400u)
#define RCM_RST_FLAG_STDBY_EXIT_SHIFT   (10u)
#define RCM_RST_FLAG_STDBY_EXIT_WIDTH   (1u)
#define RCM_RST_FLAG_FCCU_RESET_MASK    (0x200u)
#define RCM_RST_FLAG_FCCU_RESET_SHIFT   (9u)
#define RCM_RST_FLAG_FCCU_RESET_WIDTH   (1u)
#define RCM_RST_FLAG_CMU_SOSC_MASK      (0x100u)
#define RCM_RST_FLAG_CMU_SOSC_SHIFT     (8u)
#define RCM_RST_FLAG_CMU_SOSC_WIDTH     (1u)
#define RCM_RST_FLAG_CMU_PLL_MASK       (0x80u)
#define RCM_RST_FLAG_CMU_PLL_SHIFT      (7u)
#define RCM_RST_FLAG_CMU_PLL_WIDTH      (1u)
#define RCM_RST_FLAG_CMU_FIRC_MASK      (0x40u)
#define RCM_RST_FLAG_CMU_FIRC_SHIFT     (6u)
#define RCM_RST_FLAG_CMU_FIRC_WIDTH     (1u)
#define RCM_RST_FLAG_PLL_LOSS_MASK      (0x20u)
#define RCM_RST_FLAG_PLL_LOSS_SHIFT     (5u)
#define RCM_RST_FLAG_PLL_LOSS_WIDTH     (1u)
#define RCM_RST_FLAG_MDMAP_RST_MASK     (0x10u)
#define RCM_RST_FLAG_MDMAP_RST_SHIFT    (4u)
#define RCM_RST_FLAG_MDMAP_RST_WIDTH    (1u)
#define RCM_RST_FLAG_PIN_RST_MASK       (0x08u)
#define RCM_RST_FLAG_PIN_RST_SHIFT      (3u)
#define RCM_RST_FLAG_PIN_RST_WIDTH      (1u)
#define RCM_RST_FLAG_LOCKUP_RST_MASK    (0x04u)
#define RCM_RST_FLAG_LOCKUP_RST_SHIFT   (2u)
#define RCM_RST_FLAG_LOCKUP_RST_WIDTH   (1u)
#define RCM_RST_FLAG_SYS_RST_MASK       (0x02u)
#define RCM_RST_FLAG_SYS_RST_SHIFT      (1u)
#define RCM_RST_FLAG_SYS_RST_WIDTH      (1u)
#define RCM_RST_FLAG_WDG_RST_MASK       (0x01u)
#define RCM_RST_FLAG_WDG_RST_SHIFT      (0u)
#define RCM_RST_FLAG_WDG_RST_WIDTH      (1u)

/* RST_SFLAG Bit Fields */
#define RCM_RST_SFLAG_POR_RST_MASK      (0x2000u)
#define RCM_RST_SFLAG_POR_RST_SHIFT     (13u)
#define RCM_RST_SFLAG_POR_RST_WIDTH     (1u)
#define RCM_RST_SFLAG_LVR_RST_MASK      (0x1000u)
#define RCM_RST_SFLAG_LVR_RST_SHIFT     (12u)
#define RCM_RST_SFLAG_LVR_RST_WIDTH     (1u)
#define RCM_RST_SFLAG_FLS_INITIAL_MASK  (0x800u)
#define RCM_RST_SFLAG_FLS_INITIAL_SHIFT (11u)
#define RCM_RST_SFLAG_FLS_INITIAL_WIDTH (1u)
#define RCM_RST_SFLAG_STDBY_EXIT_MASK   (0x400u)
#define RCM_RST_SFLAG_STDBY_EXIT_SHIFT  (10u)
#define RCM_RST_SFLAG_STDBY_EXIT_WIDTH  (1u)
#define RCM_RST_SFLAG_FCCU_RESET_MASK   (0x200u)
#define RCM_RST_SFLAG_FCCU_RESET_SHIFT  (9u)
#define RCM_RST_SFLAG_FCCU_RESET_WIDTH  (1u)
#define RCM_RST_SFLAG_CMU_SOSC_MASK     (0x100u)
#define RCM_RST_SFLAG_CMU_SOSC_SHIFT    (8u)
#define RCM_RST_SFLAG_CMU_SOSC_WIDTH    (1u)
#define RCM_RST_SFLAG_CMU_PLL_MASK      (0x80u)
#define RCM_RST_SFLAG_CMU_PLL_SHIFT     (7u)
#define RCM_RST_SFLAG_CMU_PLL_WIDTH     (1u)
#define RCM_RST_SFLAG_CMU_FIRC_MASK     (0x40u)
#define RCM_RST_SFLAG_CMU_FIRC_SHIFT    (6u)
#define RCM_RST_SFLAG_CMU_FIRC_WIDTH    (1u)
#define RCM_RST_SFLAG_PLL_LOSS_MASK     (0x20u)
#define RCM_RST_SFLAG_PLL_LOSS_SHIFT    (5u)
#define RCM_RST_SFLAG_PLL_LOSS_WIDTH    (1u)
#define RCM_RST_SFLAG_MDMAP_RST_MASK    (0x10u)
#define RCM_RST_SFLAG_MDMAP_RST_SHIFT   (4u)
#define RCM_RST_SFLAG_MDMAP_RST_WIDTH   (1u)
#define RCM_RST_SFLAG_PIN_RST_MASK      (0x08u)
#define RCM_RST_SFLAG_PIN_RST_SHIFT     (3u)
#define RCM_RST_SFLAG_PIN_RST_WIDTH     (1u)
#define RCM_RST_SFLAG_LOCKUP_RST_MASK   (0x04u)
#define RCM_RST_SFLAG_LOCKUP_RST_SHIFT  (2u)
#define RCM_RST_SFLAG_LOCKUP_RST_WIDTH  (1u)
#define RCM_RST_SFLAG_SYS_RST_MASK      (0x02u)
#define RCM_RST_SFLAG_SYS_RST_SHIFT     (1u)
#define RCM_RST_SFLAG_SYS_RST_WIDTH     (1u)
#define RCM_RST_SFLAG_WDG_RST_MASK      (0x01u)
#define RCM_RST_SFLAG_WDG_RST_SHIFT     (0u)
#define RCM_RST_SFLAG_WDG_RST_WIDTH     (1u)

/* RST_CTRL Bit Fields */
#define RCM_RST_CTRL_LOCKUP_EN_MASK     (0x20000u)
#define RCM_RST_CTRL_LOCKUP_EN_SHIFT    (17u)
#define RCM_RST_CTRL_LOCKUP_EN_WIDTH    (1u)
#define RCM_RST_CTRL_PLL_LOSS_EN_MASK   (0x10000u)
#define RCM_RST_CTRL_PLL_LOSS_EN_SHIFT  (16u)
#define RCM_RST_CTRL_PLL_LOSS_EN_WIDTH  (1u)
#define RCM_RST_CTRL_CMU_SOSC_IE_MASK   (0x1000u)
#define RCM_RST_CTRL_CMU_SOSC_IE_SHIFT  (12u)
#define RCM_RST_CTRL_CMU_SOSC_IE_WIDTH  (1u)
#define RCM_RST_CTRL_CMU_PLL_IE_MASK    (0x800u)
#define RCM_RST_CTRL_CMU_PLL_IE_SHIFT   (11u)
#define RCM_RST_CTRL_CMU_PLL_IE_WIDTH   (1u)
#define RCM_RST_CTRL_CMU_FIRC_IE_MASK   (0x400u)
#define RCM_RST_CTRL_CMU_FIRC_IE_SHIFT  (10u)
#define RCM_RST_CTRL_CMU_FIRC_IE_WIDTH  (1u)
#define RCM_RST_CTRL_PLL_LOSS_IE_MASK   (0x200u)
#define RCM_RST_CTRL_PLL_LOSS_IE_SHIFT  (9u)
#define RCM_RST_CTRL_PLL_LOSS_IE_WIDTH  (1u)
#define RCM_RST_CTRL_MDMAP_RST_IE_MASK  (0x100u)
#define RCM_RST_CTRL_MDMAP_RST_IE_SHIFT (8u)
#define RCM_RST_CTRL_MDMAP_RST_IE_WIDTH (1u)
#define RCM_RST_CTRL_PIN_RST_IE_MASK    (0x80u)
#define RCM_RST_CTRL_PIN_RST_IE_SHIFT   (7u)
#define RCM_RST_CTRL_PIN_RST_IE_WIDTH   (1u)
#define RCM_RST_CTRL_SYS_RST_IE_MASK    (0x20u)
#define RCM_RST_CTRL_SYS_RST_IE_SHIFT   (5u)
#define RCM_RST_CTRL_SYS_RST_IE_WIDTH   (1u)
#define RCM_RST_CTRL_WDG_RST_IE_MASK    (0x10u)
#define RCM_RST_CTRL_WDG_RST_IE_SHIFT   (4u)
#define RCM_RST_CTRL_WDG_RST_IE_WIDTH   (1u)
#define RCM_RST_CTRL_GLOBAL_IE_MASK     (0x04u)
#define RCM_RST_CTRL_GLOBAL_IE_SHIFT    (2u)
#define RCM_RST_CTRL_GLOBAL_IE_WIDTH    (1u)
#define RCM_RST_CTRL_RST_DELAY_MASK     (0x03u)
#define RCM_RST_CTRL_RST_DELAY_SHIFT    (0u)
#define RCM_RST_CTRL_RST_DELAY_WIDTH    (2u)

/* RST_IRQ Bit Fields */
#define RCM_RST_IRQ_CMU_SOSC_MASK       (0x1000u)
#define RCM_RST_IRQ_CMU_SOSC_SHIFT      (12u)
#define RCM_RST_IRQ_CMU_SOSC_WIDTH      (1u)
#define RCM_RST_IRQ_CMU_PLL_MASK        (0x800u)
#define RCM_RST_IRQ_CMU_PLL_SHIFT       (11u)
#define RCM_RST_IRQ_CMU_PLL_WIDTH       (1u)
#define RCM_RST_IRQ_CMU_FIRC_MASK       (0x400u)
#define RCM_RST_IRQ_CMU_FIRC_SHIFT      (10u)
#define RCM_RST_IRQ_CMU_FIRC_WIDTH      (1u)
#define RCM_RST_IRQ_PLL_LOSS_MASK       (0x200u)
#define RCM_RST_IRQ_PLL_LOSS_SHIFT      (9u)
#define RCM_RST_IRQ_PLL_LOSS_WIDTH      (1u)
#define RCM_RST_IRQ_MDMAP_MASK          (0x100u)
#define RCM_RST_IRQ_MDMAP_SHIFT         (8u)
#define RCM_RST_IRQ_MDMAP_WIDTH         (1u)
#define RCM_RST_IRQ_PIN_MASK            (0x80u)
#define RCM_RST_IRQ_PIN_SHIFT           (7u)
#define RCM_RST_IRQ_PIN_WIDTH           (1u)
#define RCM_RST_IRQ_SYS_MASK            (0x20u)
#define RCM_RST_IRQ_SYS_SHIFT           (5u)
#define RCM_RST_IRQ_SYS_WIDTH           (1u)
#define RCM_RST_IRQ_WDG_MASK            (0x10u)
#define RCM_RST_IRQ_WDG_SHIFT           (4u)
#define RCM_RST_IRQ_WDG_WIDTH           (1u)

/* LOCK Bit Fields */
#define RCM_LOCK_KEY_MASK               (0xFFFFFFFFu)
#define RCM_LOCK_KEY_SHIFT              (0u)
#define RCM_LOCK_KEY_WIDTH              (32u)

/* LOCK_ST Bit Fields */
#define RCM_LOCK_ST_LOCK_MASK           (0x01u)
#define RCM_LOCK_ST_LOCK_SHIFT          (0u)
#define RCM_LOCK_ST_LOCK_WIDTH          (1u)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief The definition of RCM registers
 */
typedef struct _RcmRegType_
{
    volatile uint32_t       EXTRST;        /*!< External reset register, offset: 0x0 */
    const volatile uint32_t RST_FLAG;      /*!< Recent reset flag, offset: 0x4 */
    volatile uint32_t       RST_SFLAG;     /*!< Sticky reset flag, offset: 0x8 */
    volatile uint32_t       RST_CTRL;      /*!< Reset control register, offset: 0xC */
    volatile uint32_t       RST_IRQ;       /*!< Reset interrupt status register, offset: 0x10 */
    uint32_t                RESERVED0[27]; /*!< Reserved register, offset: 0x14 */
    volatile uint32_t       LOCK;          /*!< RCM lock/unlock register, offset: 0x80 */
    const volatile uint32_t LOCK_ST;       /*!< RCM unlock/lock flag, offset: 0x84 */
} RcmRegType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Gets the external reset input digital filter length
 *
 * This function gets the external reset input digital filter length
 *
 * \param[in] obj : pointer to RCM register instance
 * \return external reset input digital filter length
 *         - 00h : 1
 *         - 01h : 2
 *         - 02h : 3
 *            .
 *            .
 *            .
 *         - 1Fh : 32
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetExtRstFltLen(const RcmRegType *obj)
{
    return ((obj->EXTRST & RCM_EXTRST_FLT_LEN_MASK) >> RCM_EXTRST_FLT_LEN_SHIFT);
}

/*! \brief Sets the external reset input digital filter length
 *
 * This function sets the external reset input digital filter length
 *
 * \param[in] obj : pointer to RCM register instance
 * \param[in] value : the value of external reset input digital filter length
 *                    - 00h : 1
 *                    - 01h : 2
 *                    - 02h : 3
 *                       .
 *                       .
 *                       .
 *                    - 1Fh : 32
 */
__attribute__((always_inline)) static inline void RcmReg_SetExtRstFltLen(RcmRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->EXTRST;

    tmp &= ~RCM_EXTRST_FLT_LEN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RCM_EXTRST_FLT_LEN_SHIFT)) & RCM_EXTRST_FLT_LEN_MASK);
    obj->EXTRST = tmp;
}

/*! \brief Gets the external reset input digital filter enable
 *
 * Reset by Chip Por only
 *
 * \param[in] obj : pointer to RCM register instance
 * \return external reset input digital filter enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetExtRstFltEn(const RcmRegType *obj)
{
    return ((obj->EXTRST & RCM_EXTRST_FLT_EN_MASK) >> RCM_EXTRST_FLT_EN_SHIFT);
}

/*! \brief Sets the external reset input digital filter enable
 *
 * Reset by Chip Por only
 *
 * \param[in] obj : pointer to RCM register instance
 * \param[in] value : the value of external reset input digital filter enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void RcmReg_SetExtRstFltEn(RcmRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->EXTRST;

    tmp &= ~RCM_EXTRST_FLT_EN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RCM_EXTRST_FLT_EN_SHIFT)) & RCM_EXTRST_FLT_EN_MASK);
    obj->EXTRST = tmp;
}

/*! \brief Gets the power up reset flag
 *
 * Indicates a reset has been caused by power up reset.
 *
 * \param[in] obj : pointer to RCM register instance
 * \return power up reset flag
 *         - 0b : Reset not caused by power up reset
 *         - 1b : Reset caused by power up reset
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstFlagPorRst(const RcmRegType *obj)
{
    return ((obj->RST_FLAG & RCM_RST_FLAG_POR_RST_MASK) >> RCM_RST_FLAG_POR_RST_SHIFT);
}

/*! \brief Gets the low power reset flag
 *
 * Indicates a reset has been caused by low power reset.
 *
 * \param[in] obj : pointer to RCM register instance
 * \return low power reset flag
 *         - 0b : Reset not caused by low power reset
 *         - 1b : Reset caused by low power reset
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstFlagLvrRst(const RcmRegType *obj)
{
    return ((obj->RST_FLAG & RCM_RST_FLAG_LVR_RST_MASK) >> RCM_RST_FLAG_LVR_RST_SHIFT);
}

/*! \brief Gets the flash initial reset flag
 *
 * Indicates a reset has been caused by flash initial reset.
 *
 * \param[in] obj : pointer to RCM register instance
 * \return flash initial reset flag
 *         - 0b : Reset not caused by flash initial reset
 *         - 1b : Reset caused by flash initial reset
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstFlagFlsInitial(const RcmRegType *obj)
{
    return ((obj->RST_FLAG & RCM_RST_FLAG_FLS_INITIAL_MASK) >> RCM_RST_FLAG_FLS_INITIAL_SHIFT);
}

/*! \brief Gets the exit standby mode reset flag
 *
 * Indicates a reset has been caused by standby exit reset.
 *
 * \param[in] obj : pointer to RCM register instance
 * \return exit standby mode reset flag
 *         - 0b : Reset not caused by standby exit reset
 *         - 1b : Reset caused by standby exit reset
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstFlagStdbyExit(const RcmRegType *obj)
{
    return ((obj->RST_FLAG & RCM_RST_FLAG_STDBY_EXIT_MASK) >> RCM_RST_FLAG_STDBY_EXIT_SHIFT);
}

/*! \brief Gets the FCCU reset flag
 *
 * Indicates a reset has been caused by FCCU reset.
 *
 * \param[in] obj : pointer to RCM register instance
 * \return FCCU reset flag
 *         - 0b : Reset not caused by FCCU reset
 *         - 1b : Reset caused by FCCU reset
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstFlagFccuReset(const RcmRegType *obj)
{
    return ((obj->RST_FLAG & RCM_RST_FLAG_FCCU_RESET_MASK) >> RCM_RST_FLAG_FCCU_RESET_SHIFT);
}

/*! \brief Gets the SOSC clock monitor reset flag
 *
 * Indicates a reset has been caused by CMU SOSC reset.
 *
 * \param[in] obj : pointer to RCM register instance
 * \return SOSC clock monitor reset flag
 *         - 0b : Reset not caused by CMU SOSC reset
 *         - 1b : Reset caused by CMU SOSC reset
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstFlagCmuSosc(const RcmRegType *obj)
{
    return ((obj->RST_FLAG & RCM_RST_FLAG_CMU_SOSC_MASK) >> RCM_RST_FLAG_CMU_SOSC_SHIFT);
}

/*! \brief Gets the PLL clock monitor reset flag
 *
 * Indicates a reset has been caused by CMU PLL reset.
 *
 * \param[in] obj : pointer to RCM register instance
 * \return PLL clock monitor reset flag
 *         - 0b : Reset not caused by CMU PLL reset
 *         - 1b : Reset caused by CMU PLL reset
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstFlagCmuPll(const RcmRegType *obj)
{
    return ((obj->RST_FLAG & RCM_RST_FLAG_CMU_PLL_MASK) >> RCM_RST_FLAG_CMU_PLL_SHIFT);
}

/*! \brief Gets the FIRC clock monitor reset flag
 *
 * Indicates a reset has been caused by CMU FIRC reset.
 *
 * \param[in] obj : pointer to RCM register instance
 * \return FIRC clock monitor reset flag
 *         - 0b : Reset not caused by CMU FIRC reset
 *         - 1b : Reset caused by CMU FIRC reset
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstFlagCmuFirc(const RcmRegType *obj)
{
    return ((obj->RST_FLAG & RCM_RST_FLAG_CMU_FIRC_MASK) >> RCM_RST_FLAG_CMU_FIRC_SHIFT);
}

/*! \brief Gets the PLL lock loss reset flag
 *
 * Indicates a reset has been caused by PLL loss lock reset.
 *
 * \param[in] obj : pointer to RCM register instance
 * \return PLL lock loss reset flag
 *         - 0b : Reset not caused by PLL lock loss reset
 *         - 1b : Reset caused by PLL lock loss reset
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstFlagPllLoss(const RcmRegType *obj)
{
    return ((obj->RST_FLAG & RCM_RST_FLAG_PLL_LOSS_MASK) >> RCM_RST_FLAG_PLL_LOSS_SHIFT);
}

/*! \brief Gets the MDMAP reset flag
 *
 * Indicates a reset has been caused by MDMAP system reset.
 *
 * \param[in] obj : pointer to RCM register instance
 * \return MDMAP reset flag
 *         - 0b : Reset not caused by MDMAP system reset
 *         - 1b : Reset caused by MDMAP system reset
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstFlagMdmApRst(const RcmRegType *obj)
{
    return ((obj->RST_FLAG & RCM_RST_FLAG_MDMAP_RST_MASK) >> RCM_RST_FLAG_MDMAP_RST_SHIFT);
}

/*! \brief Gets the External PIN reset flag
 *
 * Indicates a reset has been caused by an active-low level on the external RESET (RESET_b) pin.
 *
 * \param[in] obj : pointer to RCM register instance
 * \return External PIN reset flag
 *         - 0b : Reset not caused by external reset pin
 *         - 1b : Reset caused by external reset pin
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstFlagPinRst(const RcmRegType *obj)
{
    return ((obj->RST_FLAG & RCM_RST_FLAG_PIN_RST_MASK) >> RCM_RST_FLAG_PIN_RST_SHIFT);
}

/*! \brief Gets the Core Lockup reset flag
 *
 * Indicates a reset has been caused by the Arm core indication of a LOCKUP event.
 *
 * \param[in] obj : pointer to RCM register instance
 * \return Core Lockup reset flag
 *         - 0b : Reset not caused by core LOCKUP event
 *         - 1b : Reset caused by core LOCKUP event
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstFlagLockupRst(const RcmRegType *obj)
{
    return ((obj->RST_FLAG & RCM_RST_FLAG_LOCKUP_RST_MASK) >> RCM_RST_FLAG_LOCKUP_RST_SHIFT);
}

/*! \brief Gets the CPU Software reset flag
 *
 * Indicates a reset has been caused by software setting of SYSRESETREQ bit in Application Interrupt and Reset Control Register in the Arm core.
 *
 * \param[in] obj : pointer to RCM register instance
 * \return CPU Software reset flag
 *         - 0b : Reset not caused by software setting of SYSRESETREQ bit
 *         - 1b : Reset caused by software setting of SYSRESETREQ bit
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstFlagSysRst(const RcmRegType *obj)
{
    return ((obj->RST_FLAG & RCM_RST_FLAG_SYS_RST_MASK) >> RCM_RST_FLAG_SYS_RST_SHIFT);
}

/*! \brief Gets the Watchdog reset flag
 *
 * Indicates a reset has been caused by the watchdog timer timing out. This reset source can be blocked by
disabling the watchdog.
 *
 * \param[in] obj : pointer to RCM register instance
 * \return Watchdog reset flag
 *         - 0b : Reset not caused by watchdog timeout
 *         - 1b : Reset caused by watchdog timeout
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstFlagWdgRst(const RcmRegType *obj)
{
    return ((obj->RST_FLAG & RCM_RST_FLAG_WDG_RST_MASK) >> RCM_RST_FLAG_WDG_RST_SHIFT);
}

/*! \brief Gets the Sticky power up reset flag
 *
 * Indicates a reset has been caused by power up reset.
 *
 * \param[in] obj : pointer to RCM register instance
 * \return Sticky power up reset flag
 *         - 0b : Reset not caused by power up reset
 *         - 1b : Reset caused by power up reset
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstSFlagPorRst(const RcmRegType *obj)
{
    return ((obj->RST_SFLAG & RCM_RST_SFLAG_POR_RST_MASK) >> RCM_RST_SFLAG_POR_RST_SHIFT);
}

/*! \brief Sets the Sticky power up reset flag
 *
 * Indicates a reset has been caused by power up reset.
 *
 * \param[in] obj : pointer to RCM register instance
 * \param[in] value : the value of Sticky power up reset flag
 *                    - 0b : no effect
 *                    - 1b : clear the flag
 */
__attribute__((always_inline)) static inline void RcmReg_SetRstSFlagPorRst(RcmRegType *obj, uint8_t value)
{
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    uint32_t tmp = 0;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RCM_RST_SFLAG_POR_RST_SHIFT)) & RCM_RST_SFLAG_POR_RST_MASK);
    obj->RST_SFLAG = tmp;
}

/*! \brief Gets the Sticky low power reset flag
 *
 * Indicates a reset has been caused by low power reset.
 *
 * \param[in] obj : pointer to RCM register instance
 * \return Sticky low power reset flag
 *         - 0b : Reset not caused by low power reset
 *         - 1b : Reset caused by low power reset
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstSFlagLvrRst(const RcmRegType *obj)
{
    return ((obj->RST_SFLAG & RCM_RST_SFLAG_LVR_RST_MASK) >> RCM_RST_SFLAG_LVR_RST_SHIFT);
}

/*! \brief Sets the Sticky low power reset flag
 *
 * Indicates a reset has been caused by low power reset.
 *
 * \param[in] obj : pointer to RCM register instance
 * \param[in] value : the value of Sticky low power reset flag
 *                    - 0b : no effect
 *                    - 1b : clear the flag
 */
__attribute__((always_inline)) static inline void RcmReg_SetRstSFlagLvrRst(RcmRegType *obj, uint8_t value)
{
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    uint32_t tmp = 0;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RCM_RST_SFLAG_LVR_RST_SHIFT)) & RCM_RST_SFLAG_LVR_RST_MASK);
    obj->RST_SFLAG = tmp;
}

/*! \brief Gets the Sticky flash initial reset flag
 *
 * Indicates a reset has been caused by flash initial reset.
 *
 * \param[in] obj : pointer to RCM register instance
 * \return Sticky flash initial reset flag
 *         - 0b : Reset not caused by flash initial reset
 *         - 1b : Reset caused by flash initial reset
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstSFlagFlsInitial(const RcmRegType *obj)
{
    return ((obj->RST_SFLAG & RCM_RST_SFLAG_FLS_INITIAL_MASK) >> RCM_RST_SFLAG_FLS_INITIAL_SHIFT);
}

/*! \brief Sets the Sticky flash initial reset flag
 *
 * Indicates a reset has been caused by flash initial reset.
 *
 * \param[in] obj : pointer to RCM register instance
 * \param[in] value : the value of Sticky flash initial reset flag
 *                    - 0b : no effect
 *                    - 1b : clear the flag
 */
__attribute__((always_inline)) static inline void RcmReg_SetRstSFlagFlsInitial(RcmRegType *obj, uint8_t value)
{
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    uint32_t tmp = 0;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RCM_RST_SFLAG_FLS_INITIAL_SHIFT)) & RCM_RST_SFLAG_FLS_INITIAL_MASK);
    obj->RST_SFLAG = tmp;
}

/*! \brief Gets the Sticky exit standby mode reset flag
 *
 * Indicates a reset has been caused by standby exit reset.
 *
 * \param[in] obj : pointer to RCM register instance
 * \return Sticky exit standby mode reset flag
 *         - 0b : Reset not caused by standby exit reset
 *         - 1b : Reset caused by standby exit reset
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstSFlagStdbyExit(const RcmRegType *obj)
{
    return ((obj->RST_SFLAG & RCM_RST_SFLAG_STDBY_EXIT_MASK) >> RCM_RST_SFLAG_STDBY_EXIT_SHIFT);
}

/*! \brief Sets the Sticky exit standby mode reset flag
 *
 * Indicates a reset has been caused by standby exit reset.
 *
 * \param[in] obj : pointer to RCM register instance
 * \param[in] value : the value of Sticky exit standby mode reset flag
 *                    - 0b : no effect
 *                    - 1b : clear the flag
 */
__attribute__((always_inline)) static inline void RcmReg_SetRstSFlagStdbyExit(RcmRegType *obj, uint8_t value)
{
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    uint32_t tmp = 0;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RCM_RST_SFLAG_STDBY_EXIT_SHIFT)) & RCM_RST_SFLAG_STDBY_EXIT_MASK);
    obj->RST_SFLAG = tmp;
}

/*! \brief Gets the Sticky FCCU reset flag
 *
 * Indicates a reset has been caused by FCCU reset.
 *
 * \param[in] obj : pointer to RCM register instance
 * \return Sticky FCCU reset flag
 *         - 0b : Reset not caused by FCCU reset
 *         - 1b : Reset caused by FCCU reset
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstSFlagFccuReset(const RcmRegType *obj)
{
    return ((obj->RST_SFLAG & RCM_RST_SFLAG_FCCU_RESET_MASK) >> RCM_RST_SFLAG_FCCU_RESET_SHIFT);
}

/*! \brief Sets the Sticky FCCU reset flag
 *
 * Indicates a reset has been caused by FCCU reset.
 *
 * \param[in] obj : pointer to RCM register instance
 * \param[in] value : the value of Sticky FCCU reset flag
 *                    - 0b : no effect
 *                    - 1b : clear the flag
 */
__attribute__((always_inline)) static inline void RcmReg_SetRstSFlagFccuReset(RcmRegType *obj, uint8_t value)
{
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    uint32_t tmp = 0;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RCM_RST_SFLAG_FCCU_RESET_SHIFT)) & RCM_RST_SFLAG_FCCU_RESET_MASK);
    obj->RST_SFLAG = tmp;
}

/*! \brief Gets the Sticky SOSC clock monitor reset flag
 *
 * Indicates a reset has been caused by CMU SOSC reset.
 *
 * \param[in] obj : pointer to RCM register instance
 * \return Sticky SOSC clock monitor reset flag
 *         - 0b : Reset not caused by CMU SOSC reset
 *         - 1b : Reset caused by CMU SOSC reset
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstSFlagCmuSosc(const RcmRegType *obj)
{
    return ((obj->RST_SFLAG & RCM_RST_SFLAG_CMU_SOSC_MASK) >> RCM_RST_SFLAG_CMU_SOSC_SHIFT);
}

/*! \brief Sets the Sticky SOSC clock monitor reset flag
 *
 * Indicates a reset has been caused by CMU SOSC reset.
 *
 * \param[in] obj : pointer to RCM register instance
 * \param[in] value : the value of Sticky SOSC clock monitor reset flag
 *                    - 0b : no effect
 *                    - 1b : clear the flag
 */
__attribute__((always_inline)) static inline void RcmReg_SetRstSFlagCmuSosc(RcmRegType *obj, uint8_t value)
{
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    uint32_t tmp = 0;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RCM_RST_SFLAG_CMU_SOSC_SHIFT)) & RCM_RST_SFLAG_CMU_SOSC_MASK);
    obj->RST_SFLAG = tmp;
}

/*! \brief Gets the Sticky PLL clock monitor reset flag
 *
 * Indicates a reset has been caused by CMU PLL reset.
 *
 * \param[in] obj : pointer to RCM register instance
 * \return Sticky PLL clock monitor reset flag
 *         - 0b : Reset not caused by CMU PLL reset
 *         - 1b : Reset caused by CMU PLL reset
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstSFlagCmuPll(const RcmRegType *obj)
{
    return ((obj->RST_SFLAG & RCM_RST_SFLAG_CMU_PLL_MASK) >> RCM_RST_SFLAG_CMU_PLL_SHIFT);
}

/*! \brief Sets the Sticky PLL clock monitor reset flag
 *
 * Indicates a reset has been caused by CMU PLL reset.
 *
 * \param[in] obj : pointer to RCM register instance
 * \param[in] value : the value of Sticky PLL clock monitor reset flag
 *                    - 0b : no effect
 *                    - 1b : clear the flag
 */
__attribute__((always_inline)) static inline void RcmReg_SetRstSFlagCmuPll(RcmRegType *obj, uint8_t value)
{
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    uint32_t tmp = 0;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RCM_RST_SFLAG_CMU_PLL_SHIFT)) & RCM_RST_SFLAG_CMU_PLL_MASK);
    obj->RST_SFLAG = tmp;
}

/*! \brief Gets the Sticky FIRC clock monitor reset flag
 *
 * Indicates a reset has been caused by CMU FIRC reset.
 *
 * \param[in] obj : pointer to RCM register instance
 * \return Sticky FIRC clock monitor reset flag
 *         - 0b : Reset not caused by CMU FIRC reset
 *         - 1b : Reset caused by CMU FIRC reset
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstSFlagCmuFirc(const RcmRegType *obj)
{
    return ((obj->RST_SFLAG & RCM_RST_SFLAG_CMU_FIRC_MASK) >> RCM_RST_SFLAG_CMU_FIRC_SHIFT);
}

/*! \brief Sets the Sticky FIRC clock monitor reset flag
 *
 * Indicates a reset has been caused by CMU FIRC reset.
 *
 * \param[in] obj : pointer to RCM register instance
 * \param[in] value : the value of Sticky FIRC clock monitor reset flag
 *                    - 0b : no effect
 *                    - 1b : clear the flag
 */
__attribute__((always_inline)) static inline void RcmReg_SetRstSFlagCmuFirc(RcmRegType *obj, uint8_t value)
{
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    uint32_t tmp = 0;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RCM_RST_SFLAG_CMU_FIRC_SHIFT)) & RCM_RST_SFLAG_CMU_FIRC_MASK);
    obj->RST_SFLAG = tmp;
}

/*! \brief Gets the Sticky PLL lock loss reset flag
 *
 * Indicates a reset has been caused by PLL loss lock reset.
 *
 * \param[in] obj : pointer to RCM register instance
 * \return Sticky PLL lock loss reset flag
 *         - 0b : Reset not caused by PLL lock loss reset
 *         - 1b : Reset caused by PLL lock loss reset
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstSFlagPllLoss(const RcmRegType *obj)
{
    return ((obj->RST_SFLAG & RCM_RST_SFLAG_PLL_LOSS_MASK) >> RCM_RST_SFLAG_PLL_LOSS_SHIFT);
}

/*! \brief Sets the Sticky PLL lock loss reset flag
 *
 * Indicates a reset has been caused by PLL loss lock reset.
 *
 * \param[in] obj : pointer to RCM register instance
 * \param[in] value : the value of Sticky PLL lock loss reset flag
 *                    - 0b : no effect
 *                    - 1b : clear the flag
 */
__attribute__((always_inline)) static inline void RcmReg_SetRstSFlagPllLoss(RcmRegType *obj, uint8_t value)
{
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    uint32_t tmp = 0;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RCM_RST_SFLAG_PLL_LOSS_SHIFT)) & RCM_RST_SFLAG_PLL_LOSS_MASK);
    obj->RST_SFLAG = tmp;
}

/*! \brief Gets the Sticky MDMAP reset flag
 *
 * Indicates a reset has been caused by MDMAP system reset.
 *
 * \param[in] obj : pointer to RCM register instance
 * \return Sticky MDMAP reset flag
 *         - 0b : Reset not caused by MDMAP system reset
 *         - 1b : Reset caused by MDMAP system reset
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstSFlagMdmApRst(const RcmRegType *obj)
{
    return ((obj->RST_SFLAG & RCM_RST_SFLAG_MDMAP_RST_MASK) >> RCM_RST_SFLAG_MDMAP_RST_SHIFT);
}

/*! \brief Sets the Sticky MDMAP reset flag
 *
 * Indicates a reset has been caused by MDMAP system reset.
 *
 * \param[in] obj : pointer to RCM register instance
 * \param[in] value : the value of Sticky MDMAP reset flag
 *                    - 0b : no effect
 *                    - 1b : clear the flag
 */
__attribute__((always_inline)) static inline void RcmReg_SetRstSFlagMdmApRst(RcmRegType *obj, uint8_t value)
{
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    uint32_t tmp = 0;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RCM_RST_SFLAG_MDMAP_RST_SHIFT)) & RCM_RST_SFLAG_MDMAP_RST_MASK);
    obj->RST_SFLAG = tmp;
}

/*! \brief Gets the Sticky External PIN reset flag
 *
 * Indicates a reset has been caused by an active-low level on the external RESET (RESET_b) pin.
 *
 * \param[in] obj : pointer to RCM register instance
 * \return Sticky External PIN reset flag
 *         - 0b : Reset not caused by external reset pin
 *         - 1b : Reset caused by external reset pin
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstSFlagPinRst(const RcmRegType *obj)
{
    return ((obj->RST_SFLAG & RCM_RST_SFLAG_PIN_RST_MASK) >> RCM_RST_SFLAG_PIN_RST_SHIFT);
}

/*! \brief Sets the Sticky External PIN reset flag
 *
 * Indicates a reset has been caused by an active-low level on the external RESET (RESET_b) pin.
 *
 * \param[in] obj : pointer to RCM register instance
 * \param[in] value : the value of Sticky External PIN reset flag
 *                    - 0b : no effect
 *                    - 1b : clear the flag
 */
__attribute__((always_inline)) static inline void RcmReg_SetRstSFlagPinRst(RcmRegType *obj, uint8_t value)
{
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    uint32_t tmp = 0;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RCM_RST_SFLAG_PIN_RST_SHIFT)) & RCM_RST_SFLAG_PIN_RST_MASK);
    obj->RST_SFLAG = tmp;
}

/*! \brief Gets the Sticky Core Lockup reset flag
 *
 * Indicates a reset has been caused by the Arm core indication of a LOCKUP event.
 *
 * \param[in] obj : pointer to RCM register instance
 * \return Sticky Core Lockup reset flag
 *         - 0b : Reset not caused by core LOCKUP event
 *         - 1b : Reset caused by core LOCKUP event
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstSFlagLockupRst(const RcmRegType *obj)
{
    return ((obj->RST_SFLAG & RCM_RST_SFLAG_LOCKUP_RST_MASK) >> RCM_RST_SFLAG_LOCKUP_RST_SHIFT);
}

/*! \brief Sets the Sticky Core Lockup reset flag
 *
 * Indicates a reset has been caused by the Arm core indication of a LOCKUP event.
 *
 * \param[in] obj : pointer to RCM register instance
 * \param[in] value : the value of Sticky Core Lockup reset flag
 *                    - 0b : no effect
 *                    - 1b : clear the flag
 */
__attribute__((always_inline)) static inline void RcmReg_SetRstSFlagLockupRst(RcmRegType *obj, uint8_t value)
{
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    uint32_t tmp = 0;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RCM_RST_SFLAG_LOCKUP_RST_SHIFT)) & RCM_RST_SFLAG_LOCKUP_RST_MASK);
    obj->RST_SFLAG = tmp;
}

/*! \brief Gets the Sticky CPU Software reset flag
 *
 * Indicates a reset has been caused by software setting of SYSRESETREQ bit
 * in Application Interrupt and Reset Control Register in the Arm core.
 *
 * \param[in] obj : pointer to RCM register instance
 * \return Sticky CPU Software reset flag
 *         - 0b : Reset not caused by software setting of SYSRESETREQ bit
 *         - 1b : Reset caused by software setting of SYSRESETREQ bit
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstSFlagSysRst(const RcmRegType *obj)
{
    return ((obj->RST_SFLAG & RCM_RST_SFLAG_SYS_RST_MASK) >> RCM_RST_SFLAG_SYS_RST_SHIFT);
}

/*! \brief Sets the Sticky CPU Software reset flag
 *
 * Indicates a reset has been caused by software setting of SYSRESETREQ bit
 * in Application Interrupt and Reset Control Register in the Arm core.
 *
 * \param[in] obj : pointer to RCM register instance
 * \param[in] value : the value of Sticky CPU Software reset flag
 *                    - 0b : no effect
 *                    - 1b : clear the flag
 */
__attribute__((always_inline)) static inline void RcmReg_SetRstSFlagSysRst(RcmRegType *obj, uint8_t value)
{
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    uint32_t tmp = 0;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RCM_RST_SFLAG_SYS_RST_SHIFT)) & RCM_RST_SFLAG_SYS_RST_MASK);
    obj->RST_SFLAG = tmp;
}

/*! \brief Gets the Sticky Watchdog reset flag
 *
 * Indicates a reset has been caused by the watchdog timer timing out.
 * This reset source can be blocked by disabling the watchdog.
 *
 * \param[in] obj : pointer to RCM register instance
 * \return Sticky Watchdog reset flag
 *         - 0b : Reset not caused by watchdog timeout
 *         - 1b : Reset caused by watchdog timeout
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstSFlagWdgRst(const RcmRegType *obj)
{
    return ((obj->RST_SFLAG & RCM_RST_SFLAG_WDG_RST_MASK) >> RCM_RST_SFLAG_WDG_RST_SHIFT);
}

/*! \brief Sets the Sticky Watchdog reset flag
 *
 * Indicates a reset has been caused by the watchdog timer timing out.
 * This reset source can be blocked by disabling the watchdog.
 *
 * \param[in] obj : pointer to RCM register instance
 * \param[in] value : the value of Sticky Watchdog reset flag
 *                    - 0b : no effect
 *                    - 1b : clear the flag
 */
__attribute__((always_inline)) static inline void RcmReg_SetRstSFlagWdgRst(RcmRegType *obj, uint8_t value)
{
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    uint32_t tmp = 0;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RCM_RST_SFLAG_WDG_RST_SHIFT)) & RCM_RST_SFLAG_WDG_RST_MASK);
    obj->RST_SFLAG = tmp;
}

/*! \brief Gets the lockup reset enable
 *
 * This function gets the current status of lockup reset enable
 *
 * \param[in] obj : pointer to RCM register instance
 * \return lockup reset enable
 *         - 0b : No reset or interrupt will be caused by LOCKUP.
 *         - 1b : Reset or interrupt will be caused by LOCKUP.
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstCtrlLockupEn(const RcmRegType *obj)
{
    return ((obj->RST_CTRL & RCM_RST_CTRL_LOCKUP_EN_MASK) >> RCM_RST_CTRL_LOCKUP_EN_SHIFT);
}

/*! \brief Sets the lockup reset enable
 *
 * This function sets the lockup reset enable
 *
 * \param[in] obj : pointer to RCM register instance
 * \param[in] value : the value of lockup reset enable
 *                    - 0b : No reset or interrupt will be caused by LOCKUP.
 *                    - 1b : Reset or interrupt will be caused by LOCKUP.
 */
__attribute__((always_inline)) static inline void RcmReg_SetRstCtrlLockupEn(RcmRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->RST_CTRL;

    tmp &= ~RCM_RST_CTRL_LOCKUP_EN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RCM_RST_CTRL_LOCKUP_EN_SHIFT)) & RCM_RST_CTRL_LOCKUP_EN_MASK);
    obj->RST_CTRL = tmp;
}

/*! \brief Gets the PLL lock loss reset enable
 *
 * This function gets the current status of PLL lock loss reset enable
 *
 * \param[in] obj : pointer to RCM register instance
 * \return PLL lock loss reset enable
 *         - 0b : No reset or interrupt will be caused by PLL lock loss.
 *         - 1b : Reset or interrupt will be caused by PLL lock loss.
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstCtrlPllLossEn(const RcmRegType *obj)
{
    return ((obj->RST_CTRL & RCM_RST_CTRL_PLL_LOSS_EN_MASK) >> RCM_RST_CTRL_PLL_LOSS_EN_SHIFT);
}

/*! \brief Sets the PLL lock loss reset enable
 *
 * This function sets the PLL lock loss reset enable
 *
 * \param[in] obj : pointer to RCM register instance
 * \param[in] value : the value of PLL lock loss reset enable
 *                    - 0b : No reset or interrupt will be caused by PLL lock loss.
 *                    - 1b : Reset or interrupt will be caused by PLL lock loss.
 */
__attribute__((always_inline)) static inline void RcmReg_SetRstCtrlPllLossEn(RcmRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->RST_CTRL;

    tmp &= ~RCM_RST_CTRL_PLL_LOSS_EN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RCM_RST_CTRL_PLL_LOSS_EN_SHIFT)) & RCM_RST_CTRL_PLL_LOSS_EN_MASK);
    obj->RST_CTRL = tmp;
}

/*! \brief Gets the SOSC clock monitor interrupt enable
 *
 * This function get the current status of SOSC clock monitor interrupt enable
 *
 * \param[in] obj : pointer to RCM register instance
 * \return SOSC clock monitor interrupt enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstCtrlCmuSoscIE(const RcmRegType *obj)
{
    return ((obj->RST_CTRL & RCM_RST_CTRL_CMU_SOSC_IE_MASK) >> RCM_RST_CTRL_CMU_SOSC_IE_SHIFT);
}

/*! \brief Sets the SOSC clock monitor interrupt enable
 *
 * This function sets the SOSC clock monitor interrupt enable
 *
 * \param[in] obj : pointer to RCM register instance
 * \param[in] value : the value of SOSC clock monitor interrupt enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void RcmReg_SetRstCtrlCmuSoscIE(RcmRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->RST_CTRL;

    tmp &= ~RCM_RST_CTRL_CMU_SOSC_IE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RCM_RST_CTRL_CMU_SOSC_IE_SHIFT)) & RCM_RST_CTRL_CMU_SOSC_IE_MASK);
    obj->RST_CTRL = tmp;
}

/*! \brief Gets the PLL clock monitor interrupt enable
 *
 * This function gets the current status of PLL clock monitor interrupt enable
 *
 * \param[in] obj : pointer to RCM register instance
 * \return PLL clock monitor interrupt enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstCtrlCmuPllIE(const RcmRegType *obj)
{
    return ((obj->RST_CTRL & RCM_RST_CTRL_CMU_PLL_IE_MASK) >> RCM_RST_CTRL_CMU_PLL_IE_SHIFT);
}

/*! \brief Sets the PLL clock monitor interrupt enable
 *
 * This function sets the PLL clock monitor interrupt enable
 *
 * \param[in] obj : pointer to RCM register instance
 * \param[in] value : the value of PLL clock monitor interrupt enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void RcmReg_SetRstCtrlCmuPllIE(RcmRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->RST_CTRL;

    tmp &= ~RCM_RST_CTRL_CMU_PLL_IE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RCM_RST_CTRL_CMU_PLL_IE_SHIFT)) & RCM_RST_CTRL_CMU_PLL_IE_MASK);
    obj->RST_CTRL = tmp;
}

/*! \brief Gets the FIRC clock monitor interrupt enable
 *
 * This function get the current status of FIRC clock monitor interrupt enable
 *
 * \param[in] obj : pointer to RCM register instance
 * \return FIRC clock monitor interrupt enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstCtrlCmuFircIE(const RcmRegType *obj)
{
    return ((obj->RST_CTRL & RCM_RST_CTRL_CMU_FIRC_IE_MASK) >> RCM_RST_CTRL_CMU_FIRC_IE_SHIFT);
}

/*! \brief Sets the FIRC clock monitor interrupt enable
 *
 * This function sets the FIRC clock monitor interrupt enable
 *
 * \param[in] obj : pointer to RCM register instance
 * \param[in] value : the value of FIRC clock monitor interrupt enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void RcmReg_SetRstCtrlCmuFircIE(RcmRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->RST_CTRL;

    tmp &= ~RCM_RST_CTRL_CMU_FIRC_IE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RCM_RST_CTRL_CMU_FIRC_IE_SHIFT)) & RCM_RST_CTRL_CMU_FIRC_IE_MASK);
    obj->RST_CTRL = tmp;
}

/*! \brief Gets the PLL loss reset interrupt enable
 *
 * This function gets the current status of PLL loss reset interrupt enable
 *
 * \param[in] obj : pointer to RCM register instance
 * \return PLL loss reset interrupt enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstCtrlPllLossIE(const RcmRegType *obj)
{
    return ((obj->RST_CTRL & RCM_RST_CTRL_PLL_LOSS_IE_MASK) >> RCM_RST_CTRL_PLL_LOSS_IE_SHIFT);
}

/*! \brief Sets the PLL loss reset interrupt enable
 *
 * This function sets the PLL loss reset interrupt enable
 *
 * \param[in] obj : pointer to RCM register instance
 * \param[in] value : the value of PLL loss reset interrupt enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void RcmReg_SetRstCtrlPllLossIE(RcmRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->RST_CTRL;

    tmp &= ~RCM_RST_CTRL_PLL_LOSS_IE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RCM_RST_CTRL_PLL_LOSS_IE_SHIFT)) & RCM_RST_CTRL_PLL_LOSS_IE_MASK);
    obj->RST_CTRL = tmp;
}

/*! \brief Gets the MDMAP system reset interrupt enable
 *
 * This function gets the current status of MDMAP system reset interrupt enable
 *
 * \param[in] obj : pointer to RCM register instance
 * \return MDMAP system reset interrupt enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstCtrlMdmApRstIE(const RcmRegType *obj)
{
    return ((obj->RST_CTRL & RCM_RST_CTRL_MDMAP_RST_IE_MASK) >> RCM_RST_CTRL_MDMAP_RST_IE_SHIFT);
}

/*! \brief Sets the MDMAP system reset interrupt enable
 *
 * This function sets the MDMAP system reset interrupt enable
 *
 * \param[in] obj : pointer to RCM register instance
 * \param[in] value : the value of MDMAP system reset interrupt enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void RcmReg_SetRstCtrlMdmApRstIE(RcmRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->RST_CTRL;

    tmp &= ~RCM_RST_CTRL_MDMAP_RST_IE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RCM_RST_CTRL_MDMAP_RST_IE_SHIFT)) & RCM_RST_CTRL_MDMAP_RST_IE_MASK);
    obj->RST_CTRL = tmp;
}

/*! \brief Gets the external reset pin interrupt enable
 *
 * This function gets the current status of external reset pin interrupt enable
 *
 * \param[in] obj : pointer to RCM register instance
 * \return external reset pin interrupt enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstCtrlPinRstIE(const RcmRegType *obj)
{
    return ((obj->RST_CTRL & RCM_RST_CTRL_PIN_RST_IE_MASK) >> RCM_RST_CTRL_PIN_RST_IE_SHIFT);
}

/*! \brief Sets the external reset pin interrupt enable
 *
 * This function sets the external reset pin interrupt enable
 *
 * \param[in] obj : pointer to RCM register instance
 * \param[in] value : the value of external reset pin interrupt enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void RcmReg_SetRstCtrlPinRstIE(RcmRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->RST_CTRL;

    tmp &= ~RCM_RST_CTRL_PIN_RST_IE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RCM_RST_CTRL_PIN_RST_IE_SHIFT)) & RCM_RST_CTRL_PIN_RST_IE_MASK);
    obj->RST_CTRL = tmp;
}

/*! \brief Gets the CPU system reset interrupt enable
 *
 * This function gets the current status of CPU system reset interrupt enable
 *
 * \param[in] obj : pointer to RCM register instance
 * \return CPU system reset interrupt enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstCtrlSysRstIE(const RcmRegType *obj)
{
    return ((obj->RST_CTRL & RCM_RST_CTRL_SYS_RST_IE_MASK) >> RCM_RST_CTRL_SYS_RST_IE_SHIFT);
}

/*! \brief Sets the CPU system reset interrupt enable
 *
 * This function sets the CPU system reset interrupt enable
 *
 * \param[in] obj : pointer to RCM register instance
 * \param[in] value : the value of CPU system reset interrupt enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void RcmReg_SetRstCtrlSysRstIE(RcmRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->RST_CTRL;

    tmp &= ~RCM_RST_CTRL_SYS_RST_IE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RCM_RST_CTRL_SYS_RST_IE_SHIFT)) & RCM_RST_CTRL_SYS_RST_IE_MASK);
    obj->RST_CTRL = tmp;
}

/*! \brief Gets the watchdog reset interrupt enable
 *
 * This function gets the current status of watchdog reset interrupt enable
 *
 * \param[in] obj : pointer to RCM register instance
 * \return watchdog reset interrupt enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstCtrlWdgRstIE(const RcmRegType *obj)
{
    return ((obj->RST_CTRL & RCM_RST_CTRL_WDG_RST_IE_MASK) >> RCM_RST_CTRL_WDG_RST_IE_SHIFT);
}

/*! \brief Sets the watchdog reset interrupt enable
 *
 * This function sets the watchdog reset interrupt enable
 *
 * \param[in] obj : pointer to RCM register instance
 * \param[in] value : the value of watchdog reset interrupt enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void RcmReg_SetRstCtrlWdgRstIE(RcmRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->RST_CTRL;

    tmp &= ~RCM_RST_CTRL_WDG_RST_IE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RCM_RST_CTRL_WDG_RST_IE_SHIFT)) & RCM_RST_CTRL_WDG_RST_IE_MASK);
    obj->RST_CTRL = tmp;
}

/*! \brief Gets the Global Reset Asynchronous Interrupt Enable
 *
 * This function gets the current status of Global Reset Asynchronous Interrupt Enable
 *
 * \param[in] obj : pointer to RCM register instance
 * \return Global Reset Asynchronous Interrupt Enable
 *         - 0b : All interrupt sources disabled.
 *         - 1b : All interrupt sources enabled.
Note that the individual interrupt-enable bits still need to be set to generate interrupts
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstCtrlGlobalIE(const RcmRegType *obj)
{
    return ((obj->RST_CTRL & RCM_RST_CTRL_GLOBAL_IE_MASK) >> RCM_RST_CTRL_GLOBAL_IE_SHIFT);
}

/*! \brief Sets the Global Reset Asynchronous Interrupt Enable
 *
 * This function sets the Global Reset Asynchronous Interrupt Enable
 *
 * \param[in] obj : pointer to RCM register instance
 * \param[in] value : the value of Global Reset Asynchronous Interrupt Enable
 *                    - 0b : All interrupt sources disabled.
 *                    - 1b : All interrupt sources enabled.
Note that the individual interrupt-enable bits still need to be set to generate interrupts
 */
__attribute__((always_inline)) static inline void RcmReg_SetRstCtrlGlobalIE(RcmRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->RST_CTRL;

    tmp &= ~RCM_RST_CTRL_GLOBAL_IE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RCM_RST_CTRL_GLOBAL_IE_SHIFT)) & RCM_RST_CTRL_GLOBAL_IE_MASK);
    obj->RST_CTRL = tmp;
}

/*! \brief Gets the Reset Delay Time
 *
 * Configures the maximum reset delay time from when the interrupt
 * is asserted and the system reset occurs.
 *
 * \param[in] obj : pointer to RCM register instance
 * \return Reset Delay Time
 *         - 00b : 10 LPO cycles
 *         - 01b : 34 LPO cycles
 *         - 10b : 130 LPO cycles
 *         - 11b : 514 LPO cycles
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstCtrlRstDelay(const RcmRegType *obj)
{
    return ((obj->RST_CTRL & RCM_RST_CTRL_RST_DELAY_MASK) >> RCM_RST_CTRL_RST_DELAY_SHIFT);
}

/*! \brief Sets the Reset Delay Time
 *
 * Configures the maximum reset delay time from when the interrupt
 * is asserted and the system reset occurs.
 *
 * \param[in] obj : pointer to RCM register instance
 * \param[in] value : the value of Reset Delay Time
 *                    - 00b : 10 LPO cycles
 *                    - 01b : 34 LPO cycles
 *                    - 10b : 130 LPO cycles
 *                    - 11b : 514 LPO cycles
 */
__attribute__((always_inline)) static inline void RcmReg_SetRstCtrlRstDelay(RcmRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->RST_CTRL;

    tmp &= ~RCM_RST_CTRL_RST_DELAY_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RCM_RST_CTRL_RST_DELAY_SHIFT)) & RCM_RST_CTRL_RST_DELAY_MASK);
    obj->RST_CTRL = tmp;
}

/*! \brief Gets the SOSC clock monitor interrupt status
 *
 * This function gets the current SOSC clock monitor interrupt status.
 *
 * \param[in] obj : pointer to RCM register instance
 * \return SOSC clock monitor interrupt status
 *         - 0b : no interrupt
 *         - 1b : interrupt
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstIrqCmuSosc(const RcmRegType *obj)
{
    return ((obj->RST_IRQ & RCM_RST_IRQ_CMU_SOSC_MASK) >> RCM_RST_IRQ_CMU_SOSC_SHIFT);
}

/*! \brief Gets the PLL clock monitor interrupt status
 *
 * This function gets the current PLL clock monitor interrupt status.
 *
 * \param[in] obj : pointer to RCM register instance
 * \return PLL clock monitor interrupt status
 *         - 0b : no interrupt
 *         - 1b : interrupt
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstIrqCmuPll(const RcmRegType *obj)
{
    return ((obj->RST_IRQ & RCM_RST_IRQ_CMU_PLL_MASK) >> RCM_RST_IRQ_CMU_PLL_SHIFT);
}

/*! \brief Gets the FIRC clock monitor interrupt status
 *
 * This function gets the current FIRC clock monitor interrupt status.
 *
 * \param[in] obj : pointer to RCM register instance
 * \return FIRC clock monitor interrupt status
 *         - 0b : no interrupt
 *         - 1b : interrupt
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstIrqCmuFirc(const RcmRegType *obj)
{
    return ((obj->RST_IRQ & RCM_RST_IRQ_CMU_FIRC_MASK) >> RCM_RST_IRQ_CMU_FIRC_SHIFT);
}

/*! \brief Gets the PLL loss reset interrupt status
 *
 * This function gets the current PLL loss reset interrupt status.
 *
 * \param[in] obj : pointer to RCM register instance
 * \return PLL loss reset interrupt status
 *         - 0b : no interrupt
 *         - 1b : interrupt
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstIrqPllLoss(const RcmRegType *obj)
{
    return ((obj->RST_IRQ & RCM_RST_IRQ_PLL_LOSS_MASK) >> RCM_RST_IRQ_PLL_LOSS_SHIFT);
}

/*! \brief Gets the MDMAP system reset interrupt status
 *
 * This function gets the current MDMAP system reset interrupt status.
 *
 * \param[in] obj : pointer to RCM register instance
 * \return MDMAP system reset interrupt status
 *         - 0b : no interrupt
 *         - 1b : interrupt
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstIrqMdmap(const RcmRegType *obj)
{
    return ((obj->RST_IRQ & RCM_RST_IRQ_MDMAP_MASK) >> RCM_RST_IRQ_MDMAP_SHIFT);
}

/*! \brief Gets the external reset pin interrupt status
 *
 * This function gets the current external reset pin interrupt status.
 *
 * \param[in] obj : pointer to RCM register instance
 * \return external reset pin interrupt status
 *         - 0b : no interrupt
 *         - 1b : interrupt
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstIrqPin(const RcmRegType *obj)
{
    return ((obj->RST_IRQ & RCM_RST_IRQ_PIN_MASK) >> RCM_RST_IRQ_PIN_SHIFT);
}

/*! \brief Gets the CPU system reset interrupt status
 *
 * This function gets the current CPU system reset interrupt status.
 *
 * \param[in] obj : pointer to RCM register instance
 * \return CPU system reset interrupt status
 *         - 0b : no interrupt
 *         - 1b : interrupt
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstIrqSys(const RcmRegType *obj)
{
    return ((obj->RST_IRQ & RCM_RST_IRQ_SYS_MASK) >> RCM_RST_IRQ_SYS_SHIFT);
}

/*! \brief Gets the watchdog reset interrupt status
 *
 * This function gets the current watchdog reset interrupt status.
 *
 * \param[in] obj : pointer to RCM register instance
 * \return watchdog reset interrupt status
 *         - 0b : no interrupt
 *         - 1b : interrupt
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetRstIrqWdg(const RcmRegType *obj)
{
    return ((obj->RST_IRQ & RCM_RST_IRQ_WDG_MASK) >> RCM_RST_IRQ_WDG_SHIFT);
}

/*! \brief Sets the ALON RST/SCG/PCC unlock key
 *
 * The RST/SCG/PCC registers in ALON power domain is locked by default.
 * Before writing registers, write unlock key to this register.
 *
 * \param[in] obj : pointer to RCM register instance
 * \param[in] value : the value of ALON RST/SCG/PCC unlock key
 *                    - 0x43524155 : unlock
 *                    - other : lock
 */
__attribute__((always_inline)) static inline void RcmReg_SetLockKey(RcmRegType *obj, uint32_t value)
{
    obj->LOCK = value;
}

/*! \brief Gets the RCM register lock flag
 *
 * This function gets the current RCM register lock flag.
 * Registers in RCM is locked by default.
 * Before writing registers in rcm, write unlock key .
 *
 * \param[in] obj : pointer to RCM register instance
 * \return RCM register lock flag
 *         - 0b : unlock
 *         - 1b : lock
 */
__attribute__((always_inline)) static inline uint8_t RcmReg_GetLockStLock(const RcmRegType *obj)
{
    return ((obj->LOCK_ST & RCM_LOCK_ST_LOCK_MASK) >> RCM_LOCK_ST_LOCK_SHIFT);
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _RCM_REG_H_ */
