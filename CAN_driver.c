#include "CAN_driver.h"
#include "MCP2515_driver.h"
#include "CAN MCP2515 header files\MCP2515.h"

#define TXREQ 3
#define EXIDE 3

struct CAN_struct{
	char ID;
	uint8_t length;
	uint8_t * data[8];
};

void CAN_init(){
	MCP2515_init();
	bit_modify_MCP2515(MCP_CANCTRL,0xE0,MODE_LOOPBACK);//Enables loop back mode
}

void send_CAN_message(struct CAN_struct msg){
	
	//MCP_TXB0CTRL &= ~(1<<TXREQ);
	bit_modify_MCP2515(MCP_TXB0CTRL,TXREQ,4);//Choosing to write to buffer 0
	
	//load SIDL
	bit_modify_MCP2515(MCP_TXB0_SIDL,0xFF, msg.ID<<5);// Setting identifiers corresponding to msg.ID
	//load SIDH
	bit_modify_MCP2515(MCP_TXB0_SIDL,0xFF, msg.ID>>3);// Setting identifiers corresponding to msg.ID
	//load DLC
	bit_modify_MCP2515(MCP_TXB0_DLC, 0x0F,msg.length);//setting datalength
	//if data--> TXBnDm load
	bit_modify_MCP2515(MCP_TXB0_D0,0xFF,msg.data);//setting up databuffer
	
	/*PUTTING DATA IN DATABUFFER*/
	for (int i=0; i < msg.length; i++){
		write_MCP2515(MCP_TXB0_D0+i, msg.data[i]);
	}
	/*REQUEST TO SEND*/
	request_to_send_MCP2515(0x00);// Setting the TXBnCTRL for buffer 0.//TXBnCTRL |= (1<<TXREQ) //
	
	/*CHECK IF TRANSMIT SUCCEEDS*/
	while (read_MCP2515(MCP_TXB0CTRL) & TXREQ){//will be cleared when finished
		//wait until finished transmitting
	}
	
	
	/*ABORT TRANSMISSION?*/
	
}


CAN_struct recv_CAN_message(){
	CAN_struct msg;
	
	msg.ID=((read_MCP2515(MCP_RXB0SIDH))<<3|((read_MCP2515(MCP_RXB0SIDL))>>5));
	msg.length=	read_MCP2515(MCP_RXB0_DLC);
	msg.data
	
	/*PUTTING DATA IN DATABUFFER*/
	for (int i=0; i < msg.length; i++){
		msg.data[i]= read_MCP2515(MCP_RXB0_D0+i);
	}
	
	
	
	//MUST clear RXB0IF after reading message
}
