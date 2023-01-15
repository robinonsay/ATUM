#ifndef MAAT_H
#define MAAT_H

#define CLK_FREQ    (16000000UL)
#define CLK_FREQ_MHZ    (16)

#define MAAT_BAUD_RATE (9600)

#include "maat_mem.h"
#include <avr/common.h>

typedef unsigned long long time_t;
typedef unsigned long size_t;

void Maat_Init();

unsigned long Maat_TimeNow();

int8_t Maat_InitEventTimer(unsigned long ulMicros, void (*fEventCallback)());

int8_t Maat_InitUART(uint32_t uiBaudRate);
int8_t Maat_WriteUART(char* ptrBuff, size_t sBuffSize);
int8_t Maat_ReadUART(char* ptrBuff, size_t sBuffSize);
int8_t Maat_StrWriteUART(char* str);
int8_t Maat_StrReadStrUART(char* str, size_t sBuffSize);

#endif /* MAAT_H */
