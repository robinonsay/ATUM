#ifndef MAAT_H
#define MAAT_H

#define CLK_PERIOD    (16)

#include "maat_mem.h"
#include "maat_types.h"

void Maat_Delay(uint8_t uiUSecs);
void Maat_CreateEventTimer(uint8_t uiUSecs, void (*fEventCallback)());

#endif /* MAAT_H */
