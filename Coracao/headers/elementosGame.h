#ifndef ELEMENTOSGAME
#define ELEMENTOSGAME

typedef struct tower Tower;
//typedef struct bala Bullet;
typedef struct minion Minion;
typedef struct life Life;
typedef struct orda Orda;

void atirar(Torre t, Minion *alvo);

void addTorre(float custo, Jogador *j);

void aumentaOrda(Orda *orda);
void mandaOrda(Orda orda);
//float deletarTorre(Torre *t);

void upgrade(Tower *t, Jogador *j);
#endif