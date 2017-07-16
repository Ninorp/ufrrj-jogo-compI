#include <stdio.h>
#include <SDL2/SDL.h>
#include "Coracao/headers/universoGame.h"


int main(int argc, char** argv)
{
    
    Game.init();
    //int quit = 0;
    while(Game.running) //rodar enquanto nao for para encerrar :)
    {
        
        switch (Game.state){
            case MENU:
                runMenu();
                break;
            case PLAY:
                runGame();
                break;
            case PAUSE:
                pauseGame();
                break;
            case GAME_OVER:
                runGame_Over();
                break;
        }

        clear();
        refresh();
       
    }

    Game.quit(); //encerrar a SDL
    return 0;
}