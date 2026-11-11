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

#ifndef _ADC_REG_H_
#define _ADC_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the ADC Registers
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

#define ADC_REG_LOCK_KEY            (0x0U)
#define ADC_REG_UNLOCK_KEY          (0xA5D2C3C3U)

/* Number of SC register for every ADC instance */
#define ADC_REG_SC_COUNT            (24U)
#define ADC_REG_R_COUNT             (24U)

/* CFG1 Bit Fields */
#define ADC_CFG1_WITHOUT_W1C_MASK   (0xFFFFFEFFu)
#define ADC_CFG1_CLRLTRG_MASK       (0x100u)
#define ADC_CFG1_CLRLTRG_SHIFT      (8u)
#define ADC_CFG1_CLRLTRG_WIDTH      (1u)
#define ADC_CFG1_MODE_MASK          (0x03u)
#define ADC_CFG1_MODE_SHIFT         (0u)
#define ADC_CFG1_MODE_WIDTH         (2u)

/* CFG2 Bit Fields */
#define ADC_CFG2_LEN_PWR_ON_MASK    (0x3F0000u)
#define ADC_CFG2_LEN_PWR_ON_SHIFT   (16u)
#define ADC_CFG2_LEN_PWR_ON_WIDTH   (6u)
#define ADC_CFG2_LEN_SMPL_1ST_MASK  (0xFF00u)
#define ADC_CFG2_LEN_SMPL_1ST_SHIFT (8u)
#define ADC_CFG2_LEN_SMPL_1ST_WIDTH (8u)
#define ADC_CFG2_LEN_SMPL_MASK      (0xFFu)
#define ADC_CFG2_LEN_SMPL_SHIFT     (0u)
#define ADC_CFG2_LEN_SMPL_WIDTH     (8u)

/* CV1 Bit Fields */
#define ADC_CV1_CV_MASK             (0xFFFFu)
#define ADC_CV1_CV_SHIFT            (0u)
#define ADC_CV1_CV_WIDTH            (16u)
#define ADC_CV2_CV_MASK             (0xFFFFu)
#define ADC_CV2_CV_SHIFT            (0u)
#define ADC_CV2_CV_WIDTH            (16u)

/* SC2 Bit Fields */
#define ADC_SC2_WITHOUT_W1C_MASK    (0xFFFFFFu)
#define ADC_SC2_TRGSTERR_MASK       (0xF000000u)
#define ADC_SC2_TRGSTERR_SHIFT      (24u)
#define ADC_SC2_TRGSTERR_WIDTH      (4u)
#define ADC_SC2_TRGSTLAT_MASK       (0xF0000u)
#define ADC_SC2_TRGSTLAT_SHIFT      (16u)
#define ADC_SC2_TRGSTLAT_WIDTH      (4u)
#define ADC_SC2_TRGPRNUM_MASK       (0x6000u)
#define ADC_SC2_TRGPRNUM_SHIFT      (13u)
#define ADC_SC2_TRGPRNUM_WIDTH      (2u)
#define ADC_SC2_ADACT_MASK          (0x80u)
#define ADC_SC2_ADACT_SHIFT         (7u)
#define ADC_SC2_ADACT_WIDTH         (1u)
#define ADC_SC2_ADTRG_MASK          (0x40u)
#define ADC_SC2_ADTRG_SHIFT         (6u)
#define ADC_SC2_ADTRG_WIDTH         (1u)
#define ADC_SC2_ACFE_MASK           (0x20u)
#define ADC_SC2_ACFE_SHIFT          (5u)
#define ADC_SC2_ACFE_WIDTH          (1u)
#define ADC_SC2_ACFGT_MASK          (0x10u)
#define ADC_SC2_ACFGT_SHIFT         (4u)
#define ADC_SC2_ACFGT_WIDTH         (1u)
#define ADC_SC2_ACREN_MASK          (0x08u)
#define ADC_SC2_ACREN_SHIFT         (3u)
#define ADC_SC2_ACREN_WIDTH         (1u)
#define ADC_SC2_DMAEN_MASK          (0x04u)
#define ADC_SC2_DMAEN_SHIFT         (2u)
#define ADC_SC2_DMAEN_WIDTH         (1u)
#define ADC_SC2_REFSEL_MASK         (0x01u)
#define ADC_SC2_REFSEL_SHIFT        (0u)
#define ADC_SC2_REFSEL_WIDTH        (1u)

/* SC3 Bit Fields */
#define ADC_SC3_ADC_PD_MASK         (0x10000u)
#define ADC_SC3_ADC_PD_SHIFT        (16u)
#define ADC_SC3_ADC_PD_WIDTH        (1u)
#define ADC_SC3_STSEL_MASK          (0x3000u)
#define ADC_SC3_STSEL_SHIFT         (12u)
#define ADC_SC3_STSEL_WIDTH         (2u)
#define ADC_SC3_STVCM_EN_MASK       (0x800u)
#define ADC_SC3_STVCM_EN_SHIFT      (11u)
#define ADC_SC3_STVCM_EN_WIDTH      (1u)
#define ADC_SC3_CALICAP_SEL_MASK    (0x300u)
#define ADC_SC3_CALICAP_SEL_SHIFT   (8u)
#define ADC_SC3_CALICAP_SEL_WIDTH   (2u)
#define ADC_SC3_TEST_MODE_MASK      (0x80u)
#define ADC_SC3_TEST_MODE_SHIFT     (7u)
#define ADC_SC3_TEST_MODE_WIDTH     (1u)
#define ADC_SC3_CAL_MODE_MASK       (0x40u)
#define ADC_SC3_CAL_MODE_SHIFT      (6u)
#define ADC_SC3_CAL_MODE_WIDTH      (1u)
#define ADC_SC3_CAL_GE_MASK         (0x20u)
#define ADC_SC3_CAL_GE_SHIFT        (5u)
#define ADC_SC3_CAL_GE_WIDTH        (1u)
#define ADC_SC3_CAL_OFS_MASK        (0x10u)
#define ADC_SC3_CAL_OFS_SHIFT       (4u)
#define ADC_SC3_CAL_OFS_WIDTH       (1u)
#define ADC_SC3_ADCO_MASK           (0x08u)
#define ADC_SC3_ADCO_SHIFT          (3u)
#define ADC_SC3_ADCO_WIDTH          (1u)
#define ADC_SC3_AVGE_MASK           (0x04u)
#define ADC_SC3_AVGE_SHIFT          (2u)
#define ADC_SC3_AVGE_WIDTH          (1u)
#define ADC_SC3_AVGS_MASK           (0x03u)
#define ADC_SC3_AVGS_SHIFT          (0u)
#define ADC_SC3_AVGS_WIDTH          (2u)

/* OFS Bit Fields */
#define ADC_OFS_SUB_OFS_MASK        (0x10000u)
#define ADC_OFS_SUB_OFS_SHIFT       (16u)
#define ADC_OFS_SUB_OFS_WIDTH       (1u)
#define ADC_OFS_VAL_OFS_MASK        (0x7FFu)
#define ADC_OFS_VAL_OFS_SHIFT       (0u)
#define ADC_OFS_VAL_OFS_WIDTH       (11u)

/* GE Bit Fields */
#define ADC_GE_VAL_GE_MASK          (0xFFFu)
#define ADC_GE_VAL_GE_SHIFT         (0u)
#define ADC_GE_VAL_GE_WIDTH         (12u)

/* USRK Bit Fields */
#define ADC_USRK_USER_KEY_MASK      (0xFFFFFFFFu)
#define ADC_USRK_USER_KEY_SHIFT     (0u)
#define ADC_USRK_USER_KEY_WIDTH     (32u)

/* SC Bit Fields */
#define ADC_SC_COCO_MASK            (0x80u)
#define ADC_SC_COCO_SHIFT           (7u)
#define ADC_SC_COCO_WIDTH           (1u)
#define ADC_SC_AIEN_MASK            (0x40u)
#define ADC_SC_AIEN_SHIFT           (6u)
#define ADC_SC_AIEN_WIDTH           (1u)
#define ADC_SC_ADCH_MASK            (0x1Fu)
#define ADC_SC_ADCH_SHIFT           (0u)
#define ADC_SC_ADCH_WIDTH           (5u)

/* R Bit Fields */
#define ADC_R_DATA_MASK             (0x3FFFu)
#define ADC_R_DATA_SHIFT            (0u)
#define ADC_R_DATA_WIDTH            (14u)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief The definition of ADC registers
 */
typedef struct _AdcRegType_
{
    volatile uint32_t       CFG1;                 /*!< Configs Register 1, Offset: 0000H */
    volatile uint32_t       CFG2;                 /*!< Configs Register 2, Offset: 0004H */
    volatile uint32_t       CV1;                  /*!< Compare Value 1, Offset: 0008H */
    volatile uint32_t       CV2;                  /*!< Compare Value 2, Offset: 000CH */
    volatile uint32_t       SC2;                  /*!< Status and Control Register 2, Offset: 0010H */
    volatile uint32_t       SC3;                  /*!< Status and Control Register 3, Offset: 0014H */
    volatile uint32_t       OFS;                  /*!< Offset Register, Offset: 0018H */
    volatile uint32_t       GE;                   /*!< Error Gain Register, Offset: 001CH */
    volatile uint32_t       USRK;                 /*!< User Key Register, Offset: 0020H */
    uint32_t                Reserved0[55];        /*!< reserverd block, Offset: 0024H */
    volatile uint32_t       SC[ADC_REG_SC_COUNT]; /*!< Status and Control Register, Offset: 0100H */
    uint32_t                Reserved1[8];         /*!< reserverd block, Offset: 0160H */
    const volatile uint32_t R[ADC_REG_R_COUNT];   /*!< Conversion Result Register, Offset: 0180H */
} AdcRegType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Sets the Clear Latch Trigger in Trigger Handler Block
 *
 * This function sets the Clear Latch Trigger in Trigger Handler Block.
 * Writing a 1 to this field clears all the latched triggers inside the trigger
 * handler except the one under processing. Writing 0 has no effect. This is a
 * write-only-one bit that self-clears immediately
 *
 * \param[in] obj : pointer to ADC register instance
 * \param[in] value : the value of Clear Latch Trigger in Trigger Handler Block
 */
__attribute__((always_inline)) static inline void AdcReg_ClrTrg(AdcRegType *obj)
{
    uint32_t tmp = obj->CFG1;

    tmp &= ~ADC_CFG1_CLRLTRG_MASK;
    tmp |= (((uint32_t)(((uint32_t)(1u)) << ADC_CFG1_CLRLTRG_SHIFT)) & ADC_CFG1_CLRLTRG_MASK);
    obj->CFG1 = tmp;
}

/*! \brief Gets the Conversion Mode Selection
 *
 * This function gets the current Conversion Mode Selection.
 * Selects the ADC resolution.
 *
 * \param[in] obj : pointer to ADC register instance
 * \return Conversion Mode Selection
 *         - 00b : 8-bit conversion.
 *         - x1b : 12-bit conversion.
 *         - 10b : 10-bit conversion.
 */
__attribute__((always_inline)) static inline uint8_t AdcReg_GetCfg1Mode(const AdcRegType *obj)
{
    return ((obj->CFG1 & ADC_CFG1_MODE_MASK) >> ADC_CFG1_MODE_SHIFT);
}

/*! \brief Sets the Conversion Mode Selection
 *
 * This function sets the Conversion Mode Selection.
 * Selects the ADC resolution.
 *
 * \param[in] obj : pointer to ADC register instance
 * \param[in] value : the value of Conversion Mode Selection
 *                    - 00b : 8-bit conversion.
 *                    - x1b : 12-bit conversion.
 *                    - 10b : 10-bit conversion.
 */
__attribute__((always_inline)) static inline void AdcReg_SetCfg1Mode(AdcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CFG1;
    tmp &= ADC_CFG1_WITHOUT_W1C_MASK;
    tmp &= ~ADC_CFG1_MODE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ADC_CFG1_MODE_SHIFT)) & ADC_CFG1_MODE_MASK);
    obj->CFG1 = tmp;
}

/*! \brief Gets the POWER On Sample Delay Config
 *
 * This function gets the current POWER On Sample Delay Config.
 * After ADC power on, this register configs delay time before sampling is
 * started. The delay time is (LEN_PWR_ON+1)*clk_adc
 *
 * \param[in] obj : pointer to ADC register instance
 * \return POWER On Sample Delay Config
 */
__attribute__((always_inline)) static inline uint8_t AdcReg_GetCfg2LenPwrOn(const AdcRegType *obj)
{
    return ((obj->CFG2 & ADC_CFG2_LEN_PWR_ON_MASK) >> ADC_CFG2_LEN_PWR_ON_SHIFT);
}

/*! \brief Sets the POWER On Sample Delay Config
 *
 * This function sets the POWER On Sample Delay Config.
 * After ADC power on, this register configs delay time before sampling is
 * started. The delay time is (LEN_PWR_ON+1)*clk_adc
 *
 * \param[in] obj : pointer to ADC register instance
 * \param[in] value : the value of POWER On Sample Delay Config
 */
__attribute__((always_inline)) static inline void AdcReg_SetCfg2LenPwrOn(AdcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CFG2;

    tmp &= ~ADC_CFG2_LEN_PWR_ON_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ADC_CFG2_LEN_PWR_ON_SHIFT)) & ADC_CFG2_LEN_PWR_ON_MASK);
    obj->CFG2 = tmp;
}

/*! \brief Gets the First Sample Delay Config
 *
 * This function gets the current First Sample Delay Config.
 * After ADC power on or channel changes, the first sampling time needs to be
 * LEN_SMPL added by LEN_SMPL_1ST, so the actual sample time is
 * (LEN_SMPL_1ST+LEN_SMPL+1)*clk_adc
 *
 * \param[in] obj : pointer to ADC register instance
 * \return First Sample Delay Config
 */
__attribute__((always_inline)) static inline uint8_t AdcReg_GetCfg2LenSmpl1st(const AdcRegType *obj)
{
    return ((obj->CFG2 & ADC_CFG2_LEN_SMPL_1ST_MASK) >> ADC_CFG2_LEN_SMPL_1ST_SHIFT);
}

/*! \brief Sets the First Sample Delay Config
 *
 * This function sets the First Sample Delay Config.
 * After ADC power on or channel changes, the first sampling time needs to be
 * LEN_SMPL added by LEN_SMPL_1ST, so the actual sample time is
 * (LEN_SMPL_1ST+LEN_SMPL+1)*clk_adc
 *
 * \param[in] obj : pointer to ADC register instance
 * \param[in] value : the value of First Sample Delay Config
 */
__attribute__((always_inline)) static inline void AdcReg_SetCfg2LenSmpl1st(AdcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CFG2;

    tmp &= ~ADC_CFG2_LEN_SMPL_1ST_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ADC_CFG2_LEN_SMPL_1ST_SHIFT)) & ADC_CFG2_LEN_SMPL_1ST_MASK);
    obj->CFG2 = tmp;
}

/*! \brief Gets the ADC Sampling Time
 *
 * This function gets the current ADC Sampling Time.
 * Configs ADC Sampling time, the actual time is (LEN_SMPL+1)*clk_adc
 *
 * \param[in] obj : pointer to ADC register instance
 * \return ADC Sampling Time
 */
__attribute__((always_inline)) static inline uint8_t AdcReg_GetCfg2LenSmpl(const AdcRegType *obj)
{
    return ((obj->CFG2 & ADC_CFG2_LEN_SMPL_MASK) >> ADC_CFG2_LEN_SMPL_SHIFT);
}

/*! \brief Sets the ADC Sampling Time
 *
 * This function sets the ADC Sampling Time.
 * Configs ADC Sampling time, the actual time is (LEN_SMPL+1)*clk_adc
 *
 * \param[in] obj : pointer to ADC register instance
 * \param[in] value : the value of ADC Sampling Time
 */
__attribute__((always_inline)) static inline void AdcReg_SetCfg2LenSmpl(AdcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CFG2;

    tmp &= ~ADC_CFG2_LEN_SMPL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ADC_CFG2_LEN_SMPL_SHIFT)) & ADC_CFG2_LEN_SMPL_MASK);
    obj->CFG2 = tmp;
}

/*! \brief Gets the compare value 1
 *
 * This function gets the current compare value 1.
 *
 * \param[in] obj : pointer to ADC register instance
 * \return compare value 1
 */
__attribute__((always_inline)) static inline uint16_t AdcReg_GetCv1Cv(const AdcRegType *obj)
{
    return ((obj->CV1 & ADC_CV1_CV_MASK) >> ADC_CV1_CV_SHIFT);
}

/*! \brief Sets the compare value 1
 *
 * This function sets the compare value 1.
 *
 * \param[in] obj : pointer to ADC register instance
 * \param[in] value : the value of compare value 1
 */
__attribute__((always_inline)) static inline void AdcReg_SetCv1Cv(AdcRegType *obj, uint16_t value)
{
    uint32_t tmp = obj->CV1;

    tmp &= ~ADC_CV1_CV_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ADC_CV1_CV_SHIFT)) & ADC_CV1_CV_MASK);
    obj->CV1 = tmp;
}

/*! \brief Gets the compare value 2
 *
 * This function gets the current compare value 2.
 *
 * \param[in] obj : pointer to ADC register instance
 * \return compare value 2
 */
__attribute__((always_inline)) static inline uint16_t AdcReg_GetCv2Cv(const AdcRegType *obj)
{
    return ((obj->CV2 & ADC_CV2_CV_MASK) >> ADC_CV2_CV_SHIFT);
}

/*! \brief Sets the compare value 2
 *
 * This function sets the compare value 2.
 *
 * \param[in] obj : pointer to ADC register instance
 * \param[in] value : the value of compare value 2
 */
__attribute__((always_inline)) static inline void AdcReg_SetCv2Cv(AdcRegType *obj, uint16_t value)
{
    uint32_t tmp = obj->CV2;

    tmp &= ~ADC_CV2_CV_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ADC_CV2_CV_SHIFT)) & ADC_CV2_CV_MASK);
    obj->CV2 = tmp;
}

/*! \brief Gets the Error in Multiplexed Trigger Request
 *
 * This function gets the current Error in Multiplexed Trigger Request.
 * Each of these error signals indicate that a multiplexed hardware trigger
 * request from a source has been missed, in which case the request has already
 * been latched or is being serviced. Each bit in this field can be cleared by
 * writing a 1 to it, and each bit corresponds to an individual trigger request:
 * - Bit 24 corresponds to trigger request 0
 * - Bit 25 corresponds to trigger request 1
 * - Bit 26 corresponds to trigger request 2
 * - Bit 27 corresponds to trigger request 3
 * The read value of each bit in this field is interpreted individually
 *
 * \param[in] obj : pointer to ADC register instance
 * \return Error in Multiplexed Trigger Request
 *         - 0b : No error has occurred
 *         - 1b : An error has occurred
 */
__attribute__((always_inline)) static inline uint8_t AdcReg_GetSc2TrgStErr(const AdcRegType *obj)
{
    return ((obj->SC2 & ADC_SC2_TRGSTERR_MASK) >> ADC_SC2_TRGSTERR_SHIFT);
}

/*! \brief Sets the Error in Multiplexed Trigger Request
 *
 * This function sets the Error in Multiplexed Trigger Request.
 * Each of these error signals indicate that a multiplexed hardware trigger
 * request from a source has been missed, in which case the request has already
 * been latched or is being serviced. Each bit in this field can be cleared by
 * writing a 1 to it, and each bit corresponds to an individual trigger request:
 * - Bit 24 corresponds to trigger request 0
 * - Bit 25 corresponds to trigger request 1
 * - Bit 26 corresponds to trigger request 2
 * - Bit 27 corresponds to trigger request 3
 * The read value of each bit in this field is interpreted individually
 *
 * \param[in] obj : pointer to ADC register instance
 * \param[in] value : the value of Error in Multiplexed Trigger Request
 *                    - 0b : No error has occurred
 *                    - 1b : An error has occurred
 */
__attribute__((always_inline)) static inline void AdcReg_SetSc2TrgStErr(AdcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SC2;

    tmp &= ~ADC_SC2_TRGSTERR_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ADC_SC2_TRGSTERR_SHIFT)) & ADC_SC2_TRGSTERR_MASK);
    obj->SC2 = tmp;
}

/*! \brief Gets the Trigger Status
 *
 * This function gets the current Trigger Status.
 * Each of these status bits indicate that a multiplexed hardware trigger
 * request from a source has been latched. Each bit in this field corresponds to
 * an individual trigger request:
 * - Bit 16 corresponds to trigger request 0
 * - Bit 17 corresponds to trigger request 1
 * - Bit 18 corresponds to trigger request 2
 * - Bit 19 corresponds to trigger request 3
 * The read value of each bit in this field is interpreted individually
 *
 * \param[in] obj : pointer to ADC register instance
 * \return Trigger Status
 *         - 0b : No trigger request has been latched
 *         - 1b : A trigger request has been latched
 */
__attribute__((always_inline)) static inline uint8_t AdcReg_GetSc2TrgStLat(const AdcRegType *obj)
{
    return ((obj->SC2 & ADC_SC2_TRGSTLAT_MASK) >> ADC_SC2_TRGSTLAT_SHIFT);
}

/*! \brief Gets the Trigger Process Number
 *
 * This function gets the current Trigger Process Number.
 * Indicates the trigger number that is being serviced.
 * This has to be qualified with the 1-bit value for the corresponding trigger
 * latch status.
 * - TRGPRNUM=00 is valid only if TRGSTLAT[16]=1
 * - TRGPRNUM=01 is valid only if TRGSTLAT[17]=1
 * - TRGPRNUM=10 is valid only if TRGSTLAT[18]=1
 * - TRGPRNUM=11 is valid only if TRGSTLAT[19]=1
 *
 * \note Occasionally there may be a mismatch between the TRGPRNUM and the ideal
 * trigger to be selected as per TRGSTLAT by Round Robin algorithm. This happens
 * because of different operating clocks of the TRGSTLAT and the hardware logic.
 * The TRGSTLAT is updated first with arrival of triggers, and then it is
 * synchronized into the hardware clock. So, the hardware uses a delayed version
 * of TRGSTLAT. Any trigger that arrives during the synchronization time is not
 * presented to hardware immediately, but shows in TRGSTLAT
 *
 * \param[in] obj : pointer to ADC register instance
 * \return Trigger Process Number
 */
__attribute__((always_inline)) static inline uint8_t AdcReg_GetSc2TrgPrNum(const AdcRegType *obj)
{
    return ((obj->SC2 & ADC_SC2_TRGPRNUM_MASK) >> ADC_SC2_TRGPRNUM_SHIFT);
}

/*! \brief Gets the Conversion Active
 *
 * This function gets the current Conversion Active.
 * Indicates that a conversion or hardware averaging is in progress.
 * ADACT is set when a conversion is initiated and cleared when a conversion is
 * completed or aborted.
 *
 * \param[in] obj : pointer to ADC register instance
 * \return Conversion Active
 *         - 0b : Conversion not in progress.
 *         - 1b : Conversion in progress.
 */
__attribute__((always_inline)) static inline uint8_t AdcReg_GetSc2AdAct(const AdcRegType *obj)
{
    return ((obj->SC2 & ADC_SC2_ADACT_MASK) >> ADC_SC2_ADACT_SHIFT);
}

/*! \brief Gets the Conversion Trigger state
 *
 * This function gets the current Conversion Trigger state.
 *
 * \param[in] obj : pointer to ADC register instance
 * \return Conversion Trigger Select
 *         - 0b : trigger disable.
 *         - 1b : trigger enable.
 */
__attribute__((always_inline)) static inline uint8_t AdcReg_GetSc2AdTrg(const AdcRegType *obj)
{
    return ((obj->SC2 & ADC_SC2_ADTRG_MASK) >> ADC_SC2_ADTRG_SHIFT);
}

/*! \brief Sets the Conversion Trigger state
 *
 * \param[in] obj : pointer to ADC register instance
 * \param[in] value : the value of Conversion Trigger state select
 *                    - 0b : trigger disable.
 *                    - 1b : trigger enable.
 */
__attribute__((always_inline)) static inline void AdcReg_SetSc2AdTrg(AdcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SC2;

    tmp &= ADC_SC2_WITHOUT_W1C_MASK;
    tmp &= ~ADC_SC2_ADTRG_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ADC_SC2_ADTRG_SHIFT)) & ADC_SC2_ADTRG_MASK);
    obj->SC2 = tmp;
}

/*! \brief Gets the Compare Function Enable
 *
 * This function gets the current Compare Function Enable.
 * Enables the compare function.
 *
 * \param[in] obj : pointer to ADC register instance
 * \return Compare Function Enable
 *         - 0b : Compare function disabled.
 *         - 1b : Compare function enabled.
 */
__attribute__((always_inline)) static inline uint8_t AdcReg_GetSc2Acfe(const AdcRegType *obj)
{
    return ((obj->SC2 & ADC_SC2_ACFE_MASK) >> ADC_SC2_ACFE_SHIFT);
}

/*! \brief Sets the Compare Function Enable
 *
 * This function sets the Compare Function Enable.
 * Enables the compare function.
 *
 * \param[in] obj : pointer to ADC register instance
 * \param[in] value : the value of Compare Function Enable
 *                    - 0b : Compare function disabled.
 *                    - 1b : Compare function enabled.
 */
__attribute__((always_inline)) static inline void AdcReg_SetSc2Acfe(AdcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SC2;

    tmp &= ADC_SC2_WITHOUT_W1C_MASK;
    tmp &= ~ADC_SC2_ACFE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ADC_SC2_ACFE_SHIFT)) & ADC_SC2_ACFE_MASK);
    obj->SC2 = tmp;
}

/*! \brief Gets the Compare Function Greater Than Enable
 *
 * This function gets the current Compare Function Greater Than Enable.
 * Configures the compare function to check the conversion result relative to
 * CV1 and CV2 based upon the value of ACREN. ACFE must be set for ACFGT to have
 * any effect.
 *
 * \param[in] obj : pointer to ADC register instance
 * \return Compare Function Greater Than Enable
 */
__attribute__((always_inline)) static inline uint8_t AdcReg_GetSc2AcFgt(const AdcRegType *obj)
{
    return ((obj->SC2 & ADC_SC2_ACFGT_MASK) >> ADC_SC2_ACFGT_SHIFT);
}

/*! \brief Sets the Compare Function Greater Than Enable
 *
 * This function sets the Compare Function Greater Than Enable.
 * Configures the compare function to check the conversion result relative to
 * CV1 and CV2 based upon the value of ACREN. ACFE must be set for ACFGT to have
 * any effect.
 *
 * \param[in] obj : pointer to ADC register instance
 * \param[in] value : the value of Compare Function Greater Than Enable
 */
__attribute__((always_inline)) static inline void AdcReg_SetSc2AcFgt(AdcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SC2;

    tmp &= ADC_SC2_WITHOUT_W1C_MASK;
    tmp &= ~ADC_SC2_ACFGT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ADC_SC2_ACFGT_SHIFT)) & ADC_SC2_ACFGT_MASK);
    obj->SC2 = tmp;
}

/*! \brief Gets the Compare Function Range Enable
 *
 * This function gets the current Compare Function Range Enable.
 * Configures the compare function to check if the conversion result of the
 * input being monitored is either between or outside the range formed by CV1
 * and CV2 determined by the value of ACFGT. ACFE must be set for ACFGT to have
 * any effect.
 *
 * \param[in] obj : pointer to ADC register instance
 * \return Compare Function Range Enable
 */
__attribute__((always_inline)) static inline uint8_t AdcReg_GetSc2AcREn(const AdcRegType *obj)
{
    return ((obj->SC2 & ADC_SC2_ACREN_MASK) >> ADC_SC2_ACREN_SHIFT);
}

/*! \brief Sets the Compare Function Range Enable
 *
 * This function sets the Compare Function Range Enable.
 * Configures the compare function to check if the conversion result of the
 * input being monitored is either between or outside the range formed by CV1
 * and CV2 determined by the value of ACFGT. ACFE must be set for ACFGT to have
 * any effect.
 *
 * \param[in] obj : pointer to ADC register instance
 * \param[in] value : the value of Compare Function Range Enable
 */
__attribute__((always_inline)) static inline void AdcReg_SetSc2AcREn(AdcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SC2;

    tmp &= ADC_SC2_WITHOUT_W1C_MASK;
    tmp &= ~ADC_SC2_ACREN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ADC_SC2_ACREN_SHIFT)) & ADC_SC2_ACREN_MASK);
    obj->SC2 = tmp;
}

/*! \brief Gets the DMA Enable
 *
 * This function gets the current DMA Enable.
 *
 * \param[in] obj : pointer to ADC register instance
 * \return DMA Enable
 *         - 0b : DMA is disabled.
 *         - 1b : DMA is enabled and will assert the ADC DMA request during an
 * ADC conversion complete event, which is indicated when any SCn[COCO] flag is
 * asserted.
 */
__attribute__((always_inline)) static inline uint8_t AdcReg_GetSc2DmaEn(const AdcRegType *obj)
{
    return ((obj->SC2 & ADC_SC2_DMAEN_MASK) >> ADC_SC2_DMAEN_SHIFT);
}

/*! \brief Sets the DMA Enable
 *
 * This function sets the DMA Enable.
 *
 * \param[in] obj : pointer to ADC register instance
 * \param[in] value : the value of DMA Enable
 *                    - 0b : DMA is disabled.
 *                    - 1b : DMA is enabled and will assert the ADC DMA request
 * during an ADC conversion complete event, which is indicated when any
 * SCn[COCO] flag is asserted.
 */
__attribute__((always_inline)) static inline void AdcReg_SetSc2DmaEn(AdcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SC2;

    tmp &= ADC_SC2_WITHOUT_W1C_MASK;
    tmp &= ~ADC_SC2_DMAEN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ADC_SC2_DMAEN_SHIFT)) & ADC_SC2_DMAEN_MASK);
    obj->SC2 = tmp;
}

/*! \brief Gets the ADC VREF Select
 *
 * This function gets the current ADC VREF Select.
 *
 * \note If VDDA is selected, VDDA needs to be shorted with VREFH by hardware
 *
 * \param[in] obj : pointer to ADC register instance
 * \return ADC VREF Select
 *         - 0b : VDDA
 *         - 1b : external VREF
 */
__attribute__((always_inline)) static inline uint8_t AdcReg_GetSc2RefSel(const AdcRegType *obj)
{
    return ((obj->SC2 & ADC_SC2_REFSEL_MASK) >> ADC_SC2_REFSEL_SHIFT);
}

/*! \brief Sets the ADC VREF Select
 *
 * This function sets the ADC VREF Select.
 *
 * \note If VDDA is selected, VDDA needs to be shorted with VREFH by hardware
 *
 * \param[in] obj : pointer to ADC register instance
 * \param[in] value : the value of ADC VREF Select
 *                    - 0b : VDDA
 *                    - 1b : external VREF
 */
__attribute__((always_inline)) static inline void AdcReg_SetSc2RefSel(AdcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SC2;

    tmp &= ADC_SC2_WITHOUT_W1C_MASK;
    tmp &= ~ADC_SC2_REFSEL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ADC_SC2_REFSEL_SHIFT)) & ADC_SC2_REFSEL_MASK);

    obj->USRK = ADC_REG_UNLOCK_KEY;
    obj->SC2  = tmp;
    obj->USRK = ADC_REG_LOCK_KEY;
}

/*! \brief Gets the ADC Power Down
 *
 * This function gets the current ADC Power Down.
 *
 * \note It is recommended that powers on ADC first, and then configs other
 * registers.
 *
 * \param[in] obj : pointer to ADC register instance
 * \return ADC Power Down
 *         - 0b : power on
 *         - 1b : power down
 */
__attribute__((always_inline)) static inline uint8_t AdcReg_GetSc3AdcPD(const AdcRegType *obj)
{
    return ((obj->SC3 & ADC_SC3_ADC_PD_MASK) >> ADC_SC3_ADC_PD_SHIFT);
}

/*! \brief Sets the ADC Power Down
 *
 * This function sets the ADC Power Down.
 *
 * \note It is recommended that powers on ADC first, and then configs other
 * registers.
 *
 * \param[in] obj : pointer to ADC register instance
 * \param[in] value : the value of ADC Power Down
 *                    - 0b : power on
 *                    - 1b : power down
 */
__attribute__((always_inline)) static inline void AdcReg_SetSc3AdcPD(AdcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SC3;

    tmp &= ~ADC_SC3_ADC_PD_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ADC_SC3_ADC_PD_SHIFT)) & ADC_SC3_ADC_PD_MASK);
    obj->SC3 = tmp;
}

/*! \brief Gets the ADC Self-test Channel Select
 *
 * This function gets the current ADC Self-test Channel Select.
 *
 * \param[in] obj : pointer to ADC register instance
 * \return ADC Self-test Channel Select
 *         - 00b : AVSS
 *         - 01b : 1/8*VREF
 *         - 10b : 1/2*VREF
 *         - 11b : 7/8*VREF
 */
__attribute__((always_inline)) static inline uint8_t AdcReg_GetSc3StSel(const AdcRegType *obj)
{
    return ((obj->SC3 & ADC_SC3_STSEL_MASK) >> ADC_SC3_STSEL_SHIFT);
}

/*! \brief Sets the ADC Self-test Channel Select
 *
 * This function sets the ADC Self-test Channel Select.
 *
 * \param[in] obj : pointer to ADC register instance
 * \param[in] value : the value of ADC Self-test Channel Select
 *                    - 00b : AVSS
 *                    - 01b : 1/8*VREF
 *                    - 10b : 1/2*VREF
 *                    - 11b : 7/8*VREF
 */
__attribute__((always_inline)) static inline void AdcReg_SetSc3StSel(AdcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SC3;

    tmp &= ~ADC_SC3_STSEL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ADC_SC3_STSEL_SHIFT)) & ADC_SC3_STSEL_MASK);
    obj->USRK = ADC_REG_UNLOCK_KEY;
    obj->SC3  = tmp;
    obj->USRK = ADC_REG_LOCK_KEY;
}

/*! \brief Gets the ADC Self-test Common Mode Level Enable
 *
 * This function gets the current ADC Self-test Common Mode Level Enable.
 * This configs the common mode level enable, which is used in calibration and
 * self-test
 *
 * \param[in] obj : pointer to ADC register instance
 * \return ADC Self-test Common Mode Level Enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t AdcReg_GetSc3StVcmEn(const AdcRegType *obj)
{
    return ((obj->SC3 & ADC_SC3_STVCM_EN_MASK) >> ADC_SC3_STVCM_EN_SHIFT);
}

/*! \brief Sets the ADC Self-test Common Mode Level Enable
 *
 * This function sets the ADC Self-test Common Mode Level Enable.
 * This configs the common mode level enable, which is used in calibration and
 * self-test
 *
 * \param[in] obj : pointer to ADC register instance
 * \param[in] value : the value of ADC Self-test Common Mode Level Enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void AdcReg_SetSc3StVcmEn(AdcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SC3;

    tmp &= ~ADC_SC3_STVCM_EN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ADC_SC3_STVCM_EN_SHIFT)) & ADC_SC3_STVCM_EN_MASK);
    obj->USRK = ADC_REG_UNLOCK_KEY;
    obj->SC3  = tmp;
    obj->USRK = ADC_REG_LOCK_KEY;
}

/*! \brief Gets the ADC Calibration Resistor Select
 *
 * This function gets the current ADC Calibration Resistor Select.
 *
 * \param[in] obj : pointer to ADC register instance
 * \return ADC Calibration Resistor Select
 *         - 00b : 2*Cu
 *         - 01b : 4*Cu
 *         - 10b : 6*Cu
 *         - 11b : 8*Cu
 */
__attribute__((always_inline)) static inline uint8_t AdcReg_GetSc3CaliCapSel(const AdcRegType *obj)
{
    return ((obj->SC3 & ADC_SC3_CALICAP_SEL_MASK) >> ADC_SC3_CALICAP_SEL_SHIFT);
}

/*! \brief Sets the ADC Calibration Resistor Select
 *
 * This function sets the ADC Calibration Resistor Select.
 *
 * \param[in] obj : pointer to ADC register instance
 * \param[in] value : the value of ADC Calibration Resistor Select
 *                    - 00b : 2*Cu
 *                    - 01b : 4*Cu
 *                    - 10b : 6*Cu
 *                    - 11b : 8*Cu
 */
__attribute__((always_inline)) static inline void AdcReg_SetSc3CaliCapSel(AdcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SC3;

    tmp &= ~ADC_SC3_CALICAP_SEL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ADC_SC3_CALICAP_SEL_SHIFT)) & ADC_SC3_CALICAP_SEL_MASK);
    obj->SC3 = tmp;
}

/*! \brief Gets the Test Mode Enable
 *
 * This function gets the current Test Mode Enable.
 * Configs ADC test mode
 *
 *
 * \param[in] obj : pointer to ADC register instance
 * \return Test Mode Enable
 *         - 0b : test mode disable
 *         - 1b : test mode enable
 */
__attribute__((always_inline)) static inline uint8_t AdcReg_GetSc3TestMode(const AdcRegType *obj)
{
    return ((obj->SC3 & ADC_SC3_TEST_MODE_MASK) >> ADC_SC3_TEST_MODE_SHIFT);
}

/*! \brief Sets the Test Mode Enable
 *
 * This function sets the Test Mode Enable.
 * Configs ADC test mode
 *
 * \param[in] obj : pointer to ADC register instance
 * \param[in] value : the value of Test Mode Enable
 *                    - 0b : test mode disable
 *                    - 1b : test mode enable
 */
__attribute__((always_inline)) static inline void AdcReg_SetSc3TestMode(AdcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SC3;

    tmp &= ~ADC_SC3_TEST_MODE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ADC_SC3_TEST_MODE_SHIFT)) & ADC_SC3_TEST_MODE_MASK);
    obj->SC3 = tmp;
}

/*! \brief Gets the Calibration Mode Enable
 *
 * This function gets the current Calibration Mode Enable.
 * Configs ADC test mode
 *
 * \param[in] obj : pointer to ADC register instance
 * \return Calibration Mode Enable
 *         - 0b : calibration mode disable
 *         - 1b : calibration mode enable
 */
__attribute__((always_inline)) static inline uint8_t AdcReg_GetSc3CalMode(const AdcRegType *obj)
{
    return ((obj->SC3 & ADC_SC3_CAL_MODE_MASK) >> ADC_SC3_CAL_MODE_SHIFT);
}

/*! \brief Sets the Calibration Mode Enable
 *
 * This function sets the Calibration Mode Enable.
 * Configs ADC test mode
 *
 * \param[in] obj : pointer to ADC register instance
 * \param[in] value : the value of Calibration Mode Enable
 *                    - 0b : calibration mode disable
 *                    - 1b : calibration mode enable
 */
__attribute__((always_inline)) static inline void AdcReg_SetSc3CalMode(AdcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SC3;

    tmp &= ~ADC_SC3_CAL_MODE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ADC_SC3_CAL_MODE_SHIFT)) & ADC_SC3_CAL_MODE_MASK);
    obj->SC3 = tmp;
}

/*! \brief Gets the Gain Error Calibration Start
 *
 * This function gets the current Gain Error Calibration Start.
 * Write 1 to this bit to start gain error calibration. This bit is cleared by
 * hardware when calibration finishes.
 *
 * \param[in] obj : pointer to ADC register instance
 * \return Gain Error Calibration Start
 *         - 0b : gain error calibration is no ongoing
 *         - 1b : gain error calibration is in progress
 */
__attribute__((always_inline)) static inline uint8_t AdcReg_GetSc3CalGE(const AdcRegType *obj)
{
    return ((obj->SC3 & ADC_SC3_CAL_GE_MASK) >> ADC_SC3_CAL_GE_SHIFT);
}

/*! \brief Sets the Gain Error Calibration Start
 *
 * This function sets the Gain Error Calibration Start.
 * Write 1 to this bit to start gain error calibration. This bit is cleared by
 * hardware when calibration finishes.
 *
 * \param[in] obj : pointer to ADC register instance
 * \param[in] value : the value of Gain Error Calibration Start
 *                    - 0b : gain error calibration is no ongoing
 *                    - 1b : gain error calibration is in progress
 */
__attribute__((always_inline)) static inline void AdcReg_SetSc3CalGE(AdcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SC3;

    tmp &= ~ADC_SC3_CAL_GE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ADC_SC3_CAL_GE_SHIFT)) & ADC_SC3_CAL_GE_MASK);
    obj->SC3 = tmp;
}

/*! \brief Gets the Offset Calibration Start
 *
 * This function gets the current Offset Calibration Start.
 * Write 1 to this bit to start offset calibration. This bit is cleared by
 * hardware when calibration finishes.
 *
 * \param[in] obj : pointer to ADC register instance
 * \return Offset Calibration Start
 *         - 0b : offset calibration is no ongoing
 *         - 1b : offset calibration is in progress
 */
__attribute__((always_inline)) static inline uint8_t AdcReg_GetSc3CalOfs(const AdcRegType *obj)
{
    return ((obj->SC3 & ADC_SC3_CAL_OFS_MASK) >> ADC_SC3_CAL_OFS_SHIFT);
}

/*! \brief Sets the Offset Calibration Start
 *
 * This function sets the Offset Calibration Start.
 * Write 1 to this bit to start offset calibration. This bit is cleared by
 * hardware when calibration finishes.
 *
 * \param[in] obj : pointer to ADC register instance
 * \param[in] value : the value of Offset Calibration Start
 *                    - 0b : offset calibration is no ongoing
 *                    - 1b : offset calibration is in progress
 */
__attribute__((always_inline)) static inline void AdcReg_SetSc3CalOfs(AdcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SC3;

    tmp &= ~ADC_SC3_CAL_OFS_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ADC_SC3_CAL_OFS_SHIFT)) & ADC_SC3_CAL_OFS_MASK);
    obj->SC3 = tmp;
}

/*! \brief Gets the Continuous Conversion Enable
 *
 * This function gets the current Continuous Conversion Enable.
 * Enables continuous conversions.
 *
 * \param[in] obj : pointer to ADC register instance
 * \return Continuous Conversion Enable
 *         - 0b : One conversion will be performed (or one set of conversions,
 * if AVGE is set) after a conversion is initiated.
 *         - 1b : Continuous conversions will be performed (or continuous sets
 * of conversions, if AVGE is set) after a conversion is initiated.
 */
__attribute__((always_inline)) static inline uint8_t AdcReg_GetSc3Adco(const AdcRegType *obj)
{
    return ((obj->SC3 & ADC_SC3_ADCO_MASK) >> ADC_SC3_ADCO_SHIFT);
}

/*! \brief Sets the Continuous Conversion Enable
 *
 * This function sets the Continuous Conversion Enable.
 * Enables continuous conversions.
 *
 * \param[in] obj : pointer to ADC register instance
 * \param[in] value : the value of Continuous Conversion Enable
 *                    - 0b : One conversion will be performed (or one set of
 * conversions, if AVGE is set) after a conversion is initiated.
 *                    - 1b : Continuous conversions will be performed (or
 * continuous sets of conversions, if AVGE is set) after a conversion is
 * initiated.
 */
__attribute__((always_inline)) static inline void AdcReg_SetSc3Adco(AdcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SC3;

    tmp &= ~ADC_SC3_ADCO_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ADC_SC3_ADCO_SHIFT)) & ADC_SC3_ADCO_MASK);
    obj->SC3 = tmp;
}

/*! \brief Gets the Hardware Average Enable
 *
 * This function gets the current Hardware Average Enable.
 * Enables the hardware average function of the ADC.
 *
 * \param[in] obj : pointer to ADC register instance
 * \return Hardware Average Enable
 *         - 0b : Hardware average function disabled.
 *         - 1b : Hardware average function enabled.
 */
__attribute__((always_inline)) static inline uint8_t AdcReg_GetSc3AvgE(const AdcRegType *obj)
{
    return ((obj->SC3 & ADC_SC3_AVGE_MASK) >> ADC_SC3_AVGE_SHIFT);
}

/*! \brief Sets the Hardware Average Enable
 *
 * This function sets the Hardware Average Enable.
 * Enables the hardware average function of the ADC.
 *
 * \param[in] obj : pointer to ADC register instance
 * \param[in] value : the value of Hardware Average Enable
 *                    - 0b : Hardware average function disabled.
 *                    - 1b : Hardware average function enabled.
 */
__attribute__((always_inline)) static inline void AdcReg_SetSc3AvgE(AdcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SC3;

    tmp &= ~ADC_SC3_AVGE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ADC_SC3_AVGE_SHIFT)) & ADC_SC3_AVGE_MASK);
    obj->SC3 = tmp;
}

/*! \brief Gets the Hardware Average Select
 *
 * This function gets the current Hardware Average Select.
 * Determines how many ADC conversions will be averaged to create the ADC
 * average result.
 *
 * \param[in] obj : pointer to ADC register instance
 * \return Hardware Average Select
 *         - 00b : 4 samples averaged.
 *         - 01b : 8 samples averaged.
 *         - 10b : 16 samples averaged.
 *         - 11b : 32 samples averaged.
 */
__attribute__((always_inline)) static inline uint8_t AdcReg_GetSc3AvgS(const AdcRegType *obj)
{
    return ((obj->SC3 & ADC_SC3_AVGS_MASK) >> ADC_SC3_AVGS_SHIFT);
}

/*! \brief Sets the Hardware Average Select
 *
 * This function sets the Hardware Average Select.
 * Determines how many ADC conversions will be averaged to create the ADC
 * average result.
 *
 * \param[in] obj : pointer to ADC register instance
 * \param[in] value : the value of Hardware Average Select
 *                    - 00b : 4 samples averaged.
 *                    - 01b : 8 samples averaged.
 *                    - 10b : 16 samples averaged.
 *                    - 11b : 32 samples averaged.
 */
__attribute__((always_inline)) static inline void AdcReg_SetSc3AvgS(AdcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SC3;

    tmp &= ~ADC_SC3_AVGS_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ADC_SC3_AVGS_SHIFT)) & ADC_SC3_AVGS_MASK);
    obj->SC3 = tmp;
}

/*! \brief Gets the ADC Offset Addition Subtraction Flag
 *
 * This function gets the current ADC Offset Addition Subtraction Flag.
 * This bit configs how offset is used in calibration. It can be set by hardware
 * or software.
 *
 * \param[in] obj : pointer to ADC register instance
 * \return ADC Offset Addition Subtraction Flag
 *         - 0b : ADC output will be added by VAL_OFS(ceiling to 4095)
 *         - 1b : ADC output will be subtracted by VAL_OFS(flooring to 4095)
 */
__attribute__((always_inline)) static inline uint8_t AdcReg_GetOfsSubOfs(const AdcRegType *obj)
{
    return ((obj->OFS & ADC_OFS_SUB_OFS_MASK) >> ADC_OFS_SUB_OFS_SHIFT);
}

/*! \brief Sets the ADC Offset Addition Subtraction Flag
 *
 * This function sets the ADC Offset Addition Subtraction Flag.
 * This bit configs how offset is used in calibration. It can be set by hardware
 * or software.
 *
 * \param[in] obj : pointer to ADC register instance
 * \param[in] value : the value of ADC Offset Addition Subtraction Flag
 *                    - 0b : ADC output will be added by VAL_OFS(ceiling to
 * 4095)
 *                    - 1b : ADC output will be subtracted by VAL_OFS(flooring
 * to 4095)
 */
__attribute__((always_inline)) static inline void AdcReg_SetOfsSubOfs(AdcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->OFS;

    tmp &= ~ADC_OFS_SUB_OFS_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ADC_OFS_SUB_OFS_SHIFT)) & ADC_OFS_SUB_OFS_MASK);
    obj->OFS = tmp;
}

/*! \brief Gets the ADC Offset Value
 *
 * This function gets the current ADC Offset Value.
 * Used in calibration to caculate the final result. It can be set by hardware
 * or software
 *
 * \param[in] obj : pointer to ADC register instance
 * \return ADC Offset Value
 */
__attribute__((always_inline)) static inline uint16_t AdcReg_GetOfsValOfs(const AdcRegType *obj)
{
    return ((obj->OFS & ADC_OFS_VAL_OFS_MASK) >> ADC_OFS_VAL_OFS_SHIFT);
}

/*! \brief Sets the ADC Offset Value
 *
 * This function sets the ADC Offset Value.
 * Used in calibration to caculate the final result. It can be set by hardware
 * or software
 *
 * \param[in] obj : pointer to ADC register instance
 * \param[in] value : the value of ADC Offset Value
 */
__attribute__((always_inline)) static inline void AdcReg_SetOfsValOfs(AdcRegType *obj, uint16_t value)
{
    uint32_t tmp = obj->OFS;

    tmp &= ~ADC_OFS_VAL_OFS_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ADC_OFS_VAL_OFS_SHIFT)) & ADC_OFS_VAL_OFS_MASK);
    obj->OFS = tmp;
}

/*! \brief Gets the ADC Gain Error Value
 *
 * This function gets the current ADC Gain Error Value.
 * Used in gain error adjusting. It can be set by hardware or software.
 * ADC output * 3072/VAL_GE is the gain erro
 *
 * \param[in] obj : pointer to ADC register instance
 * \return ADC Gain Error Value
 */
__attribute__((always_inline)) static inline uint16_t AdcReg_GetGeValGE(const AdcRegType *obj)
{
    return ((obj->GE & ADC_GE_VAL_GE_MASK) >> ADC_GE_VAL_GE_SHIFT);
}

/*! \brief Sets the ADC Gain Error Value
 *
 * This function sets the ADC Gain Error Value.
 * Used in gain error adjusting. It can be set by hardware or software.
 * ADC output * 3072/VAL_GE is the gain erro
 *
 * \param[in] obj : pointer to ADC register instance
 * \param[in] value : the value of ADC Gain Error Value
 */
__attribute__((always_inline)) static inline void AdcReg_SetGeValGE(AdcRegType *obj, uint16_t value)
{
    uint32_t tmp = obj->GE;

    tmp &= ~ADC_GE_VAL_GE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ADC_GE_VAL_GE_SHIFT)) & ADC_GE_VAL_GE_MASK);
    obj->GE = tmp;
}

/*! \brief Gets the Conversion Complete Flag
 *
 * This function gets the current Conversion Complete Flag.
 * This is a read-only field that is set each time a conversion is completed
 when one or more of the following is true:
 * - The compare function is disabled SC2[ACFE]=0 and the hardware average
 function is disabled SC3[AVGE]=0
 * If the compare result is true, then COCO is set upon completion of a
 conversion if one or more of the following is true:
 * - The compare function is enabled  SC2[ACFE]=1
 * COCO is set upon completion of the selected number of conversions (determined
 by AVGS) if one or more of the following is true:
 * - The hardware average function is enabled SC3[AVGE]=1
 * COCO is cleared when one of the following is true:
 - The respective SCn register is written
 - The respective Rn register is read
 *
 * \param[in] obj : pointer to ADC register instance
 * \param[in] channel : the channel number
 * \return Conversion Complete Flag
 *         - 0b : Conversion is not completed.
 *         - 1b : Conversion is completed.
 */
__attribute__((always_inline)) static inline uint8_t AdcReg_GetScCoCo(const AdcRegType *obj, uint8_t channel)
{
    return ((obj->SC[channel] & ADC_SC_COCO_MASK) >> ADC_SC_COCO_SHIFT);
}

/*! \brief Gets the Interrupt Enable
 *
 * This function gets the current Interrupt Enable.
 * Enables conversion complete interrupts. When COCO becomes set while the
 * respective AIEN is high, an interrupt is asserted.
 *
 * \param[in] obj : pointer to ADC register instance
 * \param[in] channel : the channel number
 * \return Interrupt Enable
 *         - 0b : Conversion complete interrupt is disabled.
 *         - 1b : Conversion complete interrupt is enabled.
 */
__attribute__((always_inline)) static inline uint8_t AdcReg_GetScAIEn(const AdcRegType *obj, uint8_t channel)
{
    return ((obj->SC[channel] & ADC_SC_AIEN_MASK) >> ADC_SC_AIEN_SHIFT);
}

/*! \brief Sets the Interrupt Enable
 *
 * This function sets the Interrupt Enable.
 * Enables conversion complete interrupts. When COCO becomes set while the
 * respective AIEN is high, an interrupt is asserted.
 *
 * \param[in] obj : pointer to ADC register instance
 * \param[in] channel : the channel number
 * \param[in] value : the value of Interrupt Enable
 *                    - 0b : Conversion complete interrupt is disabled.
 *                    - 1b : Conversion complete interrupt is enabled.
 */
__attribute__((always_inline)) static inline void AdcReg_SetScAIEn(AdcRegType *obj, uint8_t channel, uint8_t value)
{
    uint32_t tmp = obj->SC[channel];

    tmp &= ~ADC_SC_AIEN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ADC_SC_AIEN_SHIFT)) & ADC_SC_AIEN_MASK);
    obj->SC[channel] = tmp;
}

/*! \brief Gets the Input channel select
 *
 * This function gets the current Input channel select.
 * Selects one of the input channels.
 * The successive approximation converter subsystem is turned off when the
 * channel bits are all set (i.e.ADCH set to all 1s). This feature allows
 * explicit disabling of the ADC and isolation of the input channel from all
 * sources. Terminating continuous conversions this way prevents an additional
 * single conversion from being performed. It is not necessary to set ADCH to
 * all 1s to place the ADC in a low:power state when continuous conversions are
 * not enabled because the module automatically enters a low:power state when a
 * conversion completes.
 *
 * \param[in] obj : pointer to ADC register instance
 * \param[in] channel : the channel number
 * \return Input channel select
 *         - 0x00 : External channel 0 is selected as ADC input
 *         - 0x01 : External channel 1 is selected as ADC input
 *         - 0x02 : External channel 2 is selected as ADC input
 *         - 0x03 : External channel 3 is selected as ADC input
 *         - 0x04 : External channel 4 is selected as ADC input
 *         - 0x05 : External channel 5 is selected as ADC input
 *         - 0x06 : External channel 6 is selected as ADC input
 *         - 0x07 : External channel 7 is selected as ADC input
 *         - 0x08 : External channel 8 is selected as ADC input
 *         - 0x09 : External channel 9 is selected as ADC input
 *         - 0x0A : External channel 10 is selected as ADC input
 *         - 0x0B : External channel 11 is selected as ADC input
 *         - 0x0C : External channel 12 is selected as ADC input
 *         - 0x0D : External channel 13 is selected as ADC input
 *         - 0x0E : External channel 14 is selected as ADC input
 *         - 0x0F : External channel 15 is selected as ADC input
 *         - 0x10 : External channel 16 is selected as ADC input
 *         - 0x11 : External channel 17 is selected as ADC input
 *         - 0x12 : External channel 18 is selected as ADC input
 *         - 0x13 : External channel 19 is selected as ADC input
 *         - 0x14 : External channel 20 is selected as ADC input
 *         - 0x15 : External channel 21 is selected as ADC input
 *         - 0x16 : External channel 22 is selected as ADC input
 *         - 0x17 : External channel 23 is selected as ADC input
 *         - 0x18 : Reserved
 *         - 0x19 : LPVBG
 *         - 0x1A : VBG
 *         - 0x1B : monitor ldo output
 *         - 0x1C : Reserved
 *         - 0x1D : Self Test Voltage
 *         - 0x1E : Reserved
 *         - 0x1F : Module is disabled
 */
__attribute__((always_inline)) static inline uint8_t AdcReg_GetScAdCh(const AdcRegType *obj, uint8_t channel)
{
    return ((obj->SC[channel] & ADC_SC_ADCH_MASK) >> ADC_SC_ADCH_SHIFT);
}

/*! \brief Sets the Input channel select
 *
 * This function sets the Input channel select.
 * Selects one of the input channels.
 * The successive approximation converter subsystem is turned off when the
 * channel bits are all set (i.e.ADCH set to all 1s). This feature allows
 * explicit disabling of the ADC and isolation of the input channel from all
 * sources. Terminating continuous conversions this way prevents an additional
 * single conversion from being performed. It is not necessary to set ADCH to
 * all 1s to place the ADC in a low:power state when continuous conversions are
 * not enabled because the module automatically enters a low:power state when a
 * conversion completes.
 *
 * \param[in] obj : pointer to ADC register instance
 * \param[in] channel : the channel number
 * \param[in] value : the value of Input channel select
 *         - 0x00 : External channel 0 is selected as ADC input
 *         - 0x01 : External channel 1 is selected as ADC input
 *         - 0x02 : External channel 2 is selected as ADC input
 *         - 0x03 : External channel 3 is selected as ADC input
 *         - 0x04 : External channel 4 is selected as ADC input
 *         - 0x05 : External channel 5 is selected as ADC input
 *         - 0x06 : External channel 6 is selected as ADC input
 *         - 0x07 : External channel 7 is selected as ADC input
 *         - 0x08 : External channel 8 is selected as ADC input
 *         - 0x09 : External channel 9 is selected as ADC input
 *         - 0x0A : External channel 10 is selected as ADC input
 *         - 0x0B : External channel 11 is selected as ADC input
 *         - 0x0C : External channel 12 is selected as ADC input
 *         - 0x0D : External channel 13 is selected as ADC input
 *         - 0x0E : External channel 14 is selected as ADC input
 *         - 0x0F : External channel 15 is selected as ADC input
 *         - 0x10 : External channel 16 is selected as ADC input
 *         - 0x11 : External channel 17 is selected as ADC input
 *         - 0x12 : External channel 18 is selected as ADC input
 *         - 0x13 : External channel 19 is selected as ADC input
 *         - 0x14 : External channel 20 is selected as ADC input
 *         - 0x15 : External channel 21 is selected as ADC input
 *         - 0x16 : External channel 22 is selected as ADC input
 *         - 0x17 : External channel 23 is selected as ADC input
 *         - 0x18 : Reserved
 *         - 0x19 : LPVBG
 *         - 0x1A : VBG
 *         - 0x1B : monitor ldo output
 *         - 0x1C : Reserved
 *         - 0x1D : Self Test Voltage
 *         - 0x1E : Reserved
 *         - 0x1F : Module is disabled
 */
__attribute__((always_inline)) static inline void AdcReg_SetScAdCh(AdcRegType *obj, uint8_t channel, uint8_t value)
{
    uint32_t tmp = obj->SC[channel];

    tmp &= ~ADC_SC_ADCH_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << ADC_SC_ADCH_SHIFT)) & ADC_SC_ADCH_MASK);
    obj->SC[channel] = tmp;
}

/*! \brief Gets the ADC data result
 *
 * This function gets the current ADC data result.
 * \param[in] obj : pointer to ADC register instance
 * \param[in] channel : the channel number
 * \return ADC data result
 */
__attribute__((always_inline)) static inline uint16_t AdcReg_GetRData(const AdcRegType *obj, uint8_t channel)
{
    return ((obj->R[channel] & ADC_R_DATA_MASK) >> ADC_R_DATA_SHIFT);
}

/*! \brief Abort ADC chn
 * This function for software trigger ADC.
 * \param[in] obj : pointer to ADC register instance
 * \param[in] chn  : expect abort channel number
 */
__attribute__((always_inline)) static inline void AdcReg_AbortChn(AdcRegType *obj, uint8_t chn)
{
    uint32_t tmp  = obj->SC[chn];
    obj->SC[chn] = tmp;
}
#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _ADC_REG_H_ */
