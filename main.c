#include <stdio.h>
#include <stdlib.h>
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

//struchs do universo
typedef enum
{
  MENU = 0,
  PLAY = 1,
  PAUSE = 2,
  GAMEOVER = 3
} Game_States;




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


//metodos do universo

void game_init(void);
void game_quit(void);
void refresh();
void clear();
void runGame();
void pauseGame();
void runGame_Over();
void carregaBackground(char caminho[]);
void runMenu();
void opcoesTela();
void recordTela(Records recs);
void gravaRecord(Jogador jog);
Records leRecords();


struct {
	// define "attributes"
	int running, state;
	struct {
		unsigned int w;
		unsigned int h;
		const char* name;
		SDL_Window* window;
		SDL_Renderer* renderer;
	} screen;
 
	// define "methods"
	void (*init)(void);
	void (*quit)(void);
} Game = {
    0,0,
	{
		SCREEN_SCALE*SCREEN_W,
		SCREEN_SCALE*SCREEN_H,
		SCREEN_NAME,
		NULL,
		NULL
	},
	game_init,
	game_quit
};


//váriáveis globais do universo
//Screen screen = {0,0,0,0};
//static GameS Game = {0, screen, 0, game_init, game_quit};
Menu menu;

Mix_Music* musica;
//Mix_Music* fase;
Mix_Chunk* explosao;

SDL_Event event;

TTF_Font* fonte;




//struchs dos elementos

//life

typedef struct life{
    int cont;
    SDL_Rect backRect, bloodRect;

} Life;

//fim de vida

//orda
typedef struct orda{
    int qtd;
    float level;
} Orda;

//fim orda

//Towers

typedef struct tower{
    SDL_Rect srcrect, dstrect;
    int dano;
    float cost;
    float upgrade;
    float intervalo_disparo;
    float range;
} Tower;

//minions
typedef struct minion{
	
	Life life;
    SDL_Rect srcrect, dstrect;
	int damage;

}Minion;

//metodos dos elementos
void atirar(Tower t, Minion *alvo);

void addTower(float cost, Jogador *j);

void aumentaOrda(Orda *orda);
void mandaOrda(Orda orda);
//float deletarTower(Tower *t);

void upgrade(Tower *t, Jogador *j);

int main(int argc, char** argv)
{
    
    Game.init();
    //int quit = 0;
    while(Game.running) //rodar enquanto nao for para encerrar :)
    {
        clear();
        switch (Game.state){
            case 0:
                runMenu();
                break;
            case 1:
                runGame();
                break;
            case 2:
                pauseGame();
                break;
            case 3:
                runGame_Over();
                break;
        }
        refresh();
       
    }

    Game.quit(); //encerrar a SDL
    return 0;
}








// METODOS DE UNIVERSO

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
    Game.state = 0;
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

void runMenu(){    
    
    if(menu.m_img == NULL){
        menu.opcao = 0;
        menu.m_img =  IMG_Load("img/backmenu.png");
        menu.cursor_img = IMG_Load("img/cursor.png");
        menu.cursor_position.x = X_MENU;
        menu.cursor_position.y = Y_MENU;
        menu.cursor_position.h = 50;
        menu.cursor_position.w = 50;
        menu.cursor = SDL_CreateTextureFromSurface(Game.screen.renderer, menu.cursor_img);
        menu.img_text = SDL_CreateTextureFromSurface(Game.screen.renderer, menu.m_img);
        SDL_FreeSurface(menu.m_img);
        SDL_FreeSurface(menu.cursor_img);
    }
    
    SDL_RenderCopy(Game.screen.renderer, menu.img_text, NULL, NULL);
    SDL_RenderCopy(Game.screen.renderer, menu.cursor, NULL, &menu.cursor_position);

    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT)
        {
            Game.quit();
        }
        if(event.type == SDL_KEYDOWN){
            
            switch(event.key.keysym.sym)                    
            {                        
                case SDLK_DOWN:
                    if(menu.cursor_position.y < (Y_MENU + 4 * Y_FONT)){
                        menu.cursor_position.y += Y_FONT;
                        menu.opcao += 1;
                    }
                    break;
                case SDLK_UP:
                    if(menu.cursor_position.y > Y_MENU){
                        menu.cursor_position.y -= Y_FONT;
                        menu.opcao -= 1;
                    }
                    break;
                case SDLK_RETURN:
                    if(!menu.opcao){
                        Game.state = 1;
                    } else if(menu.opcao == 1){
                        recordTela(leRecords());
                    } else if(menu.opcao == 2){
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

    FILE* file;
    file = fopen("record.txt", "r");
    while(!feof(file)){
        k = 0;
        while((gamer.nome[k] = fgetc(file) != '|')){
            k++;
        }
        gamer.nome[k+1] = '\0';
        if(fscanf(file, "|%d\n", &gamer.pontuacao)){
            recs.jogadores[recs.cont] = gamer;
            recs.cont += 1;
        }
    }   
    fclose(file);
    return recs;
}

void carregaBackground(char caminho[]){
    SDL_Surface *background = IMG_Load(caminho);
    SDL_Texture *back = SDL_CreateTextureFromSurface(Game.screen.renderer, background);
    SDL_RenderCopy(Game.screen.renderer, back, NULL, NULL);
    SDL_FreeSurface(background);
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
        while(recs.jogadores[i].nome[k] != '\0'){
            fputc(recs.jogadores[i].nome[k], file);
            k++;
        }
        //fputc('|', file);
        fprintf(file, "|%d\n", recs.jogadores[i].pontuacao);
    }
    fclose(file);

}

void recordTela(Records recs){
    carregaBackground("img/backrecord.png");
    struct {        
        SDL_Rect rect[10];
        SDL_Surface *textsurf[10];
        SDL_Texture *tetuta[10];
    } Recds;
    char texto[50] = "";
    SDL_Color color = {0,0,0,255};
    for(int i = 0; i < 10; i++){
        Recds.rect[i].x = X_RECORD;
        Recds.rect[i].y = Y_RECORD * (i+1);
        Recds.rect[i].h = 0;
        Recds.rect[i].w = 0;
        
        
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

    
}

void opcoesTela(){

}

void runGame(){

}

void pauseGame(){
    SDL_SetRenderDrawColor(Game.screen.renderer, 255, 0, 0, 255);
    SDL_Rect rectangle;

    rectangle.x = 0;
    rectangle.y = 0;
    rectangle.w = 320;
    rectangle.h = 240;
    SDL_RenderFillRect(Game.screen.renderer, &rectangle);

    SDL_Rect rect[3];
    SDL_Surface *textsurf[3];
    SDL_Texture *tetuta[3];
    
    char texto[50] = "";
    SDL_Color color = {0,0,0,255};
    for(int i = 0; i < 3; i++){
        rect[i].x = X_RECORD;
        rect[i].y = Y_RECORD * (i+1);
        rect[i].h = 0;
        rect[i].w = 0;
        sprintf(texto, "PAUSE");
        textsurf[i] = TTF_RenderText_Solid(fonte, texto, color);
        tetuta[i] = SDL_CreateTextureFromSurface(Game.screen.renderer, textsurf[i]);
        SDL_RenderCopy(Game.screen.renderer, tetuta[i], NULL, &rect[i]);
    }

    SDL_Rect rect_voltar = {X_RECORD, Y_RECORD * 12, 0,0};
    sprintf(texto, "VOLTAR");
    SDL_Surface *surf = TTF_RenderText_Solid(fonte, texto, color);
    SDL_Texture *textuta = SDL_CreateTextureFromSurface(Game.screen.renderer, surf);
    SDL_RenderCopy(Game.screen.renderer, textuta, NULL, &rect_voltar);

    

}


void runGame_Over(){

}






//MÉTODOS DE ELEMENTOS
void addTower(float cost, Jogador *player){
    
}

void upgrade(Tower *t, Jogador *player){
    //if(t->price_upgrade < d_player){
        t->range += 2;
      //  return 1;
    //}
}

void atirar(Tower t, Minion *alvo){
    
}