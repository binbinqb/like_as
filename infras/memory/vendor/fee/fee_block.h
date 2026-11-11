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

#ifndef _FEE_BLOCK_H_
#define _FEE_BLOCK_H_

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "fee_extra.h"
#include "fee_types.h"

/*! \addtogroup Flash EEPROM Emulation
 *  @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * the defines
 ******************************************************************************/

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief Macro that defines the size of block info.
 */
#if(defined FEE_BLOCK_HEAD_INFO_SIZE)
#error FEE_BLOCK_HEAD_INFO_SIZE already defined
#endif
#define FEE_BLOCK_HEAD_INFO_SIZE (16)

/*! \brief Macro defining the calculated length of crc8 in block info.
 */
#if(defined FEE_BLOCK_CALC_HEAD_INFO_CRC8_LEN)
#error FEE_BLOCK_CALC_HEAD_INFO_CRC8_LEN already defined
#endif
#define FEE_BLOCK_CALC_HEAD_INFO_CRC8_LEN (12)

/*! \brief Macro that defines the start flag bit index in block info.
 */
#if(defined FEE_BLOCK_HEAD_INFO_START_INFO_IDX)
#error FEE_BLOCK_HEAD_INFO_START_INFO_IDX already defined
#endif
#define FEE_BLOCK_HEAD_INFO_START_INFO_IDX (0)

/*! \brief Macro that defines the index of number in block info.
 */
#if(defined FEE_BLOCK_HEAD_INFO_BLOCK_NUMBER_IDX)
#error FEE_BLOCK_HEAD_INFO_BLOCK_NUMBER_IDX already defined
#endif
#define FEE_BLOCK_HEAD_INFO_BLOCK_NUMBER_IDX (4)

/*! \brief Define the index representing the data address in block info.
 */
#if(defined FEE_BLOCK_HEAD_INFO_PHY_ADDR_IDX)
#error FEE_BLOCK_HEAD_INFO_PHY_ADDR_IDX already defined
#endif
#define FEE_BLOCK_HEAD_INFO_PHY_ADDR_IDX (8)

/*! \brief Define a macro in block info that represents the index of the crc8 result.
 */
#if(defined FEE_BLOCK_HEAD_INFO_CRC8_IDX)
#error FEE_BLOCK_HEAD_INFO_CRC8_IDX already defined
#endif
#define FEE_BLOCK_HEAD_INFO_CRC8_IDX (12)

/*! \brief Macro that defines the start flag bit in block info.
 */
#if(defined FEE_BLOCK_HEAD_INFO_START_INFO)
#error FEE_BLOCK_HEAD_INFO_START_INFO already defined
#endif
#define FEE_BLOCK_HEAD_INFO_START_INFO (0XAAAAAAAA)

/*! \brief Define flash write aligned macros.
 */
#if(defined Fee_BLOCK_WRITE_ALIGNED_SIZE)
#error Fee_BLOCK_WRITE_ALIGNED_SIZE already defined
#endif
#define Fee_BLOCK_WRITE_ALIGNED_SIZE (8)

/*! \brief Macro that defines the valid flag bits of a block.
 */
#if(defined FEE_BLOCK_VALID_WORD)
#error FEE_BLOCK_VALID_WORD already defined
#endif
#define FEE_BLOCK_VALID_WORD (0xAA)

/*! \brief Macro defining block invalid byte padding.
 */
#if(defined FEE_BLOCK_FILL_WORD)
#error FEE_BLOCK_FILL_WORD already defined
#endif
#define FEE_BLOCK_FILL_WORD (0xDD)

/*! \brief Macro that defines an invalid index for a block definition block.
 */
#if(defined FEE_INVALID_BLOCK_INDEX)
#error FEE_INVALID_BLOCK_INDEX already defined
#endif
#define FEE_INVALID_BLOCK_INDEX                                                     (0xFFFF)

/*! \brief Define macros for calculating block sizes.
 */
#define FEE_BLOCKSIZE(obj)                                                          (ALIGN8BYTE(obj->dataSize))

/*! \brief Used to define whether crc is required in a block.
 */
typedef enum
{
    FEE_CRC_NONE = 0x00,
    FEE_CRC8     = 0x01,
} Fee_BlockCrcType;

/*! \brief Define the type of block configuration.
 */
typedef struct _Fee_BlockConfigType_
{
    uint16_t         number;
    uint16_t         dataSize;
} Fee_BlockConfigType;

/*! \brief Define the type of block runtime information.
 */
typedef struct _Fee_BlockInfoType_
{
    Fee_AddressType phyAddr;
} Fee_BlockInfoType;

/*! \brief Define a block type.
 */
typedef struct _Fee_BlockType_
{
    const struct _Fee_BlockConfigType_ *  cfg;
    struct _Fee_BlockInfoType_ *          info;
} Fee_BlockType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

__attribute__((always_inline)) static inline void Fee_BlockSetPhyAddr(Fee_BlockInfoType *obj, Fee_AddressType phyAddr)
{
    obj->phyAddr = phyAddr;
}

__attribute__((always_inline)) static inline Fee_AddressType Fee_BlockGetPhyAddr(Fee_BlockInfoType *obj)
{
    return obj->phyAddr;
}

__attribute__((always_inline)) static inline bool Fee_BlockCheckBlockNumber(const Fee_BlockConfigType *obj, uint16_t blockNumber)
{
    bool ret = false;

    /* Determine whether the numbers of the incoming blocks are the same. */
    if(obj->number == blockNumber)
    {
        ret = true;
    }
    return ret;
}

__attribute__((always_inline)) static inline Fee_AddressType Fee_GetBlockHeadPhyAddr(uint8_t *data)
{
    uint32_t *phyAddr;

    phyAddr = (uint32_t *)&data[FEE_BLOCK_HEAD_INFO_PHY_ADDR_IDX];

    return (Fee_AddressType)*phyAddr;
}

__attribute__((always_inline)) static inline void Fee_WriteBlockHeadInfo(const Fee_BlockType *obj, Fee_calcCrc8Type crc8Method, uint8_t *cache)
{
    uint32_t        *startInfo;
    uint16_t        *blockNumber;
    Fee_AddressType *phyAddr;
    uint8_t         *crc8;

    /* Initialize cache. */
    memset((void *)cache, 0x00, FEE_BLOCK_HEAD_INFO_SIZE);

    startInfo   = (uint32_t *)&cache[FEE_BLOCK_HEAD_INFO_START_INFO_IDX];
    blockNumber = (uint16_t *)&cache[FEE_BLOCK_HEAD_INFO_BLOCK_NUMBER_IDX];
    phyAddr     = (Fee_AddressType *)&cache[FEE_BLOCK_HEAD_INFO_PHY_ADDR_IDX];
    crc8        = (uint8_t *)&cache[FEE_BLOCK_HEAD_INFO_CRC8_IDX];

    *startInfo   = FEE_BLOCK_HEAD_INFO_START_INFO;
    *blockNumber = obj->cfg->number;
    *phyAddr     = obj->info->phyAddr;
    *crc8        = crc8Method((void *)cache, FEE_BLOCK_CALC_HEAD_INFO_CRC8_LEN);
}

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _FEE_BLOCK_H_ */
