/**
����������10ms��ռ�ձȲ�����10%����ʹ�ö�ʱ��1��ʱ1ms������dut�������ڿ���ռ�ձȣ�
ͨ��ÿ�ζ�ʱ���жϺ����б���i����һ����dut�ȽϾ����Ǹߵ�ƽ���ǵ͵�ƽ���Դ�������ռ�ձȵĴ�С
ͨ��P1�ڽӵĿ���������dut��ֵ��

һ��Ϊû����ɵĲ���
ʹ��adc��ȡĿ���ֵ��С����ֵ��amplitude������P2�����
��adc��ȡ����ֵʹ���ⲿ�ж�0����
*/


#include "reg52.h"

typedef unsigned char uchar;
typedef unsigned int uint;

uchar dut = 1;	//����ռ�ձ�
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
��ʼ���ж�
*/
void InterruptInit()
{
	PX0 = 0;
	PT1 = 1;
	EX0 = 1;
	ET1 = 1;	//������ʱ��1�ж�
	EA = 1;		//�������ж�
}

/**
��ʼ����ʱ��
0xFC18ת��Ϊʮ������64536,����ʱ1ms.
*/
void TimerInit()
{
	TMOD |= 0x10;	//���ö�ʱ��1ģʽ
	TH1 = 0xFC;			//���ö�ʱ��1�ĸ�8λ
	TL1 = 0x18;			//���ö�ʱ��1�ĵ�8λ
	TR1 = 1;			//������ʱ��1
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
	IT0 = 1;	//�����ⲿ�ж��½��ش���
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
��ʱ��1�ж�
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