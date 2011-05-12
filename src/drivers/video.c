/*
 * video.c
 *
 *  Created on: May 11, 2011
 *      Author: cristian
 */

#include "video.h"
#include "../../include/defs.h"
#include "../libs/stdlib.h"

int defaultStyle = 0x07;

VIDEO_MODE_INFO* current_video_mode;

static VIDEO_MODE_INFO* buildVideoMode(int height, int width, int cursorX,
		int cursorY, int cursorEnabled, int textMode);

void initVideo() {
	int i = 0;
	VIDEO_MODE_INFO* default_video = NULL;
	default_video = buildVideoMode(80, 25, 1, 10, 10, 1);
	current_video_mode = default_video;
	clear_screen();
	int cx = 0;
	int cy = 10;
	printf("Ancho pantalla: %d\n", cx);
	printf("Alto  pantalla: %d\n", cy);
	getchar();
}

static VIDEO_MODE_INFO* buildVideoMode(int height, int width, int cursorX,
		int cursorY, int cursorEnabled, int textMode) {
	VIDEO_MODE_INFO* video = NULL;
	int i = 0;
	video = (VIDEO_MODE_INFO*) malloc(video, sizeof(VIDEO_MODE_INFO));
	video->height = height;
	video->width = width;
	video->curX = cursorX;
	video->curY = cursorY;
	video->cursorEnabled = cursorEnabled;
	video->textMode = textMode;
	video->shell = (SHELL_INFO*) malloc(video->shell, sizeof(SHELL_INFO));
	video->shell->screen = (char**) malloc(video->shell->screen,
			sizeof(SHELL_INFO) * width);
	for (i = 0; i < width; i++) {
		video->shell->screen[i] = (char*) malloc(video->shell->screen[i],
				sizeof(SHELL_INFO) * height);
	}
	video->shell->style = (char**) malloc(video->shell->style,
			sizeof(SHELL_INFO) * width);
	for (i = 0; i < width; i++) {
		video->shell->style[i] = (char*) malloc(video->shell->style[i],
				sizeof(SHELL_INFO) * height);
	}
	return video;
}

void putC(char c) {
	char a[] = { c, defaultStyle };
	// TODO: Fix int_80 call!!!
	int_80(WRITE, STDOUT, a, 2);
	incrementCursor();
}

int getCursorX() {
	return current_video_mode->curX;
}
int getCursorY() {
	return current_video_mode->curY;
}
void setCursorX(int x) {
	if (x >= 0 && x <= current_video_mode->width)
		current_video_mode->curX = x;
	setVideoPos(
			(current_video_mode->width * current_video_mode->curY
					+ current_video_mode->curX) * 2);
}
void setCursorY(int y) {
	if (y >= 0 && y <= current_video_mode->height)
		current_video_mode->curY = y;
	setVideoPos(
			(current_video_mode->width * current_video_mode->curY
					+ current_video_mode->curX) * 2);
}

void moveCursorToStart() {
	setCursorX(0);
	setCursorY(0);
}

void incrementCursor() {
	if (getCursorX() >= current_video_mode->width) {
		setCursorX(0);
		if (getCursorY() >= current_video_mode->height)
			setCursorY(0);
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
			setCursorX(0);
		} else {
			setCursorY(getCursorY() - 1);
			setCursorX(current_video_mode->width);
		}
		return;
	}
	setCursorX(getCursorX() - 1);
}

void clear_screen() {
	int i = 0;
	moveCursorToStart();
	while (i++ < (current_video_mode->width * (current_video_mode->height + 1))) {
		putC(' ');
	}
	moveCursorToStart();
}
