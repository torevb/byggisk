#include "CAN_driver.h"
#include "MCP2515_driver.h"
#include "CAN MCP2515 header files\MCP2515.h"

#define TXREQ 3


struct CAN_struct{
	char ID;
	char length;
	char data;
};

void CAN_init(){
	MCP2515_init();
	CANCTRL |= (1<<6); //enables loop back mode
	CANCTRL &= !((1<<7) | (1<<5));//enables loop back mode
}

void send_CAN_message(struct CAN_struct input){
	//request to send?
	write_MCP2515(input.ID, input.data);
	request_to_send_MCP2515(input.ID);// Setting the TXBnCTRL. TXREQ for the buffer corresponding to the ID.    	//TXBnCTRL |= (1<<TXREQ) // Transmit request. For initiating of transmission
	TXRTSCTRL &= !(1<<input.ID);
	

	/*CHECK IF TRANSMIT SUCCEEDS*/
	while (MCP_TXB0CTRL & (1<<TXREQ)){
		//wait until finished transmitting
	}
	
	
	/*Abort transmission??*/
	
}


void recv_CAN_message(struct CAN_struct * output){
	/*output.ID = ;
	output.length = ;
	output.data = ;*/
}
