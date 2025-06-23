#include "includes.h"

//==========================================================================================

/**
 * Inicializa uma estrutura de projétil com parâmetros básicos
 * 
 * @param p Ponteiro para a estrutura Projectile a ser inicializada
 * @param x Posição X inicial do projétil
 * @param y Posição Y inicial do projétil
 * @param vel_x Velocidade horizontal do projétil (pixels por frame)
 * @param vel_y Velocidade vertical do projétil (pixels por frame)
 */
void init_projectile(Projectile *p, float x, float y, float vel_x, float vel_y) 
{
    p->x = x;                  // Posição X inicial
    p->y = y;                  // Posição Y inicial
    p->vel_x = vel_x;          // Velocidade horizontal
    p->vel_y = vel_y;          // Velocidade vertical
    p->ativo = true;           // Projétil ativo por padrão
    p->sprite = al_load_bitmap("./assets/player/sprite/bullet.png");  // Carrega sprite
    p->altura = 2;             // Altura para cálculos de colisão
    p->largura = 10;           // Largura para cálculos de colisão
}

//==========================================================================================

/**
 * Atualiza a posição do projétil e verifica se saiu da tela
 * 
 * @param proj Ponteiro para a estrutura Projectile a ser atualizada
 */
void update_projectile(Projectile *proj) 
{
    if (!proj->ativo) return;  // Ignora projéteis inativos

    // Atualiza posição baseada na velocidade
    proj->x += proj->vel_x;
    proj->y += proj->vel_y;

    // Verifica se saiu dos limites da tela
    if (proj->x < 0 || proj->x > TELA_LARGURA || proj->y < 0 || proj->y > TELA_ALTURA)
        proj->ativo = false;   // Desativa se estiver fora da tela
}

//==========================================================================================

/**
 * Desenha o projétil na tela com rotação e flip adequados à direção
 * 
 * @param p Ponteiro para a estrutura Projectile a ser desenhada
 */
void draw_projectile(Projectile *p) 
{
    if (!p->ativo || !p->sprite)  // Verifica se pode desenhar
        return;

    // Calcula o centro do sprite para rotação
    float cx = al_get_bitmap_width(p->sprite) / 2.0;
    float cy = al_get_bitmap_height(p->sprite) / 2.0;

    // Posição de desenho (ajustada para o centro)
    float dx = p->x + cx;
    float dy = p->y + cy;

    // Valores padrão para transformação
    float angle = 0.0;      // Sem rotação
    float scale_x = 1.0;    // Sem flip horizontal
    float scale_y = 1.0;    // Sem flip vertical

    // Rotaciona 90 graus para cima se estiver subindo
    if (p->vel_y < 0)
        angle = -ALLEGRO_PI / 2;

    // Flip horizontal se estiver indo para esquerda
    if (p->vel_x < 0)
        scale_x = -1.0;

    // Desenha com as transformações aplicadas
    al_draw_tinted_scaled_rotated_bitmap(
        p->sprite,
        al_map_rgb(255, 255, 255), // Cor original (branco)
        cx, cy,                     // Ponto de origem da rotação
        dx, dy,                     // Posição na tela
        scale_x, scale_y,           // Escala (pode incluir flip)
        angle,                      // Ângulo de rotação
        0                           // Flags adicionais
    );
}

//==========================================================================================

/**
 * Libera os recursos alocados para o projétil
 * 
 * @param p Ponteiro para a estrutura Projectile a ser destruída
 */
void destroy_projectile(Projectile *p) 
{
    if (p->sprite) 
        al_destroy_bitmap(p->sprite);  // Libera o recurso de sprite
}

//==========================================================================================