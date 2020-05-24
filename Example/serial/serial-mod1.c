#include "REG52.h"
#define WORD P2

code unsigned char words[10] = {0xc0,0xf6,0xa4,0xb0,0x98,0x92,0x82,0xf8,0x80,0x90};  //use 7SEG-COM-ANODE

void serialInit(){

}

void keyScan(){

}

void show(int tab){
    WORD = words[tab];
}

void main(){

    while (1)
    {
        /* code */
    }
    
}

void serialHandler() interrupt 4
{
    if(mode){
        show(i++);
    }
}
