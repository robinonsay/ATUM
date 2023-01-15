#include "maat.h"
#include "avr/io.h"
#include "avr/interrupt.h"

#define TIMER_COMA          (6)
#define TIMER_MODE_TOGGLE   (1)
#define TIMER_MODE_CLEAR    (2)
#define TIMSK_A             (1 << 1)
#define PRESCALAR           (1024)
#define PRESCALAR_MODE_64   (5)
#define CTCMODE             (3)

static unsigned long g_ulTimeElapsed = 0;

void Maat_Init()
{
    sei();
    ptrTimer1->uiTCCRA = 0;
    ptrTimer1->uiTCCRB |= (1 << CTCMODE) | PRESCALAR_MODE_64;
    ptrTimer1->uiOCRA = CLK_FREQ / PRESCALAR;
    ptrTIMSK->uiTIMSK1 |= TIMSK_A;
}

unsigned long Maat_TimeNow()
{
    return g_ulTimeElapsed;
}

ISR(TIMER1_COMPA_vect)
{
    g_ulTimeElapsed++;
}
