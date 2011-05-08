#include "../src/IO.h"
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

void pushC(char c){
	if(charBufferPointer>=BUFFER_SIZE-1)
		charBufferPointer=BUFFER_SIZE-2;
	charBuffer[++charBufferPointer]=c;
	}

void incrementCursor(){
	if(cursorX>=MAX_COLS){
		cursorX=0;
		if(cursorY>=MAX_ROWS)
			cursorY=0;
		else
			cursorY++;
		return;
	}
	cursorX++;
}

void decrementCursor(){
	if(cursorX<1){
		if(cursorY<1){
			cursorY=0;
			cursorX=0;
		}else{
			cursorY-=1;
			cursorX=MAX_COLS;
		}
		return;
	}
	cursorX-=1;
}

void controlKey(char scancode){
	if(scancode == 42) //SHIFT IZQ
		lShift=1;
	else if(scancode == 54) //054 SHIFT DER
		rShift=1;
	else{
		lShift=rShift=0; 
	//if (scancode == 0xaa)
	//	lShift=0;
	//else if(scancode == 0xb6)
	//	rShift=0;
	//else 
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
	else if(scancode == 0x39)
		putC(' ');
	else if(scancode == 0x0f)
		putC('	');
	}
}

void escRelease(){
	return;
	}

void backSpace(){
	decrementCursor();
	putC(' ');
	decrementCursor();
	}
	
int capsOn(){
	return capsLock;
	}
int isCapital(){
	return ((lShift || rShift) && !capsLock) || capsLock && !(lShift || rShift);
	}
int isShift(){
	return lShift || rShift;
	}
void enter(){
	cursorX=0;
	if(cursorY<MAX_ROWS)
		cursorY++;
	else 
		cursorY=0;
	}

char getC(){
	if(charBufferPointer<0)
		return 0;
	return charBuffer[charBufferPointer--];
	}

void putC(char c){
	char *video = (char*) VIDEO;
	int a=(MAX_COLS*cursorY+cursorX)*2;
	video[a] = c;
	video[a+1] = style;
	incrementCursor();
}
