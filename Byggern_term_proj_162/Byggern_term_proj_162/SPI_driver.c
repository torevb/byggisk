#include <avr/io.h>


#include "SPI_driver.h"



#define SSn		4
#define MOSI	5
#define MISO	6
#define SCK		7



void SPI_init(){
	DDRB |= (1<<MOSI) | (1<<SCK) | (1<<SSn);		//Set MOSI, SCK, SSn output.
	DDRB &= ~((1<<MISO));		//Set MISO input.
	PORTB|=(1<<MISO);
	SPCR |= (1<<SPE) | (1<<MSTR)|(1<<SPR0);	//Enable SPI, Master, set clock rate fck/16.
}


void send_SPI(char data){
	
	SPDR = data;			//Send data.
	while (!(SPSR & (1<<SPIF))) {}		//Wait for transmission complete.
	
}

char read_SPI(){	
	send_SPI(0xFF);		//Send dummy byte.		
	while (!(SPSR & (1<<SPIF))) {}		//Wait for transmission complete.
	return SPDR;
}

void spi_chipselect_activate(){
	PORTB |=(1<<SSn);
}

void spi_chipselect_deactivate(){
	PORTB &=~(1<<SSn);
}


