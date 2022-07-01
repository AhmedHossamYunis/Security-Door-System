/*
 ============================================================================
 Name        : CONTROL_ECU.h
 Data        : 7 - 6 -2022
 Author      : Ahmed_Hossam
 Description : Security Door System
 ============================================================================
 */

#ifndef CONTROL_HEADER_H_
#define CONTROL_HEADER_H_

#include "I2C.h"
#include "Buzzer.h"
#include "EEPROM.h"
#include "USART.h"
#include "MOTOR.h"
#include "Timer.h"
#include "avr/interrupt.h"
#include <util/delay.h>


/*******************************************************************************
 *                                Definition                                   *
 *******************************************************************************/

#define WRONG        0
#define INITIAL      1
#define READY        2
#define OPEN_DOOR    3
#define CHANGE_PASS  5
#define SAVED        6
#define MATCH        8
#define NOT_MATCH    9
#define ALARM        10
#define ARR_SIZE     5
#define OPEN_MOTOR_TIMER_PER_SECOND 450
#define CLOSE_MOTOR_TIMER_PER_SECOND 900
#define CLOSE_BUZZER_TIMER_FOR_ONE_MIN 1860



/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description:
 * 	  1- Receive the new password.
 * 	  2- Receive the confirmation password.
 * 	  3- Compare between them.
 * 	  4- In case of the two passwords are not matched return not match.
 * 	  5- In case of the two passwords are matched return wrong.
 * */
uint8 CONTROL_receivePass(void);

/*
 * Description:
 * 	  1- Receive the entered password.
 * 	  2- Get the stored password.
 * 	  3- Compare between them.
 * 	  4- In case of the two passwords are not matched return not match.
 * 	  5- In case of the two passwords are matched return wrong.
 * */
uint8 CONTROL_matchPassword(void);

/*
 * Description:
 *		Function to rotate the motor to open the door
 * */
void CONTROL_motorOpen(void);

/*
 * Description:
 *		Function to rotate the motor to close the door
 * */
void CONTROL_motorClose(void);

/*
 * Description:
 *		Function to stop the motor.
 * */
void CONTROL_motorStop(void);

/*
 * Description:
 *		Function to rotate the motor 15 second in clockwise direction
 *		and 15 seconds in counter clockwise direction.
 * */
void CONTROL_motorProcessing(void);

/*
 * Description:
 *		Function to start the alarm for 1 minute.
 * */
void CONTROL_Buzzer(void);

/*
 * Description:
 *		Function to start buzzer and stop after one minute
 * */
void CONTROL_buzzerProcessing(void);


#endif /* CONTROL_HEADER_H_ */
