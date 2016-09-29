#include "menu.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "OLED.h"



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

node * current_pointer;




void menu_init(){

	
	root_node.name = "Main menu";
	root_node.parent = NULL;
	root_node.children[0] = &playgame_node;
	root_node.children[1]=&highscore_node;
	root_node.content_string = "Play game \nHighscores \nSettings";

	playgame_node.name = "Play game";
	playgame_node.parent = &root_node;
	for (int i=0; i<7;i++){
		playgame_node.children[i]=NULL; 
	}
	
	playgame_node.content_string = "new game, 1v1, 1vpc";

	highscore_node.name = "Highscore";
	highscore_node.parent = &root_node;
	for (int i=0; i<7;i++){
		highscore_node.children[i]=NULL;
	}
	//highscore_node.children	= {NULL,NULL,NULL,NULL,NULL,NULL,NULL};
	highscore_node.content_string = "player 1 score \nPlayer 2 score.";

	settings_node.name = "Settings";
	settings_node.parent = &root_node;
	for (int i=0; i<7;i++){
		settings_node.children[i]=NULL;
	}
	//settings_node.children	= {NULL,NULL,NULL,NULL,NULL,NULL,NULL};//calibrate_node, volume_node;
	settings_node.content_string = "calibrate_node \nVolume_node";
	
	
	current_pointer = &root_node;
	menu_print();		
	
	
		
}




void menu_print(){
	

	print_to_OLED(current_pointer->children[1]->content_string, 2);
	
	
}


