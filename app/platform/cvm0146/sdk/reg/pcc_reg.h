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

#ifndef _PCC_REG_H_
#define _PCC_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the PCC Registers
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

/* CK_CTL0 Bit Fields */
#define PCC_CK_CTL0_SRC_SPI3_MASK      (0xC000000u)
#define PCC_CK_CTL0_SRC_SPI3_SHIFT     (26u)
#define PCC_CK_CTL0_SRC_SPI3_WIDTH     (2u)
#define PCC_CK_CTL0_SRC_SPI2_MASK      (0x3000000u)
#define PCC_CK_CTL0_SRC_SPI2_SHIFT     (24u)
#define PCC_CK_CTL0_SRC_SPI2_WIDTH     (2u)
#define PCC_CK_CTL0_SRC_SPI1_MASK      (0xC00000u)
#define PCC_CK_CTL0_SRC_SPI1_SHIFT     (22u)
#define PCC_CK_CTL0_SRC_SPI1_WIDTH     (2u)
#define PCC_CK_CTL0_SRC_SPI0_MASK      (0x300000u)
#define PCC_CK_CTL0_SRC_SPI0_SHIFT     (20u)
#define PCC_CK_CTL0_SRC_SPI0_WIDTH     (2u)
#define PCC_CK_CTL0_SRC_UART3_MASK     (0xC000u)
#define PCC_CK_CTL0_SRC_UART3_SHIFT    (14u)
#define PCC_CK_CTL0_SRC_UART3_WIDTH    (2u)
#define PCC_CK_CTL0_SRC_UART2_MASK     (0x3000u)
#define PCC_CK_CTL0_SRC_UART2_SHIFT    (12u)
#define PCC_CK_CTL0_SRC_UART2_WIDTH    (2u)
#define PCC_CK_CTL0_SRC_UART1_MASK     (0xC00u)
#define PCC_CK_CTL0_SRC_UART1_SHIFT    (10u)
#define PCC_CK_CTL0_SRC_UART1_WIDTH    (2u)
#define PCC_CK_CTL0_SRC_UART0_MASK     (0x300u)
#define PCC_CK_CTL0_SRC_UART0_SHIFT    (8u)
#define PCC_CK_CTL0_SRC_UART0_WIDTH    (2u)
#define PCC_CK_CTL0_SRC_EWM_MASK       (0xC0u)
#define PCC_CK_CTL0_SRC_EWM_SHIFT      (6u)
#define PCC_CK_CTL0_SRC_EWM_WIDTH      (2u)
#define PCC_CK_CTL0_SRC_I2SM_MASK      (0x30u)
#define PCC_CK_CTL0_SRC_I2SM_SHIFT     (4u)
#define PCC_CK_CTL0_SRC_I2SM_WIDTH     (2u)
#define PCC_CK_CTL0_SRC_I2C_MASK       (0x03u)
#define PCC_CK_CTL0_SRC_I2C_SHIFT      (0u)
#define PCC_CK_CTL0_SRC_I2C_WIDTH      (2u)

/* CK_CTL1 Bit Fields */
#define PCC_CK_CTL1_DIV_I2SM_MASK      (0x3Fu)
#define PCC_CK_CTL1_DIV_I2SM_SHIFT     (0u)
#define PCC_CK_CTL1_DIV_I2SM_WIDTH     (6u)

/* CK_CTL2 Bit Fields */
#define PCC_CK_CTL2_DIV_ADC1_MASK      (0x7000u)
#define PCC_CK_CTL2_DIV_ADC1_SHIFT     (12u)
#define PCC_CK_CTL2_DIV_ADC1_WIDTH     (3u)
#define PCC_CK_CTL2_DIV_ADC0_MASK      (0x700u)
#define PCC_CK_CTL2_DIV_ADC0_SHIFT     (8u)
#define PCC_CK_CTL2_DIV_ADC0_WIDTH     (3u)
#define PCC_CK_CTL2_SRC_ADC1_MASK      (0x18u)
#define PCC_CK_CTL2_SRC_ADC1_SHIFT     (3u)
#define PCC_CK_CTL2_SRC_ADC1_WIDTH     (2u)
#define PCC_CK_CTL2_SRC_ADC0_MASK      (0x03u)
#define PCC_CK_CTL2_SRC_ADC0_SHIFT     (0u)
#define PCC_CK_CTL2_SRC_ADC0_WIDTH     (2u)

/* CK_CTL3 Bit Fields */
#define PCC_CK_CTL3_SRC_EXT_MFT5_MASK  (0x700000u)
#define PCC_CK_CTL3_SRC_EXT_MFT5_SHIFT (20u)
#define PCC_CK_CTL3_SRC_EXT_MFT5_WIDTH (3u)
#define PCC_CK_CTL3_SRC_EXT_MFT4_MASK  (0x70000u)
#define PCC_CK_CTL3_SRC_EXT_MFT4_SHIFT (16u)
#define PCC_CK_CTL3_SRC_EXT_MFT4_WIDTH (3u)
#define PCC_CK_CTL3_SRC_EXT_MFT3_MASK  (0x7000u)
#define PCC_CK_CTL3_SRC_EXT_MFT3_SHIFT (12u)
#define PCC_CK_CTL3_SRC_EXT_MFT3_WIDTH (3u)
#define PCC_CK_CTL3_SRC_EXT_MFT2_MASK  (0x700u)
#define PCC_CK_CTL3_SRC_EXT_MFT2_SHIFT (8u)
#define PCC_CK_CTL3_SRC_EXT_MFT2_WIDTH (3u)
#define PCC_CK_CTL3_SRC_EXT_MFT1_MASK  (0x70u)
#define PCC_CK_CTL3_SRC_EXT_MFT1_SHIFT (4u)
#define PCC_CK_CTL3_SRC_EXT_MFT1_WIDTH (3u)
#define PCC_CK_CTL3_SRC_EXT_MFT0_MASK  (0x07u)
#define PCC_CK_CTL3_SRC_EXT_MFT0_SHIFT (0u)
#define PCC_CK_CTL3_SRC_EXT_MFT0_WIDTH (3u)

/* CK_EN0 Bit Fields */
#define PCC_CK_EN0_PRNG_MASK           (0x40000000u)
#define PCC_CK_EN0_PRNG_SHIFT          (30u)
#define PCC_CK_EN0_PRNG_WIDTH          (1u)
#define PCC_CK_EN0_CSE_MASK            (0x20000000u)
#define PCC_CK_EN0_CSE_SHIFT           (29u)
#define PCC_CK_EN0_CSE_WIDTH           (1u)
#define PCC_CK_EN0_CRC_MASK            (0x10000000u)
#define PCC_CK_EN0_CRC_SHIFT           (28u)
#define PCC_CK_EN0_CRC_WIDTH           (1u)
#define PCC_CK_EN0_I2SS_MASK           (0x8000000u)
#define PCC_CK_EN0_I2SS_SHIFT          (27u)
#define PCC_CK_EN0_I2SS_WIDTH          (1u)
#define PCC_CK_EN0_I2SM_MASK           (0x4000000u)
#define PCC_CK_EN0_I2SM_SHIFT          (26u)
#define PCC_CK_EN0_I2SM_WIDTH          (1u)
#define PCC_CK_EN0_I2C_MASK            (0x2000000u)
#define PCC_CK_EN0_I2C_SHIFT           (25u)
#define PCC_CK_EN0_I2C_WIDTH           (1u)
#define PCC_CK_EN0_UART3_MASK          (0x1000000u)
#define PCC_CK_EN0_UART3_SHIFT         (24u)
#define PCC_CK_EN0_UART3_WIDTH         (1u)
#define PCC_CK_EN0_UART2_MASK          (0x800000u)
#define PCC_CK_EN0_UART2_SHIFT         (23u)
#define PCC_CK_EN0_UART2_WIDTH         (1u)
#define PCC_CK_EN0_UART1_MASK          (0x400000u)
#define PCC_CK_EN0_UART1_SHIFT         (22u)
#define PCC_CK_EN0_UART1_WIDTH         (1u)
#define PCC_CK_EN0_UART0_MASK          (0x200000u)
#define PCC_CK_EN0_UART0_SHIFT         (21u)
#define PCC_CK_EN0_UART0_WIDTH         (1u)
#define PCC_CK_EN0_SPI3_MASK           (0x100000u)
#define PCC_CK_EN0_SPI3_SHIFT          (20u)
#define PCC_CK_EN0_SPI3_WIDTH          (1u)
#define PCC_CK_EN0_SPI2_MASK           (0x80000u)
#define PCC_CK_EN0_SPI2_SHIFT          (19u)
#define PCC_CK_EN0_SPI2_WIDTH          (1u)
#define PCC_CK_EN0_SPI1_MASK           (0x40000u)
#define PCC_CK_EN0_SPI1_SHIFT          (18u)
#define PCC_CK_EN0_SPI1_WIDTH          (1u)
#define PCC_CK_EN0_SPI0_MASK           (0x20000u)
#define PCC_CK_EN0_SPI0_SHIFT          (17u)
#define PCC_CK_EN0_SPI0_WIDTH          (1u)
#define PCC_CK_EN0_PDB1_MASK           (0x10000u)
#define PCC_CK_EN0_PDB1_SHIFT          (16u)
#define PCC_CK_EN0_PDB1_WIDTH          (1u)
#define PCC_CK_EN0_PDB0_MASK           (0x8000u)
#define PCC_CK_EN0_PDB0_SHIFT          (15u)
#define PCC_CK_EN0_PDB0_WIDTH          (1u)
#define PCC_CK_EN0_ADC1_MASK           (0x4000u)
#define PCC_CK_EN0_ADC1_SHIFT          (14u)
#define PCC_CK_EN0_ADC1_WIDTH          (1u)
#define PCC_CK_EN0_ADC0_MASK           (0x2000u)
#define PCC_CK_EN0_ADC0_SHIFT          (13u)
#define PCC_CK_EN0_ADC0_WIDTH          (1u)
#define PCC_CK_EN0_CAN3_MASK           (0x1000u)
#define PCC_CK_EN0_CAN3_SHIFT          (12u)
#define PCC_CK_EN0_CAN3_WIDTH          (1u)
#define PCC_CK_EN0_CAN2_MASK           (0x800u)
#define PCC_CK_EN0_CAN2_SHIFT          (11u)
#define PCC_CK_EN0_CAN2_WIDTH          (1u)
#define PCC_CK_EN0_CAN1_MASK           (0x400u)
#define PCC_CK_EN0_CAN1_SHIFT          (10u)
#define PCC_CK_EN0_CAN1_WIDTH          (1u)
#define PCC_CK_EN0_CAN0_MASK           (0x200u)
#define PCC_CK_EN0_CAN0_SHIFT          (9u)
#define PCC_CK_EN0_CAN0_WIDTH          (1u)
#define PCC_CK_EN0_DMAMUX_MASK         (0x100u)
#define PCC_CK_EN0_DMAMUX_SHIFT        (8u)
#define PCC_CK_EN0_DMAMUX_WIDTH        (1u)
#define PCC_CK_EN0_EWM_MASK            (0x40u)
#define PCC_CK_EN0_EWM_SHIFT           (6u)
#define PCC_CK_EN0_EWM_WIDTH           (1u)
#define PCC_CK_EN0_MPU_MASK            (0x20u)
#define PCC_CK_EN0_MPU_SHIFT           (5u)
#define PCC_CK_EN0_MPU_WIDTH           (1u)
#define PCC_CK_EN0_MSCM_MASK           (0x10u)
#define PCC_CK_EN0_MSCM_SHIFT          (4u)
#define PCC_CK_EN0_MSCM_WIDTH          (1u)
#define PCC_CK_EN0_ERM_MASK            (0x08u)
#define PCC_CK_EN0_ERM_SHIFT           (3u)
#define PCC_CK_EN0_ERM_WIDTH           (1u)
#define PCC_CK_EN0_EIM_MASK            (0x04u)
#define PCC_CK_EN0_EIM_SHIFT           (2u)
#define PCC_CK_EN0_EIM_WIDTH           (1u)
#define PCC_CK_EN0_DMA_MASK            (0x02u)
#define PCC_CK_EN0_DMA_SHIFT           (1u)
#define PCC_CK_EN0_DMA_WIDTH           (1u)
#define PCC_CK_EN0_FLS_MASK            (0x01u)
#define PCC_CK_EN0_FLS_SHIFT           (0u)
#define PCC_CK_EN0_FLS_WIDTH           (1u)

/* CK_EN1 Bit Fields */
#define PCC_CK_EN1_CFG_CAN3_MASK       (0x80000000u)
#define PCC_CK_EN1_CFG_CAN3_SHIFT      (31u)
#define PCC_CK_EN1_CFG_CAN3_WIDTH      (1u)
#define PCC_CK_EN1_CFG_CAN2_MASK       (0x40000000u)
#define PCC_CK_EN1_CFG_CAN2_SHIFT      (30u)
#define PCC_CK_EN1_CFG_CAN2_WIDTH      (1u)
#define PCC_CK_EN1_CFG_CAN1_MASK       (0x20000000u)
#define PCC_CK_EN1_CFG_CAN1_SHIFT      (29u)
#define PCC_CK_EN1_CFG_CAN1_WIDTH      (1u)
#define PCC_CK_EN1_CFG_CAN0_MASK       (0x10000000u)
#define PCC_CK_EN1_CFG_CAN0_SHIFT      (28u)
#define PCC_CK_EN1_CFG_CAN0_WIDTH      (1u)
#define PCC_CK_EN1_FCCU_MASK           (0x8000000u)
#define PCC_CK_EN1_FCCU_SHIFT          (27u)
#define PCC_CK_EN1_FCCU_WIDTH          (1u)
#define PCC_CK_EN1_CMUS_MASK           (0x4000000u)
#define PCC_CK_EN1_CMUS_SHIFT          (26u)
#define PCC_CK_EN1_CMUS_WIDTH          (1u)
#define PCC_CK_EN1_CMUP_MASK           (0x2000000u)
#define PCC_CK_EN1_CMUP_SHIFT          (25u)
#define PCC_CK_EN1_CMUP_WIDTH          (1u)
#define PCC_CK_EN1_CMUF_MASK           (0x1000000u)
#define PCC_CK_EN1_CMUF_SHIFT          (24u)
#define PCC_CK_EN1_CMUF_WIDTH          (1u)
#define PCC_CK_EN1_PWM4_MASK           (0x4000u)
#define PCC_CK_EN1_PWM4_SHIFT          (14u)
#define PCC_CK_EN1_PWM4_WIDTH          (1u)
#define PCC_CK_EN1_PWM3_MASK           (0x2000u)
#define PCC_CK_EN1_PWM3_SHIFT          (13u)
#define PCC_CK_EN1_PWM3_WIDTH          (1u)
#define PCC_CK_EN1_PWM2_MASK           (0x1000u)
#define PCC_CK_EN1_PWM2_SHIFT          (12u)
#define PCC_CK_EN1_PWM2_WIDTH          (1u)
#define PCC_CK_EN1_PWM1_MASK           (0x800u)
#define PCC_CK_EN1_PWM1_SHIFT          (11u)
#define PCC_CK_EN1_PWM1_WIDTH          (1u)
#define PCC_CK_EN1_PWM0_MASK           (0x400u)
#define PCC_CK_EN1_PWM0_SHIFT          (10u)
#define PCC_CK_EN1_PWM0_WIDTH          (1u)
#define PCC_CK_EN1_MFT5_MASK           (0x80u)
#define PCC_CK_EN1_MFT5_SHIFT          (7u)
#define PCC_CK_EN1_MFT5_WIDTH          (1u)
#define PCC_CK_EN1_MFT4_MASK           (0x40u)
#define PCC_CK_EN1_MFT4_SHIFT          (6u)
#define PCC_CK_EN1_MFT4_WIDTH          (1u)
#define PCC_CK_EN1_MFT3_MASK           (0x20u)
#define PCC_CK_EN1_MFT3_SHIFT          (5u)
#define PCC_CK_EN1_MFT3_WIDTH          (1u)
#define PCC_CK_EN1_MFT2_MASK           (0x10u)
#define PCC_CK_EN1_MFT2_SHIFT          (4u)
#define PCC_CK_EN1_MFT2_WIDTH          (1u)
#define PCC_CK_EN1_MFT1_MASK           (0x08u)
#define PCC_CK_EN1_MFT1_SHIFT          (3u)
#define PCC_CK_EN1_MFT1_WIDTH          (1u)
#define PCC_CK_EN1_MFT0_MASK           (0x04u)
#define PCC_CK_EN1_MFT0_SHIFT          (2u)
#define PCC_CK_EN1_MFT0_WIDTH          (1u)

/* SW_RST0 Bit Fields */
#define PCC_SW_RST0_PRNG_MASK          (0x40000000u)
#define PCC_SW_RST0_PRNG_SHIFT         (30u)
#define PCC_SW_RST0_PRNG_WIDTH         (1u)
#define PCC_SW_RST0_CSE_MASK           (0x20000000u)
#define PCC_SW_RST0_CSE_SHIFT          (29u)
#define PCC_SW_RST0_CSE_WIDTH          (1u)
#define PCC_SW_RST0_CRC_MASK           (0x10000000u)
#define PCC_SW_RST0_CRC_SHIFT          (28u)
#define PCC_SW_RST0_CRC_WIDTH          (1u)
#define PCC_SW_RST0_I2SS_MASK          (0x8000000u)
#define PCC_SW_RST0_I2SS_SHIFT         (27u)
#define PCC_SW_RST0_I2SS_WIDTH         (1u)
#define PCC_SW_RST0_I2SM_MASK          (0x4000000u)
#define PCC_SW_RST0_I2SM_SHIFT         (26u)
#define PCC_SW_RST0_I2SM_WIDTH         (1u)
#define PCC_SW_RST0_I2C_MASK           (0x2000000u)
#define PCC_SW_RST0_I2C_SHIFT          (25u)
#define PCC_SW_RST0_I2C_WIDTH          (1u)
#define PCC_SW_RST0_UART3_MASK         (0x1000000u)
#define PCC_SW_RST0_UART3_SHIFT        (24u)
#define PCC_SW_RST0_UART3_WIDTH        (1u)
#define PCC_SW_RST0_UART2_MASK         (0x800000u)
#define PCC_SW_RST0_UART2_SHIFT        (23u)
#define PCC_SW_RST0_UART2_WIDTH        (1u)
#define PCC_SW_RST0_UART1_MASK         (0x400000u)
#define PCC_SW_RST0_UART1_SHIFT        (22u)
#define PCC_SW_RST0_UART1_WIDTH        (1u)
#define PCC_SW_RST0_UART0_MASK         (0x200000u)
#define PCC_SW_RST0_UART0_SHIFT        (21u)
#define PCC_SW_RST0_UART0_WIDTH        (1u)
#define PCC_SW_RST0_SPI3_MASK          (0x100000u)
#define PCC_SW_RST0_SPI3_SHIFT         (20u)
#define PCC_SW_RST0_SPI3_WIDTH         (1u)
#define PCC_SW_RST0_SPI2_MASK          (0x80000u)
#define PCC_SW_RST0_SPI2_SHIFT         (19u)
#define PCC_SW_RST0_SPI2_WIDTH         (1u)
#define PCC_SW_RST0_SPI1_MASK          (0x40000u)
#define PCC_SW_RST0_SPI1_SHIFT         (18u)
#define PCC_SW_RST0_SPI1_WIDTH         (1u)
#define PCC_SW_RST0_SPI0_MASK          (0x20000u)
#define PCC_SW_RST0_SPI0_SHIFT         (17u)
#define PCC_SW_RST0_SPI0_WIDTH         (1u)
#define PCC_SW_RST0_PDB1_MASK          (0x10000u)
#define PCC_SW_RST0_PDB1_SHIFT         (16u)
#define PCC_SW_RST0_PDB1_WIDTH         (1u)
#define PCC_SW_RST0_PDB0_MASK          (0x8000u)
#define PCC_SW_RST0_PDB0_SHIFT         (15u)
#define PCC_SW_RST0_PDB0_WIDTH         (1u)
#define PCC_SW_RST0_ADC1_MASK          (0x4000u)
#define PCC_SW_RST0_ADC1_SHIFT         (14u)
#define PCC_SW_RST0_ADC1_WIDTH         (1u)
#define PCC_SW_RST0_ADC0_MASK          (0x2000u)
#define PCC_SW_RST0_ADC0_SHIFT         (13u)
#define PCC_SW_RST0_ADC0_WIDTH         (1u)
#define PCC_SW_RST0_CAN3_MASK          (0x1000u)
#define PCC_SW_RST0_CAN3_SHIFT         (12u)
#define PCC_SW_RST0_CAN3_WIDTH         (1u)
#define PCC_SW_RST0_CAN2_MASK          (0x800u)
#define PCC_SW_RST0_CAN2_SHIFT         (11u)
#define PCC_SW_RST0_CAN2_WIDTH         (1u)
#define PCC_SW_RST0_CAN1_MASK          (0x400u)
#define PCC_SW_RST0_CAN1_SHIFT         (10u)
#define PCC_SW_RST0_CAN1_WIDTH         (1u)
#define PCC_SW_RST0_CAN0_MASK          (0x200u)
#define PCC_SW_RST0_CAN0_SHIFT         (9u)
#define PCC_SW_RST0_CAN0_WIDTH         (1u)
#define PCC_SW_RST0_DMAMUX_MASK        (0x100u)
#define PCC_SW_RST0_DMAMUX_SHIFT       (8u)
#define PCC_SW_RST0_DMAMUX_WIDTH       (1u)
#define PCC_SW_RST0_EWM_MASK           (0x40u)
#define PCC_SW_RST0_EWM_SHIFT          (6u)
#define PCC_SW_RST0_EWM_WIDTH          (1u)
#define PCC_SW_RST0_MPU_MASK           (0x20u)
#define PCC_SW_RST0_MPU_SHIFT          (5u)
#define PCC_SW_RST0_MPU_WIDTH          (1u)
#define PCC_SW_RST0_MSCM_MASK          (0x10u)
#define PCC_SW_RST0_MSCM_SHIFT         (4u)
#define PCC_SW_RST0_MSCM_WIDTH         (1u)
#define PCC_SW_RST0_ERM_MASK           (0x08u)
#define PCC_SW_RST0_ERM_SHIFT          (3u)
#define PCC_SW_RST0_ERM_WIDTH          (1u)
#define PCC_SW_RST0_EIM_MASK           (0x04u)
#define PCC_SW_RST0_EIM_SHIFT          (2u)
#define PCC_SW_RST0_EIM_WIDTH          (1u)
#define PCC_SW_RST0_DMA_MASK           (0x02u)
#define PCC_SW_RST0_DMA_SHIFT          (1u)
#define PCC_SW_RST0_DMA_WIDTH          (1u)
#define PCC_SW_RST0_FLS_MASK           (0x01u)
#define PCC_SW_RST0_FLS_SHIFT          (0u)
#define PCC_SW_RST0_FLS_WIDTH          (1u)

/* SW_RST1 Bit Fields */
#define PCC_SW_RST1_FCCU_MASK          (0x8000000u)
#define PCC_SW_RST1_FCCU_SHIFT         (27u)
#define PCC_SW_RST1_FCCU_WIDTH         (1u)
#define PCC_SW_RST1_CMUS_MASK          (0x4000000u)
#define PCC_SW_RST1_CMUS_SHIFT         (26u)
#define PCC_SW_RST1_CMUS_WIDTH         (1u)
#define PCC_SW_RST1_CMUP_MASK          (0x2000000u)
#define PCC_SW_RST1_CMUP_SHIFT         (25u)
#define PCC_SW_RST1_CMUP_WIDTH         (1u)
#define PCC_SW_RST1_CMUF_MASK          (0x1000000u)
#define PCC_SW_RST1_CMUF_SHIFT         (24u)
#define PCC_SW_RST1_CMUF_WIDTH         (1u)
#define PCC_SW_RST1_GPIO_MASK          (0x100000u)
#define PCC_SW_RST1_GPIO_SHIFT         (20u)
#define PCC_SW_RST1_GPIO_WIDTH         (1u)
#define PCC_SW_RST1_PWM4_MASK          (0x4000u)
#define PCC_SW_RST1_PWM4_SHIFT         (14u)
#define PCC_SW_RST1_PWM4_WIDTH         (1u)
#define PCC_SW_RST1_PWM3_MASK          (0x2000u)
#define PCC_SW_RST1_PWM3_SHIFT         (13u)
#define PCC_SW_RST1_PWM3_WIDTH         (1u)
#define PCC_SW_RST1_PWM2_MASK          (0x1000u)
#define PCC_SW_RST1_PWM2_SHIFT         (12u)
#define PCC_SW_RST1_PWM2_WIDTH         (1u)
#define PCC_SW_RST1_PWM1_MASK          (0x800u)
#define PCC_SW_RST1_PWM1_SHIFT         (11u)
#define PCC_SW_RST1_PWM1_WIDTH         (1u)
#define PCC_SW_RST1_PWM0_MASK          (0x400u)
#define PCC_SW_RST1_PWM0_SHIFT         (10u)
#define PCC_SW_RST1_PWM0_WIDTH         (1u)
#define PCC_SW_RST1_MFT5_MASK          (0x80u)
#define PCC_SW_RST1_MFT5_SHIFT         (7u)
#define PCC_SW_RST1_MFT5_WIDTH         (1u)
#define PCC_SW_RST1_MFT4_MASK          (0x40u)
#define PCC_SW_RST1_MFT4_SHIFT         (6u)
#define PCC_SW_RST1_MFT4_WIDTH         (1u)
#define PCC_SW_RST1_MFT3_MASK          (0x20u)
#define PCC_SW_RST1_MFT3_SHIFT         (5u)
#define PCC_SW_RST1_MFT3_WIDTH         (1u)
#define PCC_SW_RST1_MFT2_MASK          (0x10u)
#define PCC_SW_RST1_MFT2_SHIFT         (4u)
#define PCC_SW_RST1_MFT2_WIDTH         (1u)
#define PCC_SW_RST1_MFT1_MASK          (0x08u)
#define PCC_SW_RST1_MFT1_SHIFT         (3u)
#define PCC_SW_RST1_MFT1_WIDTH         (1u)
#define PCC_SW_RST1_MFT0_MASK          (0x04u)
#define PCC_SW_RST1_MFT0_SHIFT         (2u)
#define PCC_SW_RST1_MFT0_WIDTH         (1u)

/* RST_ST0 Bit Fields */
#define PCC_RST_ST0_PRNG_MASK          (0x40000000u)
#define PCC_RST_ST0_PRNG_SHIFT         (30u)
#define PCC_RST_ST0_PRNG_WIDTH         (1u)
#define PCC_RST_ST0_CSE_MASK           (0x20000000u)
#define PCC_RST_ST0_CSE_SHIFT          (29u)
#define PCC_RST_ST0_CSE_WIDTH          (1u)
#define PCC_RST_ST0_CRC_MASK           (0x10000000u)
#define PCC_RST_ST0_CRC_SHIFT          (28u)
#define PCC_RST_ST0_CRC_WIDTH          (1u)
#define PCC_RST_ST0_I2SS_MASK          (0x8000000u)
#define PCC_RST_ST0_I2SS_SHIFT         (27u)
#define PCC_RST_ST0_I2SS_WIDTH         (1u)
#define PCC_RST_ST0_I2SM_MASK          (0x4000000u)
#define PCC_RST_ST0_I2SM_SHIFT         (26u)
#define PCC_RST_ST0_I2SM_WIDTH         (1u)
#define PCC_RST_ST0_I2C_MASK           (0x2000000u)
#define PCC_RST_ST0_I2C_SHIFT          (25u)
#define PCC_RST_ST0_I2C_WIDTH          (1u)
#define PCC_RST_ST0_UART3_MASK         (0x1000000u)
#define PCC_RST_ST0_UART3_SHIFT        (24u)
#define PCC_RST_ST0_UART3_WIDTH        (1u)
#define PCC_RST_ST0_UART2_MASK         (0x800000u)
#define PCC_RST_ST0_UART2_SHIFT        (23u)
#define PCC_RST_ST0_UART2_WIDTH        (1u)
#define PCC_RST_ST0_UART1_MASK         (0x400000u)
#define PCC_RST_ST0_UART1_SHIFT        (22u)
#define PCC_RST_ST0_UART1_WIDTH        (1u)
#define PCC_RST_ST0_UART0_MASK         (0x200000u)
#define PCC_RST_ST0_UART0_SHIFT        (21u)
#define PCC_RST_ST0_UART0_WIDTH        (1u)
#define PCC_RST_ST0_SPI3_MASK          (0x100000u)
#define PCC_RST_ST0_SPI3_SHIFT         (20u)
#define PCC_RST_ST0_SPI3_WIDTH         (1u)
#define PCC_RST_ST0_SPI2_MASK          (0x80000u)
#define PCC_RST_ST0_SPI2_SHIFT         (19u)
#define PCC_RST_ST0_SPI2_WIDTH         (1u)
#define PCC_RST_ST0_SPI1_MASK          (0x40000u)
#define PCC_RST_ST0_SPI1_SHIFT         (18u)
#define PCC_RST_ST0_SPI1_WIDTH         (1u)
#define PCC_RST_ST0_SPI0_MASK          (0x20000u)
#define PCC_RST_ST0_SPI0_SHIFT         (17u)
#define PCC_RST_ST0_SPI0_WIDTH         (1u)
#define PCC_RST_ST0_PDB1_MASK          (0x10000u)
#define PCC_RST_ST0_PDB1_SHIFT         (16u)
#define PCC_RST_ST0_PDB1_WIDTH         (1u)
#define PCC_RST_ST0_PDB0_MASK          (0x8000u)
#define PCC_RST_ST0_PDB0_SHIFT         (15u)
#define PCC_RST_ST0_PDB0_WIDTH         (1u)
#define PCC_RST_ST0_ADC1_MASK          (0x4000u)
#define PCC_RST_ST0_ADC1_SHIFT         (14u)
#define PCC_RST_ST0_ADC1_WIDTH         (1u)
#define PCC_RST_ST0_ADC0_MASK          (0x2000u)
#define PCC_RST_ST0_ADC0_SHIFT         (13u)
#define PCC_RST_ST0_ADC0_WIDTH         (1u)
#define PCC_RST_ST0_CAN3_MASK          (0x1000u)
#define PCC_RST_ST0_CAN3_SHIFT         (12u)
#define PCC_RST_ST0_CAN3_WIDTH         (1u)
#define PCC_RST_ST0_CAN2_MASK          (0x800u)
#define PCC_RST_ST0_CAN2_SHIFT         (11u)
#define PCC_RST_ST0_CAN2_WIDTH         (1u)
#define PCC_RST_ST0_CAN1_MASK          (0x400u)
#define PCC_RST_ST0_CAN1_SHIFT         (10u)
#define PCC_RST_ST0_CAN1_WIDTH         (1u)
#define PCC_RST_ST0_CAN0_MASK          (0x200u)
#define PCC_RST_ST0_CAN0_SHIFT         (9u)
#define PCC_RST_ST0_CAN0_WIDTH         (1u)
#define PCC_RST_ST0_DMAMUX_MASK        (0x100u)
#define PCC_RST_ST0_DMAMUX_SHIFT       (8u)
#define PCC_RST_ST0_DMAMUX_WIDTH       (1u)
#define PCC_RST_ST0_EWM_MASK           (0x40u)
#define PCC_RST_ST0_EWM_SHIFT          (6u)
#define PCC_RST_ST0_EWM_WIDTH          (1u)
#define PCC_RST_ST0_MPU_MASK           (0x20u)
#define PCC_RST_ST0_MPU_SHIFT          (5u)
#define PCC_RST_ST0_MPU_WIDTH          (1u)
#define PCC_RST_ST0_MSCM_MASK          (0x10u)
#define PCC_RST_ST0_MSCM_SHIFT         (4u)
#define PCC_RST_ST0_MSCM_WIDTH         (1u)
#define PCC_RST_ST0_ERM_MASK           (0x08u)
#define PCC_RST_ST0_ERM_SHIFT          (3u)
#define PCC_RST_ST0_ERM_WIDTH          (1u)
#define PCC_RST_ST0_EIM_MASK           (0x04u)
#define PCC_RST_ST0_EIM_SHIFT          (2u)
#define PCC_RST_ST0_EIM_WIDTH          (1u)
#define PCC_RST_ST0_DMA_MASK           (0x02u)
#define PCC_RST_ST0_DMA_SHIFT          (1u)
#define PCC_RST_ST0_DMA_WIDTH          (1u)
#define PCC_RST_ST0_FLS_MASK           (0x01u)
#define PCC_RST_ST0_FLS_SHIFT          (0u)
#define PCC_RST_ST0_FLS_WIDTH          (1u)

/* RST_ST1 Bit Fields */
#define PCC_RST_ST1_FCCU_MASK          (0x8000000u)
#define PCC_RST_ST1_FCCU_SHIFT         (27u)
#define PCC_RST_ST1_FCCU_WIDTH         (1u)
#define PCC_RST_ST1_CMUS_MASK          (0x4000000u)
#define PCC_RST_ST1_CMUS_SHIFT         (26u)
#define PCC_RST_ST1_CMUS_WIDTH         (1u)
#define PCC_RST_ST1_CMUP_MASK          (0x2000000u)
#define PCC_RST_ST1_CMUP_SHIFT         (25u)
#define PCC_RST_ST1_CMUP_WIDTH         (1u)
#define PCC_RST_ST1_CMUF_MASK          (0x1000000u)
#define PCC_RST_ST1_CMUF_SHIFT         (24u)
#define PCC_RST_ST1_CMUF_WIDTH         (1u)
#define PCC_RST_ST1_GPIO_MASK          (0x100000u)
#define PCC_RST_ST1_GPIO_SHIFT         (20u)
#define PCC_RST_ST1_GPIO_WIDTH         (1u)
#define PCC_RST_ST1_PWM4_MASK          (0x4000u)
#define PCC_RST_ST1_PWM4_SHIFT         (14u)
#define PCC_RST_ST1_PWM4_WIDTH         (1u)
#define PCC_RST_ST1_PWM3_MASK          (0x2000u)
#define PCC_RST_ST1_PWM3_SHIFT         (13u)
#define PCC_RST_ST1_PWM3_WIDTH         (1u)
#define PCC_RST_ST1_PWM2_MASK          (0x1000u)
#define PCC_RST_ST1_PWM2_SHIFT         (12u)
#define PCC_RST_ST1_PWM2_WIDTH         (1u)
#define PCC_RST_ST1_PWM1_MASK          (0x800u)
#define PCC_RST_ST1_PWM1_SHIFT         (11u)
#define PCC_RST_ST1_PWM1_WIDTH         (1u)
#define PCC_RST_ST1_PWM0_MASK          (0x400u)
#define PCC_RST_ST1_PWM0_SHIFT         (10u)
#define PCC_RST_ST1_PWM0_WIDTH         (1u)
#define PCC_RST_ST1_MFT5_MASK          (0x80u)
#define PCC_RST_ST1_MFT5_SHIFT         (7u)
#define PCC_RST_ST1_MFT5_WIDTH         (1u)
#define PCC_RST_ST1_MFT4_MASK          (0x40u)
#define PCC_RST_ST1_MFT4_SHIFT         (6u)
#define PCC_RST_ST1_MFT4_WIDTH         (1u)
#define PCC_RST_ST1_MFT3_MASK          (0x20u)
#define PCC_RST_ST1_MFT3_SHIFT         (5u)
#define PCC_RST_ST1_MFT3_WIDTH         (1u)
#define PCC_RST_ST1_MFT2_MASK          (0x10u)
#define PCC_RST_ST1_MFT2_SHIFT         (4u)
#define PCC_RST_ST1_MFT2_WIDTH         (1u)
#define PCC_RST_ST1_MFT1_MASK          (0x08u)
#define PCC_RST_ST1_MFT1_SHIFT         (3u)
#define PCC_RST_ST1_MFT1_WIDTH         (1u)
#define PCC_RST_ST1_MFT0_MASK          (0x04u)
#define PCC_RST_ST1_MFT0_SHIFT         (2u)
#define PCC_RST_ST1_MFT0_WIDTH         (1u)

/* LOCK Bit Fields */
#define PCC_LOCK_KEY_MASK              (0xFFFFFFFFu)
#define PCC_LOCK_KEY_SHIFT             (0u)
#define PCC_LOCK_KEY_WIDTH             (32u)

/* LOCK_ST Bit Fields */
#define PCC_LOCK_ST_LOCK_MASK          (0x01u)
#define PCC_LOCK_ST_LOCK_SHIFT         (0u)
#define PCC_LOCK_ST_LOCK_WIDTH         (1u)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief The definition of PCC registers
 */
typedef struct _PccRegType_
{
    volatile uint32_t       CK_CTL0;      /*!< Peripheral clock source register0, offset: 0x00 */
    volatile uint32_t       CK_CTL1;      /*!< Perpherials clock control register 1, offset: 0x04 */
    volatile uint32_t       CK_CTL2;      /*!< Perpherials clock control register 2, offset: 0x08 */
    volatile uint32_t       CK_CTL3;      /*!< Perpherials clock control register 3, offset: 0x0C */
    volatile uint32_t       CK_EN0;       /*!< Perpherials clock enable register 0, offset: 0x10 */
    volatile uint32_t       CK_EN1;       /*!< Perpherials clock enable register 1, offset: 0x14 */
    uint32_t                RESERVED0[2]; /*!< Reserverd block, offset: 0x18 */
    volatile uint32_t       SW_RST0;      /*!< Perpherials software reset register 0, offset: 0x20 */
    volatile uint32_t       SW_RST1;      /*!< Perpherials software reset register 1, offset: 0x24 */
    const volatile uint32_t RST_ST0;      /*!< Perpherials reset status register 0, offset: 0x28 */
    const volatile uint32_t RST_ST1;      /*!< Perpherials software reset register 1, offset: 0x2C */
    uint32_t                RESERVED1[4]; /*!< Reserverd block, offset: 0x30 */
    volatile uint32_t       LOCK;         /*!< PCC module unlock/lock control, offset: 0x40 */
    const volatile uint32_t LOCK_ST;      /*!< PCC module lock status register, offset: 0x44 */
} PccRegType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Gets the SPI3 module function clock source
 *
 * This function gets the current SPI3 module function clock source.
 * If SPI3 is not available, this bit is reserved.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return SPI3 module function clock source
 *         - 0h : clk_firc_div2
 *         - 1h : clk_sosc_div2
 *         - 2h : clk_pll_div2
 *         - 3h : clk_sirc_div2
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkCtl0SrcSpi3(const PccRegType *obj)
{
    return ((obj->CK_CTL0 & PCC_CK_CTL0_SRC_SPI3_MASK) >> PCC_CK_CTL0_SRC_SPI3_SHIFT);
}

/*! \brief Sets the SPI3 module function clock source
 *
 * This function sets the SPI3 module function clock source.
 * If SPI3 is not available, this bit is reserved.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of SPI3 module function clock source
 *                    - 0h : clk_firc_div2
 *                    - 1h : clk_sosc_div2
 *                    - 2h : clk_pll_div2
 *                    - 3h : clk_sirc_div2
 */
__attribute__((always_inline)) static inline void PccReg_SetCkCtl0SrcSpi3(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_CTL0;

    tmp &= ~PCC_CK_CTL0_SRC_SPI3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_CTL0_SRC_SPI3_SHIFT)) & PCC_CK_CTL0_SRC_SPI3_MASK);
    obj->CK_CTL0 = tmp;
}

/*! \brief Gets the SPI2 module function clock source
 *
 * This function gets the current SPI2 module function clock source.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return SPI2 module function clock source
 *         - 0h : clk_firc_div2
 *         - 1h : clk_sosc_div2
 *         - 2h : clk_pll_div2
 *         - 3h : clk_sirc_div2
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkCtl0SrcSpi2(const PccRegType *obj)
{
    return ((obj->CK_CTL0 & PCC_CK_CTL0_SRC_SPI2_MASK) >> PCC_CK_CTL0_SRC_SPI2_SHIFT);
}

/*! \brief Sets the SPI2 module function clock source
 *
 * This function sets the SPI2 module function clock source.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of SPI2 module function clock source
 *                    - 0h : clk_firc_div2
 *                    - 1h : clk_sosc_div2
 *                    - 2h : clk_pll_div2
 *                    - 3h : clk_sirc_div2
 */
__attribute__((always_inline)) static inline void PccReg_SetCkCtl0SrcSpi2(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_CTL0;

    tmp &= ~PCC_CK_CTL0_SRC_SPI2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_CTL0_SRC_SPI2_SHIFT)) & PCC_CK_CTL0_SRC_SPI2_MASK);
    obj->CK_CTL0 = tmp;
}

/*! \brief Gets the SPI1 module function clock source
 *
 * This function gets the current SPI1 module function clock source.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return SPI1 module function clock source
 *         - 0h : clk_firc_div2
 *         - 1h : clk_sosc_div2
 *         - 2h : clk_pll_div2
 *         - 3h : clk_sirc_div2
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkCtl0SrcSpi1(const PccRegType *obj)
{
    return ((obj->CK_CTL0 & PCC_CK_CTL0_SRC_SPI1_MASK) >> PCC_CK_CTL0_SRC_SPI1_SHIFT);
}

/*! \brief Sets the SPI1 module function clock source
 *
 * This function sets the SPI1 module function clock source.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of SPI1 module function clock source
 *                    - 0h : clk_firc_div2
 *                    - 1h : clk_sosc_div2
 *                    - 2h : clk_pll_div2
 *                    - 3h : clk_sirc_div2
 */
__attribute__((always_inline)) static inline void PccReg_SetCkCtl0SrcSpi1(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_CTL0;

    tmp &= ~PCC_CK_CTL0_SRC_SPI1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_CTL0_SRC_SPI1_SHIFT)) & PCC_CK_CTL0_SRC_SPI1_MASK);
    obj->CK_CTL0 = tmp;
}

/*! \brief Gets the SPI0 module function clock source
 *
 * This function gets the current SPI0 module function clock source.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return SPI0 module function clock source
 *         - 0h : clk_firc_div2
 *         - 1h : clk_sosc_div2
 *         - 2h : clk_pll_div2
 *         - 3h : clk_sirc_div2
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkCtl0SrcSpi0(const PccRegType *obj)
{
    return ((obj->CK_CTL0 & PCC_CK_CTL0_SRC_SPI0_MASK) >> PCC_CK_CTL0_SRC_SPI0_SHIFT);
}

/*! \brief Sets the SPI0 module function clock source
 *
 * This function sets the SPI0 module function clock source.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of SPI0 module function clock source
 *                    - 0h : clk_firc_div2
 *                    - 1h : clk_sosc_div2
 *                    - 2h : clk_pll_div2
 *                    - 3h : clk_sirc_div2
 */
__attribute__((always_inline)) static inline void PccReg_SetCkCtl0SrcSpi0(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_CTL0;

    tmp &= ~PCC_CK_CTL0_SRC_SPI0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_CTL0_SRC_SPI0_SHIFT)) & PCC_CK_CTL0_SRC_SPI0_MASK);
    obj->CK_CTL0 = tmp;
}

/*! \brief Gets the UART3 module function clock source
 *
 * This function gets the current UART3 module function clock source.
 * If UART3 is not available, this bit is reserved.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return UART3 module function clock source
 *         - 0h : clk_firc_div2
 *         - 1h : clk_sosc_div2
 *         - 2h : clk_pll_div2
 *         - 3h : clk_sirc_div2
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkCtl0SrcUart3(const PccRegType *obj)
{
    return ((obj->CK_CTL0 & PCC_CK_CTL0_SRC_UART3_MASK) >> PCC_CK_CTL0_SRC_UART3_SHIFT);
}

/*! \brief Sets the UART3 module function clock source
 *
 * This function sets the UART3 module function clock source.
 * If UART3 is not available, this bit is reserved.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of UART3 module function clock source
 *                    - 0h : clk_firc_div2
 *                    - 1h : clk_sosc_div2
 *                    - 2h : clk_pll_div2
 *                    - 3h : clk_sirc_div2
 */
__attribute__((always_inline)) static inline void PccReg_SetCkCtl0SrcUart3(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_CTL0;

    tmp &= ~PCC_CK_CTL0_SRC_UART3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_CTL0_SRC_UART3_SHIFT)) & PCC_CK_CTL0_SRC_UART3_MASK);
    obj->CK_CTL0 = tmp;
}

/*! \brief Gets the UART2 module function clock source
 *
 * This function gets the current UART2 module function clock source.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return UART2 module function clock source
 *         - 0h : clk_firc_div2
 *         - 1h : clk_sosc_div2
 *         - 2h : clk_pll_div2
 *         - 3h : clk_sirc_div2
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkCtl0SrcUart2(const PccRegType *obj)
{
    return ((obj->CK_CTL0 & PCC_CK_CTL0_SRC_UART2_MASK) >> PCC_CK_CTL0_SRC_UART2_SHIFT);
}

/*! \brief Sets the UART2 module function clock source
 *
 * This function sets the UART2 module function clock source.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of UART2 module function clock source
 *                    - 0h : clk_firc_div2
 *                    - 1h : clk_sosc_div2
 *                    - 2h : clk_pll_div2
 *                    - 3h : clk_sirc_div2
 */
__attribute__((always_inline)) static inline void PccReg_SetCkCtl0SrcUart2(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_CTL0;

    tmp &= ~PCC_CK_CTL0_SRC_UART2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_CTL0_SRC_UART2_SHIFT)) & PCC_CK_CTL0_SRC_UART2_MASK);
    obj->CK_CTL0 = tmp;
}

/*! \brief Gets the UART1 module function clock source
 *
 * This function gets the current UART1 module function clock source.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return UART1 module function clock source
 *         - 0h : clk_firc_div2
 *         - 1h : clk_sosc_div2
 *         - 2h : clk_pll_div2
 *         - 3h : clk_sirc_div2
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkCtl0SrcUart1(const PccRegType *obj)
{
    return ((obj->CK_CTL0 & PCC_CK_CTL0_SRC_UART1_MASK) >> PCC_CK_CTL0_SRC_UART1_SHIFT);
}

/*! \brief Sets the UART1 module function clock source
 *
 * This function sets the UART1 module function clock source.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of UART1 module function clock source
 *                    - 0h : clk_firc_div2
 *                    - 1h : clk_sosc_div2
 *                    - 2h : clk_pll_div2
 *                    - 3h : clk_sirc_div2
 */
__attribute__((always_inline)) static inline void PccReg_SetCkCtl0SrcUart1(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_CTL0;

    tmp &= ~PCC_CK_CTL0_SRC_UART1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_CTL0_SRC_UART1_SHIFT)) & PCC_CK_CTL0_SRC_UART1_MASK);
    obj->CK_CTL0 = tmp;
}

/*! \brief Gets the UART0 module function clock source
 *
 * This function gets the current UART0 module function clock source.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return UART0 module function clock source
 *         - 0h : clk_firc_div2
 *         - 1h : clk_sosc_div2
 *         - 2h : clk_pll_div2
 *         - 3h : clk_sirc_div2
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkCtl0SrcUart0(const PccRegType *obj)
{
    return ((obj->CK_CTL0 & PCC_CK_CTL0_SRC_UART0_MASK) >> PCC_CK_CTL0_SRC_UART0_SHIFT);
}

/*! \brief Sets the UART0 module function clock source
 *
 * This function sets the UART0 module function clock source.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of UART0 module function clock source
 *                    - 0h : clk_firc_div2
 *                    - 1h : clk_sosc_div2
 *                    - 2h : clk_pll_div2
 *                    - 3h : clk_sirc_div2
 */
__attribute__((always_inline)) static inline void PccReg_SetCkCtl0SrcUart0(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_CTL0;

    tmp &= ~PCC_CK_CTL0_SRC_UART0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_CTL0_SRC_UART0_SHIFT)) & PCC_CK_CTL0_SRC_UART0_MASK);
    obj->CK_CTL0 = tmp;
}

/*! \brief Gets the EWM module function clock source
 *
 * This function gets the current EWM module function clock source.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return EWM module function clock source
 *         - 0h : clk_lpo128
 *         - 1h : clk_lpo32
 *         - 2h : clk_lpo1
 *         - 3h : reserved
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkCtl0SrcEwm(const PccRegType *obj)
{
    return ((obj->CK_CTL0 & PCC_CK_CTL0_SRC_EWM_MASK) >> PCC_CK_CTL0_SRC_EWM_SHIFT);
}

/*! \brief Sets the EWM module function clock source
 *
 * This function sets the EWM module function clock source.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of EWM module function clock source
 *                    - 0h : clk_lpo128
 *                    - 1h : clk_lpo32
 *                    - 2h : clk_lpo1
 *                    - 3h : reserved
 */
__attribute__((always_inline)) static inline void PccReg_SetCkCtl0SrcEwm(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_CTL0;

    tmp &= ~PCC_CK_CTL0_SRC_EWM_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_CTL0_SRC_EWM_SHIFT)) & PCC_CK_CTL0_SRC_EWM_MASK);
    obj->CK_CTL0 = tmp;
}

/*! \brief Gets the I2SM module function clock source
 *
 * This function gets the current I2SM module function clock source.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return I2SM module function clock source
 *         - 0h : clk_firc
 *         - 1h : clk_sosc
 *         - 2h : clk_pll
 *         - 3h : clk_sirc
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkCtl0SrcI2SM(const PccRegType *obj)
{
    return ((obj->CK_CTL0 & PCC_CK_CTL0_SRC_I2SM_MASK) >> PCC_CK_CTL0_SRC_I2SM_SHIFT);
}

/*! \brief Sets the I2SM module function clock source
 *
 * This function sets the I2SM module function clock source.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of I2SM module function clock source
 *                    - 0h : clk_firc
 *                    - 1h : clk_sosc
 *                    - 2h : clk_pll
 *                    - 3h : clk_sirc
 */
__attribute__((always_inline)) static inline void PccReg_SetCkCtl0SrcI2SM(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_CTL0;

    tmp &= ~PCC_CK_CTL0_SRC_I2SM_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_CTL0_SRC_I2SM_SHIFT)) & PCC_CK_CTL0_SRC_I2SM_MASK);
    obj->CK_CTL0 = tmp;
}

/*! \brief Gets the I2C module function clock source
 *
 * This function gets the current I2C module function clock source.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return I2C module function clock source
 *         - 0h : clk_firc_div2
 *         - 1h : clk_sosc_div2
 *         - 2h : clk_pll_div2
 *         - 3h : clk_sirc_div2
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkCtl0SrcI2C(const PccRegType *obj)
{
    return ((obj->CK_CTL0 & PCC_CK_CTL0_SRC_I2C_MASK) >> PCC_CK_CTL0_SRC_I2C_SHIFT);
}

/*! \brief Sets the I2C module function clock source
 *
 * This function sets the I2C module function clock source.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of I2C module function clock source
 *                    - 0h : clk_firc_div2
 *                    - 1h : clk_sosc_div2
 *                    - 2h : clk_pll_div2
 *                    - 3h : clk_sirc_div2
 */
__attribute__((always_inline)) static inline void PccReg_SetCkCtl0SrcI2C(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_CTL0;

    tmp &= ~PCC_CK_CTL0_SRC_I2C_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_CTL0_SRC_I2C_SHIFT)) & PCC_CK_CTL0_SRC_I2C_MASK);
    obj->CK_CTL0 = tmp;
}

/*! \brief Gets the I2S MST module clock divide ratio
 *
 * This function gets the current I2S MST module clock divide ratio.
 * 
 * \note The max frequency is 25M.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return I2S MST module clock divide ratio
 *         - 0h : 2
 *         - 1h : 2
 *         - 2h : 3
¡­
 *         - 63h : 64
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkCtl1DivI2SM(const PccRegType *obj)
{
    return ((obj->CK_CTL1 & PCC_CK_CTL1_DIV_I2SM_MASK) >> PCC_CK_CTL1_DIV_I2SM_SHIFT);
}

/*! \brief Sets the I2S MST module clock divide ratio
 *
 * This function sets the I2S MST module clock divide ratio.
 * 
 * \note The max frequency is 25M.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of I2S MST module clock divide ratio
 *                    - 0h : 2
 *                    - 1h : 2
 *                    - 2h : 3
¡­
 *                    - 63h : 64
 */
__attribute__((always_inline)) static inline void PccReg_SetCkCtl1DivI2SM(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_CTL1;

    tmp &= ~PCC_CK_CTL1_DIV_I2SM_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_CTL1_DIV_I2SM_SHIFT)) & PCC_CK_CTL1_DIV_I2SM_MASK);
    obj->CK_CTL1 = tmp;
}

/*! \brief Gets the module function clock divide ration
 *
 * This function gets the current module function clock divide ration.
 * 
 * \note The max frequency is 40M.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return module function clock divide ration
 *         - 0h : 1
 *         - 1h : 2
 *         - 2h : 4
 *         - 3h : 6
 *         - 4h : 8
 *         - 5h : 10
 *         - 6h : 12
 *         - 7h : 14
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkCtl2DivAdc1(const PccRegType *obj)
{
    return ((obj->CK_CTL2 & PCC_CK_CTL2_DIV_ADC1_MASK) >> PCC_CK_CTL2_DIV_ADC1_SHIFT);
}

/*! \brief Sets the module function clock divide ration
 *
 * This function sets the module function clock divide ration.
 * 
 * \note The max frequency is 40M.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of module function clock divide ration
 *                    - 0h : 1
 *                    - 1h : 2
 *                    - 2h : 4
 *                    - 3h : 6
 *                    - 4h : 8
 *                    - 5h : 10
 *                    - 6h : 12
 *                    - 7h : 14
 */
__attribute__((always_inline)) static inline void PccReg_SetCkCtl2DivAdc1(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_CTL2;

    tmp &= ~PCC_CK_CTL2_DIV_ADC1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_CTL2_DIV_ADC1_SHIFT)) & PCC_CK_CTL2_DIV_ADC1_MASK);
    obj->CK_CTL2 = tmp;
}

/*! \brief Gets the module function clock divide ration
 *
 * This function gets the current module function clock divide ration.
 * 
 * \note The max frequency is 40M.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return module function clock divide ration
 *         - 0h : 1
 *         - 1h : 2
 *         - 2h : 4
 *         - 3h : 6
 *         - 4h : 8
 *         - 5h : 10
 *         - 6h : 12
 *         - 7h : 14
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkCtl2DivAdc0(const PccRegType *obj)
{
    return ((obj->CK_CTL2 & PCC_CK_CTL2_DIV_ADC0_MASK) >> PCC_CK_CTL2_DIV_ADC0_SHIFT);
}

/*! \brief Sets the module function clock divide ration
 *
 * This function sets the module function clock divide ration.
 * 
 * \note The max frequency is 40M.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of module function clock divide ration
 *                    - 0h : 1
 *                    - 1h : 2
 *                    - 2h : 4
 *                    - 3h : 6
 *                    - 4h : 8
 *                    - 5h : 10
 *                    - 6h : 12
 *                    - 7h : 14
 */
__attribute__((always_inline)) static inline void PccReg_SetCkCtl2DivAdc0(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_CTL2;

    tmp &= ~PCC_CK_CTL2_DIV_ADC0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_CTL2_DIV_ADC0_SHIFT)) & PCC_CK_CTL2_DIV_ADC0_MASK);
    obj->CK_CTL2 = tmp;
}

/*! \brief Gets the ADC1 module function clock source
 *
 * This function gets the current ADC1 module function clock source.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return ADC1 module function clock source
 *         - 0h : clk_firc
 *         - 1h : clk_sosc
 *         - 2h : clk_pll
 *         - 3h : clk_sirc
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkCtl2SrcAdc1(const PccRegType *obj)
{
    return ((obj->CK_CTL2 & PCC_CK_CTL2_SRC_ADC1_MASK) >> PCC_CK_CTL2_SRC_ADC1_SHIFT);
}

/*! \brief Sets the ADC1 module function clock source
 *
 * This function sets the ADC1 module function clock source.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of ADC1 module function clock source
 *                    - 0h : clk_firc
 *                    - 1h : clk_sosc
 *                    - 2h : clk_pll
 *                    - 3h : clk_sirc
 */
__attribute__((always_inline)) static inline void PccReg_SetCkCtl2SrcAdc1(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_CTL2;

    tmp &= ~PCC_CK_CTL2_SRC_ADC1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_CTL2_SRC_ADC1_SHIFT)) & PCC_CK_CTL2_SRC_ADC1_MASK);
    obj->CK_CTL2 = tmp;
}

/*! \brief Gets the ADC0 module function clock source
 *
 * This function gets the current ADC0 module function clock source.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return ADC0 module function clock source
 *         - 0h : clk_firc
 *         - 1h : clk_sosc
 *         - 2h : clk_pll
 *         - 3h : clk_sirc
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkCtl2SrcAdc0(const PccRegType *obj)
{
    return ((obj->CK_CTL2 & PCC_CK_CTL2_SRC_ADC0_MASK) >> PCC_CK_CTL2_SRC_ADC0_SHIFT);
}

/*! \brief Sets the ADC0 module function clock source
 *
 * This function sets the ADC0 module function clock source.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of ADC0 module function clock source
 *                    - 0h : clk_firc
 *                    - 1h : clk_sosc
 *                    - 2h : clk_pll
 *                    - 3h : clk_sirc
 */
__attribute__((always_inline)) static inline void PccReg_SetCkCtl2SrcAdc0(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_CTL2;

    tmp &= ~PCC_CK_CTL2_SRC_ADC0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_CTL2_SRC_ADC0_SHIFT)) & PCC_CK_CTL2_SRC_ADC0_MASK);
    obj->CK_CTL2 = tmp;
}

/*! \brief Gets the MFT5 external clock source
 *
 * This function gets the current MFT5 external clock source.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return MFT5 external clock source
 *         - 0h : TCLK0
 *         - 1h : TCLK1
 *         - 2h : TCLK2
 *         - 3h : clk_firc_div1
 *         - 4h : clk_sosc_div1
 *         - 5h : clk_pll_div1
 *         - 6h : clk_sirc_div1
 *         - 7h : clk_sirc_div1
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkCtl3SrcExtMft5(const PccRegType *obj)
{
    return ((obj->CK_CTL3 & PCC_CK_CTL3_SRC_EXT_MFT5_MASK) >> PCC_CK_CTL3_SRC_EXT_MFT5_SHIFT);
}

/*! \brief Sets the MFT5 external clock source
 *
 * This function sets the MFT5 external clock source.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of MFT5 external clock source
 *                    - 0h : TCLK0
 *                    - 1h : TCLK1
 *                    - 2h : TCLK2
 *                    - 3h : clk_firc_div1
 *                    - 4h : clk_sosc_div1
 *                    - 5h : clk_pll_div1
 *                    - 6h : clk_sirc_div1
 *                    - 7h : clk_sirc_div1
 */
__attribute__((always_inline)) static inline void PccReg_SetCkCtl3SrcExtMft5(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_CTL3;

    tmp &= ~PCC_CK_CTL3_SRC_EXT_MFT5_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_CTL3_SRC_EXT_MFT5_SHIFT)) & PCC_CK_CTL3_SRC_EXT_MFT5_MASK);
    obj->CK_CTL3 = tmp;
}

/*! \brief Gets the MFT4 external clock source
 *
 * This function gets the current MFT4 external clock source.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return MFT4 external clock source
 *         - 0h : TCLK0
 *         - 1h : TCLK1
 *         - 2h : TCLK2
 *         - 3h : clk_firc_div1
 *         - 4h : clk_sosc_div1
 *         - 5h : clk_pll_div1
 *         - 6h : clk_sirc_div1
 *         - 7h : clk_sirc_div1
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkCtl3SrcExtMft4(const PccRegType *obj)
{
    return ((obj->CK_CTL3 & PCC_CK_CTL3_SRC_EXT_MFT4_MASK) >> PCC_CK_CTL3_SRC_EXT_MFT4_SHIFT);
}

/*! \brief Sets the MFT4 external clock source
 *
 * This function sets the MFT4 external clock source.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of MFT4 external clock source
 *                    - 0h : TCLK0
 *                    - 1h : TCLK1
 *                    - 2h : TCLK2
 *                    - 3h : clk_firc_div1
 *                    - 4h : clk_sosc_div1
 *                    - 5h : clk_pll_div1
 *                    - 6h : clk_sirc_div1
 *                    - 7h : clk_sirc_div1
 */
__attribute__((always_inline)) static inline void PccReg_SetCkCtl3SrcExtMft4(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_CTL3;

    tmp &= ~PCC_CK_CTL3_SRC_EXT_MFT4_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_CTL3_SRC_EXT_MFT4_SHIFT)) & PCC_CK_CTL3_SRC_EXT_MFT4_MASK);
    obj->CK_CTL3 = tmp;
}

/*! \brief Gets the MFT3 external clock source
 *
 * This function gets the current MFT3 external clock source.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return MFT3 external clock source
 *         - 0h : TCLK0
 *         - 1h : TCLK1
 *         - 2h : TCLK2
 *         - 3h : clk_firc_div1
 *         - 4h : clk_sosc_div1
 *         - 5h : clk_pll_div1
 *         - 6h : clk_sirc_div1
 *         - 7h : clk_sirc_div1
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkCtl3SrcExtMft3(const PccRegType *obj)
{
    return ((obj->CK_CTL3 & PCC_CK_CTL3_SRC_EXT_MFT3_MASK) >> PCC_CK_CTL3_SRC_EXT_MFT3_SHIFT);
}

/*! \brief Sets the MFT3 external clock source
 *
 * This function sets the MFT3 external clock source.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of MFT3 external clock source
 *                    - 0h : TCLK0
 *                    - 1h : TCLK1
 *                    - 2h : TCLK2
 *                    - 3h : clk_firc_div1
 *                    - 4h : clk_sosc_div1
 *                    - 5h : clk_pll_div1
 *                    - 6h : clk_sirc_div1
 *                    - 7h : clk_sirc_div1
 */
__attribute__((always_inline)) static inline void PccReg_SetCkCtl3SrcExtMft3(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_CTL3;

    tmp &= ~PCC_CK_CTL3_SRC_EXT_MFT3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_CTL3_SRC_EXT_MFT3_SHIFT)) & PCC_CK_CTL3_SRC_EXT_MFT3_MASK);
    obj->CK_CTL3 = tmp;
}

/*! \brief Gets the MFT2 external clock source
 *
 * This function gets the current MFT2 external clock source.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return MFT2 external clock source
 *         - 0h : TCLK0
 *         - 1h : TCLK1
 *         - 2h : TCLK2
 *         - 3h : clk_firc_div1
 *         - 4h : clk_sosc_div1
 *         - 5h : clk_pll_div1
 *         - 6h : clk_sirc_div1
 *         - 7h : clk_sirc_div1
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkCtl3SrcExtMft2(const PccRegType *obj)
{
    return ((obj->CK_CTL3 & PCC_CK_CTL3_SRC_EXT_MFT2_MASK) >> PCC_CK_CTL3_SRC_EXT_MFT2_SHIFT);
}

/*! \brief Sets the MFT2 external clock source
 *
 * This function sets the MFT2 external clock source.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of MFT2 external clock source
 *                    - 0h : TCLK0
 *                    - 1h : TCLK1
 *                    - 2h : TCLK2
 *                    - 3h : clk_firc_div1
 *                    - 4h : clk_sosc_div1
 *                    - 5h : clk_pll_div1
 *                    - 6h : clk_sirc_div1
 *                    - 7h : clk_sirc_div1
 */
__attribute__((always_inline)) static inline void PccReg_SetCkCtl3SrcExtMft2(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_CTL3;

    tmp &= ~PCC_CK_CTL3_SRC_EXT_MFT2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_CTL3_SRC_EXT_MFT2_SHIFT)) & PCC_CK_CTL3_SRC_EXT_MFT2_MASK);
    obj->CK_CTL3 = tmp;
}

/*! \brief Gets the MFT1 external clock source
 *
 * This function gets the current MFT1 external clock source.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return MFT1 external clock source
 *         - 0h : TCLK0
 *         - 1h : TCLK1
 *         - 2h : TCLK2
 *         - 3h : clk_firc_div1
 *         - 4h : clk_sosc_div1
 *         - 5h : clk_pll_div1
 *         - 6h : clk_sirc_div1
 *         - 7h : clk_sirc_div1
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkCtl3SrcExtMft1(const PccRegType *obj)
{
    return ((obj->CK_CTL3 & PCC_CK_CTL3_SRC_EXT_MFT1_MASK) >> PCC_CK_CTL3_SRC_EXT_MFT1_SHIFT);
}

/*! \brief Sets the MFT1 external clock source
 *
 * This function sets the MFT1 external clock source.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of MFT1 external clock source
 *                    - 0h : TCLK0
 *                    - 1h : TCLK1
 *                    - 2h : TCLK2
 *                    - 3h : clk_firc_div1
 *                    - 4h : clk_sosc_div1
 *                    - 5h : clk_pll_div1
 *                    - 6h : clk_sirc_div1
 *                    - 7h : clk_sirc_div1
 */
__attribute__((always_inline)) static inline void PccReg_SetCkCtl3SrcExtMft1(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_CTL3;

    tmp &= ~PCC_CK_CTL3_SRC_EXT_MFT1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_CTL3_SRC_EXT_MFT1_SHIFT)) & PCC_CK_CTL3_SRC_EXT_MFT1_MASK);
    obj->CK_CTL3 = tmp;
}

/*! \brief Gets the MFT0 external clock source
 *
 * This function gets the current MFT0 external clock source.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return MFT0 external clock source
 *         - 0h : TCLK0
 *         - 1h : TCLK1
 *         - 2h : TCLK2
 *         - 3h : clk_firc_div1
 *         - 4h : clk_sosc_div1
 *         - 5h : clk_pll_div1
 *         - 6h : clk_sirc_div1
 *         - 7h : clk_sirc_div1
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkCtl3SrcExtMft0(const PccRegType *obj)
{
    return ((obj->CK_CTL3 & PCC_CK_CTL3_SRC_EXT_MFT0_MASK) >> PCC_CK_CTL3_SRC_EXT_MFT0_SHIFT);
}

/*! \brief Sets the MFT0 external clock source
 *
 * This function sets the MFT0 external clock source.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of MFT0 external clock source
 *                    - 0h : TCLK0
 *                    - 1h : TCLK1
 *                    - 2h : TCLK2
 *                    - 3h : clk_firc_div1
 *                    - 4h : clk_sosc_div1
 *                    - 5h : clk_pll_div1
 *                    - 6h : clk_sirc_div1
 *                    - 7h : clk_sirc_div1
 */
__attribute__((always_inline)) static inline void PccReg_SetCkCtl3SrcExtMft0(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_CTL3;

    tmp &= ~PCC_CK_CTL3_SRC_EXT_MFT0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_CTL3_SRC_EXT_MFT0_SHIFT)) & PCC_CK_CTL3_SRC_EXT_MFT0_MASK);
    obj->CK_CTL3 = tmp;
}

/*! \brief Gets the PRNG clock enable
 *
 * This function gets the current PRNG clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return PRNG clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn0Prng(const PccRegType *obj)
{
    return ((obj->CK_EN0 & PCC_CK_EN0_PRNG_MASK) >> PCC_CK_EN0_PRNG_SHIFT);
}

/*! \brief Sets the PRNG clock enable
 *
 * This function sets the PRNG clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of PRNG clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn0Prng(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN0;

    tmp &= ~PCC_CK_EN0_PRNG_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN0_PRNG_SHIFT)) & PCC_CK_EN0_PRNG_MASK);
    obj->CK_EN0 = tmp;
}

/*! \brief Gets the CSE clock enable
 *
 * This function gets the current CSE clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return CSE clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn0Cse(const PccRegType *obj)
{
    return ((obj->CK_EN0 & PCC_CK_EN0_CSE_MASK) >> PCC_CK_EN0_CSE_SHIFT);
}

/*! \brief Sets the CSE clock enable
 *
 * This function sets the CSE clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of CSE clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn0Cse(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN0;

    tmp &= ~PCC_CK_EN0_CSE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN0_CSE_SHIFT)) & PCC_CK_EN0_CSE_MASK);
    obj->CK_EN0 = tmp;
}

/*! \brief Gets the CRC clock enable
 *
 * This function gets the current CRC clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return CRC clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn0Crc(const PccRegType *obj)
{
    return ((obj->CK_EN0 & PCC_CK_EN0_CRC_MASK) >> PCC_CK_EN0_CRC_SHIFT);
}

/*! \brief Sets the CRC clock enable
 *
 * This function sets the CRC clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of CRC clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn0Crc(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN0;

    tmp &= ~PCC_CK_EN0_CRC_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN0_CRC_SHIFT)) & PCC_CK_EN0_CRC_MASK);
    obj->CK_EN0 = tmp;
}

/*! \brief Gets the I2S slave clock enable
 *
 * This function gets the current I2S slave clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return I2S slave clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn0I2SS(const PccRegType *obj)
{
    return ((obj->CK_EN0 & PCC_CK_EN0_I2SS_MASK) >> PCC_CK_EN0_I2SS_SHIFT);
}

/*! \brief Sets the I2S slave clock enable
 *
 * This function sets the I2S slave clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of I2S slave clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn0I2SS(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN0;

    tmp &= ~PCC_CK_EN0_I2SS_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN0_I2SS_SHIFT)) & PCC_CK_EN0_I2SS_MASK);
    obj->CK_EN0 = tmp;
}

/*! \brief Gets the I2S master clock enable
 *
 * This function gets the current I2S master clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return I2S master clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn0I2SM(const PccRegType *obj)
{
    return ((obj->CK_EN0 & PCC_CK_EN0_I2SM_MASK) >> PCC_CK_EN0_I2SM_SHIFT);
}

/*! \brief Sets the I2S master clock enable
 *
 * This function sets the I2S master clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of I2S master clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn0I2SM(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN0;

    tmp &= ~PCC_CK_EN0_I2SM_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN0_I2SM_SHIFT)) & PCC_CK_EN0_I2SM_MASK);
    obj->CK_EN0 = tmp;
}

/*! \brief Gets the I2C clock enable
 *
 * This function gets the current I2C clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return I2C clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn0I2C(const PccRegType *obj)
{
    return ((obj->CK_EN0 & PCC_CK_EN0_I2C_MASK) >> PCC_CK_EN0_I2C_SHIFT);
}

/*! \brief Sets the I2C clock enable
 *
 * This function sets the I2C clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of I2C clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn0I2C(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN0;

    tmp &= ~PCC_CK_EN0_I2C_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN0_I2C_SHIFT)) & PCC_CK_EN0_I2C_MASK);
    obj->CK_EN0 = tmp;
}

/*! \brief Gets the UART3 clock enable
 *
 * This function gets the current UART3 clock enable.
 * It works for both function clock and configure clock.
 * If UART3 is not available, this bit is reserved.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return UART3 clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn0Uart3(const PccRegType *obj)
{
    return ((obj->CK_EN0 & PCC_CK_EN0_UART3_MASK) >> PCC_CK_EN0_UART3_SHIFT);
}

/*! \brief Sets the UART3 clock enable
 *
 * This function sets the UART3 clock enable.
 * It works for both function clock and configure clock.
 * If UART3 is not available, this bit is reserved.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of UART3 clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn0Uart3(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN0;

    tmp &= ~PCC_CK_EN0_UART3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN0_UART3_SHIFT)) & PCC_CK_EN0_UART3_MASK);
    obj->CK_EN0 = tmp;
}

/*! \brief Gets the UART2 clock enable
 *
 * This function gets the current UART2 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return UART2 clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn0Uart2(const PccRegType *obj)
{
    return ((obj->CK_EN0 & PCC_CK_EN0_UART2_MASK) >> PCC_CK_EN0_UART2_SHIFT);
}

/*! \brief Sets the UART2 clock enable
 *
 * This function sets the UART2 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of UART2 clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn0Uart2(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN0;

    tmp &= ~PCC_CK_EN0_UART2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN0_UART2_SHIFT)) & PCC_CK_EN0_UART2_MASK);
    obj->CK_EN0 = tmp;
}

/*! \brief Gets the UART1 clock enable
 *
 * This function gets the current UART1 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return UART1 clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn0Uart1(const PccRegType *obj)
{
    return ((obj->CK_EN0 & PCC_CK_EN0_UART1_MASK) >> PCC_CK_EN0_UART1_SHIFT);
}

/*! \brief Sets the UART1 clock enable
 *
 * This function sets the UART1 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of UART1 clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn0Uart1(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN0;

    tmp &= ~PCC_CK_EN0_UART1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN0_UART1_SHIFT)) & PCC_CK_EN0_UART1_MASK);
    obj->CK_EN0 = tmp;
}

/*! \brief Gets the UART0 clock enable
 *
 * This function gets the current UART0 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return UART0 clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn0Uart0(const PccRegType *obj)
{
    return ((obj->CK_EN0 & PCC_CK_EN0_UART0_MASK) >> PCC_CK_EN0_UART0_SHIFT);
}

/*! \brief Sets the UART0 clock enable
 *
 * This function sets the UART0 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of UART0 clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn0Uart0(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN0;

    tmp &= ~PCC_CK_EN0_UART0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN0_UART0_SHIFT)) & PCC_CK_EN0_UART0_MASK);
    obj->CK_EN0 = tmp;
}

/*! \brief Gets the SPI3 clock enable
 *
 * This function gets the current SPI3 clock enable.
 * It works for both function clock and configure clock.
 * If SPI3 is not available, this bit is reserved.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return SPI3 clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn0Spi3(const PccRegType *obj)
{
    return ((obj->CK_EN0 & PCC_CK_EN0_SPI3_MASK) >> PCC_CK_EN0_SPI3_SHIFT);
}

/*! \brief Sets the SPI3 clock enable
 *
 * This function sets the SPI3 clock enable.
 * It works for both function clock and configure clock.
 * If SPI3 is not available, this bit is reserved.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of SPI3 clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn0Spi3(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN0;

    tmp &= ~PCC_CK_EN0_SPI3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN0_SPI3_SHIFT)) & PCC_CK_EN0_SPI3_MASK);
    obj->CK_EN0 = tmp;
}

/*! \brief Gets the SPI2 clock enable
 *
 * This function gets the current SPI2 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return SPI2 clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn0Spi2(const PccRegType *obj)
{
    return ((obj->CK_EN0 & PCC_CK_EN0_SPI2_MASK) >> PCC_CK_EN0_SPI2_SHIFT);
}

/*! \brief Sets the SPI2 clock enable
 *
 * This function sets the SPI2 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of SPI2 clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn0Spi2(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN0;

    tmp &= ~PCC_CK_EN0_SPI2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN0_SPI2_SHIFT)) & PCC_CK_EN0_SPI2_MASK);
    obj->CK_EN0 = tmp;
}

/*! \brief Gets the SPI1 clock enable
 *
 * This function gets the current SPI1 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return SPI1 clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn0Spi1(const PccRegType *obj)
{
    return ((obj->CK_EN0 & PCC_CK_EN0_SPI1_MASK) >> PCC_CK_EN0_SPI1_SHIFT);
}

/*! \brief Sets the SPI1 clock enable
 *
 * This function sets the SPI1 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of SPI1 clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn0Spi1(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN0;

    tmp &= ~PCC_CK_EN0_SPI1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN0_SPI1_SHIFT)) & PCC_CK_EN0_SPI1_MASK);
    obj->CK_EN0 = tmp;
}

/*! \brief Gets the SPI0 clock enable
 *
 * This function gets the current SPI0 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return SPI0 clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn0Spi0(const PccRegType *obj)
{
    return ((obj->CK_EN0 & PCC_CK_EN0_SPI0_MASK) >> PCC_CK_EN0_SPI0_SHIFT);
}

/*! \brief Sets the SPI0 clock enable
 *
 * This function sets the SPI0 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of SPI0 clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn0Spi0(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN0;

    tmp &= ~PCC_CK_EN0_SPI0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN0_SPI0_SHIFT)) & PCC_CK_EN0_SPI0_MASK);
    obj->CK_EN0 = tmp;
}

/*! \brief Gets the PDB1 clock enable
 *
 * This function gets the current PDB1 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return PDB1 clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn0Pdb1(const PccRegType *obj)
{
    return ((obj->CK_EN0 & PCC_CK_EN0_PDB1_MASK) >> PCC_CK_EN0_PDB1_SHIFT);
}

/*! \brief Sets the PDB1 clock enable
 *
 * This function sets the PDB1 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of PDB1 clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn0Pdb1(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN0;

    tmp &= ~PCC_CK_EN0_PDB1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN0_PDB1_SHIFT)) & PCC_CK_EN0_PDB1_MASK);
    obj->CK_EN0 = tmp;
}

/*! \brief Gets the PDB0 clock enable
 *
 * This function gets the current PDB0 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return PDB0 clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn0Pdb0(const PccRegType *obj)
{
    return ((obj->CK_EN0 & PCC_CK_EN0_PDB0_MASK) >> PCC_CK_EN0_PDB0_SHIFT);
}

/*! \brief Sets the PDB0 clock enable
 *
 * This function sets the PDB0 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of PDB0 clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn0Pdb0(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN0;

    tmp &= ~PCC_CK_EN0_PDB0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN0_PDB0_SHIFT)) & PCC_CK_EN0_PDB0_MASK);
    obj->CK_EN0 = tmp;
}

/*! \brief Gets the ADC1 clock enable
 *
 * This function gets the current ADC1 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return ADC1 clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn0Adc1(const PccRegType *obj)
{
    return ((obj->CK_EN0 & PCC_CK_EN0_ADC1_MASK) >> PCC_CK_EN0_ADC1_SHIFT);
}

/*! \brief Sets the ADC1 clock enable
 *
 * This function sets the ADC1 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of ADC1 clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn0Adc1(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN0;

    tmp &= ~PCC_CK_EN0_ADC1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN0_ADC1_SHIFT)) & PCC_CK_EN0_ADC1_MASK);
    obj->CK_EN0 = tmp;
}

/*! \brief Gets the ADC0 clock enable
 *
 * This function gets the current ADC0 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return ADC0 clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn0Adc0(const PccRegType *obj)
{
    return ((obj->CK_EN0 & PCC_CK_EN0_ADC0_MASK) >> PCC_CK_EN0_ADC0_SHIFT);
}

/*! \brief Sets the ADC0 clock enable
 *
 * This function sets the ADC0 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of ADC0 clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn0Adc0(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN0;

    tmp &= ~PCC_CK_EN0_ADC0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN0_ADC0_SHIFT)) & PCC_CK_EN0_ADC0_MASK);
    obj->CK_EN0 = tmp;
}

/*! \brief Gets the CAN3 clock enable
 *
 * This function gets the current CAN3 clock enable.
 * It works for function clock.
 * If CAN3 is not available, this bit is reserved.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return CAN3 clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn0Can3(const PccRegType *obj)
{
    return ((obj->CK_EN0 & PCC_CK_EN0_CAN3_MASK) >> PCC_CK_EN0_CAN3_SHIFT);
}

/*! \brief Sets the CAN3 clock enable
 *
 * This function sets the CAN3 clock enable.
 * It works for function clock.
 * If CAN3 is not available, this bit is reserved.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of CAN3 clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn0Can3(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN0;

    tmp &= ~PCC_CK_EN0_CAN3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN0_CAN3_SHIFT)) & PCC_CK_EN0_CAN3_MASK);
    obj->CK_EN0 = tmp;
}

/*! \brief Gets the CAN2 clock enable
 *
 * This function gets the current CAN2 clock enable.
 * It works for function clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return CAN2 clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn0Can2(const PccRegType *obj)
{
    return ((obj->CK_EN0 & PCC_CK_EN0_CAN2_MASK) >> PCC_CK_EN0_CAN2_SHIFT);
}

/*! \brief Sets the CAN2 clock enable
 *
 * This function sets the CAN2 clock enable.
 * It works for function clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of CAN2 clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn0Can2(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN0;

    tmp &= ~PCC_CK_EN0_CAN2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN0_CAN2_SHIFT)) & PCC_CK_EN0_CAN2_MASK);
    obj->CK_EN0 = tmp;
}

/*! \brief Gets the CAN1 clock enable
 *
 * This function gets the current CAN1 clock enable.
 * It works for function clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return CAN1 clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn0Can1(const PccRegType *obj)
{
    return ((obj->CK_EN0 & PCC_CK_EN0_CAN1_MASK) >> PCC_CK_EN0_CAN1_SHIFT);
}

/*! \brief Sets the CAN1 clock enable
 *
 * This function sets the CAN1 clock enable.
 * It works for function clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of CAN1 clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn0Can1(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN0;

    tmp &= ~PCC_CK_EN0_CAN1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN0_CAN1_SHIFT)) & PCC_CK_EN0_CAN1_MASK);
    obj->CK_EN0 = tmp;
}

/*! \brief Gets the CAN0 clock enable
 *
 * This function gets the current CAN0 clock enable.
 * It works for function clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return CAN0 clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn0Can0(const PccRegType *obj)
{
    return ((obj->CK_EN0 & PCC_CK_EN0_CAN0_MASK) >> PCC_CK_EN0_CAN0_SHIFT);
}

/*! \brief Sets the CAN0 clock enable
 *
 * This function sets the CAN0 clock enable.
 * It works for function clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of CAN0 clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn0Can0(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN0;

    tmp &= ~PCC_CK_EN0_CAN0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN0_CAN0_SHIFT)) & PCC_CK_EN0_CAN0_MASK);
    obj->CK_EN0 = tmp;
}

/*! \brief Gets the DMAMUX clock enable
 *
 * This function gets the current DMAMUX clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return DMAMUX clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn0DmaMux(const PccRegType *obj)
{
    return ((obj->CK_EN0 & PCC_CK_EN0_DMAMUX_MASK) >> PCC_CK_EN0_DMAMUX_SHIFT);
}

/*! \brief Sets the DMAMUX clock enable
 *
 * This function sets the DMAMUX clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of DMAMUX clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn0DmaMux(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN0;

    tmp &= ~PCC_CK_EN0_DMAMUX_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN0_DMAMUX_SHIFT)) & PCC_CK_EN0_DMAMUX_MASK);
    obj->CK_EN0 = tmp;
}

/*! \brief Gets the EWM clock enable
 *
 * This function gets the current EWM clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return EWM clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn0Ewm(const PccRegType *obj)
{
    return ((obj->CK_EN0 & PCC_CK_EN0_EWM_MASK) >> PCC_CK_EN0_EWM_SHIFT);
}

/*! \brief Sets the EWM clock enable
 *
 * This function sets the EWM clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of EWM clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn0Ewm(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN0;

    tmp &= ~PCC_CK_EN0_EWM_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN0_EWM_SHIFT)) & PCC_CK_EN0_EWM_MASK);
    obj->CK_EN0 = tmp;
}

/*! \brief Gets the MPU clock enable
 *
 * This function gets the current MPU clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return MPU clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn0Mpu(const PccRegType *obj)
{
    return ((obj->CK_EN0 & PCC_CK_EN0_MPU_MASK) >> PCC_CK_EN0_MPU_SHIFT);
}

/*! \brief Sets the MPU clock enable
 *
 * This function sets the MPU clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of MPU clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn0Mpu(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN0;

    tmp &= ~PCC_CK_EN0_MPU_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN0_MPU_SHIFT)) & PCC_CK_EN0_MPU_MASK);
    obj->CK_EN0 = tmp;
}

/*! \brief Gets the MSCM clock enable
 *
 * This function gets the current MSCM clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return MSCM clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn0Mscm(const PccRegType *obj)
{
    return ((obj->CK_EN0 & PCC_CK_EN0_MSCM_MASK) >> PCC_CK_EN0_MSCM_SHIFT);
}

/*! \brief Sets the MSCM clock enable
 *
 * This function sets the MSCM clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of MSCM clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn0Mscm(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN0;

    tmp &= ~PCC_CK_EN0_MSCM_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN0_MSCM_SHIFT)) & PCC_CK_EN0_MSCM_MASK);
    obj->CK_EN0 = tmp;
}

/*! \brief Gets the ERM clock enable
 *
 * This function gets the current ERM clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return ERM clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn0Erm(const PccRegType *obj)
{
    return ((obj->CK_EN0 & PCC_CK_EN0_ERM_MASK) >> PCC_CK_EN0_ERM_SHIFT);
}

/*! \brief Sets the ERM clock enable
 *
 * This function sets the ERM clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of ERM clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn0Erm(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN0;

    tmp &= ~PCC_CK_EN0_ERM_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN0_ERM_SHIFT)) & PCC_CK_EN0_ERM_MASK);
    obj->CK_EN0 = tmp;
}

/*! \brief Gets the EIM clock enable
 *
 * This function gets the current EIM clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return EIM clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn0Eim(const PccRegType *obj)
{
    return ((obj->CK_EN0 & PCC_CK_EN0_EIM_MASK) >> PCC_CK_EN0_EIM_SHIFT);
}

/*! \brief Sets the EIM clock enable
 *
 * This function sets the EIM clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of EIM clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn0Eim(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN0;

    tmp &= ~PCC_CK_EN0_EIM_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN0_EIM_SHIFT)) & PCC_CK_EN0_EIM_MASK);
    obj->CK_EN0 = tmp;
}

/*! \brief Gets the DMA clock enable
 *
 * This function gets the current DMA clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return DMA clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn0Dma(const PccRegType *obj)
{
    return ((obj->CK_EN0 & PCC_CK_EN0_DMA_MASK) >> PCC_CK_EN0_DMA_SHIFT);
}

/*! \brief Sets the DMA clock enable
 *
 * This function sets the DMA clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of DMA clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn0Dma(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN0;

    tmp &= ~PCC_CK_EN0_DMA_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN0_DMA_SHIFT)) & PCC_CK_EN0_DMA_MASK);
    obj->CK_EN0 = tmp;
}

/*! \brief Gets the flash controller clock enable
 *
 * This function gets the current flash controller clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return flash controller clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn0Fls(const PccRegType *obj)
{
    return ((obj->CK_EN0 & PCC_CK_EN0_FLS_MASK) >> PCC_CK_EN0_FLS_SHIFT);
}

/*! \brief Sets the flash controller clock enable
 *
 * This function sets the flash controller clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of flash controller clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn0Fls(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN0;

    tmp &= ~PCC_CK_EN0_FLS_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN0_FLS_SHIFT)) & PCC_CK_EN0_FLS_MASK);
    obj->CK_EN0 = tmp;
}

/*! \brief Gets the CAN3 configure clock enable
 *
 * This function gets the current CAN3 configure clock enable.
 * It works for configure clock.
 * If CAN3 is not available, this bit is reserved.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return CAN3 configure clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn1CfgCan3(const PccRegType *obj)
{
    return ((obj->CK_EN1 & PCC_CK_EN1_CFG_CAN3_MASK) >> PCC_CK_EN1_CFG_CAN3_SHIFT);
}

/*! \brief Sets the CAN3 configure clock enable
 *
 * This function sets the CAN3 configure clock enable.
 * It works for configure clock.
 * If CAN3 is not available, this bit is reserved.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of CAN3 configure clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn1CfgCan3(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN1;

    tmp &= ~PCC_CK_EN1_CFG_CAN3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN1_CFG_CAN3_SHIFT)) & PCC_CK_EN1_CFG_CAN3_MASK);
    obj->CK_EN1 = tmp;
}

/*! \brief Gets the CAN2 configure clock enable
 *
 * This function gets the current CAN2 configure clock enable.
 * It works for configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return CAN2 configure clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn1CfgCan2(const PccRegType *obj)
{
    return ((obj->CK_EN1 & PCC_CK_EN1_CFG_CAN2_MASK) >> PCC_CK_EN1_CFG_CAN2_SHIFT);
}

/*! \brief Sets the CAN2 configure clock enable
 *
 * This function sets the CAN2 configure clock enable.
 * It works for configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of CAN2 configure clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn1CfgCan2(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN1;

    tmp &= ~PCC_CK_EN1_CFG_CAN2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN1_CFG_CAN2_SHIFT)) & PCC_CK_EN1_CFG_CAN2_MASK);
    obj->CK_EN1 = tmp;
}

/*! \brief Gets the CAN1 configure clock enable
 *
 * This function gets the current CAN1 configure clock enable.
 * It works for configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return CAN1 configure clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn1CfgCan1(const PccRegType *obj)
{
    return ((obj->CK_EN1 & PCC_CK_EN1_CFG_CAN1_MASK) >> PCC_CK_EN1_CFG_CAN1_SHIFT);
}

/*! \brief Sets the CAN1 configure clock enable
 *
 * This function sets the CAN1 configure clock enable.
 * It works for configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of CAN1 configure clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn1CfgCan1(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN1;

    tmp &= ~PCC_CK_EN1_CFG_CAN1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN1_CFG_CAN1_SHIFT)) & PCC_CK_EN1_CFG_CAN1_MASK);
    obj->CK_EN1 = tmp;
}

/*! \brief Gets the CAN0 configure clock enable
 *
 * This function gets the current CAN0 configure clock enable.
 * It works for configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return CAN0 configure clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn1CfgCan0(const PccRegType *obj)
{
    return ((obj->CK_EN1 & PCC_CK_EN1_CFG_CAN0_MASK) >> PCC_CK_EN1_CFG_CAN0_SHIFT);
}

/*! \brief Sets the CAN0 configure clock enable
 *
 * This function sets the CAN0 configure clock enable.
 * It works for configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of CAN0 configure clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn1CfgCan0(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN1;

    tmp &= ~PCC_CK_EN1_CFG_CAN0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN1_CFG_CAN0_SHIFT)) & PCC_CK_EN1_CFG_CAN0_MASK);
    obj->CK_EN1 = tmp;
}

/*! \brief Gets the FCCU clock enable
 *
 * This function gets the current FCCU clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return FCCU clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn1Fccu(const PccRegType *obj)
{
    return ((obj->CK_EN1 & PCC_CK_EN1_FCCU_MASK) >> PCC_CK_EN1_FCCU_SHIFT);
}

/*! \brief Sets the FCCU clock enable
 *
 * This function sets the FCCU clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of FCCU clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn1Fccu(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN1;

    tmp &= ~PCC_CK_EN1_FCCU_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN1_FCCU_SHIFT)) & PCC_CK_EN1_FCCU_MASK);
    obj->CK_EN1 = tmp;
}

/*! \brief Gets the CMUS clock enable
 *
 * This function gets the current CMUS clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return CMUS clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn1Cmus(const PccRegType *obj)
{
    return ((obj->CK_EN1 & PCC_CK_EN1_CMUS_MASK) >> PCC_CK_EN1_CMUS_SHIFT);
}

/*! \brief Sets the CMUS clock enable
 *
 * This function sets the CMUS clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of CMUS clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn1Cmus(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN1;

    tmp &= ~PCC_CK_EN1_CMUS_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN1_CMUS_SHIFT)) & PCC_CK_EN1_CMUS_MASK);
    obj->CK_EN1 = tmp;
}

/*! \brief Gets the CMUP clock enable
 *
 * This function gets the current CMUP clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return CMUP clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn1Cmup(const PccRegType *obj)
{
    return ((obj->CK_EN1 & PCC_CK_EN1_CMUP_MASK) >> PCC_CK_EN1_CMUP_SHIFT);
}

/*! \brief Sets the CMUP clock enable
 *
 * This function sets the CMUP clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of CMUP clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn1Cmup(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN1;

    tmp &= ~PCC_CK_EN1_CMUP_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN1_CMUP_SHIFT)) & PCC_CK_EN1_CMUP_MASK);
    obj->CK_EN1 = tmp;
}

/*! \brief Gets the CMUF clock enable
 *
 * This function gets the current CMUF clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return CMUF clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn1Cmuf(const PccRegType *obj)
{
    return ((obj->CK_EN1 & PCC_CK_EN1_CMUF_MASK) >> PCC_CK_EN1_CMUF_SHIFT);
}

/*! \brief Sets the CMUF clock enable
 *
 * This function sets the CMUF clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of CMUF clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn1Cmuf(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN1;

    tmp &= ~PCC_CK_EN1_CMUF_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN1_CMUF_SHIFT)) & PCC_CK_EN1_CMUF_MASK);
    obj->CK_EN1 = tmp;
}

/*! \brief Gets the PWM4 clock enable
 *
 * This function gets the current PWM4 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return PWM4 clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn1Pwm4(const PccRegType *obj)
{
    return ((obj->CK_EN1 & PCC_CK_EN1_PWM4_MASK) >> PCC_CK_EN1_PWM4_SHIFT);
}

/*! \brief Sets the PWM4 clock enable
 *
 * This function sets the PWM4 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of PWM4 clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn1Pwm4(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN1;

    tmp &= ~PCC_CK_EN1_PWM4_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN1_PWM4_SHIFT)) & PCC_CK_EN1_PWM4_MASK);
    obj->CK_EN1 = tmp;
}

/*! \brief Gets the PWM3 clock enable
 *
 * This function gets the current PWM3 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return PWM3 clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn1Pwm3(const PccRegType *obj)
{
    return ((obj->CK_EN1 & PCC_CK_EN1_PWM3_MASK) >> PCC_CK_EN1_PWM3_SHIFT);
}

/*! \brief Sets the PWM3 clock enable
 *
 * This function sets the PWM3 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of PWM3 clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn1Pwm3(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN1;

    tmp &= ~PCC_CK_EN1_PWM3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN1_PWM3_SHIFT)) & PCC_CK_EN1_PWM3_MASK);
    obj->CK_EN1 = tmp;
}

/*! \brief Gets the PWM2 clock enable
 *
 * This function gets the current PWM2 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return PWM2 clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn1Pwm2(const PccRegType *obj)
{
    return ((obj->CK_EN1 & PCC_CK_EN1_PWM2_MASK) >> PCC_CK_EN1_PWM2_SHIFT);
}

/*! \brief Sets the PWM2 clock enable
 *
 * This function sets the PWM2 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of PWM2 clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn1Pwm2(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN1;

    tmp &= ~PCC_CK_EN1_PWM2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN1_PWM2_SHIFT)) & PCC_CK_EN1_PWM2_MASK);
    obj->CK_EN1 = tmp;
}

/*! \brief Gets the PWM1 clock enable
 *
 * This function gets the current PWM1 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return PWM1 clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn1Pwm1(const PccRegType *obj)
{
    return ((obj->CK_EN1 & PCC_CK_EN1_PWM1_MASK) >> PCC_CK_EN1_PWM1_SHIFT);
}

/*! \brief Sets the PWM1 clock enable
 *
 * This function sets the PWM1 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of PWM1 clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn1Pwm1(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN1;

    tmp &= ~PCC_CK_EN1_PWM1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN1_PWM1_SHIFT)) & PCC_CK_EN1_PWM1_MASK);
    obj->CK_EN1 = tmp;
}

/*! \brief Gets the PWM0 clock enable
 *
 * This function gets the current PWM0 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return PWM0 clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn1Pwm0(const PccRegType *obj)
{
    return ((obj->CK_EN1 & PCC_CK_EN1_PWM0_MASK) >> PCC_CK_EN1_PWM0_SHIFT);
}

/*! \brief Sets the PWM0 clock enable
 *
 * This function sets the PWM0 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of PWM0 clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn1Pwm0(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN1;

    tmp &= ~PCC_CK_EN1_PWM0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN1_PWM0_SHIFT)) & PCC_CK_EN1_PWM0_MASK);
    obj->CK_EN1 = tmp;
}

/*! \brief Gets the MFT5 clock enable
 *
 * This function gets the current MFT5 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return MFT5 clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn1Mft5(const PccRegType *obj)
{
    return ((obj->CK_EN1 & PCC_CK_EN1_MFT5_MASK) >> PCC_CK_EN1_MFT5_SHIFT);
}

/*! \brief Sets the MFT5 clock enable
 *
 * This function sets the MFT5 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of MFT5 clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn1Mft5(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN1;

    tmp &= ~PCC_CK_EN1_MFT5_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN1_MFT5_SHIFT)) & PCC_CK_EN1_MFT5_MASK);
    obj->CK_EN1 = tmp;
}

/*! \brief Gets the MFT4 clock enable
 *
 * This function gets the current MFT4 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return MFT4 clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn1Mft4(const PccRegType *obj)
{
    return ((obj->CK_EN1 & PCC_CK_EN1_MFT4_MASK) >> PCC_CK_EN1_MFT4_SHIFT);
}

/*! \brief Sets the MFT4 clock enable
 *
 * This function sets the MFT4 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of MFT4 clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn1Mft4(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN1;

    tmp &= ~PCC_CK_EN1_MFT4_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN1_MFT4_SHIFT)) & PCC_CK_EN1_MFT4_MASK);
    obj->CK_EN1 = tmp;
}

/*! \brief Gets the MFT3 clock enable
 *
 * This function gets the current MFT3 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return MFT3 clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn1Mft3(const PccRegType *obj)
{
    return ((obj->CK_EN1 & PCC_CK_EN1_MFT3_MASK) >> PCC_CK_EN1_MFT3_SHIFT);
}

/*! \brief Sets the MFT3 clock enable
 *
 * This function sets the MFT3 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of MFT3 clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn1Mft3(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN1;

    tmp &= ~PCC_CK_EN1_MFT3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN1_MFT3_SHIFT)) & PCC_CK_EN1_MFT3_MASK);
    obj->CK_EN1 = tmp;
}

/*! \brief Gets the MFT2 clock enable
 *
 * This function gets the current MFT2 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return MFT2 clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn1Mft2(const PccRegType *obj)
{
    return ((obj->CK_EN1 & PCC_CK_EN1_MFT2_MASK) >> PCC_CK_EN1_MFT2_SHIFT);
}

/*! \brief Sets the MFT2 clock enable
 *
 * This function sets the MFT2 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of MFT2 clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn1Mft2(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN1;

    tmp &= ~PCC_CK_EN1_MFT2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN1_MFT2_SHIFT)) & PCC_CK_EN1_MFT2_MASK);
    obj->CK_EN1 = tmp;
}

/*! \brief Gets the MFT1 clock enable
 *
 * This function gets the current MFT1 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return MFT1 clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn1Mft1(const PccRegType *obj)
{
    return ((obj->CK_EN1 & PCC_CK_EN1_MFT1_MASK) >> PCC_CK_EN1_MFT1_SHIFT);
}

/*! \brief Sets the MFT1 clock enable
 *
 * This function sets the MFT1 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of MFT1 clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn1Mft1(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN1;

    tmp &= ~PCC_CK_EN1_MFT1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN1_MFT1_SHIFT)) & PCC_CK_EN1_MFT1_MASK);
    obj->CK_EN1 = tmp;
}

/*! \brief Gets the MFT0 clock enable
 *
 * This function gets the current MFT0 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return MFT0 clock enable
 *         - 0b : disable
 *         - 1b : enable
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetCkEn1Mft0(const PccRegType *obj)
{
    return ((obj->CK_EN1 & PCC_CK_EN1_MFT0_MASK) >> PCC_CK_EN1_MFT0_SHIFT);
}

/*! \brief Sets the MFT0 clock enable
 *
 * This function sets the MFT0 clock enable.
 * It works for both function clock and configure clock.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of MFT0 clock enable
 *                    - 0b : disable
 *                    - 1b : enable
 */
__attribute__((always_inline)) static inline void PccReg_SetCkEn1Mft0(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CK_EN1;

    tmp &= ~PCC_CK_EN1_MFT0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_CK_EN1_MFT0_SHIFT)) & PCC_CK_EN1_MFT0_MASK);
    obj->CK_EN1 = tmp;
}

/*! \brief Sets the PRNG software reset
 *
 * This function sets the PRNG software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of PRNG software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst0Prng(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST0;

    tmp &= ~PCC_SW_RST0_PRNG_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST0_PRNG_SHIFT)) & PCC_SW_RST0_PRNG_MASK);
    obj->SW_RST0 = tmp;
}

/*! \brief Sets the CSE software reset
 *
 * This function sets the CSE software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of CSE software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst0Cse(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST0;

    tmp &= ~PCC_SW_RST0_CSE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST0_CSE_SHIFT)) & PCC_SW_RST0_CSE_MASK);
    obj->SW_RST0 = tmp;
}

/*! \brief Sets the CRC software reset
 *
 * This function sets the CRC software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of CRC software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst0Crc(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST0;

    tmp &= ~PCC_SW_RST0_CRC_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST0_CRC_SHIFT)) & PCC_SW_RST0_CRC_MASK);
    obj->SW_RST0 = tmp;
}

/*! \brief Sets the I2S SLAVE software reset
 *
 * This function sets the I2S SLAVE software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of I2S SLAVE software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst0I2SS(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST0;

    tmp &= ~PCC_SW_RST0_I2SS_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST0_I2SS_SHIFT)) & PCC_SW_RST0_I2SS_MASK);
    obj->SW_RST0 = tmp;
}

/*! \brief Sets the I2S MASTER software reset
 *
 * This function sets the I2S MASTER software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of I2S MASTER software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst0I2SM(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST0;

    tmp &= ~PCC_SW_RST0_I2SM_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST0_I2SM_SHIFT)) & PCC_SW_RST0_I2SM_MASK);
    obj->SW_RST0 = tmp;
}

/*! \brief Sets the I2C software reset
 *
 * This function sets the I2C software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of I2C software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst0I2C(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST0;

    tmp &= ~PCC_SW_RST0_I2C_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST0_I2C_SHIFT)) & PCC_SW_RST0_I2C_MASK);
    obj->SW_RST0 = tmp;
}

/*! \brief Sets the UART3 software reset
 *
 * This function sets the UART3 software reset.
 * It works for both function clock domain and configure clock domain.
 * If UART3 is not available, this bit is reserved.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of UART3 software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst0Uart3(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST0;

    tmp &= ~PCC_SW_RST0_UART3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST0_UART3_SHIFT)) & PCC_SW_RST0_UART3_MASK);
    obj->SW_RST0 = tmp;
}

/*! \brief Sets the UART2 software reset
 *
 * This function sets the UART2 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of UART2 software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst0Uart2(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST0;

    tmp &= ~PCC_SW_RST0_UART2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST0_UART2_SHIFT)) & PCC_SW_RST0_UART2_MASK);
    obj->SW_RST0 = tmp;
}

/*! \brief Sets the UART1 software reset
 *
 * This function sets the UART1 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of UART1 software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst0Uart1(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST0;

    tmp &= ~PCC_SW_RST0_UART1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST0_UART1_SHIFT)) & PCC_SW_RST0_UART1_MASK);
    obj->SW_RST0 = tmp;
}

/*! \brief Sets the UART0 software reset
 *
 * This function sets the UART0 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of UART0 software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst0Uart0(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST0;

    tmp &= ~PCC_SW_RST0_UART0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST0_UART0_SHIFT)) & PCC_SW_RST0_UART0_MASK);
    obj->SW_RST0 = tmp;
}

/*! \brief Sets the SPI3 software reset
 *
 * This function sets the SPI3 software reset.
 * It works for both function clock domain and configure clock domain.
 * If SPI3 is not available, this bit is reserved.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of SPI3 software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst0Spi3(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST0;

    tmp &= ~PCC_SW_RST0_SPI3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST0_SPI3_SHIFT)) & PCC_SW_RST0_SPI3_MASK);
    obj->SW_RST0 = tmp;
}

/*! \brief Sets the SPI2 software reset
 *
 * This function sets the SPI2 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of SPI2 software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst0Spi2(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST0;

    tmp &= ~PCC_SW_RST0_SPI2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST0_SPI2_SHIFT)) & PCC_SW_RST0_SPI2_MASK);
    obj->SW_RST0 = tmp;
}

/*! \brief Sets the SPI1 software reset
 *
 * This function sets the SPI1 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of SPI1 software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst0Spi1(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST0;

    tmp &= ~PCC_SW_RST0_SPI1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST0_SPI1_SHIFT)) & PCC_SW_RST0_SPI1_MASK);
    obj->SW_RST0 = tmp;
}

/*! \brief Sets the SPI0 software reset
 *
 * This function sets the SPI0 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of SPI0 software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst0Spi0(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST0;

    tmp &= ~PCC_SW_RST0_SPI0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST0_SPI0_SHIFT)) & PCC_SW_RST0_SPI0_MASK);
    obj->SW_RST0 = tmp;
}

/*! \brief Sets the PDB1 software reset
 *
 * This function sets the PDB1 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of PDB1 software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst0Pdb1(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST0;

    tmp &= ~PCC_SW_RST0_PDB1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST0_PDB1_SHIFT)) & PCC_SW_RST0_PDB1_MASK);
    obj->SW_RST0 = tmp;
}

/*! \brief Sets the PDB0 software reset
 *
 * This function sets the PDB0 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of PDB0 software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst0Pdb0(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST0;

    tmp &= ~PCC_SW_RST0_PDB0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST0_PDB0_SHIFT)) & PCC_SW_RST0_PDB0_MASK);
    obj->SW_RST0 = tmp;
}

/*! \brief Sets the ADC1 software reset
 *
 * This function sets the ADC1 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of ADC1 software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst0Adc1(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST0;

    tmp &= ~PCC_SW_RST0_ADC1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST0_ADC1_SHIFT)) & PCC_SW_RST0_ADC1_MASK);
    obj->SW_RST0 = tmp;
}

/*! \brief Sets the ADC0 software reset
 *
 * This function sets the ADC0 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of ADC0 software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst0Adc0(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST0;

    tmp &= ~PCC_SW_RST0_ADC0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST0_ADC0_SHIFT)) & PCC_SW_RST0_ADC0_MASK);
    obj->SW_RST0 = tmp;
}

/*! \brief Sets the CAN3 software reset
 *
 * This function sets the CAN3 software reset.
 * It works for both function clock domain and configure clock domain.
 * If CAN3 is not available, this bit is reserved.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of CAN3 software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst0Can3(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST0;

    tmp &= ~PCC_SW_RST0_CAN3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST0_CAN3_SHIFT)) & PCC_SW_RST0_CAN3_MASK);
    obj->SW_RST0 = tmp;
}

/*! \brief Sets the CAN2 software reset
 *
 * This function sets the CAN2 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of CAN2 software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst0Can2(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST0;

    tmp &= ~PCC_SW_RST0_CAN2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST0_CAN2_SHIFT)) & PCC_SW_RST0_CAN2_MASK);
    obj->SW_RST0 = tmp;
}

/*! \brief Sets the CAN1 software reset
 *
 * This function sets the CAN1 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of CAN1 software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst0Can1(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST0;

    tmp &= ~PCC_SW_RST0_CAN1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST0_CAN1_SHIFT)) & PCC_SW_RST0_CAN1_MASK);
    obj->SW_RST0 = tmp;
}

/*! \brief Sets the CAN0 software reset
 *
 * This function sets the CAN0 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of CAN0 software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst0Can0(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST0;

    tmp &= ~PCC_SW_RST0_CAN0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST0_CAN0_SHIFT)) & PCC_SW_RST0_CAN0_MASK);
    obj->SW_RST0 = tmp;
}

/*! \brief Sets the DMAMUX software reset
 *
 * This function sets the DMAMUX software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of DMAMUX software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst0DmaMux(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST0;

    tmp &= ~PCC_SW_RST0_DMAMUX_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST0_DMAMUX_SHIFT)) & PCC_SW_RST0_DMAMUX_MASK);
    obj->SW_RST0 = tmp;
}

/*! \brief Sets the EWM software reset
 *
 * This function sets the EWM software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of EWM software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst0Ewm(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST0;

    tmp &= ~PCC_SW_RST0_EWM_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST0_EWM_SHIFT)) & PCC_SW_RST0_EWM_MASK);
    obj->SW_RST0 = tmp;
}

/*! \brief Sets the MPU software reset
 *
 * This function sets the MPU software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of MPU software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst0Mpu(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST0;

    tmp &= ~PCC_SW_RST0_MPU_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST0_MPU_SHIFT)) & PCC_SW_RST0_MPU_MASK);
    obj->SW_RST0 = tmp;
}

/*! \brief Sets the MSCM software reset
 *
 * This function sets the MSCM software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of MSCM software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst0Mscm(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST0;

    tmp &= ~PCC_SW_RST0_MSCM_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST0_MSCM_SHIFT)) & PCC_SW_RST0_MSCM_MASK);
    obj->SW_RST0 = tmp;
}

/*! \brief Sets the ERM software reset
 *
 * This function sets the ERM software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of ERM software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst0Erm(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST0;

    tmp &= ~PCC_SW_RST0_ERM_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST0_ERM_SHIFT)) & PCC_SW_RST0_ERM_MASK);
    obj->SW_RST0 = tmp;
}

/*! \brief Sets the EIM software reset
 *
 * This function sets the EIM software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of EIM software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst0Eim(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST0;

    tmp &= ~PCC_SW_RST0_EIM_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST0_EIM_SHIFT)) & PCC_SW_RST0_EIM_MASK);
    obj->SW_RST0 = tmp;
}

/*! \brief Sets the DMA software reset
 *
 * This function sets the DMA software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of DMA software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst0Dma(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST0;

    tmp &= ~PCC_SW_RST0_DMA_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST0_DMA_SHIFT)) & PCC_SW_RST0_DMA_MASK);
    obj->SW_RST0 = tmp;
}

/*! \brief Gets the ÉÁ´æ controller software reset
 *
 * This function gets the current ÉÁ´æ controller software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return ÉÁ´æ controller software reset
 *         - 0b : normal
 *         - 1b : reset
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetSwRst0Fls(const PccRegType *obj)
{
    return ((obj->SW_RST0 & PCC_SW_RST0_FLS_MASK) >> PCC_SW_RST0_FLS_SHIFT);
}

/*! \brief Sets the ÉÁ´æ controller software reset
 *
 * This function sets the ÉÁ´æ controller software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of ÉÁ´æ controller software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst0Fls(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST0;

    tmp &= ~PCC_SW_RST0_FLS_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST0_FLS_SHIFT)) & PCC_SW_RST0_FLS_MASK);
    obj->SW_RST0 = tmp;
}

/*! \brief Sets the FCCU software reset
 *
 * This function sets the FCCU software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of FCCU software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst1Fccu(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST1;

    tmp &= ~PCC_SW_RST1_FCCU_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST1_FCCU_SHIFT)) & PCC_SW_RST1_FCCU_MASK);
    obj->SW_RST1 = tmp;
}

/*! \brief Sets the CMUS software reset
 *
 * This function sets the CMUS software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of CMUS software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst1Cmus(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST1;

    tmp &= ~PCC_SW_RST1_CMUS_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST1_CMUS_SHIFT)) & PCC_SW_RST1_CMUS_MASK);
    obj->SW_RST1 = tmp;
}

/*! \brief Sets the CMUP software reset
 *
 * This function sets the CMUP software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of CMUP software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst1Cmup(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST1;

    tmp &= ~PCC_SW_RST1_CMUP_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST1_CMUP_SHIFT)) & PCC_SW_RST1_CMUP_MASK);
    obj->SW_RST1 = tmp;
}

/*! \brief Sets the CMUF software reset
 *
 * This function sets the CMUF software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of CMUF software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst1Cmuf(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST1;

    tmp &= ~PCC_SW_RST1_CMUF_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST1_CMUF_SHIFT)) & PCC_SW_RST1_CMUF_MASK);
    obj->SW_RST1 = tmp;
}

/*! \brief Sets the GPIO software reset
 *
 * This function sets the GPIO software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of GPIO software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst1Gpio(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST1;

    tmp &= ~PCC_SW_RST1_GPIO_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST1_GPIO_SHIFT)) & PCC_SW_RST1_GPIO_MASK);
    obj->SW_RST1 = tmp;
}

/*! \brief Sets the PWM4 software reset
 *
 * This function sets the PWM4 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of PWM4 software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst1Pwm4(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST1;

    tmp &= ~PCC_SW_RST1_PWM4_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST1_PWM4_SHIFT)) & PCC_SW_RST1_PWM4_MASK);
    obj->SW_RST1 = tmp;
}

/*! \brief Sets the PWM3 software reset
 *
 * This function sets the PWM3 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of PWM3 software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst1Pwm3(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST1;

    tmp &= ~PCC_SW_RST1_PWM3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST1_PWM3_SHIFT)) & PCC_SW_RST1_PWM3_MASK);
    obj->SW_RST1 = tmp;
}

/*! \brief Sets the PWM2 software reset
 *
 * This function sets the PWM2 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of PWM2 software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst1Pwm2(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST1;

    tmp &= ~PCC_SW_RST1_PWM2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST1_PWM2_SHIFT)) & PCC_SW_RST1_PWM2_MASK);
    obj->SW_RST1 = tmp;
}

/*! \brief Sets the PWM1 software reset
 *
 * This function sets the PWM1 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of PWM1 software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst1Pwm1(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST1;

    tmp &= ~PCC_SW_RST1_PWM1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST1_PWM1_SHIFT)) & PCC_SW_RST1_PWM1_MASK);
    obj->SW_RST1 = tmp;
}

/*! \brief Sets the PWM0 software reset
 *
 * This function sets the PWM0 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of PWM0 software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst1Pwm0(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST1;

    tmp &= ~PCC_SW_RST1_PWM0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST1_PWM0_SHIFT)) & PCC_SW_RST1_PWM0_MASK);
    obj->SW_RST1 = tmp;
}

/*! \brief Sets the MFT5 software reset
 *
 * This function sets the MFT5 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of MFT5 software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst1Mft5(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST1;

    tmp &= ~PCC_SW_RST1_MFT5_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST1_MFT5_SHIFT)) & PCC_SW_RST1_MFT5_MASK);
    obj->SW_RST1 = tmp;
}

/*! \brief Sets the MFT4 software reset
 *
 * This function sets the MFT4 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of MFT4 software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst1Mft4(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST1;

    tmp &= ~PCC_SW_RST1_MFT4_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST1_MFT4_SHIFT)) & PCC_SW_RST1_MFT4_MASK);
    obj->SW_RST1 = tmp;
}

/*! \brief Sets the MFT3 software reset
 *
 * This function sets the MFT3 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of MFT3 software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst1Mft3(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST1;

    tmp &= ~PCC_SW_RST1_MFT3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST1_MFT3_SHIFT)) & PCC_SW_RST1_MFT3_MASK);
    obj->SW_RST1 = tmp;
}

/*! \brief Sets the MFT2 software reset
 *
 * This function sets the MFT2 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of MFT2 software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst1Mft2(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST1;

    tmp &= ~PCC_SW_RST1_MFT2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST1_MFT2_SHIFT)) & PCC_SW_RST1_MFT2_MASK);
    obj->SW_RST1 = tmp;
}

/*! \brief Sets the MFT1 software reset
 *
 * This function sets the MFT1 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of MFT1 software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst1Mft1(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST1;

    tmp &= ~PCC_SW_RST1_MFT1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST1_MFT1_SHIFT)) & PCC_SW_RST1_MFT1_MASK);
    obj->SW_RST1 = tmp;
}

/*! \brief Sets the MFT0 software reset
 *
 * This function sets the MFT0 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of MFT0 software reset
 *                    - 0b : normal
 *                    - 1b : reset
 */
__attribute__((always_inline)) static inline void PccReg_SetSwRst1Mft0(PccRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SW_RST1;

    tmp &= ~PCC_SW_RST1_MFT0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PCC_SW_RST1_MFT0_SHIFT)) & PCC_SW_RST1_MFT0_MASK);
    obj->SW_RST1 = tmp;
}

/*! \brief Gets the PRNG software reset
 *
 * This function gets the current PRNG software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return PRNG software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt0Prng(const PccRegType *obj)
{
    return ((obj->RST_ST0 & PCC_RST_ST0_PRNG_MASK) >> PCC_RST_ST0_PRNG_SHIFT);
}

/*! \brief Gets the CSE software reset
 *
 * This function gets the current CSE software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return CSE software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt0Cse(const PccRegType *obj)
{
    return ((obj->RST_ST0 & PCC_RST_ST0_CSE_MASK) >> PCC_RST_ST0_CSE_SHIFT);
}

/*! \brief Gets the CRC software reset
 *
 * This function gets the current CRC software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return CRC software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt0Crc(const PccRegType *obj)
{
    return ((obj->RST_ST0 & PCC_RST_ST0_CRC_MASK) >> PCC_RST_ST0_CRC_SHIFT);
}

/*! \brief Gets the I2S SLAVE software reset
 *
 * This function gets the current I2S SLAVE software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return I2S SLAVE software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt0I2SS(const PccRegType *obj)
{
    return ((obj->RST_ST0 & PCC_RST_ST0_I2SS_MASK) >> PCC_RST_ST0_I2SS_SHIFT);
}

/*! \brief Gets the I2S MASTER software reset
 *
 * This function gets the current I2S MASTER software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return I2S MASTER software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt0I2SM(const PccRegType *obj)
{
    return ((obj->RST_ST0 & PCC_RST_ST0_I2SM_MASK) >> PCC_RST_ST0_I2SM_SHIFT);
}

/*! \brief Gets the I2C software reset
 *
 * This function gets the current I2C software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return I2C software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt0I2C(const PccRegType *obj)
{
    return ((obj->RST_ST0 & PCC_RST_ST0_I2C_MASK) >> PCC_RST_ST0_I2C_SHIFT);
}

/*! \brief Gets the UART3 software reset
 *
 * This function gets the current UART3 software reset.
 * It works for both function clock domain and configure clock domain.
 * If UART3 is not available, this bit is reserved.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return UART3 software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt0Uart3(const PccRegType *obj)
{
    return ((obj->RST_ST0 & PCC_RST_ST0_UART3_MASK) >> PCC_RST_ST0_UART3_SHIFT);
}

/*! \brief Gets the UART2 software reset
 *
 * This function gets the current UART2 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return UART2 software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt0Uart2(const PccRegType *obj)
{
    return ((obj->RST_ST0 & PCC_RST_ST0_UART2_MASK) >> PCC_RST_ST0_UART2_SHIFT);
}

/*! \brief Gets the UART1 software reset
 *
 * This function gets the current UART1 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return UART1 software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt0Uart1(const PccRegType *obj)
{
    return ((obj->RST_ST0 & PCC_RST_ST0_UART1_MASK) >> PCC_RST_ST0_UART1_SHIFT);
}

/*! \brief Gets the UART0 software reset
 *
 * This function gets the current UART0 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return UART0 software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt0Uart0(const PccRegType *obj)
{
    return ((obj->RST_ST0 & PCC_RST_ST0_UART0_MASK) >> PCC_RST_ST0_UART0_SHIFT);
}

/*! \brief Gets the SPI3 software reset
 *
 * This function gets the current SPI3 software reset.
 * It works for both function clock domain and configure clock domain.
 * If SPI3 is not available, this bit is reserved.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return SPI3 software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt0Spi3(const PccRegType *obj)
{
    return ((obj->RST_ST0 & PCC_RST_ST0_SPI3_MASK) >> PCC_RST_ST0_SPI3_SHIFT);
}

/*! \brief Gets the SPI2 software reset
 *
 * This function gets the current SPI2 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return SPI2 software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt0Spi2(const PccRegType *obj)
{
    return ((obj->RST_ST0 & PCC_RST_ST0_SPI2_MASK) >> PCC_RST_ST0_SPI2_SHIFT);
}

/*! \brief Gets the SPI1 software reset
 *
 * This function gets the current SPI1 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return SPI1 software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt0Spi1(const PccRegType *obj)
{
    return ((obj->RST_ST0 & PCC_RST_ST0_SPI1_MASK) >> PCC_RST_ST0_SPI1_SHIFT);
}

/*! \brief Gets the SPI0 software reset
 *
 * This function gets the current SPI0 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return SPI0 software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt0Spi0(const PccRegType *obj)
{
    return ((obj->RST_ST0 & PCC_RST_ST0_SPI0_MASK) >> PCC_RST_ST0_SPI0_SHIFT);
}

/*! \brief Gets the PDB1 software reset
 *
 * This function gets the current PDB1 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return PDB1 software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt0Pdb1(const PccRegType *obj)
{
    return ((obj->RST_ST0 & PCC_RST_ST0_PDB1_MASK) >> PCC_RST_ST0_PDB1_SHIFT);
}

/*! \brief Gets the PDB0 software reset
 *
 * This function gets the current PDB0 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return PDB0 software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt0Pdb0(const PccRegType *obj)
{
    return ((obj->RST_ST0 & PCC_RST_ST0_PDB0_MASK) >> PCC_RST_ST0_PDB0_SHIFT);
}

/*! \brief Gets the ADC1 software reset
 *
 * This function gets the current ADC1 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return ADC1 software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt0Adc1(const PccRegType *obj)
{
    return ((obj->RST_ST0 & PCC_RST_ST0_ADC1_MASK) >> PCC_RST_ST0_ADC1_SHIFT);
}

/*! \brief Gets the ADC0 software reset
 *
 * This function gets the current ADC0 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return ADC0 software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt0Adc0(const PccRegType *obj)
{
    return ((obj->RST_ST0 & PCC_RST_ST0_ADC0_MASK) >> PCC_RST_ST0_ADC0_SHIFT);
}

/*! \brief Gets the CAN3 software reset
 *
 * This function gets the current CAN3 software reset.
 * It works for both function clock domain and configure clock domain.
 * If CAN3 is not available, this bit is reserved.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return CAN3 software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt0Can3(const PccRegType *obj)
{
    return ((obj->RST_ST0 & PCC_RST_ST0_CAN3_MASK) >> PCC_RST_ST0_CAN3_SHIFT);
}

/*! \brief Gets the CAN2 software reset
 *
 * This function gets the current CAN2 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return CAN2 software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt0Can2(const PccRegType *obj)
{
    return ((obj->RST_ST0 & PCC_RST_ST0_CAN2_MASK) >> PCC_RST_ST0_CAN2_SHIFT);
}

/*! \brief Gets the CAN1 software reset
 *
 * This function gets the current CAN1 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return CAN1 software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt0Can1(const PccRegType *obj)
{
    return ((obj->RST_ST0 & PCC_RST_ST0_CAN1_MASK) >> PCC_RST_ST0_CAN1_SHIFT);
}

/*! \brief Gets the CAN0 software reset
 *
 * This function gets the current CAN0 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return CAN0 software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt0Can0(const PccRegType *obj)
{
    return ((obj->RST_ST0 & PCC_RST_ST0_CAN0_MASK) >> PCC_RST_ST0_CAN0_SHIFT);
}

/*! \brief Gets the DMAMUX software reset
 *
 * This function gets the current DMAMUX software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return DMAMUX software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt0DmaMux(const PccRegType *obj)
{
    return ((obj->RST_ST0 & PCC_RST_ST0_DMAMUX_MASK) >> PCC_RST_ST0_DMAMUX_SHIFT);
}

/*! \brief Gets the EWM software reset
 *
 * This function gets the current EWM software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return EWM software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt0Ewm(const PccRegType *obj)
{
    return ((obj->RST_ST0 & PCC_RST_ST0_EWM_MASK) >> PCC_RST_ST0_EWM_SHIFT);
}

/*! \brief Gets the MPU software reset
 *
 * This function gets the current MPU software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return MPU software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt0Mpu(const PccRegType *obj)
{
    return ((obj->RST_ST0 & PCC_RST_ST0_MPU_MASK) >> PCC_RST_ST0_MPU_SHIFT);
}

/*! \brief Gets the MSCM software reset
 *
 * This function gets the current MSCM software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return MSCM software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt0Mscm(const PccRegType *obj)
{
    return ((obj->RST_ST0 & PCC_RST_ST0_MSCM_MASK) >> PCC_RST_ST0_MSCM_SHIFT);
}

/*! \brief Gets the ERM software reset
 *
 * This function gets the current ERM software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return ERM software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt0Erm(const PccRegType *obj)
{
    return ((obj->RST_ST0 & PCC_RST_ST0_ERM_MASK) >> PCC_RST_ST0_ERM_SHIFT);
}

/*! \brief Gets the EIM software reset
 *
 * This function gets the current EIM software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return EIM software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt0Eim(const PccRegType *obj)
{
    return ((obj->RST_ST0 & PCC_RST_ST0_EIM_MASK) >> PCC_RST_ST0_EIM_SHIFT);
}

/*! \brief Gets the DMA software reset
 *
 * This function gets the current DMA software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return DMA software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt0Dma(const PccRegType *obj)
{
    return ((obj->RST_ST0 & PCC_RST_ST0_DMA_MASK) >> PCC_RST_ST0_DMA_SHIFT);
}

/*! \brief Gets the Flash controller software reset
 *
 * This function gets the current Flash controller software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return Flash controller software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt0Fls(const PccRegType *obj)
{
    return ((obj->RST_ST0 & PCC_RST_ST0_FLS_MASK) >> PCC_RST_ST0_FLS_SHIFT);
}

/*! \brief Gets the FCCU software reset
 *
 * This function gets the current FCCU software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return FCCU software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt1Fccu(const PccRegType *obj)
{
    return ((obj->RST_ST1 & PCC_RST_ST1_FCCU_MASK) >> PCC_RST_ST1_FCCU_SHIFT);
}

/*! \brief Gets the CMUS software reset
 *
 * This function gets the current CMUS software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return CMUS software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt1Cmus(const PccRegType *obj)
{
    return ((obj->RST_ST1 & PCC_RST_ST1_CMUS_MASK) >> PCC_RST_ST1_CMUS_SHIFT);
}

/*! \brief Gets the CMUP software reset
 *
 * This function gets the current CMUP software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return CMUP software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt1Cmup(const PccRegType *obj)
{
    return ((obj->RST_ST1 & PCC_RST_ST1_CMUP_MASK) >> PCC_RST_ST1_CMUP_SHIFT);
}

/*! \brief Gets the CMUF software reset
 *
 * This function gets the current CMUF software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return CMUF software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt1Cmuf(const PccRegType *obj)
{
    return ((obj->RST_ST1 & PCC_RST_ST1_CMUF_MASK) >> PCC_RST_ST1_CMUF_SHIFT);
}

/*! \brief Gets the GPIO software reset
 *
 * This function gets the current GPIO software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return GPIO software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt1Gpio(const PccRegType *obj)
{
    return ((obj->RST_ST1 & PCC_RST_ST1_GPIO_MASK) >> PCC_RST_ST1_GPIO_SHIFT);
}

/*! \brief Gets the PWM4 software reset
 *
 * This function gets the current PWM4 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return PWM4 software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt1Pwm4(const PccRegType *obj)
{
    return ((obj->RST_ST1 & PCC_RST_ST1_PWM4_MASK) >> PCC_RST_ST1_PWM4_SHIFT);
}

/*! \brief Gets the PWM3 software reset
 *
 * This function gets the current PWM3 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return PWM3 software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt1Pwm3(const PccRegType *obj)
{
    return ((obj->RST_ST1 & PCC_RST_ST1_PWM3_MASK) >> PCC_RST_ST1_PWM3_SHIFT);
}

/*! \brief Gets the PWM2 software reset
 *
 * This function gets the current PWM2 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return PWM2 software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt1Pwm2(const PccRegType *obj)
{
    return ((obj->RST_ST1 & PCC_RST_ST1_PWM2_MASK) >> PCC_RST_ST1_PWM2_SHIFT);
}

/*! \brief Gets the PWM1 software reset
 *
 * This function gets the current PWM1 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return PWM1 software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt1Pwm1(const PccRegType *obj)
{
    return ((obj->RST_ST1 & PCC_RST_ST1_PWM1_MASK) >> PCC_RST_ST1_PWM1_SHIFT);
}

/*! \brief Gets the PWM0 software reset
 *
 * This function gets the current PWM0 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return PWM0 software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt1Pwm0(const PccRegType *obj)
{
    return ((obj->RST_ST1 & PCC_RST_ST1_PWM0_MASK) >> PCC_RST_ST1_PWM0_SHIFT);
}

/*! \brief Gets the MFT5 software reset
 *
 * This function gets the current MFT5 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return MFT5 software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt1Mft5(const PccRegType *obj)
{
    return ((obj->RST_ST1 & PCC_RST_ST1_MFT5_MASK) >> PCC_RST_ST1_MFT5_SHIFT);
}

/*! \brief Gets the MFT4 software reset
 *
 * This function gets the current MFT4 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return MFT4 software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt1Mft4(const PccRegType *obj)
{
    return ((obj->RST_ST1 & PCC_RST_ST1_MFT4_MASK) >> PCC_RST_ST1_MFT4_SHIFT);
}

/*! \brief Gets the MFT3 software reset
 *
 * This function gets the current MFT3 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return MFT3 software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt1Mft3(const PccRegType *obj)
{
    return ((obj->RST_ST1 & PCC_RST_ST1_MFT3_MASK) >> PCC_RST_ST1_MFT3_SHIFT);
}

/*! \brief Gets the MFT2 software reset
 *
 * This function gets the current MFT2 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return MFT2 software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt1Mft2(const PccRegType *obj)
{
    return ((obj->RST_ST1 & PCC_RST_ST1_MFT2_MASK) >> PCC_RST_ST1_MFT2_SHIFT);
}

/*! \brief Gets the MFT1 software reset
 *
 * This function gets the current MFT1 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return MFT1 software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt1Mft1(const PccRegType *obj)
{
    return ((obj->RST_ST1 & PCC_RST_ST1_MFT1_MASK) >> PCC_RST_ST1_MFT1_SHIFT);
}

/*! \brief Gets the MFT0 software reset
 *
 * This function gets the current MFT0 software reset.
 * It works for both function clock domain and configure clock domain.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return MFT0 software reset
 *         - 0b : reset done
 *         - 1b : reset in progress
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetRstSt1Mft0(const PccRegType *obj)
{
    return ((obj->RST_ST1 & PCC_RST_ST1_MFT0_MASK) >> PCC_RST_ST1_MFT0_SHIFT);
}

/*! \brief Sets the PCC register unlock key
 *
 * This function sets the PCC register unlock key.
 * Registers in PCC is locked by default. Before writing registers in pcc, write unlock key to this register.
 *
 * \param[in] obj : pointer to PCC register instance
 * \param[in] value : the value of PCC register unlock key
 *                    - 0x70637577 : unlock
 *                    - other : lock
 */
__attribute__((always_inline)) static inline void PccReg_SetLockKey(PccRegType *obj, uint32_t value)
{
    obj->LOCK = value;
}

/*! \brief Gets the PCC register configuration lock status
 *
 * This function gets the current PCC register configuration lock status.
 *
 * \param[in] obj : pointer to PCC register instance
 * \return PCC register configuration lock status
 *         - 0b : unlock
 *         - 1b : lock
 */
__attribute__((always_inline)) static inline uint8_t PccReg_GetLockStLock(const PccRegType *obj)
{
    return ((obj->LOCK_ST & PCC_LOCK_ST_LOCK_MASK) >> PCC_LOCK_ST_LOCK_SHIFT);
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _PCC_REG_H_ */
