#include "atum.h"
#include "maat.h"
#define LED_PIN (5)

void init(void);
void sleep(unsigned long usecs);

void init(void)
{
    ptrB->ddr |= (1 << LED_PIN);
    ptrB->port &= ~(1 << LED_PIN);
}

int main(void)
{
    init();
    while(1)
    {
        ptrB->pin |= (1 << LED_PIN);
        sleep(500000);
    }   
    return 0;
}

void sleep(unsigned long usecs)
{
    unsigned long i = 0;
    while(i < usecs * CLK_PERIOD)
    {
        i+=10;
    }
}
