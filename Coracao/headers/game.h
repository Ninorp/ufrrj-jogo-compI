#ifndef GAME
#define GAME

    int rodando; 
    typedef struct game Game;
    SDL_Surface* screen; //superficie que representa a tela do computador
    SDL_Window *window;
    SDL_Event event; //um evento enviado pela SDL
    SDL_Renderer *rend;
    int init(const char* title, int xpos, int ypos, int width, int height);

    int renderizar();
    void atualizar();
    void pegarEventos();
    int limpar();


#endif