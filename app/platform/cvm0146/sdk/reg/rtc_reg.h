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

#ifndef _RTC_REG_H_
#define _RTC_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the RTC (Real Time Clock) Registers
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

/* TPR Bit Fields */
#define RTC_TPR_TPR_MASK   (0xFFFFu)
#define RTC_TPR_TPR_SHIFT  (0u)
#define RTC_TPR_TPR_WIDTH  (16u)

/* CR Bit Fields */
#define RTC_CR_CPE_MASK    (0x1000000u)
#define RTC_CR_CPE_SHIFT   (24u)
#define RTC_CR_CPE_WIDTH   (1u)
#define RTC_CR_CLKO_MASK   (0x200u)
#define RTC_CR_CLKO_SHIFT  (9u)
#define RTC_CR_CLKO_WIDTH  (1u)
#define RTC_CR_CPS_MASK    (0x20u)
#define RTC_CR_CPS_SHIFT   (5u)
#define RTC_CR_CPS_WIDTH   (1u)
#define RTC_CR_UM_MASK     (0x08u)
#define RTC_CR_UM_SHIFT    (3u)
#define RTC_CR_UM_WIDTH    (1u)
#define RTC_CR_SUP_MASK    (0x04u)
#define RTC_CR_SUP_SHIFT   (2u)
#define RTC_CR_SUP_WIDTH   (1u)
#define RTC_CR_SWR_MASK    (0x01u)
#define RTC_CR_SWR_SHIFT   (0u)
#define RTC_CR_SWR_WIDTH   (1u)

/* SR Bit Fields */
#define RTC_SR_TCE_MASK    (0x10u)
#define RTC_SR_TCE_SHIFT   (4u)
#define RTC_SR_TCE_WIDTH   (1u)
#define RTC_SR_CSD_MASK    (0x08u)
#define RTC_SR_CSD_SHIFT   (3u)
#define RTC_SR_CSD_WIDTH   (1u)
#define RTC_SR_TAF_MASK    (0x04u)
#define RTC_SR_TAF_SHIFT   (2u)
#define RTC_SR_TAF_WIDTH   (1u)
#define RTC_SR_TOF_MASK    (0x02u)
#define RTC_SR_TOF_SHIFT   (1u)
#define RTC_SR_TOF_WIDTH   (1u)
#define RTC_SR_TIF_MASK    (0x01u)
#define RTC_SR_TIF_SHIFT   (0u)
#define RTC_SR_TIF_WIDTH   (1u)

/* LR Bit Fields */
#define RTC_LR_LRL_MASK    (0x40u)
#define RTC_LR_LRL_SHIFT   (6u)
#define RTC_LR_LRL_WIDTH   (1u)
#define RTC_LR_SRL_MASK    (0x20u)
#define RTC_LR_SRL_SHIFT   (5u)
#define RTC_LR_SRL_WIDTH   (1u)
#define RTC_LR_CRL_MASK    (0x10u)
#define RTC_LR_CRL_SHIFT   (4u)
#define RTC_LR_CRL_WIDTH   (1u)

/* IER Bit Fields */
#define RTC_IER_TSIC_MASK  (0x70000u)
#define RTC_IER_TSIC_SHIFT (16u)
#define RTC_IER_TSIC_WIDTH (3u)
#define RTC_IER_TSIE_MASK  (0x10u)
#define RTC_IER_TSIE_SHIFT (4u)
#define RTC_IER_TSIE_WIDTH (1u)
#define RTC_IER_TAIE_MASK  (0x04u)
#define RTC_IER_TAIE_SHIFT (2u)
#define RTC_IER_TAIE_WIDTH (1u)
#define RTC_IER_TIOE_MASK  (0x02u)
#define RTC_IER_TIOE_SHIFT (1u)
#define RTC_IER_TIOE_WIDTH (1u)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief The definition of RTC registers
 */
typedef struct _RtcRegType_
{
    volatile uint32_t TSR;      /*!< time second value register, offset: 0x0 */
    volatile uint32_t TPR;      /*!< time prescaler value register, offset: 0x4 */
    volatile uint32_t TAR;      /*!< time alarm value register, offset: 0x8 */
    uint32_t          RESERVED; /*!< reserverd block, offset: 0xC */
    volatile uint32_t CR;       /*!< control register, offset: 0x10 */
    volatile uint32_t SR;       /*!< status register, offset: 0x14 */
    volatile uint32_t LR;       /*!< lock register, offset: 0x18 */
    volatile uint32_t IER;      /*!< interrupt config register, offset: 0x1C */
} RtcRegType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Gets the TSR value register
 *
 * This function gets the current TSR value register.
 * When the time counter is enabled, the TSR is read only and increments once a second.
 * The time counter will read as zero when SR[TOF] or SR[TIF] are set.
 * When the time counter is disabled, the TSR can be read or written.
 * Writing to the TSR when the time counter is disabled will clear the SR[TOF] and/or the SR[TIF].
 * Writing to TSR with zero is supported, but not recommended because TSR will read as zero when SR[TIF] or SR[TOF]
 * are set (indicating the time is invalid)
 *
 * \param[in] obj : pointer to RTC register instance
 * \return current TSR value
 */
__attribute__((always_inline)) static inline uint32_t RtcReg_GetTsr(const RtcRegType *obj)
{
    return obj->TSR;
}

/*! \brief Sets the TSR value register
 *
 * This function sets the TSR value register.
 * When the time counter is enabled, the TSR is read only and increments once a second.
 * The time counter will read as zero when SR[TOF] or SR[TIF] are set.
 * When the time counter is disabled, the TSR can be read or written.
 * Writing to the TSR when the time counter is disabled will clear the SR[TOF] and/or the SR[TIF].
 * Writing to TSR with zero is supported, but not recommended because TSR will read as zero when SR[TIF] or SR[TOF]
 * are set (indicating the time is invalid)
 *
 * \param[in] obj : pointer to RTC register instance
 * \param[in] value : the value of TSR register
 */
__attribute__((always_inline)) static inline void RtcReg_SetTsr(RtcRegType *obj, uint32_t value)
{
    obj->TSR = value;
}

/*! \brief Gets the TPR value register
 *
 * This function gets the current TPR value register.
 * When the time counter is enabled, the TPR is read only and increments every 32.768 kHz clock cycle.
 * The time counter will read as zero when SR[TOF] or SR[TIF] are set.
 * When the time counter is disabled, the TPR can be read or written.
 * The TSR[TSR] increments when bit 14 of the TPR transitions from a logic one to a logic zero
 *
 * \param[in] obj : pointer to RTC register instance
 * \return TPR value register
 */
__attribute__((always_inline)) static inline uint16_t RtcReg_GetTprTpr(const RtcRegType *obj)
{
    return ((obj->TPR & RTC_TPR_TPR_MASK) >> RTC_TPR_TPR_SHIFT);
}

/*! \brief Sets the TPR value register
 *
 * This function sets the TPR value register.
 * When the time counter is enabled, the TPR is read only and increments every 32.768 kHz clock cycle.
 * The time counter will read as zero when SR[TOF] or SR[TIF] are set.
 * When the time counter is disabled, the TPR can be read or written.
 * The TSR[TSR] increments when bit 14 of the TPR transitions from a logic one to a logic zero
 *
 * \param[in] obj : pointer to RTC register instance
 * \param[in] value : the value of TPR value register
 */
__attribute__((always_inline)) static inline void RtcReg_SetTprTpr(RtcRegType *obj, uint16_t value)
{
    uint32_t tmp = obj->TPR;

    tmp &= ~RTC_TPR_TPR_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RTC_TPR_TPR_SHIFT)) & RTC_TPR_TPR_MASK);
    obj->TPR = tmp;
}

/*! \brief Gets the TAR value register
 *
 * This function gets the current TAR value register.
 * When the time counter is enabled, the SR[TAF] is set whenever the TAR[TAR] equals the TSR[TSR] and the TSR[TSR] increments.
 * Writing to the TAR clears the SR[TAF]
 *
 * \param[in] obj : pointer to RTC register instance
 * \return TAR value register
 */
__attribute__((always_inline)) static inline uint32_t RtcReg_GetTar(const RtcRegType *obj)
{
    return obj->TAR;
}

/*! \brief Sets the TAR value register
 *
 * This function sets the TAR value register.
 * When the time counter is enabled, the SR[TAF] is set whenever the TAR[TAR] equals the TSR[TSR] and the TSR[TSR] increments.
 * Writing to the TAR clears the SR[TAF]
 *
 * \param[in] obj : pointer to RTC register instance
 * \param[in] value : the value of TAR value register
 */
__attribute__((always_inline)) static inline void RtcReg_SetTar(RtcRegType *obj, uint32_t value)
{
    obj->TAR = value;
}

/*! \brief Gets the Clock Pin Enable
 *
 * This function gets the current Clock Pin Enable.
 *
 * \param[in] obj : pointer to RTC register instance
 * \return Clock Pin Enable
 *         - 0b : The RTC_CLKOUT function is disabled.
 *         - 1b : Enable RTC_CLKOUT function.
 */
__attribute__((always_inline)) static inline uint8_t RtcReg_GetCrCpe(const RtcRegType *obj)
{
    return ((obj->CR & RTC_CR_CPE_MASK) >> RTC_CR_CPE_SHIFT);
}

/*! \brief Sets the Clock Pin Enable
 *
 * This function sets the Clock Pin Enable.
 *
 * \param[in] obj : pointer to RTC register instance
 * \param[in] value : the value of Clock Pin Enable
 *                    - 0b : The RTC_CLKOUT function is disabled.
 *                    - 1b : Enable RTC_CLKOUT function.
 */
__attribute__((always_inline)) static inline void RtcReg_SetCrCpe(RtcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CR;

    tmp &= ~RTC_CR_CPE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RTC_CR_CPE_SHIFT)) & RTC_CR_CPE_MASK);
    obj->CR = tmp;
}

/*! \brief Gets the Clock Output
 *
 * This function gets the current Clock Output.
 *
 * \param[in] obj : pointer to RTC register instance
 * \return Clock Output
 *         - 0b : The 32K/32.768KHz clock is output to other peripherals.
 *         - 1b : The 32K/32.768KHz clock is not output to other peripherals.
 */
__attribute__((always_inline)) static inline uint8_t RtcReg_GetCrClkO(const RtcRegType *obj)
{
    return ((obj->CR & RTC_CR_CLKO_MASK) >> RTC_CR_CLKO_SHIFT);
}

/*! \brief Sets the Clock Output
 *
 * This function sets the Clock Output.
 *
 * \param[in] obj : pointer to RTC register instance
 * \param[in] value : the value of Clock Output
 *                    - 0b : The 32K/32.768KHz clock is output to other peripherals.
 *                    - 1b : The 32K/32.768KHz clock is not output to other peripherals.
 */
__attribute__((always_inline)) static inline void RtcReg_SetCrClkO(RtcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CR;

    tmp &= ~RTC_CR_CLKO_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RTC_CR_CLKO_SHIFT)) & RTC_CR_CLKO_MASK);
    obj->CR = tmp;
}

/*! \brief Gets the Clock Pin Select
 *
 * This function gets the current Clock Pin Select.
 *
 * \param[in] obj : pointer to RTC register instance
 * \return Clock Pin Select
 *         - 0b : The prescaler output clock (as configured by TSIC) is output on RTC_CLKOUT.
 *         - 1b : The RTC 32.768 kHz/32kHz clock is output on RTC_CLKOUT, provided it is output to other peripherals.
 */
__attribute__((always_inline)) static inline uint8_t RtcReg_GetCrCps(const RtcRegType *obj)
{
    return ((obj->CR & RTC_CR_CPS_MASK) >> RTC_CR_CPS_SHIFT);
}

/*! \brief Sets the Clock Pin Select
 *
 * This function sets the Clock Pin Select.
 *
 * \param[in] obj : pointer to RTC register instance
 * \param[in] value : the value of Clock Pin Select
 *                    - 0b : The prescaler output clock (as configured by TSIC) is output on RTC_CLKOUT.
 *                    - 1b : The RTC 32.768 kHz/32kHz clock is output on RTC_CLKOUT, provided it is output to other peripherals.
 */
__attribute__((always_inline)) static inline void RtcReg_SetCrCps(RtcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CR;

    tmp &= ~RTC_CR_CPS_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RTC_CR_CPS_SHIFT)) & RTC_CR_CPS_MASK);
    obj->CR = tmp;
}

/*! \brief Gets the Update Mode
 *
 * This function gets the current Update Mode.
 * when UM=0 and LR[SRL]=0, SR[TCE] can't be written
 * when UM=1 and LR[SRL]=0, SR[TCE] can only be written when SR[TCE]=0 or SR[TIF]=1 or SR[TOF]=1.
 * (when LR[SRL]=1, CR[UM] has no effect on SR[TCE]. In other words, in this situation, TCE can be written at any time)
 *
 * \param[in] obj : pointer to RTC register instance
 * \return Update Mode
 *         - 0b : SR[TCE] register cannot be written when locked.
 *         - 1b : SR[TCE] register can be written when locked under limited conditions.
 */
__attribute__((always_inline)) static inline uint8_t RtcReg_GetCrUm(const RtcRegType *obj)
{
    return ((obj->CR & RTC_CR_UM_MASK) >> RTC_CR_UM_SHIFT);
}

/*! \brief Sets the Update Mode
 *
 * This function sets the Update Mode.
 * when UM=0 and LR[SRL]=0, SR[TCE] can't be written
 * when UM=1 and LR[SRL]=0, SR[TCE] can only be written when SR[TCE]=0 or SR[TIF]=1 or SR[TOF]=1.
 * (when LR[SRL]=1, CR[UM] has no effect on SR[TCE]. In other words, in this situation, TCE can be written at any time)
 *
 * \param[in] obj : pointer to RTC register instance
 * \param[in] value : the value of Update Mode
 *                    - 0b : SR[TCE] register cannot be written when locked.
 *                    - 1b : SR[TCE] register can be written when locked under limited conditions.
 */
__attribute__((always_inline)) static inline void RtcReg_SetCrUm(RtcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CR;

    tmp &= ~RTC_CR_UM_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RTC_CR_UM_SHIFT)) & RTC_CR_UM_MASK);
    obj->CR = tmp;
}

/*! \brief Gets the Supervisor Access
 *
 * This function gets the current Supervisor Access.
 *
 * \param[in] obj : pointer to RTC register instance
 * \return Supervisor Access
 *         - 0b : Non-supervisor mode write accesses are not supported and generate a bus error.
 *         - 1b : Non-supervisor mode write accesses are supported.
 */
__attribute__((always_inline)) static inline uint8_t RtcReg_GetCrSup(const RtcRegType *obj)
{
    return ((obj->CR & RTC_CR_SUP_MASK) >> RTC_CR_SUP_SHIFT);
}

/*! \brief Sets the Supervisor Access
 *
 * This function sets the Supervisor Access.
 *
 * \param[in] obj : pointer to RTC register instance
 * \param[in] value : the value of Supervisor Access
 *                    - 0b : Non-supervisor mode write accesses are not supported and generate a bus error.
 *                    - 1b : Non-supervisor mode write accesses are supported.
 */
__attribute__((always_inline)) static inline void RtcReg_SetCrSup(RtcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CR;

    tmp &= ~RTC_CR_SUP_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RTC_CR_SUP_SHIFT)) & RTC_CR_SUP_MASK);
    obj->CR = tmp;
}

/*! \brief Gets the software reset
 *
 * This function gets the current software reset .
 *
 * \param[in] obj : pointer to RTC register instance
 * \return software reset
 *         - 0b : no effect
 *         - 1b : reset all RTC  registers except for the SWR bit.
 *                The SWR bit is cleared by POR and by software explicitly clearing it
 */
__attribute__((always_inline)) static inline uint8_t RtcReg_GetCrSwr(const RtcRegType *obj)
{
    return ((obj->CR & RTC_CR_SWR_MASK) >> RTC_CR_SWR_SHIFT);
}

/*! \brief Sets the software reset
 *
 * This function sets the software reset .
 *
 * \param[in] obj : pointer to RTC register instance
 * \param[in] value : the value of software reset
 *                    - 0b : no effect
 *                    - 1b : reset all RTC  registers except for the SWR bit.
 *                           The SWR bit is cleared by POR and by software explicitly clearing it
 */
__attribute__((always_inline)) static inline void RtcReg_SetCrSwr(RtcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CR;

    tmp &= ~RTC_CR_SWR_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RTC_CR_SWR_SHIFT)) & RTC_CR_SWR_MASK);
    obj->CR = tmp;
}

/*! \brief Gets the Time Counter Enable
 *
 * This function gets the current Time Counter Enable.
 * When time counter is disabled the TSR register and TPR register are writeable, but do not increment.
 * When time counter is enabled the TSR register and TPR register are not writeable, but increment.
 *
 * \param[in] obj : pointer to RTC register instance
 * \return Time Counter Enable
 *         - 0b : Time counter is disabled.
 *         - 1b : Time counter is enabled.
 */
__attribute__((always_inline)) static inline uint8_t RtcReg_GetSrTce(const RtcRegType *obj)
{
    return ((obj->SR & RTC_SR_TCE_MASK) >> RTC_SR_TCE_SHIFT);
}

/*! \brief Sets the Time Counter Enable
 *
 * This function sets the Time Counter Enable.
 * When time counter is disabled the TSR register and TPR register are writeable, but do not increment.
 * When time counter is enabled the TSR register and TPR register are not writeable, but increment.
 *
 * \param[in] obj : pointer to RTC register instance
 * \param[in] value : the value of Time Counter Enable
 *                    - 0b : Time counter is disabled.
 *                    - 1b : Time counter is enabled.
 */
__attribute__((always_inline)) static inline void RtcReg_SetSrTce(RtcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SR;

    tmp &= ~RTC_SR_TCE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RTC_SR_TCE_SHIFT)) & RTC_SR_TCE_MASK);
    obj->SR = tmp;
}

/*! \brief Gets the Time New Config Sync Done Enable
 *
 * This function gets the current Time New Config Sync Done Enable.
 * when new config done, software should set this bit, but return 0 when software read now.
 * this bit would be 1 when the new config sync done. Its means software can enable RTC again.
 *
 * \param[in] obj : pointer to RTC register instance
 * \return Time New Config Sync Done Enable
 *         - 0b : Synchronization of New Config is Ongoing, Re-enable RTC is not allowed.
 *         - 1b : Synchronization of New Config is Done, Re-enable RTC is allowed.
 */
__attribute__((always_inline)) static inline uint8_t RtcReg_GetSrCsd(const RtcRegType *obj)
{
    return ((obj->SR & RTC_SR_CSD_MASK) >> RTC_SR_CSD_SHIFT);
}

/*! \brief Sets the Time New Config Sync Done Enable
 *
 * This function gets the current Time New Config Sync Done Enable.
 * when new config done, software should set this bit, but return 0 when software read now.
 * this bit would be 1 when the new config sync done. Its means software can enable RTC again.
 *
 * \param[in] obj : pointer to RTC register instance
 * \return Time New Config Sync Done Enable
 *         - 0b : Synchronization of New Config is Ongoing, Re-enable RTC is not allowed.
 *         - 1b : Synchronization of New Config is Done, Re-enable RTC is allowed.
 */
__attribute__((always_inline)) static inline void RtcReg_SetSrCsd(RtcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SR;

    tmp &= ~RTC_SR_CSD_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RTC_SR_CSD_SHIFT)) & RTC_SR_CSD_MASK);
    obj->SR = tmp;
}

/*! \brief Gets the Time Alarm Flag
 *
 * This function gets the current Time Alarm Flag.
 * Time alarm flag is set when the TAR[TAR] equals the TSR[TSR] and the TSR[TSR] increments.
 * This bit is cleared by writing the TAR register.
 *
 * \param[in] obj : pointer to RTC register instance
 * \return Time Alarm Flag
 *         - 0b : Time alarm has not occurred.
 *         - 1b : Time alarm has occurred.
 */
__attribute__((always_inline)) static inline uint8_t RtcReg_GetSrTaf(const RtcRegType *obj)
{
    return ((obj->SR & RTC_SR_TAF_MASK) >> RTC_SR_TAF_SHIFT);
}

/*! \brief Gets the Time Overflow Flag
 *
 * This function gets the current Time Overflow Flag.
 * Time overflow flag is set when the time counter is enabled and overflows.
 * This bit is cleared by writing the TSR register when the time counter is disabled.
 * When this bit set, both counters keep incrementing so as TCE is set.
 *
 * \param[in] obj : pointer to RTC register instance
 * \return Time Overflow Flag
 *         - 0b : Time overflow has not occurred.
 *         - 1b : Time overflow has occurred and time counter is read as zero
 */
__attribute__((always_inline)) static inline uint8_t RtcReg_GetSrTof(const RtcRegType *obj)
{
    return ((obj->SR & RTC_SR_TOF_MASK) >> RTC_SR_TOF_SHIFT);
}

/*! \brief Gets the Time Invalid Flag
 *
 * This function gets the current Time Invalid Flag.
 * The time invalid flag is set on POR or software reset.
 * This bit is cleared by writing the TSR register when the time counter is disabled.
 * When this bit set, both counters keep incrementing so as TCE is set.
 *
 * \param[in] obj : pointer to RTC register instance
 * \return Time Invalid Flag
 *         - 0b : Time is valid.
 *         - 1b : Time is invalid and time counter is read as zero
 */
__attribute__((always_inline)) static inline uint8_t RtcReg_GetSrTif(const RtcRegType *obj)
{
    return ((obj->SR & RTC_SR_TIF_MASK) >> RTC_SR_TIF_SHIFT);
}

/*! \brief Gets the Lock Register Lock
 *
 * This function gets the current Lock Register Lock.
 * After being cleared, this bit can be set only by POR or software reset.
 *
 * \param[in] obj : pointer to RTC register instance
 * \return Lock Register Lock
 *         - 0b : Lock Register is locked and writes are ignored.
 *         - 1b : Lock Register is not locked and writes complete as normal.
 */
__attribute__((always_inline)) static inline uint8_t RtcReg_GetLrLrl(const RtcRegType *obj)
{
    return ((obj->LR & RTC_LR_LRL_MASK) >> RTC_LR_LRL_SHIFT);
}

/*! \brief Sets the Lock Register Lock
 *
 * This function sets the Lock Register Lock.
 * After being cleared, this bit can be set only by POR or software reset.
 *
 * \param[in] obj : pointer to RTC register instance
 * \param[in] value : the value of Lock Register Lock
 *                    - 0b : Lock Register is locked and writes are ignored.
 *                    - 1b : Lock Register is not locked and writes complete as normal.
 */
__attribute__((always_inline)) static inline void RtcReg_SetLrLrl(RtcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->LR;

    tmp &= ~RTC_LR_LRL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RTC_LR_LRL_SHIFT)) & RTC_LR_LRL_MASK);
    obj->LR = tmp;
}

/*! \brief Gets the status Register Lock
 *
 * This function gets the current status Register Lock.
 * After being cleared, this bit can be set only by POR or software reset.
 *
 * \param[in] obj : pointer to RTC register instance
 * \return status Register Lock
 *         - 0b : Status Register is locked and writes are ignored.
 *         - 1b : Status Register is not locked and writes complete as normal
 */
__attribute__((always_inline)) static inline uint8_t RtcReg_GetLrSrl(const RtcRegType *obj)
{
    return ((obj->LR & RTC_LR_SRL_MASK) >> RTC_LR_SRL_SHIFT);
}

/*! \brief Sets the status Register Lock
 *
 * This function sets the status Register Lock.
 * After being cleared, this bit can be set only by POR or software reset.
 *
 * \param[in] obj : pointer to RTC register instance
 * \param[in] value : the value of status Register Lock
 *                    - 0b : Status Register is locked and writes are ignored.
 *                    - 1b : Status Register is not locked and writes complete as normal
 */
__attribute__((always_inline)) static inline void RtcReg_SetLrSrl(RtcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->LR;

    tmp &= ~RTC_LR_SRL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RTC_LR_SRL_SHIFT)) & RTC_LR_SRL_MASK);
    obj->LR = tmp;
}

/*! \brief Gets the Control Register Lock
 *
 * This function gets the current Control Register Lock.
 * After being cleared, this bit can only be set by POR.
 *
 * \param[in] obj : pointer to RTC register instance
 * \return Control Register Lock
 *         - 0b : Control Register is locked and writes are ignored.
 *         - 1b : Control Register is not locked and writes complete as normal.
 */
__attribute__((always_inline)) static inline uint8_t RtcReg_GetLrCrl(const RtcRegType *obj)
{
    return ((obj->LR & RTC_LR_CRL_MASK) >> RTC_LR_CRL_SHIFT);
}

/*! \brief Sets the Control Register Lock
 *
 * This function sets the Control Register Lock.
 * After being cleared, this bit can only be set by POR.
 *
 * \param[in] obj : pointer to RTC register instance
 * \param[in] value : the value of Control Register Lock
 *                    - 0b : Control Register is locked and writes are ignored.
 *                    - 1b : Control Register is not locked and writes complete as normal.
 */
__attribute__((always_inline)) static inline void RtcReg_SetLrCrl(RtcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->LR;

    tmp &= ~RTC_LR_CRL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RTC_LR_CRL_SHIFT)) & RTC_LR_CRL_MASK);
    obj->LR = tmp;
}

/*! \brief Gets the Timer Seconds Interrupt Configuration
 *
 * This function gets the current Timer Seconds Interrupt Configuration.
 * Configures the frequency of the RTC Seconds interrupt and the RTC_CLKOUT prescaler output.
 * This field should only be altered when TSIE is clear.
 *
 * \param[in] obj : pointer to RTC register instance
 * \return Timer Seconds Interrupt Configuration
 *         - 000b : 1 Hz.
 *         - 001b : 2 Hz.
 *         - 010b : 4 Hz.
 *         - 011b : 8 Hz.
 *         - 100b : 16 Hz.
 *         - 101b : 32 Hz.
 *         - 110b : 64 Hz.
 *         - 111b : 128 Hz
 */
__attribute__((always_inline)) static inline uint8_t RtcReg_GetIerTsic(const RtcRegType *obj)
{
    return ((obj->IER & RTC_IER_TSIC_MASK) >> RTC_IER_TSIC_SHIFT);
}

/*! \brief Sets the Timer Seconds Interrupt Configuration
 *
 * This function sets the Timer Seconds Interrupt Configuration.
 * Configures the frequency of the RTC Seconds interrupt and the RTC_CLKOUT prescaler output.
 * This field should only be altered when TSIE is clear.
 *
 * \param[in] obj : pointer to RTC register instance
 * \param[in] value : the value of Timer Seconds Interrupt Configuration
 *                    - 000b : 1 Hz.
 *                    - 001b : 2 Hz.
 *                    - 010b : 4 Hz.
 *                    - 011b : 8 Hz.
 *                    - 100b : 16 Hz.
 *                    - 101b : 32 Hz.
 *                    - 110b : 64 Hz.
 *                    - 111b : 128 Hz
 */
__attribute__((always_inline)) static inline void RtcReg_SetIerTsic(RtcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->IER;

    tmp &= ~RTC_IER_TSIC_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RTC_IER_TSIC_SHIFT)) & RTC_IER_TSIC_MASK);
    obj->IER = tmp;
}

/*! \brief Gets the Time Seconds Interrupt Enable
 *
 * This function gets the current Time Seconds Interrupt Enable.
 * The seconds interrupt is an edge-sensitive interrupt with a dedicated interrupt vector.
 * It is generated at least once a second and requires no software overhead (there is no corresponding status flag to clear).
 * The frequency of the seconds interrupt is configured by TSIC.
 *
 * \param[in] obj : pointer to RTC register instance
 * \return Time Seconds Interrupt Enable
 *         - 0b : Seconds interrupt is disabled.
 *         - 1b : Seconds interrupt is enabled.
 */
__attribute__((always_inline)) static inline uint8_t RtcReg_GetIerTsie(const RtcRegType *obj)
{
    return ((obj->IER & RTC_IER_TSIE_MASK) >> RTC_IER_TSIE_SHIFT);
}

/*! \brief Sets the Time Seconds Interrupt Enable
 *
 * This function sets the Time Seconds Interrupt Enable.
 * The seconds interrupt is an edge-sensitive interrupt with a dedicated interrupt vector.
 * It is generated at least once a second and requires no software overhead (there is no corresponding status flag to clear).
 * The frequency of the seconds interrupt is configured by TSIC.
 *
 * \param[in] obj : pointer to RTC register instance
 * \param[in] value : the value of Time Seconds Interrupt Enable
 *                    - 0b : Seconds interrupt is disabled.
 *                    - 1b : Seconds interrupt is enabled.
 */
__attribute__((always_inline)) static inline void RtcReg_SetIerTsie(RtcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->IER;

    tmp &= ~RTC_IER_TSIE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RTC_IER_TSIE_SHIFT)) & RTC_IER_TSIE_MASK);
    obj->IER = tmp;
}

/*! \brief Gets the Time Alarm Interrupt Enable
 *
 * This function gets the current Time Alarm Interrupt Enable.
 *
 * \param[in] obj : pointer to RTC register instance
 * \return Time Alarm Interrupt Enable
 *         - 0b : Time alarm flag does not generate an interrupt.
 *         - 1b : Time alarm flag does generate an interrupt.
 */
__attribute__((always_inline)) static inline uint8_t RtcReg_GetIerTaie(const RtcRegType *obj)
{
    return ((obj->IER & RTC_IER_TAIE_MASK) >> RTC_IER_TAIE_SHIFT);
}

/*! \brief Sets the Time Alarm Interrupt Enable
 *
 * This function sets the Time Alarm Interrupt Enable.
 *
 * \param[in] obj : pointer to RTC register instance
 * \param[in] value : the value of Time Alarm Interrupt Enable
 *                    - 0b : Time alarm flag does not generate an interrupt.
 *                    - 1b : Time alarm flag does generate an interrupt.
 */
__attribute__((always_inline)) static inline void RtcReg_SetIerTaie(RtcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->IER;

    tmp &= ~RTC_IER_TAIE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RTC_IER_TAIE_SHIFT)) & RTC_IER_TAIE_MASK);
    obj->IER = tmp;
}

/*! \brief Gets the Time Overflow Interrupt Enable
 *
 * This function gets the current Time Overflow Interrupt Enable.
 *
 * \param[in] obj : pointer to RTC register instance
 * \return Time Overflow Interrupt Enable
 *         - 0b : Time overflow flag does not generate an interrupt.
 *         - 1b : Time overflow flag does generate an interrupt.
 */
__attribute__((always_inline)) static inline uint8_t RtcReg_GetIerTioe(const RtcRegType *obj)
{
    return ((obj->IER & RTC_IER_TIOE_MASK) >> RTC_IER_TIOE_SHIFT);
}

/*! \brief Sets the Time Overflow Interrupt Enable
 *
 * This function sets the Time Overflow Interrupt Enable.
 *
 * \param[in] obj : pointer to RTC register instance
 * \param[in] value : the value of Time Overflow Interrupt Enable
 *                    - 0b : Time overflow flag does not generate an interrupt.
 *                    - 1b : Time overflow flag does generate an interrupt.
 */
__attribute__((always_inline)) static inline void RtcReg_SetIerTioe(RtcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->IER;

    tmp &= ~RTC_IER_TIOE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << RTC_IER_TIOE_SHIFT)) & RTC_IER_TIOE_MASK);
    obj->IER = tmp;
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _RTC_REG_H_ */
