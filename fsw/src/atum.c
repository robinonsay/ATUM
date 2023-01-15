#include "atum.h"
#include "maat.h"
#define LED_PIN (5)

static void init(void);

static void init(void)
{
    ptrB->ddr |= (1 << LED_PIN);
    ptrB->port &= ~(1 << LED_PIN);
}

int main(void)
{
    init();
    Maat_Init();
    Maat_InitUART(57600);
    unsigned long ulLastTime = 0;
    unsigned long ulNow = 0;
    while(1)
    {
        ulNow = Maat_TimeNow();
        if(ulNow - ulLastTime >= 1)
        {
            ulLastTime = ulNow;
            Maat_WriteUART((char*) &ulNow, sizeof(ulNow));
            Maat_StrWriteUART("\n");
            ptrB->pin |= 1 << LED_PIN;
        }
    }   
    return 0;
}
