#include "reg52.h"

typedefe unsigned char u8;
typedefe unsigned int u16;

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


#define PSTOP 0x01 
#define PGO 0x02

#define CSTOP 0x01
#define CWARN 0x02
#define CGO 0x03

typedef enum lightstate{
    int STOP = 0,
    int WORN = 1,
    int GO = 2
} TypedefLightState;



u8 wordTab[10] = {};
u8 tabIndex[8] = {};
static struct traficlight
{
    TypedefLightState carlightstate;
    TypedefLightState personlightstate;
};


void show(u8 word, u8 position){
    P1 = word;
    P3 = (P3 & 0x1c) | (position*0x03);
    P1 = 0x00;
}

void dynamicshow(u8 *array){
    for(int i = 0; i < 8; i++){
        show(array[i], tabIndex[i]);
    }
}

TypedefLightState personTraffic(){
    if(state == GO){
        personTraffic();
    }
    else{

    }
    return;
}

void carTraffic(){

}

void goStateDelay(){
    if(personState == GO && key){
        time += 30;
    }
}

void main(){

}

void timerHandler() interrupt 1
{

}