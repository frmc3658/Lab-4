/*
 * pwm.c
 *
 *  Created on: Sep 19, 2022
 *      Author: Arielle
 */
#include "pwm.h"

void start_pwm(void)
{
    TIMER_A0 -> CTL |= TIMER_A_CTL_MC__UP;// set MC to up
}

void stop_pwm(void)
{
    TIMER_A0 -> CTL = TIMER_A_CTL_MC__STOP;// set MC to halt, stop
}

void config_pwm_timer(void)
{
    TIMER_A0->CTL |= TIMER_A_CTL_CLR;           // clear R register
    TIMER_A0->CTL |= TIMER_A_CTL_SSEL__SMCLK;   // select SMCLK as source
    TIMER_A0->CTL |= TIMER_A_CTL_ID_1;          // set input divider

    //want known state + NOR glitch occurs so use TIMER_A_CCTLN_OUTMOD_7 as intermediary state
    TIMER_A0 -> CCTL[1] |= TIMER_A_CCTLN_OUTMOD_7; // NOR glitch set 1111 MODE
    TIMER_A0 -> CCTL[1] &= TIMER_A_CCTLN_OUTMOD_3; // Set/Reset mode

    TIMER_A0 -> CCR[0] = TICKS;
}


void config_pwm_timer_25(void)
{
    TIMER_A0->CCR[1] = CCR1_DUTY_25;
}


void config_pwm_timer_50(void)
{
    TIMER_A0->CCR[1] = CCR1_DUTY_50;
}


void config_pwm_timer_75(void)
{
    TIMER_A0->CCR[1] = CCR1_DUTY_75;
}

