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

#ifndef _EIM_DRV_H_
#define _EIM_DRV_H_

/*! \brief Contains public interface to various functions related
 *         to the driver of EIM
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/*! \addtogroup eim_drv
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

/*! \brief Definition of enable of EIM Channel
 */
typedef enum
{
    EIMDRV_ERRIN_ENABLE_CH0    = 0x00U, /*!< Error In Enable Channel0 SRAML      */
    EIMDRV_ERRIN_ENABLE_CH1    = 0x01U, /*!< Error In Enable Channel1 SRAMU      */
    EIMDRV_ERRIN_ENABLE_CH2    = 0x02U, /*!< Error In Enable Channel2 CACHE WAY0 */
    EIMDRV_ERRIN_ENABLE_CH3    = 0x03U, /*!< Error In Enable Channel3 CACHE WAY1 */
    EIMDRV_ERRIN_TOTAL_CHN_NUM = 0x04U  /*!< Error In Total Num                  */
} EimDrv_ChnSelType;

/*! \brief Definition EIM Sram Access Type
 */
typedef enum
{
    EIMDRV_ERRIN_SRAML          = 0x00U, /*!< Error In Access Type of SRAML */
    EIMDRV_ERRIN_SRAMU          = 0x01U, /*!< Error In Access Type of SRAMU */
    EIMDRV_ERRIN_SRAM_TOTAL_NUM = 0x02U
} EimDrv_SramAccType;

/*! \brief Definition EIM Cache Access Type
 */
typedef enum
{
    EIMDRV_ERRIN_CACHE_WAY0      = 0x00U, /*!< Error In Access Type of CACHE_WAY0 */
    EIMDRV_ERRIN_CACHE_WAY1      = 0x01U, /*!< Error In Access Type of CACHE_WAY1 */
    EIMDRV_ERRIN_CACHE_TOTAL_NUM = 0x02U
} EimDrv_CacheAccType;

/* Forward declaration of related register */
struct _EimRegType_;

/*! \brief The definition of EIM driver class
 */
typedef struct _EimDrvType_
{
    struct _EimRegType_ *reg; /*!< pointer to EIM register */
} EimDrvType;

/*! \brief struct of EIM Sram channel control
 */
typedef struct _EimDrv_ErrInSramType_
{
    uint8_t  chk;  /*!< Access Sram Error in ECC     */
    uint32_t data; /*!< Access Sram Error in data    */
    uint32_t addr; /*!< Access Sram Error in address */
} EimDrv_SramType;

/*! \brief struct of EIM Cache channel control
 */
typedef struct _EimDrv_ErrInCacheType_
{
    uint8_t  chk;   /*!< Access Cache Error in ECC   */
    uint32_t data0; /*!< Access Cache Error in data0 */
    uint32_t data1; /*!< Access Cache Error in data1 */
    uint32_t data2; /*!< Access Cache Error in data2 */
} EimDrv_CacheType;

/*! \brief struct of EIM Config
 */
typedef struct _EimDrv_ChnCfgType_
{
    bool             globalEnable;                              /*!< Eim global enable status      */
    bool             chnNumStatus[EIMDRV_ERRIN_TOTAL_CHN_NUM];  /*!< Eim channel num enable status */
    EimDrv_SramType  accSramCfg[EIMDRV_ERRIN_SRAM_TOTAL_NUM];   /*!< Access Sram Error in config   */
    EimDrv_CacheType accCacheCfg[EIMDRV_ERRIN_CACHE_TOTAL_NUM]; /*!< Access Cache Error in config  */
} EimDrv_ChnCfgType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Initializes the EIM driver module
 *
 * This function initializes EIM driver by setting the register
 * instances to it.
 *
 * \param[in] obj : pointer to EIM driver instance
 * \param[in] eimReg : pointer to EIM register instance
 */
extern void EimDrv_Init(EimDrvType *obj, struct _EimRegType_ *eimReg);

/*! \brief Get EIM Default config paramter
 *
 * This function get EIM config paramter.
 *
 * \param[in] userConfig : pointer to default parameter
 */
extern void EimDrv_GetDefaultConfig(EimDrv_ChnCfgType *userConfig);

/*! \brief Get EIM Global Channel Enable Status
 *
 * This function get global Channel enable status.
 *
 * \param[in] obj : pointer to EIM driver instance
 */
extern bool EimDrv_GetChnGlobalEnable(EimDrvType *obj);

/*! \brief Set EIM Global Channel Enable Status
 *
 * This function set global Channel enable status.
 *
 * \param[in] obj : pointer to EIM driver instance
 * \param[in] enable :
 *             - true  : enable global channel
 *             - false : disable global channel
 *
 */
extern void EimDrv_EnableGlobalChn(EimDrvType *obj, bool enable);

/*! \brief Get EIM Channel Number Enable Status
 *
 * This function get global Channel number enable status.
 *
 * \param[in] obj : pointer to EIM driver instance
 * \param[in] chnNum : destination to the channel get status
 */
extern bool EimDrv_GetChnNumEnable(EimDrvType *obj, EimDrv_ChnSelType chnNum);

/*! \brief Set EIM Channel Number Enable Status
 *
 * This function set global Channel number enable status.
 *
 * \param[in] obj : pointer to EIM driver instance
 * \param[in] chnNum : select the channel set status
 * \param[in] enable :
 *             - true  : enable selected channel
 *             - false : disable selected channel
 */
extern void EimDrv_EnableChannel(EimDrvType *obj, EimDrv_ChnSelType chnNum, bool enable);

/*! \brief Get Access Sram EIM Config
 *
 * This function get access sram EIM config parameter
 *
 * \param[in] obj : pointer to EIM driver instance
 * \param[in] sramType : pointer to get access sram paramter chk/data/addr
 * \param[in] accType : access sram type
 */
extern void EimDrv_GetSramErrInStatus(EimDrvType *obj, EimDrv_SramType *sramType, EimDrv_SramAccType accType);

/*! \brief Set Access Sram EIM Config
 *
 * This function set access sram EIM config parameter
 *
 * \param[in] obj : pointer to EIM driver instance
 * \param[in] sramType : pointer to set access sram paramter chk/data/addr
 * \param[in] accType : access sram type
 */
extern void EimDrv_SetSramErrInStatus(EimDrvType *obj, EimDrv_SramType *sramType, EimDrv_SramAccType accType);

/*! \brief Get Access Cache EIM Config
 *
 * This function get access cache EIM config parameter
 *
 * \param[in] obj : pointer to EIM driver instance
 * \param[in] cacheType : pointer to get access cache paramter chk/data0/data1/data2
 * \param[in] accType : access cache type
 */
extern void EimDrv_GetCacheErrInStatus(EimDrvType *obj, EimDrv_CacheType *cacheType, EimDrv_CacheAccType accType);

/*! \brief Set Access Cache EIM Config
 *
 * This function set access cache EIM config parameter
 *
 * \param[in] obj : pointer to EIM driver instance
 * \param[in] cacheType : pointer to set access cache paramter chk/data0/data1/data2
 * \param[in] accType : access cache type
 */
extern void EimDrv_SetCacheErrInStatus(EimDrvType *obj, EimDrv_CacheType *cacheType, EimDrv_CacheAccType accType);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _EIM_DRV_H_ */
