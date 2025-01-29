/*
 *  File name: buzzer.c
 *  Description: Source file for Buzzer driver
 *  Created on: Oct 6, 2024
 *  Author: Malak Waleed
 */

#include "buzzer.h"
#include "gpio.h"
#include "common_macros.h"

void Buzzer_init(void)
{
	/*set the direction of buzzer's pin to output*/
	GPIO_setupPinDirection(BUZZER_PORT, BUZZER_PIN, PIN_OUTPUT);

	/*turn off buzzer*/
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_LOW);
}

void Buzzer_on(void)
{
	/*turn on buzzer*/
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_HIGH);
}

void Buzzer_off(void)
{
	/*turn off buzzer*/
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_LOW);
}




