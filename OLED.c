#include "OLED.h"


#include "font.h"




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
	write_OLED_cmd(0x20);        //Set  Memory  Addressing  Mode
	write_OLED_cmd(0x02);
	write_OLED_cmd(0xdb);        //VCOM  deselect  level  mode
	write_OLED_cmd(0x30);
	write_OLED_cmd(0xad);        //master  configuration
	write_OLED_cmd(0x00);
	write_OLED_cmd(0xa4);        //out  follows  RAM  content
	write_OLED_cmd(0xa6);        //set  normal  display
	write_OLED_cmd(0xaf);        //  display  on
}


void write_OLED_cmd(int8_t number){
	volatile char *ext_oled_cs = (char *) 0x1000;
	*ext_oled_cs = number;
}

void write_OLED_data(int8_t number){
	volatile char *ext_oled_dc = (char *) 0x1200;
	*ext_oled_dc = number;
}


void OLED_reset(){
	return;
}

void OLED_home(){
	return;
}

void OLED_goto_page(int page){
	write_OLED_cmd(0xB0 + page);
	return;
}

void OLED_goto_column(int column){
	
	return;
}

void OLED_clear_line(int line){
	return;
}

void OLED_pos(int row, int column){
	return;
}

void OLED_print(const char *c){
	//write_OLED_data(0xFF);
	//write_OLED_data(pgm_read_byte(font + c));
	//write_OLED_data(pgm_read_word(font + c));
	
	
	//OLED_goto_page(0);
	//write_OLED_data(0xFF);
	
	/*
	for (int i = 0; i < 95; i++){
		if (strcmp_P(c, font[i])){
			write_OLED_data(*font[i]);
		}
	}*/
	
	return;
}









