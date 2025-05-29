#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <stdio.h>

#include "./game.h"
#include "./player.h"
#include "./enemy.h"
#include "./background.h"

static ALLEGRO_TIMER *timer;
static ALLEGRO_EVENT_QUEUE *queue;
static ALLEGRO_DISPLAY *display;
static ALLEGRO_FONT *font;

static Player player;
static Enemy inimigos[MAX_INIMIGOS];
static Background bg;


//===================================================================================================================================================================


//
EstadoJogo run_game() 
{
    // Inicialização de Allegro (assume que já foi inicializado no main)
    al_install_keyboard();
    al_init_primitives_addon();
    al_init_font_addon();
    font = al_create_builtin_font();

    display = al_create_display(TELA_LARGURA, TELA_ALTURA);
    queue = al_create_event_queue();
    timer = al_create_timer(1.0 / 60.0); // 60 FPS

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    init_player(&player);
    init_background(&bg, "./assets/bg/level1.png");

    // Inicializa inimigos
    printf("Inicializando inimigos...\n");
    for (int i = 0; i < MAX_INIMIGOS; i++)
        init_enemy(&inimigos[i], 700 + i * 120, 380);
    printf("Inimigos inicializados com sucesso...\n");

    bool running = true;
    bool redraw = true;
    ALLEGRO_EVENT ev;

    al_start_timer(timer);

    while (running) 
    {
        al_wait_for_event(queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
        {
            running = false;
            return ESTADO_SAIR;
        }

        if (ev.type == ALLEGRO_EVENT_TIMER) 
        {
            update_player(&player);
            update_background(&bg, player.x);

            for (int i = 0; i < MAX_INIMIGOS; i++)
                update_enemy(&inimigos[i]);
    

            // Verificar vitória
            bool todos_mortos = true;
            for (int i = 0; i < MAX_INIMIGOS; i++) 
            {
                if (inimigos[i].ativo)
                    todos_mortos = false;
            }

            if (todos_mortos)
                return ESTADO_VITORIA;

            // Game over se vida zerar
            if (player.vida <= 0)
                return ESTADO_GAMEOVER;

            redraw = true;
        }

        if (redraw && al_is_event_queue_empty(queue)) 
        {
            redraw = false;

            // Desenhar
            draw_background(&bg);
            draw_player(&player);

            for (int i = 0; i < MAX_INIMIGOS; i++)
                draw_enemy(&inimigos[i]);


            al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 10, 0, "Vida: %d", player.vida);
            al_flip_display();
            al_clear_to_color(al_map_rgb(0, 0, 0));
        }
    }

    destroy_player(&player);

    for (int i = 0; i < MAX_INIMIGOS; i++) 
        destroy_enemy(&inimigos[i]);

    destroy_background(&bg);

    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_display(display);
    al_destroy_font(font);

    return ESTADO_MENU;
}