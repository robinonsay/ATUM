#ifndef MAAT_H
#define MAAT_H

#define CLK_FREQ    (16000000UL)

#define MAA_DEFAULT_BAUD_RATE (9600)

#include "maat_mem.h"
#include "maat_types.h"
#include "maat_msgs.h"


#define MAAT_TELEM_ID       (0x96653400)
#define MAAT_CMD_READY      (0xFF)
#define NULL    ((void *) 0)
#define true    (1)
#define false   (0)

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

void Maat_InitUART(unsigned long uiBaudRate);
int8_t Maat_WriteUART(char* ptrBuff, size_t sBuffSize);
int8_t Maat_ReadUART(char* ptrBuff, size_t sBuffSize);
int8_t Maat_StrWriteUART(char* str);
int8_t Maat_StrReadStrUART(char* str, size_t sBuffSize);
int8_t Maat_MsgWriteUART(MAAT_MSG_T* msg);
int8_t Maat_MsgReadUART(MAAT_MSG_T* msg);

#endif /* MAAT_H */
