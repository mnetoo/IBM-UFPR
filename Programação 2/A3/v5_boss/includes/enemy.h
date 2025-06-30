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


/**
 * @brief - Função que inicializa um inimigo
 * 
 * @param e - Ponteiro para a estrutura Enemy
 * @param pox_x - valor para a posição do inimigo
 */
void init_enemy(Enemy *e, float pos_x);

//============================================================

/**
 * @brief - Função de movimentação de inimigo
 * 
 * @param e - Ponteiro para a estrutura Enemy
 * @param player_mundo - deslocamento do player
 * @param player - Ponteiro para a estrutura Player
 */
void update_enemy(Enemy *e, float player_mundo, Player *player);

//============================================================

/**
 * @brief - Carrega a sprite do inimigo
 * 
 * @param e - Ponteiro para a estrutura Enemy
*/
void draw_enemy(Enemy *e);

//============================================================

/**
 * @brief - Função que destrói inimigo
 * 
 * @param e - Ponteiro para a estrutura Enemy
*/
void destroy_enemy(Enemy *e);

//============================================================

/**
 * @brief Verifica se a posição para um novo inimigo é válida (não muito próxima de outros)
 * 
 * @param nova_pos Posição x que está sendo testada para o novo inimigo
 * @param posicoes Vetor com as posições x dos inimigos já colocados
 * @param count Quantidade de inimigos já posicionados
 * @return true Se a posição é válida (distante o suficiente de outros inimigos)
 * @return false Se a posição é inválida (muito próxima de outro inimigo)
 */
bool posicao_valida(int nova_pos, int posicoes[], int count);

//============================================================

/**
 * @brief Inicializa todos os inimigos do jogo com posições aleatórias válidas
 * 
 * @param inimigos Array de inimigos a ser inicializado
 */
int inicializa_inimigos(Enemy inimigos[]);

#endif