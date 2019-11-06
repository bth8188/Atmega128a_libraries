/*
 * I2C.c
 *
 * Created: 2018-08-28 오후 3:19:23
 *  Author: scolpig
 */ 
#include <avr/io.h>
// #define F_CPU 16000000L
// #include <util/delay.h>
//#include <avr/interrupt.h>
#include "I2C.h"

//#define START 0x08
//#define SLA_W (0x27<<1)

void I2C_init(unsigned int baud){
	TWBR = baud;
}

void I2C_start(void)
{
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));  // 시작 완료 대기
}

void I2C_transmit(uint8_t data)
{
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}

void I2C_write_byte(uint8_t address, uint8_t data)
{
	I2C_start();
	I2C_transmit(address);
	I2C_transmit(data);
	I2C_stop();
}

void I2C_stop(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO);
}

uint8_t I2C_receive_ACK(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN) |(1<<TWEA);
	
	while( !(TWCR & (1<<TWINT)));             // 수신 완료 대기
	
	return TWDR;
}

uint8_t I2C_receive_NACK(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN);
	
	while( !(TWCR & (1<<TWINT)));             // 수신 완료 대기
	
	return TWDR;
}

