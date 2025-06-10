#include "player.h"
#include "includes.h"


//==============================================================================


// Função que inicializa um inimigo
void init_enemy(Enemy *e, float pos_x) 
{
    e->x = pos_x;
    e->y = 420;
    e->vel_x = -2;
    e->vida = 20;
    e->ativo = true;

    e->frame_atual = 0;
    e->timer_animacao = 0;
    e->tempo_tiro = 0;

    for (int i = 0; i < 6; i++) 
    {
        char filename[100];
        sprintf(filename, "./assets/enemies/enemy-ghost/Sprites/Particles/frame%d.png", i + 1);
        e->sprite[i] = al_load_bitmap(filename);
        if (!e->sprite[i]) 
            printf("Erro ao carregar sprite %d do inimigo\n", i);
    }

    for (int i = 0; i < MAX_ENEMY_PROJECTILES; i++) 
        e->projeteis[i].ativo = false;
}


//==============================================================================


//  Função para o tiro/projétil
void enemy_shoot_projectile(Enemy *e) 
{
    for (int i = 0; i < MAX_ENEMY_PROJECTILES; i++) 
    {
        if (!e->projeteis[i].ativo) 
        {
            e->projeteis[i].x = e->enemy_pos_mundo_x;
            e->projeteis[i].y = 550;
            e->projeteis[i].vel_x = -50; // Tiro para esquerda
            e->projeteis[i].vel_y = 0;
            e->projeteis[i].ativo = true;
            break;
        }
    }
}


//  Função de movimentação de inimigo
void update_enemy(Enemy *e, float player_mundo) 
{
    if (!e->ativo) return;

    e->enemy_pos_mundo_x = e->x - player_mundo;

    // Atualiza animação
    e->timer_animacao++;
    if (e->timer_animacao >= 10) 
    {
        e->timer_animacao = 0;
        e->frame_atual = (e->frame_atual + 1) % 6;
    }

    // Timer simples de tiro
    e->tempo_tiro++;
    if (e->tempo_tiro >= 120) // A cada 2 segundos (se 60fps)
    {
        enemy_shoot_projectile(e);
        e->tempo_tiro = 0;
    }

    // Atualiza projéteis do inimigo
    for (int i = 0; i < MAX_ENEMY_PROJECTILES; i++) 
    {
        if (e->projeteis[i].ativo) 
        {
            e->projeteis[i].x += e->projeteis[i].vel_x;

            // Desativa se sair da tela
            if (e->projeteis[i].x < 0) 
                e->projeteis[i].ativo = false;
        }
    }
}


//==============================================================================


//  Carrega a sprite do inimigo
void draw_enemy(Enemy *e, Background *bg) 
{
    if (!e->ativo) return;

    float pos_x = e->enemy_pos_mundo_x;
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

    for (int i = 0; i < MAX_ENEMY_PROJECTILES; i++) 
    {
        if (e->projeteis[i].ativo) 
        {
            al_draw_filled_circle(
                e->projeteis[i].x,
                e->projeteis[i].y,
                8,
                al_map_rgb(255, 0, 110)
            );
        }
    }
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