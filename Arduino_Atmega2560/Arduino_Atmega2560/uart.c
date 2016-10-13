//driver for UART-RS232
// PD1 is Transmitter
//PD0 is receiver
#include "uart.h"
#include <avr/io.h>
#include <stdio.h>

#define XCK3 2
#define UCPHA0 1

void UART_Init(unsigned int ubrr)
	{
		/* Set baud rate */
		//UBRR0H = (unsigned char)(ubrr>>8);
		//UBRR0L = (unsigned char)ubrr;
		/* Enable receiver and transmitter */
		//UCSR0B = (1<<RXEN0)|(1<<TXEN0);
		/* 
		Set frame format: 8data, 2stop bit
		*/
		//UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);
		//fdevopen(&UART_Transmit, &UART_Receive);
		
		UBRR0H = (unsigned char)(ubrr>>8);
		UBRR0L = (unsigned char)ubrr;
		/* Setting the XCKn port pin as output, enables master mode. */
		DDRJ |= (1<<XCK3);
		/* Set MSPI mode of operation and SPI data mode 0. */
		UCSR0C = (1<<UMSEL01)|(1<<UMSEL00)|(0<<UCPHA0)|(0<<UCPOL0);
		/* Enable receiver and transmitter. */
		UCSR0B = (1<<RXEN0)|(1<<TXEN0);
		/* Set baud rate. */
		fdevopen(&UART_Transmit, &UART_Receive);
		/* IMPORTANT: The Baud Rate must be set after the transmitter is
		enabled */
		

	}
	
void UART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer*/
		while( !( UCSR0A & (1<<UDRE0)) )
		;
	/* Put data into buffer, sends the data*/
		UDR0 = data;
}

unsigned char UART_Receive(void)
	{
		/* Wait for data to be received*/
		while( !(UCSR0A & (1<<RXC0)) )
			;
		/* Get and return received data from buffer*/
		return UDR0;
}