/*
 * slide.c
 *
 * Created: 22.09.2016 08:22:26
 *  Author: marthauk
 */ 

#include "slide.h"




void slider_init(void){
	memory_init();
	DDRB = (0<<DDB1)&& (0<<DDB0);
	
}


int8_t get_slider_pos(ADC_channel adc_ch){
	slider_init();
	volatile char *ext_adc = (char *) 0x1400; // Start address for the ADC
	*ext_adc	= adc_ch;
	_delay_us(40);
	int8_t position = *ext_adc;
	
	return position;
	
}



int slider_right_button(void){
	
	return (PINB &(1<<PINB0));
	
}

int slider_left_button(void){
	return (PINB &(1<<PINB1));
	
}