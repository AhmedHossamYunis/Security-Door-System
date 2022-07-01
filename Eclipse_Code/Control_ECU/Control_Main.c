/*
 ============================================================================
 Name        : CONTROL_ECU
 Data        : 10 - 6 -2022
 Author      : Ahmed_Hossam
 Description : Security Door System
 ============================================================================
 */

#include "Control_header.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

extern volatile uint8 open_flag;
extern volatile uint8 close_flag;
extern volatile uint8 stop_flag;
extern volatile uint8 stop_buzzer;


/*******************************************************************************
 *                               CONTROL ECU MAIN                              *
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
	/* Configuration of EEPROM:
	 * 1- Insert the address of the slave device.
	 * Insert the bit rate
	 * */
	TWI_ConfingType configeeprom = {0x01,0x02}; /*Enter the address then bit rate*/

	uint8 state = INITIAL;
	uint8 check = WRONG;
	uint8 errorPass = 0;

	TWI_init(&configeeprom);

	USART_init(&config_UART);

	BUZZER_init();

	DcMotor_Init();

	/*Enable general interrupt*/
	sei();

	while(1)
	{
		/*In case of the system works in the first time or the user wants
		 * to change the password*/
		while((state == INITIAL) && (check == WRONG))
		{

			check = CONTROL_receivePass();
		}

		/*When HMI_ECU sends Ready, CONTROL_ECU will start to receive open the door or change password
		 * In case of the password is wrong for 3 times --> Alarm will turn on for 1 minute
		 * */
		while(USART_receiveByte() != READY);
		state = USART_receiveByte();

		if(state == OPEN_DOOR)
		{
			check = CONTROL_matchPassword();
			if(check == MATCH)
			{
				TIMER_SetCallBack(CONTROL_motorProcessing);
				errorPass = 0;
				TIMER_init(TIMER_0,&config_Timer_Motor);

				CONTROL_motorOpen();

				close_flag = 0;
				CONTROL_motorClose();

				stop_flag = 0;
				CONTROL_motorStop();

				open_flag = 0;
				close_flag = 0;
				stop_flag = 0;

				TIMER_Deinit(TIMER_0);
			}
			if (check == NOT_MATCH)
			{
				errorPass++;
				TIMER_SetCallBack(CONTROL_buzzerProcessing);
				if(errorPass >= 3)
				{
					TIMER_init(TIMER_0,&config_Timer_Buzzer);
					CONTROL_Buzzer();
					TIMER_Deinit(TIMER_0);
					stop_buzzer = 0;
				}
			}
		}
		else if (state == CHANGE_PASS)
		{
			check = CONTROL_matchPassword();
			if(check == MATCH)
			{
				errorPass = 0;
				state = INITIAL;
				check = WRONG;
			}
			if (check == NOT_MATCH)
			{

				errorPass++;
				TIMER_SetCallBack(CONTROL_buzzerProcessing);
				if(errorPass >= 3)
				{
					TIMER_init(TIMER_0,&config_Timer_Buzzer);
					CONTROL_Buzzer();
					TIMER_Deinit(TIMER_0);
					stop_buzzer = 0;
				}
			}
		}
		else
		{
			state = INITIAL;
			check = WRONG;
		}
	}
}
