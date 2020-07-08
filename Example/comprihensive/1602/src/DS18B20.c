#include "reg52.h"
#include "DS18B20.h"

sbit TEMPERATURE = P2^3;
extern bit flag;
static void delay(unsigned int time)
{
	while(time--);
}

void Reset()
{
	TEMPERATURE = 1;
	delay(2);
	TEMPERATURE = 0;
	delay(60);
	TEMPERATURE = 1;
	delay(30);
}

void write(unsigned char dat)
{
	int i;
	for(i = 8; i > 0; i--)
	{
		TEMPERATURE = 0;
		TEMPERATURE = dat&0x01;
		delay(6);
		TEMPERATURE = 1;
		dat >>= 1;
	}
}

unsigned char read()
{
	unsigned char i;
	unsigned char dat;
	for(i = 8; i > 0; i--)
	{
		TEMPERATURE = 0;
		delay(1);
		dat >>= 1;
		TEMPERATURE = 1;
		if(TEMPERATURE)
		{
			dat |= 0x80;
			
		}
		delay(2);
	}
	return (dat);
}


unsigned int getTemperature()
{
	unsigned char a, b;
	unsigned int dat;
	Reset();
	write(SKROM);
	write(CVTP);
	Reset();
	
	write(SKROM);
	write(RDSC);
	a = read();
	b = read();
	
	dat = b;
	dat <<= 8;
	dat = dat | a;
	
	if(dat < 0x07ff)
	{
		flag = 0;
	}
	else
	{
		dat = ~dat + 1;
		flag = 1;
	}
	dat *= 0.625;

	return (dat);
}