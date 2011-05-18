#ifndef _START_H_
#include "../src/drivers/video.h"
#include "../src/libs/string.h"
#include <stdarg.h>
#define _START_H_

#define CLSIZE 4

void shellStart();

#define OSDEFST "@murcielagOS:~#"

void printHelp(int size, char* args);

void internalswap(char* answ, int pos);

void selectcmd(int value, char** usr);

char* su(char* usr);

void cpuSpeed();

void init();

int logout(int size, char* args);
int login(int size, char* args);


#endif

