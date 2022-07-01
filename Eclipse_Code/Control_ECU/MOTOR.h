/*
============================================================================
 Name        : DCMotor.h
 Data        : 6 - 6 -2022
 Author      : Ahmed_Hossam
 Description : DC Motor Driver
 ============================================================================
*/

#include "std_types.h"

#ifndef MOTOR_H_
#define MOTOR_H_

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define MOTOR_PORT_ID PORTD_ID
#define MOTOR_PIN0_ID  PIN2_ID
#define MOTOR_PIN1_ID  PIN3_ID

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum
{
	MOTOR_STOP,MOTOR_CW, MOTOR_CCW
}DCMOTOR_State;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/


/*Description:
 * 1- The Function responsible for setup the direction for the two motor pins
 *  through the GPIO driver.
 * 2- Stop at the DC-Motor at the beginning through the GPIO driver. */
void DcMotor_Init(void);

/*Description:
 *1- The function responsible for rotate the DC Motor CW/ or A-CW or
 *   stop the motor based on the state input state value.
 */
void DcMotor_Rotate(uint8 direction);

#endif /* MOTOR_H_ */
