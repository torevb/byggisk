#pragma once
#include <stdint.h>
#define TXREQ 3
#define EXIDE 3

/*CAN IDs*/
#define	NODE1_ID			11
#define NODE2_ID			22
#define RCV_ID				3

typedef struct CAN_struct CAN_struct;
struct CAN_struct{
	char ID;
	uint8_t length;
	int8_t * data[8];
};

void CAN_init();
void send_CAN_message(CAN_struct * msg);
void rcv_CAN_message(CAN_struct * msg);











