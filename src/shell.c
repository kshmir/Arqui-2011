#include "shell.h"
#include "../include/defs.h"
#include "../include/kasm.h"
#include "libs/mcgio.h"
#include "libs/mcglib.h"
#include "libs/stdio.h"
#include "libs/string.h"
#include "drivers/video.h"
#include "drivers/sound.h"
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

		"test", "clear", "ssh", "confColor", "changeKeyboard", "changeHour", "morse", "tryMalloc", "tryCalloc", "tryFree",
		
		"tryPrintPages", "tryPrintPage", "tryPrintMap", "tryPrintBlock", "tryWrite", "tryRealloc", NULL };

// Functions
int ((*functions[])(int, char**)) = { logout, login, nInLineStart, printHelp,
		cpuSpeed, test, clear, ssh, confColor, changeKeyboard, changeHour, morse, tryMalloc,tryCalloc, tryFree,
		tryPrintPages, tryPrintPage, tryPrintMap, tryPrintBlock, tryWrite, tryRealloc, NULL};

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
				desp += mcg_printf("%s\n", function_names[i]);
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
	
	
}

char* loggedUser = NULL;
char* command = NULL;
void shellMain() {
	initPaging();
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
		printf("   Reznik, Luciana\n");
		printf("   Mesa Alcorta, Victoria\n");
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
			
		printf("Type `help changeKeyboard' to find out more about the function `changeKeyboard'.\n");
		printf("Type `help changeHour' to find out more about the function `changeHour'.\n");
		printf("Type `help confColor' to find out more about the function `confColor'.\n");
		printf("Type `help clear' to find out more about the function `clear'.\n");
		printf("Type `help morse' to find out more about the function `morse'.\n");
		printf("Type `help tryMalloc' to find out more about the function `tryMalloc'.\n");
		printf("Type `help tryCalloc' to find out more about the function `tryCalloc'.\n");
		printf("Type `help tryFree' to find out more about the function `tryFre'.\n");
		printf("Type `help tryPrintfPages' to find out more about the function `tryPrintPages'.\n");
		printf("Type `help tryPrintfPage' to find out more about the function `tryPrintPage'.\n");
		printf("Type `help tryPrintfMap' to find out more about the function `tryPrintMap'.\n");
		printf("Type `help tryPrintfBlock' to find out more about the function `tryPrintBlock'.\n");
		printf("Type `help tryWrite' to find out more about the function `tryWrite'.\n");

		
		
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
		}
		if( strcmp(command, "changeKeyboard")==0){
			printf("Usage: changeKeyboard ES? EN? \n");
			printf("ES will change the keyboard configuration to a Spanish one.\n");
			printf("EN will change the keyboard configuration to a English one. \n");
			printf("If no parametters are given a menu will be shown. \n");
		}
		if( strcmp(command, "changeHour")==0){
			printf("Usage: changeHour r? s? \n");
			printf("r will restore the clock to it's original values\n");
			printf("s will ask you to enter the new values for the clock. \nIf a wrong value is typed it will be 0 as default \n");
			printf("If no parametters are given a menu will be shown. \n");
		}
		if( strcmp(command, "confColor")==0){
			printf("Usage: changeHour n1? n2? \n");
			printf("n1 will change the font color to the selected one\n");
			printf("n2 will change the background color to the selected one \n If a wrong value is typed it will show the menu for that parameter\n");
			printf("The quantity of supported  colors depends on the computer");
			printf("If no parametters are given a menu will be shown. \n");
		}
			if( strcmp(command, "clear")==0){
			printf("Usage: clear it clears the screen \n");
			
		}
		if(strcmp(command,"morse")==0){
			
			printf("Usage: morse wordToTranslate \n");
			printf("morse will traslate wordToTranslate to morse code through the speaker");
			printf("If no parameters are given nothing will happen");
		}
		
		if(strcmp(command,"tryMalloc")==0){
			
			printf("Usage: tryMalloc size \n");
			printf("tryMalloc allocates unused space for an object whose size in bytes is\n");
			printf("specified by size and whose value is unspecified.\n");
			
		}
		if(strcmp(command,"tryRealloc")==0){
			
			printf("Usage: tryRealloc pointer size \n");
			printf("tryRealloc reallocates a used space from a pointer into a new one\n");
			
			
		}
		if(strcmp(command,"tryCalloc")==0){
			
			printf("Usage: tryCalloc size \n");
			printf("tryCalloc allocates unused space for an \narray of nelem elements each of whose\n"); 
			printf("size in bytes is elsize. The space shall \nbe initialized to all bits 0.\n");
			
		}
		if(strcmp(command,"tryFree")==0){
			
			printf("Usage: tryFree pointer \n");
			printf("tryFree release memory back to the heap, previously allocated\n"); 
		}				
		if(strcmp(command,"tryPrintPages")==0){
			
			printf("Usage: tryPrintPages\n");
			printf("tryPrintPages prints pages pointers\nand their used memory size\n"); 
		}				

		if(strcmp(command,"tryPrintPage")==0){
			
			printf("Usage: tryPrintPage pointer\n");
			printf("tryPrintPage prints a page showing blocks\n of used and free memory\n"); 
		}
		
		if(strcmp(command,"tryPrintMap")==0){
			
			printf("Usage: tryPrintMap pointer\n");
			printf("tryPrintMap prints the allocated block\n pointers and their size\n"); 
		}
		
		if(strcmp(command,"tryPrintBlock")==0){
			
			printf("Usage: tryPrintBlock pointer\n");
			printf("tryPrintBlock prints the memory\n"); 
		}
		
		if(strcmp(command,"tryWrite")==0){
			
			printf("Usage: tryWrite pointer character_to_write\n");
			printf("tryWrite write the character_to_write in te pointer\n");
			printf("if the pointer was allocated previously\n");
		}
		
		
		
		}	
	//	 else
	//		printf("Takes no parameters \n");
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
	printf("scanf(\"%%f\",&height);\n");
	printf(
			"printf(\"my name is:%%s i am %%d years old and %%f feet tall\\n\",name,age,height);\n");
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

int confColor(int size, char** args){
		int i=1;
		int font= -1;
		int back= -1;
		int flag = 0;
		if(size == 3){
			font=atoi(args[1]);
			back=atoi(args[2]);
		}else if(size == 2){
			font=atoi(args[1]);
		}	
		while(font<0 || font>8){
			
		printf("0 -> BLACK   4->RED          				\n");
		printf("1 -> BLUE    5->MAGENTA      			    \n");
		printf("2 -> GREEN   6->BROWN         				\n"); 
		printf("3 -> CYAN    7->LIGHTGRAY      				\n");
		printf("8->DARKGRAY									\n");
		font=getint("Please enter a font color:");
		} 
		while(back<0 || back>8 || font==back){
			
		printf("0 -> BLACK   4->RED          				\n");
		printf("1 -> BLUE    5->MAGENTA      			    \n");
		printf("2 -> GREEN   6->BROWN         				\n"); 
		printf("3 -> CYAN    7->LIGHTGRAY      				\n");
		printf("8->DARKGRAY									\n");	
		back=getint("Please enter a back color:");
		} 
		setColor(back*16 + font);
		clear(0,NULL);
}	
	
int changeHour(int size, char** args){
	
	int ret = -1;
	
	if(size > 1){
		
		if( strcmp( args[1] , "r")== 0){
			 printf("->restored \n");
			 ret = 1;
			
		}
		if( strcmp(args[1],"s")== 0){
			printf("->setting \n",args[1]);
			ret = 0;
		}	
	}
	while(ret < 0 || ret > 1){
		
		ret = getint("Please select \n1-if you whant to set the clock \n2-if you want to restore the original values \n")-1;
		
	}
	if(ret==1){
		restoreHour();
		return;
	}
	if(ret==0){
	setHour();	
	return;
	}
}
	
void setHour(){
	
	int userHour,userMinutes;
	


	printf("Please enter the new hour \n");
	scanf("%d" , &userHour);
	printf("Please enter the new minutes \n");
	scanf("%d" , &userMinutes);
	
	

	if(userMinutes<0 || userMinutes>59){
		printf("Please enter a valid minutes between 0 and 59! \n");
		setHour();
		return;
	}

	else{
	DIFF_TIME_MINUTES=userMinutes-currentMinutes;
	}
	
	if( userHour<0 || userHour>24){
		printf("Please enter a valid hour betwen 0 and 24! \n");
		setHour();
		return;
	}
	else{
		DIFF_TIME_HOURS=userHour-currentHour;
	}
	
	return;
}

void restoreHour(){
		DIFF_TIME_HOURS=0;
		DIFF_TIME_MINUTES=0;
}
		
int changeKeyboard(int size ,char** args){
	
	int ret = -1;
	
	if(size > 1){
		
		if( strcmp( args[1] , "EN")== 0){
			 printf("->ingles %s\n",args[1]);
			 ret = EN;
			
		}
		if( strcmp(args[1],"ES")== 0){
			printf("->espanol %s\n",args[1]);
			ret = ES;
		}	
	}
	/* EN is the first language code and ES is the last language code*/
	while(ret < EN || ret > ES ){
		
		ret = getint("Select the keyboard language :\n1_ English\n2_ Spanish\n")-1;
		
	}
	setCurrentKeyboard(ret);
	
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
			minutes=60+minutes;
		}
		if(hour>24){
			hour-=24;
		}
		else if(hour<0){
			hour=24+hour;
		}
		
	
		int x=getCursorX();
		int y=getCursorY();
		
		
		setCursor(FALSE);
		setCursorX(60);
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
		if(seconds<10){
		printf("0%d ",seconds);
		}
		else{
		printf("%d",seconds);
		}
	
		setCursorX(x);
		setCursorY(y);
		
		setCursor(TRUE);


}

int toDecimal(int value){
			value = ((value / 16) * 10) + (value & 0xf); 
}


int morse(int size, char** args){
	
		toMorse(size, args);	
}

int tryMalloc(int size, char** args){

	int dim;
	void *p;
	char pointer[9];
	char *print;
	
	if(size > 1){
		dim = atoi(args[1]);
		if(dim > 0){
			p = myMalloc(dim);
			if( p != NULL){
				print = toHexa(pointer,(char*)p);
				printf("Pointer: %s\n",pointer);
			}else{
				printf("Out of memory exception\n");
			}
		}else{
			printf("Invalid arguments\n");
		}
	}else{
		printf("Missing arguments\n");		
	}
}

int tryCalloc(int size, char** args){

	int dim;
	void *p;
	char pointer[9];
	char *print;
	
	if(size > 1){
		dim = atoi(args[1]);
		if(dim > 0){
			p = myCalloc(dim);
			if( p != NULL){
				print = toHexa(pointer,(char*)p);
				printf("Pointer: %s\n",pointer);
			}else{
				printf("Out of memory exception\n");
			}
		}else{
			printf("Invalid arguments\n");
		}
	}else{
		printf("Missing arguments\n");		
	}
}

int tryFree(int size, char** args){
	
	int pointer;
	
	if(size > 1){
		pointer = toInt(args[1]);
		if(pointer != -1){
			myFree((void*)pointer);
		}
		else{
			printf("Invalid arguments\n");
		}
	}else{
		printf("Missing arguments\n");		
	}
}	

int tryPrintPages(int size, char **args){		
		printPages();		
}

int tryPrintPage(int size, char **args){
		
	int pointer;
	
	if(size > 1){
		pointer = toInt(args[1]);
		if(pointer != -1){
			printPage((void*)pointer);
		}
		else{
			printf("Invalid arguments\n");
		}
	}else{
		printf("Missing arguments\n");		
	}
	
}

int tryPrintMap(int size, char **args){
		
	int pointer;
	
	if(size > 1){
		pointer = toInt(args[1]);
		if(pointer != -1){
			printMap((void*)pointer);
		}
		else{
			printf("Invalid arguments\n");
		}
	}else{
		printf("Missing arguments\n");		
	}
	
}

int tryPrintBlock(int size, char **args){
		
	int pointer;
	
	if(size > 1){
		pointer = toInt(args[1]);
		if(pointer != -1){
			printBlock((void*)pointer);
		}
		else{
			printf("Invalid arguments\n");
		}
	}else{
		printf("Missing arguments\n");		
	}
	
}

int tryWrite(int size, char **args){
	
	int pointer;
	
	if(size > 2){
		pointer = toInt(args[1]);
		if(pointer != -1){
			memInput(args[2][0],(void*)pointer);
		}
		else{
			printf("Invalid arguments\n");
		}
	}else{
		printf("Missing arguments\n");		
	}
	
}

int tryRealloc(int size, char** args){

	int dim;
	void *p;
	char pointer[9];
	int punt;
	char *print;
	
	if(size > 2){
		dim = atoi(args[2]);
		punt = toInt(args[1]);
		if(dim > 0 && punt != -1){
			p = myRealloc((void*)punt,dim);
			if( p != NULL){
				print = toHexa(pointer,(char*)p);
				printf("Pointer: %s\n",pointer);
			}else{
				printf("Out of memory exception\n");
			}
		}else{
			printf("Invalid arguments\n");
		}
	}else{
		printf("Missing arguments\n");		
	}
}
