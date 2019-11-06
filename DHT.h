/*
 * DHT.h
 *
 * Created: 2019-08-01 오후 9:02:37
 *  Author: bth8188
 */ 


#ifndef DHT_H_
#define DHT_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define _DHT11	1
#define _DHT22	2
#define DHT_type	_DHT22

#define DHT_DDR			DDRC
#define DHT_PORT		PORTC
#define DHT_PIN			PINC
#define DHT_DATA_PIN	1




uint8_t get_DHT_status();
void receive_raw_data(uint8_t _data[4]);
void get_DHT_data(uint8_t humi[2], uint8_t temp[2]);

#endif /* DHT_H_ */
