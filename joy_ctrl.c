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



struct {
	uint8_t x_pos;
	uint8_t y_pos;
} null_position;




void joy_init(){
	memory_init();
	null_position.x_pos = get_joy_position(JOY_X);
	null_position.y_pos = get_joy_position(JOY_Y);
	
	
}

void joy_relative_pos(){
	uint8_t x= get_joy_position(JOY_X);
	rel_position.x_pos=(int)(x-null_position.x_pos)*100/127;
	uint8_t y= get_joy_position(JOY_Y);
	rel_position.y_pos=(int)(y-null_position.y_pos)*100/127;
}


uint8_t get_joy_position(ADC_channel adc_ch){
	
	volatile char *ext_adc = (char *) 0x1400; // Start address for the ADC
	
	*ext_adc	= adc_ch;
	_delay_us(40);
	uint8_t position = *ext_adc;
	
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


void print_position(){
	printf("joystick position is: x: %i, y: %i\n", rel_position.x_pos, rel_position.y_pos);
}