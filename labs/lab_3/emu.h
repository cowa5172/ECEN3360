#include "em_emu.h"
#include "em_core.h"
#include "main.h"

/******************************************************************************
 * filename: emu.h                                                            *
 *                                                                            *
 * purpose: Contains function declarations and macros used in emu.c           *
 *                                                                            *
 * date created: 22 Jan 2019                                                  *
 *                                                                            *
 * authors: Dylan Oh and Mike Fruge                                           *
 *****************************************************************************/

/******************************************************************************
 * MACRO DEFINITIONS                                                          *
 *****************************************************************************/
#define MAX_EM_ELEMENTS 5
#define EM0             0
#define EM1             1
#define EM2             2
#define EM3             3
#define EM4             4


/******************************************************************************
 * FUNCTION DECLARATIONS                                                      *
 *****************************************************************************/

/*
 * function name: EMU_Block
 *
 * description: Sets a limit on the minimum allowable energy mode that the
 *              Pearl Gecko can operate in
 * 
 * arguments:
 * argument     type        description
 * --------     ----        -----------
 * EM           uint8_t     minimum mode the Pearl Gecko can operate in
 * 
 * returns: none
 */

void EMU_Block(uint8_t);

/*****************************************************************************/

/*
 * function name: EMU_Unblock
 *
 * description: Removes limit on the minimum allowable energy mode that the
 *              Pearl Gecko can operate in
 * 
 * arguments:
 * argument     type        description
 * --------     ----        -----------
 * EM           uint8_t     minimum mode the Pearl Gecko can operate in
 * 
 * returns: none
 */

void EMU_Unblock(uint8_t);

/*****************************************************************************/

/*
 * function name: EMU_Sleep
 *
 * description: Puts the Pearl Gecko to sleep in the lowest energy mode
 *              allowed by the block and unblock functions
 * 
 * arguments: none
 * 
 * returns: none
 */

void EMU_Sleep(void);
