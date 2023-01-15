#ifndef MAAT_MEM_H
#define MAAT_MEM_H

#include <avr/common.h>

#define MEM_OFFST   (0x20)

#define B_ADDR      (0x03 + MEM_OFFST)
#define C_ADDR      (0x06+ MEM_OFFST)
#define D_ADDR      (0x09 + MEM_OFFST)

#define TIMER0_ADDR (0x24 + MEM_OFFST)
#define TIMER1_ADDR (0x80)
#define TIMER2_ADDR (0xB0)

#define TIMSK_ADDR  (0x6E)
#define TIFLG_ADDR  (0x15 + MEM_OFFST)

#define USART_ADDR  (0xC0)
#define PRR_ADDR    (0x64)

typedef struct MAAT_PORT_TAG
{
    uint8_t pin;
    uint8_t ddr;
    uint8_t port;
} MAAT_PORT_T;

typedef struct MAAT_TIMER_8_TAG
{
    uint8_t uiTCCRA;
    uint8_t uiTCCRB;
    uint8_t uiTCNT;
    uint8_t uiOCRA;
    uint8_t uiOCRB;
} MAAT_TIMER_8_T;

typedef struct MAAT_TIMER_16_TAG
{
    uint8_t uiTCCRA;
    uint8_t uiTCCRB;
    uint8_t uiTCCRC;
    uint8_t _uiResv;
    uint16_t uiTCNT;
    uint16_t uiICR;
    uint16_t uiOCRA;
    uint16_t uiOCRB;
} MAAT_TIMER_16_T;

typedef struct MAAT_TIMER_INT_MASK_TAG
{
    uint8_t uiTIMSK0;
    uint8_t uiTIMSK1;
    uint8_t uiTIMSK2;
}MAAT_TIMER_INT_MASK_T;

typedef struct MAAT_TIMER_INT_FLAG_TAG
{
    uint8_t uiTIFLG0;
    uint8_t uiTIFLG1;
    uint8_t uiTIFLG2;
}MAAT_TIMER_INT_FLAG_T;

typedef struct MAAT_USART_TAG
{
    uint8_t     uiUCSRA;
    uint8_t     uiUCSRB;
    uint8_t     uiUCSRC;
    uint8_t     _uiResv;
    uint16_t    uiUBRR;
    uint8_t     uiUDR;
} MAAT_USART_T;


MAAT_PORT_T* const ptrB;
MAAT_PORT_T* const ptrC;
MAAT_PORT_T* const ptrD;

MAAT_TIMER_8_T* const ptrTimer0;
MAAT_TIMER_16_T* const ptrTimer1;
MAAT_TIMER_8_T* const ptrTimer2;

MAAT_TIMER_INT_MASK_T* const ptrTIMSK;
MAAT_TIMER_INT_FLAG_T* const ptrTFLG;

MAAT_USART_T* const ptrUSART;

uint8_t* const ptrPRR;

#endif /* MAAT_MEM_H */
