#ifndef _MCGIO_H_

#define _MCGIO_H_

#include "../../include/defs.h"

void setTabCall(void (*ptr)(char*));
void printString(char* c);
int cursorX();
int cursorY();
char* getConsoleString();

#endif /* MCGIO_H_ */

