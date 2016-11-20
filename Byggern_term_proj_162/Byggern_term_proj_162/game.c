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
	
