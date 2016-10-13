#include "CAN_driver.h"
#include "SPI_driver.h"
#include "MCP2515_driver.h"
#include <stdio.h>
void CAN_test(){
	CAN_init();
	CAN_struct msg;
	msg.ID=3;
	msg.length=6;
	msg.data[0]='T';
	msg.data[1]='O';
	msg.data[2]='R';
	msg.data[3]='E';
	msg.data[4]='#';
	msg.data[5]='1';
		
	send_CAN_message(msg);
	//printf("HER \n");
	CAN_struct rcv_msg= rcv_CAN_message();
	//printf("HER \n");
	for (int j=0;j<msg.length;j++){
		printf("Data in received message : %c \n", rcv_msg.data[j]);
	}
}