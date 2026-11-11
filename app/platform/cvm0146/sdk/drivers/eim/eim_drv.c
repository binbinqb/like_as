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

#include "eim_drv.h"
#include "eim_reg.h"

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
 * the functions
 ******************************************************************************/

#define     EIM_LENGTH_CHK                  (8)
#define     EIM_LENGTH_DATA                 (32)
#define     EIM_LENGTH_ADDR                 (32)


uint8_t arr_data2reg_chk[EIM_LENGTH_CHK]   = {
    0, 1, 3, 7, 15, 31,                                            /* REG_DATA */
    31,                                                            /* REG_ADDR */
    7                                                              /* REG_CHK  */
}; 

uint8_t arr_data2reg_data[EIM_LENGTH_DATA] = {
    2, 4, 5, 6, 8, 9, 10, 11, 12,                                  /* REG_DATA */
    13, 14, 16, 17, 18, 19, 20, 21, 22, 23, 
    24, 25, 26, 27, 28, 29, 30,
    0, 1, 2, 3, 4, 5                                               /* REG_ADDR */

};

uint8_t arr_data2reg_addr[EIM_LENGTH_ADDR] = {
    6, 7, 8, 9, 10, 11, 12, 13, 14, 15,                            /* REG_ADDR */
    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 
    26, 27, 28, 29, 30,
    0, 1, 2, 3, 4, 5, 6                                            /* REG_CHK  */
};



uint8_t arr_reg2data_chk[EIM_LENGTH_CHK]   = {
    25, 26, 27, 28, 29, 30, 31,                                    /* REG_ADDR */
    7                                                              /* REG_CHK  */
}; 

uint8_t arr_reg2data_data[EIM_LENGTH_DATA] = {
    0, 1,                                                          /* REG_CHK  */
    0,                                                             /* REG_DATA */
    2,                                                             /* REG_CHK  */
    1, 2, 3,                                                       /* REG_DATA */
    3,                                                             /* REG_CHK  */
    4, 5, 6, 7, 8, 9, 10,                                          /* REG_DATA */
    4,                                                             /* REG_CHK  */
    11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,    /* REG_DATA */
    5                                                              /* REG_CHK  */
                                   
};

uint8_t arr_reg2data_addr[EIM_LENGTH_ADDR] = {
    26, 27, 28, 29, 30, 31,                                        /* REG_DATA */
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,          /* REG_ADDR */
    16, 17, 18, 19, 20, 21, 22, 23, 24,
    6                                                              /* REG_CHK  */
};

static void EimDrv_RegToDataConvert(EimDrv_SramType *sramType, EimDrv_SramType *sramType_temp)
{
    uint8_t i;
    uint8_t length = EIM_LENGTH_CHK;

    for (i = 0; i < length; i++)
    {
        if ((sramType_temp->chk >> i) & 0x01)
        {
            if ( i <= 6 )                   sramType->addr |= 1 << arr_reg2data_chk[i];
            if (i > 6 && i < length )       sramType->chk  |= 1 << arr_reg2data_chk[i];
        }
    }

    length = EIM_LENGTH_DATA;
    for (i = 0; i < length; i++)
    {
        if ((sramType_temp->data >> i) & 0x01)
        {
            if (i <= 1 )                    sramType->chk  |= 1 << arr_reg2data_data[i];
            if (i == 2 )                    sramType->data |= 1 << arr_reg2data_data[i];
            if (i == 3 )                    sramType->chk  |= 1 << arr_reg2data_data[i];
            if (i > 3 && i <= 6 )           sramType->data |= 1 << arr_reg2data_data[i];
            if (i == 7 )                    sramType->chk  |= 1 << arr_reg2data_data[i];
            if (i > 7 && i <= 14 )          sramType->data |= 1 << arr_reg2data_data[i];
            if (i == 15 )                   sramType->chk  |= 1 << arr_reg2data_data[i];
            if (i > 16 && i <= 30 )         sramType->data |= 1 << arr_reg2data_data[i];
            if (i == 31 )                   sramType->chk  |= 1 << arr_reg2data_data[i];
        }
    }

    length = EIM_LENGTH_ADDR;
    for (i = 0; i < length; i++)
    {
        if ((sramType_temp->addr >> i) & 0x01)
        {
            if (i <= 5 )                    sramType->data |= 1 << arr_reg2data_addr[i];
            if (i > 5 && i <= 30 )          sramType->addr |= 1 << arr_reg2data_addr[i];
            if (i == 31 )                   sramType->chk  |= 1 << arr_reg2data_addr[i];
        }
    }
}

static void EimDrv_DataToRegConvert(EimDrv_SramType *sramType, EimDrv_SramType *sramType_temp)
{
    uint8_t i;
    uint8_t length = EIM_LENGTH_CHK;

    for (i = 0; i < length; i++)
    {
        if ((sramType->chk >> i) & 0x01)
        {
            if (i <= 5 )                    sramType_temp->data |= 1 << arr_data2reg_chk[i];
            if (i > 5 && i <= 6 )           sramType_temp->addr |= 1 << arr_data2reg_chk[i];
            if (i > 6 && i < length )       sramType_temp->chk  |= 1 << arr_data2reg_chk[i];
        }
    }

    length = EIM_LENGTH_DATA;
    for (i = 0; i < length; i++)
    {
        if ((sramType->data >> i) & 0x01)
        {
            if (i <= 26 )                   sramType_temp->data |= 1 << arr_data2reg_data[i];
            if (i > 26 && i < length )      sramType_temp->addr |= 1 << arr_data2reg_data[i];
        }
    }

    length = EIM_LENGTH_ADDR;
    for (i = 0; i < length; i++)
    {
        if ((sramType->addr >> i) & 0x01)
        {
            if (i <= 24 )                    sramType_temp->addr |= 1 << arr_data2reg_addr[i];
            if (i > 24 && i < length )       sramType_temp->chk  |= 1 << arr_data2reg_addr[i];
        }
    }
}

void EimDrv_Init(EimDrvType *obj, struct _EimRegType_ *eimReg)
{
    obj->reg = eimReg;
}

void EimDrv_GetDefaultConfig(EimDrv_ChnCfgType *userConfig)
{
    uint8_t errInChnNum;
    uint8_t sramChnNum;
    uint8_t cacheChnNum;

    /* Get Error in global enable status, default: false */
    userConfig->globalEnable = false;

    for(errInChnNum = 0; errInChnNum < EIMDRV_ERRIN_TOTAL_CHN_NUM; errInChnNum++)
    {
        /* Get Error in channel num enable status, default: false */
        userConfig->chnNumStatus[errInChnNum] = false;
    }

    for(sramChnNum = 0; sramChnNum < EIMDRV_ERRIN_SRAM_TOTAL_NUM; sramChnNum++)
    {
        /* Get Error in sram chk, default: 0 */
        userConfig->accSramCfg[sramChnNum].chk = 0;
        /* Get Error in sram data, default: 0 */
        userConfig->accSramCfg[sramChnNum].data = 0;
        /* Get Error in sram addr, default: 0 */
        userConfig->accSramCfg[sramChnNum].addr = 0;
    }

    for(cacheChnNum = 0; cacheChnNum < EIMDRV_ERRIN_CACHE_TOTAL_NUM; cacheChnNum++)
    {
        /* Get Error in cache chk, default: 0 */
        userConfig->accCacheCfg[cacheChnNum].chk = 0;
        /* Get Error in cache data0, default: 0 */
        userConfig->accCacheCfg[cacheChnNum].data0 = 0;
        /* Get Error in cache data1, default: 0 */
        userConfig->accCacheCfg[cacheChnNum].data1 = 0;
        /* Get Error in cache data2, default: 0 */
        userConfig->accCacheCfg[cacheChnNum].data2 = 0;
    }
}

bool EimDrv_GetChnGlobalEnable(EimDrvType *obj)
{
    /* Get Error in global enable */
    return EimReg_GetGlobalStatus(obj->reg);
}

void EimDrv_EnableGlobalChn(EimDrvType *obj, bool enable)
{
    /* Config Error in global enable */
    EimReg_Enable(obj->reg, enable);
}

bool EimDrv_GetChnNumEnable(EimDrvType *obj, EimDrv_ChnSelType chnNum)
{
    uint8_t temp;

    temp = EimReg_GetChnEnable(obj->reg);
    /* Get Error in channel num enable */
    return ((temp >> chnNum) & 0x1);
}

void EimDrv_EnableChannel(EimDrvType *obj, EimDrv_ChnSelType chnNum, bool enable)
{
    uint8_t chnStatusCtrl;

    chnStatusCtrl = EimReg_GetChnEnable(obj->reg);
    if(enable)
    {
        chnStatusCtrl |= (1 << chnNum);
    }
    else
    {
        chnStatusCtrl &= ~(1 << chnNum);
    }
    /* Config Error in channel num enable */
    EimReg_SetChnEnable(obj->reg, chnStatusCtrl);
}

void EimDrv_GetSramErrInStatus(EimDrvType *obj, EimDrv_SramType *sramType, EimDrv_SramAccType accType)
{
    EimDrv_SramType sramType_temp = {0};
    
    /* only get error in access sram channel status */
    if(accType > EIMDRV_ERRIN_SRAMU)
    {
        return;
    }

    /* get error in access sram Ecc  */
    sramType_temp.chk = EimReg_GetSramEccCHK(obj->reg, accType);
    /* get error in access sram data */
    sramType_temp.data = EimReg_GetSramEccData(obj->reg, accType);
    /* get error in access sram addr */
    sramType_temp.addr = EimReg_GetSramEccAddr(obj->reg, accType);

    EimDrv_RegToDataConvert(sramType, &sramType_temp);
}

void EimDrv_SetSramErrInStatus(EimDrvType *obj, EimDrv_SramType *sramType, EimDrv_SramAccType accType)
{
    EimDrv_SramType sramType_temp = {0};

    /* only get error in access sram channel status */
    if(accType > EIMDRV_ERRIN_SRAMU)
    {
        return;
    }

    EimDrv_DataToRegConvert(sramType, &sramType_temp);

    /* set error in access sram Ecc */
    EimReg_SetSramEccCHK(obj->reg, accType, sramType_temp.chk);
    /* set error in access sram data */
    EimReg_SetSramEccData(obj->reg, accType, sramType_temp.data);
    /* set error in access sram addr */
    EimReg_SetSramEccAddr(obj->reg, accType, sramType_temp.addr);
}

void EimDrv_GetCacheErrInStatus(EimDrvType *obj, EimDrv_CacheType *cacheType, EimDrv_CacheAccType accType)
{
    /* only get error in access cache channel status */
    if(accType > EIMDRV_ERRIN_CACHE_WAY1)
    {
        return;
    }

    /* get error in access cache Ecc  */
    cacheType->chk = EimReg_GetCacheEccCHK(obj->reg, accType);
    /* get error in access cache data0 */
    cacheType->data0 = EimReg_GetCacheEccData0(obj->reg, accType);
    /* get error in access cache data1 */
    cacheType->data1 = EimReg_GetCacheEccData1(obj->reg, accType);
    /* get error in access cache data2 */
    cacheType->data2 = EimReg_GetCacheEccData2(obj->reg, accType);
}

void EimDrv_SetCacheErrInStatus(EimDrvType *obj, EimDrv_CacheType *cacheType, EimDrv_CacheAccType accType)
{
    /* only set error in access cache channel status */
    if(accType > EIMDRV_ERRIN_CACHE_WAY1)
    {
        return;
    }

    /* set error in access cache Ecc  */
    EimReg_SetCacheEccCHK(obj->reg, accType, cacheType->chk);
    /* set error in access cache data0 */
    EimReg_SetCacheEccData0(obj->reg, accType, cacheType->data0);
    /* set error in access cache data1 */
    EimReg_SetCacheEccData1(obj->reg, accType, cacheType->data1);
    /* set error in access cache data2 */
    EimReg_SetCacheEccData2(obj->reg, accType, cacheType->data2);
}
