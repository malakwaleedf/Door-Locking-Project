/*
 *  File name: lcd.h
 *  Description: Header file for LCD driver
 *  Created on: Oct 5, 2024
 *  Author: Malak Waleed
 */

#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"

/*LCD controls config*/
#define RS_PORT PORTC_ID
#define RS_PIN PIN0_ID

#define ENABLE_PORT PORTC_ID
#define ENABLE_PIN PIN1_ID

/*LCD mode config, 4 or 8*/
#define LCD_DATA_BITS_MODE 8

/*to make sure the LCD mode is configured right*/
#if((LCD_DATA_BITS_MODE != 4) && (LCD_DATA_BITS_MODE != 8))
#error "LCD mode is either 8-bit data or 4-bit data"
#endif

#if(LCD_DATA_BITS_MODE == 8)
#define LCD_DATA_PORT PORTA_ID

#elif(LCD_DATA_BITS_MODE == 4)
#define LCD_DATA_PORT PORTA_ID

#define LCD_DATA_PIN_1 PIN3_ID
#define LCD_DATA_PIN_2 PIN4_ID
#define LCD_DATA_PIN_3 PIN5_ID
#define LCD_DATA_PIN_4 PIN6_ID
#endif

/* LCD Commands */
#define LCD_CLEAR_COMMAND                    0x01
#define LCD_GO_TO_HOME                       0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE        0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define LCD_CURSOR_OFF                       0x0C
#define LCD_CURSOR_ON                        0x0E
#define LCD_SET_CURSOR_LOCATION              0x80

/*Functions prototypes*/

/*LCD init*/
void LCD_init(void);

/*Send commad*/
void LCD_sendCommand(uint8 command);

/*Display character*/
void LCD_displayCharacter(uint8 character);

/*Display string*/
void LCD_displayString(const uint8* str);

/*Change cursor position*/
void LCD_moveCursor(uint8 row, uint8 col);

/*Integer display*/
void LCD_intgerToString(int data);

/*Float display*/
void LCD_floatToString(float32 data);

/*Clear screen*/
void LCD_clearScreen(void);


#endif /* LCD_H_ */
