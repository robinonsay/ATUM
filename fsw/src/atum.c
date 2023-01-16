#include "maat.h"

#include "atum.h"
#define ATUM_LED_TEST
#include "atum_led_test.h"

MAAT_APP_T g_AppTable[] = 
{
    {
        .Init = Atum_LEDInit,
        .Main = Atum_LEDMain,
        .uiMsgTblLen = ATUM_LED_MSG_LEN,
        .msgTbl = g_AtumLEDMsgTbl
    }
};

MAAT_SCH_ITEM_T g_SchTable[SCH_SLOTS] = 
{
    {
        .ptrApp = &g_AppTable[0]
    }
};

uint16_t g_uiSchTableLen = sizeof(g_SchTable) / sizeof(g_SchTable[0]);
uint16_t g_uiAppTableLen = sizeof(g_AppTable) / sizeof(g_AppTable[0]);

int main(void)
{
    Maat_Init();
    Maat_InitUART(0);
    Maat_InitSch(g_SchTable, g_uiSchTableLen, g_AppTable, g_uiAppTableLen);
    Maat_RunSch();
    return 0;
}
