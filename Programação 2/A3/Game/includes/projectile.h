#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "includes.h"


// Estrutura bullet
typedef struct 
{
    float x, y;
    float vel_x;
    float vel_y;
    bool ativo;
    ALLEGRO_BITMAP *sprite;
} Projectile;


//  Função que inicializa bullet
void init_projectile(Projectile *p, float x, float y, float vel_x, float vel_y);

//============================================================================

//  Função que movimentação do projétil
void update_projectile(Projectile *p);

//============================================================================

//  Função que carrega a sprite bullet
void draw_projectile(Projectile *p);

//============================================================================

//  Função que destrói bullet
void destroy_projectile(Projectile *p);

//============================================================================


#endif