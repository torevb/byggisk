#include "menu.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "solenoid.h"

#include "OLED.h"
#include "joy_ctrl.h"



/*struct node{
	struct node * parent;
	struct node * children;
	char * name;
	char * content_string;
} ;*/

typedef struct node{
	struct node * parent;
	struct node * children[7];
	char * name;
	char * content_string;
}node;

node root_node;
node playgame_node;
node highscore_node;
node settings_node;
node draw_node;

node * current_node;

uint8_t arrow_page;



void menu_init(){
	OLED_init();
	
	root_node.name = "        > Main menu < \n";
	root_node.parent = &root_node;
	root_node.children[0] = &playgame_node;
	root_node.children[1] = &highscore_node;
	root_node.children[2] = &settings_node;
	root_node.children[3]= &draw_node;
	root_node.content_string = "Play game \nHighscores \nSettings\n";

	playgame_node.name = "Back    > Play game < \n";
	playgame_node.parent = &root_node;
	for (int i=0; i<7;i++){
		playgame_node.children[i]=NULL; 
	}
	playgame_node.content_string = "new game \n1v1 \n1vsComputer \n";

	highscore_node.name = "Back     > Highscore < \n";
	highscore_node.parent = &root_node;
	for (int i=0; i<7;i++){
		highscore_node.children[i]=NULL;
	}
	highscore_node.content_string = "Player1 score. \nPlayer2 score. \n";

	settings_node.name = "Back     > Settings < \n";
	settings_node.parent = &root_node;
	for (int i=0; i<7;i++){
		settings_node.children[i]=NULL;
	}
	settings_node.content_string = "calibrate_node \nvolume_node \n";
	
	draw_node.name = "Drawing board ";
	draw_node.parent = &root_node;
	for (int i=0; i<7;i++){
		draw_node.children[i]=NULL;
	}
	//draw_node.content_string = draw_OLED();
	
	
	
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
	if (current_node == &playgame_node){
		push_solenoid();
	}
	else{
		if (arrow_page <= 0){
			current_node = current_node->parent;
			} else if (!(current_node->children[arrow_page - 1] == NULL)){
			current_node = current_node->children[arrow_page -1];
		}
		arrow_page = 0;
		menu_print();
	}
}

ISR(INT1_vect){
	current_node = current_node->parent;
	menu_print();
}

void menu_print(){
	//print_to_OLED(current_node->children[0]->content_string, 2);
	OLED_reset();
	print_to_OLED(current_node->name, 2);
	print_to_OLED(current_node->content_string, 2);
	OLED_print_arrow(arrow_page);
}


