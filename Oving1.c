
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>

//#define F_CPU 1000000UL  //for <util/delay.h>
#include <util/delay.h> //for _delay_ms()

#include "uart.h"
#include "SRAM_test.h"
#include "GAL_test.h"
#include "joy_ctrl.h"
#include "slide.h"
#include "OLED.h"
#include "memory_interface.h"
#include "menu.h"
//#include "font.h"
#include "SPI_driver.h"
#include "MCP2515_driver.h"
//#include "CAN_test.h"
#include "CAN_driver.h"
#include "CAN MCP2515 header files/MCP2515.h"


#define BAUD 9600
#define FOSC 4915200
#define MYUBRR FOSC/16/BAUD-1


int main(void)
{	
	DDRE=0x3;
	DDRA=0xFF;
	PORTA=0x00;
	PORTE=0x2;
	/*
	UART_Init(MYUBRR);
	printf("Atmega162 start\n");
	*/
	
	game_init();	//Includes all inits necessary to be able to play the game and navigate in menu

	//play_game();
	
	
	
	
	
	return 0;
	
}