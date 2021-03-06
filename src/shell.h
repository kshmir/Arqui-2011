#ifndef _START_H_
#include "../src/drivers/video.h"
#include "../src/libs/string.h"
#include "../src/drivers/sound.h"
#include "../src/libs/libmem.h"
#include <stdarg.h>
#define _START_H_

#define CLSIZE 4
#define EN 0
#define ES 1
#define TRUE 1
#define FALSE 0


void shellStart();

#define OSDEFST "@murcielagOS:~#"


void internalswap(char* answ, int pos);
void selectcmd(int value, char** usr);
char* su(char* usr);
void shellMain();
int toDecimal(int value);
void showHour();
void restoreHour();
void setHour();
int logout(int size, char** args);
int login(int size, char** args);
int ssh(int size, char** args);
int test(int size, char** args);
int clear(int size, char** args);
int cpuSpeed(int size, char** args);
int printHelp(int size, char** args);

int confColor(int size, char** args);
//void showHour();
int changeHour(int size, char** args);
int changeKeyboard(int size ,char** args);
int morse(int size, char** args);
int tryMalloc(int size, char** args);
int tryCalloc(int size, char** args);
int tryFree(int size, char** args);
int tryPrintPages(int size, char **args);
int tryPrintPage(int size, char **args);
int tryPrintMap(int size, char **args);
int tryPrintBlock(int size, char **args);
int tryWrite(int size, char **args);
int tryRealloc(int size, char** args);
int getStack(int size, char** args);
#endif

