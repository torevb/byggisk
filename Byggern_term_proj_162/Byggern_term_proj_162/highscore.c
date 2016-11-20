
#include <stdio.h>
#include <stdint.h>

#include "OLED.h"
#include "highscore.h"


#define SCORE_TABLE_SIZE	6
#define MENU_HIGHSCORE_STRING	7


uint8_t score_table[SCORE_TABLE_SIZE];

void reset_highscores(){
	for (int i=0; i<SCORE_TABLE_SIZE; i++){
		score_table[i] = 0;
	}
}

void store_highscore(int8_t insert_data){
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
		uint8_t temp = score_table[i];
		score_table[i] = shiftvalue;
		shiftvalue = temp;
	}
}

void score_print(){
	for (int i=0; i<SCORE_TABLE_SIZE; i++){
		printf("%i, \n", score_table[i]);
	}
}


void menu_highscore(){
	OLED_reset();
	goto_OLED_page(0);
	char string_print[MENU_HIGHSCORE_STRING];
	print_to_OLED("Back     > Highscore < \n", 2);
	for (int i=0; i<SCORE_TABLE_SIZE; i++){
		sprintf(string_print, "%i\n", score_table[i]);
		print_to_OLED(string_print, 2);
	}
}
