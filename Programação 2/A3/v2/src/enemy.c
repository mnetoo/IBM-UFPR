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
void enemy_shoot_projectile(Enemy *e) 
{
    for (int i = 0; i < MAX_ENEMY_PROJECTILES; i++) 
    {
        if (!e->projeteis[i].ativo) 
        {
            e->projeteis[i].x = e->enemy_pos_mundo_x - 20;
            e->projeteis[i].y = 550;
            e->projeteis[i].vel_x = -20; // Tiro para esquerda
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

    e->enemy_pos_mundo_x = e->x - player_mundo;

    // Atualiza animação
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
        enemy_shoot_projectile(e);
        e->tempo_tiro = 0;
    }

    // Atualiza projéteis do inimigo e verifica colisão com jogador
    Hitbox player_hb = get_player_hitbox(player);
    
    for (int i = 0; i < MAX_ENEMY_PROJECTILES; i++) 
    {
        if (e->projeteis[i].ativo) 
        {
            e->projeteis[i].x += e->projeteis[i].vel_x;

            // Verifica colisão com jogador
            Hitbox proj_hb = get_projectile_hitbox(&e->projeteis[i], 1);
            
            if (colisao_retangulos(
                proj_hb.x, proj_hb.y, proj_hb.w, proj_hb.h,
                player_hb.x, player_hb.y, player_hb.w, player_hb.h)) 
            {
            
                player->vida = player->vida - 5;  // Reduz vida do jogador
                e->projeteis[i].ativo = false;  // Desativa projétil
                printf("Jogador atingido! Vida: %d\n", player->vida);
            }

            // Desativa se sair da tela
            if (e->projeteis[i].x < 0)
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
void inicializa_inimigos(Enemy inimigos[]) 
{
    printf("Inicializando inimigos...\n");

    int posicoes[MAX_INIMIGOS];  // Armazena posições x já utilizadas
    int count = 0;               // Contador de inimigos posicionados

    for (int i = 0; i < MAX_INIMIGOS; i++) 
    {
        int tentativa = 0;       // Contador de tentativas de posicionamento
        int pos_x;               // Posição x do inimigo atual
        
        // Tenta encontrar posição válida (com distância mínima de outros inimigos)
        do {
            pos_x = 500 + rand() % 3200;  // Gera posição aleatória entre 500 e 3700
            tentativa++;
        } while (!posicao_valida(pos_x, posicoes, count) && tentativa < 100);

        // Avisa se não encontrou posição válida
        if (tentativa == 100)
            printf("Aviso: não foi possível encontrar posição válida após 100 tentativas.\n");

        // Armazena a posição e inicializa o inimigo
        posicoes[count++] = pos_x;
        init_enemy(&inimigos[i], pos_x);
        printf("Posição do inimigo (%d): %d\n", i, pos_x);
    }

    printf("Inimigos inicializados com sucesso...\n\n");
}