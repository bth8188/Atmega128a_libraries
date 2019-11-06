/*
 * button.h
 *
 * Created: 2019-07-12 오전 10:22:06
 *  Author: bth8188
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BUTTON_DDR DDRG
#define BUTTON_PIN PING
#define MENU_BUTTON PING1
#define UP_BUTTON PING2
#define DOWN_BUTTON PING3

void Button_Init();
int button(uint8_t _num);



#endif /* BUTTON_H_ */
