#include "player.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>


#define GRAVIDADE 0.5
#define PULO -8
#define VELOCIDADE 3

#define VIDA_PLAYER 100
#define POSICAO_INICIAL_X 100
#define POSICAO_INICIAL_Y 380
#define ALTURA_SPRITE 48
#define LARGURA_SPRITE 32


//============================================================================


//  Função para iniciar o player
void init_player(Player *p) 
{
    printf("Inicializando jogador...\n");

    p->x = POSICAO_INICIAL_X;
    p->y = POSICAO_INICIAL_Y;
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

    p->vel_x = 0;

    // Movimento horizontal
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

    // Agachar
    if (al_key_down(&keyState, ALLEGRO_KEY_DOWN))
    {
        p->estado = CROUCH;
    }

    // Pulo (só permite se estiver no chão e can_jump for true)
    if (al_key_down(&keyState, ALLEGRO_KEY_SPACE) && can_jump && p->vel_y == 0) 
    {
        p->vel_y = PULO;
        p->estado = JUMP;
        can_jump = false;  // Impede novos pulos até tocar o chão
    }

    // Atualizar posição
    p->x += p->vel_x;
    p->y += p->vel_y;
    p->vel_y += GRAVIDADE;

    // Colisão com o chão
    if (p->y >= 380) 
    {
        p->y = 380;
        p->vel_y = 0;
        can_jump = true;  // Permite pular novamente ao tocar o chão
        
        if (p->estado == JUMP)  // Atualiza o estado se estava pulando
            p->estado = STAND;
    }
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
