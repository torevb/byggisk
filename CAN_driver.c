#include "CAN_driver.h"
#include "MCP2515_driver.h"


struct CAN_struct{
	char ID;
	char length;
	char data;
};

void CAN_init(){
	MCP2515_init();
	//set something loopback mode. 
	///CANCTRL |= (1<<6);
	//CANCTRL &= !((1<<7) | (1<<5));
}

void send_CAN_message(struct CAN_struct input){
	//request to send?
	write_MCP2515(input.ID, input.data);
}


void recv_CAN_message(struct CAN_struct * output){
	/*output.ID = ;
	output.length = ;
	output.data = ;*/
}
