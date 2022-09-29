/**
 * main.c
 */

//***************************************************************
// included files
//**************************************************************/
#include "msp.h"
#include "pwm.h"
#include "gpio.c"

//***************************************************************
// main loop
//**************************************************************/
void main(void)
{
    // stop watchdog timer
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

	// stop timer_a before modifying operation; per: TRM 19.2.1
	stop_pwm();

	// configure timer_a for PWM operation
	config_pwm_timer();

	// configure P2.4 for PWM
	config_gpio();

	// start PWM timer
	start_pwm();


	//config_pwm_timer_25();
    //config_pwm_timer_50();
	config_pwm_timer_75();

	while(1)
	{
	    // main infinite while loop
	}

}
