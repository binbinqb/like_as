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

/*******************************************************************************
 * the includes
 ******************************************************************************/

#include "startup.h"
#include <stdint.h>
#include "../cva/CVM014x.h"
#include "../../../CVM014x_features.h"


/*******************************************************************************
 * the defines
 ******************************************************************************/

/*******************************************************************************
 * the typedefs
 ******************************************************************************/

/*******************************************************************************
 * the globals
 ******************************************************************************/


/*******************************************************************************
 * the functions
 ******************************************************************************/

void init_data_bss(void)
{
    uint32_t n;
/* For ARMC we are using the library method of initializing DATA, Custom Section and
 * Code RAM sections so the below variables are not needed */
#if !defined(__ARMCC_VERSION)
    /* Declare pointers for various data sections. These pointers
     * are initialized using values pulled in from the linker file */
    uint8_t*       data_ram;
    uint8_t*       code_ram;
    uint8_t*       bss_start;
    uint8_t*       custom_ram;
    const uint8_t *data_rom, *data_rom_end;
    const uint8_t *code_rom, *code_rom_end;
    const uint8_t* bss_end;
    const uint8_t *custom_rom, *custom_rom_end;
#endif
    /* Addresses for VECTOR_TABLE and VECTOR_RAM come from the linker file */

#if defined(__ARMCC_VERSION)
    extern uint32_t __RAM_VECTOR_TABLE_SIZE;
    extern uint32_t __VECTOR_ROM;
    extern uint32_t __VECTOR_RAM;
#else
    extern uint32_t __RAM_VECTOR_TABLE_SIZE[];
    extern uint32_t __VECTOR_TABLE[];
    extern uint32_t __VECTOR_RAM[];
#endif
    /* Get section information from linker files */
#if defined(__ICCARM__)
    /* Data */
    data_ram     = __section_begin(".data");
    data_rom     = __section_begin(".data_init");
    data_rom_end = __section_end(".data_init");

/* CODE RAM */
#pragma section = "__CODE_ROM"
#pragma section = "__CODE_RAM"
    code_ram     = __section_begin("__CODE_RAM");
    code_rom     = __section_begin("__CODE_ROM");
    code_rom_end = __section_end("__CODE_ROM");

    /* BSS */
    bss_start = __section_begin(".bss");
    bss_end   = __section_end(".bss");

    custom_ram     = __section_begin(".customSection");
    custom_rom     = __section_begin(".customSection_init");
    custom_rom_end = __section_end(".customSection_init");

#elif defined(__ARMCC_VERSION)
    /* VECTOR TABLE*/
    uint8_t  *vector_table_size = (uint8_t *)__RAM_VECTOR_TABLE_SIZE;
    uint32_t *vector_rom        = (uint32_t *)__VECTOR_ROM;
    uint32_t *vector_ram        = (uint32_t *)__VECTOR_RAM;
#else
    extern uint32_t __DATA_ROM[];
    extern uint32_t __DATA_RAM[];
    extern uint32_t __DATA_END[];

    extern uint32_t __CODE_RAM[];
    extern uint32_t __CODE_ROM[];
    extern uint32_t __CODE_END[];

    extern uint32_t __BSS_START[];
    extern uint32_t __BSS_END[];

    extern uint32_t __CUSTOM_ROM[];
    extern uint32_t __CUSTOM_END[];

    /* Data */
    data_ram     = (uint8_t *)__DATA_RAM;
    data_rom     = (uint8_t *)__DATA_ROM;
    data_rom_end = (uint8_t *)__DATA_END;
    /* CODE RAM */
    code_ram     = (uint8_t *)__CODE_RAM;
    code_rom     = (uint8_t *)__CODE_ROM;
    code_rom_end = (uint8_t *)__CODE_END;
    /* BSS */
    bss_start = (uint8_t *)__BSS_START;
    bss_end   = (uint8_t *)__BSS_END;

    /* Custom section */
    custom_ram     = CUSTOMSECTION_SECTION_START;
    custom_rom     = (uint8_t *)__CUSTOM_ROM;
    custom_rom_end = (uint8_t *)__CUSTOM_END;

#endif

#if !defined(__ARMCC_VERSION)
    /* Copy initialized data from ROM to RAM */
    while(data_rom_end != data_rom)
    {
        *data_ram = *data_rom;
        data_ram++;
        data_rom++;
    }

    /* Copy functions from ROM to RAM */
    while(code_rom_end != code_rom)
    {
        *code_ram = *code_rom;
        code_ram++;
        code_rom++;
    }

    /* Clear the zero-initialized data section */
    while(bss_end != bss_start)
    {
        *bss_start = 0;
        bss_start++;
    }

    /* Copy customsection rom to ram */
    while(custom_rom_end != custom_rom)
    {
        *custom_ram = *custom_rom;
        custom_rom++;
        custom_ram++;
    }
#endif
#if defined(__ARMCC_VERSION)
    /* Copy the vector table from ROM to RAM */
    /* Workaround */
    if(vector_ram != vector_rom)
    {
        for(n = 0; n < (((uint32_t)(vector_table_size)) / sizeof(uint32_t)); n++)
        {
            vector_ram[n] = vector_rom[n];
        }
        /* Point the VTOR to the position of vector table */
        SCB->VTOR = (uint32_t)__VECTOR_RAM;
    }
    else
    {
        /* Point the VTOR to the position of vector table */
        SCB->VTOR = (uint32_t)__VECTOR_ROM;
    }
#else
    /* Check if VECTOR_TABLE copy is needed */
    if(__VECTOR_RAM != __VECTOR_TABLE) /* polyspace DEFECT:DEAD_CODE [No action planned:Low] "Depend on link script" */
    {
        /* Copy the vector table from ROM to RAM */
        for(n = 0; n < (((uint32_t)__RAM_VECTOR_TABLE_SIZE) / sizeof(uint32_t)); n++)
        {
            __VECTOR_RAM[n] = __VECTOR_TABLE[n];
        }
        /* Point the VTOR to the position of vector table */
        SCB->VTOR = (uint32_t)__VECTOR_RAM;
    }
    else
    {
        /* Point the VTOR to the position of vector table */
        SCB->VTOR = (uint32_t)__VECTOR_TABLE;
    }
#endif
}
