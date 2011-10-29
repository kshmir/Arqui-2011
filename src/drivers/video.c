/*
 * video.c
 *
 *  Created on: May 11, 2011
 *      Author: cristian
 */

#include "video.h"
#include "../../include/defs.h"
#include "../../include/kasm.h"
#include "../libs/stdlib.h"

int defaultStyle = 0x07;

VIDEO_MODE_INFO* current_video_mode;

VIDEO_MODE_INFO* getVideoMode() {
	return current_video_mode;
}
// For future use.
static VIDEO_MODE_INFO* buildVideoMode(int height, int width, int cursorX,
		int cursorY, int cursorEnabled, int textMode);

// Starts default video.
void initVideo() {
	int i = 0;
	VIDEO_MODE_INFO* default_video = NULL;
	default_video = buildVideoMode(25, 78, 1, 10, 10, 1);
	current_video_mode = default_video;

	clear_screen();
}

// For future use, builds a given video mode.
static VIDEO_MODE_INFO* buildVideoMode(int height, int width, int cursorX,
		int cursorY, int cursorEnabled, int textMode) {
	VIDEO_MODE_INFO* video = NULL;
	int i = 0;
	video = (VIDEO_MODE_INFO*) malloc(sizeof(VIDEO_MODE_INFO));
	video->height = height;
	video->width = width;
	video->curX = cursorX;
	video->curY = cursorY;
	video->cursorEnabled = cursorEnabled;
	video->textMode = textMode;
	video->shell = (SHELL_INFO*) malloc(sizeof(SHELL_INFO));
	video->shell->screen = (char**) malloc(sizeof(char**) * width);
	for (i = 0; i < width; i++) {
		video->shell->screen[i] = (char*) malloc(sizeof(char*) * height);
	}
	video->shell->style = (char**) malloc(sizeof(char**) * width);
	for (i = 0; i < width; i++) {
		video->shell->style[i] = (char*) malloc(sizeof(char*) * height);
	}
	return video;
}

// Puts a character to stdout
void putC(char c) {
	char a[] = { c, defaultStyle };
	_write(STDOUT,a,2);
	incrementCursor();
}

int getCursorX() {
	return current_video_mode->curX;
}
int getCursorY() {
	return current_video_mode->curY;
}
void setCursorX(int x) {
	if (x >= 0 && x <= current_video_mode->width) {
		current_video_mode->curX = x;
		setVideoPos(
				(current_video_mode->width * current_video_mode->curY
						+ current_video_mode->curX) * 2);
	}
}
void setCursorY(int y) {
	if (y >= 0 && y <= current_video_mode->height) {
		current_video_mode->curY = y;
		setVideoPos(
				(current_video_mode->width * current_video_mode->curY
						+ current_video_mode->curX) * 2);
	}
}

void moveCursorToStart() {
	setCursorX(0);
	setCursorY(1);
}

void incrementCursor() {
	if (getCursorX() >= current_video_mode->width) {
		setCursorX(0);
		if (getCursorY() >= current_video_mode->height - 1)
		{
			newLine(); // This is not the happiest of the fixes... We can do better
			setCursorY(current_video_mode->height - 1);
		}
		else
			setCursorY(getCursorY() + 1);
		return;
	}
	setCursorX(getCursorX() + 1);
}
void decrementCursor() {
	if (getCursorX() < 1) {
		if (getCursorY() < 1) {
			setCursorY(0);
			setCursorX(current_video_mode->width);
		} else {
			setCursorY(getCursorY() - 1);
			setCursorX(current_video_mode->width);
		}
		return;
	}
	setCursorX(getCursorX() - 1);
}

void clear_screen() {
	int i = 320;
	moveCursorToStart();
	setCursor(FALSE);
	while (i++ < (current_video_mode->width * (current_video_mode->height))) {
		putC(' ');
	}
	setCursor(TRUE);
	moveCursorToStart();
}

// Clears the screen from the given cursor to the end of the page.
// And rolls the cursor back.
void clear_screen_topdown() {
	int i = 0;
	int x = getCursorX();
	int y = getCursorY();
	setCursor(FALSE);
	while (i++ < (current_video_mode->width * (current_video_mode->height
			- y)) - x) {
		putchar(' ');
	}
	setCursor(TRUE);
	setCursorX(x);
	setCursorY(y);
}
