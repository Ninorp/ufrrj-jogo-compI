#include <stdio.h>
#include <SDL2/SDL.h>
#include "Coracao/headers/game.h"

#define SCREEN_W 640
#define SCREEN_H 480

int main(int argc, char** argv)
{
    
    init("O jogo", 0,0, SCREEN_W, SCREEN_H);
    int quit = 0;
    while(!quit) //rodar enquanto nao for para encerrar :)
    {
        while(SDL_PollEvent(&event)) //checar eventos
        {
            if(event.type == SDL_QUIT) //fechar a janela?
            {
               // quit = 1; //sair do loop principal
            }
        }

       // SDL_Flip(screen); //atualizar a tela
    }

    SDL_Quit(); //encerrar a SDL
    return 0;
}