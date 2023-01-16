#include "maat.h"
#include "avr/io.h"
#include "avr/interrupt.h"

void Maat_Init()
{
    Maat_InitUART(57600);
    sei();
}
