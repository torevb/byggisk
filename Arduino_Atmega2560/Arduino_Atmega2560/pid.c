#include "pid.h"
#include "motor.h"
#include <stdint.h>


#define Kp	-0.00001//-1.15
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
	
	//p, i?
	
	//printf("input_joy %i\n", input_joy);
	//int K_p = -10000;
	//int K_i = -10000;
	
	
	int16_t motor_pos = abs(read_encoder_input());
	float e=0;
	if(abs(input_joy)<10){
		return 0;
	}
	
	//printf("motor_pos %i, input_joy %i\n", motor_pos, input_joy);
	
	float joy_value = (100 - abs(input_joy)) * (encoder_max/100);
	
	e = joy_value - motor_pos; 
	//printf("e: %i\n", e);
	
	float P = e*Kp;
	//printf("P: %d\n", P);
	
	float integrateError = e+previousError;
	float I=t*integrateError * Ki;
	//integral += e * t;
	//printf("I: %d\n", integral);
	
	previousError += e;
	
	//printf("motor_pos %i, joy_value %i\n", motor_pos, joy_value);
	//printf("K: %i %i\n", K_p, K_i);
	float u = P + I;
	//printf("u: %d\n", u);
	
	uint8_t out = abs(u) / (encoder_max/255);
	//out = abs(out);
	//printf("out %i\n", out);
	if (out > MAX_SPEED){
		out = out/1.2;
		//out = NICE_SPEED;
	}
	return out;
}





