/*
 * pwm.c
 *
 */

//***************************************************************
// included files
//**************************************************************/
#include "pwm.h"

//***************************************************************
// function definitions
//**************************************************************/
void pwm_open(void)
{
    //disables interrupt
    __disable_interrupt();

    // stop timer_a before modifying operation; per: TRM 19.2.1
    stop_pwm();

    // configure timer_a for PWM operation
    config_pwm_timer();

    // configure P2.4 for PWM
    config_gpio();

    // configure 2.3 for PWM
    config_gpio_int();

    // enable NVIC
    config_nvic();

    // start PWM timer
    start_pwm();

    //config_pwm_timer_25();
    //config_pwm_timer_50();
    //config_pwm_timer_75();
    config_pwm_timer_50_int();

    //enable interrupt
    __enable_interrupt();
}


void start_pwm(void)
{
    // set MC to up mode
    TIMER_A0->CTL |= TIMER_A_CTL_MC__UP;
}


void stop_pwm(void)
{
    // set MC to halt/stop mode
    TIMER_A0->CTL = TIMER_A_CTL_MC__STOP;
}


void config_pwm_timer(void)
{
    // clear R register
    TIMER_A0->CTL |= TIMER_A_CTL_CLR;

    // select SMCLK as source
    TIMER_A0->CTL |= TIMER_A_CTL_SSEL__SMCLK;

    // set input divider; 2^1
    TIMER_A0->CTL |= TIMER_A_CTL_ID__1;

    // intermediary state; see note at bottom of page (TRM 19.2.5.1.3)
    TIMER_A0 -> CCTL[1] |= TIMER_A_CCTLN_OUTMOD_7;

    // Set/Reset mode
    TIMER_A0 -> CCTL[1] &= TIMER_A_CCTLN_OUTMOD_3;

    // set capture/compare register 0 value
    TIMER_A0 -> CCR[0] = TICKS;

    //capture compare interrupt enable
    TIMER_A0->CCTL[1] |= TIMER_A_CCTLN_CCIE;
}

void config_nvic(void)
{
    __NVIC_EnableIRQ(TA0_N_IRQn);
}

void TA0_N_IRQHandler(void)
{
    TIMER_A0->CCTL[1] &= ~TIMER_A_CCTLN_CCIFG;
    P2->OUT ^= BIT3;
}


void config_pwm_timer_25(void)
{
    // set capture/compare reg1 value value for 25% duty cycle
    TIMER_A0->CCR[1] = CCR1_DUTY_25;
}


void config_pwm_timer_50(void)
{
    // set capture/compare reg1 value value for 50% duty cycle
    TIMER_A0->CCR[1] = CCR1_DUTY_50;
}


void config_pwm_timer_75(void)
{
    // set capture/compare reg1 value for 75% duty cycle
    TIMER_A0->CCR[1] = CCR1_DUTY_75;
}

void config_pwm_timer_50_int(void)
{
    // clear R register
        TIMER_A0->CTL |= TIMER_A_CTL_CLR;

        // select SMCLK as source
        TIMER_A0->CTL |= TIMER_A_CTL_SSEL__SMCLK;

        // set input divider; 2^0
        TIMER_A0->CTL |= TIMER_A_CTL_ID_0;

        // set capture/compare register 0 value
        TIMER_A0 -> CCR[0] = CCR0_DUTY_50_INT;

        // intermediary state; see note at bottom of page (TRM 19.2.5.1.3)
        TIMER_A0 -> CCTL[1] |= TIMER_A_CCTLN_OUTMOD_7;

        // Toggle mode
        TIMER_A0 -> CCTL[1] &= TIMER_A_CCTLN_OUTMOD_4;

        //capture compare interrupt enable
        TIMER_A0->CCTL[1] |= TIMER_A_CCTLN_CCIE;
}
