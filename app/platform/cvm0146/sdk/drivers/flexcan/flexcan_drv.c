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

#include <math.h>
#include <stddef.h>
#include "flexcan_drv.h"

/*******************************************************************************
 * the defines
 ******************************************************************************/

#define FLEXCAN_DRV_CAN_RAM_SIZE     (512U)

#define TX_PENDING_ABORT_SUCCESS     (1)
#define TX_PENDING_ABORT_NO_TRANSFER (0)
#define TX_PENDING_ABORT_FAILED      (0xFFU)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the functions
 ******************************************************************************/

static inline uint8_t FlexCanDrv_ConvertMsgBufSizeSel(uint8_t MBSizeCode)
{
    uint8_t result = 0;

    switch(MBSizeCode)
    {
    case FLEXCANDRV_MB_SIZE_BYTE_8:
        result = 16;
        break;
    case FLEXCANDRV_MB_SIZE_BYTE_16:
        result = 24;
        break;
    case FLEXCANDRV_MB_SIZE_BYTE_32:
        result = 40;
        break;
    case FLEXCANDRV_MB_SIZE_BYTE_64:
        result = 72;
        break;
    }

    return result;
}

static inline uint32_t FlexCanDrv_GetMsgBufStartAddr(FlexCanDrvType *obj, uint16_t msgBufId)
{
    /* get the first message buffer start address */
    uint32_t addr       = FlexCanReg_GetMsgBufferStartAddr(obj->flexCanReg);
    uint8_t  msgBufSize = 0;

    /* get the message buffer size */
    uint8_t msgBufSizeSel = FlexCanReg_GetRegionDataSizeSel(obj->flexCanReg, 0);

    msgBufSize = FlexCanDrv_ConvertMsgBufSizeSel(msgBufSizeSel) / 4;

    if(msgBufSizeSel == FLEXCANDRV_MB_SIZE_BYTE_8)
    {
        addr += (msgBufSize * msgBufId) * 4;
    }
    else if(msgBufSizeSel == FLEXCANDRV_MB_SIZE_BYTE_16)
    {
        addr += (msgBufSize * msgBufId + (2 * (msgBufId / 21))) * 4;
    }
    else if(msgBufSizeSel == FLEXCANDRV_MB_SIZE_BYTE_32)
    {
        addr += (msgBufSize * msgBufId + (8 * (msgBufId / 12))) * 4;
    }
    else
    {
        addr += (msgBufSize * msgBufId + (2 * (msgBufId / 7))) * 4;
    }

    return addr;
}

static inline uint8_t FlexCanDrv_DLC2DataLen(FlexCanDrv_DLCType dlc)
{
    uint8_t dataLen = 0;

    switch(dlc)
    {
    case DLC_BYTE_0:
    case DLC_BYTE_1:
    case DLC_BYTE_2:
    case DLC_BYTE_3:
    case DLC_BYTE_4:
    case DLC_BYTE_5:
    case DLC_BYTE_6:
    case DLC_BYTE_7:
    case DLC_BYTE_8:
        dataLen = (uint8_t)dlc;
        break;
    case DLC_BYTE_12:
        dataLen = 12;
        break;
    case DLC_BYTE_16:
        dataLen = 16;
        break;
    case DLC_BYTE_20:
        dataLen = 20;
        break;
    case DLC_BYTE_24:
        dataLen = 24;
        break;
    case DLC_BYTE_32:
        dataLen = 32;
        break;
    case DLC_BYTE_48:
        dataLen = 48;
        break;
    case DLC_BYTE_64:
        dataLen = 64;
        break;
    default:
        break;
    }

    return dataLen;
}

static inline uint8_t FlexCanDrv_GetMsgBufDataLen(FlexCanDrvType *obj, uint16_t msgBufId)
{
    uint32_t *msgBufPtr;
    uint8_t   dlc     = 0;
    uint8_t   dataLen = 0;

    /* get current message buffer start address */
    msgBufPtr = (uint32_t *)FlexCanDrv_GetMsgBufStartAddr(obj, msgBufId);

    /* get DLC code from message buffer */
    dlc = (*msgBufPtr & MESSAGE_BUFFER_CS_DLC_MASK) >> MESSAGE_BUFFER_CS_DLC_SHIFT;

    /* convert DLC code to data length */
    dataLen = FlexCanDrv_DLC2DataLen((FlexCanDrv_DLCType)dlc);

    return dataLen;
}

static inline void FlexCanDrv_SetMsgId(uint32_t *msgBufPtr, uint32_t msgId, bool isExt)
{
    uint32_t tempVar = 0;

    if(isExt)
    {
        /* set extended message ID bit (IDE) */
        msgBufPtr[MESSAGE_BUFFER_CS_WORD_NUM] |= (MESSAGE_BUFFER_CS_IDE_MASK | MESSAGE_BUFFER_CS_SRR_MASK);

        /* set extended message ID */
        tempVar = msgBufPtr[MESSAGE_BUFFER_ID_WORD_NUM];
        tempVar &= ~(MESSAGE_BUFFER_ID_EXT_ID_MASK);
        tempVar |= ((msgId << MESSAGE_BUFFER_ID_EXT_ID_SHIFT) & MESSAGE_BUFFER_ID_EXT_ID_MASK);
        msgBufPtr[MESSAGE_BUFFER_ID_WORD_NUM] = tempVar;
    }
    else
    {
        /* clear extended message ID bit (IDE) */
        msgBufPtr[MESSAGE_BUFFER_CS_WORD_NUM] &= ~(MESSAGE_BUFFER_CS_IDE_MASK | MESSAGE_BUFFER_CS_SRR_MASK);

        /* load standard message ID */
        tempVar = msgBufPtr[MESSAGE_BUFFER_ID_WORD_NUM];
        tempVar &= ~(MESSAGE_BUFFER_ID_STD_ID_MASK);
        tempVar |= ((msgId << MESSAGE_BUFFER_ID_STD_ID_SHIFT) & MESSAGE_BUFFER_ID_STD_ID_MASK);
        msgBufPtr[MESSAGE_BUFFER_ID_WORD_NUM] = tempVar;
    }
}

static inline void FlexCanDrv_SetMsgDLC(uint32_t *msgBufPtr, FlexCanDrv_DLCType dlc)
{
    msgBufPtr[MESSAGE_BUFFER_CS_WORD_NUM] &= (~MESSAGE_BUFFER_CS_DLC_MASK);
    msgBufPtr[MESSAGE_BUFFER_CS_WORD_NUM] |= (((uint32_t)dlc) << MESSAGE_BUFFER_CS_DLC_SHIFT & MESSAGE_BUFFER_CS_DLC_MASK);
}

static inline void FlexCanDrv_SetFDEnable(uint32_t *msgBufPtr, bool fdEnable)
{
    /* clear EDL bit */
    msgBufPtr[MESSAGE_BUFFER_CS_WORD_NUM] &= (~MESSAGE_BUFFER_CS_EDL_MASK);
    /* clear BRS bit */
    msgBufPtr[MESSAGE_BUFFER_CS_WORD_NUM] &= (~MESSAGE_BUFFER_CS_BRS_MASK);

    if(fdEnable)
    {
        /* set EDL bit */
        msgBufPtr[MESSAGE_BUFFER_CS_WORD_NUM] |= MESSAGE_BUFFER_CS_EDL_MASK;
        /* set BRS bit */
        msgBufPtr[MESSAGE_BUFFER_CS_WORD_NUM] |= MESSAGE_BUFFER_CS_BRS_MASK;
    }
    else
    {
        /* non CAN-FD keep EDL, BRS bit clear */
    }
}

static inline void FlexCanDrv_SetMsgType(uint32_t *msgBufPtr, FlexCanDrv_MsgType_t msgType)
{
    if(msgType == FLEXCANDRV_MSGTYPE_TX)
    {
        /* tx message set CODE as INACTIVE */
        msgBufPtr[MESSAGE_BUFFER_CS_WORD_NUM] &= (~MESSAGE_BUFFER_CS_CODE_MASK);
        msgBufPtr[MESSAGE_BUFFER_CS_WORD_NUM] |= ((FLEXCANDRV_MSG_BUF_CODE_INACTIVE << MESSAGE_BUFFER_CS_CODE_SHIFT) & MESSAGE_BUFFER_CS_CODE_MASK);
    }
    else if(msgType == FLEXCANDRV_MSGTYPE_RX)
    {
        /* rx message set CODE as RX_ACTIVE */
        msgBufPtr[MESSAGE_BUFFER_CS_WORD_NUM] &= (~MESSAGE_BUFFER_CS_CODE_MASK);
        msgBufPtr[MESSAGE_BUFFER_CS_WORD_NUM] |= ((FLEXCANDRV_MSG_BUF_CODE_RX_ACTIVE << MESSAGE_BUFFER_CS_CODE_SHIFT) & MESSAGE_BUFFER_CS_CODE_MASK);
    }
    else
    {
    }
}

/* BCM CAN-05: sticky failure belongs to this controller, never a global. */
static bool FlexCanDrv_WaitExpired(FlexCanDrvType *obj)
{
    if (obj->waitFailed)
    {
        return true;
    }
    if ((obj->waitExpired != 0) && obj->waitExpired(obj->waitContext))
    {
        obj->waitFailed = true;
    }
    return obj->waitFailed;
}

static inline bool FlexCanDrv_EnableCanCfgClk(FlexCanDrvType *obj)
{
    if(PccReg_GetLockStLock(obj->pccReg) != 0u)
    {
        /* unlock PCC key */
        PccReg_SetLockKey(obj->pccReg, 0x70637577);

        while(PccReg_GetLockStLock(obj->pccReg) != 0u)
        {
            if (FlexCanDrv_WaitExpired(obj))
            {
                return false;
            }
        }
    }

    /* enable CAN CFG clock */
    if(obj->initHwPar.canInstanceIdx == 0)
    {
        PccReg_SetCkEn1CfgCan0(obj->pccReg, 1);
        if(PccReg_GetCkEn1CfgCan0(obj->pccReg) == 0)
        {
            PccReg_SetCkEn1CfgCan0(obj->pccReg, 1);
        }
    }
    else if(obj->initHwPar.canInstanceIdx == 1)
    {
        PccReg_SetCkEn1CfgCan1(obj->pccReg, 1);
    }
    else if(obj->initHwPar.canInstanceIdx == 2)
    {
        PccReg_SetCkEn1CfgCan2(obj->pccReg, 1);
    }
    else if(obj->initHwPar.canInstanceIdx == 3)
    {
        PccReg_SetCkEn1CfgCan3(obj->pccReg, 1);
    }
    return true;
}

static inline void FlexCanDrv_EnableCanOperationClk(FlexCanDrvType *obj)
{
    /* unlock PCC0 key */
    PccReg_SetLockKey(obj->pccReg, 0x70637577);

    /* enable CAN operation clock */
    if(obj->initHwPar.canInstanceIdx == 0)
    {
        PccReg_SetCkEn0Can0(obj->pccReg, 1);
        if(PccReg_GetCkEn0Can0(obj->pccReg) == 0)
        {
            PccReg_SetCkEn0Can0(obj->pccReg, 1);
        }
    }
    else if(obj->initHwPar.canInstanceIdx == 1)
    {
        PccReg_SetCkEn0Can1(obj->pccReg, 1);
    }
    else if(obj->initHwPar.canInstanceIdx == 2)
    {
        PccReg_SetCkEn0Can2(obj->pccReg, 1);
    }
    else if(obj->initHwPar.canInstanceIdx == 3)
    {
        PccReg_SetCkEn0Can3(obj->pccReg, 1);
    }
}

static inline void FlexCanDrv_InitCanRAM(FlexCanDrvType *obj)
{
    uint32_t *u32Ptr = (uint32_t *)FlexCanReg_GetMsgBufferStartAddr(obj->flexCanReg);
    uint32_t *tempPtr;
    uint32_t  i = 0;

    /* 0x80 - 0x880: message buffer 512 byte * 4 region */
    for(i = 0; i < 512; i++)
    {
        tempPtr  = (u32Ptr + i);
        *tempPtr = 0;
    }

    /* 0x880 - 0xA80: RXIMR Rx Individual Mask Registers 4 byte * 128 */
    for(i = 0; i < 128; i++)
    {
        tempPtr  = (u32Ptr + 512 + i);
        *tempPtr = 0;
    }

    /* 0xA80 - 0xAAC: RXFIR(0xA80 - A94) + RXMASK(0xAA0 - 0xAAC) */
    for(i = 0; i < 11; i++)
    {
        tempPtr  = (u32Ptr + 640 + i);
        *tempPtr = 0;
    }

    /* 0xAB0 - 0xADC: SMBs (normal CAN) */
    for(i = 0; i < 11; i++)
    {
        tempPtr  = (u32Ptr + 652 + i);
        *tempPtr = 0;
    }

    /* 0xF28 - 0xFFC: SMBs (CAN-FD) */
    for(i = 0; i < 53; i++)
    {
        tempPtr  = (u32Ptr + 938 + i);
        *tempPtr = 0;
    }

    /* 0x2000 - 0x2FFC: Enhance Rx FIFO(CAN-FD) */
    u32Ptr = (uint32_t *)FlexCanReg_GetEnhRxFifoStartAddr(obj->flexCanReg);
    for(i = 0; i < 640; i++)
    {
        tempPtr  = (u32Ptr + i);
        *tempPtr = 0;
    }

    /* 0x3000 - 0xFFC: Enhance Rx Filter element 0-127 (CAN-FD) */
    u32Ptr = (uint32_t *)FlexCanReg_GetEnhRxFifoFilterStartAddr(obj->flexCanReg, 0);
    for(i = 0; i < 128; i++)
    {
        tempPtr  = (u32Ptr + i);
        *tempPtr = 0;
    }
}

void FlexCanDrv_Init(FlexCanDrvType *obj, FlexCanRegType *flexCanReg, PccRegType *pccReg, ScgRegType *scgReg, SimRegType *simReg, FlexCanDrv_InitHwParType *initHwPar)
{
    obj->waitExpired = 0;
    obj->waitContext = (void *)0;
    obj->waitFailed = false;
    obj->initHwPar.canRamNum      = initHwPar->canRamNum;
    obj->initHwPar.canInstanceIdx = initHwPar->canInstanceIdx;
    obj->flexCanReg               = flexCanReg;
    obj->pccReg                   = pccReg;
    obj->scgReg                   = scgReg;
    obj->simReg                   = simReg;
}

void FlexCanDrv_GetDefaultCfg(FlexCanDrv_ControllerCfgType *controllerCfg)
{
    controllerCfg->bitTiming.prescalerDiv      = 0;
    controllerCfg->bitTiming.propSeg           = 0;
    controllerCfg->bitTiming.phaseSeg1         = 0;
    controllerCfg->bitTiming.phaseSeg2         = 0;
    controllerCfg->bitTiming.resyncJumpWidth   = 0;
    controllerCfg->fdBitTiming.prescalerDiv    = 0;
    controllerCfg->fdBitTiming.propSeg         = 0;
    controllerCfg->fdBitTiming.phaseSeg1       = 0;
    controllerCfg->fdBitTiming.phaseSeg2       = 0;
    controllerCfg->fdBitTiming.resyncJumpWidth = 0;
    controllerCfg->clkSrc                      = FLEXCANDRV_CLKSRC_CHICLK;
    controllerCfg->fifoEnable                  = 0;
    controllerCfg->dmaEnable                   = 0;
    controllerCfg->rxMBGlobalMask              = 0xFFFFFFFF;
    controllerCfg->rxMB14Mask                  = 0xFFFFFFFF;
    controllerCfg->rxMB15Mask                  = 0xFFFFFFFF;
    controllerCfg->individualMaskEnable        = 0;
    controllerCfg->fdEnable                    = 0;
    controllerCfg->fdISOEnable                 = 0;
    controllerCfg->msgBufDataLenSel            = FLEXCANDRV_MB_SIZE_BYTE_8;
    controllerCfg->loopbackEnable              = 0;
    controllerCfg->tdcEnable                   = 0;
    controllerCfg->tdcOffset                   = 0;
    controllerCfg->txAbortEnable               = 0;
    controllerCfg->edgeWkupEnable              = 0;
    controllerCfg->busoffIntEnable             = 0;
    controllerCfg->errorIntEnable              = 0;
    controllerCfg->msgNum                      = 0;
    controllerCfg->msgCfg                      = (void *)0;
}

void FlexCanDrv_Start(FlexCanDrvType *obj)
{
    /* set freeze mode disable */
    FlexCanReg_SetFreezeMode(obj->flexCanReg, false);
    /* set halt mode disable */
    FlexCanReg_SetHaltMode(obj->flexCanReg, false);

    /* wait for synchronization */
    while(FlexCanReg_GetFreezeAck(obj->flexCanReg))
    {
        if (FlexCanDrv_WaitExpired(obj))
        {
            return;
        }
    }
}

void FlexCanDrv_SoftReset(FlexCanDrvType *obj)
{
    /* check for low power mode */
    if(FlexCanReg_GetLowPowerAck(obj->flexCanReg))
    {
        /* Enable clock */
        FlexCanReg_SetModuleDisable(obj->flexCanReg, false);
        /* wait until enabled */
        while(FlexCanReg_GetLowPowerAck(obj->flexCanReg))
        {
            if (FlexCanDrv_WaitExpired(obj))
            {
                return;
            }
            /* enable CAN operation clock */
            FlexCanDrv_EnableCanOperationClk(obj);
        }
    }

    /* Reset the CAN module */
    FlexCanReg_SetSoftResetRequest(obj->flexCanReg, true);
    /* Wait for reset cycle to complete */
    while(FlexCanReg_GetSoftResetRequest(obj->flexCanReg))
    {
        if (FlexCanDrv_WaitExpired(obj))
        {
            return;
        }
    }

    /* set freeze mode enable */
    FlexCanReg_SetFreezeMode(obj->flexCanReg, true);
    /* set halt mode enable */
    FlexCanReg_SetHaltMode(obj->flexCanReg, true);

    /* check for freeze Ack */
    while((FlexCanReg_GetFreezeAck(obj->flexCanReg) == 0) || (FlexCanReg_GetNotReadyFlag(obj->flexCanReg) == 0))
    {
        if (FlexCanDrv_WaitExpired(obj))
        {
            return;
        }
        /* soft reset failed */
    }
}

void FlexCanDrv_CfgMsgObj(FlexCanDrvType *obj, const FlexCanDrv_MsgCfgType *msgCfg, uint8_t msgBufId)
{
    uint32_t             *msgBufPtr;

    /* get current message buffer start address */
    msgBufPtr = (uint32_t *)FlexCanDrv_GetMsgBufStartAddr(obj, msgBufId);

    /* set message ID */
    FlexCanDrv_SetMsgId(msgBufPtr, msgCfg->msgId, msgCfg->isExtMsgId);

    /* set message DLC */
    FlexCanDrv_SetMsgDLC(msgBufPtr, msgCfg->dlc);

    /* set FD configures */
    FlexCanDrv_SetFDEnable(msgBufPtr, msgCfg->isFd);

    /* set message type */
    FlexCanDrv_SetMsgType(msgBufPtr, msgCfg->msgType);

    if(msgCfg->intEnable)
    {
        /* set message buffer interrupt enable */
        FlexCanDrv_EnableMsgObjInterrupt(obj, msgBufId);
    }
    else
    {
        /* message buffer interrupt disable, do nothing */
    }

    if(msgCfg->msgType == FLEXCANDRV_MSGTYPE_RX)
    {
        /* set message buffer individual mask */
        FlexCanReg_SetRxIndividualMask(obj->flexCanReg, msgBufId, msgCfg->individualMask);
    }
}

static bool FlexCanDrv_SetEnhanceRxFifoFilterInMask(FlexCanDrvType *obj, const FlexCanDrv_ControllerCfgType *controllerCfg, uint8_t extIdNum, uint8_t stdIdNum)
{
    bool     rtn = false;
    uint8_t  alignedExtIdElementNum = 0, alignedStdIdElementNum = 0, nfe = 0, nexif = 0;
    uint32_t filter = 0, mask = 0, currentSdtIdNum = 0, currentExtIdNum = 0;
    uint16_t filterElementIdx = 0, i = 0;

    if((((extIdNum << 1) + (((stdIdNum + 1u) >> 1) << 1)) <= FLEXCANDRV_MSG_FILTER_ELEMENTS_NUM) && ((extIdNum + stdIdNum) > 0))
    {
        /* set the number of extended id filter elements */
        if(extIdNum > 0u)
        {
            if((extIdNum & 0x01) != 0x00)
            {
                nexif = (extIdNum + 1u);
            }
            else
            {
                nexif = extIdNum;
            }

            if((extIdNum & 0x01) != 0x00u)
            {
                alignedExtIdElementNum = 1;
            }
        }
        else
        {
            nexif = 0;
        }

        if(stdIdNum > 0u)
        {
            nfe = nexif + ((stdIdNum + 1u) >> 1) - 1u;
            if(nfe > ((FLEXCANDRV_MSG_FILTER_ELEMENTS_NUM >> 1) - 1u))
            {
                nfe = ((FLEXCANDRV_MSG_FILTER_ELEMENTS_NUM >> 1) - 1u);
            }

            /* In this selection mode, one element space are stored with 4 standard id */
            if((stdIdNum & 0x01) != 0x00u)
            {
                alignedStdIdElementNum = 0x01;
            }
        }
        else
        {
        	if(extIdNum > 0u)
			{
				nfe = nexif - 1u;
			}
        }

        FlexCanReg_SetEnhanceRxFifoFilterElementNum(obj->flexCanReg, nfe);
        FlexCanReg_SetExtIdFilterElementNum(obj->flexCanReg, nexif);
        
        /* Configure the filter elements */
        /* Notice: the filter ram is used by extend id firstly, then the rest space are used by standard id!!!! */
        for(i = 0; i < controllerCfg->msgNum; i++)
        {
            if(controllerCfg->msgCfg[i].msgType == FLEXCANDRV_MSGTYPE_RX)
            {
                if(controllerCfg->msgCfg[i].isExtMsgId == true)
                {
                    currentExtIdNum++;
                    filter = 0;
                    mask   = 0;

                    /* FSCH = 00 */
                    filter |= (0x00ul << 30);
                    /* RTR Filter */
                    filter |= (0x00ul << 29);
                    /* EXT ID Filter */
                    filter |= controllerCfg->msgCfg[i].msgId;

                    /* RTR Mask */
                    mask |= (0x00ul << 29);
                    /* EXT ID Mask */
                    mask |= (controllerCfg->msgCfg[i].individualMask & 0x1FFFFFFF);

                    FlexCanReg_SetEnhanceRxFifoElement(obj->flexCanReg, filterElementIdx, filter);
                    filterElementIdx++;

                    FlexCanReg_SetEnhanceRxFifoElement(obj->flexCanReg, filterElementIdx, mask);
                    filterElementIdx++;

                    if(currentExtIdNum == extIdNum)
                    {
                        if (alignedExtIdElementNum > 0u)
                        {
                            /* Used the last filter value to fill */
                            FlexCanReg_SetEnhanceRxFifoElement(obj->flexCanReg, filterElementIdx, filter);
                            filterElementIdx++;

                            FlexCanReg_SetEnhanceRxFifoElement(obj->flexCanReg, filterElementIdx, mask);
                            filterElementIdx++;
                        }

                        break;
                    }
                }
            }
        }

        for(i = 0; i < controllerCfg->msgNum; i++)
        {
            if(controllerCfg->msgCfg[i].msgType == FLEXCANDRV_MSGTYPE_RX)
            {
                if(controllerCfg->msgCfg[i].isExtMsgId == false)
                {
                    currentSdtIdNum++;
                    filter = 0;
                    /* FSCH = 00 */
                    filter |= (0x00ul << 30);
                    /* RTR Filter */
                    filter |= (0x00ul << 27);
                    /* RTR Mask */
                    filter |= (0x00ul << 11);
                    /* STD ID Filter */
                    filter |= (controllerCfg->msgCfg[i].msgId << 16);
                    /* STD ID Mask */
                    filter |= ((controllerCfg->msgCfg[i].individualMask & 0x7FF) << 0);

                    FlexCanReg_SetEnhanceRxFifoElement(obj->flexCanReg, filterElementIdx, filter);
                    filterElementIdx++;

                    if(currentSdtIdNum == stdIdNum)
                    {
                        if (alignedStdIdElementNum > 0u)
                        {
                            /* use the last filter value to fill the space for aligning with two element as one group */
                            FlexCanReg_SetEnhanceRxFifoElement(obj->flexCanReg, filterElementIdx, filter);
                        }
                        
                        break;
                    }
                }
            }
        }

        rtn = true;
    }

    return rtn;
}

static bool FlexCanDrv_SetEnhanceRxFifoFilterInRange(FlexCanDrvType *obj, const FlexCanDrv_ControllerCfgType *controllerCfg, uint8_t extIdNum, uint8_t stdIdNum)
{
    bool     rtn = false, updateFilterReg = false;
    uint8_t  alignedStdIdElementNum = 0, lastValidRxIdIndex = 0, nfe = 0, nexif = 0;
    uint32_t filterMin = 0, filterMax = 0, currentSdtIdNum = 0, currentExtIdNum = 0;
    uint16_t filterElementIdx = 0, i = 0;

    if((((((extIdNum + 1u) >> 1) << 1) + ((stdIdNum + 1u) >> 1)) <= FLEXCANDRV_MSG_FILTER_ELEMENTS_NUM) && ((extIdNum + stdIdNum) > 0))
    {
        /* set the number of extended id filter elements */
        if(extIdNum > 0u)
        {
            if((extIdNum & 0x01) != 0x00)
            {
                nexif = (extIdNum + 1u) >> 1;
            }
            else
            {
                nexif = extIdNum >> 1;
            }
        }
        else
        {
            nexif = 0;
        }

        if(stdIdNum > 0u)
        {
            nfe = nexif + ((((stdIdNum + 1u) >> 1) + 1u) >> 1) - 1u;
            if(nfe > ((FLEXCANDRV_MSG_FILTER_ELEMENTS_NUM >> 1) - 1u))
            {
                nfe = ((FLEXCANDRV_MSG_FILTER_ELEMENTS_NUM >> 1) - 1u);
            }

            /* In this selection mode, one element space are stored with 4 standard id */
            if((stdIdNum & 0x03) != 0x00u)
            {
                alignedStdIdElementNum = 0x04 - (stdIdNum & 0x03);
            }
        }
        else
        {
        	if(extIdNum > 0u)
			{
				nfe = nexif - 1u;
			}
        }

        FlexCanReg_SetEnhanceRxFifoFilterElementNum(obj->flexCanReg, nfe);
        FlexCanReg_SetExtIdFilterElementNum(obj->flexCanReg, nexif);
        
        /* Configure the filter elements */
        /* Notice: the filter ram is used by extend id firstly, then the rest space are used by standard id!!!! */
        for(i = 0; i < controllerCfg->msgNum; i++)
        {
            if(controllerCfg->msgCfg[i].msgType == FLEXCANDRV_MSGTYPE_RX)
            {
                if(controllerCfg->msgCfg[i].isExtMsgId == true)
                {
                    currentExtIdNum++;
                    if(updateFilterReg == false)
                    {
                        updateFilterReg = true;
                        filterMin       = 0;
                        filterMax       = 0;

                        /* RTR Filter */
                        filterMin |= (0x00ul << 29);
                        /* EXT ID Filter */
                        filterMin |= controllerCfg->msgCfg[i].msgId;

                        if(currentExtIdNum == extIdNum)
                        {
                            /* FSCH = 01 */
                            filterMax |= (0x01ul << 30);
                            /* RTR Mask */
                            filterMax |= (0x00ul << 29);
                            /* EXT ID Mask */
                            filterMax |= controllerCfg->msgCfg[i].msgId;

                            FlexCanReg_SetEnhanceRxFifoElement(obj->flexCanReg, filterElementIdx, filterMax);
                            filterElementIdx++;

                            FlexCanReg_SetEnhanceRxFifoElement(obj->flexCanReg, filterElementIdx, filterMin);
                            filterElementIdx++;

                            updateFilterReg = false;
                            break;
                        }
                    }
                    else
                    {
                        if(controllerCfg->msgCfg[i].msgId > (filterMin & 0x1FFFFFFFF))
                        {
                            /* FSCH = 01 */
                            filterMax |= (0x01ul << 30);
                            /* RTR Mask */
                            filterMax |= (0x00ul << 29);
                            /* EXT ID Mask */
                            filterMax |= controllerCfg->msgCfg[i].msgId;
                        }
                        else
                        {
                            filterMax = (filterMin & 0x1FFFFFFFF);
                            /* RTR Mask */
                            filterMax |= (0x00ul << 29);
                            /* FSCH = 01 */
                            filterMax |= (0x01ul << 30);

                            /* EXT ID Filter */
                            filterMin = controllerCfg->msgCfg[i].msgId; 
                            /* RTR Filter */
                            filterMin |= (0x00ul << 29);
                        }

                        FlexCanReg_SetEnhanceRxFifoElement(obj->flexCanReg, filterElementIdx, filterMax);
                        filterElementIdx++;

                        FlexCanReg_SetEnhanceRxFifoElement(obj->flexCanReg, filterElementIdx, filterMin);
                        filterElementIdx++;

                        updateFilterReg = false;

                        if(currentExtIdNum == extIdNum)
                        {
                            break;
                        }
                    }
                }
            }
        }

        for(i = 0; i < controllerCfg->msgNum; i++)
        {
            if(controllerCfg->msgCfg[i].msgType == FLEXCANDRV_MSGTYPE_RX)
            {
                if(controllerCfg->msgCfg[i].isExtMsgId == false)
                {
                    /* ID >= Fitler1  ID <= Fitler2 */
                    currentSdtIdNum++;
                    if(updateFilterReg == false)
                    {
                        updateFilterReg = true;
                        filterMin       = 0;
                        /* FSCH = 01 */
                        filterMin |= (0x01ul << 30);

                        /* STD ID Filter1 */
                        filterMin |= (controllerCfg->msgCfg[i].msgId << 0);
                        /* RTR Mask */
                        filterMin |= (0x00ul << 11);

                        if(currentSdtIdNum == stdIdNum)
                        {
                            lastValidRxIdIndex = i;

                            break;
                        }
                    }
                    else
                    {
                        if(controllerCfg->msgCfg[i].msgId > (filterMin & 0x7FF))
                        {
                            /* set the max filter id as fitler id2 */
                            filterMin |= controllerCfg->msgCfg[i].msgId << 16;
                            /* RTR Filter */
                            filterMin |= (0x00ul << 27);
                        }
                        else
                        {
                            filterMax = (filterMin & 0x7FF);

                            /* FSCH = 01 */
                            filterMin = (0x01ul << 30);
                            /* STD ID Filter1 */
                            filterMin |= (controllerCfg->msgCfg[i].msgId << 0);
                            /* RTR Mask */
                            filterMin |= (0x00ul << 11);

                            filterMin |= filterMax << 16;
                            /* RTR Filter */
                            filterMin |= (0x00ul << 27);
                        }
                        
                        FlexCanReg_SetEnhanceRxFifoElement(obj->flexCanReg, filterElementIdx, filterMin);
                        filterElementIdx++;
                        updateFilterReg = false;

                        if(currentSdtIdNum == stdIdNum)
                        {
                            break;
                        }
                    }
                }
            }
        }

        switch (alignedStdIdElementNum)
        {
        case 0x00:
            break;

        case 0x01:
            /* RTR Filter */
            filterMin |= (0x00ul << 27);
            filterMin |= (controllerCfg->msgCfg[lastValidRxIdIndex].msgId << 16);
            FlexCanReg_SetEnhanceRxFifoElement(obj->flexCanReg, filterElementIdx, filterMin);
            break;

        case 0x02:
            /* Use the last element filter value to fill */
            FlexCanReg_SetEnhanceRxFifoElement(obj->flexCanReg, filterElementIdx, filterMin);
            break;

        case 0x03:
            /* Use the last element filter value to fill */
            FlexCanReg_SetEnhanceRxFifoElement(obj->flexCanReg, filterElementIdx, filterMin);
            filterElementIdx++;

            /* Use the last element filter value to fill */
            FlexCanReg_SetEnhanceRxFifoElement(obj->flexCanReg, filterElementIdx, filterMin);
            break;

        default:
            break;
        }

        rtn = true;
    }

    return rtn;
}

static bool FlexCanDrv_SetEnhanceRxFifoFilterInWithoutMask(FlexCanDrvType *obj, const FlexCanDrv_ControllerCfgType *controllerCfg, uint8_t extIdNum, uint8_t stdIdNum)
{
    bool    rtn = false, updateFilterReg = false;
    uint8_t alignedStdIdElementNum = 0, lastValidRxIdIndex = 0, nfe = 0, nexif = 0;  
    uint32_t filter = 0, mask = 0, currentSdtIdNum = 0, currentExtIdNum = 0;
    uint16_t filterElementIdx = 0, i = 0;

    if((((((extIdNum + 1u) >> 1) << 1) + ((((stdIdNum + 1u) >> 1) << 1) >> 1)) <= FLEXCANDRV_MSG_FILTER_ELEMENTS_NUM) && ((extIdNum + stdIdNum) > 0))
    {
        if(extIdNum > 0u)
        {
            if((extIdNum & 0x01) != 0x00)
            {
                nexif = ((extIdNum + 1u) >> 1);
            }
            else
            {
                nexif = (extIdNum >> 1);
            }
        }
        else
        {
            nexif = 0;
        }

        if(stdIdNum > 0u)
        {
            nfe = nexif + (((((stdIdNum + 1u) >> 1) + 1u) >> 1) - 1u);
            if(nfe > ((FLEXCANDRV_MSG_FILTER_ELEMENTS_NUM >> 1) - 1u))
            {
                nfe = ((FLEXCANDRV_MSG_FILTER_ELEMENTS_NUM >> 1) - 1u);
            }

            /* In this selection mode, one element space are stored with 4 standard id */
            if ((stdIdNum & 0x03) != 0x00u)
            {
                alignedStdIdElementNum = 0x04 - (stdIdNum & 0x03);
            }
        }
        else
        {
        	if(extIdNum > 0u)
        	{
        		nfe = nexif - 1u;
        	}
        }

        FlexCanReg_SetEnhanceRxFifoFilterElementNum(obj->flexCanReg, nfe);
        FlexCanReg_SetExtIdFilterElementNum(obj->flexCanReg, nexif);

        /* Configure the filter elements */
        /* Notice: the filter ram is used by extend id firstly, then the rest space are used by standard id!!!! */
        for(i = 0; i < controllerCfg->msgNum; i++)
        {
            if(controllerCfg->msgCfg[i].msgType == FLEXCANDRV_MSGTYPE_RX)
            {
                if(controllerCfg->msgCfg[i].isExtMsgId == true)
                {
                    currentExtIdNum++;
                    if(updateFilterReg == false)
                    {
                        updateFilterReg = true;
                        filter          = 0;
                        mask            = 0;

                        /* FSCH = 10 */
                        filter |= (0x02ul << 30);
                        /* RTR Filter */
                        filter |= (0x00ul << 29);
                        /* EXT ID Filter */
                        filter |= controllerCfg->msgCfg[i].msgId;

                        if(currentExtIdNum == extIdNum)
                        {
                            /* RTR Mask */
                            mask |= (0x00ul << 29);
                            /* EXT ID Mask */
                            mask |= controllerCfg->msgCfg[i].msgId;

                            FlexCanReg_SetEnhanceRxFifoElement(obj->flexCanReg, filterElementIdx, filter);
                            filterElementIdx++;

                            FlexCanReg_SetEnhanceRxFifoElement(obj->flexCanReg, filterElementIdx, mask);
                            filterElementIdx++;

                            updateFilterReg = false;
                            break;
                        }
                    }
                    else
                    {
                        /* RTR Mask */
                        mask |= (0x00ul << 29);
                        /* EXT ID Mask */
                        mask |= controllerCfg->msgCfg[i].msgId;

                        FlexCanReg_SetEnhanceRxFifoElement(obj->flexCanReg, filterElementIdx, filter);
                        filterElementIdx++;

                        FlexCanReg_SetEnhanceRxFifoElement(obj->flexCanReg, filterElementIdx, mask);
                        filterElementIdx++;

                        updateFilterReg = false;

                        if(currentExtIdNum == extIdNum)
                        {
                            break;
                        }
                    }
                }
            }
        }

        for(i = 0; i < controllerCfg->msgNum; i++)
        {
            if(controllerCfg->msgCfg[i].msgType == FLEXCANDRV_MSGTYPE_RX)
            {
                if(controllerCfg->msgCfg[i].isExtMsgId == false)
                {
                    currentSdtIdNum++;
                    if(updateFilterReg == false)
                    {
                        updateFilterReg = true;
                        filter        = 0;
                        /* FSCH = 10 */
                        filter |= (0x02ul << 30);

                        /* STD ID Filter1 */
                        filter |= (controllerCfg->msgCfg[i].msgId << 0);
                        /* RTR Mask */
                        filter |= (0x00ul << 11);

                        if(currentSdtIdNum == stdIdNum)
                        {
                            lastValidRxIdIndex = i;
                            break;
                        }
                    }
                    else
                    {
                        /* then use the msgid as the second filters */
                        filter |= (controllerCfg->msgCfg[i].msgId << 16);
                        /* RTR Filter */
                        filter |= (0x00ul << 27);

                        FlexCanReg_SetEnhanceRxFifoElement(obj->flexCanReg, filterElementIdx, filter);
                        filterElementIdx++;
                        updateFilterReg = false;
                    }
                }
            }
        }

        switch(alignedStdIdElementNum)
        {
        case 0x01:
            filter |= (controllerCfg->msgCfg[lastValidRxIdIndex].msgId << 16);
            /* RTR Filter */
            filter |= (0x00ul << 27);

            FlexCanReg_SetEnhanceRxFifoElement(obj->flexCanReg, filterElementIdx, filter);
            break;

        case 0x02:
            /* Use the last element filter value to fill */
            FlexCanReg_SetEnhanceRxFifoElement(obj->flexCanReg, filterElementIdx, filter);
            break;

        case 0x03:
            filter |= (controllerCfg->msgCfg[lastValidRxIdIndex].msgId << 16);
            /* RTR Filter */
            filter |= (0x00ul << 27);

            FlexCanReg_SetEnhanceRxFifoElement(obj->flexCanReg, filterElementIdx, filter);
            filterElementIdx++;

            /* Use the last element filter value to fill */
            FlexCanReg_SetEnhanceRxFifoElement(obj->flexCanReg, filterElementIdx, filter);
            break;

        default:
            break;
        }

        rtn = true;
    }

    return rtn;
}

static void FlexCanDrv_InitEnhanceRxFFFilterElement(FlexCanDrvType *obj, const FlexCanDrv_ControllerCfgType *controllerCfg)
{
    uint8_t extIdNum = 0, stdIdNum = 0, i = 0;
    uint8_t maxRxByteNum = 0, dataByteLen = 0;

    /* Get the total number of std id and ext id */
    for(i = 0; i < controllerCfg->msgNum; i++)
    {
        if(controllerCfg->msgCfg[i].msgType == FLEXCANDRV_MSGTYPE_RX)
        {
            if(controllerCfg->msgCfg[i].isExtMsgId == false)
            {
                stdIdNum++;
            }
            else
            {
                extIdNum++;
            }

            dataByteLen = FlexCanDrv_DLC2DataLen(controllerCfg->msgCfg[i].dlc);

            if(maxRxByteNum < dataByteLen)
            {
                maxRxByteNum = dataByteLen;
            }
        }
    }

    if(controllerCfg->dmaEnable == true)
    {
        uint8_t dmaLA = 0;

        /* Define the last DMA address for each enhanced rx fifo element */
        dmaLA = ((maxRxByteNum + 16) / 4) - 1u;
        FlexCanReg_SetEnhanceRxFifoDmaLastWord(obj->flexCanReg, dmaLA);
    }

    switch(controllerCfg->enhRxFFFilterSelection)
    {
    case FLEXCANDRV_ENHRXFF_FILTER_SELECT_MASK_FITLER:
        FlexCanDrv_SetEnhanceRxFifoFilterInMask(obj, controllerCfg, extIdNum, stdIdNum);
        break;

    case FLEXCANDRV_ENHRXFF_FILTER_SELECT_RANGE:
        FlexCanDrv_SetEnhanceRxFifoFilterInRange(obj, controllerCfg, extIdNum, stdIdNum);
        break;

    case FLEXCANDRV_ENHRXFF_FILTER_SELECT_TWO_FILTER_WITHOUT_MASK:
        FlexCanDrv_SetEnhanceRxFifoFilterInWithoutMask(obj, controllerCfg, extIdNum, stdIdNum);
        break;

    default:
        break;
    }
}

static void FlexCanDrv_SetEnhanceRxFifoConfig(FlexCanDrvType *obj, const FlexCanDrv_ControllerCfgType *controllerCfg)
{
    /* enhance rx fifo */
    /* Note: can_mcr.rfen must be 0 when enabling the enhance rx fifo */
    /* set Rx FIFO disable */
    FlexCanReg_SetRxFIFOEnalbe(obj->flexCanReg, false);

    FlexCanReg_SetEnhanceRxFifoEnable(obj->flexCanReg, true);

    /* Reset enhanced rx fifo engine */
    FlexCanReg_ClearEnhanceRxFifoContent(obj->flexCanReg);

    /* Clear ERFUFW ERFOVF ERFWMI ERFDA */
    FlexCanReg_SetEnhanceRxFifoUnderflowIntEnable(obj->flexCanReg, false);
    FlexCanReg_SetEnhanceRxFifoOverflowIntEnable(obj->flexCanReg, false);
    FlexCanReg_SetEnhanceRxFifoWatrmarkIntEnable(obj->flexCanReg, false);
    FlexCanReg_SetEnhanceRxFifoDataAvailableIntEnable(obj->flexCanReg, false);

    /* Configure the rx ff filter elements */
    FlexCanDrv_InitEnhanceRxFFFilterElement(obj, controllerCfg);

    /* Set default water mark */
    FlexCanReg_SetEnhanceRxFifoWatermark(obj->flexCanReg, 0);
}

void FlexCanDrv_Configure(FlexCanDrvType *obj, const FlexCanDrv_ControllerCfgType *controllerCfg)
{
    uint8_t msgBufSize;
    uint8_t msgBufNum = 0;

    /* enable CAN CFG clock */
    if (!FlexCanDrv_EnableCanCfgClk(obj))
    {
        return;
    }

    /* disable FlexCan module */
    FlexCanReg_SetModuleDisable(obj->flexCanReg, true);

    /* make sure that the module has enter into low power mode successfully */
    while(FlexCanReg_GetLowPowerAck(obj->flexCanReg) == 0)
    {
        if (FlexCanDrv_WaitExpired(obj))
        {
            return;
        }
    }

    /* configure FlexCan clock source */
    FlexCanReg_SetClockSource(obj->flexCanReg, controllerCfg->clkSrc);

    /* reset CAN internal status */
    FlexCanDrv_SoftReset(obj);
    if (FlexCanDrv_WaitExpired(obj))
    {
        return;
    }

    /* switch to supervisor mode */
    FlexCanReg_SetAccessMode(obj->flexCanReg, FLEXCANDRV_CAN_ACCESS_MODE_SUP);

    /* enable write access in freeze mode */
    FlexCanReg_SetFreezeModeWriteAcc(obj->flexCanReg, true);

    /* initial can ram */
    FlexCanDrv_InitCanRAM(obj);

    /* calculate the total message number according to the message
     * buffer size per region */
    msgBufSize = FlexCanDrv_ConvertMsgBufSizeSel(controllerCfg->msgBufDataLenSel);
    if(msgBufSize != 0)
    {
        msgBufNum = (FLEXCAN_DRV_CAN_RAM_SIZE / msgBufSize) * obj->initHwPar.canRamNum;
    }
    /* set message buffer maximum number */
    FlexCanReg_SetMaxMsgBufferNum(obj->flexCanReg, msgBufNum);

    /* Set can bit sampling type, make sure the can fd is in disabled! */
    FlexCanReg_SetBitSamplingType(obj->flexCanReg, controllerCfg->selected3bitSampling);

    /*
     *  set standard CAN bit timing
     */
    /* enable CAN extended bit timing */
    FlexCanReg_SetExtendedBitTimingEnable(obj->flexCanReg, true);
    /* set prescaler division */
    FlexCanReg_SetExtPresalerDivision(obj->flexCanReg, controllerCfg->bitTiming.prescalerDiv - 1);
    /* set resync jump width */
    FlexCanReg_SetExtResyncJumpWidth(obj->flexCanReg, controllerCfg->bitTiming.resyncJumpWidth - 1);
    /* set propagation segment */
    FlexCanReg_SetExtPorpSeg(obj->flexCanReg, controllerCfg->bitTiming.propSeg - 1);
    /* set phase segment 1 */
    FlexCanReg_SetExtPhaseSeg1(obj->flexCanReg, controllerCfg->bitTiming.phaseSeg1 - 1);
    /* set phase segment 2 */
    FlexCanReg_SetExtPhaseSeg2(obj->flexCanReg, controllerCfg->bitTiming.phaseSeg2 - 1);

    if(controllerCfg->fdEnable)
    {
        /* set CAN FD operation enable */
        FlexCanReg_SetFdEnable(obj->flexCanReg, controllerCfg->fdEnable);
        /* enable FD rate switch */
        FlexCanReg_SetFdRateSwitch(obj->flexCanReg, true);

        /* set FD prescaler division */
        FlexCanReg_SetFdPrescalerDivision(obj->flexCanReg, controllerCfg->fdBitTiming.prescalerDiv - 1);
        /* set FD resync jump width */
        FlexCanReg_SetFdResyncJumpWidth(obj->flexCanReg, controllerCfg->fdBitTiming.resyncJumpWidth - 1);
        /* set FD propagation segment */
        FlexCanReg_SetFdPorpSeg(obj->flexCanReg, controllerCfg->fdBitTiming.propSeg);
        /* set FD phase segment 1 */
        FlexCanReg_SetFdPhaseSeg1(obj->flexCanReg, controllerCfg->fdBitTiming.phaseSeg1 - 1);
        /* set FD phase segment 2 */
        FlexCanReg_SetFdPhaseSeg2(obj->flexCanReg, controllerCfg->fdBitTiming.phaseSeg2 - 1);

        /* set region 0 data size selection */
        FlexCanReg_SetRegionDataSizeSel(obj->flexCanReg, 0, controllerCfg->msgBufDataLenSel);
        /* set region 1 data size selection */
        FlexCanReg_SetRegionDataSizeSel(obj->flexCanReg, 1, controllerCfg->msgBufDataLenSel);
        /* set region 2 data size selection */
        FlexCanReg_SetRegionDataSizeSel(obj->flexCanReg, 2, controllerCfg->msgBufDataLenSel);
        /* set region 3 data size selection */
        FlexCanReg_SetRegionDataSizeSel(obj->flexCanReg, 3, controllerCfg->msgBufDataLenSel);

        if(controllerCfg->loopbackEnable == false)
        {
            /* set TDC enable */
            FlexCanReg_SetTdcEnable(obj->flexCanReg, controllerCfg->tdcEnable);
            /* set TDC offset */
            FlexCanReg_SetTdcOffset(obj->flexCanReg, controllerCfg->tdcOffset);
        }

        /* set CAN-FD ISO enable */
        FlexCanReg_SetIsoFdEnalbe(obj->flexCanReg, controllerCfg->fdISOEnable);
    }

    /* lagecy rx fifo */
    if(controllerCfg->fifoEnable)
    {
        /* Only node 0 support the feature of enhance rx fifo */
        if(obj->initHwPar.canInstanceIdx == 0)
        {
            /* Make sure the ehnhance is in disable mode */
            FlexCanReg_SetEnhanceRxFifoEnable(obj->flexCanReg, false);
        }

        /* set Rx FIFO enable */
        FlexCanReg_SetRxFIFOEnalbe(obj->flexCanReg, true);

        /* set Rx FIFO global mask */
        FlexCanReg_SetRxFifoGlobalMask(obj->flexCanReg, controllerCfg->rxFifoGlobalMask);

        /* set rx mailbox global mask */
        FlexCanReg_SetRxMailboxGlobalMask(obj->flexCanReg, controllerCfg->rxMBGlobalMask);
        /* set rx mailbox 14 mask */
        FlexCanReg_SetRxMailbox14Mask(obj->flexCanReg, controllerCfg->rxMB14Mask);
        /* set rx mailbox 15 mask */
        FlexCanReg_SetRxMailbox15Mask(obj->flexCanReg, controllerCfg->rxMB15Mask);

        /* set individual Rx masking and queue enable */
        FlexCanReg_SetIndividualMaskEnable(obj->flexCanReg, controllerCfg->individualMaskEnable);
    }
    else if(controllerCfg->enhancefifoEnable)
    {
        /* Only node 0 support the feature of enhance rx fifo */
        if(obj->initHwPar.canInstanceIdx == 0)
        {
            FlexCanDrv_SetEnhanceRxFifoConfig(obj, controllerCfg);
        }
    }
    else
    {
        /* set Rx FIFO disable */
        FlexCanReg_SetRxFIFOEnalbe(obj->flexCanReg, false);
        if(obj->initHwPar.canInstanceIdx == 0)
        {
            FlexCanReg_SetEnhanceRxFifoEnable(obj->flexCanReg, false);
            /* Reset enhanced rx fifo engine */
            FlexCanReg_ClearEnhanceRxFifoContent(obj->flexCanReg);

            /* Clear ERFUFW ERFOVF ERFWMI ERFDA */
            FlexCanReg_SetEnhanceRxFifoUnderflowIntEnable(obj->flexCanReg, false);
            FlexCanReg_SetEnhanceRxFifoOverflowIntEnable(obj->flexCanReg, false);
            FlexCanReg_SetEnhanceRxFifoWatrmarkIntEnable(obj->flexCanReg, false);
            FlexCanReg_SetEnhanceRxFifoDataAvailableIntEnable(obj->flexCanReg, false);
        }

        /* set rx mailbox global mask */
        FlexCanReg_SetRxMailboxGlobalMask(obj->flexCanReg, controllerCfg->rxMBGlobalMask);
        /* set rx mailbox 14 mask */
        FlexCanReg_SetRxMailbox14Mask(obj->flexCanReg, controllerCfg->rxMB14Mask);
        /* set rx mailbox 15 mask */
        FlexCanReg_SetRxMailbox15Mask(obj->flexCanReg, controllerCfg->rxMB15Mask);

        /* set individual Rx masking and queue enable */
        FlexCanReg_SetIndividualMaskEnable(obj->flexCanReg, controllerCfg->individualMaskEnable);
    }

    /* set Rx FIFO DMA enable */
    FlexCanReg_SetRxFIFODmaEnable(obj->flexCanReg, controllerCfg->dmaEnable);

    /* loopback mode configuration */
    if(controllerCfg->loopbackEnable)
    {
        FlexCanReg_SetSelfReceptionDisable(obj->flexCanReg, false); /* enable self reception (0) */
        FlexCanReg_SetLoopbackMode(obj->flexCanReg, true);          /* enable loop-back */
    }
    else
    {
        FlexCanReg_SetSelfReceptionDisable(obj->flexCanReg, true); /* disable self reception (1) */
        FlexCanReg_SetLoopbackMode(obj->flexCanReg, false);        /* disable loop-back */
    }

    FlexCanReg_SetListenOnlyModeEna(obj->flexCanReg, controllerCfg->listenMode);

    /* edge wakeup configuration */
    if(controllerCfg->edgeWkupEnable)
    {
        /* enable edge(self) wakeup */
        FlexCanReg_SetSelfWakeupEnable(obj->flexCanReg, 1U);
        /* enable edge(self) wakeup interrupt */
        FlexCanReg_SetWakeupIntMask(obj->flexCanReg, 1U);
    }
    else
    {
        /* disable edge(self) wakeup */
        FlexCanReg_SetSelfWakeupEnable(obj->flexCanReg, 0U);
        /* disable edge(self) wakeup interrupt */
        FlexCanReg_SetWakeupIntMask(obj->flexCanReg, 0U);
    }

    /* BusOff recovery */
    FlexCanReg_SetBusOffRecEnable(obj->flexCanReg, true);

    /* set Tx message abort enable */
    FlexCanReg_SetTxAbortEnable(obj->flexCanReg, controllerCfg->txAbortEnable);

    /* set busoff interrupt enable mask */
    FlexCanReg_SetBusOffIntEnable(obj->flexCanReg, controllerCfg->busoffIntEnable);
    /* set error interrupt enable mask */
    FlexCanReg_SetErrorIntEnable(obj->flexCanReg, controllerCfg->errorIntEnable);
    /* set warning interrupt enable */
    FlexCanReg_SetWarningIntEnable(obj->flexCanReg, controllerCfg->warningIntEnable);
    FlexCanReg_SetTxWarnIntEnable(obj->flexCanReg, controllerCfg->warningIntEnable);
    FlexCanReg_SetRxWarnIntEnable(obj->flexCanReg, controllerCfg->warningIntEnable);

    if(controllerCfg->enhancefifoEnable == false)
    {
        /* configure messages */
        uint8_t i = 0;

        for(i = 0; i < controllerCfg->msgNum; i++)
        {
            uint16_t j = 0;
            /* configure messages according to the message buffer Id and message buffer length parameters */
            for(j = controllerCfg->msgCfg[i].msgBufId; j < controllerCfg->msgCfg[i].msgBufId + controllerCfg->msgCfg[i].msgBufLen; j++)
            {
                FlexCanDrv_CfgMsgObj(obj, &controllerCfg->msgCfg[i], j);
            }
        }
    }
    else
    {
        /* configure messages */
        uint8_t i = 0;

        for(i = 0; i < controllerCfg->msgNum; i++)
        {
            uint16_t j = 0;
            /* configure messages according to the message buffer Id and message buffer length parameters */
            for(j = controllerCfg->msgCfg[i].msgBufId; j < controllerCfg->msgCfg[i].msgBufId + controllerCfg->msgCfg[i].msgBufLen; j++)
            {
                /* MB used for Tx if enhance rx fifo enabled */
                if(controllerCfg->msgCfg[i].msgType == FLEXCANDRV_MSGTYPE_TX)
                {
                    FlexCanDrv_CfgMsgObj(obj, &controllerCfg->msgCfg[i], j);
                }
            }
        }
    }

    /* Set the free running timer is by external timer tick or not */
    FlexCanReg_SetFreeRunTimerSrc(obj->flexCanReg, controllerCfg->freeRunningTmrClockedByExtTmrEn);

    /* Select which time base is used for capture in Message buffer time stamp */
    FlexCanReg_SetFreeRunTimerBase(obj->flexCanReg, controllerCfg->mbTmrBaseSelect);

    /* Select the point in time at which a 32-bit time base is captured during a can frame and stored in the HR-TimeStamp */
    FlexCanReg_SetHighResTimeStampMode(obj->flexCanReg, controllerCfg->hrTmrCapturePointSelect);

    /* clear all message buffer flags */
    FlexCanDrv_ClearAllMsgObjFlags(obj);

    /* Clear all enhance rx fifo flags */
    /* Only node 0 support the feature of enhance rx fifo */
    if(obj->initHwPar.canInstanceIdx == 0)
    {
        if(controllerCfg->enhancefifoEnable == true)
        {
            FlexCanDrv_ClearEnhanceRxFFIsrFlag(obj, FLEXCANDRV_ENHANCERXFF_ISR_SRC_DAIE | FLEXCANDRV_ENHANCERXFF_ISR_SRC_WMMIE | FLEXCANDRV_ENHANCERXFF_ISR_SRC_OVFIE | FLEXCANDRV_ENHANCERXFF_ISR_SRC_UFWIE);
        }
    }

    /* enable FlexCan module */
    FlexCanDrv_Start(obj);
    if (FlexCanDrv_WaitExpired(obj))
    {
        return;
    }

    /* switch to user mode */
    FlexCanReg_SetAccessMode(obj->flexCanReg, FLEXCANDRV_CAN_ACCESS_MODE_USER);
}

bool FlexCanDrv_ConfigureBounded(FlexCanDrvType *obj,
                                const FlexCanDrv_ControllerCfgType *controllerCfg,
                                bool (*expired)(void *context), void *context)
{
    bool success;

    if ((obj == (void *)0) || (controllerCfg == (void *)0) || (expired == 0))
    {
        return false;
    }
    obj->waitExpired = expired;
    obj->waitContext = context;
    obj->waitFailed = false;
    if (!FlexCanDrv_WaitExpired(obj))
    {
        FlexCanDrv_Configure(obj, controllerCfg);
    }
    success = !FlexCanDrv_WaitExpired(obj);
    obj->waitExpired = 0;
    obj->waitContext = (void *)0;
    return success;
}

void FlexCanDrv_TransmitMsg(FlexCanDrvType *obj, FlexCanDrv_MsgObjType *msgObj)
{
    uint32_t *msgBufPtr;

    /* get current message buffer start address */
    msgBufPtr = (uint32_t *)FlexCanDrv_GetMsgBufStartAddr(obj, msgObj->msgBufId);

    /* set transmit code for the message buffer and start transmitting */
    *msgBufPtr |= (((uint32_t)FLEXCANDRV_MSG_BUF_CODE_TX_REQUEST) << FLEXCANDRV_MSG_BUF_CODE_SHIFT);
}

void FlexCanDrv_SetTxMsg(FlexCanDrvType *obj, FlexCanDrv_MsgObjType *msgObj)
{
    uint32_t *msgBufPtr;
    uint32_t  dataLen;

    /* get current message buffer start address */
    msgBufPtr = (uint32_t *)FlexCanDrv_GetMsgBufStartAddr(obj, msgObj->msgBufId);
    /* add data field address offset (2 * 32 bit) */
    msgBufPtr += 2;

    /* get data length from message buffer DLC */
    dataLen = FlexCanDrv_GetMsgBufDataLen(obj, msgObj->msgBufId);

    /* load the data into message buffer */
    uint8_t i = 0;
    for(i = 0; i < dataLen; i++)
    {
        /* load the data in byte length */
        if((i % 4) == 0)
        {
            /* clean the old data */
            *msgBufPtr = 0;

            /* lowest byte in 32-bit */
            *msgBufPtr |= (((uint32_t)msgObj->data[i]) << 24);
        }
        else if((i % 4) == 1)
        {
            /* 2nd byte in 32-bit */
            *msgBufPtr |= (((uint32_t)msgObj->data[i]) << 16);
        }
        else if((i % 4) == 2)
        {
            /* 3rd byte in 32-bit */
            *msgBufPtr |= (((uint32_t)msgObj->data[i]) << 8);
        }
        else if((i % 4) == 3)
        {
            /* highest byte in 32-bit */
            *msgBufPtr |= ((uint32_t)msgObj->data[i]);

            /* increment the 32-bit data pointer  */
            msgBufPtr++;
        }
    }
}

void FlexCanDrv_GetRxMsg(FlexCanDrvType *obj, FlexCanDrv_MsgObjType *msgObj)
{
    uint32_t *msgBufPtr;
    uint8_t   dataLen;
    bool      isExtMsgId;

    /* get current message buffer start address */
    msgBufPtr = (uint32_t *)FlexCanDrv_GetMsgBufStartAddr(obj, msgObj->msgBufId);

    /* get the rx message DLC */
    msgObj->dlc = FlexCanDrv_DLC2DataLen((FlexCanDrv_DLCType)((*msgBufPtr & MESSAGE_BUFFER_CS_DLC_MASK) >> MESSAGE_BUFFER_CS_DLC_SHIFT));
    /* get extended message ID bit (CS.IDE) */
    isExtMsgId = (*msgBufPtr & MESSAGE_BUFFER_CS_IDE_MASK) >> MESSAGE_BUFFER_CS_IDE_SHIFT;

    /* set message buffer pointer to ID field */
    msgBufPtr++;

    /* get message ID */
    if(isExtMsgId == true)
    {
        msgObj->msgId = (*msgBufPtr & MESSAGE_BUFFER_ID_EXT_ID_MASK) >> MESSAGE_BUFFER_ID_EXT_ID_SHIFT;
    }
    else
    {
        msgObj->msgId = (*msgBufPtr & MESSAGE_BUFFER_ID_STD_ID_MASK) >> MESSAGE_BUFFER_ID_STD_ID_SHIFT;
    }

    /* set the message buffer pointer to data field */
    msgBufPtr++;

    /* get data length from message buffer DLC */
    dataLen = FlexCanDrv_GetMsgBufDataLen(obj, msgObj->msgBufId);

    /* load the data from message buffer to data array */
    uint8_t i = 0;
    for(i = 0; i < dataLen; i++)
    {
        if((i % 4) == 0)
        {
            /* load 1 byte data from highest byte in 32-bit */
            msgObj->data[i] = (*msgBufPtr >> 24);
        }
        else if((i % 4) == 1)
        {
            /* load 1 byte data from 2nd highest byte in 32-bit */
            msgObj->data[i] = (*msgBufPtr >> 16);
        }
        else if((i % 4) == 2)
        {
            /* load 1 byte data from 3nd highest byte in 32-bit */
            msgObj->data[i] = (*msgBufPtr >> 8);
        }
        /* when (i % 4) == 3 */
        else
        {
            /* load 1 byte data from lowest byte in 32-bit */
            msgObj->data[i] = (*msgBufPtr >> 0);

            /* increment message buffer 32-bit data pointer */
            msgBufPtr++;
        }
    }

    /* unlock mailbox globally */
    FlexCanReg_GetFreeRunningTimer(obj->flexCanReg);
}

void FlexCanDrv_GetRxFifoMsg(FlexCanDrvType *obj, FlexCanDrv_MsgObjType *msgObj)
{
    bool                  isExtMsgId;
    FlexCanDrv_MsgObjType tempMsgObj;

    /* get Rx FIFO out port start address (message buffer 0) */
    uint32_t *msgBufPtr = (uint32_t *)FlexCanDrv_GetMsgBufStartAddr(obj, 0);

    /* get the rx message DLC */
    msgObj->dlc = FlexCanDrv_DLC2DataLen((FlexCanDrv_DLCType)((*msgBufPtr & MESSAGE_BUFFER_CS_DLC_MASK) >> MESSAGE_BUFFER_CS_DLC_SHIFT));
    /* get extended message ID bit (CS.IDE) */
    isExtMsgId = (*msgBufPtr & MESSAGE_BUFFER_CS_IDE_MASK) >> MESSAGE_BUFFER_CS_IDE_SHIFT;

    /* set message buffer pointer to ID field */
    msgBufPtr++;

    /* get message ID */
    if(isExtMsgId == true)
    {
        msgObj->msgId = (*msgBufPtr & MESSAGE_BUFFER_ID_EXT_ID_MASK) >> MESSAGE_BUFFER_ID_EXT_ID_SHIFT;
    }
    else
    {
        msgObj->msgId = (*msgBufPtr & MESSAGE_BUFFER_ID_STD_ID_MASK) >> MESSAGE_BUFFER_ID_STD_ID_SHIFT;
    }

    /* set message buffer pointer to DATA field */
    msgBufPtr++;

    /* load the data from message buffer to data array */
    uint8_t i = 0;
    for(i = 0; i < 8; i++)
    {
        if((i % 4) == 0)
        {
            /* load 1 byte data from highest byte in 32-bit */
            msgObj->data[i] = (*msgBufPtr >> 24);
        }
        else if((i % 4) == 1)
        {
            /* load 1 byte data from 2nd highest byte in 32-bit */
            msgObj->data[i] = (*msgBufPtr >> 16);
        }
        else if((i % 4) == 2)
        {
            /* load 1 byte data from 3nd highest byte in 32-bit */
            msgObj->data[i] = (*msgBufPtr >> 8);
        }
        /* when (i % 4) == 3 */
        else
        {
            /* load 1 byte data from lowest byte in 32-bit */
            msgObj->data[i] = (*msgBufPtr >> 0);

            /* increment message buffer 32-bit data pointer */
            msgBufPtr++;
        }
    }

    /* clear Rx FIFO available flag to update Rx FIFO */
    tempMsgObj.msgBufId = 5;
    FlexCanDrv_ClearMsgObjFlag(obj, tempMsgObj.msgBufId);
}

void FlexCanDrv_ClearMsgObjFlag(FlexCanDrvType *obj, uint8_t msgBufferIdx)
{
    uint32_t temp, temp1 = 0;

    temp1 = msgBufferIdx % 32;
    temp  = 0x00000001 << temp1;

    if(msgBufferIdx > 63)
    {
        FlexCanReg_SetMsgBufInterruptFlagReg(obj->flexCanReg, 2, temp);
    }
    else if(msgBufferIdx > 31)
    {
        FlexCanReg_SetMsgBufInterruptFlagReg(obj->flexCanReg, 1, temp);
    }
    else
    {
        FlexCanReg_SetMsgBufInterruptFlagReg(obj->flexCanReg, 0, temp);
    }
}

uint8_t FlexCanDrv_GetMsgObjFlag(FlexCanDrvType *obj, uint8_t msgBufferIdx)
{
    uint32_t temp, temp1 = 0;
    temp1 = msgBufferIdx % 32;
    temp  = 0x00000001 << temp1;

    if(msgBufferIdx > 63)
    {
        temp &= FlexCanReg_GetMsgBufInterruptFlagReg(obj->flexCanReg, 2);
    }
    else if(msgBufferIdx > 31)
    {
        temp &= FlexCanReg_GetMsgBufInterruptFlagReg(obj->flexCanReg, 1);
    }
    else
    {
        temp &= FlexCanReg_GetMsgBufInterruptFlagReg(obj->flexCanReg, 0);
    }

    if(temp)
    {
        return (1);
    }
    else
    {
        return (0);
    }
}

void FlexCanDrv_ClearAllMsgObjFlags(FlexCanDrvType *obj)
{
    if(obj->initHwPar.canRamNum == 3)
    {
        FlexCanReg_SetMsgBufInterruptFlagReg(obj->flexCanReg, 2, 0xFFFFFFFF);
        FlexCanReg_SetMsgBufInterruptFlagReg(obj->flexCanReg, 1, 0xFFFFFFFF);
        FlexCanReg_SetMsgBufInterruptFlagReg(obj->flexCanReg, 0, 0xFFFFFFFF);
    }
    else if(obj->initHwPar.canRamNum == 2)
    {
        FlexCanReg_SetMsgBufInterruptFlagReg(obj->flexCanReg, 1, 0xFFFFFFFF);
        FlexCanReg_SetMsgBufInterruptFlagReg(obj->flexCanReg, 0, 0xFFFFFFFF);
    }
    else if(obj->initHwPar.canRamNum == 1)
    {
        FlexCanReg_SetMsgBufInterruptFlagReg(obj->flexCanReg, 0, 0xFFFFFFFF);
    }
}

void FlexCanDrv_EnableMsgObjInterrupt(FlexCanDrvType *obj, uint8_t msgBufferIdx)
{
    uint32_t temp, temp1 = 0;
    temp1 = msgBufferIdx % 32;
    temp  = 0x00000001 << temp1;
    if(msgBufferIdx > 63)
    {
        FlexCanReg_SetMsgBufInterruptEnable(obj->flexCanReg, 2, temp);
    }
    else if(msgBufferIdx > 31)
    {
        FlexCanReg_SetMsgBufInterruptEnable(obj->flexCanReg, 1, temp);
    }
    else
    {
        FlexCanReg_SetMsgBufInterruptEnable(obj->flexCanReg, 0, temp);
    }
}

void FlexCanDrv_DisableMsgObjInterrupt(FlexCanDrvType *obj, uint8_t msgBufferIdx)
{
    uint32_t temp, temp1 = 0;
    temp1 = msgBufferIdx % 32;
    temp  = ~(0x00000001 << temp1);
    if(msgBufferIdx > 63)
    {
        FlexCanReg_SetMsgBufInterruptDisable(obj->flexCanReg, 2, temp);
    }
    else if(msgBufferIdx > 31)
    {
        FlexCanReg_SetMsgBufInterruptDisable(obj->flexCanReg, 1, temp);
    }
    else
    {
        FlexCanReg_SetMsgBufInterruptDisable(obj->flexCanReg, 0, temp);
    }
}

FlexCanDrv_NodeStatType FlexCanDrv_GetNodeStatus(FlexCanDrvType *obj)
{
    FlexCanDrv_NodeStatType ret;

    if(FlexCanReg_GetTxState(obj->flexCanReg))
    {
        ret = FLEXCANDRV_NODESTAT_TRANSMITTING;
    }
    else if(FlexCanReg_GetRxState(obj->flexCanReg))
    {
        ret = FLEXCANDRV_NODESTAT_RECEIVING;
    }
    else if(FlexCanReg_GetIdleState(obj->flexCanReg))
    {
        ret = FLEXCANDRV_NODESTAT_IDLE;
    }
    else
    {
    }

    return ret;
}

void FlexCanDrv_GetErrorStatusFlag(FlexCanDrvType *obj, FlexCanDrv_ErrStatusType *errSts)
{
    uint32_t tempRegVal = 0;
    uint8_t  tempSts    = 0;
    tempRegVal = FlexCanReg_GetEsr1Register(obj->flexCanReg);

    tempSts = (uint8_t)((tempRegVal & FLEXCAN_ESR1_FLTCONF_MASK) >> FLEXCAN_ESR1_FLTCONF_SHIFT);
    if(tempSts & 0x2)
    {
        errSts->fltConfSts = FLEXCANDRV_FLTCONFSTS_BUSOFF;
    }
    else
    {
        errSts->fltConfSts = (FlexCanDrv_FltConfStsType)tempSts;
    }

    errSts->bit1Err       = (uint8_t)(((tempRegVal) & FLEXCAN_ESR1_BIT1ERR_MASK) >> FLEXCAN_ESR1_BIT1ERR_SHIFT);
    errSts->bit0Err       = (uint8_t)(((tempRegVal) & FLEXCAN_ESR1_BIT0ERR_MASK) >> FLEXCAN_ESR1_BIT0ERR_SHIFT);
    errSts->ackErr        = (uint8_t)(((tempRegVal) & FLEXCAN_ESR1_ACKERR_MASK) >> FLEXCAN_ESR1_ACKERR_SHIFT);
    errSts->crcErr        = (uint8_t)(((tempRegVal) & FLEXCAN_ESR1_CRCERR_MASK) >> FLEXCAN_ESR1_CRCERR_SHIFT);
    errSts->formErr       = (uint8_t)(((tempRegVal) & FLEXCAN_ESR1_FRMERR_MASK) >> FLEXCAN_ESR1_FRMERR_SHIFT);
    errSts->stuffErr      = (uint8_t)(((tempRegVal) & FLEXCAN_ESR1_STFERR_MASK) >> FLEXCAN_ESR1_STFERR_SHIFT);
    errSts->errOvr        = (uint8_t)(((tempRegVal) & FLEXCAN_ESR1_ERROVR_MASK) >> FLEXCAN_ESR1_ERROVR_SHIFT);
    errSts->busOffInt     = (uint8_t)(((tempRegVal) & FLEXCAN_ESR1_BOFFINT_MASK) >> FLEXCAN_ESR1_BOFFINT_SHIFT);
    errSts->busOffDoneInt = (uint8_t)(((tempRegVal) & FLEXCAN_ESR1_BOFFDONEINT_MASK) >> FLEXCAN_ESR1_BOFFDONEINT_SHIFT);
    errSts->synch         = (uint8_t)(((tempRegVal) & FLEXCAN_ESR1_SYNCH_MASK) >> FLEXCAN_ESR1_SYNCH_SHIFT);
    errSts->txWarning     = (uint8_t)(((tempRegVal) & FLEXCAN_ESR1_TXWRN_MASK) >> FLEXCAN_ESR1_TXWRN_SHIFT);
    errSts->rxWarning     = (uint8_t)(((tempRegVal) & FLEXCAN_ESR1_RXWRN_MASK) >> FLEXCAN_ESR1_RXWRN_SHIFT);
    errSts->txWarnintInt  = (uint8_t)(((tempRegVal) & FLEXCAN_ESR1_TWRNINT_MASK) >> FLEXCAN_ESR1_TWRNINT_SHIFT);
    errSts->rxWarningInt  = (uint8_t)(((tempRegVal) & FLEXCAN_ESR1_RWRNINT_MASK) >> FLEXCAN_ESR1_RWRNINT_SHIFT);
    errSts->errInt        = (uint8_t)(((tempRegVal) & FLEXCAN_ESR1_ERRINT_MASK) >> FLEXCAN_ESR1_ERRINT_SHIFT);
    errSts->wakeUpInt     = (uint8_t)(((tempRegVal) & FLEXCAN_ESR1_ERRINT_MASK) >> FLEXCAN_ESR1_ERRINT_SHIFT);

    if(FlexCanReg_GetFdEnable(obj->flexCanReg) == true)
    {
        errSts->bit1FastErr  = (uint8_t)(((tempRegVal) & FLEXCAN_ESR1_BIT1ERR_FAST_MASK) >> FLEXCAN_ESR1_BIT1ERR_FAST_SHIFT);
        errSts->bit0FastErr  = (uint8_t)(((tempRegVal) & FLEXCAN_ESR1_BIT0ERR_FAST_MASK) >> FLEXCAN_ESR1_BIT0ERR_FAST_SHIFT);
        errSts->crcFastErr   = (uint8_t)(((tempRegVal) & FLEXCAN_ESR1_CRCERR_FAST_MASK) >> FLEXCAN_ESR1_CRCERR_FAST_SHIFT);
        errSts->formFastErr  = (uint8_t)(((tempRegVal) & FLEXCAN_ESR1_FRMERR_FAST_MASK) >> FLEXCAN_ESR1_FRMERR_FAST_SHIFT);
        errSts->stuffFastErr = (uint8_t)(((tempRegVal) & FLEXCAN_ESR1_STFERR_FAST_MASK) >> FLEXCAN_ESR1_STFERR_FAST_SHIFT);
        errSts->errFastInt   = (uint8_t)(((tempRegVal) & FLEXCAN_ESR1_ERRINT_FAST_MASK) >> FLEXCAN_ESR1_ERRINT_FAST_SHIFT);
        ;
    }
}

void FlexCanDrv_ClearErrStatusFlag(FlexCanDrvType *obj, uint32_t errMask)
{
    FlexCanReg_ClearErrFlag(obj->flexCanReg, errMask);
}

uint8_t FlexCanDrv_AbortPendingTxMsg(FlexCanDrvType *obj, FlexCanDrv_MsgObjType *msgObj)
{
    uint32_t         *msgBufPtr;
    volatile uint32_t msgBufCode;
    uint8_t           ret;

    /* set freeze mode enable */
    FlexCanReg_SetFreezeMode(obj->flexCanReg, true);
    /* set halt mode enable */
    FlexCanReg_SetHaltMode(obj->flexCanReg, true);

    /* check for freeze Ack */
    while((FlexCanReg_GetFreezeAck(obj->flexCanReg) == 0) || (FlexCanReg_GetNotReadyFlag(obj->flexCanReg) == 0))
    {
        /* soft reset failed */
    }

    FlexCanReg_SetTxAbortEnable(obj->flexCanReg, true);

    FlexCanDrv_Start(obj);

    /* disable message buffer interrupt */
    FlexCanDrv_DisableMsgObjInterrupt(obj, msgObj->msgBufId);

    /* clear message buffer flag */
    FlexCanDrv_ClearMsgObjFlag(obj, msgObj->msgBufId);

    /* get current message buffer start address */
    msgBufPtr = (uint32_t *)FlexCanDrv_GetMsgBufStartAddr(obj, msgObj->msgBufId);
    /* clear message buffer CS.CODE field */
    *msgBufPtr &= (~FLEXCANDRV_MSG_BUF_CODE_MASK << FLEXCANDRV_MSG_BUF_CODE_SHIFT);
    /* set the message buffer code as TX ABORT */
    *msgBufPtr |= (((uint32_t)FLEXCANDRV_MSG_BUF_CODE_ABORT) << FLEXCANDRV_MSG_BUF_CODE_SHIFT);

    /* wait until message buffer flag assert */
    while(FlexCanDrv_GetMsgObjFlag(obj, msgObj->msgBufId) == 0)
    {
    }

    msgBufCode = (*msgBufPtr >> FLEXCANDRV_MSG_BUF_CODE_SHIFT) & FLEXCANDRV_MSG_BUF_CODE_MASK;

    /* check the tx pending message abort result */
    if(msgBufCode == FLEXCANDRV_MSG_BUF_CODE_ABORT)
    {
        ret = TX_PENDING_ABORT_SUCCESS;
    }
    else if(msgBufCode == FLEXCANDRV_MSG_BUF_CODE_TX_INACTIVE)
    {
        ret = TX_PENDING_ABORT_NO_TRANSFER;
    }
    else
    {
        ret = TX_PENDING_ABORT_FAILED;
    }

    /* clear message buffer flag */
    FlexCanDrv_ClearMsgObjFlag(obj, msgObj->msgBufId);

    /* set freeze mode enable */
    FlexCanReg_SetFreezeMode(obj->flexCanReg, true);
    /* set halt mode enable */
    FlexCanReg_SetHaltMode(obj->flexCanReg, true);

    /* check for freeze Ack */
    while((FlexCanReg_GetFreezeAck(obj->flexCanReg) == 0) || (FlexCanReg_GetNotReadyFlag(obj->flexCanReg) == 0))
    {
        /* soft reset failed */
    }

    FlexCanReg_SetTxAbortEnable(obj->flexCanReg, false);

    FlexCanDrv_Start(obj);

    return ret;
}

void FlexCanDrv_BitTimingCalc(FlexCanDrv_BitTimingType *bitTimingPara,
                              uint32_t                  moduleFreq,
                              uint32_t                  baudrate,
                              uint16_t                  samplePoint,
                              uint16_t                  sjw,
                              uint8_t                   isFd)
{
    int32_t maxPrescaler, maxTseg1, minTseg1, maxTseg2, maxNumTq, minNumTq;
    int32_t tempPrescaler, tempSjw, tempTseg1, tempNumTq;
    float   bestErr = 0;

    /* set default best value for all bit timing parameters */
    int32_t bestPrescaler = 1, bestSjw = 1, bestNumTq = 8, bestTseg1 = 3, bestTseg2 = 2;

    /* set the optimal value for baudrate error, number of time quatna */
    const int32_t optNumTq          = 20;
    const float   optBaudrateErr    = 0.1;
    const float   optSamplePntToler = 0.25;

    /* set the maximum & minimum value for all bit timing parameters */
    if(isFd == false)
    {
        maxPrescaler = FLEXCAN_CBT_EPRESDIV_MASK >> FLEXCAN_CBT_EPRESDIV_SHIFT;
        maxTseg1     = (FLEXCAN_CBT_EPROPSEG_MASK >> FLEXCAN_CBT_EPROPSEG_SHIFT) + (FLEXCAN_CBT_EPSEG1_MASK >> FLEXCAN_CBT_EPSEG1_SHIFT);
        minTseg1     = 3;//EPROPSEG+EPSEG=1+1=3?????
        maxTseg2     = FLEXCAN_CBT_EPSEG2_MASK >> FLEXCAN_CBT_EPSEG2_SHIFT;

        maxNumTq = maxTseg1 + maxTseg2 + 1;
        minNumTq = 8;
    }
    else
    {
        maxPrescaler = FLEXCAN_FDCBT_FPRESDIV_MASK >> FLEXCAN_FDCBT_FPRESDIV_SHIFT;
        maxTseg1     = (FLEXCAN_FDCBT_FPROPSEG_MASK >> FLEXCAN_FDCBT_FPROPSEG_SHIFT) + (FLEXCAN_FDCBT_FPSEG1_MASK >> FLEXCAN_FDCBT_FPSEG1_SHIFT);
        minTseg1     = 3;
        maxTseg2     = FLEXCAN_FDCBT_FPSEG2_MASK >> FLEXCAN_FDCBT_FPSEG2_SHIFT;

        maxNumTq = maxTseg1 + maxTseg2 + 1;
        minNumTq = 8;
    }

    /* calculate prescaler, number of Tq */
    bestErr = (float)baudrate;
    for(tempPrescaler = 1; tempPrescaler <= maxPrescaler; tempPrescaler++)
    {
        /* get the quanta frequency */
        float Fq = (float)moduleFreq / tempPrescaler;
        /* get the number of time quanta */
        tempNumTq = (int32_t)(Fq / baudrate);

        /* To avoid division by 0 and number of Tq less than minmum number of Tq */
        if((tempNumTq == 0) || (tempNumTq < minNumTq))
        {
            break;
        }

        /* calculate temp baudrate */
        float tempBaudrate = Fq / tempNumTq;
        /* calculate temp baudrate error */
        float tempErr = ((tempBaudrate - baudrate) > 0) ? (tempBaudrate - baudrate) : (baudrate - tempBaudrate);

        if((tempNumTq <= maxNumTq) && (tempErr <= bestErr))
        {
            /* set temporary prescaler, number of Tq, baudrate error as the best value */
            bestPrescaler = tempPrescaler;
            bestNumTq     = tempNumTq;
            bestErr       = tempErr;

            /* check if get the optimal condition */
            if((tempNumTq <= optNumTq) && tempErr < optBaudrateErr)
            {
                break;
            }
        }
    }

    /* calculate sample point (time segment 1) */
    bestErr = samplePoint * optSamplePntToler;

    /* saturate max time segment 1 value */
    if(bestNumTq < maxTseg1)
    {
        maxTseg1 = bestNumTq;
    }
    for(tempTseg1 = maxTseg1; tempTseg1 >= minTseg1; tempTseg1--)
    {
        /* get the temporary sample point */
        int32_t tempSamplePnt = ((tempTseg1 + 1) * 10000) / bestNumTq;
        /* get the temporary sample point error */
        int32_t tempErr = (tempSamplePnt - samplePoint) > 0 ? (tempSamplePnt - samplePoint) : (samplePoint - tempSamplePnt);

        /* break the for loop if the temporary sample point less
           than the user required sample point */
        if(tempSamplePnt < samplePoint)
        {
            break;
        }

        /* update the best T_seg1 and best error if met the tolerance */
        if(tempErr < bestErr)
        {
            bestTseg1 = tempTseg1;
            bestErr   = tempErr;
        }
    }

    /* calculate time segment 2 */
    bestTseg2 = bestNumTq - bestTseg1 - 1;

    /* calculate best SJW */
    bestErr = 10000;
    for(tempSjw = 1; tempSjw <= bestTseg2; tempSjw++)
    {
        /* get the temporary synchronize jump width percentage */
        int32_t tempSjwPercent = (tempSjw * 10000) / bestNumTq;
        int32_t tempErr        = ((tempSjwPercent - sjw) > 0) ? (tempSjwPercent - sjw) : (sjw - tempSjwPercent);

        /*  */
        if(tempErr < bestErr)
        {
            bestSjw = tempSjw;
            bestErr = tempErr;
        }
    }

    bitTimingPara->prescalerDiv    = bestPrescaler;
    bitTimingPara->propSeg         = (uint32_t)(bestTseg1 * 0.6);
    bitTimingPara->phaseSeg1       = bestTseg1 - bitTimingPara->propSeg;
    bitTimingPara->phaseSeg2       = bestTseg2;
    bitTimingPara->resyncJumpWidth = bestSjw;
}

void FlexCanDrv_SetEnhanceRxFFWaterMark(FlexCanDrvType *obj, uint8_t waterMark)
{
    /* set freeze mode enable */
    FlexCanReg_SetFreezeMode(obj->flexCanReg, true);
    /* set halt mode enable */
    FlexCanReg_SetHaltMode(obj->flexCanReg, true);

    /* check for freeze Ack */
    while((FlexCanReg_GetFreezeAck(obj->flexCanReg) == 0) || (FlexCanReg_GetNotReadyFlag(obj->flexCanReg) == 0))
    {
        /* soft reset failed */
    }

    FlexCanReg_SetEnhanceRxFifoWatermark(obj->flexCanReg, waterMark);

    /* set freeze mode disable */
    FlexCanReg_SetFreezeMode(obj->flexCanReg, false);
    /* set halt mode disable */
    FlexCanReg_SetHaltMode(obj->flexCanReg, false);
}

void FlexCanDrv_SetEnhanceRxFFIsr(FlexCanDrvType *obj, uint32_t isrSrcMask, bool enabled)
{
    if(enabled == true)
    {
        if((isrSrcMask & FLEXCANDRV_ENHANCERXFF_ISR_SRC_DAIE) != 0)
        {
            FlexCanReg_SetEnhanceRxFifoDataAvailableIntEnable(obj->flexCanReg, true);
        }

        if((isrSrcMask & FLEXCANDRV_ENHANCERXFF_ISR_SRC_WMMIE) != 0)
        {
            FlexCanReg_SetEnhanceRxFifoWatrmarkIntEnable(obj->flexCanReg, true);
        }

        if((isrSrcMask & FLEXCANDRV_ENHANCERXFF_ISR_SRC_OVFIE) != 0)
        {
            FlexCanReg_SetEnhanceRxFifoOverflowIntEnable(obj->flexCanReg, true);
        }

        if((isrSrcMask & FLEXCANDRV_ENHANCERXFF_ISR_SRC_UFWIE) != 0)
        {
            FlexCanReg_SetEnhanceRxFifoUnderflowIntEnable(obj->flexCanReg, true);
        }
    }
    else
    {
        if((isrSrcMask & FLEXCANDRV_ENHANCERXFF_ISR_SRC_DAIE) != 0)
        {
            FlexCanReg_SetEnhanceRxFifoDataAvailableIntEnable(obj->flexCanReg, false);
        }

        if((isrSrcMask & FLEXCANDRV_ENHANCERXFF_ISR_SRC_WMMIE) != 0)
        {
            FlexCanReg_SetEnhanceRxFifoWatrmarkIntEnable(obj->flexCanReg, false);
        }

        if((isrSrcMask & FLEXCANDRV_ENHANCERXFF_ISR_SRC_OVFIE) != 0)
        {
            FlexCanReg_SetEnhanceRxFifoOverflowIntEnable(obj->flexCanReg, false);
        }

        if((isrSrcMask & FLEXCANDRV_ENHANCERXFF_ISR_SRC_UFWIE) != 0)
        {
            FlexCanReg_SetEnhanceRxFifoUnderflowIntEnable(obj->flexCanReg, false);
        }
    }
}

void FlexCanDrv_ClearEnhanceRxFFIsrFlag(FlexCanDrvType *obj, uint32_t isrSrcMask)
{
    if((isrSrcMask & FLEXCANDRV_ENHANCERXFF_ISR_SRC_DAIE) != 0)
    {
        FlexCanReg_ClearEnhanceRxFifoDataAvailableFlag(obj->flexCanReg);
    }

    if((isrSrcMask & FLEXCANDRV_ENHANCERXFF_ISR_SRC_WMMIE) != 0)
    {
        FlexCanReg_ClearEnhanceRxFifoWatermarkFlag(obj->flexCanReg);
    }

    if((isrSrcMask & FLEXCANDRV_ENHANCERXFF_ISR_SRC_OVFIE) != 0)
    {
        FlexCanReg_ClearEnhanceRxFifoOverflowFlag(obj->flexCanReg);
    }

    if((isrSrcMask & FLEXCANDRV_ENHANCERXFF_ISR_SRC_UFWIE) != 0)
    {
        FlexCanReg_ClearEnhanceRxFifoUnderflowFlag(obj->flexCanReg);
    }
}

bool FlexCanDrv_GetEnhanceRxFFIsrFlag(FlexCanDrvType *obj, FlexCanDrv_EnhanceRxFFIsrSrcType isrSrc)
{
    bool ret = false;

    switch(isrSrc)
    {
    case FLEXCANDRV_ENHANCERXFF_ISR_SRC_DAIE:
        if(FlexCanReg_GetEnhanceRxFifoDataAvailableFlag(obj->flexCanReg) != 0)
        {
            ret = true;
        }
        break;

    case FLEXCANDRV_ENHANCERXFF_ISR_SRC_WMMIE:
        if(FlexCanReg_GetEnhanceRxFifoWatermarkFlag(obj->flexCanReg) != 0)
        {
            ret = true;
        }
        break;

    case FLEXCANDRV_ENHANCERXFF_ISR_SRC_OVFIE:
        if(FlexCanReg_GetEnhanceRxFifoOverflowFlag(obj->flexCanReg) != 0)
        {
            ret = true;
        }
        break;

    case FLEXCANDRV_ENHANCERXFF_ISR_SRC_UFWIE:
        if(FlexCanReg_GetEnhanceRxFifoUnderflowFlag(obj->flexCanReg) != 0)
        {
            ret = true;
        }
        break;

    default:
        break;
    }

    return ret;
}

bool FlexCanDrv_GetEnhanceRxFFIsEmpty(FlexCanDrvType *obj)
{
    bool ret = false;

    if(FlexCanReg_GetEnhanceRxFifoEmptyFlag(obj->flexCanReg) != 0)
    {
        ret = true;
    }

    return ret;
}

bool FlexCanDrv_GetEnhanceRxFFIsFull(FlexCanDrvType *obj)
{
    bool ret = false;

    if(FlexCanReg_GetEnhanceRxFifoFullFlag(obj->flexCanReg) != 0)
    {
        ret = true;
    }

    return ret;
}

uint8_t FlexCanDrv_GetEnhanceRxFFMsgNums(FlexCanDrvType *obj)
{
    uint8_t ret = 0;

    ret = FlexCanReg_GetEnhanceRxFifoElementNum(obj->flexCanReg);

    return ret;
}

void FlexCanDrv_GetEnhanceRxFifoMsg(FlexCanDrvType *obj, FlexCanDrv_MsgObjType *msgObj)
{
    uint32_t *msgBufPtr = (uint32_t *)FlexCanReg_GetEnhRxFifoStartAddr(obj->flexCanReg);
    uint8_t   dlcCode = 0, i = 0;
    bool      isExtMsgId;

    dlcCode           = ((msgBufPtr[0] >> 16) & 0x0F);
    msgObj->timeStamp = msgBufPtr[0] & 0xFFFF;

    msgObj->dlc = FlexCanDrv_DLC2DataLen((FlexCanDrv_DLCType)dlcCode);
    /* get extended message ID bit (CS.IDE) */
    isExtMsgId = (*msgBufPtr & MESSAGE_BUFFER_CS_IDE_MASK) >> MESSAGE_BUFFER_CS_IDE_SHIFT;

    /* set message buffer pointer to ID field */
    msgBufPtr++;

    /* get message ID */
    if(isExtMsgId == true)
    {
        msgObj->msgId = (*msgBufPtr & MESSAGE_BUFFER_ID_EXT_ID_MASK) >> MESSAGE_BUFFER_ID_EXT_ID_SHIFT;
    }
    else
    {
        msgObj->msgId = (*msgBufPtr & MESSAGE_BUFFER_ID_STD_ID_MASK) >> MESSAGE_BUFFER_ID_STD_ID_SHIFT;
    }

    msgBufPtr++;

    for(i = 0; i < msgObj->dlc; i++)
    {
        if((i % 4) == 0)
        {
            /* load 1 byte data from highest byte in 32-bit */
            msgObj->data[i] = (*msgBufPtr >> 24);
        }
        else if((i % 4) == 1)
        {
            /* load 1 byte data from 2nd highest byte in 32-bit */
            msgObj->data[i] = (*msgBufPtr >> 16);
        }
        else if((i % 4) == 2)
        {
            /* load 1 byte data from 3nd highest byte in 32-bit */
            msgObj->data[i] = (*msgBufPtr >> 8);
        }
        /* when (i % 4) == 3 */
        else
        {
            /* load 1 byte data from lowest byte in 32-bit */
            msgObj->data[i] = (*msgBufPtr >> 0);

            /* increment message buffer 32-bit data pointer */
            msgBufPtr++;
        }
    }

    msgBufPtr++;
    msgObj->hrTimeStamp = *msgBufPtr;

    /* Note: must clear the bit, nor make the internal point to the next RX FIFO address */
    FlexCanDrv_ClearEnhanceRxFFIsrFlag(obj, FLEXCANDRV_ENHANCERXFF_ISR_SRC_DAIE);
}
