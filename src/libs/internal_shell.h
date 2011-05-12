#ifndef _INTERNAL_SHELL_H_

#define _INTERNAL_SHELL_H_

#include "../drivers/video.h"
#define CLSIZE 4


void newLine();
void internalShellStart();

void drawComandLine();
void execute(char* c);
void nextRow();
void reDrawLines();

void putTab();
void putSpace();
void backSpace();
void onEscape();
void removeTab();

void shellKBInterrupt();


#endif

