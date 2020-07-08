#ifndef __LCD1602__
#define __LCD1602__

enum MODE
{
    COM = 0,
    DATA = 1
};

void Lcdwrite(unsigned char dat, bit mode);
unsigned char Lcdread(bit mode);
void LcdInit();
void show(char *string, unsigned char position);
#endif