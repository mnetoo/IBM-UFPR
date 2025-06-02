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
void update_enemy(Enemy *e) 
{
    if (!e->ativo) return;

    // Atualiza a posição
    //e->x += e->vel_x;

    // Atualiza animação
    const int FRAME_DELAY = 5; // quanto menor, mais rápido anima
    e->timer_animacao++;
    if (e->timer_animacao >= FRAME_DELAY)
    {
        e->timer_animacao = 0;
        e->frame_atual = (e->frame_atual + 1) % 6;
    }

    // Desativa se sair da tela
    if (e->x < -32)
        e->ativo = false;
}


//==============================================================================


//  Carrega a sprite do inimigo
void draw_enemy(Enemy *e, float camera_x) 
{
    if (!e->ativo) return;

    float escala = 5;
    int flip = ALLEGRO_FLIP_HORIZONTAL;
    float screen_x = e->x - camera_x;  // desenha no lugar relativo à câmera

    al_draw_scaled_bitmap(
        e->sprite[e->frame_atual],
        0, 0,
        al_get_bitmap_width(e->sprite[e->frame_atual]),
        al_get_bitmap_height(e->sprite[e->frame_atual]),
        screen_x,
        e->y,
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