#include "includes.h"


//==============================================================================


// Função que inicializa um inimigo com posição X bem espaçada
void init_enemy(Enemy *e, float y) 
{
    static bool primeira_chamada = true;
    if (primeira_chamada) {
        srand(time(NULL));
        primeira_chamada = false;
    }

    // Gera posição X aleatória com maior espaçamento:
    // - Entre 200% e 500% da largura da tela (mais longe)
    // - Incremento mínimo de 50% da tela entre inimigos
    float fator_base = 2.0f; // Começa em 2x a largura da tela
    float variacao = (rand() % 300) / 100.0f; // 0.0 a 3.0
    e->x = TELA_LARGURA * (fator_base + variacao); // 2.0 a 5.0 x largura
    
    // Ajuste para garantir distância mínima entre inimigos
    static float ultima_posicao = 0;
    if (e->x - ultima_posicao < TELA_LARGURA * 0.8f) { // Se muito próximo
        e->x = ultima_posicao + TELA_LARGURA * 0.8f; // Adiciona distância
    }
    ultima_posicao = e->x;

    e->y = ALTURA_CHAO - 35;
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
void update_enemy(Enemy *e) 
{
    if (!e->ativo) return;

    //Atualiza a posição
    e->x += e->vel_x;

    // Atualiza animação
    const int FRAME_DELAY = 6; // quanto menor, mais rápido anima
    e->timer_animacao++;
    if (e->timer_animacao >= FRAME_DELAY)
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

    float escala = 3.2;
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