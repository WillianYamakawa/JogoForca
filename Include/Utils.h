#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOOL char
#define FALSE 0
#define TRUE 1

#define MAX_TRIES 10

void getString(char* buffer, int maxLength);
char getChar();
char toUpperCase(char c);
void formatTerm(char* str);