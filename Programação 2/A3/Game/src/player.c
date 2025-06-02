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
    p->sprite_stand_and_stop   = al_load_bitmap("./assets/player/space-marine/Sprites/Idle/sprites/idle-gun1.png");
    p->sprite_stand_and_shot   = al_load_bitmap("./assets/player/stand_and_shot.png");

    for (int i = 0; i < 10; i++) 
    {
        char filename[100];
        sprintf(filename, "./assets/player/space-marine/Sprites/Run/sprites/run%d.png", i + 1);
        p->sprite_run[i] = al_load_bitmap(filename);
    }

    p->sprite_crouch = al_load_bitmap("./assets/player/space-marine/Sprites/Crouch/sprites/crouch3.png");
    p->sprite_jump = al_load_bitmap("./assets/player/space-marine/Sprites/Jump/sprites/jump2.png");
    

    // Verificar carregamento
    if (!p->sprite_stand_and_stop) printf("Erro ao carregar stand_and_stop.png\n");
    if (!p->sprite_stand_and_shot) printf("Erro ao carregar stand_and_shot.png\n");

    printf("Jogador inicializado com sucesso...\n\n");
}


//============================================================================


void update_player(Player *p) 
{
    static bool can_jump = true;
    const int FRAME_DELAY = 5;

    ALLEGRO_KEYBOARD_STATE keyState;
    al_get_keyboard_state(&keyState);

    p->vel_x = 0;

    bool no_ar = (p->y < (ALTURA_CHAO - ALTURA_SPRITE));
    bool esta_agachado = al_key_down(&keyState, ALLEGRO_KEY_DOWN);

    // =============================
    // PRIORIDADE: AGACHAR
    // =============================
    if (!no_ar && esta_agachado) 
    {
        p->estado = p->olhando_para_direita ? CROUCH : CROUCH;

        p->timer_agachar++;
        if (p->timer_agachar >= FRAME_DELAY)
        {
            p->timer_agachar = 0;
            p->frame_agachar = (p->frame_agachar + 1) % 10;
        }

        // Travar o movimento horizontal
        p->vel_x = 0;
        return;  // IMPORTANTE: não processa mais nada enquanto agachado
    }
    else 
    {
        p->timer_agachar = 0;
        p->frame_agachar = 0;
    }

    // =============================
    // MOVIMENTO HORIZONTAL
    // =============================
    if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT)) 
    {
        p->vel_x = VELOCIDADE;
        p->olhando_para_direita = true;

        if (no_ar)
        {
            p->estado = JUMP;
        }
        else
        {
            p->estado = WALK;
            p->timer_andar++;
            if (p->timer_andar >= FRAME_DELAY)
            {
                p->timer_andar = 0;
                p->frame_andar = (p->frame_andar + 1) % 10;
            }
        }
    } 
    else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT)) 
    {
        p->vel_x = -VELOCIDADE;
        p->olhando_para_direita = false;

        if (no_ar)
        {
            p->estado = JUMP;
        }
        else
        {
            p->estado = WALK;
            p->timer_andar++;
            if (p->timer_andar >= FRAME_DELAY)
            {
                p->timer_andar = 0;
                p->frame_andar = (p->frame_andar + 1) % 10;
            }
        }
    } 
    else if (!no_ar) 
    {
        p->estado = STAND_AND_STOP;
        p->frame_andar = 0;
        p->timer_andar = 0;
    }

    // =============================
    // PULO (inicia apenas no chão)
    // =============================
    if (al_key_down(&keyState, ALLEGRO_KEY_SPACE) && can_jump && !no_ar && !esta_agachado) 
    {
        p->vel_y = PULO;
        p->estado = p->olhando_para_direita ? JUMP : JUMP;

        p->frame_pulo = 0;
        p->timer_pulo = 0;

        can_jump = false;
    }

    // =============================
    // ANIMAÇÃO DO PULO
    // =============================
    if (no_ar && (p->estado == JUMP))
    {
        p->timer_pulo++;
        if (p->timer_pulo >= FRAME_DELAY)
        {
            p->timer_pulo = 0;
            if (p->frame_pulo < 9) // 10 frames (0 a 9)
                p->frame_pulo++;
        }
    }

    p->x = 100;  
    p->player_pos_mundo_x += p->vel_x;
    p->y += p->vel_y;

    // Gravidade e chão
    if (p->y < (ALTURA_CHAO - ALTURA_SPRITE)) 
    {
        p->vel_y += GRAVIDADE;
    } 
    else 
    {
        if ((p->estado == JUMP) && p->frame_pulo < 9) 
        {
            // Segura no ar até a animação de pulo acabar
            p->vel_y = 0;
            p->y = (ALTURA_CHAO - ALTURA_SPRITE) - 1;
        }
        else 
        {
            p->y = ALTURA_CHAO - ALTURA_SPRITE;
            p->vel_y = 0;
            can_jump = true;

            if ((p->estado == JUMP) && p->vel_x == 0)
                p->estado = STAND_AND_STOP;
        }
    }

    // Libera pulo ao soltar espaço
    if (!al_key_down(&keyState, ALLEGRO_KEY_SPACE))
        can_jump = true;

    // Limites da tela
    if (p->x < 0)
        p->x = 0;
    else if (p->x > TELA_LARGURA - LARGURA_SPRITE)
        p->x = TELA_LARGURA - LARGURA_SPRITE;
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

        case WALK:
            sprite = p->sprite_run[p->frame_andar];  // usa o frame da caminhada
            break;

        case JUMP:
            sprite = p->sprite_jump[p->frame_andar];  // usa o frame do pulo
            break;

        case CROUCH:
            sprite = p->sprite_crouch[p->frame_andar];  // usa o frame do agachado
            break;

        case CROUCH_AND_SHOT:
            sprite = p->sprite_crouch_and_shot;
            break;

        default:
            sprite = p->sprite_stand_and_stop;
            break;
    }

    if (sprite) 
    {
        float escala = 5;  // escala da sprite (pode ajustar esse valor)
        int flip = p->olhando_para_direita ? 0 : ALLEGRO_FLIP_HORIZONTAL;

        al_draw_scaled_bitmap(
            sprite,
            0, 0,
            al_get_bitmap_width(sprite),
            al_get_bitmap_height(sprite),
            p->x,
            p->y,
            al_get_bitmap_width(sprite) * escala,
            al_get_bitmap_height(sprite) * escala,
            flip
        );
    }
}



//============================================================================


//  Função para destruir o player
void destroy_player(Player *p) 
{
    al_destroy_bitmap(p->sprite_stand_and_stop);
    al_destroy_bitmap(p->sprite_stand_and_shot);
    al_destroy_bitmap(p->sprite_crouch_and_shot);

    for (int i = 0; i < 10; i++) 
    {
        if (p->sprite_run[i])
            al_destroy_bitmap(p->sprite_run[i]);

        if (p->sprite_jump[i])
            al_destroy_bitmap(p->sprite_jump[i]);

        if (p->sprite_crouch[i])
            al_destroy_bitmap(p->sprite_crouch[i]);
    }
}



//============================================================================