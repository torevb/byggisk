#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>



#define SRAM_SCORE_AREA 100	//kun arbeid i dette området.
#define SRAM_SCORE_SIZE 10
#define SRAM_OUTPUT_SIZE 0x800



//typedef unsigned int uint16_t;	//disse er vel inkludert i <stdint.h>?
//typedef unsigned char uint8_t; 



void SRAM_init();

void SRAM_clear();

void SRAM_write(uint8_t * input, uint16_t input_size);

uint8_t* SRAM_read(uint16_t output_position, uint16_t output_size);

