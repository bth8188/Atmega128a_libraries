/*
 * DHT.c
 *
 * Created: 2019-08-01 오후 9:01:57
 *  Author: bth8188
 */ 
#include "DHT.h"

enum {OK, Fail_H, Fail_T, checksum, Timeout} DHT_status;

uint8_t get_DHT_status()
{
	return DHT_status;
}

uint8_t check_timeout(uint8_t *_checker, uint8_t _timer)
{
	_delay_us(2);
	(*_checker) ++;
	if(*_checker > _timer)
	{
		DHT_status = Timeout;
		return 1;
	}
	return 0;
}

void send_s_signal()
{
	DHT_DDR |= (0x01 << DHT_DATA_PIN);		// DDR 출력 설정
	DHT_PORT |= (0x01 << DHT_DATA_PIN);		// high 신호 송출
	DHT_PORT &= ~(0x01 << DHT_DATA_PIN);	// low 신호 송출
	_delay_ms(20);		// 최소 18ms이상의 대기시간
	DHT_PORT |= (0x01 << DHT_DATA_PIN);		// high 신호 송출
}

void receive_signal()
{
	uint8_t checker = 0;
	DHT_DDR &= ~(0x01 << DHT_DATA_PIN);
	while((DHT_PIN & (0x01 << DHT_DATA_PIN)))		//DHT 신호가 0이 되는걸 대기
	{
		if(check_timeout(&checker, 30)) break;
	}
	checker = 0;
	if(DHT_status == OK)
	{
		while(!(DHT_PIN&(0x01 << DHT_DATA_PIN)))		//DHT 신호가 1이 되는걸 대기
		{
			if(check_timeout(&checker, 50)) break;
		}
		checker = 0;
		while((DHT_PIN & (0x01 << DHT_DATA_PIN)))	//DHT 신호가 0이 되는걸 대기
		{
			if(check_timeout(&checker, 50)) break;
		}
		checker = 0;
	}
}

void receive_raw_data(uint8_t _data[4])
{
	uint8_t checker = 0, raw_data[5];
	int conH =0, conV =0;
//	cli();
	DHT_status = OK;
	send_s_signal();
	receive_signal();
	if(DHT_status == OK)
	{
		for(int i=0; i< 5; i++)
		{
			raw_data[i] = 0;
			for(int j =7; j> -1; j--)
			{
				while(!(DHT_PIN&(0x01 << DHT_DATA_PIN)))		//신호가 1이 되는걸 대기
				{
					if(check_timeout(&checker, 20))
					{
						i = 5;
						break;
					}
				}
				checker = 0;
				if(DHT_status == OK)
				{
					_delay_us(35);
					raw_data[i] |= (DHT_PIN&(0x01 << DHT_DATA_PIN)) == (0x01 << DHT_DATA_PIN)? (1 << j) : 0;
					while((DHT_PIN&(0x01 << DHT_DATA_PIN)))
					{
						if(check_timeout(&checker, 25))
						{
							i = 5;
							break;
						}
					}
					checker =0;
				}
			}
		}
	}
	DHT_DDR |= (0x01 << DHT_DATA_PIN);		// DDR 출력 설정
	DHT_PORT |= (0x01 << DHT_DATA_PIN);		// high 신호 송출
//	sei();
 	if(DHT_status == OK)
 	{
		#if ((DHT_type == _DHT11))
	 	if(raw_data[0] + raw_data[1] + raw_data[2] + raw_data[3] != raw_data[4]) DHT_status = checksum;
		 
		#elif (DHT_type == _DHT22)
		if(raw_data[0] + raw_data[1] + raw_data[2] + raw_data[3] > 0xff)
		{
			if(raw_data[0] + raw_data[1] + raw_data[2] + raw_data[3] - 0x100 != raw_data[4]) DHT_status = checksum;
		}
		else if(raw_data[0] + raw_data[1] + raw_data[2] + raw_data[3] != raw_data[4]) DHT_status = checksum;
		#endif
		 
		#if (DHT_type == _DHT11)
		if((raw_data[0] >95) || (raw_data[0]) < 15) DHT_status = Fail_H;
		if((raw_data[2] >52) || (raw_data[2]) < -2) DHT_status = Fail_T;
		
  		#elif (DHT_type == _DHT22)
		conH |= ((uint16_t)raw_data[0]<<8) | raw_data[1];
		conV |= ((uint16_t)raw_data[2]<<8) | raw_data[3];
  		if( (conH >1020) || ( conH < -20) ) DHT_status = Fail_H;
  		if(  (conV > 800) || ( conV < -400) ) DHT_status = Fail_T;
  		
		#endif
 	}
	if(DHT_status == OK)
	{
		for(int k = 0; k < 4; k++) _data[k] = raw_data[k];
	}
 	if(DHT_status != OK)
 	{
 		for(int k = 0; k < 4; k++) _data[k] = '\0';
 	}
}


void get_DHT_data(uint8_t humi[2], uint8_t temp[2])
{
	uint8_t data[4];
	
	receive_raw_data(data);
	
#if (DHT_type == _DHT11)
	humi[0] = data[0];
	humi[1] = data[1];
	temp[0] = data[2];
	temp[1] = data[3];

#elif (DHT_type == _DHT22)
	uint16_t _humi =0, _temp =0;
	_humi |= ((uint16_t)data[0]<<8) | data[1];
	_temp |= ((uint16_t)data[2]<<8) | data[3];
	
	humi[0] = _humi / 10;
	humi[1] = _humi % 10;
	
	temp[0] = _temp / 10;
	temp[1] = _temp % 10;
#endif
}