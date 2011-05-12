#include "libc.h"
#include "defs.h"
#include <stdio.h>
void printHelp();

void selectcmd(int value, char** usr);

char* su(char* usr);

void init();

int getcommand();

char* getusr();

int main(){

	char* usr;
	int cmd = 8 , opt;
	myprintf("-->%d\n",0);
	printf("hola gente --> %d\n",cmd);
	scanint(&cmd);
	BORRA_BUFFER;
	myprintf(" numero %d \n",cmd);
	
	//si no se sigue el formato pedido devuelve lo que hay en los punteros
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

char* getusr() {
	int usrid;
	int flag = 0;
	do {
		myprintf("Please Select User:\n");
		usrid = getint("0-> Mario (root) \n1-> Luigi\nOption:");
		if (usrid == MARIO) {
			flag = 1;
			return MARIOST;
		} else if (usrid == LUIGI) {
			flag = 1;
			return LUIGIST;
		}
	} while (!flag);


}

int getcommand() {
	return getint("");

}

void printHelp() {

	myprintf("Murcielago bash, version 1.0.0(1)-release (i686-pc-murcielago)\n");
	myprintf(
			"These shell commands are defined internally.  Type `help' to see this list.\n");
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
	}
}

char* su(char* usr) {
	return (usr == MARIOST?LUIGIST:MARIOST);
}

