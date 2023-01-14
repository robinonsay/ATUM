#ifndef MAAT_MEM_H
#define MAAT_MEM_H

#include "maat_types.h"

#define MEM_OFFST   (0x20)

#define B_ADDR      (0x03 + MEM_OFFST)
#define C_ADDR      (0x06+ MEM_OFFST)
#define D_ADDR      (0x09 + MEM_OFFST)

#define TIMER0_ADDR (0x24 + MEM_OFFST)
#define TIMER1_ADDR (0x84)
#define TIMER2_ADDR (0xB0)

typedef struct ATUM_PORT_TAG
{
    uint8_t pin;
    uint8_t ddr;
    uint8_t port;
} ATUM_PORT_T;

typedef struct ATUM_TIMER_8_TAG
{
    uint8_t uiTCCRA;
    uint8_t uiTCCRB;
    uint8_t uiTCNT;
    uint8_t uiOCRA;
    uint8_t uiOCRB;
} ATUM_TIMER_8_T;

typedef struct ATUM_TIMER_16_TAG
{
    uint8_t uiTCCRA;
    uint8_t uiTCCRB;
    uint8_t uiTCCRC;
    uint8_t _uiResv;
    uint16_t uiTCNT;
    uint16_t uiICRA;
    uint16_t uiOCRA;
    uint16_t uiOCRB;
} ATUM_TIMER_16_T;

ATUM_PORT_T* const ptrB = (ATUM_PORT_T*) B_ADDR;
ATUM_PORT_T* const ptrC = (ATUM_PORT_T*) C_ADDR;
ATUM_PORT_T* const ptrD = (ATUM_PORT_T*) D_ADDR;

ATUM_TIMER_8_T* const ptrTimer0 = (ATUM_TIMER_8_T*) TIMER0_ADDR;
ATUM_TIMER_16_T* const ptrTimer1 = (ATUM_TIMER_16_T*) TIMER1_ADDR;
ATUM_TIMER_8_T* const ptrTimer2 = (ATUM_TIMER_8_T*) TIMER2_ADDR;

#endif /* MAAT_MEM_H */
