/*
 * slide.c
 *
 * Created: 22.09.2016 08:22:26
 *  Author: marthauk
 */ 
#include <avr/interrupt.h>


#include "slide.h"




void slider_init(void){
	DDRD &= ~((1<<PD2) | (1<<PD3));
	
	/* Enable slider button interrupts. */
	cli();								// Disable global interrupts
	MCUCR |= (1<<ISC01) | (1<<ISC11);	// Interrupt on rising edge PD2 and PD3. 
	GICR |= (1<<INT0) | (1<< INT1);		// Enable interrupt on PD2 and PD3. 
	sei();								// Enable global interrupts
}


int8_t get_slider_pos(ADC_channel adc_ch){
	//slider_init();
	volatile char *ext_adc = (char *) 0x1400; // Start address for the ADC
	*ext_adc	= adc_ch;
	_delay_us(40);
	int8_t position = *ext_adc;
	
	return position;
	
}



/*Used for going back in menu and interrupting processes*/
int slider_right_button(void){ 
	return (PIND &(1<<PIND3));
}

/*Enter-button*/
int slider_left_button(void){
	return (PIND &(1<<PIND2));
}