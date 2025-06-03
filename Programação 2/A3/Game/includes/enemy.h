#ifndef ENEMY_H
#define ENEMY_H
#include "includes.h"


//  Estrutura de inimigo
typedef struct 
{
    float x, y;
    float vel_x;
    int vida;
    bool ativo;

    ALLEGRO_BITMAP *sprite[6];
    int frame_atual;      // Índice do sprite atual
    int timer_animacao;   // Temporizador para controlar a troca de sprite
} Enemy;


//  Função que inicializa um inimigo
void init_enemy(Enemy *e, float y);

//============================================================

//  Função de movimentação de inimigo
void update_enemy(Enemy *e);

//============================================================

//  Carrega a sprite do inimigo
void draw_enemy(Enemy *e, Background *bg);

//============================================================

//  Função que destrói inimigo
void destroy_enemy(Enemy *e);

//============================================================

#endif