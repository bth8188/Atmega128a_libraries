/*
 * FND.c
 *
 * Created: 2019-06-27 오후 3:14:58
 *  Author: bth8188
 */ 
#include "FND.h"

volatile uint16_t FNDdata = 0;
int FNDnum[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x67};


void show_FND(uint8_t fndpos, uint8_t data)
{
	button_FND_digit_PORT = ~(1<<(fndpos));
	FND_4_PORT = FNDnum[data];
}

void FND_Init()
{
	FND_4_DDR = 0xff;
	button_FND_digit_DDR = 0xfc;
}

void FND1Init()
{
	FND_1_DDR = 0xff;	
}

void mode_FND(int mode)
{
	FND_1_PORT = ~(FNDnum[mode]);
}

void getFNDdata(uint16_t t)
{
	FNDdata = t;
}
