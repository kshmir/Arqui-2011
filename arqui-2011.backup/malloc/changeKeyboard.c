#include <stdio.h>
#include "../arqui-2011/src/libs/mcgio.h"

int main(void){
	
	char *args[] = {"hola","hola"};
	int i = changeKeyboard(2,args);
	
	printf("%d\n",i);
	return 0;
}


	
