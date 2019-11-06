/*
 * HX711.h
 *
 * Created: 2019-08-08 오후 2:43:33
 *  Author: bth8188
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#ifndef HX711_H_
#define HX711_H_

#define HX711_DDR	DDRC
#define HX711_PORT	PORTC
#define HX711_PIN	PINC
#define HX711_DO_PIN	PINC4
#define HX711_SCLK_PIN	PINC5

void HX711_init();
void power_off();
void set_offset(int _num);
uint32_t get_value(int num);
void calc_value(int _num, uint32_t weight[2]);





#endif /* HX711_H_ */
