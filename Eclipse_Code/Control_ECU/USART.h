/*
 ============================================================================
 Name        : USART.h
 Data        : 5 - 6 -2022
 Author      : Ahmed_Hossam
 Description : USART Driver
 ============================================================================
 */

#ifndef USART_H_
#define USART_H_

#include "std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum{
	FIVE_BITS, SIX_BITS, SEVEN_BITS, EIGHT_BITS, NINE_BITS = 7
}USART_noOfDataBit;

typedef enum{
	DISABLED, RESERVED, EVEN, ODD
}USART_parityMode;

typedef enum{
	ONE_BIT, TWO_BITS
}USART_noOfStopBits;

typedef struct{
	uint32 baud_rate;
	USART_parityMode parity;
	USART_noOfStopBits stop_bit;
	USART_noOfDataBit data_bit;
}USART_configType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description:
 *	  1- Insert the frame format as parity mode, no of stop bits, no of data bits.
 *	  2- Insert UART baud rate.
 *	  3- Enable UART.
 * */
void USART_init(const USART_configType *config);

/*
 * Description:
 * 		Functional responsible for send byte to another UART device.
 * */
void USART_sendByte(const uint8 data);

/*
 * Description:
 * 		Functional responsible for receive byte to another UART device.
 * */
uint8 USART_receiveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void USART_sendString(const char *str_ptr);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void USART_receiveString(char *str_ptr);



#endif /* USART_H_ */
