/*
 *  File name: lcd.c
 *  Description: Source file for LCD driver
 *  Created on: Oct 5, 2024
 *  Author: Malak Waleed
 */

//#define F_CPU 16000000UL

#include "lcd.h"
#include "gpio.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include "std_types.h"
#include <util/delay.h>

/*LCD init*/
void LCD_init(void)
{
	GPIO_setupPinDirection(RS_PORT, RS_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(ENABLE_PORT, ENABLE_PIN, PIN_OUTPUT);

#if(LCD_DATA_BITS_MODE == 8)
	GPIO_setupPortDirection(LCD_DATA_PORT, PORT_OUTPUT);
	_delay_ms(20);
	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);

#elif(LCD_DATA_BITS_MODE == 4)
	GPIO_setupPinDirection(LCD_DATA_PORT, LCD_DATA_PIN_1, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT, LCD_DATA_PIN_2, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT, LCD_DATA_PIN_3, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT, LCD_DATA_PIN_4, PIN_OUTPUT);
	_delay_ms(20);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);

#endif
	LCD_sendCommand(LCD_CURSOR_OFF);
	LCD_sendCommand(LCD_CLEAR_COMMAND);
}

/*Send commad*/
void LCD_sendCommand(uint8 command)
{
	GPIO_writePin(RS_PORT, RS_PIN, LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(ENABLE_PORT, ENABLE_PIN, LOGIC_HIGH);
	_delay_ms(1);
#if(LCD_DATA_BITS_MODE == 8)
	GPIO_writePort(LCD_DATA_PORT, command);

#elif(LCD_DATA_BITS_MODE == 4)
	GPIO_writePin(LCD_DATA_PORT,LCD_DATA_PIN_1,GET_BIT(command,4));
	GPIO_writePin(LCD_DATA_PORT,LCD_DATA_PIN_2,GET_BIT(command,5));
	GPIO_writePin(LCD_DATA_PORT,LCD_DATA_PIN_3,GET_BIT(command,6));
	GPIO_writePin(LCD_DATA_PORT,LCD_DATA_PIN_4,GET_BIT(command,7));

	_delay_ms(1);
	GPIO_writePin(ENABLE_PORT, ENABLE_PIN, LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(ENABLE_PORT,ENABLE_PIN,LOGIC_HIGH);
	_delay_ms(1);

	GPIO_writePin(LCD_DATA_PORT,LCD_DATA_PIN_1,GET_BIT(command,0));
	GPIO_writePin(LCD_DATA_PORT,LCD_DATA_PIN_2,GET_BIT(command,1));
	GPIO_writePin(LCD_DATA_PORT,LCD_DATA_PIN_3,GET_BIT(command,2));
	GPIO_writePin(LCD_DATA_PORT,LCD_DATA_PIN_4,GET_BIT(command,3));

#endif

	_delay_ms(1);
	GPIO_writePin(ENABLE_PORT, ENABLE_PIN, LOGIC_LOW);
	_delay_ms(1);
}

/*Display character*/
void LCD_displayCharacter(uint8 character)
{
	GPIO_writePin(RS_PORT, RS_PIN, LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePin(ENABLE_PORT, ENABLE_PIN, LOGIC_HIGH);
	_delay_ms(1);

#if(LCD_DATA_BITS_MODE == 8)
	GPIO_writePort(LCD_DATA_PORT, character);

#elif(LCD_DATA_BITS_MODE == 4)
	GPIO_writePin(LCD_DATA_PORT,LCD_DATA_PIN_1,GET_BIT(character,4));
	GPIO_writePin(LCD_DATA_PORT,LCD_DATA_PIN_2,GET_BIT(character,5));
	GPIO_writePin(LCD_DATA_PORT,LCD_DATA_PIN_3,GET_BIT(character,6));
	GPIO_writePin(LCD_DATA_PORT,LCD_DATA_PIN_4,GET_BIT(character,7));

	_delay_ms(1);
	GPIO_writePin(ENABLE_PORT, ENABLE_PIN, LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(ENABLE_PORT,ENABLE_PIN,LOGIC_HIGH);
	_delay_ms(1);

	GPIO_writePin(LCD_DATA_PORT,LCD_DATA_PIN_1,GET_BIT(character,0));
	GPIO_writePin(LCD_DATA_PORT,LCD_DATA_PIN_2,GET_BIT(character,1));
	GPIO_writePin(LCD_DATA_PORT,LCD_DATA_PIN_3,GET_BIT(character,2));
	GPIO_writePin(LCD_DATA_PORT,LCD_DATA_PIN_4,GET_BIT(character,3));

#endif

	_delay_ms(1);
	GPIO_writePin(ENABLE_PORT, ENABLE_PIN, LOGIC_LOW);
	_delay_ms(1);
}

/*Display string*/
void LCD_displayString(const uint8* str)
{
	uint8 i = 0;
	while(str[i] != '\0')
	{
		LCD_displayCharacter(str[i]);
		i++;
	}
}

/*Change cursor position*/
void LCD_moveCursor(uint8 row,uint8 col)
{
	uint8 lcd_memory_address;

	/* Calculate the required address in the LCD DDRAM */
	switch(row)
	{
	case 0:
		lcd_memory_address=col;
		break;
	case 1:
		lcd_memory_address=col+0x40;
		break;
	case 2:
		lcd_memory_address=col+0x10;
		break;
	case 3:
		lcd_memory_address=col+0x50;
		break;
	}
	/* Move the LCD cursor to this specific address */
	LCD_sendCommand(lcd_memory_address | LCD_SET_CURSOR_LOCATION);
}

/*Integer display*/
void LCD_intgerToString(int data)
{
   char buff[16]; /* String to hold the ascii result */
   itoa(data,buff,10); /* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
   LCD_displayString(buff); /* Display the string */
}

 /*Float display*/
void LCD_floatToString(float32 data)
{
	uint8 buff[16]; /* String to hold the ascii result */
	itoa((int)data,buff,10); /* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
	LCD_displayString(buff);
	LCD_displayCharacter('.');
	data -= (int)data;
	data*=1000;
	itoa((int)data,buff,10);
	LCD_displayString(buff);

}

/*Clear screen*/
void LCD_clearScreen(void)
{
	LCD_sendCommand(LCD_CLEAR_COMMAND); /* Send clear display command */
}





