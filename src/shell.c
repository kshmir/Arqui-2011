#include "../src/shell.h"

char lines[MAX_COLS][MAX_ROWS];
char lastLine[MAX_COLS];
int x = 0, y = 0;

/** Inicio del shell, borra la pantalla y escribe la linea de comandos*/
void shellStart() {
	int i, j;
	for (i = 0; i < MAX_COLS; i++) {
		for (j = 0; j < MAX_ROWS; j++)
			lines[i][j] = 0;
		lastLine[i] = 0;
	}
	x = y = 0;
	k_clear_screen();
	drawComandLine();
}

/** Dibuja la linea de comandos estandard. ATENCION: EN CASO DE 
 * MODIFICAR LA CANTIDAD DE CARACTERES DE ESTA LINEA CAMBIAR CLSIZE*/
void drawComandLine() {
	lines[x++][y] = ' ';
	lines[x++][y] = '$';
	lines[x++][y] = ':';
	lines[x++][y] = ' ';
	putC(' ');
	putC('$');
	putC(':');
	putC(' ');
}
/**TODO: aca se debe analizar lo que se recibe y ejecutar alguna
 * funcion*/
void execute(char* c) {

}

/** Esta funcion es invocada cuando IO recibe un '. Salta de renglon
 *  y en caso de llegar al final corre todas las lineas previa hacia 
 * arriba y escribe una commandLine()*/
/**	Chequeo que instruccion se recibe y la ejecuto*/

void nextRow() {
	/*int i=0,j=0;	//ESTO DEBERIA ANDAR CHEQUEAR. TIRA ERROR EL COMPILADOR. void execute(char[] command)
	 char c[MAX_COLS];
	 for (i=0;i<MAX_COLS;i++){
	 c[i]=0;}
	 int flag=0;
	 for(j=CLSIZE;(j<MAX_COLS && lines[j][y]!=0);j++){
	 c[i-CLSIZE]=lines[i][y];
	 flag=1;
	 }
	 if (flag){
	 execute(c);
	 }
	 //** TODOS LOS COMANDOS QUE SE QUIERAN AGREGAR DEBEN IR EN ESA FUNCION*/
	//** *******************************************************/
	//execute(0);	

	setCursorX(0);
	x = 0;
	if (y < MAX_ROWS - 1) {
		setCursorY(++y);
		drawComandLine();
	} else {
		int i, j;
		for (i = 0; i < MAX_COLS; i++) {
			for (j = 0; j < MAX_ROWS - 1; j++)
				lines[i][j] = lines[i][j + 1];
		}
		for (i = 0; i < MAX_COLS; i++)
			lines[i][MAX_ROWS - 1] = 0;
		reDrawLines();
		x = 0;
		y = MAX_ROWS - 1;
		setCursorX(x);
		setCursorY(y);
		drawComandLine();

	}
}
/**	Copia todo lo que hay en el BUFFER DE PANTALLA (no en la placa de 
 * video) y lo vuelve a imprimir*/
void reDrawLines() {
	int i, j;
	k_clear_screen();
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
	putC(lines[x - 1][y]);
}

void onEscape() {
	shellStart();
	putChar('R');
}

/**	Cada vez que se presiona una tecla el kernel le avisa a esta 
 * instruccion. */
void shellKBInterrupt() {
	char c = getC();
	if (x < MAX_COLS) {
		if (c == 0x0f) {
			if (getCursorX() <= MAX_COLS - 4) {
				putTab();
				lines[x++][y] = c;
			}
		} else if (c == 0x39)
			putSpace();
		else {
			putChar(c);
		}
	}

}
