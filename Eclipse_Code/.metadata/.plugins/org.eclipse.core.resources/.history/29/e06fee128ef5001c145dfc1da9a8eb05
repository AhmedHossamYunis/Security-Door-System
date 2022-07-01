/*
 ================================================================================================
 Name        : LCD.c
 Author      : Ahmed_Hossam
 Description : LCD Driver
 Date        : 14-5-2022
 ================================================================================================
 */

#include <util/delay.h>
#include "gpio.h"
#include "common_macros.h"
#include "LCD.h"
#include <stdlib.h>

/*
 * Description:
 * initialize LCD*/
void LCD_init(void)
{
	/*Configure RS, RW & E as output pins*/
	GPIO_setupPinDirection(LCD_RS_PORT_ID,LCD_RS_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_RW_PORT_ID,LCD_RW_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_E_PORT_ID,LCD_E_PIN_ID,PIN_OUTPUT);

	/*Configure Data PORT as output*/
	GPIO_setupPortDirection(LCD_DATA_PORT_ID,PORT_OUTPUT);
	/* 2 lines, 8 BIT Mode */
	LCD_sendCommand(TWO_LINE_8BIT_MODE);
	/* CURSER OFF */
	LCD_sendCommand(DISPLAY_ON_CURSER_OFF);

	/* Clear Screen */
	LCD_sendCommand(CLEAR_DISPLAY_WITH_DDRAM);
}

/*
 * Description:
 * send the required string to LCD.*/

void LCD_displayString(const char *str_ptr)
{
	uint8 i = 0;
	while(str_ptr[i] != '\0')
	{
		LCD_sendData(str_ptr[i]);
		i++;
	}
}


/*
 * Description:
 * send the required command to LCD.*/
void LCD_sendCommand(uint8 command)
{
	/* Command mode Rs = 0 */
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_LOW);
	/* Write Mode RW = 0*/
	GPIO_writePin(LCD_RW_PORT_ID, LCD_RW_PIN_ID, LOGIC_LOW);
	/*Address setup time tas = 50 ns */
	_delay_ms(1);
	/*Enable LCD */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	/*Data setup time tpw - tdsw = 290 - 100 = 190 ns*/
	_delay_ms(1);
	/* Send the required command */
	GPIO_writePort(LCD_DATA_PORT_ID, command);
	/* Disable LCD tdsw = 100ns */
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	/* Data hold time th */
	_delay_ms(1);
}

/*
 * Description:
 * send the required Data	 to LCD.*/
void LCD_sendData(uint8 data)
{
	/* Data mode Rs = 1 */
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_HIGH);
	/* Write Mode RW = 0*/
	GPIO_writePin(LCD_RW_PORT_ID, LCD_RW_PIN_ID, LOGIC_LOW);
	/*Address setup time tas = 50 ns */
	_delay_ms(1);
	/*Enable LCD */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	/*Data setup time tpw - tdsw = 290 - 100 = 190 ns*/
	_delay_ms(1);
	/* Send the required command */
	GPIO_writePort(LCD_DATA_PORT_ID, data);
	/* Disable LCD tdsw = 100ns */
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	/* Data hold time th */
	_delay_ms(1);
}

/*
 * Description:
 * clear screen.*/
void LCD_clearScreen(void)
{
	LCD_sendCommand(CLEAR_DISPLAY_WITH_DDRAM);
}


/*
 * Description :
 * Move the CURSER in the required position.
 */
void LCD_setCurser(uint8 row, uint8 col)
{
	uint8 LCD_memory_location;

	switch(row)
	{
	case 0:
		LCD_memory_location = col;
		break;
	case 1:
		LCD_memory_location = col + 0x40;
		break;
	case 2:
		LCD_memory_location = col + 0x10;
		break;
	case 3:
		LCD_memory_location = col + 0x50;
		break;
	}
	/* Set CURSER into the specific address. */
	LCD_sendCommand(LCD_memory_location | SET_CURSER_POSITION);
}

/*Description:
 * Display the required string in the required position.*/
void LCD_displayStringRowColumn(uint8 row, uint8 col, const char *str_ptr)
{
	/* Move CURSER to the required position.*/
	LCD_setCurser(row, col);
	/*Display the string.*/
	LCD_displayString(str_ptr);
}

/*Description:
 * Display the required decimal in the screen.*/
void LCD_intgerToString(int data)
{
	char buff[LCD_WIDE]; /*String to hold the ASCII result.*/
	/* C function to convert the data to its corresponding ASCII value.
	 * 10 for Decimal.*/
	itoa(data,buff,10);
	/*Display the string.*/
	LCD_displayString(buff);
}


