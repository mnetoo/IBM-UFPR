#include "includes.h"


//============================================================================


//  Função para iniciar o player
void init_player(Player *p) 
{
    printf("Inicializando jogador...\n");

    p->x = POSICAO_INICIAL_X;
    p->y = ALTURA_CHAO - LARGURA_SPRITE;
    p->vel_x = 0;
    p->vel_y = 0;
    p->width = LARGURA_SPRITE;
    p->height = ALTURA_SPRITE;
    p->vida = VIDA_PLAYER;
    p->estado = STAND;

    // Carregar sprites (coloque os arquivos reais em assets/player/)
    p->sprite_stand   = al_load_bitmap("./assets/player/stand.png");
    p->sprite_walk    = al_load_bitmap("./assets/player/walk.png");
    p->sprite_jump    = al_load_bitmap("./assets/player/jump.png");
    p->sprite_crouch  = al_load_bitmap("./assets/player/crouch.png");
    p->sprite_shoot   = al_load_bitmap("./assets/player/shoot.png");

    // Verificar carregamento
    if (!p->sprite_stand)   
        printf("Erro ao carregar stand.png\n");
    if (!p->sprite_walk)    
        printf("Erro ao carregar walk.png\n");
    if (!p->sprite_jump)    
        printf("Erro ao carregar jump.png\n");
    if (!p->sprite_crouch)  
        printf("Erro ao carregar crouch.png\n");
    if (!p->sprite_shoot)   
        printf("Erro ao carregar shoot.png\n");

    printf("Jogador inicializado com sucesso...\n\n");
}


//============================================================================


//  Função para movimentar o player
void update_player(Player *p) 
{
    static bool can_jump = true;  // Controla se o jogador pode pular
    ALLEGRO_KEYBOARD_STATE keyState;
    al_get_keyboard_state(&keyState);

    // Resetar a velocidade horizontal
    p->vel_x = 0;

    // Verifica se está no ar
    bool no_ar = (p->vel_y != 0);

    // Movimento horizontal (somente muda sprite se não estiver pulando)
    if (!no_ar) 
    {
        if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT)) 
        {
            p->vel_x = VELOCIDADE;
            p->estado = WALK;
        } 
        else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT)) 
        {
            p->vel_x = -VELOCIDADE;
            p->estado = WALK;
        } 
        else
        {
            p->estado = STAND;
        }

        // Agachar (também só se não estiver no ar)
        if (al_key_down(&keyState, ALLEGRO_KEY_DOWN))
        {
            p->estado = CROUCH;
        }
    }

    // Pulo (só permite se estiver no chão e can_jump for true)
    if (al_key_down(&keyState, ALLEGRO_KEY_SPACE) && can_jump && p->vel_y == 0) 
    {
        p->vel_y = PULO;
        p->estado = JUMP;
        can_jump = false;
    }

    // Atualizar posição
    p->x += p->vel_x;
    p->y += p->vel_y;
    p->vel_y += GRAVIDADE;

    float limite_y = ALTURA_CHAO - p->height;
    bool em_chao_visivel = tem_chao_visivel(p->x + p->width / 2);

    if (em_chao_visivel && p->y >= limite_y) 
    {
        p->y = limite_y;
        p->vel_y = 0;
        can_jump = true;

        // Só muda o estado ao tocar o chão, caso ainda estivesse em JUMP
        if (p->estado == JUMP)
        {
            if (al_key_down(&keyState, ALLEGRO_KEY_LEFT) || al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
                p->estado = WALK;
            else
                p->estado = STAND;
        }
    }

    if (p->y > TELA_ALTURA)
        p->vida = 0;  // ou mudar estado diretamente
}


//============================================================================


//  Função para trocar as sprites do player
void draw_player(Player *p) 
{
    ALLEGRO_BITMAP *sprite = NULL;

    switch (p->estado) 
    {
        case STAND:  
            sprite = p->sprite_stand; 
            break;
        case WALK:   
            sprite = p->sprite_walk; 
            break;
        case JUMP:   
            sprite = p->sprite_jump; 
            break;
        case CROUCH: 
            sprite = p->sprite_crouch; 
            break;
        case SHOOT:  
            sprite = p->sprite_shoot; 
            break;
        default:     
            sprite = p->sprite_stand;
    }

    if (sprite)
        al_draw_bitmap(sprite, p->x, p->y, 0);
}


//============================================================================


//  Função para destruir o player
void destroy_player(Player *p) 
{
    al_destroy_bitmap(p->sprite_stand);
    al_destroy_bitmap(p->sprite_walk);
    al_destroy_bitmap(p->sprite_jump);
    al_destroy_bitmap(p->sprite_crouch);
    al_destroy_bitmap(p->sprite_shoot);
}


//============================================================================