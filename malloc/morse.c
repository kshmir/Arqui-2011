#include <stdio.h>

void toMorse(void);
char* getMorseNumber(char digit);
char* getMorseLetter(char letter);
int isNumber(char input);
int isLetter(char input);
char toUpper(char letter);

int main(void){

	toMorse();

	return 0;
}

void toMorse(void){
		
	char input[250];
	char *morse;
	char output[1000];
	int i;
	int j;
	int index = 0;
	
	printf("Ingrese una frase para convertir a codigo morse:\n");
	scanf("%s",input);
	
	
	for(i = 0; input[i] != '\0'; i++){
			
		if(isNumber(input[i])){
			morse = getMorseNumber(input[i]);
			
		}else{
			if(isLetter(input[i])){
				morse = getMorseLetter(input[i]);
			}
				
		}	
		
		for(j = 0; morse[j] != '\0'; j++){
			output[index++] = morse[j];
		}	
	}
	output[index++] = '\0';
	
	/* TO DO LIST: 
	 - Ahora tengo en output un char* con la frase convertida en codigo morse 
	 - reallocar output con la nueva dimension index 
	 - Averiguar la direccion del mapa de entrada y salida del speaker 
	 - Llamar a la funcion en assembler que a partir de output hace un out por el speaker */
		
	printf("%s\n",output);

}

char* getMorseNumber(char digit){
	
	char *morse[] = {"_____",".____","..___","...__","...._",".....","_....","__...","___..","____."};
	
	return morse[digit-'0'];	
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
