#include "maat.h"
#include <util/crc16.h>

#define RX_ENABLE   (4)
#define TX_ENABLE   (3)
#define USBS        (3)
#define UCSZ        (1)
#define UDRE        (5)
#define RXC         (7)
#define UPE         (2)
#define UPM         (4)
int8_t Maat_InitUART(unsigned long uiBaudRate)
{
    int8_t iStatus = 0;
    if(uiBaudRate == 0)
    {
        uiBaudRate = MAA_DEFAULT_BAUD_RATE;
    }
    ptrUSART->uiUBRR = (uint16_t)(0xFFF & (CLK_FREQ / (16 * uiBaudRate) - 1));\
    ptrUSART->uiUCSRB = (1 << RX_ENABLE) | (1 << TX_ENABLE);
    ptrUSART->uiUCSRC = (1 << USBS) | (3 << UCSZ) | (2 << UPM);
    return iStatus;
}

int8_t Maat_WriteUART(char* ptrBuff, size_t sBuffSize)
{
    int8_t iStatus = 0;
    for(size_t i=0; i < sBuffSize; i++)
    {
        // Wait for buffer to clear
        while(!(ptrUSART->uiUCSRA & (1 << UDRE)));
        ptrUSART->uiUDR = ptrBuff[i];
    }
    return iStatus;
}

int8_t Maat_ReadUART(char* ptrBuff, size_t sBuffSize)
{
    int8_t iStatus = 0;
    for(size_t i = 0; i < sBuffSize; i++)
    {
        /* Wait for data to be received */
        while ( !(ptrUSART->uiUCSRA & (1 << RXC)) );
        ptrBuff[i] = ptrUSART->uiUDR;
    }
    iStatus = -(ptrUSART->uiUCSRA & (7 << UPE));
    return iStatus;
}

int8_t Maat_StrWriteUART(char* str)
{
    int8_t iStatus = 0;
    for(size_t i=0; str[i]; i++)
    {
        // Wait for buffer to clear
        while(!(ptrUSART->uiUCSRA & (1 << UDRE)));
        ptrUSART->uiUDR = str[i];
    }
    return iStatus;
}

int8_t Maat_StrReadStrUART(char* str, size_t sBuffSize)
{
    int8_t iStatus = 0;
    for(size_t i = 0; i < sBuffSize; i++)
    {
        /* Wait for data to be received */
        while ( !(ptrUSART->uiUCSRA & (1 << RXC)) );
        str[i] = ptrUSART->uiUDR;
        if(!str[i])
        {
            break;
        }
    }
    iStatus = -(ptrUSART->uiUCSRA & (7 << UPE));
    return iStatus;
}

int8_t Maat_MsgWriteUART(MAAT_MSG_T* msg)
{
    int8_t iStatus = 0;
    msg->crc = 0;
    for(size_t i=0; i < sizeof(MAAT_MSG_T) - sizeof(msg->crc); i++)
    {
        while(!(ptrUSART->uiUCSRA & (1 << UDRE)));
        ptrUSART->uiUDR = ((uint8_t *) msg)[i];
        msg->crc = _crc_xmodem_update(msg->crc, ((uint8_t *) msg)[i]);
    }
    while(!(ptrUSART->uiUCSRA & (1 << UDRE)));
    ptrUSART->uiUDR = (uint8_t)(msg->crc & 0xFF);
    while(!(ptrUSART->uiUCSRA & (1 << UDRE)));
    ptrUSART->uiUDR = (uint8_t)((msg->crc & 0xFF00) >> 8);
    return iStatus;
}
