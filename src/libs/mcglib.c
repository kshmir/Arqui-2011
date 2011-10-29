#include "mcglib.h"
#include "video.h"

// Splits an string, returns the length of the splitted array
// C: char array.
// ch: separator.
// len: length of the string.
char** sString(char* c, char ch, int* len) {
	char** result = (char**) malloc(sizeof(char*) * 5);
	int result_s = 5;
	*len = 0;
	int i = 0;
	int start = i;
	char* currentbuilder = 0;
	while (*(c + i) != 0) {
		if (*len >= result_s) {
			result = (char**) realloc(result, sizeof(char*) * (result_s + 5));
			result_s = *len + 5;
		}
		if (*(c + i) == ch) {
			currentbuilder = (char*) malloc(sizeof(char) * (i - start + 2));
			char cur = *(c + i);
			*(c + i) = 0;
			currentbuilder = (char*) strcpy(currentbuilder, c + start);
			start = i + 1;
			*(c + i) = cur;
			result[*len] = currentbuilder;
			(*len)++;
		}
		i++;
	}
	if (start != i) {
		currentbuilder = (char*) malloc(sizeof(char) * (i - start + 1));
		char cur = *(c + i);
		*(c + i) = 0;
		currentbuilder = (char*) strcpy(currentbuilder, c + start);
		start = i + 1;
		*(c + i) = cur;
		result[*len] = currentbuilder;
		(*len)++;
	}
	return result;
}
