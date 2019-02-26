#include "emu.h"

/* This code is originally Silicon Labs and copy righted by Silicon Labs� in 
 * 2015 and Silicon Labs� grants permission to anyone to use the software for 
 * any purpose, including commercial applications, and to alter it, and 
 * redistribute it freely subject that the origins is not miss represented, 
 * altered source version must be plainly marked, and this notice cannot be 
 * altered or removed from any source distribution.
 *
 * Names of routines have been changed to confirm to the naming convention of 
 * the application developer.
 *
 * Routines include:
 *
 * void Sleep_Block_Mode(unsigned int EM);
 * void Sleep_UnBlock_Mode(unsigned int EM);
 * void Enter_Sleep(void);
 *
 */

/******************************************************************************
 * filename: emu.c                                                            *
 *                                                                            *
 * purpose: Contains functions pertaining to the EMU of the Pearl Gecko and   *
 *          that modify the energy mode that the Pearl Gecko operates in      *
 *                                                                            *
 * date created: 22 Jan 2019                                                  *
 *                                                                            *
 * authors: Dylan Oh and Mike Fruge                                           *
 *****************************************************************************/

/******************************************************************************
 * GLOBAL VARIABLES                                                           *
 *****************************************************************************/
volatile uint32_t lowest_EM[MAX_EM_ELEMENTS];


/******************************************************************************
 * FUNCTION DEFINITIONS                                                       *
 *****************************************************************************/

void EMU_Block(uint8_t EM){
    CORE_ATOMIC_IRQ_DISABLE();
    lowest_EM[EM]++;
    CORE_ATOMIC_IRQ_ENABLE();
}

void EMU_Unblock(uint8_t EM){
    CORE_ATOMIC_IRQ_DISABLE();
    if (lowest_EM[EM] > 0) lowest_EM[EM]--;
    CORE_ATOMIC_IRQ_ENABLE();
}

void EMU_Sleep(void){
    if (lowest_EM[EM0] > 0){
        return;
    } else if (lowest_EM[EM1] > 0){
        return;
    } else if (lowest_EM[EM2] > 0){
        EMU_EnterEM1();
    } else if (lowest_EM[EM3] > 0){
        EMU_EnterEM2(true);
    } else {
        EMU_EnterEM3(true);
    }
}
