#include "includes.h"

//====================================================================================

/**
 * Inicializa a estrutura de background carregando a imagem e definindo propriedades
 * 
 * @param bg Ponteiro para a estrutura Background que será inicializada
 * @param caminho Caminho do arquivo de imagem a ser carregado
 */
void init_background(Background *bg, const char *caminho) 
{
    bg->imagem = al_load_bitmap(caminho);  // Carrega a imagem do background
    bg->scroll_x = 0;                      // Inicializa a posição de scroll
    bg->largura = al_get_bitmap_width(bg->imagem);  // Armazena largura da imagem
    bg->altura = al_get_bitmap_height(bg->imagem);  // Armazena altura da imagem
}

//====================================================================================

/**
 * Atualiza a posição de scroll do background baseado na posição do jogador
 * 
 * @param bg Ponteiro para a estrutura Background
 * @param player_pos_mundo_x Posição X atual do jogador no mundo do jogo
*/
void update_background(Background *bg, float player_pos_mundo_x)
{
    int centro_tela = TELA_LARGURA / 2;  // Calcula o centro da tela

    // Calcula a posição de scroll baseada na posição do jogador
    bg->scroll_x = player_pos_mundo_x - centro_tela;
    
    // Ajusta para looping quando ultrapassa o limite esquerdo
    if (bg->scroll_x < 0)
        bg->scroll_x += bg->largura;
}

//====================================================================================

/**
 * Desenha o background na tela com efeito de scroll e looping infinito
 * 
 * @param bg Ponteiro para a estrutura Background 
*/
void draw_background(Background *bg)
{
    if (!bg->imagem) return;  // Sai se não houver imagem carregada

    // Calcula o offset com tratamento para valores negativos e looping
    int offset = ((int)bg->scroll_x % bg->largura + bg->largura) % bg->largura;

    int sw = 300;               // Largura da porção do background a ser desenhada
    int sh = bg->altura;        // Altura do background
    int screen_w = TELA_LARGURA;  // Largura da tela
    int screen_h = TELA_ALTURA;   // Altura da tela

    // Caso 1: A porção a desenhar não ultrapassa o limite direito do background
    if (offset + sw <= bg->largura)
    {
        al_draw_scaled_bitmap(
            bg->imagem,
            offset, 0,        // Origem (x,y) na imagem fonte
            sw, sh,           // Largura e altura da porção fonte
            0, 0,            // Destino (x,y) na tela
            screen_w, screen_h,  // Largura e altura no destino
            0                // Flags (nenhuma)
        );
    }
    // Caso 2: A porção ultrapassa o limite e precisa ser desenhada em duas partes
    else
    {
        int primeira_parte = bg->largura - offset;  // Parte que vai do offset até o fim
        int segunda_parte = sw - primeira_parte;    // Parte restante do começo da imagem

        // Calcula a escala e largura para a primeira parte
        float escala1 = (float)primeira_parte / sw;
        float largura1 = escala1 * screen_w;

        // Calcula a escala e largura para a segunda parte
        float escala2 = (float)segunda_parte / sw;
        float largura2 = escala2 * screen_w;

        // Desenha a primeira parte (final da imagem)
        al_draw_scaled_bitmap(
            bg->imagem,
            offset, 0,
            primeira_parte, sh,
            0, 0,
            largura1, screen_h,
            0
        );

        // Desenha a segunda parte (início da imagem)
        al_draw_scaled_bitmap(
            bg->imagem,
            0, 0,
            segunda_parte, sh,
            largura1, 0,
            largura2, screen_h,
            0
        );
    }
}

//====================================================================================

/**
 * Libera os recursos alocados para o background
 * 
 * @param bg Ponteiro para a estrutura Background a ser destruída
 */
void destroy_background(Background *bg) 
{
    printf("Destruindo background...\n");
    if (bg->imagem) al_destroy_bitmap(bg->imagem);  // Destroi a imagem se existir
    printf("Background destruído com sucesso!\n\n");
}