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

#ifndef _ERM_REG_H_
#define _ERM_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the ERM Registers
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

/* Size of Reserved Registers Arrays */
#define ERM_REG_CR0_RESEERVED_CONUT    (0x3)
#define ERM_REG_SR_RESEERVED_CONUT     (0x3B)
#define ERM_REG_CH3ST2_RESEERVED_CONUT (0x2)

/* Error Value */
#define ERM_RES_ERR_8B                 (0xFFu)
#define ERM_RES_ERR_32B                (0xFFFFFFFFu)

/* Size of ERM Registers Arrays */
#define ERM_CHN_COUNT                  (4)

/* ERM channel nun */
#define ERM_CH0                        (0)
#define ERM_CH1                        (1)
#define ERM_CH2                        (2)
#define ERM_CH3                        (3)

/* CR0 Bit Fields */
#define ERM_CR0_MASK                   (0x3FFu)
#define ERM_CR0_SHIFT                  (0u)
#define ERM_CR0_WIDTH                  (10u)

/* SR Bit Fields */
#define ERM_SR_NCE_MASK                (0x3FFu)
#define ERM_SR_NCE_SHIFT               (0u)
#define ERM_SR_NCE_WIDTH               (10u)

/* CHx(0~2) ST0 Bit Fields */
#define ERM_CHx_ST0_MASK               (0xFFFFFFFFu)
#define ERM_CHx_ST0_SHIFT              (0u)
#define ERM_CHx_ST0_WIDTH              (32u)

/* CHx(0~2) ST1 Bit Fields */
#define ERM_CHx_ST1_MASK               (0xFF000000u)
#define ERM_CHx_ST1_SHIFT              (24u)
#define ERM_CHx_ST1_WIDTH              (8u)

/* CHx(0~2) ST2 Bit Fields */
#define ERM_CHx_ST2_MASK               (0xFFu)
#define ERM_CHx_ST2_SHIFT              (0u)
#define ERM_CHx_ST2_WIDTH              (8u)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief The definition of ERM registers
 */
typedef struct _ErmRegType_
{
    volatile uint32_t CR0; /*!< Error report channel enable control register, offset: 0x0 */
    uint32_t          RESERVED0[ERM_REG_CR0_RESEERVED_CONUT];
    volatile uint32_t SR; /*!< Error report channel status register, offset: 0x10 */
    uint32_t          RESERVED1[ERM_REG_SR_RESEERVED_CONUT];
    struct /* offset: 0x100, array step: 0x0F */
    {
        const volatile uint32_t ST0; /*!< channel error addr register, array offset: 0x0, array step: 0x0F */
        const volatile uint32_t ST1; /*!< channel error position register, array offset: 0x4, array step: 0x0F */
        volatile uint32_t       ST2; /*!< channel error recover num register, array offset: 0x8, array step: 0x0F */
        uint32_t                RESERVED3;
    } STATUS[ERM_CHN_COUNT];
    uint32_t          RESERVED4[ERM_REG_CH3ST2_RESEERVED_CONUT];
    volatile uint32_t CH4_ST2; /*!< Error report channel4 recover num register, offset: 0x148 */
} ErmRegType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Set ERM channel enable.
 *
 * This function set error report channel enable functional
 *
 * \param[in] obj : pointer to ERM register instance
 * \param[in] chnStatus : error report channel
 *             - bit[0] : channle0 Single Bit Correction Interrupt Notification
 *             - bit[1] : channle0 Multi Bits Non-Correction Interrupt Notification
 *             - bit[2] : channle1 Single Bit Correction Interrupt Notification
 *             - bit[3] : channle1 Multi Bits Non-Correction Interrupt Notification
 *             - bit[4] : channle2 Single Bit Correction Interrupt Notification
 *             - bit[5] : channle2 Multi Bits Non-Correction Interrupt Notification
 *             - bit[6] : channle3 Single Bit Correction Interrupt Notification
 *             - bit[7] : channle3 Multi Bits Non-Correction Interrupt Notification
 *             - bit[8] : channle4 Single Bit Correction Interrupt Notification
 *             - bit[9] : channle4 Multi Bits Non-Correction Interrupt Notification
 * \return none
 */
__attribute__((always_inline)) static inline void ErmReg_SetChnEnable(ErmRegType *obj, uint16_t chnStatus)
{
    uint32_t tmp = obj->CR0;

    tmp &= ~ERM_CR0_MASK;
    tmp |= (((uint32_t)((uint32_t)chnStatus << ERM_CR0_SHIFT)) & ERM_CR0_MASK);
    obj->CR0 = tmp;
}

/*! \brief Get ERM channel enable status.
 *
 * This function get error report channel enable functional
 *
 * \param[in] obj : pointer to ERM register instance
 * \return  error report channel status
 *             - bit[0] : channle0 Single Bit Correction Interrupt Notification
 *             - bit[1] : channle0 Multi Bits Non-Correction Interrupt Notification
 *             - bit[2] : channle1 Single Bit Correction Interrupt Notification
 *             - bit[3] : channle1 Multi Bits Non-Correction Interrupt Notification
 *             - bit[4] : channle2 Single Bit Correction Interrupt Notification
 *             - bit[5] : channle2 Multi Bits Non-Correction Interrupt Notification
 *             - bit[6] : channle3 Single Bit Correction Interrupt Notification
 *             - bit[7] : channle3 Multi Bits Non-Correction Interrupt Notification
 *             - bit[8] : channle4 Single Bit Correction Interrupt Notification
 *             - bit[9] : channle4 Multi Bits Non-Correction Interrupt Notification
 */
__attribute__((always_inline)) static inline uint16_t ErmReg_GetChnEnable(const ErmRegType *obj)
{
    return (uint16_t)((obj->CR0 & ERM_CR0_MASK) >> ERM_CR0_SHIFT);
}

/*! \brief Get ERM channel ERR Info status.
 *
 * This function get error report channel error information status
 *
 * \param[in] obj : pointer to ERM register instance
 *
 * \return  error report current channel error status
 *             - bit[0] : channle0 Single Bit Correction Interrupt Notification
 *             - bit[1] : channle0 Multi Bits Non-Correction Interrupt Notification
 *             - bit[2] : channle1 Single Bit Correction Interrupt Notification
 *             - bit[3] : channle1 Multi Bits Non-Correction Interrupt Notification
 *             - bit[4] : channle2 Single Bit Correction Interrupt Notification
 *             - bit[5] : channle2 Multi Bits Non-Correction Interrupt Notification
 *             - bit[6] : channle3 Single Bit Correction Interrupt Notification
 *             - bit[7] : channle3 Multi Bits Non-Correction Interrupt Notification
 *             - bit[8] : channle4 Single Bit Correction Interrupt Notification
 *             - bit[9] : channle4 Multi Bits Non-Correction Interrupt Notification
 */
__attribute__((always_inline)) static inline uint16_t ErmReg_GetChnErrStatus(const ErmRegType *obj)
{
    return (uint16_t)((obj->SR & ERM_SR_NCE_MASK) >> ERM_SR_NCE_SHIFT);
}

/*! \brief Get ERM channel ERR Status Clear .
 *
 * This function clear error report channel error status
 *
 * \param[in] obj : pointer to ERM register instance
 * \param[in] chn : error report channel
 *             - 0 : channle0 Single Bit Correction Interrupt Notification
 *             - 1 : channle0 Multi Bits Non-Correction Interrupt Notification
 *             - 2 : channle1 Single Bit Correction Interrupt Notification
 *             - 3 : channle1 Multi Bits Non-Correction Interrupt Notification
 *             - 4 : channle2 Single Bit Correction Interrupt Notification
 *             - 5 : channle2 Multi Bits Non-Correction Interrupt Notification
 *             - 6 : channle3 Single Bit Correction Interrupt Notification
 *             - 7 : channle3 Multi Bits Non-Correction Interrupt Notification
 *             - 8 : channle4 Single Bit Correction Interrupt Notification
 *             - 9 : channle4 Multi Bits Non-Correction Interrupt Notification
 * \note : SR register bit write 1 for corresponding bit clear
 * \return  None
 */
__attribute__((always_inline)) static inline void ErmReg_ClrChnErrStatus(ErmRegType *obj, uint8_t chn)
{
    obj->SR |= (1 << chn);
}

/*! \brief Get ERM channel ERR Address .
 *
 * This function get error report channel error address
 *
 * \param[in] obj : pointer to ERM register instance
 * \param[in] chn : error report channel
 *             - 0 : error report channle0
 *             - 1 : error report channle1
 *             - 2 : error report channle2
 *             - 3 : error report channle3
 * \return  produced error address
 */
__attribute__((always_inline)) static inline uint32_t ErmReg_GetErrAddr(const ErmRegType *obj, uint8_t chn)
{
    return (uint32_t)((obj->STATUS[chn].ST0 & ERM_CHx_ST0_MASK) >> ERM_CHx_ST0_SHIFT);
}

/*! \brief Get ERM channel ERR Position .
 *
 * This function get error report channel error position
 *
 * \param[in] obj : pointer to ERM register instance
 * \param[in] chn : error report channel
 *             - 0 : error report channle0
 *             - 1 : error report channle1
 *             - 2 : error report channle2
 *             - 3 : error report channle3
 * \return  produced error position
 */
__attribute__((always_inline)) static inline uint8_t ErmReg_GetErrPos(const ErmRegType *obj, uint8_t chn)
{
    return (uint8_t)((obj->STATUS[chn].ST1 & ERM_CHx_ST1_MASK) >> ERM_CHx_ST1_SHIFT);
}

/*! \brief Get ERM channel ERR Number .
 *
 * This function get error report channel error number
 *
 * \param[in] obj : pointer to ERM register instance
 * \param[in] chn : error report channel
 *             - 0 : error report channle0
 *             - 1 : error report channle1
 *             - 2 : error report channle2
 *             - 3 : error report channle3
 * \return  produced error number
 */
__attribute__((always_inline)) static inline uint8_t ErmReg_GetErrNum(const ErmRegType *obj, uint8_t chn)
{
    return (uint8_t)((obj->STATUS[chn].ST2 & ERM_CHx_ST2_MASK) >> ERM_CHx_ST2_SHIFT);
}

/*! \brief Clear ERM channel ERR Number .
 *
 * This function clear error report channel error number
 *
 * \param[in] obj : pointer to ERM register instance
 * \param[in] chn : error report channel
 *             - 0 : error report channle0
 *             - 1 : error report channle1
 *             - 2 : error report channle2
 *             - 3 : error report channle3
 * \param[in] errNumClr : write 0 for corresponding bit clear, 8bit total
 * \return  none
 */
__attribute__((always_inline)) static inline void ErmReg_ClrErrNum(ErmRegType *obj, uint8_t chn, uint8_t errNumClr)
{
    obj->STATUS[chn].ST2 = (uint32_t)errNumClr << ERM_CHx_ST2_SHIFT;
}

/*! \brief Get ERM channel4 ERR Number .
 *
 * This function get error report channel4 error number
 *
 * \param[in] obj : pointer to ERM register instance
 * \return  produced error channel4 number
 */
__attribute__((always_inline)) static inline uint8_t ErmReg_GetErrChn4Num(const ErmRegType *obj)
{
    return (uint8_t)((obj->CH4_ST2 & ERM_CHx_ST2_MASK) >> ERM_CHx_ST2_SHIFT);
}

/*! \brief Clear ERM channel4 ERR Number .
 *
 * This function clear error report channel4 error number
 *
 * \param[in] obj : pointer to ERM register instance
 * \param[in] errNumClr : write 0 for corresponding bit clear, 8bit total
 * \return  none
 */
__attribute__((always_inline)) static inline void ErmReg_ClrErrChn4Num(ErmRegType *obj, uint8_t errNumClr)
{
    obj->CH4_ST2 = (uint32_t)errNumClr << ERM_CHx_ST2_SHIFT;
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _ERM_REG_H_ */
