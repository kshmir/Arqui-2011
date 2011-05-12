#include "mcgio.h"
#include "stdio.h"

void printString(char* c) {
	int i = 0;
	while (c[i] != 0)
		putchar(c[i++]);
}
