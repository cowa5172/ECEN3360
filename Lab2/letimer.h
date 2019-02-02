/*
* Includes
*/

#include "main.h"
#include "em_letimer.h"
#include "cmu.h"

/*
* Defines
*/

#define LFXO_FREQ       32768u
#define ULFRCO_FREQ     1000u
#define LFXO_PRESC      1024u
#define LETIMER_PERIOD  5   // in seconds
#define LED_ON_TIME     0.4    // in seconds

//***********************************************************************************
// global variables
//***********************************************************************************


/*
* Function Declarations
*/

void LETIMER0_init(void);
void LETIMER0_IRQHandler(void);

