/*
 *  File name: uart.h
 *  Description: Header file for UART driver
 *  Created on: Oct 31, 2024
 *  Author: Malak Waleed
 */

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

typedef enum {
	CharacterSize_5bit = 0,
	CharacterSize_6bit,
	CharacterSize_7bit,
	CharacterSize_8bit,
	CharacterSize_9bit = 7
}UART_BitDataType;

typedef enum {
	DisabledParity = 0,
	EvenParity = 2,
	OddParity = 3
}UART_ParityType;

typedef enum {
	STOPBIT_1bit = 0,
	STOPBIT_2bit = 1
}UART_StopBitType;

typedef uint32 UART_BaudRateType;

typedef struct {
	UART_BitDataType bit_data;
	UART_ParityType parity;
	UART_StopBitType stop_bit;
	UART_BaudRateType baud_rate;
}UART_ConfigType;

void UART_init(const UART_ConfigType * Config_Ptr);

void UART_sendByte(const uint8 data);
uint8 UART_recieveByte(void);
void UART_sendString(const uint8 *Str);
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
