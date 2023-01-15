#ifndef MAAT_H
#define MAAT_H

#define CLK_FREQ    (16000000UL)

#define MAA_DEFAULT_BAUD_RATE (9600)

#include "maat_mem.h"

#define true    (1)
#define false   (0)

typedef unsigned long long time_t;
typedef unsigned long size_t;
typedef unsigned char bool_t;

typedef struct MAAT_SCH_ITEM_TAG
{
    int32_t (*Init)();
    int32_t (*Main)();
} MAAT_SCH_ITEM_T;


void Maat_Init();

int8_t Maat_InitSch(MAAT_SCH_ITEM_T schItems[], uint16_t uiNumItems);
void Maat_RunSch();

int8_t Maat_InitUART(unsigned long uiBaudRate);
int8_t Maat_WriteUART(char* ptrBuff, size_t sBuffSize);
int8_t Maat_ReadUART(char* ptrBuff, size_t sBuffSize);
int8_t Maat_StrWriteUART(char* str);
int8_t Maat_StrReadStrUART(char* str, size_t sBuffSize);

#endif /* MAAT_H */
