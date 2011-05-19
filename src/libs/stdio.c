#include "stdio.h"
#include "internal_shell.h"
#include "../drivers/video.h"
#include "../drivers/keyboard.h"
#include <stdarg.h>

void putchar(char c) {

	if (c == '\r') {
		backSpace();
	} else if (c == '\n') {
		newLine();
	} else if (c == 0x0f || c == '\t') {
		if (getCursorX() % 4 == 0) {
			int i = 0;
			for (i = 0; i < 4; ++i) {
				putChar(c);
				putC(' ');
			}
		} else
			while (getCursorX() % 4 != 0) {
				putChar(c);
				putC(' ');
			}
	} else if (c != 0) {
		putChar(c);
		putC(c);
	}
}

char getchar() {
	char c;
	int sx = getCursorX();
	int sy = getCursorY();
	while ((c = getC()) != '\n') {
		if (c != 0) {
			if (c != 0x0f) {
				if (c != '\r' || getCursorY() > sy || getCursorX() > sx)
					putchar(c);
			} else {
				putTab();
			}
		}
	}
	putchar(c);
	return c;
}

double atof(char*string) {
	int sign = 1;
	int decount = 0;
	int i = 0;
	double result = 0.0;
	double decimals = 0.1;

	while (string[i] != '\0') {
		if (string[i] == '.') {
			decount = 1;
			i++;
		} else {
			if (!decount) {
				if (string[i] == '-') {
					i++;
					sign = -1;
				} else {
					result = result * 10 + (string[i] - ASCIICERO);
					i++;
				}
			} else {
				result = result + decimals * (string[i] - ASCIICERO);
				decimals /= 10;
				i++;
			}
		}
	}
	return result * sign;
}
int atoi(char* string) {

	int i = 0;
	int result = 0;
	int sign = 1;

	while (string[i] != '\0') {
		if (string[i] == '-') {
			sign = -1;
			i++;
		}
		result = result * 10 + (string[i] - ASCIICERO);
		i++;
	}
	return result * sign;

}

void ftoa(float number, char* answ) {
	double a;
	char ascii0 = '0';
	int pos = 0;
	int decimal = 6;
	int resultado;
	char dec[7];

	char sign = FALSE;
	if (number < 0) {
		sign = TRUE;
		number *= -1;
	}
	answ[pos++] = '\0';

	if ((int) number == 0) {
		answ[pos++] = '0';
	}
	decimal--;
	a =	number - (int)number;
	
	resultado = a*1000000;
	while (decimal>=0) {
		dec[decimal] = resultado % 10 + '0';
		resultado /= 10;
		decimal--;
	}
	//dec[6] = 0;
	
	while ((int) number != 0) {
		answ[pos++] = (int) number % 10 + ascii0;
		number /= 10;


	}

	/*
	 * This is because when it get out of the whie it has been divide per 10, one more time
	 */
	number *= 10;
	if (sign == TRUE)
		answ[pos++] = '-';
	
	internalswap(answ, pos - 1);
	
	answ[pos-1]='.';
	pos++;
	for(decimal=0;decimal<=7;decimal++){
			answ[pos-1]=dec[decimal];
			pos++;
	}
	
}

void itoa(int number, char* answ) {

	int pos = 0;

	char sign = FALSE;
	if (number < 0) {
		sign = number < 0 ? TRUE : FALSE;
		number *= -1;
	}

	answ[pos++] = '\0';
	if (number == 0)
		answ[pos++] = ASCIICERO;
	else {
		while (number != 0) {
			answ[pos++] = (number % 10) + ASCIICERO;
			number /= 10;
		}
		if (sign == TRUE)
			answ[pos++] = '-';
	}
	internalswap(answ, pos - 1);
}

void printf(char* string, ...) {
	va_list ap;

	va_start(ap, string);

	vprintf(string, ap);
}

void vprintf(char* string, va_list ap) {
	int i = 0, va_count;
	while (string[i] != '\0') {
		if (string[i] == '%') {
			i++;
			switch (string[i]) {
			case 'd':
				printint(va_arg(ap,int),string);
				break;
			case 's':
				printstring( va_arg( ap, char*));
				break;
			case 'c':
				putchar( va_arg( ap, int));
				break;
			case 'f':
				printdouble(va_arg(ap,double),string);
				break;
			case '%':
				putchar('%');
				break;

			default:
				printstring("\n invalid argument type error \n");
			}
			i++;
		} else {
			putchar(string[i]);
			i++;
		}
	}
	va_end(ap);
}

void clrscr() {
	clear_screen();
}

int invalidScanf = 0;

int scanint(int *pint, char*message) {
	char result[20];
	int final;
	int i = 0;

	while (isdigit(message[i])) {
		result[i] = message[i];
		i++;
	}
	invalidScanf = (isdigit(message[i])) ? 1 : 0;
	result[i] = '\0';
	final = atoi(result);
	*(pint) = final;
	return i;

}

int scandouble(double *pdouble, char*message) {
	char result[40];
	double final;
	int i = 0;
	int pos = 0;
	int flag = TRUE;

	/* this is used to get de integer part*/
	while (isdigit(message[i])) {
		result[i] = message[pos];
		i++;
		pos++;
	}
	invalidScanf = (isdigit(message[pos])) ? 1 : 0;
	if (invalidScanf)
		return pos;
	if (message[pos] == '.') {
		result[i++] = '.';
		pos++;
	} else
		flag = FALSE;

	if (flag) {

		/* this is used to get de decimal part*/
		while (isdigit(message[pos])) {
			result[i] = message[pos];
			i++;
			pos++;
		}
		invalidScanf = (isdigit(message[pos])) ? 1 : 0;
		result[i] = '\0';
		final = atof(result);
		*(pdouble) = final;
	}

	return pos;
}
int isdigit(int ch) {
	return (ch >= '0' && ch <= '9');
}

int scanstring(char* pchar, char*message) {

	int i = 0;
	while (message[i] != '\0' && message[i] != ' ') {
		pchar[i] = message[i];
		i++;
	}
	pchar[i] = '\0';
	return i;
}

int scanf(char* string, ...) {
	int i = 0, va_count;
	int c;
	int bufpos = 0;
	int percentflag = FALSE;
	int endFlag = FALSE;
	int oldBuf = 0;

	char buffer[200];
	char *ch;
	va_list ap;

	va_start(ap, string);
	int sx = getCursorX();
	int sy = getCursorY();

	while ((c = getC()) != '\n') {
		if (c != 0) {
			if (c != 0x0f) {
				if (c != '\r' || getCursorY() > sy || getCursorX() > sx)
					putchar(c);
				if (c != '\r') {
					buffer[i] = c;
					i++;
				} else {
					if (i > 0) {
						buffer[i] = 0;
						i--;
					}
				}
			} else {
				putTab();
			}
		}
	}
	putchar(c);
	i = 0;
	while (string[i] != '\0' && !endFlag) {
		if (string[i] == '%' && !percentflag) {
			i++;
			oldBuf = bufpos;
			switch (string[i]) {
			case 'd':
				bufpos += scanint(va_arg(ap,int*),buffer+bufpos);
				break;
			case 's':
				bufpos += scanstring(va_arg(ap,char*),buffer+bufpos);
				break;
			case 'c':
				ch = va_arg(ap,char*);
				*(ch) = buffer[bufpos];
				bufpos++;
				break;
			case 'f':
				bufpos += scandouble(va_arg(ap,double*),buffer+bufpos);
				break;
			case '%':
				percentflag = TRUE;
				break;
			default:
				printstring("\n invalid argument type error \n");
			}
			i++;
		} else {
			if (string[i] != buffer[bufpos]) {
				endFlag = TRUE;
			} else {
				i++;
				bufpos++;
				percentflag = FALSE;
			}
		}
	}
	va_end(ap);
	
	return !invalidScanf; //TODO: FIX THIS
}

