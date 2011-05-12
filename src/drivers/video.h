/*
 * video.h
 *
 *  Created on: May 11, 2011
 *      Author: cristian
 */

#ifndef VIDEO_H_
#define VIDEO_H_

#define MAX_COLS 80
#define MAX_ROWS 25
#define VIDEO 0xb8000


void initVideo();
void setVideoMode();
void setVideoMode();


/** Increment's the video card's cursor position */
void incrementCursor();
/** Decrements's the video card's cursor position */
void decrementCursor();

int getCursorX();

int getCursorY();

void setCursorX(int x);
void setCursorY(int y);

void moveCursorToStart();

/**
 * Calls INT80 and prompts a write of c with it's style value
 * Then it increment's the cursor
 */
void putC(char c);

void clear_screen();

#endif /* VIDEO_H_ */
