#include "REG52.H"
#include "absacc.h"

#define KEY P1
#define DAC XBYTE [0x8000]
#define Enable_Interrupt(X) (X = 1)
#define Disable_Interrupt(X) (X = 0)

#ifdef __Enable_Priority__			//wether use the priority by your needed
	#define SetPriority(X) (IP = X)
#endif

#define Enable_Timer(X) (X = 1)
#define Disable_Timer(X) (X = 0)

#define SetTimermode(X) (TMOD |= X)
#define ResetTimermode() (TMOD = 0x00)

static unsigned int time = 0;
static unsigned char dacvalue;

void InterruptInit(){
	
#ifdef __Enable_Priority__
	SetPriority();
#endif
	
	Enable_Interrupt(ET0);
	Enable_Interrupt(EA);
}

void TimerInit(){
	SetTimermode(0x01);
}

void SetTimer(unsigned int time){
	TL0 = time & 0x00ff;
	TH0 = time >> 8;
}

void main(){
	TimerInit();
	SetTimer(time);
	InterruptInit();
    time = -117;
	Enable_Timer(TR0);
	while(1){
		
	}
}

void timerHandler() interrupt 1
{
	SetTimer(time);
	dacvalue--;
	DAC = dacvalue;
}