/*
 * UART0.c
 *
 * Created: 2019-06-27 오후 4:46:55
 *  Author: bth8188
 */ 
#include "UART0.h"

volatile uint8_t rxString[64] = {0};
volatile uint8_t rxReadyFlag = 0;

void UART0_init()
{
	UBRR0H = 0;
	UBRR0L = 207;
	/* Enable receiver and transmitter */
	UCSR0A |= _BV(U2X1);
	UCSR0C |= 0x06;
	UCSR0B = (1<<RXEN0)|(1<<TXEN0) | _BV(RXCIE0);
}

void UART0_transmit(char data)
{
	while ( !(UCSR0A & (1<<UDRE0)) );
	UDR0 = data;
}
unsigned char UART0_receive()
{
	while ( !(UCSR0A & (1<<RXC0)) );
	return UDR0;
}
void UART0_printf_string(char *str)
{
	for (int i=0; str[i]; i++)
	UART0_transmit(str[i]);
}
	
int isRxD()
{
	return (UCSR0A&(1<<RXC0));
}

uint8_t isRxString()
{
	return rxReadyFlag;
}

uint8_t *getRxString()
{
	rxReadyFlag = 0;
	return rxString;
}

void UART0_ISR_Recieve()
{
	static uint8_t head = 0;
	volatile uint8_t data;
	data= UDR0;
	
	if(data == '\n' || data == '\r')
	{
		rxString[head] = '\n';
		head = 0;
		rxReadyFlag = 1;
	}
	else
	{
		rxString[head] = data;
		head ++;
	}
}
