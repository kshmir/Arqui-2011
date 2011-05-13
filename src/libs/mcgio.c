#include "mcgio.h"
#include "stdio.h"

void (*onTabCall)(char*) = NULL;

void setTabCall(void (*ptr)(char*))
{
	onTabCall = ptr;
}

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
		return;
	} else if (c != 0) {
		putChar(c);
		putC(c);
	}
}



char* getConsoleString() {
	char c;
	char* str = NULL;
	str = (char*)malloc(str, sizeof(char) * 80); // TODO: This should increment on hit
	int i = 0;
	while ((c = getC()) != '\n') {
		if (c != 0x0f) {
			mcg_putchar(c);
			str[i] = c;
			i++;
		} else {
			if (onTabCall != NULL)
			{
				str[i] = 0;
				onTabCall(str);
			}
		}
	}
	mcg_putchar(c);
	clear_screen_topdown();
	str[i] = 0;
	return str;
}
