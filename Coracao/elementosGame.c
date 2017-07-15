
#include <stdio.h>
#include <stdlib.h>
#include "headers/torre.h"
#include "headers/BaseElemento.h"

//torres


typedef struct bullet{
    Base base;
    int damage;
    float v;//o que � v?
} Bala;

typedef struct tower{
    Base base;
    Bullet bullet;
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

void atirar(Torre *t, void *alvo){
    
}

//fim torre

//minions

