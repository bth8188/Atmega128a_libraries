#ifndef  UART0_H_
#define  UART0_H_

#include <avr/io.h>

void UART0_init();
void UART0_transmit(char data);
unsigned char UART0_receive();
void UART0_printf_string(char *str);
int isRxD();
uint8_t isRxString();
uint8_t *getRxString();
void UART0_ISR_Recieve();



#endif