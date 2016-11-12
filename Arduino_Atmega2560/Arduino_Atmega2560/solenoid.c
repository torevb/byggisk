#include "solenoid.h"
#include <avr/io.h>

//#define F_CPU 1000000UL  //for <util/delay.h>
#define DELAY_SOLENOIDE 700
#include <util/delay.h> //for _delay_ms()



void solenoid_init(){
	DDRL |= (1<<PL7);
	PORTL |= (1<<PL7);
}

void push_solenoid(){

	PORTL &= ~(1<<PL7);
	_delay_ms(DELAY_SOLENOIDE);
	PORTL |= (1<<PL7);
	
}


