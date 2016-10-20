#include "CAN_driver.h"
#include "SPI_driver.h"
#include "MCP2515_driver.h"
#include <stdio.h>
#include <util/delay.h>
void CAN_test(){
	
	CAN_init();
	/*
	CAN_struct msg;
	msg.ID=3;
	msg.length=8;
	msg.data[0]='K';
	msg.data[1]='A';
	msg.data[2]='R';
	msg.data[3]='L';
	msg.data[4]='S';
	msg.data[5]='T';
	msg.data[6]='A';
	msg.data[7]='D';
	*/
	//bit_modify_MCP2515(MCP_CANCTRL,0xE0,MODE_LOOPBACK);//Enables loop back mode
	
	while (1){
		//send_CAN_message(msg);
	
		_delay_ms(2000);
		CAN_struct rcv_msg= rcv_CAN_message();
		
		for (int j=0;j<rcv_msg.length;j++){
			printf("Data in received message : %c \n", (char) rcv_msg.data[j]);
		}
	}
}