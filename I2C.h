/*
 * I2C.h
 *
 * Created: 2018-09-03 오전 11:47:12
 *  Author: 6층교수실PC
 */ 


#ifndef I2C_H_
#define I2C_H_

void I2C_init(unsigned int baud);
void I2C_start(void);
void I2C_transmit(uint8_t data);
void I2C_write_byte(uint8_t address, uint8_t data);
void I2C_stop(void);
uint8_t I2C_receive_ACK(void);
uint8_t I2C_receive_NACK(void);

#endif /* I2C_H_ */