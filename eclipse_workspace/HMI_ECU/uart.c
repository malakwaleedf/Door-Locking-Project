/*
 *  File name: uart.h
 *  Description: Source file for UART driver
 *  Created on: Oct 31, 2024
 *  Author: Malak Waleed
 */


#include "uart.h"
#include "avr/io.h"
#include "common_macros.h"

void UART_init(const UART_ConfigType * Config_Ptr)
{
	uint16 ubrr_value = 0;

	/* U2X = 1 for double transmission speed */
	UCSRA = (1<<U2X);

	/*Receiver and transmitter enable*/
	UCSRB = (1<<RXEN) | (1<<TXEN);

	/*URSEL must be set to write in UCSRC*/
	SET_BIT(UCSRC,URSEL);

	/*choose the character size*/
	if(Config_Ptr->bit_data == CharacterSize_9bit)
	{
		SET_BIT(UCSRB,UCSZ2);
		SET_BIT(UCSRB,UCSZ1);
		SET_BIT(UCSRB,UCSZ0);

	}
	else
	{
		CLEAR_BIT(UCSRB,UCSZ2);

		if(Config_Ptr->bit_data == CharacterSize_5bit)
		{
			CLEAR_BIT(UCSRB,UCSZ1);
			CLEAR_BIT(UCSRB,UCSZ0);
		}
		else if(Config_Ptr->bit_data == CharacterSize_6bit)
		{
			CLEAR_BIT(UCSRB,UCSZ1);
			SET_BIT(UCSRB,UCSZ0);
		}
		else if(Config_Ptr->bit_data == CharacterSize_7bit)
		{
			SET_BIT(UCSRB,UCSZ1);
			CLEAR_BIT(UCSRB,UCSZ0);
		}
		else if(Config_Ptr->bit_data == CharacterSize_8bit)
		{
			SET_BIT(UCSRB,UCSZ1);
			SET_BIT(UCSRB,UCSZ0);
		}
		else
		{

		}
	}

	/*Clear UMSEL for Asynchronous Operation*/
	CLEAR_BIT(UCSRC,UMSEL);

	/*choose the parity*/
	if(Config_Ptr->parity == DisabledParity)
	{
		CLEAR_BIT(UCSRC,UPM1);
		CLEAR_BIT(UCSRC,UPM0);
	}
	else if(Config_Ptr->parity == EvenParity)
	{
		SET_BIT(UCSRC,UPM1);
		CLEAR_BIT(UCSRC,UPM0);
	}
	else if(Config_Ptr->parity == OddParity)
	{
		SET_BIT(UCSRC,UPM1);
		SET_BIT(UCSRC,UPM0);
	}
	else
	{

	}

	/*choose #stopbits*/
	if(Config_Ptr->stop_bit == STOPBIT_1bit)
	{
		CLEAR_BIT(UCSRC,USBS);
	}
	else if(Config_Ptr->stop_bit == STOPBIT_2bit)
	{
		SET_BIT(UCSRC,USBS);
	}
	else
	{

	}

	/* Calculate the UBRR register value */
	ubrr_value = (uint16)(((F_CPU / (Config_Ptr->baud_rate * 16UL))) - 1);

	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	UBRRH = ubrr_value>>8;
	UBRRL = ubrr_value;
}

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data)
{
	/*
	 * UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one
	 */
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}

	/*
	 * Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now
	 */
	UDR = data;

	/************************* Another Method *************************
	UDR = data;
	while(BIT_IS_CLEAR(UCSRA,TXC)){} // Wait until the transmission is complete TXC = 1
	SET_BIT(UCSRA,TXC); // Clear the TXC flag
	 *******************************************************************/
}

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void)
{
	/* RXC flag is set when the UART receive data so wait until this flag is set to one */
	while(BIT_IS_CLEAR(UCSRA,RXC)){}

	/*
	 * Read the received data from the Rx buffer (UDR)
	 * The RXC flag will be cleared after read the data
	 */
	return UDR;
}

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str)
{
	uint8 i = 0;

	/* Send the whole string */
	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}
	/************************* Another Method *************************
	while(*Str != '\0')
	{
		UART_sendByte(*Str);
		Str++;
	}
	 *******************************************************************/
}

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str)
{
	uint8 i = 0;

	/* Receive the first byte */
	Str[i] = UART_recieveByte();

	/* Receive the whole string until the '#' */
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_recieveByte();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	Str[i] = '\0';
}
