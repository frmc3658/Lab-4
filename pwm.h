

/*
 * pwm.h
 *
 */

//***************************************************************
// header guards
//**************************************************************/
#ifndef PWM_H_
#define PWM_H_

//***************************************************************
// included files
//**************************************************************/
#include "msp.h"
#include "gpio.h"

//***************************************************************
// defined macros
//**************************************************************/
#define TICKS               ((uint16_t) 0x5DC)
#define CCR1_DUTY_25        ((uint16_t) 0x177)
#define CCR1_DUTY_50        ((uint16_t) 0x2EE)
#define CCR1_DUTY_75        ((uint16_t) 0x465)
#define CCR0_DUTY_50_INT    ((uint16_t) 0x2EE)

//***************************************************************
// function prototypes
//**************************************************************/
void pwm_open(void);
void stop_pwm(void);
void start_pwm(void);
void config_pwm_timer(void);
void config_pwm_timer_25(void);
void config_pwm_timer_50_int(void);
void config_pwm_timer_50(void);
void config_pwm_timer_75(void);

//***************************************************************
// nvic-nested vector interrupt controller
//**************************************************************/
void config_nvic(void);

#endif /* PWM_H_ */
