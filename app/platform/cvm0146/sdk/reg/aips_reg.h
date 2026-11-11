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

#ifndef _AIPS_REG_H_
#define _AIPS_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the AIPS Registers
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

/* MPRA Bit Fields */
#define AIPS_MPRA_MTR0_MASK  (0x40000000u)
#define AIPS_MPRA_MTR0_SHIFT (30u)
#define AIPS_MPRA_MTR0_WIDTH (1u)
#define AIPS_MPRA_MTW0_MASK  (0x20000000u)
#define AIPS_MPRA_MTW0_SHIFT (29u)
#define AIPS_MPRA_MTW0_WIDTH (1u)
#define AIPS_MPRA_MPL0_MASK  (0x10000000u)
#define AIPS_MPRA_MPL0_SHIFT (28u)
#define AIPS_MPRA_MPL0_WIDTH (1u)
#define AIPS_MPRA_MTR1_MASK  (0x4000000u)
#define AIPS_MPRA_MTR1_SHIFT (26u)
#define AIPS_MPRA_MTR1_WIDTH (1u)
#define AIPS_MPRA_MTW1_MASK  (0x2000000u)
#define AIPS_MPRA_MTW1_SHIFT (25u)
#define AIPS_MPRA_MTW1_WIDTH (1u)
#define AIPS_MPRA_MPL1_MASK  (0x1000000u)
#define AIPS_MPRA_MPL1_SHIFT (24u)
#define AIPS_MPRA_MPL1_WIDTH (1u)
#define AIPS_MPRA_MTR2_MASK  (0x400000u)
#define AIPS_MPRA_MTR2_SHIFT (22u)
#define AIPS_MPRA_MTR2_WIDTH (1u)
#define AIPS_MPRA_MTW2_MASK  (0x200000u)
#define AIPS_MPRA_MTW2_SHIFT (21u)
#define AIPS_MPRA_MTW2_WIDTH (1u)
#define AIPS_MPRA_MPL2_MASK  (0x100000u)
#define AIPS_MPRA_MPL2_SHIFT (20u)
#define AIPS_MPRA_MPL2_WIDTH (1u)
#define AIPS_MPRA_MTR3_MASK  (0x40000u)
#define AIPS_MPRA_MTR3_SHIFT (18u)
#define AIPS_MPRA_MTR3_WIDTH (1u)
#define AIPS_MPRA_MTW3_MASK  (0x20000u)
#define AIPS_MPRA_MTW3_SHIFT (17u)
#define AIPS_MPRA_MTW3_WIDTH (1u)
#define AIPS_MPRA_MPL3_MASK  (0x10000u)
#define AIPS_MPRA_MPL3_SHIFT (16u)
#define AIPS_MPRA_MPL3_WIDTH (1u)

/* PACRA Bit Fields */
#define AIPS_PACRA_SP7_MASK  (0x40000000u)
#define AIPS_PACRA_SP7_SHIFT (30u)
#define AIPS_PACRA_SP7_WIDTH (1u)
#define AIPS_PACRA_WP7_MASK  (0x20000000u)
#define AIPS_PACRA_WP7_SHIFT (29u)
#define AIPS_PACRA_WP7_WIDTH (1u)
#define AIPS_PACRA_TP7_MASK  (0x10000000u)
#define AIPS_PACRA_TP7_SHIFT (28u)
#define AIPS_PACRA_TP7_WIDTH (1u)
#define AIPS_PACRA_SP6_MASK  (0x4000000u)
#define AIPS_PACRA_SP6_SHIFT (26u)
#define AIPS_PACRA_SP6_WIDTH (1u)
#define AIPS_PACRA_WP6_MASK  (0x2000000u)
#define AIPS_PACRA_WP6_SHIFT (25u)
#define AIPS_PACRA_WP6_WIDTH (1u)
#define AIPS_PACRA_TP6_MASK  (0x1000000u)
#define AIPS_PACRA_TP6_SHIFT (24u)
#define AIPS_PACRA_TP6_WIDTH (1u)
#define AIPS_PACRA_SP5_MASK  (0x400000u)
#define AIPS_PACRA_SP5_SHIFT (22u)
#define AIPS_PACRA_SP5_WIDTH (1u)
#define AIPS_PACRA_WP5_MASK  (0x200000u)
#define AIPS_PACRA_WP5_SHIFT (21u)
#define AIPS_PACRA_WP5_WIDTH (1u)
#define AIPS_PACRA_TP5_MASK  (0x100000u)
#define AIPS_PACRA_TP5_SHIFT (20u)
#define AIPS_PACRA_TP5_WIDTH (1u)
#define AIPS_PACRA_SP4_MASK  (0x40000u)
#define AIPS_PACRA_SP4_SHIFT (18u)
#define AIPS_PACRA_SP4_WIDTH (1u)
#define AIPS_PACRA_WP4_MASK  (0x20000u)
#define AIPS_PACRA_WP4_SHIFT (17u)
#define AIPS_PACRA_WP4_WIDTH (1u)
#define AIPS_PACRA_TP4_MASK  (0x10000u)
#define AIPS_PACRA_TP4_SHIFT (16u)
#define AIPS_PACRA_TP4_WIDTH (1u)
#define AIPS_PACRA_SP3_MASK  (0x4000u)
#define AIPS_PACRA_SP3_SHIFT (14u)
#define AIPS_PACRA_SP3_WIDTH (1u)
#define AIPS_PACRA_WP3_MASK  (0x2000u)
#define AIPS_PACRA_WP3_SHIFT (13u)
#define AIPS_PACRA_WP3_WIDTH (1u)
#define AIPS_PACRA_TP3_MASK  (0x1000u)
#define AIPS_PACRA_TP3_SHIFT (12u)
#define AIPS_PACRA_TP3_WIDTH (1u)
#define AIPS_PACRA_SP2_MASK  (0x400u)
#define AIPS_PACRA_SP2_SHIFT (10u)
#define AIPS_PACRA_SP2_WIDTH (1u)
#define AIPS_PACRA_WP2_MASK  (0x200u)
#define AIPS_PACRA_WP2_SHIFT (9u)
#define AIPS_PACRA_WP2_WIDTH (1u)
#define AIPS_PACRA_TP2_MASK  (0x100u)
#define AIPS_PACRA_TP2_SHIFT (8u)
#define AIPS_PACRA_TP2_WIDTH (1u)
#define AIPS_PACRA_SP1_MASK  (0x40u)
#define AIPS_PACRA_SP1_SHIFT (6u)
#define AIPS_PACRA_SP1_WIDTH (1u)
#define AIPS_PACRA_WP1_MASK  (0x20u)
#define AIPS_PACRA_WP1_SHIFT (5u)
#define AIPS_PACRA_WP1_WIDTH (1u)
#define AIPS_PACRA_TP1_MASK  (0x10u)
#define AIPS_PACRA_TP1_SHIFT (4u)
#define AIPS_PACRA_TP1_WIDTH (1u)
#define AIPS_PACRA_SP0_MASK  (0x04u)
#define AIPS_PACRA_SP0_SHIFT (2u)
#define AIPS_PACRA_SP0_WIDTH (1u)
#define AIPS_PACRA_WP0_MASK  (0x02u)
#define AIPS_PACRA_WP0_SHIFT (1u)
#define AIPS_PACRA_WP0_WIDTH (1u)
#define AIPS_PACRA_TP0_MASK  (0x01u)
#define AIPS_PACRA_TP0_SHIFT (0u)
#define AIPS_PACRA_TP0_WIDTH (1u)

/* PACRB Bit Fields */
#define AIPS_PACRB_SP7_MASK  (0x40000000u)
#define AIPS_PACRB_SP7_SHIFT (30u)
#define AIPS_PACRB_SP7_WIDTH (1u)
#define AIPS_PACRB_WP7_MASK  (0x20000000u)
#define AIPS_PACRB_WP7_SHIFT (29u)
#define AIPS_PACRB_WP7_WIDTH (1u)
#define AIPS_PACRB_TP7_MASK  (0x10000000u)
#define AIPS_PACRB_TP7_SHIFT (28u)
#define AIPS_PACRB_TP7_WIDTH (1u)
#define AIPS_PACRB_SP6_MASK  (0x4000000u)
#define AIPS_PACRB_SP6_SHIFT (26u)
#define AIPS_PACRB_SP6_WIDTH (1u)
#define AIPS_PACRB_WP6_MASK  (0x2000000u)
#define AIPS_PACRB_WP6_SHIFT (25u)
#define AIPS_PACRB_WP6_WIDTH (1u)
#define AIPS_PACRB_TP6_MASK  (0x1000000u)
#define AIPS_PACRB_TP6_SHIFT (24u)
#define AIPS_PACRB_TP6_WIDTH (1u)
#define AIPS_PACRB_SP5_MASK  (0x400000u)
#define AIPS_PACRB_SP5_SHIFT (22u)
#define AIPS_PACRB_SP5_WIDTH (1u)
#define AIPS_PACRB_WP5_MASK  (0x200000u)
#define AIPS_PACRB_WP5_SHIFT (21u)
#define AIPS_PACRB_WP5_WIDTH (1u)
#define AIPS_PACRB_TP5_MASK  (0x100000u)
#define AIPS_PACRB_TP5_SHIFT (20u)
#define AIPS_PACRB_TP5_WIDTH (1u)
#define AIPS_PACRB_SP4_MASK  (0x40000u)
#define AIPS_PACRB_SP4_SHIFT (18u)
#define AIPS_PACRB_SP4_WIDTH (1u)
#define AIPS_PACRB_WP4_MASK  (0x20000u)
#define AIPS_PACRB_WP4_SHIFT (17u)
#define AIPS_PACRB_WP4_WIDTH (1u)
#define AIPS_PACRB_TP4_MASK  (0x10000u)
#define AIPS_PACRB_TP4_SHIFT (16u)
#define AIPS_PACRB_TP4_WIDTH (1u)
#define AIPS_PACRB_SP3_MASK  (0x4000u)
#define AIPS_PACRB_SP3_SHIFT (14u)
#define AIPS_PACRB_SP3_WIDTH (1u)
#define AIPS_PACRB_WP3_MASK  (0x2000u)
#define AIPS_PACRB_WP3_SHIFT (13u)
#define AIPS_PACRB_WP3_WIDTH (1u)
#define AIPS_PACRB_TP3_MASK  (0x1000u)
#define AIPS_PACRB_TP3_SHIFT (12u)
#define AIPS_PACRB_TP3_WIDTH (1u)
#define AIPS_PACRB_SP2_MASK  (0x400u)
#define AIPS_PACRB_SP2_SHIFT (10u)
#define AIPS_PACRB_SP2_WIDTH (1u)
#define AIPS_PACRB_WP2_MASK  (0x200u)
#define AIPS_PACRB_WP2_SHIFT (9u)
#define AIPS_PACRB_WP2_WIDTH (1u)
#define AIPS_PACRB_TP2_MASK  (0x100u)
#define AIPS_PACRB_TP2_SHIFT (8u)
#define AIPS_PACRB_TP2_WIDTH (1u)
#define AIPS_PACRB_SP1_MASK  (0x40u)
#define AIPS_PACRB_SP1_SHIFT (6u)
#define AIPS_PACRB_SP1_WIDTH (1u)
#define AIPS_PACRB_WP1_MASK  (0x20u)
#define AIPS_PACRB_WP1_SHIFT (5u)
#define AIPS_PACRB_WP1_WIDTH (1u)
#define AIPS_PACRB_TP1_MASK  (0x10u)
#define AIPS_PACRB_TP1_SHIFT (4u)
#define AIPS_PACRB_TP1_WIDTH (1u)
#define AIPS_PACRB_SP0_MASK  (0x04u)
#define AIPS_PACRB_SP0_SHIFT (2u)
#define AIPS_PACRB_SP0_WIDTH (1u)
#define AIPS_PACRB_WP0_MASK  (0x02u)
#define AIPS_PACRB_WP0_SHIFT (1u)
#define AIPS_PACRB_WP0_WIDTH (1u)
#define AIPS_PACRB_TP0_MASK  (0x01u)
#define AIPS_PACRB_TP0_SHIFT (0u)
#define AIPS_PACRB_TP0_WIDTH (1u)

/* PACRC Bit Fields */
#define AIPS_PACRC_SP7_MASK  (0x40000000u)
#define AIPS_PACRC_SP7_SHIFT (30u)
#define AIPS_PACRC_SP7_WIDTH (1u)
#define AIPS_PACRC_WP7_MASK  (0x20000000u)
#define AIPS_PACRC_WP7_SHIFT (29u)
#define AIPS_PACRC_WP7_WIDTH (1u)
#define AIPS_PACRC_TP7_MASK  (0x10000000u)
#define AIPS_PACRC_TP7_SHIFT (28u)
#define AIPS_PACRC_TP7_WIDTH (1u)
#define AIPS_PACRC_SP6_MASK  (0x4000000u)
#define AIPS_PACRC_SP6_SHIFT (26u)
#define AIPS_PACRC_SP6_WIDTH (1u)
#define AIPS_PACRC_WP6_MASK  (0x2000000u)
#define AIPS_PACRC_WP6_SHIFT (25u)
#define AIPS_PACRC_WP6_WIDTH (1u)
#define AIPS_PACRC_TP6_MASK  (0x1000000u)
#define AIPS_PACRC_TP6_SHIFT (24u)
#define AIPS_PACRC_TP6_WIDTH (1u)
#define AIPS_PACRC_SP5_MASK  (0x400000u)
#define AIPS_PACRC_SP5_SHIFT (22u)
#define AIPS_PACRC_SP5_WIDTH (1u)
#define AIPS_PACRC_WP5_MASK  (0x200000u)
#define AIPS_PACRC_WP5_SHIFT (21u)
#define AIPS_PACRC_WP5_WIDTH (1u)
#define AIPS_PACRC_TP5_MASK  (0x100000u)
#define AIPS_PACRC_TP5_SHIFT (20u)
#define AIPS_PACRC_TP5_WIDTH (1u)
#define AIPS_PACRC_SP4_MASK  (0x40000u)
#define AIPS_PACRC_SP4_SHIFT (18u)
#define AIPS_PACRC_SP4_WIDTH (1u)
#define AIPS_PACRC_WP4_MASK  (0x20000u)
#define AIPS_PACRC_WP4_SHIFT (17u)
#define AIPS_PACRC_WP4_WIDTH (1u)
#define AIPS_PACRC_TP4_MASK  (0x10000u)
#define AIPS_PACRC_TP4_SHIFT (16u)
#define AIPS_PACRC_TP4_WIDTH (1u)
#define AIPS_PACRC_SP3_MASK  (0x4000u)
#define AIPS_PACRC_SP3_SHIFT (14u)
#define AIPS_PACRC_SP3_WIDTH (1u)
#define AIPS_PACRC_WP3_MASK  (0x2000u)
#define AIPS_PACRC_WP3_SHIFT (13u)
#define AIPS_PACRC_WP3_WIDTH (1u)
#define AIPS_PACRC_TP3_MASK  (0x1000u)
#define AIPS_PACRC_TP3_SHIFT (12u)
#define AIPS_PACRC_TP3_WIDTH (1u)
#define AIPS_PACRC_SP2_MASK  (0x400u)
#define AIPS_PACRC_SP2_SHIFT (10u)
#define AIPS_PACRC_SP2_WIDTH (1u)
#define AIPS_PACRC_WP2_MASK  (0x200u)
#define AIPS_PACRC_WP2_SHIFT (9u)
#define AIPS_PACRC_WP2_WIDTH (1u)
#define AIPS_PACRC_TP2_MASK  (0x100u)
#define AIPS_PACRC_TP2_SHIFT (8u)
#define AIPS_PACRC_TP2_WIDTH (1u)
#define AIPS_PACRC_SP1_MASK  (0x40u)
#define AIPS_PACRC_SP1_SHIFT (6u)
#define AIPS_PACRC_SP1_WIDTH (1u)
#define AIPS_PACRC_WP1_MASK  (0x20u)
#define AIPS_PACRC_WP1_SHIFT (5u)
#define AIPS_PACRC_WP1_WIDTH (1u)
#define AIPS_PACRC_TP1_MASK  (0x10u)
#define AIPS_PACRC_TP1_SHIFT (4u)
#define AIPS_PACRC_TP1_WIDTH (1u)
#define AIPS_PACRC_SP0_MASK  (0x04u)
#define AIPS_PACRC_SP0_SHIFT (2u)
#define AIPS_PACRC_SP0_WIDTH (1u)
#define AIPS_PACRC_WP0_MASK  (0x02u)
#define AIPS_PACRC_WP0_SHIFT (1u)
#define AIPS_PACRC_WP0_WIDTH (1u)
#define AIPS_PACRC_TP0_MASK  (0x01u)
#define AIPS_PACRC_TP0_SHIFT (0u)
#define AIPS_PACRC_TP0_WIDTH (1u)

/* PACRD Bit Fields */
#define AIPS_PACRD_SP7_MASK  (0x40000000u)
#define AIPS_PACRD_SP7_SHIFT (30u)
#define AIPS_PACRD_SP7_WIDTH (1u)
#define AIPS_PACRD_WP7_MASK  (0x20000000u)
#define AIPS_PACRD_WP7_SHIFT (29u)
#define AIPS_PACRD_WP7_WIDTH (1u)
#define AIPS_PACRD_TP7_MASK  (0x10000000u)
#define AIPS_PACRD_TP7_SHIFT (28u)
#define AIPS_PACRD_TP7_WIDTH (1u)
#define AIPS_PACRD_SP6_MASK  (0x4000000u)
#define AIPS_PACRD_SP6_SHIFT (26u)
#define AIPS_PACRD_SP6_WIDTH (1u)
#define AIPS_PACRD_WP6_MASK  (0x2000000u)
#define AIPS_PACRD_WP6_SHIFT (25u)
#define AIPS_PACRD_WP6_WIDTH (1u)
#define AIPS_PACRD_TP6_MASK  (0x1000000u)
#define AIPS_PACRD_TP6_SHIFT (24u)
#define AIPS_PACRD_TP6_WIDTH (1u)
#define AIPS_PACRD_SP5_MASK  (0x400000u)
#define AIPS_PACRD_SP5_SHIFT (22u)
#define AIPS_PACRD_SP5_WIDTH (1u)
#define AIPS_PACRD_WP5_MASK  (0x200000u)
#define AIPS_PACRD_WP5_SHIFT (21u)
#define AIPS_PACRD_WP5_WIDTH (1u)
#define AIPS_PACRD_TP5_MASK  (0x100000u)
#define AIPS_PACRD_TP5_SHIFT (20u)
#define AIPS_PACRD_TP5_WIDTH (1u)
#define AIPS_PACRD_SP4_MASK  (0x40000u)
#define AIPS_PACRD_SP4_SHIFT (18u)
#define AIPS_PACRD_SP4_WIDTH (1u)
#define AIPS_PACRD_WP4_MASK  (0x20000u)
#define AIPS_PACRD_WP4_SHIFT (17u)
#define AIPS_PACRD_WP4_WIDTH (1u)
#define AIPS_PACRD_TP4_MASK  (0x10000u)
#define AIPS_PACRD_TP4_SHIFT (16u)
#define AIPS_PACRD_TP4_WIDTH (1u)
#define AIPS_PACRD_SP3_MASK  (0x4000u)
#define AIPS_PACRD_SP3_SHIFT (14u)
#define AIPS_PACRD_SP3_WIDTH (1u)
#define AIPS_PACRD_WP3_MASK  (0x2000u)
#define AIPS_PACRD_WP3_SHIFT (13u)
#define AIPS_PACRD_WP3_WIDTH (1u)
#define AIPS_PACRD_TP3_MASK  (0x1000u)
#define AIPS_PACRD_TP3_SHIFT (12u)
#define AIPS_PACRD_TP3_WIDTH (1u)
#define AIPS_PACRD_SP2_MASK  (0x400u)
#define AIPS_PACRD_SP2_SHIFT (10u)
#define AIPS_PACRD_SP2_WIDTH (1u)
#define AIPS_PACRD_WP2_MASK  (0x200u)
#define AIPS_PACRD_WP2_SHIFT (9u)
#define AIPS_PACRD_WP2_WIDTH (1u)
#define AIPS_PACRD_TP2_MASK  (0x100u)
#define AIPS_PACRD_TP2_SHIFT (8u)
#define AIPS_PACRD_TP2_WIDTH (1u)
#define AIPS_PACRD_SP1_MASK  (0x40u)
#define AIPS_PACRD_SP1_SHIFT (6u)
#define AIPS_PACRD_SP1_WIDTH (1u)
#define AIPS_PACRD_WP1_MASK  (0x20u)
#define AIPS_PACRD_WP1_SHIFT (5u)
#define AIPS_PACRD_WP1_WIDTH (1u)
#define AIPS_PACRD_TP1_MASK  (0x10u)
#define AIPS_PACRD_TP1_SHIFT (4u)
#define AIPS_PACRD_TP1_WIDTH (1u)
#define AIPS_PACRD_SP0_MASK  (0x04u)
#define AIPS_PACRD_SP0_SHIFT (2u)
#define AIPS_PACRD_SP0_WIDTH (1u)
#define AIPS_PACRD_WP0_MASK  (0x02u)
#define AIPS_PACRD_WP0_SHIFT (1u)
#define AIPS_PACRD_WP0_WIDTH (1u)
#define AIPS_PACRD_TP0_MASK  (0x01u)
#define AIPS_PACRD_TP0_SHIFT (0u)
#define AIPS_PACRD_TP0_WIDTH (1u)

/* PACRE Bit Fields */
#define AIPS_PACRE_SP7_MASK  (0x40000000u)
#define AIPS_PACRE_SP7_SHIFT (30u)
#define AIPS_PACRE_SP7_WIDTH (1u)
#define AIPS_PACRE_WP7_MASK  (0x20000000u)
#define AIPS_PACRE_WP7_SHIFT (29u)
#define AIPS_PACRE_WP7_WIDTH (1u)
#define AIPS_PACRE_TP7_MASK  (0x10000000u)
#define AIPS_PACRE_TP7_SHIFT (28u)
#define AIPS_PACRE_TP7_WIDTH (1u)
#define AIPS_PACRE_SP6_MASK  (0x4000000u)
#define AIPS_PACRE_SP6_SHIFT (26u)
#define AIPS_PACRE_SP6_WIDTH (1u)
#define AIPS_PACRE_WP6_MASK  (0x2000000u)
#define AIPS_PACRE_WP6_SHIFT (25u)
#define AIPS_PACRE_WP6_WIDTH (1u)
#define AIPS_PACRE_TP6_MASK  (0x1000000u)
#define AIPS_PACRE_TP6_SHIFT (24u)
#define AIPS_PACRE_TP6_WIDTH (1u)
#define AIPS_PACRE_SP5_MASK  (0x400000u)
#define AIPS_PACRE_SP5_SHIFT (22u)
#define AIPS_PACRE_SP5_WIDTH (1u)
#define AIPS_PACRE_WP5_MASK  (0x200000u)
#define AIPS_PACRE_WP5_SHIFT (21u)
#define AIPS_PACRE_WP5_WIDTH (1u)
#define AIPS_PACRE_TP5_MASK  (0x100000u)
#define AIPS_PACRE_TP5_SHIFT (20u)
#define AIPS_PACRE_TP5_WIDTH (1u)
#define AIPS_PACRE_SP4_MASK  (0x40000u)
#define AIPS_PACRE_SP4_SHIFT (18u)
#define AIPS_PACRE_SP4_WIDTH (1u)
#define AIPS_PACRE_WP4_MASK  (0x20000u)
#define AIPS_PACRE_WP4_SHIFT (17u)
#define AIPS_PACRE_WP4_WIDTH (1u)
#define AIPS_PACRE_TP4_MASK  (0x10000u)
#define AIPS_PACRE_TP4_SHIFT (16u)
#define AIPS_PACRE_TP4_WIDTH (1u)
#define AIPS_PACRE_SP3_MASK  (0x4000u)
#define AIPS_PACRE_SP3_SHIFT (14u)
#define AIPS_PACRE_SP3_WIDTH (1u)
#define AIPS_PACRE_WP3_MASK  (0x2000u)
#define AIPS_PACRE_WP3_SHIFT (13u)
#define AIPS_PACRE_WP3_WIDTH (1u)
#define AIPS_PACRE_TP3_MASK  (0x1000u)
#define AIPS_PACRE_TP3_SHIFT (12u)
#define AIPS_PACRE_TP3_WIDTH (1u)
#define AIPS_PACRE_SP2_MASK  (0x400u)
#define AIPS_PACRE_SP2_SHIFT (10u)
#define AIPS_PACRE_SP2_WIDTH (1u)
#define AIPS_PACRE_WP2_MASK  (0x200u)
#define AIPS_PACRE_WP2_SHIFT (9u)
#define AIPS_PACRE_WP2_WIDTH (1u)
#define AIPS_PACRE_TP2_MASK  (0x100u)
#define AIPS_PACRE_TP2_SHIFT (8u)
#define AIPS_PACRE_TP2_WIDTH (1u)
#define AIPS_PACRE_SP1_MASK  (0x40u)
#define AIPS_PACRE_SP1_SHIFT (6u)
#define AIPS_PACRE_SP1_WIDTH (1u)
#define AIPS_PACRE_WP1_MASK  (0x20u)
#define AIPS_PACRE_WP1_SHIFT (5u)
#define AIPS_PACRE_WP1_WIDTH (1u)
#define AIPS_PACRE_TP1_MASK  (0x10u)
#define AIPS_PACRE_TP1_SHIFT (4u)
#define AIPS_PACRE_TP1_WIDTH (1u)
#define AIPS_PACRE_SP0_MASK  (0x04u)
#define AIPS_PACRE_SP0_SHIFT (2u)
#define AIPS_PACRE_SP0_WIDTH (1u)
#define AIPS_PACRE_WP0_MASK  (0x02u)
#define AIPS_PACRE_WP0_SHIFT (1u)
#define AIPS_PACRE_WP0_WIDTH (1u)
#define AIPS_PACRE_TP0_MASK  (0x01u)
#define AIPS_PACRE_TP0_SHIFT (0u)
#define AIPS_PACRE_TP0_WIDTH (1u)

/* PACRF Bit Fields */
#define AIPS_PACRF_SP7_MASK  (0x40000000u)
#define AIPS_PACRF_SP7_SHIFT (30u)
#define AIPS_PACRF_SP7_WIDTH (1u)
#define AIPS_PACRF_WP7_MASK  (0x20000000u)
#define AIPS_PACRF_WP7_SHIFT (29u)
#define AIPS_PACRF_WP7_WIDTH (1u)
#define AIPS_PACRF_TP7_MASK  (0x10000000u)
#define AIPS_PACRF_TP7_SHIFT (28u)
#define AIPS_PACRF_TP7_WIDTH (1u)
#define AIPS_PACRF_SP6_MASK  (0x4000000u)
#define AIPS_PACRF_SP6_SHIFT (26u)
#define AIPS_PACRF_SP6_WIDTH (1u)
#define AIPS_PACRF_WP6_MASK  (0x2000000u)
#define AIPS_PACRF_WP6_SHIFT (25u)
#define AIPS_PACRF_WP6_WIDTH (1u)
#define AIPS_PACRF_TP6_MASK  (0x1000000u)
#define AIPS_PACRF_TP6_SHIFT (24u)
#define AIPS_PACRF_TP6_WIDTH (1u)
#define AIPS_PACRF_SP5_MASK  (0x400000u)
#define AIPS_PACRF_SP5_SHIFT (22u)
#define AIPS_PACRF_SP5_WIDTH (1u)
#define AIPS_PACRF_WP5_MASK  (0x200000u)
#define AIPS_PACRF_WP5_SHIFT (21u)
#define AIPS_PACRF_WP5_WIDTH (1u)
#define AIPS_PACRF_TP5_MASK  (0x100000u)
#define AIPS_PACRF_TP5_SHIFT (20u)
#define AIPS_PACRF_TP5_WIDTH (1u)
#define AIPS_PACRF_SP4_MASK  (0x40000u)
#define AIPS_PACRF_SP4_SHIFT (18u)
#define AIPS_PACRF_SP4_WIDTH (1u)
#define AIPS_PACRF_WP4_MASK  (0x20000u)
#define AIPS_PACRF_WP4_SHIFT (17u)
#define AIPS_PACRF_WP4_WIDTH (1u)
#define AIPS_PACRF_TP4_MASK  (0x10000u)
#define AIPS_PACRF_TP4_SHIFT (16u)
#define AIPS_PACRF_TP4_WIDTH (1u)
#define AIPS_PACRF_SP3_MASK  (0x4000u)
#define AIPS_PACRF_SP3_SHIFT (14u)
#define AIPS_PACRF_SP3_WIDTH (1u)
#define AIPS_PACRF_WP3_MASK  (0x2000u)
#define AIPS_PACRF_WP3_SHIFT (13u)
#define AIPS_PACRF_WP3_WIDTH (1u)
#define AIPS_PACRF_TP3_MASK  (0x1000u)
#define AIPS_PACRF_TP3_SHIFT (12u)
#define AIPS_PACRF_TP3_WIDTH (1u)
#define AIPS_PACRF_SP2_MASK  (0x400u)
#define AIPS_PACRF_SP2_SHIFT (10u)
#define AIPS_PACRF_SP2_WIDTH (1u)
#define AIPS_PACRF_WP2_MASK  (0x200u)
#define AIPS_PACRF_WP2_SHIFT (9u)
#define AIPS_PACRF_WP2_WIDTH (1u)
#define AIPS_PACRF_TP2_MASK  (0x100u)
#define AIPS_PACRF_TP2_SHIFT (8u)
#define AIPS_PACRF_TP2_WIDTH (1u)
#define AIPS_PACRF_SP1_MASK  (0x40u)
#define AIPS_PACRF_SP1_SHIFT (6u)
#define AIPS_PACRF_SP1_WIDTH (1u)
#define AIPS_PACRF_WP1_MASK  (0x20u)
#define AIPS_PACRF_WP1_SHIFT (5u)
#define AIPS_PACRF_WP1_WIDTH (1u)
#define AIPS_PACRF_TP1_MASK  (0x10u)
#define AIPS_PACRF_TP1_SHIFT (4u)
#define AIPS_PACRF_TP1_WIDTH (1u)
#define AIPS_PACRF_SP0_MASK  (0x04u)
#define AIPS_PACRF_SP0_SHIFT (2u)
#define AIPS_PACRF_SP0_WIDTH (1u)
#define AIPS_PACRF_WP0_MASK  (0x02u)
#define AIPS_PACRF_WP0_SHIFT (1u)
#define AIPS_PACRF_WP0_WIDTH (1u)
#define AIPS_PACRF_TP0_MASK  (0x01u)
#define AIPS_PACRF_TP0_SHIFT (0u)
#define AIPS_PACRF_TP0_WIDTH (1u)

/* PACRG Bit Fields */
#define AIPS_PACRG_SP7_MASK  (0x40000000u)
#define AIPS_PACRG_SP7_SHIFT (30u)
#define AIPS_PACRG_SP7_WIDTH (1u)
#define AIPS_PACRG_WP7_MASK  (0x20000000u)
#define AIPS_PACRG_WP7_SHIFT (29u)
#define AIPS_PACRG_WP7_WIDTH (1u)
#define AIPS_PACRG_TP7_MASK  (0x10000000u)
#define AIPS_PACRG_TP7_SHIFT (28u)
#define AIPS_PACRG_TP7_WIDTH (1u)
#define AIPS_PACRG_SP6_MASK  (0x4000000u)
#define AIPS_PACRG_SP6_SHIFT (26u)
#define AIPS_PACRG_SP6_WIDTH (1u)
#define AIPS_PACRG_WP6_MASK  (0x2000000u)
#define AIPS_PACRG_WP6_SHIFT (25u)
#define AIPS_PACRG_WP6_WIDTH (1u)
#define AIPS_PACRG_TP6_MASK  (0x1000000u)
#define AIPS_PACRG_TP6_SHIFT (24u)
#define AIPS_PACRG_TP6_WIDTH (1u)
#define AIPS_PACRG_SP5_MASK  (0x400000u)
#define AIPS_PACRG_SP5_SHIFT (22u)
#define AIPS_PACRG_SP5_WIDTH (1u)
#define AIPS_PACRG_WP5_MASK  (0x200000u)
#define AIPS_PACRG_WP5_SHIFT (21u)
#define AIPS_PACRG_WP5_WIDTH (1u)
#define AIPS_PACRG_TP5_MASK  (0x100000u)
#define AIPS_PACRG_TP5_SHIFT (20u)
#define AIPS_PACRG_TP5_WIDTH (1u)
#define AIPS_PACRG_SP4_MASK  (0x40000u)
#define AIPS_PACRG_SP4_SHIFT (18u)
#define AIPS_PACRG_SP4_WIDTH (1u)
#define AIPS_PACRG_WP4_MASK  (0x20000u)
#define AIPS_PACRG_WP4_SHIFT (17u)
#define AIPS_PACRG_WP4_WIDTH (1u)
#define AIPS_PACRG_TP4_MASK  (0x10000u)
#define AIPS_PACRG_TP4_SHIFT (16u)
#define AIPS_PACRG_TP4_WIDTH (1u)
#define AIPS_PACRG_SP3_MASK  (0x4000u)
#define AIPS_PACRG_SP3_SHIFT (14u)
#define AIPS_PACRG_SP3_WIDTH (1u)
#define AIPS_PACRG_WP3_MASK  (0x2000u)
#define AIPS_PACRG_WP3_SHIFT (13u)
#define AIPS_PACRG_WP3_WIDTH (1u)
#define AIPS_PACRG_TP3_MASK  (0x1000u)
#define AIPS_PACRG_TP3_SHIFT (12u)
#define AIPS_PACRG_TP3_WIDTH (1u)
#define AIPS_PACRG_SP2_MASK  (0x400u)
#define AIPS_PACRG_SP2_SHIFT (10u)
#define AIPS_PACRG_SP2_WIDTH (1u)
#define AIPS_PACRG_WP2_MASK  (0x200u)
#define AIPS_PACRG_WP2_SHIFT (9u)
#define AIPS_PACRG_WP2_WIDTH (1u)
#define AIPS_PACRG_TP2_MASK  (0x100u)
#define AIPS_PACRG_TP2_SHIFT (8u)
#define AIPS_PACRG_TP2_WIDTH (1u)
#define AIPS_PACRG_SP1_MASK  (0x40u)
#define AIPS_PACRG_SP1_SHIFT (6u)
#define AIPS_PACRG_SP1_WIDTH (1u)
#define AIPS_PACRG_WP1_MASK  (0x20u)
#define AIPS_PACRG_WP1_SHIFT (5u)
#define AIPS_PACRG_WP1_WIDTH (1u)
#define AIPS_PACRG_TP1_MASK  (0x10u)
#define AIPS_PACRG_TP1_SHIFT (4u)
#define AIPS_PACRG_TP1_WIDTH (1u)
#define AIPS_PACRG_SP0_MASK  (0x04u)
#define AIPS_PACRG_SP0_SHIFT (2u)
#define AIPS_PACRG_SP0_WIDTH (1u)
#define AIPS_PACRG_WP0_MASK  (0x02u)
#define AIPS_PACRG_WP0_SHIFT (1u)
#define AIPS_PACRG_WP0_WIDTH (1u)
#define AIPS_PACRG_TP0_MASK  (0x01u)
#define AIPS_PACRG_TP0_SHIFT (0u)
#define AIPS_PACRG_TP0_WIDTH (1u)

/* PACRH Bit Fields */
#define AIPS_PACRH_SP7_MASK  (0x40000000u)
#define AIPS_PACRH_SP7_SHIFT (30u)
#define AIPS_PACRH_SP7_WIDTH (1u)
#define AIPS_PACRH_WP7_MASK  (0x20000000u)
#define AIPS_PACRH_WP7_SHIFT (29u)
#define AIPS_PACRH_WP7_WIDTH (1u)
#define AIPS_PACRH_TP7_MASK  (0x10000000u)
#define AIPS_PACRH_TP7_SHIFT (28u)
#define AIPS_PACRH_TP7_WIDTH (1u)
#define AIPS_PACRH_SP6_MASK  (0x4000000u)
#define AIPS_PACRH_SP6_SHIFT (26u)
#define AIPS_PACRH_SP6_WIDTH (1u)
#define AIPS_PACRH_WP6_MASK  (0x2000000u)
#define AIPS_PACRH_WP6_SHIFT (25u)
#define AIPS_PACRH_WP6_WIDTH (1u)
#define AIPS_PACRH_TP6_MASK  (0x1000000u)
#define AIPS_PACRH_TP6_SHIFT (24u)
#define AIPS_PACRH_TP6_WIDTH (1u)
#define AIPS_PACRH_SP5_MASK  (0x400000u)
#define AIPS_PACRH_SP5_SHIFT (22u)
#define AIPS_PACRH_SP5_WIDTH (1u)
#define AIPS_PACRH_WP5_MASK  (0x200000u)
#define AIPS_PACRH_WP5_SHIFT (21u)
#define AIPS_PACRH_WP5_WIDTH (1u)
#define AIPS_PACRH_TP5_MASK  (0x100000u)
#define AIPS_PACRH_TP5_SHIFT (20u)
#define AIPS_PACRH_TP5_WIDTH (1u)
#define AIPS_PACRH_SP4_MASK  (0x40000u)
#define AIPS_PACRH_SP4_SHIFT (18u)
#define AIPS_PACRH_SP4_WIDTH (1u)
#define AIPS_PACRH_WP4_MASK  (0x20000u)
#define AIPS_PACRH_WP4_SHIFT (17u)
#define AIPS_PACRH_WP4_WIDTH (1u)
#define AIPS_PACRH_TP4_MASK  (0x10000u)
#define AIPS_PACRH_TP4_SHIFT (16u)
#define AIPS_PACRH_TP4_WIDTH (1u)
#define AIPS_PACRH_SP3_MASK  (0x4000u)
#define AIPS_PACRH_SP3_SHIFT (14u)
#define AIPS_PACRH_SP3_WIDTH (1u)
#define AIPS_PACRH_WP3_MASK  (0x2000u)
#define AIPS_PACRH_WP3_SHIFT (13u)
#define AIPS_PACRH_WP3_WIDTH (1u)
#define AIPS_PACRH_TP3_MASK  (0x1000u)
#define AIPS_PACRH_TP3_SHIFT (12u)
#define AIPS_PACRH_TP3_WIDTH (1u)
#define AIPS_PACRH_SP2_MASK  (0x400u)
#define AIPS_PACRH_SP2_SHIFT (10u)
#define AIPS_PACRH_SP2_WIDTH (1u)
#define AIPS_PACRH_WP2_MASK  (0x200u)
#define AIPS_PACRH_WP2_SHIFT (9u)
#define AIPS_PACRH_WP2_WIDTH (1u)
#define AIPS_PACRH_TP2_MASK  (0x100u)
#define AIPS_PACRH_TP2_SHIFT (8u)
#define AIPS_PACRH_TP2_WIDTH (1u)
#define AIPS_PACRH_SP1_MASK  (0x40u)
#define AIPS_PACRH_SP1_SHIFT (6u)
#define AIPS_PACRH_SP1_WIDTH (1u)
#define AIPS_PACRH_WP1_MASK  (0x20u)
#define AIPS_PACRH_WP1_SHIFT (5u)
#define AIPS_PACRH_WP1_WIDTH (1u)
#define AIPS_PACRH_TP1_MASK  (0x10u)
#define AIPS_PACRH_TP1_SHIFT (4u)
#define AIPS_PACRH_TP1_WIDTH (1u)
#define AIPS_PACRH_SP0_MASK  (0x04u)
#define AIPS_PACRH_SP0_SHIFT (2u)
#define AIPS_PACRH_SP0_WIDTH (1u)
#define AIPS_PACRH_WP0_MASK  (0x02u)
#define AIPS_PACRH_WP0_SHIFT (1u)
#define AIPS_PACRH_WP0_WIDTH (1u)
#define AIPS_PACRH_TP0_MASK  (0x01u)
#define AIPS_PACRH_TP0_SHIFT (0u)
#define AIPS_PACRH_TP0_WIDTH (1u)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief The definition of AIPS registers
 */
typedef struct _AipsRegType_
{
    volatile uint32_t MPRA;         /*!< Master Privilege Register, offset: 0x00 */
    uint32_t          RESERVED0[7]; /*!< Reserverd block, offset: 0x04 */
    volatile uint32_t PACRA;        /*!< Peripheral Access Control Register A, offset: 0x20 */
    volatile uint32_t PACRB;        /*!< Peripheral Access Control Register B, offset: 0x24 */
    volatile uint32_t PACRC;        /*!< Peripheral Access Control Register C, offset: 0x28 */
    volatile uint32_t PACRD;        /*!< Peripheral Access Control Register D, offset: 0x2C */
    volatile uint32_t PACRE;        /*!< Peripheral Access Control Register E, offset: 0x30 */
    volatile uint32_t PACRF;        /*!< Peripheral Access Control Register F, offset: 0x34 */
    volatile uint32_t PACRG;        /*!< Peripheral Access Control Register G, offset: 0x38 */
    volatile uint32_t PACRH;        /*!< Peripheral Access Control Register H, offset: 0x3C */
} AipsRegType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Gets the Master 0 Trusted For read
 *
 * This function gets the current Master 0 Trusted For read.
 * Determines whether the Master is trusted For read accesses.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Master 0 Trusted For read
 *         - 0b : This Master is not trusted For read accesses.
 *         - 1b : This Master is trusted For read accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetMpraMtr0(const AipsRegType *obj)
{
    return ((obj->MPRA & AIPS_MPRA_MTR0_MASK) >> AIPS_MPRA_MTR0_SHIFT);
}

/*! \brief Sets the Master 0 Trusted For read
 *
 * This function sets the Master 0 Trusted For read.
 * Determines whether the Master is trusted For read accesses.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Master 0 Trusted For read
 *                    - 0b : This Master is not trusted For read accesses.
 *                    - 1b : This Master is trusted For read accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetMpraMtr0(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MPRA;

    tmp &= ~AIPS_MPRA_MTR0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_MPRA_MTR0_SHIFT)) & AIPS_MPRA_MTR0_MASK);
    obj->MPRA = tmp;
}

/*! \brief Gets the Master 0 Trusted For write
 *
 * This function gets the current Master 0 Trusted For write.
 * Determines whether the Master is trusted for write accesses.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Master 0 Trusted For write
 *         - 0b : This Master is not trusted for write accesses.
 *         - 1b : This Master is trusted for write accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetMpraMtw0(const AipsRegType *obj)
{
    return ((obj->MPRA & AIPS_MPRA_MTW0_MASK) >> AIPS_MPRA_MTW0_SHIFT);
}

/*! \brief Sets the Master 0 Trusted For write
 *
 * This function sets the Master 0 Trusted For write.
 * Determines whether the Master is trusted for write accesses.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Master 0 Trusted For write
 *                    - 0b : This Master is not trusted for write accesses.
 *                    - 1b : This Master is trusted for write accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetMpraMtw0(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MPRA;

    tmp &= ~AIPS_MPRA_MTW0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_MPRA_MTW0_SHIFT)) & AIPS_MPRA_MTW0_MASK);
    obj->MPRA = tmp;
}

/*! \brief Gets the Master 0 Privilege Level
 *
 * This function gets the current Master 0 Privilege Level.
 * Specifies how the Privilege Level# of the Master is determined.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Master 0 Privilege Level
 *         - 0b : Accesses from this Master are forced to user-mode.
 *         - 1b : Accesses from this Master are not forced to user-mode.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetMpraMpl0(const AipsRegType *obj)
{
    return ((obj->MPRA & AIPS_MPRA_MPL0_MASK) >> AIPS_MPRA_MPL0_SHIFT);
}

/*! \brief Sets the Master 0 Privilege Level
 *
 * This function sets the Master 0 Privilege Level.
 * Specifies how the Privilege Level# of the Master is determined.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Master 0 Privilege Level
 *                    - 0b : Accesses from this Master are forced to user-mode.
 *                    - 1b : Accesses from this Master are not forced to user-mode.
 */
__attribute__((always_inline)) static inline void AipsReg_SetMpraMpl0(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MPRA;

    tmp &= ~AIPS_MPRA_MPL0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_MPRA_MPL0_SHIFT)) & AIPS_MPRA_MPL0_MASK);
    obj->MPRA = tmp;
}

/*! \brief Gets the Master 1 Trusted For read
 *
 * This function gets the current Master 1 Trusted For read.
 * Determines whether the Master is trusted For read accesses.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Master 1 Trusted For read
 *         - 0b : This Master is not trusted For read accesses.
 *         - 1b : This Master is trusted For read accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetMpraMtr1(const AipsRegType *obj)
{
    return ((obj->MPRA & AIPS_MPRA_MTR1_MASK) >> AIPS_MPRA_MTR1_SHIFT);
}

/*! \brief Sets the Master 1 Trusted For read
 *
 * This function sets the Master 1 Trusted For read.
 * Determines whether the Master is trusted For read accesses.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Master 1 Trusted For read
 *                    - 0b : This Master is not trusted For read accesses.
 *                    - 1b : This Master is trusted For read accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetMpraMtr1(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MPRA;

    tmp &= ~AIPS_MPRA_MTR1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_MPRA_MTR1_SHIFT)) & AIPS_MPRA_MTR1_MASK);
    obj->MPRA = tmp;
}

/*! \brief Gets the Master 1 Trusted For write
 *
 * This function gets the current Master 1 Trusted For write.
 * Determines whether the Master is trusted for write accesses.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Master 1 Trusted For write
 *         - 0b : This Master is not trusted for write accesses.
 *         - 1b : This Master is trusted for write accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetMpraMtw1(const AipsRegType *obj)
{
    return ((obj->MPRA & AIPS_MPRA_MTW1_MASK) >> AIPS_MPRA_MTW1_SHIFT);
}

/*! \brief Sets the Master 1 Trusted For write
 *
 * This function sets the Master 1 Trusted For write.
 * Determines whether the Master is trusted for write accesses.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Master 1 Trusted For write
 *                    - 0b : This Master is not trusted for write accesses.
 *                    - 1b : This Master is trusted for write accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetMpraMtw1(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MPRA;

    tmp &= ~AIPS_MPRA_MTW1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_MPRA_MTW1_SHIFT)) & AIPS_MPRA_MTW1_MASK);
    obj->MPRA = tmp;
}

/*! \brief Gets the Master 1 Privilege Level
 *
 * This function gets the current Master 1 Privilege Level.
 * Specifies how the Privilege Level# of the Master is determined.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Master 1 Privilege Level
 *         - 0b : Accesses from this Master are forced to user-mode.
 *         - 1b : Accesses from this Master are not forced to user-mode.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetMpraMpl1(const AipsRegType *obj)
{
    return ((obj->MPRA & AIPS_MPRA_MPL1_MASK) >> AIPS_MPRA_MPL1_SHIFT);
}

/*! \brief Sets the Master 1 Privilege Level
 *
 * This function sets the Master 1 Privilege Level.
 * Specifies how the Privilege Level# of the Master is determined.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Master 1 Privilege Level
 *                    - 0b : Accesses from this Master are forced to user-mode.
 *                    - 1b : Accesses from this Master are not forced to user-mode.
 */
__attribute__((always_inline)) static inline void AipsReg_SetMpraMpl1(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MPRA;

    tmp &= ~AIPS_MPRA_MPL1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_MPRA_MPL1_SHIFT)) & AIPS_MPRA_MPL1_MASK);
    obj->MPRA = tmp;
}

/*! \brief Gets the Master 2 Trusted For read
 *
 * This function gets the current Master 2 Trusted For read.
 * Determines whether the Master is trusted For read accesses.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Master 2 Trusted For read
 *         - 0b : This Master is not trusted For read accesses.
 *         - 1b : This Master is trusted For read accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetMpraMtr2(const AipsRegType *obj)
{
    return ((obj->MPRA & AIPS_MPRA_MTR2_MASK) >> AIPS_MPRA_MTR2_SHIFT);
}

/*! \brief Sets the Master 2 Trusted For read
 *
 * This function sets the Master 2 Trusted For read.
 * Determines whether the Master is trusted For read accesses.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Master 2 Trusted For read
 *                    - 0b : This Master is not trusted For read accesses.
 *                    - 1b : This Master is trusted For read accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetMpraMtr2(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MPRA;

    tmp &= ~AIPS_MPRA_MTR2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_MPRA_MTR2_SHIFT)) & AIPS_MPRA_MTR2_MASK);
    obj->MPRA = tmp;
}

/*! \brief Gets the Master 2 Trusted For write
 *
 * This function gets the current Master 2 Trusted For write.
 * Determines whether the Master is trusted for write accesses.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Master 2 Trusted For write
 *         - 0b : This Master is not trusted for write accesses.
 *         - 1b : This Master is trusted for write accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetMpraMtw2(const AipsRegType *obj)
{
    return ((obj->MPRA & AIPS_MPRA_MTW2_MASK) >> AIPS_MPRA_MTW2_SHIFT);
}

/*! \brief Sets the Master 2 Trusted For write
 *
 * This function sets the Master 2 Trusted For write.
 * Determines whether the Master is trusted for write accesses.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Master 2 Trusted For write
 *                    - 0b : This Master is not trusted for write accesses.
 *                    - 1b : This Master is trusted for write accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetMpraMtw2(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MPRA;

    tmp &= ~AIPS_MPRA_MTW2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_MPRA_MTW2_SHIFT)) & AIPS_MPRA_MTW2_MASK);
    obj->MPRA = tmp;
}

/*! \brief Gets the Master 2 Privilege Level
 *
 * This function gets the current Master 2 Privilege Level.
 * Specifies how the Privilege Level# of the Master is determined.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Master 2 Privilege Level
 *         - 0b : Accesses from this Master are forced to user-mode.
 *         - 1b : Accesses from this Master are not forced to user-mode.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetMpraMpl2(const AipsRegType *obj)
{
    return ((obj->MPRA & AIPS_MPRA_MPL2_MASK) >> AIPS_MPRA_MPL2_SHIFT);
}

/*! \brief Sets the Master 2 Privilege Level
 *
 * This function sets the Master 2 Privilege Level.
 * Specifies how the Privilege Level# of the Master is determined.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Master 2 Privilege Level
 *                    - 0b : Accesses from this Master are forced to user-mode.
 *                    - 1b : Accesses from this Master are not forced to user-mode.
 */
__attribute__((always_inline)) static inline void AipsReg_SetMpraMpl2(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MPRA;

    tmp &= ~AIPS_MPRA_MPL2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_MPRA_MPL2_SHIFT)) & AIPS_MPRA_MPL2_MASK);
    obj->MPRA = tmp;
}

/*! \brief Gets the Master 3 Trusted For read
 *
 * This function gets the current Master 3 Trusted For read.
 * Determines whether the Master is trusted For read accesses.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Master 3 Trusted For read
 *         - 0b : This Master is not trusted For read accesses.
 *         - 1b : This Master is trusted For read accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetMpraMtr3(const AipsRegType *obj)
{
    return ((obj->MPRA & AIPS_MPRA_MTR3_MASK) >> AIPS_MPRA_MTR3_SHIFT);
}

/*! \brief Sets the Master 3 Trusted For read
 *
 * This function sets the Master 3 Trusted For read.
 * Determines whether the Master is trusted For read accesses.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Master 3 Trusted For read
 *                    - 0b : This Master is not trusted For read accesses.
 *                    - 1b : This Master is trusted For read accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetMpraMtr3(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MPRA;

    tmp &= ~AIPS_MPRA_MTR3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_MPRA_MTR3_SHIFT)) & AIPS_MPRA_MTR3_MASK);
    obj->MPRA = tmp;
}

/*! \brief Gets the Master 3 Trusted For write
 *
 * This function gets the current Master 3 Trusted For write.
 * Determines whether the Master is trusted for write accesses.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Master 3 Trusted For write
 *         - 0b : This Master is not trusted for write accesses.
 *         - 1b : This Master is trusted for write accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetMpraMtw3(const AipsRegType *obj)
{
    return ((obj->MPRA & AIPS_MPRA_MTW3_MASK) >> AIPS_MPRA_MTW3_SHIFT);
}

/*! \brief Sets the Master 3 Trusted For write
 *
 * This function sets the Master 3 Trusted For write.
 * Determines whether the Master is trusted for write accesses.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Master 3 Trusted For write
 *                    - 0b : This Master is not trusted for write accesses.
 *                    - 1b : This Master is trusted for write accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetMpraMtw3(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MPRA;

    tmp &= ~AIPS_MPRA_MTW3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_MPRA_MTW3_SHIFT)) & AIPS_MPRA_MTW3_MASK);
    obj->MPRA = tmp;
}

/*! \brief Gets the Master 3 Privilege Level
 *
 * This function gets the current Master 3 Privilege Level.
 * Specifies how the Privilege Level# of the Master is determined.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Master 3 Privilege Level
 *         - 0b : Accesses from this Master are forced to user-mode.
 *         - 1b : Accesses from this Master are not forced to user-mode.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetMpraMpl3(const AipsRegType *obj)
{
    return ((obj->MPRA & AIPS_MPRA_MPL3_MASK) >> AIPS_MPRA_MPL3_SHIFT);
}

/*! \brief Sets the Master 3 Privilege Level
 *
 * This function sets the Master 3 Privilege Level.
 * Specifies how the Privilege Level# of the Master is determined.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Master 3 Privilege Level
 *                    - 0b : Accesses from this Master are forced to user-mode.
 *                    - 1b : Accesses from this Master are not forced to user-mode.
 */
__attribute__((always_inline)) static inline void AipsReg_SetMpraMpl3(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->MPRA;

    tmp &= ~AIPS_MPRA_MPL3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_MPRA_MPL3_SHIFT)) & AIPS_MPRA_MPL3_MASK);
    obj->MPRA = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrASp7(const AipsRegType *obj)
{
    return ((obj->PACRA & AIPS_PACRA_SP7_MASK) >> AIPS_PACRA_SP7_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrASp7(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRA;

    tmp &= ~AIPS_PACRA_SP7_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRA_SP7_SHIFT)) & AIPS_PACRA_SP7_MASK);
    obj->PACRA = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrAWp7(const AipsRegType *obj)
{
    return ((obj->PACRA & AIPS_PACRA_WP7_MASK) >> AIPS_PACRA_WP7_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrAWp7(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRA;

    tmp &= ~AIPS_PACRA_WP7_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRA_WP7_SHIFT)) & AIPS_PACRA_WP7_MASK);
    obj->PACRA = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrATp7(const AipsRegType *obj)
{
    return ((obj->PACRA & AIPS_PACRA_TP7_MASK) >> AIPS_PACRA_TP7_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrATp7(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRA;

    tmp &= ~AIPS_PACRA_TP7_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRA_TP7_SHIFT)) & AIPS_PACRA_TP7_MASK);
    obj->PACRA = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrASp6(const AipsRegType *obj)
{
    return ((obj->PACRA & AIPS_PACRA_SP6_MASK) >> AIPS_PACRA_SP6_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrASp6(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRA;

    tmp &= ~AIPS_PACRA_SP6_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRA_SP6_SHIFT)) & AIPS_PACRA_SP6_MASK);
    obj->PACRA = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrAWp6(const AipsRegType *obj)
{
    return ((obj->PACRA & AIPS_PACRA_WP6_MASK) >> AIPS_PACRA_WP6_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrAWp6(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRA;

    tmp &= ~AIPS_PACRA_WP6_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRA_WP6_SHIFT)) & AIPS_PACRA_WP6_MASK);
    obj->PACRA = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrATp6(const AipsRegType *obj)
{
    return ((obj->PACRA & AIPS_PACRA_TP6_MASK) >> AIPS_PACRA_TP6_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrATp6(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRA;

    tmp &= ~AIPS_PACRA_TP6_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRA_TP6_SHIFT)) & AIPS_PACRA_TP6_MASK);
    obj->PACRA = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrASp5(const AipsRegType *obj)
{
    return ((obj->PACRA & AIPS_PACRA_SP5_MASK) >> AIPS_PACRA_SP5_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrASp5(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRA;

    tmp &= ~AIPS_PACRA_SP5_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRA_SP5_SHIFT)) & AIPS_PACRA_SP5_MASK);
    obj->PACRA = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrAWp5(const AipsRegType *obj)
{
    return ((obj->PACRA & AIPS_PACRA_WP5_MASK) >> AIPS_PACRA_WP5_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrAWp5(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRA;

    tmp &= ~AIPS_PACRA_WP5_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRA_WP5_SHIFT)) & AIPS_PACRA_WP5_MASK);
    obj->PACRA = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrATp5(const AipsRegType *obj)
{
    return ((obj->PACRA & AIPS_PACRA_TP5_MASK) >> AIPS_PACRA_TP5_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrATp5(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRA;

    tmp &= ~AIPS_PACRA_TP5_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRA_TP5_SHIFT)) & AIPS_PACRA_TP5_MASK);
    obj->PACRA = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrASp4(const AipsRegType *obj)
{
    return ((obj->PACRA & AIPS_PACRA_SP4_MASK) >> AIPS_PACRA_SP4_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrASp4(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRA;

    tmp &= ~AIPS_PACRA_SP4_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRA_SP4_SHIFT)) & AIPS_PACRA_SP4_MASK);
    obj->PACRA = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrAWp4(const AipsRegType *obj)
{
    return ((obj->PACRA & AIPS_PACRA_WP4_MASK) >> AIPS_PACRA_WP4_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrAWp4(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRA;

    tmp &= ~AIPS_PACRA_WP4_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRA_WP4_SHIFT)) & AIPS_PACRA_WP4_MASK);
    obj->PACRA = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrATp4(const AipsRegType *obj)
{
    return ((obj->PACRA & AIPS_PACRA_TP4_MASK) >> AIPS_PACRA_TP4_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrATp4(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRA;

    tmp &= ~AIPS_PACRA_TP4_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRA_TP4_SHIFT)) & AIPS_PACRA_TP4_MASK);
    obj->PACRA = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrASp3(const AipsRegType *obj)
{
    return ((obj->PACRA & AIPS_PACRA_SP3_MASK) >> AIPS_PACRA_SP3_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrASp3(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRA;

    tmp &= ~AIPS_PACRA_SP3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRA_SP3_SHIFT)) & AIPS_PACRA_SP3_MASK);
    obj->PACRA = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrAWp3(const AipsRegType *obj)
{
    return ((obj->PACRA & AIPS_PACRA_WP3_MASK) >> AIPS_PACRA_WP3_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrAWp3(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRA;

    tmp &= ~AIPS_PACRA_WP3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRA_WP3_SHIFT)) & AIPS_PACRA_WP3_MASK);
    obj->PACRA = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrATp3(const AipsRegType *obj)
{
    return ((obj->PACRA & AIPS_PACRA_TP3_MASK) >> AIPS_PACRA_TP3_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrATp3(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRA;

    tmp &= ~AIPS_PACRA_TP3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRA_TP3_SHIFT)) & AIPS_PACRA_TP3_MASK);
    obj->PACRA = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrASp2(const AipsRegType *obj)
{
    return ((obj->PACRA & AIPS_PACRA_SP2_MASK) >> AIPS_PACRA_SP2_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrASp2(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRA;

    tmp &= ~AIPS_PACRA_SP2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRA_SP2_SHIFT)) & AIPS_PACRA_SP2_MASK);
    obj->PACRA = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrAWp2(const AipsRegType *obj)
{
    return ((obj->PACRA & AIPS_PACRA_WP2_MASK) >> AIPS_PACRA_WP2_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrAWp2(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRA;

    tmp &= ~AIPS_PACRA_WP2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRA_WP2_SHIFT)) & AIPS_PACRA_WP2_MASK);
    obj->PACRA = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrATp2(const AipsRegType *obj)
{
    return ((obj->PACRA & AIPS_PACRA_TP2_MASK) >> AIPS_PACRA_TP2_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrATp2(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRA;

    tmp &= ~AIPS_PACRA_TP2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRA_TP2_SHIFT)) & AIPS_PACRA_TP2_MASK);
    obj->PACRA = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrASp1(const AipsRegType *obj)
{
    return ((obj->PACRA & AIPS_PACRA_SP1_MASK) >> AIPS_PACRA_SP1_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrASp1(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRA;

    tmp &= ~AIPS_PACRA_SP1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRA_SP1_SHIFT)) & AIPS_PACRA_SP1_MASK);
    obj->PACRA = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrAWp1(const AipsRegType *obj)
{
    return ((obj->PACRA & AIPS_PACRA_WP1_MASK) >> AIPS_PACRA_WP1_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrAWp1(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRA;

    tmp &= ~AIPS_PACRA_WP1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRA_WP1_SHIFT)) & AIPS_PACRA_WP1_MASK);
    obj->PACRA = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrATp1(const AipsRegType *obj)
{
    return ((obj->PACRA & AIPS_PACRA_TP1_MASK) >> AIPS_PACRA_TP1_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrATp1(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRA;

    tmp &= ~AIPS_PACRA_TP1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRA_TP1_SHIFT)) & AIPS_PACRA_TP1_MASK);
    obj->PACRA = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrASp0(const AipsRegType *obj)
{
    return ((obj->PACRA & AIPS_PACRA_SP0_MASK) >> AIPS_PACRA_SP0_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrASp0(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRA;

    tmp &= ~AIPS_PACRA_SP0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRA_SP0_SHIFT)) & AIPS_PACRA_SP0_MASK);
    obj->PACRA = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrAWp0(const AipsRegType *obj)
{
    return ((obj->PACRA & AIPS_PACRA_WP0_MASK) >> AIPS_PACRA_WP0_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrAWp0(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRA;

    tmp &= ~AIPS_PACRA_WP0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRA_WP0_SHIFT)) & AIPS_PACRA_WP0_MASK);
    obj->PACRA = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrATp0(const AipsRegType *obj)
{
    return ((obj->PACRA & AIPS_PACRA_TP0_MASK) >> AIPS_PACRA_TP0_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrATp0(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRA;

    tmp &= ~AIPS_PACRA_TP0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRA_TP0_SHIFT)) & AIPS_PACRA_TP0_MASK);
    obj->PACRA = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrBSp7(const AipsRegType *obj)
{
    return ((obj->PACRB & AIPS_PACRB_SP7_MASK) >> AIPS_PACRB_SP7_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrBSp7(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRB;

    tmp &= ~AIPS_PACRB_SP7_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRB_SP7_SHIFT)) & AIPS_PACRB_SP7_MASK);
    obj->PACRB = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrBWp7(const AipsRegType *obj)
{
    return ((obj->PACRB & AIPS_PACRB_WP7_MASK) >> AIPS_PACRB_WP7_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrBWp7(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRB;

    tmp &= ~AIPS_PACRB_WP7_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRB_WP7_SHIFT)) & AIPS_PACRB_WP7_MASK);
    obj->PACRB = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrBTp7(const AipsRegType *obj)
{
    return ((obj->PACRB & AIPS_PACRB_TP7_MASK) >> AIPS_PACRB_TP7_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrBTp7(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRB;

    tmp &= ~AIPS_PACRB_TP7_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRB_TP7_SHIFT)) & AIPS_PACRB_TP7_MASK);
    obj->PACRB = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrBSp6(const AipsRegType *obj)
{
    return ((obj->PACRB & AIPS_PACRB_SP6_MASK) >> AIPS_PACRB_SP6_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrBSp6(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRB;

    tmp &= ~AIPS_PACRB_SP6_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRB_SP6_SHIFT)) & AIPS_PACRB_SP6_MASK);
    obj->PACRB = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrBWp6(const AipsRegType *obj)
{
    return ((obj->PACRB & AIPS_PACRB_WP6_MASK) >> AIPS_PACRB_WP6_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrBWp6(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRB;

    tmp &= ~AIPS_PACRB_WP6_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRB_WP6_SHIFT)) & AIPS_PACRB_WP6_MASK);
    obj->PACRB = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrBTp6(const AipsRegType *obj)
{
    return ((obj->PACRB & AIPS_PACRB_TP6_MASK) >> AIPS_PACRB_TP6_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrBTp6(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRB;

    tmp &= ~AIPS_PACRB_TP6_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRB_TP6_SHIFT)) & AIPS_PACRB_TP6_MASK);
    obj->PACRB = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrBSp5(const AipsRegType *obj)
{
    return ((obj->PACRB & AIPS_PACRB_SP5_MASK) >> AIPS_PACRB_SP5_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrBSp5(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRB;

    tmp &= ~AIPS_PACRB_SP5_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRB_SP5_SHIFT)) & AIPS_PACRB_SP5_MASK);
    obj->PACRB = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrBWp5(const AipsRegType *obj)
{
    return ((obj->PACRB & AIPS_PACRB_WP5_MASK) >> AIPS_PACRB_WP5_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrBWp5(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRB;

    tmp &= ~AIPS_PACRB_WP5_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRB_WP5_SHIFT)) & AIPS_PACRB_WP5_MASK);
    obj->PACRB = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrBTp5(const AipsRegType *obj)
{
    return ((obj->PACRB & AIPS_PACRB_TP5_MASK) >> AIPS_PACRB_TP5_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrBTp5(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRB;

    tmp &= ~AIPS_PACRB_TP5_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRB_TP5_SHIFT)) & AIPS_PACRB_TP5_MASK);
    obj->PACRB = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrBSp4(const AipsRegType *obj)
{
    return ((obj->PACRB & AIPS_PACRB_SP4_MASK) >> AIPS_PACRB_SP4_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrBSp4(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRB;

    tmp &= ~AIPS_PACRB_SP4_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRB_SP4_SHIFT)) & AIPS_PACRB_SP4_MASK);
    obj->PACRB = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrBWp4(const AipsRegType *obj)
{
    return ((obj->PACRB & AIPS_PACRB_WP4_MASK) >> AIPS_PACRB_WP4_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrBWp4(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRB;

    tmp &= ~AIPS_PACRB_WP4_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRB_WP4_SHIFT)) & AIPS_PACRB_WP4_MASK);
    obj->PACRB = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrBTp4(const AipsRegType *obj)
{
    return ((obj->PACRB & AIPS_PACRB_TP4_MASK) >> AIPS_PACRB_TP4_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrBTp4(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRB;

    tmp &= ~AIPS_PACRB_TP4_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRB_TP4_SHIFT)) & AIPS_PACRB_TP4_MASK);
    obj->PACRB = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrBSp3(const AipsRegType *obj)
{
    return ((obj->PACRB & AIPS_PACRB_SP3_MASK) >> AIPS_PACRB_SP3_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrBSp3(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRB;

    tmp &= ~AIPS_PACRB_SP3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRB_SP3_SHIFT)) & AIPS_PACRB_SP3_MASK);
    obj->PACRB = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrBWp3(const AipsRegType *obj)
{
    return ((obj->PACRB & AIPS_PACRB_WP3_MASK) >> AIPS_PACRB_WP3_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrBWp3(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRB;

    tmp &= ~AIPS_PACRB_WP3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRB_WP3_SHIFT)) & AIPS_PACRB_WP3_MASK);
    obj->PACRB = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrBTp3(const AipsRegType *obj)
{
    return ((obj->PACRB & AIPS_PACRB_TP3_MASK) >> AIPS_PACRB_TP3_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrBTp3(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRB;

    tmp &= ~AIPS_PACRB_TP3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRB_TP3_SHIFT)) & AIPS_PACRB_TP3_MASK);
    obj->PACRB = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrBSp2(const AipsRegType *obj)
{
    return ((obj->PACRB & AIPS_PACRB_SP2_MASK) >> AIPS_PACRB_SP2_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrBSp2(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRB;

    tmp &= ~AIPS_PACRB_SP2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRB_SP2_SHIFT)) & AIPS_PACRB_SP2_MASK);
    obj->PACRB = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrBWp2(const AipsRegType *obj)
{
    return ((obj->PACRB & AIPS_PACRB_WP2_MASK) >> AIPS_PACRB_WP2_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrBWp2(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRB;

    tmp &= ~AIPS_PACRB_WP2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRB_WP2_SHIFT)) & AIPS_PACRB_WP2_MASK);
    obj->PACRB = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrBTp2(const AipsRegType *obj)
{
    return ((obj->PACRB & AIPS_PACRB_TP2_MASK) >> AIPS_PACRB_TP2_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrBTp2(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRB;

    tmp &= ~AIPS_PACRB_TP2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRB_TP2_SHIFT)) & AIPS_PACRB_TP2_MASK);
    obj->PACRB = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrBSp1(const AipsRegType *obj)
{
    return ((obj->PACRB & AIPS_PACRB_SP1_MASK) >> AIPS_PACRB_SP1_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrBSp1(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRB;

    tmp &= ~AIPS_PACRB_SP1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRB_SP1_SHIFT)) & AIPS_PACRB_SP1_MASK);
    obj->PACRB = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrBWp1(const AipsRegType *obj)
{
    return ((obj->PACRB & AIPS_PACRB_WP1_MASK) >> AIPS_PACRB_WP1_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrBWp1(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRB;

    tmp &= ~AIPS_PACRB_WP1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRB_WP1_SHIFT)) & AIPS_PACRB_WP1_MASK);
    obj->PACRB = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrBTp1(const AipsRegType *obj)
{
    return ((obj->PACRB & AIPS_PACRB_TP1_MASK) >> AIPS_PACRB_TP1_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrBTp1(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRB;

    tmp &= ~AIPS_PACRB_TP1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRB_TP1_SHIFT)) & AIPS_PACRB_TP1_MASK);
    obj->PACRB = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrBSp0(const AipsRegType *obj)
{
    return ((obj->PACRB & AIPS_PACRB_SP0_MASK) >> AIPS_PACRB_SP0_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrBSp0(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRB;

    tmp &= ~AIPS_PACRB_SP0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRB_SP0_SHIFT)) & AIPS_PACRB_SP0_MASK);
    obj->PACRB = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrBWp0(const AipsRegType *obj)
{
    return ((obj->PACRB & AIPS_PACRB_WP0_MASK) >> AIPS_PACRB_WP0_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrBWp0(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRB;

    tmp &= ~AIPS_PACRB_WP0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRB_WP0_SHIFT)) & AIPS_PACRB_WP0_MASK);
    obj->PACRB = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrBTp0(const AipsRegType *obj)
{
    return ((obj->PACRB & AIPS_PACRB_TP0_MASK) >> AIPS_PACRB_TP0_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrBTp0(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRB;

    tmp &= ~AIPS_PACRB_TP0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRB_TP0_SHIFT)) & AIPS_PACRB_TP0_MASK);
    obj->PACRB = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrCSp7(const AipsRegType *obj)
{
    return ((obj->PACRC & AIPS_PACRC_SP7_MASK) >> AIPS_PACRC_SP7_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrCSp7(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRC;

    tmp &= ~AIPS_PACRC_SP7_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRC_SP7_SHIFT)) & AIPS_PACRC_SP7_MASK);
    obj->PACRC = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrCWp7(const AipsRegType *obj)
{
    return ((obj->PACRC & AIPS_PACRC_WP7_MASK) >> AIPS_PACRC_WP7_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrCWp7(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRC;

    tmp &= ~AIPS_PACRC_WP7_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRC_WP7_SHIFT)) & AIPS_PACRC_WP7_MASK);
    obj->PACRC = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrCTp7(const AipsRegType *obj)
{
    return ((obj->PACRC & AIPS_PACRC_TP7_MASK) >> AIPS_PACRC_TP7_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrCTp7(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRC;

    tmp &= ~AIPS_PACRC_TP7_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRC_TP7_SHIFT)) & AIPS_PACRC_TP7_MASK);
    obj->PACRC = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrCSp6(const AipsRegType *obj)
{
    return ((obj->PACRC & AIPS_PACRC_SP6_MASK) >> AIPS_PACRC_SP6_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrCSp6(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRC;

    tmp &= ~AIPS_PACRC_SP6_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRC_SP6_SHIFT)) & AIPS_PACRC_SP6_MASK);
    obj->PACRC = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrCWp6(const AipsRegType *obj)
{
    return ((obj->PACRC & AIPS_PACRC_WP6_MASK) >> AIPS_PACRC_WP6_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrCWp6(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRC;

    tmp &= ~AIPS_PACRC_WP6_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRC_WP6_SHIFT)) & AIPS_PACRC_WP6_MASK);
    obj->PACRC = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrCTp6(const AipsRegType *obj)
{
    return ((obj->PACRC & AIPS_PACRC_TP6_MASK) >> AIPS_PACRC_TP6_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrCTp6(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRC;

    tmp &= ~AIPS_PACRC_TP6_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRC_TP6_SHIFT)) & AIPS_PACRC_TP6_MASK);
    obj->PACRC = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrCSp5(const AipsRegType *obj)
{
    return ((obj->PACRC & AIPS_PACRC_SP5_MASK) >> AIPS_PACRC_SP5_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrCSp5(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRC;

    tmp &= ~AIPS_PACRC_SP5_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRC_SP5_SHIFT)) & AIPS_PACRC_SP5_MASK);
    obj->PACRC = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrCWp5(const AipsRegType *obj)
{
    return ((obj->PACRC & AIPS_PACRC_WP5_MASK) >> AIPS_PACRC_WP5_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrCWp5(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRC;

    tmp &= ~AIPS_PACRC_WP5_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRC_WP5_SHIFT)) & AIPS_PACRC_WP5_MASK);
    obj->PACRC = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrCTp5(const AipsRegType *obj)
{
    return ((obj->PACRC & AIPS_PACRC_TP5_MASK) >> AIPS_PACRC_TP5_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrCTp5(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRC;

    tmp &= ~AIPS_PACRC_TP5_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRC_TP5_SHIFT)) & AIPS_PACRC_TP5_MASK);
    obj->PACRC = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrCSp4(const AipsRegType *obj)
{
    return ((obj->PACRC & AIPS_PACRC_SP4_MASK) >> AIPS_PACRC_SP4_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrCSp4(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRC;

    tmp &= ~AIPS_PACRC_SP4_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRC_SP4_SHIFT)) & AIPS_PACRC_SP4_MASK);
    obj->PACRC = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrCWp4(const AipsRegType *obj)
{
    return ((obj->PACRC & AIPS_PACRC_WP4_MASK) >> AIPS_PACRC_WP4_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrCWp4(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRC;

    tmp &= ~AIPS_PACRC_WP4_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRC_WP4_SHIFT)) & AIPS_PACRC_WP4_MASK);
    obj->PACRC = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrCTp4(const AipsRegType *obj)
{
    return ((obj->PACRC & AIPS_PACRC_TP4_MASK) >> AIPS_PACRC_TP4_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrCTp4(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRC;

    tmp &= ~AIPS_PACRC_TP4_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRC_TP4_SHIFT)) & AIPS_PACRC_TP4_MASK);
    obj->PACRC = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrCSp3(const AipsRegType *obj)
{
    return ((obj->PACRC & AIPS_PACRC_SP3_MASK) >> AIPS_PACRC_SP3_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrCSp3(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRC;

    tmp &= ~AIPS_PACRC_SP3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRC_SP3_SHIFT)) & AIPS_PACRC_SP3_MASK);
    obj->PACRC = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrCWp3(const AipsRegType *obj)
{
    return ((obj->PACRC & AIPS_PACRC_WP3_MASK) >> AIPS_PACRC_WP3_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrCWp3(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRC;

    tmp &= ~AIPS_PACRC_WP3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRC_WP3_SHIFT)) & AIPS_PACRC_WP3_MASK);
    obj->PACRC = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrCTp3(const AipsRegType *obj)
{
    return ((obj->PACRC & AIPS_PACRC_TP3_MASK) >> AIPS_PACRC_TP3_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrCTp3(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRC;

    tmp &= ~AIPS_PACRC_TP3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRC_TP3_SHIFT)) & AIPS_PACRC_TP3_MASK);
    obj->PACRC = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrCSp2(const AipsRegType *obj)
{
    return ((obj->PACRC & AIPS_PACRC_SP2_MASK) >> AIPS_PACRC_SP2_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrCSp2(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRC;

    tmp &= ~AIPS_PACRC_SP2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRC_SP2_SHIFT)) & AIPS_PACRC_SP2_MASK);
    obj->PACRC = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrCWp2(const AipsRegType *obj)
{
    return ((obj->PACRC & AIPS_PACRC_WP2_MASK) >> AIPS_PACRC_WP2_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrCWp2(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRC;

    tmp &= ~AIPS_PACRC_WP2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRC_WP2_SHIFT)) & AIPS_PACRC_WP2_MASK);
    obj->PACRC = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrCTp2(const AipsRegType *obj)
{
    return ((obj->PACRC & AIPS_PACRC_TP2_MASK) >> AIPS_PACRC_TP2_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrCTp2(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRC;

    tmp &= ~AIPS_PACRC_TP2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRC_TP2_SHIFT)) & AIPS_PACRC_TP2_MASK);
    obj->PACRC = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrCSp1(const AipsRegType *obj)
{
    return ((obj->PACRC & AIPS_PACRC_SP1_MASK) >> AIPS_PACRC_SP1_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrCSp1(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRC;

    tmp &= ~AIPS_PACRC_SP1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRC_SP1_SHIFT)) & AIPS_PACRC_SP1_MASK);
    obj->PACRC = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrCWp1(const AipsRegType *obj)
{
    return ((obj->PACRC & AIPS_PACRC_WP1_MASK) >> AIPS_PACRC_WP1_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrCWp1(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRC;

    tmp &= ~AIPS_PACRC_WP1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRC_WP1_SHIFT)) & AIPS_PACRC_WP1_MASK);
    obj->PACRC = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrCTp1(const AipsRegType *obj)
{
    return ((obj->PACRC & AIPS_PACRC_TP1_MASK) >> AIPS_PACRC_TP1_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrCTp1(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRC;

    tmp &= ~AIPS_PACRC_TP1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRC_TP1_SHIFT)) & AIPS_PACRC_TP1_MASK);
    obj->PACRC = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrCSp0(const AipsRegType *obj)
{
    return ((obj->PACRC & AIPS_PACRC_SP0_MASK) >> AIPS_PACRC_SP0_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrCSp0(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRC;

    tmp &= ~AIPS_PACRC_SP0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRC_SP0_SHIFT)) & AIPS_PACRC_SP0_MASK);
    obj->PACRC = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrCWp0(const AipsRegType *obj)
{
    return ((obj->PACRC & AIPS_PACRC_WP0_MASK) >> AIPS_PACRC_WP0_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrCWp0(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRC;

    tmp &= ~AIPS_PACRC_WP0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRC_WP0_SHIFT)) & AIPS_PACRC_WP0_MASK);
    obj->PACRC = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrCTp0(const AipsRegType *obj)
{
    return ((obj->PACRC & AIPS_PACRC_TP0_MASK) >> AIPS_PACRC_TP0_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrCTp0(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRC;

    tmp &= ~AIPS_PACRC_TP0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRC_TP0_SHIFT)) & AIPS_PACRC_TP0_MASK);
    obj->PACRC = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrDSp7(const AipsRegType *obj)
{
    return ((obj->PACRD & AIPS_PACRD_SP7_MASK) >> AIPS_PACRD_SP7_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrDSp7(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRD;

    tmp &= ~AIPS_PACRD_SP7_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRD_SP7_SHIFT)) & AIPS_PACRD_SP7_MASK);
    obj->PACRD = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrDWp7(const AipsRegType *obj)
{
    return ((obj->PACRD & AIPS_PACRD_WP7_MASK) >> AIPS_PACRD_WP7_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrDWp7(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRD;

    tmp &= ~AIPS_PACRD_WP7_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRD_WP7_SHIFT)) & AIPS_PACRD_WP7_MASK);
    obj->PACRD = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrDTp7(const AipsRegType *obj)
{
    return ((obj->PACRD & AIPS_PACRD_TP7_MASK) >> AIPS_PACRD_TP7_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrDTp7(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRD;

    tmp &= ~AIPS_PACRD_TP7_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRD_TP7_SHIFT)) & AIPS_PACRD_TP7_MASK);
    obj->PACRD = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrDSp6(const AipsRegType *obj)
{
    return ((obj->PACRD & AIPS_PACRD_SP6_MASK) >> AIPS_PACRD_SP6_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrDSp6(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRD;

    tmp &= ~AIPS_PACRD_SP6_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRD_SP6_SHIFT)) & AIPS_PACRD_SP6_MASK);
    obj->PACRD = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrDWp6(const AipsRegType *obj)
{
    return ((obj->PACRD & AIPS_PACRD_WP6_MASK) >> AIPS_PACRD_WP6_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrDWp6(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRD;

    tmp &= ~AIPS_PACRD_WP6_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRD_WP6_SHIFT)) & AIPS_PACRD_WP6_MASK);
    obj->PACRD = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrDTp6(const AipsRegType *obj)
{
    return ((obj->PACRD & AIPS_PACRD_TP6_MASK) >> AIPS_PACRD_TP6_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrDTp6(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRD;

    tmp &= ~AIPS_PACRD_TP6_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRD_TP6_SHIFT)) & AIPS_PACRD_TP6_MASK);
    obj->PACRD = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrDSp5(const AipsRegType *obj)
{
    return ((obj->PACRD & AIPS_PACRD_SP5_MASK) >> AIPS_PACRD_SP5_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrDSp5(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRD;

    tmp &= ~AIPS_PACRD_SP5_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRD_SP5_SHIFT)) & AIPS_PACRD_SP5_MASK);
    obj->PACRD = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrDWp5(const AipsRegType *obj)
{
    return ((obj->PACRD & AIPS_PACRD_WP5_MASK) >> AIPS_PACRD_WP5_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrDWp5(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRD;

    tmp &= ~AIPS_PACRD_WP5_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRD_WP5_SHIFT)) & AIPS_PACRD_WP5_MASK);
    obj->PACRD = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrDTp5(const AipsRegType *obj)
{
    return ((obj->PACRD & AIPS_PACRD_TP5_MASK) >> AIPS_PACRD_TP5_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrDTp5(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRD;

    tmp &= ~AIPS_PACRD_TP5_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRD_TP5_SHIFT)) & AIPS_PACRD_TP5_MASK);
    obj->PACRD = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrDSp4(const AipsRegType *obj)
{
    return ((obj->PACRD & AIPS_PACRD_SP4_MASK) >> AIPS_PACRD_SP4_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrDSp4(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRD;

    tmp &= ~AIPS_PACRD_SP4_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRD_SP4_SHIFT)) & AIPS_PACRD_SP4_MASK);
    obj->PACRD = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrDWp4(const AipsRegType *obj)
{
    return ((obj->PACRD & AIPS_PACRD_WP4_MASK) >> AIPS_PACRD_WP4_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrDWp4(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRD;

    tmp &= ~AIPS_PACRD_WP4_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRD_WP4_SHIFT)) & AIPS_PACRD_WP4_MASK);
    obj->PACRD = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrDTp4(const AipsRegType *obj)
{
    return ((obj->PACRD & AIPS_PACRD_TP4_MASK) >> AIPS_PACRD_TP4_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrDTp4(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRD;

    tmp &= ~AIPS_PACRD_TP4_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRD_TP4_SHIFT)) & AIPS_PACRD_TP4_MASK);
    obj->PACRD = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrDSp3(const AipsRegType *obj)
{
    return ((obj->PACRD & AIPS_PACRD_SP3_MASK) >> AIPS_PACRD_SP3_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrDSp3(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRD;

    tmp &= ~AIPS_PACRD_SP3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRD_SP3_SHIFT)) & AIPS_PACRD_SP3_MASK);
    obj->PACRD = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrDWp3(const AipsRegType *obj)
{
    return ((obj->PACRD & AIPS_PACRD_WP3_MASK) >> AIPS_PACRD_WP3_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrDWp3(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRD;

    tmp &= ~AIPS_PACRD_WP3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRD_WP3_SHIFT)) & AIPS_PACRD_WP3_MASK);
    obj->PACRD = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrDTp3(const AipsRegType *obj)
{
    return ((obj->PACRD & AIPS_PACRD_TP3_MASK) >> AIPS_PACRD_TP3_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrDTp3(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRD;

    tmp &= ~AIPS_PACRD_TP3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRD_TP3_SHIFT)) & AIPS_PACRD_TP3_MASK);
    obj->PACRD = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrDSp2(const AipsRegType *obj)
{
    return ((obj->PACRD & AIPS_PACRD_SP2_MASK) >> AIPS_PACRD_SP2_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrDSp2(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRD;

    tmp &= ~AIPS_PACRD_SP2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRD_SP2_SHIFT)) & AIPS_PACRD_SP2_MASK);
    obj->PACRD = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrDWp2(const AipsRegType *obj)
{
    return ((obj->PACRD & AIPS_PACRD_WP2_MASK) >> AIPS_PACRD_WP2_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrDWp2(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRD;

    tmp &= ~AIPS_PACRD_WP2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRD_WP2_SHIFT)) & AIPS_PACRD_WP2_MASK);
    obj->PACRD = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrDTp2(const AipsRegType *obj)
{
    return ((obj->PACRD & AIPS_PACRD_TP2_MASK) >> AIPS_PACRD_TP2_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrDTp2(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRD;

    tmp &= ~AIPS_PACRD_TP2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRD_TP2_SHIFT)) & AIPS_PACRD_TP2_MASK);
    obj->PACRD = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrDSp1(const AipsRegType *obj)
{
    return ((obj->PACRD & AIPS_PACRD_SP1_MASK) >> AIPS_PACRD_SP1_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrDSp1(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRD;

    tmp &= ~AIPS_PACRD_SP1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRD_SP1_SHIFT)) & AIPS_PACRD_SP1_MASK);
    obj->PACRD = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrDWp1(const AipsRegType *obj)
{
    return ((obj->PACRD & AIPS_PACRD_WP1_MASK) >> AIPS_PACRD_WP1_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrDWp1(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRD;

    tmp &= ~AIPS_PACRD_WP1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRD_WP1_SHIFT)) & AIPS_PACRD_WP1_MASK);
    obj->PACRD = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrDTp1(const AipsRegType *obj)
{
    return ((obj->PACRD & AIPS_PACRD_TP1_MASK) >> AIPS_PACRD_TP1_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrDTp1(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRD;

    tmp &= ~AIPS_PACRD_TP1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRD_TP1_SHIFT)) & AIPS_PACRD_TP1_MASK);
    obj->PACRD = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrDSp0(const AipsRegType *obj)
{
    return ((obj->PACRD & AIPS_PACRD_SP0_MASK) >> AIPS_PACRD_SP0_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrDSp0(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRD;

    tmp &= ~AIPS_PACRD_SP0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRD_SP0_SHIFT)) & AIPS_PACRD_SP0_MASK);
    obj->PACRD = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrDWp0(const AipsRegType *obj)
{
    return ((obj->PACRD & AIPS_PACRD_WP0_MASK) >> AIPS_PACRD_WP0_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrDWp0(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRD;

    tmp &= ~AIPS_PACRD_WP0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRD_WP0_SHIFT)) & AIPS_PACRD_WP0_MASK);
    obj->PACRD = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrDTp0(const AipsRegType *obj)
{
    return ((obj->PACRD & AIPS_PACRD_TP0_MASK) >> AIPS_PACRD_TP0_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrDTp0(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRD;

    tmp &= ~AIPS_PACRD_TP0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRD_TP0_SHIFT)) & AIPS_PACRD_TP0_MASK);
    obj->PACRD = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrESp7(const AipsRegType *obj)
{
    return ((obj->PACRE & AIPS_PACRE_SP7_MASK) >> AIPS_PACRE_SP7_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrESp7(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRE;

    tmp &= ~AIPS_PACRE_SP7_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRE_SP7_SHIFT)) & AIPS_PACRE_SP7_MASK);
    obj->PACRE = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrEWp7(const AipsRegType *obj)
{
    return ((obj->PACRE & AIPS_PACRE_WP7_MASK) >> AIPS_PACRE_WP7_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrEWp7(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRE;

    tmp &= ~AIPS_PACRE_WP7_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRE_WP7_SHIFT)) & AIPS_PACRE_WP7_MASK);
    obj->PACRE = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrETp7(const AipsRegType *obj)
{
    return ((obj->PACRE & AIPS_PACRE_TP7_MASK) >> AIPS_PACRE_TP7_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrETp7(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRE;

    tmp &= ~AIPS_PACRE_TP7_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRE_TP7_SHIFT)) & AIPS_PACRE_TP7_MASK);
    obj->PACRE = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrESp6(const AipsRegType *obj)
{
    return ((obj->PACRE & AIPS_PACRE_SP6_MASK) >> AIPS_PACRE_SP6_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrESp6(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRE;

    tmp &= ~AIPS_PACRE_SP6_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRE_SP6_SHIFT)) & AIPS_PACRE_SP6_MASK);
    obj->PACRE = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrEWp6(const AipsRegType *obj)
{
    return ((obj->PACRE & AIPS_PACRE_WP6_MASK) >> AIPS_PACRE_WP6_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrEWp6(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRE;

    tmp &= ~AIPS_PACRE_WP6_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRE_WP6_SHIFT)) & AIPS_PACRE_WP6_MASK);
    obj->PACRE = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrETp6(const AipsRegType *obj)
{
    return ((obj->PACRE & AIPS_PACRE_TP6_MASK) >> AIPS_PACRE_TP6_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrETp6(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRE;

    tmp &= ~AIPS_PACRE_TP6_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRE_TP6_SHIFT)) & AIPS_PACRE_TP6_MASK);
    obj->PACRE = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrESp5(const AipsRegType *obj)
{
    return ((obj->PACRE & AIPS_PACRE_SP5_MASK) >> AIPS_PACRE_SP5_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrESp5(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRE;

    tmp &= ~AIPS_PACRE_SP5_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRE_SP5_SHIFT)) & AIPS_PACRE_SP5_MASK);
    obj->PACRE = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrEWp5(const AipsRegType *obj)
{
    return ((obj->PACRE & AIPS_PACRE_WP5_MASK) >> AIPS_PACRE_WP5_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrEWp5(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRE;

    tmp &= ~AIPS_PACRE_WP5_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRE_WP5_SHIFT)) & AIPS_PACRE_WP5_MASK);
    obj->PACRE = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrETp5(const AipsRegType *obj)
{
    return ((obj->PACRE & AIPS_PACRE_TP5_MASK) >> AIPS_PACRE_TP5_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrETp5(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRE;

    tmp &= ~AIPS_PACRE_TP5_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRE_TP5_SHIFT)) & AIPS_PACRE_TP5_MASK);
    obj->PACRE = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrESp4(const AipsRegType *obj)
{
    return ((obj->PACRE & AIPS_PACRE_SP4_MASK) >> AIPS_PACRE_SP4_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrESp4(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRE;

    tmp &= ~AIPS_PACRE_SP4_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRE_SP4_SHIFT)) & AIPS_PACRE_SP4_MASK);
    obj->PACRE = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrEWp4(const AipsRegType *obj)
{
    return ((obj->PACRE & AIPS_PACRE_WP4_MASK) >> AIPS_PACRE_WP4_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrEWp4(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRE;

    tmp &= ~AIPS_PACRE_WP4_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRE_WP4_SHIFT)) & AIPS_PACRE_WP4_MASK);
    obj->PACRE = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrETp4(const AipsRegType *obj)
{
    return ((obj->PACRE & AIPS_PACRE_TP4_MASK) >> AIPS_PACRE_TP4_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrETp4(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRE;

    tmp &= ~AIPS_PACRE_TP4_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRE_TP4_SHIFT)) & AIPS_PACRE_TP4_MASK);
    obj->PACRE = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrESp3(const AipsRegType *obj)
{
    return ((obj->PACRE & AIPS_PACRE_SP3_MASK) >> AIPS_PACRE_SP3_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrESp3(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRE;

    tmp &= ~AIPS_PACRE_SP3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRE_SP3_SHIFT)) & AIPS_PACRE_SP3_MASK);
    obj->PACRE = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrEWp3(const AipsRegType *obj)
{
    return ((obj->PACRE & AIPS_PACRE_WP3_MASK) >> AIPS_PACRE_WP3_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrEWp3(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRE;

    tmp &= ~AIPS_PACRE_WP3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRE_WP3_SHIFT)) & AIPS_PACRE_WP3_MASK);
    obj->PACRE = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrETp3(const AipsRegType *obj)
{
    return ((obj->PACRE & AIPS_PACRE_TP3_MASK) >> AIPS_PACRE_TP3_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrETp3(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRE;

    tmp &= ~AIPS_PACRE_TP3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRE_TP3_SHIFT)) & AIPS_PACRE_TP3_MASK);
    obj->PACRE = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrESp2(const AipsRegType *obj)
{
    return ((obj->PACRE & AIPS_PACRE_SP2_MASK) >> AIPS_PACRE_SP2_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrESp2(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRE;

    tmp &= ~AIPS_PACRE_SP2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRE_SP2_SHIFT)) & AIPS_PACRE_SP2_MASK);
    obj->PACRE = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrEWp2(const AipsRegType *obj)
{
    return ((obj->PACRE & AIPS_PACRE_WP2_MASK) >> AIPS_PACRE_WP2_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrEWp2(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRE;

    tmp &= ~AIPS_PACRE_WP2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRE_WP2_SHIFT)) & AIPS_PACRE_WP2_MASK);
    obj->PACRE = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrETp2(const AipsRegType *obj)
{
    return ((obj->PACRE & AIPS_PACRE_TP2_MASK) >> AIPS_PACRE_TP2_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrETp2(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRE;

    tmp &= ~AIPS_PACRE_TP2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRE_TP2_SHIFT)) & AIPS_PACRE_TP2_MASK);
    obj->PACRE = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrESp1(const AipsRegType *obj)
{
    return ((obj->PACRE & AIPS_PACRE_SP1_MASK) >> AIPS_PACRE_SP1_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrESp1(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRE;

    tmp &= ~AIPS_PACRE_SP1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRE_SP1_SHIFT)) & AIPS_PACRE_SP1_MASK);
    obj->PACRE = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrEWp1(const AipsRegType *obj)
{
    return ((obj->PACRE & AIPS_PACRE_WP1_MASK) >> AIPS_PACRE_WP1_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrEWp1(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRE;

    tmp &= ~AIPS_PACRE_WP1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRE_WP1_SHIFT)) & AIPS_PACRE_WP1_MASK);
    obj->PACRE = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrETp1(const AipsRegType *obj)
{
    return ((obj->PACRE & AIPS_PACRE_TP1_MASK) >> AIPS_PACRE_TP1_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrETp1(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRE;

    tmp &= ~AIPS_PACRE_TP1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRE_TP1_SHIFT)) & AIPS_PACRE_TP1_MASK);
    obj->PACRE = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrESp0(const AipsRegType *obj)
{
    return ((obj->PACRE & AIPS_PACRE_SP0_MASK) >> AIPS_PACRE_SP0_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrESp0(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRE;

    tmp &= ~AIPS_PACRE_SP0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRE_SP0_SHIFT)) & AIPS_PACRE_SP0_MASK);
    obj->PACRE = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrEWp0(const AipsRegType *obj)
{
    return ((obj->PACRE & AIPS_PACRE_WP0_MASK) >> AIPS_PACRE_WP0_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrEWp0(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRE;

    tmp &= ~AIPS_PACRE_WP0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRE_WP0_SHIFT)) & AIPS_PACRE_WP0_MASK);
    obj->PACRE = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrETp0(const AipsRegType *obj)
{
    return ((obj->PACRE & AIPS_PACRE_TP0_MASK) >> AIPS_PACRE_TP0_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrETp0(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRE;

    tmp &= ~AIPS_PACRE_TP0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRE_TP0_SHIFT)) & AIPS_PACRE_TP0_MASK);
    obj->PACRE = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrFSp7(const AipsRegType *obj)
{
    return ((obj->PACRF & AIPS_PACRF_SP7_MASK) >> AIPS_PACRF_SP7_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrFSp7(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRF;

    tmp &= ~AIPS_PACRF_SP7_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRF_SP7_SHIFT)) & AIPS_PACRF_SP7_MASK);
    obj->PACRF = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrFWp7(const AipsRegType *obj)
{
    return ((obj->PACRF & AIPS_PACRF_WP7_MASK) >> AIPS_PACRF_WP7_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrFWp7(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRF;

    tmp &= ~AIPS_PACRF_WP7_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRF_WP7_SHIFT)) & AIPS_PACRF_WP7_MASK);
    obj->PACRF = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrFTp7(const AipsRegType *obj)
{
    return ((obj->PACRF & AIPS_PACRF_TP7_MASK) >> AIPS_PACRF_TP7_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrFTp7(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRF;

    tmp &= ~AIPS_PACRF_TP7_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRF_TP7_SHIFT)) & AIPS_PACRF_TP7_MASK);
    obj->PACRF = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrFSp6(const AipsRegType *obj)
{
    return ((obj->PACRF & AIPS_PACRF_SP6_MASK) >> AIPS_PACRF_SP6_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrFSp6(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRF;

    tmp &= ~AIPS_PACRF_SP6_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRF_SP6_SHIFT)) & AIPS_PACRF_SP6_MASK);
    obj->PACRF = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrFWp6(const AipsRegType *obj)
{
    return ((obj->PACRF & AIPS_PACRF_WP6_MASK) >> AIPS_PACRF_WP6_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrFWp6(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRF;

    tmp &= ~AIPS_PACRF_WP6_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRF_WP6_SHIFT)) & AIPS_PACRF_WP6_MASK);
    obj->PACRF = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrFTp6(const AipsRegType *obj)
{
    return ((obj->PACRF & AIPS_PACRF_TP6_MASK) >> AIPS_PACRF_TP6_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrFTp6(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRF;

    tmp &= ~AIPS_PACRF_TP6_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRF_TP6_SHIFT)) & AIPS_PACRF_TP6_MASK);
    obj->PACRF = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrFSp5(const AipsRegType *obj)
{
    return ((obj->PACRF & AIPS_PACRF_SP5_MASK) >> AIPS_PACRF_SP5_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrFSp5(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRF;

    tmp &= ~AIPS_PACRF_SP5_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRF_SP5_SHIFT)) & AIPS_PACRF_SP5_MASK);
    obj->PACRF = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrFWp5(const AipsRegType *obj)
{
    return ((obj->PACRF & AIPS_PACRF_WP5_MASK) >> AIPS_PACRF_WP5_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrFWp5(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRF;

    tmp &= ~AIPS_PACRF_WP5_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRF_WP5_SHIFT)) & AIPS_PACRF_WP5_MASK);
    obj->PACRF = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrFTp5(const AipsRegType *obj)
{
    return ((obj->PACRF & AIPS_PACRF_TP5_MASK) >> AIPS_PACRF_TP5_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrFTp5(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRF;

    tmp &= ~AIPS_PACRF_TP5_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRF_TP5_SHIFT)) & AIPS_PACRF_TP5_MASK);
    obj->PACRF = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrFSp4(const AipsRegType *obj)
{
    return ((obj->PACRF & AIPS_PACRF_SP4_MASK) >> AIPS_PACRF_SP4_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrFSp4(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRF;

    tmp &= ~AIPS_PACRF_SP4_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRF_SP4_SHIFT)) & AIPS_PACRF_SP4_MASK);
    obj->PACRF = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrFWp4(const AipsRegType *obj)
{
    return ((obj->PACRF & AIPS_PACRF_WP4_MASK) >> AIPS_PACRF_WP4_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrFWp4(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRF;

    tmp &= ~AIPS_PACRF_WP4_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRF_WP4_SHIFT)) & AIPS_PACRF_WP4_MASK);
    obj->PACRF = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrFTp4(const AipsRegType *obj)
{
    return ((obj->PACRF & AIPS_PACRF_TP4_MASK) >> AIPS_PACRF_TP4_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrFTp4(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRF;

    tmp &= ~AIPS_PACRF_TP4_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRF_TP4_SHIFT)) & AIPS_PACRF_TP4_MASK);
    obj->PACRF = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrFSp3(const AipsRegType *obj)
{
    return ((obj->PACRF & AIPS_PACRF_SP3_MASK) >> AIPS_PACRF_SP3_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrFSp3(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRF;

    tmp &= ~AIPS_PACRF_SP3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRF_SP3_SHIFT)) & AIPS_PACRF_SP3_MASK);
    obj->PACRF = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrFWp3(const AipsRegType *obj)
{
    return ((obj->PACRF & AIPS_PACRF_WP3_MASK) >> AIPS_PACRF_WP3_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrFWp3(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRF;

    tmp &= ~AIPS_PACRF_WP3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRF_WP3_SHIFT)) & AIPS_PACRF_WP3_MASK);
    obj->PACRF = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrFTp3(const AipsRegType *obj)
{
    return ((obj->PACRF & AIPS_PACRF_TP3_MASK) >> AIPS_PACRF_TP3_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrFTp3(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRF;

    tmp &= ~AIPS_PACRF_TP3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRF_TP3_SHIFT)) & AIPS_PACRF_TP3_MASK);
    obj->PACRF = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrFSp2(const AipsRegType *obj)
{
    return ((obj->PACRF & AIPS_PACRF_SP2_MASK) >> AIPS_PACRF_SP2_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrFSp2(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRF;

    tmp &= ~AIPS_PACRF_SP2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRF_SP2_SHIFT)) & AIPS_PACRF_SP2_MASK);
    obj->PACRF = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrFWp2(const AipsRegType *obj)
{
    return ((obj->PACRF & AIPS_PACRF_WP2_MASK) >> AIPS_PACRF_WP2_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrFWp2(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRF;

    tmp &= ~AIPS_PACRF_WP2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRF_WP2_SHIFT)) & AIPS_PACRF_WP2_MASK);
    obj->PACRF = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrFTp2(const AipsRegType *obj)
{
    return ((obj->PACRF & AIPS_PACRF_TP2_MASK) >> AIPS_PACRF_TP2_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrFTp2(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRF;

    tmp &= ~AIPS_PACRF_TP2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRF_TP2_SHIFT)) & AIPS_PACRF_TP2_MASK);
    obj->PACRF = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrFSp1(const AipsRegType *obj)
{
    return ((obj->PACRF & AIPS_PACRF_SP1_MASK) >> AIPS_PACRF_SP1_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrFSp1(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRF;

    tmp &= ~AIPS_PACRF_SP1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRF_SP1_SHIFT)) & AIPS_PACRF_SP1_MASK);
    obj->PACRF = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrFWp1(const AipsRegType *obj)
{
    return ((obj->PACRF & AIPS_PACRF_WP1_MASK) >> AIPS_PACRF_WP1_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrFWp1(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRF;

    tmp &= ~AIPS_PACRF_WP1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRF_WP1_SHIFT)) & AIPS_PACRF_WP1_MASK);
    obj->PACRF = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrFTp1(const AipsRegType *obj)
{
    return ((obj->PACRF & AIPS_PACRF_TP1_MASK) >> AIPS_PACRF_TP1_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrFTp1(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRF;

    tmp &= ~AIPS_PACRF_TP1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRF_TP1_SHIFT)) & AIPS_PACRF_TP1_MASK);
    obj->PACRF = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrFSp0(const AipsRegType *obj)
{
    return ((obj->PACRF & AIPS_PACRF_SP0_MASK) >> AIPS_PACRF_SP0_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrFSp0(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRF;

    tmp &= ~AIPS_PACRF_SP0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRF_SP0_SHIFT)) & AIPS_PACRF_SP0_MASK);
    obj->PACRF = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrFWp0(const AipsRegType *obj)
{
    return ((obj->PACRF & AIPS_PACRF_WP0_MASK) >> AIPS_PACRF_WP0_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrFWp0(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRF;

    tmp &= ~AIPS_PACRF_WP0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRF_WP0_SHIFT)) & AIPS_PACRF_WP0_MASK);
    obj->PACRF = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrFTp0(const AipsRegType *obj)
{
    return ((obj->PACRF & AIPS_PACRF_TP0_MASK) >> AIPS_PACRF_TP0_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrFTp0(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRF;

    tmp &= ~AIPS_PACRF_TP0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRF_TP0_SHIFT)) & AIPS_PACRF_TP0_MASK);
    obj->PACRF = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrGSp7(const AipsRegType *obj)
{
    return ((obj->PACRG & AIPS_PACRG_SP7_MASK) >> AIPS_PACRG_SP7_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrGSp7(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRG;

    tmp &= ~AIPS_PACRG_SP7_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRG_SP7_SHIFT)) & AIPS_PACRG_SP7_MASK);
    obj->PACRG = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrGWp7(const AipsRegType *obj)
{
    return ((obj->PACRG & AIPS_PACRG_WP7_MASK) >> AIPS_PACRG_WP7_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrGWp7(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRG;

    tmp &= ~AIPS_PACRG_WP7_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRG_WP7_SHIFT)) & AIPS_PACRG_WP7_MASK);
    obj->PACRG = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrGTp7(const AipsRegType *obj)
{
    return ((obj->PACRG & AIPS_PACRG_TP7_MASK) >> AIPS_PACRG_TP7_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrGTp7(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRG;

    tmp &= ~AIPS_PACRG_TP7_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRG_TP7_SHIFT)) & AIPS_PACRG_TP7_MASK);
    obj->PACRG = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrGSp6(const AipsRegType *obj)
{
    return ((obj->PACRG & AIPS_PACRG_SP6_MASK) >> AIPS_PACRG_SP6_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrGSp6(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRG;

    tmp &= ~AIPS_PACRG_SP6_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRG_SP6_SHIFT)) & AIPS_PACRG_SP6_MASK);
    obj->PACRG = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrGWp6(const AipsRegType *obj)
{
    return ((obj->PACRG & AIPS_PACRG_WP6_MASK) >> AIPS_PACRG_WP6_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrGWp6(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRG;

    tmp &= ~AIPS_PACRG_WP6_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRG_WP6_SHIFT)) & AIPS_PACRG_WP6_MASK);
    obj->PACRG = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrGTp6(const AipsRegType *obj)
{
    return ((obj->PACRG & AIPS_PACRG_TP6_MASK) >> AIPS_PACRG_TP6_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrGTp6(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRG;

    tmp &= ~AIPS_PACRG_TP6_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRG_TP6_SHIFT)) & AIPS_PACRG_TP6_MASK);
    obj->PACRG = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrGSp5(const AipsRegType *obj)
{
    return ((obj->PACRG & AIPS_PACRG_SP5_MASK) >> AIPS_PACRG_SP5_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrGSp5(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRG;

    tmp &= ~AIPS_PACRG_SP5_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRG_SP5_SHIFT)) & AIPS_PACRG_SP5_MASK);
    obj->PACRG = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrGWp5(const AipsRegType *obj)
{
    return ((obj->PACRG & AIPS_PACRG_WP5_MASK) >> AIPS_PACRG_WP5_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrGWp5(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRG;

    tmp &= ~AIPS_PACRG_WP5_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRG_WP5_SHIFT)) & AIPS_PACRG_WP5_MASK);
    obj->PACRG = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrGTp5(const AipsRegType *obj)
{
    return ((obj->PACRG & AIPS_PACRG_TP5_MASK) >> AIPS_PACRG_TP5_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrGTp5(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRG;

    tmp &= ~AIPS_PACRG_TP5_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRG_TP5_SHIFT)) & AIPS_PACRG_TP5_MASK);
    obj->PACRG = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrGSp4(const AipsRegType *obj)
{
    return ((obj->PACRG & AIPS_PACRG_SP4_MASK) >> AIPS_PACRG_SP4_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrGSp4(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRG;

    tmp &= ~AIPS_PACRG_SP4_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRG_SP4_SHIFT)) & AIPS_PACRG_SP4_MASK);
    obj->PACRG = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrGWp4(const AipsRegType *obj)
{
    return ((obj->PACRG & AIPS_PACRG_WP4_MASK) >> AIPS_PACRG_WP4_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrGWp4(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRG;

    tmp &= ~AIPS_PACRG_WP4_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRG_WP4_SHIFT)) & AIPS_PACRG_WP4_MASK);
    obj->PACRG = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrGTp4(const AipsRegType *obj)
{
    return ((obj->PACRG & AIPS_PACRG_TP4_MASK) >> AIPS_PACRG_TP4_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrGTp4(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRG;

    tmp &= ~AIPS_PACRG_TP4_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRG_TP4_SHIFT)) & AIPS_PACRG_TP4_MASK);
    obj->PACRG = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrGSp3(const AipsRegType *obj)
{
    return ((obj->PACRG & AIPS_PACRG_SP3_MASK) >> AIPS_PACRG_SP3_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrGSp3(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRG;

    tmp &= ~AIPS_PACRG_SP3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRG_SP3_SHIFT)) & AIPS_PACRG_SP3_MASK);
    obj->PACRG = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrGWp3(const AipsRegType *obj)
{
    return ((obj->PACRG & AIPS_PACRG_WP3_MASK) >> AIPS_PACRG_WP3_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrGWp3(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRG;

    tmp &= ~AIPS_PACRG_WP3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRG_WP3_SHIFT)) & AIPS_PACRG_WP3_MASK);
    obj->PACRG = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrGTp3(const AipsRegType *obj)
{
    return ((obj->PACRG & AIPS_PACRG_TP3_MASK) >> AIPS_PACRG_TP3_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrGTp3(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRG;

    tmp &= ~AIPS_PACRG_TP3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRG_TP3_SHIFT)) & AIPS_PACRG_TP3_MASK);
    obj->PACRG = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrGSp2(const AipsRegType *obj)
{
    return ((obj->PACRG & AIPS_PACRG_SP2_MASK) >> AIPS_PACRG_SP2_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrGSp2(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRG;

    tmp &= ~AIPS_PACRG_SP2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRG_SP2_SHIFT)) & AIPS_PACRG_SP2_MASK);
    obj->PACRG = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrGWp2(const AipsRegType *obj)
{
    return ((obj->PACRG & AIPS_PACRG_WP2_MASK) >> AIPS_PACRG_WP2_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrGWp2(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRG;

    tmp &= ~AIPS_PACRG_WP2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRG_WP2_SHIFT)) & AIPS_PACRG_WP2_MASK);
    obj->PACRG = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrGTp2(const AipsRegType *obj)
{
    return ((obj->PACRG & AIPS_PACRG_TP2_MASK) >> AIPS_PACRG_TP2_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrGTp2(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRG;

    tmp &= ~AIPS_PACRG_TP2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRG_TP2_SHIFT)) & AIPS_PACRG_TP2_MASK);
    obj->PACRG = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrGSp1(const AipsRegType *obj)
{
    return ((obj->PACRG & AIPS_PACRG_SP1_MASK) >> AIPS_PACRG_SP1_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrGSp1(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRG;

    tmp &= ~AIPS_PACRG_SP1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRG_SP1_SHIFT)) & AIPS_PACRG_SP1_MASK);
    obj->PACRG = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrGWp1(const AipsRegType *obj)
{
    return ((obj->PACRG & AIPS_PACRG_WP1_MASK) >> AIPS_PACRG_WP1_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrGWp1(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRG;

    tmp &= ~AIPS_PACRG_WP1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRG_WP1_SHIFT)) & AIPS_PACRG_WP1_MASK);
    obj->PACRG = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrGTp1(const AipsRegType *obj)
{
    return ((obj->PACRG & AIPS_PACRG_TP1_MASK) >> AIPS_PACRG_TP1_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrGTp1(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRG;

    tmp &= ~AIPS_PACRG_TP1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRG_TP1_SHIFT)) & AIPS_PACRG_TP1_MASK);
    obj->PACRG = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrGSp0(const AipsRegType *obj)
{
    return ((obj->PACRG & AIPS_PACRG_SP0_MASK) >> AIPS_PACRG_SP0_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrGSp0(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRG;

    tmp &= ~AIPS_PACRG_SP0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRG_SP0_SHIFT)) & AIPS_PACRG_SP0_MASK);
    obj->PACRG = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrGWp0(const AipsRegType *obj)
{
    return ((obj->PACRG & AIPS_PACRG_WP0_MASK) >> AIPS_PACRG_WP0_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrGWp0(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRG;

    tmp &= ~AIPS_PACRG_WP0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRG_WP0_SHIFT)) & AIPS_PACRG_WP0_MASK);
    obj->PACRG = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrGTp0(const AipsRegType *obj)
{
    return ((obj->PACRG & AIPS_PACRG_TP0_MASK) >> AIPS_PACRG_TP0_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrGTp0(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRG;

    tmp &= ~AIPS_PACRG_TP0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRG_TP0_SHIFT)) & AIPS_PACRG_TP0_MASK);
    obj->PACRG = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrHSp7(const AipsRegType *obj)
{
    return ((obj->PACRH & AIPS_PACRH_SP7_MASK) >> AIPS_PACRH_SP7_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrHSp7(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRH;

    tmp &= ~AIPS_PACRH_SP7_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRH_SP7_SHIFT)) & AIPS_PACRH_SP7_MASK);
    obj->PACRH = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrHWp7(const AipsRegType *obj)
{
    return ((obj->PACRH & AIPS_PACRH_WP7_MASK) >> AIPS_PACRH_WP7_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrHWp7(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRH;

    tmp &= ~AIPS_PACRH_WP7_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRH_WP7_SHIFT)) & AIPS_PACRH_WP7_MASK);
    obj->PACRH = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrHTp7(const AipsRegType *obj)
{
    return ((obj->PACRH & AIPS_PACRH_TP7_MASK) >> AIPS_PACRH_TP7_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrHTp7(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRH;

    tmp &= ~AIPS_PACRH_TP7_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRH_TP7_SHIFT)) & AIPS_PACRH_TP7_MASK);
    obj->PACRH = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrHSp6(const AipsRegType *obj)
{
    return ((obj->PACRH & AIPS_PACRH_SP6_MASK) >> AIPS_PACRH_SP6_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrHSp6(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRH;

    tmp &= ~AIPS_PACRH_SP6_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRH_SP6_SHIFT)) & AIPS_PACRH_SP6_MASK);
    obj->PACRH = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrHWp6(const AipsRegType *obj)
{
    return ((obj->PACRH & AIPS_PACRH_WP6_MASK) >> AIPS_PACRH_WP6_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrHWp6(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRH;

    tmp &= ~AIPS_PACRH_WP6_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRH_WP6_SHIFT)) & AIPS_PACRH_WP6_MASK);
    obj->PACRH = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrHTp6(const AipsRegType *obj)
{
    return ((obj->PACRH & AIPS_PACRH_TP6_MASK) >> AIPS_PACRH_TP6_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrHTp6(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRH;

    tmp &= ~AIPS_PACRH_TP6_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRH_TP6_SHIFT)) & AIPS_PACRH_TP6_MASK);
    obj->PACRH = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrHSp5(const AipsRegType *obj)
{
    return ((obj->PACRH & AIPS_PACRH_SP5_MASK) >> AIPS_PACRH_SP5_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrHSp5(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRH;

    tmp &= ~AIPS_PACRH_SP5_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRH_SP5_SHIFT)) & AIPS_PACRH_SP5_MASK);
    obj->PACRH = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrHWp5(const AipsRegType *obj)
{
    return ((obj->PACRH & AIPS_PACRH_WP5_MASK) >> AIPS_PACRH_WP5_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrHWp5(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRH;

    tmp &= ~AIPS_PACRH_WP5_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRH_WP5_SHIFT)) & AIPS_PACRH_WP5_MASK);
    obj->PACRH = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrHTp5(const AipsRegType *obj)
{
    return ((obj->PACRH & AIPS_PACRH_TP5_MASK) >> AIPS_PACRH_TP5_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrHTp5(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRH;

    tmp &= ~AIPS_PACRH_TP5_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRH_TP5_SHIFT)) & AIPS_PACRH_TP5_MASK);
    obj->PACRH = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrHSp4(const AipsRegType *obj)
{
    return ((obj->PACRH & AIPS_PACRH_SP4_MASK) >> AIPS_PACRH_SP4_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrHSp4(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRH;

    tmp &= ~AIPS_PACRH_SP4_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRH_SP4_SHIFT)) & AIPS_PACRH_SP4_MASK);
    obj->PACRH = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrHWp4(const AipsRegType *obj)
{
    return ((obj->PACRH & AIPS_PACRH_WP4_MASK) >> AIPS_PACRH_WP4_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrHWp4(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRH;

    tmp &= ~AIPS_PACRH_WP4_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRH_WP4_SHIFT)) & AIPS_PACRH_WP4_MASK);
    obj->PACRH = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrHTp4(const AipsRegType *obj)
{
    return ((obj->PACRH & AIPS_PACRH_TP4_MASK) >> AIPS_PACRH_TP4_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrHTp4(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRH;

    tmp &= ~AIPS_PACRH_TP4_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRH_TP4_SHIFT)) & AIPS_PACRH_TP4_MASK);
    obj->PACRH = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrHSp3(const AipsRegType *obj)
{
    return ((obj->PACRH & AIPS_PACRH_SP3_MASK) >> AIPS_PACRH_SP3_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrHSp3(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRH;

    tmp &= ~AIPS_PACRH_SP3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRH_SP3_SHIFT)) & AIPS_PACRH_SP3_MASK);
    obj->PACRH = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrHWp3(const AipsRegType *obj)
{
    return ((obj->PACRH & AIPS_PACRH_WP3_MASK) >> AIPS_PACRH_WP3_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrHWp3(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRH;

    tmp &= ~AIPS_PACRH_WP3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRH_WP3_SHIFT)) & AIPS_PACRH_WP3_MASK);
    obj->PACRH = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrHTp3(const AipsRegType *obj)
{
    return ((obj->PACRH & AIPS_PACRH_TP3_MASK) >> AIPS_PACRH_TP3_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrHTp3(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRH;

    tmp &= ~AIPS_PACRH_TP3_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRH_TP3_SHIFT)) & AIPS_PACRH_TP3_MASK);
    obj->PACRH = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrHSp2(const AipsRegType *obj)
{
    return ((obj->PACRH & AIPS_PACRH_SP2_MASK) >> AIPS_PACRH_SP2_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrHSp2(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRH;

    tmp &= ~AIPS_PACRH_SP2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRH_SP2_SHIFT)) & AIPS_PACRH_SP2_MASK);
    obj->PACRH = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrHWp2(const AipsRegType *obj)
{
    return ((obj->PACRH & AIPS_PACRH_WP2_MASK) >> AIPS_PACRH_WP2_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrHWp2(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRH;

    tmp &= ~AIPS_PACRH_WP2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRH_WP2_SHIFT)) & AIPS_PACRH_WP2_MASK);
    obj->PACRH = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrHTp2(const AipsRegType *obj)
{
    return ((obj->PACRH & AIPS_PACRH_TP2_MASK) >> AIPS_PACRH_TP2_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrHTp2(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRH;

    tmp &= ~AIPS_PACRH_TP2_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRH_TP2_SHIFT)) & AIPS_PACRH_TP2_MASK);
    obj->PACRH = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrHSp1(const AipsRegType *obj)
{
    return ((obj->PACRH & AIPS_PACRH_SP1_MASK) >> AIPS_PACRH_SP1_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrHSp1(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRH;

    tmp &= ~AIPS_PACRH_SP1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRH_SP1_SHIFT)) & AIPS_PACRH_SP1_MASK);
    obj->PACRH = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrHWp1(const AipsRegType *obj)
{
    return ((obj->PACRH & AIPS_PACRH_WP1_MASK) >> AIPS_PACRH_WP1_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrHWp1(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRH;

    tmp &= ~AIPS_PACRH_WP1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRH_WP1_SHIFT)) & AIPS_PACRH_WP1_MASK);
    obj->PACRH = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrHTp1(const AipsRegType *obj)
{
    return ((obj->PACRH & AIPS_PACRH_TP1_MASK) >> AIPS_PACRH_TP1_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrHTp1(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRH;

    tmp &= ~AIPS_PACRH_TP1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRH_TP1_SHIFT)) & AIPS_PACRH_TP1_MASK);
    obj->PACRH = tmp;
}

/*! \brief Gets the Supervisor Protect
 *
 * This function gets the current Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Supervisor Protect
 *         - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *         - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrHSp0(const AipsRegType *obj)
{
    return ((obj->PACRH & AIPS_PACRH_SP0_MASK) >> AIPS_PACRH_SP0_SHIFT);
}

/*! \brief Sets the Supervisor Protect
 *
 * This function sets the Supervisor Protect.
 * Determines whether the peripheral requires supervisor Privilege Level for accesses.
 * When this field is set, the Master Privilege Level# must indicate the supervisor access attribute,
 * and the MPRx[MPLn] control field for the Master must be set.
 * If not, access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Supervisor Protect
 *                    - 0b : This peripheral does not require supervisor Privilege Level for accesses.
 *                    - 1b : This peripheral requires supervisor Privilege Level for accesses.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrHSp0(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRH;

    tmp &= ~AIPS_PACRH_SP0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRH_SP0_SHIFT)) & AIPS_PACRH_SP0_MASK);
    obj->PACRH = tmp;
}

/*! \brief Gets the Write Protect
 *
 * This function gets the current Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Write Protect
 *         - 0b : This peripheral allows write accesses.
 *         - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrHWp0(const AipsRegType *obj)
{
    return ((obj->PACRH & AIPS_PACRH_WP0_MASK) >> AIPS_PACRH_WP0_SHIFT);
}

/*! \brief Sets the Write Protect
 *
 * This function sets the Write Protect.
 * Determines whether the peripheral allows write accesses.
 * When this field is set and a write access is attempted,
 * access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Write Protect
 *                    - 0b : This peripheral allows write accesses.
 *                    - 1b : This peripheral is write protected.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrHWp0(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRH;

    tmp &= ~AIPS_PACRH_WP0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRH_WP0_SHIFT)) & AIPS_PACRH_WP0_MASK);
    obj->PACRH = tmp;
}

/*! \brief Gets the Trusted Protect
 *
 * This function gets the current Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \return Trusted Protect
 *         - 0b : Accesses from an untrusted Master are allowed.
 *         - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline uint8_t AipsReg_GetPacrHTp0(const AipsRegType *obj)
{
    return ((obj->PACRH & AIPS_PACRH_TP0_MASK) >> AIPS_PACRH_TP0_SHIFT);
}

/*! \brief Sets the Trusted Protect
 *
 * This function sets the Trusted Protect.
 * Determines whether the peripheral allows accesses from an untrusted Master.
 * When this field is set and an access is attempted by an untrusted Master,
 * the access terminates with an error response and no peripheral access initiates.
 *
 * \param[in] obj : pointer to AIPS register instance
 * \param[in] value : the value of Trusted Protect
 *                    - 0b : Accesses from an untrusted Master are allowed.
 *                    - 1b : Accesses from an untrusted Master are not allowed.
 */
__attribute__((always_inline)) static inline void AipsReg_SetPacrHTp0(AipsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->PACRH;

    tmp &= ~AIPS_PACRH_TP0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AIPS_PACRH_TP0_SHIFT)) & AIPS_PACRH_TP0_MASK);
    obj->PACRH = tmp;
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _AIPS_REG_H_ */
