/*
 *  File name: timer.c
 *  Description: Source file for Timer driver
 *  Created on: Oct 31, 2024
 *  Author: Malak Waleed
 */

#include "timer.h"
#include "common_macros.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/*static volatile void(*g_timer0NormalModeCallBackFuncPtr)(void) = NULL_PTR;
static volatile void(*g_timer0CompareModeCallBackFuncPtr)(void) = NULL_PTR;

static volatile void(*g_timer1NormalModeCallBackFuncPtr)(void) = NULL_PTR;
static volatile void(*g_timer1CompareModeCallBackFuncPtr)(void) = NULL_PTR;

static volatile void(*g_timer2NormalModeCallBackFuncPtr)(void) = NULL_PTR;
static volatile void(*g_timer2CompareModeCallBackFuncPtr)(void) = NULL_PTR;*/

static volatile void(*g_timer0CallBackFuncPtr)(void) = NULL_PTR;
static volatile void(*g_timer1CallBackFuncPtr)(void) = NULL_PTR;
static volatile void(*g_timer2CallBackFuncPtr)(void) = NULL_PTR;

static char g_timer0Mode = 0;
static char g_timer1Mode = 0;
static char g_timer2Mode = 0;

/*interrupt service routine of timer0 in normal mode*/
ISR(TIMER0_OVF_vect)
{
	if(g_timer0CallBackFuncPtr != NULL_PTR)
	{
		(*g_timer0CallBackFuncPtr)();
	}
}

/*interrupt service routine of timer0 in compare mode*/
ISR(TIMER0_COMP_vect)
{
	if(g_timer0CallBackFuncPtr != NULL_PTR)
	{
		(*g_timer0CallBackFuncPtr)();
	}
}

/*interrupt service routine of timer1 in normal mode*/
ISR(TIMER1_OVF_vect)
{
	if(g_timer1CallBackFuncPtr != NULL_PTR)
	{
		(*g_timer1CallBackFuncPtr)();
	}
}

/*interrupt service routine of timer1 in compare mode*/
ISR(TIMER1_COMPA_vect)
{
	if(g_timer1CallBackFuncPtr != NULL_PTR)
	{
		(*g_timer1CallBackFuncPtr)();
	}
}

/*interrupt service routine of timer2 in normal mode*/
ISR(TIMER2_OVF_vect)
{
	if(g_timer2CallBackFuncPtr != NULL_PTR)
	{
		(*g_timer2CallBackFuncPtr)();
	}
}

/*interrupt service routine of timer2 in compare mode*/
ISR(TIMER2_COMP_vect)
{
	if(g_timer2CallBackFuncPtr != NULL_PTR)
	{
		(*g_timer2CallBackFuncPtr)();
	}
}

/*Function to initialize the Timer driver*/
void Timer_init(const Timer_ConfigType * Config_Ptr)
{
	if(Config_Ptr->timer_ID == TIMER0)
	{
		SET_BIT(TCCR0,FOC0);

		if(Config_Ptr->timer_mode == NORMAL_MODE)
		{
			SET_BIT(TIMSK,TOIE0);

			g_timer0Mode = NORMAL_MODE;
		}
		else if(Config_Ptr->timer_mode == COMPARE_MODE)
		{
			SET_BIT(TCCR0,WGM01);

			OCR0 = Config_Ptr->timer_compare_MatchValue;

			SET_BIT(TIMSK,OCIE0);

			g_timer0Mode = COMPARE_MODE;
		}

		TCCR0 = (TCCR0 & 0xF8) | (Config_Ptr->timer_clock & 0x07);

		TCNT0 = Config_Ptr->timer_InitialValue;
	}

	else if(Config_Ptr->timer_ID == TIMER1)
	{
		SET_BIT(TCCR1A,FOC1A);
		SET_BIT(TCCR1A,FOC1B);

		if(Config_Ptr->timer_mode == NORMAL_MODE)
		{
			SET_BIT(TIMSK,TOIE1);

			g_timer1Mode = NORMAL_MODE;
		}
		else if(Config_Ptr->timer_mode == COMPARE_MODE)
		{
			SET_BIT(TCCR1B,WGM12);

			/*Using channel A*/
			OCR1A = Config_Ptr->timer_compare_MatchValue;

			SET_BIT(TIMSK,OCIE1A);

			g_timer1Mode = COMPARE_MODE;
		}

		TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->timer_clock & 0x07);

		TCNT1 = Config_Ptr->timer_InitialValue;
	}

	else if(Config_Ptr->timer_ID == TIMER2)
	{
		SET_BIT(TCCR2,FOC2);

		if(Config_Ptr->timer_mode == NORMAL_MODE)
		{
			SET_BIT(TIMSK,TOIE2);

			g_timer2Mode = NORMAL_MODE;
		}
		else if(Config_Ptr->timer_mode == COMPARE_MODE)
		{
			SET_BIT(TCCR2,WGM21);

			OCR2 = Config_Ptr->timer_compare_MatchValue;

			SET_BIT(TIMSK,OCIE2);

			g_timer2Mode = COMPARE_MODE;
		}

		TCCR2 = (TCCR2 & 0xF8) | (Config_Ptr->timer_clock & 0x07);

		TCNT2 = Config_Ptr->timer_InitialValue;

	}

	else
	{

	}

}

/*Function to disable the Timer via Timer_ID*/
void Timer_deInit(Timer_ID_Type timer_type)
{
	if(timer_type == TIMER0)
	{
		TCCR0 = (TCCR0 & 0xF8) | (NO_CLOCK & 0x07); // check this
	}
	else if(timer_type == TIMER1)
	{
		TCCR1B = (TCCR1B & 0xF8) | (NO_CLOCK & 0x07); // check this
	}
	else if(timer_type == TIMER2)
	{
		TCCR2 = (TCCR2 & 0xF8) | (NO_CLOCK & 0x07); // check this
	}
	else
	{

	}

}

/*void Timer_setCallBack(void(*a_ptr)(void), Timer_ID_Type a_timer_ID )
{
	if(a_timer_ID == TIMER0)
	{
		if(g_timer0Mode == NORMAL_MODE)
		{
			g_timer0NormalModeCallBackFuncPtr = a_ptr;
		}
		else if(g_timer0Mode == COMPARE_MODE)
		{
			g_timer0CompareModeCallBackFuncPtr = a_ptr;
		}
	}
	else if(a_timer_ID == TIMER1)
	{
		if(g_timer1Mode == NORMAL_MODE)
		{
			g_timer1NormalModeCallBackFuncPtr = a_ptr;
		}
		else if(g_timer1Mode == COMPARE_MODE)
		{
			g_timer1CompareModeCallBackFuncPtr = a_ptr;
		}
	}
	else if(a_timer_ID == TIMER2)
	{
		if(g_timer2Mode == NORMAL_MODE)
		{
			g_timer2NormalModeCallBackFuncPtr = a_ptr;
		}
		else if(g_timer2Mode == COMPARE_MODE)
		{
			g_timer2CompareModeCallBackFuncPtr = a_ptr;
		}
	}
	else
	{

	}

}*/

/*Function to set the Call Back function address to the required Timer.*/
void Timer_setCallBack(void(*a_ptr)(void), Timer_ID_Type a_timer_ID )
{
	if(a_timer_ID == TIMER0)
	{
		g_timer0CallBackFuncPtr = a_ptr;
	}
	else if(a_timer_ID == TIMER1)
	{
		g_timer1CallBackFuncPtr = a_ptr;
	}
	else if(a_timer_ID == TIMER2)
	{
		g_timer2CallBackFuncPtr = a_ptr;
	}
	else
	{

	}
}













