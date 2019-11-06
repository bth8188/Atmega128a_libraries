/*
 * dcmotor.h
 *
 * Created: 2019-07-05 오후 5:24:13
 *  Author: bth8188
 */ 


#ifndef DCMOTOR_H_
#define DCMOTOR_H_
#include <avr/io.h>

#define MOTOR_R  OCR3A
#define MOTOR_L  OCR3B

void DCmotorInit();
void DCmotorstop();
void DCmotorleft(uint8_t leftspeed);
void DCmotorright(uint8_t rightspeed);



#endif /* DCMOTOR_H_ */
