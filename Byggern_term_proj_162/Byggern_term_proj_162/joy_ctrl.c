/*
 * CFile2.c
 *
 * Created: 15.09.2016 12:58:30
 *  Author: marthauk
 */ 
#define F_CPU 16000000UL  //for <util/delay.h>
#include <util/delay.h> //for _delay_ms()
#include "joy_ctrl.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include "memory_interface.h"
#include "OLED.h"

#define JOY_NEUTRAL 20
#define JOY_MAX 100

struct {
	int x_pos;
	int y_pos;
} null_position;

void joy_init(){
	null_position.x_pos = get_joy_position(JOY_X);
	null_position.y_pos = get_joy_position(JOY_Y);
}

void joy_relative_pos(){
	int y= get_joy_position(JOY_Y);
	//rel_position.y_pos=(int)(y-null_position.y_pos)*100/127;
	rel_position.y_pos=(int)(y-null_position.y_pos)*(JOY_MAX-1)/127;
	int x= get_joy_position(JOY_X);
	//rel_position.x_pos=(int)(x-null_position.x_pos)*100/127;
	rel_position.x_pos=(int)(x-null_position.x_pos)*(JOY_MAX-1)/127;
}


uint8_t get_joy_position(ADC_channel adc_ch){
	volatile char *ext_adc = (char *) 0x1400; // Start address for the ADC
	
	*ext_adc	= adc_ch;
	_delay_us(20);//delay kan justeres ned til 20 mikro, sidan klokka går på 4915200
	////connect interruptsignal til pbx. if(PBx=1){}...
	uint8_t position = *ext_adc;
	
	return position;
}


int get_joy_direction(){
	//sammenlign x og y-fortegn og bestem kvadrant.
	//legg inn rom for neutral f.eks. <20%. 
	joy_direction x_dir=NEUTRAL;
	joy_direction y_dir=NEUTRAL;
	int8_t priority=1; 
	
	if (abs(rel_position.x_pos)>abs(rel_position.y_pos)){
		priority=0;
	}
	
	if(! priority){
		if (rel_position.x_pos>=-JOY_NEUTRAL && rel_position.x_pos<=JOY_NEUTRAL){
		x_dir=NEUTRAL;
		}
		else if (rel_position.x_pos>=JOY_NEUTRAL){
			x_dir=RIGHT;
		}
		else{
			x_dir=LEFT;
		}	
		return x_dir;
	}
	else{
		if (rel_position.y_pos>=-JOY_NEUTRAL && rel_position.y_pos<=JOY_NEUTRAL){
			y_dir=NEUTRAL;
		}
		else if (rel_position.y_pos>=JOY_NEUTRAL){
			y_dir=UP;
		}
		else{
			y_dir=DOWN;
		}
		return y_dir;
	}
	
}



