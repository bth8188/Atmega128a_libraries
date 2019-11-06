/*
 * BT.h
 *
 * Created: 2019-07-25 ¿ÀÀü 9:39:47
 *  Author: bth8188
 */ 

#ifndef  UART0_H_
#define  UART0_H_

#include <avr/io.h>

void UART0_init();
void UART0_transmit(char data);
unsigned char UART0_receive();
void UART0_printf_string(char *str);
int isRxD0();
int isRxD1();
uint8_t isRxString();
uint8_t *getRxString();
void UART0_ISR_Recieve();
void UART0_ISR_BTset();
void UART1_init();
void UART1_transmit(char data);
unsigned char UART1_receive();
void UART1_printf_string(char *str);
void UART1_ISR_Recieve();
void UART1_ISR_BTset();





#endif
