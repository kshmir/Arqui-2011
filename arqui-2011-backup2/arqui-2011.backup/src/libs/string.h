#ifndef _STRING_H_

#define _STRING_H_

char* strcpy(char* s1, char* s2);
char* strncpy(char* s1, char* s2, int n);
int strlen(char* s1);
char* strcat(char* s1, char* s2);
char* strncat(char* s1, char* s2, int n);
int strcmp(char* s1, char* s2);
int strncmp(char* s1, char* s2, int n);
char* strchr(char* s1, char c);
char* strrchr(char* s1, char c);
char* strpbrk(char* s1, char* s2);
char* strstr(char* s1, char* s2);

#endif
