#include "pwm.h"

#include <avr/io.h>



#define TIMER1_PERIOD 1249		//20 ms with prescaler 256. 
#define DUTY_CYCLE_CENTER 94 //(TIMER1_PERIOD*(15/200))	//1,5 ms OF 20 ms. (94)
#define DUTY_CONVERT_FACTOR 2.8	//An input of +/- 100 gives approximately +/- 37 output


void pwm_init(){
	/* Set period to 20 ms. */
	//ICR1H = TIMER1_PERIOD & (0xFFFF << 8);
	//ICR1L = TIMER1_PERIOD & (0xFFFF << 0);
	ICR1 = TIMER1_PERIOD;
	
	/* Initialize duty cycle to 1,5 ms for "neutral" position. */
	//OCR1AH = DUTY_CYCLE_NEUTRAL & (0xFFFF << 8);
	//OCR1AL = DUTY_CYCLE_NEUTRAL & (0xFFFF << 0);
	OCR1A = DUTY_CYCLE_CENTER;
	
	/* Set DDRB OC1A as output. */
	DDRB |= (1<<PB5);
	
	/* Set Waveform Generation Mode 14 (fast PWM). */
	TCCR1A &= ~(1<<WGM10);
	TCCR1A |= (1<<WGM11);
	TCCR1B |= ((1<<WGM13) | (1<<WGM12));
	
	/* Compare output mode for fast PWM. */
	TCCR1A &= ~(1<<COM1A0);
	TCCR1A |= (1<<COM1A1);
	
	/* Prescaler 256. */
	TCCR1B &= ~((1<<CS11) | (1<<CS10));
	TCCR1B |= (1<<CS12);
}

void set_pwm_duty_cycle(int8_t input_joy_position){
	if ((input_joy_position <= 100) && (input_joy_position >= -100)){
		OCR1A = DUTY_CYCLE_CENTER + (input_joy_position / DUTY_CONVERT_FACTOR);
	}
	else if (input_joy_position >= 100){
		OCR1A = DUTY_CYCLE_CENTER + 37;
	}
	else if (input_joy_position <= -100){
		OCR1A = DUTY_CYCLE_CENTER - 37;
	}
	else {	//never occurs.
		OCR1A = DUTY_CYCLE_CENTER;
	}
}

