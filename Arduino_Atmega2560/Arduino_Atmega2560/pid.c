#include "pid.h"
#include "motor.h"
#include <stdint.h>


#define Kp	-0.8//-1.15
#define Ki	0.05
#define Kd	0.01

int previousError=0;


uint8_t speed_regulator(int8_t input_joy, int *t){
	//p, i?
	
	int8_t motor_pos=read_encoder_input();
	float e=0;
	if(abs(input_joy)<10){
		
	}
	
	e= motor_pos/(*t/(10^3))- abs(input_joy); 
	
	float P = Kp*e;
	float integrateError=e+previousError;
	
	float I=Ki*(*t/(10^3))*integrateError;
	previousError=e;
	
	if (motor_pos!=0){
		*t=0;
		}
		
		
		
	return P+I;
}





