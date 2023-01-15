#ifndef ATUM_LED_TEST_H
#define ATUM_LED_TEST_H

#include "maat.h"
#include "maat_string.h"

int32_t Atum_LEDInit(char log[]);

int32_t Atum_LEDMain(char log[]);

#endif

#ifdef ATUM_LED_TEST
#undef ATUM_LED_TEST
#define LED_PIN (5)
unsigned long g_ulIter = 0;

int32_t Atum_LEDInit(char log[])
{
    ptrB->ddr |= (1 << LED_PIN);
    ptrB->port &= ~(1 << LED_PIN);
    return 0;
}

int32_t Atum_LEDMain(char log[])
{
    Maat_Sprintf(log, "ATUM_LED_TEST: ITERATION NO. %u\n", g_ulIter);
    ptrB->pin |= 1 << LED_PIN;
    g_ulIter++;
    return 0;
}
#endif
