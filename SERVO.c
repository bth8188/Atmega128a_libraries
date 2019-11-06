/*
 * SERVO.c
 *
 * Created: 2019-07-10 오후 3:04:42
 *  Author: kccistc
 */ 

#include "SERVO.h"

void servoInit()
{
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12) | (1 << WGM13) ;
	
	TCCR1A |= (1 << COM1A1); 
	TCCR1B |= (1 << CS11) | (1 << CS10);
	
	ICR1 = 5000-1;
}

void servo_run(uint8_t degree)
{
	OCR1A = (degree / 180.0) * 500 + 124;
}