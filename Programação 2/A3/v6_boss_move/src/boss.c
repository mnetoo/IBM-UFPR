#include "includes.h"

// Estado atual do Boss
static BossState boss_state = BURN;

//==============================================================================


/**
 * @brief - Função que inicializa o Boss
 * 
 * @param b - Ponteiro para a estrutura Boss
 * @param pos_x - posição do boss
 */
void init_boss(Boss *b, float pos_x) 
{
    printf("Inicializando Boss...\n");

    b->x = pos_x;
    b->y = 200;
    b->vel_x = 0; // Começa parado, o movimento será definido em update_boss
    b->vel_y = 0; // Não se move verticalmente
    b->vida = 400;

    b->frame_atual = 0;
    b->timer_animacao = 0;
    
    // Inicializa os timers do ataque especial
    b->special_attack_cooldown_timer = 0;
    b->special_attack_phase_timer = 0;

    b->olhando_para_direita = false; // Começa olhando para a esquerda

    b->morto = false;

    // Carrega sprites idle
    for (int i = 0; i < NUM_FRAMES_IDLE; i++) 
    {
        char filename[100];
        sprintf(filename, "./assets/enemies/boss/Fire-Skull-Files/Sprites/NoFire/frame%d.png", i + 1);
        b->idle[i] = al_load_bitmap(filename);
        
        if (!b->idle[i])
            fprintf(stderr, "Erro ao carregar sprite idle: %s\n", filename);
    }
    
    // Carrega sprites burn
    for (int i = 0; i < NUM_FRAMES_BURN; i++) 
    {
        char filename[100];
        sprintf(filename, "./assets/enemies/boss/Fire-Skull-Files/Sprites/Fire/frame%d.png", i + 1);
        b->burn[i] = al_load_bitmap(filename);
    
        if (!b->burn[i])
            fprintf(stderr, "Erro ao carregar sprite burn: %s\n", filename);
    }

    // Carrega sprites de ataque
    for (int i = 0; i < NUM_FRAMES_PROJ; i++) 
    {
        char filename[100];
        sprintf(filename, "./assets/enemies/Hell-Beast-Files/Fireball/Sprites/frame%d.png", i + 1);
        b->ataque[i] = al_load_bitmap(filename);
    
        if (!b->ataque[i])
            fprintf(stderr, "Erro ao carregar sprite ataque: %s\n", filename);
    }

    boss_state = BURN;
    b->tempo_tiro = 0;

    // Inicializa projéteis
    for (int i = 0; i < MAX_BOSS_PROJECTILES; i++) 
    {
        b->projeteis[i].ativo = false;
        b->projeteis[i].frame_atual = 0;
        b->projeteis[i].timer_animacao = 0;
    }

    printf("Boss inicializado com sucesso.\n\n");
}


//==============================================================================


/**
 * @brief - Dispara uma "parede" vertical de projéteis.
 * 
 * @param b - Ponteiro para a estrutura Boss
 */
void boss_shoot_wall(Boss *b)
{
    if(b->morto) return;

    const int NUM_PROJETEIS_PAREDE = 6; // Quantos tiros na parede vertical
    const float ESPACAMENTO_VERTICAL = 50.0f; // Espaço entre cada tiro
    const float VELOCIDADE_PAREDE = -15.0f; // Velocidade horizontal dos tiros
    float y_inicial = 200.0f; // Posição Y do tiro mais alto

    for (int i = 0; i < NUM_PROJETEIS_PAREDE; i++)
    {
        // Encontra um projétil inativo (vamos precisar de muitos projéteis disponíveis!)
        for (int j = 0; j < MAX_BOSS_PROJECTILES; j++)
        {
            if (!b->projeteis[j].ativo)
            {
                b->projeteis[j].x = b->pos_mundo_x + 100;
                b->projeteis[j].y = y_inicial + (i * ESPACAMENTO_VERTICAL);
                
                // Estes tiros não são teleguiados, têm velocidade fixa
                b->projeteis[j].vel_x = VELOCIDADE_PAREDE;
                b->projeteis[j].vel_y = 0;
                
                b->projeteis[j].ativo = true;
                b->projeteis[j].frame_atual = 0;
                b->projeteis[j].timer_animacao = 0;
                break;
            }
        }
    }
}


//==============================================================================


/**
 * @brief - Função que atira projétil do Boss
 * 
 * @param b - Ponteiro para a estrutura Boss
 */
void boss_shoot_projectile(Boss *b) 
{
    if(b->morto) return;

    int ajuste = 0;
    if (boss_state == IDLE)
        ajuste = 170;
    else
        ajuste = 300;

    for (int i = 0; i < MAX_BOSS_PROJECTILES; i++) 
    {
        if (!b->projeteis[i].ativo) 
        {
            b->projeteis[i].x = b->pos_mundo_x + 100;
            b->projeteis[i].y = b->y + ajuste;
            b->projeteis[i].vel_x = 0;
            b->projeteis[i].vel_y = 0;
            b->projeteis[i].ativo = true;
            b->projeteis[i].frame_atual = 0;
            b->projeteis[i].timer_animacao = 0;
            break;
        }
    }
}  


//==============================================================================


/**
 * @brief - Gerencia a lógica de estados, animação e ataques do Boss.
 * 
 * @param b - Ponteiro para a estrutura Boss
 * @param player_mundo - deslocamento do player no mundo
 * @param p - Ponteiro para a estrutura Player 
 */
void update_boss(Boss *b, float player_mundo, Player *p) 
{
    if (b->morto) return;

    const float VELOCIDADE_MOVIMENTO_BOSS = 2.5f;
    const int COOLDOWN_ATAQUE_ESPECIAL = 500; // A cada 10 segundos (a 60 FPS)
    const int DURACAO_AVISO = 90;             // 1.5 segundos de aviso
    const int DURACAO_ATAQUE_ESPECIAL = 120;  // Ataque especial dura 2 segundos
    const int COOLDOWN_TIRO_NORMAL = 90;      // Cooldown para o tiro teleguiado normal

    // Parâmetros do projétil teleguiado
    const float VELOCIDADE_PROJETIL_BOSS = 11.0f;
    const float FATOR_DE_CURVA = 0.02f;

    // Parâmetros do dano de queimadura
    const int DANO_IMPACTO_BOSS = 5;
    const int DURACAO_QUEIMADURA_FRAMES = 180;

    if(p->olhando_para_direita)
        b->olhando_para_direita = false;
    else
        b->olhando_para_direita = true;

    // 1. Calcular a direção horizontal para o jogador
    float distancia_x = p->player_pos_mundo_x - b->x;

    // 2. Definir a direção que o boss está olhando (sempre encara o jogador)
    b->olhando_para_direita = (distancia_x > 0);
    
    // 3. Lógica de movimento (só se move se não estiver no meio de um ataque especial)
    if (boss_state != TELEGRAPH && boss_state != SPECIAL_ATTACK)
    {
        // Se o jogador está à direita, move para a direita.
        if (distancia_x > 5)// Adicionamos uma pequena margem para evitar "tremer"
            b->vel_x = VELOCIDADE_MOVIMENTO_BOSS;
        // Se o jogador está à esquerda, move para a esquerda.
        else if (distancia_x < -5)
            b->vel_x = -VELOCIDADE_MOVIMENTO_BOSS;
        // Se estiverem muito próximos, para.
        else
            b->vel_x = 0;
        
        // Aplica o movimento na posição de mundo
        b->x += b->vel_x;
    }
    else // Se estiver em um ataque especial, ele para no lugar
        b->vel_x = 0;

    // Atualiza a posição do Boss na tela (necessário para desenhar e atirar)
    b->pos_mundo_x = b->x - player_mundo;

    //  Máquina de estados do boss
    switch(boss_state)
    {
        case BURN:
        case IDLE:

            boss_state = (b->vida > 200) ? BURN : IDLE;
            if (boss_state == IDLE) b->y = 330;
            b->tempo_tiro++;
            if (b->tempo_tiro >= COOLDOWN_TIRO_NORMAL) 
            {
                boss_shoot_projectile(b);
                b->tempo_tiro = 0;
            }

            b->special_attack_cooldown_timer++;
            if (b->special_attack_cooldown_timer >= COOLDOWN_ATAQUE_ESPECIAL) 
            {
                boss_state = TELEGRAPH;
                b->special_attack_phase_timer = 0;
            }
            break;

        case TELEGRAPH:

            b->special_attack_phase_timer++;
            if (b->special_attack_phase_timer >= DURACAO_AVISO) 
            {
                boss_state = SPECIAL_ATTACK;
                b->special_attack_phase_timer = 0;
                boss_shoot_wall(b);
            }
            break;

        case SPECIAL_ATTACK:

            b->special_attack_phase_timer++;
            if (b->special_attack_phase_timer % 30 == 0)
                boss_shoot_wall(b);

            if (b->special_attack_phase_timer >= DURACAO_ATAQUE_ESPECIAL) 
            {
                b->special_attack_cooldown_timer = 0;
                boss_state = (b->vida > 200) ? BURN : IDLE;
            }
            break;
    }

    // Atualiza a animação do Boss
    b->timer_animacao++;
    if (b->timer_animacao >= 10) 
    {
        // Animação BURN para todos os estados de ataque, IDLE apenas quando estiver com pouca vida
        int max_frames = (boss_state == IDLE) ? NUM_FRAMES_IDLE : NUM_FRAMES_BURN;
        b->frame_atual = (b->frame_atual + 1) % max_frames;
        b->timer_animacao = 0;
    }

    Hitbox hitbox_jogador = get_playerBoss_hitbox(p);
    float target_x = hitbox_jogador.x + hitbox_jogador.w / 2;
    float target_y = hitbox_jogador.y + hitbox_jogador.h / 2;

    for (int i = 0; i < MAX_BOSS_PROJECTILES; i++) 
    {
        if (b->projeteis[i].ativo)
        {
            // Os tiros da parede têm vel_y=0, então a lógica teleguiada não os afeta.
            // Os tiros teleguiados têm vel_y=0 inicialmente, então a lógica os assume.
            
            // SE O PROJÉTIL NÃO TEM VELOCIDADE HORIZONTAL INICIAL, ELE É TELEGUIDADO.
            if(b->projeteis[i].vel_x == 0 && b->projeteis[i].vel_y == 0)
            {
                // Copiado da sua função original - lógica do projétil com curva
                float target_dir_x = target_x - b->projeteis[i].x;
                float target_dir_y = target_y - b->projeteis[i].y;
                float distancia = sqrt(target_dir_x * target_dir_x + target_dir_y * target_dir_y);
                if (distancia > 0) { target_dir_x /= distancia; target_dir_y /= distancia; }

                float vel_mag_atual = sqrt(b->projeteis[i].vel_x * b->projeteis[i].vel_x + b->projeteis[i].vel_y * b->projeteis[i].vel_y);
                float dir_atual_x = (vel_mag_atual > 0) ? b->projeteis[i].vel_x / vel_mag_atual : target_dir_x;
                float dir_atual_y = (vel_mag_atual > 0) ? b->projeteis[i].vel_y / vel_mag_atual : target_dir_y;

                dir_atual_x += (target_dir_x - dir_atual_x) * FATOR_DE_CURVA;
                dir_atual_y += (target_dir_y - dir_atual_y) * FATOR_DE_CURVA;

                float dir_final_mag = sqrt(dir_atual_x * dir_atual_x + dir_atual_y * dir_atual_y);
                if (dir_final_mag > 0) {
                    b->projeteis[i].vel_x = (dir_atual_x / dir_final_mag) * VELOCIDADE_PROJETIL_BOSS;
                    b->projeteis[i].vel_y = (dir_atual_y / dir_final_mag) * VELOCIDADE_PROJETIL_BOSS;
                }
            }
            
            // Mover o projétil
            b->projeteis[i].x += b->projeteis[i].vel_x;
            b->projeteis[i].y += b->projeteis[i].vel_y;

            // Animação do projétil
            b->projeteis[i].timer_animacao++;
            if (b->projeteis[i].timer_animacao >= 5) 
            {
                b->projeteis[i].frame_atual = (b->projeteis[i].frame_atual + 1) % NUM_FRAMES_PROJ;
                b->projeteis[i].timer_animacao = 0;
            }

            // Verificação de colisão (funciona para ambos os tipos)
            Hitbox hitbox_proj = get_projectile_hitbox(&(b->projeteis[i]), 1);
            if (colisao_retangulos(hitbox_jogador.x, hitbox_jogador.y, hitbox_jogador.w, hitbox_jogador.h,
                                hitbox_proj.x, hitbox_proj.y, hitbox_proj.w, hitbox_proj.h)) 
            {
                p->vida -= DANO_IMPACTO_BOSS;
                p->burn_timer = DURACAO_QUEIMADURA_FRAMES;
                b->projeteis[i].ativo = false;
                printf("Jogador atingido e QUEIMANDO! Vida: %d\n", p->vida);
            }

            // Desativa se sair da tela
            if (b->projeteis[i].x < -50 || b->projeteis[i].x > 1300)
                b->projeteis[i].ativo = false;
        }
    }
}


//==============================================================================


/**
 * @brief - Desenha o Boss e seus projéteis, considerando a direção (flip).
 * 
 * @param b - Ponteiro para a estrutura Boss
 */
void draw_boss(Boss *b, Player *p) 
{
    if (!b || b->morto) return;

    ALLEGRO_BITMAP *sprite_atual = NULL;

    if (boss_state == IDLE && b->frame_atual < NUM_FRAMES_IDLE) {
        sprite_atual = b->idle[b->frame_atual];
    } 
    else if ((boss_state == BURN || boss_state == TELEGRAPH || boss_state == SPECIAL_ATTACK) && b->frame_atual < NUM_FRAMES_BURN) {
        sprite_atual = b->burn[b->frame_atual];
    }

    if (sprite_atual) 
    {
        float escala = 4;
        int flip = p->olhando_para_direita ? 0 : 0;

        al_draw_scaled_bitmap(
            sprite_atual,
            0, 0,
            al_get_bitmap_width(sprite_atual),
            al_get_bitmap_height(sprite_atual),
            b->pos_mundo_x,
            b->y,
            al_get_bitmap_width(sprite_atual) * escala,
            al_get_bitmap_height(sprite_atual) * escala,
            flip // <<< USA A VARIÁVEL FLIP CORRIGIDA AQUI
        );
    }

    // Desenha os projéteis
    for (int i = 0; i < MAX_BOSS_PROJECTILES; i++) 
    {
        if (b->projeteis[i].ativo) 
        {
            int frame = b->projeteis[i].frame_atual;
            if (frame >= 0 && frame < NUM_FRAMES_PROJ && b->ataque[frame] != NULL) 
            {
                float escala_proj = 3.5;
                al_draw_scaled_bitmap(
                    b->ataque[frame],
                    0, 0,
                    al_get_bitmap_width(b->ataque[frame]),
                    al_get_bitmap_height(b->ataque[frame]),
                    b->projeteis[i].x,
                    b->projeteis[i].y,
                    al_get_bitmap_width(b->ataque[frame]) * escala_proj,
                    al_get_bitmap_height(b->ataque[frame]) * escala_proj,
                    0
                );
            }
        }
    }
}


//==============================================================================


/**
 * @brief - Função que destróis Boss
 * 
 * @param b - Ponteiro para a estrutura Boss
 */
void destroy_boss(Boss *b) 
{
    printf("Destruindo Boss...\n");

    for (int i = 0; i < 4; i++) 
    {
        if (b->idle[i]) 
        {
            al_destroy_bitmap(b->idle[i]);
            b->idle[i] = NULL;
        }
    }

    for (int i = 0; i < 8; i++) 
    {
        if (b->burn[i]) 
        {
            al_destroy_bitmap(b->burn[i]);
            b->burn[i] = NULL;
        }
    }

    for (int i = 0; i < 3; i++) 
    {
        if (b->ataque[i]) 
        {
            al_destroy_bitmap(b->ataque[i]);
            b->ataque[i] = NULL;
        }
    }

    printf("Boss foi destruído com sucesso.\n\n");
}


//==============================================================================