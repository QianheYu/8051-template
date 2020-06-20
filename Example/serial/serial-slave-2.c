#include "REG52.h"
#include "absacc.h"
/**
 * Define the function about Timer, Interrupt and Serial
 * to make them looks great more.
*/
#define Enable_Interrupt(X) (X = 1)
#define Disable_Interrupt(X) (X = 0)

#ifdef __Enable_Priority__			//use the priority on your needs
	#define SetPriority(X) (IP = X)
#endif

#define Enable_Timer(X) (X = 1)
#define Disable_Timer(X) (X = 0)

#define SetTimermode(X) (TMOD |= X)
#define ResetTimermode() (TMOD = 0x00)

#define SetSerial(X) (SCON = X)
#define Enable_MultFrequency() (SMOD = 1)
#define Disable_MultFrequnency() (SMOD = 0)
#define Enable_Reseive() (REN = 1)
#define Disable_Reseive() (REN = 0)
#define GetState(X) (X)

#define LED XBYTE [0x9000]
/**
 * @function Init Interrupt
*/
void InterruptInit(){
	
#ifdef __Enable_Priority__
	SetPriority();
#endif
	
	Enable_Interrupt(ES);
	Enable_Interrupt(EA);
}

/**
 * @function Init Timer.
*/
void TimerInit(){
    SetTimermode(0x20);
    TH1 = 0xfd;
    TL1 = 0xfd;
}

void main(){
    InterruptInit();
    TimerInit();
    SetSerial(0x50);
    Enable_Timer(TR1);
    while (1)
    {

    }
}

void serialHandler() interrupt 4
{
    if(GetState(RI)){
		LED = SBUF;
		RI = 0;
    } 
}
