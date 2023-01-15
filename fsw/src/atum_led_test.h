#ifndef ATUM_LED_TEST_H
#define ATUM_LED_TEST_H

#include "maat.h"

int32_t Atum_LEDInit();

int32_t Atum_LEDMain();

#endif

#ifdef ATUM_LED_TEST
#undef ATUM_LED_TEST
#define LED_PIN (5)
int32_t Atum_LEDInit()
{
    Maat_InitUART(57600);
    ptrB->ddr |= (1 << LED_PIN);
    ptrB->port &= ~(1 << LED_PIN);
    return 0;
}

int32_t Atum_LEDMain()
{
    Maat_StrWriteUART("Hello from scheduled task\n");
    ptrB->pin |= 1 << LED_PIN;
    return 0;
}
#endif
