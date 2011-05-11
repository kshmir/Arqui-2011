#include "../src/IO.h"
#include "../include/defs.h"
char charBuffer[BUFFER_SIZE];
int charBufferPointer=-1;
char style=0x07;
char numLock=0;
char capsLock=0;
char lShift=0;
char rShift=0;
char lCtrl=0;
char rCtrl=0;
char lAlt=0;
char rAlt=0;
int cursorX=0;
int cursorY=0;

/**	Almacena todos los caracteres que recive en un buffer y los devuelve
 *  a medida que se los piden con getC()	*/
void pushC(char c){
	if(charBufferPointer>=BUFFER_SIZE-1)
		charBufferPointer=BUFFER_SIZE-2;
	charBuffer[++charBufferPointer]=c;
	}
/** Incrementa el cursor de la placa de video en 1 posicion */
void incrementCursor(){
	if(cursorX>=MAX_COLS){
		setCursorX(0);
		if(cursorY>=MAX_ROWS)
			setCursorY(0);
		else
			setCursorY(getCursorY()+1);
		return;
	}
	setCursorX(getCursorX()+1);
}
/** Decrementa el cursor de la placa de video en 1 posicion */
void decrementCursor(){
	if(cursorX<1){
		if(cursorY<1){
			setCursorY(0);
			setCursorX(0);
		}else{
			setCursorY(getCursorY()-1);
			setCursorX(MAX_COLS);
		}
		return;
	}
	setCursorX(getCursorX()-1);
}

/**	Recibe como parametro todos los scancodes que no corresponden a una 
 * tecla y segun la tecla a la que le corresponda la toma y cambia el 
 * estado del shift, etc	*/
void controlKey(char scancode){
	if(scancode == 42) //SHIFT IZQ
		lShift=1;
	else if(scancode == 54) //054 SHIFT DER
		rShift=1;
	else{
		lShift=rShift=0; 
	if (scancode == 0xaa)
		lShift=0;
	else if(scancode == 0xb6)
		rShift=0;
	else 
	if(scancode == 0x1c)
		enter();
	else if(scancode == 0x38)
		lAlt=1;
	else if(scancode == 0xB8)
		lAlt=0;
	else if(scancode == 0x1D)
		lCtrl=1;
	else if(scancode == 0x9D)
		lCtrl=0;
	else if(scancode == 0x81) //release esc
		escRelease();
	else if(scancode == 0x45)
		numLock=numLock?0:1;
	else if(scancode == 0x0E)
		backSpace();
	else if(scancode == 0x3A)
		capsLock=capsLock?0:1;
	else if(scancode == 0x39){ //space
		pushC(scancode);
		shellKBInterrupt();
	}else if(scancode == 0x0f){
		//putC('	');
		pushC(scancode);
		shellKBInterrupt();
		}
	}
}
/**	Esta funcion es ejecutada por controlKey cada vez que la tecla esc 
 * es liberada*/
void escRelease(){
	onEscape();
	}
/**	Borra el caracter ubicado una posicion anterior al cursor y deja el 
 * cursor en dicha posicion*/
void removeLastC(){
	decrementCursor();
	putC(' ');
	decrementCursor();
	}
	
int capsOn(){
	return capsLock;
	}
	
/** Devuelve true si algun shift se encuentra presionado o si el capLock
 *  se encuentra activo y devuelve false si ambos se encuentran 
 * activados*/
int isCapital(){
	return ((lShift || rShift) && !capsLock) || capsLock && !(lShift || rShift);
	}
/**	retorna si alguno de los dos shift se encuentran apretados*/
int isShift(){
	return lShift || rShift;
	}

/**	Esta funcion es ejecutada por controlKey cada vez que la tecla enter 
 * es presionada*/
void enter(){
	nextRow();
	}

/** retorna el ultimo caracter recibido */
char getC(){
	if(charBufferPointer<0)
		return 0;
	return charBuffer[charBufferPointer--];
	}

/**	Llama a la interrupcion int 80 y pide que se escriba en STDOUT el 
 * caracter recibido seguido del valor del estilo. Luego incrementa 
 * el cursor*/
void putC(char c){
	
	char a[]={c,style};
	
	int_80 (WRITE, STDOUT, a, 2 );
	incrementCursor();
}

int getCursorX(){
	return cursorX;
	}
int getCursorY(){
	return cursorY;
	}
	
/**	Setea la posicion del cursor horizontal de la pantalla de video 
 * logica y luego le pide al kernel que actualice el puntero efectivo de
 *  la placa de video*/
void setCursorX(int x){
	if(x>=0 && x<=MAX_COLS)
		cursorX=x;
	setVideoPos((MAX_COLS*cursorY+cursorX)*2);
	}
	
/**	Setea la posicion del cursor de la pantalla de video logica y luego 
 * le pide al kernel que actualice el puntero efectivo de la placa de 
 * video*/
void setCursorY(int y){
	if(y>=0 && y<=MAX_ROWS)
		cursorY=y;
	setVideoPos((MAX_COLS*cursorY+cursorX)*2);
	}	

void moveCursorToStart(){
	setCursorX(0);
	setCursorY(0);
	}
