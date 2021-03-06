/*
============================================================================
 Name        : USART.c
 Data        : 5 - 6 -2022
 Author      : Ahmed_Hossam
 Description : USART Driver
 ============================================================================
 */


#include "USART.h"
#include "avr/io.h"
#include "common_macros.h"


/*
 * Description:
 *	  1- Insert the frame format as parity mode, no of stop bits, no of data bits.
 *	  2- Insert UART baud rate.
 *	  3- Enable UART.
 * */
void USART_init( const USART_configType *config)
{

	uint16 ubrr_value = 0;

	/*For double transmission speed, this bit has effect for the asynchronous operation*/
	SET_BIT(UCSRA,U2X);

	/************************** UCSRB Description **************************
	 * RXCIE = 0 Disable USART RX Complete Interrupt Enable
	 * TXCIE = 0 Disable USART Tx Complete Interrupt Enable
	 * UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
	 * RXEN  = 1 Receiver Enable
	 * RXEN  = 1 Transmitter Enable
	 * Insert no of bits data mode (UCSZ2).
	 * RXB8 & TXB8 not used for 8-bit data mode
	 ***********************************************************************/
	SET_BIT(UCSRB, RXEN);
	SET_BIT(UCSRB, TXEN);
	UCSRB = (UCSRB & 0xFB) | (((config->data_bit) & 0x04)<<2);


	/************************** UCSRC Description **************************
	 * URSEL   = 1 The URSEL must be one when writing the UCSRC
	 * UMSEL   = 0 Asynchronous Operation
	 * Insert parity mode (UPM1:0).
	 * Insert no of stop bits (USBS).
	 * Insert no of data bits (UCSZ1:0).
	 * UCPOL   = 0 Used with the Synchronous operation only
	 ***********************************************************************/
	UCSRC = (UCSRC & 0xCF) | ((config->parity)<<4);
	UCSRC = (UCSRC & 0xF7) | ((config->stop_bit)<<3);
	UCSRC = (UCSRC & 0xF9) | (((config->data_bit) & 0x03)<<1);

	SET_BIT(UCSRC, RXEN);

	/* Calculate the UBRR register value */
	ubrr_value = (uint16)(((F_CPU / ((config->baud_rate) * 8UL))) - 1);

	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/

	UBRRH = ubrr_value>>8;
	UBRRL = ubrr_value;
	return;
}

/*
 * Description:
 * 		Functional responsible for send byte to another UART device.
 * */
void USART_sendByte(const uint8 data)
{
	/*
	 * UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one
	 */
	while(BIT_IS_CLEAR(UCSRA, UDRE)){}

	/*
	 * The Transmit Data Buffer Register (TXB) will be the destination
	 * for data written to the UDR Register location.
	 * */
	UDR = data;

	return;
}

/*
 * Description:
 * 		Functional responsible for receive byte to another UART device.
 * */
uint8 USART_receiveByte(void)
{
	/*
	 *  RXC flag is set when the UART receive data so wait until this flag is set to one
	 * */
	while(BIT_IS_CLEAR(UCSRA, RXC)){}

	/*
	 * Reading the UDR Register location will return the contents of the Receive Data
	 * Buffer Register (RXB).
	 * */
	return UDR;
}

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void USART_sendString(const char *str_ptr)
{
	uint8 i = 0;

	while(str_ptr[i] != '\0')
	{
		USART_sendByte(str_ptr[i]);
		i++;
	}

	return;
}

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void USART_receiveString(char *str_ptr)
{
	uint8 i = 0;

	str_ptr[i] = USART_receiveByte();

	while(str_ptr[i] != '#')
	{
		i++;
		str_ptr[i] = USART_receiveByte();
	}

	str_ptr[i] = '\0';
	return;
}
