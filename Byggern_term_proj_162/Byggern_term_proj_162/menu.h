#pragma once

#include <stdint.h>



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
node ingame_node;
node calibrate_joy_node;

node * current_node;

uint8_t highscore;

void menu_init(void);

void menu_print(void);

void menu_arrow();



