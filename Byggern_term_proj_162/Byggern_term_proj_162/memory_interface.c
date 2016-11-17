#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>



void memory_init(void){
	MCUCR|=(1<<SRE);
	SFIOR|=(1<<XMM2);
}
