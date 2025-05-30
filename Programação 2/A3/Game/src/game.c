#include "includes.h"

static ALLEGRO_TIMER *timer;
static ALLEGRO_EVENT_QUEUE *queue;
static ALLEGRO_DISPLAY *display;
static ALLEGRO_FONT *font;

static Player player;
static Enemy inimigos[MAX_INIMIGOS];
static Background bg;


//===================================================================================================================================================================


// Função para desenhar um fundo gradiente vertical simples
void desenha_gradiente(ALLEGRO_DISPLAY *display) 
{
    for (int i = 0; i < ALTURA; i++) 
    {
        float r = (float)i / ALTURA * 60;
        float g = (float)i / ALTURA * 60;
        float b = (float)i / ALTURA * 90 + 40;
        al_draw_line(0, i, LARGURA, i, al_map_rgb((int)r, (int)g, (int)b), 1);
    }
}


//==============================================================================================================================================================


//  Função que roda o jogo
EstadoJogo run_game() 
{
    al_install_keyboard();
    al_init_primitives_addon();
    al_init_font_addon();
    font = al_create_builtin_font();

    display = al_create_display(TELA_LARGURA, TELA_ALTURA);
    queue = al_create_event_queue();
    timer = al_create_timer(1.0 / 60.0);

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    init_player(&player);
    init_background(&bg, "./assets/bg/level1.png");

    // Inicializa inimigos
    printf("Inicializando inimigos...\n");
    for (int i = 0; i < MAX_INIMIGOS; i++)
        init_enemy(&inimigos[i], 700 + i * 120, 380);
    printf("Inimigos inicializados com sucesso...\n\n");

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


            al_draw_textf(font, al_map_rgb(255, 255, 255), 20, 20, 0, "Life: %d", player.vida);
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


//==============================================================================================================================================================


//  Função que roda a tela de MENU
EstadoJogo run_menu() 
{
    al_init_primitives_addon();
    ALLEGRO_DISPLAY *display = al_create_display(TELA_LARGURA, TELA_ALTURA);
    al_set_window_title(display, "Menu - Seu Jogo");
    ALLEGRO_FONT *font_titulo = al_load_ttf_font("arial.ttf", 78, 0);
    ALLEGRO_FONT *font_opcao  = al_load_ttf_font("arial.ttf", 48, 0);

    if (!font_titulo || !font_opcao) 
    {
        font_titulo = al_create_builtin_font();
        font_opcao = al_create_builtin_font();
    }

    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_EVENT ev;

    al_install_keyboard();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));


    bool running = true;
    while (running) 
    {
        desenha_gradiente(display);

        al_draw_text(font_titulo, al_map_rgb(255, 255, 255), LARGURA / 2, ALTURA / 4, ALLEGRO_ALIGN_CENTER, "RUNN GUN");
        al_draw_text(font_opcao, al_map_rgb(200, 255, 200), LARGURA / 2, ALTURA / 2, ALLEGRO_ALIGN_CENTER, "Pressione ENTER para Jogar");
        al_draw_text(font_opcao, al_map_rgb(255, 180, 180), LARGURA / 2, ALTURA / 2 + 40, ALLEGRO_ALIGN_CENTER, "Pressione ESC para Sair");

        al_flip_display();

        al_wait_for_event(queue, &ev);
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) 
        {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER) 
            {
                running = false;
                break;
            } 
            else if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) 
            {
                running = false;
                al_destroy_event_queue(queue);
                al_destroy_font(font_titulo);
                al_destroy_font(font_opcao);
                al_destroy_display(display);
                return ESTADO_SAIR;
            }
        } 
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
        {
            running = false;
            al_destroy_event_queue(queue);
            al_destroy_font(font_titulo);
            al_destroy_font(font_opcao);
            al_destroy_display(display);
            return ESTADO_SAIR;
        }
    }

    al_destroy_event_queue(queue);
    al_destroy_font(font_titulo);
    al_destroy_font(font_opcao);
    al_destroy_display(display);
    return ESTADO_JOGO;
}


//==============================================================================================================================================================


//  Função que roda tela de GAME OVER
EstadoJogo run_gameover() 
{
    al_init_primitives_addon();
    ALLEGRO_DISPLAY *display = al_create_display(TELA_LARGURA, TELA_ALTURA);
    al_set_window_title(display, "Game Over");
    ALLEGRO_FONT *font_titulo = al_load_ttf_font("arial.ttf", 78, 0);
    ALLEGRO_FONT *font_opcao  = al_load_ttf_font("arial.ttf", 48, 0);

    if (!font_titulo || !font_opcao) 
    {
        font_titulo = al_create_builtin_font();
        font_opcao = al_create_builtin_font();
    }

    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_EVENT ev;

    al_install_keyboard();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));

    bool running = true;
    while (running) 
    {
        desenha_gradiente(display);

        al_draw_text(font_titulo, al_map_rgb(255, 100, 100), LARGURA / 2, ALTURA / 3,ALLEGRO_ALIGN_CENTER, "GAME OVER");
        al_draw_text(font_opcao, al_map_rgb(255, 255, 255), LARGURA / 2, ALTURA / 2,ALLEGRO_ALIGN_CENTER, "Pressione ENTER para voltar ao menu");

        al_flip_display();

        al_wait_for_event(queue, &ev);
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) 
        {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER) 
            {
                running = false;
                break;
            }
        } 
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
        {
            running = false;
            al_destroy_event_queue(queue);
            al_destroy_font(font_titulo);
            al_destroy_font(font_opcao);
            al_destroy_display(display);
            return ESTADO_SAIR;
        }
    }

    al_destroy_event_queue(queue);
    al_destroy_font(font_titulo);
    al_destroy_font(font_opcao);
    al_destroy_display(display);
    return ESTADO_MENU;
}


//==============================================================================================================================================================