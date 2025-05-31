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
    p->estado = STAND_AND_STOP;
    p->olhando_para_direita = 1;

    // Carregar sprites
    p->sprite_stand_and_stop   = al_load_bitmap("./assets/player/stand_and_stop.png");
    p->sprite_stand_and_shot   = al_load_bitmap("./assets/player/stand_and_shot.png");

    p->sprite_walk1 = al_load_bitmap("./assets/player/walk1.png");
    p->sprite_walk2 = al_load_bitmap("./assets/player/walk2.png");
    p->sprite_walk3 = al_load_bitmap("./assets/player/walk3.png");
    p->sprite_walk4 = al_load_bitmap("./assets/player/walk4.png");

    p->sprite_jump1 = al_load_bitmap("./assets/player/jump1.png");
    p->sprite_jump2 = al_load_bitmap("./assets/player/jump2.png");

    p->sprite_crouch1 = al_load_bitmap("./assets/player/crouch1.png"); // direita
    p->sprite_crouch2 = al_load_bitmap("./assets/player/crouch2.png"); // esquerda

    p->sprite_crouch_and_shot = al_load_bitmap("./assets/player/crouch_and_shot.png");

    // Verificar carregamento
    if (!p->sprite_stand_and_stop) printf("Erro ao carregar stand_and_stop.png\n");
    if (!p->sprite_stand_and_shot) printf("Erro ao carregar stand_and_shot.png\n");

    if (!p->sprite_walk1) printf("Erro ao carregar walk1.png\n");
    if (!p->sprite_walk2) printf("Erro ao carregar walk2.png\n");
    if (!p->sprite_walk3) printf("Erro ao carregar walk3.png\n");
    if (!p->sprite_walk4) printf("Erro ao carregar walk4.png\n");

    if (!p->sprite_jump1) printf("Erro ao carregar jump1.png\n");
    if (!p->sprite_jump2) printf("Erro ao carregar jump2.png\n");

    if (!p->sprite_crouch1) printf("Erro ao carregar crouch1.png\n");
    if (!p->sprite_crouch2) printf("Erro ao carregar crouch2.png\n");
    if (!p->sprite_crouch_and_shot) printf("Erro ao carregar crouch_and_shot.png\n");

    printf("Jogador inicializado com sucesso...\n\n");
}


//============================================================================


void update_player(Player *p) 
{
    static bool can_jump = true;
    static int walk_timer = 0;
    const int WALK_FRAME_DELAY = 10;

    ALLEGRO_KEYBOARD_STATE keyState;
    al_get_keyboard_state(&keyState);

    p->vel_x = 0;

    bool no_ar = (p->y < (ALTURA_CHAO - ALTURA_SPRITE));
    bool esta_agachado = al_key_down(&keyState, ALLEGRO_KEY_DOWN);

    // Movimento horizontal
    if (!esta_agachado) 
    {
        if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT)) 
        {
            p->vel_x = VELOCIDADE;
            p->olhando_para_direita = true;  // Atualiza direção
            if (no_ar)
                p->estado = JUMP1;
            else {
                if (walk_timer < WALK_FRAME_DELAY)
                    p->estado = WALK1;
                else
                    p->estado = WALK2;
                walk_timer = (walk_timer + 1) % (2 * WALK_FRAME_DELAY);
            }
        } 
        else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT)) 
        {
            p->vel_x = -VELOCIDADE;
            p->olhando_para_direita = false; // Atualiza direção
            if (no_ar)
                p->estado = JUMP2;
            else {
                if (walk_timer < WALK_FRAME_DELAY)
                    p->estado = WALK3;
                else
                    p->estado = WALK4;
                walk_timer = (walk_timer + 1) % (2 * WALK_FRAME_DELAY);
            }
        } 
        else if (!no_ar) 
        {
            p->estado = STAND_AND_STOP;
            walk_timer = 0;
        }
    }

    // Agachar
    if (!no_ar && esta_agachado) 
    {
        if (p->vel_x > 0)
            p->estado = CROUCH1;
        else if (p->vel_x < 0)
            p->estado = CROUCH2;
        else
            p->estado = p->olhando_para_direita ? CROUCH1 : CROUCH2;  // Corrigido aqui

        walk_timer = 0;
    }

    // Pulo
    if (al_key_down(&keyState, ALLEGRO_KEY_SPACE) && can_jump && !no_ar && !esta_agachado) 
    {
        p->vel_y = PULO;

        if (p->vel_x > 0)
            p->estado = JUMP1;
        else if (p->vel_x < 0)
            p->estado = JUMP2;
        else
            p->estado = p->olhando_para_direita ? JUMP1 : JUMP2;

        can_jump = false;
    }

    p->x += p->vel_x;
    p->y += p->vel_y;

    if (p->y < (ALTURA_CHAO - ALTURA_SPRITE)) 
    {
        p->vel_y += GRAVIDADE;
    } 
    else 
    {
        p->y = ALTURA_CHAO - ALTURA_SPRITE;
        p->vel_y = 0;
        can_jump = true;
    
        if ((p->estado == JUMP1 || p->estado == JUMP2) && p->vel_x == 0)
            p->estado = STAND_AND_STOP;
    }
    

    if (!al_key_down(&keyState, ALLEGRO_KEY_SPACE))
        can_jump = true;

    //if (p->y > TELA_ALTURA)
        //p->vida = 0;
}


//============================================================================


//  Função para trocar as sprites do player
void draw_player(Player *p) 
{
    ALLEGRO_BITMAP *sprite = NULL;

    switch (p->estado) 
    {
        case STAND_AND_STOP:
            sprite = p->sprite_stand_and_stop;
            break;
        case STAND_AND_SHOT:
            sprite = p->sprite_stand_and_shot;
            break;
        case WALK1:
            sprite = p->sprite_walk1;
            break;
        case WALK2:
            sprite = p->sprite_walk2;
            break;
        case WALK3:
            sprite = p->sprite_walk3;
            break;
        case WALK4:
            sprite = p->sprite_walk4;
            break;
        case JUMP1:
            sprite = p->sprite_jump1;
            break;
        case JUMP2:
            sprite = p->sprite_jump2;
            break;
        case CROUCH1:
            sprite = p->sprite_crouch1;
            break;
        case CROUCH2:
            sprite = p->sprite_crouch2;
            break;
        case CROUCH_AND_SHOT:
            sprite = p->sprite_crouch_and_shot;
            break;
        default:
            sprite = p->sprite_stand_and_stop;
            break;
    }

    if (sprite)
        al_draw_bitmap(sprite, p->x, p->y, 0);
}



//============================================================================


//  Função para destruir o player
void destroy_player(Player *p) 
{
    al_destroy_bitmap(p->sprite_stand_and_stop);
    al_destroy_bitmap(p->sprite_stand_and_shot);

    al_destroy_bitmap(p->sprite_walk1);
    al_destroy_bitmap(p->sprite_walk2);
    al_destroy_bitmap(p->sprite_walk3);
    al_destroy_bitmap(p->sprite_walk4);

    al_destroy_bitmap(p->sprite_jump1);
    al_destroy_bitmap(p->sprite_jump2);

    al_destroy_bitmap(p->sprite_crouch1);
    al_destroy_bitmap(p->sprite_crouch2);
    al_destroy_bitmap(p->sprite_crouch_and_shot);
}


//============================================================================