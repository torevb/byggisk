#include "ir_led.h"

#include "adc.h"



void ir_init(){
	adc_init();
	
	//kalibrer?
	
}

/* Read IR LED and say if it's triggered/blocked. */
int triggered_ir(){
	int out = read_adc_out();
	//TODO Create trigger area somewhere. This is "digital filter".
	
	
	return out;
}



