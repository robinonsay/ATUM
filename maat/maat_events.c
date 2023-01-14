#include "maat.h"
#include "avr/io.h"
#include "avr/interrupt.h"

static unsigned long g_ulEventCeil = 1;
static unsigned long g_ulEventTimerTicks = 0;
static const uint16_t g_uiTIMER_PRESCALERS[] = {1, 8, 64, 256, 1024};
static void NoOpISR();
static void (*g_EventTimerCallback)() = &NoOpISR;

#define MAX_MICROS          (16320)
#define TIMER_COMA          (6)
#define TIMER_MODE_TOGGLE   (1)
#define TIMER_MODE_CLEAR    (2)
#define TIMSK_A             (2)
#define TIFLG_A             (2)


int Maat_InitEventTimer(unsigned long ulMicros, void (*fEventCallback)())
{
    int iStatus = -1;
    unsigned long ulTimerClkFreq = 0;
    unsigned long ulCnts = 0;
    unsigned long ulScaledMicros = ulMicros;
    g_ulEventCeil = 1;
    while(ulScaledMicros > MAX_MICROS)
    {
        g_ulEventCeil++;
        while(ulMicros % g_ulEventCeil != 0)
        {
            g_ulEventCeil++;
        }
        ulScaledMicros = ulMicros / g_ulEventCeil;
    }
    for(uint8_t i = 0; i < 5 && ulScaledMicros > 0; i++)
    {
        ulTimerClkFreq = CLK_FREQ / g_uiTIMER_PRESCALERS[i];

        ulCnts = ulScaledMicros * ulTimerClkFreq / 1000000UL;
        if(ulCnts < 0x100 && ulCnts != 0)
        {
            iStatus = ulScaledMicros * ulTimerClkFreq % 1000000UL;
            ptrTimer0->uiTCCRB = i+1;
            break;
        }
    }
    if(iStatus != -1)
    {
        g_EventTimerCallback = fEventCallback;
        ptrTimer0->uiTCCRA = 0;
        ptrTimer0->uiTCCRA |= (TIMER_MODE_CLEAR << TIMER_COMA);
        ptrTimer0->uiOCRA = (uint8_t) (0xFF & ulCnts);
        ptrTIMSK->uiTIMSK0 = TIMSK_A;
        ptrTFLG->uiTIFLG0 = TIFLG_A;
    }
    return iStatus;
}

ISR(TIMER0_COMPA_vect)
{
    if(g_ulEventTimerTicks == 0 && g_ulEventCeil != 0)
    {
        g_EventTimerCallback();
    }
    g_ulEventTimerTicks = (g_ulEventTimerTicks + 1) % g_ulEventCeil;
}

void NoOpISR()
{
    
}
