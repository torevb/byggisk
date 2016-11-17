#pragma once

#include "SRAM_test.h"
#include <avr/io.h>

#define DISPLAY_PAGES		8
#define DISPLAY_COLUMNS		128

struct {
	uint8_t width;
	uint8_t height;
	uint8_t ascii_offset;
	char *data;
}font_type;




void OLED_init(void);

void write_OLED_cmd(uint8_t number);

void write_OLED_data(uint8_t number);


void OLED_reset(void);

void OLED_home(void);

/*A page is equivalent to a one-byte row */
void goto_OLED_page(uint8_t page);

/* 0-63 (dec) step */
void goto_OLED_char_column(uint8_t column);

void clear_arrow_space();
	
/* 0-127 (dec) step */
void goto_OLED_physical_column(uint8_t column);

void clear_OLED_page(uint8_t page);

void OLED_pos(uint8_t page, uint8_t column);

void print_to_OLED(const char * string, uint8_t start_column);

void OLED_print_arrow (uint8_t page);

void OLED_print_square(uint8_t page,uint8_t column);

void draw_OLED();

void goto_next_pixel();
