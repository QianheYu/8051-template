#define FAIL 0x80;

#define Enable_Recieve(UARTHANDLER) (UARTHANDLER->ren = 1)
#define Disable_Recieve(UARTHANDLER) (UARTHANDLER->ren = 0)

/*接收缓存栈数据结构*/
typedef static struct Rbuff
{
    char buff;
    TypedefRbuff *next;
} TypedefRbuff;

/*发送缓存栈数据结构*/
typedef static struct Tbuff
{
    char buff;
    TypedefTbuff *next;
} TypedefTbuff;

/*UART状态枚举*/
typedef int enum state{
    Fail = -1,
    WAIT = 0,
    OK = 1
}TypedefState;

/*UART接口配置数据结构*/
typedef struct
{
    unsigned char mode;
    unsigned char time;
    bit Dfrequncy;
    char *buff;
    sbit ren;
    bit TI;
    bit RI;
}TypedefUart;


void Transform_IT(TypedefUart *handler, int *pdata, int len, int timeout);
