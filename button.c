/*
 * button.c
 *
 * Created: 2019-07-12 오전 10:21:48
 *  Author: bth8188
 */ 

#include "button.h"

static uint8_t button_state[] = {0, 0, 0, 0, 0, 0, 0};

void Button_Init()
{
	BUTTON_DDR &= ~(0x0e);
}

int button(uint8_t _num)
{
		
	if( ((BUTTON_PIN & (1<<_num)) == 0) && (button_state[_num] == 0) )
	{
		button_state[_num] = 1;
		return 0;
	}
	else if( ((BUTTON_PIN & (1 << _num)) == (1 << _num)) && (button_state[_num] == 1) )
	{
		button_state[_num] = 0;
		return 1;
	}
	return 0;
}
