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

#ifndef _EIM_REG_H_
#define _EIM_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the EIM Registers
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

/* Error Value */
#define EIM_RES_ERR_8B                 (0xFFu)
#define EIM_RES_ERR_11B                (0x3FFu)
#define EIM_RES_ERR_32B                (0xFFFFFFFFu)

/* Size of Reserved Registers Arrays */
#define EIM_REG_EICHEN_RESEERVED_CONUT (0x3E)
#define EIM_REG_SRAML_RESEERVED_CONUT  (0xD)
#define EIM_REG_SRAMU_RESEERVED_CONUT  (0xD)
#define EIM_REG_WAY0_RESEERVED_CONUT   (0xC)

/* CR Bit Fields */
#define EIM_CR_GEIEN_MASK              (0x1u)
#define EIM_CR_GEIEN_SHIFT             (0u)
#define EIM_CR_GEIEN_WIDTH             (1u)

/* CHEN Bit Fields */
#define EIM_CHEN_MASK                  (0xFu)
#define EIM_CHEN_SHIFT                 (0u)
#define EIM_CHEN_WIDTH                 (4u)

/* CH0 CHK Bit Fields */
#define EIM_CH0_CHK_MASK               (0xFF000000u)
#define EIM_CH0_CHK_SHIFT              (24u)
#define EIM_CH0_CHK_WIDTH              (8u)

/* CH0 DATA Bit Fields */
#define EIM_CH0_DATA_MASK              (0xFFFFFFFFu)
#define EIM_CH0_DATA_SHIFT             (0u)
#define EIM_CH0_DATA_WIDTH             (32u)

/* CH0 ADDR Bit Fields */
#define EIM_CH0_ADDR_MASK              (0xFFFFFFFFu)
#define EIM_CH0_ADDR_SHIFT             (0u)
#define EIM_CH0_ADDR_WIDTH             (32u)

/* CH1 CHK Bit Fields */
#define EIM_CH1_CHK_MASK               (0xFF000000u)
#define EIM_CH1_CHK_SHIFT              (24u)
#define EIM_CH1_CHK_WIDTH              (8u)

/* CH1 DATA Bit Fields */
#define EIM_CH1_DATA_MASK              (0xFFFFFFFFu)
#define EIM_CH1_DATA_SHIFT             (0u)
#define EIM_CH1_DATA_WIDTH             (32u)

/* CH1 ADDR Bit Fields */
#define EIM_CH1_ADDR_MASK              (0xFFFFFFFFu)
#define EIM_CH1_ADDR_SHIFT             (0u)
#define EIM_CH1_ADDR_WIDTH             (32u)

/* CH2 DATA0 Bit Fields */
#define EIM_CH1_ADDR_MASK              (0xFFFFFFFFu)
#define EIM_CH1_ADDR_SHIFT             (0u)
#define EIM_CH1_ADDR_WIDTH             (32u)

/* CH2 CHK Bit Fields */
#define EIM_CH2_CHK_MASK               (0xFF000000u)
#define EIM_CH2_CHK_SHIFT              (24u)
#define EIM_CH2_CHK_WIDTH              (8u)

/* CH2 DATA0 Bit Fields */
#define EIM_CH2_DATA0_MASK             (0xFFFFFFFFu)
#define EIM_CH2_DATA0_SHIFT            (0u)
#define EIM_CH2_DATA0_WIDTH            (32u)

/* CH2 DATA1 Bit Fields */
#define EIM_CH2_DATA1_MASK             (0xFFFFFFFFu)
#define EIM_CH2_DATA1_SHIFT            (0u)
#define EIM_CH2_DATA1_WIDTH            (32u)

/* CH2 DATA2 Bit Fields */
#define EIM_CH2_DATA2_MASK             (0x3FFu)
#define EIM_CH2_DATA2_SHIFT            (0u)
#define EIM_CH2_DATA2_WIDTH            (11u)

/* CH3 CHK Bit Fields */
#define EIM_CH3_CHK_MASK               (0xFF000000u)
#define EIM_CH3_CHK_SHIFT              (24u)
#define EIM_CH3_CHK_WIDTH              (8u)

/* CH3 DATA0 Bit Fields */
#define EIM_CH3_DATA0_MASK             (0xFFFFFFFFu)
#define EIM_CH3_DATA0_SHIFT            (0u)
#define EIM_CH3_DATA0_WIDTH            (32u)

/* CH3 DATA1 Bit Fields */
#define EIM_CH3_DATA1_MASK             (0xFFFFFFFFu)
#define EIM_CH3_DATA1_SHIFT            (0u)
#define EIM_CH3_DATA1_WIDTH            (32u)

/* CH3 DATA2 Bit Fields */
#define EIM_CH3_DATA2_MASK             (0x3FFu)
#define EIM_CH3_DATA2_SHIFT            (0u)
#define EIM_CH3_DATA2_WIDTH            (11u)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief The definition of EIM registers
 */
typedef struct _EimRegType_
{
    volatile uint32_t CR;   /*!< Control, Error in Control Register, offset: 0x0 */
    volatile uint32_t CHEN; /*!< Control, Error in channel enable Register, offset: 0x4 */
    uint32_t          RESERVED_0[EIM_REG_EICHEN_RESEERVED_CONUT];
    struct
    {                           /* offset: 0x100, array step: 0x0C        */
        volatile uint32_t CHK;  /*!< ECC Register Address, offset: 0x100  */
        volatile uint32_t DATA; /*!< Data Register Address, offset: 0x104 */
        volatile uint32_t ADDR; /*!< Addr Register Address, offset: 0x108 */
    } SRAML;
    uint32_t RESERVED_1[EIM_REG_SRAML_RESEERVED_CONUT];
    struct
    {                           /* offset: 0x140, array step: 0x0C        */
        volatile uint32_t CHK;  /*!< ECC Register Address, offset: 0x140  */
        volatile uint32_t DATA; /*!< Data Register Address, offset: 0x144 */
        volatile uint32_t ADDR; /*!< Addr Register Address, offset: 0x148 */
    } SRAMU;
    uint32_t RESERVED_2[EIM_REG_SRAMU_RESEERVED_CONUT];
    struct
    {                            /* offset: 0x180, array step: 0x0F         */
        volatile uint32_t CHK;   /*!< ECC Register Address, offset: 0x180   */
        volatile uint32_t DATA0; /*!< Data0 Register Address, offset: 0x184 */
        volatile uint32_t DATA1; /*!< Data1 Register Address, offset: 0x188 */
        volatile uint32_t DATA2; /*!< Data2 Register Address, offset: 0x188 */
    } CACHE_WAY0;
    uint32_t RESERVED_3[EIM_REG_WAY0_RESEERVED_CONUT];
    struct
    {                            /* offset: 0x1C0, array step: 0x0F         */
        volatile uint32_t CHK;   /*!< ECC Register Address, offset: 0x1C0   */
        volatile uint32_t DATA0; /*!< Data0 Register Address, offset: 0x1C4 */
        volatile uint32_t DATA1; /*!< Data1 Register Address, offset: 0x1C8 */
        volatile uint32_t DATA2; /*!< Data2 Register Address, offset: 0x1CC */
    } CACHE_WAY1;
} EimRegType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Enables the EIM module.
 *
 * This function enables the functional of EIM module
 *
 * \param[in] obj : pointer to EIM register instance
 * \param[in] enable State
 *             - 1  : Enable the EIM module.
 *             - 0  : Disable the EIM module.
 * \return None
 */
__attribute__((always_inline)) static inline void EimReg_Enable(EimRegType *obj, uint8_t enable)
{
    uint32_t tmp = obj->CR;

    tmp &= ~EIM_CR_GEIEN_MASK;
    tmp |= (((uint32_t)(enable ? 1 << EIM_CR_GEIEN_SHIFT : 0 << EIM_CR_GEIEN_SHIFT)) & EIM_CR_GEIEN_MASK);
    obj->CR = tmp;
}

/*! \brief Enables the EIM module.
 *
 * This function enables the functional of EIM module
 *
 * \param[in] obj : pointer to EIM register instance
 * \return The Status of EIM Global control Register
 *             - 1  : Enable the EIM module.
 *             - 0  : Disable the EIM module.
 */
__attribute__((always_inline)) static inline uint8_t EimReg_GetGlobalStatus(const EimRegType *obj)
{
    return (uint8_t)((obj->CR & EIM_CR_GEIEN_MASK) >> EIM_CR_GEIEN_SHIFT);
}

/*! \brief Set EIM Error in channel enable.
 *
 * This function set EIM error in channel enable functional
 *
 * \param[in] obj : pointer to EIM register instance
 * \param[in] eimChn : Error in channel num
 *             - 0 : channel0
 *             - 1 : channel1
 *             - 2 : channel2
 *             - 3 : channel3
 * \param[in] enable State
 *             - 1  : Enable the EIM module.
 *             - 0  : Disable the EIM module.
 * \return None
 */
__attribute__((always_inline)) static inline void EimReg_SetChnEnable(EimRegType *obj, uint8_t ChnNum)
{
    uint32_t tmp = obj->CHEN;

    tmp &= ~EIM_CHEN_MASK;
    tmp |= (uint32_t)(ChnNum << EIM_CHEN_SHIFT);
    obj->CHEN = tmp;
}

/*! \brief Get EIM Error in channel enable.
 *
 * This function get EIM error in channel status
 *
 * \param[in] obj : pointer to EIM register instance
 * \param[in] eimChn : Error in channel num
 * \return Status of Error in channel
 *             - 1  : Enable the EIM module.
 *             - 0  : Disable the EIM module.
 */
__attribute__((always_inline)) static inline uint8_t EimReg_GetChnEnable(const EimRegType *obj)
{
    return (uint8_t)((obj->CHEN & EIM_CHEN_MASK) >> EIM_CHEN_SHIFT);
}

/*! \brief Set SRAM ECC Check.
 *
 * This function set SRAM ecc check
 *
 * \param[in] obj : pointer to EIM register instance
 * \param[in] eimChn : Error in channel num
 *             - 0 : Channel SRAML
 *             - 1 : Channel SRAMU
 * \param[in] chk : ECC for read data from RAM
 * \return None
 */
__attribute__((always_inline)) static inline void EimReg_SetSramEccCHK(EimRegType *obj, uint8_t eimChnNum, uint8_t chk)
{
    uint32_t tmp;

    switch(eimChnNum)
    {
    case 0: /* ECC SRAML ErrIn CHK */
        tmp = obj->SRAML.CHK;
        tmp &= ~EIM_CH0_CHK_MASK;
        tmp |= (((uint32_t)((uint32_t)chk << EIM_CH0_CHK_SHIFT)) & EIM_CH0_CHK_MASK);
        obj->SRAML.CHK = tmp;
        break;
    case 1: /* ECC SRAMU ErrIn CHK */
        tmp = obj->SRAMU.CHK;
        tmp &= ~EIM_CH1_CHK_MASK;
        tmp |= (((uint32_t)((uint32_t)chk << EIM_CH1_CHK_SHIFT)) & EIM_CH1_CHK_MASK);
        obj->SRAMU.CHK = tmp;
        break;
    default:
        break;
    }
}

/*! \brief Get SRAM ECC Check.
 *
 * This function get SRAM ecc check
 *
 * \param[in] obj : pointer to EIM register instance
 * \param[in] eimChn : Error in channel num
 *             - 0 : Channel SRAML
 *             - 1 : Channel SRAMU
 * \return
 *          ECC for read data from RAM
 */
__attribute__((always_inline)) static inline uint8_t EimReg_GetSramEccCHK(const EimRegType *obj, uint8_t eimChnNum)
{
    switch(eimChnNum)
    {
    case 0: /* ECC SRAML ErrIn CHK */
        return (uint8_t)((obj->SRAML.CHK & EIM_CH0_CHK_MASK) >> EIM_CH0_CHK_SHIFT);
    case 1: /* ECC SRAMU ErrIn CHK */
        return (uint8_t)((obj->SRAMU.CHK & EIM_CH1_CHK_MASK) >> EIM_CH1_CHK_SHIFT);
    default:
        return EIM_RES_ERR_8B;
    }
}

/*! \brief Set SRAM ERRIN Data.
 *
 * This function set SRAM error in data
 *
 * \param[in] obj : pointer to EIM register instance
 * \param[in] eimChn : Error in channel num
 *             - 0 : Channel SRAML
 *             - 1 : Channel SRAMU
 * \param[in] data : read data from RAM
 * \return None
 */
__attribute__((always_inline)) static inline void EimReg_SetSramEccData(EimRegType *obj, uint8_t eimChnNum, uint32_t data)
{
    uint32_t tmp;

    switch(eimChnNum)
    {
    case 0: /* ECC SRAML ErrIn Data */
        tmp = obj->SRAML.DATA;
        tmp &= ~EIM_CH0_DATA_MASK;
        tmp |= (((uint32_t)((uint32_t)data << EIM_CH0_DATA_SHIFT)) & EIM_CH0_DATA_MASK);
        obj->SRAML.DATA = tmp;
        break;
    case 1: /* ECC SRAMU ErrIn Data */
        tmp = obj->SRAMU.DATA;
        tmp &= ~EIM_CH1_DATA_MASK;
        tmp |= (((uint32_t)((uint32_t)data << EIM_CH1_DATA_SHIFT)) & EIM_CH1_DATA_MASK);
        obj->SRAMU.DATA = tmp;
        break;
    default:
        break;
    }
}

/*! \brief Get SRAM ERRIN Data.
 *
 * This function get SRAM error in data
 *
 * \param[in] obj : pointer to EIM register instance
 * \param[in] eimChn : Error in channel num
 *             - 0 : Channel SRAML
 *             - 1 : Channel SRAMU
 * \return
 *          read data from RAM
 */
__attribute__((always_inline)) static inline uint32_t EimReg_GetSramEccData(const EimRegType *obj, uint8_t eimChnNum)
{
    switch(eimChnNum)
    {
    case 0: /* ECC SRAML ErrIn Data */
        return ((obj->SRAML.DATA & EIM_CH0_DATA_MASK) >> EIM_CH0_DATA_SHIFT);
    case 1: /* ECC SRAMU ErrIn Data */
        return ((obj->SRAMU.DATA & EIM_CH1_DATA_MASK) >> EIM_CH1_DATA_SHIFT);
    default:
        return EIM_RES_ERR_32B;
    }
}

/*! \brief Set SRAM ERRIN Addr.
 *
 * This function set SRAM error in addr
 *
 * \param[in] obj : pointer to EIM register instance
 * \param[in] eimChn : Error in channel num
 *             - 0 : Channel SRAML
 *             - 1 : Channel SRAMU
 * \param[in] addr : read addr from RAM
 * \return None
 */
__attribute__((always_inline)) static inline void EimReg_SetSramEccAddr(EimRegType *obj, uint8_t eimChnNum, uint32_t addr)
{
    uint32_t tmp;

    switch(eimChnNum)
    {
    case 0: /* ECC SRAML ErrIn Addr */
        tmp = obj->SRAML.ADDR;
        tmp &= ~EIM_CH0_ADDR_MASK;
        tmp |= (((uint32_t)((uint32_t)addr << EIM_CH0_ADDR_SHIFT)) & EIM_CH0_ADDR_MASK);
        obj->SRAML.ADDR = tmp;
        break;
    case 1: /* ECC SRAMU ErrIn Addr */
        tmp = obj->SRAMU.ADDR;
        tmp &= ~EIM_CH1_ADDR_MASK;
        tmp |= (((uint32_t)((uint32_t)addr << EIM_CH1_ADDR_SHIFT)) & EIM_CH1_ADDR_MASK);
        obj->SRAMU.ADDR = tmp;
        break;
    default:
        break;
    }
}

/*! \brief Get SRAM ERRIN addr.
 *
 * This function get SRAM error in addr
 *
 * \param[in] obj : pointer to EIM register instance
 * \param[in] eimChn : Error in channel num
 *             - 0 : Channel SRAML
 *             - 1 : Channel SRAMU
 * \return
 *          read addr from RAM
 */
__attribute__((always_inline)) static inline uint32_t EimReg_GetSramEccAddr(const EimRegType *obj, uint8_t eimChnNum)
{
    switch(eimChnNum)
    {
    case 0: /* ECC SRAML ErrIn Addr */
        return ((obj->SRAML.ADDR & EIM_CH0_ADDR_MASK) >> EIM_CH0_ADDR_SHIFT);
    case 1: /* ECC SRAMU ErrIn Addr */
        return ((obj->SRAMU.ADDR & EIM_CH1_ADDR_MASK) >> EIM_CH1_ADDR_SHIFT);
    default:
        return EIM_RES_ERR_32B;
    }
}

/*! \brief Set CACHE ECC Check.
 *
 * This function set CACHE ecc check
 *
 * \param[in] obj : pointer to EIM register instance
 * \param[in] eimChn : Error in channel num
 *             - 0 : Channel CACHE way0
 *             - 1 : Channel CACHE way1
 * \param[in] chk : ECC for read data from CACHE
 * \return None
 */
__attribute__((always_inline)) static inline void EimReg_SetCacheEccCHK(EimRegType *obj, uint8_t eimChnNum, uint8_t chk)
{
    uint32_t tmp;

    switch(eimChnNum)
    {
    case 0: /* ECC CACHE way0 ErrIn CHK */
        tmp = obj->CACHE_WAY0.CHK;
        tmp &= ~EIM_CH2_CHK_MASK;
        tmp |= (((uint32_t)((uint32_t)chk << EIM_CH2_CHK_SHIFT)) & EIM_CH2_CHK_MASK);
        obj->CACHE_WAY0.CHK = tmp;
        break;
    case 1: /* ECC CACHE way1 ErrIn CHK */
        tmp = obj->CACHE_WAY1.CHK;
        tmp &= ~EIM_CH3_CHK_MASK;
        tmp |= (((uint32_t)((uint32_t)chk << EIM_CH3_CHK_SHIFT)) & EIM_CH3_CHK_MASK);
        obj->CACHE_WAY1.CHK = tmp;
        break;
    default:
        break;
    }
}

/*! \brief Get CACHE ECC Check.
 *
 * This function get CACHE ecc check
 *
 * \param[in] obj : pointer to EIM register instance
 * \param[in] eimChn : Error in channel num
 *             - 0 : Channel CACHE way0
 *             - 1 : Channel CACHE way1
 * \return
 *          ECC for read data from CACHE
 */
__attribute__((always_inline)) static inline uint8_t EimReg_GetCacheEccCHK(const EimRegType *obj, uint8_t eimChnNum)
{
    switch(eimChnNum)
    {
    case 0: /* ECC CACHE way0 ErrIn CHK */
        return (uint8_t)((obj->CACHE_WAY0.CHK & EIM_CH2_CHK_MASK) >> EIM_CH2_CHK_SHIFT);
    case 1: /* ECC CACHE way1 ErrIn CHK */
        return (uint8_t)((obj->CACHE_WAY1.CHK & EIM_CH3_CHK_MASK) >> EIM_CH3_CHK_SHIFT);
    default:
        return EIM_RES_ERR_8B;
    }
}

/*! \brief Set CACHE ERRIN Data0.
 *
 * This function set CACHE error in data0
 *
 * \param[in] obj : pointer to EIM register instance
 * \param[in] eimChn : Error in channel num
 *             - 0 : Channel CACHE way0
 *             - 1 : Channel CACHE way1
 * \param[in] data : read data from CACHE
 * \return None
 */
__attribute__((always_inline)) static inline void EimReg_SetCacheEccData0(EimRegType *obj, uint8_t eimChnNum, uint32_t data)
{
    uint32_t tmp;

    switch(eimChnNum)
    {
    case 0: /* ECC CACHE way0 ErrIn Data */
        tmp = obj->CACHE_WAY0.DATA0;
        tmp &= ~EIM_CH2_DATA0_MASK;
        tmp |= (((uint32_t)((uint32_t)data << EIM_CH2_DATA0_SHIFT)) & EIM_CH2_DATA0_MASK);
        obj->CACHE_WAY0.DATA0 = tmp;
        break;
    case 1: /* ECC CACHE way1 ErrIn Data */
        tmp = obj->CACHE_WAY1.DATA0;
        tmp &= ~EIM_CH3_DATA1_MASK;
        tmp |= (((uint32_t)((uint32_t)data << EIM_CH3_DATA1_SHIFT)) & EIM_CH3_DATA1_MASK);
        obj->CACHE_WAY1.DATA0 = tmp;
        break;
    default:
        break;
    }
}

/*! \brief Get CACHE ERRIN Data0.
 *
 * This function get CACHE error in data0
 *
 * \param[in] obj : pointer to EIM register instance
 * \param[in] eimChn : Error in channel num
 *             - 0 : Channel CACHE way0
 *             - 1 : Channel CACHE way1
 * \return
 *          read data from CACHE
 */
__attribute__((always_inline)) static inline uint32_t EimReg_GetCacheEccData0(const EimRegType *obj, uint8_t eimChnNum)
{
    switch(eimChnNum)
    {
    case 0: /* ECC CACHE way0 ErrIn Data */
        return ((obj->CACHE_WAY0.DATA0 & EIM_CH2_DATA0_MASK) >> EIM_CH2_DATA0_SHIFT);
    case 1: /* ECC CACHE way1 ErrIn Data */
        return ((obj->CACHE_WAY1.DATA1 & EIM_CH3_DATA1_MASK) >> EIM_CH3_DATA1_SHIFT);
    default:
        return EIM_RES_ERR_32B;
    }
}

/*! \brief Set CACHE ERRIN Data1.
 *
 * This function set CACHE error in data1
 *
 * \param[in] obj : pointer to EIM register instance
 * \param[in] eimChn : Error in channel num
 *             - 0 : Channel CACHE way0
 *             - 1 : Channel CACHE way1
 * \param[in] addr : read addr from CACHE
 * \return None
 */
__attribute__((always_inline)) static inline void EimReg_SetCacheEccData1(EimRegType *obj, uint8_t eimChnNum, uint32_t addr)
{
    uint32_t tmp;

    switch(eimChnNum)
    {
    case 0: /* ECC CACHE way0 ErrIn Addr */
        tmp = obj->CACHE_WAY0.DATA1;
        tmp &= ~EIM_CH2_DATA1_MASK;
        tmp |= (((uint32_t)((uint32_t)addr << EIM_CH2_DATA1_SHIFT)) & EIM_CH2_DATA1_MASK);
        obj->CACHE_WAY0.DATA1 = tmp;
        break;
    case 1: /* ECC CACHE way1 ErrIn Addr */
        tmp = obj->CACHE_WAY1.DATA1;
        tmp &= ~EIM_CH3_DATA1_MASK;
        tmp |= (((uint32_t)((uint32_t)addr << EIM_CH3_DATA1_SHIFT)) & EIM_CH3_DATA1_MASK);
        obj->CACHE_WAY1.DATA1 = tmp;
        break;
    default:
        break;
    }
}

/*! \brief Get CACHE ERRIN Data1.
 *
 * This function get CACHE error in data1
 *
 * \param[in] obj : pointer to EIM register instance
 * \param[in] eimChn : Error in channel num
 *             - 0 : Channel CACHE way0
 *             - 1 : Channel CACHE way1
 * \return
 *          read addr from CACHE
 */
__attribute__((always_inline)) static inline uint32_t EimReg_GetCacheEccData1(const EimRegType *obj, uint8_t eimChnNum)
{
    switch(eimChnNum)
    {
    case 0: /* ECC CACHE way0 ErrIn Addr */
        return ((obj->CACHE_WAY0.DATA1 & EIM_CH2_DATA1_MASK) >> EIM_CH2_DATA1_SHIFT);
    case 1: /* ECC CACHE way0 ErrIn Addr */
        return ((obj->CACHE_WAY1.DATA1 & EIM_CH3_DATA1_MASK) >> EIM_CH3_DATA1_SHIFT);
    default:
        return EIM_RES_ERR_32B;
    }
}

/*! \brief Set CACHE ERRIN Data2.
 *
 * This function set CACHE error in data2
 *
 * \param[in] obj : pointer to EIM register instance
 * \param[in] eimChn : Error in channel num
 *             - 0 : Channel CACHE way0
 *             - 1 : Channel CACHE way1
 * \param[in] addr : read addr from CACHE
 * \return None
 */
__attribute__((always_inline)) static inline void EimReg_SetCacheEccData2(EimRegType *obj, uint8_t eimChnNum, uint32_t data)
{
    uint32_t tmp;

    switch(eimChnNum)
    {
    case 0: /* ECC CACHE way0 ErrIn Addr */
        tmp = obj->CACHE_WAY0.DATA2;
        tmp &= ~EIM_CH2_DATA2_MASK;
        tmp |= (((uint32_t)((uint32_t)data << EIM_CH2_DATA2_SHIFT)) & EIM_CH2_DATA2_MASK);
        obj->CACHE_WAY0.DATA2 = tmp;
        break;
    case 1: /* ECC CACHE way1 ErrIn Addr */
        tmp = obj->CACHE_WAY1.DATA2;
        tmp &= ~EIM_CH3_DATA2_MASK;
        tmp |= (((uint32_t)((uint32_t)data << EIM_CH3_DATA2_SHIFT)) & EIM_CH3_DATA2_MASK);
        obj->CACHE_WAY1.DATA2 = tmp;
        break;
    default:
        break;
    }
}

/*! \brief Get CACHE ERRIN Data2.
 *
 * This function get CACHE error in data2
 *
 * \param[in] obj : pointer to EIM register instance
 * \param[in] eimChn : Error in channel num
 *             - 0 : Channel CACHE way0
 *             - 1 : Channel CACHE way1
 * \return
 *          read addr from CACHE
 */
__attribute__((always_inline)) static inline uint32_t EimReg_GetCacheEccData2(const EimRegType *obj, uint8_t eimChnNum)
{
    switch(eimChnNum)
    {
    case 0: /* ECC CACHE way0 ErrIn Addr */
        return ((obj->CACHE_WAY0.DATA2 & EIM_CH2_DATA2_MASK) >> EIM_CH2_DATA2_SHIFT);
    case 1: /* ECC CACHE way1 ErrIn Addr */
        return ((obj->CACHE_WAY1.DATA2 & EIM_CH3_DATA2_MASK) >> EIM_CH3_DATA2_SHIFT);
    default:
        return EIM_RES_ERR_11B;
    }
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _EIM_REG_H_ */
