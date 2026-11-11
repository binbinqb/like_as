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

#include "mpu_drv.h"
#include "mpu_reg.h"

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

void MpuDrv_Init(MpuDrvType *obj, struct _MpuRegType_ *reg)
{
    obj->reg = reg;
}

void MpuDrv_GetDefaultConfig(MpuDrv_ConfigType *userConfig)
{
    uint8_t regDescNum;
    uint8_t masterNum;
    uint8_t slvPortNum;

    /* mpu PID is used, default: false */
    userConfig->isEnableErrPid = false;
    /* mpu main switch, default: enable */
    userConfig->ctrlInfo.mpuValid = true;
    /* region description total num, default: 16 */
    userConfig->ctrlInfo.mpuTotalNumRegDesc = MPUDRV_NUMOFRGD_16;

    /* mpu control info */
    for(slvPortNum = 0; slvPortNum < MPUDRV_SLVPORTMAX; slvPortNum++)
    {
        /* slave port error status, default: false */
        userConfig->ctrlInfo.slvPortErrStatus[slvPortNum] = false;

        /*
         * slave port default info
         */

        /* slave port access master number */
        userConfig->slvPortErrInfo->master = (MpuDrv_MasterType)0;
        /* salve port error PID number,default: 0 */
        userConfig->slvPortErrInfo->pidNumber = 0;
        /* salve port access mode, default: user mode */
        userConfig->slvPortErrInfo->attrbutes = MPUDRV_INSTRUCTION_ACCESS_IN_USER_MODE;
        /* slave port access type, default: read mode */
        userConfig->slvPortErrInfo->accType = MPUDRV_ERRTYPE_READ;
        /* salve port access error claw(EACD), default: 0 */
        userConfig->slvPortErrInfo->accCtrl = 0;
        /* salve port error address, when master access fault,default: 0 */
        userConfig->slvPortErrInfo->addr = 0;
    }

    /* region description default configure */
    for(regDescNum = 0; regDescNum < MPUDRV_CHMAX; regDescNum++)
    {
        /* region description channel 0 default all rights allow */
        if(regDescNum == 0)
        {
            /* RGD channel 0 tatus, mpu functions, default: enable */
            userConfig->regDescCfgInfo[regDescNum].chnEnable = true;
            /* RGD channel 0 start address, default: 0 */
            userConfig->regDescCfgInfo[regDescNum].startAddr = 0;
            /* RGD channel 0 end address, default: 0xFFFFFF1F */
            userConfig->regDescCfgInfo[regDescNum].endAddr = 0xFFFFFF1F;
            /* RGD channel 0 PID mask number, default: 0 */
            userConfig->regDescCfgInfo[regDescNum].pidMask = 0;
            /* RGD channel 0 PID number, default: 0 */
            userConfig->regDescCfgInfo[regDescNum].pidNumber = 0;

            for(masterNum = 0; masterNum < MPUDRV_MASTER_NUMMAX; masterNum++)
            {
                /* RGD master in privilege mode access right, default: same as user */
                userConfig->regDescCfgInfo[regDescNum].masterAccRight[masterNum].masterPrivilegeAccRight = MPUDRV_SUPERVISOR_SAME_AS_USER;
                /* RGD master in user mode access right, default: RWX allow */
                userConfig->regDescCfgInfo[regDescNum].masterAccRight[masterNum].masterUserAccRight = MPUDRV_USER_RWX;
                /* RGD master PID enable flag, default: false */
                userConfig->regDescCfgInfo[regDescNum].masterAccRight[masterNum].pidFlagEnable = false;

                /*
                 * Alternate Access Control channel 0 default all rights allow
                 */

                /* AAC channel 0 onfig master in privilege mode access right, default: same as user */
                userConfig->aacCfgInfo[regDescNum].masterPrivilegeAccRight = MPUDRV_SUPERVISOR_SAME_AS_USER;
                /* AAC channel 0 config master in user mode access right, default: RWX allow */
                userConfig->aacCfgInfo[regDescNum].masterUserAccRight = MPUDRV_USER_RWX;
                /* AAC channel 0 config master PID enable flag, default: false */
                userConfig->aacCfgInfo[regDescNum].pidFlagEnable = false;
            }
        }
        else
        {
            /*
             * region description channel 1~15 default all rights forbidden
             */

            /* RGD channel 1~15 tatus, mpu functions, default: disable */
            userConfig->regDescCfgInfo[regDescNum].chnEnable = false;
            /* RGD channel 1~15 start address, default: 0 */
            userConfig->regDescCfgInfo[regDescNum].startAddr = 0;
            /* RGD channel 1~15 end address, default: 0x0 */
            userConfig->regDescCfgInfo[regDescNum].endAddr = 0x1F;
            /* RGD channel 1~15 PID mask number, default: 0 */
            userConfig->regDescCfgInfo[regDescNum].pidMask = 0;
            /* RGD channel 1~15  PID number, default: 0 */
            userConfig->regDescCfgInfo[regDescNum].pidNumber = 0;

            for(masterNum = 0; masterNum < MPUDRV_MASTER_NUMMAX; masterNum++)
            {
                /* RGD master in privilege mode access right, default: RWX allow */
                userConfig->regDescCfgInfo[regDescNum].masterAccRight[masterNum].masterPrivilegeAccRight = MPUDRV_SUPERVISOR_RWX;
                /* RGD master in user mode access right, default: none */
                userConfig->regDescCfgInfo[regDescNum].masterAccRight[masterNum].masterUserAccRight = MPUDRV_USER_NONE;
                /* RGD master PID enable flag, default: false */
                userConfig->regDescCfgInfo[regDescNum].masterAccRight[masterNum].pidFlagEnable = false;

                /*
                 * Alternate Access Control channel 1~15 default all rights forbidden
                 */

                /* AAC channel 1~15 onfig master in privilege mode access right, default: RWX allow */
                userConfig->aacCfgInfo[regDescNum].masterPrivilegeAccRight = MPUDRV_SUPERVISOR_RWX;
                /* AAC channel 1~15 config master in user mode access right, default: none */
                userConfig->aacCfgInfo[regDescNum].masterUserAccRight = MPUDRV_USER_NONE;
                /* AAC channel 1~15 config master PID enable flag, default: false */
                userConfig->aacCfgInfo[regDescNum].pidFlagEnable = false;
            }
        }
    }
}

void MpuDrv_GetCtrlInfo(MpuDrvType *obj, MpuDrv_CtrlInfoType *ctrlInfo)
{
    uint8_t slvPortNum;

    for(slvPortNum = 0; slvPortNum < MPUDRV_SLVPORTMAX; slvPortNum++)
    {
        /* get slave port error info */
        ctrlInfo->slvPortErrStatus[slvPortNum] = MpuReg_GetSlvPortErrStatus(obj->reg, slvPortNum);
    }
    /* get total number of region description */
    ctrlInfo->mpuTotalNumRegDesc = (MpuDrv_RegDescTotalNumType)MpuReg_GetNumOfRegionDesc(obj->reg);
    /* get MPU global enable status */
    ctrlInfo->mpuValid = MpuReg_GetMpuGlobalEnableStatus(obj->reg);
}

__attribute__((always_inline)) static inline MpuDrv_MasterType MpuDrv_SlvPortEMNtoMaster(uint8_t emn)
{
    switch(emn)
    {
        case 0:
        case 2:
        case 3:
            return MPUDRV_MASTER_CPU;
        case 1:
            return MPUDRV_MASTER_DEBUGGER;
        case 4:
            return MPUDRV_MASTER_DMA;
        case 5:
            return MPUDRV_MASTER_CSE;
        default:
            return MPUDRV_MASTER_NUMMAX;
    }
}


void MpuDrv_GetSlvPortErrInfo(MpuDrvType *obj, MpuDrv_SlvPortErrInfoType *slvPortErrInfo, bool isEnablePid)
{
    uint8_t slvPortNum;

    for(slvPortNum = 0; slvPortNum < MPUDRV_SLVPORTMAX; slvPortNum++)
    {
        /* get slave port error access detail info */
        slvPortErrInfo[slvPortNum].accCtrl = MpuReg_GetSlvPortEACD(obj->reg, slvPortNum);
        /* get slave port error type R/W */
        slvPortErrInfo[slvPortNum].accType = (MpuDrv_AccType)MpuReg_GetSlvPortErrDetailERW(obj->reg, slvPortNum);
        /* get slave port error type master number */
        slvPortErrInfo[slvPortNum].master = (MpuDrv_MasterType)MpuDrv_SlvPortEMNtoMaster(MpuReg_GetSlvPortErrDetailEMN(obj->reg, slvPortNum));
        /* get slave port error attribute */
        slvPortErrInfo[slvPortNum].attrbutes = (MpuDrv_AttrType)MpuReg_GetSlvPortErrDetailEAttr(obj->reg, slvPortNum);
        /* get slave port error address */
        slvPortErrInfo[slvPortNum].addr = MpuReg_GetSlvPortErrAddr(obj->reg, slvPortNum);

        if(isEnablePid)
        {
            /* get slave port error PID */
            slvPortErrInfo[slvPortNum].pidNumber = MpuReg_GetSlvPortErrPID(obj->reg, slvPortNum);
        }
    }
}

void MpuDrv_GetMasterAccRight(MpuDrvType                 *obj,
                              MpuDrv_MasterAccConfigType *masterAccRight,
                              MpuDrv_RegDescChnNumType    regDescNum,
                              MpuDrv_MasterType           masterNum)
{
    /* get master privilege mode access right */
    masterAccRight[masterNum].masterPrivilegeAccRight = (MpuDrv_MasterPrivilegeAccType)MpuReg_GetRegionDescPrivilegeAuthority(obj->reg, regDescNum, masterNum);
    /* get master user mode access right */
    masterAccRight[masterNum].masterUserAccRight = (MpuDrv_MasterUserAccType)MpuReg_GetRegionDescUserAuthority(obj->reg, regDescNum, masterNum);
    /* get master PID enable status (Only master0 & master1) */
    masterAccRight[masterNum].pidFlagEnable = MpuReg_GetRegionDescPIDFlagEnableStatus(obj->reg, regDescNum, masterNum);
}

void MpuDrv_GetRegDescCfgInfo(MpuDrvType *obj, MpuDrv_RegDescType *regDesc, bool isEnablePid)
{
    uint8_t regDescNum;
    uint8_t masterNum;

    for(regDescNum = 0; regDescNum < MPUDRV_CHMAX; regDescNum++)
    {
        /* get region description current channel start address */
        regDesc[regDescNum].startAddr = MpuReg_GetRegionDescStartAddr(obj->reg, regDescNum);
        /* get region description current channel end address */
        regDesc[regDescNum].endAddr = MpuReg_GetRegionDescEndAddr(obj->reg, regDescNum);

        for(masterNum = 0; masterNum < MPUDRV_MASTER_NUMMAX; masterNum++)
        {
            /* get region description current channel master accsee right */
            MpuDrv_GetMasterAccRight(obj, &regDesc[regDescNum].masterAccRight[masterNum], (MpuDrv_RegDescChnNumType)regDescNum, (MpuDrv_MasterType)masterNum);
        }

        if(isEnablePid)
        {
            /* get region description current channel PID */
            regDesc[regDescNum].pidNumber = MpuReg_GetPID(obj->reg, regDescNum);
            /* get region description current channel PIDMask */
            regDesc[regDescNum].pidMask = MpuReg_GetPIDMask(obj->reg, regDescNum);
        }
    }
}

void MpuDrv_GetAacCtrlInfo(MpuDrvType *obj, MpuDrv_MasterAccConfigType *aacRegDesc)
{
    uint8_t regDescNum;
    uint8_t masterNum;

    for(regDescNum = 0; regDescNum < MPUDRV_CHMAX; regDescNum++)
    {
        for(masterNum = 0; masterNum < MPUDRV_MASTER_NUMMAX; masterNum++)
        {
            /* get AAC config master privilege mode access right */
            aacRegDesc[masterNum].masterPrivilegeAccRight = (MpuDrv_MasterPrivilegeAccType)MpuReg_GetRegionDescAACPrivilegeAuthority(obj->reg, regDescNum, masterNum);
            /* get AAC config master user mode access right */
            aacRegDesc[masterNum].masterUserAccRight = (MpuDrv_MasterUserAccType)MpuReg_GetRegionDescAACUserAuthority(obj->reg, regDescNum, masterNum);
            /* get AAC config master PID enable status (Only master0 & master1) */
            aacRegDesc[masterNum].pidFlagEnable = MpuReg_GetRegionDescAACPIDFlagEnableStatus(obj->reg, regDescNum, masterNum);
        }
    }
}

void MpuDrv_GetConfigure(MpuDrvType *obj, MpuDrv_ConfigType *userConfig)
{
    /* get common part control info */
    MpuDrv_GetCtrlInfo(obj, &userConfig->ctrlInfo);
    /* get slave port error info */
    MpuDrv_GetSlvPortErrInfo(obj, (MpuDrv_SlvPortErrInfoType *)&userConfig->slvPortErrInfo, userConfig->isEnableErrPid);
    /* get region description config info */
    MpuDrv_GetRegDescCfgInfo(obj, (MpuDrv_RegDescType *)&userConfig->regDescCfgInfo, userConfig->isEnableErrPid);
    /* get alternate access config info   */
    MpuDrv_GetAacCtrlInfo(obj, (MpuDrv_MasterAccConfigType *)&userConfig->aacCfgInfo);
}

static void MpuDrv_SetMasterAccRight(MpuDrvType                 *obj,
                                     MpuDrv_MasterAccConfigType *masterAccRight,
                                     MpuDrv_RegDescChnNumType    regDescChnNum,
                                     MpuDrv_MasterType           masterNum)
{
    /* set master privilege mode access right */
    MpuReg_SetRegionDescPrivilegeAuthority(obj->reg, regDescChnNum, masterNum, masterAccRight[masterNum].masterPrivilegeAccRight);
    /* set master user mode access right */
    MpuReg_SetRegionDescUserAuthority(obj->reg, regDescChnNum, masterNum, masterAccRight[masterNum].masterUserAccRight);
    /* set master PID enable status (Only master0 & master1) */
    MpuReg_SetRegionDescPIDFlagEnable(obj->reg, regDescChnNum, masterNum, masterAccRight[masterNum].pidFlagEnable);
}

void MpuDrv_EnableRegDescChn(MpuDrvType *obj, MpuDrv_RegDescChnNumType chnNum, bool enable)
{
    /* set region description channle enable */
    MpuReg_SetRegionDescValid(obj->reg, chnNum, enable);
}

void MpuDrv_SetRegDescChnCfg(MpuDrvType              *obj,
                             const MpuDrv_RegDescType      *regDescCfg,
                             MpuDrv_RegDescChnNumType regDescChnNum,
                             bool                     pidEnable)
{
    uint8_t masterNum;

    /* set region description start address */
    MpuReg_SetRegionDescStartAddr(obj->reg, regDescCfg->startAddr, regDescChnNum);
    /* set region description end address */
    MpuReg_SetRegionDescEndAddr(obj->reg, regDescCfg->endAddr, regDescChnNum);

    for(masterNum = 0; masterNum < MPUDRV_MASTER_NUMMAX; masterNum++)
    {
        /* set region description master access right */
        MpuDrv_SetMasterAccRight(obj, (MpuDrv_MasterAccConfigType *)&regDescCfg->masterAccRight, (MpuDrv_RegDescChnNumType)regDescChnNum, (MpuDrv_MasterType)masterNum);
        if(masterNum < MPUDRV_MASTER_DMA)
        {
            /* set region description pid enable */
            MpuReg_SetRegionDescPIDFlagEnable(obj->reg, regDescChnNum, masterNum, pidEnable);
        }
    }

    MpuDrv_EnableRegDescChn(obj, regDescChnNum, regDescCfg->chnEnable);
}

void MpuDrv_SetAacCtrlInfo(MpuDrvType                 *obj,
                           MpuDrv_MasterAccConfigType *aacRegDesc,
                           MpuDrv_RegDescChnNumType    regDescChnNum,
                           MpuDrv_MasterType           masterNum)
{
    if(regDescChnNum >= MPUDRV_CHMAX || masterNum >= MPUDRV_MASTER_NUMMAX)
    {
        return;
    }

    /* set AAC config master privilege mode access right */
    MpuReg_SetRegionDescAACPrivilegeAuthority(obj->reg, regDescChnNum, masterNum, aacRegDesc->masterPrivilegeAccRight);
    /* set AAC config master user mode access right */
    MpuReg_SetRegionDescAACUserAuthority(obj->reg, regDescChnNum, masterNum, aacRegDesc->masterUserAccRight);
    /* set AAC config master PID enable status (Only master0 & master1) */
    MpuReg_SetRegionDescAACPIDFlagEnable(obj->reg, regDescChnNum, masterNum, aacRegDesc->pidFlagEnable);
}

bool MpuDrv_GetGlobalEnableStatus(MpuDrvType *obj)
{
    /* Get MPU Enable status */
    return MpuReg_GetMpuGlobalEnableStatus(obj->reg);
}

void MpuDrv_SetGlobalEnable(MpuDrvType *obj, bool enable)
{
    /* Set MPU global Enable status */
    MpuReg_GlobalEnable(obj->reg, enable);
}
