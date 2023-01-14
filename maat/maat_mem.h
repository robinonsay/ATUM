#ifndef MAAT_MEM_H
#define MAAT_MEM_H

#include <avr/common.h>

#define MEM_OFFST   (0x20)

#define B_ADDR      (0x03 + MEM_OFFST)
#define C_ADDR      (0x06+ MEM_OFFST)
#define D_ADDR      (0x09 + MEM_OFFST)

#define TIMER0_ADDR (0x24 + MEM_OFFST)
#define TIMER1_ADDR (0x84)
#define TIMER2_ADDR (0xB0)

#define TIMSK_ADDR (0x6E)
#define TIFLG_ADDR (0x15 + MEM_OFFST)

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

typedef struct ATUM_TIMER_INT_MASK_TAG
{
    uint8_t uiTIMSK0;
    uint8_t uiTIMSK1;
    uint8_t uiTIMSK2;
}ATUM_TIMER_INT_MASK_T;

typedef struct ATUM_TIMER_INT_FLAG_TAG
{
    uint8_t uiTIFLG0;
    uint8_t uiTIFLG1;
    uint8_t uiTIFLG2;
}ATUM_TIMER_INT_FLAG_T;


ATUM_PORT_T* const ptrB;
ATUM_PORT_T* const ptrC;
ATUM_PORT_T* const ptrD;

ATUM_TIMER_8_T* const ptrTimer0;
ATUM_TIMER_16_T* const ptrTimer1;
ATUM_TIMER_8_T* const ptrTimer2;

ATUM_TIMER_INT_MASK_T* const ptrTIMSK;
ATUM_TIMER_INT_FLAG_T* const ptrTFLG;

#endif /* MAAT_MEM_H */
