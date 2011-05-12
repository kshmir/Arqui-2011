#include "stdio.h"
#include "video.h"
#include "keyboard.h"

void putchar(char c)
{
	if (c != 0)
		putC(c);
}




char getchar()
{
	return getC();
}
