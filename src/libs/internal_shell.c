#include "internal_shell.h"

void newLine()
{
	setCursorY(getCursorY() + 1);
	setCursorX(0);
}
