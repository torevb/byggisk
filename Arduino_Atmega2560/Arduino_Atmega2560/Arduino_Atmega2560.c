
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



int main(void){
	UART_Init(MYUBRR);		
	printf("Atmega2560 start.\n");
	
	CAN_init();
	motor_init();
	pwm_init();
	solenoid_init();
	ir_init();
	//calibrate_encoder();
	
	CAN_struct send_msg;
	send_msg.ID = NODE2_ID;
	send_msg.length=4;
	
	CAN_struct rcv_msg;
	rcv_msg.ID = RCV_ID;
	rcv_msg.length = 4;
	
	send_msg.data[0] = 0;	//joy_x
	send_msg.data[1] = 0;	//slider_left
	send_msg.data[2] = 0;	//button_left / interrupt
	
	rcv_msg.data[3] = 0;	//highscore value
	
	while(1){
		send_msg.data[3] = 0;	//highscore value			<---
		
		rcv_msg.data[0] = 0;	//joy_x						<---
		rcv_msg.data[1] = 0;	//slider_left				<---
		rcv_msg.data[2] = 0;	//button_left / interrupt	<---
		
		rcv_CAN_message(&rcv_msg);
		
		if (rcv_msg.data[0] != 0){		//joy_x
			//printf("CAN joy data\n");
			int8_t temp_joy_x= rcv_msg.data[0];
			set_motor_dir(temp_joy_x);
			uint8_t regulated_speed=speed_regulator(temp_joy_x, 0.01);
			//printf("speed %i\n", regulated_speed);
			send_motor_speed(regulated_speed);
		}
		
		if (rcv_msg.data[1] != 0){		//slider_left
			//printf("CAN slider data\n");
			uint8_t temp_slider = rcv_msg.data[1];
			set_pwm_duty_cycle(temp_slider);
		}
		
		if (rcv_msg.data[2] != 0){		//button_left / interrupt
			printf("CAN button data\n");
			push_solenoid();
		}
		
		send_msg.data[3] = score_count();
		printf("Scorecount %i",send_msg.data[3]);
		
		
		send_CAN_message(& send_msg);
		
		printf("loop\n"); 
	}
	return 0;
}

