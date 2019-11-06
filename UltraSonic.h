/*
 * UltraSonic.h
 *
 * Created: 2019-07-03 오후 5:04:30
 *  Author: bth8188
 */ 


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void ultInit();
uint8_t measure_distance();
void UltraSonic_Recieve();
uint16_t dist();


#endif /* ULTRASONIC_H_ */
