/**
 * main.c
 * dep 2 level
 */

//***************************************************************
// included files
//**************************************************************/
#include "msp.h"
#include "pwm.h"
#include "gpio.h"


//***************************************************************
// main loop
//**************************************************************/
void main(void)
{
    // stop watchdog timer
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

    // open PWM
    pwm_open();

    while(1)
    {
        // main infinite while loop
    }

}
