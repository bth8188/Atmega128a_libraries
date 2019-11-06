#include "DS1302.h"

void DS1302_Init(void)
{
	DS1302_CLK_DDR |= (1<<DS1302_CLK);
	DS1302_DAT_DDR |= (1<<DS1302_DAT);
	DS1302_RST_DDR |= (1<<DS1302_RST);
}

void DS1302_Selected(void)
{
	DS1302_RST_PORT |= (1<<DS1302_RST); // CE High
}

void DS1302_Deselected(void)
{
	DS1302_RST_PORT &= ~(1<<DS1302_RST); // CE High
}

void DS1302_Clock(void)
{
	DS1302_CLK_PORT &= ~(1<<DS1302_CLK); // clk l->h->l
	DS1302_CLK_PORT |= (1<<DS1302_CLK);
	DS1302_CLK_PORT &= ~(1<<DS1302_CLK);

}

void DS1302_DataBitSet(void)
{
	DS1302_DAT_PORT |= (1<<DS1302_DAT); // data bit high
}

void DS1302_DataBitReset(void)
{
	DS1302_DAT_PORT &= ~(1<<DS1302_DAT); // data bit low
}


uint8_t DS1302_Read_DataPin(void)
{
	return (DS1302_DAT_PIN & (1<<DS1302_DAT));
}

void DS1302_Change_ReadMode(void)
{
	DS1302_DAT_DDR &= ~(1<<DS1302_DAT); // read mode
}

void DS1302_Change_WriteMode(void)
{
	DS1302_DAT_DDR |= (1<<DS1302_DAT); // write mode
}

uint8_t decimal_to_bcd(uint8_t decimal)
{
	return ( ((decimal/10)<<4) | (decimal%10) );
}

uint8_t bcd_to_decimal(uint8_t bcd)
{
	return ( ((bcd>>4) * 10) + (bcd & 0x0f) );
}

void DS1302_TxData(uint8_t txData)
{
	DS1302_Change_WriteMode();
	for (int i=0; i<8; i++)
	{
		if (txData & (1<<i))
		DS1302_DataBitSet();
		else
		DS1302_DataBitReset();
		
		DS1302_Clock();
	}
}

uint8_t DS1302_RxData(void)
{
	uint8_t rxData = 0;
	DS1302_Change_ReadMode();
	for (int i=0; i<8; i++)
	{
		rxData |= DS1302_Read_DataPin() ? (1<<i) : 0;
		// data = A ? b : c;  A가 참이면 b 반환, A가 거짓이면 c 반환
		DS1302_Clock();
	}
	return rxData;
}

void DS1302_WriteData(uint8_t address, uint8_t data)
{
	DS1302_Selected();
	DS1302_TxData(address);
	DS1302_TxData(decimal_to_bcd(data));
	DS1302_Deselected();
}

uint8_t DS1302_ReadData(uint8_t address)
{
	uint8_t rxData = 0;
	DS1302_Selected();
	DS1302_TxData(address+1);
	rxData = DS1302_RxData();
	DS1302_Deselected();
	
	return bcd_to_decimal(rxData);
}




void DS1302_GetTime(DS1302 *timeData)
{
	timeData->seconds = DS1302_ReadData(ADDRESS_SECONDS); // sec
	timeData->minutes = DS1302_ReadData(ADDRESS_MINUTES);
	timeData->hour = DS1302_ReadData(ADDRESS_HOUR);
}

void DS1302_GetDate(DS1302 *dateData)
{
	dateData->date = DS1302_ReadData(ADDRESS_DATE);
	dateData->month = DS1302_ReadData(ADDRESS_MONTH);
	dateData->dayofweek = DS1302_ReadData(ADDRESS_DAYOFWEEK);
	dateData->year = DS1302_ReadData(ADDRESS_YEAR);
}

void DS1302_SetTimeDates(DS1302 timeDate)
{
	DS1302_WriteData(ADDRESS_SECONDS, timeDate.seconds);
	DS1302_WriteData(ADDRESS_MINUTES, timeDate.minutes);
	DS1302_WriteData(ADDRESS_HOUR, timeDate.hour);
	DS1302_WriteData(ADDRESS_DATE, timeDate.date);
	DS1302_WriteData(ADDRESS_MONTH, timeDate.month);
	DS1302_WriteData(ADDRESS_DAYOFWEEK, timeDate.dayofweek);
	DS1302_WriteData(ADDRESS_YEAR, timeDate.year);
}

struct _ds1302 stTime;