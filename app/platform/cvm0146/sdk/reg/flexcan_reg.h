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

#ifndef _FLEXCAN_REG_H_
#define _FLEXCAN_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the FLEXCAN Registers
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
#define MESSAGE_BUFFER_ADDR_OFF         (0x80UL)

#define MESSAGE_BUFFER_CS_WORD_NUM      (0)
#define MESSAGE_BUFFER_ID_WORD_NUM      (1)

/* message buffer CS field */
#define MESSAGE_BUFFER_CS_EDL_SHIFT     (31U)
#define MESSAGE_BUFFER_CS_EDL_MASK      (0x1UL << MESSAGE_BUFFER_CS_EDL_SHIFT)
#define MESSAGE_BUFFER_CS_BRS_SHIFT     (30U)
#define MESSAGE_BUFFER_CS_BRS_MASK      (0x1UL << MESSAGE_BUFFER_CS_BRS_SHIFT)
#define MESSAGE_BUFFER_CS_CODE_SHIFT    (24U)
#define MESSAGE_BUFFER_CS_CODE_MASK     (0xFUL << MESSAGE_BUFFER_CS_CODE_SHIFT)
#define MESSAGE_BUFFER_CS_SRR_SHIFT     (22U)
#define MESSAGE_BUFFER_CS_SRR_MASK      (0x1UL << MESSAGE_BUFFER_CS_SRR_SHIFT)
#define MESSAGE_BUFFER_CS_IDE_SHIFT     (21U)
#define MESSAGE_BUFFER_CS_IDE_MASK      (0x1UL << MESSAGE_BUFFER_CS_IDE_SHIFT)
#define MESSAGE_BUFFER_CS_RTR_SHIFT     (20)
#define MESSAGE_BUFFER_CS_RTR_MASK      (0x1UL << MESSAGE_BUFFER_CS_RTR_SHIFT)
#define MESSAGE_BUFFER_CS_DLC_SHIFT     (16U)
#define MESSAGE_BUFFER_CS_DLC_MASK      (0xFUL << MESSAGE_BUFFER_CS_DLC_SHIFT)
#define MESSAGE_BUFFER_CS_TS_SHIFT      (0U)
#define MESSAGE_BUFFER_CS_TS_MASK       (0xFFFFUL << MESSAGE_BUFFER_CS_TS_SHIFT)

/* legacy rx fifo cs field */
#define LEGACY_FF_CS_IDHIT_SHIFT        (23U)
#define LEGACY_FF_CS_IDHIT_MASK         (0x1FFUL << LEGACY_FF_CS_IDHIT_SHIFT)
#define LEGACY_FF_CS_SRR_SHIFT          (22U)
#define LEGACY_FF_CS_SRR_MASK           (0x1UL << LEGACY_FF_CS_SRR_SHIFT)
#define LEGACY_FF_CS_IDE_SHIFT          (21U)
#define LEGACY_FF_CS_IDE_MASK           (0x1UL << LEGACY_FF_CS_IDE_SHIFT)
#define LEGACY_FF_CS_RTR_SHIFT          (20)
#define LEGACY_FF_CS_RTR_MASK           (0x1UL << LEGACY_FF_CS_RTR_SHIFT)
#define LEGACY_FF_CS_DLC_SHIFT          (16U)
#define LEGACY_FF_CS_DLC_MASK           (0xFUL << LEGACY_FF_CS_DLC_SHIFT)
#define LEGACY_FF_CS_TS_SHIFT           (0U)
#define LEGACY_FF_CS_TS_MASK            (0xFFFFUL << LEGACY_FF_CS_TS_SHIFT)

/* message buffer ID field */
#define MESSAGE_BUFFER_ID_EXT_ID_SHIFT  (0U)
#define MESSAGE_BUFFER_ID_EXT_ID_MASK   (0x1FFFFFFFUL << MESSAGE_BUFFER_ID_EXT_ID_SHIFT)
#define MESSAGE_BUFFER_ID_STD_ID_SHIFT  (18U)
#define MESSAGE_BUFFER_ID_STD_ID_MASK   (0x7FFUL << MESSAGE_BUFFER_ID_STD_ID_SHIFT)

/* MCR register */
#define FLEXCAN_MCR_MDIS_SHIFT          (31U)
#define FLEXCAN_MCR_MDIS_MASK           (0x1UL << FLEXCAN_MCR_MDIS_SHIFT)
#define FLEXCAN_MCR_MDIS_WIDTH          (1u)
#define FLEXCAN_MCR_FRZ_SHIFT           (30U)
#define FLEXCAN_MCR_FRZ_MASK            (0x1UL << FLEXCAN_MCR_FRZ_SHIFT)
#define FLEXCAN_MCR_FRZ_WIDTH           (1u)
#define FLEXCAN_MCR_RFEN_SHIFT          (29U)
#define FLEXCAN_MCR_RFEN_MASK           (0x1UL << FLEXCAN_MCR_RFEN_SHIFT)
#define FLEXCAN_MCR_RFEN_WIDTH          (1u)
#define FLEXCAN_MCR_HALT_SHIFT          (28U)
#define FLEXCAN_MCR_HALT_MASK           (0x1UL << FLEXCAN_MCR_HALT_SHIFT)
#define FLEXCAN_MCR_HALT_WIDTH          (1u)
#define FLEXCAN_MCR_NOTRDY_SHIFT        (27U)
#define FLEXCAN_MCR_NOTRDY_MASK         (0x1UL << FLEXCAN_MCR_NOTRDY_SHIFT)
#define FLEXCAN_MCR_WAKMSK_SHIFT        (26U)
#define FLEXCAN_MCR_WAKMSK_MASK         (0x1UL << FLEXCAN_MCR_WAKMSK_SHIFT)
#define FLEXCAN_MCR_SOFTRST_SHIFT       (25U)
#define FLEXCAN_MCR_SOFTRST_MASK        (0x1UL << FLEXCAN_MCR_SOFTRST_SHIFT)
#define FLEXCAN_MCR_SOFTRST_WIDTH       (1u)
#define FLEXCAN_MCR_FRZACK_SHIFT        (24U)
#define FLEXCAN_MCR_FRZACK_MASK         (0x1UL << FLEXCAN_MCR_FRZACK_SHIFT)
#define FLEXCAN_MCR_FRZACK_WIDTH        (1u)
#define FLEXCAN_MCR_SUPV_SHIFT          (23U)
#define FLEXCAN_MCR_SUPV_MASK           (0x1UL << FLEXCAN_MCR_SUPV_SHIFT)
#define FLEXCAN_MCR_SUPV_WIDTH          (1u)
#define FLEXCAN_MCR_SLFWAK_SHIFT        (22U)
#define FLEXCAN_MCR_SLFWAK_MASK         (0x1UL << FLEXCAN_MCR_SLFWAK_SHIFT)
#define FLEXCAN_MCR_SLFWAK_WIDTH        (1u)
#define FLEXCAN_MCR_WRNEN_SHIFT         (21U)
#define FLEXCAN_MCR_WRNEN_MASK          (0x1UL << FLEXCAN_MCR_WRNEN_SHIFT)
#define FLEXCAN_MCR_WRNEN_WIDTH         (1u)
#define FLEXCAN_MCR_LPMACK_SHIFT        (20U)
#define FLEXCAN_MCR_LPMACK_MASK         (0x1UL << FLEXCAN_MCR_LPMACK_SHIFT)
#define FLEXCAN_MCR_LPMACK_WIDTH        (1u)
#define FLEXCAN_MCR_WAKSRC_SHIFT        (19U)
#define FLEXCAN_MCR_WAKSRC_MASK         (0x1UL << FLEXCAN_MCR_WAKSRC_SHIFT)
#define FLEXCAN_MCR_WAKSRC_WIDTH        (1u)
#define FLEXCAN_MCR_DOZE_SHIFT          (18U)
#define FLEXCAN_MCR_DOZE_MASK           (0x1UL << FLEXCAN_MCR_DOZE_SHIFT)
#define FLEXCAN_MCR_DOZE_WIDTH          (1u)
#define FLEXCAN_MCR_SRXDIS_SHIFT        (17U)
#define FLEXCAN_MCR_SRXDIS_MASK         (0x1UL << FLEXCAN_MCR_SRXDIS_SHIFT)
#define FLEXCAN_MCR_SRXDIS_WIDTH        (1u)
#define FLEXCAN_MCR_IRQM_SHIFT          (16U)
#define FLEXCAN_MCR_IRQM_MASK           (0x1UL << FLEXCAN_MCR_IRQM_SHIFT)
#define FLEXCAN_MCR_IRMQ_WIDTH          (1u)
#define FLEXCAN_MCR_DMA_SHIFT           (15U)
#define FLEXCAN_MCR_DMA_MASK            (0x1UL << FLEXCAN_MCR_DMA_SHIFT)
#define FLEXCAN_MCR_DMA_WIDTH           (1u)
#define FLEXCAN_MCR_PNET_EN_MASK        (0x4000u)
#define FLEXCAN_MCR_PNET_EN_SHIFT       (14)
#define FLEXCAN_MCR_PNET_EN_WIDTH       (1)
#define FLEXCAN_MCR_LPRIOEN_MASK        (0x2000u)
#define FLEXCAN_MCR_LPRIOEN_SHIFT       (13u)
#define FLEXCAN_MCR_LPRIOEN_WIDTH       (1u)
#define FLEXCAN_MCR_AEN_SHIFT           (12U)
#define FLEXCAN_MCR_AEN_MASK            (0x1UL << FLEXCAN_MCR_AEN_SHIFT)
#define FELXCAN_MCR_AEN_WIDTH           (1U)
#define FLEXCAN_MCR_FDEN_SHIFT          (11U)
#define FLEXCAN_MCR_FDEN_MASK           (0x1UL << FLEXCAN_MCR_FDEN_SHIFT)
#define FLEXCAN_MCR_FDEN_WIDTH          (1u)
#define FLEXCAN_MCR_IDAM_SHIFT          (8U)
#define FLEXCAN_MCR_IDAM_MASK           (0x3UL << FLEXCAN_MCR_IDAM_SHIFT)
#define FLEXCAN_MCR_IDAM_WIDTH          (2U)
#define FLEXCAN_MCR_MAXMB_SHIFT         (0U)
#define FLEXCAN_MCR_MAXMB_MASK          (0x7FUL << FLEXCAN_MCR_MAXMB_SHIFT)
#define FLEXCAN_MCR_MAXMB_WIDTH         (7u)

/* CTRL1 register */
#define FLEXCAN_CTRL1_PRESDIV_MASK      (0xFF000000u)
#define FLEXCAN_CTRL1_PRESDIV_SHIFT     (24u)
#define FLEXCAN_CTRL1_PRESDIV_WIDTH     (8u)
#define FLEXCAN_CTRL1_RJW_MASK          (0xC00000u)
#define FLEXCAN_CTRL1_RJW_SHIFT         (22u)
#define FLEXCAN_CTRL1_RJW_WIDTH         (2u)
#define FLEXCAN_CTRL1_PSEG1_MASK        (0x380000u)
#define FLEXCAN_CTRL1_PSEG1_SHIFT       (19u)
#define FLEXCAN_CTRL1_PSEG1_WIDTH       (3u)
#define FLEXCAN_CTRL1_PSEG2_MASK        (0x70000u)
#define FLEXCAN_CTRL1_PSEG2_SHIFT       (16u)
#define FLEXCAN_CTRL1_PSEG2_WIDTH       (3u)
#define FLEXCAN_CTRL1_BOFFMSK_SHIFT     (15U)
#define FLEXCAN_CTRL1_BOFFMSK_MASK      (0x1UL << FLEXCAN_CTRL1_BOFFMSK_SHIFT)
#define FLEXCAN_CTRL1_BOFFMSK_WIDTH     (1U)
#define FLEXCAN_CTRL1_ERRMSK_SHIFT      (14U)
#define FLEXCAN_CTRL1_ERRMSK_MASK       (0x1UL << FLEXCAN_CTRL1_ERRMSK_SHIFT)
#define FLEXCAN_CTRL1_ERRMSK_WIDTH      (1UL)
#define FLEXCAN_CTRL1_CLKSRC_SHIFT      (13U)
#define FLEXCAN_CTRL1_CLKSRC_MASK       (0x1UL << FLEXCAN_CTRL1_CLKSRC_SHIFT)
#define FLEXCAN_CTRL1_CLKSRC_WIDTH      (1u)
#define FLEXCAN_CTRL1_LPB_SHIFT         (12U)
#define FLEXCAN_CTRL1_LPB_MASK          (0x1UL << FLEXCAN_CTRL1_LPB_SHIFT)
#define FLEXCAN_CTRL1_LPB_WIDTH         (1u)
#define FLEXCAN_CTRL1_TWRNMSK_SHIFT     (11U)
#define FLEXCAN_CTRL1_TWRNMSK_MASK      (0x1UL << FLEXCAN_CTRL1_TWRNMSK_SHIFT)
#define FLEXCAN_CTRL1_TWRNMSK_WIDTH     (1U)
#define FLEXCAN_CTRL1_RWRNMSK_SHIFT     (10U)
#define FLEXCAN_CTRL1_RWRNMSK_MASK      (1UL << FLEXCAN_CTRL1_RWRNMSK_SHIFT)
#define FLEXCAN_CTRL1_RWRNMSK_WIDTH     (1U)
#define FLEXCAN_CTRL1_SMP_SHIFT         (7U)
#define FLEXCAN_CTRL1_SMP_MASK          (1UL << FLEXCAN_CTRL1_SMP_SHIFT)
#define FLEXCAN_CTRL1_SMP_WIDTH         (1U)
#define FLEXCAN_CTRL1_BOFFREC_SHIFT     (6U)
#define FLEXCAN_CTRL1_BOFFREC_MASK      (1UL << FLEXCAN_CTRL1_BOFFREC_SHIFT)
#define FLEXCAN_CTRL1_BOFFREC_WIDTH     (1U)
#define FLEXCAN_CTRL1_TSYN_SHIFT        (5U)
#define FLEXCAN_CTRL1_TSYN_MASK         (0x1UL << FLEXCAN_CTRL1_TSYN_SHIFT)
#define FLEXCAN_CTRL1_TSYN_WIDTH        (1U)
#define FLEXCAN_CTRL1_LBUF_SHIFT        (4U)
#define FLEXCAN_CTRL1_LBUF_MASK         (0x1UL << FLEXCAN_CTRL1_LBUF_SHIFT)
#define FLEXCAN_CTRL1_LBUF_WIDTH        (1U)
#define FLEXCAN_CTRL1_LOM_SHIFT         (3U)
#define FLEXCAN_CTRL1_LOM_MASK          (0x1UL << FLEXCAN_CTRL1_LOM_SHIFT)
#define FLEXCAN_CTRL1_LOM_WIDTH         (1U)
#define FLEXCAN_CTRL1_PROPSEG_MASK      (0x07u)
#define FLEXCAN_CTRL1_PROPSEG_SHIFT     (0u)
#define FLEXCAN_CTRL1_PROPSEG_WIDTH     (3u)

/* TIMER register */
#define FLEXCAN_TIMER_TIMER_MASK        (0xFFFFu)
#define FLEXCAN_TIMER_TIMER_SHIFT       (0u)
#define FLEXCAN_TIMER_TIMER_WIDTH       (16u)

/* RXMGMASK register */
#define FLEXCAN_RXMGMASK_MG_MASK        (0xFFFFFFFFu)
#define FLEXCAN_RXMGMASK_MG_SHIFT       (0u)
#define FLEXCAN_RXMGMASK_MG_WIDTH       (32u)

/* RX14MASK register */
#define FLEXCAN_RX14MASK_RX14M_MASK     (0xFFFFFFFFu)
#define FLEXCAN_RX14MASK_RX14M_SHIFT    (0u)
#define FLEXCAN_RX14MASK_RX14M_WIDTH    (32u)

/* RX15MASK register */
#define FLEXCAN_RX15MASK_RX15M_MASK     (0xFFFFFFFFu)
#define FLEXCAN_RX15MASK_RX15M_SHIFT    (0u)
#define FLEXCAN_RX15MASK_RX15M_WIDTH    (32u)

/* ECR register */
#define FLEXCAN_ECR_RXERRCNTFAST_MASK   (0xFF000000u)
#define FLEXCAN_ECR_RXERRCNTFAST_SHIFT  (24u)
#define FLEXCAN_ECR_RXERRCNTFAST_WIDTH  (8u)
#define FLEXCAN_ECR_TXERRCNTFAST_MASK   (0xFF0000u)
#define FLEXCAN_ECR_TXERRCNTFAST_SHIFT  (16u)
#define FLEXCAN_ECR_TXERRCNTFAST_WIDTH  (8u)
#define FLEXCAN_ECR_RXERRCNT_MASK       (0xFF00u)
#define FLEXCAN_ECR_RXERRCNT_SHIFT      (8u)
#define FLEXCAN_ECR_RXERRCNT_WIDTH      (8u)
#define FLEXCAN_ECR_TXERRCNT_MASK       (0xFFu)
#define FLEXCAN_ECR_TXERRCNT_SHIFT      (0u)
#define FLEXCAN_ECR_TXERRCNT_WIDTH      (8u)

/* ESR1 register */
#define FLEXCAN_ESR1_BIT1ERR_FAST_SHIFT (31U)
#define FLEXCAN_ESR1_BIT1ERR_FAST_MASK  (1UL << FLEXCAN_ESR1_BIT1ERR_FAST_SHIFT)
#define FLEXCAN_ESR1_BIT1ERR_FAST_WIDTH (1U)
#define FLEXCAN_ESR1_BIT0ERR_FAST_SHIFT (30U)
#define FLEXCAN_ESR1_BIT0ERR_FAST_MASK  (1UL << FLEXCAN_ESR1_BIT0ERR_FAST_SHIFT)
#define FLEXCAN_ESR1_BIT0ERR_FAST_WIDTH (1U)
#define FLEXCAN_ESR1_CRCERR_FAST_SHIFT  (28U)
#define FLEXCAN_ESR1_CRCERR_FAST_MASK   (1UL << FLEXCAN_ESR1_CRCERR_FAST_SHIFT)
#define FLEXCAN_ESR1_CRCERR_FAST_WIDTH  (1U)
#define FLEXCAN_ESR1_FRMERR_FAST_SHIFT  (27U)
#define FLEXCAN_ESR1_FRMERR_FAST_MASK   (1UL << FLEXCAN_ESR1_FRMERR_FAST_SHIFT)
#define FLEXCAN_ESR1_FRMERR_FAST_WIDTH  (1U)
#define FLEXCAN_ESR1_STFERR_FAST_SHIFT  (26U)
#define FLEXCAN_ESR1_STFERR_FAST_MASK   (1UL << FLEXCAN_ESR1_STFERR_FAST_SHIFT)
#define FLEXCAN_ESR1_STFERR_FAST_WIDTH  (1U)
#define FLEXCAN_ESR1_ERROVR_SHIFT       (21U)
#define FLEXCAN_ESR1_ERROVR_MASK        (1UL << FLEXCAN_ESR1_ERROVR_SHIFT)
#define FLEXCAN_ESR1_ERROVR_WIDTH       (1U)
#define FLEXCAN_ESR1_ERRINT_FAST_SHIFT  (20U)
#define FLEXCAN_ESR1_ERRINT_FAST_MASK   (1UL << FLEXCAN_ESR1_ERRINT_FAST_SHIFT)
#define FLEXCAN_ESR1_ERRINT_FAST_WIDTH  (1U)
#define FLEXCAN_ESR1_BOFFDONEINT_SHIFT  (19U)
#define FLEXCAN_ESR1_BOFFDONEINT_MASK   (1UL << FLEXCAN_ESR1_BOFFDONEINT_SHIFT)
#define FLEXCAN_ESR1_BOFFDONEINT_WIDTH  (1U)
#define FLEXCAN_ESR1_SYNCH_SHIFT        (18U)
#define FLEXCAN_ESR1_SYNCH_MASK         (1UL << FLEXCAN_ESR1_SYNCH_SHIFT)
#define FLEXCAN_ESR1_SYNCH_WIDTH        (1U)
#define FLEXCAN_ESR1_TWRNINT_SHIFT      (17U)
#define FLEXCAN_ESR1_TWRNINT_MASK       (1UL << FLEXCAN_ESR1_TWRNINT_SHIFT)
#define FLEXCAN_ESR1_TWRNINT_WIDTH      (1U)
#define FLEXCAN_ESR1_RWRNINT_SHIFT      (16U)
#define FLEXCAN_ESR1_RWRNINT_MASK       (1UL << FLEXCAN_ESR1_RWRNINT_SHIFT)
#define FLEXCAN_ESR1_RWRNINT_WIDTH      (1U)
#define FLEXCAN_ESR1_BIT1ERR_SHIFT      (15U)
#define FLEXCAN_ESR1_BIT1ERR_MASK       (1UL << FLEXCAN_ESR1_BIT1ERR_SHIFT)
#define FLEXCAN_ESR1_BIT1ERR_WIDTH      (1U)
#define FLEXCAN_ESR1_BIT0ERR_SHIFT      (14U)
#define FLEXCAN_ESR1_BIT0ERR_MASK       (1UL << FLEXCAN_ESR1_BIT0ERR_SHIFT)
#define FLEXCAN_ESR1_BIT0ERR_WIDTH      (1U)
#define FLEXCAN_ESR1_ACKERR_SHIFT       (13U)
#define FLEXCAN_ESR1_ACKERR_MASK        (1UL << FLEXCAN_ESR1_ACKERR_SHIFT)
#define FLEXCAN_ESR1_ACKERR_WIDTH       (1U)
#define FLEXCAN_ESR1_CRCERR_SHIFT       (12U)
#define FLEXCAN_ESR1_CRCERR_MASK        (1UL << FLEXCAN_ESR1_CRCERR_SHIFT)
#define FLEXCAN_ESR1_CRCERR_WIDTH       (1U)
#define FLEXCAN_ESR1_FRMERR_SHIFT       (11U)
#define FLEXCAN_ESR1_FRMERR_MASK        (1UL << FLEXCAN_ESR1_FRMERR_SHIFT)
#define FLEXCAN_ESR1_FRMERR_WIDTH       (1U)
#define FLEXCAN_ESR1_STFERR_SHIFT       (10U)
#define FLEXCAN_ESR1_STFERR_MASK        (1UL << FLEXCAN_ESR1_STFERR_SHIFT)
#define FLEXCAN_ESR1_STFERR_WIDTH       (1U)
#define FLEXCAN_ESR1_TXWRN_SHIFT        (9U)
#define FLEXCAN_ESR1_TXWRN_MASK         (0x1UL << FLEXCAN_ESR1_TXWRN_SHIFT)
#define FLEXCAN_ESR1_TXWRN_WIDTH        (1U)
#define FLEXCAN_ESR1_RXWRN_SHIFT        (8U)
#define FLEXCAN_ESR1_RXWRN_MASK         (0x1UL << FLEXCAN_ESR1_RXWRN_SHIFT)
#define FLEXCAN_ESR1_RXWRN_WIDTH        (1U)
#define FLEXCAN_ESR1_IDLE_SHIFT         (7U)
#define FLEXCAN_ESR1_IDLE_MASK          (1UL << FLEXCAN_ESR1_IDLE_SHIFT)
#define FLEXCAN_ESR1_IDLE_WIDTH         (1U)
#define FLEXCAN_ESR1_TX_SHIFT           (6U)
#define FLEXCAN_ESR1_TX_MASK            (1UL << FLEXCAN_ESR1_TX_SHIFT)
#define FLEXCAN_ESR1_TX_WIDTH           (1U)
#define FLEXCAN_ESR1_FLTCONF_SHIFT      (4U)
#define FLEXCAN_ESR1_FLTCONF_MASK       (3UL << FLEXCAN_ESR1_FLTCONF_SHIFT)
#define FLEXCAN_ESR1_FLTCONF_WIDTH      (2U)
#define FLEXCAN_ESR1_RX_SHIFT           (3U)
#define FLEXCAN_ESR1_RX_MASK            (1UL << FLEXCAN_ESR1_RX_SHIFT)
#define FLEXCAN_ESR1_RX_WIDTH           (1U)
#define FLEXCAN_ESR1_BOFFINT_SHIFT      (2U)
#define FLEXCAN_ESR1_BOFFINT_MASK       (0x1UL << FLEXCAN_ESR1_BOFFINT_SHIFT)
#define FLEXCAN_ESR1_BOFFINT_WIDTH      (1U)
#define FLEXCAN_ESR1_ERRINT_SHIFT       (1U)
#define FLEXCAN_ESR1_ERRINT_MASK        (0x1UL << FLEXCAN_ESR1_ERRINT_SHIFT)
#define FLEXCAN_ESR1_ERRINT_WIDTH       (1U)
#define FLEXCAN_ESR1_WAKINT_SHIFT       (0U)
#define FLEXCAN_ESR1_WAKINT_MASK        (0x1UL << FLEXCAN_ESR1_WAKINT_SHIFT)
#define FLEXCAN_ESR1_WAKINT_WIDTH       (1U)

/* CTRL2 register */
#define FLEXCAN_CTRL2_ERRMSKFAST_MASK   (0x80000000u)
#define FLEXCAN_CTRL2_ERRMSKFAST_SHIFT  (31u)
#define FLEXCAN_CTRL2_ERRMSKFAST_WIDTH  (1u)
#define FLEXCAN_CTRL2_BOFFDONEMSK_MASK  (0x40000000u)
#define FLEXCAN_CTRL2_BOFFDONEMSK_SHIFT (30u)
#define FLEXCAN_CTRL2_BOFFDONEMSK_WIDTH (1u)
#define FLEXCAN_CTRL2_ECRWRE_SHIFT      (29U)
#define FLEXCAN_CTRL2_ECRWRE_MASK       (0x1UL << FLEXCAN_CTRL2_ECRWRE_SHIFT)
#define FLEXCAN_CTRL2_ECRWRE_WIDTH      (1u)
#define FLEXCAN_CTRL2_WRMFRZ_SHIFT      (28U)
#define FLEXCAN_CTRL2_WRMFRZ_MASK       (0x1UL << FLEXCAN_CTRL2_WRMFRZ_SHIFT)
#define FLEXCAN_CTRL2_WRMFRZ_WIDTH      (1u)
#define FLEXCAN_CTRL2_RFFN_SHIFT        (24U)
#define FLEXCAN_CTRL2_RFFN_MASK         (0xFUL << FLEXCAN_CTRL2_RFFN_SHIFT)
#define FLEXCAN_CTRL2_RFFN_WIDTH        (4U)
#define FLEXCAN_CTRL2_TASD_MASK         (0xF80000u)
#define FLEXCAN_CTRL2_TASD_SHIFT        (19u)
#define FLEXCAN_CTRL2_TASD_WIDTH        (5u)
#define FLEXCAN_CTRL2_MRP_MASK          (0x40000u)
#define FLEXCAN_CTRL2_MRP_SHIFT         (18u)
#define FLEXCAN_CTRL2_MRP_WIDTH         (1u)
#define FLEXCAN_CTRL2_RRS_MASK          (0x20000u)
#define FLEXCAN_CTRL2_RRS_SHIFT         (17u)
#define FLEXCAN_CTRL2_RRS_WIDTH         (1u)
#define FLEXCAN_CTRL2_EACEN_MASK        (0x10000u)
#define FLEXCAN_CTRL2_EACEN_SHIFT       (16u)
#define FLEXCAN_CTRL2_EACEN_WIDTH       (1u)
#define FLEXCAN_CTRL2_TIMERSRC_MASK     (0x8000u)
#define FLEXCAN_CTRL2_TIMERSRC_SHIFT    (15u)
#define FLEXCAN_CTRL2_TIMERSRC_WIDTH    (1u)
#define FLEXCAN_CTRL2_PREXCEN_MASK      (0x4000u)
#define FLEXCAN_CTRL2_PREXCEN_SHIFT     (14u)
#define FLEXCAN_CTRL2_PREXCEN_WIDTH     (1u)
#define FLEXCAN_CTRL2_BTE_MASK          (0x2000u)
#define FLEXCAN_CTRL2_BTE_SHIFT         (13)
#define FLEXCAN_CTRL2_BTE_WIDTH         (1)
#define FLEXCAN_CTRL2_ISOCANFDEN_SHIFT  (12U)
#define FLEXCAN_CTRL2_ISOCANFDEN_MASK   (0x1UL << FLEXCAN_CTRL2_ISOCANFDEN_SHIFT)
#define FLEXCAN_CTRL2_ISOCANFDEN_WIDTH  (1u)
#define FLEXCAN_CTRL2_EDFLTDIS_MASK     (0x800u)
#define FLEXCAN_CTRL2_EDFLTDIS_SHIFT    (11u)
#define FLEXCAN_CTRL2_EDFLTDIS_WIDTH    (1u)
#define FLEXCAN_CTRL2_MBTSBASE_MASK     (0x300u)
#define FLEXCAN_CTRL2_MBTSBASE_SHIFT    (8)
#define FLEXCAN_CTRL2_MBTSBASE_WIDTH    (2)
#define FLEXCAN_CTRL2_TSTAMPCAP_MASK    (0xC0u)
#define FLEXCAN_CTRL2_TSTAMPCAP_SHIFT   (6)
#define FLEXCAN_CTRL2_TSTAMPCAP_WIDTH   (2)

/* ESR2 register */
#define FLEXCAN_ESR2_LPTM_MASK          (0x7F0000u)
#define FLEXCAN_ESR2_LPTM_SHIFT         (16u)
#define FLEXCAN_ESR2_LPTM_WIDTH         (7u)
#define FLEXCAN_ESR2_VPS_MASK           (0x4000u)
#define FLEXCAN_ESR2_VPS_SHIFT          (14u)
#define FLEXCAN_ESR2_VPS_WIDTH          (1u)
#define FLEXCAN_ESR2_IMB_MASK           (0x2000u)
#define FLEXCAN_ESR2_IMB_SHIFT          (13u)
#define FLEXCAN_ESR2_IMB_WIDTH          (1u)

/* CRCR register */
#define FLEXCAN_CRCR_MBCRC_MASK         (0x7F0000u)
#define FLEXCAN_CRCR_MBCRC_SHIFT        (16u)
#define FLEXCAN_CRCR_MBCRC_WIDTH        (7u)
#define FLEXCAN_CRCR_TXCRC_MASK         (0x7FFFu)
#define FLEXCAN_CRCR_TXCRC_SHIFT        (0u)
#define FLEXCAN_CRCR_TXCRC_WIDTH        (15u)

/* RXFGMASK register */
#define FLEXCAN_RXFGMASK_FGM_MASK       (0xFFFFFFFFu)
#define FLEXCAN_RXFGMASK_FGM_SHIFT      (0u)
#define FLEXCAN_RXFGMASK_FGM_WIDTH      (32u)

/* RXFIR register */
#define FLEXCAN_RXFIR_IDHIT_MASK        (0x1FFu)
#define FLEXCAN_RXFIR_IDHIT_SHIFT       (0u)
#define FLEXCAN_RXFIR_IDHIT_WIDTH       (9u)

/* CBT register */
#define FLEXCAN_CBT_BTF_SHIFT           (31U)
#define FLEXCAN_CBT_BTF_MASK            (0x1UL << FLEXCAN_CBT_BTF_SHIFT)
#define FLEXCAN_CBT_BTF_WIDTH           (1u)
#define FLEXCAN_CBT_EPRESDIV_SHIFT      (21U)
#define FLEXCAN_CBT_EPRESDIV_MASK       (0x3FFUL << FLEXCAN_CBT_EPRESDIV_SHIFT)
#define FLEXCAN_CBT_EPRESDIV_WIDTH      (10u)
#define FLEXCAN_CBT_ERJW_SHIFT          (16U)
#define FLEXCAN_CBT_ERJW_MASK           (0x1FUL << FLEXCAN_CBT_ERJW_SHIFT)
#define FLEXCAN_CBT_ERJW_WIDTH          (5u)
#define FLEXCAN_CBT_EPROPSEG_SHIFT      (10U)
#define FLEXCAN_CBT_EPROPSEG_MASK       (0x3FUL << FLEXCAN_CBT_EPROPSEG_SHIFT)
#define FLEXCAN_CBT_EPROPSEG_WIDTH      (6u)
#define FLEXCAN_CBT_EPSEG1_SHIFT        (5U)
#define FLEXCAN_CBT_EPSEG1_MASK         (0x1FUL << FLEXCAN_CBT_EPSEG1_SHIFT)
#define FLEXCAN_CBT_EPSEG1_WIDTH        (5u)
#define FLEXCAN_CBT_EPSEG2_SHIFT        (0U)
#define FLEXCAN_CBT_EPSEG2_MASK         (0x1FUL << FLEXCAN_CBT_EPSEG2_SHIFT)

/* IMASK4 register */
#define FLEXCAN_IMASK4_BUF127TO96M_MASK  (0xFFFFFFFFu)
#define FLEXCAN_IMASK4_BUF127TO96M_SHIFT (0u)
#define FLEXCAN_IMASK4_BUF127TO96M_WIDTH (32u)

/* IMASK3 register */
#define FLEXCAN_IMASK3_BUF95TO64M_MASK   (0xFFFFFFFFu)
#define FLEXCAN_IMASK3_BUF95TO64M_SHIFT  (0u)
#define FLEXCAN_IMASK3_BUF95TO64M_WIDTH  (32u)

/* IFLAG4 register */
#define FLEXCAN_IFLAG4_BUF127TO96_MASK   (0xFFFFFFFFu)
#define FLEXCAN_IFLAG4_BUF127TO96_SHIFT  (0u)
#define FLEXCAN_IFLAG4_BUF127TO96_WIDTH  (32u)

/* IFLAG3 register */
#define FLEXCAN_IFLAG3_BUF95TO64_MASK    (0xFFFFFFFFu)
#define FLEXCAN_IFLAG3_BUF95TO64_SHIFT   (0u)
#define FLEXCAN_IFLAG3_BUF95TO64_WIDTH   (32u)

/* RXIMRN register */
#define FLEXCAN_RXIMRN_MI_MASK           (0xFFFFFFFFu)
#define FLEXCAN_RXIMRN_MI_SHIFT          (0u)
#define FLEXCAN_RXIMRN_MI_WIDTH          (32u)

/* MECR register */
#define FLEXCAN_MECR_ECRWRDIS_SHIFT     (31U)
#define FLEXCAN_MECR_ECRWRDIS_MASK      (0x1UL << FLEXCAN_MECR_ECRWRDIS_SHIFT)
#define FLEXCAN_MECR_ECRWRDIS_WIDTH     (1u)
#define FLEXCAN_MECR_HANCEIMSK_MASK     (0x80000u)
#define FLEXCAN_MECR_HANCEIMSK_SHIFT    (19u)
#define FLEXCAN_MECR_HANCEIMSK_WIDTH    (1u)
#define FLEXCAN_MECR_FANCEIMSK_MASK     (0x40000u)
#define FLEXCAN_MECR_FANCEIMSK_SHIFT    (18u)
#define FLEXCAN_MECR_FANCEIMSK_WIDTH    (1u)
#define FLEXCAN_MECR_CEIMSK_MASK        (0x10000u)
#define FLEXCAN_MECR_CEIMSK_SHIFT       (16u)
#define FLEXCAN_MECR_CEIMSK_WIDTH       (1u)
#define FLEXCAN_MECR_HAERRIE_MASK       (0x8000u)
#define FLEXCAN_MECR_HAERRIE_SHIFT      (15u)
#define FLEXCAN_MECR_HAERRIE_WIDTH      (1u)
#define FLEXCAN_MECR_FAERRIE_MASK       (0x4000u)
#define FLEXCAN_MECR_FAERRIE_SHIFT      (14u)
#define FLEXCAN_MECR_FAERRIE_WIDTH      (1u)
#define FLEXCAN_MECR_EXTERRIE_MASK      (0x2000u)
#define FLEXCAN_MECR_EXTERRIE_SHIFT     (13u)
#define FLEXCAN_MECR_EXTERRIE_WIDTH     (1u)
#define FLEXCAN_MECR_RERRDIS_MASK       (0x200u)
#define FLEXCAN_MECR_RERRDIS_SHIFT      (9u)
#define FLEXCAN_MECR_RERRDIS_WIDTH      (1u)
#define FLEXCAN_MECR_ECCDIS_SHIFT       (8U)
#define FLEXCAN_MECR_ECCDIS_MASK        (0x1UL << FLEXCAN_MECR_ECCDIS_SHIFT)
#define FLEXCAN_MECR_ECCDIS_WIDTH       (1u)
#define FLEXCAN_MECR_NCEFAFRZ_SHIFT     (7U)
#define FLEXCAN_MECR_NCEFAFRZ_MASK      (0x1UL << FLEXCAN_MECR_NCEFAFRZ_SHIFT)
#define FLEXCAN_MECR_NCEFAFRZ_WIDTH     (1u)

/* EPRS register */
#define FLEXCAN_EPRS_EDPRESDIV_SHIFT    (16U)
#define FLEXCAN_EPRS_EDPRESDIV_MASK     (0x3FFUL << FLEXCAN_EPRS_EDPRESDIV_SHIFT)
#define FLEXCAN_EPRS_EDPRESDIV_WIDTH    (10U)
#define FLEXCAN_EPRS_ENPRESDIV_SHIFT    (0U)
#define FLEXCAN_EPRS_ENPRESDIV_MASK     (0x3FFUL << FLEXCAN_EPRS_ENPRESDIV_SHIFT)
#define FLEXCAN_EPRS_ENPRESDIV_WIDTH    (10U)

/* ENCBT register */
#define FLEXCAN_ENCBT_NRJW_SHIFT        (22U)
#define FLEXCAN_ENCBT_NRJW_MASK         (0x7FL << FLEXCAN_ENCBT_NRJW_SHIFT)
#define FLEXCAN_ENCBT_NRJW_WIDTH        (7U)
#define FLEXCAN_ENCBT_NTSEG2_SHIFT      (12U)
#define FLEXCAN_ENCBT_NTSEG2_MASK       (0x7FUL << FLEXCAN_ENCBT_NTSEG2_SHIFT)
#define FLEXCAN_ENCBT_NTSEG2_WIDTH      (7U)
#define FLEXCAN_ENCBT_NTSEG1_SHIFT      (0U)
#define FLEXCAN_ENCBT_NTSEG1_MASK       (0xFFUL << FLEXCAN_ENCBT_NTSEG1_SHIFT)
#define FLEXCAN_ENCBT_NTSEG1_WIDTH      (8U)

/* EDCBT register */
#define FLEXCAN_EDCBT_DRJW_SHIFT        (22U)
#define FLEXCAN_EDCBT_DRJW_MASK         (0xFUL << FLEXCAN_EDCBT_DRJW_SHIFT)
#define FLEXCAN_EDCBT_DRJW_WIDTH        (4U)
#define FLEXCAN_EDCBT_DTSEG2_SHIFT      (12U)
#define FLEXCAN_EDCBT_DTSEG2_MASK       (0xFUL << FLEXCAN_EDCBT_DTSEG2_SHIFT)
#define FLEXCAN_EDCBT_DTSEG2_WIDTH      (4U)
#define FLEXCAN_EDCBT_DTSEG1_SHIFT      (0U)
#define FLEXCAN_EDCBT_DTSEG1_MASK       (0x1FUL << FLEXCAN_EDCBT_DTSEG1_SHIFT)
#define FLEXCAN_EDCBT_DTSEG1_WIDTH      (5U)

/* FDCTRL register */
#define FLEXCAN_FDCTRL_FDRATE_SHIFT     (31U)
#define FLEXCAN_FDCTRL_FDRATE_MASK      (0x1UL << FLEXCAN_FDCTRL_FDRATE_SHIFT)
#define FLEXCAN_FDCTRL_FDRATE_WIDTH     (1u)
#define FLEXCAN_FDCTRL_MBDSR3_SHIFT     (25U)
#define FLEXCAN_FDCTRL_MBDSR3_MASK      (0x3UL << FLEXCAN_FDCTRL_MBDSR3_SHIFT)
#define FLEXCAN_FDCTRL_MBDSR3_WIDTH     (2u)
#define FLEXCAN_FDCTRL_MBDSR2_SHIFT     (22U)
#define FLEXCAN_FDCTRL_MBDSR2_MASK      (0x3UL << FLEXCAN_FDCTRL_MBDSR2_SHIFT)
#define FLEXCAN_FDCTRL_MBDSR2_WIDTH     (2u)
#define FLEXCAN_FDCTRL_MBDSR1_SHIFT     (19U)
#define FLEXCAN_FDCTRL_MBDSR1_MASK      (0x3UL << FLEXCAN_FDCTRL_MBDSR1_SHIFT)
#define FLEXCAN_FDCTRL_MBDSR1_WIDTH     (2u)
#define FLEXCAN_FDCTRL_MBDSR0_SHIFT     (16U)
#define FLEXCAN_FDCTRL_MBDSR0_MASK      (0x3UL << FLEXCAN_FDCTRL_MBDSR0_SHIFT)
#define FLEXCAN_FDCTRL_MBDSR0_WIDTH     (2u)
#define FLEXCAN_FDCTRL_TDCEN_SHIFT      (15U)
#define FLEXCAN_FDCTRL_TDCEN_MASK       (0x1UL << FLEXCAN_FDCTRL_TDCEN_SHIFT)
#define FLEXCAN_FDCTRL_TDCEN_WIDTH      (1u)
#define FLEXCAN_FDCTRL_TDCFAIL_MASK     (0x4000u)
#define FLEXCAN_FDCTRL_TDCFAIL_SHIFT    (14u)
#define FLEXCAN_FDCTRL_TDCFAIL_WIDTH    (1u)
#define FLEXCAN_FDCTRL_TDCOFF_SHIFT     (8U)
#define FLEXCAN_FDCTRL_TDCOFF_MASK      (0x1FUL << FLEXCAN_FDCTRL_TDCOFF_SHIFT)
#define FLEXCAN_FDCTRL_TDCOFF_WIDTH     (5u)
#define FLEXCAN_FDCTRL_TDCVAL_MASK      (0x3Fu)
#define FLEXCAN_FDCTRL_TDCVAL_SHIFT     (0u)
#define FLEXCAN_FDCTRL_TDCVAL_WIDTH     (6u)

/* FDCBT register */
#define FLEXCAN_FDCBT_FPRESDIV_SHIFT    (20U)
#define FLEXCAN_FDCBT_FPRESDIV_MASK     (0x3FFUL << FLEXCAN_FDCBT_FPRESDIV_SHIFT)
#define FLEXCAN_FDCBT_FPRESDIV_WIDTH    (10u)
#define FLEXCAN_FDCBT_FRJW_SHIFT        (16U)
#define FLEXCAN_FDCBT_FRJW_MASK         (0x7UL << FLEXCAN_FDCBT_FRJW_SHIFT)
#define FLEXCAN_FDCBT_FPJW_WIDTH        (3u)
#define FLEXCAN_FDCBT_FPROPSEG_SHIFT    (10U)
#define FLEXCAN_FDCBT_FPROPSEG_MASK     (0x1FUL << FLEXCAN_FDCBT_FPROPSEG_SHIFT)
#define FLEXCAN_FDCBT_FPROPSEG_WIDTH    (5u)
#define FLEXCAN_FDCBT_FPSEG1_SHIFT      (5U)
#define FLEXCAN_FDCBT_FPSEG1_MASK       (0x7UL << FLEXCAN_FDCBT_FPSEG1_SHIFT)
#define FLEXCAN_FDCBT_FPSEG1_WIDTH      (3u)
#define FLEXCAN_FDCBT_FPSEG2_SHIFT      (0U)
#define FLEXCAN_FDCBT_FPSEG2_MASK       (0x7UL << FLEXCAN_FDCBT_FPSEG2_SHIFT)
#define FLEXCAN_FDCBT_FPSEG2_WIDTH      (3u)

/* FDCRC register */
#define CAN_FDCRC_FDMBCRC_MASK          (0x7F000000u)
#define CAN_FDCRC_FDMBCRC_SHIFT         (24u)
#define CAN_FDCRC_FDMBCRC_WIDTH         (7u)
#define CAN_FDCRC_FDTXCRC_MASK          (0x1FFFFFu)
#define CAN_FDCRC_FDTXCRC_SHIFT         (0u)
#define CAN_FDCRC_FDTXCRC_WIDTH         (21u)

/* ERFCR register */
#define FLEXCAN_ERFCR_ERFEN_SHIFT       (31U)
#define FLEXCAN_ERFCR_ERFEN_MASK        (1UL << FLEXCAN_ERFCR_ERFEN_SHIFT)
#define FLEXCAN_ERFCR_ERFEN_WIDTH       (1U)
#define FLEXCAN_ERFCR_DMALW_SHIFT       (26U)
#define FLEXCAN_ERFCR_DMALW_MASK        (0x1FUL << FLEXCAN_ERFCR_DMALW_SHIFT)
#define FLEXCAN_ERFCR_DMALW_WIDTH       (5U)
#define FLEXCAN_ERFCR_NEXIF_SHIFT       (16U)
#define FLEXCAN_ERFCR_NEXIF_MASK        (0x7FUL << FLEXCAN_ERFCR_NEXIF_SHIFT)
#define FLEXCAN_ERFCR_NEXIF_WIDTH       (7U)
#define FLEXCAN_ERFCR_NFE_SHIFT         (8U)
#define FLEXCAN_ERFCR_NFE_MASK          (0x3FUL << FLEXCAN_ERFCR_NFE_SHIFT)
#define FLEXCAN_ERFCR_NFE_WIDTH         (6U)
#define FLEXCAN_ERFCR_ERFWM_SHIFT       (0U)
#define FLEXCAN_ERFCR_ERFWM_MASK        (0x1FUL << FLEXCAN_ERFCR_ERFWM_SHIFT)
#define FLEXCAN_ERFCR_ERFWM_WIDTH       (5U)

/* ERFIER register */
#define FLEXCAN_ERFIER_ERFUFWIE_SHIFT   (31U)
#define FLEXCAN_ERFIER_ERFUFWIE_MASK    (1UL << FLEXCAN_ERFIER_ERFUFWIE_SHIFT)
#define FLEXCAN_ERFIER_ERFUFWIE_WIDTH   (1U)
#define FLEXCAN_ERFIER_ERFOVFIE_SHIFT   (30U)
#define FLEXCAN_ERFIER_ERFOVFIE_MASK    (1UL << FLEXCAN_ERFIER_ERFOVFIE_SHIFT)
#define FLEXCAN_ERFIER_ERFOVFIE_WIDTH   (1U)
#define FLEXCAN_ERFIER_ERFWMIIE_SHIFT   (29U)
#define FLEXCAN_ERFIER_ERFWMIIE_MASK    (1UL << FLEXCAN_ERFIER_ERFWMIIE_SHIFT)
#define FLEXCAN_ERFIER_ERFWMIIE_WIDTH   (1U)
#define FLEXCAN_ERFIER_ERFDAIE_SHIFT    (28U)
#define FLEXCAN_ERFIER_ERFDAIE_MASK     (1UL << FLEXCAN_ERFIER_ERFDAIE_SHIFT)
#define FLEXCAN_ERFIER_ERFDAIE_WIDTH    (1U)

/* ERFSR register */
#define FLEXCAN_ERFSR_ERFUFW_SHIFT      (31U)
#define FLEXCAN_ERFSR_ERFUFW_MASK       (1UL << FLEXCAN_ERFSR_ERFUFW_SHIFT)
#define FLEXCAN_ERFSR_ERFUFW_WIDTH      (1U)
#define FLEXCAN_ERFSR_ERFOVF_SHIFT      (30U)
#define FLEXCAN_ERFSR_ERFOVF_MASK       (1UL << FLEXCAN_ERFSR_ERFOVF_SHIFT)
#define FLEXCAN_ERFSR_ERFOVF_WIDTH      (1U)
#define FLEXCAN_ERFSR_ERFWMI_SHIFT      (29U)
#define FLEXCAN_ERFSR_ERFWMI_MASK       (1UL << FLEXCAN_ERFSR_ERFWMI_SHIFT)
#define FLEXCAN_ERFSR_ERFWMI_WIDTH      (1U)
#define FLEXCAN_ERFSR_ERFDA_SHIFT       (28U)
#define FLEXCAN_ERFSR_ERFDA_MASK        (1UL << FLEXCAN_ERFSR_ERFDA_SHIFT)
#define FLEXCAN_ERFSR_ERFDA_WIDTH       (1U)
#define FLEXCAN_ERFSR_ERFCLR_SHIFT      (27U)
#define FLEXCAN_ERFSR_ERFCLR_MASK       (1UL << FLEXCAN_ERFSR_ERFCLR_SHIFT)
#define FLEXCAN_ERFSR_ERFCLR_WIDTH      (1U)
#define FLEXCAN_ERFSR_ERFE_SHIFT        (17U)
#define FLEXCAN_ERFSR_ERFE_MASK         (1UL << FLEXCAN_ERFSR_ERFE_SHIFT)
#define FLEXCAN_ERFSR_ERFE_WIDTH        (1U)
#define FLEXCAN_ERFSR_ERFF_SHIFT        (16U)
#define FLEXCAN_ERFSR_ERFF_MASK         (1UL << FLEXCAN_ERFSR_ERFF_SHIFT)
#define FLEXCAN_ERFSR_ERFF_WIDTH        (1U)
#define FLEXCAN_ERFSR_ERFEL_SHIFT       (0U)
#define FLEXCAN_ERFSR_ERFEL_MASK        (0x3FUL << FLEXCAN_ERFSR_ERFEL_SHIFT)
#define FLEXCAN_ERFSR_ERFEL_WIDTH       (6U)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief The definition of FLEXCAN registers
 */
typedef struct _FlexCanRegType_
{
    volatile uint32_t MCR;                /*!< module configuration register, offset: 0000H */
    volatile uint32_t CTRL1;              /*!< control1 register, offset: 0004H */
    volatile uint32_t TIMER;              /*!< free running timer register, offset: 0008H */
    volatile uint32_t REVERSED0;          /*!< resverd register, offset: 000CH */
    volatile uint32_t RXMGMASK;           /*!< rx mailbox global mask register, offset: 0010H */
    volatile uint32_t RX14MASK;           /*!< rx 14 mask register, offset: 0014H */
    volatile uint32_t RX15MASK;           /*!< rx 15 mask register, offset: 0018H */
    volatile uint32_t ECR;                /*!< error countner register, offset: 001CH */
    volatile uint32_t ESR1;               /*!< error and status 1 register, offset: 0020H */
    volatile uint32_t IMASK2;             /*!< interrupt mask 2 register, offset: 0024H */
    volatile uint32_t IMASK1;             /*!< interrupt mask 1 register, offset: 0028H */
    volatile uint32_t IFLAG2;             /*!< interrupt flags 2 register, offset: 002CH */
    volatile uint32_t IFLAG1;             /*!< interrupt flags 1 register, offset: 0030H */
    volatile uint32_t CTRL2;              /*!< control 2 register, offset: 0034H */
    volatile uint32_t ESR2;               /*!< error and status 2 register, offset: 0038H */
    volatile uint32_t REVERSED1[2];       /*!< reversed register, offset: 003CH */
    volatile uint32_t CRCR;               /*!< crc register, offset: 0044H */
    volatile uint32_t RXFGMASK;           /*!< rx fifo global mask register, offset: 0048H */
    volatile uint32_t RXFIR;              /*!< rx fifo information register, offset: 004CH */
    volatile uint32_t CBT;                /*!< CAN bit timing register, offset: 0050H */
    volatile uint32_t REVERSED2[5];       /*!< reversed register, offset: 0054H */
    volatile uint32_t IMASK4;             /*!< interrupt mask 4 register, offset: 0068H */
    volatile uint32_t IMASK3;             /*!< interrupt mask 3 register, offset: 006CH */
    volatile uint32_t IFLAG4;             /*!< interrupt flags 4 register, offset: 0070H */
    volatile uint32_t IFLAG3;             /*!< interrupt flags 3 register, offset: 0074H */
    volatile uint32_t REVERSED3[2];       /*!< reversed registers, offset: 0078H */
    volatile uint32_t MSGBUF[512];        /*!< message buffers, offset: 0080H */
    volatile uint32_t RXIMR[128];         /*!< rx individual mask registers, offset: 0880H */
    volatile uint32_t REVERSED4[24];      /*!< reversed register, offset: 0A80H */
    volatile uint32_t MECR;               /*!< memory error control register, offset: 0AE0H */
    volatile uint32_t ERRIAR;             /*!< error injection address register, offset: 0AE4H */
    volatile uint32_t ERRIDPR;            /*!< error injection data pattern register, offset: 0AE8H */
    volatile uint32_t ERRIPPR;            /*!< error injection parity pattern register, offset: 0AECH */
    volatile uint32_t RERRAR;             /*!< error report address register, offset: 0AF0H */
    volatile uint32_t RERRDR;             /*!< error report data register, offset: 0AF4H */
    volatile uint32_t RERRSYNR;           /*!< error report syndrome register, offset: 0AF8H */
    volatile uint32_t ERRSR;              /*!< error status register, offset: 0AFCH */
    volatile uint32_t CTRL1_PN;           /*!< pretended networking control 1 register, offset: 0B00H */
    volatile uint32_t CTRL2_PN;           /*!< pretended networking control 2 register, offset: 0B04H */
    volatile uint32_t WU_MTC;             /*!< pretended networking wake up match register, offset: 0B08H */
    volatile uint32_t FLT_ID1;            /*!< pretended networking ID filter 1 register, offset: 0B0CH */
    volatile uint32_t FLT_DLC;            /*!< pretended networking DLC filter register, offset: 0B10H */
    volatile uint32_t PL1_LO;             /*!< pretended networking payload low filter 1 register, offset: 0B14H */
    volatile uint32_t PL1_HI;             /*!< pretended networking payload high filter 1 register, offset: 0B18H */
    volatile uint32_t FLT_ID2_IDMASK;     /*!< pretended networking ID filter 2 register / ID mask register, offset: 0B1CH */
    volatile uint32_t PL2_PLMASK_LO;      /*!< pretended networking payload low filter 2 register / payload low mask register, offset: 0B20H */
    volatile uint32_t PL2_PLMASK_HI;      /*!< pretended networking payload high filter 2 high order bits / payload high mask register, offset: 0B24H */
    volatile uint32_t REVERSED5[6];       /*!< reversed registers, offset: 0B28H */
    volatile uint32_t WMB0_CS;            /*!< wakeup message buffer 0 register for C/S, offset: 0B40H */
    volatile uint32_t WMB0_ID;            /*!< wakeup message buffer 0 register for ID, offset: 0B44H */
    volatile uint32_t WMB0_D03;           /*!< wakeup message buffer 0 register for data 0 - 3, offset: 0B48H */
    volatile uint32_t WMB0_D47;           /*!< wakeup message buffer 0 register for data 4 - 7, offset: 0B4CH */
    volatile uint32_t WMB1_CS;            /*!< wakeup message buffer 1 register for C/S, offset: 0B50H */
    volatile uint32_t WMB1_ID;            /*!< wakeup message buffer 1 register for ID, offset: 0B54H */
    volatile uint32_t WMB1_D03;           /*!< wakeup message buffer 1 register for data 0 - 3, offset: 0B58H */
    volatile uint32_t WMB1_D47;           /*!< wakeup message buffer 1 register for data 4 - 7, offest: 0B5CH */
    volatile uint32_t WMB2_CS;            /*!< wakeup message buffer 2 register for C/S, offset: 0B60H */
    volatile uint32_t WMB2_ID;            /*!< wakeup message buffer 2 register for ID, offset: 0B64H */
    volatile uint32_t WMB2_D03;           /*!< wakeup message buffer 2 register for data 0 - 3, offset: 0B68H */
    volatile uint32_t WMB2_D47;           /*!< wakeup message buffer 2 register for data 4 - 7, offest: 0B6CH */
    volatile uint32_t WMB3_CS;            /*!< wakeup message buffer 3 register for C/S, offset: 0B70H */
    volatile uint32_t WMB3_ID;            /*!< wakeup message buffer 3 register for ID, offset: 0B74H */
    volatile uint32_t WMB3_D03;           /*!< wakeup message buffer 3 register for data 0 - 3, offset: 0B78H */
    volatile uint32_t WMB3_D47;           /*!< wakeup message buffer 3 register for data 4 - 7, offest: 0B7CH */
    volatile uint32_t REVERSED6[28];      /*!< reversed registers, offset: 0B80H */
    volatile uint32_t EPRS;               /*!< Enhanced CAN Bit timing prescalers register, offset: 0BF0H */
    volatile uint32_t ENCBT;              /*!< Enhanced nominal CAN Bit timing register, offset: 0BF4H */
    volatile uint32_t EDCBT;              /*!< Enhanced data phase CAN bit timing register, offset: 0BF8H */
    volatile uint32_t REVERSED7;          /*!< reversed registers, offset: 0BFCH */
    volatile uint32_t FDCTRL;             /*!< CAN FD control register, offset: 0C00H */
    volatile uint32_t FDCBT;              /*!< CAN FD bit timing register, offset: 0C04H */
    volatile uint32_t FDCRC;              /*!< CAN FD CRC register, offset: 0C08H */
    volatile uint32_t ERFCR;              /*!< Enhanced Rx FIFO control register, offset: 0C0CH */
    volatile uint32_t ERFIER;             /*!< Enhanced Rx FIFO interrupt enable register, offset: 0C10H */
    volatile uint32_t ERFSR;              /*!< Enhanced Rx FIFO Status register, offset: 0C14H */
    volatile uint32_t REVERSED8[6];       /*!< reversed registers, offset: 0C18H */
    volatile uint32_t HR_TIME_STAMP[128]; /*!< High resolution time stamp registers, offset: 0C30H */
    volatile uint32_t REVERSED9[1140];    /*!< reversed registers, offset: 0E30H */
    volatile uint32_t ENHRXFIFO[640];     /*!< Enhanced Rx FIFO, offset: 2000H */
    volatile uint32_t REVERSED10[384];    /*!< reversed registers, offset: 0E30H */
    volatile uint32_t ERFFEL[128];        /*!< Enhanced Rx FIFO filter element reigster, offset: 3000H */
} FlexCanRegType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/
/*! \brief Get message buffer start address
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return message buffer start address
 *
 */
__attribute__((always_inline)) static inline uint32_t FlexCanReg_GetMsgBufferStartAddr(FlexCanRegType *obj)
{
    return (uint32_t)(&obj->MSGBUF[0]);
}

/*! \brief Get enhanced Rx FIFO start address
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return enhanced Rx FIFO start address
 *
 */
__attribute__((always_inline)) static inline uint32_t FlexCanReg_GetEnhRxFifoStartAddr(FlexCanRegType *obj)
{
    return (uint32_t)(&obj->ENHRXFIFO[0]);
}

/*! \brief Get enhanced Rx FIFO filter start address
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return enhanced Rx FIFO filter start address
 *
 */
__attribute__((always_inline)) static inline uint32_t FlexCanReg_GetEnhRxFifoFilterStartAddr(FlexCanRegType *obj, uint8_t filtElementNo)
{
    return (uint32_t)(&obj->ERFFEL[filtElementNo]);
}

/*! \brief Get FlexCAN module disable status
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return module disable status
 *              -0b： enable the FlexCAN module
 *              -1b： disable the FlexCAN module
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetModuleDisable(FlexCanRegType *obj)
{
    return (uint8_t)((obj->MCR & FLEXCAN_MCR_MDIS_MASK) >> FLEXCAN_MCR_MDIS_SHIFT);
}

/*! \brief Set FlexCAN module enable
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] enable : module enable
 *              -0b： enable the FlexCAN module
 *              -1b： disable the FlexCAN module
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetModuleDisable(FlexCanRegType *obj, uint8_t isDisable)
{
    uint32_t tempReg;
    tempReg = obj->MCR;
    tempReg &= (~FLEXCAN_MCR_MDIS_MASK);
    tempReg |= (((uint32_t)isDisable) << FLEXCAN_MCR_MDIS_SHIFT) & FLEXCAN_MCR_MDIS_MASK;

    obj->MCR = tempReg;
}

/*! \brief Get freeze mode
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return freeze mode
 *              -0b： not enabled to enter freeze mode
 *              -1b： enabled to enter freeze mode
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetFreezeMode(FlexCanRegType *obj)
{
    return (uint8_t)((obj->MCR & FLEXCAN_MCR_FRZ_MASK) >> FLEXCAN_MCR_FRZ_SHIFT);
}

/*! \brief Set freeze mode
 *
 * \param[in] obj : pointer to flexCAN register instance
 * \param[in] frzModeReq : freeze mode request
 *              -0b： not enabled to enter freeze mode
 *              -1b： enabled to enter freeze mode
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetFreezeMode(FlexCanRegType *obj, uint8_t frzModeReq)
{
    uint32_t tempReg;
    tempReg = obj->MCR;
    tempReg &= (~FLEXCAN_MCR_FRZ_MASK);
    tempReg |= (((uint32_t)frzModeReq) << FLEXCAN_MCR_FRZ_SHIFT) & FLEXCAN_MCR_FRZ_MASK;

    obj->MCR = tempReg;
}

/*! \brief Get Rx FIFO enable status
 *
 * \param[in] obj : pointer to flexCAN register instance
 * \return freeze mode
 *              -0b： Rx FIFO not enable
 *              -1b： Rx FIFO enable
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetRxFIFOEnable(FlexCanRegType *obj)
{
    return (uint8_t)((obj->MCR & FLEXCAN_MCR_RFEN_MASK) >> FLEXCAN_MCR_RFEN_SHIFT);
}

/*! \brief Set Rx FIFO enable status
 *
 * \param[in] obj : pointer to flexCAN register instance
 * \param[in] fifoEnable : rx FIFO enable status
 *              -0b： Rx FIFO not enable
 *              -1b： Rx FIFO enable
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetRxFIFOEnalbe(FlexCanRegType *obj, uint8_t fifoEnable)
{
    uint32_t tempReg;
    tempReg = obj->MCR;
    tempReg &= (~FLEXCAN_MCR_RFEN_MASK);
    tempReg |= (((uint32_t)fifoEnable) << FLEXCAN_MCR_RFEN_SHIFT) & FLEXCAN_MCR_RFEN_MASK;

    obj->MCR = tempReg;
}

/*! \brief Get halt mode
 *
 * \param[in] obj : pointer to flexCAN register instance
 * \return halt mode
 *              -0b： request halt mode
 *              -1b： no halt mode reuqest
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetHaltMode(FlexCanRegType *obj)
{
    return (uint8_t)((obj->MCR & FLEXCAN_MCR_HALT_MASK) >> FLEXCAN_MCR_HALT_SHIFT);
}

/*! \brief Set halt mode
 *
 * \param[in] obj : pointer to flexCAN register instance
 * \param[in] haltModeReq : halt mode request
 *              -0b： request halt mode
 *              -1b： no halt mode reuqest
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetHaltMode(FlexCanRegType *obj, uint8_t haltModeReq)
{
    uint32_t tempReg;
    tempReg = obj->MCR;
    tempReg &= (~FLEXCAN_MCR_HALT_MASK);
    tempReg |= (((uint32_t)haltModeReq) << FLEXCAN_MCR_HALT_SHIFT) & FLEXCAN_MCR_HALT_MASK;

    obj->MCR = tempReg;
}

/*! \brief Get not ready flag
 *
 * \param[in] obj : pointer to flexCAN register instance
 * \return not ready flag
 *              -0b： FlexCAN is either in normal, listen-only, or loop-back mode
 *              -1b： FlexCAN is either in module disable, doze, stop, or freeze mode
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetNotReadyFlag(FlexCanRegType *obj)
{
    return (uint8_t)((obj->MCR & FLEXCAN_MCR_NOTRDY_MASK) >> FLEXCAN_MCR_NOTRDY_SHIFT);
}

/*! \brief Get wakeup interrupt mask
 *
 * \param[in] obj : pointer to flexCAN register instance
 * \return wakeup interrupt mask
 *              -0b： disable wakeup interrupt
 *              -1b： enable wakeup interrupt
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetWakupIntMask(FlexCanRegType *obj)
{
    return (uint8_t)((obj->MCR & FLEXCAN_MCR_WAKMSK_MASK) >> FLEXCAN_MCR_WAKMSK_SHIFT);
}

/*! \brief Set wakeup interrupt mask
 *
 * \param[in] obj : pointer to flexCAN register instance
 * \param[in] enable : wakeup interrupt mask enable
 *              -0b： disable wakeup interrupt
 *              -1b： enable wakeup interrupt
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetWakeupIntMask(FlexCanRegType *obj, uint8_t enable)
{
    uint32_t tempReg;
    tempReg = obj->MCR;
    tempReg &= (~FLEXCAN_MCR_WAKMSK_MASK);
    tempReg |= (((uint32_t)enable) << FLEXCAN_MCR_WAKMSK_SHIFT) & FLEXCAN_MCR_WAKMSK_MASK;

    obj->MCR = tempReg;
}

/*! \brief Get soft reset request
 *
 * \param[in] obj : pointer to flexCAN register instance
 * \return soft reset request
 *              -0b： reset the registers affected by soft reset
 *              -1b： no reset request
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetSoftResetRequest(FlexCanRegType *obj)
{
    return (uint8_t)((obj->MCR & FLEXCAN_MCR_SOFTRST_MASK) >> FLEXCAN_MCR_SOFTRST_SHIFT);
}

/*! \brief Set soft reset request
 *
 * \param[in] obj : pointer to flexCAN register instance
 * \param[in] enable : soft reset request
 *              -0b : reset the registers affected by soft reset
 *              -1b : no reset request
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetSoftResetRequest(FlexCanRegType *obj, uint8_t softRstReq)
{
    uint32_t tempReg;
    tempReg = obj->MCR;
    tempReg &= (~FLEXCAN_MCR_SOFTRST_MASK);
    tempReg |= (((uint32_t)softRstReq) << FLEXCAN_MCR_SOFTRST_SHIFT) & FLEXCAN_MCR_SOFTRST_MASK;

    obj->MCR = tempReg;
}

/*! \brief Get freeze mode acknowledge
 *
 * \param[in] obj : pointer to flexCAN register instance
 * \return freeze mode acknowledge
 *              -0b : FlexCAN not in freeze mode, prescaler running
 *              -1b : FlexCAN in freeze mode, prescaler stopped
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetFreezeAck(FlexCanRegType *obj)
{
    return (uint8_t)((obj->MCR & FLEXCAN_MCR_FRZACK_MASK) >> FLEXCAN_MCR_FRZACK_SHIFT);
}

/*! \brief Get FlexCAN access mode
 *
 * \param[in] obj : pointer to flexCAN register instance
 * \return access mode
 *              -0b : FlexCAN is in user mode, affected registers allow both
 *                    supervisor and unrestricted access
 *              -1b : FlexCAN is in supervisor mode. Affected registers allow
 *                    only supervisor access. Unrestricted access behaves as
 *                    though the access was done to an unnimplemented register
 *                    location.
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetAccessMode(FlexCanRegType *obj)
{
    return (uint8_t)((obj->MCR & FLEXCAN_MCR_SUPV_MASK) >> FLEXCAN_MCR_SUPV_SHIFT);
}

/*! \brief Set FlexCAN access mode
 *
 * \param[in] obj : pointer to flexCAN register instance
 * \param[in] accMode : access mode
 *              -0b : FlexCAN is in user mode, affected registers allow both
 *                    supervisor and unrestricted access
 *              -1b : FlexCAN is in supervisor mode. Affected registers allow
 *                    only supervisor access. Unrestricted access behaves as
 *                    though the access was done to an unimplemented register
 *                    location.
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetAccessMode(FlexCanRegType *obj, uint8_t accMode)
{
    uint32_t tempReg;
    tempReg = obj->MCR;
    tempReg &= (~FLEXCAN_MCR_SUPV_MASK);
    tempReg |= (((uint32_t)accMode) << FLEXCAN_MCR_SUPV_SHIFT) & FLEXCAN_MCR_SUPV_MASK;

    obj->MCR = tempReg;
}

/*! \brief Get self wakeup enable
 *
 * \param[in] obj : pointer to flexCAN register instance
 * \return self wakeup enable
 *              -0b : Disable FlexCAN self wakeup feature
 *              -1b : Enable FlexCAN self wakeup feature
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetSelfWakeupEnable(FlexCanRegType *obj)
{
    return (uint8_t)((obj->MCR & FLEXCAN_MCR_SLFWAK_MASK) >> FLEXCAN_MCR_SLFWAK_SHIFT);
}

/*! \brief Get self wakeup enable
 *
 * \param[in] obj : pointer to flexCAN register instance
 * \param[in] enable : self wakeup enable
 *              -0b : Disable FlexCAN self wakeup feature
 *              -1b : Enable FlexCAN self wakeup feature
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetSelfWakeupEnable(FlexCanRegType *obj, uint8_t enable)
{
    uint32_t tempReg;
    tempReg = obj->MCR;
    tempReg &= (~FLEXCAN_MCR_SLFWAK_MASK);
    tempReg |= (((uint32_t)enable) << FLEXCAN_MCR_SLFWAK_SHIFT) & FLEXCAN_MCR_SLFWAK_MASK;

    obj->MCR = tempReg;
}

/*! \brief Get self warning interrupt enable
 *
 * \param[in] obj : pointer to flexCAN register instance
 * \return warning interrupt enable
 *              -0b : warning interrupt not enable
 *              -1b : warning interrupt enable
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetWarningIntEnable(FlexCanRegType *obj)
{
    return (uint8_t)((obj->MCR & FLEXCAN_MCR_WRNEN_MASK) >> FLEXCAN_MCR_WRNEN_SHIFT);
}

/*! \brief Set self warning interrupt enable
 *
 * \param[in] obj : pointer to flexCAN register instance
 * \param[in] enable : warning interrupt enable
 *              -0b : warning interrupt not enable
 *              -1b : warning interrupt enable
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetWarningIntEnable(FlexCanRegType *obj, uint8_t enable)
{
    uint32_t tempReg;
    tempReg = obj->MCR;
    tempReg &= (~FLEXCAN_MCR_WRNEN_MASK);
    tempReg |= (((uint32_t)enable) << FLEXCAN_MCR_WRNEN_SHIFT) & FLEXCAN_MCR_WRNEN_MASK;

    obj->MCR = tempReg;
}

/*! \brief Get low power mode acknowledge
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return low power mode acknowledge
 *              -0b : FlexCAN is not in a low power mode
 *              -1b : FlexCAN is in a low power mode
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetLowPowerAck(FlexCanRegType *obj)
{
    return (uint8_t)((obj->MCR & FLEXCAN_MCR_LPMACK_MASK) >> FLEXCAN_MCR_LPMACK_SHIFT);
}

/*! \brief Get wake up source
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return wake up source
 *              -0b : FlexCAN uses the unfiltered Rx input to detect recessive-to-dominant edges on the CAN bus
 *              -1b : FlexCAN uses the filtered Rx input to detect recessive-to-dominant edges on the CAN bus
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetWakeupSource(FlexCanRegType *obj)
{
    return (uint8_t)((obj->MCR & FLEXCAN_MCR_WAKSRC_MASK) >> FLEXCAN_MCR_WAKSRC_SHIFT);
}

/*! \brief Set wake up source
 *
 * \param[in] obj : pointer to flexCAN register instance
 * \param[in] enable : wake up source
 *              -0b : FlexCAN uses the unfiltered Rx input to detect recessive-to-dominant edges on the CAN bus
 *              -1b : FlexCAN uses the filtered Rx input to detect recessive-to-dominant edges on the CAN bus
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetWakeupSource(FlexCanRegType *obj, uint8_t enable)
{
    uint32_t tempReg;
    tempReg = obj->MCR;
    tempReg &= (~FLEXCAN_MCR_WAKSRC_MASK);
    tempReg |= (((uint32_t)enable) << FLEXCAN_MCR_WAKSRC_SHIFT) & FLEXCAN_MCR_WAKSRC_MASK;

    obj->MCR = tempReg;
}

/*! \brief Get doze mode enable
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return doze mode enable
 *              -0b : FlexCAN is not enabled to enter low-power mode when Doze mode is request
 *              -1b : FlexCAN is enabled to enter low-power mode when Doze mode is request
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetDozeMode(FlexCanRegType *obj)
{
    return (uint8_t)((obj->MCR & FLEXCAN_MCR_DOZE_MASK) >> FLEXCAN_MCR_DOZE_SHIFT);
}

/*! \brief Set doze mode enable
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] enable : doze mode enable
 *              -0b : FlexCAN is not enabled to enter low-power mode when Doze mode is request
 *              -1b : FlexCAN is enabled to enter low-power mode when Doze mode is request
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetDozeMode(FlexCanRegType *obj, uint8_t enable)
{
    uint32_t tempReg;
    tempReg = obj->MCR;
    tempReg &= (~FLEXCAN_MCR_DOZE_MASK);
    tempReg |= (((uint32_t)enable) << FLEXCAN_MCR_DOZE_SHIFT) & FLEXCAN_MCR_DOZE_MASK;

    obj->MCR = tempReg;
}

/*! \brief Get self reception
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return self reception enable
 *              -0b : self reception enable
 *              -1b : self reception disable
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetSelfReceptionDisable(FlexCanRegType *obj)
{
    return (uint8_t)((obj->MCR & FLEXCAN_MCR_SRXDIS_MASK) >> FLEXCAN_MCR_SRXDIS_SHIFT);
}

/*! \brief Set self reception
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] enable : self reception enable
 *              -0b : self reception enable
 *              -1b : self reception disable
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetSelfReceptionDisable(FlexCanRegType *obj, uint8_t isDisable)
{
    uint32_t tempReg;
    tempReg = obj->MCR;
    tempReg &= (~FLEXCAN_MCR_SRXDIS_MASK);
    tempReg |= (((uint32_t)isDisable) << FLEXCAN_MCR_SRXDIS_SHIFT) & FLEXCAN_MCR_SRXDIS_MASK;

    obj->MCR = tempReg;
}

/*! \brief Get rx individual mask
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return individual mask enable
 *              -0b : individual mask disable
 *              -1b : individual mask enable
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetIndividualMaskEnable(const FlexCanRegType *obj)
{
    return ((obj->MCR & FLEXCAN_MCR_IRQM_MASK) >> FLEXCAN_MCR_IRQM_SHIFT);
}

/*! \brief Set rx individual mask
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] enable : self reception enable
 *              -0b : self reception disable
 *              -1b : self reception enable
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetIndividualMaskEnable(FlexCanRegType *obj, uint8_t enable)
{
    uint32_t tempReg;
    tempReg = obj->MCR;
    tempReg &= (~FLEXCAN_MCR_IRQM_MASK);
    tempReg |= (((uint32_t)enable) << FLEXCAN_MCR_IRQM_SHIFT) & FLEXCAN_MCR_IRQM_MASK;

    obj->MCR = tempReg;
}

/*! \brief Get rx fifo dma enable or disable
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return rx fifo dma enable
 *          -0b : rx fifo dma disable
 *          -1b : rx fifo dma enable
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetRxFIFODmaEnable(const FlexCanRegType *obj)
{
    return ((obj->MCR & FLEXCAN_MCR_DMA_MASK) >> FLEXCAN_MCR_DMA_SHIFT);
}

/*! \brief Set rx fifo dma enable or disable
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] enable : rx fifo dma enable
 *              -0b : rx fifo dma disable
 *              -1b : rx fifo dma enable
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetRxFIFODmaEnable(FlexCanRegType *obj, uint8_t enable)
{
    uint32_t tempReg;
    tempReg = obj->MCR;
    tempReg &= (~FLEXCAN_MCR_DMA_MASK);
    tempReg |= (((uint32_t)enable) << FLEXCAN_MCR_DMA_SHIFT) & FLEXCAN_MCR_DMA_MASK;

    obj->MCR = tempReg;
}

/*! \brief Get local priority enable
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return local priority enable
 *          -0b : local priority disable
 *          -1b : local priority enable
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetMcrLprioen(const FlexCanRegType *obj)
{
    return ((obj->MCR & FLEXCAN_MCR_LPRIOEN_MASK) >> FLEXCAN_MCR_LPRIOEN_SHIFT);
}

/*! \brief Set local priority enable
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] enable : local priority enable
 *              -0b : local priority disable
 *              -1b : local priority enable
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetMcrLprioen(FlexCanRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MCR;

    tmp &= ~FLEXCAN_MCR_LPRIOEN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << FLEXCAN_MCR_LPRIOEN_SHIFT)) & FLEXCAN_MCR_LPRIOEN_MASK);
    obj->MCR = tmp;
}

/*! \brief Set rx acceptance id mode
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] idam : rx acceptance id mode
 *              00b - Format A – One full ID (standard and extended) per ID Filter Table element.
 *              01b - Format B – Two full standard IDs or two partial 14-bit (standard and extended) IDs per ID Filter Table element.
 *              10b - Format C – Four partial 8-bit standard IDs per ID Filter Table element.
 *              11b - Format D – All frames rejected.
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetRxIdAcceptanceMode(FlexCanRegType *obj, uint8_t idam)
{
    uint32_t tempReg;
    tempReg = obj->MCR;
    tempReg &= (~FLEXCAN_MCR_IDAM_MASK);
    tempReg |= (((uint32_t)idam) << FLEXCAN_MCR_IDAM_SHIFT) & FLEXCAN_MCR_IDAM_MASK;

    obj->MCR = tempReg;
}

/*! \brief Get rx acceptance id mode
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return rx acceptance id mode
 *              00b - Format A – One full ID (standard and extended) per ID Filter Table element.
 *              01b - Format B – Two full standard IDs or two partial 14-bit (standard and extended) IDs per ID Filter Table element.
 *              10b - Format C – Four partial 8-bit standard IDs per ID Filter Table element.
 *              11b - Format D – All frames rejected.
 */
__attribute__((always_inline)) static inline uint32_t FlexCanReg_GetRxIdAcceptanceMode(FlexCanRegType *obj)
{
    uint8_t  idam = 0;
    uint32_t tempReg;

    tempReg = obj->MCR;

    idam = ((tempReg & FLEXCAN_MCR_IDAM_MASK) >> FLEXCAN_MCR_IDAM_SHIFT);

    return idam;
}

/*! \brief Set max buffer numbers
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] maxNum : max buffer numbers
 *
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetMaxMsgBufferNum(FlexCanRegType *obj, uint8_t maxNum)
{
    uint32_t tempReg;
    tempReg = obj->MCR;
    tempReg &= (~FLEXCAN_MCR_MAXMB_MASK);
    tempReg |= (((uint32_t)maxNum) << FLEXCAN_MCR_MAXMB_SHIFT) & FLEXCAN_MCR_MAXMB_MASK;

    obj->MCR = tempReg;
}

/*! \brief Get max buffer numbers
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return max buffer numbers
 *
 */
__attribute__((always_inline)) static inline uint32_t FlexCanReg_GetMaxMsgBufferNum(FlexCanRegType *obj)
{
    uint8_t  maxNum;
    uint32_t tempReg;

    tempReg = obj->MCR;

    maxNum = ((tempReg & FLEXCAN_MCR_MAXMB_MASK) >> FLEXCAN_MCR_MAXMB_SHIFT);

    return maxNum;
}

/*! \brief Get Pretended Networking Enable
 *
 * \param[in] obj : pointer to flexCAN register instance
 * \return Pretended Networking Enable
 *              0b - Disable Pretended Networking mode.
 *              1b - Enable Pretended Networking mode.
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetMcrPneten(const FlexCanRegType *obj)
{
    return ((obj->MCR & FLEXCAN_MCR_PNET_EN_MASK) >> FLEXCAN_MCR_PNET_EN_SHIFT);
}

/*! \brief Pretended Networking Enable – Enables the Pretended Networking functionality:
 *
 * \param[in] obj : pointer to flexCAN register instance
 * \param[in] value : enable or disable pn mode
 * \return Tx message pending abort mechanism enable
 *              0b - Disable Pretended Networking mode.
 *              1b - Enable Pretended Networking mode.
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetMcrPneten(FlexCanRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MCR;

    tmp &= ~FLEXCAN_MCR_PNET_EN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << FLEXCAN_MCR_PNET_EN_SHIFT)) & FLEXCAN_MCR_PNET_EN_MASK);
    obj->MCR = tmp;
}

/*! \brief Get Tx message pending abort mechanism enable
 *
 * \param[in] obj : pointer to flexCAN register instance
 * \return Tx message pending abort mechanism enable
 *              -0b： disable abort
 *              -1b： enable abort
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetTxAbortEnable(FlexCanRegType *obj)
{
    return (uint8_t)((obj->MCR & FLEXCAN_MCR_AEN_MASK) >> FLEXCAN_MCR_AEN_SHIFT);
}

/*! \brief Set Tx message pending abort mechanism enable
 *
 * \param[in] obj : pointer to flexCAN register instance
 * \param[in] enable : Tx message pending abort mechanism enable
 *              -0b： disable abort
 *              -1b： enable abort
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetTxAbortEnable(FlexCanRegType *obj, uint8_t enable)
{
    uint32_t tempReg;
    tempReg = obj->MCR;
    tempReg &= (~FLEXCAN_MCR_AEN_MASK);
    tempReg |= (((uint32_t)enable) << FLEXCAN_MCR_AEN_SHIFT) & FLEXCAN_MCR_AEN_MASK;

    obj->MCR = tempReg;
}

/*! \brief Set CAN FD feature enable
 *
 * \param[in] obj : pointer to flexCAN register instance
 * \param[in] enable : CAN FD feature enable
 *              -0b： disable
 *              -1b： enable
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetFdEnable(FlexCanRegType *obj, uint8_t enable)
{
    uint32_t tempReg;
    tempReg = obj->MCR;
    tempReg &= (~FLEXCAN_MCR_FDEN_MASK);
    tempReg |= (((uint32_t)enable) << FLEXCAN_MCR_FDEN_SHIFT) & FLEXCAN_MCR_FDEN_MASK;

    obj->MCR = tempReg;
}

/*! \brief Get CAN FD feature enable
 *
 * \param[in] obj : pointer to flexCAN register instance
 * \return CAN FD feature enable
 *              -0b： disable
 *              -1b： enable
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetFdEnable(FlexCanRegType *obj)
{
    uint8_t  enable = 0;
    uint32_t tempReg;

    tempReg = obj->MCR;

    if(((tempReg & FLEXCAN_MCR_FDEN_MASK) >> FLEXCAN_MCR_FDEN_SHIFT) != 0u)
    {
        enable = 1;
    }

    return enable;
}

/*! \brief Get prescaler division factor
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: prescaler division factor
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetCtrl1Presdiv(const FlexCanRegType *obj)
{
    return ((obj->CTRL1 & FLEXCAN_CTRL1_PRESDIV_MASK) >> FLEXCAN_CTRL1_PRESDIV_SHIFT);
}

/*! \brief Set prescaler division factor
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] value : prescaler division factor
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetCtrl1Presdiv(FlexCanRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CTRL1;

    tmp &= ~FLEXCAN_CTRL1_PRESDIV_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << FLEXCAN_CTRL1_PRESDIV_SHIFT)) & FLEXCAN_CTRL1_PRESDIV_MASK);
    obj->CTRL1 = tmp;
}

/*! \brief Get resync jump width
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: resync jump width
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetCtrl1Rjw(const FlexCanRegType *obj)
{
    return ((obj->CTRL1 & FLEXCAN_CTRL1_RJW_MASK) >> FLEXCAN_CTRL1_RJW_SHIFT);
}

/*! \brief Set resync jump width
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] value : resync jump width
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetCtrl1Rjw(FlexCanRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CTRL1;

    tmp &= ~FLEXCAN_CTRL1_RJW_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << FLEXCAN_CTRL1_RJW_SHIFT)) & FLEXCAN_CTRL1_RJW_MASK);
    obj->CTRL1 = tmp;
}

/*! \brief Get phase segment 1
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: phase segment 1
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetCtrl1Pseg1(const FlexCanRegType *obj)
{
    return ((obj->CTRL1 & FLEXCAN_CTRL1_PSEG1_MASK) >> FLEXCAN_CTRL1_PSEG1_SHIFT);
}

/*! \brief Set phase segment 1
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] value : phase segment 1
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetCtrl1Pseg1(FlexCanRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CTRL1;

    tmp &= ~FLEXCAN_CTRL1_PSEG1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << FLEXCAN_CTRL1_PSEG1_SHIFT)) & FLEXCAN_CTRL1_PSEG1_MASK);
    obj->CTRL1 = tmp;
}

/*! \brief Get phase segment 2
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: phase segment 2
 */
__attribute__((always_inline)) static inline uint8_t CanReg_GetCtrl1Pseg2(const FlexCanRegType *obj)
{
    return ((obj->CTRL1 & FLEXCAN_CTRL1_PSEG2_MASK) >> FLEXCAN_CTRL1_PSEG2_SHIFT);
}

/*! \brief Set phase segment 2
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] value : phase segment 2
 */
__attribute__((always_inline)) static inline void CanReg_SetCtrl1Pseg2(FlexCanRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CTRL1;

    tmp &= ~FLEXCAN_CTRL1_PSEG2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << FLEXCAN_CTRL1_PSEG2_SHIFT)) & FLEXCAN_CTRL1_PSEG2_MASK);
    obj->CTRL1 = tmp;
}

/*! \brief Set bus off interrupt enable
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] enable : bus off interrupt enable
 *              -0b : bus off interrupt disabled
 *              -1b : bus off interrupt enable
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetBusOffIntEnable(FlexCanRegType *obj, uint8_t enable)
{
    uint32_t tempReg;
    tempReg = obj->CTRL1;
    tempReg &= (~FLEXCAN_CTRL1_BOFFMSK_MASK);
    tempReg |= (((uint32_t)enable) << FLEXCAN_CTRL1_BOFFMSK_SHIFT) & FLEXCAN_CTRL1_BOFFMSK_MASK;

    obj->CTRL1 = tempReg;
}

/*! \brief Get bus off interrupt enable
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: bus off interrupt enable
 *              -0b : bus off interrupt disabled
 *              -1b : bus off interrupt enable
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetBusOffIntEnable(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->CTRL1) & FLEXCAN_CTRL1_BOFFMSK_MASK) >> FLEXCAN_CTRL1_BOFFMSK_SHIFT);
}

/*! \brief Set error interrupt enable
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] enable : error interrupt enable
 *              -0b : error interrupt disabled
 *              -1b : error interrupt enable
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetErrorIntEnable(FlexCanRegType *obj, uint8_t enable)
{
    uint32_t tempReg;
    tempReg = obj->CTRL1;
    tempReg &= (~FLEXCAN_CTRL1_ERRMSK_MASK);
    tempReg |= (((uint32_t)enable) << FLEXCAN_CTRL1_ERRMSK_SHIFT) & FLEXCAN_CTRL1_ERRMSK_MASK;

    obj->CTRL1 = tempReg;
}

/*! \brief Get error interrupt enable
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: error interrupt enable
 *              -0b : error interrupt disabled
 *              -1b : error interrupt enable
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetErrorIntEnable(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->CTRL1) & FLEXCAN_CTRL1_ERRMSK_MASK) >> FLEXCAN_CTRL1_ERRMSK_SHIFT);
}

/*! \brief Get module clock source
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: module clock source
 *              -0b : The PE clock source is the oscillator clock.
 *              -1b : The PE clock source is the peripheral clock.
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetClockSource(const FlexCanRegType *obj)
{
    return ((obj->CTRL1 & FLEXCAN_CTRL1_CLKSRC_MASK) >> FLEXCAN_CTRL1_CLKSRC_SHIFT);
}

/*! \brief Selects the clock source to the PE submodule to be either the peripheral clock or the oscillator clock
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] clkSrc :
 *              0b - The PE clock source is the oscillator clock.
 *              1b - The PE clock source is the peripheral clock.
 *
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetClockSource(FlexCanRegType *obj, uint8_t clkSrc)
{
    uint32_t tempReg;
    tempReg = obj->CTRL1;
    tempReg &= (~FLEXCAN_CTRL1_CLKSRC_MASK);
    tempReg |= (((uint32_t)clkSrc) << FLEXCAN_CTRL1_CLKSRC_SHIFT) & FLEXCAN_CTRL1_CLKSRC_MASK;

    obj->CTRL1 = tempReg;
}

/*! \brief Get can loop back mode
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: can loop back mode
 *              0b - disable
 *              1b - enable
 */
__attribute__((always_inline)) static inline uint8_t CanReg_GetLoopbackMode(const FlexCanRegType *obj)
{
    return ((obj->CTRL1 & FLEXCAN_CTRL1_LPB_MASK) >> FLEXCAN_CTRL1_LPB_SHIFT);
}

/*! \brief Set can loop back mode
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] enable : loop back mode feature select
 *              0b - disable
 *              1b - enable
 *
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetLoopbackMode(FlexCanRegType *obj, uint8_t enable)
{
    uint32_t tempReg;
    tempReg = obj->CTRL1;
    tempReg &= (~FLEXCAN_CTRL1_LPB_MASK);
    tempReg |= (((uint32_t)enable) << FLEXCAN_CTRL1_LPB_SHIFT) & FLEXCAN_CTRL1_LPB_MASK;

    obj->CTRL1 = tempReg;
}

/*! \brief Set tx warning interrupt enable
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] enable : tx warning interrupt enable
 *              -0b : tx warning interrupt disabled
 *              -1b : tx warning interrupt enable
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetTxWarnIntEnable(FlexCanRegType *obj, uint8_t enable)
{
    uint32_t tempReg;
    tempReg = obj->CTRL1;
    tempReg &= (~FLEXCAN_CTRL1_TWRNMSK_MASK);
    tempReg |= (((uint32_t)enable) << FLEXCAN_CTRL1_TWRNMSK_SHIFT) & FLEXCAN_CTRL1_TWRNMSK_MASK;

    obj->CTRL1 = tempReg;
}

/*! \brief Get tx warning interrupt enable
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: tx warning interrupt enable
 *              -0b : tx warning interrupt disabled
 *              -1b : tx warning interrupt enable
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetTxWarnIntEnable(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->CTRL1) & FLEXCAN_CTRL1_TWRNMSK_MASK) >> FLEXCAN_CTRL1_TWRNMSK_SHIFT);
}

/*! \brief Set rx warning interrupt enable
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] enable : rx warning interrupt enable
 *              -0b : rx warning interrupt disabled
 *              -1b : rx warning interrupt enable
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetRxWarnIntEnable(FlexCanRegType *obj, uint8_t enable)
{
    uint32_t tempReg;
    tempReg = obj->CTRL1;
    tempReg &= (~FLEXCAN_CTRL1_RWRNMSK_MASK);
    tempReg |= (((uint32_t)enable) << FLEXCAN_CTRL1_RWRNMSK_SHIFT) & FLEXCAN_CTRL1_RWRNMSK_MASK;

    obj->CTRL1 = tempReg;
}

/*! \brief Get rx warning interrupt enable
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: rx warning interrupt enable
 *              -0b : rx warning interrupt disabled
 *              -1b : rx warning interrupt enable
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetRxWarnIntEnable(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->CTRL1) & FLEXCAN_CTRL1_RWRNMSK_MASK) >> FLEXCAN_CTRL1_RWRNMSK_SHIFT);
}

/*! \brief Get CAN bit sampling mode
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: CAN bit sampling mode
 *              -0b : one sample is used to determine the bit value
 *              -1b : three samples are used to determine the value of the received bit
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetBitSamplingType(const FlexCanRegType *obj)
{
    return ((obj->CTRL1 & FLEXCAN_CTRL1_SMP_MASK) >> FLEXCAN_CTRL1_SMP_SHIFT);
}

/*! \brief Set bus off automatic recovering enable
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] threeSamplingEn : can bit sampling
 *              -0b : one sample is used to determine the bit value
 *              -1b : three samples are used to determine the value of the received bit
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetBitSamplingType(FlexCanRegType *obj, uint8_t threeSamplingEn)
{
    uint32_t tempReg;
    tempReg = obj->CTRL1;
    tempReg &= (~FLEXCAN_CTRL1_SMP_MASK);
    tempReg |= (((uint32_t)threeSamplingEn) << FLEXCAN_CTRL1_SMP_SHIFT) & FLEXCAN_CTRL1_SMP_MASK;

    obj->CTRL1 = tempReg;
}

/*! \brief Set bus off automatic recovering enable
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] enable : bus off automatic recovering enable
 *              -1b : bus off automatic recovering disabled
 *              -0b : bus off automatic recovering enable
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetBusOffRecEnable(FlexCanRegType *obj, uint8_t enable)
{
    uint32_t tempReg;
    tempReg = obj->CTRL1;
    tempReg &= (~FLEXCAN_CTRL1_BOFFREC_MASK);
    if(enable == true)
    {
        tempReg |= (((uint32_t)0) << FLEXCAN_CTRL1_BOFFREC_SHIFT) & FLEXCAN_CTRL1_BOFFREC_MASK;
    }
    else
    {
        tempReg |= (((uint32_t)1) << FLEXCAN_CTRL1_BOFFREC_SHIFT) & FLEXCAN_CTRL1_BOFFREC_MASK;
    }

    obj->CTRL1 = tempReg;
}

/*! \brief Get bus off automatic recovering enable
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: bus off automatic recovering enable
 *              -0b : bus off automatic recovering disabled
 *              -1b : bus off automatic recovering enable
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetBusOffRecEnable(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->CTRL1) & FLEXCAN_CTRL1_BOFFREC_MASK) >> FLEXCAN_CTRL1_BOFFREC_SHIFT);
}

/*! \brief Set timer synchronze feature enable
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] enable : timer synchronze feature enable
 *              -0b : timer sync feature disabled
 *              -1b : timer sync feature enabled
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetTimerSyncEnable(FlexCanRegType *obj, uint8_t enable)
{
    uint32_t tempReg;
    tempReg = obj->CTRL1;
    tempReg &= (~FLEXCAN_CTRL1_TSYN_MASK);
    tempReg |= (((uint32_t)enable) << FLEXCAN_CTRL1_TSYN_SHIFT) & FLEXCAN_CTRL1_TSYN_MASK;

    obj->CTRL1 = tempReg;
}

/*! \brief Get timer synchronze feature enable
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: timer synchronze feature enable
 *              -0b : timer sync feature disabled
 *              -1b : timer sync feature enabled
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetTimerSyncEnable(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->CTRL1) & FLEXCAN_CTRL1_TSYN_MASK) >> FLEXCAN_CTRL1_TSYN_SHIFT);
}

/*! \brief Set lowest buffer transmit first enable
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] enable : timer synchronze feature enable
 *              -0b : lowest buffer transmit first disable
 *              -1b : lowest buffer transmit first enable
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetLowestBufTxFirstEna(FlexCanRegType *obj, uint8_t enable)
{
    uint32_t tempReg;
    tempReg = obj->CTRL1;
    tempReg &= (~FLEXCAN_CTRL1_LBUF_MASK);
    tempReg |= (((uint32_t)enable) << FLEXCAN_CTRL1_LBUF_SHIFT) & FLEXCAN_CTRL1_LBUF_MASK;

    obj->CTRL1 = tempReg;
}

/*! \brief Get lowest buffer transmit first enable
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: lowest buffer transmit first enable
 *              -0b : lowest buffer transmit first disable
 *              -1b : lowest buffer transmit first enable
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetLowestBufTxFirstEna(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->CTRL1) & FLEXCAN_CTRL1_LBUF_MASK) >> FLEXCAN_CTRL1_LBUF_SHIFT);
}

/*! \brief Set listen only mode enable
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] enable : listen only mode enable
 *              -0b : listen only mode disable
 *              -1b : listen only mode enable
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetListenOnlyModeEna(FlexCanRegType *obj, uint8_t enable)
{
    uint32_t tempReg;
    tempReg = obj->CTRL1;
    tempReg &= (~FLEXCAN_CTRL1_LOM_MASK);
    tempReg |= (((uint32_t)enable) << FLEXCAN_CTRL1_LOM_SHIFT) & FLEXCAN_CTRL1_LOM_MASK;

    obj->CTRL1 = tempReg;
}

/*! \brief Get listen only mode enable
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: listen only mode enable
 *              -0b : listen only mode disable
 *              -1b : listen only mode enable
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetListenOnlyModeEna(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->CTRL1) & FLEXCAN_CTRL1_LOM_MASK) >> FLEXCAN_CTRL1_LOM_SHIFT);
}

/*! \brief Get propagation segment
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: propagation segment length
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetCtrl1Propseg(const FlexCanRegType *obj)
{
    return ((obj->CTRL1 & FLEXCAN_CTRL1_PROPSEG_MASK) >> FLEXCAN_CTRL1_PROPSEG_SHIFT);
}

/*! \brief Set propagation segment
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] value : propagation segment length
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetCtrl1Propseg(FlexCanRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CTRL1;

    tmp &= ~FLEXCAN_CTRL1_PROPSEG_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << FLEXCAN_CTRL1_PROPSEG_SHIFT)) & FLEXCAN_CTRL1_PROPSEG_MASK);
    obj->CTRL1 = tmp;
}

/*! \brief Get free running timer
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: free running timer counter
 *
 */
__attribute__((always_inline)) static inline uint32_t FlexCanReg_GetFreeRunningTimer(FlexCanRegType *obj)
{
    return obj->TIMER;
}

/*! \brief Get receive error counter for fast bits
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: receive error counter for fast bits
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetEcrRxerrcntfast(const FlexCanRegType *obj)
{
    return ((obj->ECR & FLEXCAN_ECR_RXERRCNTFAST_MASK) >> FLEXCAN_ECR_RXERRCNTFAST_SHIFT);
}

/*! \brief Set receive error counter for fast bits
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] value : receive error counter for fast bits
 *
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetEcrRxerrcntfast(FlexCanRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->ECR;

    tmp &= ~FLEXCAN_ECR_RXERRCNTFAST_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << FLEXCAN_ECR_RXERRCNTFAST_SHIFT)) & FLEXCAN_ECR_RXERRCNTFAST_MASK);
    obj->ECR = tmp;
}

/*! \brief Get transmit error counter for fast bits
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: transmit error counter for fast bits
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetEcrTxerrcntfast(const FlexCanRegType *obj)
{
    return ((obj->ECR & FLEXCAN_ECR_TXERRCNTFAST_MASK) >> FLEXCAN_ECR_TXERRCNTFAST_SHIFT);
}

/*! \brief Set transmit error counter for fast bits
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] value : transmit error counter for fast bits
 *
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetEcrTxerrcntfast(FlexCanRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->ECR;

    tmp &= ~FLEXCAN_ECR_TXERRCNTFAST_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << FLEXCAN_ECR_TXERRCNTFAST_SHIFT)) & FLEXCAN_ECR_TXERRCNTFAST_MASK);
    obj->ECR = tmp;
}

/*! \brief Set fast error interrupt enable
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] enable : fast error interrupt enable
 *              -0b : fast error interrupt disabled
 *              -1b : fast error interrupt enabled
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetFastErrIntEnable(FlexCanRegType *obj, uint8_t enable)
{
    uint32_t tempReg;
    tempReg = obj->CTRL2;
    tempReg &= (~FLEXCAN_CTRL2_ERRMSKFAST_MASK);
    tempReg |= (((uint32_t)enable) << FLEXCAN_CTRL2_ERRMSKFAST_SHIFT) & FLEXCAN_CTRL2_ERRMSKFAST_MASK;

    obj->CTRL2 = tempReg;
}

/*! \brief Get fast error interrupt enable
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: fast error interrupt enable
 *              -0b : fast error interrupt disabled
 *              -1b : fast error interrupt enabled
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetFastErrIntEnable(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->CTRL2) & FLEXCAN_CTRL2_ERRMSKFAST_MASK) >> FLEXCAN_CTRL2_ERRMSKFAST_SHIFT);
}

/*! \brief Get error correction configuration register write enable
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: error correction configuration register write enable
 *              0: error correction configuration register write disable
 *              1: error correction configuration register write enable
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetMemErrCtrlRegWriteEnable(const FlexCanRegType *obj)
{
    return ((obj->CTRL2 & FLEXCAN_CTRL2_ECRWRE_MASK) >> FLEXCAN_CTRL2_ECRWRE_SHIFT);
}

/*! \brief Correction Configuration Register Write Enable
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] enable : fast error interrupt enable
 *              -0b : Disable update.
 *              -1b : Enable update.
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetMemErrCtrlRegWriteEnable(FlexCanRegType *obj, uint8_t enable)
{
    uint32_t tempReg;
    tempReg = obj->CTRL2;
    tempReg &= (~FLEXCAN_CTRL2_ECRWRE_MASK);
    tempReg |= (((uint32_t)enable) << FLEXCAN_CTRL2_ECRWRE_SHIFT) & FLEXCAN_CTRL2_ECRWRE_MASK;

    obj->CTRL2 = tempReg;
}

/*! \brief Get write access to memory in freeze mode enable
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: write access to memory in freeze mode enable
 *              0: write access to memory in freeze mode disable
 *              1: write access to memory in freeze mode enable
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetFreezeModeWriteAcc(const FlexCanRegType *obj)
{
    return ((obj->CTRL2 & FLEXCAN_CTRL2_WRMFRZ_MASK) >> FLEXCAN_CTRL2_WRMFRZ_SHIFT);
}

/*! \brief Set freeze mode
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] enable : freeze mode
 *              -0b : Disable.
 *              -1b : Enable.
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetFreezeModeWriteAcc(FlexCanRegType *obj, uint8_t enable)
{
    uint32_t tempReg;
    tempReg = obj->CTRL2;
    tempReg &= (~FLEXCAN_CTRL2_WRMFRZ_MASK);
    tempReg |= (((uint32_t)enable) << FLEXCAN_CTRL2_WRMFRZ_SHIFT) & FLEXCAN_CTRL2_WRMFRZ_MASK;

    obj->CTRL2 = tempReg;
}

/*! \brief Set free running timer source
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] val : free running timer source selection
 *              -0b : clocked by CAN bit clock
 *              -1b : clocked by an external time tick
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetFreeRunTimerSrc(FlexCanRegType *obj, uint8_t val)
{
    uint32_t tempReg;
    tempReg = obj->CTRL2;
    tempReg &= (~FLEXCAN_CTRL2_TIMERSRC_MASK);
    tempReg |= (((uint32_t)val) << FLEXCAN_CTRL2_TIMERSRC_SHIFT) & FLEXCAN_CTRL2_TIMERSRC_MASK;

    obj->CTRL2 = tempReg;
}

/*! \brief Get free running timer source
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: free running timer source selection
 *          -0b : clocked by CAN bit clock
 *          -1b : clocked by an external time tick
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetFreeRunTimerSrc(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->CTRL2) & FLEXCAN_CTRL2_TIMERSRC_MASK) >> FLEXCAN_CTRL2_TIMERSRC_SHIFT);
}

/*! \brief Set mailboxes reception priority
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] mrp : mailboxes reception priority
 *              -1b : matching starts from mailboxes and continues on legacy rx ff
 *              -0b : matching starts from legacy rx ff and continues on mailboxes
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetMailboxesReceptionPrio(FlexCanRegType *obj, bool mrp)
{
    uint32_t tempReg;
    tempReg = obj->CTRL2;
    tempReg &= (~FLEXCAN_CTRL2_MRP_MASK);
    tempReg |= (((uint32_t)mrp) << FLEXCAN_CTRL2_MRP_SHIFT) & FLEXCAN_CTRL2_MRP_MASK;

    obj->CTRL2 = tempReg;
}

/*! \brief Get mailboxes reception priority
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: mailboxes reception priority
 *              -1b : matching starts from mailboxes and continues on legacy rx ff
 *              -0b : matching starts from legacy rx ff and continues on mailboxes
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetMailboxesReceptionPrio(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->CTRL2) & FLEXCAN_CTRL2_MRP_MASK) >> FLEXCAN_CTRL2_MRP_SHIFT);
}

/*! \brief Get remote request storing
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: remote request storing
 *              0: remote response frame is generated
 *              1: remote request frame is stored
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetCtrl2Rrs(const FlexCanRegType *obj)
{
    return ((obj->CTRL2 & FLEXCAN_CTRL2_RRS_MASK) >> FLEXCAN_CTRL2_RRS_SHIFT);
}

/*! \brief Set remote request storing
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] value : remote request storing
 *              0: remote response frame is generated
 *              1: remote request frame is stored
 * 
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetCtrl2Rrs(FlexCanRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CTRL2;

    tmp &= ~FLEXCAN_CTRL2_RRS_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << FLEXCAN_CTRL2_RRS_SHIFT)) & FLEXCAN_CTRL2_RRS_MASK);
    obj->CTRL2 = tmp;
}

/*! \brief Get entire frame arbitration field comparison enable for rx mailboxes
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: entire frame arbitration field comparison enable for rx mailboxes
 *              0: rx mailbox filter's IDE bit is always compared and RTR is never
 *                 compared, regardless of mask bits
 *              1: enable the comparison of both the IDE and RTR bits of an
 *                 Rx mailbox filter with the corresponding bits of the incoming
 *                 frame. Mask bits do apply
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetCtrl2Eacen(const FlexCanRegType *obj)
{
    return ((obj->CTRL2 & FLEXCAN_CTRL2_EACEN_MASK) >> FLEXCAN_CTRL2_EACEN_SHIFT);
}

/*! \brief Set entire frame arbitration field comparison enable for rx mailboxes
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] value : entire frame arbitration field comparison enable for rx mailboxes
 *              0: rx mailbox filter's IDE bit is always compared and RTR is never
 *                 compared, regardless of mask bits
 *              1: enable the comparison of both the IDE and RTR bits of an
 *                 Rx mailbox filter with the corresponding bits of the incoming
 *                 frame. Mask bits do apply
 * 
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetCtrl2Eacen(FlexCanRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CTRL2;

    tmp &= ~FLEXCAN_CTRL2_EACEN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << FLEXCAN_CTRL2_EACEN_SHIFT)) & FLEXCAN_CTRL2_EACEN_MASK);
    obj->CTRL2 = tmp;
}

/*! \brief Set number of legacy rx fifo filter
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] rffn : number of legacy rx fifo filter
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetLegacyRxFifoFilterNums(FlexCanRegType *obj, uint8_t rffn)
{
    uint32_t tempReg;
    tempReg = obj->CTRL2;
    tempReg &= (~FLEXCAN_CTRL2_RFFN_MASK);
    tempReg |= (((uint32_t)rffn) << FLEXCAN_CTRL2_RFFN_SHIFT) & FLEXCAN_CTRL2_RFFN_MASK;

    obj->CTRL2 = tempReg;
}

/*! \brief Get number of legacy rx fifo filter
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: number of legacy rx fifo filter
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetLegacyRxFifoFilterNums(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->CTRL2) & FLEXCAN_CTRL2_RFFN_MASK) >> FLEXCAN_CTRL2_RFFN_SHIFT);
}

/*! \brief Get Tx arbitration start delay
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: Tx arbitration start delay
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetCtrl2Tasd(const FlexCanRegType *obj)
{
    return ((obj->CTRL2 & FLEXCAN_CTRL2_TASD_MASK) >> FLEXCAN_CTRL2_TASD_SHIFT);
}

/*! \brief Set Tx arbitration start delay
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] value : Tx arbitration start delay
 *
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetCtrl2Tasd(FlexCanRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CTRL2;

    tmp &= ~FLEXCAN_CTRL2_TASD_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << FLEXCAN_CTRL2_TASD_SHIFT)) & FLEXCAN_CTRL2_TASD_MASK);
    obj->CTRL2 = tmp;
}

/*! \brief Set bus off done interrupt mask
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] boffdoneMask : bus off done interrupt mask
 *              -1b : bus off done interrupt enabled
 *              -0b : bus off done interrupt disabled
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetBusOffDoneIntMask(FlexCanRegType *obj, bool boffdoneMask)
{
    uint32_t tempReg;
    tempReg = obj->CTRL2;
    tempReg &= (~FLEXCAN_CTRL2_BOFFDONEMSK_MASK);
    tempReg |= (((uint32_t)boffdoneMask) << FLEXCAN_CTRL2_BOFFDONEMSK_SHIFT) & FLEXCAN_CTRL2_BOFFDONEMSK_MASK;

    obj->CTRL2 = tempReg;
}

/*! \brief Get bus off done interrupt mask
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: bus off done interrupt mask
 *              -1b : bus off done interrupt enabled
 *              -0b : bus off done interrupt disabled
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetBusOffDoneIntMask(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->CTRL2) & FLEXCAN_CTRL2_BOFFDONEMSK_MASK) >> FLEXCAN_CTRL2_BOFFDONEMSK_SHIFT);
}

/*! \brief Set enahnced bit timing enable
 *  enable the use of the CAN_EPRS, CAN_EDCBT, CAN_ENCBT regisgers to configure
 *  the CAN bit timing segments, instead of using the bit timing fields of the
 *  CAN_CBT, CAN_FDCNT and CAN_CTRL1 registers
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] enable : enhanced bit timing enable
 *              -0b : Enhanced bit timing disable
 *              -1b : Enhanced bit timing enable
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetEnhBitTimingEnable(FlexCanRegType *obj, uint8_t enable)
{
    uint32_t tempReg;
    tempReg = obj->CTRL2;
    tempReg &= (~FLEXCAN_CTRL2_BTE_MASK);
    tempReg |= (((uint32_t)enable) << FLEXCAN_CTRL2_BTE_SHIFT) & FLEXCAN_CTRL2_BTE_MASK;

    obj->CTRL2 = tempReg;
}

/*! \brief Get enahnced bit timing enable
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: enahnced bit timing enable
 *          - 0 : Enhanced bit timing disable
 *          - 1 : Enhanced bit timing enable
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetEnhBitTimingEnable(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->CTRL2) & FLEXCAN_CTRL2_BTE_MASK) >> FLEXCAN_CTRL2_BTE_SHIFT);
}

/*! \brief Set free running timer base
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] val : free running timer base selection
 *              -00b : select CAN_TIMER as free running timer base
 *              -01b : select lower 16 bits of high resolution timer as free running timer base
 *              -10b : select upper 16 bits of high resolution timer as free running timer base
 *              -11b : reversed
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetFreeRunTimerBase(FlexCanRegType *obj, uint8_t val)
{
    uint32_t tempReg;
    tempReg = obj->CTRL2;
    tempReg &= (~FLEXCAN_CTRL2_MBTSBASE_MASK);
    tempReg |= (((uint32_t)val) << FLEXCAN_CTRL2_MBTSBASE_SHIFT) & FLEXCAN_CTRL2_MBTSBASE_MASK;

    obj->CTRL2 = tempReg;
}

/*! \brief Get free running timer base
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: free running timer base selection
 *              -00b : select CAN_TIMER as free running timer base
 *              -01b : select lower 16 bits of high resolution timer as free running timer base
 *              -10b : select upper 16 bits of high resolution timer as free running timer base
 *              -11b : reversed
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetFreeRunTimerBase(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->CTRL2) & FLEXCAN_CTRL2_MBTSBASE_MASK) >> FLEXCAN_CTRL2_MBTSBASE_SHIFT);
}

/*! \brief Set high resolution time stamp mode
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] val :  high resolution time stamp mode
 *              -00b : select high-resolution time stamp mode is disabled
 *              -01b : select high-resolution time stamp mode is at the end of the CAN frame
 *              -10b : select high-resolution time stamp mode is at the start of the CAN frame
 *              -11b : select high-resolution time stamp mode is at the RES bit of the CAN frame
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetHighResTimeStampMode(FlexCanRegType *obj, uint8_t val)
{
    uint32_t tempReg;
    tempReg = obj->CTRL2;
    tempReg &= (~FLEXCAN_CTRL2_TSTAMPCAP_MASK);
    tempReg |= (((uint32_t)val) << FLEXCAN_CTRL2_TSTAMPCAP_SHIFT) & FLEXCAN_CTRL2_TSTAMPCAP_MASK;

    obj->CTRL2 = tempReg;
}

/*! \brief Get high resolution time stamp mode
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: high resolution time stamp mode
 *              -00b : select high-resolution time stamp mode is disabled
 *              -01b : select high-resolution time stamp mode is at the end of the CAN frame
 *              -10b : select high-resolution time stamp mode is at the start of the CAN frame
 *              -11b : select high-resolution time stamp mode is at the RES bit of the CAN frame
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetHighResTimeStampMode(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->CTRL2) & FLEXCAN_CTRL2_TSTAMPCAP_MASK) >> FLEXCAN_CTRL2_MBTSBASE_SHIFT);
}

/*! \brief Get error overrun interrupt flag
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: fast error interrupt flag
 *              - 0 : error overrun interrupt assert
 *              - 1 : error overrun interrupt deassert
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetErrOverrunIntFlag(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ESR1) & FLEXCAN_ESR1_ERROVR_MASK) >> FLEXCAN_ESR1_ERROVR_SHIFT);
}

/*! \brief Clear error overrun interrupt flag
 *
 * \param[in] obj : pointer to FlexCAN register instance
 *
 */
__attribute__((always_inline)) static inline void FlexCanReg_ClearErrOverrunIntFlag(FlexCanRegType *obj)
{
    obj->ESR1 = FLEXCAN_ESR1_ERROVR_MASK;
}

/*! \brief Get fast error interrupt flag
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: fast error interrupt flag
 *              - 0 : fast error interrupt assert
 *              - 1 : fast error interrupt deassert
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetFastErrIntFlag(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ESR1) & FLEXCAN_ESR1_ERRINT_FAST_MASK) >> FLEXCAN_ESR1_ERRINT_FAST_SHIFT);
}

/*! \brief Clear fast error interrupt flag
 *
 * \param[in] obj : pointer to FlexCAN register instance
 *
 */
__attribute__((always_inline)) static inline void FlexCanReg_ClearFastErrIntFlag(FlexCanRegType *obj)
{
    obj->ESR1 = FLEXCAN_ESR1_ERRINT_FAST_MASK;
}

/*! \brief Get tx warning interrupt flag
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: tx warning interrupt flag
 *              - 0 : tx warning interrupt assert
 *              - 1 : tx warning interrupt deassert
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetTxWarnIntFlag(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ESR1) & FLEXCAN_ESR1_TWRNINT_MASK) >> FLEXCAN_ESR1_TWRNINT_SHIFT);
}

/*! \brief Clear tx warning interrupt flag
 *
 * \param[in] obj : pointer to FlexCAN register instance
 *
 */
__attribute__((always_inline)) static inline void FlexCanReg_ClearTxWarnIntFlag(FlexCanRegType *obj)
{
    obj->ESR1 = FLEXCAN_ESR1_TWRNINT_MASK;
}

/*! \brief Get bus off done interrupt flag
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: tx warning interrupt flag
 *              - 0 : flexcan has completed bus off process
 *              - 1 : no such occurence
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetBusOffDoneIntFlag(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ESR1) & FLEXCAN_ESR1_BOFFDONEINT_MASK) >> FLEXCAN_ESR1_BOFFDONEINT_SHIFT);
}

/*! \brief Clear bus off done interrupt flag
 *
 * \param[in] obj : pointer to FlexCAN register instance
 *
 */
__attribute__((always_inline)) static inline void FlexCanReg_ClearBusOffDoneIntFlag(FlexCanRegType *obj)
{
    obj->ESR1 = FLEXCAN_ESR1_BOFFDONEINT_MASK;
}

/*! \brief Get synch status
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: synch status
 *              - 0 : flexcan is not synchronized to the can bus
 *              - 1 : flexcan is synchronized to the can bus
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetSynchFlag(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ESR1) & FLEXCAN_ESR1_SYNCH_MASK) >> FLEXCAN_ESR1_SYNCH_SHIFT);
}

/*! \brief Get rx warning interrupt flag
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: rx warning interrupt flag
 *              - 0 : rx warning interrupt assert
 *              - 1 : rx warning interrupt deassert
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetRxWarnIntFlag(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ESR1) & FLEXCAN_ESR1_RWRNINT_MASK) >> FLEXCAN_ESR1_RWRNINT_SHIFT);
}

/*! \brief Clear rx warning interrupt flag
 *
 * \param[in] obj : pointer to FlexCAN register instance
 *
 */
__attribute__((always_inline)) static inline void FlexCanReg_ClearRxWarnIntFlag(FlexCanRegType *obj)
{
    obj->ESR1 = FLEXCAN_ESR1_RWRNINT_MASK;
}

/*! \brief Get tx warning flag
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: tx warning flag
 *              - 0 : tx warning assert
 *              - 1 : tx warning deassert
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetTxWarnFlag(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ESR1) & FLEXCAN_ESR1_TXWRN_MASK) >> FLEXCAN_ESR1_TXWRN_SHIFT);
}

/*! \brief Get rx warning flag
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: rx warning flag
 *              - 0 : rx warning assert
 *              - 1 : rx warning deassert
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetRxWarnFlag(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ESR1) & FLEXCAN_ESR1_RXWRN_MASK) >> FLEXCAN_ESR1_RXWRN_SHIFT);
}

/*! \brief Get bus off interrupt flag
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: bus off interrupt flag
 *              - 0 : bus off interrupt assert
 *              - 1 : bus off interrupt deassert
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetBusoffIntFlag(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ESR1) & FLEXCAN_ESR1_BOFFINT_MASK) >> FLEXCAN_ESR1_BOFFINT_SHIFT);
}

/*! \brief Clear bus off interrupt flag
 *
 * \param[in] obj : pointer to FlexCAN register instance
 *
 */
__attribute__((always_inline)) static inline void FlexCanReg_ClearBusoffIntFlag(FlexCanRegType *obj)
{
    obj->ESR1 = FLEXCAN_ESR1_BOFFINT_MASK;
}

/*! \brief Get error interrupt flag
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: error interrupt flag
 *              - 0 : error interrupt assert
 *              - 1 : error interrupt deassert
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetErrIntFlag(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ESR1) & FLEXCAN_ESR1_ERRINT_MASK) >> FLEXCAN_ESR1_ERRINT_SHIFT);
}

/*! \brief Clear error interrupt flag
 *
 * \param[in] obj : pointer to FlexCAN register instance
 *
 */
__attribute__((always_inline)) static inline void FlexCanReg_ClearErrIntFlag(FlexCanRegType *obj)
{
    obj->ESR1 = FLEXCAN_ESR1_ERRINT_MASK;
}

/*! \brief Get edge wakeup interrupt flag
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: edge wakeup interrupt flag
 *              - 0 : wakeup interrupt assert
 *              - 1 : wakeup interrupt deassert
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetEdgeWakeIntFlag(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ESR1) & FLEXCAN_ESR1_WAKINT_MASK) >> FLEXCAN_ESR1_WAKINT_SHIFT);
}

/*! \brief Clear err state with mask
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] errMask : err mask bits
 *
 */
__attribute__((always_inline)) static inline void FlexCanReg_ClearErrFlag(FlexCanRegType *obj, uint32_t errMask)
{
    obj->ESR1 = errMask;
}

/*! \brief Clear edge wakeup interrupt flag
 *
 * \param[in] obj : pointer to FlexCAN register instance
 *
 */
__attribute__((always_inline)) static inline void FlexCanReg_ClearEdgeWakeIntFlag(FlexCanRegType *obj)
{
    obj->ESR1 = FLEXCAN_ESR1_WAKINT_MASK;
}

/*! \brief Get Rx mailboxes global mask
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: Rx mailboxes global mask
 *
 */
__attribute__((always_inline)) static inline uint32_t FlexCanReg_GetRxMailboxGlobalMask(FlexCanRegType *obj)
{
    return obj->RXMGMASK;
}

/*! \brief Set Rx mailboxes global mask
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] mask : Rx mailboxes global mask
 *
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetRxMailboxGlobalMask(FlexCanRegType *obj, uint32_t mask)
{
    obj->RXMGMASK = mask;
}

/*! \brief Set Rx mailbox 14 mask
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] mask : mask for Rx mailbox 14
 *
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetRxMailbox14Mask(FlexCanRegType *obj, uint32_t mask)
{
    obj->RX14MASK = mask;
}

/*! \brief Get Rx mailbox 14 mask
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: mask for Rx mailbox 14
 *
 */
__attribute__((always_inline)) static inline uint32_t FlexCanReg_GetRxMailbox14Mask(FlexCanRegType *obj)
{
    return (obj->RX14MASK);
}

/*! \brief Set Rx mailbox 15 mask
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] mask : mask for Rx mailbox 15
 *
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetRxMailbox15Mask(FlexCanRegType *obj, uint32_t mask)
{
    obj->RX15MASK = mask;
}

/*! \brief Get Rx mailbox 15 mask
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: mask for Rx mailbox 15
 *
 */
__attribute__((always_inline)) static inline uint32_t FlexCanReg_GetRxMailbox15Mask(FlexCanRegType *obj)
{
    return (obj->RX15MASK);
}

/*! \brief Get ESR1 register
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: 32 bit ESR1 register value
 *
 */
__attribute__((always_inline)) static inline uint32_t FlexCanReg_GetEsr1Register(FlexCanRegType *obj)
{
    return (uint32_t)(obj->ESR1);
}

/*! \brief Get bit 1 error in FD frame data phase
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: bit 1 error in FD frame data phase
 *              - 0 : no such error occurrence
 *              - 1 : at least one bit sent as recessive is received as dominant
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetBit1FastError(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ESR1) & FLEXCAN_ESR1_BIT1ERR_FAST_MASK) >> FLEXCAN_ESR1_BIT1ERR_FAST_SHIFT);
}

/*! \brief Get bit 0 error in FD frame data phase
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: bit 0 error in FD frame data phase
 *              - 0 : no such error occurrence
 *              - 1 : at least one bit sent as dominant is received as recessive
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetBit0FastError(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ESR1) & FLEXCAN_ESR1_BIT0ERR_FAST_MASK) >> FLEXCAN_ESR1_BIT0ERR_FAST_SHIFT);
}

/*! \brief Get CRC error in FD frame data phase
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: CRC error in FD frame data phase
 *              - 0 : no such error occurrence
 *              - 1 : a CRC error occurred since last read of this register
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetCrcFastError(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ESR1) & FLEXCAN_ESR1_CRCERR_FAST_MASK) >> FLEXCAN_ESR1_CRCERR_FAST_SHIFT);
}

/*! \brief Get form error in FD frame data phase
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: form error in FD frame data phase
 *              - 0 : no such error occurrence
 *              - 1 : a form error occurred since last read of this register
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetFormFastError(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ESR1) & FLEXCAN_ESR1_FRMERR_FAST_MASK) >> FLEXCAN_ESR1_FRMERR_FAST_SHIFT);
}

/*! \brief Get stuff error in FD frame data phase
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: stuff error in FD frame data phase
 *              - 0 : no such error occurrence
 *              - 1 : a stuff error occurred since last read of this register
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetStuffFastError(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ESR1) & FLEXCAN_ESR1_STFERR_FAST_MASK) >> FLEXCAN_ESR1_STFERR_FAST_SHIFT);
}

/*! \brief Get bit 1 error
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: bit 1 error
 *              - 0 : no such error occurrence
 *              - 1 : at least one bit sent as recessive is received as dominant
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetBit1Error(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ESR1) & FLEXCAN_ESR1_BIT1ERR_MASK) >> FLEXCAN_ESR1_BIT1ERR_SHIFT);
}

/*! \brief Get bit 0 error
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: bit 0 error
 *              - 0 : no such error occurrence
 *              - 1 : at least one bit sent as dominant is received as recessive
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetBit0Error(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ESR1) & FLEXCAN_ESR1_BIT0ERR_MASK) >> FLEXCAN_ESR1_BIT0ERR_SHIFT);
}

/*! \brief Get ACK error
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: ACK error
 *              - 0 : no such error occurrence
 *              - 1 : an ACK error occurred since last read of this register
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetAckError(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ESR1) & FLEXCAN_ESR1_ACKERR_MASK) >> FLEXCAN_ESR1_ACKERR_SHIFT);
}

/*! \brief Get CRC error
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: CRC error
 *              - 0 : no such error occurrence
 *              - 1 : an CRC error occurred since last read of this register
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetCrcError(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ESR1) & FLEXCAN_ESR1_CRCERR_MASK) >> FLEXCAN_ESR1_CRCERR_SHIFT);
}

/*! \brief Get form error
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: form error
 *              - 0 : no such error occurrence
 *              - 1 : an form error occurred since last read of this register
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetFormError(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ESR1) & FLEXCAN_ESR1_FRMERR_MASK) >> FLEXCAN_ESR1_FRMERR_SHIFT);
}

/*! \brief Get stuff error
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: stuff error
 *              - 0 : no such error occurrence
 *              - 1 : an stuff error occurred since last read of this register
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetStuffError(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ESR1) & FLEXCAN_ESR1_STFERR_MASK) >> FLEXCAN_ESR1_STFERR_SHIFT);
}

/*! \brief Get Tx error warning
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: Tx error warning
 *              - 0 : no such error occurrence
 *              - 1 : TXERRCNT is greater than or equal to 96
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetTxErrWarning(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ESR1) & FLEXCAN_ESR1_TXWRN_MASK) >> FLEXCAN_ESR1_TXWRN_SHIFT);
}

/*! \brief Get Rx error warning
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: Rx error warning
 *              - 0 : no such error occurrence
 *              - 1 : RXERRCNT is greater than or equal to 96
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetRxErrWarning(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ESR1) & FLEXCAN_ESR1_RXWRN_MASK) >> FLEXCAN_ESR1_RXWRN_SHIFT);
}

/*! \brief Get idle state
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: idle state
 *              - 0 : no such occurrence
 *              - 1 : CAN bus is now idle
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetIdleState(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ESR1) & FLEXCAN_ESR1_IDLE_MASK) >> FLEXCAN_ESR1_IDLE_SHIFT);
}

/*! \brief Get Tx state
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: Tx state
 *              - 0 : FlexCan is not transmitting a message
 *              - 1 : FlexCan is transmitting a message
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetTxState(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ESR1) & FLEXCAN_ESR1_TX_MASK) >> FLEXCAN_ESR1_TX_SHIFT);
}

/*! \brief Get fault confinement state
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: fault confinement state
 *              - 0b00 : error passive
 *              - 0b01 : error active
 *              - 0b1x : bus off
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetFltConfinementState(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ESR1) & FLEXCAN_ESR1_FLTCONF_MASK) >> FLEXCAN_ESR1_FLTCONF_SHIFT);
}

/*! \brief Get FlexCan Rx state
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: FlexCan Rx state
 *              - 0 : FlexCan is not receiving a message
 *              - 1 : FlexCan is receiving a message
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetRxState(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ESR1) & FLEXCAN_ESR1_RX_MASK) >> FLEXCAN_ESR1_RX_SHIFT);
}

/*! \brief Set FlexCan message buffer interrupt enable mask
 *
 * \param[in] obj   : pointer to FlexCAN register instance
 * \param[in] regId : register index
 * \param[in] val   : message buffer interrupt enable mask
 *
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetMsgBufInterruptEnable(FlexCanRegType *obj, uint32_t regId, uint32_t val)
{
    switch(regId)
    {
    case 0:
        obj->IMASK1 |= val;
        break;
    case 1:
        obj->IMASK2 |= val;
        break;
    case 2:
        obj->IMASK3 |= val;
        break;
    case 3:
        obj->IMASK4 |= val;
        break;
    default:
        break;
    }
}

/*! \brief Set FlexCan message buffer interrupt disable mask
 *
 * \param[in] obj   : pointer to FlexCAN register instance
 * \param[in] regId : register index
 * \param[in] val   : message buffer interrupt disable mask
 *
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetMsgBufInterruptDisable(FlexCanRegType *obj, uint32_t regId, uint32_t val)
{
    switch(regId)
    {
    case 0:
        obj->IMASK1 &= val;
        break;
    case 1:
        obj->IMASK2 &= val;
        break;
    case 2:
        obj->IMASK3 &= val;
        break;
    case 3:
        obj->IMASK4 &= val;
        break;
    default:
        break;
    }
}

/*! \brief Get FlexCan message buffer interrupt flag register mask
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] regId : register index
 * \return: FlexCan message buffer interrupt flag register[n] mask
 *
 */
__attribute__((always_inline)) static inline uint32_t FlexCanReg_GetMsgBufInterruptFlagReg(FlexCanRegType *obj, uint32_t regId)
{
    uint32_t retVal = 0;

    switch(regId)
    {
    case 0:
        retVal = obj->IFLAG1;
        break;
    case 1:
        retVal = obj->IFLAG2;
        break;
    case 2:
        retVal = obj->IFLAG3;
        break;
    case 3:
        retVal = obj->IFLAG4;
        break;
    default:
        break;
    }

    return retVal;
}

/*! \brief Set FlexCan message buffer interrupt flag
 *
 * \param[in] obj   : pointer to FlexCAN register instance
 * \param[in] regId : register index
 * \param[in] val   : message buffer interrupt flag
 *
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetMsgBufInterruptFlagReg(FlexCanRegType *obj, uint32_t regId, uint32_t val)
{
    switch(regId)
    {
    case 0:
        obj->IFLAG1 = val;
        break;
    case 1:
        obj->IFLAG2 = val;
        break;
    case 2:
        obj->IFLAG3 = val;
        break;
    case 3:
        obj->IFLAG4 = val;
        break;
    default:
        break;
    }
}

/*! \brief Set Rx FIFO global mask
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] val : Rx FIFO global mask
 *
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetRxFifoGlobalMask(FlexCanRegType *obj, uint32_t val)
{
    obj->RXFGMASK = val;
}

/*! \brief Set Rx FIFO global mask
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: Rx FIFO global mask
 *
 */
__attribute__((always_inline)) static inline uint32_t FlexCanReg_GetRxFifoGlobalMask(FlexCanRegType *obj, uint32_t val)
{
    return (obj->RXFGMASK);
}

/*! \brief Get identifier acceptance filter hit indicator
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: identifier acceptance filter hit indicator
 *
 */
__attribute__((always_inline)) static inline uint16_t FlexCanReg_GetRxfirIdhit(const FlexCanRegType *obj)
{
    return ((obj->RXFIR & FLEXCAN_RXFIR_IDHIT_MASK) >> FLEXCAN_RXFIR_IDHIT_SHIFT);
}

/*! \brief Get extended bit timing format enable
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: extended bit timing format enable
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetExtendedBitTimingEnable(const FlexCanRegType *obj)
{
    return ((obj->CBT & FLEXCAN_CBT_BTF_MASK) >> FLEXCAN_CBT_BTF_SHIFT);
}

/*! \brief Set Extended bit timing feature
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] enable : Extended bit timing feature
 *              0: disable
 *              1: enable
 *
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetExtendedBitTimingEnable(FlexCanRegType *obj, uint8_t enable)
{
    uint32_t tempReg;
    tempReg = obj->CBT;
    tempReg &= (~FLEXCAN_CBT_BTF_MASK);
    tempReg |= (((uint32_t)enable) << FLEXCAN_CBT_BTF_SHIFT) & FLEXCAN_CBT_BTF_MASK;

    obj->CBT = tempReg;
}

/*! \brief Get extended prescaler division factor
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: extended prescaler division factor
 *
 */
__attribute__((always_inline)) static inline uint16_t FlexCanReg_GetExtPresalerDivision(const FlexCanRegType *obj)
{
    return ((obj->CBT & FLEXCAN_CBT_EPRESDIV_MASK) >> FLEXCAN_CBT_EPRESDIV_SHIFT);
}

/*! \brief Set Extended presaler div
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] val : Extended presaler div
 *
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetExtPresalerDivision(FlexCanRegType *obj, uint16_t val)
{
    uint32_t tempReg;
    tempReg = obj->CBT;
    tempReg &= (~FLEXCAN_CBT_EPRESDIV_MASK);
    tempReg |= (((uint32_t)val) << FLEXCAN_CBT_EPRESDIV_SHIFT) & FLEXCAN_CBT_EPRESDIV_MASK;

    obj->CBT = tempReg;
}

/*! \brief Get extended resync jump width
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: extended resync jump width
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetExtResyncJumpWidth(const FlexCanRegType *obj)
{
    return ((obj->CBT & FLEXCAN_CBT_ERJW_MASK) >> FLEXCAN_CBT_ERJW_SHIFT);
}

/*! \brief Set extended resynce jump width
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] val : extended resynce jump width
 *
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetExtResyncJumpWidth(FlexCanRegType *obj, uint16_t val)
{
    uint32_t tempReg;
    tempReg = obj->CBT;
    tempReg &= (~FLEXCAN_CBT_ERJW_MASK);
    tempReg |= (((uint32_t)val) << FLEXCAN_CBT_ERJW_SHIFT) & FLEXCAN_CBT_ERJW_MASK;

    obj->CBT = tempReg;
}

/*! \brief Get extended propagation segment
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: extended propagation segment
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetExtPorpSeg(const FlexCanRegType *obj)
{
    return ((obj->CBT & FLEXCAN_CBT_EPROPSEG_MASK) >> FLEXCAN_CBT_EPROPSEG_SHIFT);
}

/*! \brief Set extended porp seg
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] val : extended porp seg
 *
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetExtPorpSeg(FlexCanRegType *obj, uint16_t val)
{
    uint32_t tempReg;
    tempReg = obj->CBT;
    tempReg &= (~FLEXCAN_CBT_EPROPSEG_MASK);
    tempReg |= (((uint32_t)val) << FLEXCAN_CBT_EPROPSEG_SHIFT) & FLEXCAN_CBT_EPROPSEG_MASK;

    obj->CBT = tempReg;
}

/*! \brief Get extended phase segment 1
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: extended phase segment 1
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetExtPhaseSeg1(const FlexCanRegType *obj)
{
    return ((obj->CBT & FLEXCAN_CBT_EPSEG1_MASK) >> FLEXCAN_CBT_EPSEG1_SHIFT);
}

/*! \brief Set extended phase seg1
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] val : extended phase seg1
 *
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetExtPhaseSeg1(FlexCanRegType *obj, uint16_t val)
{
    uint32_t tempReg;
    tempReg = obj->CBT;
    tempReg &= (~FLEXCAN_CBT_EPSEG1_MASK);
    tempReg |= (((uint32_t)val) << FLEXCAN_CBT_EPSEG1_SHIFT) & FLEXCAN_CBT_EPSEG1_MASK;

    obj->CBT = tempReg;
}

/*! \brief Get extended phase segment 2
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: extended phase segment 2
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetExtPhaseSeg2(const FlexCanRegType *obj)
{
    return ((obj->CBT & FLEXCAN_CBT_EPSEG2_MASK) >> FLEXCAN_CBT_EPSEG2_SHIFT);
}

/*! \brief Set extended phase seg2
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] val : extended phase seg2
 *
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetExtPhaseSeg2(FlexCanRegType *obj, uint16_t val)
{
    uint32_t tempReg;
    tempReg = obj->CBT;
    tempReg &= (~FLEXCAN_CBT_EPSEG2_MASK);
    tempReg |= (((uint32_t)val) << FLEXCAN_CBT_EPSEG2_SHIFT) & FLEXCAN_CBT_EPSEG2_MASK;

    obj->CBT = tempReg;
}

/*! \brief Set Rx individual mask n
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] num : number of Rx individual mask
 * \param[in] mask: mask
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetRxIndividualMask(FlexCanRegType *obj, uint8_t num, uint32_t mask)
{
    obj->RXIMR[num] = mask;
}

/*! \brief Get Rx individual mask n
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] num : number of Rx individual mask
 * \return : mask value
 */
__attribute__((always_inline)) static inline uint32_t FlexCanReg_GetRxIndividualMask(FlexCanRegType *obj, uint8_t num)
{
    return (obj->RXIMR[num]);
}

/*! \brief Error Configuration Register Write Disable
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] disable : Configuration Register Write Disable
 *              1b - Write is disabled.
 *              0b - Write is enabled.
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetErrCfgRegWriteDisable(FlexCanRegType *obj, uint8_t disable)
{
    uint32_t tempReg;
    tempReg = obj->MECR;
    tempReg &= (~FLEXCAN_MECR_ECRWRDIS_MASK);
    tempReg |= (((uint32_t)disable) << FLEXCAN_MECR_ECRWRDIS_SHIFT) & FLEXCAN_MECR_ECRWRDIS_MASK;

    obj->MECR = tempReg;
}

/*! \brief Error Correction Disable
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] disable : Error Correction Disable
 *              1b - Disable memory error correction.
 *              0b - Enable memory error correction.
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetEccDisable(FlexCanRegType *obj, uint8_t disable)
{
    uint32_t tempReg;
    tempReg = obj->MECR;
    tempReg &= (~FLEXCAN_MECR_ECCDIS_MASK);
    tempReg |= (((uint32_t)disable) << FLEXCAN_MECR_ECCDIS_SHIFT) & FLEXCAN_MECR_ECCDIS_MASK;

    obj->MECR = tempReg;
}

/*! \brief Non-Correctable Errors In FlexCAN Access Put Device In Freeze Mode
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] disable : Error Correction Disable
 *              1b - res
 *              0b - Keep normal operation.
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetNonCorrErrToFrzModeEnable(FlexCanRegType *obj, uint8_t enable)
{
    uint32_t tempReg;
    tempReg = obj->MECR;
    tempReg &= (~FLEXCAN_MECR_NCEFAFRZ_MASK);
    tempReg |= (((uint32_t)enable) << FLEXCAN_MECR_NCEFAFRZ_SHIFT) & FLEXCAN_MECR_NCEFAFRZ_MASK;

    obj->MECR = tempReg;
}

/*! \brief Get bit rate switch enable
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return : bit rate switch enable
 *               0: transmit a frame in nominal rate, the BRS bit in the Tx MB has no effect
 *               1: transmit a frame with bit rate switching if the BRS bit in the Tx MB is
 *                  recessive
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetFdRateSwitch(const FlexCanRegType *obj)
{
    return ((obj->FDCTRL & FLEXCAN_FDCTRL_FDRATE_MASK) >> FLEXCAN_FDCTRL_FDRATE_SHIFT);
}

/*! \brief Set fd rate switch
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] enable : fd rate switch
 *              1b - enable
 *              0b - disable
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetFdRateSwitch(FlexCanRegType *obj, uint8_t enable)
{
    uint32_t tempReg;
    tempReg = obj->FDCTRL;
    tempReg &= (~FLEXCAN_FDCTRL_FDRATE_MASK);
    tempReg |= (((uint32_t)enable) << FLEXCAN_FDCTRL_FDRATE_SHIFT) & FLEXCAN_FDCTRL_FDRATE_MASK;

    obj->FDCTRL = tempReg;
}

/*! \brief Set fd rate switch
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] region : ram region index
 * \param[in] sizeSel : region size
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetRegionDataSizeSel(FlexCanRegType *obj, uint8_t region, uint8_t sizeSel)
{
    uint32_t tempReg;
    tempReg = obj->FDCTRL;

    switch(region)
    {
    case 0:
        tempReg &= (~FLEXCAN_FDCTRL_MBDSR0_MASK);
        tempReg |= (((uint32_t)sizeSel) << FLEXCAN_FDCTRL_MBDSR0_SHIFT) & FLEXCAN_FDCTRL_MBDSR0_MASK;
        break;
    case 1:
        tempReg &= (~FLEXCAN_FDCTRL_MBDSR1_MASK);
        tempReg |= (((uint32_t)sizeSel) << FLEXCAN_FDCTRL_MBDSR1_SHIFT) & FLEXCAN_FDCTRL_MBDSR1_MASK;
        break;
    case 2:
        tempReg &= (~FLEXCAN_FDCTRL_MBDSR2_MASK);
        tempReg |= (((uint32_t)sizeSel) << FLEXCAN_FDCTRL_MBDSR2_SHIFT) & FLEXCAN_FDCTRL_MBDSR2_MASK;
        break;
    case 3:
        tempReg &= (~FLEXCAN_FDCTRL_MBDSR3_MASK);
        tempReg |= (((uint32_t)sizeSel) << FLEXCAN_FDCTRL_MBDSR3_SHIFT) & FLEXCAN_FDCTRL_MBDSR3_MASK;
        break;
    default:
        /* size select wrong, do something */
        break;
    }

    obj->FDCTRL = tempReg;
}

/*! \brief Get fd rate switch
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] region : ram region index
 * \return region size
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetRegionDataSizeSel(FlexCanRegType *obj, uint8_t region)
{
    uint8_t retVal = 0;

    switch(region)
    {
    case 0:
        retVal = (uint8_t)((obj->FDCTRL & FLEXCAN_FDCTRL_MBDSR0_MASK) >> FLEXCAN_FDCTRL_MBDSR0_SHIFT);
        break;
    case 1:
        retVal = (uint8_t)((obj->FDCTRL & FLEXCAN_FDCTRL_MBDSR1_MASK) >> FLEXCAN_FDCTRL_MBDSR1_SHIFT);
        break;
    case 2:
        retVal = (uint8_t)((obj->FDCTRL & FLEXCAN_FDCTRL_MBDSR2_MASK) >> FLEXCAN_FDCTRL_MBDSR2_SHIFT);
        break;
    case 3:
        retVal = (uint8_t)((obj->FDCTRL & FLEXCAN_FDCTRL_MBDSR3_MASK) >> FLEXCAN_FDCTRL_MBDSR3_SHIFT);
        break;
    default:
        /* size select wrong, do something */
        break;
    }

    return retVal;
}

/*! \brief Get bit rate switch enable
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return : bit rate switch enable
 *               0: transmit a frame in nominal rate, the BRS bit in the Tx MB has no effect
 *               1: transmit a frame with bit rate switching if the BRS bit in the Tx MB is
 *                  recessive
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetTdcEnable(const FlexCanRegType *obj)
{
    return ((obj->FDCTRL & FLEXCAN_FDCTRL_TDCEN_MASK) >> FLEXCAN_FDCTRL_TDCEN_SHIFT);
}

/*! \brief Set Transceiver Delay Compensation Enable
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] enable : Transceiver Delay Compensation Enable
 *              1b - TDC is enabled.
 *              0b - TDC is disabled.
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetTdcEnable(FlexCanRegType *obj, uint8_t enable)
{
    uint32_t tempReg;
    tempReg = obj->FDCTRL;
    tempReg &= (~FLEXCAN_FDCTRL_TDCEN_MASK);
    tempReg |= (((uint32_t)enable) << FLEXCAN_FDCTRL_TDCEN_SHIFT) & FLEXCAN_FDCTRL_TDCEN_MASK;

    obj->FDCTRL = tempReg;
}

/*! \brief Get transceiver delay compensation fail
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return : transceiver delay compensation fail
 *               0: measured loop delay is in range
 *               1: transmit a frame with bit rate switching if the BRS bit in the Tx MB is
 *                  recessive
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetFdctrlTdcfail(const FlexCanRegType *obj)
{
    return ((obj->FDCTRL & FLEXCAN_FDCTRL_TDCFAIL_MASK) >> FLEXCAN_FDCTRL_TDCFAIL_SHIFT);
}

/*! \brief Clear transceiver delay compensation fail
 *
 * \param[in] obj : pointer to FlexCAN register instance
 */
__attribute__((always_inline)) static inline void FlexCanReg_ClearFdctrlTdcfail(FlexCanRegType *obj)
{
    uint32_t tmp = obj->FDCTRL;

    tmp |= (((uint32_t)(((uint32_t)(1)) << FLEXCAN_FDCTRL_TDCFAIL_SHIFT)) & FLEXCAN_FDCTRL_TDCFAIL_MASK);
    obj->FDCTRL = tmp;
}

/*! \brief Get transceiver delay compensation offset
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return : transceiver delay compensation offset
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetFdctrlTdcoff(const FlexCanRegType *obj)
{
    return ((obj->FDCTRL & FLEXCAN_FDCTRL_TDCOFF_MASK) >> FLEXCAN_FDCTRL_TDCOFF_SHIFT);
}

/*! \brief Set Transceiver Delay Compensation offset
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] offset : Transceiver Delay Compensation offset
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetTdcOffset(FlexCanRegType *obj, uint8_t offset)
{
    uint32_t tempReg;
    tempReg = obj->FDCTRL;
    tempReg &= (~FLEXCAN_FDCTRL_TDCOFF_MASK);
    tempReg |= (((uint32_t)offset) << FLEXCAN_FDCTRL_TDCOFF_SHIFT) & FLEXCAN_FDCTRL_TDCOFF_MASK;

    obj->FDCTRL = tempReg;
}

/*! \brief Get transceiver delay compensation value
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return : transceiver delay compensation value
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetFdctrlTdcval(const FlexCanRegType *obj)
{
    return ((obj->FDCTRL & FLEXCAN_FDCTRL_TDCVAL_MASK) >> FLEXCAN_FDCTRL_TDCVAL_SHIFT);
}

/*! \brief Get fast prescaler division factor
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return : fast prescaler division factor
 */
__attribute__((always_inline)) static inline uint16_t FlexCanReg_GetFdPrescalerDivision(const FlexCanRegType *obj)
{
    return ((obj->FDCBT & FLEXCAN_FDCBT_FPRESDIV_MASK) >> FLEXCAN_FDCBT_FPRESDIV_SHIFT);
}

/*! \brief Set CAN FD prescaler div
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] val : CAN FD prescaler div
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetFdPrescalerDivision(FlexCanRegType *obj, uint16_t val)
{
    uint32_t tempReg;
    tempReg = obj->FDCBT;
    tempReg &= (~FLEXCAN_FDCBT_FPRESDIV_MASK);
    tempReg |= (((uint32_t)val) << FLEXCAN_FDCBT_FPRESDIV_SHIFT) & FLEXCAN_FDCBT_FPRESDIV_MASK;

    obj->FDCBT = tempReg;
}

/*! \brief Get fast resync jump width
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return : fast resync jump width
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetFdResyncJumpWidth(const FlexCanRegType *obj)
{
    return ((obj->FDCBT & FLEXCAN_FDCBT_FRJW_MASK) >> FLEXCAN_FDCBT_FRJW_SHIFT);
}

/*! \brief Set CAN FD resync jump width
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] val : CAN FD resync jump width
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetFdResyncJumpWidth(FlexCanRegType *obj, uint16_t val)
{
    uint32_t tempReg;
    tempReg = obj->FDCBT;
    tempReg &= (~FLEXCAN_FDCBT_FRJW_MASK);
    tempReg |= (((uint32_t)val) << FLEXCAN_FDCBT_FRJW_SHIFT) & FLEXCAN_FDCBT_FRJW_MASK;

    obj->FDCBT = tempReg;
}

/*! \brief Get fast propagation segment
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return : fast propagation segment
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetFdPorpSeg(const FlexCanRegType *obj)
{
    return ((obj->FDCBT & FLEXCAN_FDCBT_FPROPSEG_MASK) >> FLEXCAN_FDCBT_FPROPSEG_SHIFT);
}

/*! \brief Set CAN FD porp seg
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] val : CAN FD porp seg
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetFdPorpSeg(FlexCanRegType *obj, uint16_t val)
{
    uint32_t tempReg;
    tempReg = obj->FDCBT;
    tempReg &= (~FLEXCAN_FDCBT_FPROPSEG_MASK);
    tempReg |= (((uint32_t)val) << FLEXCAN_FDCBT_FPROPSEG_SHIFT) & FLEXCAN_FDCBT_FPROPSEG_MASK;

    obj->FDCBT = tempReg;
}

/*! \brief Get fast phase segment 1
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return : fast phase segment 1
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetFdPhaseSeg1(const FlexCanRegType *obj)
{
    return ((obj->FDCBT & FLEXCAN_FDCBT_FPSEG1_MASK) >> FLEXCAN_FDCBT_FPSEG1_SHIFT);
}

/*! \brief Set CAN FD phase seg1
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] val : CAN FD phase seg1
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetFdPhaseSeg1(FlexCanRegType *obj, uint16_t val)
{
    uint32_t tempReg;
    tempReg = obj->FDCBT;
    tempReg &= (~FLEXCAN_FDCBT_FPSEG1_MASK);
    tempReg |= (((uint32_t)val) << FLEXCAN_FDCBT_FPSEG1_SHIFT) & FLEXCAN_FDCBT_FPSEG1_MASK;

    obj->FDCBT = tempReg;
}

/*! \brief Get fast phase segment 2
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return : fast phase segment 2
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetFdPhaseSeg2(const FlexCanRegType *obj)
{
    return ((obj->FDCBT & FLEXCAN_FDCBT_FPSEG2_MASK) >> FLEXCAN_FDCBT_FPSEG2_SHIFT);
}

/*! \brief Set CAN FD phase seg2
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] val : CAN FD phase seg2
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetFdPhaseSeg2(FlexCanRegType *obj, uint16_t val)
{
    uint32_t tempReg;
    tempReg = obj->FDCBT;
    tempReg &= (~FLEXCAN_FDCBT_FPSEG2_MASK);
    tempReg |= (((uint32_t)val) << FLEXCAN_FDCBT_FPSEG2_SHIFT) & FLEXCAN_FDCBT_FPSEG2_MASK;

    obj->FDCBT = tempReg;
}

/*! \brief Get crc mailbox number for FD_TXCRC
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return : crc mailbox number for FD_TXCRC
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetFdcrcFdmbcrc(const FlexCanRegType *obj)
{
    return ((obj->FDCRC & CAN_FDCRC_FDMBCRC_MASK) >> CAN_FDCRC_FDMBCRC_SHIFT);
}

/*! \brief Get extended transmitted CRC value
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return : extended transmitted CRC value
 */
__attribute__((always_inline)) static inline uint32_t FlexCanReg_GetFdcrcFdtxcrc(const FlexCanRegType *obj)
{
    return ((obj->FDCRC & CAN_FDCRC_FDTXCRC_MASK) >> CAN_FDCRC_FDTXCRC_SHIFT);
}

/*! \brief Set high resolution extended data phase prescaler division factor
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] val : value of high resolution extended data phase predivision factor
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetHighResExtDataPhasePreDiv(FlexCanRegType *obj, uint16_t val)
{
    uint32_t tempReg;
    tempReg = obj->EPRS;
    tempReg &= (~FLEXCAN_EPRS_EDPRESDIV_MASK);
    tempReg |= (((uint32_t)val) << FLEXCAN_EPRS_EDPRESDIV_SHIFT) & FLEXCAN_EPRS_EDPRESDIV_MASK;

    obj->EPRS = tempReg;
}

/*! \brief Get high resolution extended data phase prescaler division factor
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: value of high resolution extended data phase predivision factor
 */
__attribute__((always_inline)) static inline uint16_t FlexCanReg_GetHighResExtDataPhasePreDiv(FlexCanRegType *obj)
{
    return (uint16_t)(((obj->EPRS) & FLEXCAN_EPRS_EDPRESDIV_MASK) >> FLEXCAN_EPRS_EDPRESDIV_SHIFT);
}

/*! \brief Set high resolution extended nominal phase prescaler division factor
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] val : value of high resolution extended nominal phase predivision factor
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetHighResExtNominalPhasePreDiv(FlexCanRegType *obj, uint16_t val)
{
    uint32_t tempReg;
    tempReg = obj->EPRS;
    tempReg &= (~FLEXCAN_EPRS_ENPRESDIV_MASK);
    tempReg |= (((uint32_t)val) << FLEXCAN_EPRS_ENPRESDIV_SHIFT) & FLEXCAN_EPRS_ENPRESDIV_MASK;

    obj->EPRS = tempReg;
}

/*! \brief Get high resolution extended nominal phase prescaler division factor
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: value of high resolution extended nominal phase predivision factor
 */
__attribute__((always_inline)) static inline uint16_t FlexCanReg_GetHighResExtNominalPhasePreDiv(FlexCanRegType *obj)
{
    return (uint16_t)(((obj->EPRS) & FLEXCAN_EPRS_ENPRESDIV_MASK) >> FLEXCAN_EPRS_ENPRESDIV_SHIFT);
}

/*! \brief Set high resolution nominal resynchronization jump width
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] val : value of high resolution nominal resynchronization jump width
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetHighResNominalResyncJumpWidth(FlexCanRegType *obj, uint8_t val)
{
    uint32_t tempReg;
    tempReg = obj->ENCBT;
    tempReg &= (~FLEXCAN_ENCBT_NRJW_MASK);
    tempReg |= (((uint32_t)val) << FLEXCAN_ENCBT_NRJW_SHIFT) & FLEXCAN_ENCBT_NRJW_MASK;

    obj->ENCBT = tempReg;
}

/*! \brief Get high resolution nominal resynchronization jump width
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: value of high resolution nominal resynchronization jump width
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetHighResNominalResyncJumpWidth(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->EPRS) & FLEXCAN_EPRS_ENPRESDIV_MASK) >> FLEXCAN_EPRS_ENPRESDIV_SHIFT);
}

/*! \brief Set high resolution nominal time segment 2
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] val : value of high resolution nominal time segment 2
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetHighResTimeSeg2(FlexCanRegType *obj, uint8_t val)
{
    uint32_t tempReg;
    tempReg = obj->ENCBT;
    tempReg &= (~FLEXCAN_ENCBT_NTSEG2_MASK);
    tempReg |= (((uint32_t)val) << FLEXCAN_ENCBT_NTSEG2_SHIFT) & FLEXCAN_ENCBT_NTSEG2_MASK;

    obj->ENCBT = tempReg;
}

/*! \brief Get high resolution nominal nominal time segment 2
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: value of high resolution nominal nominal time segment 2
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetHighResTimeSeg2(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ENCBT) & FLEXCAN_ENCBT_NTSEG2_MASK) >> FLEXCAN_ENCBT_NTSEG2_SHIFT);
}

/*! \brief Set high resolution nominal time segment 1
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] val : value of high resolution nominal time segment 1
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetHighResTimeSeg1(FlexCanRegType *obj, uint8_t val)
{
    uint32_t tempReg;
    tempReg = obj->ENCBT;
    tempReg &= (~FLEXCAN_ENCBT_NTSEG1_MASK);
    tempReg |= (((uint32_t)val) << FLEXCAN_ENCBT_NTSEG1_SHIFT) & FLEXCAN_ENCBT_NTSEG1_MASK;

    obj->ENCBT = tempReg;
}

/*! \brief Get high resolution nominal nominal time segment 1
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: value of high resolution nominal nominal time segment 1
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetHighResTimeSeg1(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ENCBT) & FLEXCAN_ENCBT_NTSEG1_MASK) >> FLEXCAN_ENCBT_NTSEG1_SHIFT);
}

/*! \brief Set high resolution data phase resynchronization jump width
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] val : value of data phase resynchronization jump width
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetHighResDataPhaseResynJumpWidth(FlexCanRegType *obj, uint8_t val)
{
    uint32_t tempReg;
    tempReg = obj->EDCBT;
    tempReg &= (~FLEXCAN_EDCBT_DRJW_MASK);
    tempReg |= (((uint32_t)val) << FLEXCAN_EDCBT_DRJW_SHIFT) & FLEXCAN_EDCBT_DRJW_MASK;

    obj->EDCBT = tempReg;
}

/*! \brief Get high resolution data phase resynchronization jump width
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: value of high resolution data phase resynchronization jump width
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetHighResDataPhaseResynJumpWidth(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->EDCBT) & FLEXCAN_EDCBT_DRJW_MASK) >> FLEXCAN_EDCBT_DRJW_SHIFT);
}

/*! \brief Set high resolution data phase time segment 2
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] val : value of data phase time segment 2
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetHighResDataPhaseTimeSeg2(FlexCanRegType *obj, uint8_t val)
{
    uint32_t tempReg;
    tempReg = obj->EDCBT;
    tempReg &= (~FLEXCAN_EDCBT_DTSEG2_MASK);
    tempReg |= (((uint32_t)val) << FLEXCAN_EDCBT_DTSEG2_SHIFT) & FLEXCAN_EDCBT_DTSEG2_MASK;

    obj->EDCBT = tempReg;
}

/*! \brief Get high resolution data phase time segment 2
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: value of high resolution data phase time segment 2
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetHighResDataPhaseTimeSeg2(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->EDCBT) & FLEXCAN_EDCBT_DRJW_MASK) >> FLEXCAN_EDCBT_DRJW_SHIFT);
}

/*! \brief Set high resolution data phase time segment 1
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] val : value of data phase time segment 1
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetHighResDataPhaseTimeSeg1(FlexCanRegType *obj, uint8_t val)
{
    uint32_t tempReg;
    tempReg = obj->EDCBT;
    tempReg &= (~FLEXCAN_EDCBT_DTSEG1_MASK);
    tempReg |= (((uint32_t)val) << FLEXCAN_EDCBT_DTSEG1_SHIFT) & FLEXCAN_EDCBT_DTSEG1_MASK;

    obj->EDCBT = tempReg;
}

/*! \brief Get high resolution data phase time segment 1
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: value of high resolution data phase time segment 1
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetHighResDataPhaseTimeSeg1(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->EDCBT) & FLEXCAN_EDCBT_DTSEG1_MASK) >> FLEXCAN_EDCBT_DTSEG1_SHIFT);
}

/*! \brief Set enhanced Rx FIFO enable
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] enable : enhance Rx FIFO enable
 *                     - 0 : Enhance Rx FIFO enable
 *                     - 1 : Enhance Rx FIFO disable
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetEnhanceRxFifoEnable(FlexCanRegType *obj, uint8_t enable)
{
    uint32_t tempReg;
    tempReg = obj->ERFCR;
    tempReg &= (~FLEXCAN_ERFCR_ERFEN_MASK);
    tempReg |= (((uint32_t)enable) << FLEXCAN_ERFCR_ERFEN_SHIFT) & FLEXCAN_ERFCR_ERFEN_MASK;

    obj->ERFCR = tempReg;
}

/*! \brief Get enhanced Rx FIFO enable
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: enhanced Rx FIFO enable
 *          - 0 : Enhance Rx FIFO enable
 *          - 1 : Enhance Rx FIFO disable
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetEnhanceRxFifoEnable(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ERFCR) & FLEXCAN_ERFCR_ERFEN_MASK) >> FLEXCAN_ERFCR_ERFEN_SHIFT);
}

/*! \brief Set the last DMA address for each enhanced Rx FIFO element
 *
 * This function set the last DMA address for each Enchanced Rx FIFO element
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] value : last DMA address for each enhanced Rx FIFO element
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetEnhanceRxFifoDmaLastWord(FlexCanRegType *obj, uint8_t val)
{
    uint32_t tempReg;
    tempReg = obj->ERFCR;
    tempReg &= (~FLEXCAN_ERFCR_DMALW_MASK);
    tempReg |= (((uint32_t)val) << FLEXCAN_ERFCR_DMALW_SHIFT) & FLEXCAN_ERFCR_DMALW_MASK;

    obj->ERFCR = tempReg;
}

/*! \brief Get the last DMA address for each enhanced Rx FIFO element
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: the last DMA address for each enhanced Rx FIFO element
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetEnhanceRxFifoDmaLastWord(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ERFCR) & FLEXCAN_ERFCR_DMALW_MASK) >> FLEXCAN_ERFCR_DMALW_SHIFT);
}

/*! \brief Set the number of extended ID filter elemennts in enhannced Rx FIFO
 *
 * This function set the number of extended ID filter elemennts in enhannced Rx FIFO
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] value : the number of extended ID filter elemennts in enhannced Rx FIFO
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetExtIdFilterElementNum(FlexCanRegType *obj, uint8_t val)
{
    uint32_t tempReg;
    tempReg = obj->ERFCR;
    tempReg &= (~FLEXCAN_ERFCR_NEXIF_MASK);
    tempReg |= (((uint32_t)val) << FLEXCAN_ERFCR_NEXIF_SHIFT) & FLEXCAN_ERFCR_NEXIF_MASK;

    obj->ERFCR = tempReg;
}

/*! \brief Get the number of extended ID filter elements in enhannced Rx FIFO
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: the number of extended ID filter elemennts in enhannced Rx FIFO
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetExtIdFilterElementNum(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ERFCR) & FLEXCAN_ERFCR_NEXIF_MASK) >> FLEXCAN_ERFCR_NEXIF_SHIFT);
}

/*! \brief Set the number of enhanced Rx FIFO filter elements
 *
 * This function set the number of enhanced Rx FIFO filter elements
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] value : the number of enhanced Rx FIFO filter elements
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetEnhanceRxFifoFilterElementNum(FlexCanRegType *obj, uint8_t val)
{
    uint32_t tempReg;
    tempReg = obj->ERFCR;
    tempReg &= (~FLEXCAN_ERFCR_NFE_MASK);
    tempReg |= (((uint32_t)val) << FLEXCAN_ERFCR_NFE_SHIFT) & FLEXCAN_ERFCR_NFE_MASK;

    obj->ERFCR = tempReg;
}

/*! \brief Get the number of enhanced Rx FIFO filter elements
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: the number of enhanced Rx FIFO filter elements
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetEnhanceRxFifoFilterElementNum(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ERFCR) & FLEXCAN_ERFCR_NFE_MASK) >> FLEXCAN_ERFCR_NFE_SHIFT);
}

/*! \brief Set the enhanced Rx FIFO watermark
 *
 * This function set the enhanced Rx FIFO watermark
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] value : the enhanced Rx FIFO watermark
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetEnhanceRxFifoWatermark(FlexCanRegType *obj, uint8_t val)
{
    uint32_t tempReg;
    tempReg = obj->ERFCR;
    tempReg &= (~FLEXCAN_ERFCR_ERFWM_MASK);
    tempReg |= (((uint32_t)val) << FLEXCAN_ERFCR_ERFWM_SHIFT) & FLEXCAN_ERFCR_ERFWM_MASK;

    obj->ERFCR = tempReg;
}

/*! \brief Get the enhanced Rx FIFO watermark
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: enhanced Rx FIFO watermark
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetEnhanceRxFifoWatermark(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ERFCR) & FLEXCAN_ERFCR_ERFWM_MASK) >> FLEXCAN_ERFCR_ERFWM_SHIFT);
}

/*! \brief Set enhanced Rx FIFO underflow interrupt enable
 *
 * This function set enhanced Rx FIFO underflow interrupt enable
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] enable : enhanced Rx FIFO underflow interrupt enable
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetEnhanceRxFifoUnderflowIntEnable(FlexCanRegType *obj, uint8_t enable)
{
    uint32_t tempReg;
    tempReg = obj->ERFIER;
    tempReg &= (~FLEXCAN_ERFIER_ERFUFWIE_MASK);
    tempReg |= (((uint32_t)enable) << FLEXCAN_ERFIER_ERFUFWIE_SHIFT) & FLEXCAN_ERFIER_ERFUFWIE_MASK;

    obj->ERFIER = tempReg;
}

/*! \brief Get the enhanced Rx FIFO underflow interrupt enable
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: enhanced Rx FIFO underflow interrupt enable
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetEnhanceRxFifoUnderflowEnable(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ERFIER) & FLEXCAN_ERFIER_ERFUFWIE_MASK) >> FLEXCAN_ERFIER_ERFUFWIE_SHIFT);
}

/*! \brief Set enhanced Rx FIFO overflow interrupt enable
 *
 * This function set enhanced Rx FIFO overflow interrupt enable
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] enable : enhanced Rx FIFO overflow interrupt enable
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetEnhanceRxFifoOverflowIntEnable(FlexCanRegType *obj, uint8_t enable)
{
    uint32_t tempReg;
    tempReg = obj->ERFIER;
    tempReg &= (~FLEXCAN_ERFIER_ERFOVFIE_MASK);
    tempReg |= (((uint32_t)enable) << FLEXCAN_ERFIER_ERFOVFIE_SHIFT) & FLEXCAN_ERFIER_ERFOVFIE_MASK;

    obj->ERFIER = tempReg;
}

/*! \brief Get the enhanced Rx FIFO overflow interrupt enable
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: enhanced Rx FIFO overflow interrupt enable
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetEnhanceRxFifoOverflowIntEnable(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ERFIER) & FLEXCAN_ERFIER_ERFOVFIE_MASK) >> FLEXCAN_ERFIER_ERFOVFIE_SHIFT);
}

/*! \brief Set enhanced Rx FIFO watermark indication interrupt enable
 *
 * This function set enhanced Rx FIFO watermark indication interrupt enable
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] enable : enhanced Rx FIFO watermark indication interrupt enable
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetEnhanceRxFifoWatrmarkIntEnable(FlexCanRegType *obj, uint8_t enable)
{
    uint32_t tempReg;
    tempReg = obj->ERFIER;
    tempReg &= (~FLEXCAN_ERFIER_ERFWMIIE_MASK);
    tempReg |= (((uint32_t)enable) << FLEXCAN_ERFIER_ERFWMIIE_SHIFT) & FLEXCAN_ERFIER_ERFWMIIE_MASK;

    obj->ERFIER = tempReg;
}

/*! \brief Get enhanced Rx FIFO watermark indication interrupt enable
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: enhanced Rx FIFO watermark indication interrupt enable
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetEnhanceRxFifoWatrmarkIntEnable(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ERFIER) & FLEXCAN_ERFIER_ERFWMIIE_MASK) >> FLEXCAN_ERFIER_ERFWMIIE_SHIFT);
}

/*! \brief Set enhanced Rx FIFO data available interrupt enable
 *
 * This function set enhanced Rx FIFO data available interrupt enable
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] enable : enhanced Rx FIFO data available interrupt enable
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetEnhanceRxFifoDataAvailableIntEnable(FlexCanRegType *obj, uint8_t enable)
{
    uint32_t tempReg;
    tempReg = obj->ERFIER;
    tempReg &= (~FLEXCAN_ERFIER_ERFDAIE_MASK);
    tempReg |= (((uint32_t)enable) << FLEXCAN_ERFIER_ERFDAIE_SHIFT) & FLEXCAN_ERFIER_ERFDAIE_MASK;

    obj->ERFIER = tempReg;
}

/*! \brief Get enhanced Rx FIFO watermark data available interrupt enable
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: enhanced Rx FIFO watermark data available interrupt enable
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetEnhanceRxFifoDataAvailableIntEnable(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ERFIER) & FLEXCAN_ERFIER_ERFDAIE_MASK) >> FLEXCAN_ERFIER_ERFDAIE_SHIFT);
}

/*! \brief Clear enhanced Rx FIFO underflow interrupt flag
 *
 * \param[in] obj : pointer to FlexCAN register instance
 *
 */
__attribute__((always_inline)) static inline void FlexCanReg_ClearEnhanceRxFifoUnderflowFlag(FlexCanRegType *obj)
{
    obj->ERFSR = FLEXCAN_ERFSR_ERFUFW_MASK;
}

/*! \brief Get enhanced Rx FIFO underflow interrupt flag
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: enhanced Rx FIFO underflow interrupt flag
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetEnhanceRxFifoUnderflowFlag(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ERFSR) & FLEXCAN_ERFSR_ERFUFW_MASK) >> FLEXCAN_ERFSR_ERFUFW_SHIFT);
}

/*! \brief Clear enhanced Rx FIFO overflow interrupt flag
 *
 * \param[in] obj : pointer to FlexCAN register instance
 *
 */
__attribute__((always_inline)) static inline void FlexCanReg_ClearEnhanceRxFifoOverflowFlag(FlexCanRegType *obj)
{
    obj->ERFSR = FLEXCAN_ERFSR_ERFOVF_MASK;
}

/*! \brief Get enhanced Rx FIFO overflow interrupt flag
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: enhanced Rx FIFO overflow interrupt flag
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetEnhanceRxFifoOverflowFlag(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ERFSR) & FLEXCAN_ERFSR_ERFOVF_MASK) >> FLEXCAN_ERFSR_ERFOVF_SHIFT);
}

/*! \brief Clear enhanced Rx FIFO watermark indication interrupt flag
 *
 * \param[in] obj : pointer to FlexCAN register instance
 *
 */
__attribute__((always_inline)) static inline void FlexCanReg_ClearEnhanceRxFifoWatermarkFlag(FlexCanRegType *obj)
{
    obj->ERFSR = FLEXCAN_ERFSR_ERFWMI_MASK;
}

/*! \brief Get enhanced Rx FIFO watermark indication interrupt flag
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: enhanced Rx FIFO watermark indication interrupt flag
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetEnhanceRxFifoWatermarkFlag(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ERFSR) & FLEXCAN_ERFSR_ERFWMI_MASK) >> FLEXCAN_ERFSR_ERFWMI_SHIFT);
}

/*! \brief Clear enhanced Rx FIFO data available interrupt flag
 *
 * \param[in] obj : pointer to FlexCAN register instance
 *
 */
__attribute__((always_inline)) static inline void FlexCanReg_ClearEnhanceRxFifoDataAvailableFlag(FlexCanRegType *obj)
{
    obj->ERFSR = FLEXCAN_ERFSR_ERFDA_MASK;
}

/*! \brief Get enhanced Rx FIFO data available interrupt flag
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: enhanced Rx FIFO data available interrupt flag
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetEnhanceRxFifoDataAvailableFlag(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ERFSR) & FLEXCAN_ERFSR_ERFDA_MASK) >> FLEXCAN_ERFSR_ERFDA_SHIFT);
}

/*! \brief Clear enhanced Rx FIFO content
 *
 * \param[in] obj : pointer to FlexCAN register instance
 *
 */
__attribute__((always_inline)) static inline void FlexCanReg_ClearEnhanceRxFifoContent(FlexCanRegType *obj)
{
    obj->ERFSR |= FLEXCAN_ERFSR_ERFCLR_MASK;
}

/*! \brief Get enhanced Rx FIFO empty flag
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: enhanced Rx FIFO empty flag
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetEnhanceRxFifoEmptyFlag(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ERFSR) & FLEXCAN_ERFSR_ERFE_MASK) >> FLEXCAN_ERFSR_ERFE_SHIFT);
}

/*! \brief Get enhanced Rx FIFO full flag
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: enhanced Rx FIFO full flag
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetEnhanceRxFifoFullFlag(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ERFSR) & FLEXCAN_ERFSR_ERFF_MASK) >> FLEXCAN_ERFSR_ERFF_SHIFT);
}

/*! \brief Get element number stored in enhanced Rx FIFO
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: element number stored in enhanced Rx FIFO
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetEnhanceRxFifoElementNum(FlexCanRegType *obj)
{
    return (uint8_t)(((obj->ERFSR) & FLEXCAN_ERFSR_ERFEL_MASK) >> FLEXCAN_ERFSR_ERFEL_SHIFT);
}

/*! \brief Get message buffer high resolution time stamp
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: message buffer high resolution time stamp
 */
__attribute__((always_inline)) static inline uint32_t FlexCanReg_GetMsgBufHighResTimeStamp(FlexCanRegType *obj, uint16_t msgBufId)
{
    return obj->HR_TIME_STAMP[msgBufId];
}

/*! \brief Read enhanced Rx FIFO content
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[out] ptr : read data 32-bit pointer
 *
 */
__attribute__((always_inline)) static inline void FlexCanReg_ReadEnhRxFifo(FlexCanRegType *obj, uint32_t *ptr)
{
    for(uint8_t i = 0; i < 20; i++)
    {
        ptr[i] = obj->ENHRXFIFO[i];
    }
}

/*! \brief Set enhanced Rx FIFO filter element value
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] elementId : Rx FIFO filter element ID
 * \param[in] val : Rx FIFO filter value
 *
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetEnhanceRxFifoElement(FlexCanRegType *obj, uint16_t elementId, uint32_t val)
{
    obj->ERFFEL[elementId] = val;
}

/*! \brief Get enhanced Rx FIFO filter element value
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] elementId : Rx FIFO filter element ID
 * \return: enhanced Rx FIFO filter element value
 */
__attribute__((always_inline)) static inline uint32_t FlexCanReg_GetEnhanceRxFifoElement(FlexCanRegType *obj, uint16_t elementId)
{
    return obj->ERFFEL[elementId];
}

/*! \brief Get protocol exception enable
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: protocol exception enable
 *              0: protocol exception disable
 *              1: protocol exception enable
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetCtrl2Prexcen(const FlexCanRegType *obj)
{
    return ((obj->CTRL2 & FLEXCAN_CTRL2_PREXCEN_MASK) >> FLEXCAN_CTRL2_PREXCEN_SHIFT);
}

/*! \brief Sets protocol exception enable
 *
 * This function sets protocol exception enable
 *
 * \param[in] obj : pointer to CAN register instance
 * \param[in] value : protocol exception value
 *                    - 0b : protocol exception disable
 *                    - 1b : protocol exception enable
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetCtrl2Prexcen(FlexCanRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CTRL2;

    tmp &= ~FLEXCAN_CTRL2_PREXCEN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << FLEXCAN_CTRL2_PREXCEN_SHIFT)) & FLEXCAN_CTRL2_PREXCEN_MASK);
    obj->CTRL2 = tmp;
}

/*! \brief Get ISO CAN FD enable
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: ISO CAN FD enable
 *              0: ISO CAN FD disable
 *              1: ISO CAN FD enable
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetIsoFdEnalbe(const FlexCanRegType *obj)
{
    return ((obj->CTRL2 & FLEXCAN_CTRL2_ISOCANFDEN_MASK) >> FLEXCAN_CTRL2_ISOCANFDEN_SHIFT);
}

/*! \brief Set ISO CAN FD enable
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] value : ISO CAN FD enable
 *              0: ISO CAN FD disable
 *              1: ISO CAN FD enable
 * 
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetIsoFdEnalbe(FlexCanRegType *obj, uint8_t enable)
{
    uint32_t tempReg;
    tempReg = obj->CTRL2;
    tempReg &= (~FLEXCAN_CTRL2_ISOCANFDEN_MASK);
    tempReg |= (((uint32_t)enable) << FLEXCAN_CTRL2_ISOCANFDEN_SHIFT) & FLEXCAN_CTRL2_ISOCANFDEN_MASK;

    obj->CTRL2 = tempReg;
}

/*! \brief Get edge filter enable
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: edge filter enable
 *              0: edge filter enable
 *              1: edge filter disable
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetCtrl2Edfltdis(const FlexCanRegType *obj)
{
    return ((obj->CTRL2 & FLEXCAN_CTRL2_EDFLTDIS_MASK) >> FLEXCAN_CTRL2_EDFLTDIS_SHIFT);
}

/*! \brief Set edge filter enable
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] value : edge filter enable
 *              0: edge filter enable
 *              1: edge filter disable
 * 
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetCtrl2Edfltdis(FlexCanRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CTRL2;

    tmp &= ~FLEXCAN_CTRL2_EDFLTDIS_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << FLEXCAN_CTRL2_EDFLTDIS_SHIFT)) & FLEXCAN_CTRL2_EDFLTDIS_MASK);
    obj->CTRL2 = tmp;
}

/*! \brief Get lowest priority Tx mailbox 
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: lowest priority Tx mailbox 
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetEsr2Lptm(const FlexCanRegType *obj)
{
    return ((obj->ESR2 & FLEXCAN_ESR2_LPTM_MASK) >> FLEXCAN_ESR2_LPTM_SHIFT);
}

/*! \brief Get valid priority status
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: valid priority status
 *              0: contents of IMB and LPTM are invalid
 *              1: contents of IMB and LPTM are valid
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetEsr2Vps(const FlexCanRegType *obj)
{
    return ((obj->ESR2 & FLEXCAN_ESR2_VPS_MASK) >> FLEXCAN_ESR2_VPS_SHIFT);
}

/*! \brief Get Inactive mailbox
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: Inactive mailbox
 *              0: if CAN_ESR2.VPS is asserted, CAN_ESR2.LPTM is not an inactive mailbox
 *              1: if CAN_ESR2.VPS is asserted, there is at least one inactive maibox.
 *                 CAN_ESR2.LPTM content is the number of the first one
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetEsr2Imb(const FlexCanRegType *obj)
{
    return ((obj->ESR2 & FLEXCAN_ESR2_IMB_MASK) >> FLEXCAN_ESR2_IMB_SHIFT);
}

/*! \brief Get CRC mailbox
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: CRC mailbox, indicats the number of the mailbox corresponding to the value
 *          in the CAN_CRCR.TXCRC field
 *
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetCrcrMbcrc(const FlexCanRegType *obj)
{
    return ((obj->CRCR & FLEXCAN_CRCR_MBCRC_MASK) >> FLEXCAN_CRCR_MBCRC_SHIFT);
}

/*! \brief Get transmitted CRC mailbox
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \return: transmitted CRC mailbox, indicats the CRC value of the last transmitted
 *          message for non-FD frames
 *
 */
__attribute__((always_inline)) static inline uint16_t FlexCanReg_GetCrcrTxcrc(const FlexCanRegType *obj)
{
    return ((obj->CRCR & FLEXCAN_CRCR_TXCRC_MASK) >> FLEXCAN_CRCR_TXCRC_SHIFT);
}

/*! \brief Gets transmit error counter for all errors detected in received message
 *
 * This function gets transmit error counter for all errors detected in received message
 *
 * \param[in] obj : pointer to CAN register instance
 * \return transmit error counter for all errors detected in received message
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetEcrTxerrcnt(const FlexCanRegType *obj)
{
    return ((obj->ECR & FLEXCAN_ECR_TXERRCNT_MASK) >> FLEXCAN_ECR_TXERRCNT_SHIFT);
}

/*! \brief Set transmit error counter
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] value : transmit error counter
 *
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetEcrTxerrcnt(FlexCanRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->ECR;

    tmp &= ~FLEXCAN_ECR_TXERRCNT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << FLEXCAN_ECR_TXERRCNT_SHIFT)) & FLEXCAN_ECR_TXERRCNT_MASK);
    obj->ECR = tmp;
}

/*! \brief Gets receive error counter for all errors detected in received message
 *
 * This function gets receive error counter for all errors detected in received message
 *
 * \param[in] obj : pointer to CAN register instance
 * \return receive error counter for all errors detected in received message
 */
__attribute__((always_inline)) static inline uint8_t FlexCanReg_GetEcrRxerrcnt(const FlexCanRegType *obj)
{
    return ((obj->ECR & FLEXCAN_ECR_RXERRCNT_MASK) >> FLEXCAN_ECR_RXERRCNT_SHIFT);
}

/*! \brief Set receive error counter
 *
 *
 * \param[in] obj : pointer to FlexCAN register instance
 * \param[in] value : receive error counter
 *
 */
__attribute__((always_inline)) static inline void FlexCanReg_SetEcrRxerrcnt(FlexCanRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->ECR;

    tmp &= ~FLEXCAN_ECR_RXERRCNT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << FLEXCAN_ECR_RXERRCNT_SHIFT)) & FLEXCAN_ECR_RXERRCNT_MASK);
    obj->ECR = tmp;
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _FLEXCAN_REG_H_ */
