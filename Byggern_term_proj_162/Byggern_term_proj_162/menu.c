#include "menu.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#include "OLED.h"
#include "joy_ctrl.h"
#include "CAN_driver.h"

CAN_struct solenoide_push;


uint8_t arrow_page;



void menu_init(){
	OLED_init();
	
	root_node.name = "        > Main menu < \n";
	root_node.parent = &root_node;
	for (int i=0; i<3;i++){ root_node.children[i] = NULL; }
	root_node.children[0] = &ingame_node;
	root_node.children[1] = &highscore_node;
	root_node.children[2] = &draw_node;
	root_node.content_string = "Play Ping-Pong game \nHighscores \nDraw a doodle \n";

	highscore_node.name = "Back     > Highscore < \n";
	highscore_node.parent = &root_node;
	for (int i=0; i<3;i++){ highscore_node.children[i] = NULL; }
	highscore_node.content_string = " ";


	
	draw_node.name = "         > Drawing board < \n";
	draw_node.parent = &root_node;
	for (int i=0; i<3;i++){ draw_node.children[i] = NULL; }
	
	
	
	ingame_node.name = "         > In-game < \n";
	ingame_node.parent = &root_node;
	for (int i=0; i<3;i++){ ingame_node.children[i] = NULL; }
	ingame_node.content_string = "\nCurrent score: \n";
	
	
	
	current_node = &root_node; 
	arrow_page = 0;
}


void menu_arrow(){
	clear_arrow_space();
	int direction = get_joy_direction();
	if (direction == 0){
	} else if (direction == 3){
		arrow_page = (arrow_page -1) % DISPLAY_PAGES;
	} else if (direction == 4){
		arrow_page = (arrow_page +1) % DISPLAY_PAGES;
	}
	OLED_print_arrow(arrow_page);
}

/* Left slider button, INT0_vect, pin PD2. Right slider button, INT1_vect, pin PD3.*/
ISR(INT0_vect){
	
	if (current_node == &ingame_node){
		solenoid_flag = 1;
	}
	else if (current_node == &draw_node){
		OLED_reset();	
	}
	else{	//This means we are in normal menu mode.
		if (arrow_page <= 0){
			current_node = current_node->parent;
		} else if (!(current_node->children[arrow_page - 1] == NULL)){
			current_node = current_node->children[arrow_page -1];
		}
		arrow_page = 0;
		menu_print();
		if (current_node == &ingame_node){
			menu_score(0);
		}
	}
	
}

/*Used for going backwards/upwards in menu*/
ISR(INT1_vect){
	if (current_node == &ingame_node){
		leave_game_flag = 1;
	}
	
	current_node = current_node->parent;
	
	OLED_reset();
	menu_print();
}

void menu_print(){
	OLED_reset();
	print_to_OLED(current_node->name, 2);
	print_to_OLED(current_node->content_string, 2);
	if ((current_node != &ingame_node) | (current_node != &draw_node)){
		OLED_print_arrow(arrow_page);
	}
}

//Call when in-game.
void menu_score(uint8_t score){
	
	goto_OLED_page(0);
	char string[10];
	sprintf(string, "%i", score);
	
	print_to_OLED("         > In-game < \n\nCurrent score: ", 2);
	print_to_OLED(string, 20);
}

