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
    __disable_interrupt();
    stop_pwm();
    config_pwm_timer_50_int();
    config_pwm_gpio();
    config_gpio();
    config_pwm_nvic();
}


void start_pwm(void)
{
    // set MC to up mode (TRM 19.3.1; MC bitfield)
    TIMER_A0->CTL |= TIMER_A_CTL_MC__UP;

    // enable interrupt
    __enable_interrupt();
}


void stop_pwm(void)
{
    // set MC to halt/stop mode (TRM 19.3.1; MC bitfield)
    TIMER_A0->CTL &= ~TIMER_A_CTL_MC__STOP;
}


void config_pwm_timer(void)
{
    // clear R register (TRM 19.3.1; TACLR bitfield)
    TIMER_A0->CTL |= TIMER_A_CTL_CLR;

    // select SMCLK as source (TRM 19.3.1; TASSEL bitfield)
    TIMER_A0->CTL |= TIMER_A_CTL_SSEL__SMCLK;

    // set input divider; 2^1 (TRM 19.3.1; ID bitfield)
    TIMER_A0->CTL |= TIMER_A_CTL_ID_1;

    // CCTL[1] defaults to OUTMOD_0, so we need an intermediate state to avoid
    // NOR gate glitch; see note at bottom of page (TRM 19.2.5.1.3)
    TIMER_A0->CCTL[1] |= TIMER_A_CCTLN_OUTMOD_7;

    // Set/Reset output mode (TRM 19.3.3; OUTMOD bitfield)
    TIMER_A0->CCTL[1] &= TIMER_A_CCTLN_OUTMOD_3;

    // save calculated ticks to CCR0 register (TRM19.3.4)
    TIMER_A0->CCR[0] = TICKS;
}


void config_pwm_timer_25(void)
{
    // set CCR1 value for 25% duty cycle
    TIMER_A0->CCR[1] = CCR1_DUTY_25;
}


void config_pwm_timer_50(void)
{
    // set CCR1 value for 50% duty cycle
    TIMER_A0->CCR[1] = CCR1_DUTY_50;
}

void config_pwm_timer_50_int(void)
{
    // clear R register (TRM 19.3.1; TACLR bitfield)
    TIMER_A0->CTL |= TIMER_A_CTL_CLR;

    // select SMCLK as source (TRM 19.3.1; TASSEL bitfield)
    TIMER_A0->CTL |= TIMER_A_CTL_SSEL__SMCLK;

    // set input divider; 2^1 (TRM 19.3.1; ID bitfield)
    TIMER_A0->CTL |= TIMER_A_CTL_ID__4;

    // save calculated ticks to CCR0 register (TRM 19.3.4)
    TIMER_A0->CCR[0] = TICKS;

    // CCTL[1] defaults to OUTMOD_0, so we need an intermediate state to avoid
    // NOR gate glitch; see note at bottom of page (TRM 19.2.5.1.3)
    TIMER_A0->CCTL[1] |= TIMER_A_CCTLN_OUTMOD_7;

    // toggle output mode (TRM 19.3.3; OUTMOD bitfield)
    TIMER_A0->CCTL[1] &= TIMER_A_CCTLN_OUTMOD_4;

    // enable timer interrupts for capture/compare (TRM 19.3.3)
    TIMER_A0->CCTL[1] |= TIMER_A_CCTLN_CCIE;
}

void config_pwm_timer_75(void)
{
    // set CCR1 value for 75% duty cycle
    TIMER_A0->CCR[1] = CCR1_DUTY_75;
}

void config_pwm_nvic(void)
{
    // enable NVIC IRQ
    __NVIC_EnableIRQ(TA0_N_IRQn);
}

void TA0_N_IRQHandler(void)
{
    // if CCTL flag raised ...
    if(TIMER_A0->CCTL[1] & BIT0)
    {
        // ... lower CCTL flag (TRM 19.3.1; TAIFG bitfield)
        TIMER_A0->CCTL[1] &= ~(TIMER_A_CCTLN_CCIFG);
    }

    // toggle LED on P2.0
    P1->OUT ^= BIT0;

    // toggle LED on P2.2
    P2->OUT ^= BIT2;
}
