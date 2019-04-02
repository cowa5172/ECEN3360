#include "main.h"
#include "em_cmu.h"

/******************************************************************************
 * filename: cmu.h                                                            *
 *                                                                            *
 * purpose: Contains function declarations and macros used in cmu.c           *
 *                                                                            *
 * date created: 22 Jan 2019                                                  *
 *                                                                            *
 * authors: Dylan Oh and Mike Fruge                                           *
 *****************************************************************************/

/******************************************************************************
 * FUNCTION DECLARATIONS                                                      *
 *****************************************************************************/

/*
 * function name: cmu_init
 *
 * description: Configures the clock tree, selects the clocks to be used, and 
 *              initialises the clocks
 * 
 * arguments: none
 * 
 * returns: none
 */

void cmu_init(void);
