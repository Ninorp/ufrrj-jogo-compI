
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "headers/elementosGame.h"

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

//torres

typedef struct tower{
    SDL_Rect srcrect, dstrect;
    int dano;
    float cost;
    float upgrade;
    float intervalo_disparo;
    float range;
} Tower;

int addTower(float cost, float d_player){
    if(cost < d_palyer){
        return 1;
    }    
    return 0;
}

int upgrade(Tower *t, float d_player){
    if(t->price_upgrade < d_player){
        t->range += 2;
        return 1;
    }
}

void atirar(Torre t, Minion *alvo){
    
}

//fim torre

//minions
typedef struct minions{
	
	Life life;
    SDL_Rect srcrect, dstrect;
	int damage;

}Minions;
