#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <allegro5/allegro.h>







typedef struct 
{
    float scroll_x;
    ALLEGRO_BITMAP *imagem;
} Background;





void init_background(Background *bg, const char *caminho);

void update_background(Background *bg, float player_x);

void draw_background(Background *bg);

void destroy_background(Background *bg);

#endif