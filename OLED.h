#pragma once

#include "SRAM_test.h"
#include <avr/io.h>



void OLED_init(void);

void write_OLED_cmd(int8_t number);

void write_OLED_data(int8_t number);


void OLED_reset(void);

void OLED_home(void);

void OLED_goto_line(int line);

void OLED_goto_column(int column);

void OLED_clear_line(int line);

void OLED_pos(int row, int column);

void OLED_print(const char *temp);


