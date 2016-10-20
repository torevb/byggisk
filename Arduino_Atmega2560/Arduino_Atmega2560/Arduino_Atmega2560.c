
#include <avr/io.h>
#include "CAN_driver.h"
#include "SPI_driver.h"
#include "uart.h"
#include "CAN_test.h"
#include "MCP2515.h"
#include <stdio.h>


#define BAUD 9600
#define FOSC 16000000
#define MYUBRR FOSC/16/BAUD-1


int main(void)
{
	UART_Init(MYUBRR);		
	printf("Atmega2560 start.\n");
	
	MCP2515_init();
	
	CAN_test();
}