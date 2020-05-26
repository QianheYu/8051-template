#include "uart.h"

void uart_handler() interrupt 4
{
    UartHandlerIRQ();
}
