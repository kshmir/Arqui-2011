#include "../src/IO.h"
#define MAX 0xff
/* Pongo 2 coordenadas. 1: tecla normal. 2: Shift. */
/* Confio en que las entradas no completadas se completan con 0 = NPRTBL */
//#DEFINE MAX_KEYS 100

#define NPRTBL 0

unsigned char keyboard[][2] = { { NPRTBL, NPRTBL },//000
		{ NPRTBL, NPRTBL },//001 ESCAPE
		{ '1', '!' }, //002
		{ '2', '\"' }, //003
		{ '3', '#' }, //004
		{ '4', '$' }, //005
		{ '5', '%' }, //006
		{ '6', '&' }, //007
		{ '7', '/' }, //008
		{ '8', '(' }, //009
		{ '9', ')' }, //010
		{ '0', '=' }, //011
		{ '\'', '?' }, //012
		{ '¿', '¡' }, //013
		{ '\b', '\b' }, //014 BACKSPACE
		{ '\t', '\t' }, //015 TAB
		{ 'q', 'Q' }, //016
		{ 'w', 'W' }, //017
		{ 'e', 'E' }, //018
		{ 'r', 'R' }, //019
		{ 't', 'T' }, //020
		{ 'y', 'Y' }, //021
		{ 'u', 'U' }, //022
		{ 'i', 'I' }, //023
		{ 'o', 'O' }, //024
		{ 'p', 'P' }, //025
		{ '\'', '\"' }, //026
		{ '+', '*' }, //027
		{ '\n', '\n' }, //028
		{ NPRTBL, NPRTBL },//029 CTRL IZQ
		{ 'a', 'A' }, //030
		{ 's', 'S' }, //031
		{ 'd', 'D' }, //032
		{ 'f', 'F' }, //033
		{ 'g', 'G' }, //034
		{ 'h', 'H' }, //035
		{ 'j', 'J' }, //036
		{ 'k', 'K' }, //037
		{ 'l', 'L' }, //038
		{ '.', ';' }, //039
		{ '{', '[' }, //040
		{ '}', ']' }, //041
		{ NPRTBL, NPRTBL },//042 SHIFT IZQ
		{ '<', '>' }, //043
		{ 'z', 'Z' }, //044
		{ 'x', 'X' }, //045
		{ 'c', 'C' }, //046
		{ 'v', 'V' }, //047
		{ 'b', 'B' }, //048
		{ 'n', 'N' }, //049
		{ 'm', 'M' }, //050
		{ ',', ';' }, //051
		{ '.', ':' }, //052
		{ '?', '?' }, //053
		{ NPRTBL, NPRTBL },//054 SHIFT DER
		{ '*', '*' }, //055 KEY *
		{ NPRTBL, NPRTBL },//056 ALT IZQ
		{ ' ', ' ' }, //057 SPACE
		{ NPRTBL, NPRTBL },//058 CAPSLOCK
		{ NPRTBL, NPRTBL },//059 F1
		{ NPRTBL, NPRTBL },//060 F2
		{ NPRTBL, NPRTBL },//061 F3
		{ NPRTBL, NPRTBL },//062 F4
		{ NPRTBL, NPRTBL },//063 F5
		{ NPRTBL, NPRTBL },//064 F6
		{ NPRTBL, NPRTBL },//065 F7
		{ NPRTBL, NPRTBL },//066 F8
		{ NPRTBL, NPRTBL },//067 F9
		{ NPRTBL, NPRTBL },//068 F10
		{ NPRTBL, NPRTBL },//069 NUM LOCK
		{ NPRTBL, NPRTBL },//070 SCROLL LOCK
		{ '7', '7' }, //071 KEY 7
		{ '8', '8' }, //072 KEY 8
		{ '9', '9' }, //073 KEY 9
		{ '-', '-' }, //074 KEY -
		{ '4', '4' }, //075 KEY 4
		{ '5', '5' }, //076 KEY 5
		{ '6', '6' }, //077 KEY 6
		{ '+', '+' }, //078 KEY +
		{ '1', '1' }, //079 KEY 1
		{ '2', '2' }, //080 KEY 2
		{ '3', '3' }, //081 KEY 3
		{ '0', '0' }, //082 KEY 0
		{ '.', '.' }, //083 KEY .
		{ NPRTBL, NPRTBL },//084 SYS REQ (AT)
		{ '+', '*' }, //085
		{ '+', '*' }, //086
		{ NPRTBL, NPRTBL },//087 F11
		{ NPRTBL, NPRTBL },//088 F12
		{ '+', '*' }, //089
		{ '+', '*' }  //090
		//Para asegurarme podria llenar con NPRTBL lo que queda
};

char scanCodeToChar(char scanCode) {
	if (scanCode >= 0x02 && scanCode <= 0x0d)
		return keyboard[scanCode][isShifted()];
	return keyboard[scanCode][isCapital()];
}
