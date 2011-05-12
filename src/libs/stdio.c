#include "stdio.h"
#include "../drivers/video.h"
#include "../drivers/keyboard.h"

void writeLine()
{

}

void putchar(char c)
{
	if (c == '\n')
		writeLine();
	else if (c != 0 )
		putC(c);
}




char getchar()
{
	return getC();
}
