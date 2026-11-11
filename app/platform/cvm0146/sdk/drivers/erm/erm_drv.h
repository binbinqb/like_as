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

#ifndef _ERM_DRV_H_
#define _ERM_DRV_H_

/*! \brief Contains public interface to various functions related
 *         to the driver of ERM
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/*! \addtogroup erm_drv
 *  @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * the defines
 ******************************************************************************/

/* ERM error clear  */
#define ERMDRV_RECOVER_ERRNUM_CLR (0)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief Definition ERM channel number
 */
typedef enum
{
    ERMDRV_CH0_RECOVER_IRQ    = 0U, /*!< ERM channel0 SRAML single-bit recover Irq enable           */
    ERMDRV_CH0_NONRECOVER_IRQ = 1U, /*!< ERM channel0 SRAML multi-bits non-recover Irq enable       */
    ERMDRV_CH1_RECOVER_IRQ    = 2U, /*!< ERM channel1 SRAMU single-bit recover Irq enable           */
    ERMDRV_CH1_NONRECOVER_IRQ = 3U, /*!< ERM channel1 SRAMU multi-bits non-recover Irq enabl        */
    ERMDRV_CH2_RECOVER_IRQ    = 4U, /*!< ERM channel2 FTFC  single-bit recover Irq enable           */
    ERMDRV_CH2_NONRECOVER_IRQ = 5U, /*!< ERM channel2 FTFC  multi-bits non-recover Irq enabl        */
    ERMDRV_CH3_RECOVER_IRQ    = 6U, /*!< ERM channel3 FLASH AXBS single-bit recover Irq enable      */
    ERMDRV_CH3_NONRECOVER_IRQ = 7U, /*!< ERM channel3 FLASH AXBS multi-bits non-recover Irq enabl   */
    ERMDRV_CH4_RECOVER_IRQ    = 8U, /*!< ERM channel4 CACHE single-bit recover Irq enable           */
    ERMDRV_CH4_NONRECOVER_IRQ = 9U, /*!< ERM channel4 CACHE multi-bits non-recover Irq enabl        */
    ERMDRV_CH_TOTAL_NUM       = 10U /*!< ERM channel total num                                      */
} ErmDrv_ChnNumType;

/*! \brief Definition ERM channel number
 */
typedef enum
{
    ERMDRV_CH0               = 0U, /*!< ERM channel0          */
    ERMDRV_CH1               = 1U, /*!< ERM channel1          */
    ERMDRV_CH2               = 2U, /*!< ERM channel2          */
    ERMDRV_CH3               = 3U, /*!< ERM channel3          */
    ERMDRV_CH4               = 4U, /*!< ERM channel4          */
    ERMDRV_CH_CTRL_TOTAL_NUM = 5U  /*!< ERM channel total num */
} ErmDrv_CtrlChnNumType;

/* Forward declaration of related register */
struct _ErmRegType_;

/*! \brief The definition of ERM driver class
 */
typedef struct _ErmDrvType_
{
    struct _ErmRegType_ *reg; /*!< pointer to ERM register */
} ErmDrvType;

/*! \brief ERM channel status config
 */
typedef struct _ErmDrv_ChnNumInfoType_
{
    uint32_t errAddr;       /*!< error report address  */
    uint32_t errPos;        /*!< error report position */
    uint32_t errRecoverNum; /*!< error report recover  */
} ErmDrv_ChnNumInfoType;

/*! \brief channel status and channel num error info
 */
typedef struct _ErmDrv_ChnErrConfigType_
{
    bool                  chnEvent[ERMDRV_CH_TOTAL_NUM];       /*!< channel correction event status get */
    bool                  chnIrq[ERMDRV_CH_TOTAL_NUM];         /*!< channel interrupt notification set  */
    ErmDrv_ChnNumInfoType chnStatus[ERMDRV_CH_CTRL_TOTAL_NUM]; /*!< channel status info                 */
} ErmDrv_ChnErrConfigType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Initializes the ERM driver module
 *
 * This function initializes ERM driver by setting the register
 * instances to it.
 *
 * \param[in] obj : pointer to ERM driver instance
 * \param[in] ermReg : pointer to ERM register instance
 */
extern void ErmDrv_Init(ErmDrvType *obj, struct _ErmRegType_ *ermReg);

/*! \brief Get ERM Default Config Parameter
 *
 * This function initializes ERM config parameter
 *
 * \param[in] userConfig : pointer to get ERM default config parameter
 */
extern void ErmDrv_GetDefaultConfig(ErmDrv_ChnErrConfigType *userConfig);

/*! \brief Set ERM Channel Error Irq Enable
 *
 * This function set channel error interrupt enable
 *
 * \param[in] obj : pointer to ERM driver instance
 * \param[in] chnNum : select config channel
 * \param[in] enable :
 *             - true  : enable select channel
 *             - false  : disable select channel
 */
extern void ErmDrv_SetChnErrIrqEnable(ErmDrvType *obj, ErmDrv_ChnNumType chnNum, bool enable);

/*! \brief Get ERM Channel Error Irq Enable
 *
 * This function get channel error interrupt enable
 *
 * \param[in] obj : pointer to ERM driver instance
 * \param[in] chnNum : select config channel
 *
 * \return The result of configuring channel
 *             - true  : enable select channel
 *             - false  : disable select channel
 */
extern bool ErmDrv_GetChnErrIrqEnable(ErmDrvType *obj, ErmDrv_ChnNumType chnNum);

/*! \brief Get ERM Channel Error Status
 *
 * This function get channel error status
 *
 * \param[in] obj : pointer to ERM driver instance
 * \param[in] chnNum : select config channel
 *
 * \return The result of configuring channel
 *             - true  : select channel error happened
 *             - false  : select channel none error
 */
extern bool ErmDrv_GetChnErrInfoStatus(ErmDrvType *obj, ErmDrv_ChnNumType chnNum);

/*! \brief Clear ERM Channel Error Status
 *
 * This function clear channel error status
 *
 * \param[in] obj : pointer to ERM driver instance
 * \param[in] chnNum : clear select config channel
 *
 * \return none
 */
extern void ErmDrv_ClrChnErrInfoStatus(ErmDrvType *obj, ErmDrv_ChnNumType chnNum);

/*! \brief Get ERM Channel Config Parameter
 *
 * This function get channel error config parameter
 *
 * \param[in] obj : pointer to ERM driver instance
 * \param[in] chnNumInfo : pointer to current channel config info
 * \param[in] chnNum : select config channel
 */
extern void ErmDrv_GetChnNumCfg(ErmDrvType *obj, ErmDrv_ChnNumInfoType *chnNumInfo, ErmDrv_CtrlChnNumType ctrlChnNum);

/*! \brief Clear ERM Channel Config Parameter
 *
 * This function clear channel error config parameter
 *
 * \param[in] obj : pointer to ERM driver instance
 * \param[in] chnNumInfo : pointer to current channel config info
 * \param[in] chnNum : select config channel
 */
extern void ErmDrv_ClrChnNumCfg(ErmDrvType *obj, ErmDrv_CtrlChnNumType ctrlChnNum);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _ERM_DRV_H_ */
