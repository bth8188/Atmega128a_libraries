/*
 * ADC.h
 *
 * Created: 2019-07-10 오후 2:08:46
 *  Author: kccistc
 */ 


#ifndef ADC_H_
#define ADC_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void ADC_Init();
int read_ADC(unsigned char channel);




#endif /* ADC_H_ */