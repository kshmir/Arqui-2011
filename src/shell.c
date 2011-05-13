#include "shell.h"
#include "../include/defs.h"
#include "libs/mcgio.h"
#include "libs/stdio.h"
#include "drivers/video.h"
#include <stdarg.h>

int glb = 1;


void whenTabCalls(char* s){
	int startX = getCursorX();
	int startY = getCursorY();
	int desp = glb, i = 0;
	printf("\n");
	for (i = 0; i < glb; ++i) {
		printf("%d%d%d%d%d\t", i,i,i,i,i);
	}
	glb++;
	VIDEO_MODE_INFO * mode = getVideoMode();
	if (getCursorY() == mode->height - 1){
		if (startY != getCursorY())
			setCursorY(getCursorY() - desp);
		else
			setCursorY(startY - desp);
	}
	else
		setCursorY(startY);
	setCursorX(startX);
}

void shellStart() {
	printf("Murcielag O.S. is loading...\n");
	setTabCall(whenTabCalls);
}

void init() {
	while(1)
		getConsoleString();
	return;
}

int getint(char* mensaje, ...) {
	int n, salir = 0;
	va_list ap;

	do {
		printf(mensaje);
		if (getchar() != '1') {
			printf("Invalid Value, please Try again\n");
			BORRA_BUFFER;
		} else
			salir = 1;
	} while (!salir);
	BORRA_BUFFER;
	return n;
}



char* getusr() {
	int usrid;
	int flag = 0;
	do {
		printf("Please Select User:\n");
		printf("0->Mario(root):\n");
		printf("1->Luigi:\n");
		usrid = getint("Option:\n");
		if (usrid == MARIO) {
			flag = 1;
			return MARIOST;
		} else if (usrid == LUIGI) {
			flag = 1;
			return LUIGIST;
		}
	} while (!flag);

}

int getcommand() {
	return getint("");

}

void printHelp() {

	printf("Murcielago bash, version 1.0.0(1)-release (i686-pc-murcielago)\n");
	printf(
			"These shell commands are defined internally.  Type `help' to see this list.\n");
	printf("Type `help name' to find out more about the function `name'.\n");
	printf("Use `info bash' to find out more about the shell in general.\n\n");
	printf("%d->help [pattern ...]\n", HELP);
	printf("%d->clear\n", CLEAR);
	printf("%d->echo [arg ...]\n", ECHO);
	printf("%d->cpuspeed\n", CPUSPEED);
	printf("%d->su\n", SU);
	printf("%d->logout [n]\n", LOGOUT);

}

void selectcmd(int opt, char** usr) {
	switch (opt) {
	case HELP:
		printHelp();
		break;
	case SU:
		*usr = su(*usr);
		break;
	case CLEAR:
		printf("cablear clear screen maxi\n");
		break;
	case ECHO:
		printf("crear echo\n");
		break;
	case CPUSPEED:
		printf("es muy alta \n");
		break;
	}
}

char* su(char* usr) {
	return (usr == MARIOST ? LUIGIST : MARIOST);
}

void printf(char* string, ...) {

	int i = 0, va_count;
	va_list ap;

	va_start(ap, string);

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

void printstring(char* message) {
	int i = 0;
	while (message[i] != '\0') {
		putchar(message[i]);
		i++;
	}
}

void printdouble(double number, char* format) {

	char chardouble[40];

	ftoa(number, chardouble);
	int i = 0;
	while (chardouble[i] != '\0') {
		putchar(chardouble[i]);
		i++;
	}
}



