/*
 * CFile2.c
 *
 * Created: 15.09.2016 12:58:30
 *  Author: marthauk
 */ 
#include <util/delay.h> //for _delay_ms()
#include "joy_ctrl.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include "memory_interface.h"

uint8_t read_bus(){
	DDRA=0x00;//A er input
	uint8_t position= PORTA;
	return position;
}

uint8_t get_joy_position(ADC_channel adc_ch){
	memory_init();
	volatile char *ext_adc = (char *) 0x1400; // Start address for the ADC
	
	*ext_adc	= adc_ch;
	_delay_us(40);
	int8_t position = *ext_adc;
	
	return position;
}





int get_joy_direction(void){
	//sammenlign x og y-fortegn og bestem kvadrant.
	//legg inn rom for neutral f.eks. <20%. 
	
	return 0;
}

int8_t calculate_percentage(int8_t position){
	int8_t shifted_position = position-(int8_t)0x7F;
	//int8_t percentage = shifted_position*100/127; 
	return shifted_position;
}


void print_position(int8_t percentage_x, int8_t percentage_y){
	printf("joystick position is: x: %i, y: %i\n", percentage_x, percentage_y);
}