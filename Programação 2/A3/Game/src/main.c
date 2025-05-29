#include "includes.h"


int main() 
{
    al_init();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();

    ALLEGRO_MONITOR_INFO info;
    al_get_monitor_info(0, &info);
    int screen_width = info.x2 - info.x1;
    int screen_height = info.y2 - info.y1;

    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    ALLEGRO_DISPLAY *display = al_create_display(screen_width, screen_height);

    EstadoJogo estado_atual = ESTADO_MENU;

    while (estado_atual != ESTADO_SAIR) 
    {
        switch (estado_atual) 
        {
            case ESTADO_MENU:
                estado_atual = run_menu(display);
                break;
            case ESTADO_JOGO:
                estado_atual = run_game(); // atualize esta função também se precisar da tela
                break;
            case ESTADO_GAMEOVER:
                estado_atual = run_gameover(display);
                break;
            case ESTADO_VITORIA:
                estado_atual = run_menu(display);
                break;
            default:
                estado_atual = ESTADO_SAIR;
                break;
        }
    }

    al_destroy_display(display);
    return 0;
}