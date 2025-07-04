#include "includes.h"


//============================================================================


/**
 * @brief - Inicializa o jogador com valores padrão e carrega seus sprites
 * 
 * @param p - Ponteiro para a estrutura Player que será inicializada
 */
void init_player(Player *p) 
{
    printf("Inicializando jogador...\n");

    // Inicialização das propriedades básicas do jogador
    p->x = ALTURA_CHAO;
    p->y = ALTURA_CHAO - LARGURA_SPRITE;
    p->vel_x = 0;
    p->vel_y = 0;
    p->width = LARGURA_SPRITE;  
    p->height = ALTURA_SPRITE; 
    p->vida = VIDA_PLAYER; 
    p->estado = STAND_AND_STOP;
    p->olhando_para_direita = 1;

    // Inicializa os timers do efeito de queimadura
    p->burn_timer = 0;
    p->burn_tick_timer = 0;

    // Carregamento dos sprites - cada estado tem seu próprio sprite
    p->sprite_stand_and_stop = al_load_bitmap("./assets/player/space-marine/Sprites/Idle/sprites/idle-gun1.png");
    p->sprite_crouch = al_load_bitmap("./assets/player/space-marine/Sprites/Crouch/sprites/crouch3.png");
    p->sprite_jump = al_load_bitmap("./assets/player/space-marine/Sprites/Jump/sprites/jump2.png");
    p->sprite_jump_and_shot = al_load_bitmap("./assets/player/space-marine/Sprites/Jump/sprites/jump2.png");
    
    // Carrega os sprites de corrida (10 frames)
    for (int i = 0; i < 10; i++) 
    {
        char filename[100];
        sprintf(filename, "./assets/player/space-marine/Sprites/Run_Gun/sprites/run%d.png", i + 1);
        p->sprite_run[i] = al_load_bitmap(filename);
    }   
    
    // Carrega os sprites de tiro (2 frames)
    for (int i = 0; i < 2; i++) 
    {
        char filename[100];
        sprintf(filename, "./assets/player/space-marine/Sprites/Shoot/sprites/shoot%d.png", i + 1);
        p->sprite_shoot[i] = al_load_bitmap(filename);
    } 

    // Carrega os sprites de tiro agachado (2 frames)
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


/**
 * @brief - Dispara um projétil na direção especificada
 * 
 * @param p - Ponteiro para a estrutura Player que está atirando
 * @param direcao - Direção do tiro (SHOOT_DIREITA, SHOOT_ESQUERDA ou SHOOT_CIMA)
 */
void shoot_projectile(Player *p, int direcao) 
{
    // Define a posição Y inicial do projétil baseado no estado do jogador
    float origem_y;

    if(p->estado == CROUCH || p->estado == CROUCH_AND_SHOT)
        origem_y = 555;  // Posição Y quando agachado
    else if(p->estado == JUMP || p->estado == JUMP_AND_SHOT)
        origem_y = 450;  // Posição Y quando pulando
    else
        origem_y = 525;  // Posição Y padrão (em pé)

    // Procura por um projétil inativo para atirar
    for (int i = 0; i < MAX_PROJECTILES; i++) 
    {
        if (!p->projeteis[i].ativo) 
        {
            float vel_x = 0, vel_y = 0;
            float origem_x = p->x + 70; // posição horizontal centralizada

            // Define a direção e velocidade do projétil
            switch (direcao) 
            {
                case SHOOT_DIREITA:
                    vel_x = VELOCIDADE_BULLET;  // Velocidade positiva para direita
                    origem_x = p->x + 150;      // Ajusta posição de origem
                    break;
                case SHOOT_ESQUERDA:
                    vel_x = -VELOCIDADE_BULLET; // Velocidade negativa para esquerda
                    origem_x = p->x + 100;     // Ajusta posição de origem
                    break;
                case SHOOT_CIMA:
                    vel_y = -VELOCIDADE_BULLET; // Velocidade negativa para cima
                    origem_x = p->x + 150;      // Ajusta posição X
                    origem_y = p->y + 150;     // Ajusta posição Y
                    break;
            }

            // Inicializa o projétil com os parâmetros calculados
            init_projectile(&p->projeteis[i], origem_x, origem_y, vel_x, vel_y);
            break;  // Sai do loop após encontrar um projétil disponível
        }
    }
}


//============================================================================


/**
 * @brief - Atualiza o estado do jogador a cada frame
 * 
 * @param p - Ponteiro para a estrutura Player a ser atualizada
 * @param enemies - Vetor de inimigos para verificação de colisão
 * @param boss - Ponteiro para o boss para verificação de colisão
 */
void update_player(Player *p, Enemy enemies[], Boss *boss) 
{
    static bool can_jump = true;  // Controla se o jogador pode pular
    const int FRAME_DELAY = 5;    // Delay entre frames de animação

    // Obtém o estado atual do teclado
    ALLEGRO_KEYBOARD_STATE keyState;
    al_get_keyboard_state(&keyState);

    // Verifica teclas de tiro (setas)
    bool seta_direita = al_key_down(&keyState, ALLEGRO_KEY_RIGHT);
    bool seta_esquerda = al_key_down(&keyState, ALLEGRO_KEY_LEFT);
    bool seta_cima = al_key_down(&keyState, ALLEGRO_KEY_UP);

    static bool seta_segura = false;  // Evita tiros contínuos enquanto a tecla está pressionada
    bool atirando = false;            // Controla se o jogador está atirando no frame atual

    // Lógica para detectar quando o jogador começa a atirar
    if (!seta_segura) 
    {
        if (seta_direita) 
        {
            shoot_projectile(p, SHOOT_DIREITA);
            seta_segura = true;
            atirando = true;
        } 
        else if (seta_esquerda) 
        {
            shoot_projectile(p, SHOOT_ESQUERDA);
            seta_segura = true;
            atirando = true;
        } 
        else if (seta_cima) 
        {
            shoot_projectile(p, SHOOT_CIMA);
            seta_segura = true;
            atirando = true;
        }
    }

    // Libera o bloqueio de tiro quando as teclas são soltas
    if (!seta_direita && !seta_esquerda && !seta_cima)
        seta_segura = false;

    // Reinicia a velocidade horizontal
    p->vel_x = 0;
    // Verifica se o jogador está no ar
    bool no_ar = (p->y < (ALTURA_CHAO - ALTURA_SPRITE));

    // Verifica se o jogador está agachado
    bool esta_agachado = al_key_down(&keyState, ALLEGRO_KEY_S) || al_key_down(&keyState, ALLEGRO_KEY_LSHIFT);

    // Lógica de pulo
    if ((al_key_down(&keyState, ALLEGRO_KEY_SPACE) || al_key_down(&keyState, ALLEGRO_KEY_W)) && can_jump && !no_ar && !esta_agachado) 
    {
        p->vel_y = PULO;      // Aplica velocidade vertical (pulo)
        can_jump = false;      // Impede pulos consecutivos
    }

    // Lógica de movimento horizontal
    if (al_key_down(&keyState, ALLEGRO_KEY_D))
    {
        p->vel_x = VELOCIDADE;            // Move para direita
        p->olhando_para_direita = 1;       // Atualiza direção do sprite
    } 
    else if (al_key_down(&keyState, ALLEGRO_KEY_A))
    {
        p->vel_x = -VELOCIDADE;           // Move para esquerda
        p->olhando_para_direita = 0;      // Atualiza direção do sprite
    }

    // MÁQUINA DE ESTADOS - Define o estado atual do jogador
    if (no_ar) 
    {
        // Estados no ar
        if (atirando)
            p->estado = JUMP_AND_SHOT;  // Pulo + tiro
        else
            p->estado = JUMP;           // Pulo normal
    } 
    else if (esta_agachado) 
    {
        // Estados agachado
        if (atirando)
            p->estado = CROUCH_AND_SHOT;  // Agachado + tiro
        else
            p->estado = CROUCH;            // Agachado normal
    } 
    else if (p->vel_x != 0) 
    {
        // Estados em movimento horizontal
        if (atirando)
            p->estado = STAND_AND_SHOT;  // Andando + tiro
        else 
        {
            p->estado = WALK;            // Andando normal
            // Avança a animação de andar
            p->timer_andar++;
            if (p->timer_andar >= FRAME_DELAY) 
            {
                p->timer_andar = 0;
                p->frame_andar = (p->frame_andar + 1) % 10;  // Cicla entre 0-9
            }
        }
    } 
    else 
    {
        // Estados parado
        if (atirando)
            p->estado = STAND_AND_SHOT;  // Parado + tiro
        else
            p->estado = STAND_AND_STOP; // Parado normal
    }

    // Animação de tiro
    if (atirando) 
    {
        p->timer_shoot++;
        if (p->timer_shoot >= FRAME_DELAY) 
        {
            p->timer_shoot = 0;
            p->frame_shoot = (p->frame_shoot + 1) % NUM_FRAMES_SHOOT;  // Cicla entre 0-1
        }
    }

    // Atualiza posição do jogador
    p->x = 100; // Mantém posição X fixa na tela
    p->player_pos_mundo_x += p->vel_x;  // Atualiza posição no mundo
    p->y += p->vel_y;                   // Atualiza posição vertical

    // Aplica gravidade se estiver no ar
    if (p->y < (ALTURA_CHAO - ALTURA_SPRITE)) 
        p->vel_y += GRAVIDADE;  // (queda)
    else 
    {
        // Limita a posição Y ao chão
        p->y = ALTURA_CHAO - ALTURA_SPRITE;
        p->vel_y = 0;           // Zera velocidade vertical
        can_jump = true;        // Permite pular novamente
    }

    // Permite novo pulo quando a tecla é solta
    if (!(al_key_down(&keyState, ALLEGRO_KEY_SPACE) || al_key_down(&keyState, ALLEGRO_KEY_W)))
        can_jump = true;

    // --- LÓGICA DE DANO POR QUEIMADURA (DoT) ---
    const int DANO_QUEIMADURA = 2;
    const int INTERVALO_TICK_QUEIMADURA = 30; // Dano a cada meio segundo (a 60 FPS)

    if (p->burn_timer > 0)
    {
        p->burn_timer--; // Decrementa a duração total do efeito a cada frame
        p->burn_tick_timer++; // Incrementa o timer do tick

        // Verifica se é hora de aplicar o dano do tick
        if (p->burn_tick_timer >= INTERVALO_TICK_QUEIMADURA)
        {
            p->vida -= DANO_QUEIMADURA;
            p->burn_tick_timer = 0; // Reseta o timer do tick para a próxima contagem
            printf("Queimando! Vida atual: %d\n", p->vida);
        }

        // Se o timer zerar, o efeito acaba
        if (p->burn_timer == 0)
        {
            printf("Efeito de queimadura terminou.\n");
        }
    }

    // Atualiza projéteis e verifica colisão com inimigos/boss
    for (int i = 0; i < MAX_PROJECTILES; i++) 
    {
        if (p->projeteis[i].ativo) 
        {
            update_projectile(&p->projeteis[i]);  // Atualiza posição do projétil
            
            // Obtém hitbox do projétil
            Hitbox proj_hb = get_projectile_hitbox(&p->projeteis[i], 1);

            bool colidiu = false;  // Flag para evitar colisão múltipla

            // Verifica colisão com o boss
            if (p->projeteis[i].ativo && boss->vida > 0) 
            {
                // Obtém hitbox do Boss
                Hitbox boss_hb = get_boss_hitbox(boss);
                if (colisao_retangulos(proj_hb.x, proj_hb.y, proj_hb.w, proj_hb.h,
                                        boss_hb.x, boss_hb.y, boss_hb.w, boss_hb.h)) 
                {
                    boss->vida -= 10;                  // Reduz vida do boss
                    p->projeteis[i].ativo = false;     // Desativa projétil
                    printf("Boss atingido! Vida restante: %d\n", boss->vida);
                    colidiu = true;                    // Marca como colidido

                    // Verifica se o boss morreu
                    if (boss->vida <= 0)
                    {
                        boss->morto = true;
                        printf("Boss derrotado!\n\n");
                    }
                }
            }

            // Verifica colisão com inimigos (apenas se não colidiu com o boss)
            if (!colidiu) 
            {
                for (int j = 0; j < MAX_INIMIGOS; j++) 
                {
                    if (enemies[j].ativo) 
                    {
                        // Obtém hitbox do inimigo
                        Hitbox enemy_hb = get_enemy_hitbox(&enemies[j]);
                        
                        if (colisao_retangulos(
                            proj_hb.x, proj_hb.y, proj_hb.w, proj_hb.h,
                            enemy_hb.x, enemy_hb.y, enemy_hb.w, enemy_hb.h)) 
                        {
                            enemies[j].vida = enemies[j].vida  - 10;  // Reduz vida do inimigo
                            p->projeteis[i].ativo = false;            // Desativa projétil
                            printf("Inimigo atingido! Vida restante: %d\n", enemies[j].vida);
                            
                            // Verifica se inimigo morreu
                            if (enemies[j].vida <= 0) 
                            {
                                enemies[j].ativo = false;
                                printf("Inimigo derrotado!\n\n");
                            }
                            break;  // Sai do loop após acertar um inimigo
                        }
                    }
                }
            }
            // Desativa projétil se sair da tela
            if (p->projeteis[i].x < 0 || p->projeteis[i].x > TELA_LARGURA)
                p->projeteis[i].ativo = false;
        }
    }
}


//============================================================================


/**
 * @brief - Desenha o jogador na tela de acordo com seu estado atual
 * 
 * @param p - Ponteiro para a estrutura Player a ser desenhada
 */
void draw_player(Player *p) 
{
    ALLEGRO_BITMAP *sprite = NULL;  // Ponteiro para o sprite atual

    // Seleciona o sprite baseado no estado atual
    switch (p->estado) 
    {
        case STAND_AND_STOP:
            sprite = p->sprite_stand_and_stop;  // Sprite parado
            break;

        case STAND_AND_SHOT:
            sprite = p->sprite_shoot[p->frame_shoot];  // Sprite atirando em pé (usa frame atual)
            break;

        case WALK:
            sprite = p->sprite_run[p->frame_andar];  // Sprite andando (usa frame atual)
            break;

        case JUMP:
            sprite = p->sprite_jump;  // Sprite pulando
            break;

        case JUMP_AND_SHOT:
            sprite = p->sprite_jump_and_shot;  // Sprite pulando e atirando
            break;

        case CROUCH:
            sprite = p->sprite_crouch;  // Sprite agachado
            break;

        case CROUCH_AND_SHOT:
            sprite = p->sprite_crouch_and_shot[p->frame_shoot];  // Sprite agachado e atirando (usa frame atual)
            break;

        default:
            sprite = p->sprite_stand_and_stop;  // Sprite padrão (fallback)
            break;
    }

    if (sprite) 
    {
        float escala = 3.5;
        float sw = al_get_bitmap_width(sprite);
        float sh = al_get_bitmap_height(sprite);
        float dw = sw * escala;
        float dh = sh * escala;
        int flip = p->olhando_para_direita ? 0 : ALLEGRO_FLIP_HORIZONTAL;

        // 1. Desenha o sprite normal do jogador
        al_draw_scaled_bitmap(
            sprite,
            0, 0, sw, sh,
            p->x, p->y, dw, dh,
            flip
        );

        // 3. Desenha todos os projéteis ativos do jogador
        for (int i = 0; i < MAX_PROJECTILES; i++)
            draw_projectile(&p->projeteis[i]);
    }
}


//============================================================================


/**
 * @brief - Libera a memória alocada para os sprites e projéteis do jogador
 * 
 * @param p - Ponteiro para a estrutura Player a ser destruída
 */
void destroy_player(Player *p) 
{
    printf("Destruindo jogador...\n");

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

    // Destrói os frames de tiro em pé
    for (int i = 0; i < 2; i++) 
        if (p->sprite_shoot[i])
            al_destroy_bitmap(p->sprite_shoot[i]);

    // Destrói os frames de tiro agachado
    for (int i = 0; i < 2; i++) 
        if (p->sprite_crouch_and_shot[i])
            al_destroy_bitmap(p->sprite_crouch_and_shot[i]);

    printf("Jogador destruído com sucesso!\n\n");

    // Destrói todos os projéteis
    printf("Destruindo projéteis...\n");
    for (int i = 0; i < MAX_PROJECTILES; i++)
        destroy_projectile(&p->projeteis[i]);
    printf("Projéteis destruídos!\n\n");
}


//============================================================================ 