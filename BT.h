/*
 * BT.h
 *
 * Created: 2019-07-25 오전 9:39:47
 *  Author: bth8188
 */ 

#ifndef BT_H_
#define BT_H_

#include <avr/io.h>


#define BTBRRH  UBRR1H
#define BTBRRL  UBRR1L
#define BTCSRA  UCSR1A
#define BTCSRB  UCSR1B
#define BTCSRC  UCSR1C
#define BTDR	UDR1
#define	BTDRE	UDRE1
#define BTRXEN	4
#define BTTXEN	3
#define BTRXCIE	7
#define BTRXC	7

void BT_Init();
void BT_transmit(char data);
unsigned char BT_receive();
uint8_t isBTString();
uint8_t *getBTtring();
void BT_ISR_Receive();
void BT_printf_string(char *str);



#endif /* BT_H_ */
