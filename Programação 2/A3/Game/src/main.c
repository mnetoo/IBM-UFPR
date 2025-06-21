#include "includes.h"

int main() 
{
    // No início da run_game()
    if (!al_init()) {
        fprintf(stderr, "Erro ao inicializar Allegro.\n");
        return ESTADO_SAIR;
    }

    if (!al_install_keyboard()) {
        fprintf(stderr, "Erro ao inicializar o teclado.\n");
        return ESTADO_SAIR;
    }

    if (!al_init_font_addon() || !al_init_ttf_addon()) {
        fprintf(stderr, "Erro ao inicializar addon de fontes.\n");
        return ESTADO_SAIR;
    }

    if (!al_init_image_addon()) {
        fprintf(stderr, "Erro ao inicializar addon de imagens.\n");
        return ESTADO_SAIR;
    }

    if (!al_init_primitives_addon()) {
        fprintf(stderr, "Erro ao inicializar addon primitives.\n");
        return ESTADO_SAIR;
    }

    if (!al_install_mouse()) {
        fprintf(stderr, "Erro ao inicializar mouse.\n");
        return ESTADO_SAIR;
    }


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
                estado_atual = run_vitoria();
                break;
            default:
                estado_atual = ESTADO_SAIR;
                break;
        }
    }

    return 0;
}