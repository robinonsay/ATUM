#include "maat.h"
#include "avr/io.h"
#include "avr/interrupt.h"

unsigned long g_ulEventCeil = 1;
unsigned long g_ulEventTimerTicks = 0;
const uint16_t g_uiTIMER_PRESCALERS[] = {1, 8, 64, 256, 1024};
void NoOpISR();
void (*g_EventTimerCallback)() = &NoOpISR;

void Maat_Delay(uint8_t ulMicros)
{

}

#define MAX_MICROS          (16320)
#define TIMER_COMA          (6)
#define TIMER_MODE_TOGGLE   (1)
#define TIMER_MODE_CLEAR    (2)
#define TIMER_RES_HIGH      (1)
#define TIMER_RES_8         (1)
#define TIMER_RES_64        (1)
#define TIMER_RES_256       (1)
#define TIMER_RES_1024      (1)
#define TIMSK_A             (2)
#define TIFLG_A             (2)


int Maat_InitEventTimer(unsigned long ulMicros, void (*fEventCallback)())
{
    sei();
    int iStatus = -1;
    unsigned long ulTimerClkFreq = 0;
    unsigned long ulCnts = 0;
    uint16_t uiScaledMicros = ulMicros;
    g_ulEventCeil = 1;
    while(uiScaledMicros > MAX_MICROS)
    {
        g_ulEventCeil++;
        while(ulMicros % g_ulEventCeil != 0)
        {
            g_ulEventCeil++;
        }
        uiScaledMicros = ulMicros / g_ulEventCeil;
    }
    for(uint8_t i = 0; i < 5; i++)
    {
        ulTimerClkFreq = CLK_FREQ / g_uiTIMER_PRESCALERS[i];
        ulCnts = uiScaledMicros * ulTimerClkFreq / 1000000UL;
        if(ulCnts < 0x100 && ulCnts != 0)
        {
            iStatus = 0;
            ptrTimer0->uiTCCRB = i+1;
            break;
        }
    }
    if(iStatus == 0)
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
