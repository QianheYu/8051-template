/**
 * *********************************************
 * 
 * 8051 control LCD1602 demo
 * 
 * @author qianhe yu
 * 
 * *********************************************
*/

#include "REG52.H"
#include "LCD1602.H"
//#include "DS18B20.h"
#include "PWM.h"


typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;

typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int32_t;

//char *string = "TEMP:    . C";
//char *motorstate = "SPEED:0  ";
//char *beepstate = "normal ";

extern char string[];
extern char *motorstate;
extern char *beepstate;

//void formatData()
//{
//	int dat = getTemperature();
//	int temp = dat/10;
//	string[7] = '0' + (dat%1000/100);
//	string[8] = '0' + (dat%100/10);
//	string[10] = '0' + (dat%10);
//	if(flag)
//	{
//		string[5] = '-';
//	}
//	else
//	{
//		string[5] = ' ';
//	}
//	
//#ifndef __DEBUG__
//	if(!flag)
//	{
//		if(temp > 25)
//		{
//			if(temp > 30)
//			{
//				beep = 0;
//				beepstate = "warning";
//			}
//			else
//			{
//				beep = 1;
//				beepstate = "normal ";
//			}
//			motor = 1;
//			motorstate = "SPEED:3  ";
//		}
//		else
//		{
//			beep = 1;
//			motor = 0;
//			beepstate = "normal ";
//			motorstate = "SPEED:0  ";
//		}
//	}
//#else
//	if(!flag)
//	{
//		if(temp > 25)
//		{
//			if(temp > 30)
//			{
//				motorControl(10);
//				beep = 0;
//				return;
//				
//			}
//			motorControl((temp - 25)*2); 
//			beep = 1;
//		}
//		else
//		{
//			motorControl(0);
//			beep = 1;
//		}
//	}
//#endif
//}

void main()
{
	timerInit();
	interruptInit();
	LcdInit();
    while (1)
    {
//        formatData();
		
		show(string, 0x00);
		show(motorstate, 0x40);
		show(beepstate, 0x48);
    }
}
