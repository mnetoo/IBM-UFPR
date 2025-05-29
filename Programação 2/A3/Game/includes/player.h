#ifndef PLAYER_H
#define PLAYER_H
#include "includes.h"


//  Estado do Player
typedef enum
{
    STAND,
    WALK,
    JUMP,
    CROUCH,
    SHOOT
} PlayerState;


//  Estrutura do Player
typedef struct 
{
    float x, y;
    float vel_x, vel_y;
    int width, height;
    int vida;

    PlayerState estado;

    ALLEGRO_BITMAP *sprite_stand;
    ALLEGRO_BITMAP *sprite_walk;
    ALLEGRO_BITMAP *sprite_jump;
    ALLEGRO_BITMAP *sprite_crouch;
    ALLEGRO_BITMAP *sprite_shoot;
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