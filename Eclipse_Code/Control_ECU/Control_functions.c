/*
 ============================================================================
 Name        : CONTROL_ECU.c
 Data        : 7 - 6 -2022
 Author      : Ahmed_Hossam
 Description : Security Door System
 ============================================================================
 */

#include "Control_header.h"
#include <util/delay.h>
#include <string.h>

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

volatile uint16 g_tick = 0;
volatile uint8 open_flag = 0;
volatile uint8 close_flag = 0;
volatile uint8 stop_flag = 0;
volatile uint8 stop_buzzer = 0;


/*******************************************************************************
 *                      Functions Definition                                   *
 *******************************************************************************/

/*
 * Description:
 *    Function to store the password after comparing them and they are matched.
 * */
static void storePassword(char *pass_ptr)
{
	uint8 i;

	for(i = 0; i<ARR_SIZE;i++)
	{
		EEPROM_writeByte(i,pass_ptr[i]);
		for (volatile long cnt = 10000; cnt; cnt--);
	}

}

/*
 * Description:
 * 	  1- Receive the new password.
 * 	  2- Receive the confirmation password.
 * 	  3- Compare between them.
 * 	  4- In case of the two passwords are not matched return not match.
 * 	  5- In case of the two passwords are matched return wrong.
 * */
uint8 CONTROL_receivePass(void)
{
	char pass1_arr[ARR_SIZE+1];
	char pass2_arr[ARR_SIZE+1];
	uint8 check;

	while(USART_receiveByte() != READY){};
	USART_receiveString(pass1_arr);

	while(USART_receiveByte() != READY){};
	USART_receiveString(pass2_arr);

	check = strcmp(pass1_arr, pass2_arr);

	if (check == 0)
	{

		storePassword(pass2_arr);
		while(USART_receiveByte() != READY);
		USART_sendByte(MATCH);
		return MATCH;
	}
	else
	{
		while(USART_receiveByte() != READY);
		USART_sendByte(WRONG);
		return WRONG;
	}
}

/*
 * Description:
 * 	  1- Receive the entered password.
 * 	  2- Get the stored password.
 * 	  3- Compare between them.
 * 	  4- In case of the two passwords are not matched return not match.
 * 	  5- In case of the two passwords are matched return match.
 * */
uint8 CONTROL_matchPassword(void)
{
	uint8 counter;
	uint8 checkMatch;
	char check;

	char passIsMatch_arr[ARR_SIZE+1];
	char storedPAss_arr[ARR_SIZE+1];

	while(USART_receiveByte() != READY);
	USART_receiveString(passIsMatch_arr);

	for(counter = 0; counter < ARR_SIZE; counter++ )
	{
		check = EEPROM_readByte(counter,&storedPAss_arr[counter]);


	}

	storedPAss_arr[counter] = '\0';

	checkMatch = strcmp(passIsMatch_arr, storedPAss_arr);

	if(checkMatch == 0)
	{
		while(USART_receiveByte() != READY);
		USART_sendByte(MATCH);
		return MATCH;
	}
	else
	{
		while(USART_receiveByte() != READY);
		USART_sendByte(NOT_MATCH);
		return NOT_MATCH;
	}
}

/*
 * Description:
 *		Function to rotate the motor to open the door
 * */
void CONTROL_motorOpen(void)
{
	DcMotor_Rotate(MOTOR_CCW);
	while(open_flag == 0);
}

/*
 * Description:
 *		Function to rotate the motor to close the door
 * */
void CONTROL_motorClose(void)
{
	DcMotor_Rotate(MOTOR_CW);
	while(close_flag != 1);
}

/*
 * Description:
 *		Function to stop the motor.
 * */
void CONTROL_motorStop(void)
{
	DcMotor_Rotate(MOTOR_STOP);
	while(stop_flag != 1);
}

/*
 * Description:
 *		Function to rotate the motor 15 second in clockwise direction
 *		and 15 seconds in counter clockwise direction.
 * */
void CONTROL_motorProcessing(void)
{
	g_tick++;

	if(g_tick == OPEN_MOTOR_TIMER_PER_SECOND)
	{
		open_flag = 1;

	}
	else if(g_tick == CLOSE_MOTOR_TIMER_PER_SECOND)
	{

		close_flag = 1;

	}
	else if(g_tick > CLOSE_MOTOR_TIMER_PER_SECOND)
	{
		g_tick = 0;
		stop_flag = 1;
	}
}

/*
 * Description:
 *		Function to start the alarm for 1 minute.
 * */
void CONTROL_Buzzer(void)
{
	while (1)
	{
		if(stop_buzzer > 0)
		{
			break;
		}
		else
		{
			BUZZER_start();
			for (volatile long cnt = 128000; cnt; cnt--);
		}
	}
}

/*
 * Description:
 *		Function to start buzzer and stop after one minute
 * */
void CONTROL_buzzerProcessing(void)
{
	g_tick++;

	if(g_tick == CLOSE_BUZZER_TIMER_FOR_ONE_MIN)
	{
		stop_buzzer = 1;

	}
	else if(g_tick > CLOSE_BUZZER_TIMER_FOR_ONE_MIN)
	{
		g_tick = 0;
	}
}







