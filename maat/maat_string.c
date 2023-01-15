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

char* Maat_Strcat(char str0[], char str1[])
{
    uint32_t uiStr0Len = Maat_Strlen(str0);
    for(uint32_t i = 0; str1[i]; i++)
    {
        str0[uiStr0Len + i] = str1[i];
    }
    return str0;
}

void Maat_Sprintf(char buff[], char str[], ...)
{
    va_list arguments;
    va_start(arguments, str);
    unsigned long num;
    uint16_t uiNumDigits = 0;
    uint32_t uiOffst = 0;
    uint32_t uiBuffN = 0;
    char temp = 0;
    for(uint32_t i = 0; str[i]; i++)
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
    buff[uiBuffN] = '\0';
    va_end(arguments);
}