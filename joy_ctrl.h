/*
 * joy_ctrl.h
 *
 * Created: 15.09.2016 14:53:09
 *  Author: marthauk
 */ 


#ifndef JOY_CTRL_H_
#define JOY_CTRL_H_
typedef enum 
{   LEFT=0,
	RIGHT=1,
	UP=2,
	DOWN=3,
	NEUTRAL=4,
}joy_direction;
typedef enum{
	JOY_Y=4,
	JOY_X=5,
	SLIDE_L=6,
	SLIDE_R=7,
}ADC_channel;


uint8_t read_bus(void);

uint8_t get_joy_position(ADC_channel adc_ch);

int get_joy_direction(void);

int8_t calculate_percentage(int8_t position);

void print_position(int8_t percentage_x, int8_t percentage_y);




#endif /* JOY_CTRL_H_ */