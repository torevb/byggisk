#include "CAN_driver.h"
#include "MCP2515_driver.h"
#include "CAN MCP2515 header files\MCP2515.h"

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>

#define RX0IF 0



void CAN_init(){
	MCP2515_init();
	
	//write_MCP2515(MCP_CANCTRL, (1<<7));
	
	bit_modify_MCP2515(MCP_RXB0CTRL, 0b01100000, 0xff);//set filters off
	bit_modify_MCP2515( MCP_RXB0CTRL, 0b00000100, 0x00);//set rollover off

	//bit_modify_MCP2515(MCP_CANINTE, 0x05, 0b00000001);//Set RX0 full enable interrupt
	bit_modify_MCP2515(MCP_CANINTE, 0x05, 0b00000101);//Set RX0 full and TX0 empty enable interrupt
	
	//bit_modify_MCP2515(MCP_CANINTF, (1<<RX0IF), 0x00);
	
	//bit_modify_MCP2515(MCP_CANCTRL,0xE0,MODE_LOOPBACK);//Enables loop back mode
	bit_modify_MCP2515(MCP_CANCTRL,0xE0,MODE_NORMAL);//Enables normal mode
}

void send_CAN_message(struct CAN_struct msg){
	printf("MCP_TXB0CTRL: %x\n", read_MCP2515(MCP_TXB0CTRL));
	while (read_MCP2515(MCP_TXB0CTRL) & (1<<TXREQ)){//will be cleared when finished
		//wait until finished transmitting
	}
	//MCP_TXB0CTRL &= ~(1<<TXREQ);
	//bit_modify_MCP2515(MCP_TXB0CTRL,TXREQ,4);//Choosing to write to buffer 0
	//bit_modify_MCP2515(MCP_TXB0CTRL,(1<<TXREQ),(1<<TXREQ));//Choosing to write to buffer 0
	
	//write_MCP2515(MCP_TXB0CTRL,);
	
	//load SIDL
	write_MCP2515(MCP_TXB0_SIDL, msg.ID << 5);
	
	//load SIDH
	write_MCP2515(MCP_TXB0_SIDH, msg.ID >> 3);

	
	//load DLC
	//bit_modify_MCP2515(MCP_TXB0_DLC, 0x0F,(char)msg.length);//setting datalength
	
	write_MCP2515(MCP_TXB0_DLC,(char)msg.length);
	//printf("MCP_TXB0_DLC: %x\n", read_MCP2515(MCP_TXB0_DLC));
	//printf(" : %c\n",l);
	
	//if data--> TXBnDm load
	//write_MCP2515(MCP_TXB0_D0,(char)msg.data);
	
	/*PUTTING DATA IN DATABUFFER*/
	for (int i=0; i < msg.length; i++){
		//printf(" I: %i\n",i);
		write_MCP2515(MCP_TXB0_D0+i,(char)msg.data[i]);
		//printf("MCP_TXB0_D0: %x\n", read_MCP2515(MCP_TXB0_D0+i));
		
	}
	//printf("MCP_TXB0_SIDL: %x\n", read_MCP2515(MCP_TXB0_SIDL));
	//printf("MCP_TXB0_SIDH: %x\n", read_MCP2515(MCP_TXB0_SIDH));

	
	//printf("reg: %x\n", read_MCP2515(MCP_TXB0_SIDH));
	printf("MCP_TXB0CTRL: %x\n", read_MCP2515(MCP_TXB0CTRL));
	/*REQUEST TO SEND*/
	request_to_send_MCP2515(0x01);// Setting the TXBnCTRL for buffer 0.
	printf("MCP_TXB0CTRL: %x\n", read_MCP2515(MCP_TXB0CTRL));
	printf("Requesting to send!\n");
	printf("CANINTF: %x\n", read_MCP2515(MCP_CANINTF));
	/*CHECK IF TRANSMIT SUCCEEDS*/

	/*ABORT TRANSMISSION?*/
	
}


CAN_struct rcv_CAN_message(){

	CAN_struct msg;
	
	//memset(&msg,0,sizeof(CAN_struct));
	printf("CANTSTAT: %x\n", read_MCP2515(MCP_CANINTF));
	
	while (!(read_MCP2515(MCP_CANINTF) & (1<<RX0IF))) {} //wait for interrupt
	msg.ID=((read_MCP2515(MCP_RXB0SIDH))<<3|((read_MCP2515(MCP_RXB0SIDL))>>5));
	msg.length=	(int)(read_MCP2515(MCP_RXB0_DLC) & 0x0f);
	printf(" Message length %i:\n",msg.length);
	
	
	/*READING DATA FROM DATABUFFER*/
	for (int i=0; i < msg.length; i++){
		msg.data[i]= read_MCP2515(MCP_RXB0_D0+i);
		
	}
	//MUST clear RXB0IF after reading message
	bit_modify_MCP2515(MCP_CANINTF, (1<<RX0IF),0x00);
	
	/*else {
		msg.ID = 0;
	}*/
	
	return msg;
}
