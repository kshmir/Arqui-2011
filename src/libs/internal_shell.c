#include "internal_shell.h"
#include "stdlib.h"
#include "../../include/kasm.h"

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

/** Inicio del shell, borra la pantalla y escribe la linea de comandos*/
void internalShellStart() {

}

/**TODO: aca se debe analizar lo que se recibe y ejecutar alguna
 * funcion*/
void execute(char* c) {

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

void putSpace() {
	putC(getC());
	getVideoMode()->shell->screen[getCursorX() + 1][getCursorY()] = ' ';
}

void putTab() {
	putchar(0x0f);
}

void backSpace() {
	if (getCursorX() % 4 == 0
			&& getVideoMode()->shell->screen[getCursorX() - 1][getCursorY()]
					== 0x0f) {
		removeTab();
	} else {
		removeLastC();
	}

}

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

void onEscape() {
	shellStart();
}

void removeLastC() {
	decrementCursor();
	putChar(' ');
	putC(' ');
	decrementCursor();
}

