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

#ifndef _AXBS_REG_H_
#define _AXBS_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the AXBS Registers
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

#define AXBS_MASTER_NUM            (8)

/* CSR Bit Fields */
#define AXBS_CSR_MERR7_MASK        (0x80000000u)
#define AXBS_CSR_MERR7_SHIFT       (31u)
#define AXBS_CSR_MERR7_WIDTH       (1u)
#define AXBS_CSR_MERR6_MASK        (0x40000000u)
#define AXBS_CSR_MERR6_SHIFT       (30u)
#define AXBS_CSR_MERR6_WIDTH       (1u)
#define AXBS_CSR_MERR5_MASK        (0x20000000u)
#define AXBS_CSR_MERR5_SHIFT       (29u)
#define AXBS_CSR_MERR5_WIDTH       (1u)
#define AXBS_CSR_MERR4_MASK        (0x10000000u)
#define AXBS_CSR_MERR4_SHIFT       (28u)
#define AXBS_CSR_MERR4_WIDTH       (1u)
#define AXBS_CSR_MERR3_MASK        (0x8000000u)
#define AXBS_CSR_MERR3_SHIFT       (27u)
#define AXBS_CSR_MERR3_WIDTH       (1u)
#define AXBS_CSR_MERR2_MASK        (0x4000000u)
#define AXBS_CSR_MERR2_SHIFT       (26u)
#define AXBS_CSR_MERR2_WIDTH       (1u)
#define AXBS_CSR_MERR1_MASK        (0x2000000u)
#define AXBS_CSR_MERR1_SHIFT       (25u)
#define AXBS_CSR_MERR1_WIDTH       (1u)
#define AXBS_CSR_MERR0_MASK        (0x1000000u)
#define AXBS_CSR_MERR0_SHIFT       (24u)
#define AXBS_CSR_MERR0_WIDTH       (1u)
#define AXBS_CSR_AHB_REG_VLD_MASK  (0x01u)
#define AXBS_CSR_AHB_REG_VLD_SHIFT (0u)
#define AXBS_CSR_AHB_REG_VLD_WIDTH (1u)

/* EAR Bit Fields */
#define AXBS_EAR_EADDR_MASK        (0xFFFFFFFFu)
#define AXBS_EAR_EADDR_SHIFT       (0u)
#define AXBS_EAR_EADDR_WIDTH       (32u)

/* EDR Bit Fields */
#define AXBS_EDR_EMN_MASK          (0xF000u)
#define AXBS_EDR_EMN_SHIFT         (12u)
#define AXBS_EDR_EMN_WIDTH         (4u)
#define AXBS_EDR_EATTR_MASK        (0xF0u)
#define AXBS_EDR_EATTR_SHIFT       (4u)
#define AXBS_EDR_EATTR_WIDTH       (4u)
#define AXBS_EDR_ERW_MASK          (0x01u)
#define AXBS_EDR_ERW_SHIFT         (0u)
#define AXBS_EDR_ERW_WIDTH         (1u)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief The definition of AHB registers
 */
typedef struct _AxbsRegType_
{
    volatile uint32_t CSR;          /*!< AXBS control/error status register, offset: 0x0 */
    uint32_t          RESERVED0[3]; /*!< Reserverd block, 0004H */
    struct
    {
        const volatile uint32_t EAR; /*!< Master n Error Address Register */
        const volatile uint32_t EDR; /*!< Master n Error Detail Register */
    } ERR[AXBS_MASTER_NUM];
} AxbsRegType;

/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Gets the AXBS master 0 Error
 *
 * This function gets the current AXBS master 0 Error.
 * Indicates a captured error in AXBS master0 interface.
 * This bit is set when the hardware detects an error and records the faulting address and attributes.
 * It is cleared by writing one to it.
 * If another error is captured at the exact same cycle as the write, the flag remains set,
 * and the latest error information is captured.
 *
 * \param[in] obj : pointer to AXBS register instance
 * \return AXBS master 0 Error
 *         - 0b : No error has occurred for AXBS master 0 interface.
 *         - 1b : An error has occurred for  AXBS master 0 interface.
 */
__attribute__((always_inline)) static inline uint8_t AxbsReg_GetCsrMErr0(const AxbsRegType *obj)
{
    return ((obj->CSR & AXBS_CSR_MERR0_MASK) >> AXBS_CSR_MERR0_SHIFT);
}

/*! \brief Sets the AXBS master 0 Error
 *
 * This function sets the AXBS master 0 Error.
 * Indicates a captured error in AXBS master0 interface.
 * This bit is set when the hardware detects an error and records the faulting address and attributes.
 * It is cleared by writing one to it.
 * If another error is captured at the exact same cycle as the write, the flag remains set,
 * and the latest error information is captured.
 *
 * \param[in] obj : pointer to AXBS register instance
 * \param[in] value : whether to clear the flag
 *                    - 0b : No effect
 *                    - 1b : Clear the error flag
 */
__attribute__((always_inline)) static inline void AxbsReg_SetCsrMErr0(AxbsRegType *obj, uint8_t value)
{
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    uint32_t tmp = obj->CSR & AXBS_CSR_AHB_REG_VLD_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AXBS_CSR_MERR0_SHIFT)) & AXBS_CSR_MERR0_MASK);
    obj->CSR = tmp;
}

/*! \brief Gets the AXBS master 1 Error
 *
 * This function gets the current AXBS master 1 Error.
 * Indicates a captured error in AXBS master1 interface.
 * This bit is set when the hardware detects an error and records the faulting address and attributes.
 * It is cleared by writing one to it.
 * If another error is captured at the exact same cycle as the write, the flag remains set,
 * and the latest error information is captured.
 *
 * \param[in] obj : pointer to AXBS register instance
 * \return AXBS master 1 Error
 *         - 0b : No error has occurred for AXBS master 1 interface.
 *         - 1b : An error has occurred for  AXBS master 1 interface.
 */
__attribute__((always_inline)) static inline uint8_t AxbsReg_GetCsrMErr1(const AxbsRegType *obj)
{
    return ((obj->CSR & AXBS_CSR_MERR1_MASK) >> AXBS_CSR_MERR1_SHIFT);
}

/*! \brief Sets the AXBS master 1 Error
 *
 * This function sets the AXBS master 1 Error.
 * Indicates a captured error in AXBS master1 interface.
 * This bit is set when the hardware detects an error and records the faulting address and attributes.
 * It is cleared by writing one to it.
 * If another error is captured at the exact same cycle as the write, the flag remains set,
 * and the latest error information is captured.
 *
 * \param[in] obj : pointer to AXBS register instance
 * \param[in] value : whether to clear the flag
 *                    - 0b : No effect
 *                    - 1b : Clear the error flag
 */
__attribute__((always_inline)) static inline void AxbsReg_SetCsrMErr1(AxbsRegType *obj, uint8_t value)
{
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    uint32_t tmp = obj->CSR & AXBS_CSR_AHB_REG_VLD_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AXBS_CSR_MERR1_SHIFT)) & AXBS_CSR_MERR1_MASK);
    obj->CSR = tmp;
}

/*! \brief Gets the AXBS master 2 Error
 *
 * This function gets the current AXBS master 2 Error.
 * Indicates a captured error in AXBS master2 interface.
 * This bit is set when the hardware detects an error and records the faulting address and attributes.
 * It is cleared by writing one to it.
 * If another error is captured at the exact same cycle as the write, the flag remains set,
 * and the latest error information is captured.
 *
 * \param[in] obj : pointer to AXBS register instance
 * \return AXBS master 2 Error
 *         - 0b : No error has occurred for AXBS master 2 interface.
 *         - 1b : An error has occurred for  AXBS master 2 interface.
 */
__attribute__((always_inline)) static inline uint8_t AxbsReg_GetCsrMErr2(const AxbsRegType *obj)
{
    return ((obj->CSR & AXBS_CSR_MERR2_MASK) >> AXBS_CSR_MERR2_SHIFT);
}

/*! \brief Sets the AXBS master 2 Error
 *
 * This function sets the AXBS master 2 Error.
 * Indicates a captured error in AXBS master2 interface.
 * This bit is set when the hardware detects an error and records the faulting address and attributes.
 * It is cleared by writing one to it.
 * If another error is captured at the exact same cycle as the write, the flag remains set,
 * and the latest error information is captured.
 *
 * \param[in] obj : pointer to AXBS register instance
 * \param[in] value : whether to clear the flag
 *                    - 0b : No effect
 *                    - 1b : Clear the error flag
 */
__attribute__((always_inline)) static inline void AxbsReg_SetCsrMErr2(AxbsRegType *obj, uint8_t value)
{
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    uint32_t tmp = obj->CSR & AXBS_CSR_AHB_REG_VLD_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AXBS_CSR_MERR2_SHIFT)) & AXBS_CSR_MERR2_MASK);
    obj->CSR = tmp;
}

/*! \brief Gets the AXBS master 3 Error
 *
 * This function gets the current AXBS master 3 Error.
 * Indicates a captured error in AXBS master3 interface.
 * This bit is set when the hardware detects an error and records the faulting address and attributes.
 * It is cleared by writing one to it.
 * If another error is captured at the exact same cycle as the write, the flag remains set,
 * and the latest error information is captured.
 *
 * \param[in] obj : pointer to AXBS register instance
 * \return AXBS master 3 Error
 *         - 0b : No error has occurred for AXBS master 3 interface.
 *         - 1b : An error has occurred for  AXBS master 3 interface.
 */
__attribute__((always_inline)) static inline uint8_t AxbsReg_GetCsrMErr3(const AxbsRegType *obj)
{
    return ((obj->CSR & AXBS_CSR_MERR3_MASK) >> AXBS_CSR_MERR3_SHIFT);
}

/*! \brief Sets the AXBS master 3 Error
 *
 * This function sets the AXBS master 3 Error.
 * Indicates a captured error in AXBS master3 interface.
 * This bit is set when the hardware detects an error and records the faulting address and attributes.
 * It is cleared by writing one to it.
 * If another error is captured at the exact same cycle as the write, the flag remains set,
 * and the latest error information is captured.
 *
 * \param[in] obj : pointer to AXBS register instance
 * \param[in] value : whether to clear the flag
 *                    - 0b : No effect
 *                    - 1b : Clear the error flag
 */
__attribute__((always_inline)) static inline void AxbsReg_SetCsrMErr3(AxbsRegType *obj, uint8_t value)
{
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    uint32_t tmp = obj->CSR & AXBS_CSR_AHB_REG_VLD_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AXBS_CSR_MERR3_SHIFT)) & AXBS_CSR_MERR3_MASK);
    obj->CSR = tmp;
}

/*! \brief Gets the AXBS master 4 Error
 *
 * This function gets the current AXBS master 4 Error.
 * Indicates a captured error in AXBS master4 interface.
 * This bit is set when the hardware detects an error and records the faulting address and attributes.
 * It is cleared by writing one to it.
 * If another error is captured at the exact same cycle as the write, the flag remains set,
 * and the latest error information is captured.
 *
 * \param[in] obj : pointer to AXBS register instance
 * \return AXBS master 4 Error
 *         - 0b : No error has occurred for AXBS master 4 interface.
 *         - 1b : An error has occurred for  AXBS master 4 interface.
 */
__attribute__((always_inline)) static inline uint8_t AxbsReg_GetCsrMErr4(const AxbsRegType *obj)
{
    return ((obj->CSR & AXBS_CSR_MERR4_MASK) >> AXBS_CSR_MERR4_SHIFT);
}

/*! \brief Sets the AXBS master 4 Error
 *
 * This function sets the AXBS master 4 Error.
 * Indicates a captured error in AXBS master4 interface.
 * This bit is set when the hardware detects an error and records the faulting address and attributes.
 * It is cleared by writing one to it.
 * If another error is captured at the exact same cycle as the write, the flag remains set,
 * and the latest error information is captured.
 *
 * \param[in] obj : pointer to AXBS register instance
 * \param[in] value : whether to clear the flag
 *                    - 0b : No effect
 *                    - 1b : Clear the error flag
 */
__attribute__((always_inline)) static inline void AxbsReg_SetCsrMErr4(AxbsRegType *obj, uint8_t value)
{
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    uint32_t tmp = obj->CSR & AXBS_CSR_AHB_REG_VLD_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AXBS_CSR_MERR4_SHIFT)) & AXBS_CSR_MERR4_MASK);
    obj->CSR = tmp;
}

/*! \brief Gets the AXBS master 5 Error
 *
 * This function gets the current AXBS master 5 Error.
 * Indicates a captured error in AXBS master5 interface.
 * This bit is set when the hardware detects an error and records the faulting address and attributes.
 * It is cleared by writing one to it.
 * If another error is captured at the exact same cycle as the write, the flag remains set,
 * and the latest error information is captured.
 *
 * \param[in] obj : pointer to AXBS register instance
 * \return AXBS master 5 Error
 *         - 0b : No error has occurred for AXBS master 5 interface.
 *         - 1b : An error has occurred for  AXBS master 5 interface.
 */
__attribute__((always_inline)) static inline uint8_t AxbsReg_GetCsrMErr5(const AxbsRegType *obj)
{
    return ((obj->CSR & AXBS_CSR_MERR5_MASK) >> AXBS_CSR_MERR5_SHIFT);
}

/*! \brief Sets the AXBS master 5 Error
 *
 * This function sets the AXBS master 5 Error.
 * Indicates a captured error in AXBS master5 interface.
 * This bit is set when the hardware detects an error and records the faulting address and attributes.
 * It is cleared by writing one to it.
 * If another error is captured at the exact same cycle as the write, the flag remains set,
 * and the latest error information is captured.
 *
 * \param[in] obj : pointer to AXBS register instance
 * \param[in] value : whether to clear the flag
 *                    - 0b : No effect
 *                    - 1b : Clear the error flag
 */
__attribute__((always_inline)) static inline void AxbsReg_SetCsrMErr5(AxbsRegType *obj, uint8_t value)
{
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    uint32_t tmp = obj->CSR & AXBS_CSR_AHB_REG_VLD_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AXBS_CSR_MERR5_SHIFT)) & AXBS_CSR_MERR5_MASK);
    obj->CSR = tmp;
}

/*! \brief Gets the AXBS master 6 Error
 *
 * This function gets the current AXBS master 6 Error.
 * Indicates a captured error in AXBS master6 interface.
 * This bit is set when the hardware detects an error and records the faulting address and attributes.
 * It is cleared by writing one to it.
 * If another error is captured at the exact same cycle as the write, the flag remains set,
 * and the latest error information is captured.
 *
 * \param[in] obj : pointer to AXBS register instance
 * \return AXBS master 6 Error
 *         - 0b : No error has occurred for AXBS master 6 interface.
 *         - 1b : An error has occurred for  AXBS master 6 interface.
 */
__attribute__((always_inline)) static inline uint8_t AxbsReg_GetCsrMErr6(const AxbsRegType *obj)
{
    return ((obj->CSR & AXBS_CSR_MERR6_MASK) >> AXBS_CSR_MERR6_SHIFT);
}

/*! \brief Sets the AXBS master 6 Error
 *
 * This function sets the AXBS master 6 Error.
 * Indicates a captured error in AXBS master6 interface.
 * This bit is set when the hardware detects an error and records the faulting address and attributes.
 * It is cleared by writing one to it.
 * If another error is captured at the exact same cycle as the write, the flag remains set,
 * and the latest error information is captured.
 *
 * \param[in] obj : pointer to AXBS register instance
 * \param[in] value : whether to clear the flag
 *                    - 0b : No effect
 *                    - 1b : Clear the error flag
 */
__attribute__((always_inline)) static inline void AxbsReg_SetCsrMErr6(AxbsRegType *obj, uint8_t value)
{
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    uint32_t tmp = obj->CSR & AXBS_CSR_AHB_REG_VLD_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AXBS_CSR_MERR6_SHIFT)) & AXBS_CSR_MERR6_MASK);
    obj->CSR = tmp;
}

/*! \brief Gets the AXBS master 7 Error
 *
 * This function gets the current AXBS master 7 Error.
 * Indicates a captured error in AXBS master7 interface.
 * This bit is set when the hardware detects an error and records the faulting address and attributes.
 * It is cleared by writing one to it.
 * If another error is captured at the exact same cycle as the write, the flag remains set,
 * and the latest error information is captured.
 *
 * \param[in] obj : pointer to AXBS register instance
 * \return AXBS master 7 Error
 *         - 0b : No error has occurred for AXBS master 7 interface.
 *         - 1b : An error has occurred for  AXBS master 7 interface.
 */
__attribute__((always_inline)) static inline uint8_t AxbsReg_GetCsrMErr7(const AxbsRegType *obj)
{
    return ((obj->CSR & AXBS_CSR_MERR7_MASK) >> AXBS_CSR_MERR7_SHIFT);
}

/*! \brief Sets the AXBS master 7 Error
 *
 * This function sets the AXBS master 7 Error.
 * Indicates a captured error in AXBS master7 interface.
 * This bit is set when the hardware detects an error and records the faulting address and attributes.
 * It is cleared by writing one to it.
 * If another error is captured at the exact same cycle as the write, the flag remains set,
 * and the latest error information is captured.
 *
 * \param[in] obj : pointer to AXBS register instance
 * \param[in] value : whether to clear the flag
 *                    - 0b : No effect
 *                    - 1b : Clear the error flag
 */
__attribute__((always_inline)) static inline void AxbsReg_SetCsrMErr7(AxbsRegType *obj, uint8_t value)
{
    /* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
    uint32_t tmp = obj->CSR & AXBS_CSR_AHB_REG_VLD_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AXBS_CSR_MERR7_SHIFT)) & AXBS_CSR_MERR7_MASK);
    obj->CSR = tmp;
}

/*! \brief Gets the AXBS status regsiter module enable flag
 *
 * This function gets the current AXBS status regsiter module enable flag
 *
 * \param[in] obj : pointer to AXBS register instance
 * \return the current AXBS status regsiter module enable flag
 */
__attribute__((always_inline)) static inline uint8_t AxbsReg_GetCsrRegVld(const AxbsRegType *obj)
{
    return ((obj->CSR & AXBS_CSR_AHB_REG_VLD_MASK) >> AXBS_CSR_AHB_REG_VLD_SHIFT);
}

/*! \brief Sets the AXBS status regsiter module enable flag
 *
 * This function sets the AXBS status regsiter module enable flag.
 *
 * \param[in] obj : pointer to AXBS register instance
 * \param[in] value : the value of AXBS status regsiter module enable flag
 */
__attribute__((always_inline)) static inline void AxbsReg_SetCsrRegVld(AxbsRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->CSR;

    tmp &= ~AXBS_CSR_AHB_REG_VLD_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << AXBS_CSR_AHB_REG_VLD_SHIFT)) & AXBS_CSR_AHB_REG_VLD_MASK);
    obj->CSR = tmp;
}

/*! \brief Gets the Error Address
 *
 * This function gets the current Error Address.
 * Indicates the reference address from master 0 that generated the access erro
 *
 * \param[in] obj : pointer to AXBS register instance
 * \param[in] master : the master index
 * \return Error Address
 */
__attribute__((always_inline)) static inline uint32_t AxbsReg_GetEarEAddr(const AxbsRegType *obj, uint8_t master)
{
    return ((obj->ERR[master].EAR & AXBS_EAR_EADDR_MASK) >> AXBS_EAR_EADDR_SHIFT);
}

/*! \brief Gets the Error Master Number
 *
 * This function gets the current Error Master Number.
 * Indicates the bus master that generated the access error
 *
 * \param[in] obj : pointer to AXBS register instance
 * \param[in] master : the master index
 * \return Error Master Number
 */
__attribute__((always_inline)) static inline uint8_t AxbsReg_GetEdrEmn(const AxbsRegType *obj, uint8_t master)
{
    return ((obj->ERR[master].EDR & AXBS_EDR_EMN_MASK) >> AXBS_EDR_EMN_SHIFT);
}

/*! \brief Gets the Error Attributes
 *
 * This function gets the current Error Attributes.
 * Indicates hprot[3:0] of error access
 *
 * \param[in] obj : pointer to AXBS register instance
 * \param[in] master : the master index
 * \return Error Attributes
 */
__attribute__((always_inline)) static inline uint8_t AxbsReg_GetEdrEAttr(const AxbsRegType *obj, uint8_t master)
{
    return ((obj->ERR[master].EDR & AXBS_EDR_EATTR_MASK) >> AXBS_EDR_EATTR_SHIFT);
}

/*! \brief Gets the Error Read/Write
 *
 * This function gets the current Error Read/Write.
 * Indicates the access type of the faulting reference.
 *
 * \param[in] obj : pointer to AXBS register instance
 * \param[in] master : the master index
 * \return Error Read/Write
 *         - 0b : Read
 *         - 1b : Write
 */
__attribute__((always_inline)) static inline uint8_t AxbsReg_GetEdrErw(const AxbsRegType *obj, uint8_t master)
{
    return ((obj->ERR[master].EDR & AXBS_EDR_ERW_MASK) >> AXBS_EDR_ERW_SHIFT);
}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _AXBS_REG_H_ */
