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

#ifndef _FEE_SECTOR_H_
#define _FEE_SECTOR_H_

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "fee_block.h"
#include "fee_extra.h"
#include "fee_trace.h"
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

/*! \brief Macro that defines the number of flags contained in the section header.
 */
#if(defined FEE_SECTOR_HEAD_MARK_NUM)
#error FEE_SECTOR_HEAD_MARK_NUM already defined
#endif
#define FEE_SECTOR_HEAD_MARK_NUM (4)

/*! \brief Macro for the size of the sector header information flag header.
 */
#if(defined FEE_SECTOR_HEAD_SIZE)
#error FEE_SECTOR_HEAD_SIZE already defined
#endif
#define FEE_SECTOR_HEAD_SIZE (64)

/*! \brief Defines the minimum unit of sector size,
 *         which depends on the hardware of the flash and needs to be aligned with the flash section.
 */
#if(defined FEE_SECTION_LENGTH)
#error FEE_SECTION_LENGTH already defined
#endif
#define FEE_SECTION_LENGTH (1024)

/*! \brief Define the size of each flag bit in the sector header.
 */
#if(defined FEE_SECTOR_HEAD_INFO_LEN)
#error FEE_SECTOR_HEAD_INFO_LEN already defined
#endif
#define FEE_SECTOR_HEAD_INFO_LEN (8)

/*! \brief Define the size of the backup redundancy area for each flag bit in the sector header.
 */
#if(defined FEE_SECTOR_HEAD_INFO_BACKUP_AREA_LEN)
#error FEE_SECTOR_HEAD_INFO_BACKUP_AREA_LEN already defined
#endif
#define FEE_SECTOR_HEAD_INFO_BACKUP_AREA_LEN (4)

/*! \brief Defines the index of the header of the flag bit in the sector information header.
 */
#if(defined FEE_SECTOR_HEAD_MARK_IDX)
#error FEE_SECTOR_HEAD_MARK_IDX already defined
#endif
#define FEE_SECTOR_HEAD_MARK_IDX (0)

/*! \brief The index of the FLAG that defines the flag bits in the sector header.
 */
#if(defined FEE_SECTOR_HEAD_FLAG_IDX)
#error FEE_SECTOR_HEAD_FLAG_IDX already defined
#endif
#define FEE_SECTOR_HEAD_FLAG_IDX (1)

/*! \brief The index that defines the fill of the flag bit in the sector header.
 */
#if(defined FEE_SECTOR_HEAD_FILL_IDX)
#error FEE_SECTOR_HEAD_FILL_IDX already defined
#endif
#define FEE_SECTOR_HEAD_FILL_IDX (2)

/*! \brief Defines the index of the crc8 flag bit in the sector header.
 */
#if(defined FEE_SECTOR_HEAD_CRC_IDX)
#error FEE_SECTOR_HEAD_CRC_IDX already defined
#endif
#define FEE_SECTOR_HEAD_CRC_IDX (3)

/*! \brief Macro that defines the calculated length of the crc8 flag bit in the sector header.
 */
#if(defined FEE_SECTOR_HEAD_CRC_LEN)
#error FEE_SECTOR_HEAD_CRC_LEN already defined
#endif
#define FEE_SECTOR_HEAD_CRC_LEN (3)

/*! \brief Macro that defines the header of the flag bit in the sector information header.
 */
#if(defined FEE_SECTOR_VALID_WORD)
#error FEE_SECTOR_VALID_WORD already defined
#endif
#define FEE_SECTOR_VALID_WORD (0X5A)

/*! \brief Macro that defines the header of the flag bit in the sector information header.
 */
#if(defined FEE_SECTOR_INIT_FLAG_WORD)
#error FEE_SECTOR_INIT_FLAG_WORD already defined
#endif
#define FEE_SECTOR_INIT_FLAG_WORD (0X01)

/*! \brief Macro that defines the initialization status flag bits in the sector header.
 */
#if(defined FEE_SECTOR_INIT_START_FLAG_WORD)
#error FEE_SECTOR_INIT_START_FLAG_WORD already defined
#endif
#define FEE_SECTOR_INIT_START_FLAG_WORD (0X02)

/*! \brief Macro that defines the transport completion status flag bit in the sector header.
 */
#if(defined FEE_SECTOR_INIT_WRITE_END_FLAG_WORD)
#error FEE_SECTOR_INIT_WRITE_END_FLAG_WORD already defined
#endif
#define FEE_SECTOR_INIT_WRITE_END_FLAG_WORD (0X03)

/*! \brief Macro that defines the enable sector status flag bits in the sector header.
 */
#if(defined FEE_SECTOR_INIT_ENABLE_FLAG_WORD)
#error FEE_SECTOR_INIT_ENABLE_FLAG_WORD already defined
#endif
#define FEE_SECTOR_INIT_ENABLE_FLAG_WORD (0X04)

/*! \brief Define macros that need to be filled in the sector.
 */
#if(defined FEE_SECTOR_FILL_WORD)
#error FEE_SECTOR_FILL_WORD already defined
#endif
#define FEE_SECTOR_FILL_WORD      (0x00)

/*! \brief Macro that defines the position of the sector initialization flag bit in the sector header information.
 */
#define FEE_SECTOR_INIT_IDX       (0)

/*! \brief Macro that defines the position of the start moving flag bit in the sector header information.
 */
#define FEE_SECTOR_START_HAND_IDX (8)

/*! \brief A macro that defines the position of the transport end flag bit in the sector header information.
 */
#define FEE_SECTOR_END_HAND_IDX   (16)

/*! \brief Macro that defines the position of the enable flag bit in the sector header information.
 */
#define FEE_SECTOR_EN_SECTOR_IDX  (24)

/*! \brief Define macros for marking data addresses in the backup sector header.
 */
#define FEE_SECTOR_BACKUP_HEAD_ADDR(obj) (obj->endAddr - FEE_SECTOR_HEAD_SIZE)
/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief Define the type of sector state.
 */
typedef enum
{

    FEE_SECTOR_INIT              = 0x00,
    FEE_SECTOR_INIT_FINISH       = 0x01,
    FEE_SECTOR_START_HAND        = 0x02,
    FEE_SECTOR_START_HAND_FINISH = 0x03,
    FEE_SECTOR_END_HAND          = 0x04,
    FEE_SECTOR_END_HAND_FINISH   = 0x05,
    FEE_SECTOR_EN                = 0x06,
    FEE_SECTOR_EN_FINISH         = 0x07,
    FEE_SECTOR_UNUSED            = 0x08,
    FEE_SECTOR_ACTIVE            = 0x09,
    FEE_SECTOR_ERASE             = 0x0A,
    FEE_SECTOR_UNDEFINE          = 0xFF,
} Fee_SectorStatusType;

/*! \brief Define sector error types.
 */
typedef enum
{
    FEE_SECTOR_NOT_ERROR               = 0x00000000,
    FEE_SECTOR_READ_ERROR              = 0x00000001,
    FEE_SECTOR_WRITE_ERROR             = 0x00000002,
    FEE_SECTOR_ERASE_ERROR             = 0x00000004,
    FEE_SECTOR_ADDR_NOALIGNED          = 0x00000008,
    FEE_SECTOR_WRITE_EN_MARK_ERROR     = 0x00000010,
    FEE_SECTOR_WRITE_INIT_MARK_ERROR   = 0x00000020,
    FEE_SECTOR_WRITE_START_MARK_ERROR  = 0x00000040,
    FEE_SECTOR_WRITE_END_MARK_ERROR    = 0x00000080,
    FEE_SECTOR_WRITE_FINISH_MARK_ERROR = 0x00000100,
    FEE_SECTOR_WRITE_HEAD_FILL_ERROR   = 0x00000200,
    FEE_SECTOR_UNDEFINE_ERROR          = 0x00000400,
} Fee_SectorErrorType;

/*! \brief Define the type of external state feedback from the sector.
 */
typedef enum
{
    FEE_SECTOR_RETURN_SECTOR1_ACTIVE                 = 0x01,
    FEE_SECTOR_RETURN_SECTOR2_ACTIVE                 = 0x02,
    FEE_SECTOR_RETURN_SECTOR1_ACTIVE_SECTOR2_UNERASE = 0x03,
    FEE_SECTOR_RETURN_SECTOR2_ACTIVE_SECTOR1_UNERASE = 0x04,
    FEE_SECTOR_RETURN_UNINITIALIZATION               = 0x05,
    FEE_SECTOR_RETURN_SECTOR1_UNERASE                = 0x06,
    FEE_SECTOR_RETURN_SECTOR2_UNERASE                = 0x07,
    FEE_SECTOR_RETURN_UNDEFINE                       = 0x08,
} Fee_SectorReturnType;

/*! \brief Define the type of sector runtime information.
 */
typedef struct _Fee_SectorInfoType_
{
    Fee_AddressType      searchAddr;
    Fee_AddressType      remAddr;
    Fee_AddressType      headInfoAddr;
    uint32_t             eraseSectionIdx;
    Fee_SectorStatusType status;
    Fee_SectorErrorType  errors;
} Fee_SectorInfoType;

/*! \brief Define the type of sector configuration information.
 */
typedef struct _Fee_SectorConfigType_
{
    Fee_AddressType                    startAddr;
    Fee_AddressType                    endAddr;
    uint32_t const                     eraseSectionNum;
    struct _Fee_SectorInfoType_ *const info;
} Fee_SectorConfigType;

/*! \brief Define the type of the sector object.
 */
typedef struct _Fee_SectorType_
{
    uint16_t                             sectorSize;
    const struct _Fee_SectorConfigType_ *sectors;
    uint16_t                             blockSize;
    const struct _Fee_BlockType_        *blocks;
} Fee_SectorType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

__attribute__((always_inline)) static inline bool Fee_SectorIsErase(const Fee_SectorConfigType *obj, const Fee_MethodType *method)
{
    bool     ret = true;
    uint32_t sectionIdx;

    /* Check whether all the flash space of the sector is writable. */

    for(sectionIdx = 0; sectionIdx < obj->eraseSectionNum; sectionIdx++)
    {
        if(FLS_STATE_NOT_WRITABLE == method->isWriteable((Fee_AddressType)(obj->startAddr + sectionIdx * FEE_SECTION_LENGTH), FEE_SECTION_LENGTH))
        {
            ret = false;
            break;
        }
    }

    return ret;
}

__attribute__((always_inline)) static inline void Fee_SectorCheckErase(const Fee_SectorConfigType *obj, const Fee_MethodType *method)
{
    if (Fee_SectorIsErase(obj, method))
    {
        obj->info->status = FEE_SECTOR_ERASE;    
    }
}

__attribute__((always_inline)) static inline bool Fee_CheckSectorIsInitFinished(const Fee_calcCrc8Type method, uint8_t *cache)
{
    bool    ret = false;
    uint8_t crc;

    /* The flag bits of the sector header information are composed of a start flag, */
    /* a status flag, an idle bit fill, and a crc8 check code to check the integrity of the flag bit data. */

    crc = method(cache, FEE_SECTOR_HEAD_CRC_LEN);

    if(cache[FEE_SECTOR_HEAD_CRC_IDX] == crc)
    {
        if(FEE_SECTOR_VALID_WORD == cache[FEE_SECTOR_HEAD_MARK_IDX])
        {
            if(FEE_SECTOR_INIT_FLAG_WORD == cache[FEE_SECTOR_HEAD_FLAG_IDX])
            {
                if(FEE_SECTOR_FILL_WORD == cache[FEE_SECTOR_HEAD_FILL_IDX])
                {
                    ret = true;
                }
            }
        }
    }

    return ret;
}

__attribute__((always_inline)) static inline bool Fee_CheckSectorIsStartHand(const Fee_calcCrc8Type method, uint8_t *cache)
{
    bool    ret = false;
    uint8_t crc;

    /* The flag bits of the sector header information are composed of a start flag, */
    /* a status flag, an idle bit fill, and a crc8 check code to check the integrity of the flag bit data. */

    crc = method(cache, FEE_SECTOR_HEAD_CRC_LEN);

    if(cache[FEE_SECTOR_HEAD_CRC_IDX] == crc)
    {
        if(FEE_SECTOR_VALID_WORD == cache[FEE_SECTOR_HEAD_MARK_IDX])
        {
            if(FEE_SECTOR_INIT_START_FLAG_WORD == cache[FEE_SECTOR_HEAD_FLAG_IDX])
            {
                if(FEE_SECTOR_FILL_WORD == cache[FEE_SECTOR_HEAD_FILL_IDX])
                {
                    ret = true;
                }
            }
        }
    }

    return ret;
}

__attribute__((always_inline)) static inline bool Fee_CheckSectorIsEndHand(const Fee_calcCrc8Type method, uint8_t *cache)
{
    bool    ret = false;
    uint8_t crc;

    /* The flag bits of the sector header information are composed of a start flag, */
    /* a status flag, an idle bit fill, and a crc8 check code to check the integrity of the flag bit data. */

    crc = method(cache, FEE_SECTOR_HEAD_CRC_LEN);

    if(cache[FEE_SECTOR_HEAD_CRC_IDX] == crc)
    {
        if(FEE_SECTOR_VALID_WORD == cache[FEE_SECTOR_HEAD_MARK_IDX])
        {
            if(FEE_SECTOR_INIT_WRITE_END_FLAG_WORD == cache[FEE_SECTOR_HEAD_FLAG_IDX])
            {
                if(FEE_SECTOR_FILL_WORD == cache[FEE_SECTOR_HEAD_FILL_IDX])
                {
                    ret = true;
                }
            }
        }
    }

    return ret;
}

__attribute__((always_inline)) static inline bool Fee_CheckSectorIsEnSector(const Fee_calcCrc8Type method, uint8_t *cache)
{
    bool    ret = false;
    uint8_t crc;

    /* The flag bits of the sector header information are composed of a start flag, */
    /* a status flag, an idle bit fill, and a crc8 check code to check the integrity of the flag bit data. */

    crc = method(cache, FEE_SECTOR_HEAD_CRC_LEN);

    if(cache[FEE_SECTOR_HEAD_CRC_IDX] == crc)
    {
        if(FEE_SECTOR_VALID_WORD == cache[FEE_SECTOR_HEAD_MARK_IDX])
        {
            if(FEE_SECTOR_INIT_ENABLE_FLAG_WORD == cache[FEE_SECTOR_HEAD_FLAG_IDX])
            {
                if(FEE_SECTOR_FILL_WORD == cache[FEE_SECTOR_HEAD_FILL_IDX])
                {
                    ret = true;
                }
            }
        }
    }

    return ret;
}

__attribute__((always_inline)) static inline void Fee_UpdateSectorStatus(const Fee_SectorConfigType *obj, const Fee_calcCrc8Type method, uint8_t *data)
{
    if(Fee_CheckSectorIsInitFinished(method, &data[FEE_SECTOR_INIT_IDX]) || Fee_CheckSectorIsInitFinished(method, &data[FEE_SECTOR_INIT_IDX + FEE_SECTOR_HEAD_INFO_BACKUP_AREA_LEN]))
    {
        obj->info->status = FEE_SECTOR_INIT_FINISH;
    }
    else
    {
        return;
    }
    if(Fee_CheckSectorIsStartHand(method, &data[FEE_SECTOR_START_HAND_IDX]) || Fee_CheckSectorIsStartHand(method, &data[FEE_SECTOR_START_HAND_IDX + FEE_SECTOR_HEAD_INFO_BACKUP_AREA_LEN]))
    {
        obj->info->status = FEE_SECTOR_START_HAND_FINISH;
    }
    else
    {
        return;
    }
    if(Fee_CheckSectorIsEndHand(method, &data[FEE_SECTOR_END_HAND_IDX]) || Fee_CheckSectorIsEndHand(method, &data[FEE_SECTOR_END_HAND_IDX + FEE_SECTOR_HEAD_INFO_BACKUP_AREA_LEN]))
    {
        obj->info->status = FEE_SECTOR_END_HAND_FINISH;
    }
    else
    {
        return;
    }
    if(Fee_CheckSectorIsEnSector(method, &data[FEE_SECTOR_EN_SECTOR_IDX]) || Fee_CheckSectorIsEnSector(method, &data[FEE_SECTOR_EN_SECTOR_IDX + FEE_SECTOR_HEAD_INFO_BACKUP_AREA_LEN]))
    {
        obj->info->status = FEE_SECTOR_EN_FINISH;
    }
    else
    {
        return;
    }
}

__attribute__((always_inline)) static inline void Fee_CheckSectorIsValid(const Fee_SectorConfigType *obj, const Fee_MethodType *method, uint8_t *cache)
{
    /* When it is detected that the header information of a sector is not writable, */
    /* it will be checked to see if the sector is in an active state. */
    /* The sector initialization flag, the start of transport flag, the transport completion flag, */
    /* and the enable sector flag should be checked respectively. */
    /* Only when all flag bits are checked to be valid can they be considered active sectors.*/
    Fls_StateType flsState;

    flsState = method->read(obj->startAddr, cache, FEE_SECTOR_HEAD_SIZE);
    
    if(FLS_STATE_OK == flsState)
    {
        Fee_UpdateSectorStatus(obj, method->crc8, cache);
    }
    else if ((FLS_STATE_ECC_ERROR == flsState) || (FLS_STATE_READ_BACK_FAIL == flsState))
    {
        flsState = method->read(FEE_SECTOR_BACKUP_HEAD_ADDR(obj), cache, FEE_SECTOR_HEAD_SIZE);
        
        if(FLS_STATE_OK == flsState)
        {
            Fee_UpdateSectorStatus(obj, method->crc8, cache);
        }
        else
        {
            obj->info->errors = FEE_SECTOR_READ_ERROR;
        }
    }
    else if (FLS_STATE_NOT_WRITTEN == flsState)
    {
        obj->info->status = FEE_SECTOR_UNDEFINE;
    }
    else
    {
        obj->info->errors = FEE_SECTOR_READ_ERROR;
    }
       
}

__attribute__((always_inline)) static inline void Fee_SectorInitInfo(const Fee_SectorConfigType *obj)
{
    obj->info->remAddr      = obj->startAddr + FEE_SECTOR_HEAD_SIZE;
    obj->info->headInfoAddr = obj->endAddr - FEE_SECTOR_HEAD_SIZE - FEE_BLOCK_HEAD_INFO_SIZE;
    obj->info->searchAddr   = obj->endAddr - FEE_SECTOR_HEAD_SIZE - FEE_BLOCK_HEAD_INFO_SIZE;
    obj->info->errors       = FEE_SECTOR_NOT_ERROR;
    obj->info->status       = FEE_SECTOR_UNDEFINE;
}

__attribute__((always_inline)) static inline void Fee_SectorsInit(const Fee_SectorType *obj, const Fee_MethodType *method, void *cache)
{
    int sectorIdx;

    /* Reset the information of the sector runtime and check the status of the sector based on its header information. */

    for(sectorIdx = 0; sectorIdx < obj->sectorSize; sectorIdx++)
    {
        Fee_SectorInitInfo(&obj->sectors[sectorIdx]);
    }
}

__attribute__((always_inline)) static inline bool Fee_CheckRemSpace(const Fee_SectorConfigType *obj, const Fee_BlockType *block)
{
    bool     ret = false;
    uint16_t freeSize;
    int      preFreeSize;

    /* Calculation of sector free space size: */
    /* Total space - Space occupied by block info - Space occupied by block data - 64Byte sector header information - 8-byte placeholder. */
    /* In order to prevent the area of block info and block data from crossing each other's boundaries, */
    /* at least one flash phrase size placeholder should be reserved. */

    freeSize    = obj->info->headInfoAddr - obj->info->remAddr;
    preFreeSize = freeSize - FEE_BLOCKSIZE(block->cfg) - FEE_BLOCK_HEAD_INFO_SIZE - Fee_BLOCK_WRITE_ALIGNED_SIZE;

    if(preFreeSize > 0)
    {
        ret = true;
    }

    return ret;
}

__attribute__((always_inline)) static inline const Fee_SectorConfigType *Fee_GetFirstSector(const Fee_SectorType *obj)
{
    const Fee_SectorConfigType *ret = NULL;

    if(obj->sectors != NULL)
    {
        ret = &obj->sectors[0];
    }

    return ret;
}

__attribute__((always_inline)) static inline const Fee_SectorConfigType *Fee_SearchValidSector(const Fee_SectorType *obj)
{
    const Fee_SectorConfigType *ret              = NULL;
    int                         sectorEnFinshCnt = 0;
    int                         sectorIdx;

    for(sectorIdx = 0; sectorIdx < obj->sectorSize; sectorIdx++)
    {
        if((FEE_SECTOR_EN_FINISH == obj->sectors[sectorIdx].info->status) && (FEE_SECTOR_NOT_ERROR == obj->sectors[sectorIdx].info->errors))
        {
            sectorEnFinshCnt++;
            ret = &obj->sectors[sectorIdx];
        }
    }
    if(sectorEnFinshCnt != 1)
    {
        FEE_DBG_SEARCH_MULTIPLE_VALID_SECTOR_ERROR_ENTRY();
        ret = NULL;
    }
    return ret;
}

__attribute__((always_inline)) static inline const Fee_SectorConfigType *Fee_SearchGcSector(const Fee_SectorType *obj)
{
    const Fee_SectorConfigType *ret         = NULL;
    bool                        gcSectorCnt = 0;
    int                         sectorIdx;

    /* When switching from one sector to another, */
    /* first look for sectors with a status of either unint or not active. */

    for(sectorIdx = 0; sectorIdx < obj->sectorSize; sectorIdx++)
    {
        if((obj->sectors[sectorIdx].info->status < FEE_SECTOR_EN_FINISH) && (FEE_SECTOR_NOT_ERROR == obj->sectors[sectorIdx].info->errors))
        {
            gcSectorCnt++;
            ret = &obj->sectors[sectorIdx];
        }
    }

    if(gcSectorCnt != 1)
    {
        FEE_DBG_SEARCH_MULTIPLE_GC_SECTOR_ERROR_ENTRY();
        ret = NULL;
    }
    return ret;
}

__attribute__((always_inline)) static inline void Fee_InitEraseSector(const Fee_SectorConfigType *obj)
{
    obj->info->eraseSectionIdx = 0;
}

__attribute__((always_inline)) static inline void Fee_EraseSector(const Fee_SectorConfigType *obj, const Fee_MethodType *method)
{
    Fee_AddressType eraseAddr;

    /* When erasing a sector, */
    /* erase the sections of the N flash files that make up the sector in a time-sharing manner. */

    if((obj->info->status != FEE_SECTOR_ACTIVE) && (obj->info->status != FEE_SECTOR_ERASE))
    {
        if(obj->info->eraseSectionIdx < obj->eraseSectionNum)
        {
            eraseAddr = obj->startAddr + (obj->info->eraseSectionIdx * FEE_SECTION_LENGTH);

            if(ALIGNED((eraseAddr) + FEE_SECTION_LENGTH - 1, FEE_SECTION_LENGTH) > ALIGNED(eraseAddr, FEE_SECTION_LENGTH))
            {
                obj->info->errors = FEE_SECTOR_ADDR_NOALIGNED;
            }
            else if(FLS_STATE_OK != method->erase(eraseAddr))
            {
                obj->info->errors = FEE_SECTOR_ERASE_ERROR;
            }
            else
            {
                obj->info->eraseSectionIdx++;
            }
        }
        else
        {
            obj->info->status = FEE_SECTOR_ERASE;
        }
    }
}

__attribute__((always_inline)) static inline bool Fee_SectorWriteHeadMark(const Fee_MethodType *method, Fee_AddressType writeAddr, uint8_t *cache)
{
    bool ret = false;

    if(FLS_STATE_OK == method->write(writeAddr, cache, FEE_SECTOR_HEAD_INFO_LEN))
    {
        ret = true;
    }

    return ret;
}

__attribute__((always_inline)) static inline void Fee_SectorWriteInitMark(const Fee_SectorConfigType *obj, const Fee_MethodType *method, uint8_t *cache)
{
    int idx;

    /* The data format of the flag bit of the sector header information consists of a start flag bit, */
    /* a status flag bit, a fill bit, and a crc check bit. */
    /* When assembling a flag bit, the check value of crc8 is written last. */
    if(((FEE_SECTOR_UNUSED == obj->info->status) || (FEE_SECTOR_ERASE == obj->info->status)) && (FEE_SECTOR_NOT_ERROR == obj->info->errors))
    {
        obj->info->status = FEE_SECTOR_INIT;

        cache[FEE_SECTOR_HEAD_MARK_IDX] = FEE_SECTOR_VALID_WORD;
        cache[FEE_SECTOR_HEAD_FLAG_IDX] = FEE_SECTOR_INIT_FLAG_WORD;
        cache[FEE_SECTOR_HEAD_FILL_IDX] = FEE_SECTOR_FILL_WORD;
        cache[FEE_SECTOR_HEAD_CRC_IDX]  = method->crc8(cache, FEE_SECTOR_HEAD_CRC_LEN);

        for(idx = 0; idx < FEE_SECTOR_HEAD_INFO_BACKUP_AREA_LEN; idx++)
        {
            cache[FEE_SECTOR_HEAD_INFO_BACKUP_AREA_LEN + idx] = cache[idx];
        }

        if(Fee_SectorWriteHeadMark(method, obj->startAddr + FEE_SECTOR_INIT_IDX, cache))
        {
            Fee_SectorWriteHeadMark(method, FEE_SECTOR_BACKUP_HEAD_ADDR(obj) + FEE_SECTOR_INIT_IDX, cache);
            obj->info->status = FEE_SECTOR_INIT_FINISH;
        }
        else
        {
            obj->info->errors = FEE_SECTOR_WRITE_INIT_MARK_ERROR;
        }
    }
    else
    {
        obj->info->errors = FEE_SECTOR_WRITE_INIT_MARK_ERROR;
    }
}

__attribute__((always_inline)) static inline void Fee_SectorWriteStartHandMark(const Fee_SectorConfigType *obj, const Fee_MethodType *method, uint8_t *cache)
{
    int idx;

    /* The data format of the flag bit of the sector header information consists of a start flag bit, */
    /* a status flag bit, a fill bit, and a crc check bit. */
    /* When assembling a flag bit, the check value of crc8 is written last. */

    if((FEE_SECTOR_INIT_FINISH == obj->info->status) && (FEE_SECTOR_NOT_ERROR == obj->info->errors))
    {
        obj->info->status = FEE_SECTOR_START_HAND;

        cache[FEE_SECTOR_HEAD_MARK_IDX] = FEE_SECTOR_VALID_WORD;
        cache[FEE_SECTOR_HEAD_FLAG_IDX] = FEE_SECTOR_INIT_START_FLAG_WORD;
        cache[FEE_SECTOR_HEAD_FILL_IDX] = FEE_SECTOR_FILL_WORD;
        cache[FEE_SECTOR_HEAD_CRC_IDX]  = method->crc8(cache, FEE_SECTOR_HEAD_CRC_LEN);

        for(idx = 0; idx < FEE_SECTOR_HEAD_INFO_BACKUP_AREA_LEN; idx++)
        {
            cache[FEE_SECTOR_HEAD_INFO_BACKUP_AREA_LEN + idx] = cache[idx];
        }

        if(Fee_SectorWriteHeadMark(method, obj->startAddr + FEE_SECTOR_START_HAND_IDX, cache))
        {
            Fee_SectorWriteHeadMark(method, FEE_SECTOR_BACKUP_HEAD_ADDR(obj) + FEE_SECTOR_START_HAND_IDX, cache);
            obj->info->status = FEE_SECTOR_START_HAND_FINISH;
        }
        else
        {
            obj->info->errors = FEE_SECTOR_WRITE_START_MARK_ERROR;
        }
    }
    else
    {
        obj->info->errors = FEE_SECTOR_WRITE_START_MARK_ERROR;
    }
}

__attribute__((always_inline)) static inline void Fee_SectorWriteEndHandMark(const Fee_SectorConfigType *obj, const Fee_MethodType *method, uint8_t *cache)
{
    int idx;

    /* The data format of the flag bit of the sector header information consists of a start flag bit, */
    /* a status flag bit, a fill bit, and a crc check bit. */
    /* When assembling a flag bit, the check value of crc8 is written last. */

    if(FEE_SECTOR_START_HAND_FINISH == obj->info->status)
    {
        obj->info->status = FEE_SECTOR_END_HAND;

        cache[FEE_SECTOR_HEAD_MARK_IDX] = FEE_SECTOR_VALID_WORD;
        cache[FEE_SECTOR_HEAD_FLAG_IDX] = FEE_SECTOR_INIT_WRITE_END_FLAG_WORD;
        cache[FEE_SECTOR_HEAD_FILL_IDX] = FEE_SECTOR_FILL_WORD;
        cache[FEE_SECTOR_HEAD_CRC_IDX]  = method->crc8(cache, FEE_SECTOR_HEAD_CRC_LEN);

        for(idx = 0; idx < FEE_SECTOR_HEAD_INFO_BACKUP_AREA_LEN; idx++)
        {
            cache[FEE_SECTOR_HEAD_INFO_BACKUP_AREA_LEN + idx] = cache[idx];
        }

        if(Fee_SectorWriteHeadMark(method, obj->startAddr + FEE_SECTOR_END_HAND_IDX, cache))
        {
            Fee_SectorWriteHeadMark(method, FEE_SECTOR_BACKUP_HEAD_ADDR(obj) + FEE_SECTOR_END_HAND_IDX, cache);
            obj->info->status = FEE_SECTOR_END_HAND_FINISH;
        }
        else
        {
            obj->info->errors = FEE_SECTOR_WRITE_END_MARK_ERROR;
        }
    }
    else
    {
        obj->info->errors = FEE_SECTOR_WRITE_END_MARK_ERROR;
    }
}

__attribute__((always_inline)) static inline void Fee_SectorWriteEnableSectorMark(const Fee_SectorConfigType *obj, const Fee_MethodType *method, uint8_t *cache)
{
    int idx;

    /* The data format of the flag bit of the sector header information consists of a start flag bit, */
    /* a status flag bit, a fill bit, and a crc check bit. */
    /* When assembling a flag bit, the check value of crc8 is written last. */

    if(FEE_SECTOR_END_HAND_FINISH == obj->info->status)
    {
        obj->info->status = FEE_SECTOR_EN;

        cache[FEE_SECTOR_HEAD_MARK_IDX] = FEE_SECTOR_VALID_WORD;
        cache[FEE_SECTOR_HEAD_FLAG_IDX] = FEE_SECTOR_INIT_ENABLE_FLAG_WORD;
        cache[FEE_SECTOR_HEAD_FILL_IDX] = FEE_SECTOR_FILL_WORD;
        cache[FEE_SECTOR_HEAD_CRC_IDX]  = method->crc8(cache, FEE_SECTOR_HEAD_CRC_LEN);

        for(idx = 0; idx < FEE_SECTOR_HEAD_INFO_BACKUP_AREA_LEN; idx++)
        {
            cache[FEE_SECTOR_HEAD_INFO_BACKUP_AREA_LEN + idx] = cache[idx];
        }

        if(Fee_SectorWriteHeadMark(method, obj->startAddr + FEE_SECTOR_EN_SECTOR_IDX, cache))
        {
            Fee_SectorWriteHeadMark(method, FEE_SECTOR_BACKUP_HEAD_ADDR(obj) + FEE_SECTOR_EN_SECTOR_IDX, cache);
            obj->info->status = FEE_SECTOR_EN_FINISH;
        }
        else
        {
            obj->info->errors = FEE_SECTOR_WRITE_EN_MARK_ERROR;
        }
    }
    else
    {
        obj->info->errors = FEE_SECTOR_WRITE_EN_MARK_ERROR;
    }
}

__attribute__((always_inline)) static inline void Fee_SectorFillHeadInfo(const Fee_SectorConfigType *obj, const Fee_MethodType *method, uint8_t *cache)
{
    Fee_AddressType writeAddr;
    Fee_AddressType startWriteAddr = obj->startAddr + (FEE_SECTOR_HEAD_MARK_NUM * FEE_SECTOR_HEAD_INFO_LEN);
    Fee_AddressType endWriteAddr   = obj->startAddr + FEE_SECTOR_HEAD_SIZE;

    /* After initializing the header information of the sector, */
    /* in order to ensure the security of the sector's flash operation, */
    /* the remaining unused header information should be filled in to initialize to ensure the certainty of the sector.*/

    if(FEE_SECTOR_EN_FINISH == obj->info->status)
    {
        memset((void *)cache, FEE_SECTOR_FILL_WORD, ALIGN8BYTE(FEE_SECTOR_HEAD_INFO_LEN));

        for(writeAddr = startWriteAddr; writeAddr < endWriteAddr; writeAddr = writeAddr + Fee_BLOCK_WRITE_ALIGNED_SIZE)
        {
            if(FLS_STATE_OK != method->write(writeAddr, cache, ALIGN8BYTE(FEE_SECTOR_HEAD_INFO_LEN)))
            {
                obj->info->errors |= FEE_SECTOR_WRITE_HEAD_FILL_ERROR;
                break;
            }
        }

        startWriteAddr = FEE_SECTOR_BACKUP_HEAD_ADDR(obj) + (FEE_SECTOR_HEAD_MARK_NUM * FEE_SECTOR_HEAD_INFO_LEN);
        endWriteAddr   = FEE_SECTOR_BACKUP_HEAD_ADDR(obj) + FEE_SECTOR_HEAD_SIZE;

        for(writeAddr = startWriteAddr; writeAddr < endWriteAddr; writeAddr = writeAddr + Fee_BLOCK_WRITE_ALIGNED_SIZE)
        {
            if(FLS_STATE_OK != method->write(writeAddr, cache, ALIGN8BYTE(FEE_SECTOR_HEAD_INFO_LEN)))
            {
                obj->info->errors |= FEE_SECTOR_WRITE_HEAD_FILL_ERROR;
                break;
            }
        }
    }
    else
    {
        obj->info->errors |= FEE_SECTOR_WRITE_HEAD_FILL_ERROR;
    }
}

__attribute__((always_inline)) static inline Fee_SectorStatusType Fee_SectorGetStatus(const Fee_SectorConfigType *obj)
{
    return obj->info->status;
}

__attribute__((always_inline)) static inline void Fee_SectorWriteHeadInfo(const Fee_SectorConfigType *obj, const Fee_MethodType *method, uint8_t *cache)
{
    if(FEE_SECTOR_UNUSED == obj->info->status)
    {
        Fee_SectorWriteInitMark(obj, method, cache);
        Fee_SectorWriteStartHandMark(obj, method, cache);
        Fee_SectorWriteEndHandMark(obj, method, cache);
        Fee_SectorWriteEnableSectorMark(obj, method, cache);
        Fee_SectorFillHeadInfo(obj, method, cache);
    }
}

__attribute__((always_inline)) static inline const Fee_BlockType *Fee_MatchBlock(const Fee_SectorType *obj, const Fee_MethodType *method, uint8_t *data)
{
    const Fee_BlockType *ret = NULL;
    uint8_t              calcCrc;
    uint8_t             *blockCrc;
    uint32_t            *blockEnMark;
    uint16_t            *blockNumber;
    int                  blockIdx;

    /* Block info parses the format according to the protocol, */
    /* and after performing integrity checks, the description information of the block will be paired to ensure that the description of the block info can access the corresponding block data. */

    blockCrc = (uint8_t *)&(data[FEE_BLOCK_HEAD_INFO_CRC8_IDX]);
    calcCrc  = method->crc8((void *)data, FEE_BLOCK_CALC_HEAD_INFO_CRC8_LEN);

    if((*blockCrc) == calcCrc)
    {
        blockEnMark = (uint32_t *)&(data[FEE_BLOCK_HEAD_INFO_START_INFO_IDX]);
        blockNumber = (uint16_t *)&(data[FEE_BLOCK_HEAD_INFO_BLOCK_NUMBER_IDX]);

        if(FEE_BLOCK_HEAD_INFO_START_INFO == (*blockEnMark))
        {
            for(blockIdx = 0; blockIdx < obj->blockSize; blockIdx++)
            {
                if(Fee_BlockCheckBlockNumber(obj->blocks[blockIdx].cfg, *blockNumber))
                {
                    ret = &obj->blocks[blockIdx];
                    break;
                }
            }
        }
    }
    return ret;
}

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _FEE_SECTOR_H_ */
