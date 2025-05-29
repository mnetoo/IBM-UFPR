#ifndef ENEMY_H
#define ENEMY_H
#include <allegro5/allegro.h>









typedef struct 
{
    float x, y;
    float vel_x;
    int vida;
    bool ativo;

    ALLEGRO_BITMAP *sprite;
} Enemy;






void init_enemy(Enemy *e, float x, float y);

void update_enemy(Enemy *e);

void draw_enemy(Enemy *e);

void destroy_enemy(Enemy *e);



#endif