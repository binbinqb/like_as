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

#include "pdb_drv.h"
#include "pdb_reg.h"
#include "sim_reg.h"

/*******************************************************************************
 * the defines
 ******************************************************************************/

#define PDB_CF_MASK                (1U)
#define PDBDRV_PRE_TRG_ENABLE      (1U)
#define PDBDRV_PRE_BB_MODE_ENABLE  (1U)
#define PDBDRV_PRE_DLY_MODE_ENABLE (1U)
#define PDBDRV_PO_ENABLE           (1U)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the functions
 ******************************************************************************/

void PdbDrv_Init(PdbDrvType *obj, struct _PdbRegType_ *pdbReg, struct _SimRegType_ *simReg)
{
    obj->pdbReg = pdbReg;
    obj->simReg = simReg;
}

void PdbDrv_EnablePdb(PdbDrvType *obj)
{
    PdbReg_SetPdbenReg(obj->pdbReg, true);
}

void PdbDrv_PdbDisable(PdbDrvType *obj)
{
    PdbReg_SetPdbenReg(obj->pdbReg, false);
}

void PdbDrv_SwtrigCmd(PdbDrvType *obj)
{
    PdbReg_SwtrigReg(obj->pdbReg);
}

void PdbDrv_ClrPdbif(PdbDrvType *obj)
{
    PdbReg_ClrPdbifReg(obj->pdbReg);
}

void PdbDrv_LoadCmd(PdbDrvType *obj)
{
    PdbReg_StartLoadReg(obj->pdbReg);
}

uint16_t PdbDrv_GetCnt(const PdbDrvType *obj)
{
    return (PdbReg_GetCntReg(obj->pdbReg));
}

uint8_t PdbDrv_GetChnCf(const PdbDrvType *obj, PdbDrv_ChType chn)
{
    uint8_t tmp;
    tmp = PdbReg_GetChnCfReg(obj->pdbReg, (uint8_t)chn);
    return (tmp);
}

void PdbDrv_ClrChnCf(PdbDrvType *obj, PdbDrv_ChType chn)
{
    PdbReg_ClrChnCfReg(obj->pdbReg, (uint8_t)chn);
}

uint8_t PdbDrv_GetChnErr(const PdbDrvType *obj, PdbDrv_ChType chn)
{
    uint8_t tmp;
    tmp = PdbReg_GetChnErrReg(obj->pdbReg, (uint8_t)chn);
    return (tmp);
}

void PdbDrv_ClrChnErr(PdbDrvType *obj, PdbDrv_ChType chn)
{
    PdbReg_ClrChnErrReg(obj->pdbReg, (uint8_t)chn);
}

void PdbDrv_SetChnBbMode(PdbDrvType *obj, PdbDrv_ChType chn, uint8_t value)
{
    PdbReg_SetChnBbReg(obj->pdbReg, value, (uint8_t)chn);
}

uint8_t PdbDrv_GetChnBbMode(PdbDrvType *obj, PdbDrv_ChType chn)
{
    return (PdbReg_GetChnBbReg(obj->pdbReg, (uint8_t)chn));
}

void PdbDrv_SetChnTosMode(PdbDrvType *obj, PdbDrv_ChType chn, uint8_t value)
{
    PdbReg_SetChnTosReg(obj->pdbReg, value, (uint8_t)chn);
}

uint8_t PdbDrv_GetChnTosMode(PdbDrvType *obj, PdbDrv_ChType chn)
{
    return (PdbReg_GetChnTosReg(obj->pdbReg, (uint8_t)chn));
}

void PdbDrv_ConfigPreTrg(PdbDrvType *obj, const PdbDrv_PreTrgType *userConfig)
{
    PdbDrv_ChType    ch;
    PdbDrv_PreChType preCh;
    uint8_t          tos;
    uint8_t          en;
    uint8_t          bb;
    /* Pre-Trigger channel configuration */
    for(ch = PDBDRV_CHANNEL0; ch < PDBDRV_CH_NUMBER; ch++)
    {
        tos = 0;
        en  = 0;
        bb  = 0;
        for(preCh = PDBDRV_PRE_CHANNEL0; preCh < PDBDRV_PRE_CH_NUMBER; preCh++)
        {
            switch(userConfig->mode[ch][preCh])
            {
            case PDBDRV_PRETRG_DISABLE:
                break;
            case PDBDRV_PRETRG_BYPASSED_MODE:
                en |= PDBDRV_PRE_TRG_ENABLE << preCh;
                break;
            case PDBDRV_PRETRG_DELAY_MODE:
                en |= PDBDRV_PRE_TRG_ENABLE << preCh;
                tos |= PDBDRV_PRE_DLY_MODE_ENABLE << preCh;
                break;
            case PDBDRV_PRETRG_BB_MODE:
                en |= PDBDRV_PRE_TRG_ENABLE << preCh;
                bb |= PDBDRV_PRE_BB_MODE_ENABLE << preCh;
                break;
            default:
                /* Impossible case */
                break;
            }
        }
        PdbReg_SetChnBbReg(obj->pdbReg, bb, ch);
        PdbReg_SetChnTosReg(obj->pdbReg, tos, ch);
        PdbReg_SetChnEnReg(obj->pdbReg, en, ch);
    }
}

void PdbDrv_GetPreTrgCfg(const PdbDrvType *obj, PdbDrv_PreTrgType *userConfig)
{
    PdbDrv_ChType    ch;
    PdbDrv_PreChType preCh;
    uint8_t          tos;
    uint8_t          en;
    uint8_t          bb;
    /* Pre-Trigger channel configuration */
    for(ch = PDBDRV_CHANNEL0; ch < PDBDRV_CH_NUMBER; ch++)
    {
        tos = PdbReg_GetChnTosReg(obj->pdbReg, ch);
        en  = PdbReg_GetChnEnReg(obj->pdbReg, ch);
        bb  = PdbReg_GetChnBbReg(obj->pdbReg, ch);
        for(preCh = PDBDRV_PRE_CHANNEL0; preCh < PDBDRV_PRE_CH_NUMBER; preCh++)
        {
            uint8_t preChEn  = (en >> preCh) & PDBDRV_PRE_TRG_ENABLE;
            uint8_t preChBb  = (bb >> preCh) & PDBDRV_PRE_BB_MODE_ENABLE;
            uint8_t preChDly = (tos >> preCh) & PDBDRV_PRE_DLY_MODE_ENABLE;
            if(preChEn == 0)
            {
                userConfig->mode[ch][preCh] = PDBDRV_PRETRG_DISABLE;
            }
            else if(preChBb == 1)
            {
                userConfig->mode[ch][preCh] = PDBDRV_PRETRG_BB_MODE;
            }
            else if(preChDly == 1)
            {
                userConfig->mode[ch][preCh] = PDBDRV_PRETRG_DELAY_MODE;
            }
            else
            {
                userConfig->mode[ch][preCh] = PDBDRV_PRETRG_BYPASSED_MODE;
            }
        }
    }
}

void PdbDrv_GetDefaultConfig(PdbDrv_ConfigType *userConfig)
{
    userConfig->ldmode          = PDBDRV_LDMOD_LOAD_VAL_IMMEDIATELY;
    userConfig->pdbeie          = false;
    userConfig->dmaen           = false;
    userConfig->prescalerFactor = PDBDRV_PRESCALER_1MULT;
    userConfig->trgInSel        = PDBDRV_TRGSEL_TRGGER_SOFTWARE;
    userConfig->pdbie           = false;
    userConfig->mult            = PDBDRV_MULT_FACTOR_1;
    userConfig->cMode           = PDBDRV_CONT_CONTINUOUS;

    userConfig->dlyCfg.modCnt  = 60000;
    userConfig->dlyCfg.idlyCnt = 0;

    PdbDrv_ChType    ch;
    PdbDrv_PreChType preCh;
    PdbDrv_PoChType  poCh;
    for(ch = PDBDRV_CHANNEL0; ch < PDBDRV_CH_NUMBER; ch++)
    {
        for(preCh = PDBDRV_PRE_CHANNEL0; preCh < PDBDRV_PRE_CH_NUMBER; preCh++)
        {
            userConfig->preTrgCfg.mode[ch][preCh] = PDBDRV_PRETRG_DISABLE;
            userConfig->dlyCfg.dlyCnt[ch][preCh]  = 0;
        }
    }
    userConfig->preTrgCfg.mode[0][0] = PDBDRV_PRETRG_BYPASSED_MODE;

    for(poCh = PDBDRV_PO_CHANNEL0; poCh < PDBDRV_PO_CH_NUMBER; poCh++)
    {
        userConfig->poCfg.poen[poCh] = false;
        userConfig->poCfg.dly1[poCh] = 0;
        userConfig->poCfg.dly2[poCh] = 0;
    }

    userConfig->bbSel = 0;
}

void PdbDrv_Configure(PdbDrvType *obj, const PdbDrv_ConfigType *userConfig)
{
    PdbDrv_ChType    ch;
    PdbDrv_PreChType preCh;
    PdbDrv_PoChType  poCh;

    /* Disable PDB */
    PdbDrv_PdbDisable(obj);

    /* Delay count configuration */
    PdbReg_SetModReg(obj->pdbReg, userConfig->dlyCfg.modCnt);
    PdbReg_SetIdlyReg(obj->pdbReg, userConfig->dlyCfg.idlyCnt);
    for(ch = PDBDRV_CHANNEL0; ch < PDBDRV_CH_NUMBER; ch++)
    {
        for(preCh = PDBDRV_PRE_CHANNEL0; preCh < PDBDRV_PRE_CH_NUMBER; preCh++)
        {
            PdbReg_SetChnDlyReg(obj->pdbReg, userConfig->dlyCfg.dlyCnt[ch][preCh], ch, preCh);
        }
    }

    /* Pre-trigger channel configuration */
    PdbDrv_ConfigPreTrg(obj, &userConfig->preTrgCfg);

    /* General configuration*/
    PdbReg_SetPdbeieReg(obj->pdbReg, (uint8_t)userConfig->pdbeie);
    PdbReg_SetDmaenReg(obj->pdbReg, (uint8_t)userConfig->dmaen);
    PdbReg_SetPrescalerReg(obj->pdbReg, userConfig->prescalerFactor);
    PdbReg_SetTrgselReg(obj->pdbReg, (uint8_t)userConfig->trgInSel);
    PdbReg_SetPdbieReg(obj->pdbReg, (uint8_t)userConfig->pdbie);
    PdbReg_SetMultReg(obj->pdbReg, userConfig->mult);
    PdbReg_SetContReg(obj->pdbReg, (uint8_t)userConfig->cMode);

    /* Pulse out configuration*/
    uint8_t poen = 0;

    for(poCh = PDBDRV_PO_CHANNEL0; poCh < PDBDRV_PO_CH_NUMBER; poCh++)
    {
        uint32_t tmp;
        tmp = (userConfig->poCfg.dly1[poCh] << PDB_POnDLY_DLY1_SHIFT) | (userConfig->poCfg.dly2[poCh] << PDB_POnDLY_DLY2_SHIFT);

        /*! \note dly1 & dly2 need at the same time to write*/
        PdbReg_SetPonDlyReg(obj->pdbReg, tmp, poCh);

        if(userConfig->poCfg.poen[poCh])
        {
            poen |= PDBDRV_PO_ENABLE << poCh;
        }
    }
    PdbReg_SetPoenReg(obj->pdbReg, poen);

    /* Selects ADC COCO source as PDB back-to-back mode */
    SimReg_SetPdbBbSel(obj->simReg, userConfig->bbSel);

    /* Load delay count first*/
    PdbDrv_EnablePdb(obj);
    PdbReg_SetLdmodReg(obj->pdbReg, (uint8_t)PDBDRV_LDMOD_LOAD_VAL_IMMEDIATELY);
    PdbDrv_LoadCmd(obj);
    PdbDrv_PdbDisable(obj);

    /* Load mode configuration */
    PdbReg_SetLdmodReg(obj->pdbReg, (uint8_t)userConfig->ldmode);

    /*! \note When enable PDB depend on user(use PdbDrv_EnablePdb for enable PDB)*/
}

void PdbDrv_GetConfig(const PdbDrvType *obj, PdbDrv_ConfigType *userConfig)
{
    PdbDrv_ChType    ch;
    PdbDrv_PreChType preCh;
    PdbDrv_PoChType  poCh;

    /* Get general configuration */
    userConfig->ldmode          = (PdbDrv_LdmodType) (PdbReg_GetLdmodReg(obj->pdbReg));
    userConfig->pdbeie          = PdbReg_GetPdbeieReg(obj->pdbReg);
    userConfig->dmaen           = PdbReg_GetDmaenReg(obj->pdbReg);
    userConfig->prescalerFactor = (PdbDrv_PrescalerType) PdbReg_GetPrescalerReg(obj->pdbReg);
    userConfig->trgInSel        = (PdbDrv_TrgselType) PdbReg_GetTrgselReg(obj->pdbReg);
    userConfig->pdbie           = PdbReg_GetPdbieReg(obj->pdbReg);
    userConfig->mult            = (PdbDrv_MultFactorType) PdbReg_GetMultReg(obj->pdbReg);
    userConfig->cMode           = (PdbDrv_ContType) PdbReg_GetContReg(obj->pdbReg);

    /* Get pre-trigger channel configuration */
    PdbDrv_PreTrgType preTrgCfg;
    PdbDrv_GetPreTrgCfg(obj, &preTrgCfg);

    /* Get delay count configuration */
    userConfig->dlyCfg.modCnt  = PdbReg_GetModReg(obj->pdbReg);
    userConfig->dlyCfg.idlyCnt = PdbReg_GetIdlyReg(obj->pdbReg);
    for(ch = PDBDRV_CHANNEL0; ch < PDBDRV_CH_NUMBER; ch++)
    {
        for(preCh = PDBDRV_PRE_CHANNEL0; preCh < PDBDRV_PRE_CH_NUMBER; preCh++)
        {
            userConfig->dlyCfg.dlyCnt[ch][preCh]  = PdbReg_GetChnDlyReg(obj->pdbReg, ch, preCh);
            userConfig->preTrgCfg.mode[ch][preCh] = preTrgCfg.mode[ch][preCh];
        }
    }

    /* Get pulse out configuration */
    uint8_t poen = PdbReg_GetPoenReg(obj->pdbReg);
    for(poCh = PDBDRV_PO_CHANNEL0; poCh < PDBDRV_PO_CH_NUMBER; poCh++)
    {
        userConfig->poCfg.poen[poCh] = (poen >> poCh) & PDBDRV_PO_ENABLE;
        userConfig->poCfg.dly1[poCh] = PdbReg_GetPonDly1Reg(obj->pdbReg, poCh);
        userConfig->poCfg.dly2[poCh] = PdbReg_GetPonDly2Reg(obj->pdbReg, poCh);
    }

    /* Selects ADC COCO source as PDB back-to-back mode */
    userConfig->bbSel = SimReg_GetPdbBbSel(obj->simReg);
}

void PdbDrv_ConfigDly(PdbDrvType *obj, const PdbDrv_DlyCfgType *userConfig)
{
    PdbDrv_ChType    ch;
    PdbDrv_PreChType preCh;

    /* Delay count configuration */
    PdbReg_SetModReg(obj->pdbReg, userConfig->modCnt);
    PdbReg_SetIdlyReg(obj->pdbReg, userConfig->idlyCnt);
    for(ch = PDBDRV_CHANNEL0; ch < PDBDRV_CH_NUMBER; ch++)
    {
        for(preCh = PDBDRV_PRE_CHANNEL0; preCh < PDBDRV_PRE_CH_NUMBER; preCh++)
        {
            PdbReg_SetChnDlyReg(obj->pdbReg, userConfig->dlyCnt[ch][preCh], ch, preCh);
        }
    }

    /*! \note When effective delay count depend on user & load mode(use PdbDrv_LoadCmd for load)*/
}

void PdbDrv_GetConfigDly(const PdbDrvType *obj, PdbDrv_DlyCfgType *userConfig)
{
    PdbDrv_ChType    ch;
    PdbDrv_PreChType preCh;

    /* Get delay count configuration */
    userConfig->modCnt  = PdbReg_GetModReg(obj->pdbReg);
    userConfig->idlyCnt = PdbReg_GetIdlyReg(obj->pdbReg);
    for(ch = PDBDRV_CHANNEL0; ch < PDBDRV_CH_NUMBER; ch++)
    {
        for(preCh = PDBDRV_PRE_CHANNEL0; preCh < PDBDRV_PRE_CH_NUMBER; preCh++)
        {
            userConfig->dlyCnt[ch][preCh] = PdbReg_GetChnDlyReg(obj->pdbReg, ch, preCh);
        }
    }

    /*! \note When effective delay count depend on user(use PdbDrv_LoadCmd for load)*/
}

void PdbDrv_ConfigPo(PdbDrvType *obj, const PdbDrv_PoCfgType *userConfig)
{
    PdbDrv_PoChType poCh;

    /* Pulse out configuration */

    uint8_t poen = 0;
    for(poCh = PDBDRV_PO_CHANNEL0; poCh < PDBDRV_PO_CH_NUMBER; poCh++)
    {
        uint32_t tmp;
        tmp = (userConfig->dly1[poCh] << PDB_POnDLY_DLY1_SHIFT) | (userConfig->dly2[poCh] << PDB_POnDLY_DLY2_SHIFT);
        PdbReg_SetPonDlyReg(obj->pdbReg, tmp, poCh);
        if(userConfig->poen[poCh])
        {
            poen |= PDBDRV_PO_ENABLE << poCh;
        }
    }
    PdbReg_SetPoenReg(obj->pdbReg, poen);

    /*! \note When effective delay count depend on user & load mode(use PdbDrv_LoadCmd for load)*/
}

void PdbDrv_GetConfigPo(const PdbDrvType *obj, PdbDrv_PoCfgType *userConfig)
{
    PdbDrv_PoChType poCh;

    /* Pulse out configuration */
    uint8_t poen = 0;
    poen         = PdbReg_GetPoenReg(obj->pdbReg);
    for(poCh = PDBDRV_PO_CHANNEL0; poCh < PDBDRV_PO_CH_NUMBER; poCh++)
    {
        userConfig->dly1[poCh] = PdbReg_GetPonDly1Reg(obj->pdbReg, poCh);
        userConfig->dly2[poCh] = PdbReg_GetPonDly2Reg(obj->pdbReg, poCh);
        uint8_t poChPoen       = (poen >> poCh) & PDBDRV_PO_ENABLE;
        if(poChPoen == 1U)
        {
            userConfig->poen[poCh] = true;
        }
    }
}
