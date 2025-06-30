#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "includes.h"



//  Estrutura do bakground
typedef struct 
{
    ALLEGRO_BITMAP *imagem;
    int scroll_x;
    int largura;
    int altura;
} Background;


/**
 * Inicializa a estrutura de background carregando a imagem e definindo propriedades
 * 
 * @param bg Ponteiro para a estrutura Background que será inicializada
 * @param caminho Caminho do arquivo de imagem a ser carregado
 */
void init_background(Background *bg, const char *caminho);

//=========================================================================

/**
 * Atualiza a posição de scroll do background baseado na posição do jogador
 * 
 * @param bg Ponteiro para a estrutura Background
 * @param player_pos_mundo_x Posição X atual do jogador no mundo do jogo
*/
void update_background(Background *bg, float player_x);

//=========================================================================

/**
 * Desenha o background na tela com efeito de scroll e looping infinito
 * 
 * @param bg Ponteiro para a estrutura Background 
*/
void draw_background(Background *bg);

//=========================================================================

/**
 * Libera os recursos alocados para o background
 * 
 * @param bg Ponteiro para a estrutura Background a ser destruída
 */
void destroy_background(Background *bg);

//=========================================================================

#endif