#ifndef UNIVERSOGAME
#define UNIVERSOGAME


typedef enum game_states Game_States;

typedef struct screen Screen;
typedef struct records Records;
typedef struct menu Menu;
typedef struct jogador Jogador;
typedef struct game GameS;
typedef struct gameOver GameOver;


void game_init(void);
void game_quit(void);
void runMenu(int first);
void opcoesTela();
void recordTela(Records recs);
void gravaRecord(Jogador jog);
Recordes leRecords();



//musicas
Mix_Music* musica;
Mix_Music* fase;
Mix_Chunk* explosao;

SDL_Event event;

TTF_Font* fonte;



#endif