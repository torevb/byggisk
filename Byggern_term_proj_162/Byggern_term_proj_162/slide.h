#pragma once



#include "SRAM_test.h"
#include "joy_ctrl.h"
#include <avr/io.h>
#include <util/delay.h> //for _delay_ms()



void slider_init(void);
int8_t get_slider_pos(ADC_channel adc_ch);
int slider_right_button(void);
int slider_left_button(void);



