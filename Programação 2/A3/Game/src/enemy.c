#include "includes.h"


//==============================================================================


//  Função que inicializa um inimigo
void init_enemy(Enemy *e, float x, float y) 
{
    e->x = x;
    e->y = y;
    e->vel_x = -1.5; // Anda da direita para a esquerda
    e->vida = 20;
    e->ativo = true;

    e->sprite = al_load_bitmap("./assets/enemies/enemy.png");

    if(!e->sprite)
        printf("Erro ao carregar sprite do inimigo\n");
}


//==============================================================================


//  Função de movimentação de inimigo
void update_enemy(Enemy *e) 
{
    if (!e->ativo) return;

    //e->x += e->vel_x;

    if (e->x < -32)
        e->ativo = false; // saiu da tela

}


//==============================================================================


//  Carrega a sprite do inimigo
void draw_enemy(Enemy *e) 
{
    if (!e->ativo || !e->sprite) 
        return;

    al_draw_bitmap(e->sprite, e->x, e->y, 0);
}


//==============================================================================


//  Função que destrói inimigo
void destroy_enemy(Enemy *e) 
{
    if (e->sprite) al_destroy_bitmap(e->sprite);
}


//===============================================================================