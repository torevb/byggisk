#pragma once

#include "SRAM_test.h"
#include <avr/io.h>



void OLED_init(void);

void write_OLED_cmd(uint8_t number);

void write_OLED_data(uint8_t number);


void OLED_reset(void);

void OLED_home(void);

/*A page is equivalent to a one-byte row */
void goto_OLED_page(uint8_t page);

void goto_OLED_column(uint8_t column);

void clear_OLED_page(uint8_t page);

void OLED_pos(uint8_t page, uint8_t column);

void print_to_OLED(const char *temp);


