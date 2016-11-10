#include "pid.h"
#include "motor.h"
#include <stdint.h>


#define Kp	-1.15
#define Ki	0.05
#define Kd	0.01


void speed_regulator(int16_t input_joy){
	//p, i, d?
	int16_t output = input_joy * Kp;
	
	
	
	
}





