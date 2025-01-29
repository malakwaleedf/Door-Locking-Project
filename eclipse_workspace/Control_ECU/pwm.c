/*
 *  File name: pwm.c
 *  Description: Source file for PWM driver
 *  Created on: Oct 5, 2024
 *  Author: Malak Waleed
 */

#include "pwm.h"
#include "common_macros.h"
#include "std_types.h"
#include <avr/io.h>

void PWM_Timer0_Start(uint8 duty_cycle)
{
		SET_BIT(TCCR0,WGM01);
		SET_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,COM01);
		SET_BIT(TCCR0,CS00);
		SET_BIT(TCCR0,CS01);
		TCNT0 = 0;
		OCR0 = (duty_cycle * 255)/100;
		SET_BIT(DDRB,PB3);
}
