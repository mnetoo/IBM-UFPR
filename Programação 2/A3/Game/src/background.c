#include "includes.h"


//====================================================================================


//  Função que inicializa o background
void init_background(Background *bg, const char *caminho) 
{
    bg->imagem = al_load_bitmap(caminho);
    bg->scroll_x = 0;
}


//====================================================================================


//  Função para o Rolling Background
void update_background(Background *bg, float player_x) 
{
    // Atualiza o scroll para seguir o jogador, mas limitado ao tamanho do fundo
    if (player_x > 320)
        bg->scroll_x = player_x - 320;
}


//====================================================================================


//  Carrega o background
void draw_background(Background *bg) 
{
    if (bg->imagem)
        al_draw_bitmap(bg->imagem, 0, 0, 0); // Sem scroll por enquanto
}


//====================================================================================


//  Função que destrói o background
void destroy_background(Background *bg) 
{
    if (bg->imagem) al_destroy_bitmap(bg->imagem);
}


//====================================================================================