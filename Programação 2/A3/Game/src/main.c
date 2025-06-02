#include "includes.h"

int main() 
{
    al_init();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    al_init_primitives_addon();
    al_install_mouse();


    EstadoJogo estado_atual = ESTADO_MENU;

    while (estado_atual != ESTADO_SAIR) 
    {
        switch (estado_atual) 
        {
            case ESTADO_MENU:
                estado_atual = run_menu();
                break;
            case ESTADO_JOGO:
                estado_atual = run_game();
                break;
            case ESTADO_GAMEOVER:
                estado_atual = run_gameover();
                break;
            case ESTADO_VITORIA:
                estado_atual = run_menu();
                break;
            default:
                estado_atual = ESTADO_SAIR;
                break;
        }
    }

    return 0;
}