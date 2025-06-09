#include "includes.h"


//==========================================================================================


//  Função que inicializa bullet
void init_projectile(Projectile *p, float x, float y, float vel_x, float vel_y) 
{
    p->x = x;
    p->y = y;
    p->vel_x = vel_x;
    p->vel_y = vel_y;
    p->ativo = true;
    p->sprite = al_load_bitmap("./assets/player/sprite/bullet.png");
}


//==========================================================================================


//  Função que movimentação do projétil
void update_projectile(Projectile *proj) 
{
    if (!proj->ativo) return;

    proj->x += proj->vel_x;
    proj->y += proj->vel_y;

    // desativa se sair da tela
    if (proj->x < 0 || proj->x > TELA_LARGURA || proj->y < 0 || proj->y > TELA_ALTURA)
        proj->ativo = false;
}


//==========================================================================================


//  Função que carrega a sprite bullet
void draw_projectile(Projectile *p) 
{
    if (!p->ativo || !p->sprite)
        return;

    float cx = al_get_bitmap_width(p->sprite) / 2.0;
    float cy = al_get_bitmap_height(p->sprite) / 2.0;

    float dx = p->x + cx;
    float dy = p->y + cy;

    float angle = 0.0;
    float scale_x = 1.0;
    float scale_y = 1.0;

    // Rotaciona para cima
    if (p->vel_y < 0)
        angle = -ALLEGRO_PI / 2;

    // Flip horizontal se for para esquerda
    if (p->vel_x < 0)
        scale_x = -1.0;

    // Desenha com rotação e flip se necessário
    al_draw_tinted_scaled_rotated_bitmap(
        p->sprite,
        al_map_rgb(255, 255, 255), // cor sem alteração
        cx, cy,
        dx, dy,
        scale_x, scale_y,
        angle,
        0
    );
}


//==========================================================================================


//  Função que destrói bullet
void destroy_projectile(Projectile *p) 
{
    if (p->sprite) 
        al_destroy_bitmap(p->sprite);
}


//==========================================================================================