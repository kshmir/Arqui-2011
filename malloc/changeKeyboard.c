#include <stdio.h>
#include "../arqui-2011/src/libs/mcgio.h"

int main(void){
	
	char *args[] = {"hola","hola"};
	int i = changeKeyboard(2,args);
	
	printf("%d\n",i);
	return 0;
}

int changeKeyboard(int size ,char** args){
	
	int ret = -1;
	
	if(size > 1){
		if( args[1] == "EN"){
			ret = 0;
		}else{
			if( args[1] == "ES"){
				ret = 1;
			}	
		}
	}
	while(ret != 0 && ret!= 1){
		
		ret = getint("Elija la opcion para el idioma del teclado:\n1_ English\n2_Español\n");
		
	}
	return ret;
}
	
