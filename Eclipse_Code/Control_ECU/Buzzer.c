/*
============================================================================
 Name        : Buzzer.c
 Data        : 26 - 5 -2022
 Author      : Ahmed_Hossam
 Description : Buzzer Driver
 ============================================================================
 */

#include "gpio.h"
#include <avr/io.h>
#include "Buzzer.h"
#include <util/delay.h>

/*Description:
 *    Function to initialize the Buzzer by set the connected pin as output
 * */
void BUZZER_init(void)
{
	GPIO_setupPinDirection(BUZZER_PORT_ID, BUZZER_PIN_ID, PIN_OUTPUT);
	return;
}

/*Description:
 *    Function to start the Buzzer
 * */
void BUZZER_start(void)
{
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_HIGH);
	_delay_ms(10);
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);
	return;
}

