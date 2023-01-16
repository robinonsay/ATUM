#ifndef ATUM_LED_TEST_H
#define ATUM_LED_TEST_H

#include "maat.h"
#include "maat_string.h"


int32_t Atum_LEDInit(char log[]);

int32_t Atum_LEDMain();

#define ATUM_LED_MSG_LEN  (2)

MAAT_MSG_T g_AtumLEDMsgTbl[ATUM_LED_MSG_LEN];

#endif

#ifdef ATUM_LED_TEST
#undef ATUM_LED_TEST
#define LED_PIN (5)
unsigned long g_ulIter = 0;
char* g_strLog;


int32_t Atum_LEDInit(char log[])
{
    g_AtumLEDMsgTbl[0].hdr.ulMid = 0x0000;
    g_AtumLEDMsgTbl[0].hdr.type = MSG_TELEM;
    g_AtumLEDMsgTbl[0].data.telem.type = TELEM_ULONG;
    g_AtumLEDMsgTbl[1].hdr.ulMid = 0x0001;
    g_AtumLEDMsgTbl[1].hdr.type = MSG_LOG;
    g_AtumLEDMsgTbl[1].hdr.ulSize = sizeof(g_AtumLEDMsgTbl[0].data.log);
    ptrB->ddr |= (1 << LED_PIN);
    ptrB->port &= ~(1 << LED_PIN);
    g_strLog = log;
    return 0;
}

int32_t Atum_LEDMain()
{
    ptrB->pin |= 1 << LED_PIN;
    g_AtumLEDMsgTbl[0].data.telem.data.ulLong = g_ulIter;
    Maat_Sprintf(g_AtumLEDMsgTbl[1].data.log, "ATUM_LED: %u\n", g_ulIter);
    g_ulIter++;
    return 0;
}
#endif
