#include "menu.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#include "solenoid.h"
#include "OLED.h"
#include "joy_ctrl.h"
#include "CAN_driver.h"



uint8_t arrow_page;



void menu_init(){
	OLED_init();
	
	root_node.name = "        > Main menu < \n";
	root_node.parent = &root_node;
	for (int i=0; i<7;i++){ root_node.children[i] = NULL; }
	root_node.children[0] = &playgame_node;
	root_node.children[1] = &highscore_node;
	root_node.children[2] = &settings_node;
	root_node.children[3] = &draw_node;
	root_node.content_string = "Play Ping-Pong game \nHighscores \nSettings \nDraw a doodle \n";

	playgame_node.name = "Back    > New game < \n";
	playgame_node.parent = &root_node;
	for (int i=0; i<7;i++){ playgame_node.children[i] = NULL; }
	playgame_node.children[0] = &ingame_node; 	//Holder kanskje uten denne ekstra noden?
	playgame_node.content_string = "Play game \n";	

	highscore_node.name = "Back     > Highscore < \n";
	highscore_node.parent = &root_node;
	for (int i=0; i<7;i++){ highscore_node.children[i] = NULL; }
	highscore_node.content_string = "Player1 score. \nPlayer2 score. \n";

	settings_node.name = "Back     > Settings < \n";
	settings_node.parent = &root_node;
	for (int i=0; i<7;i++){ settings_node.children[i] = NULL; }
	settings_node.content_string = "Clear highscore \nCalibrate joystick \nTest SRAM \nCalibrate motor encoder \n";
	
	draw_node.name = "         > Drawing board < \n";
	draw_node.parent = &root_node;
	for (int i=0; i<7;i++){ draw_node.children[i] = NULL; }
	//draw_node.content_string = draw_OLED();
	
	calibrate_joy_node.name = "         > Calibrate joystick < \n";
	calibrate_joy_node.parent = &settings_node;
	for (int i=0; i<7;i++){ calibrate_joy_node.children[i] = NULL; }
	calibrate_joy_node.content_string = "Reset axis offset \nIncrease neutral zone \nDecrease neutral zone \n";
	
	ingame_node.name = "         > In-game < \n";
	ingame_node.parent = &playgame_node;
	for (int i=0; i<7;i++){ ingame_node.children[i] = NULL; }
	ingame_node.content_string = "\nCurrent score: \n";
	
	
	current_node = &playgame_node;//&root_node;
	arrow_page = 0;
}

void menu_arrow(){
	clear_arrow_space();
	int direction = get_joy_direction();
	if (direction == 0){
	} else if (direction == 3){
		arrow_page = arrow_page -1 % DISPLAY_PAGES;
	} else if (direction == 4){
		arrow_page = arrow_page +1 % DISPLAY_PAGES;
	}
	OLED_print_arrow(arrow_page);
}

/* Left slider button, INT0_vect, pin PD2. Right slider button, INT1_vect, pin PD3.*/
ISR(INT0_vect){//, INT1_vect){
	if (current_node == &ingame_node){
		CAN_struct solenoide_push;
		solenoide_push.ID= SOLENOIDE_PUSH_ID;
		solenoide_push.data[0]=0;
		solenoide_push.length=1;
		if (DEBUG) { printf("Sending following message :\n ID: %i \n data: %i\n length %i",solenoide_push.ID,solenoide_push.data[0],solenoide_push.length); }
		send_CAN_message(solenoide_push);
		
		
		//push_solenoid();
	}
	else{	//This means we are in normal menu mode.
		if (arrow_page <= 0){
			current_node = current_node->parent;
		} else if (!(current_node->children[arrow_page - 1] == NULL)){
			current_node = current_node->children[arrow_page -1];
		}
		arrow_page = 0;
		menu_print();
	}
}

/*Used for going backwards/upwards in menu*/
ISR(INT1_vect){
	current_node = current_node->parent;
	menu_print();
}

void menu_print(){
	//print_to_OLED(current_node->children[0]->content_string, 2);
	OLED_reset();
	print_to_OLED(current_node->name, 2);
	print_to_OLED(current_node->content_string, 2);
	if ((current_node != &ingame_node) | (current_node != &draw_node)){
		OLED_print_arrow(arrow_page);
	}
}

//Call when in-game.
void menu_score(uint8_t score){
	goto_OLED_page(2);
	//goto_OLED_page(3);
	char string[10];
	sprintf(string, "%i", score);
	//string = score + '0';
	print_to_OLED(string, 15);
}
