#pragma once
#include <stdint.h>
#define TXREQ 3
#define EXIDE 3

/*CAN IDs*/
#define	HIGHSCORE_ID		0
#define JOYSTICK_ID			1
#define SOLENOIDE_PUSH_ID	2
#define SLIDER_ID			3

typedef struct CAN_struct CAN_struct;
struct CAN_struct{
	char ID;
	uint8_t length;
	int8_t * data[8];
};

void CAN_init();
void send_CAN_message(struct CAN_struct msg);
void rcv_CAN_message(CAN_struct * msg);











