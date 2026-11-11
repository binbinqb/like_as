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

#ifndef _PDB_REG_H_
#define _PDB_REG_H_

/*! \brief Contains public interface to various functions related
 *         to the PDB (Programmable Delay Block) Registers
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

/* PDB - Size of Registers Arrays */
#define PDB_CH_COUNT                        (3u)
#define PDB_DLY_COUNT                       (8u)
#define PDB_PODLY_COUNT                     (1u)

/* SC Bit Fields */
#define PDB_SC_LDMOD_MASK                   (0xC0000u)
#define PDB_SC_LDMOD_SHIFT                  (18u)
#define PDB_SC_LDMOD_WIDTH                  (2u)
#define PDB_SC_PDBEIE_MASK                  (0x20000u)
#define PDB_SC_PDBEIE_SHIFT                 (17u)
#define PDB_SC_PDBEIE_WIDTH                 (1u)
#define PDB_SC_SWTRIG_MASK                  (0x10000u)
#define PDB_SC_SWTRIG_SHIFT                 (16u)
#define PDB_SC_SWTRIG_WIDTH                 (1u)
#define PDB_SC_DMAEN_MASK                   (0x8000u)
#define PDB_SC_DMAEN_SHIFT                  (15u)
#define PDB_SC_DMAEN_WIDTH                  (1u)
#define PDB_SC_PRESCALER_MASK               (0x7000u)
#define PDB_SC_PRESCALER_SHIFT              (12u)
#define PDB_SC_PRESCALER_WIDTH              (3u)
#define PDB_SC_TRGSEL_MASK                  (0xF00u)
#define PDB_SC_TRGSEL_SHIFT                 (8u)
#define PDB_SC_TRGSEL_WIDTH                 (4u)
#define PDB_SC_PDBEN_MASK                   (0x80u)
#define PDB_SC_PDBEN_SHIFT                  (7u)
#define PDB_SC_PDBEN_WIDTH                  (1u)
#define PDB_SC_PDBIF_MASK                   (0x40u)
#define PDB_SC_PDBIF_SHIFT                  (6u)
#define PDB_SC_PDBIF_WIDTH                  (1u)
#define PDB_SC_PDBIE_MASK                   (0x20u)
#define PDB_SC_PDBIE_SHIFT                  (5u)
#define PDB_SC_PDBIE_WIDTH                  (1u)
#define PDB_SC_MULT_MASK                    (0xCu)
#define PDB_SC_MULT_SHIFT                   (2u)
#define PDB_SC_MULT_WIDTH                   (2u)
#define PDB_SC_CONT_MASK                    (0x2u)
#define PDB_SC_CONT_SHIFT                   (1u)
#define PDB_SC_CONT_WIDTH                   (1u)
#define PDB_SC_LDOK_MASK                    (0x1u)
#define PDB_SC_LDOK_SHIFT                   (0u)
#define PDB_SC_LDOK_WIDTH                   (1u)

/* MOD Bit Fields */
#define PDB_MOD_MOD_MASK                    (0xFFFFu)
#define PDB_MOD_MOD_SHIFT                   (0u)
#define PDB_MOD_MOD_WIDTH                   (16u)

/* CNT Bit Fields */
#define PDB_CNT_CNT_MASK                    (0xFFFFu)
#define PDB_CNT_CNT_SHIFT                   (0u)
#define PDB_CNT_CNT_WIDTH                   (16u)

/* IDLY Bit Fields */
#define PDB_IDLY_IDLY_MASK                  (0xFFFFu)
#define PDB_IDLY_IDLY_SHIFT                 (0u)
#define PDB_IDLY_IDLY_WIDTH                 (16u)

/* CHnC1 Bit Fields */
#define PDB_CHnC1_BB_MASK                   (0xFF0000u)
#define PDB_CHnC1_BB_SHIFT                  (16u)
#define PDB_CHnC1_BB_WIDTH                  (8u)
#define PDB_CHnC1_TOS_MASK                  (0xFF00u)
#define PDB_CHnC1_TOS_SHIFT                 (8u)
#define PDB_CHnC1_TOS_WIDTH                 (8u)
#define PDB_CHnC1_EN_MASK                   (0xFFu)
#define PDB_CHnC1_EN_SHIFT                  (0u)
#define PDB_CHnC1_EN_WIDTH                  (8u)

/* CHnS Bit Fields */
#define PDB_CHnS_CF_MASK                    (0xFF0000u)
#define PDB_CHnS_CF_SHIFT                   (16u)
#define PDB_CHnS_CF_WIDTH                   (8u)
#define PDB_CHnS_ERR_MASK                   (0xFFu)
#define PDB_CHnS_ERR_SHIFT                  (0u)
#define PDB_CHnS_ERR_WIDTH                  (8u)

/* CHnDLY Bit Fields */
#define PDB_CHnDLY_DLY_MASK                 (0xFFFFu)
#define PDB_CHnDLY_DLY_SHIFT                (0u)
#define PDB_CHnDLY_DLY_WIDTH                (16u)

/* POEN Bit Fields */
#define PDB_POEN_POEN_MASK                  (0xFFu)
#define PDB_POEN_POEN_SHIFT                 (0u)
#define PDB_POEN_POEN_WIDTH                 (8u)

/* POnDLY Bit Fields */
#define PDB_POnDLY_DLY1_MASK                (0xFFFF0000u)
#define PDB_POnDLY_DLY1_SHIFT               (16u)
#define PDB_POnDLY_DLY1_WIDTH               (16u)
#define PDB_POnDLY_DLY2_MASK                (0xFFFFu)
#define PDB_POnDLY_DLY2_SHIFT               (0u)
#define PDB_POnDLY_DLY2_WIDTH               (16u)

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*! \brief The definition of PDB registers
 */
typedef struct _PdbRegType_
{
    volatile uint32_t SC;                      /*!< status and control register, offset: 0000H */
    volatile uint32_t MOD;                     /*!< modulus register, offset: 0004H */
    volatile uint32_t CNT;                     /*!< counter register, offset: 0008H */
    volatile uint32_t IDLY;                    /*!< interrupt delay register, offset: 000CH */
    struct {
        volatile uint32_t C1;                  /*!< channel n control register, offset: 0010H + n*0028H */
        volatile uint32_t S;                   /*!< channel n status register, offset: 0014H + n*0028H*/
        volatile uint32_t DLY[PDB_DLY_COUNT];  /*!< channel n delay register, offset: 0018H + n*0028H*/
    }CH[PDB_CH_COUNT];
    uint32_t RESERVED[66];                     /*!< Reserved register, offset: 0088H */
    volatile uint32_t POEN;                    /*!< pulse out enable register, offset: 0190H */
    volatile uint32_t PODLY[PDB_PODLY_COUNT];  /*!< pulse out delay register, offset: 0194H */

} PdbRegType;


/*******************************************************************************
 * the globals
 ******************************************************************************/

/*******************************************************************************
 * the function prototypes
 ******************************************************************************/

/*! \brief Get the current PDB LDMOD register configuration
 *
 * This function gets the current PDB LDMOD register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to PDB register instance
 * \return the current PDB LDMOD register configuration.
 * - 00b: The internal registers are loaded with the values from their buffers, immediately after 1 is written to LDOK.
 * - 01b: The internal registers are loaded with the values from their buffers when the PDB counter (CNT) = MOD + 1 CNT delay elapsed, after 1 is written to LDOK.
 * - 10b: The internal registers are loaded with the values from their buffers when a trigger input event is detected, after 1 is written to LDOK.
 * - 11b: The internal registers are loaded with the values from their buffers when either the PDB counter (CNT) = MOD + 1 CNT delay elapsed, or a trigger 
 *        input event is detected, after 1 is written to LDOK.
 */
__attribute__((always_inline)) static inline uint8_t PdbReg_GetLdmodReg(const PdbRegType *obj)
{
    return ((obj->SC & PDB_SC_LDMOD_MASK) >> PDB_SC_LDMOD_SHIFT);
}

/*! \brief Set PDB LDMODR configuration
 *
 * This function writes new configuration to PDB LDMODR register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj  : pointer to PDB register instance
 * \param[in] value : expected PDB LDMODR register configuration
 * - 00b: The internal registers are loaded with the values from their buffers, immediately after 1 is written to LDOK.
 * - 01b: The internal registers are loaded with the values from their buffers when the PDB counter (CNT) = MOD + 1 CNT delay elapsed, after 1 is written to LDOK.
 * - 10b: The internal registers are loaded with the values from their buffers when a trigger input event is detected, after 1 is written to LDOK.
 * - 11b: The internal registers are loaded with the values from their buffers when either the PDB counter (CNT) = MOD + 1 CNT delay elapsed, or a trigger 
 *        input event is detected, after 1 is written to LDOK. 
 */
__attribute__((always_inline)) static inline void PdbReg_SetLdmodReg(PdbRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SC;

    tmp &= ~PDB_SC_LDMOD_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PDB_SC_LDMOD_SHIFT)) & PDB_SC_LDMOD_MASK);
    obj->SC = tmp;
}

/*! \brief Get the current PDB PDBEIE register configuration
 *
 * This function gets the current PDB PDBEIE register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to PDB register instance
 * \return the current PDB PDBEIE register configuration.
 * - 0b: PDB sequence error interrupt disabled.
 * - 1b: PDB sequence error interrupt enabled.
 */
__attribute__((always_inline)) static inline uint8_t PdbReg_GetPdbeieReg(const PdbRegType *obj)
{
    return ((obj->SC & PDB_SC_PDBEIE_MASK) >> PDB_SC_PDBEIE_SHIFT);
}

/*! \brief Set PDB PDBEIE configuration
 *
 * This function writes new configuration to PDB PDBEIE register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj  : pointer to PDB register instance
 * \param[in] value : expected PDB PDBEIE register configuration
 * - 0b: PDB sequence error interrupt disabled.
 * - 1b: PDB sequence error interrupt enabled.
 */
__attribute__((always_inline)) static inline void PdbReg_SetPdbeieReg(PdbRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SC;

    tmp &= ~PDB_SC_PDBEIE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PDB_SC_PDBEIE_SHIFT)) & PDB_SC_PDBEIE_MASK);
    obj->SC = tmp;
}

/*! \brief Software Trigger
 *
 * When PDB is enabled and the software trigger is selected as the trigger input source,
 * writing 1 to SWTRIG resets and restarts the counter.
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj  : pointer to PDB register instance
 */
__attribute__((always_inline)) static inline void PdbReg_SwtrigReg(PdbRegType *obj)
{
    uint32_t tmp = obj->SC;

    tmp &= ~PDB_SC_SWTRIG_MASK;
    tmp &= ~PDB_SC_LDOK_MASK;
    tmp |= (((uint32_t)(((uint32_t)(1u)) << PDB_SC_SWTRIG_SHIFT)) & PDB_SC_SWTRIG_MASK);
    obj->SC = tmp;
}

/*! \brief Get the current PDB DMAEN register configuration
 *
 * This function gets the current PDB DMAEN register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to PDB register instance
 * \return the current PDB DMAEN register configuration.
 * - 0b: DMA disabled.
 * - 1b: DMA enabled.
 */
__attribute__((always_inline)) static inline uint8_t PdbReg_GetDmaenReg(const PdbRegType *obj)
{
    return ((obj->SC & PDB_SC_PDBEIE_MASK) >> PDB_SC_PDBEIE_SHIFT);
}

/*! \brief Set PDB DMAEN configuration
 *
 * This function writes new configuration to PDB DMAEN register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj  : pointer to PDB register instance
 * \param[in] value : expected PDB DMAEN register configuration
 * - 0b: DMA disabled.
 * - 1b: DMA enabled. 
 */
__attribute__((always_inline)) static inline void PdbReg_SetDmaenReg(PdbRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SC;

    tmp &= ~PDB_SC_DMAEN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PDB_SC_DMAEN_SHIFT)) & PDB_SC_DMAEN_MASK);
    obj->SC = tmp;
}

/*! \brief Get the current PDB PRESCALER register configuration
 *
 * This function gets the current PDB PRESCALER register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to PDB register instance
 * \return the current PDB PRESCALER register configuration.
 * - 000b: Counting uses the peripheral clock divided by MULT (the multiplication factor).
 * - 001b: Counting uses the peripheral clock divided by 2 x MULT (the multiplication factor).
 * - 010b: Counting uses the peripheral clock divided by 4 x MULT (the multiplication factor).
 * - 011b: Counting uses the peripheral clock divided by 8 x MULT (the multiplication factor).
 * - 100b: Counting uses the peripheral clock divided by 16 x MULT (the multiplication factor).
 * - 101b: Counting uses the peripheral clock divided by 32 x MULT (the multiplication factor).
 * - 110b: Counting uses the peripheral clock divided by 64 x MULT (the multiplication factor).
 * - 111b: Counting uses the peripheral clock divided by 128 x MULT (the multiplication factor). 
 */
__attribute__((always_inline)) static inline uint8_t PdbReg_GetPrescalerReg(const PdbRegType *obj)
{
    return ((obj->SC & PDB_SC_PRESCALER_MASK) >> PDB_SC_PRESCALER_SHIFT);
}

/*! \brief Set PDB PRESCALER configuration
 *
 * This function writes new configuration to PDB PRESCALER register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj  : pointer to PDB register instance
 * \param[in] value : expected PDB PRESCALER register configuration
 * - 000b: Counting uses the peripheral clock divided by MULT (the multiplication factor).
 * - 001b: Counting uses the peripheral clock divided by 2 x MULT (the multiplication factor).
 * - 010b: Counting uses the peripheral clock divided by 4 x MULT (the multiplication factor).
 * - 011b: Counting uses the peripheral clock divided by 8 x MULT (the multiplication factor).
 * - 100b: Counting uses the peripheral clock divided by 16 x MULT (the multiplication factor).
 * - 101b: Counting uses the peripheral clock divided by 32 x MULT (the multiplication factor).
 * - 110b: Counting uses the peripheral clock divided by 64 x MULT (the multiplication factor).
 * - 111b: Counting uses the peripheral clock divided by 128 x MULT (the multiplication factor). 
 */
__attribute__((always_inline)) static inline void PdbReg_SetPrescalerReg(PdbRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SC;

    tmp &= ~PDB_SC_PRESCALER_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PDB_SC_PRESCALER_SHIFT)) & PDB_SC_PRESCALER_MASK);
    obj->SC = tmp;
}

/*! \brief Get the current PDB TRGSEL register configuration
 *
 * This function gets the current PDB TRGSEL register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to PDB register instance
 * \return the current PDB TRGSEL register configuration.
 * - 0000b: Trigger-In 0 is selected.
 * - 0001b: Trigger-In 1 is selected.
 * - 0010b: Trigger-In 2 is selected.
 * - 0011b: Trigger-In 3 is selected.
 * - 0100b: Trigger-In 4 is selected.
 * - 0101b: Trigger-In 5 is selected.
 * - 0110b: Trigger-In 6 is selected.
 * - 0111b: Trigger-In 7 is selected.
 * - 1000b: Trigger-In 8 is selected.
 * - 1001b: Trigger-In 9 is selected.
 * - 1010b: Trigger-In 10 is selected.
 * - 1011b: Trigger-In 11 is selected.
 * - 1100b: Trigger-In 12 is selected.
 * - 1101b: Trigger-In 13 is selected.
 * - 1110b: Trigger-In 14 is selected.
 * - 1111b: Software trigger is selected. 
 */
__attribute__((always_inline)) static inline uint8_t PdbReg_GetTrgselReg(const PdbRegType *obj)
{
    return ((obj->SC & PDB_SC_TRGSEL_MASK) >> PDB_SC_TRGSEL_SHIFT);
}

/*! \brief Set PDB TRGSEL configuration
 *
 * This function writes new configuration to PDB TRGSEL register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj  : pointer to PDB register instance
 * \param[in] value : expected PDB TRGSEL register configuration
 * - 0000b: Trigger-In 0 is selected.
 * - 0001b: Trigger-In 1 is selected.
 * - 0010b: Trigger-In 2 is selected.
 * - 0011b: Trigger-In 3 is selected.
 * - 0100b: Trigger-In 4 is selected.
 * - 0101b: Trigger-In 5 is selected.
 * - 0110b: Trigger-In 6 is selected.
 * - 0111b: Trigger-In 7 is selected.
 * - 1000b: Trigger-In 8 is selected.
 * - 1001b: Trigger-In 9 is selected.
 * - 1010b: Trigger-In 10 is selected.
 * - 1011b: Trigger-In 11 is selected.
 * - 1100b: Trigger-In 12 is selected.
 * - 1101b: Trigger-In 13 is selected.
 * - 1110b: Trigger-In 14 is selected.
 * - 1111b: Software trigger is selected.  
 */
__attribute__((always_inline)) static inline void PdbReg_SetTrgselReg(PdbRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SC;

    tmp &= ~PDB_SC_TRGSEL_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PDB_SC_TRGSEL_SHIFT)) & PDB_SC_TRGSEL_MASK);
    obj->SC = tmp;
}

/*! \brief Get the current PDB PDBEN register configuration
 *
 * This function gets the current PDB PDBEN register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to PDB register instance
 * \return the current PDB PDBEN register configuration.
 * - 0b: PDB disabled. Counter is off.
 * - 1b: PDB enabled. 
 */
__attribute__((always_inline)) static inline uint8_t PdbReg_GetPdbenReg(const PdbRegType *obj)
{
    return ((obj->SC & PDB_SC_PDBEN_MASK) >> PDB_SC_PDBEN_SHIFT);
}

/*! \brief Set PDB PDBEN configuration
 *
 * This function writes new configuration to PDB PDBEN register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj  : pointer to PDB register instance
 * \param[in] value : expected PDB PDBEN register configuration
 * - 0b: PDB disabled. Counter is off.
 * - 1b: PDB enabled.  
 */
__attribute__((always_inline)) static inline void PdbReg_SetPdbenReg(PdbRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SC;

    tmp &= ~PDB_SC_PDBEN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PDB_SC_PDBEN_SHIFT)) & PDB_SC_PDBEN_MASK);
    obj->SC = tmp;
}

/*! \brief Get the current PDB PDBIF register configuration
 *
 * This function gets the current PDB PDBIF register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to PDB register instance
 * \return the current PDB PDBEN register configuration.
 */
__attribute__((always_inline)) static inline uint8_t PdbReg_GetPdbifReg(const PdbRegType *obj)
{
    return ((obj->SC & PDB_SC_PDBIF_MASK) >> PDB_SC_PDBIF_SHIFT);
}

/*! \brief Clear PDB PDBIF
 *
 * This function clear PDB PDBIF register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 * Write 0 to clear PDBIF.
 * Writing 1 to PDBIF has no effect. 
 *
 * \param[in] obj  : pointer to PDB register instance
 */
__attribute__((always_inline)) static inline void PdbReg_ClrPdbifReg(PdbRegType *obj)
{
    uint32_t tmp = obj->SC;

    tmp &= ~PDB_SC_PDBIF_MASK;
    obj->SC = tmp;
    (void)(obj->SC);
}

/*! \brief Get the current PDB PDBIE register configuration
 *
 * This function gets the current PDB PDBIE register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to PDB register instance
 * \return the current PDB PDBIE register configuration.
 * - 0b: PDB interrupt disabled.
 * - 1b: PDB interrupt enabled. 
 */
__attribute__((always_inline)) static inline uint8_t PdbReg_GetPdbieReg(const PdbRegType *obj)
{
    return ((obj->SC & PDB_SC_PDBIE_MASK) >> PDB_SC_PDBIE_SHIFT);
}

/*! \brief Set PDB PDBIE configuration
 *
 * This function writes new configuration to PDB PDBIE register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj  : pointer to PDB register instance
 * \param[in] value : expected PDB PDBIE register configuration
 * - 0b: PDB interrupt disabled.
 * - 1b: PDB interrupt enabled.  
 */
__attribute__((always_inline)) static inline void PdbReg_SetPdbieReg(PdbRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SC;

    tmp &= ~PDB_SC_PDBIE_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PDB_SC_PDBIE_SHIFT)) & PDB_SC_PDBIE_MASK);
    obj->SC = tmp;
}

/*! \brief Get the current PDB MULT register configuration
 *
 * This function gets the current PDB MULT register configuration.
 * If data size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj : pointer to PDB register instance
 * \return the current PDB MULT register configuration.
 * - 00b: Multiplication factor is 1.
 * - 01b: Multiplication factor is 10.
 * - 10b: Multiplication factor is 20.
 * - 11b: Multiplication factor is 40. 
 */
__attribute__((always_inline)) static inline uint8_t PdbReg_GetMultReg(const PdbRegType *obj)
{
    return ((obj->SC & PDB_SC_MULT_MASK) >> PDB_SC_MULT_SHIFT);
}

/*! \brief Set PDB MULT configuration
 *
 * This function writes new configuration to PDB MULT register
 * If configuration size is less than 32 bits, the least significant bits are used for
 * the correct value.
 *
 * \param[in] obj  : pointer to PDB register instance
 * \param[in] value : expected PDB MULT register configuration
 * - 00b: Multiplication factor is 1.
 * - 01b: Multiplication factor is 10.
 * - 10b: Multiplication factor is 20.
 * - 11b: Multiplication factor is 40.  
 */
__attribute__((always_inline)) static inline void PdbReg_SetMultReg(PdbRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SC;

    tmp &= ~PDB_SC_MULT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PDB_SC_MULT_SHIFT)) & PDB_SC_MULT_MASK);
    obj->SC = tmp;
}

/*! \brief Get the current PDB CONT register configuration
 *
 * This function gets the current PDB CONT register configuration.
 * If data size is less than 32 bits, the least significant bits are used for the correct value.
 *
 * \param[in] obj : pointer to PDB register instance
 * \return the current PDB CONT register configuration.
 * - 0b: PDB operation in One-Shot mode
 * - 1b: PDB operation in Continuous mode
 */
__attribute__((always_inline)) static inline uint8_t PdbReg_GetContReg(const PdbRegType *obj)
{
    return ((obj->SC & PDB_SC_CONT_MASK) >> PDB_SC_CONT_SHIFT);
}

/*! \brief Set PDB CONT configuration
 *
 * This function writes new configuration to PDB CONT register
 * If configuration size is less than 32 bits, the least significant bits are used for the correct value.
 *
 * \param[in] obj  : pointer to PDB register instance
 * \param[in] value : expected PDB CONT register configuration
 * - 0b: PDB operation in One-Shot mode
 * - 1b: PDB operation in Continuous mode 
 */
__attribute__((always_inline)) static inline void PdbReg_SetContReg(PdbRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->SC;

    tmp &= ~PDB_SC_CONT_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PDB_SC_CONT_SHIFT)) & PDB_SC_CONT_MASK);
    obj->SC = tmp;
}

/*! \brief Get the current PDB LDOK state
 *
 * This function gets the current PDB LDOK state.
 * If data size is less than 32 bits, the least significant bits are used for the correct value.
 *
 * \param[in] obj : pointer to PDB register instance
 * \return the current PDB LDOK register configuration.
 */
__attribute__((always_inline)) static inline uint8_t PdbReg_GetLdokReg(const PdbRegType *obj)
{
    return ((obj->SC & PDB_SC_LDOK_MASK) >> PDB_SC_LDOK_SHIFT);
}

/*! \brief Start PDB Load
 *
 * This function writing 1 to LDOK bit updates the MOD, IDLY, CHnDLYm, and POyDLY registers.
 * If configuration size is less than 32 bits, the least significant bits are used for the correct value.
 * Writing 1 to LDOK bit updates the MOD, IDLY, CHnDLYm, and POyDLY registers with the values previously written to their internal buffers (and stored there). 
 *      The new values of MOD, IDLY, CHnDLYm, and POyDLY registers will take effect according to the setting of the LDMOD field (Load Mode Select).
 * Before 1 is written to the LDOK field, the values in the internal buffers of these registers are not effective.
 * LDOK can be written only when PDBEN is set, or LDOK can be written at the same time when PDBEN is written to 1.
 * LDOK is automatically cleared when the values in the internal buffers are loaded into the registers or when PDBEN bit (PDB Enable) is cleared.
 * Writing 0 to LDOK has no effect.
 * \param[in] obj  : pointer to PDB register instance
 */
__attribute__((always_inline)) static inline void PdbReg_StartLoadReg(PdbRegType *obj)
{
    uint32_t tmp = obj->SC;

    tmp &= ~PDB_SC_LDOK_MASK;
    tmp |= (((uint32_t)(((uint32_t)(1u)) << PDB_SC_LDOK_SHIFT)) & PDB_SC_LDOK_MASK);
    obj->SC = tmp;
}

/*! \brief Get the current PDB MOD register configuration
 *
 * This function gets the current PDB MOD register configuration.
 * If data size is less than 32 bits, the least significant bits are used for the correct value.
 * 
 * \param[in] obj : pointer to PDB register instance
 * \return the current PDB MOD register configuration.
 * Specifies the period of the counter. When the counter reaches this value, it will be reset back to zero. 
 * If the PDB is in Continuous mode, the count begins anew.
 * Reading this field returns the value of the internal register that is effective for the current cycle of PDB. 
 */
__attribute__((always_inline)) static inline uint16_t PdbReg_GetModReg(const PdbRegType *obj)
{
    return ((obj->MOD & PDB_MOD_MOD_MASK) >> PDB_MOD_MOD_SHIFT);
}

/*! \brief Set PDB MOD configuration
 *
 * This function writes new configuration to PDB MOD register
 * If configuration size is less than 32 bits, the least significant bits are used for the correct value.
 * 
 * \param[in] obj  : pointer to PDB register instance
 * \param[in] value : expected PDB MOD register configuration
 */
__attribute__((always_inline)) static inline void PdbReg_SetModReg(PdbRegType *obj, uint16_t value)
{
    uint32_t tmp = obj->MOD;

    tmp &= ~PDB_MOD_MOD_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PDB_MOD_MOD_SHIFT)) & PDB_MOD_MOD_MASK);
    obj->MOD = tmp;
}

/*! \brief Get the current PDB CNT register
 *
 * This function gets the contains the current value of the counter.
 * If data size is less than 32 bits, the least significant bits are used for the correct value.
 *
 * \param[in] obj : pointer to PDB register instance
 * \return the current PDB counter.
 */
__attribute__((always_inline)) static inline uint16_t PdbReg_GetCntReg(const PdbRegType *obj)
{
    return ((obj->CNT & PDB_CNT_CNT_MASK) >> PDB_CNT_CNT_SHIFT);
}

/*! \brief Get the current PDB IDLY register configuration
 *
 * This function gets the current PDB IDLY register configuration.
 * If data size is less than 32 bits, the least significant bits are used for the correct value.
 * Specifies the delay value to schedule the PDB interrupt. 
 * It can be used to schedule an independent interrupt at some point in the PDB cycle.
 * If enabled, a PDB interrupt is generated, when the counter is equal to the IDLY. Reading this field returns the value 
 *     of internal register that is effective for the current cycle of the PDB.
 * \param[in] obj : pointer to PDB register instance
 * \return the current PDB IDLY register configuration.
 */
__attribute__((always_inline)) static inline uint16_t PdbReg_GetIdlyReg(const PdbRegType *obj)
{
    return ((obj->IDLY & PDB_IDLY_IDLY_MASK) >> PDB_IDLY_IDLY_SHIFT);
}

/*! \brief Set PDB IDLY configuration
 *
 * This function writes new configuration to PDB IDLY register
 * If configuration size is less than 32 bits, the least significant bits are used for the correct value.
 *
 * \param[in] obj  : pointer to PDB register instance
 * \param[in] value : expected PDB IDLY register configuration
 */
__attribute__((always_inline)) static inline void PdbReg_SetIdlyReg(PdbRegType *obj, uint16_t value)
{
    uint32_t tmp = obj->IDLY;

    tmp &= ~PDB_IDLY_IDLY_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PDB_IDLY_IDLY_SHIFT)) & PDB_IDLY_IDLY_MASK);
    obj->IDLY = tmp;
}

/*! \brief Get the current PDB CHnC1[BB] register configuration
 *
 * This function gets the current PDB CHnC1[BB] register configuration.
 * If data size is less than 32 bits, the least significant bits are used for the correct value.
 *
 * \param[in] obj : pointer to PDB register instance
 * \param[in] chn  : channel number
 *
 * |---------|---------|-----|---------|---------|
 * |CH7_state|CH6_state|.....|CH1_state|CH0_state|
 * |---------|---------|-----|---------|---------|
 * - 0b: PDB channel's corresponding pre-trigger back-to-back operation disabled.
 * - 1b: PDB channel's corresponding pre-trigger back-to-back operation enabled.
 * \return the current PDB CHnC1[BB] register configuration.
 */
__attribute__((always_inline)) static inline uint8_t PdbReg_GetChnBbReg(const PdbRegType *obj,uint8_t chn)
{
    return ((obj->CH[chn].C1 & PDB_CHnC1_BB_MASK) >> PDB_CHnC1_BB_SHIFT);
}

/*! \brief Set PDB CHnC1[BB] configuration
 *
 * This function writes new configuration to PDB CHnC1[BB] register
 * If configuration size is less than 32 bits, the least significant bits are used for the correct value.
 *
 * \param[in] obj  : pointer to PDB register instance
 *
 * |---------|---------|-----|---------|---------|
 * |CH7_state|CH6_state|.....|CH1_state|CH0_state|
 * |---------|---------|-----|---------|---------|
 * - 0b: PDB channel's corresponding pre-trigger back-to-back operation disabled.
 * - 1b: PDB channel's corresponding pre-trigger back-to-back operation enabled.
 * \param[in] value : expected PDB CHnC1[BB] register configuration
 *
 * \param[in] chn   : channel number
 */
__attribute__((always_inline)) static inline void PdbReg_SetChnBbReg(PdbRegType *obj, uint8_t value,uint8_t chn)
{
    uint32_t tmp = obj->CH[chn].C1;

    tmp &= ~PDB_CHnC1_BB_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PDB_CHnC1_BB_SHIFT)) & PDB_CHnC1_BB_MASK);
    obj->CH[chn].C1= tmp;
}

/*! \brief Get the current PDB CHnC1[TOS] register configuration
 *
 * This function gets the current PDB CHnC1[TOS] register configuration.
 * If data size is less than 32 bits, the least significant bits are used for the correct value.
 * 
 * \param[in] obj : pointer to PDB register instance
 * \param[in] chn  : channel number
 *
 * |---------|---------|-----|---------|---------|
 * |CH7_state|CH6_state|.....|CH1_state|CH0_state|
 * |---------|---------|-----|---------|---------|
 * - 0b: PDB channel's corresponding pre-trigger is in bypassed mode. The pre-trigger asserts one peripheral clock cycle after a rising edge 
             is detected on selected trigger input source or software trigger is selected and SWTRIG is written with 1.
 * - 1b: PDB channel's corresponding pre-trigger asserts when the counter reaches the channel delay register plus one peripheral clock cycle 
             after a rising edge is detected on selected trigger input source or software trigger is selected and SWTRIG is written with 1.
 * \return the current PDB CHnC1[TOS] register configuration.
 */
__attribute__((always_inline)) static inline uint8_t PdbReg_GetChnTosReg(const PdbRegType *obj,uint8_t chn)
{
    return ((obj->CH[chn].C1 & PDB_CHnC1_TOS_MASK) >> PDB_CHnC1_TOS_SHIFT);
}

/*! \brief Set PDB CHnC1[TOS] configuration
 *
 * This function writes new configuration to PDB CHnC1[TOS] register
 * If configuration size is less than 32 bits, the least significant bits are used for the correct value.
 * 
 * \param[in] obj  : pointer to PDB register instance
 *
 * |---------|---------|-----|---------|---------|
 * |CH7_state|CH6_state|.....|CH1_state|CH0_state|
 * |---------|---------|-----|---------|---------|
 * - 0b: PDB channel's corresponding pre-trigger is in bypassed mode. The pre-trigger asserts one peripheral clock cycle after a rising edge 
             is detected on selected trigger input source or software trigger is selected and SWTRIG is written with 1.
 * - 1b: PDB channel's corresponding pre-trigger asserts when the counter reaches the channel delay register plus one peripheral clock cycle 
             after a rising edge is detected on selected trigger input source or software trigger is selected and SWTRIG is written with 1.
 * \param[in] value : expected PDB CHnC1[TOS] register configuration
 * \param[in] chn   : channel number
 */
__attribute__((always_inline)) static inline void PdbReg_SetChnTosReg(PdbRegType *obj, uint8_t value,uint8_t chn)
{
    uint32_t tmp = obj->CH[chn].C1;

    tmp &= ~PDB_CHnC1_TOS_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PDB_CHnC1_TOS_SHIFT)) & PDB_CHnC1_TOS_MASK);
    obj->CH[chn].C1= tmp;
}

/*! \brief Get the current PDB CHnC1[EN] register configuration
 *
 * This function gets the current PDB CHnC1[EN] register configuration.
 * If data size is less than 32 bits, the least significant bits are used for the correct value.
 *
 * \param[in] obj : pointer to PDB register instance
 * \param[in] chn  : channel number
 *
 * |---------|---------|-----|---------|---------|
 * |CH7_state|CH6_state|.....|CH1_state|CH0_state|
 * |---------|---------|-----|---------|---------|
 * - 0b: PDB channel's corresponding pre-trigger disabled.
 * * 1b: PDB channel's corresponding pre-trigger enabled.
 * \return the current PDB CHnC1[EN] register configuration.
 */
__attribute__((always_inline)) static inline uint8_t PdbReg_GetChnEnReg(const PdbRegType *obj,uint8_t chn)
{
    return ((obj->CH[chn].C1 & PDB_CHnC1_EN_MASK) >> PDB_CHnC1_EN_SHIFT);
}

/*! \brief Set PDB CHnC1[EN] configuration
 *
 * This function writes new configuration to PDB CHnC1[EN] register
 * If configuration size is less than 32 bits, the least significant bits are used for the correct value.
 * 
 * \param[in] obj  : pointer to PDB register instance
 *
 * |---------|---------|-----|---------|---------|
 * |CH7_state|CH6_state|.....|CH1_state|CH0_state|
 * |---------|---------|-----|---------|---------|
 * - 0b: PDB channel's corresponding pre-trigger disabled.
 * * 1b: PDB channel's corresponding pre-trigger enabled.
 *
 * \param[in] value : expected PDB CHnC1[EN] register configuration
 * \param[in] chn   : channel number
 */
__attribute__((always_inline)) static inline void PdbReg_SetChnEnReg(PdbRegType *obj, uint8_t value,uint8_t chn)
{
    uint32_t tmp = obj->CH[chn].C1;

    tmp &= ~PDB_CHnC1_EN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PDB_CHnC1_EN_SHIFT)) & PDB_CHnC1_EN_MASK);
    obj->CH[chn].C1= tmp;
}

/*! \brief Get the current PDB CHnS[CF] register.
 *
 * This function gets the current PDB CHnS[CF] register.
 * If data size is less than 32 bits, the least significant bits are used for the correct value.
 * 
 * \param[in] obj : pointer to PDB register instance
 * \param[in] chn  : channel number
 *
 * |---------|---------|-----|---------|---------|
 * |CH7_state|CH6_state|.....|CH1_state|CH0_state|
 * |---------|---------|-----|---------|---------|
 * \return the current PDB CHnS[CF] register.
 */
__attribute__((always_inline)) static inline uint8_t PdbReg_GetChnCfReg(const PdbRegType *obj,uint8_t chn)
{
    return ((obj->CH[chn].S & PDB_CHnS_CF_MASK) >> PDB_CHnS_CF_SHIFT);
}

/*! \brief clear PDB CHnS[CF].
 *
 * This function writes new configuration to PDB CHnS[CF] register
 * If configuration size is less than 32 bits, the least significant bits are used for the correct value.
 * Write 0 to clear CHn[preCH[0-7]]CF.
 * \param[in] obj  : pointer to PDB register instance
 * \param[in] chn   : channel number
 */
__attribute__((always_inline)) static inline void PdbReg_ClrChnCfReg(PdbRegType *obj,uint8_t chn)
{
    uint32_t tmp = obj->CH[chn].S;
    tmp &= ~PDB_CHnS_CF_MASK;
    obj->CH[chn].S= tmp;
}

/*! \brief Get the current PDB CHnS[ERR] register.
 *
 * This function gets the current PDB CHnS[ERR] register.
 * If data size is less than 32 bits, the least significant bits are used for the correct value.
 * 
 * \param[in] obj : pointer to PDB register instance
 * \param[in] chn  : channel number
 *
 * |---------|---------|-----|---------|---------|
 * |CH7_state|CH6_state|.....|CH1_state|CH0_state|
 * |---------|---------|-----|---------|---------|
 * - 0b: Sequence error not detected on PDB channel's corresponding pre-trigger.
 * - 1b: Sequence error detected on PDB channel's corresponding pre-trigger. 
 * \return the current PDB CHnS[ERR] register.
 */
__attribute__((always_inline)) static inline uint8_t PdbReg_GetChnErrReg(const PdbRegType *obj,uint8_t chn)
{
    return ((obj->CH[chn].S & PDB_CHnS_ERR_MASK) >> PDB_CHnS_ERR_SHIFT);
}

/*! \brief clear PDB CHnS[ERR] configuration
 *
 * This function writes new configuration to PDB CHnS[ERR] register
 * If configuration size is less than 32 bits, the least significant bits are used for the correct value.
 * Write 0 to clear CHn[preCH[0-7]]ERR.
 * \param[in] obj  : pointer to PDB register instance
 * \param[in] chn   : channel number
 */
__attribute__((always_inline)) static inline void PdbReg_ClrChnErrReg(PdbRegType *obj,uint8_t chn)
{
    uint32_t tmp = obj->CH[chn].S;
    tmp &= ~PDB_CHnS_ERR_MASK;
    obj->CH[chn].S = tmp;
    (void)(obj->CH[chn].S);
}

/*! \brief Get the current PDB CHnDLY[DLY] register.
 *
 * This function gets the current PDB CHnDLY[DLY] register.
 * If data size is less than 32 bits, the least significant bits are used for the correct value.
 * Reading these bits returns the value of internal register that is effective for the current PDB cycle.
 * \param[in] obj   : pointer to PDB register instance
 * \param[in] chn    : channel number
 * \param[in] preChn : pre-trigger number
 * \return the current PDB CHnDLY[DLY] register.
 */
__attribute__((always_inline)) static inline uint16_t PdbReg_GetChnDlyReg(const PdbRegType *obj,uint8_t chn, uint8_t preChn)
{
    return ((obj->CH[chn].DLY[preChn] & PDB_CHnDLY_DLY_MASK) >> PDB_CHnDLY_DLY_SHIFT);
}

/*! \brief Set PDB CHnDLY[DLY] configuration
 *
 * This function writes new configuration to PDB CHnDLY[DLY] register
 * If configuration size is less than 32 bits, the least significant bits are used for the correct value.
 * 
 * \param[in] obj   : pointer to PDB register instance
 * \param[in] value  : expected PDB CHnDLY[DLY] register configuration
 * \param[in] chn    : channel number
 * \param[in] preChn : pre-trigger number
 */
__attribute__((always_inline)) static inline void PdbReg_SetChnDlyReg(PdbRegType *obj, uint16_t value,uint8_t chn, uint8_t preChn)
{
    uint32_t tmp = obj->CH[chn].DLY[preChn];

    tmp &= ~PDB_CHnDLY_DLY_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PDB_CHnDLY_DLY_SHIFT)) & PDB_CHnDLY_DLY_MASK);
    obj->CH[chn].DLY[preChn]= tmp;
}

/*! \brief Get the current PDB POEN register.
 *
 * This function gets the current PDB POEN register.
 * If data size is less than 32 bits, the least significant bits are used for the correct value.
 * 
 * \param[in] obj : pointer to PDB register instance
 * 
 * |---------|---------|-----|---------|---------|
 * |CH7_state|CH6_state|.....|CH1_state|CH0_state|
 * |---------|---------|-----|---------|---------|
 * - 0b: PDB Pulse-Out disabled
 * - 1b: PDB Pulse-Out enabled
 * \return the current PDB POEN register.
 */
__attribute__((always_inline)) static inline uint8_t PdbReg_GetPoenReg(const PdbRegType *obj)
{
    return ((obj->POEN & PDB_POEN_POEN_MASK) >> PDB_POEN_POEN_SHIFT);
}

/*! \brief Set PDB POEN configuration
 *
 * This function writes new configuration to PDB POEN register
 * If configuration size is less than 32 bits, the least significant bits are used for the correct value.
 * 
 * \param[in] obj  : pointer to PDB register instance
 * 
 * |---------|---------|-----|---------|---------|
 * |CH7_state|CH6_state|.....|CH1_state|CH0_state|
 * |---------|---------|-----|---------|---------|
 * - 0b: PDB Pulse-Out disabled
 * - 1b: PDB Pulse-Out enabled
 * \param[in] value : expected PDB POEN register configuration 
 */
__attribute__((always_inline)) static inline void PdbReg_SetPoenReg(PdbRegType *obj, uint8_t value)
{
    uint32_t tmp = obj->POEN;

    tmp &= ~PDB_POEN_POEN_MASK;
    tmp |= (((uint32_t)(((uint32_t)(value)) << PDB_POEN_POEN_SHIFT)) & PDB_POEN_POEN_MASK);
    obj->POEN = tmp;
}

/*! \brief Get the current PDB POnDLY[DLY1] register.
 *
 * This function gets the current PDB POnDLY[DLY1] register.
 * If data size is less than 32 bits, the least significant bits are used for the correct value.
 * Reading these bits returns the value of internal register that is effective for the current PDB cycle.
 *
 * \param[in] obj : pointer to PDB register instance
 * \param[in] Pon  : PO number
 * \return the current PDB POnDLY[DLY1] register.
 */
__attribute__((always_inline)) static inline uint16_t PdbReg_GetPonDly1Reg(const PdbRegType *obj,uint8_t Pon)
{
    return ((obj->PODLY[Pon] & PDB_POnDLY_DLY1_MASK) >> PDB_POnDLY_DLY1_SHIFT);
}

/*! \brief Get the current PDB POnDLY[DLY2] register.
 *
 * This function gets the current PDB POnDLY[DLY2] register.
 * If data size is less than 32 bits, the least significant bits are used for the correct value.
 * Reading these bits returns the value of internal register that is effective for the current PDB cycle.
 *
 * \param[in] obj : pointer to PDB register instance
 * \param[in] Pon  : PO number
 * \return the current PDB POnDLY[DLY2] register.
 */
__attribute__((always_inline)) static inline uint16_t PdbReg_GetPonDly2Reg(const PdbRegType *obj,uint8_t Pon)
{
    return ((obj->PODLY[Pon] & PDB_POnDLY_DLY2_MASK) >> PDB_POnDLY_DLY2_SHIFT);
}

/*! \brief Set PDB POnDLY configuration
 *
 * This function writes new configuration to PDB POnDLY[DLY1] register
 * If configuration size is less than 32 bits, the least significant bits are used for the correct value.
 * 
 * \param[in] obj  : pointer to PDB register instance
 * \param[in] value : expected PDB POnDLY register configuration(bit0~15 is DLY2,bit 16~31 is DLY1)
 * \param[in] Pon   : PO number
 */
__attribute__((always_inline)) static inline void PdbReg_SetPonDlyReg(PdbRegType *obj, uint32_t value,uint8_t Pon)
{
    obj->PODLY[Pon] = value;
}
#ifdef __cplusplus
}
#endif /* extern "C" */


#endif /* _PDB_REG_H_ */
