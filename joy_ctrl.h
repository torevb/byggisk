/*
 * joy_ctrl.h
 *
 * Created: 15.09.2016 14:53:09
 *  Author: marthauk
 */ 

#pragma once

typedef enum 
{   NEUTRAL=0,
	LEFT=1,
	RIGHT=2,
	UP=3,
	DOWN=4,
}joy_direction;

/* Mayhaps we might need to swap x and y. */
typedef enum{
	JOY_Y=4,
	JOY_X=5,
	SLIDE_L=6,
	SLIDE_R=7,
}ADC_channel;

struct {
	int x_pos;
	int y_pos;
} rel_position;

uint8_t get_joy_position(ADC_channel adc_ch);

int get_joy_direction();

int8_t calculate_percentage(int8_t position);

void print_position(void);

void joy_relative_pos(void);

void joy_init(void);

void print_direction(void);
