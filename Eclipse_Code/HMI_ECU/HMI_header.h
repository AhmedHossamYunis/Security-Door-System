/*
 ============================================================================
 Name        : HMI_ECU.h
 Data        : 7 - 6 -2022
 Author      : Ahmed_Hossam
 Description : Security Door System
 ============================================================================
 */

#ifndef HMI_HEADER_H_
#define HMI_HEADER_H_

#include "keypad.h"
#include "LCD.h"
#include "Timer.h"
#include "USART.h"
#include "avr/interrupt.h"
#include "gpio.h"

/*******************************************************************************
 *                            Definition                                       *
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
#define NOT_INITIAL  11

#define ARR_SIZE     5

#define OPEN_LCD_TIMER_PER_SECOND 450
#define CLOSE_LCD_TIMER_PER_SECOND 900
#define CLOSE_BUZZER_TIMER_FOR_ONE_MIN 1860



/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description:
 *	Function to get the new password and send it to control EUC
 * */
void HMI_setNewPassword(void);

/*
 * Description:
 *	Function to get the confirmation password and send it to control EUC
 *	to compare if the two password are matched or not.
 * */
uint8 HMI_confirmPass(void);

/*
 * Description:
 *	  Function to get the password from the user and send it to control EUC
 * */
uint8 HMI_enterPass(void);


/*
 * Description:
 *	  Function that indicate if the entered password and the stored password
 *	  are matched or not
 * */
uint8 HMI_matchPass(void);

/*
 * Description:
 *	  Function to display the main option of the system
 *	  + : open the door.
 *	  - : Change password.
 * */
void HMI_mainOption(void);

/*
 * Description:
 *	  Function to choose from the main options
 *	  + : open the door.
 *	  - : Change password.
 *	  and send it to CONTROL ECU
 * */
uint8 HMI_chooseOption(void);

/*
 * Description:
 *	  Function to display the state of the door "Door is opening"
 *	  after choosing from the main option --> open the door for 15 seconds.
 * */
void HMI_openDoor(void);

/*
 * Description:
 *	  Function to display the state of the door "Door is closing"
 *	  after choosing from the main option --> open the door for 15 seconds.
 * */
void HMI_closeDoor(void);

/*
 * Description:
 *	  Function to manage the time of the motor:
 *	  1- 15 seconds rotates in clockwise direction
 *	  2- 15 seconds rotates in counter clockwise direction.
 *	  3- stop motor
 * */
void HMI_LCDProcessing(void);

/*
 * Description:
 *		Function to start display the alarm for 1 minute.
 * */
void HMI_Buzzer(void);

/*
 * Description:
 *		Function to display alarm and stop after one minute
 * */
void HMI_buzzerProcessing(void);


#endif /* HMI_HEADER_H_ */
