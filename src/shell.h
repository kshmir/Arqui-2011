#include "../src/IO.h"
#include "../src/libc.h"
#define CLSIZE 4

void shellStart();

void drawComandLine();
void excecute(char* c);
void nextRow();
void reDrawLines();

void putTab();
void putSpace();
void backSpace();
void onEscape();
void removeTab();
	
void shellKBInterrupt();
