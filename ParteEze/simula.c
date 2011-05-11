#include <stdio.h>
#include <stdarg.h>

#define ASCIICERO 0x30
#define MARIO 0
#define LUIGI 1
#define MARIOST "mario"
#define LUIGIST "luigi"
#define OSDEFST "@murcielago:~#"
#define HELP 0
#define CLEAR 1
#define ECHO 2
#define CPUSPEED 3
#define SU 4
#define LOGOUT 5
#define REBOOT 6

#define BORRA_BUFFER while (getchar() != '\n')

void printHelp();

void myitoa(int number, char* resp);

void printint(int number, char* format);

void myprintf(char* string, ...);

void selectcmd(int value, char** usr);

char* su(char* usr);

void init();

int getcommand();

int getint(const char mensaje[], ... );

char* getusr();

void myftoa(int number, char* answ);


int main(){

	char* usr;
	int cmd;
	init();
	usr = getusr();
	do{
		do{
			printf("%s%s ",usr,OSDEFST);
			cmd=getcommand();
		}while(cmd<HELP || cmd>LOGOUT);
		selectcmd(cmd, &usr);
	}while(cmd!=LOGOUT);
	return 0;
}

void init(){

	int i = 0;
	printf("Muricelag O.S. is loading");
	
	for(;i<20;i++){
		int j=0;
		for(j=0;j<100000;j++){
		putchar('\0');
		}
		putchar('.');
	}
	printf("100 %% \n");

}

int 
getint(const char mensaje[], ... )
{
	int n, salir = 0;
	va_list ap;
		
	do	
	{
		va_start(ap, mensaje);
		vprintf(mensaje, ap);
		va_end(ap);

		if ( scanf("%d",&n) != 1)
		{
			printf("\nInvalid Value, please Try agian\n");
			BORRA_BUFFER;
		}
		else
			salir = 1;
	} while (! salir);
	BORRA_BUFFER;
	return n;
}

char* getusr(){
	int usrid;
	int flag = 0;
	do{
	printf("Please Select User:\n");
	usrid= getint("0-> Mario (root) \n1-> Luigi\nOption:");
	if (usrid ==MARIO){
		flag=1;
		return MARIOST;
	}
	else if (usrid == LUIGI){
		flag=1;
		return LUIGIST;
	}
	}while(!flag);
	
}

int getcommand(){
	return getint("");
	
}

void printHelp(){
	
	printf("Murcielago bash, version 1.0.0(1)-release (i686-pc-muricelago)\n");
	printf("These shell commands are defined internally.  Type `help' to see this list.\n");
	printf("Type `help name' to find out more about the function `name'.\n");
	printf("Use `info bash' to find out more about the shell in general.\n\n");
	printf("%d->help [pattern ...]\n", HELP);
	printf("%d->clear\n", CLEAR);
	printf("%d->echo [arg ...]\n", ECHO);
	printf("%d->cpuspeed\n", CPUSPEED);
	printf("%d->su\n", SU);
	printf("%d->logout [n]\n", LOGOUT);	
	
}

void selectcmd(int opt, char** usr){
	switch(opt){
		case HELP: printHelp();
		break;
		case SU: *usr=su(*usr);
		break;
		case CLEAR : printf("cablear clear screen maxi\n");
		break;
		case ECHO : printf("crear echo\n");
		break;
		case CPUSPEED : printf("es muy alta \n");
		break;
		
	}
	
}

char* su(char* usr){
	return (usr == MARIOST?LUIGIST:MARIOST);
}


void myprintf(char* string, ...){
	
	int va_count;
	va_list ap;
	
	va_start(ap, string);
	
	va_end(ap);

}

void myitoa(int number, char* answ){

	char ascii0 = 0x30;
	int pos = 0;
	
	char sign = number<0?'-':'0';
	
	while(number!=0){
		answ[pos++]=(number%10)+0x30;
		number/=10;
	}
	answ[pos++]=sign;
	answ[pos]='\0';
}

void printint(int number, char* format){
		
		char charint[20];
		myitoa(number, charint);
		int i=0;
		while (charint[i]!='\0')
			putchar(charint[i++])		;
		
}

void myftoa(int number, char* answ){

	char ascii0 = ASCIICERO;
	int pos = 0;
	
	char sign = number<0?'-':'';
	
	while(number!=0){
		answ[pos++]=(number%10)+ASCIICERO;
		number/=10;
	}
	answ[pos++]=sign;
	answ[pos]='\0';
}