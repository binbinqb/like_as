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

#include <stdbool.h>
#include <math.h>
#include "cse_drv.h"
#include "cse_reg.h"

/*******************************************************************************
 * the defines
 ******************************************************************************/

#define KEY_LEN        (16U)

#define FLS_CSE_BK_KEY (0x43564143UL)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the functions
 ******************************************************************************/

void CseDrv_Init(CseDrvType *obj, struct _CseRegType_ *cseReg)
{
    obj->cseReg = cseReg;
}

static inline uint16_t CseDrv_KeyMode2KeySize(CseDrv_KeyLenType keyMode)
{
    uint16_t keySize = 0;

    switch(keyMode)
    {
    case CSEDRV_KEY_LEN_128BIT:
        keySize = 16;
        break;
    case CSEDRV_KEY_LEN_192BIT:
        keySize = 24;
        break;
    case CSEDRV_KEY_LEN_256BIT:
        keySize = 32;
        break;
    }

    return keySize;
}

static void CseDrv_KeyLoad(CseDrvType *obj, CseDrv_CryptEngineType cryptEngine, CseDrv_LoadModeType keyLoadMode, uint32_t keyAddr, CseDrv_KeyLenType keyMode)
{
    uint16_t  keySize = 0;
    uint32_t *keyPtr  = (uint32_t *)keyAddr;

    /* configure crypt engine */
    CseReg_SetCryptEngine(obj->cseReg, cryptEngine);

    /* use 128-bit as key length by default */
    CseReg_SetKeyMode(obj->cseReg, keyMode);

    /* configure key endian */
    CseReg_SetKeyEndian(obj->cseReg, true);

    /* configure text endian */
    CseReg_SetTextEndian(obj->cseReg, true);

    /* configure according to CPU or DMA handler */
    if(keyLoadMode == CSEDRV_LOAD_MODE_DMA)
    {
        /* enalbe DMA */
        CseReg_SetCtrlDmaEn(obj->cseReg, true);

        /* configure key address to load */
        CseReg_SetKeyAddr(obj->cseReg, keyAddr);

        /* start key load */
        CseReg_SetCtrlKeyLoad(obj->cseReg, true);

        /* wait until key load operation done */
        while(CseReg_GetKeyValidStatus(obj->cseReg) == false)
        {
        }
    }
    else if(keyLoadMode == CSEDRV_LOAD_MODE_CPU)
    {
        keySize = CseDrv_KeyMode2KeySize(keyMode);

        uint8_t i = 0;
        for(i = 0; i < 8; i++)
        {
            if(i < (keySize / 4))
            {
                /* load key value */
                CseReg_SetKey(obj->cseReg, *keyPtr);
                keyPtr++;
            }
            else
            {
                /* padding remaining word as 0 if the key size is less than 8 words */
                CseReg_SetKey(obj->cseReg, 0x0UL);
            }
        }
    }
}

static void CseDrv_CMacSubkey(CseDrvType *obj, uint32_t keyAddr)
{
    /* load key TODO: need to determine the key address */
    CseDrv_KeyLoad(obj, CSEDRV_CRYPT_ENGINE_AES, CSEDRV_LOAD_MODE_DMA, keyAddr, CSEDRV_KEY_LEN_128BIT);

    /* configure crypt engine as AES */
    CseReg_SetCryptEngine(obj->cseReg, CSEDRV_CRYPT_ENGINE_AES);

    /* configure ECB mode */
    CseReg_SetOpMode(obj->cseReg, CSEDRV_OP_MODE_ECB);

    /* configure as encryption */
    CseReg_SetSymmCfgEnc(obj->cseReg, true);

    /* configure endian */
    CseReg_SetKeyEndian(obj->cseReg, true);
    CseReg_SetTextEndian(obj->cseReg, true);

    /* configure crypt finished IRQ as false temporarily */
    CseReg_SetIrqEnReady(obj->cseReg, false);

    /* use 128-bit as key length by default */
    CseReg_SetKeyMode(obj->cseReg, CSEDRV_KEY_LEN_128BIT);

    /* enable subkey generation and generate key for k1
       TODO: for the sake of simplicity only use k1 by default
       later should also implement the logic k2 */
    CseReg_SetSymmCfgCMacSkGen(obj->cseReg, true);
    CseReg_SetSymmCfgCMacSkSel(obj->cseReg, CSEDRV_SUBKEYSEL_K1);

    /* enalbe DMA */
    CseReg_SetCtrlDmaEn(obj->cseReg, true);

    /* config as the last message block for crypt engine */
    CseReg_SetCfgFinal(obj->cseReg, true);

    /* start encryption */
    CseReg_SetCtrlStart(obj->cseReg, true);

    if(CseReg_GetIrqEnReady(obj->cseReg) == false)
    {
        /* not using IRQ so wait until encrypt engine finished */
        while(CseReg_GetStatusReady(obj->cseReg) == false)
        {
        }
        /* clear the ready flag */
        CseReg_ClearStatusReady(obj->cseReg);
    }
    else
    {
        /* use IRQ, do nothing */
    }

    /* enable subkey generation */
    CseReg_SetSymmCfgCMacSkGen(obj->cseReg, false);

    /* soft reset */
    CseReg_SetCtrlSwRst(obj->cseReg);
}

static void CseDrv_CMacLoadRefVal(CseDrvType *obj, uint32_t addr)
{
    /* enable DMA mode */
    CseReg_SetCtrlDmaEn(obj->cseReg, true);

    /* load the reference value address to the dedicated
       register */
    CseReg_SetCMacAddr(obj->cseReg, addr);

    /* start CMAC load */
    CseReg_SetCMacLoadEnable(obj->cseReg, true);

    /* wait until cmac reference value load success */
    while(CseReg_GetStatusCMacValid(obj->cseReg) == false)
    {
    }
}

bool CseDrv_IskeyExist(CseDrvType *obj, CseDrv_KeyIdType keyId)
{
    uint32_t keyStsVal = 0;

    /* configure input message address */
    CseReg_SetDmaRAddr(obj->cseReg, (KEY_SECTOR_START_ADD + keyId * KEY_LEN));

    /* configure DMA operation data size 16 bytes */
    CseReg_SetDmaSize(obj->cseReg, KEY_LEN);

    /* enable DMA mode */
    CseReg_SetCtrlDmaEn(obj->cseReg, true);

    /* enable key analysis */
    CseReg_SetKeyAnaEnable(obj->cseReg, true);

    /* wait until key analysis finished */
    while(CseReg_GetKeyAnaStatus(obj->cseReg))
    {
    }

    /* get the overall key status */
    keyStsVal = CseReg_GetKeyExi(obj->cseReg);

    /* get the status of specific key index */
    keyStsVal = keyStsVal >> keyId;

    return keyStsVal > 0 ? true : false;
}

void CseDrv_CMacHandler(CseDrvType *obj,
                        uint32_t    keyAddr,
                        uint32_t    inpDataAddr,
                        uint32_t    dataSize,
                        uint32_t    refValAddr,
                        uint32_t    oupResAddr,
                        bool       *isAuthPass)
{
    CseDrv_CMacSubkey(obj, keyAddr);

    /* load CMAC reference value */
    CseDrv_CMacLoadRefVal(obj, refValAddr);

    /* configure crypt engine as AES */
    CseReg_SetCryptEngine(obj->cseReg, CSEDRV_CRYPT_ENGINE_AES);

    /* configure CMAC mode */
    CseReg_SetOpMode(obj->cseReg, CSEDRV_OP_MODE_CMAC);

    /* configure encryption */
    CseReg_SetSymmCfgEnc(obj->cseReg, true);

    /* configure little endian as default */
    CseReg_SetKeyEndian(obj->cseReg, true);

    /* configure crypt finished IRQ as false temporarily */
    CseReg_SetIrqEnReady(obj->cseReg, false);

    /* use 128-bit as key length by default */
    CseReg_SetKeyMode(obj->cseReg, CSEDRV_KEY_LEN_128BIT);

    /* configure input message address */
    CseReg_SetDmaRAddr(obj->cseReg, inpDataAddr);

    /* set all initial value vector register SYMM_IVn as 0 */
    CseReg_SetSymmIV0(obj->cseReg, 0);
    CseReg_SetSymmIV1(obj->cseReg, 0);
    CseReg_SetSymmIV2(obj->cseReg, 0);
    CseReg_SetSymmIV3(obj->cseReg, 0);

    /* use k1 or k2 TODO: for simplicity use k1 as default, later
       need to also implement the logic for using k2 */
    CseReg_SetSymmCfgCMacSkGen(obj->cseReg, false);
    CseReg_SetSymmCfgCMacSkSel(obj->cseReg, CSEDRV_SUBKEYSEL_K1);

    /* enable DMA mode */
    CseReg_SetCtrlDmaEn(obj->cseReg, true);

    /* configure DMA operation data size */
    CseReg_SetDmaSize(obj->cseReg, dataSize);

    /* configure output the CMAC result output */
    if(oupResAddr == 0)
    {
        CseReg_SetCMacResultOutEnable(obj->cseReg, false);
    }
    else
    {
        CseReg_SetCMacResultOutEnable(obj->cseReg, true);
        CseReg_SetDmaWAddr(obj->cseReg, oupResAddr);
    }

    /* config as the last message block for crypt engine */
    CseReg_SetCfgFinal(obj->cseReg, true);

    /* enable CMAC authentication */
    CseReg_SetCMacAuthEnable(obj->cseReg, true);

    /* start running encryption / decryption */
    CseReg_SetCtrlStart(obj->cseReg, true);

    if(CseReg_GetIrqEnReady(obj->cseReg) == false)
    {
        /* not using IRQ so wait until encrypt engine finished */
        while(CseReg_GetStatusReady(obj->cseReg) == false)
        {
        }
        /* clear the ready flag */
        CseReg_ClearStatusReady(obj->cseReg);
    }
    else
    {
        /* use IRQ, do nothing */
    }

    if(CseReg_GetCMacOkStatus(obj->cseReg))
    {
        *isAuthPass = true;
    }

    /* TODO: if need to know the CMAC result, check the crypt_cmac_ok
       and get the result from dest address */

    /* soft reset */
    CseReg_SetCtrlSwRst(obj->cseReg);
}

void CseDrv_Operation(CseDrvType *obj, const CseDrv_CfgType *cfg)
{
    /*
        NOTE: this function use synchronzie mode
    */

    uint32_t  blockSize     = 0;
    uint32_t *inputMsgPtr   = (uint32_t *)cfg->inputAddr;
    uint32_t *outputDataPtr = (uint32_t *)cfg->outputAddr;

    if(cfg->opMode == CSEDRV_OP_MODE_MP)
    {
        /* if in MP operation mode, do nothing */
    }
    else
    {
        /* if not in MP operation mode, then load key */
        CseDrv_KeyLoad(obj, cfg->cryptEngine, cfg->keyLoadMode, cfg->keyAddr, cfg->keyLen);
    }

    /* set encrypt / decrypt engine */
    CseReg_SetCryptEngine(obj->cseReg, cfg->cryptEngine);

    /* set operation mode */
    CseReg_SetOpMode(obj->cseReg, cfg->opMode);

    /* set encrpty or decrypt */
    CseReg_SetSymmCfgEnc(obj->cseReg, cfg->isEncrypt);

    /* set key endian */
    CseReg_SetKeyEndian(obj->cseReg, cfg->keyEndian);

    /* configure text endian */
    CseReg_SetTextEndian(obj->cseReg, cfg->inputEndian);

    /* set encrypt ready interrupt */
    CseReg_SetIrqEnReady(obj->cseReg, cfg->intEnable);

    /* set key mode */
    if(cfg->opMode == CSEDRV_OP_MODE_MP)
    {
        /* if in MP operation mode, only support 128-bit key mode */
        CseReg_SetKeyMode(obj->cseReg, CSEDRV_KEY_LEN_128BIT);
    }
    else
    {
        /* if not in MP operation mode, then load key */
        CseReg_SetKeyMode(obj->cseReg, cfg->keyLen);
    }

    if(cfg->opMode == CSEDRV_OP_MODE_CBC)
    {
        /* set initial vector if in CBC operation mode */
        CseReg_SetSymmIV0(obj->cseReg, cfg->initVector[0]);
        CseReg_SetSymmIV1(obj->cseReg, cfg->initVector[1]);
        CseReg_SetSymmIV2(obj->cseReg, cfg->initVector[2]);
        CseReg_SetSymmIV3(obj->cseReg, cfg->initVector[3]);
    }
    else
    {
    }

    if(cfg->inputLoadMode == CSEDRV_LOAD_MODE_DMA)
    {
        /*
            DMA load mode
        */

        /* enable DMA mode */
        CseReg_SetCtrlDmaEn(obj->cseReg, true);

        /* configure input data address */
        CseReg_SetDmaRAddr(obj->cseReg, cfg->inputAddr);

        /* configure output data address */
        CseReg_SetDmaWAddr(obj->cseReg, cfg->outputAddr);

        /* configure DMA operation data size */
        CseReg_SetDmaSize(obj->cseReg, cfg->inputLen);

        /* config as the last message block for crypt engine */
        CseReg_SetCfgFinal(obj->cseReg, true);

        /* start running encryption / decryption */
        CseReg_SetCtrlStart(obj->cseReg, true);

        if(cfg->intEnable == false)
        {
            /* ready interrupt disabled, polling the ready flag */
            while((CseReg_GetStatusReady(obj->cseReg) == false))
            {
            }

            /* clear the ready flag */
            CseReg_ClearStatusReady(obj->cseReg);

            /* soft reset CSE */
            CseReg_SetCtrlSwRst(obj->cseReg);
        }
    }
    else
    {
        /*
            CPU load mode
        */
        CseReg_SetCtrlDmaEn(obj->cseReg, false);

        /* calculate block size (here assume the data size can be divisible by 16 bytes) */
        blockSize = cfg->inputLen / 16;

        uint8_t i = 0;
        for(i = 0; i < blockSize; i++)
        {
            uint8_t j = 0;
            for(j = 0; j < 4; j++)
            {
                CseReg_SetMessage(obj->cseReg, *inputMsgPtr);
                inputMsgPtr++;
            }

            if(i == blockSize - 1)
            {
                /* last block write, set final flag */
                CseReg_SetCfgFinal(obj->cseReg, true);
            }
            else
            {
            }

            /* start running encryption / decryption */
            CseReg_SetCtrlStart(obj->cseReg, true);

            /* ready interrupt disabled, polling the ready flag */
            while(CseReg_GetStatusReady(obj->cseReg) == false)
            {
            }

            /* clear the ready flag */
            CseReg_ClearStatusReady(obj->cseReg);

            uint8_t k = 0;
            for(k = 0; k < 4; k++)
            {
                *outputDataPtr = CseReg_GetDataOutput(obj->cseReg);
                outputDataPtr++;
            }
        }

        /* soft reset CSE */
        CseReg_SetCtrlSwRst(obj->cseReg);
    }
}

void CseDrv_EncryptEcb(CseDrvType *obj, CseDrv_CfgType *cfg)
{
    cfg->opMode        = CSEDRV_OP_MODE_ECB;
    cfg->isEncrypt     = true;
    cfg->initVector[0] = 0;
    cfg->initVector[1] = 0;
    cfg->initVector[2] = 0;
    cfg->initVector[3] = 0;

    /* start CSE operation - ECB encryption */
    CseDrv_Operation(obj, cfg);
}

void CseDrv_DecryptEcb(CseDrvType *obj, CseDrv_CfgType *cfg)
{
    cfg->opMode        = CSEDRV_OP_MODE_ECB;
    cfg->isEncrypt     = false;
    cfg->initVector[0] = 0;
    cfg->initVector[1] = 0;
    cfg->initVector[2] = 0;
    cfg->initVector[3] = 0;

    /* start CSE operation - ECB decryption */
    CseDrv_Operation(obj, cfg);
}

void CseDrv_EncryptCbc(CseDrvType *obj, CseDrv_CfgType *cfg)
{
    cfg->opMode    = CSEDRV_OP_MODE_CBC;
    cfg->isEncrypt = true;

    /* start CSE operation - CBC encryption */
    CseDrv_Operation(obj, cfg);
}

void CseDrv_DecryptCbc(CseDrvType *obj, CseDrv_CfgType *cfg)
{
    cfg->opMode    = CSEDRV_OP_MODE_CBC;
    cfg->isEncrypt = false;

    /* start CSE operation - CBC decryption */
    CseDrv_Operation(obj, cfg);
}
