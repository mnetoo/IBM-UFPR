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
    b->vel_x = -2;
    b->vel_y = -2;
    b->vida = 400;

    b->frame_atual = 0;
    b->timer_animacao = 0;

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
 * @brief - Função de animação do Boss e lógica de seus projéteis teleguiados com curva.
 * 
 * @param b - Ponteiro para a estrutura Boss
 * @param player_mundo - deslocamento do player no mundo
 * @param p - Ponteiro para a estrutura Player
 */
void update_boss(Boss *b, float player_mundo, Player *p) 
{
    // ... (toda a sua lógica de atualização de posição, estado e animação do Boss continua aqui) ...
    // Atualiza posição mundial
    b->pos_mundo_x = b->x - player_mundo;

    // Muda estado apenas conforme vida
    if (b->vida > 100)
        boss_state = BURN;
    else
    {
        boss_state = IDLE;
        b->y = 330;
    }

    // Atualiza animação
    b->timer_animacao++;
    if (b->timer_animacao >= 10) 
    {
        int max_frames = (boss_state == BURN) ? NUM_FRAMES_BURN : NUM_FRAMES_IDLE;
        b->frame_atual = (b->frame_atual + 1) % max_frames;
        b->timer_animacao = 0;
    }

    // Controle de tiros
    b->tempo_tiro++;
    if (b->tempo_tiro >= BOSS_SHOOT_COOLDOWN) 
    {
        boss_shoot_projectile(b);
        b->tempo_tiro = 0;
    }

    // --- LÓGICA DE ATUALIZAÇÃO DOS PROJÉTEIS ---

    Hitbox hitbox_jogador = get_playerBoss_hitbox(p);
    float target_x = hitbox_jogador.x + hitbox_jogador.w / 2;
    float target_y = hitbox_jogador.y + hitbox_jogador.h / 2;
    
    // --- PARÂMETROS DE AJUSTE PARA O PROJÉTIL ---
    const float VELOCIDADE_PROJETIL_BOSS = 11.0f; // Pode ser um pouco mais rápido agora que tem curva
    const float FATOR_DE_CURVA = 0.02f;         // Quanto MENOR, mais lenta a curva (mais fácil de desviar)
                                                // Valores bons para testar: 0.02, 0.05, 0.1

    const int DANO_IMPACTO_BOSS = 5;
    const int DURACAO_QUEIMADURA_FRAMES = 180; // 3 segundos a 60 FPS

    // Atualiza projéteis
    for (int i = 0; i < MAX_BOSS_PROJECTILES; i++) 
    {
        if (b->projeteis[i].ativo)
        {
            // ===== INÍCIO DA LÓGICA DO PROJÉTIL COM CURVA SUAVE =====

            // 1. Calcular a direção DESEJADA (direto para o jogador)
            float target_dir_x = target_x - b->projeteis[i].x;
            float target_dir_y = target_y - b->projeteis[i].y;
            
            // 2. Normalizar a direção desejada para ter comprimento 1
            float distancia = sqrt(target_dir_x * target_dir_x + target_dir_y * target_dir_y);
            if (distancia > 0) {
                target_dir_x /= distancia;
                target_dir_y /= distancia;
            }

            // 3. Obter a direção ATUAL do projétil
            float vel_mag_atual = sqrt(b->projeteis[i].vel_x * b->projeteis[i].vel_x + b->projeteis[i].vel_y * b->projeteis[i].vel_y);
            float dir_atual_x = (vel_mag_atual > 0) ? b->projeteis[i].vel_x / vel_mag_atual : target_dir_x; // Se parado, aponta para o alvo
            float dir_atual_y = (vel_mag_atual > 0) ? b->projeteis[i].vel_y / vel_mag_atual : target_dir_y; // Se parado, aponta para o alvo

            // 4. Interpolar suavemente da direção ATUAL para a DESEJADA
            dir_atual_x += (target_dir_x - dir_atual_x) * FATOR_DE_CURVA;
            dir_atual_y += (target_dir_y - dir_atual_y) * FATOR_DE_CURVA;

            // 5. Renormalizar a nova direção para manter a velocidade constante e definir a velocidade final
            float dir_final_mag = sqrt(dir_atual_x * dir_atual_x + dir_atual_y * dir_atual_y);
            if (dir_final_mag > 0) {
                b->projeteis[i].vel_x = (dir_atual_x / dir_final_mag) * VELOCIDADE_PROJETIL_BOSS;
                b->projeteis[i].vel_y = (dir_atual_y / dir_final_mag) * VELOCIDADE_PROJETIL_BOSS;
            }
            
            // ===== FIM DA LÓGICA DO PROJÉTIL COM CURVA SUAVE =====
            
            // 6. Mover o projétil
            b->projeteis[i].x += b->projeteis[i].vel_x;
            b->projeteis[i].y += b->projeteis[i].vel_y;

            // ... (O resto do código: animação do projétil, colisão e sair da tela) ...
            b->projeteis[i].timer_animacao++;
            if (b->projeteis[i].timer_animacao >= 5) 
            {
                b->projeteis[i].frame_atual = (b->projeteis[i].frame_atual + 1) % NUM_FRAMES_PROJ;
                b->projeteis[i].timer_animacao = 0;
            }

            Hitbox hitbox_proj = get_projectile_hitbox(&(b->projeteis[i]), 1);

            if (colisao_retangulos(hitbox_jogador.x, hitbox_jogador.y, hitbox_jogador.w, hitbox_jogador.h,
                                hitbox_proj.x, hitbox_proj.y, hitbox_proj.w, hitbox_proj.h)) 
            {
                // ---- LÓGICA DE COLISÃO ATUALIZADA ----
                p->vida -= DANO_IMPACTO_BOSS;       // Aplica um dano de impacto menor
                p->burn_timer = DURACAO_QUEIMADURA_FRAMES; // Inicia o timer da queimadura
                
                b->projeteis[i].ativo = false;      // Desativa o projétil
                printf("Jogador atingido e QUEIMANDO! Vida: %d\n", p->vida);
            }

            if (b->projeteis[i].x < -50 || b->projeteis[i].x > 1300)
                b->projeteis[i].ativo = false;
        }
    }
}


//==============================================================================


/**
 * @brief - Desenha o Boss e projéteis
 * 
 * @param b - Ponteiro para a estrutura Boss
 */
void draw_boss(Boss *b) 
{
    if (!b) return;

    if(b->morto) return;

    // Determina qual sprite usar (IDLE ou BURN)
    ALLEGRO_BITMAP *sprite_atual = NULL;
    if (boss_state == IDLE && b->frame_atual < NUM_FRAMES_IDLE) 
    {
        sprite_atual = b->idle[b->frame_atual];
    } 
    else if (boss_state == BURN && b->frame_atual < NUM_FRAMES_BURN)
    {
        sprite_atual = b->burn[b->frame_atual];
    }

    // Desenha o boss
    if (sprite_atual) 
    {
        float escala = 4;
        al_draw_scaled_bitmap(
            sprite_atual,
            0, 0,
            al_get_bitmap_width(sprite_atual),
            al_get_bitmap_height(sprite_atual),
            b->pos_mundo_x,
            b->y,
            al_get_bitmap_width(sprite_atual) * escala,
            al_get_bitmap_height(sprite_atual) * escala,
            0
        );
    }

    // Desenha os projéteis (mantido igual)
    for (int i = 0; i < MAX_BOSS_PROJECTILES; i++) 
    {
        if (b->projeteis[i].ativo) 
        {
            int frame = b->projeteis[i].frame_atual;
            if (frame >= 0 && frame < NUM_FRAMES_PROJ && b->ataque[frame] != NULL) 
            {
                float escala_proj = 5;
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