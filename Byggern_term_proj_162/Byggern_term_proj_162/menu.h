#pragma once

#include <stdint.h>



typedef struct node{
	struct node * parent;
	struct node * children[2];
	char * name;
	char * content_string;
}node;



node root_node;
node draw_node;
node ingame_node;


node * current_node;

uint8_t highscore;

void menu_init(void);

void menu_print(void);

void menu_arrow();



