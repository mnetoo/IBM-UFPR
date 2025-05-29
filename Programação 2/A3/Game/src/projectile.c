#include <allegro5/allegro_image.h>
#include "projectile.h"


//==========================================================================================


//
void init_projectile(Projectile *p, float x, float y, float vel_x) 
{
    p->x = x;
    p->y = y;
    p->vel_x = vel_x;
    p->ativo = true;
    p->sprite = al_load_bitmap("./assets/bullet.png");
}


//==========================================================================================


//
void update_projectile(Projectile *p)
{
    if (!p->ativo) return;

    p->x += p->vel_x;

    if (p->x < 0 || p->x > 840)
        p->ativo = false;

}


//==========================================================================================


//
void draw_projectile(Projectile *p) 
{
    if (p->ativo && p->sprite)
        al_draw_bitmap(p->sprite, p->x, p->y, 0);
}


//==========================================================================================


//
void destroy_projectile(Projectile *p) 
{
    if (p->sprite) 
        al_destroy_bitmap(p->sprite);
}


//==========================================================================================