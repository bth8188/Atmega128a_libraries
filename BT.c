/*
 * BT.c
 *
 * Created: 2019-07-25 오전 9:39:09
 *  Author: bth8188
 */ 
#include "BT.h"

volatile uint8_t BT_String[64] = {0};
volatile uint8_t BT_Receive_Flag = 0;

void BT_Init()
{
	BTBRRH = 0;
	BTBRRL = 103;
	BTCSRB = (1<<BTRXEN) | (1<<BTTXEN) | (1<<BTRXCIE);
}

void BT_transmit(char data)
{
	while ( !(BTCSRA & (1<<BTDRE)) );
	BTDR = data;
}

unsigned char BT_receive()
{
	while ( !(BTCSRA & (1<<BTRXC)) );
	return BTDR;
}


void BT_printf_string(char *str)
{
	for (int i=0; str[i]; i++)
	BT_transmit(str[i]);
}

uint8_t isBTString()
{
	return BT_Receive_Flag;
}

uint8_t *getBTtring()
{
	BT_Receive_Flag = 0;
	return BT_String;
}

void BT_ISR_Receive()
{
	static uint8_t thead = 0;
	volatile uint8_t data;
	data= BTDR;
	
	if(data == '\n' || data == '\r')
	{
		BT_String[thead] = '\0';
		thead = 0;
		BT_Receive_Flag = 1;
	}
	else if(data != '\n')
	{
		BT_String[thead] = data;
		thead ++;
	}
}
