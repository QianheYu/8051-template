#include "REG52.h"
#define KEY P1^0
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

code unsigned char words[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};  //0-9 use 7SEG-COM-ANODE

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

void delay(unsigned int time){
	while(time--);
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
    int i = 1;
    InterruptInit();
    TimerInit();
    SetSerial(0x50);
    Enable_Timer(TR1);
    while (1)
    {
//        switch(~KEY){
//            case 1:
//                SBUF = ~words[i++];
//                break;
//            default:
//                SBUF = 0xff;
//        }
		SBUF = ~words[i++];
		while(!TI){
			TI = 0;
		}
        if(i > 9){
            i = 0;
        }
		delay(65535);
    }
}
