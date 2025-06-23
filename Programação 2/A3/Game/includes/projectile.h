#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "includes.h"


// Estrutura bullet
typedef struct Projectile
{
    float x, y;
    float vel_x;
    float vel_y;
    bool ativo;
    ALLEGRO_BITMAP *sprite;

    float altura;
    float largura;

} Projectile;


/**
 * Inicializa uma estrutura de projétil com parâmetros básicos
 * 
 * @param p Ponteiro para a estrutura Projectile a ser inicializada
 * @param x Posição X inicial do projétil
 * @param y Posição Y inicial do projétil
 * @param vel_x Velocidade horizontal do projétil (pixels por frame)
 * @param vel_y Velocidade vertical do projétil (pixels por frame)
 */
void init_projectile(Projectile *p, float x, float y, float vel_x, float vel_y);

//============================================================================

/**
 * Atualiza a posição do projétil e verifica se saiu da tela
 * 
 * @param proj Ponteiro para a estrutura Projectile a ser atualizada
 */
void update_projectile(Projectile *p);

//============================================================================

/**
 * Desenha o projétil na tela com rotação e flip adequados à direção
 * 
 * @param p Ponteiro para a estrutura Projectile a ser desenhada
 */
void draw_projectile(Projectile *p);

//============================================================================

/**
 * Libera os recursos alocados para o projétil
 * 
 * @param p Ponteiro para a estrutura Projectile a ser destruída
 */
void destroy_projectile(Projectile *p);

//============================================================================


#endif