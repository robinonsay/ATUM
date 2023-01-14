#include "atum.h"
#include "maat.h"
#define LED_PIN (5)

void init(void);
void LEDCallback();

void init(void)
{
    ptrB->ddr |= (1 << LED_PIN);
    ptrB->port &= ~(1 << LED_PIN);
}

int main(void)
{
    init();
    Maat_InitEventTimer(500000, &LEDCallback);
    while(1)
    {
    }   
    return 0;
}

void LEDCallback()
{
    ptrB->pin |= (1 << LED_PIN);
}
