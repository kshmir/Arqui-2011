#include "defs.h"
#include <stdarg.h>
#include <stdio.h>
#include "libc.h"

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
	
	if ((int)number==0){
				answ[pos++]='0';
	}
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
	if (number ==0)
		answ[pos++]=ASCIICERO;
	else{	
		while(number!=0){
			answ[pos++]=(number%10)+ASCIICERO;
			number/=10;
		}
		if(sign == TRUE)
			answ[pos++]='-';
	}
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

int myatoi(char* string){
	
	int i=0;
	int result=0;
	int sign =1;
	
	while(string[i]!='\0'){
		if(string[i]=='-'){
			sign=-1;
			i++;
		}
		result=result*10 + (string[i]-ASCIICERO);
		i++;
	}
	return result*sign;
		
}

double myatof(char*string){
	int sign = 1;
	int decount=0;
	int i=0;
	double result= 0.0;
	double decimals = 0.1;

	while(string[i]!='\0'){
		if (string[i]=='.'){
			decount=1;
			i++;
		}
		else{
			if(!decount){
				if(string[i]=='-'){
					i++;
					sign=-1;
				}
				else{
					result=result*10 + (string[i]-ASCIICERO);
					i++;
				}
			}
			else {
				result=result + decimals*(string[i]-ASCIICERO);
				decimals/=10;
				i++;
			}
		}
	}
	return result*sign;
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

int isdigit(int ch){
	return (ch>='0' && ch<='9');
}

int isalpha(int ch){
	return ((ch>='A' && ch<='Z' )||(ch>='a' && ch<='z' ));
}
/*
void myscanf(char* string, ...){
	int i = 0, va_count;
	va_list ap;
	
	va_start(ap, string);
	
	while(string[i]!='\0'){
		if (string[i]=='%'){
			i++;
			switch(string[i]){
				case 'd':scanint(va_arg(ap,int),string);
				break;
				case 's':scanstring(va_arg(ap,char*));
				break;
				case 'c':getchar(va_arg(ap,int));
				break;
				case 'f':scandouble(va_arg(ap,double),string);
				break;
				case '%':getchar();
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
*/
void scanint(int *pint){
		char result[20];
		int final;
		int i = 0;
		char c;
		while(isdigit(c=getchar())){
				result[i]=c;
				i++;
		}
		result[i]='\0';
		final=myatoi(result);
		*(pint)=final;
}

void scandouble(double *pdouble){
		char result[40];
		double final;
		int i = 0;
		int flag = TRUE;
		char c;
		/* this is used to get de integer part*/
		while(isdigit(c=getchar())){
				result[i]=c;
				i++;
		}
		if (c=='.')
			result[i++]='.';
		else
			flag = FALSE;
		if (flag){
			/* this is used to get de decimal part*/
			while(isdigit(c=getchar())){
					result[i]=c;
					i++;
			}
			result[i]='\0';
			final=myatof(result);
			*(pdouble)=final;
		}
	
}

void scanstring(char* pchar){
	
	int c, i=0;
	while((c=getchar())!='\0' && c!='\n'){
					pchar[i]=c;
					i++;
			}
	pchar[i]='\0';
}

