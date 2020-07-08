#ifndef __DS18B20__

#define __DS18B20__

/**ROM Commond Code*/
#define RDROM 0x33
#define MAROM 0x55
#define SKROM 0xCC
#define SRROM 0xF0
#define AMSR 0xEC

/**Scratchpad Commond Code*/
#define WDSC 0x4E
#define RDSC 0xBE
#define CPSC 0x48
#define CVTP 0x44
#define REPR 0xB8
#define RDPS 0xB4



void Reset();
void write(unsigned char dat);
unsigned char read();
unsigned int getTemperature();

#endif