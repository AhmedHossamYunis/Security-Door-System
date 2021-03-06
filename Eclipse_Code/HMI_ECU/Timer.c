/*
============================================================================
 Name        : Timer.c
 Data        : 5 - 6 -2022
 Author      : Ahmed_Hossam
 Description : Timer Driver
 ============================================================================
 */


#include "Timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "common_macros.h"
/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

static volatile void (*g_callBack_ptr)(void) = NULL_PTR;  /*Timer 0*/

static volatile void (*g_callBack_ptr1)(void) = NULL_PTR; /*Timer 1*/

static volatile void (*g_callBack_ptr2)(void) = NULL_PTR; /*Timer 2*/


/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/


ISR(TIMER0_OVF_vect)
{

	if(g_callBack_ptr != NULL_PTR)
	{
		/* Call the call back function in the application after counting the required time*/
		(*g_callBack_ptr)();
	}

}
ISR(TIMER0_COMP_vect)
{
	if(g_callBack_ptr != NULL_PTR)
	{
		/* Call the call back function in the application after counting the required time*/
		(*g_callBack_ptr)();
	}

}

ISR(TIMER1_OVF_vect)
{

	if(g_callBack_ptr != NULL_PTR)
	{
		/* Call the call back function in the application after counting the required time*/
		(*g_callBack_ptr)();
	}

}
ISR(TIMER1_COMPA_vect)
{
	if(g_callBack_ptr != NULL_PTR)
	{
		/* Call the call back function in the application after counting the required time*/
		(*g_callBack_ptr)();
	}

}

ISR(TIMER1_COMPB_vect)
{
	if(g_callBack_ptr != NULL_PTR)
	{
		/* Call the call back function in the application after counting the required time*/
		(*g_callBack_ptr)();
	}

}


ISR(TIMER2_OVF_vect)
{

	if(g_callBack_ptr != NULL_PTR)
	{
		/* Call the call back function in the application after counting the required time*/
		(*g_callBack_ptr)();
	}

}
ISR(TIMER2_COMP_vect)
{
	if(g_callBack_ptr != NULL_PTR)
	{
		/* Call the call back function in the application after counting the required time*/
		(*g_callBack_ptr)();
	}

}


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*Description:
 *   1- Set Non-PWM mode
 *   2- Insert the required mode.
 *   3- Insert the required compare match mode.
 *   4- Insert the required prescaler.
 *   5- Insert the required initial time value.
 *   6- Insert the compare mode time value in case of Compare mode is inserted.
 *   7- Enable timer interrupt module.
 *   8- Insert the required timer --> 0, 1 or 2.
 *   9- In case of timer1 --> Insert the required channel -> A or B.
 **/
void TIMER_init(uint8 timerNo,const TIMER_ConfigType *config){

	if(timerNo == TIMER_0)
	{
		/*Non PWM mode*/
		SET_BIT(TCCR0,FOC0);

		/*Insert the required prescaler*/
		TCCR0 = (TCCR0 & 0xF8) | ((config->prescaler));

		/*Insert the required initial time value*/
		TCNT0 = config->Timer_Initial_Time_Value;

		if ((config->mode) == COMPARE)
		{

			/*Insert the required mode */
			CLEAR_BIT(TCCR0, WGM00);
			SET_BIT(TCCR0, WGM01);

			/*Insert the required compare time value.*/
			OCR0 = config->Timer_Compare_Time_Value;

			/*Insert the required the compare output mode*/
			TCCR0 = (TCCR0 & 0xCF) | ((config->compareMatch)<<4);


			/*Enable interrupt for compare mode*/
			SET_BIT(TIMSK, OCIE0);
		}
		else if((config->mode) == NORMAL_MODE)
		{
			/*The required mode */
			CLEAR_BIT(TCCR0, WGM00);
			CLEAR_BIT(TCCR0, WGM01);

			/*Enable interrupt for normal mode*/
			SET_BIT(TIMSK, TOIE0);
		}
	}
	else if(timerNo == TIMER_1)
	{
		SET_BIT(TCCR1A,FOC1A);
		SET_BIT(TCCR1A,FOC1B);

		TCNT1 = config->Timer_Initial_Time_Value;

		TCCR1B = (TCCR1B & 0xF8) | (config->prescaler);

		if ((config->mode) == COMPARE)
		{
			TCCR1A = (TCCR1A & 0x0F) | ((config->compareMatch)<<4);

			CLEAR_BIT(TCCR1A, WGM10);
			CLEAR_BIT(TCCR1A, WGM11);
			SET_BIT(TCCR1B,WGM12);
			CLEAR_BIT(TCCR1B, WGM13);

			if((config->channel) == 'A')
			{
				OCR1A = config->Timer_Compare_Time_Value;

				/*Enable interrupt for normal mode*/
				SET_BIT(TIMSK, OCIE1A);
			}
			else if ((config->channel) == 'B')
			{
				OCR1B = config->Timer_Compare_Time_Value;

				/*Enable interrupt for normal mode*/
				SET_BIT(TIMSK, OCIE1B);
			}

		}
		else if((config->mode) == NORMAL_MODE)
		{
			CLEAR_BIT(TCCR1A, COM1B0);
			CLEAR_BIT(TCCR1A, COM1B1);
			CLEAR_BIT(TCCR1A, COM1A0);
			CLEAR_BIT(TCCR1A, COM1A1);

			CLEAR_BIT(TCCR1A, WGM10);
			CLEAR_BIT(TCCR1A, WGM11);
			CLEAR_BIT(TCCR1B, WGM12);
			CLEAR_BIT(TCCR1B, WGM13);

			/*Enable interrupt for normal mode*/
			SET_BIT(TIMSK, TOIE1);
		}
	}
	else if(timerNo == TIMER_2)
	{
		/*Non PWM mode*/
		SET_BIT(TCCR2,FOC2);

		/*Insert the required prescaler*/
		TCCR2 = (TCCR2 & 0xF8) | ((config->prescaler));

		/*Insert the required initial time value*/
		TCNT2 = config->Timer_Initial_Time_Value;

		if ((config->mode) == COMPARE)
		{

			/*Insert the required mode */
			CLEAR_BIT(TCCR2, WGM20);
			SET_BIT(TCCR2, WGM21);

			/*Insert the required compare time value.*/
			OCR2 = config->Timer_Compare_Time_Value;

			/*Insert the required the compare output mode*/
			TCCR2 = (TCCR2 & 0xCF) | ((config->compareMatch)<<4);


			/*Enable interrupt for compare mode*/
			SET_BIT(TIMSK, OCIE2);
		}
		else if((config->mode) == NORMAL_MODE)
		{
			/*The required mode */
			CLEAR_BIT(TCCR2, WGM20);
			CLEAR_BIT(TCCR2, WGM21);

			/*Enable interrupt for normal mode*/
			SET_BIT(TIMSK, TOIE2);
		}
	}

	return;
}

/*Description:
 *   1- Insert the required timer to stop it
 *  */
void TIMER_Deinit(uint8 timer_type)
{
	if(timer_type == TIMER_0)
	{
		TCCR0 = 0;
		TIMSK = 0;
	}
	else if(timer_type == TIMER_1)
	{
		TCCR1A = 0;
		TCCR1B = 0;
		OCR1A = 0;
		TIMSK = 0;
	}
	else if (timer_type == TIMER_2)
	{
		TCCR2 = 0;
		TIMSK = 0;
	}

}

/*Description:
 *   Function to set call back function address.
 * */
void TIMER_SetCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBack_ptr = (void*)a_ptr;
}

/*Description:
 *   Function to set call back function address for timer 1.
 * */
void TIMER1_SetCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBack_ptr1 = (void*)a_ptr;
}

/*Description:
 *   Function to set call back function address for timer 2.
 * */
void TIMER2_SetCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBack_ptr2 = (void*)a_ptr;
}

