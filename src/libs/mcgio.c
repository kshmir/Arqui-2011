#include "mcgio.h"
#include "stdio.h"

void printString(char* c) {
	int i = 0;
	while (c[i] != 0)
		putchar(c[i++]);
}


void mcg_putchar(char c) {
	if (c == '\r') {
		backSpace();
	} else if (c == '\n') {
		newLine();
	} else if (c == 0x0f) {

	} else if (c != 0) {
		putChar(c);
		putC(c);
	}
}
