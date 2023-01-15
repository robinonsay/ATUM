#include "maat_string.h"
#include <avr/common.h>
#include <stdarg.h>

#define BASE_10 (10)

char g_Digits[] = "0123456789";

unsigned long Maat_Strlen(char str[])
{
    unsigned long ulStrLen = 0;
    for(unsigned long i = 0; str[i]; i++)
    {
        ulStrLen++;
    }
    return ulStrLen;
}

void Maat_Sprintf(char buff[], char str[], ...)
{
    va_list arguments;
    va_start(arguments, str);
    unsigned long num;
    uint8_t uiNumDigits = 0;
    uint8_t uiOffst = 0;
    uint8_t uiBuffN = 0;
    char temp = 0;
    for(uint8_t i = 0; str[i]; i++)
    {
        if(str[i] == '%')
        {
            i++;
            switch(str[i])
            {
                case 'u':
                    num = va_arg(arguments, unsigned long);
                    uiNumDigits = 0;
                    while(num >= BASE_10)
                    {
                        uiNumDigits++;
                        buff[uiBuffN] = g_Digits[num % BASE_10];
                        num = num / BASE_10;
                        uiBuffN++;
                    }
                    buff[uiBuffN] = g_Digits[num % BASE_10];
                    uiOffst = uiBuffN - uiNumDigits;
                    for(uint8_t n = 0; n <= uiNumDigits / 2; n++)
                    {
                        temp = buff[uiOffst + n];
                        buff[uiOffst + n] = buff[uiOffst + uiNumDigits- n];
                        buff[uiOffst + uiNumDigits - n] = temp;
                    }
                break;
            }
        }
        else
        {
            buff[uiBuffN] = str[i];
        }
        uiBuffN++;
    }
    va_end(arguments);
}