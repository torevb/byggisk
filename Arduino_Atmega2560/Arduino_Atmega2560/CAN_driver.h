#pragma once
#include <stdint.h>
#define TXREQ 3
#define EXIDE 3

typedef struct CAN_struct CAN_struct;
struct CAN_struct{
	char ID;
	uint8_t length;
	int8_t * data[8];
};

void CAN_init();
void send_CAN_message(struct CAN_struct msg);
CAN_struct rcv_CAN_message();











