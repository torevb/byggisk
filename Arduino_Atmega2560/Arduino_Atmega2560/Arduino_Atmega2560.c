
#include <avr/io.h>
#include "CAN_driver.h"
#include "SPI_driver.h"
#include "uart.h"
#include "CAN_test.h"
#include "MCP2515.h"
#include <stdio.h>
#include "pwm.h"
#include "ir_receiver.h"
#include "scoretable.h"
#include "motor.h"
#include "pid.h"

#define F_CPU 16000000UL  //for <util/delay.h>
#include <util/delay.h> //for _delay_ms()



#define BAUD 9600
#define FOSC 16000000
#define MYUBRR FOSC/16/BAUD-1




int main(void)
{
	UART_Init(MYUBRR);		
	printf("Atmega2560 start.\n");
	//ir_init();
	CAN_init();
	motor_init();
	solenoid_init();
	pwm_init();

	
	int8_t rcv_data= 0;
	CAN_struct msg;
	
	while(1){
		rcv_CAN_message(&msg);
		rcv_data=msg.data[0];
		//printf("Received ID: %i\n Received data: %i \n",msg.ID,rcv_data);
		if (msg.ID==SOLENOIDE_PUSH_ID){
			push_solenoid();
			
		}
		else if (msg.ID==JOYSTICK_ID){
			int8_t temp_joy= msg.data[0];
			set_motor_dir(temp_joy);
			uint8_t regulated_speed=speed_regulator(temp_joy, 0.01);
			send_motor_speed(regulated_speed);
			
		}
		else if(msg.ID==SLIDER_ID){
			printf("Hey\n");
			set_pwm_duty_cycle(msg.data[0]);
		}
		
		

		
		
	}

	
	
	
	
	return 0;
}




