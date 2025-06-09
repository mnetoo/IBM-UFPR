#include "player.h"
#include "includes.h"


//==============================================================================


// Função que inicializa um inimigo
void init_enemy(Enemy *e) 
{
    e->x = 900;
    e->y = 470;
    e->vel_x = -2;
    e->vida = 20;
    e->ativo = true;

    e->frame_atual = 0;
    e->timer_animacao = 0;

    for (int i = 0; i < 6; i++) 
    {
        char filename[100];
        sprintf(filename, "./assets/enemies/enemy-ghost/Sprites/Particles/frame%d.png", i + 1);
        e->sprite[i] = al_load_bitmap(filename);

        if (!e->sprite[i]) 
            printf("Erro ao carregar sprite %d do inimigo\n", i);
    }
}


//==============================================================================


//  Função de movimentação de inimigo
void update_enemy(Enemy *e, float player_mundo) 
{
    if (!e->ativo) return;

    // Move o inimigo no mundo
    e->enemy_pos_mundo_x += e->vel_x;

    // Converte a posição no mundo para posição na tela
    e->x = e->enemy_pos_mundo_x - player_mundo;

    // Animação: troca de sprite a cada 10 frames
    e->timer_animacao++;
    if (e->timer_animacao >= 10) 
    {
        e->timer_animacao = 0;
        e->frame_atual = (e->frame_atual + 1) % 6;
    }
}


//==============================================================================


//  Carrega a sprite do inimigo
void draw_enemy(Enemy *e, Background *bg) 
{
    if (!e->ativo) return;

    float pos_x = e->x;
    float pos_y = e->y;

    float escala = 3.5;
    int flip = ALLEGRO_FLIP_HORIZONTAL;

    al_draw_scaled_bitmap(
        e->sprite[e->frame_atual],
        0, 0,
        al_get_bitmap_width(e->sprite[e->frame_atual]),
        al_get_bitmap_height(e->sprite[e->frame_atual]),
        pos_x,
        pos_y,
        al_get_bitmap_width(e->sprite[e->frame_atual]) * escala,
        al_get_bitmap_height(e->sprite[e->frame_atual]) * escala,
        flip
    );
}


//==============================================================================


//  Função que destrói inimigo
void destroy_enemy(Enemy *e) 
{
    for (int i = 0; i < 6; i++)
    {
        if (e->sprite[i])
        {
            al_destroy_bitmap(e->sprite[i]);
            e->sprite[i] = NULL;
        }
    }
}


//===============================================================================