
#pragma once

typedef enum 
{   NEUTRAL=0,
	LEFT=1,
	RIGHT=2,
	UP=3,
	DOWN=4,
}joy_direction;

typedef enum{
	JOY_X=4,
	JOY_Y=5,
	SLIDE_L=6,
	SLIDE_R=7,
}ADC_channel;

struct {
	int x_pos;
	int y_pos;
} rel_position;

uint8_t get_joy_position(ADC_channel adc_ch);

int get_joy_direction();

void joy_relative_pos(void);

void joy_init(void);


