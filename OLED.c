#include "OLED.h"


#include "font.h"



#define DISPLAY_PAGES		8
#define DISPLAY_COLUMNS		128



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
	write_OLED_cmd(0x20);        //Set  Memory  Addressing  Mode to horizontal mode.
	write_OLED_cmd(0x00);
	write_OLED_cmd(0xdb);        //VCOM  deselect  level  mode
	write_OLED_cmd(0x30);
	write_OLED_cmd(0xad);        //master  configuration sets external Iref. 
	write_OLED_cmd(0x00);	
	write_OLED_cmd(0xa4);        //out  follows  RAM  content
	write_OLED_cmd(0xa6);        //set  normal  display
	write_OLED_cmd(0xaf);        //  display  on
	
	//write_OLED_cmd(0xA7);		//Inverse display.
	//write_OLED_cmd(0xA5);		//Output ignores RAM content. 
	
	//OLED_reset();
	//OLED_home();
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
	for (uint8_t i = 0; i < DISPLAY_PAGES; i++){
		goto_OLED_page(i);
		for (uint8_t j = 0; j < DISPLAY_COLUMNS; j++){
			goto_OLED_column(j);
			write_OLED_data(0);
		}
	}
	return;
}

void OLED_home(){
	goto_OLED_page(0);
	goto_OLED_column(0);
	return;
}

void goto_OLED_page(uint8_t page){
	if (page >= DISPLAY_PAGES){
		printf("Error at goto_OLED_page. %ui max input.\n", DISPLAY_PAGES);
	}
	write_OLED_cmd(0xB0 + page);
	return;
}

void goto_OLED_column(uint8_t column){
	if (column >= DISPLAY_COLUMNS){
		printf("Error at goto_OLED_column. %ui max input.\n", DISPLAY_COLUMNS);
	}
	
	//??
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

void print_to_OLED(const char *c){
	write_OLED_data(0xAA);
	//write_OLED_data(pgm_read_byte(font + c));
	//write_OLED_data(pgm_read_word(font + c));
	
	
	//goto_OLED_page(0);
	//write_OLED_data(0xFF);
	
	/*
	for (int i = 0; i < 95; i++){
		if (strcmp_P(c, font[i])){
			write_OLED_data(*font[i]);
		}
	}*/
	
	return;
}









