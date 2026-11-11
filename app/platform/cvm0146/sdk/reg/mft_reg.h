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

#ifndef _MFT_REG_H_
#define _MFT_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the MFT Registers
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

/* Total number of MFT channels */
#define MFT_CHANNEL_NUM                 (8)
/* Pair number of Deadtime channels */
#define MFT_DEADTIME_PAIR               (MFT_CHANNEL_NUM / 2)
/* Pair number of Deadtime channels */
#define MFT_FAULT_INPUT_NUM             (4)

/* SC Bit Fields */
#define MFT_SC_FLTPS_MASK               (0xF000000u)
#define MFT_SC_FLTPS_SHIFT              (24u)
#define MFT_SC_FLTPS_WIDTH              (4u)
#define MFT_SC_PWMEN7_MASK              (0x800000u)
#define MFT_SC_PWMEN7_SHIFT             (23u)
#define MFT_SC_PWMEN7_WIDTH             (1u)
#define MFT_SC_PWMEN6_MASK              (0x400000u)
#define MFT_SC_PWMEN6_SHIFT             (22u)
#define MFT_SC_PWMEN6_WIDTH             (1u)
#define MFT_SC_PWMEN5_MASK              (0x200000u)
#define MFT_SC_PWMEN5_SHIFT             (21u)
#define MFT_SC_PWMEN5_WIDTH             (1u)
#define MFT_SC_PWMEN4_MASK              (0x100000u)
#define MFT_SC_PWMEN4_SHIFT             (20u)
#define MFT_SC_PWMEN4_WIDTH             (1u)
#define MFT_SC_PWMEN3_MASK              (0x80000u)
#define MFT_SC_PWMEN3_SHIFT             (19u)
#define MFT_SC_PWMEN3_WIDTH             (1u)
#define MFT_SC_PWMEN2_MASK              (0x40000u)
#define MFT_SC_PWMEN2_SHIFT             (18u)
#define MFT_SC_PWMEN2_WIDTH             (1u)
#define MFT_SC_PWMEN1_MASK              (0x20000u)
#define MFT_SC_PWMEN1_SHIFT             (17u)
#define MFT_SC_PWMEN1_WIDTH             (1u)
#define MFT_SC_PWMEN0_MASK              (0x10000u)
#define MFT_SC_PWMEN0_SHIFT             (16u)
#define MFT_SC_PWMEN0_WIDTH             (1u)
#define MFT_SC_TOF_MASK                 (0x200u)
#define MFT_SC_TOF_SHIFT                (9u)
#define MFT_SC_TOF_WIDTH                (1u)
#define MFT_SC_TOIE_MASK                (0x100u)
#define MFT_SC_TOIE_SHIFT               (8u)
#define MFT_SC_TOIE_WIDTH               (1u)
#define MFT_SC_RF_MASK                  (0x80u)
#define MFT_SC_RF_SHIFT                 (7u)
#define MFT_SC_RF_WIDTH                 (1u)
#define MFT_SC_RIE_MASK                 (0x40u)
#define MFT_SC_RIE_SHIFT                (6u)
#define MFT_SC_RIE_WIDTH                (1u)
#define MFT_SC_CPWMS_MASK               (0x20u)
#define MFT_SC_CPWMS_SHIFT              (5u)
#define MFT_SC_CPWMS_WIDTH              (1u)
#define MFT_SC_CLKS_MASK                (0x18u)
#define MFT_SC_CLKS_SHIFT               (3u)
#define MFT_SC_CLKS_WIDTH               (2u)
#define MFT_SC_PS_MASK                  (0x07u)
#define MFT_SC_PS_SHIFT                 (0u)
#define MFT_SC_PS_WIDTH                 (3u)

/* CNT Bit Fields */
#define MFT_CNT_COUNT_MASK              (0xFFFFu)
#define MFT_CNT_COUNT_SHIFT             (0u)
#define MFT_CNT_COUNT_WIDTH             (16u)

/* MODULO Bit Fields */
#define MFT_MODULO_MOD_MASK             (0xFFFFu)
#define MFT_MODULO_MOD_SHIFT            (0u)
#define MFT_MODULO_MOD_WIDTH            (16u)

/* CSC Bit Fields */
#define MFT_CSC_CHOV_MASK               (0x400u)
#define MFT_CSC_CHOV_SHIFT              (10u)
#define MFT_CSC_CHOV_WIDTH              (1u)
#define MFT_CSC_CHIS_MASK               (0x200u)
#define MFT_CSC_CHIS_SHIFT              (9u)
#define MFT_CSC_CHIS_WIDTH              (1u)
#define MFT_CSC_TRIGMODE_MASK           (0x100u)
#define MFT_CSC_TRIGMODE_SHIFT          (8u)
#define MFT_CSC_TRIGMODE_WIDTH          (1u)
#define MFT_CSC_CHF_MASK                (0x80u)
#define MFT_CSC_CHF_SHIFT               (7u)
#define MFT_CSC_CHF_WIDTH               (1u)
#define MFT_CSC_CHIE_MASK               (0x40u)
#define MFT_CSC_CHIE_SHIFT              (6u)
#define MFT_CSC_CHIE_WIDTH              (1u)
#define MFT_CSC_MSB_MASK                (0x20u)
#define MFT_CSC_MSB_SHIFT               (5u)
#define MFT_CSC_MSB_WIDTH               (1u)
#define MFT_CSC_MSA_MASK                (0x10u)
#define MFT_CSC_MSA_SHIFT               (4u)
#define MFT_CSC_MSA_WIDTH               (1u)
#define MFT_CSC_ELSB_MASK               (0x08u)
#define MFT_CSC_ELSB_SHIFT              (3u)
#define MFT_CSC_ELSB_WIDTH              (1u)
#define MFT_CSC_ELSA_MASK               (0x04u)
#define MFT_CSC_ELSA_SHIFT              (2u)
#define MFT_CSC_ELSA_WIDTH              (1u)
#define MFT_CSC_ICRST_MASK              (0x02u)
#define MFT_CSC_ICRST_SHIFT             (1u)
#define MFT_CSC_ICRST_WIDTH             (1u)
#define MFT_CSC_DMA_MASK                (0x01u)
#define MFT_CSC_DMA_SHIFT               (0u)
#define MFT_CSC_DMA_WIDTH               (1u)

/* CV Bit Fields */
#define MFT_CV_VAL_MASK                 (0xFFFFu)
#define MFT_CV_VAL_SHIFT                (0u)
#define MFT_CV_VAL_WIDTH                (16u)

/* CNTIN Bit Fields */
#define MFT_CNTIN_CNTINIT_MASK          (0xFFFFu)
#define MFT_CNTIN_CNTINIT_SHIFT         (0u)
#define MFT_CNTIN_CNTINIT_WIDTH         (16u)

/* STATUS Bit Fields */
#define MFT_STATUS_CH7F_MASK            (0x80u)
#define MFT_STATUS_CH7F_SHIFT           (7u)
#define MFT_STATUS_CH7F_WIDTH           (1u)
#define MFT_STATUS_CH6F_MASK            (0x40u)
#define MFT_STATUS_CH6F_SHIFT           (6u)
#define MFT_STATUS_CH6F_WIDTH           (1u)
#define MFT_STATUS_CH5F_MASK            (0x20u)
#define MFT_STATUS_CH5F_SHIFT           (5u)
#define MFT_STATUS_CH5F_WIDTH           (1u)
#define MFT_STATUS_CH4F_MASK            (0x10u)
#define MFT_STATUS_CH4F_SHIFT           (4u)
#define MFT_STATUS_CH4F_WIDTH           (1u)
#define MFT_STATUS_CH3F_MASK            (0x08u)
#define MFT_STATUS_CH3F_SHIFT           (3u)
#define MFT_STATUS_CH3F_WIDTH           (1u)
#define MFT_STATUS_CH2F_MASK            (0x04u)
#define MFT_STATUS_CH2F_SHIFT           (2u)
#define MFT_STATUS_CH2F_WIDTH           (1u)
#define MFT_STATUS_CH1F_MASK            (0x02u)
#define MFT_STATUS_CH1F_SHIFT           (1u)
#define MFT_STATUS_CH1F_WIDTH           (1u)
#define MFT_STATUS_CH0F_MASK            (0x01u)
#define MFT_STATUS_CH0F_SHIFT           (0u)
#define MFT_STATUS_CH0F_WIDTH           (1u)

/* MODE Bit Fields */
#define MFT_MODE_FAULTIE_MASK           (0x80u)
#define MFT_MODE_FAULTIE_SHIFT          (7u)
#define MFT_MODE_FAULTIE_WIDTH          (1u)
#define MFT_MODE_FAULTM_MASK            (0x60u)
#define MFT_MODE_FAULTM_SHIFT           (5u)
#define MFT_MODE_FAULTM_WIDTH           (2u)
#define MFT_MODE_CAPTEST_MASK           (0x10u)
#define MFT_MODE_CAPTEST_SHIFT          (4u)
#define MFT_MODE_CAPTEST_WIDTH          (1u)
#define MFT_MODE_PWMSYNC_MASK           (0x08u)
#define MFT_MODE_PWMSYNC_SHIFT          (3u)
#define MFT_MODE_PWMSYNC_WIDTH          (1u)
#define MFT_MODE_WPDIS_MASK             (0x04u)
#define MFT_MODE_WPDIS_SHIFT            (2u)
#define MFT_MODE_WPDIS_WIDTH            (1u)
#define MFT_MODE_INIT_MASK              (0x02u)
#define MFT_MODE_INIT_SHIFT             (1u)
#define MFT_MODE_INIT_WIDTH             (1u)
#define MFT_MODE_MFTEN_MASK             (0x01u)
#define MFT_MODE_MFTEN_SHIFT            (0u)
#define MFT_MODE_MFTEN_WIDTH            (1u)

/* SYNC Bit Fields */
#define MFT_SYNC_SWSYNC_MASK            (0x80u)
#define MFT_SYNC_SWSYNC_SHIFT           (7u)
#define MFT_SYNC_SWSYNC_WIDTH           (1u)
#define MFT_SYNC_TRIG2_MASK             (0x40u)
#define MFT_SYNC_TRIG2_SHIFT            (6u)
#define MFT_SYNC_TRIG2_WIDTH            (1u)
#define MFT_SYNC_TRIG1_MASK             (0x20u)
#define MFT_SYNC_TRIG1_SHIFT            (5u)
#define MFT_SYNC_TRIG1_WIDTH            (1u)
#define MFT_SYNC_TRIG0_MASK             (0x10u)
#define MFT_SYNC_TRIG0_SHIFT            (4u)
#define MFT_SYNC_TRIG0_WIDTH            (1u)
#define MFT_SYNC_SYNCHOM_MASK           (0x08u)
#define MFT_SYNC_SYNCHOM_SHIFT          (3u)
#define MFT_SYNC_SYNCHOM_WIDTH          (1u)
#define MFT_SYNC_REINIT_MASK            (0x04u)
#define MFT_SYNC_REINIT_SHIFT           (2u)
#define MFT_SYNC_REINIT_WIDTH           (1u)
#define MFT_SYNC_CNTMAX_MASK            (0x02u)
#define MFT_SYNC_CNTMAX_SHIFT           (1u)
#define MFT_SYNC_CNTMAX_WIDTH           (1u)
#define MFT_SYNC_CNTMIN_MASK            (0x01u)
#define MFT_SYNC_CNTMIN_SHIFT           (0u)
#define MFT_SYNC_CNTMIN_WIDTH           (1u)

/* OUTINIT Bit Fields */
#define MFT_OUTINIT_CH7OI_MASK          (0x80u)
#define MFT_OUTINIT_CH7OI_SHIFT         (7u)
#define MFT_OUTINIT_CH7OI_WIDTH         (1u)
#define MFT_OUTINIT_CH6OI_MASK          (0x40u)
#define MFT_OUTINIT_CH6OI_SHIFT         (6u)
#define MFT_OUTINIT_CH6OI_WIDTH         (1u)
#define MFT_OUTINIT_CH5OI_MASK          (0x20u)
#define MFT_OUTINIT_CH5OI_SHIFT         (5u)
#define MFT_OUTINIT_CH5OI_WIDTH         (1u)
#define MFT_OUTINIT_CH4OI_MASK          (0x10u)
#define MFT_OUTINIT_CH4OI_SHIFT         (4u)
#define MFT_OUTINIT_CH4OI_WIDTH         (1u)
#define MFT_OUTINIT_CH3OI_MASK          (0x08u)
#define MFT_OUTINIT_CH3OI_SHIFT         (3u)
#define MFT_OUTINIT_CH3OI_WIDTH         (1u)
#define MFT_OUTINIT_CH2OI_MASK          (0x04u)
#define MFT_OUTINIT_CH2OI_SHIFT         (2u)
#define MFT_OUTINIT_CH2OI_WIDTH         (1u)
#define MFT_OUTINIT_CH1OI_MASK          (0x02u)
#define MFT_OUTINIT_CH1OI_SHIFT         (1u)
#define MFT_OUTINIT_CH1OI_WIDTH         (1u)
#define MFT_OUTINIT_CH0OI_MASK          (0x01u)
#define MFT_OUTINIT_CH0OI_SHIFT         (0u)
#define MFT_OUTINIT_CH0OI_WIDTH         (1u)

/* OUTMASK Bit Fields */
#define MFT_OUTMASK_CH7OM_MASK          (0x80u)
#define MFT_OUTMASK_CH7OM_SHIFT         (7u)
#define MFT_OUTMASK_CH7OM_WIDTH         (1u)
#define MFT_OUTMASK_CH6OM_MASK          (0x40u)
#define MFT_OUTMASK_CH6OM_SHIFT         (6u)
#define MFT_OUTMASK_CH6OM_WIDTH         (1u)
#define MFT_OUTMASK_CH5OM_MASK          (0x20u)
#define MFT_OUTMASK_CH5OM_SHIFT         (5u)
#define MFT_OUTMASK_CH5OM_WIDTH         (1u)
#define MFT_OUTMASK_CH4OM_MASK          (0x10u)
#define MFT_OUTMASK_CH4OM_SHIFT         (4u)
#define MFT_OUTMASK_CH4OM_WIDTH         (1u)
#define MFT_OUTMASK_CH3OM_MASK          (0x08u)
#define MFT_OUTMASK_CH3OM_SHIFT         (3u)
#define MFT_OUTMASK_CH3OM_WIDTH         (1u)
#define MFT_OUTMASK_CH2OM_MASK          (0x04u)
#define MFT_OUTMASK_CH2OM_SHIFT         (2u)
#define MFT_OUTMASK_CH2OM_WIDTH         (1u)
#define MFT_OUTMASK_CH1OM_MASK          (0x02u)
#define MFT_OUTMASK_CH1OM_SHIFT         (1u)
#define MFT_OUTMASK_CH1OM_WIDTH         (1u)
#define MFT_OUTMASK_CH0OM_MASK          (0x01u)
#define MFT_OUTMASK_CH0OM_SHIFT         (0u)
#define MFT_OUTMASK_CH0OM_WIDTH         (1u)

/* COMBINE Bit Fields */
#define MFT_COMBINE_MCOMBINE3_MASK      (0x80000000u)
#define MFT_COMBINE_MCOMBINE3_SHIFT     (31u)
#define MFT_COMBINE_MCOMBINE3_WIDTH     (1u)
#define MFT_COMBINE_FAULTEN3_MASK       (0x40000000u)
#define MFT_COMBINE_FAULTEN3_SHIFT      (30u)
#define MFT_COMBINE_FAULTEN3_WIDTH      (1u)
#define MFT_COMBINE_SYNCEN3_MASK        (0x20000000u)
#define MFT_COMBINE_SYNCEN3_SHIFT       (29u)
#define MFT_COMBINE_SYNCEN3_WIDTH       (1u)
#define MFT_COMBINE_DTEN3_MASK          (0x10000000u)
#define MFT_COMBINE_DTEN3_SHIFT         (28u)
#define MFT_COMBINE_DTEN3_WIDTH         (1u)
#define MFT_COMBINE_DECAP3_MASK         (0x8000000u)
#define MFT_COMBINE_DECAP3_SHIFT        (27u)
#define MFT_COMBINE_DECAP3_WIDTH        (1u)
#define MFT_COMBINE_DECAPEN3_MASK       (0x4000000u)
#define MFT_COMBINE_DECAPEN3_SHIFT      (26u)
#define MFT_COMBINE_DECAPEN3_WIDTH      (1u)
#define MFT_COMBINE_COMP3_MASK          (0x2000000u)
#define MFT_COMBINE_COMP3_SHIFT         (25u)
#define MFT_COMBINE_COMP3_WIDTH         (1u)
#define MFT_COMBINE_COMBINE3_MASK       (0x1000000u)
#define MFT_COMBINE_COMBINE3_SHIFT      (24u)
#define MFT_COMBINE_COMBINE3_WIDTH      (1u)
#define MFT_COMBINE_MCOMBINE2_MASK      (0x800000u)
#define MFT_COMBINE_MCOMBINE2_SHIFT     (23u)
#define MFT_COMBINE_MCOMBINE2_WIDTH     (1u)
#define MFT_COMBINE_FAULTEN2_MASK       (0x400000u)
#define MFT_COMBINE_FAULTEN2_SHIFT      (22u)
#define MFT_COMBINE_FAULTEN2_WIDTH      (1u)
#define MFT_COMBINE_SYNCEN2_MASK        (0x200000u)
#define MFT_COMBINE_SYNCEN2_SHIFT       (21u)
#define MFT_COMBINE_SYNCEN2_WIDTH       (1u)
#define MFT_COMBINE_DTEN2_MASK          (0x100000u)
#define MFT_COMBINE_DTEN2_SHIFT         (20u)
#define MFT_COMBINE_DTEN2_WIDTH         (1u)
#define MFT_COMBINE_DECAP2_MASK         (0x80000u)
#define MFT_COMBINE_DECAP2_SHIFT        (19u)
#define MFT_COMBINE_DECAP2_WIDTH        (1u)
#define MFT_COMBINE_DECAPEN2_MASK       (0x40000u)
#define MFT_COMBINE_DECAPEN2_SHIFT      (18u)
#define MFT_COMBINE_DECAPEN2_WIDTH      (1u)
#define MFT_COMBINE_COMP2_MASK          (0x20000u)
#define MFT_COMBINE_COMP2_SHIFT         (17u)
#define MFT_COMBINE_COMP2_WIDTH         (1u)
#define MFT_COMBINE_COMBINE2_MASK       (0x10000u)
#define MFT_COMBINE_COMBINE2_SHIFT      (16u)
#define MFT_COMBINE_COMBINE2_WIDTH      (1u)
#define MFT_COMBINE_MCOMBINE1_MASK      (0x8000u)
#define MFT_COMBINE_MCOMBINE1_SHIFT     (15u)
#define MFT_COMBINE_MCOMBINE1_WIDTH     (1u)
#define MFT_COMBINE_FAULTEN1_MASK       (0x4000u)
#define MFT_COMBINE_FAULTEN1_SHIFT      (14u)
#define MFT_COMBINE_FAULTEN1_WIDTH      (1u)
#define MFT_COMBINE_SYNCEN1_MASK        (0x2000u)
#define MFT_COMBINE_SYNCEN1_SHIFT       (13u)
#define MFT_COMBINE_SYNCEN1_WIDTH       (1u)
#define MFT_COMBINE_DTEN1_MASK          (0x1000u)
#define MFT_COMBINE_DTEN1_SHIFT         (12u)
#define MFT_COMBINE_DTEN1_WIDTH         (1u)
#define MFT_COMBINE_DECAP1_MASK         (0x800u)
#define MFT_COMBINE_DECAP1_SHIFT        (11u)
#define MFT_COMBINE_DECAP1_WIDTH        (1u)
#define MFT_COMBINE_DECAPEN1_MASK       (0x400u)
#define MFT_COMBINE_DECAPEN1_SHIFT      (10u)
#define MFT_COMBINE_DECAPEN1_WIDTH      (1u)
#define MFT_COMBINE_COMP1_MASK          (0x200u)
#define MFT_COMBINE_COMP1_SHIFT         (9u)
#define MFT_COMBINE_COMP1_WIDTH         (1u)
#define MFT_COMBINE_COMBINE1_MASK       (0x100u)
#define MFT_COMBINE_COMBINE1_SHIFT      (8u)
#define MFT_COMBINE_COMBINE1_WIDTH      (1u)
#define MFT_COMBINE_MCOMBINE0_MASK      (0x80u)
#define MFT_COMBINE_MCOMBINE0_SHIFT     (7u)
#define MFT_COMBINE_MCOMBINE0_WIDTH     (1u)
#define MFT_COMBINE_FAULTEN0_MASK       (0x40u)
#define MFT_COMBINE_FAULTEN0_SHIFT      (6u)
#define MFT_COMBINE_FAULTEN0_WIDTH      (1u)
#define MFT_COMBINE_SYNCEN0_MASK        (0x20u)
#define MFT_COMBINE_SYNCEN0_SHIFT       (5u)
#define MFT_COMBINE_SYNCEN0_WIDTH       (1u)
#define MFT_COMBINE_DTEN0_MASK          (0x10u)
#define MFT_COMBINE_DTEN0_SHIFT         (4u)
#define MFT_COMBINE_DTEN0_WIDTH         (1u)
#define MFT_COMBINE_DECAP0_MASK         (0x08u)
#define MFT_COMBINE_DECAP0_SHIFT        (3u)
#define MFT_COMBINE_DECAP0_WIDTH        (1u)
#define MFT_COMBINE_DECAPEN0_MASK       (0x04u)
#define MFT_COMBINE_DECAPEN0_SHIFT      (2u)
#define MFT_COMBINE_DECAPEN0_WIDTH      (1u)
#define MFT_COMBINE_COMP0_MASK          (0x02u)
#define MFT_COMBINE_COMP0_SHIFT         (1u)
#define MFT_COMBINE_COMP0_WIDTH         (1u)
#define MFT_COMBINE_COMBINE0_MASK       (0x01u)
#define MFT_COMBINE_COMBINE0_SHIFT      (0u)
#define MFT_COMBINE_COMBINE0_WIDTH      (1u)

/* DEADTIME Bit Fields */
#define MFT_DEADTIME_DTVALEX_MASK       (0xF0000u)
#define MFT_DEADTIME_DTVALEX_SHIFT      (16u)
#define MFT_DEADTIME_DTVALEX_WIDTH      (4u)
#define MFT_DEADTIME_DTPS_MASK          (0xC0u)
#define MFT_DEADTIME_DTPS_SHIFT         (6u)
#define MFT_DEADTIME_DTPS_WIDTH         (2u)
#define MFT_DEADTIME_DTVAL_MASK         (0x3Fu)
#define MFT_DEADTIME_DTVAL_SHIFT        (0u)
#define MFT_DEADTIME_DTVAL_WIDTH        (6u)

/* EXTTRIG Bit Fields */
#define MFT_EXTTRIG_CH7TRIG_MASK        (0x200u)
#define MFT_EXTTRIG_CH7TRIG_SHIFT       (9u)
#define MFT_EXTTRIG_CH7TRIG_WIDTH       (1u)
#define MFT_EXTTRIG_CH6TRIG_MASK        (0x100u)
#define MFT_EXTTRIG_CH6TRIG_SHIFT       (8u)
#define MFT_EXTTRIG_CH6TRIG_WIDTH       (1u)
#define MFT_EXTTRIG_TRIGF_MASK          (0x80u)
#define MFT_EXTTRIG_TRIGF_SHIFT         (7u)
#define MFT_EXTTRIG_TRIGF_WIDTH         (1u)
#define MFT_EXTTRIG_INITTRIGEN_MASK     (0x40u)
#define MFT_EXTTRIG_INITTRIGEN_SHIFT    (6u)
#define MFT_EXTTRIG_INITTRIGEN_WIDTH    (1u)
#define MFT_EXTTRIG_CH1TRIG_MASK        (0x20u)
#define MFT_EXTTRIG_CH1TRIG_SHIFT       (5u)
#define MFT_EXTTRIG_CH1TRIG_WIDTH       (1u)
#define MFT_EXTTRIG_CH0TRIG_MASK        (0x10u)
#define MFT_EXTTRIG_CH0TRIG_SHIFT       (4u)
#define MFT_EXTTRIG_CH0TRIG_WIDTH       (1u)
#define MFT_EXTTRIG_CH5TRIG_MASK        (0x08u)
#define MFT_EXTTRIG_CH5TRIG_SHIFT       (3u)
#define MFT_EXTTRIG_CH5TRIG_WIDTH       (1u)
#define MFT_EXTTRIG_CH4TRIG_MASK        (0x04u)
#define MFT_EXTTRIG_CH4TRIG_SHIFT       (2u)
#define MFT_EXTTRIG_CH4TRIG_WIDTH       (1u)
#define MFT_EXTTRIG_CH3TRIG_MASK        (0x02u)
#define MFT_EXTTRIG_CH3TRIG_SHIFT       (1u)
#define MFT_EXTTRIG_CH3TRIG_WIDTH       (1u)
#define MFT_EXTTRIG_CH2TRIG_MASK        (0x01u)
#define MFT_EXTTRIG_CH2TRIG_SHIFT       (0u)
#define MFT_EXTTRIG_CH2TRIG_WIDTH       (1u)

/* POL Bit Fields */
#define MFT_POL_POL7_MASK               (0x80u)
#define MFT_POL_POL7_SHIFT              (7u)
#define MFT_POL_POL7_WIDTH              (1u)
#define MFT_POL_POL6_MASK               (0x40u)
#define MFT_POL_POL6_SHIFT              (6u)
#define MFT_POL_POL6_WIDTH              (1u)
#define MFT_POL_POL5_MASK               (0x20u)
#define MFT_POL_POL5_SHIFT              (5u)
#define MFT_POL_POL5_WIDTH              (1u)
#define MFT_POL_POL4_MASK               (0x10u)
#define MFT_POL_POL4_SHIFT              (4u)
#define MFT_POL_POL4_WIDTH              (1u)
#define MFT_POL_POL3_MASK               (0x08u)
#define MFT_POL_POL3_SHIFT              (3u)
#define MFT_POL_POL3_WIDTH              (1u)
#define MFT_POL_POL2_MASK               (0x04u)
#define MFT_POL_POL2_SHIFT              (2u)
#define MFT_POL_POL2_WIDTH              (1u)
#define MFT_POL_POL1_MASK               (0x02u)
#define MFT_POL_POL1_SHIFT              (1u)
#define MFT_POL_POL1_WIDTH              (1u)
#define MFT_POL_POL0_MASK               (0x01u)
#define MFT_POL_POL0_SHIFT              (0u)
#define MFT_POL_POL0_WIDTH              (1u)

/* FMS Bit Fields */
#define MFT_FMS_FAULTF_MASK             (0x80u)
#define MFT_FMS_FAULTF_SHIFT            (7u)
#define MFT_FMS_FAULTF_WIDTH            (1u)
#define MFT_FMS_WPEN_MASK               (0x40u)
#define MFT_FMS_WPEN_SHIFT              (6u)
#define MFT_FMS_WPEN_WIDTH              (1u)
#define MFT_FMS_FAULTIN_MASK            (0x20u)
#define MFT_FMS_FAULTIN_SHIFT           (5u)
#define MFT_FMS_FAULTIN_WIDTH           (1u)
#define MFT_FMS_FAULTF3_MASK            (0x08u)
#define MFT_FMS_FAULTF3_SHIFT           (3u)
#define MFT_FMS_FAULTF3_WIDTH           (1u)
#define MFT_FMS_FAULTF2_MASK            (0x04u)
#define MFT_FMS_FAULTF2_SHIFT           (2u)
#define MFT_FMS_FAULTF2_WIDTH           (1u)
#define MFT_FMS_FAULTF1_MASK            (0x02u)
#define MFT_FMS_FAULTF1_SHIFT           (1u)
#define MFT_FMS_FAULTF1_WIDTH           (1u)
#define MFT_FMS_FAULTF0_MASK            (0x01u)
#define MFT_FMS_FAULTF0_SHIFT           (0u)
#define MFT_FMS_FAULTF0_WIDTH           (1u)

/* FILTER Bit Fields */
#define MFT_FILTER_CH3FVAL_MASK         (0xF000u)
#define MFT_FILTER_CH3FVAL_SHIFT        (12u)
#define MFT_FILTER_CH3FVAL_WIDTH        (4u)
#define MFT_FILTER_CH2FVAL_MASK         (0xF00u)
#define MFT_FILTER_CH2FVAL_SHIFT        (8u)
#define MFT_FILTER_CH2FVAL_WIDTH        (4u)
#define MFT_FILTER_CH1FVAL_MASK         (0xF0u)
#define MFT_FILTER_CH1FVAL_SHIFT        (4u)
#define MFT_FILTER_CH1FVAL_WIDTH        (4u)
#define MFT_FILTER_CH0FVAL_MASK         (0x0Fu)
#define MFT_FILTER_CH0FVAL_SHIFT        (0u)
#define MFT_FILTER_CH0FVAL_WIDTH        (4u)

/* FLTCTRL Bit Fields */
#define MFT_FLTCTRL_FSTATE_MASK         (0x8000u)
#define MFT_FLTCTRL_FSTATE_SHIFT        (15u)
#define MFT_FLTCTRL_FSTATE_WIDTH        (1u)
#define MFT_FLTCTRL_FFVAL_MASK          (0xF00u)
#define MFT_FLTCTRL_FFVAL_SHIFT         (8u)
#define MFT_FLTCTRL_FFVAL_WIDTH         (4u)
#define MFT_FLTCTRL_FFLTR3EN_MASK       (0x80u)
#define MFT_FLTCTRL_FFLTR3EN_SHIFT      (7u)
#define MFT_FLTCTRL_FFLTR3EN_WIDTH      (1u)
#define MFT_FLTCTRL_FFLTR2EN_MASK       (0x40u)
#define MFT_FLTCTRL_FFLTR2EN_SHIFT      (6u)
#define MFT_FLTCTRL_FFLTR2EN_WIDTH      (1u)
#define MFT_FLTCTRL_FFLTR1EN_MASK       (0x20u)
#define MFT_FLTCTRL_FFLTR1EN_SHIFT      (5u)
#define MFT_FLTCTRL_FFLTR1EN_WIDTH      (1u)
#define MFT_FLTCTRL_FFLTR0EN_MASK       (0x10u)
#define MFT_FLTCTRL_FFLTR0EN_SHIFT      (4u)
#define MFT_FLTCTRL_FFLTR0EN_WIDTH      (1u)
#define MFT_FLTCTRL_FAULT3EN_MASK       (0x08u)
#define MFT_FLTCTRL_FAULT3EN_SHIFT      (3u)
#define MFT_FLTCTRL_FAULT3EN_WIDTH      (1u)
#define MFT_FLTCTRL_FAULT2EN_MASK       (0x04u)
#define MFT_FLTCTRL_FAULT2EN_SHIFT      (2u)
#define MFT_FLTCTRL_FAULT2EN_WIDTH      (1u)
#define MFT_FLTCTRL_FAULT1EN_MASK       (0x02u)
#define MFT_FLTCTRL_FAULT1EN_SHIFT      (1u)
#define MFT_FLTCTRL_FAULT1EN_WIDTH      (1u)
#define MFT_FLTCTRL_FAULT0EN_MASK       (0x01u)
#define MFT_FLTCTRL_FAULT0EN_SHIFT      (0u)
#define MFT_FLTCTRL_FAULT0EN_WIDTH      (1u)

/* QDCTRL Bit Fields */
#define MFT_QDCTRL_PHZCOF_MASK          (0x1000u)                                   
#define MFT_QDCTRL_PHZCOF_SHIFT         (12)                                         
#define MFT_QDCTRL_PHZCOF_WIDTH         (1)                                          
#define MFT_QDCTRL_PHZMODE_MASK         (0xC00u)                                    
#define MFT_QDCTRL_PHZMODE_SHIFT        (10)                                        
#define MFT_QDCTRL_PHZMODE_WIDTH        (2)                                          
#define MFT_QDCTRL_PHZPOL_MASK          (0x200u)                                     
#define MFT_QDCTRL_PHZPOL_SHIFT         (9)                                          
#define MFT_QDCTRL_PHZPOL_WIDTH         (1)                                         
#define MFT_QDCTRL_PHZFLTREN_MASK       (0x100u)                                     
#define MFT_QDCTRL_PHZFLTREN_SHIFT      (8)                                         
#define MFT_QDCTRL_PHZFLTREN_WIDTH      (1)                                        
#define MFT_QDCTRL_PHAFLTREN_MASK       (0x80u)
#define MFT_QDCTRL_PHAFLTREN_SHIFT      (7u)
#define MFT_QDCTRL_PHAFLTREN_WIDTH      (1u)
#define MFT_QDCTRL_PHBFLTREN_MASK       (0x40u)
#define MFT_QDCTRL_PHBFLTREN_SHIFT      (6u)
#define MFT_QDCTRL_PHBFLTREN_WIDTH      (1u)
#define MFT_QDCTRL_PHAPOL_MASK          (0x20u)
#define MFT_QDCTRL_PHAPOL_SHIFT         (5u)
#define MFT_QDCTRL_PHAPOL_WIDTH         (1u)
#define MFT_QDCTRL_PHBPOL_MASK          (0x10u)
#define MFT_QDCTRL_PHBPOL_SHIFT         (4u)
#define MFT_QDCTRL_PHBPOL_WIDTH         (1u)
#define MFT_QDCTRL_QUADMODE_MASK        (0x08u)
#define MFT_QDCTRL_QUADMODE_SHIFT       (3u)
#define MFT_QDCTRL_QUADMODE_WIDTH       (1u)
#define MFT_QDCTRL_QUADIR_MASK          (0x04u)
#define MFT_QDCTRL_QUADIR_SHIFT         (2u)
#define MFT_QDCTRL_QUADIR_WIDTH         (1u)
#define MFT_QDCTRL_TOFDIR_MASK          (0x02u)
#define MFT_QDCTRL_TOFDIR_SHIFT         (1u)
#define MFT_QDCTRL_TOFDIR_WIDTH         (1u)
#define MFT_QDCTRL_QUADEN_MASK          (0x01u)
#define MFT_QDCTRL_QUADEN_SHIFT         (0u)
#define MFT_QDCTRL_QUADEN_WIDTH         (1u)

/* CONF Bit Fields */
#define MFT_CONF_ITRIGR_MASK            (0x800u)
#define MFT_CONF_ITRIGR_SHIFT           (11u)
#define MFT_CONF_ITRIGR_WIDTH           (1u)
#define MFT_CONF_GTBEOUT_MASK           (0x400u)
#define MFT_CONF_GTBEOUT_SHIFT          (10u)
#define MFT_CONF_GTBEOUT_WIDTH          (1u)
#define MFT_CONF_GTBEEN_MASK            (0x200u)
#define MFT_CONF_GTBEEN_SHIFT           (9u)
#define MFT_CONF_GTBEEN_WIDTH           (1u)
#define MFT_CONF_BDMMODE_MASK           (0xC0u)
#define MFT_CONF_BDMMODE_SHIFT          (6u)
#define MFT_CONF_BDMMODE_WIDTH          (2u)
#define MFT_CONF_LDFQ_MASK              (0x1Fu)
#define MFT_CONF_LDFQ_SHIFT             (0u)
#define MFT_CONF_LDFQ_WIDTH             (5u)

/* FLTPOL Bit Fields */
#define MFT_FLTPOL_FLT3POL_MASK         (0x08u)
#define MFT_FLTPOL_FLT3POL_SHIFT        (3u)
#define MFT_FLTPOL_FLT3POL_WIDTH        (1u)
#define MFT_FLTPOL_FLT2POL_MASK         (0x04u)
#define MFT_FLTPOL_FLT2POL_SHIFT        (2u)
#define MFT_FLTPOL_FLT2POL_WIDTH        (1u)
#define MFT_FLTPOL_FLT1POL_MASK         (0x02u)
#define MFT_FLTPOL_FLT1POL_SHIFT        (1u)
#define MFT_FLTPOL_FLT1POL_WIDTH        (1u)
#define MFT_FLTPOL_FLT0POL_MASK         (0x01u)
#define MFT_FLTPOL_FLT0POL_SHIFT        (0u)
#define MFT_FLTPOL_FLT0POL_WIDTH        (1u)

/* SYNCONF Bit Fields */
#define MFT_SYNCONF_HWSOC_MASK          (0x100000u)
#define MFT_SYNCONF_HWSOC_SHIFT         (20u)
#define MFT_SYNCONF_HWSOC_WIDTH         (1u)
#define MFT_SYNCONF_HWINVC_MASK         (0x80000u)
#define MFT_SYNCONF_HWINVC_SHIFT        (19u)
#define MFT_SYNCONF_HWINVC_WIDTH        (1u)
#define MFT_SYNCONF_HWOM_MASK           (0x40000u)
#define MFT_SYNCONF_HWOM_SHIFT          (18u)
#define MFT_SYNCONF_HWOM_WIDTH          (1u)
#define MFT_SYNCONF_HWWRBUF_MASK        (0x20000u)
#define MFT_SYNCONF_HWWRBUF_SHIFT       (17u)
#define MFT_SYNCONF_HWWRBUF_WIDTH       (1u)
#define MFT_SYNCONF_HWRSTCNT_MASK       (0x10000u)
#define MFT_SYNCONF_HWRSTCNT_SHIFT      (16u)
#define MFT_SYNCONF_HWRSTCNT_WIDTH      (1u)
#define MFT_SYNCONF_SWSOC_MASK          (0x1000u)
#define MFT_SYNCONF_SWSOC_SHIFT         (12u)
#define MFT_SYNCONF_SWSOC_WIDTH         (1u)
#define MFT_SYNCONF_SWINVC_MASK         (0x800u)
#define MFT_SYNCONF_SWINVC_SHIFT        (11u)
#define MFT_SYNCONF_SWINVC_WIDTH        (1u)
#define MFT_SYNCONF_SWOM_MASK           (0x400u)
#define MFT_SYNCONF_SWOM_SHIFT          (10u)
#define MFT_SYNCONF_SWOM_WIDTH          (1u)
#define MFT_SYNCONF_SWWRBUF_MASK        (0x200u)
#define MFT_SYNCONF_SWWRBUF_SHIFT       (9u)
#define MFT_SYNCONF_SWWRBUF_WIDTH       (1u)
#define MFT_SYNCONF_SWRSTCNT_MASK       (0x100u)
#define MFT_SYNCONF_SWRSTCNT_SHIFT      (8u)
#define MFT_SYNCONF_SWRSTCNT_WIDTH      (1u)
#define MFT_SYNCONF_SYNCMODE_MASK       (0x80u)
#define MFT_SYNCONF_SYNCMODE_SHIFT      (7u)
#define MFT_SYNCONF_SYNCMODE_WIDTH      (1u)
#define MFT_SYNCONF_SWOC_MASK           (0x20u)
#define MFT_SYNCONF_SWOC_SHIFT          (5u)
#define MFT_SYNCONF_SWOC_WIDTH          (1u)
#define MFT_SYNCONF_INVC_MASK           (0x10u)
#define MFT_SYNCONF_INVC_SHIFT          (4u)
#define MFT_SYNCONF_INVC_WIDTH          (1u)
#define MFT_SYNCONF_CNTINC_MASK         (0x04u)
#define MFT_SYNCONF_CNTINC_SHIFT        (2u)
#define MFT_SYNCONF_CNTINC_WIDTH        (1u)
#define MFT_SYNCONF_HWTRIGMODE_MASK     (0x01u)
#define MFT_SYNCONF_HWTRIGMODE_SHIFT    (0u)
#define MFT_SYNCONF_HWTRIGMODE_WIDTH    (1u)

/* INVCTRL Bit Fields */
#define MFT_INVCTRL_INV3EN_MASK         (0x08u)
#define MFT_INVCTRL_INV3EN_SHIFT        (3u)
#define MFT_INVCTRL_INV3EN_WIDTH        (1u)
#define MFT_INVCTRL_INV2EN_MASK         (0x04u)
#define MFT_INVCTRL_INV2EN_SHIFT        (2u)
#define MFT_INVCTRL_INV2EN_WIDTH        (1u)
#define MFT_INVCTRL_INV1EN_MASK         (0x02u)
#define MFT_INVCTRL_INV1EN_SHIFT        (1u)
#define MFT_INVCTRL_INV1EN_WIDTH        (1u)
#define MFT_INVCTRL_INV0EN_MASK         (0x01u)
#define MFT_INVCTRL_INV0EN_SHIFT        (0u)
#define MFT_INVCTRL_INV0EN_WIDTH        (1u)

/* SWOCTRL Bit Fields */
#define MFT_SWOCTRL_CH7OCV_MASK         (0x8000u)
#define MFT_SWOCTRL_CH7OCV_SHIFT        (15u)
#define MFT_SWOCTRL_CH7OCV_WIDTH        (1u)
#define MFT_SWOCTRL_CH6OCV_MASK         (0x4000u)
#define MFT_SWOCTRL_CH6OCV_SHIFT        (14u)
#define MFT_SWOCTRL_CH6OCV_WIDTH        (1u)
#define MFT_SWOCTRL_CH5OCV_MASK         (0x2000u)
#define MFT_SWOCTRL_CH5OCV_SHIFT        (13u)
#define MFT_SWOCTRL_CH5OCV_WIDTH        (1u)
#define MFT_SWOCTRL_CH4OCV_MASK         (0x1000u)
#define MFT_SWOCTRL_CH4OCV_SHIFT        (12u)
#define MFT_SWOCTRL_CH4OCV_WIDTH        (1u)
#define MFT_SWOCTRL_CH3OCV_MASK         (0x800u)
#define MFT_SWOCTRL_CH3OCV_SHIFT        (11u)
#define MFT_SWOCTRL_CH3OCV_WIDTH        (1u)
#define MFT_SWOCTRL_CH2OCV_MASK         (0x400u)
#define MFT_SWOCTRL_CH2OCV_SHIFT        (10u)
#define MFT_SWOCTRL_CH2OCV_WIDTH        (1u)
#define MFT_SWOCTRL_CH1OCV_MASK         (0x200u)
#define MFT_SWOCTRL_CH1OCV_SHIFT        (9u)
#define MFT_SWOCTRL_CH1OCV_WIDTH        (1u)
#define MFT_SWOCTRL_CH0OCV_MASK         (0x100u)
#define MFT_SWOCTRL_CH0OCV_SHIFT        (8u)
#define MFT_SWOCTRL_CH0OCV_WIDTH        (1u)
#define MFT_SWOCTRL_CH7OC_MASK          (0x80u)
#define MFT_SWOCTRL_CH7OC_SHIFT         (7u)
#define MFT_SWOCTRL_CH7OC_WIDTH         (1u)
#define MFT_SWOCTRL_CH6OC_MASK          (0x40u)
#define MFT_SWOCTRL_CH6OC_SHIFT         (6u)
#define MFT_SWOCTRL_CH6OC_WIDTH         (1u)
#define MFT_SWOCTRL_CH5OC_MASK          (0x20u)
#define MFT_SWOCTRL_CH5OC_SHIFT         (5u)
#define MFT_SWOCTRL_CH5OC_WIDTH         (1u)
#define MFT_SWOCTRL_CH4OC_MASK          (0x10u)
#define MFT_SWOCTRL_CH4OC_SHIFT         (4u)
#define MFT_SWOCTRL_CH4OC_WIDTH         (1u)
#define MFT_SWOCTRL_CH3OC_MASK          (0x08u)
#define MFT_SWOCTRL_CH3OC_SHIFT         (3u)
#define MFT_SWOCTRL_CH3OC_WIDTH         (1u)
#define MFT_SWOCTRL_CH2OC_MASK          (0x04u)
#define MFT_SWOCTRL_CH2OC_SHIFT         (2u)
#define MFT_SWOCTRL_CH2OC_WIDTH         (1u)
#define MFT_SWOCTRL_CH1OC_MASK          (0x02u)
#define MFT_SWOCTRL_CH1OC_SHIFT         (1u)
#define MFT_SWOCTRL_CH1OC_WIDTH         (1u)
#define MFT_SWOCTRL_CH0OC_MASK          (0x01u)
#define MFT_SWOCTRL_CH0OC_SHIFT         (0u)
#define MFT_SWOCTRL_CH0OC_WIDTH         (1u)

/* PWMLOAD Bit Fields */
#define MFT_PWMLOAD_GLDOK_MASK          (0x800u)
#define MFT_PWMLOAD_GLDOK_SHIFT         (11u)
#define MFT_PWMLOAD_GLDOK_WIDTH         (1u)
#define MFT_PWMLOAD_GLEN_MASK           (0x400u)
#define MFT_PWMLOAD_GLEN_SHIFT          (10u)
#define MFT_PWMLOAD_GLEN_WIDTH          (1u)
#define MFT_PWMLOAD_LDOK_MASK           (0x200u)
#define MFT_PWMLOAD_LDOK_SHIFT          (9u)
#define MFT_PWMLOAD_LDOK_WIDTH          (1u)
#define MFT_PWMLOAD_HCSEL_MASK          (0x100u)
#define MFT_PWMLOAD_HCSEL_SHIFT         (8u)
#define MFT_PWMLOAD_HCSEL_WIDTH         (1u)
#define MFT_PWMLOAD_CH7SEL_MASK         (0x80u)
#define MFT_PWMLOAD_CH7SEL_SHIFT        (7u)
#define MFT_PWMLOAD_CH7SEL_WIDTH        (1u)
#define MFT_PWMLOAD_CH6SEL_MASK         (0x40u)
#define MFT_PWMLOAD_CH6SEL_SHIFT        (6u)
#define MFT_PWMLOAD_CH6SEL_WIDTH        (1u)
#define MFT_PWMLOAD_CH5SEL_MASK         (0x20u)
#define MFT_PWMLOAD_CH5SEL_SHIFT        (5u)
#define MFT_PWMLOAD_CH5SEL_WIDTH        (1u)
#define MFT_PWMLOAD_CH4SEL_MASK         (0x10u)
#define MFT_PWMLOAD_CH4SEL_SHIFT        (4u)
#define MFT_PWMLOAD_CH4SEL_WIDTH        (1u)
#define MFT_PWMLOAD_CH3SEL_MASK         (0x08u)
#define MFT_PWMLOAD_CH3SEL_SHIFT        (3u)
#define MFT_PWMLOAD_CH3SEL_WIDTH        (1u)
#define MFT_PWMLOAD_CH2SEL_MASK         (0x04u)
#define MFT_PWMLOAD_CH2SEL_SHIFT        (2u)
#define MFT_PWMLOAD_CH2SEL_WIDTH        (1u)
#define MFT_PWMLOAD_CH1SEL_MASK         (0x02u)
#define MFT_PWMLOAD_CH1SEL_SHIFT        (1u)
#define MFT_PWMLOAD_CH1SEL_WIDTH        (1u)
#define MFT_PWMLOAD_CH0SEL_MASK         (0x01u)
#define MFT_PWMLOAD_CH0SEL_SHIFT        (0u)
#define MFT_PWMLOAD_CH0SEL_WIDTH        (1u)

/* HCR Bit Fields */
#define MFT_HCR_HCVAL_MASK              (0xFFFFu)
#define MFT_HCR_HCVAL_SHIFT             (0u)
#define MFT_HCR_HCVAL_WIDTH             (16u)

/* PAIR_DEADTIME Bit Fields */
#define MFT_PAIR_DEADTIME_DTVALEX_MASK  (0xF0000u)
#define MFT_PAIR_DEADTIME_DTVALEX_SHIFT (16u)
#define MFT_PAIR_DEADTIME_DTVALEX_WIDTH (4u)
#define MFT_PAIR_DEADTIME_DTPS_MASK     (0xC0u)
#define MFT_PAIR_DEADTIME_DTPS_SHIFT    (6u)
#define MFT_PAIR_DEADTIME_DTPS_WIDTH    (2u)
#define MFT_PAIR_DEADTIME_DTVAL_MASK    (0x3Fu)
#define MFT_PAIR_DEADTIME_DTVAL_SHIFT   (0u)
#define MFT_PAIR_DEADTIME_DTVAL_WIDTH   (6u)

/* MOD_MIRROR Bit Fields */
#define MFT_MOD_MIRROR_MOD_M_MASK       (0xFFFF0000u)
#define MFT_MOD_MIRROR_MOD_M_SHIFT      (16u)
#define MFT_MOD_MIRROR_MOD_M_WIDTH      (16u)
#define MFT_MOD_MIRROR_FRACMOD_M_MASK   (0xF800u)
#define MFT_MOD_MIRROR_FRACMOD_M_SHIFT  (11u)
#define MFT_MOD_MIRROR_FRACMOD_M_WIDTH  (5u)

/* CV_MIRROR Bit Fields */
#define MFT_CV_MIRROR_VAL_M_MASK        (0xFFFF0000u)
#define MFT_CV_MIRROR_VAL_M_SHIFT       (16u)
#define MFT_CV_MIRROR_VAL_M_WIDTH       (16u)
#define MFT_CV_MIRROR_FRACVAL_MASK      (0xF800u)
#define MFT_CV_MIRROR_FRACVAL_SHIFT     (11u)
#define MFT_CV_MIRROR_FRACVAL_WIDTH     (5u)

/* SIM_OBE Bit Fields */
#define MFT_SIM_OBE_OBE_MASK            (0x01u)
#define MFT_SIM_OBE_OBE_SHIFT           (0u)
#define MFT_SIM_OBE_OBE_WIDTH           (1u)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/
typedef struct _MftRegType_
{
    volatile uint32_t SC;     /*!< Status And Control, offset: 0x00 */
    volatile uint32_t CNT;    /*!< Counter, offset: 0x04 */
    volatile uint32_t MODULO; /*!< Modulo, offset: 0x08 */
    struct
    {
        volatile uint32_t CSC;  /*!< Channel Status And Control */
        volatile uint32_t CV;   /*!< Channel Value */
    } CH[MFT_CHANNEL_NUM];      /*!< channels, offset: 0x0C */
    volatile uint32_t CNTIN;    /*!< Counter Initial Value, offset: 0x4C */
    volatile uint32_t STATUS;   /*!< Capture And Compare Status, offset: 0x50 */
    volatile uint32_t MODE;     /*!< Features Mode Selection, offset: 0x54 */
    volatile uint32_t SYNC;     /*!< Synchronization, offset: 0x58 */
    volatile uint32_t OUTINIT;  /*!< Initial State For Channels Output, offset: 0x5C */
    volatile uint32_t OUTMASK;  /*!< Output Mask, offset: 0x60 */
    volatile uint32_t COMBINE;  /*!< Function For Linked Channels, offset: 0x64 */
    volatile uint32_t DEADTIME; /*!< Deadtime Configuration, offset: 0x68 */
    volatile uint32_t EXTTRIG;  /*!< MFT External Trigger, offset: 0x6C */
    volatile uint32_t POL;      /*!< Channels Polarity, offset: 0x70 */
    volatile uint32_t FMS;      /*!< Fault Mode Status, offset: 0x74 */
    volatile uint32_t FILTER;   /*!< Input Capture Filter Control, offset: 0x78 */
    volatile uint32_t FLTCTRL;  /*!< Fault Control, offset: 0x7C */
    volatile uint32_t QDCTRL;   /*!< Quadrature Decoder Control And Status, offset: 0x80 */
    volatile uint32_t CONF;     /*!< Configuration, offset: 0x84 */
    volatile uint32_t FLTPOL;   /*!< MFT Fault Input Polarity, offset: 0x88 */
    volatile uint32_t SYNCONF;  /*!< Synchronization Configuration, offset: 0x8C */
    volatile uint32_t INVCTRL;  /*!< MFT Inverting Control, offset: 0x90 */
    volatile uint32_t SWOCTRL;  /*!< MFT Software Output Control, offset: 0x94 */
    volatile uint32_t PWMLOAD;  /*!< MFT PWM Load, offset: 0x98 */
    volatile uint32_t HCR;      /*!< Half Cycle Register, offset: 0x9C */
    struct
    {
        volatile uint32_t DEADTIME; /*!< Pair Deadtime Configuration */
    } PAIR[MFT_DEADTIME_PAIR];      /*!< Pairs, offset: 0xA0 */
    volatile uint32_t MOD_MIRROR;   /*!< Mirror of Modulo Value, offset: 0xB0 */
    struct
    {
        volatile uint32_t CV;      /*!< Mirror of Channel Match Value */
    } MIRROR[MFT_CHANNEL_NUM];     /*!< Mirror registers, offset: 0xB4 */
    uint32_t          RESERVED[1]; /*!< Reserverd block, offset: 0xD4 */
    volatile uint32_t SIM_OBE;     /*!< SIM Output Enable, offset: 0xD8 */
} MftRegType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Gets the Filter Prescaler
 *
 * This function gets the current Filter Prescaler.
 * The bits FLTPS selects the clock prescaler used in the MFT filters:
 * - channel input filters
 * - fault inputs filters
 * - quadrature decoder phase A and B inputs filters
 * Writing to the bits FLTPS has immediate effect.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Filter Prescaler
 *         - 0000b : Divide by 1
 *         - 0001b : Divide by 2
 *         - 0010b : Divide by 3
 *         - 0011b : Divide by 4
 *         - 0100b : Divide by 5
 *         - 0101b : Divide by 6
 *         - 0110b : Divide by 7
 *         - 0111b : Divide by 8
 *         - 1000b : Divide by 9
 *         - 1001b : Divide by 10
 *         - 1010b : Divide by 11
 *         - 1011b : Divide by 12
 *         - 1100b : Divide by 13
 *         - 1101b : Divide by 14
 *         - 1110b : Divide by 15
 *         - 1111b : Divide by 16
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetScFltPs(const MftRegType *obj)
{
    return ((obj->SC & MFT_SC_FLTPS_MASK) >> MFT_SC_FLTPS_SHIFT);
}

/*! \brief Sets the Filter Prescaler
 *
 * This function sets the Filter Prescaler.
 * The bits FLTPS selects the clock prescaler used in the MFT filters:
 * - channel input filters
 * - fault inputs filters
 * - quadrature decoder phase A and B inputs filters
 * Writing to the bits FLTPS has immediate effect.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Filter Prescaler
 *                    - 0000b : Divide by 1
 *                    - 0001b : Divide by 2
 *                    - 0010b : Divide by 3
 *                    - 0011b : Divide by 4
 *                    - 0100b : Divide by 5
 *                    - 0101b : Divide by 6
 *                    - 0110b : Divide by 7
 *                    - 0111b : Divide by 8
 *                    - 1000b : Divide by 9
 *                    - 1001b : Divide by 10
 *                    - 1010b : Divide by 11
 *                    - 1011b : Divide by 12
 *                    - 1100b : Divide by 13
 *                    - 1101b : Divide by 14
 *                    - 1110b : Divide by 15
 *                    - 1111b : Divide by 16
 */
__attribute__((always_inline)) static inline void MftReg_SetScFltPs(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SC;

    tmp &= ~MFT_SC_FLTPS_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SC_FLTPS_SHIFT)) & MFT_SC_FLTPS_MASK);
    obj->SC = tmp;
}

/*! \brief Gets the Channel 7 PWM enable bit
 *
 * This function gets the current Channel 7 PWM enable bit.
 * This bit enables the PWM channel output. This bit should be set to 0 (output disabled) when an input mode is used.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 7 PWM enable bit
 *         - 0b : Channel output port is disabled.
 *         - 1b : Channel output port is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetScPwmEn7(const MftRegType *obj)
{
    return ((obj->SC & MFT_SC_PWMEN7_MASK) >> MFT_SC_PWMEN7_SHIFT);
}

/*! \brief Sets the Channel 7 PWM enable bit
 *
 * This function sets the Channel 7 PWM enable bit.
 * This bit enables the PWM channel output. This bit should be set to 0 (output disabled) when an input mode is used.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 7 PWM enable bit
 *                    - 0b : Channel output port is disabled.
 *                    - 1b : Channel output port is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetScPwmEn7(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SC;

    tmp &= ~MFT_SC_PWMEN7_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SC_PWMEN7_SHIFT)) & MFT_SC_PWMEN7_MASK);
    obj->SC = tmp;
}

/*! \brief Gets the Channel 6 PWM enable bit
 *
 * This function gets the current Channel 6 PWM enable bit.
 * This bit enables the PWM channel output. This bit should be set to 0 (output disabled) when an input mode is used.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 6 PWM enable bit
 *         - 0b : Channel output port is disabled.
 *         - 1b : Channel output port is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetScPwmEn6(const MftRegType *obj)
{
    return ((obj->SC & MFT_SC_PWMEN6_MASK) >> MFT_SC_PWMEN6_SHIFT);
}

/*! \brief Sets the Channel 6 PWM enable bit
 *
 * This function sets the Channel 6 PWM enable bit.
 * This bit enables the PWM channel output. This bit should be set to 0 (output disabled) when an input mode is used.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 6 PWM enable bit
 *                    - 0b : Channel output port is disabled.
 *                    - 1b : Channel output port is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetScPwmEn6(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SC;

    tmp &= ~MFT_SC_PWMEN6_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SC_PWMEN6_SHIFT)) & MFT_SC_PWMEN6_MASK);
    obj->SC = tmp;
}

/*! \brief Gets the Channel 5 PWM enable bit
 *
 * This function gets the current Channel 5 PWM enable bit.
 * This bit enables the PWM channel output. This bit should be set to 0 (output disabled) when an input mode is used.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 5 PWM enable bit
 *         - 0b : Channel output port is disabled.
 *         - 1b : Channel output port is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetScPwmEn5(const MftRegType *obj)
{
    return ((obj->SC & MFT_SC_PWMEN5_MASK) >> MFT_SC_PWMEN5_SHIFT);
}

/*! \brief Sets the Channel 5 PWM enable bit
 *
 * This function sets the Channel 5 PWM enable bit.
 * This bit enables the PWM channel output. This bit should be set to 0 (output disabled) when an input mode is used.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 5 PWM enable bit
 *                    - 0b : Channel output port is disabled.
 *                    - 1b : Channel output port is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetScPwmEn5(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SC;

    tmp &= ~MFT_SC_PWMEN5_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SC_PWMEN5_SHIFT)) & MFT_SC_PWMEN5_MASK);
    obj->SC = tmp;
}

/*! \brief Gets the Channel 4 PWM enable bit
 *
 * This function gets the current Channel 4 PWM enable bit.
 * This bit enables the PWM channel output. This bit should be set to 0 (output disabled) when an input mode is used.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 4 PWM enable bit
 *         - 0b : Channel output port is disabled.
 *         - 1b : Channel output port is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetScPwmEn4(const MftRegType *obj)
{
    return ((obj->SC & MFT_SC_PWMEN4_MASK) >> MFT_SC_PWMEN4_SHIFT);
}

/*! \brief Sets the Channel 4 PWM enable bit
 *
 * This function sets the Channel 4 PWM enable bit.
 * This bit enables the PWM channel output. This bit should be set to 0 (output disabled) when an input mode is used.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 4 PWM enable bit
 *                    - 0b : Channel output port is disabled.
 *                    - 1b : Channel output port is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetScPwmEn4(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SC;

    tmp &= ~MFT_SC_PWMEN4_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SC_PWMEN4_SHIFT)) & MFT_SC_PWMEN4_MASK);
    obj->SC = tmp;
}

/*! \brief Gets the Channel 3 PWM enable bit
 *
 * This function gets the current Channel 3 PWM enable bit.
 * This bit enables the PWM channel output. This bit should be set to 0 (output disabled) when an input mode is used.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 3 PWM enable bit
 *         - 0b : Channel output port is disabled.
 *         - 1b : Channel output port is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetScPwmEn3(const MftRegType *obj)
{
    return ((obj->SC & MFT_SC_PWMEN3_MASK) >> MFT_SC_PWMEN3_SHIFT);
}

/*! \brief Sets the Channel 3 PWM enable bit
 *
 * This function sets the Channel 3 PWM enable bit.
 * This bit enables the PWM channel output. This bit should be set to 0 (output disabled) when an input mode is used.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 3 PWM enable bit
 *                    - 0b : Channel output port is disabled.
 *                    - 1b : Channel output port is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetScPwmEn3(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SC;

    tmp &= ~MFT_SC_PWMEN3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SC_PWMEN3_SHIFT)) & MFT_SC_PWMEN3_MASK);
    obj->SC = tmp;
}

/*! \brief Gets the Channel 2 PWM enable bit
 *
 * This function gets the current Channel 2 PWM enable bit.
 * This bit enables the PWM channel output. This bit should be set to 0 (output disabled) when an input mode is used.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 2 PWM enable bit
 *         - 0b : Channel output port is disabled.
 *         - 1b : Channel output port is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetScPwmEn2(const MftRegType *obj)
{
    return ((obj->SC & MFT_SC_PWMEN2_MASK) >> MFT_SC_PWMEN2_SHIFT);
}

/*! \brief Sets the Channel 2 PWM enable bit
 *
 * This function sets the Channel 2 PWM enable bit.
 * This bit enables the PWM channel output. This bit should be set to 0 (output disabled) when an input mode is used.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 2 PWM enable bit
 *                    - 0b : Channel output port is disabled.
 *                    - 1b : Channel output port is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetScPwmEn2(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SC;

    tmp &= ~MFT_SC_PWMEN2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SC_PWMEN2_SHIFT)) & MFT_SC_PWMEN2_MASK);
    obj->SC = tmp;
}

/*! \brief Gets the Channel 1 PWM enable bit
 *
 * This function gets the current Channel 1 PWM enable bit.
 * This bit enables the PWM channel output. This bit should be set to 0 (output disabled) when an input mode is used.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 1 PWM enable bit
 *         - 0b : Channel output port is disabled.
 *         - 1b : Channel output port is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetScPwmEn1(const MftRegType *obj)
{
    return ((obj->SC & MFT_SC_PWMEN1_MASK) >> MFT_SC_PWMEN1_SHIFT);
}

/*! \brief Sets the Channel 1 PWM enable bit
 *
 * This function sets the Channel 1 PWM enable bit.
 * This bit enables the PWM channel output. This bit should be set to 0 (output disabled) when an input mode is used.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 1 PWM enable bit
 *                    - 0b : Channel output port is disabled.
 *                    - 1b : Channel output port is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetScPwmEn1(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SC;

    tmp &= ~MFT_SC_PWMEN1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SC_PWMEN1_SHIFT)) & MFT_SC_PWMEN1_MASK);
    obj->SC = tmp;
}

/*! \brief Gets the Channel 0 PWM enable bit
 *
 * This function gets the current Channel 0 PWM enable bit.
 * This bit enables the PWM channel output. This bit should be set to 0 (output disabled) when an input mode is used.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 0 PWM enable bit
 *         - 0b : Channel output port is disabled.
 *         - 1b : Channel output port is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetScPwmEn0(const MftRegType *obj)
{
    return ((obj->SC & MFT_SC_PWMEN0_MASK) >> MFT_SC_PWMEN0_SHIFT);
}

/*! \brief Sets the Channel 0 PWM enable bit
 *
 * This function sets the Channel 0 PWM enable bit.
 * This bit enables the PWM channel output. This bit should be set to 0 (output disabled) when an input mode is used.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 0 PWM enable bit
 *                    - 0b : Channel output port is disabled.
 *                    - 1b : Channel output port is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetScPwmEn0(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SC;

    tmp &= ~MFT_SC_PWMEN0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SC_PWMEN0_SHIFT)) & MFT_SC_PWMEN0_MASK);
    obj->SC = tmp;
}

/*! \brief Gets the Timer Overflow Flag
 *
 * This function gets the current Timer Overflow Flag.
 * Set by hardware when the MFT counter passes the value in the MOD register. The TOF bit is cleared by
 * reading the SC register while TOF is set and then writing a 0 to TOF bit. Writing a 1 to TOF has no effect.
 * If another MFT overflow occurs between the read and write operations, the write operation has no effect;
 * therefore, TOF remains set indicating an overflow has occurred. In this case, a TOF interrupt request is
 * not lost due to the clearing sequence for a previous TOF.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Timer Overflow Flag
 *         - 0b : MFT counter has not overflowed.
 *         - 1b : MFT counter has overflowed.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetScTof(const MftRegType *obj)
{
    return ((obj->SC & MFT_SC_TOF_MASK) >> MFT_SC_TOF_SHIFT);
}

/*! \brief Sets the Timer Overflow Flag
 *
 * This function sets the Timer Overflow Flag.
 * Set by hardware when the MFT counter passes the value in the MOD register. The TOF bit is cleared by
 * reading the SC register while TOF is set and then writing a 0 to TOF bit. Writing a 1 to TOF has no effect.
 * If another MFT overflow occurs between the read and write operations, the write operation has no effect;
 * therefore, TOF remains set indicating an overflow has occurred. In this case, a TOF interrupt request is
 * not lost due to the clearing sequence for a previous TOF.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Timer Overflow Flag
 *                    - 0b : clear the flag
 *                    - 1b : No effect
 */
__attribute__((always_inline)) static inline void MftReg_SetScTof(MftRegType *obj, uint8_t value)
{
    /* Write 1 has no effect */
    if(value != 0)
    {
        return;
    }

    uint32_t tmp = obj->SC;

    tmp &= ~MFT_SC_TOF_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SC_TOF_SHIFT)) & MFT_SC_TOF_MASK);
    obj->SC = tmp;
    /* Read back to avoid problem */
    (void)obj->SC;
}

/*! \brief Gets the Timer Overflow Interrupt Enable
 *
 * This function gets the current Timer Overflow Interrupt Enable.
 * Enables MFT overflow interrupts.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Timer Overflow Interrupt Enable
 *         - 0b : Disable TOF interrupts. Use software polling.
 *         - 1b : Enable TOF interrupts. An interrupt is generated when TOF equals one.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetScToie(const MftRegType *obj)
{
    return ((obj->SC & MFT_SC_TOIE_MASK) >> MFT_SC_TOIE_SHIFT);
}

/*! \brief Sets the Timer Overflow Interrupt Enable
 *
 * This function sets the Timer Overflow Interrupt Enable.
 * Enables MFT overflow interrupts.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Timer Overflow Interrupt Enable
 *                    - 0b : Disable TOF interrupts. Use software polling.
 *                    - 1b : Enable TOF interrupts. An interrupt is generated when TOF equals one.
 */
__attribute__((always_inline)) static inline void MftReg_SetScToie(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SC;

    tmp &= ~MFT_SC_TOIE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SC_TOIE_SHIFT)) & MFT_SC_TOIE_MASK);
    obj->SC = tmp;
}

/*! \brief Gets the Reload Flag
 *
 * This function gets the current Reload Flag.
 * The RF bit is set at each selected reload point. See Reload Points.
 * The RF bit is cleared by reading the SC register while RF is set and then writing a 0 to RF bit. Writing 1 to
 * RF has no effect. If another selected reload point happens between the read and write operations, the
 * write operation has no effect; therefore, RF remains set.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Reload Flag
 *         - 0b : A selected reload point did not happen
 *         - 1b : A selected reload point happened
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetScRf(const MftRegType *obj)
{
    return ((obj->SC & MFT_SC_RF_MASK) >> MFT_SC_RF_SHIFT);
}

/*! \brief Sets the Reload Flag
 *
 * This function sets the Reload Flag.
 * The RF bit is set at each selected reload point. See Reload Points.
 * The RF bit is cleared by reading the SC register while RF is set and then writing a 0 to RF bit. Writing 1 to
 * RF has no effect. If another selected reload point happens between the read and write operations, the
 * write operation has no effect; therefore, RF remains set.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Reload Flag
 *                    - 0b : clear the flag
 *                    - 1b : no effect
 */
__attribute__((always_inline)) static inline void MftReg_SetScRf(MftRegType *obj, uint8_t value)
{
    /* Write 1 has no effect */
    if(value != 0)
    {
        return;
    }

    uint32_t tmp = obj->SC;

    tmp &= ~MFT_SC_RF_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SC_RF_SHIFT)) & MFT_SC_RF_MASK);
    obj->SC = tmp;
    /* Read back to avoid problem */
    (void)obj->SC;
}

/*! \brief Gets the Reload Point Interrupt Enable
 *
 * This function gets the current Reload Point Interrupt Enable.
 * Enables the reload point interrupt.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Reload Point Interrupt Enable
 *         - 0b : Reload point interrupt is disabled.
 *         - 1b : Reload point interrupt is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetScRie(const MftRegType *obj)
{
    return ((obj->SC & MFT_SC_RIE_MASK) >> MFT_SC_RIE_SHIFT);
}

/*! \brief Sets the Reload Point Interrupt Enable
 *
 * This function sets the Reload Point Interrupt Enable.
 * Enables the reload point interrupt.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Reload Point Interrupt Enable
 *                    - 0b : Reload point interrupt is disabled.
 *                    - 1b : Reload point interrupt is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetScRie(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SC;

    tmp &= ~MFT_SC_RIE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SC_RIE_SHIFT)) & MFT_SC_RIE_MASK);
    obj->SC = tmp;
}

/*! \brief Gets the Center-Aligned PWM Select
 *
 * This function gets the current Center-Aligned PWM Select.
 * Selects CPWM mode. This mode configures the MFT to operate in Up-Down Counting mode.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Center-Aligned PWM Select
 *         - 0b : MFT counter operates in Up Counting mode.
 *         - 1b : MFT counter operates in Up-Down Counting mode.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetScCPwms(const MftRegType *obj)
{
    return ((obj->SC & MFT_SC_CPWMS_MASK) >> MFT_SC_CPWMS_SHIFT);
}

/*! \brief Sets the Center-Aligned PWM Select
 *
 * This function sets the Center-Aligned PWM Select.
 * Selects CPWM mode. This mode configures the MFT to operate in Up-Down Counting mode.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Center-Aligned PWM Select
 *                    - 0b : MFT counter operates in Up Counting mode.
 *                    - 1b : MFT counter operates in Up-Down Counting mode.
 */
__attribute__((always_inline)) static inline void MftReg_SetScCPwms(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SC;

    tmp &= ~MFT_SC_CPWMS_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SC_CPWMS_SHIFT)) & MFT_SC_CPWMS_MASK);
    obj->SC = tmp;
}

/*! \brief Gets the Clock Source Selection
 *
 * This function gets the current Clock Source Selection.
 * Selects one of the three MFT counter clock sources.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Clock Source Selection
 *         - 00b : No clock selected. This in effect disables the MFT counter.
 *         - 01b : MFT input clock
 *         - 10b : Fixed frequency
 *         - 11b : External clock
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetScClks(const MftRegType *obj)
{
    return ((obj->SC & MFT_SC_CLKS_MASK) >> MFT_SC_CLKS_SHIFT);
}

/*! \brief Sets the Clock Source Selection
 *
 * This function sets the Clock Source Selection.
 * Selects one of the three MFT counter clock sources.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Clock Source Selection
 *                    - 00b : No clock selected. This in effect disables the MFT counter.
 *                    - 01b : MFT input clock
 *                    - 10b : Fixed frequency
 *                    - 11b : External clock
 */
__attribute__((always_inline)) static inline void MftReg_SetScClks(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SC;

    tmp &= ~MFT_SC_CLKS_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SC_CLKS_SHIFT)) & MFT_SC_CLKS_MASK);
    obj->SC = tmp;
}

/*! \brief Gets the Prescale Factor Selection
 *
 * This function gets the current Prescale Factor Selection.
 * Selects one of 8 division factors for the clock source selected by CLKS. The new prescaler factor affects
 * the clock source on the next MFT input clock cycle after the new value is updated into the register bits.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Prescale Factor Selection
 *         - 000b : Divide by 1
 *         - 001b : Divide by 2
 *         - 010b : Divide by 4
 *         - 011b : Divide by 8
 *         - 100b : Divide by 16
 *         - 101b : Divide by 32
 *         - 110b : Divide by 64
 *         - 111b : Divide by 128
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetScPs(const MftRegType *obj)
{
    return ((obj->SC & MFT_SC_PS_MASK) >> MFT_SC_PS_SHIFT);
}

/*! \brief Sets the Prescale Factor Selection
 *
 * This function sets the Prescale Factor Selection.
 * Selects one of 8 division factors for the clock source selected by CLKS. The new prescaler factor affects
 * the clock source on the next MFT input clock cycle after the new value is updated into the register bits.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Prescale Factor Selection
 *                    - 000b : Divide by 1
 *                    - 001b : Divide by 2
 *                    - 010b : Divide by 4
 *                    - 011b : Divide by 8
 *                    - 100b : Divide by 16
 *                    - 101b : Divide by 32
 *                    - 110b : Divide by 64
 *                    - 111b : Divide by 128
 */
__attribute__((always_inline)) static inline void MftReg_SetScPs(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SC;

    tmp &= ~MFT_SC_PS_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SC_PS_SHIFT)) & MFT_SC_PS_MASK);
    obj->SC = tmp;
}

/*! \brief Gets the Counter Value
 *
 * This function gets the current Counter Value.
 * The CNT register contains the MFT counter value.
 * Reset clears the CNT register. Writing any value to COUNT updates the counter with its initial value, CNTIN
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Counter Value
 */
__attribute__((always_inline)) static inline uint16_t MftReg_GetCntCount(const MftRegType *obj)
{
    return ((obj->CNT & MFT_CNT_COUNT_MASK) >> MFT_CNT_COUNT_SHIFT);
}

/*! \brief Sets the Counter Value
 *
 * This function sets the current Counter Value.
 * The CNT register contains the MFT counter value.
 * Reset clears the CNT register. Writing any value to COUNT updates the counter with its initial value, CNTIN
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : Counter Value
 */
__attribute__((always_inline)) static inline void MftReg_SetCntCount(MftRegType *obj, uint16_t value)
{
    uint32_t tmp = obj->CNT;

    tmp &= ~MFT_CNT_COUNT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_CNT_COUNT_SHIFT)) & MFT_CNT_COUNT_MASK);
    obj->CNT = tmp;
}

/*! \brief Gets the Modulo Value
 *
 * This function gets the current Modulo Value.
 * Writes to the MOD register are done on its write buffer.
 * The MOD register is updated with its write buffer value according to Registers updated from write buffers.
 * If MFTEN = 0, a write to SC register resets manually this write coherency mechanism
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Modulo Value
 */
__attribute__((always_inline)) static inline uint16_t MftReg_GetModuloMod(const MftRegType *obj)
{
    return ((obj->MODULO & MFT_MODULO_MOD_MASK) >> MFT_MODULO_MOD_SHIFT);
}

/*! \brief Sets the Modulo Value
 *
 * This function sets the Modulo Value.
 * Writes to the MOD register are done on its write buffer.
 * The MOD register is updated with its write buffer value according to Registers updated from write buffers.
 * If MFTEN = 0, a write to SC register resets manually this write coherency mechanism
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Modulo Value
 */
__attribute__((always_inline)) static inline void MftReg_SetModuloMod(MftRegType *obj, uint16_t value)
{
    uint32_t tmp = obj->MODULO;

    tmp &= ~MFT_MODULO_MOD_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_MODULO_MOD_SHIFT)) & MFT_MODULO_MOD_MASK);
    obj->MODULO = tmp;
}

/*! \brief Gets the Channel (n) Output Value
 *
 * This function gets the current Channel (n) Output Value.
 * The CHOV bit has the final value of the channel (n) output.
 *
 * \note The CHOV bit should be ignored when the channel (n) is not in an output mode.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] channel : the channel index
 * \return Channel (n) Output Value
 *         - 0b : The channel (n) output is zero.
 *         - 1b : The channel (n) output is one.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCscChov(const MftRegType *obj, uint8_t channel)
{
    return ((obj->CH[channel].CSC & MFT_CSC_CHOV_MASK) >> MFT_CSC_CHOV_SHIFT);
}

/*! \brief Gets the Channel (n) Input State
 *
 * This function gets the current Channel (n) Input State.
 * The CHIS bit has the value of the channel (n) input after the double-sampling or the filtering (if the
 * channel (n) filter is enabled) both them are inside the MFT.
 *
 * \note The CHIS bit should be ignored when the channel (n) is not in an input mode.
 *
 * \note When the pair channels is on dual edge mode, the channel (n+1) CHIS bit is the channel (n+1)
 * input value and not the channel (n) input value (this signal is the input signal used by the dual
 * edge mode).
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] channel : the channel index
 * \return Channel (n) Input State
 *         - 0b : The channel (n) input is zero.
 *         - 1b : The channel (n) input is one.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCscChis(const MftRegType *obj, uint8_t channel)
{
    return ((obj->CH[channel].CSC & MFT_CSC_CHIS_MASK) >> MFT_CSC_CHIS_SHIFT);
}

/*! \brief Gets the Trigger mode control
 *
 * This function gets the current Trigger mode control.
 * This bit controls the trigger generation on MFT channel outputs. This mode is allowed only if when MFT
 * channel is configured to EPWM or CPWM modes. If a match in the channel occurs, a trigger pulse with
 * one MFT clock cycle width will be generated in the channel output. See Channel trigger output.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] channel : the channel index
 * \return Trigger mode control
 *         - 0b : Channel outputs will generate the normal PWM outputs without generating a pulse.
 *         - 1b : If a match in the channel occurs, a trigger generation on channel output will happen.
 *                The trigger pulse width has one MFT clock cycle.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCscTrigMode(const MftRegType *obj, uint8_t channel)
{
    return ((obj->CH[channel].CSC & MFT_CSC_TRIGMODE_MASK) >> MFT_CSC_TRIGMODE_SHIFT);
}

/*! \brief Sets the Trigger mode control
 *
 * This function sets the Trigger mode control.
 * This bit controls the trigger generation on MFT channel outputs. This mode is allowed only if when MFT
 * channel is configured to EPWM or CPWM modes. If a match in the channel occurs, a trigger pulse with
 * one MFT clock cycle width will be generated in the channel output. See Channel trigger output.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] channel : the channel index
 * \param[in] value : the value of Trigger mode control
 *                    - 0b : Channel outputs will generate the normal PWM outputs without generating a pulse.
 *                    - 1b : If a match in the channel occurs, a trigger generation on channel output will happen.
 *                           The trigger pulse width has one MFT clock cycle.
 */
__attribute__((always_inline)) static inline void MftReg_SetCscTrigMode(MftRegType *obj, uint8_t channel, uint8_t value)
{
    uint32_t tmp = obj->CH[channel].CSC;

    tmp &= ~MFT_CSC_TRIGMODE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_CSC_TRIGMODE_SHIFT)) & MFT_CSC_TRIGMODE_MASK);
    obj->CH[channel].CSC = tmp;
}

/*! \brief Gets the Channel (n) Flag
 *
 * This function gets the current Channel (n) Flag.
 * Set by hardware when an event occurs on the channel (n). CHF is cleared by reading the CnSC register
 * while CHF is set and then writing a 0 to the CHF bit. Writing a 1 to CHF has no effect.
 * If another event occurs between the read and write operations, the write operation has no effect;
 * therefore, CHF remains set indicating an event has occurred. In this case a CHF interrupt request is not
 * lost due to the clearing sequence for a previous CHF.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] channel : the channel index
 * \return Channel (n) Flag
 *         - 0b : No channel (n) event has occurred.
 *         - 1b : A channel (n) event has occurred.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCscChf(const MftRegType *obj, uint8_t channel)
{
    return ((obj->CH[channel].CSC & MFT_CSC_CHF_MASK) >> MFT_CSC_CHF_SHIFT);
}

/*! \brief Sets the Channel (n) Flag
 *
 * This function sets the Channel (n) Flag.
 * Set by hardware when an event occurs on the channel (n). CHF is cleared by reading the CnSC register
 * while CHF is set and then writing a 0 to the CHF bit. Writing a 1 to CHF has no effect.
 * If another event occurs between the read and write operations, the write operation has no effect;
 * therefore, CHF remains set indicating an event has occurred. In this case a CHF interrupt request is not
 * lost due to the clearing sequence for a previous CHF.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] channel : the channel index
 * \param[in] value : the value of Channel (n) Flag
 *                    - 0b : clear the flag
 *                    - 1b : no effect
 */
__attribute__((always_inline)) static inline void MftReg_SetCscChf(MftRegType *obj, uint8_t channel, uint8_t value)
{
    /* Write 1 has no effect */
    if(value != 0)
    {
        return;
    }

    uint32_t tmp = obj->CH[channel].CSC;

    tmp &= ~MFT_CSC_CHF_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_CSC_CHF_SHIFT)) & MFT_CSC_CHF_MASK);
    obj->CH[channel].CSC = tmp;
    /* Read back to avoid problem */
    (void)obj->CH[channel].CSC;
}

/*! \brief Gets the Channel (n) Interrupt Enable
 *
 * This function gets the current Channel (n) Interrupt Enable.
 * Enables channel (n) interrupt.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] channel : the channel index
 * \return Channel (n) Interrupt Enable
 *         - 0b : Disable channel (n) interrupt. Use software polling.
 *         - 1b : Enable channel (n) interrupt.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCscChie(const MftRegType *obj, uint8_t channel)
{
    return ((obj->CH[channel].CSC & MFT_CSC_CHIE_MASK) >> MFT_CSC_CHIE_SHIFT);
}

/*! \brief Sets the Channel (n) Interrupt Enable
 *
 * This function sets the Channel (n) Interrupt Enable.
 * Enables channel (n) interrupt.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] channel : the channel index
 * \param[in] value : the value of Channel (n) Interrupt Enable
 *                    - 0b : Disable channel (n) interrupt. Use software polling.
 *                    - 1b : Enable channel (n) interrupt.
 */
__attribute__((always_inline)) static inline void MftReg_SetCscChie(MftRegType *obj, uint8_t channel, uint8_t value)
{
    uint32_t tmp = obj->CH[channel].CSC;

    tmp &= ~MFT_CSC_CHIE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_CSC_CHIE_SHIFT)) & MFT_CSC_CHIE_MASK);
    obj->CH[channel].CSC = tmp;
}

/*! \brief Gets the Channel (n) Mode Select
 *
 * This function gets the current Channel (n) Mode Select.
 * Used on the selection of the channel (n) mode. See Channel Modes.
This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] channel : the channel index
 * \return Channel (n) Mode Select
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCscMsb(const MftRegType *obj, uint8_t channel)
{
    return ((obj->CH[channel].CSC & MFT_CSC_MSB_MASK) >> MFT_CSC_MSB_SHIFT);
}

/*! \brief Sets the Channel (n) Mode Select
 *
 * This function sets the Channel (n) Mode Select.
 * Used on the selection of the channel (n) mode. See Channel Modes.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] channel : the channel index
 * \param[in] value : the value of Channel (n) Mode Select
 */
__attribute__((always_inline)) static inline void MftReg_SetCscMsb(MftRegType *obj, uint8_t channel, uint8_t value)
{
    uint32_t tmp = obj->CH[channel].CSC;

    tmp &= ~MFT_CSC_MSB_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_CSC_MSB_SHIFT)) & MFT_CSC_MSB_MASK);
    obj->CH[channel].CSC = tmp;
}

/*! \brief Gets the Channel (n) Mode Select
 *
 * This function gets the current Channel (n) Mode Select.
 * Used on the selection of the channel (n) mode. See Channel Modes.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] channel : the channel index
 * \return Channel (n) Mode Select
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCscMsa(const MftRegType *obj, uint8_t channel)
{
    return ((obj->CH[channel].CSC & MFT_CSC_MSA_MASK) >> MFT_CSC_MSA_SHIFT);
}

/*! \brief Sets the Channel (n) Mode Select
 *
 * This function sets the Channel (n) Mode Select.
 * Used on the selection of the channel (n) mode. See Channel Modes.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] channel : the channel index
 * \param[in] value : the value of Channel (n) Mode Select
 */
__attribute__((always_inline)) static inline void MftReg_SetCscMsa(MftRegType *obj, uint8_t channel, uint8_t value)
{
    uint32_t tmp = obj->CH[channel].CSC;

    tmp &= ~MFT_CSC_MSA_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_CSC_MSA_SHIFT)) & MFT_CSC_MSA_MASK);
    obj->CH[channel].CSC = tmp;
}

/*! \brief Gets the Channel (n) Edge or Level Select
 *
 * This function gets the current Channel (n) Edge or Level Select.
 * Used on the selection of the channel (n) mode. See Channel Modes.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] channel : the channel index
 * \return Channel (n) Edge or Level Select
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCscElsb(const MftRegType *obj, uint8_t channel)
{
    return ((obj->CH[channel].CSC & MFT_CSC_ELSB_MASK) >> MFT_CSC_ELSB_SHIFT);
}

/*! \brief Sets the Channel (n) Edge or Level Select
 *
 * This function sets the Channel (n) Edge or Level Select.
 * Used on the selection of the channel (n) mode. See Channel Modes.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] channel : the channel index
 * \param[in] value : the value of Channel (n) Edge or Level Select
 */
__attribute__((always_inline)) static inline void MftReg_SetCscElsb(MftRegType *obj, uint8_t channel, uint8_t value)
{
    uint32_t tmp = obj->CH[channel].CSC;

    tmp &= ~MFT_CSC_ELSB_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_CSC_ELSB_SHIFT)) & MFT_CSC_ELSB_MASK);
    obj->CH[channel].CSC = tmp;
}

/*! \brief Gets the Channel (n) Edge or Level Select
 *
 * This function gets the current Channel (n) Edge or Level Select.
 * Used on the selection of the channel (n) mode. See Channel Modes.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] channel : the channel index
 * \return Channel (n) Edge or Level Select
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCscElsa(const MftRegType *obj, uint8_t channel)
{
    return ((obj->CH[channel].CSC & MFT_CSC_ELSA_MASK) >> MFT_CSC_ELSA_SHIFT);
}

/*! \brief Sets the Channel (n) Edge or Level Select
 *
 * This function sets the Channel (n) Edge or Level Select.
 * Used on the selection of the channel (n) mode. See Channel Modes.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] channel : the channel index
 * \param[in] value : the value of Channel (n) Edge or Level Select
 */
__attribute__((always_inline)) static inline void MftReg_SetCscElsa(MftRegType *obj, uint8_t channel, uint8_t value)
{
    uint32_t tmp = obj->CH[channel].CSC;

    tmp &= ~MFT_CSC_ELSA_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_CSC_ELSA_SHIFT)) & MFT_CSC_ELSA_MASK);
    obj->CH[channel].CSC = tmp;
}

/*! \brief Gets the MFT counter reset by the selected input capture event
 *
 * This function gets the current MFT counter reset by the selected input capture event.
 * MFT counter reset is driven by the selected event of the channel (n) in the Input Capture mode.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] channel : the channel index
 * \return MFT counter reset by the selected input capture event
 *         - 0b : MFT counter is not reset when the selected channel (n) input event is detected.
 *         - 1b : MFT counter is reset when the selected channel (n) input event is detected.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCscIcrst(const MftRegType *obj, uint8_t channel)
{
    return ((obj->CH[channel].CSC & MFT_CSC_ICRST_MASK) >> MFT_CSC_ICRST_SHIFT);
}

/*! \brief Sets the MFT counter reset by the selected input capture event
 *
 * This function sets the MFT counter reset by the selected input capture event.
 * MFT counter reset is driven by the selected event of the channel (n) in the Input Capture mode.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] channel : the channel index
 * \param[in] value : the value of MFT counter reset by the selected input capture event
 *                    - 0b : MFT counter is not reset when the selected channel (n) input event is detected.
 *                    - 1b : MFT counter is reset when the selected channel (n) input event is detected.
 */
__attribute__((always_inline)) static inline void MftReg_SetCscIcrst(MftRegType *obj, uint8_t channel, uint8_t value)
{
    uint32_t tmp = obj->CH[channel].CSC;

    tmp &= ~MFT_CSC_ICRST_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_CSC_ICRST_SHIFT)) & MFT_CSC_ICRST_MASK);
    obj->CH[channel].CSC = tmp;
}

/*! \brief Gets the DMA Enable
 *
 * This function gets the current DMA Enable.
 * Enables DMA transfers for the channel.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] channel : the channel index
 * \return DMA Enable
 *         - 0b : Disable DMA transfers.
 *         - 1b : Enable DMA transfers.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCscDma(const MftRegType *obj, uint8_t channel)
{
    return ((obj->CH[channel].CSC & MFT_CSC_DMA_MASK) >> MFT_CSC_DMA_SHIFT);
}

/*! \brief Sets the DMA Enable
 *
 * This function sets the DMA Enable.
 * Enables DMA transfers for the channel.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] channel : the channel index
 * \param[in] value : the value of DMA Enable
 *                    - 0b : Disable DMA transfers.
 *                    - 1b : Enable DMA transfers.
 */
__attribute__((always_inline)) static inline void MftReg_SetCscDma(MftRegType *obj, uint8_t channel, uint8_t value)
{
    uint32_t tmp = obj->CH[channel].CSC;

    tmp &= ~MFT_CSC_DMA_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_CSC_DMA_SHIFT)) & MFT_CSC_DMA_MASK);
    obj->CH[channel].CSC = tmp;
}

/*! \brief Gets the Channel Value
 *
 * This function gets the current Channel Value.
 * Captured MFT counter value of the input modes or the match value for the output modes
 * In Input Capture , Capture Test, and Dual Edge Capture modes, any write to a CnV register is ignored.
 * In output modes, writes to the CnV register are done on its write buffer
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] channel : the channel index
 * \return Channel Value
 */
__attribute__((always_inline)) static inline uint16_t MftReg_GetCvVal(const MftRegType *obj, uint8_t channel)
{
    return ((obj->CH[channel].CV & MFT_CV_VAL_MASK) >> MFT_CV_VAL_SHIFT);
}

/*! \brief Sets the Channel Value
 *
 * This function sets the current Channel Value.
 * Captured MFT counter value of the input modes or the match value for the output modes
 * In Input Capture , Capture Test, and Dual Edge Capture modes, any write to a CnV register is ignored.
 * In output modes, writes to the CnV register are done on its write buffer
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] channel : the channel index
 * \param[in] value : Channel Value
 */
__attribute__((always_inline)) static inline void MftReg_SetCvVal(MftRegType *obj, uint8_t channel, uint16_t value)
{
    uint32_t tmp = obj->CH[channel].CV;

    tmp &= ~MFT_CV_VAL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_CV_VAL_SHIFT)) & MFT_CV_VAL_MASK);
    obj->CH[channel].CV = tmp;
}

/*! \brief Gets the Initial Value Of The MFT Counter
 *
 * This function gets the current Initial Value Of The MFT Counter.
 * Writing to the CNTIN register latches the value into a buffer.
 * The CNTIN register is updated with the value of its write buffer according to Registers updated from write buffers
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Initial Value Of The MFT Counter
 */
__attribute__((always_inline)) static inline uint16_t MftReg_GetCntInCntInit(const MftRegType *obj)
{
    return ((obj->CNTIN & MFT_CNTIN_CNTINIT_MASK) >> MFT_CNTIN_CNTINIT_SHIFT);
}

/*! \brief Sets the Initial Value Of The MFT Counter
 *
 * This function sets the Initial Value Of The MFT Counter.
 * Writing to the CNTIN register latches the value into a buffer.
 * The CNTIN register is updated with the value of its write buffer according to Registers updated from write buffers
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Initial Value Of The MFT Counter
 */
__attribute__((always_inline)) static inline void MftReg_SetCntInCntInit(MftRegType *obj, uint16_t value)
{
    uint32_t tmp = obj->CNTIN;

    tmp &= ~MFT_CNTIN_CNTINIT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_CNTIN_CNTINIT_SHIFT)) & MFT_CNTIN_CNTINIT_MASK);
    obj->CNTIN = tmp;
}

/*! \brief Gets the Channel 7 Flag
 *
 * This function gets the current Channel 7 Flag.
 * See the register description.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 7 Flag
 *         - 0b : No channel event has occurred.
 *         - 1b : A channel event has occurred.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetStatusCh7F(const MftRegType *obj)
{
    return ((obj->STATUS & MFT_STATUS_CH7F_MASK) >> MFT_STATUS_CH7F_SHIFT);
}

/*! \brief Sets the Channel 7 Flag
 *
 * This function sets the Channel 7 Flag.
 * See the register description.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 7 Flag
 *                    - 0b : clear the flag
 *                    - 1b : no effect
 */
__attribute__((always_inline)) static inline void MftReg_SetStatusCh7F(MftRegType *obj, uint8_t value)
{
    /* Write 1 has no effect */
    if(value != 0)
    {
        return;
    }

    uint32_t tmp = obj->STATUS;

    tmp &= ~MFT_STATUS_CH7F_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_STATUS_CH7F_SHIFT)) & MFT_STATUS_CH7F_MASK);
    obj->STATUS = tmp;
    /* Read back to avoid problem */
    (void)obj->STATUS;
}

/*! \brief Gets the Channel 6 Flag
 *
 * This function gets the current Channel 6 Flag.
 * See the register description.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 6 Flag
 *         - 0b : No channel event has occurred.
 *         - 1b : A channel event has occurred.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetStatusCh6F(const MftRegType *obj)
{
    return ((obj->STATUS & MFT_STATUS_CH6F_MASK) >> MFT_STATUS_CH6F_SHIFT);
}

/*! \brief Sets the Channel 6 Flag
 *
 * This function sets the Channel 6 Flag.
 * See the register description.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 6 Flag
 *                    - 0b : clear the flag
 *                    - 1b : no effect
 */
__attribute__((always_inline)) static inline void MftReg_SetStatusCh6F(MftRegType *obj, uint8_t value)
{
    /* Write 1 has no effect */
    if(value != 0)
    {
        return;
    }

    uint32_t tmp = obj->STATUS;

    tmp &= ~MFT_STATUS_CH6F_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_STATUS_CH6F_SHIFT)) & MFT_STATUS_CH6F_MASK);
    obj->STATUS = tmp;
    /* Read back to avoid problem */
    (void)obj->STATUS;
}

/*! \brief Gets the Channel 5 Flag
 *
 * This function gets the current Channel 5 Flag.
 * See the register description.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 5 Flag
 *         - 0b : No channel event has occurred.
 *         - 1b : A channel event has occurred.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetStatusCh5F(const MftRegType *obj)
{
    return ((obj->STATUS & MFT_STATUS_CH5F_MASK) >> MFT_STATUS_CH5F_SHIFT);
}

/*! \brief Sets the Channel 5 Flag
 *
 * This function sets the Channel 5 Flag.
 * See the register description.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 5 Flag
 *                    - 0b : clear the flag
 *                    - 1b : no effect
 */
__attribute__((always_inline)) static inline void MftReg_SetStatusCh5F(MftRegType *obj, uint8_t value)
{
    /* Write 1 has no effect */
    if(value != 0)
    {
        return;
    }

    uint32_t tmp = obj->STATUS;

    tmp &= ~MFT_STATUS_CH5F_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_STATUS_CH5F_SHIFT)) & MFT_STATUS_CH5F_MASK);
    obj->STATUS = tmp;
    /* Read back to avoid problem */
    (void)obj->STATUS;
}

/*! \brief Gets the Channel 4 Flag
 *
 * This function gets the current Channel 4 Flag.
 * See the register description.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 4 Flag
 *         - 0b : No channel event has occurred.
 *         - 1b : A channel event has occurred.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetStatusCh4F(const MftRegType *obj)
{
    return ((obj->STATUS & MFT_STATUS_CH4F_MASK) >> MFT_STATUS_CH4F_SHIFT);
}

/*! \brief Sets the Channel 4 Flag
 *
 * This function sets the Channel 4 Flag.
 * See the register description.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 4 Flag
 *                    - 0b : clear the flag
 *                    - 1b : no effect
 */
__attribute__((always_inline)) static inline void MftReg_SetStatusCh4F(MftRegType *obj, uint8_t value)
{
    /* Write 1 has no effect */
    if(value != 0)
    {
        return;
    }

    uint32_t tmp = obj->STATUS;

    tmp &= ~MFT_STATUS_CH4F_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_STATUS_CH4F_SHIFT)) & MFT_STATUS_CH4F_MASK);
    obj->STATUS = tmp;
    /* Read back to avoid problem */
    (void)obj->STATUS;
}

/*! \brief Gets the Channel 3 Flag
 *
 * This function gets the current Channel 3 Flag.
 * See the register description.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 3 Flag
 *         - 0b : No channel event has occurred.
 *         - 1b : A channel event has occurred.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetStatusCh3F(const MftRegType *obj)
{
    return ((obj->STATUS & MFT_STATUS_CH3F_MASK) >> MFT_STATUS_CH3F_SHIFT);
}

/*! \brief Sets the Channel 3 Flag
 *
 * This function sets the Channel 3 Flag.
 * See the register description.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 3 Flag
 *                    - 0b : clear the flag
 *                    - 1b : no effect
 */
__attribute__((always_inline)) static inline void MftReg_SetStatusCh3F(MftRegType *obj, uint8_t value)
{
    /* Write 1 has no effect */
    if(value != 0)
    {
        return;
    }

    uint32_t tmp = obj->STATUS;

    tmp &= ~MFT_STATUS_CH3F_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_STATUS_CH3F_SHIFT)) & MFT_STATUS_CH3F_MASK);
    obj->STATUS = tmp;
    /* Read back to avoid problem */
    (void)obj->STATUS;
}

/*! \brief Gets the Channel 2 Flag
 *
 * This function gets the current Channel 2 Flag.
 * See the register description.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 2 Flag
 *         - 0b : No channel event has occurred.
 *         - 1b : A channel event has occurred.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetStatusCh2F(const MftRegType *obj)
{
    return ((obj->STATUS & MFT_STATUS_CH2F_MASK) >> MFT_STATUS_CH2F_SHIFT);
}

/*! \brief Sets the Channel 2 Flag
 *
 * This function sets the Channel 2 Flag.
 * See the register description.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 2 Flag
 *                    - 0b : clear the flag
 *                    - 1b : no effect
 */
__attribute__((always_inline)) static inline void MftReg_SetStatusCh2F(MftRegType *obj, uint8_t value)
{
    /* Write 1 has no effect */
    if(value != 0)
    {
        return;
    }

    uint32_t tmp = obj->STATUS;

    tmp &= ~MFT_STATUS_CH2F_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_STATUS_CH2F_SHIFT)) & MFT_STATUS_CH2F_MASK);
    obj->STATUS = tmp;
    /* Read back to avoid problem */
    (void)obj->STATUS;
}

/*! \brief Gets the Channel 1 Flag
 *
 * This function gets the current Channel 1 Flag.
 * See the register description.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 1 Flag
 *         - 0b : No channel event has occurred.
 *         - 1b : A channel event has occurred.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetStatusCh1F(const MftRegType *obj)
{
    return ((obj->STATUS & MFT_STATUS_CH1F_MASK) >> MFT_STATUS_CH1F_SHIFT);
}

/*! \brief Sets the Channel 1 Flag
 *
 * This function sets the Channel 1 Flag.
 * See the register description.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 1 Flag
 *                    - 0b : clear the flag
 *                    - 1b : no effect
 */
__attribute__((always_inline)) static inline void MftReg_SetStatusCh1F(MftRegType *obj, uint8_t value)
{
    /* Write 1 has no effect */
    if(value != 0)
    {
        return;
    }

    uint32_t tmp = obj->STATUS;

    tmp &= ~MFT_STATUS_CH1F_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_STATUS_CH1F_SHIFT)) & MFT_STATUS_CH1F_MASK);
    obj->STATUS = tmp;
    /* Read back to avoid problem */
    (void)obj->STATUS;
}

/*! \brief Gets the Channel 0 Flag
 *
 * This function gets the current Channel 0 Flag.
 * See the register description.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 0 Flag
 *         - 0b : No channel event has occurred.
 *         - 1b : A channel event has occurred.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetStatusCh0F(const MftRegType *obj)
{
    return ((obj->STATUS & MFT_STATUS_CH0F_MASK) >> MFT_STATUS_CH0F_SHIFT);
}

/*! \brief Sets the Channel 0 Flag
 *
 * This function sets the Channel 0 Flag.
 * See the register description.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 0 Flag
 *                    - 0b : clear the flag
 *                    - 1b : no effect
 */
__attribute__((always_inline)) static inline void MftReg_SetStatusCh0F(MftRegType *obj, uint8_t value)
{
    /* Write 1 has no effect */
    if(value != 0)
    {
        return;
    }

    uint32_t tmp = obj->STATUS;

    tmp &= ~MFT_STATUS_CH0F_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_STATUS_CH0F_SHIFT)) & MFT_STATUS_CH0F_MASK);
    obj->STATUS = tmp;
    /* Read back to avoid problem */
    (void)obj->STATUS;
}

/*! \brief Gets the Fault Interrupt Enable
 *
 * This function gets the current Fault Interrupt Enable.
 * Enables the generation of an interrupt when a fault is detected by MFT and the MFT fault control is enabled.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Fault Interrupt Enable
 *         - 0b : Fault control interrupt is disabled.
 *         - 1b : Fault control interrupt is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetModeFaultIE(const MftRegType *obj)
{
    return ((obj->MODE & MFT_MODE_FAULTIE_MASK) >> MFT_MODE_FAULTIE_SHIFT);
}

/*! \brief Sets the Fault Interrupt Enable
 *
 * This function sets the Fault Interrupt Enable.
 * Enables the generation of an interrupt when a fault is detected by MFT and the MFT fault control is enabled.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Fault Interrupt Enable
 *                    - 0b : Fault control interrupt is disabled.
 *                    - 1b : Fault control interrupt is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetModeFaultIE(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MODE;

    tmp &= ~MFT_MODE_FAULTIE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_MODE_FAULTIE_SHIFT)) & MFT_MODE_FAULTIE_MASK);
    obj->MODE = tmp;
}

/*! \brief Gets the Fault Control Mode
 *
 * This function gets the current Fault Control Mode.
 * Defines the MFT fault control mode.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Fault Control Mode
 *         - 00b : Fault control is disabled for all channels.
 *         - 01b : Fault control is enabled for even channels only (channels 0, 2, 4, and 6), and the selected mode is the manual fault clearing.
 *         - 10b : Fault control is enabled for all channels, and the selected mode is the manual fault clearing.
 *         - 11b : Fault control is enabled for all channels, and the selected mode is the automatic fault clearing.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetModeFaultM(const MftRegType *obj)
{
    return ((obj->MODE & MFT_MODE_FAULTM_MASK) >> MFT_MODE_FAULTM_SHIFT);
}

/*! \brief Sets the Fault Control Mode
 *
 * This function sets the Fault Control Mode.
 * Defines the MFT fault control mode.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Fault Control Mode
 *                    - 00b : Fault control is disabled for all channels.
 *                    - 01b : Fault control is enabled for even channels only (channels 0, 2, 4, and 6), and the selected mode is the manual fault clearing.
 *                    - 10b : Fault control is enabled for all channels, and the selected mode is the manual fault clearing.
 *                    - 11b : Fault control is enabled for all channels, and the selected mode is the automatic fault clearing.
 */
__attribute__((always_inline)) static inline void MftReg_SetModeFaultM(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MODE;

    tmp &= ~MFT_MODE_FAULTM_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_MODE_FAULTM_SHIFT)) & MFT_MODE_FAULTM_MASK);
    obj->MODE = tmp;
}

/*! \brief Gets the Capture Test Mode Enable
 *
 * This function gets the current Capture Test Mode Enable.
 * Enables the capture test mode.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Capture Test Mode Enable
 *         - 0b : Capture test mode is disabled.
 *         - 1b : Capture test mode is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetModeCapTest(const MftRegType *obj)
{
    return ((obj->MODE & MFT_MODE_CAPTEST_MASK) >> MFT_MODE_CAPTEST_SHIFT);
}

/*! \brief Sets the Capture Test Mode Enable
 *
 * This function sets the Capture Test Mode Enable.
 * Enables the capture test mode.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Capture Test Mode Enable
 *                    - 0b : Capture test mode is disabled.
 *                    - 1b : Capture test mode is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetModeCapTest(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MODE;

    tmp &= ~MFT_MODE_CAPTEST_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_MODE_CAPTEST_SHIFT)) & MFT_MODE_CAPTEST_MASK);
    obj->MODE = tmp;
}

/*! \brief Gets the PWM Synchronization Mode
 *
 * This function gets the current PWM Synchronization Mode.
 * Selects which triggers can be used by MOD, CnV, OUTMASK, and MFT counter synchronization.
 * The PWMSYNC bit configures the synchronization when SYNCMODE is 0.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return PWM Synchronization Mode
 *         - 0b : No restrictions. Software and hardware triggers can be used by
 *                MOD, CnV, OUTMASK, and MFT counter synchronization.
 *         - 1b : Software trigger can only be used by MOD and CnV synchronization,
 *                and hardware triggers can only be used by OUTMASK and MFT counter synchronization.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetModePwmSync(const MftRegType *obj)
{
    return ((obj->MODE & MFT_MODE_PWMSYNC_MASK) >> MFT_MODE_PWMSYNC_SHIFT);
}

/*! \brief Sets the PWM Synchronization Mode
 *
 * This function sets the PWM Synchronization Mode.
 * Selects which triggers can be used by MOD, CnV, OUTMASK, and MFT counter synchronization. The PWMSYNC bit configures the synchronization
 * when SYNCMODE is 0.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of PWM Synchronization Mode
 *                    - 0b : No restrictions. Software and hardware triggers can be used by
 *                           MOD, CnV, OUTMASK, and MFT counter synchronization.
 *                    - 1b : Software trigger can only be used by MOD and CnV synchronization,
 *                           and hardware triggers can only be used by OUTMASK and MFT counter synchronization.
 */
__attribute__((always_inline)) static inline void MftReg_SetModePwmSync(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MODE;

    tmp &= ~MFT_MODE_PWMSYNC_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_MODE_PWMSYNC_SHIFT)) & MFT_MODE_PWMSYNC_MASK);
    obj->MODE = tmp;
}

/*! \brief Gets the Write Protection Disable
 *
 * This function gets the current Write Protection Disable.
 * When write protection is enabled (WPDIS = 0), write protected bits cannot be written. When write
 * protection is disabled (WPDIS = 1), write protected bits can be written. The WPDIS bit is the negation of
 * the WPEN bit. WPDIS is cleared when 1 is written to WPEN. WPDIS is set when WPEN bit is read as a 1
 * and then 1 is written to WPDIS. Writing 0 to WPDIS has no effect.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Write Protection Disable
 *         - 0b : Write protection is enabled.
 *         - 1b : Write protection is disabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetModeWpDis(const MftRegType *obj)
{
    return ((obj->MODE & MFT_MODE_WPDIS_MASK) >> MFT_MODE_WPDIS_SHIFT);
}

/*! \brief Sets the Write Protection Disable
 *
 * This function sets the Write Protection Disable.
 * When write protection is enabled (WPDIS = 0), write protected bits cannot be written. When write
 * protection is disabled (WPDIS = 1), write protected bits can be written. The WPDIS bit is the negation of
 * the WPEN bit. WPDIS is cleared when 1 is written to WPEN. WPDIS is set when WPEN bit is read as a 1
 * and then 1 is written to WPDIS. Writing 0 to WPDIS has no effect.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Write Protection Disable
 *                    - 0b : Write protection is enabled.
 *                    - 1b : Write protection is disabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetModeWpDis(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MODE;

    tmp &= ~MFT_MODE_WPDIS_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_MODE_WPDIS_SHIFT)) & MFT_MODE_WPDIS_MASK);
    obj->MODE = tmp;
}

/*! \brief Sets the Initialize The Channels Output
 *
 * This function sets the Initialize The Channels Output.
 * When a 1 is written to INIT bit the channels output is initialized according to the state of their
 * corresponding bit in the OUTINIT register. Writing a 0 to INIT bit has no effect.
 * The INIT bit is always read as 0
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Initialize The Channels Output
 */
__attribute__((always_inline)) static inline void MftReg_SetModeInit(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MODE;

    tmp &= ~MFT_MODE_INIT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_MODE_INIT_SHIFT)) & MFT_MODE_INIT_MASK);
    obj->MODE = tmp;
}

/*! \brief Gets the MFT Enable
 *
 * This function gets the current MFT Enable.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return MFT Enable
 *         - 0b : TPM compatibility. Free running counter and synchronization compatible with TPM.
 *         - 1b : Free running counter and synchronization are different from TPM behavior.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetModeMftEn(const MftRegType *obj)
{
    return ((obj->MODE & MFT_MODE_MFTEN_MASK) >> MFT_MODE_MFTEN_SHIFT);
}

/*! \brief Sets the MFT Enable
 *
 * This function sets the MFT Enable.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of MFT Enable
 *                    - 0b : TPM compatibility. Free running counter and synchronization compatible with TPM.
 *                    - 1b : Free running counter and synchronization are different from TPM behavior.
 */
__attribute__((always_inline)) static inline void MftReg_SetModeMftEn(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MODE;

    tmp &= ~MFT_MODE_MFTEN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_MODE_MFTEN_SHIFT)) & MFT_MODE_MFTEN_MASK);
    obj->MODE = tmp;
}

/*! \brief Gets the PWM Synchronization Software Trigger
 *
 * This function gets the current PWM Synchronization Software Trigger.
 * Selects the software trigger as the PWM synchronization trigger.
 * The software trigger happens when a 1 is written to SWSYNC bit.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return PWM Synchronization Software Trigger
 *         - 0b : Software trigger is not selected.
 *         - 1b : Software trigger is selected.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetSyncSwSync(const MftRegType *obj)
{
    return ((obj->SYNC & MFT_SYNC_SWSYNC_MASK) >> MFT_SYNC_SWSYNC_SHIFT);
}

/*! \brief Sets the PWM Synchronization Software Trigger
 *
 * This function sets the PWM Synchronization Software Trigger.
 * Selects the software trigger as the PWM synchronization trigger.
 * The software trigger happens when a 1 is written to SWSYNC bit.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of PWM Synchronization Software Trigger
 *                    - 0b : Software trigger is not selected.
 *                    - 1b : Software trigger is selected.
 */
__attribute__((always_inline)) static inline void MftReg_SetSyncSwSync(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SYNC;

    tmp &= ~MFT_SYNC_SWSYNC_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SYNC_SWSYNC_SHIFT)) & MFT_SYNC_SWSYNC_MASK);
    obj->SYNC = tmp;
}

/*! \brief Gets the PWM Synchronization Hardware Trigger 2
 *
 * This function gets the current PWM Synchronization Hardware Trigger 2.
 * Enables hardware trigger 2 to the PWM synchronization.
 * Hardware trigger 2 happens when a rising edge is detected at the trigger 2 input signal.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return PWM Synchronization Hardware Trigger 2
 *         - 0b : Trigger is disabled.
 *         - 1b : Trigger is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetSyncTrig2(const MftRegType *obj)
{
    return ((obj->SYNC & MFT_SYNC_TRIG2_MASK) >> MFT_SYNC_TRIG2_SHIFT);
}

/*! \brief Sets the PWM Synchronization Hardware Trigger 2
 *
 * This function sets the PWM Synchronization Hardware Trigger 2.
 * Enables hardware trigger 2 to the PWM synchronization.
 * Hardware trigger 2 happens when a rising edge is detected at the trigger 2 input signal.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of PWM Synchronization Hardware Trigger 2
 *                    - 0b : Trigger is disabled.
 *                    - 1b : Trigger is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetSyncTrig2(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SYNC;

    tmp &= ~MFT_SYNC_TRIG2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SYNC_TRIG2_SHIFT)) & MFT_SYNC_TRIG2_MASK);
    obj->SYNC = tmp;
}

/*! \brief Gets the PWM Synchronization Hardware Trigger 1
 *
 * This function gets the current PWM Synchronization Hardware Trigger 1.
 * Enables hardware trigger 1 to the PWM synchronization.
 * Hardware trigger 1 happens when a rising edge is detected at the trigger 1 input signal.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return PWM Synchronization Hardware Trigger 1
 *         - 0b : Trigger is disabled.
 *         - 1b : Trigger is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetSyncTrig1(const MftRegType *obj)
{
    return ((obj->SYNC & MFT_SYNC_TRIG1_MASK) >> MFT_SYNC_TRIG1_SHIFT);
}

/*! \brief Sets the PWM Synchronization Hardware Trigger 1
 *
 * This function sets the PWM Synchronization Hardware Trigger 1.
 * Enables hardware trigger 1 to the PWM synchronization.
 * Hardware trigger 1 happens when a rising edge is detected at the trigger 1 input signal.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of PWM Synchronization Hardware Trigger 1
 *                    - 0b : Trigger is disabled.
 *                    - 1b : Trigger is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetSyncTrig1(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SYNC;

    tmp &= ~MFT_SYNC_TRIG1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SYNC_TRIG1_SHIFT)) & MFT_SYNC_TRIG1_MASK);
    obj->SYNC = tmp;
}

/*! \brief Gets the PWM Synchronization Hardware Trigger 0
 *
 * This function gets the current PWM Synchronization Hardware Trigger 0.
 * Enables hardware trigger 0 to the PWM synchronization.
 * Hardware trigger 0 occurs when a rising edge is detected at the trigger 0 input signal.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return PWM Synchronization Hardware Trigger 0
 *         - 0b : Trigger is disabled.
 *         - 1b : Trigger is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetSyncTrig0(const MftRegType *obj)
{
    return ((obj->SYNC & MFT_SYNC_TRIG0_MASK) >> MFT_SYNC_TRIG0_SHIFT);
}

/*! \brief Sets the PWM Synchronization Hardware Trigger 0
 *
 * This function sets the PWM Synchronization Hardware Trigger 0.
 * Enables hardware trigger 0 to the PWM synchronization.
 * Hardware trigger 0 occurs when a rising edge is detected at the trigger 0 input signal.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of PWM Synchronization Hardware Trigger 0
 *                    - 0b : Trigger is disabled.
 *                    - 1b : Trigger is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetSyncTrig0(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SYNC;

    tmp &= ~MFT_SYNC_TRIG0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SYNC_TRIG0_SHIFT)) & MFT_SYNC_TRIG0_MASK);
    obj->SYNC = tmp;
}

/*! \brief Gets the Output Mask Synchronization
 *
 * This function gets the current Output Mask Synchronization.
 * Selects when the OUTMASK register is updated with the value of its buffer.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Output Mask Synchronization
 *         - 0b : OUTMASK register is updated with the value of its buffer in all rising edges of the MFT input clock.
 *         - 1b : OUTMASK register is updated with the value of its buffer only by the PWM synchronization.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetSyncSynchOM(const MftRegType *obj)
{
    return ((obj->SYNC & MFT_SYNC_SYNCHOM_MASK) >> MFT_SYNC_SYNCHOM_SHIFT);
}

/*! \brief Sets the Output Mask Synchronization
 *
 * This function sets the Output Mask Synchronization.
 * Selects when the OUTMASK register is updated with the value of its buffer.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Output Mask Synchronization
 *                    - 0b : OUTMASK register is updated with the value of its buffer in all rising edges of the MFT input clock.
 *                    - 1b : OUTMASK register is updated with the value of its buffer only by the PWM synchronization.
 */
__attribute__((always_inline)) static inline void MftReg_SetSyncSynchOM(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SYNC;

    tmp &= ~MFT_SYNC_SYNCHOM_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SYNC_SYNCHOM_SHIFT)) & MFT_SYNC_SYNCHOM_MASK);
    obj->SYNC = tmp;
}

/*! \brief Gets the MFT Counter Reinitialization by Synchronization
 *
 * This function gets the current MFT Counter Reinitialization by Synchronization.
 * Determines if the MFT counter is reinitialized when the selected trigger for the synchronization is detected
 * (MFT counter synchronization). The REINIT bit configures the synchronization when SYNCMODE is zero.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return MFT Counter Reinitialization by Synchronization
 *         - 0b : MFT counter continues to count normally.
 *         - 1b : MFT counter is updated with its initial value when the selected trigger is detected.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetSyncReInit(const MftRegType *obj)
{
    return ((obj->SYNC & MFT_SYNC_REINIT_MASK) >> MFT_SYNC_REINIT_SHIFT);
}

/*! \brief Sets the MFT Counter Reinitialization by Synchronization
 *
 * This function sets the MFT Counter Reinitialization by Synchronization.
 * Determines if the MFT counter is reinitialized when the selected trigger for the synchronization is detected
 * (MFT counter synchronization). The REINIT bit configures the synchronization when SYNCMODE is zero.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of MFT Counter Reinitialization by Synchronization
 *                    - 0b : MFT counter continues to count normally.
 *                    - 1b : MFT counter is updated with its initial value when the selected trigger is detected.
 */
__attribute__((always_inline)) static inline void MftReg_SetSyncReInit(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SYNC;

    tmp &= ~MFT_SYNC_REINIT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SYNC_REINIT_SHIFT)) & MFT_SYNC_REINIT_MASK);
    obj->SYNC = tmp;
}

/*! \brief Gets the Maximum Loading Point Enable
 *
 * This function gets the current Maximum Loading Point Enable.
 * Selects the maximum loading point to PWM synchronization (Synchronization Points).
 * If CNTMAX is 1, the selected loading point is when the MFT counter reaches its maximum value (MOD register).
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Maximum Loading Point Enable
 *         - 0b : The maximum loading point is disabled.
 *         - 1b : The maximum loading point is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetSyncCntMax(const MftRegType *obj)
{
    return ((obj->SYNC & MFT_SYNC_CNTMAX_MASK) >> MFT_SYNC_CNTMAX_SHIFT);
}

/*! \brief Sets the Maximum Loading Point Enable
 *
 * This function sets the Maximum Loading Point Enable.
 * Selects the maximum loading point to PWM synchronization (Synchronization Points).
 * If CNTMAX is 1, the selected loading point is when the MFT counter reaches its maximum value (MOD register).
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Maximum Loading Point Enable
 *                    - 0b : The maximum loading point is disabled.
 *                    - 1b : The maximum loading point is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetSyncCntMax(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SYNC;

    tmp &= ~MFT_SYNC_CNTMAX_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SYNC_CNTMAX_SHIFT)) & MFT_SYNC_CNTMAX_MASK);
    obj->SYNC = tmp;
}

/*! \brief Gets the Minimum Loading Point Enable
 *
 * This function gets the current Minimum Loading Point Enable.
 * Selects the minimum loading point to PWM synchronization (Synchronization Points).
 * If CNTMIN is 1, the selected loading point is when the MFT counter reaches its minimum value (CNTIN register).
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Minimum Loading Point Enable
 *         - 0b : The minimum loading point is disabled.
 *         - 1b : The minimum loading point is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetSyncCntMin(const MftRegType *obj)
{
    return ((obj->SYNC & MFT_SYNC_CNTMIN_MASK) >> MFT_SYNC_CNTMIN_SHIFT);
}

/*! \brief Sets the Minimum Loading Point Enable
 *
 * This function sets the Minimum Loading Point Enable.
 * Selects the minimum loading point to PWM synchronization (Synchronization Points).
 * If CNTMIN is 1, the selected loading point is when the MFT counter reaches its minimum value (CNTIN register).
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Minimum Loading Point Enable
 *                    - 0b : The minimum loading point is disabled.
 *                    - 1b : The minimum loading point is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetSyncCntMin(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SYNC;

    tmp &= ~MFT_SYNC_CNTMIN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SYNC_CNTMIN_SHIFT)) & MFT_SYNC_CNTMIN_MASK);
    obj->SYNC = tmp;
}

/*! \brief Gets the Channel 7 Output Initialization Value
 *
 * This function gets the current Channel 7 Output Initialization Value.
 * Selects the value that is forced into the channel output when the initialization occurs.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 7 Output Initialization Value
 *         - 0b : The initialization value is 0.
 *         - 1b : The initialization value is 1.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetOutInitCh7OI(const MftRegType *obj)
{
    return ((obj->OUTINIT & MFT_OUTINIT_CH7OI_MASK) >> MFT_OUTINIT_CH7OI_SHIFT);
}

/*! \brief Sets the Channel 7 Output Initialization Value
 *
 * This function sets the Channel 7 Output Initialization Value.
 * Selects the value that is forced into the channel output when the initialization occurs.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 7 Output Initialization Value
 *                    - 0b : The initialization value is 0.
 *                    - 1b : The initialization value is 1.
 */
__attribute__((always_inline)) static inline void MftReg_SetOutInitCh7OI(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->OUTINIT;

    tmp &= ~MFT_OUTINIT_CH7OI_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_OUTINIT_CH7OI_SHIFT)) & MFT_OUTINIT_CH7OI_MASK);
    obj->OUTINIT = tmp;
}

/*! \brief Gets the Channel 6 Output Initialization Value
 *
 * This function gets the current Channel 6 Output Initialization Value.
 * Selects the value that is forced into the channel output when the initialization occurs.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 6 Output Initialization Value
 *         - 0b : The initialization value is 0.
 *         - 1b : The initialization value is 1.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetOutInitCh6OI(const MftRegType *obj)
{
    return ((obj->OUTINIT & MFT_OUTINIT_CH6OI_MASK) >> MFT_OUTINIT_CH6OI_SHIFT);
}

/*! \brief Sets the Channel 6 Output Initialization Value
 *
 * This function sets the Channel 6 Output Initialization Value.
 * Selects the value that is forced into the channel output when the initialization occurs.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 6 Output Initialization Value
 *                    - 0b : The initialization value is 0.
 *                    - 1b : The initialization value is 1.
 */
__attribute__((always_inline)) static inline void MftReg_SetOutInitCh6OI(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->OUTINIT;

    tmp &= ~MFT_OUTINIT_CH6OI_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_OUTINIT_CH6OI_SHIFT)) & MFT_OUTINIT_CH6OI_MASK);
    obj->OUTINIT = tmp;
}

/*! \brief Gets the Channel 5 Output Initialization Value
 *
 * This function gets the current Channel 5 Output Initialization Value.
 * Selects the value that is forced into the channel output when the initialization occurs.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 5 Output Initialization Value
 *         - 0b : The initialization value is 0.
 *         - 1b : The initialization value is 1.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetOutInitCh5OI(const MftRegType *obj)
{
    return ((obj->OUTINIT & MFT_OUTINIT_CH5OI_MASK) >> MFT_OUTINIT_CH5OI_SHIFT);
}

/*! \brief Sets the Channel 5 Output Initialization Value
 *
 * This function sets the Channel 5 Output Initialization Value.
 * Selects the value that is forced into the channel output when the initialization occurs.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 5 Output Initialization Value
 *                    - 0b : The initialization value is 0.
 *                    - 1b : The initialization value is 1.
 */
__attribute__((always_inline)) static inline void MftReg_SetOutInitCh5OI(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->OUTINIT;

    tmp &= ~MFT_OUTINIT_CH5OI_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_OUTINIT_CH5OI_SHIFT)) & MFT_OUTINIT_CH5OI_MASK);
    obj->OUTINIT = tmp;
}

/*! \brief Gets the Channel 4 Output Initialization Value
 *
 * This function gets the current Channel 4 Output Initialization Value.
 * Selects the value that is forced into the channel output when the initialization occurs.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 4 Output Initialization Value
 *         - 0b : The initialization value is 0.
 *         - 1b : The initialization value is 1.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetOutInitCh4OI(const MftRegType *obj)
{
    return ((obj->OUTINIT & MFT_OUTINIT_CH4OI_MASK) >> MFT_OUTINIT_CH4OI_SHIFT);
}

/*! \brief Sets the Channel 4 Output Initialization Value
 *
 * This function sets the Channel 4 Output Initialization Value.
 * Selects the value that is forced into the channel output when the initialization occurs.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 4 Output Initialization Value
 *                    - 0b : The initialization value is 0.
 *                    - 1b : The initialization value is 1.
 */
__attribute__((always_inline)) static inline void MftReg_SetOutInitCh4OI(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->OUTINIT;

    tmp &= ~MFT_OUTINIT_CH4OI_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_OUTINIT_CH4OI_SHIFT)) & MFT_OUTINIT_CH4OI_MASK);
    obj->OUTINIT = tmp;
}

/*! \brief Gets the Channel 3 Output Initialization Value
 *
 * This function gets the current Channel 3 Output Initialization Value.
 * Selects the value that is forced into the channel output when the initialization occurs.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 3 Output Initialization Value
 *         - 0b : The initialization value is 0.
 *         - 1b : The initialization value is 1.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetOutInitCh3OI(const MftRegType *obj)
{
    return ((obj->OUTINIT & MFT_OUTINIT_CH3OI_MASK) >> MFT_OUTINIT_CH3OI_SHIFT);
}

/*! \brief Sets the Channel 3 Output Initialization Value
 *
 * This function sets the Channel 3 Output Initialization Value.
 * Selects the value that is forced into the channel output when the initialization occurs.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 3 Output Initialization Value
 *                    - 0b : The initialization value is 0.
 *                    - 1b : The initialization value is 1.
 */
__attribute__((always_inline)) static inline void MftReg_SetOutInitCh3OI(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->OUTINIT;

    tmp &= ~MFT_OUTINIT_CH3OI_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_OUTINIT_CH3OI_SHIFT)) & MFT_OUTINIT_CH3OI_MASK);
    obj->OUTINIT = tmp;
}

/*! \brief Gets the Channel 2 Output Initialization Value
 *
 * This function gets the current Channel 2 Output Initialization Value.
 * Selects the value that is forced into the channel output when the initialization occurs.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 2 Output Initialization Value
 *         - 0b : The initialization value is 0.
 *         - 1b : The initialization value is 1.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetOutInitCh2OI(const MftRegType *obj)
{
    return ((obj->OUTINIT & MFT_OUTINIT_CH2OI_MASK) >> MFT_OUTINIT_CH2OI_SHIFT);
}

/*! \brief Sets the Channel 2 Output Initialization Value
 *
 * This function sets the Channel 2 Output Initialization Value.
 * Selects the value that is forced into the channel output when the initialization occurs.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 2 Output Initialization Value
 *                    - 0b : The initialization value is 0.
 *                    - 1b : The initialization value is 1.
 */
__attribute__((always_inline)) static inline void MftReg_SetOutInitCh2OI(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->OUTINIT;

    tmp &= ~MFT_OUTINIT_CH2OI_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_OUTINIT_CH2OI_SHIFT)) & MFT_OUTINIT_CH2OI_MASK);
    obj->OUTINIT = tmp;
}

/*! \brief Gets the Channel 1 Output Initialization Value
 *
 * This function gets the current Channel 1 Output Initialization Value.
 * Selects the value that is forced into the channel output when the initialization occurs.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 1 Output Initialization Value
 *         - 0b : The initialization value is 0.
 *         - 1b : The initialization value is 1.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetOutInitCh1OI(const MftRegType *obj)
{
    return ((obj->OUTINIT & MFT_OUTINIT_CH1OI_MASK) >> MFT_OUTINIT_CH1OI_SHIFT);
}

/*! \brief Sets the Channel 1 Output Initialization Value
 *
 * This function sets the Channel 1 Output Initialization Value.
 * Selects the value that is forced into the channel output when the initialization occurs.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 1 Output Initialization Value
 *                    - 0b : The initialization value is 0.
 *                    - 1b : The initialization value is 1.
 */
__attribute__((always_inline)) static inline void MftReg_SetOutInitCh1OI(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->OUTINIT;

    tmp &= ~MFT_OUTINIT_CH1OI_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_OUTINIT_CH1OI_SHIFT)) & MFT_OUTINIT_CH1OI_MASK);
    obj->OUTINIT = tmp;
}

/*! \brief Gets the Channel 0 Output Initialization Value
 *
 * This function gets the current Channel 0 Output Initialization Value.
 * Selects the value that is forced into the channel output when the initialization occurs.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 0 Output Initialization Value
 *         - 0b : The initialization value is 0.
 *         - 1b : The initialization value is 1.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetOutInitCh0OI(const MftRegType *obj)
{
    return ((obj->OUTINIT & MFT_OUTINIT_CH0OI_MASK) >> MFT_OUTINIT_CH0OI_SHIFT);
}

/*! \brief Sets the Channel 0 Output Initialization Value
 *
 * This function sets the Channel 0 Output Initialization Value.
 * Selects the value that is forced into the channel output when the initialization occurs.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 0 Output Initialization Value
 *                    - 0b : The initialization value is 0.
 *                    - 1b : The initialization value is 1.
 */
__attribute__((always_inline)) static inline void MftReg_SetOutInitCh0OI(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->OUTINIT;

    tmp &= ~MFT_OUTINIT_CH0OI_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_OUTINIT_CH0OI_SHIFT)) & MFT_OUTINIT_CH0OI_MASK);
    obj->OUTINIT = tmp;
}

/*! \brief Gets the Channel 7 Output Mask
 *
 * This function gets the current Channel 7 Output Mask.
 * Defines if the channel output is masked or unmasked.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 7 Output Mask
 *         - 0b : Channel output is not masked. It continues to operate normally.
 *         - 1b : Channel output is masked. It is forced to its inactive state.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetOutMaskCh7OM(const MftRegType *obj)
{
    return ((obj->OUTMASK & MFT_OUTMASK_CH7OM_MASK) >> MFT_OUTMASK_CH7OM_SHIFT);
}

/*! \brief Sets the Channel 7 Output Mask
 *
 * This function sets the Channel 7 Output Mask.
 * Defines if the channel output is masked or unmasked.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 7 Output Mask
 *                    - 0b : Channel output is not masked. It continues to operate normally.
 *                    - 1b : Channel output is masked. It is forced to its inactive state.
 */
__attribute__((always_inline)) static inline void MftReg_SetOutMaskCh7OM(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->OUTMASK;

    tmp &= ~MFT_OUTMASK_CH7OM_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_OUTMASK_CH7OM_SHIFT)) & MFT_OUTMASK_CH7OM_MASK);
    obj->OUTMASK = tmp;
}

/*! \brief Gets the Channel 6 Output Mask
 *
 * This function gets the current Channel 6 Output Mask.
 * Defines if the channel output is masked or unmasked.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 6 Output Mask
 *         - 0b : Channel output is not masked. It continues to operate normally.
 *         - 1b : Channel output is masked. It is forced to its inactive state.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetOutMaskCh6OM(const MftRegType *obj)
{
    return ((obj->OUTMASK & MFT_OUTMASK_CH6OM_MASK) >> MFT_OUTMASK_CH6OM_SHIFT);
}

/*! \brief Sets the Channel 6 Output Mask
 *
 * This function sets the Channel 6 Output Mask.
 * Defines if the channel output is masked or unmasked.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 6 Output Mask
 *                    - 0b : Channel output is not masked. It continues to operate normally.
 *                    - 1b : Channel output is masked. It is forced to its inactive state.
 */
__attribute__((always_inline)) static inline void MftReg_SetOutMaskCh6OM(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->OUTMASK;

    tmp &= ~MFT_OUTMASK_CH6OM_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_OUTMASK_CH6OM_SHIFT)) & MFT_OUTMASK_CH6OM_MASK);
    obj->OUTMASK = tmp;
}

/*! \brief Gets the Channel 5 Output Mask
 *
 * This function gets the current Channel 5 Output Mask.
 * Defines if the channel output is masked or unmasked.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 5 Output Mask
 *         - 0b : Channel output is not masked. It continues to operate normally.
 *         - 1b : Channel output is masked. It is forced to its inactive state.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetOutMaskCh5OM(const MftRegType *obj)
{
    return ((obj->OUTMASK & MFT_OUTMASK_CH5OM_MASK) >> MFT_OUTMASK_CH5OM_SHIFT);
}

/*! \brief Sets the Channel 5 Output Mask
 *
 * This function sets the Channel 5 Output Mask.
 * Defines if the channel output is masked or unmasked.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 5 Output Mask
 *                    - 0b : Channel output is not masked. It continues to operate normally.
 *                    - 1b : Channel output is masked. It is forced to its inactive state.
 */
__attribute__((always_inline)) static inline void MftReg_SetOutMaskCh5OM(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->OUTMASK;

    tmp &= ~MFT_OUTMASK_CH5OM_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_OUTMASK_CH5OM_SHIFT)) & MFT_OUTMASK_CH5OM_MASK);
    obj->OUTMASK = tmp;
}

/*! \brief Gets the Channel 4 Output Mask
 *
 * This function gets the current Channel 4 Output Mask.
 * Defines if the channel output is masked or unmasked.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 4 Output Mask
 *         - 0b : Channel output is not masked. It continues to operate normally.
 *         - 1b : Channel output is masked. It is forced to its inactive state.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetOutMaskCh4OM(const MftRegType *obj)
{
    return ((obj->OUTMASK & MFT_OUTMASK_CH4OM_MASK) >> MFT_OUTMASK_CH4OM_SHIFT);
}

/*! \brief Sets the Channel 4 Output Mask
 *
 * This function sets the Channel 4 Output Mask.
 * Defines if the channel output is masked or unmasked.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 4 Output Mask
 *                    - 0b : Channel output is not masked. It continues to operate normally.
 *                    - 1b : Channel output is masked. It is forced to its inactive state.
 */
__attribute__((always_inline)) static inline void MftReg_SetOutMaskCh4OM(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->OUTMASK;

    tmp &= ~MFT_OUTMASK_CH4OM_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_OUTMASK_CH4OM_SHIFT)) & MFT_OUTMASK_CH4OM_MASK);
    obj->OUTMASK = tmp;
}

/*! \brief Gets the Channel 3 Output Mask
 *
 * This function gets the current Channel 3 Output Mask.
 * Defines if the channel output is masked or unmasked.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 3 Output Mask
 *         - 0b : Channel output is not masked. It continues to operate normally.
 *         - 1b : Channel output is masked. It is forced to its inactive state.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetOutMaskCh3OM(const MftRegType *obj)
{
    return ((obj->OUTMASK & MFT_OUTMASK_CH3OM_MASK) >> MFT_OUTMASK_CH3OM_SHIFT);
}

/*! \brief Sets the Channel 3 Output Mask
 *
 * This function sets the Channel 3 Output Mask.
 * Defines if the channel output is masked or unmasked.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 3 Output Mask
 *                    - 0b : Channel output is not masked. It continues to operate normally.
 *                    - 1b : Channel output is masked. It is forced to its inactive state.
 */
__attribute__((always_inline)) static inline void MftReg_SetOutMaskCh3OM(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->OUTMASK;

    tmp &= ~MFT_OUTMASK_CH3OM_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_OUTMASK_CH3OM_SHIFT)) & MFT_OUTMASK_CH3OM_MASK);
    obj->OUTMASK = tmp;
}

/*! \brief Gets the Channel 2 Output Mask
 *
 * This function gets the current Channel 2 Output Mask.
 * Defines if the channel output is masked or unmasked.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 2 Output Mask
 *         - 0b : Channel output is not masked. It continues to operate normally.
 *         - 1b : Channel output is masked. It is forced to its inactive state.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetOutMaskCh2OM(const MftRegType *obj)
{
    return ((obj->OUTMASK & MFT_OUTMASK_CH2OM_MASK) >> MFT_OUTMASK_CH2OM_SHIFT);
}

/*! \brief Sets the Channel 2 Output Mask
 *
 * This function sets the Channel 2 Output Mask.
 * Defines if the channel output is masked or unmasked.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 2 Output Mask
 *                    - 0b : Channel output is not masked. It continues to operate normally.
 *                    - 1b : Channel output is masked. It is forced to its inactive state.
 */
__attribute__((always_inline)) static inline void MftReg_SetOutMaskCh2OM(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->OUTMASK;

    tmp &= ~MFT_OUTMASK_CH2OM_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_OUTMASK_CH2OM_SHIFT)) & MFT_OUTMASK_CH2OM_MASK);
    obj->OUTMASK = tmp;
}

/*! \brief Gets the Channel 1 Output Mask
 *
 * This function gets the current Channel 1 Output Mask.
 * Defines if the channel output is masked or unmasked.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 1 Output Mask
 *         - 0b : Channel output is not masked. It continues to operate normally.
 *         - 1b : Channel output is masked. It is forced to its inactive state.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetOutMaskCh1OM(const MftRegType *obj)
{
    return ((obj->OUTMASK & MFT_OUTMASK_CH1OM_MASK) >> MFT_OUTMASK_CH1OM_SHIFT);
}

/*! \brief Sets the Channel 1 Output Mask
 *
 * This function sets the Channel 1 Output Mask.
 * Defines if the channel output is masked or unmasked.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 1 Output Mask
 *                    - 0b : Channel output is not masked. It continues to operate normally.
 *                    - 1b : Channel output is masked. It is forced to its inactive state.
 */
__attribute__((always_inline)) static inline void MftReg_SetOutMaskCh1OM(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->OUTMASK;

    tmp &= ~MFT_OUTMASK_CH1OM_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_OUTMASK_CH1OM_SHIFT)) & MFT_OUTMASK_CH1OM_MASK);
    obj->OUTMASK = tmp;
}

/*! \brief Gets the Channel 0 Output Mask
 *
 * This function gets the current Channel 0 Output Mask.
 * Defines if the channel output is masked or unmasked.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 0 Output Mask
 *         - 0b : Channel output is not masked. It continues to operate normally.
 *         - 1b : Channel output is masked. It is forced to its inactive state.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetOutMaskCh0OM(const MftRegType *obj)
{
    return ((obj->OUTMASK & MFT_OUTMASK_CH0OM_MASK) >> MFT_OUTMASK_CH0OM_SHIFT);
}

/*! \brief Sets the Channel 0 Output Mask
 *
 * This function sets the Channel 0 Output Mask.
 * Defines if the channel output is masked or unmasked.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 0 Output Mask
 *                    - 0b : Channel output is not masked. It continues to operate normally.
 *                    - 1b : Channel output is masked. It is forced to its inactive state.
 */
__attribute__((always_inline)) static inline void MftReg_SetOutMaskCh0OM(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->OUTMASK;

    tmp &= ~MFT_OUTMASK_CH0OM_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_OUTMASK_CH0OM_SHIFT)) & MFT_OUTMASK_CH0OM_MASK);
    obj->OUTMASK = tmp;
}

/*! \brief Gets the Modified Combine Mode For n = 6
 *
 * This function gets the current Modified Combine Mode For n = 6.
 * Used on the selection of the modified combine mode for channels (n) and (n+1).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Modified Combine Mode For n = 6
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCombineMCombine3(const MftRegType *obj)
{
    return ((obj->COMBINE & MFT_COMBINE_MCOMBINE3_MASK) >> MFT_COMBINE_MCOMBINE3_SHIFT);
}

/*! \brief Sets the Modified Combine Mode For n = 6
 *
 * This function sets the Modified Combine Mode For n = 6.
 * Used on the selection of the modified combine mode for channels (n) and (n+1).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Modified Combine Mode For n = 6
 */
__attribute__((always_inline)) static inline void MftReg_SetCombineMCombine3(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->COMBINE;

    tmp &= ~MFT_COMBINE_MCOMBINE3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_COMBINE_MCOMBINE3_SHIFT)) & MFT_COMBINE_MCOMBINE3_MASK);
    obj->COMBINE = tmp;
}

/*! \brief Gets the Fault Control Enable For n = 6
 *
 * This function gets the current Fault Control Enable For n = 6.
 * Enables the fault control in channels (n) and (n+1).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Fault Control Enable For n = 6
 *         - 0b : The fault control in this pair of channels is disabled.
 *         - 1b : The fault control in this pair of channels is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCombineFaultEn3(const MftRegType *obj)
{
    return ((obj->COMBINE & MFT_COMBINE_FAULTEN3_MASK) >> MFT_COMBINE_FAULTEN3_SHIFT);
}

/*! \brief Sets the Fault Control Enable For n = 6
 *
 * This function sets the Fault Control Enable For n = 6.
 * Enables the fault control in channels (n) and (n+1).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Fault Control Enable For n = 6
 *                    - 0b : The fault control in this pair of channels is disabled.
 *                    - 1b : The fault control in this pair of channels is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetCombineFaultEn3(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->COMBINE;

    tmp &= ~MFT_COMBINE_FAULTEN3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_COMBINE_FAULTEN3_SHIFT)) & MFT_COMBINE_FAULTEN3_MASK);
    obj->COMBINE = tmp;
}

/*! \brief Gets the Synchronization Enable For n = 6
 *
 * This function gets the current Synchronization Enable For n = 6.
 * Enables PWM synchronization of registers C(n)V and C(n+1)V.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Synchronization Enable For n = 6
 *         - 0b : The PWM synchronization in this pair of channels is disabled.
 *         - 1b : The PWM synchronization in this pair of channels is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCombineSyncEn3(const MftRegType *obj)
{
    return ((obj->COMBINE & MFT_COMBINE_SYNCEN3_MASK) >> MFT_COMBINE_SYNCEN3_SHIFT);
}

/*! \brief Sets the Synchronization Enable For n = 6
 *
 * This function sets the Synchronization Enable For n = 6.
 * Enables PWM synchronization of registers C(n)V and C(n+1)V.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Synchronization Enable For n = 6
 *                    - 0b : The PWM synchronization in this pair of channels is disabled.
 *                    - 1b : The PWM synchronization in this pair of channels is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetCombineSyncEn3(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->COMBINE;

    tmp &= ~MFT_COMBINE_SYNCEN3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_COMBINE_SYNCEN3_SHIFT)) & MFT_COMBINE_SYNCEN3_MASK);
    obj->COMBINE = tmp;
}

/*! \brief Gets the Deadtime Enable For n = 6
 *
 * This function gets the current Deadtime Enable For n = 6.
 * Enables the deadtime insertion in the channels (n) and (n+1).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Deadtime Enable For n = 6
 *         - 0b : The deadtime insertion in this pair of channels is disabled.
 *         - 1b : The deadtime insertion in this pair of channels is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCombineDtEn3(const MftRegType *obj)
{
    return ((obj->COMBINE & MFT_COMBINE_DTEN3_MASK) >> MFT_COMBINE_DTEN3_SHIFT);
}

/*! \brief Sets the Deadtime Enable For n = 6
 *
 * This function sets the Deadtime Enable For n = 6.
 * Enables the deadtime insertion in the channels (n) and (n+1).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Deadtime Enable For n = 6
 *                    - 0b : The deadtime insertion in this pair of channels is disabled.
 *                    - 1b : The deadtime insertion in this pair of channels is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetCombineDtEn3(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->COMBINE;

    tmp &= ~MFT_COMBINE_DTEN3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_COMBINE_DTEN3_SHIFT)) & MFT_COMBINE_DTEN3_MASK);
    obj->COMBINE = tmp;
}

/*! \brief Gets the Dual Edge Capture Mode Captures For n = 6
 *
 * This function gets the current Dual Edge Capture Mode Captures For n = 6.
 * Enables the capture of the MFT counter value according to the channel (n) input event and the
 * configuration of the dual edge capture bits.
 * This field applies only when DECAPEN = 1.
 * DECAP bit is cleared automatically by hardware if dual edge capture ¨C one-shot mode is selected and
 * when the capture of channel (n+1) event is made.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Dual Edge Capture Mode Captures For n = 6
 *         - 0b : The dual edge captures are inactive.
 *         - 1b : The dual edge captures are active.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCombineDecap3(const MftRegType *obj)
{
    return ((obj->COMBINE & MFT_COMBINE_DECAP3_MASK) >> MFT_COMBINE_DECAP3_SHIFT);
}

/*! \brief Sets the Dual Edge Capture Mode Captures For n = 6
 *
 * This function sets the Dual Edge Capture Mode Captures For n = 6.
 * Enables the capture of the MFT counter value according to the channel (n) input event and the
 * configuration of the dual edge capture bits.
 * This field applies only when DECAPEN = 1.
 * DECAP bit is cleared automatically by hardware if dual edge capture ¨C one-shot mode is selected and
 * when the capture of channel (n+1) event is made.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Dual Edge Capture Mode Captures For n = 6
 *                    - 0b : The dual edge captures are inactive.
 *                    - 1b : The dual edge captures are active.
 */
__attribute__((always_inline)) static inline void MftReg_SetCombineDecap3(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->COMBINE;

    tmp &= ~MFT_COMBINE_DECAP3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_COMBINE_DECAP3_SHIFT)) & MFT_COMBINE_DECAP3_MASK);
    obj->COMBINE = tmp;
}

/*! \brief Gets the Dual Edge Capture Mode Enable For n = 6
 *
 * This function gets the current Dual Edge Capture Mode Enable For n = 6.
 * Enables the Dual Edge Capture mode in the channels (n) and (n+1).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Dual Edge Capture Mode Enable For n = 6
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCombineDecapEn3(const MftRegType *obj)
{
    return ((obj->COMBINE & MFT_COMBINE_DECAPEN3_MASK) >> MFT_COMBINE_DECAPEN3_SHIFT);
}

/*! \brief Sets the Dual Edge Capture Mode Enable For n = 6
 *
 * This function sets the Dual Edge Capture Mode Enable For n = 6.
 * Enables the Dual Edge Capture mode in the channels (n) and (n+1).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Dual Edge Capture Mode Enable For n = 6
 */
__attribute__((always_inline)) static inline void MftReg_SetCombineDecapEn3(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->COMBINE;

    tmp &= ~MFT_COMBINE_DECAPEN3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_COMBINE_DECAPEN3_SHIFT)) & MFT_COMBINE_DECAPEN3_MASK);
    obj->COMBINE = tmp;
}

/*! \brief Gets the Complement Of Channel (n) for n = 6
 *
 * This function gets the current Complement Of Channel (n) for n = 6.
 * In Complementary mode the channel (n+1) output is the inverse of the channel (n) output.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Complement Of Channel (n) for n = 6
 *         - 0b : If the channels (n) and (n+1) are in Combine Mode or Modified Combine PWM Mode,
 *                the channel (n+1) output is the same as the channel (n) output.
 *                If the channel (n+1) is in Output Compare Mode, EPWM or CPWM,
 *                the channel (n+1) output is independent from channel (n) output.
 *         - 1b : The channel (n+1) output is the complement of the channel (n) output.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCombineComp3(const MftRegType *obj)
{
    return ((obj->COMBINE & MFT_COMBINE_COMP3_MASK) >> MFT_COMBINE_COMP3_SHIFT);
}

/*! \brief Sets the Complement Of Channel (n) for n = 6
 *
 * This function sets the Complement Of Channel (n) for n = 6.
 * In Complementary mode the channel (n+1) output is the inverse of the channel (n) output.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Complement Of Channel (n) for n = 6
 *                    - 0b : If the channels (n) and (n+1) are in Combine Mode or Modified Combine PWM Mode,
 *                           the channel (n+1) output is the same as the channel (n) output.
 *                           If the channel (n+1) is in Output Compare Mode, EPWM or CPWM,
 *                           the channel (n+1) output is independent from channel (n) output.
 *                    - 1b : The channel (n+1) output is the complement of the channel (n) output.
 */
__attribute__((always_inline)) static inline void MftReg_SetCombineComp3(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->COMBINE;

    tmp &= ~MFT_COMBINE_COMP3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_COMBINE_COMP3_SHIFT)) & MFT_COMBINE_COMP3_MASK);
    obj->COMBINE = tmp;
}

/*! \brief Gets the Combine Channels For n = 6
 *
 * This function gets the current Combine Channels For n = 6.
 * Used on the selection of the combine mode for channels (n) and (n+1).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Combine Channels For n = 6
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCombineCombine3(const MftRegType *obj)
{
    return ((obj->COMBINE & MFT_COMBINE_COMBINE3_MASK) >> MFT_COMBINE_COMBINE3_SHIFT);
}

/*! \brief Sets the Combine Channels For n = 6
 *
 * This function sets the Combine Channels For n = 6.
 * Used on the selection of the combine mode for channels (n) and (n+1).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Combine Channels For n = 6
 */
__attribute__((always_inline)) static inline void MftReg_SetCombineCombine3(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->COMBINE;

    tmp &= ~MFT_COMBINE_COMBINE3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_COMBINE_COMBINE3_SHIFT)) & MFT_COMBINE_COMBINE3_MASK);
    obj->COMBINE = tmp;
}

/*! \brief Gets the Modified Combine Mode For n = 4
 *
 * This function gets the current Modified Combine Mode For n = 4.
 * Used on the selection of the modified combine mode for channels (n) and (n+1).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Modified Combine Mode For n = 4
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCombineMCombine2(const MftRegType *obj)
{
    return ((obj->COMBINE & MFT_COMBINE_MCOMBINE2_MASK) >> MFT_COMBINE_MCOMBINE2_SHIFT);
}

/*! \brief Sets the Modified Combine Mode For n = 4
 *
 * This function sets the Modified Combine Mode For n = 4.
 * Used on the selection of the modified combine mode for channels (n) and (n+1).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Modified Combine Mode For n = 4
 */
__attribute__((always_inline)) static inline void MftReg_SetCombineMCombine2(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->COMBINE;

    tmp &= ~MFT_COMBINE_MCOMBINE2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_COMBINE_MCOMBINE2_SHIFT)) & MFT_COMBINE_MCOMBINE2_MASK);
    obj->COMBINE = tmp;
}

/*! \brief Gets the Fault Control Enable For n = 4
 *
 * This function gets the current Fault Control Enable For n = 4.
 * Enables the fault control in channels (n) and (n+1).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Fault Control Enable For n = 4
 *         - 0b : The fault control in this pair of channels is disabled.
 *         - 1b : The fault control in this pair of channels is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCombineFaultEn2(const MftRegType *obj)
{
    return ((obj->COMBINE & MFT_COMBINE_FAULTEN2_MASK) >> MFT_COMBINE_FAULTEN2_SHIFT);
}

/*! \brief Sets the Fault Control Enable For n = 4
 *
 * This function sets the Fault Control Enable For n = 4.
 * Enables the fault control in channels (n) and (n+1).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Fault Control Enable For n = 4
 *                    - 0b : The fault control in this pair of channels is disabled.
 *                    - 1b : The fault control in this pair of channels is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetCombineFaultEn2(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->COMBINE;

    tmp &= ~MFT_COMBINE_FAULTEN2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_COMBINE_FAULTEN2_SHIFT)) & MFT_COMBINE_FAULTEN2_MASK);
    obj->COMBINE = tmp;
}

/*! \brief Gets the Synchronization Enable For n = 4
 *
 * This function gets the current Synchronization Enable For n = 4.
 * Enables PWM synchronization of registers C(n)V and C(n+1)V.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Synchronization Enable For n = 4
 *         - 0b : The PWM synchronization in this pair of channels is disabled.
 *         - 1b : The PWM synchronization in this pair of channels is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCombineSyncEn2(const MftRegType *obj)
{
    return ((obj->COMBINE & MFT_COMBINE_SYNCEN2_MASK) >> MFT_COMBINE_SYNCEN2_SHIFT);
}

/*! \brief Sets the Synchronization Enable For n = 4
 *
 * This function sets the Synchronization Enable For n = 4.
 * Enables PWM synchronization of registers C(n)V and C(n+1)V.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Synchronization Enable For n = 4
 *                    - 0b : The PWM synchronization in this pair of channels is disabled.
 *                    - 1b : The PWM synchronization in this pair of channels is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetCombineSyncEn2(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->COMBINE;

    tmp &= ~MFT_COMBINE_SYNCEN2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_COMBINE_SYNCEN2_SHIFT)) & MFT_COMBINE_SYNCEN2_MASK);
    obj->COMBINE = tmp;
}

/*! \brief Gets the Deadtime Enable For n = 4
 *
 * This function gets the current Deadtime Enable For n = 4.
 * Enables the deadtime insertion in the channels (n) and (n+1).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Deadtime Enable For n = 4
 *         - 0b : The deadtime insertion in this pair of channels is disabled.
 *         - 1b : The deadtime insertion in this pair of channels is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCombineDtEn2(const MftRegType *obj)
{
    return ((obj->COMBINE & MFT_COMBINE_DTEN2_MASK) >> MFT_COMBINE_DTEN2_SHIFT);
}

/*! \brief Sets the Deadtime Enable For n = 4
 *
 * This function sets the Deadtime Enable For n = 4.
 * Enables the deadtime insertion in the channels (n) and (n+1).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Deadtime Enable For n = 4
 *                    - 0b : The deadtime insertion in this pair of channels is disabled.
 *                    - 1b : The deadtime insertion in this pair of channels is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetCombineDtEn2(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->COMBINE;

    tmp &= ~MFT_COMBINE_DTEN2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_COMBINE_DTEN2_SHIFT)) & MFT_COMBINE_DTEN2_MASK);
    obj->COMBINE = tmp;
}

/*! \brief Gets the Dual Edge Capture Mode Captures For n = 4
 *
 * This function gets the current Dual Edge Capture Mode Captures For n = 4.
 * Enables the capture of the MFT counter value according to the channel (n) input event and the
 * configuration of the dual edge capture bits.
 * This field applies only when DECAPEN = 1.
 * DECAP bit is cleared automatically by hardware if dual edge capture ¨C one-shot mode is selected and
 * when the capture of channel (n+1) event is made.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Dual Edge Capture Mode Captures For n = 4
 *         - 0b : The dual edge captures are inactive.
 *         - 1b : The dual edge captures are active.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCombineDecap2(const MftRegType *obj)
{
    return ((obj->COMBINE & MFT_COMBINE_DECAP2_MASK) >> MFT_COMBINE_DECAP2_SHIFT);
}

/*! \brief Sets the Dual Edge Capture Mode Captures For n = 4
 *
 * This function sets the Dual Edge Capture Mode Captures For n = 4.
 * Enables the capture of the MFT counter value according to the channel (n) input event and the
 * configuration of the dual edge capture bits.
 * This field applies only when DECAPEN = 1.
 * DECAP bit is cleared automatically by hardware if dual edge capture ¨C one-shot mode is selected and
 * when the capture of channel (n+1) event is made.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Dual Edge Capture Mode Captures For n = 4
 *                    - 0b : The dual edge captures are inactive.
 *                    - 1b : The dual edge captures are active.
 */
__attribute__((always_inline)) static inline void MftReg_SetCombineDecap2(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->COMBINE;

    tmp &= ~MFT_COMBINE_DECAP2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_COMBINE_DECAP2_SHIFT)) & MFT_COMBINE_DECAP2_MASK);
    obj->COMBINE = tmp;
}

/*! \brief Gets the Dual Edge Capture Mode Enable For n = 4
 *
 * This function gets the current Dual Edge Capture Mode Enable For n = 4.
 * Enables the Dual Edge Capture mode in the channels (n) and (n+1).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Dual Edge Capture Mode Enable For n = 4
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCombineDecapEn2(const MftRegType *obj)
{
    return ((obj->COMBINE & MFT_COMBINE_DECAPEN2_MASK) >> MFT_COMBINE_DECAPEN2_SHIFT);
}

/*! \brief Sets the Dual Edge Capture Mode Enable For n = 4
 *
 * This function sets the Dual Edge Capture Mode Enable For n = 4.
 * Enables the Dual Edge Capture mode in the channels (n) and (n+1).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Dual Edge Capture Mode Enable For n = 4
 */
__attribute__((always_inline)) static inline void MftReg_SetCombineDecapEn2(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->COMBINE;

    tmp &= ~MFT_COMBINE_DECAPEN2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_COMBINE_DECAPEN2_SHIFT)) & MFT_COMBINE_DECAPEN2_MASK);
    obj->COMBINE = tmp;
}

/*! \brief Gets the Complement Of Channel (n) for n = 4
 *
 * This function gets the current Complement Of Channel (n) for n = 4.
 * In Complementary mode the channel (n+1) output is the inverse of the channel (n) output.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Complement Of Channel (n) for n = 4
 *         - 0b : If the channels (n) and (n+1) are in Combine Mode or Modified Combine PWM Mode,
 *                the channel (n+1) output is the same as the channel (n) output.
 *                If the channel (n+1) is in Output Compare Mode, EPWM or CPWM,
 *                the channel (n+1) output is independent from channel (n) output.
 *         - 1b : The channel (n+1) output is the complement of the channel (n) output.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCombineComp2(const MftRegType *obj)
{
    return ((obj->COMBINE & MFT_COMBINE_COMP2_MASK) >> MFT_COMBINE_COMP2_SHIFT);
}

/*! \brief Sets the Complement Of Channel (n) for n = 4
 *
 * This function sets the Complement Of Channel (n) for n = 4.
 * In Complementary mode the channel (n+1) output is the inverse of the channel (n) output.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Complement Of Channel (n) for n = 4
 *                    - 0b : If the channels (n) and (n+1) are in Combine Mode or Modified Combine PWM Mode,
 *                           the channel (n+1) output is the same as the channel (n) output.
 *                           If the channel (n+1) is in Output Compare Mode, EPWM or CPWM,
 *                           the channel (n+1) output is independent from channel (n) output.
 *                    - 1b : The channel (n+1) output is the complement of the channel (n) output.
 */
__attribute__((always_inline)) static inline void MftReg_SetCombineComp2(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->COMBINE;

    tmp &= ~MFT_COMBINE_COMP2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_COMBINE_COMP2_SHIFT)) & MFT_COMBINE_COMP2_MASK);
    obj->COMBINE = tmp;
}

/*! \brief Gets the Combine Channels For n = 4
 *
 * This function gets the current Combine Channels For n = 4.
 * Used on the selection of the combine mode for channels (n) and (n+1).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Combine Channels For n = 4
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCombineCombine2(const MftRegType *obj)
{
    return ((obj->COMBINE & MFT_COMBINE_COMBINE2_MASK) >> MFT_COMBINE_COMBINE2_SHIFT);
}

/*! \brief Sets the Combine Channels For n = 4
 *
 * This function sets the Combine Channels For n = 4.
 * Used on the selection of the combine mode for channels (n) and (n+1).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Combine Channels For n = 4
 */
__attribute__((always_inline)) static inline void MftReg_SetCombineCombine2(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->COMBINE;

    tmp &= ~MFT_COMBINE_COMBINE2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_COMBINE_COMBINE2_SHIFT)) & MFT_COMBINE_COMBINE2_MASK);
    obj->COMBINE = tmp;
}

/*! \brief Gets the Modified Combine Mode For n = 2
 *
 * This function gets the current Modified Combine Mode For n = 2.
 * Used on the selection of the modified combine mode for channels (n) and (n+1).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Modified Combine Mode For n = 2
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCombineMCombine1(const MftRegType *obj)
{
    return ((obj->COMBINE & MFT_COMBINE_MCOMBINE1_MASK) >> MFT_COMBINE_MCOMBINE1_SHIFT);
}

/*! \brief Sets the Modified Combine Mode For n = 2
 *
 * This function sets the Modified Combine Mode For n = 2.
 * Used on the selection of the modified combine mode for channels (n) and (n+1).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Modified Combine Mode For n = 2
 */
__attribute__((always_inline)) static inline void MftReg_SetCombineMCombine1(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->COMBINE;

    tmp &= ~MFT_COMBINE_MCOMBINE1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_COMBINE_MCOMBINE1_SHIFT)) & MFT_COMBINE_MCOMBINE1_MASK);
    obj->COMBINE = tmp;
}

/*! \brief Gets the Fault Control Enable For n = 2
 *
 * This function gets the current Fault Control Enable For n = 2.
 * Enables the fault control in channels (n) and (n+1).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Fault Control Enable For n = 2
 *         - 0b : The fault control in this pair of channels is disabled.
 *         - 1b : The fault control in this pair of channels is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCombineFaultEn1(const MftRegType *obj)
{
    return ((obj->COMBINE & MFT_COMBINE_FAULTEN1_MASK) >> MFT_COMBINE_FAULTEN1_SHIFT);
}

/*! \brief Sets the Fault Control Enable For n = 2
 *
 * This function sets the Fault Control Enable For n = 2.
 * Enables the fault control in channels (n) and (n+1).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Fault Control Enable For n = 2
 *                    - 0b : The fault control in this pair of channels is disabled.
 *                    - 1b : The fault control in this pair of channels is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetCombineFaultEn1(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->COMBINE;

    tmp &= ~MFT_COMBINE_FAULTEN1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_COMBINE_FAULTEN1_SHIFT)) & MFT_COMBINE_FAULTEN1_MASK);
    obj->COMBINE = tmp;
}

/*! \brief Gets the Synchronization Enable For n = 2
 *
 * This function gets the current Synchronization Enable For n = 2.
 * Enables PWM synchronization of registers C(n)V and C(n+1)V.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Synchronization Enable For n = 2
 *         - 0b : The PWM synchronization in this pair of channels is disabled.
 *         - 1b : The PWM synchronization in this pair of channels is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCombineSyncEn1(const MftRegType *obj)
{
    return ((obj->COMBINE & MFT_COMBINE_SYNCEN1_MASK) >> MFT_COMBINE_SYNCEN1_SHIFT);
}

/*! \brief Sets the Synchronization Enable For n = 2
 *
 * This function sets the Synchronization Enable For n = 2.
 * Enables PWM synchronization of registers C(n)V and C(n+1)V.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Synchronization Enable For n = 2
 *                    - 0b : The PWM synchronization in this pair of channels is disabled.
 *                    - 1b : The PWM synchronization in this pair of channels is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetCombineSyncEn1(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->COMBINE;

    tmp &= ~MFT_COMBINE_SYNCEN1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_COMBINE_SYNCEN1_SHIFT)) & MFT_COMBINE_SYNCEN1_MASK);
    obj->COMBINE = tmp;
}

/*! \brief Gets the Deadtime Enable For n = 2
 *
 * This function gets the current Deadtime Enable For n = 2.
 * Enables the deadtime insertion in the channels (n) and (n+1).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Deadtime Enable For n = 2
 *         - 0b : The deadtime insertion in this pair of channels is disabled.
 *         - 1b : The deadtime insertion in this pair of channels is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCombineDtEn1(const MftRegType *obj)
{
    return ((obj->COMBINE & MFT_COMBINE_DTEN1_MASK) >> MFT_COMBINE_DTEN1_SHIFT);
}

/*! \brief Sets the Deadtime Enable For n = 2
 *
 * This function sets the Deadtime Enable For n = 2.
 * Enables the deadtime insertion in the channels (n) and (n+1).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Deadtime Enable For n = 2
 *                    - 0b : The deadtime insertion in this pair of channels is disabled.
 *                    - 1b : The deadtime insertion in this pair of channels is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetCombineDtEn1(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->COMBINE;

    tmp &= ~MFT_COMBINE_DTEN1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_COMBINE_DTEN1_SHIFT)) & MFT_COMBINE_DTEN1_MASK);
    obj->COMBINE = tmp;
}

/*! \brief Gets the Dual Edge Capture Mode Captures For n = 2
 *
 * This function gets the current Dual Edge Capture Mode Captures For n = 2.
 * Enables the capture of the MFT counter value according to the channel (n) input event and the
 * configuration of the dual edge capture bits.
 * This field applies only when DECAPEN = 1.
 * DECAP bit is cleared automatically by hardware if dual edge capture ¨C one-shot mode is selected and
 * when the capture of channel (n+1) event is made.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Dual Edge Capture Mode Captures For n = 2
 *         - 0b : The dual edge captures are inactive.
 *         - 1b : The dual edge captures are active.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCombineDecap1(const MftRegType *obj)
{
    return ((obj->COMBINE & MFT_COMBINE_DECAP1_MASK) >> MFT_COMBINE_DECAP1_SHIFT);
}

/*! \brief Sets the Dual Edge Capture Mode Captures For n = 2
 *
 * This function sets the Dual Edge Capture Mode Captures For n = 2.
 * Enables the capture of the MFT counter value according to the channel (n) input event and the
 * configuration of the dual edge capture bits.
 * This field applies only when DECAPEN = 1.
 * DECAP bit is cleared automatically by hardware if dual edge capture ¨C one-shot mode is selected and
 * when the capture of channel (n+1) event is made.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Dual Edge Capture Mode Captures For n = 2
 *                    - 0b : The dual edge captures are inactive.
 *                    - 1b : The dual edge captures are active.
 */
__attribute__((always_inline)) static inline void MftReg_SetCombineDecap1(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->COMBINE;

    tmp &= ~MFT_COMBINE_DECAP1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_COMBINE_DECAP1_SHIFT)) & MFT_COMBINE_DECAP1_MASK);
    obj->COMBINE = tmp;
}

/*! \brief Gets the Dual Edge Capture Mode Enable For n = 2
 *
 * This function gets the current Dual Edge Capture Mode Enable For n = 2.
 * Enables the Dual Edge Capture mode in the channels (n) and (n+1).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Dual Edge Capture Mode Enable For n = 2
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCombineDecapEn1(const MftRegType *obj)
{
    return ((obj->COMBINE & MFT_COMBINE_DECAPEN1_MASK) >> MFT_COMBINE_DECAPEN1_SHIFT);
}

/*! \brief Sets the Dual Edge Capture Mode Enable For n = 2
 *
 * This function sets the Dual Edge Capture Mode Enable For n = 2.
 * Enables the Dual Edge Capture mode in the channels (n) and (n+1).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Dual Edge Capture Mode Enable For n = 2
 */
__attribute__((always_inline)) static inline void MftReg_SetCombineDecapEn1(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->COMBINE;

    tmp &= ~MFT_COMBINE_DECAPEN1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_COMBINE_DECAPEN1_SHIFT)) & MFT_COMBINE_DECAPEN1_MASK);
    obj->COMBINE = tmp;
}

/*! \brief Gets the Complement Of Channel (n) for n = 2
 *
 * This function gets the current Complement Of Channel (n) for n = 2.
 * In Complementary mode the channel (n+1) output is the inverse of the channel (n) output.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Complement Of Channel (n) for n = 2
 *         - 0b : If the channels (n) and (n+1) are in Combine Mode or Modified Combine PWM Mode,
 *                the channel (n+1) output is the same as the channel (n) output.
 *                If the channel (n+1) is in Output Compare Mode, EPWM or CPWM,
 *                the channel (n+1) output is independent from channel (n) output.
 *         - 1b : The channel (n+1) output is the complement of the channel (n) output.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCombineComp1(const MftRegType *obj)
{
    return ((obj->COMBINE & MFT_COMBINE_COMP1_MASK) >> MFT_COMBINE_COMP1_SHIFT);
}

/*! \brief Sets the Complement Of Channel (n) for n = 2
 *
 * This function sets the Complement Of Channel (n) for n = 2.
 * In Complementary mode the channel (n+1) output is the inverse of the channel (n) output.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Complement Of Channel (n) for n = 2
 *                    - 0b : If the channels (n) and (n+1) are in Combine Mode or Modified Combine PWM Mode,
 *                           the channel (n+1) output is the same as the channel (n) output.
 *                           If the channel (n+1) is in Output Compare Mode, EPWM or CPWM,
 *                           the channel (n+1) output is independent from channel (n) output.
 *                    - 1b : The channel (n+1) output is the complement of the channel (n) output.
 */
__attribute__((always_inline)) static inline void MftReg_SetCombineComp1(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->COMBINE;

    tmp &= ~MFT_COMBINE_COMP1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_COMBINE_COMP1_SHIFT)) & MFT_COMBINE_COMP1_MASK);
    obj->COMBINE = tmp;
}

/*! \brief Gets the Combine Channels For n = 2
 *
 * This function gets the current Combine Channels For n = 2.
 * Used on the selection of the combine mode for channels (n) and (n+1).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Combine Channels For n = 2
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCombineCombine1(const MftRegType *obj)
{
    return ((obj->COMBINE & MFT_COMBINE_COMBINE1_MASK) >> MFT_COMBINE_COMBINE1_SHIFT);
}

/*! \brief Sets the Combine Channels For n = 2
 *
 * This function sets the Combine Channels For n = 2.
 * Used on the selection of the combine mode for channels (n) and (n+1).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Combine Channels For n = 2
 */
__attribute__((always_inline)) static inline void MftReg_SetCombineCombine1(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->COMBINE;

    tmp &= ~MFT_COMBINE_COMBINE1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_COMBINE_COMBINE1_SHIFT)) & MFT_COMBINE_COMBINE1_MASK);
    obj->COMBINE = tmp;
}

/*! \brief Gets the Modified Combine Mode For n = 0
 *
 * This function gets the current Modified Combine Mode For n = 0.
 * Used on the selection of the modified combine mode for channels (n) and (n+1).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Modified Combine Mode For n = 0
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCombineMCombine0(const MftRegType *obj)
{
    return ((obj->COMBINE & MFT_COMBINE_MCOMBINE0_MASK) >> MFT_COMBINE_MCOMBINE0_SHIFT);
}

/*! \brief Sets the Modified Combine Mode For n = 0
 *
 * This function sets the Modified Combine Mode For n = 0.
 * Used on the selection of the modified combine mode for channels (n) and (n+1).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Modified Combine Mode For n = 0
 */
__attribute__((always_inline)) static inline void MftReg_SetCombineMCombine0(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->COMBINE;

    tmp &= ~MFT_COMBINE_MCOMBINE0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_COMBINE_MCOMBINE0_SHIFT)) & MFT_COMBINE_MCOMBINE0_MASK);
    obj->COMBINE = tmp;
}

/*! \brief Gets the Fault Control Enable For n = 0
 *
 * This function gets the current Fault Control Enable For n = 0.
 * Enables the fault control in channels (n) and (n+1).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Fault Control Enable For n = 0
 *         - 0b : The fault control in this pair of channels is disabled.
 *         - 1b : The fault control in this pair of channels is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCombineFaultEn0(const MftRegType *obj)
{
    return ((obj->COMBINE & MFT_COMBINE_FAULTEN0_MASK) >> MFT_COMBINE_FAULTEN0_SHIFT);
}

/*! \brief Sets the Fault Control Enable For n = 0
 *
 * This function sets the Fault Control Enable For n = 0.
 * Enables the fault control in channels (n) and (n+1).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Fault Control Enable For n = 0
 *                    - 0b : The fault control in this pair of channels is disabled.
 *                    - 1b : The fault control in this pair of channels is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetCombineFaultEn0(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->COMBINE;

    tmp &= ~MFT_COMBINE_FAULTEN0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_COMBINE_FAULTEN0_SHIFT)) & MFT_COMBINE_FAULTEN0_MASK);
    obj->COMBINE = tmp;
}

/*! \brief Gets the Synchronization Enable For n = 0
 *
 * This function gets the current Synchronization Enable For n = 0.
 * Enables PWM synchronization of registers C(n)V and C(n+1)V.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Synchronization Enable For n = 0
 *         - 0b : The PWM synchronization in this pair of channels is disabled.
 *         - 1b : The PWM synchronization in this pair of channels is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCombineSyncEn0(const MftRegType *obj)
{
    return ((obj->COMBINE & MFT_COMBINE_SYNCEN0_MASK) >> MFT_COMBINE_SYNCEN0_SHIFT);
}

/*! \brief Sets the Synchronization Enable For n = 0
 *
 * This function sets the Synchronization Enable For n = 0.
 * Enables PWM synchronization of registers C(n)V and C(n+1)V.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Synchronization Enable For n = 0
 *                    - 0b : The PWM synchronization in this pair of channels is disabled.
 *                    - 1b : The PWM synchronization in this pair of channels is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetCombineSyncEn0(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->COMBINE;

    tmp &= ~MFT_COMBINE_SYNCEN0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_COMBINE_SYNCEN0_SHIFT)) & MFT_COMBINE_SYNCEN0_MASK);
    obj->COMBINE = tmp;
}

/*! \brief Gets the Deadtime Enable For n = 0
 *
 * This function gets the current Deadtime Enable For n = 0.
 * Enables the deadtime insertion in the channels (n) and (n+1).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Deadtime Enable For n = 0
 *         - 0b : The deadtime insertion in this pair of channels is disabled.
 *         - 1b : The deadtime insertion in this pair of channels is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCombineDtEn0(const MftRegType *obj)
{
    return ((obj->COMBINE & MFT_COMBINE_DTEN0_MASK) >> MFT_COMBINE_DTEN0_SHIFT);
}

/*! \brief Sets the Deadtime Enable For n = 0
 *
 * This function sets the Deadtime Enable For n = 0.
 * Enables the deadtime insertion in the channels (n) and (n+1).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Deadtime Enable For n = 0
 *                    - 0b : The deadtime insertion in this pair of channels is disabled.
 *                    - 1b : The deadtime insertion in this pair of channels is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetCombineDtEn0(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->COMBINE;

    tmp &= ~MFT_COMBINE_DTEN0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_COMBINE_DTEN0_SHIFT)) & MFT_COMBINE_DTEN0_MASK);
    obj->COMBINE = tmp;
}

/*! \brief Gets the Dual Edge Capture Mode Captures For n = 0
 *
 * This function gets the current Dual Edge Capture Mode Captures For n = 0.
 * Enables the capture of the MFT counter value according to the channel (n) input event and the
 * configuration of the dual edge capture bits.
 * This field applies only when DECAPEN = 1.
 * DECAP bit is cleared automatically by hardware if dual edge capture ¨C one-shot mode is selected and
 * when the capture of channel (n+1) event is made.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Dual Edge Capture Mode Captures For n = 0
 *         - 0b : The dual edge captures are inactive.
 *         - 1b : The dual edge captures are active.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCombineDecap0(const MftRegType *obj)
{
    return ((obj->COMBINE & MFT_COMBINE_DECAP0_MASK) >> MFT_COMBINE_DECAP0_SHIFT);
}

/*! \brief Sets the Dual Edge Capture Mode Captures For n = 0
 *
 * This function sets the Dual Edge Capture Mode Captures For n = 0.
 * Enables the capture of the MFT counter value according to the channel (n) input event and the
 * configuration of the dual edge capture bits.
 * This field applies only when DECAPEN = 1.
 * DECAP bit is cleared automatically by hardware if dual edge capture ¨C one-shot mode is selected and
 * when the capture of channel (n+1) event is made.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Dual Edge Capture Mode Captures For n = 0
 *                    - 0b : The dual edge captures are inactive.
 *                    - 1b : The dual edge captures are active.
 */
__attribute__((always_inline)) static inline void MftReg_SetCombineDecap0(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->COMBINE;

    tmp &= ~MFT_COMBINE_DECAP0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_COMBINE_DECAP0_SHIFT)) & MFT_COMBINE_DECAP0_MASK);
    obj->COMBINE = tmp;
}

/*! \brief Gets the Dual Edge Capture Mode Enable For n = 0
 *
 * This function gets the current Dual Edge Capture Mode Enable For n = 0.
 * Enables the Dual Edge Capture mode in the channels (n) and (n+1).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Dual Edge Capture Mode Enable For n = 0
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCombineDecapEn0(const MftRegType *obj)
{
    return ((obj->COMBINE & MFT_COMBINE_DECAPEN0_MASK) >> MFT_COMBINE_DECAPEN0_SHIFT);
}

/*! \brief Sets the Dual Edge Capture Mode Enable For n = 0
 *
 * This function sets the Dual Edge Capture Mode Enable For n = 0.
 * Enables the Dual Edge Capture mode in the channels (n) and (n+1).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Dual Edge Capture Mode Enable For n = 0
 */
__attribute__((always_inline)) static inline void MftReg_SetCombineDecapEn0(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->COMBINE;

    tmp &= ~MFT_COMBINE_DECAPEN0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_COMBINE_DECAPEN0_SHIFT)) & MFT_COMBINE_DECAPEN0_MASK);
    obj->COMBINE = tmp;
}

/*! \brief Gets the Complement Of Channel (n) for n = 0
 *
 * This function gets the current Complement Of Channel (n) for n = 0.
 * In Complementary mode the channel (n+1) output is the inverse of the channel (n) output.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Complement Of Channel (n) for n = 0
 *         - 0b : If the channels (n) and (n+1) are in Combine Mode or Modified Combine PWM Mode,
 *                the channel (n+1) output is the same as the channel (n) output.
 *                If the channel (n+1) is in Output Compare Mode, EPWM or CPWM,
 *                the channel (n+1) output is independent from channel (n) output.
 *         - 1b : The channel (n+1) output is the complement of the channel (n) output.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCombineComp0(const MftRegType *obj)
{
    return ((obj->COMBINE & MFT_COMBINE_COMP0_MASK) >> MFT_COMBINE_COMP0_SHIFT);
}

/*! \brief Sets the Complement Of Channel (n) for n = 0
 *
 * This function sets the Complement Of Channel (n) for n = 0.
 * In Complementary mode the channel (n+1) output is the inverse of the channel (n) output.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Complement Of Channel (n) for n = 0
 *                    - 0b : If the channels (n) and (n+1) are in Combine Mode or Modified Combine PWM Mode,
 *                           the channel (n+1) output is the same as the channel (n) output.
 *                           If the channel (n+1) is in Output Compare Mode, EPWM or CPWM,
 *                           the channel (n+1) output is independent from channel (n) output.
 *                    - 1b : The channel (n+1) output is the complement of the channel (n) output.
 */
__attribute__((always_inline)) static inline void MftReg_SetCombineComp0(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->COMBINE;

    tmp &= ~MFT_COMBINE_COMP0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_COMBINE_COMP0_SHIFT)) & MFT_COMBINE_COMP0_MASK);
    obj->COMBINE = tmp;
}

/*! \brief Gets the Combine Channels For n = 0
 *
 * This function gets the current Combine Channels For n = 0.
 * Used on the selection of the combine mode for channels (n) and (n+1).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Combine Channels For n = 0
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCombineCombine0(const MftRegType *obj)
{
    return ((obj->COMBINE & MFT_COMBINE_COMBINE0_MASK) >> MFT_COMBINE_COMBINE0_SHIFT);
}

/*! \brief Sets the Combine Channels For n = 0
 *
 * This function sets the Combine Channels For n = 0.
 * Used on the selection of the combine mode for channels (n) and (n+1).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Combine Channels For n = 0
 */
__attribute__((always_inline)) static inline void MftReg_SetCombineCombine0(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->COMBINE;

    tmp &= ~MFT_COMBINE_COMBINE0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_COMBINE_COMBINE0_SHIFT)) & MFT_COMBINE_COMBINE0_MASK);
    obj->COMBINE = tmp;
}

/*! \brief Gets the Extended Deadtime Value
 *
 * This function gets the current Extended Deadtime Value.
 * This field is a bit extension of the DTVAL field. It defines the 4 most significant bits of the deadtime value.
 * The maximum deadtime value is extended to 1023 using the concatenation {DTVALEX, DTVAL}.
 * Deadtime insert value = (DTPS * {DTVALEX, DTVAL}).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \note If full compatibility is needed with previous software versions, write 0 to DTVALEX bits
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Extended Deadtime Value
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetDeadTimeDtValEx(const MftRegType *obj)
{
    return ((obj->DEADTIME & MFT_DEADTIME_DTVALEX_MASK) >> MFT_DEADTIME_DTVALEX_SHIFT);
}

/*! \brief Sets the Extended Deadtime Value
 *
 * This function sets the Extended Deadtime Value.
 * This field is a bit extension of the DTVAL field. It defines the 4 most significant bits of the deadtime value.
 * The maximum deadtime value is extended to 1023 using the concatenation {DTVALEX, DTVAL}.
 * Deadtime insert value = (DTPS * {DTVALEX, DTVAL}).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \note If full compatibility is needed with previous software versions, write 0 to DTVALEX bits
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Extended Deadtime Value
 */
__attribute__((always_inline)) static inline void MftReg_SetDeadTimeDtValEx(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->DEADTIME;

    tmp &= ~MFT_DEADTIME_DTVALEX_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_DEADTIME_DTVALEX_SHIFT)) & MFT_DEADTIME_DTVALEX_MASK);
    obj->DEADTIME = tmp;
}

/*! \brief Gets the Deadtime Prescaler Value
 *
 * This function gets the current Deadtime Prescaler Value.
 * Selects the division factor of the MFT input clock. This prescaled clock is used by the deadtime counter.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Deadtime Prescaler Value
 *         - 0xb : Divide the MFT input clock by 1.
 *         - 10b : Divide the MFT input clock by 4.
 *         - 11b : Divide the MFT input clock by 16.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetDeadTimeDtPs(const MftRegType *obj)
{
    return ((obj->DEADTIME & MFT_DEADTIME_DTPS_MASK) >> MFT_DEADTIME_DTPS_SHIFT);
}

/*! \brief Sets the Deadtime Prescaler Value
 *
 * This function sets the Deadtime Prescaler Value.
 * Selects the division factor of the MFT input clock. This prescaled clock is used by the deadtime counter.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Deadtime Prescaler Value
 *                    - 0xb : Divide the MFT input clock by 1.
 *                    - 10b : Divide the MFT input clock by 4.
 *                    - 11b : Divide the MFT input clock by 16.
 */
__attribute__((always_inline)) static inline void MftReg_SetDeadTimeDtPs(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->DEADTIME;

    tmp &= ~MFT_DEADTIME_DTPS_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_DEADTIME_DTPS_SHIFT)) & MFT_DEADTIME_DTPS_MASK);
    obj->DEADTIME = tmp;
}

/*! \brief Gets the Deadtime Value
 *
 * This function gets the current Deadtime Value.
 * Selects the deadtime value.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Deadtime Value
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetDeadTimeDtVal(const MftRegType *obj)
{
    return ((obj->DEADTIME & MFT_DEADTIME_DTVAL_MASK) >> MFT_DEADTIME_DTVAL_SHIFT);
}

/*! \brief Sets the Deadtime Value
 *
 * This function sets the Deadtime Value.
 * Selects the deadtime value.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Deadtime Value
 */
__attribute__((always_inline)) static inline void MftReg_SetDeadTimeDtVal(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->DEADTIME;

    tmp &= ~MFT_DEADTIME_DTVAL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_DEADTIME_DTVAL_SHIFT)) & MFT_DEADTIME_DTVAL_MASK);
    obj->DEADTIME = tmp;
}

/*! \brief Gets the Channel 7 External Trigger Enable
 *
 * This function gets the current Channel 7 External Trigger Enable.
 * Enables the generation of the external trigger when MFT counter = C2V.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 7 External Trigger Enable
 *         - 0b : The generation of this external trigger is disabled.
 *         - 1b : The generation of this external trigger is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetExtTrigCh7Trig(const MftRegType *obj)
{
    return ((obj->EXTTRIG & MFT_EXTTRIG_CH7TRIG_MASK) >> MFT_EXTTRIG_CH7TRIG_SHIFT);
}

/*! \brief Sets the Channel 7 External Trigger Enable
 *
 * This function sets the Channel 7 External Trigger Enable.
 * Enables the generation of the external trigger when MFT counter = C2V.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 7 External Trigger Enable
 *                    - 0b : The generation of this external trigger is disabled.
 *                    - 1b : The generation of this external trigger is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetExtTrigCh7Trig(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->EXTTRIG;

    tmp &= ~MFT_EXTTRIG_CH7TRIG_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_EXTTRIG_CH7TRIG_SHIFT)) & MFT_EXTTRIG_CH7TRIG_MASK);
    obj->EXTTRIG = tmp;
}

/*! \brief Gets the Channel 6 External Trigger Enable
 *
 * This function gets the current Channel 6 External Trigger Enable.
 * Enables the generation of the external trigger when MFT counter = C2V.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 6 External Trigger Enable
 *         - 0b : The generation of this external trigger is disabled.
 *         - 1b : The generation of this external trigger is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetExtTrigCh6Trig(const MftRegType *obj)
{
    return ((obj->EXTTRIG & MFT_EXTTRIG_CH6TRIG_MASK) >> MFT_EXTTRIG_CH6TRIG_SHIFT);
}

/*! \brief Sets the Channel 6 External Trigger Enable
 *
 * This function sets the Channel 6 External Trigger Enable.
 * Enables the generation of the external trigger when MFT counter = C2V.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 6 External Trigger Enable
 *                    - 0b : The generation of this external trigger is disabled.
 *                    - 1b : The generation of this external trigger is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetExtTrigCh6Trig(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->EXTTRIG;

    tmp &= ~MFT_EXTTRIG_CH6TRIG_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_EXTTRIG_CH6TRIG_SHIFT)) & MFT_EXTTRIG_CH6TRIG_MASK);
    obj->EXTTRIG = tmp;
}

/*! \brief Gets the Channel Trigger Flag
 *
 * This function gets the current Channel Trigger Flag.
 * Set by hardware when a channel trigger is generated.
 * Clear TRIGF by reading EXTTRIG while TRIGF is set and then writing a 0 to TRIGF.
 * Writing a 1 to TRIGF has no effect.
 * If another channel trigger is generated before the clearing sequence is completed,
 * the sequence is reset so TRIGF remains set after the clear sequence is completed for the earlier TRIGF.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel Trigger Flag
 *         - 0b : No channel trigger was generated.
 *         - 1b : A channel trigger was generated.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetExtTrigTrigF(const MftRegType *obj)
{
    return ((obj->EXTTRIG & MFT_EXTTRIG_TRIGF_MASK) >> MFT_EXTTRIG_TRIGF_SHIFT);
}

/*! \brief Sets the Channel Trigger Flag
 *
 * This function sets the Channel Trigger Flag.
 * Set by hardware when a channel trigger is generated.
 * Clear TRIGF by reading EXTTRIG while TRIGF is set and then writing a 0 to TRIGF.
 * Writing a 1 to TRIGF has no effect.
 * If another channel trigger is generated before the clearing sequence is completed,
 * the sequence is reset so TRIGF remains set after the clear sequence is completed for the earlier TRIGF.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel Trigger Flag
 *                    - 0b : clear the flag
 *                    - 1b : no effect
 */
__attribute__((always_inline)) static inline void MftReg_SetExtTrigTrigF(MftRegType *obj, uint8_t value)
{
    /* Write 1 has no effect */
    if(value != 0)
    {
        return;
    }

    uint32_t tmp = obj->EXTTRIG;

    tmp &= ~MFT_EXTTRIG_TRIGF_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_EXTTRIG_TRIGF_SHIFT)) & MFT_EXTTRIG_TRIGF_MASK);
    obj->EXTTRIG = tmp;
}

/*! \brief Gets the Initialization Trigger Enable
 *
 * This function gets the current Initialization Trigger Enable.
 * Enables the generation of the trigger when the MFT counter is equal to the CNTIN register.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Initialization Trigger Enable
 *         - 0b : The generation of initialization trigger is disabled.
 *         - 1b : The generation of initialization trigger is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetExtTrigInitTrigEn(const MftRegType *obj)
{
    return ((obj->EXTTRIG & MFT_EXTTRIG_INITTRIGEN_MASK) >> MFT_EXTTRIG_INITTRIGEN_SHIFT);
}

/*! \brief Sets the Initialization Trigger Enable
 *
 * This function sets the Initialization Trigger Enable.
 * Enables the generation of the trigger when the MFT counter is equal to the CNTIN register.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Initialization Trigger Enable
 *                    - 0b : The generation of initialization trigger is disabled.
 *                    - 1b : The generation of initialization trigger is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetExtTrigInitTrigEn(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->EXTTRIG;

    tmp &= ~MFT_EXTTRIG_INITTRIGEN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_EXTTRIG_INITTRIGEN_SHIFT)) & MFT_EXTTRIG_INITTRIGEN_MASK);
    obj->EXTTRIG = tmp;
}

/*! \brief Gets the Channel 1 External Trigger Enable
 *
 * This function gets the current Channel 1 External Trigger Enable.
 * Enables the generation of the external trigger when MFT counter = C2V.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 1 External Trigger Enable
 *         - 0b : The generation of this external trigger is disabled.
 *         - 1b : The generation of this external trigger is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetExtTrigCh1Trig(const MftRegType *obj)
{
    return ((obj->EXTTRIG & MFT_EXTTRIG_CH1TRIG_MASK) >> MFT_EXTTRIG_CH1TRIG_SHIFT);
}

/*! \brief Sets the Channel 1 External Trigger Enable
 *
 * This function sets the Channel 1 External Trigger Enable.
 * Enables the generation of the external trigger when MFT counter = C2V.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 1 External Trigger Enable
 *                    - 0b : The generation of this external trigger is disabled.
 *                    - 1b : The generation of this external trigger is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetExtTrigCh1Trig(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->EXTTRIG;

    tmp &= ~MFT_EXTTRIG_CH1TRIG_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_EXTTRIG_CH1TRIG_SHIFT)) & MFT_EXTTRIG_CH1TRIG_MASK);
    obj->EXTTRIG = tmp;
}

/*! \brief Gets the Channel 0 External Trigger Enable
 *
 * This function gets the current Channel 0 External Trigger Enable.
 * Enables the generation of the external trigger when MFT counter = C2V.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 0 External Trigger Enable
 *         - 0b : The generation of this external trigger is disabled.
 *         - 1b : The generation of this external trigger is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetExtTrigCh0Trig(const MftRegType *obj)
{
    return ((obj->EXTTRIG & MFT_EXTTRIG_CH0TRIG_MASK) >> MFT_EXTTRIG_CH0TRIG_SHIFT);
}

/*! \brief Sets the Channel 0 External Trigger Enable
 *
 * This function sets the Channel 0 External Trigger Enable.
 * Enables the generation of the external trigger when MFT counter = C2V.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 0 External Trigger Enable
 *                    - 0b : The generation of this external trigger is disabled.
 *                    - 1b : The generation of this external trigger is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetExtTrigCh0Trig(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->EXTTRIG;

    tmp &= ~MFT_EXTTRIG_CH0TRIG_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_EXTTRIG_CH0TRIG_SHIFT)) & MFT_EXTTRIG_CH0TRIG_MASK);
    obj->EXTTRIG = tmp;
}

/*! \brief Gets the Channel 5 External Trigger Enable
 *
 * This function gets the current Channel 5 External Trigger Enable.
 * Enables the generation of the external trigger when MFT counter = C2V.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 5 External Trigger Enable
 *         - 0b : The generation of this external trigger is disabled.
 *         - 1b : The generation of this external trigger is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetExtTrigCh5Trig(const MftRegType *obj)
{
    return ((obj->EXTTRIG & MFT_EXTTRIG_CH5TRIG_MASK) >> MFT_EXTTRIG_CH5TRIG_SHIFT);
}

/*! \brief Sets the Channel 5 External Trigger Enable
 *
 * This function sets the Channel 5 External Trigger Enable.
 * Enables the generation of the external trigger when MFT counter = C2V.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 5 External Trigger Enable
 *                    - 0b : The generation of this external trigger is disabled.
 *                    - 1b : The generation of this external trigger is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetExtTrigCh5Trig(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->EXTTRIG;

    tmp &= ~MFT_EXTTRIG_CH5TRIG_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_EXTTRIG_CH5TRIG_SHIFT)) & MFT_EXTTRIG_CH5TRIG_MASK);
    obj->EXTTRIG = tmp;
}

/*! \brief Gets the Channel 4 External Trigger Enable
 *
 * This function gets the current Channel 4 External Trigger Enable.
 * Enables the generation of the external trigger when MFT counter = C2V.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 4 External Trigger Enable
 *         - 0b : The generation of this external trigger is disabled.
 *         - 1b : The generation of this external trigger is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetExtTrigCh4Trig(const MftRegType *obj)
{
    return ((obj->EXTTRIG & MFT_EXTTRIG_CH4TRIG_MASK) >> MFT_EXTTRIG_CH4TRIG_SHIFT);
}

/*! \brief Sets the Channel 4 External Trigger Enable
 *
 * This function sets the Channel 4 External Trigger Enable.
 * Enables the generation of the external trigger when MFT counter = C2V.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 4 External Trigger Enable
 *                    - 0b : The generation of this external trigger is disabled.
 *                    - 1b : The generation of this external trigger is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetExtTrigCh4Trig(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->EXTTRIG;

    tmp &= ~MFT_EXTTRIG_CH4TRIG_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_EXTTRIG_CH4TRIG_SHIFT)) & MFT_EXTTRIG_CH4TRIG_MASK);
    obj->EXTTRIG = tmp;
}

/*! \brief Gets the Channel 3 External Trigger Enable
 *
 * This function gets the current Channel 3 External Trigger Enable.
 * Enables the generation of the external trigger when MFT counter = C2V.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 3 External Trigger Enable
 *         - 0b : The generation of this external trigger is disabled.
 *         - 1b : The generation of this external trigger is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetExtTrigCh3Trig(const MftRegType *obj)
{
    return ((obj->EXTTRIG & MFT_EXTTRIG_CH3TRIG_MASK) >> MFT_EXTTRIG_CH3TRIG_SHIFT);
}

/*! \brief Sets the Channel 3 External Trigger Enable
 *
 * This function sets the Channel 3 External Trigger Enable.
 * Enables the generation of the external trigger when MFT counter = C2V.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 3 External Trigger Enable
 *                    - 0b : The generation of this external trigger is disabled.
 *                    - 1b : The generation of this external trigger is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetExtTrigCh3Trig(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->EXTTRIG;

    tmp &= ~MFT_EXTTRIG_CH3TRIG_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_EXTTRIG_CH3TRIG_SHIFT)) & MFT_EXTTRIG_CH3TRIG_MASK);
    obj->EXTTRIG = tmp;
}

/*! \brief Gets the Channel 2 External Trigger Enable
 *
 * This function gets the current Channel 2 External Trigger Enable.
 * Enables the generation of the external trigger when MFT counter = C2V.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 2 External Trigger Enable
 *         - 0b : The generation of this external trigger is disabled.
 *         - 1b : The generation of this external trigger is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetExtTrigCh2Trig(const MftRegType *obj)
{
    return ((obj->EXTTRIG & MFT_EXTTRIG_CH2TRIG_MASK) >> MFT_EXTTRIG_CH2TRIG_SHIFT);
}

/*! \brief Sets the Channel 2 External Trigger Enable
 *
 * This function sets the Channel 2 External Trigger Enable.
 * Enables the generation of the external trigger when MFT counter = C2V.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 2 External Trigger Enable
 *                    - 0b : The generation of this external trigger is disabled.
 *                    - 1b : The generation of this external trigger is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetExtTrigCh2Trig(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->EXTTRIG;

    tmp &= ~MFT_EXTTRIG_CH2TRIG_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_EXTTRIG_CH2TRIG_SHIFT)) & MFT_EXTTRIG_CH2TRIG_MASK);
    obj->EXTTRIG = tmp;
}

/*! \brief Gets the Channel 7 Polarity
 *
 * This function gets the current Channel 7 Polarity.
 * Defines the polarity of the channel output.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 7 Polarity
 *         - 0b : The channel polarity is active high.
 *         - 1b : The channel polarity is active low.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetPolPol7(const MftRegType *obj)
{
    return ((obj->POL & MFT_POL_POL7_MASK) >> MFT_POL_POL7_SHIFT);
}

/*! \brief Sets the Channel 7 Polarity
 *
 * This function sets the Channel 7 Polarity.
 * Defines the polarity of the channel output.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 7 Polarity
 *                    - 0b : The channel polarity is active high.
 *                    - 1b : The channel polarity is active low.
 */
__attribute__((always_inline)) static inline void MftReg_SetPolPol7(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->POL;

    tmp &= ~MFT_POL_POL7_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_POL_POL7_SHIFT)) & MFT_POL_POL7_MASK);
    obj->POL = tmp;
}

/*! \brief Gets the Channel 6 Polarity
 *
 * This function gets the current Channel 6 Polarity.
 * Defines the polarity of the channel output.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 6 Polarity
 *         - 0b : The channel polarity is active high.
 *         - 1b : The channel polarity is active low.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetPolPol6(const MftRegType *obj)
{
    return ((obj->POL & MFT_POL_POL6_MASK) >> MFT_POL_POL6_SHIFT);
}

/*! \brief Sets the Channel 6 Polarity
 *
 * This function sets the Channel 6 Polarity.
 * Defines the polarity of the channel output.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 6 Polarity
 *                    - 0b : The channel polarity is active high.
 *                    - 1b : The channel polarity is active low.
 */
__attribute__((always_inline)) static inline void MftReg_SetPolPol6(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->POL;

    tmp &= ~MFT_POL_POL6_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_POL_POL6_SHIFT)) & MFT_POL_POL6_MASK);
    obj->POL = tmp;
}

/*! \brief Gets the Channel 5 Polarity
 *
 * This function gets the current Channel 5 Polarity.
 * Defines the polarity of the channel output.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 5 Polarity
 *         - 0b : The channel polarity is active high.
 *         - 1b : The channel polarity is active low.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetPolPol5(const MftRegType *obj)
{
    return ((obj->POL & MFT_POL_POL5_MASK) >> MFT_POL_POL5_SHIFT);
}

/*! \brief Sets the Channel 5 Polarity
 *
 * This function sets the Channel 5 Polarity.
 * Defines the polarity of the channel output.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 5 Polarity
 *                    - 0b : The channel polarity is active high.
 *                    - 1b : The channel polarity is active low.
 */
__attribute__((always_inline)) static inline void MftReg_SetPolPol5(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->POL;

    tmp &= ~MFT_POL_POL5_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_POL_POL5_SHIFT)) & MFT_POL_POL5_MASK);
    obj->POL = tmp;
}

/*! \brief Gets the Channel 4 Polarity
 *
 * This function gets the current Channel 4 Polarity.
 * Defines the polarity of the channel output.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 4 Polarity
 *         - 0b : The channel polarity is active high.
 *         - 1b : The channel polarity is active low.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetPolPol4(const MftRegType *obj)
{
    return ((obj->POL & MFT_POL_POL4_MASK) >> MFT_POL_POL4_SHIFT);
}

/*! \brief Sets the Channel 4 Polarity
 *
 * This function sets the Channel 4 Polarity.
 * Defines the polarity of the channel output.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 4 Polarity
 *                    - 0b : The channel polarity is active high.
 *                    - 1b : The channel polarity is active low.
 */
__attribute__((always_inline)) static inline void MftReg_SetPolPol4(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->POL;

    tmp &= ~MFT_POL_POL4_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_POL_POL4_SHIFT)) & MFT_POL_POL4_MASK);
    obj->POL = tmp;
}

/*! \brief Gets the Channel 3 Polarity
 *
 * This function gets the current Channel 3 Polarity.
 * Defines the polarity of the channel output.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 3 Polarity
 *         - 0b : The channel polarity is active high.
 *         - 1b : The channel polarity is active low.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetPolPol3(const MftRegType *obj)
{
    return ((obj->POL & MFT_POL_POL3_MASK) >> MFT_POL_POL3_SHIFT);
}

/*! \brief Sets the Channel 3 Polarity
 *
 * This function sets the Channel 3 Polarity.
 * Defines the polarity of the channel output.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 3 Polarity
 *                    - 0b : The channel polarity is active high.
 *                    - 1b : The channel polarity is active low.
 */
__attribute__((always_inline)) static inline void MftReg_SetPolPol3(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->POL;

    tmp &= ~MFT_POL_POL3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_POL_POL3_SHIFT)) & MFT_POL_POL3_MASK);
    obj->POL = tmp;
}

/*! \brief Gets the Channel 2 Polarity
 *
 * This function gets the current Channel 2 Polarity.
 * Defines the polarity of the channel output.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 2 Polarity
 *         - 0b : The channel polarity is active high.
 *         - 1b : The channel polarity is active low.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetPolPol2(const MftRegType *obj)
{
    return ((obj->POL & MFT_POL_POL2_MASK) >> MFT_POL_POL2_SHIFT);
}

/*! \brief Sets the Channel 2 Polarity
 *
 * This function sets the Channel 2 Polarity.
 * Defines the polarity of the channel output.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 2 Polarity
 *                    - 0b : The channel polarity is active high.
 *                    - 1b : The channel polarity is active low.
 */
__attribute__((always_inline)) static inline void MftReg_SetPolPol2(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->POL;

    tmp &= ~MFT_POL_POL2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_POL_POL2_SHIFT)) & MFT_POL_POL2_MASK);
    obj->POL = tmp;
}

/*! \brief Gets the Channel 1 Polarity
 *
 * This function gets the current Channel 1 Polarity.
 * Defines the polarity of the channel output.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 1 Polarity
 *         - 0b : The channel polarity is active high.
 *         - 1b : The channel polarity is active low.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetPolPol1(const MftRegType *obj)
{
    return ((obj->POL & MFT_POL_POL1_MASK) >> MFT_POL_POL1_SHIFT);
}

/*! \brief Sets the Channel 1 Polarity
 *
 * This function sets the Channel 1 Polarity.
 * Defines the polarity of the channel output.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 1 Polarity
 *                    - 0b : The channel polarity is active high.
 *                    - 1b : The channel polarity is active low.
 */
__attribute__((always_inline)) static inline void MftReg_SetPolPol1(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->POL;

    tmp &= ~MFT_POL_POL1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_POL_POL1_SHIFT)) & MFT_POL_POL1_MASK);
    obj->POL = tmp;
}

/*! \brief Gets the Channel 0 Polarity
 *
 * This function gets the current Channel 0 Polarity.
 * Defines the polarity of the channel output.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 0 Polarity
 *         - 0b : The channel polarity is active high.
 *         - 1b : The channel polarity is active low.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetPolPol0(const MftRegType *obj)
{
    return ((obj->POL & MFT_POL_POL0_MASK) >> MFT_POL_POL0_SHIFT);
}

/*! \brief Sets the Channel 0 Polarity
 *
 * This function sets the Channel 0 Polarity.
 * Defines the polarity of the channel output.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 0 Polarity
 *                    - 0b : The channel polarity is active high.
 *                    - 1b : The channel polarity is active low.
 */
__attribute__((always_inline)) static inline void MftReg_SetPolPol0(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->POL;

    tmp &= ~MFT_POL_POL0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_POL_POL0_SHIFT)) & MFT_POL_POL0_MASK);
    obj->POL = tmp;
}

/*! \brief Gets the Fault Detection Flag
 *
 * This function gets the current Fault Detection Flag.
 * Represents the logic OR of the FAULTF bit of each enabled fault input.
 * Clear FAULTF by reading the FMS register while FAULTF is set and then writing a 0 to FAULTF
 * while there is no existing fault condition at the enabled fault inputs. Writing a 1 to FAULTF has no effect.
 * If another fault condition is detected in an enabled fault input before the clearing sequence is completed,
 * the sequence is reset so FAULTF remains set after the clearing sequence is completed for the earlier fault condition.
 * FAULTF is also cleared when FAULTF bit of each enabled fault input is cleared.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Fault Detection Flag
 *         - 0b : No fault condition was detected.
 *         - 1b : A fault condition was detected.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetFmsFaultF(const MftRegType *obj)
{
    return ((obj->FMS & MFT_FMS_FAULTF_MASK) >> MFT_FMS_FAULTF_SHIFT);
}

/*! \brief Sets the Fault Detection Flag
 *
 * This function sets the Fault Detection Flag.
 * Represents the logic OR of the FAULTF bit of each enabled fault input.
 * Clear FAULTF by reading the FMS register while FAULTF is set and then writing a 0 to FAULTF
 * while there is no existing fault condition at the enabled fault inputs. Writing a 1 to FAULTF has no effect.
 * If another fault condition is detected in an enabled fault input before the clearing sequence is completed,
 * the sequence is reset so FAULTF remains set after the clearing sequence is completed for the earlier fault condition.
 * FAULTF is also cleared when FAULTF bit of each enabled fault input is cleared.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Fault Detection Flag
 *                    - 0b : clear the flag
 *                    - 1b : no effect
 */
__attribute__((always_inline)) static inline void MftReg_SetFmsFaultF(MftRegType *obj, uint8_t value)
{
    /* Write 1 has no effect */
    if(value != 0)
    {
        return;
    }

    uint32_t tmp = obj->FMS;

    tmp &= ~MFT_FMS_FAULTF_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_FMS_FAULTF_SHIFT)) & MFT_FMS_FAULTF_MASK);
    obj->FMS = tmp;
    /* Read back to avoid problem */
    (void)obj->FMS;
}

/*! \brief Gets the Write Protection Enable
 *
 * This function gets the current Write Protection Enable.
 * The WPEN bit is the negation of the WPDIS bit. WPEN is set when 1 is written to it. WPEN is cleared
 * when WPEN bit is read as a 1 and then 1 is written to WPDIS. Writing 0 to WPEN has no effect.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Write Protection Enable
 *         - 0b : Write protection is disabled. Write protected bits can be written.
 *         - 1b : Write protection is enabled. Write protected bits cannot be written.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetFmsWpEn(const MftRegType *obj)
{
    return ((obj->FMS & MFT_FMS_WPEN_MASK) >> MFT_FMS_WPEN_SHIFT);
}

/*! \brief Sets the Write Protection Enable
 *
 * This function sets the Write Protection Enable.
 * The WPEN bit is the negation of the WPDIS bit. WPEN is set when 1 is written to it. WPEN is cleared
 * when WPEN bit is read as a 1 and then 1 is written to WPDIS. Writing 0 to WPEN has no effect.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Write Protection Enable
 *                    - 0b : Write protection is disabled. Write protected bits can be written.
 *                    - 1b : Write protection is enabled. Write protected bits cannot be written.
 */
__attribute__((always_inline)) static inline void MftReg_SetFmsWpEn(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->FMS;

    tmp &= ~MFT_FMS_WPEN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_FMS_WPEN_SHIFT)) & MFT_FMS_WPEN_MASK);
    obj->FMS = tmp;
}

/*! \brief Gets the Fault Inputs
 *
 * This function gets the current Fault Inputs.
 * Represents the logic OR of the enabled fault inputs after their filter (if their filter is enabled)
 * when fault control is enabled.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Fault Inputs
 *         - 0b : The logic OR of the enabled fault inputs is 0.
 *         - 1b : The logic OR of the enabled fault inputs is 1.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetFmsFaultIn(const MftRegType *obj)
{
    return ((obj->FMS & MFT_FMS_FAULTIN_MASK) >> MFT_FMS_FAULTIN_SHIFT);
}

/*! \brief Gets the Fault Detection Flag 3
 *
 * This function gets the current Fault Detection Flag 3.
 * Set by hardware when fault control is enabled,
 * the corresponding fault input is enabled and a fault condition is detected at the fault input.
 * Clear FAULTF3 by reading the FMS register while FAULTF3 is set and then writing a 0 to FAULTF3
 * while there is no existing fault condition at the corresponding fault input. Writing a 1 to FAULTF3 has no effect.
 * FAULTF3 bit is also cleared when FAULTF bit is cleared.
 * If another fault condition is detected at the corresponding fault input before the clearing sequence is completed,
 * the sequence is reset so FAULTF3 remains set after the clearing sequence is completed for the earlier fault condition
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Fault Detection Flag 3
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetFmsFaultF3(const MftRegType *obj)
{
    return ((obj->FMS & MFT_FMS_FAULTF3_MASK) >> MFT_FMS_FAULTF3_SHIFT);
}

/*! \brief Sets the Fault Detection Flag 3
 *
 * This function sets the Fault Detection Flag 3.
 * Set by hardware when fault control is enabled,
 * the corresponding fault input is enabled and a fault condition is detected at the fault input.
 * Clear FAULTF3 by reading the FMS register while FAULTF3 is set and then writing a 0 to FAULTF3
 * while there is no existing fault condition at the corresponding fault input. Writing a 1 to FAULTF3 has no effect.
 * FAULTF3 bit is also cleared when FAULTF bit is cleared.
 * If another fault condition is detected at the corresponding fault input before the clearing sequence is completed,
 * the sequence is reset so FAULTF3 remains set after the clearing sequence is completed for the earlier fault condition
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Fault Detection Flag 3
 *                    - 0b : clear the flag
 *                    - 1b : no effect
 */
__attribute__((always_inline)) static inline void MftReg_SetFmsFaultF3(MftRegType *obj, uint8_t value)
{
    /* Write 1 has no effect */
    if(value != 0)
    {
        return;
    }

    uint32_t tmp = obj->FMS;

    tmp &= ~MFT_FMS_FAULTF3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_FMS_FAULTF3_SHIFT)) & MFT_FMS_FAULTF3_MASK);
    obj->FMS = tmp;
    /* Read back to avoid problem */
    (void)obj->FMS;
}

/*! \brief Gets the Fault Detection Flag 2
 *
 * This function gets the current Fault Detection Flag 2.
 * Set by hardware when fault control is enabled,
 * the corresponding fault input is enabled and a fault condition is detected at the fault input.
 * Clear FAULTF2 by reading the FMS register while FAULTF2 is set and then writing a 0 to FAULTF2
 * while there is no existing fault condition at the corresponding fault input. Writing a 1 to FAULTF2 has no effect.
 * FAULTF2 bit is also cleared when FAULTF bit is cleared.
 * If another fault condition is detected at the corresponding fault input before the clearing sequence is completed,
 * the sequence is reset so FAULTF2 remains set after the clearing sequence is completed for the earlier fault condition
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Fault Detection Flag 2
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetFmsFaultF2(const MftRegType *obj)
{
    return ((obj->FMS & MFT_FMS_FAULTF2_MASK) >> MFT_FMS_FAULTF2_SHIFT);
}

/*! \brief Sets the Fault Detection Flag 2
 *
 * This function sets the Fault Detection Flag 2.
 * Set by hardware when fault control is enabled,
 * the corresponding fault input is enabled and a fault condition is detected at the fault input.
 * Clear FAULTF2 by reading the FMS register while FAULTF2 is set and then writing a 0 to FAULTF2
 * while there is no existing fault condition at the corresponding fault input. Writing a 1 to FAULTF2 has no effect.
 * FAULTF2 bit is also cleared when FAULTF bit is cleared.
 * If another fault condition is detected at the corresponding fault input before the clearing sequence is completed,
 * the sequence is reset so FAULTF2 remains set after the clearing sequence is completed for the earlier fault condition
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Fault Detection Flag 2
 *                    - 0b : clear the flag
 *                    - 1b : no effect
 */
__attribute__((always_inline)) static inline void MftReg_SetFmsFaultF2(MftRegType *obj, uint8_t value)
{
    /* Write 1 has no effect */
    if(value != 0)
    {
        return;
    }

    uint32_t tmp = obj->FMS;

    tmp &= ~MFT_FMS_FAULTF2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_FMS_FAULTF2_SHIFT)) & MFT_FMS_FAULTF2_MASK);
    obj->FMS = tmp;
    /* Read back to avoid problem */
    (void)obj->FMS;
}

/*! \brief Gets the Fault Detection Flag 1
 *
 * This function gets the current Fault Detection Flag 1.
 * Set by hardware when fault control is enabled,
 * the corresponding fault input is enabled and a fault condition is detected at the fault input.
 * Clear FAULTF1 by reading the FMS register while FAULTF1 is set and then writing a 0 to FAULTF1
 * while there is no existing fault condition at the corresponding fault input. Writing a 1 to FAULTF1 has no effect.
 * FAULTF1 bit is also cleared when FAULTF bit is cleared.
 * If another fault condition is detected at the corresponding fault input before the clearing sequence is completed,
 * the sequence is reset so FAULTF1 remains set after the clearing sequence is completed for the earlier fault condition
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Fault Detection Flag 1
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetFmsFaultF1(const MftRegType *obj)
{
    return ((obj->FMS & MFT_FMS_FAULTF1_MASK) >> MFT_FMS_FAULTF1_SHIFT);
}

/*! \brief Sets the Fault Detection Flag 1
 *
 * This function sets the Fault Detection Flag 1.
 * Set by hardware when fault control is enabled,
 * the corresponding fault input is enabled and a fault condition is detected at the fault input.
 * Clear FAULTF1 by reading the FMS register while FAULTF1 is set and then writing a 0 to FAULTF1
 * while there is no existing fault condition at the corresponding fault input. Writing a 1 to FAULTF1 has no effect.
 * FAULTF1 bit is also cleared when FAULTF bit is cleared.
 * If another fault condition is detected at the corresponding fault input before the clearing sequence is completed,
 * the sequence is reset so FAULTF1 remains set after the clearing sequence is completed for the earlier fault condition
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Fault Detection Flag 1
 *                    - 0b : clear the flag
 *                    - 1b : no effect
 */
__attribute__((always_inline)) static inline void MftReg_SetFmsFaultF1(MftRegType *obj, uint8_t value)
{
    /* Write 1 has no effect */
    if(value != 0)
    {
        return;
    }

    uint32_t tmp = obj->FMS;

    tmp &= ~MFT_FMS_FAULTF1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_FMS_FAULTF1_SHIFT)) & MFT_FMS_FAULTF1_MASK);
    obj->FMS = tmp;
    /* Read back to avoid problem */
    (void)obj->FMS;
}

/*! \brief Gets the Fault Detection Flag 0
 *
 * This function gets the current Fault Detection Flag 0.
 * Set by hardware when fault control is enabled,
 * the corresponding fault input is enabled and a fault condition is detected at the fault input.
 * Clear FAULTF0 by reading the FMS register while FAULTF0 is set and then writing a 0 to FAULTF0
 * while there is no existing fault condition at the corresponding fault input. Writing a 1 to FAULTF0 has no effect.
 * FAULTF0 bit is also cleared when FAULTF bit is cleared.
 * If another fault condition is detected at the corresponding fault input before the clearing sequence is completed,
 * the sequence is reset so FAULTF0 remains set after the clearing sequence is completed for the earlier fault condition
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Fault Detection Flag 0
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetFmsFaultF0(const MftRegType *obj)
{
    return ((obj->FMS & MFT_FMS_FAULTF0_MASK) >> MFT_FMS_FAULTF0_SHIFT);
}

/*! \brief Sets the Fault Detection Flag 0
 *
 * This function sets the Fault Detection Flag 0.
 * Set by hardware when fault control is enabled,
 * the corresponding fault input is enabled and a fault condition is detected at the fault input.
 * Clear FAULTF0 by reading the FMS register while FAULTF0 is set and then writing a 0 to FAULTF0
 * while there is no existing fault condition at the corresponding fault input. Writing a 1 to FAULTF0 has no effect.
 * FAULTF0 bit is also cleared when FAULTF bit is cleared.
 * If another fault condition is detected at the corresponding fault input before the clearing sequence is completed,
 * the sequence is reset so FAULTF0 remains set after the clearing sequence is completed for the earlier fault condition
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Fault Detection Flag 0
 *                    - 0b : clear the flag
 *                    - 1b : no effect
 */
__attribute__((always_inline)) static inline void MftReg_SetFmsFaultF0(MftRegType *obj, uint8_t value)
{
    /* Write 1 has no effect */
    if(value != 0)
    {
        return;
    }

    uint32_t tmp = obj->FMS;

    tmp &= ~MFT_FMS_FAULTF0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_FMS_FAULTF0_SHIFT)) & MFT_FMS_FAULTF0_MASK);
    obj->FMS = tmp;
    /* Read back to avoid problem */
    (void)obj->FMS;
}

/*! \brief Gets the Channel 3 Input Filter
 *
 * This function gets the current Channel 3 Input Filter.
 * Selects the filter value for the channel input.
 * The filter is disabled when the value is zero
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 3 Input Filter
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetFilterCh3FVal(const MftRegType *obj)
{
    return ((obj->FILTER & MFT_FILTER_CH3FVAL_MASK) >> MFT_FILTER_CH3FVAL_SHIFT);
}

/*! \brief Sets the Channel 3 Input Filter
 *
 * This function sets the Channel 3 Input Filter.
 * Selects the filter value for the channel input.
 * The filter is disabled when the value is zero
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 3 Input Filter
 */
__attribute__((always_inline)) static inline void MftReg_SetFilterCh3FVal(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->FILTER;

    tmp &= ~MFT_FILTER_CH3FVAL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_FILTER_CH3FVAL_SHIFT)) & MFT_FILTER_CH3FVAL_MASK);
    obj->FILTER = tmp;
}

/*! \brief Gets the Channel 2 Input Filter
 *
 * This function gets the current Channel 2 Input Filter.
 * Selects the filter value for the channel input.
 * The filter is disabled when the value is zero
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 2 Input Filter
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetFilterCh2FVal(const MftRegType *obj)
{
    return ((obj->FILTER & MFT_FILTER_CH2FVAL_MASK) >> MFT_FILTER_CH2FVAL_SHIFT);
}

/*! \brief Sets the Channel 2 Input Filter
 *
 * This function sets the Channel 2 Input Filter.
 * Selects the filter value for the channel input.
 * The filter is disabled when the value is zero
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 2 Input Filter
 */
__attribute__((always_inline)) static inline void MftReg_SetFilterCh2FVal(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->FILTER;

    tmp &= ~MFT_FILTER_CH2FVAL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_FILTER_CH2FVAL_SHIFT)) & MFT_FILTER_CH2FVAL_MASK);
    obj->FILTER = tmp;
}

/*! \brief Gets the Channel 1 Input Filter
 *
 * This function gets the current Channel 1 Input Filter.
 * Selects the filter value for the channel input.
 * The filter is disabled when the value is zero
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 1 Input Filter
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetFilterCh1FVal(const MftRegType *obj)
{
    return ((obj->FILTER & MFT_FILTER_CH1FVAL_MASK) >> MFT_FILTER_CH1FVAL_SHIFT);
}

/*! \brief Sets the Channel 1 Input Filter
 *
 * This function sets the Channel 1 Input Filter.
 * Selects the filter value for the channel input.
 * The filter is disabled when the value is zero
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 1 Input Filter
 */
__attribute__((always_inline)) static inline void MftReg_SetFilterCh1FVal(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->FILTER;

    tmp &= ~MFT_FILTER_CH1FVAL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_FILTER_CH1FVAL_SHIFT)) & MFT_FILTER_CH1FVAL_MASK);
    obj->FILTER = tmp;
}

/*! \brief Gets the Channel 0 Input Filter
 *
 * This function gets the current Channel 0 Input Filter.
 * Selects the filter value for the channel input.
 * The filter is disabled when the value is zero
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 0 Input Filter
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetFilterCh0FVal(const MftRegType *obj)
{
    return ((obj->FILTER & MFT_FILTER_CH0FVAL_MASK) >> MFT_FILTER_CH0FVAL_SHIFT);
}

/*! \brief Sets the Channel 0 Input Filter
 *
 * This function sets the Channel 0 Input Filter.
 * Selects the filter value for the channel input.
 * The filter is disabled when the value is zero
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 0 Input Filter
 */
__attribute__((always_inline)) static inline void MftReg_SetFilterCh0FVal(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->FILTER;

    tmp &= ~MFT_FILTER_CH0FVAL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_FILTER_CH0FVAL_SHIFT)) & MFT_FILTER_CH0FVAL_MASK);
    obj->FILTER = tmp;
}

/*! \brief Gets the Fault output state
 *
 * This function gets the current Fault output state.
 * This configuration allows to put the MFT outputs tri-stated when a fault event is ongoing.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Fault output state
 *         - 0b : MFT outputs will be placed into safe values when fault events in ongoing (defined by POL bits).
 *         - 1b : MFT outputs will be tri-stated when fault event is ongoing
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetFltCtrlFstate(const MftRegType *obj)
{
    return ((obj->FLTCTRL & MFT_FLTCTRL_FSTATE_MASK) >> MFT_FLTCTRL_FSTATE_SHIFT);
}

/*! \brief Sets the Fault output state
 *
 * This function sets the Fault output state.
 * This configuration allows to put the MFT outputs tri-stated when a fault event is ongoing.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Fault output state
 *                    - 0b : MFT outputs will be placed into safe values when fault events in ongoing (defined by POL bits).
 *                    - 1b : MFT outputs will be tri-stated when fault event is ongoing
 */
__attribute__((always_inline)) static inline void MftReg_SetFltCtrlFstate(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->FLTCTRL;

    tmp &= ~MFT_FLTCTRL_FSTATE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_FLTCTRL_FSTATE_SHIFT)) & MFT_FLTCTRL_FSTATE_MASK);
    obj->FLTCTRL = tmp;
}

/*! \brief Gets the Fault Input Filter
 *
 * This function gets the current Fault Input Filter.
 * Selects the filter value for the fault inputs.
 * The fault filter is disabled when the value is zero.
 *
 * \note Writing to this field has immediate effect and must be done only when the fault contro
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Fault Input Filter
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetFltCtrlFFVal(const MftRegType *obj)
{
    return ((obj->FLTCTRL & MFT_FLTCTRL_FFVAL_MASK) >> MFT_FLTCTRL_FFVAL_SHIFT);
}

/*! \brief Sets the Fault Input Filter
 *
 * This function sets the Fault Input Filter.
 * Selects the filter value for the fault inputs.
 * The fault filter is disabled when the value is zero.
 *
 * \note Writing to this field has immediate effect and must be done only when the fault contro
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Fault Input Filter
 */
__attribute__((always_inline)) static inline void MftReg_SetFltCtrlFFVal(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->FLTCTRL;

    tmp &= ~MFT_FLTCTRL_FFVAL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_FLTCTRL_FFVAL_SHIFT)) & MFT_FLTCTRL_FFVAL_MASK);
    obj->FLTCTRL = tmp;
}

/*! \brief Gets the Fault Input 3 Filter Enable
 *
 * This function gets the current Fault Input 3 Filter Enable.
 * Enables the filter for the fault input.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Fault Input 3 Filter Enable
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetFltCtrlFFltr3En(const MftRegType *obj)
{
    return ((obj->FLTCTRL & MFT_FLTCTRL_FFLTR3EN_MASK) >> MFT_FLTCTRL_FFLTR3EN_SHIFT);
}

/*! \brief Sets the Fault Input 3 Filter Enable
 *
 * This function sets the Fault Input 3 Filter Enable.
 * Enables the filter for the fault input.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Fault Input 3 Filter Enable
 */
__attribute__((always_inline)) static inline void MftReg_SetFltCtrlFFltr3En(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->FLTCTRL;

    tmp &= ~MFT_FLTCTRL_FFLTR3EN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_FLTCTRL_FFLTR3EN_SHIFT)) & MFT_FLTCTRL_FFLTR3EN_MASK);
    obj->FLTCTRL = tmp;
}

/*! \brief Gets the Fault Input 2 Filter Enable
 *
 * This function gets the current Fault Input 2 Filter Enable.
 * Enables the filter for the fault input.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Fault Input 2 Filter Enable
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetFltCtrlFFltr2En(const MftRegType *obj)
{
    return ((obj->FLTCTRL & MFT_FLTCTRL_FFLTR2EN_MASK) >> MFT_FLTCTRL_FFLTR2EN_SHIFT);
}

/*! \brief Sets the Fault Input 2 Filter Enable
 *
 * This function sets the Fault Input 2 Filter Enable.
 * Enables the filter for the fault input.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Fault Input 2 Filter Enable
 */
__attribute__((always_inline)) static inline void MftReg_SetFltCtrlFFltr2En(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->FLTCTRL;

    tmp &= ~MFT_FLTCTRL_FFLTR2EN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_FLTCTRL_FFLTR2EN_SHIFT)) & MFT_FLTCTRL_FFLTR2EN_MASK);
    obj->FLTCTRL = tmp;
}

/*! \brief Gets the Fault Input 1 Filter Enable
 *
 * This function gets the current Fault Input 1 Filter Enable.
 * Enables the filter for the fault input.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Fault Input 1 Filter Enable
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetFltCtrlFFltr1En(const MftRegType *obj)
{
    return ((obj->FLTCTRL & MFT_FLTCTRL_FFLTR1EN_MASK) >> MFT_FLTCTRL_FFLTR1EN_SHIFT);
}

/*! \brief Sets the Fault Input 1 Filter Enable
 *
 * This function sets the Fault Input 1 Filter Enable.
 * Enables the filter for the fault input.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Fault Input 1 Filter Enable
 */
__attribute__((always_inline)) static inline void MftReg_SetFltCtrlFFltr1En(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->FLTCTRL;

    tmp &= ~MFT_FLTCTRL_FFLTR1EN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_FLTCTRL_FFLTR1EN_SHIFT)) & MFT_FLTCTRL_FFLTR1EN_MASK);
    obj->FLTCTRL = tmp;
}

/*! \brief Gets the Fault Input 0 Filter Enable
 *
 * This function gets the current Fault Input 0 Filter Enable.
 * Enables the filter for the fault input.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Fault Input 0 Filter Enable
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetFltCtrlFFltr0En(const MftRegType *obj)
{
    return ((obj->FLTCTRL & MFT_FLTCTRL_FFLTR0EN_MASK) >> MFT_FLTCTRL_FFLTR0EN_SHIFT);
}

/*! \brief Sets the Fault Input 0 Filter Enable
 *
 * This function sets the Fault Input 0 Filter Enable.
 * Enables the filter for the fault input.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Fault Input 0 Filter Enable
 */
__attribute__((always_inline)) static inline void MftReg_SetFltCtrlFFltr0En(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->FLTCTRL;

    tmp &= ~MFT_FLTCTRL_FFLTR0EN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_FLTCTRL_FFLTR0EN_SHIFT)) & MFT_FLTCTRL_FFLTR0EN_MASK);
    obj->FLTCTRL = tmp;
}

/*! \brief Gets the Fault Input 3 Filter Enable
 *
 * This function gets the current Fault Input 3 Filter Enable.
 * Enables the filter for the fault input.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Fault Input 3 Filter Enable
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetFltCtrlFault3En(const MftRegType *obj)
{
    return ((obj->FLTCTRL & MFT_FLTCTRL_FAULT3EN_MASK) >> MFT_FLTCTRL_FAULT3EN_SHIFT);
}

/*! \brief Sets the Fault Input 3 Filter Enable
 *
 * This function sets the Fault Input 3 Filter Enable.
 * Enables the filter for the fault input.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Fault Input 3 Filter Enable
 */
__attribute__((always_inline)) static inline void MftReg_SetFltCtrlFault3En(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->FLTCTRL;

    tmp &= ~MFT_FLTCTRL_FAULT3EN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_FLTCTRL_FAULT3EN_SHIFT)) & MFT_FLTCTRL_FAULT3EN_MASK);
    obj->FLTCTRL = tmp;
}

/*! \brief Gets the Fault Input 2 Filter Enable
 *
 * This function gets the current Fault Input 2 Filter Enable.
 * Enables the filter for the fault input.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Fault Input 2 Filter Enable
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetFltCtrlFault2En(const MftRegType *obj)
{
    return ((obj->FLTCTRL & MFT_FLTCTRL_FAULT2EN_MASK) >> MFT_FLTCTRL_FAULT2EN_SHIFT);
}

/*! \brief Sets the Fault Input 2 Filter Enable
 *
 * This function sets the Fault Input 2 Filter Enable.
 * Enables the filter for the fault input.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Fault Input 2 Filter Enable
 */
__attribute__((always_inline)) static inline void MftReg_SetFltCtrlFault2En(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->FLTCTRL;

    tmp &= ~MFT_FLTCTRL_FAULT2EN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_FLTCTRL_FAULT2EN_SHIFT)) & MFT_FLTCTRL_FAULT2EN_MASK);
    obj->FLTCTRL = tmp;
}

/*! \brief Gets the Fault Input 1 Filter Enable
 *
 * This function gets the current Fault Input 1 Filter Enable.
 * Enables the filter for the fault input.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Fault Input 1 Filter Enable
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetFltCtrlFault1En(const MftRegType *obj)
{
    return ((obj->FLTCTRL & MFT_FLTCTRL_FAULT1EN_MASK) >> MFT_FLTCTRL_FAULT1EN_SHIFT);
}

/*! \brief Sets the Fault Input 1 Filter Enable
 *
 * This function sets the Fault Input 1 Filter Enable.
 * Enables the filter for the fault input.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Fault Input 1 Filter Enable
 */
__attribute__((always_inline)) static inline void MftReg_SetFltCtrlFault1En(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->FLTCTRL;

    tmp &= ~MFT_FLTCTRL_FAULT1EN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_FLTCTRL_FAULT1EN_SHIFT)) & MFT_FLTCTRL_FAULT1EN_MASK);
    obj->FLTCTRL = tmp;
}

/*! \brief Gets the Fault Input 0 Filter Enable
 *
 * This function gets the current Fault Input 0 Filter Enable.
 * Enables the filter for the fault input.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Fault Input 0 Filter Enable
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetFltCtrlFault0En(const MftRegType *obj)
{
    return ((obj->FLTCTRL & MFT_FLTCTRL_FAULT0EN_MASK) >> MFT_FLTCTRL_FAULT0EN_SHIFT);
}

/*! \brief Sets the Fault Input 0 Filter Enable
 *
 * This function sets the Fault Input 0 Filter Enable.
 * Enables the filter for the fault input.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Fault Input 0 Filter Enable
 */
__attribute__((always_inline)) static inline void MftReg_SetFltCtrlFault0En(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->FLTCTRL;

    tmp &= ~MFT_FLTCTRL_FAULT0EN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_FLTCTRL_FAULT0EN_SHIFT)) & MFT_FLTCTRL_FAULT0EN_MASK);
    obj->FLTCTRL = tmp;
}

/*! \brief Gets the Phase Z Input Filter Enable
 *
 * This function gets the current Phase Z Input Filter Enable.
 * Enables the filter for the quadrature decoder phase Z input.
 * The filter value for the phase Z input is defined by the CH0FVAL field of FILTER.
 * The phase Z filter is also disabled when CH0FVAL is zero
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Phase Z Input Filter Enable
 *         - 0 : disable
 *         - 1 : enable
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetQDCtrlPhzFltrEn(const MftRegType *obj)
{
    return ((obj->QDCTRL & MFT_QDCTRL_PHZFLTREN_MASK) >> MFT_QDCTRL_PHZFLTREN_SHIFT);
}

/*! \brief Sets the Phase Z Input Filter Enable
 *
 * This function sets the Phase Z Input Filter Enable.
 * Enables the filter for the quadrature decoder phase Z input.
 * The filter value for the phase Z input is defined by the CH0FVAL field of FILTER.
 * The phase Z filter is also disabled when CH0FVAL is zero
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Phase Z Input Filter Enable
 *                    - 0 : disable
 *                    - 1 : enable
 */
__attribute__((always_inline)) static inline void MftReg_SetQDCtrlPhzFltrEn(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->QDCTRL;

    tmp &= ~MFT_QDCTRL_PHZFLTREN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_QDCTRL_PHZFLTREN_SHIFT)) & MFT_QDCTRL_PHZFLTREN_MASK);
    obj->QDCTRL = tmp;
}

/*! \brief Gets the Phase Z Input Polarity
 *
 * This function gets the current Phase Z Input Polarity.
 * Selects the polarity for the quadrature decoder phase Z input.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Phase A Input Polarity
 *         - 0b : Normal polarity. Phase Z input signal is not inverted
 *                before identifying the rising and falling edges of this signal.
 *         - 1b : Inverted polarity. Phase Z input signal is inverted
 *                before identifying the rising and falling edges of this signal.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetQDCtrlPhzPol(const MftRegType *obj)
{
    return ((obj->QDCTRL & MFT_QDCTRL_PHZPOL_MASK) >> MFT_QDCTRL_PHZPOL_SHIFT);
}

/*! \brief Sets the Phase Z Input Polarity
 *
 * This function sets the Phase Z Input Polarity.
 * Selects the polarity for the quadrature decoder phase Z input.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Phase Z Input Polarity
 *                    - 0b : Normal polarity. Phase Z input signal is not inverted
 *                           before identifying the rising and falling edges of this signal.
 *                    - 1b : Inverted polarity. Phase Z input signal is inverted
 *                           before identifying the rising and falling edges of this signal.
 */
__attribute__((always_inline)) static inline void MftReg_SetQDCtrlPhzPol(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->QDCTRL;

    tmp &= ~MFT_QDCTRL_PHZPOL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_QDCTRL_PHZPOL_SHIFT)) & MFT_QDCTRL_PHZPOL_MASK);
    obj->QDCTRL = tmp;
}

/*! \brief Gets the Phase Z Clearing Mode
 *
 * This function gets the Phase Z Clearing Mode.
 * Selects the condition in which phase Z input signal clears the counter. 
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Phase Z clear Mode
 *                    - 00b :  phase Z input does not reset the counter.
 *                    - 01b : every effective edge of phase Z input resets the counter
 *                            (Reseting does not happen immediately, but after the first or 
 *                             recorded phase A or phase B input edge).
 *                    - 10b : phase Z input resets the counter only once
 *                              (Reseting does not happen immediately, but after the first 
 *                              phase A or phase B input edge).
 *                    - 11b : Clear immediately when the effective edge of Phase Z signal comes.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetQDCtrlPhzClearMode(const MftRegType *obj)
{
    return ((obj->QDCTRL & MFT_QDCTRL_PHZMODE_MASK) >> MFT_QDCTRL_PHZMODE_SHIFT);
}

/*! \brief Sets the Phase Z Clearing Mode
 *
 * This function sets the Phase Z Clearing Mode.
 * Selects the condition in which phase Z input signal clears the counter. 
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Phase Z Clearing Mode
 *                    - 00b :  phase Z input does not reset the counter.
 *                    - 01b : every effective edge of phase Z input resets the counter
 *                            (Reseting does not happen immediately, but after the first or 
 *                             recorded phase A or phase B input edge).
 *                    - 10b : phase Z input resets the counter only once
 *                              (Reseting does not happen immediately, but after the first 
 *                              phase A or phase B input edge).
 *                    - 11b : Clear immediately when the effective edge of Phase Z signal comes.
 *
 */
__attribute__((always_inline)) static inline void MftReg_SetQDCtrlPhzClearMode(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->QDCTRL;

    tmp &= ~MFT_QDCTRL_PHZMODE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_QDCTRL_PHZMODE_SHIFT)) & MFT_QDCTRL_PHZMODE_MASK);
    obj->QDCTRL = tmp;
}

/*! \brief Gets the Phase Z First has occurred status
 *
 * This function gets the Phase Z First index pulse has occurred status.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Phase Z First occurred status
 *                    - 0b : phase Z clearing once has not happened
 *                    - 1b : phase Z clearing once has happened
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetQDCtrlPhzFirstHappened(const MftRegType *obj)
{
    return ((obj->QDCTRL & MFT_QDCTRL_PHZCOF_MASK) >> MFT_QDCTRL_PHZCOF_SHIFT);
}

/*! \brief Clear the Phase Z has occurred status
 *
 * This function clear the Phase Z First index pulse has occurred status.
 *
 * \param[in] obj : pointer to MFT register instance
 */
__attribute__((always_inline)) static inline void MftReg_ClearQDCtrlPhzFirstHappend(MftRegType *obj)
{
    uint32_t tmp = obj->QDCTRL;

    tmp &= ~MFT_QDCTRL_PHZCOF_MASK;
    tmp |= (((uint32_t)(((uint32_t)(1)) << MFT_QDCTRL_PHZCOF_SHIFT)) & MFT_QDCTRL_PHZCOF_MASK);
    obj->QDCTRL = tmp;
}

/*! \brief Gets the Phase A Input Filter Enable
 *
 * This function gets the current Phase A Input Filter Enable.
 * Enables the filter for the quadrature decoder phase A input.
 * The filter value for the phase A input is defined by the CH0FVAL field of FILTER.
 * The phase A filter is also disabled when CH0FVAL is zero
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Phase A Input Filter Enable
 *         - 0 : disable
 *         - 1 : enable
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetQDCtrlPhaFltrEn(const MftRegType *obj)
{
    return ((obj->QDCTRL & MFT_QDCTRL_PHAFLTREN_MASK) >> MFT_QDCTRL_PHAFLTREN_SHIFT);
}

/*! \brief Sets the Phase A Input Filter Enable
 *
 * This function sets the Phase A Input Filter Enable.
 * Enables the filter for the quadrature decoder phase A input.
 * The filter value for the phase A input is defined by the CH0FVAL field of FILTER.
 * The phase A filter is also disabled when CH0FVAL is zero
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Phase A Input Filter Enable
 *                    - 0 : disable
 *                    - 1 : enable
 */
__attribute__((always_inline)) static inline void MftReg_SetQDCtrlPhaFltrEn(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->QDCTRL;

    tmp &= ~MFT_QDCTRL_PHAFLTREN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_QDCTRL_PHAFLTREN_SHIFT)) & MFT_QDCTRL_PHAFLTREN_MASK);
    obj->QDCTRL = tmp;
}

/*! \brief Gets the Phase B Input Filter Enable
 *
 * This function gets the current Phase B Input Filter Enable.
 * Enables the filter for the quadrature decoder phase B input.
 * The filter value for the phase B input is defined by the CH1FVAL field of FILTER.
 * The phase B filter is also disabled when CH1FVAL is zero
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Phase B Input Filter Enable
 *         - 0 : disable
 *         - 1 : enable
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetQDCtrlPhbFltrEn(const MftRegType *obj)
{
    return ((obj->QDCTRL & MFT_QDCTRL_PHBFLTREN_MASK) >> MFT_QDCTRL_PHBFLTREN_SHIFT);
}

/*! \brief Sets the Phase B Input Filter Enable
 *
 * This function sets the Phase B Input Filter Enable.
 * Enables the filter for the quadrature decoder phase B input.
 * The filter value for the phase B input is defined by the CH1FVAL field of FILTER.
 * The phase B filter is also disabled when CH1FVAL is zero
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Phase B Input Filter Enable
 *                    - 0 : disable
 *                    - 1 : enable
 */
__attribute__((always_inline)) static inline void MftReg_SetQDCtrlPhbFltrEn(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->QDCTRL;

    tmp &= ~MFT_QDCTRL_PHBFLTREN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_QDCTRL_PHBFLTREN_SHIFT)) & MFT_QDCTRL_PHBFLTREN_MASK);
    obj->QDCTRL = tmp;
}

/*! \brief Gets the Phase A Input Polarity
 *
 * This function gets the current Phase A Input Polarity.
 * Selects the polarity for the quadrature decoder phase A input.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Phase A Input Polarity
 *         - 0b : Normal polarity. Phase A input signal is not inverted
 *                before identifying the rising and falling edges of this signal.
 *         - 1b : Inverted polarity. Phase A input signal is inverted
 *                before identifying the rising and falling edges of this signal.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetQDCtrlPhaPol(const MftRegType *obj)
{
    return ((obj->QDCTRL & MFT_QDCTRL_PHAPOL_MASK) >> MFT_QDCTRL_PHAPOL_SHIFT);
}

/*! \brief Sets the Phase A Input Polarity
 *
 * This function sets the Phase A Input Polarity.
 * Selects the polarity for the quadrature decoder phase A input.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Phase A Input Polarity
 *                    - 0b : Normal polarity. Phase A input signal is not inverted
 *                           before identifying the rising and falling edges of this signal.
 *                    - 1b : Inverted polarity. Phase A input signal is inverted
 *                           before identifying the rising and falling edges of this signal.
 */
__attribute__((always_inline)) static inline void MftReg_SetQDCtrlPhaPol(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->QDCTRL;

    tmp &= ~MFT_QDCTRL_PHAPOL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_QDCTRL_PHAPOL_SHIFT)) & MFT_QDCTRL_PHAPOL_MASK);
    obj->QDCTRL = tmp;
}

/*! \brief Gets the Phase B Input Polarity
 *
 * This function gets the current Phase B Input Polarity.
 * Selects the polarity for the quadrature decoder phase B input.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Phase B Input Polarity
 *         - 0b : Normal polarity. Phase B input signal is not inverted
 *                before identifying the rising and falling edges of this signal.
 *         - 1b : Inverted polarity. Phase B input signal is inverted
 *                before identifying the rising and falling edges of this signal.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetQDCtrlPhbPol(const MftRegType *obj)
{
    return ((obj->QDCTRL & MFT_QDCTRL_PHBPOL_MASK) >> MFT_QDCTRL_PHBPOL_SHIFT);
}

/*! \brief Sets the Phase B Input Polarity
 *
 * This function sets the Phase B Input Polarity.
 * Selects the polarity for the quadrature decoder phase B input.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Phase B Input Polarity
 *                    - 0b : Normal polarity. Phase B input signal is not inverted
 *                           before identifying the rising and falling edges of this signal.
 *                    - 1b : Inverted polarity. Phase B input signal is inverted
 *                           before identifying the rising and falling edges of this signal.
 */
__attribute__((always_inline)) static inline void MftReg_SetQDCtrlPhbPol(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->QDCTRL;

    tmp &= ~MFT_QDCTRL_PHBPOL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_QDCTRL_PHBPOL_SHIFT)) & MFT_QDCTRL_PHBPOL_MASK);
    obj->QDCTRL = tmp;
}

/*! \brief Gets the Quadrature Decoder Mode
 *
 * This function gets the current Quadrature Decoder Mode.
 * Selects the encoding mode used in the Quadrature Decoder mode.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Quadrature Decoder Mode
 *         - 0b : Phase A and phase B encoding mode.
 *         - 1b : Count and direction encoding mode.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetQDCtrlQuadMode(const MftRegType *obj)
{
    return ((obj->QDCTRL & MFT_QDCTRL_QUADMODE_MASK) >> MFT_QDCTRL_QUADMODE_SHIFT);
}

/*! \brief Sets the Quadrature Decoder Mode
 *
 * This function sets the Quadrature Decoder Mode.
 * Selects the encoding mode used in the Quadrature Decoder mode.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Quadrature Decoder Mode
 *                    - 0b : Phase A and phase B encoding mode.
 *                    - 1b : Count and direction encoding mode.
 */
__attribute__((always_inline)) static inline void MftReg_SetQDCtrlQuadMode(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->QDCTRL;

    tmp &= ~MFT_QDCTRL_QUADMODE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_QDCTRL_QUADMODE_SHIFT)) & MFT_QDCTRL_QUADMODE_MASK);
    obj->QDCTRL = tmp;
}

/*! \brief Gets the MFT Counter Direction In Quadrature Decoder Mode
 *
 * This function gets the current MFT Counter Direction In Quadrature Decoder Mode.
 * Indicates the counting direction.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return MFT Counter Direction In Quadrature Decoder Mode
 *         - 0b : Counting direction is decreasing (MFT counter decrement).
 *         - 1b : Counting direction is increasing (MFT counter increment).
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetQDCtrlQuaDir(const MftRegType *obj)
{
    return ((obj->QDCTRL & MFT_QDCTRL_QUADIR_MASK) >> MFT_QDCTRL_QUADIR_SHIFT);
}

/*! \brief Gets the Timer Overflow Direction In Quadrature Decoder Mode
 *
 * This function gets the current Timer Overflow Direction In Quadrature Decoder Mode.
 * Indicates if the TOF bit was set on the top or the bottom of counting.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Timer Overflow Direction In Quadrature Decoder Mode
 *         - 0b : TOF bit was set on the bottom of counting.
 *                There was an MFT counter decrement and MFT counter changes
 *                from its minimum value (CNTIN register) to its maximum value (MOD register).
 *         - 1b : TOF bit was set on the top of counting.
 *                There was an MFT counter increment and MFT counter changes
 *                from its maximum value (MOD register) to its minimum value (CNTIN register).
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetQDCtrlTorDir(const MftRegType *obj)
{
    return ((obj->QDCTRL & MFT_QDCTRL_TOFDIR_MASK) >> MFT_QDCTRL_TOFDIR_SHIFT);
}

/*! \brief Gets the Quadrature Decoder Mode Enable
 *
 * This function gets the current Quadrature Decoder Mode Enable.
 * Enables the Quadrature Decoder mode.
 * In this mode, the phase A and B input signals control the MFT counter direction.
 * The Quadrature Decoder mode has precedence over the other modes.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Quadrature Decoder Mode Enable
 *         - 0b : Quadrature Decoder mode is disabled.
 *         - 1b : Quadrature Decoder mode is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetQDCtrlQuadEn(const MftRegType *obj)
{
    return ((obj->QDCTRL & MFT_QDCTRL_QUADEN_MASK) >> MFT_QDCTRL_QUADEN_SHIFT);
}

/*! \brief Sets the Quadrature Decoder Mode Enable
 *
 * This function sets the Quadrature Decoder Mode Enable.
 * Enables the Quadrature Decoder mode.
 * In this mode, the phase A and B input signals control the MFT counter direction.
 * The Quadrature Decoder mode has precedence over the other modes.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Quadrature Decoder Mode Enable
 *                    - 0b : Quadrature Decoder mode is disabled.
 *                    - 1b : Quadrature Decoder mode is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetQDCtrlQuadEn(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->QDCTRL;

    tmp &= ~MFT_QDCTRL_QUADEN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_QDCTRL_QUADEN_SHIFT)) & MFT_QDCTRL_QUADEN_MASK);
    obj->QDCTRL = tmp;
}

/*! \brief Gets the Initialization trigger on Reload Point
 *
 * This function gets the current Initialization trigger on Reload Point.
 * This bit controls whether an initialization trigger is generated when a reload point configured by
 * PWMLOAD register is reached considering the MFT_CONF[LDFQ] settings.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Initialization trigger on Reload Point
 *         - 0b : Initialization trigger is generated on counter wrap events.
 *         - 1b : Initialization trigger is generated when a reload point is reached.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetConfITrigR(const MftRegType *obj)
{
    return ((obj->CONF & MFT_CONF_ITRIGR_MASK) >> MFT_CONF_ITRIGR_SHIFT);
}

/*! \brief Sets the Initialization trigger on Reload Point
 *
 * This function sets the Initialization trigger on Reload Point.
 * This bit controls whether an initialization trigger is generated when a reload point configured by
 * PWMLOAD register is reached considering the MFT_CONF[LDFQ] settings.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Initialization trigger on Reload Point
 *                    - 0b : Initialization trigger is generated on counter wrap events.
 *                    - 1b : Initialization trigger is generated when a reload point is reached.
 */
__attribute__((always_inline)) static inline void MftReg_SetConfITrigR(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CONF;

    tmp &= ~MFT_CONF_ITRIGR_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_CONF_ITRIGR_SHIFT)) & MFT_CONF_ITRIGR_MASK);
    obj->CONF = tmp;
}

/*! \brief Gets the Global Time Base Output
 *
 * This function gets the current Global Time Base Output.
 * Enables the global time base signal generation to other MFTs.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Global Time Base Output
 *         - 0b : A global time base signal generation is disabled.
 *         - 1b : A global time base signal generation is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetConfGtbeOut(const MftRegType *obj)
{
    return ((obj->CONF & MFT_CONF_GTBEOUT_MASK) >> MFT_CONF_GTBEOUT_SHIFT);
}

/*! \brief Sets the Global Time Base Output
 *
 * This function sets the Global Time Base Output.
 * Enables the global time base signal generation to other MFTs.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Global Time Base Output
 *                    - 0b : A global time base signal generation is disabled.
 *                    - 1b : A global time base signal generation is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetConfGtbeOut(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CONF;

    tmp &= ~MFT_CONF_GTBEOUT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_CONF_GTBEOUT_SHIFT)) & MFT_CONF_GTBEOUT_MASK);
    obj->CONF = tmp;
}

/*! \brief Gets the Global Time Base Enable
 *
 * This function gets the current Global Time Base Enable.
 * Configures the MFT to use an external global time base signal that is generated by another MFT.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Global Time Base Enable
 *         - 0b : Use of an external global time base is disabled.
 *         - 1b : Use of an external global time base is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetConfGtbeEn(const MftRegType *obj)
{
    return ((obj->CONF & MFT_CONF_GTBEEN_MASK) >> MFT_CONF_GTBEEN_SHIFT);
}

/*! \brief Sets the Global Time Base Enable
 *
 * This function sets the Global Time Base Enable.
 * Configures the MFT to use an external global time base signal that is generated by another MFT.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Global Time Base Enable
 *                    - 0b : Use of an external global time base is disabled.
 *                    - 1b : Use of an external global time base is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetConfGtbeEn(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CONF;

    tmp &= ~MFT_CONF_GTBEEN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_CONF_GTBEEN_SHIFT)) & MFT_CONF_GTBEEN_MASK);
    obj->CONF = tmp;
}

/*! \brief Gets the Debug Mode
 *
 * This function gets the current Debug Mode.
 * Selects the MFT behavior in Debug mod
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Debug Mode
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetConfBdmMode(const MftRegType *obj)
{
    return ((obj->CONF & MFT_CONF_BDMMODE_MASK) >> MFT_CONF_BDMMODE_SHIFT);
}

/*! \brief Sets the Debug Mode
 *
 * This function sets the Debug Mode.
 * Selects the MFT behavior in Debug mod
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Debug Mode
 */
__attribute__((always_inline)) static inline void MftReg_SetConfBdmMode(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CONF;

    tmp &= ~MFT_CONF_BDMMODE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_CONF_BDMMODE_SHIFT)) & MFT_CONF_BDMMODE_MASK);
    obj->CONF = tmp;
}

/*! \brief Gets the Frequency of the Reload Opportunities
 *
 * This function gets the current Frequency of the Reload Opportunities.
 * The LDFQ[4:0] bits define the number of enabled reload opportunities should happen
 * until an enabled reload opportunity becomes a reload point. See Reload Points
 * LDFQ = 0: All reload opportunities are reload points.
 * LDFQ = 1: There is a reload point each 2 reload oportunities.
 * LDFQ = 2: There is a reload point each 3 reload oportunities.
 * LDFQ = 3: There is a reload point each 4 reload oportunities.
 * This pattern continues up to a maximum of 32
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Frequency of the Reload Opportunities
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetConfLdfq(const MftRegType *obj)
{
    return ((obj->CONF & MFT_CONF_LDFQ_MASK) >> MFT_CONF_LDFQ_SHIFT);
}

/*! \brief Sets the Frequency of the Reload Opportunities
 *
 * This function sets the Frequency of the Reload Opportunities.
 * The LDFQ[4:0] bits define the number of enabled reload opportunities should happen
 * until an enabled reload opportunity becomes a reload point. See Reload Points
 * LDFQ = 0: All reload opportunities are reload points.
 * LDFQ = 1: There is a reload point each 2 reload oportunities.
 * LDFQ = 2: There is a reload point each 3 reload oportunities.
 * LDFQ = 3: There is a reload point each 4 reload oportunities.
 * This pattern continues up to a maximum of 32
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Frequency of the Reload Opportunities
 */
__attribute__((always_inline)) static inline void MftReg_SetConfLdfq(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CONF;

    tmp &= ~MFT_CONF_LDFQ_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_CONF_LDFQ_SHIFT)) & MFT_CONF_LDFQ_MASK);
    obj->CONF = tmp;
}

/*! \brief Gets the Fault Input 3 Polarity
 *
 * This function gets the current Fault Input 3 Polarity.
 * Defines the polarity of the fault input.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Fault Input 3 Polarity
 *         - 0b : The fault input polarity is active high. A 1 at the fault input indicates a fault.
 *         - 1b : The fault input polarity is active low. A 0 at the fault input indicates a fault.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetFltPolFlt3Pol(const MftRegType *obj)
{
    return ((obj->FLTPOL & MFT_FLTPOL_FLT3POL_MASK) >> MFT_FLTPOL_FLT3POL_SHIFT);
}

/*! \brief Sets the Fault Input 3 Polarity
 *
 * This function sets the Fault Input 3 Polarity.
 * Defines the polarity of the fault input.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Fault Input 3 Polarity
 *                    - 0b : The fault input polarity is active high. A 1 at the fault input indicates a fault.
 *                    - 1b : The fault input polarity is active low. A 0 at the fault input indicates a fault.
 */
__attribute__((always_inline)) static inline void MftReg_SetFltPolFlt3Pol(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->FLTPOL;

    tmp &= ~MFT_FLTPOL_FLT3POL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_FLTPOL_FLT3POL_SHIFT)) & MFT_FLTPOL_FLT3POL_MASK);
    obj->FLTPOL = tmp;
}

/*! \brief Gets the Fault Input 2 Polarity
 *
 * This function gets the current Fault Input 2 Polarity.
 * Defines the polarity of the fault input.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Fault Input 2 Polarity
 *         - 0b : The fault input polarity is active high. A 1 at the fault input indicates a fault.
 *         - 1b : The fault input polarity is active low. A 0 at the fault input indicates a fault.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetFltPolFlt2Pol(const MftRegType *obj)
{
    return ((obj->FLTPOL & MFT_FLTPOL_FLT2POL_MASK) >> MFT_FLTPOL_FLT2POL_SHIFT);
}

/*! \brief Sets the Fault Input 2 Polarity
 *
 * This function sets the Fault Input 2 Polarity.
 * Defines the polarity of the fault input.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Fault Input 2 Polarity
 *                    - 0b : The fault input polarity is active high. A 1 at the fault input indicates a fault.
 *                    - 1b : The fault input polarity is active low. A 0 at the fault input indicates a fault.
 */
__attribute__((always_inline)) static inline void MftReg_SetFltPolFlt2Pol(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->FLTPOL;

    tmp &= ~MFT_FLTPOL_FLT2POL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_FLTPOL_FLT2POL_SHIFT)) & MFT_FLTPOL_FLT2POL_MASK);
    obj->FLTPOL = tmp;
}

/*! \brief Gets the Fault Input 1 Polarity
 *
 * This function gets the current Fault Input 1 Polarity.
 * Defines the polarity of the fault input.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Fault Input 1 Polarity
 *         - 0b : The fault input polarity is active high. A 1 at the fault input indicates a fault.
 *         - 1b : The fault input polarity is active low. A 0 at the fault input indicates a fault.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetFltPolFlt1Pol(const MftRegType *obj)
{
    return ((obj->FLTPOL & MFT_FLTPOL_FLT1POL_MASK) >> MFT_FLTPOL_FLT1POL_SHIFT);
}

/*! \brief Sets the Fault Input 1 Polarity
 *
 * This function sets the Fault Input 1 Polarity.
 * Defines the polarity of the fault input.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Fault Input 1 Polarity
 *                    - 0b : The fault input polarity is active high. A 1 at the fault input indicates a fault.
 *                    - 1b : The fault input polarity is active low. A 0 at the fault input indicates a fault.
 */
__attribute__((always_inline)) static inline void MftReg_SetFltPolFlt1Pol(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->FLTPOL;

    tmp &= ~MFT_FLTPOL_FLT1POL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_FLTPOL_FLT1POL_SHIFT)) & MFT_FLTPOL_FLT1POL_MASK);
    obj->FLTPOL = tmp;
}

/*! \brief Gets the Fault Input 0 Polarity
 *
 * This function gets the current Fault Input 0 Polarity.
 * Defines the polarity of the fault input.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Fault Input 0 Polarity
 *         - 0b : The fault input polarity is active high. A 1 at the fault input indicates a fault.
 *         - 1b : The fault input polarity is active low. A 0 at the fault input indicates a fault.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetFltPolFlt0Pol(const MftRegType *obj)
{
    return ((obj->FLTPOL & MFT_FLTPOL_FLT0POL_MASK) >> MFT_FLTPOL_FLT0POL_SHIFT);
}

/*! \brief Sets the Fault Input 0 Polarity
 *
 * This function sets the Fault Input 0 Polarity.
 * Defines the polarity of the fault input.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Fault Input 0 Polarity
 *                    - 0b : The fault input polarity is active high. A 1 at the fault input indicates a fault.
 *                    - 1b : The fault input polarity is active low. A 0 at the fault input indicates a fault.
 */
__attribute__((always_inline)) static inline void MftReg_SetFltPolFlt0Pol(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->FLTPOL;

    tmp &= ~MFT_FLTPOL_FLT0POL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_FLTPOL_FLT0POL_SHIFT)) & MFT_FLTPOL_FLT0POL_MASK);
    obj->FLTPOL = tmp;
}

/*! \brief Gets the Software output control synchronization is activated by a hardware trigger
 *
 * This function gets the current Software output control synchronization is activated by a hardware trigger.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Software output control synchronization is activated by a hardware trigger
 *         - 0b : A hardware trigger does not activate the SWOCTRL register synchronization.
 *         - 1b : A hardware trigger activates the SWOCTRL register synchronization.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetSynConfHwSoc(const MftRegType *obj)
{
    return ((obj->SYNCONF & MFT_SYNCONF_HWSOC_MASK) >> MFT_SYNCONF_HWSOC_SHIFT);
}

/*! \brief Sets the Software output control synchronization is activated by a hardware trigger
 *
 * This function sets the Software output control synchronization is activated by a hardware trigger.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Software output control synchronization is activated by a hardware trigger
 *                    - 0b : A hardware trigger does not activate the SWOCTRL register synchronization.
 *                    - 1b : A hardware trigger activates the SWOCTRL register synchronization.
 */
__attribute__((always_inline)) static inline void MftReg_SetSynConfHwSoc(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SYNCONF;

    tmp &= ~MFT_SYNCONF_HWSOC_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SYNCONF_HWSOC_SHIFT)) & MFT_SYNCONF_HWSOC_MASK);
    obj->SYNCONF = tmp;
}

/*! \brief Gets the Inverting control synchronization is activated by a hardware trigger
 *
 * This function gets the current Inverting control synchronization is activated by a hardware trigger.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Inverting control synchronization is activated by a hardware trigger
 *         - 0b : A hardware trigger does not activate the INVCTRL register synchronization.
 *         - 1b : A hardware trigger activates the INVCTRL register synchronization.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetSynConfHwInvC(const MftRegType *obj)
{
    return ((obj->SYNCONF & MFT_SYNCONF_HWINVC_MASK) >> MFT_SYNCONF_HWINVC_SHIFT);
}

/*! \brief Sets the Inverting control synchronization is activated by a hardware trigger
 *
 * This function sets the Inverting control synchronization is activated by a hardware trigger.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Inverting control synchronization is activated by a hardware trigger
 *                    - 0b : A hardware trigger does not activate the INVCTRL register synchronization.
 *                    - 1b : A hardware trigger activates the INVCTRL register synchronization.
 */
__attribute__((always_inline)) static inline void MftReg_SetSynConfHwInvC(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SYNCONF;

    tmp &= ~MFT_SYNCONF_HWINVC_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SYNCONF_HWINVC_SHIFT)) & MFT_SYNCONF_HWINVC_MASK);
    obj->SYNCONF = tmp;
}

/*! \brief Gets the Output mask synchronization is activated by a hardware trigger
 *
 * This function gets the current Output mask synchronization is activated by a hardware trigger.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Output mask synchronization is activated by a hardware trigger
 *         - 0b : A hardware trigger does not activate the OUTMASK register synchronization.
 *         - 1b : A hardware trigger activates the OUTMASK register synchronization.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetSynConfHwOM(const MftRegType *obj)
{
    return ((obj->SYNCONF & MFT_SYNCONF_HWOM_MASK) >> MFT_SYNCONF_HWOM_SHIFT);
}

/*! \brief Sets the Output mask synchronization is activated by a hardware trigger
 *
 * This function sets the Output mask synchronization is activated by a hardware trigger.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Output mask synchronization is activated by a hardware trigger
 *                    - 0b : A hardware trigger does not activate the OUTMASK register synchronization.
 *                    - 1b : A hardware trigger activates the OUTMASK register synchronization.
 */
__attribute__((always_inline)) static inline void MftReg_SetSynConfHwOM(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SYNCONF;

    tmp &= ~MFT_SYNCONF_HWOM_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SYNCONF_HWOM_SHIFT)) & MFT_SYNCONF_HWOM_MASK);
    obj->SYNCONF = tmp;
}

/*! \brief Gets the MOD, HCR, CNTIN, and CV registers synchronization is activated by a hardware trigger
 *
 * This function gets the current MOD, HCR, CNTIN, and CV registers synchronization is activated by a hardware trigger.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return MOD, HCR, CNTIN, and CV registers synchronization is activated by a hardware trigger
 *         - 0b : A hardware trigger does not activate MOD, HCR, CNTIN, and CV registers synchronization.
 *         - 1b : A hardware trigger activates MOD, HCR, CNTIN, and CV registers synchronization.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetSynConfHwWrbuf(const MftRegType *obj)
{
    return ((obj->SYNCONF & MFT_SYNCONF_HWWRBUF_MASK) >> MFT_SYNCONF_HWWRBUF_SHIFT);
}

/*! \brief Sets the MOD, HCR, CNTIN, and CV registers synchronization is activated by a hardware trigger
 *
 * This function sets the MOD, HCR, CNTIN, and CV registers synchronization is activated by a hardware trigger.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of MOD, HCR, CNTIN, and CV registers synchronization is activated by a hardware trigger
 *                    - 0b : A hardware trigger does not activate MOD, HCR, CNTIN, and CV registers synchronization.
 *                    - 1b : A hardware trigger activates MOD, HCR, CNTIN, and CV registers synchronization.
 */
__attribute__((always_inline)) static inline void MftReg_SetSynConfHwWrbuf(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SYNCONF;

    tmp &= ~MFT_SYNCONF_HWWRBUF_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SYNCONF_HWWRBUF_SHIFT)) & MFT_SYNCONF_HWWRBUF_MASK);
    obj->SYNCONF = tmp;
}

/*! \brief Gets the MFT counter synchronization is activated by a hardware trigger
 *
 * This function gets the current MFT counter synchronization is activated by a hardware trigger.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return MFT counter synchronization is activated by a hardware trigger
 *         - 0b : A hardware trigger does not activate the MFT counter synchronization.
 *         - 1b : A hardware trigger activates the MFT counter synchronization.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetSynConfHwRstCnt(const MftRegType *obj)
{
    return ((obj->SYNCONF & MFT_SYNCONF_HWRSTCNT_MASK) >> MFT_SYNCONF_HWRSTCNT_SHIFT);
}

/*! \brief Sets the MFT counter synchronization is activated by a hardware trigger
 *
 * This function sets the MFT counter synchronization is activated by a hardware trigger.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of MFT counter synchronization is activated by a hardware trigger
 *                    - 0b : A hardware trigger does not activate the MFT counter synchronization.
 *                    - 1b : A hardware trigger activates the MFT counter synchronization.
 */
__attribute__((always_inline)) static inline void MftReg_SetSynConfHwRstCnt(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SYNCONF;

    tmp &= ~MFT_SYNCONF_HWRSTCNT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SYNCONF_HWRSTCNT_SHIFT)) & MFT_SYNCONF_HWRSTCNT_MASK);
    obj->SYNCONF = tmp;
}

/*! \brief Gets the Software output control synchronization is activated by the software trigger
 *
 * This function gets the current Software output control synchronization is activated by the software trigger.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Software output control synchronization is activated by the software trigger
 *         - 0b : The software trigger does not activate the SWOCTRL register synchronization.
 *         - 1b : The software trigger activates the SWOCTRL register synchronization.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetSynConfSwSoc(const MftRegType *obj)
{
    return ((obj->SYNCONF & MFT_SYNCONF_SWSOC_MASK) >> MFT_SYNCONF_SWSOC_SHIFT);
}

/*! \brief Sets the Software output control synchronization is activated by the software trigger
 *
 * This function sets the Software output control synchronization is activated by the software trigger.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Software output control synchronization is activated by the software trigger
 *                    - 0b : The software trigger does not activate the SWOCTRL register synchronization.
 *                    - 1b : The software trigger activates the SWOCTRL register synchronization.
 */
__attribute__((always_inline)) static inline void MftReg_SetSynConfSwSoc(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SYNCONF;

    tmp &= ~MFT_SYNCONF_SWSOC_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SYNCONF_SWSOC_SHIFT)) & MFT_SYNCONF_SWSOC_MASK);
    obj->SYNCONF = tmp;
}

/*! \brief Gets the Inverting control synchronization is activated by the software trigger
 *
 * This function gets the current Inverting control synchronization is activated by the software trigger.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Inverting control synchronization is activated by the software trigger
 *         - 0b : The software trigger does not activate the INVCTRL register synchronization.
 *         - 1b : The software trigger activates the INVCTRL register synchronization.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetSynConfSwInvC(const MftRegType *obj)
{
    return ((obj->SYNCONF & MFT_SYNCONF_SWINVC_MASK) >> MFT_SYNCONF_SWINVC_SHIFT);
}

/*! \brief Sets the Inverting control synchronization is activated by the software trigger
 *
 * This function sets the Inverting control synchronization is activated by the software trigger.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Inverting control synchronization is activated by the software trigger
 *                    - 0b : The software trigger does not activate the INVCTRL register synchronization.
 *                    - 1b : The software trigger activates the INVCTRL register synchronization.
 */
__attribute__((always_inline)) static inline void MftReg_SetSynConfSwInvC(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SYNCONF;

    tmp &= ~MFT_SYNCONF_SWINVC_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SYNCONF_SWINVC_SHIFT)) & MFT_SYNCONF_SWINVC_MASK);
    obj->SYNCONF = tmp;
}

/*! \brief Gets the Output mask synchronization is activated by the software trigger
 *
 * This function gets the current Output mask synchronization is activated by the software trigger.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Output mask synchronization is activated by the software trigger
 *         - 0b : The software trigger does not activate the OUTMASK register synchronization.
 *         - 1b : The software trigger activates the OUTMASK register synchronization.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetSynConfSwOM(const MftRegType *obj)
{
    return ((obj->SYNCONF & MFT_SYNCONF_SWOM_MASK) >> MFT_SYNCONF_SWOM_SHIFT);
}

/*! \brief Sets the Output mask synchronization is activated by the software trigger
 *
 * This function sets the Output mask synchronization is activated by the software trigger.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Output mask synchronization is activated by the software trigger
 *                    - 0b : The software trigger does not activate the OUTMASK register synchronization.
 *                    - 1b : The software trigger activates the OUTMASK register synchronization.
 */
__attribute__((always_inline)) static inline void MftReg_SetSynConfSwOM(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SYNCONF;

    tmp &= ~MFT_SYNCONF_SWOM_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SYNCONF_SWOM_SHIFT)) & MFT_SYNCONF_SWOM_MASK);
    obj->SYNCONF = tmp;
}

/*! \brief Gets the MOD, HCR, CNTIN, and CV registers synchronization is activated by the software trigger
 *
 * This function gets the current MOD, HCR, CNTIN, and CV registers synchronization is activated by the software trigger.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return MOD, HCR, CNTIN, and CV registers synchronization is activated by the software trigger
 *         - 0b : The software trigger does not activate MOD, HCR, CNTIN, and CV registers synchronization.
 *         - 1b : The software trigger activates MOD, HCR, CNTIN, and CV registers synchronization.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetSynConfSwWrbuf(const MftRegType *obj)
{
    return ((obj->SYNCONF & MFT_SYNCONF_SWWRBUF_MASK) >> MFT_SYNCONF_SWWRBUF_SHIFT);
}

/*! \brief Sets the MOD, HCR, CNTIN, and CV registers synchronization is activated by the software trigger
 *
 * This function sets the MOD, HCR, CNTIN, and CV registers synchronization is activated by the software trigger.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of MOD, HCR, CNTIN, and CV registers synchronization is activated by the software trigger
 *                    - 0b : The software trigger does not activate MOD, HCR, CNTIN, and CV registers synchronization.
 *                    - 1b : The software trigger activates MOD, HCR, CNTIN, and CV registers synchronization.
 */
__attribute__((always_inline)) static inline void MftReg_SetSynConfSwWrbuf(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SYNCONF;

    tmp &= ~MFT_SYNCONF_SWWRBUF_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SYNCONF_SWWRBUF_SHIFT)) & MFT_SYNCONF_SWWRBUF_MASK);
    obj->SYNCONF = tmp;
}

/*! \brief Gets the MFT counter synchronization is activated by the software trigger
 *
 * This function gets the current MFT counter synchronization is activated by the software trigger.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return MFT counter synchronization is activated by the software trigger
 *         - 0b : The software trigger does not activate the MFT counter synchronization.
 *         - 1b : The software trigger activates the MFT counter synchronization.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetSynConfSwRstCnt(const MftRegType *obj)
{
    return ((obj->SYNCONF & MFT_SYNCONF_SWRSTCNT_MASK) >> MFT_SYNCONF_SWRSTCNT_SHIFT);
}

/*! \brief Sets the MFT counter synchronization is activated by the software trigger
 *
 * This function sets the MFT counter synchronization is activated by the software trigger.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of MFT counter synchronization is activated by the software trigger
 *                    - 0b : The software trigger does not activate the MFT counter synchronization.
 *                    - 1b : The software trigger activates the MFT counter synchronization.
 */
__attribute__((always_inline)) static inline void MftReg_SetSynConfSwRstCnt(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SYNCONF;

    tmp &= ~MFT_SYNCONF_SWRSTCNT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SYNCONF_SWRSTCNT_SHIFT)) & MFT_SYNCONF_SWRSTCNT_MASK);
    obj->SYNCONF = tmp;
}

/*! \brief Gets the Synchronization Mode
 *
 * This function gets the current Synchronization Mode.
 * Selects the PWM Synchronization mode.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Synchronization Mode
 *         - 0b : Legacy PWM synchronization is selected.
 *         - 1b : Enhanced PWM synchronization is selected.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetSynConfSyncMode(const MftRegType *obj)
{
    return ((obj->SYNCONF & MFT_SYNCONF_SYNCMODE_MASK) >> MFT_SYNCONF_SYNCMODE_SHIFT);
}

/*! \brief Sets the Synchronization Mode
 *
 * This function sets the Synchronization Mode.
 * Selects the PWM Synchronization mode.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Synchronization Mode
 *                    - 0b : Legacy PWM synchronization is selected.
 *                    - 1b : Enhanced PWM synchronization is selected.
 */
__attribute__((always_inline)) static inline void MftReg_SetSynConfSyncMode(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SYNCONF;

    tmp &= ~MFT_SYNCONF_SYNCMODE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SYNCONF_SYNCMODE_SHIFT)) & MFT_SYNCONF_SYNCMODE_MASK);
    obj->SYNCONF = tmp;
}

/*! \brief Gets the SWOCTRL Register Synchronization
 *
 * This function gets the current SWOCTRL Register Synchronization.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return SWOCTRL Register Synchronization
 *         - 0b : SWOCTRL register is updated with its buffer value at all rising edges of MFT input clock.
 *         - 1b : SWOCTRL register is updated with its buffer value by the PWM synchronization.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetSynConfSwOC(const MftRegType *obj)
{
    return ((obj->SYNCONF & MFT_SYNCONF_SWOC_MASK) >> MFT_SYNCONF_SWOC_SHIFT);
}

/*! \brief Sets the SWOCTRL Register Synchronization
 *
 * This function sets the SWOCTRL Register Synchronization.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of SWOCTRL Register Synchronization
 *                    - 0b : SWOCTRL register is updated with its buffer value at all rising edges of MFT input clock.
 *                    - 1b : SWOCTRL register is updated with its buffer value by the PWM synchronization.
 */
__attribute__((always_inline)) static inline void MftReg_SetSynConfSwOC(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SYNCONF;

    tmp &= ~MFT_SYNCONF_SWOC_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SYNCONF_SWOC_SHIFT)) & MFT_SYNCONF_SWOC_MASK);
    obj->SYNCONF = tmp;
}

/*! \brief Gets the INVCTRL Register Synchronization
 *
 * This function gets the current INVCTRL Register Synchronization.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return INVCTRL Register Synchronization
 *         - 0b : INVCTRL register is updated with its buffer value at all rising edges of MFT input clock.
 *         - 1b : INVCTRL register is updated with its buffer value by the PWM synchronization.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetSynConfInvC(const MftRegType *obj)
{
    return ((obj->SYNCONF & MFT_SYNCONF_INVC_MASK) >> MFT_SYNCONF_INVC_SHIFT);
}

/*! \brief Sets the INVCTRL Register Synchronization
 *
 * This function sets the INVCTRL Register Synchronization.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of INVCTRL Register Synchronization
 *                    - 0b : INVCTRL register is updated with its buffer value at all rising edges of MFT input clock.
 *                    - 1b : INVCTRL register is updated with its buffer value by the PWM synchronization.
 */
__attribute__((always_inline)) static inline void MftReg_SetSynConfInvC(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SYNCONF;

    tmp &= ~MFT_SYNCONF_INVC_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SYNCONF_INVC_SHIFT)) & MFT_SYNCONF_INVC_MASK);
    obj->SYNCONF = tmp;
}

/*! \brief Gets the CNTIN Register Synchronization
 *
 * This function gets the current CNTIN Register Synchronization.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return CNTIN Register Synchronization
 *         - 0b : CNTIN register is updated with its buffer value at all rising edges of MFT input clock.
 *         - 1b : CNTIN register is updated with its buffer value by the PWM synchronization.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetSynConfCntInC(const MftRegType *obj)
{
    return ((obj->SYNCONF & MFT_SYNCONF_CNTINC_MASK) >> MFT_SYNCONF_CNTINC_SHIFT);
}

/*! \brief Sets the CNTIN Register Synchronization
 *
 * This function sets the CNTIN Register Synchronization.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of CNTIN Register Synchronization
 *                    - 0b : CNTIN register is updated with its buffer value at all rising edges of MFT input clock.
 *                    - 1b : CNTIN register is updated with its buffer value by the PWM synchronization.
 */
__attribute__((always_inline)) static inline void MftReg_SetSynConfCntInC(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SYNCONF;

    tmp &= ~MFT_SYNCONF_CNTINC_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SYNCONF_CNTINC_SHIFT)) & MFT_SYNCONF_CNTINC_MASK);
    obj->SYNCONF = tmp;
}

/*! \brief Gets the Hardware Trigger Mode
 *
 * This function gets the current Hardware Trigger Mode.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Hardware Trigger Mode
 *         - 0b : MFT clears the TRIGj bit when the hardware trigger j is detected, where j = 0, 1,2.
 *         - 1b : MFT does not clear the TRIGj bit when the hardware trigger j is detected, where j = 0, 1,2.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetSynConfHwTrigMode(const MftRegType *obj)
{
    return ((obj->SYNCONF & MFT_SYNCONF_HWTRIGMODE_MASK) >> MFT_SYNCONF_HWTRIGMODE_SHIFT);
}

/*! \brief Sets the Hardware Trigger Mode
 *
 * This function sets the Hardware Trigger Mode.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Hardware Trigger Mode
 *                    - 0b : MFT clears the TRIGj bit when the hardware trigger j is detected, where j = 0, 1,2.
 *                    - 1b : MFT does not clear the TRIGj bit when the hardware trigger j is detected, where j = 0, 1,2.
 */
__attribute__((always_inline)) static inline void MftReg_SetSynConfHwTrigMode(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SYNCONF;

    tmp &= ~MFT_SYNCONF_HWTRIGMODE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SYNCONF_HWTRIGMODE_SHIFT)) & MFT_SYNCONF_HWTRIGMODE_MASK);
    obj->SYNCONF = tmp;
}

/*! \brief Gets the Pair Channels 3 Inverting Enable
 *
 * This function gets the current Pair Channels 3 Inverting Enable.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Pair Channels 3 Inverting Enable
 *         - 0b : Inverting is disabled.
 *         - 1b : Inverting is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetInvCtrlInv3En(const MftRegType *obj)
{
    return ((obj->INVCTRL & MFT_INVCTRL_INV3EN_MASK) >> MFT_INVCTRL_INV3EN_SHIFT);
}

/*! \brief Sets the Pair Channels 3 Inverting Enable
 *
 * This function sets the Pair Channels 3 Inverting Enable.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Pair Channels 3 Inverting Enable
 *                    - 0b : Inverting is disabled.
 *                    - 1b : Inverting is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetInvCtrlInv3En(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->INVCTRL;

    tmp &= ~MFT_INVCTRL_INV3EN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_INVCTRL_INV3EN_SHIFT)) & MFT_INVCTRL_INV3EN_MASK);
    obj->INVCTRL = tmp;
}

/*! \brief Gets the Pair Channels 2 Inverting Enable
 *
 * This function gets the current Pair Channels 2 Inverting Enable.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Pair Channels 2 Inverting Enable
 *         - 0b : Inverting is disabled.
 *         - 1b : Inverting is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetInvCtrlInv2En(const MftRegType *obj)
{
    return ((obj->INVCTRL & MFT_INVCTRL_INV2EN_MASK) >> MFT_INVCTRL_INV2EN_SHIFT);
}

/*! \brief Sets the Pair Channels 2 Inverting Enable
 *
 * This function sets the Pair Channels 2 Inverting Enable.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Pair Channels 2 Inverting Enable
 *                    - 0b : Inverting is disabled.
 *                    - 1b : Inverting is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetInvCtrlInv2En(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->INVCTRL;

    tmp &= ~MFT_INVCTRL_INV2EN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_INVCTRL_INV2EN_SHIFT)) & MFT_INVCTRL_INV2EN_MASK);
    obj->INVCTRL = tmp;
}

/*! \brief Gets the Pair Channels 1 Inverting Enable
 *
 * This function gets the current Pair Channels 1 Inverting Enable.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Pair Channels 1 Inverting Enable
 *         - 0b : Inverting is disabled.
 *         - 1b : Inverting is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetInvCtrlInv1En(const MftRegType *obj)
{
    return ((obj->INVCTRL & MFT_INVCTRL_INV1EN_MASK) >> MFT_INVCTRL_INV1EN_SHIFT);
}

/*! \brief Sets the Pair Channels 1 Inverting Enable
 *
 * This function sets the Pair Channels 1 Inverting Enable.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Pair Channels 1 Inverting Enable
 *                    - 0b : Inverting is disabled.
 *                    - 1b : Inverting is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetInvCtrlInv1En(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->INVCTRL;

    tmp &= ~MFT_INVCTRL_INV1EN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_INVCTRL_INV1EN_SHIFT)) & MFT_INVCTRL_INV1EN_MASK);
    obj->INVCTRL = tmp;
}

/*! \brief Gets the Pair Channels 0 Inverting Enable
 *
 * This function gets the current Pair Channels 0 Inverting Enable.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Pair Channels 0 Inverting Enable
 *         - 0b : Inverting is disabled.
 *         - 1b : Inverting is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetInvCtrlInv0En(const MftRegType *obj)
{
    return ((obj->INVCTRL & MFT_INVCTRL_INV0EN_MASK) >> MFT_INVCTRL_INV0EN_SHIFT);
}

/*! \brief Sets the Pair Channels 0 Inverting Enable
 *
 * This function sets the Pair Channels 0 Inverting Enable.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Pair Channels 0 Inverting Enable
 *                    - 0b : Inverting is disabled.
 *                    - 1b : Inverting is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetInvCtrlInv0En(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->INVCTRL;

    tmp &= ~MFT_INVCTRL_INV0EN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_INVCTRL_INV0EN_SHIFT)) & MFT_INVCTRL_INV0EN_MASK);
    obj->INVCTRL = tmp;
}

/*! \brief Gets the Channel 7 Software Output Control Value
 *
 * This function gets the current Channel 7 Software Output Control Value.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 7 Software Output Control Value
 *         - 0b : The software output control forces 0 to the channel output.
 *         - 1b : The software output control forces 1 to the channel output.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetSwOCtrlCh7Ocv(const MftRegType *obj)
{
    return ((obj->SWOCTRL & MFT_SWOCTRL_CH7OCV_MASK) >> MFT_SWOCTRL_CH7OCV_SHIFT);
}

/*! \brief Sets the Channel 7 Software Output Control Value
 *
 * This function sets the Channel 7 Software Output Control Value.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 7 Software Output Control Value
 *                    - 0b : The software output control forces 0 to the channel output.
 *                    - 1b : The software output control forces 1 to the channel output.
 */
__attribute__((always_inline)) static inline void MftReg_SetSwOCtrlCh7Ocv(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SWOCTRL;

    tmp &= ~MFT_SWOCTRL_CH7OCV_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SWOCTRL_CH7OCV_SHIFT)) & MFT_SWOCTRL_CH7OCV_MASK);
    obj->SWOCTRL = tmp;
}

/*! \brief Gets the Channel 6 Software Output Control Value
 *
 * This function gets the current Channel 6 Software Output Control Value.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 6 Software Output Control Value
 *         - 0b : The software output control forces 0 to the channel output.
 *         - 1b : The software output control forces 1 to the channel output.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetSwOCtrlCh6Ocv(const MftRegType *obj)
{
    return ((obj->SWOCTRL & MFT_SWOCTRL_CH6OCV_MASK) >> MFT_SWOCTRL_CH6OCV_SHIFT);
}

/*! \brief Sets the Channel 6 Software Output Control Value
 *
 * This function sets the Channel 6 Software Output Control Value.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 6 Software Output Control Value
 *                    - 0b : The software output control forces 0 to the channel output.
 *                    - 1b : The software output control forces 1 to the channel output.
 */
__attribute__((always_inline)) static inline void MftReg_SetSwOCtrlCh6Ocv(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SWOCTRL;

    tmp &= ~MFT_SWOCTRL_CH6OCV_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SWOCTRL_CH6OCV_SHIFT)) & MFT_SWOCTRL_CH6OCV_MASK);
    obj->SWOCTRL = tmp;
}

/*! \brief Gets the Channel 5 Software Output Control Value
 *
 * This function gets the current Channel 5 Software Output Control Value.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 5 Software Output Control Value
 *         - 0b : The software output control forces 0 to the channel output.
 *         - 1b : The software output control forces 1 to the channel output.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetSwOCtrlCh5Ocv(const MftRegType *obj)
{
    return ((obj->SWOCTRL & MFT_SWOCTRL_CH5OCV_MASK) >> MFT_SWOCTRL_CH5OCV_SHIFT);
}

/*! \brief Sets the Channel 5 Software Output Control Value
 *
 * This function sets the Channel 5 Software Output Control Value.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 5 Software Output Control Value
 *                    - 0b : The software output control forces 0 to the channel output.
 *                    - 1b : The software output control forces 1 to the channel output.
 */
__attribute__((always_inline)) static inline void MftReg_SetSwOCtrlCh5Ocv(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SWOCTRL;

    tmp &= ~MFT_SWOCTRL_CH5OCV_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SWOCTRL_CH5OCV_SHIFT)) & MFT_SWOCTRL_CH5OCV_MASK);
    obj->SWOCTRL = tmp;
}

/*! \brief Gets the Channel 4 Software Output Control Value
 *
 * This function gets the current Channel 4 Software Output Control Value.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 4 Software Output Control Value
 *         - 0b : The software output control forces 0 to the channel output.
 *         - 1b : The software output control forces 1 to the channel output.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetSwOCtrlCh4Ocv(const MftRegType *obj)
{
    return ((obj->SWOCTRL & MFT_SWOCTRL_CH4OCV_MASK) >> MFT_SWOCTRL_CH4OCV_SHIFT);
}

/*! \brief Sets the Channel 4 Software Output Control Value
 *
 * This function sets the Channel 4 Software Output Control Value.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 4 Software Output Control Value
 *                    - 0b : The software output control forces 0 to the channel output.
 *                    - 1b : The software output control forces 1 to the channel output.
 */
__attribute__((always_inline)) static inline void MftReg_SetSwOCtrlCh4Ocv(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SWOCTRL;

    tmp &= ~MFT_SWOCTRL_CH4OCV_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SWOCTRL_CH4OCV_SHIFT)) & MFT_SWOCTRL_CH4OCV_MASK);
    obj->SWOCTRL = tmp;
}

/*! \brief Gets the Channel 3 Software Output Control Value
 *
 * This function gets the current Channel 3 Software Output Control Value.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 3 Software Output Control Value
 *         - 0b : The software output control forces 0 to the channel output.
 *         - 1b : The software output control forces 1 to the channel output.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetSwOCtrlCh3Ocv(const MftRegType *obj)
{
    return ((obj->SWOCTRL & MFT_SWOCTRL_CH3OCV_MASK) >> MFT_SWOCTRL_CH3OCV_SHIFT);
}

/*! \brief Sets the Channel 3 Software Output Control Value
 *
 * This function sets the Channel 3 Software Output Control Value.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 3 Software Output Control Value
 *                    - 0b : The software output control forces 0 to the channel output.
 *                    - 1b : The software output control forces 1 to the channel output.
 */
__attribute__((always_inline)) static inline void MftReg_SetSwOCtrlCh3Ocv(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SWOCTRL;

    tmp &= ~MFT_SWOCTRL_CH3OCV_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SWOCTRL_CH3OCV_SHIFT)) & MFT_SWOCTRL_CH3OCV_MASK);
    obj->SWOCTRL = tmp;
}

/*! \brief Gets the Channel 2 Software Output Control Value
 *
 * This function gets the current Channel 2 Software Output Control Value.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 2 Software Output Control Value
 *         - 0b : The software output control forces 0 to the channel output.
 *         - 1b : The software output control forces 1 to the channel output.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetSwOCtrlCh2Ocv(const MftRegType *obj)
{
    return ((obj->SWOCTRL & MFT_SWOCTRL_CH2OCV_MASK) >> MFT_SWOCTRL_CH2OCV_SHIFT);
}

/*! \brief Sets the Channel 2 Software Output Control Value
 *
 * This function sets the Channel 2 Software Output Control Value.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 2 Software Output Control Value
 *                    - 0b : The software output control forces 0 to the channel output.
 *                    - 1b : The software output control forces 1 to the channel output.
 */
__attribute__((always_inline)) static inline void MftReg_SetSwOCtrlCh2Ocv(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SWOCTRL;

    tmp &= ~MFT_SWOCTRL_CH2OCV_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SWOCTRL_CH2OCV_SHIFT)) & MFT_SWOCTRL_CH2OCV_MASK);
    obj->SWOCTRL = tmp;
}

/*! \brief Gets the Channel 1 Software Output Control Value
 *
 * This function gets the current Channel 1 Software Output Control Value.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 1 Software Output Control Value
 *         - 0b : The software output control forces 0 to the channel output.
 *         - 1b : The software output control forces 1 to the channel output.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetSwOCtrlCh1Ocv(const MftRegType *obj)
{
    return ((obj->SWOCTRL & MFT_SWOCTRL_CH1OCV_MASK) >> MFT_SWOCTRL_CH1OCV_SHIFT);
}

/*! \brief Sets the Channel 1 Software Output Control Value
 *
 * This function sets the Channel 1 Software Output Control Value.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 1 Software Output Control Value
 *                    - 0b : The software output control forces 0 to the channel output.
 *                    - 1b : The software output control forces 1 to the channel output.
 */
__attribute__((always_inline)) static inline void MftReg_SetSwOCtrlCh1Ocv(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SWOCTRL;

    tmp &= ~MFT_SWOCTRL_CH1OCV_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SWOCTRL_CH1OCV_SHIFT)) & MFT_SWOCTRL_CH1OCV_MASK);
    obj->SWOCTRL = tmp;
}

/*! \brief Gets the Channel 0 Software Output Control Value
 *
 * This function gets the current Channel 0 Software Output Control Value.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 0 Software Output Control Value
 *         - 0b : The software output control forces 0 to the channel output.
 *         - 1b : The software output control forces 1 to the channel output.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetSwOCtrlCh0Ocv(const MftRegType *obj)
{
    return ((obj->SWOCTRL & MFT_SWOCTRL_CH0OCV_MASK) >> MFT_SWOCTRL_CH0OCV_SHIFT);
}

/*! \brief Sets the Channel 0 Software Output Control Value
 *
 * This function sets the Channel 0 Software Output Control Value.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 0 Software Output Control Value
 *                    - 0b : The software output control forces 0 to the channel output.
 *                    - 1b : The software output control forces 1 to the channel output.
 */
__attribute__((always_inline)) static inline void MftReg_SetSwOCtrlCh0Ocv(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SWOCTRL;

    tmp &= ~MFT_SWOCTRL_CH0OCV_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SWOCTRL_CH0OCV_SHIFT)) & MFT_SWOCTRL_CH0OCV_MASK);
    obj->SWOCTRL = tmp;
}

/*! \brief Gets the Channel 7 Software Output Control Enable
 *
 * This function gets the current Channel 7 Software Output Control Enable.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 7 Software Output Control Enable
 *         - 0b : The channel output is not affected by software output control.
 *         - 1b : The channel output is affected by software output control.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetSwOCtrlCh7Oc(const MftRegType *obj)
{
    return ((obj->SWOCTRL & MFT_SWOCTRL_CH7OC_MASK) >> MFT_SWOCTRL_CH7OC_SHIFT);
}

/*! \brief Sets the Channel 7 Software Output Control Enable
 *
 * This function sets the Channel 7 Software Output Control Enable.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 7 Software Output Control Enable
 *                    - 0b : The channel output is not affected by software output control.
 *                    - 1b : The channel output is affected by software output control.
 */
__attribute__((always_inline)) static inline void MftReg_SetSwOCtrlCh7Oc(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SWOCTRL;

    tmp &= ~MFT_SWOCTRL_CH7OC_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SWOCTRL_CH7OC_SHIFT)) & MFT_SWOCTRL_CH7OC_MASK);
    obj->SWOCTRL = tmp;
}

/*! \brief Gets the Channel 6 Software Output Control Enable
 *
 * This function gets the current Channel 6 Software Output Control Enable.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 6 Software Output Control Enable
 *         - 0b : The channel output is not affected by software output control.
 *         - 1b : The channel output is affected by software output control.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetSwOCtrlCh6Oc(const MftRegType *obj)
{
    return ((obj->SWOCTRL & MFT_SWOCTRL_CH6OC_MASK) >> MFT_SWOCTRL_CH6OC_SHIFT);
}

/*! \brief Sets the Channel 6 Software Output Control Enable
 *
 * This function sets the Channel 6 Software Output Control Enable.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 6 Software Output Control Enable
 *                    - 0b : The channel output is not affected by software output control.
 *                    - 1b : The channel output is affected by software output control.
 */
__attribute__((always_inline)) static inline void MftReg_SetSwOCtrlCh6Oc(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SWOCTRL;

    tmp &= ~MFT_SWOCTRL_CH6OC_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SWOCTRL_CH6OC_SHIFT)) & MFT_SWOCTRL_CH6OC_MASK);
    obj->SWOCTRL = tmp;
}

/*! \brief Gets the Channel 5 Software Output Control Enable
 *
 * This function gets the current Channel 5 Software Output Control Enable.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 5 Software Output Control Enable
 *         - 0b : The channel output is not affected by software output control.
 *         - 1b : The channel output is affected by software output control.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetSwOCtrlCh5Oc(const MftRegType *obj)
{
    return ((obj->SWOCTRL & MFT_SWOCTRL_CH5OC_MASK) >> MFT_SWOCTRL_CH5OC_SHIFT);
}

/*! \brief Sets the Channel 5 Software Output Control Enable
 *
 * This function sets the Channel 5 Software Output Control Enable.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 5 Software Output Control Enable
 *                    - 0b : The channel output is not affected by software output control.
 *                    - 1b : The channel output is affected by software output control.
 */
__attribute__((always_inline)) static inline void MftReg_SetSwOCtrlCh5Oc(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SWOCTRL;

    tmp &= ~MFT_SWOCTRL_CH5OC_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SWOCTRL_CH5OC_SHIFT)) & MFT_SWOCTRL_CH5OC_MASK);
    obj->SWOCTRL = tmp;
}

/*! \brief Gets the Channel 4 Software Output Control Enable
 *
 * This function gets the current Channel 4 Software Output Control Enable.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 4 Software Output Control Enable
 *         - 0b : The channel output is not affected by software output control.
 *         - 1b : The channel output is affected by software output control.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetSwOCtrlCh4Oc(const MftRegType *obj)
{
    return ((obj->SWOCTRL & MFT_SWOCTRL_CH4OC_MASK) >> MFT_SWOCTRL_CH4OC_SHIFT);
}

/*! \brief Sets the Channel 4 Software Output Control Enable
 *
 * This function sets the Channel 4 Software Output Control Enable.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 4 Software Output Control Enable
 *                    - 0b : The channel output is not affected by software output control.
 *                    - 1b : The channel output is affected by software output control.
 */
__attribute__((always_inline)) static inline void MftReg_SetSwOCtrlCh4Oc(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SWOCTRL;

    tmp &= ~MFT_SWOCTRL_CH4OC_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SWOCTRL_CH4OC_SHIFT)) & MFT_SWOCTRL_CH4OC_MASK);
    obj->SWOCTRL = tmp;
}

/*! \brief Gets the Channel 3 Software Output Control Enable
 *
 * This function gets the current Channel 3 Software Output Control Enable.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 3 Software Output Control Enable
 *         - 0b : The channel output is not affected by software output control.
 *         - 1b : The channel output is affected by software output control.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetSwOCtrlCh3Oc(const MftRegType *obj)
{
    return ((obj->SWOCTRL & MFT_SWOCTRL_CH3OC_MASK) >> MFT_SWOCTRL_CH3OC_SHIFT);
}

/*! \brief Sets the Channel 3 Software Output Control Enable
 *
 * This function sets the Channel 3 Software Output Control Enable.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 3 Software Output Control Enable
 *                    - 0b : The channel output is not affected by software output control.
 *                    - 1b : The channel output is affected by software output control.
 */
__attribute__((always_inline)) static inline void MftReg_SetSwOCtrlCh3Oc(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SWOCTRL;

    tmp &= ~MFT_SWOCTRL_CH3OC_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SWOCTRL_CH3OC_SHIFT)) & MFT_SWOCTRL_CH3OC_MASK);
    obj->SWOCTRL = tmp;
}

/*! \brief Gets the Channel 2 Software Output Control Enable
 *
 * This function gets the current Channel 2 Software Output Control Enable.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 2 Software Output Control Enable
 *         - 0b : The channel output is not affected by software output control.
 *         - 1b : The channel output is affected by software output control.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetSwOCtrlCh2Oc(const MftRegType *obj)
{
    return ((obj->SWOCTRL & MFT_SWOCTRL_CH2OC_MASK) >> MFT_SWOCTRL_CH2OC_SHIFT);
}

/*! \brief Sets the Channel 2 Software Output Control Enable
 *
 * This function sets the Channel 2 Software Output Control Enable.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 2 Software Output Control Enable
 *                    - 0b : The channel output is not affected by software output control.
 *                    - 1b : The channel output is affected by software output control.
 */
__attribute__((always_inline)) static inline void MftReg_SetSwOCtrlCh2Oc(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SWOCTRL;

    tmp &= ~MFT_SWOCTRL_CH2OC_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SWOCTRL_CH2OC_SHIFT)) & MFT_SWOCTRL_CH2OC_MASK);
    obj->SWOCTRL = tmp;
}

/*! \brief Gets the Channel 1 Software Output Control Enable
 *
 * This function gets the current Channel 1 Software Output Control Enable.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 1 Software Output Control Enable
 *         - 0b : The channel output is not affected by software output control.
 *         - 1b : The channel output is affected by software output control.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetSwOCtrlCh1Oc(const MftRegType *obj)
{
    return ((obj->SWOCTRL & MFT_SWOCTRL_CH1OC_MASK) >> MFT_SWOCTRL_CH1OC_SHIFT);
}

/*! \brief Sets the Channel 1 Software Output Control Enable
 *
 * This function sets the Channel 1 Software Output Control Enable.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 1 Software Output Control Enable
 *                    - 0b : The channel output is not affected by software output control.
 *                    - 1b : The channel output is affected by software output control.
 */
__attribute__((always_inline)) static inline void MftReg_SetSwOCtrlCh1Oc(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SWOCTRL;

    tmp &= ~MFT_SWOCTRL_CH1OC_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SWOCTRL_CH1OC_SHIFT)) & MFT_SWOCTRL_CH1OC_MASK);
    obj->SWOCTRL = tmp;
}

/*! \brief Gets the Channel 0 Software Output Control Enable
 *
 * This function gets the current Channel 0 Software Output Control Enable.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 0 Software Output Control Enable
 *         - 0b : The channel output is not affected by software output control.
 *         - 1b : The channel output is affected by software output control.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetSwOCtrlCh0Oc(const MftRegType *obj)
{
    return ((obj->SWOCTRL & MFT_SWOCTRL_CH0OC_MASK) >> MFT_SWOCTRL_CH0OC_SHIFT);
}

/*! \brief Sets the Channel 0 Software Output Control Enable
 *
 * This function sets the Channel 0 Software Output Control Enable.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 0 Software Output Control Enable
 *                    - 0b : The channel output is not affected by software output control.
 *                    - 1b : The channel output is affected by software output control.
 */
__attribute__((always_inline)) static inline void MftReg_SetSwOCtrlCh0Oc(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SWOCTRL;

    tmp &= ~MFT_SWOCTRL_CH0OC_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SWOCTRL_CH0OC_SHIFT)) & MFT_SWOCTRL_CH0OC_MASK);
    obj->SWOCTRL = tmp;
}

/*! \brief Sets the Global Load OK
 *
 * This function sets the Global Load OK.
 * This bit controls the global load mechanism.
 * It generates a pulse at MFT module global load output with one MFT clock cycle width,
 * which is used to set LDOK bits of MFT and other modules (including other MFTs).
 * This bit is self-cleared and read value is always zero.
 * The global load mechanism depends on SoC specific information. Refer to MFT SoC specific information to more details.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Global Load OK
 *                    - 0b : No action.
 *                    - 1b : LDOK bit is set.
 */
__attribute__((always_inline)) static inline void MftReg_SetPwmLoadGLdOk(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PWMLOAD;

    tmp &= ~MFT_PWMLOAD_GLDOK_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_PWMLOAD_GLDOK_SHIFT)) & MFT_PWMLOAD_GLDOK_MASK);
    obj->PWMLOAD = tmp;
}

/*! \brief Gets the Global Load Enable
 *
 * This function gets the current Global Load Enable.
 * This bit enables the global load mechanism implemented by GLDOK. If GLEN bit is set, then an external
 * event on the MFT global load input sets the LDOK bit. The clear of the LDOK bit is done by CPU writes '0'
 * to the bit.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Global Load Enable
 *         - 0b : Global Load Ok disabled.
 *         - 1b : Global Load OK enabled. A pulse event on the module global load input sets the LDOK bit.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetPwmLoadGLEn(const MftRegType *obj)
{
    return ((obj->PWMLOAD & MFT_PWMLOAD_GLEN_MASK) >> MFT_PWMLOAD_GLEN_SHIFT);
}

/*! \brief Sets the Global Load Enable
 *
 * This function sets the Global Load Enable.
 * This bit enables the global load mechanism implemented by GLDOK. If GLEN bit is set, then an external
 * event on the MFT global load input sets the LDOK bit. The clear of the LDOK bit is done by CPU writes '0'
 * to the bit.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Global Load Enable
 *                    - 0b : Global Load Ok disabled.
 *                    - 1b : Global Load OK enabled. A pulse event on the module global load input sets the LDOK bit.
 */
__attribute__((always_inline)) static inline void MftReg_SetPwmLoadGLEn(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PWMLOAD;

    tmp &= ~MFT_PWMLOAD_GLEN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_PWMLOAD_GLEN_SHIFT)) & MFT_PWMLOAD_GLEN_MASK);
    obj->PWMLOAD = tmp;
}

/*! \brief Gets the Load Enable
 *
 * This function gets the current Load Enable.
 * Enables the loading of the MOD, CNTIN, HCR and CV registers with the values of their buffers.
 * The LDOK bit can also be set by the Global Load mechanism if GLEN bit is enabled.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Load Enable
 *         - 0b : Loading updated values is disabled.
 *         - 1b : Loading updated values is enabled.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetPwmLoadLdOk(const MftRegType *obj)
{
    return ((obj->PWMLOAD & MFT_PWMLOAD_LDOK_MASK) >> MFT_PWMLOAD_LDOK_SHIFT);
}

/*! \brief Sets the Load Enable
 *
 * This function sets the Load Enable.
 * Enables the loading of the MOD, CNTIN, HCR and CV registers with the values of their buffers.
 * The LDOK bit can also be set by the Global Load mechanism if GLEN bit is enabled.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Load Enable
 *                    - 0b : Loading updated values is disabled.
 *                    - 1b : Loading updated values is enabled.
 */
__attribute__((always_inline)) static inline void MftReg_SetPwmLoadLdOk(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PWMLOAD;

    tmp &= ~MFT_PWMLOAD_LDOK_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_PWMLOAD_LDOK_SHIFT)) & MFT_PWMLOAD_LDOK_MASK);
    obj->PWMLOAD = tmp;
}

/*! \brief Gets the Half Cycle Select
 *
 * This function gets the current Half Cycle Select.
 * This bit enables the half cycle match as a reload oportunity. A half cycle is defined by when the MFT
 * counter matches the HCR register.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Half Cycle Select
 *         - 0b : Half cycle reload is disabled and it is not considered as a reload opportunity.
 *         - 1b : Half cycle reload is enabled and it is considered as a reload opportunity.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetPwmLoadHCSel(const MftRegType *obj)
{
    return ((obj->PWMLOAD & MFT_PWMLOAD_HCSEL_MASK) >> MFT_PWMLOAD_HCSEL_SHIFT);
}

/*! \brief Sets the Half Cycle Select
 *
 * This function sets the Half Cycle Select.
 * This bit enables the half cycle match as a reload oportunity. A half cycle is defined by when the MFT
 * counter matches the HCR register.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Half Cycle Select
 *                    - 0b : Half cycle reload is disabled and it is not considered as a reload opportunity.
 *                    - 1b : Half cycle reload is enabled and it is considered as a reload opportunity.
 */
__attribute__((always_inline)) static inline void MftReg_SetPwmLoadHCSel(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PWMLOAD;

    tmp &= ~MFT_PWMLOAD_HCSEL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_PWMLOAD_HCSEL_SHIFT)) & MFT_PWMLOAD_HCSEL_MASK);
    obj->PWMLOAD = tmp;
}

/*! \brief Gets the Channel 7 Select
 *
 * This function gets the current Channel 7 Select.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 7 Select
 *         - 0b : Channel match is not included as a reload opportunity.
 *         - 1b : Channel match is included as a reload opportunity.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetPwmLoadCh7Sel(const MftRegType *obj)
{
    return ((obj->PWMLOAD & MFT_PWMLOAD_CH7SEL_MASK) >> MFT_PWMLOAD_CH7SEL_SHIFT);
}

/*! \brief Sets the Channel 7 Select
 *
 * This function sets the Channel 7 Select.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 7 Select
 *                    - 0b : Channel match is not included as a reload opportunity.
 *                    - 1b : Channel match is included as a reload opportunity.
 */
__attribute__((always_inline)) static inline void MftReg_SetPwmLoadCh7Sel(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PWMLOAD;

    tmp &= ~MFT_PWMLOAD_CH7SEL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_PWMLOAD_CH7SEL_SHIFT)) & MFT_PWMLOAD_CH7SEL_MASK);
    obj->PWMLOAD = tmp;
}

/*! \brief Gets the Channel 6 Select
 *
 * This function gets the current Channel 6 Select.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 6 Select
 *         - 0b : Channel match is not included as a reload opportunity.
 *         - 1b : Channel match is included as a reload opportunity.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetPwmLoadCh6Sel(const MftRegType *obj)
{
    return ((obj->PWMLOAD & MFT_PWMLOAD_CH6SEL_MASK) >> MFT_PWMLOAD_CH6SEL_SHIFT);
}

/*! \brief Sets the Channel 6 Select
 *
 * This function sets the Channel 6 Select.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 6 Select
 *                    - 0b : Channel match is not included as a reload opportunity.
 *                    - 1b : Channel match is included as a reload opportunity.
 */
__attribute__((always_inline)) static inline void MftReg_SetPwmLoadCh6Sel(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PWMLOAD;

    tmp &= ~MFT_PWMLOAD_CH6SEL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_PWMLOAD_CH6SEL_SHIFT)) & MFT_PWMLOAD_CH6SEL_MASK);
    obj->PWMLOAD = tmp;
}

/*! \brief Gets the Channel 5 Select
 *
 * This function gets the current Channel 5 Select.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 5 Select
 *         - 0b : Channel match is not included as a reload opportunity.
 *         - 1b : Channel match is included as a reload opportunity.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetPwmLoadCh5Sel(const MftRegType *obj)
{
    return ((obj->PWMLOAD & MFT_PWMLOAD_CH5SEL_MASK) >> MFT_PWMLOAD_CH5SEL_SHIFT);
}

/*! \brief Sets the Channel 5 Select
 *
 * This function sets the Channel 5 Select.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 5 Select
 *                    - 0b : Channel match is not included as a reload opportunity.
 *                    - 1b : Channel match is included as a reload opportunity.
 */
__attribute__((always_inline)) static inline void MftReg_SetPwmLoadCh5Sel(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PWMLOAD;

    tmp &= ~MFT_PWMLOAD_CH5SEL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_PWMLOAD_CH5SEL_SHIFT)) & MFT_PWMLOAD_CH5SEL_MASK);
    obj->PWMLOAD = tmp;
}

/*! \brief Gets the Channel 4 Select
 *
 * This function gets the current Channel 4 Select.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 4 Select
 *         - 0b : Channel match is not included as a reload opportunity.
 *         - 1b : Channel match is included as a reload opportunity.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetPwmLoadCh4Sel(const MftRegType *obj)
{
    return ((obj->PWMLOAD & MFT_PWMLOAD_CH4SEL_MASK) >> MFT_PWMLOAD_CH4SEL_SHIFT);
}

/*! \brief Sets the Channel 4 Select
 *
 * This function sets the Channel 4 Select.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 4 Select
 *                    - 0b : Channel match is not included as a reload opportunity.
 *                    - 1b : Channel match is included as a reload opportunity.
 */
__attribute__((always_inline)) static inline void MftReg_SetPwmLoadCh4Sel(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PWMLOAD;

    tmp &= ~MFT_PWMLOAD_CH4SEL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_PWMLOAD_CH4SEL_SHIFT)) & MFT_PWMLOAD_CH4SEL_MASK);
    obj->PWMLOAD = tmp;
}

/*! \brief Gets the Channel 3 Select
 *
 * This function gets the current Channel 3 Select.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 3 Select
 *         - 0b : Channel match is not included as a reload opportunity.
 *         - 1b : Channel match is included as a reload opportunity.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetPwmLoadCh3Sel(const MftRegType *obj)
{
    return ((obj->PWMLOAD & MFT_PWMLOAD_CH3SEL_MASK) >> MFT_PWMLOAD_CH3SEL_SHIFT);
}

/*! \brief Sets the Channel 3 Select
 *
 * This function sets the Channel 3 Select.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 3 Select
 *                    - 0b : Channel match is not included as a reload opportunity.
 *                    - 1b : Channel match is included as a reload opportunity.
 */
__attribute__((always_inline)) static inline void MftReg_SetPwmLoadCh3Sel(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PWMLOAD;

    tmp &= ~MFT_PWMLOAD_CH3SEL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_PWMLOAD_CH3SEL_SHIFT)) & MFT_PWMLOAD_CH3SEL_MASK);
    obj->PWMLOAD = tmp;
}

/*! \brief Gets the Channel 2 Select
 *
 * This function gets the current Channel 2 Select.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 2 Select
 *         - 0b : Channel match is not included as a reload opportunity.
 *         - 1b : Channel match is included as a reload opportunity.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetPwmLoadCh2Sel(const MftRegType *obj)
{
    return ((obj->PWMLOAD & MFT_PWMLOAD_CH2SEL_MASK) >> MFT_PWMLOAD_CH2SEL_SHIFT);
}

/*! \brief Sets the Channel 2 Select
 *
 * This function sets the Channel 2 Select.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 2 Select
 *                    - 0b : Channel match is not included as a reload opportunity.
 *                    - 1b : Channel match is included as a reload opportunity.
 */
__attribute__((always_inline)) static inline void MftReg_SetPwmLoadCh2Sel(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PWMLOAD;

    tmp &= ~MFT_PWMLOAD_CH2SEL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_PWMLOAD_CH2SEL_SHIFT)) & MFT_PWMLOAD_CH2SEL_MASK);
    obj->PWMLOAD = tmp;
}

/*! \brief Gets the Channel 1 Select
 *
 * This function gets the current Channel 1 Select.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 1 Select
 *         - 0b : Channel match is not included as a reload opportunity.
 *         - 1b : Channel match is included as a reload opportunity.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetPwmLoadCh1Sel(const MftRegType *obj)
{
    return ((obj->PWMLOAD & MFT_PWMLOAD_CH1SEL_MASK) >> MFT_PWMLOAD_CH1SEL_SHIFT);
}

/*! \brief Sets the Channel 1 Select
 *
 * This function sets the Channel 1 Select.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 1 Select
 *                    - 0b : Channel match is not included as a reload opportunity.
 *                    - 1b : Channel match is included as a reload opportunity.
 */
__attribute__((always_inline)) static inline void MftReg_SetPwmLoadCh1Sel(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PWMLOAD;

    tmp &= ~MFT_PWMLOAD_CH1SEL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_PWMLOAD_CH1SEL_SHIFT)) & MFT_PWMLOAD_CH1SEL_MASK);
    obj->PWMLOAD = tmp;
}

/*! \brief Gets the Channel 0 Select
 *
 * This function gets the current Channel 0 Select.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel 0 Select
 *         - 0b : Channel match is not included as a reload opportunity.
 *         - 1b : Channel match is included as a reload opportunity.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetPwmLoadCh0Sel(const MftRegType *obj)
{
    return ((obj->PWMLOAD & MFT_PWMLOAD_CH0SEL_MASK) >> MFT_PWMLOAD_CH0SEL_SHIFT);
}

/*! \brief Sets the Channel 0 Select
 *
 * This function sets the Channel 0 Select.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel 0 Select
 *                    - 0b : Channel match is not included as a reload opportunity.
 *                    - 1b : Channel match is included as a reload opportunity.
 */
__attribute__((always_inline)) static inline void MftReg_SetPwmLoadCh0Sel(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PWMLOAD;

    tmp &= ~MFT_PWMLOAD_CH0SEL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_PWMLOAD_CH0SEL_SHIFT)) & MFT_PWMLOAD_CH0SEL_MASK);
    obj->PWMLOAD = tmp;
}

/*! \brief Gets the Half Cycle Value
 *
 * This function gets the current Half Cycle Value.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Half Cycle Value
 */
__attribute__((always_inline)) static inline uint16_t MftReg_GetHcrHCVal(const MftRegType *obj)
{
    return ((obj->HCR & MFT_HCR_HCVAL_MASK) >> MFT_HCR_HCVAL_SHIFT);
}

/*! \brief Sets the Half Cycle Value
 *
 * This function sets the Half Cycle Value.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Half Cycle Value
 */
__attribute__((always_inline)) static inline void MftReg_SetHcrHCVal(MftRegType *obj, uint16_t value)
{
    uint32_t tmp = obj->HCR;

    tmp &= ~MFT_HCR_HCVAL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_HCR_HCVAL_SHIFT)) & MFT_HCR_HCVAL_MASK);
    obj->HCR = tmp;
}

/*! \brief Gets the Extended Deadtime Value
 *
 * This function gets the current Extended Deadtime Value.
 * This field is a bit extension of the DTVAL field. It defines the 4 most significant bits of the deadtime value.
 * The maximum deadtime value is extended to 1023 using the concatenation {DTVALEX, DTVAL}.
 * Deadtime insert value = (DTPS * {DTVALEX, DTVAL}).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] pairIndex : the pair index
 * \return Extended Deadtime Value
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetPairDeadTimeDtValEx(const MftRegType *obj, uint8_t pairIndex)
{
    return ((obj->PAIR[pairIndex].DEADTIME & MFT_PAIR_DEADTIME_DTVALEX_MASK) >> MFT_PAIR_DEADTIME_DTVALEX_SHIFT);
}

/*! \brief Sets the Extended Deadtime Value
 *
 * This function sets the Extended Deadtime Value.
 * This field is a bit extension of the DTVAL field. It defines the 4 most significant bits of the deadtime value.
 * The maximum deadtime value is extended to 1023 using the concatenation {DTVALEX, DTVAL}.
 * Deadtime insert value = (DTPS * {DTVALEX, DTVAL}).
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] pairIndex : the pair index
 * \param[in] value : the value of Extended Deadtime Value
 */
__attribute__((always_inline)) static inline void MftReg_SetPairDeadTimeDtValEx(MftRegType *obj, uint8_t pairIndex, uint8_t value)
{
    uint32_t tmp = obj->PAIR[pairIndex].DEADTIME;

    tmp &= ~MFT_PAIR_DEADTIME_DTVALEX_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_PAIR_DEADTIME_DTVALEX_SHIFT)) & MFT_PAIR_DEADTIME_DTVALEX_MASK);
    obj->PAIR[pairIndex].DEADTIME = tmp;
}

/*! \brief Gets the Deadtime Prescaler Value
 *
 * This function gets the current Deadtime Prescaler Value.
 * Selects the division factor of the MFT input clock. This prescaled clock is used by the deadtime counter.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] pairIndex : the pair index
 * \return Deadtime Prescaler Value
 *         - 0xb : Divide the MFT input clock by 1.
 *         - 10b : Divide the MFT input clock by 4.
 *         - 11b : Divide the MFT input clock by 16.
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetPairDeadTimeDtPs(const MftRegType *obj, uint8_t pairIndex)
{
    return ((obj->PAIR[pairIndex].DEADTIME & MFT_PAIR_DEADTIME_DTPS_MASK) >> MFT_PAIR_DEADTIME_DTPS_SHIFT);
}

/*! \brief Sets the Deadtime Prescaler Value
 *
 * This function sets the Deadtime Prescaler Value.
 * Selects the division factor of the MFT input clock. This prescaled clock is used by the deadtime counter.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] pairIndex : the pair index
 * \param[in] value : the value of Deadtime Prescaler Value
 *                    - 0xb : Divide the MFT input clock by 1.
 *                    - 10b : Divide the MFT input clock by 4.
 *                    - 11b : Divide the MFT input clock by 16.
 */
__attribute__((always_inline)) static inline void MftReg_SetPairDeadTimeDtPs(MftRegType *obj, uint8_t pairIndex, uint8_t value)
{
    uint32_t tmp = obj->PAIR[pairIndex].DEADTIME;

    tmp &= ~MFT_PAIR_DEADTIME_DTPS_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_PAIR_DEADTIME_DTPS_SHIFT)) & MFT_PAIR_DEADTIME_DTPS_MASK);
    obj->PAIR[pairIndex].DEADTIME = tmp;
}

/*! \brief Gets the Deadtime Value
 *
 * This function gets the current Deadtime Value.
 * Selects the deadtime value.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] pairIndex : the pair index
 * \return Deadtime Value
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetPairDeadTimeDtVal(const MftRegType *obj, uint8_t pairIndex)
{
    return ((obj->PAIR[pairIndex].DEADTIME & MFT_PAIR_DEADTIME_DTVAL_MASK) >> MFT_PAIR_DEADTIME_DTVAL_SHIFT);
}

/*! \brief Sets the Deadtime Value
 *
 * This function sets the Deadtime Value.
 * Selects the deadtime value.
 * This field is write protected. It can be written only when MODE[WPDIS] = 1
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] pairIndex : the pair index
 * \param[in] value : the value of Deadtime Value
 */
__attribute__((always_inline)) static inline void MftReg_SetPairDeadTimeDtVal(MftRegType *obj, uint8_t pairIndex, uint8_t value)
{
    uint32_t tmp = obj->PAIR[pairIndex].DEADTIME;

    tmp &= ~MFT_PAIR_DEADTIME_DTVAL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_PAIR_DEADTIME_DTVAL_SHIFT)) & MFT_PAIR_DEADTIME_DTVAL_MASK);
    obj->PAIR[pairIndex].DEADTIME = tmp;
}

/*! \brief Gets the Mirror of the Modulo Integer Value
 *
 * This function gets the current Mirror of the Modulo Integer Value.
 * See the field MOD of the register MOD
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Mirror of the Modulo Integer Value
 */
__attribute__((always_inline)) static inline uint16_t MftReg_GetModMirrorModM(const MftRegType *obj)
{
    return ((obj->MOD_MIRROR & MFT_MOD_MIRROR_MOD_M_MASK) >> MFT_MOD_MIRROR_MOD_M_SHIFT);
}

/*! \brief Sets the Mirror of the Modulo Integer Value
 *
 * This function sets the Mirror of the Modulo Integer Value.
 * See the field MOD of the register MOD
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Mirror of the Modulo Integer Value
 */
__attribute__((always_inline)) static inline void MftReg_SetModMirrorModM(MftRegType *obj, uint16_t value)
{
    uint32_t tmp = obj->MOD_MIRROR;

    tmp &= ~MFT_MOD_MIRROR_MOD_M_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_MOD_MIRROR_MOD_M_SHIFT)) & MFT_MOD_MIRROR_MOD_M_MASK);
    obj->MOD_MIRROR = tmp;
}

/*! \brief Gets the Modulo Fractional Value
 *
 * This function gets the current Modulo Fractional Value.
 * The modulo fractional value is used in the PWM period dithering.
 * This value is added to an internal accumulator at the end of each PWM period.
 * Writes to the field FRACMOD are done on its write buffer.
 * The FRACMOD is updated with its write buffer value according to Registers updated from write buffers.
 * If MFTEN = 0, a write to SC register resets manually this write coherency mechanism
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Modulo Fractional Value
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetModMirrorFracModM(const MftRegType *obj)
{
    return ((obj->MOD_MIRROR & MFT_MOD_MIRROR_FRACMOD_M_MASK) >> MFT_MOD_MIRROR_FRACMOD_M_SHIFT);
}

/*! \brief Sets the Modulo Fractional Value
 *
 * This function sets the Modulo Fractional Value.
 * The modulo fractional value is used in the PWM period dithering.
 * This value is added to an internal accumulator at the end of each PWM period.
 * Writes to the field FRACMOD are done on its write buffer.
 * The FRACMOD is updated with its write buffer value according to Registers updated from write buffers.
 * If MFTEN = 0, a write to SC register resets manually this write coherency mechanism
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Modulo Fractional Value
 */
__attribute__((always_inline)) static inline void MftReg_SetModMirrorFracModM(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MOD_MIRROR;

    tmp &= ~MFT_MOD_MIRROR_FRACMOD_M_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_MOD_MIRROR_FRACMOD_M_SHIFT)) & MFT_MOD_MIRROR_FRACMOD_M_MASK);
    obj->MOD_MIRROR = tmp;
}

/*! \brief Gets the Mirror of the Channel Match Integer Value
 *
 * This function gets the current Mirror of the Channel Match Integer Value.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] channel : the channel index
 * \return Mirror of the Channel Match Integer Value
 */
__attribute__((always_inline)) static inline uint16_t MftReg_GetCvMirrorValM(const MftRegType *obj, uint8_t channel)
{
    return ((obj->MIRROR[channel].CV & MFT_CV_MIRROR_VAL_M_MASK) >> MFT_CV_MIRROR_VAL_M_SHIFT);
}

/*! \brief Sets the Mirror of the Channel Match Integer Value
 *
 * This function sets the Mirror of the Channel Match Integer Value.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] channel : the channel index
 * \param[in] value : the value of Mirror of the Channel Match Integer Value
 */
__attribute__((always_inline)) static inline void MftReg_SetCvMirrorValM(MftRegType *obj, uint8_t channel, uint16_t value)
{
    uint32_t tmp = obj->MIRROR[channel].CV;

    tmp &= ~MFT_CV_MIRROR_VAL_M_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_CV_MIRROR_VAL_M_SHIFT)) & MFT_CV_MIRROR_VAL_M_MASK);
    obj->MIRROR[channel].CV = tmp;
}

/*! \brief Gets the Channel Match Fractional Value
 *
 * This function gets the current Channel Match Fractional Value.
 * The channel match fractional value is used in the PWM edge dithering.
 * This value is added to the channel internal accumulator at the end of each PWM period.
 * Writes to the field FRACVAL are done on its write buffer.
 * The FRACVAL is updated with its write buffer value according to Registers updated from write buffers.
 * If MFTEN = 0, a write to CnSC register resets manually this write coherency mechanism
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] channel : the channel index
 * \return Channel Match Fractional Value
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetCvMirrorFracVal(const MftRegType *obj, uint8_t channel)
{
    return ((obj->MIRROR[channel].CV & MFT_CV_MIRROR_FRACVAL_MASK) >> MFT_CV_MIRROR_FRACVAL_SHIFT);
}

/*! \brief Sets the Channel Match Fractional Value
 *
 * This function sets the Channel Match Fractional Value.
 * The channel match fractional value is used in the PWM edge dithering.
 * This value is added to the channel internal accumulator at the end of each PWM period.
 * Writes to the field FRACVAL are done on its write buffer.
 * The FRACVAL is updated with its write buffer value according to Registers updated from write buffers.
 * If MFTEN = 0, a write to CnSC register resets manually this write coherency mechanism
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] channel : the channel index
 * \param[in] value : the value of Channel Match Fractional Value
 */
__attribute__((always_inline)) static inline void MftReg_SetCvMirrorFracVal(MftRegType *obj, uint8_t channel, uint8_t value)
{
    uint32_t tmp = obj->MIRROR[channel].CV;

    tmp &= ~MFT_CV_MIRROR_FRACVAL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_CV_MIRROR_FRACVAL_SHIFT)) & MFT_CV_MIRROR_FRACVAL_MASK);
    obj->MIRROR[channel].CV = tmp;
}

/*! \brief Gets the Channel Output Enable Signal
 *
 * This function gets the current Channel Output Enable Signal.
 *
 * \param[in] obj : pointer to MFT register instance
 * \return Channel Output Enable Signal
 *         - 0b : The MFT channel output is put to safe state when the MFT counter is enabled and the MFT
 *                channel output is enabled by Fault Control (MFT_MODE[FAULTM]!=2'b00 and
 *                MFT_FLTCTRL[FSTATE]=1'b0) and PWM is enabled (MFT_SC[PWMENn] = 1'b1).
 *                Otherwise the channel output is tristated.
 *         - 1b : The MFT channel output state is retained when the channel is in output mode.
 *                The output channel is tristated when the channel is in input capture [DECAPEN=1'b0, COMBINE=1'b0,
 *                MSnB:MSnA=2'b00] or dual edge capture mode [DECAPEN=1'b1].
 */
__attribute__((always_inline)) static inline uint8_t MftReg_GetSimObeObe(const MftRegType *obj)
{
    return ((obj->SIM_OBE & MFT_SIM_OBE_OBE_MASK) >> MFT_SIM_OBE_OBE_SHIFT);
}

/*! \brief Sets the Channel Output Enable Signal
 *
 * This function sets the Channel Output Enable Signal.
 *
 * \param[in] obj : pointer to MFT register instance
 * \param[in] value : the value of Channel Output Enable Signal
 *                    - 0b : The MFT channel output is put to safe state when the MFT counter is enabled and the MFT
 *                           channel output is enabled by Fault Control (MFT_MODE[FAULTM]!=2'b00 and
 *                           MFT_FLTCTRL[FSTATE]=1'b0) and PWM is enabled (MFT_SC[PWMENn] = 1'b1). Otherwise the
 *                           channel output is tristated.
 *                    - 1b : The MFT channel output state is retained when the channel is in output mode. The output
 *                           channel is tristated when the channel is in input capture [DECAPEN=1'b0, COMBINE=1'b0,
 *                           MSnB:MSnA=2'b00] or dual edge capture mode [DECAPEN=1'b1].
 */
__attribute__((always_inline)) static inline void MftReg_SetSimObeObe(MftRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SIM_OBE;

    tmp &= ~MFT_SIM_OBE_OBE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << MFT_SIM_OBE_OBE_SHIFT)) & MFT_SIM_OBE_OBE_MASK);
    obj->SIM_OBE = tmp;
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _MFT_REG_H_ */
