#include "maat.h"
#include "avr/io.h"
#include "avr/interrupt.h"

#define SCH_MINOR_FRAME_SEC (1)
#define TIMER_COMA          (6)
#define TIMER_MODE_TOGGLE   (1)
#define TIMER_MODE_CLEAR    (2)
#define TIMSK_A             (1 << 1)
#define PRESCALAR           (1024)
#define PRESCALAR_MODE_64   (5)
#define CTCMODE             (3)

static bool_t g_bNextItemFlag = false;
static MAAT_SCH_ITEM_T*    g_SchItems;
static uint16_t            g_uiNumItems;
static bool_t g_bRunStatus = true;

int8_t Maat_InitSch(MAAT_SCH_ITEM_T schItems[], uint16_t uiNumItems)
{
    int8_t iStatus = 0;
    g_SchItems = schItems;
    g_uiNumItems = uiNumItems;
    ptrTimer1->uiTCCRA = 0;
    ptrTimer1->uiTCCRB |= (1 << CTCMODE) | PRESCALAR_MODE_64;
    ptrTimer1->uiOCRA = CLK_FREQ / PRESCALAR * SCH_MINOR_FRAME_SEC;
    ptrTIMSK->uiTIMSK1 |= TIMSK_A;
    for(uint8_t i = 0; i < uiNumItems; i++)
    {
        iStatus = g_SchItems[i].Init();
        if(iStatus < 0)
        {
            break;
        }
    }
    return iStatus;
}

void Maat_RunSch()
{
    uint16_t uiItemNum = 0;
    while(g_bRunStatus)
    {
        if(g_bNextItemFlag)
        {
            g_SchItems[uiItemNum].Main();
            g_bNextItemFlag = false;
            uiItemNum++;
            if(uiItemNum == g_uiNumItems)
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
