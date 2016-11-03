#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "CAN_driver.h"
#include "TWI_Master.h"
#include <avr/interrupt.h>
#include "uart.h"

#define DIR PH1
#define SEL PH3
#define EN PH4
#define OEn PH5
#define RST PH6
#define SCL PD0
#define SDA PD1


#define TWI_DAC_SLAVE_ADDR 0b01010000

/*motor baud rate is 115200*/

void motor_init(){
	TWI_Master_Initialise();
	CAN_init();
	DDRD |= (1<<SCL) | (1<<SDA);	//Set SCL and SDA as output. 
	TWBR = 12;// Set SCK on TWI to 400kbps
	
	DDRH= 0xFF; //setting all PINH to output.
	PINH&=~((1<<RST)|(1<<OEn));//ensures reset is low and enable output
	
	sei();
}

void read_encoder_input(){
	/*Read on MJ2*/
}

void send_motor_speed(){
	/*Send to MJ1 on motor box*/
	PINH|=(1<<EN); // enable MJ1
	
	
	/*read joystick position-> send to motor*/
	CAN_struct rcv_msg_joy= rcv_CAN_message();
	printf("Position %x \n", rcv_msg_joy.data[0]);
	/*Message for TWI format*/
	int8_t messageBuf[4];

	
	/*Send via TWI*/
	/*MAX520 DAC address is 00. Setting Read byte to 0. */
	messageBuf[0]=TWI_DAC_SLAVE_ADDR + 0;		//DAC address + readBit
	messageBuf[1] = 0x00;             // The first byte is used for commands.
	/*Need to set direction for the motor. Set DIR on MJ1 DIR->PH1*/
	if (rcv_msg_joy.data[0]<0){
		PINH|=(1<< DIR);
	}
	else{
		PINH&=~(1<<DIR);
	}
	messageBuf[2] =   rcv_msg_joy.data[0];                        // The second byte is used for the data.
	
	TWI_Start_Transceiver_With_Data(messageBuf,3);
	
}







