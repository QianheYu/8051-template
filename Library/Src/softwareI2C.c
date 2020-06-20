#include "reg52.h"
#define BUFF_LENGTH 10


typedef unsigned char u8;
typedef unsigned int u16;

sbit KEY1 = P1^0;
sbit KEY2 = P1^1;
code u8 wordTab[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
sbit scl1 = P1^2;
sbit sda1 = P1^3;

typedef enum state
{
	SUCCESS,
	FAIL,
} TypedefState;

typedef struct I2Cconfig
{
	u8 scl;
	u8 sda;
	u8 txbuff[BUFF_LENGTH];
	u8 rxbuff[BUFF_LENGTH];
	u8 txbuffIndex;
	u8 rxbuffIndex;
} TypedefI2C;

TypedefI2C i2cport1;

void delay(unsigned int time){
	while(time--);
}

static void start (TypedefI2C *handler)
{
    handler->sda = 1;
    delay(10);
    handler->scl = 1;
    delay(10);
    handler->scl = 0;
    delay(10);
    handler->sda = 0;
    delay(10);
}

static void stop (TypedefI2C *handler)
{
    handler->sda = 0;
    delay(10);
    handler->scl = 1;
    delay(10);
    handler->sda = 1;
    delay(10);
}

/**
transimt a bite data to stave
*/
u8 transmit (TypedefI2C *handler, u8 *pointdata, unsigned int timeout){
    int i = 8;
    do {
        handler->sda = *pointdata;
        delay(10);
        handler->scl = 1;
        delay(10);
        handler->scl = 0;
        delay(10);
        i--;
    } while (i > 0);
    handler->sda = 1;
    handler->scl = 1;
    while (handler->sda) {
        timeout--;
        if (!timeout){
            handler->scl = 0;
            delay(10);
            return 0;
        }
    }
    handler->scl = 0;
    delay(10);
    return 1;
}

/**
reseive a bite data from slave
*/
u8 receive (TypedefI2C *handler, u8 *pointdata, unsigned int timeout)
{
    u8 temp;
    int i = 8;
    handler->sda = 1;
    delay(10);
    do {
        handler->scl = 1;
        delay(10);
        temp |= handler->sda;
        temp <<= 1;
        delay(10);
        handler->scl = 0;
        delay(10);
        i--;
    } while (i > 0);
    *pointdata = temp;
    return 1;
}

/**
send the data that in TXbuff to slave
*/
void Send(TypedefI2C *handler, u8 address, unsigned int len,unsigned int timeout)
{
    int i = 0;
	address <<= 1;
	start(handler);
    transmit(handler, &address, timeout);
    for(i = 0; i < len; i++){
		if(!transmit(handler, &(handler->txbuff[i]), timeout))
		{
			return;
		}
    }
    stop(handler);
    return;
}

/**
get data from slave
*/
void requestFrom(TypedefI2C *handler, u8 address, u8 iaddress, unsigned int isize, unsigned int len, unsigned int timeout)
{
    int i = 0;
	u8 temp;
	address = address<<1 | 1;
	start(handler);
    transmit(handler, &address, timeout);//send the hardwire address
	while(isize-- > 0){
		u8 temp =  iaddress >> (isize*8);
		transmit(handler, &temp, timeout);//send iaddress to destination before receiveing
	}
	
	while(len){
		if(len > BUFF_LENGTH){
			return;
		}
	}
    for(i = len; i > 0; i--)
    {
        if(receive(handler, &temp, timeout)) {//receive data to memory in variable
             handler->rxbuff[i] = temp;
        }
    }
    stop(handler);
}
/**
Write data to TXbuff
*/
void Write(TypedefI2C *handler, u8 wdata){
	if(handler->txbuffIndex < BUFF_LENGTH){
		handler->txbuff[handler->txbuffIndex] = wdata;
		handler->txbuffIndex++;
	}
	else
	{
		handler->txbuffIndex = 0;
	}
}

/**
Read data from RXbuff
*/
int Read(TypedefI2C *handler){
	int value = -1;
	if(handler->rxbuffIndex < BUFF_LENGTH){
		value = handler->rxbuff[handler->rxbuffIndex];
		handler->rxbuffIndex++;
	}
	else
	{
		handler->rxbuffIndex = 0;
	}
	return value;
}

void show(u8 word){
	P2 = wordTab[word];
}

void main(){
	u8 count = 0;	
	while(1){
		if(!KEY1){
			if(!KEY1){
				count++;
				while(KEY1);
			}
		}
		if(!KEY2){
			if(!KEY2){
				Write(&i2cport1, 0x01);
				Write(&i2cport1, count);
				Send(&i2cport1, 0x28, 2, 100);
				while(KEY2){
					requestFrom(&i2cport1, 0x28, 0x01, 1, 1, 100);
					show((u8)(Read()));
				}
			}
		}
	}
}