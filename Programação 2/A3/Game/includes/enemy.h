#ifndef ENEMY_H
#define ENEMY_H
#include "includes.h"


typedef struct 
{
    float x, y;
    float vel_x, vel_y;
    bool ativo;
} EnemyProjectile;


//  Estrutura de inimigo
typedef struct Enemy
{
    float x, y;
    float vel_x;
    int vida;
    bool ativo;

    float enemy_pos_mundo_x;

    int frame_atual;
    int timer_animacao;

    ALLEGRO_BITMAP *sprite[6];

    EnemyProjectile projeteis[MAX_ENEMY_PROJECTILES];
    int tempo_tiro;
} Enemy;


//  Função que inicializa um inimigo
void init_enemy(Enemy *e, float pos_x);

//============================================================

//  Função de movimentação de inimigo
void update_enemy(Enemy *e, float player_mundo, Player *player);

//============================================================

//  Carrega a sprite do inimigo
void draw_enemy(Enemy *e, Background *bg);

//============================================================

//  Função que destrói inimigo
void destroy_enemy(Enemy *e);

//============================================================


bool posicao_valida(int nova_pos, int posicoes[], int count);

void inicializa_inimigos(Enemy inimigos[]);

#endif