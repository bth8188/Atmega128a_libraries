/*
 * HallSensor.c
 *
 * Created: 2019-08-27 오후 3:09:24
 *  Author: kccistc
 */ 
#include "HallSensor.h"

uint8_t a = 0, b = 0;
uint8_t ready_Flag = 0, left_Flag = 0;
uint32_t rot = 0;

void HallSensor_Init()
{
	HallSensor_Port |= (1 << HallSensor_Apin) | (1 << HallSensor_Bpin);
	EIMSK |= (1 << INT6) | (1 << INT7);
	EICRB |= (1 << ISC61) |(1 << ISC60) | (1 << ISC71) | (1 << ISC70);
}

void ISR_Toggle_A()
{
	a ^= 1;
	if(a)
	{
		EICRB &= ~(0 << ISC60);
		b? rot++: (left_Flag = 1);
	}
	else EICRB |= (1 << ISC60);
}

void ISR_Toggle_B()
{
	b ^= 1;
	if(b)
	{
		EICRB &= ~(0 << ISC70);
		a? rot++ : (left_Flag = 0);
	}
	else EICRB |= (1 << ISC70);
}

uint32_t get_rotation()
{
	return rot;
}

void set_rotation(uint32_t _num)
{
	rot = _num;
}

uint8_t get_direction()
{
	return left_Flag;
}