#ifndef PLAYER_H
#define PLAYER_H
#include "includes.h"


//  Estado do Player
typedef enum
{
    STAND_AND_STOP,
    STAND_AND_SHOT,
    WALK1,
    WALK2,
    WALK3,
    WALK4,
    JUMP1,
    JUMP2,
    CROUCH1,
    CROUCH2,
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

    PlayerState estado;

    ALLEGRO_BITMAP *sprite_stand_and_stop;
    ALLEGRO_BITMAP *sprite_stand_and_shot;

    //  Direita
    ALLEGRO_BITMAP *sprite_walk1;
    ALLEGRO_BITMAP *sprite_walk2;
    //  Esquerda
    ALLEGRO_BITMAP *sprite_walk3;
    ALLEGRO_BITMAP *sprite_walk4;

    //  Direita
    ALLEGRO_BITMAP *sprite_jump1;
    //  Esquerda
    ALLEGRO_BITMAP *sprite_jump2;

    //  Direita
    ALLEGRO_BITMAP *sprite_crouch1;
    //Esquerda
    ALLEGRO_BITMAP *sprite_crouch2;

    ALLEGRO_BITMAP *sprite_crouch_and_shot;

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