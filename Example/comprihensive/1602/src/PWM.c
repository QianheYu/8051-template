/****************************************
 * 
 * PWM demo
 * 
 * @author Qianhe Yu
 * 
 * **************************************
*/
#include "REG52.H"
#include "formatData.h"

sbit motor = P2^5;
extern unsigned short width;

void interruptInit()
{
	ET0 = 1;
	EA = 1;
}

void timerInit()
{
    TMOD |= 0x01;
    TH0 = 0xFC;
    TL0 = 0x18;
    TR0 = 1;
}

void handler() interrupt 1
{
	unsigned short count;
	TH0 = 0xFC;
    TL0 = 0x18;
    count = (++count)%10;
	if(count < width)
	{
		motor = 1;
	}
	else
	{
		motor = 0;
	}
	if(count == 0)
	{
		formatData();
	}
}
