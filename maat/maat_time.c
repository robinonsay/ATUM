#include "maat.h"
#include "avr/io.h"
#include "avr/interrupt.h"

static time_t g_tTimeNow = 0;
static uint16_t g_uiTicksMicro = 1;
static const uint16_t g_uiTIMER_PRESCALERS[] = {1, 8, 32, 64, 128, 256, 1024};

time_t Maat_TimeNow()
{
    return g_tTimeNow;
}

#define TIMER_COMA          (6)
#define TIMER_MODE_TOGGLE   (1)
#define TIMER_MODE_CLEAR    (2)
#define TIMSK_A             (1 << 1)
#define TIFLG_A             (1 << 1)
int Maat_InitTime(uint16_t uiTicksMicros)
{
    int iStatus = -1;
    unsigned long ulTimerClkFreq = 0;
    unsigned long ulCnts = 0;
    g_uiTicksMicro = uiTicksMicros;
    for(uint8_t i = 0; i < 7 && uiTicksMicros != 0; i++)
    {
        ulTimerClkFreq = CLK_FREQ / g_uiTIMER_PRESCALERS[i];
        ulCnts = uiTicksMicros * ulTimerClkFreq / 1000000UL;
        if(ulCnts < 0x100 && ulCnts != 0)
        {
            iStatus = ulCnts * ulTimerClkFreq % 1000000UL;
            ptrTimer0->uiTCCRB = i+1;
            ptrTimer2->uiTCCRB = i+1;
            break;
        }
    }
    if(iStatus != -1)
    {
        ptrTimer2->uiTCCRA = 0;
        ptrTimer2->uiTCCRA |= (TIMER_MODE_CLEAR << TIMER_COMA);
        ptrTimer2->uiOCRA = (uint8_t) (0xFF & (ulCnts));
        ptrTIMSK->uiTIMSK2 = TIMSK_A;
        ptrTFLG->uiTIFLG2 = TIFLG_A;
    }
    return iStatus;
}

ISR(TIMER2_COMPA_vect)
{
    g_tTimeNow += g_uiTicksMicro;
}
