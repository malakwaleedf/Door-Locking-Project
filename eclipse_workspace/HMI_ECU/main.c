/*
 *  File name: main.c
 *  Description: Source file for HMI_ECU main func
 *  Created on: Nov 1, 2024
 *  Author: Malak Waleed
 */

/*HMI_ECU*/
#define F_CPU 16000000UL

#include "std_types.h"
#include "lcd.h"
#include "keypad.h"
#include "common_macros.h"
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"

/*system cases*/
#define NEW_PASSWORD_ENTER 0
#define MAIN_OPTIONS 1
#define ENTER_PASSWORD 2
#define WRONG_PASSWORD_ENTERED 3
#define RIGHT_PASSWORD_ENTERED 4
#define CHANGE_PASSWORD 5

/*UART communication symbols*/
#define SEND_DONE 0
#define SEND_NEW_PASSWORD 1
#define RETRIEVE_NEW_PASSWORD 2
#define Control_ECU_READY 3
#define RIGHT_PASSWORD 4
#define WRONG_PASSWORD 5
#define PIR_OFF 6


#define PASSWORD_SIZE 5

int main(void)
{
	SET_BIT(SREG,7);

	uint8 system_case = 0;
	uint8 i = 0;
	uint8 new_password[6];
	uint8 saved_password[6];
	uint8 entered_password[6];
	uint8 choice = 0;
	uint8 check_flag = 0;
	uint8 enter_key = ' ';
	uint8 unmatch_num = 0;


	/*peripherals config*/
	UART_ConfigType uart_conf_hmi = {
			CharacterSize_8bit,
			DisabledParity,
			STOPBIT_1bit,
			9600
	};
	UART_init(&uart_conf_hmi);

	/*devices initialization*/
	LCD_init();
	LCD_moveCursor(0,0);


	while(1)
	{
		switch(system_case)
		{
		case NEW_PASSWORD_ENTER:
			LCD_clearScreen();
			LCD_displayString("Plz enter pass:");
			LCD_moveCursor(1,0);

			for(i = 0; i<PASSWORD_SIZE; i++)
			{
				new_password[i] = KEYPAD_getPressedKey();
				LCD_displayCharacter('*');
				_delay_ms(50);
			}

			while(KEYPAD_getPressedKey() != enter_key);

			LCD_moveCursor(1,0);
			LCD_displayString("Same pass:");

			LCD_moveCursor(1,11);
			for(i = 0; i<PASSWORD_SIZE; i++)
			{
				new_password[i] = KEYPAD_getPressedKey();
				LCD_displayCharacter('*');
				_delay_ms(50);
			}

			while(KEYPAD_getPressedKey() != enter_key);

			new_password[i] = '#';
			_delay_ms(100);

			UART_sendByte(SEND_NEW_PASSWORD);
			while(UART_recieveByte() != Control_ECU_READY){}
			UART_sendString(new_password);
			UART_sendByte(SEND_DONE);
			system_case = MAIN_OPTIONS;
			break;


		case MAIN_OPTIONS:
			LCD_clearScreen();
			LCD_moveCursor(0,0);
			LCD_displayString("+ : Open Door");
			LCD_moveCursor(1,0);
			LCD_displayString("- : Change Pass");
			choice = KEYPAD_getPressedKey();
			if(choice == '+')
			{
				system_case = ENTER_PASSWORD;
			}
			else if(choice == '-')
			{
				system_case = ENTER_PASSWORD;
			}
			break;

		case ENTER_PASSWORD:
			UART_sendByte(RETRIEVE_NEW_PASSWORD);
			UART_sendByte(Control_ECU_READY);
			UART_receiveString(saved_password);
			UART_sendByte(SEND_DONE); /*saved password retrieved*/

			/*ask user to enter password*/
			LCD_clearScreen();
			LCD_moveCursor(0,0);
			LCD_displayString("Plz enter pass:");
			LCD_moveCursor(1,0);

			for(i = 0; i<PASSWORD_SIZE; i++)
			{
				entered_password[i] = KEYPAD_getPressedKey();
				LCD_displayCharacter('*');
				_delay_ms(50);
			}

			while(KEYPAD_getPressedKey() != enter_key);

			/*check if password is right*/
			for(i = 0; i<PASSWORD_SIZE; i++)
			{
				if(entered_password[i] != saved_password[i])
				{
					system_case = WRONG_PASSWORD_ENTERED;
					break;
				}
				else
				{

				}
				check_flag = 1;
			}
			if(check_flag && choice == '+')
			{
				unmatch_num =0;
				system_case = RIGHT_PASSWORD_ENTERED;
			}
			else if(check_flag && choice == '-')
			{
				unmatch_num =0;
				system_case = NEW_PASSWORD_ENTER;
			}
			break;

		case RIGHT_PASSWORD_ENTERED:
			UART_sendByte(RIGHT_PASSWORD);
			LCD_clearScreen();
			LCD_moveCursor(0,0);
			LCD_displayString("Door is ");
			LCD_moveCursor(1,0);
			LCD_displayString("Unlocking");
			_delay_ms(15000);

			LCD_clearScreen();
			LCD_moveCursor(0,0);
			LCD_displayString("Wait for people");
			LCD_moveCursor(1,5);
			LCD_displayString("to Enter");

			while(UART_recieveByte() != PIR_OFF){}

			LCD_clearScreen();
			LCD_moveCursor(0,0);
			LCD_displayString("Door is Locking");
			_delay_ms(15000);
			LCD_clearScreen();

			UART_sendByte(SEND_DONE);

			system_case = MAIN_OPTIONS;
			break;

		case WRONG_PASSWORD_ENTERED:
			unmatch_num++;
			LCD_clearScreen();
			LCD_moveCursor(0,0);
			LCD_displayString("Wrong pass");
			_delay_ms(500);
			LCD_clearScreen();
			if(unmatch_num == 3)
			{
				UART_sendByte(WRONG_PASSWORD);
				LCD_moveCursor(0,4);
				LCD_displayString("ERROR");
				for(i=0; i<61; i++)
				{
					_delay_ms(1000);
				}

				UART_sendByte(SEND_DONE);
				system_case = MAIN_OPTIONS;
			}
			else
			{
				system_case = ENTER_PASSWORD;
			}
			break;


		}

	}
}

