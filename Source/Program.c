#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "GameState.h"
#include "Utils.h"
#include "DynamicArray.h"

BOOL hasLetterBeenGuessed(GameState* state, char letter){
    for(int i = 0; i < state->rightCount; i++){
        if(state->rightLetters[i] == letter){
            return TRUE;
        }
    }
    for(int i = 0; i < state->wrongCount; i++){
        if(state->wrongLetters[i] == letter){
            return TRUE;
        }
    }
    return FALSE;
}

void guessLetter(GameState* state, char letter){
    letter = toUpperCase(letter);
    if(hasLetterBeenGuessed(state, letter)) return;
    for(int i = 0; i < state->termLength; i++){
        if(state->term[i] == letter){
            state->rightLetters[state->rightCount++] = letter;
            return;
        }
    }
    state->wrongLetters[state->wrongCount++] = letter;
}

void GetRandomTerm(const char* fileName, DynamicArray* term){
    FILE* file = fopen(fileName, "r");
    if(!file){
        printf("Arquivo \"%s\" nao encontrado\n", fileName);
        exit(1);
    }
    char buffer[256];
    DynamicArray termArray;
    initDynamicArray(&termArray, sizeof(DynamicArray), 10);
    initDynamicArray(term, sizeof(char), 32);
    int len;
    while((len = fread(buffer, 1, 256, file)) > 0){
        for(int i = 0; i < len; i++){
            char c = buffer[i];
            if(c == '\n'){
                if(term->size > 0){
                    DynamicArray da;
                    initDynamicArray(&da, term->elementSize, term->size + 1);
                    char nullByte = '\0';
                    copyDynamicArray(&da, term);
                    addToDynamicArray(&da, &nullByte);
                    addToDynamicArray(&termArray, &da);
                }
                clearDynamicArray(term);
            }else{
                addToDynamicArray(term, &c);
            }
        }
    }

    fclose(file);

    if(term->size > 0){
        DynamicArray da;
        initDynamicArray(&da, term->elementSize, term->size + 1);
        char nullByte = '\0';
        copyDynamicArray(&da, term);
        addToDynamicArray(&da, &nullByte);
        addToDynamicArray(&termArray, &da);
    }

    if(termArray.size <= 0){
        printf("Arquivo \"%s\" nao contem palavras validas\n", fileName);
        exit(1);
    }

    srand(time(0));
    int randomInt = rand() % termArray.size;
    for(int i = 0; i < termArray.size; i++){
        DynamicArray da;
        getDynamicArray(&termArray, i, &da);
        if(i == randomInt){
            copyDynamicArray(term, &da);
        }
        destroyDynamicArray(&da);
    }
    destroyDynamicArray(&termArray);
}

void printGameTerm(GameState* state){
    for(int i = 0; i < state->termLength; i++){
        char c = state->term[i];
        printf("%c ", hasLetterBeenGuessed(state, c) || c == ' ' ? c : '_');
    }
}

void printGuessedLetters(GameState* state){
    printf("Letras erradas: ");
    for(int i = 0; i < MAX_TRIES; i++){
        printf("[%c] ", i >= state->wrongCount ? ' ' : state->wrongLetters[i]);
    }
}

int getRemainingLife(GameState* state){
    return MAX_TRIES - state->wrongCount;
}

BOOL isGameOver(GameState* state){
    for(int i = 0; i < state->termLength; i++){
        if(state->term[i] != ' ' && !hasLetterBeenGuessed(state, state->term[i])) return FALSE;
    }
    return TRUE;
}

char getUserGuess(){
    printf("Chute uma letra: ");
    char c = getChar();
    c = toUpperCase(c);
    printf("\033[A\033[K"); // Ir para linha de cima e limpar
    return c < 'A' || c > 'Z' ? 0 : c;
}

void startGame(GameState* state){
    while(TRUE){
        printGameTerm(state);
        printf(" ");
        printGuessedLetters(state);

        if(isGameOver(state)){
            printf("\n VOCE GANHOUU !!!! :) ");
            break;
        }else if(getRemainingLife(state) <= 0){
            printf("\n VOCE PERDEU, a palavra era: [%s] ", state->term);
            break;
        }else{
            char c = getUserGuess();
            if(c != 0) guessLetter(state, c);
        }
    }
}

int main(int argc, char *argv []){
    DynamicArray term;
    GameState* state = initGameState("");
    char result;
    do{
        GetRandomTerm(argc >= 3 && !strcmp(argv[1], "-a") ? argv[2] : "palavras.txt", &term);
        restartGame(state, term.buffer);
        startGame(state);
        printf("Gostaria de jogar novamente? [S] Sim / [N] Nao\n");
        result = getChar(result);
        printf("\033[A\033[K\033[A\033[K\033[A\033[K");
    }while(result == 's' || result == 'S');
    destroyDynamicArray(&term);
    destroyGameState(state);
}