#include "REG52.H"
#include "absacc.h"

#define KEY P1
#define DAC XBYTE [0x8000]
#define BUFF XBYTE [0x9000]

#define Enable_Interrupt(X) (X = 1)
#define Disable_Interrupt(X) (X = 0)

#ifdef __Enable_Priority__			//wether use the priority by your needed
	#define SetPriority(X) (IP = X)
#endif

#define Enable_Timer(X) (X = 1)
#define Disable_Timer(X) (X = 0)

#define SetTimermode(X) (TMOD |= X)
#define ResetTimermode() (TMOD = 0x00)

code int sin[60] = {100,110,121,131,141,150,159,167,174,181,187,191,195,198,199,200,199,198,195,191,187,181,174,167,159,150,
                    141,131,121,110,100,90,79,69,59,50,41,33,26,19,13,9,5,2,1,0,1,2,5,9,13,19,26,33,41,50,59,69,79,90};
static char mode = 0;


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
	Enable_Timer(TR0);
    while(1){
        mode = ~KEY;
        switch (mode)
        {
        case 1:
            time = -666;
            break;
        case 2:
            time = -20000;
            break;
        }
    }
}

void handler() interrupt 1
{
    switch(mode){
        case 1:
            if(i > 59){
				i = 0;
			}
			dacvalue = sin[i++];
            break;
        case 2:
            if(q){
				dacvalue = 0xff;
			}
			else{
				dacvalue = 0x00;
			}
			q = ~q;
            break;
    }
    DAC = dacvalue;
    BUFF = 0;
}
