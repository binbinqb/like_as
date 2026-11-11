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

#ifndef _FTFC_REG_H_
#define _FTFC_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the FTFC Registers
 */

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * the defines
 ******************************************************************************/

/* FSTAT Bit Fields */
#define FTFC_FSTAT_MGSTAT0_MASK     (0x1u)        /*!<FTFC FSTAT: MGSTAT0 Mask */
#define FTFC_FSTAT_MGSTAT0_SHIFT    (0)           /*!<FTFC FSTAT: MGSTAT0 Position */
#define FTFC_FSTAT_MGSTAT0_WIDTH    (1)           /*!<FTFC FSTAT: MGSTAT0 width */
#define FTFC_FSTAT_RSPERR_MASK      (0x2u)        /*!<FTFC FSTAT: RSPERR Mask */
#define FTFC_FSTAT_RSPERR_SHIFT     (1)           /*!<FTFC FSTAT: RSPERR Position */
#define FTFC_FSTAT_RSPERR_WIDTH     (1)           /*!<FTFC FSTAT: RSPERR width */
#define FTFC_FSTAT_PVIOL_MASK       (0x10u)       /*!<FTFC FSTAT: PVIOL Mask */
#define FTFC_FSTAT_PVIOL_SHIFT      (4)           /*!<FTFC FSTAT: PVIOL Position */
#define FTFC_FSTAT_PVIOL_WIDTH      (1)           /*!<FTFC FSTAT: PVIOL width */
#define FTFC_FSTAT_ACCERR_MASK      (0x20u)       /*!<FTFC FSTAT: ACCERR Mask */
#define FTFC_FSTAT_ACCERR_SHIFT     (5)           /*!<FTFC FSTAT: ACCERR Position */
#define FTFC_FSTAT_ACCERR_WIDTH     (1)           /*!<FTFC FSTAT: ACCERR width */
#define FTFC_FSTAT_RDCOLERR_MASK    (0x40u)       /*!<FTFC FSTAT: RDCOLERR Mask */
#define FTFC_FSTAT_RDCOLERR_SHIFT   (6)           /*!<FTFC FSTAT: RDCOLERR Position */
#define FTFC_FSTAT_RDCOLERR_WIDTH   (1)           /*!<FTFC FSTAT: RDCOLERR width */
#define FTFC_FSTAT_CCIF_MASK        (0x80u)       /*!<FTFC FSTAT: CCIF Mask */
#define FTFC_FSTAT_CCIF_SHIFT       (7)           /*!<FTFC FSTAT: CCIF Position */
#define FTFC_FSTAT_CCIF_WIDTH       (1)           /*!<FTFC FSTAT: CCIF width */
#define FTFC_FSTAT_ERSA_REQ_MASK    (0x100u)      /*!<FTFC FSTAT: ERSA_REQ Mask */
#define FTFC_FSTAT_ERSA_REQ_SHIFT   (8)           /*!<FTFC FSTAT: ERSA_REQ Position */
#define FTFC_FSTAT_ERSA_REQ_WIDTH   (1)           /*!<FTFC FSTAT: ERSA_REQ width */
#define FTFC_FSTAT_FL_DONE_MASK     (0x200u)      /*!<FTFC FSTAT: FL_DONE Mask */
#define FTFC_FSTAT_FL_DONE_SHIFT    (9)           /*!<FTFC FSTAT: FL_DONE Position */
#define FTFC_FSTAT_FL_DONE_WIDTH    (1)           /*!<FTFC FSTAT: FL_DONE width */
#define FTFC_FSTAT_FL_ERRF_MASK     (0x400u)      /*!<FTFC FSTAT: FL_ERRF Mask */
#define FTFC_FSTAT_FL_ERRF_SHIFT    (10)          /*!<FTFC FSTAT: FL_ERRF Position */
#define FTFC_FSTAT_FL_ERRF_WIDTH    (1)           /*!<FTFC FSTAT: FL_ERRF width */
#define FTFC_FSTAT_EEERDY_MASK       (0x800u)      /*!<FTFC FSTAT:EEERDY Mask */
#define FTFC_FSTAT_EEERDY_SHIFT      (11)          /*!<FTFC FSTAT:EEERDY Position */
#define FTFC_FSTAT_EEERDY_WIDTH      (1)           /*!<FTFC FSTAT:EEERDY width */
#define FTFC_FSTAT_RAMRDY_MASK      (0x1000u)     /*!<FTFC FSTAT: RAMRDY Mask */
#define FTFC_FSTAT_RAMRDY_SHIFT     (12)          /*!<FTFC FSTAT: RAMRDY Position */
#define FTFC_FSTAT_RAMRDY_WIDTH     (1)           /*!<FTFC FSTAT: RAMRDY width */
#define FTFC_FSTAT_EEE_TLOV_MASK    (0x2000u)     /*!<FTFC FSTAT: EEE_TLOV Mask */
#define FTFC_FSTAT_EEE_TLOV_SHIFT   (13)          /*!<FTFC FSTAT: EEE_TLOV Position */
#define FTFC_FSTAT_EEE_TLOV_WIDTH   (1)           /*!<FTFC FSTAT: EEE_TLOV width */
#define FTFC_FSTAT_EEE_FLOV_MASK    (0x4000u)     /*!<FTFC FSTAT: EEE_FLOV Mask */
#define FTFC_FSTAT_EEE_FLOV_SHIFT   (14)          /*!<FTFC FSTAT: EEE_FLOV Position */
#define FTFC_FSTAT_EEE_FLOV_WIDTH   (1)           /*!<FTFC FSTAT: EEE_FLOV width */
#define FTFC_FSTAT_EEE_SPERR_MASK   (0x8000u)     /*!<FTFC FSTAT: EEE_SPERR Mask */
#define FTFC_FSTAT_EEE_SPERR_SHIFT  (15)          /*!<FTFC FSTAT: EEE_SPERR Position */
#define FTFC_FSTAT_EEE_SPERR_WIDTH  (1)           /*!<FTFC FSTAT: EEE_SPERR width */
#define FTFC_FSTAT_CCI_CLR_MASK     (0x10000u)    /*!<FTFC FSTAT: CCI_CLR Mask */
#define FTFC_FSTAT_CCI_CLR_SHIFT    (16)          /*!<FTFC FSTAT: CCI_CLR Position */
#define FTFC_FSTAT_CCI_CLR_WIDTH    (1)           /*!<FTFC FSTAT: CCI_CLR width */
#define FTFC_FSTAT_EEEVLD_MASK      (0x100000u)   /*!<FTFC FSTAT: EEEVLD Mask */
#define FTFC_FSTAT_EEEVLD_SHIFT     (20)          /*!<FTFC FSTAT: EEEVLD Position */
#define FTFC_FSTAT_EEEVLD_WIDTH     (1)           /*!<FTFC FSTAT: EEEVLD width */
#define FTFC_FSTAT_AHB_DEDF_MASK    (0x1000000u)  /*!<FTFC FSTAT: AHB_DEDF Mask */
#define FTFC_FSTAT_AHB_DEDF_SHIFT   (24)          /*!<FTFC FSTAT: AHB_DEDF Position */
#define FTFC_FSTAT_AHB_DEDF_WIDTH   (1)           /*!<FTFC FSTAT: AHB_DEDF width */
#define FTFC_FSTAT_AHB_SECF_MASK    (0x2000000u)  /*!<FTFC FSTAT: AHB_SECF Mask */
#define FTFC_FSTAT_AHB_SECF_SHIFT   (25)          /*!<FTFC FSTAT: AHB_SECF Position */
#define FTFC_FSTAT_AHB_SECF_WIDTH   (1)           /*!<FTFC FSTAT: AHB_SECF width */
#define FTFC_FSTAT_FTFC_DEDF_MASK   (0x4000000u)  /*!<FTFC FSTAT: FTFC_DEDF Mask */
#define FTFC_FSTAT_FTFC_DEDF_SHIFT  (26)          /*!<FTFC FSTAT: FTFC_DEDF Position */
#define FTFC_FSTAT_FTFC_DEDF_WIDTH  (1)           /*!<FTFC FSTAT: FTFC_DEDF width */
#define FTFC_FSTAT_FTFC_SECF_MASK   (0x8000000u)  /*!<FTFC FSTAT: FTFC_SECF Mask */
#define FTFC_FSTAT_FTFC_SECF_SHIFT  (27)          /*!<FTFC FSTAT: FTFC_SECF Position */
#define FTFC_FSTAT_FTFC_SECF_WIDTH  (1)           /*!<FTFC FSTAT: FTFC_SECF width */
#define FTFC_FSTAT_KEY_AL1SF_MASK   (0x10000000u) /*!<FTFC FSTAT: KEY_AL1SF Mask */
#define FTFC_FSTAT_KEY_AL1SF_SHIFT  (28)          /*!<FTFC FSTAT: KEY_AL1SF Position */
#define FTFC_FSTAT_KEY_AL1SF_WIDTH  (1)           /*!<FTFC FSTAT: KEY_AL1SF width */

/* FCNFG Bit Fields */
#define FTFC_FCNFG_RDCOL_IE_MASK    (0x1u)   /*!<FTFC FCNFG: RDCOL_IE Mask */
#define FTFC_FCNFG_RDCOL_IE_SHIFT   (0)      /*!<FTFC FCNFG: RDCOL_IE Position */
#define FTFC_FCNFG_RDCOL_IE_WIDTH   (1)      /*!<FTFC FCNFG: RDCOL_IE width */
#define FTFC_FCNFG_CCIF_IE_MASK     (0x2u)   /*!<FTFC FCNFG: CCIF_IE Mask */
#define FTFC_FCNFG_CCIF_IE_SHIFT    (1)      /*!<FTFC FCNFG: CCIF_IE Position */
#define FTFC_FCNFG_CCIF_IE_WIDTH    (1)      /*!<FTFC FCNFG: CCIF_IE width */
#define FTFC_FCNFG_RSP_ERR_IE_MASK  (0x4u)   /*!<FTFC FCNFG: RSP_ERR_IE Mask */
#define FTFC_FCNFG_RSP_ERR_IE_SHIFT (2)      /*!<FTFC FCNFG: RSP_ERR_IE Position */
#define FTFC_FCNFG_RSP_ERR_IE_WIDTH (1)      /*!<FTFC FCNFG: RSP_ERR_IE width */
#define FTFC_FCNFG_ERS_SUS_MASK     (0x8u)   /*!<FTFC FCNFG: ERS_SUS Mask */
#define FTFC_FCNFG_ERS_SUS_SHIFT    (3)      /*!<FTFC FCNFG: ERS_SUS Position */
#define FTFC_FCNFG_ERS_SUS_WIDTH    (1)      /*!<FTFC FCNFG: ERS_SUS width */
#define FTFC_FCNFG_AUTO_GC_MASK     (0x10u)  /*!<FTFC FCNFG: AUTO_GC Mask */
#define FTFC_FCNFG_AUTO_GC_SHIFT    (4)      /*!<FTFC FCNFG: AUTO_GC Position */
#define FTFC_FCNFG_AUTO_GC_WIDTH    (1)      /*!<FTFC FCNFG: AUTO_GC width */
#define FTFC_FCNFG_BUSRD_T_MASK     (0xF00u) /*!<FTFC FCNFG: BUSRD_T Mask */
#define FTFC_FCNFG_BUSRD_T_SHIFT    (8)      /*!<FTFC FCNFG: BUSRD_T Position */
#define FTFC_FCNFG_BUSRD_T_WIDTH    (4)      /*!<FTFC FCNFG: BUSRD_T width */

/* FSEC Bit Fields */
#define FTFC_FSEC_SECURE_MASK       (0x3u)  /*!<FTFC FSEC: SECURE Mask */
#define FTFC_FSEC_SECURE_SHIFT      (0)     /*!<FTFC FSEC: SECURE Position */
#define FTFC_FSEC_SECURE_WIDTH      (2)     /*!<FTFC FSEC: SECURE width */
#define FTFC_FSEC_MEEN_MASK         (0x30u) /*!<FTFC FSEC: MEEN Mask */
#define FTFC_FSEC_MEEN_SHIFT        (4)     /*!<FTFC FSEC: MEEN Position */
#define FTFC_FSEC_MEEN_WIDTH        (2)     /*!<FTFC FSEC: MEEN width */
#define FTFC_FSEC_KEYEN_MASK        (0xC0u) /*!<FTFC FSEC: KEYEN Mask */
#define FTFC_FSEC_KEYEN_SHIFT       (6)     /*!<FTFC FSEC: KEYEN Position */
#define FTFC_FSEC_KEYEN_WIDTH       (2)     /*!<FTFC FSEC: KEYEN width */

/* PFPRONT0 Bit Fields */
#define FTFC_PFPROT0_PFPROT0_MASK   (0xFFFFFFFFu) /*!<FTFC PFPROT0: PFPROT0 Mask */
#define FTFC_PFPROT0_PFPROT0_SHIFT  (0u)          /*!<FTFC PFPROT0: PFPROT0 Position */
#define FTFC_PFPROT0_PFPROT0_WIDTH  (32u)         /*!<FTFC PFPROT0: PFPROT0 width */

/* PFPRONT0 Bit Fields */
#define FTFC_PFPROT1_PFPROT1_MASK   (0xFFFFFFFFu) /*!<FTFC PFPROT0: PFPROT0 Mask */
#define FTFC_PFPROT1_PFPROT1_SHIFT  (0u)          /*!<FTFC PFPROT0: PFPROT0 Position */
#define FTFC_PFPROT1_PFPROT1_WIDTH  (32u)         /*!<FTFC PFPROT0: PFPROT0 width */

/* DFPRONT Bit Fields */
#define FTFC_DFPROT_DFPROT_MASK     (0xFFFFu) /*!<FTFC DFPROT: DFPROT Mask */
#define FTFC_DFPROT_DFPROT_SHIFT    (0)       /*!<FTFC DFPROT: DFPROT Position */
#define FTFC_DFPROT_DFPROT_WIDTH    (16)      /*!<FTFC DFPROT: DFPROT width */

/* EFPRONT Bit Fields */
#define FTFC_EFPROT_EFPROT_MASK     (0xFFu)    /*!<FTFC EFPROT: EFPROT Mask */
#define FTFC_EFPROT_EFPROT_SHIFT    (0)        /*!<FTFC EFPROT: EFPROT Position */
#define FTFC_EFPROT_EFPROT_WIDTH    (8)        /*!<FTFC EFPROT: EFPROT width */
#define FTFC_EFPROT_SECPROT_MASK    (0x10000u) /*!<FTFC EFPROT: SECPROT Mask */
#define FTFC_EFPROT_SECPROT_SHIFT   (16)       /*!<FTFC EFPROT: SECPROT Position */
#define FTFC_EFPROT_SECPROT_WIDTH   (1)        /*!<FTFC EFPROT: SECPROT width */

/* CSEBK Bit Fields */
#define FTFC_CSEBK_CSEBK_MASK       (0xFFFFFFFFu)
#define FTFC_CSEBK_CSEBK_SHIFT      (0u)
#define FTFC_CSEBK_CSEBK_WIDTH      (32u)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief The definition of FTFC registers
 */
typedef struct _FtfcRegType_
{
    volatile uint32_t       FSTAT;     /*!< flash module status, offset: 0x00 */
    volatile uint32_t       FCNFG;     /*!< flash module configuration, offset: 0x04 */
    const volatile uint32_t FSEC;      /*!< flash module secure setting, offset: 0x08 */
    volatile uint32_t       PFPROT0;   /*!< flash module program flash protection0, offset: 0x0C */
    volatile uint32_t       PFPROT1;   /*!< flash module program flash protection1, offset: 0x10 */
    volatile uint32_t       DFPROT;    /*!< flash module data flash protection, offset: 0x14 */
    volatile uint32_t       EFPROT;    /*!< flash module eee_ram protection, offset: 0x18 */
    volatile uint8_t        FCCOB[16]; /*!< flash common command object 0 - 15, offset: 0x1C */
    volatile uint32_t       CSEKEY;    /*!< flash module cse key, offset: 0x2C */
} FtfcRegType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Sets the flash command complete interrupt clear
 *
 * This function sets the flash command complete interrupt clear.
 * clear the flash command complete interrupter
 *
 * \param[in] obj : pointer to FTFC register instance
 * \param[in] value : the value of flash command complete interrupt clear
 *                    - 0b : invlaid operation
 *                    - 1b : clear the command complete interrupt
 */
__attribute__((always_inline)) static inline void FtfcReg_SetFstatCcifClr(FtfcRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << FTFC_FSTAT_CCI_CLR_SHIFT)) & FTFC_FSTAT_CCI_CLR_MASK);
    obj->FSTAT   = tmp;
}

/*! \brief Gets the flash eee state page error flag
 *
 * This function gets the current flash eee state page error flag.
 * flash eee state page error flag
 *
 * \param[in] obj : pointer to FTFC register instance
 * \return flash eee state page error flag
 *         - 0b : eee state pasges ok
 *         - 1b : eee state pasges error
 */
__attribute__((always_inline)) static inline uint8_t FtfcReg_GetFstatEeeStpgErrF(const FtfcRegType *obj)
{
    return ((obj->FSTAT & FTFC_FSTAT_EEE_SPERR_MASK) >> FTFC_FSTAT_EEE_SPERR_SHIFT);
}

/*! \brief Sets the emulated eeprom full level overflow flag
 *
 * This function sets the emulated eeprom full level overflow flag.
 * emulated eeprom full level overflow flag
 *
 * \param[in] obj : pointer to FTFC register instance
 * \param[in] value : the value of emulated eeprom full level overflow flag
 *                    - 0b : no effect
 *                    - 1b : clear the flag
 */
__attribute__((always_inline)) static inline void FtfcReg_SetFstatEeeFlov(FtfcRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << FTFC_FSTAT_EEE_FLOV_SHIFT)) & FTFC_FSTAT_EEE_FLOV_MASK);
    obj->FSTAT   = tmp;
}

/*! \brief Gets the emulated eeprom full level overflow flag
 *
 * This function gets the current emulated eeprom full level overflow flag.
 * the emulated eeprom full level overflow flag
 *
 * \param[in] obj : pointer to FTFC register instance
 * \return the emulated eeprom full level overflow flag
 *         - 0b : eee write pointer under full level
 *         - 1b : eee write pointer reach/over full level
 */
__attribute__((always_inline)) static inline uint8_t FtfcReg_GetFstatEeeFlov(const FtfcRegType *obj)
{
    return ((obj->FSTAT & FTFC_FSTAT_EEE_FLOV_MASK) >> FTFC_FSTAT_EEE_FLOV_SHIFT);
}

/*! \brief Gets the emulated eeprom threshold level overflow flag
 *
 * This function gets the current emulated eeprom threshold level overflow flag.
 * the emulated eeprom threshold level overflow flag
 *
 * \param[in] obj : pointer to FTFC register instance
 * \return the emulated eeprom threshold level overflow flag
 *         - 0b : eee write pointer under threshold level
 *         - 1b : eee write pointer reach/over threshold level
 */
__attribute__((always_inline)) static inline uint8_t FtfcReg_GetFstatEeeTlov(const FtfcRegType *obj)
{
    return ((obj->FSTAT & FTFC_FSTAT_EEE_TLOV_MASK) >> FTFC_FSTAT_EEE_TLOV_SHIFT);
}

/*! \brief Sets the emulated eeprom threshold level overflow flag
 *
 * This function sets the emulated eeprom threshold level overflow flag.
 * emulated eeprom threshold level overflow flag
 *
 * \param[in] obj : pointer to FTFC register instance
 * \param[in] value : the value of emulated eeprom threshold level overflow flag
 *                    - 0b : no effect
 *                    - 1b : clear the flag
 */
__attribute__((always_inline)) static inline void FtfcReg_SetFstatEeeTlov(FtfcRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << FTFC_FSTAT_EEE_TLOV_SHIFT)) & FTFC_FSTAT_EEE_TLOV_MASK);
    obj->FSTAT   = tmp;
}

/*! \brief Sets the flash eee state page error flag
 *
 * This function sets the flash eee state page error flag.
 * flash eee state page error flag
 *
 * \param[in] obj : pointer to FTFC register instance
 * \param[in] value : the value of flash eee state page error flag
 *                    - 0b : no effect
 *                    - 1b : clear the flag
 */
__attribute__((always_inline)) static inline void FtfcReg_SetFstatStpgErrF(FtfcRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << FTFC_FSTAT_EEE_SPERR_SHIFT)) & FTFC_FSTAT_EEE_SPERR_MASK);
    obj->FSTAT   = tmp;
}

/*! \brief Gets the ram ready flag
 *
 * This function gets the current ram ready flag.
 * ram ready flag
 *
 * \param[in] obj : pointer to FTFC register instance
 * \return ram ready flag
 *         - 0b : flexram is not ready for system ram
 *         - 1b : flexram is ready for system ram
 */
__attribute__((always_inline)) static inline uint8_t FtfcReg_GetFstatRamRdy(const FtfcRegType *obj)
{
    return ((obj->FSTAT & FTFC_FSTAT_RAMRDY_MASK) >> FTFC_FSTAT_RAMRDY_SHIFT);
}

/*! \brief Gets the eee_ram ready flag
 *
 * This function gets the current eee_ram ready flag.
 * eee_ram ready flag
 *
 * \param[in] obj : pointer to FTFC register instance
 * \return emulated eee_ram ready flag
 *         - 0b : flexram is not ready for eee_ram
 *         - 1b :  flexram is ready for eee_ram
 */
__attribute__((always_inline)) static inline uint8_t FtfcReg_GetFstatEeeRamRdy(const FtfcRegType *obj)
{
    return ((obj->FSTAT & FTFC_FSTAT_EEERDY_MASK) >> FTFC_FSTAT_EEERDY_SHIFT);
}

/*! \brief Gets the emulated eeprom valid flag
 *
 * This function gets the emulated eeprom valid flag
 * emulated eeprom valid flag
 *
 * \param[in] obj : pointer to FTFC register instance
 * \return emulated eeprom valid flag
 *         - 0b : emulated eeprom is not valid
 *         - 1b : emulated eeprom is valid
 */
__attribute__((always_inline)) static inline uint8_t FtfcReg_GetFstatEeeVld(const FtfcRegType *obj)
{
    return ((obj->FSTAT & FTFC_FSTAT_EEEVLD_MASK) >> FTFC_FSTAT_EEEVLD_SHIFT);
}

/*! \brief Gets the flash loader error flag
 *
 * This function gets the current flash loader error flag.
 * flash loader error flag
 *
 * \param[in] obj : pointer to FTFC register instance
 * \return flash loader error flag
 *         - 0b : flash loader no error
 *         - 1b : flash loader error
 */
__attribute__((always_inline)) static inline uint8_t FtfcReg_GetFstatFlErrF(const FtfcRegType *obj)
{
    return ((obj->FSTAT & FTFC_FSTAT_FL_ERRF_MASK) >> FTFC_FSTAT_FL_ERRF_SHIFT);
}

/*! \brief Gets the flash loader done flag
 *
 * This function gets the current flash loader done flag.
 * flash loader done flag
 *
 * \param[in] obj : pointer to FTFC register instance
 * \return flash loader done flag
 *         - 0b : flash loader is not done
 *         - 1b : flash loader is done
 */
__attribute__((always_inline)) static inline uint8_t FtfcReg_GetFstatFlDone(const FtfcRegType *obj)
{
    return ((obj->FSTAT & FTFC_FSTAT_FL_DONE_MASK) >> FTFC_FSTAT_FL_DONE_SHIFT);
}

/*! \brief Gets the flash erase sector flag
 *
 * This function gets the current flash erase sector flag.
 * flash erase sector flag
 *
 * \param[in] obj : pointer to FTFC register instance
 * \return flash erase sector flag
 *         - 0b : not erasing sector
 *         - 1b : erasing sector
 */
__attribute__((always_inline)) static inline uint8_t FtfcReg_GetFstatErsSctF(const FtfcRegType *obj)
{
    return ((obj->FSTAT & FTFC_FSTAT_ERSA_REQ_MASK) >> FTFC_FSTAT_ERSA_REQ_SHIFT);
}

/*! \brief Gets the flash command complete flag
 *
 * This function gets the current flash command complete flag.
 * presents whether ftfc command is completed
 *
 * \param[in] obj : pointer to FTFC register instance
 * \return ftfc command complete flag
 *         - 0b : not completed
 *         - 1b : completed
 */
__attribute__((always_inline)) static inline uint8_t FtfcReg_GetFstatCcif(const FtfcRegType *obj)
{
    return ((obj->FSTAT & FTFC_FSTAT_CCIF_MASK) >> FTFC_FSTAT_CCIF_SHIFT);
}

/*! \brief Sets the flash command complete flag
 *
 * This function sets the flash command complete flag.
 * presents whether flash command is completed
 *
 * \param[in] obj : pointer to FTFC register instance
 * \param[in] value : the value of flash command complete flag
 *                    - 0b : no effect
 *                    - 1b : clear the flag
 */
__attribute__((always_inline)) static inline void FtfcReg_SetFstatCcif(FtfcRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << FTFC_FSTAT_CCIF_SHIFT)) & FTFC_FSTAT_CCIF_MASK);
    obj->FSTAT   = tmp;
}

/*! \brief Gets the flash read collide error flag
 *
 * This function gets the current flash read collide error flag.
 * presents whether flash happens read collide
 *
 * \param[in] obj : pointer to FTFC register instance
 * \return flash read collide error flag
 *         - 0b : not collide
 *         - 1b : collided
 */
__attribute__((always_inline)) static inline uint8_t FtfcReg_GetFstatRdColF(const FtfcRegType *obj)
{
    return ((obj->FSTAT & FTFC_FSTAT_RDCOLERR_MASK) >> FTFC_FSTAT_RDCOLERR_SHIFT);
}

/*! \brief Sets the flash read collide error flag
 *
 * This function sets the flash read collide error flag.
 * presents whether flash happens read collide
 *
 * \param[in] obj : pointer to FTFC register instance
 * \param[in] value : the value of flash read collide error flag
 *                    - 0b : no effect
 *                    - 1b : clear the flag
 */
__attribute__((always_inline)) static inline void FtfcReg_SetFstatRdColF(FtfcRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << FTFC_FSTAT_RDCOLERR_SHIFT)) & FTFC_FSTAT_RDCOLERR_MASK);
    obj->FSTAT   = tmp;
}

/*! \brief Gets the flash command configuration error flag
 *
 * This function gets the current flash command configuration error flag.
 * flash command configuration error flag
 *
 * \param[in] obj : pointer to FTFC register instance
 * \return flash command configuration error flag
 *         - 0b : no command configuration error
 *         - 1b : command configuration error has occurred
 */
__attribute__((always_inline)) static inline uint8_t FtfcReg_GetFstatAccErrF(const FtfcRegType *obj)
{
    return ((obj->FSTAT & FTFC_FSTAT_ACCERR_MASK) >> FTFC_FSTAT_ACCERR_SHIFT);
}

/*! \brief Sets the flash command configuration error flag
 *
 * This function sets the flash command configuration error flag.
 * flash command configuration error flag
 *
 * \param[in] obj : pointer to FTFC register instance
 * \param[in] value : the value of flash command configuration error flag
 *                    - 0b : no effect
 *                    - 1b : clear the flag
 */
__attribute__((always_inline)) static inline void FtfcReg_SetFstatAccErrF(FtfcRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << FTFC_FSTAT_ACCERR_SHIFT)) & FTFC_FSTAT_ACCERR_MASK);
    obj->FSTAT   = tmp;
}

/*! \brief Gets the flash protection violation error flag
 *
 * This function gets the current flash protection violation error flag.
 * presents whether flash happens protection violation
 *
 * \param[in] obj : pointer to FTFC register instance
 * \return flash protection violation error flag
 *         - 0b : not violation
 *         - 1b : violation
 */
__attribute__((always_inline)) static inline uint8_t FtfcReg_GetFstatProtViolF(const FtfcRegType *obj)
{
    return ((obj->FSTAT & FTFC_FSTAT_PVIOL_MASK) >> FTFC_FSTAT_PVIOL_SHIFT);
}

/*! \brief Sets the flash protection violation error flag
 *
 * This function sets the flash protection violation error flag.
 * presents whether flash happensprotection violation
 *
 * \param[in] obj : pointer to FTFC register instance
 * \param[in] value : the value of flash protection violation error flag
 *                    - 0b : no effect
 *                    - 1b : clear the flag
 */
__attribute__((always_inline)) static inline void FtfcReg_SetFstatProtViolF(FtfcRegType *obj, uint8_t value)
{
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid
     * side-effects */
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << FTFC_FSTAT_PVIOL_SHIFT)) & FTFC_FSTAT_PVIOL_MASK);
    obj->FSTAT   = tmp;
}

/*! \brief Gets the flash ahb ecc sec error flag
 *
 * This function gets the current flash ahb ecc sec error flag.
 * presents whether flash ahb access happens ecc sec error
 *
 * \param[in] obj : pointer to FTFC register instance
 * \return flash ahb ecc sec error flag
 *         - 0b : not ecc sec error
 *         - 1b : ecc sec error
 */
__attribute__((always_inline)) static inline uint8_t FtfcReg_GetFstatAhbSecF(const FtfcRegType *obj)
{
    return ((obj->FSTAT & FTFC_FSTAT_AHB_SECF_MASK) >> FTFC_FSTAT_AHB_SECF_SHIFT);
}

/*! \brief Sets the flash ahb ecc sec error flag
 *
 * This function sets the flash ahb ecc sec error flag.
 * presents whether flash ahb access happens ecc sec error
 *
 * \param[in] obj : pointer to FTFC register instance
 * \param[in] value : the value of flash  ahb ecc sec error flag
 *                    - 0b : no effect
 *                    - 1b : clear the flag
 */
__attribute__((always_inline)) static inline void FtfcReg_SetFstatAhbSecF(FtfcRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << FTFC_FSTAT_AHB_SECF_SHIFT)) & FTFC_FSTAT_AHB_SECF_MASK);
    obj->FSTAT   = tmp;
}

/*! \brief Gets the flash ftfc ecc sec error flag
 *
 * This function gets the current flash ahb ftfc sec error flag.
 * presents whether flash ftfc access happens ecc sec error
 *
 * \param[in] obj : pointer to FTFC register instance
 * \return flash ftfc ecc sec error flag
 *         - 0b : not ecc sec error
 *         - 1b : ecc sec error
 */
__attribute__((always_inline)) static inline uint8_t FtfcReg_GetFstatFtfcSecF(const FtfcRegType *obj)
{
    return ((obj->FSTAT & FTFC_FSTAT_FTFC_SECF_MASK) >> FTFC_FSTAT_FTFC_SECF_SHIFT);
}

/*! \brief Sets the flash ftfc ecc sec error flag
 *
 * This function sets the flash ftfc ecc sec error flag.
 * presents whether flash ftfc access happens ecc sec error
 *
 * \param[in] obj : pointer to FTFC register instance
 * \param[in] value : the value of flash ftfc ecc sec error flag
 *                    - 0b : no effect
 *                    - 1b : clear the flag
 */
__attribute__((always_inline)) static inline void FtfcReg_SetFstatFtfcSecF(FtfcRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << FTFC_FSTAT_FTFC_SECF_SHIFT)) & FTFC_FSTAT_FTFC_SECF_MASK);
    obj->FSTAT   = tmp;
}

/*! \brief Gets the flash ahb ecc ded error flag
 *
 * This function gets the current flash ahb ecc ded error flag.
 * presents whether flash ahb access happens ecc ded error
 *
 * \param[in] obj : pointer to FTFC register instance
 * \return ahb ecc ded error flag
 *         - 0b : not ecc ded error
 *         - 1b : ecc ded error
 */
__attribute__((always_inline)) static inline uint8_t FtfcReg_GetFstatAhbDedF(const FtfcRegType *obj)
{
    return ((obj->FSTAT & FTFC_FSTAT_AHB_DEDF_MASK) >> FTFC_FSTAT_AHB_DEDF_SHIFT);
}

/*! \brief Sets the flash ahb ecc ded error flag
 *
 * This function sets the flash ahb ecc ded error flag.
 * presents whether flash happens ahb ecc ded error
 *
 * \param[in] obj : pointer to FTFC register instance
 * \param[in] value : the value of flash ahb ecc ded error flag
 *                    - 0b : no effect
 *                    - 1b : clear the flag
 */
__attribute__((always_inline)) static inline void FtfcReg_SetFstatAhbDedF(FtfcRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << FTFC_FSTAT_AHB_DEDF_SHIFT)) & FTFC_FSTAT_AHB_DEDF_MASK);
    obj->FSTAT   = tmp;
}

/*! \brief Gets the flash ftfc ecc ded error flag
 *
 * This function gets the current flash ftfc ecc ded error flag.
 * presents whether flash ftfc access happens ecc ded error
 *
 * \param[in] obj : pointer to FTFC register instance
 * \return ftfc ecc ded error flag
 *         - 0b : not ecc ded error
 *         - 1b : ecc ded error
 */
__attribute__((always_inline)) static inline uint8_t FtfcReg_GetFstatFtfcDedF(const FtfcRegType *obj)
{
    return ((obj->FSTAT & FTFC_FSTAT_FTFC_DEDF_MASK) >> FTFC_FSTAT_FTFC_DEDF_SHIFT);
}

/*! \brief Sets the flash ftfc ecc ded error flag
 *
 * This function sets the flash ftfc ecc ded error flag.
 * presents whether flash happens ftfc ecc ded error
 *
 * \param[in] obj : pointer to FTFC register instance
 * \param[in] value : the value of flash ftfc ecc ded error flag
 *                    - 0b : no effect
 *                    - 1b : clear the flag
 */
__attribute__((always_inline)) static inline void FtfcReg_SetFstatFtfcDedF(FtfcRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << FTFC_FSTAT_FTFC_DEDF_SHIFT)) & FTFC_FSTAT_FTFC_DEDF_MASK);
    obj->FSTAT   = tmp;
}

/*! \brief Gets the cse key all 1s flag
 *
 * This function gets the current the cse key all 1s flag.
 * flash the cse key all 1s flag
 *
 * \param[in] obj : pointer to FTFC register instance
 * \return the cse key all 1s flag
 *         - 0b : not all 1s, the key secotor is programmed
 *         - 1b : all 1s, the key secotor is not programmed
 */
__attribute__((always_inline)) static inline uint8_t FtfcReg_GetFstatKeyAl1sF(const FtfcRegType *obj)
{
    return ((obj->FSTAT & FTFC_FSTAT_KEY_AL1SF_MASK) >> FTFC_FSTAT_KEY_AL1SF_SHIFT);
}

/*! \brief Sets the cse key all 1s flag
 *
 * This function sets the cse key all 1s flag.
 * flash cse key all 1s flag
 *
 * \param[in] obj : pointer to FTFC register instance
 * \param[in] value : the value of the cse key all 1s flag
 *                    - 0b : no effect
 *                    - 1b : clear the flag
 */
__attribute__((always_inline)) static inline void FtfcReg_SetFstatKeyAl1sF(FtfcRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << FTFC_FSTAT_KEY_AL1SF_SHIFT)) & FTFC_FSTAT_KEY_AL1SF_MASK);
    obj->FSTAT   = tmp;
}

/*! \brief Sets the response error flag
 *
 * This function sets the response error flag.
 *
 * \param[in] obj : pointer to FTFC register instance
 * \param[in] value : the value of the response error flag
 *                    - 0b : no effect
 *                    - 1b : clear the flag
 */
__attribute__((always_inline)) static inline void FtfcReg_SetFstatRspErrF(FtfcRegType *obj, uint8_t value)
{
    uint32_t tmp = 0;
    tmp          = (((uint32_t)(((uint32_t)(value)) << FTFC_FSTAT_RSPERR_MASK)) & FTFC_FSTAT_RSPERR_SHIFT);
    obj->FSTAT   = tmp;
}

/*! \brief Gets the flash ahb bus response error flag
 *
 * This function gets the current flash ahb bus response error flag.
 * presents whether flash ahb bus response error occurred
 *
 * \param[in] obj : pointer to FTFC register instance
 * \return flash ahb bus response error flag
 *         - 0b : no response error
 *         - 1b : response error occurred
 */
__attribute__((always_inline)) static inline uint8_t FtfcReg_GetFstatRspErrF(const FtfcRegType *obj)
{
    return ((obj->FSTAT & FTFC_FSTAT_RSPERR_MASK) >> FTFC_FSTAT_RSPERR_SHIFT);
}

/*! \brief Gets the flash command run error flag
 *
 * This function gets the current flash command run error flag.
 * presents whether flash command run error
 *
 * \param[in] obj : pointer to FTFC register instance
 * \return flash command run error flag
 *         - 0b : no run error
 *         - 1b : run error has happened
 */
__attribute__((always_inline)) static inline uint8_t FtfcReg_GetFstatMgStat(const FtfcRegType *obj)
{
    return ((obj->FSTAT & FTFC_FSTAT_MGSTAT0_MASK) >> FTFC_FSTAT_MGSTAT0_SHIFT);
}

/*! \brief Gets the flash ahb bus read access time
 *
 * This function gets the current flash ahb bus read access time.
 * time step: T: 1 AHB clock cycle;
 * suppose : n * T >= 20ns;
 *
 * \param[in] obj : pointer to FTFC register instance
 * \return the flash ahb bus read access time
 *         - 0h : 1T
 *         - 1h : 2T
 *         - 2h : 3T
 *         - 3h : 4T
 *         - 4h : 5T
 *         - 5h : 6T
 *         - 6h : 7T
 *         - 7h : 8T
 *         - 8h : 9T
 *         - 9h : 10T
 *         - Ah : 11T
 *         - Bh : 12T
 *         - Ch : 13T
 *         - Dh : 14T
 *         - Eh : 15T
 *         - Fh : 16T
 */
__attribute__((always_inline)) static inline uint8_t FtfcReg_GetFcnfgBusReadTm(const FtfcRegType *obj)
{
    return ((obj->FCNFG & FTFC_FCNFG_BUSRD_T_MASK) >> FTFC_FCNFG_BUSRD_T_SHIFT);
}

/*! \brief Sets the flash ahb bus read access time
 *
 * This function sets the flash ahb bus read access time.
 * when CCIF=0, can not modify this register;
 * Before AHB clock changed，set this register;
 * time step: T: 1 AHB clock cycle;
 * requirment : n * T >= 20ns;
 *
 * \param[in] obj : pointer to FTFC register instance
 * \param[in] value : the value of flash ahb bus read access time
 *         - 0h : 1T
 *         - 1h : 2T
 *         - 2h : 3T
 *         - 3h : 4T
 *         - 4h : 5T
 *         - 5h : 6T
 *         - 6h : 7T
 *         - 7h : 8T
 *         - 8h : 9T
 *         - 9h : 10T
 *         - Ah : 11T
 *         - Bh : 12T
 *         - Ch : 13T
 *         - Dh : 14T
 *         - Eh : 15T
 *         - Fh : 16T
 */
__attribute__((always_inline)) static inline void FtfcReg_SetFcnfgBusReadTm(FtfcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->FCNFG;

    tmp &= ~FTFC_FCNFG_BUSRD_T_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << FTFC_FCNFG_BUSRD_T_SHIFT)) & FTFC_FCNFG_BUSRD_T_MASK);
    obj->FCNFG = tmp;
}

/*! \brief Gets the erase sector suspend
 *
 * This function gets the current erase sector suspend.
 * suspend flash erase sector operation
 *
 * \param[in] obj : pointer to FTFC register instance
 * \return erase sector suspend
 *         - 0b : not suspend
 *         - 1b : suspend
 */
__attribute__((always_inline)) static inline uint8_t FtfcReg_GetFcnfgErsSus(const FtfcRegType *obj)
{
    return ((obj->FCNFG & FTFC_FCNFG_ERS_SUS_MASK) >> FTFC_FCNFG_ERS_SUS_SHIFT);
}

/*! \brief Sets the erase sector suspend
 *
 * This function sets the erase sector suspend.
 * suspend flash erase sector operation
 *
 * \param[in] obj : pointer to FTFC register instance
 * \param[in] value : the value of erase sector suspend
 *                    - 0b : not suspend
 *                    - 1b : suspend
 */
__attribute__((always_inline)) static inline void FtfcReg_SetFcnfgErsSus(FtfcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->FCNFG;

    tmp &= ~FTFC_FCNFG_ERS_SUS_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << FTFC_FCNFG_ERS_SUS_SHIFT)) & FTFC_FCNFG_ERS_SUS_MASK);
    obj->FCNFG = tmp;
}

/*! \brief Gets the bus error response interrupt enable
 *
 * This function gets the current bus error response interrupt enable.
 * ahb bus access error response interrupt enable
 *
 * \param[in] obj : pointer to FTFC register instance
 * \return bus error response interrupt enable
 *         - 0b : disable interupt
 *         - 1b : enable interrupt
 */
__attribute__((always_inline)) static inline uint8_t FtfcReg_GetFcnfgRspErrIE(const FtfcRegType *obj)
{
    return ((obj->FCNFG & FTFC_FCNFG_RSP_ERR_IE_MASK) >> FTFC_FCNFG_RSP_ERR_IE_SHIFT);
}

/*! \brief Sets the bus error response interrupt enable
 *
 * This function sets the bus error response interrupt enable.
 * ahb bus access error response interrupt enable
 *
 * \param[in] obj : pointer to FTFC register instance
 * \param[in] value : the value of bus error response interrupt enable
 *                    - 0b : disable interupt
 *                    - 1b : enable interrupt
 */
__attribute__((always_inline)) static inline void FtfcReg_SetFcnfgRspErrIE(FtfcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->FCNFG;

    tmp &= ~FTFC_FCNFG_RSP_ERR_IE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << FTFC_FCNFG_RSP_ERR_IE_SHIFT)) & FTFC_FCNFG_RSP_ERR_IE_MASK);
    obj->FCNFG = tmp;
}

/*! \brief Gets the flash command complete interrupt enable
 *
 * This function gets the current flash command complete interrupt enable.
 * flash command complete interrupt enable
 *
 * \param[in] obj : pointer to FTFC register instance
 * \return flash command complete interrupt enable
 *         - 0b : disable interupt
 *         - 1b : enable interrupt
 */
__attribute__((always_inline)) static inline uint8_t FtfcReg_GetFcnfgCcifIE(const FtfcRegType *obj)
{
    return ((obj->FCNFG & FTFC_FCNFG_CCIF_IE_MASK) >> FTFC_FCNFG_CCIF_IE_SHIFT);
}

/*! \brief Sets the flash command complete interrupt enable
 *
 * This function sets the flash command complete interrupt enable.
 * flash command complete interrupt enable
 *
 * \param[in] obj : pointer to FTFC register instance
 * \param[in] value : the value of flash command complete interrupt enable
 *                    - 0b : disable interupt
 *                    - 1b : enable interrupt
 */
__attribute__((always_inline)) static inline void FtfcReg_SetFcnfgCcifIE(FtfcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->FCNFG;

    tmp &= ~FTFC_FCNFG_CCIF_IE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << FTFC_FCNFG_CCIF_IE_SHIFT)) & FTFC_FCNFG_CCIF_IE_MASK);
    obj->FCNFG = tmp;
}

/*! \brief Gets the flash read collide interrupt enable
 *
 * This function gets the current flash read collide interrupt enable.
 * flash command and ahb bus read collide interrupt enable
 *
 * \param[in] obj : pointer to FTFC register instance
 * \return flash read collide interrupt enable
 *         - 0b : disable interupt
 *         - 1b : enable interrupt
 */
__attribute__((always_inline)) static inline uint8_t FtfcReg_GetFcnfgRdColIE(const FtfcRegType *obj)
{
    return ((obj->FCNFG & FTFC_FCNFG_RDCOL_IE_MASK) >> FTFC_FCNFG_RDCOL_IE_SHIFT);
}

/*! \brief Sets the flash read collide interrupt enable
 *
 * This function sets the flash read collide interrupt enable.
 * flash command and ahb bus read collide interrupt enable
 *
 * \param[in] obj : pointer to FTFC register instance
 * \param[in] value : the value of flash read collide interrupt enable
 *                    - 0b : disable interupt
 *                    - 1b : enable interrupt
 */
__attribute__((always_inline)) static inline void FtfcReg_SetFcnfgRdColIE(FtfcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->FCNFG;

    tmp &= ~FTFC_FCNFG_RDCOL_IE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << FTFC_FCNFG_RDCOL_IE_SHIFT)) & FTFC_FCNFG_RDCOL_IE_MASK);
    obj->FCNFG = tmp;
}

/*! \brief Gets the flash eee auto_gc enable
 *
 * This function gets the current eee auto_gc enable.
 * flash eee auto_gc enable
 *
 * \param[in] obj : pointer to FTFC register instance
 * \return eee auto_gc enable
 *         - 0b : auto_gc not enabled
 *         - 1b : auto_gc enabled
 */
__attribute__((always_inline)) static inline uint8_t FtfcReg_GetFcnfgAutoGc(const FtfcRegType *obj)
{
    return ((obj->FCNFG & FTFC_FCNFG_AUTO_GC_MASK) >> FTFC_FCNFG_AUTO_GC_SHIFT);
}

/*! \brief Sets the flash eee auto_gc enable
 *
 * This function sets the flash eee auto_gc enable.
 * flash eee auto_gc enable
 *
 * \param[in] obj : pointer to FTFC register instance
 * \param[in] value : the value of flash eee auto_gc enable
 *                    - 0b : disable auto_gc
 *                    - 1b : enable auto_gc
 */
__attribute__((always_inline)) static inline void FtfcReg_SetFcnfgAutoGc(FtfcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->FCNFG;

    tmp &= ~FTFC_FCNFG_AUTO_GC_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << FTFC_FCNFG_AUTO_GC_SHIFT)) & FTFC_FCNFG_AUTO_GC_MASK);
    obj->FCNFG = tmp;
}

/*! \brief Gets the verify backdoor key enable
 *
 * This function gets the current verify backdoor key enable.
 * enable verify backdoor key command
 *
 * \param[in] obj : pointer to FTFC register instance
 * \return verify backdoor key enable
 *         - 00b : disable
 *         - 01b : disable
 *         - 10b : enable
 *         - 11b : disable
 */
__attribute__((always_inline)) static inline uint8_t FtfcReg_GetFsecKeyEn(const FtfcRegType *obj)
{
    return ((obj->FSEC & FTFC_FSEC_KEYEN_MASK) >> FTFC_FSEC_KEYEN_SHIFT);
}

/*! \brief Gets the mass erase enable
 *
 * This function gets the current mass erase enable.
 * erase all command enable
 *
 * \param[in] obj : pointer to FTFC register instance
 * \return mass erase enable
 *         - 00b : enable
 *         - 01b : enable
 *         - 10b : disable
 *         - 11b : enable
 */
__attribute__((always_inline)) static inline uint8_t FtfcReg_GetFsecMeen(const FtfcRegType *obj)
{
    return ((obj->FSEC & FTFC_FSEC_MEEN_MASK) >> FTFC_FSEC_MEEN_SHIFT);
}

/*! \brief Gets the secure setting
 *
 * This function gets the current secure setting.
 * MCU chip secure setting
 *
 * \param[in] obj : pointer to FTFC register instance
 * \return secure setting
 *         - 10b : unsecure
 *         - 11b : secure
 *         - 01b : secure
 *         - 00b : secure
 */
__attribute__((always_inline)) static inline uint8_t FtfcReg_GetFsecSecure(const FtfcRegType *obj)
{
    return ((obj->FSEC & FTFC_FSEC_SECURE_MASK) >> FTFC_FSEC_SECURE_SHIFT);
}
/*! \brief Gets the pflash protection setting
 *
 * This function gets the current pflash protection setting.
 * pflash protection bits can only change from 1 to 0, unprotection to
 * protection;
 *
 * \param[in] obj : pointer to FTFC register instance
 * \return pflash protection setting
 *         - 0b : corresponding area is unprotected
 *         - 1b : corresponding area is protected
 */
__attribute__((always_inline)) static inline uint32_t FtfcReg_GetPfProtection0(const FtfcRegType *obj)
{
    return ((obj->PFPROT0 & FTFC_PFPROT0_PFPROT0_MASK) >> FTFC_PFPROT0_PFPROT0_SHIFT);
}

/*! \brief Sets the pflash protection setting
 *
 * This function sets the pflash protection setting.
 * pflash protection bits can only change from 1 to 0, unprotection to
 * protection;
 *
 * \param[in] obj : pointer to FTFC register instance
 * \param[in] value : the value of pflash protection setting
 *                    - 0b : corresponding area is unprotected
 *                    - 1b : corresponding area is protected
 */
__attribute__((always_inline)) static inline void FtfcReg_SetPfProtection0(FtfcRegType *obj,
                                                                          uint32_t     value)
{
    uint32_t tmp = obj->PFPROT0;

    tmp &= ~FTFC_PFPROT0_PFPROT0_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << FTFC_PFPROT0_PFPROT0_SHIFT)) & FTFC_PFPROT0_PFPROT0_MASK);
    obj->PFPROT0 = tmp;
}

/*! \brief Gets the pflash protection setting
 *
 * This function gets the current pflash protection setting.
 * pflash protection bits can only change from 1 to 0, unprotection to
 * protection;
 *
 * \param[in] obj : pointer to FTFC register instance
 * \return pflash protection setting
 *         - 0b : corresponding area is unprotected
 *         - 1b : corresponding area is protected
 */
__attribute__((always_inline)) static inline uint32_t FtfcReg_GetPfProtection1(const FtfcRegType *obj)
{
    return ((obj->PFPROT1 & FTFC_PFPROT1_PFPROT1_MASK) >> FTFC_PFPROT1_PFPROT1_SHIFT);
}

/*! \brief Sets the pflash protection setting
 *
 * This function sets the pflash protection setting.
 * pflash protection bits can only change from 1 to 0, unprotection to
 * protection;
 *
 * \param[in] obj : pointer to FTFC register instance
 * \param[in] value : the value of pflash protection setting
 *                    - 0b : corresponding area is unprotected
 *                    - 1b : corresponding area is protected
 */
__attribute__((always_inline)) static inline void FtfcReg_SetPfProtection1(FtfcRegType *obj,
                                                                          uint32_t     value)
{
    uint32_t tmp = obj->PFPROT1;

    tmp &= ~FTFC_PFPROT1_PFPROT1_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << FTFC_PFPROT1_PFPROT1_SHIFT)) & FTFC_PFPROT1_PFPROT1_MASK);
    obj->PFPROT1 = tmp;
}

/*! \brief Gets the dflash protection setting
 *
 * This function gets the current dflash protection setting.
 * dflash protection bits can only change from 0 to 1, unprotection to
 * protection;
 *
 * \param[in] obj : pointer to FTFC register instance
 * \return dflash protection setting
 *         - 0b : corresponding area is unprotected
 *         - 1b : corresponding area is protected
 */
__attribute__((always_inline)) static inline uint16_t FtfcReg_GetDfProtection(const FtfcRegType *obj)
{
    return ((obj->DFPROT & FTFC_DFPROT_DFPROT_MASK) >> FTFC_DFPROT_DFPROT_SHIFT);
}

/*! \brief Sets the dflash protection setting
 *
 * This function sets the dflash protection setting.
 * dflash protection bits can only change from 0 to 1, unprotection to
 * protection;
 *
 * \param[in] obj : pointer to FTFC register instance
 * \param[in] value : the value of dflash protection setting
 *                    - 0b : corresponding area is unprotected
 *                    - 1b : corresponding area is protected
 */
__attribute__((always_inline)) static inline void FtfcReg_SetDfProtection(FtfcRegType *obj, uint16_t value)
{
    uint32_t tmp = obj->DFPROT;

    tmp &= ~FTFC_DFPROT_DFPROT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << FTFC_DFPROT_DFPROT_SHIFT)) & FTFC_DFPROT_DFPROT_MASK);
    obj->DFPROT = tmp;
}

/*! \brief Gets the eee_ram protection setting
 *
 * This function gets the current eee_ram protection setting.
 * dflash protection bits can only change from 0 to 1, unprotection to
 * protection;
 *
 * \param[in] obj : pointer to FTFC register instance
 * \return eee_ram protection setting
 *         - 0b : corresponding area is unprotected
 *         - 1b : corresponding area is protected
 */
__attribute__((always_inline)) static inline uint8_t FtfcReg_GetEfProtection(const FtfcRegType *obj)
{
    return ((obj->EFPROT & FTFC_EFPROT_EFPROT_MASK) >> FTFC_EFPROT_EFPROT_SHIFT);
}

/*! \brief Sets the eee_ram protection setting
 *
 * This function sets the eee_ram protection setting.
 * dflash protection bits can only change from 0 to 1, unprotection to
 * protection;
 *
 * \param[in] obj : pointer to FTFC register instance
 * \param[in] value : the value of eee_ram protection setting
 *                    - 0b : corresponding area is unprotected
 *                    - 1b : corresponding area is protected
 */
__attribute__((always_inline)) static inline void FtfcReg_SetEfProtection(FtfcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->EFPROT;

    tmp &= ~FTFC_EFPROT_EFPROT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << FTFC_EFPROT_EFPROT_SHIFT)) & FTFC_EFPROT_EFPROT_MASK);
    obj->EFPROT = tmp;
}

/*! \brief Gets the secure_info protection setting
 *
 * This function gets the current secure_info protection setting.
 * secure_info protection bits can only change from 0 to 1, unprotection to
 * protection;
 *
 * \param[in] obj : pointer to FTFC register instance
 * \return secure_info protection setting
 *         - 0b : corresponding area is unprotected
 *         - 1b : corresponding area is protected
 */
__attribute__((always_inline)) static inline uint8_t FtfcReg_GetSecProtection(const FtfcRegType *obj)
{
    return ((obj->EFPROT & FTFC_EFPROT_SECPROT_MASK) >> FTFC_EFPROT_SECPROT_SHIFT);
}

/*! \brief Sets the secure_info protection setting
 *
 * This function sets the secure_info protection setting.
 * secure_info protection bits can only change from 0 to 1, unprotection to
 * protection;
 *
 * \param[in] obj : pointer to FTFC register instance
 * \param[in] value : the value of secure_info protection setting
 *                    - 0b : corresponding area is unprotected
 *                    - 1b : corresponding area is protected
 */
__attribute__((always_inline)) static inline void FtfcReg_SetSecProtection(FtfcRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->EFPROT;

    tmp &= ~FTFC_EFPROT_SECPROT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << FTFC_EFPROT_SECPROT_SHIFT)) & FTFC_EFPROT_SECPROT_MASK);
    obj->EFPROT = tmp;
}

/*! \brief Gets the flash common command object
 *
 * This function gets the current flash common command object.
 * when CCIF=0, can not modify this register;
 *
 * \param[in] obj : pointer to FTFC register instance
 * \param[in] index : the index of command object
 *                    - 0 : FCCOB0
 *                    - 1 : FCCOB1
 *                    - 2 : FCCOB2
 *                    - 3 : FCCOB3
 *                    - 4 : FCCOB4
 *                    - 5 : FCCOB5
 *                    - 6 : FCCOB6
 *                    - 7 : FCCOB7
 *                    - 8 : FCCOB8
 *                    - 9 : FCCOB9
 *                    - 10 : FCCOBa
 *                    - 11 : FCCOBb
 *                    - 12 : FCCOBc
 *                    - 13 : FCCOBd
 *                    - 14 : FCCOBe
 *                    - 15 : FCCOBf
 * \return flash common command object
 */
__attribute__((always_inline)) static inline uint8_t FtfcReg_GetFccob(const FtfcRegType *obj, uint8_t index)
{
    uint8_t retval = 0;

    retval = obj->FCCOB[index];

    return retval;
}

/*! \brief Sets the flash common command object
 *
 * This function sets the flash common command object.
 * when CCIF=0, can not modify this register;
 *
 * \param[in] obj : pointer to FTFC register instance
 * \param[in] index : the index of command object
 *                    - 0 : FCCOB0
 *                    - 1 : FCCOB1
 *                    - 2 : FCCOB2
 *                    - 3 : FCCOB3
 *                    - 4 : FCCOB4
 *                    - 5 : FCCOB5
 *                    - 6 : FCCOB6
 *                    - 7 : FCCOB7
 *                    - 8 : FCCOB8
 *                    - 9 : FCCOB9
 *                    - 10 : FCCOBa
 *                    - 11 : FCCOBb
 *                    - 12 : FCCOBc
 *                    - 13 : FCCOBd
 *                    - 14 : FCCOBe
 *                    - 15 : FCCOBf
 * \param[in] value : the value of flash common command object
 */
__attribute__((always_inline)) static inline void FtfcReg_SetFccob(FtfcRegType *obj, uint8_t index, uint8_t value)
{
    uint8_t tmp  = 0;
    uint8_t mask = 0xff;
    tmp          = obj->FCCOB[index];
    tmp &= ~mask;
    tmp |= ((uint8_t)(value)&mask);
    obj->FCCOB[index] = tmp;
}

/*! \brief Gets the csec function backdoor key
 *
 * This function gets the current csec function backdoor key.
 * backdoor keys, for csec command;
 * when CCIF=0, can not modify this register;
 * CSEc keys: 0x43564143;
 * CSEc can configure this register only;
 *
 * \param[in] obj : pointer to FTFC register instance
 * \return csec function backdoor key
 *         - 0h : default value
 */
__attribute__((always_inline)) static inline uint32_t FtfcReg_GetCseBk(const FtfcRegType *obj)
{
    return ((obj->CSEKEY & FTFC_CSEBK_CSEBK_MASK) >> FTFC_CSEBK_CSEBK_SHIFT);
}

/*! \brief Sets the csec function backdoor key
 *
 * This function sets the csec function backdoor key.
 * backdoor keys, for csec command;
 * when CCIF=0, can not modify this register;
 * CSEc keys: 0x43564143;
 * CSEc can configure this register only;
 *
 * \param[in] obj : pointer to FTFC register instance
 * \param[in] value : the value of csec function backdoor key
 *                    - 0h : default value
 */
__attribute__((always_inline)) static inline void FtfcReg_SetCseBk(FtfcRegType *obj, uint32_t value)
{
    uint32_t tmp = obj->CSEKEY;

    tmp &= ~FTFC_CSEBK_CSEBK_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << FTFC_CSEBK_CSEBK_SHIFT)) & FTFC_CSEBK_CSEBK_MASK);
    obj->CSEKEY = tmp;
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _FTFC_REG_H_ */
