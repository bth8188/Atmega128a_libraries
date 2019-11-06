/*
 * dcmotor.c
 *
 * Created: 2019-07-05 오후 5:23:52
 *  Author: bth8188
 */ 
#include "dcmotor.h"


void DCmotorInit()
{
	DDRE = 0xff;
	TCCR3B |= _BV(CS30) | _BV(WGM32);
	TCCR3A |= _BV(WGM30);
	TCCR3A |= _BV(COM3A1) | _BV(COM3B1);
}

void DCmotorstop()
{
	MOTOR_R = 0;
	MOTOR_L = 0;
}

void DCmotorleft(uint8_t leftspeed)
{
	MOTOR_R = 0;if(leftspeed > 255) leftspeed = 255;
	else if(leftspeed < 0) leftspeed =0;
	MOTOR_L = leftspeed;
}

void DCmotorright(uint8_t rightspeed)
{
	if(rightspeed > 255) rightspeed = 255;
	else if(rightspeed < 0) rightspeed =0;
	MOTOR_R = rightspeed;
	MOTOR_L = 0;
}
