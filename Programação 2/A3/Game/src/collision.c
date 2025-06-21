#include "includes.h"


/**
 * Verifica colisão entre dois retângulos alinhados aos eixos (AABB - Axis-Aligned Bounding Box)
 * 
 * @param x1 Coordenada X do canto superior esquerdo do primeiro retângulo
 * @param y1 Coordenada Y do canto superior esquerdo do primeiro retângulo
 * @param w1 Largura (width) do primeiro retângulo
 * @param h1 Altura (height) do primeiro retângulo
 * @param x2 Coordenada X do canto superior esquerdo do segundo retângulo
 * @param y2 Coordenada Y do canto superior esquerdo do segundo retângulo
 * @param w2 Largura (width) do segundo retângulo
 * @param h2 Altura (height) do segundo retângulo
 * 
 * @return true se os retângulos estão colidindo, false caso contrário
 * 
 * @note Esta função assume que:
 * - O sistema de coordenadas tem Y crescente para baixo (como em muitos sistemas gráficos)
 * - A origem (x,y) de cada retângulo é seu canto superior esquerdo
 * - Os retângulos estão alinhados aos eixos (não rotacionados)
 */
bool colisao_retangulos(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
{
    // Verifica se há sobreposição nos eixos X e Y simultaneamente
    return (x1 < x2 + w2 &&   // Extremo direito do ret1 à esquerda do extremo direito do ret2
    x1 + w1 > x2 &&   // Extremo direito do ret1 à direita do extremo esquerdo do ret2
    y1 < y2 + h2 &&   // Extremo inferior do ret1 acima do extremo inferior do ret2
    y1 + h1 > y2);    // Extremo inferior do ret1 abaixo do extremo superior do ret2
}




// Função para criar uma hitbox a partir de um projétil
Hitbox get_projectile_hitbox(void *p, int is_enemy_projectile) 
{
    Hitbox hb;
    if (is_enemy_projectile) 
    {
        EnemyProjectile *ep = (EnemyProjectile *)p;
        hb.x = ep->x - 10;
        hb.y = ep->y - 10;
    } 
    else 
    {
        Projectile *pp = (Projectile *)p;
        hb.x = pp->x - 8;
        hb.y = pp->y - 8;
    }
    hb.w = 16;
    hb.h = 16;
    return hb;
}



// Função para criar uma hitbox do jogador
Hitbox get_player_hitbox(Player *p) 
{
    Hitbox hb;
    hb.x = p->x + 10;  // Ajuste para a área de colisão do jogador
    hb.y = p->y + 90;
    
    // Get the first sprite frame (assuming it's an ALLEGRO_BITMAP*)
    ALLEGRO_BITMAP* sprite = p->sprite_shoot[0];
    
    // Check if sprite exists before getting dimensions
    if (sprite) {
        hb.w = al_get_bitmap_width(sprite) - 40;  // Typically you'd subtract to make hitbox smaller than sprite
        hb.h = al_get_bitmap_height(sprite) - 40;
    } else {
        // Default values if sprite isn't loaded
        hb.w = 20;
        hb.h = 20;
    }
    
    return hb;
}

// Função para criar uma hitbox do jogador
Hitbox get_playerBoss_hitbox(Player *p) 
{
    Hitbox hb;
    hb.x = p->x + 10;  // Ajuste para a área de colisão do jogador
    hb.y = p->y + 40;
    
    // Get the first sprite frame (assuming it's an ALLEGRO_BITMAP*)
    ALLEGRO_BITMAP* sprite = p->sprite_shoot[0];
    
    // Check if sprite exists before getting dimensions
    if (sprite) {
        hb.w = al_get_bitmap_width(sprite) - 40;  // Typically you'd subtract to make hitbox smaller than sprite
        hb.h = al_get_bitmap_height(sprite) - 40;
    } else {
        // Default values if sprite isn't loaded
        hb.w = 20;
        hb.h = 20;
    }
    
    return hb;
}

// Função para criar uma hitbox do inimigo
Hitbox get_enemy_hitbox(Enemy *e) 
{
    Hitbox hb;
    hb.x = e->enemy_pos_mundo_x + 10;
    hb.y = e->y + 10;
    hb.w = al_get_bitmap_width(e->sprite[0]) * 3.5 - 20;  // Considerando o scale 3.5
    hb.h = al_get_bitmap_height(e->sprite[0]) * 3.5 - 20;
    return hb;
}

Hitbox get_boss_hitbox(Boss *b)
{
    Hitbox hb;
    hb.x = b->pos_mundo_x + 10;
    hb.y = b->y;
    hb.w = al_get_bitmap_width(b->burn[0]) * 4 - 20;
    hb.h = al_get_bitmap_height(b->burn[0]) * 4 - 20;
    return hb;
}