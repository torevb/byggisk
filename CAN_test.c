#include "CAN_driver.h"
#include "SPI_driver.h"
#include "MCP2515_driver.h"
#include <stdio.h>
void CAN_test(){
	CAN_init();
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
	//bit_modify_MCP2515(MCP_CANCTRL,0xE0,MODE_LOOPBACK);//Enables loop back mode
		
	send_CAN_message(msg);
	//printf("HER \n");
	CAN_struct rcv_msg= rcv_CAN_message();
	//printf("HER \n");
	for (int j=0;j<msg.length;j++){
		printf("Data in received message : %c \n", rcv_msg.data[j]);
	}
}

void CAN_test_communication(){
	CAN_init();
	

	while (1){
		CAN_struct rcv_msg= rcv_CAN_message();
		//printf("HER \n");
		for (int j=0;j<msg.length;j++){
			printf("Data in received message : %c \n", rcv_msg.data[j]);
		}
	}
}
