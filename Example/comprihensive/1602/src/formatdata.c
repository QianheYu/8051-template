#include "reg52.h"
#include "DS18B02.h"

extern char string[];
extern char *motorstate;
extern char *beepstate;
unsigned short width;
bit flag = 0;
sbit beep = P2^4;

void formatData()
{
	int dat = getTemperature();
	int temp = dat/10;
	string[7] = '0' + (dat%1000/100);
	string[8] = '0' + (dat%100/10);
	string[10] = '0' + (dat%10);
	if(flag)
	{
		string[5] = '-';
	}
	else
	{
		string[5] = ' ';
	}

	if(!flag)
	{
		if(temp > 25)
		{
			if(temp > 30)
			{
				width = 10;
				beep = 0;
				motorstate = "SPEED:2";
				beepstate = "warning";
			}
			else
			{
				width = (temp - 25)*2;
				beep = 1;
				motorstate = "SPEED:1";
				beepstate = "normal ";
			}
		}
		else
		{
			width = 0;
			beep = 1;
			motorstate = "SPEED:0";
			beepstate = "normal ";
		}
	}
}