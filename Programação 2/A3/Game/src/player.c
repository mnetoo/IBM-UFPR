#include "includes.h"


//============================================================================


// Função para iniciar o player
void init_player(Player *p) 
{
    printf("Inicializando jogador...\n");

    // Inicialização das propriedades básicas do jogador
    p->x = POSICAO_INICIAL_X;  // Posição X inicial definida por constante
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
    p->sprite_stand_and_shot = al_load_bitmap("./assets/player/space-marine/Sprites/Shoot/sprites/shoot1.png");
    p->sprite_crouch = al_load_bitmap("./assets/player/space-marine/Sprites/Crouch/sprites/crouch3.png");
    p->sprite_jump = al_load_bitmap("./assets/player/space-marine/Sprites/Jump/sprites/jump2.png");
    
    // Carrega os 10 frames da animação de corrida
    for (int i = 0; i < 10; i++) 
    {
        char filename[100];
        sprintf(filename, "./assets/player/space-marine/Sprites/Run_Gun/sprites/run%d.png", i + 1);
        p->sprite_run[i] = al_load_bitmap(filename);
    }    

    // Verificação de erros no carregamento dos sprites
    if (!p->sprite_stand_and_stop) printf("Erro ao carregar stand_and_stop.png\n");
    if (!p->sprite_stand_and_shot) printf("Erro ao carregar stand_and_shot.png\n");
    if (!p->sprite_crouch) printf("Erro ao carregar crouch.png\n");
    if (!p->sprite_jump) printf("Erro ao carregar jump.png\n");

    for (int i = 0; i < 10; i++) 
        if(!p->sprite_run[i]) printf("Erro ao carregar sprites de corrida\n");

    printf("Jogador inicializado com sucesso...\n\n");
}


//============================================================================


// Função de atualização do estado do jogador a cada frame
void update_player(Player *p) 
{
    static bool can_jump = true;  // Controla se o jogador pode pular (evita pulo contínuo)
    const int FRAME_DELAY = 5;  // Atraso entre frames de animação

    // Obtém o estado atual do teclado
    ALLEGRO_KEYBOARD_STATE keyState;
    al_get_keyboard_state(&keyState);

    p->vel_x = 0;  // Reseta a velocidade horizontal a cada frame

    // Variáveis de estado auxiliares
    bool no_ar = (p->y < (ALTURA_CHAO - ALTURA_SPRITE));  // Verifica se o jogador está no ar
    bool esta_agachado = al_key_down(&keyState, ALLEGRO_KEY_DOWN);  // Verifica se a tecla para baixo está pressionada

    // AGACHAR
    // Agachar tem prioridade sobre outros estados quando no chão
    if (!no_ar && esta_agachado)
    {
        p->estado = p->olhando_para_direita ? CROUCH : CROUCH;  // Mantém a direção mas usa o mesmo sprite
        p->vel_x = 0;  // Impede movimento enquanto agachado
        return;  // Sai da função - nada mais é processado enquanto agachado
    }

    // MOVIMENTO HORIZONTAL
    if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT)) 
    {
        p->vel_x = VELOCIDADE;  // Move para direita
        p->olhando_para_direita = true;  // Atualiza direção

        // Define o estado baseado se está no ar ou não
        if (no_ar)
            p->estado = JUMP;  // Mantém estado de pulo se estiver no ar
        else 
        {
            p->estado = WALK;  // Estado de caminhada
            // Animação da caminhada
            p->timer_andar++;
            if (p->timer_andar >= FRAME_DELAY) 
            {
                p->timer_andar = 0;
                p->frame_andar = (p->frame_andar + 1) % 10;  // Cicla entre os 10 frames
            }
        }
    } 
    else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT)) 
    {
        p->vel_x = -VELOCIDADE;  // Move para esquerda (velocidade negativa)
        p->olhando_para_direita = false;  // Atualiza direção

        // Lógica idêntica ao movimento para direita
        if (no_ar)
            p->estado = JUMP;
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
    {  // Se não estiver se movendo e estiver no chão
        p->estado = STAND_AND_STOP;  // Estado parado
        p->frame_andar = 0;  // Reseta animação de caminhada
        p->timer_andar = 0;
    }

    // PULO (inicia apenas no chão)
    if (al_key_down(&keyState, ALLEGRO_KEY_SPACE) && can_jump && !no_ar && !esta_agachado) 
    {
        p->vel_y = PULO;  // Aplica velocidade vertical (pulo)
        p->estado = p->olhando_para_direita ? JUMP : JUMP;  // Estado de pulo
        can_jump = false;  // Impede pulos consecutivos
    }

    // Atualização da posição
    p->x = 100;  // Mantém X fixo na tela (o mundo se move ao redor)
    p->player_pos_mundo_x += p->vel_x;  // Atualiza posição no mundo
    p->y += p->vel_y;  // Atualiza posição vertical

    // GRAVIDADE E CHÃO
    if (p->y < (ALTURA_CHAO - ALTURA_SPRITE)) // Se estiver no ar
        p->vel_y += GRAVIDADE;  // Aplica gravidade
    else 
    {  // Se estiver no chão
        p->y = ALTURA_CHAO - ALTURA_SPRITE;  // Corrige posição para não afundar
        p->vel_y = 0;  // Zera velocidade vertical
        can_jump = true;  // Permite pular novamente

        // Se estava pulando e parou de se mover, volta para estado parado
        if ((p->estado == JUMP) && p->vel_x == 0)
            p->estado = STAND_AND_STOP;
    }

    // Libera pulo ao soltar espaço (permite novo pulo)
    if (!al_key_down(&keyState, ALLEGRO_KEY_SPACE))
        can_jump = true;

    // LIMITES DA TELA
    if (p->x < 0)
        p->x = 0;  // Impede sair pela esquerda
    else if (p->x > TELA_LARGURA - LARGURA_SPRITE)
        p->x = TELA_LARGURA - LARGURA_SPRITE;  // Impede sair pela direita
}


//============================================================================


//  Função para trocar as sprites do player
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
            sprite = p->sprite_stand_and_shot;  // Sprite atirando em pé
            break;

        case WALK:
            sprite = p->sprite_run[p->frame_andar];  // Usa o frame atual da animação de corrida
            break;

        case JUMP:
            sprite = p->sprite_jump;  // Sprite de pulo
            break;

        case CROUCH:
            sprite = p->sprite_crouch;  // Sprite agachado
            break;

        case CROUCH_AND_SHOT:
            sprite = p->sprite_crouch_and_shot;  // Sprite atirando agachado
            break;

        default:
            sprite = p->sprite_stand_and_stop;  // Fallback - sprite parado
            break;
    }

    // Se o sprite foi carregado corretamente
    if (sprite) 
    {
        float escala = 5;  // Fator de escala para aumentar o sprite
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
    }
}



//============================================================================


//  Função para destruir o player
void destroy_player(Player *p) 
{
    // Destrói todos os bitmaps carregados
    al_destroy_bitmap(p->sprite_stand_and_stop);
    al_destroy_bitmap(p->sprite_stand_and_shot);
    al_destroy_bitmap(p->sprite_crouch_and_shot);
    al_destroy_bitmap(p->sprite_crouch);
    al_destroy_bitmap(p->sprite_jump);

    // Destrói todos os frames da animação de corrida
    for (int i = 0; i < 10; i++) 
    {
        if (p->sprite_run[i])
            al_destroy_bitmap(p->sprite_run[i]);
    }
}



//============================================================================