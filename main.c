#include "msp.h"
#include "pwm.h"

/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	stop_pwm(); //KNOWN STATE
	config_pwm_timer(); //only run once

	//todo config gpio
	P2->DIR |= BIT4;
	P2->SEL0 |= BIT4;
	P2->SEL1 &= ~BIT4;
    P2->OUT &= ~(BIT4);

	start_pwm();
	//config_pwm_timer_25();
    //config_pwm_timer_50();
	config_pwm_timer_75();

	while(1)
	{

	}

}
