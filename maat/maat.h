#ifndef MAAT_H
#define MAAT_H

#define CLK_FREQ    (16000000UL)
#define CLK_FREQ_MHZ    (16)

#include "maat_mem.h"
#include <avr/common.h>

typedef unsigned long long time_t;

void Maat_Init();
int Maat_InitTime(uint16_t uiTicksMicros);
time_t Maat_TimeNow();
int Maat_InitEventTimer(unsigned long ulMicros, void (*fEventCallback)());

#endif /* MAAT_H */
