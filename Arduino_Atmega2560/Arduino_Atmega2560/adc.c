#include "adc.h"
#include <avr/io.h>




void adc_init(){
	
	/* Set reference voltage 1.1V. */
	ADMUX |= (1<<REFS1); 
	ADMUX &=~(1<<REFS0);
	
	/* Set output ADC data register leftshifted or rightshifted. ADLAR == 0 is rightshifted. */
	ADMUX &= ~((1<<ADLAR));
	
	/* Set PF0 as input */
	DDRF &=~(1<<PF0);
	
	/* Set input pins. Use ADC8--PF */
	ADCSRB &= ~((1<<MUX5));
	ADMUX &= ~((1<<MUX4)|(1<<MUX3)|(1<<MUX2)|(1<<MUX1) |(1<<MUX0));
	
	
	/* Set ADC prescaling. Choose to divide XTAL by 128 */
	ADCSRA |=  (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	

	
	/* Set free running mode. */
	ADCSRB &= ~((1<<ADTS2) | (1<<ADTS1) | (1<<ADTS0));
	
	
	
	/* Enable the ADC. */
	ADCSRA |= (1<<ADEN);
}


int adc_done(){
	return (ADCSRA & (1<<ADIF));
}

int read_adc_out(){
	ADCSRA |= (1<<ADSC);				//Start ADC. First run takes 25 cycles. Others take 13.
	
	while ((ADCSRA & (1<<ADSC))) {}		//Wait till conversion is done. 
	
	return ADCH;
}






