/******************************************************************************
 * filename: si7021.h                                                         *
 *                                                                            *
 * purpose: Contains function declarations and macros used in si7021.c        *
 *                                                                            *
 * date created: 22 Jan 2019                                                  *
 *                                                                            *
 * authors: Dylan Oh and Mike Fruge                                           *
 *****************************************************************************/

/******************************************************************************
 * MACRO DEFINITIONS                                                          *
 *****************************************************************************/

/******************************************************************************
 * FUNCTION DECLARATIONS                                                      *
 *****************************************************************************/
void enable_LPM(void);
void disable_LPM(void);
uint8_t read_user_reg(void);
uint8_t measure_temp(void);
uint8_t convert_temp(uint8_t);
