#include "pid.h"
#include "motor.h"
#include <stdint.h>


#define Kp	-0.2//-1.15
#define Ki	-0.005
#define Kd	-0.001

float previousError=0;
int encoder_max = 3000;
#define MAX_SPEED 100
float integral = 0;
#define NICE_SPEED 100

void set_encoder_max(int value){
	encoder_max = value;
}

uint8_t speed_regulator(int8_t input_joy, float t){
	
	
	int16_t motor_pos = abs(read_encoder_input());
	float e=0; //ERROR
	if(abs(input_joy)<10){
		return 0;
	}
	

	
	float joy_value = (100 - abs(input_joy)) * (encoder_max/100);
	
	e = joy_value - motor_pos; 

	float P = e*Kp;
	
	
	float integrateError = e+previousError;
	float I=t*integrateError * Ki;

	
	previousError += e;
	

	float u = P + I;
	
	
	uint8_t out = abs(u) / (encoder_max/255);

	if (out > MAX_SPEED){
		out = MAX_SPEED; 
	}
	return out;
}





