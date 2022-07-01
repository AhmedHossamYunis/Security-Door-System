/*
 ============================================================================
 Name        : I2C.c
 Data        : 6 - 6 -2022
 Author      : Ahmed_Hossam
 Description : I2C Driver
 ============================================================================
 */



#include <avr/io.h>
#include "common_macros.h"
#include "I2C.h"
 /*
  * Description:
  * 	1- Insert the required bit rate.
  * 	2- Insert the required address.
  * 	3- zero prescaler.
  * 	4- Enable TWI module.
  * */
void TWI_init(const TWI_ConfingType *config)
{
	/*
	 * Bit rate 400 kbps (fast mode)
	 * TWBR --> Value of the TWI Bit Rate Register.
	 * TWPS --> Value of the prescaler bits in the TWI Status Register.
	 * */
	TWBR = config->bit_rate;
//	TWBR = 0x02;
	/*Using zero prescaler*/
	TWSR = 0x00;

	/*
	 * Two Wire Bus address my address if any master device want to call me
	 * use the inserted address(used in case this MC is a slave device)
	 * General Call Recognition: Off
	 * */
	TWAR = (config->address)<<1; // my address = 0x01 :)
//	TWAR = 0b00000010;
	/*Enable TWI module*/
	TWCR = (1<<TWEN);
}

/*
 * Description:
 * 	1- Clear the flag before sending start bit.
 * 	2- Send start bit.
 * 	3- Enable TWI module.
 * 	4- Wait until the start bit is send successfully.
 * */
//void TWI_start(void)
//{
//	/* Clear the flag before sending the start bit. */
//	SET_BIT(TWCR, TWINT);
//
//	/* Send start bit. */
//	SET_BIT(TWCR, TWSTA);
//
//	/*Enable TWI module*/
//	SET_BIT(TWCR, TWEN);
//
//	/* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
//	while(BIT_IS_CLEAR(TWCR,TWINT));
//
//	return;
//}
//
///*
// * Description:
// * 	1- Clear the flag before sending start bit.
// * 	2- Send stop bit.
// * 	3- Enable TWI module.
// * 	4- Wait until the stop bit is send successfully.
// * */
//void TWI_stop(void)
//{
//	/* Clear the flag before sending the start bit. */
//	SET_BIT(TWCR, TWINT);
//
//	/* Send stop bit. */
//	SET_BIT(TWCR, TWSTO);
//
//	/*Enable TWI module*/
//	SET_BIT(TWCR, TWEN);
//
//	return;
//}
//
///*
// * Description:
// * 	1- Store data in TWI data register.
// * 	2- Clear the flag before sending the start bit.
// * 	3- Enable TWI module.
// * 	4- Wait until data send successfully.
// * */
//void TWI_writeByte(uint8 data)
//{
//	/*Store data in TWI data register. */
//	TWDR = data;
//
//	/* Clear the flag before sending the start bit. */
//	SET_BIT(TWCR, TWINT);
//
//	/*Enable TWI module*/
//	SET_BIT(TWCR, TWEN);
//
//	/* Wait for TWINT flag set in TWCR Register (data send successfully) */
//	while(BIT_IS_CLEAR(TWCR,TWINT));
//
//	return;
//}
//
///*
// * Description:
// * 	1- Clear the flag before receiving the start bit.
// * 	2- Enable TWI module.
// * 	3- Enable TWI module.
// * 	4- Enable sending ACK after reading or receiving data.
// * 	5- Wait until the data received successfully.
// * */
//uint8 TWI_readByteWithACK(void)
//{
//
//	/* Clear the flag before receiving the start bit. */
//	SET_BIT(TWCR, TWINT);
//
//	/*Enable TWI module*/
//	SET_BIT(TWCR, TWEN);
//
//	/*Enable sending ACK after reading or receiving data TWEA=1*/
//	SET_BIT(TWCR, TWEA);
//
//	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
//	while(BIT_IS_CLEAR(TWCR,TWINT));
//
//	return TWDR;
//}
//
///*
// * Description:
// * 	1- Clear the flag before receiving the start bit.
// * 	2- Enable TWI module.
// * 	3- Enable TWI module.
// * 	4- Wait until the data received successfully.
// * */
//uint8 TWI_readByteWithNACK(void)
//{
//
//	/* Clear the flag before receiving the start bit. */
//	SET_BIT(TWCR, TWINT);
//
//	/*Enable TWI module*/
//	SET_BIT(TWCR, TWEN);
//
//	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
//	while(BIT_IS_CLEAR(TWCR,TWINT));
//
//	return TWDR;
//}
//
//
///*
// * Description:
// * 	 Function to get the status of the bits.
// * */
//uint8 TWI_getStatus(void)
//{
//    uint8 status;
//    /* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
//    status = TWSR & 0xF8;
//    return status;
//}

void TWI_start(void)
{
    /*
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    /* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
}

void TWI_stop(void)
{
    /*
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void TWI_writeByte(uint8 data)
{
    /* Put data On TWI data Register */
    TWDR = data;
    /*
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWINT) | (1 << TWEN);
    /* Wait for TWINT flag set in TWCR Register(data is send successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
}

uint8 TWI_readByteWithACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
    /* Read Data */
    return TWDR;
}

uint8 TWI_readByteWithNACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWINT) | (1 << TWEN);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
    /* Read Data */
    return TWDR;
}

uint8 TWI_getStatus(void)
{
    uint8 status;
    /* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
    status = TWSR & 0xF8;
    return status;
}

