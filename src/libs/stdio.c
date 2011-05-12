#include "stdio.h"
#include "internal_shell.h"
#include "../drivers/video.h"
#include "../drivers/keyboard.h"

void putchar(char c)
{
	if (c == '\n')
		newLine();
	else if (c != 0 )
		putC(c);
}




char getchar()
{
	char c;
	while((c = getC()) != '\n') putchar(c);
	return c;
}
