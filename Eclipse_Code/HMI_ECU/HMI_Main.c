/*
 ============================================================================
 Name        : HMI_ECU
 Data        : 10 - 6 -2022
 Author      : Ahmed_Hossam
 Description : security door system
 ============================================================================
 */

#include "HMI_header.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

extern volatile uint8 open_flag;
extern volatile uint8 stop_flag;
extern volatile uint8 stop_buzzer;

/*******************************************************************************
 *                               HMI ECU MAIN                                  *
 *******************************************************************************/


int main()
{
	/* Configuration of USART:
	 * 1- Bit rate = 9600.
	 * 2- Parity is disabled.
	 * 3- No of stop bits = 1.
	 * 4- No of data bit = 8 bits.
	 * */
	USART_configType config_UART = {9600, DISABLED, ONE_BIT, EIGHT_BITS};
	/* Configuration of Timer:
	 * 1- Compare value = 255 in case of working in compare mode.
	 * 2- Configure the timer to work in normal mode.
	 * 3- Prescaler = F_CPU/1024
	 * 4- Normal port operation OC0 is disconnected
	 * 5- insert the initial value = 0.
	 * 6- Insert the channel in case of TIMER 1.
	 * */
	TIMER_ConfigType config_Timer_Motor = {255,NORMAL_MODE, F_CPU_1024, NORMAL_MATCH, 0,'A'};
	/* Configuration of Timer:
	 * 1- Compare value = 255.
	 * 2- Configure the timer to work in compare mode.
	 * 3- Prescaler = F_CPU/1024
	 * 4- Normal port operation OC0 is disconnected
	 * 5- insert the initial value = 0.
	 * 6- Insert the channel in case of TIMER 1.
	 * */
	TIMER_ConfigType config_Timer_Buzzer = {255,COMPARE, F_CPU_1024, NORMAL_MATCH, 0,'A'};

	uint8 state = INITIAL;
	uint8 check = WRONG;
	uint8 errorPass = 0;
	volatile uint32 cnt;

	LCD_init();

	USART_init(&config_UART);
	/*Enable global interrupt*/
	sei();

	while(1)
	{
		/*In case of the system works in the first time or the user wants
		 * to change the password*/
		while((state == INITIAL) && (check == WRONG))
		{

			HMI_setNewPassword();
			while((HMI_confirmPass()) != READY);
			check = HMI_matchPass();
			LCD_clearScreen();
			if(check == MATCH)
			{
				LCD_displayStringRowColumn(0,4, "Success");
				for (cnt = 128000; cnt; cnt--);
				break;
			}
			else
			{
				LCD_displayStringRowColumn(0,0, "In valid pass");
				state = INITIAL;
				check = WRONG;
				for (cnt = 128000; cnt; cnt--);
			}

		}

		/*After setting the new password the main menu starts to display
		 * In case of press + --> the door will open for 15 and close for 15 sec
		 * In case of press - --> Change the password
		 * In case of the password is wrong for 3 times --> Alarm will turn on for 1 minute
		 *  */
		HMI_mainOption();
		state = HMI_chooseOption();

		if(state == OPEN_DOOR)
		{
			check = HMI_enterPass();
			if(check == MATCH)
			{
				TIMER_SetCallBack(HMI_LCDProcessing);
				errorPass = 0;
				USART_sendByte(MATCH);
				TIMER_init(TIMER_0 ,&config_Timer_Motor);

				LCD_clearScreen();
				LCD_displayStringRowColumn(0,0,"Door is opening ");
				while(open_flag != 1);

				stop_flag = 0;
				LCD_displayStringRowColumn(0,0,"Door is closing");
				while(stop_flag != 1);

				TIMER_Deinit(TIMER_0);

				open_flag = 0;
				stop_flag = 0;

			}
			if (check == NOT_MATCH)
			{
				errorPass++;
				LCD_clearScreen();
				TIMER_SetCallBack(HMI_buzzerProcessing);
				if(errorPass >= 3)
				{
					state = NOT_INITIAL;
					TIMER_init(TIMER_0, &config_Timer_Buzzer);
					HMI_Buzzer();
					TIMER_Deinit(TIMER_0);
					stop_buzzer = 0;
				}
				else
				{
					LCD_displayStringRowColumn(0,0, "In valid input");
					for (cnt = 128000; cnt; cnt--);
				}
			}
		}
		else if (state == CHANGE_PASS)
		{
			check = HMI_enterPass();
			if(check == MATCH)
			{
				errorPass = 0;
				state = INITIAL;
				check = WRONG;
			}
			if (check == NOT_MATCH)
			{
				errorPass++;
				LCD_clearScreen();
				TIMER_SetCallBack(HMI_buzzerProcessing);
				if(errorPass >= 3)
				{
					state = NOT_INITIAL;
					TIMER_init(TIMER_0, &config_Timer_Buzzer);
					HMI_Buzzer();
					TIMER_Deinit(TIMER_0);
					stop_buzzer = 0;
				}
				else
				{
					LCD_displayStringRowColumn(0,0, "In valid input");
					for (cnt = 128000; cnt; cnt--);
				}
			}
		}
		else if(state == NOT_INITIAL)
		{
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"In valid input");
			for (cnt = 128000; cnt; cnt--);
			state = NOT_INITIAL;
		}
		else
		{
			state = INITIAL;
			check = WRONG;
		}
	}
}

