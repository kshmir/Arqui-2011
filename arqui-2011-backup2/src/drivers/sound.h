#include "../libs/stdio.h"

#define MAX_MORSE 10000

void toMorse(int size, char** args);
char* getMorseNumber(char digit);
char* getMorseLetter(char letter);
int isNumber(char input);
int isLetter(char input);
char toUpper(char letter);
void soundOn();
void soundOf();
void toBuffer(char* morse);
void printSound();
