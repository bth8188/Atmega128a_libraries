/*
 * buzzer.c
 *
 * Created: 2019-07-02 오후 5:16:22
 *  Author: bth8188
 */ 
#include "buzzer.h"

static double scaleoct[12][8] =
{
	{32.7032, 65.4064, 130.8128, 261.6256, 523.2511, 1046.502, 2093.005, 4186.009},
	{34.6478, 69.2957, 138.5913, 277.1826, 554.3653, 1108.731, 2217.461, 4434.992},
	{36.7081, 73.4162, 146.8324, 293.6648, 587.3295, 1174.659, 2349.318, 4698.636},
	{38.8909, 77.7817, 155.5635, 311.1270, 622.2540, 1244.508, 2489.016, 4978.032},
	{41.2034, 82.4069, 164.8138, 329.6276, 659.2551, 1318.510, 2637.020, 5274.041},
	{43.6535, 87.3071, 174.6141, 349.2282, 698.4565, 1396.913, 2793.826, 5587.652},
	{46.2493, 92.4986, 184.9972, 369.9944, 739.9888, 1479.978, 2959.955, 5919.911},
	{48.9994, 97.9989, 195.9977, 391.9954, 783.9909, 1567.982, 3135.963, 6271.927},
	{51.9130, 103.8262, 207.65253, 415.3047, 830.6094, 1661.219, 3322.438, 6644.875},
	{55.0, 110.0, 220.0, 440.0, 880.0, 1760.0, 3520.0, 7040.0},
	{58.2705, 116.5409, 233.0819, 466.1638, 932.3275, 1864.655, 3729.310, 7458.620},
	{61.7354, 123.4708, 246.9417, 493.8833, 987.7666, 1975.533, 3951.066, 7902.133},
};
char scale[] = {'c', 'C', 'd', 'D', 'e', 'E', 'f', 'F', 'g', 'G', 'a', 'A', 'b', 'B'};
char notenote[4];

void buzzerInit()
{
	DDRE |= 1<<3;
	TCCR3B |= _BV(CS31);
	TCCR3B |= _BV(WGM32);
	TCCR3A |= _BV(COM3A0);
	OCR3A = 1000;
	nobuzzer();
}

void setbuzzer(int note)
{
	int ocr_value = 1000000 / note;
	OCR3A = ocr_value;
}

void nobuzzer()
{
	TCCR3A &= ~(_BV(COM3A0) | _BV(COM3A1));
}

void playbuzzer()
{
	TCCR3A |= _BV(COM3A0);
}

void pibibip()
{
	setbuzzer(300);
	playbuzzer();
	_delay_ms(10);
	setbuzzer(700);
	_delay_ms(10);
	setbuzzer(1500);
	_delay_ms(10);
	nobuzzer();
}

void pibibip2()
{
	setbuzzer(3000);
	playbuzzer();
	_delay_ms(10);
	setbuzzer(1500);
	_delay_ms(10);
	setbuzzer(300);
	_delay_ms(10);
	nobuzzer();
}

void start_sound()
{
	setbuzzer(3816);
	playbuzzer();
	_delay_ms(300);
	setbuzzer(3030);
	_delay_ms(300);
	setbuzzer(2551);
	_delay_ms(300);
	nobuzzer();
}

void measure_sound()
{
	setbuzzer(2551);
	playbuzzer();
	_delay_ms(150);
	setbuzzer(2865);
	_delay_ms(150);
	nobuzzer();
}


void ready_sound()
{
	setbuzzer(2865);
	playbuzzer();
	_delay_ms(150);
	setbuzzer(2551);
	_delay_ms(150);
	nobuzzer();
}

void result_sound()
{
	setbuzzer(2551);
	playbuzzer();
	_delay_ms(100);
	nobuzzer();
	_delay_ms(30);
	playbuzzer();
	setbuzzer(2551);
	_delay_ms(150);
	nobuzzer();
}

void bear_sound()
{
	nobuzzer();
	
	setbuzzer(2551); //도(4) 
	playbuzzer();
	_delay_ms(400);
	nobuzzer();
	_delay_ms(30);
	
	setbuzzer(2551); //도(2) 
	playbuzzer();
	_delay_ms(200);
	nobuzzer();
	_delay_ms(30);
	
	setbuzzer(2551); //도(2) 
	playbuzzer();
	_delay_ms(200);
	nobuzzer();
	_delay_ms(30);
	
	setbuzzer(2551); //도(4) 
	playbuzzer();
	_delay_ms(400);
	nobuzzer();
	_delay_ms(30);
	
	setbuzzer(2551); //도(4)  
	playbuzzer();
	_delay_ms(400);
	nobuzzer();
	_delay_ms(30);
	
	setbuzzer(3030); //미(4) 
	playbuzzer();
	_delay_ms(400);
	nobuzzer();
	_delay_ms(30);
	
	setbuzzer(3816); //솔(2) 
	playbuzzer();
	_delay_ms(200);
	nobuzzer();
	_delay_ms(30);
	
	setbuzzer(3816); //솔(2) 
	playbuzzer();
	_delay_ms(200);
	nobuzzer();
	_delay_ms(30);
	
	setbuzzer(3030); //미(4)
	playbuzzer();
	_delay_ms(400);
	nobuzzer();
	_delay_ms(30);
	
	setbuzzer(2551); //도(4) 
	playbuzzer();
	_delay_ms(400);
	nobuzzer();
	_delay_ms(30);
	
	setbuzzer(3816); //솔(2)
	playbuzzer();
	_delay_ms(200);
	nobuzzer();
	_delay_ms(30);
	
	setbuzzer(3816); //솔(2)
	playbuzzer();
	_delay_ms(200);
	nobuzzer();
	_delay_ms(30);
	
	setbuzzer(3030); //미(4)
	playbuzzer();
	_delay_ms(400);
	nobuzzer();
	_delay_ms(30);
	
	setbuzzer(3816); //솔(2)
	playbuzzer();
	_delay_ms(200);
	nobuzzer();
	_delay_ms(30);
	
	setbuzzer(3816); //솔(2)
	playbuzzer();
	_delay_ms(200);
	nobuzzer();
	_delay_ms(30);
	
	setbuzzer(3030); //미(4)
	playbuzzer();
	_delay_ms(400);
	nobuzzer();
	_delay_ms(30);
	
	setbuzzer(2551); //도(4)
	playbuzzer();
	_delay_ms(400);
	nobuzzer();
	_delay_ms(30);
	
	setbuzzer(2551); //도(4)
	playbuzzer();
	_delay_ms(400);
	nobuzzer();
	_delay_ms(30);
	
	setbuzzer(2551); //도(8)
	playbuzzer();
	_delay_ms(800);
	nobuzzer();
	_delay_ms(30);
}

int chat_to_note(char *_ca)
{
	int i, scaler;
	for(i = 0; i<12; i++)
	{
		if(_ca[0] == scale[i])
		{
			scaler = i;
			if(_ca[1] == '#') scaler ++;
		}
	}
	return scaler;
}

int chat_to_oct(char *_ca)
{
	int i, octer;
	if(_ca[1] != '#')
	{
		octer = _ca[1];
	}
	else
	{
		octer = _ca[2];
	}
	return octer;
}

void cla_hertz(int k, int j)
{
	int hertz;
	hertz = scaleoct[k][j];
	OCR3A = hertz;
}

void piano(char *_note, int _beat)
{
	int i, k;
	i = chat_to_note(_note);
	k = chat_to_oct(_note);
	cla_hertz(i, k);
	playbuzzer();
	beatbeat(_beat);
}

void beatbeat(int _beat)
{
	uint16_t _start=0, _end = 0;
	_start = millis();
	while(1)
	{
		_end = millis();
		if(_end - _start >= _beat) break;
	}
	nobuzzer();
}
