#include "SRAM.h"

#include "memory_interface.h"




void SRAM_init(){
	memory_init();
	SRAM_clear();
}

void SRAM_clear(){
	uint16_t ext_ram_size = 0x800;
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
	for (int i = 0; i < ext_ram_size; i++){
		ext_ram[i] = 0;
	}
}

void SRAM_write(uint8_t * input, uint16_t input_position, uint16_t input_size){
	uint16_t ext_ram_size = 0x800;
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
	if (input_size >= ext_ram_size - input_position){
		input_size = ext_ram_size - input_position;
	}
	for (int i = 0; i < input_size; i++){
		ext_ram[input_position + i] = input[i];
	}
}

uint8_t* SRAM_read(uint16_t output_position, uint16_t output_size){
	uint16_t ext_ram_size = 0x800;
	uint8_t output[SRAM_OUTPUT_SIZE];
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
	if (output_size >= ext_ram_size - output_position){
		output_size = ext_ram_size - output_position;
	}
	for (int i = 0; i < output_size; i++){
		ext_ram[output_position + i] = output[i];
	}
	return output;
}

