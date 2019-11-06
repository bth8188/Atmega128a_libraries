/*
 * buzzer.h
 *
 * Created: 2019-07-02 오후 5:16:35
 *  Author: bth8188
 */ 


#ifndef BUZZER_H_
#define BUZZER_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "time.h"

void buzzerInit();
void setbuzzer(int note);
void nobuzzer();
void playbuzzer();
void pibibip();
void pibibip2();
void start_sound();
void measure_sound();
void ready_sound();
void result_sound();
void bear_sound();
int chat_to_note(char *_ca);
int chat_to_oct(char *_ca);
void cla_hertz(int k, int j);
void piano(char *_note, int _beat);
void beatbeat(int _beat);




#endif /* BUZZER_H_ */
