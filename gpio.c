/*
 * gpio.c
 *
 */


//***************************************************************
// included files
//**************************************************************/
#include "gpio.h"

//***************************************************************
// defined macros
//**************************************************************/


//***************************************************************
// function definitions
//**************************************************************/
void config_pwm_gpio(void)
{
    // set P2.4 as output (TRM 12.2.3)
    P2->DIR |= BIT4;

    // set OUT register to high (TRM 12.2.2)
    P2->OUT |= BIT4;

    // set drive strength to high (TRM 12.2.5)
    P2->DS |= BIT4;

    // select primary module function of P2.4 (TRM 12.2.6)
    P2->SEL0 |= BIT4;
    P2->SEL1 &= ~BIT4;

}

void config_gpio(void)
{
    // set P1.0 & P2.2 as output (TRM 12.2.3)
    P1->DIR |= BIT0;
    P2->DIR |= BIT2;

    // set OUT register to high (TRM 12.2.2)
    P1->OUT |= BIT0;

    // set drive strength to high (TRM 12.2.2)
    P1->DS |= BIT0;
    P2->DS |= BIT2;
}
