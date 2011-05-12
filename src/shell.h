
#ifndef _START_H_
#include "../src/libs/video.h"
#include <stdarg.h>
#define _START_H_

#define CLSIZE 4

void shellStart();

#define ASCIICERO 0x30
#define MARIO 0
#define LUIGI 1
#define MARIOST "mario"
#define LUIGIST "luigi"
#define OSDEFST "@murcielago:~#"
#define HELP 0
#define CLEAR 1
#define ECHO 2
#define CPUSPEED 3
#define SU 4
#define LOGOUT 5
#define REBOOT 6
#define TRUE 1
#define FALSE 0

#define BORRA_BUFFER while (getchar() != '\n')

double myatof(char*string);

int myatoi(char* string);

void printdouble(double number, char* format);

void internalswap(char* answ, int pos);

void printHelp();

void printstring(char* message);

void myitoa(int number, char* resp);

void printint(int number, char* format);

void myprintf(char* string, ...);

void selectcmd(int value, char** usr);

char* su(char* usr);

void init();

int getcommand();

int getint(char* mensaje, ...);

char* getusr();

void myftoa(float number, char* answ);


#endif

