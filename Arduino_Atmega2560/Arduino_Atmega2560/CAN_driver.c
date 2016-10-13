#include "CAN_driver.h"
#include "MCP2515_driver.h"
#include "MCP2515.h"

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>



void CAN_init(){
	MCP2515_init();
	bit_modify_MCP2515(MCP_CANCTRL,0xE0,MODE_NORMAL);//Enables normal mode
	bit_modify_MCP2515(0x60, 0b01100000, 0xff);//set filters off
	bit_modify_MCP2515( 0x60, 0b00000100, 0x00);//sett rollover off

	bit_modify_MCP2515(0x2b, 0b00000001, 0xff);//Set RX0 full enable
	
}

void send_CAN_message(struct CAN_struct msg){

	//MCP_TXB0CTRL &= ~(1<<TXREQ);
	bit_modify_MCP2515(MCP_TXB0CTRL,TXREQ,4);//Choosing to write to buffer 0
	
	//load SIDL
	write_MCP2515(MCP_TXB0_SIDL, msg.ID << 5);
	
	//load SIDH
	write_MCP2515(MCP_TXB0_SIDH, msg.ID >> 3);

	
	//load DLC
	//bit_modify_MCP2515(MCP_TXB0_DLC, 0x0F,(char)msg.length);//setting datalength
	
	write_MCP2515(MCP_TXB0_DLC,(char)msg.length);
	//printf(" : %c\n",l);
	
	//if data--> TXBnDm load
	write_MCP2515(MCP_TXB0_D0,(char)msg.data);
	
	/*PUTTING DATA IN DATABUFFER*/
	for (int i=0; i < msg.length; i++){
		//printf(" I: %i\n",i);
		write_MCP2515(MCP_TXB0_D0+i,(char)msg.data[i]);
		
	}
	
	/*REQUEST TO SEND*/
	request_to_send_MCP2515(0x01);// Setting the TXBnCTRL for buffer 0.
	
	/*CHECK IF TRANSMIT SUCCEEDS*/
	while (read_MCP2515(MCP_TXB0CTRL) & TXREQ){//will be cleared when finished
		//wait until finished transmitting
	}
	
	
	/*ABORT TRANSMISSION?*/
	
}


CAN_struct rcv_CAN_message(){

	CAN_struct msg;
	
	memset(&msg,0,sizeof(CAN_struct));
	
	msg.ID=((read_MCP2515(MCP_RXB0SIDH))<<3|((read_MCP2515(MCP_RXB0SIDL))>>5));
	msg.length=	(int)(read_MCP2515(MCP_RXB0_DLC) & 0x0f);
	printf(" Message length %i:\n",msg.length);
	
	
	/*READING DATA FROM DATABUFFER*/
	for (int i=0; i < msg.length; i++){
		msg.data[i]= read_MCP2515(MCP_RXB0_D0+i);
		
	}
	
	//MUST clear RXB0IF after reading message
	bit_modify_MCP2515(MCP_CANINTF, 0,0x00);
	
	return msg;
}
