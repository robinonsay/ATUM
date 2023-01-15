#ifndef MAAT_H
#define MAAT_H

#define CLK_FREQ    (16000000UL)

#define MAA_DEFAULT_BAUD_RATE (9600)

#include "maat_mem.h"

#define NULL    ((void *) 0)
#define true    (1)
#define false   (0)
#define TELEM_RAW_SIZE  (32)
#define NUM_TELEM_ITEMS (8)

typedef unsigned long long time_t;
typedef unsigned long size_t;
typedef unsigned char bool_t;

typedef enum MAAT_TELEM_TYPE_TAG
{
    TELEM_FLOAT= 0,
    TELEM_DOUBLE= 1,
    TELEM_INT= 2,
    TELEM_LONG= 3,
    TELEM_LLONG= 4,
    TELEM_RAW=5
} MAAT_TELEM_TYPE_T;

typedef union MAAT_TELEM_DATA_TAG
{
    float       fFloat;
    double      dDouble;
    int         iInt;
    long        lLong;
    long long   llLongLong;
    char        raw[TELEM_RAW_SIZE];
} MAAT_TELEM_DATA_T;

typedef struct MAAT_TELEM_TAG
{
    MAAT_TELEM_TYPE_T   type;
    MAAT_TELEM_DATA_T   data;
} MAAT_TELEM_T;

typedef struct MAAT_APP_TAG
{
    int32_t         (*Init)(char log[]);
    int32_t         (*Main)();
    uint8_t         uiTelemTblLen;
    MAAT_TELEM_T*   telemTbl;
} MAAT_APP_T;

typedef struct MAAT_SCH_ITEM_TAG
{
    MAAT_APP_T* ptrApp;
} MAAT_SCH_ITEM_T;


void Maat_Init();

int8_t Maat_InitSch(MAAT_SCH_ITEM_T schTable[], uint16_t uiSchTableLen, MAAT_APP_T appTable[],  uint16_t uiAppTableLen);
void Maat_RunSch();

int8_t Maat_InitUART(unsigned long uiBaudRate);
int8_t Maat_WriteUART(char* ptrBuff, size_t sBuffSize);
int8_t Maat_ReadUART(char* ptrBuff, size_t sBuffSize);
int8_t Maat_StrWriteUART(char* str);
int8_t Maat_StrReadStrUART(char* str, size_t sBuffSize);

#endif /* MAAT_H */
