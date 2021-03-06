/*
============================================================================
 Name        : DCMotor.c
 Data        : 6 - 6 -2022
 Author      : Ahmed_Hossam
 Description : DC Motor Driver
 ============================================================================
 */

#include "MOTOR.h"
#include "gpio.h"
#include "common_macros.h"

/*Description:
 * 1- The Function responsible for setup the direction for the two motor pins
 *  through the GPIO driver.
 * 2- Stop at the DC-Motor at the beginning through the GPIO driver. */
void DcMotor_Init(void)
{
	GPIO_setupPinDirection(MOTOR_PORT_ID, MOTOR_PIN0_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(MOTOR_PORT_ID, MOTOR_PIN1_ID, PIN_OUTPUT);
	GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN0_ID, LOGIC_LOW);
	GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN1_ID, LOGIC_LOW);
	return ;
}

/*Description:
 *1- The function responsible for rotate the DC Motor CW/ or A-CW or
 *   stop the motor based on the state input state value.
 */
void DcMotor_Rotate(uint8 direction)
{
	if(direction == MOTOR_CCW){
	GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN0_ID, LOGIC_HIGH);
	GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN1_ID, LOGIC_LOW);
	}
	else if (direction == MOTOR_CW)
	{
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN0_ID, LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN1_ID, LOGIC_HIGH);
	}
	else if (direction == MOTOR_STOP)
	{
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN0_ID, LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN1_ID, LOGIC_LOW);
	}
	return;
}




