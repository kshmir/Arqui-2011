#include "shell.h"
#include "../include/defs.h"
#include "libs/mcgio.h"
#include "libs/stdio.h"
#include "libs/string.h"
#include "drivers/video.h"
#include "software/nInLineFront.h"

typedef struct {
	void* parent;
	void* next;
	char* name;
} ShellCall;

ShellCall* lastCall;
ShellCall* currentCall;

void createCall(char* command) {
	ShellCall* call = malloc(sizeof(ShellCall));
	char* comm = malloc(sizeof(char) * strlen(command) + 1);
	comm = strcpy(comm, command);
	if (lastCall != NULL)
		lastCall->next = call;
	call->parent = lastCall;
	call->name = comm;
	lastCall = call;
}

char* onKey(int direction) {
	if (currentCall == NULL)
		currentCall = lastCall;
	else {
		if (direction == 1 && currentCall->parent != NULL)
			currentCall = currentCall->parent;
		else if (direction == 1 && currentCall->parent != NULL)
			currentCall = currentCall;
		else if (direction == -1 && currentCall->next != NULL)
			currentCall = currentCall->next;
		else if (direction == -1 && currentCall->next == NULL)
					return "";
	}

	if (currentCall != NULL)
		return currentCall->name;
	return NULL;
}

char* function_names[] = { "logout", "login", "ninline", "help","cpuSpeed","test","clear", NULL };

int ((*functions[])(int, char*)) = { logout, login, nInLineStart, printHelp, cpuSpeed, test, clear, NULL };

char* whenTabCalls(char* s) {
	int startX = getCursorX();
	int startY = getCursorY();
	int desp = 0, i = 0, c = 0, ind;
	VIDEO_MODE_INFO * mode = getVideoMode();
	clear_screen_topdown();
	for (i = 0; function_names[i] != NULL; ++i) {
		if (strlen(s) > 0 && strstr(function_names[i], s) == function_names[i]) {
			c++;
			ind = i;
		}
	}
	if (c == 1) {
		return function_names[ind] + (strlen(s) - 1);
	} else if (c > 1) {
		desp += mcg_printf("\n");
		for (i = 0; function_names[i] != NULL; ++i) {
			if (strlen(s) > 0 && strstr(function_names[i], s)
					== function_names[i])
				desp += mcg_printf("%s\t", function_names[i]);
		}

	}

	if (getCursorY() == mode->height - 1) {
		if (startY != getCursorY())
			setCursorY(getCursorY() - desp);
		else
			setCursorY(startY - desp);
	} else
		setCursorY(startY);
	setCursorX(startX);
	return NULL;
}

void shellStart() {
	char * hola;

	printf("Murcielag O.S. is loading...\n");
	setTabCall(whenTabCalls);
	setArrowHit(onKey);

	printf("\n     ***Mucielag O.S*** \n\n\n\n");
	printf("         (_    ,_,    _) \n");
	printf("         / `'--) (--'` \\ \n");
	printf("        /  _,-'\\_/'-,_  \\ \n");
	printf("       /.-'     \"     '-.\\ \n\n\n\n");
}

char* loggedUser = NULL;
char* command = NULL;
void init() {
	while (1) {
		if (loggedUser == NULL)
			login(0, NULL);
		printf(loggedUser);
		printf(OSDEFST);
		printf(" ");
		command = getConsoleString(TRUE);
		int index = 0;
		if (command[0] != 0 && command[0] != '\n') {
			createCall(command);
			currentCall = NULL;
			for (index = 0; function_names[index] != NULL; ++index) {
				if (!strcmp(command, function_names[index])) {

					functions[index](0, NULL);
				}
			}
		}
	}
	return;
}

int login(int size, char* args) {
	if (loggedUser != NULL) {
		printf("You are already logged in as: %s\n", loggedUser);
	} else
		do {
			printf("MurcielagOS login:");
			loggedUser = getConsoleString(FALSE);
		} while (loggedUser[0] == 0 || loggedUser[0] == '\n');
}

int logout(int size, char* args) {
	printf("\nBye bye %s\n", loggedUser);
	free(loggedUser);
	loggedUser = NULL;
}

void cpuSpeed() {
	double* a = getFrequency();
	int b = (*a);
	printf("\nspeed: %d Mhz\n", b);
}

void printHelp(int size, char* args) {
	printf("MurcielagOS bash, version 1.0.0(1)-release (i686-pc-murcielago)\n");
	printf(
			"These shell commands are defined internally.  Type `help' to see this list.\n");
	printf("Type `name help' to find out more about the function `name'.\n");
}

void test(){
	
	
	printf("welcome to the test programme\n\n");
	printf("We are gonna test the following code:\n");
	
	
	char name[200];
	char surname[200];
	int age = 0;
	double height = 0.0;
	
	
	printf("char name[200];\nchar surname[200];\nint age = 0;\n");
	printf("double height = 0.0;\nprintf(\"please enter your name:\");\n");
	printf("scanf(\"%%s\",name);\n");
	printf("printf(\"please enter you age:\");\n");
	printf("scanf(\"%%d\",&age);\n");
	printf("printf(\"please enter you height:\");\n");
	printf("scanf(\"%%f\",&height);\n");
	printf("printf(\"my name is:%%s i am %%d years old and %%f feet tall\\n\",name,age,height);\n");
	printf("printf(\"please enter your name surname \\nfor example Bruce Wayne:\");\n");
	printf("scanf(\"%%s %%s\",name,surname);\n");
	printf("printf(\"my name is %%s and my surname is %%s\\n\",name,surname);\n");
	
	printf("\nPress ENTER to begin the test");
	getchar();
	printf("\n\nplease enter your name:");
	scanf("%s",name);
	printf("please enter you age:");
	scanf("%d",&age);
	printf("please enter you height:");
	scanf("%f",&height);
	printf("my name is:%s i am %d years old and %f feet tall\n",name,age,height);
	printf("please enter your name surname \nfor example Bruce Wayne:");
	scanf("%s %s",name,surname);
	printf("my name is %s and my surname is %s\n",name,surname);
	
}

void clear(){
	clear_screen();
 }

