#include "shell.h"
#include "../include/defs.h"
#include "../include/kasm.h"
#include "libs/mcgio.h"
#include "libs/mcglib.h"
#include "libs/stdio.h"
#include "libs/string.h"
#include "drivers/video.h"
#include "software/nInLineFront.h"

int DIFF_TIME_HOURS=0;
int DIFF_TIME_MINUTES=0;
int currentHour=0;
int currentMinutes=0;

// Used for autocomplete.
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

// Handler for each key.
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
		else if (direction == -1 && currentCall->next == NULL) {
			currentCall = currentCall->next;
			return "";
		}
	}

	if (currentCall != NULL)
		return currentCall->name;
	return NULL;
}

// Function names
char* function_names[] = { "logout", "login", "ninline", "help", "cpuSpeed",
		"test", "clear", "ssh","changeHour", NULL };

// Functions
int ((*functions[])(int, char**)) = { logout, login, nInLineStart, printHelp,
		cpuSpeed, test, clear, ssh,changeHour, NULL };

// Tab callback for autocomplete.
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

// Shell startup
void shellStart() {

	printf("Murcielag O.S. is loading...\n");
	setTabCall(whenTabCalls);
	setArrowHit(onKey);

	double f = 2.0;
	f / 5.0;
	f / 10.0;
	f * 10;
	f - 2.0;

	_rdtsc();

	printf("\n     ***Mucielag O.S*** \n\n");
	printf("         (_    ,_,    _) \n");
	printf("         / `'--) (--'` \\ \n");
	printf("        /  _,-'\\_/'-,_  \\ \n");
	printf("       /.-'     \"     '-.\\ \n\n\n\n");

	setKeyboard(0);
	setKeyboard(1);
	
}

char* loggedUser = NULL;
char* command = NULL;
void shellMain() {
	while (1) {
		if (loggedUser == NULL)
			login(0, NULL);
		printf(loggedUser);
		int var = 0;
		printf(OSDEFST);
		printf(" ");
		
		command = getConsoleString(TRUE);
		int index = 0;
		if (command[0] != 0 && command[0] != '\n') {
			createCall(command);
			currentCall = NULL;
			for (index = 0; function_names[index] != NULL; ++index) {
				if (!strcmp(command, function_names[index]) && strlen(command)
						>= strlen(function_names[index])) {
					int n = 0;
					char** strs = sString(command, ' ', &n);
					functions[index](n, strs);
				}
			}
		}
	}
	return;
}

// "Logs in" a user just for fun and test
int login(int size, char** args) {
	if (loggedUser != NULL) {
		printf("You are already logged in as: %s\n", loggedUser);
	} else {
		do {
			printf("MurcielagOS login:");
			loggedUser = getConsoleString(FALSE);
		} while (loggedUser[0] == 0 || loggedUser[0] == '\n');

		printf(
				"Type `help cpuSpeed' to find out more about the function `cpuSpeed'.\n");
		printf("   Ortiz, Ezequiel\n");
		printf("   Pereyra, Cristian\n");
		printf("   Videla, Maximo\n");
	}
}
// "Logs out" a user just for fun and test
int logout(int size, char** args) {
	printf("\nBye bye %s\n", loggedUser);
	free(loggedUser);
	loggedUser = NULL;
}

// Secret sauce
int cpuSpeed(int size, char** args) {
	int precision = 0, ticks = 0, approx = 1;
	if (size > 1) {
		if (strcmp(args[1], "e") == 0)
			approx = 0;
	}
	if (size > 2) {
		precision = atoi(args[2]);
	}
	if (size > 3) {
		ticks = atoi(args[3]);
	}
	if (precision <= 0)
		precision = 1;
	if (ticks <= 2)
		ticks = 2;


	double* a = (double*)getFrequency(precision, ticks);


	if (approx) {
		int b = (int) *a;
		if (b % 5 >= 3)
			b = b - b % 5 + 5;
		else
			b = b - b % 5;
		printf("\nSpeed: %d Mhz\n", b);
	}
	else
	{
		printf("\nSpeed: %f Mhz\n", *a);
	}
}

// Helps teachers to understand a bit our mess, well, no
int printHelp(int size, char** args) {
	int found = 0, index = 0;

	char * command = NULL;
	if (size > 1) {
		command = args[1];
		for (index = 0; function_names[index] != NULL; ++index) {
			if (!strcmp(command, function_names[index]) && strlen(command)
					>= strlen(function_names[index])) {
				found = index;
			}
		}
	}

	if (!found) {
		printf(
				"MurcielagOS bash, version 1.0.0(1)-release (i686-pc-murcielago)\n");
		printf(
				"These shell commands are defined internally.  Type `help' to see this list.\n");
		printf(
				"Type `help cpuSpeed' to find out more about the function `cpuSpeed'.\n");
	} else {
		if (strcmp(command, "cpuSpeed") == 0) {
			printf(
					"Usage: cpuSpeed (r)? (numberofiterations) (numberofticks)\n");
			printf("numberofiterations is 1 by default\n");
			printf("numbeofticks is 2 by default (wastes 1 for synchrony)\n");
			printf(
					"\"e\" will make the result more exact, by not approximating\n");
			printf(
					"Only use the extra params if you don't get good precision\n");
		} else
			printf("Takes no parameters \n");
	}
}

// Test the breakable code
int test(int size, char** args) {

	printf("welcome to the test programme\n\n");
	printf("We are gonna test the following code:\n");

	char name[200];
	char surname[200];
	int age = 0;
	double height = 2.0;

	printf("char name[200];\nchar surname[200];\nint age = 0;\n");
	printf("double height = 0.0;\nprintf(\"please enter your name:\");\n");
	printf("scanf(\"%%s\",name);\n");
	printf("printf(\"please enter you age:\");\n");
	printf("scanf(\"%%d\",&age);\n");
	printf("printf(\"please enter you height:\");\n");
	printf("scanf(\"%%d\",&height);\n");
	printf(
			"printf(\"my name is:%%s i am %%d years old and %%d feet tall\\n\",name,age,height);\n");
	printf(
			"printf(\"please enter your name surname \\nfor example Bruce Wayne:\");\n");
	printf("scanf(\"%%s %%s\",name,surname);\n");
	printf(
			"printf(\"my name is %%s and my surname is %%s\\n\",name,surname);\n");

	printf("\nPress ENTER to begin the test");
	getchar();
	printf("\n\nplease enter your name:");
	scanf("%s", name);
	printf("please enter you age:");
	scanf("%d", &age);
	printf("please enter you height:");
	scanf("%f", &height);
	printf("my name is:%s i am %d years old and %f feet tall\n", name, age,
			height);
	printf("please enter your name surname \nfor example Bruce Wayne:");
	scanf("%s %s", name, surname);
	printf("my name is %s and my surname is %s\n", name, surname);

	printf("These lines should be splitted");
	int n = 0;
	char** strs = sString("These lines should be splitted\n", ' ', &n);
	int var = 0;
	for (var = 0; var < n; ++var) {
		printf("%s\n", strs[var]);
	}

	

}

// Just to have more functions in the autocomplete
int ssh(int size, char** args) {
	printf("Attempting to connect...\n");
	printf("Oooops we forgot our internals don't have any TCP/IP backend...\n");
	printf(
			"You'll have to wait for MurcielagOS 2.0 or maybe 11.0 to see this working\n");
	printf("Take a seat and wait!!!\n");
	printf("...\n");
	printf("...\n");
	printf("...\n");
	getchar();
	printf("Our autocomplete looked just empty so we made this :)\n");
	getchar();
}

// Clears the screen
int clear(int size, char** args) {
	clear_screen();
}
int changeHour(int size, char** args){
	
	int userHour,userMinutes;
	
	printf("Please enter the new hour \n -1 if you don't want to change it \n -2 if you want to restore the original value: \n");
	scanf("%d" , &userHour);
	printf("Please enter the new minutes \n -1 if you don't want to change it \n -2 if you want to restore the original value: \n");
	scanf("%d" , &userMinutes);
	
	

	if(userMinutes<0 || userMinutes>60){
		printf("Please enter a valid minutes: \n");
		changeHour(size, args);
		return;
	}
	if(userMinutes==-2){
		DIFF_TIME_MINUTES=0;
		return;
	}
	
	else if(userMinutes!=-1){
		DIFF_TIME_MINUTES=userMinutes-currentMinutes;
	}
	
	
	if( userHour<0 || userHour>24){
		printf("Please enter a valid hour! \n");
		changeHour(size, args);
		return;
	}
	if(userHour==-2){
		DIFF_TIME_HOURS=0;
	}
	else if(userHour!=-1){
	
		DIFF_TIME_HOURS=userHour-currentHour;
	}
	
	return;
}
		

	

	

	
void showHour(){
	
		unsigned int hour= _getHour();
		unsigned int minutes= _getMinutes();
		unsigned int seconds=_getSeconds();
		
		
		currentHour=toDecimal(hour);
		currentMinutes=toDecimal(minutes);
		seconds=toDecimal(seconds);
		
		
		hour = currentHour + DIFF_TIME_HOURS;
		minutes = currentMinutes + DIFF_TIME_MINUTES;
		
		
				
		if(minutes>60){
			hour++;
			minutes-=60;
		}
		else if(minutes<0){
			hour--;
			minutes=60-minutes;
		}
		if(hour>24){
			hour-=24;
		}
		else if(hour<0){
			hour=24-hour;
		}
		
	
		int x=getCursorX();
		int y=getCursorY();
		
		setCursorX(64);
		setCursorY(0);
		clearFirstLine();
		if(hour<10)
		printf("hora 0%d:",hour);
		else{
		printf("hora %d:",hour);
		}
		if(minutes<10){
		printf("0%d:",minutes);
		}
		else{
		printf("%d:",minutes);
		}
		printf("%d ",seconds);
		setCursorX(x);
		setCursorY(y);
}

int toDecimal(int value){
			value = ((value / 16) * 10) + (value & 0xf); 
}
