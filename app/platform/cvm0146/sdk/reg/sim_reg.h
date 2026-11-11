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

#ifndef _SIM_REG_H_
#define _SIM_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the SIM (System Integration Module) Registers
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

/* ETM Bit Fields */
#define SIM_ETM_INTNUM_MASK              (0xFF8u)
#define SIM_ETM_INTNUM_SHIFT             (3u)
#define SIM_ETM_INTNUM_WIDTH             (9u)
#define SIM_ETM_INTSTAT_MASK             (0x07u)
#define SIM_ETM_INTSTAT_SHIFT            (0u)
#define SIM_ETM_INTSTAT_WIDTH            (3u)

/* CHIP Bit Fields */
#define SIM_CHIP_SRAMU_INIT_ST_MASK      (0x20u)
#define SIM_CHIP_SRAMU_INIT_ST_SHIFT     (5u)
#define SIM_CHIP_SRAMU_INIT_ST_WIDTH     (1u)
#define SIM_CHIP_SRAML_INIT_ST_MASK      (0x10u)
#define SIM_CHIP_SRAML_INIT_ST_SHIFT     (4u)
#define SIM_CHIP_SRAML_INIT_ST_WIDTH     (1u)
#define SIM_CHIP_SRAMU_INIT_MASK         (0x08u)
#define SIM_CHIP_SRAMU_INIT_SHIFT        (3u)
#define SIM_CHIP_SRAMU_INIT_WIDTH        (1u)
#define SIM_CHIP_SRAML_INIT_MASK         (0x04u)
#define SIM_CHIP_SRAML_INIT_SHIFT        (2u)
#define SIM_CHIP_SRAML_INIT_WIDTH        (1u)
#define SIM_CHIP_SRAMU_RETEN_MASK        (0x02u)
#define SIM_CHIP_SRAMU_RETEN_SHIFT       (1u)
#define SIM_CHIP_SRAMU_RETEN_WIDTH       (1u)
#define SIM_CHIP_SRAML_RETEN_MASK        (0x01u)
#define SIM_CHIP_SRAML_RETEN_SHIFT       (0u)
#define SIM_CHIP_SRAML_RETEN_WIDTH       (1u)

/* SYS_INFO Bit Fields */
#define SIM_SYS_INFO_DFLASH_SIZE_MASK    (0xC0u)
#define SIM_SYS_INFO_DFLASH_SIZE_SHIFT   (6u)
#define SIM_SYS_INFO_DFLASH_SIZE_WIDTH   (2u)
#define SIM_SYS_INFO_PFLASH_SIZE_MASK    (0x30u)
#define SIM_SYS_INFO_PFLASH_SIZE_SHIFT   (4u)
#define SIM_SYS_INFO_PFLASH_SIZE_WIDTH   (2u)
#define SIM_SYS_INFO_SRAMU_SIZE_MASK     (0x08u)
#define SIM_SYS_INFO_SRAMU_SIZE_SHIFT    (3u)
#define SIM_SYS_INFO_SRAMU_SIZE_WIDTH    (1u)
#define SIM_SYS_INFO_SRAML_SIZE_MASK     (0x04u)
#define SIM_SYS_INFO_SRAML_SIZE_SHIFT    (2u)
#define SIM_SYS_INFO_SRAML_SIZE_WIDTH    (1u)
#define SIM_SYS_INFO_PIN_NUM_MASK        (0x03u)
#define SIM_SYS_INFO_PIN_NUM_SHIFT       (0u)
#define SIM_SYS_INFO_PIN_NUM_WIDTH       (2u)

/* PER_INFO Bit Fields */
#define SIM_PER_INFO_MFT_NUM_MASK        (0x08u)
#define SIM_PER_INFO_MFT_NUM_SHIFT       (3u)
#define SIM_PER_INFO_MFT_NUM_WIDTH       (1u)
#define SIM_PER_INFO_CAN_NUM_MASK        (0x04u)
#define SIM_PER_INFO_CAN_NUM_SHIFT       (2u)
#define SIM_PER_INFO_CAN_NUM_WIDTH       (1u)
#define SIM_PER_INFO_UART_NUM_MASK       (0x02u)
#define SIM_PER_INFO_UART_NUM_SHIFT      (1u)
#define SIM_PER_INFO_UART_NUM_WIDTH      (1u)
#define SIM_PER_INFO_SPI_NUM_MASK        (0x01u)
#define SIM_PER_INFO_SPI_NUM_SHIFT       (0u)
#define SIM_PER_INFO_SPI_NUM_WIDTH       (1u)

/* PWM_CTRL0 Bit Fields */
#define SIM_PWM_CTRL0_PWM_FUNC3_MASK     (0x3F000000u)
#define SIM_PWM_CTRL0_PWM_FUNC3_SHIFT    (24u)
#define SIM_PWM_CTRL0_PWM_FUNC3_WIDTH    (6u)
#define SIM_PWM_CTRL0_PWM_FUNC2_MASK     (0x3F0000u)
#define SIM_PWM_CTRL0_PWM_FUNC2_SHIFT    (16u)
#define SIM_PWM_CTRL0_PWM_FUNC2_WIDTH    (6u)
#define SIM_PWM_CTRL0_PWM_FUNC1_MASK     (0x3F00u)
#define SIM_PWM_CTRL0_PWM_FUNC1_SHIFT    (8u)
#define SIM_PWM_CTRL0_PWM_FUNC1_WIDTH    (6u)
#define SIM_PWM_CTRL0_PWM_FUNC0_MASK     (0x3Fu)
#define SIM_PWM_CTRL0_PWM_FUNC0_SHIFT    (0u)
#define SIM_PWM_CTRL0_PWM_FUNC0_WIDTH    (6u)

/* PWM_CTRL1 Bit Fields */
#define SIM_PWM_CTRL1_PWM_FUNC7_MASK     (0x3F000000u)
#define SIM_PWM_CTRL1_PWM_FUNC7_SHIFT    (24u)
#define SIM_PWM_CTRL1_PWM_FUNC7_WIDTH    (6u)
#define SIM_PWM_CTRL1_PWM_FUNC6_MASK     (0x3F0000u)
#define SIM_PWM_CTRL1_PWM_FUNC6_SHIFT    (16u)
#define SIM_PWM_CTRL1_PWM_FUNC6_WIDTH    (6u)
#define SIM_PWM_CTRL1_PWM_FUNC5_MASK     (0x3F00u)
#define SIM_PWM_CTRL1_PWM_FUNC5_SHIFT    (8u)
#define SIM_PWM_CTRL1_PWM_FUNC5_WIDTH    (6u)
#define SIM_PWM_CTRL1_PWM_FUNC4_MASK     (0x3Fu)
#define SIM_PWM_CTRL1_PWM_FUNC4_SHIFT    (0u)
#define SIM_PWM_CTRL1_PWM_FUNC4_WIDTH    (6u)

/* ADC Bit Fields */
#define SIM_ADC_IL_SRC_MASK              (0xF000000u)
#define SIM_ADC_IL_SRC_SHIFT             (24u)
#define SIM_ADC_IL_SRC_WIDTH             (4u)
#define SIM_ADC_MON_EN_MASK              (0x100000u)
#define SIM_ADC_MON_EN_SHIFT             (20u)
#define SIM_ADC_MON_EN_WIDTH             (1u)
#define SIM_ADC_MON_LDO_SEL_MASK         (0xC0000u)
#define SIM_ADC_MON_LDO_SEL_SHIFT        (18u)
#define SIM_ADC_MON_LDO_SEL_WIDTH        (2u)
#define SIM_ADC_MON_VOLT_SEL_MASK        (0x30000u)
#define SIM_ADC_MON_VOLT_SEL_SHIFT       (16u)
#define SIM_ADC_MON_VOLT_SEL_WIDTH       (2u)
#define SIM_ADC_TRG1_SRC_MASK            (0x2000u)
#define SIM_ADC_TRG1_SRC_SHIFT           (13u)
#define SIM_ADC_TRG1_SRC_WIDTH           (1u)
#define SIM_ADC_PRETRG1_SW_SRC_MASK      (0x1C00u)
#define SIM_ADC_PRETRG1_SW_SRC_SHIFT     (10u)
#define SIM_ADC_PRETRG1_SW_SRC_WIDTH     (3u)
#define SIM_ADC_PRETRG1_SRC_MASK         (0x300u)
#define SIM_ADC_PRETRG1_SRC_SHIFT        (8u)
#define SIM_ADC_PRETRG1_SRC_WIDTH        (2u)
#define SIM_ADC_TRG0_SRC_MASK            (0x20u)
#define SIM_ADC_TRG0_SRC_SHIFT           (5u)
#define SIM_ADC_TRG0_SRC_WIDTH           (1u)
#define SIM_ADC_PRETRG0_SW_SRC_MASK      (0x1Cu)
#define SIM_ADC_PRETRG0_SW_SRC_SHIFT     (2u)
#define SIM_ADC_PRETRG0_SW_SRC_WIDTH     (3u)
#define SIM_ADC_PRETRG0_SRC_MASK         (0x03u)
#define SIM_ADC_PRETRG0_SRC_SHIFT        (0u)
#define SIM_ADC_PRETRG0_SRC_WIDTH        (2u)

/* PDB Bit Fields */
#define SIM_PDB_BB_SEL_MASK              (0x07u)
#define SIM_PDB_BB_SEL_SHIFT             (0u)
#define SIM_PDB_BB_SEL_WIDTH             (3u)

/* I2S Bit Fields */
#define SIM_I2S_SLV_DMA_IRQ_MASK         (0x04u)
#define SIM_I2S_SLV_DMA_IRQ_SHIFT        (2u)
#define SIM_I2S_SLV_DMA_IRQ_WIDTH        (1u)
#define SIM_I2S_MST_DMA_IRQ_MASK         (0x02u)
#define SIM_I2S_MST_DMA_IRQ_SHIFT        (1u)
#define SIM_I2S_MST_DMA_IRQ_WIDTH        (1u)
#define SIM_I2S_MODE_MASK                (0x01u)
#define SIM_I2S_MODE_SHIFT               (0u)
#define SIM_I2S_MODE_WIDTH               (1u)

/* MFT_CTRL0 Bit Fields */
#define SIM_MFT_CTRL0_MFT3_FLT_SEL_MASK  (0x70000000u)
#define SIM_MFT_CTRL0_MFT3_FLT_SEL_SHIFT (28u)
#define SIM_MFT_CTRL0_MFT3_FLT_SEL_WIDTH (3u)
#define SIM_MFT_CTRL0_MFT2_FLT_SEL_MASK  (0x7000000u)
#define SIM_MFT_CTRL0_MFT2_FLT_SEL_SHIFT (24u)
#define SIM_MFT_CTRL0_MFT2_FLT_SEL_WIDTH (3u)
#define SIM_MFT_CTRL0_MFT1_FLT_SEL_MASK  (0x700000u)
#define SIM_MFT_CTRL0_MFT1_FLT_SEL_SHIFT (20u)
#define SIM_MFT_CTRL0_MFT1_FLT_SEL_WIDTH (3u)
#define SIM_MFT_CTRL0_MFT0_FLT_SEL_MASK  (0x70000u)
#define SIM_MFT_CTRL0_MFT0_FLT_SEL_SHIFT (16u)
#define SIM_MFT_CTRL0_MFT0_FLT_SEL_WIDTH (3u)
#define SIM_MFT_CTRL0_GLDOK_MASK         (0x01u)
#define SIM_MFT_CTRL0_GLDOK_SHIFT        (0u)
#define SIM_MFT_CTRL0_GLDOK_WIDTH        (1u)

/* MFT_CTRL1 Bit Fields */
#define SIM_MFT_CTRL1_MFT5SYNCBIT_MASK   (0x20000000u)
#define SIM_MFT_CTRL1_MFT5SYNCBIT_SHIFT  (29u)
#define SIM_MFT_CTRL1_MFT5SYNCBIT_WIDTH  (1u)
#define SIM_MFT_CTRL1_MFT4SYNCBIT_MASK   (0x10000000u)
#define SIM_MFT_CTRL1_MFT4SYNCBIT_SHIFT  (28u)
#define SIM_MFT_CTRL1_MFT4SYNCBIT_WIDTH  (1u)
#define SIM_MFT_CTRL1_MFT3SYNCBIT_MASK   (0x8000000u)
#define SIM_MFT_CTRL1_MFT3SYNCBIT_SHIFT  (27u)
#define SIM_MFT_CTRL1_MFT3SYNCBIT_WIDTH  (1u)
#define SIM_MFT_CTRL1_MFT2SYNCBIT_MASK   (0x4000000u)
#define SIM_MFT_CTRL1_MFT2SYNCBIT_SHIFT  (26u)
#define SIM_MFT_CTRL1_MFT2SYNCBIT_WIDTH  (1u)
#define SIM_MFT_CTRL1_MFT1SYNCBIT_MASK   (0x2000000u)
#define SIM_MFT_CTRL1_MFT1SYNCBIT_SHIFT  (25u)
#define SIM_MFT_CTRL1_MFT1SYNCBIT_WIDTH  (1u)
#define SIM_MFT_CTRL1_MFT0SYNCBIT_MASK   (0x1000000u)
#define SIM_MFT_CTRL1_MFT0SYNCBIT_SHIFT  (24u)
#define SIM_MFT_CTRL1_MFT0SYNCBIT_WIDTH  (1u)
#define SIM_MFT_CTRL1_MFT1CH0SEL_MASK    (0x80000u)
#define SIM_MFT_CTRL1_MFT1CH0SEL_SHIFT   (19u)
#define SIM_MFT_CTRL1_MFT1CH0SEL_WIDTH   (1u)
#define SIM_MFT_CTRL1_MFT2CH0SEL_MASK    (0x60000u)
#define SIM_MFT_CTRL1_MFT2CH0SEL_SHIFT   (17u)
#define SIM_MFT_CTRL1_MFT2CH0SEL_WIDTH   (2u)
#define SIM_MFT_CTRL1_MFT2CH1SEL_MASK    (0x10000u)
#define SIM_MFT_CTRL1_MFT2CH1SEL_SHIFT   (16u)
#define SIM_MFT_CTRL1_MFT2CH1SEL_WIDTH   (1u)
#define SIM_MFT_CTRL1_MFT0_OUTSEL_MASK   (0xFF00u)
#define SIM_MFT_CTRL1_MFT0_OUTSEL_SHIFT  (8u)
#define SIM_MFT_CTRL1_MFT0_OUTSEL_WIDTH  (8u)
#define SIM_MFT_CTRL1_MFT3_OUTSEL_MASK   (0xFFu)
#define SIM_MFT_CTRL1_MFT3_OUTSEL_SHIFT  (0u)
#define SIM_MFT_CTRL1_MFT3_OUTSEL_WIDTH  (8u)

/* FLASH Bit Fields */
#define SIM_FLASH_LOAD_DONE_MASK         (0x200u)
#define SIM_FLASH_LOAD_DONE_SHIFT        (9u)
#define SIM_FLASH_LOAD_DONE_WIDTH        (1u)
#define SIM_FLASH_VIRGIN_FLAG_MASK       (0x100u)
#define SIM_FLASH_VIRGIN_FLAG_SHIFT      (8u)
#define SIM_FLASH_VIRGIN_FLAG_WIDTH      (1u)
#define SIM_FLASH_DFLS_FLUSH_EN_MASK     (0x08u)
#define SIM_FLASH_DFLS_FLUSH_EN_SHIFT    (3u)
#define SIM_FLASH_DFLS_FLUSH_EN_WIDTH    (1u)
#define SIM_FLASH_PFLS_FLUSH_EN_MASK     (0x04u)
#define SIM_FLASH_PFLS_FLUSH_EN_SHIFT    (2u)
#define SIM_FLASH_PFLS_FLUSH_EN_WIDTH    (1u)
#define SIM_FLASH_DFLS_PFB_EN_MASK       (0x02u)
#define SIM_FLASH_DFLS_PFB_EN_SHIFT      (1u)
#define SIM_FLASH_DFLS_PFB_EN_WIDTH      (1u)
#define SIM_FLASH_PFLS_PFB_EN_MASK       (0x01u)
#define SIM_FLASH_PFLS_PFB_EN_SHIFT      (0u)
#define SIM_FLASH_PFLS_PFB_EN_WIDTH      (1u)

/* UDIDH Bit Fields */
#define SIM_UDIDH_H_MASK                 (0xFFFFFFFFu)
#define SIM_UDIDH_H_SHIFT                (0u)
#define SIM_UDIDH_H_WIDTH                (32u)

/* UDIDMH Bit Fields */
#define SIM_UDIDMH_MH_MASK               (0xFFFFFFFFu)
#define SIM_UDIDMH_MH_SHIFT              (0u)
#define SIM_UDIDMH_MH_WIDTH              (32u)

/* UDIDML Bit Fields */
#define SIM_UDIDML_ML_MASK               (0xFFFFFFFFu)
#define SIM_UDIDML_ML_SHIFT              (0u)
#define SIM_UDIDML_ML_WIDTH              (32u)

/* UDIDL Bit Fields */
#define SIM_UDIDL_L_MASK                 (0xFFFFFFFFu)
#define SIM_UDIDL_L_SHIFT                (0u)
#define SIM_UDIDL_L_WIDTH                (32u)

/* SDIDH Bit Fields */
#define SIM_SDIDH_IDH_MASK               (0xFFFFFFFFu)
#define SIM_SDIDH_IDH_SHIFT              (0u)
#define SIM_SDIDH_IDH_WIDTH              (32u)

/* SDIDL Bit Fields */
#define SIM_SDIDL_IDL_MASK               (0xFFFFFFFFu)
#define SIM_SDIDL_IDL_SHIFT              (0u)
#define SIM_SDIDL_IDL_WIDTH              (32u)

/* SW_TRG Bit Fields */
#define SIM_SW_TRG_SW_TRG_MASK           (0x01u)
#define SIM_SW_TRG_SW_TRG_SHIFT          (0u)
#define SIM_SW_TRG_SW_TRG_WIDTH          (1u)

/* E2E_CR Bit Fields */
#define SIM_E2E_CR_EN_MASK               (0x01u)
#define SIM_E2E_CR_EN_SHIFT              (0u)
#define SIM_E2E_CR_EN_WIDTH              (1u)

/* E2E_INJ Bit Fields */
#define SIM_E2E_INJ_CH_EN_MASK           (0xFFFFu)
#define SIM_E2E_INJ_CH_EN_SHIFT          (0u)
#define SIM_E2E_INJ_CH_EN_WIDTH          (16u)

/* E2E_ST Bit Fields */
#define SIM_E2E_ST_CH15_MASK             (0x8000u)
#define SIM_E2E_ST_CH15_SHIFT            (15u)
#define SIM_E2E_ST_CH15_WIDTH            (1u)
#define SIM_E2E_ST_CH14_MASK             (0x4000u)
#define SIM_E2E_ST_CH14_SHIFT            (14u)
#define SIM_E2E_ST_CH14_WIDTH            (1u)
#define SIM_E2E_ST_CH13_MASK             (0x2000u)
#define SIM_E2E_ST_CH13_SHIFT            (13u)
#define SIM_E2E_ST_CH13_WIDTH            (1u)
#define SIM_E2E_ST_CH12_MASK             (0x1000u)
#define SIM_E2E_ST_CH12_SHIFT            (12u)
#define SIM_E2E_ST_CH12_WIDTH            (1u)
#define SIM_E2E_ST_CH11_MASK             (0x800u)
#define SIM_E2E_ST_CH11_SHIFT            (11u)
#define SIM_E2E_ST_CH11_WIDTH            (1u)
#define SIM_E2E_ST_CH10_MASK             (0x400u)
#define SIM_E2E_ST_CH10_SHIFT            (10u)
#define SIM_E2E_ST_CH10_WIDTH            (1u)
#define SIM_E2E_ST_CH9_MASK              (0x200u)
#define SIM_E2E_ST_CH9_SHIFT             (9u)
#define SIM_E2E_ST_CH9_WIDTH             (1u)
#define SIM_E2E_ST_CH8_MASK              (0x100u)
#define SIM_E2E_ST_CH8_SHIFT             (8u)
#define SIM_E2E_ST_CH8_WIDTH             (1u)
#define SIM_E2E_ST_CH7_MASK              (0x80u)
#define SIM_E2E_ST_CH7_SHIFT             (7u)
#define SIM_E2E_ST_CH7_WIDTH             (1u)
#define SIM_E2E_ST_CH6_MASK              (0x40u)
#define SIM_E2E_ST_CH6_SHIFT             (6u)
#define SIM_E2E_ST_CH6_WIDTH             (1u)
#define SIM_E2E_ST_CH5_MASK              (0x20u)
#define SIM_E2E_ST_CH5_SHIFT             (5u)
#define SIM_E2E_ST_CH5_WIDTH             (1u)
#define SIM_E2E_ST_CH4_MASK              (0x10u)
#define SIM_E2E_ST_CH4_SHIFT             (4u)
#define SIM_E2E_ST_CH4_WIDTH             (1u)
#define SIM_E2E_ST_CH3_MASK              (0x08u)
#define SIM_E2E_ST_CH3_SHIFT             (3u)
#define SIM_E2E_ST_CH3_WIDTH             (1u)
#define SIM_E2E_ST_CH2_MASK              (0x04u)
#define SIM_E2E_ST_CH2_SHIFT             (2u)
#define SIM_E2E_ST_CH2_WIDTH             (1u)
#define SIM_E2E_ST_CH1_MASK              (0x02u)
#define SIM_E2E_ST_CH1_SHIFT             (1u)
#define SIM_E2E_ST_CH1_WIDTH             (1u)
#define SIM_E2E_ST_CH0_MASK              (0x01u)
#define SIM_E2E_ST_CH0_SHIFT             (0u)
#define SIM_E2E_ST_CH0_WIDTH             (1u)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief The definition of SIM registers
 */
typedef struct _SimRegType_
{
    const volatile uint32_t ETM;       /*!< system ETM status register, offset: 0x00 */
    volatile uint32_t       CHIP;      /*!< system chip register, offset: 0x04 */
    const volatile uint32_t SYS_INFO;  /*!< system package register, offset: 0x08 */
    const volatile uint32_t PER_INFO;  /*!< system peripheral register, offset: 0x0C */
    volatile uint32_t       PWM_CTRL0; /*!< system PWM register 0, offset: 0x10 */
    volatile uint32_t       PWM_CTRL1; /*!< system PWM register 1, offset: 0x14 */
    volatile uint32_t       ADC;       /*!< system ADC register, offset: 0x18 */
    volatile uint32_t       PDB;       /*!< system PDB register, offset: 0x1C */
    volatile uint32_t       I2S;       /*!< system I2S register, offset: 0x20 */
    volatile uint32_t       MFT_CTRL0; /*!< system MFT register 0, offset: 0x24 */
    volatile uint32_t       MFT_CTRL1; /*!< system MFT register 1, offset: 0x28 */
    volatile uint32_t       FLASH;     /*!< system flash controller register, offset: 0x2C */
    const volatile uint32_t UDIDH;     /*!< system UD ID high register, offset: 0x30 */
    const volatile uint32_t UDIDMH;    /*!< system UD ID medium high register, offset: 0x34 */
    const volatile uint32_t UDIDML;    /*!< system UD ID medium low register, offset: 0x38 */
    const volatile uint32_t UDIDL;     /*!< system UD ID low register, offset: 0x3C */
    const volatile uint32_t SDIDH;     /*!< system SDID high register, offset: 0x40 */
    const volatile uint32_t SDIDL;     /*!< system SDID low register, offset: 0x44 */
    volatile uint32_t       SW_TRG;    /*!< system software trigger register, offset: 0x48 */
    volatile uint32_t       E2E_CR;    /*!< system E2E configuration register, offset: 0x4C */
    volatile uint32_t       E2E_INJ;   /*!< system E2E error injection register, offset: 0x50 */
    volatile uint32_t       E2E_ST;    /*!< system E2E status register, offset: 0x54 */
} SimRegType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Gets the ETM interrupt number
 *
 * This function gets the current ETM interrupt number.
 * The interrupt number that will be vectored to
 *
 * \param[in] obj : pointer to SIM register instance
 * \return ETM interrupt number

 */
__attribute__((always_inline)) static inline uint16_t SimReg_GetEtmIntNum(const SimRegType *obj)
{
    return ((obj->ETM & SIM_ETM_INTNUM_MASK) >> SIM_ETM_INTNUM_SHIFT);
}

/*! \brief Gets the ETM Interrupt status
 *
 * This function gets the current ETM Interrupt status.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return ETM Interrupt status
 *         - 0h : no status
 *         - 1h : interrupt entry
 *         - 2h : interrupt exit
 *         - 3h : interrupt return
 *         - 4h : vector fetch and stack push
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetEtmIntStat(const SimRegType *obj)
{
    return ((obj->ETM & SIM_ETM_INTSTAT_MASK) >> SIM_ETM_INTSTAT_SHIFT);
}

/*! \brief Gets the SRAMU initial status
 *
 * This function gets the current SRAMU initial status.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return SRAMU initial status
 *         - 0b : sram initial progress not done
 *         - 1b : sram intial progress done
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetChipSRamUInitSt(const SimRegType *obj)
{
    return ((obj->CHIP & SIM_CHIP_SRAMU_INIT_ST_MASK) >> SIM_CHIP_SRAMU_INIT_ST_SHIFT);
}

/*! \brief Gets the SRAML initial status
 *
 * This function gets the current SRAML initial status.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return SRAML initial status
 *         - 0b : sram initial progress not done
 *         - 1b : sram intial progress done
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetChipSRamLInitSt(const SimRegType *obj)
{
    return ((obj->CHIP & SIM_CHIP_SRAML_INIT_ST_MASK) >> SIM_CHIP_SRAML_INIT_ST_SHIFT);
}

/*! \brief Sets the SRAMU initial command
 *
 * This function sets the SRAMU initial command.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of SRAMU initial command

 */
__attribute__((always_inline)) static inline void SimReg_SetChipSRamUInit(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CHIP;

    tmp &= ~SIM_CHIP_SRAMU_INIT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_CHIP_SRAMU_INIT_SHIFT)) & SIM_CHIP_SRAMU_INIT_MASK);
    obj->CHIP = tmp;
}

/*! \brief Sets the SRAML initial command
 *
 * This function sets the SRAML initial command.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of SRAML initial command

 */
__attribute__((always_inline)) static inline void SimReg_SetChipSRamLInit(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CHIP;

    tmp &= ~SIM_CHIP_SRAML_INIT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_CHIP_SRAML_INIT_SHIFT)) & SIM_CHIP_SRAML_INIT_MASK);
    obj->CHIP = tmp;
}

/*! \brief Gets the SRAMU retention
 *
 * This function gets the current SRAMU retention.
 * It is reseted by power up and standby exit only.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return SRAMU retention
 *         - 0b : memory contents are retained across resets.
 *         - 1b : No memory contents retention.
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetChipSRamUReten(const SimRegType *obj)
{
    return ((obj->CHIP & SIM_CHIP_SRAMU_RETEN_MASK) >> SIM_CHIP_SRAMU_RETEN_SHIFT);
}

/*! \brief Sets the SRAMU retention
 *
 * This function sets the SRAMU retention.
 * It is reseted by power up and standby exit only.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of SRAMU retention
 *                    - 0b : memory contents are retained across resets.
 *                    - 1b : No memory contents retention.
 */
__attribute__((always_inline)) static inline void SimReg_SetChipSRamUReten(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CHIP;

    tmp &= ~SIM_CHIP_SRAMU_RETEN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_CHIP_SRAMU_RETEN_SHIFT)) & SIM_CHIP_SRAMU_RETEN_MASK);
    obj->CHIP = tmp;
}

/*! \brief Gets the SRAML retention
 *
 * This function gets the current SRAML retention.
 * It is reseted by power up and standby exit only.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return SRAML retention
 *         - 0b : memory contents are retained across resets.
 *         - 1b : No memory contents retention.
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetChipSRamLReten(const SimRegType *obj)
{
    return ((obj->CHIP & SIM_CHIP_SRAML_RETEN_MASK) >> SIM_CHIP_SRAML_RETEN_SHIFT);
}

/*! \brief Sets the SRAML retention
 *
 * This function sets the SRAML retention.
 * It is reseted by power up and standby exit only.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of SRAML retention
 *                    - 0b : memory contents are retained across resets.
 *                    - 1b : No memory contents retention.
 */
__attribute__((always_inline)) static inline void SimReg_SetChipSRamLReten(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CHIP;

    tmp &= ~SIM_CHIP_SRAML_RETEN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_CHIP_SRAML_RETEN_SHIFT)) & SIM_CHIP_SRAML_RETEN_MASK);
    obj->CHIP = tmp;
}

/*! \brief Gets the DFLASH size
 *
 * This function gets the current DFLASH size.
 * Its value is loaded during POR/LVR/STANDBY reset from FLASH0 NVR0.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return DFLASH size
 *         -  00b��64KB
 *         -  01b��128KB
 *         -  10b��reserved
 *         -  11b��reserve d
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetSysInfoDFlashSize(const SimRegType *obj)
{
    return ((obj->SYS_INFO & SIM_SYS_INFO_DFLASH_SIZE_MASK) >> SIM_SYS_INFO_DFLASH_SIZE_SHIFT);
}

/*! \brief Gets the PFLASH size
 *
 * This function gets the current PFLASH size.
 * Its value is loaded during POR/LVR/STANDBY reset from FLASH0  NVR0.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return PFLASH size
 *         -  00b��256KB
 *         -  01b��512KB
 *         -  10b��1MB
 *         -  11b��reserve d
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetSysInfoPFlashSize(const SimRegType *obj)
{
    return ((obj->SYS_INFO & SIM_SYS_INFO_PFLASH_SIZE_MASK) >> SIM_SYS_INFO_PFLASH_SIZE_SHIFT);
}

/*! \brief Gets the SRAMU SIZE
 *
 * This function gets the current SRAMU SIZE.
 * Its value is loaded during POR/LVR/STANDBY reset from FLASH0 NVR0.
system SRAML size
 *
 * \param[in] obj : pointer to SIM register instance
 * \return SRAMU SIZE
 *         - 0b : 28KB
 *         - 1b : 60KB
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetSysInfoSRamUSize(const SimRegType *obj)
{
    return ((obj->SYS_INFO & SIM_SYS_INFO_SRAMU_SIZE_MASK) >> SIM_SYS_INFO_SRAMU_SIZE_SHIFT);
}

/*! \brief Gets the SRAML SIZE
 *
 * This function gets the current SRAML SIZE.
 * Its value is loaded during POR/LVR/STANDBY reset from FLASH0 NVR0.
system SRAML size
 *
 * \param[in] obj : pointer to SIM register instance
 * \return SRAML SIZE
 *         - 0b : 32KB
 *         - 1b : 64KB
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetSysInfoSRamLSize(const SimRegType *obj)
{
    return ((obj->SYS_INFO & SIM_SYS_INFO_SRAML_SIZE_MASK) >> SIM_SYS_INFO_SRAML_SIZE_SHIFT);
}

/*! \brief Gets the system package pin number
 *
 * This function gets the current system package pin number.
 * Its value is loaded during POR/LVR reset from FLASH0 NVR_CFG.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return system package pin number
 *         - 0h : 64
 *         - 1h : 100
 *         - 2h : 144
 *         - 3h : reserved

 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetSysInfoPinNum(const SimRegType *obj)
{
    return ((obj->SYS_INFO & SIM_SYS_INFO_PIN_NUM_MASK) >> SIM_SYS_INFO_PIN_NUM_SHIFT);
}

/*! \brief Gets the MFT module number
 *
 * This function gets the current MFT module number.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return MFT module number
 *         - 0b : 4, MFT0/1/2/3 is valid
 *         - 1b : 6, MFT0/1/2/3/4/5 is valid
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetPerInfoMftNum(const SimRegType *obj)
{
    return ((obj->PER_INFO & SIM_PER_INFO_MFT_NUM_MASK) >> SIM_PER_INFO_MFT_NUM_SHIFT);
}

/*! \brief Gets the CAN module number
 *
 * This function gets the current CAN module number.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return CAN module number
 *         - 0b : 3, can0/1/2 is valid
 *         - 1b : 4, can0/1/2/3 is valid
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetPerInfoCanNum(const SimRegType *obj)
{
    return ((obj->PER_INFO & SIM_PER_INFO_CAN_NUM_MASK) >> SIM_PER_INFO_CAN_NUM_SHIFT);
}

/*! \brief Gets the UART module number
 *
 * This function gets the current UART module number.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return UART module number
 *         - 0b : 3, UART0/1/2 is valid
 *         - 1b : 4, UART0/1/2/3 is valid
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetPerInfoUartNum(const SimRegType *obj)
{
    return ((obj->PER_INFO & SIM_PER_INFO_UART_NUM_MASK) >> SIM_PER_INFO_UART_NUM_SHIFT);
}

/*! \brief Gets the SPImodule number
 *
 * This function gets the current SPImodule number.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return SPImodule number
 *         - 0b : 3, SPI0/1/2 is valid
 *         - 1b : 4, SPI0/1/2/3 is valid
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetPerInfoSpiNum(const SimRegType *obj)
{
    return ((obj->PER_INFO & SIM_PER_INFO_SPI_NUM_MASK) >> SIM_PER_INFO_SPI_NUM_SHIFT);
}

/*! \brief Gets the PWM3 output channel select
 *
 * This function gets the current PWM3 output channel select.
 * channel details are same with SIM_PWM_CTRL0[PWM_FUNC0]
 *
 * \param[in] obj : pointer to SIM register instance
 * \return PWM3 output channel select

 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetPwmCtrl0PwmFunc3(const SimRegType *obj)
{
    return ((obj->PWM_CTRL0 & SIM_PWM_CTRL0_PWM_FUNC3_MASK) >> SIM_PWM_CTRL0_PWM_FUNC3_SHIFT);
}

/*! \brief Sets the PWM3 output channel select
 *
 * This function sets the PWM3 output channel select.
 * channel details are same with SIM_PWM_CTRL0[PWM_FUNC0]
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of PWM3 output channel select

 */
__attribute__((always_inline)) static inline void SimReg_SetPwmCtrl0PwmFunc3(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PWM_CTRL0;

    tmp &= ~SIM_PWM_CTRL0_PWM_FUNC3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_PWM_CTRL0_PWM_FUNC3_SHIFT)) & SIM_PWM_CTRL0_PWM_FUNC3_MASK);
    obj->PWM_CTRL0 = tmp;
}

/*! \brief Gets the PWM2 output channel select
 *
 * This function gets the current PWM2 output channel select.
 * channel details are same with SIM_PWM_CTRL0[PWM_FUNC0]
 *
 * \param[in] obj : pointer to SIM register instance
 * \return PWM2 output channel select

 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetPwmCtrl0PwmFunc2(const SimRegType *obj)
{
    return ((obj->PWM_CTRL0 & SIM_PWM_CTRL0_PWM_FUNC2_MASK) >> SIM_PWM_CTRL0_PWM_FUNC2_SHIFT);
}

/*! \brief Sets the PWM2 output channel select
 *
 * This function sets the PWM2 output channel select.
 * channel details are same with SIM_PWM_CTRL0[PWM_FUNC0]
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of PWM2 output channel select

 */
__attribute__((always_inline)) static inline void SimReg_SetPwmCtrl0PwmFunc2(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PWM_CTRL0;

    tmp &= ~SIM_PWM_CTRL0_PWM_FUNC2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_PWM_CTRL0_PWM_FUNC2_SHIFT)) & SIM_PWM_CTRL0_PWM_FUNC2_MASK);
    obj->PWM_CTRL0 = tmp;
}

/*! \brief Gets the PWM1 output channel select
 *
 * This function gets the current PWM1 output channel select.
 * channel details are same with SIM_PWM_CTRL0[PWM_FUNC0]
 *
 * \param[in] obj : pointer to SIM register instance
 * \return PWM1 output channel select

 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetPwmCtrl0PwmFunc1(const SimRegType *obj)
{
    return ((obj->PWM_CTRL0 & SIM_PWM_CTRL0_PWM_FUNC1_MASK) >> SIM_PWM_CTRL0_PWM_FUNC1_SHIFT);
}

/*! \brief Sets the PWM1 output channel select
 *
 * This function sets the PWM1 output channel select.
 * channel details are same with SIM_PWM_CTRL0[PWM_FUNC0]
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of PWM1 output channel select

 */
__attribute__((always_inline)) static inline void SimReg_SetPwmCtrl0PwmFunc1(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PWM_CTRL0;

    tmp &= ~SIM_PWM_CTRL0_PWM_FUNC1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_PWM_CTRL0_PWM_FUNC1_SHIFT)) & SIM_PWM_CTRL0_PWM_FUNC1_MASK);
    obj->PWM_CTRL0 = tmp;
}

/*! \brief Gets the PWM0 output channel select
 *
 * This function gets the current PWM0 output channel select.
 * 0: PWM0[0];1: PWM0[1];2: PWM0[2];3: PWM0[3];
4: PWM0[4];5: PWM0[5];6: PWM0[6];7: PWM0[7];
8: PWM1[0];9: PWM1[1];10: PWM1[2];11: PWM1[3];
12: PWM1[4];13: PWM1[5];14: PWM1[6];15: PWM1[7];
16: PWM2[0];17: PWM2[1];18: PWM2[2];19: PWM2[3];
20: PWM2[4];21: PWM2[5];22: PWM2[6];23: PWM2[7];
24: PWM3[0];25: PWM3[1];26: PWM3[2];27: PWM3[3];
28: PWM3[4];29: PWM3[5];30: PWM3[6];31: PWM3[7];
32: PWM4[0];33: PWM4[1];34: PWM4[2];35: PWM4[3];
36: PWM4[4];37: PWM4[5];38: PWM4[6];39: PWM4[7];
 *
 * \param[in] obj : pointer to SIM register instance
 * \return PWM0 output channel select

 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetPwmCtrl0PwmFunc0(const SimRegType *obj)
{
    return ((obj->PWM_CTRL0 & SIM_PWM_CTRL0_PWM_FUNC0_MASK) >> SIM_PWM_CTRL0_PWM_FUNC0_SHIFT);
}

/*! \brief Sets the PWM0 output channel select
 *
 * This function sets the PWM0 output channel select.
 * 0: PWM0[0];1: PWM0[1];2: PWM0[2];3: PWM0[3];
4: PWM0[4];5: PWM0[5];6: PWM0[6];7: PWM0[7];
8: PWM1[0];9: PWM1[1];10: PWM1[2];11: PWM1[3];
12: PWM1[4];13: PWM1[5];14: PWM1[6];15: PWM1[7];
16: PWM2[0];17: PWM2[1];18: PWM2[2];19: PWM2[3];
20: PWM2[4];21: PWM2[5];22: PWM2[6];23: PWM2[7];
24: PWM3[0];25: PWM3[1];26: PWM3[2];27: PWM3[3];
28: PWM3[4];29: PWM3[5];30: PWM3[6];31: PWM3[7];
32: PWM4[0];33: PWM4[1];34: PWM4[2];35: PWM4[3];
36: PWM4[4];37: PWM4[5];38: PWM4[6];39: PWM4[7];
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of PWM0 output channel select

 */
__attribute__((always_inline)) static inline void SimReg_SetPwmCtrl0PwmFunc0(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PWM_CTRL0;

    tmp &= ~SIM_PWM_CTRL0_PWM_FUNC0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_PWM_CTRL0_PWM_FUNC0_SHIFT)) & SIM_PWM_CTRL0_PWM_FUNC0_MASK);
    obj->PWM_CTRL0 = tmp;
}

/*! \brief Gets the PWM7 output channel select
 *
 * This function gets the current PWM7 output channel select.
 * channel details are same with SIM_PWM_CTRL0[PWM_FUNC0]
 *
 * \param[in] obj : pointer to SIM register instance
 * \return PWM7 output channel select

 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetPwmCtrl1PwmFunc7(const SimRegType *obj)
{
    return ((obj->PWM_CTRL1 & SIM_PWM_CTRL1_PWM_FUNC7_MASK) >> SIM_PWM_CTRL1_PWM_FUNC7_SHIFT);
}

/*! \brief Sets the PWM7 output channel select
 *
 * This function sets the PWM7 output channel select.
 * channel details are same with SIM_PWM_CTRL0[PWM_FUNC0]
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of PWM7 output channel select

 */
__attribute__((always_inline)) static inline void SimReg_SetPwmCtrl1PwmFunc7(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PWM_CTRL1;

    tmp &= ~SIM_PWM_CTRL1_PWM_FUNC7_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_PWM_CTRL1_PWM_FUNC7_SHIFT)) & SIM_PWM_CTRL1_PWM_FUNC7_MASK);
    obj->PWM_CTRL1 = tmp;
}

/*! \brief Gets the PWM6 output channel select
 *
 * This function gets the current PWM6 output channel select.
 * channel details are same with SIM_PWM_CTRL0[PWM_FUNC0]
 *
 * \param[in] obj : pointer to SIM register instance
 * \return PWM6 output channel select

 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetPwmCtrl1PwmFunc6(const SimRegType *obj)
{
    return ((obj->PWM_CTRL1 & SIM_PWM_CTRL1_PWM_FUNC6_MASK) >> SIM_PWM_CTRL1_PWM_FUNC6_SHIFT);
}

/*! \brief Sets the PWM6 output channel select
 *
 * This function sets the PWM6 output channel select.
 * channel details are same with SIM_PWM_CTRL0[PWM_FUNC0]
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of PWM6 output channel select

 */
__attribute__((always_inline)) static inline void SimReg_SetPwmCtrl1PwmFunc6(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PWM_CTRL1;

    tmp &= ~SIM_PWM_CTRL1_PWM_FUNC6_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_PWM_CTRL1_PWM_FUNC6_SHIFT)) & SIM_PWM_CTRL1_PWM_FUNC6_MASK);
    obj->PWM_CTRL1 = tmp;
}

/*! \brief Gets the PWM5 output channel select
 *
 * This function gets the current PWM5 output channel select.
 * channel details are same with SIM_PWM_CTRL0[PWM_FUNC0]
 *
 * \param[in] obj : pointer to SIM register instance
 * \return PWM5 output channel select

 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetPwmCtrl1PwmFunc5(const SimRegType *obj)
{
    return ((obj->PWM_CTRL1 & SIM_PWM_CTRL1_PWM_FUNC5_MASK) >> SIM_PWM_CTRL1_PWM_FUNC5_SHIFT);
}

/*! \brief Sets the PWM5 output channel select
 *
 * This function sets the PWM5 output channel select.
 * channel details are same with SIM_PWM_CTRL0[PWM_FUNC0]
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of PWM5 output channel select

 */
__attribute__((always_inline)) static inline void SimReg_SetPwmCtrl1PwmFunc5(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PWM_CTRL1;

    tmp &= ~SIM_PWM_CTRL1_PWM_FUNC5_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_PWM_CTRL1_PWM_FUNC5_SHIFT)) & SIM_PWM_CTRL1_PWM_FUNC5_MASK);
    obj->PWM_CTRL1 = tmp;
}

/*! \brief Gets the PWM4 output channel select
 *
 * This function gets the current PWM4 output channel select.
 * channel details are same with SIM_PWM_CTRL0[PWM_FUNC0]
 *
 * \param[in] obj : pointer to SIM register instance
 * \return PWM4 output channel select

 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetPwmCtrl1PwmFunc4(const SimRegType *obj)
{
    return ((obj->PWM_CTRL1 & SIM_PWM_CTRL1_PWM_FUNC4_MASK) >> SIM_PWM_CTRL1_PWM_FUNC4_SHIFT);
}

/*! \brief Sets the PWM4 output channel select
 *
 * This function sets the PWM4 output channel select.
 * channel details are same with SIM_PWM_CTRL0[PWM_FUNC0]
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of PWM4 output channel select

 */
__attribute__((always_inline)) static inline void SimReg_SetPwmCtrl1PwmFunc4(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PWM_CTRL1;

    tmp &= ~SIM_PWM_CTRL1_PWM_FUNC4_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_PWM_CTRL1_PWM_FUNC4_SHIFT)) & SIM_PWM_CTRL1_PWM_FUNC4_MASK);
    obj->PWM_CTRL1 = tmp;
}

/*! \brief Gets the ADC channel interleave source
 *
 * This function gets the current ADC channel interleave source.
 * bit3 controls the ADC0 channel 9 source:
0: ADC0_SE9
1: ADC1_SE9

bit2 controls the ADC0 channel 8 source:
0: ADC0_SE8
1: ADC1_SE8

bit1 controls the ADC1 channel 15 source:
0: ADC1_SE15
1: ADC0_SE15

bit0 controls the ADC1 channel 14 source:
0: ADC1_SE14
1: ADC0_SE1
 *
 * \param[in] obj : pointer to SIM register instance
 * \return ADC channel interleave source

 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetAdcILSrc(const SimRegType *obj)
{
    return ((obj->ADC & SIM_ADC_IL_SRC_MASK) >> SIM_ADC_IL_SRC_SHIFT);
}

/*! \brief Sets the ADC channel interleave source
 *
 * This function sets the ADC channel interleave source.
 * bit3 controls the ADC0 channel 9 source:
0: ADC0_SE9
1: ADC1_SE9

bit2 controls the ADC0 channel 8 source:
0: ADC0_SE8
1: ADC1_SE8

bit1 controls the ADC1 channel 15 source:
0: ADC1_SE15
1: ADC0_SE15

bit0 controls the ADC1 channel 14 source:
0: ADC1_SE14
1: ADC0_SE1
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of ADC channel interleave source

 */
__attribute__((always_inline)) static inline void SimReg_SetAdcILSrc(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->ADC;

    tmp &= ~SIM_ADC_IL_SRC_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_ADC_IL_SRC_SHIFT)) & SIM_ADC_IL_SRC_MASK);
    obj->ADC = tmp;
}

/*! \brief Gets the ADC power monitor enable
 *
 * This function gets the current ADC power monitor enable.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return ADC power monitor enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetAdcMonEn(const SimRegType *obj)
{
    return ((obj->ADC & SIM_ADC_MON_EN_MASK) >> SIM_ADC_MON_EN_SHIFT);
}

/*! \brief Sets the ADC power monitor enable
 *
 * This function sets the ADC power monitor enable.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of ADC power monitor enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void SimReg_SetAdcMonEn(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->ADC;

    tmp &= ~SIM_ADC_MON_EN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_ADC_MON_EN_SHIFT)) & SIM_ADC_MON_EN_MASK);
    obj->ADC = tmp;
}

/*! \brief Gets the power monitor source in channel 19 of ADC0/ADC1
 *
 * This function gets the current power monitor source in channel 19 of ADC0/ADC1.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return power monitor source in channel 19 of ADC0/ADC1
 *         - 00b : AVSS
 *         - 01b : AVDD
 *         - 10b : DVDD
 *         - 11b : VREFH
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetAdcMonLdoSel(const SimRegType *obj)
{
    return ((obj->ADC & SIM_ADC_MON_LDO_SEL_MASK) >> SIM_ADC_MON_LDO_SEL_SHIFT);
}

/*! \brief Sets the power monitor source in channel 19 of ADC0/ADC1
 *
 * This function sets the power monitor source in channel 19 of ADC0/ADC1.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of power monitor source in channel 19 of ADC0/ADC1
 *                    - 00b : AVSS
 *                    - 01b : AVDD
 *                    - 10b : DVDD
 *                    - 11b : VREFH
 */
__attribute__((always_inline)) static inline void SimReg_SetAdcMonLdoSel(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->ADC;

    tmp &= ~SIM_ADC_MON_LDO_SEL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_ADC_MON_LDO_SEL_SHIFT)) & SIM_ADC_MON_LDO_SEL_MASK);
    obj->ADC = tmp;
}

/*! \brief Gets the power monitor source in channel 20 of ADC0/ADC1
 *
 * This function gets the current power monitor source in channel 20 of ADC0/ADC1.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return power monitor source in channel 20 of ADC0/ADC1
 *         - 00b : AVSS
 *         - 01b : AVDD
 *         - 10b : DVDD
 *         - 11b : VREFH
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetAdcMonVoltSel(const SimRegType *obj)
{
    return ((obj->ADC & SIM_ADC_MON_VOLT_SEL_MASK) >> SIM_ADC_MON_VOLT_SEL_SHIFT);
}

/*! \brief Sets the power monitor source in channel 20 of ADC0/ADC1
 *
 * This function sets the power monitor source in channel 20 of ADC0/ADC1.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of power monitor source in channel 20 of ADC0/ADC1
 *                    - 00b : AVSS
 *                    - 01b : AVDD
 *                    - 10b : DVDD
 *                    - 11b : VREFH
 */
__attribute__((always_inline)) static inline void SimReg_SetAdcMonVoltSel(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->ADC;

    tmp &= ~SIM_ADC_MON_VOLT_SEL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_ADC_MON_VOLT_SEL_SHIFT)) & SIM_ADC_MON_VOLT_SEL_MASK);
    obj->ADC = tmp;
}

/*! \brief Gets the ADC1 trigger source
 *
 * This function gets the current ADC1 trigger source.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return ADC1 trigger source
 *         -  0b��PDB1 trigger out
 *         -  1b��TRGMUX outpu t
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetAdcTrg1Src(const SimRegType *obj)
{
    return ((obj->ADC & SIM_ADC_TRG1_SRC_MASK) >> SIM_ADC_TRG1_SRC_SHIFT);
}

/*! \brief Sets the ADC1 trigger source
 *
 * This function sets the ADC1 trigger source.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of ADC1 trigger source
 *                    -  0b��PDB1 trigger out
 *                    -  1b��TRGMUX outpu t
 */
__attribute__((always_inline)) static inline void SimReg_SetAdcTrg1Src(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->ADC;

    tmp &= ~SIM_ADC_TRG1_SRC_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_ADC_TRG1_SRC_SHIFT)) & SIM_ADC_TRG1_SRC_MASK);
    obj->ADC = tmp;
}

/*! \brief Gets the ADC1 software pre trigger source
 *
 * This function gets the current ADC1 software pre trigger source.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return ADC1 software pre trigger source
 *         - 100b : pretrigger 0
 *         - 101b : pretrigger 1
 *         - 110b : pretrigger 2
 *         - 111b : pretrigger 3
 *         - others : reserved
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetAdcPreTrg1SwSrc(const SimRegType *obj)
{
    return ((obj->ADC & SIM_ADC_PRETRG1_SW_SRC_MASK) >> SIM_ADC_PRETRG1_SW_SRC_SHIFT);
}

/*! \brief Sets the ADC1 software pre trigger source
 *
 * This function sets the ADC1 software pre trigger source.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of ADC1 software pre trigger source
 *                    - 100b : pretrigger 0
 *                    - 101b : pretrigger 1
 *                    - 110b : pretrigger 2
 *                    - 111b : pretrigger 3
 *                    - others : reserved
 */
__attribute__((always_inline)) static inline void SimReg_SetAdcPreTrg1SwSrc(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->ADC;

    tmp &= ~SIM_ADC_PRETRG1_SW_SRC_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_ADC_PRETRG1_SW_SRC_SHIFT)) & SIM_ADC_PRETRG1_SW_SRC_MASK);
    obj->ADC = tmp;
}

/*! \brief Gets the ADC1 pre trigger source
 *
 * This function gets the current ADC1 pre trigger source.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return ADC1 pre trigger source
 *         - 00b : PDB1 trigger out
 *         - 01b : TRGMUX output
 *         - 10b : software configure PRETRG1_SW_SRC
 *         - 11b : no hardware trigger
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetAdcPreTrg1Src(const SimRegType *obj)
{
    return ((obj->ADC & SIM_ADC_PRETRG1_SRC_MASK) >> SIM_ADC_PRETRG1_SRC_SHIFT);
}

/*! \brief Sets the ADC1 pre trigger source
 *
 * This function sets the ADC1 pre trigger source.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of ADC1 pre trigger source
 *                    - 00b : PDB1 trigger out
 *                    - 01b : TRGMUX output
 *                    - 10b : software configure PRETRG1_SW_SRC
 *                    - 11b : no hardware trigger
 */
__attribute__((always_inline)) static inline void SimReg_SetAdcPreTrg1Src(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->ADC;

    tmp &= ~SIM_ADC_PRETRG1_SRC_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_ADC_PRETRG1_SRC_SHIFT)) & SIM_ADC_PRETRG1_SRC_MASK);
    obj->ADC = tmp;
}

/*! \brief Gets the ADC0 trigger source
 *
 * This function gets the current ADC0 trigger source.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return ADC0 trigger source
 *         -  0b��PDB0 trigger out
 *         -  1b��TRGMUX outpu t
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetAdcTrg0Src(const SimRegType *obj)
{
    return ((obj->ADC & SIM_ADC_TRG0_SRC_MASK) >> SIM_ADC_TRG0_SRC_SHIFT);
}

/*! \brief Sets the ADC0 trigger source
 *
 * This function sets the ADC0 trigger source.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of ADC0 trigger source
 *                    -  0b��PDB0 trigger out
 *                    -  1b��TRGMUX outpu t
 */
__attribute__((always_inline)) static inline void SimReg_SetAdcTrg0Src(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->ADC;

    tmp &= ~SIM_ADC_TRG0_SRC_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_ADC_TRG0_SRC_SHIFT)) & SIM_ADC_TRG0_SRC_MASK);
    obj->ADC = tmp;
}

/*! \brief Gets the ADC0 software pre trigger source
 *
 * This function gets the current ADC0 software pre trigger source.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return ADC0 software pre trigger source
 *         - 100b : pretrigger 0
 *         - 101b : pretrigger 1
 *         - 110b : pretrigger 2
 *         - 111b : pretrigger 3
 *         - others : reserved
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetAdcPreTrg0SwSrc(const SimRegType *obj)
{
    return ((obj->ADC & SIM_ADC_PRETRG0_SW_SRC_MASK) >> SIM_ADC_PRETRG0_SW_SRC_SHIFT);
}

/*! \brief Sets the ADC0 software pre trigger source
 *
 * This function sets the ADC0 software pre trigger source.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of ADC0 software pre trigger source
 *                    - 100b : pretrigger 0
 *                    - 101b : pretrigger 1
 *                    - 110b : pretrigger 2
 *                    - 111b : pretrigger 3
 *                    - others : reserved
 */
__attribute__((always_inline)) static inline void SimReg_SetAdcPreTrg0SwSrc(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->ADC;

    tmp &= ~SIM_ADC_PRETRG0_SW_SRC_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_ADC_PRETRG0_SW_SRC_SHIFT)) & SIM_ADC_PRETRG0_SW_SRC_MASK);
    obj->ADC = tmp;
}

/*! \brief Gets the ADC0 pre trigger source
 *
 * This function gets the current ADC0 pre trigger source.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return ADC0 pre trigger source
 *         - 00b : PDB0 trigger out
 *         - 01b : TRGMUX output
 *         - 10b : software configure PRETRG1_SW_SRC
 *         - 11b : no hardware trigger
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetAdcPreTrg0Src(const SimRegType *obj)
{
    return ((obj->ADC & SIM_ADC_PRETRG0_SRC_MASK) >> SIM_ADC_PRETRG0_SRC_SHIFT);
}

/*! \brief Sets the ADC0 pre trigger source
 *
 * This function sets the ADC0 pre trigger source.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of ADC0 pre trigger source
 *                    - 00b : PDB0 trigger out
 *                    - 01b : TRGMUX output
 *                    - 10b : software configure PRETRG1_SW_SRC
 *                    - 11b : no hardware trigger
 */
__attribute__((always_inline)) static inline void SimReg_SetAdcPreTrg0Src(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->ADC;

    tmp &= ~SIM_ADC_PRETRG0_SRC_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_ADC_PRETRG0_SRC_SHIFT)) & SIM_ADC_PRETRG0_SRC_MASK);
    obj->ADC = tmp;
}

/*! \brief Gets the PDB0 and PDB1 back-to-back source select
 *
 * This function gets the current PDB0 and PDB1 back-to-back source select.
 * Selects ADC COCO source as PDB back-to-back mode
 *
 * \param[in] obj : pointer to SIM register instance
 * \return PDB0 and PDB1 back-to-back source select
 *         - 000b : PDB0 and PDB1 operates independently. PDB0 CH0 operate with ADC0 COCO[7:0], and PDB1 CH0 operate with ADC1 COCO[7:0]
 *         - 001b : Chaining of CH0-CH0 of PDB0 and PDB1. Channel0 of PDB0 and PDB1 back-to-back operation with COCO[7:0] of ADC0 and ADC1
 *         - 01xb : Inter channel chaining of PDB0 CH0 and CH1. CH0 and CH1 of PDB0 back-to-back operation with COCO[7:0] and COCO[15:8] of ADC0. PDB1 CH0 back to back operation with ADC1 COCO[7:0]
 *         - 10xb : Inter channel chaining of PDB1 CH0 and CH1. CH0 and CH1 of PDB1 back-to-back operation with COCO[7:0] and COCO[15:8] of ADC1. PDB0 CH0 back to back operation with ADC0 COCO[7:0]
 *         - 11xb : Inter channel chaining of PDB0 CH0 and CH1 and PDB1 CH0 and CH1 both. CH0 and CH1 of PDB0 back-to-back operation with COCO[7:0] and COCO[15:8] of ADC0, and CH0 and CH1 of PDB1 back-to-back operation with COCO[7:0] and COCO[15:8] of ADC1.
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetPdbBbSel(const SimRegType *obj)
{
    return ((obj->PDB & SIM_PDB_BB_SEL_MASK) >> SIM_PDB_BB_SEL_SHIFT);
}

/*! \brief Sets the PDB0 and PDB1 back-to-back source select
 *
 * This function sets the PDB0 and PDB1 back-to-back source select.
 * Selects ADC COCO source as PDB back-to-back mode
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of PDB0 and PDB1 back-to-back source select
 *                    - 000b : PDB0 and PDB1 operates independently. PDB0 CH0 operate with ADC0 COCO[7:0], and PDB1 CH0 operate with ADC1 COCO[7:0]
 *                    - 001b : Chaining of CH0-CH0 of PDB0 and PDB1. Channel0 of PDB0 and PDB1 back-to-back operation with COCO[7:0] of ADC0 and ADC1
 *                    - 01xb : Inter channel chaining of PDB0 CH0 and CH1. CH0 and CH1 of PDB0 back-to-back operation with COCO[7:0] and COCO[15:8] of ADC0. PDB1 CH0 back to back operation with ADC1 COCO[7:0]
 *                    - 10xb : Inter channel chaining of PDB1 CH0 and CH1. CH0 and CH1 of PDB1 back-to-back operation with COCO[7:0] and COCO[15:8] of ADC1. PDB0 CH0 back to back operation with ADC0 COCO[7:0]
 *                    - 11xb : Inter channel chaining of PDB0 CH0 and CH1 and PDB1 CH0 and CH1 both. CH0 and CH1 of PDB0 back-to-back operation with COCO[7:0] and COCO[15:8] of ADC0, and CH0 and CH1 of PDB1 back-to-back operation with COCO[7:0] and COCO[15:8] of ADC1.
 */
__attribute__((always_inline)) static inline void SimReg_SetPdbBbSel(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PDB;

    tmp &= ~SIM_PDB_BB_SEL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_PDB_BB_SEL_SHIFT)) & SIM_PDB_BB_SEL_MASK);
    obj->PDB = tmp;
}

/*! \brief Gets the I2S Slave dma or interrupt mode
 *
 * This function gets the current I2S Slave dma or interrupt mode.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return I2S Slave dma or interrupt mode
 *         - 0b : interrupt
 *         - 1b : dma
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetI2sSlvDmaIrq(const SimRegType *obj)
{
    return ((obj->I2S & SIM_I2S_SLV_DMA_IRQ_MASK) >> SIM_I2S_SLV_DMA_IRQ_SHIFT);
}

/*! \brief Sets the I2S Slave dma or interrupt mode
 *
 * This function sets the I2S Slave dma or interrupt mode.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of I2S Slave dma or interrupt mode
 *                    - 0b : interrupt
 *                    - 1b : dma
 */
__attribute__((always_inline)) static inline void SimReg_SetI2sSlvDmaIrq(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->I2S;

    tmp &= ~SIM_I2S_SLV_DMA_IRQ_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_I2S_SLV_DMA_IRQ_SHIFT)) & SIM_I2S_SLV_DMA_IRQ_MASK);
    obj->I2S = tmp;
}

/*! \brief Gets the I2S Master dma or interrupt mode
 *
 * This function gets the current I2S Master dma or interrupt mode.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return I2S Master dma or interrupt mode
 *         - 0b : interrupt
 *         - 1b : dma
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetI2sMstDmaIrq(const SimRegType *obj)
{
    return ((obj->I2S & SIM_I2S_MST_DMA_IRQ_MASK) >> SIM_I2S_MST_DMA_IRQ_SHIFT);
}

/*! \brief Sets the I2S Master dma or interrupt mode
 *
 * This function sets the I2S Master dma or interrupt mode.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of I2S Master dma or interrupt mode
 *                    - 0b : interrupt
 *                    - 1b : dma
 */
__attribute__((always_inline)) static inline void SimReg_SetI2sMstDmaIrq(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->I2S;

    tmp &= ~SIM_I2S_MST_DMA_IRQ_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_I2S_MST_DMA_IRQ_SHIFT)) & SIM_I2S_MST_DMA_IRQ_MASK);
    obj->I2S = tmp;
}

/*! \brief Gets the I2S mode
 *
 * This function gets the current I2S mode.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return I2S mode
 *         - 0b : slave
 *         - 1b : master
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetI2sMode(const SimRegType *obj)
{
    return ((obj->I2S & SIM_I2S_MODE_MASK) >> SIM_I2S_MODE_SHIFT);
}

/*! \brief Sets the I2S mode
 *
 * This function sets the I2S mode.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of I2S mode
 *                    - 0b : slave
 *                    - 1b : master
 */
__attribute__((always_inline)) static inline void SimReg_SetI2sMode(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->I2S;

    tmp &= ~SIM_I2S_MODE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_I2S_MODE_SHIFT)) & SIM_I2S_MODE_MASK);
    obj->I2S = tmp;
}

/*! \brief Gets the MFT3 Fault X Select
 *
 * This function gets the current MFT3 Fault X Select.
 * Selects the source of the MFT3 fault. Every bit means one fault input, respectively.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return MFT3 Fault X Select
 *         - 0b : MFT3_FLTx pin
 *         - 1b : TRGMUX_MFT3 out
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetMftCtrl0Mft3FltSel(const SimRegType *obj)
{
    return ((obj->MFT_CTRL0 & SIM_MFT_CTRL0_MFT3_FLT_SEL_MASK) >> SIM_MFT_CTRL0_MFT3_FLT_SEL_SHIFT);
}

/*! \brief Sets the MFT3 Fault X Select
 *
 * This function sets the MFT3 Fault X Select.
 * Selects the source of the MFT3 fault. Every bit means one fault input, respectively.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of MFT3 Fault X Select
 *                    - 0b : MFT3_FLTx pin
 *                    - 1b : TRGMUX_MFT3 out
 */
__attribute__((always_inline)) static inline void SimReg_SetMftCtrl0Mft3FltSel(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT_CTRL0;

    tmp &= ~SIM_MFT_CTRL0_MFT3_FLT_SEL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_MFT_CTRL0_MFT3_FLT_SEL_SHIFT)) & SIM_MFT_CTRL0_MFT3_FLT_SEL_MASK);
    obj->MFT_CTRL0 = tmp;
}

/*! \brief Gets the MFT2 Fault X Select
 *
 * This function gets the current MFT2 Fault X Select.
 * Selects the source of the MFT3 fault. Every bit means one fault input, respectively.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return MFT2 Fault X Select
 *         - 0b : MFT2_FLTx pin
 *         - 1b : TRGMUX_MFT2 out
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetMftCtrl0Mft2FltSel(const SimRegType *obj)
{
    return ((obj->MFT_CTRL0 & SIM_MFT_CTRL0_MFT2_FLT_SEL_MASK) >> SIM_MFT_CTRL0_MFT2_FLT_SEL_SHIFT);
}

/*! \brief Sets the MFT2 Fault X Select
 *
 * This function sets the MFT2 Fault X Select.
 * Selects the source of the MFT3 fault. Every bit means one fault input, respectively.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of MFT2 Fault X Select
 *                    - 0b : MFT2_FLTx pin
 *                    - 1b : TRGMUX_MFT2 out
 */
__attribute__((always_inline)) static inline void SimReg_SetMftCtrl0Mft2FltSel(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT_CTRL0;

    tmp &= ~SIM_MFT_CTRL0_MFT2_FLT_SEL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_MFT_CTRL0_MFT2_FLT_SEL_SHIFT)) & SIM_MFT_CTRL0_MFT2_FLT_SEL_MASK);
    obj->MFT_CTRL0 = tmp;
}

/*! \brief Gets the MFT1 Fault X Select
 *
 * This function gets the current MFT1 Fault X Select.
 * Selects the source of the MFT1 fault. Every bit means one fault input, respectively.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return MFT1 Fault X Select
 *         - 0b : MFT1_FLTx pin
 *         - 1b : TRGMUX_MFT1 out
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetMftCtrl0Mft1FltSel(const SimRegType *obj)
{
    return ((obj->MFT_CTRL0 & SIM_MFT_CTRL0_MFT1_FLT_SEL_MASK) >> SIM_MFT_CTRL0_MFT1_FLT_SEL_SHIFT);
}

/*! \brief Sets the MFT1 Fault X Select
 *
 * This function sets the MFT1 Fault X Select.
 * Selects the source of the MFT1 fault. Every bit means one fault input, respectively.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of MFT1 Fault X Select
 *                    - 0b : MFT1_FLTx pin
 *                    - 1b : TRGMUX_MFT1 out
 */
__attribute__((always_inline)) static inline void SimReg_SetMftCtrl0Mft1FltSel(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT_CTRL0;

    tmp &= ~SIM_MFT_CTRL0_MFT1_FLT_SEL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_MFT_CTRL0_MFT1_FLT_SEL_SHIFT)) & SIM_MFT_CTRL0_MFT1_FLT_SEL_MASK);
    obj->MFT_CTRL0 = tmp;
}

/*! \brief Gets the MFT0 Fault X Select
 *
 * This function gets the current MFT0 Fault X Select.
 * Selects the source of the MFT0 fault. Every bit means one fault input, respectively.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return MFT0 Fault X Select
 *         - 0b : MFT0_FLTx pin
 *         - 1b : TRGMUX_MFT0 out
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetMftCtrl0Mft0FltSel(const SimRegType *obj)
{
    return ((obj->MFT_CTRL0 & SIM_MFT_CTRL0_MFT0_FLT_SEL_MASK) >> SIM_MFT_CTRL0_MFT0_FLT_SEL_SHIFT);
}

/*! \brief Sets the MFT0 Fault X Select
 *
 * This function sets the MFT0 Fault X Select.
 * Selects the source of the MFT0 fault. Every bit means one fault input, respectively.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of MFT0 Fault X Select
 *                    - 0b : MFT0_FLTx pin
 *                    - 1b : TRGMUX_MFT0 out
 */
__attribute__((always_inline)) static inline void SimReg_SetMftCtrl0Mft0FltSel(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT_CTRL0;

    tmp &= ~SIM_MFT_CTRL0_MFT0_FLT_SEL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_MFT_CTRL0_MFT0_FLT_SEL_SHIFT)) & SIM_MFT_CTRL0_MFT0_FLT_SEL_MASK);
    obj->MFT_CTRL0 = tmp;
}

/*! \brief Gets the MFT global load enable
 *
 * This function gets the current MFT global load enable.
 * This bit is not self-clearing. For subsequent reload operations, it should be cleared and then set.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return MFT global load enable
 *         - 0b : MFT Global load mechanism disabled.
 *         - 1b : MFT Global load mechanism enabled
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetMftCtrl0GldOk(const SimRegType *obj)
{
    return ((obj->MFT_CTRL0 & SIM_MFT_CTRL0_GLDOK_MASK) >> SIM_MFT_CTRL0_GLDOK_SHIFT);
}

/*! \brief Sets the MFT global load enable
 *
 * This function sets the MFT global load enable.
 * This bit is not self-clearing. For subsequent reload operations, it should be cleared and then set.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of MFT global load enable
 *                    - 0b : MFT Global load mechanism disabled.
 *                    - 1b : MFT Global load mechanism enabled
 */
__attribute__((always_inline)) static inline void SimReg_SetMftCtrl0GldOk(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT_CTRL0;

    tmp &= ~SIM_MFT_CTRL0_GLDOK_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_MFT_CTRL0_GLDOK_SHIFT)) & SIM_MFT_CTRL0_GLDOK_MASK);
    obj->MFT_CTRL0 = tmp;
}

/*! \brief Gets the MFT5 Sync Bit
 *
 * This function gets the current MFT5 Sync Bit.
 * This is used as trigger source for MFT
 *
 * \param[in] obj : pointer to SIM register instance
 * \return MFT5 Sync Bit

 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetMftCtrl1Mft5SyncBit(const SimRegType *obj)
{
    return ((obj->MFT_CTRL1 & SIM_MFT_CTRL1_MFT5SYNCBIT_MASK) >> SIM_MFT_CTRL1_MFT5SYNCBIT_SHIFT);
}

/*! \brief Sets the MFT5 Sync Bit
 *
 * This function sets the MFT5 Sync Bit.
 * This is used as trigger source for MFT
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of MFT5 Sync Bit

 */
__attribute__((always_inline)) static inline void SimReg_SetMftCtrl1Mft5SyncBit(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT_CTRL1;

    tmp &= ~SIM_MFT_CTRL1_MFT5SYNCBIT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_MFT_CTRL1_MFT5SYNCBIT_SHIFT)) & SIM_MFT_CTRL1_MFT5SYNCBIT_MASK);
    obj->MFT_CTRL1 = tmp;
}

/*! \brief Gets the MFT4 Sync Bit
 *
 * This function gets the current MFT4 Sync Bit.
 * This is used as trigger source for MFT
 *
 * \param[in] obj : pointer to SIM register instance
 * \return MFT4 Sync Bit

 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetMftCtrl1Mft4SyncBit(const SimRegType *obj)
{
    return ((obj->MFT_CTRL1 & SIM_MFT_CTRL1_MFT4SYNCBIT_MASK) >> SIM_MFT_CTRL1_MFT4SYNCBIT_SHIFT);
}

/*! \brief Sets the MFT4 Sync Bit
 *
 * This function sets the MFT4 Sync Bit.
 * This is used as trigger source for MFT
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of MFT4 Sync Bit

 */
__attribute__((always_inline)) static inline void SimReg_SetMftCtrl1Mft4SyncBit(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT_CTRL1;

    tmp &= ~SIM_MFT_CTRL1_MFT4SYNCBIT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_MFT_CTRL1_MFT4SYNCBIT_SHIFT)) & SIM_MFT_CTRL1_MFT4SYNCBIT_MASK);
    obj->MFT_CTRL1 = tmp;
}

/*! \brief Gets the MFT3 Sync Bit
 *
 * This function gets the current MFT3 Sync Bit.
 * This is used as trigger source for MFT
 *
 * \param[in] obj : pointer to SIM register instance
 * \return MFT3 Sync Bit

 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetMftCtrl1Mft3SyncBit(const SimRegType *obj)
{
    return ((obj->MFT_CTRL1 & SIM_MFT_CTRL1_MFT3SYNCBIT_MASK) >> SIM_MFT_CTRL1_MFT3SYNCBIT_SHIFT);
}

/*! \brief Sets the MFT3 Sync Bit
 *
 * This function sets the MFT3 Sync Bit.
 * This is used as trigger source for MFT
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of MFT3 Sync Bit

 */
__attribute__((always_inline)) static inline void SimReg_SetMftCtrl1Mft3SyncBit(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT_CTRL1;

    tmp &= ~SIM_MFT_CTRL1_MFT3SYNCBIT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_MFT_CTRL1_MFT3SYNCBIT_SHIFT)) & SIM_MFT_CTRL1_MFT3SYNCBIT_MASK);
    obj->MFT_CTRL1 = tmp;
}

/*! \brief Gets the MFT2 Sync Bit
 *
 * This function gets the current MFT2 Sync Bit.
 * This is used as trigger source for MFT
 *
 * \param[in] obj : pointer to SIM register instance
 * \return MFT2 Sync Bit

 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetMftCtrl1Mft2SyncBit(const SimRegType *obj)
{
    return ((obj->MFT_CTRL1 & SIM_MFT_CTRL1_MFT2SYNCBIT_MASK) >> SIM_MFT_CTRL1_MFT2SYNCBIT_SHIFT);
}

/*! \brief Sets the MFT2 Sync Bit
 *
 * This function sets the MFT2 Sync Bit.
 * This is used as trigger source for MFT
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of MFT2 Sync Bit

 */
__attribute__((always_inline)) static inline void SimReg_SetMftCtrl1Mft2SyncBit(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT_CTRL1;

    tmp &= ~SIM_MFT_CTRL1_MFT2SYNCBIT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_MFT_CTRL1_MFT2SYNCBIT_SHIFT)) & SIM_MFT_CTRL1_MFT2SYNCBIT_MASK);
    obj->MFT_CTRL1 = tmp;
}

/*! \brief Gets the MFT1 Sync Bit
 *
 * This function gets the current MFT1 Sync Bit.
 * This is used as trigger source for MFT
 *
 * \param[in] obj : pointer to SIM register instance
 * \return MFT1 Sync Bit

 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetMftCtrl1Mft1SyncBit(const SimRegType *obj)
{
    return ((obj->MFT_CTRL1 & SIM_MFT_CTRL1_MFT1SYNCBIT_MASK) >> SIM_MFT_CTRL1_MFT1SYNCBIT_SHIFT);
}

/*! \brief Sets the MFT1 Sync Bit
 *
 * This function sets the MFT1 Sync Bit.
 * This is used as trigger source for MFT
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of MFT1 Sync Bit

 */
__attribute__((always_inline)) static inline void SimReg_SetMftCtrl1Mft1SyncBit(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT_CTRL1;

    tmp &= ~SIM_MFT_CTRL1_MFT1SYNCBIT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_MFT_CTRL1_MFT1SYNCBIT_SHIFT)) & SIM_MFT_CTRL1_MFT1SYNCBIT_MASK);
    obj->MFT_CTRL1 = tmp;
}

/*! \brief Gets the MFT0 Sync Bit
 *
 * This function gets the current MFT0 Sync Bit.
 * This is used as trigger source for MFT
 *
 * \param[in] obj : pointer to SIM register instance
 * \return MFT0 Sync Bit

 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetMftCtrl1Mft0SyncBit(const SimRegType *obj)
{
    return ((obj->MFT_CTRL1 & SIM_MFT_CTRL1_MFT0SYNCBIT_MASK) >> SIM_MFT_CTRL1_MFT0SYNCBIT_SHIFT);
}

/*! \brief Sets the MFT0 Sync Bit
 *
 * This function sets the MFT0 Sync Bit.
 * This is used as trigger source for MFT
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of MFT0 Sync Bit

 */
__attribute__((always_inline)) static inline void SimReg_SetMftCtrl1Mft0SyncBit(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT_CTRL1;

    tmp &= ~SIM_MFT_CTRL1_MFT0SYNCBIT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_MFT_CTRL1_MFT0SYNCBIT_SHIFT)) & SIM_MFT_CTRL1_MFT0SYNCBIT_MASK);
    obj->MFT_CTRL1 = tmp;
}

/*! \brief Gets the MFT1 CH0 Select
 *
 * This function gets the current MFT1 CH0 Select.
 * Selects MFT1 Channel0's input
 *
 * \param[in] obj : pointer to SIM register instance
 * \return MFT1 CH0 Select
 *         - 0b : MFT1_CH0 input from PAD
 *         - 1b : CMP0 output
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetMftCtrl1Mft1Ch0Sel(const SimRegType *obj)
{
    return ((obj->MFT_CTRL1 & SIM_MFT_CTRL1_MFT1CH0SEL_MASK) >> SIM_MFT_CTRL1_MFT1CH0SEL_SHIFT);
}

/*! \brief Sets the MFT1 CH0 Select
 *
 * This function sets the MFT1 CH0 Select.
 * Selects MFT1 Channel0's input
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of MFT1 CH0 Select
 *                    - 0b : MFT1_CH0 input from PAD
 *                    - 1b : CMP0 output
 */
__attribute__((always_inline)) static inline void SimReg_SetMftCtrl1Mft1Ch0Sel(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT_CTRL1;

    tmp &= ~SIM_MFT_CTRL1_MFT1CH0SEL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_MFT_CTRL1_MFT1CH0SEL_SHIFT)) & SIM_MFT_CTRL1_MFT1CH0SEL_MASK);
    obj->MFT_CTRL1 = tmp;
}

/*! \brief Gets the MFT2 CH0 Select
 *
 * This function gets the current MFT2 CH0 Select.
 * Selects MFT2 Channel0's input
 *
 * \param[in] obj : pointer to SIM register instance
 * \return MFT2 CH0 Select
 *         - 00b  : MFT2_CH0 input from PAD
 *         - 01b  : CMP0 output
 *         - 10b  : Reserved
 *         - 11b  : Reserved
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetMftCtrl1Mft2Ch0Sel(const SimRegType *obj)
{
    return ((obj->MFT_CTRL1 & SIM_MFT_CTRL1_MFT2CH0SEL_MASK) >> SIM_MFT_CTRL1_MFT2CH0SEL_SHIFT);
}

/*! \brief Sets the MFT2 CH0 Select
 *
 * This function sets the MFT2 CH0 Select.
 * Selects MFT2 Channel0's input
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of MFT2 CH0 Select
 *                    - 00b  : MFT2_CH0 input from PAD
 *                    - 01b  : CMP0 output
 *                    - 10b  : Reserved
 *                    - 11b  : Reserved
 */
__attribute__((always_inline)) static inline void SimReg_SetMftCtrl1Mft2Ch0Sel(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT_CTRL1;

    tmp &= ~SIM_MFT_CTRL1_MFT2CH0SEL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_MFT_CTRL1_MFT2CH0SEL_SHIFT)) & SIM_MFT_CTRL1_MFT2CH0SEL_MASK);
    obj->MFT_CTRL1 = tmp;
}

/*! \brief Gets the MFT2 CH1 Select
 *
 * This function gets the current MFT2 CH1 Select.
 * Selects MFT2 CH1 input
 *
 * \param[in] obj : pointer to SIM register instance
 * \return MFT2 CH1 Select
 *         - 0b : MFT2_CH1 input
 *         - 1b : exclusive OR of MFT2_CH0,MFT2_CH1,and MFT1_CH1
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetMftCtrl1Mft2Ch1Sel(const SimRegType *obj)
{
    return ((obj->MFT_CTRL1 & SIM_MFT_CTRL1_MFT2CH1SEL_MASK) >> SIM_MFT_CTRL1_MFT2CH1SEL_SHIFT);
}

/*! \brief Sets the MFT2 CH1 Select
 *
 * This function sets the MFT2 CH1 Select.
 * Selects MFT2 CH1 input
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of MFT2 CH1 Select
 *                    - 0b : MFT2_CH1 input
 *                    - 1b : exclusive OR of MFT2_CH0,MFT2_CH1,and MFT1_CH1
 */
__attribute__((always_inline)) static inline void SimReg_SetMftCtrl1Mft2Ch1Sel(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT_CTRL1;

    tmp &= ~SIM_MFT_CTRL1_MFT2CH1SEL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_MFT_CTRL1_MFT2CH1SEL_SHIFT)) & SIM_MFT_CTRL1_MFT2CH1SEL_MASK);
    obj->MFT_CTRL1 = tmp;
}

/*! \brief Gets the MFT0 channel modulation select with MFT1_CH1
 *
 * This function gets the current MFT0 channel modulation select with MFT1_CH1.
 * Bits 7 to 0 of this field are for channel 7 to 0, respectively. For each channel,
 *
 * \param[in] obj : pointer to SIM register instance
 * \return MFT0 channel modulation select with MFT1_CH1
 *         - 0b : No modulation with MFT1_CH1
 *         - 1b : Modulation with MFT1_CH1
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetMftCtrl1Mft0OutSel(const SimRegType *obj)
{
    return ((obj->MFT_CTRL1 & SIM_MFT_CTRL1_MFT0_OUTSEL_MASK) >> SIM_MFT_CTRL1_MFT0_OUTSEL_SHIFT);
}

/*! \brief Sets the MFT0 channel modulation select with MFT1_CH1
 *
 * This function sets the MFT0 channel modulation select with MFT1_CH1.
 * Bits 7 to 0 of this field are for channel 7 to 0, respectively. For each channel,
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of MFT0 channel modulation select with MFT1_CH1
 *                    - 0b : No modulation with MFT1_CH1
 *                    - 1b : Modulation with MFT1_CH1
 */
__attribute__((always_inline)) static inline void SimReg_SetMftCtrl1Mft0OutSel(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT_CTRL1;

    tmp &= ~SIM_MFT_CTRL1_MFT0_OUTSEL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_MFT_CTRL1_MFT0_OUTSEL_SHIFT)) & SIM_MFT_CTRL1_MFT0_OUTSEL_MASK);
    obj->MFT_CTRL1 = tmp;
}

/*! \brief Gets the MFT3 channel modulation select with MFT2_CH1
 *
 * This function gets the current MFT3 channel modulation select with MFT2_CH1.
 * Bits 7 to 0 of this field are for channel 7 to 0, respectively. For each channel,
 *
 * \param[in] obj : pointer to SIM register instance
 * \return MFT3 channel modulation select with MFT2_CH1
 *         - 0b : No modulation with MFT2_CH1
 *         - 1b : Modulation with MFT2_CH1
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetMftCtrl1Mft3OutSel(const SimRegType *obj)
{
    return ((obj->MFT_CTRL1 & SIM_MFT_CTRL1_MFT3_OUTSEL_MASK) >> SIM_MFT_CTRL1_MFT3_OUTSEL_SHIFT);
}

/*! \brief Sets the MFT3 channel modulation select with MFT2_CH1
 *
 * This function sets the MFT3 channel modulation select with MFT2_CH1.
 * Bits 7 to 0 of this field are for channel 7 to 0, respectively. For each channel,
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of MFT3 channel modulation select with MFT2_CH1
 *                    - 0b : No modulation with MFT2_CH1
 *                    - 1b : Modulation with MFT2_CH1
 */
__attribute__((always_inline)) static inline void SimReg_SetMftCtrl1Mft3OutSel(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MFT_CTRL1;

    tmp &= ~SIM_MFT_CTRL1_MFT3_OUTSEL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_MFT_CTRL1_MFT3_OUTSEL_SHIFT)) & SIM_MFT_CTRL1_MFT3_OUTSEL_MASK);
    obj->MFT_CTRL1 = tmp;
}

/*! \brief Gets the flash load is done
 *
 * This function gets the current flash load is done.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return flash load is done
 *         - 0b : during load progress
 *         - 1b : load done
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetFlashLoadDone(const SimRegType *obj)
{
    return ((obj->FLASH & SIM_FLASH_LOAD_DONE_MASK) >> SIM_FLASH_LOAD_DONE_SHIFT);
}

/*! \brief Gets the flash is blank
 *
 * This function gets the current flash is blank.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return flash is blank
 *         - 0b : flash is not blank
 *         - 1b : flash is blank
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetFlashVirginFlag(const SimRegType *obj)
{
    return ((obj->FLASH & SIM_FLASH_VIRGIN_FLAG_MASK) >> SIM_FLASH_VIRGIN_FLAG_SHIFT);
}

/*! \brief Gets the dflash prefetch buffer flush
 *
 * This function gets the current dflash prefetch buffer flush.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return dflash prefetch buffer flush
 *         - 0b : do not flush dflash prefetch buffer;
 *         - 1b : flush dflash prefetch buffer;
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetFlashDFlsFlushEn(const SimRegType *obj)
{
    return ((obj->FLASH & SIM_FLASH_DFLS_FLUSH_EN_MASK) >> SIM_FLASH_DFLS_FLUSH_EN_SHIFT);
}

/*! \brief Sets the dflash prefetch buffer flush
 *
 * This function sets the dflash prefetch buffer flush.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of dflash prefetch buffer flush
 *                    - 0b : do not flush dflash prefetch buffer;
 *                    - 1b : flush dflash prefetch buffer;
 */
__attribute__((always_inline)) static inline void SimReg_SetFlashDFlsFlushEn(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->FLASH;

    tmp &= ~SIM_FLASH_DFLS_FLUSH_EN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_FLASH_DFLS_FLUSH_EN_SHIFT)) & SIM_FLASH_DFLS_FLUSH_EN_MASK);
    obj->FLASH = tmp;
}

/*! \brief Gets the pflash prefetch buffer flush
 *
 * This function gets the current pflash prefetch buffer flush.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return pflash prefetch buffer flush
 *         - 0b : do not flush pflash prefetch buffer;
 *         - 1b : flush pflash prefetch buffer;
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetFlashPFlsFlushEn(const SimRegType *obj)
{
    return ((obj->FLASH & SIM_FLASH_PFLS_FLUSH_EN_MASK) >> SIM_FLASH_PFLS_FLUSH_EN_SHIFT);
}

/*! \brief Sets the pflash prefetch buffer flush
 *
 * This function sets the pflash prefetch buffer flush.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of pflash prefetch buffer flush
 *                    - 0b : do not flush pflash prefetch buffer;
 *                    - 1b : flush pflash prefetch buffer;
 */
__attribute__((always_inline)) static inline void SimReg_SetFlashPFlsFlushEn(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->FLASH;

    tmp &= ~SIM_FLASH_PFLS_FLUSH_EN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_FLASH_PFLS_FLUSH_EN_SHIFT)) & SIM_FLASH_PFLS_FLUSH_EN_MASK);
    obj->FLASH = tmp;
}

/*! \brief Gets the dflash prefetch enable
 *
 * This function gets the current dflash prefetch enable.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return dflash prefetch enable
 *         - 0b : disable dflash prefetch;
 *         - 1b : enable dflash prefetch;
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetFlashDFlsPfbEn(const SimRegType *obj)
{
    return ((obj->FLASH & SIM_FLASH_DFLS_PFB_EN_MASK) >> SIM_FLASH_DFLS_PFB_EN_SHIFT);
}

/*! \brief Sets the dflash prefetch enable
 *
 * This function sets the dflash prefetch enable.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of dflash prefetch enable
 *                    - 0b : disable dflash prefetch;
 *                    - 1b : enable dflash prefetch;
 */
__attribute__((always_inline)) static inline void SimReg_SetFlashDFlsPfbEn(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->FLASH;

    tmp &= ~SIM_FLASH_DFLS_PFB_EN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_FLASH_DFLS_PFB_EN_SHIFT)) & SIM_FLASH_DFLS_PFB_EN_MASK);
    obj->FLASH = tmp;
}

/*! \brief Gets the pflash prefetch enable
 *
 * This function gets the current pflash prefetch enable.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return pflash prefetch enable
 *         - 0b : disable pflash prefetch;
 *         - 1b : enable pflash prefetch;
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetFlashPFlsPfbEn(const SimRegType *obj)
{
    return ((obj->FLASH & SIM_FLASH_PFLS_PFB_EN_MASK) >> SIM_FLASH_PFLS_PFB_EN_SHIFT);
}

/*! \brief Sets the pflash prefetch enable
 *
 * This function sets the pflash prefetch enable.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of pflash prefetch enable
 *                    - 0b : disable pflash prefetch;
 *                    - 1b : enable pflash prefetch;
 */
__attribute__((always_inline)) static inline void SimReg_SetFlashPFlsPfbEn(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->FLASH;

    tmp &= ~SIM_FLASH_PFLS_PFB_EN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_FLASH_PFLS_PFB_EN_SHIFT)) & SIM_FLASH_PFLS_PFB_EN_MASK);
    obj->FLASH = tmp;
}

/*! \brief Gets the Unique Identification[127:96]
 *
 * This function gets the current Unique Identification[127:96].
 *
 * \param[in] obj : pointer to SIM register instance
 * \return Unique Identification[127:96]

 */
__attribute__((always_inline)) static inline uint32_t SimReg_GetUdidH(const SimRegType *obj)
{
    return ((obj->UDIDH & SIM_UDIDH_H_MASK) >> SIM_UDIDH_H_SHIFT);
}

/*! \brief Gets the Unique Identification[95:64]
 *
 * This function gets the current Unique Identification[95:64].
 *
 * \param[in] obj : pointer to SIM register instance
 * \return Unique Identification[95:64]

 */
__attribute__((always_inline)) static inline uint32_t SimReg_GetUdidMH(const SimRegType *obj)
{
    return ((obj->UDIDMH & SIM_UDIDMH_MH_MASK) >> SIM_UDIDMH_MH_SHIFT);
}

/*! \brief Gets the Unique Identification[63:32]
 *
 * This function gets the current Unique Identification[63:32].
 *
 * \param[in] obj : pointer to SIM register instance
 * \return Unique Identification[63:32]

 */
__attribute__((always_inline)) static inline uint32_t SimReg_GetUdidML(const SimRegType *obj)
{
    return ((obj->UDIDML & SIM_UDIDML_ML_MASK) >> SIM_UDIDML_ML_SHIFT);
}

/*! \brief Gets the Unique Identification[31:0]
 *
 * This function gets the current Unique Identification[31:0].
 *
 * \param[in] obj : pointer to SIM register instance
 * \return Unique Identification[31:0]

 */
__attribute__((always_inline)) static inline uint32_t SimReg_GetUdidL(const SimRegType *obj)
{
    return ((obj->UDIDL & SIM_UDIDL_L_MASK) >> SIM_UDIDL_L_SHIFT);
}

/*! \brief Gets the System Device Identification[63:32]
 *
 * This function gets the current System Device Identification[63:32].
 *
 * \param[in] obj : pointer to SIM register instance
 * \return System Device Identification[63:32]

 */
__attribute__((always_inline)) static inline uint32_t SimReg_GetSdidH(const SimRegType *obj)
{
    return ((obj->SDIDH & SIM_SDIDH_IDH_MASK) >> SIM_SDIDH_IDH_SHIFT);
}

/*! \brief Gets the System Device Identification[31:0]
 *
 * This function gets the current System Device Identification[31:0].
 *
 * \param[in] obj : pointer to SIM register instance
 * \return System Device Identification[31:0]

 */
__attribute__((always_inline)) static inline uint32_t SimReg_GetSdidL(const SimRegType *obj)
{
    return ((obj->SDIDL & SIM_SDIDL_IDL_MASK) >> SIM_SDIDL_IDL_SHIFT);
}

/*! \brief Gets the Software trigger to TRGMUX
 *
 * This function gets the current Software trigger to TRGMUX.
 * Writing to this bit generates software trigger to peripheral
 *
 * \param[in] obj : pointer to SIM register instance
 * \return Software trigger to TRGMUX

 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetSwTrg(const SimRegType *obj)
{
    return ((obj->SW_TRG & SIM_SW_TRG_SW_TRG_MASK) >> SIM_SW_TRG_SW_TRG_SHIFT);
}

/*! \brief Sets the Software trigger to TRGMUX
 *
 * This function sets the Software trigger to TRGMUX.
 * Writing to this bit generates software trigger to peripheral
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of Software trigger to TRGMUX

 */
__attribute__((always_inline)) static inline void SimReg_SetSwTrg(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_TRG;

    tmp &= ~SIM_SW_TRG_SW_TRG_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_SW_TRG_SW_TRG_SHIFT)) & SIM_SW_TRG_SW_TRG_MASK);
    obj->SW_TRG = tmp;
}

/*! \brief Gets the E2E control
 *
 * This function gets the current E2E control.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return E2E control
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetE2eCrEn(const SimRegType *obj)
{
    return ((obj->E2E_CR & SIM_E2E_CR_EN_MASK) >> SIM_E2E_CR_EN_SHIFT);
}

/*! \brief Sets the E2E control
 *
 * This function sets the E2E control.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of E2E control
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void SimReg_SetE2eCrEn(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->E2E_CR;

    tmp &= ~SIM_E2E_CR_EN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_E2E_CR_EN_SHIFT)) & SIM_E2E_CR_EN_MASK);
    obj->E2E_CR = tmp;
}

/*! \brief Gets the E2E channel  error injection control
 *
 * This function gets the current E2E channel  error injection control.
 * Each channel has its own error injection enable.For each channel:
 *
 * \param[in] obj : pointer to SIM register instance
 * \return E2E channel  error injection control
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint16_t SimReg_GetE2eInjChEn(const SimRegType *obj)
{
    return ((obj->E2E_INJ & SIM_E2E_INJ_CH_EN_MASK) >> SIM_E2E_INJ_CH_EN_SHIFT);
}

/*! \brief Sets the E2E channel  error injection control
 *
 * This function sets the E2E channel  error injection control.
 * Each channel has its own error injection enable.For each channel:
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of E2E channel  error injection control
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void SimReg_SetE2eInjChEn(SimRegType *obj, uint16_t value)
{
    uint32_t tmp = obj->E2E_INJ;

    tmp &= ~SIM_E2E_INJ_CH_EN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << SIM_E2E_INJ_CH_EN_SHIFT)) & SIM_E2E_INJ_CH_EN_MASK);
    obj->E2E_INJ = tmp;
}

/*! \brief Gets the E2E channel status
 *
 * This function gets the current E2E channel status.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return E2E channel status
 *         - 0b : normal
 *         - 1b : interrupt
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetE2eStCh15(const SimRegType *obj)
{
    return ((obj->E2E_ST & SIM_E2E_ST_CH15_MASK) >> SIM_E2E_ST_CH15_SHIFT);
}

/*! \brief Sets the E2E channel status
 *
 * This function sets the E2E channel status.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of E2E channel status
 *                    - 0b : normal
 *                    - 1b : interrupt
 */
__attribute__((always_inline)) static inline void SimReg_SetE2eStCh15(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << SIM_E2E_ST_CH15_SHIFT)) & SIM_E2E_ST_CH15_MASK);
    obj->E2E_ST  = tmp;
}

/*! \brief Gets the E2E channel status
 *
 * This function gets the current E2E channel status.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return E2E channel status
 *         - 0b : normal
 *         - 1b : interrupt
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetE2eStCh14(const SimRegType *obj)
{
    return ((obj->E2E_ST & SIM_E2E_ST_CH14_MASK) >> SIM_E2E_ST_CH14_SHIFT);
}

/*! \brief Sets the E2E channel status
 *
 * This function sets the E2E channel status.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of E2E channel status
 *                    - 0b : normal
 *                    - 1b : interrupt
 */
__attribute__((always_inline)) static inline void SimReg_SetE2eStCh14(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << SIM_E2E_ST_CH14_SHIFT)) & SIM_E2E_ST_CH14_MASK);
    obj->E2E_ST  = tmp;
}

/*! \brief Gets the E2E channel status
 *
 * This function gets the current E2E channel status.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return E2E channel status
 *         - 0b : normal
 *         - 1b : interrupt
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetE2eStCh13(const SimRegType *obj)
{
    return ((obj->E2E_ST & SIM_E2E_ST_CH13_MASK) >> SIM_E2E_ST_CH13_SHIFT);
}

/*! \brief Sets the E2E channel status
 *
 * This function sets the E2E channel status.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of E2E channel status
 *                    - 0b : normal
 *                    - 1b : interrupt
 */
__attribute__((always_inline)) static inline void SimReg_SetE2eStCh13(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << SIM_E2E_ST_CH13_SHIFT)) & SIM_E2E_ST_CH13_MASK);
    obj->E2E_ST  = tmp;
}

/*! \brief Gets the E2E channel status
 *
 * This function gets the current E2E channel status.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return E2E channel status
 *         - 0b : normal
 *         - 1b : interrupt
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetE2eStCh12(const SimRegType *obj)
{
    return ((obj->E2E_ST & SIM_E2E_ST_CH12_MASK) >> SIM_E2E_ST_CH12_SHIFT);
}

/*! \brief Sets the E2E channel status
 *
 * This function sets the E2E channel status.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of E2E channel status
 *                    - 0b : normal
 *                    - 1b : interrupt
 */
__attribute__((always_inline)) static inline void SimReg_SetE2eStCh12(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << SIM_E2E_ST_CH12_SHIFT)) & SIM_E2E_ST_CH12_MASK);
    obj->E2E_ST  = tmp;
}

/*! \brief Gets the E2E channel status
 *
 * This function gets the current E2E channel status.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return E2E channel status
 *         - 0b : normal
 *         - 1b : interrupt
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetE2eStCh11(const SimRegType *obj)
{
    return ((obj->E2E_ST & SIM_E2E_ST_CH11_MASK) >> SIM_E2E_ST_CH11_SHIFT);
}

/*! \brief Sets the E2E channel status
 *
 * This function sets the E2E channel status.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of E2E channel status
 *                    - 0b : normal
 *                    - 1b : interrupt
 */
__attribute__((always_inline)) static inline void SimReg_SetE2eStCh11(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << SIM_E2E_ST_CH11_SHIFT)) & SIM_E2E_ST_CH11_MASK);
    obj->E2E_ST  = tmp;
}

/*! \brief Gets the E2E channel status
 *
 * This function gets the current E2E channel status.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return E2E channel status
 *         - 0b : normal
 *         - 1b : interrupt
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetE2eStCh10(const SimRegType *obj)
{
    return ((obj->E2E_ST & SIM_E2E_ST_CH10_MASK) >> SIM_E2E_ST_CH10_SHIFT);
}

/*! \brief Sets the E2E channel status
 *
 * This function sets the E2E channel status.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of E2E channel status
 *                    - 0b : normal
 *                    - 1b : interrupt
 */
__attribute__((always_inline)) static inline void SimReg_SetE2eStCh10(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << SIM_E2E_ST_CH10_SHIFT)) & SIM_E2E_ST_CH10_MASK);
    obj->E2E_ST  = tmp;
}

/*! \brief Gets the E2E channel status
 *
 * This function gets the current E2E channel status.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return E2E channel status
 *         - 0b : normal
 *         - 1b : interrupt
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetE2eStCh9(const SimRegType *obj)
{
    return ((obj->E2E_ST & SIM_E2E_ST_CH9_MASK) >> SIM_E2E_ST_CH9_SHIFT);
}

/*! \brief Sets the E2E channel status
 *
 * This function sets the E2E channel status.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of E2E channel status
 *                    - 0b : normal
 *                    - 1b : interrupt
 */
__attribute__((always_inline)) static inline void SimReg_SetE2eStCh9(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << SIM_E2E_ST_CH9_SHIFT)) & SIM_E2E_ST_CH9_MASK);
    obj->E2E_ST  = tmp;
}

/*! \brief Gets the E2E channel status
 *
 * This function gets the current E2E channel status.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return E2E channel status
 *         - 0b : normal
 *         - 1b : interrupt
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetE2eStCh8(const SimRegType *obj)
{
    return ((obj->E2E_ST & SIM_E2E_ST_CH8_MASK) >> SIM_E2E_ST_CH8_SHIFT);
}

/*! \brief Sets the E2E channel status
 *
 * This function sets the E2E channel status.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of E2E channel status
 *                    - 0b : normal
 *                    - 1b : interrupt
 */
__attribute__((always_inline)) static inline void SimReg_SetE2eStCh8(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << SIM_E2E_ST_CH8_SHIFT)) & SIM_E2E_ST_CH8_MASK);
    obj->E2E_ST  = tmp;
}

/*! \brief Gets the E2E channel status
 *
 * This function gets the current E2E channel status.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return E2E channel status
 *         - 0b : normal
 *         - 1b : interrupt
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetE2eStCh7(const SimRegType *obj)
{
    return ((obj->E2E_ST & SIM_E2E_ST_CH7_MASK) >> SIM_E2E_ST_CH7_SHIFT);
}

/*! \brief Sets the E2E channel status
 *
 * This function sets the E2E channel status.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of E2E channel status
 *                    - 0b : normal
 *                    - 1b : interrupt
 */
__attribute__((always_inline)) static inline void SimReg_SetE2eStCh7(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << SIM_E2E_ST_CH7_SHIFT)) & SIM_E2E_ST_CH7_MASK);
    obj->E2E_ST  = tmp;
}

/*! \brief Gets the E2E channel status
 *
 * This function gets the current E2E channel status.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return E2E channel status
 *         - 0b : normal
 *         - 1b : interrupt
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetE2eStCh6(const SimRegType *obj)
{
    return ((obj->E2E_ST & SIM_E2E_ST_CH6_MASK) >> SIM_E2E_ST_CH6_SHIFT);
}

/*! \brief Sets the E2E channel status
 *
 * This function sets the E2E channel status.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of E2E channel status
 *                    - 0b : normal
 *                    - 1b : interrupt
 */
__attribute__((always_inline)) static inline void SimReg_SetE2eStCh6(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << SIM_E2E_ST_CH6_SHIFT)) & SIM_E2E_ST_CH6_MASK);
    obj->E2E_ST  = tmp;
}

/*! \brief Gets the E2E channel status
 *
 * This function gets the current E2E channel status.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return E2E channel status
 *         - 0b : normal
 *         - 1b : interrupt
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetE2eStCh5(const SimRegType *obj)
{
    return ((obj->E2E_ST & SIM_E2E_ST_CH5_MASK) >> SIM_E2E_ST_CH5_SHIFT);
}

/*! \brief Sets the E2E channel status
 *
 * This function sets the E2E channel status.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of E2E channel status
 *                    - 0b : normal
 *                    - 1b : interrupt
 */
__attribute__((always_inline)) static inline void SimReg_SetE2eStCh5(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << SIM_E2E_ST_CH5_SHIFT)) & SIM_E2E_ST_CH5_MASK);
    obj->E2E_ST  = tmp;
}

/*! \brief Gets the E2E channel status
 *
 * This function gets the current E2E channel status.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return E2E channel status
 *         - 0b : normal
 *         - 1b : interrupt
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetE2eStCh4(const SimRegType *obj)
{
    return ((obj->E2E_ST & SIM_E2E_ST_CH4_MASK) >> SIM_E2E_ST_CH4_SHIFT);
}

/*! \brief Sets the E2E channel status
 *
 * This function sets the E2E channel status.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of E2E channel status
 *                    - 0b : normal
 *                    - 1b : interrupt
 */
__attribute__((always_inline)) static inline void SimReg_SetE2eStCh4(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << SIM_E2E_ST_CH4_SHIFT)) & SIM_E2E_ST_CH4_MASK);
    obj->E2E_ST  = tmp;
}

/*! \brief Gets the E2E channel status
 *
 * This function gets the current E2E channel status.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return E2E channel status
 *         - 0b : normal
 *         - 1b : interrupt
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetE2eStCh3(const SimRegType *obj)
{
    return ((obj->E2E_ST & SIM_E2E_ST_CH3_MASK) >> SIM_E2E_ST_CH3_SHIFT);
}

/*! \brief Sets the E2E channel status
 *
 * This function sets the E2E channel status.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of E2E channel status
 *                    - 0b : normal
 *                    - 1b : interrupt
 */
__attribute__((always_inline)) static inline void SimReg_SetE2eStCh3(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << SIM_E2E_ST_CH3_SHIFT)) & SIM_E2E_ST_CH3_MASK);
    obj->E2E_ST  = tmp;
}

/*! \brief Gets the E2E channel status
 *
 * This function gets the current E2E channel status.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return E2E channel status
 *         - 0b : normal
 *         - 1b : interrupt
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetE2eStCh2(const SimRegType *obj)
{
    return ((obj->E2E_ST & SIM_E2E_ST_CH2_MASK) >> SIM_E2E_ST_CH2_SHIFT);
}

/*! \brief Sets the E2E channel status
 *
 * This function sets the E2E channel status.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of E2E channel status
 *                    - 0b : normal
 *                    - 1b : interrupt
 */
__attribute__((always_inline)) static inline void SimReg_SetE2eStCh2(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << SIM_E2E_ST_CH2_SHIFT)) & SIM_E2E_ST_CH2_MASK);
    obj->E2E_ST  = tmp;
}

/*! \brief Gets the E2E channel status
 *
 * This function gets the current E2E channel status.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return E2E channel status
 *         - 0b : normal
 *         - 1b : interrupt
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetE2eStCh1(const SimRegType *obj)
{
    return ((obj->E2E_ST & SIM_E2E_ST_CH1_MASK) >> SIM_E2E_ST_CH1_SHIFT);
}

/*! \brief Sets the E2E channel status
 *
 * This function sets the E2E channel status.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of E2E channel status
 *                    - 0b : normal
 *                    - 1b : interrupt
 */
__attribute__((always_inline)) static inline void SimReg_SetE2eStCh1(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << SIM_E2E_ST_CH1_SHIFT)) & SIM_E2E_ST_CH1_MASK);
    obj->E2E_ST  = tmp;
}

/*! \brief Gets the E2E channel status
 *
 * This function gets the current E2E channel status.
 *
 * \param[in] obj : pointer to SIM register instance
 * \return E2E channel status
 *         - 0b : normal
 *         - 1b : interrupt
 */
__attribute__((always_inline)) static inline uint8_t SimReg_GetE2eStCh0(const SimRegType *obj)
{
    return ((obj->E2E_ST & SIM_E2E_ST_CH0_MASK) >> SIM_E2E_ST_CH0_SHIFT);
}

/*! \brief Sets the E2E channel status
 *
 * This function sets the E2E channel status.
 *
 * \param[in] obj : pointer to SIM register instance
 * \param[in] value : the value of E2E channel status
 *                    - 0b : normal
 *                    - 1b : interrupt
 */
__attribute__((always_inline)) static inline void SimReg_SetE2eStCh0(SimRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << SIM_E2E_ST_CH0_SHIFT)) & SIM_E2E_ST_CH0_MASK);
    obj->E2E_ST  = tmp;
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _SIM_REG_H_ */
