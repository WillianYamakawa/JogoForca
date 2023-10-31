#include "Utils.h"

void getString(char* buffer, int maxLength){ //Fiz essa função pq fgets e gets é zoado
    fflush(stdin); //Limpar lixo q tiver
    char c;
    int i;
    for(i = 0; i < maxLength - 1; i++){
        fread(&c, sizeof(char), 1, stdin);
        if(c == '\n') break;
        buffer[i] = c;
    }
    buffer[i] = '\0';
    fflush(stdin);
}

char getChar(){
    char c;
    fflush(stdin);
    fread(&c, sizeof(char), 1, stdin);
    fflush(stdin);
    return c;
}

char toUpperCase(char c){
    return c - 32 * (c >= 'a' && c <= 'z');
}

void formatTerm(char* str){
    int len = strlen(str);
    for(int i = 0; i < len; i++){
        str[i] = toUpperCase(str[i]); // UPPERCASE
        if((str[i] < 'A' || str[i] > 'Z') && str[i] != ' '){ // Check all chars is letters or space
            printf("Palavra invalida: %s\n", str);
            exit(1);
        }
    }
}