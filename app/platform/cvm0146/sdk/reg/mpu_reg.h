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

#ifndef _MPU_REG_H_
#define _MPU_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the MPU Registers
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
/* Error Value */
#define MPU_RES_ERR                  (0xFFu)
/* Size of Reserved Registers Arrays */
#define MPU_REG_EADR_RESEERVED_CONUT (3)
#define MPU_REG_RGDN_RESEERVED_CONUT (0x34)

/* Size of Slave Port Arrays */
#define MPU_SLVPORT_COUNT            (4)

/* Size of Region Descption Arrays */
#define MPU_REGIONDESC_COUNT         (16)

/* Size of Region Descption Alternate Access Control Arrays */
#define MPU_REGIONDESCAAC_COUNT      (16)

/* Slave Port Number Set */
#define MPU_SLVPORT3                 (3)
#define MPU_SLVPORT2                 (2)
#define MPU_SLVPORT1                 (1)
#define MPU_SLVPORT0                 (0)

/* CESR Bit Fields */
#define MPU_CESR_VLD_MASK            (0x1u)
#define MPU_CESR_VLD_SHIFT           (0u)
#define MPU_CESR_VLD_WIDTH           (1u)
#define MPU_CESR_NRGD_MASK           (0xF00u)
#define MPU_CESR_NRGD_SHIFT          (8u)
#define MPU_CESR_NRGD_WIDTH          (4u)
#define MPU_CESR_NSP_MASK            (0xF000u)
#define MPU_CESR_NSP_SHIFT           (12u)
#define MPU_CESR_NSP_WIDTH           (4u)
#define MPU_CESR_HRL_MASK            (0xF0000u)
#define MPU_CESR_HRL_SHIFT           (16u)
#define MPU_CESR_HRL_WIDTH           (4u)
#define MPU_CESR_SPERR3_MASK         (0x10000000u)
#define MPU_CESR_SPERR3_SHIFT        (28u)
#define MPU_CESR_SPERR3_WIDTH        (1u)
#define MPU_CESR_SPERR2_MASK         (0x20000000u)
#define MPU_CESR_SPERR2_SHIFT        (29u)
#define MPU_CESR_SPERR2_WIDTH        (1u)
#define MPU_CESR_SPERR1_MASK         (0x40000000u)
#define MPU_CESR_SPERR1_SHIFT        (30u)
#define MPU_CESR_SPERR1_WIDTH        (1u)
#define MPU_CESR_SPERR0_MASK         (0x80000000u)
#define MPU_CESR_SPERR0_SHIFT        (31u)
#define MPU_CESR_SPERR0_WIDTH        (1u)

/* EARn(0~3) Bit Fields */
#define MPU_EAR_EADDR_MASK           (0xFFFFFFFFu)
#define MPU_EAR_EADDR_SHIFT          (0u)
#define MPU_EAR_EADDR_WIDTH          (32u)

/* EDRn(0~3) Bit Fields */
#define MPU_EDR_ERW_MASK             (0x1u)
#define MPU_EDR_ERW_SHIFT            (0u)
#define MPU_EDR_ERW_WIDTH            (1u)
#define MPU_EDR_EATTR_MASK           (0xEu)
#define MPU_EDR_EATTR_SHIFT          (1u)
#define MPU_EDR_EATTR_WIDTH          (3u)
#define MPU_EDR_EMN_MASK             (0xF0u)
#define MPU_EDR_EMN_SHIFT            (4u)
#define MPU_EDR_EMN_WIDTH            (4u)
#define MPU_EDR_EPID_MASK            (0xFF00u)
#define MPU_EDR_EPID_SHIFT           (8u)
#define MPU_EDR_EPID_WIDTH           (8u)
#define MPU_EDR_EACD_MASK            (0xFFFF0000u)
#define MPU_EDR_EACD_SHIFT           (16u)
#define MPU_EDR_EACD_WIDTH           (16u)

/* RGDn_WD0(0~15) Bit Fields */
#define MPU_RGD_WD0_SRTADDR_MASK     (0xFFFFFFE0u)
#define MPU_RGD_WD0_SRTADDR_SHIFT    (0u)
#define MPU_RGD_WD0_SRTADDR_WIDTH    (27u)

/* RGDn_WD1(0~15) Bit Fields */
#define MPU_RGD_WD1_ENDADDR_MASK     (0xFFFFFFE0u)
#define MPU_RGD_WD1_ENDADDR_SHIFT    (0u)
#define MPU_RGD_WD1_ENDADDR_WIDTH    (27u)

/* RGDn_WD2(0~15) Bit Fields */
#define MPU_RGD_WD2_M0UM_MASK        (0x7u)
#define MPU_RGD_WD2_M0UM_SHIFT       (0u)
#define MPU_RGD_WD2_M0UM_WIDTH       (3u)
#define MPU_RGD_WD2_M0SM_MASK        (0x18u)
#define MPU_RGD_WD2_M0SM_SHIFT       (3u)
#define MPU_RGD_WD2_M0SM_WIDTH       (2u)
#define MPU_RGD_WD2_M0PE_MASK        (0x20u)
#define MPU_RGD_WD2_M0PE_SHIFT       (5u)
#define MPU_RGD_WD2_M0PE_WIDTH       (1u)
#define MPU_RGD_WD2_M1UM_MASK        (0x1C0u)
#define MPU_RGD_WD2_M1UM_SHIFT       (6u)
#define MPU_RGD_WD2_M1UM_WIDTH       (3u)
#define MPU_RGD_WD2_M1SM_MASK        (0x600u)
#define MPU_RGD_WD2_M1SM_SHIFT       (9u)
#define MPU_RGD_WD2_M1SM_WIDTH       (2u)
#define MPU_RGD_WD2_M1PE_MASK        (0x800u)
#define MPU_RGD_WD2_M1PE_SHIFT       (11u)
#define MPU_RGD_WD2_M1PE_WIDTH       (1u)
#define MPU_RGD_WD2_M2UM_MASK        (0x7000u)
#define MPU_RGD_WD2_M2UM_SHIFT       (12u)
#define MPU_RGD_WD2_M2UM_WIDTH       (3u)
#define MPU_RGD_WD2_M2SM_MASK        (0x18000u)
#define MPU_RGD_WD2_M2SM_SHIFT       (15u)
#define MPU_RGD_WD2_M2SM_WIDTH       (2u)
#define MPU_RGD_WD2_M3UM_MASK        (0x1C0000u)
#define MPU_RGD_WD2_M3UM_SHIFT       (18u)
#define MPU_RGD_WD2_M3UM_WIDTH       (3u)
#define MPU_RGD_WD2_M3SM_MASK        (0x600000u)
#define MPU_RGD_WD2_M3SM_SHIFT       (21u)
#define MPU_RGD_WD2_M3SM_WIDTH       (2u)

/* RGDn_WD3(0~15) Bit Fields */
#define MPU_RGD_WD3_VLD_MASK         (0x1u)
#define MPU_RGD_WD3_VLD_SHIFT        (0u)
#define MPU_RGD_WD3_VLD_WIDTH        (1u)
#define MPU_RGD_WD3_PIDMASK_MASK     (0xFF0000u)
#define MPU_RGD_WD3_PIDMASK_SHIFT    (16u)
#define MPU_RGD_WD3_PIDMASK_WIDTH    (8u)
#define MPU_RGD_WD3_PID_MASK         (0xFF000000u)
#define MPU_RGD_WD3_PID_SHIFT        (24u)
#define MPU_RGD_WD3_PID_WIDTH        (8u)

/* RGDAAC(0~15) Bit Fields */
#define MPU_RGDAAC_M0UM_MASK         (0x7u)
#define MPU_RGDAAC_M0UM_SHIFT        (0u)
#define MPU_RGDAAC_M0UM_WIDTH        (3u)
#define MPU_RGDAAC_M0SM_MASK         (0x18u)
#define MPU_RGDAAC_M0SM_SHIFT        (3u)
#define MPU_RGDAAC_M0SM_WIDTH        (2u)
#define MPU_RGDAAC_M0PE_MASK         (0x20u)
#define MPU_RGDAAC_M0PE_SHIFT        (5u)
#define MPU_RGDAAC_M0PE_WIDTH        (1u)
#define MPU_RGDAAC_M1UM_MASK         (0x1C0u)
#define MPU_RGDAAC_M1UM_SHIFT        (6u)
#define MPU_RGDAAC_M1UM_WIDTH        (3u)
#define MPU_RGDAAC_M1SM_MASK         (0x600u)
#define MPU_RGDAAC_M1SM_SHIFT        (9u)
#define MPU_RGDAAC_M1SM_WIDTH        (2u)
#define MPU_RGDAAC_M1PE_MASK         (0x800u)
#define MPU_RGDAAC_M1PE_SHIFT        (11u)
#define MPU_RGDAAC_M1PE_WIDTH        (1u)
#define MPU_RGDAAC_M2UM_MASK         (0x7000u)
#define MPU_RGDAAC_M2UM_SHIFT        (12u)
#define MPU_RGDAAC_M2UM_WIDTH        (3u)
#define MPU_RGDAAC_M2SM_MASK         (0x18000u)
#define MPU_RGDAAC_M2SM_SHIFT        (15u)
#define MPU_RGDAAC_M2SM_WIDTH        (2u)
#define MPU_RGDAAC_M3UM_MASK         (0x1C0000u)
#define MPU_RGDAAC_M3UM_SHIFT        (18u)
#define MPU_RGDAAC_M3UM_WIDTH        (3u)
#define MPU_RGDAAC_M3SM_MASK         (0x600000u)
#define MPU_RGDAAC_M3SM_SHIFT        (21u)
#define MPU_RGDAAC_M3SM_WIDTH        (3u)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief The definition of MPU registers
 */
typedef struct _MpuRegType_
{
    volatile uint32_t CESR;                                    /*!< Control, Error info and Mpu Enable Register, offset: 0x0 */
    uint32_t          RESERVED0[MPU_REG_EADR_RESEERVED_CONUT]; /* Reserved Register, offset: 0x04, array step: 0x0C */
    struct                                                     
    {                                                          /*!< offset: 0x10, array step: 0x08 */
        const volatile uint32_t EAR;                           /*!< Slave Port Error Register Address, offset: 0x10, array step: 0x08 */
        const volatile uint32_t EDR;                           /*!< Slave Port Error Detail Register, offset: 0x14, array step: 0x08 */
    } SLVPORT[MPU_SLVPORT_COUNT];                              
    uint32_t RESERVED1[MPU_REG_RGDN_RESEERVED_CONUT];          /* Reserved register, offset: 0x30, array step: 0xD0 */
    struct                                                     
    {                                                          /*!< offset: 0x100, array step: 0x10 */
        volatile uint32_t WORD0;                               /*!< Value of Access Start Register Address, offset: 0x100, array step: 0x10 */
        volatile uint32_t WORD1;                               /*!< Value of Access End Register Address, offset : 0x104, array step: 0x10 */
        volatile uint32_t WORD2;                               /*!< Configure of Master Access Rights Register, offset: 0x108, array step: 0x10 */
        volatile uint32_t WORD3;                               /*!< Configure of PID, PID Mask and Region Description valid, offset: 0x10C, array step: 0x10 */
    } RGD[MPU_REGIONDESC_COUNT];                               
    volatile uint32_t                                          
        AAC[MPU_REGIONDESC_COUNT];                             /*!< Configure of Master Alternate Access Rights Register, offset: 0x200, array step: 0x04 */
} MpuRegType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Enables the MPU module.
 *
 * This function enables the functional of MPU module
 *
 * \param[in] obj : pointer to MPU register instance
 * \param[in] enable State
 *             - 1  : Enable the MPU module.
 *             - 0  : Disable the MPU module.
 * \return None
 */
__attribute__((always_inline)) static inline void MpuReg_GlobalEnable(MpuRegType *obj, uint8_t enable)
{
    uint32_t tmp = obj->CESR;

    tmp &= ~MPU_CESR_VLD_MASK;
    tmp |= (((uint32_t)(enable ? 1u << MPU_CESR_VLD_SHIFT : 0u << MPU_CESR_VLD_SHIFT)) & MPU_CESR_VLD_MASK);
    obj->CESR = tmp;
}

/*! \brief Get MPU module status.
 *
 * This function get the functional of MPU module status
 *
 * \param[in] obj : pointer to MPU register instance
 * \return MPU Global Enable valid or invalid
 */
__attribute__((always_inline)) static inline uint8_t MpuReg_GetMpuGlobalEnableStatus(const MpuRegType *obj)
{
    return ((obj->CESR & MPU_CESR_VLD_MASK) >> MPU_CESR_VLD_SHIFT);
}

/*! \brief Get Number of Region Description.
 *
 * This function get the Number of Region Description.
 *
 * \param[in] obj : pointer to MPU register instance
 * \return the current command of debug mode
 *             - 0 : 8 of Region Description
 *             - 1 : 12 of Region Description
 *             - 2 : 16 of Region Description
 */
__attribute__((always_inline)) static inline uint8_t MpuReg_GetNumOfRegionDesc(const MpuRegType *obj)
{
    return ((obj->CESR & MPU_CESR_NRGD_MASK) >> MPU_CESR_NRGD_SHIFT);
}

/*! \brief Get Number of Slave Port.
 *
 * This function get the Number of Slave Port.
 *
 * \param[in] obj : pointer to MPU register instance
 * \return the Number of Slave Port
 *             - 4 : default value is 4, other values are undefined
 */
__attribute__((always_inline)) static inline uint8_t MpuReg_GetNumOfSlavePort(const MpuRegType *obj)
{
    return ((obj->CESR & MPU_CESR_NSP_MASK) >> MPU_CESR_NSP_SHIFT);
}

/*! \brief Get Hardware Revision Level.
 *
 * This function get the Get Hardware Revision Level.
 *
 * \param[in] obj : pointer to MPU register instance
 * \return the Hardware Revision Level
 *             - 1 : version of this chip
 */
__attribute__((always_inline)) static inline uint8_t MpuReg_GetHwOfRevLvl(const MpuRegType *obj)
{
    return ((obj->CESR & MPU_CESR_HRL_MASK) >> MPU_CESR_HRL_SHIFT);
}

/*! \brief Get Slave Port Error Status.
 *
 * This function get the Slave Port Error Status.
 *
 * \param[in] obj : pointer to MPU register instance
 * \param[in] port : set number of port
 * \return the Hardware Revision Level
 *             - 1 : An error has occurred for slave port
 * *           - 0 : None error has occurred for slave port
 */
__attribute__((always_inline)) static inline uint8_t MpuReg_GetSlvPortErrStatus(const MpuRegType *obj, uint8_t port)
{
    switch(port)
    {
    case MPU_SLVPORT3:
        return ((obj->CESR & MPU_CESR_SPERR3_MASK) >> MPU_CESR_SPERR3_SHIFT);
    case MPU_SLVPORT2:
        return ((obj->CESR & MPU_CESR_SPERR2_MASK) >> MPU_CESR_SPERR2_SHIFT);
    case MPU_SLVPORT1:
        return ((obj->CESR & MPU_CESR_SPERR1_MASK) >> MPU_CESR_SPERR1_SHIFT);
    case MPU_SLVPORT0:
        return ((obj->CESR & MPU_CESR_SPERR0_MASK) >> MPU_CESR_SPERR0_SHIFT);
    default:
        return MPU_RES_ERR;
    }
}

/*! \brief Clear Slave Port Error status.
 *
 * This function clear the Slave Port Error Status.
 *
 * \param[in] obj : pointer to MPU register instance
 * \param[in] port : set number of port
 */
__attribute__((always_inline)) static inline void MpuReg_ClrSlvPortErrStatus(MpuRegType *obj, uint8_t port)
{
    switch(port)
    {
    case MPU_SLVPORT3:
        obj->CESR |= MPU_CESR_SPERR3_MASK;
        break;
    case MPU_SLVPORT2:
        obj->CESR |= MPU_CESR_SPERR2_MASK;
        break;
    case MPU_SLVPORT1:
        obj->CESR |= MPU_CESR_SPERR1_MASK;
        break;
    case MPU_SLVPORT0:
        obj->CESR |= MPU_CESR_SPERR0_MASK;
        break;
    default:
        break;
    }
}

/*! \brief Get Slave Port Error Address.
 *
 * This function get the Slave Port Error Address.
 *
 * \param[in] obj : pointer to MPU register instance
 * \param[in] port : set number of port
 * \return Error Address
 *                 An error has occurred for slave port, return error address
 */
__attribute__((always_inline)) static inline uint32_t MpuReg_GetSlvPortErrAddr(const MpuRegType *obj, uint8_t port)
{
    return ((obj->SLVPORT[port].EAR & MPU_EAR_EADDR_MASK) >> MPU_EAR_EADDR_SHIFT);
}

/*! \brief Get Slave Port Error Detail Type R/W.
 *
 * This function get the Slave Port Error Detail Type R/W.
 *
 * \param[in] obj : pointer to MPU register instance
 * \param[in] port : set number of port
 * \return Error Type for R/W
 *
 */
__attribute__((always_inline)) static inline uint8_t MpuReg_GetSlvPortErrDetailERW(const MpuRegType *obj, uint8_t port)
{
    return ((obj->SLVPORT[port].EDR & MPU_EDR_ERW_MASK) >> MPU_EDR_ERW_SHIFT);
}

/*! \brief Get Slave Port Error Detail Type Attribute.
 *
 * This function get the Slave Port Error Detail Type Attribute.
 *
 * \param[in] obj : pointer to MPU register instance
 * \param[in] port : set number of port
 * \return Error Type for Attribute
 *             - 0 : Mode - User,       Access - Instruction
 *             - 1 : Mode - User,       Access - Data
 *             - 2 : Mode - privilege,  Access - Instruction
 *             - 3 : Mode - privilege,  Access - Data
 *
 */
__attribute__((always_inline)) static inline uint8_t MpuReg_GetSlvPortErrDetailEAttr(const MpuRegType *obj, uint8_t port)
{
    return ((obj->SLVPORT[port].EDR & MPU_EDR_EATTR_MASK) >> MPU_EDR_EATTR_SHIFT);
}

/*! \brief Get Slave Port Error Detail Type ErrMasterNumber.
 *
 * This function get the Slave Port Error Detail Type ErrMasterNumber.
 *
 * \param[in] obj : pointer to MPU register instance
 * \param[in] port : set number of port
 * \return Error Type for ErrMasterNumber
 *             - 0 : CPU CORE
 *             - 1 : DEBUG
 *             - 2 : CPU CORE
 *             - 3 : CPU CORE
 *             - 4 : DMA
 *             - 5 : CSE
 *
 */
__attribute__((always_inline)) static inline uint8_t MpuReg_GetSlvPortErrDetailEMN(const MpuRegType *obj, uint8_t port)
{
    return ((obj->SLVPORT[port].EDR & MPU_EDR_EMN_MASK) >> MPU_EDR_EMN_SHIFT);
}

/*! \brief Get Error Process ID
 *
 * This function record error process identification.
 *
 * \param[in] obj : pointer to MPU register instance
 * \param[in] port : set number of port
 * \return Error Type for Error Process ID Number.
 *
 */
__attribute__((always_inline)) static inline uint8_t MpuReg_GetSlvPortErrPID(const MpuRegType *obj, uint8_t port)
{
    return ((obj->SLVPORT[port].EDR & MPU_EDR_EPID_MASK) >> MPU_EDR_EPID_SHIFT);
}

/*! \brief Get Access Region Error Description.
 *
 * This function record error process identification.
 *
 * \param[in] obj : pointer to MPU register instance
 * \param[in] port : set number of port
 * \return Access Error Description.
 *             - 0 : Hit none region
 *             - one bit set : Hit protect single unoverlapping description
 *             - multi bit set : Hit protect multi overlapping description
 *
 */
__attribute__((always_inline)) static inline uint16_t MpuReg_GetSlvPortEACD(const MpuRegType *obj, uint8_t port)
{
    return (uint16_t)((obj->SLVPORT[port].EDR & MPU_EDR_EACD_MASK) >> MPU_EDR_EACD_SHIFT);
}

/*! \brief Set Region Description Start Address.
 *
 * This function set region description start address.
 *
 * \param[in] obj : pointer to MPU register instance
 * \param[in] startAddr : protect start address
 * \param[in] regDescNumber : Region Description number set
 * \return None
 *
 */
__attribute__((always_inline)) static inline void MpuReg_SetRegionDescStartAddr(MpuRegType *obj, uint32_t startAddr, uint8_t regDescNum)
{
    uint32_t tmp = obj->RGD[regDescNum].WORD0;

    tmp &= ~MPU_RGD_WD0_SRTADDR_MASK;
    tmp |= (((uint32_t)((uint32_t)startAddr << MPU_RGD_WD0_SRTADDR_SHIFT)) & MPU_RGD_WD0_SRTADDR_MASK);
    obj->RGD[regDescNum].WORD0 = tmp;
}

/*! \brief Get Region Description Start Address.
 *
 * This function get region description start address.
 *
 * \param[in] obj : pointer to MPU register instance
 * \param[in] startAddr : protect start address
 * \return current region description protect start address
 *
 */
__attribute__((always_inline)) static inline uint32_t MpuReg_GetRegionDescStartAddr(const MpuRegType *obj, uint8_t regDescNum)
{
    return ((obj->RGD[regDescNum].WORD0 & MPU_RGD_WD0_SRTADDR_MASK) >> MPU_RGD_WD0_SRTADDR_SHIFT);
}

/*! \brief Set Region Description End Address.
 *
 * This function set region description end address.
 *
 * \param[in] obj : pointer to MPU register instance
 * \param[in] endAddr : protect end address
 * \param[in] regDescNum : Region Description number set
 * \return None
 *
 */
__attribute__((always_inline)) static inline void MpuReg_SetRegionDescEndAddr(MpuRegType *obj, uint32_t endAddr, uint8_t regDescNum)
{
    uint32_t tmp = obj->RGD[regDescNum].WORD1;

    tmp &= ~MPU_RGD_WD1_ENDADDR_MASK;
    tmp |= (((uint32_t)((uint32_t)endAddr << MPU_RGD_WD1_ENDADDR_SHIFT)) & MPU_RGD_WD1_ENDADDR_MASK);
    obj->RGD[regDescNum].WORD1 = tmp;
}

/*! \brief Get Region Description End Address.
 *
 * This function get region description end address.
 *
 * \param[in] obj : pointer to MPU register instance
 * \param[in] endAddr : protect start address
 * \return current region description protect end address
 *
 */
__attribute__((always_inline)) static inline uint32_t MpuReg_GetRegionDescEndAddr(const MpuRegType *obj, uint8_t regDescNum)
{
    return ((obj->RGD[regDescNum].WORD1 & MPU_RGD_WD1_ENDADDR_MASK) >> MPU_RGD_WD1_ENDADDR_SHIFT);
}

/*! \brief Set Region Description User Bus Masterx Authority mode.
 *
 * This function set region description user bus master authority mode.
 *
 * \param[in] obj : pointer to MPU register instance
 * \param[in] regDescNum : Region Description number set
 * \param[in] masterNo : Select Master number
 *             - 0 : Bus Master0
 *             - 1 : Bus Master1
 *             - 2 : Bus Master2
 *             - 3 : Bus Master3
 * \param[in] userMode : Configure Masterx Access Authority bit[0/1/2]
 *             - 0 : Try to access may abort by error, and do not excute Access
 *             - 1 : Access will be grant
 * \return None
 *
 */
__attribute__((always_inline)) static inline void MpuReg_SetRegionDescUserAuthority(MpuRegType *obj, uint8_t regDescNum, uint8_t masterNo, uint8_t userMode)
{
    uint32_t tmp = obj->RGD[regDescNum].WORD2;

    switch(masterNo)
    {
    case 0:
        tmp &= ~MPU_RGD_WD2_M0UM_MASK;  /*!< Bus Master0 User mode */
        tmp |= (((uint32_t)((uint32_t)userMode << MPU_RGD_WD2_M0UM_SHIFT)) & MPU_RGD_WD2_M0UM_MASK);
        obj->RGD[regDescNum].WORD2 = tmp;
        break;
    case 1:
        tmp &= ~MPU_RGD_WD2_M1UM_MASK;  /*!< Bus Master1 User mode */
        tmp |= (((uint32_t)((uint32_t)userMode << MPU_RGD_WD2_M1UM_SHIFT)) & MPU_RGD_WD2_M1UM_MASK);
        obj->RGD[regDescNum].WORD2 = tmp;
        break;
    case 2:
        tmp &= ~MPU_RGD_WD2_M2UM_MASK;  /*!< Bus Master2 User mode */
        tmp |= (((uint32_t)((uint32_t)userMode << MPU_RGD_WD2_M2UM_SHIFT)) & MPU_RGD_WD2_M2UM_MASK);
        obj->RGD[regDescNum].WORD2 = tmp;
        break;
    case 3:
        tmp &= ~MPU_RGD_WD2_M3UM_MASK;  /*!< Bus Master3 User mode */
        tmp |= (((uint32_t)((uint32_t)userMode << MPU_RGD_WD2_M3UM_SHIFT)) & MPU_RGD_WD2_M3UM_MASK);
        obj->RGD[regDescNum].WORD2 = tmp;
        break;
    default:
        break;
    }
}

/*! \brief Get Region Description User Bus Masterx Authority mode.
 *
 * This function get region description user bus master authority mode.
 *
 * \param[in] obj : pointer to MPU register instance
 * \param[in] regDescNum : Region Description number set
 * \param[in] masterNo : Select Master number
 *             - 0 : Bus Master0
 *             - 1 : Bus Master1
 *             - 2 : Bus Master2
 *             - 3 : Bus Master3
 * \return Masterx Access Authority bit[0/1/2]
 *
 */
__attribute__((always_inline)) static inline uint8_t MpuReg_GetRegionDescUserAuthority(const MpuRegType *obj, uint8_t regDescNum, uint8_t masterNo)
{
    switch(masterNo)
    {
    case 0:
        return ((obj->RGD[regDescNum].WORD2 & MPU_RGD_WD2_M0UM_MASK) >> MPU_RGD_WD2_M0UM_SHIFT); /*!< Bus Master0 User mode */
    case 1:
        return ((obj->RGD[regDescNum].WORD2 & MPU_RGD_WD2_M1UM_MASK) >> MPU_RGD_WD2_M1UM_SHIFT); /*!< Bus Master1 User mode */
    case 2:
        return ((obj->RGD[regDescNum].WORD2 & MPU_RGD_WD2_M2UM_MASK) >> MPU_RGD_WD2_M2UM_SHIFT); /*!< Bus Master2 User mode */
    case 3:
        return ((obj->RGD[regDescNum].WORD2 & MPU_RGD_WD2_M3UM_MASK) >> MPU_RGD_WD2_M3UM_SHIFT); /*!< Bus Master3 User mode */
    default:
        return MPU_RES_ERR;
    }
}

/*! \brief Set Region Description Privilege Bus Masterx Authority mode.
 *
 * This function set region description privilege bus master authority mode.
 *
 * \param[in] obj : pointer to MPU register instance
 * \param[in] regDescNum : Region Description number set
 * \param[in] masterNo : Select Master number
 *             - 0 : Bus Master0
 *             - 1 : Bus Master1
 *             - 2 : Bus Master2
 *             - 3 : Bus Master3
 * \param[in] userMode : Configure Masterx Access Authority
 *             - 0 : R/W/X
 *             - 1 : R/X
 *             - 2 : R/W
 *             - 3 : same as user masterx
 * \return None
 *
 */
__attribute__((always_inline)) static inline void MpuReg_SetRegionDescPrivilegeAuthority(MpuRegType *obj, uint8_t regDescNum, uint8_t masterNo, uint8_t privilegeMode)
{
    uint32_t tmp = obj->RGD[regDescNum].WORD2;

    switch(masterNo)
    {
    case 0:
        tmp &= ~MPU_RGD_WD2_M0SM_MASK;      /*!< Bus Master0 Privilege mode */
        tmp |= (((uint32_t)((uint32_t)privilegeMode << MPU_RGD_WD2_M0SM_SHIFT)) & MPU_RGD_WD2_M0SM_MASK);
        obj->RGD[regDescNum].WORD2 = tmp;
        break;
    case 1:
        tmp &= ~MPU_RGD_WD2_M1SM_MASK;      /*!< Bus Master1 Privilege mode */
        tmp |= (((uint32_t)((uint32_t)privilegeMode << MPU_RGD_WD2_M1SM_SHIFT)) & MPU_RGD_WD2_M1SM_MASK);
        obj->RGD[regDescNum].WORD2 = tmp;
        break;
    case 2:
        tmp &= ~MPU_RGD_WD2_M2SM_MASK;      /*!< Bus Master2 Privilege mode */
        tmp |= (((uint32_t)((uint32_t)privilegeMode << MPU_RGD_WD2_M2SM_SHIFT)) & MPU_RGD_WD2_M2SM_MASK);
        obj->RGD[regDescNum].WORD2 = tmp;
        break;
    case 3:
        tmp &= ~MPU_RGD_WD2_M3SM_MASK;      /*!< Bus Master3 Privilege mode */
        tmp |= (((uint32_t)((uint32_t)privilegeMode << MPU_RGD_WD2_M3SM_SHIFT)) & MPU_RGD_WD2_M3SM_MASK);
        obj->RGD[regDescNum].WORD2 = tmp;
        break;
    default:
        break;
    }
}

/*! \brief Get Region Description Privilege Bus Masterx Authority mode.
 *
 * This function get region description privilege bus master authority mode.
 *
 * \param[in] obj : pointer to MPU register instance
 * \param[in] regDescNum : Region Description number set
 * \param[in] masterNo : Select Master number
 *             - 0 : Bus Master0
 *             - 1 : Bus Master1
 *             - 2 : Bus Master2
 *             - 3 : Bus Master3
 * \return Masterx Access Authority
 *             - 0 : R/W/X
 *             - 1 : R/X
 *             - 2 : R/W
 *             - 3 : same as user masterx
 *
 */
__attribute__((always_inline)) static inline uint8_t MpuReg_GetRegionDescPrivilegeAuthority(const MpuRegType *obj, uint8_t regDescNum, uint8_t masterNo)
{
    switch(masterNo)
    {
    case 0:
        return ((obj->RGD[regDescNum].WORD2 & MPU_RGD_WD2_M0SM_MASK) >> MPU_RGD_WD2_M0SM_SHIFT); /*!< Bus Master0 Privilege mode */
    case 1:
        return ((obj->RGD[regDescNum].WORD2 & MPU_RGD_WD2_M1SM_MASK) >> MPU_RGD_WD2_M1SM_SHIFT); /*!< Bus Master1 Privilege mode */
    case 2:
        return ((obj->RGD[regDescNum].WORD2 & MPU_RGD_WD2_M2SM_MASK) >> MPU_RGD_WD2_M2SM_SHIFT); /*!< Bus Master2 Privilege mode */
    case 3:
        return ((obj->RGD[regDescNum].WORD2 & MPU_RGD_WD2_M3SM_MASK) >> MPU_RGD_WD2_M3SM_SHIFT); /*!< Bus Master3 Privilege mode */
    default:
        return MPU_RES_ERR;
    }
}

/*! \brief Set Evaluate if Processing include PID.
 *
 * This function set evaluate if processing include Process Identification.
 *
 * \param[in] obj : pointer to MPU register instance
 * \param[in] regDescNum : Region Description number set
 * \param[in] masterNo : Select Master number
 *             - 0 : Bus Master0
 *             - 1 : Bus Master1
 * \param[in] pidMode : Configure Evaluate Process
 *             - 0 : Evaluate processing do not include PID
 *             - 1 : Evaluate processing include PID
 * \return None
 *
 */
__attribute__((always_inline)) static inline void MpuReg_SetRegionDescPIDFlagEnable(MpuRegType *obj, uint8_t regDescNum, uint8_t masterNo, uint8_t pidMode)
{
    uint32_t tmp = obj->RGD[regDescNum].WORD2;
    
    switch(masterNo)
    {
    case 0:
        tmp &= ~MPU_RGD_WD2_M0PE_MASK;      /*!< Bus Master0 PID mode */
        tmp |= (((uint32_t)((uint32_t)pidMode << MPU_RGD_WD2_M0PE_SHIFT)) & MPU_RGD_WD2_M0PE_MASK);
        obj->RGD[regDescNum].WORD2 = tmp;
        break;
    case 1:
        tmp &= ~MPU_RGD_WD2_M1PE_MASK;      /*!< Bus Master1 PID mode */
        tmp |= (((uint32_t)((uint32_t)pidMode << MPU_RGD_WD2_M1PE_SHIFT)) & MPU_RGD_WD2_M1PE_MASK);
        obj->RGD[regDescNum].WORD2 = tmp;
        break;
    default:
        break;
    }
}

/*! \brief Get Evaluate Processing include PID.
 *
 * This function get evaluate processing include Process Identification.
 *
 * \param[in] obj : pointer to MPU register instance
 * \param[in] regDescNum : Region Description number set
 * \param[in] masterNo : Select Master number
 *             - 0 : Bus Master0
 *             - 1 : Bus Master1
 * \return Evaluate Process
 *             - 0 : Evaluate processing do not include PID
 *             - 1 : Evaluate processing include PID
 *
 */
__attribute__((always_inline)) static inline uint8_t MpuReg_GetRegionDescPIDFlagEnableStatus(const MpuRegType *obj, uint8_t regDescNum, uint8_t masterNo)
{
    switch(masterNo)
    {
    case 0:
        return ((obj->RGD[regDescNum].WORD2 & MPU_RGD_WD2_M0PE_MASK) >> MPU_RGD_WD2_M0PE_SHIFT); /*!< Bus Master0 PID mode */
    case 1:
        return ((obj->RGD[regDescNum].WORD2 & MPU_RGD_WD2_M1PE_MASK) >> MPU_RGD_WD2_M1PE_SHIFT); /*!< Bus Master1 PID mode */
    default:
        return MPU_RES_ERR;
    }
}

/*! \brief Set Region Description valid or invalid.
 *
 * This function set region description valid or not.
 *
 * \param[in] obj : pointer to MPU register instance
 * \param[in] regDescNum : Region Description number set
 * \param[in] valid : Configure Region Description
 *             - 0 : Region Description invalid
 *             - 1 : Region Description valid
 * \return None
 *
 */
__attribute__((always_inline)) static inline void MpuReg_SetRegionDescValid(MpuRegType *obj, uint8_t regDescNum, uint8_t valid)
{
    uint32_t tmp = obj->RGD[regDescNum].WORD3;
    
    tmp &= ~MPU_RGD_WD3_VLD_MASK;
    tmp |= (((uint32_t)((uint32_t)valid << MPU_RGD_WD3_VLD_SHIFT)) & MPU_RGD_WD3_VLD_MASK);
    obj->RGD[regDescNum].WORD3 = tmp;
}

/*! \brief Get Region Description valid or invalid.
 *
 * This function get region description valid or not.
 *
 * \param[in] obj : pointer to MPU register instance
 * \param[in] regDescNum : Region Description number set
 * \return Region Description
 *             - 0 : Region Description invalid
 *             - 1 : Region Description valid
 *
 */
__attribute__((always_inline)) static inline uint8_t MpuReg_GetRegionDescValid(const MpuRegType *obj, uint8_t regDescNum)
{
    return ((obj->RGD[regDescNum].WORD3 & MPU_RGD_WD3_VLD_MASK) >> MPU_RGD_WD3_VLD_SHIFT);
}

/*! \brief Set Processing Identification Mask.
 *
 * This function set processing identification mask.
 *
 * \param[in] obj : pointer to MPU register instance
 * \param[in] regDescNum : Region Description number set
 * \param[in] PIDMask : Configure Processing ID Mask
 * \return None
 *
 */
__attribute__((always_inline)) static inline void MpuReg_SetPIDMask(MpuRegType *obj, uint8_t regDescNum, uint8_t pidMask)
{
    uint32_t tmp = obj->RGD[regDescNum].WORD3;
    
    tmp &= ~MPU_RGD_WD3_PIDMASK_MASK;
    tmp |= (((uint32_t)((uint32_t)pidMask << MPU_RGD_WD3_PIDMASK_SHIFT)) & MPU_RGD_WD3_PIDMASK_MASK);
    obj->RGD[regDescNum].WORD3 = tmp;
}

/*! \brief Get Processing Identification Mask.
 *
 * This function get processing identification mask.
 *
 * \param[in] obj : pointer to MPU register instance
 * \param[in] regDescNum : Region Description number set
 * \return Processing ID Mask value
 *
 */
__attribute__((always_inline)) static inline uint8_t MpuReg_GetPIDMask(const MpuRegType *obj, uint8_t regDescNum)
{
    return ((obj->RGD[regDescNum].WORD3 & MPU_RGD_WD3_PIDMASK_MASK) >> MPU_RGD_WD3_PIDMASK_SHIFT);
}

/*! \brief Set Processing Identification.
 *
 * This function set processing identification.
 *
 * \param[in] obj : pointer to MPU register instance
 * \param[in] regDescNum : Region Description number set
 * \param[in] PID : Configure Processing ID Mask
 * \return None
 *
 */
__attribute__((always_inline)) static inline void MpuReg_SetPID(MpuRegType *obj, uint8_t regDescNum, uint8_t pid)
{
    uint32_t tmp = obj->RGD[regDescNum].WORD3;
    
    tmp &= ~MPU_RGD_WD3_PID_MASK;
    tmp |= (((uint32_t)((uint32_t)pid << MPU_RGD_WD3_PID_SHIFT)) & MPU_RGD_WD3_PID_MASK);
    obj->RGD[regDescNum].WORD3 = tmp;
}

/*! \brief Get Processing Identification.
 *
 * This function get processing identification.
 *
 * \param[in] obj : pointer to MPU register instance
 * \param[in] regDescNum : Region Description number set
 * \return Processing ID value
 *
 */
__attribute__((always_inline)) static inline uint8_t MpuReg_GetPID(const MpuRegType *obj, uint8_t regDescNum)
{
    return ((obj->RGD[regDescNum].WORD3 & MPU_RGD_WD3_PID_MASK) >> MPU_RGD_WD3_PID_SHIFT);
}

/*! \brief Set Region Description Alternate Access Control User Bus Masterx Authority mode.
 *
 * This function set region description alternate access control user bus master authority mode.
 *
 * \param[in] obj : pointer to MPU register instance
 * \param[in] regDescNum : Region Description number set
 * \param[in] masterNo : Select Master Num
 *             - 0 : Bus Master0
 *             - 1 : Bus Master1
 *             - 2 : Bus Master2
 *             - 3 : Bus Master3
 * \param[in] aacUserMode : Configure Masterx Access Authority bit[0/1/2]
 *             - 0 : Try to access may abort by error, and do not excute Access
 *             - 1 : Access will be grant
 * \return None
 *
 */
__attribute__((always_inline)) static inline void MpuReg_SetRegionDescAACUserAuthority(MpuRegType *obj, uint8_t aacChnNum, uint8_t masterNo, uint8_t aacUserMode)
{
    uint32_t tmp = obj->AAC[aacChnNum];
    
    switch(masterNo)
    {
    case 0:
        tmp &= ~MPU_RGDAAC_M0UM_MASK;       /*!< AAC Master0 User mode */
        tmp |= (((uint32_t)((uint32_t)aacUserMode << MPU_RGDAAC_M0UM_SHIFT)) & MPU_RGDAAC_M0UM_MASK);
        obj->AAC[aacChnNum] = tmp;
        break;
    case 1:
        tmp &= ~MPU_RGDAAC_M1UM_MASK;       /*!< AAC Master1 User mode */
        tmp |= (((uint32_t)((uint32_t)aacUserMode << MPU_RGDAAC_M1UM_SHIFT)) & MPU_RGDAAC_M1UM_MASK);
        obj->AAC[aacChnNum] = tmp;
        break;
    case 2:
        tmp &= ~MPU_RGDAAC_M2UM_MASK;       /*!< AAC Master2 User mode */
        tmp |= (((uint32_t)((uint32_t)aacUserMode << MPU_RGDAAC_M2UM_SHIFT)) & MPU_RGDAAC_M2UM_MASK);
        obj->AAC[aacChnNum] = tmp;
        break;
    case 3:
        tmp &= ~MPU_RGDAAC_M3UM_MASK;       /*!< AAC Master2 User mode */
        tmp |= (((uint32_t)((uint32_t)aacUserMode << MPU_RGDAAC_M3UM_SHIFT)) & MPU_RGDAAC_M3UM_MASK);
        obj->AAC[aacChnNum] = tmp;
        break;
    default:
        break;
    }
}

/*! \brief Get Region Description Alternate Access Control User Bus Masterx Authority mode.
 *
 * This function get region description alternate access control user bus master authority mode.
 *
 * \param[in] obj : pointer to MPU register instance
 * \param[in] regDescNum : Region Description number set
 * \param[in] masterNo : Select Master number
 *             - 0 : Bus Master0
 *             - 1 : Bus Master1
 *             - 2 : Bus Master2
 *             - 3 : Bus Master3
 * \return Masterx Access Authority bit[0/1/2]
 *
 */
__attribute__((always_inline)) static inline uint8_t MpuReg_GetRegionDescAACUserAuthority(const MpuRegType *obj, uint8_t aacChnNum, uint8_t masterNo)
{
    switch(masterNo)
    {
    case 0:
        return (uint8_t)((obj->AAC[aacChnNum] & MPU_RGDAAC_M0UM_MASK) >> MPU_RGDAAC_M0UM_SHIFT); /*!< AAC Master0 User mode */
    case 1:
        return (uint8_t)((obj->AAC[aacChnNum] & MPU_RGDAAC_M1UM_MASK) >> MPU_RGDAAC_M1UM_SHIFT); /*!< AAC Master1 User mode */
    case 2:
        return (uint8_t)((obj->AAC[aacChnNum] & MPU_RGDAAC_M2UM_MASK) >> MPU_RGDAAC_M2UM_SHIFT); /*!< AAC Master2 User mode */
    case 3:
        return (uint8_t)((obj->AAC[aacChnNum] & MPU_RGDAAC_M3UM_MASK) >> MPU_RGDAAC_M3UM_SHIFT); /*!< AAC Master3 User mode */
    default:
        return MPU_RES_ERR;
    }
}

/*! \brief Set Region Description Alternate Access Control Privilege Bus Masterx Authority mode.
 *
 * This function set region description alternate access control privilege bus master authority mode.
 *
 * \param[in] obj : pointer to MPU register instance
 * \param[in] regDescNum : Region Description number set
 * \param[in] masterNo : Select Master number
 *             - 0 : Bus Master0
 *             - 1 : Bus Master1
 *             - 2 : Bus Master2
 *             - 3 : Bus Master3
 * \param[in] aacPrivilegeMode : Configure Masterx Access Authority
 *             - 0 : R/W/X
 *             - 1 : R/X
 *             - 2 : R/W
 *             - 3 : same as user masterx
 * \return None
 *
 */
__attribute__((always_inline)) static inline void MpuReg_SetRegionDescAACPrivilegeAuthority(MpuRegType *obj,
                                                             uint8_t aacChnNum,
                                                             uint8_t masterNo,
                                                             uint8_t aacPrivilegeMode)
{
    uint32_t tmp = obj->AAC[aacChnNum];

    switch(masterNo)
    {
    case 0:
        tmp &= ~MPU_RGDAAC_M0SM_MASK;       /*!< AAC Bus Master0 Privilege mode */
        tmp |= (((uint32_t)((uint32_t)aacPrivilegeMode << MPU_RGDAAC_M0SM_SHIFT)) & MPU_RGDAAC_M0SM_MASK);
        obj->AAC[aacChnNum] = tmp;
        break;
    case 1:
        tmp &= ~MPU_RGDAAC_M1SM_MASK;       /*!< AAC Bus Master1 Privilege mode */
        tmp |= (((uint32_t)((uint32_t)aacPrivilegeMode << MPU_RGDAAC_M1SM_SHIFT)) & MPU_RGDAAC_M1SM_MASK);
        obj->AAC[aacChnNum] = tmp;
        break;
    case 2:
        tmp &= ~MPU_RGDAAC_M2SM_MASK;       /*!< AAC Bus Master2 Privilege mode */
        tmp |= (((uint32_t)((uint32_t)aacPrivilegeMode << MPU_RGDAAC_M2SM_SHIFT)) & MPU_RGDAAC_M2SM_MASK);
        obj->AAC[aacChnNum] = tmp;
        break;
    case 3:
        tmp &= ~MPU_RGDAAC_M3SM_MASK;       /*!< AAC Bus Master3 Privilege mode */
        tmp |= (((uint32_t)((uint32_t)aacPrivilegeMode << MPU_RGDAAC_M3SM_SHIFT)) & MPU_RGDAAC_M3SM_MASK);
        obj->AAC[aacChnNum] = tmp;
        break;
    default:
        break;
    }
}

/*! \brief Get Region Description Alternate Access Control Privilege Bus Masterx Authority mode.
 *
 * This function get region description alternate access control privilege bus master authority mode.
 *
 * \param[in] obj : pointer to MPU register instance
 * \param[in] regDescNum : Region Description number set
 * \param[in] masterNo : Select Master Num
 *             - 0 : Bus Master0
 *             - 1 : Bus Master1
 *             - 2 : Bus Master2
 *             - 3 : Bus Master3
 * \return Masterx Access Authority
 *             - 0 : R/W/X
 *             - 1 : R/X
 *             - 2 : R/W
 *             - 3 : same as user masterx
 *
 */
__attribute__((always_inline)) static inline uint8_t MpuReg_GetRegionDescAACPrivilegeAuthority(const MpuRegType *obj, uint8_t aacChnNum, uint8_t masterNo)
{
    switch(masterNo)
    {
    case 0:
        return ((obj->AAC[aacChnNum] & MPU_RGDAAC_M0SM_MASK) >> MPU_RGDAAC_M0SM_SHIFT); /*!< AAC Bus Master0 Privilege mode */
    case 1:
        return ((obj->AAC[aacChnNum] & MPU_RGDAAC_M1SM_MASK) >> MPU_RGDAAC_M1SM_SHIFT); /*!< AAC Bus Master1 Privilege mode */
    case 2:
        return ((obj->AAC[aacChnNum] & MPU_RGDAAC_M2SM_MASK) >> MPU_RGDAAC_M2SM_SHIFT); /*!< AAC Bus Master2 Privilege mode */
    case 3:
        return ((obj->AAC[aacChnNum] & MPU_RGDAAC_M3SM_MASK) >> MPU_RGDAAC_M3SM_SHIFT); /*!< AAC Bus Master3 Privilege mode */
    default:
        return MPU_RES_ERR;
    }
}

/*! \brief Set Evaluate Alternate Access Control if Processing include PID.
 *
 * This function set evaluate alternate access control if processing include Process Identification.
 *
 * \param[in] obj : pointer to MPU register instance
 * \param[in] regDescNum : Region Description number set
 * \param[in] masterNo : Select Master number
 *             - 0 : Bus Master0
 *             - 1 : Bus Master1
 * \param[in] aacPIDMode : Configure Evaluate Process
 *             - 0 : Evaluate processing do not include PID
 *             - 1 : Evaluate processing include PID
 * \return None
 *
 */
__attribute__((always_inline)) static inline void MpuReg_SetRegionDescAACPIDFlagEnable(MpuRegType *obj, uint8_t aacChnNum, uint8_t masterNo, uint8_t aacPIDMode)
{
    uint32_t tmp = obj->AAC[aacChnNum];
    
    switch(masterNo)
    {
    case 0:
        tmp &= ~MPU_RGDAAC_M0PE_MASK;       /*!< AAC Bus Master0 PID mode */
        tmp |= (((uint32_t)((uint32_t)aacPIDMode << MPU_RGDAAC_M0PE_SHIFT)) & MPU_RGDAAC_M0PE_MASK);
        obj->AAC[aacChnNum] = tmp;
        break;
    case 1:
        tmp &= ~MPU_RGDAAC_M1PE_MASK;       /*!< AAC Bus Master1 PID mode */
        tmp |= (((uint32_t)((uint32_t)aacPIDMode << MPU_RGDAAC_M1PE_SHIFT)) & MPU_RGDAAC_M1PE_MASK);
        obj->AAC[aacChnNum] = tmp;
        break;
    default:
        break;
    }
}

/*! \brief Get Evaluate Alternate Access Control Processing include PID.
 *
 * This function get evaluate alternate access control processing include Process Identification.
 *
 * \param[in] obj : pointer to MPU register instance
 * \param[in] regDescNum : Region Description number set
 * \param[in] masterNo : Select Master number
 *             - 0 : Bus Master0
 *             - 1 : Bus Master1
 * \return Evaluate Process
               - 0 : Evaluate processing do not include PID
 *             - 1 : Evaluate processing include PID
 *
 */
__attribute__((always_inline)) static inline uint8_t MpuReg_GetRegionDescAACPIDFlagEnableStatus(const MpuRegType *obj, uint8_t aacChnNum, uint8_t masterNo)
{
    switch(masterNo)
    {
    case 0:
        return ((obj->AAC[aacChnNum] & MPU_RGDAAC_M0PE_MASK) >> MPU_RGDAAC_M0PE_SHIFT); /*!< AAC Bus Master0 PID mode */
    case 1:
        return ((obj->AAC[aacChnNum] & MPU_RGDAAC_M0PE_MASK) >> MPU_RGDAAC_M0PE_SHIFT); /*!< AAC Bus Master1 PID mode */
    default:
        return MPU_RES_ERR;
    }
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _MPU_REG_H_ */
