#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "includes.h"






//  Estrutura do bakground
typedef struct 
{
    float scroll_x;
    ALLEGRO_BITMAP *imagem;
} Background;


//  Função que inicializa o background
void init_background(Background *bg, const char *caminho);

//=========================================================================

//  Função para o Rolling Background
void update_background(Background *bg, float player_x);

//=========================================================================

//  Carrega o background
void draw_background(Background *bg);

//=========================================================================

//  Função que destrói o background
void destroy_background(Background *bg);

//=========================================================================

#endif