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
#define TRUE 0
#define FALSE 1

#define BORRA_BUFFER while (getchar() != '\n')

void printdouble(double number, char* format);

void internalswap(char* answ,int pos);

void printHelp();

void printstring(char* message);

void myitoa(int number, char* resp);

void printint(int number, char* format);

void myprintf(char* string, ...);

void selectcmd(int value, char** usr);

char* su(char* usr);

void init();

int getcommand();

int getint(const char mensaje[], ... );

char* getusr();

void myftoa(float number, char* answ);


int main(){

	char* usr;
	int cmd;
	printdouble(1.23456, usr);
	printstring("\n");
	printstring("hola%\n");
	myprintf("hola %f charola %d soy %c y vos sos %s \n", 123.7, 25, 'h',"sofia");
	init();
	usr = getusr();
	do{
		do{
			myprintf("%s%s ",usr,OSDEFST);
			cmd=getcommand();
		}while(cmd<HELP || cmd>LOGOUT);
		selectcmd(cmd, &usr);
	}while(cmd!=LOGOUT);
	return 0;
}

void init(){

	int i = 0;
	myprintf("Muricelag O.S. is loading");
	
	for(;i<20;i++){
		int j=0;
		for(j=0;j<100000;j++){
		putchar('\0');
		}
		putchar('.');
	}
	myprintf("100 %% \n");

}

int getint(const char mensaje[], ... ){
	int n, salir = 0;
	va_list ap;
		
	do	
	{
		va_start(ap, mensaje);
		vprintf(mensaje, ap);
		va_end(ap);

		if ( scanf("%d",&n) != 1)
		{
			myprintf("\nInvalid Value, please Try agian\n");
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
	myprintf("Please Select User:\n");
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

void selectcmd(int opt, char** usr){
	switch(opt){
		case HELP: printHelp();
		break;
		case SU: *usr=su(*usr);
		break;
		case CLEAR : myprintf("cablear clear screen maxi\n");
		break;
		case ECHO : myprintf("crear echo\n");
		break;
		case CPUSPEED : myprintf("es muy alta \n");
		break;
		
	}
	
}

char* su(char* usr){
	return (usr == MARIOST?LUIGIST:MARIOST);
}

void myprintf(char* string, ...){
	
	int i = 0, va_count;
	va_list ap;
	
	va_start(ap, string);
	
	while(string[i]!='\0'){
		if (string[i]=='%'){
			i++;
			switch(string[i]){
				case 'd':printint(va_arg(ap,int),string);
				break;
				case 's':printstring(va_arg(ap,char*));
				break;
				case 'c':putchar(va_arg(ap,int));
				break;
				case 'f':printdouble(va_arg(ap,double),string);
				break;
				case '%':putchar('%');
				break;
				
				default: printstring("\n invalid argument type error \n");
				
			}
		i++;
		}
		else {
			putchar(string[i]);
			i++;
		}
	}
	va_end(ap);

}

void printint(int number, char* format){
		
		char charint[20];
	
		myitoa(number, charint);
				
		int i=0;
		while (charint[i]!='\0')
				putchar(charint[i++]);
		
		
}

void myftoa(float number, char* answ){

	char ascii0 = ASCIICERO;
	int pos = 0;
	int decimal = 6;
	
	char sign = FALSE;
	if (number<0){
		sign = number<0?TRUE:FALSE;
		number*=-1;
	}
	answ[pos++]='\0';
	
	/*
	 * This is used to get a integer number.
	 * 
	 */ 
	number*=1000000;
	number=(int)number; 
	while(decimal){
		answ[pos++]=(int)number%10+ASCIICERO;
		number/=10;
		decimal--;
	}
	answ[pos++]='.';
	while((int)number!=0){
		answ[pos++]=(int)number%10+ASCIICERO;
		number/=10;
		
	}	
	
	/*
	 * This is because when it get out of the whie it has been divide per 10, one more time 
	 */
	number*=10;
	if(sign == TRUE)
		answ[pos++]='-';
	
	internalswap(answ,pos-1);
	
	
}

void internalswap(char* answ,int pos){

	
	int correccion=0;
	int i = 0;
	correccion += pos%2;
	while(i<(pos+correccion)/2){
		char aux = answ[i];
		answ[i]=answ[pos-i];
		answ[pos-i]=aux;
		i++;
	} 
}

void myitoa(int number, char* answ){

	int pos = 0;
	
	char sign = FALSE;
	if (number<0){
		sign = number<0?TRUE:FALSE;
		number*=-1;
	}
		
	answ[pos++]='\0';
	
	while(number!=0){
		answ[pos++]=(number%10)+ASCIICERO;
		number/=10;
	}
	if(sign == TRUE)
		answ[pos++]='-';

	internalswap(answ,pos-1);
	
}

void printstring(char* message){
	int i =0;
	while(message[i]!='\0'){
		putchar(message[i]);
		i++;
	}
}
	
void printdouble(double number, char* format){

		char chardouble[40];
		
		myftoa(number, chardouble);
		int i=0;
		while (chardouble[i]!='\0'){
				putchar(chardouble[i]);
				i++;
		}
}
