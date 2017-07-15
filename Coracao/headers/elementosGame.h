#ifndef ELEMENTOSGAME
#define ELEMENTOSGAME

typedef struct tower Tower;
typedef struct bala Bullet;
typedef struct minion Minions;
typedef struct life Life;
typedef struct jogador Jogador;

void atirar(Torre *t, void *alvo);

int addTorre(float custo, float d_jogador);

//float deletarTorre(Torre *t);

int melhorarTorre(Tower *t, float d_jogador);
#endif