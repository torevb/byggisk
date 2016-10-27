#include "adc.h"
#include <avr/io.h>




void adc_init(){
	/* Set reference voltage 2,56V. */
	ADMUX |= (1<<REFS1) | (1<<REFS0);
	
	/* Set output ADC data register leftshifted or rightshifted. ADLAR == 0 is rightshifted. */
	ADMUX &= ~((1<<ADLAR));
	
	/* Set input pins. */							////////////////////////////////////////////////////////////////////////////////////////////////////////////////<<<<----fix///
	ADCSRB &= ~((1<<MUX5));
	ADMUX &= ~((1<<MUX4)|(1<<MUX3)|(1<<MUX2)|(1<<MUX1));
	ADMUX |= (1<<MUX0);
	
	/* Set ADC prescaling. */						////////////////////////////////////////////////////////////////////////////////////////////////////////////////<<<<----fix///
	//ADCSRA &= ~((1<<ADPS2) | (1<<ADPS1));	
	ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	
	/* Set free running mode. */
	ADCSRB &= ~((1<<ADTS2) | (1<<ADTS1) | (1<<ADTS0));
	
	
	
	
	
	
	/* Enable ADC interrupt. */
	//ADCSRA |= (1<<ADIE);
	
	/* Enable the ADC. */
	ADCSRA |= (1<<ADEN);
}

/*
void start_adc(){
	ADCSRA |= (1<<ADSC);
}*/

int adc_done(){
	return (ADCSRA & (1<<ADIF));
}

int read_adc_out(){
	//ADCSRA |= (1<<ADIF);				//Clear interrupt flag. 
	
	ADCSRA |= (1<<ADSC);				//Start ADC. First run takes 25 cycles. Others take 13.
	
	while ((ADCSRA & (1<<ADSC))) {}		//Wait till conversion is done. 
	
	return ((ADCL << 0) | (ADCH << 8));
}






