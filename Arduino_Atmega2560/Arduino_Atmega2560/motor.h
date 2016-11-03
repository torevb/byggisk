#pragma once




void motor_init();

void read_encoder_input();

/* Send data to the motor through the DAC and Motor Box Controller. */
void send_motor_speed();