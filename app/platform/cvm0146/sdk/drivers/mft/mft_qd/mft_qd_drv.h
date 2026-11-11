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

#ifndef _MFT_QD_DRV_H_
#define _MFT_QD_DRV_H_

/*! \brief Contains public interface to various functions related
 *         to the quadrature decode mode driver of MFT
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "../mft_drv.h"

/*! \addtogroup mft_qd_drv
 *  \ingroup mft_drv
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

/*! \brief MFT quadrature decode modes, phase encode or count and direction mode
 */
typedef enum
{
    MFTQDDRV_PHASE_ENCODE  = 0x00U, /*!< Phase encoding mode                 */
    MFTQDDRV_COUNT_AND_DIR = 0x01U  /*!< Counter and direction encoding mode */
} MftQdDrv_ModeType;

/*! \brief MFT quadrature phase polarities, normal or inverted polarity
 */
typedef enum
{
    MFTQDDRV_PHASE_NORMAL = 0x00U, /*!< Phase input signal is not inverted before identifying
                                    *   the rising and falling edges of this signal */
    MFTQDDRV_PHASE_INVERT = 0x01U  /*!< Phase input signal is inverted before identifying
                                    *   the rising and falling edges of this signal */
} MftQdDrv_PhasePolarityType;

typedef enum
{
    MFTQDDRV_PHASEZ_CLEAR_NONE  = 0x00U, /*!< Phase Z input does not reset the counter */
    MFTQDDRV_PHASEZ_CLEAR_EVENT = 0x01U, /*!< Every effective edge of phase Z input resets the counter
                                          *    (Reseting does not happen immediately, but after the first or
                                          *    recorded phase A or phase B input edge) */
    MFTQDDRV_PHASEZ_CLEAR_FIRST = 0x02U, /*!< phase Z input resets the counter only once
                                          *   (Reseting does not happen immediately, but after the first
                                          *   phase A or phase B input edge) */
    MFTQDDRV_PHASEZ_CLEAR_EDGE = 0x03U   /*!< Clear immediately when the effective edge of Phase Z signal comes */
}MftQdDrv_PhaseZClearType;

/*! \brief MFT quadrature decoder channel parameters
 */
typedef struct
{
    bool                       phaseInputFilter; /*!< false: disable phase filter, true: enable phase filter */
    uint8_t                    phaseFilterVal;   /*!< Filter value (if input filter is enabled)*/
    MftQdDrv_PhasePolarityType phasePolarity;    /*!< Phase polarity */
} MftQdDrv_PhaseParamsType;

/*! \brief MFT driver Input capture parameters for each channel
 */
typedef struct _MftQdDrv_ConfigType_
{
    MftQdDrv_ModeType        mode;         /*!< Mode of quadrature decoder */
    uint16_t                 initialVal;   /*!< Initial counter value */
    uint16_t                 maxVal;       /*!< Maximum counter value */
    MftQdDrv_PhaseZClearType phaseZClearMode; /*!<Configuration for the phase z clear mode */
    MftQdDrv_PhaseParamsType phaseAConfig; /*!< Configuration for the input phase a */
    MftQdDrv_PhaseParamsType phaseBConfig; /*!< Configuration for the input phase b */
    MftQdDrv_PhaseParamsType phaseZConfig; /*!< Configuration for the input phase z */
} MftQdDrv_ConfigType;

/*! \brief MFT quadrature state(counter value and flags)
 */
typedef struct
{
    uint16_t counter;           /*!< Counter value */
    bool     overflowFlag;      /*!< True if overflow occurred, False if overflow doesn't occurred */
    bool     overflowDirection; /*!< False if overflow occurred at minimum value, True if overflow occurred at maximum value */
    bool     counterDirection;  /*!< False MFT counter is increasing, True MFT counter is decreasing */
} MftQdDrv_StateType;

/*! \brief The definition of MFT capture driver prototype
 * \details Derived from MFT driver
 */
typedef struct _MftQdDrvType_
{
    MftDrvType *base;      /*!< base class is MFT driver */
    bool        isStarted; /*!< Is quadrature decoder started */
} MftQdDrvType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Initializes the MFT quadrature decode mode
 *
 * This function initializes MFT quadrature decode driver by setting the MFT driver
 * instance to it.
 *
 * \param[in] obj : pointer to MFT quadrature decode mode driver instance
 * \param[in] base : pointer to MFT driver instance
 */
extern void MftQdDrv_Init(MftQdDrvType *obj, MftDrvType *base);

/*! \brief Get default configures the MFT quadrature decode mode for configuration structure
 *
 * This function gets default configures the MFT quadrature decode mode for user configuration structure
 *
 * \note This function is a "static" function regardless of instances
 *
 * \param[out] userConfig : pointer to configuration structure
 */
extern void MftQdDrv_GetDefaultConfig(MftQdDrv_ConfigType *userConfig);

/*! \brief Configures the quadrature mode and starts measurement
 *
 * This function configures the quadrature mode and starts measurement
 *
 * \param[in] obj : pointer to MFT quadrature decode mode driver instance
 * \param[in] userConfig : pointer to configuration structure
 */
extern void MftQdDrv_ConfigAndStart(MftQdDrvType *obj, const MftQdDrv_ConfigType *userConfig);

/*! \brief De-activates the quadrature decode mode.
 *
 * This function de-activates the quadrature decode mode.
 *
 * \param[in] obj : pointer to MFT quadrature decode mode driver instance
 */
extern void MftQdDrv_QuadDecodeStop(MftQdDrvType *obj);

/*! \brief Get the current quadrature decoder state
 *
 * This function get the current quadrature decoder state (counter value, overflow flag and
 * overflow direction)
 *
 * \param[in] obj : pointer to MFT quadrature decode mode driver instance
 * \param[out] state : pointer to the current state of quadrature decoder
 */
extern void MftQdDrv_GetState(MftQdDrvType *obj, MftQdDrv_StateType *state);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _MFT_QD_DRV_H_ */
