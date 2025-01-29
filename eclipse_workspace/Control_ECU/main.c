/*
 *  File name: main.c
 *  Description: Source file for Control_ECU main func
 *  Created on: Nov 1, 2024
 *  Author: Malak Waleed
 */

/*Control_ECU*/
#define F_CPU 8000000UL

#include "std_types.h"
#include "common_macros.h"
#include <avr/io.h>
#include "pir_sensor.h"
#include "dc_motor.h"
#include "buzzer.h"
#include "twi.h"
#include "external_eeprom.h"
#include <util/delay.h>
#include "uart.h"

#define PASSWORD_SIZE 5

/*UART communication symbols*/
#define SEND_DONE 0
#define SEND_NEW_PASSWORD 1
#define RETRIEVE_NEW_PASSWORD 2
#define Control_ECU_READY 3
#define RIGHT_PASSWORD 4
#define WRONG_PASSWORD 5
#define PIR_OFF 6

uint8 new_password[6];
uint8 saved_password[6];

void new_password_save(void)
{
	uint8 i = 0;
	uint8 write_status = 0;
	for(i=0; i<PASSWORD_SIZE; i++)
	{
		write_status = EEPROM_writeByte(0x0010 + i, new_password[i]);
		if(write_status)
		{
			_delay_ms(200);
		}

	}
}

void saved_password_retrieve(void)
{
	uint8 i = 0;
	for(i=0; i<PASSWORD_SIZE; i++)
	{
		EEPROM_readByte(0x0010 + i, &saved_password[i]);
	}
	saved_password[i] = '#';
}
int main(void)
{
	SET_BIT(DDRA,0);
	SET_BIT(PORTA,0);

	uint8 system = 0;
	uint8 i = 0;

	SET_BIT(SREG,7);

	/*peripherals config*/
	TWI_ConfigType	TWIStruct = {0x01 , BAUD_RATE_400KHZ};
	TWI_init(&TWIStruct);

	UART_ConfigType uart_conf_control = {
			CharacterSize_8bit,
			DisabledParity,
			STOPBIT_1bit,
			4800
	};
	UART_init(&uart_conf_control);

	/*Devices initialization*/
	PIRSensor_init();
	DcMotor_Init();
	Buzzer_init();

	while(1)
	{

		switch(UART_recieveByte())
		{
		case SEND_NEW_PASSWORD:
			UART_sendByte(Control_ECU_READY);
			UART_receiveString(new_password);

			new_password_save();
			break;

		case RETRIEVE_NEW_PASSWORD:
			saved_password_retrieve();
			while(UART_recieveByte() != Control_ECU_READY){}
			UART_sendString(saved_password);
			break;

		case RIGHT_PASSWORD:
			DcMotor_Rotate(DC_MOTOR_CLOCKWISE, 100);
			_delay_ms(15000);
			DcMotor_Rotate(DC_MOTOR_CLOCKWISE, DC_MOTOR_STOP);

			while(PIRSensor_getValue())
			{

			}
			UART_sendByte(PIR_OFF);
			DcMotor_Rotate(DC_MOTOR_ANTI_CLOCKWISE, 100);
			_delay_ms(15000);
			DcMotor_Rotate(DC_MOTOR_CLOCKWISE, DC_MOTOR_STOP);
			break;

		case WRONG_PASSWORD:
			Buzzer_on();
			for(i=0; i<61; i++)
			{
				_delay_ms(1000);
			}
			Buzzer_off();
		}


	}
}
