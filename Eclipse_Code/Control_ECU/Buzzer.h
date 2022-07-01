/*
============================================================================
 Name        : Buzzer.h
 Data        : 26 - 5 -2022
 Author      : Ahmed_Hossam
 Description : Buzzer Driver
 ============================================================================
 */


#ifndef BUZZER_H_
#define BUZZER_H_

#include "std_types.h"

/*******************************************************************************
 *                               Definitions                                   *
 *******************************************************************************/

#define BUZZER_PORT_ID PORTC_ID
#define BUZZER_PIN_ID  PIN2_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*Description:
 *    Function to initialize the Buzzer by set the connected pin as output
 * */
void BUZZER_init(void);

/*Description:
 *    Function to start the Buzzer
 * */
void BUZZER_start(void);




#endif /* BUZZER_H_ */
