#include "maat.h"
#include "maat_string.h"
#include "avr/io.h"
#include "avr/interrupt.h"

#define LOG_SIZE    (256)

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
static char                 g_strLog[LOG_SIZE] = {0};

int8_t Maat_InitSch(MAAT_SCH_ITEM_T schTable[], uint16_t uiSchTableLen, MAAT_APP_T appTable[],  uint16_t uiAppTableLen)
{
    int8_t iStatus = 0;
    iStatus = Maat_InitUART(57600);
    Maat_StrWriteUART("MAAT SCHEDULER STARTING\n");
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
        iStatus = g_AppTable[i].Init(g_strLog);
        if(iStatus)
        {
            Maat_Sprintf(g_strLog, "ERROR: INIT SCH ITEM %u\n", i);
            break;
        }
        Maat_Sprintf(g_strLog, "INIT SCH ITEM %u SUCCESS\n", i);
    }
    Maat_StrWriteUART(g_strLog);
    g_strLog[0] = 0;
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
                ptrSchItem->ptrApp->Main(g_strLog);
                Maat_WriteUART((char*) ptrSchItem->ptrApp->telemTbl,
                                sizeof(MAAT_TELEM_T) * ptrSchItem->ptrApp->uiTelemTblLen);
                Maat_StrWriteUART(g_strLog);
                g_strLog[0] = 0;
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
