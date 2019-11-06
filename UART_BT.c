/*
 * UART0.c
 *
 * Created: 2019-06-27 오후 4:46:55
 *  Author: bth8188
 */ 
#include "UART_BT.h"

volatile uint8_t rxString[64] = {0};
volatile uint8_t rxReadyFlag = 0;

void UART0_init()
{
	UBRR0H = 0;
	UBRR0L = 207;
	/* Enable receiver and transmitter */
	UCSR0A |= _BV(U2X0);
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
	
int isRxD0()
{
	return (UCSR0A&(1<<RXC0));
}

int isRxD1()
{
	return (UCSR1A&(1<<RXC1));
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
		rxString[head] = '\0';
		head = 0;
		rxReadyFlag = 1;
	}
	else
	{
		rxString[head] = data;
		head ++;
	}
}

void UART0_ISR_BTset()
{
	static uint8_t head = 0;
	volatile uint8_t data;
	data= UDR0;
	
	if(data == '\n' || data == '\r')
	{
		rxString[head] = '\r';
		rxString[head+1] = data;
		rxString[head+2] = '\0';
		head = 0;
		rxReadyFlag = 1;
	}
	else
	{
		rxString[head] = data;
		head ++;
	}
}

void UART1_init()
{
	UBRR1H = 0;
	UBRR1L = 207;
	/* Enable receiver and transmitter */
	UCSR1A |= _BV(U2X1);
	UCSR1C |= 0x06;
	UCSR1B = (1<<RXEN1)|(1<<TXEN1) | _BV(RXCIE1);
}

void UART1_transmit(char data)
{
	while ( !(UCSR1A & (1<<UDRE1)) );
	UDR1 = data;
}

unsigned char UART1_receive()
{
	while ( !(UCSR1A & (1<<RXC1)) );
	return UDR1;
}

void UART1_printf_string(char *str)
{
	for (int i=0; str[i]; i++)
	UART1_transmit(str[i]);
}


void UART1_ISR_Recieve()
{
	static uint8_t head = 0;
	volatile uint8_t data;
	data= UDR1;
	
	if(data == '\n' || data == '\r')
	{
		rxString[head] = '\0';
		head = 0;
		rxReadyFlag = 1;
	}
	else
	{
		rxString[head] = data;
		head ++;
	}
}

void UART1_ISR_BTset()
{
	static uint8_t head = 0;
	volatile uint8_t data;
	data= UDR1;
	
	if(data == '\n' || data == '\r')
	{
		rxString[head] = '\r';
		rxString[head+1] = data;
		rxString[head+2] = '\0';
		head = 0;
		rxReadyFlag = 1;
	}
	else
	{
		rxString[head] = data;
		head ++;
	}
}
