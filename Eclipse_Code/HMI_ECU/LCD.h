/*
 ================================================================================================
 Name        : LCD.h
 Author      : Ahmed_Hossam
 Description : LCD Driver
 Date        : 14-5-2022
 ================================================================================================
 */

#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define LCD_RS_PORT_ID    PORTB_ID
#define LCD_RW_PORT_ID    PORTB_ID
#define LCD_E_PORT_ID     PORTB_ID

#define LCD_DATA_PORT_ID  PORTC_ID

#define LCD_RS_PIN_ID     PIN0_ID
#define LCD_RW_PIN_ID     PIN1_ID
#define LCD_E_PIN_ID      PIN2_ID

#define LCD_WIDE 16

/*******************************************************************************
 *                                Commands                                     *
 *******************************************************************************/
#define TWO_LINE_8BIT_MODE                  0x38
#define TWO_LINE_4BIT_MODE                  0x28
#define ONE_LINE_8BIT_MODE                  0x30
#define ONE_LINE_4BIT_MODE                  0x20
#define ENTRY_MODE                          0x06
#define DISPLAY_CURSER_OFF_WITHOUT_DDRAM    0x08
#define DISPLAY_CURSER_ON                   0x0E
#define DISPLAY_ON_CURSER_OFF               0x0C
#define DISPLAY_ON_CURSER_BLINKING          0x0F
#define SHIFT_DISPLAY_LEFT                  0x18
#define SHIFT_DISPLAY_RIGHT                 0x1C
#define MOVE_CURSER_LEFT_BY_ONE_CHAR        0x10
#define MOVE_CURSER_RIGHT_BY_ONE_CHAR       0x14
#define CLEAR_DISPLAY_WITH_DDRAM            0x01
#define SET_CURSER_POSITION                 0x80

/*******************************************************************************
 *                                Functions Prototypes                         *
 *******************************************************************************/

/*
 * Description:
 * initialize LCD*/
void LCD_init(void);

/*
 * Description:
 * send the required command to LCD.*/
void LCD_sendCommand(uint8 command);

/*
 * Description:
 * send the required string to LCD.*/
void LCD_displayString(const char *str_ptr);

/*
 * Description:
 * send the required Data	 to LCD.*/
void LCD_sendData(uint8 data);

/*
 * Description:
 * clear screen with DDRAM content.*/
void LCD_clearScreen(void);

/*
 * Description :
 * Move the CURSER in the required position.
 */
void LCD_setCurser(uint8 row, uint8 col);

/*Description:
 * Display the required string in the required position.*/
void LCD_displayStringRowColumn(uint8 row, uint8 col, const char *str_ptr);

/*Description:
 * Display the required decimal in the screen.*/
void LCD_intgerToString(int data);


#endif /* LCD_H_ */
