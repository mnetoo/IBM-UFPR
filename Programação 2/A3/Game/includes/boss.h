#ifndef BOSS_H
#define BOSS_H
#include "includes.h"


typedef struct {
    float x, y;
    float vel_x, vel_y;
    bool ativo;

    int frame_atual;
    int timer_animacao;
} BossProjectile;


//  Estrutura do Boss
typedef struct 
{
    float x, y;         // Posição na tela
    float vel_x;
    float vel_y;
    float pos_mundo_x;
    int vida;

    ALLEGRO_BITMAP *idle[4];
    ALLEGRO_BITMAP *burn[8];
    ALLEGRO_BITMAP *ataque[3];

    BossProjectile projeteis[MAX_BOSS_PROJECTILES];
    int tempo_tiro; // Timer do tiro
    
    int frame_atual;      // Índice do sprite atual
    int timer_animacao;   // Temporizador para controlar a troca de sprite
} Boss;


//  Estado do Boss
typedef enum
{
    IDLE,
    BURN,
} BossState;


//  Função que inicializa um inimigo
void init_boss(Boss *b, float pos_x);

//============================================================

//  Função de movimentação de inimigo
void update_boss(Boss *b, float player_mundo);

//============================================================

//  Carrega a sprite do inimigo
void draw_boss(Boss *b);

//============================================================

//  Função que destrói inimigo
void destroy_boss(Boss *b);

//============================================================


#endif