#include "pwm.h"

#include <avr/io.h>
#include "uart.h"



#define TIMER1_PERIOD 1249		//20 ms with prescaler 256.
#define DUTY_CYCLE_CENTER 94 //(TIMER1_PERIOD*(15/200))	//1,5 ms OF 20 ms. (94)
#define DUTY_CONVERT_FACTOR 3.5	//An input of +- 127 gives approximately +/- 37 output
#define DUTY_MAX 37
#define SLIDE_NEUTRAL 20
#define SLIDE_MAX 255
#define SLIDE_MIN 0
#define SLIDE_CENTER (SLIDE_MAX/2)

void pwm_init(){
	/* Set period to 20 ms. */

	ICR1 = TIMER1_PERIOD;
	
	/* Initialize duty cycle to 1,5 ms for "neutral" position. */
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



void set_pwm_duty_cycle(uint8_t input_slide_pos){
	printf("Position %i \n", input_slide_pos);
	if (input_slide_pos >= SLIDE_MAX){
		OCR1A = DUTY_CYCLE_CENTER + DUTY_MAX;
	}
	else if (input_slide_pos <= SLIDE_MIN){
		OCR1A = DUTY_CYCLE_CENTER - DUTY_MAX;
	}
	else if (input_slide_pos >= SLIDE_CENTER+SLIDE_NEUTRAL){
		int8_t input_slide_pos_int = input_slide_pos -127;
		OCR1A = DUTY_CYCLE_CENTER + (input_slide_pos_int / DUTY_CONVERT_FACTOR);
	}
	else if (input_slide_pos <= SLIDE_CENTER-SLIDE_NEUTRAL){
		int8_t input_slide_pos_int = input_slide_pos -127;
		OCR1A = DUTY_CYCLE_CENTER + (input_slide_pos_int / DUTY_CONVERT_FACTOR);
	}
	else {
		OCR1A = DUTY_CYCLE_CENTER;
	}
}
