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

#ifndef _I2C_REG_H_
#define _I2C_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the driver of I2C module
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

/* CTRL Bit fields */
#define I2C_CTRL_MST_MODE_MASK                          (0x00000001ul)
#define I2C_CTRL_MST_MODE_SHIFT                         (0u)

#define I2C_CTRL_SPEED_MASK                             (0x00000006ul)
#define I2C_CTRL_SPEED_SHIFT                            (1u)

#define I2C_CTRL_SLV_ADDR_MODE_MASK                     (0x00000008ul)
#define I2C_CTRL_SLV_ADDR_MODE_SHIFT                    (3u)

#define I2C_CTRL_MST_ADDR_MODE_MASK                     (0x00000010ul)
#define I2C_CTRL_MST_ADDR_MODE_SHIFT                    (4u)

#define I2C_CTRL_RESTART_EN_MASK                        (0x00000020ul)
#define I2C_CTRL_RESTART_EN_SHIFT                       (5u)

#define I2C_CTRL_SLAVE_DISABLE_MASK                     (0x00000040ul)
#define I2C_CTRL_SLAVE_DISABLE_SHIFT                    (6u)

#define I2C_CTRL_STOP_DET_IFADDRESSED_MASK              (0x00000080ul)
#define I2C_CTRL_STOP_DET_IFADDRESSED_SHIFT             (7u)

#define I2C_CTRL_TX_EMPTY_CTRL_MASK                     (0x00000100ul)
#define I2C_CTRL_TX_EMPTY_CTRL_SHIFT                    (8u)

/* TAR Bit fields */
#define I2C_TAR_TAR_MASK                                (0x000003FFul)
#define I2C_TAR_TAR_SHIFT                               (0u)

#define I2C_TAR_GC_OR_START_MASK                        (0x00000400ul)
#define I2C_TAR_GC_OR_START_SHIFT                       (10u)

#define I2C_TAR_SPECIAL_MASK                            (0x00000800ul)
#define I2C_TAR_SPECIAL_SHIFT                           (11u)

/* SAR Bit fields */
#define I2C_SAR_SAR_MASK                                (0x000003FFul)
#define I2C_SAR_SAR_SHIFT                               (0u)

/* DATA_CMD Bit fields */
#define I2C_DATA_CMD_DATA_MASK                          (0x000000FFul)
#define I2C_DATA_CMD_DATA_SHIFT                         (0u)

#define I2C_DATA_CMD_CMD_MASK                           (0x00000100ul)
#define I2C_DATA_CMD_CMD_SHIFT                          (8u)

/* XX_SCL_XXX_CNT Bit fields */
#define I2C_XX_SCL_XXX_CNT_COUNTER_MASK                 (0x0000FFFFul)
#define I2C_XX_SCL_XXX_CNT_COUNTER_SHIFT                (0u)

/* INTR_STAT Bit fields */
#define I2C_INTR_STAT_RX_UNDER_MASK                     (0x00000001ul)
#define I2C_INTR_STAT_RX_UNDER_SHIFT                    (0u)

#define I2C_INTR_STAT_RX_OVER_MASK                     (0x00000002ul)
#define I2C_INTR_STAT_RX_OVER_SHIFT                    (1u)

#define I2C_INTR_STAT_RX_FULL_MASK                      (0x00000004ul)
#define I2C_INTR_STAT_RX_FULL_SHIFT                     (2u)

#define I2C_INTR_STAT_TX_OVER_MASK                      (0x00000008ul)
#define I2C_INTR_STAT_TX_OVER_SHIFT                     (3u)

#define I2C_INTR_STAT_TX_EMPTY_MASK                     (0x00000010ul)
#define I2C_INTR_STAT_TX_EMPTY_SHIFT                    (4u)

#define I2C_INTR_STAT_RD_REQ_MASK                       (0x00000020ul)
#define I2C_INTR_STAT_RD_REQ_SHIFT                      (5u)

#define I2C_INTR_STAT_TX_ABRT_MASK                      (0x00000040ul)
#define I2C_INTR_STAT_TX_ABRT_SHIFT                     (6u)

#define I2C_INTR_STAT_RX_DONE_MASK                      (0x00000080ul)
#define I2C_INTR_STAT_RX_DONE_SHIFT                     (7u)

#define I2C_INTR_STAT_ACTIVITY_MASK                     (0x00000100ul)
#define I2C_INTR_STAT_ACTIVITY_SHIFT                    (8u)

#define I2C_INTR_STAT_STOP_DET_MASK                     (0x00000200ul)
#define I2C_INTR_STAT_STOP_DET_SHIFT                    (9u)

#define I2C_INTR_STAT_START_DET_MASK                    (0x00000400ul)
#define I2C_INTR_STAT_START_DET_SHIFT                   (10u)

#define I2C_INTR_STAT_GEN_CALL_MASK                     (0x00000800ul)
#define I2C_INTR_STAT_GEN_CALL_SHIFT                    (11u)

#define I2C_INTR_STAT_RESTART_DET_MASK                  (0x00001000ul)
#define I2C_INTR_STAT_RESTART_DET_SHIFT                 (12u)

#define I2C_INTR_STAT_MASTER_ON_HOLD_MASK               (0x00002000ul)
#define I2C_INTR_STAT_MASTER_ON_HOLD_SHIFT              (13u)

#define I2C_INTR_STAT_SCL_STUCK_AT_LOW_MASK             (0x00004000ul)
#define I2C_INTR_STAT_SCL_STUCK_AT_LOW_SHIFT            (14u)

/* INTR_MASK Bit fields */
#define I2C_INTR_MASK_RX_UNDER_MASK                     (0x00000001ul)
#define I2C_INTR_MASK_RX_UNDER_SHIFT                    (0u)

#define I2C_INTR_MASK_RX_OVER_MASK                     (0x00000002ul)
#define I2C_INTR_MASK_RX_OVER_SHIFT                    (1u)

#define I2C_INTR_MASK_RX_FULL_MASK                      (0x00000004ul)
#define I2C_INTR_MASK_RX_FULL_SHIFT                     (2u)

#define I2C_INTR_MASK_TX_OVER_MASK                      (0x00000008ul)
#define I2C_INTR_MASK_TX_OVER_SHIFT                     (3u)

#define I2C_INTR_MASK_TX_EMPTY_MASK                     (0x00000010ul)
#define I2C_INTR_MASK_TX_EMPTY_SHIFT                    (4u)

#define I2C_INTR_MASK_RD_REQ_MASK                       (0x00000020ul)
#define I2C_INTR_MASK_RD_REQ_SHIFT                      (5u)

#define I2C_INTR_MASK_TX_ABRT_MASK                      (0x00000040ul)
#define I2C_INTR_MASK_TX_ABRT_SHIFT                     (6u)

#define I2C_INTR_MASK_RX_DONE_MASK                      (0x00000080ul)
#define I2C_INTR_MASK_RX_DONE_SHIFT                     (7u)

#define I2C_INTR_MASK_ACTIVITY_MASK                     (0x00000100ul)
#define I2C_INTR_MASK_ACTIVITY_SHIFT                    (8u)

#define I2C_INTR_MASK_STOP_DET_MASK                     (0x00000200ul)
#define I2C_INTR_MASK_STOP_DET_SHIFT                    (9u)

#define I2C_INTR_MASK_START_DET_MASK                    (0x00000400ul)
#define I2C_INTR_MASK_START_DET_SHIFT                   (10u)

#define I2C_INTR_MASK_GEN_CALL_MASK                     (0x00000800ul)
#define I2C_INTR_MASK_GEN_CALL_SHIFT                    (11u)

#define I2C_INTR_MASK_RESTART_DET_MASK                  (0x00001000ul)
#define I2C_INTR_MASK_RESTART_DET_SHIFT                 (12u)

#define I2C_INTR_MASK_MASTER_ON_HOLD_MASK               (0x00002000ul)
#define I2C_INTR_MASK_MASTER_ON_HOLD_SHIFT              (13u)

#define I2C_INTR_MASK_SCL_STUCK_AT_LOW_MASK             (0x00004000ul)
#define I2C_INTR_MASK_SCL_STUCK_AT_LOW_SHIFT            (14u)

/* CLR_XXX Bit fields */
#define I2C_CLR_XXX_CLR_REQ_MASK                        (0x00000001ul)
#define I2C_CLR_XXX_CLR_REQ_SHIFT                       (0u)

/* ENABLE Bit fields */
#define I2C_ENABLE_ENABLE_MASK                          (0x00000001ul)
#define I2C_ENABLE_ENABLE_SHIFT                         (0u)

#define I2C_ENABLE_ABORT_MASK                           (0x00000002ul)
#define I2C_ENABLE_ABORT_SHIFT                          (1u)

/* STATUS Bit fields */
#define I2C_STAUTS_ACTIVITY_MASK                        (0x00000001ul)
#define I2C_STAUTS_ACTIVITY_SHIFT                       (0u)

#define I2C_STAUTS_TFNF_MASK                            (0x00000002ul)
#define I2C_STAUTS_TFNF_SHIFT                           (1u)

#define I2C_STAUTS_TFE_MASK                             (0x00000004ul)
#define I2C_STAUTS_TFE_SHIFT                            (2u)

#define I2C_STAUTS_RFNE_MASK                            (0x00000008ul)
#define I2C_STAUTS_RFNE_SHIFT                           (3u)

#define I2C_STAUTS_RFF_MASK                             (0x00000010ul)
#define I2C_STAUTS_RFF_SHIFT                            (4u)

#define I2C_STAUTS_MST_ACTIVITY_MASK                    (0x00000020ul)
#define I2C_STAUTS_MST_ACTIVITY_SHIFT                   (5u)

#define I2C_STAUTS_SLV_ACTIVITY_MASK                    (0x00000040ul)
#define I2C_STAUTS_SLV_ACTIVITY_SHIFT                   (6u)

/* TXFLR Bit fields */
#define I2C_TXFLR_TXFLR_MASK                            (0x0000001Ful)
#define I2C_TXFLR_TXFLR_SHIFT                           (0u)

/* RXFLR Bit fields */
#define I2C_RXFLR_RXFLR_MASK                            (0x0000001Ful)
#define I2C_RXFLR_RXFLR_SHIFT                           (0u)

/* SDA_HOLD Bit fields */
#define I2C_SDA_HOLD_RX_HOLD_MASK                       (0x000000FFul)
#define I2C_SDA_HOLD_RX_HOLD_SHIFT                      (16u)

#define I2C_SDA_HOLD_TX_HOLD_MASK                       (0x0000FFFFul)
#define I2C_SDA_HOLD_TX_HOLD_SHIFT                      (0u)

/* SDA_HOLD Bit fields */
#define I2C_TX_ABRT_SOURCE_ABRT_7B_ADDR_NOACK_MASK      (0x00000001ul)
#define I2C_TX_ABRT_SOURCE_ABRT_7B_ADDR_NOACK_SHIFT     (0u)

#define I2C_TX_ABRT_SOURCE_ABRT_10ADDR1_NOACK_MASK      (0x00000002ul)
#define I2C_TX_ABRT_SOURCE_ABRT_10ADDR1_NOACK_SHIFT     (1u)

#define I2C_TX_ABRT_SOURCE_ABRT_10ADDR2_NOACK_MASK      (0x00000004ul)
#define I2C_TX_ABRT_SOURCE_ABRT_10ADDR2_NOACK_SHIFT     (2u)

#define I2C_TX_ABRT_SOURCE_ABRT_TXDATA_NOACK_MASK       (0x00000008ul)
#define I2C_TX_ABRT_SOURCE_ABRT_TXDATA_NOACK_SHIFT      (3u)

#define I2C_TX_ABRT_SOURCE_ABRT_GCALL_NOACK_MASK        (0x00000010ul)
#define I2C_TX_ABRT_SOURCE_ABRT_GCALL_NOACK_SHIFT       (4u)

#define I2C_TX_ABRT_SOURCE_ABRT_GCALL_READ_MASK         (0x00000020ul)
#define I2C_TX_ABRT_SOURCE_ABRT_GCALL_READ_SHIFT        (5u)

#define I2C_TX_ABRT_SOURCE_ABRT_HS_ACKDET_MASK          (0x00000040ul)
#define I2C_TX_ABRT_SOURCE_ABRT_HS_ACKDET_SHIFT         (6u)

#define I2C_TX_ABRT_SOURCE_ABRT_SBYTE_ACKDET_MASK       (0x00000080ul)
#define I2C_TX_ABRT_SOURCE_ABRT_SBYTE_ACKDET_SHIFT      (7u)

#define I2C_TX_ABRT_SOURCE_ABRT_HS_NORSTRT_MASK         (0x00000100ul)
#define I2C_TX_ABRT_SOURCE_ABRT_HS_NORSTRT_SHIFT        (8u)

#define I2C_TX_ABRT_SOURCE_ARB_SBYTE_NORSTRT_MASK       (0x00000200ul)
#define I2C_TX_ABRT_SOURCE_ARB_SBYTE_NORSTRT_SHIFT      (9u)

#define I2C_TX_ABRT_SOURCE_ARB_10B_RD_NORSTRT_MASK      (0x00000400ul)
#define I2C_TX_ABRT_SOURCE_ARB_10B_RD_NORSTRT_SHIFT     (10u)

#define I2C_TX_ABRT_SOURCE_ARB_MASTER_DIS_MASK          (0x00000800ul)
#define I2C_TX_ABRT_SOURCE_ARB_MASTER_DIS_SHIFT         (11u)

#define I2C_TX_ABRT_SOURCE_ARB_LOST_MASK                (0x00001000ul)
#define I2C_TX_ABRT_SOURCE_ARB_LOST_SHIFT               (12u)

#define I2C_TX_ABRT_SOURCE_ABRT_SLVFLUSH_TXFIFO_MASK    (0x00002000ul)
#define I2C_TX_ABRT_SOURCE_ABRT_SLVFLUSH_TXFIFO_SHIFT   (13u)

#define I2C_TX_ABRT_SOURCE_ABRT_SLV_ARBLOST_MASK        (0x00004000ul)
#define I2C_TX_ABRT_SOURCE_ABRT_SLV_ARBLOST_SHIFT       (14u)

#define I2C_TX_ABRT_SOURCE_ABRT_SLVRD_INTX_MASK         (0x00008000ul)
#define I2C_TX_ABRT_SOURCE_ABRT_SLVRD_INTX_SHIFT        (15u)

#define I2C_TX_ABRT_SOURCE_ABRT_USER_ABRT_MASK          (0x00010000ul)
#define I2C_TX_ABRT_SOURCE_ABRT_USER_ABRT_SHIFT         (16u)

#define I2C_TX_ABRT_SOURCE_TX_FLUSH_CNT_MASK            (0x0F800000ul)
#define I2C_TX_ABRT_SOURCE_TX_FLUSH_CNT_SHIFT           (23u)

/* I2C_DMA_CR Bit fields */
#define I2C_DMA_CR_RDMAE_MASK                           (0x00000001ul)
#define I2C_DMA_CR_RDMAE_SHIFT                          (0u)

#define I2C_DMA_CR_TDMAE_MASK                           (0x00000002ul)
#define I2C_DMA_CR_TDMAE_SHIFT                          (1u)

/* I2C_DMA_TDLR Bit fields */
#define I2C_DMA_TDLR_DMATDL_MASK                        (0x0000000Ful)
#define I2C_DMA_TDLR_DMATDL_SHIFT                       (0u)

/* I2C_DMA_RDLR Bit fields */
#define I2C_DMA_RDLR_DMARDL_MASK                        (0x0000000Ful)
#define I2C_DMA_RDLR_DMARDL_SHIFT                       (0u)

/* I2C_SDA_SETUP Bit fields */
#define I2C_SDA_SETUP_SDA_SETUP_MASK                    (0x000000FFul)
#define I2C_SDA_SETUP_SDA_SETUP_SHIFT                   (0u)

/* I2C_ACK_GCALL Bit fields */
#define I2C_ACK_GCALL_ACK_GEN_CALL_MASK                 (0x00000001ul)
#define I2C_ACK_GCALL_ACK_GEN_CALL_SHIFT                (0u)

/* I2C_ENABLE_STATUS Bit fields */
#define I2C_ENABLE_STATUS_EN_MASK                       (0x00000001ul)
#define I2C_ENABLE_STATUS_EN_SHIFT                      (0u)

#define I2C_ENABLE_STATUS_SLV_DISABLED_WHILE_BUSY_MASK  (0x00000002ul)
#define I2C_ENABLE_STATUS_SLV_DISABLED_WHILE_BUSY_SHIFT (1u)

#define I2C_ENABLE_STATUS_SLV_RX_DATA_LOST_MASK         (0x00000004ul)
#define I2C_ENABLE_STATUS_SLV_RX_DATA_LOST_SHIFT        (2u)

/* I2C_SPKLEN Bit fields */
#define I2C_SPKLEN_LEN_MASK                             (0x000000FFul)
#define I2C_SPKLEN_LEN_SHIFT                            (0u)

/******************************************************************************
 * the typedefs
 *****************************************************************************/

/*! \brief the definition of i2c register */
typedef struct _I2cRegType_
{
    volatile uint32_t CTRL; /*!< I2C Control Register, offset: 0x0 */
    volatile uint32_t TAR;  /*!< I2C Target address Register, offset: 0x4 */
    volatile uint32_t SAR;  /*!< I2C Slave address Register, offset: 0x8 */
    uint32_t          Res0;
    volatile uint32_t DATA_CMD;    /*!< I2C Data & Command Register, offset: 0x10 */
    volatile uint32_t SS_SCL_HCNT; /*!< I2C Standard Speed I2C clock high count Register, offset: 0x14 */
    volatile uint32_t SS_SCL_LCNT; /*!< I2C Standard Speed I2C clock high count Register, offset: 0x18 */
    volatile uint32_t FS_SCL_HCNT; /*!< I2C Fast speed I2C clock high count Register, offset: 0x1c */
    volatile uint32_t FS_SCL_LCNT; /*!< I2C Fast speed I2C clock low count Register, offset: 0x20 */
    uint32_t          Res1[2];
    volatile uint32_t INTR_STAT;      /*!< I2C Interrupt status Register, offset: 0x2C */
    volatile uint32_t INTR_MASK;      /*!< I2C Interrupt mask Register, offset: 0x30 */
    volatile uint32_t RAW_INTR_STAT;  /*!< I2C RAW INTERRUPT Register, offset: 0x34 */
    volatile uint32_t RX_TL;          /*!< I2C RX FIFO threshold Register, offset: 0x38 */
    volatile uint32_t TX_TL;          /*!< I2C TX FIFO threshold Register, offset: 0x3C */
    volatile uint32_t CLR_INTR;       /*!< I2C Clear interrupt Register, offset: 0x40 */
    volatile uint32_t CLR_RX_UNDER;   /*!< I2C Clear RX_UNDER interrupt Register, offset: 0x44 */
    volatile uint32_t CLR_RX_OVER;    /*!< I2C Clear RX OVER interrupt Register, offset: 0x48 */
    volatile uint32_t CLR_TX_OVER;    /*!< I2C Clear TX OVER interrupt Register, offset: 0x4C */
    volatile uint32_t CLR_RD_REQ;     /*!< I2C Clear RD_REQ interrupt Register, offset: 0x50 */
    volatile uint32_t CLR_TX_ABRT;    /*!< I2C Clear TX_ABRT interrupt Register, offset: 0x54 */
    volatile uint32_t CLR_RX_DONE;    /*!< I2C Clear RX DONE interrupt Register, offset: 0x58 */
    volatile uint32_t CLR_ACTIVITY;   /*!< I2C Clear ACTIVITY interrupt Register, offset: 0x5C */
    volatile uint32_t CLR_STOP_DET;   /*!< I2C Clear STOP_DET interrupt Register, offset: 0x60 */
    volatile uint32_t CLR_START_DET;  /*!< I2C Clear START_DET interrupt Register, offset: 0x64 */
    volatile uint32_t CLR_GEN_CALL;   /*!< I2C Clear GEN_CALL interrupt Register, offset: 0x68 */
    volatile uint32_t ENABLE;         /*!< I2C ENABLE Register, offset: 0x6C */
    volatile uint32_t STATUS;         /*!< I2C STATUS Register, offset: 0x70 */
    volatile uint32_t TXFLR;          /*!< I2C TX FIFO LEVEL Register, offset: 0x74 */
    volatile uint32_t RXFLR;          /*!< I2C RX FIFO LEVEL Register, offset: 0x78 */
    volatile uint32_t SDA_HOLD;       /*!< I2C SDA HOLD TIME length Register, offset: 0x7C */
    volatile uint32_t TX_ABRT_SOURCE; /*!< I2C Transmit ABORT source Register, offset: 0x80 */
    uint32_t          Res2;
    volatile uint32_t DMA_CR;        /*!< I2C DMA control Register, offset: 0x88 */
    volatile uint32_t DMA_TDLR;      /*!< I2C DMA Transmit Data Level Register, offset: 0x8C */
    volatile uint32_t DMA_RDLR;      /*!< I2C DMA Receive Data Level Register, offset: 0x90 */
    volatile uint32_t SDA_SETUP;     /*!< I2C SDA SETUP Register, offset: 0x94 */
    volatile uint32_t ACK_GCALL;     /*!< I2C Ack for General Call Register, offset: 0x98 */
    volatile uint32_t ENABLE_STATUS; /*!< I2C ENABLE status Register, offset: 0x9C */
    volatile uint32_t SPKLEN;        /*!< I2C SS,FS,FM+ spike suppression limit Register, offset: 0xA0 */
    uint32_t          Res3[23];
} I2cRegType;

/******************************************************************************
 * the globals
 *****************************************************************************/

/******************************************************************************
 * the function prototypes
 *****************************************************************************/

/*! \brief Set the method of controls the generation of TX_EMPTY interrupt.
 *
 * the bit be operated only in the module is in disable
 *
 * \param[in] obj: base address for the i2cinstance
 * \param[in] ctrlMode:
 *              0h: default behaviour
 *              1h: controled generation
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_SetTxEmptyCtrl(I2cRegType *obj, uint8_t ctrlMode)
{
    uint32_t tRegValue = obj->CTRL;

    obj->CTRL = (((uint32_t)ctrlMode << I2C_CTRL_TX_EMPTY_CTRL_SHIFT) | ((~I2C_CTRL_TX_EMPTY_CTRL_MASK) & tRegValue));
}

/*! \brief Set the mode of detect stop bit condition
 *
 * the bit be operated only in the module is in disable
 *
 * \param[in] obj: base address for the i2cinstance
 * \param[in] stopDetMode
 *            0h: issue the STOP_DET irrespective of whether it is addressed or not
 *            1h: issue the STOP_DET irrespective only when it is addressed
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_SetSlaveDetectStopBitMode(I2cRegType *obj, uint8_t stopDetMode)
{
    uint32_t tRegValue = obj->CTRL;

    obj->CTRL = (((uint32_t)stopDetMode << I2C_CTRL_STOP_DET_IFADDRESSED_SHIFT) | ((~I2C_CTRL_STOP_DET_IFADDRESSED_MASK) & tRegValue));
}

/*! \brief slave mode disable
 *
 * this function set the node as slave node or not
 *
 * \param[in] obj: base address for the i2cinstance
 * \param[in] DdisableSlaveMode:
 *            false: enable slave mode
 *            true:  disable slave mode
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_SetSlaveModeDisable(I2cRegType *obj, bool disableSlaveMode)
{
    uint32_t tRegValue = obj->CTRL;

    if(disableSlaveMode == true)
    {
        obj->CTRL = ((1ul << I2C_CTRL_SLAVE_DISABLE_SHIFT) | ((~I2C_CTRL_SLAVE_DISABLE_MASK) & tRegValue));
    }
    else
    {
        obj->CTRL = ((0ul << I2C_CTRL_SLAVE_DISABLE_SHIFT) | ((~I2C_CTRL_SLAVE_DISABLE_MASK) & tRegValue));
    }
}

/*! \brief master RESTART enable
 *
 * the bit be operated only in the module is in disable
 *
 * \param[in] obj: base address for the i2cinstance
 * \param[in] restartEnable:
 *            false: Disabled
 *            true: Enabled
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_SetMasterRestartEnable(I2cRegType *obj, bool restartEnable)
{
    uint32_t tRegValue = obj->CTRL;

    if(restartEnable == true)
    {
        obj->CTRL = ((1ul << I2C_CTRL_RESTART_EN_SHIFT) | ((~I2C_CTRL_RESTART_EN_MASK) & tRegValue));
    }
    else
    {
        obj->CTRL = ((0ul << I2C_CTRL_RESTART_EN_SHIFT) | ((~I2C_CTRL_RESTART_EN_MASK) & tRegValue));
    }
}

/*! \brief Set master address mode
 *
 * the bit be operated only in the module is in disable
 *
 * \param[in] obj: base address for the i2cinstance
 * \param[in] addressMode:
 *            0h:7bit address
 *            1h:10bit address
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_SetMasterAddressMode(I2cRegType *obj, uint8_t addressMode)
{
    uint32_t tRegValue = obj->CTRL;

    obj->CTRL = (((uint32_t)addressMode << I2C_CTRL_MST_ADDR_MODE_SHIFT) | ((~I2C_CTRL_MST_ADDR_MODE_MASK) & tRegValue));
}

/*! \brief Set slave address mode
 *
 * the bit be operated only in the module is in disable
 *
 * \param[in] obj: base address for the i2cinstance
 * \param[in] addressMode:
 *            0h:7bit address
 *            1h:10bit address
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_SetSlaveAddressMode(I2cRegType *obj, uint8_t addressMode)
{
    uint32_t tRegValue = obj->CTRL;

    obj->CTRL = (((uint32_t)addressMode << I2C_CTRL_SLV_ADDR_MODE_SHIFT) | ((~I2C_CTRL_SLV_ADDR_MODE_MASK) & tRegValue));
}

/*! \brief Set the master speed
 *
 * the bit be operated only in the module is in disable
 *
 * \param[in] obj: base address for the i2cinstance
 * \param[in] speedMode:
 *            1h:standard mode,100kbit/s
 *            2h:fast mode <=400kbit/s or fast mode plus<=1000kbit/s;
 *            3h: high speed 3.4Mbit/s--not supported
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_SetSpeedMode(I2cRegType *obj, uint8_t speedMode)
{
    uint32_t tRegValue = obj->CTRL;

    obj->CTRL = (((uint32_t)speedMode << I2C_CTRL_SPEED_SHIFT) | ((~I2C_CTRL_SPEED_MASK) & tRegValue));
}

/*! \brief Get the master speed
 *
 * this function get the master speed
 *
 * \param[in] obj: base address for the i2cinstance
 * \return: uint8_t
 *          1h:standard mode,100kbit/s
 *          2h:fast mode <=400kbit/s or fast mode plus<=1000kbit/s;
 *          3h: high speed 3.4Mbit/s--not supported
 */
__attribute__((always_inline)) static inline uint8_t I2cReg_GetSpeedMode(const I2cRegType *obj)
{
    uint8_t tRtn = 0;

    tRtn = (((obj->CTRL & I2C_CTRL_SPEED_MASK) >> I2C_CTRL_SPEED_SHIFT) & 0xFF);

    return tRtn;
}

/*! \brief I2C master mode control
 *
 * the bit be operated only in the module is in disable
 *
 * \param[in] obj: base address for the i2cinstance
 * \param[in] masterMode:
 *            0h: slave mode
 *            1h: master mode
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_SetMasterMode(I2cRegType *obj, bool masterMode)
{
    uint32_t tRegValue = obj->CTRL;

    if(masterMode == true)
    {
        obj->CTRL = ((1ul << I2C_CTRL_MST_MODE_SHIFT) | ((~I2C_CTRL_MST_MODE_MASK) & tRegValue));
    }
    else
    {
        obj->CTRL = ((0ul << I2C_CTRL_MST_MODE_SHIFT) | ((~I2C_CTRL_MST_MODE_MASK) & tRegValue));
    }
}

/*! \brief Get the type of the node
 *
 * this function get the moudle whether it be used as master node
 *
 * \param[in] obj: base address for the i2cinstance
 * \return: bool
 *          true: as a master node
 *          false:as a slave node
 */
__attribute__((always_inline)) static inline bool I2cReg_GetModuleAsMaster(const I2cRegType *obj)
{
    bool tRtn = false;

    if((obj->CTRL & I2C_CTRL_MST_MODE_MASK) != 0ul)
    {
        tRtn = true;
    }

    return tRtn;
}

/*! \brief indicates whether software performs a General Call or Start Byte command
 *
 * the bit be operated only in the module is in disable
 *
 * \param[in] obj: base address for the i2cinstance
 * \param[in] supportedSpecialCmd:
 *            0b: not support
 *            1b: support
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_SetSpecialCommand(I2cRegType *obj, uint8_t supportedSpecialCmd)
{
    uint32_t tRegValue = obj->TAR;

    obj->TAR = (((uint32_t)supportedSpecialCmd << I2C_TAR_SPECIAL_SHIFT) | ((~I2C_TAR_SPECIAL_MASK) & tRegValue));
}

/*! \brief Set special type
 *
 * the bit be operated only in the module is in disable
 *
 * \param[in] obj: base address for the i2cinstance
 * \param[in] SsecialCmdType:
 *            0h:General Call
 *            1h:Start byte
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_SetSpecialCmdType(I2cRegType *obj, uint8_t specialCmdType)
{
    uint32_t tRegValue = obj->TAR;

    obj->TAR = (((uint32_t)specialCmdType << I2C_TAR_GC_OR_START_SHIFT) | ((~I2C_TAR_GC_OR_START_MASK) & tRegValue));
}

/*! \brief Set target address for master
 *
 * It is the target address for master transaction. When transmitting a Genral Call, it is ignored,
 *       the bit be operated only in the module is in disable
 *
 * \param[in] obj: base address for the i2cinstance
 * \param[in] targetAddr: the target address of node
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_SetTargetAddress(I2cRegType *obj, uint16_t targetAddr)
{
    uint32_t tRegValue = obj->TAR;

    obj->TAR = (((uint32_t)targetAddr << I2C_TAR_TAR_SHIFT) | ((~I2C_TAR_TAR_MASK) & tRegValue));
}

/*! \brief Get the current target address for master
 *
 * this function get the target address for master
 *
 * \param[in] obj: base address for the i2cinstance
 * \return: the target node of address
 */
__attribute__((always_inline)) static inline uint32_t I2cReg_GetTargetAddress(const I2cRegType *obj)
{
    uint32_t tRtn = 0;

    tRtn = ((obj->TAR & I2C_TAR_TAR_MASK) >> I2C_TAR_TAR_SHIFT);

    return tRtn;
}

/*! \brief Set slave address
 *
 * only be written when I2C interface is disabled.the bit be operated only in the module is in disable
 *
 * \param[in] obj: base address for the i2cinstance
 * \param[in] slaveAddress: the slave node of address
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_SetSlaveAddress(I2cRegType *obj, uint16_t slaveAddress)
{
    uint32_t tRegValue = obj->SAR;

    obj->SAR = (((uint32_t)slaveAddress << I2C_SAR_SAR_SHIFT) | ((~I2C_SAR_SAR_MASK) & tRegValue));
}

/*! \brief Write transmit data and command
 *
 * Read or write data from this register
 *
 * \param[in] obj: base address for the i2cinstance
 * \param[in] data: the transmit data
 * \param[in] readCmd:
 *            0b: write command
 *            1b: read command
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_SetDataAndCmd(I2cRegType *obj, uint8_t data, bool readCmd)
{
    uint32_t tDataCmd = 0;

    tDataCmd = data;

    if(readCmd == true)
    {
        tDataCmd |= I2C_DATA_CMD_CMD_MASK;
    }

    obj->DATA_CMD = tDataCmd;
}

/*! \brief Get received data
 *
 * this function read out datas from rx fifo
 *
 * \param[in] obj: base address for the i2cinstance
 * \return: received data
 */
__attribute__((always_inline)) static inline uint8_t I2cReg_GetData(const I2cRegType *obj)
{
    uint8_t tRtn = 0;

    tRtn = (((obj->DATA_CMD & I2C_DATA_CMD_DATA_MASK) >> I2C_DATA_CMD_DATA_SHIFT) & 0xFF);

    return tRtn;
}

/*! \brief Set Standard Speed I2C clock high count
 *
 * This register can be written only when the I2C interface is disabled
 *
 * \param[in] obj: base address for the i2cinstance
 * \param[in] highCount: the i2c clock high count value
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_SetStandardModeHighLevelCount(I2cRegType *obj, uint16_t highCount)
{
    uint32_t tRegValue = obj->SS_SCL_HCNT;

    obj->SS_SCL_HCNT = (((uint32_t)highCount << I2C_XX_SCL_XXX_CNT_COUNTER_SHIFT) | ((~I2C_XX_SCL_XXX_CNT_COUNTER_MASK) & tRegValue));
}

/*! \brief Get Standard Speed I2C clock high count
 *
 * this function get the high counter in standard speed mode
 *
 * \param[in] obj: base address for the i2cinstance
 * \return: the i2c clock high count value
 */
__attribute__((always_inline)) static inline uint16_t I2cReg_GetStandardModeHighLevelCount(const I2cRegType *obj)
{
    uint16_t tRtn = 0;

    tRtn = ((obj->SS_SCL_HCNT & I2C_XX_SCL_XXX_CNT_COUNTER_MASK) & 0xFFFF);

    return tRtn;
}

/*! \brief Set Standard Speed I2C clock low count
 *
 * This register can be written only when the I2C interface is disabled
 *
 * \param[in] obj: base address for the i2cinstance
 * \param[in] lowCount: Standard Speed I2C clock low count
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_SetStandardModeLowLevelCount(I2cRegType *obj, uint16_t lowCount)
{
    uint32_t tRegValue = obj->SS_SCL_LCNT;

    obj->SS_SCL_LCNT = (((uint32_t)lowCount << I2C_XX_SCL_XXX_CNT_COUNTER_SHIFT) | ((~I2C_XX_SCL_XXX_CNT_COUNTER_MASK) & tRegValue));
}

/*! \brief Get Standard Speed I2C clock low count
 *
 * this function get the low counter in standard speed mode
 *
 * \param[in] obj: base address for the i2cinstance
 * \return: Standard Speed I2C clock low count
 */
__attribute__((always_inline)) static inline uint16_t I2cReg_GetStandardModeLowLevelCount(const I2cRegType *obj)
{
    uint16_t tRtn = 0;

    tRtn = ((obj->SS_SCL_LCNT & I2C_XX_SCL_XXX_CNT_COUNTER_MASK) & 0xFFFF);

    return tRtn;
}

/*! \brief Set FAST Speed I2C clock high count
 *
 * This register can be written only when the I2C interface is disabled
 *
 * \param[in] obj: base address for the i2cinstance
 * \param[in] highCount: FAST Speed I2C clock high count
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_SetFastModeHighLevelCount(I2cRegType *obj, uint16_t highCount)
{
    uint32_t tRegValue = obj->FS_SCL_HCNT;

    obj->FS_SCL_HCNT = (((uint32_t)highCount << I2C_XX_SCL_XXX_CNT_COUNTER_SHIFT) | ((~I2C_XX_SCL_XXX_CNT_COUNTER_MASK) & tRegValue));
}

/*! \brief Get Fast Speed I2C clock High count
 *
 * this function get the high counter in fast speed mode
 *
 * \param[in] obj: base address for the i2cinstance
 * \return: Fast Speed I2C clock High count
 */
__attribute__((always_inline)) static inline uint16_t I2cReg_GetFastModeHighLevelCount(const I2cRegType *obj)
{
    uint16_t tRtn = 0;

    tRtn = ((obj->FS_SCL_HCNT & I2C_XX_SCL_XXX_CNT_COUNTER_MASK) & 0xFFFF);

    return tRtn;
}

/*! \brief Set FAST Speed I2C clock low count
 *
 * This register can be written only when the I2C interface is disabled
 *
 * \param[in] obj: base address for the i2cinstance
 * \param[in] lowCount:  FAST Speed I2C clock low count
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_SetFastModeLowLevelCount(I2cRegType *obj, uint16_t lowCount)
{
    uint32_t tRegValue = obj->FS_SCL_LCNT;

    obj->FS_SCL_LCNT = (((uint32_t)lowCount << I2C_XX_SCL_XXX_CNT_COUNTER_SHIFT) | ((~I2C_XX_SCL_XXX_CNT_COUNTER_MASK) & tRegValue));
}

/*! \brief Get Fast Speed I2C clock low count
 *
 * Note:this function get the low counter in fast speed mode
 *
 * \param[in] obj: base address for the i2cinstance
 * \return: Fast Speed I2C clock low count
 */
__attribute__((always_inline)) static inline uint16_t I2cReg_GetFastModeLowLevelCount(const I2cRegType *obj)
{
    uint16_t tRtn = 0;

    tRtn = ((obj->FS_SCL_LCNT & I2C_XX_SCL_XXX_CNT_COUNTER_MASK) & 0xFFFF);

    return tRtn;
}

/*! \brief Get I2C interrupt status
 *
 * this function get the special interrupt status
 *
 * \param[in] obj: base address for the i2cinstance
 * \param[in] interruptStatusMask: conbination of more than one status
 * \return: bool
 *          0h: inactive
 *          1h: active
 */
__attribute__((always_inline)) static inline bool I2cReg_GetInterruptStatus(const I2cRegType *obj, uint32_t interruptStatusMask)
{
    uint32_t tIsrStatus = 0;
    bool     tRtn       = false;

    tIsrStatus = obj->INTR_STAT;

    if((tIsrStatus & interruptStatusMask) != 0u)
    {
        tRtn = true;
    }

    return tRtn;
}

/*! \brief Get I2C raw interrupt status
 *
 * this function get the interrupt raw status
 *
 * \param[in] obj: base address for the i2cinstance
 * \param[in] interruptStatusMask: conbination of more than one status
 * \return: bool
 *          0h: inactive
 *          1h: active
 */
__attribute__((always_inline)) static inline bool I2cReg_GetInterruptRawStatus(const I2cRegType *obj, uint32_t interruptStatusMask)
{
    uint32_t tStatus = 0;
    bool     tRtn    = false;

    tStatus = obj->RAW_INTR_STAT;

    if((tStatus & interruptStatusMask) != 0u)
    {
        tRtn = true;
    }

    return tRtn;
}

/*! \brief Get Ic Status
 *
 * this function get the ic module status
 *
 * \param[in] obj: base address for the i2cinstance
 * \param[in] statusMask: conbination of more than one status
 * \return: bool
 *          false: no happend
 *          true: happend
 */
__attribute__((always_inline)) static inline bool I2cReg_GetICStatus(const I2cRegType *obj, uint32_t statusMask)
{
    uint32_t tStatus = 0;
    bool     tRtn    = false;

    tStatus = obj->STATUS;

    if((tStatus & statusMask) != 0u)
    {
        tRtn = true;
    }

    return tRtn;
}

/*! \brief Enable or disable interrupt req
 *
 * this function set the special interrupt request action when condition is matched
 *
 * \param[in] obj: base address for the i2cinstance
 * \param[in] interruptStatusMask: the special interrupt status
 * \param[in] enInterruptReq: enable or disable
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_SetInterruptMask(I2cRegType *obj, uint32_t interruptStatusMask, bool enInterruptReq)
{
    if(enInterruptReq == true)
    {
        obj->INTR_MASK |= interruptStatusMask;
    }
    else
    {
        obj->INTR_MASK &= (~interruptStatusMask);
    }
}

/*! \brief Get the current interrupt status
 *
 * This function get the current inyrttupy is enabled or disabled
 *
 * \param[in] obj: base address for the i2cinstance
 * \param[in] interruptStatusMask: the special interrupt status
 * \return: bool
 *          true: is enabled
 *          false: is disabled
 */
__attribute__((always_inline)) static inline bool I2cReg_GetInterruptIsEnabled(const I2cRegType *obj, uint32_t interruptStatusMask)
{
    bool isEnabled = false;

    if((obj->INTR_MASK & interruptStatusMask) != 0u)
    {
        isEnabled = true;
    }

    return isEnabled;
}

/*! \brief Set RX FIFO threshold
 *
 * I2C RX FIFO threshold FIFO depth is 16
 *
 * \param[in] obj: base address for the i2cinstance
 * \param[in] rxFifoThreshold: RX FIFO threshold value
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_SetRxFifoThreshold(I2cRegType *obj, uint8_t rxFifoThreshold)
{
    uint32_t tRegValue = obj->RX_TL;

    obj->RX_TL = (((uint32_t)rxFifoThreshold << I2C_RXFLR_RXFLR_SHIFT) | ((~I2C_RXFLR_RXFLR_MASK) & tRegValue));
}

/*! \brief Set TX FIFO threshold
 *
 * I2C TX FIFO threshold FIFO depth is 16
 *
 * \param[in] obj: base address for the i2cinstance
 * \param[in] txFifoThreshold: TX FIFO threshold
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_SetTxFifoThreshold(I2cRegType *obj, uint8_t txFifoThreshold)
{
    uint32_t tRegValue = obj->TX_TL;

    obj->TX_TL = (((uint32_t)txFifoThreshold << I2C_TXFLR_TXFLR_SHIFT) | ((~I2C_TXFLR_TXFLR_MASK) & tRegValue));
}

/*! \brief Clear all interrupt status
 *
 * Read this register to clear all interrupts and I2C_TX_ABRT_SOURCE, It does not clear hardware clearable interrupts but software clearable interrupts.
 *
 * \param[in] obj: base address for the i2cinstance
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_ClearAllInterruptStatus(I2cRegType *obj)
{
    (void)((obj->CLR_INTR & I2C_CLR_XXX_CLR_REQ_MASK) >> I2C_CLR_XXX_CLR_REQ_SHIFT);

    /* Read back to avoid problem */
    (void)obj->CLR_INTR;
}

/*! \brief clear interrupt status in the RAW_INTR_STAT
 *
 * this function clear the rx under status after interrupt request handler
 *
 * \param[in] obj: base address for the i2cinstance
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_ClearRxUnderStatus(I2cRegType *obj)
{
    (void)((obj->CLR_RX_UNDER & I2C_CLR_XXX_CLR_REQ_MASK) >> I2C_CLR_XXX_CLR_REQ_SHIFT);

    /* Read back to avoid problem */
    (void)obj->CLR_RX_UNDER;
}

/*! \brief clear interrupt status in the RAW_INTR_STAT
 *
 * Note:this function clear the rx overflow status after interrupt request handler
 *
 * \param[in] obj: base address for the i2cinstance
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_ClearRxOverStatus(I2cRegType *obj)
{
    (void)((obj->CLR_RX_OVER & I2C_CLR_XXX_CLR_REQ_MASK) >> I2C_CLR_XXX_CLR_REQ_SHIFT);

    /* Read back to avoid problem */
    (void)obj->CLR_RX_OVER;
}

/*! \brief clear interrupt status in the RAW_INTR_STAT
 *
 * Note:this function clear the tx overflow status after interrupt request handler
 *
 * \param[in] obj: base address for the i2cinstance
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_ClearTxOverStatus(I2cRegType *obj)
{
    (void)((obj->CLR_TX_OVER & I2C_CLR_XXX_CLR_REQ_MASK) >> I2C_CLR_XXX_CLR_REQ_SHIFT);

    /* Read back to avoid problem */
    (void)obj->CLR_TX_OVER;
}

/*! \brief clear interrupt status in the RAW_INTR_STAT
 *
 * Note:this function clear the rx read request status after interrupt request handler
 *
 * \param[in] obj: base address for the i2cinstance
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_ClearReadReqStatus(I2cRegType *obj)
{
    (void)((obj->CLR_RD_REQ & I2C_CLR_XXX_CLR_REQ_MASK) >> I2C_CLR_XXX_CLR_REQ_SHIFT);

    /* Read back to avoid problem */
    (void)obj->CLR_RD_REQ;
}

/*! \brief clear interrupt status in the RAW_INTR_STAT
 *
 * Note:this function clear the tx abort status after interrupt request handler
 *
 * \param[in] obj: base address for the i2cinstance
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_ClearTxAbortStatus(I2cRegType *obj)
{
    (void)((obj->CLR_TX_ABRT & I2C_CLR_XXX_CLR_REQ_MASK) >> I2C_CLR_XXX_CLR_REQ_SHIFT);

    /* Read back to avoid problem */
    (void)obj->CLR_TX_ABRT;
}

/*! \brief clear interrupt status in the RAW_INTR_STAT
 *
 * Note:this function clear the rx done status after interrupt request handler
 *
 * \param[in] obj: base address for the i2cinstance
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_ClearRxDoneStatus(I2cRegType *obj)
{
    (void)((obj->CLR_RX_DONE & I2C_CLR_XXX_CLR_REQ_MASK) >> I2C_CLR_XXX_CLR_REQ_SHIFT);

    /* Read back to avoid problem */
    (void)obj->CLR_RX_DONE;
}

/*! \brief clear interrupt status in the RAW_INTR_STAT
 *
 * Note:this function clear the activity status after interrupt request handler
 *
 * \param[in] obj: base address for the i2cinstance
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_ClearActivityStatus(I2cRegType *obj)
{
    (void)((obj->CLR_ACTIVITY & I2C_CLR_XXX_CLR_REQ_MASK) >> I2C_CLR_XXX_CLR_REQ_SHIFT);

    /* Read back to avoid problem */
    (void)obj->CLR_ACTIVITY;
}

/*! \brief clear interrupt status in the RAW_INTR_STAT
 *
 * Note:this function clear the stop bit detected status after interrupt request handler
 *
 * \param[in] obj: base address for the i2cinstance
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_ClearStopBitDetectStatus(I2cRegType *obj)
{
    (void)((obj->CLR_STOP_DET & I2C_CLR_XXX_CLR_REQ_MASK) >> I2C_CLR_XXX_CLR_REQ_SHIFT);

    /* Read back to avoid problem */
    (void)obj->CLR_STOP_DET;
}

/*! \brief clear interrupt status in the RAW_INTR_STAT
 *
 * Note:this function clear the start bit detected status after interrupt request handler
 *
 * \param[in] obj: base address for the i2cinstance
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_ClearStartBitDetectStatus(I2cRegType *obj)
{
    (void)((obj->CLR_START_DET & I2C_CLR_XXX_CLR_REQ_MASK) >> I2C_CLR_XXX_CLR_REQ_SHIFT);

    /* Read back to avoid problem */
    (void)obj->CLR_START_DET;
}

/*! \brief clear interrupt status in the RAW_INTR_STAT
 *
 * Note:this function clear the general call status after interrupt request handler
 *
 * \param[in] obj: base address for the i2cinstance
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_ClearGeneralCallStatus(I2cRegType *obj)
{
    (void)((obj->CLR_GEN_CALL & I2C_CLR_XXX_CLR_REQ_MASK) >> I2C_CLR_XXX_CLR_REQ_SHIFT);

    /* Read back to avoid problem */
    (void)obj->CLR_GEN_CALL;
}

/*! \brief Set module enable
 *
 * this function enable or disable the i2c module
 *
 * \param[in] obj: base address for the i2cinstance
 * \param[in] ModuleEn: enable or disable
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_SetModuleEnable(I2cRegType *obj, bool moduleEn)
{
    uint32_t tRegValue = obj->ENABLE;

    if(moduleEn == true)
    {
        obj->ENABLE = ((1ul << I2C_ENABLE_ENABLE_SHIFT) | ((~I2C_ENABLE_ENABLE_MASK) & tRegValue));
    }
    else
    {
        obj->ENABLE = ((0ul << I2C_ENABLE_ENABLE_SHIFT) | ((~I2C_ENABLE_ENABLE_MASK) & tRegValue));
    }
}

/*! \brief Abort transfer
 *
 * only set one in the enable bit is 1, clear by hardware
 * after set 1, the hardware will generate a stop condition and clear tx fifo, then hardware clear this bit again
 *
 * \param[in] obj: base address for the i2cinstance
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_SetAbortReq(I2cRegType *obj)
{
    uint32_t tRegValue = obj->ENABLE;

    obj->ENABLE = ((1ul << I2C_ENABLE_ABORT_SHIFT) | ((~I2C_ENABLE_ABORT_MASK) & tRegValue));
}

/*! \brief Get i2c status
 *
 * this function get the current status of module
 *
 * \param[in] obj: base address for the i2cinstance
 * \param[in] StatusMask: one special status mask, only one status
 * \return: bool
 *          false: not exist
 *          true: exist
 */
__attribute__((always_inline)) static inline bool I2cReg_GetModuleStatus(const I2cRegType *obj, uint32_t statusMask)
{
    uint32_t tStatus = 0;
    bool     tRtn    = false;

    tStatus = obj->STATUS;
    if((tStatus & statusMask) != 0u)
    {
        tRtn = true;
    }

    return tRtn;
}

/*! \brief Contains the number of valid data entries in the transmit FIFO.
 *
 * this function get the number of valid data entries in the transmit FIFO
 *
 * \param[in] obj: base address for the i2cinstance
 * \return: the number of valid data entries
 */
__attribute__((always_inline)) static inline uint8_t I2cReg_GetTxFifoLevel(const I2cRegType *obj)
{
    uint8_t tTxFifoLevel = 0;

    tTxFifoLevel = (((obj->TXFLR & I2C_TXFLR_TXFLR_MASK) >> I2C_TXFLR_TXFLR_SHIFT) & 0xFF);

    return tTxFifoLevel;
}

/*! \brief Contains the number of valid data entries in the receive FIFO.
 *
 * this function get the number of valid data entries in the receive FIFO.
 *
 * \param[in] obj: base address for the i2cinstance
 * \return: the number of valid data entries in the receive FIFO.
 */
__attribute__((always_inline)) static inline uint8_t I2cReg_GetRxFifoLevel(const I2cRegType *obj)
{
    uint8_t tRxFifoLevel = 0;

    tRxFifoLevel = (((obj->RXFLR & I2C_RXFLR_RXFLR_MASK) >> I2C_RXFLR_RXFLR_SHIFT) & 0xFF);

    return tRxFifoLevel;
}

/*! \brief Set RX SDA hold time
 *
 * this function set IC SDA HOLD TIME length
 *
 * \param[in] obj: base address for the i2cinstance
 * \param[in] HoldTime: IC SDA HOLD TIME length
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_SetRxDataHoldTime(I2cRegType *obj, uint16_t holdTime)
{
    uint32_t tRegValue = obj->SDA_HOLD;

    obj->SDA_HOLD = (((uint32_t)holdTime << I2C_SDA_HOLD_RX_HOLD_SHIFT) | ((~I2C_SDA_HOLD_RX_HOLD_MASK) & tRegValue));
}

/*! \brief Set TX SDA hold time
 *
 * This bit field can only be written when the I2C_ENABLE[ENABLE] is disabled .
 *
 * \param[in] obj: base address for the i2cinstance
 * \param[in] HoldTime: TX SDA hold time
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_SetTxDataHoldTime(I2cRegType *obj, uint16_t holdTime)
{
    uint32_t tRegValue = obj->SDA_HOLD;

    obj->SDA_HOLD = (((uint32_t)holdTime << I2C_SDA_HOLD_TX_HOLD_SHIFT) | ((~I2C_SDA_HOLD_TX_HOLD_MASK) & tRegValue));
}

/*! \brief Get the Tx abort source information except the tx flush cnt
 *
 * this function get the tx abort information
 *
 * \param[in] obj: base address for the i2cinstance
 * \param[in] AbortSourceMask: which abort source
 * \return: bool
 *          true: abort detected
 *          false: abort not detected
 */
__attribute__((always_inline)) static inline bool I2cReg_GetTxAbortInfo(const I2cRegType *obj, uint32_t abortSourceMask)
{
    uint32_t tAbortSource = 0;
    bool     tRtn         = false;

    tAbortSource = obj->TX_ABRT_SOURCE;

    if((tAbortSource & abortSourceMask) != 0u)
    {
        tRtn = true;
    }

    return tRtn;
}

/*! \brief flush count in TX FIFO
 *
 * This field indicates the number of Tx FIFO Data Commands which are flushed due to TX_ABRT interrupt. It is cleared whenever I2C is disabled.
 *
 * \param[in] obj: base address for the i2cinstance
 * \return: the number of Tx FIFO Data Commands which are flushed
 */
__attribute__((always_inline)) static inline uint8_t I2cReg_GetTxFlushCounter(const I2cRegType *obj)
{
    uint8_t tTxFlushCounter = 0;

    tTxFlushCounter = (((obj->TX_ABRT_SOURCE & I2C_TX_ABRT_SOURCE_TX_FLUSH_CNT_MASK) >> I2C_TX_ABRT_SOURCE_TX_FLUSH_CNT_SHIFT) & 0xFF);

    return tTxFlushCounter;
}

/*! \brief This bit enables/disables the transmit FIFO DMA channel.
 *
 * this function enable or disable the tx with dma features
 *
 * \param[in] obj: base address for the i2cinstance
 * \param[in] en:
 *            false: Dma tx disabled
 *            true: Dma tx enabled
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_SetTxDmaEnable(I2cRegType *obj, bool en)
{
    uint32_t tRegValue = obj->DMA_CR;

    if(en == true)
    {
        obj->DMA_CR = ((1ul << I2C_DMA_CR_TDMAE_SHIFT) | ((~I2C_DMA_CR_TDMAE_MASK) & tRegValue));
    }
    else
    {
        obj->DMA_CR = ((0ul << I2C_DMA_CR_TDMAE_SHIFT) | ((~I2C_DMA_CR_TDMAE_MASK) & tRegValue));
    }
}

/*! \brief Get enables/disables the transmit FIFO DMA channel.
 *
 * this function get the current tx mode is used with dma
 *
 * \param[in] obj: base address for the i2cinstance
 * \return: bool
 */
__attribute__((always_inline)) static inline bool I2cReg_GetDmaTxIsEnabled(const I2cRegType *obj)
{
    bool tRtn = false;

    if((obj->DMA_CR & I2C_DMA_CR_TDMAE_MASK) != 0u)
    {
        tRtn = true;
    }

    return tRtn;
}

/*! \brief This bit enables/disables the receiver FIFO DMA channel.
 *
 * this function enable or disable the rx with dma features
 *
 * \param[in] obj: base address for the i2cinstance
 * \param[in] en:
 *            false: Dma rx disabled
 *            true: Dma rx enabled
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_SetRxDmaEnable(I2cRegType *obj, bool en)
{
    uint32_t tRegValue = obj->DMA_CR;

    if(en == true)
    {
        obj->DMA_CR = ((1ul << I2C_DMA_CR_RDMAE_SHIFT) | ((~I2C_DMA_CR_RDMAE_MASK) & tRegValue));
    }
    else
    {
        obj->DMA_CR = ((0ul << I2C_DMA_CR_RDMAE_SHIFT) | ((~I2C_DMA_CR_RDMAE_MASK) & tRegValue));
    }
}

/*! \brief Get enables/disables the transmit FIFO DMA channel.
 *
 * this function get the current rx mode is used with dma
 *
 * \param[in] obj: base address for the i2cinstance
 * \return: bool
 *          false: Dma rx disabled
 *          true: Dma rx enabled
 */
__attribute__((always_inline)) static inline bool I2cReg_GetDmaRxIsEnabled(const I2cRegType *obj)
{
    bool tRtn = false;

    if((obj->DMA_CR & I2C_DMA_CR_RDMAE_MASK) != 0u)
    {
        tRtn = true;
    }

    return tRtn;
}

/*! \brief controls the level at which a DMA request is made by the transmit logic
 *
 * It is equal to the watermark level; that is, the dma_tx_req signal is generated when the number of valid data entries in the transmit FIFO is equal to
 *       or below this field value, and TDMAE = 1
 *
 * \param[in] obj: base address for the i2cinstance
 * \param[in] txLevel: the watermark level
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_SetDmaTxLevel(I2cRegType *obj, uint8_t txLevel)
{
    uint32_t tRegValue = obj->DMA_TDLR;

    obj->DMA_TDLR = (((uint32_t)txLevel << I2C_DMA_TDLR_DMATDL_SHIFT) | ((~I2C_DMA_TDLR_DMATDL_MASK) & tRegValue));
}

/*! \brief controls the level at which a DMA request is made by the receive logic
 *
 * The watermark level = DMARDL+1; that is, dma_rx_req is generated when the number of valid data entries in the receive FIFO is equal
 *       to or more than this field value + 1, and RDMAE =1.
 *
 * \param[in] obj: base address for the i2cinstance
 * \param[in] rxLevel: The rx watermark level
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_SetDmaRxLevel(I2cRegType *obj, uint8_t rxLevel)
{
    uint32_t tRegValue = obj->DMA_RDLR;

    obj->DMA_RDLR = (((uint32_t)rxLevel << I2C_DMA_RDLR_DMARDL_SHIFT) | ((~I2C_DMA_RDLR_DMARDL_MASK) & tRegValue));
}

/*! \brief SDA setup
 *
 * It is recommended that if the required delay is
 *       1000ns, then for an I2C_clk frequency of 10 MHz,I2C_SDA_SETUP should be programmed to a value of 11. I2C_SDA_SETUP >=2
 *
 * \param[in] obj: base address for the i2cinstance
 * \param[in] SetUpTime: SDA setup
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_SetDataSetUpTime(I2cRegType *obj, uint8_t setUpTime)
{
    uint32_t tRegValue = obj->SDA_SETUP;

    obj->SDA_SETUP = (((uint32_t)setUpTime << I2C_SDA_SETUP_SDA_SETUP_SHIFT) | ((~I2C_SDA_SETUP_SDA_SETUP_MASK) & tRegValue));
}

/*! \brief Set ack for General Call
 *
 * this function configure the ack for the general call cmd
 *
 * \param[in] obj: base address for the i2cinstance
 * \param[in] ackEn:
 *            false: Disable ack for general call
 *            true: Enable ack for general call
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_SetAckForGeneralCall(I2cRegType *obj, bool ackEn)
{
    uint32_t tRegValue = obj->ACK_GCALL;

    if(ackEn == true)
    {
        obj->ACK_GCALL = ((1ul << I2C_ACK_GCALL_ACK_GEN_CALL_SHIFT) | ((~I2C_ACK_GCALL_ACK_GEN_CALL_MASK) & tRegValue));
    }
    else
    {
        obj->ACK_GCALL = ((0ul << I2C_ACK_GCALL_ACK_GEN_CALL_SHIFT) | ((~I2C_ACK_GCALL_ACK_GEN_CALL_MASK) & tRegValue));
    }
}

/*! \brief Get slave rx data lost
 *
 * this function get the status if rx data is lost before
 *
 * \param[in] obj: base address for the i2cinstance
 * \return: bool
 *          false: Slave RX data is not lost
 *          true:  Slave RX data is lost
 */
__attribute__((always_inline)) static inline bool I2cReg_GetSlaveRxDataLostStatus(const I2cRegType *obj)
{
    bool tRtn = false;

    if((obj->ENABLE_STATUS & I2C_ENABLE_STATUS_SLV_RX_DATA_LOST_MASK) != 0u)
    {
        tRtn = true;
    }

    return tRtn;
}

/*! \brief Get whether slave is disabled when active
 *
 * this function get the status if slave is disable but in busy status
 *
 * \param[in] obj: base address for the i2cinstance
 * \return: bool
 *          false: slave is disabled when it is idle
 *          true:  slave is disabled when it is active
 */
__attribute__((always_inline)) static inline bool I2cReg_GetSlaveDisabledWhileBusyStatus(const I2cRegType *obj)
{
    bool tRtn = false;

    if((obj->ENABLE_STATUS & I2C_ENABLE_STATUS_SLV_DISABLED_WHILE_BUSY_MASK) != 0u)
    {
        tRtn = true;
    }

    return tRtn;
}

/*! \brief Get module enable status
 *
 * this function get the current status about module
 *
 * \param[in] obj: base address for the i2cinstance
 * \return: bool
 *          false: disabled
 *          true:  enabled
 */
__attribute__((always_inline)) static inline bool I2cReg_GetModuleEnableStatus(const I2cRegType *obj)
{
    bool tRtn = false;

    if((obj->ENABLE_STATUS & I2C_ENABLE_STATUS_EN_MASK) != 0u)
    {
        tRtn = true;
    }

    return tRtn;
}

/*! \brief sets the duration about spike length
 *
 * ,measured in I2C_clk cycles, of the longest spike in the SCL or SDA lines that will be filtered out by the spike suppression logic
 *
 * \param[in] obj: base address for the i2cinstance
 * \param[in] SpikeLen: the duration about spike length
 * \return: void
 */
__attribute__((always_inline)) static inline void I2cReg_SetSpikeLen(I2cRegType *obj, uint8_t spikeLen)
{
    uint32_t tRegValue = obj->SPKLEN;

    obj->SPKLEN = (((uint32_t)spikeLen << I2C_SPKLEN_LEN_SHIFT) | ((~I2C_SPKLEN_LEN_MASK) & tRegValue));
}

/*! \brief Gets the duration,measured in I2C_clk cycles
 *
 * this function get the spike length ticks
 *
 * \param[in] obj: base address for the i2cinstance
 * \return: the duration,measured in I2C_clk cycles
 */
__attribute__((always_inline)) static inline uint8_t I2cReg_GetSpikeLen(const I2cRegType *obj)
{
    uint8_t tRtn = 0;

    tRtn = (((obj->SPKLEN & I2C_SPKLEN_LEN_MASK) >> I2C_SPKLEN_LEN_SHIFT) & 0xFF);

    return tRtn;
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _I2C_REG_H_ */
