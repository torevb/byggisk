#include "MCP2515_driver.h"
#include "SPI_driver.h"
#include "../../CAN MCP2515 header files/MCP2515.h"



void MCP2515_init(){
	SPI_init();
	reset_MCP2515();	
}


char read_MCP2515(char read_address){
	spi_chipselect_deactivate();
	send_SPI(0x03);	//'read' instruction. 
	send_SPI(read_address);
	
	char val=read_SPI();
	spi_chipselect_activate();
	return val;
}


void write_MCP2515(char write_address, char write_data){
	spi_chipselect_deactivate();
	send_SPI(0x02);	//'write byte' instruction.
	send_SPI(write_address);
	send_SPI(write_data);
	spi_chipselect_activate();
	
}

void request_to_send_MCP2515(char RTS_in){
	spi_chipselect_deactivate();
	RTS_in = RTS_in % 8;		//Ensures no more than 3 bits proceed.
	send_SPI(0x80 + RTS_in);

	spi_chipselect_activate();
}

char read_status_MCP2515(){
	spi_chipselect_deactivate();
	send_SPI(0xA0);		//'read status' instruction.
	char out = read_SPI();
	char repeat = read_SPI();
	spi_chipselect_activate();
	return out;
}

void bit_modify_MCP2515(char address, char mask_byte, char data){
	spi_chipselect_deactivate();
	send_SPI(0x05);	//'bit modify' instruction.
	send_SPI(address);
	send_SPI(mask_byte);
	send_SPI(data);
	spi_chipselect_activate();
}

void reset_MCP2515(){
	spi_chipselect_deactivate();
	send_SPI(0xC0);	//'reset' instruction.
	spi_chipselect_activate();
}


