#include "CAN_driver.h"
#include <stdio.h>
void CAN_test(){
	CAN_struct msg;
	msg.ID=3;
	msg.length=4;
	msg.data[0]='a';
	msg.data[1]='b';
	msg.data[2]='c';
	msg.data[3]='d';
		
	send_CAN_message(msg);
	CAN_struct rcv_msg= rcv_CAN_message();
	for (int j=0;j<msg.length;j++){
		printf("Data in received message : %c \n", rcv_msg.data[j]);
	}
}