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

#ifndef _CLOCK_DRV_H_
#define _CLOCK_DRV_H_

/*! \brief Contains public interface to various functions related
 *         to the driver of Clock
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/*! \addtogroup clock_drv
 *  @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * the defines
 ******************************************************************************/

/* TCLK clock number */
#define TCLK_INPUTS_NUM (3U)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief Definition of Clock names.
 */
typedef enum
{
    /* Source clocks */
    CLOCKDRV_SOSC = 0,  /* system crystal oscillator clock*/
    CLOCKDRV_SIRC,      /* slow internal reference clock */
    CLOCKDRV_FIRC,      /* fast internal reference clock */
    CLOCKDRV_PLL,       /* PLL clock */
    CLOCKDRV_SOSC_DIV1, /* SOSC_DIV1 clock */
    CLOCKDRV_SOSC_DIV2, /* SOSC_DIV2 clock */
    CLOCKDRV_SIRC_DIV1, /* SIRC_DIV1 clock */
    CLOCKDRV_SIRC_DIV2, /* SIRC_DIV2 clock */
    CLOCKDRV_FIRC_DIV1, /* FIRC_DIV1 clock */
    CLOCKDRV_FIRC_DIV2, /* FIRC_DIV2 clock */
    CLOCKDRV_PLL_DIV1,  /* PLL_DIV1 clock */
    CLOCKDRV_PLL_DIV2,  /* PLL_DIV2 clock */
    CLOCKDRV_SYS,       /* system clock */
    CLOCKDRV_CORE,      /* core clock */
    CLOCKDRV_APB,       /* bus clock */
    CLOCKDRV_FLS,       /* flash clock */
    CLOCKDRV_TRACE,     /* trace clock */
    CLOCKDRV_CLKOUT,    /* CLKOUT clock */
    CLOCKDRV_RTC_PADIN, /* RTC pad input clock */
    CLOCKDRV_LPO_1K,    /* LPO 1KHz clock */
    CLOCKDRV_LPO_32K,   /* LPO 32KHz clock */
    CLOCKDRV_LPO_128K,  /* LPO 128KHz clock */
    /* Always-on clocks */
    CLOCKDRV_RTC,       /* RTC source clock, it's also used for other modules */
    CLOCKDRV_EXT_FLT,   /* External Reset pin digital Filter clock */
    CLOCKDRV_LPIT,      /* LPIT clock */
    CLOCKDRV_LPTMR,     /* LPTMR clock */
    CLOCKDRV_RTC_CNT,   /* RTC module clock for counter */
    CLOCKDRV_PORTA_FLT, /* PORTA digital filter clock */
    CLOCKDRV_PORTB_FLT, /* PORTB digital filter clock */
    CLOCKDRV_PORTC_FLT, /* PORTC digital filter clock */
    CLOCKDRV_PORTD_FLT, /* PORTD digital filter clock */
    CLOCKDRV_PORTE_FLT, /* PORTE digital filter clock */
    CLOCKDRV_PORTA,     /* PORTA clock */
    CLOCKDRV_PORTB,     /* PORTB clock */
    CLOCKDRV_PORTC,     /* PORTC clock */
    CLOCKDRV_PORTD,     /* PORTD clock */
    CLOCKDRV_PORTE,     /* PORTE clock */
    CLOCKDRV_CMP0,      /* CMP clock */
    /* Peripheral clocks */
    CLOCKDRV_DMA,      /* DMA clock */
    CLOCKDRV_EIM,      /* EIM clock */
    CLOCKDRV_ERM,      /* ERM clock */
    CLOCKDRV_MPU,      /* MPU clock */
    CLOCKDRV_CRC,      /* CRC clock */
    CLOCKDRV_CSE,      /* CSE clock */
    CLOCKDRV_MFT0,     /* MFT0 input clock, please note this is not MFT functional clock */
    CLOCKDRV_MFT1,     /* MFT1 input clock, please note this is not MFT functional clock */
    CLOCKDRV_MFT2,     /* MFT2 input clock, please note this is not MFT functional clock */
    CLOCKDRV_MFT3,     /* MFT3 input clock, please note this is not MFT functional clock */
    CLOCKDRV_MFT4,     /* MFT4 input clock, please note this is not MFT functional clock */
    CLOCKDRV_MFT5,     /* MFT5 input clock, please note this is not MFT functional clock */
    CLOCKDRV_MSCM,     /* MSCM clock */
    CLOCKDRV_DMA_MUX,  /* DMA_MUX clock */
    CLOCKDRV_PDB0,     /* PDB0 clock */
    CLOCKDRV_PDB1,     /* PDB1 clock */
    CLOCKDRV_PWMLITE0, /* PWM_LITE0 clock */
    CLOCKDRV_PWMLITE1, /* PWM_LITE1 clock */
    CLOCKDRV_PWMLITE2, /* PWM_LITE2 clock */
    CLOCKDRV_PWMLITE3, /* PWM_LITE3 clock */
    CLOCKDRV_PWMLITE4, /* PWM_LITE4 clock */
    CLOCKDRV_PRNG,     /* PRNG clock */
    CLOCKDRV_CMUS,     /* CMUS clock */
    CLOCKDRV_CMUF,     /* CMUF clock */
    CLOCKDRV_FCCU,     /* FCCU clock */
    CLOCKDRV_CMUP,     /* CMUP clock */
    CLOCKDRV_I2C,      /* I2C clock */
    CLOCKDRV_SPI0,     /* SPI0 clock */
    CLOCKDRV_SPI1,     /* SPI1 clock */
    CLOCKDRV_SPI2,     /* SPI2 clock */
    CLOCKDRV_SPI3,     /* SPI3 clock */
    CLOCKDRV_UART0,    /* UART0 clock */
    CLOCKDRV_UART1,    /* UART1 clock */
    CLOCKDRV_UART2,    /* UART2 clock */
    CLOCKDRV_UART3,    /* UART3 clock */
    CLOCKDRV_I2SM,     /* I2S Mater clock */
    CLOCKDRV_I2SS,     /* I2S Slave clock */
    CLOCKDRV_ADC0,     /* ADC0 clock */
    CLOCKDRV_ADC1,     /* ADC1 clock */
    CLOCKDRV_TCLK0,    /* TCLK0 clock */
    CLOCKDRV_TCLK1,    /* TCLK1 clock */
    CLOCKDRV_TCLK2,    /* TCLK2 clock */
    CLOCKDRV_EXT_MFT0, /* EXT_MFT0 clock */
    CLOCKDRV_EXT_MFT1, /* EXT_MFT1 clock */
    CLOCKDRV_EXT_MFT2, /* EXT_MFT2 clock */
    CLOCKDRV_EXT_MFT3, /* EXT_MFT3 clock */
    CLOCKDRV_EXT_MFT4, /* EXT_MFT4 clock */
    CLOCKDRV_EXT_MFT5, /* EXT_MFT5 clock */
    CLOCKDRV_EWM,      /* EWM clock */

    CLOCKDRV_CLOCK_NUM
} ClockDrv_NamesType;

/*! \brief module clock configuration.
 */
typedef struct _ClockDrv_ModuleClkConfigType_
{
    bool               gating; /*!< Clock gating. */
    ClockDrv_NamesType source; /*!< Clock source input (some modules don't have protocol clock) */
    uint16_t           mult;   /*!< Multiplier (some modules don't have fractional) */
    uint16_t           div;    /*!< Divider (some modules don't have divider) */

    /* Only PLL clock has following configures */
    struct
    {
        uint32_t fblSel;  /*!< feedback clock divider pre-scaler */
        uint32_t preDiv;  /*!< pre-divider */
        uint32_t postDiv; /*!< post-divider */
    } pllConfig;          /*!< PLL related config */
} ClockDrv_ModuleClkConfigType;

/*! \brief Initial parameters
 */
typedef struct _ClockDrv_InitParamsType_
{
    uint32_t fircFreq;                  /*!< FIRC frequency */
    uint32_t sircFreq;                  /*!< SIRC frequency */
    uint32_t xtalClkFreq;               /*!< XTAL clock frequency. */
    uint32_t rtcClkInFreq;              /*!< RTC_CLKIN clock frequency. */
    uint32_t tclkFreq[TCLK_INPUTS_NUM]; /*!< TCLKx clocks    */
} ClockDrv_InitParamsType;

/* Forward declaration of related register */
struct _AcgRegType_;
struct _ApcRegType_;
struct _ScgRegType_;
struct _PccRegType_;

/*! \brief The definition of LPIT driver class
 */
typedef struct _ClockDrvType_
{
    struct _AcgRegType_ *acgReg;                    /*!< pointer to RCSM register */
    struct _ApcRegType_ *apcReg;                    /*!< pointer to RCSM register */
    struct _ScgRegType_ *scgReg;                    /*!< pointer to SCG register */
    struct _PccRegType_ *pccReg;                    /*!< pointer to PCC register */
    uint32_t             fircFreq;                  /*!< FIRC frequency */
    uint32_t             sircFreq;                  /*!< SIRC frequency */
    uint32_t             xtalClkFreq;               /*!< XTAL clock frequency */
    uint32_t             rtcClkInFreq;              /*!< RTC_CLKIN clock frequency */
    uint32_t             tclkFreq[TCLK_INPUTS_NUM]; /*!< TCLKx clocks */
} ClockDrvType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Initializes the Clock driver module
 *
 * This function initializes Clock driver by setting the register
 * instances to it.
 *
 * \param[in] obj : pointer to Clock driver instance
 * \param[in] rcsmReg : pointer to RCSM register instance
 * \param[in] scgReg : pointer to SCG register instance
 * \param[in] pccReg : pointer to PCC register instance
 * \param[in] initParams : pointer to clock initialization parameters
 */
extern void ClockDrv_Init(ClockDrvType                  *obj,
                          struct _AcgRegType_           *acgReg,
                          struct _ApcRegType_           *apcReg,
                          struct _ScgRegType_           *scgReg,
                          struct _PccRegType_           *pccReg,
                          const ClockDrv_InitParamsType *initParams);

/*! \brief Gets the clock frequency for a specific clock name.
 *
 * This function checks the current clock configurations and then calculates
 * the clock frequency for a specific clock name defined in ClockDrv_NamesType.
 * Clock modules must be properly configured before using this function.
 * If it cannot find the clock name or the clock is not enabled or
 * it's not configured properly, it returns false.
 *
 * \note If return false, don't trust the value of out parameter "frequency"
 *       even if it's changed.
 *
 * \param[in] obj : pointer to Clock driver instance
 * \param[in] clockName : Clock names defined
 * \param[out] frequency : clock frequency value in Hertz
 * \return The result of the operation
 *         - false : Failed to get the frequency
 *         - true : Success
 */
extern bool ClockDrv_GetFreq(const ClockDrvType *obj, ClockDrv_NamesType clockName, uint32_t *frequency);

/*! \brief Configures module clock
 *
 * This function configures a module clock according to the configuration.
 *
 * \note If the target clock do not have mul or div, the corresponding configuration in
 *       moduleClkConfig will be ignored.
 *
 * \param[in] obj : pointer to Clock driver instance
 * \param[in] clockName : Clock name of the configured module clock
 * \param[in] moduleClkConfig : Pointer to the configuration structure.
 * \return The result of the operation
 *         - false : configure failed
 *         - true : success
 */
extern bool ClockDrv_ConfigureClock(ClockDrvType *obj, ClockDrv_NamesType clockName, const ClockDrv_ModuleClkConfigType *moduleClkConfig);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*! @}*/

#endif /* _CLOCK_DRV_H_ */
