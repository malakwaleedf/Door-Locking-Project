/*
 *  File name: dc_motor.c
 *  Description: Source file for DC Motor driver
 *  Created on: Oct 5, 2024
 *  Author: Malak Waleed
 */

#include "dc_motor.h"
#include "gpio.h"
#include "pwm.h"
#include "common_macros.h"

void DcMotor_Init(void)
{
	/*set the direction of dc motor input pins to output*/
	GPIO_setupPinDirection(DC_MOTOR_INPUT_PORT, DC_MOTOR_IN1, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_INPUT_PORT, DC_MOTOR_IN2, PIN_OUTPUT);

	/*stop dc motor*/
	GPIO_writePin(DC_MOTOR_INPUT_PORT, DC_MOTOR_IN1, LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_INPUT_PORT, DC_MOTOR_IN2, LOGIC_LOW);
}

void DcMotor_Rotate(DcMotor_State state, uint8 speed)
{
	switch(state)
	{
	case DC_MOTOR_STOP:
		GPIO_writePin(DC_MOTOR_INPUT_PORT, DC_MOTOR_IN1, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_INPUT_PORT, DC_MOTOR_IN2, LOGIC_LOW);
		break;
	case DC_MOTOR_CLOCKWISE:
		GPIO_writePin(DC_MOTOR_INPUT_PORT, DC_MOTOR_IN1, LOGIC_HIGH);
		GPIO_writePin(DC_MOTOR_INPUT_PORT, DC_MOTOR_IN2, LOGIC_LOW);
		break;
	case DC_MOTOR_ANTI_CLOCKWISE:
		GPIO_writePin(DC_MOTOR_INPUT_PORT, DC_MOTOR_IN1, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_INPUT_PORT, DC_MOTOR_IN2, LOGIC_HIGH);
		break;
	}
	PWM_Timer0_Start(speed);
}
