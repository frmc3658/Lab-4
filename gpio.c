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
void config_gpio(void)
{
    // set P2.4 as output (TRM 12.2.3)
    P2->DIR |= BIT4;

    // select primary module function of P2.4 (TRM 12.2.6)
    P2->SEL0 |= BIT4;
    P2->SEL1 &= ~BIT4;

    // set OUT register to low (TRM 12.2.2)
    P2->OUT &= ~(BIT4);
}

void config_gpio_int(void)
{
    P2->DIR |= BIT3;
    P2->OUT |= BIT3;
    P2->DS |= BIT3;
}
