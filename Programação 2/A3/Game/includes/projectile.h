#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <allegro5/allegro.h>





typedef struct 
{
    float x, y;
    float vel_x;
    bool ativo;
    ALLEGRO_BITMAP *sprite;
} Projectile;





void init_projectile(Projectile *p, float x, float y, float vel_x);

void update_projectile(Projectile *p);

void draw_projectile(Projectile *p);

void destroy_projectile(Projectile *p);




#endif