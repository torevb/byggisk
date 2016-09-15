/*
 * memory_interface.c
 *
 * Created: 15.09.2016 15:32:10
 *  Author: marthauk
 */ 

#include <stdlib.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>


void memory_init(void){
	MCUCR|=(1<<SRE);
	SFIOR|=(1<<XMM2);
}