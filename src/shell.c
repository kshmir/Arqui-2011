#include "shell.h"
#include "../include/defs.h"
#include "libs/mcgio.h"
#include "libs/stdio.h"
#include "libs/string.h"
#include "drivers/video.h"

char* function_names[] = { "logout", "login", NULL };

int ((*functions[])(int, char*)) = { logout, login, NULL };

void whenTabCalls(char* s) {
	int startX = getCursorX();
	int startY = getCursorY();
	int desp = 0, i = 0;
	VIDEO_MODE_INFO * mode = getVideoMode();
	clear_screen_topdown();



	desp += mcg_printf("\n");
	for (i = 0; function_names[i] != NULL; ++i) {
		if (strlen(s)  > 0 && strstr(function_names[i],s) != NULL)
			desp += mcg_printf("%s\t", function_names[i]);
	}


	if (getCursorY() == mode->height - 1) {
		if (startY != getCursorY())
			setCursorY(getCursorY() - desp);
		else
			setCursorY(startY - desp);
	} else
		setCursorY(startY);
	setCursorX(startX);
}

void shellStart() {
	printf("Murcielag O.S. is loading...\n");
	setTabCall(whenTabCalls);
}

char* loggedUser = NULL;

void init() {
	while (1) {
		char* command;
		if (loggedUser == NULL)
			login(0, NULL);
		printf(loggedUser);
		printf(OSDEFST);
		printf(" ");
		command = getConsoleString(TRUE);
		int index = 0;
		for (index = 0; function_names[index] != NULL; ++index) {
			if (!strcmp(command, function_names[index]))
				functions[index](0,NULL);
		}
	}
	return;
}

int login(int size, char* args) {
	if (loggedUser != NULL)
		printf("You are already logged as %s\n", loggedUser);
	else
	do {
		printf("MurcielagOS login:");
		loggedUser = getConsoleString(FALSE);
	} while (loggedUser[0] == 0);
}

int logout(int size, char* args) {
	printf("\nBye bye %s\n", loggedUser);
	free(loggedUser);
	loggedUser = NULL;
}

void printHelp() {
	printf("Murcielago bash, version 1.0.0(1)-release (i686-pc-murcielago)\n");
	printf(
			"These shell commands are defined internally.  Type `help' to see this list.\n");
	printf("Type `help name' to find out more about the function `name'.\n");
	printf("Use `info bash' to find out more about the shell in general.\n\n");
}

