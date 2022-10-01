/**
 * main.c
 */

//***************************************************************
// included files
//**************************************************************/
#include "msp.h"
#include "pwm.h"

//***************************************************************
// main loop
//**************************************************************/
void main(void)
{
    // stop watchdog timer
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

	pwm_open();
	start_pwm();

	// main infinite while loop
	while(1)
	{

	}

}
