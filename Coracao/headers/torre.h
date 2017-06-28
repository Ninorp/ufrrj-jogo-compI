#ifndef TORRE
#define TORRE

typedef struct torre Torre;
typedef struct bala Bala;

void atirar(Torre *t, void *alvo);

int addTorre(float custo, float d_jogador);

//float deletarTorre(Torre *t);

int melhorarTorre(Torre *t, float d_jogador);
#endif