
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>

#include <util/delay.h> //for _delay_ms()

#include "uart.h"
#include "joy_ctrl.h"
#include "slide.h"
#include "OLED.h"
#include "memory_interface.h"
#include "menu.h"
#include "SPI_driver.h"
#include "MCP2515_driver.h"
#include "SRAM.h"
#include "highscore.h"

#include "CAN_driver.h"
#include "../../CAN MCP2515 header files/MCP2515.h"

#define SLIDER_TRESHOLD 5
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
	reset_highscores();
	menu_init();
	
	CAN_struct send_msg;
	send_msg.ID = NODE1_ID;
	send_msg.length=4;
	
	CAN_struct rcv_msg;
	rcv_msg.ID = RCV_ID;
	rcv_msg.length = 4;
	
	
	int8_t previous_slider_pos=-128;
	uint8_t current_highscore = 0;
	uint8_t previous_highscore=0;

	leave_game_flag = 0;
	
	send_msg.data[3] = 0;	//highscore value
	
	rcv_msg.data[0] = 0;	//joy_x
	rcv_msg.data[1] = 0;	//slider_left
	rcv_msg.data[2] = 0;	//button_left / interrupt
	
	
	menu_print();
	

	
	while(1){
		printf("alive\n");
		
		send_msg.data[0] = 0;	//joy_x						<---
		send_msg.data[1] = 0;	//slider_left				<---
		send_msg.data[2] = 0;	//button_left / interrupt	<---
		
		joy_relative_pos();
		
		if (current_node==&ingame_node){
			int8_t current_joy_x = rel_position.x_pos;
			send_msg.data[0] = current_joy_x;
			//printf("joy_x %i\n", current_joy_x);
			
			int8_t current_slide_pos = get_slider_pos(SLIDE_L);
			if((current_slide_pos>=previous_slider_pos+SLIDER_TRESHOLD)||(current_slide_pos<=previous_slider_pos-SLIDER_TRESHOLD)){
				previous_slider_pos = current_slide_pos;
			}
			else{
				current_slide_pos = 0;
			}
			send_msg.data[1] = current_slide_pos;
			
			if(solenoid_flag == 1){ /* detected button push->send data*/
				send_msg.data[2] = 1;
				solenoid_flag = 0;
			}
			
			if (rcv_msg.data[3] != 0){		//highscore value
				current_highscore += rcv_msg.data[3];
				menu_score(current_highscore);
				previous_highscore=current_highscore;
			}
		}
		else if (leave_game_flag == 1){
			store_highscore(current_highscore);
			current_highscore=0;
			previous_highscore=0;
			leave_game_flag = 0;
		}
		else if (current_node == &highscore_node){
			menu_highscore();
			_delay_ms(400);
		}
		else if(current_node== &draw_node){
		
			draw_OLED();
			_delay_ms(200);
		}
		else{
			menu_arrow();
			_delay_ms(400);
		}	
		
		send_CAN_message(&send_msg);
		
		rcv_msg.data[3] = 0;	//highscore value			<---
		
		rcv_CAN_message(& rcv_msg);
		
	}
	return 0;
}