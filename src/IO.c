#include "../src/IO.h"
#include "../include/defs.h"
char charBuffer[BUFFER_SIZE];
int charBufferPointer = -1;

int style = 0x07;

// TODO: Bitshift all of these.
/** Num lock's flag */
char numLock = 0;
/** Caps lock's flag */
char capsLock = 0;
/** Left shift's flag */
char lShift = 0;
/** Right shift's flag */
char rShift = 0;
/** Left control's flag */
char lCtrl = 0;
/** Right control's flag */
char rCtrl = 0;
/** Left Alt's flag */
char lAlt = 0;
/** Right Alt's flag */
char rAlt = 0;
/** X axis' cursor */
int cursorX = 0;
/** Y axis' cursor */
int cursorY = 0;

// TODO: LOW ense–arle a maxi que recive es con B. #jokewestill<3u
void pushC(char c) {
	if (charBufferPointer >= BUFFER_SIZE - 1)
		charBufferPointer = BUFFER_SIZE - 2;
	charBuffer[++charBufferPointer] = c;
}

void incrementCursor() {
	if (cursorX >= MAX_COLS) {
		setCursorX(0);
		if (cursorY >= MAX_ROWS)
			setCursorY(0);
		else
			setCursorY(getCursorY() + 1);
		return;
	}
	setCursorX(getCursorX() + 1);
}
void decrementCursor() {
	if (cursorX < 1) {
		if (cursorY < 1) {
			setCursorY(0);
			setCursorX(0);
		} else {
			setCursorY(getCursorY() - 1);
			setCursorX(MAX_COLS);
		}
		return;
	}
	setCursorX(getCursorX() - 1);
}

void controlKey(char scancode) {
	// TODO: MID Defines for all the scan codes!
	if (scancode == 42) //SHIFT IZQ
		lShift = 1;
	else if (scancode == 54) //054 SHIFT DER
		rShift = 1;
	else {

		if (scancode == 170)
			lShift = 0;
		else if (scancode == 0xb6)
			rShift = 0;
		else if (scancode == 0x1c)
			enter();
		else if (scancode == 0x38)
			lAlt = 1;
		else if (scancode == 0xB8)
			lAlt = 0;
		else if (scancode == 0x1D)
			lCtrl = 1;
		else if (scancode == 0x9D)
			lCtrl = 0;
		else if (scancode == 0x81) //release esc
			escRelease();
		else if (scancode == 0x45)
			numLock = numLock ? 0 : 1;
		else if (scancode == 0x0E)
			backSpace();
		else if (scancode == 0x3A)
			capsLock = capsLock ? 0 : 1;
		else if (scancode == 0x39) { //space
			pushC(scancode);
			shellKBInterrupt();
		} else if (scancode == 0x0f) {
			pushC(scancode);
			shellKBInterrupt();
		}
	}
}

void escRelease() {
	onEscape();
}
void removeLastC() {
	// TODO: LOW Can we improve this?
	decrementCursor();
	putC(' ');
	decrementCursor();
}

int capsOn() {
	return capsLock;
}

int isCapital() {
	return ((lShift || rShift) && !capsLock) || capsLock && !(lShift || rShift);
}
int isShifted() {
	return lShift || rShift;
}

/**	Esta funcion es ejecutada por controlKey cada vez que la tecla enter 
 * es presionada*/
void enter() {
	nextRow();
}

char getC() {
	if (charBufferPointer < 0)
		return 0;
	return charBuffer[charBufferPointer--];
}

void putC(char c) {
	char a[] = { c, style };
	int_80(WRITE, STDOUT, a, 2);
	incrementCursor();
}

int getCursorX() {
	return cursorX;
}
int getCursorY() {
	return cursorY;
}
void setCursorX(int x) {
	if (x >= 0 && x <= MAX_COLS)
		cursorX = x;
	setVideoPos((MAX_COLS * cursorY + cursorX) * 2);
}
void setCursorY(int y) {
	if (y >= 0 && y <= MAX_ROWS)
		cursorY = y;
	setVideoPos((MAX_COLS * cursorY + cursorX) * 2);
}

void moveCursorToStart() {
	setCursorX(0);
	setCursorY(0);
}
