#include "reg52.h"
#include "absacc.h"

//#define __USEINTERRUPT__

typedef unsigned char u8;
typedef unsigned int u16;

#define ADC XBYTE[0x8000]
#define WORD XBYTE[0xa000]
#define POSITION XBYTE[0xb000]

sbit EOC = P3^2;
code u8 wordTab[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,     //0-9
                    0x77,0x7c,0x39,0x5e,0x79,0x71,0x3d,0x76,0x19,0x0d,0x72,0x38,0x55,0x54,      //A-N
                    0x5d,0x73,0x67,0x50,0x6d,0x78,0x3e,0x1c,0x6a,0x1d,0x6e,0x49,0x40};
code u8 tabIndex[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
u8 number[8] = {0x00,0x00,0x00,0x24,0x24,0x00,0x00,0x00};

void delay(u16 time){
    while(time--);
}

void show(u8 word, u8 port){
    WORD = word;
    POSITION = port;
    delay(100);
    WORD = 0xff;
}

void dynamicShow(u8 buffer[]){
    int i;
    for(i = 0; i < 8; i++){
        show(~wordTab[buffer[i]], tabIndex[i]);	
    }
}

static int adc_data = 0;
static bit ch = 0;

void main(){
	
#ifdef __USEINTERRUPT__
	EA = 1;
	EX0 = 1;
	IT0 = 1;
#endif
	
    ADC = (u8)ch;
    while(1){
		
#ifndef __USEINTERRUPT__
		if(!EOC){
			adc_data = ADC;
			if(ch){
				number[5] = adc_data/100;
				number[6] = (adc_data%100)/10;
				number[7] = adc_data%10;
			}
			else{
				number[0] = adc_data/100;
				number[1] = (adc_data%100)/10;
				number[2] = adc_data%10;
			}
			ch = ~ch;
			ADC = (u8)ch;
        }
#endif
		
		dynamicShow(number);
    }
}

#ifdef __USEINTERRUPT__
void Handler() interrupt 0
{
	adc_data = ADC;
    number[5] = adc_data/100;
    number[6] = (adc_data%100)/10;
    number[7] = adc_data%10;
	ADC = 1;
}
#endif
