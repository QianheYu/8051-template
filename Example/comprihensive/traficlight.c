#include "reg52.h"

typedef unsigned char u8;
typedef unsigned int u16;

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

#define PRED 0x01
#define PGREEN 0x02
#define RED 0x06
#define YELLOW 0x05
#define GREEN 0x03
#define NOLIGHT 0x07

sbit dknb = P2^5;
sbit dkrx = P2^6;

typedef enum toward{
    NB,
    RX
} TypedefTowardState;

typedef enum lightstate{
    STOP,
    WARN,
    GO
} TypedefLightState;

typedef struct traficlightstate
{
    TypedefTowardState toward;
    TypedefLightState carlightstate;
    TypedefLightState personlightstate;
} TypedefTrafficLightState;

TypedefTrafficLightState trafficlight;
u8 wordTab[10] = {};
u8 tabIndex[8] = {};
static int time = 0;
static int basetime = 0;

void timerInit(){
    SetTimermode(0x02);
    TH0 = 56;
    TL0 = 56;
    Enable_Timer(TR0);
}

void interruptInit(){
    Enable_Interrupt(EA);
    Enable_Interrupt(TF0);
}
/**
 * @fun show a number on a 7seg.
 * @par word, the words code.
 *      position, show words code on the position of a 7segs. 
*/
void show(u8 word, u8 position){
    P0 = word;
    P2 = (P2 & 0xe3) | (position*0x04);
    P0 = 0x00;
}
/**
 * @func show sth. on a 7segs.
 * @par usigned char *array, a array pointer that you want to show.
*/
void groupShow(u8 *array){
    for(int i = 0; i < 8; i++){
        show(array[i], tabIndex[i]);
    }
}

/**
 * @function change time
 * @return Timer ranmaining
*/
int timeControl()
{
    if(basetime == 5000)
    {
        time--;
    }
    if(!time)
    {
        time = 33;
        if(trafficlight.toward == NB)
        {
            trafficlight.toward == RX;
        }
        else
        {
            trafficlight.toward == NB;
        }
    }
    switch (time)
    {
    case 33:
        trafficlight.carlightstate == GO;
        break;
    case 3:
        trafficlight.carlightstate == WARN;
        break;
    }
    return time;
}

TypedefLightState carTraffic(){
    static TypedefTrafficLightState ctemp;
    static u8 cMultiplier = 0x02;
    if (ctemp != trafficlight)
    {
        if(trafficlight.carlightstate == GO){
            temp = GREEN;
        }
        else if(trafficlight.carlightstate == WARN)
        {
            temp = YELLOW;
        }
        if (trafficlight.carlightstate == NB)
        {
            temp = temp*cMultiplier || RED*(~cMultiplier && 0x03);
        }
        else
        {
            temp = temp*(~cMultiplier && 0x03) || RED*cMultiplier;
        }
    }
    P1 = temp | (P1 & 0x02);
    return trafficlight.carlightstate;
}

TypedefLightState personLight()
{
    static TypedefTrafficLightState stemp;
    static u8 pMultiplier;
    if (stemp != trafficlight)
    {
        if (trafficlight.carlightstate == GO)
        {
            temp = GREEN;
            trafficlight.personlightstate = GO;
        }
        else
        {
            temp = RED;
            trafficlight.personlightstate = STOP;
        }
        if (trafficlight.toward == NB)
        {
            P1 = temp | (P1 & 0xfd); 
            P3 = RED | (P1 & 0xfd);
        }
        else
        {
            P1 = RED | (P1 & 0xfd); 
            P3 = temp | (P1 & 0xfd); 
        }
    }
    return trafficlight.personlightstate;
}

void lightBlink(TypedefLightState car, TypedefLightState peo){
    static u8 cblink = 0x02;
    static u8 pblink = ;
    if (trafficlight.toward == NB)
    {
        
    }
    if (trafficlight.carlightstate == WARN && timetemp - basetime > 100)
    {

    }
    if (trafficlight.personlightstate == GO && time < 5 && timetemp - basetime > 100)
    {
        
    }
}

void goStateDelay(){
    if(traficlight.toward == NB){
        if(traficlight.personlightstate == GO && dknb){
            int temp = basetime;
            if( (temp+30) == basetime){
                time += 30;
            }
        }
    }
    else
    {
        if(traficlight.personlightstate == GO && dkrx){
            int temp = basetime;
            if( (temp+30) == basetime){
                time += 30;
            }
        }
    }
}

void main(){
    timerInit();
    interruptInit();
    while (1)
    {
        timeControl();
        carTraffic();
        personTraffic();
        lightControl();
        goStateDelay();
    }
    
}

void timerHandler() interrupt 1
{
    basetime++;
}