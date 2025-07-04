#ifndef BOSS_H
#define BOSS_H
#include "includes.h"


typedef struct 
{
    float x, y;
    float vel_x, vel_y;
    bool ativo;

    int frame_atual;
    int timer_animacao;
} BossProjectile;


//  Estrutura do Boss
typedef struct Boss
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

    // NOVAS VARIÁVEIS PARA O ATAQUE ESPECIAL
    int special_attack_cooldown_timer; // Timer que conta o tempo ENTRE os ataques especiais
    int special_attack_phase_timer;    // Timer que gerencia as fases do ataque (aviso e duração)

    float patrol_limit_left;
    float patrol_limit_right;
    bool olhando_para_direita;

    bool morto;
} Boss;


//  Estado do Boss
typedef enum 
{
    BURN,             // Estado normal, vida alta
    IDLE,             // Estado normal, vida baixa
    TELEGRAPH,        // Estado de "aviso" antes do ataque especial
    SPECIAL_ATTACK    // Estado onde o ataque especial está acontecendo
} BossState;


/**
 * @brief - Função que inicializa o Boss
 * 
 * @param b - Ponteiro para a estrutura Boss
 * @param pos_x - posição do boss
 */
void init_boss(Boss *b, float pos_x);

//============================================================

/**
 * @brief - Função de animação do Boss
 * 
 * @param b - Ponteiro para a estrutura Boss
 * @param player_mundo - deslocamento do player no mundo
 * @param p - Ponteiro para a estrutura Player
 */
void update_boss(Boss *b, float player_mundo, Player *p);

//============================================================

/**
 * @brief - Desenha o Boss e projéteis
 * 
 * @param b - Ponteiro para a estrutura Boss
 */
void draw_boss(Boss *b);

//============================================================

/**
 * @brief - Função que destróis Boss
 * 
 * @param b - Ponteiro para a estrutura Boss
 */
void destroy_boss(Boss *b);

//============================================================


#endif