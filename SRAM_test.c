/*
 * SRAM_test.c
 *
 * Created: 08.09.2016 11:51:27
 *  Author: marthauk
 */ 

#include <stdlib.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include "memory_interface.h"



typedef unsigned int uint16_t;
typedef unsigned char uint8_t; 


void SRAM_clear(){
	uint16_t ext_ram_size = 0x800;
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
	for (int i = 0; i < ext_ram_size; i++){
		ext_ram[i] = 0;
	}
}


void SRAM_test(void)
{
	memory_init();
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
	uint16_t ext_ram_size = 0x800;
	uint16_t write_errors = 0;
	uint16_t retrieval_errors = 0;
	printf("Starting SRAM test...\n");
	// rand() stores some internal state, so calling this function in a loop will
	// yield different seeds each time (unless srand() is called before this function)
	uint16_t seed = rand();
	// Write phase: Immediately check that the correct value was stored
	srand(seed);
	for (uint16_t i = 0; i < ext_ram_size; i++) 
	{
		uint8_t some_value = rand();
		ext_ram[i] = some_value;
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n", i,retreived_value, some_value);
			write_errors++;
		}
	}
	// Retrieval phase: Check that no values were changed during or after the write phase
	srand(seed);
	// reset the PRNG to the state it had before the write phase
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
			retrieval_errors++;
		}
	}
	printf("SRAM test completed with\n%4d errors in write phase and\n%4d errors in retrieval phase\n\n", write_errors, retrieval_errors);
}


