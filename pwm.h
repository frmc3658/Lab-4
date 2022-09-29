/*
 * pwm.h
 *
 *  Created on: Sep 19, 2022
 *      Author: Arielle
 */

#ifndef PWM_H_
#define PWM_H_
#include "msp.h"

#define TICKS               ((uint16_t) 0xBB8)
#define CCR1_DUTY_25        ((uint16_t) 0x177)
#define CCR1_DUTY_50        ((uint16_t) 0x2EE)
#define CCR1_DUTY_75        ((uint16_t) 0x465)


void config_pwm_timer(void);
void stop_pwm(void);
void start_pwm(void);

void config_pwm_timer_25(void);
void config_pwm_timer_50(void);
void config_pwm_timer_75(void);


#endif /* PWM_H_ */
