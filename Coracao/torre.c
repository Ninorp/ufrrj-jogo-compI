#include <stdio.h>
#include <stdlib.h>
#include "headers/torre.h"
#include "headers/BaseElemento.h"

typedef struct bala{
    Base base;
    int dano;
    float v;
} Bala;

typedef struct torre{
    Base base;
    Bala bala;
    float custo;
    float custo_melhora;
    float intervalo_disparo;
    float raio;
} Torre;

int addTorre(float custo, float d_jogador){
    if(custo < d_jogador){
        return 1;
    }    
    return 0;
}

int melhorarTorre(Torre *t, float d_jogador){
    if(t->custo_melhora < d_jogador){
        t->raio += 2;
        return 1;
    }
}

void atirar(Torre *t, void *alvo){
    
}