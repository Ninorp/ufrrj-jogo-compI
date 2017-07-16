#include <stdio.h>
#include "headers/universoGame.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>

#define SCREEN_W 640
#define SCREEN_H 480
#define SCREEN_SCALE 1
#define SCREEN_NAME "O  J O G O"

#define Y_FONT 20
#define Y_MENU 280
#define X_MENU 440
#define Y_RECORD 120
#define X_RECORD 320

typedef enum game_states
{
  MENU = 0,
  PLAY = 1,
  PAUSE = 2,
  GAMEOVER = 3
}Game_States;


typedef struct screen{
    unsigned int w;
	unsigned int h;
	const char* name;
	SDL_Window* window;
	SDL_Renderer* renderer;
} Screen;

typedef struct game{
    int running;
    Screen screen;
    Game_States state;
    // define "methods"
	void (*init)(void);
	void (*quit)(void);
} GameS;

typedef struct menu{
    Mix_Music* musica;
    Mix_Music* toque;
    int opcao;
    SDL_Surface *cursor_img;
    SDL_Texture *cursor;
    SDL_Rect cursor_position;
    SDL_Surface *m_img;
    SDL_Texture *img_text;
} Menu;

typedef struct jogador{
    float grana;
    int vida, pontuacao;
    char nome[50];
} Jogador;

typedef struct records{
    int cont;
    Jogador jogadores[10];
} Records;

typedef struct gameOver{
    Mix_Music* musica;
    Mix_Music* toque;
    int opcao;
    SDL_Surface  *img;
} GameOver;

//variaveis globais
GameS Game = NULL;
Menu menu = NULL;

Mix_Music* musica = NULL;
Mix_Music* fase = NULL;
Mix_Chunk* explosao = NULL;

SDL_Event event = NULL;

TTF_Font* fonte = NULL;

void game_init(void) {
	if(SDL_Init(SDL_INIT_EVERYTHING)!=0) {
		printf("SDL error -> %sn", SDL_GetError());
		exit(1);
	}

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n",
        Mix_GetError());        
    }

    Game.screen.w = SCREEN_W * SCREEN_SCALE;
    Game.screen.h = SCREEN_H * SCREEN_SCALE;
    Game.screen.name = SCREEN_NAME;
	unsigned int w = Game.screen.w;
	unsigned int h = Game.screen.h;
	const char* name = Game.screen.name;

	Game.screen.window = SDL_CreateWindow(
		name,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		w, h, 0
	);
	Game.screen.renderer = SDL_CreateRenderer(
		Game.screen.window, -1,
		SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC
	);
    TTF_Init();
    fonte = TTF_OpenFont("Arial.ttf", Y_FONT);

	Game.running = 1;
    Game.state = Game_States.MENU;
}

void refresh(){
    SDL_RenderPresent(Game.screen.renderer);
}

void clear(){
    SDL_RenderClear(Game.screen.renderer);
}
void game_quit(void) {
	SDL_DestroyRenderer(Game.screen.renderer);
	SDL_DestroyWindow(Game.screen.window);

	Game.screen.window = NULL;
	Game.screen.renderer = NULL;

	SDL_Quit();
}

void runMenu()){    
    
    if(menu == NULL){
        menu.opcao = 0;
        menu.m_img =  IMG_Load("img/menu.png");
        menu.cursor_img = IMG_Load("img/cursor.png");
        menu.cursor_position.x = X_MENU;
        menu.cursor_position.y = Y_MENU;
        menu.cursor_position.h = 50;
        menu.cursor_position.w = 50;
        menu.cursor = SDL_CreateTextureFromSurface(Game.screen.renderer, menu.cursor_img);
        menu.img_text = SDL_CreateTextureFromSurface(Game.screen.renderer, menu.m_img;
        SDL_FreeSurface(menu.m_img);
        SDL_FreeSurface(menu.cursor_img);
    }
    
    SDL_RenderCopy(Game.screen.renderer, menu.img_text, NULL, NULL);
    SDL_RenderCopy(Game.screen.renderer, menu.cursor, NULL, &menu.cursor_position);

    while(SDL_PollEvent(&event)){
        if(event.type == SDL_KEYDOWN){
            SDLKey keyPressed = event.key.keysym.sym;
            switch(keyPressed)                    
            {                        
                case SDLK_DOWN:
                    if(menu.cursor.cursor_position < (Y_MENU + 4 * Y_FONT)
                        menu.cursor.cursor_position.y += Y_FONT;
                        opcao += 1;
                        break;
                case SDLK_UP:
                    if(menu.cursor.cursor_position > Y_MENU)
                        menu.cursor.cursor_position.y -= Y_FONT;
                        opcao -= 1;
                        break;
                case SDLK_RETURN:
                    if(!opcao){
                        Game.state = Game_States.PLAY;
                    } else if(opcao == 1){
                        recordTela(leRecords());
                    } else if(opcao == 2){
                        opcoesTela();
                    } else{
                        Game.quit();
                    }
                    break;
            }    
        }
    }
}

Records leRecords(){
    int i, k;
    Records recs;
    recs.cont = 0;    
    Jogador gamer;
    game.nome = "";
    FILE* file;
    file = fopen("record.txt", "r");
    while(!feof(file)){
        k = 0;
        while((gamer.nome[k] = fgetc(file) != '|')){
            k++;
        }
        fscanf(file, "|%d\n", &gamer.pontuacao);
        recs.jogadores[recs.cont] = gamer;
        recs.cont += 1;
    }   
    fclose(file);
    return recs;
}

void gravaRecord(Jogador jog){
    Records recs = leRecords();
    Jogador aux;
    for(int i = 0; i < recs.cont - 1; i++){
        if(recs.jogadores[i].pontuacao < jog.pontuacao){
            aux = recs.jogadores[i];
            recs.jogadores[i] = jog;
            recs.jogadores[i+1] = aux;
        }
    }
    FILE *file = fopen("record.txt", "w");
    int k;
    for(int i = 0; i < recs.cont - 1; i++){
        k = 0;
        while(recs.nome[k] != '\0'){
            fputc(recs.nome[k], file);
            k++;
        }
        //fputc('|', file);
        fprintf(file, "|%d\n", recs.jogadores[i].pontuacao);
    }
    fclose(file);

}

void recordTela(Records recs){
    SDL_Surface *background = IMG_Load("img/backrecord.png");
    SDL_Texture *back = SDL_CreateTextureFromSurface(Game.screen.renderer, background);
    SDL_RenderCopy(Game.screen.renderer, back, NULL, NULL);
    struct {        
        SDL_Rect rect[10];
        SDL_Surface *textsurf[10];
        SDL_Texture *tetuta[10];
    } Recds = {
        NULL, NULL, NULL
    };
    char texto[50] = "";
    SDL_Color color = {0,0,0,255};
    for(int i = 0; i < 10; i++){
        Recds.rect[i] = {X_RECORD, Y_RECORD * (i+1), 0, 0};
        sprintf(texto, "%d :: %s :: %d", i+1, recs.jogadores[i].nome, recs.jogadores[i].pontuacao);
        Recds.textsurf[i] = TTF_RenderText_Solid(fonte, texto, color);
        Recds.tetuta[i] = SDL_CreateTextureFromSurface(Game.screen.renderer, Recds.textsurf[i]);
        SDL_RenderCopy(Game.screen.renderer, Recds.tetuta[i], NULL, &Recds.rect[i]);
    }

    SDL_Rect rect_voltar = {X_RECORD, Y_RECORD * 12, 0,0};
    sprintf(texto, "VOLTAR");
    SDL_Surface *surf = TTF_RenderText_Solid(fonte, texto, color);
    SDL_Texture *textuta = SDL_CreateTextureFromSurface(Game.screen.renderer, surf);
    SDL_RenderCopy(Game.screen.renderer, textuta, NULL, &rect_voltar);
    
    while(SDL_PollEvent(&event)){
        if(event.type==SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    runMenu();
                    menu.opcao = 0;
                    break;
            }        
        } else if(event.type == SDL_MOUSEBUTTONDOWN){
            if(event.button.button == SDL_BUTTON_LEFT){
                int x = event.button.x;
                int y = event.button.y;

                if((x >= X_RECORD && x <= X_RECORD + 26 * 6) 
                    && (y >= Y_RECORD * 12 && y <= Y_RECORD * 12 + 26 * 6)){
                        runMenu();
                        menu.opcao = 0;
                    }
            }
        }
        if(!menu.opcao)
            break;
    }

    SDL_FreeSurface(background);
}

void opcoesTela(){

}

void runGame(){

}

void pauseGame(){

}


void runGame_Over(){

}