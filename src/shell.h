
#ifndef _START_H_
#include "../src/libs/video.h"
#define _START_H_

#define CLSIZE 4

void shellStart();

void drawComandLine();
void execute(char* c);
void nextRow();
void reDrawLines();

void putTab();
void putSpace();
void backSpace();
void onEscape();
void removeTab();

void putChar(char c);

void shellKBInterrupt();

#endif

