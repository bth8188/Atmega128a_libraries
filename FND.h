/*
 * FND.h
 *
 * Created: 2019-06-27 오후 3:15:11
 *  Author: bth8188
 */ 

#ifndef FND_H_
#define FND_H_


#include <avr/io.h>

#define button_FND_digit_DDR    DDRA
#define button_FND_digit_PORT    PORTA
#define FND_4_DDR   DDRB
#define FND_4_PORT   PORTB
#define FND_1_DDR   DDRC
#define FND_1_PORT   PORTC
#define FND_POS1	6
#define FND_POS2	5
#define FND_POS3	4
#define FND_POS4	3

void show_FND(uint8_t fndpos, uint8_t data);
void FND_Init();
void FND1Init();
void mode_FND(int mode);
void getFNDdata(uint16_t t);



#endif /* FND_H_ */
