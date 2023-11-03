#ifndef _GMSTT
#define _GMSTT

typedef struct _gameState{
    char   *term;            // Palavra do jogo
    int     termLength;      // Tamanho da palavra do jogo
    char   *wrongLetters;    // Letras chutadas erradas
    char   *rightLetters;    // Letras chutadas certas
    int     wrongCount;      // Tamanho letras chutadas erradas
    int     rightCount;      // Tamanho letras chutadas certas
} GameState;

GameState* initGameState(const char* term);
void restartGame(GameState* state, const char* term);
void destroyGameState(GameState* state);

#endif