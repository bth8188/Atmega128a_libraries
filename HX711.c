/*
 * HX711.c
 *
 * Created: 2019-08-08 오후 2:43:13
 *  Author: bth8188
 */ 
#include "HX711.h"

uint32_t offset;
double load_scale = 440.5997;

void power_off()
{
	HX711_PORT |= (1 << HX711_SCLK_PIN);
	_delay_us(60);
}

void power_on()
{
	HX711_PORT &= ~(1 << HX711_SCLK_PIN);
}

void HX711_init()
{
	//DDR setting
	HX711_DDR &= ~(1 << HX711_DO_PIN);
	HX711_DDR |= (0x01 << HX711_SCLK_PIN);
}

void rising_edge()
{
	HX711_PORT &= ~(1 << HX711_SCLK_PIN);
	HX711_PORT |= (1 << HX711_SCLK_PIN);
}

void falling_edge()
{
	HX711_PORT |= (1 << HX711_SCLK_PIN);
	HX711_PORT &= ~(1 << HX711_SCLK_PIN);
}

uint8_t Load_Cell_Ready()
{
	power_on();
	if(HX711_PIN & (1 << HX711_DO_PIN)) return 0;
	else return 1;
}


uint32_t read_load_cell()
{
	uint32_t temp = 0;
	uint8_t filler = 0x00, at;
	while(!Load_Cell_Ready());
	for(int j =23; j > -1; j--)
	{
		rising_edge();
		at = (HX711_PIN & (1 << HX711_DO_PIN)) == (1 << HX711_DO_PIN) ? 0x01 : 0x00;
		temp |= ((uint32_t)at << j);
	}
	rising_edge();
	falling_edge();
	if(temp & 0x800000) filler = 0xff;
	temp |= ((uint32_t)filler << 24);

	return temp;
}

uint32_t avg_value(int num)
{
	uint32_t sum =0;
	for(int i =0; i <num; i++)
	{
		sum += (read_load_cell() / num);
	}
	return sum;
}

void set_offset(int _num)
{
	offset = avg_value(_num);
}

uint32_t get_value(int num)
{
	uint32_t temp = avg_value(num) - offset;
	if(temp>0xffff0000) temp =0;
	return temp;
}

void calc_value(int _num, uint32_t weight[2])
{
	weight[0] = (double)get_value(_num) / load_scale;
	weight[1] = (uint32_t)(((double)get_value(_num) / load_scale) *100) %100;
}
