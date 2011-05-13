#ifndef _STDLIO_H_

#define _STDLIO_H_
#include "../../include/defs.h"
#include <stdarg.h>

void putchar(char c);
char getchar();

double atof(char*string);
int  atoi(char* string);
void itoa(int number, char* resp);
void printf(char* string, ...);

void ftoa(float number, char* answ);
void vprintf(char* string, va_list ap);

void clrsrc();
#endif /* STDLIO_H_ */

