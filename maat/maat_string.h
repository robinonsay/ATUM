#ifndef MAAT_STRING_H
#define MAAT_STRING_H

#include "maat_types.h"

void Maat_Memcpy(char* dest, char* src, size_t len);
unsigned long Maat_Strlen(char str[]);
char* Maat_Strcat(char str0[], char str1[]);
void Maat_Sprintf(char buff[], char str[], ...);

#endif /* MAAT_STRING_H */