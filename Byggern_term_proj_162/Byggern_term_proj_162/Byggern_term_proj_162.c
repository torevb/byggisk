
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>

//#define F_CPU 1000000UL  //for <util/delay.h>
#include <util/delay.h> //for _delay_ms()

#include "uart.h"

#include "joy_ctrl.h"
#include "slide.h"
#include "OLED.h"
#include "memory_interface.h"
#include "menu.h"
//#include "font.h"
#include "SPI_driver.h"
#include "MCP2515_driver.h"
//#include "CAN_test.h"
#include "CAN_driver.h"
#include "../../CAN MCP2515 header files/MCP2515.h"
#define SLIDER_TRESHOLD 10

#define BAUD 9600
#define FOSC 4915200
#define MYUBRR FOSC/16/BAUD-1


int main(void)
{	
	DDRE=0x3;
	DDRA=0xFF;
	PORTA=0x00;
	PORTE=0x2;
	
	SRAM_init();
	UART_Init(MYUBRR);
	printf("Atmega162 start\n");
	

	CAN_init();
	slider_init();
	joy_init();
	

	menu_init();
		
	//game_init();	//Includes all inits necessary to be able to play the game and navigate in menu

	//play_game();
	menu_print();
	CAN_struct msg;
	msg.length=1;
	int8_t previous_slider_pos=-128;
	int8_t current_slide_pos=-128;
	while(1){
		menu_arrow();
		
		//play_game();  //menu_print(); while(current_node == &ingame_node){ }
			
		if(current_node==&ingame_node){
			current_slide_pos=get_slider_pos(SLIDE_L);
			//printf("Current s pos: %i\n",current_slide_pos);
			if((current_slide_pos>=previous_slider_pos+SLIDER_TRESHOLD)||(current_slide_pos<=previous_slider_pos-SLIDER_TRESHOLD)){
				msg.ID=SLIDER_ID;
				msg.data[0]=current_slide_pos;
				previous_slider_pos=current_slide_pos;
				send_CAN_message(msg);
			}
			else{			
					joy_relative_pos();
					msg.ID=JOYSTICK_ID;
					int8_t x_pos  = rel_position.x_pos;
					//printf("halla\n");
					msg.data[0] = x_pos;
					
					//printf("Sending this shit , ID: %i , data : %i\n",msg.ID,msg.data[0]);
					send_CAN_message(msg);
			}	

		}

		//draw_game();  //menu_print(); while(current_node == &draw_node){ }
		_delay_ms(10);
	}
	
	
	
	
	return 0;
	
}