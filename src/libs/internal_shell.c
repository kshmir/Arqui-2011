#include "internal_shell.h"
#include "stdlib.h"
#include "../../include/kasm.h"

// Makes a new line
void newLine() {
	setCursorX(0);
	if (!(getCursorY() >= getVideoMode()->height - 1)) {
		setCursorY(getCursorY() + 1);
	} else {
		int i, j;
		int last_len = 0, current_len;
		for (j = 2; j < getVideoMode()->height; j++) {
			for (i = 0; i < getVideoMode()->width; i++) {
				getVideoMode()->shell->screen[i][j]
						= getVideoMode()->shell->screen[i][j + 1];
			}
		}
		for (i = 0; i < getVideoMode()->width; i++)
			getVideoMode()->shell->screen[i][getVideoMode()->height] = ' ';
		reDrawLines();
		setCursorY(getCursorY() - 1);
		setCursorX(0);
	}
}

/**	Copia todo lo que hay en el BUFFER DE PANTALLA (no en la placa de
 * video) y lo vuelve a imprimir*/
void reDrawLines() {
	int i, j;
	setCursor(FALSE);
	setCursorY(2);
	for (j = 2; j < getVideoMode()->height; j++) {
		setCursorX(0);
		for (i = 0; i < getVideoMode()->width; i++) {
			putC(getVideoMode()->shell->screen[i][j]);
		}
		setCursorY(getCursorY() + 1);
	}
	setCursor(TRUE);
	setCursorX(0);
}

// Puts a space
void putSpace() {
	putC(getC());
	getVideoMode()->shell->screen[getCursorX() + 1][getCursorY()] = ' ';
}

// Inserts a tab
void putTab() {
	putchar(0x0f);
}

// Makes a backspace
void backSpace() {
	if (getCursorX() % 4 == 0
			&& getVideoMode()->shell->screen[getCursorX() - 1][getCursorY()]
					== 0x0f) {
		removeTab();
	} else {
		removeLastC();
	}

}

// Removes a tab
void removeTab() {
	int oneStep = 1;
	int x = getCursorX();
	while (x % 4 > 0 || oneStep) {
		if (getVideoMode()->shell->screen[x - 1][getCursorY()] == 0x0f
				|| getVideoMode()->shell->screen[x - 1][getCursorY()] == 0) {
			removeLastC();
		}
		oneStep = 0;
		x--;

	}
}

// Puts a char
void putChar(char c) {
	int x = getCursorX();
	int y = getCursorY();
	if (x <= getVideoMode()->width) {
		if (c != '\r')
			getVideoMode()->shell->screen[x][y] = c;
		x += (c != '\r') ? 1 : -1;
	} else {
		newLine();
		getVideoMode()->shell->screen[x][y] = c;
	}
}

// Escape trigger, deprecated
void onEscape() {
	clear_screen();
}

// Backspace trigger
void removeLastC() {
	decrementCursor();
	putChar(' ');
	putC(' ');
	decrementCursor();
}

