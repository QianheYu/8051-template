#include "uart.h"
/**
 * 做一个先进先出缓存栈buff
*/

static TypedefState Receive(TypedefUart *handler){

}

static TypedefState Transform(){

}

void callback(){

}


void UartHandlerIRQ(){
    /**
     * @function errer process.
    */
    if(){

    }
}

void SetUartMode(TypedefUART *handler){
    handler->mode;
}

/**
 * @function 
*/
TypedefState Transform_IT(TypedefUart *handler, int *pdata, int len, int timeout){
    if(!(handler->TI)){
        int Tbuff;
        Tbuff = *pdata & 0xff;
        handler->pBuff = Tbuff;
        while(handler->TI);
        handler->TI = 0;
        if(len - 8 <= 0){
            return OK;
        }
        else{
            *pdata >>= 8;
            len -= 8;
        }
    else
    {
        return WAIT;
    }
}

/**
 * @function 
*/
TypedefState Recieve_IT(TypedefUart *handler, int *pdata, int len, int timeout){
    
    if(handler->RI){
        *pdata <<= 8;
        *pdata =  *pdata & handler->Rbuff;
        handler->Rbuff;
    }
    return WAIT;
}