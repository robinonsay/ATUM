#include "maat.h"
#include "maat_string.h"
#include "avr/io.h"
#include "avr/interrupt.h"

#define SCH_MINOR_FRAME_SEC 1 / 100
#define TIMER_COMA          (6)
#define TIMER_MODE_TOGGLE   (1)
#define TIMER_MODE_CLEAR    (2)
#define TIMSK_A             (1 << 1)
#define PRESCALAR           (1024)
#define PRESCALAR_MODE_64   (5)
#define CTCMODE             (3)

static MAAT_SCH_ITEM_T*     g_SchItems;
static uint16_t             g_uiNumItems;
static bool_t               g_bNextItemFlag = false;
static bool_t               g_bRunStatus = true;
static char                 g_strLog[APP_LOG_SIZE] = {0};
static unsigned long        g_ulMET = 0;

int8_t Maat_InitSch(MAAT_SCH_ITEM_T schItems[], uint16_t uiNumItems)
{
    int8_t iStatus = 0;
    iStatus = Maat_InitUART(57600);
    Maat_StrWriteUART("MAAT SCHEDULER STARTING\n");
    if(iStatus)
    {
        goto exit;
    }
    g_SchItems = schItems;
    g_uiNumItems = uiNumItems;
    ptrTimer1->uiTCCRA = 0;
    ptrTimer1->uiTCCRB |= (1 << CTCMODE) | PRESCALAR_MODE_64;
    ptrTimer1->uiOCRA = CLK_FREQ / PRESCALAR * SCH_MINOR_FRAME_SEC;
    ptrTIMSK->uiTIMSK1 |= TIMSK_A;
    for(uint8_t i = 0; i < uiNumItems; i++)
    {
        if(g_SchItems[i].Init)
        {
            iStatus = g_SchItems[i].Init(g_strLog);
            if(iStatus)
            {
                Maat_Sprintf(g_strLog, "ERROR: INIT SCH ITEM %u\n", i);
                break;
            }
            Maat_Sprintf(g_strLog, "INIT SCH ITEM %u SUCCESS\n", i);
        }
    }
    Maat_StrWriteUART(g_strLog);
    g_strLog[0] = 0;
exit:
    return iStatus;
}

void Maat_RunSch()
{
    uint16_t uiItemNum = 0;
    MAAT_SCH_ITEM_T* schItemCurrent = NULL;
    char strMET[32];
    while(g_bRunStatus)
    {
        if(g_bNextItemFlag)
        {
            schItemCurrent = &g_SchItems[uiItemNum];
            if(schItemCurrent->Main)
            {
                schItemCurrent->Main(g_strLog);
                Maat_Sprintf(strMET, "MET: %u\n", g_ulMET);
                Maat_Strcat(g_strLog, strMET);
                Maat_StrWriteUART(g_strLog);
                g_strLog[0] = 0;
            }
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
    g_ulMET++;
    g_bNextItemFlag = true;
}
