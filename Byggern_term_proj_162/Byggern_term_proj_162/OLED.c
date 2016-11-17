#include "OLED.h"


#include "font.h"
#include <avr/pgmspace.h>
#include <string.h>
#include "joy_ctrl.h"



#define ARROW_WIDTH			8 //5 +3 for readability



static uint8_t current_column;
static uint8_t current_page;



void OLED_init()
{
	write_OLED_cmd(0xae);        //  display  off
	write_OLED_cmd(0xa1);        //segment  remap
	write_OLED_cmd(0xda);        //common  pads  hardware:  alternative
	write_OLED_cmd(0x12);
	write_OLED_cmd(0xc8);        //common output scan direction:com63~com0
	write_OLED_cmd(0xa8);        //multiplex  ration  mode:63
	write_OLED_cmd(0x3f);
	write_OLED_cmd(0xd5);        //display divide ratio/osc. freq. mode
	write_OLED_cmd(0x80);
	write_OLED_cmd(0x81);        //contrast  control
	write_OLED_cmd(0x50);
	write_OLED_cmd(0xd9);        //set  pre-charge  period
	write_OLED_cmd(0x21);
	write_OLED_cmd(0x20);        //Set  Memory  Addressing  Mode to page mode.
	write_OLED_cmd(0x02);
	write_OLED_cmd(0xdb);        //VCOM  deselect  level  mode
	write_OLED_cmd(0x30);
	write_OLED_cmd(0xad);        //master  configuration sets external Iref. 
	write_OLED_cmd(0x00);	
	write_OLED_cmd(0xa4);        //out  follows  RAM  content
	write_OLED_cmd(0xa6);        //set  normal  display
	write_OLED_cmd(0xaf);        //  display  on
	
	
	//write_OLED_cmd(0xA7);		//Inverse display.
	//write_OLED_cmd(0xA5);		//Output ignores RAM content. 
	
	
	OLED_reset();
	set_font4x6();
}


void write_OLED_cmd(uint8_t number){
	volatile char *ext_oled_cs = (char *) 0x1000;
	*ext_oled_cs = number;
}

void write_OLED_data(uint8_t number){
	volatile char *ext_oled_dc = (char *) 0x1200;
	*ext_oled_dc = number;
}


void OLED_reset(){
	write_OLED_cmd(0x40);		//Set display line start at page 0. 
	for (uint8_t i = 0; i < DISPLAY_PAGES; i++){
		clear_OLED_page(i);
	}
	OLED_home();
	return;
}

void OLED_home(){
	goto_OLED_page(0);
	goto_OLED_char_column(0);
	return;
}

void goto_OLED_page(uint8_t page){
	current_page = page % DISPLAY_PAGES;
	write_OLED_cmd(0xB0 + current_page);
	return;
}

void goto_OLED_char_column(uint8_t column){
	uint8_t c = column * font_type.width;
	uint8_t low_bits = c & 0x0f;
	uint8_t high_bits = c & 0xf0;
	write_OLED_cmd(0x00 + low_bits);
	write_OLED_cmd(0x10 + (high_bits >> 4));
	
	current_column = column;
	return;
}

void clear_arrow_space(){
	int temp_page = current_page;
	int temp_col = current_column;
	for (uint8_t j = 0; j < DISPLAY_PAGES; j++){
		goto_OLED_page(j);
		for (uint8_t i = 0; i < ARROW_WIDTH; i++){
			goto_OLED_physical_column(i);
			write_OLED_data(0);
		}
	}
	current_page = temp_page;
	current_column = temp_col;
	return;
}

void goto_OLED_physical_column(uint8_t column){
	uint8_t low_bits = column & 0x0f;
	uint8_t high_bits = column & 0xf0;
	write_OLED_cmd(0x00 + low_bits);
	write_OLED_cmd(0x10 + (high_bits >> 4));
	
	current_column = column;
	return;
}

void clear_OLED_page(uint8_t page){
	goto_OLED_page(page);
	for (uint8_t i = 0; i < DISPLAY_COLUMNS; i++){
		write_OLED_data(0);
	}
	return;
}



void OLED_pos(uint8_t page, uint8_t column){
	return;
}

void print_to_OLED(const char * string, uint8_t start_column){
	goto_OLED_char_column(start_column);
	int length = strlen(string);
	
	for (int i = 0; i < length; i++){
		char c = string[i];
		if (c == '\n') {
			goto_OLED_page((current_page + 1) % DISPLAY_PAGES);
			goto_OLED_char_column(start_column);
		}
		else{
			for (int j = 0; j < font_type.width; j++){
				write_OLED_data(pgm_read_byte(font_type.data + (c - font_type.ascii_offset) * font_type.width +j));
				//write_OLED_data(pgm_read_byte(&font[c-font_type.ascii_offset][j]));
				//write_OLED_data(pgm_read_byte(&font_type.data[c-font_type.ascii_offset][j]));
				current_column = current_column + font_type.width;
			}
		}
	}
	return;
}

void OLED_print_arrow(uint8_t page)
{	int temp = current_page;
	goto_OLED_page(page);
	goto_OLED_physical_column(1);
	
	write_OLED_data(0b00011000);
	write_OLED_data(0b00011000);
	write_OLED_data(0b01111110);
	write_OLED_data(0b00111100);
	write_OLED_data(0b00011000);
	current_column = ARROW_WIDTH;
	
	goto_OLED_page(temp);
}

void OLED_print_square(uint8_t page,uint8_t column){
	int temp_page = current_page;
	int temp_column=current_column;
	goto_OLED_page(page);
	goto_OLED_physical_column(column);
	write_OLED_data(0b11111111);
	write_OLED_data(0b11111111);
	write_OLED_data(0b11111111);
	write_OLED_data(0b11111111);
	current_column=temp_column+4;
	goto_OLED_page(temp_page);
	
}


void draw_OLED(){
	
	while(1){
		OLED_print_square(current_page,current_column);
		_delay_ms(10);
	}
	
}




