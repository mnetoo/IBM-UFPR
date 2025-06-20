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


bool colisao_retangulos(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);

// Modifique a declaração para:
Hitbox get_projectile_hitbox(void *p, int is_enemy_projectile);

Hitbox get_player_hitbox(Player *p);

Hitbox get_enemy_hitbox(Enemy *e);


#endif