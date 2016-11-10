#pragma once

#include <stdint.h>




void motor_init();

int16_t read_encoder_input();

/* Send data to the motor through the DAC and Motor Box Controller. */
void send_motor_speed();

void set_motor_speed(int16_t input_speed);

void calibrate_encoder();