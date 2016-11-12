#include "solenoid.h"
#include <avr/io.h>

//#define F_CPU 1000000UL  //for <util/delay.h>
#define DELAY_SOLENOIDE 500
#include <util/delay.h> //for _delay_ms()



void solenoid_init(){
	DDRB |= (1<<PB0);
	PORTB |= (1<<PB0);
}

void push_solenoid(){

	PORTB &= ~(1<<PB0);
	_delay_ms(DELAY_SOLENOIDE);
	PORTB |= (1<<PB0);
	
}


