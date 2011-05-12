#include "mcglib.h"
#include "video.h"

void printString(char* c) {
	int i = 0;
	while (c[i] != 0)
		putC(c[i++]);
}
