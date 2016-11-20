
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>

//#define F_CPU 1000000UL  //for <util/delay.h>
#include <util/delay.h> //for _delay_ms()

#include "uart.h"
#include "SRAM_test.h"
#include "GAL_test.h"
#include "joy_ctrl.h"
#include "slide.h"
#include "OLED.h"
#include "memory_interface.h"
#include "menu.h"
//#include "font.h"
#include "SPI_driver.h"
#include "MCP2515_driver.h"
#include "SRAM.h"

#include "CAN_driver.h"
#include "../../CAN MCP2515 header files/MCP2515.h"

#define SLIDER_TRESHOLD 10
#define BAUD 9600
#define FOSC 4915200
#define MYUBRR FOSC/16/BAUD-1


int main(void){	
	DDRE=0x3;
	DDRA=0xFF;
	PORTA=0x00;
	PORTE=0x2;
	
	UART_Init(MYUBRR);
	printf("Atmega162 start\n");
	
	SRAM_init();
	adc_init();
	CAN_init();
	slider_init();
	joy_init();
	
	menu_init();
	
	CAN_struct send_msg;
	send_msg.ID = NODE1_ID;
	send_msg.length=4;
	
	CAN_struct rcv_msg;
	rcv_msg.ID = RCV_ID;
	rcv_msg.length = 4;
	
	
	int8_t previous_slider_pos=-128;
	
	send_msg.data[3] = 0;	//highscore value
	
	rcv_msg.data[0] = 0;	//joy_x
	rcv_msg.data[1] = 0;	//slider_left
	rcv_msg.data[2] = 0;	//button_left / interrupt
	
	
	while(1){
		send_msg.data[0] = 0;	//joy_x						<---
		send_msg.data[1] = 0;	//slider_left				<---
		send_msg.data[2] = 0;	//button_left / interrupt	<---
		
		joy_relative_pos();
		
		if (current_node==&ingame_node){
			int8_t joy_x_temp = rel_position.x_pos;
			send_msg.data[0] = joy_x_temp;
			
			int8_t current_slide_pos = get_slider_pos(SLIDE_L);
			if((current_slide_pos>=previous_slider_pos+SLIDER_TRESHOLD)||(current_slide_pos<=previous_slider_pos-SLIDER_TRESHOLD)){
				previous_slider_pos = current_slide_pos;
			}
			else{
				current_slide_pos = 0;
			}
			send_msg.data[1] = current_slide_pos;
			
			if(solenoid_flag == 1){
				send_msg.data[2] = 1;
				solenoid_flag = 0;
			}
			
			if (rcv_msg.data[3] != 0){		//highscore value
				//printf("CAN highscore data\n");
				uint8_t temp_highscore = 115;//rcv_msg.data[3];
				menu_score(temp_highscore);
			}
		}
		else{
			menu_arrow();
			_delay_ms(100);
		}	
		
		send_CAN_message(&send_msg);
		
		rcv_msg.data[3] = 0;	//highscore value			<---
		
		rcv_CAN_message(& rcv_msg);
	}
	return 0;
}