/**
 * @author YuQianhe
由于周期是10ms，占空比步进是10%。故使用定时器1定时1ms，定义dut变量用于控制占空比，
通过每次定时器中断函数中变量i自增一次与dut比较决定是高电平还是低电平，以此来控制占空比的大小
通过P1口接的开关来控制dut的值。
period变量用于控制波形的周期，amplictude变量用于控制波形的幅值，他们分别从ADC0809的第一和第二通道读出
ADC0809使用外部中断0来执行读取操作。
*/


#include "reg52.h"

typedef unsigned char uchar;
typedef unsigned int uint;

uchar dut = 1;	//控制占空比
uchar amplitude;
uchar period = 10;
sbit CH = P1^5;
sbit OE = P1^6;
sbit ST = P1^7;

void delay(uint time)
{
	while(time--);
}


/**
初始化中断
*/
void InterruptInit()
{
	PX0 = 0;
	PT1 = 1;
	EX0 = 1;
	ET1 = 1;	//开启定时器1中断
	EA = 1;		//开启总中断
}

/**
初始化定时器
0xFC18转换为十进制是64536,即定时1ms.
*/
void TimerInit()
{
	TMOD |= 0x10;	//设置定时器1模式
	TH1 = 0xFC;			//设置定时器1的高8位
	TL1 = 0x18;			//设置定时器1的低8位
	TR1 = 1;			//开启定时器1
}

uchar keyScan()
{
	static uchar temp = 0;
	if((P1&0x0f) != temp)
	{
		delay(100);
		if((P1&0x0f) != temp)
		{
			temp = 0xf0|(P1&0x0f);
			return ~temp;
		}
	}
	return ~temp;
}

void main()
{
	CH = 0;
	IT0 = 1;	//设置外部中断下降沿触发
	TimerInit();
	InterruptInit();
	while(1)
	{
		dut = keyScan();
		ST = 0;
		ST = 1;
		ST = 0;
		delay(5000);
	}
}

/**
定时器1中断
*/
void TimerHandler() interrupt 3
{
	static uchar i = 0;
	TH1 = 0xFC;
	TL1 = 0x18;
	if(i >= dut*period/0.1){
		P2 = 0x00;
	}
	else
	{
		P2 = amplitude;
	}
	i = (++i)%period;
}
/**
 * 外部中断0
 * 读取ADC芯片的转换结果
 * ch为0时读周期，为1时读幅值
*/
void handler() interrupt 0
{
	uchar temp;
	static bit ch = 0;
	OE = 1;
	temp = P0;
	OE = 0;
	if(ch)
	{
		amplitude = temp;
	}
	else
	{
		period = temp;
	}
	ch = ~ch;
	CH = ch;
}