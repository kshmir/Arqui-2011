#include "../../include/defs.h"
#include "mcgio.h"
#include "stdio.h"
#include <stdarg.h>

void (*onTabCall)(char*) = NULL;

void setTabCall(void(*ptr)(char*)) {
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

char* getConsoleString(int sendAutocomplete) {
	char c;
	char* str = NULL;
	str = (char*) malloc(sizeof(char) * 80); // TODO: This should increment on hit
	int i = 0;
	int sx = getCursorX();
	int sy = getCursorY();
	while ((c = getC()) != '\n') {
		if (c != 0x0f && c != 0) {
			if (c != '\r' || getCursorY() > sy || getCursorX() > sx)
				mcg_putchar(c);
			if (c != '\r')
			{
				str[i] = c;
				i++;
			}
			else
			{
				if (i > 0)	{
					str[i] = 0;
					i--;
				}
			}

		} else if (c != 0){
			if (onTabCall != NULL && sendAutocomplete) {
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

void printstring(char* message) {
	int i = 0;
	while (message[i] != '\0') {
		putchar(message[i]);
		i++;
	}
}

int getint(char* mensaje, ... ){
	int n, salir = 0;
	va_list ap;

	do
	{
		va_start(ap, mensaje);
		vprintf(mensaje, ap);
		va_end(ap);

		if ( scanf("%d",&n) != 1)
		{
			printf("\nInvalid Value, please Try again\n");
		}
		else
		{
			BORRA_BUFFER;
			salir = 1;
		}
	} while (! salir);
	return n;
}

void printdouble(double number, char* format) {
	char chardouble[40];
	ftoa(number, chardouble);
	printf("valor del numero ->%s\n",chardouble);
	int i = 0;
	while (chardouble[i] != '\0') {
		putchar(chardouble[i]);
		i++;
	}
}

void printint(int number, char* format) {
	char charint[20];
	itoa(number, charint);
	int i = 0;
	while (charint[i] != '\0')
		putchar(charint[i++]);
}

void internalswap(char* answ, int pos) {
	int correccion = 0;
	int i = 0;
	correccion += pos % 2;
	while (i < (pos + correccion) / 2) {
		char aux = answ[i];
		answ[i] = answ[pos - i];
		answ[pos - i] = aux;
		i++;
	}
}

int mcg_printf(char* string, ...) {
	int i = 0, c = 0, va_count;
	va_list ap,bp;
	va_start(ap, string);
	while (string[i] != '\0') {
		if (string[i] == '\n')
			c++;
		else
		if (string[i] == '%') {
			i++;
			switch (string[i]) {
			case 's':
				c += entersOnString(va_arg(ap,char*));
				break;
			case 'c':
				c += (va_arg( ap, int)) ? 1 : 0;
				break;
			}
		}
		i++;
	}
	va_start(bp, string);
	vprintf(string, bp);
	va_end(ap);
	return c;
}

int entersOnString(char* str) {
	int i = 0, c = 0;
	for (i = 0; str[i] != 0; ++i)
		c += (str[i] == '\n') ? 1 : 0;
	return c;
}

