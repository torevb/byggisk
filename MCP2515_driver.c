#include "MCP2515_driver.h"
#include "SPI_driver.h"
#include "CAN MCP2515 header files\MCP2515.h"



void MCP2515_init(){
	SPI_master_init();
}


char read_MCP2515(char read_address){
	//SPI_master_init() first
	send_master_SPI(0x03);	//'read' instruction. 
	send_master_SPI(read_address);
	return read_master_SPI();
}


void write_MCP2515(char write_address, char write_data){
	send_master_SPI(0x02);	//'write byte' instruction.
	send_master_SPI(write_address);
	send_master_SPI(write_data);
}

void request_to_send_MCP2515(char RTS_in){
	RTS_in = RTS_in % 8;		//Ensures no more than 3 bits proceed.
	send_master_SPI(0x80 + RTS_in);
}

char read_status_MCP2515(){
	send_master_SPI(0xA0);		//'read status' instruction.
	char out = read_master_SPI();
	char repeat = read_master_SPI();
	/*if (out != repeat){
		return repeat;
	}*/
	return out;
}

void bit_modify_MCP2515(char address, char mask_byte, char data){
	send_master_SPI(0x05);	//'bit modify' instruction.
	send_master_SPI(address);
	send_master_SPI(mask_byte);
	send_master_SPI(data);
}

void reset_MCP2515(){
	send_master_SPI(0xC0);	//'reset' instruction.
}


