#include "reg52.h"
#include "LCD1602.h"

sbit RS = P2^0;
sbit RW = P2^1;
sbit EN = P2^2;
sfr DATAPort = 0x80;

static void delay(unsigned int time)
{
    char i;
	while (time--)
	{
		for(i = 0; i < 120; i++);
	}
}

bit getLcdState()
{
    unsigned char state;
    RS = 0;
    RW = 1;
	EN = 1;
    state = DATAPort;
	delay(5);
	EN = 0;
    return (bit)((state&0x80)>>7);
}

void Lcdwrite(unsigned char dat, bit mode)
{
    while(getLcdState());
    RS = mode;
    RW = 0;
	EN = 0;
    DATAPort = dat;
    delay(5);
    EN = 1;
    delay(5);
    EN = 0;
}

unsigned char Lcdread(bit mode)
{
    unsigned char dat;
	while(getLcdState());
    RS = mode;
    RW = 1;
	EN = 1;
    dat = DATAPort;
    delay(5);
    EN = 0;
	return dat;
}

void LcdInit()
{
	EN = 0;
	Lcdwrite(0x38, 0);
	Lcdwrite(0x0c, 0);
	Lcdwrite(0x06, 0);
	Lcdwrite(0x01, 0);
}


void show(char *string, unsigned char position)
{
	int i;
	Lcdwrite(position + 0x80, 0);
	for(i = 0; string[i] != '\0'; i++)
	{
		Lcdwrite(string[i], 1);
	}
	
}
