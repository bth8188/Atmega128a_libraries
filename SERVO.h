/*
 * SERVO.h
 *
 * Created: 2019-07-10 오후 3:05:03
 *  Author: kccistc
 */ 


#ifndef SERVO_H_
#define SERVO_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void servoInit();
void servo_run(uint8_t degree);




#endif /* SERVO_H_ */