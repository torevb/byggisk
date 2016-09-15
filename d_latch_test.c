/*
 * d_latch_test.c
 *
 * Created: 08.09.2016 10:27:55
 *  Author: marthauk
 */ 
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>

#include "uart.h"



#define BAUD 9600
#define FOSC 4915200
#define MYUBRR FOSC/16/BAUD-1



//PORTE|=(1<<PE1);
//PORTA|=(1<<PA0);



