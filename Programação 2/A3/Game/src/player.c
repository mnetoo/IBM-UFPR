#include "includes.h"


//============================================================================


// Função para iniciar o player
void init_player(Player *p) 
{
    printf("Inicializando jogador...\n");

    // Inicialização das propriedades básicas do jogador
    p->x = ALTURA_CHAO;  // Posição X inicial definida por constante
    p->y = ALTURA_CHAO - LARGURA_SPRITE;  // Posiciona o jogador no chão

    p->vel_x = 0;  // Velocidade horizontal inicial zero
    p->vel_y = 0;  // Velocidade vertical inicial zero

    p->width = LARGURA_SPRITE;  // Largura do sprite
    p->height = ALTURA_SPRITE;  // Altura do sprite

    p->vida = VIDA_PLAYER;  // Vida inicial definida por constante

    p->estado = STAND_AND_STOP;  // Estado inicial: parado

    p->olhando_para_direita = 1;  // Direção inicial: direita

    // Carregamento dos sprites - cada estado tem seu próprio sprite
    p->sprite_stand_and_stop = al_load_bitmap("./assets/player/space-marine/Sprites/Idle/sprites/idle-gun1.png");
    p->sprite_crouch = al_load_bitmap("./assets/player/space-marine/Sprites/Crouch/sprites/crouch3.png");
    p->sprite_jump = al_load_bitmap("./assets/player/space-marine/Sprites/Jump/sprites/jump2.png");
    p->sprite_jump_and_shot = al_load_bitmap("./assets/player/space-marine/Sprites/Jump/sprites/jump2.png");
    
    for (int i = 0; i < 10; i++) 
    {
        char filename[100];
        sprintf(filename, "./assets/player/space-marine/Sprites/Run_Gun/sprites/run%d.png", i + 1);
        p->sprite_run[i] = al_load_bitmap(filename);
    }   
    
    for (int i = 0; i < 2; i++) 
    {
        char filename[100];
        sprintf(filename, "./assets/player/space-marine/Sprites/Shoot/sprites/shoot%d.png", i + 1);
        p->sprite_shoot[i] = al_load_bitmap(filename);
    } 

    for (int i = 0; i < 2; i++) 
    {
        char filename[100];
        sprintf(filename, "./assets/player/space-marine/Sprites/Crouch _Shoot/sprites/crouch-shoot%d.png", i + 1);
        p->sprite_crouch_and_shot[i] = al_load_bitmap(filename);
    } 

    // Verificação de erros no carregamento dos sprites
    if (!p->sprite_stand_and_stop) printf("Erro ao carregar stand_and_stop.png\n");
    if (!p->sprite_crouch) printf("Erro ao carregar crouch.png\n");
    if (!p->sprite_jump) printf("Erro ao carregar jump.png\n");
    if (!p->sprite_jump_and_shot) printf("Erro ao carregar jump_and_shot.png\n");
    for (int i = 0; i < 10; i++) 
        if(!p->sprite_run[i]) printf("Erro ao carregar sprites de corrida\n");
    for (int i = 0; i < 2; i++) 
        if(!p->sprite_shoot[i]) printf("Erro ao carregar sprites de tiro\n");
    for (int i = 0; i < 2; i++) 
        if(!p->sprite_crouch_and_shot[i]) printf("Erro ao carregar sprites de tiro agachado\n");

    printf("Jogador inicializado com sucesso...\n\n");
}


//============================================================================


//  Função para criar o projétil
void shoot_projectile(Player *p) 
{
    float origem_y = 0;

    //  se estiver agachado o tiro sai mais baixo
    if(p->estado == CROUCH || p->estado == CROUCH_AND_SHOT)
        origem_y = 555;
    //  se estiver pulando o tiro sai mais alto
    else if(p->estado == JUMP || p->estado == JUMP_AND_SHOT)
        origem_y = 450;
    //  esta de pe altura normal
    else
        origem_y = 525;

    for (int i = 0; i < MAX_PROJECTILES; i++)
     {
        if (!p->projeteis[i].ativo) 
        {
            float velocidade = p->olhando_para_direita ? VELOCIDADE_BULLET : -VELOCIDADE_BULLET;
            float origem_x = p->x + (p->olhando_para_direita ? 150 : -10);
            init_projectile(&p->projeteis[i], origem_x, origem_y, velocidade);
            break;
        }
    }
}


//============================================================================


// Função de atualização do estado do jogador a cada frame
void update_player(Player *p) 
{
    static bool can_jump = true;
    static bool mouse_seguro = false;
    const int FRAME_DELAY = 5;

    ALLEGRO_KEYBOARD_STATE keyState;
    ALLEGRO_MOUSE_STATE mouseState;
    al_get_keyboard_state(&keyState);
    al_get_mouse_state(&mouseState);

    bool atirando = mouseState.buttons & 1;
    if (atirando && !mouse_seguro) 
    {
        shoot_projectile(p);
        mouse_seguro = true;
    }
    if (!atirando) mouse_seguro = false;

    p->vel_x = 0;
    bool no_ar = (p->y < (ALTURA_CHAO - ALTURA_SPRITE));

    bool esta_agachado = al_key_down(&keyState, ALLEGRO_KEY_S) || 
                          al_key_down(&keyState, ALLEGRO_KEY_DOWN) || 
                          al_key_down(&keyState, ALLEGRO_KEY_LSHIFT);

    // Pulo
    if ((al_key_down(&keyState, ALLEGRO_KEY_SPACE) || al_key_down(&keyState, ALLEGRO_KEY_UP) || al_key_down(&keyState, ALLEGRO_KEY_W)) 
        && can_jump && !no_ar && !esta_agachado) 
    {
        p->vel_y = PULO;
        can_jump = false;
    }

    // Movimento
    if (al_key_down(&keyState, ALLEGRO_KEY_D) || al_key_down(&keyState, ALLEGRO_KEY_RIGHT)) {
        p->vel_x = VELOCIDADE;
        p->olhando_para_direita = 1;
    } else if (al_key_down(&keyState, ALLEGRO_KEY_A) || al_key_down(&keyState, ALLEGRO_KEY_LEFT)) {
        p->vel_x = -VELOCIDADE;
        p->olhando_para_direita = 0;
    }

    // ESTADOS
    if (no_ar) 
    {
        if (atirando)
            p->estado = JUMP_AND_SHOT;
        else
            p->estado = JUMP;
    } 
    else if (esta_agachado) 
    {
        if (atirando)
            p->estado = CROUCH_AND_SHOT;
        else
            p->estado = CROUCH;
    } 
    else if (p->vel_x != 0) 
    {
        if (atirando)
            p->estado = STAND_AND_SHOT; // Pode criar um novo estado WALK_AND_SHOT se quiser animação separada
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
    else 
    {
        if (atirando)
            p->estado = STAND_AND_SHOT;
        else
            p->estado = STAND_AND_STOP;
    }

    // Animação de tiro
    if (atirando) 
    {
        p->timer_shoot++;
        if (p->timer_shoot >= FRAME_DELAY) 
        {
            p->timer_shoot = 0;
            p->frame_shoot = (p->frame_shoot + 1) % NUM_FRAMES_SHOOT;
        }
    }

    // Atualiza posição
    p->x = 100; // Fixo na tela
    p->player_pos_mundo_x += p->vel_x;
    p->y += p->vel_y;

    // Gravidade
    if (p->y < (ALTURA_CHAO - ALTURA_SPRITE)) 
        p->vel_y += GRAVIDADE;
    else 
    {
        p->y = ALTURA_CHAO - ALTURA_SPRITE;
        p->vel_y = 0;
        can_jump = true;
    }

    if (!(al_key_down(&keyState, ALLEGRO_KEY_SPACE) || 
          al_key_down(&keyState, ALLEGRO_KEY_UP) || 
          al_key_down(&keyState, ALLEGRO_KEY_W)))
        can_jump = true;

    // Atualiza projéteis
    for (int i = 0; i < MAX_PROJECTILES; i++)
        update_projectile(&p->projeteis[i]);
}



//============================================================================


//  Função para trocar as sprites do player
void draw_player(Player *p) 
{
    ALLEGRO_BITMAP *sprite = NULL;  // Ponteiro para o sprite atual

    switch (p->estado) 
    {
        case STAND_AND_STOP:
            sprite = p->sprite_stand_and_stop;
            break;

        case STAND_AND_SHOT:
            sprite = p->sprite_shoot[p->frame_shoot];
            break;

        case WALK:
            sprite = p->sprite_run[p->frame_andar];
            break;

        case JUMP:
            sprite = p->sprite_jump;
            break;

        case JUMP_AND_SHOT:
            sprite = p->sprite_jump_and_shot;
            break;

        case CROUCH:
            sprite = p->sprite_crouch;
            break;

        case CROUCH_AND_SHOT:
            sprite = p->sprite_crouch_and_shot[p->frame_shoot];
            break;

        default:
            sprite = p->sprite_stand_and_stop;
            break;
    }

    // Se o sprite foi carregado corretamente
    if (sprite) 
    {
        float escala = 3.5;  // Fator de escala para aumentar o sprite
        int flip = p->olhando_para_direita ? 0 : ALLEGRO_FLIP_HORIZONTAL;  // Flip horizontal se olhando para esquerda

        // Desenha o sprite com transformações
        al_draw_scaled_bitmap(
            sprite,  // Bitmap a ser desenhado
            0, 0,  // Posição de origem no bitmap
            al_get_bitmap_width(sprite),  // Largura do bitmap
            al_get_bitmap_height(sprite),  // Altura do bitmap
            p->x,  // Posição X na tela
            p->y,  // Posição Y na tela
            al_get_bitmap_width(sprite) * escala,  // Largura escalada
            al_get_bitmap_height(sprite) * escala,  // Altura escalada
            flip  // Flags de transformação (flip horizontal)
        );

        for (int i = 0; i < MAX_PROJECTILES; i++)
            draw_projectile(&p->projeteis[i]);
    }
}



//============================================================================


//  Função para destruir o player
void destroy_player(Player *p) 
{
    // Destrói todos os bitmaps carregados
    al_destroy_bitmap(p->sprite_stand_and_stop);
    al_destroy_bitmap(p->sprite_jump_and_shot);
    al_destroy_bitmap(p->sprite_crouch);
    al_destroy_bitmap(p->sprite_jump);

    // Destrói todos os frames da animação de corrida
    for (int i = 0; i < 10; i++) 
    {
        if (p->sprite_run[i])
            al_destroy_bitmap(p->sprite_run[i]);
    }

    for (int i = 0; i < 2; i++) 
        if (p->sprite_shoot[i])
            al_destroy_bitmap(p->sprite_shoot[i]);

    for (int i = 0; i < 10; i++) 
        if (p->sprite_crouch_and_shot[i])
            al_destroy_bitmap(p->sprite_crouch_and_shot[i]);

    for (int i = 0; i < MAX_PROJECTILES; i++)
        destroy_projectile(&p->projeteis[i]);
    
}



//============================================================================