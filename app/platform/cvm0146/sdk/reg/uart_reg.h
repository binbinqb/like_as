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

#ifndef _UART_REG_H_
#define _UART_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the driver of UART module
 */

/******************************************************************************
 * the includes
 *****************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 * the defines
 *****************************************************************************/

/* CR1 Bit fields */
#define UART_CR1_UE_MASK              (0x00000001ul)
#define UART_CR1_UE_SHIFT             (0u)
#define UART_CR1_UE_WIDTH             (1u)

#define UART_CR1_RE_MASK              (0x00000004ul)
#define UART_CR1_RE_SHIFT             (2u)
#define UART_CR1_RE_WIDTH             (1u)

#define UART_CR1_TE_MASK              (0x00000008ul)
#define UART_CR1_TE_SHIFT             (3u)
#define UART_CR1_TE_WIDTH             (1u)

#define UART_CR1_IDLEIE_MASK          (0x00000010ul)
#define UART_CR1_IDLEIE_SHIFT         (4u)
#define UART_CR1_IDLEIE_WIDTH         (1u)

#define UART_CR1_RDRFIE_MASK          (0x00000020ul)
#define UART_CR1_RDRFIE_SHIFT         (5u)
#define UART_CR1_RDRFIE_WIDTH         (1u)

#define UART_CR1_TCIE_MASK            (0x00000040ul)
#define UART_CR1_TCIE_SHIFT           (6u)
#define UART_CR1_TCIE_WIDTH           (1u)

#define UART_CR1_TDREIE_MASK          (0x00000080ul)
#define UART_CR1_TDREIE_SHIFT         (7u)
#define UART_CR1_TDREIE_WIDTH         (1u)

#define UART_CR1_PEIE_MASK            (0x00000100ul)
#define UART_CR1_PEIE_SHIFT           (8u)
#define UART_CR1_PEIE_WIDTH           (1u)

#define UART_CR1_PS_MASK              (0x00000200ul)
#define UART_CR1_PS_SHIFT             (9u)
#define UART_CR1_PS_WIDTH             (1u)

#define UART_CR1_PCE_MASK             (0x00000400ul)
#define UART_CR1_PCE_SHIFT            (10u)
#define UART_CR1_PCE_WIDTH            (1u)

#define UART_CR1_WAKE_MASK            (0x00000800ul)
#define UART_CR1_WAKE_IDLE_LINE       (0x00000000ul)
#define UART_CR1_WAKE_ADDR_MARK       (0x00000800ul)
#define UART_CR1_WAKE_SHIFT           (11u)
#define UART_CR1_WAKE_WIDTH           (1u)

#define UART_CR1_M_MASK               (0x00001000ul)
#define UART_CR1_M_8BITS              (0x00000000ul)
#define UART_CR1_M_9BITS              (0x00001000ul)
#define UART_CR1_M_SHIFT              (12u)
#define UART_CR1_M_WIDTH              (1u)

#define UART_CR1_MME_MASK             (0x00002000ul)
#define UART_CR1_MME_SHIFT            (13u)
#define UART_CR1_MME_WIDTH            (1u)

#define UART_CR1_SBRKDIE_MASK         (0x00004000ul)
#define UART_CR1_SBRKDIE_SHIFT        (14u)
#define UART_CR1_SBRKDIE_WIDTH        (1u)

#define UART_CR1_OVER8_MASK           (0x00008000ul)
#define UART_CR1_OVER8_SHIFT          (15u)
#define UART_CR1_OVER8_WIDTH          (1u)

#define UART_CR1_DEDT_MASK            (0x001F0000ul)
#define UART_CR1_DEDT_SHIFT           (16u)
#define UART_CR1_DEDT_WIDTH           (5u)

#define UART_CR1_DEAT_MASK            (0x01F00000ul)
#define UART_CR1_DEAT_SHIFT           (21u)
#define UART_CR1_DEAT_WIDTH           (5u)

#define UART_CR1_RTOIE_MASK           (0x04000000ul)
#define UART_CR1_RTOIE_SHIFT          (26u)
#define UART_CR1_RTOIE_WIDTH          (1u)

#define UART_CR1_ABLFIE_MASK          (0x08000000ul)
#define UART_CR1_ABLFIE_SHIFT         (27u)
#define UART_CR1_ABLFIE_WIDTH         (1u)

/* CR2 Bit fields */
#define UART_CR2_SBRK_LEN_MASK        (0x00000003ul)
#define UART_CR2_SBRK_LEN_13BITS      (0x00000000ul)
#define UART_CR2_SBRK_LEN_14BITS      (0x00000001ul)
#define UART_CR2_SBRK_LEN_15BITS      (0x00000002ul)
#define UART_CR2_SBRK_LEN_SHIFT       (0u)
#define UART_CR2_SBRK_LEN_WIDTH       (2u)

#define UART_CR2_SDEL_LEN_MASK        (0x00000004ul)
#define UART_CR2_SDEL_LEN_1BITS       (0x00000000ul)
#define UART_CR2_SDEL_LEN_2BITS       (0x00000004ul)
#define UART_CR2_SDEL_LEN_SHIFT       (2u)
#define UART_CR2_SDEL_LEN_WIDTH       (1u)

#define UART_CR2_ADDM_MASK            (0x00000010ul)
#define UART_CR2_ADDM_4BITS           (0x00000000ul)
#define UART_CR2_ADDM_7BITS           (0x00000010ul)
#define UART_CR2_ADDM_SHIFT           (4u)
#define UART_CR2_ADDM_WIDTH           (1u)

#define UART_CR2_LBDL_MASK            (0x00000060ul)
#define UART_CR2_LBDL_11BITS          (0x00000000ul)
#define UART_CR2_LBDL_12BITS          (0x00000020ul)
#define UART_CR2_LBDL_13BITS          (0x00000040ul)
#define UART_CR2_LBDL_SHIFT           (5u)
#define UART_CR2_LBDL_WIDTH           (2u)

#define UART_CR2_LBDTIE_MASK          (0x00000080ul)
#define UART_CR2_LBDTIE_SHIFT         (7u)
#define UART_CR2_LBDTIE_WIDTH         (1u)

#define UART_CR2_IDLECFG_MASK         (0x00000700ul)
#define UART_CR2_IDLECFG_1DILE_CHAR   (0x00000000ul)
#define UART_CR2_IDLECFG_2DILE_CHAR   (0x00000100ul)
#define UART_CR2_IDLECFG_4DILE_CHAR   (0x00000200ul)
#define UART_CR2_IDLECFG_8DILE_CHAR   (0x00000300ul)
#define UART_CR2_IDLECFG_16DILE_CHAR  (0x00000400ul)
#define UART_CR2_IDLECFG_32DILE_CHAR  (0x00000500ul)
#define UART_CR2_IDLECFG_64DILE_CHAR  (0x00000600ul)
#define UART_CR2_IDLECFG_128DILE_CHAR (0x00000700ul)
#define UART_CR2_IDLECFG_SHIFT        (8u)
#define UART_CR2_IDLECFG_WIDTH        (3u)

#define UART_CR2_STOP_MASK            (0x00002000ul)
#define UART_CR2_STOP_SHIFT           (13u)
#define UART_CR2_STOP_WIDTH           (1u)

#define UART_CR2_LINEN_MASK           (0x00004000ul)
#define UART_CR2_LINEN_SHIFT          (14u)
#define UART_CR2_LINEN_WIDTH          (1u)

#define UART_CR2_LIN_BDSYNC_MASK      (0x00008000ul)
#define UART_CR2_LIN_BDSYNC_SHIFT     (15u)
#define UART_CR2_LIN_BDSYNC_WIDTH     (1u)

#define UART_CR2_RXINV_MASK           (0x00010000ul)
#define UART_CR2_RXINV_SHIFT          (16u)
#define UART_CR2_RXINV_WIDTH          (1u)

#define UART_CR2_TXINV_MASK           (0x00020000ul)
#define UART_CR2_TXINV_SHIFT          (17u)
#define UART_CR2_TXINV_WIDTH          (1u)

#define UART_CR2_DATAINV_MASK         (0x00040000ul)
#define UART_CR2_DATAINV_SHIFT        (18u)
#define UART_CR2_DATAINV_WIDTH        (1u)

#define UART_CR2_MSBFIRST_MASK        (0x00080000ul)
#define UART_CR2_MSBFIRST_SHIFT       (19u)
#define UART_CR2_MSBFIRST_WIDTH       (1u)

#define UART_CR2_ABREN_MASK           (0x00100000ul)
#define UART_CR2_ABREN_SHIFT          (20u)
#define UART_CR2_ABREN_WIDTH          (1u)

#define UART_CR2_ABRMOD_MASK          (0x00600000ul)
#define UART_CR2_ABRMOD_SHIFT         (21u)
#define UART_CR2_ABRMOD_WIDTH         (2u)

#define UART_CR2_RTOEN_MASK           (0x00800000ul)
#define UART_CR2_RTOEN_SHIFT          (23u)
#define UART_CR2_RTOEN_WIDTH          (1u)

#define UART_CR2_ADD_MASK             (0xFF000000ul)
#define UART_CR2_ADD_SHIFT            (24u)
#define UART_CR2_ADD_WIDTH            (8u)

/* CR3 Bit fields */
#define UART_CR3_EIE_MASK             (0x00000001uL)
#define UART_CR3_EIE_SHIFT            (0u)
#define UART_CR3_EIE_WIDTH            (1u)

#define UART_CR3_LOOPS_MASK           (0x00000004uL)
#define UART_CR3_LOOPS_SHIFT          (2u)
#define UART_CR3_LOOPS_WIDTH          (1u)

#define UART_CR3_HDSEL_MASK           (0x00000008uL)
#define UART_CR3_HDSEL_SHIFT          (3u)
#define UART_CR3_HDSEL_WIDTH          (1u)

#define UART_CR3_DMAR_MASK            (0x00000040ul)
#define UART_CR3_DMAR_SHIFT           (6u)
#define UART_CR3_DMAR_WIDTH           (1u)

#define UART_CR3_DMAT_MASK            (0x00000080ul)
#define UART_CR3_DMAT_SHIFT           (7u)
#define UART_CR3_DMAT_WIDTH           (1u)

#define UART_CR3_RTSE_MASK            (0x00000100ul)
#define UART_CR3_RTSE_SHIFT           (8u)
#define UART_CR3_RTSE_WIDTH           (1u)

#define UART_CR3_CTSE_MASK            (0x00000200ul)
#define UART_CR3_CTSE_SHIFT           (9u)
#define UART_CR3_CTSE_WIDTH           (1u)

#define UART_CR3_CTSIE_MASK           (0x00000400ul)
#define UART_CR3_CTSIE_SHIFT          (10u)
#define UART_CR3_CTSIE_WIDTH          (1u)

#define UART_CR3_ONEBIT_MASK          (0x00000800ul)
#define UART_CR3_ONEBIT_SHIFT         (11u)
#define UART_CR3_ONEBIT_WIDTH         (1u)

#define UART_CR3_DEM_MASK             (0x00004000ul)
#define UART_CR3_DEM_SHIFT            (14u)
#define UART_CR3_DEM_WIDTH            (1u)

#define UART_CR3_DEP_MASK             (0x00008000ul)
#define UART_CR3_DEP_SHIFT            (15u)
#define UART_CR3_DEP_WIDTH            (1u)

/* BRR Bit fields */
#define UART_BRR_BRR_MASK             (0x00FFFFFFul)
#define UART_BRR_BRR_SHIFT            (0u)
#define UART_BRR_BRR_WIDTH            (24u)

/* RTOR Bit fields */
#define UART_RTOR_LIN_BDRTO_MASK      (0xFF000000ul)
#define UART_RTOR_LIN_BDRTO_SHIFT     (24u)
#define UART_RTOR_LIN_BDRTO_WIDTH     (8u)

#define UART_RTOR_RTO_MASK            (0x00FFFFFFul)
#define UART_RTOR_RTO_SHIFT           (0u)
#define UART_RTOR_RTO_WIDTH           (24u)

/* RQR Bit fields */
#define UART_RQR_ABRRQ_MASK           (0x00000001ul)
#define UART_RQR_ABRRQ_SHIFT          (0u)
#define UART_RQR_ABRRQ_WIDTH          (1u)

#define UART_RQR_SBRKRQ_MASK          (0x00000002ul)
#define UART_RQR_SBRKRQ_SHIFT         (1u)
#define UART_RQR_SBRKRQ_WIDTH         (1u)

#define UART_RQR_MMRQ_MASK            (0x00000004ul)
#define UART_RQR_MMRQ_SHIFT           (2u)
#define UART_RQR_MMRQ_WIDTH           (1u)

/* ISR Bit fields */
#define UART_ISR_PE_MASK              (0x00000001ul)
#define UART_ISR_PE_SHIFT             (0u)
#define UART_ISR_PE_WIDTH             (1u)

#define UART_ISR_FE_MASK              (0x00000002ul)
#define UART_ISR_FE_SHIFT             (1u)
#define UART_ISR_FE_WIDTH             (1u)

#define UART_ISR_NF_MASK              (0x00000004ul)
#define UART_ISR_NF_SHIFT             (2u)
#define UART_ISR_NF_WIDTH             (1u)

#define UART_ISR_ORE_MASK             (0x00000008ul)
#define UART_ISR_ORE_SHIFT            (3u)
#define UART_ISR_ORE_WIDTH            (1u)

#define UART_ISR_IDLE_MASK            (0x00000010ul)
#define UART_ISR_IDLE_SHIFT           (4u)
#define UART_ISR_IDLE_WIDTH           (1u)

#define UART_ISR_RDRF_MASK            (0x00000020ul)
#define UART_ISR_RDRF_SHIFT           (5u)
#define UART_ISR_RDRF_WIDTH           (1u)

#define UART_ISR_TC_MASK              (0x00000040ul)
#define UART_ISR_TC_SHIFT             (6u)
#define UART_ISR_TC_WIDTH             (1u)

#define UART_ISR_TDRE_MASK            (0x00000080ul)
#define UART_ISR_TDRE_SHIFT           (7u)
#define UART_ISR_TDRE_WIDTH           (1u)

#define UART_ISR_LBDT_DONE_MASK       (0x00000100ul)
#define UART_ISR_LBDT_DONE_SHIFT      (8u)
#define UART_ISR_LBDT_DONE_WIDTH      (1u)

#define UART_ISR_CTSIF_MASK           (0x00000200ul)
#define UART_ISR_CTSIF_SHIFT          (9u)
#define UART_ISR_CTSIF_WIDTH          (1u)

#define UART_ISR_CTS_MASK             (0x00000400ul)
#define UART_ISR_CTS_SHIFT            (10u)
#define UART_ISR_CTS_WIDTH            (1u)

#define UART_ISR_RTOF_MASK            (0x00000800ul)
#define UART_ISR_RTOF_SHIFT           (11u)
#define UART_ISR_RTOF_WIDTH           (1u)

#define UART_ISR_ABRE_MASK            (0x00004000ul)
#define UART_ISR_ABRE_SHIFT           (14u)
#define UART_ISR_ABRE_WIDTH           (1u)

#define UART_ISR_ABRF_MASK            (0x00008000ul)
#define UART_ISR_ABRF_SHIFT           (15u)
#define UART_ISR_ABRF_WIDTH           (1u)

#define UART_ISR_BUSY_MASK            (0x00010000ul)
#define UART_ISR_BUSY_SHIFT           (16u)
#define UART_ISR_BUSY_WIDTH           (1u)

#define UART_ISR_LBDT_FAIL_MASK       (0x00020000ul)
#define UART_ISR_LBDT_FAIL_SHIFT      (17u)
#define UART_ISR_LBDT_FAIL_WIDTH      (1u)

#define UART_ISR_SBRKD_MASK           (0x00040000ul)
#define UART_ISR_SBRKD_SHIFT          (18u)
#define UART_ISR_SBRKD_WIDTH          (1u)

#define UART_ISR_RWU_MASK             (0x00080000ul)
#define UART_ISR_RWU_SHIFT            (19u)
#define UART_ISR_RWU_WIDTH            (1u)

/* ICR Bit fields */
#define UART_ICR_PECF_MASK            (0x00000001ul)
#define UART_ICR_PECF_SHIFT           (0u)
#define UART_ICR_PECF_WIDTH           (1u)

#define UART_ICR_FECF_MASK            (0x00000002ul)
#define UART_ICR_FECF_SHIFT           (1u)
#define UART_ICR_FECF_WIDTH           (1u)

#define UART_ICR_NCF_MASK             (0x00000004ul)
#define UART_ICR_NCF_SHIFT            (2u)
#define UART_ICR_NCF_WIDTH            (1u)

#define UART_ICR_ORECF_MASK           (0x00000008ul)
#define UART_ICR_ORECF_SHIFT          (3u)
#define UART_ICR_ORECF_WIDTH          (1u)

#define UART_ICR_IDLECF_MASK          (0x00000010ul)
#define UART_ICR_IDLECF_SHIFT         (4u)
#define UART_ICR_IDLECF_WIDTH         (1u)

#define UART_ICR_TCCF_MASK            (0x00000040ul)
#define UART_ICR_TCCF_SHIFT           (6u)
#define UART_ICR_TCCF_WIDTH           (1u)

#define UART_ICR_LBDTCF_MASK          (0x00000100ul)
#define UART_ICR_LBDTCF_SHIFT         (8u)
#define UART_ICR_LBDTCF_WIDTH         (1u)

#define UART_ICR_CTSCF_MASK           (0x00000200ul)
#define UART_ICR_CTSCF_SHIFT          (9u)
#define UART_ICR_CTSCF_WIDTH          (1u)

#define UART_ICR_RTOCF_MASK           (0x00000800ul)
#define UART_ICR_RTOCF_SHIFT          (11u)
#define UART_ICR_RTOCF_WIDTH          (1u)

#define UART_ICR_SBRKDCF_MASK         (0x00040000ul)
#define UART_ICR_SBRKDCF_SHIFT        (18u)
#define UART_ICR_SBRKDCF_WIDTH        (1u)

/* RDR Bit fields */
#define UART_RDR_RDR_MASK             (0x000001FFul)
#define UART_RDR_RDR_SHIFT            (0u)
#define UART_RDR_RDR_WIDTH            (9u)

#define UART_RDR_FE_MASK              (0x00002000ul)
#define UART_RDR_FE_SHIFT             (13u)
#define UART_RDR_FE_WIDTH             (1u)

#define UART_RDR_PE_MASK              (0x00004000ul)
#define UART_RDR_PE_SHIFT             (14u)
#define UART_RDR_PE_WIDTH             (1u)

#define UART_RDR_NF_MASK              (0x00008000ul)
#define UART_RDR_NF_SHIFT             (15u)
#define UART_RDR_NF_WIDTH             (1u)

#define UART_RDR_ERR_MASK             (0x0000E000ul)
#define UART_RDR_ERR_SHIFT            (13u)
#define UART_RDR_ERR_WIDTH            (3u)

/* TDR Bit fields */
#define UART_TDR_TDR_MASK             (0x000001FFul)
#define UART_TDR_TDR_SHIFT            (0u)
#define UART_TDR_TDR_WIDTH            (9u)

/* FIFO Bit fields */
#define UART_FIFO_RXUFE_MASK          (0x00000100ul)
#define UART_FIFO_RXUFE_SHIFT         (8u)
#define UART_FIFO_RXUFE_WIDTH         (1u)

#define UART_FIFO_TXOFE_MASK          (0x00000200ul)
#define UART_FIFO_TXOFE_SHIFT         (9u)
#define UART_FIFO_TXOFE_WIDTH         (1u)

#define UART_FIFO_RXFLUSH_MASK        (0x00004000ul)
#define UART_FIFO_RXFLUSH_SHIFT       (14u)
#define UART_FIFO_RXFLUSH_WIDTH       (1u)

#define UART_FIFO_TXFLUSH_MASK        (0x00008000ul)
#define UART_FIFO_TXFLUSH_SHIFT       (15u)
#define UART_FIFO_TXFLUSH_WIDTH       (1u)

#define UART_FIFO_RXUF_MASK           (0x00010000ul)
#define UART_FIFO_RXUF_SHIFT          (16u)
#define UART_FIFO_RXUF_WIDTH          (1u)

#define UART_FIFO_TXOF_MASK           (0x00020000ul)
#define UART_FIFO_TXOF_SHIFT          (17u)
#define UART_FIFO_TXOF_WIDTH          (1u)

#define UART_FIFO_RXEMPT_MASK         (0x00400000ul)
#define UART_FIFO_RXEMPT_SHIFT        (22u)
#define UART_FIFO_RXEMPT_WIDTH        (1u)

#define UART_FIFO_TXEMPT_MASK         (0x00800000ul)
#define UART_FIFO_TXEMPT_SHIFT        (23u)
#define UART_FIFO_TXEMPT_WIDTH        (1u)

/* WATER Bit fields */
#define UART_WATER_TXWATER_MASK       (0x00000003ul)
#define UART_WATER_TXWATER_SHIFT      (0u)
#define UART_WATER_TXWATER_WIDTH      (2u)

#define UART_WATER_TXCOUNT_MASK       (0x00000700ul)
#define UART_WATER_TXCOUNT_SHIFT      (8u)
#define UART_WATER_TXCOUNT_WIDTH      (3u)
#define UART_WATER_RXWATER_MASK       (0x00030000ul)
#define UART_WATER_RXWATER_SHIFT      (16u)
#define UART_WATER_RXWATER_WIDTH      (2u)

#define UART_WATER_RXCOUNT_MASK       (0x07000000ul)
#define UART_WATER_RXCOUNT_SHIFT      (24u)
#define UART_WATER_RXCOUNT_WIDTH      (3u)

/******************************************************************************
 * the typedefs
 *****************************************************************************/

/*! \brief The definition of UART registers */
typedef struct _UartRegType_
{
    volatile uint32_t       CR1; /*!< UART Control Register 1, offset: 0x0 */
    volatile uint32_t       CR2; /*!< UART Control Register 2, offset: 0x4 */
    volatile uint32_t       CR3; /*!< UART Control Register 3, offset: 0x8 */
    volatile uint32_t       BRR; /*!< UART Baud Rate Register, offset: 0xC */
    uint32_t                RES;
    volatile uint32_t       RTOR;  /*!< UART Receiver timeout Value Register, offset: 0x14 */
    volatile uint32_t       RQR;   /*!< UART Request Register, offset: 0x18 */
    volatile const uint32_t ISR;   /*!< UART Status Register, offset: 0x1C */
    volatile uint32_t       ICR;   /*!< UART Interrupt Clear Register, offset: 0x20 */
    volatile uint32_t       RDR;   /*!< UART Receive data Register, offset: 0x24 */
    volatile uint32_t       TDR;   /*!< UART Transmit data Register, offset: 0x28 */
    volatile uint32_t       FIFO;  /*!< UART FIFO Register, offset: 0x2C */
    volatile uint32_t       WATER; /*!< UART Watermark Register, offset: 0x30 */
} UartRegType;

/******************************************************************************
 * the globals
 ******************************************************************************/

/******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Auto baud rate detection or LIN BREAK detection fail interrupt enable
 *
 *  this function enable the Auto baud rate detection or LIN BREAK detection fail interrupt
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] enable :
 *            0: Interrupt is inhibited
 *            1: An UART interrupt is generated when the  ABRE or LBDT_FAIL bit is set in the ISR register.
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SetAutoBaudrateOrLinBreakDetectedFailedIsr(UartRegType *const obj, bool enable)
{
    uint32_t tmp = obj->CR1;

    if(enable == true)
    {
        obj->CR1 = ((1ul << UART_CR1_ABLFIE_SHIFT) | ((~UART_CR1_ABLFIE_MASK) & tmp));
    }
    else
    {
        obj->CR1 = ((0ul << UART_CR1_ABLFIE_SHIFT) | ((~UART_CR1_ABLFIE_MASK) & tmp));
    }
}

/*! \brief Auto baud rate detection or LIN BREAK detection fail interrupt enable
 *
 *  this function get the Auto baud rate detection or LIN BREAK detection fail interrupt is enabled or not
 *
 * \param[in] obj : pointer to UART driver instance
 * \return: bool :
 *            0: Interrupt is inhibited
 *            1: An UART interrupt is generated when the  ABRE or LBDT_FAIL bit is set in the ISR register.
 */
__attribute__((always_inline)) static inline bool UartReg_GetAutoBaudrateOrLinBreakDetectedFailedIsrIsEnabled(const UartRegType *obj)
{
    bool     tRtn      = false;
    uint32_t tmp = obj->CR1;

    if((tmp & UART_CR1_ABLFIE_MASK) != 0u)
    {
        tRtn = true;
    }

    return tRtn;
}

/*! \brief Receiver timeout interrupt enable or disable
 *
 *  this function enable the rx timeout interrupt features
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] enable :
 *            0: Interrupt is inhibited
 *            1: An UART interrupt is generated when the RTOF bit is set in the ISR register.
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SetRxTimeoutIsr(UartRegType *obj, bool enable)
{
    uint32_t tmp = obj->CR1;

    if(enable == true)
    {
        obj->CR1 = ((1ul << UART_CR1_RTOIE_SHIFT) | ((~UART_CR1_RTOIE_MASK) & tmp));
    }
    else
    {
        obj->CR1 = ((0ul << UART_CR1_RTOIE_SHIFT) | ((~UART_CR1_RTOIE_MASK) & tmp));
    }
}

/*! \brief Get the RxTimeoutIsr enable status
 *
 * Readout the current Interrupt enable is active or not
 *
 * \param[in] obj : pointer to UART driver instance
 * \return: bool
 *          true: Enabled
 *          false: Disabled
 */
__attribute__((always_inline)) static inline bool UartReg_GetRxTimeoutIsrIsEnabled(const UartRegType *obj)
{
    bool isEnabled = false;

    if((obj->CR1 & UART_CR1_RTOIE_MASK) != 0u)
    {
        isEnabled = true;
    }

    return isEnabled;
}

/*! \brief Driver Enable assertion time
 *
 *  This bit field can only be written when the UART is disabled (UE=0).
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] deat :This 5-bit value defines the time between the activation of the DE (Driver Enable) signal and the beginning of the start bit
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SetDEAT(UartRegType *obj, uint8_t deat)
{
    uint32_t tmp = obj->CR1;
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    tmp &= ~UART_CR1_DEAT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(deat)) << UART_CR1_DEAT_SHIFT)) & UART_CR1_DEAT_MASK);
    obj->CR1 = tmp;
}

/*! \brief Driver Enable de-assertion time
 *
 *  This bit field can only be written when the UART is disabled (UE=0).
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] dedt: This 5-bit value defines the time between the end of the last stop bit,
 *            in a transmitted message, and the de-activation of the DE (Driver Enable) signal
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SetDEDT(UartRegType *obj, uint8_t dedt)
{
    uint32_t tmp = obj->CR1;
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    tmp &= ~UART_CR1_DEDT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(dedt)) << UART_CR1_DEDT_SHIFT)) & UART_CR1_DEDT_MASK);
    obj->CR1 = tmp;
}

/*! \brief Oversampling mode
 *
 *  This bit can only be written when the UART is disabled (UE=0).
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] samplingBy8BitModeEn:
 *            0: Oversampling by 16
 *            1: Oversampling by 8
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SetOverSamplingMode(UartRegType *obj, bool samplingBy8BitModeEn)
{
    uint32_t tmp = obj->CR1;

    if(samplingBy8BitModeEn == true)
    {
        obj->CR1 = ((1ul << UART_CR1_OVER8_SHIFT) | ((~UART_CR1_OVER8_MASK) & tmp));
    }
    else
    {
        obj->CR1 = ((0ul << UART_CR1_OVER8_SHIFT) | ((~UART_CR1_OVER8_MASK) & tmp));
    }
}

/*! \brief SBRKD interrupt enable
 *
 *  this function enable the break tx completed interrupt request if finished tx break signal
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] txBreakOkIsr:
 *            0: Interrupt is inhibited
 *            1: A UART interrupt is generated whenever SBRKD=1 in the ISR register
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SetBreakTxCompletedIsr(UartRegType *obj, bool txBreakOkIsr)
{
    uint32_t tmp = obj->CR1;

    if(txBreakOkIsr == true)
    {
        obj->CR1 = ((1ul << UART_CR1_SBRKDIE_SHIFT) | ((~UART_CR1_SBRKDIE_MASK) & tmp));
    }
    else
    {
        obj->CR1 = ((0ul << UART_CR1_SBRKDIE_SHIFT) | ((~UART_CR1_SBRKDIE_MASK) & tmp));
    }
}

/*! \brief Get the BreakTxCompletedIsr enable status
 *
 * Readout the current Interrupt enable is active or not
 *
 * \param[in] obj : pointer to UART driver instance
 * \return: bool
 *          true: Enabled
 *          false: Disabled
 */
__attribute__((always_inline)) static inline bool UartReg_GetBreakTxCompletedIsrIsEnabled(const UartRegType *obj)
{
    bool isEnabled = false;

    if((obj->CR1 & UART_CR1_SBRKDIE_MASK) != 0u)
    {
        isEnabled = true;
    }

    return isEnabled;
}

/*! \brief Mute mode enable
 *
 *  This bit activates the mute mode function of the UART. when set, the UART can switch between the active and mute modes,
 *       as defined by the WAKE bit.
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] muteEn:
 *            0: Receiver in active mode permanently
 *            1: Receiver can switch between mute mode and active mode.
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SetMuteMode(UartRegType *obj, bool muteEn)
{
    uint32_t tmp = obj->CR1;

    if(muteEn == true)
    {
        obj->CR1 = ((1ul << UART_CR1_MME_SHIFT) | ((~UART_CR1_MME_MASK) & tmp));
    }
    else
    {
        obj->CR1 = ((0ul << UART_CR1_MME_SHIFT) | ((~UART_CR1_MME_MASK) & tmp));
    }
}

/*! \brief Get the mute
 *
 *  this function get the mute mode is active or not
 *
 * \param[in] obj : pointer to UART driver instance
 * \return: bool
 *          0: Receiver in active mode permanently
 *          1: Receiver can switch between mute mode and active mode.
 */
__attribute__((always_inline)) static inline bool UartReg_GetMuteIsActive(const UartRegType *obj)
{
    bool tRtn = false;

    if((obj->CR1 & UART_CR1_MME_MASK) != 0u)
    {
        tRtn = true;
    }

    return tRtn;
}

/*! \brief Set Word length
 *
 *  this function set the frame bits formate
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] wordLen:
 *            0: 1 Start bit, 8 data bits, n stop bits
 *            1: 1 Start bit, 9 data bits, n stop bits
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SetWordLength(UartRegType *obj, uint8_t wordLen)
{
    uint32_t tmp = obj->CR1;
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    tmp &= ~UART_CR1_M_MASK;
    tmp |= (((uint32_t)(((uint32_t)(wordLen)) << UART_CR1_M_SHIFT)) & UART_CR1_M_MASK);
    obj->CR1 = tmp;
}

/*! \brief Set Receiver wakeup method
 *
 *  This bit field can only be written when the UART is disabled (UE=0).
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] wkpMethod:
 *            0: Idle line
 *            1: Address mark
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SetWakeupMethod(UartRegType *obj, uint8_t wkpMethod)
{
    uint32_t tmp = obj->CR1;
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    tmp &= ~UART_CR1_WAKE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(wkpMethod)) << UART_CR1_WAKE_SHIFT)) & UART_CR1_WAKE_MASK);
    obj->CR1 = tmp;
}

/*! \brief Get wake up source
 *
 *  this function get the address to wakeup
 *
 * \param[in] obj : pointer to UART driver instance
 * \return: bool
 *          0: Idle line
 *          1: Address mark
 */
__attribute__((always_inline)) static inline bool UartReg_GetWakeUpByAddress(const UartRegType *obj)
{
    bool tRtn = false;

    if((obj->CR1 & UART_CR1_WAKE_MASK) != 0u)
    {
        tRtn = true;
    }

    return tRtn;
}

/*! \brief  selects the hardware parity control
 *
 *  This bit field can only be written when the UART is disabled (UE=0).
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] parityCtrlEn: enable or disable
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SetParityControlEnable(UartRegType *obj, bool parityCtrlEn)
{
    uint32_t tmp = obj->CR1;

    if(parityCtrlEn == true)
    {
        obj->CR1 = ((1ul << UART_CR1_PCE_SHIFT) | ((~UART_CR1_PCE_MASK) & tmp));
    }
    else
    {
        obj->CR1 = ((0ul << UART_CR1_PCE_SHIFT) | ((~UART_CR1_PCE_MASK) & tmp));
    }
}

/*! \brief This bit selects the odd or even parity when the parity generation/detection is enabled (PCE bit set).
 *
 *  This bit field can only be written when the UART is disabled (UE=0).
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] paritySelection:
 *            0: Even parity
 *            1: Odd parity
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SelectParity(UartRegType *obj, uint8_t paritySelection)
{
    uint32_t tmp = obj->CR1;
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    tmp &= ~UART_CR1_PS_MASK;
    tmp |= (((uint32_t)(((uint32_t)(paritySelection)) << UART_CR1_PS_SHIFT)) & UART_CR1_PS_MASK);
    obj->CR1 = tmp;
}

/*! \brief Set Parity error interrupt enable or disable
 *
 *  this function set the  Parity error interrupt enable or disable
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] parityErrIsrEn:
 *            0: Interrupt is inhibited
 *            1: A UART interrupt is generated whenever PE=1 in the ISR register
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SetParityErrIsr(UartRegType *obj, bool parityErrIsrEn)
{
    uint32_t tmp = obj->CR1;

    if(parityErrIsrEn == true)
    {
        obj->CR1 = ((1ul << UART_CR1_PEIE_SHIFT) | ((~UART_CR1_PEIE_MASK) & tmp));
    }
    else
    {
        obj->CR1 = ((0ul << UART_CR1_PEIE_SHIFT) | ((~UART_CR1_PEIE_MASK) & tmp));
    }
}

/*! \brief Get the ParityErrIsr enable status
 *
 * Readout the current Interrupt enable is active or not
 *
 * \param[in] obj : pointer to UART driver instance
 * \return: bool
 *          true: Enabled
 *          false: Disabled
 */
__attribute__((always_inline)) static inline bool UartReg_GetParityErrIsrIsEnabled(const UartRegType *obj)
{
    bool isEnabled = false;

    if((obj->CR1 & UART_CR1_PEIE_MASK) != 0u)
    {
        isEnabled = true;
    }

    return isEnabled;
}

/*! \brief Set tx buffer empty interrupt enable or disable
 *
 *  this function set the tx buffer empty interrupt request when condition is matched
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] enable:
 *            0: Interrupt is inhibited
 *            1: A UART interrupt is generated whenever TDRE=1 in the ISR register
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SetTxBufferEmptyIsr(UartRegType *obj, bool enable)
{
    uint32_t tmp = obj->CR1;

    if(enable == true)
    {
        obj->CR1 = ((1ul << UART_CR1_TDREIE_SHIFT) | ((~UART_CR1_TDREIE_MASK) & tmp));
    }
    else
    {
        obj->CR1 = ((0ul << UART_CR1_TDREIE_SHIFT) | ((~UART_CR1_TDREIE_MASK) & tmp));
    }
}

/*! \brief Get the TxBufferEmptyIsr enable status
 *
 * Readout the current Interrupt enable is active or not
 *
 * \param[in] obj : pointer to UART driver instance
 * \return: bool
 *          true: Enabled
 *          false: Disabled
 */
__attribute__((always_inline)) static inline bool UartReg_GetTxBufferEmptyIsrIsEnabled(const UartRegType *obj)
{
    bool isEnabled = false;

    if((obj->CR1 & UART_CR1_TDREIE_MASK) != 0u)
    {
        isEnabled = true;
    }

    return isEnabled;
}

/*! \brief Set Transmission complete interrupt enable or disable
 *
 *  This bit is set and cleared by software.
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] enable:
 *            0: Interrupt is inhibited
 *            1: A UART interrupt is generated whenever TC=1 in the ISR register
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SetTxCompletedIsr(UartRegType *obj, bool enable)
{
    uint32_t tmp = obj->CR1;

    if(enable == true)
    {
        obj->CR1 = ((1ul << UART_CR1_TCIE_SHIFT) | ((~UART_CR1_TCIE_MASK) & tmp));
    }
    else
    {
        obj->CR1 = ((0ul << UART_CR1_TCIE_SHIFT) | ((~UART_CR1_TCIE_MASK) & tmp));
    }
}

/*! \brief Get the TxCompletedIsr enable status
 *
 * Readout the current Interrupt enable is active or not
 *
 * \param[in] obj : pointer to UART driver instance
 * \return: bool
 *          true: Enabled
 *          false: Disabled
 */
__attribute__((always_inline)) static inline bool UartReg_GetTxCompletedIsrIsEnabled(const UartRegType *obj)
{
    bool isEnabled = false;

    if((obj->CR1 & UART_CR1_TCIE_MASK) != 0u)
    {
        isEnabled = true;
    }

    return isEnabled;
}

/*! \brief Set rx buffer full interrupt enable or disable
 *
 *  this function set the rx buffer full interrupt request when condition is matched
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] enable:
 *            0: Interrupt is inhibited
 *            1: A UART interrupt is generated when RDRF=1 in the ISR register
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SetRxBufferFullIsr(UartRegType *obj, bool enable)
{
    uint32_t tmp = obj->CR1;

    if(enable == true)
    {
        obj->CR1 = ((1ul << UART_CR1_RDRFIE_SHIFT) | ((~UART_CR1_RDRFIE_MASK) & tmp));
    }
    else
    {
        obj->CR1 = ((0ul << UART_CR1_RDRFIE_SHIFT) | ((~UART_CR1_RDRFIE_MASK) & tmp));
    }
}

/*! \brief Get the RxBufferFullIsr enable status
 *
 * Readout the current Interrupt enable is active or not
 *
 * \param[in] obj : pointer to UART driver instance
 * \return: bool
 *          true: Enabled
 *          false: Disabled
 */
__attribute__((always_inline)) static inline bool UartReg_GetRxBufferFullIsrIsEnabled(const UartRegType *obj)
{
    bool isEnabled = false;

    if((obj->CR1 & UART_CR1_RDRFIE_MASK) != 0u)
    {
        isEnabled = true;
    }

    return isEnabled;
}

/*! \brief Set IDLE interrupt enable or disable
 *
 *  this function set the idle interrupt request when condition is matched
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] enable:
 *            0: Interrupt is inhibited
 *            1: A UART interrupt is generated whenever IDLE=1 in the ISR register
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SetIdleIsr(UartRegType *obj, bool enable)
{
    uint32_t tmp = obj->CR1;

    if(enable == true)
    {
        obj->CR1 = ((1ul << UART_CR1_IDLEIE_SHIFT) | ((~UART_CR1_IDLEIE_MASK) & tmp));
    }
    else
    {
        obj->CR1 = ((0ul << UART_CR1_IDLEIE_SHIFT) | ((~UART_CR1_IDLEIE_MASK) & tmp));
    }
}

/*! \brief Get the IdleIsr enable status
 *
 * Readout the current Interrupt enable is active or not
 *
 * \param[in] obj : pointer to UART driver instance
 * \return: bool
 *          true: Enabled
 *          false: Disabled
 */
__attribute__((always_inline)) static inline bool UartReg_GetIdleIsrIsEnabled(const UartRegType *obj)
{
    bool isEnabled = false;

    if((obj->CR1 & UART_CR1_IDLEIE_MASK) != 0u)
    {
        isEnabled = true;
    }

    return isEnabled;
}

/*! \brief Set Transmitter enable or disable
 *
 *  this function enable the transmitter feature
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] enable:
 *            0: Transmitter is disabled
 *            1: Transmitter is enabled
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SetTransmitterEnable(UartRegType *obj, bool enable)
{
    uint32_t tmp = obj->CR1;

    if(enable == true)
    {
        obj->CR1 = ((1ul << UART_CR1_TE_SHIFT) | ((~UART_CR1_TE_MASK) & tmp));
    }
    else
    {
        obj->CR1 = ((0ul << UART_CR1_TE_SHIFT) | ((~UART_CR1_TE_MASK) & tmp));
    }
}

/*! \brief Set Receiver enable or disable
 *
 * this function enable the receive feature
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] enable:
 *            0: Receiver is disabled
 *            1: Receiver is enabled and begins searching for a start bit
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SetReceiverEnable(UartRegType *obj, bool enable)
{
    uint32_t tmp = obj->CR1;

    if(enable == true)
    {
        obj->CR1 = ((1ul << UART_CR1_RE_SHIFT) | ((~UART_CR1_RE_MASK) & tmp));
    }
    else
    {
        obj->CR1 = ((0ul << UART_CR1_RE_SHIFT) | ((~UART_CR1_RE_MASK) & tmp));
    }
}

/*! \brief UART module enable
 *
 *  In order to go into low-power mode without generating errors on the line, the TE bit must be reset before and
 *       the software must wait for the TC bit in the ISR to be set before resetting the UE bit.
 *       The DMA requests are also reset when UE = 0 so the DMA channel must be disabled before resetting the UE bit.
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] enable:
 *            0: UART prescaler and outputs disabled, low-power mode
 *            1: UART enabled
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_EnableModule(UartRegType *obj, bool enable)
{
    uint32_t tmp = obj->CR1;

    if(enable == true)
    {
        obj->CR1 = ((1ul << UART_CR1_UE_SHIFT) | ((~UART_CR1_UE_MASK) & tmp));
    }
    else
    {
        obj->CR1 = ((0ul << UART_CR1_UE_SHIFT) | ((~UART_CR1_UE_MASK) & tmp));
    }
}

/*! \brief Get UART module enable state
 *
 * This function get the enable state of LPTMR.
 * When UE is clear, the UART is disabled.
 * When UE is set, the UART is enabled.
 *
 * \param[in] obj : pointer to UART driver instance
 * \return the state of the UART
 *         - 0 : UART is disabled.
 *         - 1 : UART is enabled.
 */
__attribute__((always_inline)) static inline uint8_t UartReg_GetEnable(const UartRegType *obj)
{
    return ((obj->CR1 & UART_CR1_UE_MASK) >> UART_CR1_UE_SHIFT);
}

/*! \brief Set Address of the UART node
 *
 *  This bit field can only be written when reception is disabled (RE = 0) or the UART is disabled (UE=0)
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] address: This bit-field gives the address of the UART node or a character code to be recognized.
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SetNodeAddress(UartRegType *obj, uint8_t address)
{
    uint32_t tmp = obj->CR2;
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    tmp &= ~UART_CR2_ADD_MASK;
    tmp |= (((uint32_t)(((uint32_t)(address)) << UART_CR2_ADD_SHIFT)) & UART_CR2_ADD_MASK);
    obj->CR2 = tmp;
}

/*! \brief Receiver timeout enable
 *
 *  When this feature is enabled, the RTOF flag in the ISR register is set if the RX line is idle (no reception)
 *       for the duration programmed in the RTOR (receiver timeout register).
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] enable:
 *            0: Receiver timeout feature disabled.
 *            1: Receiver timeout feature enabled.
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_EnableRxTimeoutFeature(UartRegType *obj, bool enable)
{
    uint32_t tmp = obj->CR2;

    if(enable == true)
    {
        obj->CR2 = ((1ul << UART_CR2_RTOEN_SHIFT) | ((~UART_CR2_RTOEN_MASK) & tmp));
    }
    else
    {
        obj->CR2 = ((0ul << UART_CR2_RTOEN_SHIFT) | ((~UART_CR2_RTOEN_MASK) & tmp));
    }
}

/*! \brief Get RxTimeout feature enable or disable
 *
 *  this function get the config of rx timeout feature tha is enable or disable
 *
 * \param[in] obj : pointer to UART driver instance
 * \return: bool
 *          0: Receiver timeout feature disabled.
 *          1: Receiver timeout feature enabled.
 */
__attribute__((always_inline)) static inline bool UartReg_GetRxTimeoutFeatureEnable(const UartRegType *obj)
{
    bool tRtn = false;

    if((obj->CR2 & UART_CR2_RTOEN_MASK) != 0u)
    {
        tRtn = true;
    }

    return tRtn;
}

/*! \brief Auto baud rate mode
 *
 *  This bit field can only be written when ABREN = 0 or the UART is disabled (UE=0).
 *       If DATAINV=1 and/or MSBFIRST=1 the patterns must be the same on the line, for example 0xAA for MSBFIRST)
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] autoMode:
 *            00: Measurement of the start bit is used to detect the baud rate.
 *            01: Falling edge to falling edge measurement. (the received frame must start with a single bit = 1 -> Frame = Start10xxxxxx)
 *            10: 0x7F frame detection.
 *            11: 0x55 frame detection
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SetAutoBaudrateMode(UartRegType *obj, uint8_t autoMode)
{
    uint32_t tmp = obj->CR2;
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    tmp &= ~UART_CR2_ABRMOD_MASK;
    tmp |= (((uint32_t)(((uint32_t)(autoMode)) << UART_CR2_ABRMOD_SHIFT)) & UART_CR2_ABRMOD_MASK);
    obj->CR2 = tmp;
}

/*! \brief Auto baud rate mode
 *
 *  This bit field can only be written when ABREN = 0 or the UART is disabled (UE=0).
 *       If DATAINV=1 and/or MSBFIRST=1 the patterns must be the same on the line, for example 0xAA for MSBFIRST)
 *
 * \param[in] obj : pointer to UART driver instance
 * \return: uint8_t
 *            00: Measurement of the start bit is used to detect the baud rate.
 *            01: Falling edge to falling edge measurement. (the received frame must start with a single bit = 1 -> Frame = Start10xxxxxx)
 *            10: 0x7F frame detection.
 *            11: 0x55 frame detection
 */
__attribute__((always_inline)) static inline uint8_t UartReg_GetAutoBaudrateMode(const UartRegType *obj)
{
    uint8_t  tRtn      = 0;
    uint32_t tmp = obj->CR2;

    tRtn = ((tmp & UART_CR2_ABRMOD_MASK) >> UART_CR2_ABRMOD_SHIFT) & 0xFF;

    return tRtn;
}

/*! \brief Set Auto baud rate enable or disable
 *
 *  this function enable auto baudrate features
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] enable:
 *            0: Auto baud rate detection is disabled.
 *            1: Auto baud rate detection is enabled.
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_EnableAutoBaudrateFeature(UartRegType *obj, bool enable)
{
    uint32_t tmp = obj->CR2;

    if(enable == true)
    {
        obj->CR2 = ((1ul << UART_CR2_ABREN_SHIFT) | ((~UART_CR2_ABREN_MASK) & tmp));
    }
    else
    {
        obj->CR2 = ((0ul << UART_CR2_ABREN_SHIFT) | ((~UART_CR2_ABREN_MASK) & tmp));
    }
}

/*! \brief Most significant bit first
 *
 *  This bit field can only be written when the UART is disabled (UE=0).
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] mbsFirst:
 *            0: data is transmitted/received with data bit 0 first, following the start bit.
 *            1: data is transmitted/received with the MSB (bit 7/8/9) first, following the start bit.
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SetFirstBitShift(UartRegType *obj, uint8_t mbsFirst)
{
    uint32_t tmp = obj->CR2;
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    tmp &= ~UART_CR2_MSBFIRST_MASK;
    tmp |= (((uint32_t)(((uint32_t)(mbsFirst)) << UART_CR2_MSBFIRST_SHIFT)) & UART_CR2_MSBFIRST_MASK);
    obj->CR2 = tmp;
}

/*! \brief Binary data inversion
 *
 *  This bit field can only be written when the UART is disabled (UE=0).
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] enable:
 *            0: Logical data from the data register are send/received in positive/direct logic. (1=H, 0=L)
 *            1: Logical data from the data register are send/received in negative/inverse logic. (1=L, 0=H). The parity bit is also inverted.
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_EnableDataInverteFeature(UartRegType *obj, bool enable)
{
    uint32_t tmp = obj->CR2;

    if(enable == true)
    {
        obj->CR2 = ((1ul << UART_CR2_DATAINV_SHIFT) | ((~UART_CR2_DATAINV_MASK) & tmp));
    }
    else
    {
        obj->CR2 = ((0ul << UART_CR2_DATAINV_SHIFT) | ((~UART_CR2_DATAINV_MASK) & tmp));
    }
}

/*! \brief TX pin active level inversion
 *
 *  This bit field can only be written when the UART is disabled (UE=0).
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] enable:
 *            0: TX pin signal works using the standard logic levels (VDD =1/idle, Gnd=0/mark)
 *            1: TX pin signal values are inverted. (VDD =0/mark, Gnd=1/idle). This allows the use of an external inverter on the TX line.
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_EnableTxInverteFeature(UartRegType *obj, bool enable)
{
    uint32_t tmp = obj->CR2;

    if(enable == true)
    {
        obj->CR2 = ((1ul << UART_CR2_TXINV_SHIFT) | ((~UART_CR2_TXINV_MASK) & tmp));
    }
    else
    {
        obj->CR2 = ((0ul << UART_CR2_TXINV_SHIFT) | ((~UART_CR2_TXINV_MASK) & tmp));
    }
}

/*! \brief RX pin active level inversion
 *
 *  This bit field can only be written when the UART is disabled (UE=0).
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] enable:
 *            0: RX pin signal works using the standard logic levels (VDD =1/idle, Gnd=0/mark)
 *            1: RX pin signal values are inverted. (VDD =0/mark, Gnd=1/idle). This allows the use of an external inverter on the RX line.
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_EnableRxInverteFeature(UartRegType *obj, bool enable)
{
    uint32_t tmp = obj->CR2;

    if(enable == true)
    {
        obj->CR2 = ((1ul << UART_CR2_RXINV_SHIFT) | ((~UART_CR2_RXINV_MASK) & tmp));
    }
    else
    {
        obj->CR2 = ((0ul << UART_CR2_RXINV_SHIFT) | ((~UART_CR2_RXINV_MASK) & tmp));
    }
}

/*! \brief LIN baud rate auto detect feature enable or disable
 *
 *  this function is used only in lin mode, after LIN BREAK successfully detected. If baud rate detection fails, it restarts from LIN BREAK detection.
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] enable:
 *            0: Baud rate detection is not auto enabled by hardware
 *            1: Baud rate detection is auto enabled by hardware
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_EnableLineBaudrateAutoDetectFeature(UartRegType *obj, bool enable)
{
    uint32_t tmp = obj->CR2;

    if(enable == true)
    {
        obj->CR2 = ((1ul << UART_CR2_LIN_BDSYNC_SHIFT) | ((~UART_CR2_LIN_BDSYNC_MASK) & tmp));
    }
    else
    {
        obj->CR2 = ((0ul << UART_CR2_LIN_BDSYNC_SHIFT) | ((~UART_CR2_LIN_BDSYNC_MASK) & tmp));
    }
}

/*! \brief LIN baud rate auto detect feature enable or disable
 *
 *  this function is get whether the lin baudrate auto detected feature is enabled or not
 *
 * \param[in] obj : pointer to UART driver instance
 * \return: bool:
 *            0: Baud rate detection is not auto enabled by hardware
 *            1: Baud rate detection is auto enabled by hardware
 */
__attribute__((always_inline)) static inline bool UartReg_GetLinBaudrateAutoDetectIsEnabled(const UartRegType *obj)
{
    bool     tRtn      = false;
    uint32_t tmp = obj->CR2;

    if((tmp & UART_CR2_LIN_BDSYNC_MASK) != 0u)
    {
        tRtn = true;
    }

    return tRtn;
}

/*! \brief LIN feature enable or disable
 *
 *  this function is used only in lin mode
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] enable:
 *            0: LIN break detect disabled
 *            1: LIN break detect enabled
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_EnableLineBreakDetectFeature(UartRegType *obj, bool enable)
{
    uint32_t tmp = obj->CR2;

    if(enable == true)
    {
        obj->CR2 = ((1ul << UART_CR2_LINEN_SHIFT) | ((~UART_CR2_LINEN_MASK) & tmp));
    }
    else
    {
        obj->CR2 = ((0ul << UART_CR2_LINEN_SHIFT) | ((~UART_CR2_LINEN_MASK) & tmp));
    }
}

/*! \brief Get break synect detected enable status
 *
 *   this function get the lin break detected features tha is enable or disbale
 *
 * \param[in] obj : pointer to UART driver instance
 * \return: bool
 *          0: LIN break detect disabled
 *          1: LIN break detect enabled
 */
__attribute__((always_inline)) static inline bool UartReg_GetLinBreakDetecteEnable(const UartRegType *obj)
{
    bool tRtn = false;

    if((obj->CR2 & UART_CR2_LINEN_MASK) != 0u)
    {
        tRtn = true;
    }

    return tRtn;
}

/*! \brief These bits are used for programming the stop bits.
 *
 *  This bit field can only be written when the UART is disabled (UE=0).
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] stopBitsNum:
 *            0: 1 stop bit
 *            1: 2 stop bits
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SetStopBitNums(UartRegType *obj, uint8_t stopBitsNum)
{
    uint32_t tmp = obj->CR2;
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    tmp &= ~UART_CR2_STOP_MASK;
    tmp |= (((uint32_t)(((uint32_t)(stopBitsNum)) << UART_CR2_STOP_SHIFT)) & UART_CR2_STOP_MASK);
    obj->CR2 = tmp;
}

/*! \brief Configures the number of idle characters that must be received before the IDLE flag is set.
 *
 *  This bit field can only be written when the UART is disabled (UE=0).
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] idleCfg:
 *            000b : 1 idle character
 *            001b : 2 idle characters
 *            010b : 4 idle characters
 *            011b : 8 idle characters
 *            100b : 16 idle characters
 *            101b : 32 idle characters
 *            110b : 64 idle characters
 *            111b : 128 idle characters
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SetIdleConfig(UartRegType *obj, uint8_t idleCfg)
{
    uint32_t tmp = obj->CR2;
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    tmp &= ~UART_CR2_IDLECFG_MASK;
    tmp |= (((uint32_t)(((uint32_t)(idleCfg)) << UART_CR2_IDLECFG_SHIFT)) & UART_CR2_IDLECFG_MASK);
    obj->CR2 = tmp;
}

/*! \brief LIN break detection done interrupt enable
 *
 *  this function set lin break signal detected to trigger one interrupt request
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] enable:
 *            0: Interrupt is inhibited
 *            1: An interrupt is generated whenever LBDT_DONE=1 in the ISR register
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SetLinBreakDetectedIsr(UartRegType *obj, bool enable)
{
    uint32_t tmp = obj->CR2;

    if(enable == true)
    {
        obj->CR2 = ((1ul << UART_CR2_LBDTIE_SHIFT) | ((~UART_CR2_LBDTIE_MASK) & tmp));
    }
    else
    {
        obj->CR2 = ((0ul << UART_CR2_LBDTIE_SHIFT) | ((~UART_CR2_LBDTIE_MASK) & tmp));
    }
}

/*! \brief Get the LinBreakDetectedIsr enable status
 *
 * Readout the current Interrupt enable is active or not
 *
 * \param[in] obj : pointer to UART driver instance
 * \return: bool
 *          true: Enabled
 *          false: Disabled
 */
__attribute__((always_inline)) static inline bool UartReg_GetLinBreakDetectedIsrIsEnabled(const UartRegType *obj)
{
    bool isEnabled = false;

    if((obj->CR2 & UART_CR2_LBDTIE_MASK) != 0u)
    {
        isEnabled = true;
    }

    return isEnabled;
}

/*! \brief LIN synch break detect length
 *
 *  This bit field can only be written when the UART is disabled (UE=0).
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] breakLen:
 *            00: 11bit
 *            01: 12bit
 *            10: 13bit
 *            11: 11bit
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SetLinSyncBreakDetectLen(UartRegType *obj, uint8_t breakLen)
{
    uint32_t tmp = obj->CR2;
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    tmp &= ~UART_CR2_LBDL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(breakLen)) << UART_CR2_LBDL_SHIFT)) & UART_CR2_LBDL_MASK);
    obj->CR2 = tmp;
}

/*! \brief This bit is for selection between 4-bit address detection or 7-bit address detection.
 *
 *  This bit can only be written when the UART is disabled (UE=0)
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] addressSelection:
 *            0: 4-bit address detection
 *            1: 7-bit address detection (in 8-bit data mode)
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SetAddreDetectMode(UartRegType *obj, uint8_t addressSelection)
{
    uint32_t tmp = obj->CR2;
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    tmp &= ~UART_CR2_ADDM_MASK;
    tmp |= (((uint32_t)(((uint32_t)(addressSelection)) << UART_CR2_ADDM_SHIFT)) & UART_CR2_ADDM_MASK);
    obj->CR2 = tmp;
}

/*! \brief Config Transmiting LIN Delimitor Width
 *
 *  This bit field can only be written when the UART is disabled (UE=0).
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] delimitorWidth:
 *            0 : 1 bit
 *            1 : 2 bits
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SetLinDelimitorWidth(UartRegType *obj, uint8_t delimitorWidth)
{
    uint32_t tmp = obj->CR2;
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    tmp &= ~UART_CR2_SDEL_LEN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(delimitorWidth)) << UART_CR2_SDEL_LEN_SHIFT)) & UART_CR2_SDEL_LEN_MASK);
    obj->CR2 = tmp;
}

/*! \brief Config Transmiting synch break Width
 *
 *  This bit field can only be written when the UART is disabled (UE=0).
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] syncBreakLen:
 *            00b : 13 bits
 *            01b : 14 bits
 *            10b : 15 bits
 *            11b : 13 bits
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SetTxLinSyncBreakWidth(UartRegType *obj, uint8_t syncBreakLen)
{
    uint32_t tmp = obj->CR2;
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    tmp &= ~UART_CR2_SBRK_LEN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(syncBreakLen)) << UART_CR2_SBRK_LEN_SHIFT)) & UART_CR2_SBRK_LEN_MASK);
    obj->CR2 = tmp;
}

/*! \brief Driver enable polarity selection
 *
 *  This bit can only be written when the UART is disabled (UE=0).
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] deInActiveIsLowEn:
 *            0: DE signal is active high.
 *            1: DE signal is active low.
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SetDriverPolarity(UartRegType *obj, bool deInActiveIsLowEn)
{
    uint32_t tmp = obj->CR3;

    if(deInActiveIsLowEn == true)
    {
        obj->CR3 = ((1ul << UART_CR3_DEP_SHIFT) | ((~UART_CR3_DEP_MASK) & tmp));
    }
    else
    {
        obj->CR3 = ((0ul << UART_CR3_DEP_SHIFT) | ((~UART_CR3_DEP_MASK) & tmp));
    }
}

/*! \brief This bit allows the user to activate the external transceiver control, through the DE signal
 *
 *  This bit can only be written when the UART is disabled (UE=0).
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] enable:
 *            0: DE function is disabled.
 *            1: DE function is enabled. The DE signal is output on the RTS pin.
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SetDriverEnableMode(UartRegType *obj, bool enable)
{
    uint32_t tmp = obj->CR3;

    if(enable == true)
    {
        obj->CR3 = ((1ul << UART_CR3_DEM_SHIFT) | ((~UART_CR3_DEM_MASK) & tmp));
    }
    else
    {
        obj->CR3 = ((0ul << UART_CR3_DEM_SHIFT) | ((~UART_CR3_DEM_MASK) & tmp));
    }
}

/*! \brief This bit allows the user to select the sample method
 *
 *  This bit can only be written when the UART is disabled (UE=0). ONEBIT feature applies only to data bits, It does not apply to Start bit.
 *       When the one sample bit method is selected the noise detection flag (NF) is disabled.
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] sampleBitMethod:
 *            0: Three sample bit method
 *            1: One sample bit method
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SetSampleBitMethod(UartRegType *obj, uint8_t sampleBitMethod)
{
    uint32_t tmp = obj->CR3;
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    tmp &= ~UART_CR3_ONEBIT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(sampleBitMethod)) << UART_CR3_ONEBIT_SHIFT)) & UART_CR3_ONEBIT_MASK);
    obj->CR3 = tmp;
}

/*! \brief CTS interrupt enable
 *
 *  this function set the cts interrupt request, but only in rs232 mode
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] enable:
 *            0: Interrupt is inhibited
 *            1: An interrupt is generated whenever CTSIF=1 in the ISR register
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SetCtsIsr(UartRegType *obj, bool enable)
{
    uint32_t tmp = obj->CR3;

    if(enable == true)
    {
        obj->CR3 = ((1ul << UART_CR3_CTSIE_SHIFT) | ((~UART_CR3_CTSIE_MASK) & tmp));
    }
    else
    {
        obj->CR3 = ((0ul << UART_CR3_CTSIE_SHIFT) | ((~UART_CR3_CTSIE_MASK) & tmp));
    }
}

/*! \brief Get the CtsIsr enable status
 *
 * Readout the current Interrupt enable is active or not
 *
 * \param[in] obj : pointer to UART driver instance
 * \return: bool
 *          true: Enabled
 *          false: Disabled
 */
__attribute__((always_inline)) static inline bool UartReg_GetCtsIsrIsEnabled(const UartRegType *obj)
{
    bool isEnabled = false;

    if((obj->CR3 & UART_CR3_CTSIE_MASK) != 0u)
    {
        isEnabled = true;
    }

    return isEnabled;
}

/*! \brief CTS enable
 *
 *  This bit can only be written when the UART is disabled (UE=0)
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] enable:
 *            0: CTS hardware flow control disabled
 *            1: CTS mode enabled, data is only transmitted when the CTS input
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_EnableCts(UartRegType *obj, bool enable)
{
    uint32_t tmp = obj->CR3;

    if(enable == true)
    {
        obj->CR3 = ((1ul << UART_CR3_CTSE_SHIFT) | ((~UART_CR3_CTSE_MASK) & tmp));
    }
    else
    {
        obj->CR3 = ((0ul << UART_CR3_CTSE_SHIFT) | ((~UART_CR3_CTSE_MASK) & tmp));
    }
}

/*! \brief RTS enable or disable
 *
 *  This bit can only be written when the UART is disabled (UE=0).
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] enable:
 *            0: RTS hardware flow control disabled
 *            1: RTS output enabled, data is only requested when there is space in the receive buffer
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_EnableRts(UartRegType *obj, bool enable)
{
    uint32_t tmp = obj->CR3;

    if(enable == true)
    {
        obj->CR3 = ((1ul << UART_CR3_RTSE_SHIFT) | ((~UART_CR3_RTSE_MASK) & tmp));
    }
    else
    {
        obj->CR3 = ((0ul << UART_CR3_RTSE_SHIFT) | ((~UART_CR3_RTSE_MASK) & tmp));
    }
}

/*! \brief DMA enable transmitter
 *
 *  this function set the tx data used DMA mode
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] enable:
 *            0: DMA mode is disabled for transmission
 *            1: DMA mode is enabled for transmission
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_EnableTxDMA(UartRegType *obj, bool enable)
{
    uint32_t tmp = obj->CR3;

    if(enable == true)
    {
        obj->CR3 = ((1ul << UART_CR3_DMAT_SHIFT) | ((~UART_CR3_DMAT_MASK) & tmp));
    }
    else
    {
        obj->CR3 = ((0ul << UART_CR3_DMAT_SHIFT) | ((~UART_CR3_DMAT_MASK) & tmp));
    }
}

/*! \brief DMA enable receiver
 *
 *  This function set the received data used DMA
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] enable:
 *            0: DMA mode is disabled for reception
 *            1: DMA mode is enabled for reception
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_EnableRxDMA(UartRegType *obj, bool enable)
{
    uint32_t tmp = obj->CR3;

    if(enable == true)
    {
        obj->CR3 = ((1ul << UART_CR3_DMAR_SHIFT) | ((~UART_CR3_DMAR_MASK) & tmp));
    }
    else
    {
        obj->CR3 = ((0ul << UART_CR3_DMAR_SHIFT) | ((~UART_CR3_DMAR_MASK) & tmp));
    }
}

/*! \brief Half-duplex selection
 *
 *  This bit can only be written when the UART is disabled (UE=0). If LOOPS and HDSEL are both 1, HDSEL is invalid.
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] enable:
 *            0: Half duplex mode is not selected
 *            1: Half duplex mode is selected
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SetHalfDuplex(UartRegType *obj, bool enable)
{
    uint32_t tmp = obj->CR3;

    if(enable == true)
    {
        obj->CR3 = ((1ul << UART_CR3_HDSEL_SHIFT) | ((~UART_CR3_HDSEL_MASK) & tmp));
    }
    else
    {
        obj->CR3 = ((0ul << UART_CR3_HDSEL_SHIFT) | ((~UART_CR3_HDSEL_MASK) & tmp));
    }
}

/*! \brief Loop Mode Selec
 *
 *  This bit can only be written when the UART is disabled (UE=0). If LOOPS and HDSEL are both 1, HDSEL is invalid.
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] enable:
 *            0: Normal operation - RXD and TXD use separate pins.
 *            1: Loop mode mode where transmitter outputs are internally connected to receiver input.
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SetLoopsMode(UartRegType *obj, bool enable)
{
    uint32_t tmp = obj->CR3;

    if(enable == true)
    {
        obj->CR3 = ((1ul << UART_CR3_LOOPS_SHIFT) | ((~UART_CR3_LOOPS_MASK) & tmp));
    }
    else
    {
        obj->CR3 = ((0ul << UART_CR3_LOOPS_SHIFT) | ((~UART_CR3_LOOPS_MASK) & tmp));
    }
}

/*! \brief Error Interrupt Enable
 *
 *  Error Interrupt Enable bit is required to enable interrupt generation in case of a framing error,
 *       overrun error or noise flag (FE=1 or ORE=1 or NF=1 in the ISR register).
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] enable:
 *            0: Interrupt is inhibited
 *            1: An interrupt is generated when FE=1 or ORE=1 or NF=1 in the ISR register.
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SetErrIsr(UartRegType *obj, bool enable)
{
    uint32_t tmp = obj->CR3;

    if(enable == true)
    {
        obj->CR3 = ((1ul << UART_CR3_EIE_SHIFT) | ((~UART_CR3_EIE_MASK) & tmp));
    }
    else
    {
        obj->CR3 = ((0ul << UART_CR3_EIE_SHIFT) | ((~UART_CR3_EIE_MASK) & tmp));
    }
}

/*! \brief Get the Error Interrupt enable status
 *
 * Readout the current Error Interrupt enable is active or not
 *
 * \param[in] obj : pointer to UART driver instance
 * \return: bool
 *          true: Enabled
 *          false: Disabled
 */
__attribute__((always_inline)) static inline bool UartReg_GetErrIsrIsEnabled(const UartRegType *obj)
{
    bool isEnabled = false;

    if((obj->CR3 & UART_CR3_EIE_MASK) != 0u)
    {
        isEnabled = true;
    }

    return isEnabled;
}

/*! \brief Send break done clear flag
 *
 * Writing 1 to this bit clears the SBRKD flag in the ISR register.
 *
 * \param[in] obj : pointer to UART driver instance
 * \return void
 */
__attribute__((always_inline)) static inline void UartReg_ClearTxBreakDoneFlag(UartRegType *obj)
{
    obj->ICR |= UART_ICR_SBRKDCF_MASK;
    /* Read back to avoid problem */
    (void)obj->ICR;
}

/*! \brief Receiver timeout clear flag
 *
 * Writing 1 to this bit clears the RTOF flag in the ISR register.
 *
 * \param[in] obj : pointer to UART driver instance
 * \return void
 */
__attribute__((always_inline)) static inline void UartReg_ClearRxTimeoutFlag(UartRegType *obj)
{
    obj->ICR |= UART_ICR_RTOCF_MASK;
    /* Read back to avoid problem */
    (void)obj->ICR;
}

/*! \brief CTS clear flag
 *
 * Writing 1 to this bit clears the CTSIF flag in the ISR register.
 *
 * \param[in] obj : pointer to UART driver instance
 * \return void
 */
__attribute__((always_inline)) static inline void UartReg_ClearCtsFlag(UartRegType *obj)
{
    obj->ICR |= UART_ICR_CTSCF_MASK;
    /* Read back to avoid problem */
    (void)obj->ICR;
}

/*! \brief LIN break detection result (LBDT_DONE and LBDT_FAIL) clear flag
 *
 * Writing 1 to this bit clears the LBDT_DONE and LBDT_FAIL flag in the ISR register.
 *
 * \param[in] obj : pointer to UART driver instance
 * \return void
 */
__attribute__((always_inline)) static inline void UartReg_ClearLinBreakDetectedResultFlag(UartRegType *obj)
{
    obj->ICR |= UART_ICR_LBDTCF_MASK;
    /* Read back to avoid problem */
    (void)obj->ICR;
}

/*! \brief Transmission complete clear flag
 *
 * Writing 1 to this bit clears the TC flag in the ISR register.
 *
 * \param[in] obj : pointer to UART driver instance
 * \return void
 */
__attribute__((always_inline)) static inline void UartReg_ClearTxCompletedFlag(UartRegType *obj)
{
    obj->ICR |= UART_ICR_TCCF_MASK;
    /* Read back to avoid problem */
    (void)obj->ICR;
}

/*! \brief Idle line detected clear flag
 *
 * Writing 1 to this bit clears the IDLE flag in the ISR register.
 *
 * \param[in] obj : pointer to UART driver instance
 * \return void
 */
__attribute__((always_inline)) static inline void UartReg_ClearIdlelineDetectedFlag(UartRegType *obj)
{
    obj->ICR |= UART_ICR_IDLECF_MASK;
    /* Read back to avoid problem */
    (void)obj->ICR;
}

/*! \brief Overrun error clear flag
 *
 * Writing 1 to this bit clears the ORE flag in the ISR register.
 *
 * \param[in] obj : pointer to UART driver instance
 * \return void
 */
__attribute__((always_inline)) static inline void UartReg_ClearOverRunnErrFlag(UartRegType *obj)
{
    obj->ICR |= UART_ICR_ORECF_MASK;
    /* Read back to avoid problem */
    (void)obj->ICR;
}

/*! \brief Noise detected clear flag
 *
 * Writing 1 to this bit clears the NE flag in the ISR register.
 *
 * \param[in] obj : pointer to UART driver instance
 * \return void
 */
__attribute__((always_inline)) static inline void UartReg_ClearNoiseDetectedFlag(UartRegType *obj)
{
    obj->ICR |= UART_ICR_NCF_MASK;
    /* Read back to avoid problem */
    (void)obj->ICR;
}

/*! \brief Framing error clear flag
 *
 * Writing 1 to this bit clears the FE flag in the ISR register.
 *
 * \param[in] obj : pointer to UART driver instance
 * \return void
 */
__attribute__((always_inline)) static inline void UartReg_ClearFrameErrFlag(UartRegType *obj)
{
    obj->ICR |= UART_ICR_FECF_MASK;
    /* Read back to avoid problem */
    (void)obj->ICR;
}

/*! \brief Parity error clear flag
 *
 * Writing 1 to this bit clears the PE flag in the ISR register.
 *
 * \param[in] obj : pointer to UART driver instance
 * \return void
 */
__attribute__((always_inline)) static inline void UartReg_ClearParityErrFlag(UartRegType *obj)
{
    obj->ICR |= UART_ICR_PECF_MASK;
    /* Read back to avoid problem */
    (void)obj->ICR;
}

/*! \brief Baud Rate Regiter
 *
 *  This register can only be written when the UART is disabled (UE=0),
 *       It may be automatically updated by hardware in auto baud rate detection mode.
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] brr:
 *            BRR[15:4] = UARTDIV[15:4]
 *            When OVER8 = 0, BRR[3:0] = UARTDIV[3:0].
 *            When OVER8 = 1: BRR[2:0] = UARTDIV[3:0] shifted 1 bit to the right. BRR[3] must be kept cleared.
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SetBaudRate(UartRegType *obj, uint16_t brr)
{
    uint32_t tmp = obj->BRR;
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    tmp &= ~UART_BRR_BRR_MASK;
    tmp |= (((uint32_t)(((uint32_t)(brr)) << UART_BRR_BRR_SHIFT)) & UART_BRR_BRR_MASK);
    obj->BRR = tmp;
}

/*! \brief LIN baud rate receiver timeout value
 *
 *  This bit-field configures LIN sync byte field timeout threshold.When LIN_BDSYNC=1 and LINEN=1,
 *  if baud rate adjustment does not finish within the timeout threshold, hardware regards it as fail and
 *  restart from LIN break detection. Timeout is based on number of bits, counted by baud rate of last frame
 *  (not affected by current baud rate adjustment).  When LIN_BDSYNC=0 or LINEN=0, baud rate timeout is not enabled.
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] timeout: Receiver timeout value
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SetLinBaudrateRxTimeout(UartRegType *obj, uint32_t timeout)
{
    uint32_t tmp = obj->RTOR;
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    tmp &= ~UART_RTOR_LIN_BDRTO_MASK;
    tmp |= (((uint32_t)(((uint32_t)(timeout)) << UART_RTOR_LIN_BDRTO_SHIFT)) & UART_RTOR_LIN_BDRTO_MASK);
    obj->RTOR = tmp;
}

/*! \brief This bit-field gives the Receiver timeout value in terms of number of bit duration.
 *
 *  This value must only be programmed once per received character.
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] timeout: Receiver timeout value
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SetRxTimeout(UartRegType *obj, uint32_t timeout)
{
    uint32_t tmp = obj->RTOR;
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    tmp &= ~UART_RTOR_RTO_MASK;
    tmp |= (((uint32_t)(((uint32_t)(timeout)) << UART_RTOR_RTO_SHIFT)) & UART_RTOR_RTO_MASK);
    obj->RTOR = tmp;
}

/*! \brief Mute mode request
 *
 *  Writing 1 to this bit puts the UART in mute mode and sets the RWU flag.
 *
 * \param[in] obj : pointer to UART driver instance
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_ReqMuteMode(UartRegType *obj)
{
    uint32_t tmp = obj->RQR;

    obj->RQR = ((1ul << UART_RQR_MMRQ_SHIFT) | ((~UART_RQR_MMRQ_MASK) & tmp));
}

/*! \brief Send break request
 *
 * In the case the application needs to send the break character following all previously inserted data,
 *        including the ones not yet transmitted, the software should wait for the TXEMPT flag assertion before setting the SBRKRQ bit.
 *
 * \param[in] obj : pointer to UART driver instance
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_ReqTxBreak(UartRegType *obj)
{
    uint32_t tmp = obj->RQR;

    obj->RQR = ((1ul << UART_RQR_SBRKRQ_SHIFT) | ((~UART_RQR_SBRKRQ_MASK) & tmp));
}

/*! \brief Auto baud rate request
 *
 *  Writing 1 to this bit resets the ABRF flag in the ISR and request an automatic baud rate measurement on the next received data frame.
 *
 * \param[in] obj : pointer to UART driver instance
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_ReqAutoBaudRate(UartRegType *obj)
{
    uint32_t tmp = obj->RQR;

    obj->RQR = ((1ul << UART_RQR_ABRRQ_SHIFT) | ((~UART_RQR_ABRRQ_MASK) & tmp));
}

/*! \brief Transmit data
 *
 * Note: Contains the data character to be transmitted. When transmitting with the parity enabled (PCE bit set to 1 in the CR1 register),
 *       the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect because it is replaced by the parity
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] txData : the tx data value
 * \return void
 */
__attribute__((always_inline)) static inline void UartReg_TxData(UartRegType *obj, uint16_t txData)
{
    uint32_t tmp = obj->TDR;
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    tmp &= ~UART_TDR_TDR_MASK;
    tmp |= (((uint32_t)(((uint32_t)(txData)) << UART_TDR_TDR_SHIFT)) & UART_TDR_TDR_MASK);
    obj->TDR = tmp;
}

/*! \brief Transmit Buffer/FIFO Empty
 *
 *  this function get the current tx buffer is empty or not
 *
 * \param[in] obj : pointer to UART driver instance
 * \return: uint8_t
 *          0b : Transmit buffer is not empty.
 *          1b : Transmit buffer is empty.
 */
__attribute__((always_inline)) static inline uint8_t UartReg_GetTxBufferIsEmpty(const UartRegType *obj)
{
    uint8_t tRtn = 0;

    tRtn = (((obj->FIFO & UART_FIFO_TXEMPT_MASK) >> UART_FIFO_TXEMPT_SHIFT) & 0xFF);

    return tRtn;
}

/*! \brief Receive Buffer/FIFO Empty
 *
 *  this function get the current rx buffer is empty or not
 *
 * \param[in] obj : pointer to UART driver instance
 * \return: uint8_t
 *          0b : Receive buffer is not empty.
 *          1b : Receive buffer is empty.
 */
__attribute__((always_inline)) static inline uint8_t UartReg_GetRxBufferIsEmpty(const UartRegType *obj)
{
    uint8_t tRtn = 0;

    tRtn = (((obj->FIFO & UART_FIFO_RXEMPT_MASK) >> UART_FIFO_RXEMPT_SHIFT) & 0xFF);

    return tRtn;
}

/*! \brief Get Transmitter Buffer Overflow Flag
 *
 *  Indicates that more data has been written to the transmit buffer than it can hold. This field asserts regardless of the value of TXOFE. However,
 *       an interrupt is issued to the host only if TXOFE is set.
 *
 * \param[in] obj : pointer to UART driver instance
 * \return: uint8_t
 *          0b : No transmit buffer overflow has occurred since the last time the flag was cleared.
 *          1b : At least one transmit buffer overflow has occurred since the last time the flag was cleared.
 */
__attribute__((always_inline)) static inline uint8_t UartReg_GetTxOverflowFlag(const UartRegType *obj)
{
    uint8_t tRtn = 0;

    tRtn = (((obj->FIFO & UART_FIFO_TXOF_MASK) >> UART_FIFO_TXOF_SHIFT) & 0xFF);

    return tRtn;
}

/*! \brief Clear Transmitter Buffer Overflow Flag
 *
 *  This flag is cleared by writing a 1.
 *
 * \param[in] obj : pointer to UART driver instance
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_ClearTxOverflowFlag(UartRegType *obj)
{
    obj->FIFO |= UART_FIFO_TXOF_MASK;
    /* Read back to avoid problem */
    (void)obj->FIFO;
}

/*! \brief Get Receiver Buffer Underflow Flag
 *
 *  This flag is cleared by writing a 1.
 *
 * \param[in] obj : pointer to UART driver instance
 * \return: uint8_t
 *          0b : No receive buffer underflow has occurred since the last time the flag was cleared.
 *          1b : At least one receive buffer underflow has occurred since the last time the flag was cleared.
 */
__attribute__((always_inline)) static inline uint8_t UartReg_GetRxUnderflowFlag(const UartRegType *obj)
{
    uint8_t tRtn = 0;

    tRtn = (((obj->FIFO & UART_FIFO_RXUF_MASK) >> UART_FIFO_RXUF_SHIFT) & 0xFF);

    return tRtn;
}

/*! \brief Clear Receiver Buffer Underflow Flag
 *
 *  Indicates that more data has been read from the receive buffer than was present. This field asserts regardless of the value of RXUFE. However,
 *       an interrupt is issued to the host only if RXUFE is setThis flag is cleared by writing a 1.
 *
 * \param[in] obj : pointer to UART driver instance
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_ClearRxUnderflowFlag(UartRegType *obj)
{
    obj->FIFO |= UART_FIFO_RXUF_MASK;
    /* Read back to avoid problem */
    (void)obj->FIFO;
}

/*! \brief Transmit FIFO/Buffer Flush
 *
 *  Set and cleared by software. When using this bit, it is recommended this bit is high for at least three clock cycles.
 *
 * \param[in] obj : pointer to UART driver instance
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_FlushTxFifo(UartRegType *obj)
{
    uint32_t tmp = obj->FIFO;

    obj->FIFO = ((1ul << UART_FIFO_TXFLUSH_SHIFT) | ((~UART_FIFO_TXFLUSH_MASK) & tmp));

    __asm volatile("nop");
    __asm volatile("nop");
    __asm volatile("nop");
    __asm volatile("nop");

    obj->FIFO = ((0ul << UART_FIFO_TXFLUSH_SHIFT) | ((~UART_FIFO_TXFLUSH_MASK) & tmp));
}

/*! \brief Receiver FIFO/Buffer Flush
 *
 *  Set and cleared by software. When using this bit, it is recommended this bit is high for at least three clock cycles.
 *
 * \param[in] obj : pointer to UART driver instance
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_FlushRxFifo(UartRegType *obj)
{
    uint32_t tmp = obj->FIFO;

    obj->FIFO = ((1ul << UART_FIFO_RXFLUSH_SHIFT) | ((~UART_FIFO_RXFLUSH_MASK) & tmp));

    __asm volatile("nop");
    __asm volatile("nop");
    __asm volatile("nop");
    __asm volatile("nop");

    obj->FIFO = ((0ul << UART_FIFO_RXFLUSH_SHIFT) | ((~UART_FIFO_RXFLUSH_MASK) & tmp));
}

/*! \brief Transmit FIFO Overflow Interrupt Enable
 *
 *  When this field is set, the TXOF flag generates an interrupt to the host.
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] enable:
 *            0b : TXOF flag does not generate an interrupt to the host.
 *            1b : TXOF flag generates an interrupt to the host.
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SetTxOverflowIsr(UartRegType *obj, bool enable)
{
    uint32_t tmp = obj->FIFO;

    if(enable == true)
    {
        obj->FIFO = ((1ul << UART_FIFO_TXOFE_SHIFT) | ((~UART_FIFO_TXOFE_MASK) & tmp));
    }
    else
    {
        obj->FIFO = ((0ul << UART_FIFO_TXOFE_SHIFT) | ((~UART_FIFO_TXOFE_MASK) & tmp));
    }
}

/*! \brief Get the TxOverflowIsr enable status
 *
 * Readout the current Interrupt enable is active or not
 *
 * \param[in] obj : pointer to UART driver instance
 * \return: bool
 *          true: Enabled
 *          false: Disabled
 */
__attribute__((always_inline)) static inline bool UartReg_GetTxOverflowIsrIsEnabled(const UartRegType *obj)
{
    bool isEnabled = false;

    if((obj->FIFO & UART_FIFO_TXOFE_MASK) != 0u)
    {
        isEnabled = true;
    }

    return isEnabled;
}

/*! \brief Receive FIFO Underflow Interrupt Enable
 *
 *  When this field is set, the RXUF flag generates an interrupt to the host.
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] enable:
 *            0b : No receive buffer underflow has occurred since the last time the flag was cleared.
 *            1b : At least one receive buffer underflow has occurred since the last time the flag was cleared.
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SetRxUnderflowIsr(UartRegType *obj, bool enable)
{
    uint32_t tmp = obj->FIFO;

    if(enable == true)
    {
        obj->FIFO = ((1ul << UART_FIFO_RXUFE_SHIFT) | ((~UART_FIFO_RXUFE_MASK) & tmp));
    }
    else
    {
        obj->FIFO = ((0ul << UART_FIFO_RXUFE_SHIFT) | ((~UART_FIFO_RXUFE_MASK) & tmp));
    }
}

/*! \brief Get the RxUnderflowIsr enable status
 *
 * Readout the current Interrupt enable is active or not
 *
 * \param[in] obj : pointer to UART driver instance
 * \return: bool
 *          true: Enabled
 *          false: Disabled
 */
__attribute__((always_inline)) static inline bool UartReg_GetRxUnderflowIsrIsEnabled(const UartRegType *obj)
{
    bool isEnabled = false;

    if((obj->FIFO & UART_FIFO_RXUFE_MASK) != 0u)
    {
        isEnabled = true;
    }

    return isEnabled;
}

/*! \brief The value in this register indicates the number of datawords that are in the receive FIFO/buffer
 *
 *  If a dataword is being received, that is, in the receive shift register, it is not included in the count.
 *       This value may be used to calculate how much room is left in the receive FIFO/buffer.
 *
 * \param[in] obj : pointer to UART driver instance
 * \return: Receive Counter
 */
__attribute__((always_inline)) static inline uint8_t UartReg_GetRxCounter(const UartRegType *obj)
{
    uint8_t tRxCnt = 0;

    tRxCnt = (((obj->WATER & UART_WATER_RXCOUNT_MASK) >> UART_WATER_RXCOUNT_SHIFT) & 0xFF);

    return tRxCnt;
}

/*! \brief When the number of datawords in the receive FIFO/buffer is greater than the value in this register field,
 *         an interrupt or a DMA request is generated.
 *
 *  These 2 bits can only be written when the UART is disabled (UE=0)
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] rxWater: Receive Watermark
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SetRxWater(UartRegType *obj, uint8_t rxWater)
{
    uint32_t tmp = obj->WATER;
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    tmp &= ~UART_WATER_RXWATER_MASK;
    tmp |= (((uint32_t)(((uint32_t)(rxWater)) << UART_WATER_RXWATER_SHIFT)) & UART_WATER_RXWATER_MASK);
    obj->WATER = tmp;
}

/*! \brief The value in this register indicates the number of datawords that are in the receive FIFO/buffer
 *
 *  If a dataword is being transmitted, that is, in the transmit shift register, it is not included in the count.
 *       This value may be used to calculate how much room is left in the transmit FIFO/buffer.
 *
 * \param[in] obj : pointer to UART driver instance
 * \return: Transmit Counter
 */
__attribute__((always_inline)) static inline uint8_t UartReg_GetTxCounter(const UartRegType *obj)
{
    uint8_t tTxCnt = 0;

    tTxCnt = (((obj->WATER & UART_WATER_TXCOUNT_MASK) >> UART_WATER_TXCOUNT_SHIFT) & 0xFF);

    return tTxCnt;
}

/*! \brief When the number of datawords in the transmit FIFO/buffer is equal to or less than the value in this register field,
 *         an interrupt or a DMA request is generated.
 *
 *  These 2 bits can only be written when the UART is disabled (UE=0)
 *
 * \param[in] obj : pointer to UART driver instance
 * \param[in] txWater: Transmit Watermark
 * \return: void
 */
__attribute__((always_inline)) static inline void UartReg_SetTxWater(UartRegType *obj, uint8_t txWater)
{
    uint32_t tmp = obj->WATER;
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    tmp &= ~UART_WATER_TXWATER_MASK;
    tmp |= (((uint32_t)(((uint32_t)(txWater)) << UART_WATER_TXWATER_SHIFT)) & UART_WATER_TXWATER_MASK);
    obj->WATER = tmp;
}

/*! \brief Get Tx water mark
 *
 *  This function get the theshold value to compared with tx counter
 *
 * \param[in] obj : pointer to UART driver instance
 * \return: Transmit Watermark
 */
__attribute__((always_inline)) static inline uint8_t UartReg_GetTxWaterMark(const UartRegType *obj)
{
    uint8_t tTxWaterMark = 0;

    tTxWaterMark = (((obj->WATER & UART_WATER_TXWATER_MASK) >> UART_WATER_TXWATER_SHIFT) & 0xFF);

    return tTxWaterMark;
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _UART_REG_H_ */
