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

#ifndef _PRNG_DRV_H_
#define _PRNG_DRV_H_

/*! \brief Contains public interface to various functions related
 *         to the PRNG (Pseudo Random Number Generator) module
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * the defines
 ******************************************************************************/

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief type random command mode
 */
typedef enum
{
    RANDCMDMODE_NOP   = 0x0, /*!< NOP command */
    RANDCMDMODE_RAND  = 0x1, /*!< random number generation mode */
    RANDCMDMODE_NONCE = 0x3, /*!< NONCE reseed mode */
} PrngDrv_RandCmdModeType;

struct _PrngRegType_;

/*! \brief The definition of PRNG driver class
 */
typedef struct _PrngDrvType_
{
    struct _PrngRegType_ *reg;
} PrngDrvType;

/*! \brief type for Prng configure
 */
typedef struct _PrngCfgType_
{
    PrngDrv_RandCmdModeType cmd;           /*!< command mode */
    bool                    randRdyIntEna; /*!< random ready interrupt enable */
    uint32_t                seed[8];
} PrngCfgType;

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Initializes the Prng driver module
 *
 * This function initializes Prng driver by setting the register
 * instance to it.
 *
 * \param[in] obj : pointer to Prng driver instance
 * \param[in] reg : pointer to Prng register instance
 */
extern void PrngDrv_Init(PrngDrvType *obj, struct _PrngRegType_ *reg);

/*! \brief Run random operation
 *
 * This function run the random operation based on the configure operation parameters
 *
 * \param[in] obj : pointer to Prng driver instance
 * \prarm[in] cfg : pointer to Prng operation configuraion
 */
extern void PrngDrv_Run(PrngDrvType *obj, PrngCfgType *cfg);

#endif
