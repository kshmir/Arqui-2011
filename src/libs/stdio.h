#ifndef _STDLIO_H_

#define _STDLIO_H_
#include "../../include/defs.h"

void putchar(char c);
char getchar();

double atof(char*string);
int atoi(char* string);
void itoa(int number, char* resp);
void printf(char* string, ...);
void ftoa(float number, char* answ);

#endif /* STDLIO_H_ */

