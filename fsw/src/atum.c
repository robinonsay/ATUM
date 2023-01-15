#include "maat.h"

#include "atum.h"
#define ATUM_LED_TEST
#include "atum_led_test.h"

MAAT_SCH_ITEM_T g_schItemTable[] = 
{
    {
        .Init = Atum_LEDInit,
        .Main = Atum_LEDMain,
    }
};

uint16_t g_uiNumItems = sizeof(g_schItemTable) / sizeof(g_schItemTable[0]);

int main(void)
{
    Maat_Init();
    Maat_InitSch(g_schItemTable, g_uiNumItems);
    Maat_RunSch();
    return 0;
}
