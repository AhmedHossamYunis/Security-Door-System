/*
============================================================================
 Name        : Timer.h
 Data        : 5 - 6 -2022
 Author      : Ahmed_Hossam
 Description : Timer Driver
 ============================================================================
 */
#ifndef TIMER_H_
#define TIMER_H_
#include "std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/


typedef enum{
	NORMAL_MODE, COMPARE = 2
}TIMER_Mode;

typedef enum{
	NO_CLOCK_SOURCE, NO_PRESCALER, F_CPU_8, F_CPU_64, F_CPU_256, F_CPU_1024, EXTERNAL_FALLING_EDGE, EXTERNAL_RISING_EDGE
}TIMER_Prescaler;

typedef enum{
	NORMAL_MATCH, TOGGLE_ON_COMPARE_MATCH, CLEAR_ON_COMPARE_MATCH, SET_ON_COMPARE_MATCH
}TIMER_Compare_Mode_Match;

typedef struct{
	uint16 Timer_Compare_Time_Value;
	TIMER_Mode mode;
	TIMER_Prescaler prescaler;
	TIMER_Compare_Mode_Match compareMatch;
	uint8 Timer_Initial_Time_Value;
	uint8 channel;

}TIMER_ConfigType;

#define TIMER_0 0
#define TIMER_1 1
#define TIMER_2 2

/*******************************************************************************
 *                      Functions Prototypes                                   *
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
void TIMER_init(uint8 timerNo,const TIMER_ConfigType *config);

/*Description:
 *   1- Insert the required timer to stop it
 *  */
void TIMER_Deinit(uint8 timer_type);

/*Description:
 *   Function to set call back function address for timer 0.
 * */
void TIMER_SetCallBack(void(*a_ptr)(void));

/*Description:
 *   Function to set call back function address for timer 1.
 * */
void TIMER1_SetCallBack(void(*a_ptr)(void));

/*Description:
 *   Function to set call back function address for timer 2.
 * */
void TIMER2_SetCallBack(void(*a_ptr)(void));


#endif /* TIMER_H_ */
