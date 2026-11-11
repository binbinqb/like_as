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

#include <stddef.h>
#include "dmamux_reg.h"
#include "edma_drv.h"

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

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void EDmaDrv_ClearIntStatus(EDmaDrvType *obj, uint8_t channel);
static void EDmaDrv_ClearSoftwareTCD(EDmaDrv_SoftwareTcdType *stcd);
static void EDmaDrv_ClearStructure(uint8_t *sructPtr, size_t size);

/*******************************************************************************
 * Code
 ******************************************************************************/
void EDmaDrv_BaseInit(EDmaDrvType *obj)
{
    uint8_t i;
    /* Clear the bit of CR register */
    uint32_t regValTemp;
    regValTemp = obj->edmaReg->CR;
    regValTemp &= ~(EDMA_CR_CLM_MASK);
    regValTemp &= ~(EDMA_CR_CX_MASK);
    regValTemp &= ~(EDMA_CR_ECX_MASK);
    regValTemp &= ~(EDMA_CR_EDBG_MASK);
    regValTemp &= ~(EDMA_CR_EMLM_MASK);
    regValTemp &= ~(EDMA_CR_ERCA_MASK);
    obj->edmaReg->CR = regValTemp;

    for(i = 0; i < EDMA_CHANNELS; i++)
    {
        EDmaReg_ClearTcdReg(obj->edmaReg, i);
    }
}

void EDmaDrv_Init(EDmaDrvType *obj, struct _EDmaRegType_ *dmaReg, struct _DmamuxRegType_ *dmamuxReg)
{
    obj->edmaReg   = dmaReg;
    obj->dmamuxReg = dmamuxReg;
}

void EDmaDrv_GetDefaultConfigure(EDmaDrv_ModuleConfigType *userConfig)
{
    userConfig->chnArbitration      = EDMADRV_ARBITRATION_FIXED_PRIORITY;
    userConfig->haltOnError         = false;
    userConfig->channelPriority[0]  = EDMADRV_CHN_PRIORITY_0;
    userConfig->channelPriority[1]  = EDMADRV_CHN_PRIORITY_1;
    userConfig->channelPriority[2]  = EDMADRV_CHN_PRIORITY_2;
    userConfig->channelPriority[3]  = EDMADRV_CHN_PRIORITY_3;
    userConfig->channelPriority[4]  = EDMADRV_CHN_PRIORITY_4;
    userConfig->channelPriority[5]  = EDMADRV_CHN_PRIORITY_5;
    userConfig->channelPriority[6]  = EDMADRV_CHN_PRIORITY_6;
    userConfig->channelPriority[7]  = EDMADRV_CHN_PRIORITY_7;
    userConfig->channelPriority[8]  = EDMADRV_CHN_PRIORITY_8;
    userConfig->channelPriority[9]  = EDMADRV_CHN_PRIORITY_9;
    userConfig->channelPriority[10] = EDMADRV_CHN_PRIORITY_10;
    userConfig->channelPriority[11] = EDMADRV_CHN_PRIORITY_11;
    userConfig->channelPriority[12] = EDMADRV_CHN_PRIORITY_12;
    userConfig->channelPriority[13] = EDMADRV_CHN_PRIORITY_13;
    userConfig->channelPriority[14] = EDMADRV_CHN_PRIORITY_14;
    userConfig->channelPriority[15] = EDMADRV_CHN_PRIORITY_15;
}

void EDmaDrv_GetDefaultChannelConfigure(EDmaDrv_ChannelConfigType *channelConfig)
{
    channelConfig->channelPriority = EDMADRV_CHN_DEFAULT_PRIORITY;
    channelConfig->chnConfig       = 0;
    channelConfig->source          = EDMA_REQ_DISABLED;
    channelConfig->callback        = NULL;
    channelConfig->callbackParam   = NULL;
    channelConfig->enableTrigger   = false;
}

EDmaDrv_Status EDmaDrv_Configure(EDmaDrvType *obj, EDmaDrv_StateType *edmaState, const EDmaDrv_ModuleConfigType *userConfig)
{
    uint32_t index = 0U;

    EDmaDrv_Status edmaStatus    = STATUS_SUCCESS;

    obj->dmaState = edmaState;

#ifdef DMAMUX_AVAILABLE
    /* Initialize all DMAMUX instances */
    DmamuxReg_Init(obj->dmamuxReg);
#endif

    /* Clear the state structure. */
    EDmaDrv_ClearStructure((uint8_t *)obj->dmaState, sizeof(EDmaDrv_StateType));

    /* Init eDMA module on hardware level. */
    EDmaDrv_BaseInit(obj);

    /* Set arbitration mode */
    EDmaReg_SetChannelArbitrationMode(obj->edmaReg, userConfig->chnArbitration);

    if(EDmaReg_GetChannelArbitrationMode(obj->edmaReg) == EDMADRV_ARBITRATION_FIXED_PRIORITY)
    {
        for(index = 0U; index < EDMA_CHANNELS_INTERRUPT_LINES; index++)
        {
            EDmaReg_SetChannelPriority(obj->edmaReg, index, (userConfig->channelPriority[index]));
        }
    }

    /* Set 'Halt on error' configuration */
    EDmaReg_SetHaltOnErrorCmd(obj->edmaReg, userConfig->haltOnError);

    return edmaStatus;
}

EDmaDrv_Status EDmaDrv_ConfigureChannel(EDmaDrvType                           *obj,
                                        EDmaDrv_ChnStateType *const            chnStateArray[],
                                        const EDmaDrv_ChannelConfigType *const chnConfig)
{
    EDmaDrv_Status edmaStatus    = STATUS_SUCCESS;

    /* Initialize the channels based on configuration list */
    if((chnStateArray != NULL) && (chnConfig != NULL))
    {
        edmaStatus = EDmaDrv_ChannelInit(obj, chnStateArray[chnConfig->chnConfig], chnConfig);
    }
    else
    {
        edmaStatus = STATUS_ERROR;
    }
    return edmaStatus;
}

EDmaDrv_Status EDmaDrv_Deinit(EDmaDrvType *obj)
{
    uint32_t                    index    = 0U;

    if(obj->dmaState != NULL)
    {
        /* Release all edma channel. */
        for(index = 0U; index < (uint32_t)EDMA_CHANNELS; index++)
        {
            /* Release all channels. */
            if(obj->dmaState->chnState[index] != NULL)
            {
                (void)EDmaDrv_ReleaseChannel(obj, index);
            }
        }
    }

    obj->dmaState = NULL;

    return STATUS_SUCCESS;
}

EDmaDrv_Status EDmaDrv_ChannelInit(EDmaDrvType                     *obj,
                                   EDmaDrv_ChnStateType            *edmaChannelState,
                                   const EDmaDrv_ChannelConfigType *edmaChannelConfig)
{
    uint8_t channel = edmaChannelConfig->chnConfig;

    /* Get status */
    EDmaDrv_Status retStatus = STATUS_SUCCESS;
    /* Reset the channel state structure to default value. */
    EDmaDrv_ClearStructure((uint8_t *)(edmaChannelState), sizeof(EDmaDrv_ChnStateType));

#ifdef DMAMUX_AVAILABLE
    if(edmaChannelConfig->source != EDMA_REQ_DISABLED)
    {
        retStatus = EDmaDrv_SetChannelRequestAndTrigger(obj,
                                                        edmaChannelConfig->chnConfig,
                                                        (uint8_t)edmaChannelConfig->source,
                                                        edmaChannelConfig->enableTrigger);
    }
#endif

    /* Clear the TCD registers for this channel */
    EDmaReg_ClearTcdReg(obj->edmaReg, channel);

    /* polyspace-begin DEFECT:USELESS_IF [ Not a defect: Low ] "Still keep this if statement." */
    if(retStatus == STATUS_SUCCESS)
    {
        obj->dmaState->chnState[channel]         = edmaChannelState;
        obj->dmaState->chnState[channel]->chn    = channel;
        obj->dmaState->chnState[channel]->status = DMA_CHN_NORMAL;

        /* Set the channel priority, as defined in the configuration, only if fixed arbitration mode is selected */
        if((EDmaReg_GetChannelArbitrationMode(obj->edmaReg) == EDMADRV_ARBITRATION_FIXED_PRIORITY)
           && (edmaChannelConfig->channelPriority != EDMADRV_CHN_DEFAULT_PRIORITY))
        {
            EDmaReg_SetChannelPriority(obj->edmaReg, channel, edmaChannelConfig->channelPriority);
        }
        /* Install the user callback */
        obj->dmaState->chnState[channel]->callback  = edmaChannelConfig->callback;
        obj->dmaState->chnState[channel]->parameter = edmaChannelConfig->callbackParam;
    }
    /* polyspace-end DEFECT:USELESS_IF [ Not a defect: Low ] "Still keep this if statement." */

    return retStatus;
}

EDmaDrv_Status EDmaDrv_InstallCallback(EDmaDrvType *obj, uint8_t channel, EDmaDrv_CallBackType callback, void *parameter)
{
    obj->dmaState->chnState[channel]->callback  = callback;
    obj->dmaState->chnState[channel]->parameter = parameter;
    return STATUS_SUCCESS;
}

EDmaDrv_Status EDmaDrv_ReleaseChannel(EDmaDrvType *obj, uint8_t channel)
{
    /* Stop edma channel. */
    EDmaReg_SetDmaRequestCmd(obj->edmaReg, channel, false);

    /* Reset the channel state structure to default value. */
    EDmaDrv_ClearStructure((uint8_t *)obj->dmaState->chnState[channel], sizeof(EDmaDrv_ChnStateType));

    obj->dmaState->chnState[channel] = NULL;

    return STATUS_SUCCESS;
}

static void EDmaDrv_ClearIntStatus(EDmaDrvType *obj, uint8_t channel)
{
    EDmaReg_ClearDoneStatusFlag(obj->edmaReg, channel);
    EDmaReg_ClearIntStatusFlag(obj->edmaReg, channel);
}

static void EDmaDrv_ClearSoftwareTCD(EDmaDrv_SoftwareTcdType *stcd)
{
    EDmaDrv_ClearStructure((uint8_t *)stcd, sizeof(EDmaDrv_SoftwareTcdType));
}

void EDmaDrv_IRQHandler(EDmaDrvType *obj, uint8_t channel)
{
    const EDmaDrv_ChnStateType *chnState = obj->dmaState->chnState[channel];

    EDmaDrv_ClearIntStatus(obj, channel);

    if(chnState != NULL)
    {
        if(chnState->callback != NULL)
        {
            chnState->callback(chnState->parameter, chnState->status);
        }
    }
}

void EDmaDrv_ErrorIRQHandler(EDmaDrvType *obj, uint8_t channel)
{
    EDmaReg_SetDmaRequestCmd(obj->edmaReg, channel, false);
    EDmaDrv_ChnStateType *chnState = obj->dmaState->chnState[channel];
    if(chnState != NULL)
    {
        EDmaDrv_ClearIntStatus(obj, channel);
        EDmaReg_ClearErrorIntStatusFlag(obj->edmaReg, channel);
        chnState->status = DMA_CHN_ERROR;
        if(chnState->callback != NULL)
        {
            chnState->callback(chnState->parameter, chnState->status);
        }
    }
}

EDmaDrv_Status EDmaDrv_ConfigSingleBlockTransfer(EDmaDrvType             *obj,
                                                 uint8_t                  channel,
                                                 EDmaDrv_TransferType     type,
                                                 uint32_t                 srcAddr,
                                                 uint32_t                 destAddr,
                                                 EDmaDrv_TransferSizeType transferSize,
                                                 uint32_t                 dataBufferSize,
                                                 bool                     enableHwClrDone)
{
    EDmaDrv_Status retStatus = STATUS_SUCCESS;

    /* Compute the transfer offset, based on transfer size.
     * The number of bytes transferred in each source read/destination write
     * is obtained with the following formula:
     *    source_read_size = 2^SSIZE
     *    destination_write_size = 2^DSIZE
     */
    uint8_t transferOffset = (uint8_t)(1U << ((uint8_t)transferSize));

    /* The number of bytes to be transferred (buffer size) must
     * be a multiple of the source read/destination write size
     */
    if((dataBufferSize % transferOffset) != 0U)
    {
        retStatus = STATUS_ERROR;
    }

    if(retStatus == STATUS_SUCCESS)
    {
        /* Clear transfer control descriptor for the current channel */
        EDmaReg_ClearTcdReg(obj->edmaReg, channel);

        EDmaReg_SetMinorLoopMappingCmd(obj->edmaReg, true);

        /* Configure source and destination addresses */
        EDmaReg_SetTcdSrcAddr(obj->edmaReg, channel, srcAddr);
        EDmaReg_SetTcdDestAddr(obj->edmaReg, channel, destAddr);

        /* Set transfer size (1B/2B/4B/16B/32B) */
        EDmaReg_SetTcdAttribute(obj->edmaReg, channel, EDMADRV_MODULO_OFF, EDMADRV_MODULO_OFF, transferSize);

        /* Configure source/destination offset. */
        switch(type)
        {
        case EDMADRV_TRANSFER_PERIPH2MEM:
            EDmaReg_SetTcdSrcOffset(obj->edmaReg, channel, 0);
            EDmaReg_SetTcdDestOffset(obj->edmaReg, channel, (int8_t)transferOffset);
            break;
        case EDMADRV_TRANSFER_MEM2PERIPH:
            EDmaReg_SetTcdSrcOffset(obj->edmaReg, channel, (int8_t)transferOffset);
            EDmaReg_SetTcdDestOffset(obj->edmaReg, channel, 0);
            break;
        case EDMADRV_TRANSFER_MEM2MEM:
            EDmaReg_SetTcdSrcOffset(obj->edmaReg, channel, (int8_t)transferOffset);
            EDmaReg_SetTcdDestOffset(obj->edmaReg, channel, (int8_t)transferOffset);
            break;
        case EDMADRV_TRANSFER_PERIPH2PERIPH:
            EDmaReg_SetTcdSrcOffset(obj->edmaReg, channel, 0);
            EDmaReg_SetTcdDestOffset(obj->edmaReg, channel, 0);
            break;
        default:
            /* This should never be reached - all the possible values have been handled. */
            break;
        }

        /* Set the total number of bytes to be transfered */
        EDmaReg_SetTcdNbytes(obj->edmaReg, channel, dataBufferSize);

        /* Set major iteration count to 1 (single block mode) */
        EDmaReg_SetTcdMajorCount(obj->edmaReg, channel, 1U);

        /* Enable interrupt when the transfer completes */
        EDmaReg_SetTcdMajorCompleteIntCmd(obj->edmaReg, channel, true);

        EDmaReg_SetTcdHardClrDoneCmd(obj->edmaReg, channel, enableHwClrDone);
        /* Set channel status to normal */
        obj->dmaState->chnState[channel]->status = DMA_CHN_NORMAL;
    }

    return retStatus;
}

EDmaDrv_Status EDmaDrv_ConfigMultiBlockTransfer(EDmaDrvType             *obj,
                                                uint8_t                  channel,
                                                EDmaDrv_TransferType     type,
                                                uint32_t                 srcAddr,
                                                uint32_t                 destAddr,
                                                EDmaDrv_TransferSizeType transferSize,
                                                uint32_t                 blockSize,
                                                uint32_t                 blockCount,
                                                bool                     enableHwClrDone,
                                                bool                     disableReqOnCompletion)
{
    EDmaDrv_Status retStatus = STATUS_SUCCESS;

    /* Configure the transfer for one data block */
    retStatus = EDmaDrv_ConfigSingleBlockTransfer(obj, channel, type, srcAddr, destAddr, transferSize, blockSize, enableHwClrDone);

    if(retStatus == STATUS_SUCCESS)
    {
        /* Set the number of data blocks */
        EDmaReg_SetTcdMajorCount(obj->edmaReg, channel, blockCount);

        /* Enable/disable requests upon completion */
        EDmaReg_SetTcdDisableDmaRequestAfterTcdDoneCmd(obj->edmaReg, channel, disableReqOnCompletion);
    }

    return retStatus;
}

EDmaDrv_Status EDmaDrv_ConfigLoopTransfer(EDmaDrvType *obj, uint8_t channel, const EDmaDrv_TransferConfigType *transferConfig)
{
    EDmaReg_SetMinorLoopMappingCmd(obj->edmaReg, true);

    /* Write the configuration in the transfer control descriptor registers */
    EDmaDrv_PushConfigToReg(obj, channel, transferConfig);

    /* Set channel status to normal */
    obj->dmaState->chnState[channel]->status = DMA_CHN_NORMAL;

    return STATUS_SUCCESS;
}

EDmaDrv_Status EDmaDrv_ConfigScatterGatherTransfer(EDmaDrvType                          *obj,
                                                   uint8_t                               channel,
                                                   EDmaDrv_SoftwareTcdType              *stcd,
                                                   EDmaDrv_TransferSizeType              transferSize,
                                                   uint32_t                              bytesOnEachRequest,
                                                   bool                                  hardClrDone,
                                                   const EDmaDrv_ScatterGatherListType  *srcList,
                                                   const EDmaDrv_ScatterGatherListType  *destList,
                                                   const EDmaDrv_LoopTransferConfigType *loopTransferList,
                                                   uint8_t                               tcdCount)
{
    uint8_t                        i               = 0U;
    uint16_t                       transferOffset  = 0U;
    uint32_t                       stcdAlignedAddr = STCD_ADDR(stcd);
    EDmaDrv_SoftwareTcdType       *edmaSwTcdAddr   = (EDmaDrv_SoftwareTcdType *)stcdAlignedAddr;
    EDmaDrv_LoopTransferConfigType edmaLoopConfig;
    EDmaDrv_TransferConfigType     edmaTransferConfig;
    EDmaDrv_Status                 retStatus = STATUS_SUCCESS;

    /* Set channel status to normal */
    obj->dmaState->chnState[channel]->status = DMA_CHN_NORMAL;

    /* Compute the transfer offset, based on transfer size.
     * The number of bytes transferred in each source read/destination write
     * is obtained with the following formula:
     *    source_read_size = 2^SSIZE
     *    destination_write_size = 2^DSIZE
     */
    transferOffset = (uint16_t)(1UL << ((uint16_t)transferSize));

    /* The number of bytes to be transferred on each request must
     * be a multiple of the source read/destination write size
     */
    if((bytesOnEachRequest % transferOffset) != 0U)
    {
        retStatus = STATUS_ERROR;
    }

    /* Clear the configuration structures before initializing them. */
    EDmaDrv_ClearStructure((uint8_t *)(&edmaTransferConfig), sizeof(EDmaDrv_TransferConfigType));
    EDmaDrv_ClearStructure((uint8_t *)(&edmaLoopConfig), sizeof(EDmaDrv_LoopTransferConfigType));

    /* Configure the transfer for scatter/gather mode. */
    edmaTransferConfig.srcLastAddrAdjust                   = 0;
    edmaTransferConfig.destLastAddrAdjust                  = 0;
    edmaTransferConfig.srcModulo                           = EDMADRV_MODULO_OFF;
    edmaTransferConfig.destModulo                          = EDMADRV_MODULO_OFF;
    edmaTransferConfig.srcDestTransferSize                 = transferSize;
    edmaTransferConfig.minorByteTransferCount              = bytesOnEachRequest;
    edmaTransferConfig.interruptEnable                     = true;
    edmaTransferConfig.scatterGatherEnable                 = true;
    edmaTransferConfig.hardClrDone                         = hardClrDone;
    edmaTransferConfig.loopTransferConfig                  = &edmaLoopConfig;
    edmaTransferConfig.loopTransferConfig->srcOffsetEnable = false;
    edmaTransferConfig.loopTransferConfig->dstOffsetEnable = false;


    /* Copy scatter/gather lists to transfer configuration*/
    for(i = 0U; (i < tcdCount) && (retStatus == STATUS_SUCCESS); i++)
    {
        if(loopTransferList != NULL)
        {
            edmaTransferConfig.loopTransferConfig->minorLoopChnLinkEnable = loopTransferList[i].minorLoopChnLinkEnable;
            edmaTransferConfig.loopTransferConfig->majorLoopChnLinkEnable = loopTransferList[i].majorLoopChnLinkEnable;
            edmaTransferConfig.loopTransferConfig->minorLoopChnLinkNumber = loopTransferList[i].minorLoopChnLinkNumber;
            edmaTransferConfig.loopTransferConfig->majorLoopChnLinkNumber = loopTransferList[i].majorLoopChnLinkNumber;
        }
        else
        {
            edmaTransferConfig.loopTransferConfig->minorLoopChnLinkEnable = false;
            edmaTransferConfig.loopTransferConfig->majorLoopChnLinkEnable = false;
            edmaTransferConfig.loopTransferConfig->minorLoopChnLinkNumber = 0;
            edmaTransferConfig.loopTransferConfig->majorLoopChnLinkNumber = 0;
        }

        edmaTransferConfig.srcAddr  = srcList[i].address;
        edmaTransferConfig.destAddr = destList[i].address;
        if((srcList[i].length != destList[i].length) || (srcList[i].type != destList[i].type))
        {
            retStatus = STATUS_ERROR;
            break;
        }
        edmaTransferConfig.loopTransferConfig->majorLoopIterationCount = srcList[i].length / bytesOnEachRequest;

        switch(srcList[i].type)
        {
        case EDMADRV_TRANSFER_PERIPH2MEM:
            /* Configure Source Read. */
            edmaTransferConfig.srcOffset = 0;
            /* Configure Dest Write. */
            edmaTransferConfig.destOffset = (int16_t)transferOffset;
            break;
        case EDMADRV_TRANSFER_MEM2PERIPH:
            /* Configure Source Read. */
            edmaTransferConfig.srcOffset = (int16_t)transferOffset;
            /* Configure Dest Write. */
            edmaTransferConfig.destOffset = 0;
            break;
        case EDMADRV_TRANSFER_MEM2MEM:
            /* Configure Source Read. */
            edmaTransferConfig.srcOffset = (int16_t)transferOffset;
            /* Configure Dest Write. */
            edmaTransferConfig.destOffset = (int16_t)transferOffset;
            break;
        case EDMADRV_TRANSFER_PERIPH2PERIPH:
            /* Configure Source Read. */
            edmaTransferConfig.srcOffset = 0;
            /* Configure Dest Write. */
            edmaTransferConfig.destOffset = 0;
            break;
        default:
            /* This should never be reached - all the possible values have been handled. */
            break;
        }

        /* Configure the pointer to next software TCD structure; for the last one, this address should be 0 */
        EDmaDrv_SoftwareTcdType *ptNextAddr;
        
        if(i == ((uint8_t)(tcdCount - 1U)))
        {
            ptNextAddr          = &edmaSwTcdAddr[0];
        }
        else
        {
            ptNextAddr          = &edmaSwTcdAddr[i + 1];
        }
        edmaTransferConfig.scatterGatherNextDescAddr = ((uint32_t)ptNextAddr);

        if(i == 0U)
        {
            /* Push the configuration for the first descriptor to registers */
            EDmaDrv_PushConfigToReg(obj, channel, &edmaTransferConfig);
        }
        EDmaDrv_PushConfigToSTcd(&edmaTransferConfig, &edmaSwTcdAddr[i]);
    }

    return retStatus;
}

EDmaDrv_Status EDmaDrv_StartChannel(EDmaDrvType *obj, uint8_t channel)
{
    /* Enable requests for current channel */
    EDmaReg_SetDmaRequestCmd(obj->edmaReg, channel, true);

    return STATUS_SUCCESS;
}

EDmaDrv_Status EDmaDrv_StopChannel(EDmaDrvType *obj, uint8_t channel)
{
    /* Disable requests for current channel */
    EDmaReg_SetDmaRequestCmd(obj->edmaReg, channel, false);

    return STATUS_SUCCESS;
}

EDmaDrv_Status EDmaDrv_SetChannelRequestAndTrigger(EDmaDrvType *obj, uint8_t channel, uint8_t request, bool enableTrigger)
{
#ifdef DMAMUX_AVAILABLE
    /* Get request index for the corresponding DMAMUX instance */
    uint8_t dmaMuxRequest = (uint8_t)request;

    /* Set request and trigger */
    DmamuxReg_SetChannelCmd(obj->dmamuxReg, channel, false);
    DmamuxReg_SetChannelSource(obj->dmamuxReg, channel, dmaMuxRequest);
#ifdef DMAMUX_HAS_TRIG
    DmamuxReg_SetChannelTrigger(obj->dmamuxReg, channel, enableTrigger);
#else
    (void)enableTrigger;
#endif
    DmamuxReg_SetChannelCmd(obj->dmamuxReg, channel, true);

    return STATUS_SUCCESS;
#else
    (void)channel;
    (void)request;
    (void)enableTrigger;
    return STATUS_UNSUPPORTED;
#endif
}

void EDmaDrv_ClearTcd(EDmaDrvType *obj, uint8_t channel)
{
    /* Clear the TCD memory */
    EDmaReg_ClearTcdReg(obj->edmaReg, channel);
}

void EDmaDrv_SetSrcAddr(EDmaDrvType *obj, uint8_t channel, uint32_t address)
{
    /* Set channel TCD source address */
    EDmaReg_SetTcdSrcAddr(obj->edmaReg, channel, address);
}

void EDmaDrv_SetSrcOffset(EDmaDrvType *obj, uint8_t channel, int16_t offset)
{
    /* Set channel TCD source offset */
    EDmaReg_SetTcdSrcOffset(obj->edmaReg, channel, (uint16_t)offset);
}

void EDmaDrv_SetSrcReadDestWriteChunkSize(EDmaDrvType *obj, uint8_t channel, EDmaDrv_TransferSizeType size)
{
    /* Set channel TCD source transfer size */
    EDmaReg_SetTcdSrcDesTransferSize(obj->edmaReg, channel, size);
}

void EDmaDrv_SetSrcLastAddrAdjustment(EDmaDrvType *obj, uint8_t channel, int32_t adjust)
{
    /* Set channel TCD source last adjustment */
    EDmaReg_SetTcdSrcLastAdjust(obj->edmaReg, channel, adjust);
}

void EDmaDrv_SetDestLastAddrAdjustment(EDmaDrvType *obj, uint8_t channel, int32_t adjust)
{
    /* Set channel TCD source last adjustment */
    EDmaReg_SetTcdDestLastAdjust(obj->edmaReg, channel, adjust);
}

void EDmaDrv_SetDestAddr(EDmaDrvType *obj, uint8_t channel, uint32_t address)
{
    /* Set channel TCD destination address */
    EDmaReg_SetTcdDestAddr(obj->edmaReg, channel, address);
}

void EDmaDrv_SetDestOffset(EDmaDrvType *obj, uint8_t channel, int16_t offset)
{
    /* Set channel TCD destination offset */
    EDmaReg_SetTcdDestOffset(obj->edmaReg, channel, (uint16_t)offset);
}

void EDmaDrv_SetMinorLoopBlockSize(EDmaDrvType *obj, uint8_t channel, uint32_t nbytes)
{
    /* Set channel TCD minor loop block size */
    EDmaReg_SetTcdNbytes(obj->edmaReg, channel, nbytes);
}

void EDmaDrv_SetMajorLoopIterationCount(EDmaDrvType *obj, uint8_t channel, uint32_t majorLoopCount)
{
    /* Set the major loop iteration count */
    EDmaReg_SetTcdMajorCount(obj->edmaReg, channel, majorLoopCount);
}

uint32_t EDmaDrv_GetRemainingMajorIterationsCount(EDmaDrvType *obj, uint8_t channel)
{
    /* Retrieve the number of minor loops yet to be triggered */
    uint32_t count = EDmaReg_GetTcdCurrentMajorCount(obj->edmaReg, channel);

    return count;
}

void EDmaDrv_SetScatterGatherLink(EDmaDrvType *obj, uint8_t channel, uint32_t nextTCDAddr)
{
    /* Configures the memory address of the next TCD */
    EDmaReg_SetTcdScatterGatherLink(obj->edmaReg, channel, nextTCDAddr);
}

void EDmaDrv_DisableRequestsOnTransferComplete(EDmaDrvType *obj, uint8_t channel, bool disable)
{
    /* Disables/Enables the DMA request upon TCD completion */
    EDmaReg_SetTcdDisableDmaRequestAfterTcdDoneCmd(obj->edmaReg, channel, disable);
}

void EDmaDrv_ConfigureInterrupt(EDmaDrvType *obj, uint8_t channel, EDmaDrv_ChannelInterruptType intSrc, bool enable)
{
    /* Disables/Enables the channel interrupt requests. */
    switch(intSrc)
    {
    case EDMADRV_CHN_ERR_INT:
        /* Enable channel interrupt request when error conditions occur */
        EDmaReg_SetErrorIntCmd(obj->edmaReg, channel, enable);
        break;
    case EDMADRV_CHN_HALF_MAJOR_LOOP_INT:
        /* Enable channel interrupt request when major iteration count reaches halfway point */
        EDmaReg_SetTcdMajorHalfCompleteIntCmd(obj->edmaReg, channel, enable);
        break;
    case EDMADRV_CHN_MAJOR_LOOP_INT:
        /* Enable channel interrupt request when major iteration count reaches zero */
        EDmaReg_SetTcdMajorCompleteIntCmd(obj->edmaReg, channel, enable);
        break;
    default:
        /* This branch should never be reached if driver API is used properly */
        break;
    }
}

void EDmaDrv_CancelTransfer(EDmaDrvType *obj, bool error)
{
    /* Cancel the running transfer. */
    if(error)
    {
        EDmaReg_CancelTransferWithError(obj->edmaReg);
    }
    else
    {
        EDmaReg_CancelTransfer(obj->edmaReg);
    }
}

void EDmaDrv_TriggerSwRequest(EDmaDrvType *obj, uint8_t channel)
{
    /* Trigger the channel transfer. */
    EDmaReg_SetChannelStartFlag(obj->edmaReg, channel);
}

void EDmaDrv_PushConfigToSTcd(const EDmaDrv_TransferConfigType *config, EDmaDrv_SoftwareTcdType *stcd)
{
    if((config != NULL) && (stcd != NULL))
    {
        /* Clear the array of software TCDs passed by the user */
        EDmaDrv_ClearSoftwareTCD(stcd);

        /* Set the software TCD fields */
        stcd->ATTR   = (uint16_t)(EDMA_TCD_ATTR_SMOD(config->srcModulo) | EDMA_TCD_ATTR_SDSIZE(config->srcDestTransferSize)
                                | EDMA_TCD_ATTR_DMOD(config->destModulo));
        stcd->SADDR  = config->srcAddr;
        stcd->SOFF   = config->srcOffset;
        stcd->NBYTES = config->minorByteTransferCount;
        stcd->SLAST  = config->srcLastAddrAdjust;
        stcd->DADDR  = config->destAddr;
        stcd->DOFF   = config->destOffset;
        stcd->CITER  = (uint16_t)config->loopTransferConfig->majorLoopIterationCount;
        stcd->BITER  = (uint16_t)config->loopTransferConfig->majorLoopIterationCount;
        if(config->scatterGatherEnable)
        {
            stcd->DLAST_SGA = (int32_t)config->scatterGatherNextDescAddr;
        }
        else
        {
            stcd->DLAST_SGA = config->destLastAddrAdjust;
        }
        stcd->CSR = (uint16_t)(((config->interruptEnable ? 1UL : 0UL) << EDMA_TCD_CSR_INTMAJOR_SHIFT)
                               | ((config->scatterGatherEnable ? 1UL : 0UL) << EDMA_TCD_CSR_ESG_SHIFT));

        if (config->hardClrDone)
        {
            stcd->CSR |= EDMA_TCD_CSR_HARD_CLR_DONE_MASK;
        }
        else
        {
            stcd->CSR &= ~EDMA_TCD_CSR_HARD_CLR_DONE_MASK;
        }


        if(config->loopTransferConfig->majorLoopChnLinkEnable)
        {
            stcd->CSR |= (uint16_t)((EDMA_TCD_CSR_MAJORELINK_MASK)
                                   | (config->loopTransferConfig->majorLoopChnLinkNumber << EDMA_TCD_CSR_MAJORLINKCH_SHIFT));
        }
        else
        {
            stcd->CSR &= ~((uint16_t)EDMA_TCD_CSR_MAJORELINK_MASK);
            stcd->CSR &= ~((uint16_t)EDMA_TCD_CSR_MAJORLINKCH_MASK);
        }

        if(config->loopTransferConfig->minorLoopChnLinkEnable)
        {
            uint16_t biterElinkTemp;
            biterElinkTemp = stcd->CITER;
            biterElinkTemp |=  EDMA_TCD_BITER_ELINKYES_ELINK_MASK;
            biterElinkTemp &= (uint16_t) ~(EDMA_TCD_BITER_ELINKYES_LINKCH_MASK);
            biterElinkTemp |= (((uint16_t)(((uint16_t)(config->loopTransferConfig->minorLoopChnLinkNumber)) << EDMA_TCD_BITER_ELINKYES_LINKCH_SHIFT)) & EDMA_TCD_BITER_ELINKYES_LINKCH_MASK);
            stcd->CITER = biterElinkTemp;
            stcd->BITER = biterElinkTemp;
        }
        else
        {
            stcd->CITER &= (uint16_t) ~(EDMA_TCD_BITER_ELINKYES_LINKCH_MASK);
            stcd->BITER &= (uint16_t) ~(EDMA_TCD_BITER_ELINKYES_LINKCH_MASK);
            stcd->CITER &=  ~EDMA_TCD_BITER_ELINKYES_ELINK_MASK;
            stcd->BITER &=  ~EDMA_TCD_BITER_ELINKYES_ELINK_MASK;
        }
    }
}

void EDmaDrv_PushConfigToReg(EDmaDrvType *obj, uint8_t channel, const EDmaDrv_TransferConfigType *tcd)
{
    /* Clear TCD registers */
    EDmaReg_ClearTcdReg(obj->edmaReg, channel);

    /* Set source and destination addresses */
    EDmaReg_SetTcdSrcAddr(obj->edmaReg, channel, tcd->srcAddr);
    EDmaReg_SetTcdDestAddr(obj->edmaReg, channel, tcd->destAddr);
    /* Set source/destination modulo feature and transfer size */
    EDmaReg_SetTcdAttribute(obj->edmaReg, channel, tcd->srcModulo, tcd->destModulo, tcd->srcDestTransferSize);
    /* Set source/destination offset and last adjustment; for scatter/gather operation, destination
     * last adjustment is the address of the next TCD structure to be loaded by the eDMA engine */
    EDmaReg_SetTcdSrcOffset(obj->edmaReg, channel, (uint16_t)tcd->srcOffset);
    EDmaReg_SetTcdDestOffset(obj->edmaReg, channel, (uint16_t)tcd->destOffset);
    EDmaReg_SetTcdSrcLastAdjust(obj->edmaReg, channel, tcd->srcLastAddrAdjust);

    if(tcd->scatterGatherEnable)
    {
        EDmaReg_SetTcdScatterGatherCmd(obj->edmaReg, channel, true);
        EDmaReg_SetTcdScatterGatherLink(obj->edmaReg, channel, tcd->scatterGatherNextDescAddr);
    }
    else
    {
        EDmaReg_SetTcdScatterGatherCmd(obj->edmaReg, channel, false);
        EDmaReg_SetTcdDestLastAdjust(obj->edmaReg, channel, tcd->destLastAddrAdjust);
    }

    /* Configure channel interrupt */
    EDmaReg_SetTcdMajorCompleteIntCmd(obj->edmaReg, channel, tcd->interruptEnable);

    /* Configure channel clear done automatically*/
    EDmaReg_SetTcdHardClrDoneCmd(obj->edmaReg, channel, tcd->hardClrDone);

    /* If loop configuration is available, copy minor/major loop setup to registers */
    if(tcd->loopTransferConfig != NULL)
    {
        EDmaReg_SetTcdSrcMinorLoopOffsetCmd(obj->edmaReg, channel, tcd->loopTransferConfig->srcOffsetEnable);
        EDmaReg_SetTcdDestMinorLoopOffsetCmd(obj->edmaReg, channel, tcd->loopTransferConfig->dstOffsetEnable);
        EDmaReg_SetTcdMinorLoopOffset(obj->edmaReg, channel, tcd->loopTransferConfig->minorLoopOffset);
        EDmaReg_SetTcdNbytes(obj->edmaReg, channel, tcd->minorByteTransferCount);

        EDmaReg_SetTcdChannelMinorLink(obj->edmaReg,
                                       channel,
                                       tcd->loopTransferConfig->minorLoopChnLinkNumber,
                                       tcd->loopTransferConfig->minorLoopChnLinkEnable);
        EDmaReg_SetTcdChannelMajorLink(obj->edmaReg,
                                       channel,
                                       tcd->loopTransferConfig->majorLoopChnLinkNumber,
                                       tcd->loopTransferConfig->majorLoopChnLinkEnable);

        EDmaReg_SetTcdMajorCount(obj->edmaReg, channel, tcd->loopTransferConfig->majorLoopIterationCount);
    }
    else
    {
        EDmaReg_SetTcdNbytes(obj->edmaReg, channel, tcd->minorByteTransferCount);
    }

    if (EDmaReg_GetChannelErrorStatusFlag(obj->edmaReg, channel))
    {
        EDmaReg_ClearErrorIntStatusFlag(obj->edmaReg, channel);
    }
}

#if defined(CUSTOM_DEVASSERT) || defined(DEV_ERROR_DETECT)
/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_DRV_ValidTransferSize
 * Description   : Check if the transfer size value is legal (0/1/2/4/5).
 *
 *END**************************************************************************/
static bool EDmaDrv_ValidTransferSize(edma_transfer_size_t size)
{
    bool isValid;
    switch(size)
    {
    case EDMA_TRANSFER_SIZE_1B:
    case EDMA_TRANSFER_SIZE_2B:
    case EDMA_TRANSFER_SIZE_4B:
#ifdef FEATURE_DMA_TRANSFER_SIZE_8B
    case EDMA_TRANSFER_SIZE_8B:
#endif
#ifdef FEATURE_DMA_TRANSFER_SIZE_16B
    case EDMA_TRANSFER_SIZE_16B:
#endif
#ifdef FEATURE_DMA_TRANSFER_SIZE_32B
    case EDMA_TRANSFER_SIZE_32B:
#endif
#ifdef FEATURE_DMA_TRANSFER_SIZE_64B
    case EDMA_TRANSFER_SIZE_64B:
#endif
        isValid = true;
        break;
    default:
        isValid = false;
        break;
    }
    return isValid;
}
#endif

EDmaDrv_ChnStatusType EDmaDrv_GetChannelStatus(EDmaDrvType *obj, uint8_t channel)
{
    return obj->dmaState->chnState[channel]->status;
}

static void EDmaDrv_ClearStructure(uint8_t *sructPtr, size_t size)
{
    while(size > 0U)
    {
        *sructPtr = 0;
        sructPtr++;
        size--;
    }
}
