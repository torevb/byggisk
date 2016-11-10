#include "solenoid.h"
#include <avr/io.h>

//#define F_CPU 1000000UL  //for <util/delay.h>
#include <util/delay.h> //for _delay_ms()



void solenoid_init(){
	DDRB |= (1<<PB0);
	//PORTB |= (1<<PB0);
}

void push_solenoid(){
	//int output = slider_left_button() >> 2;
	//PORTB |= (output & (1<<PB0));
	
	PORTB |= (1<<PB0);
	_delay_ms(50);
	PORTB &= ~(1<<PB0);
	
}


