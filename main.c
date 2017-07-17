#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>

#define FPS 30
#define MS_PER_FRAME 1000 / FPS

#define SCREEN_W 973
#define SCREEN_H 483
#define SCREEN_SCALE 1
#define SCREEN_NAME "O  J O G O"

#define Y_FONT 16
#define Y_FONT_MENU 39
#define Y_MENU 278
#define X_MENU 650
#define Y_RECORD 120
#define X_RECORD SCREEN_W / 8
#define X_VOLTA_INI 424
#define X_VOLTA_FIM 555
#define Y_VOLTA_INI 200
#define Y_VOLTA_FIM 235
#define X_ABANDONAR_INI 395
#define X_ABANDONAR_FIM 580
#define Y_ABANDONAR_INI 270
#define Y_ABANDONAR_FIM 300

//struchs do universo
typedef enum
{
  MENU = 0,
  PLAY = 1,
  PAUSE = 2,
  GAMEOVER = 3
} Game_States;




typedef struct {
    Mix_Music* musica;
    Mix_Music* toque;
    int opcao, enterPressed;
    SDL_Surface *cursor_img;
    SDL_Texture *cursor;
    SDL_Rect cursor_position;
    SDL_Surface *m_img;
    SDL_Texture *img_text;
} Menu;

typedef struct {
    float grana;
    int vida, pontuacao;
    char nome[50];
} Jogador;

typedef struct{
    int cont;
    Jogador jogador[10];
} Records;

typedef struct{
    Mix_Music* musica;
    Mix_Music* toque;
    int opcao;
    SDL_Surface  *img;
} GameOver;


//metodos do universo

void game_init(void);
void game_quit(void);
void gdraw(int x, int y, int h, int w, SDL_Surface *surface);
void refresh();
void clear();
void runGame();
void pauseGame();
void runGame_Over();
void carregaBackground(char caminho[]);
void runMenu();
void imgToWindowFull(char caminho[]);
void recordTela(Records recs);
void gravaRecord(Records *recs, Jogador jog);
void leRecords(Records *);
void sort(Records *);
void bubble_sort(Jogador *, int);
//void insere(Records *, Jogador);
void remove_posicao(Records *, int);


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
    Jogador jogador;
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
    {1000,1000,0, '\0'},
	game_init,
	game_quit
};

/*typedef struct{
    int cont;
    char *id;
    SDL_Texture *mTexture;
} arrayTexture;
*/
//váriáveis globais do universo
//Screen screen = {0,0,0,0};
//static GameS Game = {0, screen, 0, game_init, game_quit};
Menu menu;
//arrayTexture mapTexture;
SDL_Texture *mTexture;
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


//int endRecs;


//MAIN --------------------------------------------------

int main(int argc, char** argv)
{
    
   
    Game.init();
    //int quit = 0;
    while(Game.running) //rodar enquanto nao for para encerrar :)
    {
        unsigned
            comeco =
                SDL_GetTicks();
        clear();
        if(event.type == SDL_QUIT)
        {
            Game.quit();
        }
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
        unsigned
            fim =
                SDL_GetTicks();
        unsigned
            delta =
                fim -
                comeco;
        if (delta <
            MS_PER_FRAME)
        {
            SDL_Delay(MS_PER_FRAME -
                      delta);
        }
        //printf(" %llf ", delta);
        refresh();
       
    }

    Game.quit(); //encerrar a SDL
    return 0;
}

//MAIN -------------------------------------------------- fim






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
    musica=Mix_LoadMUS("music/menu.mp3");

   // Jogador j = {0,0,50, "2CARINHA"};
    //for(int i = 0; i < 10; i++)
   // Records recs;
   // printf("->");
   // leRecords(&recs);
   // printf("->2");
   // gravaRecord(&recs, j);

	Game.running = 1;
    Game.state = 0;
}

void gdraw(int x, int y, int h, int w, SDL_Surface *surface){
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = destRect.w = w;
    srcRect.h = destRect.h = h;
    destRect.x = x;
    destRect.y = y;
    mTexture = SDL_CreateTextureFromSurface(Game.screen.renderer, surface);
    if(h > 0 && w > 0)
        SDL_RenderCopy(Game.screen.renderer, mTexture, &srcRect, &destRect);
    else
        SDL_RenderCopy(Game.screen.renderer, mTexture, NULL, NULL);
    SDL_DestroyTexture(mTexture);
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
    exit(-1);
}

void runMenu(){    
    Records recs; 
    if(menu.m_img == NULL){
        Mix_PlayMusic( musica, -1 );
        menu.opcao = 0;
        menu.m_img =  IMG_Load("img/backmenu.png");
        menu.cursor_img = IMG_Load("img/cursor.png");
        menu.cursor_position.x = X_MENU;
        menu.cursor_position.y = Y_MENU;
        menu.cursor_position.h = 45;
        menu.cursor_position.w = 45;
        menu.cursor = SDL_CreateTextureFromSurface(Game.screen.renderer, menu.cursor_img);
        menu.img_text = SDL_CreateTextureFromSurface(Game.screen.renderer, menu.m_img);

        SDL_FreeSurface(menu.m_img);
        SDL_FreeSurface(menu.cursor_img);
    }
    if(menu.enterPressed == 0){
    SDL_RenderCopy(Game.screen.renderer, menu.img_text, NULL, NULL);
    SDL_RenderCopy(Game.screen.renderer, menu.cursor, NULL, &menu.cursor_position);
    } else {
        if (!menu.opcao)
        {
            Game.state = 1;
        }
        else if (menu.opcao == 1)
        {
            imgToWindowFull("img/instrucoes.jpg");
        }
        else if (menu.opcao == 2)
        {
            
            leRecords(&recs);
           // printf(" passou ");
            recordTela(recs);
            //imgToWindowFull("img/background.jpg");
        }
        else if (menu.opcao == 3)
        {
            imgToWindowFull("img/sobre.jpg");
        }
        else
        {
            //Game.quit();
        }
        return;
    }
    while(SDL_PollEvent(&event)){
        
        if(event.type == SDL_KEYDOWN){
            
            switch(event.key.keysym.sym)                    
            {                        
                case SDLK_DOWN:
                    if(menu.cursor_position.y < (Y_MENU + 4 * Y_FONT_MENU)){
                        menu.cursor_position.y += Y_FONT_MENU;
                        menu.opcao += 1;
                    } else{
                        menu.cursor_position.y = Y_MENU;
                        menu.opcao = 0;
                    }
                    break;
                case SDLK_UP:
                    if(menu.cursor_position.y > Y_MENU){
                        menu.cursor_position.y -= Y_FONT_MENU;
                        menu.opcao -= 1;
                    } else{
                        menu.cursor_position.y = Y_MENU + 4 * Y_FONT_MENU;
                        menu.opcao = 4;
                    }
                    break;
                case SDLK_RETURN:
                    if(!menu.opcao){
                        Game.state = 1;                        
                    }
                    else if(menu.opcao == 1){
                        imgToWindowFull("img/instrucoes.jpg");
                    } else if(menu.opcao == 2){
                        
                        leRecords(&recs);
                        
                        //Records *recs;
                        //leRecords(recs);
                        //printf(" passou ");
                        recordTela(recs);
                       //imgToWindowFull("img/background.jpg");
                    } else if(menu.opcao == 3){
                        imgToWindowFull("img/sobre.jpg");
                    } else{
                        Game.quit();
                    }
                    menu.enterPressed = 1;
                    break;                
            }    
        }
    }
}

void leRecords(Records *recs){
    int i, k;
    //Records recs;
    recs->cont = 0;    
    Jogador gamer;
   // printf("0");
    FILE* f;
    f = fopen("record.bin", "rb");
    if (f != NULL)
    {
        //printf("1");
        for(i = 0; i < 10; i++)
        {
            fseek(f, i * sizeof(Jogador), SEEK_SET);
            int size = fread(&gamer, sizeof(Jogador), 1, f);
     //       printf("1.1");
		    if (size > 0 && gamer.nome != '\0'){
                
                recs->jogador[recs->cont] = gamer;
                recs->cont += 1;
      //          printf("%s", recs->jogador[recs->cont].nome);
            }
           // printf("2");
        }
        fclose(f);
    }
    //printf("3");
    //printf(" %d cont",recs->cont);
    //return recs;
}

void carregaBackground(char caminho[]){
    SDL_Surface *background = IMG_Load(caminho);
    //SDL_Texture *back = SDL_CreateTextureFromSurface(Game.screen.renderer, background);
    //SDL_RenderCopy(Game.screen.renderer, back, NULL, NULL);
    gdraw(0,0,0,0, background);
    SDL_FreeSurface(background);
}

void gravaRecord(Records *recs, Jogador jog){
    //Records recs; 
    //leRecords(&recs);
    //Records *recs;
    //leRecords(recs);
    //Jogador aux;
    //printf("1");
    if(recs->cont < 10)
    {
        recs->jogador[recs->cont] = jog;
        recs->cont += 1;
        //printf("1.0.1");
    }
    else
    {
        Jogador menor_recorde;
        menor_recorde = recs->jogador[10-1];
        
        if(menor_recorde.pontuacao >= jog.pontuacao)
        {
            //printf("1.ret");
            return;
        }
        else
        {
            //printf("1.0.2");
            remove_posicao(recs, 10 - 1);
            gravaRecord(recs, jog);
            return;
        }
    }
    //printf("1.sort");
    sort(recs);
    //printf("1.open");
    FILE *fPtr = fopen("record.bin", "wb");
    //int k;
    for(int i = 0; i < recs->cont; i++){
        fseek(fPtr, i * sizeof(Jogador), SEEK_SET);
		fwrite(&recs->jogador[i], sizeof(Jogador), 1, fPtr);
    }
    //printf("1.fim");
    fclose(fPtr);

}

void remove_posicao(Records *array, int posicao)
{
	if(array->cont == 0)
	{
		return;
	}
	else if(array->cont == 1)
	{
		array->cont -= 1;
		return;
	}
	else
	{
		array->cont -= 1;
		array->jogador[posicao] = array->jogador[array->cont];
	}
    
    sort(array);
}

void sort(Records *array)
{
	bubble_sort(array->jogador, array->cont);
}

void bubble_sort(Jogador list[], int n)
{
	int i, j;
    Jogador swap;

	for(i = 0 ; i < ( n - 1 ); i++)
	{
		for(j = 0 ; j < n - i - 1; j++)
		{
			if(list[j].pontuacao < list[j+1].pontuacao)
			{ 
				swap = list[j];
				list[j] = list[j+1];
				list[j+1] = swap;
			}
		}
	}
}

void recordTela(Records recs){
    carregaBackground("img/background.jpg");
    //printf("%d cont",recs.cont);
    if (recs.cont > 0)
    {
        
        //SDL_Rect rect[10];
        SDL_Surface *textsurf;
        SDL_Texture *tempTexture;

        char texto[50] = "";
        SDL_Color color = {0, 0, 0, 255};
        int texW = 0;
        int texH = 0;
        for (int i = 0; i < recs.cont; i++)
        {
            
           // printf("5");
            sprintf(texto, "%d :: %s :: %d", i + 1, recs.jogador[i].nome, recs.jogador[i].pontuacao);
            //printf("%s", texto);
            textsurf = TTF_RenderText_Solid(fonte, texto, color);
            tempTexture = SDL_CreateTextureFromSurface(Game.screen.renderer, textsurf);
            SDL_QueryTexture(tempTexture, NULL, NULL, &texW, &texH);
            SDL_DestroyTexture(tempTexture);
            //tetuta[i] = SDL_CreateTextureFromSurface(Game.screen.renderer, textsurf[i]);
            //SDL_RenderCopy(Game.screen.renderer, tetuta[i], NULL, &rect[i]);
            gdraw(X_RECORD, Y_RECORD + (texH * (i + 1)), texH, texW, textsurf);
            //printf("7");
            SDL_FreeSurface(textsurf);
        }
    }
    /*SDL_Rect rect_voltar = {X_RECORD, Y_RECORD * 12, 0,0};
    sprintf(texto, "VOLTAR");
    SDL_Surface *surf = TTF_RenderText_Solid(fonte, texto, color);
    SDL_Texture *textuta = SDL_CreateTextureFromSurface(Game.screen.renderer, surf);
    SDL_RenderCopy(Game.screen.renderer, textuta, NULL, &rect_voltar);*/
    
    while(SDL_PollEvent(&event)){
        if(event.type==SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    runMenu();
                   // menu.opcao = 0;
                    menu.enterPressed = 0;
                    break;
            }        
        } /*else if(event.type == SDL_MOUSEBUTTONDOWN){
            if(event.button.button == SDL_BUTTON_LEFT){
                int x = event.button.x;
                int y = event.button.y;

                if((x >= X_RECORD && x <= X_RECORD + 26 * 6) 
                    && (y >= Y_RECORD * 12 && y <= Y_RECORD * 12 + 26 * 6)){
                        runMenu();
                        //menu.opcao = 0;
                        menu.enterPressed = 0;
                    }
            }
        }*/
        if(!menu.enterPressed)
            break;
    }

    
}

void imgToWindowFull(char caminho[]){
    carregaBackground(caminho);
    while(SDL_PollEvent(&event)){
        if(event.type==SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    runMenu();
                    //menu.opcao = 0;
                    menu.enterPressed = 0;
                    break;
            }        
        }
        if(!menu.enterPressed)
            break;
    }
}

void runGame(){
     while(SDL_PollEvent(&event)){
        if(event.type==SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    Game.state = 2;                
                    break;
            }        
        }
        else if(event.type == SDL_MOUSEBUTTONDOWN){
            if(event.button.button == SDL_BUTTON_LEFT){
                int x = event.button.x;
                int y = event.button.y;
                //printf("x = %d, y = %d", x, y);
                /*if ((x >= 424 && x <= 554) && (y >= 200 && y <= 234))
                {
                    Game.state = 1;
                }*/
            }
        }
        if(Game.state != 1)
            break;
    }
}

void pauseGame(){
    
    SDL_Surface *img = IMG_Load("img/pause.png");
    //SDL_Texture *back = SDL_CreateTextureFromSurface(Game.screen.renderer, background);
    //SDL_RenderCopy(Game.screen.renderer, back, NULL, NULL);
    gdraw(SCREEN_W/4, SCREEN_H/8, 293, 486, img);
    SDL_FreeSurface(img);
    while(SDL_PollEvent(&event)){
        if(event.type==SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    Game.state = 1;                
                    break;
            }        
        }
        else if(event.type == SDL_MOUSEBUTTONDOWN){
            if(event.button.button == SDL_BUTTON_LEFT){
                int x = event.button.x;
                int y = event.button.y;
                printf("x = %d, y = %d", x, y);
                if ((x >= X_VOLTA_INI && x <= X_VOLTA_FIM) && (y >= Y_VOLTA_INI && y <= Y_VOLTA_FIM))
                {
                    Game.state = 1;
                } 
                else if ((x >= X_ABANDONAR_INI && x <= X_ABANDONAR_FIM) && (y >= Y_ABANDONAR_INI && y <= Y_ABANDONAR_FIM))
                {
                    Game.state = 0;
                    menu.opcao = 0;
                    menu.enterPressed = 0;
                }
            }
        }
        if(Game.state != 2)
            break;
    }
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