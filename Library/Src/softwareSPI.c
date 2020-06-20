#include "reg52.h"


typedef  unsigned int u16;
typedef  unsigned char u8;

sbit KEY1 = P3^0;
sbit KEY2 = P3^1;

void delay(u16 time){
    while(time--);
}

void writeByte(){
    u8 i;
    sck = 0;
    for(i = 0; i < 8; i++){
        si = (bit)(dat&0x80);
        sck = 0;
        sck = 1;
        dat <<= 1;
    }
}

u8 readByte(){
    u8 i;
    u8 dat = 0x00;
    sck = 1;
    fot(i = 0; i < 8; i++){
        sck = 1;
        sck = 0;
        dat <<= 1;
        dat |= (u8)sc;
    }
    return dat;
}

void writeState(u8 dat){
    cs = 0;
    writeByte(WREN);
    cs = 1;
    cs = 0;
    writeByte(WRSR);
    writeByte(dat);
    cs = 1;
}

/**
使用递归生成片选引脚值
*/
int chipselect(u8 chip, u8 maxpin)
{
    if(!(chip/maxpin))
    {
        if((maxpin >> 1) > 0)
        {
           return chipselect(chip, (maxpin>>1)); 
        }
        else
        {
            return -1;
        }
    }
    return maxpin;
}


#ifdef __DEBUG__
void writeData(u8 addr, u8 chipselect, u8 dat){
    sck = 0;
    P1 &= chipselect;
    // cs = 0;
    writeByte(WREN);
    cs = 1;
    cs = 0;
    writeByte(WRUTE);
    writeByte(addr);
    writeByte(dat);
    cs = 1;
    sck = 0;
}
#else
void writeData(u8 addr, u8 chipselect, u8 dat){
    sck = 0;
    cs = 0;
    writeByte(WREN);
    cs = 1;
    cs = 0;
    writeByte(WRUTE);
    writeByte(addr);
    writeByte(dat);
    cs = 1;
    sck = 0;
}
#endif


u8 readData(u8 addr){
    u8 dat;
    sck = 0;
    cs = 0;
    writeByte(REND);
    writeByte(addr);
    dat = readByte();
    cs = 1;
    sck = 0;
    return dat;
}

void key(){
    if(!KEY1)
    {
        delay();
        if(!KEY1)
        {
            writeData();
            while(!KEY1);
            P2 = readData();
        }
    }
    if(!KEY2)
    {
        delay();
        if(!KEY2)
        {
            writeData();
            while(!KEY2);
            P2 = readData();
        }
    
    }
}