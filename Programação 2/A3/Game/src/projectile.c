#include "includes.h"


//==========================================================================================


//  Função que inicializa bullet
void init_projectile(Projectile *p, float x, float y, float vel_x) 
{
    p->x = x;
    p->y = y;
    p->vel_x = vel_x;
    p->ativo = true;
    p->sprite = al_load_bitmap("./assets/player/sprite/bullet.png");
}


//==========================================================================================


//  Função que movimentação do projétil
void update_projectile(Projectile *p)
{
    if (!p->ativo) return;

    p->x += p->vel_x;

    if (p->x < 0 || p->x > 1200)
        p->ativo = false;
}


//==========================================================================================


//  Função que carrega a sprite bullet
void draw_projectile(Projectile *p) 
{
    if (p->ativo && p->sprite)
        al_draw_bitmap(p->sprite, p->x, p->y, 0);
}


//==========================================================================================


//  Função que destrói bullet
void destroy_projectile(Projectile *p) 
{
    if (p->sprite) 
        al_destroy_bitmap(p->sprite);
}


//==========================================================================================