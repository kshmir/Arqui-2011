/*
 * video.h
 *
 *  Created on: May 11, 2011
 *      Author: cristian
 */

#ifndef VIDEO_H_
#define VIDEO_H_

#define VIDEO 0xb8000
//AGREGADO POR MI
#define DEFAULTSTYLE 0x07
#include "../../include/defs.h"


void initVideo();
void setVideoMode(VIDEO_MODE_INFO* vid);
VIDEO_MODE_INFO* getVideoMode();


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

void setColor(char colour);

#endif /* VIDEO_H_ */
