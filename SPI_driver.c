#include <avr/io.h>


#include "SPI_driver.h"



#define SSn		4
#define MOSI	5
#define MISO	6
#define SCK		7



void SPI_master_init(){
	DDRB |= (1<<MOSI) | (1<<SCK) | (1<<SSn);		//Set MOSI, SCK, SSn output.
	DDRB &= ~((1<<MISO));		//Set MISO input.
	SPCR = (1<<SPE) | (1<<MSTR)|(1<<SPR0);	//Enable SPI, Master, set clock rate fck/16.
	//PINB &= !(1<<PB4);
}

void SPI_slave_init(){
	DDRB |= (1<<MISO);	//Set as output.
	DDRB &= ~((1<<MOSI)|(1<<SCK)|(1<<SSn)); //Set as input.
	SPCR = (1<<SPE);	//Enable SPI.
}

void send_master_SPI(char data){
	SPDR = data;				//Send data.
	while (!(SPSR & (1<<SPIF))) {}		//Wait for transmission complete.
	
}

char read_master_SPI(){
	//send_master_SPI(1);		//Send dummy byte.
	SPDR = 0x00;						
	while (!(SPSR & (1<<SPIF))) {}		//Wait for transmission complete.
	return SPDR;
}



void send_slave_SPI(){
	
}

char read_slave_SPI(){
	//send dummy byte for � dytte utp� datapakke.
	while (!(SPSR & (1<<SPIF))) {}
	return SPDR;
}

