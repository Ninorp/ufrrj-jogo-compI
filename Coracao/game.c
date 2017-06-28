#include <stdio.h>
#include <SDL2/SDL.h>
#include "headers/game.h"
#include "headers/inimigo.h"
#include "headers/gamer.h"
#include "headers/torre.h"


typedef enum game_estado {
    MENU = 0,
    JOGANDO = 1,
    PAUSADO = 2,
    GAME_OVER = 3
} Game_Estado;

typedef struct game{
    int rodando;
    Game_Estado estado;
}Game;
int rodando = 0;

SDL_Surface* screen; //superficie que representa a tela do computador
SDL_Window *window;
SDL_Event event; //um evento enviado pela SDL
SDL_Renderer *rend;
int init(const char* title, int xpos, int ypos, int width, int height){
    if(SDL_Init(SDL_INIT_VIDEO)){
        window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_SHOWN);
        rend = SDL_CreateRenderer(window,-1,0);
        return 1;
    }
    return 0;
}