#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "menu.h"

#define LARGURA 900
#define ALTURA 600


//===================================================================================================================================================================


//
EstadoJogo run_menu() 
{
    ALLEGRO_DISPLAY *display = al_create_display(LARGURA, ALTURA);
    ALLEGRO_FONT *font = al_create_builtin_font();
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_EVENT ev;

    al_install_keyboard();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));

    bool running = true;
    while (running) 
    {
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_text(font, al_map_rgb(255, 255, 255), LARGURA / 2, ALTURA / 3, ALLEGRO_ALIGN_CENTER, "GAME");
        al_draw_text(font, al_map_rgb(255, 255, 255), LARGURA / 2, ALTURA / 2, ALLEGRO_ALIGN_CENTER, "Pressione ENTER para jogar");
        al_draw_text(font, al_map_rgb(255, 255, 255), LARGURA / 2, ALTURA / 2 + 30, ALLEGRO_ALIGN_CENTER, "ESC para sair");
        al_flip_display();

        al_wait_for_event(queue, &ev);
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) 
        {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER) 
            {
                running = false;
                al_destroy_event_queue(queue);
                al_destroy_font(font);
                al_destroy_display(display);
                return ESTADO_JOGO;
            } 
            else if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) 
            {
                running = false;
                al_destroy_event_queue(queue);
                al_destroy_font(font);
                al_destroy_display(display);
                return ESTADO_SAIR;
            }
        } 
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
        {
            running = false;
            al_destroy_event_queue(queue);
            al_destroy_font(font);
            al_destroy_display(display);
            return ESTADO_SAIR;
        }
    }

    return ESTADO_MENU;
}


//===================================================================================================================================================================


//
EstadoJogo run_gameover() 
{
    ALLEGRO_DISPLAY *display = al_create_display(LARGURA, ALTURA);
    ALLEGRO_FONT *font = al_create_builtin_font();
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_EVENT ev;

    al_install_keyboard();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));

    bool running = true;
    while (running) 
    {
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_text(font, al_map_rgb(255, 0, 0), LARGURA / 2, ALTURA / 3, ALLEGRO_ALIGN_CENTER, "Game Over");
        al_draw_text(font, al_map_rgb(255, 255, 255), LARGURA / 2, ALTURA / 2, ALLEGRO_ALIGN_CENTER, "Pressione ENTER para voltar ao menu");
        al_flip_display();

        al_wait_for_event(queue, &ev);
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) 
        {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER) 
            {
                running = false;
                al_destroy_event_queue(queue);
                al_destroy_font(font);
                al_destroy_display(display);
                return ESTADO_MENU;
            }
        } 
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
        {
            running = false;
            al_destroy_event_queue(queue);
            al_destroy_font(font);
            al_destroy_display(display);
            return ESTADO_SAIR;
        }
    }

    return ESTADO_MENU;
}
