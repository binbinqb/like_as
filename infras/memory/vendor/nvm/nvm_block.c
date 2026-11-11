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

/*******************************************************************************
 * the includes
 ******************************************************************************/
#include <string.h>
#include "nvm_block.h"

/*******************************************************************************
 * the defines
 ******************************************************************************/

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the static
 ******************************************************************************/

/*******************************************************************************
 * the functions
 ******************************************************************************/
void Nvm_Block_DataRepair(const Nvm_BlockType *obj, const Nvm_MethodType *method, uint16_t blockIdx, uint16_t datasetIdx)
{
    bool     writeFlag = false;
    uint8_t *mainBuff;
    uint8_t *backupBuff;
    uint8_t *tempBuff;
    uint8_t *romBuff;
    uint32_t copySize;
    uint32_t dataSize;

    /* Obtain necessary data for performing block data validity checks. */
    mainBuff = NVM_BLOCK_GET_RAM_BUFF_PTR(obj, blockIdx, datasetIdx);
    tempBuff = NVM_BLOCK_GET_TEMP_RAM_BUFF_PTR(obj, blockIdx);
    romBuff  = NVM_BLOCK_GET_ROM_BUFF_PTR(obj, blockIdx, datasetIdx);
    copySize = Nvm_Block_CalcUseSize(obj, blockIdx);
    dataSize = NVM_BLOCK_GET_DATASIZE(obj, blockIdx);

    /* Check if the block is configured with verification function. */
    if(NVM_BLOCK_IS_CRC(obj, blockIdx))
    {
        /* Check if the block type is redundant. */
        if(NVM_BLOCK_IS_REDUNDANT(obj, blockIdx))
        {
            /* Perform data checks on the main area. */
            Nvm_Block_IntegrityCheck(obj, blockIdx, NVM_BLOCK_MAIN_IDX, method);
            /* Check whether the data validation result of the main area is invalid. */
            if(NVM_BLOCK_CRC_FAIL_MASK == NVM_BLOCK_GET_INTEGRITY(obj, blockIdx, NVM_BLOCK_MAIN_IDX))
            {
                /* Obtain the backup data address of the redundant type block. */
                backupBuff = NVM_BLOCK_GET_RAM_BUFF_PTR(obj, blockIdx, NVM_BLOCK_BACKUP_IDX);
                /* Perform data checks on the backup area */
                Nvm_Block_IntegrityCheck(obj, blockIdx, NVM_BLOCK_BACKUP_IDX, method);
                /* Check whether the data validation result of the backup area is valid. */
                if(NVM_BLOCK_CRC_OK_MASK == NVM_BLOCK_GET_INTEGRITY(obj, blockIdx, NVM_BLOCK_BACKUP_IDX))
                {
                    /* Restore the data in the backup area to the main area. */
                    memcpy(tempBuff, backupBuff, copySize);
                    writeFlag = true;
                }
                else
                {
                    /* Restore data from the ROM region to the main region. */
                    memcpy(tempBuff, romBuff, dataSize);
                    writeFlag = true;
                }
            }
        }
        else
        {
            /* Perform data checks on the main area. */
            Nvm_Block_IntegrityCheck(obj, blockIdx, datasetIdx, method);
            /* Check whether the data validation result of the main area is invalid. */
            if(NVM_BLOCK_CRC_OK_MASK != NVM_BLOCK_GET_INTEGRITY(obj, blockIdx, datasetIdx))
            {
                /* Restore data from the ROM region to the main region. */
                memcpy((void *)tempBuff, (void *)romBuff, dataSize);
                writeFlag = true;
            }
        }
    }
    else
    {
        /* Initialize tempbuff. */
        memset((void *)tempBuff, NVM_BLOCK_RAMBUFF_DEFAULT_VALUE, ALIGN8BYTE(copySize));
        /* Check if the data in the main area is uninitialized. */
        if (0 == memcmp((void *)mainBuff, (void *)tempBuff, ALIGN8BYTE(copySize)))
        {
            /* Check if the block type is redundant. */
            if(NVM_BLOCK_IS_REDUNDANT(obj, blockIdx))
            {
                /* Obtain the backup data address of the redundant type block. */
                backupBuff = NVM_BLOCK_GET_RAM_BUFF_PTR(obj, blockIdx, NVM_BLOCK_BACKUP_IDX);

                /* Check if the data in the backup area is uninitialized. */
                if (0 == memcmp((void *)backupBuff, tempBuff, ALIGN8BYTE(copySize)))
                {
                    /* Restore data from ROM area to main and backup areas. */
                    memcpy(tempBuff, romBuff, dataSize); 
                    writeFlag = true;
                }
                else
                {
                    /* Restore the data in the backup area to the main area. */
                    memcpy(tempBuff, backupBuff, copySize);
                    writeFlag = true;
                }
            }
            else
            {
                /* Restore data from ROM area to main and backup areas. */
                memcpy(tempBuff, romBuff, dataSize);
                writeFlag = true;
            }
        }
        else
        {
            /* Restore data from main area to block all area data. */
            memcpy(tempBuff, mainBuff, dataSize); 
            writeFlag = true;
        }
    }

    if(writeFlag)
    {
        /* Perform data recovery. */
        Nvm_Block_WriteDataToRamBlock(obj, method, blockIdx, datasetIdx, tempBuff);
    }
}

void Nvm_Block_SetDefaultVal(const Nvm_BlockType *obj, const Nvm_MethodType *method, uint16_t blockIdx, uint16_t datasetIdx)
{
    uint8_t *buff;
    /* Initialize all data regions of the block with data from non rom regions. */
    buff = NVM_BLOCK_GET_TEMP_RAM_BUFF_PTR(obj, blockIdx);
    Nvm_Block_GetRomData(obj, blockIdx, datasetIdx, buff);
    Nvm_Block_WriteDataToRamBlock(obj, method, blockIdx, datasetIdx, buff);
}

void Nvm_Block_ClrRamBuff(const Nvm_BlockType *obj, uint16_t blockIdx, uint16_t datasetIdx)
{
    uint8_t *mainRamBuff;
    uint32_t dataSize;

    /* Initialize all initializable data regions of the dataset in the block. */
    dataSize      = ALIGN8BYTE(Nvm_Block_CalcUseSize(obj, blockIdx));
    mainRamBuff   = NVM_BLOCK_GET_RAM_BUFF_PTR(obj, blockIdx, datasetIdx);

    memset((void *)mainRamBuff, NVM_BLOCK_RAMBUFF_DEFAULT_VALUE, dataSize);
}

void Nvm_Block_ClrBlockRamBuff(const Nvm_BlockType *obj, uint16_t blockIdx, uint16_t datasetIdx)
{
    /* Initialize all initializable data regions of the block. */
    if(NVM_BLOCK_IS_REDUNDANT(obj, blockIdx))
    {
        Nvm_Block_ClrRamBuff(obj, blockIdx, NVM_BLOCK_MAIN_IDX);
        Nvm_Block_ClrRamBuff(obj, blockIdx, NVM_BLOCK_BACKUP_IDX);
    }
    else
    {
        Nvm_Block_ClrRamBuff(obj, blockIdx, datasetIdx);
    }
}

void Nvm_Block_SetState(const Nvm_BlockType *obj, uint16_t blockIdx, uint16_t datasetIdx, Nvm_BlockState state)
{
    /* Set the status of the dataset in the block. */
    obj->items[blockIdx].info[datasetIdx].state = state;
}

void Nvm_Block_SetInternalState(const Nvm_BlockType *obj, uint16_t blockIdx, uint16_t datasetIdx, Nvm_BlockState state)
{
    /* Set the internal processing status of the NVM for the dataset in the block. */
    obj->items[blockIdx].info[datasetIdx].internalState = state;
}

void Nvm_Block_SetTempRamBuffDefaultVal(const Nvm_BlockType *obj, uint16_t blockIdx, uint16_t datasetIdx)
{
    /* Initialize the tempbuff of the block. */
    memset((void *)obj->items[blockIdx].tempRamBuffPtr, NVM_BLOCK_RAMBUFF_DEFAULT_VALUE, ALIGN8BYTE(Nvm_Block_CalcUseSize(obj, blockIdx)));
}

uint32_t Nvm_Block_CalcUseSize(const Nvm_BlockType *obj, uint16_t blockIdx)
{
    uint32_t ret;

    /* Check if the block is configured with crc verification. */
    if(NVM_CRC8 == obj->items[blockIdx].crc)
    {
        /* Calculate the size used to store valid data in BLCOK. */
        ret = obj->items[blockIdx].dataSize + NVM_BLOCK_PLACEHOLDER_BYTES + NVM_BLOCK_CRC_BYTES;
    }
    else
    {
        /* Calculate the size used to store valid data in BLCOK. */
        ret = obj->items[blockIdx].dataSize + NVM_BLOCK_PLACEHOLDER_BYTES;
    }

    return ret;
}

void Nvm_Block_GetRomData(const Nvm_BlockType *obj, uint16_t blockIdx, uint8_t datasetIdx, uint8_t *data)
{
    uint8_t *romBuff;

    /* Obtain data from the rom area of the dataset in the block. */
    romBuff = NVM_BLOCK_GET_ROM_BUFF_PTR(obj, blockIdx, datasetIdx);
    memcpy((void *)data, (void *)romBuff, NVM_BLOCK_GET_DATASIZE(obj, blockIdx));
}

bool Nvm_Block_GetWriteData(const Nvm_BlockType *obj, uint16_t blockIdx, uint8_t datasetIdx, const Nvm_MethodType *method, uint8_t *data)
{
    bool    ret = true;
    uint8_t integrity;

   
    /* Check if the block type is redundant. */
    if(NVM_BLOCK_IS_REDUNDANT(obj, blockIdx))
    {
        /* Perform data checks on the main area. */
        Nvm_Block_IntegrityCheck(obj, blockIdx, NVM_BLOCK_MAIN_IDX, method);
        /* Perform data checks on the main area. */
        integrity = NVM_BLOCK_GET_INTEGRITY(obj, blockIdx, NVM_BLOCK_MAIN_IDX);
        /* Check whether the data validation result of the main area is invalid. */
        if(NVM_BLOCK_CRC_OK_MASK == integrity)
        {
            /* Copy valid data */
            memcpy((void *)data, (void *)NVM_BLOCK_GET_RAM_BUFF_PTR(obj, blockIdx, NVM_BLOCK_MAIN_IDX), NVM_BLOCK_GET_DATASIZE(obj, blockIdx));
        }
        else
        {
            /* Perform data checks on the backup area. */
            Nvm_Block_IntegrityCheck(obj, blockIdx, datasetIdx, method);
            /* Perform data checks on the backup area. */
            integrity = NVM_BLOCK_GET_INTEGRITY(obj, blockIdx, NVM_BLOCK_BACKUP_IDX);
            /* Check whether the data validation result of the backup area is invalid. */
            if(NVM_BLOCK_CRC_OK_MASK == integrity)
            {
                /* Copy valid data. */
                memcpy((void *)data, (void *)NVM_BLOCK_GET_RAM_BUFF_PTR(obj, blockIdx, NVM_BLOCK_BACKUP_IDX), NVM_BLOCK_GET_DATASIZE(obj, blockIdx));
            }
            else
            {
                ret = false;
            }
        }
    }
    else
    {
        /* Perform data checks on the dataset area. */
        Nvm_Block_IntegrityCheck(obj, blockIdx, datasetIdx, method);
        /* Perform data checks on the dataset area. */
        integrity = NVM_BLOCK_GET_INTEGRITY(obj, blockIdx, datasetIdx);
        /* Check whether the data validation result of the dataset area is invalid. */
        if(NVM_BLOCK_CRC_OK_MASK == integrity)
        {
            /* Copy valid data. */
            memcpy((void *)data, (void *)NVM_BLOCK_GET_RAM_BUFF_PTR(obj, blockIdx, datasetIdx), NVM_BLOCK_GET_DATASIZE(obj, blockIdx));
        }
        else
        {
            ret = false;
        }
    }

    return ret;
}

void Nvm_Block_IntegrityCheck(const Nvm_BlockType *obj, uint16_t blockIdx, uint8_t datasetIdx, const Nvm_MethodType *method)
{
    uint8_t  crc;
    uint32_t crcLen;
    uint8_t *mainRamBuff;

    /* Set the data validity flag bit of the dataset in the block to error */
    obj->items[blockIdx].info[datasetIdx].integrity = NVM_BLOCK_CRC_FAIL_MASK;

    /* Check if the block is configured with crc verification */
    if(NVM_BLOCK_IS_CRC(obj, blockIdx))
    {
        /* The required data length, starting address, and parity bits for obtaining verification data */
        crcLen      = NVM_BLOCK_GET_CRC_LEN(obj, blockIdx);
        mainRamBuff = obj->items[blockIdx].buff[datasetIdx].ramBuffPtr;
        crc         = method->crc8(mainRamBuff, crcLen);
        /* Compare check bits */
        if(crc == mainRamBuff[crcLen])
        {
            /* Verification passed, configure the data validity flag as successful */
            obj->items[blockIdx].info[datasetIdx].integrity = NVM_BLOCK_CRC_OK_MASK;
        }
    }
    else
    {
        /* Verification passed, configure the data validity flag as successful */
        obj->items[blockIdx].info[datasetIdx].integrity = NVM_BLOCK_CRC_OK_MASK;
    }
}

void Nvm_Block_WriteDataToBuff(const Nvm_BlockType *obj, const Nvm_MethodType *method, uint16_t blockIdx, uint16_t datasetIdx, uint8_t *data)
{
    uint8_t * buff;
    uint32_t  dataSize;
    uint32_t  crcLen;

    /* Write data to the corresponding RAM area based on blockid and dataset */
    buff     = NVM_BLOCK_GET_RAM_BUFF_PTR(obj, blockIdx, datasetIdx);
    dataSize = ALIGN8BYTE(Nvm_Block_CalcUseSize(obj, blockIdx));
    
    memset((void *)buff, NVM_BLOCK_RAMBUFF_DEFAULT_VALUE, ALIGN8BYTE(Nvm_Block_CalcUseSize(obj, blockIdx)));
    memcpy((void *)buff, (void *)data, dataSize);
    
    if(NVM_BLOCK_IS_CRC(obj, blockIdx))
    {
        crcLen       = NVM_BLOCK_GET_CRC_LEN(obj, blockIdx);
        buff[crcLen] = method->crc8(buff, crcLen);
    }
}

void Nvm_Block_WriteDataToRamBlock(const Nvm_BlockType *obj, const Nvm_MethodType *method, uint16_t blockIdx, uint16_t datasetIdx, uint8_t *data)
{
    /* If the type of the block is redundant, the data will be written to the main and backup areas. */
    /* Otherwise, the data will be written to the dataset area. */
    if(NVM_BLOCK_IS_REDUNDANT(obj, blockIdx))
    {
        Nvm_Block_WriteDataToBuff(obj, method, blockIdx, NVM_BLOCK_MAIN_IDX, data);
        Nvm_Block_WriteDataToBuff(obj, method, blockIdx, NVM_BLOCK_BACKUP_IDX, data);
    }
    else
    {
        Nvm_Block_WriteDataToBuff(obj, method, blockIdx, datasetIdx, data);
    }
}

uint16_t Nvm_Block_Search(const Nvm_BlockType *obj, uint16_t blockNumber)
{
    uint16_t retBlock       = NVM_BLOCK_INVALID_IDX;
    uint16_t blockStartIdx  = 0;
    uint16_t blockMiddleIdx = (obj->itemsNum - 1) / 2;
    uint16_t blockEndIdx    = obj->itemsNum - 1;
    bool     retFlag        = false;

    while(false == retFlag)
    {
        /* If the current block and the input block are the same */
        if(blockNumber == obj->items[blockMiddleIdx].number)
        {
            /* Returns the index of the block */
            retBlock = blockMiddleIdx;
            retFlag  = true;
        }
        else
        {
            /* Currently, there are only two or fewer blocks left that are not found, then check the other block */
            if((blockEndIdx - blockStartIdx) <= 1)
            {
                retFlag = true;
                if(blockNumber == obj->items[blockEndIdx].number)
                {
                    retBlock = blockEndIdx;
                }
            }
            else
            {
                /* In descending order, first determine whether it is in the right range, */
                /* and then check whether it is in the left range */
                if(obj->items[blockMiddleIdx].number < blockNumber)
                {
                    blockStartIdx = blockMiddleIdx + 1;
                }
                else
                {
                    blockEndIdx = blockMiddleIdx - 1;
                }
                
                /* Calculate Median */
                blockMiddleIdx = blockEndIdx + blockStartIdx;
                blockMiddleIdx /= 2;
            }
        }
    }

    return retBlock;
}
