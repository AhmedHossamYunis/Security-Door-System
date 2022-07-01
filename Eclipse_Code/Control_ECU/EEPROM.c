/*
 ============================================================================
 Name        : EEPROM.c
 Data        : 6 - 6 -2022
 Author      : Ahmed_Hossam
 Description : EEPROM Driver
 ============================================================================
 */

#include "I2C.h"
#include "EEPROM.h"


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
uint8 EEPROM_writeByte(uint16 u16addr, uint8 u8data)
{

	TWI_start();
	if(TWI_getStatus() != TWI_START)
	{
		return ERROR;
	}

	TWI_writeByte((uint8)(0xA0 | ((u16addr & 0x0700)>>7)));
	if(TWI_getStatus() != TWI_MT_SLA_W_ACK)
	{
		return ERROR;
	}

	TWI_writeByte((uint8)(u16addr));
	if(TWI_getStatus() != TWI_MT_DATA_ACK)
	{
		return ERROR;
	}

	TWI_writeByte(u8data);
	if(TWI_getStatus() != TWI_MT_DATA_ACK)
	{
		return ERROR;
	}

	TWI_stop();

	return SUCCESS;

}

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
uint8 EEPROM_readByte(uint16 u16addr, char *u8data)
{

	TWI_start();
	if(TWI_getStatus() != TWI_START)
	{
		return ERROR;
	}

	TWI_writeByte((uint8)(0xA0 | ((u16addr & 0x0700)>>7)));
	if(TWI_getStatus() != TWI_MT_SLA_W_ACK)
	{
		return ERROR;
	}

	TWI_writeByte((uint8)(u16addr));
	if(TWI_getStatus() != TWI_MT_DATA_ACK)
	{
		return ERROR;
	}

	TWI_start();
	if(TWI_getStatus() != TWI_REP_START)
	{
		return ERROR;
	}

	TWI_writeByte((uint8)((0xA0) | ((u16addr & 0x0700)>>7)|1));
	if(TWI_getStatus() != TWI_MT_SLA_R_ACK)
	{
		return ERROR;
	}

	*u8data = TWI_readByteWithNACK();
	if (TWI_getStatus() != TWI_MR_DATA_NACK)
	{
		return ERROR;
	}

	TWI_stop();

	return SUCCESS;
}

