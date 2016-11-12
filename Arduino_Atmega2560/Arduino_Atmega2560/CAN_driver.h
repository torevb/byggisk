#pragma once
#include <stdint.h>
#define TXREQ 3
#define EXIDE 3

/*CAN IDs*/
#define JOYSTICK_ID			0
#define SOLENOIDE_PUSH_ID	1
#define SLIDER_ID			2

typedef struct CAN_struct CAN_struct;
struct CAN_struct{
	char ID;
	uint8_t length;
	int8_t * data[8];
};

void CAN_init();
void send_CAN_message(struct CAN_struct msg);
CAN_struct rcv_CAN_message();











