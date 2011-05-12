/*
 * video.c
 *
 *  Created on: May 11, 2011
 *      Author: cristian
 */

#include "video.h"
#include "../../include/defs.h"

/** X axis' cursor */
int cursorX = 0;
/** Y axis' cursor */
int cursorY = 0;
int style = 0x07;

void putC(char c) {
	char a[] = { c, style };
	// TODO: Fix int_80 call!!!
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

void clear_screen() {
	int i = 0;
	moveCursorToStart();
	while (i++ < (MAX_COLS * (MAX_ROWS + 1))) {
		putC(' ');
	}
	moveCursorToStart();
}
