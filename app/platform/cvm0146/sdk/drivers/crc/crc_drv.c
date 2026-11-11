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

#include "crc_drv.h"
#include "crc_reg.h"

/*******************************************************************************
 * the defines
 ******************************************************************************/

#define CRCDRV_FIFO_MAX (4)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the functions
 ******************************************************************************/

void CrcDrv_Init(CrcDrvType *obj, struct _CrcRegType_ *reg)
{
    obj->reg = reg;
}

void CrcDrv_Configure(CrcDrvType *obj, const CrcDrv_ConfigType *userConfig)
{
    /* Set CRC mode */
    CrcReg_SetCrProtocolWidth(obj->reg, (uint8_t)userConfig->crcWidth);
    /* Set transposes options */
    CrcReg_SetCrReverseOut(obj->reg, (uint8_t)userConfig->readTranspose);
    /* Set CRC polynomial */
    CrcReg_SetPolyReg(obj->reg, userConfig->polynomial);
    /* Set writes transposes */
    CrcReg_SetCrReverseIn(obj->reg, (uint8_t)userConfig->writeTranspose);
    /* Sets complement or inversion checksum */
    CrcReg_SetCrFXor(obj->reg, userConfig->complementChecksum);
    /* Write a seed - initial checksum */
    CrcReg_SetInitReg(obj->reg, userConfig->seed);
}

void CrcDrv_GetConfig(const CrcDrvType *obj, CrcDrv_ConfigType *userConfig)
{
    /* Gets CRC mode */
    userConfig->crcWidth = (CrcDrv_BitWidthType)CrcReg_GetCrProtocolWidth(obj->reg);
    /* Gets transposes and complement options */
    userConfig->readTranspose = (CrcDrv_TransposeType)CrcReg_GetCrReverseOut(obj->reg);
    /* Get a polynomial */
    userConfig->polynomial = CrcReg_GetPolyReg(obj->reg);
    /* Gets transposes options */
    userConfig->writeTranspose = (CrcDrv_TransposeType)CrcReg_GetCrReverseIn(obj->reg);
    /* Gets complement or inversion checksum */
    userConfig->complementChecksum = CrcReg_GetCrFXor(obj->reg);
    /* Get a seed - initial checksum */
    userConfig->seed = CrcReg_GetInitReg(obj->reg);
}

void CrcDrv_GetDefaultConfig(CrcDrv_ConfigType *userConfig)
{
    /* Gets CRC mode default is 16 bit */
    userConfig->crcWidth = CRCDRV_BITWIDTH_16;
    /* Gets default a polynomial default is reset value */
    userConfig->polynomial = 0x1021U;
    /* Gets default read transposes none */
    userConfig->readTranspose = CRCDRV_TRANSPOSE_NONE;
    /* Gets default write transpose none */
    userConfig->writeTranspose = CRCDRV_TRANSPOSE_NONE;
    /* Gets default no complement or inversion checksum */
    userConfig->complementChecksum = false;
    /* Gets default a seed - initial checksum */
    userConfig->seed = 0xFFFFFFFFU;
}

void CrcDrv_SetNewSeed(CrcDrvType *obj, uint32_t seed)
{
    /* Write a seed - initial checksum */
    CrcReg_SetInitReg(obj->reg, seed);
}

void CrcDrv_CrcReset(CrcDrvType *obj)
{
    /* execute CRC rsset */
    CrcReg_SetCrReset(obj->reg);

    /* wait until CRC rsset execute completely */
    while(CrcReg_GetCrReset(obj->reg) != 0)
    {
    }
}

uint32_t CrcDrv_GetCrcResult(CrcDrvType *obj)
{
    CrcDrv_BitWidthType  width = (CrcDrv_BitWidthType)(CrcReg_GetCrProtocolWidth(obj->reg));
    CrcDrv_TransposeType transpose;
    uint32_t             result;

    if(width == CRCDRV_BITWIDTH_16)
    {
        transpose = (CrcDrv_TransposeType)(CrcReg_GetCrReverseOut(obj->reg));
        if((transpose == CRCDRV_TRANSPOSE_BITS_AND_BYTES) || (transpose == CRCDRV_TRANSPOSE_BYTES))
        {
            /* Wait until no remaining data in FIFO */
            while(CrcReg_GetDataNumInFifo(obj->reg) != 0)
            {
            }
            /* Returns upper 16 bits of CRC because of transposition in 16-bit mode */
            result = (uint32_t)((CrcReg_GetDataReg(obj->reg) >> 16) & 0xFFFF);
        }
        else
        {
            /* Wait until no remaining data in FIFO */
            while(CrcReg_GetDataNumInFifo(obj->reg) != 0)
            {
            }
            /* Get the lower 16 bits */
            result = (uint32_t)(CrcReg_GetDataReg(obj->reg) & 0xFFFF);
        }
    }
    else
    {
        /* Wait until no remaining data in FIFO */
        while(CrcReg_GetDataNumInFifo(obj->reg) != 0)
        {
        }
        result = CrcReg_GetDataReg(obj->reg);
    }

    return result;
}

void CrcDrv_WriteData8(CrcDrvType *obj, const uint8_t *data, uint32_t dataSize)
{
    uint32_t group    = 0;
    uint32_t groupNum = dataSize / CRCDRV_FIFO_MAX;
    uint32_t left     = dataSize - groupNum * CRCDRV_FIFO_MAX;
    uint32_t i        = 0;

    /* 8-bit writes till end of data buffer */
    for(group = 0; group < groupNum; ++group)
    {
        /* Wait until no remaining data in FIFO */
        while(CrcReg_GetDataNumInFifo(obj->reg) != 0)
        {
        }
        /* Write as many as possible until FIFO is full */
        for(i = 0; i < CRCDRV_FIFO_MAX; ++i)
        {
            CrcReg_SetData8Reg(obj->reg, data[group * CRCDRV_FIFO_MAX + i]);
        }
    }
    /* If still data buffering, wait until no remaining data in FIFO */
    while(left != 0 && CrcReg_GetDataNumInFifo(obj->reg) != 0)
    {
    }
    for(i = 0; i < left; ++i)
    {
        CrcReg_SetData8Reg(obj->reg, data[dataSize - left + i]);
    }
}

void CrcDrv_WriteData16(CrcDrvType *obj, const uint16_t *data, uint32_t dataSize)
{
    uint32_t group    = 0;
    uint32_t groupNum = dataSize / CRCDRV_FIFO_MAX;
    uint32_t left     = dataSize - groupNum * CRCDRV_FIFO_MAX;
    uint32_t i        = 0;

    /* 8-bit writes till end of data buffer */
    for(group = 0; group < groupNum; ++group)
    {
        /* Wait until no remaining data in FIFO */
        while(CrcReg_GetDataNumInFifo(obj->reg) != 0)
        {
        }
        /* Write as many as possible until FIFO is full */
        for(i = 0; i < CRCDRV_FIFO_MAX; ++i)
        {
            CrcReg_SetData16Reg(obj->reg, data[group * CRCDRV_FIFO_MAX + i]);
        }
    }
    /* If still data buffering, wait until no remaining data in FIFO */
    while(left != 0 && CrcReg_GetDataNumInFifo(obj->reg) != 0)
    {
    }
    for(i = 0; i < left; ++i)
    {
        CrcReg_SetData16Reg(obj->reg, data[dataSize - left + i]);
    }
}

void CrcDrv_WriteData32(CrcDrvType *obj, const uint32_t *data, uint32_t dataSize)
{
    uint32_t group    = 0;
    uint32_t groupNum = dataSize / CRCDRV_FIFO_MAX;
    uint32_t left     = dataSize - groupNum * CRCDRV_FIFO_MAX;
    uint32_t i        = 0;

    /* 8-bit writes till end of data buffer */
    for(group = 0; group < groupNum; ++group)
    {
        /* Wait until no remaining data in FIFO */
        while(CrcReg_GetDataNumInFifo(obj->reg) != 0)
        {
        }
        /* Write as many as possible until FIFO is full */
        for(i = 0; i < CRCDRV_FIFO_MAX; ++i)
        {
            CrcReg_SetDataReg(obj->reg, data[group * CRCDRV_FIFO_MAX + i]);
        }
    }
    /* If still data buffering, wait until no remaining data in FIFO */
    while(left != 0 && CrcReg_GetDataNumInFifo(obj->reg) != 0)
    {
    }
    for(i = 0; i < left; ++i)
    {
        CrcReg_SetDataReg(obj->reg, data[dataSize - left + i]);
    }
}
