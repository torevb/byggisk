
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>

//#define F_CPU 1000000UL  //for <util/delay.h>
#include <util/delay.h> //for _delay_ms()

#include "uart.h"
#include "SRAM_test.h"
#include "GAL_test.h"
#include "joy_ctrl.h"
#include "slide.h"
#include "OLED.h"
#include "memory_interface.h"
#include "menu.h"
//#include "font.h"
#include "SPI_driver.h"
#include "MCP2515_driver.h"
#include "CAN_test.h"
#include "CAN_driver.h"
#include "CAN MCP2515 header files/MCP2515.h"


#define BAUD 9600
#define FOSC 4915200
#define MYUBRR FOSC/16/BAUD-1


int main(void)
{	
	DDRE=0x3;
	DDRA=0xFF;
	PORTA=0x00;
	PORTE=0x2;
	
	
	
	memory_init();
	UART_Init(MYUBRR);
	printf("Atmega162 start\n");
	
	CAN_init();
	slider_init();
	//solenoid_init();
	menu_init();
	joy_init();
	menu_print();
	CAN_struct slidemsg;
	slidemsg.ID=SLIDER_ID;
	while(1){
		/*joy_relative_pos();
		int trudeluu = rel_position.x_pos;
		
		joyfull.data[0] = trudeluu;
		joyfull.length=1;
		printf("Sending this data : %i\n",joyfull.data[0]);
		
		send_CAN_message(joyfull);
		
		*/
		//uint8_t sliderpos=get_slider_pos(SLIDE_L);
		//printf("Sliderpos: %i\n",sliderpos);
	
		slidemsg.data[0] = get_slider_pos(SLIDE_L);
		slidemsg.length=1;
		printf("Sending this data : %i\n",slidemsg.data[0]);
		
		send_CAN_message(slidemsg);
		
			
	}
	
	
	return 0;
	
}