/*
 * Oving1.c
 *
 * Created: 01.09.2016 08:28:15
 *  Author: marthauk
 */ 
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



#define BAUD 9600
#define FOSC 4915200
#define MYUBRR FOSC/16/BAUD-1


int main(void)
{	
	//ov1////////////////////////////////
	
	UART_Init(MYUBRR);
	//DDRD=0x01;
	//PORTD=0x01;
	//UART_Transmit(10);
	
	 //while(1){
		 //	PORTD ^= (1 << PD0);
		 //for (int i=0;i<1000;i++){
		 //}
		 //int test = 0;
		 //printf("hei, %i", test);
		 //unsigned char c=UART_Receive();
		 //UART_Transmit(c);
	 //}
	
	
	//ov2////////////////////////////////
	
	DDRE=0x3;
	DDRA=0xFF;
	PORTA=0x00;
	PORTE=0x2;

	
			
    //while(1){
		////for (int i=0;i<1000;i++){
		////}
		//_delay_ms(1000);
		//PORTE|=(1<<PE1);
		//PORTA^=(1<<PA0);
		//PORTA^=(1<<PA1);
		//
    //}
	
	
	
	//PORTE|=(1<<PE1);
	//PORTA|=(1<<PA0);
	//PORTA|=(1<<PA1);
	//SRAM_test();
	
	//GAL_test();
	
	DDRD = 0xFF;
	
	PORTD = (1<<PD6);
	PORTD = (0<<PD7);
	
	//while(1){
	//	PORTD ^= (1<<PD6);
	//	_delay_ms(1000);
	//	PORTD ^= (1<<PD7);
		
	//}
	
	//////////////////////////
	///////oving3/////////////
	/////////////////////////
	while(1){
	ADC_channel joy_test= JOY_Y;
	uint8_t position =get_joy_position(joy_test);
	printf("Position is : %i\n",position);
	int percentage= calculate_percentage(position);
	print_position(42,position);
	}
	
	return 0;
	
}