#include "libc.h"
#include "defs.h"
#include <stdio.h>
#include "nInLineFront.h"

void printHelp();

void selectcmd(int value, char** usr);

char* su(char* usr);

void init();

int getcommand();

char* getusr();

int main(){

	char* usr;
	char hola[20];
	char hola2[20];
	int cmd = 8 , opt;
	double hh =2.8;
	
	scanf("%s %s",hola,hola2);
	printf("hola->%s\n",hola);
	printf("hola2->%s\n",hola2);
	
	init();
	usr = getusr();
	do {
		do {
			myprintf("%s%s ", usr, OSDEFST);
			cmd = getcommand();
		} while (cmd < HELP || cmd > LOGOUT);
		selectcmd(cmd, &usr);
	} while (cmd != LOGOUT);
	return 0;
}

void init() {

	int i = 0;
	myprintf("Murcielag O.S. is loading");

	for (; i < 20; i++) {
		int j = 0;
		for (j = 0; j < 100000; j++) {
			putchar('\0');
		}
		putchar('.');
	}
	myprintf("100 %% \n");

}

char* getusr(){
	int usrid;
	int flag = FALSE;
	char user[20];
	do{
	myprintf("Please Select User:\n");
	myprintf("Mario (root) \nLuigi\nOption:");
	myscanf("%s",user);
	if (!strcmp(user,MARIOST)){
		flag=TRUE;
		return MARIOST;
	}
	else if (!strcmp(user,LUIGIST)){
		flag=TRUE;
		return LUIGIST;
	}
	else{
		myprintf("Invalid User please try again\n");
	}
	myprintf("lo que se escribio %s\n",user);
	}while(!flag);
	
}	
int getcommand() {
	return getint("");

}

void printHelp() {

	myprintf("Murcielago bash, version 1.0.0(1)-release (i686-pc-murcielago)\n");
	myprintf("These shell commands are defined internally.  Type `help' to see this list.\n");
	myprintf("Type `help name' to find out more about the function `name'.\n");
	myprintf("Use `info bash' to find out more about the shell in general.\n\n");
	myprintf("%d->help [pattern ...]\n", HELP);
	myprintf("%d->clear\n", CLEAR);
	myprintf("%d->echo [arg ...]\n", ECHO);
	myprintf("%d->cpuspeed\n", CPUSPEED);
	myprintf("%d->su\n", SU);
	myprintf("%d->logout [n]\n", LOGOUT);

}

void selectcmd(int opt, char** usr) {
	switch (opt) {
	case HELP:
		printHelp();
		break;
	case SU:
		*usr = su(*usr);
		break;
	case CLEAR:
		myprintf("cablear clear screen maxi\n");
		break;
	case ECHO:
		myprintf("crear echo\n");
		break;
	case CPUSPEED:
		myprintf("es muy alta \n");
		break;
	case PLAY:
		start();
	}
}

char* su(char* usr) {
	return (!strcmp(usr,MARIOST)?LUIGIST:MARIOST);
}

