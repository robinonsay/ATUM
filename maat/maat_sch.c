#include "maat.h"
#include "maat_string.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define MAAT_TELEM_ID       (0x096600)
#define SCH_MINOR_FRAME_SEC 1 / 100
#define TIMER_COMA          (6)
#define TIMER_MODE_TOGGLE   (1)
#define TIMER_MODE_CLEAR    (2)
#define TIMSK_A             (1 << 1)
#define PRESCALAR           (1024)
#define PRESCALAR_MODE_64   (5)
#define CTCMODE             (3)

static MAAT_SCH_ITEM_T*     g_SchTable;
static MAAT_APP_T*          g_AppTable;
static uint16_t             g_uiSchTableLen;
static uint16_t             g_uiAppTableLen;
static bool_t               g_bNextItemFlag = false;
static bool_t               g_bRunStatus = true;
static MAAT_MSG_T           g_MaatMsg = {0};

int8_t Maat_InitSch(MAAT_SCH_ITEM_T schTable[], uint16_t uiSchTableLen, MAAT_APP_T appTable[],  uint16_t uiAppTableLen)
{
    int8_t iStatus = 0;
    iStatus = Maat_InitUART(57600);
    g_MaatMsg.hdr.ulID = MAAT_TELEM_ID;
    g_MaatMsg.hdr.type = MSG_LOG;
    g_MaatMsg.hdr.ulSize = sizeof(g_MaatMsg.data.log);
    Maat_Sprintf(g_MaatMsg.data.log, "MAAT SCHEDULER STARTING\n");
    Maat_MsgWriteUART(&g_MaatMsg);
    if(iStatus)
    {
        goto exit;
    }
    g_SchTable = schTable;
    g_AppTable = appTable;
    g_uiSchTableLen = uiSchTableLen;
    g_uiAppTableLen = uiAppTableLen;
    ptrTimer1->uiTCCRA = 0;
    ptrTimer1->uiTCCRB |= (1 << CTCMODE) | PRESCALAR_MODE_64;
    ptrTimer1->uiOCRA = CLK_FREQ / PRESCALAR * SCH_MINOR_FRAME_SEC;
    ptrTIMSK->uiTIMSK1 |= TIMSK_A;
    for(uint8_t i = 0; i < uiAppTableLen; i++)
    {
        iStatus = g_AppTable[i].Init();
        if(iStatus)
        {
            Maat_Sprintf(g_MaatMsg.data.log, "ERROR: INIT SCH ITEM %u\n", i);
            break;
        }
        Maat_Sprintf(g_MaatMsg.data.log, "INIT SCH ITEM %u SUCCESS\n", i);
    }
    Maat_MsgWriteUART(&g_MaatMsg);
exit:
    return iStatus;
}

void Maat_RunSch()
{
    uint16_t uiItemNum = 0;
    MAAT_SCH_ITEM_T* ptrSchItem = NULL;
    while(g_bRunStatus)
    {
        if(g_bNextItemFlag)
        {
            g_bNextItemFlag = false;
            ptrSchItem = &g_SchTable[uiItemNum];
            uiItemNum++;
            if(ptrSchItem->ptrApp)
            {
                ptrSchItem->ptrApp->Main();
                for(uint8_t i = 0; i < ptrSchItem->ptrApp->uiMsgTblLen; i++)
                {
                    if(ptrSchItem->ptrApp->msgTbl[i].hdr.type == MSG_TELEM)
                    {
                        ptrSchItem->ptrApp->msgTbl[i].hdr.ulSize = sizeof(ptrSchItem->ptrApp->msgTbl[i].data.telem);
                    }
                    else if(ptrSchItem->ptrApp->msgTbl[i].hdr.type == MSG_LOG)
                    {
                        ptrSchItem->ptrApp->msgTbl[i].hdr.ulSize = sizeof(ptrSchItem->ptrApp->msgTbl[i].data.log);
                    }
                    Maat_MsgWriteUART(&ptrSchItem->ptrApp->msgTbl[i]);
                }
            }
            if(uiItemNum == g_uiSchTableLen)
            {
                uiItemNum = 0;
            }
        }
    }
}

ISR(TIMER1_COMPA_vect)
{
    g_bNextItemFlag = true;
}
