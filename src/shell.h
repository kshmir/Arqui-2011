#ifndef _START_H_
#include "../src/drivers/video.h"
#include <stdarg.h>
#define _START_H_

#define CLSIZE 4

void shellStart();

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

#define BORRA_BUFFER while (getchar() != '\n')

void printHelp();

void printdouble(double number, char* format);

void internalswap(char* answ, int pos);

void printstring(char* message);

void printint(int number, char* format);




void selectcmd(int value, char** usr);

char* su(char* usr);

void init();

int getcommand();

int getint(char* mensaje, ...);

char* getusr();

#endif

