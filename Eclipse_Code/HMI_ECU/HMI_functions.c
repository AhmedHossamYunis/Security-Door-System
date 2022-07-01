/*
 ============================================================================
 Name        : HMI_ECU.c
 Data        : 7 - 6 -2022
 Author      : Ahmed_Hossam
 Description : Security Door System
 ============================================================================
 */

#include "HMI_header.h"

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
 *	Function to get the new password and send it to control EUC
 * */
void HMI_setNewPassword(void)
{
	char newPass_arr[ARR_SIZE + 2];
	uint8 counter;
	LCD_clearScreen();
	LCD_setCurser(0,0);
	LCD_displayString("New Password");

	for(counter = 0; counter<ARR_SIZE; counter++)
	{
		volatile uint32 cnt;
		newPass_arr[counter] = KEYPAD_getPressedKey();
		for (cnt = 109000; cnt; cnt--);

		if((newPass_arr[counter] >= 0) && (newPass_arr[counter] <= 9))
		{
			if(newPass_arr[counter] == 0)
			{
				/* replace zero by -1 to avoid conflict with null*/
				newPass_arr[counter] = -1;
				LCD_setCurser(1, counter);
				LCD_sendData('*');
			}
			else
			{
				LCD_setCurser(1, counter);
				LCD_sendData('*');
			}
		}
		else
		{
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"Invalid Data");
			for (cnt = 109000; cnt; cnt--);
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"New Password");
			counter = -1;
		}
	}
	newPass_arr[counter] = '#';
	counter++;
	newPass_arr[counter] = '\0';

	USART_sendByte(READY);
	USART_sendString(newPass_arr);


	return;
}

/*
 * Description:
 *	Function to get the confirmation password and send it to control EUC
 *	to compare if the two password are matched or not.
 * */
uint8 HMI_confirmPass(void)
{
	volatile uint32 cnt;
	char confPass_arr[ARR_SIZE + 2];
	uint8 counter;
	uint8 errorConfirm = 0;
	LCD_clearScreen();
	LCD_setCurser(0,0);
	LCD_displayString("Confirm Password");

	for(counter = 0; counter<ARR_SIZE; counter++)
	{
		confPass_arr[counter] = KEYPAD_getPressedKey();
		for (cnt = 109000; cnt; cnt--);

		if((confPass_arr[counter] >= 0) && (confPass_arr[counter] <= 9))
		{
			/* replace zero by -1 to avoid conflict with null*/
			if(confPass_arr[counter] == 0)
			{
				confPass_arr[counter] = -1;
				LCD_setCurser(1, counter);
				LCD_sendData('*');
			}
			else
			{
				LCD_setCurser(1, counter);
				LCD_sendData('*');

			}
		}
		else
		{
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"Invalid Data    ");
			for (cnt = 128000; cnt; cnt--);
			LCD_displayStringRowColumn(0,0,"Confirm Password");
			counter = -1;
			errorConfirm++;
			if(errorConfirm >= 5)
			{
				LCD_clearScreen();
				LCD_displayStringRowColumn(0,0,"Set New password");
				for (cnt = 128000; cnt; cnt--);
				break;
			}
		}
	}
	for(counter = 0; counter<ARR_SIZE; counter++)
	{
		if(confPass_arr[counter] == 0)
		{
			return WRONG;
		}
	}
	confPass_arr[counter] = '#';
	counter++;
	confPass_arr[counter] = '\0';

	USART_sendByte(READY);
	USART_sendString(confPass_arr);

	return READY;
}

/*
 * Description:
 *	  Function to get the password from the user and send it to control EUC
 * */
uint8 HMI_enterPass(void)
{
	volatile uint32 cnt;
	char enterPass[ARR_SIZE+2];
	uint8 counter;

	LCD_clearScreen();
	LCD_setCurser(0,0);
	LCD_displayString("Enter Password");

	for(counter = 0; counter<ARR_SIZE; counter++)
	{
		/* replace zero by -1 to avoid conflict with null*/
		enterPass[counter] = KEYPAD_getPressedKey();
		for (cnt = 109000; cnt; cnt--);

		if((enterPass[counter] >= 0) && (enterPass[counter] <= 9))
		{
			if(enterPass[counter] == 0)
			{
				enterPass[counter] = -1;
				LCD_setCurser(1, counter);
				LCD_sendData('*');
			}
			else
			{
				LCD_setCurser(1, counter);
				LCD_sendData('*');
			}
		}
		else
		{
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"Invalid Data");
			for (cnt = 128000; cnt; cnt--);
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"Enter Password");
			counter = -1;
		}
	}
	enterPass[counter] = '#';
	counter++;
	enterPass[counter] = '\0';

	USART_sendByte(READY);
	USART_sendString(enterPass);

	USART_sendByte(READY);
	return USART_receiveByte();
}


/*
 * Description:
 *	  Function that indicate if the entered password and the stored password
 *	  are matched or not
 * */
uint8 HMI_matchPass(void)
{
	USART_sendByte(READY);

	return USART_receiveByte();
}

/*
 * Description:
 *	  Function to display the main option of the system
 *	  + : open the door.
 *	  - : Change password.
 * */
void HMI_mainOption(void)
{
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "+: Open Door");
	LCD_displayStringRowColumn(1, 0, "-: Change Pass");

}

/*
 * Description:
 *	  Function to choose from the main options
 *	  + : open the door.
 *	  - : Change password.
 *	  and send it to CONTROL ECU
 * */
uint8 HMI_chooseOption(void)
{
	uint8 key_option;
	volatile uint32 cnt;
	key_option = KEYPAD_getPressedKey();
	for (cnt = 128000; cnt; cnt--);

	if((key_option == '+') || (key_option == '-'))
	{
		if(key_option == '+')
		{
			USART_sendByte(READY);
			USART_sendByte(OPEN_DOOR);
			return OPEN_DOOR;
		}
		else if(key_option == '-')
		{
			USART_sendByte(READY);
			USART_sendByte(CHANGE_PASS);
			return CHANGE_PASS;
		}
	}
	else
	{
		return NOT_INITIAL;

	}
	return NOT_INITIAL;
}

/*
 * Description:
 *	  Function to display the state of the door "Door is opening"
 *	  after choosing from the main option --> open the door for 15 seconds.
 * */
void HMI_openDoor(void)
{
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "Door is opening");
}

/*
 * Description:
 *	  Function to display the state of the door "Door is closing"
 *	  after choosing from the main option --> open the door for 15 seconds.
 * */
void HMI_closeDoor(void)
{
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "Door is closing");
}

/*
 * Description:
 *	  Function to manage the time of the motor:
 *	  1- 15 seconds rotates in clockwise direction
 *	  2- 15 seconds rotates in counter clockwise direction.
 *	  3- stop motor
 * */
void HMI_LCDProcessing(void)
{
	g_tick++;

	if(g_tick == OPEN_LCD_TIMER_PER_SECOND)
	{
		open_flag = 1;
	}
	else if(g_tick > CLOSE_LCD_TIMER_PER_SECOND)
	{
		g_tick = 0;
		stop_flag = 1;
	}
}

/*
 * Description:
 *		Function to start display the alarm for 1 minute.
 * */
void HMI_Buzzer(void)
{
	while (1)
	{
		if(stop_buzzer > 0)
		{
			break;
		}
		else
		{
			LCD_displayStringRowColumn(0,5, "Alarm");

		}
	}
}

/*
 * Description:
 *		Function to display alarm and stop after one minute
 * */
void HMI_buzzerProcessing(void)
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


