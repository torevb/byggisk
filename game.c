
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>

#include "slide.h"
#include "OLED.h"
#include "menu.h"


#include "CAN_driver.h"
#include "CAN MCP2515 header files/MCP2515.h"

void game_init(){
	
	DDRE=0x3;
	PORTE=0x2;
	DDRA=0xFF; //All A pins set as output 
	PORTA=0x00; 
	
	
	/*Initializing all we need to play the game*/
	memory_init();
	CAN_init();
	slider_init();	
	menu_init();
	joy_init();

}

void play_game(){
	menu_print();
	
	rcv_new_highscore_flag=0; 
	CAN_struct joy_msg;
	joy_msg.ID=JOYSTICK_ID;
	
	while(current_node==&ingame_node){
		/*Need to print new menu if we receive new highscore only*/
		if(rcv_new_highscore_flag){
			menu_print();
		}
		joy_relative_pos();
		int8_t x_pos  = rel_position.x_pos;
		
		joy_msg.data[0] = x_pos;
		joy_msg.length=1;
		
		send_CAN_message(joy_msg);
			
	}	
 	
}