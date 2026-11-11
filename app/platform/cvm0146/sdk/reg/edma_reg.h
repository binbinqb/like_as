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

#ifndef _EDMA_REG_H_
#define _EDMA_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the EDMA (Enhance Direct Memory Access) Registers
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * the defines
 ******************************************************************************/

/* Number of EDMA channels. */
#define EDMA_CHANNELS                 (16U)
/* brief Number of EDMA interrupt lines. */
#define EDMA_CHANNELS_INTERRUPT_LINES (16U)
/* brief EDMA supports the following particular transfer size: */
#define EDMA_TRANSFER_SIZE_16B
#define EDMA_TRANSFER_SIZE_32B


/*! \brief Structure for the EDMA hardware request
 *
 * Defines the structure for the EDMA hardware request collections. The user can configure the
 * hardware request into EDMAMUX to trigger the EDMA transfer accordingly. The index
 * of the hardware request varies according  to the to SoC.
 */
typedef enum
{
    EDMA_REQ_DISABLED  = 0U,

    EDMA_REQ_TRIGGER_0 = 1U,
    EDMA_REQ_TRIGGER_1 = 2U,

    EDMA_REQ_UART0_RX = 3U,
    EDMA_REQ_UART0_TX = 4U,
    EDMA_REQ_UART1_RX = 5U,
    EDMA_REQ_UART1_TX = 6U,
    EDMA_REQ_UART2_RX = 7U,
    EDMA_REQ_UART2_TX = 8U,
    EDMA_REQ_UART3_RX = 9U,
    EDMA_REQ_UART3_TX = 10U,

    EDMA_REQ_I2S_SLV = 11U,
    EDMA_REQ_I2S_MST = 12U,

    EDMA_REQ_SPI0_RX = 13U,
    EDMA_REQ_SPI0_TX = 14U,
    EDMA_REQ_SPI1_RX = 15U,
    EDMA_REQ_SPI1_TX = 16U,
    EDMA_REQ_SPI2_RX = 17U,
    EDMA_REQ_SPI2_TX = 18U,
    EDMA_REQ_SPI3_RX = 19U,
    EDMA_REQ_SPI3_TX = 20U,

    EDMA_REQ_MFT1_CHANNEL_0 = 21U,
    EDMA_REQ_MFT1_CHANNEL_1 = 22U,
    EDMA_REQ_MFT1_CHANNEL_2 = 23U,
    EDMA_REQ_MFT1_CHANNEL_3 = 24U,
    EDMA_REQ_MFT1_CHANNEL_4 = 25U,
    EDMA_REQ_MFT1_CHANNEL_5 = 26U,
    EDMA_REQ_MFT1_CHANNEL_6 = 27U,
    EDMA_REQ_MFT1_CHANNEL_7 = 28U,

    EDMA_REQ_MFT2_CHANNEL_0 = 29U,
    EDMA_REQ_MFT2_CHANNEL_1 = 30U,
    EDMA_REQ_MFT2_CHANNEL_2 = 31U,
    EDMA_REQ_MFT2_CHANNEL_3 = 32U,
    EDMA_REQ_MFT2_CHANNEL_4 = 33U,
    EDMA_REQ_MFT2_CHANNEL_5 = 34U,
    EDMA_REQ_MFT2_CHANNEL_6 = 35U,
    EDMA_REQ_MFT2_CHANNEL_7 = 36U,

    EDMA_REQ_MFT0_CHANNEL_0_1 = 37U,
    EDMA_REQ_MFT0_CHANNEL_2_3 = 38U,
    EDMA_REQ_MFT0_CHANNEL_4_5 = 39U,
    EDMA_REQ_MFT0_CHANNEL_6_7 = 40U,

    EDMA_REQ_MFT3_CHANNEL_0_1 = 41U,
    EDMA_REQ_MFT3_CHANNEL_2_3 = 42U,
    EDMA_REQ_MFT3_CHANNEL_4_5 = 43U,
    EDMA_REQ_MFT3_CHANNEL_6_7 = 44U,

    EDMA_REQ_MFT4_CHANNEL_0_1 = 45U,
    EDMA_REQ_MFT4_CHANNEL_2_3 = 46U,
    EDMA_REQ_MFT4_CHANNEL_4_5 = 47U,
    EDMA_REQ_MFT4_CHANNEL_6_7 = 48U,

    EDMA_REQ_MFT5_CHANNEL_0_1 = 49U,
    EDMA_REQ_MFT5_CHANNEL_2_3 = 50U,
    EDMA_REQ_MFT5_CHANNEL_4_5 = 51U,
    EDMA_REQ_MFT5_CHANNEL_6_7 = 52U,

    EDMA_REQ_I2C0_RX = 53U,
    EDMA_REQ_I2C0_TX = 54U,

    EDMA_REQ_PDB0 = 55U,
    EDMA_REQ_PDB1 = 56U,
    EDMA_REQ_CMP0 = 57U,

    EDMA_REQ_PORTA = 58U,
    EDMA_REQ_PORTB = 59U,
    EDMA_REQ_PORTC = 60U,
    EDMA_REQ_PORTD = 61U,
    EDMA_REQ_PORTE = 62U,

    EDMA_REQ_CAN0 = 63U,
    EDMA_REQ_CAN1 = 64U,
    EDMA_REQ_CAN2 = 65U,
    EDMA_REQ_CAN3 = 66U,

    EDMA_REQ_LPTMR0 = 69U,

    EDMA_REQ_ADC0 = 70U,
    EDMA_REQ_ADC1 = 71U,
} EDma_RequestSourceType;

/* CR Bit Fields */
#define EDMA_CR_EDBG_MASK                     (0x2u)
#define EDMA_CR_EDBG_SHIFT                    (1u)
#define EDMA_CR_EDBG_WIDTH                    (1u)
#define EDMA_CR_ERCA_MASK                     (0x4u)
#define EDMA_CR_ERCA_SHIFT                    (2u)
#define EDMA_CR_ERCA_WIDTH                    (1u)
#define EDMA_CR_HOE_MASK                      (0x10u)
#define EDMA_CR_HOE_SHIFT                     (4u)
#define EDMA_CR_HOE_WIDTH                     (1u)
#define EDMA_CR_HALT_MASK                     (0x20u)
#define EDMA_CR_HALT_SHIFT                    (5u)
#define EDMA_CR_HALT_WIDTH                    (1u)
#define EDMA_CR_CLM_MASK                      (0x40u)
#define EDMA_CR_CLM_SHIFT                     (6u)
#define EDMA_CR_CLM_WIDTH                     (1u)
#define EDMA_CR_EMLM_MASK                     (0x80u)
#define EDMA_CR_EMLM_SHIFT                    (7u)
#define EDMA_CR_EMLM_WIDTH                    (1u)
#define EDMA_CR_ECX_MASK                      (0x10000u)
#define EDMA_CR_ECX_SHIFT                     (16u)
#define EDMA_CR_ECX_WIDTH                     (1u)
#define EDMA_CR_CX_MASK                       (0x20000u)
#define EDMA_CR_CX_SHIFT                      (17u)
#define EDMA_CR_CX_WIDTH                      (1u)
#define EDMA_CR_ACTIVE_MASK                   (0x80000000u)
#define EDMA_CR_ACTIVE_SHIFT                  (31u)
#define EDMA_CR_ACTIVE_WIDTH                  (1u)

/* ES Bit Fields */
#define EDMA_ES_DBE_MASK                      (0x1u)
#define EDMA_ES_DBE_SHIFT                     (0u)
#define EDMA_ES_DBE_WIDTH                     (1u)
#define EDMA_ES_SBE_MASK                      (0x2u)
#define EDMA_ES_SBE_SHIFT                     (1u)
#define EDMA_ES_SBE_WIDTH                     (1u)
#define EDMA_ES_SGE_MASK                      (0x4u)
#define EDMA_ES_SGE_SHIFT                     (2u)
#define EDMA_ES_SGE_WIDTH                     (1u)
#define EDMA_ES_NCE_MASK                      (0x8u)
#define EDMA_ES_NCE_SHIFT                     (3u)
#define EDMA_ES_NCE_WIDTH                     (1u)
#define EDMA_ES_DOE_MASK                      (0x10u)
#define EDMA_ES_DOE_SHIFT                     (4u)
#define EDMA_ES_DOE_WIDTH                     (1u)
#define EDMA_ES_DAE_MASK                      (0x20u)
#define EDMA_ES_DAE_SHIFT                     (5u)
#define EDMA_ES_DAE_WIDTH                     (1u)
#define EDMA_ES_SOE_MASK                      (0x40u)
#define EDMA_ES_SOE_SHIFT                     (6u)
#define EDMA_ES_SOE_WIDTH                     (1u)
#define EDMA_ES_SAE_MASK                      (0x80u)
#define EDMA_ES_SAE_SHIFT                     (7u)
#define EDMA_ES_SAE_WIDTH                     (1u)
#define EDMA_ES_ERRCHN_MASK                   (0xF00u)
#define EDMA_ES_ERRCHN_SHIFT                  (8u)
#define EDMA_ES_ERRCHN_WIDTH                  (4u)
#define EDMA_ES_CPE_MASK                      (0x4000u)
#define EDMA_ES_CPE_SHIFT                     (14u)
#define EDMA_ES_CPE_WIDTH                     (1u)
#define EDMA_ES_ECX_MASK                      (0x10000u)
#define EDMA_ES_ECX_SHIFT                     (16u)
#define EDMA_ES_ECX_WIDTH                     (1u)
#define EDMA_ES_VLD_MASK                      (0x80000000u)
#define EDMA_ES_VLD_SHIFT                     (31u)
#define EDMA_ES_VLD_WIDTH                     (1u)

/* ERQ Bit Fields */
#define EDMA_ERQ_ERQ0_MASK                    (0x1u)
#define EDMA_ERQ_ERQ0_SHIFT                   (0u)
#define EDMA_ERQ_ERQ0_WIDTH                   (1u)
#define EDMA_ERQ_ERQ1_MASK                    (0x2u)
#define EDMA_ERQ_ERQ1_SHIFT                   (1u)
#define EDMA_ERQ_ERQ1_WIDTH                   (1u)
#define EDMA_ERQ_ERQ2_MASK                    (0x4u)
#define EDMA_ERQ_ERQ2_SHIFT                   (2u)
#define EDMA_ERQ_ERQ2_WIDTH                   (1u)
#define EDMA_ERQ_ERQ3_MASK                    (0x8u)
#define EDMA_ERQ_ERQ3_SHIFT                   (3u)
#define EDMA_ERQ_ERQ3_WIDTH                   (1u)
#define EDMA_ERQ_ERQ4_MASK                    (0x10u)
#define EDMA_ERQ_ERQ4_SHIFT                   (4u)
#define EDMA_ERQ_ERQ4_WIDTH                   (1u)
#define EDMA_ERQ_ERQ5_MASK                    (0x20u)
#define EDMA_ERQ_ERQ5_SHIFT                   (5u)
#define EDMA_ERQ_ERQ5_WIDTH                   (1u)
#define EDMA_ERQ_ERQ6_MASK                    (0x40u)
#define EDMA_ERQ_ERQ6_SHIFT                   (6u)
#define EDMA_ERQ_ERQ6_WIDTH                   (1u)
#define EDMA_ERQ_ERQ7_MASK                    (0x80u)
#define EDMA_ERQ_ERQ7_SHIFT                   (7u)
#define EDMA_ERQ_ERQ7_WIDTH                   (1u)
#define EDMA_ERQ_ERQ8_MASK                    (0x100u)
#define EDMA_ERQ_ERQ8_SHIFT                   (8u)
#define EDMA_ERQ_ERQ8_WIDTH                   (1u)
#define EDMA_ERQ_ERQ9_MASK                    (0x200u)
#define EDMA_ERQ_ERQ9_SHIFT                   (9u)
#define EDMA_ERQ_ERQ9_WIDTH                   (1u)
#define EDMA_ERQ_ERQ10_MASK                   (0x400u)
#define EDMA_ERQ_ERQ10_SHIFT                  (10u)
#define EDMA_ERQ_ERQ10_WIDTH                  (1u)
#define EDMA_ERQ_ERQ11_MASK                   (0x800u)
#define EDMA_ERQ_ERQ11_SHIFT                  (11u)
#define EDMA_ERQ_ERQ11_WIDTH                  (1u)
#define EDMA_ERQ_ERQ12_MASK                   (0x1000u)
#define EDMA_ERQ_ERQ12_SHIFT                  (12u)
#define EDMA_ERQ_ERQ12_WIDTH                  (1u)
#define EDMA_ERQ_ERQ13_MASK                   (0x2000u)
#define EDMA_ERQ_ERQ13_SHIFT                  (13u)
#define EDMA_ERQ_ERQ13_WIDTH                  (1u)
#define EDMA_ERQ_ERQ14_MASK                   (0x4000u)
#define EDMA_ERQ_ERQ14_SHIFT                  (14u)
#define EDMA_ERQ_ERQ14_WIDTH                  (1u)
#define EDMA_ERQ_ERQ15_MASK                   (0x8000u)
#define EDMA_ERQ_ERQ15_SHIFT                  (15u)
#define EDMA_ERQ_ERQ15_WIDTH                  (1u)

/* EEI Bit Fields */
#define EDMA_EEI_EEI0_MASK                    (0x1u)
#define EDMA_EEI_EEI0_SHIFT                   (0u)
#define EDMA_EEI_EEI0_WIDTH                   (1u)
#define EDMA_EEI_EEI1_MASK                    (0x2u)
#define EDMA_EEI_EEI1_SHIFT                   (1u)
#define EDMA_EEI_EEI1_WIDTH                   (1u)
#define EDMA_EEI_EEI2_MASK                    (0x4u)
#define EDMA_EEI_EEI2_SHIFT                   (2u)
#define EDMA_EEI_EEI2_WIDTH                   (1u)
#define EDMA_EEI_EEI3_MASK                    (0x8u)
#define EDMA_EEI_EEI3_SHIFT                   (3u)
#define EDMA_EEI_EEI3_WIDTH                   (1u)
#define EDMA_EEI_EEI4_MASK                    (0x10u)
#define EDMA_EEI_EEI4_SHIFT                   (4u)
#define EDMA_EEI_EEI4_WIDTH                   (1u)
#define EDMA_EEI_EEI5_MASK                    (0x20u)
#define EDMA_EEI_EEI5_SHIFT                   (5u)
#define EDMA_EEI_EEI5_WIDTH                   (1u)
#define EDMA_EEI_EEI6_MASK                    (0x40u)
#define EDMA_EEI_EEI6_SHIFT                   (6u)
#define EDMA_EEI_EEI6_WIDTH                   (1u)
#define EDMA_EEI_EEI7_MASK                    (0x80u)
#define EDMA_EEI_EEI7_SHIFT                   (7u)
#define EDMA_EEI_EEI7_WIDTH                   (1u)
#define EDMA_EEI_EEI8_MASK                    (0x100u)
#define EDMA_EEI_EEI8_SHIFT                   (8u)
#define EDMA_EEI_EEI8_WIDTH                   (1u)
#define EDMA_EEI_EEI9_MASK                    (0x200u)
#define EDMA_EEI_EEI9_SHIFT                   (9u)
#define EDMA_EEI_EEI9_WIDTH                   (1u)
#define EDMA_EEI_EEI10_MASK                   (0x400u)
#define EDMA_EEI_EEI10_SHIFT                  (10u)
#define EDMA_EEI_EEI10_WIDTH                  (1u)
#define EDMA_EEI_EEI11_MASK                   (0x800u)
#define EDMA_EEI_EEI11_SHIFT                  (11u)
#define EDMA_EEI_EEI11_WIDTH                  (1u)
#define EDMA_EEI_EEI12_MASK                   (0x1000u)
#define EDMA_EEI_EEI12_SHIFT                  (12u)
#define EDMA_EEI_EEI12_WIDTH                  (1u)
#define EDMA_EEI_EEI13_MASK                   (0x2000u)
#define EDMA_EEI_EEI13_SHIFT                  (13u)
#define EDMA_EEI_EEI13_WIDTH                  (1u)
#define EDMA_EEI_EEI14_MASK                   (0x4000u)
#define EDMA_EEI_EEI14_SHIFT                  (14u)
#define EDMA_EEI_EEI14_WIDTH                  (1u)
#define EDMA_EEI_EEI15_MASK                   (0x8000u)
#define EDMA_EEI_EEI15_SHIFT                  (15u)
#define EDMA_EEI_EEI15_WIDTH                  (1u)

/* CEEI Bit Fields */
#define EDMA_CEEI_CEEI_MASK                   (0xFu)
#define EDMA_CEEI_CEEI_SHIFT                  (0u)
#define EDMA_CEEI_CEEI_WIDTH                  (4u)
#define EDMA_CEEI_CAEE_MASK                   (0x40u)
#define EDMA_CEEI_CAEE_SHIFT                  (6u)
#define EDMA_CEEI_CAEE_WIDTH                  (1u)
#define EDMA_CEEI_NOP_MASK                    (0x80u)
#define EDMA_CEEI_NOP_SHIFT                   (7u)
#define EDMA_CEEI_NOP_WIDTH                   (1u)

/* SEEI Bit Fields */
#define EDMA_SEEI_SEEI_MASK                   (0xFu)
#define EDMA_SEEI_SEEI_SHIFT                  (0u)
#define EDMA_SEEI_SEEI_WIDTH                  (4u)
#define EDMA_SEEI_SAEE_MASK                   (0x40u)
#define EDMA_SEEI_SAEE_SHIFT                  (6u)
#define EDMA_SEEI_SAEE_WIDTH                  (1u)
#define EDMA_SEEI_NOP_MASK                    (0x80u)
#define EDMA_SEEI_NOP_SHIFT                   (7u)
#define EDMA_SEEI_NOP_WIDTH                   (1u)

/* CERQ Bit Fields */
#define EDMA_CERQ_CERQ_MASK                   (0xFu)
#define EDMA_CERQ_CERQ_SHIFT                  (0u)
#define EDMA_CERQ_CERQ_WIDTH                  (4u)
#define EDMA_CERQ_CAER_MASK                   (0x40u)
#define EDMA_CERQ_CAER_SHIFT                  (6u)
#define EDMA_CERQ_CAER_WIDTH                  (1u)
#define EDMA_CERQ_NOP_MASK                    (0x80u)
#define EDMA_CERQ_NOP_SHIFT                   (7u)
#define EDMA_CERQ_NOP_WIDTH                   (1u)

/* SERQ Bit Fields */
#define EDMA_SERQ_SERQ_MASK                   (0xFu)
#define EDMA_SERQ_SERQ_SHIFT                  (0u)
#define EDMA_SERQ_SERQ_WIDTH                  (4u)
#define EDMA_SERQ_SAER_MASK                   (0x40u)
#define EDMA_SERQ_SAER_SHIFT                  (6u)
#define EDMA_SERQ_SAER_WIDTH                  (1u)
#define EDMA_SERQ_NOP_MASK                    (0x80u)
#define EDMA_SERQ_NOP_SHIFT                   (7u)
#define EDMA_SERQ_NOP_WIDTH                   (1u)

/* CDNE Bit Fields */
#define EDMA_CDNE_CDNE_MASK                   (0xFu)
#define EDMA_CDNE_CDNE_SHIFT                  (0u)
#define EDMA_CDNE_CDNE_WIDTH                  (4u)
#define EDMA_CDNE_CADN_MASK                   (0x40u)
#define EDMA_CDNE_CADN_SHIFT                  (6u)
#define EDMA_CDNE_CADN_WIDTH                  (1u)
#define EDMA_CDNE_NOP_MASK                    (0x80u)
#define EDMA_CDNE_NOP_SHIFT                   (7u)
#define EDMA_CDNE_NOP_WIDTH                   (1u)

/* SSRT Bit Fields */
#define EDMA_SSRT_SSRT_MASK                   (0xFu)
#define EDMA_SSRT_SSRT_SHIFT                  (0u)
#define EDMA_SSRT_SSRT_WIDTH                  (4u)
#define EDMA_SSRT_SAST_MASK                   (0x40u)
#define EDMA_SSRT_SAST_SHIFT                  (6u)
#define EDMA_SSRT_SAST_WIDTH                  (1u)
#define EDMA_SSRT_NOP_MASK                    (0x80u)
#define EDMA_SSRT_NOP_SHIFT                   (7u)
#define EDMA_SSRT_NOP_WIDTH                   (1u)

/* CERR Bit Fields */
#define EDMA_CERR_CERR_MASK                   (0xFu)
#define EDMA_CERR_CERR_SHIFT                  (0u)
#define EDMA_CERR_CERR_WIDTH                  (4u)
#define EDMA_CERR_CAEI_MASK                   (0x40u)
#define EDMA_CERR_CAEI_SHIFT                  (6u)
#define EDMA_CERR_CAEI_WIDTH                  (1u)
#define EDMA_CERR_NOP_MASK                    (0x80u)
#define EDMA_CERR_NOP_SHIFT                   (7u)
#define EDMA_CERR_NOP_WIDTH                   (1u)

/* CINT Bit Fields */
#define EDMA_CINT_CINT_MASK                   (0xFu)
#define EDMA_CINT_CINT_SHIFT                  (0u)
#define EDMA_CINT_CINT_WIDTH                  (4u)
#define EDMA_CINT_CAIR_MASK                   (0x40u)
#define EDMA_CINT_CAIR_SHIFT                  (6u)
#define EDMA_CINT_CAIR_WIDTH                  (1u)
#define EDMA_CINT_NOP_MASK                    (0x80u)
#define EDMA_CINT_NOP_SHIFT                   (7u)
#define EDMA_CINT_NOP_WIDTH                   (1u)

/* INT Bit Fields */
#define EDMA_INT_INT0_MASK                    (0x1u)
#define EDMA_INT_INT0_SHIFT                   (0u)
#define EDMA_INT_INT0_WIDTH                   (1u)
#define EDMA_INT_INT1_MASK                    (0x2u)
#define EDMA_INT_INT1_SHIFT                   (1u)
#define EDMA_INT_INT1_WIDTH                   (1u)
#define EDMA_INT_INT2_MASK                    (0x4u)
#define EDMA_INT_INT2_SHIFT                   (2u)
#define EDMA_INT_INT2_WIDTH                   (1u)
#define EDMA_INT_INT3_MASK                    (0x8u)
#define EDMA_INT_INT3_SHIFT                   (3u)
#define EDMA_INT_INT3_WIDTH                   (1u)
#define EDMA_INT_INT4_MASK                    (0x10u)
#define EDMA_INT_INT4_SHIFT                   (4u)
#define EDMA_INT_INT4_WIDTH                   (1u)
#define EDMA_INT_INT5_MASK                    (0x20u)
#define EDMA_INT_INT5_SHIFT                   (5u)
#define EDMA_INT_INT5_WIDTH                   (1u)
#define EDMA_INT_INT6_MASK                    (0x40u)
#define EDMA_INT_INT6_SHIFT                   (6u)
#define EDMA_INT_INT6_WIDTH                   (1u)
#define EDMA_INT_INT7_MASK                    (0x80u)
#define EDMA_INT_INT7_SHIFT                   (7u)
#define EDMA_INT_INT7_WIDTH                   (1u)
#define EDMA_INT_INT8_MASK                    (0x100u)
#define EDMA_INT_INT8_SHIFT                   (8u)
#define EDMA_INT_INT8_WIDTH                   (1u)
#define EDMA_INT_INT9_MASK                    (0x200u)
#define EDMA_INT_INT9_SHIFT                   (9u)
#define EDMA_INT_INT9_WIDTH                   (1u)
#define EDMA_INT_INT10_MASK                   (0x400u)
#define EDMA_INT_INT10_SHIFT                  (10u)
#define EDMA_INT_INT10_WIDTH                  (1u)
#define EDMA_INT_INT11_MASK                   (0x800u)
#define EDMA_INT_INT11_SHIFT                  (11u)
#define EDMA_INT_INT11_WIDTH                  (1u)
#define EDMA_INT_INT12_MASK                   (0x1000u)
#define EDMA_INT_INT12_SHIFT                  (12u)
#define EDMA_INT_INT12_WIDTH                  (1u)
#define EDMA_INT_INT13_MASK                   (0x2000u)
#define EDMA_INT_INT13_SHIFT                  (13u)
#define EDMA_INT_INT13_WIDTH                  (1u)
#define EDMA_INT_INT14_MASK                   (0x4000u)
#define EDMA_INT_INT14_SHIFT                  (14u)
#define EDMA_INT_INT14_WIDTH                  (1u)
#define EDMA_INT_INT15_MASK                   (0x8000u)
#define EDMA_INT_INT15_SHIFT                  (15u)
#define EDMA_INT_INT15_WIDTH                  (1u)

/* ERR Bit Fields */
#define EDMA_ERR_ERRN_MASK                    (0x1u)
#define EDMA_ERR_ERR0_MASK                    (0x1u)
#define EDMA_ERR_ERR0_SHIFT                   (0u)
#define EDMA_ERR_ERR0_WIDTH                   (1u)
#define EDMA_ERR_ERR1_MASK                    (0x2u)
#define EDMA_ERR_ERR1_SHIFT                   (1u)
#define EDMA_ERR_ERR1_WIDTH                   (1u)
#define EDMA_ERR_ERR2_MASK                    (0x4u)
#define EDMA_ERR_ERR2_SHIFT                   (2u)
#define EDMA_ERR_ERR2_WIDTH                   (1u)
#define EDMA_ERR_ERR3_MASK                    (0x8u)
#define EDMA_ERR_ERR3_SHIFT                   (3u)
#define EDMA_ERR_ERR3_WIDTH                   (1u)
#define EDMA_ERR_ERR4_MASK                    (0x10u)
#define EDMA_ERR_ERR4_SHIFT                   (4u)
#define EDMA_ERR_ERR4_WIDTH                   (1u)
#define EDMA_ERR_ERR5_MASK                    (0x20u)
#define EDMA_ERR_ERR5_SHIFT                   (5u)
#define EDMA_ERR_ERR5_WIDTH                   (1u)
#define EDMA_ERR_ERR6_MASK                    (0x40u)
#define EDMA_ERR_ERR6_SHIFT                   (6u)
#define EDMA_ERR_ERR6_WIDTH                   (1u)
#define EDMA_ERR_ERR7_MASK                    (0x80u)
#define EDMA_ERR_ERR7_SHIFT                   (7u)
#define EDMA_ERR_ERR7_WIDTH                   (1u)
#define EDMA_ERR_ERR8_MASK                    (0x100u)
#define EDMA_ERR_ERR8_SHIFT                   (8u)
#define EDMA_ERR_ERR8_WIDTH                   (1u)
#define EDMA_ERR_ERR9_MASK                    (0x200u)
#define EDMA_ERR_ERR9_SHIFT                   (9u)
#define EDMA_ERR_ERR9_WIDTH                   (1u)
#define EDMA_ERR_ERR10_MASK                   (0x400u)
#define EDMA_ERR_ERR10_SHIFT                  (10u)
#define EDMA_ERR_ERR10_WIDTH                  (1u)
#define EDMA_ERR_ERR11_MASK                   (0x800u)
#define EDMA_ERR_ERR11_SHIFT                  (11u)
#define EDMA_ERR_ERR11_WIDTH                  (1u)
#define EDMA_ERR_ERR12_MASK                   (0x1000u)
#define EDMA_ERR_ERR12_SHIFT                  (12u)
#define EDMA_ERR_ERR12_WIDTH                  (1u)
#define EDMA_ERR_ERR13_MASK                   (0x2000u)
#define EDMA_ERR_ERR13_SHIFT                  (13u)
#define EDMA_ERR_ERR13_WIDTH                  (1u)
#define EDMA_ERR_ERR14_MASK                   (0x4000u)
#define EDMA_ERR_ERR14_SHIFT                  (14u)
#define EDMA_ERR_ERR14_WIDTH                  (1u)
#define EDMA_ERR_ERR15_MASK                   (0x8000u)
#define EDMA_ERR_ERR15_SHIFT                  (15u)
#define EDMA_ERR_ERR15_WIDTH                  (1u)

/* HRS Bit Fields */
#define EDMA_HRS_HRS0_MASK                    (0x1u)
#define EDMA_HRS_HRS0_SHIFT                   (0u)
#define EDMA_HRS_HRS0_WIDTH                   (1u)
#define EDMA_HRS_HRS1_MASK                    (0x2u)
#define EDMA_HRS_HRS1_SHIFT                   (1u)
#define EDMA_HRS_HRS1_WIDTH                   (1u)
#define EDMA_HRS_HRS2_MASK                    (0x4u)
#define EDMA_HRS_HRS2_SHIFT                   (2u)
#define EDMA_HRS_HRS2_WIDTH                   (1u)
#define EDMA_HRS_HRS3_MASK                    (0x8u)
#define EDMA_HRS_HRS3_SHIFT                   (3u)
#define EDMA_HRS_HRS3_WIDTH                   (1u)
#define EDMA_HRS_HRS4_MASK                    (0x10u)
#define EDMA_HRS_HRS4_SHIFT                   (4u)
#define EDMA_HRS_HRS4_WIDTH                   (1u)
#define EDMA_HRS_HRS5_MASK                    (0x20u)
#define EDMA_HRS_HRS5_SHIFT                   (5u)
#define EDMA_HRS_HRS5_WIDTH                   (1u)
#define EDMA_HRS_HRS6_MASK                    (0x40u)
#define EDMA_HRS_HRS6_SHIFT                   (6u)
#define EDMA_HRS_HRS6_WIDTH                   (1u)
#define EDMA_HRS_HRS7_MASK                    (0x80u)
#define EDMA_HRS_HRS7_SHIFT                   (7u)
#define EDMA_HRS_HRS7_WIDTH                   (1u)
#define EDMA_HRS_HRS8_MASK                    (0x100u)
#define EDMA_HRS_HRS8_SHIFT                   (8u)
#define EDMA_HRS_HRS8_WIDTH                   (1u)
#define EDMA_HRS_HRS9_MASK                    (0x200u)
#define EDMA_HRS_HRS9_SHIFT                   (9u)
#define EDMA_HRS_HRS9_WIDTH                   (1u)
#define EDMA_HRS_HRS10_MASK                   (0x400u)
#define EDMA_HRS_HRS10_SHIFT                  (10u)
#define EDMA_HRS_HRS10_WIDTH                  (1u)
#define EDMA_HRS_HRS11_MASK                   (0x800u)
#define EDMA_HRS_HRS11_SHIFT                  (11u)
#define EDMA_HRS_HRS11_WIDTH                  (1u)
#define EDMA_HRS_HRS12_MASK                   (0x1000u)
#define EDMA_HRS_HRS12_SHIFT                  (12u)
#define EDMA_HRS_HRS12_WIDTH                  (1u)
#define EDMA_HRS_HRS13_MASK                   (0x2000u)
#define EDMA_HRS_HRS13_SHIFT                  (13u)
#define EDMA_HRS_HRS13_WIDTH                  (1u)
#define EDMA_HRS_HRS14_MASK                   (0x4000u)
#define EDMA_HRS_HRS14_SHIFT                  (14u)
#define EDMA_HRS_HRS14_WIDTH                  (1u)
#define EDMA_HRS_HRS15_MASK                   (0x8000u)
#define EDMA_HRS_HRS15_SHIFT                  (15u)
#define EDMA_HRS_HRS15_WIDTH                  (1u)

/* DCHPRI Bit Fields */
#define EDMA_DCHPRI_CHPRI_MASK                (0xFu)
#define EDMA_DCHPRI_CHPRI_SHIFT               (0u)
#define EDMA_DCHPRI_CHPRI_WIDTH               (4u)
#define EDMA_DCHPRI_DPA_MASK                  (0x40u)
#define EDMA_DCHPRI_DPA_SHIFT                 (6u)
#define EDMA_DCHPRI_DPA_WIDTH                 (1u)
#define EDMA_DCHPRI_ECP_MASK                  (0x80u)
#define EDMA_DCHPRI_ECP_SHIFT                 (7u)
#define EDMA_DCHPRI_ECP_WIDTH                 (1u)

/* TCD_SADDR Bit Fields */
#define EDMA_TCD_SADDR_SADDR_MASK             (0xFFFFFFFFu)
#define EDMA_TCD_SADDR_SADDR_SHIFT            (0u)
#define EDMA_TCD_SADDR_SADDR_WIDTH            (32u)

/* TCD_SOFF Bit Fields */
#define EDMA_TCD_SOFF_SOFF_MASK               (0xFFFFu)
#define EDMA_TCD_SOFF_SOFF_SHIFT              (0u)
#define EDMA_TCD_SOFF_SOFF_WIDTH              (16u)

/* TCD_ATTR Bit Fields */
#define EDMA_TCD_ATTR_SDSIZE_MASK             (0x7u)
#define EDMA_TCD_ATTR_SDSIZE_SHIFT            (0u)
#define EDMA_TCD_ATTR_SDSIZE_WIDTH            (3u)
#define EDMA_TCD_ATTR_SDSIZE(x)               (((uint16_t)(((uint16_t)(x)) << EDMA_TCD_ATTR_SDSIZE_SHIFT)) & EDMA_TCD_ATTR_SDSIZE_MASK)
#define EDMA_TCD_ATTR_DMOD_MASK               (0xF8u)
#define EDMA_TCD_ATTR_DMOD_SHIFT              (3u)
#define EDMA_TCD_ATTR_DMOD_WIDTH              (5u)
#define EDMA_TCD_ATTR_DMOD(x)                 (((uint16_t)(((uint16_t)(x)) << EDMA_TCD_ATTR_DMOD_SHIFT)) & EDMA_TCD_ATTR_DMOD_MASK)
#define EDMA_TCD_ATTR_SMOD_MASK               (0xF800u)
#define EDMA_TCD_ATTR_SMOD_SHIFT              (11u)
#define EDMA_TCD_ATTR_SMOD_WIDTH              (5u)
#define EDMA_TCD_ATTR_SMOD(x)                 (((uint16_t)(((uint16_t)(x)) << EDMA_TCD_ATTR_SMOD_SHIFT)) & EDMA_TCD_ATTR_SMOD_MASK)

/* TCD_NBYTES_MLOFFNO Bit Fields */
#define EDMA_TCD_NBYTES_MLOFFNO_NBYTES_MASK   (0x3FFFFFFFu)
#define EDMA_TCD_NBYTES_MLOFFNO_NBYTES_SHIFT  (0u)
#define EDMA_TCD_NBYTES_MLOFFNO_NBYTES_WIDTH  (30u)
#define EDMA_TCD_NBYTES_MLOFFNO_DMLOE_MASK    (0x40000000u)
#define EDMA_TCD_NBYTES_MLOFFNO_DMLOE_SHIFT   (30u)
#define EDMA_TCD_NBYTES_MLOFFNO_DMLOE_WIDTH   (1u)
#define EDMA_TCD_NBYTES_MLOFFNO_SMLOE_MASK    (0x80000000u)
#define EDMA_TCD_NBYTES_MLOFFNO_SMLOE_SHIFT   (31u)
#define EDMA_TCD_NBYTES_MLOFFNO_SMLOE_WIDTH   (1u)

/* TCD_NBYTES_MLOFFYES Bit Fields */
#define EDMA_TCD_NBYTES_MLOFFYES_NBYTES_MASK  (0x3FFu)
#define EDMA_TCD_NBYTES_MLOFFYES_NBYTES_SHIFT (0u)
#define EDMA_TCD_NBYTES_MLOFFYES_NBYTES_WIDTH (10u)
#define EDMA_TCD_NBYTES_MLOFFYES_MLOFF_MASK   (0x3FFFFC00u)
#define EDMA_TCD_NBYTES_MLOFFYES_MLOFF_SHIFT  (10u)
#define EDMA_TCD_NBYTES_MLOFFYES_MLOFF_WIDTH  (20u)
#define EDMA_TCD_NBYTES_MLOFFYES_DMLOE_MASK   (0x40000000u)
#define EDMA_TCD_NBYTES_MLOFFYES_DMLOE_SHIFT  (30u)
#define EDMA_TCD_NBYTES_MLOFFYES_DMLOE_WIDTH  (1u)
#define EDMA_TCD_NBYTES_MLOFFYES_SMLOE_MASK   (0x80000000u)
#define EDMA_TCD_NBYTES_MLOFFYES_SMLOE_SHIFT  (31u)
#define EDMA_TCD_NBYTES_MLOFFYES_SMLOE_WIDTH  (1u)

/* TCD_SLAST Bit Fields */
#define EDMA_TCD_SLAST_SLAST_MASK             (0xFFFFFFFFu)
#define EDMA_TCD_SLAST_SLAST_SHIFT            (0u)
#define EDMA_TCD_SLAST_SLAST_WIDTH            (32u)

/* TCD_DADDR Bit Fields */
#define EDMA_TCD_DADDR_DADDR_MASK             (0xFFFFFFFFu)
#define EDMA_TCD_DADDR_DADDR_SHIFT            (0u)
#define EDMA_TCD_DADDR_DADDR_WIDTH            (32u)

/* TCD_DOFF Bit Fields */
#define EDMA_TCD_DOFF_DOFF_MASK               (0xFFFFu)
#define EDMA_TCD_DOFF_DOFF_SHIFT              (0u)
#define EDMA_TCD_DOFF_DOFF_WIDTH              (16u)

/* TCD_CITER_ELINKNO Bit Fields */
#define EDMA_TCD_CITER_ELINKNO_CITER_MASK     (0x7FFFu)
#define EDMA_TCD_CITER_ELINKNO_CITER_SHIFT    (0u)
#define EDMA_TCD_CITER_ELINKNO_CITER_WIDTH    (15u)
#define EDMA_TCD_CITER_ELINKNO_ELINK_MASK     (0x8000u)
#define EDMA_TCD_CITER_ELINKNO_ELINK_SHIFT    (15u)
#define EDMA_TCD_CITER_ELINKNO_ELINK_WIDTH    (1u)

/* TCD_CITER_ELINKYES Bit Fields */
#define EDMA_TCD_CITER_ELINKYES_CITER_MASK    (0x1FFu)
#define EDMA_TCD_CITER_ELINKYES_CITER_SHIFT   (0u)
#define EDMA_TCD_CITER_ELINKYES_CITER_WIDTH   (9u)
#define EDMA_TCD_CITER_ELINKYES_LINKCH_MASK   (0x1E00u)
#define EDMA_TCD_CITER_ELINKYES_LINKCH_SHIFT  (9u)
#define EDMA_TCD_CITER_ELINKYES_LINKCH_WIDTH  (4u)
#define EDMA_TCD_CITER_ELINKYES_ELINK_MASK    (0x8000u)
#define EDMA_TCD_CITER_ELINKYES_ELINK_SHIFT   (15u)
#define EDMA_TCD_CITER_ELINKYES_ELINK_WIDTH   (1u)

/* TCD_DLASTSGA Bit Fields */
#define EDMA_TCD_DLASTSGA_DLASTSGA_MASK       (0xFFFFFFFFu)
#define EDMA_TCD_DLASTSGA_DLASTSGA_SHIFT      (0u)
#define EDMA_TCD_DLASTSGA_DLASTSGA_WIDTH      (32u)

/* TCD_CSR Bit Fields */
#define EDMA_TCD_CSR_START_MASK               (0x1u)
#define EDMA_TCD_CSR_START_SHIFT              (0u)
#define EDMA_TCD_CSR_START_WIDTH              (1u)
#define EDMA_TCD_CSR_INTMAJOR_MASK            (0x2u)
#define EDMA_TCD_CSR_INTMAJOR_SHIFT           (1u)
#define EDMA_TCD_CSR_INTMAJOR_WIDTH           (1u)
#define EDMA_TCD_CSR_INTHALF_MASK             (0x4u)
#define EDMA_TCD_CSR_INTHALF_SHIFT            (2u)
#define EDMA_TCD_CSR_INTHALF_WIDTH            (1u)
#define EDMA_TCD_CSR_DREQ_MASK                (0x8u)
#define EDMA_TCD_CSR_DREQ_SHIFT               (3u)
#define EDMA_TCD_CSR_DREQ_WIDTH               (1u)
#define EDMA_TCD_CSR_ESG_MASK                 (0x10u)
#define EDMA_TCD_CSR_ESG_SHIFT                (4u)
#define EDMA_TCD_CSR_ESG_WIDTH                (1u)
#define EDMA_TCD_CSR_MAJORELINK_MASK          (0x20u)
#define EDMA_TCD_CSR_MAJORELINK_SHIFT         (5u)
#define EDMA_TCD_CSR_MAJORELINK_WIDTH         (1u)
#define EDMA_TCD_CSR_ACTIVE_MASK              (0x40u)
#define EDMA_TCD_CSR_ACTIVE_SHIFT             (6u)
#define EDMA_TCD_CSR_ACTIVE_WIDTH             (1u)
#define EDMA_TCD_CSR_DONE_MASK                (0x80u)
#define EDMA_TCD_CSR_DONE_SHIFT               (7u)
#define EDMA_TCD_CSR_DONE_WIDTH               (1u)
#define EDMA_TCD_CSR_MAJORLINKCH_MASK         (0xF00u)
#define EDMA_TCD_CSR_MAJORLINKCH_SHIFT        (8u)
#define EDMA_TCD_CSR_MAJORLINKCH_WIDTH        (4u)
#define EDMA_TCD_CSR_HARD_CLR_DONE_MASK       (0x1000u)
#define EDMA_TCD_CSR_HARD_CLR_DONE_SHIFT      (12u)
#define EDMA_TCD_CSR_HARD_CLR_DONE_WIDTH      (1u)

/* TCD_BITER_ELINKNO Bit Fields */
#define EDMA_TCD_BITER_ELINKNO_BITER_MASK     (0x7FFFu)
#define EDMA_TCD_BITER_ELINKNO_BITER_SHIFT    (0u)
#define EDMA_TCD_BITER_ELINKNO_BITER_WIDTH    (15u)
#define EDMA_TCD_BITER_ELINKNO_ELINK_MASK     (0x8000u)
#define EDMA_TCD_BITER_ELINKNO_ELINK_SHIFT    (15u)
#define EDMA_TCD_BITER_ELINKNO_ELINK_WIDTH    (1u)

/* TCD_BITER_ELINKYES Bit Fields */
#define EDMA_TCD_BITER_ELINKYES_BITER_MASK    (0x1FFu)
#define EDMA_TCD_BITER_ELINKYES_BITER_SHIFT   (0u)
#define EDMA_TCD_BITER_ELINKYES_BITER_WIDTH   (9u)
#define EDMA_TCD_BITER_ELINKYES_LINKCH_MASK   (0x1E00u)
#define EDMA_TCD_BITER_ELINKYES_LINKCH_SHIFT  (9u)
#define EDMA_TCD_BITER_ELINKYES_LINKCH_WIDTH  (4u)
#define EDMA_TCD_BITER_ELINKYES_ELINK_MASK    (0x8000u)
#define EDMA_TCD_BITER_ELINKYES_ELINK_SHIFT   (15u)
#define EDMA_TCD_BITER_ELINKYES_ELINK_WIDTH   (1u)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/
/*! \brief EDMA - Size of Registers Arrays
 */
#define EDMA_DCHPRI_COUNT                     (16u)
#define EDMA_TCD_COUNT                        (16u)

/*! \brief The definition of EDMA registers
 */
typedef struct _EDmaRegType_
{
    volatile uint32_t CR;                          /*!< EDMA control register, offset: 0x0 */
    volatile uint32_t ES;                          /*!< EDMA status register, offset: 0x4 */
    uint32_t          RESERVED0;                   /*!< Reserved register, offset: 0x8 */
    volatile uint32_t ERQ;                         /*!< EDMA enable request register, offset: 0xC */
    uint32_t          RESERVED1;                   /*!< Reserved register, offset: 0x10 */
    volatile uint32_t EEI;                         /*!< EDMA enable error interrupt register, offset: 0x14 */
    volatile uint8_t  CEEI;                        /*!< EDMA clear enable error interrupt register, offset: 0x18 */
    volatile uint8_t  SEEI;                        /*!< EDMA clear enable error interrupt register, offset: 0x19 */
    volatile uint8_t  CERQ;                        /*!< EDMA clear enable error interrupt register, offset: 0x1A */
    volatile uint8_t  SERQ;                        /*!< EDMA clear enable error interrupt register, offset: 0x1B */
    volatile uint8_t  CDNE;                        /*!< EDMA clear enable error interrupt register, offset: 0x1C */
    volatile uint8_t  SSRT;                        /*!< EDMA clear enable error interrupt register, offset: 0x1D */
    volatile uint8_t  CERR;                        /*!< EDMA clear enable error interrupt register, offset: 0x1E */
    volatile uint8_t  CINT;                        /*!< EDMA clear enable error interrupt register, offset: 0x1F */
    uint32_t          RESERVED2;                   /*!< Reserved register, offset: 0x20 */
    volatile uint32_t INT;                         /*!< EDMA interrupt request register, offset: 0x24 */
    uint32_t          RESERVED3;                   /*!< Reserved register, offset: 0x28 */
    volatile uint32_t ERR;                         /*!< EDMA error register, offset: 0x2C */
    uint32_t          RESERVED4;                   /*!< Reserved register, offset: 0x30 */
    volatile uint32_t HRS;                         /*!< EDMA hardware request status register, offset: 0x34 */
    uint32_t          RESERVED5[50];               /*!< Reserved register, offset: 0x38 */
    volatile uint8_t  DCHPRI_N[EDMA_DCHPRI_COUNT]; /*!< EDMA channel N arbitration priority register, offset: 0x100 */
    uint32_t          RESERVED6[956];              /*!< Reserved register, offset: 0x110 */
    struct                                         
    {                                              
        volatile uint32_t SADDR;                   /*!< EDMA tcd source address register, offset: 0x1000 */
        volatile uint16_t SOFF;                    /*!< EDMA tcd signed source address offset register, offset: 0x1004 */
        volatile uint16_t ATTR;                    /*!< EDMA tcd transfer attributes register, offset: 0x1006 */
        volatile uint32_t NBYTES;                  /*!< EDMA tcd minor byte count register, offset: 0x1008 */
        volatile int32_t  SLAST;                   /*!< EDMA tcd last source address adjustment register, offset: 0x100C */
        volatile uint32_t DADDR;                   /*!< EDMA tcd destination address register, offset: 0x1010 */
        volatile uint16_t DOFF;                    /*!< EDMA tcd destination address signed offset register, offset: 0x1014 */
        volatile uint16_t CITER;                   /*!< EDMA tcd current minor loop link major loop link register, offset: 0x1016 */
        volatile int32_t  DLASTSGA;                /*!< EDMA last destination address adjustment/scatter gather address register, offset: 0x1018 */
        volatile uint16_t CSR;                     /*!< EDMA tcd control and status register, offset 0x101C */
        volatile uint16_t BITER;                   /*!< EDMA tcd current begining minor loop link, major loop count register, offset: 0x101E */
    } TCD[EDMA_TCD_COUNT];
} EDmaRegType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/
/*! \brief Get Debug mode
 *
 * \param[in] obj : pointer to eDMA register instance
 * \return debug mode
 *              -0b： when in debug mode, the DMA continues to operate
 *              -1b： when in debug mode, the DMA stalls the start of a new channel.
 */
__attribute__((always_inline)) static inline uint8_t EDmaReg_GetDebugMode(const EDmaRegType *obj)
{
    return ((obj->CR & EDMA_CR_EDBG_MASK) >> EDMA_CR_EDBG_SHIFT);
}

/*! \brief Set When in debug mode, the DMA stalls the start of a new channel.
 *
 * \param[in] obj : pointer to eDMA register instance
 */
__attribute__((always_inline)) static inline void EDmaReg_EnableDebugStall(EDmaRegType *obj)
{
    obj->CR |= EDMA_CR_EDBG_MASK;
}

/*! \brief Set When in debug mode,  the DMA continues to operate
 *
 * \param[in] obj : pointer to eDMA register instance
 */
__attribute__((always_inline)) static inline void EDmaReg_DisableDebugStall(EDmaRegType *obj)
{
    obj->CR &= ~EDMA_CR_EDBG_MASK;
}

/*! \brief Get the channel arbitration mode
 *
 * \param[in] obj base pointer to eDMA register instance
 * \return arbitration mode
 *                     - 0b： Fixed priority arbitration is used for channel selection
 *                     - 1b： Round-Robin arbitration is used for channel selection
 */
__attribute__((always_inline)) static inline uint8_t EDmaReg_GetChannelArbitrationMode(const EDmaRegType *obj)
{
    return ((obj->CR & EDMA_CR_ERCA_MASK) >> EDMA_CR_ERCA_SHIFT);
}

/*! \brief Sets the channel arbitration algorithm.
 *
 * \param[in] obj : pointer to eDMA register instance
 * \param[in] mode : Round-Robin(1) way or fixed(0) priority way.
 */
__attribute__((always_inline)) static inline void EDmaReg_SetChannelArbitrationMode(EDmaRegType *obj, uint8_t mode)
{
    if(mode)
    {
        obj->CR |= EDMA_CR_ERCA_MASK;
    }
    else
    {
        obj->CR &= ~EDMA_CR_ERCA_MASK;
    }
}

/*! \brief Get Halt on error
 *
 * \param[in] obj : pointer to eDMA register instance
 * \return halt on error mode
 *                  - 0： Normal operation
 *                  - 1： Any error causes the HALT bit to set.Subsequently,all service requests are ignored until the HALT bit is cleared.
 */
__attribute__((always_inline)) static inline uint8_t EDmaReg_GetHaltOnError(const EDmaRegType *obj)
{
    return ((obj->CR & EDMA_CR_HOE_MASK) >> EDMA_CR_HOE_SHIFT);
}

/*! \brief Halts or does not halt the eDMA module when an error occurs.
 *
 * An error causes the HALT bit to be set. Subsequently, all service requests are ignored until the
 * HALT bit is cleared.
 *
 * \param[in] base pointer to eDMA register instance
 * \param[in] enable Halts (true) or not halt (false) eDMA module when an error occurs.
 */
__attribute__((always_inline)) static inline void EDmaReg_SetHaltOnErrorCmd(EDmaRegType *obj, uint8_t enable)
{
    if(enable)
    {
        obj->CR |= EDMA_CR_HOE_MASK;
    }
    else
    {
        obj->CR &= ~EDMA_CR_HOE_MASK;
    }
}

/*! \brief Get Halt eDMA operations
 *
 * \param[in] obj ： pointer to eDMA register instance
 * \return    Halt eDMA operations
 *                      - 0b： normal operation
 *                      - 1b： stall the start of any new channels.Executing channels are allowed to complete.
 *                             Channel execution resumes when this bit is cleared
 */
__attribute__((always_inline)) static inline uint8_t EDmaReg_GetHalt(EDmaRegType *obj)
{
    return ((obj->CR & EDMA_CR_HALT_MASK) >> EDMA_CR_HALT_SHIFT);
}

/*! \brief Halts or does not halt the eDMA module .
 *
 * Execution channels are not allowed to complete, dma stop transfer at the end fo read-write sequence
 *
 * \param[in] obj : pointer to eDMA register instance
 * \param[in] enable : Halts (true) or not halt (false) eDMA module.
 */
__attribute__((always_inline)) static inline void EDmaReg_SetHaltCmd(EDmaRegType *obj, uint8_t enable)
{
    if(enable)
    {
        obj->CR |= EDMA_CR_HALT_MASK;
    }
    else
    {
        obj->CR &= ~EDMA_CR_HALT_MASK;
    }
}

/*! \brief Get continuous link mode
 *
 * \param[in] obj : pointer to eDMA register instance
 * \return continuous link mode
 *             - 0b： a minor loop channel link made to itself goes through channel arbitration before being activated again
 *             - 1b： a minor loop channel link made to itself does not go through channel arbitration before being activated again.
 */
__attribute__((always_inline)) static inline uint8_t EDmaReg_GetClm(const EDmaRegType *obj)
{
    return ((obj->CR & EDMA_CR_CLM_MASK) >> EDMA_CR_CLM_SHIFT);
}

/*! \brief Enable continuous link mode
 *
 * \param[in] obj : pointer to eDMA register instance
 */
__attribute__((always_inline)) static inline void EDmaReg_EnableClm(EDmaRegType *obj)
{
    obj->CR |= EDMA_CR_CLM_MASK;
}

/*! \brief Disable continuous link mode
 *
 * \param[in] obj : pointer to eDMA register instance
 */
__attribute__((always_inline)) static inline void EDmaReg_DisableClm(EDmaRegType *obj)
{
    obj->CR &= ~EDMA_CR_CLM_MASK;
}

/*! \brief Get Minor Loop Mapping
 *
 * \param[in] obj pointer to eDMA register instance
 * \return minor loop mapping mode
 *         - 0b： disable.
 *         - 1b： enabled
 */
__attribute__((always_inline)) static inline uint8_t EDmaReg_GetMinorLoopMapping(const EDmaRegType *obj)
{
    return ((obj->CR & EDMA_CR_EMLM_MASK) >> EDMA_CR_EMLM_SHIFT);
}

/*! \brief Enables/Disables the minor loop mapping.
 *
 * This function enables/disables the minor loop mapping feature.
 * If enabled, the NBYTES is redefined to include the individual enable fields and the NBYTES field. The
 * individual enable fields allow the minor loop offset to be applied to the source address, the
 * destination address, or both. The NBYTES field is reduced when either offset is enabled.
 *
 * \param[in] obj : pointer to eDMA register instance
 * \param[in] enable : Enables (true) or Disable (false) minor loop mapping.
 */
__attribute__((always_inline)) static inline void EDmaReg_SetMinorLoopMappingCmd(EDmaRegType *obj, uint8_t enable)
{
    if(enable)
    {
        obj->CR |= EDMA_CR_EMLM_MASK;
    }
    else
    {
        obj->CR &= ~EDMA_CR_EMLM_MASK;
    }
}

/*! \brief Get Error cancel transfer mode
 *
 * \param[in] obj : pointer to eDMA register instance
 * \return error cancel transfer mode
 *         - 0b： normal operation
 *         - 1b： cancel the remaining data transfer same as CX bit. Moreover, ECX treats the cancel as an error condition,
 *                thus updating the Error Status register (DMAx_ES) and generating an optional error interrupt.
 */
__attribute__((always_inline)) static inline uint8_t EDmaReg_GetEcx(const EDmaRegType *obj)
{
    return ((obj->CR & EDMA_CR_ECX_MASK) >> EDMA_CR_ECX_SHIFT);
}

/*! \brief  Cancels the remaining data transfer and treats it as an error condition.
 *
 * \param[in] obj : pointer to eDMA register instance
 */
__attribute__((always_inline)) static inline void EDmaReg_EnableEcx(EDmaRegType *obj)
{
    obj->CR |= EDMA_CR_ECX_MASK;
}

/*! \brief  Disable error cancel transfer
 *
 * \param[in] obj : pointer to eDMA register instance
 */
__attribute__((always_inline)) static inline void EDmaReg_DisableEcx(EDmaRegType *obj)
{
    obj->CR &= ~EDMA_CR_ECX_MASK;
}

/*! \brief Get Cancel transfer mode
 *
 * \param[in] obj : pointer to eDMA register instance
 * \return cancel transfer mode
 *              - 0b： normal operation
 *              - 1b： cancel the remaining data transfer. Stop the executing channel and force the minor loop to finish.
 *              The cancel takes effect after the last write of the current read/write sequence. The CX bit clears itself
 *              after the cancel has been honored. This cancel retires the channel normally as if the minor loop was completed. no error
 */
__attribute__((always_inline)) static inline uint8_t EDmaReg_GetCx(const EDmaRegType *obj)
{
    return ((obj->CR & EDMA_CR_CX_MASK) >> EDMA_CR_CX_SHIFT);
}

/*! \brief  Cancels the remaining data transfer.
 *
 * \param[in] obj : pointer to eDMA register instance
 */
__attribute__((always_inline)) static inline void EDmaReg_EnableCx(EDmaRegType *obj)
{
    obj->CR |= EDMA_CR_CX_MASK;
}

/*! \brief  Disable cancel transfer
 *
 * \param[in] obj : pointer to eDMA register instance
 */
__attribute__((always_inline)) static inline void EDmaReg_DisableCx(EDmaRegType *obj)
{
    obj->CR &= ~EDMA_CR_CX_MASK;
}

/*! \brief  EDMA active status
 *
 * \param[in] obj : pointer to eDMA register instance
 * \return dma active status
 *         - 0b： eDMA is idle
 *         - 1b： eDMA is excuting a channel
 */
__attribute__((always_inline)) static inline uint8_t EDmaReg_GetActiveStatus(const EDmaRegType *obj)
{
    return ((obj->CR & EDMA_CR_ACTIVE_MASK) >> EDMA_CR_ACTIVE_SHIFT);
}

/*! \brief Get destination bus error status
 *
 * \param[in] obj : pointer to eDMA register instance
 * \return destination bus error status
 *                  - 0b: No destination bus error
 *                  - 1b: The last recorded error was a bus error on a destination write
 */
__attribute__((always_inline)) static inline uint8_t EDmaReg_GetDbeStatus(const EDmaRegType *obj)
{
    return ((obj->ES & EDMA_ES_DBE_MASK) >> EDMA_ES_DBE_SHIFT);
}

/*! \brief Get source bus error status
 *
 * \param[in] obj : pointer to eDMA register instance
 * \return source bus error status
 *                  - 0b: No source bus error
 *                  - 1b: The last recorded error was a bus error on a source read
 */
__attribute__((always_inline)) static inline uint8_t EDmaReg_GetSbeStatus(const EDmaRegType *obj)
{
    return ((obj->ES & EDMA_ES_SBE_MASK) >> EDMA_ES_SBE_SHIFT);
}

/*! \brief Get Scatter/Gather configuration error
 *
 * \param[in] obj : pointer to eDMA register instance
 * \return Scatter/Gather configuration error status
 *                  - 0b: No scatter/gather configuration error
 *                  - 1b: The last recorded error was a configuration error detected in the TCDn_DLASTSGA field.
 *                  TCDn_DLASTSGA is not on a 32 bits boundary.
 */
__attribute__((always_inline)) static inline uint8_t EDmaReg_GetSgeStatus(const EDmaRegType *obj)
{
    return ((obj->ES & EDMA_ES_SGE_MASK) >> EDMA_ES_SGE_SHIFT);
}

/*! \brief Get NBYTES/CITER configuration Error
 *
 * \param[in] obj : pointer to eDMA register instance
 * \return NBYTES/CITER configuration error status
 *                 - 0b: No NBYTES/CITER configuration error
 *                 - 1b: The last recorded error was a configuration error detected in the TCDn_NBYTES or TCDn_CITER fields.
 *                 TCDn_NBYTES is not a multiple of TCDn_ATTR[SSIZE] and TCDn_ATTR[DSIZE], orTCDn_CITER[CITER] is equal to zero,
 *                 orTCDn_CITER[ELINK] is not equal to TCDn_BITER[ELINK]
 */
__attribute__((always_inline)) static inline uint8_t EDmaReg_GetNceStatus(const EDmaRegType *obj)
{
    return ((obj->ES & EDMA_ES_NCE_MASK) >> EDMA_ES_NCE_SHIFT);
}

/*! \brief Get destination offset error
 *
 * \param[in] obj : pointer to eDMA register instance
 * \return destination offset error status
 *                - 0b: No destination offset configuration error
 *                - 1b: The last recorded error was a configuration error detected in the TCDn_DOFF field.
 *                      TCDn_DOFF is inconsistent with TCDn_ATTR[SIZE].
 */
__attribute__((always_inline)) static inline uint8_t EDmaReg_GetDoeStatus(const EDmaRegType *obj)
{
    return ((obj->ES & EDMA_ES_DOE_MASK) >> EDMA_ES_DOE_SHIFT);
}

/*! \brief Get destination address error
 *
 * \param[in] obj : pointer to eDMA register instance
 * \return destination address error status
 *                - 0b: No destination address configuration error
 *                - 1b: The last recorded error was a configuration error detected in the TCDn_DADDR field.
 *                      TCDn_DADDR is inconsistent with TCDn_ATTR[SIZE]
 */
__attribute__((always_inline)) static inline uint8_t EDmaReg_GetDaeStatus(const EDmaRegType *obj)
{
    return ((obj->ES & EDMA_ES_DAE_MASK) >> EDMA_ES_DAE_SHIFT);
}

/*! \brief Get source offset error
 *
 * \param[in] obj : pointer to eDMA register instance
 * \return source offset error status
 *                - 0b: No source offset configuration error
 *                - 1b: The last recorded error was a configuration error detected in the TCDn_SOFF field.
 *                      TCDn_SOFF is inconsistent with TCDn_ATTR[SIZE].
 */
__attribute__((always_inline)) static inline uint8_t EDmaReg_GetSoeStatus(const EDmaRegType *obj)
{
    return ((obj->ES & EDMA_ES_SOE_MASK) >> EDMA_ES_SOE_SHIFT);
}

/*! \brief Get source address Error
 *
 * \param[in] obj : pointer to eDMA register instance
 * \return source address error status
 *                - 0b: No source address configuration error.
 *                - 1b: The last recorded error was a configuration error detected in the TCDn_SADDR field.
 *                TCDn_SADDR is inconsistent with TCDn_ATTR[SIZE].
 */
__attribute__((always_inline)) static inline uint8_t EDmaReg_GetSaeStatus(const EDmaRegType *obj)
{
    return ((obj->ES & EDMA_ES_SAE_MASK) >> EDMA_ES_SAE_SHIFT);
}

/*! \brief Get error channel number or canceled channel number
 *
 *  \param[in] obj : pointer to eDMA register instance
 *  \return  The channel number of the last recorded error, excluding CPE errors, or last recorded error canceled transfer
 */
__attribute__((always_inline)) static inline uint8_t EDmaReg_GetErrChn(const EDmaRegType *obj)
{
    return ((obj->ES & EDMA_ES_ERRCHN_MASK) >> EDMA_ES_ERRCHN_SHIFT);
}

/*! \brief Get channel priority error
 *
 * \param[in] obj : pointer to eDMA register instance
 * \return  channel priority error status
 *                - 0b: No channel priority error
 *                - 1b: The last recorded error was a configuration error in the channel priorities . Channel priorities are not unique.
 */
__attribute__((always_inline)) static inline uint8_t EDmaReg_GetCpeStatus(const EDmaRegType *obj)
{
    return ((obj->ES & EDMA_ES_CPE_MASK) >> EDMA_ES_CPE_SHIFT);
}

/*! \brief Get transfer Canceled status
 *
 * \param[in] obj : pointer to eDMA register instance
 * \return transfer canceled status
 *                - 0b: No canceled transfers
 *                - 1b: The last recorded entry was a canceled transfer by the error cancel transfer input
 */
__attribute__((always_inline)) static inline uint8_t EDmaReg_GetEcxStatus(const EDmaRegType *obj)
{
    return ((obj->ES & EDMA_ES_ECX_MASK) >> EDMA_ES_ECX_SHIFT);
}

/*! \brief Get logical OR of all error status bits
 *
 * \param[in] obj : pointer to eDMA register instance
 * \return logical OR of all error status bits
 *                - 0b: No ERR bits are set.
 *                - 1b: At least one ERR bit is set indicating a valid error exists that has not been cleared
 */
__attribute__((always_inline)) static inline uint8_t EDmaReg_GetVldStatus(const EDmaRegType *obj)
{
    return ((obj->ES & EDMA_ES_VLD_MASK) >> EDMA_ES_VLD_SHIFT);
}

/*! \brief Clear enable error interrupt register
 *
 * \param[in] obj : pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 */
__attribute__((always_inline)) static inline void EDmaReg_ClearEnableErrorInterrupt(EDmaRegType *obj, uint8_t value)
{
    uint32_t ceeiTmp = 0;
    ceeiTmp |= (((uint32_t)(((uint32_t)(value)) << EDMA_CEEI_CEEI_SHIFT)) & EDMA_CEEI_CEEI_MASK);
    obj->CEEI = ceeiTmp;
}

/*! \brief Clear all bits in EEI
 *
 * \param[in] obj ： pointer to eDMA register instance
 */
__attribute__((always_inline)) static inline void EDmaReg_EnableCaee(EDmaRegType *obj)
{
    uint32_t ceeiTmp = 0;
    ceeiTmp |= EDMA_CEEI_CAEE_MASK;
    obj->CEEI = ceeiTmp;
}

/*! \brief : Clear only the EEI bit specified in the CEEI field
 *
 * \param[in] obj ： pointer to eDMA register instance
 */
__attribute__((always_inline)) static inline void EDmaReg_DisableCaee(EDmaRegType *obj)
{
    uint32_t ceeiTmp = 0;
    ceeiTmp &= ~EDMA_CEEI_CAEE_MASK;
    obj->CEEI = ceeiTmp;
}

/*! \brief Set enable error interrupt register
 *
 * \param[in] obj : pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 */
__attribute__((always_inline)) static inline void EDmaReg_SetEnableErrorInterrupt(EDmaRegType *obj, uint8_t channel)
{
    uint8_t seeiTmp = 0;
    seeiTmp |= (((uint8_t)(((uint8_t)(channel)) << EDMA_SEEI_SEEI_SHIFT)) & EDMA_SEEI_SEEI_MASK);
    obj->SEEI = seeiTmp;
}

/*! \brief Sets all bits in EEI
 *
 * \param[in] obj ：pointer to eDMA register instance
 */
__attribute__((always_inline)) static inline void EDmaReg_EnableSaee(EDmaRegType *obj)
{
    uint8_t seeiTmp = 0;
    seeiTmp |= EDMA_SEEI_SAEE_MASK;
    obj->SEEI = seeiTmp;
}

/*! \brief Set only the EEI bit specified in the SEEI field.
 *
 * \param[in] obj ：pointer to eDMA register instance
 */
__attribute__((always_inline)) static inline void EDmaReg_DisableSaee(EDmaRegType *obj)
{
    uint8_t seeiTmp = 0;
    seeiTmp &= ~EDMA_SEEI_SAEE_MASK;
    obj->SEEI = seeiTmp;
}

/*! \brief Clear enable request register
 *
 * \param[in] obj : pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 */
__attribute__((always_inline)) static inline void EDmaReg_ClearEnableRequest(EDmaRegType *obj, uint8_t channel)
{
    uint8_t cerqTmp = 0;
    cerqTmp |= (((uint8_t)(((uint8_t)(channel)) << EDMA_CERQ_CERQ_SHIFT)) & EDMA_CERQ_CERQ_MASK);
    obj->CERQ = cerqTmp;
}

/*! \brief Clear only the ERQ bit specified in the CERQ field
 *
 * \param[in] obj ：pointer to eDMA register instance
 */
__attribute__((always_inline)) static inline void EDmaReg_EnableCaer(EDmaRegType *obj)
{
    uint8_t cerqTmp = 0;
    cerqTmp |= EDMA_CERQ_CAER_MASK;
    obj->CERQ = cerqTmp;
}

/*! \brief Clear all bits in ERQ
 *
 * \param[in] obj ：pointer to eDMA register instance
 */
__attribute__((always_inline)) static inline void EDmaReg_DisableCaer(EDmaRegType *obj)
{
    uint8_t cerqTmp = 0;
    cerqTmp &= ~EDMA_CERQ_CAER_MASK;
    obj->CERQ = cerqTmp;
}

/*! \brief Set enable request register
 *
 * \param[in] obj : pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 */
__attribute__((always_inline)) static inline void EDmaReg_SetEnableRequest(EDmaRegType *obj, uint8_t channel)
{
    uint32_t serqTmp = 0;
    serqTmp |= (((uint8_t)(((uint8_t)(channel)) << EDMA_SERQ_SERQ_SHIFT)) & EDMA_SERQ_SERQ_MASK);
    obj->SERQ = serqTmp;
}

/*! \brief Set all bits in ERQ
 *
 * \param[in] obj ：pointer to eDMA register instance
 */
__attribute__((always_inline)) static inline void EDmaReg_EnableSaer(EDmaRegType *obj)
{
    uint8_t serqTmp = 0;
    serqTmp |= EDMA_SERQ_SAER_MASK;
    obj->SERQ = serqTmp;
}

/*! \brief Set only the ERQ bit specified in the SERQ field
 *
 * \param[in] obj ：pointer to eDMA register instance
 */
__attribute__((always_inline)) static inline void EDmaReg_DisableSaer(EDmaRegType *obj)
{
    uint8_t serqTmp = 0;
    serqTmp &= ~EDMA_SERQ_SAER_MASK;
    obj->SERQ = serqTmp;
}

/*! \brief Clears the done status for a channel or all channels.
 *
 * \param[in] obj : pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 */
__attribute__((always_inline)) static inline void EDmaReg_ClearDoneStatusFlag(EDmaRegType *obj, uint8_t channel)
{
    uint8_t cdenTmp = 0;
    cdenTmp |= (((uint8_t)(((uint8_t)(channel)) << EDMA_CDNE_CDNE_SHIFT)) & EDMA_CDNE_CDNE_MASK);
    obj->CDNE = cdenTmp;
}

/*! \brief Clears all bits in TCDn_CSR[DONE]
 *
 * \param[in] obj ： pointer to eDMA register instance
 */
__attribute__((always_inline)) static inline void EDmaReg_EnableCadn(EDmaRegType *obj)
{
    uint8_t cdenTmp = 0;
    cdenTmp |= EDMA_CDNE_CDNE_MASK;
    obj->CDNE = cdenTmp;
}

/*! \brief  Clears only the TCDn_CSR[DONE] bit specified in the CDNE field
 *
 * \param[in] obj ： pointer to eDMA register instance
 */
__attribute__((always_inline)) static inline void EDmaReg_DisableCadn(EDmaRegType *obj)
{
    uint8_t cdenTmp = 0;
    cdenTmp &= ~EDMA_CDNE_CDNE_MASK;
    obj->CDNE = cdenTmp;
}

/*! \brief Set set START bit register
 *
 * \param[in] obj  pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 */
__attribute__((always_inline)) static inline void EDmaReg_SetChannelStartFlag(EDmaRegType *obj, uint8_t channel)
{
    uint8_t ssrtTmp = 0;
    ssrtTmp |= (((uint8_t)(((uint8_t)(channel)) << EDMA_SSRT_SSRT_SHIFT)) & EDMA_SSRT_SSRT_MASK);
    obj->SSRT = ssrtTmp;
}

/*! \brief Set all bits in TCDn_CSR[START]
 *
 * \param[in] obj ： pointer to eDMA register instance
 */
__attribute__((always_inline)) static inline void EDmaReg_EnableSast(EDmaRegType *obj)
{
    uint8_t ssrtTmp = 0;
    ssrtTmp |= EDMA_SSRT_SAST_MASK;
    obj->SSRT = ssrtTmp;
}
/*! \brief Set only the TCDn_CSR[START] bit specified in the SSRT field
 *
 * \param[in] obj ： pointer to eDMA register instance
 */
__attribute__((always_inline)) static inline void EDmaReg_DisableSast(EDmaRegType *obj)
{
    uint8_t ssrtTmp = 0;
    ssrtTmp &= ~EDMA_SSRT_SAST_MASK;
    obj->SSRT = ssrtTmp;
}

/*! \brief Clears the error status for the eDMA channel or channels.
 *
 * \param[in] obj : pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 */
__attribute__((always_inline)) static inline void EDmaReg_ClearErrorIntStatusFlag(EDmaRegType *obj, uint8_t channel)
{
    uint8_t cerrTmp = 0;
    cerrTmp |= (((uint8_t)(((uint8_t)(channel)) << EDMA_CERR_CERR_SHIFT)) & EDMA_CERR_CERR_MASK);
    obj->CERR = cerrTmp;
    /* Read back to avoid problem */
    (void)obj->CERR;
}

/*! \brief Clear all bits in ERR
 *
 * \param[in] obj ： pointer to eDMA register instance
 */
__attribute__((always_inline)) static inline void EDmaReg_EnableCaei(EDmaRegType *obj)
{
    uint8_t cerrTmp = 0;
    cerrTmp |= EDMA_CERR_CAEI_MASK;
    obj->CERR = cerrTmp;
}

/*! \brief Clear only the ERR bit specified in the CERR field
 *
 * \param[in] obj ： pointer to eDMA register instance
 */
__attribute__((always_inline)) static inline void EDmaReg_DisableCaei(EDmaRegType *obj)
{
    uint8_t cerrTmp = 0;
    cerrTmp &= ~EDMA_CERR_CAEI_MASK;
    obj->CERR = cerrTmp;
}

/*! \brief Clear interrupt register
 *
 * \param[in] obj : pointer to eDMA register instance
 * \param[in] channel ： eDMA channel number.
 */
__attribute__((always_inline)) static inline void EDmaReg_ClearIntStatusFlag(EDmaRegType *obj, uint8_t channel)
{
    uint8_t cintTmp = 0;
    cintTmp |= (((uint8_t)(((uint8_t)(channel)) << EDMA_CINT_CINT_SHIFT)) & EDMA_CINT_CINT_MASK);
    obj->CINT = cintTmp;
    /* Read back to avoid problem */
    (void)obj->CINT;
}

/*! \brief  Clear all bits in interrupt
 *
 * \param[in] obj ： pointer to eDMA register instance
 */
__attribute__((always_inline)) static inline void EDmaReg_EnableCair(EDmaRegType *obj)
{
    uint8_t cintTmp = 0;
    cintTmp |= EDMA_CINT_CAIR_MASK;
    obj->CINT = cintTmp;
}

/*! \brief Clear only the interrupt bit specified in the CINT field
 *
 * \param[in] obj ： pointer to eDMA register instance
 */
__attribute__((always_inline)) static inline void EDmaReg_DisableCair(EDmaRegType *obj)
{
    uint8_t cintTmp = 0;
    cintTmp &= ~EDMA_CINT_CAIR_MASK;
    obj->CINT = cintTmp;
}

/*! \brief Gets error status
 *
 * \param[in] obj ： pointer to eDMA register instance
 * \return 32 bit variable indicating error channels. If error happens on eDMA channel n, the bit n
 * of this variable is '1'. If not, the bit n of this variable is '0'.
 */
__attribute__((always_inline)) static inline uint32_t EDmaReg_GetErrorStatusFlag(const EDmaRegType *obj)
{
    return obj->ERR;
}

/*! \brief Gets channel error status
 *
 * \param[in] obj ： pointer to eDMA register instance
 * \param[in] channel ： eDMA channel number.
 * \return bool variable indicating error channels.
 */
__attribute__((always_inline)) static inline bool EDmaReg_GetChannelErrorStatusFlag(EDmaRegType *obj, const uint8_t channel)
{
    uint32_t errTmp = 0;
    errTmp = obj->ERR;
    return 1UL == ((errTmp >> channel) & EDMA_ERR_ERRN_MASK);
}

/*! \brief Sets the eDMA channel priority.
 *
 * \param[in] obj ： pointer to eDMA register instance
 * \param[in] channel ： eDMA channel number.
 * \param[in] value ： Priority of the DMA channel. Different channels should have different priority
 * setting inside a group.
 */
__attribute__((always_inline)) static inline void EDmaReg_SetChannelPriority(EDmaRegType *obj, const uint8_t channel, uint8_t value)
{
    uint32_t dchpriTmp = obj->DCHPRI_N[channel];

    dchpriTmp &= ~(EDMA_DCHPRI_CHPRI_MASK);
    dchpriTmp |= (((uint32_t)(((uint32_t)(value)) << EDMA_DCHPRI_CHPRI_SHIFT)) & EDMA_DCHPRI_CHPRI_MASK);
    obj->DCHPRI_N[channel] = dchpriTmp;
}

/*! \brief  Channel n can suspend a lower priority channel.
 *
 * \param[in] obj : pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 */
__attribute__((always_inline)) static inline void EDmaReg_EnablePreemptAbility(EDmaRegType *obj, const uint8_t channel)
{
    obj->DCHPRI_N[channel] &= ~EDMA_DCHPRI_DPA_MASK;
}

/*! \brief  Channel n cannot suspend any channel, regardless of channel
 *
 * \param[in] obj : pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 */
__attribute__((always_inline)) static inline void EDmaReg_DisablePreemptAbility(EDmaRegType *obj, const uint8_t channel)
{
    obj->DCHPRI_N[channel] |= EDMA_DCHPRI_DPA_MASK;
}

/*! \brief Channel n can be temporarilly suspended by the service request of a higher priority channel.
 *
 * \param[in] obj : pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 */
__attribute__((always_inline)) static inline void EDmaReg_EnableChannelPreemption(EDmaRegType *obj, const uint8_t channel)
{
    obj->DCHPRI_N[channel] |= EDMA_DCHPRI_ECP_MASK;
}

/*! \brief Channel n cannot be suspended by a higher priority channel's service request.
 *
 * \param[in] obj : pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 */
__attribute__((always_inline)) static inline void EDmaReg_DisableChannelPreemption(EDmaRegType *obj, const uint8_t channel)
{
    obj->DCHPRI_N[channel] &= ~EDMA_DCHPRI_ECP_MASK;
}

/*! \brief Configures the source address for the hardware TCD.
 *
 * \param[in] obj : pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 * \param[in] value : The pointer to the source memory address.
 */
__attribute__((always_inline)) static inline void EDmaReg_SetTcdSrcAddr(EDmaRegType *obj, const uint8_t channel, uint32_t value)
{
    obj->TCD[channel].SADDR = value;
}

/*! \brief Configures the source address signed offset for the hardware TCD.
 *
 * Sign-extended offset applied to the current source address to form the next-state value as each
 * source read is complete.
 *
 * \param[in] obj :  pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 * \param[in] value : signed-offset for source address.
 */
__attribute__((always_inline)) static inline void EDmaReg_SetTcdSrcOffset(EDmaRegType *obj, uint8_t channel, int16_t value)
{
    obj->TCD[channel].SOFF = (int16_t)value;
}

/*! \brief Sets the source/destination transfer size.
 *
 * Configures the source/destination data read transfer size (1/2/4/16/32 bytes).
 *
 * \param[in] obj : base pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 * \param[in] size : Source transfer size.
 */
__attribute__((always_inline)) static inline void EDmaReg_SetTcdSrcDesTransferSize(EDmaRegType *obj, uint8_t channel, uint8_t value)
{
    uint16_t attrTemp;
    attrTemp = obj->TCD[channel].ATTR;
    attrTemp &= (uint16_t)(~(EDMA_TCD_ATTR_SDSIZE_MASK));
    attrTemp |= (((uint16_t)(((uint16_t)(value)) << EDMA_TCD_ATTR_SDSIZE_SHIFT)) & EDMA_TCD_ATTR_SDSIZE_MASK);
    obj->TCD[channel].ATTR = attrTemp;
}

/*! \brief Set the destination address modulo.
 *
 * 00000b: destination address modulo feature is disabled
 * 00001~11111b: This value defnies a specific address range specified to be the value after SADDR + SOFF
 * calculation is performed on the original register value. Setting this field provides the ability to implement
 * a circular data queue easily. For data queues requiring power-of-2 size bytes, the queue should start
 * at a 0-modulo-size address and the SMOD field should be set to the appropriate value for the queue, freezing
 * the desired number of upper address bits. The value programmed into this field specifieds the number of lower
 * bits alllowed to change. For a cicular queue application, the SOFF is typically set to the transfer size to
 * implement post-increment addressing with the SMOD funciton constraining the addresses to a 0-modulo-size range.
 *
 * \param[in] obj : base pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 * \param[in] value : address modulo.
 */
__attribute__((always_inline)) static inline void EDmaReg_SetTcdDmod(EDmaRegType *obj, uint8_t channel, uint8_t value)
{
    uint16_t attrTemp;
    attrTemp = obj->TCD[channel].ATTR;
    attrTemp &= (uint16_t)(~(EDMA_TCD_ATTR_DMOD_MASK));
    attrTemp |= (((uint16_t)(((uint16_t)(value)) << EDMA_TCD_ATTR_DMOD_SHIFT)) & EDMA_TCD_ATTR_DMOD_MASK);
    obj->TCD[channel].ATTR = attrTemp;
}

/*! \brief Set the source address modulo.
 *
 * 00000b: Source address modulo feature is disabled
 * 00001~11111b: This value defnies a specific address range specified to be the value after SADDR + SOFF
 * calculation is performed on the original register value. Setting thsi field provides the ability to implement
 * a circular data queue easily. For data queues requiring power-of-2 size bytes, the queue should start
 * at a 0-modulo-size address and the SMOD field should be set to the appropriate value for the queue, freezing
 * the desired number of upper address bits. The value programmed into this field specifieds the number of lower
 * bits alllowed to change. For a cicular queue application, the SOFF is typically set to the transfer size to
 * implement post-increment addressing with the SMOD funciton constraining the addresses to a 0-modulo-size range.
 *
 * \param[in] obj : base pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 * \param[in] value : Source transfer size.
 */
__attribute__((always_inline)) static inline void EDmaReg_SetTcdSmod(EDmaRegType *obj, uint8_t channel, uint8_t value)
{
    uint16_t attrTemp;
    attrTemp = obj->TCD[channel].ATTR;
    attrTemp &= (uint16_t)(~(EDMA_TCD_ATTR_SMOD_MASK));
    attrTemp |= (((uint16_t)(((uint16_t)(value)) << EDMA_TCD_ATTR_SMOD_SHIFT)) & EDMA_TCD_ATTR_SMOD_MASK);
    obj->TCD[channel].ATTR = attrTemp;
}

/*! \brief Configures the nbytes for the eDMA channel.
 *
 *
 * Note here that user need firstly configure the minor loop mapping feature and then call this
 * function.
 *
 * \param[in] obj : pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 * \param[in] value : Number of bytes to be transferred in each service request of the channel
 */
__attribute__((always_inline)) static inline void EDmaReg_SetTcdNbytes(EDmaRegType *obj, uint8_t channel, uint32_t value)
{
    if(((obj->CR & EDMA_CR_EMLM_MASK) >> EDMA_CR_EMLM_SHIFT) != 0UL)
    {
        bool mlOffNo = false;
        if(((obj->TCD[channel].NBYTES & EDMA_TCD_NBYTES_MLOFFNO_SMLOE_MASK) >> EDMA_TCD_NBYTES_MLOFFNO_SMLOE_SHIFT) == 0UL)
        {
            if(((obj->TCD[channel].NBYTES & EDMA_TCD_NBYTES_MLOFFNO_DMLOE_MASK) >> EDMA_TCD_NBYTES_MLOFFNO_DMLOE_SHIFT) == 0UL)
            {
                obj->TCD[channel].NBYTES = (value & EDMA_TCD_NBYTES_MLOFFNO_NBYTES_MASK);
                mlOffNo                   = true;
            }
        }
        if(!mlOffNo)
        {
            uint32_t regValTemp;
            regValTemp = obj->TCD[channel].NBYTES;
            regValTemp &= ~(EDMA_TCD_NBYTES_MLOFFYES_NBYTES_MASK);
            regValTemp
                |= (((uint16_t)(((uint16_t)(value)) << EDMA_TCD_NBYTES_MLOFFYES_NBYTES_SHIFT)) & EDMA_TCD_NBYTES_MLOFFYES_NBYTES_MASK);
            obj->TCD[channel].NBYTES = regValTemp;
        }
    }
    else
    {
        obj->TCD[channel].NBYTES = value;
    }
}

/*! \brief Enables/disables the source minor loop offset feature for the TCD.
 *
 * Configures whether the minor loop offset is applied to the source address
 * upon minor loop completion.
 * NOTE: EMLM bit needs to be enabled prior to calling this function, otherwise
 * it has no effect.
 *
 * \param[in] obj : pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 * \param[in] enable : Enables (true) or disables (false) source minor loop offset.
 */
__attribute__((always_inline)) static inline void EDmaReg_SetTcdSrcMinorLoopOffsetCmd(EDmaRegType *obj, uint8_t channel, bool enable)
{
    if(((obj->CR >> EDMA_CR_EMLM_SHIFT) & 1U) != 0U)
    {
        if(enable)
        {
            obj->TCD[channel].NBYTES |= EDMA_TCD_NBYTES_MLOFFYES_SMLOE_MASK;
        }
        else
        {
            obj->TCD[channel].NBYTES &= ~EDMA_TCD_NBYTES_MLOFFYES_SMLOE_MASK;
        }
    }
}

/*! \brief Enables/disables the destination minor loop offset feature for the TCD.
 *
 * Configures whether the minor loop offset is applied to the destination address
 * upon minor loop completion.
 * NOTE: EMLM bit needs to be enabled prior to calling this function, otherwise
 * it has no effect.
 *
 * \param[in] obj : pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 * \param[in] enable : Enables (true) or disables (false) destination minor loop offset.
 */
__attribute__((always_inline)) static inline void EDmaReg_SetTcdDestMinorLoopOffsetCmd(EDmaRegType *obj, uint8_t channel, bool enable)
{
    if(((obj->CR >> EDMA_CR_EMLM_SHIFT) & 1U) != 0U)
    {
        if(enable)
        {
            obj->TCD[channel].NBYTES |= EDMA_TCD_NBYTES_MLOFFYES_DMLOE_MASK;
        }
        else
        {
            obj->TCD[channel].NBYTES &= ~EDMA_TCD_NBYTES_MLOFFYES_DMLOE_MASK;
        }
    }
}

/*! \brief Configures the minor loop offset for the TCD.
 *
 * Configures the offset value. If neither source nor destination offset is enabled,
 * offset is not configured.
 * NOTE: EMLM bit needs to be enabled prior to calling this function, otherwise
 * it has no effect.
 *
 * \param[in] obj : pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 * \param[in] offset : Minor loop offset
 */
__attribute__((always_inline)) static inline void EDmaReg_SetTcdMinorLoopOffset(EDmaRegType *obj, uint8_t channel, int32_t offset)
{
    if(((obj->CR & EDMA_CR_EMLM_MASK) >> EDMA_CR_EMLM_SHIFT) != 0UL)
    {
        bool mlOffNo = false;
        if(((obj->TCD[channel].NBYTES & EDMA_TCD_NBYTES_MLOFFNO_SMLOE_MASK) >> EDMA_TCD_NBYTES_MLOFFNO_SMLOE_SHIFT) != 0UL)
        {
            mlOffNo = true;
        }
        if(((obj->TCD[channel].NBYTES & EDMA_TCD_NBYTES_MLOFFNO_DMLOE_MASK) >> EDMA_TCD_NBYTES_MLOFFNO_DMLOE_SHIFT) != 0UL)
        {
            mlOffNo = true;
        }
        if(mlOffNo)
        {
            uint32_t regValTemp;
            regValTemp = obj->TCD[channel].NBYTES;
            regValTemp &= ~(EDMA_TCD_NBYTES_MLOFFYES_MLOFF_MASK);
            regValTemp
                |= (((uint32_t)(((uint32_t)(offset)) << EDMA_TCD_NBYTES_MLOFFYES_MLOFF_SHIFT)) & EDMA_TCD_NBYTES_MLOFFYES_MLOFF_MASK);
            obj->TCD[channel].NBYTES = regValTemp;
        }
    }
}

/*! \brief Configures the last source address adjustment for the TCD.
 *
 * Adjustment value added to the source address at the completion of the major iteration count. This
 * value can be applied to restore the source address to the initial value, or adjust the address to
 * reference the next data structure.
 *
 * \param[in] obj : pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 * \param[in] value : adjustment value
 */
__attribute__((always_inline)) static inline void EDmaReg_SetTcdSrcLastAdjust(EDmaRegType *obj, uint8_t channel, int32_t value)
{
    obj->TCD[channel].SLAST = value;
}

/*! \brief Configures the destination address for the TCD.
 *
 * \param[in] obj : pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 * \param[in] value : The pointer to the destination address.
 */
__attribute__((always_inline)) static inline void EDmaReg_SetTcdDestAddr(EDmaRegType *obj, uint8_t channel, uint32_t value)
{
    obj->TCD[channel].DADDR = value;
}

/*! \brief Configures the destination address signed offset for the TCD.
 *
 * Sign-extended offset applied to the current source address to form the next-state value as each
 * destination write is complete.
 *
 * \param[in] obj : pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 * \param[in] value : signed-offset
 */
__attribute__((always_inline)) static inline void EDmaReg_SetTcdDestOffset(EDmaRegType *obj, uint8_t channel, int16_t value)
{
    obj->TCD[channel].DOFF = (uint16_t)value;
}

/*! \brief Enable/Disables channel-to-channel linking on minor-loop complete.
 *
 * As the channel completes the minor loop,this flag enables linking to another channel, defined by the
 * LINKC field. THe link target channel initiates a channel service request via an internal mechanism
 * that sets the TCDn_CSR[START]bit of the specified channel.
 * If channel linking is disabled, the CITER value is extended to 15 bits in place of a link channel number.
 * If the major loop is exhausted, this link mechanism is suppressed in favor of the MAJORELINK channel linking.
 *
   NOTE: this bit must be equal to the BITER[ELINK] bit;oterwise, a configuration error is reported.
 * \param[in] obj : pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 * \param[in] enable : Enables (true) or disables (false) signed-offset
 */
__attribute__((always_inline)) static inline void EDmaReg_SetTcdCiterMinorLinkCmd(EDmaRegType *obj, uint8_t channel, uint8_t enable)
{
    if(enable)
    {
        obj->TCD[channel].CITER |= EDMA_TCD_CITER_ELINKYES_ELINK_MASK;
    }
    else
    {
        obj->TCD[channel].CITER &= ~EDMA_TCD_CITER_ELINKYES_ELINK_MASK;
    }
}

/*! \brief Configures the minor loop link channel number.
 *
 * If channel-to-channel linking is enabled(ELINK = 1),then after the minor loop is exhausted.
 * \param[in] obj : pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 * \param[in] value : channel number for minor link
 */
__attribute__((always_inline)) static inline void EDmaReg_SetTcdCiterMinorLinkChannel(EDmaRegType *obj, uint8_t channel, uint8_t value)
{
    uint16_t citerElinkTemp;
    citerElinkTemp = obj->TCD[channel].CITER;
    citerElinkTemp &= (uint16_t) ~(EDMA_TCD_CITER_ELINKYES_LINKCH_MASK);
    citerElinkTemp |= (((uint16_t)(((uint16_t)(value)) << EDMA_TCD_CITER_ELINKYES_LINKCH_SHIFT)) & EDMA_TCD_CITER_ELINKYES_LINKCH_MASK);
    obj->TCD[channel].CITER = citerElinkTemp;
}

/*! \brief Configures the major loop count for the channel.
 *
 * It is decremented each time the minor loop is completed and updated in the transfer control descriptor
 * memory. After the major iteration count is exhausted, the channel performs a number of operations, for
 * example,final source and destination address calculations, optionally generating an interrupt to signal
 * channel completion before reloading the CITER field from the Beginning iteration Count(BITER)field.
 *
 *  NOTE: When the CITER field is initially loaded by software, it must be set to the same value as that
 * contained in the BITER field. if the channel is configured to execute a single service request. the
 * initial values of BITER and CITER should be 0x0001.
 *
 * \param[in] obj : pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 * \param[in] value : channel number for minor link
 */
__attribute__((always_inline)) static inline void EDmaReg_SetTcdMajorCount(EDmaRegType *obj, uint8_t channel, uint16_t count)
{
    uint16_t regValTemp = 0;
    if((obj->TCD[channel].BITER & EDMA_TCD_BITER_ELINKNO_ELINK_MASK) == EDMA_TCD_BITER_ELINKNO_ELINK_MASK)
    {
        regValTemp = obj->TCD[channel].BITER;
        regValTemp &= (uint16_t) ~(EDMA_TCD_BITER_ELINKYES_BITER_MASK);
        regValTemp |= (((uint16_t)(((uint16_t)(count)) << EDMA_TCD_BITER_ELINKYES_BITER_SHIFT)) & EDMA_TCD_BITER_ELINKYES_BITER_MASK);
        obj->TCD[channel].BITER = regValTemp;

        regValTemp = obj->TCD[channel].CITER;
        regValTemp &= (uint16_t) ~(EDMA_TCD_CITER_ELINKYES_CITER_MASK);
        regValTemp |= (((uint16_t)(((uint16_t)(count)) << EDMA_TCD_CITER_ELINKYES_CITER_SHIFT)) & EDMA_TCD_CITER_ELINKYES_CITER_MASK);
        obj->TCD[channel].CITER = regValTemp;
    }
    else
    {
        regValTemp = obj->TCD[channel].BITER;
        regValTemp &= (uint16_t) ~(EDMA_TCD_BITER_ELINKNO_BITER_MASK);
        regValTemp |= (((uint16_t)(((uint16_t)(count)) << EDMA_TCD_BITER_ELINKNO_BITER_SHIFT)) & EDMA_TCD_BITER_ELINKNO_BITER_MASK);
        obj->TCD[channel].BITER = regValTemp;

        regValTemp = obj->TCD[channel].CITER;
        regValTemp &= (uint16_t) ~(EDMA_TCD_CITER_ELINKNO_CITER_MASK);
        regValTemp |= (((uint16_t)(((uint16_t)(count)) << EDMA_TCD_CITER_ELINKNO_CITER_SHIFT)) & EDMA_TCD_CITER_ELINKNO_CITER_MASK);
        obj->TCD[channel].CITER = regValTemp;
    }
}

/*! \brief Returns the current major iteration count.
 *
 * Gets the current major iteration count according to minor loop channel link settings.
 *
 * \param[in] obj : pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 * \return current : iteration count
 */
__attribute__((always_inline)) static inline uint32_t EDmaReg_GetTcdCurrentMajorCount(const EDmaRegType *obj, uint8_t channel)
{
    uint16_t result = 0U;
    if((obj->TCD[channel].BITER & EDMA_TCD_BITER_ELINKNO_ELINK_MASK) == EDMA_TCD_BITER_ELINKNO_ELINK_MASK)
    {
        result = (uint16_t)((obj->TCD[channel].CITER & EDMA_TCD_CITER_ELINKYES_CITER_MASK) >> EDMA_TCD_CITER_ELINKYES_CITER_SHIFT);
    }
    else
    {
        result = (uint16_t)((obj->TCD[channel].CITER & EDMA_TCD_CITER_ELINKNO_CITER_MASK) >> EDMA_TCD_CITER_ELINKNO_CITER_SHIFT);
    }
    return (uint32_t)result;
}

/*! \brief Configures the last source address adjustment.
 *
 * This function adds an adjustment value added to the source address at the completion of the major
 * iteration count. This value can be applied to restore the source address to the initial value, or
 * adjust the address to reference the next data structure.
 *
 * \param[in] obj : pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 * \param[in] value : adjustment value
 */
__attribute__((always_inline)) static inline void EDmaReg_SetTcdDestLastAdjust(EDmaRegType *obj, uint8_t channel, int32_t value)
{
    obj->TCD[channel].DLASTSGA = value;
}

/*! \brief Configures the memory address of the next TCD, in Scatter/Gather mode.
 *
 * This address points to the beginning of a 0-modulo-32-byte region containing the next transfer control
 * descriptor to be loaded into this channel. This channel reload is performed as the major iteration
 * count completes. The scatter/gather address must be 0-modulo-32-byte, oterwise a configuration error
 * is reported.
 *
 * \param[in] obj : pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 * \param[in] value : next tcd address
 */
__attribute__((always_inline)) static inline void EDmaReg_SetTcdScatterGatherLink(EDmaRegType *obj, uint8_t channel, int32_t value)
{
    obj->TCD[channel].DLASTSGA = value;
}

/*! \brief  Channel Start
 *
 * \param[in] obj : pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 * \param[in] enable : Enable (true) /Disable (false) interrupt after TCD done.
 */
__attribute__((always_inline)) static inline void EDmaReg_SetTcdStartCmd(EDmaRegType *obj, uint8_t channel, uint8_t enable)
{
    if(enable)
    {
        obj->TCD[channel].CSR |= EDMA_TCD_CSR_START_MASK;
    }
    else
    {
        obj->TCD[channel].CSR &= ~EDMA_TCD_CSR_START_MASK;
    }
}

/*! \brief Enables/Disables the interrupt after the major loop completes for the TCD.
 *
 * If enabled, the channel generates an interrupt request by setting the appropriate bit in the
 * interrupt register when the current major iteration count reaches zero.
 *
 * \param[in] obj : pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 * \param[in] enable : Enable (true) /Disable (false) interrupt after TCD done.
 */
__attribute__((always_inline)) static inline void EDmaReg_SetTcdMajorCompleteIntCmd(EDmaRegType *obj, uint8_t channel, uint8_t enable)
{
    if(enable)
    {
        obj->TCD[channel].CSR |= EDMA_TCD_CSR_INTMAJOR_MASK;
    }
    else
    {
        obj->TCD[channel].CSR &= ~EDMA_TCD_CSR_INTMAJOR_MASK;
    }
}

/*! \brief Enables/Disables the half complete interrupt for the TCD.
 *
 * If set, the channel generates an interrupt request by setting the appropriate bit in the
 * interrupt register when the current major iteration count reaches the halfway point. Specifically,
 * the comparison performed by the eDMA engine is (CITER == (BITER >> 1)). This half-way point
 * interrupt request is provided to support the double-buffered schemes or other types of data movement
 * where the processor needs an early indication of the transfer's process.
 *
 * \param[in] obj : pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 * \param[in] enable : Enable (true) /Disable (false) half complete interrupt.
 */
__attribute__((always_inline)) static inline void EDmaReg_SetTcdMajorHalfCompleteIntCmd(EDmaRegType *obj, uint8_t channel, uint8_t enable)
{
    if(enable)
    {
        obj->TCD[channel].CSR |= EDMA_TCD_CSR_INTHALF_MASK;
    }
    else
    {
        obj->TCD[channel].CSR &= ~EDMA_TCD_CSR_INTHALF_MASK;
    }
}

/*! \brief Disables/Enables the DMA request after the major loop completes for the TCD.
 *
 * If disabled, the eDMA hardware automatically clears the corresponding DMA request when the
 * current major iteration count reaches zero.
 *
 * \param[in] obj : pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 * \param[in] enable : Disable (true)/Enable (false) DMA request after TCD complete.
 */
__attribute__((always_inline)) static inline void EDmaReg_SetTcdDisableDmaRequestAfterTcdDoneCmd(EDmaRegType *obj, uint8_t channel, uint8_t disable)
{
    if(disable)
    {
        obj->TCD[channel].CSR |= EDMA_TCD_CSR_DREQ_MASK;
    }
    else
    {
        obj->TCD[channel].CSR &= ~EDMA_TCD_CSR_DREQ_MASK;
    }
}

/*! \brief Enables/Disables the scatter/gather feature for the TCD.
 *
 * \param[in] obj : base pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 * \param[in] enable : Enables (true) /Disables (false) scatter/gather feature.
 */
__attribute__((always_inline)) static inline void EDmaReg_SetTcdScatterGatherCmd(EDmaRegType *obj, uint8_t channel, uint8_t enable)
{
    if(enable)
    {
        obj->TCD[channel].CSR |= EDMA_TCD_CSR_ESG_MASK;
    }
    else
    {
        obj->TCD[channel].CSR &= ~EDMA_TCD_CSR_ESG_MASK;
    }
}

/*! \brief Configures the major channel link the TCD.
 *
 * If the major link is enabled, after the major loop counter is exhausted, the eDMA engine initiates a
 * channel service request at the channel defined by these six bits by setting that channel start
 * bits.
 *
 * \param[in] obj : pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 * \param[in] enable : Enables (true) or Disables (false) channel major link.
 */
__attribute__((always_inline)) static inline void EDmaReg_SetTcdChannelMajorLinkCmd(EDmaRegType *obj, uint8_t channel, uint8_t enable)
{
    if(enable)
    {
        obj->TCD[channel].CSR |= EDMA_TCD_CSR_MAJORELINK_MASK;
    }
    else
    {
        obj->TCD[channel].CSR &= ~EDMA_TCD_CSR_MAJORELINK_MASK;
    }
}

/*! \brief This flag signals the channel is currently in execution
 *
 * \param[in] obj : pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 *
 */
__attribute__((always_inline)) static inline uint8_t EDmaReg_GetTcdChannelActiveStatus(EDmaRegType *obj, uint8_t channel)
{
    return ((obj->TCD[channel].CSR & EDMA_TCD_CSR_ACTIVE_MASK) >> EDMA_TCD_CSR_ACTIVE_SHIFT);
}

/*! \brief This flag signals the eDMA has completed the major loop.
 *
 * The eDMA engine sets it as the CITER count reaches zero.The software clears it, orthe hardware when the
 * channel is activated. This bit must be cleared to write the MAJORELINK or ESG bits.
 *
 * \param[in] obj : pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 */
__attribute__((always_inline)) static inline uint8_t EDmaReg_GetTcdChannelDoneStatus(EDmaRegType *obj, uint8_t channel)
{
    return ((obj->TCD[channel].CSR & EDMA_TCD_CSR_DONE_MASK) >> EDMA_TCD_CSR_DONE_SHIFT);
}

/*! \brief Configures the major channel link the TCD.
 *
 * If the major link is enabled, after the major loop counter is exhausted, the eDMA engine initiates a
 * channel service request at the channel defined by these field by setting that channel's TCDn_CSR[MAJORELINK]
 * bit.
 *
 * \param[in] obj : pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 * \param[in] majorLinkChannel : channel number for major link
 * \param[in] enable : Enables (true) or Disables (false) channel major link.
 */
__attribute__((always_inline)) static inline void EDmaReg_SetTcdMajorLinkChannel(EDmaRegType *obj, uint8_t channel, uint8_t value)
{
    uint16_t csrTemp;
    csrTemp = obj->TCD[channel].CSR;
    csrTemp &= (uint16_t) ~(EDMA_TCD_CSR_MAJORLINKCH_MASK);
    csrTemp |= (((uint16_t)(((uint16_t)(value)) << EDMA_TCD_CSR_MAJORLINKCH_SHIFT)) & EDMA_TCD_CSR_MAJORLINKCH_MASK);
    ;
    obj->TCD[channel].CSR = csrTemp;
}

/*! \brief Get Hardware clear Done automatically
 *
 * \param[in] obj: pointer to eDMA register instance
 * \param[in] channel: eDMA channel number.
 * \param[in] enable: Enables (true) or Disables (false) would clear Done automatically.
 *                      0:hardware would not clear Done automatically
 *                      1:hardware would clear Done automatically
 */
__attribute__((always_inline)) static inline void EDmaReg_SetTcdHardClrDoneCmd(EDmaRegType *obj, uint8_t channel, uint8_t enable)
{
    if(enable)
    {
        obj->TCD[channel].CSR |= EDMA_TCD_CSR_HARD_CLR_DONE_MASK;
    }
    else
    {
        obj->TCD[channel].CSR &= ~EDMA_TCD_CSR_HARD_CLR_DONE_MASK;
    }
}

/*! \brief Get Hardware clear Done automatically
 *
 * \param[in] obj: pointer to eDMA register instance
 * \param[in] channel: eDMA channel number.
 * \return   0:hardware would not clear Done automatically
 *           1:hardware would clear Done automatically
 */
__attribute__((always_inline)) static inline uint8_t EDmaReg_getTcdHardClrDone(EDmaRegType *obj, uint8_t channel)
{
    return ((obj->TCD[channel].CSR & EDMA_TCD_CSR_HARD_CLR_DONE_MASK) >> EDMA_TCD_CSR_HARD_CLR_DONE_SHIFT);
}

/*! \brief Sets the channel minor link for the TCD.
 *
 * \param[in] obj: pointer to eDMA register instance
 * \param[in] channel: eDMA channel number.
 * \param[in] enable: Channel to be linked on minor loop complete.
 */
__attribute__((always_inline)) static inline void EDmaReg_SetTcdBiterMinorLinkChannel(EDmaRegType *obj, uint8_t channel, uint8_t value)
{
    uint16_t biterElinkTemp;
    biterElinkTemp = obj->TCD[channel].BITER;
    biterElinkTemp &= (uint16_t) ~(EDMA_TCD_BITER_ELINKYES_LINKCH_MASK);
    biterElinkTemp |= (((uint16_t)(((uint16_t)(value)) << EDMA_TCD_BITER_ELINKYES_LINKCH_SHIFT)) & EDMA_TCD_BITER_ELINKYES_LINKCH_MASK);
    obj->TCD[channel].BITER = biterElinkTemp;
}

/*! \brief Configures the minor channel link the TCD.
 *
 * If the major link is enabled, after the major loop counter is exhausted, the eDMA engine initiates a
 * channel service request at the channel defined by these six bits by setting that channel start
 * bits.
 *
 * \param[in] obj: pointer to eDMA register instance
 * \param[in] channel: eDMA channel number.
 * \param[in] enable: Enables (true) or Disables (false) channel major link.
 */
__attribute__((always_inline)) static inline void EDmaReg_SetTcdBiterMinorLinkCmd(EDmaRegType *obj, uint8_t channel, uint8_t enable)
{
    if(enable)
    {
        obj->TCD[channel].BITER |= EDMA_TCD_BITER_ELINKYES_ELINK_MASK;
    }
    else
    {
        obj->TCD[channel].BITER &= ~EDMA_TCD_BITER_ELINKYES_ELINK_MASK;
    }
}

/*! \brief Cancels the remaining data transfer.
 *
 * This function stops the executing channel and forces the minor loop
 * to finish. The cancellation takes effect after the last write of the
 * current read/write sequence. The CX clears itself after the cancel has
 * been honored. This cancel retires the channel normally as if the minor
 * loop had completed.
 *
 * \param[in] obj: pointer to eDMA register instance
 */
__attribute__((always_inline)) static inline void EDmaReg_CancelTransfer(EDmaRegType *obj)
{
    EDmaReg_EnableCx(obj);
    while(EDmaReg_GetCx(obj) != 0UL)
    {
    }
}

/*! \brief Cancels the remaining data transfer and treats it as an error condition.
 *
 * This function stops the executing channel and forces the minor loop
 * to finish. The cancellation takes effect after the last write of the
 * current read/write sequence. The CX clears itself after the cancel has
 * been honoured. This cancel retires the channel normally as if the minor
 * loop had completed. Additional thing is to treat this operation as an error
 * condition.
 *
 * \param[in] obj: pointer to eDMA register instance
 */
__attribute__((always_inline)) static inline void EDmaReg_CancelTransferWithError(EDmaRegType *obj)
{
    EDmaReg_EnableEcx(obj);
    while(EDmaReg_GetEcx(obj) != 0UL)
    {
    }
}

/*! \brief Enables/Disables the error interrupt for channels.
 *
 * \param[in] obj: base pointer to eDMA register instance
 * \param[in] channel: Channel indicator.
 * \param[in] enable : Enable(true) or Disable (false) error interrupt.
 */
__attribute__((always_inline)) static inline void EDmaReg_SetErrorIntCmd(EDmaRegType *obj, uint8_t channel, bool enable)
{
    if(enable)
    {
        EDmaReg_SetEnableErrorInterrupt(obj, channel);
    }
    else
    {
        EDmaReg_ClearEnableErrorInterrupt(obj, channel);
    }
}

/*! \brief Enables/Disables the DMA request for the channel or all channels.
 *
 * \param[in] obj : pointer to eDMA register instance
 * \param[in] enable : Enable(true) or Disable (false) eDMA request.
 * \param[in] channel : Channel indicator.
 */
__attribute__((always_inline)) static inline void EDmaReg_SetDmaRequestCmd(EDmaRegType *obj, uint8_t channel, bool enable)
{
    if(enable)
    {
        EDmaReg_SetEnableRequest(obj, channel);
    }
    else
    {
        EDmaReg_ClearEnableRequest(obj, channel);
    }
}

/*! \brief Clears all registers to 0 for the hardware TCD.
 *
 * \param[in] obj : pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 */
__attribute__((always_inline)) static inline void EDmaReg_ClearTcdReg(EDmaRegType *obj, uint8_t channel)
{
    obj->TCD[channel].NBYTES   = 0U;
    obj->TCD[channel].SADDR    = 0U;
    obj->TCD[channel].SOFF     = 0;
    obj->TCD[channel].ATTR     = 0U;
    obj->TCD[channel].SLAST    = 0;
    obj->TCD[channel].DADDR    = 0U;
    obj->TCD[channel].DOFF     = 0;
    obj->TCD[channel].CITER    = 1U;
    obj->TCD[channel].DLASTSGA = 0;
    obj->TCD[channel].CSR      = 0U;
    obj->TCD[channel].BITER    = 1U;
}

/*! \brief Configures the transfer attribute for the eDMA channel.
 *
 * \param[in] obj : pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 * \param[in] srcModulo : enumeration type for an allowed source modulo. The value defines a specific address range
 * specified as the value after the SADDR + SOFF calculation is performed on the original register
 * value. Setting this field provides the ability to implement a circular data. For data queues
 * requiring power-of-2 size bytes, the queue should start at a 0-modulo-size address and the SMOD
 * field should be set to the appropriate value for the queue, freezing the desired number of upper
 * address bits. The value programmed into this field specifies the number of the lower address bits
 * allowed to change. For a circular queue application, the SOFF is typically set to the transfer
 * size to implement post-increment addressing with SMOD function restricting the addresses to a
 * 0-modulo-size range.
 * \param[in] destModulo : Enum type for an allowed destination modulo.
 * \param[in] transferSize : Enum type for source/destination transfer size.
 */
__attribute__((always_inline)) static inline void EDmaReg_SetTcdAttribute(EDmaRegType *obj, uint8_t channel, uint8_t srcModulo, uint8_t destModulo, uint8_t transferSize)
{
    EDmaReg_SetTcdDmod(obj, channel, destModulo);
    EDmaReg_SetTcdSmod(obj, channel, srcModulo);
    EDmaReg_SetTcdSrcDesTransferSize(obj, channel, transferSize);
}

/*! \brief Configures the major channel link the TCD.
 *
 * If the major link is enabled, after the major loop counter is exhausted, the eDMA engine initiates a
 * channel service request at the channel defined by these six bits by setting that channel start
 * bits.
 *
 * \param[in] obj : pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 * \param[in] majorLinkChannel : channel number for major link
 * \param[in] enable : Enables (true) or Disables (false) channel major link.
 */
__attribute__((always_inline)) static inline void EDmaReg_SetTcdChannelMajorLink(EDmaRegType *obj, uint8_t channel, uint32_t majorLinkChannel, bool enable)
{
    EDmaReg_SetTcdChannelMajorLinkCmd(obj, channel, enable);
    EDmaReg_SetTcdMajorLinkChannel(obj, channel, majorLinkChannel);
}

/*! \brief Sets the channel minor link for the TCD.
 *
 * \param[in] obj : pointer to eDMA register instance
 * \param[in] channel : eDMA channel number.
 * \param[in] linkChannel : Channel to be linked on minor loop complete.
 * \param[in] enable : Enable (true)/Disable (false) channel minor link.
 */
__attribute__((always_inline)) static inline void EDmaReg_SetTcdChannelMinorLink(EDmaRegType *obj, uint8_t channel, uint32_t linkChannel, bool enable)
{
    EDmaReg_SetTcdBiterMinorLinkCmd(obj, channel, enable);
    EDmaReg_SetTcdCiterMinorLinkCmd(obj, channel, enable);
    if(enable)
    {
        EDmaReg_SetTcdBiterMinorLinkChannel(obj, channel, linkChannel);
        EDmaReg_SetTcdCiterMinorLinkChannel(obj, channel, linkChannel);
    }
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _DMA_REG_H_ */
