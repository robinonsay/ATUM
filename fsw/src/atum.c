#include "atum.h"
#include "maat.h"
#define LED_PIN (5)

static void init(void);
static void LEDCallback();

static void init(void)
{
    ptrB->ddr |= (1 << LED_PIN);
    ptrB->port &= ~(1 << LED_PIN);
}

int main(void)
{
    init();
    Maat_Init();
    Maat_InitTime(1000);
    Maat_InitEventTimer(1000000, &LEDCallback);
    while(1)
    {
    }   
    return 0;
}

static void LEDCallback()
{
    if(Maat_TimeNow() > 10000000ULL)
    {
        ptrB->pin |= (1 << LED_PIN);
    }
}
