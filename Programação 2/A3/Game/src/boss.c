#include "includes.h"

// Número de quadros por animação
const int NUM_FRAMES = 6;

// Estado atual do Boss (poderia também estar no struct Boss)
static BossState boss_state = IDLE;


//==============================================================================


// Função auxiliar para carregar animações
void load_animation(ALLEGRO_BITMAP *dest[], const char *path_template, const char *label) 
{
    for (int i = 0; i < NUM_FRAMES; i++)
     {
        char filename[100];
        sprintf(filename, path_template, i + 1);
        dest[i] = al_load_bitmap(filename);
        if (!dest[i])
            printf("Erro ao carregar sprite %s %d\n", label, i);
    }
}


// Função que inicializa o Boss
void init_boss(Boss *b, float pos_x) 
{
    printf("Inicializando The Boss...\n");

    b->x = pos_x;
    b->y = 420;
    b->vel_x = -2;
    b->vel_y = -2;
    b->vida = 200;

    b->frame_atual = 0;
    b->timer_animacao = 0;

    load_animation(b->idle, "./assets/enemies/Hell-Beast-Files/Idle/Sprites/hell-beast-idle%d.png", "idle");
    load_animation(b->burn, "./assets/enemies/Hell-Beast-Files/Burn/Sprites/hell-beast-burn%d.png", "burn");

    boss_state = IDLE;

    printf("The Boss inicializado com sucesso.\n\n");
}


//==============================================================================


// Função de movimentação e animação do Boss
void update_boss(Boss *b, float player_mundo) 
{
    // Movimento simples
    b->x += b->vel_x;
    b->y += b->vel_y;

    // Atualiza animação
    b->timer_animacao++;
    if (b->timer_animacao >= 10) 
    {
        b->frame_atual = (b->frame_atual + 1) % NUM_FRAMES;
        b->timer_animacao = 0;
    }

    // Exemplo de mudança de estado (opcional)
    if (b->vida < 100)
        boss_state = BURN;
    else
        boss_state = IDLE;
}


//==============================================================================


// Desenha o Boss com base no estado atual
void draw_boss(Boss *b) 
{
    float pos_x = b->x;
    float pos_y = b->y;
    float escala = 5;
    int flip = ALLEGRO_FLIP_HORIZONTAL;

    ALLEGRO_BITMAP *sprite_atual = NULL;

    if (boss_state == IDLE)
        sprite_atual = b->idle[b->frame_atual];
    else if (boss_state == BURN)
        sprite_atual = b->burn[b->frame_atual];

    if (sprite_atual) 
    {
        al_draw_scaled_bitmap(
            sprite_atual,
            0, 0,
            al_get_bitmap_width(sprite_atual),
            al_get_bitmap_height(sprite_atual),
            pos_x,
            pos_y,
            al_get_bitmap_width(sprite_atual) * escala,
            al_get_bitmap_height(sprite_atual) * escala,
            flip
        );
    }
}


//==============================================================================


// Libera memória dos bitmaps do Boss
void destroy_boss(Boss *b) 
{
    for (int i = 0; i < NUM_FRAMES; i++) 
    {
        if (b->idle[i]) 
        {
            al_destroy_bitmap(b->idle[i]);
            b->idle[i] = NULL;
        }

        if (b->burn[i]) 
        {
            al_destroy_bitmap(b->burn[i]);
            b->burn[i] = NULL;
        }
    }

    printf("The Boss foi destruído com sucesso.\n");
}


//==============================================================================