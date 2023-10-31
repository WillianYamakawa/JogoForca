#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GameState.h"
#include "Utils.h"

GameState* initGameState(const char* term){
    int size = strlen(term);
    GameState* state = malloc(sizeof(GameState));
    state->term = malloc(size * sizeof(char) + 1);
    strcpy(state->term, term);
    formatTerm(state->term);
    state->termLength = size;
    state->rightLetters = malloc(26 * sizeof(char));
    state->wrongLetters = malloc(MAX_TRIES * sizeof(char));
    state->rightCount = 0;
    state->wrongCount = 0;
    return state;
}

void restartGame(GameState* state, const char* term){
    int size = strlen(term);
    if(size > state->termLength) {
        free(state->term);
        state->term = malloc(size * sizeof(char) + 1);
    }
    strcpy(state->term, term);
    formatTerm(state->term);
    state->termLength = size;
    state->rightCount = 0;
    state->wrongCount = 0;
}

void destroyGameState(GameState* state){
    if(state){
        free(state->rightLetters);
        free(state->wrongLetters);
        free(state);
    }
}
