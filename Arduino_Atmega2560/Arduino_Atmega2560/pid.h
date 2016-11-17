#pragma once
#include <stdint.h>


void set_encoder_max(int value);
uint8_t speed_regulator(int8_t input_joy, float  t);