#include "CAN_driver.h"
#include "SPI_driver.h"
#include "MCP2515_driver.h"
#include "CAN MCP2515 header files/MCP2515.h"
#include <stdio.h>
#include <util/delay.h> //for _delay_ms()

#define RX0IF 0


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
	
	while(1){
		send_CAN_message(msg);
	}
	
	
	//CAN_struct rcv_msg= rcv_CAN_message();
	
	//for (int j=0;j<rcv_msg.length;j++){
	//	printf("Data in received message : %c \n", (char) rcv_msg.data[j]);
	//}
}

void CAN_test_communication(){
	CAN_init();
	
	while (1){
		CAN_struct rcv_msg= rcv_CAN_message();
		printf("ID: %i, length: %i\n", rcv_msg.ID, rcv_msg.length);
		for (int j=0;j<8;j++){//rcv_msg.length;j++){
			printf("Data in received message : %c at line %i\n", (char) rcv_msg.data[j], j);
		}
		_delay_ms(1000);
	}
}

