
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



void test_pwm_duty();



int main(void)
{
	UART_Init(MYUBRR);		
	printf("Atmega2560 start.\n");
	//ir_init();
	motor_init();
	//printf("HAllo1\n");
	//calibrate_encoder();
	
	while(1){
		send_motor_speed();
		//_delay_ms(6000);
		//read_encoder_input();
		
	}

	
	//CAN_test();
	
	//test_pwm_duty();
	
	
	//int out=255;
	//while(1){
	//	printf("Score : %i \n",score_count());
	//}

	
	
	
	
	
	
	
	
	
	return 0;
}






void test_pwm_duty(){
	pwm_init();
	CAN_init();

	CAN_struct joyfull;
	
	while (1){
		joyfull = rcv_CAN_message();
		/*for (int i = 0; i < joyfull.length; i++){
			int8_t test =  joyfull.data[i];
			printf("joyfull.data[i]: %i\n", test);
		}*/
		set_pwm_duty_cycle(joyfull.data[0]);
		printf("joyfull.data[0]: %x\n", joyfull.data[0]);
		printf("pwm duty: %i\n", OCR1A);
	}
}