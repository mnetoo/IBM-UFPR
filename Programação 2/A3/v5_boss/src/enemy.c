#include "includes.h"


//==============================================================================


/**
 * @brief - Função que inicializa um inimigo
 * 
 * @param e - Ponteiro para a estrutura Enemy
 * @param pox_x - valor para a posição do inimigo
 */
void init_enemy(Enemy *e, float pos_x) 
{
    e->x = pos_x;
    e->y = 420;
    e->vel_x = -2;
    e->vida = 20;
    e->ativo = true;

    e->frame_atual = 0;
    e->timer_animacao = 0;
    e->tempo_tiro = 0;

    for (int i = 0; i < 6; i++) 
    {
        char filename[100];
        sprintf(filename, "./assets/enemies/enemy-ghost/Sprites/Particles/frame%d.png", i + 1);
        e->sprite[i] = al_load_bitmap(filename);
        if (!e->sprite[i]) 
            printf("Erro ao carregar sprite %d do inimigo\n", i);
    }

    for (int i = 0; i < MAX_ENEMY_PROJECTILES; i++) 
        e->projeteis[i].ativo = false;
}


//==============================================================================


/**
 * @brief - Função para o tiro/projétil
 * 
 * @param e - Ponteiro para a estrutura Enemy
 */
/**
 * @brief - Ativa um projétil na posição do inimigo.
 * 
 * @param e - Ponteiro para a estrutura Enemy
 */
void enemy_shoot_projectile(Enemy *e) 
{
    for (int i = 0; i < MAX_ENEMY_PROJECTILES; i++) 
    {
        if (!e->projeteis[i].ativo) 
        {
            // Posição inicial do projétil (centro do inimigo)
            float start_x = e->enemy_pos_mundo_x + (al_get_bitmap_width(e->sprite[e->frame_atual]) * 3.5) / 2;
            float start_y = e->y + (al_get_bitmap_height(e->sprite[e->frame_atual]) * 3.5) / 2;

            e->projeteis[i].x = start_x;
            e->projeteis[i].y = start_y;
            
            // A velocidade será calculada a cada frame, então podemos inicializá-la como 0
            e->projeteis[i].vel_x = 0; 
            e->projeteis[i].vel_y = 0;

            e->projeteis[i].ativo = true;
            break; 
        }
    }
}


//==============================================================================


/**
 * @brief - Função de movimentação de inimigo
 * 
 * @param e - Ponteiro para a estrutura Enemy
 * @param player_mundo - deslocamento do player
 * @param player - Ponteiro para a estrutura Player
 */
void update_enemy(Enemy *e, float player_mundo, Player *player) 
{
    if (!e->ativo) return;

    // Velocidade do projétil teleguiado
    const float VELOCIDADE_PROJETIL = 13.0f;

    e->enemy_pos_mundo_x = e->x - player_mundo;

    e->timer_animacao++;
    if (e->timer_animacao >= 10) 
    {
        e->timer_animacao = 0;
        e->frame_atual = (e->frame_atual + 1) % 6;
    }

    // Timer simples de tiro
    e->tempo_tiro++;
    if (e->tempo_tiro >= 240) 
    {
        // A função de tiro agora é mais simples
        enemy_shoot_projectile(e);
        e->tempo_tiro = 0;
    }

    // Atualiza projéteis do inimigo e verifica colisão com jogador
    Hitbox player_hb = get_player_hitbox(player);
    float target_x = player_hb.x + player_hb.w - 10 / 2; // Centro do jogador em X
    float target_y = player_hb.y + player_hb.h - 10/ 2; // Centro do jogador em Y
    
    for (int i = 0; i < MAX_ENEMY_PROJECTILES; i++) 
    {
        if (e->projeteis[i].ativo) 
        {
            const float FATOR_DE_CURVA = 0.04f; // Valor entre 0 e 1. Quanto menor, mais lenta a curva.

            //  Calcular o vetor de direção DESEJADO para o jogador
            float target_dir_x = target_x - e->projeteis[i].x;
            float target_dir_y = target_y - e->projeteis[i].y;

            //  Normalizar o vetor de direção desejado
            float distancia = sqrt(target_dir_x * target_dir_x + target_dir_y * target_dir_y);
            if (distancia > 0) 
            {
                target_dir_x /= distancia;
                target_dir_y /= distancia;
            }

            //  Interpolar a velocidade atual em direção à velocidade desejada
            float vel_atual_mag = sqrt(e->projeteis[i].vel_x * e->projeteis[i].vel_x + e->projeteis[i].vel_y * e->projeteis[i].vel_y);
            
            //  Normalizar a velocidade atual para obter apenas a direção atual
            float dir_atual_x = (vel_atual_mag > 0) ? e->projeteis[i].vel_x / vel_atual_mag : 0;
            float dir_atual_y = (vel_atual_mag > 0) ? e->projeteis[i].vel_y / vel_atual_mag : 0;

            // Se for o primeiro frame, aponta direto para o jogador
            if (vel_atual_mag == 0) 
            {
                dir_atual_x = target_dir_x;
                dir_atual_y = target_dir_y;
            }

            // Interpola a direção
            dir_atual_x += (target_dir_x - dir_atual_x) * FATOR_DE_CURVA;
            dir_atual_y += (target_dir_y - dir_atual_y) * FATOR_DE_CURVA;

            // Renormaliza a direção final para manter a velocidade constante
            float dir_final_mag = sqrt(dir_atual_x * dir_atual_x + dir_atual_y * dir_atual_y);
            if(dir_final_mag > 0) 
            {
                e->projeteis[i].vel_x = (dir_atual_x / dir_final_mag) * VELOCIDADE_PROJETIL;
                e->projeteis[i].vel_y = (dir_atual_y / dir_final_mag) * VELOCIDADE_PROJETIL;
            }

            //  Mover o projétil
            e->projeteis[i].x += e->projeteis[i].vel_x;
            e->projeteis[i].y += e->projeteis[i].vel_y;

            // Verifica colisão com jogador
            Hitbox proj_hb = get_projectile_hitbox(&e->projeteis[i], 1);
            
            if (colisao_retangulos(
                proj_hb.x, proj_hb.y, proj_hb.w, proj_hb.h,
                player_hb.x, player_hb.y, player_hb.w, player_hb.h)) 
            {
                player->vida = player->vida - 5;
                e->projeteis[i].ativo = false;
                printf("Jogador atingido! Vida: %d\n", player->vida);
            }

            // Desativa se sair da tela
            if (e->projeteis[i].x < -50 || e->projeteis[i].x > TELA_LARGURA + 50 || e->projeteis[i].y < -50 || e->projeteis[i].y > TELA_ALTURA + 50)
                e->projeteis[i].ativo = false;
        }
    }
}


//==============================================================================


/**
 * @brief - Carrega a sprite do inimigo
 * 
 * @param e - Ponteiro para a estrutura Enemy
*/
void draw_enemy(Enemy *e) 
{
    if (!e->ativo) return;

    float pos_x = e->enemy_pos_mundo_x;
    float pos_y = e->y;

    float escala = 3.5;
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

    for (int i = 0; i < MAX_ENEMY_PROJECTILES; i++) 
    {
        if (e->projeteis[i].ativo) 
        {
            al_draw_filled_circle(
                e->projeteis[i].x,
                e->projeteis[i].y,
                8,
                al_map_rgb(255, 0, 110)
            );
        }
    }
}


//==============================================================================


/**
 * @brief - Função que destrói inimigo
 * 
 * @param e - Ponteiro para a estrutura Enemy
*/
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

/**
 * @brief Verifica se a posição para um novo inimigo é válida (não muito próxima de outros)
 * 
 * @param nova_pos Posição x que está sendo testada para o novo inimigo
 * @param posicoes Vetor com as posições x dos inimigos já colocados
 * @param count Quantidade de inimigos já posicionados
 * @return true Se a posição é válida (distante o suficiente de outros inimigos)
 * @return false Se a posição é inválida (muito próxima de outro inimigo)
 */
bool posicao_valida(int nova_pos, int posicoes[], int count) 
{
    for (int i = 0; i < count; i++)
        if (abs(nova_pos - posicoes[i]) < DIST_MINIMA)
            return false;

    return true;
}

/**
 * @brief Inicializa todos os inimigos do jogo com posições aleatórias válidas
 * 
 * @param inimigos Array de inimigos a ser inicializado
 */
int inicializa_inimigos(Enemy inimigos[]) 
{
    printf("Inicializando inimigos...\n");

    int posicoes[MAX_INIMIGOS];
    int count = 0;
    int ultima_pos = 0;

    for (int i = 0; i < MAX_INIMIGOS; i++) 
    {
        int tentativa = 0;
        int pos_x;
        
        do {
            pos_x = 500 + rand() % 2800;
            tentativa++;
        } while (!posicao_valida(pos_x, posicoes, count) && tentativa < 100);

        if (tentativa == 100)
            printf("Aviso: não foi possível encontrar posição válida após 100 tentativas.\n");

        posicoes[count++] = pos_x;
        init_enemy(&inimigos[i], pos_x);
        printf("Posição do inimigo (%d): %d\n", i, pos_x);

        // Atualiza o maior valor encontrado
        if (pos_x > ultima_pos)
            ultima_pos = pos_x;
    }

    printf("Inimigos inicializados com sucesso...\n\n");
    return ultima_pos;
}