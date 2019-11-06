/*
 * lcd.c
 *
 * Created: 2019-07-02 오후 2:11:27
 *  Author: bth8188
 */ 
#include "lcd.h"


void LCD_pulse_enable()
{
	PORT_CONTROL |= _BV(E_PIN);
	_delay_ms(1);
	PORT_CONTROL &= ~(_BV(E_PIN));
	_delay_ms(1);
}

void LCD_write_data(uint8_t data)
{
	PORT_CONTROL |= _BV(RS_PIN);
	PORT_DATA = data;
	LCD_pulse_enable();
	_delay_ms(2);
}

void LCD_write_command(uint8_t command)
{
	PORT_CONTROL &= ~(_BV(RS_PIN));
	PORT_DATA = command;
	LCD_pulse_enable();
	_delay_ms(2);
}

void LCD_clear()
{
	LCD_write_command(COMMAND_CLEAR_DISPLAY);
	_delay_ms(2);
}

void LCD_init()
{
	_delay_ms(50);
	
	DDR_DATA = 0xff;
	PORT_DATA = 0x00;
	DDR_CONTROL |= _BV(RS_PIN) | _BV(RW_PIN) |_BV(E_PIN);
	
	PORT_CONTROL &= ~(_BV(RW_PIN));
	
	LCD_write_command(COMMAND_8_BIT_MODE);
	
	uint8_t command = 0x08 | _BV(COMMAND_DISPLAY_ON_OFF_BIT);
	LCD_write_command(command);
	
	LCD_clear();
	
	LCD_write_command(0x06);
}

void LCD_write_string(char *string)
{
	uint8_t i;
	for(i=0; string[i]; i++)
	LCD_write_data(string[i]);
}

void LCD_goto_XY(uint8_t row, uint8_t col)
{
	col %= 16;
	row %= 2;
	
	uint8_t address = (0x40 * row) +col;
	uint8_t command = 0x80 + address;
	
	LCD_write_command(command);
}

void LCD_write_XY_string(uint8_t row, uint8_t col, char *string)
{
	LCD_goto_XY(row, col);
	LCD_write_string(string);
}

void Time_Frame()
{
	LCD_write_XY_string(0, 0, "Time>>");
	LCD_write_XY_string(0, 8, ":");
	LCD_write_XY_string(0, 11, ":");
}
