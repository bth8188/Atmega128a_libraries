/*
 * graphic.h
 *
 * Created: 2019-09-02 오후 8:32:28
 *  Author: kccistc
 */ 


#ifndef GRAPHIC_H_
#define GRAPHIC_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define GP_LCD_Data_DDR DDRD
#define GP_LCD_Data_PORT PORTD
#define GP_LCD_Data_PIN PIND
#define GP_LCD_CMD_DDR DDRF
#define GP_LCD_CMD_PORT PORTF
#define GP_LCD_Data_DB0 0
#define GP_LCD_Data_DB1 1
#define GP_LCD_Data_DB2 2
#define GP_LCD_Data_DB3 3
#define GP_LCD_Data_DB4 4
#define GP_LCD_Data_DB5 5
#define GP_LCD_Data_DB6 6
#define GP_LCD_Data_DB7 7

#define GP_LCD_CS1 PINF0
#define GP_LCD_CS2 PINF1
#define GP_LCD_RES PINF2
#define GP_LCD_RW PINF3
#define GP_LCD_DI PINF4
#define GP_LCD_ECLK PINF5

#define CMD_On	0x3f
#define CMD_Off	0x3E
#define CMD_Set_Yaddr	0x40
#define CMD_Set_Page	0xB8
#define CMD_Set_Sline	0xC0
#define CMD_Clear	0x01
#define CS_Low_Active	(0x00 | (1 << GP_LCD_CS1) | (1 << GP_LCD_CS2))
#define CS_High_Active	0x00
#define GLCD_CS_Type	CS_High_Active

#define Left_side 0
#define Right_side 1
#define Both_side 2
#define Non_side 3

void LCD_Init();
void LCD_Ypage_Write_Data(uint8_t _side ,int y, uint8_t page, uint8_t dot);
void GLCD_handler(char rs, char cs, char data);
void test_l();

#endif /* GRAPHIC_H_ */