#ifndef ELEMENTOSGAME
#define ELEMENTOSGAME

typedef struct tower Tower;
//typedef struct bala Bullet;
typedef struct minion Minion;
typedef struct life Life;
typedef struct jogador Jogador;
typedef struct game Game;

void atirar(Torre t, Minion *alvo);

int addTorre(float custo, float d_jogador);

//float deletarTorre(Torre *t);

int melhorarTorre(Tower *t, float d_jogador);
#endif