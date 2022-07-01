/*
 ============================================================================
 Name        : I2C.h
 Data        : 6 - 6 -2022
 Author      : Ahmed_Hossam
 Description : I2C Driver
 ============================================================================
 */

#ifndef I2C_H_
#define I2C_H_

#include "std_types.h"
/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
 typedef struct{
	 uint8 address;
	 uint8 bit_rate;
 }TWI_ConfingType;


/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

 /*
  * Description:
  * 	1- Insert the required bit rate.
  * 	2- Insert the required address.
  * 	3- zero prescaler.
  * 	4- Enable TWI module.
  * */
void TWI_init(const TWI_ConfingType *config);

/*
 * Description:
 * 	1- Clear the flag before sending start bit.
 * 	2- Send start bit.
 * 	3- Enable TWI module.
 * 	4- Wait until the start bit is send successfully.
 * */
void TWI_start(void);

/*
 * Description:
 * 	1- Clear the flag before sending start bit.
 * 	2- Send stop bit.
 * 	3- Enable TWI module.
 * 	4- Wait until the stop bit is send successfully.
 * */
void TWI_stop(void);

/*
 * Description:
 * 	1- Store data in TWI data register.
 * 	2- Clear the flag before sending the start bit.
 * 	3- Enable TWI module.
 * 	4- Wait until data send successfully.
 * */
void TWI_writeByte(uint8 data);

/*
 * Description:
 * 	1- Clear the flag before receiving the start bit.
 * 	2- Enable TWI module.
 * 	3- Enable TWI module.
 * 	4- Enable sending ACK after reading or receiving data.
 * 	5- Wait until the data received successfully.
 * */
uint8 TWI_readByteWithACK(void);

/*
 * Description:
 * 	1- Clear the flag before receiving the start bit.
 * 	2- Enable TWI module.
 * 	3- Enable TWI module.
 * 	4- Wait until the data received successfully.
 * */
uint8 TWI_readByteWithNACK(void);

/*
 * Description:
 * 	 Function to get the status of the bits.
 * */
uint8 TWI_getStatus(void);




#endif /* I2C_H_ */
