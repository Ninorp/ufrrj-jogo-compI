#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define FPS 30
#define MS_PER_FRAME 1000 / FPS

#define SCREEN_W 973
#define SCREEN_H 483
#define SCREEN_SCALE 1
#define SCREEN_NAME "O  J O G O"

#define Y_FONT 18
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

#define X_MENUL_INI 447
#define X_MENUL_FIM 528
#define Y_MENUL_INI 390
#define Y_MENUL_FIM 512

#define VIDA_CHEIA 1000
#define GRANA_CHEIA 500
#define MIN_RECOMPENSA 5
#define MIN_DAMAGE 10

#define X_BARRA_LATERAL SCREEN_W / 1.5
#define BARRA_LATERAL_W SCREEN_W - X_BARRA_LATERAL
#define BARRA_LATERAL_H SCREEN_H

#define TORRE_W 25
#define TORRE_W_FIXA 150
#define TORRE_H_FIXA 50
#define TORRE_H 50
#define TORRE_PRECO_MIN 2
#define X_TORRE_FIXA_INI SCREEN_W / 1.5 + 50
#define X_TORRE_FIXA_FIM X_TORRE_FIXA_INI + TORRE_W
#define Y_TORRE_FIXA_INI SCREEN_H / 6
#define Y_TORRE_FIXA_FIM Y_TORRE_FIXA_INI + TORRE_H

#define MINION_W 20
#define MINION_H 60

#define MAX_MINIONS_POR_ORDA 144
#define MAX_LEVEL 24
#define MIN_MINIONS_POR_ORDA 6

#define PATH_CIRCLE "img/circle.png"
#define TOWER_PNG_N "img/tower_%d.png"

#define CURVA_W 22
#define CURVA_H 35
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
void mGdraw(SDL_Rect srcRect, SDL_Rect destRect, SDL_Surface *surface);
void gdrawProsMinions(SDL_Rect imgRect, SDL_Rect positionRect, SDL_Surface *);
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

void descobreWH(int *, int *, SDL_Surface *);
int colidiu(SDL_Rect, SDL_Rect);
int podeAddTower(SDL_Rect);
int random_int(int min, int max);

void pitagoras(int *a, int *b, int *c);
float velocidadeAtual(float, float, float);
float posicaoAtual(float so, float vo, float a, float t);

struct {
	// define "attributes"
	int running, state, resume;
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
    0,0,0,
	{
		SCREEN_SCALE*SCREEN_W,
		SCREEN_SCALE*SCREEN_H,
		SCREEN_NAME,
		NULL,
		NULL
	},
    {VIDA_CHEIA,GRANA_CHEIA,0, '\0'},
	game_init,
	game_quit
};

typedef struct 
{
    int x, y, xOry, limite;
} CURVA;

typedef struct 
{
    int cont;
    CURVA curva[4];
} ARRAYCURVA;

ARRAUCURVA aCurva;

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



//fim orda

//Towers

typedef struct tower{
    //SDL_Rect srcrect, dstrect;
    int x, y, indeximg;
    int damage;
    float cost;
    float upgrade;
    float intervalo_disparo;
    float range;
    SDL_Surface *icon, *circle;
} Tower;

//minions
typedef struct{
	
	Life life;
    SDL_Rect srcrect, dstrect;
    SDL_Surface *spritesheet;
	int damage, aceleracao, morreu, indexcurva;

}Minion;

//orda
typedef struct orda{
    int qtd;
    float level;
    Minion minion[100];
} Orda;

Orda aMinion;

typedef struct 
{
    int cont;
    Tower tower[100];
} ARRAYTOWER;

ARRAYTOWER aTower;
//metodos dos elementos
void atirar(Tower t, Minion *alvo);

void addTower(Tower t, Jogador *j);

void aumentaOrda();
void mandaOrda();
//float deletarTower(Tower *t);

void upgrade(Tower *t, Jogador *j);

void spotarTowers();

//int endRecs;


//MAIN --------------------------------------------------

int main(int argc, char** argv)
{
    aTower.cont = 0;
    srand( (unsigned)time(NULL) );
    //ARRAYTOWER.tower = (Tower *) malloc(sizeof(Tower) * 10);
    Game.init();
    //int quit = 0;

    aCurva.cont = 0;
    //for(int i = 0; i < 4; i++)
    {
        aCurva.curva[0].x = 225;
        aCurva.curva[0].y = 0;
        aCurva.curva[0].xOry = 225;
        aCurva.curva[0].limite = 225 + CURVA_W;
    aCurva.cont += 1;
        aCurva.curva[1].x = 0;
        aCurva.curva[1].y = 30;
        aCurva.curva[1].xOry = 30;
        aCurva.curva[1].limite = 30 - CURVA_H;
    aCurva.cont += 1;
        aCurva.curva[2].x = 675;
        aCurva.curva[2].y = 0;
        aCurva.curva[2].xOry = 675;
        aCurva.curva[2].limite = 675 + CURVA_W;
    aCurva.cont += 1;
        aCurva.curva[3].x = 0;
        aCurva.curva[3].y = 430;
        aCurva.curva[3].xOry = 430;
        aCurva.curva[3].limite = 430 + CURVA_H;
    aCurva.cont += 1;

    }
    
    while(Game.running) //rodar enquanto nao for para encerrar :)
    {
        unsigned
            comeco =
                SDL_GetTicks();
        clear();
        if(event.type == SDL_QUIT)
        {
            Game.running = 0;
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
    fonte = TTF_OpenFont("FRIZQT.TTF", Y_FONT);
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
    //printf("FOI AQUI1");
    mGdraw(srcRect,destRect, surface);
}

void mGdraw(SDL_Rect srcRect, SDL_Rect destRect, SDL_Surface *surface){
    //printf("ENTROU AQUI1");
    mTexture = SDL_CreateTextureFromSurface(Game.screen.renderer, surface);
    

    if(destRect.h > 0 && destRect.w > 0)
        SDL_RenderCopy(Game.screen.renderer, mTexture, &srcRect, &destRect);
    else
        SDL_RenderCopy(Game.screen.renderer, mTexture, NULL, NULL);
    //printf("FOI AQUI5 ");
    SDL_DestroyTexture(mTexture);
    //printf(" saiu ");
}

void gdrawProsMinions(SDL_Rect imgRect, SDL_Rect positionRect, SDL_Surface *spritesheet){
    mGdraw(imgRect, positionRect, spritesheet);
}

void refresh(){
    SDL_RenderPresent(Game.screen.renderer);
}

void clear(){
    SDL_SetRenderDrawColor(Game.screen.renderer,0,0,0,255);
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
            aTower.cont = 0;
            Game.jogador.vida = VIDA_CHEIA;
            Game.jogador.grana = GRANA_CHEIA;
            Game.jogador.pontuacao = 0;
            Game.jogador.nome[0] = '\0';
            printf("resetei");
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
            Game.quit();
        }
        return;
    }
    while(SDL_PollEvent(&event)){
        if(menu.enterPressed)
            break;

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
                    menu.enterPressed = 1;
                    break;                
            }    
        } else if(event.type == SDL_MOUSEMOTION)
        {
            int x = event.motion.x;
            int y = event.motion.y;
            SDL_Rect mouse = {x, y, 0, 0};
            SDL_Rect item_menu = {X_MENU + menu.cursor_position.w, Y_MENU, 150, Y_FONT_MENU};

            for (int i = 0; i < 5; i++)
            {
                item_menu.y = Y_MENU + Y_FONT_MENU * i;
                if (colidiu(mouse, item_menu))
                {
                    menu.opcao = i;
                    menu.cursor_position.y = Y_MENU + Y_FONT_MENU * i;
                }
            }
        } else if(event.type == SDL_MOUSEBUTTONDOWN){
            SDL_Rect mouse = {event.button.x, event.button.y, 0, 0};
            SDL_Rect button = {X_MENU + menu.cursor_position.w, (Y_MENU + (Y_FONT_MENU * menu.opcao)), 150, Y_FONT_MENU};

            //printf(" x = %d, y = %d", x, y);
            if (colidiu(mouse, button))
            {
                menu.enterPressed = 1;
            }
        }
        if(menu.opcao == 1)
        {
            break;
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
    carregaBackground("img/backrecord.png");
    //printf("%d cont",recs.cont);
    if (recs.cont > 0)
    {
        
        //SDL_Rect rect[10];
        SDL_Surface *textsurf;
        

        char texto[50] = "";
        SDL_Color color = {0, 0, 0, 255};
        int texW = 0;
        int texH = 0;
        for (int i = 0; i < recs.cont; i++)
        {
            
           // printf("5");
            sprintf(texto, "%d :: %s :: %d", i + 1, recs.jogador[i].nome, recs.jogador[i].pontuacao);
            //printf("%s", texto);
            textsurf = TTF_RenderUTF8_Solid(fonte, texto, color);
            descobreWH(&texW, &texH, textsurf);
            //tetuta[i] = SDL_CreateTextureFromSurface(Game.screen.renderer, textsurf[i]);
            //SDL_RenderCopy(Game.screen.renderer, tetuta[i], NULL, &rect[i]);
            gdraw(X_RECORD, Y_RECORD + (texH * (i + 1)), texH, texW, textsurf);
            //printf("7");
            SDL_FreeSurface(textsurf);
        }
    }
    /*SDL_Rect rect_voltar = {X_RECORD, Y_RECORD * 12, 0,0};
    sprintf(texto, "VOLTAR");
    SDL_Surface *surf = TTF_RenderUTF8_Solid(fonte, texto, color);
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

void spotarMapa();

void spotarMapa(){
    SDL_Surface *mapa = IMG_Load("img/mapa.png");
    gdraw(0,0,483,700, mapa);
    SDL_FreeSurface(mapa);
}

void spotarDadosJogador();
void spotarDadosJogador(){
    SDL_Surface *textsurf;
        

        char texto[50] = "";
        SDL_Color color = {0, 0, 0, 255};
        int texW = 0;
        int texH = 0;
        //for (int i = 0; i < recs.cont; i++)
        {
            
           // printf("5");
            sprintf(texto, "Pontuação: %d", Game.jogador.pontuacao);
            //printf("%s", texto);
            textsurf = TTF_RenderUTF8_Solid(fonte, texto, color);
            descobreWH(&texW, &texH, textsurf);
            //printf("\nH = %d e W = %d\n", texH, texW);
            //tetuta[i] = SDL_CreateTextureFromSurface(Game.screen.renderer, textsurf[i]);
            //SDL_RenderCopy(Game.screen.renderer, tetuta[i], NULL, &rect[i]);
            gdraw(X_TORRE_FIXA_INI, 300, texH, texW, textsurf);
            //printf("7");
            SDL_FreeSurface(textsurf);

            sprintf(texto, "Vida: %d", Game.jogador.vida);
            //printf("%s", texto);
            textsurf = TTF_RenderUTF8_Solid(fonte, texto, color);
            descobreWH(&texW, &texH, textsurf);
            //printf("\nH = %d e W = %d\n", texH, texW);
            //tetuta[i] = SDL_CreateTextureFromSurface(Game.screen.renderer, textsurf[i]);
            //SDL_RenderCopy(Game.screen.renderer, tetuta[i], NULL, &rect[i]);
            gdraw(X_TORRE_FIXA_INI, 300 + texH * 1, texH, texW, textsurf);
            //printf("7");
            SDL_FreeSurface(textsurf);

            sprintf(texto, "Dinheiro: %.0f", Game.jogador.grana);
            //printf("%s", texto);
            textsurf = TTF_RenderUTF8_Solid(fonte, texto, color);
            descobreWH(&texW, &texH, textsurf);
            //printf("\nH = %d e W = %d\n", texH, texW);
            //tetuta[i] = SDL_CreateTextureFromSurface(Game.screen.renderer, textsurf[i]);
            //SDL_RenderCopy(Game.screen.renderer, tetuta[i], NULL, &rect[i]);
            gdraw(X_TORRE_FIXA_INI, 300 + texH * 2, texH, texW, textsurf);
            //printf("7");
            SDL_FreeSurface(textsurf);
        }
}

struct 
{
    int pegouTorre, prendeuTorre;
    int towerPresa;
    SDL_Rect position;
} MOUSE = {0,0,-1, {0,0,0,0}};

int xNovaTorre, yNovaTorre;
void runGame()
{
    //printf("entrou1");
    Tower towersFixas[2];
    char path[100];
    for(int i = 1; i < 3; i++)
    {
        sprintf(path,"img/tower_fixa_%d.png", i);
        towersFixas[i-1].icon = IMG_Load(path);
        towersFixas[i-1].indeximg = i;
    }
    
    spotarMapa();


    
    // if (Game.resume)
    {
        //Game.resume = 0;
    }
   // else
    {

        //iniciar o jogo
        spotarTowers();
        //printf("PASSEI");
        SDL_Surface *img = IMG_Load("img/back.png");
        //printf("1");
        gdraw(X_BARRA_LATERAL, 0, BARRA_LATERAL_H, BARRA_LATERAL_W, img);
        SDL_FreeSurface(img);
        spotarDadosJogador();

        //gdraw(X_TORRE_FIXA_INI, Y_TORRE_FIXA_INI + (TORRE_H * 0), 50, 50, towersFixas[0].icon);
        for (int i = 0; i < 2; i++)
        {
            //towersFixas[i - 1].circle = IMG_Load(PATH_CIRCLE);
            towersFixas[i].x = X_TORRE_FIXA_INI;
            towersFixas[i].y = Y_TORRE_FIXA_INI + (TORRE_H_FIXA * (i));
            towersFixas[i].damage = 2 + 8 * i;
            towersFixas[i].cost = 20 + 80 * i;
            towersFixas[i].upgrade = 50;
            towersFixas[i].intervalo_disparo = 3;
            towersFixas[i].range = 20;
            gdraw(towersFixas[i].x, towersFixas[i].y, TORRE_H_FIXA, TORRE_W_FIXA, towersFixas[i].icon);
           // printf("i ");
        }
    }
    if (Game.jogador.vida)
    {
        //MANDA OS MINIONS E O CARAMBA A 4
    }
    else
    {
        //DEU BLAYBEYDE PARA O CARINHA, GAME OVER, BABY
        Game.state = 4;
        return;
    }
    //printf("P2");
    while (SDL_PollEvent(&event))
    {
      //  printf("event.type = %d", event.type);
        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                Game.state = 2;
                break;
            }
        } else if(event.type == SDL_MOUSEBUTTONUP)
        {
            switch (event.button.button)
            {
            case  SDL_BUTTON_LEFT:
                if (MOUSE.pegouTorre && MOUSE.prendeuTorre && event.button.state == SDL_RELEASED)
                {
                    SDL_Rect mouseComTower = {MOUSE.position.x , MOUSE.position.y, TORRE_W, TORRE_H};
                    MOUSE.pegouTorre = MOUSE.prendeuTorre = 0;  
                    if (podeAddTower(mouseComTower))
                    {
                        //gdraw(MOUSE.position.x - TORRE_W / 2, MOUSE.position.y - TORRE_H / 2, TORRE_H, TORRE_W - 100, towersFixas[MOUSE.towerPresa].icon);
                        

                        addTower(towersFixas[MOUSE.towerPresa], &(Game.jogador));
                               
                        printf("SOLTEI A TORRE\n");
                        //addTower()
                    }
                }
                break;
            default:
                break;
            }
            
        }
        
        else if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                MOUSE.position.x = event.button.x;
                MOUSE.position.y = event.button.y;

                SDL_Rect item_towers = {X_TORRE_FIXA_INI, Y_TORRE_FIXA_INI, TORRE_W_FIXA, TORRE_H_FIXA};

                if (event.button.state == SDL_PRESSED)
                {
                    /* code */
                    //printf("1");
                    for (int i = 0; i < 2; i++)
                    {
                        item_towers.y = Y_TORRE_FIXA_INI + TORRE_H_FIXA * (i);
                        
                        if ((MOUSE.pegouTorre = colidiu(MOUSE.position, item_towers)))
                        {
                            MOUSE.prendeuTorre = 1;
                            MOUSE.towerPresa = i;
                            printf("\nxm = %d, ym = %d, x = %d, y = %d\n", MOUSE.position.x, MOUSE.position.y, item_towers.x, item_towers.y);
                            break;
                        }
                    }
                }
                else
                {
                    /* code */
                }

                               
            }
            
        }
        else if (event.type == SDL_MOUSEMOTION)
        {
            MOUSE.position.x = event.motion.x;
            MOUSE.position.y = event.motion.y;
            
            SDL_Rect item_towers = {X_TORRE_FIXA_INI, Y_TORRE_FIXA_INI, TORRE_W_FIXA, TORRE_H};

            if (event.motion.state == SDL_PRESSED)  
            {
                /* code */
                //printf("1");             
            }
            else
            {
                /* code */
            }

            for (int i = 0; i < 3; i++)
            {
                item_towers.y = Y_TORRE_FIXA_INI + TORRE_H * i;
                if (colidiu(MOUSE.position, item_towers))
                {
                    //printf("2");
                }
            }
        }
        
        
        
        if (Game.state != 1)
            break;
    }
    //printf(" passeiporaqui ");
    if(MOUSE.pegouTorre && MOUSE.prendeuTorre)
    {
        xNovaTorre = MOUSE.position.x - (TORRE_W / 2);
        yNovaTorre = MOUSE.position.y - (TORRE_H / 2);
        //printf(" printaquedeumerda ");
        sprintf(path,"img/tower_%d.png", towersFixas[MOUSE.towerPresa].indeximg);
        
        SDL_Surface *tempSurface = IMG_Load(path);
        gdraw(xNovaTorre, yNovaTorre, TORRE_H, TORRE_W, tempSurface);
        SDL_FreeSurface(tempSurface);          
    }
  //SDL_FreeSurface(MOUSE.towerPresa.icon);
    for (int i = 0; i < 2; i++)
    {
        SDL_FreeSurface(towersFixas[i].icon);
    }
    for(int i = 0; i <= aTower.cont; i++)
    {
        //SDL_FreeSurface(aTower.tower[i].icon);
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
               // printf("x = %d, y = %d", x, y);
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
        if(Game.state != 2){
            if(Game.state == 1){
                Game.resume = 1;
            }
            break;
        }
            
    }
}


 char *composition;
 Sint32 cursor;
 Sint32 selection_len;


void runGame_Over(){
    if(SDL_IsTextInputActive == SDL_FALSE){
        SDL_StartTextInput();
        //Game.jogador.pontuacao = 100;
    }
    carregaBackground("img/gameover.png");

    SDL_Surface *textsurf;
    SDL_Texture *tempTexture;
    char texto[50];

    SDL_Color color = {255, 255, 255, 255};
    int texW = 0;
    int texH = 0;

    textsurf = TTF_RenderUTF8_Solid(fonte, Game.jogador.nome, color);
    tempTexture = SDL_CreateTextureFromSurface(Game.screen.renderer, textsurf);
    SDL_QueryTexture(tempTexture, NULL, NULL, &texW, &texH);
    SDL_DestroyTexture(tempTexture);
    gdraw(342, 248, texH, texW, textsurf);
    //Game.jogador.pontuacao = 95;
    sprintf(texto, "Sua pontuação: %d", Game.jogador.pontuacao);
    textsurf = TTF_RenderUTF8_Solid(fonte, texto, color);
    
    tempTexture = SDL_CreateTextureFromSurface(Game.screen.renderer, textsurf);
    SDL_QueryTexture(tempTexture, NULL, NULL, &texW, &texH);
    SDL_DestroyTexture(tempTexture);
    gdraw(339, 280, texH, texW, textsurf);

    SDL_FreeSurface(textsurf);

    

    while(SDL_PollEvent(&event)){
        if(event.type==SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    Game.state = 0;                
                    break;
                /*case SDLK_BACKSPACE:
                    
                    break;*/
            }
            if(event.key.keysym.sym == SDLK_BACKSPACE){
                size_t tam = strlen(Game.jogador.nome);
                if (tam > 0)
                {
                    Game.jogador.nome[tam - 1] = '\0';
                }
            }
                    
        }
        else if(event.type == SDL_MOUSEBUTTONDOWN){
            if(event.button.button == SDL_BUTTON_LEFT){
                SDL_Rect mouse = {event.button.x, event.button.y, 0, 0};
                SDL_Rect button = {X_MENUL_INI, Y_MENUL_INI, X_MENUL_FIM - X_MENUL_INI, Y_MENUL_FIM - Y_MENUL_INI};
                
               //printf(" x = %d, y = %d", x, y);
                if (colidiu(mouse, button))
                {
                    Game.state = 0;
                }
            }
        } else if(event.type == SDL_TEXTINPUT){
            strcat(Game.jogador.nome, event.text.text);
        } else if(event.type == SDL_TEXTEDITING){
            composition = event.edit.text;
            cursor = event.edit.start;
            selection_len = event.edit.length;
            strcmp(Game.jogador.nome, composition);
            
        }

        if (Game.state != 3)
        {
            SDL_StopTextInput();
            if(strlen(Game.jogador.nome) > 0){
                Records recs;
                leRecords(&recs);
                
                gravaRecord(&recs, Game.jogador);
                Game.jogador.vida = VIDA_CHEIA;
                Game.jogador.pontuacao = 0;
                Game.jogador.grana = GRANA_CHEIA;
            }
            
            break;
        }
    }
}






//MÉTODOS DE ELEMENTOS
void addTower(Tower t, Jogador *player){
    if(aTower.cont >= 100)
        return;
    printf(" %f , %f\n", Game.jogador.grana, t.cost);
    if(player->grana >= t.cost){
        player->grana -= t.cost;
        int i = aTower.cont;
        Tower *tw = &(aTower.tower[i]);

        *tw = t;
        tw->x = xNovaTorre;
        tw->y = yNovaTorre;
        //char path[100];
        //sprintf(path,TOWER_PNG_N, t.indeximg);
       // tw->icon = IMG_Load(path);
        printf(" %d %d %d ", tw->x, tw->y, aTower.cont+1);

        aTower.cont += 1;
    }
}

void upgrade(Tower *t, Jogador *player){
    //if(t->price_upgrade < d_player){
        t->range += 2;
      //  return 1;
    //}
}

#define MINION_PNG_N "img/minion_%d.png"
#define Y_PORTAL 264*2
#define PORTAL_H 22



void criaMinions();
void criaMinions(){
    int div = aMinion.qtd / 3;
    int x_start = -15;
    //int k = 0;
    for(int i = 0; i < 3; i++)
    {
        char path[100];
        for(int j = div * i; j < div * (i+1); j++)
        {
            sprintf(path, MINION_PNG_N, i+1);
            aMinion.minion[j].spritesheet = IMG_Load(path);
            aMinion.minion[j].life = {0, NULL, NULL};
            aMinion.minion[j].damage = MIN_DAMAGE * (i+1);  
            aMinion.minion[j].dstrect.x = x_start;
            aMinion.minion[j].dstrect.y = random_int(Y_PORTAL, Y_PORTAL + PORTAL_H);
            aMinion.minion[j].morreu = aMinion[j].indexcurva = 0;
            //aMinion.minion[j].aceleracao = 
            x_start -= 15;
        }
    }
    
}
void quemMorreu();
void quemMorreu(){
    for(int i = 0; i < aMinion.qtd; i++){
        if(aMinion.minion[i].life.cont == 0 && aMinion.minion[i].morreu == 0)
        {
            aMinion.minion[i].morreu = 1;            
        }        
    }
}

int morreramTodos();
int morreramTodos(){
    for(int i = 0; i < aMinion.qtd; i++){
        if(aMinion[i].morreu > 0)
        {
            quemMorreu();
            return 0;
        }
        
    }
    return 1;
}

void movimentaMinions();
void movimentaMinions(){
    for(int i = 0; i < aMinion.qtd; i++){
        if(morreramTodos()){
            aMinion.qtd = 0;
            return;
        }
            
        if(!aMinion.minion[i].morreu){
            int x = &(aMinion.minion[i].dstrect.x);
            int y = &(aMinion.minion[i].dstrect.y);
            int indexcurva = &(aMinion.minion[i].indexcurva);

            if(x < aCurva.curva[indexcurva].x)
            {
                x++;
            }
            else if(x < aCurva.curva[indexcurva].limite 
                && aCurva.curva[indexcurva].x == aCurva.curva[indexcurva].xOry )
            {
                int escolha = random_int(0,2);
                if(escolha)
                    x++;
                else{
                    y++;
                    indexcurva++;
                }
                    
            } else if(y > aCurva.curva[indexcurva].y)
            {
                y--;
            }
            else if(y > aCurva.curva[indexcurva].limite 
                && aCurva.curva[indexcurva].y == aCurva.curva[indexcurva].xOry )
            {
                int escolha = random_int(0,2);
                if(escolha)
                    y--;
                else{
                    x++;
                    indexcurva++;
                }
                    
            } else if(y < aCurva.curva[indexcurva].y)
            {
                y++;
            }
            else if(y < aCurva.curva[indexcurva].limite 
                && aCurva.curva[indexcurva].y == aCurva.curva[indexcurva].xOry )
            {
                int escolha = random_int(0,2);
                if(escolha)
                    y++;
                else{
                    x++;
                    indexcurva++;
                }                    
            }
        }

    }
}

void mandaOrda(){
    if(aMinion.qtd == 0)
    {
        aMinion.level += 1;
        if(aMinion.level >= MAX_LEVEL)
            aMinion.level = MAX_LEVEL;
        aMinion.qtd = MIN_MINIONS_POR_ORDA * aMinion.level;
        criaMinions();
    }
    else
    {
        movimentaMinions();
    }
    
}

void atirar(Tower t, Minion *alvo){
    
}

SDL_Surface *mSurface;
void spotarTowers(){
    
    for(int i = 0; i < aTower.cont; i++)
    {
       // printf("\n%d  ", i);
        Tower *tw = &(aTower.tower[i]);
        {
            char path[100];
            sprintf(path,"img/tower_%d.png", tw->indeximg);
            //printf("\n%s\n", path);
            mSurface = IMG_Load(path);
        //    printf(" MODIFICOU ");
        }
        
        //if(tw->icon != NULL)
        {
           // printf(" %d %d %d ere \n", tw->x, tw->y, 0  );
            
            gdraw(tw->x, tw->y, TORRE_H, TORRE_W, mSurface);
            SDL_FreeSurface(mSurface);
            //printf(" TERMINEI ");
        }
        
       
    }
    
}


///MONITORADORES DESSA JOÇA ---------------------------------- #MERESPEITA


int colidiu(SDL_Rect de, SDL_Rect com){
    
    if ((de.x >= com.x && (de.x + de.w) <= (com.x + com.w)) 
        && (de.y >= com.y && (de.y + de.h) <= (com.y + com.h)))
    {
        return 1;
    }
    //printf(" x=%d e y=%d || x=%d e y=%d , h=%d e w=%d", de.x, de.y, com.x, com.y, com.h, com.y );
    return 0;
}

int podeAddTower(SDL_Rect mouseComTower){
    int x = mouseComTower.x;
    int y = mouseComTower.y;
    int w = mouseComTower.w;
    int h = mouseComTower.h;
    if(x < X_BARRA_LATERAL){
        
        SDL_Rect rectTower = {0,0, TORRE_W, TORRE_H};
        for(int i = 0; i < aTower.cont; i++)
        {
            rectTower.x = aTower.tower[i].x;
            rectTower.y = aTower.tower[i].y;
            if(colidiu(mouseComTower, rectTower))
                return 0;
        }
        
        
        
    } else {
        return 0;
    }
    return 1;
}

void descobreWH(int *w, int *h, SDL_Surface *surface){
    SDL_Texture *tempoTexture = SDL_CreateTextureFromSurface(Game.screen.renderer, surface);
    SDL_QueryTexture(tempoTexture, NULL, NULL, w, h);
    SDL_DestroyTexture(tempoTexture);
}

int random_int(int min, int max)
{
   return min + rand() % (max+1 - min);
}


///CAUCULOS MATEMÁTICOS E FÍSICOS ------------

void pitagoras(int *a, int *b, int *c){
    if(*a == 0)
    {
        /* code: PITÁBORAS PARA A */
    }
    else if(*b == 0)
    {
        /* code: PITÁGORAS PARA B */
    }
    else
    {
        /* code PITÁBORAS PARA C*/
    }
    
}

float velocidadeAtual(float vo, float a, float t){
    return vo + a * t;
}

float posicaoAtual(float so, float vo, float a, float t){
    return so + vo * t + (a*t) / 2;
}