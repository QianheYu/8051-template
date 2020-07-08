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

char string[] = "TEMP:    . C";
char *motorstate = "SPEED:0  ";
char *beepstate = "normal ";

extern char string[];
extern char *motorstate;
extern char *beepstate;

void main()
{
	timerInit();
	interruptInit();
	LcdInit();
    while (1)
    {
		show(string, 0x00);
		show(motorstate, 0x40);
		show(beepstate, 0x48);
    }
}
