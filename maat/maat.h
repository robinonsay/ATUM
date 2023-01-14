#ifndef MAAT_H
#define MAAT_H

#define CLK_FREQ    (16000000UL)
#define CLK_FREQ_MHZ    (16)

#include "maat_mem.h"

typedef enum EVENT_TIMER_8_TAG
{
    EVENT_TIMER_A=0,
    EVENT_TIMER_B=1
}EVENT_TIMER_8_T;

void Maat_Delay(uint8_t ulMicros);
int Maat_InitEventTimer(unsigned long ulMicros, void (*fEventCallback)());

#endif /* MAAT_H */
