#pragma once

#include <stdint.h>



typedef struct node{
	struct node * parent;
	struct node * children[7];
	char * name;
	char * content_string;
}node;



node root_node;
node highscore_node;
node draw_node;
node ingame_node;


node * current_node;

uint8_t highscore;
uint8_t solenoid_flag;

void menu_init(void);

void menu_print(void);

void menu_arrow();



