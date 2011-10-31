#include "sound.h"

int buff;
char toSound[MAX_MORSE];
int singleton = 1;

void toMorse(int size, char** args){
	
	char *morse;
	char output[10000];
	int i;
	int k;
	int j;
	int index = 0;
		
	
	for(i = 1; i < size; i++){
		for(j = 0; args[i][j] != '\0'; j++){
			if(isNumber(args[i][j])){
				morse = getMorseNumber(args[i][j]);
			}else{
				if(isLetter(args[i][j])){
					morse = getMorseLetter(args[i][j]);
				}
					
			}	
			
			for(k = 0; morse[k] != '\0'; k++){
				output[index++] = morse[k];
			}
		}
		output[index++] = ' ';
	}
	output[index++] = '\0';
	
	toBuffer(output);
	
}
char* getMorseNumber(char digit){
		char *morse[] = {"_____",".____","..___","...__","...._",".....","_....","__...","___..","____."};
	
	return morse[digit - '0'];	
}
char* getMorseLetter(char letter){
		char *ret;

	char *morse[] = {".__","_...","_._.","_..",".",".._.","__.","....","..",".___","_._","._..","__","_.","___",".__.","__._","._.","...","_",".._","..._",".__","_.._","_.__","__.."};
	
		
	if(letter == ' '){
		ret = " ";
	}else{
			letter = toUpper(letter);	
			ret = morse[letter - 'A'];
	}
	
	return ret;

}
int isNumber(char input){
	int ret = 0;
	
	if(input >= '0' && input <= '9'){
		ret = 1;
	}
	return ret;

}
int isLetter(char input){
	int ret = 0;
	
	if((toUpper(input) >= 'A' && toUpper(input) <= 'Z') || input == ' '){
		ret = 1;
	}
	
	return ret;	
}
char toUpper(char letter){
	if(letter >= 'a' && letter <= 'z'){
		letter = letter - 'a' + 'A';
	}
	
	return letter;

}
void soundOn(){
		char value;
	
	_out(0x43,0xB6);
	_out(0x42,54);
	_out(0x42,124);
	
	value = _in(0x61);
	value = value | 3;	/*(Turn on bits 1 and 2)*/
  _out (0x61, value);

}
void soundOf(){
		char value;
	
	_out(0x43,0xB6);
	_out(0x42,54);
	_out(0x42,124);
	
	value = _in(0x61);
	value = value & 252;	/*(Turn on bits 1 and 2)*/
	_out(0x61,value);
}
void toBuffer(char* morse){

	int i;
	int dim;
	
	for( i = 0, dim = 0; morse[i] != '\0'; i++){
		
		if( morse[i] == '.'){
			toSound[dim++] = 5;
			toSound[dim++] = -5;
			
		}else{ if( morse[i] == '_'){
			toSound[dim++] = 10;
			toSound[dim++] = -5;
			
			}else if(morse[i] == ' '){
				toSound[dim++] = -10;
			}
		}
	}
	toSound[dim++] = 0;	
	
}
void printSound(){
	if(singleton){
		toSound[0] = 0;
		toSound[1] = 0;
		singleton = 0;	
		buff = 0;	
	}
	
	if(toSound[buff] != 0){
		if(toSound[buff] > 0){
			soundOn();
			printf("on%d",toSound[buff]);
			toSound[buff] = toSound[buff] - 1;
		}else{
			soundOf();
			printf("off%d",toSound[buff]);
			toSound[buff] = toSound[buff] + 1;
		}	
	}else{
		if(buff < MAX_MORSE - 1 && toSound[buff + 1] != 0){
			buff++;
		}else{
			buff = 0;
			toSound[buff] = 0;
			toSound[buff + 1] = 0;			
		}	
	}
}
