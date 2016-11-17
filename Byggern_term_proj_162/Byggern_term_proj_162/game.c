#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>

#include "slide.h"
#include "OLED.h"
#include "menu.h"
#include "game.h"
#include "CAN_driver.h"
#include "../../CAN MCP2515 header files/MCP2515.h"



//#define DEBUG 0



void game_init(){
	DDRE=0x3;
	PORTE=0x2;
	DDRA=0xFF; //All A pins set as output 
	PORTA=0x00; 
	rcv_new_highscore_flag=0;
	
	/*Initializing all we need to play the game*/
	memory_init();
	CAN_init();
	slider_init();	
	joy_init();
	menu_init();
	
	
}

void play_game(){
	menu_print();
	
	rcv_new_highscore_flag=0; 
	CAN_struct joy_msg;
	joy_msg.ID=JOYSTICK_ID;
	
	while(current_node==&ingame_node){
		/*Need to print new menu if we receive new highscore only*/
		if(rcv_new_highscore_flag){
			menu_score(highscore);
		}
		joy_relative_pos();
	
		int8_t x_pos  = rel_position.x_pos;
		
		joy_msg.data[0] = x_pos;
		joy_msg.length=1;
		send_CAN_message(joy_msg);
			
	}	
 	
}


void draw_game(){
	menu_print();
	
	
	while (current_node == &draw_node){
		draw_OLED();
		
		_delay_ms(100);
	}
	
}