#include "string.h"
#include "../../include/defs.h"

char* strcpy(char* s1, char* s2) {
	int i;
	for (i = 0; (s1[i] = s2[i]); i++)
		;
	return s1;
}

char* strncpy(char* s1, char* s2, int n) {
	int i;
	for (i = 0; i < n && (s1[i] = s2[i]); i++)
		;
	return s1;
}

int strlen(char* s1) {
	int i;
	for (i = 0; s1[i++];)
		;
	return i;
}

char* strcat(char* s1, char* s2) {
	strcpy(s1 + strlen(s1), s2);
	return s1;
}

char* strncat(char* s1, char* s2, int n) {
	strncpy(s1 + strlen(s1), s2, n);
	return s1;
}

int strcmp(char* s1, char* s2) {
	int c, i;
	for (c = i = 0; s1[i] && s2[i] && (c == 0); i++)
		c = s1[i] - s2[i];
	return c;
}

int strncmp(char* s1, char* s2, int n) {
	int c, i;
	for (c = i = 0; i < n && s1[i] && s2[i] && (c == 0); i++)
		c = s1[i] - s2[i];
	return c;
}

char* strchr(char* s1, char c) {
	char* r = NULL;
	int i;
	for (i = 0; s1[i] && (r = (s1[i] == c) ? s1 + i : r) == NULL; i++)
		;
	return r;
}

char* strrchr(char* s1, char c) {
	char* r = NULL;
	int i;
	for (i = 0; s1[i] && ((r = (s1[i] == c) ? &s1[i] : r) != (char*)!r); i++)
		;
	return r;
}

char* strpbrk(char* s1, char* s2) {
	char* r = NULL;
	int j;
	for (j = 0; s2[j] && !r; j++)
		r = strchr(s1, s2[j]);
	return r;
}

char* strstr(char* s1, char* s2) {
	char* r = NULL;
	int i, j = 0, s2size = strlen(s2) - 1;
	for (i = 0; s1[i] && !r; i++) {
		for (j = 0; s2[j] && s1[i + j] && s1[i + j] == s2[j]; j++)
			;
		r = (s2size == j) ? &s1[i] : r;
	}

	return r;
}
