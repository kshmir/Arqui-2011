#ifndef _MCGIO_H_

#define _MCGIO_H_

#include "../../include/defs.h"

void setTabCall(char* (*ptr)(char*));
void setArrowHit(char* (*ptr)(int));
void printString(char* c);
int cursorX();
int cursorY();
char* getConsoleString();

void printdouble(double number, char* format);
void printstring(char* message);
void printint(int number, char* format);
int getint(char* mensaje, ...);

#endif /* MCGIO_H_ */

