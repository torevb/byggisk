#include "ir_receiver.h"

#include "adc.h"



void ir_init(){
	adc_init();
}

/* Read IR LED and say if it's triggered/blocked. */
int triggered_ir(){
	int out = read_adc_out();
	if (out){
		return 0;
	}
	
	
	return 1;
}



