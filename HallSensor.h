/*
 * HallSensor.h
 *
 * Created: 2019-08-27 오후 3:09:41
 *  Author: kccistc
 */ 


#ifndef HALLSENSOR_H_
#define HALLSENSOR_H_

#include <avr/interrupt.h>
#include <avr/io.h>

#define HallSensor_Port PORTE
#define HallSensor_Apin PINE6
#define HallSensor_Bpin PINE7

void HallSensor_Init();
void ISR_Toggle_A();
void ISR_Toggle_B();
uint32_t get_rotation();
uint8_t get_direction();
void set_rotation(uint32_t _num);



#endif /* HALLSENSOR_H_ */