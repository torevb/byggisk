#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "CAN_driver.h"
#include "TWI_Master.h"
#include <avr/interrupt.h>
#include "uart.h"
#define F_CPU 16000000UL  //for <util/delay.h>
#include <util/delay.h> //for _delay_ms()



#define DIR PH1
#define SEL PH3
#define EN PH4
#define OEn PH5
#define RSTn PH6
#define SCL PD0
#define SDA PD1


#define TWI_DAC_SLAVE_ADDR 0b01010000

/*motor baud rate is 115200*/

void motor_init(){
	TWI_Master_Initialise();
	CAN_init();
	DDRD |= (1<<SCL) | (1<<SDA);	//Set SCL and SDA as output. 
	DDRK =0x00; //set A as input. Used to read encoder data
	TWBR = 12;// Set SCK on TWI to 400kbps
	
	DDRH= 0xFF; //setting all PINH to output.
	PORTH|=(1<<EN)|(1<<DIR)|(1<<RSTn);
	sei();
}

int16_t read_encoder_input(){
	/*Read on MJ2*/
	
	PORTH&=~((1<<OEn)|(1<<SEL)); //Output enable to low to enable output of encode, set SEL low to get high byte
	_delay_ms(20); //delay about 20 ms
	int16_t motor_encoder_data= ((PINK&0xFF) <<8); // read MSB
	PORTH|=(1<<SEL);
	_delay_ms(20); //delay about 20 ms
	
	//printf("Motor encoder data : %i\n",motor_encoder_data);
	motor_encoder_data|= (PINK&0xFF); // read MSB
	
	PORTH&=~(1<<RSTn);//Toggle reset to start counting again
	_delay_ms(5); //delay about 20 ms
	PORTH|=(1<<RSTn)|(1<<OEn);//disable output from encoder

	if (motor_encoder_data != 0) {printf("Motor encoder data : %i\n", motor_encoder_data);}
		
	return motor_encoder_data;	
}

//int joy_samples[5] = {0,0,0,0,0};

void send_motor_speed(CAN_struct rcv_msg_joy){
	/*Send to MJ1 on motor box*/
	//PINH|=(1<<EN); // enable MJ1
	
	//int joy_average = 0;
	
	/*read joystick position-> send to motor*/
	//CAN_struct rcv_msg_joy = rcv_CAN_message();
	
	//joy_samples[0] = rcv_msg_joy.data[0];
	
	/*
	for(int i=0; i<5; i++){
		joy_average += joy_samples[i];
	}
	joy_average = joy_average / 5;
	*/
	/*for (int i = 0; i<5; i++){
		rcv_msg_joy= rcv_CAN_message();
		joy_average += rcv_msg_joy.data[0];
	}
	*/
	
	
	//if(rcv_msg_joy.ID==SLIDER_ID){/*SLIDER_data from 0-255*/
		/*Message for TWI format*/
		int8_t messageBuf[4];

		int16_t motor_strength=rcv_msg_joy.data[0];
		
		//printf("Motor strength %i,\n",motor_strength);
		//printf("Position %i \n", rcv_msg_joy.data[0]);
		/*Send via TWI*/
		/*MAX520 DAC address is 00. Setting Read byte to 0. */
		messageBuf[0]=TWI_DAC_SLAVE_ADDR + 0;		//DAC address + readBit
		messageBuf[1] = 0x00;             // The first byte is used for commands.
		/*Need to set direction for the motor. Set DIR on MJ1 DIR->PH1*/
	
		PORTH|=(1<< DIR);
		if (motor_strength<130){ /*Get drops down to 0 in DIR anyways*/
			motor_strength=motor_strength; 
		}
		else{
		
			PORTH&=~(1<<DIR);
			motor_strength= abs(motor_strength-255);// to scale 
		}
		messageBuf[2] =motor_strength;                         // The second byte is used for the data.
		//printf("Motor strength %i,\n",motor_strength);
		TWI_Start_Transceiver_With_Data(messageBuf,3);
	
	//}
}

void set_motor_speed(int16_t input_speed){
	/*Message for TWI format*/
	int8_t messageBuf[4];

	int16_t motor_strength=input_speed;
	//printf("Motor strength %i,\n",motor_strength);
	//printf("Position %i \n", rcv_msg_joy.data[0]);
	/*Send via TWI*/
	/*MAX520 DAC address is 00. Setting Read byte to 0. */
	messageBuf[0]=TWI_DAC_SLAVE_ADDR + 0;		//DAC address + readBit
	messageBuf[1] = 0x00;             // The first byte is used for commands.
	/*Need to set direction for the motor. Set DIR on MJ1 DIR->PH1*/
	
	PORTH|=(1<< DIR);
	if (motor_strength<130){ /*Get drops down to 0 in DIR anyways*/
		motor_strength=motor_strength*2;
	}
	else{
		
		PORTH&=~(1<<DIR);
		motor_strength= abs(motor_strength-255)*2;// to scale
	}
	messageBuf[2] =motor_strength;                         // The second byte is used for the data.
	//printf("Motor strength %i,\n",motor_strength);
	TWI_Start_Transceiver_With_Data(messageBuf,3);
}

#define ENCODER_TIME	1000
#define ENCODER_SPEED	40

int16_t encoder_length = 0;


void calibrate_encoder(){
	
	
	
	set_motor_speed(255-ENCODER_SPEED);
	while (read_encoder_input() != 0){
		set_motor_speed(ENCODER_SPEED);
	}
	printf("turn\n");
	int time = 0;
	while (time < ENCODER_TIME){
		set_motor_speed(255-ENCODER_SPEED);
		time++;
		_delay_ms(5);
	}
	//_delay_ms(ENCODER_TIME);
	
	encoder_length = read_encoder_input();
	
	printf("encoder_length; %i\n", encoder_length);
	
	int16_t temp = encoder_length;
	
	while (temp > encoder_length / 2){
		set_motor_speed(30);
		temp = temp + read_encoder_input();
	}
}





