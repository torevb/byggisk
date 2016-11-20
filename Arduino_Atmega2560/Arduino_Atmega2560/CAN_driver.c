#include "CAN_driver.h"
#include "MCP2515_driver.h"
#include "MCP2515.h"


#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>

#define RX0IF 0



void CAN_init(){
	MCP2515_init();
	
	bit_modify_MCP2515(MCP_RXB0CTRL, 0b01100000, 0xff);//set filters off
	bit_modify_MCP2515( MCP_RXB0CTRL, 0b00000100, 0x00);//sett rollover off
	
	bit_modify_MCP2515(MCP_CANINTE, 0b00000101, 0b00000001);//Set RX0 full enable
	
	//bit_modify_MCP2515(MCP_CANCTRL,0xE0,MODE_LOOPBACK);//Enables loop back mode
	bit_modify_MCP2515(MCP_CANCTRL,0xF0,MODE_NORMAL);//Enables normal mode
}

void send_CAN_message(CAN_struct *msg){
	while (read_MCP2515(MCP_TXB0CTRL) & (1<<TXREQ)){// & TXREQ){ //will be cleared when finished
		//wait until finished transmitting
	}

	//load SIDL
	write_MCP2515(MCP_TXB0_SIDL, (*msg).ID << 5);
	
	//load SIDH
	write_MCP2515(MCP_TXB0_SIDH, (*msg).ID >> 3);

	write_MCP2515(MCP_TXB0_DLC,(char)(*msg).length);

	/*PUTTING DATA IN DATABUFFER*/
	for (int i=0; i < (*msg).length; i++){
		write_MCP2515(MCP_TXB0_D0+i,(char)(*msg).data[i]);
	}

	/*REQUEST TO SEND*/
	request_to_send_MCP2515(0x01);// Setting the TXBnCTRL for buffer 0.
}


void rcv_CAN_message(CAN_struct * msg){
	
	msg->data[0] = 0;
	msg->ID = 0;
	msg->length = 0;

	//memset(&msg, 0, sizeof(CAN_struct));
	while (!(read_MCP2515(MCP_CANINTF) & (1<<RX0IF))) {} //wait for interrupt
	
	msg->ID=((read_MCP2515(MCP_RXB0SIDH))<<3|((read_MCP2515(MCP_RXB0SIDL))>>5));
	msg->length=	(int)(read_MCP2515(MCP_RXB0_DLC) & 0x0f);
	
	
	/*READING DATA FROM DATABUFFER*/
	for (int i=0; i < msg->length; i++){
		msg->data[i]= read_MCP2515(MCP_RXB0_D0+i);
	}
	
	//MUST clear RXB0IF after reading message
	bit_modify_MCP2515(MCP_CANINTF, (1<<RX0IF), 0x00);

	//printf("Message ID,data and length in receive-function %u , %d, %u \n", msg->ID,msg->data[0],msg->length);
		
	//return msg;

}
