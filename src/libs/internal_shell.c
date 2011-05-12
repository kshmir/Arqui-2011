#include "internal_shell.h"
#include "stdlib.h"

void newLine()
{
	setCursorY(getCursorY() + 1);
	setCursorX(0);
}

char lines[MAX_COLS][MAX_ROWS];
char lastLine[MAX_COLS];
int x = 0, y = 0;

/** Inicio del shell, borra la pantalla y escribe la linea de comandos*/
void internalShellStart() {
	int i, j;
	for (i = 0; i < MAX_COLS; i++) {
		for (j = 0; j < MAX_ROWS; j++)
			lines[i][j] = 0;
		lastLine[i] = 0;
	}
	x = y = 0;
}

/**TODO: aca se debe analizar lo que se recibe y ejecutar alguna
 * funcion*/
void execute(char* c) {

}

/**	Copia todo lo que hay en el BUFFER DE PANTALLA (no en la placa de
 * video) y lo vuelve a imprimir*/
void reDrawLines() {
	int i, j;
	clear_screen();
	y = 0;
	for (j = 0; j < MAX_ROWS; j++) {
		x = 0;
		setCursorX(0);
		setCursorY(y++);
		for (i = 0; i < MAX_COLS; i++) {
			if (lines[i][j] == 0x0f) {
				putTab();
			} else if (lines[i][j] == 0) {
				i = MAX_COLS;
			} else {
				putC(lines[i][j]);
				x++;
			}
		}

	}
	//x=0;
	//setCursorX(0);
}

void putSpace() {
	putC(getC());
	lines[x++][y] = ' ';
}

void putTab() {
	putC(' ');
	putC(' ');
	putC(' ');
	putC(' ');
}

void backSpace() {
	if (x > CLSIZE) {
		char c = lines[--x][y];
		lines[x][y] = 0;
		if (c == 0x0f)
			removeTab();
		else {
			removeLastC();
			//setCursorX(getCursorX()-1);
		}
	}
}

void removeTab() {
	removeLastC();
	removeLastC();
	removeLastC();
	removeLastC();
}

void putChar(char c) {
	lines[x++][y] = c;
}

void onEscape() {
	shellStart();
	putChar('R');
}




