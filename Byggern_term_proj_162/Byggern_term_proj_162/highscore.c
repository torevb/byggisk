//#include "highscore.h"

#include <stdio.h>
#include <stdint.h>

// #include "menu.h"
#include "OLED.h"


#define SCORE_TABLE_SIZE	6
#define MENU_HIGHSCORE_STRING	7


// int score_table[SCORE_TABLE_SIZE];
uint8_t score_table[SCORE_TABLE_SIZE];

void reset_highscores(){
	for (int i=0; i<SCORE_TABLE_SIZE; i++){
		score_table[i] = 0;
	}
}

void store_data(int8_t insert_data){
	int i = 0;
	uint8_t shiftvalue = 0;
	for (i=0; i<SCORE_TABLE_SIZE; i++){
		if (insert_data > score_table[i]){
			shiftvalue = score_table[i];
			score_table[i] = insert_data;
			break;
		}
	}
	for (i=i+1; i<SCORE_TABLE_SIZE; i++){
		//printf("\tshiftvalue %i", shiftvalue);
		uint8_t temp = score_table[i];
		score_table[i] = shiftvalue;
		shiftvalue = temp;
	}
	//printf("\n");
}

void score_print(){
	for (int i=0; i<SCORE_TABLE_SIZE; i++){
		printf("%i, \n", score_table[i]);
	}
}

void print_to_OLED(char * inputstring, int offset){
	for (int i=0; i<offset; i++){
		printf(" ");
	}
	printf(inputstring);
}

void menu_highscore(){
	char string_print[MENU_HIGHSCORE_STRING];
	//print_to_OLED("Back     > Highscore < \n", 2);
	for (int i=0; i<SCORE_TABLE_SIZE; i++){
		sprintf(string_print, "%i\n", score_table[i]);
		print_to_OLED(string_print, 2);
	}
}


int main(){
	reset_highscores();
	// score_print();
	
	store_data(10);
	store_data(9);
	store_data(11);
	store_data(54);
	store_data(2);
	store_data(2);
	store_data(7);
	store_data(72);
	store_data(72);
	store_data(72);
	//score_print();
	
	menu_highscore();
	
	
	return 0;
}




