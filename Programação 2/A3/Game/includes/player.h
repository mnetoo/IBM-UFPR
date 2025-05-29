#ifndef PLAYER_H
#define PLAYER_H


#include <allegro5/allegro.h>



typedef enum
{
    STAND,
    WALK,
    JUMP,
    CROUCH,
    SHOOT
} PlayerState;


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



void init_player(Player *p);

void update_player(Player *p);

void draw_player(Player *p);

void destroy_player(Player *p);




#endif