#ifndef MAAT_H
#define MAAT_H

#define CLK_FREQ    (16000000UL)

#define MAA_DEFAULT_BAUD_RATE (9600)

#include "maat_mem.h"
#include "maat_types.h"

#define NULL    ((void *) 0)
#define true    (1)
#define false   (0)
#define LOG_SIZE        (256)
#define TELEM_RAW_SIZE  (64)
#define NUM_TELEM_ITEMS (8)

typedef enum MAAT_TELEM_TYPE_TAG
{
    TELEM_FLOAT= 0,
    TELEM_DOUBLE= 1,
    TELEM_INT= 2,
    TELEM_UINT= 3,
    TELEM_LONG= 4,
    TELEM_ULONG= 5,
    TELEM_LLONG= 6,
    TELEM_ULLONG= 7,
    TELEM_RAW=8
} MAAT_TELEM_TYPE_T;

typedef enum MAAT_MSG_TYPE_TAG
{
    MSG_TELEM = 0,
    MSG_LOG = 1
} MAAT_MSG_TYPE_T;

typedef union MAAT_TELEM_DATA_TAG
{
    float               fFloat;
    double              dDouble;
    int                 iInt;
    unsigned int        uiInt;
    long                lLong;
    unsigned long       ulLong;
    long long           llLongLong;
    unsigned long long  ullLongLong;
    char                raw[TELEM_RAW_SIZE];
} MAAT_TELEM_DATA_T;

typedef struct MAAT_TELEM_HDR_TAG
{
    unsigned long       ulID;
    unsigned long       ulSize;
    MAAT_MSG_TYPE_T     type;

} MAAT_TELEM_HDR_T;

typedef struct MAAT_TELEM_TAG
{
    MAAT_TELEM_TYPE_T   type;
    MAAT_TELEM_DATA_T   data;
} MAAT_TELEM_T;

typedef struct MAAT_MSG_TAG
{
    MAAT_TELEM_HDR_T    hdr;
    union
    {
        MAAT_TELEM_T    telem;
        char            log[LOG_SIZE];
    } data;
    uint16_t            crc;
} MAAT_MSG_T;

typedef struct MAAT_APP_TAG
{
    int32_t         (*Init)();
    int32_t         (*Main)();
    uint8_t         uiMsgTblLen;
    MAAT_MSG_T*     msgTbl;
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
int8_t Maat_MsgWriteUART(MAAT_MSG_T* msg);
int8_t Maat_MsgReadUART(MAAT_MSG_T* msg);

#endif /* MAAT_H */
