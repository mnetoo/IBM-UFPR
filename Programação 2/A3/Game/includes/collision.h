#ifndef COLLISION_H
#define COLLISION_H



// Estrutura para representar um retângulo de colisão
typedef struct {
    float x, y;
    float w, h;
} Hitbox;

// Declara que Enemy é uma struct (sem precisar saber os campos ainda)
typedef struct Enemy Enemy;

// Declara que Enemy é uma struct (sem precisar saber os campos ainda)
typedef struct Player Player;

// Declara que Enemy é uma struct (sem precisar saber os campos ainda)
typedef struct Projectile Projectile;

// Declara que Enemy é uma struct (sem precisar saber os campos ainda)
typedef struct Boss Boss;


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
bool colisao_retangulos(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);

//========================================================


/**
 * Cria uma hitbox para um projétil (do jogador ou inimigo)
 * 
 * @param p Ponteiro para o projétil (pode ser EnemyProjectile ou Projectile)
 * @param is_enemy_projectile Flag indicando se é um projétil de inimigo (1) ou do jogador (0)
 */
Hitbox get_projectile_hitbox(void *p, int is_enemy_projectile);

//========================================================

/**
 * Cria uma hitbox para o jogador (versão normal)
 * 
 * @param p Ponteiro para a estrutura do jogador
 */
Hitbox get_player_hitbox(Player *p);

//========================================================

/**
 * Cria uma hitbox para o jogador (versão de boss)
 * 
 * @param p Ponteiro para a estrutura do jogador
 */
Hitbox get_playerBoss_hitbox(Player *p) ;

//========================================================

/**
 * Cria uma hitbox para um inimigo
 * 
 * @param e Ponteiro para a estrutura do inimigo
 */
Hitbox get_enemy_hitbox(Enemy *e);

//========================================================

/**
 * Cria uma hitbox para um boss
 * 
 * @param b Ponteiro para a estrutura do boss
 */
Hitbox get_boss_hitbox(Boss *b);

//========================================================

#endif