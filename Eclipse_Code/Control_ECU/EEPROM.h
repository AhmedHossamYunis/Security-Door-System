/*
 ============================================================================
 Name        : EEPROM.H
 Data        : 6 - 6 -2022
 Author      : Ahmed_Hossam
 Description : EEPROM Driver
 ============================================================================
 */

#ifndef EEPROM_H_
#define EEPROM_H_

#include "std_types.h"


/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define ERROR   0
#define SUCCESS 1


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description:
 * 	  1- Send start bit.
 * 	  2- Send the device address.
 * 	  3- Send the required memory location
 * 	  4- Send R/W = 0.
 * 	  5- Write byte to EEPROM.
 * 	  6- Send stop bit.
 * 	  7- return SUCCESS or ERROR.
 *
 * */
uint8 EEPROM_writeByte(uint16 u16addr, uint8 u8data);

/*
 * Description:
 * 	  1- Send start bit.
 * 	  2- Send the device address.
 * 	  3- Send the required memory location
 * 	  4- Send repeated start.
 * 	  5- Send R/W = 1.
 * 	  6- Read byte from EEPROM.
 * 	  7- Send stop bit.
 *
 * */
uint8 EEPROM_readByte(uint16 u16addr, char *u8data);



#endif /* EEPROM_H_ */
