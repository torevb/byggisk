#include "ir_receiver.h"
#define F_CPU 16000000UL  //for <util/delay.h>
#define NEW_ROUND_SETUP 1000
#include <util/delay.h> //for _delay_ms()


int score=0;
int previousTrigger=0;

int score_count(){
	int8_t triggered =triggered_ir();
	if (previousTrigger!=triggered){
		score+=triggered;
		previousTrigger=triggered;
		_delay_ms(NEW_ROUND_SETUP);		//move to print_score() afterwards. 
		
	}
	return triggered;
}

void reset_score(){
	score=0;
	previousTrigger=0;
}