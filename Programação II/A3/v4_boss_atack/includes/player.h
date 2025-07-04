#ifndef PLAYER_H
#define PLAYER_H
#include "includes.h"


//  Estado do Player
typedef enum
{
    STAND_AND_STOP,
    STAND_AND_SHOT,
    WALK,
    JUMP,
    JUMP_AND_SHOT,
    CROUCH,
    CROUCH_AND_SHOT
} PlayerState;


//  Estrutura do Player
typedef struct Player
{
    float x, y;
    float vel_x, vel_y;
    int width, height;
    int vida;
    int olhando_para_direita; // 1 para direita, 0 para esquerda
    float player_pos_mundo_x;

    PlayerState estado;

    ALLEGRO_BITMAP *sprite_stand_and_stop;
    ALLEGRO_BITMAP *sprite_shoot[2];

    // Array para sprites de andar
    ALLEGRO_BITMAP *sprite_run[10]; 

    ALLEGRO_BITMAP *sprite_jump; 
    ALLEGRO_BITMAP *sprite_jump_and_shot;

    ALLEGRO_BITMAP *sprite_crouch;
    ALLEGRO_BITMAP *sprite_crouch_and_shot[2];

    int frame_andar;    // índice atual da animação de andar
    int timer_andar;    // contador para controle da troca de frame

    int frame_shoot;    // índice atual da animação de tiro
    int timer_shoot;    // contador para controle da troca de tiro

    Projectile projeteis[MAX_PROJECTILES];

    // NOVAS VARIÁVEIS PARA O EFEITO DE QUEIMADURA
    int burn_timer;       // Timer para a duração total do efeito. Se > 0, o jogador está queimando.
    int burn_tick_timer;  // Timer para controlar a frequência do dano (o "tick").

} Player;


// Declara que Enemy é uma struct 
typedef struct Enemy Enemy;

// Declara que Boss é uma struct
typedef struct Boss Boss;


/**
 * @brief - Inicializa o jogador com valores padrão e carrega seus sprites
 * 
 * @param p - Ponteiro para a estrutura Player que será inicializada
 */
void init_player(Player *p);

//========================================================

/**
 * @brief - Atualiza o estado do jogador a cada frame
 * 
 * @param p - Ponteiro para a estrutura Player a ser atualizada
 * @param enemies - Vetor de inimigos para verificação de colisão
 * @param boss - Ponteiro para o boss para verificação de colisão
 */
void update_player(Player *p, Enemy *enemies, Boss *boss);

//========================================================

/**
 * @brief - Desenha o jogador na tela de acordo com seu estado atual
 * 
 * @param p - Ponteiro para a estrutura Player a ser desenhada
 */
void draw_player(Player *p);

//========================================================

/**
 * @brief - Libera a memória alocada para os sprites e projéteis do jogador
 * 
 * @param p - Ponteiro para a estrutura Player a ser destruída
 */
void destroy_player(Player *p);

//========================================================


#endif