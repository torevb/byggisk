#include "ir_receiver.h"
#define F_CPU 16000000UL  //for <util/delay.h>
#define NEW_ROUND_SETUP 3000
#include <util/delay.h> //for _delay_ms()


int score=0;
int previousTrigger=0;
int score_count(){
	
	if (previousTrigger!=triggered_ir()){
		score+=triggered_ir();
		previousTrigger=triggered_ir();
		_delay_ms(NEW_ROUND_SETUP);		//move to print_score() afterwards. 
		
	}
	return score;
}

void reset_score(){
	score=0;
	previousTrigger=0;
}