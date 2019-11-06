/*
 * time.c
 *
 * Created: 2019-07-02 오전 10:27:47
 *  Author: bth8188
 */ 

#include "time.h"

static uint32_t milliSec2 = 0;
static uint32_t milliSec = 0;
static uint8_t sec=0, min=0, hour=0;
static uint8_t mm3=0, sec2=0, min2=0, hour2=0;
static uint8_t _time[20] = {0,0,0,0,0};


void timer0init()
{
	//분주비 64
	TCCR0 |= _BV(CS02);
	//CTC mode 사용
	TCCR0 |= _BV(WGM01);
	//ouput compare interrupt enable
	TIMSK |= _BV(OCIE0);
	OCR0 = 250;
	// tcnt set 250
}

void incMilliSec()
{
	milliSec ++;
}

uint32_t millis()
{
	return milliSec;
}

void incTime()
{
	if((milliSec%1000) == 0)
	{
		sec++;
		if(sec >= 60)
		{
			sec = 0;
			min ++;
			if(min>=60)
			{
				min = 0;
				hour ++;
				if(hour>=24)
				{
					hour =0;
				}
			}
		}
	}
}

void hh(char *curtime)
{
	sprintf(curtime,"%02d",hour);
}

void mm(char *curtime)
{
	sprintf(curtime,"%02d",min);
}

void ss(char *curtime)
{
	sprintf(curtime,"%02d",sec);
}

void incStop()
{
	milliSec2 ++;
}

uint32_t stpmills()
{
	return milliSec2;
}

void incstp()
{
	if((milliSec2%10) == 0)
	{
		mm3++;
		if(mm3 >= 100)
		{
			mm3 = 0;
			sec2 ++;
			if(sec2 >= 60)
			{
				sec2 = 0;
				min2 ++;
				if(min2>=60)
				{
					min2 = 0;
					hour2 ++;
					if(hour2>=24)
					{
						hour2 =0;
					}
				}
			}
		}
	}
}

void rst()
{
	hour2 = min2 = sec2 = mm3 = 0;
}

void hh2(char *curtime)
{
	sprintf(curtime,"%02d",hour2);
}

void mm2(char *curtime)
{
	sprintf(curtime,"%02d",min2);
}

void ss2(char *curtime)
{
	sprintf(curtime,"%02d",sec2);
}

void mimi(char *curtime)
{
	sprintf(curtime,"%02d", mm3);
}

int fortime()
{
	uint16_t forr=0;
	if(milliSec%10==0)
	{
		forr++;
		if(forr>=10)
		{
			forr = 0;
			return 1;
		}
	}
	return 0;
}

void timer1Init()
{
	TCCR1B |= _BV(CS10) | _BV(CS11);
}

uint8_t* Cur_Time()
{
	sprintf(_time, "%s", "Time>>00:00:00");
	return _time;
}
