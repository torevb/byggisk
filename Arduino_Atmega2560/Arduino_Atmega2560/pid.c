#include "pid.h"
#include "motor.h"
#include <stdint.h>


#define Kp	-1.15
#define Ki	0.05
#define Kd	0.01

int n =0;
#define ERROR_SIZE 100


void speed_regulator(int16_t input_joy){
	//p, i?
	n++;
	int16_t motor_pos=read_encoder_input();
	int e[ERROR_SIZE]={0};
	/*100 used for time*/
	int16_t e[n]= motor_pos/100- abs(input_joy); 
	
	
	
}





