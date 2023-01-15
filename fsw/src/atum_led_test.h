#ifndef ATUM_LED_TEST_H
#define ATUM_LED_TEST_H

#include "maat.h"
#include "maat_string.h"

int32_t Atum_LEDInit(char log[]);

int32_t Atum_LEDMain(char log[]);

#define ATUM_LED_TELEM_LEN  (1)

MAAT_TELEM_T g_AtumLEDTelemTbl[ATUM_LED_TELEM_LEN];

#endif

#ifdef ATUM_LED_TEST
#undef ATUM_LED_TEST
#define LED_PIN (5)
unsigned long g_ulIter = 0;


int32_t Atum_LEDInit(char log[])
{
    g_AtumLEDTelemTbl[0].type = TELEM_LONG;
    ptrB->ddr |= (1 << LED_PIN);
    ptrB->port &= ~(1 << LED_PIN);
    return 0;
}

int32_t Atum_LEDMain(char log[])
{
    ptrB->pin |= 1 << LED_PIN;
    g_AtumLEDTelemTbl[0].data.lLong = g_ulIter;
    g_ulIter++;
    return 0;
}
#endif
