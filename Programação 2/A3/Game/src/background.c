#include "includes.h"

//====================================================================================


// Inicializa o background
void init_background(Background *bg, const char *caminho) 
{
    bg->imagem = al_load_bitmap(caminho);
    bg->scroll_x = 0;
    bg->largura = al_get_bitmap_width(bg->imagem); // salva largura da imagem
    bg->altura = al_get_bitmap_height(bg->imagem); // salva altura
}


//====================================================================================


// Atualiza o background com base na posição do jogador
void update_background(Background *bg, float player_pos_mundo_x)
{
    int centro_tela = TELA_LARGURA / 2;
    bg->scroll_x = (int)(player_pos_mundo_x - centro_tela);

    // Garante que o scroll_x sempre fique no intervalo [0, largura)
    bg->scroll_x %= bg->largura;
    if (bg->scroll_x < 0)
        bg->scroll_x += bg->largura;
}



//====================================================================================


// Desenha o fundo com scroll e efeito de repetição (loop infinito)
void draw_background(Background *bg) 
{
    if (!bg->imagem) return;

    int sx = bg->scroll_x;
    int sw = 300; // largura do recorte
    int sh = bg->altura; // 176
    int screen_h = TELA_ALTURA;
    int screen_w = TELA_LARGURA;

    if (sx + sw <= bg->largura) 
    {
        // Caso 1: tudo dentro da imagem
        al_draw_scaled_bitmap(
            bg->imagem,
            sx, 0,
            sw, sh,
            0, 0,
            screen_w, screen_h,
            0
        );
    } 
    else 
    {
        // Caso 2: parte do final da imagem + parte do início (efeito looping)

        int primeira_parte = bg->largura - sx;
        int segunda_parte = sw - primeira_parte;

        float escala1 = (float)primeira_parte / sw;
        float largura1 = escala1 * screen_w;

        float escala2 = (float)segunda_parte / sw;
        float largura2 = escala2 * screen_w;

        // Desenha primeira parte (final da imagem)
        al_draw_scaled_bitmap(
            bg->imagem,
            sx, 0,
            primeira_parte, sh,
            0, 0,
            largura1, screen_h,
            0
        );

        // Desenha segunda parte (início da imagem)
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


void destroy_background(Background *bg) 
{
    if (bg->imagem) al_destroy_bitmap(bg->imagem);
}