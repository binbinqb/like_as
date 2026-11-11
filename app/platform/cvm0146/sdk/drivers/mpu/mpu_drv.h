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

#ifndef _MPU_DRV_H_
#define _MPU_DRV_H_

/*! \brief Contains public interface to various functions related
 *         to the driver of MPU
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/*! \addtogroup mpu_drv
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

/*! \brief MPU access error
 */
typedef enum
{
    MPUDRV_ERRTYPE_READ  = 0U, /*!< MPU error type: read  */
    MPUDRV_ERRTYPE_WRITE = 1U  /*!< MPU error type: write */
} MpuDrv_AccType;

/*! \brief MPU access error attributes
 */
typedef enum
{
    MPUDRV_INSTRUCTION_ACCESS_IN_USER_MODE       = 0U, /*!< Access instruction error in user mode       */
    MPUDRV_DATA_ACCESS_IN_USER_MODE              = 1U, /*!< Access data error in user mode              */
    MPUDRV_INSTRUCTION_ACCESS_IN_SUPERVISOR_MODE = 2U, /*!< Access instruction error in supervisor mode */
    MPUDRV_DATA_ACCESS_IN_SUPERVISOR_MODE        = 3U  /*!< Access data error in supervisor mode        */
} MpuDrv_AttrType;

/*! \brief MPU Region Description Number
 */
typedef enum
{
    MPUDRV_NUMOFRGD_8  = 0U, /*!< MPU Total Number of Region 8 Descriptions  */
    MPUDRV_NUMOFRGD_12 = 1U, /*!< MPU Total Number of Region 12 Descriptions */
    MPUDRV_NUMOFRGD_16 = 2U, /*!< MPU Total Number of Region 16 Descriptions */
} MpuDrv_RegDescTotalNumType;

/*! \brief MPU access Master Type
 *  Implements : MpuDrv_MasterType
 */
typedef enum
{
    MPUDRV_MASTER_CPU      = 0U, /*!< MPU Access Master Type CPU      */
    MPUDRV_MASTER_DEBUGGER = 1U, /*!< MPU Access Master Type DEBUGGER */
    MPUDRV_MASTER_DMA      = 2U, /*!< MPU Access Master Type DMA      */
    MPUDRV_MASTER_CSE      = 3U, /*!< MPU Access Master Type CSE      */
    MPUDRV_MASTER_NUMMAX   = 4U  /*!< Master Number value Max         */
} MpuDrv_MasterType;

/*! \brief MPU slave port Type
 */
typedef enum
{
    MPUDRV_SLVPORT0   = 0U, /*!< MPU Slave Port Number0   */
    MPUDRV_SLVPORT1   = 1U, /*!< MPU Slave Port Number1   */
    MPUDRV_SLVPORT2   = 2U, /*!< MPU Slave Port Number2   */
    MPUDRV_SLVPORT3   = 3U, /*!< MPU Slave Port Number3   */
    MPUDRV_SLVPORTMAX = 4U  /*!< MPU Slave Port NumberMax */
} MpuDrv_SlvPortNumType;

/*! \brief MPU Region Description Type
 */
typedef enum
{
    MPUDRV_CH0   = 0U,  /*!< MPU RGD channel number 0  */
    MPUDRV_CH1   = 1U,  /*!< MPU RGD channel number 1  */
    MPUDRV_CH2   = 2U,  /*!< MPU RGD channel number 2  */
    MPUDRV_CH3   = 3U,  /*!< MPU RGD channel number 3  */
    MPUDRV_CH4   = 4U,  /*!< MPU RGD channel number 4  */
    MPUDRV_CH5   = 5U,  /*!< MPU RGD channel number 5  */
    MPUDRV_CH6   = 6U,  /*!< MPU RGD channel number 6  */
    MPUDRV_CH7   = 7U,  /*!< MPU RGD channel number 7  */
    MPUDRV_CH8   = 8U,  /*!< MPU RGD channel number 8  */
    MPUDRV_CH9   = 9U,  /*!< MPU RGD channel number 9  */
    MPUDRV_CH10  = 10U, /*!< MPU RGD channel number 10 */
    MPUDRV_CH11  = 11U, /*!< MPU RGD channel number 11 */
    MPUDRV_CH12  = 12U, /*!< MPU RGD channel number 12 */
    MPUDRV_CH13  = 13U, /*!< MPU RGD channel number 13 */
    MPUDRV_CH14  = 14U, /*!< MPU RGD channel number 14 */
    MPUDRV_CH15  = 15U, /*!< MPU RGD channel number 15 */
    MPUDRV_CHMAX = 16U  /*!< MPU RGD channel total num */
} MpuDrv_RegDescChnNumType;

/*! \brief MPU privilege access rights.
 */
typedef enum
{
    MPUDRV_SUPERVISOR_RWX          = 0x0U, /*!< 0b00U : rwx, Allow Read, write, execute in supervisor mode */
    MPUDRV_SUPERVISOR_RX           = 0x1U, /*!< 0b01U : r-x, Allow Read, execute in supervisor mode        */
    MPUDRV_SUPERVISOR_RW           = 0x2U, /*!< 0b10U : rw-, Allow Read, write in supervisor mode          */
    MPUDRV_SUPERVISOR_SAME_AS_USER = 0x3U, /*!< 0b11U : xxx, Allow right the same as user mode             */
} MpuDrv_MasterPrivilegeAccType;

/*! \brief MPU user access rights.
 */
typedef enum
{
    MPUDRV_USER_NONE = 0x00U, /*!< 0b000U : ---, No access allowed user modes                           */
    MPUDRV_USER_X    = 0x01U, /*!< 0b001U : --x, Execute operation is allowed user modes                */
    MPUDRV_USER_W    = 0x02U, /*!< 0b010U : -w-, Write operation is allowed user modes                  */
    MPUDRV_USER_WX   = 0x03U, /*!< 0b011U : -wx, Write and execute operations are allowed in user modes */
    MPUDRV_USER_R    = 0x04U, /*!< 0b100U : r--, Read operation is allowed user modes                   */
    MPUDRV_USER_RX   = 0x05U, /*!< 0b101U : r-x, Allow Read, execute in user mode                       */
    MPUDRV_USER_RW   = 0x06U, /*!< 0b110U : rw-, Allow Read, write in user mode                         */
    MPUDRV_USER_RWX  = 0x07U, /*!< 0b111U : rwx, Allow Read, write, execute in user mode                */
} MpuDrv_MasterUserAccType;

/* Forward declaration of MPU register */
struct _MpuRegType_;

/*! \brief The definition of MPU driver class
 */
typedef struct _MpuDrvType_
{
    struct _MpuRegType_ *reg;
} MpuDrvType;

/*! \brief MPU control info
 */
typedef struct _MpuDrv_CtrlInfoType_
{
    bool                       mpuValid;                            /*!< MPU main enable                       */
    MpuDrv_RegDescTotalNumType mpuTotalNumRegDesc;                  /*!< MPU channel num of region description */
    bool                       slvPortErrStatus[MPUDRV_SLVPORTMAX]; /*!< MPU slave portx error status          */
} MpuDrv_CtrlInfoType;

/*! \brief MPU slave port detail error access info
 */
typedef struct _MpuDrv_SlvPortErrInfoType_
{
    MpuDrv_MasterType master;    /*!< Access error master                   */
    MpuDrv_AttrType   attrbutes; /*!< Access error attributes               */
    MpuDrv_AccType    accType;   /*!< Access error type                     */
    uint16_t           accCtrl;   /*!< Access error control(EACD)            */
    uint32_t          addr;      /*!< Access error address                  */
    uint8_t           pidNumber; /*!< Access error processor identification */
} MpuDrv_SlvPortErrInfoType;

/*! \brief MPU master access rights.
 */
typedef struct _MpuDrv_MasterAccConfigType_
{
    MpuDrv_MasterPrivilegeAccType masterPrivilegeAccRight; /*!< Master Privilege Access right          */
    MpuDrv_MasterUserAccType      masterUserAccRight;      /*!< Master User Access right               */
    bool                          pidFlagEnable;           /*!< Enables or disables process identifier */
} MpuDrv_MasterAccConfigType;

/*! \brief MPU Region Description rights
 */
typedef struct _MpuDrv_RegDescType_
{
    uint32_t                   startAddr;                            /*!< Memory region start address                                                             */
    uint32_t                   endAddr;                              /*!< Memory region end address                                                               */
    MpuDrv_MasterAccConfigType masterAccRight[MPUDRV_MASTER_NUMMAX]; /*!< Access right for masters                                                                */
    uint8_t                    pidNumber;                            /*!< Process identifier                                                                      */
    uint8_t                    pidMask;                              /*!< Process identifier mask. The setting bit will ignore the same bit in process identifier */
    bool                       chnEnable;                            /*!< current channel protect function enable                                                 */
} MpuDrv_RegDescType;

/*! \brief The definition of MPU driver class
 */
typedef struct _MpuDrv_ConfigType_
{
    MpuDrv_CtrlInfoType        ctrlInfo;                          /*!< MPU main ctrl info                      */
    MpuDrv_SlvPortErrInfoType  slvPortErrInfo[MPUDRV_SLVPORTMAX]; /*!< MPU slave port error info               */
    MpuDrv_RegDescType         regDescCfgInfo[MPUDRV_CHMAX];      /*!< MPU region description config info      */
    MpuDrv_MasterAccConfigType aacCfgInfo[MPUDRV_CHMAX];          /*!< MPU AAC register config info            */
    bool                       isEnableErrPid;                    /*!< MPU Error PID is enable, user determine */
} MpuDrv_ConfigType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Initializes the MPU driver module
 *
 * This function initializes MPU driver by setting the register
 * instance to it.
 *
 * \param[in] obj : pointer to MPU driver instance
 * \param[in] reg : pointer to MPU register instance
 */
extern void MpuDrv_Init(MpuDrvType *obj, struct _MpuRegType_ *reg);

/*! \brief Get MPU Default Config
 *
 * This function get MPU all default paramters
 *
 * \param[in] obj : pointer to MPU driver instance
 * \param[in] userConfig : pointer to user get all default
 *
 */
extern void MpuDrv_GetDefaultConfig(MpuDrv_ConfigType *userConfig);

/*! \brief Get MPU common Control Config
 *
 * This function get MPU common control paramters
 *
 * \param[in] obj : pointer to MPU driver instance
 * \param[in] ctrlInfo : pointer to common config paramter
 *
 */
extern void MpuDrv_GetCtrlInfo(MpuDrvType *obj, MpuDrv_CtrlInfoType *ctrlInfo);

/*! \brief Get MPU slave port Error info
 *
 * This function get MPU slave error info
 *
 * \param[in] obj : pointer to MPU driver instance
 * \param[in] slvPortErrInfo : slave port error info
 * \param[in] isEnablePID : PID status
 *
 */
extern void MpuDrv_GetSlvPortErrInfo(MpuDrvType *obj, MpuDrv_SlvPortErrInfoType *slvPortErrInfo, bool isEnablePid);

/*! \brief Get MPU Master Config
 *
 * This function get MPU master config
 *
 * \param[in] obj : pointer to MPU driver instance
 * \param[in] masterAccRight : master access right
 * \param[in] regDescNum : region description number
 * \param[in] masterNum : master number
 *
 */
extern void MpuDrv_GetMasterAccRight(MpuDrvType *obj, MpuDrv_MasterAccConfigType *masterAccRight, MpuDrv_RegDescChnNumType regDescNum, MpuDrv_MasterType masterNum);

/*! \brief Get MPU Region Description config
 *
 * This function get MPU region description config parameters
 *
 * \param[in] obj : pointer to MPU driver instance
 * \param[in] regDesc : pointer to region description config parameter
 * \param[in] isEnablePID : region description PID enable status
 *
 */
extern void MpuDrv_GetRegDescCfgInfo(MpuDrvType *obj, MpuDrv_RegDescType *regDesc, bool isEnablePid);

/*! \brief Get MPU Master Access Right
 *
 * This function get MPU master access right
 *
 * \param[in] obj : pointer to MPU driver instance
 * \param[in] aacRegDesc : pointer to mster access right paramter
 *
 */
extern void MpuDrv_GetAacCtrlInfo(MpuDrvType *obj, MpuDrv_MasterAccConfigType *aacRegDesc);

/*! \brief Get MPU Current all Config
 *
 * This function get MPU current all config paramters
 *
 * \param[in] obj : pointer to MPU driver instance
 * \param[in] userConfig : pointer to user get current all config
 *
 */
extern void MpuDrv_GetConfigure(MpuDrvType *obj, MpuDrv_ConfigType *userConfig);

/*! \brief Set Region Description channel Enable
 *
 * This function set mpu region description channle enable
 *
 * \param[in] obj : pointer to MPU driver instance
 * \param[in] chnNum : select config channel
 * \param[in] enable :
 *             - true : enable
 *             - false : disable
 *
 */
extern void MpuDrv_EnableRegDescChn(MpuDrvType *obj, MpuDrv_RegDescChnNumType chnNum, bool enable);

/*! \brief Set Region Description channel Enable
 *
 * This function set mpu region description channle enable
 *
 * \param[in] obj : pointer to MPU driver instance
 * \param[in] regDescCfg : pointer to region description
 * \param[in] regDescChnNum : region description number
 * \param[in] pidEnable :
 *             - true : enable
 *             - false : disable
 *
 */
extern void MpuDrv_SetRegDescChnCfg(MpuDrvType *obj,const MpuDrv_RegDescType *regDescCfg, MpuDrv_RegDescChnNumType regDescChnNum, bool pidEnable);

/*! \brief Set Master Access Right
 *
 * This function set master access ram or flash right
 *
 * \param[in] obj : pointer to MPU driver instance
 * \param[in] aacRegDesc : pointer to master access right
 * \param[in] regDescChnNum : region description number
 * \param[in] masterNum : master number
 *
 */
extern void MpuDrv_SetAacCtrlInfo(MpuDrvType *obj, MpuDrv_MasterAccConfigType *aacRegDesc, MpuDrv_RegDescChnNumType regDescChnNum, MpuDrv_MasterType masterNum);

/*! \brief Get MPU enable status
 *
 * This function get MPU enable status enable
 *
 * \param[in] obj : pointer to MPU driver instance
 *
 */
extern bool MpuDrv_GetGlobalEnableStatus(MpuDrvType *obj);

/*! \brief Get MPU enable status
 *
 * This function get MPU enable status enable
 *
 * \param[in] obj : pointer to MPU driver instance
 * \param[in] enable :
 *             - true : enable
 *             - false : disable
 *
 */
extern void MpuDrv_SetGlobalEnable(MpuDrvType *obj, bool enable);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _MPU_DRV_H_ */
