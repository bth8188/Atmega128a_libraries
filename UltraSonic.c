/*
 * UltraSonic.c
 *
 * Created: 2019-07-03 오후 5:04:10
 *  Author: bth8188
 */ 
#include "UltraSonic.h"

enum {stop, run} ult_sonic;
volatile uint16_t distime = 0;

void ultInit()
{
	DDRD |= (1<<PORTD0);
	DDRD &= ~(1<<PIND1);
	EICRA |= _BV(ISC10) | _BV(ISC11);
	EIMSK |= _BV(INT1);
}

uint8_t measure_distance()
{
	PORTD &= ~(1 << PORTD0);
	_delay_ms(1);
	PORTD |= (1 << PORTD0);
	_delay_ms(10);
	PORTD &= ~(1 << PORTD0);
}

void UltraSonic_Recieve()
{	
	EICRA ^= _BV(ISC10);
	if(ult_sonic == run)
	{
		distime = TCNT1;
	}
	TCNT1 = 0;
	ult_sonic ^= 1;
}

uint16_t dist()
{
	uint16_t k = distime * 0.068;
	
	return k;
}
