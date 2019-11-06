/*
 * ADC.c
 *
 * Created: 2019-07-10 오후 2:08:34
 *  Author: kccistc
 */ 
#include "ADC.h"

void ADC_Init()
{
	ADMUX |= (1 << REFS0);	//AVCC를 기준전압으로 선택
	
	ADCSRA |= 0X07;		//분주비 설정
	ADCSRA |= (1 << ADEN);		//ADC 활성화
	ADCSRA |= (1 << ADFR);		//프리러닝 모드
	
	ADCSRA |= (1 << ADSC);			//변환 시작
}

int read_ADC(unsigned char channel)
{
	ADMUX = ((ADMUX & 0XE0) | channel);		//채널 선택
	while(!(ADCSRA & (1 << ADIF)));		//변환종료 대기
	
	return ADC;			//10비트 값을 봔환
	
}