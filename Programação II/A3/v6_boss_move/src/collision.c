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
 */
bool colisao_retangulos(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
{
    // Verifica se há sobreposição nos eixos X e Y simultaneamente
    return (x1 < x2 + w2 &&   // Extremo direito do ret1 à esquerda do extremo direito do ret2
            x1 + w1 > x2 &&   // Extremo direito do ret1 à direita do extremo esquerdo do ret2
            y1 < y2 + h2 &&   // Extremo inferior do ret1 acima do extremo inferior do ret2
            y1 + h1 > y2);   // Extremo inferior do ret1 abaixo do extremo superior do ret2
}


//============================================================================


/**
 * Cria uma hitbox para um projétil (do jogador ou inimigo)
 * 
 * @param p Ponteiro para o projétil (pode ser EnemyProjectile ou Projectile)
 * @param is_enemy_projectile Flag indicando se é um projétil de inimigo (1) ou do jogador (0)
 */
Hitbox get_projectile_hitbox(void *p, int is_enemy_projectile) 
{
    Hitbox hb;
    if (is_enemy_projectile) 
    {
        EnemyProjectile *ep = (EnemyProjectile *)p;
        hb.x = ep->x - 10;  // Ajuste para centralizar a hitbox
        hb.y = ep->y - 10;
    } 
    else 
    {
        Projectile *pp = (Projectile *)p;
        hb.x = pp->x - 8;   // Ajuste para centralizar a hitbox
        hb.y = pp->y - 8;
    }
    hb.w = 16;  // Largura padrão para hitbox de projétil
    hb.h = 16;  // Altura padrão para hitbox de projétil
    return hb;
}


//============================================================================


/**
 * Cria uma hitbox para o jogador (versão normal)
 * 
 * @param p Ponteiro para a estrutura do jogador
 */
Hitbox get_player_hitbox(Player *p) 
{
    Hitbox hb;
    hb.x = p->x + 10;  // Ajuste horizontal para área de colisão
    hb.y = p->y + 90;  // Ajuste vertical para área de colisão (parte inferior)
    
    // Obtém o primeiro frame do sprite (assumindo que é um ALLEGRO_BITMAP*)
    ALLEGRO_BITMAP* sprite = p->sprite_shoot[0];
    
    // Verifica se o sprite existe antes de obter dimensões
    if (sprite) {
        hb.w = al_get_bitmap_width(sprite) - 40;  // Reduz a largura para hitbox menor que o sprite
        hb.h = al_get_bitmap_height(sprite) - 40; // Reduz a altura para hitbox menor que o sprite
    } else {
        // Valores padrão caso o sprite não esteja carregado
        hb.w = 20;
        hb.h = 20;
    }
    
    return hb;
}


//============================================================================


/**
 * Cria uma hitbox para o jogador (versão de boss)
 * 
 * @param p Ponteiro para a estrutura do jogador
 */
Hitbox get_playerBoss_hitbox(Player *p) 
{
    Hitbox hb;
    hb.x = p->x + 10;  // Ajuste horizontal para área de colisão
    hb.y = p->y + 40;  // Ajuste vertical diferente para batalha contra boss
    
    // Obtém o primeiro frame do sprite (assumindo que é um ALLEGRO_BITMAP*)
    ALLEGRO_BITMAP* sprite = p->sprite_shoot[0];
    
    // Verifica se o sprite existe antes de obter dimensões
    if (sprite) {
        hb.w = al_get_bitmap_width(sprite) - 40;  // Reduz a largura para hitbox menor que o sprite
        hb.h = al_get_bitmap_height(sprite) - 40; // Reduz a altura para hitbox menor que o sprite
    } else {
        // Valores padrão caso o sprite não esteja carregado
        hb.w = 20;
        hb.h = 20;
    }
    
    return hb;
}


//============================================================================


/**
 * Cria uma hitbox para um inimigo
 * 
 * @param e Ponteiro para a estrutura do inimigo
 */
Hitbox get_enemy_hitbox(Enemy *e) 
{
    Hitbox hb;
    hb.x = e->enemy_pos_mundo_x + 10;  // Posição X com ajuste
    hb.y = e->y + 10;                  // Posição Y com ajuste
    hb.w = al_get_bitmap_width(e->sprite[0]) * 3.5 - 20;  // Largura considerando escala 3.5x
    hb.h = al_get_bitmap_height(e->sprite[0]) * 3.5 - 20; // Altura considerando escala 3.5x
    return hb;
}


//============================================================================


/**
 * Cria uma hitbox para um boss
 * 
 * @param b Ponteiro para a estrutura do boss
 */
Hitbox get_boss_hitbox(Boss *b)
{
    Hitbox hb;
    hb.x = b->pos_mundo_x + 10;  // Posição X com ajuste
    hb.y = b->y;                 // Posição Y sem ajuste vertical
    hb.w = al_get_bitmap_width(b->burn[0]) * 4 - 20;  // Largura considerando escala 4x
    hb.h = al_get_bitmap_height(b->burn[0]) * 4 - 20; // Altura considerando escala 4x
    return hb;
}