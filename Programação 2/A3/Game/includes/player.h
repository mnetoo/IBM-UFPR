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
typedef struct 
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

    Projectile projeteis[MAX_PROJECTILES]; // <- Lista de projéteis
} Player;


//  Função para iniciar o player
void init_player(Player *p);

//========================================================

//  Função para movimentar o player
void update_player(Player *p);

//========================================================

//  Função para trocar as sprites do player
void draw_player(Player *p);

//========================================================

//  Função para destruir o player
void destroy_player(Player *p);

//========================================================


#endif